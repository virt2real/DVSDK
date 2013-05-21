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

#ifdef _DVTB_NONTSPA_ 
#define SETP_USAGE  SYS_ERROR("Usage: setp <auddec|sphenc|sphdec|videnc1|aachedec1|mp3basedec1|aacheenc1|h264enc1|h264fhdenc1|viddec2|h264dec2|h2641080pdec2|mpeg2dec2|mpeg4dec2|imgenc1|imgdec1|aacenc|jpegdec1|jpegenc1|ac3dec1> [option] [value] \n")
#else
#define SETP_USAGE  SYS_ERROR("Usage: setp <auddec|sphenc|sphdec|videnc1|aachedec1|mp3basedec1|h264fhdenc1|viddec2|h2641080pdec2|mpeg2dec2|mpeg4dec2|imgenc1|imgdec1|aacenc|jpegdec1|jpegenc1> [option] [value] \n")
#endif


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
	G->vpbe.setupFxn.openV4l2Osd = (DvevmStRetCode(*)(void *)) NULL;
	G->vpbe.setupFxn.ioctlV4l2Osd = (DvevmStRetCode(*)(void *, unsigned int, void *)) NULL;
	G->vpbe.setupFxn.setV4l2Fmt = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2OutputFmtOverride;
	G->vpbe.setupFxn.initV4l2OutputMmapBuffs = (DvevmStRetCode(*)(void *)) dvtb_initV4l2OutputMmapBuffs;
	G->vpbe.setupFxn.initV4l2OutputUserBuffs = (DvevmStRetCode(*)(void *)) dvtb_initV4l2OutputUserBuffs;
	G->vpbe.setupFxn.setV4l2PreFmtConfiguration = (DvevmStRetCode(*)(void *)) NULL;
	G->vpbe.setupFxn.setV4l2PostFmtConfiguration = (DvevmStRetCode(*)(void *)) NULL;

	G->vpbe.qBuffFxn.setV4l2UserBuffConfig = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2UserBuffConfig;
	G->vpbe.qBuffFxn.setV4l2MmapBuffConfig = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2MmapBuffConfig;

	G->vpbe.dqBuffFxn.getV4l2UserBuff = (void* (*)(void *)) dvtb_getV4l2UserBuff;
	G->vpbe.dqBuffFxn.getV4l2MmapBuff = (void* (*)(void *)) dvtb_getV4l2MmapBuff;

	G->idec1.dvtb_ptrAllocCmem = &dvtb_allocCmem;
	G->idec1.dvtb_ptrFreeCmem = &dvtb_freeCmem;

	G->vpbe.pixelformat = VID_FMT_YUV422UVP;
	G->vpbe.opMode = 0;
	G->aud.framesize = 0;
	dvtb_vpbeSetupPtr = &dvtb_vpbeSetup;
	dvtb_audioSetControlContentsPtr = NULL;
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 0.9 Base     ***************************************************************/
	/************************************************************************************************/
	G->aenc.aencParams.size = sizeof(IAUDENC_Params);
	G->aenc.aencDynParams.size = sizeof(AUDENC_DynamicParams);
	G->aenc.aencStatus.size = sizeof(AUDENC_Status);

	G->adec.adecParams.size = sizeof(IAUDDEC_Params);
	G->adec.adecDynParams.size = sizeof(AUDDEC_DynamicParams);
	G->adec.adecStatus.size = sizeof(AUDDEC_Status);

	G->senc.sencParams.size = sizeof(SPHENC_Params);
	G->senc.sencDynParams.size = sizeof(SPHENC_DynamicParams);
	G->senc.sencStatus.size = sizeof(SPHENC_Status);
	G->senc.sencInArgs.size = sizeof(SPHENC_InArgs);
	G->senc.sencOutArgs.size = sizeof(SPHENC_OutArgs);

	G->sdec.sdecParams.size = sizeof(SPHDEC_Params);
	G->sdec.sdecDynParams.size = sizeof(SPHDEC_DynamicParams);
	G->sdec.sdecStatus.size = sizeof(SPHDEC_Status);
	G->sdec.sdecInArgs.size = sizeof(SPHDEC_InArgs);
	G->sdec.sdecOutArgs.size = sizeof(SPHDEC_OutArgs);
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 0.9 Extended     ***********************************************************/
	/************************************************************************************************/
#if 0
	G->aacenc.aencParams.audenc_params.size = sizeof(IAACENC_Params);
	G->aacenc.aencDynParams.audenc_dynamicparams.size = sizeof(IAACENC_DynamicParams);
	G->aacenc.aencStatus.audenc_status.size = sizeof(IAACENC_Status);
	G->aacenc.aencInArgs.audenc_inArgs.size = sizeof(IAACENC_InArgs);
	G->aacenc.aencOutArgs.audenc_outArgs.size = sizeof(IAACENC_OutArgs);
#endif
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 1.0 Base     ***************************************************************/
	/************************************************************************************************/
	G->venc1.venc1Params.size = sizeof(VIDENC1_Params);
	G->venc1.venc1DynParams.size = sizeof(VIDENC1_DynamicParams);
	G->venc1.venc1Status.size = sizeof(VIDENC1_Status);
	G->venc1.venc1InArgs.size = sizeof(VIDENC1_InArgs);
	G->venc1.venc1OutArgs.size = sizeof(VIDENC1_OutArgs);

	G->aenc1.audenc1Params.size = sizeof(IAUDENC1_Params);
	G->aenc1.audenc1DynParams.size = sizeof(IAUDENC1_DynamicParams);
	G->aenc1.audenc1Status.size = sizeof(IAUDENC1_Status);
	G->aenc1.audenc1InArgs.size = sizeof(IAUDENC1_InArgs);
	G->aenc1.audenc1OutArgs.size = sizeof(IAUDENC1_OutArgs);
	G->aenc1.InSamplesPerChannel = AUDENC1_FRAME_SIZE;

	G->adec1.adecParams.size = sizeof(IAUDDEC1_Params);
	G->adec1.adecDynParams.size = sizeof(IAUDDEC1_DynamicParams);
	G->adec1.adecStatus.size = sizeof(IAUDDEC1_Status);
	G->adec1.adecInArgs.size = sizeof(IAUDDEC1_InArgs);
	G->adec1.adecOutArgs.size = sizeof(IAUDDEC1_OutArgs);
	G->adec1.lfeFlag = 0;

	G->mp3basedec1.adecParams.size = sizeof(IAUDDEC1_Params);
	G->mp3basedec1.adecStatus.size = sizeof(AUDDEC1_Status);
	G->mp3basedec1.adecDynParams.size = sizeof(AUDDEC1_DynamicParams);
	G->mp3basedec1.adecInArgs.size = sizeof(AUDDEC1_InArgs);
	G->mp3basedec1.adecOutArgs.size = sizeof(AUDDEC1_OutArgs);


	G->senc1.sencParams.size = sizeof(SPHENC1_Params);
	G->senc1.sencDynParams.size = sizeof(SPHENC1_DynamicParams);
	G->senc1.sencStatus.size = sizeof(SPHENC1_Status);
	G->senc1.sencInArgs.size = sizeof(SPHENC1_InArgs);
	G->senc1.sencOutArgs.size = sizeof(SPHENC1_OutArgs);

	G->sdec1.sdecParams.size = sizeof(SPHDEC1_Params);
	G->sdec1.sdecDynParams.size = sizeof(SPHDEC1_DynamicParams);
	G->sdec1.sdecStatus.size = sizeof(SPHDEC1_Status);
	G->sdec1.sdecInArgs.size = sizeof(SPHDEC1_InArgs);
	G->sdec1.sdecOutArgs.size = sizeof(SPHDEC1_OutArgs);

	G->idec1.idec1Params.size = sizeof(IMGDEC1_Params);
	G->idec1.idec1Status.size = sizeof(IMGDEC1_Status);
	G->idec1.idec1DynParams.size = sizeof(IMGDEC1_DynamicParams);
	G->idec1.idec1InArgs.size = sizeof(IMGDEC1_InArgs);
	G->idec1.idec1OutArgs.size = sizeof(IMGDEC1_OutArgs);

	G->ienc1.ienc1Params.size = sizeof(IMGENC1_Params);
	G->ienc1.ienc1Status.size = sizeof(IMGENC1_Status);
	G->ienc1.ienc1DynParams.size = sizeof(IMGENC1_DynamicParams);
	G->ienc1.ienc1InArgs.size = sizeof(IMGENC1_InArgs);
	G->ienc1.ienc1OutArgs.size = sizeof(IMGENC1_OutArgs);
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 1.0 Extended     ***********************************************************/
	/************************************************************************************************/

	G->h264enc1.venc1Params.videncParams.size = sizeof(IH264VENC_Params);
	G->h264enc1.venc1DynParams.videncDynamicParams.size = sizeof(IH264VENC_DynamicParams);
	G->h264enc1.venc1Status.videncStatus.size = sizeof(IH264VENC_Status);
	G->h264enc1.venc1InArgs.videncInArgs.size = sizeof(IH264VENC_InArgs);
	G->h264enc1.venc1OutArgs.videncOutArgs.size = sizeof(IH264VENC_OutArgs);

	G->h264fhdenc1.venc1Params.videncParams.size = sizeof(IH264FHDVENC_Params);
	G->h264fhdenc1.venc1DynParams.videncDynamicParams.size = sizeof(IH264FHDVENC_DynamicParams);
	G->h264fhdenc1.venc1Status.videncStatus.size = sizeof(IH264FHDVENC_Status);
	G->h264fhdenc1.venc1InArgs.videncInArgs.size = sizeof(IH264FHDVENC_InArgs);
	G->h264fhdenc1.venc1OutArgs.videncOutArgs.size = sizeof(IH264FHDVENC_OutArgs);
	G->h264fhdenc1.venc1DynParams.VUIData.buf = NULL;
	G->h264fhdenc1.venc1DynParams.VUIData.bufSize = 0;
	G->h264fhdenc1.venc1DynParams.NALUnitCallback = NULL;
	

	G->mpeg4enc1.venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
	G->mpeg4enc1.venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
	G->mpeg4enc1.venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);
	G->mpeg4enc1.venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
	G->mpeg4enc1.venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);

	G->aachedec1.adecParams.auddec_params.size = sizeof(IAACDEC_Params);
	G->aachedec1.adecDynParams.auddec_dynamicparams.size = sizeof(IAACDEC_DynamicParams);
	G->aachedec1.adecStatus.auddec_status.size = sizeof(IAACDEC_Status);
	G->aachedec1.adecInArgs.auddec_inArgs.size = sizeof(IAACDEC_InArgs);
	G->aachedec1.adecOutArgs.auddec_outArgs.size = sizeof(IAACDEC_OutArgs);

#ifdef _DVTB_NONTSPA_
	G->aacheenc1.aacenc1Params.audenc_params.size = sizeof(IAACENC_Params);
	G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.size = sizeof(IAACENC_DynamicParams);
	G->aacheenc1.aacenc1Status.audenc_status.size = sizeof(IAACENC_Status);
	G->aacheenc1.aacenc1InArgs.audenc_inArgs.size = sizeof(IAACENC_InArgs);
	G->aacheenc1.aacenc1OutArgs.audenc_outArgs.size = sizeof(IAACENC_OutArgs);

	G->ac3dec1.adecParams.auddec_params.size = sizeof(IDOLBYAC3DEC_Params);
	G->ac3dec1.adecDynParams.auddec_dynamicparams.size = sizeof(IDOLBYAC3DEC_DynamicParams);
	G->ac3dec1.adecStatus.auddec_status.size = sizeof(IDOLBYAC3DEC_Status);
	G->ac3dec1.adecInArgs.auddec_inArgs.size = sizeof(IDOLBYAC3DEC_InArgs);
	G->ac3dec1.adecOutArgs.auddec_outArgs.size = sizeof(IDOLBYAC3DEC_OutArgs);
#endif

	G->jpegdec1.idec1Params.imgdecParams.size = sizeof(IJPEGDEC_Params);
	G->jpegdec1.idec1Status.imgdecStatus.size = sizeof(IJPEGDEC_Status);
	G->jpegdec1.idec1DynParams.imgdecDynamicParams.size = sizeof(IJPEGDEC_DynamicParams);
	G->jpegdec1.idec1InArgs.imgdecInArgs.size = sizeof(IJPEGDEC_InArgs);
	G->jpegdec1.idec1OutArgs.imgdecOutArgs.size = sizeof(IJPEGDEC_OutArgs);

	G->jpegenc1.ienc1Params.params.size = sizeof(IDMJPGE_TIGEM_Params);
	G->jpegenc1.ienc1DynParams.params.size = sizeof(IDMJPGE_TIGEM_DynamicParams);
	G->jpegenc1.ienc1InArgs.inArgs.size = sizeof(IDMJPGE_TIGEM_InArgs);
	G->jpegenc1.ienc1OutArgs.outArgs.size = sizeof(IDMJPGE_TIGEM_OutArgs);
	G->jpegenc1.ienc1Status.status.size = sizeof(IDMJPGE_TIGEM_Status);
	G->jpegenc1.ienc1DynParams.quantTable = NULL;
	G->jpegenc1.commentBuff = NULL;
//	memcpy(&G->jpegenc1.commentBuff[0],"DVTB Jpeg Encoder",17);
//	G->jpegenc1.commentBuff[17] ='\0';
//	G->jpegenc1.ienc1DynParams.huffmanTable = NULL;
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 1.2 Base     ***************************************************************/
	/************************************************************************************************/
	G->vdec2.vdec2Params.size = sizeof(VIDDEC2_Params);
	G->vdec2.vdec2DynParams.size = sizeof(VIDDEC2_DynamicParams);
	G->vdec2.vdec2Status.size = sizeof(VIDDEC2_Status);
	G->vdec2.vdec2InArgs.size = sizeof(VIDDEC2_InArgs);
	G->vdec2.vdec2OutArgs.size = sizeof(VIDDEC2_OutArgs);
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 1.2 Extended     ***********************************************************/
	/************************************************************************************************/
#ifdef _DVTB_H264DEC_
	G->h264dec2.vdec2Params.viddecParams.size = sizeof(IH264VDEC_Params);
	G->h264dec2.vdec2DynParams.viddecDynamicParams.size = sizeof(IH264VDEC_DynamicParams);
	G->h264dec2.vdec2Status.viddecStatus.size = sizeof(IH264VDEC_Status);
	G->h264dec2.vdec2InArgs.viddecInArgs.size = sizeof(IH264VDEC_InArgs);
	G->h264dec2.vdec2OutArgs.viddecOutArgs.size = sizeof(IH264VDEC_OutArgs);

#endif

#ifdef _DVTB_H2641080p60VDEC_
	G->h2641080pdec2.vdec2Params.viddecParams.size = sizeof(IH2641080P60VDEC_Params);
	G->h2641080pdec2.vdec2DynParams.viddecDynamicParams.size = sizeof(IH2641080P60VDEC_DynamicParams);
	G->h2641080pdec2.vdec2Status.viddecStatus.size = sizeof(IH2641080P60VDEC_Status);
	G->h2641080pdec2.vdec2InArgs.viddecInArgs.size = sizeof(IH2641080P60VDEC_InArgs);
	G->h2641080pdec2.vdec2OutArgs.viddecOutArgs.size = sizeof(IH2641080P60VDEC_OutArgs);
#endif

	G->mpeg2dec2.vdec2Params.viddecParams.size = sizeof(Imp2VDEC_Params);
	G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.size = sizeof(Imp2VDEC_DynamicParams);
	G->mpeg2dec2.vdec2Status.viddecStatus.size = sizeof(Imp2VDEC_Status);
	G->mpeg2dec2.vdec2InArgs.viddecInArgs.size = sizeof(Imp2VDEC_InArgs);
	G->mpeg2dec2.vdec2OutArgs.viddecOutArgs.size = sizeof(Imp2VDEC_OutArgs);

	G->mpeg4dec2.vdec2Params.viddecParams.size = sizeof(Imp4VDEC_Params);
	G->mpeg4dec2.vdec2DynParams.viddecDynamicParams.size = sizeof(Imp4VDEC_DynamicParams);
	G->mpeg4dec2.vdec2Status.viddecStatus.size = sizeof(Imp4VDEC_Status);
	G->mpeg4dec2.vdec2InArgs.viddecInArgs.size = sizeof(Imp4VDEC_InArgs);
	G->mpeg4dec2.vdec2OutArgs.viddecOutArgs.size = sizeof(Imp4VDEC_OutArgs);
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
