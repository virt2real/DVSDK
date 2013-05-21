/*
 * dvtbAC3Play1Core.h
 *
 * Interfaces for XDM1.0 AC3 Decode related Core Functions
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

#ifndef _DVEVM_ST_AC3_PLAY1_CORE_H
#define _DVEVM_ST_AC3_PLAY1_CORE_H

#include "dvtbGlobal.h"
#include "dvtbAC3Dec1.h"
#include "dvtbALSAAudio.h"
#include "dvtbUtils.h"

void
dvtb_ac3Dec1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames);

void
dvtb_ac3Dec1InitPtrs(DvevmStAC3Dec1Info *ad);

DvevmStRetCode
dvtb_ac3Dec1HanInit(DvevmStAC3Dec1Info *ad, char *engName);

void
dvtb_ac3Dec1HanClose(DvevmStAC3Dec1Info *ad, char *engName);

DvevmStRetCode
dvtb_ac3Dec1DecProcess(DvevmStAC3Dec1Info *ad, int *decDuration);

DvevmStRetCode
dvtb_ac3WriteToThreeStereoFiles(XDAS_Int32 **ppData, XDAS_Int32 channelMode, FILE *fp1, FILE *fp2, FILE *fp3 , XDAS_Int32 samples, XDAS_Int32 bit_precision, XDAS_Int32 pcmFormat, XDAS_Int32 lfeFlag);

DvevmStRetCode
dvtb_ac3WriteToAStereoFile(XDAS_Int32 *pLeft, XDAS_Int32 *pRght, FILE *fp, XDAS_Int32 samples, XDAS_Int32 bit_precision, XDAS_Int32 pcmFormat, XDAS_Int32 numChans);

DvevmStRetCode
dvtb_ac3Dec1ProcessOutBuff(DvevmStAudioInfo *aud, DvevmStAC3Dec1Info *ad, DvevmStBool fileBased, char *buff, int nBytes, FILE *fp1, FILE *fp2, FILE *fp3);

#endif
