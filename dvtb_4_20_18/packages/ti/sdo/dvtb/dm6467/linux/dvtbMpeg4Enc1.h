/*
 * dvtbMpeg4Enc1.h
 *
 * XDM1.0 MPEG4 Encode Interface
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

#ifndef _DVEVM_ST_MPEG4_ENC1_H
#define _DVEVM_ST_MPEG4_ENC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/video1/videnc1.h>
#include <ti/sdo/codecs/mpeg4enc/impeg4enc.h>

#define MPEG4ENC1_MAX_WD           (720)
#define MPEG4ENC1_MAX_HT           (576)
#define MPEG4ENC1_MAX_FR           (30000)
#define MPEG4ENC1_MAX_BR           2000000//((VIDENC1_MAX_FR) * (VIDENC1_MAX_HT) * (VIDENC1_MAX_WD) * 2)
#define MPEG4ENC1_INTRA_FI         (30)
#define DEF_CAP_FRAMES           (30)

typedef struct Motion_MBData
{
	short MVx;
	short MVy;
	unsigned int SAD;
}Motion_MBData;

typedef struct
{
	char venc1Name[MAX_NAME_LEN];

	VIDENC1_Cmd venc1Cmd;
	IMP4VENC_Params venc1Params;
	IMP4VENC_DynamicParams venc1DynParams;
	IMP4VENC_InArgs venc1InArgs;
	IMP4VENC_OutArgs venc1OutArgs;
	IMP4VENC_Status venc1Status;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;
	IVIDEO1_BufDescIn inBufDesc;
	XDM_BufDesc outBufDesc;

	Engine_Handle ceHdl;
	VIDENC1_Handle venc1Hdl;

	DvevmStBool skipFrame;
	int numFrames;
} DvevmStMPEG4Enc1Info;

void
dvtb_MPEG4Enc1XDM1SingleBufDescDebug(XDM1_SingleBufDesc *sbd);

void
dvtb_MPEG4Enc1IVIDEO1_BufDescDebug(IVIDEO1_BufDesc *bd);

void
dvtb_MPEG4Enc1InArgsDebug(IMP4VENC_InArgs *vei);

void
dvtb_MPEG4Enc1Cleanup(DvevmStMPEG4Enc1Info *ve);

DvevmStRetCode
dvtb_MPEG4Enc1Init(DvevmStMPEG4Enc1Info *ve);

DvevmStRetCode
dvtb_MPEG4Enc1Encode(DvevmStMPEG4Enc1Info *ve, int* encDuration);

DvevmStRetCode
dvtb_MPEG4Enc1Control(DvevmStMPEG4Enc1Info *ve);

DvevmStRetCode
dvtb_MPEG4Enc1Close(DvevmStMPEG4Enc1Info *ve);

#endif

