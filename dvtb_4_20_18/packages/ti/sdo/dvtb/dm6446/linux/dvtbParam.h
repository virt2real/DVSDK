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
#include "dvtbV4L2VPBE.h"
#include "dvtbV4L2VPFE.h"
#include "dvtbALSAAudio.h"

//XDM 0.9 Base
#include "dvtbVidDec.h"
#include "dvtbVidEnc.h"
#include "dvtbAudDec.h"
#include "dvtbMP3BaseDec.h"
#include "dvtbSphEnc.h"
#include "dvtbSphDec.h"
#include "dvtbImgDec.h"
#include "dvtbImgEnc.h"
#include "dvtbAudEnc.h"

//XDM 1.0 Base
#include "dvtbVidEnc1.h"
#include "dvtbImgEnc1.h"
#include "dvtbImgDec1.h"
#include "dvtbAudEnc1.h"
#include "dvtbAudDec1.h"
#include "dvtbMP3BaseDec1.h"
#include "dvtbSphEnc1.h"
#include "dvtbSphDec1.h"

//XDM 1.0 Extended
#include "dvtbAACLCEnc1.h"
#include "dvtbAACHEEnc1.h"

//XDM 1.2 Base
#include "dvtbVidDec2.h"

typedef enum
{
	DVEVM_ST_INT = 0,
	DVEVM_ST_SHORT,
	DVEVM_ST_STR,
	DVEVM_ST_CHAR,
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
	DvevmStVidEncInfo venc; // Video Encoder Info
	DvevmStVidDecInfo vdec; // Video Decoder Info
	DvevmStAudDecInfo adec; // Audio Decoder Info
	DvevmStMP3BaseDecInfo mp3basedec; // MP3 Audio Decoder Info
	DvevmStSphEncInfo senc; // Speech Encoder Info
	DvevmStSphDecInfo sdec; // Speech Decoder Info
	DvevmStImgDecInfo idec; // Image Decoder Info
	DvevmStImgEncInfo ienc; // Image Encoder Info
	DvevmStAudEncInfo aenc; // Audio Encoder Info

	//XDM 1.0 Base
	DvevmStVidEnc1Info venc1; // Video Encoder Info
	DvevmStImgEnc1Info ienc1; // Image Encoder Info
	DvevmStImgDec1Info idec1; // Image Decoder Info
	DvevmStAudEnc1Info aenc1; // Audio Encoder Info
	DvevmStAudDec1Info adec1; // Audio Decoder Info
	DvevmStSphEnc1Info senc1; // Speech Encoder Info
	DvevmStSphDec1Info sdec1; // Speech Decoder Info

	//XDM 1.0 Extended
	DvevmStAacLcEnc1Info aaclcenc1; // AAC LC Audio Decoder Info
	DvevmStAacHeEnc1Info aacheenc1; // AAC HE Audio Encoder Info
	DvevmStMP3BaseDec1Info mp3basedec1; // MP3 Audio Decoder Info

	//XDM 1.2 Base
	DvevmStVidDec2Info vdec2; // Audio Decoder Info

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
