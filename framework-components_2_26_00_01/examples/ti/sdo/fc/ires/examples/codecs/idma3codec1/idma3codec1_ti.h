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
 *  ======== idma3codec1_ti.h ========
 *  Interface for the audio decoder copy example that uses an example IDMA3
 *  resource. This example exposes both an IIDMA3CODEC1_Fxns interface and an
 *  IDMA3_Fxns interface.
 */
#ifndef IDMA3CODEC1_TI_
#define IDMA3CODEC1_TI_

#ifdef __cplusplus
extern "C" {
#endif

#include "iidma3codec1.h"

/*
 *  ======== IDMA3CODEC1_TI_CODECIRES ========
 *  Our implementation of the IIDMA3CODEC1 interface
 */
extern IIDMA3CODEC1_Fxns IDMA3CODEC1_TI_CODECIDMA3;

/*
 *  ======== IDMA3CODEC1_TI_IDMA3 ========
 *  Our implementation of the IDMA3_Fxns interface
 */
extern IDMA3_Fxns IDMA3CODEC1_TI_IDMA3;


/*
 *  ======== IDMA3CODEC1_TI_PARAMS ========
 */
extern IIDMA3CODEC1_Params IDMA3CODEC1_TI_PARAMS;


#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.idma3codec1; 1, 0, 0,19; 12-1-2010 17:25:08; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

