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
 *  ======== _imgenc.h ========
 */
#ifndef ti_sdo_ce_image__IMGENC_
#define ti_sdo_ce_image__IMGENC_

#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/iimgenc.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _IMGENC_CPROCESS        0
#define _IMGENC_CCONTROL        1

/* msgq message to encode */
typedef struct {
    VISA_MsgHeader  visa;
    union {
        struct {
            /* must flatten the above structs b/c they contain pointers */
            XDAS_Int8          *inBufs[XDM_MAX_IO_BUFFERS];
            XDAS_Int32          numInBufs;
            XDAS_Int32          inBufSizes[XDM_MAX_IO_BUFFERS];

            XDAS_Int8          *outBufs[XDM_MAX_IO_BUFFERS];
            XDAS_Int32          numOutBufs;
            XDAS_Int32          outBufSizes[XDM_MAX_IO_BUFFERS];

            IIMGENC_InArgs  inArgs;

            /*
             * outArgs follows inArgs
             * IIMGENC_OutArgs     outArgs;
             *
             * Add a pad here for outArgs so we have a correct "minimum"
             * msg size.  The IPC framework may give us bigger msgs, so
             * we can handle variable sized extended fields, but this pad
             * ensures we get at least enough for base params.
             */
            UInt8               pad[sizeof(IIMGENC_OutArgs)];
        } process;
        struct {
            IIMGENC_Cmd            id;

            IIMGENC_DynamicParams  params;

            /*
             * status follows params
             * IIMGENC_Status      status;
             *
             * Similar to above, allow for a status-sized pad here.
             */
            UInt8               pad[sizeof(IIMGENC_Status)];
        } control;
    } cmd;
} _IMGENC_Msg;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.image; 1, 0, 3,352; 12-2-2010 21:23:57; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

