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
#include "dvtbV4L2VPBEFeatures.h"

#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/linuxutils/cmem/include/cmem.h>

#include <ti/sdo/fc/ires/memtcm/ires_memtcm.h>
#include <ti/sdo/fc/ires/memtcm/iresman_memtcm.h>

#define SETP_USAGE  SYS_ERROR("Usage: setp <sphdec|sphenc|videnc1|mpeg4enc1|mpeg4hdvicpenc1|h264enc1|viddec2|mpeg4dec2|mpeg4hdvicpdec2|h264dec2|imgenc1|jpegenc1|imgdec1|jpegdec1|sphenc|sphdec|mpeg2dec2|mpeg2enc1|vc1dec2|auddec1|audenc1|aachedec1|aaclcenc1|mp3dec1|mp3enc1|wmadec1|wmaenc1> [option] [value]\n")

DvevmStRetCode dvtb_initParams(void);

DvevmStGlobalParams dvevmStGlobalParams;
DvevmStGlobalParams *G = &dvevmStGlobalParams;

DvevmStRetCode
dvtb_initApp(void)
{
	DvevmStRetCode rc = DVEVM_ST_FAIL;
	IRESMAN_MemTcmParams memTcmConfigParams;

	dvtb_ceRuntimeInit(&G->eng);

	CMEM_init( );

	rc = dvtb_initParams( );
	ASSERT(rc != DVEVM_ST_FAIL);

	if (RMAN_init( ) != IRES_OK)
	{
		SYS_ERROR("Cannot Init RMAN.\n");
		return DVEVM_ST_FAIL;
	} else
		SYS_OUT("RMAN initialized.\n");

	/*
	 * Register IRES components
	 */
	memTcmConfigParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
	memTcmConfigParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
	memTcmConfigParams.baseConfig.size = sizeof(IRESMAN_MemTcmParams);;

	if (RMAN_register(&IRESMAN_MEMTCM, (IRESMAN_Params *) &memTcmConfigParams) != IRES_OK)
	{
		SYS_ERROR("MEMTCM Protocol Registration Failed \n");
		return DVEVM_ST_FAIL;
	}
	SYS_DEBUG("MEMTCM Protocol Registration Success \n");

	return DVEVM_ST_SUCCESS;
}

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
	G->vpbe.setupFxn.setV4l2Fmt = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2OutputFmt;
	G->vpbe.setupFxn.initV4l2OutputMmapBuffs = (DvevmStRetCode(*)(void *)) dvtb_initV4l2OutputMmapBuffs;
	G->vpbe.setupFxn.initV4l2OutputUserBuffs = (DvevmStRetCode(*)(void *)) dvtb_initV4l2OutputUserBuffs;
	G->vpbe.setupFxn.setV4l2PreFmtConfiguration = (DvevmStRetCode(*)(void *)) dvtb_PreFmtConfiguration;
	G->vpbe.setupFxn.setV4l2PostFmtConfiguration = (DvevmStRetCode(*)(void *)) NULL;

	G->vpbe.qBuffFxn.setV4l2UserBuffConfig = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2UserBuffConfig;
	G->vpbe.qBuffFxn.setV4l2MmapBuffConfig = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2MmapBuffConfig;

	G->vpbe.dqBuffFxn.getV4l2UserBuff = (void* (*)(void *)) dvtb_getV4l2UserBuff;
	G->vpbe.dqBuffFxn.getV4l2MmapBuff = (void* (*)(void *)) dvtb_getV4l2MmapBuff;

	G->vpbe.xres = G->vpbe.imageWidth;
	G->vpbe.yres = G->vpbe.imageHeight;
	G->vpbe.pixelformat = VID_FMT_YUV420SP;

	G->vpbe.buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	G->vpbe.req.count = MIN_DISPLAY_BUFFERS;

	G->vpfe.field = V4L2_FIELD_INTERLACED;
	G->vpfe.hdCapStdIndex = 0; // initialized for 720P capture. Need to be changed as per requirments.

	G->vpfe.crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	G->vpbe.crop.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;

	G->aud.framesize = 0;

	G->vpRsz.rsz_fd = DVEVM_ST_FALSE;
	G->vpPrvw.preview_fd = DVEVM_ST_FALSE;

	G->idec1.dvtb_ptrAllocCmem = dvtb_allocCmemSingleChunk;
	G->idec1.dvtb_ptrFreeCmem = dvtb_freeCmemSingleChunk;

	strcpy(G->vpRsz.resizeDevice, VIDRESIZE_DEVICE);
	strcpy(G->vpPrvw.previewDevice, VIDPREVIEW_DEVICE);

	dvtb_vpbeSetupPtr = &dvtb_vpbeSetup;
	dvtb_audioSetControlContentsPtr = NULL;

	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 0.9 Base     ***************************************************************/
	/************************************************************************************************/
//	G->sdec.sdecParams.size = sizeof(SPHDEC_Params);
//	G->sdec.sdecStatus.size = sizeof(SPHDEC_Status);
//	G->sdec.sdecDynParams.size = sizeof(SPHDEC_DynamicParams);
//	G->sdec.sdecInArgs.size = sizeof(SPHDEC_InArgs);
//	G->sdec.sdecOutArgs.size = sizeof(SPHDEC_OutArgs);

//	G->senc.sencParams.size = sizeof(SPHENC_Params);
//	G->senc.sencStatus.size = sizeof(SPHENC_Status);
//	G->senc.sencDynParams.size = sizeof(SPHENC_DynamicParams);
//	G->senc.sencInArgs.size = sizeof(SPHENC_InArgs);
//	G->senc.sencOutArgs.size = sizeof(SPHENC_OutArgs);
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 1.0 Base     ***************************************************************/
	/************************************************************************************************/
	G->venc1.venc1Params.size = sizeof(VIDENC1_Params);
	G->venc1.venc1Status.size = sizeof(VIDENC1_Status);
	G->venc1.venc1DynParams.size = sizeof(VIDENC1_DynamicParams);
	G->venc1.venc1InArgs.size = sizeof(VIDENC1_InArgs);
	G->venc1.venc1OutArgs.size = sizeof(VIDENC1_OutArgs);

	G->aenc1.audenc1Params.size = sizeof(IAUDENC1_Params);
	G->aenc1.audenc1DynParams.size = sizeof(IAUDENC1_DynamicParams);
	G->aenc1.audenc1Status.size = sizeof(IAUDENC1_Status);
	G->aenc1.audenc1InArgs.size = sizeof(IAUDENC1_InArgs);
	G->aenc1.audenc1OutArgs.size = sizeof(IAUDENC1_OutArgs);
	
	G->adec1.adecParams.size = sizeof(IAUDDEC1_Params);
	G->adec1.adecDynParams.size = sizeof(IAUDDEC1_DynamicParams);
	G->adec1.adecStatus.size = sizeof(IAUDDEC1_Status);
	G->adec1.adecInArgs.size = sizeof(IAUDDEC1_InArgs);
	G->adec1.adecOutArgs.size = sizeof(IAUDDEC1_OutArgs);

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
	G->jpegenc1.ienc1Params.imgencParams.size = sizeof(IJPEGENC_Params);
	G->jpegenc1.ienc1DynParams.imgencDynamicParams.size = sizeof(IJPEGENC_DynamicParams);
	G->jpegenc1.ienc1InArgs.imgencInArgs.size = sizeof(IJPEGENC_InArgs);
	G->jpegenc1.ienc1OutArgs.imgencOutArgs.size = sizeof(IJPEGENC_OutArgs);
	G->jpegenc1.ienc1Status.imgencStatus.size = sizeof(IJPEGENC_Status);

	G->jpegdec1.idec1Params.imgdecParams.size = sizeof(IJPEGDEC_Params);
	G->jpegdec1.idec1DynParams.imgdecDynamicParams.size = sizeof(IJPEGDEC_DynamicParams);
	G->jpegdec1.idec1InArgs.imgdecInArgs.size = sizeof(IJPEGDEC_InArgs);
	G->jpegdec1.idec1OutArgs.imgdecOutArgs.size = sizeof(IJPEGDEC_OutArgs);
	G->jpegdec1.idec1Status.imgdecStatus.size = sizeof(IJPEGDEC_Status);

	G->h264enc1.venc1Params.videncParams.size = sizeof(IH264VENC_Params);
	G->h264enc1.venc1Status.videncStatus.size = sizeof(IH264VENC_Status);
	G->h264enc1.venc1DynParams.videncDynamicParams.size = sizeof(IH264VENC_DynamicParams);
	G->h264enc1.venc1InArgs.videncInArgs.size = sizeof(IH264VENC_InArgs);
	G->h264enc1.venc1OutArgs.videncOutArgs.size = sizeof(IH264VENC_OutArgs);
	G->h264enc1.venc1DynParams.VUI_Buffer = NULL;
	G->h264enc1.venc1DynParams.CustomScaleMatrix_Buffer = NULL;
	G->h264enc1.venc1DynParams.putDataGetSpaceFxn = NULL;
	G->h264enc1.venc1DynParams.dataSyncHandle = NULL;
	
	G->mpeg4enc1.venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
	G->mpeg4enc1.venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);
	G->mpeg4enc1.venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
	G->mpeg4enc1.venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
	G->mpeg4enc1.venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);

	G->mpeg4hdvicpenc1.venc1Params.videncParams.size = sizeof(IMP4HDVICPENC_Params);
	G->mpeg4hdvicpenc1.venc1Status.videncStatus.size = sizeof(IMP4HDVICPENC_Status);
	G->mpeg4hdvicpenc1.venc1DynParams.videncDynamicParams.size = sizeof(IMP4HDVICPENC_DynamicParams);
	G->mpeg4hdvicpenc1.venc1InArgs.videncInArgs.size = sizeof(IMP4HDVICPENC_InArgs);
	G->mpeg4hdvicpenc1.venc1OutArgs.videncOutArgs.size = sizeof(IMP4HDVICPENC_OutArgs);
	G->mpeg4hdvicpenc1.venc1Params.hdvicpHandle = NULL;

	G->mpeg2enc1.venc1Params.videncParams.size = sizeof(IMP2VENC_Params);
	G->mpeg2enc1.venc1Status.videncStatus.size = sizeof(IMP2VENC_Status);
	G->mpeg2enc1.venc1DynParams.videncDynamicParams.size = sizeof(IMP2VENC_DynamicParams);
	G->mpeg2enc1.venc1InArgs.videncInArgs.size = sizeof(IMP2VENC_InArgs);
	G->mpeg2enc1.venc1OutArgs.videncOutArgs.size = sizeof(IMP2VENC_OutArgs);
	G->mpeg2enc1.venc1Params.hdvicpHandle = NULL;	

	G->aachedec1.adecParams.auddec_params.size = sizeof(IAACDEC_Params);
	G->aachedec1.adecDynParams.auddec_dynamicparams.size = sizeof(IAACDEC_DynamicParams);
	G->aachedec1.adecStatus.auddec_status.size = sizeof(IAACDEC_Status);
	G->aachedec1.adecInArgs.auddec_inArgs.size = sizeof(IAACDEC_InArgs);
	G->aachedec1.adecOutArgs.auddec_outArgs.size = sizeof(IAACDEC_OutArgs);

        G->aacheenc1.aacenc1Params.audenc_params.size = sizeof(ITTIAM_EAACPLUSENC_Params);
        G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.size = sizeof(ITTIAM_EAACPLUSENC_DynamicParams);
        G->aacheenc1.aacenc1Status.audenc_status.size = sizeof(ITTIAM_EAACPLUSENC_Status);
        G->aacheenc1.aacenc1InArgs.audenc_inArgs.size = sizeof(ITTIAM_EAACPLUSENC_InArgs);
        G->aacheenc1.aacenc1OutArgs.audenc_outArgs.size = sizeof(ITTIAM_EAACPLUSENC_OutArgs);
	G->aacheenc1.outObjectType = AACENC_OBJ_TYP_LC;

	G->mp3dec1.adecParams.auddec_params.size = sizeof(ITTIAM_MP3DEC_Params);
	G->mp3dec1.adecDynParams.auddec_dynamicparams.size = sizeof(ITTIAM_MP3DEC_DynamicParams);
	G->mp3dec1.adecStatus.auddec_status.size = sizeof(ITTIAM_MP3DEC_Status);
	G->mp3dec1.adecInArgs.auddec_inArgs.size = sizeof(ITTIAM_MP3DEC_InArgs);
	G->mp3dec1.adecOutArgs.auddec_outArgs.size = sizeof(ITTIAM_MP3DEC_OutArgs);

        G->mp3enc1.aenc1Params.audenc_params.size = sizeof(ITTIAM_MP3ENC_Params);
        G->mp3enc1.aenc1DynParams.audenc_dynamicparams.size = sizeof(ITTIAM_MP3ENC_DynamicParams);
        G->mp3enc1.aenc1Status.audenc_status.size = sizeof(ITTIAM_MP3ENC_Status);
        G->mp3enc1.aenc1InArgs.audenc_inArgs.size = sizeof(ITTIAM_MP3ENC_InArgs);
        G->mp3enc1.aenc1OutArgs.audenc_outArgs.size = sizeof(ITTIAM_MP3ENC_OutArgs);

	G->wmadec1.adecParams.auddec_params.size = sizeof(ITTIAM_WMADEC_Params);
	G->wmadec1.adecDynParams.auddec_dynamicparams.size = sizeof(ITTIAM_WMADEC_DynamicParams);
	G->wmadec1.adecStatus.auddec_status.size = sizeof(ITTIAM_WMADEC_Status);
	G->wmadec1.adecInArgs.auddec_inArgs.size = sizeof(ITTIAM_WMADEC_InArgs);
	G->wmadec1.adecOutArgs.auddec_outArgs.size = sizeof(ITTIAM_WMADEC_OutArgs);

        G->wmaenc1.aenc1Params.audenc_params.size = sizeof(ITTIAM_WMAENC_Params);
        G->wmaenc1.aenc1DynParams.audenc_dynamicparams.size = sizeof(ITTIAM_WMAENC_DynamicParams);
        G->wmaenc1.aenc1Status.audenc_status.size = sizeof(ITTIAM_WMAENC_Status);
        G->wmaenc1.aenc1InArgs.audenc_inArgs.size = sizeof(ITTIAM_WMAENC_InArgs);
        G->wmaenc1.aenc1OutArgs.audenc_outArgs.size = sizeof(ITTIAM_WMAENC_OutArgs);
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

	/************************************************************************************************/
	/***********     XDM 1.2 Base     ***************************************************************/
	/************************************************************************************************/
	G->h264dec2.vdec2Params.viddecParams.size = sizeof(IH264VDEC_Params);
	G->h264dec2.vdec2Status.viddecStatus.size = sizeof(IH264VDEC_Status);
	G->h264dec2.vdec2DynParams.viddecDynamicParams.size = sizeof(IH264VDEC_DynamicParams);
	G->h264dec2.vdec2InArgs.viddecInArgs.size = sizeof(IH264VDEC_InArgs);
	G->h264dec2.vdec2OutArgs.viddecOutArgs.size = sizeof(IH264VDEC_OutArgs);

        G->mpeg2dec2.vdec2Params.viddecParams.size = sizeof(Imp2VDEC_Params);
        G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.size = sizeof(Imp2VDEC_DynamicParams);
        G->mpeg2dec2.vdec2Status.viddecStatus.size = sizeof(Imp2VDEC_Status);
        G->mpeg2dec2.vdec2InArgs.viddecInArgs.size = sizeof(Imp2VDEC_InArgs);
        G->mpeg2dec2.vdec2OutArgs.viddecOutArgs.size = sizeof(Imp2VDEC_OutArgs);

	G->mpeg4dec2.vdec2Params.viddecParams.size = sizeof(IMP4VDEC_Params);
	G->mpeg4dec2.vdec2Status.viddecStatus.size = sizeof(IMP4VDEC_Status);
	G->mpeg4dec2.vdec2DynParams.viddecDynamicParams.size = sizeof(IMP4VDEC_DynamicParams);
	G->mpeg4dec2.vdec2InArgs.viddecInArgs.size = sizeof(IMP4VDEC_InArgs);
	G->mpeg4dec2.vdec2OutArgs.viddecOutArgs.size = sizeof(IMP4VDEC_OutArgs);

	G->mpeg4hdvicpdec2.vdec2Params.viddecParams.size = sizeof(Imp4VDEC_Params);
	G->mpeg4hdvicpdec2.vdec2Status.viddecStatus.size = sizeof(Imp4VDEC_Status);
	G->mpeg4hdvicpdec2.vdec2DynParams.viddecDynamicParams.size = sizeof(Imp4VDEC_DynamicParams);
	G->mpeg4hdvicpdec2.vdec2InArgs.viddecInArgs.size = sizeof(Imp4VDEC_InArgs);
	G->mpeg4hdvicpdec2.vdec2OutArgs.viddecOutArgs.size = sizeof(Imp4VDEC_OutArgs);
	G->mpeg4hdvicpdec2.vdec2Params.hdvicpHandle = NULL;

	G->vc1dec2.vdec2Params.viddecParams.size = sizeof(IVC1VDEC_Params);
	G->vc1dec2.vdec2Status.viddecStatus.size = sizeof(IVC1VDEC_Status);
	G->vc1dec2.vdec2DynParams.viddecDynamicParams.size = sizeof(IVC1VDEC_DynamicParams);
	G->vc1dec2.vdec2InArgs.viddecInArgs.size = sizeof(IVC1VDEC_InArgs);
	G->vc1dec2.vdec2OutArgs.viddecOutArgs.size = sizeof(IVC1VDEC_OutArgs);
	G->vc1dec2.vdec2Params.hdvicpHandle = NULL;;

	return DVEVM_ST_SUCCESS;
}
