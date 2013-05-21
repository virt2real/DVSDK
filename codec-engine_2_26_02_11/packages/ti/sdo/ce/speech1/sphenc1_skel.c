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
 *  ======== sphenc1_skel.c ========
 *  This file contains the implemenation of the SKEL interface for the
 *  speech encoder class of algorithms.
 *
 *  These functions are the "server-side" of the the stubs defined in
 *  sphenc1_stubs.c
 */
#include <xdc/std.h>
#include <ti/sdo/ce/skel.h>
#include <ti/sdo/ce/osal/Memory.h>

#include "sphenc1.h"
#include "_sphenc1.h"

/*
 *  ======== call ========
 */
static VISA_Status call(VISA_Handle visaHandle, VISA_Msg visaMsg)
{
    _SPHENC1_Msg *msg  = (_SPHENC1_Msg *)visaMsg;
    SPHENC1_Handle handle = (SPHENC1_Handle)visaHandle;
    XDM1_SingleBufDesc inBuf, outBuf;
    ISPHENC1_OutArgs *pOutArgs;
    ISPHENC1_Status *pStatus;

    /* perform the requested SPHENC1 operation by parsing message. */
    switch (msg->visa.cmd) {

        case _SPHENC1_CPROCESS: {
            /* unmarshal inBufs and outBufs */
            inBuf.buf      = msg->cmd.process.inBuf.buf;
            inBuf.bufSize  = msg->cmd.process.inBuf.bufSize;
            outBuf.buf     = msg->cmd.process.outBuf.buf;
            outBuf.bufSize = msg->cmd.process.outBuf.bufSize;

            if (SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB) {
                /* invalidate cache for input buffer */
                Memory_cacheInv(inBuf.buf, inBuf.bufSize);

                /* invalidate cache for output buffer */
                Memory_cacheInv(outBuf.buf, outBuf.bufSize);

                /* conditionally invalidate cache for inArgs.data buffer */
                if (msg->cmd.process.inArgs.data.buf != NULL) {
                    Memory_cacheInv(msg->cmd.process.inArgs.data.buf,
                            msg->cmd.process.inArgs.data.bufSize);
                }
            }

            /* unmarshall outArgs based on the "size" of inArgs */
            pOutArgs = (ISPHENC1_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
                msg->cmd.process.inArgs.size);

            /* make the process call */
            msg->visa.status = SPHENC1_process(handle, &inBuf,
                &outBuf, &(msg->cmd.process.inArgs), pOutArgs);

            /* return outBuf.bufSize, and writeback cache for output buffer  */
            msg->cmd.process.outBuf.bufSize = outBuf.bufSize;

            if (SKEL_cachingPolicy == SKEL_WBINVALL) {
                Memory_cacheWbInvAll();
            }
            else if (SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB) {
                if ((outBuf.buf != NULL) &&
                        XDM_ISACCESSMODE_WRITE(outBuf.accessMask)) {

                    Memory_cacheWb(outBuf.buf, outBuf.bufSize);

                    /*
                     * Since we've cacheWb this buffer, we arguably should
                     * reflect this cache state and clear the WRITE bit in
                     * the .accessMask field.  However, we know the stub
                     * doesn't propogate this field to the calling app, so
                     * this extra buffer management detail isn't necessary:
                     *
                     * XDM_CLEARACCESSMODE_WRITE(outBuf.accessMask);
                     */
                }

                /* writeback inArgs.data.buf if necessary */
                if ((msg->cmd.process.inArgs.data.buf != NULL) &&
                        XDM_ISACCESSMODE_WRITE(
                            msg->cmd.process.inArgs.data.accessMask)) {

                    Memory_cacheWb(msg->cmd.process.inArgs.data.buf,
                            msg->cmd.process.inArgs.data.bufSize);

                    /*
                     * Since we've cacheWb this buffer, we arguably should
                     * reflect this cache state and clear the WRITE bit in
                     * the .accessMask field.  However, we know the stub
                     * doesn't propogate this field to the calling app, so
                     * this extra buffer management detail isn't necessary:
                     *
                     * XDM_CLEARACCESSMODE_WRITE(
                     *         msg->cmd.process.inArgs.data.accessMask);
                     */
                }
            }
#if 0
            /* when 'checking' is supported, assert inBuf is not written to */
#endif

            /*
             * Note that any changes to outArgs made by
             * the codec will automatically update msg->cmd.process.outArgs
             */

            break;
        }

        case _SPHENC1_CCONTROL: {
            /* unmarshall status based on the "size" of params */
            pStatus = (ISPHENC1_Status *)((UInt)(&(msg->cmd.control.params)) +
                msg->cmd.control.params.size);

            /* invalidate data buffer */
            if (pStatus->data.buf != NULL) {
                Memory_cacheInv(pStatus->data.buf, pStatus->data.bufSize);
            }

            msg->visa.status = SPHENC1_control(handle, msg->cmd.control.id,
                &(msg->cmd.control.params), pStatus);

            /* writeback data buffer */
            if ((pStatus->data.buf != NULL) &&
                XDM_ISACCESSMODE_WRITE(pStatus->data.accessMask)) {

                Memory_cacheWb(pStatus->data.buf, pStatus->data.bufSize);

                /*
                 * Since we've cacheWb this buffer, we arguably should
                 * reflect this cache state and clear the WRITE bit in
                 * the .accessMask field.  However, we know the stub
                 * doesn't propogate this field to the calling app, so
                 * this extra buffer management detail isn't necessary:
                 *
                 * XDM_CLEARACCESSMODE_WRITE(pStatus->data.accessMask);
                 */
            }

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
 *  ======== SPHENC1_SKEL ========
 */
SKEL_Fxns SPHENC1_SKEL = {
    call,
    (SKEL_CREATEFXN)&SPHENC1_create,
    (SKEL_DESTROYFXN)&SPHENC1_delete,
};
/*
 *  @(#) ti.sdo.ce.speech1; 1, 0, 1,276; 12-2-2010 21:25:22; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

