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
 *  ======== universal_skel.c ========
 *  This file contains the implemenation of the SKEL interface for the
 *  universal class of algorithms.
 *
 *  These functions are the "server-side" of the the stubs defined in
 *  universal_stubs.c
 */
#include <xdc/std.h>
#include <ti/sdo/ce/skel.h>
#include <ti/sdo/ce/osal/Memory.h>

#include "universal.h"
#include "_universal.h"

/*
 *  ======== call ========
 */
static VISA_Status call(VISA_Handle visaHandle, VISA_Msg visaMsg)
{
    _UNIVERSAL_Msg *msg  = (_UNIVERSAL_Msg *)visaMsg;
    UNIVERSAL_Handle handle = (UNIVERSAL_Handle)visaHandle;
    Int i;
    XDM1_BufDesc inBufs, *pInBufs = &inBufs;
    XDM1_BufDesc outBufs, *pOutBufs = &outBufs;
    XDM1_BufDesc inOutBufs, *pInOutBufs = &inOutBufs;
    IUNIVERSAL_OutArgs *pOutArgs;
    IUNIVERSAL_Status *pStatus;
    Int numBufs;

    /* perform the requested UNIVERSAL operation by parsing message. */
    switch (msg->visa.cmd) {

        case _UNIVERSAL_CPROCESS: {
            /* unmarshal buffers */
            if (msg->cmd.process.inBufs.numBufs == 0) {
                pInBufs = NULL;
            }
            else {
                inBufs = msg->cmd.process.inBufs;

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
                }
            }

            if (msg->cmd.process.outBufs.numBufs == 0) {
                pOutBufs = NULL;
            }
            else {
                outBufs = msg->cmd.process.outBufs;

                if (SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB) {
                    /* invalidate cache for all output buffers */
                    for (i = 0, numBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
                        if (outBufs.descs[i].buf != NULL) {
                            /* valid member of sparse array, manage it */
                            Memory_cacheInv(outBufs.descs[i].buf,
                                    outBufs.descs[i].bufSize);

                            if (++numBufs == outBufs.numBufs) {
                                break;
                            }
                        }
                    }
                }
            }

            if (msg->cmd.process.inOutBufs.numBufs == 0) {
                pInOutBufs = NULL;
            }
            else {
                inOutBufs = msg->cmd.process.inOutBufs;

                if (SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB) {
                    /* invalidate cache for all in/out buffers */
                    for (i = 0, numBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
                        if (inOutBufs.descs[i].buf != NULL) {
                            /* valid member of sparse array, manage it */
                            Memory_cacheInv(inOutBufs.descs[i].buf,
                                    inOutBufs.descs[i].bufSize);

                            if (++numBufs == inOutBufs.numBufs) {
                                break;
                            }
                        }
                    }
                }
            }

            /* unmarshall outArgs based on the "size" of inArgs */
            pOutArgs =
                (IUNIVERSAL_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
                        msg->cmd.process.inArgs.size);

            /* make the process call */
            msg->visa.status = UNIVERSAL_process(handle,
                    pInBufs, pOutBufs, pInOutBufs, &(msg->cmd.process.inArgs),
                    pOutArgs);

            if (SKEL_cachingPolicy == SKEL_WBINVALL) {
                Memory_cacheWbInvAll();
            }
            else if (SKEL_cachingPolicy == SKEL_LOCALBUFFERINVWB) {
                /* writeback cache for output buffers  */
                if (pOutBufs != NULL) {
                    for (i = 0, numBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
                        if (outBufs.descs[i].buf != NULL) {
                            if (XDM_ISACCESSMODE_WRITE(outBufs.descs[i]
                                        .accessMask)) {

                                /* valid member of sparse array, written via CPU */
                                Memory_cacheWb(outBufs.descs[i].buf,
                                        outBufs.descs[i].bufSize);

                                /*
                                 * Since we've cacheWb this buffer, we arguably
                                 * should reflect this cache state and clear the
                                 * WRITE bit in the .accessMask field.  However,
                                 * we know the stub doesn't propogate this field
                                 * to the calling app, so this extra buffer
                                 * management detail isn't necessary:
                                 *
                                 * XDM_CLEARACCESSMODE_WRITE(outBufs.descs[i]
                                 *         .accessMask);
                                 */
                            }

                            if (++numBufs == outBufs.numBufs) {
                                break;
                            }
                        }
                    }
                }

                if (pInOutBufs != NULL) {
                    /* writeback cache for in/out buffers  */
                    for (i = 0, numBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
                        if (inOutBufs.descs[i].buf != NULL) {
                            if (XDM_ISACCESSMODE_WRITE(inOutBufs.descs[i]
                                        .accessMask)) {
                        
                                /* valid member of sparse array, written via CPU */
                                Memory_cacheWb(inOutBufs.descs[i].buf,
                                        inOutBufs.descs[i].bufSize);

                                /*
                                 * Since we've cacheWb this buffer, we arguably
                                 * should reflect this cache state and clear the
                                 * WRITE bit in the .accessMask field.  However,
                                 * we know the stub doesn't propogate this field
                                 * to the calling app, so this extra buffer
                                 * management detail isn't necessary:
                                 *
                                 * XDM_CLEARACCESSMODE_WRITE(inOutBufs.descs[i]
                                 *         .accessMask);
                                 */
                            }

                            if (++numBufs == inOutBufs.numBufs) {
                                break;
                            }
                        }
                    }
                }
            }
            break;
        }

        case _UNIVERSAL_CCONTROL: {
            /* unmarshall status based on the "size" of dynParams */
            pStatus =
                (IUNIVERSAL_Status *)((UInt)(&(msg->cmd.control.dynParams)) +
                msg->cmd.control.dynParams.size);

            /* invalidate data buffers */
            for (i = 0, numBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
                if (pStatus->data.descs[i].buf != NULL) {
                    /* valid member of sparse array, manage it */
                    Memory_cacheInv(pStatus->data.descs[i].buf,
                            pStatus->data.descs[i].bufSize);

                    if (++numBufs == pStatus->data.numBufs) {
                        break;
                    }
                }
            }

            msg->visa.status = UNIVERSAL_control(handle, msg->cmd.control.id,
                    &(msg->cmd.control.dynParams), pStatus);

            /* writeback data buffers */
            for (i = 0, numBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
                if (pStatus->data.descs[i].buf != NULL) {
                    if (XDM_ISACCESSMODE_WRITE(pStatus->data.descs[i]
                            .accessMask)) {

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
                         * XDM_CLEARACCESSMODE_WRITE(pStatus->data.descs[i]
                         *         .accessMask);
                         */
                    }

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
 *  ======== UNIVERSAL_SKEL ========
 */
SKEL_Fxns UNIVERSAL_SKEL = {
    call,
    (SKEL_CREATEFXN)&UNIVERSAL_create,
    (SKEL_DESTROYFXN)&UNIVERSAL_delete,
};
/*
 *  @(#) ti.sdo.ce.universal; 1, 0, 0,141; 12-2-2010 21:27:56; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

