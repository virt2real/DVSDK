/*
 * dvtbJPEGDec1.h
 *
 * XDM1.0 JPEG Decode Interface
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

#ifndef _DVEVM_ST_JPEG_DEC1_H
#define _DVEVM_ST_JPEG_DEC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/image1/imgdec1.h>
#include <ti/sdo/codecs/jpegdec/ijpegdec.h>

typedef struct
{
	char idec1Name[MAX_NAME_LEN]; // Codec Name

	IJPEGDEC_Params idec1Params; // Encoder parameters
	IIMGDEC1_Cmd idec1Cmd; // Codec control Command
	IJPEGDEC_DynamicParams idec1DynParams; // Dynamic Parameters
	IJPEGDEC_Status idec1Status; // Status of encode process
	IJPEGDEC_InArgs idec1InArgs;
	IJPEGDEC_OutArgs idec1OutArgs; // Output arguments

	DvevmStXdmBuffer inBuf; // Input XDM Buffer
	DvevmStXdmBuffer outBuf; // Output XDM Buffer
	XDM1_BufDesc inBufDesc;
	XDM1_BufDesc outBufDesc;

	Engine_Handle ceHdl; // Codec Engine Handle
	IMGDEC1_Handle idec1Hdl; // Encoder Handle

} DvevmStJpegDec1Info;

DvevmStRetCode
dvtb_jpegDec1Init(DvevmStJpegDec1Info *idec);

DvevmStRetCode
dvtb_jpegDec1Decode(DvevmStJpegDec1Info *idec, int *decDuration);

DvevmStRetCode
dvtb_jpegDec1Control(DvevmStJpegDec1Info *idec);

void
dvtb_jpegDec1Cleanup(DvevmStJpegDec1Info *jpeg1);

DvevmStRetCode
dvtb_jpegDec1Close(DvevmStJpegDec1Info *idec);

#endif
