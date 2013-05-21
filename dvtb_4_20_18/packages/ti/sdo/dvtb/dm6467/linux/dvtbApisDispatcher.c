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
#include "dvtbAudEnc.h"
#include "dvtbAudDec.h"
#include "dvtbSphEnc.h"
#include "dvtbSphDec.h"

//XDM 0.9 Extended
#include "dvtbAACEnc.h"

//XDM 1.0 Base
#include "dvtbAudEnc1.h"
#include "dvtbMP3BaseDec1.h"
#include "dvtbAudDec1.h"
#include "dvtbSphEnc1.h"
#include "dvtbSphDec1.h"

//XDM 1.0 Extended
#include "dvtbH264Enc1.h"
#include "dvtbH264fhdEnc1.h"
#include "dvtbMpeg4Enc1.h"
#include "dvtbAACHEDec1.h"

//XDM 1.2 Base
#include "dvtbVidDec2.h"

//XDM 1.2 Extended
#ifdef _DVTB_H264DEC_
#include "dvtbH264Dec2.h"
#endif
#ifdef _DVTB_H2641080p60VDEC_
#include "dvtbH2641080pDec2.h"
#endif
#include "dvtbMpeg2Dec2.h"
#include "dvtbMpeg4Dec2.h"

#define APIS_USAGE  SYS_ERROR("\nUsage: apis \ <engine|auddec|videnc|viddec|h264mpdec|mpeg2mpdec|audenc|mpeg2mp1dot1dec>\
    [open|mem|cpu|close|create|control|process|delete] \n")

#ifdef _DVTB_NONTSPA_
//XDM 1.0 Extended
#include "dvtbAACHEEnc1.h"
#endif

DvevmStApiTable *API = NULL;
unsigned int DVEVM_CE_NUM = 0;

DvevmStRetCode
dvtb_apisInit()
{
	DvevmStApiTable dvevmStApiArr[] =
	{
#if 0
			/*Api for Codec Engine*/
			{	"engine", "runtime", (DvevmStApiFunction) dvtb_ceRuntimeInit, &G->eng},
			{	"engine", "open", (DvevmStApiFunction) dvtb_ceOpen, &G->eng},
			{	"engine", "getmem", (DvevmStApiFunction) dvtb_ceMem, &G->eng},
			{	"engine", "getcpu", (DvevmStApiFunction) dvtb_ceCpu, &G->eng},
			{	"engine", "close", (DvevmStApiFunction) dvtb_ceClose, &G->eng},
#endif

			/************************************************************************************************/
			/***********     XDM 0.9 Base     ***************************************************************/
			/************************************************************************************************/
			/* Api for Audio Decoder */
			{ "auddec", "create", (DvevmStApiFunction) dvtb_audDecInit, &G->adec },
			{ "auddec", "process", (DvevmStApiFunction) dvtb_audDecDecode, &G->adec },
			{ "auddec", "control", (DvevmStApiFunction) dvtb_audDecControl, &G->adec },
			{ "auddec", "delete", (DvevmStApiFunction) dvtb_audDecClose, &G->adec },

			/* Api for Speech Encoder */
			{ "sphenc", "create", (DvevmStApiFunction) dvtb_sphEncInit, &G->senc },
			{ "sphenc", "process", (DvevmStApiFunction) dvtb_sphEncEncode, &G->senc },
			{ "sphenc", "control", (DvevmStApiFunction) dvtb_sphEncControl, &G->senc },
			{ "sphenc", "delete", (DvevmStApiFunction) dvtb_sphEncClose, &G->senc },

			/* Api for Speech Decoder */
			{ "sphdec", "create", (DvevmStApiFunction) dvtb_sphDecInit, &G->sdec },
			{ "sphdec", "process", (DvevmStApiFunction) dvtb_sphDecDecode, &G->sdec },
			{ "sphdec", "control", (DvevmStApiFunction) dvtb_sphDecControl, &G->sdec },
			{ "sphdec", "delete", (DvevmStApiFunction) dvtb_sphDecClose, &G->sdec },

			/* Api for AACLC 1dot0 Audio Encoder */
			{ "aacenc", "create", (DvevmStApiFunction) dvtb_aacEncInit, &G->aacenc },
			{ "aacenc", "process", (DvevmStApiFunction) dvtb_aacEncEncode, &G->aacenc },
			{ "aacenc", "control", (DvevmStApiFunction) dvtb_aacEncControl, &G->aacenc },
			{ "aacenc", "delete", (DvevmStApiFunction) dvtb_aacEncClose, &G->aacenc },
			/************************************************************************************************/

			/************************************************************************************************/
			/***********     XDM 1.0 Base     ***************************************************************/
			/************************************************************************************************/
			/* Api for Video Encoder XDM 1.0*/
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

			/* Api for Speech 1.0 Encoder */
			{ "sphenc1", "create", (DvevmStApiFunction) dvtb_sphEnc1Init, &G->senc1 },
			{ "sphenc1", "process", (DvevmStApiFunction) dvtb_sphEnc1Encode, &G->senc1 },
			{ "sphenc1", "control", (DvevmStApiFunction) dvtb_sphEnc1Control, &G->senc1 },
			{ "sphenc1", "delete", (DvevmStApiFunction) dvtb_sphEnc1Close, &G->senc1 },

			/* Api for Speech 1.0 Decoder */
			{ "sphdec1", "create", (DvevmStApiFunction) dvtb_sphDec1Init, &G->sdec1 },
			{ "sphdec1", "process", (DvevmStApiFunction) dvtb_sphDec1Decode, &G->sdec1 },
			{ "sphdec1", "control", (DvevmStApiFunction) dvtb_sphDec1Control, &G->sdec1 },
			{ "sphdec1", "delete", (DvevmStApiFunction) dvtb_sphDec1Close, &G->sdec1 },

			/* Api for Image Encoder XDM 1.0*/
			{"imgenc1", "create", (DvevmStApiFunction) dvtb_imgEnc1Init, &G->ienc1},
			{"imgenc1", "process", (DvevmStApiFunction) dvtb_imgEnc1Encode, &G->ienc1},
			{"imgenc1", "control", (DvevmStApiFunction) dvtb_imgEnc1Control, &G->ienc1},
			{"imgenc1", "delete", (DvevmStApiFunction) dvtb_imgEnc1Close, &G->ienc1},

			/* Api for image Decoder XDM 1.0*/
			{"imgdec1", "create", (DvevmStApiFunction) dvtb_imgDec1Init, &G->idec1},
			{"imgdec1", "process", (DvevmStApiFunction) dvtb_imgDec1Decode, &G->idec1},
			{"imgdec1", "control", (DvevmStApiFunction) dvtb_imgDec1Control, &G->idec1},
			{"imgdec1", "delete", (DvevmStApiFunction) dvtb_imgDec1Close, &G->idec1},

			/* Api for Audio1 Decoder */
			{"mp3basedec1", "create", (DvevmStApiFunction) dvtb_mp3basedec1Init, &G->mp3basedec1},
			{"mp3basedec1", "process", (DvevmStApiFunction) dvtb_mp3basedec1Decode, &G->mp3basedec1},
			{"mp3basedec1", "control", (DvevmStApiFunction) dvtb_mp3basedec1Control, &G->mp3basedec1},
			{"mp3basedec1", "delete", (DvevmStApiFunction) dvtb_mp3basedec1Close, &G->mp3basedec1},
			/************************************************************************************************/

			/************************************************************************************************/
			/***********     XDM 1.0 Extended     ***********************************************************/
			/************************************************************************************************/
			/* Api for H264 Encoder XDM 1.0*/
			{ "h264enc1", "create", (DvevmStApiFunction) dvtb_h264Enc1Init, &G->h264enc1 },
			{ "h264enc1", "process", (DvevmStApiFunction) dvtb_h264Enc1Encode, &G->h264enc1 },
			{ "h264enc1", "control", (DvevmStApiFunction) dvtb_h264Enc1Control, &G->h264enc1 },
			{ "h264enc1", "delete", (DvevmStApiFunction) dvtb_h264Enc1Close, &G->h264enc1 },

			/* Api for H264FHD Encoder XDM 1.0*/
			{ "h264fhdenc1", "create", (DvevmStApiFunction) dvtb_h264fhdEnc1Init, &G->h264fhdenc1 },
			{ "h264fhdenc1", "process", (DvevmStApiFunction) dvtb_h264fhdEnc1Encode, &G->h264fhdenc1 },
			{ "h264fhdenc1", "control", (DvevmStApiFunction) dvtb_h264fhdEnc1Control, &G->h264fhdenc1 },
			{ "h264fhdenc1", "delete", (DvevmStApiFunction) dvtb_h264fhdEnc1Close, &G->h264fhdenc1 },

			/* Api for MPEG4 Encoder XDM 1.0*/
			{ "mpeg4enc1", "create", (DvevmStApiFunction) dvtb_MPEG4Enc1Init, &G->mpeg4enc1 },
			{ "mpeg4enc1", "process", (DvevmStApiFunction) dvtb_MPEG4Enc1Encode, &G->mpeg4enc1 },
			{ "mpeg4enc1", "control", (DvevmStApiFunction) dvtb_MPEG4Enc1Control, &G->mpeg4enc1 },
			{ "mpeg4enc1", "delete", (DvevmStApiFunction) dvtb_MPEG4Enc1Close, &G->mpeg4enc1 },

			/* Api for AAC HE 1.0 Decoder */
			{ "aachedec1", "create", (DvevmStApiFunction) dvtb_aacheDec1Init, &G->aachedec1 },
			{ "aachedec1", "process", (DvevmStApiFunction) dvtb_aacheDec1Decode, &G->aachedec1 },
			{ "aachedec1", "control", (DvevmStApiFunction) dvtb_aacheDec1Control, &G->aachedec1 },
			{ "aachedec1", "delete", (DvevmStApiFunction) dvtb_aacheDec1Close, &G->aachedec1 },

#ifdef _DVTB_NONTSPA_
			/* Api for AAC HE 1.0 Encoder */
			{ "aacheenc1", "create", (DvevmStApiFunction) dvtb_aacheEnc1Init, &G->aacheenc1 },
			{ "aacheenc1", "process", (DvevmStApiFunction) dvtb_aacheEnc1Encode, &G->aacheenc1 },
			{ "aacheenc1", "control", (DvevmStApiFunction) dvtb_aacheEnc1Control, &G->aacheenc1 },
			{ "aacheenc1", "delete", (DvevmStApiFunction) dvtb_aacheEnc1Close, &G->aacheenc1 },
#endif

			/* Api for jpeg Decoder XDM1.0 */
			{"jpegdec1", "create", (DvevmStApiFunction) dvtb_jpegDec1Init, &G->jpegdec1},
			{"jpegdec1", "process", (DvevmStApiFunction) dvtb_jpegDec1Decode, &G->jpegdec1},
			{"jpegdec1", "control", (DvevmStApiFunction) dvtb_jpegDec1Control, &G->jpegdec1},
			{"jpegdec1", "delete", (DvevmStApiFunction) dvtb_jpegDec1Close, &G->jpegdec1},

			/* Api for JPEG Encoder XDM 1.0*/
			{ "jpegenc1", "create", (DvevmStApiFunction) dvtb_jpegEnc1Init, &G->jpegenc1 },
			{ "jpegenc1", "process", (DvevmStApiFunction) dvtb_jpegEnc1Encode, &G->jpegenc1 },
			{ "jpegenc1", "control", (DvevmStApiFunction) dvtb_jpegEnc1Control, &G->jpegenc1 },
			{ "jpegenc1", "delete", (DvevmStApiFunction) dvtb_jpegEnc1Close, &G->jpegenc1 },
			/************************************************************************************************/

			/************************************************************************************************/
			/***********     XDM 1.2 Base     ***************************************************************/
			/************************************************************************************************/
			/* Api for Video Decoder XDM 1.0*/
			{ "viddec2", "create", (DvevmStApiFunction) dvtb_vidDec2Init, &G->vdec2 },
			{ "viddec2", "process", (DvevmStApiFunction) dvtb_vidDec2Decode, &G->vdec2 },
			{ "viddec2", "control", (DvevmStApiFunction) dvtb_vidDec2Control, &G->vdec2 },
			{ "viddec2", "delete", (DvevmStApiFunction) dvtb_vidDec2Close, &G->vdec2 },


			/************************************************************************************************/
			/***********     XDM 1.2 Extended     ***********************************************************/
			/************************************************************************************************/
			/* Api for H264 Decoder XDM 1.0*/
#ifdef _DVTB_H264DEC_
			{ "h264dec2", "create", (DvevmStApiFunction) dvtb_h264Dec2Init, &G->h264dec2 },
			{ "h264dec2", "process", (DvevmStApiFunction) dvtb_h264Dec2Decode, &G->h264dec2 },
			{ "h264dec2", "control", (DvevmStApiFunction) dvtb_h264Dec2Control, &G->h264dec2 },
			{ "h264dec2", "delete", (DvevmStApiFunction) dvtb_h264Dec2Close, &G->h264dec2 },

#endif

#ifdef _DVTB_H2641080p60VDEC_
			/* Api for H2641080p Decoder XDM 1.0*/
			{ "h2641080pdec2", "create", (DvevmStApiFunction) dvtb_h2641080pDec2Init, &G->h2641080pdec2 },
			{ "h2641080pdec2", "process", (DvevmStApiFunction) dvtb_h2641080pDec2Decode, &G->h2641080pdec2 },
			{ "h2641080pdec2", "control", (DvevmStApiFunction) dvtb_h2641080pDec2Control, &G->h2641080pdec2 },
			{ "h2641080pdec2", "delete", (DvevmStApiFunction) dvtb_h2641080pDec2Close, &G->h2641080pdec2 },
#endif

			/* Api for Mpeg2 Decoder XDM 1.0*/
			{ "mpeg2dec2", "create", (DvevmStApiFunction) dvtb_mpeg2Dec2Init, &G->mpeg2dec2 },
			{ "mpeg2dec2", "process", (DvevmStApiFunction) dvtb_mpeg2Dec2Decode, &G->mpeg2dec2 },
			{ "mpeg2dec2", "control", (DvevmStApiFunction) dvtb_mpeg2Dec2Control, &G->mpeg2dec2 },
			{ "mpeg2dec2", "delete", (DvevmStApiFunction) dvtb_mpeg2Dec2Close, &G->mpeg2dec2 },
			
			/* Api for Mpeg2 Decoder XDM 1.0*/
			{ "mpeg4dec2", "create", (DvevmStApiFunction) dvtb_mpeg4Dec2Init, &G->mpeg4dec2 },
			{ "mpeg4dec2", "process", (DvevmStApiFunction) dvtb_mpeg4Dec2Decode, &G->mpeg4dec2 },
			{ "mpeg4dec2", "control", (DvevmStApiFunction) dvtb_mpeg4Dec2Control, &G->mpeg4dec2 },
			{ "mpeg4dec2", "delete", (DvevmStApiFunction) dvtb_mpeg4Dec2Close, &G->mpeg4dec2 },
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

	if ((numTokens != 2))
	{
		//APIS_USAGE;
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
