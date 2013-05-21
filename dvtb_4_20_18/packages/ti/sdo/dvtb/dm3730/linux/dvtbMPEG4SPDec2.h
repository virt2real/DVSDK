/*
 * dvtbMPEG4SPDec2.h
 *
 * XDM1.2 MPEG4 SP Decode Interface
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

#ifndef _DVEVM_ST_MPEG4SP_DEC2_H
#define _DVEVM_ST_MPEG4SP_DEC2_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include "dvtbVidDec2.h"
#include <ti/sdo/ce/video2/viddec2.h>
#include <ti/sdo/codecs/mpeg4dec/impeg4vdec.h>


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

	IMPEG4VDEC_Params mpeg4sp_vdecParams;
	VIDDEC2_Cmd vdecCmd;
	IMPEG4VDEC_DynamicParams mpeg4sp_vdecDynParams;
	IMPEG4VDEC_InArgs mpeg4sp_vdecInArgs;
	IMPEG4VDEC_Status mpeg4sp_vdecStatus;
	IMPEG4VDEC_OutArgs mpeg4sp_vdecOutArgs;

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
} DvevmStMPEG4SPDecInfo;

DvevmStRetCode
dvtb_mpeg4spDec2Init(DvevmStMPEG4SPDecInfo *vd);

DvevmStRetCode
dvtb_mpeg4spDec2Decode(DvevmStMPEG4SPDecInfo *vd,int *decDuration);

DvevmStRetCode
dvtb_mpeg4spDec2Control(DvevmStMPEG4SPDecInfo *vd);

void
dvtb_mpeg4spDec2Cleanup(DvevmStMPEG4SPDecInfo *vd);

DvevmStRetCode
dvtb_mpeg4spDec2Close(DvevmStMPEG4SPDecInfo *vd);

#endif
