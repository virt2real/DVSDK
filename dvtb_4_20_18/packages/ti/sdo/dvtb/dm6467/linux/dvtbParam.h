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
#include "dvtbVdce.h"
#include "dvtbALSAAudio.h"

//XDM 0.9 Base
#include "dvtbAudEnc.h"
#include "dvtbAudDec.h"
#include "dvtbSphEnc.h"
#include "dvtbSphDec.h"

//XDM 0.9 Extended
#include "dvtbAACEnc.h"

//XDM 1.0 Base
#include "dvtbVidEnc1.h"
#include "dvtbMP3BaseDec1.h"
#include "dvtbSphEnc1.h"
#include "dvtbSphDec1.h"
#include "dvtbAudEnc1.h"
#include "dvtbAudDec1.h"
#include "dvtbImgDec1.h"
#include "dvtbImgEnc1.h"

//XDM 1.0 Extended
#include "dvtbH264fhdEnc1.h"
#include "dvtbMpeg4Enc1.h"
#include "dvtbAACHEDec1.h"
#include "dvtbH264Enc1.h"
#include "dvtbJPEGDec1.h"
#include "dvtbJPEGEnc1.h"

//XDM 1.2 Base
#include "dvtbVidDec2.h"

//XDM 1.2 Extended
#include "dvtbMpeg2Dec2.h"
#include "dvtbMpeg4Dec2.h"
#ifdef _DVTB_H264DEC_
#include "dvtbH264Dec2.h"
#endif
#ifdef _DVTB_H2641080p60VDEC_
#include "dvtbH2641080pDec2.h"
#endif

#ifdef _DVTB_NONTSPA_
//XDM 1.0 Extended
#include "dvtbAACHEEnc1.h"
#include "dvtbAC3Dec1.h"
#endif

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
	DvevmStAudioInfo aud; // Audio Driver Info
	DvevmStVpbeInfo vpbe; // VPBE Driver Info
	DvevmStVpfeInfo vpfe; // VPFE Driver Info
	DvevmStVdceInfo disvdce; // VDCE Driver Info for display
	DvevmStVdceInfo capvdce; // VDCE Driver Info for capture

	//XDM 0.9 Base
	DvevmStAudEncInfo aenc; // Audio Encoder XDM 0.9 Info
	DvevmStAudDecInfo adec; // Audio Decoder XDM 0.9 Info
	DvevmStSphEncInfo senc; // Speech Encoder XDM 0.9 Info
	DvevmStSphDecInfo sdec; // Speech Decoder XDM 0.9 Info

	//XDM 0.9 Extended
	DvevmStAACEncInfo aacenc; // AACLC 0.9 Audio Encoder Extended Parameter Info

	//XDM 1.0 Base
	DvevmStVidEnc1Info venc1; // Video Encoder XDM 1.0 Info
	DvevmStAudEnc1Info aenc1; // Audio Encoder XDM 1.0 Info
	DvevmStAudDec1Info adec1; // Audio Decoder XDM 1.0 Info
	DvevmStSphEnc1Info senc1; // Speech Encoder XDM 1.0 Info
	DvevmStSphDec1Info sdec1; // Speech Decoder XDM 1.0 Info
	DvevmStImgEnc1Info ienc1; // Image  Encoder Info
	DvevmStImgDec1Info idec1; // Image  Decoder Info
	DvevmStMP3BaseDec1Info mp3basedec1; // MP3    Decoder Info

	//XDM 1.0 Extended
	DvevmStH264Enc1Info h264enc1; // H264 XDM 1.0 Encoder Extended Parameter Info
	DvevmStH264fhdEnc1Info h264fhdenc1; // H264FHD XDM 1.0 Encoder Extended Parameter Info
	DvevmStMPEG4Enc1Info mpeg4enc1; // MPEG4 XDM 1.0 Encoder Extended Parameter Info
	DvevmStAacheDec1Info aachedec1;   // AACHE Decoder XDM 1.0 Info
	DvevmStJpegDec1Info jpegdec1; // JPEG   Decoder Info
	DvevmStJpegEnc1Info jpegenc1; // JPEG Encoder Info

	//XDM 1.2 Base
	DvevmStVidDec2Info vdec2; // Video Decoder XDM 1.2 Info

	//XDM 1.2 Extended
#ifdef _DVTB_H264DEC_
	DvevmStH264Dec2Info h264dec2; // H264 Decoder XDM 1.2 Extended ParameterInfo
#endif
#ifdef _DVTB_H2641080p60VDEC_
	DvevmStH2641080pDec2Info h2641080pdec2; // H2641080p Decoder XDM 1.2 Extended ParameterInfo
#endif
	DvevmStMpeg2Dec2Info mpeg2dec2; // Mpeg2 Decoder XDM 1.2 Extended ParameterInfo
	DvevmStMPEG4DecInfo mpeg4dec2; // Mpeg4 Decoder XDM 1.2 Extended ParameterInfo

#ifdef _DVTB_NONTSPA_
	//XDM 1.0 Extended
	DvevmStAacHeEnc1Info aacheenc1; // AAC HE Encoder XDM 1.0 Extended Parameter Info
	DvevmStAC3Dec1Info ac3dec1;   // AC3 Decoder XDM 1.0 Info
#endif

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

void dvtb_initValues();

#endif
