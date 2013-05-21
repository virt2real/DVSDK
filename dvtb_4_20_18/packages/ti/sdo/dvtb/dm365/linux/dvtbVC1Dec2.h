/*
 * dvtbVC1Dec2.h
 *
 * XDM1.2 VC1 Decode Interface
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

#ifndef _DVEVM_ST_VC1_DEC2_H
#define _DVEVM_ST_VC1_DEC2_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/video2/viddec2.h>
#include <ti/sdo/codecs/vc1dec/ivc1vdec.h>

#define IVC1VDEC_MAX_WD           (720)
#define IVC1VDEC_MAX_HT           (480)
#define IVC1VDEC_MAX_FR           (30000)
#define IVC1VDEC_MAX_BR           (10000000)//((IMP4VDEC_MAX_FR/1000) * (IMP4VDEC_MAX_HT) * (IMP4VDEC_MAX_WD) * 2)

typedef struct
{
	char vc1dec2Name[MAX_NAME_LEN];

	IVC1VDEC_Cmd vdec2Cmd;
	IVC1VDEC_Params vdec2Params;
	IVC1VDEC_DynamicParams vdec2DynParams;
	IVC1VDEC_InArgs vdec2InArgs;
	IVC1VDEC_OutArgs vdec2OutArgs;
	IVC1VDEC_Status vdec2Status;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;
	XDM1_BufDesc inBufDesc;
	XDM_BufDesc outBufDesc;

	DvevmStBufElement outBufArray[VIDDEC2_PLAY_MAX_BUFFERS];
	DvevmStOutBuffsInUse dispBufArray[VIDDEC2_PLAY_MAX_BUFFERS];
	int buffIdSearchStart;

	Engine_Handle ceHdl;
	IVC1VDEC_Handle vdec2Hdl;

	DvevmStBool skipFrame;
	int numFrames;
	int totBuf;
} DvevmStVC1Dec2Info;

DvevmStRetCode
dvtb_vc1Dec2Init(DvevmStVC1Dec2Info *vd);

DvevmStRetCode
dvtb_vc1Dec2Decode(DvevmStVC1Dec2Info *vd, int nFrames, int *decDuration);

DvevmStRetCode
dvtb_vc1Dec2Control(DvevmStVC1Dec2Info *vd);

void
dvtb_vc1Dec2Cleanup(DvevmStVC1Dec2Info *vd);

DvevmStRetCode
dvtb_vc1Dec2Close(DvevmStVC1Dec2Info *vd);

#endif
