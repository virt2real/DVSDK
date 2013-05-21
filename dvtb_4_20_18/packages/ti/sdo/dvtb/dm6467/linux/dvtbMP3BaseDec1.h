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

#define MP3BASEDEC1_MAX_SR              (48000)
#define MP3BASEDEC1_MAX_CH              (2)
#define MP3BASEDEC1_MAX_BR              (448000)//(MP3BASEDEC_MAX_SR*MP3BASEDEC_MAX_CH*4)  /* Assuming 16 bits per sample */
#define MP3BASEDEC1_INBUF_SIZE          (2048)//(4096)
#define MP3BASEDEC1_OUTBUF_SIZE         (8192)//(4608)
#define MP3BASEDEC1_PCM_WIDTH		   (16)

typedef struct
{
	char adecName[MAX_NAME_LEN];

	IAUDDEC1_Params adecParams;
	IAUDDEC1_Cmd adecCmd;
	IAUDDEC1_DynamicParams adecDynParams;
	IAUDDEC1_Status adecStatus;
	IAUDDEC1_InArgs adecInArgs;
	IAUDDEC1_OutArgs adecOutArgs;

	int inFrameSize;
	int decFrameSize;

	DvevmStBuffer inBuf;
	DvevmStBuffer outBuf;

	Engine_Handle ceHdl;
	AUDDEC1_Handle adecHdl;
} DvevmStMP3BaseDec1Info;

DvevmStRetCode
dvtb_mp3basedec1Init(DvevmStMP3BaseDec1Info *ad);

DvevmStRetCode
dvtb_mp3basedec1Decode(DvevmStMP3BaseDec1Info *ad, int *decDuration);

void
dvtb_mp3basedec1Cleanup(DvevmStMP3BaseDec1Info *ad);

DvevmStRetCode
dvtb_mp3basedec1Control(DvevmStMP3BaseDec1Info *ad);

DvevmStRetCode
dvtb_mp3basedec1Close(DvevmStMP3BaseDec1Info *ad);
#endif
