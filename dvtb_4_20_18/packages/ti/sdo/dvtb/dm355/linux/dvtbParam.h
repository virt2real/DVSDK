/*
 * dvtbParam.h
 *
 * DVTB Handlers Initialization interface
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

#ifndef _DVEVM_ST_PARAM_H
#define _DVEVM_ST_PARAM_H

#include "dvtbGlobal.h"
#include "dvtbDefs.h"

//Drivers
#include "dvtbV4L2VPBE.h"
#include "dvtbV4L2VPFE.h"
#include "dvtbALSAAudio.h"

//XDM 0.9 Base
#include "dvtbSphEnc.h"
#include "dvtbSphDec.h"

//XDM 1.0 Base
#include "dvtbVidEnc1.h"
#include "dvtbImgEnc1.h"
#include "dvtbImgDec1.h"
#include "dvtbSphEnc1.h"
#include "dvtbSphDec1.h"

//XDM 1.0 Extended
#include "dvtbMPEG4SPEnc1.h"
#include "dvtbJPEGEnc1.h"
#include "dvtbJPEGDec1.h"

//XDM 1.2 Base
#include "dvtbVidDec2.h"

//XDM 1.2 Extended
#include "dvtbMPEG4SPDec2.h"

//Application Specific
#include "dvtbIPNCUC0Def.h"
#include "dvtbIPNCUC1Def.h"
#include "dvtbIPNCUC2Def.h"
#include "dvtbDVRUC0Def.h"
#include "dvtbDVREncDef.h"
#include "dvtbDVREncDecDef.h"

typedef enum
{
	DVEVM_ST_INT = 0,
	DVEVM_ST_STR,
	DVEVM_ST_CHAR,
	DVEVM_ST_SHORT,
	DVEVM_ST_INVALID
} DvevmStType;

typedef struct
{
	DvevmStEngineInfo eng; // Codec Engine Info

	//Drivers
	DvevmStVpbeInfo vpbe; // VPBE Driver Info
	DvevmStVpfeInfo vpfe; // VPFE Driver Info
	DvevmStAudioInfo aud; // Audio Driver Info

	//XDM 0.9 Base
	DvevmStSphEncInfo senc; // Speech Encoder Info
	DvevmStSphDecInfo sdec; // Speech Decoder Info

	//XDM 1.0 Base
	DvevmStVidEnc1Info venc1; // Video Encoder Info
	DvevmStImgEnc1Info ienc1; // Image Encoder Info
	DvevmStImgDec1Info idec1; // Image Decoder Info
	DvevmStSphEnc1Info senc1; // Speech Encoder Info
	DvevmStSphDec1Info sdec1; // Speech Decoder Info


	//XDM 1.0 Extended
	DvevmStMPEG4SPVEncInfo mpeg4spenc1; // MPEG4 SP Encoder Info
	DvevmStJpegEnc1Info jpegenc1; // JPEG Encoder Info
	DvevmStJpegDec1Info jpegdec1; // JPEG Decoder Info

	//XDM 1.2 Base
	DvevmStVidDec2Info vdec2; // Video Decoder Info

	//XDM 1.2 Extended
	DvevmStMPEG4SPDecInfo mpeg4spdec2; // MPEG4 SP Decoder Info

	//Application Specific
	DvevmStIPNCUC0Info IPNCUC0; // IPNC UC-0
	DvevmStIPNCUC1Info IPNCUC1; // IPNC UC-1
	DvevmStIPNCUC2Info IPNCUC2; // IPNC UC-2
	DvevmStDVRUC0Info DVRUC0; // DVR UC-0
	DvevmStDVREncInfo DVREnc; // DVR UC-1
	DvevmStDVREncDecInfo DVREncDec; // DVR UC-2

} DvevmStGlobalParams;

typedef struct
{
	char className[MAX_KEY_SIZE];
	char fieldName[MAX_NAME_LEN];
	DvevmStType fieldType;
	void *value;
	void *defaultValue;
} DvevmStMapTable;

extern unsigned int DVEVM_CODEC_NUM;

extern DvevmStMapTable *MAP;
extern DvevmStGlobalParams *G;

void
dvtb_initValues();

#endif
