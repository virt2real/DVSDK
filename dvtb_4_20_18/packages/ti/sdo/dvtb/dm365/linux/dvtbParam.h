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
#include "dvtbPreviewer.h"
#include "dvtbResizer.h"

//XDM 0.9 Base
//#include "dvtbSphEnc.h"
//#include "dvtbSphDec.h"

//XDM 1.0 Base
#include "dvtbVidEnc1.h"
#include "dvtbImgEnc1.h"
#include "dvtbImgDec1.h"
#include "dvtbSphEnc1.h"
#include "dvtbSphDec1.h"
#include "dvtbAudEnc1.h"
#include "dvtbAudDec1.h"


//XDM 1.0 Extended
#include "dvtbJPEGEnc1.h"
#include "dvtbJPEGDec1.h"
#include "dvtbH264Enc1.h"
#include "dvtbMPEG4Enc1.h"
#include "dvtbMPEG4HDVICPEnc1.h"
#include "dvtbMPEG2Enc1.h"
#include "dvtbAACHEDec1.h"
#include "dvtbMPEG2Enc1.h"
#include "dvtbAACHEEnc1.h"
#include "dvtbMP3Dec1.h"
#include "dvtbMP3Enc1.h"
#include "dvtbWMADec1.h"
#include "dvtbWMAEnc1.h"

//XDM 1.2 Base
#include "dvtbVidDec2.h"

//XDM 1.2 Extended
#include "dvtbH264Dec2.h"
#include "dvtbMPEG4Dec2.h"
#include "dvtbMPEG4HDVICPDec2.h"
#include "dvtbMPEG2Dec2.h"
#include "dvtbVC1Dec2.h"

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
	DvtbPreviewerInfo vpPrvw; // Previewer module for capture
	DvtbResizerInfo vpRsz; // Resizer module for capture

	//XDM 0.9 Base
//	DvevmStSphEncInfo senc; // Speech Encoder Info
//	DvevmStSphDecInfo sdec; // Speech Decoder Info

	//XDM 1.0 Base
	DvevmStVidEnc1Info venc1; // Video Encoder Info
	DvevmStImgEnc1Info ienc1; // Image Encoder Info
	DvevmStImgDec1Info idec1; // Image Decoder Info
	DvevmStSphEnc1Info senc1; // Speech Encoder Info
	DvevmStSphDec1Info sdec1; // Speech Decoder Info
	DvevmStAudEnc1Info aenc1; // Audio Encoder XDM 1.0 Info
	DvevmStAudDec1Info adec1; // Audio Decoder XDM 1.0 Info

	//XDM 1.0 Extended
	DvevmStJpegEnc1Info jpegenc1; // JPEG Encoder Info
	DvevmStJpegDec1Info jpegdec1; // JPEG Decoder Info
	DvevmStH264Enc1Info h264enc1; // H264 Encoder Info
	DvevmStMpeg4Enc1Info mpeg4enc1; // MPEG4 Encoder Info
	DvevmStMpeg4HDVICPEnc1Info mpeg4hdvicpenc1; // MPEG4 Encoder Info
	DvevmStAacheDec1Info aachedec1;   // AACHE Decoder XDM 1.0 Info
	DvevmStMpeg2Enc1Info mpeg2enc1; // MPEG2 Encoder Info
	DvevmStAacHeEnc1Info aacheenc1; // AAC HE Encoder XDM 1.0 Extended Parameter Info
	DvevmStMp3Dec1Info mp3dec1;   // MP3 Decoder XDM 1.0 
	DvevmStMp3Enc1Info mp3enc1; // MP3 Encoder XDM 1.0 Extended Parameter Info
	DvevmStWmaDec1Info wmadec1;   // WMA Decoder XDM 1.0 
	DvevmStWmaEnc1Info wmaenc1; // WMA Encoder XDM 1.0 Extended Parameter Info

	//XDM 1.2 Base
	DvevmStVidDec2Info vdec2; // Video Decoder Info

	//XDM 1.2 Extended
	DvevmStH264Dec2Info h264dec2; // H264 Video Decoder Info
	DvevmStMPEG4Dec2Info mpeg4dec2; // H264 Video Decoder Info
	DvevmStMPEG4HDVICPDec2Info mpeg4hdvicpdec2; // H264 Video Decoder Info
	DvevmStMPEG2Dec2Info mpeg2dec2; // Mpeg2 Decoder XDM 1.2 Extended ParameterInfo
	DvevmStVC1Dec2Info vc1dec2; // VC1 Decoder XDM 1.2 Extended ParameterInfo

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
