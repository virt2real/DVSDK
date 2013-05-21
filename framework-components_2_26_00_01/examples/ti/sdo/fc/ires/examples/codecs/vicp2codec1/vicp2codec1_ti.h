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
 *  ======== vicp2codec1_ti.h ========
 *  Interface for a dummy VICP2 codec example that uses an example IRES
 *  resource. This example exposes both an IVICP2CODEC1_Fxns interface and an
 *  IRES_Fxns interface.
 */
#ifndef VICP2CODEC1_TI_
#define VICP2CODEC1_TI_

#ifdef __cplusplus
extern "C" {
#endif

#include "ivicp2codec1.h"

/*
 *  ======== VICP2CODEC1_TI_CODECIRES ========
 *  Our implementation of the IVICP2CODEC1 interface
 */
extern IVICP2CODEC1_Fxns VICP2CODEC1_TI_CODECIRES;

/*
 *  ======== VICP2CODEC1_TI_IRES ========
 *  Our implementation of the IRES_Fxns interface
 */
extern IRES_Fxns VICP2CODEC1_TI_IRES;


/*
 *  ======== VICP2CODEC1_TI_PARAMS ========
 */
extern IVICP2CODEC1_Params VICP2CODEC1_TI_PARAMS;


#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.vicp2codec1; 1, 0, 0,32; 12-1-2010 17:25:11; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

