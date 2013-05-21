/*
 * dvtbAudDec.h
 *
 * XDM0.9 Audio Decode Interface
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

#ifndef _DVEVM_ST_AUD_DEC_H
#define _DVEVM_ST_AUD_DEC_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/audio/auddec.h>

#define AUDDEC_MAX_SR              48000//(96000)
#define AUDDEC_MAX_CH              (2)
#define AUDDEC_MAX_BR              384000//(AUDDEC_MAX_SR*AUDDEC_MAX_CH*4)  /* Assuming 16 bits per sample */
#define AUDDEC_INBUF_SIZE          25600 //For normal audio decoding (1648), For wma decoding 25600
#define AUDDEC_OUTBUF_SIZE         16384 //For normal audio decoding (8192), For wma decoding 16384
typedef struct
{
	char adecName[MAX_NAME_LEN];

	AUDDEC_Params adecParams;
	AUDDEC_Cmd adecCmd;
	AUDDEC_DynamicParams adecDynParams;
	AUDDEC_Status adecStatus;
	AUDDEC_InArgs adecInArgs;
	AUDDEC_OutArgs adecOutArgs;

	int inFrameSize;
	int decFrameSize;

	DvevmStBuffer inBuf;
	DvevmStBuffer outBuf;

	Engine_Handle ceHdl;
	AUDDEC_Handle adecHdl;
} DvevmStAudDecInfo;

DvevmStRetCode
dvtb_audDecInit(DvevmStAudDecInfo *ad);

DvevmStRetCode
dvtb_audDecDecode(DvevmStAudDecInfo *ad, int *decDuration);

void
dvtb_audDecCleanup(DvevmStAudDecInfo *ad);

DvevmStRetCode
dvtb_audDecControl(DvevmStAudDecInfo *ad);

DvevmStRetCode
dvtb_audDecClose(DvevmStAudDecInfo *ad);

#endif
