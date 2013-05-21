/*
 * dvtbVidDec2.h
 *
 * DVTB(linux) XDM1.0 Video Decoder Interface
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

#ifndef _DVEVM_ST_VID_DEC2_H
#define _DVEVM_ST_VID_DEC2_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include "dvtbDefs.h"
#include <ti/sdo/ce/video2/viddec2.h>


typedef struct
{
	char vdec2Name[MAX_NAME_LEN];

	VIDDEC2_Cmd vdec2Cmd;
	VIDDEC2_Params vdec2Params;
	VIDDEC2_DynamicParams vdec2DynParams;
	VIDDEC2_InArgs vdec2InArgs;
	VIDDEC2_OutArgs vdec2OutArgs;
	VIDDEC2_Status vdec2Status;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;
	XDM1_BufDesc inBufDesc;
	XDM_BufDesc outBufDesc;

	DvevmStBufElement outBufArray[VIDDEC2_PLAY_MAX_BUFFERS];
	DvevmStOutBuffsInUse dispBufArray[VIDDEC2_PLAY_MAX_BUFFERS];
	int buffIdSearchStart;

	Engine_Handle ceHdl;
	VIDDEC2_Handle vdec2Hdl;

	DvevmStBool skipFrame;
	DvevmStXdmBuffer firstBuffer;
	int numFrames;
	int totBuf;
	unsigned int pEnable;
} DvevmStVidDec2Info;

void
dvtb_vidDec2XDM1SingleBufDescDebug(XDM1_SingleBufDesc *sbd);

void
dvtb_vidDec2IVIDEO2_BufDescDebug(IVIDEO1_BufDesc *bd);

void
dvtb_vidDec2InitDebug(VIDDEC2_Params *vdp);

void
dvtb_vidDec2InArgsDebug(VIDDEC2_InArgs *vdi);

void
dvtb_vidDec2OutArgsDebug(VIDDEC2_OutArgs *vdo);

void
dvtb_vidDec2ControlDebug(VIDDEC2_Status *vds);

void
dvtb_vidDec2Cleanup(DvevmStVidDec2Info *vd);

DvevmStRetCode
dvtb_vidDec2Init(DvevmStVidDec2Info *vd);

DvevmStRetCode
dvtb_vidDec2Decode(DvevmStVidDec2Info *vd, int *decDuration);

DvevmStRetCode
dvtb_vidDec2Control(DvevmStVidDec2Info *vd);

DvevmStRetCode
dvtb_vidDec2Close(DvevmStVidDec2Info *vd);

#endif
