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
 *  ======== rms.c ========
 */
#include <xdc/std.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>

#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Thread.h>
#include <ti/sdo/ce/osal/Trace.h>
#include <ti/sdo/ce/ipc/Comm.h>

#include <ti/sdo/ce/rms.h>
#include <ti/sdo/utils/trace/CBuf.h>
#include <ti/sdo/utils/trace/gt.h>
#include <ti/sdo/ce/alg/Algorithm.h>
#include <ti/sdo/ce/node/node.h>
#include <ti/sdo/ce/node/_node.h>  /* RMS is a "friend" of NODE */

#include <ti/xdais/ialg.h>

#define MAXNUMLEN   8
#define MAXNUMSEGS  1024        /* Maximum number of heaps checked for */

/*
 *  Maximum length of codec name (Should be the same as in visa.c)
 */
#define MAXNAMELEN 127          /* Maximum length of codec name */

#define HEADERSIZE  ( \
    (Char *)&(((RMS_RmsMsg *)0)->cmdBuf) - (Char *)0  \
)

/* this function is for internal use only */
#define RMS_checkUuid(uuid1, uuid2) \
    ( (uuid1.data) == (uuid2.data) )

/* internal description of a created node instance */
typedef struct RMS_Obj {
    NODE_Handle     node;       /* NULL means free */
    NODE_Desc       *nodeDesc;  /* ptr to entry in node database */
    Comm_Queue      nodeQueue;  /* node's input message queue */
    Comm_Queue      gppQueue;   /* gpp's (client's) message queue */
    Int             instanceId; /* unique instance ID */
    String          name;       /* node's instance name */
} RMS_Obj;


static Int           initCount = 0;

static Comm_Queue    rmsMsgQueue = Comm_INVALIDMSGQ;
static Comm_Handle   rmsMsgHandle = NULL;
static RMS_RmsMsg    *rmsMsg = NULL;
static Thread_Handle rmsTsk = NULL;
static GT_Mask curTrace;
static Bool traceTokenAvailable = TRUE;

/* default RMS configuration data set */
RMS_Config RMS_CONFIG = RMS_CONFIGDEFAULT;

Void RMS_run(Void); /* RMS task entry function prototype */

static Void RMS_exec(Void);
static Char *formatNum(Char *ptr, UInt32 un);
static Void freeInst(RMS_Obj *inst);
static RMS_Status getAlg(RMS_CmdSetGetAlgIn *cmdIn,
        RMS_CmdSetGetAlgOut *cmdOut);
static RMS_Status getMemRecs(RMS_CmdSetGetMemRecsIn *cmdIn,
        RMS_CmdSetGetMemRecsOut *cmdOut);
static RMS_Status getNumAlgs(RMS_CmdSetGetNumAlgsOut *cmdOut);
static RMS_Status getNumRecs(RMS_CmdSetGetNumRecsIn *cmdIn,
        RMS_CmdSetGetNumRecsOut *cmdOut);
static RMS_Status getSegStat(Int segId, RMS_CmdSetGetSegStatOut *out);
static RMS_Obj *mkInst(String nodeName, Int id);

static RMS_Status processRmsCmd(RMS_CmdBuf *cmdBuf, Int size);
static RMS_Status redefineHeap(String name, Int segId, Uint32 base,
        Uint32 size);
static RMS_Status restoreHeap(String name);

/*
 *  ======== RMS_init ========
 *  Calls to RMS_init() must be serialized.
 */
Void RMS_init(Void)
{
    if (initCount++ == 0) {
        Thread_Attrs rmsTskAttrs;
        Comm_Attrs commAttrs;

        NODE_init();
        Thread_init();
        Comm_init();

        GT_create(&curTrace, "CR");

        /* HACK: we set callFxn in advance in case we run with an
         * OSAL that does not support separate Thread threads
         */
        commAttrs = Comm_ATTRS;
        commAttrs.callFxn = (Comm_CallFxn)RMS_exec;

        /* create RMS's MSGQ for msg exchange with host */
        rmsMsgHandle = Comm_create(RMS_CMDQNAME, &rmsMsgQueue, &commAttrs);
        assert(rmsMsgHandle != NULL);

        /* now, create the RMS task that acts on the server's behalf */
        rmsTskAttrs = Thread_ATTRS;
        rmsTskAttrs.priority  = RMS_config.tskPriority;
        rmsTskAttrs.stacksize = RMS_config.tskStacksize;
        rmsTskAttrs.stackseg  = RMS_config.tskStackseg;
        rmsTskAttrs.name      = "RMS";
        rmsTsk = Thread_create((Fxn)RMS_run, &rmsTskAttrs);
        assert(rmsTsk != NULL);
    }
}

/*
 *  ======== RMS_exit ========
 */
Void RMS_exit(Void)
{
    if (initCount-- <= 1) {
        initCount = 0;

        /* wait for rms thread to terminate */
        if (rmsTsk != NULL) {
//            Thread_join(rmsTsk);
        }

        if (rmsMsgHandle != NULL) {
            Comm_delete(rmsMsgHandle);
            rmsMsgHandle = NULL;
        }
        rmsMsgQueue = Comm_INVALIDMSGQ;

        if (rmsTsk != NULL) {
            Thread_delete(rmsTsk);
            rmsTsk = NULL;
        }

        traceTokenAvailable = TRUE;
    }
}

/*
 *  ======== RMS_run ========
 */
Void RMS_run(Void)
{
    for (;;) {
        RMS_exec();
    }
}

/*
 *  ======== RMS_exec ========
 */
static Void RMS_exec(Void)
{
    RMS_CmdBuf  *cmdBuf;
    Int         commStatus;
    Comm_Queue  sendersMsgQueue;
    RMS_Status  status;

    /* get something to do */
    commStatus = Comm_get(rmsMsgQueue, (Comm_Msg *)&rmsMsg, Comm_FOREVER);
    if (commStatus == Comm_EOK) {
        Int msgSize = Comm_getMsgSize((Comm_Msg)rmsMsg);

        /* we assume message recieved is at least as large as we require */
        assert(msgSize >= sizeof (RMS_RmsMsg));

        /* do it */
        cmdBuf = (RMS_CmdBuf *)&(rmsMsg->cmdBuf);
        status = processRmsCmd(cmdBuf, msgSize - HEADERSIZE);
        cmdBuf->status = status;

        /* find out who the sender was */
        commStatus = Comm_getSrcQueue((Comm_Msg)rmsMsg, &sendersMsgQueue);
        assert(commStatus == Comm_EOK);

        /* then send the message back */
        commStatus = Comm_put(sendersMsgQueue, (Comm_Msg)rmsMsg);
        assert(commStatus == Comm_EOK);
    }
    else {
#if 0
        /* In some cases (like shutdown) this is expected */
        GT_1trace(curTrace, GT_7CLASS, "RMS_exec> Comm_get failed (0x%x)\n",
            commStatus);
#endif
    }
}

/*
 *  ======== checkStack ========
 */
static Void checkStack(Void)
{
    Thread_Stat buf;

    if (Thread_stat(Thread_self(), &buf) == 0) {
        UInt8 classId = GT_5CLASS;
        Int headroom = 100;

        /* check stack size to see if we are close to overrun */
        if (buf.stacksize != 0) {
            headroom = (buf.stacksize > buf.stackused)
                ? ((buf.stacksize - buf.stackused) * 100) / buf.stacksize : 0;
        }

        if (headroom < 10) {
            classId |= GT_6CLASS; /* less than 10%, generate warning */
        }
        GT_3trace(curTrace, classId,
            "RMS: stack size = %d, stack used = %d(%d%%)\n",
            buf.stacksize, buf.stackused, 100 - headroom);
    }
}

/*
 *  ======== createNode ========
 */
static RMS_Status createNode(RMS_CmdSetCreateNodeIn  *cmdIn,
                              RMS_CmdSetCreateNodeOut *cmdOut)
{
    RMS_Obj     *rmsInst;
    NODE_Desc   *nodeDesc;
    NODE_Desc   desc;
    NODE_Attrs  nodeAttrs;
    NODE_Handle node;
    Int         priority;
    RMS_Status  status;
    Char        tmpName[MAXNAMELEN + 1];
    String      createArgBuf;
    Int         createArgLen;

    /* instance ID -- unique across all instances */
    static Int          instanceId = 0;

    /* search the database of nodes for the given uuid       */
    for (nodeDesc = RMS_nodeTab; nodeDesc->name != NULL; nodeDesc++) {
        if (RMS_checkUuid(cmdIn->uuid, nodeDesc->uuid)) {
            break;  /* found it */
        }
    }
    if (nodeDesc->name == NULL) {
        return (RMS_EINVUUID);
    }
    if (nodeDesc->rpcProtocolVersion != cmdIn->rpcProtocolVersion) {
        return (RMS_EINVPROT);
    }

    /* create an RMS node instance */
    rmsInst = mkInst(nodeDesc->name, instanceId);
    if (rmsInst == NULL) {
        return (RMS_ERESOURCE);
    }

    /* point to the args buffer of the in structure */
    createArgLen = cmdIn->argLength;
    if (createArgLen > 0) {
        createArgBuf = (String)(cmdIn->argBuffer);
    }
    else {
        createArgBuf = NULL;
    }

    /* Initilize desc with configured values. */
    desc = *nodeDesc;
    nodeAttrs = *(nodeDesc->nodeAttrs);
    desc.nodeAttrs = &nodeAttrs;

    /*
     *  If create parameters have priority set to -1, use configured priority,
     *  otherwise override the configured priority with the value passed in
     *  the create args.
     */
    priority = (Int)(cmdIn->nodePriority);
    if (priority != -1) {
        if ((priority < Thread_MINPRI) || (priority > Thread_MAXPRI)) {
            return (RMS_EINVAL);
        }
        nodeAttrs.initPriority = priority;
    }

    /*
     *  Create new name combining nodeDesc->name and ::1 if cmdIn->useExtHeap
     *  is TRUE. We need to do this because NODE_create() calls the codec's
     *  create function (which only takes its own attributes arg).
     */
    if (cmdIn->useExtHeap) {
        desc.name = tmpName;
        strncpy(tmpName, nodeDesc->name, MAXNAMELEN - strlen("::1"));
        tmpName[MAXNAMELEN - strlen("::1")] = '\0';

        strcpy(tmpName + strlen(tmpName), "::1");
        tmpName[MAXNAMELEN] = '\0';
    }

    status = NODE_create(
        &desc,                          /* in: */
        createArgLen,                   /* in: */
        createArgBuf,                   /* in: */
        (Comm_Queue)cmdIn->gppQueue,    /* in:  sendQueue (to gpp msgq) */
        rmsInst->name,                  /* in:  node instance name */
        &node                           /* out: node handle */
    );
    if (status != NODE_EOK) {
        freeInst(rmsInst);
        status = (status == NODE_EOUTOFMEMORY) ? RMS_EOUTOFMEMORY :
            (status == NODE_ETASK) ? RMS_ETASK : RMS_EFAIL;
        return (status);
    }

    /* record the node instance data */
    rmsInst->node       = node;
    rmsInst->nodeDesc   = nodeDesc;
    rmsInst->nodeQueue  = NODE_getRecvQueue(node);
    rmsInst->gppQueue   = (Comm_Queue)cmdIn->gppQueue;
    rmsInst->instanceId = instanceId;
    instanceId++;

    /* prepare command output  */
    cmdOut->node       = (RMS_Word)rmsInst;
    cmdOut->nodeQueue  = rmsInst->nodeQueue;
    cmdOut->remoteVisa = (RMS_Word)NODE_getEnv(node);

    return (RMS_EOK);
}

/*
 *  ======== deleteNode ========
 */
static RMS_Status deleteNode(RMS_CmdSetDeleteNodeIn *cmdIn, RMS_CmdSetDeleteNodeOut *cmdOut)
{
    RMS_Obj     *rmsInst = (RMS_Obj *)cmdIn->node;
    RMS_Status  status = RMS_EOK;
    NODE_Stat   buf;

    /* get current stack info before deleting node */
    if (NODE_stat(rmsInst->node, &buf) == 0) {
        cmdOut->stackSize = buf.stackSize;
        cmdOut->stackUsed = buf.stackUsed;
    }
    else {
        cmdOut->stackSize = 0;
        cmdOut->stackUsed = 0;
    }

    /* delete the node object itself */
    if (NODE_delete(rmsInst->node) != NODE_EOK) {
        status = RMS_EFAIL;
    }

    freeInst(rmsInst);

    return (status);
}

/*
 *  ======== startNode ========
 */
static RMS_Status startNode(RMS_CmdSetExecuteNodeIn *cmdIn)
{
    RMS_Obj     *rmsInst = (RMS_Obj *)cmdIn->node;
    RMS_Status  status = RMS_EOK;

    if (NODE_start(rmsInst->node) != NODE_EOK) {
        status = RMS_EFAIL;
    }

    return (status);
}

/*
 *  ======== formatNum ========
 */
static Char *formatNum(Char *ptr, UInt32 un)
{
    Int i = 0;
    UInt32 n = un;
    static const Char digtohex[] = "0123456789abcdef";

    /* compute digits in number from right to left */
    do {
        *(--ptr) = digtohex[n & 0xf];
        n = n >> 4;
        ++i;
    } while (n);

    return (ptr);
}

/*
 *  ======== freeInst ========
 */
static Void freeInst(RMS_Obj *inst)
{
    if (inst->name != NULL) {
        Memory_free(inst->name, strlen(inst->name) + 1, NULL);
    }
    Memory_free(inst, sizeof (RMS_Obj), NULL);
}

/*
 *  ======== getAlg ========
 */
static RMS_Status getAlg(RMS_CmdSetGetAlgIn *cmdIn,
        RMS_CmdSetGetAlgOut *cmdOut)
{
    NODE_Desc *desc;
    Int        len;
    Int        index = (Int)cmdIn->index;

    desc = RMS_nodeTab + index;

    /* Copy alg name */
    len = strlen(desc->name);
    if (len >= RMS_MAXSTRLEN) {
        /* Name is too big to copy */
        GT_1trace(curTrace, GT_7CLASS, "RMS getAlg> Length of alg name [%d] "
                "is too big to copy!\n", len);
        return (RMS_EFAIL);
    }
    strncpy((Char *)cmdOut->name, desc->name, RMS_MAXSTRLEN);

    /* Copy stub functions name */
    len = strlen(desc->stubFxnsName);
    if (len >= RMS_MAXSTRLEN) {
        /* Name is too big to copy */
        GT_1trace(curTrace, GT_7CLASS, "RMS getAlg> Length of alg's stub "
                "functions name [%d] is too big to copy!\n", len);
        return (RMS_EFAIL);
    }
    strncpy((Char *)cmdOut->stubFxns, desc->stubFxnsName, RMS_MAXSTRLEN);

    /* Copy the typetab string */
    len = strlen(desc->typeTab);
    if (len >= RMS_MAXSTRLEN) {
        /* Name is too big to copy */
        GT_1trace(curTrace, GT_7CLASS, "RMS getAlg> Length of alg's typeTab "
                "string [%d] is too big to copy!\n", len);
        return (RMS_EFAIL);
    }
    strncpy((Char *)cmdOut->typeTab, desc->typeTab, RMS_MAXSTRLEN);

    /* Copy the rest of the stuff */
    cmdOut->uuid = desc->uuid;
    cmdOut->rpcProtocolVersion = desc->rpcProtocolVersion;

    return (RMS_EOK);
}


/*
 *  ======== getMemStat ========
 */
static RMS_Status getMemStat(RMS_CmdSetGetMemStatOut *out)
{
    Int i;
    Memory_Stat statBuf;
    UInt32 total = 0;

    for (i = 0; i < MAXNUMSEGS; i++) {
        if (Memory_segStat(i, &statBuf) != TRUE) {
            break;
        }
        total += statBuf.used;
    }

    if (i == MAXNUMSEGS) {
        /* Memory may be corrupted, print warning */
        GT_1trace(curTrace, GT_6CLASS,
                "RMS> getMemStat() finding > %d heaps!!!\n", MAXNUMSEGS);
    }
    out->used = total;

    checkStack();

    return (RMS_EOK);
}

/*
 *  ======== getMemRecs ========
 */
static RMS_Status getMemRecs(RMS_CmdSetGetMemRecsIn *cmdIn,
        RMS_CmdSetGetMemRecsOut *cmdOut)
{
    RMS_Obj         *rmsInst = (RMS_Obj *)cmdIn->node;
    Algorithm_Handle alg;
    VISA_Handle      visa;
    Int              maxRecs = cmdIn->numRecs;
    IALG_MemRec     *memTab = (IALG_MemRec *)(cmdOut->memRecs);
    RMS_Status       status = RMS_EOK;

    visa = (VISA_Handle)NODE_getEnv(rmsInst->node);
    alg = (Algorithm_Handle)VISA_getAlgorithmHandle(visa);

    cmdOut->numRecs = Algorithm_getMemRecs(alg, memTab, maxRecs);

    return (status);
}

/*
 *  ======== getNumAlgs ========
 */
static RMS_Status getNumAlgs(RMS_CmdSetGetNumAlgsOut *cmdOut)
{
    NODE_Desc   *desc;
    Int          numAlgs = 0;

    /* Count the number of nodes in the database */
    for (desc = RMS_nodeTab; desc->name != NULL; desc++, numAlgs++) {
    }

    cmdOut->numAlgs = numAlgs;
    return (RMS_EOK);
}

/*
 *  ======== getNumRecs ========
 */
static RMS_Status getNumRecs(RMS_CmdSetGetNumRecsIn *cmdIn,
        RMS_CmdSetGetNumRecsOut *cmdOut)
{
    RMS_Obj         *rmsInst = (RMS_Obj *)cmdIn->node;
    Algorithm_Handle alg;
    VISA_Handle      visa;
    RMS_Status       status = RMS_EOK;

    visa = (VISA_Handle)NODE_getEnv(rmsInst->node);
    alg = (Algorithm_Handle)VISA_getAlgorithmHandle(visa);

    cmdOut->numRecs = Algorithm_getNumRecs(alg);

    return (status);
}

/*
 *  ======== getSegStat ========
 */
static RMS_Status getSegStat(Int segId, RMS_CmdSetGetSegStatOut *out)
{
    Memory_Stat statBuf;

    if (Memory_segStat(segId, &statBuf) != TRUE) {
        /* segId is out of range */
        GT_1trace(curTrace, GT_6CLASS,
                "RMS> getSegStat() segment [%d] not found\n", segId);
        return (RMS_ENOTFOUND);
    }
    else {
        /* Copy to out */
        out->base = statBuf.base;
        out->size = statBuf.size;
        out->used = statBuf.used;
        out->maxBlockLen = statBuf.length;

        /* Copy memory segment name */
        strncpy((Char *)out->name, statBuf.name, RMS_MAXSEGNAMELENGTH);
        ((Char *)(out->name))[RMS_MAXSEGNAMELENGTH] = '\0';
    }

    return (RMS_EOK);
}

/*
 *  ======== getCpuStat ========
 */
static RMS_Status getCpuStat(RMS_CmdSetGetCpuStatOut *out)
{
    out->cpuLoad = Global_getCpuLoad();
    return (RMS_EOK);
}

/*
 *  ======== getTrace ========
 */
static RMS_Status getTrace(RMS_CmdSetGetTraceOut *out, Int size)
{
    CBuf_Handle traceBuf = Trace_getTrace();

    if (traceBuf != NULL) {
        size_t avail;

        /* must call CBuf_lost() *before* CBuf_get() */
        out->lost = CBuf_lost(traceBuf);
        out->max = CBuf_getSize(traceBuf);
        out->size = CBuf_get(traceBuf, (Char *)out->buf, size, &avail);

        out->avail = avail;
        return (RMS_EOK);
    }

    out->size = 0;
    return (RMS_EFAIL);
}

/*
 *  ======== setTraceMask ========
 */
static RMS_Status setTraceMask(RMS_CmdSetSetTraceMaskIn *in)
{
    String mask = (String)in->traceMask;

    mask[RMS_MAXTRACEMASKSIZE + 1] = '\0';

    GT_1trace(curTrace, GT_ENTER, "setting trace mask to %s\n", mask);

    GT_set(mask);

    Global_setSpecialTrace(mask);

    return (RMS_EOK);
}

/*
 *  ======== getVers ========
 */
static RMS_Status getVers(RMS_CmdSetGetVersOut *out)
{
    extern String ti_sdo_ce__versionString;

    if (ti_sdo_ce__versionString != NULL) {
        /* The CE version */
        strncpy((Char *)out->vers, ti_sdo_ce__versionString,
            RMS_READBUFSIZE - 1);
        ((Char *)out->vers)[RMS_READBUFSIZE - 1] = '\0';

        /* The RMS Protocol version */
        out->rpcMajor = RMS_VERSION_MAJOR;
        out->rpcSource = RMS_VERSION_SOURCE;
        out->rpcMinor = RMS_VERSION_MINOR;

        return (RMS_EOK);
    }

    return (RMS_EFAIL);
}

/*
 *  ======== mkInst ========
 */
static RMS_Obj *mkInst(String nodeName, Int id)
{
    Char idBuf[MAXNUMLEN + 1];  /* +1 for terminating '\0' */
    String idString;
    Int len;
    RMS_Obj *inst;

    inst = Memory_alloc(sizeof (RMS_Obj), NULL);
    if (inst == NULL) {
        return (NULL);
    }

    idBuf[MAXNUMLEN] = '\0';
    idString = formatNum(idBuf + MAXNUMLEN, id);

    len = strlen(nodeName) + strlen(idString) + 2;  /* +2 for '\0' and '#' */
    inst->name = (String)Memory_alloc(len, NULL);
    if (inst->name == NULL) {
        freeInst(inst);
        return (NULL);
    }

    strcpy(inst->name, nodeName);
    strcat(inst->name, "#");
    strcat(inst->name, idString);

    return (inst);
}

/*
 *  ======== processRmsCmd ========
 */
static RMS_Status processRmsCmd(RMS_CmdBuf *cmdBuf, Int cmdBufSize)
{
    GT_3trace(curTrace, GT_ENTER, "processRmsCmd(0x%x, %d): cmd = %d\n",
        cmdBuf, cmdBufSize, cmdBuf->cmd);

    switch (cmdBuf->cmd) {
        case RMS_CREATENODE:
            return createNode(&cmdBuf->data.createNodeIn,
                               &cmdBuf->data.createNodeOut);
        case RMS_STARTNODE:
            return startNode(&cmdBuf->data.startNodeIn);

        case RMS_DELETENODE:
            return deleteNode(&cmdBuf->data.deleteNodeIn,
                &cmdBuf->data.deleteNodeOut);

        case RMS_GETMEMSTAT:
            return getMemStat(&cmdBuf->data.getMemStatOut);

        case RMS_GETNUMSEGS:
            cmdBuf->data.getNumSegsOut.numSegs = Memory_getNumHeaps();
            return (RMS_EOK);

        case RMS_GETSEGSTAT:
            return getSegStat((Int)(cmdBuf->data.getSegStatIn.segId),
                    &cmdBuf->data.getSegStatOut);

        case RMS_GETCPUSTAT:
            return getCpuStat(&cmdBuf->data.getCpuStatOut);

        case RMS_GETTRACE: {
            Int traceSize = cmdBufSize - (
                (Char *)cmdBuf->data.getTraceOut.buf - (Char *)cmdBuf
            );
            GT_2trace(curTrace, GT_ENTER,
                "remote time = 0x%x, trace buffer size = %d\n",
                cmdBuf->data.getTraceIn.curTime, traceSize);
            return getTrace(&cmdBuf->data.getTraceOut, traceSize);
        }

        case RMS_SETTRACEMASK:
            return setTraceMask(&cmdBuf->data.setTraceMaskIn);

        case RMS_GETVERS:
            return getVers(&cmdBuf->data.getVersOut);

        case RMS_REDEFINEHEAP:
            return redefineHeap((String)(cmdBuf->data.redefineHeapIn.name),
                    -1, /* Redefine heap by name, not segid */
                    cmdBuf->data.redefineHeapIn.base,
                    cmdBuf->data.redefineHeapIn.size);

        case RMS_RELTRACETOKEN:
            traceTokenAvailable = TRUE;
            return (RMS_EOK);

        case RMS_REQTRACETOKEN:
            if (traceTokenAvailable == TRUE) {
                traceTokenAvailable = FALSE;
                return (RMS_EOK);
            }
            else {
                return (RMS_ERESOURCE);
            }

        case RMS_RESTOREHEAP:
            return restoreHeap((String)(cmdBuf->data.redefineHeapIn.name));

        case RMS_WRITEWORD:
            *(Int *)(cmdBuf->data.writeWordIn.addr) =
                (Int)cmdBuf->data.writeWordIn.value;
            return (RMS_EOK);

        case RMS_GETNUMMEMRECS:
            return getNumRecs(&cmdBuf->data.getNumRecsIn,
                               &cmdBuf->data.getNumRecsOut);

        case RMS_GETMEMRECS:
            return getMemRecs(&cmdBuf->data.getMemRecsIn,
                               &cmdBuf->data.getMemRecsOut);
        case RMS_GETALG:
            return (getAlg(&cmdBuf->data.getAlgIn, &cmdBuf->data.getAlgOut));

        case RMS_GETNUMALGS:
            return (getNumAlgs(&cmdBuf->data.getNumAlgsOut));

        default:
            return (RMS_EFAIL);
    }
}

/*
 *  ======== redefineHeap ========
 *  Redefine the heap defined by either name (if not NULL), or by segId
 *  (if name is NULL).
 */
static RMS_Status redefineHeap(String name, Int segId, UInt32 base,
        UInt32 size)
{
    Memory_Stat stat;
    Uint32      end = base + size - 1;
    Int         i;

    if (name != NULL) {
        if ((segId = Memory_getHeapId(name)) < 0) {
            GT_1trace(curTrace, GT_6CLASS,
                    "RMS> redefineHeap() heap %s found\n", name);
            return (RMS_ENOTFOUND);
        }
    }

    GT_assert(curTrace, Memory_segStat(segId, &stat));

    /*
     *  Check for memory overlap with another heap, if size > 0.
     *  (This check still does not guarentee that [base, base + size - 1]
     *  is a valid memory segment.)
     */
    if (size > 0) {
        for (i = 0; Memory_segStat(i, &stat); i++) {
            if (i == segId) {
                continue;
            }

            if (((stat.base <= base) && (base < stat.base + stat.size)) ||
                    ((base <= stat.base) && (stat.base <= end))) {
                /* Memory overlap */
                return (RMS_EINVAL);
            }
        }
    }

    if (!Memory_redefine(segId, base, size)) {
        /*
         *  Should not get here unless memory is in use, since we've
         *  already checked that segment exists.
         */
        return (RMS_EFREE);
    }

    return (RMS_EOK);
}

/*
 *  ======== restoreHeap ========
 */
static RMS_Status restoreHeap(String name)
{
    Int         segId;

    if ((segId = Memory_getHeapId(name)) < 0) {
        GT_1trace(curTrace, GT_6CLASS,
                "RMS> restoreHeap() heap %s not found\n", name);
        return (RMS_ENOTFOUND);
    }

    if (!Memory_restoreHeap(segId)) {
        /*
         *  Should not get here unless memory is in use, since we've
         *  already checked that segment exists.
         */
        return (RMS_EFREE);
    }
    
    return (RMS_EOK);
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,432; 12-2-2010 21:19:09; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

