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
 *  ======== _sphdec.h ========
 */
#ifndef ti_sdo_ce_speech__SPHDEC_
#define ti_sdo_ce_speech__SPHDEC_

#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/isphdec.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _SPHDEC_CPROCESS        0
#define _SPHDEC_CCONTROL        1

/* msgq message to decode */
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

            ISPHDEC_InArgs      inArgs;     /* size def'd by 1st field */

            /*
             * outArgs follows inArgs
             * ISPHDEC_OutArgs     outArgs;
             *
             * Add a pad here for outArgs so we have a correct "minimum"
             * msg size.  The IPC framework may give us bigger msgs, so
             * we can handle variable sized extended fields, but this pad
             * ensures we get at least enough for base params.
             */
            UInt8               pad[sizeof(ISPHDEC_OutArgs)];
        } process;
        struct {
            ISPHDEC_Cmd            id;

            ISPHDEC_DynamicParams params;   /* size def'd by 1st field */

            /*
             * status follows params
             * ISPHDEC_Status      status;
             *
             * Similar to above, allow for a status-sized pad here.
             */
            UInt8               pad[sizeof(ISPHDEC_Status)];
        } control;
    } cmd;
} _SPHDEC_Msg;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.speech; 1, 0, 2,416; 12-2-2010 21:25:16; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

