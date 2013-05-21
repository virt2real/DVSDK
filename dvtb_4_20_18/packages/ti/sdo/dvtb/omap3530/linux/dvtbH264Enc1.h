/*
 * dvtbH264Enc1.h
 *
 * XDM1.0 H264 Encode Interface
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

#ifndef _DVEVM_ST_H264_ENC1_H
#define _DVEVM_ST_H264_ENC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/video1/videnc1.h>
#define C6000
#include <ti/sdo/codecs/h264enc/ih264venc.h>

#define H264ENC1_MAX_WD           (720)
#define H264ENC1_MAX_HT           (576)
#define H264ENC1_MAX_FR           (30000)
#define H264ENC1_MAX_BR           2000000//((VIDENC1_MAX_FR) * (VIDENC1_MAX_HT) * (VIDENC1_MAX_WD) * 2)
#define H264ENC1_INTRA_FI         (30)
#define DEF_CAP_FRAMES           (30)

typedef struct
{
	char venc1Name[MAX_NAME_LEN];

	VIDENC1_Cmd venc1Cmd;
	IH264VENC_Params venc1Params;
	IH264VENC_DynamicParams venc1DynParams;
	IH264VENC_InArgs venc1InArgs;
	IH264VENC_OutArgs venc1OutArgs;
	IH264VENC_Status venc1Status;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;
	IVIDEO1_BufDescIn inBufDesc;
	XDM_BufDesc outBufDesc;

	Engine_Handle ceHdl;
	VIDENC1_Handle venc1Hdl;

	DvevmStBool skipFrame;
	int numFrames;
} DvevmStH264Enc1Info;

void
dvtb_h264Enc1XDM1SingleBufDescDebug(XDM1_SingleBufDesc *sbd);

void
dvtb_h264Enc1IVIDEO1_BufDescDebug(IVIDEO1_BufDesc *bd);

void
dvtb_h264Enc1InArgsDebug(IH264VENC_InArgs *vei);

void
dvtb_h264Enc1Cleanup(DvevmStH264Enc1Info *ve);

DvevmStRetCode
dvtb_h264Enc1Init(DvevmStH264Enc1Info *ve);

DvevmStRetCode
dvtb_h264Enc1Encode(DvevmStH264Enc1Info *ve, int* encDuration);

DvevmStRetCode
dvtb_h264Enc1Control(DvevmStH264Enc1Info *ve);

DvevmStRetCode
dvtb_h264Enc1Close(DvevmStH264Enc1Info *ve);

#endif

