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
 *  ======== _scale.h ========
 */
#ifndef ti_sdo_ce_examples_extensions_scale__SCALE_H_
#define ti_sdo_ce_examples_extensions_scale__SCALE_H_

#include <ti/sdo/ce/visa.h>
#include <scale.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _SCALE_CPROCESS        0
#define _SCALE_CCONTROL        1

/* msgq message to decode */
typedef struct {
    VISA_MsgHeader  visa;
    union {
        struct {
            XDAS_Int8           *inBuf;
            XDAS_Int8           *outBuf;
            SCALE_InArgs        inArgs;
            SCALE_OutArgs       outArgs;
        } process;
        struct {
            SCALE_Cmd           id;
            SCALE_DynamicParams params;
        } control;
    } cmd;
} _SCALE_Msg;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.examples.extensions.scale; 1, 0, 0,261; 12-2-2010 21:23:31; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

