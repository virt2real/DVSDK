/*
 * dvtbAudEnc1.h
 *
 * DVTB(linux) XDM1.0 Audio Encoder Interface
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

#ifndef _DVEVM_ST_AUD_ENC1_H
#define _DVEVM_ST_AUD_ENC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/audio1/audenc1.h>

#define AUDENC1_MAX_SR              (64000) //(16000)
#define AUDENC1_BR                  (48000)
#define AUDENC1_SR                  (44100)
#define AUDENC1_MAX_BR              (192000)
#define AUDENC1_MODE                (0)
#define AUDENC1_BPS                 (16)
#define AUDENC1_DMONO               (0)
#define AUDENC1_CRC                 (0)
#define AUDENC1_ANC                 (1)
#define AUDENC1_LFE                 (0)
#define AUDENC1_MAX_CH              (2) //(1)
#define AUDENC1_MAX_BR              (192000)
#define AUDENC1_INBUF_SIZE          (8192)//(1648)//(4096)
#define AUDENC1_OUTBUF_SIZE         (3000)
#define AUDENC1_OUTBUF_SIZE         (3000)
#define DEFAULT_AUDENC1_TIME        (10)

#define AUDENC1_DMIX (0)
#define AUDENC1_OTYPE ( AACENC_OBJ_TYP_HEAAC )
#define AUDENC1_OFF   (AACENC_TT_ADTS)
#define AUDENC1_ARATE  (-1)
#define AUDENC1_BRM    (0)

typedef struct
{
	char audenc1Name[MAX_NAME_LEN];

	IAUDENC1_Params audenc1Params;
	IAUDENC1_Cmd audenc1Cmd;
	IAUDENC1_DynamicParams audenc1DynParams;
	IAUDENC1_Status audenc1Status;
	IAUDENC1_InArgs audenc1InArgs;
	IAUDENC1_OutArgs audenc1OutArgs;

	XDM1_BufDesc inBuf;
	XDM1_BufDesc outBuf;

	DvevmStBuffer ancBuf;

	Engine_Handle ceHdl;
	AUDENC1_Handle audenc1Hdl;

	unsigned int seconds; /* Number of seconds for audio capture */
	unsigned int outsamples;
	unsigned int insamples;
	unsigned int consumedInsamples;
	int InSamplesPerChannel;
	volatile int Framenum;
	int numChannels;

} DvevmStAudEnc1Info;

void
dvtb_audEnc1Cleanup(DvevmStAudEnc1Info *aenc1);

DvevmStRetCode
dvtb_audEnc1Init(DvevmStAudEnc1Info *aenc1);

DvevmStRetCode
dvtb_audEnc1Encode(DvevmStAudEnc1Info *aenc1, int *encDuration);

DvevmStRetCode
dvtb_audEnc1Control(DvevmStAudEnc1Info *aenc1);

DvevmStRetCode
dvtb_audEnc1Close(DvevmStAudEnc1Info *aenc1);

#endif
