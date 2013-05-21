/*
 * dvtbMpeg4Dec2.h
 *
 * XDM1.2 MPEG4 Decode Interface
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

#ifndef _DVEVM_ST_MPEG4_DEC2_H
#define _DVEVM_ST_MPEG4_DEC2_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include "dvtbVidDec2.h"
#include <ti/sdo/ce/video2/viddec2.h>
#include <ti/sdo/codecs/mpeg4dec/imp4vdec.h>


#define MAX_MPEG4DEC2_OUTBUFS (1)
#define XDM_MAX_BUFFERS 17

typedef struct {
        int id;
        //char *bufs[2]; //One for Chroma and one for Luma
        //int bufSizes[2];
        DvevmStXdmBuffer buffer;
        DvevmStBool isFree;
} DvevmStMPEG4Dec2BufElement;


typedef struct {
	char vdec2Name[MAX_NAME_LEN];

	Imp4VDEC_Params vdec2Params;
	VIDDEC2_Cmd vdecCmd;
	Imp4VDEC_DynamicParams vdec2DynParams;
	Imp4VDEC_InArgs vdec2InArgs;
	Imp4VDEC_Status vdec2Status;
	Imp4VDEC_OutArgs vdec2OutArgs;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;
	XDM1_BufDesc inBufDesc;
	XDM_BufDesc outBufDesc;

	DvevmStMPEG4Dec2BufElement outBufArray[XDM_MAX_BUFFERS];

	Engine_Handle ceHdl;
	VIDDEC2_Handle vdec2Hdl;

	DvevmStBool skipFrame;
	int numFrames;
	int totBuf;
} DvevmStMPEG4DecInfo;

DvevmStRetCode
dvtb_mpeg4Dec2Init(DvevmStMPEG4DecInfo *vd);

DvevmStRetCode
dvtb_mpeg4Dec2Decode(DvevmStMPEG4DecInfo *vd,int *decDuration);

DvevmStRetCode
dvtb_mpeg4Dec2Control(DvevmStMPEG4DecInfo *vd);

void
dvtb_mpeg4Dec2Cleanup(DvevmStMPEG4DecInfo *vd);

DvevmStRetCode
dvtb_mpeg4Dec2Close(DvevmStMPEG4DecInfo *vd);

#endif
