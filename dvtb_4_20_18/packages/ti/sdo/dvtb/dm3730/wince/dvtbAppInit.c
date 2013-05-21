/*
 * dvtbAppInit.c
 *
 * Application Initialization
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

#include "dvtbAppInit.h"
#include "dvtbGlobal.h"
#include "dvtbParam.h"
#include "dvtbSetParam.h"
#include "dvtbMemory.h"

#define SETP_USAGE  SYS_ERROR("Usage: setp <global|auddec|spcenc|spcdec|videnc|viddec|viddec2|videnc1|imgenc1> [option] [value]\n")

DvevmStGlobalParams dvevmStGlobalParams;
DvevmStGlobalParams *G = &dvevmStGlobalParams;
LARGE_INTEGER PerformanceFrequency;

DvevmStRetCode
dvtb_initParams()
{
	unsigned int index = 0;
	DVTBASSERT(G != NULL);

	memset(G, 0, sizeof(DvevmStGlobalParams));
	dvtb_initValues( );

	for (index = 0; index < DVEVM_CODEC_NUM; index++)
		dvtb_setpStr(index, NULL);

	if (!(QueryPerformanceFrequency(&PerformanceFrequency)))
	{
		SYS_ERROR("Unable to query Performance Frequency \n");
	}

	/************************************************************************************************/
	/***********     Drivers     ********************************************************************/
	/************************************************************************************************/
//	G->aud.framesize = 0;
//	G->vpbe.pixelformat = V4L2_PIX_FMT_UYVY;
//	G->vpbe.opMode = 0;
//	G->vpbe.maxBuffers = 3;
	G->idec1.dvtb_ptrAllocCmem = &dvtb_allocCmem;
	G->idec1.dvtb_ptrFreeCmem = &dvtb_freeCmem;
//	dvtb_vpbeSetupPtr = &dvtb_vpbeOMAPSetup;
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 0.9 Base     ***************************************************************/
	/************************************************************************************************/

	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 1.0 Base     ***************************************************************/
	/************************************************************************************************/

	G->adec1.adecParams.size = sizeof(IAUDDEC1_Params);
	G->adec1.adecStatus.size = sizeof(AUDDEC1_Status);
	G->adec1.adecDynParams.size = sizeof(AUDDEC1_DynamicParams);
	G->adec1.adecInArgs.size = sizeof(AUDDEC1_InArgs);
	G->adec1.adecOutArgs.size = sizeof(AUDDEC1_OutArgs);

	G->mp3basedec1.adecParams.size = sizeof(IAUDDEC1_Params);
	G->mp3basedec1.adecStatus.size = sizeof(AUDDEC1_Status);
	G->mp3basedec1.adecDynParams.size = sizeof(AUDDEC1_DynamicParams);
	G->mp3basedec1.adecInArgs.size = sizeof(AUDDEC1_InArgs);
	G->mp3basedec1.adecOutArgs.size = sizeof(AUDDEC1_OutArgs);

	G->idec1.idec1Params.size = sizeof(IMGDEC1_Params);
	G->idec1.idec1Status.size = sizeof(IMGDEC1_Status);
	G->idec1.idec1DynParams.size = sizeof(IMGDEC1_DynamicParams);
	G->idec1.idec1InArgs.size = sizeof(IMGDEC1_InArgs);
	G->idec1.idec1OutArgs.size = sizeof(IMGDEC1_OutArgs);

	G->venc1.venc1Params.size = sizeof(VIDENC1_Params);
	G->venc1.venc1Status.size = sizeof(VIDENC1_Status);
	G->venc1.venc1DynParams.size = sizeof(VIDENC1_DynamicParams);
	G->venc1.venc1InArgs.size = sizeof(VIDENC1_InArgs);
	G->venc1.venc1OutArgs.size = sizeof(VIDENC1_OutArgs);

	G->ienc1.ienc1Params.size = sizeof(IMGENC1_Params);
	G->ienc1.ienc1Status.size = sizeof(IMGENC1_Status);
	G->ienc1.ienc1DynParams.size = sizeof(IMGENC1_DynamicParams);
	G->ienc1.ienc1InArgs.size = sizeof(IMGENC1_InArgs);
	G->ienc1.ienc1OutArgs.size = sizeof(IMGENC1_OutArgs);

	G->senc1.sencParams.size = sizeof(SPHENC1_Params);
	G->senc1.sencStatus.size = sizeof(SPHENC1_Status);
	G->senc1.sencDynParams.size = sizeof(SPHENC1_DynamicParams);
	G->senc1.sencInArgs.size = sizeof(SPHENC1_InArgs);
	G->senc1.sencOutArgs.size = sizeof(SPHENC1_OutArgs);

	G->sdec1.sdecParams.size = sizeof(SPHDEC1_Params);
	G->sdec1.sdecStatus.size = sizeof(SPHDEC1_Status);
	G->sdec1.sdecDynParams.size = sizeof(SPHDEC1_DynamicParams);
	G->sdec1.sdecInArgs.size = sizeof(SPHDEC1_InArgs);
	G->sdec1.sdecOutArgs.size = sizeof(SPHDEC1_OutArgs);

	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 1.0 Extended     ***********************************************************/
	/************************************************************************************************/

	G->jpegdec1.idec1Params.imgdecParams.size = sizeof(IJPEGDEC_Params);
	G->jpegdec1.idec1Status.imgdecStatus.size = sizeof(IJPEGDEC_Status);
	G->jpegdec1.idec1DynParams.imgdecDynamicParams.size = sizeof(IJPEGDEC_DynamicParams);
	G->jpegdec1.idec1InArgs.imgdecInArgs.size = sizeof(IJPEGDEC_InArgs);
	G->jpegdec1.idec1OutArgs.imgdecOutArgs.size = sizeof(IJPEGDEC_OutArgs);

	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 1.2 Base     ***************************************************************/
	/************************************************************************************************/

	G->viddec2.vdec2Params.size = sizeof(VIDDEC2_Params);
	G->viddec2.vdec2Status.size = sizeof(VIDDEC2_Status);
	G->viddec2.vdec2DynParams.size = sizeof(VIDDEC2_DynamicParams);
	G->viddec2.vdec2InArgs.size = sizeof(VIDDEC2_InArgs);
	G->viddec2.vdec2OutArgs.size = sizeof(VIDDEC2_OutArgs);

	/************************************************************************************************/

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode dvtb_initApp(void)
{
	DvevmStRetCode rc = DVEVM_ST_FAIL;

	dvtb_ceRuntimeInit(&G->eng);
	rc = dvtb_initParams( );
	return rc;
}
