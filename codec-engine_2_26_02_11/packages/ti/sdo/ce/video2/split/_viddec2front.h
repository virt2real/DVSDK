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
 *  ======== _viddec2.h ========
 */
#ifndef ti_sdo_ce_video2__VIDDEC2_
#define ti_sdo_ce_video2__VIDDEC2_

#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/ividdec2.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _VIDDEC2FRONT_CPROCESS        0
#define _VIDDEC2FRONT_CCONTROL        1

/* msgq message to decode */
typedef struct {
    VISA_MsgHeader  visa;
    union {
        struct {
            XDM_Context          context;

            IVIDDEC2_InArgs      inArgs;     /* size def'd by 1st field */

            /*
             * outArgs follows inArgs
             * IVIDDEC2FRONT_OutArgs     outArgs;
             *
             * Add a pad here for outArgs, plus "extended args".
             * But, how big is "big enough"?!?  We'll guess 2kB, as the default
             * Link msg size is 4kB.
             */
            UInt8               pad[2096];
        } process;
        struct {
            IVIDDEC2_Cmd             id;

            XDM_Context              context;

            IVIDDEC2_DynamicParams params;   /* size def'd by 1st field */

            /*
             * status follows params
             * IVIDDEC2FRONT_Status      status;
             *
             * Similar to above, allow for a 2kB pad here for status and
             * "extended args".
             */
            UInt8               pad[2096];
        } control;
    } cmd;
} _VIDDEC2FRONT_Msg;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.video2.split; 1, 0, 0,165; 12-2-2010 21:28:40; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

