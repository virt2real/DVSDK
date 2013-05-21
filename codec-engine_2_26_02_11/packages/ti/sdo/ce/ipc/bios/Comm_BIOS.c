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
 *  ======== Comm_BIOS.c ========
 *
 *  Note that the implementation of this module assumes that
 *  Comm_EOK == SYS_EOK as it often returns "whatever MSGQ returns".
 */
#include <xdc/std.h>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/ipc/Comm.h>

#include <ti/bios/include/std.h>
#include <ti/bios/include/msgq.h>
#include <ti/bios/include/sem.h>
#include <ti/bios/include/sys.h>

typedef struct Comm_Obj {
    MSGQ_Queue      queue;
    SEM_Obj         sem;
} Comm_Obj;

Comm_Attrs Comm_ATTRS = {
    Comm_PEND
};

/*
 *  ======== Comm_create ========
 */
Comm_Handle Comm_create(String queueName, Comm_Queue *msgqQueue, Comm_Attrs *myAttrs)
{
    Comm_Obj   *msgq;
    MSGQ_Attrs attrs       = MSGQ_ATTRS;

    if (myAttrs == NULL) {
        myAttrs = &Comm_ATTRS;
    }

    msgq = (Comm_Obj *)Memory_alloc(sizeof(Comm_Obj), NULL);
    if (msgq == NULL) {
        return (NULL);
    }

    if (myAttrs->type == Comm_PEND) {
        SEM_new(&msgq->sem, 0);
        attrs.notifyHandle = &msgq->sem;
        attrs.pend         = (MSGQ_Pend)SEM_pendBinary;
        attrs.post         = (MSGQ_Post)SEM_postBinary;
    }
    else if (myAttrs->type == Comm_CALL) {
        attrs.notifyHandle = myAttrs->callHandle;
        attrs.post         = (MSGQ_Post)myAttrs->callFxn;
    }
    else {
        assert(FALSE);  /* unknown Comm type */
    }

    if (MSGQ_open(queueName, msgqQueue, &attrs) != SYS_OK) {
        Memory_free(msgq, sizeof(Comm_Obj), NULL);
        return (NULL);
    }
    msgq->queue = *msgqQueue;

    return (msgq);
}

/*
 *  ======== Comm_delete ========
 */
Void Comm_delete(Comm_Handle msgq)
{
    if (msgq != NULL) {
        MSGQ_close(msgq->queue);
        Memory_free(msgq, sizeof (Comm_Obj), NULL);
    }
}

/*
 *  ======== Comm_locate ========
 */
Int  Comm_locate(String queueName, Comm_Queue *msgqQueue)
{
    *msgqQueue = Comm_INVALIDMSGQ;
    return (MSGQ_locate(queueName, (MSGQ_Queue *)msgqQueue, NULL));
}

/*
 *  ======== Comm_release ========
 */
Int Comm_release(Comm_Queue msgqQueue)
{
    return (MSGQ_release((MSGQ_Queue)msgqQueue));
}

/*
 *  ======== Comm_alloc ========
 */
Int Comm_alloc(UInt16 poolId, Comm_Msg *msg, UInt16 size)
{
    return (MSGQ_alloc(poolId, (MSGQ_Msg *)msg, size));
}

/*
 *  ======== Comm_free ========
 */
Int Comm_free(Comm_Msg msg)
{
    return (MSGQ_free((MSGQ_Msg)msg));
}

/*
 *  ======== Comm_put ========
 */
Int Comm_put(Comm_Queue msgqQueue, Comm_Msg msg)
{
    return (MSGQ_put((MSGQ_Queue)msgqQueue, (MSGQ_Msg)msg));
}

/*
 *  ======== Comm_get ========
 */
Int Comm_get(Comm_Queue msgqQueue, Comm_Msg *msg, UInt timeout)
{
    *msg = NULL;

    return (MSGQ_get((MSGQ_Queue)msgqQueue, (MSGQ_Msg *)msg, timeout));
}

/*
 *  ======== Comm_getMsgSize ========
 */
Int Comm_getMsgSize(Comm_Msg msg)
{
    return (MSGQ_getMsgSize((MSGQ_Msg)msg));
}

/*
 *  ======== Comm_getSrcQueue ========
 */
Int Comm_getSrcQueue(Comm_Msg msg, Comm_Queue *msgqQueue)
{
    return (MSGQ_getSrcQueue((MSGQ_Msg)msg, (MSGQ_Queue *)msgqQueue));
}

/*
 *  ======== Comm_setSrcQueue ========
 */
Void Comm_setSrcQueue(Comm_Msg msg, Comm_Queue msgqQueue)
{
    MSGQ_setSrcQueue((MSGQ_Msg)msg, (MSGQ_Queue)msgqQueue);
}

/*
 *  ======== Comm_init ========
 */
Bool Comm_init(Void)
{
    assert(sizeof (Comm_MsgHeader) >= sizeof (MSGQ_MsgHeader));

    return (TRUE);
}

/*
 *  ======== Comm_exit ========
 */
Void Comm_exit(Void)
{
}

/*
 *  @(#) ti.sdo.ce.ipc.bios; 2, 0, 1,179; 12-2-2010 21:24:02; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

