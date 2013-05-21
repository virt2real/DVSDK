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
#include "_viddec2.h"

#include <ti/sdo/utils/trace/gt.h>

#define MEASURE_TIME 0

#if MEASURE_TIME
extern GT_Mask ti_sdo_ce_video2_VIDDEC2_curTrace;
#define CURTRACE ti_sdo_ce_video2_VIDDEC2_curTrace

#define TIME_START() (startTime = GT_curTime())

#define TIME_STOP0(format) \
         GT_1trace(CURTRACE, GT_4CLASS, format " elapsed time: %06d ticks\n", \
                GT_curTime() - startTime)

#define TIME_STOP1(format, arg0) \
         GT_2trace(CURTRACE, GT_4CLASS, format " elapsed time: %06d ticks\n", \
                arg0, GT_curTime() - startTime)

#define TIME_STOP2(format, arg0, arg1) \
         GT_3trace(CURTRACE, GT_4CLASS, format " elapsed time: %06d ticks\n", \
                arg0, arg1, GT_curTime() - startTime)

#define TIME_STOP3(format, arg0, arg1, arg2) \
         GT_4trace(CURTRACE, GT_4CLASS, format " elapsed time: %06d ticks\n", \
                arg0, arg1, arg2, GT_curTime() - startTime)

static UInt32 startTime;

#else

#define TIME_START()
#define TIME_STOP0(format)
#define TIME_STOP1(format, arg0)
#define TIME_STOP2(format, arg0, arg1)
#define TIME_STOP3(format, arg0, arg1, arg2)

#endif


/*
 *  ======== call ========
 */
static VISA_Status call(VISA_Handle visaHandle, VISA_Msg visaMsg)
{
    _VIDDEC2_Msg *msg  = (_VIDDEC2_Msg *)visaMsg;
    VIDDEC2_Handle handle = (VIDDEC2_Handle)visaHandle;
    Int i, j;
    XDM1_BufDesc inBufs;
    XDM_BufDesc outBufs;
    IVIDDEC2_OutArgs *pOutArgs;
    IVIDDEC2_Status *pStatus;
    IVIDDEC2_CodecClassConfig *codecClassConfig;
    Int numBufs;

    /* get stub/skeleton config data; can be NULL (for old codecs) */
    codecClassConfig = (IVIDDEC2_CodecClassConfig *)
                        VISA_getCodecClassConfig( visaHandle );

    /* perform the requested VIDDEC2 operation by parsing message. */
    switch (msg->visa.cmd) {

        case _VIDDEC2_CPROCESS: {
            /* unmarshall inBufs and outBufs */
            inBufs           = msg->cmd.process.inBufs;

            outBufs.bufs     = msg->cmd.process.outBufs;
            outBufs.numBufs  = msg->cmd.process.numOutBufs;
            outBufs.bufSizes = msg->cmd.process.outBufSizes;

            if (SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB) {
                /* invalidate cache for all input buffers */
                for (i = 0, numBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
                    if (inBufs.descs[i].buf != NULL) {
                        /* valid member of sparse array,
                         * invalidate it unless user configured it not to
                         */
                        if (codecClassConfig != NULL &&
                                codecClassConfig->manageInBufsCache[i] == FALSE) {
                            /* do nothing, i.e. don't invalidate */
                        } else {
                            TIME_START();
                            Memory_cacheInv(inBufs.descs[i].buf,
                                    inBufs.descs[i].bufSize);
                            TIME_STOP2("inBuf[%d] (size: %07d) pre-process "
                                    "cache inv", i, inBufs.descs[i].bufSize);
                        }

                        if (++numBufs == inBufs.numBufs) {
                            break;
                        }
                    }
                }

                /* invalidate cache for all output buffers */
                for (i = 0, numBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
                    if (outBufs.bufs[i] != NULL) {
                        /* valid member of sparse array,
                         * invalidate it unless user configured it not to
                         */
                        if (codecClassConfig != NULL &&
                                codecClassConfig->manageOutBufsCache[i] == FALSE) {
                            /* do nothing, i.e. don't invalidate */
                        } else {
                            TIME_START();
                            Memory_cacheInv(outBufs.bufs[i], outBufs.bufSizes[i]);
                            TIME_STOP2("outBufs[%d] (size: %07d) pre-process "
                                       "cache inv", i, outBufs.bufSizes[i]);
                        }

                        if (++numBufs == outBufs.numBufs) {
                            break;
                        }
                    }
                }
            }

            /* unmarshall outArgs based on the "size" of inArgs */
            pOutArgs = (IVIDDEC2_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
                msg->cmd.process.inArgs.size);

            /*
             * Note, there's no need to invalidate cache for
             * pOutArgs->decodedBuf bufs nor pOutArgs->displayBufs
             * bufs as the app doesn't provide OUT buffers to the
             * algorithm via these fields.
             */

            /* make the process call */
            TIME_START();
            msg->visa.status = VIDDEC2_process(handle,
                &inBufs, &outBufs, &(msg->cmd.process.inArgs), pOutArgs);
            TIME_STOP0("process()");

            if (SKEL_cachingPolicy == SKEL_WBINVALL) {
                TIME_START();
                Memory_cacheWbInvAll();
                TIME_STOP0("post-process cache wbInvAll");
            }
            else if (SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB) {
                /*
                 * We probably should only be doing this if msg->visa.status
                 * is IVIDDEC2_EOK or _EFAIL and .extendedError is non-fatal.
                 */

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

                        TIME_START();
                        Memory_cacheWb(pOutArgs->decodedBufs.bufDesc[i].buf,
                                pOutArgs->decodedBufs.bufDesc[i].bufSize);
                        TIME_STOP2("decodedBuf[%d], size %07d, post-process "
                                "cache wb", i,
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

                for (i = 0; (pOutArgs->outputID[i] != 0) && (i < IVIDDEC2_MAX_IO_BUFFERS); i++) {
                    for (j = 0; j < pOutArgs->displayBufs[i].numBufs; j++) {
                        if ((pOutArgs->displayBufs[i].bufDesc[j].buf != NULL) &&
                                (XDM_ISACCESSMODE_WRITE(pOutArgs->displayBufs[i].bufDesc[j].accessMask))) {

                            TIME_START();
                            Memory_cacheWb(pOutArgs->displayBufs[i].bufDesc[j].buf,
                                    pOutArgs->displayBufs[i].bufDesc[j].bufSize);
                            TIME_STOP3("displayBufs[%d][%d], size %07d, post-process "
                                    "cache wb", i, j,
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

                    TIME_START();
                    Memory_cacheWb(pOutArgs->mbDataBuf.buf,
                            pOutArgs->mbDataBuf.bufSize);
                    TIME_STOP1("mbDataBuf, size %07d, post-process "
                               "cache wb", pOutArgs->mbDataBuf.bufSize);

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

        case _VIDDEC2_CCONTROL: {
            /* unmarshall status based on the "size" of params */
            pStatus = (IVIDDEC2_Status *)((UInt)(&(msg->cmd.control.params)) +
                msg->cmd.control.params.size);

            /* invalidate data buffer */
            if (pStatus->data.buf != NULL) {
                Memory_cacheInv(pStatus->data.buf, pStatus->data.bufSize);
            }

            msg->visa.status = VIDDEC2_control(handle, msg->cmd.control.id,
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
 *  ======== VIDDEC2_SKEL ========
 */
SKEL_Fxns VIDDEC2_SKEL = {
    call,
    (SKEL_CREATEFXN)&VIDDEC2_create,
    (SKEL_DESTROYFXN)&VIDDEC2_delete,
};
/*
 *  @(#) ti.sdo.ce.video2; 1, 0, 2,176; 12-2-2010 21:28:24; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

