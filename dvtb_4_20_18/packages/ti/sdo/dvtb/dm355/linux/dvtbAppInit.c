/*
 * dvtbAppInit.c
 *
 * DVTB(linux) Application Initialization funtions
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

#define SETP_USAGE  SYS_ERROR("Usage: setp <videnc1|mpeg4spenc1|viddec2|mpeg4spdec2|imgenc1|jpegenc1|imgdec1|jpegdec1|sphenc|sphdec|IPNCUC0|IPNCUC1|IPNCUC2|DVRUC0|DVREnc|DVREncDec> [option] [value]\n")

DvevmStGlobalParams dvevmStGlobalParams;
DvevmStGlobalParams *G = &dvevmStGlobalParams;

DvevmStRetCode
dvtb_initParams()
{
	int index = 0, i = 0;

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
	G->vpbe.setupFxn.setV4l2PreFmtConfiguration = (DvevmStRetCode(*)(void *)) dvtb_PreFmtConfiguration;
	G->vpbe.setupFxn.setV4l2PostFmtConfiguration = (DvevmStRetCode(*)(void *)) NULL;

	G->vpbe.qBuffFxn.setV4l2UserBuffConfig = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2UserBuffConfig;
	G->vpbe.qBuffFxn.setV4l2MmapBuffConfig = (DvevmStRetCode(*)(void *, void *)) dvtb_setV4l2MmapBuffConfig;

	G->vpbe.dqBuffFxn.getV4l2UserBuff = (void* (*)(void *)) dvtb_getV4l2UserBuff;
	G->vpbe.dqBuffFxn.getV4l2MmapBuff = (void* (*)(void *)) dvtb_getV4l2MmapBuff;

	G->vpbe.xres = G->vpbe.imageWidth;
	G->vpbe.yres = G->vpbe.imageHeight;
	G->vpbe.pixelformat = VID_FMT_UYVY;
	G->vpbe.opMode = 0;
	G->vpbe.bpp = DEF_BPP;
	G->aud.framesize = 0;
	G->idec1.dvtb_ptrAllocCmem = &dvtb_allocCmem;
	G->idec1.dvtb_ptrFreeCmem = &dvtb_freeCmem;
	dvtb_vpbeSetupPtr = &dvtb_vpbeSetup;
	dvtb_audioSetControlContentsPtr = NULL;
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     XDM 0.9 Base     ***************************************************************/
	/************************************************************************************************/
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
	G->mpeg4spenc1.venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
	G->mpeg4spenc1.venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
	G->mpeg4spenc1.venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
	G->mpeg4spenc1.venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);
	G->mpeg4spenc1.venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);

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
	/***********     XDM 1.2 Extended     ***********************************************************/
	/************************************************************************************************/
	G->mpeg4spdec2.mpeg4sp_vdecParams.viddecParams.size = sizeof(IMP4VDEC_Params);
	G->mpeg4spdec2.mpeg4sp_vdecDynParams.viddecDynamicParams.size = sizeof(IMP4VDEC_DynamicParams);
	G->mpeg4spdec2.mpeg4sp_vdecInArgs.viddecInArgs.size = sizeof(IMP4VDEC_InArgs);
	G->mpeg4spdec2.mpeg4sp_vdecOutArgs.viddecOutArgs.size = sizeof(IMP4VDEC_OutArgs);
	G->mpeg4spdec2.mpeg4sp_vdecStatus.viddecStatus.size = sizeof(IMP4VDEC_Status);
	/************************************************************************************************/

	/************************************************************************************************/
	/***********     Application Specific     *******************************************************/
	/************************************************************************************************/
	G->IPNCUC0.enc720p.venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
	G->IPNCUC0.enc720p.venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
	G->IPNCUC0.enc720p.venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
	G->IPNCUC0.enc720p.venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);
	G->IPNCUC0.enc720p.venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);
	G->IPNCUC0.encSIF.venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
	G->IPNCUC0.encSIF.venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
	G->IPNCUC0.encSIF.venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
	G->IPNCUC0.encSIF.venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);
	G->IPNCUC0.encSIF.venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);

	G->IPNCUC1.encD1.venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
	G->IPNCUC1.encD1.venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
	G->IPNCUC1.encD1.venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
	G->IPNCUC1.encD1.venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);
	G->IPNCUC1.encD1.venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);
	G->IPNCUC1.encSIF.venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
	G->IPNCUC1.encSIF.venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
	G->IPNCUC1.encSIF.venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
	G->IPNCUC1.encSIF.venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);
	G->IPNCUC1.encSIF.venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);
	G->IPNCUC1.encJPEGD1.ienc1Params.size = sizeof(IMGENC1_Params);
	G->IPNCUC1.encJPEGD1.ienc1Status.size = sizeof(IMGENC1_Status);
	G->IPNCUC1.encJPEGD1.ienc1DynParams.size = sizeof(IMGENC1_DynamicParams);
	G->IPNCUC1.encJPEGD1.ienc1InArgs.size = sizeof(IMGENC1_InArgs);
	G->IPNCUC1.encJPEGD1.ienc1OutArgs.size = sizeof(IMGENC1_OutArgs);

	G->IPNCUC2.enc720p.venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
	G->IPNCUC2.enc720p.venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
	G->IPNCUC2.enc720p.venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
	G->IPNCUC2.enc720p.venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);
	G->IPNCUC2.enc720p.venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);
	G->IPNCUC2.encSIF.venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
	G->IPNCUC2.encSIF.venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
	G->IPNCUC2.encSIF.venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
	G->IPNCUC2.encSIF.venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);
	G->IPNCUC2.encSIF.venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);
	G->IPNCUC2.encJPEGD1.ienc1Params.size = sizeof(IMGENC1_Params);
	G->IPNCUC2.encJPEGD1.ienc1Status.size = sizeof(IMGENC1_Status);
	G->IPNCUC2.encJPEGD1.ienc1DynParams.size = sizeof(IMGENC1_DynamicParams);
	G->IPNCUC2.encJPEGD1.ienc1InArgs.size = sizeof(IMGENC1_InArgs);
	G->IPNCUC2.encJPEGD1.ienc1OutArgs.size = sizeof(IMGENC1_OutArgs);

	G->DVRUC0.enc1D1.venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
	G->DVRUC0.enc1D1.venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
	G->DVRUC0.enc1D1.venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
	G->DVRUC0.enc1D1.venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);
	G->DVRUC0.enc1D1.venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);
	G->DVRUC0.enc2D1.venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
	G->DVRUC0.enc2D1.venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
	G->DVRUC0.enc2D1.venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
	G->DVRUC0.enc2D1.venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);
	G->DVRUC0.enc2D1.venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);

	for (i = 0; i < MAX_MPEG4_INSTANCES; i++)
	{
		G->DVREnc.enc[i].venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
		G->DVREnc.enc[i].venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
		G->DVREnc.enc[i].venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
		G->DVREnc.enc[i].venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);
		G->DVREnc.enc[i].venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);
	}

	for (i = 0; i < MAX_DVRENCDEC_MPEG4_INSTANCES; i++)
	{
		G->DVREncDec.enc[i].venc1Params.videncParams.size = sizeof(IMP4VENC_Params);
		G->DVREncDec.enc[i].venc1DynParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
		G->DVREncDec.enc[i].venc1InArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
		G->DVREncDec.enc[i].venc1OutArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);
		G->DVREncDec.enc[i].venc1Status.videncStatus.size = sizeof(IMP4VENC_Status);

		G->DVREncDec.dec[i].mpeg4sp_vdecParams.viddecParams.size = sizeof(IMP4VDEC_Params);
		G->DVREncDec.dec[i].mpeg4sp_vdecDynParams.viddecDynamicParams.size = sizeof(IMP4VDEC_DynamicParams);
		G->DVREncDec.dec[i].mpeg4sp_vdecInArgs.viddecInArgs.size = sizeof(IMP4VDEC_InArgs);
		G->DVREncDec.dec[i].mpeg4sp_vdecOutArgs.viddecOutArgs.size = sizeof(IMP4VDEC_OutArgs);
		G->DVREncDec.dec[i].mpeg4sp_vdecStatus.viddecStatus.size = sizeof(IMP4VDEC_Status);
	}
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
