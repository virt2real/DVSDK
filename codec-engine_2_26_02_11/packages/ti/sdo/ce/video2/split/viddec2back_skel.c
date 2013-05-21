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
 *  ======== viddec2_skel.c ========
 *  This file contains the implemenation of the SKEL interface for the
 *  IVIDDEC2 class of algorithms.
 *
 *  These functions are the "server-side" of the the stubs defined in
 *  viddec2_stubs.c
 */
#include <xdc/std.h>
#include <ti/sdo/ce/skel.h>
#include <ti/sdo/ce/osal/Memory.h>

#include "viddec2.h"
#include "_viddec2back.h"

/*
 *  ======== call ========
 */
static VISA_Status call(VISA_Handle visaHandle, VISA_Msg visaMsg)
{
    _VIDDEC2BACK_Msg *msg  = (_VIDDEC2BACK_Msg *)visaMsg;
    VIDDEC2BACK_Handle handle = (VIDDEC2BACK_Handle)visaHandle;
    Int i, j;
//    XDM1_BufDesc inBufs;
//    XDM_BufDesc outBufs;
    IVIDDEC2_OutArgs *pOutArgs;
    IVIDDEC2_Status *pStatus;
    XDM_Context *pContext;
    IVIDDEC2BACK_CodecClassConfig *codecClassConfig;
    Int numBufs;

    /* get stub/skeleton config data; can be NULL (for old codecs) */
    codecClassConfig = (IVIDDEC2BACK_CodecClassConfig *)
                        VISA_getCodecClassConfig( visaHandle );

    /* perform the requested VIDDEC2 operation by parsing message. */
    switch (msg->visa.cmd) {

        case _VIDDEC2BACK_CPROCESS: {

            pContext = &(msg->cmd.process.context);

            if (SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB) {

                /* invalidate cache for algContext */
                if (pContext->algContext.buf != NULL) {
                    Memory_cacheInv(pContext->algContext.buf,
                            pContext->algContext.bufSize);
                }

                /* invalidate cache for all input buffers */
                for (i = 0, numBufs = 0; i < XDM_MAX_CONTEXT_BUFFERS; i++) {
                    if (pContext->inBufs[i].buf != NULL) {
                        /* valid member of sparse array,
                         * invalidate it unless user configured it not to
                         */
                        if (codecClassConfig != NULL &&
                                codecClassConfig->manageInBufsCache[i] == FALSE) {
                            /* do nothing, i.e. don't invalidate */
                        } else { 
                            Memory_cacheInv(pContext->inBufs[i].buf,
                                    pContext->inBufs[i].bufSize);
                        } 
                        if (++numBufs == pContext->numInBufs) {
                            break;
                        }
                    }
                }

                /* invalidate cache for all output buffers */
                for (i = 0, numBufs = 0; i < XDM_MAX_CONTEXT_BUFFERS; i++) {
                    if (pContext->outBufs[i].buf != NULL) {
                        /* valid member of sparse array,
                         * invalidate it unless user configured it not to
                         */
                        if (codecClassConfig != NULL && 
                                codecClassConfig->manageOutBufsCache[i] == FALSE) {
                            /* do nothing, i.e. don't invalidate */
                        } else {
                            Memory_cacheInv(pContext->outBufs[i].buf,
                                    pContext->outBufs[i].bufSize);
                        }

                        if (++numBufs == pContext->numOutBufs) {
                            break;
                        }
                    }
                }

                /* invalidate cache for all intermediate buffers */
                for (i = 0; ((i < XDM_MAX_CONTEXT_BUFFERS) &&
                             (pContext->intermediateBufs[i].buf != NULL)); i++) {
                    /*
                     * invalidate it unless user configured it not to
                     */
                    if (codecClassConfig != NULL &&
                            codecClassConfig->manageIntermediateBufsCache[i] == FALSE) {
                        /* do nothing, i.e. don't invalidate */
                    } else {
                        Memory_cacheInv(pContext->intermediateBufs[i].buf,
                                pContext->intermediateBufs[i].bufSize);
                    }
                }
            }

            /*
             * Note we don't handle inOutBufs, as the IVIDDEC2BACK
             * interface doesn't require them.
             */

            /*
             * Note, there's no need to invalidate cache for
             * pOutArgs->decodedBuf bufs nor pOutArgs->displayBufs
             * bufs as the app doesn't provide OUT buffers to the
             * algorithm via these fields.
             */

            pOutArgs = &(msg->cmd.process.outArgs);

            /* make the process call */
            msg->visa.status = VIDDEC2BACK_process(handle,
                    &(msg->cmd.process.context), pOutArgs);

            if (SKEL_cachingPolicy == SKEL_WBINVALL) {
                Memory_cacheWbInvAll();
            }
            else if (SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB) {
                /*
                 * Writeback cache for all output buffers:
                 *   - .decodedBufs
                 *   - .displayBufs
                 *   - .mbDataBuf
                 */
                for (i = 0; (i < pOutArgs->decodedBufs.numBufs) &&
                         (i < IVIDEO_MAX_YUV_BUFFERS); i++) {
                    if ((pOutArgs->decodedBufs.bufDesc[i].buf != NULL) &&
                            (XDM_ISACCESSMODE_WRITE(
                                pOutArgs->decodedBufs.bufDesc[i].accessMask))) {
                        Memory_cacheWb(pOutArgs->decodedBufs.bufDesc[i].buf,
                                pOutArgs->decodedBufs.bufDesc[i].bufSize);
                    }

                    /*
                     * Since we've cacheWb this buffer, we arguably should
                     * reflect this cache state and clear the WRITE bit in
                     * the .accessMask field.  However, we know the stub
                     * doesn't propogate this field to the calling app, so
                     * this extra buffer management detail isn't necessary:
                     *
                     * XDM_CLEARACCESSMODE_WRITE(
                     *         outArgs->decodedBufs.bufDesc[i].accessMask);
                     */
                }

                for (i = 0;
                     (pOutArgs->outputID[i] != 0) && (i < IVIDDEC2_MAX_IO_BUFFERS);
                     i++) {
                    for (j = 0; j < pOutArgs->displayBufs[i].numBufs; j++) {
                        if ((pOutArgs->displayBufs[i].bufDesc[j].buf != NULL) &&
                                (XDM_ISACCESSMODE_WRITE(
                                    pOutArgs->displayBufs[i].bufDesc[j].accessMask))) {

                            Memory_cacheWb(pOutArgs->displayBufs[i].bufDesc[j].buf,
                                    pOutArgs->displayBufs[i].bufDesc[j].bufSize);

                            /*
                             * Since we've cacheWb this buffer, we arguably should
                             * reflect this cache state and clear the WRITE bit in
                             * the .accessMask field.  However, we know the stub
                             * doesn't propogate this field to the calling app, so
                             * this extra buffer management detail isn't necessary:
                             *
                             * XDM_CLEARACCESSMODE_WRITE(
                             *         outArgs->displayBufs.bufDesc[i].accessMask);
                             */
                        }
                    }
                }

                if ((pOutArgs->outputMbDataID != 0) &&
                        (pOutArgs->mbDataBuf.buf != NULL) &&
                        (XDM_ISACCESSMODE_WRITE(pOutArgs->mbDataBuf.accessMask))) {

                    Memory_cacheWb(pOutArgs->mbDataBuf.buf,
                            pOutArgs->mbDataBuf.bufSize);

                    /*
                     * Since we've cacheWb this buffer, we arguably should
                     * reflect this cache state and clear the WRITE bit in
                     * the .accessMask field.  However, we know the stub
                     * doesn't propogate this field to the calling app, so
                     * this extra buffer management detail isn't necessary:
                     *
                     * XDM_CLEARACCESSMODE_WRITE(outArgs->mbDataBuf.accessMask);
                     */
                }
            }

            /*
             * Note that any changes to individual outBufs[i] values made by
             * the codec will automatically update msg->cmd.process.outBufs
             * as we pass the outBufs array by reference.
             */

            break;
        }

        case _VIDDEC2BACK_CCONTROL: {
            /* unmarshall status based on the "size" of params */
            pStatus = &(msg->cmd.control.status);

#if 0
            /* invalidate data buffer */
            if (pStatus->data.buf != NULL) {
                Memory_cacheInv(pStatus->data.buf, pStatus->data.bufSize);
            }
#endif
            msg->visa.status = VIDDEC2BACK_control(handle,
                    &(msg->cmd.control.context), pStatus);

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
 *  ======== VIDDEC2BACK_SKEL ========
 */
SKEL_Fxns VIDDEC2BACK_SKEL = {
    call,
    (SKEL_CREATEFXN)&VIDDEC2BACK_create,
    (SKEL_DESTROYFXN)&VIDDEC2BACK_delete,
};
/*
 *  @(#) ti.sdo.ce.video2.split; 1, 0, 0,165; 12-2-2010 21:28:42; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

