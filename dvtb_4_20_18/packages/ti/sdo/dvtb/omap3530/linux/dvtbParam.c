/*
 * dvtbParam.c
 *
 * DVTB Handlers Initialization
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

#include "dvtbParam.h"

dvtbMapTable *MAP = NULL;
unsigned int DVEVM_CODEC_NUM = 0;

static DvevmStBool valInitialized = DVEVM_ST_FALSE;

/* Hack : C doesn't support non-constant initialization of global variables. We
 * achieve this is a round about way */

void
dvtb_initValues()
{
	if (!valInitialized)
	{
		/* className, fieldName, field Type, value, defaultValue */
		dvtbMapTable dvtbMapArr[] =
		{
			/* All global parameters */
			{ "engine", "name", DVEVM_ST_STR, G->eng.name, DEFAULT_ENGINE_NAME },

			/* Parameters for audio device */
			{ "audio", "device", DVEVM_ST_STR, G->aud.device, DEF_SND_DEVICE },
			{ "audio", "format", DVEVM_ST_INT, &(G->aud.format), (void *) SND_PCM_FORMAT_S16_LE },
			{ "audio", "samplerate", DVEVM_ST_INT, &(G->aud.sampleRate), (void *) DEF_SAMPLE_RATE },
			{ "audio", "channels", DVEVM_ST_INT, &(G->aud.numChannels), (void *) DEF_NUM_CHANNELS },
			{ "audio", "type", DVEVM_ST_INT, &(G->aud.blocking_mode), 0 },

			/* Parameters for VPBE device */
			{ "vpbe", "device", DVEVM_ST_STR, G->vpbe.device, VID_DEVICE },
			{ "vpbe", "width", DVEVM_ST_INT, &(G->vpbe.imageWidth), (void *) NTSC_XRES },
			{ "vpbe", "height", DVEVM_ST_INT, &(G->vpbe.imageHeight), (void *) NTSC_YRES },
			{ "vpbe", "output", DVEVM_ST_INT, &(G->vpbe.outputDevice), (void *) DVEVM_ST_LCD },
			{ "vpbe", "scaling", DVEVM_ST_INT, &(G->vpbe.scaling), (void *) 1 },
			{ "vpbe", "ch_mode", DVEVM_ST_STR, &(G->vpbe.ch_mode), (void *) "VGA" },
			{ "vpbe", "rotate", DVEVM_ST_INT, &(G->vpbe.rotate), (void *) 0 },

			/* Parameters for VPFE device */
			{ "vpfe", "device", DVEVM_ST_STR, G->vpfe.device, VIDCAP_DEVICE },
			{ "vpfe", "standard", DVEVM_ST_INT, &(G->vpfe.capStd), (void *) VID_STD_NTSC },
			{ "vpfe", "format", DVEVM_ST_INT, &(G->vpfe.capFmt), (void *) VID_FMT_UYVY },
			{ "vpfe", "input", DVEVM_ST_INT, &(G->vpfe.input), (void *) 0 }, //need to change
			{ "vpfe", "width", DVEVM_ST_INT, &(G->vpfe.capWidth), (void *) NTSC_WIDTH },
			{ "vpfe", "height", DVEVM_ST_INT, &(G->vpfe.capHeight), (void *) NTSC_HEIGHT },

			/* Parameters for VPFE device */
			{ "vprsz", "device", DVEVM_ST_STR, G->vprsz.resizeDevice, VIDRESIZE_DEVICE },
			{ "vprsz", "rszEnable", DVEVM_ST_INT, &(G->vprsz.rszEnable), (void *) 0 },
 
			/* Parameters for Universal Codec */
			{ "deinter", "codec", DVEVM_ST_STR, G->deinter.deinterName, "deinterlacer" },
			{ "deinter", "deinterEnable", DVEVM_ST_INT, &(G->deinter.deinterEnable), (void *) 0 },

			/* Parameters for Video Encoder XDM 1.0*/
			{ "videnc1", "codec", DVEVM_ST_STR, G->venc1.venc1Name, DEFAULT_VIDENC1_NAME },
			{ "videnc1", "encodingPreset", DVEVM_ST_INT, &(G->venc1.venc1Params.encodingPreset), (void *) XDM_DEFAULT },
			{ "videnc1", "rateControlPreset", DVEVM_ST_INT, &(G->venc1.venc1Params.rateControlPreset), (void *) 1 },
			{ "videnc1", "maxHeight", DVEVM_ST_INT, &(G->venc1.venc1Params.maxHeight), (void *) PAL_YRES },
			{ "videnc1", "maxWidth", DVEVM_ST_INT, &(G->venc1.venc1Params.maxWidth), (void *) PAL_XRES },
			{ "videnc1", "maxFrameRate", DVEVM_ST_INT, &(G->venc1.venc1Params.maxFrameRate), (void *) VIDENC1_MAX_FR },
			{ "videnc1", "maxBitRate", DVEVM_ST_INT, &(G->venc1.venc1Params.maxBitRate), (void *) VIDENC1_MAX_BR },
			{ "videnc1", "dataEndianness", DVEVM_ST_INT, &(G->venc1.venc1Params.dataEndianness), (void *) XDM_BYTE },
			{ "videnc1", "maxInterFrameInterval", DVEVM_ST_INT, &(G->venc1.venc1Params.maxInterFrameInterval), (void *) 1 },
			{ "videnc1", "inputChromaFormat", DVEVM_ST_INT, &(G->venc1.venc1Params.inputChromaFormat), (void *) XDM_YUV_420P },
			{ "videnc1", "inputContentType", DVEVM_ST_INT, &(G->venc1.venc1Params.inputContentType), (void *) IVIDEO_PROGRESSIVE },
			{ "videnc1", "reconChromaFormat", DVEVM_ST_INT, &(G->venc1.venc1Params.reconChromaFormat), (void *) XDM_CHROMA_NA },
			{ "videnc1", "inputHeight", DVEVM_ST_INT, &(G->venc1.venc1DynParams.inputHeight), (void *) VIDENC1_MAX_HT },
			{ "videnc1", "inputWidth", DVEVM_ST_INT, &(G->venc1.venc1DynParams.inputWidth), (void *) VIDENC1_MAX_WD },
			{ "videnc1", "refFrameRate", DVEVM_ST_INT, &(G->venc1.venc1DynParams.refFrameRate), (void *) VIDENC1_MAX_FR },
			{ "videnc1", "targetFrameRate", DVEVM_ST_INT, &(G->venc1.venc1DynParams.targetFrameRate), (void *) VIDENC1_MAX_FR },
			{ "videnc1", "targetBitRate", DVEVM_ST_INT, &(G->venc1.venc1DynParams.targetBitRate), (void *) VIDENC1_MAX_BR },
			{ "videnc1", "intraFrameInterval", DVEVM_ST_INT, &(G->venc1.venc1DynParams.intraFrameInterval), (void *) VIDENC1_INTRA_FI },
			{ "videnc1", "generateHeader", DVEVM_ST_INT, &(G->venc1.venc1DynParams.generateHeader), (void *) XDM_DECODE_AU },
			{ "videnc1", "captureWidth", DVEVM_ST_INT, &(G->venc1.venc1DynParams.captureWidth), (void *) 0 },
			{ "videnc1", "forceFrame", DVEVM_ST_INT, &(G->venc1.venc1DynParams.forceFrame), (void *) 0 },
			{ "videnc1", "interFrameInterval", DVEVM_ST_INT, &(G->venc1.venc1DynParams.interFrameInterval), (void *) 1 },
			{ "videnc1", "mbDataFlag", DVEVM_ST_INT, &(G->venc1.venc1DynParams.mbDataFlag), (void *) 0 },
			{ "videnc1", "framePitch", DVEVM_ST_INT, &(G->venc1.inBufDesc.framePitch), (void *) VIDENC1_MAX_WD },
			{ "videnc1", "numFrames", DVEVM_ST_INT, &(G->venc1.numFrames), (void *) DEF_CAP_FRAMES },

			/* Parameters for Speech Decoder XDM 1.0*/
			{ "sphdec1", "codec", DVEVM_ST_STR, G->sdec1.sdecName, DEFAULT_SPHDEC1_NAME },
			{ "sphdec1", "compandingLaw", DVEVM_ST_SHORT, &(G->sdec1.sdecParams.compandingLaw), (void *) SPHDEC1_CL },
			{ "sphdec1", "packingType", DVEVM_ST_SHORT, &(G->sdec1.sdecParams.packingType), (void *) SPHDEC1_PT },
			{ "sphdec1", "codecSelection", DVEVM_ST_SHORT, &(G->sdec1.sdecParams.codecSelection), (void *) 0 },
			{ "sphdec1", "bitRate", DVEVM_ST_SHORT, &(G->sdec1.sdecParams.bitRate), (void *) 12000 },
			{ "sphdec1", "inbufsize", DVEVM_ST_INT, &(G->sdec1.inBuf.size), (void *) SPHDEC1_INBUF_SIZE },
			{ "sphdec1", "outbufsize", DVEVM_ST_INT, &(G->sdec1.outBuf.size), (void *) SPHDEC1_OUTBUF_SIZE },

			// Parameters for Speech Encoder XDM 1.0
			{ "sphenc1", "codec", DVEVM_ST_STR, G->senc1.sencName, DEFAULT_SPHENC1_NAME },
			{ "sphenc1", "seconds", DVEVM_ST_INT, &(G->senc1.seconds), (void *) DEFAULT_SPHENC1_TIME },
			{ "sphenc1", "frameSize", DVEVM_ST_SHORT, &(G->senc1.sencParams.frameSize), (void *) SPHENC1_FRAME_SIZE },
			{ "sphenc1", "compandingLaw", DVEVM_ST_SHORT, &(G->senc1.sencParams.compandingLaw), (void *) SPHENC1_CL },
			{ "sphenc1", "packingType", DVEVM_ST_SHORT, &(G->senc1.sencParams.packingType), (void *) SPHENC1_PT },
			{ "sphenc1", "vadSelection", DVEVM_ST_SHORT, &(G->senc1.sencParams.vadSelection), (void *) SPHENC1_VS },
			{ "sphenc1", "codecSelection", DVEVM_ST_SHORT, &(G->senc1.sencParams.codecSelection), (void *) 0 },
			{ "sphenc1", "bitRate", DVEVM_ST_SHORT, &(G->senc1.sencParams.bitRate), (void *) 12000 },
			{ "sphenc1", "inbufsize", DVEVM_ST_INT, &(G->senc1.inBuf.size), (void *) (SPHENC1_FRAME_SIZE * 2) },
			{ "sphenc1", "outbufsize", DVEVM_ST_INT, &(G->senc1.outBuf.size), (void *) SPHENC1_FRAME_SIZE },

			/* Parameters for Audio1 Decoder */
			{ "auddec1", "codec", DVEVM_ST_STR, G->adec1.adecName, DEFAULT_AUDDEC1_NAME },
			{ "auddec1", "outputPCMWidth", DVEVM_ST_INT, &(G->adec1.adecParams.outputPCMWidth), (void *) AUDDEC1_PCM_WIDTH },
			{ "auddec1", "pcmFormat", DVEVM_ST_INT, &(G->adec1.adecParams.pcmFormat), (void *) IAUDIO_INTERLEAVED },
			{ "auddec1", "dataEndianness", DVEVM_ST_INT, &(G->adec1.adecParams.dataEndianness), (void *) XDM_BYTE },
			{ "auddec1", "desiredChannelMode", DVEVM_ST_INT, &(G->adec1.desiredChannelMode), (void *) IAUDIO_2_0 },
			{ "auddec1", "downSampleSbrFlag", DVEVM_ST_INT, &(G->adec1.adecDynParams.downSampleSbrFlag), (void *) XDAS_FALSE },
			{ "auddec1", "inbufsize", DVEVM_ST_INT, &(G->adec1.inBuf.bufSizes[0]), (void *) AUDDEC1_INBUF_SIZE },
			{ "auddec1", "outbufsize", DVEVM_ST_INT, &(G->adec1.outBuf.bufSizes[0]), (void *) AUDDEC1_OUTBUF_SIZE },
			{ "auddec1", "pwrManagerEnable", DVEVM_ST_INT, &(G->adec1.pEnable), (void *) 0 },

			/* Parameters for MP3 XDM1 Decoder */
			{ "mp3basedec1", "codec", DVEVM_ST_STR, G->mp3basedec1.adecName, DEFAULT_MP3BASEDEC1_NAME },
			{ "mp3basedec1", "outputPCMWidth", DVEVM_ST_INT, &(G->mp3basedec1.adecParams.outputPCMWidth), (void *) MP3BASEDEC1_PCM_WIDTH },
			{ "mp3basedec1", "pcmFormat", DVEVM_ST_INT, &(G->mp3basedec1.adecParams.pcmFormat), (void *) IAUDIO_INTERLEAVED },
			{ "mp3basedec1", "dataEndianness", DVEVM_ST_INT, &(G->mp3basedec1.adecParams.dataEndianness), (void *) XDM_BYTE },
			{ "mp3basedec1", "downSampleSbrFlag", DVEVM_ST_INT, &(G->mp3basedec1.adecDynParams.downSampleSbrFlag), (void *) XDAS_FALSE },
			{ "mp3basedec1", "inbufsize", DVEVM_ST_INT, &(G->mp3basedec1.inBuf.bufSizes[0]), (void *) MP3BASEDEC1_INBUF_SIZE },
			{ "mp3basedec1", "outbufsize", DVEVM_ST_INT, &(G->mp3basedec1.outBuf.bufSizes[0]), (void *) MP3BASEDEC1_OUTBUF_SIZE },
			{ "mp3basedec1", "pwrManagerEnable", DVEVM_ST_INT, &(G->mp3basedec1.pEnable), (void *) 0 },

			/* Parameters for xdm 1.0 Image Decoder */
			{ "imgdec1", "codec", DVEVM_ST_STR, G->idec1.idec1Name, DEFAULT_IMGDEC_NAME },
			{ "imgdec1", "maxHeight", DVEVM_ST_INT, &(G->idec1.idec1Params.maxHeight), (void *) IMGDEC1_MAX_HT },
			{ "imgdec1", "maxWidth", DVEVM_ST_INT, &(G->idec1.idec1Params.maxWidth), (void *) IMGDEC1_MAX_WD },
			{ "imgdec1", "maxScans", DVEVM_ST_INT, &(G->idec1.idec1Params.maxScans), (void *) IMGDEC1_MAX_SCANS },
			{ "imgdec1", "dataEndianness", DVEVM_ST_INT, &(G->idec1.idec1Params.dataEndianness), (void *) XDM_BYTE },
			{ "imgdec1", "forceChromaFormat", DVEVM_ST_INT, &(G->idec1.idec1Params.forceChromaFormat), (void *) XDM_YUV_422ILE },
			{ "imgdec1", "numAU", DVEVM_ST_INT, &(G->idec1.idec1DynParams.numAU), (void *) XDM_DEFAULT },
			{ "imgdec1", "decodeHeader", DVEVM_ST_INT, &(G->idec1.idec1DynParams.decodeHeader), (void *) XDM_DECODE_AU },
			{ "imgdec1", "displayWidth", DVEVM_ST_INT, &(G->idec1.idec1DynParams.displayWidth), (void *) XDM_DEFAULT },

			/* Parameters for xdm 1.0 Image Encoder */
			{ "imgenc1", "codec", DVEVM_ST_STR, G->ienc1.ienc1Name, DEFAULT_IMGENC1_NAME },
			{ "imgenc1", "maxHeight", DVEVM_ST_INT, &(G->ienc1.ienc1Params.maxHeight), (void *) PAL_YRES },
			{ "imgenc1", "maxWidth", DVEVM_ST_INT, &(G->ienc1.ienc1Params.maxWidth), (void *) PAL_XRES },
			{ "imgenc1", "maxScans", DVEVM_ST_INT, &(G->ienc1.ienc1Params.maxScans), (void *) XDM_DEFAULT },
			{ "imgenc1", "dataEndianness", DVEVM_ST_INT, &(G->ienc1.ienc1Params.dataEndianness), (void *) XDM_BYTE },
			{ "imgenc1", "forceChromaFormat", DVEVM_ST_INT, &(G->ienc1.ienc1Params.forceChromaFormat), (void *) XDM_YUV_422P },
			{ "imgenc1", "numAU", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.numAU), (void *) XDM_DEFAULT },
			{ "imgenc1", "inputChromaFormat", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.inputChromaFormat), (void *) XDM_YUV_422ILE },
			{ "imgenc1", "inputHeight", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.inputHeight), (void *) IMGENC1_MAX_HT },
			{ "imgenc1", "inputWidth", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.inputWidth), (void *) IMGENC1_MAX_WD },
			{ "imgenc1", "captureWidth", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.captureWidth), (void *) IMGENC1_MAX_WD },
			{ "imgenc1", "generateHeader", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.generateHeader), (void *) XDM_ENCODE_AU },
			{ "imgenc1", "qValue", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.qValue), (void *) 73 },

			/* Parameters for JPEG Decoder XDM 1.0*/
			{ "jpegdec1", "codec", DVEVM_ST_STR, G->jpegdec1.idec1Name, DEFAULT_IMGDEC_NAME },
			{ "jpegdec1", "maxHeight", DVEVM_ST_INT, &(G->jpegdec1.idec1Params.imgdecParams.maxHeight), (void *) IMGDEC1_MAX_HT },
			{ "jpegdec1", "maxWidth", DVEVM_ST_INT, &(G->jpegdec1.idec1Params.imgdecParams.maxWidth), (void *) IMGDEC1_MAX_WD },
			{ "jpegdec1", "maxScans", DVEVM_ST_INT, &(G->jpegdec1.idec1Params.imgdecParams.maxScans), (void *) 15 },
			{ "jpegdec1", "dataEndianness", DVEVM_ST_INT, &(G->jpegdec1.idec1Params.imgdecParams.dataEndianness), (void *) XDM_BYTE },
			{ "jpegdec1", "forceChromaFormat", DVEVM_ST_INT, &(G->jpegdec1.idec1Params.imgdecParams.forceChromaFormat), (void *) XDM_YUV_422ILE },
			{ "jpegdec1", "progressiveDecFlag", DVEVM_ST_INT, &(G->jpegdec1.idec1Params.progressiveDecFlag), (void *) 1 },
			{ "jpegdec1", "outImgRes", DVEVM_ST_INT, &(G->jpegdec1.idec1Params.outImgRes), (void *) 0 },
			{ "jpegdec1", "numAU", DVEVM_ST_INT, &(G->jpegdec1.idec1DynParams.imgdecDynamicParams.numAU), (void *) XDM_DEFAULT },
			{ "jpegdec1", "decodeHeader", DVEVM_ST_INT, &(G->jpegdec1.idec1DynParams.imgdecDynamicParams.decodeHeader), (void *) XDM_DECODE_AU },
			{ "jpegdec1", "displayWidth", DVEVM_ST_INT, &(G->jpegdec1.idec1DynParams.imgdecDynamicParams.displayWidth), (void *) XDM_DEFAULT },
			{ "jpegdec1", "progDisplay", DVEVM_ST_INT, &(G->jpegdec1.idec1DynParams.progDisplay), (void *) 0 },
			{ "jpegdec1", "resizeOption", DVEVM_ST_INT, &(G->jpegdec1.idec1DynParams.resizeOption), (void *) 0 },
			{ "jpegdec1", "RGB_Format", DVEVM_ST_INT, &(G->jpegdec1.idec1DynParams.RGB_Format), (void *) 0 },
			{ "jpegdec1", "numMCU_row", DVEVM_ST_INT, &(G->jpegdec1.idec1DynParams.numMCU_row), (void *) 0 },
			{ "jpegdec1", "x_org", DVEVM_ST_INT, &(G->jpegdec1.idec1DynParams.x_org), (void *) 0 },
			{ "jpegdec1", "y_org", DVEVM_ST_INT, &(G->jpegdec1.idec1DynParams.y_org), (void *) 0 },
			{ "jpegdec1", "x_length", DVEVM_ST_INT, &(G->jpegdec1.idec1DynParams.x_length), (void *) 0 },
			{ "jpegdec1", "y_length", DVEVM_ST_INT, &(G->jpegdec1.idec1DynParams.y_length), (void *) 0 },
			{ "jpegdec1", "alpha_rgb", DVEVM_ST_INT, &(G->jpegdec1.idec1DynParams.alpha_rgb), (void *) 0 },

			/* Parameters for Power Manager */
			{ "pwrmanager", "scalingGovernor", DVEVM_ST_STR, G->pmanager.scalingGovernor, "performance" },
			{ "pwrmanager", "vdd1PState", DVEVM_ST_INT, &(G->pmanager.vdd1PState), (void *) 4 },
			{ "pwrmanager", "vdd2PState", DVEVM_ST_INT, &(G->pmanager.vdd2PState), (void *) 3 },
			{ "pwrmanager", "cpuIdleState", DVEVM_ST_INT, &(G->pmanager.cpuIdleState), (void *) 1 },

			/* Parameters for MPEG2 Decoder XDM 1.0*/
			{ "viddec2", "codec", DVEVM_ST_STR, G->viddec2.vdec2Name, DEFAULT_VIDDEC2_NAME },
			{ "viddec2", "maxHeight", DVEVM_ST_INT, &(G->viddec2.vdec2Params.maxHeight), (void *) PAL_YRES },
			{ "viddec2", "maxWidth", DVEVM_ST_INT, &(G->viddec2.vdec2Params.maxWidth), (void *) PAL_XRES },
			{ "viddec2", "maxFrameRate", DVEVM_ST_INT, &(G->viddec2.vdec2Params.maxFrameRate), (void *) VIDDEC2_MAX_FR },
			{ "viddec2", "maxBitRate", DVEVM_ST_INT, &(G->viddec2.vdec2Params.maxBitRate), (void *) VIDDEC2_MAX_BR },
			{ "viddec2", "dataEndianness", DVEVM_ST_INT, &(G->viddec2.vdec2Params.dataEndianness), (void *) XDM_BYTE },
			{ "viddec2", "forceChromaFormat", DVEVM_ST_INT, &(G->viddec2.vdec2Params.forceChromaFormat), (void *) XDM_YUV_422ILE },
			{ "viddec2", "decodeHeader", DVEVM_ST_INT, &(G->viddec2.vdec2DynParams.decodeHeader), (void *) XDM_DECODE_AU },
			{ "viddec2", "displayWidth", DVEVM_ST_INT, &(G->viddec2.vdec2DynParams.displayWidth), (void *) XDM_DEFAULT },
			{ "viddec2", "frameSkipMode", DVEVM_ST_INT, &(G->viddec2.vdec2DynParams.frameSkipMode), (void *) IVIDEO_NO_SKIP },
			{ "viddec2", "frameOrder", DVEVM_ST_INT, &(G->viddec2.vdec2DynParams.frameOrder), (void *) 0 },
			{ "viddec2", "newFrameFlag", DVEVM_ST_INT, &(G->viddec2.vdec2DynParams.newFrameFlag), (void *) 0 },
			{ "viddec2", "mbDataFlag", DVEVM_ST_INT, &(G->viddec2.vdec2DynParams.mbDataFlag), (void *) 0 },
			{ "viddec2", "numFrames", DVEVM_ST_INT, &(G->viddec2.numFrames), (void *) 100 },
			{ "viddec2", "pwrManagerEnable", DVEVM_ST_INT, &(G->viddec2.pEnable), (void *) 0 },

			/* Parameters for H264 Decoder XDM 1.2*/
			{ "h264dec2", "codec", DVEVM_ST_STR, G->h264dec2.vdec2Name, DEFAULT_H264DEC2_NAME },
			{ "h264dec2", "maxHeight", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.viddecParams.maxHeight), (void *) PAL_YRES },
			{ "h264dec2", "maxWidth", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.viddecParams.maxWidth), (void *) PAL_XRES },
			{ "h264dec2", "maxFrameRate", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.viddecParams.maxFrameRate), (void *) VIDDEC2_MAX_FR },
			{ "h264dec2", "maxBitRate", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.viddecParams.maxBitRate), (void *) VIDDEC2_MAX_BR },
			{ "h264dec2", "dataEndianness", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.viddecParams.dataEndianness), (void *) XDM_BYTE },
			{ "h264dec2", "forceChromaFormat", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.viddecParams.forceChromaFormat), (void *) XDM_YUV_422ILE },
			{ "h264dec2", "inputStreamFormat", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.inputStreamFormat), (void *) 0 },
			{ "h264dec2", "maxDisplayDelay", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.maxDisplayDelay), (void *) 0 },
			{ "h264dec2", "decodeHeader", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.viddecDynamicParams.decodeHeader), (void *) XDM_DECODE_AU },
			{ "h264dec2", "displayWidth", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.viddecDynamicParams.displayWidth), (void *) XDM_DEFAULT },
			{ "h264dec2", "frameSkipMode", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.viddecDynamicParams.frameSkipMode), (void *) IVIDEO_NO_SKIP },
			{ "h264dec2", "frameOrder", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.viddecDynamicParams.frameOrder), (void *) 0 },
			{ "h264dec2", "newFrameFlag", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.viddecDynamicParams.newFrameFlag), (void *) 0 },
			{ "h264dec2", "mbDataFlag", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.viddecDynamicParams.mbDataFlag), (void *) 0 },
			{ "h264dec2", "mbErrorBufFlag", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.mbErrorBufFlag), (void *) 0 },
			{ "h264dec2", "mbErrorBufSize", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.mbErrorBufSize), (void *) 0 },
			{ "h264dec2", "Sei_Vui_parse_flag", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.Sei_Vui_parse_flag), (void *) 0 },
			{ "h264dec2", "numNALunits", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.numNALunits), (void *) 0 },
			{ "h264dec2", "numFrames", DVEVM_ST_INT, &(G->h264dec2.numFrames), (void *) 100 },

			/* Parameters for H264 Encoder XDM 1.0*/
			{ "h264enc1", "codec", DVEVM_ST_STR, G->h264enc1.venc1Name, DEFAULT_H264ENC1_NAME },
			{ "h264enc1", "encodingPreset", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.encodingPreset), (void *) XDM_DEFAULT },
			{ "h264enc1", "rateControlPreset", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.rateControlPreset), (void *) 1 },
			{ "h264enc1", "maxHeight", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.maxHeight), (void *) H264ENC1_MAX_HT },
			{ "h264enc1", "maxWidth", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.maxWidth), (void *) H264ENC1_MAX_WD },
			{ "h264enc1", "maxFrameRate", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.maxFrameRate), (void *) H264ENC1_MAX_FR },
			{ "h264enc1", "maxBitRate", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.maxBitRate), (void *) H264ENC1_MAX_BR },
			{ "h264enc1", "dataEndianness", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.dataEndianness), (void *) XDM_BYTE },
			{ "h264enc1", "maxInterFrameInterval", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.maxInterFrameInterval), (void *) 0 },
			{ "h264enc1", "inputChromaFormat", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.inputChromaFormat), (void *) XDM_YUV_420P },
			{ "h264enc1", "inputContentType", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.inputContentType), (void *) IVIDEO_PROGRESSIVE },
			{ "h264enc1", "reconChromaFormat", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.reconChromaFormat), (void *) XDM_YUV_420P },
			{ "h264enc1", "profileIdc", DVEVM_ST_INT, &(G->h264enc1.venc1Params.profileIdc), (void *) 66 },
			{ "h264enc1", "levelIdc", DVEVM_ST_INT, &(G->h264enc1.venc1Params.levelIdc), (void *) IH264_LEVEL_30 },
			{ "h264enc1", "rcAlgo", DVEVM_ST_INT, &(G->h264enc1.venc1Params.rcAlgo), (void *) 0 },
			{ "h264enc1", "searchRange", DVEVM_ST_INT, &(G->h264enc1.venc1Params.searchRange), (void *) 64},
			{ "h264enc1", "inputHeight", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.videncDynamicParams.inputHeight), (void *) H264ENC1_MAX_HT },
			{ "h264enc1", "inputWidth", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.videncDynamicParams.inputWidth), (void *) H264ENC1_MAX_WD },
			{ "h264enc1", "refFrameRate", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.videncDynamicParams.refFrameRate), (void *) H264ENC1_MAX_FR },
			{ "h264enc1", "targetFrameRate", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.videncDynamicParams.targetFrameRate), (void *) VIDENC1_MAX_FR },
			{ "h264enc1", "targetBitRate", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.videncDynamicParams.targetBitRate), (void *) H264ENC1_MAX_BR },
			{ "h264enc1", "intraFrameInterval", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.videncDynamicParams.intraFrameInterval), (void *) H264ENC1_INTRA_FI },
			{ "h264enc1", "generateHeader", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.videncDynamicParams.generateHeader), (void *) XDM_DECODE_AU },
			{ "h264enc1", "captureWidth", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.videncDynamicParams.captureWidth), (void *) 0 },
			{ "h264enc1", "forceFrame", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.videncDynamicParams.forceFrame), (void *) 0 },
			{ "h264enc1", "interFrameInterval", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.videncDynamicParams.interFrameInterval), (void *) 0 },
			{ "h264enc1", "mbDataFlag", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.videncDynamicParams.mbDataFlag), (void *) 0 },
			{ "h264enc1", "qpIntra", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.qpIntra), (void *) 24 },
			{ "h264enc1", "qpInter", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.qpInter), (void *) 24 },
			{ "h264enc1", "qpMax", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.qpMax), (void *) 51 },
			{ "h264enc1", "qpMin", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.qpMin), (void *) 0 },
			{ "h264enc1", "lfDisableIdc", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.lfDisableIdc), (void *) 0 },
			{ "h264enc1", "quartPelDisable", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.quartPelDisable), (void *) 1 },
			{ "h264enc1", "airMbPeriod", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.airMbPeriod), (void *) 0 },
			{ "h264enc1", "maxMBsPerSlice", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.maxMBsPerSlice), (void *) 0 },
			{ "h264enc1", "maxBytesPerSlice", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.maxBytesPerSlice), (void *) 0 },
			{ "h264enc1", "sliceRefreshRowStartNumber", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceRefreshRowStartNumber), (void *) 0 },
			{ "h264enc1", "sliceRefreshRowNumber", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceRefreshRowNumber), (void *) 0 },
			{ "h264enc1", "filterOffsetA", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.filterOffsetA), (void *) 0 },
			{ "h264enc1", "filterOffsetB", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.filterOffsetB), (void *) 0 },
			{ "h264enc1", "log2MaxFNumMinus4", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.log2MaxFNumMinus4), (void *) 0 },
			{ "h264enc1", "chromaQPIndexOffset", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.chromaQPIndexOffset), (void *) 0 },
			{ "h264enc1", "constrainedIntraPredEnable", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.constrainedIntraPredEnable), (void *) 0 },
			{ "h264enc1", "picOrderCountType", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.picOrderCountType), (void *) 0 },
			{ "h264enc1", "maxMVperMB", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.maxMVperMB), (void *) 1 },
			{ "h264enc1", "intra4x4EnableIdc", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.intra4x4EnableIdc), (void *) INTRA4x4_NONE },
			{ "h264enc1", "mvDataEnable", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.mvDataEnable), (void *) 0 },
			{ "h264enc1", "hierCodingEnable", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.hierCodingEnable), (void *) 1 },
			{ "h264enc1", "streamFormat", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.streamFormat), (void *) IH264_BYTE_STREAM },
			{ "h264enc1", "intraRefreshMethod", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.intraRefreshMethod), (void *) IH264_INTRAREFRESH_NONE },
			{ "h264enc1", "perceptualQuant", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.perceptualQuant), (void *) 0 },
			{ "h264enc1", "sceneChangeDet", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sceneChangeDet), (void *) 0 },
			{ "h264enc1", "numSliceASO", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.numSliceASO), (void *) 0 },
			{ "h264enc1", "asoSliceOrder[0]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.asoSliceOrder[0]), (void *) 0 },
			{ "h264enc1", "asoSliceOrder[1]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.asoSliceOrder[1]), (void *) 0 },
			{ "h264enc1", "asoSliceOrder[2]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.asoSliceOrder[2]), (void *) 0 },
			{ "h264enc1", "asoSliceOrder[3]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.asoSliceOrder[3]), (void *) 0 },
			{ "h264enc1", "asoSliceOrder[4]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.asoSliceOrder[4]), (void *) 0 },
			{ "h264enc1", "asoSliceOrder[5]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.asoSliceOrder[5]), (void *) 0 },
			{ "h264enc1", "asoSliceOrder[6]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.asoSliceOrder[6]), (void *) 0 },
			{ "h264enc1", "asoSliceOrder[7]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.asoSliceOrder[7]), (void *) 0 },
			{ "h264enc1", "numSliceGroups", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.numSliceGroups), (void *) 0 },
			{ "h264enc1", "sliceGroupMapType", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceGroupMapType), (void *) 0 },
			{ "h264enc1", "sliceGroupChangeDirectionFlag", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceGroupChangeDirectionFlag), (void *) 0 },
			{ "h264enc1", "sliceGroupChangeRate", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceGroupChangeRate), (void *) 0 },
			{ "h264enc1", "sliceGroupChangeCycle", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceGroupChangeCycle), (void *) 0 },
			{ "h264enc1", "sliceGroupParams[0]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceGroupParams[0]), (void *) 0 },
			{ "h264enc1", "sliceGroupParams[1]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceGroupParams[1]), (void *) 0 },
			{ "h264enc1", "sliceGroupParams[2]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceGroupParams[2]), (void *) 0 },
			{ "h264enc1", "sliceGroupParams[3]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceGroupParams[3]), (void *) 0 },
			{ "h264enc1", "sliceGroupParams[4]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceGroupParams[4]), (void *) 0 },
			{ "h264enc1", "sliceGroupParams[5]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceGroupParams[5]), (void *) 0 },
			{ "h264enc1", "sliceGroupParams[6]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceGroupParams[6]), (void *) 0 },
			{ "h264enc1", "sliceGroupParams[7]", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.sliceGroupParams[7]), (void *) 0 },
			{ "h264enc1", "framePitch", DVEVM_ST_INT, &(G->h264enc1.inBufDesc.framePitch), (void *) H264ENC1_MAX_WD },
			{ "h264enc1", "numFrames", DVEVM_ST_INT, &(G->h264enc1.numFrames), (void *) DEF_CAP_FRAMES },

			/* Parameters for xdm 1.0 MPEG4SP Video Encoder */
			{ "mpeg4spenc1", "codec", DVEVM_ST_STR, G->mpeg4spenc1.venc1Name, DEFAULT_MPEG4ENC1_NAME },
			{ "mpeg4spenc1", "encodingPreset", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.videncParams.encodingPreset), (void *) XDM_DEFAULT },
			{ "mpeg4spenc1", "rateControlPreset", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.videncParams.rateControlPreset), (void *) 1 }, //1 earlier
			{ "mpeg4spenc1", "maxHeight", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.videncParams.maxHeight), (void *) VIDENC1_MAX_HT },
			{ "mpeg4spenc1", "maxWidth", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.videncParams.maxWidth), (void *) VIDENC1_MAX_WD },
			{ "mpeg4spenc1", "maxFrameRate", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.videncParams.maxFrameRate), (void *) VIDENC1_MAX_FR },
			{ "mpeg4spenc1", "maxBitRate", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.videncParams.maxBitRate), (void *) VIDENC1_MAX_BR },
			{ "mpeg4spenc1", "dataEndianness", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.videncParams.dataEndianness), (void *) XDM_BYTE },
			{ "mpeg4spenc1", "maxInterFrameInterval", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.videncParams.maxInterFrameInterval), (void *) 0 },
			{ "mpeg4spenc1", "inputChromaFormat", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.videncParams.inputChromaFormat), (void *) XDM_YUV_420SP },
			{ "mpeg4spenc1", "inputContentType", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.videncParams.inputContentType), (void *) IVIDEO_PROGRESSIVE },
			{ "mpeg4spenc1", "reconChromaFormat", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.videncParams.reconChromaFormat), (void *) XDM_YUV_420P },
			{ "mpeg4spenc1", "inputHeight", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.videncDynamicParams.inputHeight), (void *) VIDENC1_MAX_HT },
			{ "mpeg4spenc1", "inputWidth", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.videncDynamicParams.inputWidth), (void *) VIDENC1_MAX_WD },
			{ "mpeg4spenc1", "refFrameRate", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.videncDynamicParams.refFrameRate), (void *) VIDENC1_MAX_FR },
			{ "mpeg4spenc1", "targetFrameRate", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.videncDynamicParams.targetFrameRate), (void *) VIDENC1_MAX_FR },
			{ "mpeg4spenc1", "targetBitRate", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.videncDynamicParams.targetBitRate), (void *) VIDENC1_MAX_BR },
			{ "mpeg4spenc1", "intraFrameInterval", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.videncDynamicParams.intraFrameInterval), (void *) VIDENC1_INTRA_FI },
			{ "mpeg4spenc1", "generateHeader", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.videncDynamicParams.generateHeader), (void *) XDM_DECODE_AU },
			{ "mpeg4spenc1", "captureWidth", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.videncDynamicParams.captureWidth), (void *) 0 },
			{ "mpeg4spenc1", "forceFrame", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.videncDynamicParams.forceFrame), (void *) 0 },
			{ "mpeg4spenc1", "interFrameInterval", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.videncDynamicParams.interFrameInterval), (void *) 0 },
			{ "mpeg4spenc1", "mbDataFlag", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.videncDynamicParams.mbDataFlag), (void *) 0 },
			{ "mpeg4spenc1", "encodeMode", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.encodeMode), (void *) 1 },
			{ "mpeg4spenc1", "levelIdc", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.levelIdc), (void *) 5 },
			{ "mpeg4spenc1", "VM4RCnumFrames", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.numFrames), (void *) 2147483647 },//0x7fffffff
			{ "mpeg4spenc1", "rcAlgo", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.rcAlgo), (void *) 8 },
			{ "mpeg4spenc1", "vbvBufferSize", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.vbvBufferSize), (void *) 112 },
			{ "mpeg4spenc1", "vbvParamEnable", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.vbvParamEnable), (void *) 0 },
			{ "mpeg4spenc1", "useVOS", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.useVOS), (void *) 1 },
			{ "mpeg4spenc1", "useGOV", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.useGOV), (void *) 0 },
			{ "mpeg4spenc1", "useDataPartition", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.useDataPartition), (void *) 0 },
			{ "mpeg4spenc1", "useRVLC", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.useRVLC), (void *) 0 },
			{ "mpeg4spenc1", "maxDelay", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.maxDelay), (void *) 1000 },
			{ "mpeg4spenc1", "h263SliceMode", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1Params.h263SliceMode), (void *) 0 },
			{ "mpeg4spenc1", "resyncInterval", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.resyncInterval), (void *) 0 },
			{ "mpeg4spenc1", "hecInterval", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.hecInterval), (void *) 0 },
			{ "mpeg4spenc1", "airRate", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.airRate), (void *) 0 },
			{ "mpeg4spenc1", "mirRate", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.mirRate), (void *) 0 },
			{ "mpeg4spenc1", "qpIntra", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.qpIntra), (void *) 8 },
			{ "mpeg4spenc1", "qpInter", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.qpInter), (void *) 8 },
			{ "mpeg4spenc1", "fCode", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.fCode), (void *) 3 },
			{ "mpeg4spenc1", "useHpi", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.useHpi), (void *) 1 },
			{ "mpeg4spenc1", "useAcPred", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.useAcPred), (void *) 0 },
			{ "mpeg4spenc1", "lastFrame", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.lastFrame), (void *) 0 },
			{ "mpeg4spenc1", "MVDataEnable", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.MVDataEnable), (void *) 0 },
			{ "mpeg4spenc1", "useUMV", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.useUMV), (void *) 1 },
			{ "mpeg4spenc1", "use4MV", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.use4MV), (void *) 0 },
			{ "mpeg4spenc1", "ResyncDataEnable", DVEVM_ST_INT, &(G->mpeg4spenc1.venc1DynParams.ResyncDataEnable), (void *) 0 },
			{ "mpeg4spenc1", "framePitch", DVEVM_ST_INT, &(G->mpeg4spenc1.inBufDesc.framePitch), (void *) VIDENC1_MAX_WD },
			{ "mpeg4spenc1", "numFrames", DVEVM_ST_INT, &(G->mpeg4spenc1.numFrames), (void *) DEF_CAP_FRAMES },

			/* Parameters for xdm 1.0 MPEG4SP Video Decoder */
                        { "mpeg4spdec2", "codec", DVEVM_ST_STR, G->mpeg4spdec2.vdec2Name, DEFAULT_MPEG4DEC2_NAME },
                        { "mpeg4spdec2", "maxHeight", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecParams.viddecParams.maxHeight), (void *) PAL_YRES },
                        { "mpeg4spdec2", "maxWidth", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecParams.viddecParams.maxWidth), (void *) PAL_XRES },
                        { "mpeg4spdec2", "maxFrameRate", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecParams.viddecParams.maxFrameRate), (void *) VIDDEC2_MAX_FR },
                        { "mpeg4spdec2", "maxBitRate", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecParams.viddecParams.maxBitRate), (void *) VIDDEC2_MAX_BR },
                        { "mpeg4spdec2", "dataEndianness", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecParams.viddecParams.dataEndianness), (void *) XDM_BYTE },
                        { "mpeg4spdec2", "forceChromaFormat", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecParams.viddecParams.forceChromaFormat), (void *) XDM_YUV_422ILE },
                        { "mpeg4spdec2", "decodeHeader", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecDynParams.viddecDynamicParams.decodeHeader), (void *) XDM_DECODE_AU },
                        { "mpeg4spdec2", "displayWidth", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecDynParams.viddecDynamicParams.displayWidth), (void *) XDM_DEFAULT },
                        { "mpeg4spdec2", "frameSkipMode", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecDynParams.viddecDynamicParams.frameSkipMode), (void *) IVIDEO_NO_SKIP },
                        { "mpeg4spdec2", "frameOrder", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecDynParams.viddecDynamicParams.frameOrder), (void *) 0 },
                        { "mpeg4spdec2", "newFrameFlag", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecDynParams.viddecDynamicParams.newFrameFlag), (void *)0 },
                        { "mpeg4spdec2", "mbDataFlag", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecDynParams.viddecDynamicParams.mbDataFlag), (void *) 0 },
                        { "mpeg4spdec2", "postDeblock", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecDynParams.postDeblock), (void *) 0 },
                        { "mpeg4spdec2", "postDering", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecDynParams.postDering), (void *) 0 },
                        { "mpeg4spdec2", "errorConceal", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecDynParams.errorConceal), (void *) 0 },
                        { "mpeg4spdec2", "FrameLevelByteSwap", DVEVM_ST_INT, &(G->mpeg4spdec2.mpeg4sp_vdecDynParams.FrameLevelByteSwap), (void *) 1 }, 
                        { "mpeg4spdec2", "numFrames", DVEVM_ST_INT, &(G->mpeg4spdec2.numFrames), (void *) 100 },

			/* Parameters for MPEG2 Decoder XDM 1.2*/
			{ "mpeg2dec2", "codec", DVEVM_ST_STR, G->mpeg2dec2.vdec2Name, DEFAULT_MPEG2DEC2_NAME },
			{ "mpeg2dec2", "maxHeight", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2Params.viddecParams.maxHeight), (void *) PAL_YRES },
			{ "mpeg2dec2", "maxWidth", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2Params.viddecParams.maxWidth), (void *) PAL_XRES },
			{ "mpeg2dec2", "maxFrameRate", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2Params.viddecParams.maxFrameRate), (void *) VIDDEC2_MAX_FR },
			{ "mpeg2dec2", "maxBitRate", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2Params.viddecParams.maxBitRate), (void *) VIDDEC2_MAX_BR },
			{ "mpeg2dec2", "dataEndianness", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2Params.viddecParams.dataEndianness), (void *) XDM_BYTE },
			{ "mpeg2dec2", "forceChromaFormat", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2Params.viddecParams.forceChromaFormat), (void *) XDM_YUV_422ILE },
			{ "mpeg2dec2", "decodeHeader", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.decodeHeader), (void *) XDM_DECODE_AU },
			{ "mpeg2dec2", "displayWidth", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.displayWidth), (void *) XDM_DEFAULT },
			{ "mpeg2dec2", "frameSkipMode", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.frameSkipMode), (void *) IVIDEO_NO_SKIP },
			{ "mpeg2dec2", "frameOrder", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.frameOrder), (void *) 0 },
			{ "mpeg2dec2", "newFrameFlag", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.newFrameFlag), (void *) 0 },
			{ "mpeg2dec2", "mbDataFlag", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.mbDataFlag), (void *) 0 },
			{ "mpeg2dec2", "ppNone", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.ppNone), (void *) 0 },
			{ "mpeg2dec2", "dyna_chroma_format", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.dyna_chroma_format), (void *) XDM_YUV_422ILE },
			{ "mpeg2dec2", "displayFieldReorder", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.displayFieldReorder), (void *) 0 },
			{ "mpeg2dec2", "frameLevelByteSwap", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.frameLevelByteSwap), (void *) 0 },
			{ "mpeg2dec2", "skip_B_frame", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.skip_B_frame), (void *) 0 },
			{ "mpeg2dec2", "goto_next_I_frame", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.goto_next_I_frame), (void *) 0 },
			{ "mpeg2dec2", "skip_curr_frame", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.skip_curr_frame), (void *) 0 },
			{ "mpeg2dec2", "seek_frame_end", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.seek_frame_end), (void *) 0 },
			{ "mpeg2dec2", "getDisplayHdrInfo", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.getDisplayHdrInfo), (void *) 0 },
			{ "mpeg2dec2", "reverse_play", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.reverse_play), (void *) 0 },
			{ "mpeg2dec2", "robustness_level", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.robustness_level), (void *) 1 },
			{ "mpeg2dec2", "no_delay_display", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.no_delay_display), (void *) 0 },
			{ "mpeg2dec2", "numFrames", DVEVM_ST_INT, &(G->mpeg2dec2.numFrames), (void *) 100 },

			/* Parameters for AACHE Decoder 1.0 */
			{ "aachedec1", "codec", DVEVM_ST_STR, G->aachedec1.adecName, DEFAULT_AUDDEC1_NAME },
			{ "aachedec1", "outputPCMWidth", DVEVM_ST_INT, &(G->aachedec1.adecParams.auddec_params.outputPCMWidth), (void *) AUDDEC1_PCM_WIDTH },
			{ "aachedec1", "pcmFormat", DVEVM_ST_INT, &(G->aachedec1.adecParams.auddec_params.pcmFormat), (void *) IAUDIO_INTERLEAVED },
			{ "aachedec1", "dataEndianness", DVEVM_ST_INT, &(G->aachedec1.adecParams.auddec_params.dataEndianness), (void *) XDM_BYTE },
			{ "aachedec1", "desiredChannelMode", DVEVM_ST_INT, &(G->aachedec1.desiredChannelMode), (void *) IAUDIO_2_0 },
			{ "aachedec1", "downSampleSbrFlag", DVEVM_ST_INT, &(G->aachedec1.adecDynParams.auddec_dynamicparams.downSampleSbrFlag), (void *) 0 },
			{ "aachedec1", "sixChannelMode", DVEVM_ST_INT, &(G->aachedec1.adecParams.sixChannelMode), (void *) 1},
			{ "aachedec1", "enablePS", DVEVM_ST_INT, &(G->aachedec1.adecDynParams.enablePS), (void *) 0},
			{ "aachedec1", "ulSamplingRateIdx", DVEVM_ST_INT, &(G->aachedec1.adecDynParams.ulSamplingRateIdx), (void *) 3},
			{ "aachedec1", "nProfile", DVEVM_ST_INT, &(G->aachedec1.adecDynParams.nProfile), (void *) 0 },
			{ "aachedec1", "bRawFormat", DVEVM_ST_INT, &(G->aachedec1.adecDynParams.bRawFormat), (void *) 0 },
			{ "aachedec1", "pseudoSurroundEnableFlag", DVEVM_ST_INT, &(G->aachedec1.adecDynParams.pseudoSurroundEnableFlag), (void *) 1},
			{ "aachedec1", "enableARIBDownmix", DVEVM_ST_INT, &(G->aachedec1.adecDynParams.enableARIBDownmix), (void *) 0},
			{ "aachedec1", "inbufsize", DVEVM_ST_INT, &(G->aachedec1.inBuf.bufSizes[0]), (void *) 10000 },
			{ "aachedec1", "outbufsize", DVEVM_ST_INT, &(G->aachedec1.outBuf.bufSizes[0]), (void *) 16384 },

	                /* Parameters for xdm 1.0 JPEG Encoder */
        	        { "jpegenc1", "codec", DVEVM_ST_STR, G->jpegenc1.ienc1Name, "jpegenc" },
                	{ "jpegenc1", "maxHeight", DVEVM_ST_INT, &(G->jpegenc1.ienc1Params.params.maxHeight), (void *) PAL_YRES },
	                { "jpegenc1", "maxWidth", DVEVM_ST_INT, &(G->jpegenc1.ienc1Params.params.maxWidth), (void *) PAL_XRES },
        	        { "jpegenc1", "maxScans", DVEVM_ST_INT, &(G->jpegenc1.ienc1Params.params.maxScans), (void *) XDM_DEFAULT },
                	{ "jpegenc1", "dataEndianness", DVEVM_ST_INT, &(G->jpegenc1.ienc1Params.params.dataEndianness), (void *) XDM_BYTE },
	                { "jpegenc1", "forceChromaFormat", DVEVM_ST_INT, &(G->jpegenc1.ienc1Params.params.forceChromaFormat), (void *) XDM_YUV_422P },
        	        { "jpegenc1", "numAU", DVEVM_ST_INT, &(G->jpegenc1.ienc1DynParams.params.numAU), (void *) XDM_DEFAULT },
                	{ "jpegenc1", "inputChromaFormat", DVEVM_ST_INT, &(G->jpegenc1.ienc1DynParams.params.inputChromaFormat), (void *) XDM_YUV_422ILE },
	                { "jpegenc1", "inputHeight", DVEVM_ST_INT, &(G->jpegenc1.ienc1DynParams.params.inputHeight), (void *) IMGENC1_MAX_HT },
        	        { "jpegenc1", "inputWidth", DVEVM_ST_INT, &(G->jpegenc1.ienc1DynParams.params.inputWidth), (void *) IMGENC1_MAX_WD },
                	{ "jpegenc1", "captureWidth", DVEVM_ST_INT, &(G->jpegenc1.ienc1DynParams.params.captureWidth), (void *) IMGENC1_MAX_WD },
	                { "jpegenc1", "generateHeader", DVEVM_ST_INT, &(G->jpegenc1.ienc1DynParams.params.generateHeader), (void *) XDM_ENCODE_AU },
        	        { "jpegenc1", "qValue", DVEVM_ST_INT, &(G->jpegenc1.ienc1DynParams.params.qValue), (void *) 73 },
                	{ "jpegenc1", "MaxThumbnail_H_size_App0", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1Params.MaxThumbnail_H_size_App0), (void *) 0 },
                	{ "jpegenc1", "MaxThumbnail_V_size_App0", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1Params.MaxThumbnail_V_size_App0), (void *) 0 },
                	{ "jpegenc1", "MaxThumbnail_H_size_App1", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1Params.MaxThumbnail_H_size_App1), (void *) 0 },
                	{ "jpegenc1", "MaxThumbnail_V_size_App1", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1Params.MaxThumbnail_V_size_App1), (void *) 0 },
                	{ "jpegenc1", "MaxThumbnail_H_size_App13", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1Params.MaxThumbnail_H_size_App13), (void *) 0 },
                	{ "jpegenc1", "MaxThumbnail_V_size_App13", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1Params.MaxThumbnail_V_size_App13), (void *) 0 },
        	        { "jpegenc1", "captureHeight", DVEVM_ST_INT, &(G->jpegenc1.ienc1DynParams.captureHeight), (void *) 0 },
        	        { "jpegenc1", "DRI_Interval", DVEVM_ST_INT, &(G->jpegenc1.ienc1DynParams.DRI_Interval), (void *) 0 },
        	        { "jpegenc1", "Thumbnail_Index_App0", DVEVM_ST_CHAR, &(G->jpegenc1.ienc1DynParams.Thumbnail_Index_App0), (void *) 0 },
        	        { "jpegenc1", "Thumbnail_Index_App1", DVEVM_ST_CHAR, &(G->jpegenc1.ienc1DynParams.Thumbnail_Index_App1), (void *) 0 },
        	        { "jpegenc1", "Thumbnail_Index_App13", DVEVM_ST_CHAR, &(G->jpegenc1.ienc1DynParams.Thumbnail_Index_App13), (void *) 0 },
        	        { "jpegenc1", "APPN0_numBufs", DVEVM_ST_CHAR, &(G->jpegenc1.ienc1DynParams.APPN0_numBufs), (void *) 0 },
        	        { "jpegenc1", "APPN1_numBufs", DVEVM_ST_CHAR, &(G->jpegenc1.ienc1DynParams.APPN1_numBufs), (void *) 0 },
        	        { "jpegenc1", "APPN13_numBufs", DVEVM_ST_CHAR, &(G->jpegenc1.ienc1DynParams.APPN13_numBufs), (void *) 0 },
        	        { "jpegenc1", "APPN0_startBuf", DVEVM_ST_CHAR, &(G->jpegenc1.ienc1DynParams.APPN0_startBuf), (void *) 0 },
        	        { "jpegenc1", "APPN1_startBuf", DVEVM_ST_CHAR, &(G->jpegenc1.ienc1DynParams.APPN1_startBuf), (void *) 0 },
		        { "jpegenc1", "APPN13_startBuf", DVEVM_ST_CHAR, &(G->jpegenc1.ienc1DynParams.APPN13_startBuf), (void *) 0 },
        	        { "jpegenc1", "COMMENT_startBuf", DVEVM_ST_CHAR, &(G->jpegenc1.ienc1DynParams.COMMENT_startBuf), (void *) 0 },
        	        { "jpegenc1", "COMMENT_insert", DVEVM_ST_CHAR, &(G->jpegenc1.ienc1DynParams.COMMENT_insert), (void *) 0 },
                	{ "jpegenc1", "Thumbnail_H_size_App1", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1DynParams.Thumbnail_H_size_App1), (void *) 0 },
                	{ "jpegenc1", "Thumbnail_V_size_App1", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1DynParams.Thumbnail_V_size_App1), (void *) 0 },
                	{ "jpegenc1", "Thumbnail_H_size_App0", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1DynParams.Thumbnail_H_size_App0), (void *) 0 },
                	{ "jpegenc1", "Thumbnail_V_size_App0", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1DynParams.Thumbnail_V_size_App0), (void *) 0 },
                	{ "jpegenc1", "Thumbnail_H_size_App13", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1DynParams.Thumbnail_H_size_App13), (void *) 0 },
                	{ "jpegenc1", "Thumbnail_V_size_App13", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1DynParams.Thumbnail_V_size_App13), (void *) 0 },



		};

		DVEVM_CODEC_NUM = sizeof(dvtbMapArr) / sizeof(dvtbMapTable);
		MAP = (dvtbMapTable *) calloc(DVEVM_CODEC_NUM, sizeof(dvtbMapTable));
		if (MAP != NULL)
		{
			memcpy(MAP, dvtbMapArr, DVEVM_CODEC_NUM * sizeof(dvtbMapTable));
			valInitialized = DVEVM_ST_TRUE;
		}
	}
}
