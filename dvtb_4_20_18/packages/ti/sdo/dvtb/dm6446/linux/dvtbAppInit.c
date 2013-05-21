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

#define SETP_USAGE  SYS_ERROR("Usage: setp <auddec|sphenc|sphdec|videnc|viddec|mp3basedec> [option] [value]\n")

DvevmStGlobalParams dvevmStGlobalParams;
DvevmStGlobalParams *G = &dvevmStGlobalParams;

DvevmStRetCode
dvtb_initParams()
{
	int index = 0;
	ASSERT(G != NULL);

	memset(G, 0, sizeof(DvevmStGlobalParams));
	dvtb_initValues( );

	for (index = 0; index < DVEVM_CODEC_NUM; index++)
		dvtb_setpStr(index, NULL);

	/************************************************************************************************/
	/***********     Drivers     ********************************************************************/
	/************************************************************************************************/
	G->vpbe.setupFxn.openV4l2Osd = (DvevmStRetCode(*)(void *)) dvtb_openV4l2Osd;
	G->vpbe.setupFxn.ioctlV4l2Osd = (DvevmStRetCode(*)(void *, unsigned int, void *)) dvtb_ioctlV4l2Osd;
	G->vpbe.setupFxn.setV4l2Fmt = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2OutputFmtOverride;
	G->vpbe.setupFxn.initV4l2OutputMmapBuffs = (DvevmStRetCode(*)(void *)) dvtb_initV4l2OutputMmapBuffs;
	G->vpbe.setupFxn.initV4l2OutputUserBuffs = (DvevmStRetCode(*)(void *)) dvtb_initV4l2OutputUserBuffs;
	G->vpbe.setupFxn.setV4l2PreFmtConfiguration = (DvevmStRetCode(*)(void *)) NULL;
	G->vpbe.setupFxn.setV4l2PostFmtConfiguration = (DvevmStRetCode(*)(void *)) NULL;

	G->vpbe.qBuffFxn.setV4l2UserBuffConfig = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2UserBuffConfig;
	G->vpbe.qBuffFxn.setV4l2MmapBuffConfig = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2MmapBuffConfig;

	G->vpbe.dqBuffFxn.getV4l2UserBuff = (void* (*)(void *)) dvtb_getV4l2UserBuff;
	G->vpbe.dqBuffFxn.getV4l2MmapBuff = (void* (*)(void *)) dvtb_getV4l2MmapBuff;

	G->vpbe.xres = G->vpbe.imageWidth;
	G->vpbe.yres = G->vpbe.imageHeight;
	G->vpbe.pixelformat = VID_FMT_UYVY;
	G->vpbe.opMode = 0;
	G->aud.framesize = 0;
	G->idec1.dvtb_ptrAllocCmem = &dvtb_allocCmem;
	G->idec1.dvtb_ptrFreeCmem = &dvtb_freeCmem;
	dvtb_vpbeSetupPtr = &dvtb_vpbeSetup;
	dvtb_audioSetControlContentsPtr = NULL;
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 0.9 Base     ***************************************************************/
	/************************************************************************************************/
	G->venc.vencParams.size = sizeof(VIDENC_Params);
	G->venc.vencStatus.size = sizeof(VIDENC_Status);
	G->venc.vencDynParams.size = sizeof(VIDENC_DynamicParams);
	G->venc.vencInArgs.size = sizeof(VIDENC_InArgs);
	G->venc.vencOutArgs.size = sizeof(VIDENC_OutArgs);

	G->vdec.vdecParams.size = sizeof(VIDDEC_Params);
	G->vdec.vdecStatus.size = sizeof(VIDDEC_Status);
	G->vdec.vdecDynParams.size = sizeof(VIDDEC_DynamicParams);
	G->vdec.vdecInArgs.size = sizeof(VIDDEC_InArgs);
	G->vdec.vdecOutArgs.size = sizeof(VIDDEC_OutArgs);

	G->adec.adecParams.size = sizeof(IAUDDEC_Params);
	G->adec.adecStatus.size = sizeof(AUDDEC_Status);
	G->adec.adecDynParams.size = sizeof(AUDDEC_DynamicParams);
	G->adec.adecOutArgs.size = sizeof(AUDDEC_OutArgs);
	G->adec.adecInArgs.size = sizeof(AUDDEC_InArgs);

	G->mp3basedec.adecParams.size = sizeof(AUDDEC_Params);
	G->mp3basedec.adecStatus.size = sizeof(AUDDEC_Status);
	G->mp3basedec.adecDynParams.size = sizeof(AUDDEC_DynamicParams);

	G->senc.sencParams.size = sizeof(SPHENC_Params);
	G->senc.sencStatus.size = sizeof(SPHENC_Status);
	G->senc.sencDynParams.size = sizeof(SPHENC_DynamicParams);
	G->senc.sencInArgs.size = sizeof(SPHENC_InArgs);
	G->senc.sencOutArgs.size = sizeof(SPHENC_OutArgs);

	G->sdec.sdecParams.size = sizeof(SPHDEC_Params);
	G->sdec.sdecStatus.size = sizeof(SPHDEC_Status);
	G->sdec.sdecDynParams.size = sizeof(SPHDEC_DynamicParams);
	G->sdec.sdecInArgs.size = sizeof(SPHDEC_InArgs);
	G->sdec.sdecOutArgs.size = sizeof(SPHDEC_OutArgs);

	G->aenc.aencParams.size = sizeof(AUDENC_Params);
	G->aenc.aencStatus.size = sizeof(AUDENC_Status);
	G->aenc.aencDynParams.size = sizeof(AUDENC_DynamicParams);

	G->idec.idecParams.size = sizeof(IMGDEC_Params);
	G->idec.idecStatus.size = sizeof(IMGDEC_Status);
	G->idec.idecDynParams.size = sizeof(IMGDEC_DynamicParams);
	G->idec.idecInArgs.size = sizeof(IMGDEC_InArgs);
	G->idec.idecOutArgs.size = sizeof(IMGDEC_OutArgs);

	G->ienc.iencParams.size = sizeof(IMGENC_Params);
	G->ienc.iencStatus.size = sizeof(IMGENC_Status);
	G->ienc.iencDynParams.size = sizeof(IMGENC_DynamicParams);
	G->ienc.iencOutArgs.size = sizeof(IMGENC_OutArgs);
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 1.0 Base     ***************************************************************/
	/************************************************************************************************/
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

	G->idec1.idec1Params.size = sizeof(IMGDEC1_Params);
	G->idec1.idec1Status.size = sizeof(IMGDEC1_Status);
	G->idec1.idec1DynParams.size = sizeof(IMGDEC1_DynamicParams);
	G->idec1.idec1InArgs.size = sizeof(IMGDEC1_InArgs);
	G->idec1.idec1OutArgs.size = sizeof(IMGDEC1_OutArgs);

	G->aenc1.audenc1Params.size = sizeof(IAUDENC1_Params);
	G->aenc1.audenc1Status.size = sizeof(IAUDENC1_Status);
	G->aenc1.audenc1DynParams.size = sizeof(IAUDENC1_DynamicParams);
	G->aenc1.audenc1InArgs.size = sizeof(IAUDENC1_InArgs);
	G->aenc1.audenc1OutArgs.size = sizeof(IAUDENC1_OutArgs);
	G->aenc1.InSamplesPerChannel = AUDENC1_FRAME_SIZE;

	G->adec1.adecParams.size = sizeof(IAUDDEC1_Params);
	G->adec1.adecStatus.size = sizeof(IAUDDEC1_Status);
	G->adec1.adecDynParams.size = sizeof(IAUDDEC1_DynamicParams);
	G->adec1.adecInArgs.size = sizeof(IAUDDEC1_InArgs);
	G->adec1.adecOutArgs.size = sizeof(IAUDDEC1_OutArgs);
	G->adec1.lfeFlag = 0;

	G->mp3basedec1.adecParams.size = sizeof(IAUDDEC1_Params);
	G->mp3basedec1.adecStatus.size = sizeof(IAUDDEC1_Status);
	G->mp3basedec1.adecDynParams.size = sizeof(IAUDDEC1_DynamicParams);
	G->mp3basedec1.adecInArgs.size = sizeof(IAUDDEC1_InArgs);
	G->mp3basedec1.adecOutArgs.size = sizeof(IAUDDEC1_OutArgs);

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
	G->aaclcenc1.aacenc1Params.audenc_params.size = sizeof(IAACENC_Params);
	G->aaclcenc1.aacenc1Status.audenc_status.size = sizeof(IAACENC_Status);
	G->aaclcenc1.aacenc1DynParams.audenc_dynamicparams.size = sizeof(IAACENC_DynamicParams);
	G->aaclcenc1.aacenc1InArgs.audenc_inArgs.size = sizeof(IAACENC_InArgs);
	G->aaclcenc1.aacenc1OutArgs.audenc_outArgs.size = sizeof(IAACENC_OutArgs);

	G->aacheenc1.aacenc1Params.audenc_params.size = sizeof(IAACENC_Params);
	G->aacheenc1.aacenc1Status.audenc_status.size = sizeof(IAACENC_Status);
	G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.size = sizeof(IAACENC_DynamicParams);
	G->aacheenc1.aacenc1InArgs.audenc_inArgs.size = sizeof(IAACENC_InArgs);
	G->aacheenc1.aacenc1OutArgs.audenc_outArgs.size = sizeof(IAACENC_OutArgs);
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 1.2 Base     ***************************************************************/
	/************************************************************************************************/
	G->vdec2.vdec2Params.size = sizeof(VIDDEC2_Params);
	G->vdec2.vdec2Status.size = sizeof(VIDDEC2_Status);
	G->vdec2.vdec2DynParams.size = sizeof(VIDDEC2_DynamicParams);
	G->vdec2.vdec2InArgs.size = sizeof(VIDDEC2_InArgs);
	G->vdec2.vdec2OutArgs.size = sizeof(VIDDEC2_OutArgs);
	/************************************************************************************************/

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_initApp(void)
{
	DvevmStRetCode rc = DVEVM_ST_FAIL;

	dvtb_ceRuntimeInit(&G->eng);
	rc = dvtb_initParams( );
	return rc;
}
