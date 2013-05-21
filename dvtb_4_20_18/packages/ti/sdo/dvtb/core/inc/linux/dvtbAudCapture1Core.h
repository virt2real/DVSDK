/*
 * dvtbAudCapture1Core.h
 *
 * Interfaces for DVTB(linux) XDM1.0 Audio Encode related Core Functions
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef _DVEVM_ST_AUD_CAPTURE1_CORE_H
#define _DVEVM_ST_AUD_CAPTURE1_CORE_H

#include "dvtbGlobal.h"
#include "dvtbAudEnc1.h"
#include "dvtbALSAAudio.h"

void
dvtb_audEnc1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int seconds);

void
dvtb_audEnc1InitPtrs(DvevmStAudEnc1Info *aenc1);

DvevmStRetCode
dvtb_audEnc1HanInit(DvevmStAudEnc1Info *aenc1, char *engName);

void
dvtb_audEnc1HanClose(DvevmStAudEnc1Info *aenc1, char *engName);

DvevmStRetCode
dvtb_audEnc1EncProcess(DvevmStAudEnc1Info *aenc1, int *encDuration);

DvevmStRetCode
dvtb_audEnc1ReadInput(DvevmStAudioInfo *aud, DvevmStAudEnc1Info *aenc1, FILE *fp, DvevmStBool fileBased, int *nBytes);

DvevmStRetCode
dvtb_audEnc1Flush(DvevmStAudEnc1Info *aenc1, int nBytes, int *encDuration);

DvevmStRetCode
dvtb_audEnc1numChannels(int channelMode, int *numChannels);


#endif
