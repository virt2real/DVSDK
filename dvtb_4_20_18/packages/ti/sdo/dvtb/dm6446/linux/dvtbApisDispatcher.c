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
#include "dvtbVidEnc.h"
#include "dvtbVidDec.h"
#include "dvtbAudDec.h"
#include "dvtbMP3BaseDec.h"
#include "dvtbSphEnc.h"
#include "dvtbSphDec.h"
#include "dvtbAudEnc.h"
#include "dvtbImgDec.h"
#include "dvtbImgEnc.h"

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

DvevmStApiTable *API = NULL;
unsigned int DVEVM_CE_NUM = 0;

DvevmStRetCode dvtb_apisInit()
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
	/* Api for Video Encoder */
	{ "videnc", "create", (DvevmStApiFunction) dvtb_vidEncInit, &G->venc },
	{ "videnc", "process", (DvevmStApiFunction) dvtb_vidEncEncode, &G->venc },
	{ "videnc", "control", (DvevmStApiFunction) dvtb_vidEncControl, &G->venc },
	{ "videnc", "delete", (DvevmStApiFunction) dvtb_vidEncClose, &G->venc },
	/* Api for Video Decoder */
	{ "viddec", "create", (DvevmStApiFunction) dvtb_vidDecInit, &G->vdec },
	{ "viddec", "process", (DvevmStApiFunction) dvtb_vidDecDecode, &G->vdec },
	{ "viddec", "control", (DvevmStApiFunction) dvtb_vidDecControl, &G->vdec },
	{ "viddec", "delete", (DvevmStApiFunction) dvtb_vidDecClose, &G->vdec },
	/* Api for Audio Decoder */
	{ "auddec", "create", (DvevmStApiFunction) dvtb_audDecInit, &G->adec },
	{ "auddec", "process", (DvevmStApiFunction) dvtb_audDecDecode, &G->adec },
	{ "auddec", "control", (DvevmStApiFunction) dvtb_audDecControl, &G->adec },
	{ "auddec", "delete", (DvevmStApiFunction) dvtb_audDecClose, &G->adec },
	/* Api for MP3 Bse params Audio Decoder */
	{ "mp3basedec", "create", (DvevmStApiFunction) dvtb_mp3baseDecInit, &G->mp3basedec },
	{ "mp3basedec", "process", (DvevmStApiFunction) dvtb_mp3baseDecDecode, &G->mp3basedec },
	{ "mp3basedec", "control", (DvevmStApiFunction) dvtb_mp3baseDecControl, &G->mp3basedec },
	{ "mp3basedec", "delete", (DvevmStApiFunction) dvtb_mp3baseDecClose, &G->mp3basedec },
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

	/* Api for Audio Encoder */
	{ "audenc", "create", (DvevmStApiFunction) dvtb_audEncInit, &G->aenc },
	{ "audenc", "process", (DvevmStApiFunction) dvtb_audEncEncode, &G->aenc },
	{ "audenc", "control", (DvevmStApiFunction) dvtb_audEncControl, &G->aenc },
	{ "audenc", "delete", (DvevmStApiFunction) dvtb_audEncClose, &G->aenc },

	/* Api for Image Decoder */
	{ "imgdec", "create", (DvevmStApiFunction) dvtb_imgDecInit, &G->idec },
	{ "imgdec", "process", (DvevmStApiFunction) dvtb_imgDecDecode, &G->idec },
	{ "imgdec", "control", (DvevmStApiFunction) dvtb_imgDecControl, &G->idec },
	{ "imgdec", "delete", (DvevmStApiFunction) dvtb_imgDecClose, &G->idec },

	/* Api for Image Encoder */
	{ "imgenc", "create", (DvevmStApiFunction) dvtb_imgEncInit, &G->ienc },
	{ "imgenc", "process", (DvevmStApiFunction) dvtb_imgEncEncode, &G->ienc },
	{ "imgenc", "control", (DvevmStApiFunction) dvtb_imgEncControl, &G->ienc },
	{ "imgenc", "delete", (DvevmStApiFunction) dvtb_imgEncClose, &G->ienc },
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 1.0 Base     ***************************************************************/
	/************************************************************************************************/
	/* Api for Video Encoder */
	{ "videnc1", "create", (DvevmStApiFunction) dvtb_vidEnc1Init, &G->venc1 },
	{ "videnc1", "process", (DvevmStApiFunction) dvtb_vidEnc1Encode, &G->venc1 },
	{ "videnc1", "control", (DvevmStApiFunction) dvtb_vidEnc1Control, &G->venc1 },
	{ "videnc1", "delete", (DvevmStApiFunction) dvtb_vidEnc1Close, &G->venc1 },
	/* Api for Image Encoder */
	{ "imgenc1", "create", (DvevmStApiFunction) dvtb_imgEnc1Init, &G->ienc1 },
	{ "imgenc1", "process", (DvevmStApiFunction) dvtb_imgEnc1Encode, &G->ienc1 },
	{ "imgenc1", "control", (DvevmStApiFunction) dvtb_imgEnc1Control, &G->ienc1 },
	{ "imgenc1", "delete", (DvevmStApiFunction) dvtb_imgEnc1Close, &G->ienc1 },
	/* Api for image Decoder */
	{ "imgdec1", "create", (DvevmStApiFunction) dvtb_imgDec1Init, &G->idec1 },
	{ "imgdec1", "process", (DvevmStApiFunction) dvtb_imgDec1Decode, &G->idec1 },
	{ "imgdec1", "control", (DvevmStApiFunction) dvtb_imgDec1Control, &G->idec1 },
	{ "imgdec1", "delete", (DvevmStApiFunction) dvtb_imgDec1Close, &G->idec1 },
	/* Api for Audio Encoder */
	{ "audenc1", "create", (DvevmStApiFunction) dvtb_audEnc1Init, &G->aenc1 },
	{ "audenc1", "process", (DvevmStApiFunction) dvtb_audEnc1Encode, &G->aenc1 },
	{ "audenc1", "control", (DvevmStApiFunction) dvtb_audEnc1Control, &G->aenc1 },
	{ "audenc1", "delete", (DvevmStApiFunction) dvtb_audEnc1Close, &G->aenc1 },
	/* Api for Audio Decoder */
	{ "auddec1", "create", (DvevmStApiFunction) dvtb_audDec1Init, &G->adec1 },
	{ "auddec1", "process", (DvevmStApiFunction) dvtb_audDec1Decode, &G->adec1 },
	{ "auddec1", "control", (DvevmStApiFunction) dvtb_audDec1Control, &G->adec1 },
	{ "auddec1", "delete", (DvevmStApiFunction) dvtb_audDec1Close, &G->adec1 },
	/* Api for MP3 Base params Audio Decoder */
	{ "mp3basedec1", "create", (DvevmStApiFunction) dvtb_mp3basedec1Init, &G->mp3basedec1 },
	{ "mp3basedec1", "process", (DvevmStApiFunction) dvtb_mp3basedec1Decode, &G->mp3basedec1 },
	{ "mp3basedec1", "control", (DvevmStApiFunction) dvtb_mp3basedec1Control, &G->mp3basedec1 },
	{ "mp3basedec1", "delete", (DvevmStApiFunction) dvtb_mp3basedec1Close, &G->mp3basedec1 },
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
	/* Api for AAC LC Encoder */
	{ "aaclcenc1", "create", (DvevmStApiFunction) dvtb_aaclcEnc1Init, &G->aaclcenc1 },
	{ "aaclcenc1", "process", (DvevmStApiFunction) dvtb_aaclcEnc1Encode, &G->aaclcenc1 },
	{ "aaclcenc1", "control", (DvevmStApiFunction) dvtb_aaclcEnc1Control, &G->aaclcenc1 },
	{ "aaclcenc1", "delete", (DvevmStApiFunction) dvtb_aaclcEnc1Close, &G->aaclcenc1 },
	/* Api for AAC HE Encoder */
	{ "aacheenc1", "create", (DvevmStApiFunction) dvtb_aacheEnc1Init, &G->aacheenc1 },
	{ "aacheenc1", "process", (DvevmStApiFunction) dvtb_aacheEnc1Encode, &G->aacheenc1 },
	{ "aacheenc1", "control", (DvevmStApiFunction) dvtb_aacheEnc1Control, &G->aacheenc1 },
	{ "aacheenc1", "delete", (DvevmStApiFunction) dvtb_aacheEnc1Close, &G->aacheenc1 },
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 1.2 Base     ***************************************************************/
	/************************************************************************************************/
	/* Api for Video Decoder XDM 1.2*/
	{ "viddec2", "create", (DvevmStApiFunction) dvtb_vidDec2Init, &G->vdec2 },
	{ "viddec2", "process", (DvevmStApiFunction) dvtb_vidDec2Decode, &G->vdec2 },
	{ "viddec2", "control", (DvevmStApiFunction) dvtb_vidDec2Control, &G->vdec2 },
	{ "viddec2", "delete", (DvevmStApiFunction) dvtb_vidDec2Close, &G->vdec2 },
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
		SYS_ERROR("\nUsage: apis <engine|auddec|sphenc|sphdec|videnc|viddec|mp3basedec> \n");
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
