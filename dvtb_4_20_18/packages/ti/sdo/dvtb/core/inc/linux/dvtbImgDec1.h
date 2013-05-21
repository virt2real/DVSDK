/*
 * dvtbImgDec1.h
 *
 * DVTB(linux) XDM1.0 Image Decoder Interface
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

#ifndef _DVEVM_ST_IMG_DEC1_H
#define _DVEVM_ST_IMG_DEC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/image1/imgdec1.h>

typedef struct
{
	char idec1Name[MAX_NAME_LEN];

	IMGDEC1_Params idec1Params;
	IMGDEC1_Cmd idec1Cmd;
	IMGDEC1_DynamicParams idec1DynParams;
	IMGDEC1_InArgs idec1InArgs;
	IMGDEC1_OutArgs idec1OutArgs;
	IMGDEC1_Status idec1Status;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;

	Engine_Handle ceHdl;
	IMGDEC1_Handle idec1Hdl;

	DvevmStRetCode (*dvtb_ptrAllocCmem)(DvevmStXdmBuffer *xdmbuff);
	DvevmStRetCode (*dvtb_ptrFreeCmem)(DvevmStXdmBuffer *xdmbuf);

} DvevmStImgDec1Info;

DvevmStRetCode
dvtb_imgDec1Init(DvevmStImgDec1Info *idec);

DvevmStRetCode
dvtb_imgDec1Decode(DvevmStImgDec1Info *idec, int *decDuration);

DvevmStRetCode
dvtb_imgDec1Control(DvevmStImgDec1Info *idec);

void
dvtb_imgDec1Cleanup(DvevmStImgDec1Info *idec);

DvevmStRetCode
dvtb_imgDec1Close(DvevmStImgDec1Info *idec);

#endif
