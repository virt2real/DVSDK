/*
 * dvtbMP3BaseDec1.h
 *
 * XDM1.0 MP3Base Decode Interface
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

#ifndef _DVEVM_ST_MP3BASE_DEC1_H
#define _DVEVM_ST_MP3BASE_DEC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/audio1/auddec1.h>

#define MP3BASEDEC1_PCM_WIDTH           16

#define MP3BASEDEC1_INBUF_SIZE          25600 //For normal audio decoding (1648), For wma decoding 25600
#define MP3BASEDEC1_OUTBUF_SIZE         16384 //For normal audio decoding (8192), For wma decoding 16384
typedef struct
{
	char adecName[MAX_NAME_LEN];
	AUDDEC1_Params adecParams;

	AUDDEC1_Cmd adecCmd;
	AUDDEC1_DynamicParams adecDynParams;
	AUDDEC1_Status adecStatus;
	AUDDEC1_InArgs adecInArgs;
	AUDDEC1_OutArgs adecOutArgs;

	int inFrameSize;
	int decFrameSize;
	unsigned int pEnable;
	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;

	Engine_Handle ceHdl;
	AUDDEC1_Handle adecHdl;
} DvevmStMP3BaseDec1Info;

DvevmStRetCode
dvtb_mp3baseDec1Init(DvevmStMP3BaseDec1Info *ad);

DvevmStRetCode
dvtb_mp3baseDec1Decode(DvevmStMP3BaseDec1Info *ad, int *decDuration);

DvevmStRetCode
dvtb_mp3baseDec1Control(DvevmStMP3BaseDec1Info *ad);

void
dvtb_mp3baseDec1Cleanup(DvevmStMP3BaseDec1Info *ad);

DvevmStRetCode
dvtb_mp3baseDec1Close(DvevmStMP3BaseDec1Info *ad);

#endif
