/*
 * dvtbAC3Dec1.h
 *
 * XDM1.0 AC3 Decode Interface
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

#ifndef _DVEVM_ST_AC3_DEC1_H
#define _DVEVM_ST_AC3_DEC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include "dvtbDefs.h"
#include <ti/sdo/ce/audio1/auddec1.h>
#include <ti/sdo/codecs/dolbyac3dec/idolbyac3dec.h>

typedef struct
{
	char adecName[MAX_NAME_LEN];
	IDOLBYAC3DEC_Params adecParams;

	IAUDDEC1_Cmd adecCmd;
	IDOLBYAC3DEC_DynamicParams adecDynParams;
	IDOLBYAC3DEC_Status adecStatus;
	IDOLBYAC3DEC_InArgs adecInArgs;
	IDOLBYAC3DEC_OutArgs adecOutArgs;

	int desiredChannelMode;
	int inFrameSize;
	int decFrameSize;
	int lfeflag;
	int aux;
	int sourceDual;
	int sourceKaraoke;
	unsigned int pEnable;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;

	Engine_Handle ceHdl;
	AUDDEC1_Handle adecHdl;
} DvevmStAC3Dec1Info;

DvevmStRetCode
dvtb_ac3Dec1Init(DvevmStAC3Dec1Info *ad);

DvevmStRetCode
dvtb_ac3Dec1Decode(DvevmStAC3Dec1Info *ad, int *decDuration);

DvevmStRetCode
dvtb_ac3Dec1Control(DvevmStAC3Dec1Info *ad);

void
dvtb_ac3Dec1Cleanup(DvevmStAC3Dec1Info *ad);

DvevmStRetCode
dvtb_ac3Dec1Close(DvevmStAC3Dec1Info *ad);

#endif
