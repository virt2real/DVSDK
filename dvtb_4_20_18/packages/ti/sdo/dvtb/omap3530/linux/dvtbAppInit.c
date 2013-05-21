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
#include "dvtbALSAControlContent.h"

#define SETP_USAGE  SYS_ERROR("Usage: setp <global|auddec|spcenc|spcdec|videnc|viddec|viddec2|videnc1|imgenc1|h264enc1|h264dec2|mpeg4spenc1|mpeg4spdec2|mpeg2dec2|aachedec1|jpegenc1> [option] [value]\n")

DvevmStGlobalParams dvevmStGlobalParams;
DvevmStGlobalParams *G = &dvevmStGlobalParams;

DvevmStRetCode dvtb_initParams()
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
	G->vpbe.setupFxn.openV4l2Osd = (DvevmStRetCode(*)(void *)) NULL;
	G->vpbe.setupFxn.ioctlV4l2Osd = (DvevmStRetCode(*)(void *, unsigned int, void *)) NULL;
	G->vpbe.setupFxn.setV4l2Fmt = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2OutputFmtOverride;
	G->vpbe.setupFxn.initV4l2OutputMmapBuffs = (DvevmStRetCode(*)(void *)) dvtb_initV4l2OutputMmapBuffs;
	G->vpbe.setupFxn.initV4l2OutputUserBuffs = (DvevmStRetCode(*)(void *)) dvtb_initV4l2OutputUserBuffsOverride;
	G->vpbe.setupFxn.setV4l2PreFmtConfiguration = (DvevmStRetCode(*)(void *)) dvtb_setV4l2PreFmtConfiguration;
	G->vpbe.setupFxn.setV4l2PostFmtConfiguration = (DvevmStRetCode(*)(void *)) dvtb_setV4l2PostFmtConfiguration;

	G->vpbe.qBuffFxn.setV4l2UserBuffConfig = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2UserBuffConfigOverride;
	G->vpbe.qBuffFxn.setV4l2MmapBuffConfig = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2MmapBuffConfig;

	G->vpbe.dqBuffFxn.getV4l2UserBuff = (void* (*)(void *)) dvtb_getV4l2UserBuff;
	G->vpbe.dqBuffFxn.getV4l2MmapBuff = (void* (*)(void *)) dvtb_getV4l2MmapBuff;

	G->aud.framesize = 0;
	G->vpfe.opMode = DVEVM_ST_USERBUFFER;

	G->vpbe.pixelformat = VID_FMT_UYVY;
	G->vpbe.opMode = 0;
	G->vpbe.maxBuffers = 3;
	G->idec1.dvtb_ptrAllocCmem = &dvtb_allocCmem;
	G->idec1.dvtb_ptrFreeCmem = &dvtb_freeCmem;
	dvtb_vpbeSetupPtr = &dvtb_vpbeSetup;
	dvtb_audioSetControlContentsPtr = &dvtb_audioSetControlContents;
	/************************************************************************************************/



	/************************************************************************************************/
	/***********     Universal Codec  ***************************************************************/
	/************************************************************************************************/
	G->deinter.deinterParams.size                     = sizeof(II2P_Params);
	G->deinter.deinterDynParams.size                  = sizeof(UNIVERSAL_DynamicParams);
	G->deinter.deinterInArgs.universalInArgs.size     = sizeof(IDEINTER_InArgs);
	G->deinter.deinterOutArgs.universalOutArgs.size   = sizeof(IDEINTER_OutArgs);
	G->deinter.deinterStatus.size                     = sizeof(UNIVERSAL_Status);
	G->deinter.deinterHdl                             = NULL;
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
	G->adec1.lfeFlag = 0;

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

	G->h264enc1.venc1Params.videncParams.size = sizeof(IH264VENC_Params);
	G->h264enc1.venc1DynParams.videncDynamicParams.size = sizeof(IH264VENC_DynamicParams);
	G->h264enc1.venc1Status.videncStatus.size = sizeof(IH264VENC_Status);
	G->h264enc1.venc1InArgs.videncInArgs.size = sizeof(IH264VENC_InArgs);
	G->h264enc1.venc1OutArgs.videncOutArgs.size = sizeof(IH264VENC_OutArgs);
	G->h264enc1.venc1DynParams.pfNalUnitCallBack = NULL;

        G->mpeg4spenc1.venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
        G->mpeg4spenc1.venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
        G->mpeg4spenc1.venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
        G->mpeg4spenc1.venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);
        G->mpeg4spenc1.venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);

        G->aachedec1.adecParams.auddec_params.size = sizeof(IAACDEC_Params);
        G->aachedec1.adecDynParams.auddec_dynamicparams.size = sizeof(IAACDEC_DynamicParams);
        G->aachedec1.adecStatus.auddec_status.size = sizeof(IAACDEC_Status);
        G->aachedec1.adecInArgs.auddec_inArgs.size = sizeof(IAACDEC_InArgs);
        G->aachedec1.adecOutArgs.auddec_outArgs.size = sizeof(IAACDEC_OutArgs);

        G->jpegenc1.ienc1Params.params.size = sizeof(IDMJPGE_TIGEM_Params);
        G->jpegenc1.ienc1DynParams.params.size = sizeof(IDMJPGE_TIGEM_DynamicParams);
        G->jpegenc1.ienc1InArgs.inArgs.size = sizeof(IDMJPGE_TIGEM_InArgs);
        G->jpegenc1.ienc1OutArgs.outArgs.size = sizeof(IDMJPGE_TIGEM_OutArgs);
        G->jpegenc1.ienc1Status.status.size = sizeof(IDMJPGE_TIGEM_Status);
	G->jpegenc1.ienc1DynParams.quantTable = NULL;
//	G->jpegenc1.ienc1DynParams.huffmanTable = NULL;

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

	/************************************************************************************************/
	/***********     XDM 1.2 Extended     ***********************************************************/
	/************************************************************************************************/
	G->h264dec2.vdec2Params.viddecParams.size = sizeof(IH264VDEC_Params);
	G->h264dec2.vdec2DynParams.viddecDynamicParams.size = sizeof(IH264VDEC_DynamicParams);
	G->h264dec2.vdec2Status.viddecStatus.size = sizeof(IH264VDEC_Status);
	G->h264dec2.vdec2InArgs.viddecInArgs.size = sizeof(IH264VDEC_InArgs);
	G->h264dec2.vdec2OutArgs.viddecOutArgs.size = sizeof(IH264VDEC_OutArgs);

        G->mpeg4spdec2.mpeg4sp_vdecParams.viddecParams.size = sizeof(IM4H3DEC_Params);
        G->mpeg4spdec2.mpeg4sp_vdecDynParams.viddecDynamicParams.size = sizeof(IM4H3DEC_DynamicParams);
        G->mpeg4spdec2.mpeg4sp_vdecStatus.viddecStatus.size = sizeof(IM4H3DEC_Status);
        G->mpeg4spdec2.mpeg4sp_vdecInArgs.viddecInArgs.size = sizeof(IM4H3DEC_InArgs);
        G->mpeg4spdec2.mpeg4sp_vdecOutArgs.viddecOutArgs.size = sizeof(IM4H3DEC_OutArgs);

        G->mpeg2dec2.vdec2Params.viddecParams.size = sizeof(IMPEG2VDEC_Params);
        G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.size = sizeof(IMPEG2VDEC_DynamicParams);
        G->mpeg2dec2.vdec2Status.viddecStatus.size = sizeof(IMPEG2VDEC_Status);
        G->mpeg2dec2.vdec2InArgs.viddecInArgs.size = sizeof(IMPEG2VDEC_InArgs);
        G->mpeg2dec2.vdec2OutArgs.viddecOutArgs.size = sizeof(IMPEG2VDEC_OutArgs);
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
