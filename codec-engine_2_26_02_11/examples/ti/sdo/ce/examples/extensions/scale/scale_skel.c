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
 *  ======== scale_skel.c ========
 *  This file contains the implemenation of the SKEL interface for
 *  SCALE algorithms.
 *
 *  These functions are the "server-side" of the the stubs defined in
 *  scale_stubs.c
 */
#include <xdc/std.h>
#include <ti/sdo/ce/skel.h>
#include <ti/sdo/ce/osal/Memory.h>

#include "scale.h"
#include "_scale.h"

/*
 *  ======== call ========
 */
static VISA_Status call(VISA_Handle visaHandle, VISA_Msg visaMsg)
{
    _SCALE_Msg *msg  = (_SCALE_Msg *)visaMsg;
    SCALE_Handle handle = (SCALE_Handle)visaHandle;
    XDAS_Int8 *inBuf;
    XDAS_Int8 *outBuf;

    /* perform the requested SCALE operation by parsing message. */
    switch (msg->visa.cmd) {

        case _SCALE_CPROCESS: {
            /* unmarshall inBuf and outBuf */
            inBuf  = msg->cmd.process.inBuf;
            outBuf = msg->cmd.process.outBuf;

            /* invalidate cache for input and output buffers */
            Memory_cacheInv(inBuf, msg->cmd.process.inArgs.inBufSize);
            Memory_cacheInv(outBuf, msg->cmd.process.inArgs.outBufSize);

            /* make the process call */
            msg->visa.status = SCALE_process(handle, inBuf, outBuf,
                &(msg->cmd.process.inArgs), &(msg->cmd.process.outArgs));

            /* flush cache for output buffer */
            Memory_cacheWbInv(outBuf, msg->cmd.process.inArgs.outBufSize);

            /*
             * Note that any changes to individual outBufs[i] values made by
             * the codec will automatically update msg->cmd.process.outBufs
             * as we pass the outBufs array by reference.
             */

            break;
        }

        case _SCALE_CCONTROL: {
            msg->visa.status = SCALE_control(handle, msg->cmd.control.id,
                &(msg->cmd.control.params));

             break;
        }

        default: {
            msg->visa.status = VISA_EFAIL;

            break;
        }
    }
    return (VISA_EOK);
}

/*
 *  ======== SCALE_SKEL ========
 */
SKEL_Fxns SCALE_SKEL = {
    call,
    (SKEL_CREATEFXN)SCALE_create,
    (SKEL_DESTROYFXN)SCALE_delete,
};
/*
 *  @(#) ti.sdo.ce.examples.extensions.scale; 1, 0, 0,261; 12-2-2010 21:23:31; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

