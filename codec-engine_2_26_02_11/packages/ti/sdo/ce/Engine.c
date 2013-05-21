/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/*
 *  ======== Engine.c ========
 */
#include <xdc/std.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Lock.h>
#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/ipc/Processor.h>
#include <ti/sdo/ce/osal/Queue.h>
#include <ti/sdo/ce/osal/Global.h>

#include <ti/sdo/ce/rms.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/alg/Algorithm.h>
#include <ti/sdo/ce/node/node.h>
#include <ti/sdo/utils/trace/gt.h>

#include <ti/xdais/ialg.h>

#ifdef WIN32
/* max line line length before forcing a newline for DSP trace */
#define MAXLINE 200
#endif

/* Big enough to hold "gppfromname" + <ID> */
#define MAXCOMMNAMELEN 30

typedef struct RServerObj {
    Processor_Handle  dspProc;
    String            imageName;
    Int               refCount;
} RServerObj, *RServer;

typedef struct Engine_Obj {
    Queue_Elem      link;
    RServer         server;
    Comm_Queue      toRMS;
    Comm_Queue      fromRMS;
    Comm_Handle     msgq;       /* handle for fromRMS */
    UInt16          rmsPoolId;
    Comm_Msg        rmsMsg;
    Engine_Desc     *desc;
    Engine_Error    lastError;
    Bool            hasServer;  /* TRUE <=> there is a server */

    /* Filled in when Engine_initFromServer() is called */
    Engine_AlgDesc *remoteAlgTab;
    Int numRemoteAlgs;
} Engine_Obj;

typedef struct Engine_NodeObj {
    Engine_Handle   engine;
    Comm_Queue      stdIn;      /* the node's input queue */
    Comm_Queue      stdOut;     /* the node's output queue */
    Comm_Handle     msgq;       /* handle for stdOut */
    String          impId;      /* algorithm implementation name */
    RMS_Word        rmsNode;    /* remote node handle */
    size_t          msgSize;    /* size of messages exchanged with node */
    RMS_Word        remoteVisa; /* Remote visa handle */
} Engine_NodeObj;


/*
 *  Stub function entry that can be queued up.
 */
typedef struct Engine_StubFxnsElem {
    Queue_Elem  link;
    String      name;
    IALG_Fxns  *stubFxns;
} Engine_StubFxnsElem;



#if defined(xdc_target__isaCompatible_v5T) || defined(xdc_target__isaCompatible_v4T)
extern Int Global_useLinkArbiter;
#else
#define Global_useLinkArbiter FALSE
#endif


/*
 *  ======== Engine_ALGCREATEATTRS ========
 */
Engine_AlgCreateAttrs Engine_ALGCREATEATTRS = {
    FALSE,      /* Use external heap */
    -1,         /* priority */
};

extern Bool ti_sdo_ce_Engine_noCommName;
extern Bool Server_holdingTraceToken;

static Engine_Node allocNode(Engine_Handle s, String impId);
static RMS_Status callServer(Engine_Handle engine, Comm_Msg *msg);
static Bool checkServer(Engine_Handle engine);
static Void cleanup(Void);
static Int copyToFile(Char *cp, Int size, String prefix, Bool *nl, FILE *out);
static Void freeNode(Engine_Node node);
static Void freeServerTab(Engine_Handle engine);
static String getServerKey(Engine_Handle engine);
static Bool isa(Engine_AlgDesc *alg, String type);
static Void name2Uuid(Engine_Obj *engine, String name, NODE_Uuid *uuid);
static Engine_Handle rmsInit(Engine_Obj *engine, Engine_Error *ec);
static Int getRpcProtocolVersion(Engine_Obj *engine, NODE_Uuid uuid);

#ifdef WIN32
static Int outputDspTrace(Char *cp, Int size, String prefix);
#endif

static Void rserverClose(RServer server);
static RServer rserverOpen(Engine_Desc * desc, Bool * startedServer);

/* REMEMBER: if you add an initialized static var, reinitialize it at cleanup */
static Bool curInit = FALSE;

static RServerObj serverTab[1] = { /* TODO: len should be a config param */
    {NULL, NULL, 0},
};

static Queue_Elem stubFxnsList;

/* set by CERuntime.xdt, determines if to collect DSP trace and how to set it */
Bool   Engine_alwaysCollectDspTrace = FALSE;
String Engine_ceDebugDspTraceMask   = "";

static Lock_Handle serverLock;      /* serialize access to serverTab */
static Lock_Handle traceLock;       /* serialize access in collectDspTrace */
static Lock_Handle engineLock;      /* serialize access in rest of Engine */

static UInt32 gppCommId = 0;        /* ID of the messageQ ("comm") on GPP */

static Engine_Handle localEngine = NULL;
static Queue_Elem engineList;

static Int traceToken = FALSE;

static GT_Mask curTrace;


/*
 *  ======== collectDspTrace ========
 */
static Void collectDspTrace( Engine_Handle engine )
{
    Lock_acquire(traceLock);
    Engine_fwriteTrace( engine, "[DSP] ", stdout );
    Lock_release(traceLock);
}


/*
 *  ======== Engine_addStubFxns ========
 */
Engine_Error Engine_addStubFxns(String fxnsName, IALG_Fxns *fxns)
{
    Engine_StubFxnsElem *stubs;
    Engine_Error         status = Engine_EOK;


    stubs = (Engine_StubFxnsElem *)Memory_alloc(sizeof(Engine_StubFxnsElem),
            NULL);

    if (stubs == NULL) {
        GT_0trace(curTrace, GT_7CLASS, "Engine_addStubFxns> Memory allocation "
                  "failed!\n");
        status = Engine_ENOMEM;
    }
    else {
        Queue_new(&stubs->link);

        stubs->name = fxnsName;
        stubs->stubFxns = fxns;

        Queue_put(&stubFxnsList, stubs);
    }

    return (status);
}


/*
 *  ======== Engine_call ========
 */
Int Engine_call(Engine_Node node, Comm_Msg *msg)
{
    Int status;

    /* ensure that the node simply passes message to exec/call fxn */
    NODE_Msg nodeMsg = (NODE_Msg)*msg;
    nodeMsg->cmd.id = NODE_CCALL;

    /* send the message */
    Comm_setSrcQueue(*msg, node->stdOut);
    status = Comm_put(node->stdIn, *msg);

    /* wait for the return message with the processed result */
    if (status == Comm_EOK) {
        status = Comm_get(node->stdOut, msg, Comm_FOREVER);
    }

    if (Engine_alwaysCollectDspTrace) {
        collectDspTrace( node->engine );
    }

    return (status);
}

/*
 *  ======== Engine_callAsync ========
 */
Int Engine_callAsync(Engine_Node node, Comm_Msg *msg)
{
    Int status;

    /* ensure that the node simply passes message to exec/call fxn */
    NODE_Msg nodeMsg = (NODE_Msg)*msg;
    nodeMsg->cmd.id = NODE_CCALL;

    /* send the message */
    Comm_setSrcQueue(*msg, node->stdOut);
    status = Comm_put(node->stdIn, *msg);

    if (Engine_alwaysCollectDspTrace) {
        collectDspTrace( node->engine );
    }

    /* return w/o waiting for the return message with the processed result */
    return (status);
}

/*
 *  ======== Engine_callWait ========
 */
Int Engine_callWait(Engine_Node node, Comm_Msg *msg, UInt timeout)
{
    Int status;

    status = Comm_get(node->stdOut, msg, timeout);

    if (status != Comm_ETIMEOUT && Engine_alwaysCollectDspTrace) {
        collectDspTrace( node->engine );
    }

    return (status);
}

/*
 *  ======== Engine_getMemStat ========
 */
Engine_Error Engine_getMemStat(Server_Handle server, Int segNum,
    Engine_MemStat *stat)
{
    Engine_Handle    engine = (Engine_Handle)server;
    RMS_RmsMsg      *msg;
    Engine_Error     status = Engine_EOK;

    GT_3trace(curTrace, GT_ENTER, "Engine_getMemStat(0x%lx, %d, 0x%lx)\n",
        engine, segNum, stat);

    if (engine->hasServer != TRUE) {
        return (Engine_ENOSERVER);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        GT_0trace(curTrace, GT_6CLASS,
            "Engine_getMemStat> internal error: rms message null\n");
        return (Engine_ERUNTIME);
    }

    /* Set up command */
    msg->cmdBuf.cmd = RMS_GETSEGSTAT;
    msg->cmdBuf.status = RMS_EFAIL;
    msg->cmdBuf.data.getSegStatIn.segId = segNum;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status == RMS_ENOTFOUND) {
        /* segNum is out of range. */
        status = engine->lastError = Engine_ENOTFOUND;
    }
    else if (msg->cmdBuf.status != RMS_EOK) {
        status = engine->lastError = Engine_ERUNTIME;
    }
    else {
        /* Copy data into stat */
        strncpy(stat->name, (Char *)msg->cmdBuf.data.getSegStatOut.name,
                Engine_MAXSEGNAMELENGTH);
        stat->name[Engine_MAXSEGNAMELENGTH] = '\0';
        stat->base = msg->cmdBuf.data.getSegStatOut.base;
        stat->size = msg->cmdBuf.data.getSegStatOut.size;
        stat->used = msg->cmdBuf.data.getSegStatOut.used;
        stat->maxBlockLen = msg->cmdBuf.data.getSegStatOut.maxBlockLen;
    }

    return (status);
}

/*
 *  ======== Engine_getNumServerAlgs ========
 */
Engine_Error Engine_getNumServerAlgs(Server_Handle server, Int *nAlgs)
{
    Engine_Handle    engine = (Engine_Handle)server;
    RMS_RmsMsg      *msg;
    Engine_Error     status = Engine_EOK;

    GT_2trace(curTrace, GT_ENTER, "Engine_getNumServerAlgs(0x%lx 0x%lx)\n",
        engine, nAlgs);

    if (engine->hasServer != TRUE) {
        GT_0trace(curTrace, GT_6CLASS,
            "Engine_getNumServerAlgs> Engine does not have a server\n");
        return (Engine_ENOSERVER);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        GT_0trace(curTrace, GT_6CLASS,
            "Engine_getNumServerAlgs> internal error: rms message null\n");
        return (Engine_ERUNTIME);
    }

    /* copy command */
    msg->cmdBuf.cmd = RMS_GETNUMALGS;
    msg->cmdBuf.status = RMS_EFAIL;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        engine->lastError = Engine_ERUNTIME;
        status = Engine_ERUNTIME;
    }
    else {
        *nAlgs = msg->cmdBuf.data.getNumAlgsOut.numAlgs;
    }

    GT_1trace(curTrace, GT_ENTER, "Engine_getNumServerAlgs number of server "
            "algs = %d\n", *nAlgs);

    GT_1trace(curTrace, GT_ENTER, "Engine_getNumServerAlgs exit %d\n", status);
    return (status);
}

/*
 *  ======== Engine_getNumMemSegs ========
 */
Engine_Error Engine_getNumMemSegs(Server_Handle server, Int *numSegs)
{
    Engine_Handle    engine = (Engine_Handle)server;
    RMS_RmsMsg      *msg;
    Engine_Error     status = Engine_EOK;

    GT_2trace(curTrace, GT_ENTER, "Engine_getNumMemSegs(0x%lx 0x%lx)\n",
        engine, numSegs);

    if (engine->hasServer != TRUE) {
        return (Engine_ENOSERVER);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        GT_0trace(curTrace, GT_6CLASS,
            "Engine_getNumMemSegs> internal error: rms message null\n");
        return (Engine_ERUNTIME);
    }

    /* copy command */
    msg->cmdBuf.cmd = RMS_GETNUMSEGS;
    msg->cmdBuf.status = RMS_EFAIL;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        engine->lastError = Engine_ERUNTIME;
        status = Engine_ERUNTIME;
    }
    else {
        *numSegs = msg->cmdBuf.data.getNumSegsOut.numSegs;
    }

    return (status);
}

/*
 *  ======== Engine_close ========
 */
Void Engine_close(Engine_Handle engine)
{
    GT_1trace(curTrace, GT_ENTER, "Engine_close(0x%lx)\n", engine);

    if (engine != NULL) {

        if (Engine_alwaysCollectDspTrace) {
            collectDspTrace( engine );
        }

        /*
         *  If we're not connected to trace, traceToken will be FALSE and
         *  this function will just return.
         */
        Server_disconnectTrace((Server_Handle)engine, traceToken);

        /* atomically remove engine from any list it may be on */
        Queue_extract(&engine->link);

        if (engine->rmsMsg != NULL) {
            Comm_free(engine->rmsMsg);
        }

        if (engine->msgq != NULL) {
            Comm_delete(engine->msgq);
        }

        if (engine->toRMS != Comm_INVALIDMSGQ) {
            Comm_release(engine->toRMS);
        }

        if (engine->server != NULL) {
            rserverClose(engine->server);
        }

        if (engine->remoteAlgTab != NULL) {
            freeServerTab(engine);
        }

        /* free Engine object */
        Memory_free(engine, sizeof (Engine_Obj), NULL);
    }

    GT_0trace(curTrace, GT_ENTER, "Engine_close exit\n");
}

/*
 *  ======== Engine_createNode ========
 */
Engine_Node Engine_createNode(Engine_Handle engine, String impId,
    size_t msgSize, IALG_Params *nodeAttrs, Engine_AlgCreateAttrs *attrs)
{
    Int nodeAttrsSize;

    GT_5trace(curTrace, GT_ENTER,
            "Engine_createNode(0x%lx, '%s', %d, 0x%lx, 0x%lx)\n",
            engine, impId, msgSize, nodeAttrs, attrs);

    nodeAttrsSize = nodeAttrs ? nodeAttrs->size : 0;

    return (Engine_createNode2(engine, impId, msgSize, nodeAttrs, nodeAttrsSize,
            attrs));
}

/*
 *  ======== Engine_createNode2 ========
 */
Engine_Node Engine_createNode2(Engine_Handle engine, String impId,
    size_t msgSize, IALG_Params *nodeAttrs, Int nodeAttrsSize,
    Engine_AlgCreateAttrs *attrs)
{
    RMS_RmsMsg *msg;
    Engine_Node node = NULL;

    GT_6trace(curTrace, GT_ENTER,
            "Engine_createNode(0x%lx, '%s', %d, 0x%lx, 0x%lx, 0x%lx)\n",
            engine, impId, msgSize, nodeAttrs, nodeAttrsSize, attrs);

    if (attrs == NULL) {
        attrs = &Engine_ALGCREATEATTRS;
    }

    if (nodeAttrsSize > (sizeof(RMS_Word) * RMS_MAXARGSLENGTH)) {
        GT_2trace(curTrace, GT_6CLASS,
                "Engine_createNode> rms message size [%d] insufficient"
                " for nodeAttrsSize [%d]\n",
                sizeof(RMS_Word) * RMS_MAXARGSLENGTH, nodeAttrsSize);

        engine->lastError = Engine_EINVAL;
        goto createNodeEnd;
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        GT_0trace(curTrace, GT_6CLASS,
                "Engine_createNode> internal error: rms message null\n");

        engine->lastError = Engine_ERUNTIME;
        goto createNodeEnd;
    }

    if ((node = allocNode(engine, impId)) == NULL) {
        GT_0trace(curTrace, GT_6CLASS,
                "Engine_createNode> Node allocation failed.\n");

        /* engine->lastError is set in allocNode, don't override it */
        goto createNodeEnd;
    }

    node->msgSize = msgSize;

    /* init a "node create" message */
    msg->cmdBuf.cmd = RMS_CREATENODE;
    msg->cmdBuf.status = RMS_EFAIL;
    name2Uuid(engine, impId, &msg->cmdBuf.data.createNodeIn.uuid);
    msg->cmdBuf.data.createNodeIn.rpcProtocolVersion =
        getRpcProtocolVersion(engine, msg->cmdBuf.data.createNodeIn.uuid);
    msg->cmdBuf.data.createNodeIn.gppQueue = node->stdOut;
    msg->cmdBuf.data.createNodeIn.nodePriority = attrs->priority;
    msg->cmdBuf.data.createNodeIn.useExtHeap = attrs->useExtHeap;

    if (nodeAttrs == NULL) {
        msg->cmdBuf.data.createNodeIn.argLength = 0;
    }
    else {
        assert(nodeAttrsSize <= (sizeof (RMS_Word) * RMS_MAXARGSLENGTH));
        msg->cmdBuf.data.createNodeIn.argLength = nodeAttrsSize;
        memcpy(msg->cmdBuf.data.createNodeIn.argBuffer, nodeAttrs,
                nodeAttrsSize);
    }

    /* send create message to RMS */
    Comm_setSrcQueue((Comm_Msg)msg, engine->fromRMS);
    if (Comm_put(engine->toRMS, (Comm_Msg)msg) == Comm_EOK) {
        Int status;
        status = Comm_get(engine->fromRMS, (Comm_Msg *)&msg, Comm_FOREVER);
        assert(status == Comm_EOK);
        engine->rmsMsg = (Comm_Msg)msg;
    }
    else {
        freeNode(node);
        node = NULL;
        GT_0trace(curTrace, GT_6CLASS,
                "Engine_createNode> FAILED to send creation msg to DSP.\n");

        engine->lastError = Engine_ENOCOMM;
        goto createNodeEnd;
    }

    /* check that remote create succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        freeNode(node);
        node = NULL;
        GT_1trace(curTrace, GT_6CLASS,
            "Engine_createNode> Remote node creation FAILED (0x%x).\n",
            msg->cmdBuf.status);
        engine->lastError = Engine_ECODECCREATE;

        goto createNodeEnd;
    }

    /* get the remote node and visa handles, and remote message queue */
    node->rmsNode = msg->cmdBuf.data.createNodeOut.node;
    node->remoteVisa = msg->cmdBuf.data.createNodeOut.remoteVisa;

    /* we really should do a locate here!!! */
    node->stdIn = msg->cmdBuf.data.createNodeOut.nodeQueue;

    /* put start message to engine's RMS */
    msg->cmdBuf.cmd = RMS_STARTNODE;
    msg->cmdBuf.status = RMS_EFAIL;
    msg->cmdBuf.data.startNodeIn.node = node->rmsNode;
    Comm_setSrcQueue((Comm_Msg)msg, engine->fromRMS);
    if (Comm_put(engine->toRMS, (Comm_Msg)msg) == Comm_EOK) {
        Int status;
        status = Comm_get(engine->fromRMS, (Comm_Msg *)&msg, Comm_FOREVER);
        assert(status == Comm_EOK);
        engine->rmsMsg = (Comm_Msg)msg;
    }

    /* check that remote start succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        freeNode(node);
        node = NULL;
        GT_1trace(curTrace, GT_6CLASS,
            "Engine_createNode> Remote start FAILED (0x%x).\n",
            msg->cmdBuf.status);

        engine->lastError = Engine_ECODECSTART;
        goto createNodeEnd;
    }

    GT_6trace(curTrace, GT_4CLASS, "Engine_createNode> created node"
        "(stdIn=0x%x, stdOut=0x%x, msgq=0x%x, algName='%s', rmsNode=0x%x, "
        "algHandle=0x%x)\n", node->stdIn, node->stdOut,
        node->msgq, node->impId, node->rmsNode, node->remoteVisa);

createNodeEnd:

    if (Engine_alwaysCollectDspTrace) {
        collectDspTrace( engine );
    }

    GT_1trace(curTrace, GT_2CLASS,
        "Engine_createNode> Returning 0x%x\n", node);

    return (node);
}

/*
 *  ======== Engine_ctrlNode ========
 */
Int Engine_ctrlNode(Engine_Node node, Comm_Msg *msg, Engine_Ctrl code)
{
    Int status;
    NODE_Msg nodeMsg = (NODE_Msg)*msg;

    GT_3trace(curTrace, GT_ENTER, "Engine_ctrlNode(0x%lx, 0x%x, 0x%x)\n",
            node, msg, code);

    if (code != Engine_CEXIT) {
        return (Engine_EINVAL);
    }

    nodeMsg->cmd.id = NODE_CEXIT;

    /* send the message */
    Comm_setSrcQueue(*msg, node->stdOut);
    status = Comm_put(node->stdIn, *msg);

    /* wait for the return message with the processed result */
    if (status == Comm_EOK) {
        status = Comm_get(node->stdOut, msg, Comm_FOREVER);
    }

    GT_1trace(curTrace, GT_ENTER, "Engine_ctrlNode> Returning 0x%x\n", status);

    return (status);
}
/*
 *  ======== Engine_deleteNode ========
 */
Void Engine_deleteNode(Engine_Node node)
{
    Engine_Handle engine = node->engine;
    RMS_RmsMsg *msg = (RMS_RmsMsg *)engine->rmsMsg;

    GT_1trace(curTrace, GT_ENTER, "Engine_deleteNode(0x%lx)\n", node);

    /* init a node delete message */
    msg->cmdBuf.cmd = RMS_DELETENODE;
    msg->cmdBuf.data.deleteNodeIn.node = node->rmsNode;

    /* put delete node message to engine's RMS */
    Comm_setSrcQueue((Comm_Msg)msg, engine->fromRMS);
    if (Comm_put(engine->toRMS, (Comm_Msg)msg) == Comm_EOK) {
        Int status;
        status = Comm_get(engine->fromRMS, (Comm_Msg *)&msg, Comm_FOREVER);
        if (status == Comm_EOK) {
            /* check stack size to see if we are close to overrun */
            UInt8 classMask = GT_5CLASS;
            UInt stacksize = msg->cmdBuf.data.deleteNodeOut.stackSize;
            UInt stackused = msg->cmdBuf.data.deleteNodeOut.stackUsed;
            Int headroom = 100;

            if (stacksize != 0) {
                headroom = (stacksize > stackused)
                    ? ((stacksize - stackused) * 100) / stacksize : 0;
            }

            if (headroom < 10) {
                classMask |= GT_6CLASS; /* less than 10%, generate warning */
            }
            GT_6trace(curTrace, classMask, "Engine_deleteNode(0x%x): "
                "algName = %s, algHandle = 0x%x, stack size = %d, "
                "stack used = %d(%d%%)\n",
                node, node->impId, node->remoteVisa,
                stacksize, stackused, 100 - headroom);

            engine->rmsMsg = (Comm_Msg)msg;
        }
    }

    freeNode(node);
}

/*
 *  ======== Engine_getAlgInfo ========
 */
Engine_Error Engine_getAlgInfo(String name, Engine_AlgInfo *algInfo, Int index)
{
    Engine_AlgDesc  *alg;
    Engine_Desc     *desc;
    Engine_Error     status = Engine_EOK;

    GT_3trace(curTrace, GT_ENTER, "Engine_getAlgInfo('%s', 0x%lx, 0x%x)\n",
        name, algInfo, index);

    /* Make sure size matches with this library version's size */
    if (algInfo->algInfoSize != sizeof(Engine_AlgInfo)) {
        GT_2trace(curTrace, GT_6CLASS,
            "Engine_getAlgInfo(): Input Engine_AlgInfo struct size [%d]"
            "does not match library Engine_AlgInfo struct size [%d]\n",
            algInfo->algInfoSize, sizeof(Engine_AlgInfo));
        return (Engine_EINVAL);
    }

    /* parse name and locate engine */
    for (desc = Engine_config.engineTab; desc->name != NULL; desc++) {
        if (strcmp(desc->name, name) == 0) {
            break;
        }
    }

    if (desc->name == NULL) {
        return (Engine_EEXIST);
    }

    if ((index < 0) || (index >= desc->numAlgs)) {
        return (Engine_ENOTFOUND);
    }

    /* Engine found - get alg info */
    alg = &(desc->algTab[index]);

    algInfo->name = alg->name;
    algInfo->typeTab = alg->typeTab;
    algInfo->isLocal = alg->isLocal;

    return (status);
}

/*
 *  ======== Engine_getAlgInfo2 ========
 */
Engine_Error Engine_getAlgInfo2(String name, Engine_Handle engine,
        Engine_AlgInfo2 *algInfo2, Int index)
{
    Engine_AlgDesc  *alg;
    Engine_Desc     *desc;
    Engine_Error     status = Engine_EOK;

    GT_4trace(curTrace, GT_ENTER, "Engine_getAlgInfo2('%s', 0x%lx, "
            "0x%lx, 0x%x)\n", name, engine, algInfo2, index);

    /* Make sure size matches with this library version's size */
    if (algInfo2->algInfoSize != sizeof(Engine_AlgInfo2)) {
        GT_2trace(curTrace, GT_6CLASS,
            "Engine_getAlgInfo2(): Input Engine_AlgInfo2 struct size [%d]"
            "does not match library Engine_AlgInfo2 struct size [%d]\n",
            algInfo2->algInfoSize, sizeof(Engine_AlgInfo2));
        return (Engine_EINVAL);
    }

    if (engine == NULL) {
        /* parse name and locate engine */
        for (desc = Engine_config.engineTab; desc->name != NULL; desc++) {
            if (strcmp(desc->name, name) == 0) {
                break;
            }
        }

        if (desc->name == NULL) {
            return (Engine_EEXIST);
        }

        if ((index < 0) || (index >= desc->numAlgs)) {
            return (Engine_ENOTFOUND);
        }

        /* Engine found - get alg info */
        alg = &(desc->algTab[index]);
    }
    else {
        desc = engine->desc;
        if ((index < 0) || (index >= (desc->numAlgs + engine->numRemoteAlgs))){
            GT_2trace(curTrace, GT_6CLASS, "Engine_getAlgInfo2> index [%d] "
                    "out of range. Maximum number of algs = %d\n", index,
                    desc->numAlgs + engine->numRemoteAlgs);
            return (Engine_ENOTFOUND);
        }

        if (index < engine->desc->numAlgs) {
            alg = &(desc->algTab[index]);
        }
        else {
            alg = &(engine->remoteAlgTab[index - engine->desc->numAlgs]);
        }
    }

    algInfo2->isLocal = alg->isLocal;
    algInfo2->name = alg->name;

    /*
     *  For auto-generated alg tables and algs obtained from the server,
     *  alg->types will not be NULL. If alg table was not generated with
     *  XDC tools (eg, for run-time config), this could be NULL. In that
     *  case, just use typeTab[0], since that will contain the complete
     *  inheritence hierarchy (assuming the it was configured correctly by
     *  the app).
     */
    algInfo2->types = (alg->types == NULL) ? alg->typeTab[0] : alg->types;

    return (status);
}


/*
 *  ======== Engine_getAlgMemRecs ========
 */
Engine_Error Engine_getAlgMemRecs(Engine_Node node, IALG_MemRec *memTab,
        Int size, Int *numRecs)
{
    Engine_Handle    engine;
    RMS_RmsMsg      *msg;
    Int              nRecs;
    Int              i;
    IALG_MemRec     *memRecs;
    Engine_Error     status = Engine_EOK;

    GT_4trace(curTrace, GT_ENTER,
            "Engine_getAlgMemRecs(0x%lx, 0x%x, %d, 0x%lx)\n",
        node, memTab, size, numRecs);

    engine = node->engine;
    msg = (RMS_RmsMsg *)engine->rmsMsg;

    /* Compute maximum number of IALG_MemRecs that can be copied. */
    nRecs = (size > RMS_MAXMEMRECS) ? RMS_MAXMEMRECS : size;
    if (size > nRecs) {
        GT_3trace(curTrace, GT_4CLASS,
                "Engine_getAlgMemRecs: memTab array size (%d) is larger"
                " then the number of records that can be copied (%d) for"
                " node (0x%x)\n",
                size, RMS_MAXMEMRECS, node);
    }

    /* Set up command */
    msg->cmdBuf.cmd = RMS_GETMEMRECS;
    msg->cmdBuf.status = RMS_EFAIL;
    msg->cmdBuf.data.getMemRecsIn.node = node->rmsNode;
    msg->cmdBuf.data.getMemRecsIn.numRecs = nRecs;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        // TODO: Determine what type of errors will be returned.
        if (msg->cmdBuf.status == RMS_EINVAL) {
            status = engine->lastError = Engine_EINVAL;
        }
        else if (msg->cmdBuf.status == RMS_ENOTFOUND) {
            status = engine->lastError = Engine_ENOTFOUND;
        }
        else {
            status = engine->lastError = Engine_ERUNTIME;
        }
    }
    else {
        *numRecs = msg->cmdBuf.data.getMemRecsOut.numRecs;
        memRecs = (IALG_MemRec *)(msg->cmdBuf.data.getMemRecsOut.memRecs);

        for (i = 0; i < nRecs; i++) {
            memTab[i] = memRecs[i];
        }
    }

    GT_1trace(curTrace, GT_ENTER,
        "Engine_getAlgMemRecs> Returning %d\n", status);

    return (status);
}

/*
 *  ======== Engine_getAlgNumRecs ========
 */
Engine_Error Engine_getAlgNumRecs(Engine_Node node, Int *numRecs)
{
    Engine_Handle    engine;
    RMS_RmsMsg      *msg;
    Engine_Error     status = Engine_EOK;

    GT_2trace(curTrace, GT_ENTER, "Engine_getAlgNumRecs(0x%lx, 0x%x)\n",
        node, numRecs);

    engine = node->engine;
    msg = (RMS_RmsMsg *)engine->rmsMsg;

    /* Set up command */
    msg->cmdBuf.cmd = RMS_GETNUMMEMRECS;
    msg->cmdBuf.status = RMS_EFAIL;
    msg->cmdBuf.data.getNumRecsIn.node = node->rmsNode;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        // TODO: Determine what type of errors will be returned.
        if (msg->cmdBuf.status == RMS_EINVAL) {
            status = engine->lastError = Engine_EINVAL;
        }
        else if (msg->cmdBuf.status == RMS_ENOTFOUND) {
            status = engine->lastError = Engine_ENOTFOUND;
        }
        else {
            status = engine->lastError = Engine_ERUNTIME;
        }
    }
    else {
        *numRecs = msg->cmdBuf.data.getNumRecsOut.numRecs;
    }

    GT_1trace(curTrace, GT_ENTER,
        "Engine_getAlgNumRecs> Returning %d\n", status);

    return (status);
}

/*
 *  ======== Engine_getNumAlgs ========
 */
Engine_Error Engine_getNumAlgs(String name, Int *numAlgs)
{
    Engine_Desc      *desc;

    GT_2trace(curTrace, GT_ENTER, "Engine_getNumAlgs('%s', 0x%lx)\n",
        name, numAlgs);

    *numAlgs = 0;

    /* parse name and locate engine */
    for (desc = Engine_config.engineTab; desc->name != NULL; desc++) {
        if (strcmp(desc->name, name) == 0) {
            break;
        }
    }
    if (desc->name == NULL) {
        return (Engine_EEXIST);
    }

    /* Engine found - get number of algs */
    *numAlgs = desc->numAlgs;

    return (Engine_EOK);
}

/*
 *  ======== Engine_getNumAlgs2 ========
 */
Engine_Error Engine_getNumAlgs2(String name, Engine_Handle engine, Int *nAlgs)
{
    Engine_Desc      *desc;

    GT_3trace(curTrace, GT_ENTER, "Engine_getNumAlgs2('%s', 0x%ls, 0x%lx)\n",
        name, engine, nAlgs);

    *nAlgs = 0;

    if (engine == NULL) {
        return (Engine_getNumAlgs(name, nAlgs));
    }
    else {
        desc = engine->desc;
        *nAlgs = desc->numAlgs + engine->numRemoteAlgs;
    }

    return (Engine_EOK);
}


/*
 *  ======== Engine_getConstName ========
 */
String Engine_getConstName(Engine_Handle engine, String name, String type)
{
    Engine_AlgDesc *alg;
    Engine_AlgDesc *algTab;

    if (engine == NULL) {
        engine = Engine_getLocalEngine();
    }

    algTab = engine->desc->algTab;

    if (algTab != NULL) {
        for (alg = algTab; alg->name != NULL; alg++) {
            if (strcmp(name, alg->name) == 0) {
                if (isa(alg, type)) {
                    return (alg->name);
                }
            }
        }
    }

    algTab = engine->remoteAlgTab;

    if (algTab != NULL) {
        for (alg = algTab; alg->name != NULL; alg++) {
            if (strcmp(name, alg->name) == 0) {
                if (isa(alg, type)) {
                    return (alg->name);
                }
            }
        }
    }

    GT_2trace(curTrace, GT_6CLASS, "Engine_getConstName> Unable to locate "
            "alg \"%s\" (type \"%s\").\n", name, type);
    return (NULL);
}

/*
 *  ======== Engine_getFxns ========
 */
IALG_Fxns *Engine_getFxns(Engine_Handle engine, String name, String type,
        Bool *isLocal, Ptr *idmaFxns, Ptr *iresFxns, Int *groupId,
        Engine_CachedMemType *memType)
{
    Engine_AlgDesc *alg;
    Engine_AlgDesc *algTab;

    if (engine == NULL) {
        engine = Engine_getLocalEngine();
    }

    algTab = engine->desc->algTab;

    if (algTab != NULL) {
        for (alg = algTab; alg->name != NULL; alg++) {
            if (strcmp(name, alg->name) == 0) {
                if (isa(alg, type)) {
                    *isLocal = alg->isLocal;
                    *idmaFxns = alg->idmaFxns;
                    *iresFxns = alg->iresFxns;
                    *groupId = alg->groupId;
                    *memType = alg->memType;
                    return (alg->fxns);
                }
            }
        }
    }

    algTab = engine->remoteAlgTab;

    if (algTab != NULL) {
        for (alg = algTab; alg->name != NULL; alg++) {
            if (strcmp(name, alg->name) == 0) {
                if (isa(alg, type)) {
                    *isLocal = alg->isLocal;
                    *idmaFxns = alg->idmaFxns;
                    *iresFxns = alg->iresFxns;
                    *groupId = alg->groupId;
                    *memType = alg->memType;
                    return (alg->fxns);
                }
            }
        }
    }

    GT_1trace(curTrace, GT_6CLASS,
        "Engine_getFxns> Unable to locate alg \"%s\".\n", name);
    return (NULL);
}

/*
 *  ======== Engine_getLocalEngine ========
 */
Engine_Handle Engine_getLocalEngine(Void)
{
    if (localEngine == NULL) {
        localEngine = Engine_open(Engine_config.localEngine, NULL, NULL);
    }

    return (localEngine);
}

/*
 *  ======== Engine_getMemId ========
 */
Int Engine_getMemId(Engine_Handle engine)
{
    if (engine == NULL) {
        engine = Engine_getLocalEngine();
    }

    return (engine->rmsPoolId);
}

/*
 *  ======== Engine_getEngine ========
 */
Engine_Handle Engine_getEngine(Engine_Node node)
{
    return (node->engine);
}

/*
 *  ======== Engine_getCpuLoad ========
 */
Int Engine_getCpuLoad(Engine_Handle engine)
{
    RMS_RmsMsg *msg;

    GT_1trace(curTrace, GT_ENTER, "Engine_getCpuLoad(0x%lx)\n", engine);

    /* This function is only valid for the Server CPU load */
    if (engine->hasServer != TRUE) {
        GT_0trace(curTrace, GT_6CLASS,
            "Engine_getCpuLoad> Only valid if there is a server\n");
        engine->lastError = Engine_ERUNTIME;
        return (-1);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        engine->lastError = Engine_ERUNTIME;
        return (-1);
    }

    /* init a "get CPU status" message */
    msg->cmdBuf.cmd = RMS_GETCPUSTAT;
    msg->cmdBuf.status = RMS_EFAIL;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        engine->lastError = Engine_ERUNTIME;
        return (-1);
    }

    return (msg->cmdBuf.data.getCpuStatOut.cpuLoad);
}

/*
 *  ======== Engine_getLastError ========
 */
Engine_Error Engine_getLastError(Engine_Handle engine)
{
    return (engine->lastError);
}

/*
 *  ======== Engine_getServer ========
 */
Server_Handle Engine_getServer(Engine_Handle engine)
{
    GT_1trace(curTrace, GT_ENTER, "Engine_getServer(0x%lx)\n", engine);

    if (engine->hasServer) {
        return ((Server_Handle)engine);
    }
    else {
        engine->lastError = Engine_ENOSERVER;
        return (NULL);
    }
}

/*
 *  ======== Engine_getServerAlgInfo ========
 */
Engine_Error Engine_getServerAlgInfo(Server_Handle server, Int algNum,
        Engine_AlgInfo *algInfo)
{
    Engine_Handle    engine = (Engine_Handle)server;
    Engine_Error     status = Engine_EOK;

    GT_3trace(curTrace, GT_ENTER, "Engine_getServerAlgInfo(0x%x %d 0x%x)\n",
            engine, algNum, algInfo);

    if ((algNum < 0) || (algNum > engine->numRemoteAlgs)) {
        GT_2trace(curTrace, GT_6CLASS, "Engine_getServerAlgInfo> Index [%d] "
                "of requested alg is out of range. The number of remote "
                "algs is [%d]\n", algNum, engine->numRemoteAlgs);
        status = Engine_EINVAL;
    }
    else {
        algInfo->name = engine->remoteAlgTab[algNum].name;
        algInfo->typeTab = engine->remoteAlgTab[algNum].typeTab;
        algInfo->isLocal = FALSE;
    }

    GT_1trace(curTrace, GT_ENTER, "Engine_getServerAlgInfo> returning [%d]\n",
            status);

    return (status);
}

/*
 *  ======== Engine_getCodecClassConfig ========
 */
Ptr Engine_getCodecClassConfig(Engine_Handle engine, String name, String type)
{
    Engine_AlgDesc *alg;
    Engine_AlgDesc *algTab;

    if (engine == NULL) {
        engine = Engine_getLocalEngine();
    }

    algTab = engine->desc->algTab;

    if (algTab != NULL) {
        for (alg = algTab; alg->name != NULL; alg++) {
            if (strcmp(name, alg->name) == 0) {
                if (isa(alg, type)) {
                    return (alg->codecClassConfig);
                }
            }
        }
    }

    return (NULL);
}

/*
 *  ======== Engine_initFromServer ========
 */
Engine_Error Engine_initFromServer(Engine_Handle engine)
{
    RMS_RmsMsg      *msg;
    Int              index;
    Int              i;
    Int              len;
    Char            *algName;
    Char            *typeTab;
    Char            *stubsName;
    Engine_AlgDesc  *desc = NULL;
    Engine_AlgDesc  *alg = NULL;
    Int              numAlgs = 0;
    Int              numRemoteAlgs = 0;
    Engine_StubFxnsElem *stubs;
    Engine_Error     status = Engine_EOK;


    GT_1trace(curTrace, GT_ENTER, "Engine_initFromServer(0x%lx)\n", engine);

    if (engine->hasServer != TRUE) {
        GT_1trace(curTrace, GT_ENTER, "Engine_initFromServer> Returning %d\n",
                status);
        return (Engine_ENOSERVER);
    }

    /* Get the number of algs on the server */
    status = Engine_getNumServerAlgs((Server_Handle)engine, &numAlgs);

    if (status != Engine_EOK) {
        GT_1trace(curTrace, GT_7CLASS, "Engine_initFromServer> Failed to "
                  "get number of server algs, returning %d\n", status);
        return (status);
    }

    if (numAlgs <= 0) {
        /* Shouldn't happen, but just in case... */
        GT_1trace(curTrace, GT_6CLASS, "Engine_initFromServer> Server has "
                  "no remote algs, returning %d\n", status);
        return (status);
    }

    /* Count the number of remote algs that were statically configured. */
    alg = engine->desc->algTab;
    numRemoteAlgs = 0;
    for (; (alg != NULL) && (alg->name != NULL); alg++) {
        if (alg->isLocal == FALSE) {
            numRemoteAlgs++;
        }
    }

    GT_1trace(curTrace, GT_2CLASS, "Engine_initFromServer> Number of remote "
            "algs statically configured in engine: %d\n", numRemoteAlgs);

    if (numAlgs == numRemoteAlgs) {
        /*
         *  ALl remote algs were statically configured. No need to get
         *  information from the server.
         */
        GT_1trace(curTrace, GT_2CLASS, "Engine_initFromServer> Number of "
                "statically configured remote algs = number of server "
                "algs: %d\n", numAlgs);

        GT_1trace(curTrace, GT_ENTER, "Engine_initFromServer> Returning %d\n",
                status);
        return (status);
    }

    /*
     *  Server contains remote algs that were not statically configured
     *  into the engine. Allocate a table to hold server's alg info, and
     *  get the alg info from the server.
     */

    GT_1trace(curTrace, GT_2CLASS, "Engine_initFromServer> Allocating  "
            "descriptor array for [%d] server algs\n", numAlgs);
    desc = (Engine_AlgDesc *)Memory_alloc(sizeof(Engine_AlgDesc) * numAlgs,
            NULL);
    if (desc == NULL) {
        GT_0trace(curTrace, GT_7CLASS, "Engine_initFromServer> Failed "
                "to allocate memory for engine table\n");
        status = Engine_ENOMEM;
    }

    GT_1trace(curTrace, GT_2CLASS, "Engine_initFromServer> Initializing  "
            "descriptor array for [%d] server algs\n", numAlgs);
    if (status == Engine_EOK) {
        for (i = 0; i < numAlgs; i++) {
            /*
             *  Initialize desc fields that will be alloc'd so we don't
             *  try to free invalid memory if something goes wrong.
             */
            desc[i].name = NULL;
            desc[i].typeTab = NULL;
        }
    }

    if (status == Engine_EOK) {
        if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
            GT_0trace(curTrace, GT_6CLASS, "Engine_initFromServer> "
                    "internal error: rms message null\n");
            status = Engine_ERUNTIME;
        }
    }

    index = 0;
    while ((status == Engine_EOK) && (index < numAlgs)) {
        /* Get the info for alg 'index' */
        msg->cmdBuf.cmd = RMS_GETALG;
        msg->cmdBuf.status = RMS_EFAIL;
        msg->cmdBuf.data.getAlgIn.index = index;

        GT_1trace(curTrace, GT_2CLASS, "Engine_initFromServer> "
                "Sending RMS_GETALG command for alg [%d]\n", index);
        callServer(engine, (Comm_Msg *)&msg);

        engine->rmsMsg = (Comm_Msg)msg;

        /* check that remote cmd succeeded */
        if (msg->cmdBuf.status == RMS_ENOTFOUND) {
            /* Index is out of range (shouldn't happen), we're done. */
            GT_2trace(curTrace, GT_6CLASS, "Engine_initFromServer> WARNING "
                    "Cannot get info for alg [%d], numAlgs = %d\n",
                    index, numAlgs);
            break;
        }
        else if (msg->cmdBuf.status != RMS_EOK) {
            status = engine->lastError = Engine_ERUNTIME;
            GT_2trace(curTrace, GT_7CLASS, "Engine_initFromServer> "
                    "failed to get information for alg [%d] from server. "
                    "status = 0x%x\n", index, msg->cmdBuf.status);
        }
        else {
            /* Copy the codec name */
            algName = (Char *)msg->cmdBuf.data.getAlgOut.name;
            len = strlen(algName);
            desc[index].name = Memory_alloc(len + 1, NULL);
            if (desc[index].name == NULL) {
                GT_0trace(curTrace, GT_7CLASS, "Engine_initFromServer> "
                        "Memory allocation failed!\n");
                status = Engine_ENOMEM;
                break;
            }
            strcpy(desc[index].name, algName);
            desc[index].name[len] = '\0';

            /*
             *  Use a simplified typeTab, where strings are separated by ';'
             *  instead of having an array of strings. We still need a null
             *  terminated array to conform to the Engine_AlgDesc structure.
             */
            desc[index].typeTab = Memory_alloc(2 * sizeof(String *), NULL);
            if (desc[index].typeTab == NULL) {
                GT_0trace(curTrace, GT_7CLASS, "Engine_initFromServer> "
                        "Memory allocation failed!\n");
                status = Engine_ENOMEM;
                break;
            }

            desc[index].typeTab[1] = NULL;

            typeTab = (Char *)msg->cmdBuf.data.getAlgOut.typeTab;
            len = strlen(typeTab);
            desc[index].typeTab[0] = Memory_alloc(len + 1, NULL);

            if (desc[index].typeTab[0] == NULL) {
                GT_0trace(curTrace, GT_7CLASS, "Engine_initFromServer> "
                        "Memory allocation for typeTab[0] failed!\n");
                status = Engine_ENOMEM;
                break;
            }
            strcpy(desc[index].typeTab[0], typeTab);
            desc[index].typeTab[0][len] = '\0';
            desc[index].types = desc[index].typeTab[0];

            /*
             *  Look up the stub functions in table. If they're not found,
             *  just leave them as NULL. In that case the alg cannot be
             *  used.
             */
            stubsName = (Char *)msg->cmdBuf.data.getAlgOut.stubFxns;
            desc[index].fxns = NULL;
            i = 0;

            stubs = (Engine_StubFxnsElem *)Queue_head(&stubFxnsList);
            while ((Queue_Elem *)stubs != &stubFxnsList) {
                if ((strcmp(stubsName, stubs->name)) == 0) {
                    /* Found match */
                    desc[index].fxns = stubs->stubFxns;
                    break;
                }
                stubs = Queue_next(stubs);
            }
            if (desc[index].fxns == NULL) {
                GT_1trace(curTrace, GT_5CLASS, "Engine_initFromServer> "
                        "Warning: No stub functions were found for %s. "
                        "The algorithm that requires these stub functions "
                        "cannot be run remotely.\n", stubsName);
            }

            desc[index].uuid = msg->cmdBuf.data.getAlgOut.uuid;

            /* Don't care about groupId since alg is remote */
            desc[index].groupId = -1;

            desc[index].rpcProtocolVersion =
                msg->cmdBuf.data.getAlgOut.rpcProtocolVersion;

            /* Fill in the rest */
            desc[index].idmaFxns = NULL;
            desc[index].isLocal = FALSE;
            desc[index].iresFxns = NULL;
            desc[index].memType = Engine_USECACHEDMEM_DEFAULT;
            desc[index].codecClassConfig = NULL;  // Is this right?

            /*
             *  Print a warning if another alg of the same name already exists
             *  in the static engine table.
             */
            alg = engine->desc->algTab;
            algName = desc[index].name;
            for (; (alg != NULL) && (alg->name != NULL); alg++) {
                if ((strcmp(algName, alg->name) == 0) && alg->isLocal) {
                    GT_1trace(curTrace, GT_6CLASS, "Engine_initFromServer> "
                            "WARNING: Local algorithm named \"%s\" in "
                            "static engine table matches a server alg name. "
                            "Behavior as to which algorithm will be created "
                            "when using this name is undefined.\n", alg->name);
                }
            }

            index++;
        }
    }

    /*
     *  Assign these even if an error occurred so we can call freeServerTab()
     *  to clean things up.
     */
    engine->numRemoteAlgs = (desc == NULL) ? 0 : numAlgs;
    engine->remoteAlgTab = desc;

    if (status != Engine_EOK) {
        /* Free anything allocated so far */
        freeServerTab(engine);
    }

    GT_1trace(curTrace, GT_ENTER, "Engine_initFromServer engine->server = "
            "0x%x\n", engine->server);

    GT_1trace(curTrace, GT_ENTER, "Engine_initFromServer> Returning %d\n",
            status);

    return (status);
}

/*
 *  ======== Engine_redefineHeap ========
 */
Engine_Error Engine_redefineHeap(Server_Handle server, String name,
        Uint32 base, Uint32 size)
{
    Engine_Handle    engine = (Engine_Handle)server;
    String           heapName;
    RMS_RmsMsg      *msg;
    Engine_Error     status = Engine_EOK;

    GT_4trace(curTrace, GT_ENTER, "Engine_redefineHeap(0x%x %s 0x%x 0x%x)\n",
            engine, name, base, size);

    if (engine->hasServer != TRUE) {
        return (Engine_ENOSERVER);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        GT_0trace(curTrace, GT_6CLASS,
            "Engine_redefineHeap> internal error: rms message null\n");
        return (Engine_ERUNTIME);
    }

    /* Set up command */
    msg->cmdBuf.cmd = RMS_REDEFINEHEAP;
    msg->cmdBuf.status = RMS_EFAIL;

    heapName = (Char *)(msg->cmdBuf.data.redefineHeapIn.name);
    strncpy(heapName, name, RMS_MAXSEGNAMELENGTH);
    heapName[RMS_MAXSEGNAMELENGTH] = '\0';

    msg->cmdBuf.data.redefineHeapIn.base = base;
    msg->cmdBuf.data.redefineHeapIn.size = size;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        if (msg->cmdBuf.status == RMS_EFREE) {
            /* The heap is still in use on the DSP */
            status = engine->lastError = Engine_EINUSE;
        }
        else if (msg->cmdBuf.status == RMS_EINVAL) {
            status = engine->lastError = Engine_EINVAL;
        }
        else if (msg->cmdBuf.status == RMS_ENOTFOUND) {
            status = engine->lastError = Engine_ENOTFOUND;
        }
        else {
            status = engine->lastError = Engine_ERUNTIME;
        }
    }

    return (status);
}

/*
 *  ======== Engine_releaseTraceToken ========
 */
Bool Engine_releaseTraceToken(Server_Handle server)
{
    Engine_Handle engine = (Engine_Handle)server;
    RMS_RmsMsg *msg;

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        engine->lastError = Engine_ERUNTIME;
        return (FALSE);
    }

    /* init a "release trace token" message */
    msg->cmdBuf.cmd = RMS_RELTRACETOKEN;
    msg->cmdBuf.status = RMS_EFAIL;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        return (FALSE);
    }
    else {
        return (TRUE);
    }
}

/*
 *  ======== Engine_requestTraceToken ========
 */
Engine_Error Engine_requestTraceToken(Server_Handle server)
{
    Engine_Handle engine = (Engine_Handle)server;
    Engine_Error status = Engine_ERUNTIME;
    RMS_RmsMsg *msg;

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) != NULL) {

        /* init a "request trace token" message */
        msg->cmdBuf.cmd = RMS_REQTRACETOKEN;
        msg->cmdBuf.status = RMS_EFAIL;

        callServer(engine, (Comm_Msg *)&msg);

        engine->rmsMsg = (Comm_Msg)msg;

        /* check if remote cmd succeeded */
        if (msg->cmdBuf.status == RMS_EOK) {
            status = Engine_EOK;
        }
        else if (msg->cmdBuf.status == RMS_ERESOURCE) {
            status = Engine_EINUSE;
        }
    }

    return(status);
}

/*
 *  ======== Engine_restoreHeap ========
 */
Engine_Error Engine_restoreHeap(Server_Handle server, String name)
{
    Engine_Handle    engine = (Engine_Handle)server;
    RMS_RmsMsg      *msg;
    String           heapName;
    Engine_Error     status = Engine_EOK;

    GT_1trace(curTrace, GT_ENTER, "Engine_restoreHeap(0x%x)\n", engine);

    if (engine->hasServer != TRUE) {
        return (Engine_ENOSERVER);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        GT_0trace(curTrace, GT_6CLASS,
            "Engine_restoreHeap> internal error: rms message null\n");
        return (Engine_ERUNTIME);
    }

    /* Set up command */
    msg->cmdBuf.cmd = RMS_RESTOREHEAP;
    msg->cmdBuf.status = RMS_EFAIL;

    heapName = (Char *)(msg->cmdBuf.data.restoreHeapIn.name);
    strncpy(heapName, name, RMS_MAXSEGNAMELENGTH);
    heapName[RMS_MAXSEGNAMELENGTH] = '\0';

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        if (msg->cmdBuf.status == RMS_EFREE) {
            /* The heap is still in use on the DSP */
            status = engine->lastError = Engine_EINUSE;
        }
        else if (msg->cmdBuf.status == RMS_EINVAL) {
            status = engine->lastError = Engine_EINVAL;
        }
        else if (msg->cmdBuf.status == RMS_ENOTFOUND) {
            status = engine->lastError = Engine_ENOTFOUND;
        }
        else {
            status = engine->lastError = Engine_ERUNTIME;
        }
    }

    return (status);
}

/*
 *  ======== Engine_fwriteTrace ========
 */
Int Engine_fwriteTrace(Engine_Handle engine, String prefix, FILE *out)
{
    RMS_RmsMsg *msg;
    Int count = 0;
    Int readCount = 0;
    Bool newLine = TRUE;

    /* this should really be the ENTER class but it obscures the output */
    GT_3trace(curTrace, GT_3CLASS, "Engine_fwriteTrace(0x%lx, '%s', 0x%lx)\n",
        engine, prefix, out);

    if (engine->hasServer != TRUE) {
        GT_0trace(curTrace, GT_3CLASS,
                "Engine_fwriteTrace> Engine has no server\n");
        return (0);
    }

    if (!Server_holdingTraceToken) {
        GT_0trace(curTrace, GT_3CLASS, "Engine_fwriteTrace> Engine in use\n");
        engine->lastError = Engine_EINUSE;
        return (-1);
    }

    do {
        UInt32 timeKey;

        if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
            engine->lastError = Engine_ERUNTIME;
            return (-1);
        }


        timeKey = GT_curTime();

        /* init a "get trace" message */
        msg->cmdBuf.cmd = RMS_GETTRACE;
        msg->cmdBuf.status = RMS_EFAIL;
        msg->cmdBuf.data.getTraceIn.curTime = timeKey;
        msg->cmdBuf.data.getTraceOut.size = 0;
        msg->cmdBuf.data.getTraceOut.lost = 0;

        GT_1trace(curTrace, GT_3CLASS,
            "Engine_fwriteTrace(): requesting DSP trace @0x%x ...\n", timeKey);

        /* send it to the DSP and wait for results ... */
        callServer(engine, (Comm_Msg *)&msg);

        engine->rmsMsg = (Comm_Msg)msg;

        /* check that remote cmd succeeded */
        if (msg->cmdBuf.status != RMS_EOK) {
            engine->lastError = Engine_ERUNTIME;
            return (-1);
        }

        GT_5trace(curTrace, GT_3CLASS, "Engine_fwriteTrace> "
            "got %d chars @0x%x (%d still avail, max: %d, lost: %d)\n",
            msg->cmdBuf.data.getTraceOut.size,
            timeKey,
            msg->cmdBuf.data.getTraceOut.avail,
            msg->cmdBuf.data.getTraceOut.max,
            msg->cmdBuf.data.getTraceOut.lost);

        readCount += msg->cmdBuf.data.getTraceOut.size;

        if (msg->cmdBuf.data.getTraceOut.lost > 0) {
            fprintf(out, " [ARM] WARNING: lost %d characters of DSP server trace "
                    "due to buffer wrapping (got %d chars, %d left, max=%d; "
                    "collect trace more often, or add "
                    "Server.traceBufferSize = <largerSizeInBytes> "
                    "to DSP server's .cfg file). %s",
                    msg->cmdBuf.data.getTraceOut.lost,
                    msg->cmdBuf.data.getTraceOut.size,
                    msg->cmdBuf.data.getTraceOut.avail,
                    msg->cmdBuf.data.getTraceOut.max, prefix );
            newLine = FALSE;
        }

#ifdef WIN32
        /*
         *  Use GT->PRINTFXN to output DSP trace for WinCE.
         *  TODO: Should we do this for Linux too?
         */
        count += outputDspTrace((Char *)msg->cmdBuf.data.getTraceOut.buf,
                msg->cmdBuf.data.getTraceOut.size, prefix);
#else
        /* write to file stream */
        count += copyToFile((Char *)msg->cmdBuf.data.getTraceOut.buf,
            msg->cmdBuf.data.getTraceOut.size, prefix, &newLine, out);
#endif

    } while ((msg->cmdBuf.data.getTraceOut.avail > 0)
        && (readCount < msg->cmdBuf.data.getTraceOut.max));

    /* return number of characters actually copied */
    GT_1trace(curTrace, GT_ENTER, "Engine_fwriteTrace> returning count [%d]\n",
            count);
    return (count);
}

/*
 *  ======== Engine_getName ========
 */
String Engine_getName(Engine_Handle engine)
{
    return (engine->desc->name);
}

/*
 *  ======== Engine_getRemoteVisa ========
 */
UInt32 Engine_getRemoteVisa(Engine_Node node)
{
    GT_assert(curTrace, node != NULL);

    return (node->remoteVisa);
}

/*
 *  ======== Engine_getNodeQueues ========
 */
Void Engine_getNodeQueues(Engine_Node node,
    Comm_Queue *stdIn, Comm_Queue *stdOut)
{
    if (node != NULL) {
        *stdIn  = node->stdIn;
        *stdOut = node->stdOut;
    }
    else {
        *stdIn  = Comm_INVALIDMSGQ;
        *stdOut = Comm_INVALIDMSGQ;
    }
}

/*
 *  ======== Engine_getUsedMem ========
 */
UInt32 Engine_getUsedMem(Engine_Handle engine)
{
    RMS_RmsMsg *msg;

    GT_1trace(curTrace, GT_ENTER, "Engine_getUsedMem(0x%lx)\n", engine);

    if (engine->hasServer != TRUE) {
        engine->lastError = Engine_ENOTAVAIL;
        return (0);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        engine->lastError = Engine_ERUNTIME;
        return (0);
    }

    /* init a "node create" message */
    msg->cmdBuf.cmd = RMS_GETMEMSTAT;
    msg->cmdBuf.status = RMS_EFAIL;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        engine->lastError = Engine_ERUNTIME;
        return (0);
    }

    return (msg->cmdBuf.data.getMemStatOut.used);
}

/*
 *  ======== Engine_hasServer ========
 */
Bool Engine_hasServer(Engine_Handle engine)
{
    if (engine) {
        return (engine->hasServer);
    }
    else {
        return (FALSE);
    }
}

/*
 *  ======== Engine_init ========
 */
Void Engine_init(Void)
{
    Engine_Desc    *desc = NULL;
    Engine_AlgDesc *alg = NULL;
    Engine_AlgDesc *algTab = NULL;
    Int             numAlgs;

    if (curInit != TRUE) {
        curInit = TRUE;

        GT_create(&curTrace, Engine_GTNAME);

        if (Global_getenv("CE_DEBUG") != NULL) {
            GT_1trace(curTrace, GT_6CLASS, "Engine_init> CE debugging on "
                      "(CE_DEBUG=%s; allowed CE_DEBUG levels: "
                      "1=min, 2=good, 3=max)\n", Global_getenv("CE_DEBUG") );
        }

        Queue_new(&engineList);
        Queue_new(&stubFxnsList);
        Global_atexit((Fxn)cleanup);

        serverLock = Lock_create(NULL);
        assert(serverLock != NULL);

        traceLock = Lock_create(NULL);
        assert(traceLock != NULL);

        engineLock = Lock_create(NULL);
        assert(engineLock != NULL);

        /*
         *  For each engine, go through the alg table, and add the group ID
         *  of each local alg. This enables run-time config apps to not
         *  have to set up an array of group IDs that are used.
         *
         *  Also make sure the number of numAlgs in the engine desc matches the
         *  number of algs in the engine desc algTab. Correct numAlgs, if
         *  necessary (this mismatch is possible for run-time configuration,
         *  where the engine table is set up with incorrect numAlgs).
         */
        for (desc = Engine_config.engineTab; desc->name != NULL; desc++) {
            algTab = desc->algTab;

            if (algTab != NULL) {
                numAlgs = 0;
                for (alg = algTab; alg->name != NULL; alg++) {
                    numAlgs++;
                    if (alg->isLocal) {
                        Algorithm_addGroup(alg->groupId);
                    }
                }
                if (desc->numAlgs != numAlgs) {
                    GT_3trace(curTrace, GT_5CLASS, "Engine_init> Descriptor "
                            "for engine %s configured with %d algs. Setting "
                            "to actual number of algs: %d.\n", desc->name,
                            desc->numAlgs, numAlgs);
                    desc->numAlgs = numAlgs;
                }
            }
        }
    }
}

/*
 *  ======== Engine_open ========
 */
Engine_Handle Engine_open(String name, Engine_Attrs *attrs, Engine_Error *ec)
{
    Engine_Handle engine;
    Engine_Desc  *desc;
    Engine_Error dummy;

    if (ec == NULL) {
        ec = &dummy;
    }

    GT_3trace(curTrace, GT_ENTER, "Engine_open> Enter('%s', 0x%lx, 0x%x)\n",
        name, attrs, ec);

    /* parse name and locate engine */
    for (desc = Engine_config.engineTab; desc->name != NULL; desc++) {
        if (strcmp(desc->name, name) == 0) {
            break;
        }
    }
    if (desc->name == NULL) {
        *ec = Engine_EEXIST;
        return (NULL);
    }

    /* create Engine object */
    engine = (Engine_Obj *)Memory_alloc(sizeof (struct Engine_Obj), NULL);
    if (engine == NULL) {
        *ec = Engine_ENOMEM;
        return (NULL);
    }

    /* initialize Engine_Obj fields */
    Queue_new(&engine->link);
    engine->server = NULL;
    engine->toRMS = Comm_INVALIDMSGQ;
    engine->fromRMS = Comm_INVALIDMSGQ;
    engine->msgq = NULL;
    engine->rmsPoolId = 0;
    engine->rmsMsg = NULL;
    engine->desc = desc;
    engine->hasServer = FALSE;
    engine->remoteAlgTab = NULL;
    engine->numRemoteAlgs = 0;

    /*
     *  If we're getting trace from the DSP, make sure that the thread that
     *  starts up the RMS server also sends the trace mask to the DSP.
     */
    if (Engine_alwaysCollectDspTrace) {
        Lock_acquire(engineLock);
    }

    /* initialize RMS communications */
    engine = rmsInit(engine, ec);
    GT_1trace(curTrace, GT_4CLASS, "Engine_open> engine->server = 0x%x\n",
            engine->server);

    if (Engine_alwaysCollectDspTrace) {
        Lock_release(engineLock);
    }

    if ((engine != NULL) && Engine_alwaysCollectDspTrace) {
        collectDspTrace( engine );
    }

    /* Initialize alg table with server algs */
    if (engine && engine->hasServer) {
        *ec = Engine_initFromServer(engine);
        if (*ec != Engine_EOK) {
            GT_1trace(curTrace, GT_6CLASS, "Engine_open> WARNING: Unable to "
                    "initialize remote enging alg table from server. "
                    "Status = %d\n", *ec);
        }
    }

    GT_1trace(curTrace, GT_ENTER, "Engine_open> return(%d)\n", engine);

    return (engine);
}

/*
 *  ======== Engine_setTrace ========
 */
Int Engine_setTrace(Engine_Handle engine, String mask)
{
    RMS_RmsMsg *msg;
    int         retVal = Engine_EOK;

    GT_2trace(curTrace, GT_ENTER, "Engine_setTrace> "
        "Enter(engine=0x%x, mask='%s')\n", engine, mask);

    if (engine->hasServer != TRUE) {
        retVal = Engine_ENOSERVER;
        goto setTrace_return;
    }

    if (!Server_holdingTraceToken) {
        retVal = Engine_EINUSE;
        goto setTrace_return;
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        retVal = Engine_ERUNTIME;
        goto setTrace_return;
    }

    /* init a "set trace" message */
    msg->cmdBuf.cmd = RMS_SETTRACEMASK;
    msg->cmdBuf.status = RMS_EFAIL;
    strncpy((Char *)msg->cmdBuf.data.setTraceMaskIn.traceMask, mask,
        RMS_MAXTRACEMASKSIZE);
    if (strlen(mask) > RMS_MAXTRACEMASKSIZE) {
        GT_1trace(curTrace, GT_6CLASS, "Engine_setTrace> "
            "Warning: server trace mask too long, truncated to %d chars.\n",
            RMS_MAXTRACEMASKSIZE);
    }
    GT_0trace(curTrace, GT_1CLASS, "Engine_setTrace> "
        "Requesting DSP set trace ...\n");

    /* send it to the DSP and wait for results ... */
    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        retVal = Engine_ERUNTIME;
        goto setTrace_return;
    }

setTrace_return:

    GT_1trace(curTrace, GT_ENTER, "Engine_setTrace> return(%d)\n", retVal);
    return (retVal);
}

/*
 *  ======== allocNode ========
 */
static Engine_Node allocNode(Engine_Handle engine, String impId)
{
    Engine_Node node;
    UInt32      commId;
    Char        commName[ MAXCOMMNAMELEN ];

    GT_2trace(curTrace, GT_ENTER, "Engine> allocNode "
        "Enter(engine=0x%x, impId='%s')\n", engine, impId);

    /* allocate local node object */
    node = (Engine_NodeObj *)Memory_alloc(sizeof (Engine_NodeObj), NULL);
    if (node == NULL) {
        engine->lastError = Engine_ENOMEM;
        return (NULL);
    }

    node->engine = engine;
    node->impId = impId;

    /* create a unique comm name */
    Lock_acquire(engineLock);
    commId = gppCommId++;
    Lock_release(engineLock);

    if (ti_sdo_ce_Engine_noCommName == FALSE) {
        /* Assign a name to the message queue */
        sprintf( commName, "gppfromnode_%lu_%u", Global_getProcessId(),
                (unsigned)commId );

        /* create Comm for messages from the "remote" node */
        GT_2trace(curTrace, GT_ENTER, "Engine> allocNode(). Calling ("
                "Comm_create(%s, 0x%x, NULL)\n", commName, &node->stdOut);
        node->msgq = Comm_create(commName, &node->stdOut, NULL);
    }
    else {
        /*
         *  Assign NULL to mesage queue name.  This is necessary in WinCE
         *  when different drivers running in kernel (hence the same process
         *  id) call Engine_open().  MSGQ will not allow two queues to be
         *  created with the same name, so we pass NULL to avoid this.
         *  Since we will never use Comm_locate(), we don't care about the
         *  name.
         */
        GT_1trace(curTrace, GT_ENTER, "Engine> allocNode(). Calling "
                "Comm_create(NULL, 0x%x, NULL)\n", &node->stdOut);
        node->msgq = Comm_create(NULL, &node->stdOut, NULL);
    }

    if (node->msgq == NULL) {
        freeNode(node);
        engine->lastError = Engine_ENOCOMM;
        return (NULL);
    }

    return (node);
}

/*
 *  ======== callServer ========
 */
static RMS_Status callServer(Engine_Handle engine, Comm_Msg *msg)
{
    /* set reply queue to our fromRMS queue */
    Comm_setSrcQueue(*msg, engine->fromRMS);

    /* send create message to RMS */
    if (Comm_put(engine->toRMS, *msg) == Comm_EOK) {
        Int status;
        /* wait for reply on fromRMS queue */
        status = Comm_get(engine->fromRMS, msg, Comm_FOREVER);
        assert(status == Comm_EOK);
    }

    return (((RMS_RmsMsg *)(*msg))->cmdBuf.status);
}

/*
 *  ======== checkServer ========
 */
static Bool checkServer(Engine_Handle engine)
{
    /* This string is defined in ti/sdo/ce/libvers.xdt */
    extern String ti_sdo_ce__versionString;

    GT_1trace(curTrace, GT_ENTER, "checkServer(0x%lx)\n", engine);

    /*
     *  TODO: Also send message to RMS to get the RPC protocol version
     *  to make sure it matches.
     */
    if (ti_sdo_ce__versionString != NULL) {
        String skey = getServerKey(engine);

        if (skey == NULL || strcmp(skey, ti_sdo_ce__versionString) != 0) {
            /* if skey == NULL, lastError has already been set */
            if (skey != NULL) {
                engine->lastError = Engine_EBADSERVER;
            }
            GT_3trace(curTrace, GT_6CLASS,
                "checkServer(0x%lx) failed: server = '%s', engine = '%s'\n",
                engine, skey == NULL ? "" : skey, ti_sdo_ce__versionString);
            return (FALSE);
        }
    }

    return (TRUE);
}

/*
 *  ======== cleanup ========
 */
static Void cleanup(Void)
{
    Engine_Desc    *desc;
    Engine_AlgDesc *algTab;
    Engine_AlgDesc *alg;

    static RServerObj serverTabInit = {NULL, NULL, 0};

    if (curInit != FALSE) {
        curInit = FALSE;

        #if 0
        while (Queue_head(&engineList) != &engineList) {
            Engine_Handle engine = Queue_get(&engineList);
            Engine_close(engine);
        }
        #endif

        while (Queue_head(&stubFxnsList) != &stubFxnsList) {
            Engine_StubFxnsElem *stubs = Queue_get(&stubFxnsList);
            Memory_free(stubs, sizeof(Engine_StubFxnsElem), NULL);
        }

        for (desc = Engine_config.engineTab; desc->name != NULL; desc++) {
            algTab = desc->algTab;

            if (algTab != NULL) {
                for (alg = algTab; alg->name != NULL; alg++) {
                    if (alg->isLocal) {
                        Algorithm_removeGroup(alg->groupId);
                    }
                }
            }
        }

        if (serverLock != NULL) {
            Lock_delete(serverLock);
        }
        if (traceLock != NULL) {
            Lock_delete(traceLock);
        }
        if (engineLock != NULL) {
            Lock_delete(engineLock);
        }
        gppCommId = 0;

        /* reinitialize static vars */
        serverTab[0] = serverTabInit;
        localEngine = NULL;
    }
}

/*
 *  ======== copyToFile ========
 *  copy buffer to file stream with optional prefix in front of each line
 */
static Int copyToFile(Char *cp, Int size, String prefix, Bool *newLine,
    FILE *out)
{
    Int count, i;
    Int prefixLen = 0;

    if ((prefix != NULL) && (prefix[0] != '\0')) {
        prefixLen = strlen(prefix);
    }

    count = 0;
    for (i = 0; i < size; i++) {
        if (prefixLen > 0 && *newLine) {
            fputs(prefix, out);
            count += prefixLen;
            *newLine = FALSE;
        }

        fputc(cp[i], out);
        count++;

        if (cp[i] == '\n') {
            *newLine = TRUE;
        }
    }

    return (count);
}

#ifdef WIN32
/*
 *  ======== outputDspTrace ========
 *  Output DSP trace messages.
 */
static Int outputDspTrace(Char *cp, Int size, String prefix)
{
    static Char buffer[MAXLINE + 3];
    static Int  bufIndex = 0;
    static Bool newLine = TRUE;
    Int         count;
    Int         i, j;
    Int         prefixLen = 0;

    if ((prefix != NULL) && (prefix[0] != '\0')) {
        prefixLen = strlen(prefix);

        /* Cut the prefix in half if it's too big (should never happen). */
        if (prefixLen > MAXLINE) {
            prefixLen = MAXLINE / 2;
        }
    }

    count = 0;

    for (i = 0; i < size; i++) {
        /* Hit a newline, copy the prefix to beginning of buffer. */
        if (newLine) {
            for (j = 0; j < prefixLen; j++) {
                buffer[j] = prefix[j];
            }

            count += prefixLen;
            bufIndex = prefixLen;
            newLine = FALSE;
        }

        buffer[bufIndex++] = cp[i];
        count++;

        if ((cp[i] == '\n') || (bufIndex >= MAXLINE)) {
            newLine = TRUE;
            buffer[bufIndex] = 0;
            bufIndex = 0;

            if (GT->PRINTFXN) {
                (*GT->PRINTFXN)(buffer);
            }
        }
    }

    return (count);
}
#endif

/*
 *  ======== freeNode ========
 */
static Void freeNode(Engine_Node node)
{
    if (node != NULL) {
        if (node->msgq != NULL) {
            Comm_delete(node->msgq);
        }

        Memory_free(node, sizeof(Engine_NodeObj), NULL);
    }
}

/*
 *  ======== freeServerTab ========
 */
static Void freeServerTab(Engine_Handle engine)
{
    Engine_AlgDesc *desc;
    Int             i;
    Int             len;
    Int             nAlgs = engine->numRemoteAlgs;


    GT_1trace(curTrace, GT_ENTER, "Engine freeServerTab() enter(0x%x)\n",
            engine);
    
    GT_1trace(curTrace, GT_2CLASS, "Engine freeServerTab() engine->"
            "numRemoteAlgs = %d\n", nAlgs);

    if (engine->remoteAlgTab == NULL) {
        return;
    }

    for (i = 0; i < nAlgs; i++) {
        desc = &(engine->remoteAlgTab[i]);

        if (desc->name) {
            Memory_free(desc->name, strlen(desc->name) + 1, NULL);
        }
        if (desc->typeTab) {
            if (desc->typeTab[0]) {
                len = strlen(desc->typeTab[0]) + 1;
                Memory_free(desc->typeTab[0], len, NULL);
            }
            Memory_free(desc->typeTab, 2 * sizeof(String *), NULL);
        }
    }
    Memory_free(engine->remoteAlgTab, nAlgs * sizeof(Engine_AlgDesc),NULL);

    engine->numRemoteAlgs = 0;
    engine->remoteAlgTab = NULL;

    GT_0trace(curTrace, GT_ENTER, "Engine freeServerTab() exit\n");
}

/*
 *  ======== getServerKey ========
 */
static String getServerKey(Engine_Handle engine)
{
    RMS_RmsMsg *msg;

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        engine->lastError = Engine_ERUNTIME;
        return (NULL);
    }

    /* init a "node create" message */
    msg->cmdBuf.cmd = RMS_GETVERS;
    msg->cmdBuf.status = RMS_EFAIL;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        engine->lastError = Engine_ERUNTIME;
        return (NULL);
    }

    /* Check the protocol version */
    if ((msg->cmdBuf.data.getVersOut.rpcMajor != RMS_VERSION_MAJOR) ||
            (msg->cmdBuf.data.getVersOut.rpcSource != RMS_VERSION_SOURCE) ||
            (msg->cmdBuf.data.getVersOut.rpcMinor < RMS_VERSION_MINOR)) {

        GT_1trace(curTrace, GT_6CLASS,
                "getServerKey(0x%lx) protocol mismatch: \n", engine);
        GT_3trace(curTrace, GT_6CLASS,
                "   server: major = %d, source key = %d, minor key = %d\n",
                msg->cmdBuf.data.getVersOut.rpcMajor,
                msg->cmdBuf.data.getVersOut.rpcSource,
                msg->cmdBuf.data.getVersOut.rpcMinor);
        GT_3trace(curTrace, GT_6CLASS,
                "   engine: major = %d, source key = %d, minor key = %d\n",
                RMS_VERSION_MAJOR, RMS_VERSION_SOURCE, RMS_VERSION_MINOR);

        engine->lastError = Engine_ERUNTIME;
        return (NULL);
    }

    return ((String)msg->cmdBuf.data.getVersOut.vers);
}

/*
 *  ======== getRpcProtocolVersion ========
 *
 *  TODO:L For performance reasons, it'd likely be quicker to look this up
 *  given a UUID rather than a name.  Then we could do "==" rather than
 *  "strcmp".
 */
static Int getRpcProtocolVersion(Engine_Handle engine, NODE_Uuid uuid)
{
    Engine_AlgDesc *alg;
    Int i;
    Int ver = -1;

    alg = engine->desc->algTab;
    for (; (alg != NULL) && (alg->name != NULL); alg++) {
        if (NODE_uuidMatch(&(alg->uuid), &uuid)) {
            /* match */
            ver = alg->rpcProtocolVersion;
            return (ver);
        }
    }

    /* Check dynamic table, if not found in static table */
    if (engine->remoteAlgTab) {
        for (i = 0; i < engine->numRemoteAlgs; i++) {
            if (NODE_uuidMatch(&(engine->remoteAlgTab[i].uuid), &uuid)) {
                ver = engine->remoteAlgTab[i].rpcProtocolVersion;
                break;
            }
        }
    }

    return (ver);
}

/*
 *  ======== isa ========
 */
static Bool isa(Engine_AlgDesc *alg, String type)
{
    String *tp;
    Char   *endStr = NULL;
    Char   *begStr = NULL;
    Char    sep = ';';
    Int     len;

    if ((tp = alg->typeTab) != NULL) {
        for (; *tp != NULL; tp++) {
            if ((endStr = strchr(*tp, sep)) == NULL) {
                /* typeTab is an array of types, not separated by ';' */
                if (strcmp(*tp, type) == 0) {
                    return (TRUE);
                }
            }
            else {
                /* all types are in typeTab[0], separated by ';' */
                begStr = *tp;
                while ((begStr != NULL) && (*begStr != '\0')) {
                    len = (endStr != NULL) ? endStr - begStr : strlen(begStr);
                    if ((strncmp(begStr, type, len) == 0) &&
                            (strlen(type) == len)) {
                        return (TRUE);
                    }

                    begStr = (endStr == NULL) ? NULL : endStr + 1;
                    endStr = (endStr == NULL) ? NULL : strchr(begStr, sep);
                }

                if (endStr == NULL) {
                    return (FALSE);
                }
            }
        }
    }

    return (FALSE);
}

/*
 *  ======== name2Uuid ========
 *  map the name of the algorithm supplied by the application to an
 *  implementation to a UUID.  This id is used on the server-side to lookup
 *  the appropriate NODE_Desc; i.e., the skeleton fxns, stack size, priority,
 *  etc.
 */
static Void name2Uuid(Engine_Handle engine, String name, NODE_Uuid *uuid)
{
    Engine_AlgDesc *alg;
    Int             i;

    /*
     *  Check the engine's static alg table.
     */
    alg = engine->desc->algTab;
    for (; (alg != NULL) && (alg->name != NULL); alg++) {
        if (strcmp(alg->name, name) == 0) {
            *uuid = alg->uuid;
            return;
        }
    }

    /* Alg was not found in the static alg table, check the dynamic table. */
    if (engine->remoteAlgTab) {
        for (i = 0; i < engine->numRemoteAlgs; i++) {
            if (strcmp(engine->remoteAlgTab[i].name, name) == 0) {
                *uuid = engine->remoteAlgTab[i].uuid;
                break;
            }
        }
    }
}

/*
 *  ======== rmsInit ========
 */
static Engine_Handle rmsInit(Engine_Obj *engine, Engine_Error *ec)
{
    Int             status;
    Engine_AlgDesc *alg;
    Bool            startedServer = FALSE;
    String          traceMask = NULL;
    UInt32          commId, commNameLength;
    String          commName = NULL;
    String          algName = NULL;

    /* if all fxns are local there is no need for an RMS server */
    alg = engine->desc->algTab;
    for (; (alg != NULL) && (alg->name != NULL); alg++) {
        if (alg->isLocal != TRUE) {
            algName = alg->name;
            break;
        }
    }

    if ((algName != NULL) || (engine->desc->remoteName != NULL)) {
        /* There are remote algorithms */
        engine->hasServer = TRUE;

        if (engine->desc->remoteName == NULL) {
            /* strange, but supported, the "remote" server is on this proc */
            engine->server = NULL;
        }
        else {
            /* load, start, and connect to RMS */
            engine->server = rserverOpen(engine->desc, &startedServer);
            if (engine->server == NULL) {
                *ec = Engine_EDSPLOAD;
                goto fail;
            }
        }

        /* create a unique name for the Comm (MSGQ) */
        Lock_acquire(engineLock);
        commId = gppCommId++;
        Lock_release(engineLock);

        if (ti_sdo_ce_Engine_noCommName == FALSE) {
            commNameLength =  strlen(engine->desc->name) + MAXCOMMNAMELEN;
            commName = (String)Memory_alloc( commNameLength, NULL );
            if (commName == NULL) {
                *ec = Engine_ENOMEM;
                goto fail;
            }
            sprintf( commName, "%s_%lu_%u", engine->desc->name,
                    Global_getProcessId(), (unsigned)commId );

            /* create a message queue for RMS replies */
            engine->msgq = Comm_create(commName, &engine->fromRMS, NULL);
            Memory_free( commName, commNameLength, NULL );
        }
        else {
            /* Don't care about the name */
            engine->msgq = Comm_create(NULL, &engine->fromRMS, NULL);
        }

        if (engine->msgq == NULL) {
            *ec = Engine_ENOCOMM;
            goto fail;
        }

        /* allocate message to exchange with RMS */
        status = Comm_alloc(engine->rmsPoolId,
            (Comm_Msg *)&engine->rmsMsg, sizeof (RMS_RmsMsg));
        if (status != Comm_EOK) {
            *ec = Engine_ECOMALLOC;
            goto fail;
        }

        /* locate RMS's message queue */
        status = Comm_locate(RMS_CMDQNAME, &engine->toRMS);
        if (status != Comm_EOK) {
            *ec = Engine_ENOSERVER;
            goto fail;
        }

        /* check server compatibility key */
        if (checkServer(engine) != TRUE) {
            *ec = engine->lastError;
            goto fail;
        }
    }

    /* put opened engine on engineList */
    Queue_put(&engineList, &engine->link);
    *ec = Engine_EOK;

    /* if started up server optionally set the DSP trace mask */
    if (startedServer == TRUE) {
        traceMask = Global_getenv("CE_DSP0TRACE");

        /*
         *  If we're using LAD, we need to get the trace token.
         */
        if (((traceMask != NULL) || Engine_alwaysCollectDspTrace) &&
                Global_useLinkArbiter) {
            /*
             *  Don't do anything if this fails, since another process may
             *  already own the trace token.
             */
            Server_connectTrace((Server_Handle)engine, &traceToken);
        }

        if (Engine_alwaysCollectDspTrace) {
            GT_2trace(curTrace, GT_ENTER,
                "rmsInit> RMS initialized(0x%lx); CE_DEBUG on, "
                "setting DSP trace mask to %s\n",
                engine, Engine_ceDebugDspTraceMask);
            Engine_setTrace(engine, Engine_ceDebugDspTraceMask);
        }
        if (traceMask != NULL) {
            GT_2trace(curTrace, GT_ENTER,
                "rmsInit(0x%lx), setting DSP trace mask to %s\n", engine,
                traceMask);
            Engine_setTrace(engine, traceMask);
        }
    }

    return (engine);

fail:
    Engine_close(engine);
    return (NULL);
}

/*
 *  ======== rserverClose ========
 */
static Void rserverClose(RServer server)
{
    Lock_acquire(serverLock);
    GT_2trace(curTrace, GT_ENTER, "rserverClose(0x%lx), count = %d\n",
        server, server->refCount);

    /* decrement reference count */
    if (server->refCount-- == 1) {
        /* if no more references exist, turn off the DSP */
        Processor_delete(server->dspProc);
    }

    GT_1trace(curTrace, GT_ENTER, "rserverClose(0x%lx) done.\n", server);
    Lock_release(serverLock);
}

/*
 *  ======== rserverOpen ========
 */
static RServer rserverOpen(Engine_Desc * desc, Bool * startedServer)
{
    RServer server = &serverTab[0];

    Lock_acquire(serverLock);
    GT_2trace(curTrace, GT_ENTER, "rserverOpen('%s'), count = %d\n",
        desc->remoteName, server->refCount);

    if (server->refCount == 0) {
        /* if no references exist, load the DSP */
        String argv[3] = {NULL, NULL, NULL};
        Processor_Attrs attrs = Processor_ATTRS;

        attrs.argv = argv;
        attrs.argv[0] = desc->remoteName;
        attrs.argc = 1;

        if ((server->dspProc = Processor_create(desc->remoteName,
            desc->linkCfg, &attrs)) != NULL) {
            server->imageName = desc->remoteName;
            *startedServer = TRUE;
        }
        else {
            /* failed to "create" the server, return NULL */
            GT_1trace(curTrace, GT_6CLASS,
                "rserverOpen: can't start '%s'; Processor_create failed\n",
                desc->remoteName);
            server = NULL;
        }
    }
    else {
        if (strcmp(server->imageName, desc->remoteName) != 0) {
            GT_2trace(curTrace, GT_6CLASS,
                "rserverOpen: can't start '%s'; '%s' already running\n",
                desc->remoteName, server->imageName);
            server = NULL;
        }
    }

    if (server != NULL) {
        server->refCount++;
    }

    GT_2trace(curTrace, GT_ENTER, "rserverOpen('%s'): 0x%lx done.\n",
        desc->remoteName, server);
    Lock_release(serverLock);

    return (server);
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,432; 12-2-2010 21:19:07; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

