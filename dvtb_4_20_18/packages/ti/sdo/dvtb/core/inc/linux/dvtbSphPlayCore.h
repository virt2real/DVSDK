/*
 * dvtbSphPlayCore.h
 *
 * DVTB(linux) XDM0.9 Speech Decode related Core Functions
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

#ifndef _DVEVM_ST_SPH_PLAY_CORE_H
#define _DVEVM_ST_SPH_PLAY_CORE_H

#include "dvtbSphDec.h"
#include "dvtbALSAAudio.h"

//Print "Number of speech frames" processed
void
dvtb_sphDecProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames);

//Initialize elements of structure DvevmStSphDecInfo
void
dvtb_sphDecInitPtrs(DvevmStSphDecInfo *sd);

//Initialize CE and codec instance
DvevmStRetCode
dvtb_sphDecHanInit(DvevmStSphDecInfo *sd, char *engName);

//Close codec instance and CE
void
dvtb_sphDecHanClose(DvevmStSphDecInfo *sd, char *engName);

//Decode speech frame
DvevmStRetCode
dvtb_sphDecDecProcess(DvevmStSphDecInfo *sd, int *decDuration);

//Either write output to file of play through driver
DvevmStRetCode
dvtb_sphDecProcessOutBuff(DvevmStAudioInfo *aud, FILE *fp, char *buff, int nBytes, DvevmStBool fileBased);

#endif
