/*
 * dvtbMPEG2Enc1.h
 *
 * XDM1.0 MPEG2 Encode Interface
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

#ifndef _DVEVM_ST_MPEG2_ENC1_H
#define _DVEVM_ST_MPEG2_ENC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/video1/videnc1.h>
#include <ti/sdo/codecs/mpeg2enc/imp2venc.h>

#define MPEG2ENC1_MAX_WD           (720)
#define MPEG2ENC1_MAX_HT           (480)
#define MPEG2ENC1_MAX_FR           (30000)
#define MPEG2ENC1_MAX_BR           2000000//((MPEG2ENC1_MAX_FR) * (MPEG2ENC1_MAX_HT) * (MPEG2ENC1_MAX_WD) * 2)
#define MPEG2ENC1_INTRA_FI         (30)
#define DEF_CAP_FRAMES           (30)
#define MPEG2ENC1_PACKET_BUF_SIZE  (400)

typedef struct
{
	char mpeg2enc1Name[MAX_NAME_LEN];

	IMP2VENC_Cmd venc1Cmd;
	IMP2VENC_Params venc1Params;
	IMP2VENC_DynamicParams venc1DynParams;
	IMP2VENC_InArgs venc1InArgs;
	IMP2VENC_OutArgs venc1OutArgs;
	IMP2VENC_Status venc1Status;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;
	IVIDEO1_BufDescIn inBufDesc;
	XDM_BufDesc outBufDesc;

	IMP2VENC_Handle venc1Hdl;
	Engine_Handle ceHdl;

	DvevmStBool skipFrame;
	int numFrames;
} DvevmStMpeg2Enc1Info;

DvevmStRetCode
dvtb_mpeg2Enc1Close(DvevmStMpeg2Enc1Info *ve);

void
dvtb_mpeg2Enc1IVIDEO1_BufDescDebug(IVIDEO1_BufDesc *bd);

void
dvtb_mpeg2Enc1XDM1SingleBufDescDebug(XDM1_SingleBufDesc *sbd);

void
dvtb_mpeg2Enc1IVIDEO1_BufDescDebug(IVIDEO1_BufDesc *bd);

void
dvtb_mpeg2Enc1InArgsDebug(IMP2VENC_InArgs *vei);

DvevmStRetCode
dvtb_mpeg2Enc1Init(DvevmStMpeg2Enc1Info *ve);

DvevmStRetCode
dvtb_mpeg2Enc1Encode(DvevmStMpeg2Enc1Info *ve, int* encDuration);

DvevmStRetCode
dvtb_mpeg2Enc1Control(DvevmStMpeg2Enc1Info *ve);

void
dvtb_mpeg2Enc1Cleanup(DvevmStMpeg2Enc1Info *ve);


#endif
