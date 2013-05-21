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
 *  ======== visa.c ========
 *  SPI used by alg stubs to communicate with corresponding skeletons
 *
 *  Benchmark trace support:
 *                                  Trace Event
 *          App CPU                  (Arm:DSP)    DSP CPU
 *          -------                   -------     -------
 *      client calls alg API fxn:
 *          msg = VISA_allocMsg()       1:
 *          marshal args into msg
 *          VISA_call(msg)              2:     --> NODE_receive()
 *                                       :3        call skeleton
 *                                                     unmarshall args
 *                                                     call alg API
 *                                       :4                VISA_enter()
 *                                                         call local alg fxn
 *                                       :5                VISA_exit();
 *                                                     marshall results
 *                                      7:6    <-- NODE_reply()
 *          retrieve command status
 *          VISA_freeMsg(msg)           8:
 *          return to client
 *
 *  Trace Events:
 *      1 - VISA_allocMsg: generated at the beginning of each remote
 *              call; contains a message id (messageId)
 *      2 - VISA_call enter: contains visa handle, messageId, and command id
 *      3 - NODE call start: contains messageId, DSP visa handle (algHandle)
 *      4 - VISA_enter: contains algHandle
 *      5 - VISA_exit: contains algHandle
 *      6 - NODE call end: contains algHandle and messageId
 *      7 - VISA_call exit: contains messageId, and command id, and exit status
 *      8 - VISA_freeMsg: generated just prior to returning to client of
 *              a remote call; contains messageId
 *
 *  Events 1, 2, 7, and 8 are in the Arm-side trace log.  Events 3, 4, 5,
 *  and 6 are in the DSP-side trace log.
 */
#include <xdc/std.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/ipc/Comm.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/utils/trace/gt.h>

#include <ti/sdo/ce/alg/Algorithm.h>
#include <ti/sdo/ce/osal/Thread.h>
#include <ti/sdo/ce/osal/Log.h>

#include "visa.h"

#define GTNAME "CV"

#define FIELD_SEP ':'    /* Separates codec name and params, eg, "mp4:6:0" */
#define MAXNAMELEN 127   /* Max length of codec name (should be the same as
                          *  in rms.c)
                          */

static GT_Mask curTrace = {NULL,NULL};

/*
 *  ======== VISA_Obj ========
 */
typedef struct VISA_Obj {
    IALG_Fxns       *fxns;          /* this must be first */
    Ptr             algHandle;      /* local ALG_Handle or VISA_Handle */
    Engine_Node     node;           /* remote node */
    VISA_Msg        *cmd;           /* remote node messages */
    Int             cmdAllocIndex;
    Int             cmdFreeIndex;
    Int             nCmds;
    Int             maxMsgSize;     /* for remote algs, max size of msg */
    Bool            isLocal;        /* does this need remote services? */
    UInt32          remoteVisa;     /* if remote, the remote VISA handle */
    UInt32          context;        /* optional context */
    String          name;           /* name passed to VISA_create() */
    Ptr             codecClassConfig; /* stub/skeleton config data, if any */
} VISA_Obj;


/*
 *  ======== VISA_allocMsg ========
 */
VISA_Msg VISA_allocMsg(VISA_Handle visa)
{
    Int i;
    VISA_Msg msg;

    i = visa->cmdAllocIndex;
    msg = visa->cmd[i];

    if (msg != NULL) {
        visa->cmdAllocIndex++;
        if (visa->cmdAllocIndex == visa->nCmds) {
            visa->cmdAllocIndex = 0;
        }
        visa->cmd[i] = NULL;

        /* increment the sequence number */
        ++msg->header.header.msgId;

        /* embed a 16-bit sequence number into ID of message */
        msg->header.cmd.arg1 = (msg->header.cmd.arg1 & 0xffff0000) |
            (msg->header.header.msgId & 0xffff);

        GT_1trace(curTrace, GT_5CLASS, "VISA_allocMsg> "
            "Allocating message for messageId=0x%08x\n", msg->header.cmd.arg1);
    }
    else {
        GT_0trace(curTrace, GT_6CLASS,
                  "VISA_allocMsg> FAILED to allocate message.\n"
                  "Try increasing # messages for codec.\n");
    }

    return (msg);
}

/*
 *  ======== VISA_call ========
 *  Send command (specified in msg) to the algorithm instance, wait for
 *  a response from last completed command, return status from last
 *  completed command (in msg), and the response (msg).
 */
VISA_Status VISA_call(VISA_Handle visa, VISA_Msg *msg)
{
    VISA_Status status = VISA_ERUNTIME;

    GT_4trace(curTrace, GT_ENTER | GT_5CLASS, "VISA_call"
        "(visa=0x%x, msg=0x%x): messageId=0x%08x, command=0x%x\n",
        visa, *msg, (*msg)->header.cmd.arg1, (*msg)->cmd);

    /* call remote function and wait for results */
    if (Engine_call(visa->node, (Comm_Msg *)msg) == Comm_EOK) {
        status = (*msg)->status; /* if call completed, copy remote status */
    }

    GT_3trace(curTrace, GT_ENTER | GT_5CLASS, "VISA_call "
        "Completed: messageId=0x%08x, command=0x%x, return(status=%d)\n",
        (*msg)->header.cmd.arg1, (*msg)->cmd, status);

    return (status);
}

/*
 *  ======== VISA_callAsync ========
 *  Send command (specified in msg) to the algorithm instance, but don't
 *  wait for a response from last completed command.  Return status of
 *  command transmission.  (Should return value be the Int return from
 *  Engine_callAsync()?)
 */
VISA_Status VISA_callAsync(VISA_Handle visa, VISA_Msg *msg)
{
    VISA_Status retVal;
    Int status;

    GT_4trace(curTrace, GT_ENTER | GT_5CLASS, "VISA_callAsync"
        "(visa=0x%x, msg=0x%x): messageId=0x%08x, command=0x%x\n",
        visa, *msg, (*msg)->header.cmd.arg1, (*msg)->cmd);

    /* call remote function w/o waiting for results */
    status = Engine_callAsync(visa->node, (Comm_Msg *)msg);

    retVal = status == Comm_EOK ? VISA_EOK : VISA_ERUNTIME;

    GT_3trace(curTrace, GT_ENTER | GT_5CLASS, "VISA_callAsync "
        "Completed: messageId=0x%08x, command=0x%x, return(%d)\n",
        (*msg)->header.cmd.arg1, (*msg)->cmd, retVal);

    return (retVal);
}

/*
 *  ======== VISA_wait ========
 *  Wait for response from an async command that was submitted with
 *  VISA_callAsync(), returning status from last completed command (in msg),
 *  and the response (msg).
 */
VISA_Status VISA_wait(VISA_Handle visa, VISA_Msg *msg, UInt timeout)
{
    VISA_Status status;
    Int retVal;

    GT_2trace(curTrace, GT_ENTER | GT_5CLASS, "VISA_wait"
        "(visa=0x%x): timeout=0x%x\n", visa, timeout);

    /* wait for a result from remote function and return first one */
    retVal = Engine_callWait(visa->node, (Comm_Msg *)msg, timeout);
    switch (retVal) {
      case Comm_EOK:
        status = (*msg)->status; /* if call completed, copy remote status */
        break;

      case Comm_ETIMEOUT:
        status = VISA_ETIMEOUT;
        break;

      default:
        status = VISA_ERUNTIME;
        break;
    }

#if GT_TRACE == 1
    if (retVal == Comm_ETIMEOUT) {
        GT_1trace(curTrace, GT_2CLASS, "VISA_wait"
                  ": Engine_callWait() returned Comm_ETIMEOUT, "
                  "return(status=%d)\n", status);
    }
    else {
        if (*msg == NULL) {
            GT_1trace(curTrace, GT_ENTER | GT_5CLASS, "VISA_wait "
                "Completed: No message returned, return(status=%d)\n",
                status);
        }
        else {
            GT_3trace(curTrace, GT_ENTER | GT_5CLASS, "VISA_wait "
                "Completed: messageId=0x%08x, command=0x%x, "
                "return(status=%d)\n",
                (*msg)->header.cmd.arg1, (*msg)->cmd, status);
        }
    }
#endif

    return (status);
}

/*
 *  ======== VISA_create ========
 */
VISA_Handle VISA_create(Engine_Handle engine, String name,
    IALG_Params *params, size_t msgSize, String type)
{
    Int paramsSize;

    if (curTrace.modName == NULL) {   /* initialize GT (tracing) */
        GT_create(&curTrace, GTNAME);
    }

    GT_5trace(curTrace, GT_ENTER, "VISA_create(0x%x, '%s', 0x%x, 0x%d, '%s')\n",
        engine, name, params, msgSize, type);

    paramsSize = params ? params->size : 0;

    return (VISA_create2(engine, name, params, paramsSize, msgSize, type));
}

/*
 *  ======== VISA_create2 ========
 */
VISA_Handle VISA_create2(Engine_Handle engine, String name,
    IALG_Params *params, Int paramsSize, size_t msgSize, String type)
{
    VISA_Handle visa = NULL;
    Engine_AlgCreateAttrs createAttrs = Engine_ALGCREATEATTRS;
    Bool isLocal;
    IALG_Fxns *fxns;
    Ptr  idma3Fxns;
    Ptr  iresFxns;
    Engine_CachedMemType memType;
    Int  priority = -1;
    Bool useExtHeap = FALSE;
    Int  nMsgs = 1;
    Char tmpName[MAXNAMELEN + 1];
    Char *priStr = NULL;
    Char *heapStr = NULL;
    Char *nmsgStr = NULL;
    Char *strPtr;
    Char *constName = NULL;
    Ptr  codecClassConfig = NULL;
    Algorithm_Attrs attrs;
    Comm_Queue localQueue, remoteQueue;
    Int i;

    if (curTrace.modName == NULL) {   /* initialize GT (tracing) */
        GT_create(&curTrace, GTNAME);
    }

    GT_6trace(curTrace, GT_ENTER,
        "VISA_create2(0x%x, '%s', 0x%x, 0x%x, 0x%d, '%s')\n",
        engine, name, params, paramsSize, msgSize, type);

    /*
     *  Parse name to get any optional create parameters. eg, name
     *  may be "mp4", "mp4:10", "mp4::1", "mp4:10:1", "mp4:::3",
     *  or "mp4:10:1:3". The argument after the first ':' will be parsed
     *  as a priority that will be passed to RMS to override the
     *  configured priority. The value after the second ':' will be parsed
     *  as a flag, that if non-zero, will mean that all memory requests
     *  will be allocated from a single heap in external memory.  The value
     *  after the third ':' will be parsed as the number of VISA messages
     *  that will be allocated, and is useful when the "asynchronous" process
     *  method is used, i.e., VISA_callAsync()/VISA_wait().
     *  NOTE: We're not using strtok here because it is non-reentrant.
     */
    if (strlen(name) > MAXNAMELEN) {
        GT_3trace(curTrace, GT_6CLASS, "VISA_create2> Name of codec [%s] is "
                "too long: [%d] chars.\n Can be at most [%d] characters "
                "long.\n", name, strlen(name), MAXNAMELEN);
        goto fail;
    }

    strncpy(tmpName, name, MAXNAMELEN);
    tmpName[MAXNAMELEN] = '\0';

    strPtr = tmpName;
    while ((*strPtr != FIELD_SEP) && (*strPtr != '\0')) {
        strPtr++;
    }
    if (*strPtr == FIELD_SEP) {
        *strPtr++ = '\0';
        priStr = strPtr;
        while ((*strPtr != FIELD_SEP) && (*strPtr != '\0')) {
            strPtr++;
        }
        if (*strPtr == FIELD_SEP) {
            /* Null-terminate the "priority" string */
            *strPtr++ = '\0';

            /* Null-terminate the "useExtHeap" string */
            heapStr = strPtr;
            while ((*strPtr != FIELD_SEP) && (*strPtr != '\0')) {
                strPtr++;
            }
            if (*strPtr == FIELD_SEP) {
                *strPtr++ = '\0';

                /* Null-terminate the "nMsgs" string */
                nmsgStr = strPtr;
                while ((*strPtr != FIELD_SEP) && (*strPtr != '\0')) {
                    strPtr++;
                }
                *strPtr++ = '\0';

                if (*nmsgStr != '\0') {
                    nMsgs = atoi(nmsgStr);
                }
            }
            if (*heapStr != '\0') {
                useExtHeap = (atoi(heapStr) == 0) ? FALSE : TRUE;
            }
        }
        if (*priStr != '\0') {
            /* TODO: Only allow changing priority of remote codec? */
            priority = atoi(priStr);
            /* TODO: Check range of priority? */
        }
    }

    if ((heapStr != NULL) || (priStr != NULL) || (nmsgStr != NULL)) {
        GT_4trace(curTrace, GT_3CLASS, "VISA_create2> name: %s  priority: %d"
                " single heap: %d  # messages: %d\n",
                tmpName, priority, useExtHeap, nMsgs);
    }

    createAttrs.priority = priority;
    createAttrs.useExtHeap = useExtHeap;

    /*
     *  Get the configured name of the codec to pass to Engine_createNode.
     *  We also need the const name so LOG (and SoCrates) can display it.
     */
    constName = Engine_getConstName(engine, tmpName, type);
    if (constName == NULL) {
        GT_1trace(curTrace, GT_6CLASS,
                "VISA_create2> Unable to locate alg \"%s\".\n", name);
        goto fail;
    }

    /*
     *  Get codec-specific stub/skeleton configuration data, that the stub/skel
     *  can retrieve via VISA_getCodecClassConfig(). Can be NULL.
     */
    codecClassConfig = Engine_getCodecClassConfig(engine, tmpName, type);

    /* get IALG interface functions (of the right type) */
    if ((fxns = Engine_getFxns(engine, constName, type, &isLocal, &idma3Fxns,
        &iresFxns, &(attrs.groupId), &memType)) == NULL) {

        GT_0trace(curTrace, GT_6CLASS,
            "VISA_create2> FAILED to get IALG functions.\n"
            "Check Engine configuration and module name of codec class "
            "(type arg).\n");
        goto fail;
    }
    attrs.useExtHeap = useExtHeap;
    attrs.useCachedMem = (memType == Engine_USECACHEDMEM_DEFAULT) ?
        Algorithm_USECACHEDMEM_DEFAULT :
        (memType == Engine_USECACHEDMEM_CACHED) ?
        Algorithm_USECACHEDMEM_CACHED : Algorithm_USECACHEDMEM_NONCACHED;

    /* create the VISA object */
    visa = (VISA_Obj *)Memory_alloc(sizeof (VISA_Obj), NULL);
    if (visa != NULL) {
        visa->fxns = fxns;
        visa->isLocal = isLocal;
        visa->node = NULL;
        visa->cmd = NULL;
        visa->maxMsgSize = 0;
        visa->remoteVisa = 0;
        visa->codecClassConfig = codecClassConfig;

        /* We use the const name so LOG (and SoCrates) can display it. */
        visa->name = constName;

        /* create the underlying alg object */
        if (isLocal) {

            /* if it's local use Algorithm to construct alg object */
            visa->algHandle = Algorithm_create((IALG_Fxns *)visa->fxns,
                 idma3Fxns, iresFxns, params, &attrs);

            if (visa->algHandle == NULL) {
                GT_0trace(curTrace, GT_6CLASS,
                    "VISA_create2> FAILED to create local codec.\n");
                goto fail;
            }

            /*
             * Note, leave the prefix "VISA_create>" as GT_5CLASS trace
             * statements are seen by DVT, and changes may break them.
             */
            GT_2trace(curTrace, GT_5CLASS, "VISA_create> "
                "local codec created (name='%s', handle=0x%x)\n",
                constName, visa->algHandle);
        }
        else {
            /* if it is "remote", use the Engine to create remote instance */
            Int status;
            visa->algHandle = visa;

            /*
             * First, try to allocate the messages.  We'll need them if we
             * want to communicate with the Node we're about to create.  If
             * we don't have enough messages, we want to fail early - before
             * we try to create the node (which we won't be able to talk to
             * if we can't allocate any msgs!).
             */
            visa->cmd = (VISA_Msg *)Memory_alloc((nMsgs * sizeof(VISA_Msg)),
                    NULL);
            if (visa->cmd == NULL) {
                GT_0trace(curTrace, GT_6CLASS,
                        "VISA_create2> FAILED to allocate cmd array.\n");
                goto fail;
            }

            /* this is how many msgs are requested */
            visa->nCmds = nMsgs;

            /* initialize invalid */
            for (i = 0; i < nMsgs; i++) {
                visa->cmd[i] = NULL;
            }

            /* allocate msgs to send back and forth */
            for (i = 0; i < nMsgs; i++) {
                status = Comm_alloc(Engine_getMemId(engine),
                    (Comm_Msg *)&visa->cmd[i], msgSize);
                if (status != Comm_EOK) {
                    GT_1trace(curTrace, GT_6CLASS,
                        "VISA_create2> FAILED to allocate message #%d.\n", i);
                    goto fail;
                }
            }

            /*
             * Now that we have msgs to communicate with the node, let's
             * create the node.
             */
            visa->node = Engine_createNode2(engine, constName, msgSize, params,
                paramsSize, &createAttrs);
            if (visa->node == NULL) {
                GT_1trace(curTrace, GT_6CLASS,
                    "VISA_create2> FAILED to create remote codec (0x%x).\n",
                    Engine_getLastError(engine));
                goto fail;
            }
            visa->remoteVisa = Engine_getRemoteVisa(visa->node);

            /* Can't do this until after Engine_createNode2() */
            Engine_getNodeQueues(visa->node, &remoteQueue, &localQueue);

            /* initialize our alloc/free indexes */
            visa->cmdAllocIndex = 0;
            visa->cmdFreeIndex = 0;

            /* initialize each msg's 'arg1' uniquely for DVT */
            for (i = 0; i < nMsgs; i++) {
                visa->cmd[i]->header.cmd.arg1 = ((UInt32)remoteQueue << 16);
            }

            /* An assumption is made here that all msgs are the same size */
            visa->maxMsgSize = Comm_getMsgSize((Comm_Msg)visa->cmd[0]);

            /*
             * Note, leave the prefix "VISA_create>" as GT_5CLASS trace
             * statements are seen by DVT, and changes may break them.
             */
            GT_3trace(curTrace, GT_5CLASS, "VISA_create> "
                "remote codec created (name='%s', localQueueID=0x%x, "
                "remoteQueueID=0x%04x)\n", constName, localQueue, remoteQueue);
        }
    }

    return (visa);

fail:
    /* Either clean up visa->cmd Memory_alloc here or do so in VISA_delete */
    VISA_delete(visa);
    return (NULL);
}

/*
 *  ======== VISA_delete ========
 */
Void VISA_delete(VISA_Handle visa)
{
    Comm_Queue localQueue, remoteQueue;
    Int        status;
    Int        i;

    GT_1trace(curTrace, GT_ENTER, "VISA_delete(0x%x)\n", visa);

    if (visa != NULL) {

        Engine_getNodeQueues(visa->node, &remoteQueue, &localQueue);

        GT_2trace(curTrace, GT_5CLASS, "VISA_delete> "
            "deleting codec (localQueue=0x%x, remoteQueue=0x%x)\n",
            localQueue, remoteQueue);

        if (visa->isLocal && visa->algHandle) {
            GT_1trace(curTrace, GT_5CLASS, "VISA_delete> "
                    "deleting codec 0x%x\n", visa->algHandle);
            Algorithm_delete((Algorithm_Handle)visa->algHandle);
        }

        if (visa->node != NULL) {
            if (visa->cmd != NULL) {
                /* tell node that we want to exit and wait for ack */
                status = Engine_ctrlNode(visa->node,
                    (Comm_Msg *)&visa->cmd[0], Engine_CEXIT);
                if (status != Comm_EOK) {
                    GT_2trace(curTrace, GT_6CLASS,
                        "VISA_delete> Engine_ctrlNode failed: visa = 0x%x"
                        " status = 0x%x\n", visa, status);
                }
            }
            Engine_deleteNode(visa->node);
        }

        if (visa->cmd != NULL) {
            for (i = 0; i < visa->nCmds; i++) {
                if (visa->cmd[i]) {
                    Comm_free((Comm_Msg)visa->cmd[i]);
                }
            }
            Memory_free(visa->cmd, visa->nCmds * sizeof(VISA_Msg), NULL);
        }

        Memory_free(visa, sizeof (VISA_Obj), NULL);
    }
}

/*
 *  ======== VISA_enter ========
 */
Void VISA_enter(VISA_Handle visa)
{
    if (visa->isLocal && visa->algHandle) {
        GT_2trace(curTrace, GT_5CLASS, "VISA_enter"
            "(visa=0x%x): algHandle = 0x%x\n", visa, visa->algHandle);

        /*
         *  First log in sequence:
         *      thread handle, codec handle, index in sequence = 1
         */
        Log_printf(ti_sdo_ce_dvtLog,
            "ThreadID: 0x%x codec handle: 0x%x pre-activate",
            (Arg)Thread_self(), (Arg)visa, (Arg)1);
        Algorithm_activate((Algorithm_Handle)visa->algHandle);

        /*
         *  Second log in sequence:
         *      index in sequence = 2, codec handle, codec name
         *  Want the name in a string by itself in this case.
         */
        Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)visa->name, (Arg)visa, (Arg)2);
    }
}

/*
 *  ======== VISA_exit ========
 */
Void VISA_exit(VISA_Handle visa)
{
    if (visa->isLocal && visa->algHandle) {
        GT_2trace(curTrace, GT_5CLASS, "VISA_exit"
            "(visa=0x%x): algHandle = 0x%x\n", visa, visa->algHandle);

        /*
         *  Third log in sequence:
         *      index in sequence = 3, codec handle
         *  (Pass codec handle twice, since we want it as arg1).
         */
        Log_printf(ti_sdo_ce_dvtLog, "Codec handle: 0x%x pre-deactivate",
            (Arg)visa, (Arg)visa, (Arg)3);
        Algorithm_deactivate((Algorithm_Handle)visa->algHandle);

        /*
         *  Fourth log in sequence:
         *      index in sequence = 4, codec handle
         *  (Pass codec handle twice, since we want it as arg1).
         */
        Log_printf(ti_sdo_ce_dvtLog, "Codec handle: 0x%x post-deactivate",
            (Arg)visa, (Arg)visa, (Arg)4);
    }
}

/*
 *  ======== VISA_freeMsg ========
 */
Void VISA_freeMsg(VISA_Handle visa, VISA_Msg msg)
{
    assert(visa->cmd[visa->cmdFreeIndex] == NULL);

    GT_3trace(curTrace, GT_5CLASS, "VISA_freeMsg"
        "(0x%x, 0x%x): Freeing message with messageId=0x%08x\n",
        visa, msg, msg->header.cmd.arg1);

    if (!msg) {
        GT_0trace(curTrace, GT_6CLASS,
            "VISA_freeMsg> FAILED (NULL message).\n");
    }
    else {
        visa->cmd[visa->cmdFreeIndex++] = msg;
        if (visa->cmdFreeIndex == visa->nCmds) {
            visa->cmdFreeIndex = 0;
        }
    }
}

/*
 *  ======== VISA_getAlgFxns ========
 */
IALG_Fxns *VISA_getAlgFxns(VISA_Handle visa)
{
    return (visa->fxns);
}

/*
 *  ======== VISA_getAlgHandle ========
 *
 *  Note, this fxn returns the algorithm's handle (the one needed to pass
 *  to the IALG_Fxns returned by VISA_getAlgFxns).  If the alg is local,
 *  we need to return the IALG_Handle, since IALG_Fxns is an ialg.  If it's
 *  remote, we need to return the VISA handle, since the IALG_Fxns is a stub,
 *  which needs a VISA_Handle.
 */
Ptr VISA_getAlgHandle(VISA_Handle visa)
{
    if (visa->isLocal) {
        return (Algorithm_getAlgHandle(visa->algHandle));
    }
    else {
        return (visa->algHandle);
    }
}

/*
 *  ======== VISA_getAlgorithmHandle ========
 */
Ptr VISA_getAlgorithmHandle(VISA_Handle visa)
{
    return (visa->algHandle);
}

/*
 *  ======== VISA_getAlgMemRecs ========
 */
VISA_Status VISA_getAlgMemRecs(VISA_Handle visa, IALG_MemRec *memTab, Int size,
        Int *numRecs)
{
    VISA_Status  status = VISA_EOK;
    Engine_Error err = Engine_EOK;

    if (visa->isLocal) {
        *numRecs = Algorithm_getMemRecs(visa->algHandle, memTab, size);
    }
    else {
        err =  Engine_getAlgMemRecs(visa->node, memTab, size, numRecs);
    }

    if (err != Engine_EOK) {
        status = VISA_EFAIL;
    }

    return (status);
}

/*
 *  ======== VISA_getAlgNumRecs ========
 */
VISA_Status VISA_getAlgNumRecs(VISA_Handle visa, Int *numRecs)
{
    VISA_Status status = VISA_EOK;
    Engine_Error err = Engine_EOK;

    if (visa->isLocal) {
        *numRecs = Algorithm_getNumRecs(visa->algHandle);
    }
    else {
        err =  Engine_getAlgNumRecs(visa->node, numRecs);
    }

    if (err != Engine_EOK) {
        status = VISA_EFAIL;
    }

    return (status);
}

/*
 *  ======== VISA_getContext ========
 */
Void VISA_getContext(VISA_Handle visa, UInt32 * pContext)
{
    *pContext = visa->context;
}

/*
 *  ======== VISA_getMaxMsgSize ========
 */
UInt VISA_getMaxMsgSize(VISA_Handle visa)
{
    GT_2trace(curTrace, GT_4CLASS, "VISA_getMaxMsgSize"
            "(0x%x): returning 0x%x\n", visa, visa->maxMsgSize);
    return (visa->maxMsgSize);
}

/*
 *  ======== VISA_setContext ========
 */
Void VISA_setContext(VISA_Handle visa, UInt32 context)
{
    visa->context = context;
}

/*
 *  ======== VISA_getCodecClassConfig ========
 */
Ptr VISA_getCodecClassConfig(VISA_Handle visa)
{
    return (visa->codecClassConfig);
}

/*
 *  ======== VISA_isLocal ========
 */
Bool VISA_isLocal(VISA_Handle visa)
{
    return (visa->isLocal);
}

/*
 *  @(#) ti.sdo.ce; 1, 0, 6,432; 12-2-2010 21:19:09; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

