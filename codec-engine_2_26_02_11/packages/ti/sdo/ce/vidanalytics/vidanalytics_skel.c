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
 *  ======== vidanalytics_skel.c ========
 *  This file contains the implemenation of the SKEL interface for the
 *  video analytics class of algorithms.
 *
 *  These functions are the "server-side" of the the stubs defined in
 *  vidanalytics_stubs.c
 */
#include <xdc/std.h>
#include <ti/sdo/ce/skel.h>
#include <ti/sdo/ce/osal/Memory.h>

#include "vidanalytics.h"
#include "_vidanalytics.h"

/*
 *  ======== call ========
 */
static VISA_Status call(VISA_Handle visaHandle, VISA_Msg visaMsg)
{
    _VIDANALYTICS_Msg *msg  = (_VIDANALYTICS_Msg *)visaMsg;
    VIDANALYTICS_Handle handle = (VIDANALYTICS_Handle)visaHandle;
    Int i;
    XDM1_BufDesc inBufs;
    XDM1_BufDesc outBufs;
    IVIDANALYTICS_OutArgs *pOutArgs;
    IVIDANALYTICS_Status *pStatus;
    Int numBufs;

    /* perform the requested VIDANALYTICS operation by parsing message. */
    switch (msg->visa.cmd) {

        case _VIDANALYTICS_CPROCESS: {
            /* unmarshal inBufs and outBufs */
            inBufs           = msg->cmd.process.inBufs;
            outBufs          = msg->cmd.process.outBufs;

            if (SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB) {
                /* invalidate cache for all input buffers */
                for (i = 0, numBufs = 0; (numBufs < inBufs.numBufs) &&
                         (i < XDM_MAX_IO_BUFFERS); i++) {
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
                for (i = 0, numBufs = 0; (numBufs < outBufs.numBufs) &&
                         (i < XDM_MAX_IO_BUFFERS); i++) {
                    if (outBufs.descs[i].buf != NULL) {
                        /* valid member of sparse array, manage it */
                        Memory_cacheInv(outBufs.descs[i].buf,
                                outBufs.descs[i].bufSize);

                        if (++numBufs == outBufs.numBufs) {
                            break;
                        }
                    }
                }
            } /* SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB */

            /* unmarshall outArgs based on the "size" of inArgs */
            pOutArgs =
                (IVIDANALYTICS_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
                    msg->cmd.process.inArgs.size);

            /*
             * Note, there's no need to invalidate cache for
             * pOutArgs->encodedBuf bufs as they're
             * not _really_ OUT buffers.  Rather they're references to
             * the _real_ OUT buffers that are provided in outBufs - which
             * were already invalidated above.
             */

            /* make the process call */
            msg->visa.status = VIDANALYTICS_process(handle,
                &inBufs, &outBufs, &(msg->cmd.process.inArgs), pOutArgs);

            if (SKEL_cachingPolicy == SKEL_WBINVALL) {
                Memory_cacheWbInvAll();
            }
            else if (SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB) {
                /* writeback cache for analysis output buffers  */
                for (i = 0, numBufs = 0; (numBufs < outBufs.numBufs) &&
                         (i < XDM_MAX_IO_BUFFERS); i++) {
                    if ((outBufs.descs[i].buf != NULL) &&
                            XDM_ISACCESSMODE_WRITE(outBufs.descs[i].accessMask)) {

                        /* valid member of sparse array, written to via CPU */
                        Memory_cacheWb(outBufs.descs[i].buf,
                                outBufs.descs[i].bufSize);

                        /*
                         * Since we've cacheWb this buffer, we arguably should
                         * reflect this cache state and clear the WRITE bit in
                         * the .accessMask field.  However, we know the stub
                         * doesn't propogate this field to the calling app, so
                         * this extra buffer management detail isn't necessary:
                         *
                         * XDM_CLEARACCESSMODE_WRITE(outBufs.descs[i].accessMask);
                         */

                        if (++numBufs == outBufs.numBufs) {
                            break;
                        }
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

        case _VIDANALYTICS_CCONTROL: {
            /* unmarshall status based on the "size" of dynParams */
            pStatus =
                (IVIDANALYTICS_Status *)((UInt)(&(msg->cmd.control.dynParams)) +
                msg->cmd.control.dynParams.size);

            /* invalidate data buffers */
            for (i = 0, numBufs = 0; (numBufs < pStatus->data.numBufs) &&
                    (i < XDM_MAX_IO_BUFFERS); i++) {
                if (pStatus->data.descs[i].buf != NULL) {
                    /* valid member of sparse array, manage it */
                    Memory_cacheInv(pStatus->data.descs[i].buf,
                        pStatus->data.descs[i].bufSize);

                    if (++numBufs == pStatus->data.numBufs) {
                        break;
                    }
                }
            }

            msg->visa.status = VIDANALYTICS_control(handle, msg->cmd.control.id,
                &(msg->cmd.control.dynParams), pStatus);

            /* writeback data buffers */
            for (i = 0, numBufs = 0; (numBufs < pStatus->data.numBufs) &&
                    (i < XDM_MAX_IO_BUFFERS); i++) {
                if ((pStatus->data.descs[i].buf != NULL) &&
                    XDM_ISACCESSMODE_WRITE(pStatus->data.descs[i].accessMask)) {

                    /* valid member of sparse array, manage it */
                    Memory_cacheWb(pStatus->data.descs[i].buf,
                        pStatus->data.descs[i].bufSize);

                    /*
                     * Since we've cacheWb this buffer, we arguably should
                     * reflect this cache state and clear the WRITE bit in
                     * the .accessMask field.  However, we know the stub
                     * doesn't propogate this field to the calling app, so
                     * this extra buffer management detail isn't necessary:
                     *
                     * XDM_CLEARACCESSMODE_WRITE(
                     *         pStatus->data.descs[i].accessMask);
                     */

                    if (++numBufs == pStatus->data.numBufs) {
                        break;
                    }
                }
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
 *  ======== VIDANALYTICS_SKEL ========
 */
SKEL_Fxns VIDANALYTICS_SKEL = {
    call,
    (SKEL_CREATEFXN)&VIDANALYTICS_create,
    (SKEL_DESTROYFXN)&VIDANALYTICS_delete,
};
/*
 *  @(#) ti.sdo.ce.vidanalytics; 1, 0, 1,209; 12-2-2010 21:28:16; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

