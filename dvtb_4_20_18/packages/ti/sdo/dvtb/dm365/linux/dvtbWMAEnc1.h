/*
 * dvtbWMAEnc1.h
 *
 * XDM1.0 WMA Encode Interface
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

#ifndef _DVEVM_ST_WMA_ENC1_H
#define _DVEVM_ST_WMA_ENC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/xdais/dm/xdm.h>
#include <ti/sdo/ce/audio1/audenc1.h>

typedef struct ITTIAM_WMAENC_Params
{
	IAUDENC1_Params audenc_params;

	XDAS_Int32 iBitRate_var;
}ITTIAM_WMAENC_Params;

typedef struct ITTIAM_WMAENC_DynamicParams 
{
	IAUDENC1_DynamicParams audenc_dynamicparams;
}ITTIAM_WMAENC_DynamicParams;

typedef struct ITTIAM_WMAENC_Status
{
	IAUDENC1_Status  audenc_status;
	XDAS_UInt32 nMaxSamplesPerPacket; 
	XDAS_UInt32 nBlockAlign; 
	XDAS_UInt32 wEncodeOptions; 
	XDAS_Int32 iBitRateVar;
	XDAS_Int32 iFramesPerPacket; 
	XDAS_Int32 iSamplesPerFrame;
}ITTIAM_WMAENC_Status;

typedef struct ITTIAM_WMAENC_InArgs
{
	IAUDENC1_InArgs audenc_inArgs;
}ITTIAM_WMAENC_InArgs;

typedef struct ITTIAM_WMAENC_OutArgs 
{
	IAUDENC1_OutArgs audenc_outArgs;
	XDAS_Int32 i_exec_done; 
	XDAS_Int32 i_num_samples_in_packet;
}ITTIAM_WMAENC_OutArgs;

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
	ITTIAM_WMAENC_Params aenc1Params;
	ITTIAM_WMAENC_DynamicParams aenc1DynParams;
	ITTIAM_WMAENC_Status aenc1Status;
	ITTIAM_WMAENC_InArgs aenc1InArgs;
	ITTIAM_WMAENC_OutArgs aenc1OutArgs;
	XDM1_BufDesc inBuf;
	XDM1_BufDesc outBuf;

	DvevmStBuffer ancBuf;
	int consumedSamples;

	Engine_Handle ceHdl;
	AUDENC1_Handle aenc1Hdl;
} DvevmStWmaEnc1Info;

void
dvtb_wmaEnc1Cleanup(DvevmStWmaEnc1Info *ae);

DvevmStRetCode
dvtb_wmaEnc1Init(DvevmStWmaEnc1Info *ae);

DvevmStRetCode
dvtb_wmaEnc1Encode(DvevmStWmaEnc1Info *ae, int *encDuration);

DvevmStRetCode
dvtb_wmaEnc1Control(DvevmStWmaEnc1Info *ae);

DvevmStRetCode
dvtb_wmaEnc1Close(DvevmStWmaEnc1Info *ae);

#endif
