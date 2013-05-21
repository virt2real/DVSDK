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
#if 0
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
#endif
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

#if 0
			/* Parameters for Power Manager */
			{ "pwrmanager", "scalingGovernor", DVEVM_ST_STR, G->pmanager.scalingGovernor, "performance" },
			{ "pwrmanager", "vdd1PState", DVEVM_ST_INT, &(G->pmanager.vdd1PState), (void *) 4 },
			{ "pwrmanager", "vdd2PState", DVEVM_ST_INT, &(G->pmanager.vdd2PState), (void *) 3 },
			{ "pwrmanager", "cpuIdleState", DVEVM_ST_INT, &(G->pmanager.cpuIdleState), (void *) 1 },
#endif
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
