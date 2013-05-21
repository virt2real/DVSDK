/*
 * dvtbSphEnc1.h
 *
 * DVTB(wince) XDM1.0 Speech Encoder Interface
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

#ifndef _DVEVM_ST_SPH_ENC1_H
#define _DVEVM_ST_SPH_ENC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/speech1/sphenc1.h>
#include "dvtbTime.h"

#define SPHENC1_FRAME_SIZE      (80)

#define SPHENC1_CL               (1)
#define SPHENC1_PT               (0)
#define SPHENC1_VS               (0)
#define DEFAULT_SPHENC1_TIME     (10)

typedef struct {
	char sencName[MAX_NAME_LEN];
	unsigned int seconds; /* Number of seconds for audio capture */

	SPHENC1_Params sencParams;
	SPHENC1_Status sencStatus;
	SPHENC1_DynamicParams sencDynParams;
	SPHENC1_InArgs sencInArgs;
	SPHENC1_OutArgs sencOutArgs;

	DvevmStBuffer inBuf;
	DvevmStBuffer outBuf;

	Time_Handle hTime;

	Engine_Handle ceHdl;
	SPHENC1_Handle sencHdl;
} DvevmStSphEnc1Info;

DvevmStRetCode
dvtb_sphEnc1Init(DvevmStSphEnc1Info *se);

DvevmStRetCode
dvtb_sphEnc1Encode(DvevmStSphEnc1Info *se, int *encDuration);

DvevmStRetCode
dvtb_sphEnc1Control(DvevmStSphEnc1Info *se);

void
dvtb_sphEnc1Cleanup(DvevmStSphEnc1Info *se);

DvevmStRetCode
dvtb_sphEnc1Close(DvevmStSphEnc1Info *se);

#endif
