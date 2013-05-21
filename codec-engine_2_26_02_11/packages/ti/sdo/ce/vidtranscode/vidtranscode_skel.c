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
 *  ======== vidtranscode_skel.c ========
 *  This file contains the implemenation of the SKEL interface for the
 *  video transcoder class of algorithms.
 *
 *  These functions are the "server-side" of the the stubs defined in
 *  vidtranscode_stubs.c
 */
#include <xdc/std.h>
#include <ti/sdo/ce/skel.h>
#include <ti/sdo/ce/osal/Memory.h>

#include "vidtranscode.h"
#include "_vidtranscode.h"

/*
 *  ======== call ========
 */
static VISA_Status call(VISA_Handle visaHandle, VISA_Msg visaMsg)
{
    _VIDTRANSCODE_Msg *msg  = (_VIDTRANSCODE_Msg *)visaMsg;
    VIDTRANSCODE_Handle handle = (VIDTRANSCODE_Handle)visaHandle;
    Int i;
    XDM1_BufDesc inBufs;
    XDM_BufDesc outBufs;
    IVIDTRANSCODE_OutArgs *pOutArgs;
    IVIDTRANSCODE_Status *pStatus;
    Int numBufs;

    /* perform the requested VIDTRANSCODE operation by parsing message. */
    switch (msg->visa.cmd) {

        case _VIDTRANSCODE_CPROCESS: {
            /* unmarshal inBufs and outBufs */
            inBufs           = msg->cmd.process.inBufs;

            outBufs.bufs     = msg->cmd.process.outBufs;
            outBufs.numBufs  = msg->cmd.process.numOutBufs;
            outBufs.bufSizes = msg->cmd.process.outBufSizes;

            if (SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB) {
                /* invalidate cache for all input buffers */
                for (i = 0, numBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
                    if (inBufs.descs[i].buf != NULL) {
                        /* valid member of sparse array, manage it */
                        Memory_cacheInv(inBufs.descs[i].buf,
                                inBufs.descs[i].bufSize);

                        if (++numBufs == inBufs.numBufs) {
                            break;
                        }
                    }
                }

                /* invalidate cache for all output buffers */
                for (i = 0, numBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
                    if (outBufs.bufs[i] != NULL) {
                        /* valid member of sparse array, manage it */
                        Memory_cacheInv(outBufs.bufs[i], outBufs.bufSizes[i]);

                        if (++numBufs == outBufs.numBufs) {
                            break;
                        }
                    }
                }
            }

            /* unmarshall outArgs based on the "size" of inArgs */
            pOutArgs = (IVIDTRANSCODE_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
                msg->cmd.process.inArgs.size);

            /*
             * Note, there's no need to invalidate cache for
             * pOutArgs->encodedBuf bufs as they're
             * not _really_ OUT buffers.  Rather they're references to
             * the _real_ OUT buffers that are provided in outBufs - which
             * were already invalidated above.
             */

            /* make the process call */
            msg->visa.status = VIDTRANSCODE_process(handle,
                &inBufs, &outBufs, &(msg->cmd.process.inArgs), pOutArgs);

            if (SKEL_cachingPolicy == SKEL_WBINVALL) {
                Memory_cacheWbInvAll();
            }
            else if (SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB) {
                /* writeback cache for encoded buffers  */
                for (i = 0; i < IVIDTRANSCODE_MAXOUTSTREAMS; i++) {
                    if ((pOutArgs->outputID[0] != 0) &&
                            (pOutArgs->encodedBuf[i].buf != NULL) &&
                            XDM_ISACCESSMODE_WRITE(pOutArgs->encodedBuf[i].accessMask)) {

                        Memory_cacheWb(pOutArgs->encodedBuf[i].buf,
                                pOutArgs->encodedBuf[i].bufSize);

                        /*
                         * Since we've cacheWb this buffer, we arguably should
                         * reflect this cache state and clear the WRITE bit in
                         * the .accessMask field.  However, we know the stub
                         * doesn't propogate this field to the calling app, so
                         * this extra buffer management detail isn't necessary:
                         *
                         * XDM_CLEARACCESSMODE_WRITE(
                         *         pOutArgs.encodedBuf[i].accessMask);
                         */
                    }
                }
            }

            /*
             * Note that any changes to individual outBufs[i] values made by
             * the codec will automatically update msg->cmd.process.outBufs
             * as we pass the outBufs array by reference.
             */

            break;
        }

        case _VIDTRANSCODE_CCONTROL: {
            /* unmarshall status based on the "size" of params */
            pStatus =
                (IVIDTRANSCODE_Status *)((UInt)(&(msg->cmd.control.dynParams)) +
                msg->cmd.control.dynParams.size);

            /* invalidate data buffer */
            if (pStatus->data.buf != NULL) {
                Memory_cacheInv(pStatus->data.buf, pStatus->data.bufSize);
            }

            msg->visa.status = VIDTRANSCODE_control(handle, msg->cmd.control.id,
                &(msg->cmd.control.dynParams), pStatus);

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
 *  ======== VIDTRANSCODE_SKEL ========
 */
SKEL_Fxns VIDTRANSCODE_SKEL = {
    call,
    (SKEL_CREATEFXN)&VIDTRANSCODE_create,
    (SKEL_DESTROYFXN)&VIDTRANSCODE_delete,
};
/*
 *  @(#) ti.sdo.ce.vidtranscode; 1, 0, 1,227; 12-2-2010 21:28:34; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

