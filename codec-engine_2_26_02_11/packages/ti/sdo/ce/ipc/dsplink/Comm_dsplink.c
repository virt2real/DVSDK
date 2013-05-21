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
 *  ======== Comm_dsplink.c ========
 */

#include <xdc/std.h>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/osal/Lock.h>
#include <ti/sdo/ce/osal/Global.h>

#include <ti/sdo/utils/trace/gt.h>

/*  ----------------------------------- DSP/BIOS Link                   */
#include <ti/sdo/ce/ipc/dsplink/_adapted_link_gpptypes.h>

#include <dsplink.h>
/*  ----------------------------------- DSP/BIOS LINK API               */
#include <proc.h>
#include <msgq.h>
#include <pool.h>

/* TODO: We don't have Thread_sleep(), so we'll do this instead */
#ifdef xdc_target__os_Linux
#include <unistd.h>
#else
#define sleep(x)
#endif

/* Number of seconds to sleep for in timeout error spin loop */
#define MAXSLEEP 10

extern SMAPOOL_Attrs Global_cePoolAttrs;
extern UInt32 ti_sdo_ce_ipc_dsplink_Ipc_maxTimeout;

static Void initCePoolAttrs();
static Void destroyCePoolAttrs();

/*
 *  ======== Comm_Obj ========
 */
typedef struct Comm_Obj {
    MsgqQueue  queue;
} Comm_Obj;

/*
 *  ======== Comm_ATTRS ========
 *  Default creation attrs
 */
Comm_Attrs Comm_ATTRS = {
    Comm_PEND
};

/* REMINDER: if you add an initialized static var, reinitialize it at cleanup */
static Int curInit = 0;                 /* module init counter */
static Lock_Handle moduleLock = NULL;
static GT_Mask curTrace;

/*
 *  ======== Comm_alloc ========
 */
Int Comm_alloc(UInt16 poolId, Comm_Msg *msg, UInt16 size)
{
    DSP_STATUS status;
    Int        retVal;

    GT_assert(curTrace, curInit > 0);
    GT_assert(curTrace, msg != NULL);

    GT_3trace(curTrace, GT_ENTER, "Comm_alloc> "
        "Enter(poolId=0x%x, msg=0x%x, size=%d)\n", poolId, msg, size);

    /* TODO:H temporary to make best-fit succeed; we allow only messages */
    /* smaller than the standard size */
    assert(size <= Global_cePoolAttrs.bufSizes[poolId]);
    if (size < Global_cePoolAttrs.bufSizes[poolId]) {
        size = Global_cePoolAttrs.bufSizes[poolId];
    }

    status = MSGQ_alloc(poolId, size, (MsgqMsg *)msg);

    retVal = (status == DSP_SOK ? Comm_EOK : Comm_EFAIL);

    GT_2trace(curTrace, GT_ENTER, "Comm_alloc> msg=0x%x, returning (%d)\n",
        *msg, retVal);

    return (retVal);
}


/*
 *  ======== Comm_create ========
 */
Comm_Handle Comm_create(String queueName, Comm_Queue *queue,
    Comm_Attrs *attrs)
{
    Comm_Obj *comm;
    DSP_STATUS status;

    GT_assert(curTrace, curInit > 0);

    GT_3trace(curTrace, GT_ENTER, "Comm_create> "
        "Enter(queueName='%s', queue=0x%x, attrs=0x%x)\n",
        queueName, queue, attrs);

    if (attrs == NULL) {
        attrs = &Comm_ATTRS;
    }

    /* we only support PEND type since Link MSGQ does not appear to have
     * default MsgqAttrs and we don't know what to set the pend function to
     */
    if (attrs->type != Comm_PEND) {
        GT_1trace(curTrace, GT_7CLASS, "Comm_create> Unsupported Comm_Attrs "
            "(0x%x)\n", attrs->type);
        return (NULL);
    }

    comm = (Comm_Obj *)Memory_alloc(sizeof(Comm_Obj), NULL);
    if (comm == NULL) {
        return (NULL);
    }

    if ((status = MSGQ_open(queueName, queue, NULL)) != DSP_SOK) {
        GT_2trace(curTrace, GT_6CLASS,
            "Comm_create('%s', ...) failed: status 0x%x\n",
            queueName, status);

        Memory_free(comm, sizeof(Comm_Obj), NULL);
        return (NULL);
    }
    comm->queue = *queue;

    GT_1trace(curTrace, GT_ENTER, "Comm_create> return (0x%x)\n", comm);

    return (comm);
}


/*
 *  ======== Comm_delete ========
 */
Void Comm_delete(Comm_Handle comm)
{
    DSP_STATUS status = DSP_SOK;

    GT_assert(curTrace, curInit > 0);

    GT_1trace(curTrace, GT_ENTER, "Comm_delete> Enter (comm=0x%x)\n", comm);

    if (comm != NULL) {
        if ((status = MSGQ_close(comm->queue)) != DSP_SOK) {
            GT_2trace(curTrace, GT_7CLASS,
                "Comm_delete(0x%x) failed: MSGQ_close() returned status 0x%x\n",
                comm, status);
        }
        Memory_free(comm, sizeof(Comm_Obj), NULL);
    }

    GT_1trace(curTrace, GT_ENTER, "Comm_delete> return%s\n",
        status == DSP_SOK ? "" : " (note MSGQ_close() failure)");
}


/*
 *  ======== Comm_exit ========
 */
Void Comm_exit(Void)
{
    GT_assert(curTrace, curInit > 0);

    if (--curInit == 0) {
//TODO:H        Memory_exit();

        if (moduleLock != NULL) {
            Lock_delete(moduleLock);
        }

        destroyCePoolAttrs();
    }
}


/*
 *  ======== Comm_free ========
 */
Int Comm_free(Comm_Msg msg)
{
    DSP_STATUS status;
    Int        retVal;

    GT_assert(curTrace, curInit > 0);

    GT_1trace(curTrace, GT_ENTER, "Comm_free> Enter (msg=0x%x)\n", msg);

    status = MSGQ_free((MsgqMsg)msg);
    retVal = (status == DSP_SOK ? Comm_EOK : Comm_EFAIL);

    GT_1trace(curTrace, GT_ENTER, "Comm_free> return (%d)\n", retVal);

    return (retVal);
}


/*
 *  ======== Comm_get ========
 */
Int Comm_get(Comm_Queue queue, Comm_Msg *msg, UInt timeout)
{
    UInt32     maxTimeout = timeout;
    DSP_STATUS status;
    Int        retVal;

    GT_assert(curTrace, curInit > 0);

    GT_3trace(curTrace, GT_ENTER, "Comm_get> "
        "Enter(queue=0x%x, msg=0x%x, timeout=%d)\n", queue, msg, timeout);

    *msg = NULL;

    if (timeout > ti_sdo_ce_ipc_dsplink_Ipc_maxTimeout) {
        GT_2trace(curTrace, GT_2CLASS, "Comm_get> overriding timeout provided "
                "(0x%x) with max configured timeout (0x%x)\n",
                timeout, ti_sdo_ce_ipc_dsplink_Ipc_maxTimeout);

        maxTimeout = ti_sdo_ce_ipc_dsplink_Ipc_maxTimeout;
    }

    status = MSGQ_get((MsgqQueue)queue,
            maxTimeout == Comm_FOREVER ? WAIT_FOREVER : maxTimeout,
            (MsgqMsg *)msg);

    switch (status) {
        case DSP_SOK:
            retVal = Comm_EOK;
            break;

        case DSP_ETIMEOUT:
        case DSP_ENOTCOMPLETE:
            /*
             * DSP_ENOTCOMPLETE is returned only when timeout is 0 (or, in
             * DSPLINK-speak, is SYNC_NOWAIT or WAIT_NONE) and the resource
             * is not available.
             *
             * DSP_ETIMEOUT is returned when timeout is non-zero and the
             * resource is not available.  For the "FOREVER" case it should
             * not be possible to return with failure (it either returns
             * sucesss or waits forever), but other out-of-band failures could
             * occur, in which case we just "punt" by spinning forever.  If
             * the user wants to handle this case as a timeout instead of
             * spinning, they should set the ti.sdo.ce.ipc.dsplink.maxTimeout
             * config element to a non-FOREVER value (i.e., not -1), in which
             * case a value of Comm_FOREVER will never be seen here (it will
             * get "capped" above).
             */
            retVal = Comm_ETIMEOUT;

            if (timeout == Comm_FOREVER) {
                GT_0trace(curTrace, GT_7CLASS, "Comm_get()> Error: "
                        "timeout occurred, spinning forever\n");
                while (1) {
                    sleep(MAXSLEEP);
                }

                GT_assert(curTrace, FALSE);
            }

            break;

        default:
            retVal = Comm_EFAIL;
            break;
    }

    GT_2trace(curTrace, GT_ENTER, "Comm_get> MSGQ_get() status=0x%x, return (%d)\n", status, retVal);

    return (retVal);
}

/*
 *  ======== Comm_getMsgSize ========
 */
Int Comm_getMsgSize(Comm_Msg msg)
{
    GT_assert(curTrace, curInit > 0);

    return (MSGQ_getMsgSize((MsgqMsg)msg));
}

/*
 *  ======== Comm_getSrcQueue ========
 */
Int Comm_getSrcQueue(Comm_Msg msg, Comm_Queue *msgqQueue)
{
    DSP_STATUS status;
    Int        retVal;

    GT_assert(curTrace, curInit > 0);

    status = MSGQ_getSrcQueue((MsgqMsg)msg, (MsgqQueue *)msgqQueue);
    retVal = (status == DSP_SOK ? Comm_EOK : Comm_EFAIL);

    return (retVal);
}


/*
 *  ======== Comm_init ========
 */
Bool Comm_init(Void)
{
    if (curInit++ == 0) {

        GT_create(&curTrace, Comm_GTNAME);

        initCePoolAttrs();

        moduleLock = Lock_create(NULL);
        if (moduleLock == NULL) {
            GT_0trace(curTrace, GT_7CLASS, "Comm_init> "
              "ERROR: could not create pthread mutex.\n");
            assert(FALSE);
        }

        Global_atexit((Fxn)Comm_exit);
    }

    assert(sizeof(Comm_MsgHeader) >= sizeof(MsgqMsgHeader));

    return (TRUE);
}


/*
 *  ======== Comm_locate ========
 */
Int Comm_locate(String queueName, Comm_Queue *queue)
{
    MsgqLocateAttrs syncLocateAttrs;
    DSP_STATUS status;
    Int retVal;

    /* number of times to retry locate; generated by Global.xdt */
    extern Int Comm_LOCATERETRIES;

    Int retries = 1;

    GT_assert(curTrace, curInit > 0);

    GT_2trace(curTrace, GT_ENTER, "Comm_locate> "
        "Enter(queueName='%s', queue=0x%x)\n", queueName, queue);

    *queue = Comm_INVALIDMSGQ;
    syncLocateAttrs.timeout = WAIT_FOREVER;

    do {
        Lock_acquire(moduleLock);
        status = MSGQ_locate(queueName, (MsgqQueue *)queue,
            &syncLocateAttrs);
        Lock_release(moduleLock);

        if (status != DSP_SOK) {
            GT_3trace(curTrace, GT_6CLASS, "Comm_locate> "
            "Attempt %d of %d to locate DSP's MSGQ '%s' failed. Retrying...\n",
            retries, Comm_LOCATERETRIES, queueName);
        }

        ++retries;
    } while ((retries <= Comm_LOCATERETRIES) && (status != DSP_SOK));

    /* TODO:M other osals should do the same thing, not return what their */
    /* callees return */
    retVal = (status == DSP_SOK ? Comm_EOK : Comm_EFAIL);

    if (status != DSP_SOK) {
        GT_2trace(curTrace, GT_7CLASS, "Comm_locate> "
        "Error: could not locate DSP server's MSGQ '%s' in %d retries. "
        "Check if you have the "
        "correct DSP image, or increase the number of retries "
        "(see ti.sdo.ce.osal.Global's commLocateRetries config param.\n",
        queueName, Comm_LOCATERETRIES );
    }

    GT_1trace(curTrace, GT_ENTER, "Comm_locate> return (%d)\n", retVal);

    return (retVal);
}


/*
 *  ======== Comm_put ========
 */
Int Comm_put(Comm_Queue queue, Comm_Msg msg)
{
    DSP_STATUS status;
    Int        retVal;

    GT_assert(curTrace, curInit > 0);

    GT_2trace(curTrace, GT_ENTER, "Comm_put> "
        "Enter(queue=0x%x, msg=0x%x)\n", queue, msg);

    status = MSGQ_put((MsgqQueue)queue, (MsgqMsg)msg);
    retVal = (status == DSP_SOK ? Comm_EOK : Comm_EFAIL);

    GT_1trace(curTrace, GT_ENTER, "Comm_put> return (%d)\n", retVal);

    return (retVal);
}


/*
 *  ======== Comm_release ========
 */
Int Comm_release(Comm_Queue queue)
{
    DSP_STATUS status;
    Int        retVal;

    GT_assert(curTrace, curInit > 0);

    GT_1trace(curTrace, GT_ENTER, "Comm_release> Enter(queue=0x%x)\n", queue);

    status = MSGQ_release((MsgqQueue)queue);
    retVal = (status == DSP_SOK ? Comm_EOK : Comm_EFAIL);

    GT_1trace(curTrace, GT_ENTER, "Comm_release> "
        "return (%d)\n", retVal);

    return (retVal);
}


/*
 *  ======== Comm_setSrcQueue ========
 */
Void Comm_setSrcQueue(Comm_Msg msg, Comm_Queue queue)
{
    GT_assert(curTrace, curInit > 0);

    MSGQ_setSrcQueue((MsgqMsg)msg, (MsgqQueue)queue);
}





/* --------------------------------------------------------------- */
/* DSPLINK POOL configuration                                      */

#if 0    /* this is how we used to statically configure link */
         /* keep this #if0-endif block for reference, remove when all stable */

/* TODO:H some/all of this has to be configurable */
#include <platform.h>   /* needed for ZCPYMQT_CTRLMSG_SIZE */

/** ===========================================================================
 *  @name   CEPOOLID
 *
 *  @desc   ID of the POOL used for the server.
 *  ===========================================================================
 */
Int Global_cePoolId = 0;

/** ===========================================================================
 *  @const  NUMMSGPOOLS
 *
 *  @desc   Number of BUF pools in the pool
 *  ===========================================================================
 */
#define NUMMSGPOOLS     2

/** ===========================================================================
 *  @const  NUMMSGINPOOL0
 *
 *  @desc   Number in first message pool.
 *  ===========================================================================
 */
#define NUMMSGINPOOL0   64

/** ===========================================================================
 *  @const  NUMMSGINPOOL1
 *
 *  @desc   Number in second message pool.
 *  ===========================================================================
 */
#define NUMMSGINPOOL1   16

/** ===========================================================================
 *  @name   commBufSizes
 *
 *  @desc   Message sizes managed by the pool.
 *  ===========================================================================
 */
static UInt32 commBufSizes[NUMMSGPOOLS] =
{
    Comm_MSGSIZE,
    ZCPYMQT_CTRLMSG_SIZE,
};

/** ===========================================================================
 *  @name   commNumBuffers
 *
 *  @desc   Number of messages in each pool managed by the pool.
 *  ===========================================================================
 */
static UInt32 commNumBuffers[NUMMSGPOOLS] =
{
    NUMMSGINPOOL0,
    NUMMSGINPOOL1,
};

/** ===========================================================================
 *  @name   Global_cePoolAttrs
 *
 *  @desc   Definition of attributes for the pool based on physical link used
 *          by the MQT.
 *  ===========================================================================
 */
SmaPoolAttrs Global_cePoolAttrs =
{
    NUMMSGPOOLS,        /* number of buffer sizes */
    commBufSizes,       /* array of buffer sizes in this pool */
    commNumBuffers,     /* array of number of buffers of each size */
    TRUE                /* exact match required */
};

#endif // 0

#include <archdefs.h>   /* needed for ZCPYMQT_CTRLMSG_SIZE */


/* ID of the POOL used for the server */
Int Global_cePoolId = 0;

/* Number of BUF pools in the pool */
#define NUMMSGPOOLS     2

/* Number of messages in the first message pool */
extern  UInt32 Comm_NUMMSGS;                         /* defined in Global.xdt */

/* Number of messages in the second message pool */
#define NUMMSGINPOOL1   16

/* Sizes of buffers in each pool -- undefs to be set in the function below */
static UInt32 commBufSizes[ NUMMSGPOOLS ] =
{
    -1,                       /* undefined; will be set to Comm_MSGSIZE below */
    ZCPYMQT_CTRLMSG_SIZE,
};

/* Number of messages in each pool -- to be set in the function below */
static UInt32 commNumBuffers[ NUMMSGPOOLS ] =
{
    -1,                      /* will be set to Comm_NUMMSGS below */
    NUMMSGINPOOL1,
};

/* Definition of attributes for the pool based on physical link used by MQT */
SmaPoolAttrs Global_cePoolAttrs =
{
    NUMMSGPOOLS,        /* number of buffer sizes */
    commBufSizes,       /* array of buffer sizes in this pool */
    commNumBuffers,     /* array of number of buffers of each size */
    TRUE                /* exact match required */
};

/*
 *  ======== initCePoolAttrs ========
 *  Based on Global configuration, fills in the Global_cePoolAttrs structure
 *  above to be used by Processor when it calls DSPLINK's POOL_open()
 */
static Void initCePoolAttrs()
{
    commBufSizes[0]   = Comm_MSGSIZE;
    commNumBuffers[0] = Comm_NUMMSGS;
}

/*
 *  ======== destroyCePoolAttrs ========
 *  Deletes any resources allocated for creation of pool attrs
 */
static Void destroyCePoolAttrs()
{
    /* nothing to do since we didn't allocate anything; all the space comes
     * from the DSPLINK segment on the DSP.
     */
}
/*
 *  @(#) ti.sdo.ce.ipc.dsplink; 2, 0, 1,182; 12-2-2010 21:24:20; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

