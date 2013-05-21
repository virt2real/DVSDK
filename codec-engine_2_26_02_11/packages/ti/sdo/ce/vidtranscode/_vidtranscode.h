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
 *  ======== _vidtranscode.h ========
 */
#ifndef ti_sdo_ce_vidtranscode__VIDTRANSCODE_
#define ti_sdo_ce_vidtranscode__VIDTRANSCODE_

#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/ividtranscode.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _VIDTRANSCODE_CPROCESS      0
#define _VIDTRANSCODE_CCONTROL      1

/* msgq message to encode */
typedef struct {
    VISA_MsgHeader visa;
    union {
        struct {
            XDM1_BufDesc            inBufs;

            /* must flatten outBufs struct b/c they contain pointers */
            XDAS_Int8              *outBufs[XDM_MAX_IO_BUFFERS];
            XDAS_Int32              numOutBufs;
            XDAS_Int32              outBufSizes[XDM_MAX_IO_BUFFERS];

            IVIDTRANSCODE_InArgs    inArgs;     /* size def'd by 1st field */

            /*
             * outArgs follows inArgs
             * IVIDTRANSCODE_OutArgs outArgs;
             *
             * Add a pad here for outArgs so we have a correct "minimum"
             * msg size.  The IPC framework may give us bigger msgs, so
             * we can handle variable sized extended fields, but this pad
             * ensures we get at least enough for base params.
             */
            UInt8                   pad[sizeof(IVIDTRANSCODE_OutArgs)];
        } process;
        struct {
            IVIDTRANSCODE_Cmd       id;

            IVIDTRANSCODE_DynamicParams dynParams;  /* sized by 1st field */

            /*
             * status follows params
             * IVIDTRANSCODE_Status status;
             *
             * Similar to above, allow for a status-sized pad here.
             */
            UInt8                   pad[sizeof(IVIDTRANSCODE_Status)];
        } control;
    } cmd;
} _VIDTRANSCODE_Msg;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.vidtranscode; 1, 0, 1,227; 12-2-2010 21:28:33; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

