/*
 * dvtbApisDispatcher.c
 *
 * APIs Dispatcher
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

#include "dvtbApisDispatcher.h"
#include "dvtbParam.h"
#include "dvtbEngine.h"

//XDM 0.9 Base
//#include "dvtbSphDec.h"
//#include "dvtbSphEnc.h"

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

#define APIS_USAGE  SYS_ERROR("\nUsage: apis  <engine|videnc1|viddec1|imgenc1|imgdec1|sphenc1|sphdec1>\
    [open|mem|cpu|close|create|control|process|delete] \n");

DvevmStApiTable *API = NULL;
unsigned int DVEVM_CE_NUM = 0;

DvevmStRetCode
dvtb_apisInit()
{
	DvevmStApiTable dvevmStApiArr[] =
	{
		/*Api for Codec Engine*/
		{ "engine", "runtime", (DvevmStApiFunction) dvtb_ceRuntimeInit, &G->eng },
		{ "engine", "open", (DvevmStApiFunction) dvtb_ceOpen, &G->eng },
		{ "engine", "getmem", (DvevmStApiFunction) dvtb_ceMem, &G->eng },
		{ "engine", "getcpu", (DvevmStApiFunction) dvtb_ceCpu, &G->eng },
		{ "engine", "close", (DvevmStApiFunction) dvtb_ceClose, &G->eng },
		/************************************************************************************************/
		/***********     XDM 0.9 Base     ***************************************************************/
		/************************************************************************************************/
//		{"sphenc", "create", (DvevmStApiFunction) dvtb_sphEncInit, &G->senc},
//		{"sphenc", "process", (DvevmStApiFunction) dvtb_sphEncEncode, &G->senc},
//		{"sphenc", "control", (DvevmStApiFunction) dvtb_sphEncControl, &G->senc},
//		{"sphenc", "delete", (DvevmStApiFunction) dvtb_sphEncClose, &G->senc},
		
		/* Api for Speech Decoder */
//		{"sphdec", "create", (DvevmStApiFunction) dvtb_sphDecInit, &G->sdec},
//		{"sphdec", "process", (DvevmStApiFunction) dvtb_sphDecDecode, &G->sdec},
//		{"sphdec", "control", (DvevmStApiFunction) dvtb_sphDecControl, &G->sdec},
//		{"sphdec", "delete", (DvevmStApiFunction) dvtb_sphDecClose, &G->sdec},
		/************************************************************************************************/
		/***********     XDM 1.0 Base     ***************************************************************/
		/************************************************************************************************/
		/* Api for Video Encoder */
		{ "videnc1", "create", (DvevmStApiFunction) dvtb_vidEnc1Init, &G->venc1 },
		{ "videnc1", "process", (DvevmStApiFunction) dvtb_vidEnc1Encode, &G->venc1 },
		{ "videnc1", "control", (DvevmStApiFunction) dvtb_vidEnc1Control, &G->venc1 },
		{ "videnc1", "delete", (DvevmStApiFunction) dvtb_vidEnc1Close, &G->venc1 },
		/* Api for AAC HE 1.0 Base params Encoder */
		{ "audenc1", "create", (DvevmStApiFunction) dvtb_audEnc1Init, &G->aenc1 },
		{ "audenc1", "process", (DvevmStApiFunction) dvtb_audEnc1Encode, &G->aenc1 },
		{ "audenc1", "control", (DvevmStApiFunction) dvtb_audEnc1Control, &G->aenc1 },
		{ "audenc1", "delete", (DvevmStApiFunction) dvtb_audEnc1Close, &G->aenc1 },
		/* Api for Audio Decoder 1.0*/
		{ "auddec1", "create", (DvevmStApiFunction) dvtb_audDec1Init, &G->adec1 },
		{ "auddec1", "process", (DvevmStApiFunction) dvtb_audDec1Decode, &G->adec1 },
		{ "auddec1", "control", (DvevmStApiFunction) dvtb_audDec1Control, &G->adec1 },
		{ "auddec1", "delete", (DvevmStApiFunction) dvtb_audDec1Close, &G->adec1 },
		/* Api for Image Encoder */
		{ "imgenc1", "create", (DvevmStApiFunction) dvtb_imgEnc1Init, &G->ienc1 },
		{ "imgenc1", "process", (DvevmStApiFunction) dvtb_imgEnc1Encode, &G->ienc1 },
		{ "imgenc1", "control", (DvevmStApiFunction) dvtb_imgEnc1Control, &G->ienc1 },
		{ "imgenc1", "delete", (DvevmStApiFunction) dvtb_imgEnc1Close, &G->ienc1 },
		/* Api for Image Decoder */
		{ "imgdec1", "create", (DvevmStApiFunction) dvtb_imgDec1Init, &G->idec1 },
		{ "imgdec1", "process", (DvevmStApiFunction) dvtb_imgDec1Decode, &G->idec1 },
		{ "imgdec1", "control", (DvevmStApiFunction) dvtb_imgDec1Control, &G->idec1 },
		{ "imgdec1", "delete", (DvevmStApiFunction) dvtb_imgDec1Close, &G->idec1 },
		/* Api for Speech Encoder */
		{ "sphenc1", "create", (DvevmStApiFunction) dvtb_sphEnc1Init, &G->senc1 },
		{ "sphenc1", "process", (DvevmStApiFunction) dvtb_sphEnc1Encode, &G->senc1 },
		{ "sphenc1", "control", (DvevmStApiFunction) dvtb_sphEnc1Control, &G->senc1 },
		{ "sphenc1", "delete", (DvevmStApiFunction) dvtb_sphEnc1Close, &G->senc1 },
		/* Api for Speech Decoder */
		{ "sphdec1", "create", (DvevmStApiFunction) dvtb_sphDec1Init, &G->sdec1 },
		{ "sphdec1", "process", (DvevmStApiFunction) dvtb_sphDec1Decode, &G->sdec1 },
		{ "sphdec1", "control", (DvevmStApiFunction) dvtb_sphDec1Control, &G->sdec1 },
		{ "sphdec1", "delete", (DvevmStApiFunction) dvtb_sphDec1Close, &G->sdec1 },
		/************************************************************************************************/
		/************************************************************************************************/
		/***********     XDM 1.0 Extended     ***********************************************************/
		/************************************************************************************************/
		/* Api for JPEG Encoder XDM 1.0*/
		{ "jpegenc1", "create", (DvevmStApiFunction) dvtb_jpegEnc1Init, &G->jpegenc1 },
		{ "jpegenc1", "process", (DvevmStApiFunction) dvtb_jpegEnc1Encode, &G->jpegenc1 },
		{ "jpegenc1", "control", (DvevmStApiFunction) dvtb_jpegEnc1Control, &G->jpegenc1 },
		{ "jpegenc1", "delete", (DvevmStApiFunction) dvtb_jpegEnc1Close, &G->jpegenc1 },
		/* Api for JPEG Decoder XDM 1.0*/
		{ "jpegdec1", "create", (DvevmStApiFunction) dvtb_jpegDec1Init, &G->jpegdec1 },
		{ "jpegdec1", "process", (DvevmStApiFunction) dvtb_jpegDec1Decode, &G->jpegdec1 },
		{ "jpegdec1", "control", (DvevmStApiFunction) dvtb_jpegDec1Control, &G->jpegdec1 },
		{ "jpegdec1", "delete", (DvevmStApiFunction) dvtb_jpegDec1Close, &G->jpegdec1 },
		/* Api for H264 Video Encoder */
		{ "h264enc1", "create", (DvevmStApiFunction) dvtb_h264Enc1Init, &G->h264enc1 },
		{ "h264enc1", "process", (DvevmStApiFunction) dvtb_h264Enc1Encode, &G->h264enc1 },
		{ "h264enc1", "control", (DvevmStApiFunction) dvtb_h264Enc1Control, &G->h264enc1 },
		{ "h264enc1", "delete", (DvevmStApiFunction) dvtb_h264Enc1Close, &G->h264enc1 },
		/* Api for mpeg4 Video Encoder */
		{ "mpeg4enc1", "create", (DvevmStApiFunction) dvtb_mpeg4Enc1Init, &G->mpeg4enc1 },
		{ "mpeg4enc1", "process", (DvevmStApiFunction) dvtb_mpeg4Enc1Encode, &G->mpeg4enc1 },
		{ "mpeg4enc1", "control", (DvevmStApiFunction) dvtb_mpeg4Enc1Control, &G->mpeg4enc1 },
		{ "mpeg4enc1", "delete", (DvevmStApiFunction) dvtb_mpeg4Enc1Close, &G->mpeg4enc1 },
		/* Api for mpeg4 Video Encoder */
		{ "mpeg4hdvicpenc1", "create", (DvevmStApiFunction) dvtb_mpeg4HDVICPEnc1Init, &G->mpeg4hdvicpenc1 },
		{ "mpeg4hdvicpenc1", "process", (DvevmStApiFunction) dvtb_mpeg4HDVICPEnc1Encode, &G->mpeg4hdvicpenc1 },
		{ "mpeg4hdvicpenc1", "control", (DvevmStApiFunction) dvtb_mpeg4HDVICPEnc1Control, &G->mpeg4hdvicpenc1 },
		{ "mpeg4hdvicpenc1", "delete", (DvevmStApiFunction) dvtb_mpeg4HDVICPEnc1Close, &G->mpeg4hdvicpenc1 },
		/* Api for Mpeg2 Video Encoder */
		{ "mpeg2enc1", "create", (DvevmStApiFunction) dvtb_mpeg2Enc1Init, &G->mpeg2enc1 },
		{ "mpeg2enc1", "process", (DvevmStApiFunction) dvtb_mpeg2Enc1Encode, &G->mpeg2enc1 },
		{ "mpeg2enc1", "control", (DvevmStApiFunction) dvtb_mpeg2Enc1Control, &G->mpeg2enc1 },
		{ "mpeg2enc1", "delete", (DvevmStApiFunction) dvtb_mpeg2Enc1Close, &G->mpeg2enc1 },
		/* Api for AAC HE 1.0 Decoder */
		{ "aachedec1", "create", (DvevmStApiFunction) dvtb_aacheDec1Init, &G->aachedec1 },
		{ "aachedec1", "process", (DvevmStApiFunction) dvtb_aacheDec1Decode, &G->aachedec1 },
		{ "aachedec1", "control", (DvevmStApiFunction) dvtb_aacheDec1Control, &G->aachedec1 },
		{ "aachedec1", "delete", (DvevmStApiFunction) dvtb_aacheDec1Close, &G->aachedec1 },

		/* Api for AAC HE 1.0 Encoder */
		{ "aaclcenc1", "create", (DvevmStApiFunction) dvtb_aacheEnc1Init, &G->aacheenc1 },
		{ "aaclcenc1", "process", (DvevmStApiFunction) dvtb_aacheEnc1Encode, &G->aacheenc1 },
		{ "aaclcenc1", "control", (DvevmStApiFunction) dvtb_aacheEnc1Control, &G->aacheenc1 },
		{ "aaclcenc1", "delete", (DvevmStApiFunction) dvtb_aacheEnc1Close, &G->aacheenc1 },
		/* Api for MP3 1.0 Decoder */
		{ "mp3dec1", "create", (DvevmStApiFunction) dvtb_mp3Dec1Init, &G->mp3dec1 },
		{ "mp3dec1", "process", (DvevmStApiFunction) dvtb_mp3Dec1Decode, &G->mp3dec1 },
		{ "mp3dec1", "control", (DvevmStApiFunction) dvtb_mp3Dec1Control, &G->mp3dec1 },
		{ "mp3dec1", "delete", (DvevmStApiFunction) dvtb_mp3Dec1Close, &G->mp3dec1 },
		/* Api for MP3 1.0 Encoder */
		{ "mp3enc1", "create", (DvevmStApiFunction) dvtb_mp3Enc1Init, &G->mp3enc1 },
		{ "mp3enc1", "process", (DvevmStApiFunction) dvtb_mp3Enc1Encode, &G->mp3enc1 },
		{ "mp3enc1", "control", (DvevmStApiFunction) dvtb_mp3Enc1Control, &G->mp3enc1 },
		{ "mp3enc1", "delete", (DvevmStApiFunction) dvtb_mp3Enc1Close, &G->mp3enc1 },
		/* Api for WMA 1.0 Decoder */
		{ "wmadec1", "create", (DvevmStApiFunction) dvtb_wmaDec1Init, &G->wmadec1 },
		{ "wmadec1", "process", (DvevmStApiFunction) dvtb_wmaDec1Decode, &G->wmadec1 },
		{ "wmadec1", "control", (DvevmStApiFunction) dvtb_wmaDec1Control, &G->wmadec1 },
		{ "wmadec1", "delete", (DvevmStApiFunction) dvtb_wmaDec1Close, &G->wmadec1 },
		/* Api for WMA 1.0 Encoder */
		{ "wmaenc1", "create", (DvevmStApiFunction) dvtb_wmaEnc1Init, &G->wmaenc1 },
		{ "wmaenc1", "process", (DvevmStApiFunction) dvtb_wmaEnc1Encode, &G->wmaenc1 },
		{ "wmaenc1", "control", (DvevmStApiFunction) dvtb_wmaEnc1Control, &G->wmaenc1 },
		{ "wmaenc1", "delete", (DvevmStApiFunction) dvtb_wmaEnc1Close, &G->wmaenc1 },
		/************************************************************************************************/
		/************************************************************************************************/
		/***********     XDM 1.2 Base     ***************************************************************/
		/************************************************************************************************/
		/* Api for Video Decoder*/
		{ "viddec2", "create", (DvevmStApiFunction) dvtb_vidDec2Init, &G->vdec2 },
		{ "viddec2", "process", (DvevmStApiFunction) dvtb_vidDec2Decode, &G->vdec2 },
		{ "viddec2", "control", (DvevmStApiFunction) dvtb_vidDec2Control, &G->vdec2 },
		{ "viddec2", "delete", (DvevmStApiFunction) dvtb_vidDec2Close, &G->vdec2 },
		/************************************************************************************************/

		/************************************************************************************************/
		/***********     XDM 1.2 Extended   *************************************************************/
		/************************************************************************************************/
		/* Api for H264 Video Decoder*/
		{ "h264dec2", "create", (DvevmStApiFunction) dvtb_h264Dec2Init, &G->h264dec2 },
		{ "h264dec2", "process", (DvevmStApiFunction) dvtb_h264Dec2Decode, &G->h264dec2 },
		{ "h264dec2", "control", (DvevmStApiFunction) dvtb_h264Dec2Control, &G->h264dec2 },
		{ "h264dec2", "delete", (DvevmStApiFunction) dvtb_h264Dec2Close, &G->h264dec2 },
		/* Api for H264 Video Decoder*/
		{ "mpeg4dec2", "create", (DvevmStApiFunction) dvtb_mpeg4Dec2Init, &G->mpeg4dec2 },
		{ "mpeg4dec2", "process", (DvevmStApiFunction) dvtb_mpeg4Dec2Decode, &G->mpeg4dec2 },
		{ "mpeg4dec2", "control", (DvevmStApiFunction) dvtb_mpeg4Dec2Control, &G->mpeg4dec2 },
		{ "mpeg4dec2", "delete", (DvevmStApiFunction) dvtb_mpeg4Dec2Close, &G->mpeg4dec2 },
		/* Api for H264 Video Decoder*/
		{ "mpeg4hdvicpdec2", "create", (DvevmStApiFunction) dvtb_mpeg4HDVICPDec2Init, &G->mpeg4hdvicpdec2 },
		{ "mpeg4hdvicpdec2", "process", (DvevmStApiFunction) dvtb_mpeg4HDVICPDec2Decode, &G->mpeg4hdvicpdec2 },
		{ "mpeg4hdvicpdec2", "control", (DvevmStApiFunction) dvtb_mpeg4HDVICPDec2Control, &G->mpeg4hdvicpdec2 },
		{ "mpeg4hdvicpdec2", "delete", (DvevmStApiFunction) dvtb_mpeg4HDVICPDec2Close, &G->mpeg4hdvicpdec2 },

		/* Api for VC1 Video Decoder*/
		{ "vc1dec2", "create", (DvevmStApiFunction) dvtb_vc1Dec2Init, &G->vc1dec2 },
		{ "vc1dec2", "process", (DvevmStApiFunction) dvtb_vc1Dec2Decode, &G->vc1dec2 },
		{ "vc1dec2", "control", (DvevmStApiFunction) dvtb_vc1Dec2Control, &G->vc1dec2 },
		{ "vc1dec2", "delete", (DvevmStApiFunction) dvtb_vc1Dec2Close, &G->vc1dec2 },

		/* Api for Mpeg2 Decoder XDM 1.0*/
		{ "mpeg2dec2", "create", (DvevmStApiFunction) dvtb_mpeg2Dec2Init, &G->mpeg2dec2 },
		{ "mpeg2dec2", "process", (DvevmStApiFunction) dvtb_mpeg2Dec2Decode, &G->mpeg2dec2 },
		{ "mpeg2dec2", "control", (DvevmStApiFunction) dvtb_mpeg2Dec2Control, &G->mpeg2dec2 },
		{ "mpeg2dec2", "delete", (DvevmStApiFunction) dvtb_mpeg2Dec2Close, &G->mpeg2dec2 },
		/************************************************************************************************/

	};

	DVEVM_CE_NUM = sizeof(dvevmStApiArr) / sizeof(DvevmStApiTable);
	API = (DvevmStApiTable *) calloc(DVEVM_CE_NUM, sizeof(DvevmStApiTable));
	if (API != NULL)
	{
		memcpy(API, dvevmStApiArr, DVEVM_CE_NUM * sizeof(DvevmStApiTable));
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_apisExecute(int numTokens, char **tokens)
{
	int i = 0;

	DvevmStRetCode retval = DVEVM_ST_FAIL;

	if (numTokens != 2)
	{
		APIS_USAGE
	}
	else
	{
		for (i = 0; i < DVEVM_CE_NUM; i++)
		{
			if (0 == strcmp(*tokens, API[i].codecName))
			{
				if (0 == strcmp(tokens[1], API[i].apiName))
					retval = API[i].apiptr(API[i].param);
			}
		}
	}

	return retval;
}
