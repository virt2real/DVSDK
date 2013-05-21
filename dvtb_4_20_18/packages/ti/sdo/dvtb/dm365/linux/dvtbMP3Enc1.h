/*
 * dvtbMP3Enc1.c
 *
 * XDM1.0 MP3 Encode Interface
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

#ifndef _DVEVM_ST_MP3_ENC1_H
#define _DVEVM_ST_MP3_ENC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/xdais/dm/xdm.h>
#include <ti/sdo/ce/audio1/audenc1.h>

typedef struct ITTIAM_MP3ENC_Params
{
	IAUDENC1_Params audenc_params;

	XDAS_Int32 packet;
}ITTIAM_MP3ENC_Params;

typedef struct ITTIAM_MP3ENC_DynamicParams 
{
	IAUDENC1_DynamicParams audenc_dynamicparams;
}ITTIAM_MP3ENC_DynamicParams;

typedef struct ITTIAM_MP3ENC_Status
{
	IAUDENC1_Status  audenc_status;
}ITTIAM_MP3ENC_Status;

typedef struct ITTIAM_MP3ENC_InArgs
{
	IAUDENC1_InArgs audenc_inArgs;
}ITTIAM_MP3ENC_InArgs;

typedef struct ITTIAM_MP3ENC_OutArgs 
{
	IAUDENC1_OutArgs audenc_outArgs;
	XDAS_Int32 i_exec_done; 
	XDAS_Int32 i_ittiam_err_code;
}ITTIAM_MP3ENC_OutArgs;

typedef struct
{
	IAUDENC1_Cmd aenc1Cmd;
	char aenc1Name[MAX_NAME_LEN];
	unsigned int seconds; /* Number of seconds for audio capture */
	unsigned int outsamples;
	unsigned int insamples;
	volatile int Framenum;
	int framesize;
	int numChannels;
	ITTIAM_MP3ENC_Params aenc1Params;
	ITTIAM_MP3ENC_DynamicParams aenc1DynParams;
	ITTIAM_MP3ENC_Status aenc1Status;
	ITTIAM_MP3ENC_InArgs aenc1InArgs;
	ITTIAM_MP3ENC_OutArgs aenc1OutArgs;
	XDM1_BufDesc inBuf;
	XDM1_BufDesc outBuf;

	DvevmStBuffer ancBuf;

	Engine_Handle ceHdl;
	AUDENC1_Handle aenc1Hdl;
} DvevmStMp3Enc1Info;

void
dvtb_mp3Enc1Cleanup(DvevmStMp3Enc1Info *ae);

DvevmStRetCode
dvtb_mp3Enc1Init(DvevmStMp3Enc1Info *ae);

DvevmStRetCode
dvtb_mp3Enc1Encode(DvevmStMp3Enc1Info *ae, int *encDuration);

DvevmStRetCode
dvtb_mp3Enc1Control(DvevmStMp3Enc1Info *ae);

DvevmStRetCode
dvtb_mp3Enc1Close(DvevmStMp3Enc1Info *ae);

#endif
