/*
 * dvtbApisDispatcher.c
 *
 * DVTB APIs Dispatcher
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

#define APIS_USAGE  SYS_ERROR("\nUsage: apis  <engine|videnc1|viddec1|imgenc1|imgdec1|sphenc|sphdec>\
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
		/* Api for MPEG4SP Encoder */
		{ "mpeg4spenc1", "create", (DvevmStApiFunction) dvtb_mpeg4spEnc1Init, &G->mpeg4spenc1 },
		{ "mpeg4spenc1", "process", (DvevmStApiFunction) dvtb_mpeg4spEnc1Encode, &G->mpeg4spenc1 },
		{ "mpeg4spenc1", "control", (DvevmStApiFunction) dvtb_mpeg4spEnc1Control, &G->mpeg4spenc1 },
		{ "mpeg4spenc1", "delete", (DvevmStApiFunction) dvtb_mpeg4spEnc1Close, &G->mpeg4spenc1 },
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
		/***********     XDM 1.2 Extended     ***********************************************************/
		/************************************************************************************************/
		/* Api for MPEG4SP Encoder */
		{ "mpeg4spdec2", "create", (DvevmStApiFunction) dvtb_mpeg4spDec2Init, &G->mpeg4spdec2 },
		{ "mpeg4spdec2", "process", (DvevmStApiFunction) dvtb_mpeg4spDec2Decode, &G->mpeg4spdec2 },
		{ "mpeg4spdec2", "control", (DvevmStApiFunction) dvtb_mpeg4spDec2Control, &G->mpeg4spdec2 },
		{ "mpeg4spdec2", "delete", (DvevmStApiFunction) dvtb_mpeg4spDec2Close, &G->mpeg4spdec2 },
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
