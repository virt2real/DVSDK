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
 * */
/*
 *  ======== edmacodec1_ti.h ========
 *  Interface for the audio decoder copy example that uses an example IRES
 *  resource. This example exposes both an IEDMACODEC1_Fxns interface and an
 *  IRES_Fxns interface.
 */
#ifndef EDMACODEC1_TI_
#define EDMACODEC1_TI_

#ifdef __cplusplus
extern "C" {
#endif

#include "iedmacodec1.h"

/*
 *  ======== EDMACODEC1_TI_CODECIRES ========
 *  Our implementation of the IEDMACODEC1 interface
 */
extern IEDMACODEC1_Fxns EDMACODEC1_TI_CODECIRES;

/*
 *  ======== EDMACODEC1_TI_IRES ========
 *  Our implementation of the IRES_Fxns interface
 */
extern IRES_Fxns EDMACODEC1_TI_IRES;


/*
 *  ======== EDMACODEC1_TI_PARAMS ========
 */
extern IEDMACODEC1_Params EDMACODEC1_TI_PARAMS;


#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.edmacodec1; 1, 0, 0,133; 12-1-2010 17:25:05; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

