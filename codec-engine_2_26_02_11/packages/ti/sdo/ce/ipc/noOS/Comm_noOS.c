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
 *  ======== Comm_noOS.c ========
 */

#include <xdc/std.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/osal/Global.h>

#include <ti/sdo/utils/trace/gt.h>

typedef struct Comm_Obj {
    String                 name;        /* Unique name of the queue         */
    struct Comm_Obj       *next;        /* next Comm_Obj in the global list */
    struct Comm_MsgHeader *msg;         /* NULL or the one message waiting  */
    Comm_CallFxn           callFxn;     /* opt. "R"PC fxn to call on put()  */
    Ptr                    callHandle;  /* arguments to the fxn             */
    Bool                   inUse;       /* in use flag */
} Comm_Obj;

/*
 *  ======== Comm_ATTRS ========
 *  Default creation attrs
 */
Comm_Attrs Comm_ATTRS = {
    Comm_CALL,
    NULL,
    NULL
};

/* REMINDER: if you add an initialized static var, reinitialize it at cleanup */
static Int curInit = 0;                 /* module init counter */
static Comm_Handle msgqList = NULL;
static GT_Mask curTrace;

/*
 *  ======== Comm_alloc ========
 */
Int  Comm_alloc(UInt16 poolId, Comm_Msg *msg, UInt16 size)
{
    GT_assert(curTrace, curInit > 0);
    GT_assert(curTrace, msg != NULL);

    GT_3trace(curTrace, GT_ENTER, "Comm_alloc> "
        "Enter(poolId=0x%x, msg=0x%x, size=%d)\n", poolId, msg, size);

    *msg = (Comm_Msg)malloc(size);
    (*msg)->size = size;
    return ((msg == NULL) ? Comm_EFAIL : Comm_EOK);
}


/*
 *  ======== Comm_create ========
 */
Comm_Handle Comm_create(String queueName, Comm_Queue *msgqQueue,
    Comm_Attrs *attrs)
{
    Comm_Handle mq;
    Bool newFlag = FALSE;

    for (mq = msgqList; mq != NULL; mq = mq->next) {
        if (mq->inUse && strcmp(mq->name, queueName) == 0) {
            GT_1trace(curTrace, GT_4CLASS,
                "Comm_create> creating identically named queues (%s)\n",
                mq->name);
        }
    }

    /* try to find a non-inUse Comm slot and reuse it, or create a new one */
    for (mq = msgqList; mq != NULL; mq = mq->next) {
        if (mq->inUse == FALSE) {
            break;  /* found one */
        }
    }
    if (mq == NULL) {
        mq = (Comm_Handle)malloc(sizeof(Comm_Obj));
        if (mq == NULL) {
            return (NULL);
        }
        newFlag = TRUE;
    }

    if (attrs == NULL) {
        attrs = &Comm_ATTRS;
    }

    mq->msg        = NULL;
    mq->name       = queueName;
    mq->callFxn    = attrs->callFxn;
    mq->callHandle = attrs->callHandle;
    mq->inUse      = TRUE;

    if (newFlag) {
        mq->next = msgqList;
        msgqList = mq;
    }

    *msgqQueue = (Comm_Queue)mq;

    return (mq);
}


/*
 *  ======== Comm_delete ========
 */
Void Comm_delete(Comm_Handle msgqQueue)
{
    msgqQueue->inUse = FALSE;
}


/*
 *  ======== Comm_exit ========
 */
Void Comm_exit(Void)
{
    GT_assert(curTrace, curInit > 0);

    if (--curInit == 0) {
    }
}


/*
 *  ======== Comm_free ========
 */
Int  Comm_free(Comm_Msg msg)
{
    free(msg);
    return (Comm_EOK);
}

/*
 *  ======== Comm_get ========
 */
Int  Comm_get(Comm_Queue msgqQueue, Comm_Msg *msg, UInt timeout)
{
    Comm_Handle mq = (Comm_Handle)msgqQueue;

    assert(mq->msg != NULL);

    *msg = mq->msg;
    mq->msg = NULL;

    return (Comm_EOK);
}

/*
 *  ======== Comm_getMsgSize ========
 */
Int Comm_getMsgSize(Comm_Msg msg)
{
    return (msg->size);
}

/*
 *  ======== Comm_getSrcQueue ========
 */
Int  Comm_getSrcQueue(Comm_Msg msg, Comm_Queue *msgqQueue)
{
    if (msg->reserved4 == Comm_INVALIDMSGQ) {
        return (Comm_EFAIL);
    }

    *msgqQueue = msg->reserved4;
    return (Comm_EOK);
}


/*
 *  ======== Comm_init ========
 */
Bool Comm_init(Void)
{
    if (curInit++ == 0) {

        GT_create(&curTrace, Comm_GTNAME);

        Global_atexit((Fxn)Comm_exit);
    }

    return (TRUE);
}

/*
 *  ======== Comm_locate ========
 */
Int Comm_locate(String queueName, Comm_Queue *msgqQueue)
{
    Comm_Handle mq;

    *msgqQueue = Comm_INVALIDMSGQ;
    for (mq = msgqList; mq != NULL; mq = mq->next) {
        if (mq->inUse && strcmp(mq->name, queueName) == 0) {
            *msgqQueue = (Comm_Queue)mq;
            return (Comm_EOK);
        }
    }

    return (Comm_EFAIL);
}


/*
 *  ======== Comm_release ========
 */
Int  Comm_release(Comm_Queue msgqQueue)
{
    return (Comm_EOK);
}




/*
 *  ======== Comm_put ========
 */
Int  Comm_put(Comm_Queue msgqQueue, Comm_Msg msg)
{
    Comm_Handle mq = (Comm_Handle)msgqQueue;

    mq->msg = msg;

    if (mq->callFxn != NULL) {
        mq->callFxn(mq->callHandle);
    } /* TODO:L no status  */

    return (Comm_EOK);
}



/*
 *  ======== Comm_setSrcQueue ========
 */
Void Comm_setSrcQueue(Comm_Msg msg, Comm_Queue msgqQueue)
{
    msg->reserved4 = msgqQueue;
}


/*
 *  @(#) ti.sdo.ce.ipc.noOS; 2, 0, 1,179; 12-2-2010 21:24:21; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

