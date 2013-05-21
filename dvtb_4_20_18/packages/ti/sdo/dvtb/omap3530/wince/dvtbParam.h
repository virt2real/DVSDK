/*
 * dvtbParam.h
 *
 * DVTB Handlers Initialization interfaces
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
//#include "dvtbALSAAudio.h"
//#include "dvtbV4L2VPBE.h"
//#include "dvtbV4L2VPBEFeatures.h"

//XDM 0.9 Base

//XDM 1.0 Base
#include "dvtbAudDec1.h"
#include "dvtbMP3BaseDec1.h"
#include "dvtbImgDec1.h"
#include "dvtbVidEnc1.h"
#include "dvtbImgEnc1.h"
#include "dvtbSphEnc1.h"
#include "dvtbSphDec1.h"

//XDM 1.0 Extended
#include "dvtbJPEGDec1.h"

//XDM 1.2 Base
#include "dvtbVidDec2.h"

//XDM 1.2 Extended

//Application Specific
//#include "dvtbPwrManager.h"

typedef enum
{
	DVEVM_ST_INT = 0,
	DVEVM_ST_SHORT,
	DVEVM_ST_STR,
	DVEVM_ST_CHAR,
	DVEVM_ST_INVALID
} dvtbType;

typedef struct
{
	DvevmStEngineInfo eng; // Codec  Engine Info

	//Drivers
//	DvevmStAudioInfo aud; // Audio  Driver Info
//	DvevmStVpbeInfo vpbe; // VPBE   Driver Info

	//XDM 1.0 Base
	DvevmStAudDec1Info adec1; // Audio  Decoder Info
	DvevmStImgDec1Info idec1; // Image  Decoder Info
	DvevmStSphEnc1Info senc1; // Speech Encoder Info
	DvevmStSphDec1Info sdec1; // Speech Decoder Info
	DvevmStVidEnc1Info venc1; // Video  Encoder Info
	DvevmStImgEnc1Info ienc1; // Image  Encoder Info
	DvevmStMP3BaseDec1Info mp3basedec1; // MP3    Decoder Info

	//XDM 1.0 Extended
	DvevmStJpegDec1Info jpegdec1; // JPEG   Decoder Info

	//XDM 1.2 Base
	DvevmStVidDec2Info viddec2; // Video  Decoder Info

	//Application Specific
//	DvevmStPwrManagerInfo pmanager; // Power Manager

} DvevmStGlobalParams;

typedef struct
{
	char className[MAX_KEY_SIZE];
	char fieldName[MAX_NAME_LEN];
	dvtbType fieldType;
	void *value;
	void *defaultValue;
} dvtbMapTable;

extern unsigned int DVEVM_CODEC_NUM;

extern dvtbMapTable *MAP;
extern DvevmStGlobalParams *G;

void
dvtb_initValues();

#endif