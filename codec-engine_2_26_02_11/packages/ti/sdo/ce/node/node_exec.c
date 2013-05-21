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
 *  ======== node_exec.c ========
 */
#include <xdc/std.h>
#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/osal/Thread.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/utils/trace/gt.h>

#include "node.h"
#include "_node.h"

/*
 *  ======== NODE_receive ========
 */
static inline NODE_Status NODE_receive(NODE_Handle node, NODE_Msg *msg)
{
    Comm_Queue  myQueue;
    NODE_Status status = NODE_EOK;

    myQueue = NODE_getRecvQueue(node);
    if (Comm_get(myQueue, (Comm_Msg *)msg, Comm_FOREVER) != Comm_EOK) {
        status = NODE_EFAIL;
    }

    return (status);
}

/*
 *  ======== NODE_reply ========
 */
static inline NODE_Status NODE_reply(NODE_Handle node, NODE_Msg msg)
{
    Comm_Queue  gppQueue;
    NODE_Status status = NODE_EOK;

    gppQueue = NODE_getSendQueue(node);
    if (Comm_put(gppQueue, (Comm_Msg)msg) != Comm_EOK) {
        status = NODE_EFAIL;
    }

    return (status);
}

/*
 *  ======== NODE_EXECFXN ========
 */
NODE_Status NODE_EXECFXN(NODE_Handle node)
{
    VISA_Msg msg;
    VISA_Handle visaHandle = NODE_getEnv(node);
    NODE_Status status;

    for (;;) {
        /* wait for a data message -- Comm messsage from GPP */
        if ((status = NODE_receive(node, (NODE_Msg *)&msg)) != NODE_EOK) {
            break;
        }

        /* if we are told to exit, ack and return */
        if (msg->header.cmd.id == NODE_CEXIT) {
            NODE_reply(node, (NODE_Msg)msg);
            GT_2trace(_NODE_curTrace, GT_ENTER,
                "NODE_EXECFXN(0x%x): %s exiting per request ...\n",
                node, Thread_getname(Thread_self()));
            return (NODE_EOK);
        }

        /* otherwise, do the work */
        GT_5trace(_NODE_curTrace, GT_5CLASS, "NODE> 0x%x(%s) "
            "call(algHandle=0x%x, msg=0x%x); messageId=0x%08x\n",
            node, Thread_getname(Thread_self()), visaHandle,
            msg, msg->header.cmd.arg1);

        node->skelFxns->call(visaHandle, msg);

        GT_3trace(_NODE_curTrace, GT_5CLASS, "NODE> "
            "returned from call(algHandle=0x%x, msg=0x%x); messageId=0x%08x\n",
            visaHandle, msg, msg->header.cmd.arg1);

        /* send back results */
        if ((status = NODE_reply(node, (NODE_Msg)msg)) != NODE_EOK) {
            break;
        }
    }

    /* terminating. */
    GT_3trace(_NODE_curTrace, GT_6CLASS, "NODE_EXECFXN(0x%x): %s "
        "terminated early due to comm failure (exit status %d)\n",
        node, Thread_getname(Thread_self()), status);
    return (status);
}
/*
 *  @(#) ti.sdo.ce.node; 1, 0, 0,427; 12-2-2010 21:24:36; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

