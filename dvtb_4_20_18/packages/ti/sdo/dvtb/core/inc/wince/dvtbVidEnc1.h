/*
 * dvtbVidEnc1.h
 *
 * DVTB(wince) XDM1.0 Video Encoder Interface
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

#ifndef _DVEVM_ST_VID_ENC1_H
#define _DVEVM_ST_VID_ENC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/video1/videnc1.h>
#include "dvtbTime.h"

typedef struct
{
	char venc1Name[MAX_NAME_LEN];

	VIDENC1_Cmd venc1Cmd;
	VIDENC1_Params venc1Params;
	VIDENC1_DynamicParams venc1DynParams;
	VIDENC1_InArgs venc1InArgs;
	VIDENC1_OutArgs venc1OutArgs;
	VIDENC1_Status venc1Status;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;
	IVIDEO1_BufDescIn inBufDesc;
	XDM_BufDesc outBufDesc;

	Engine_Handle ceHdl;
	VIDENC1_Handle venc1Hdl;

	Time_Handle hTime;

	DvevmStBool skipFrame;
	int numFrames;
} DvevmStVidEnc1Info;

void
dvtb_vidEnc1XDM1SingleBufDescDebug(XDM1_SingleBufDesc *sbd);

void
dvtb_vidEnc1IVIDEO1_BufDescDebug(IVIDEO1_BufDesc *bd);

void
dvtb_vidEnc1InArgsDebug(VIDENC1_InArgs *vei);

DvevmStRetCode
dvtb_vidEnc1Init(DvevmStVidEnc1Info *ve);

DvevmStRetCode
dvtb_vidEnc1Encode(DvevmStVidEnc1Info *ve, int* encDuration);

DvevmStRetCode
dvtb_vidEnc1Control(DvevmStVidEnc1Info *ve);

void
dvtb_vidEnc1Cleanup(DvevmStVidEnc1Info *ve);

DvevmStRetCode
dvtb_vidEnc1Close(DvevmStVidEnc1Info *ve);

#endif
