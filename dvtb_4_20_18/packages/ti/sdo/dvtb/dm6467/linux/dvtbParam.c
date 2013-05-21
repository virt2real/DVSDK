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

DvevmStMapTable *MAP = NULL;
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
		DvevmStMapTable dvevmStMapArr[] =
		{
		/* All global parameters */
		{ "engine", "name", DVEVM_ST_STR, G->eng.name, DEFAULT_ENGINE_NAME },

#if 0
				/* Parameters for OSS audio device */
				{	"audio", "device", DVEVM_ST_STR, G->aud.device, DEF_SND_DEVICE},
				{	"audio", "samplesize", DVEVM_ST_INT, &(G->aud.sampleSize), (void *) DEF_SAMPLE_SIZE},
				{	"audio", "samplerate", DVEVM_ST_INT, &(G->aud.sampleRate), (void *) DEF_SAMPLE_RATE},
				{	"audio", "channels", DVEVM_ST_INT, &(G->aud.numChannels), (void *) DEF_NUM_CHANNELS},
				{	"audio", "source", DVEVM_ST_INT, &(G->aud.src), (void *) MIC},
#endif
				/* Parameters for ALSA audio device */
				{ "audio", "device", DVEVM_ST_STR, G->aud.device, DEF_SND_DEVICE },
				{ "audio", "format", DVEVM_ST_INT, &(G->aud.format), (void *) SND_PCM_FORMAT_S16_LE },
				{ "audio", "samplerate", DVEVM_ST_INT, &(G->aud.sampleRate), (void *) DEF_SAMPLE_RATE },
				{ "audio", "channels", DVEVM_ST_INT, &(G->aud.numChannels), (void *) DEF_NUM_CHANNELS },
				{ "audio", "type", DVEVM_ST_INT, &(G->aud.blocking_mode), 0 },

				/* Parameters for VPBE device */
				{ "vpbe", "device", DVEVM_ST_STR, G->vpbe.device, VID_DEVICE },
				{ "vpbe", "width", DVEVM_ST_INT, &(G->vpbe.imageWidth), (void *) DEF_XRES },
				{ "vpbe", "height", DVEVM_ST_INT, &(G->vpbe.imageHeight), (void *) DEF_YRES },
				{ "vpbe", "std", DVEVM_ST_INT, &(G->vpbe.dispStd), (void *) DVEVM_ST_1080I_30 },
				{ "vpbe", "output", DVEVM_ST_INT, &(G->vpbe.dispOutput), (void *) DVEVM_ST_COMPONENT },

				/* Parameters for VPFE device */
				{ "vpfe", "device", DVEVM_ST_STR, G->vpfe.device, VIDCAP_DEVICE },
				{ "vpfe", "standard", DVEVM_ST_INT, &(G->vpfe.capStd), (void *) VID_STD_NA },
				{ "vpfe", "format", DVEVM_ST_INT, &(G->vpfe.capFmt), (void *) VID_FMT_YUV422UVP },
				{ "vpfe", "input", DVEVM_ST_INT, &(G->vpfe.input), (void *) 1 },
				{ "vpfe", "width", DVEVM_ST_INT, &(G->vpfe.capWidth), (void *) NTSC_WIDTH },
				{ "vpfe", "height", DVEVM_ST_INT, &(G->vpfe.capHeight), (void *) NTSC_HEIGHT },

				/* Parameters for Audio Decoder */
				{ "auddec", "codec", DVEVM_ST_STR, G->adec.adecName, DEFAULT_AUDDEC_NAME },
				{ "auddec", "maxSampleRate", DVEVM_ST_INT, &(G->adec.adecParams.maxSampleRate), (void *) AUDDEC_MAX_SR },
				{ "auddec", "maxBitrate", DVEVM_ST_INT, &(G->adec.adecParams.maxBitrate), (void *) AUDDEC_MAX_BR },
				{ "auddec", "maxNoOfCh", DVEVM_ST_INT, &(G->adec.adecParams.maxNoOfCh), (void *) IAUDIO_STEREO },
				{ "auddec", "dataEndianness", DVEVM_ST_INT, &(G->adec.adecParams.dataEndianness), (void *) XDM_BYTE },
				{ "auddec", "outputFormat", DVEVM_ST_INT, &(G->adec.adecDynParams.outputFormat), (void *) IAUDIO_INTERLEAVED },
				{ "auddec", "inbufsize", DVEVM_ST_INT, &(G->adec.inBuf.size), (void *) AUDDEC_INBUF_SIZE },
				{ "auddec", "outbufsize", DVEVM_ST_INT, &(G->adec.outBuf.size), (void *) AUDDEC_OUTBUF_SIZE },

				/* Parameters for Speech Encoder */
				{ "sphenc", "codec", DVEVM_ST_STR, G->senc.sencName, DEFAULT_SPHENC_NAME },
				{ "sphenc", "seconds", DVEVM_ST_INT, &(G->senc.seconds), (void *) DEFAULT_SPHENC_TIME },
				{ "sphenc", "frameSize", DVEVM_ST_INT, &(G->senc.sencParams.frameSize), (void *) SPHENC_FRAME_SIZE },
				{ "sphenc", "compandingLaw", DVEVM_ST_INT, &(G->senc.sencParams.compandingLaw), (void *) SPHENC_CL },
				{ "sphenc", "packingType", DVEVM_ST_INT, &(G->senc.sencParams.packingType), (void *) SPHENC_PT },
				{ "sphenc", "vadSelection", DVEVM_ST_INT, &(G->senc.sencParams.vadSelection), (void *) SPHENC_VS },
				{ "sphenc", "inbufsize", DVEVM_ST_INT, &(G->senc.inBuf.size), (void *) (SPHENC_FRAME_SIZE * 2) },
				{ "sphenc", "outbufsize", DVEVM_ST_INT, &(G->senc.outBuf.size), (void *) SPHENC_FRAME_SIZE },

				/* Parameters for Speech Decoder */
				{ "sphdec", "codec", DVEVM_ST_STR, G->sdec.sdecName, DEFAULT_SPHDEC_NAME },
				{ "sphdec", "dataEnable", DVEVM_ST_INT, &(G->sdec.sdecParams.dataEnable), (void *) SPHDEC_DE },
				{ "sphdec", "compandingLaw", DVEVM_ST_INT, &(G->sdec.sdecParams.compandingLaw), (void *) 1 /*SPHDEC_CL*/},
				{ "sphdec", "packingType", DVEVM_ST_INT, &(G->sdec.sdecParams.packingType), (void *) SPHDEC_PT },
				{ "sphdec", "inbufsize", DVEVM_ST_INT, &(G->sdec.inBuf.size), (void *) SPHDEC_INBUF_SIZE },
				{ "sphdec", "outbufsize", DVEVM_ST_INT, &(G->sdec.outBuf.size), (void *) SPHDEC_OUTBUF_SIZE },

				/* Parameters for Video Encoder XDM 1.0*/
				{ "videnc1", "codec", DVEVM_ST_STR, G->venc1.venc1Name, DEFAULT_VIDENC1_NAME },
				{ "videnc1", "encodingPreset", DVEVM_ST_INT, &(G->venc1.venc1Params.encodingPreset), (void *) XDM_DEFAULT },
				{ "videnc1", "rateControlPreset", DVEVM_ST_INT, &(G->venc1.venc1Params.rateControlPreset), (void *) 1 },
				{ "videnc1", "maxHeight", DVEVM_ST_INT, &(G->venc1.venc1Params.maxHeight), (void *) VIDENC1_MAX_HT },
				{ "videnc1", "maxWidth", DVEVM_ST_INT, &(G->venc1.venc1Params.maxWidth), (void *) VIDENC1_MAX_WD },
				{ "videnc1", "maxFrameRate", DVEVM_ST_INT, &(G->venc1.venc1Params.maxFrameRate), (void *) VIDENC1_MAX_FR },
				{ "videnc1", "maxBitRate", DVEVM_ST_INT, &(G->venc1.venc1Params.maxBitRate), (void *) VIDENC1_MAX_BR },
				{ "videnc1", "dataEndianness", DVEVM_ST_INT, &(G->venc1.venc1Params.dataEndianness), (void *) XDM_BYTE },
				{ "videnc1", "maxInterFrameInterval", DVEVM_ST_INT, &(G->venc1.venc1Params.maxInterFrameInterval), (void *) 0 },
				{ "videnc1", "inputChromaFormat", DVEVM_ST_INT, &(G->venc1.venc1Params.inputChromaFormat), (void *) XDM_YUV_420P },
				{ "videnc1", "inputContentType", DVEVM_ST_INT, &(G->venc1.venc1Params.inputContentType), (void *) IVIDEO_PROGRESSIVE },
				{ "videnc1", "reconChromaFormat", DVEVM_ST_INT, &(G->venc1.venc1Params.reconChromaFormat), (void *) XDM_YUV_420P },
				{ "videnc1", "inputHeight", DVEVM_ST_INT, &(G->venc1.venc1DynParams.inputHeight), (void *) VIDENC1_MAX_HT },
				{ "videnc1", "inputWidth", DVEVM_ST_INT, &(G->venc1.venc1DynParams.inputWidth), (void *) VIDENC1_MAX_WD },
				{ "videnc1", "refFrameRate", DVEVM_ST_INT, &(G->venc1.venc1DynParams.refFrameRate), (void *) VIDENC1_MAX_FR },
				{ "videnc1", "targetFrameRate", DVEVM_ST_INT, &(G->venc1.venc1DynParams.targetFrameRate), (void *) VIDENC1_MAX_FR },
				{ "videnc1", "targetBitRate", DVEVM_ST_INT, &(G->venc1.venc1DynParams.targetBitRate), (void *) VIDENC1_MAX_BR },
				{ "videnc1", "intraFrameInterval", DVEVM_ST_INT, &(G->venc1.venc1DynParams.intraFrameInterval), (void *) VIDENC1_INTRA_FI },
				{ "videnc1", "generateHeader", DVEVM_ST_INT, &(G->venc1.venc1DynParams.generateHeader), (void *) XDM_DECODE_AU },
				{ "videnc1", "captureWidth", DVEVM_ST_INT, &(G->venc1.venc1DynParams.captureWidth), (void *) 0 },
				{ "videnc1", "forceFrame", DVEVM_ST_INT, &(G->venc1.venc1DynParams.forceFrame), (void *) -1 },
				{ "videnc1", "interFrameInterval", DVEVM_ST_INT, &(G->venc1.venc1DynParams.interFrameInterval), (void *) 0 },
				{ "videnc1", "mbDataFlag", DVEVM_ST_INT, &(G->venc1.venc1DynParams.mbDataFlag), (void *) 0 },
				{ "videnc1", "framePitch", DVEVM_ST_INT, &(G->venc1.inBufDesc.framePitch), (void *) VIDENC1_DMAI_DEFAULT_WD },
				{ "videnc1", "numFrames", DVEVM_ST_INT, &(G->venc1.numFrames), (void *) DEF_CAP_FRAMES },

				/* Parameters for AAC HE Encoder XDM 1.0 Base Params*/
				{ "audenc1", "codec", DVEVM_ST_STR, G->aenc1.audenc1Name, "aacheenc" },
				{ "audenc1", "seconds", DVEVM_ST_INT, &(G->aenc1.seconds), (void *) DEFAULT_AUDENC1_TIME },
				{ "audenc1", "sampleRate", DVEVM_ST_INT, &(G->aenc1.audenc1Params.sampleRate), (void *) 44100 },
				{ "audenc1", "bitRate", DVEVM_ST_INT, &(G->aenc1.audenc1Params.bitRate), (void *) 64000 },
				{ "audenc1", "channelMode", DVEVM_ST_INT, &(G->aenc1.audenc1Params.channelMode), (void *) 1 },
				{ "audenc1", "dataEndianness", DVEVM_ST_INT, &(G->aenc1.audenc1Params.dataEndianness), (void *) (XDAS_Int32)(XDM_LE_16) },
				{ "audenc1", "encMode", DVEVM_ST_INT, &(G->aenc1.audenc1Params.encMode), (void *) 0 },
				{ "audenc1", "inputFormat", DVEVM_ST_INT, &(G->aenc1.audenc1Params.inputFormat), (void *) 1 },
				{ "audenc1", "inputBitsPerSample", DVEVM_ST_INT, &(G->aenc1.audenc1Params.inputBitsPerSample), (void *) 16 },
				{ "audenc1", "maxBitRate", DVEVM_ST_INT, &(G->aenc1.audenc1Params.maxBitRate), (void *) 192000 },
				{ "audenc1", "dualMonoMode", DVEVM_ST_INT, &(G->aenc1.audenc1Params.dualMonoMode), (void *) 0 },
				{ "audenc1", "crcFlag", DVEVM_ST_INT, &(G->aenc1.audenc1Params.crcFlag), (void *) 0 },
				{ "audenc1", "ancFlag", DVEVM_ST_INT, &(G->aenc1.audenc1Params.ancFlag), (void *) AUDENC1_ANC },
				{ "audenc1", "lfeFlag", DVEVM_ST_INT, &(G->aenc1.audenc1Params.lfeFlag), (void *) 0 },
				{ "audenc1", "dynamicparams.sampleRate", DVEVM_ST_INT, &(G->aenc1.audenc1DynParams.sampleRate), (void *) 44100 },
				{ "audenc1", "dynamicparams.bitRate", DVEVM_ST_INT, &(G->aenc1.audenc1DynParams.bitRate), (void *) 64000 },
				{ "audenc1", "dynamicparams.channelMode", DVEVM_ST_INT, &(G->aenc1.audenc1DynParams.channelMode), (void *) 1 },
				{ "audenc1", "dynamicparams.lfeFlag", DVEVM_ST_INT, &(G->aenc1.audenc1DynParams.lfeFlag), (void *) 0 },
				{ "audenc1", "dynamicparams.dualMonoMode", DVEVM_ST_INT, &(G->aenc1.audenc1DynParams.dualMonoMode), (void *) 0 },
				{ "audenc1", "dynamicparams.inputBitsPerSample", DVEVM_ST_INT, &(G->aenc1.audenc1DynParams.inputBitsPerSample), (void *) 16 },

				/* Parameters for Audio Decoder 1.0 */
				{ "auddec1", "codec", DVEVM_ST_STR, G->adec1.adecName, DEFAULT_AUDDEC1_NAME },
				{ "auddec1", "outputPCMWidth", DVEVM_ST_INT, &(G->adec1.adecParams.outputPCMWidth), (void *) AUDDEC1_PCM_WIDTH },
				{ "auddec1", "pcmFormat", DVEVM_ST_INT, &(G->adec1.adecParams.pcmFormat), (void *) IAUDIO_INTERLEAVED },
				{ "auddec1", "dataEndianness", DVEVM_ST_INT, &(G->adec1.adecParams.dataEndianness), (void *) XDM_BYTE },
				{ "auddec1", "desiredChannelMode", DVEVM_ST_INT, &(G->adec1.desiredChannelMode), (void *) IAUDIO_2_0 },
				{ "auddec1", "downSampleSbrFlag", DVEVM_ST_INT, &(G->adec1.adecDynParams.downSampleSbrFlag), (void *) 0 },
				{ "auddec1", "inbufsize", DVEVM_ST_INT, &(G->adec1.inBuf.bufSizes[0]), (void *) 10000 },
				{ "auddec1", "outbufsize", DVEVM_ST_INT, &(G->adec1.outBuf.bufSizes[0]), (void *) 16384 },

				// Parameters for Speech 1.0 Encoder
				{ "sphenc1", "codec", DVEVM_ST_STR, G->senc1.sencName, DEFAULT_SPHENC1_NAME },
				{ "sphenc1", "seconds", DVEVM_ST_INT, &(G->senc1.seconds), (void *) DEFAULT_SPHENC1_TIME },
				{ "sphenc1", "frameSize", DVEVM_ST_SHORT, &(G->senc1.sencParams.frameSize), (void *) SPHENC1_FRAME_SIZE },
				{ "sphenc1", "compandingLaw", DVEVM_ST_SHORT, &(G->senc1.sencParams.compandingLaw), (void *) SPHENC1_CL },
				{ "sphenc1", "packingType", DVEVM_ST_SHORT, &(G->senc1.sencParams.packingType), (void *) SPHENC1_PT },
				{ "sphenc1", "vadSelection", DVEVM_ST_SHORT, &(G->senc1.sencParams.vadSelection), (void *) SPHENC1_VS },
				{ "sphenc1", "codecSelection", DVEVM_ST_SHORT, &(G->senc1.sencParams.codecSelection), (void *) 0 },
				{ "sphenc1", "bitRate", DVEVM_ST_SHORT, &(G->senc1.sencParams.bitRate), (void *) 0 },
				{ "sphenc1", "vadFlag", DVEVM_ST_SHORT, &(G->senc1.sencDynParams.vadFlag), (void *) ISPEECH1_VADFLAG_OFF },
				{ "sphenc1", "inbufsize", DVEVM_ST_INT, &(G->senc1.inBuf.size), (void *) (SPHENC1_FRAME_SIZE * 2) },
				{ "sphenc1", "outbufsize", DVEVM_ST_INT, &(G->senc1.outBuf.size), (void *) SPHENC1_FRAME_SIZE },

				/* Parameters for Speech 1.0 Decoder */
				{ "sphdec1", "codec", DVEVM_ST_STR, G->sdec1.sdecName, DEFAULT_SPHDEC1_NAME },
				{ "sphdec1", "compandingLaw", DVEVM_ST_SHORT, &(G->sdec1.sdecParams.compandingLaw), (void *) SPHDEC1_CL },
				{ "sphdec1", "packingType", DVEVM_ST_SHORT, &(G->sdec1.sdecParams.packingType), (void *) SPHDEC1_PT },
				{ "sphdec1", "codecSelection", DVEVM_ST_SHORT, &(G->sdec1.sdecParams.codecSelection), (void *) 0 },
				{ "sphdec1", "bitRate", DVEVM_ST_SHORT, &(G->sdec1.sdecParams.bitRate), (void *) 12000 },
				{ "sphdec1", "inbufsize", DVEVM_ST_INT, &(G->sdec1.inBuf.size), (void *) SPHDEC1_INBUF_SIZE },
				{ "sphdec1", "outbufsize", DVEVM_ST_INT, &(G->sdec1.outBuf.size), (void *) SPHDEC1_OUTBUF_SIZE },

				/* Parameters for MPEG2 Decoder XDM 1.2*/
				{ "viddec2", "codec", DVEVM_ST_STR, G->vdec2.vdec2Name, DEFAULT_VIDDEC2_NAME },
				{ "viddec2", "maxHeight", DVEVM_ST_INT, &(G->vdec2.vdec2Params.maxHeight), (void *) VIDDEC2_MAX_HT },
				{ "viddec2", "maxWidth", DVEVM_ST_INT, &(G->vdec2.vdec2Params.maxWidth), (void *) VIDDEC2_MAX_WD },
				{ "viddec2", "maxFrameRate", DVEVM_ST_INT, &(G->vdec2.vdec2Params.maxFrameRate), (void *) VIDDEC2_MAX_FR },
				{ "viddec2", "maxBitRate", DVEVM_ST_INT, &(G->vdec2.vdec2Params.maxBitRate), (void *) VIDDEC2_MAX_BR },
				{ "viddec2", "dataEndianness", DVEVM_ST_INT, &(G->vdec2.vdec2Params.dataEndianness), (void *) XDM_BYTE },
				{ "viddec2", "forceChromaFormat", DVEVM_ST_INT, &(G->vdec2.vdec2Params.forceChromaFormat), (void *) XDM_YUV_420SP },
				{ "viddec2", "decodeHeader", DVEVM_ST_INT, &(G->vdec2.vdec2DynParams.decodeHeader), (void *) XDM_DECODE_AU },
				{ "viddec2", "displayWidth", DVEVM_ST_INT, &(G->vdec2.vdec2DynParams.displayWidth), (void *) XDM_DEFAULT },
				{ "viddec2", "frameSkipMode", DVEVM_ST_INT, &(G->vdec2.vdec2DynParams.frameSkipMode), (void *) IVIDEO_NO_SKIP },
				{ "viddec2", "frameOrder", DVEVM_ST_INT, &(G->vdec2.vdec2DynParams.frameOrder), (void *) 0 },
				{ "viddec2", "newFrameFlag", DVEVM_ST_INT, &(G->vdec2.vdec2DynParams.newFrameFlag), (void *) 0 },
				{ "viddec2", "mbDataFlag", DVEVM_ST_INT, &(G->vdec2.vdec2DynParams.mbDataFlag), (void *) 0 },
				{ "viddec2", "numFrames", DVEVM_ST_INT, &(G->vdec2.numFrames), (void *) 100 },

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

				/* Parameters for MPEG2 Decoder XDM 1.2*/
				{ "mpeg2dec2", "codec", DVEVM_ST_STR, G->mpeg2dec2.vdec2Name, DEFAULT_MPEG2DEC2_NAME },
				{ "mpeg2dec2", "maxHeight", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2Params.viddecParams.maxHeight), (void *) VIDDEC2_MAX_HT },
				{ "mpeg2dec2", "maxWidth", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2Params.viddecParams.maxWidth), (void *) VIDDEC2_MAX_WD },
				{ "mpeg2dec2", "maxFrameRate", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2Params.viddecParams.maxFrameRate), (void *) VIDDEC2_MAX_FR },
				{ "mpeg2dec2", "maxBitRate", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2Params.viddecParams.maxBitRate), (void *) VIDDEC2_MAX_BR },
				{ "mpeg2dec2", "dataEndianness", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2Params.viddecParams.dataEndianness), (void *) XDM_BYTE },
				{ "mpeg2dec2", "forceChromaFormat", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2Params.viddecParams.forceChromaFormat), (void *) XDM_YUV_420SP },
				{ "mpeg2dec2", "DeBlocking", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2Params.DeBlocking), (void *) 0 },
				{ "mpeg2dec2", "decodeHeader", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.decodeHeader), (void *) XDM_DECODE_AU },
				{ "mpeg2dec2", "displayWidth", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.displayWidth), (void *) XDM_DEFAULT },
				{ "mpeg2dec2", "frameSkipMode", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.frameSkipMode), (void *) IVIDEO_NO_SKIP },
				{ "mpeg2dec2", "frameOrder", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.frameOrder), (void *) 0 },
				{ "mpeg2dec2", "newFrameFlag", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.newFrameFlag), (void *) 0 },
				{ "mpeg2dec2", "mbDataFlag", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.viddecDynamicParams.mbDataFlag), (void *) 0 },
				{ "mpeg2dec2", "bottom_fld_DDR_Opt", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.bottom_fld_DDR_Opt), (void *) 0 },
				{ "mpeg2dec2", "mb_error_reporting", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.mb_error_reporting), (void *) 1 },
				{ "mpeg2dec2", "errorConceal", DVEVM_ST_INT, &(G->mpeg2dec2.vdec2DynParams.errorConceal), (void *) 1 },
				{ "mpeg2dec2", "numFrames", DVEVM_ST_INT, &(G->mpeg2dec2.numFrames), (void *) 100 },

				/* Parameters for MPEG2 Decoder XDM 1.2*/
				{ "mpeg4dec2", "codec", DVEVM_ST_STR, G->mpeg4dec2.vdec2Name, DEFAULT_MPEG4DEC2_NAME },
				{ "mpeg4dec2", "maxHeight", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2Params.viddecParams.maxHeight), (void *) 576 },
				{ "mpeg4dec2", "maxWidth", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2Params.viddecParams.maxWidth), (void *) 864 },
				{ "mpeg4dec2", "maxFrameRate", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2Params.viddecParams.maxFrameRate), (void *) VIDDEC2_MAX_FR },
				{ "mpeg4dec2", "maxBitRate", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2Params.viddecParams.maxBitRate), (void *) VIDDEC2_MAX_BR },
				{ "mpeg4dec2", "dataEndianness", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2Params.viddecParams.dataEndianness), (void *) XDM_BYTE },
				{ "mpeg4dec2", "forceChromaFormat", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2Params.viddecParams.forceChromaFormat), (void *) XDM_YUV_420SP },
				{ "mpeg4dec2", "display_delay", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2Params.display_delay), (void *) 0 },
				{ "mpeg4dec2", "reset_vIMCOP_every_frame", DVEVM_ST_CHAR, &(G->mpeg4dec2.vdec2Params.reset_vIMCOP_every_frame), (void *) 0 },
				{ "mpeg4dec2", "decodeHeader", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2DynParams.viddecDynamicParams.decodeHeader), (void *) XDM_DECODE_AU },
				{ "mpeg4dec2", "displayWidth", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2DynParams.viddecDynamicParams.displayWidth), (void *) 0 },
				{ "mpeg4dec2", "frameSkipMode", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2DynParams.viddecDynamicParams.frameSkipMode), (void *) IVIDEO_NO_SKIP },
				{ "mpeg4dec2", "frameOrder", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2DynParams.viddecDynamicParams.frameOrder), (void *) 0 },
				{ "mpeg4dec2", "newFrameFlag", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2DynParams.viddecDynamicParams.newFrameFlag), (void *) 0 },
				{ "mpeg4dec2", "mbDataFlag", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2DynParams.viddecDynamicParams.mbDataFlag), (void *) 0 },
				{ "mpeg4dec2", "outloopDeblocking", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2DynParams.outloopDeblocking), (void *) 0 },
				{ "mpeg4dec2", "outloopDeRinging", DVEVM_ST_INT, &(G->mpeg4dec2.vdec2DynParams.outloopDeRinging), (void *) 0 },
				{ "mpeg4dec2", "numFrames", DVEVM_ST_INT, &(G->mpeg4dec2.numFrames), (void *) 100 },

#ifdef _DVTB_H264DEC_
				/* Parameters for H264 Decoder XDM 1.2*/
				{ "h264dec2", "codec", DVEVM_ST_STR, G->h264dec2.vdec2Name, DEFAULT_H264DEC2_NAME },
				{ "h264dec2", "maxHeight", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.viddecParams.maxHeight), (void *) VIDDEC2_MAX_HT },
				{ "h264dec2", "maxWidth", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.viddecParams.maxWidth), (void *) VIDDEC2_MAX_WD },
				{ "h264dec2", "maxFrameRate", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.viddecParams.maxFrameRate), (void *) VIDDEC2_MAX_FR },
				{ "h264dec2", "maxBitRate", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.viddecParams.maxBitRate), (void *) VIDDEC2_MAX_BR },
				{ "h264dec2", "dataEndianness", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.viddecParams.dataEndianness), (void *) XDM_BYTE },
				{ "h264dec2", "forceChromaFormat", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.viddecParams.forceChromaFormat), (void *) XDM_YUV_420SP },
				{ "h264dec2", "displayDelay", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.displayDelay), (void *) 16 },
				{ "h264dec2", "presetLevelIdc", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.presetLevelIdc), (void *) Level4},
				{ "h264dec2", "presetProfileIdc", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.presetProfileIdc), (void *) Profile_Any },
				{ "h264dec2", "temporalDirModePred", DVEVM_ST_INT, &(G->h264dec2.vdec2Params.temporalDirModePred), (void *) 1 },
				{ "h264dec2", "decodeHeader", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.viddecDynamicParams.decodeHeader), (void *) XDM_DECODE_AU },
				{ "h264dec2", "displayWidth", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.viddecDynamicParams.displayWidth), (void *) XDM_DEFAULT },
				{ "h264dec2", "frameSkipMode", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.viddecDynamicParams.frameSkipMode), (void *) IVIDEO_NO_SKIP },
				{ "h264dec2", "frameOrder", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.viddecDynamicParams.frameOrder), (void *) 0 },
				{ "h264dec2", "newFrameFlag", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.viddecDynamicParams.newFrameFlag), (void *) 0 },
				{ "h264dec2", "mbDataFlag", DVEVM_ST_INT, &(G->h264dec2.vdec2DynParams.viddecDynamicParams.mbDataFlag), (void *) 0 },
				{ "h264dec2", "numFrames", DVEVM_ST_INT, &(G->h264dec2.numFrames), (void *) 100 },

#endif

#ifdef _DVTB_H2641080p60VDEC_
				/* Parameters for H264 Decoder XDM 1.2*/
				{ "h2641080pdec2", "codec", DVEVM_ST_STR, G->h2641080pdec2.vdec2Name, DEFAULT_H2641080pDEC2_NAME },
				{ "h2641080pdec2", "maxHeight", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2Params.viddecParams.maxHeight), (void *) VIDDEC2_MAX_HT },
				{ "h2641080pdec2", "maxWidth", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2Params.viddecParams.maxWidth), (void *) VIDDEC2_MAX_WD },
				{ "h2641080pdec2", "maxFrameRate", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2Params.viddecParams.maxFrameRate), (void *) VIDDEC2_MAX_FR },
				{ "h2641080pdec2", "maxBitRate", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2Params.viddecParams.maxBitRate), (void *) VIDDEC2_MAX_BR },
				{ "h2641080pdec2", "dataEndianness", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2Params.viddecParams.dataEndianness), (void *) XDM_BYTE },
				{ "h2641080pdec2", "forceChromaFormat", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2Params.viddecParams.forceChromaFormat), (void *) XDM_YUV_420SP },
				{ "h2641080pdec2", "displayDelay", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2Params.displayDelay), (void *) 16 },
				{ "h2641080pdec2", "presetLevelIdc", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2Params.presetLevelIdc), (void *)  H2641080P60D_Level4},
				{ "h2641080pdec2", "presetProfileIdc", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2Params.presetProfileIdc), (void *) H2641080P60D_Profile_Any },
				{ "h2641080pdec2", "temporalDirModePred", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2Params.temporalDirModePred), (void *) 1 },
				{ "h2641080pdec2", "decodeHeader", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2DynParams.viddecDynamicParams.decodeHeader), (void *) XDM_DECODE_AU },
				{ "h2641080pdec2", "displayWidth", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2DynParams.viddecDynamicParams.displayWidth), (void *) XDM_DEFAULT },
				{ "h2641080pdec2", "frameSkipMode", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2DynParams.viddecDynamicParams.frameSkipMode), (void *) IVIDEO_NO_SKIP },
				{ "h2641080pdec2", "frameOrder", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2DynParams.viddecDynamicParams.frameOrder), (void *) 0 },
				{ "h2641080pdec2", "newFrameFlag", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2DynParams.viddecDynamicParams.newFrameFlag), (void *) 0 },
				{ "h2641080pdec2", "mbDataFlag", DVEVM_ST_INT, &(G->h2641080pdec2.vdec2DynParams.viddecDynamicParams.mbDataFlag), (void *) 0 },
				{ "h2641080pdec2", "numFrames", DVEVM_ST_INT, &(G->h2641080pdec2.numFrames), (void *) 100 },
#endif

				/* Parameters for MP3 XDM1 Decoder */
				{ "mp3basedec1", "codec", DVEVM_ST_STR, G->mp3basedec1.adecName, DEFAULT_MP3BASEDEC1_NAME },
				{ "mp3basedec1", "outputPCMWidth", DVEVM_ST_INT, &(G->mp3basedec1.adecParams.outputPCMWidth), (void *) MP3BASEDEC1_PCM_WIDTH },				
				{ "mp3basedec1", "pcmFormat", DVEVM_ST_INT, &(G->mp3basedec1.adecParams.pcmFormat), (void *) IAUDIO_INTERLEAVED },
				{ "mp3basedec1", "dataEndianness", DVEVM_ST_INT, &(G->mp3basedec1.adecParams.dataEndianness), (void *) XDM_BYTE },
				{ "mp3basedec1", "downSampleSbrFlag", DVEVM_ST_INT, &(G->mp3basedec1.adecDynParams.downSampleSbrFlag), (void *) XDAS_FALSE },
				{ "mp3basedec1", "inbufsize", DVEVM_ST_INT, &(G->mp3basedec1.inBuf.size), (void *) MP3BASEDEC1_INBUF_SIZE },
				{ "mp3basedec1", "outbufsize", DVEVM_ST_INT, &(G->mp3basedec1.outBuf.size), (void *) MP3BASEDEC1_OUTBUF_SIZE },


				{ "mpeg4enc1", "codec", DVEVM_ST_STR, G->mpeg4enc1.venc1Name, DEFAULT_MPEG4ENC1_NAME },
				{ "mpeg4enc1", "encodingPreset", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.videncParams.encodingPreset), (void *) XDM_DEFAULT },
				{ "mpeg4enc1", "rateControlPreset", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.videncParams.rateControlPreset), (void *) 1 }, //1 earlier
				{ "mpeg4enc1", "maxHeight", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.videncParams.maxHeight), (void *) VIDENC1_MAX_HT },
				{ "mpeg4enc1", "maxWidth", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.videncParams.maxWidth), (void *) VIDENC1_MAX_WD },
				{ "mpeg4enc1", "maxFrameRate", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.videncParams.maxFrameRate), (void *) VIDENC1_MAX_FR },
				{ "mpeg4enc1", "maxBitRate", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.videncParams.maxBitRate), (void *) VIDENC1_MAX_BR },
				{ "mpeg4enc1", "dataEndianness", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.videncParams.dataEndianness), (void *) XDM_BYTE },
				{ "mpeg4enc1", "maxInterFrameInterval", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.videncParams.maxInterFrameInterval), (void *) 0 },
				{ "mpeg4enc1", "inputChromaFormat", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.videncParams.inputChromaFormat), (void *) XDM_YUV_420SP },
				{ "mpeg4enc1", "inputContentType", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.videncParams.inputContentType), (void *) IVIDEO_PROGRESSIVE },
				{ "mpeg4enc1", "reconChromaFormat", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.videncParams.reconChromaFormat), (void *) XDM_YUV_420P },
				{ "mpeg4enc1", "inputHeight", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.videncDynamicParams.inputHeight), (void *) VIDENC1_MAX_HT },
				{ "mpeg4enc1", "inputWidth", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.videncDynamicParams.inputWidth), (void *) VIDENC1_MAX_WD },
				{ "mpeg4enc1", "refFrameRate", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.videncDynamicParams.refFrameRate), (void *) VIDENC1_MAX_FR },
				{ "mpeg4enc1", "targetFrameRate", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.videncDynamicParams.targetFrameRate), (void *) VIDENC1_MAX_FR },
				{ "mpeg4enc1", "targetBitRate", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.videncDynamicParams.targetBitRate), (void *) VIDENC1_MAX_BR },
				{ "mpeg4enc1", "intraFrameInterval", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.videncDynamicParams.intraFrameInterval), (void *) VIDENC1_INTRA_FI },
				{ "mpeg4enc1", "generateHeader", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.videncDynamicParams.generateHeader), (void *) XDM_DECODE_AU },
				{ "mpeg4enc1", "captureWidth", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.videncDynamicParams.captureWidth), (void *) 0 },
				{ "mpeg4enc1", "forceFrame", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.videncDynamicParams.forceFrame), (void *) 0 },
				{ "mpeg4enc1", "interFrameInterval", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.videncDynamicParams.interFrameInterval), (void *) 0 },
				{ "mpeg4enc1", "mbDataFlag", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.videncDynamicParams.mbDataFlag), (void *) 0 },
				{ "mpeg4enc1", "MPEG4_mode", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.MPEG4_mode), (void *) 1 },
				{ "mpeg4enc1", "levelIdc", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.levelIdc), (void *) IMP4VENC_SP_LEVEL_5 },
				{ "mpeg4enc1", "profileIdc", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.profileIdc), (void *) 0},
				{ "mpeg4enc1", "useVOS", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.useVOS), (void *) 1 },
				{ "mpeg4enc1", "useGOV", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.useGOV), (void *) 0},
				{ "mpeg4enc1", "useVOLatGOV", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.useVOLatGOV), (void *) 0 },
				{ "mpeg4enc1", "useQpel", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.useQpel), (void *) 0 },
				{ "mpeg4enc1", "useInterlace", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.useInterlace), (void *) 0 },
				{ "mpeg4enc1", "aspectRatio", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.aspectRatio), (void *) IMP4VENC_AR_DEFAULT},
				{ "mpeg4enc1", "pixelRange", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.pixelRange), (void *) IMP4VENC_PR_DEFAULT},
				{ "mpeg4enc1", "timerResolution", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.timerResolution), (void *) 30000 },
				{ "mpeg4enc1", "reset_vIMCOP_every_frame", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.reset_vIMCOP_every_frame), (void *) 0 },
				{ "mpeg4enc1", "UMV", DVEVM_ST_INT, &(G->mpeg4enc1.venc1Params.UMV), (void *) 0 },
				{ "mpeg4enc1", "Four_MV_mode", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.Four_MV_mode), (void *) 0 },
				{ "mpeg4enc1", "PacketSize", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.PacketSize), (void *) 0 },
				{ "mpeg4enc1", "qpIntra", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.qpIntra), (void *) 8 },
				{ "mpeg4enc1", "qpInter", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.qpInter), (void *) 8 },
				{ "mpeg4enc1", "useHEC", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.useHEC), (void *) 0 },
				{ "mpeg4enc1", "useGOBSync", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.useGOBSync), (void *) 0 },
				{ "mpeg4enc1", "RcAlgo", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.RcAlgo), (void *) IMP4VENC_RC_DEFAULT },
				{ "mpeg4enc1", "QPMax", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.QPMax), (void *) 31 },
				{ "mpeg4enc1", "QPMin", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.QPMin), (void *) 2 },
				{ "mpeg4enc1", "maxDelay", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.maxDelay), (void *) 1000 },
				{ "mpeg4enc1", "qpInit", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.qpInit), (void *) 0 },
				{ "mpeg4enc1", "MVaccessFlag", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.MVaccessFlag), (void *) 0 },
				{ "mpeg4enc1", "ME_Type", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.ME_Type), (void *) 1 },
				{ "mpeg4enc1", "PerceptualRC", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.PerceptualRC), (void *) 0 },
				{ "mpeg4enc1", "Insert_End_Seq_code", DVEVM_ST_INT, &(G->mpeg4enc1.venc1DynParams.Insert_End_Seq_code), (void *) 0 },
				{ "mpeg4enc1", "framePitch", DVEVM_ST_INT, &(G->mpeg4enc1.inBufDesc.framePitch), (void *) VIDENC1_DMAI_DEFAULT_WD },
				{ "mpeg4enc1", "numFrames", DVEVM_ST_INT, &(G->mpeg4enc1.numFrames), (void *) DEF_CAP_FRAMES },

				/* Parameters for H264iFHD Encoder XDM 1.0*/
				{ "h264fhdenc1", "codec", DVEVM_ST_STR, G->h264fhdenc1.venc1Name, DEFAULT_H264FHDENC1_NAME },
				{ "h264fhdenc1", "encodingPreset", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.videncParams.encodingPreset), (void *) XDM_DEFAULT },
				{ "h264fhdenc1", "rateControlPreset", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.videncParams.rateControlPreset), (void *) 1 },
				{ "h264fhdenc1", "maxHeight", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.videncParams.maxHeight), (void *) H264FHDENC1_MAX_HT },
				{ "h264fhdenc1", "maxWidth", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.videncParams.maxWidth), (void *) H264FHDENC1_MAX_WD },
				{ "h264fhdenc1", "maxFrameRate", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.videncParams.maxFrameRate), (void *) H264FHDENC1_MAX_FR },
				{ "h264fhdenc1", "maxBitRate", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.videncParams.maxBitRate), (void *) H264FHDENC1_MAX_BR },
				{ "h264fhdenc1", "dataEndianness", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.videncParams.dataEndianness), (void *) XDM_LE_32 },
				{ "h264fhdenc1", "maxInterFrameInterval", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.videncParams.maxInterFrameInterval), (void *) 0 },
				{ "h264fhdenc1", "inputChromaFormat", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.videncParams.inputChromaFormat), (void *) XDM_YUV_420SP },
				{ "h264fhdenc1", "inputContentType", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.videncParams.inputContentType), (void *) IVIDEO_PROGRESSIVE },
				{ "h264fhdenc1", "reconChromaFormat", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.videncParams.reconChromaFormat), (void *) XDM_CHROMA_NA },
				{ "h264fhdenc1", "profileIdc", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.profileIdc), (void *) 66 },
				{ "h264fhdenc1", "levelIdc", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.levelIdc), (void *) 40 },
				{ "h264fhdenc1", "EntropyCodingMode", DVEVM_ST_INT, &(G->h264fhdenc1.venc1Params.EntropyCodingMode), (void *) 0 },
				{ "h264fhdenc1", "inputHeight", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.videncDynamicParams.inputHeight), (void *) H264FHDENC1_MAX_HT },
				{ "h264fhdenc1", "inputWidth", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.videncDynamicParams.inputWidth), (void *) H264FHDENC1_MAX_WD },
				{ "h264fhdenc1", "refFrameRate", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.videncDynamicParams.refFrameRate), (void *) H264FHDENC1_MAX_FR },
				{ "h264fhdenc1", "targetFrameRate", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.videncDynamicParams.targetFrameRate), (void *) VIDENC1_MAX_FR },
				{ "h264fhdenc1", "targetBitRate", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.videncDynamicParams.targetBitRate), (void *) H264FHDENC1_MAX_BR },
				{ "h264fhdenc1", "intraFrameInterval", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.videncDynamicParams.intraFrameInterval), (void *) H264FHDENC1_INTRA_FI },
				{ "h264fhdenc1", "generateHeader", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.videncDynamicParams.generateHeader), (void *) XDM_DECODE_AU },
				{ "h264fhdenc1", "captureWidth", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.videncDynamicParams.captureWidth), (void *) 0 },
				{ "h264fhdenc1", "forceFrame", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.videncDynamicParams.forceFrame), (void *) -1 },
				{ "h264fhdenc1", "interFrameInterval", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.videncDynamicParams.interFrameInterval), (void *) 0 },
				{ "h264fhdenc1", "mbDataFlag", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.videncDynamicParams.mbDataFlag), (void *) 0 },
				{ "h264fhdenc1", "sliceCodingPreset", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.sliceCodingParams.sliceCodingPreset), (void *) IH264_SLICECODING_DEFAULT },
				{ "h264fhdenc1", "sliceMode", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.sliceCodingParams.sliceMode), (void *) IH264_SLICEMODE_NONE },
				{ "h264fhdenc1", "sliceUnitSize", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.sliceCodingParams.sliceUnitSize), (void *) 0 },
				{ "h264fhdenc1", "sliceStartOffset[0]", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.sliceCodingParams.sliceStartOffset[0]), (void *) 0 },
				{ "h264fhdenc1", "sliceStartOffset[1]", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.sliceCodingParams.sliceStartOffset[1]), (void *) 0 },
				{ "h264fhdenc1", "sliceStartOffset[2]", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.sliceCodingParams.sliceStartOffset[2]), (void *) 0 },
				{ "h264fhdenc1", "sliceStartOffset[3]", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.sliceCodingParams.sliceStartOffset[3]), (void *) 0 },
				{ "h264fhdenc1", "streamFormat", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.sliceCodingParams.streamFormat), (void *) IH264_STREAM_FORMAT_DEFAULT },
				{ "h264fhdenc1", "OutBufSize", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.OutBufSize), (void *) -1 },
				{ "h264fhdenc1", "QPISlice", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.QPISlice), (void *) 28 },
				{ "h264fhdenc1", "QPSlice", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.QPSlice), (void *) 28 },
				{ "h264fhdenc1", "RateCtrlQpMax", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.RateCtrlQpMax), (void *) 51 },
				{ "h264fhdenc1", "RateCtrlQpMin", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.RateCtrlQpMin), (void *) 0 },
				{ "h264fhdenc1", "NumRowsInSlice", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.NumRowsInSlice), (void *) 0 },
				{ "h264fhdenc1", "LfDisableIdc", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.LfDisableIdc), (void *) 0 },
				{ "h264fhdenc1", "LFAlphaC0Offset", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.LFAlphaC0Offset), (void *) 0 },
				{ "h264fhdenc1", "LFBetaOffset", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.LFBetaOffset), (void *) 0 },
				{ "h264fhdenc1", "ChromaQPOffset", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.ChromaQPOffset), (void *) 0 },
				{ "h264fhdenc1", "SecChromaQPOffset", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.SecChromaQPOffset), (void *) 0 },
				{ "h264fhdenc1", "PicAFFFlag", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.PicAFFFlag), (void *) 0 },
				{ "h264fhdenc1", "PicOrderCountType", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.PicOrderCountType), (void *) 0 },
				{ "h264fhdenc1", "AdaptiveMBs", DVEVM_ST_SHORT, &(G->h264fhdenc1.venc1DynParams.AdaptiveMBs), (void *) 0 },
				{ "h264fhdenc1", "SEIParametersFlag", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.SEIParametersFlag), (void *) 0 },
				{ "h264fhdenc1", "VUIParametersFlag", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.VUIParametersFlag), (void *) 0 },
				{ "h264fhdenc1", "SkipStartCodesInCallback", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.SkipStartCodesInCallback), (void *) 1 },
				{ "h264fhdenc1", "Intra4x4EnableFlag", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.Intra4x4EnableFlag), (void *) 0 },
				{ "h264fhdenc1", "BlockingCallFlag", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.BlockingCallFlag), (void *) 0 },
				{ "h264fhdenc1", "MESelect", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.MESelect), (void *) 1 },
				{ "h264fhdenc1", "ME1080iMode", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.ME1080iMode), (void *) 0 },
				{ "h264fhdenc1", "MVDataFlag", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.MVDataFlag), (void *) 0 },
				{ "h264fhdenc1", "Transform8x8DisableFlag", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.Transform8x8DisableFlag), (void *) 1 },
				{ "h264fhdenc1", "Intra8x8EnableFlag", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.Intra8x8EnableFlag), (void *) 0 },
				{ "h264fhdenc1", "InterlaceReferenceMode", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.InterlaceReferenceMode), (void *) 0 },
				{ "h264fhdenc1", "ChromaConversionMode", DVEVM_ST_CHAR, &(G->h264fhdenc1.venc1DynParams.ChromaConversionMode), (void *) 0 },
				{ "h264fhdenc1", "maxDelay", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.maxDelay), (void *) 1000 },
				{ "h264fhdenc1", "MaxSlicesSupported", DVEVM_ST_INT, &(G->h264fhdenc1.venc1DynParams.MaxSlicesSupported), (void *) 90 },
				{ "h264fhdenc1", "framePitch", DVEVM_ST_INT, &(G->h264fhdenc1.inBufDesc.framePitch), (void *) H264FHDENC1_MAX_WD },
				{ "h264fhdenc1", "numFrames", DVEVM_ST_INT, &(G->h264fhdenc1.numFrames), (void *) DEF_CAP_FRAMES },

				/* Parameters for H264 Encoder XDM 1.0*/
				{ "h264enc1", "codec", DVEVM_ST_STR, G->h264enc1.venc1Name, DEFAULT_VIDENC1_NAME },
				{ "h264enc1", "encodingPreset", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.encodingPreset), (void *) XDM_DEFAULT },
				{ "h264enc1", "rateControlPreset", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.rateControlPreset), (void *) 1 },
				{ "h264enc1", "maxHeight", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.maxHeight), (void *) H264ENC1_MAX_HT },
				{ "h264enc1", "maxWidth", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.maxWidth), (void *) H264ENC1_MAX_WD },
				{ "h264enc1", "maxFrameRate", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.maxFrameRate), (void *) H264ENC1_MAX_FR },
				{ "h264enc1", "maxBitRate", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.maxBitRate), (void *) H264ENC1_MAX_BR },
				{ "h264enc1", "dataEndianness", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.dataEndianness), (void *) XDM_LE_32 },
				{ "h264enc1", "maxInterFrameInterval", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.maxInterFrameInterval), (void *) 0 },
				{ "h264enc1", "inputChromaFormat", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.inputChromaFormat), (void *) XDM_YUV_420SP },
				{ "h264enc1", "inputContentType", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.inputContentType), (void *) IVIDEO_PROGRESSIVE },
				{ "h264enc1", "reconChromaFormat", DVEVM_ST_INT, &(G->h264enc1.venc1Params.videncParams.reconChromaFormat), (void *) XDM_YUV_420P },
				{ "h264enc1", "profileIdc", DVEVM_ST_INT, &(G->h264enc1.venc1Params.profileIdc), (void *) 66 },
				{ "h264enc1", "METype", DVEVM_ST_INT, &(G->h264enc1.venc1Params.METype), (void *) 1 },
				{ "h264enc1", "ScalingMatType", DVEVM_ST_INT, &(G->h264enc1.venc1Params.ScalingMatType), (void *) 0 },
				{ "h264enc1", "ScalingFactor", DVEVM_ST_INT, &(G->h264enc1.venc1Params.ScalingFactor), (void *) 0 },
				{ "h264enc1", "levelIdc", DVEVM_ST_INT, &(G->h264enc1.venc1Params.levelIdc), (void *) 31 },
				{ "h264enc1", "EntropyCodingMode", DVEVM_ST_INT, &(G->h264enc1.venc1Params.EntropyCodingMode), (void *) 0 },
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
				{ "h264enc1", "OutBufSize", DVEVM_ST_INT, &(G->h264enc1.venc1DynParams.OutBufSize), (void *) -1 },
				{ "h264enc1", "QPISlice", DVEVM_ST_CHAR, &(G->h264enc1.venc1DynParams.QPISlice), (void *) 28 },
				{ "h264enc1", "QPSlice", DVEVM_ST_CHAR, &(G->h264enc1.venc1DynParams.QPSlice), (void *) 28 },
				{ "h264enc1", "RateCtrlQpMax", DVEVM_ST_CHAR, &(G->h264enc1.venc1DynParams.RateCtrlQpMax), (void *) 51 },
				{ "h264enc1", "RateCtrlQpMin", DVEVM_ST_CHAR, &(G->h264enc1.venc1DynParams.RateCtrlQpMin), (void *) 0 },
				{ "h264enc1", "NumRowsInSlice", DVEVM_ST_CHAR, &(G->h264enc1.venc1DynParams.NumRowsInSlice), (void *) 3 },
				{ "h264enc1", "LfDisableIdc", DVEVM_ST_CHAR, &(G->h264enc1.venc1DynParams.LfDisableIdc), (void *) 0 },
				{ "h264enc1", "LFAlphaC0Offset", DVEVM_ST_CHAR, &(G->h264enc1.venc1DynParams.LFAlphaC0Offset), (void *) 6 },
				{ "h264enc1", "LFBetaOffset", DVEVM_ST_CHAR, &(G->h264enc1.venc1DynParams.LFBetaOffset), (void *) 6 },
				{ "h264enc1", "ChromaQPOffset", DVEVM_ST_CHAR, &(G->h264enc1.venc1DynParams.ChromaQPOffset), (void *) 0 },
				{ "h264enc1", "SecChromaQPOffset", DVEVM_ST_CHAR, &(G->h264enc1.venc1DynParams.SecChromaQPOffset), (void *) 0 },
				{ "h264enc1", "framePitch", DVEVM_ST_INT, &(G->h264enc1.inBufDesc.framePitch), (void *) H264ENC1_MAX_WD },
				{ "h264enc1", "numFrames", DVEVM_ST_INT, &(G->h264enc1.numFrames), (void *) DEF_CAP_FRAMES },

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

#ifdef _DVTB_NONTSPA_
				/* Parameters for AAC HE Encoder XDM 1.0 Extended Params*/
				{ "aacheenc1", "codec", DVEVM_ST_STR, G->aacheenc1.aacenc1Name, "aacheenc" },
				{ "aacheenc1", "seconds", DVEVM_ST_INT, &(G->aacheenc1.seconds), (void *) DEFAULT_AACHEENC1_TIME },
				{ "aacheenc1", "sampleRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.sampleRate), (void *) 44100 },
				{ "aacheenc1", "bitRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.bitRate), (void *) 64000 },
				{ "aacheenc1", "channelMode", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.channelMode), (void *) (XDAS_Int32)(IAUDIO_2_0) },
				{ "aacheenc1", "dataEndianness", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.dataEndianness), (void *) (XDAS_Int32)(XDM_LE_16) },
				{ "aacheenc1", "encMode", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.encMode), (void *) (XDAS_Int32)(IAUDIO_CBR) },
				{ "aacheenc1", "inputFormat", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.inputFormat), (void *) (XDAS_Int32)(IAUDIO_INTERLEAVED) },
				{ "aacheenc1", "inputBitsPerSample", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.inputBitsPerSample), (void *) 16 },
				{ "aacheenc1", "maxBitRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.maxBitRate), (void *) 192000 },
				{ "aacheenc1", "dualMonoMode", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.dualMonoMode), (void *) (XDAS_Int32) IAUDIO_DUALMONO_LR },
				{ "aacheenc1", "crcFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.crcFlag), (void *) XDAS_FALSE },
				{ "aacheenc1", "ancFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.ancFlag), (void *) XDAS_TRUE },
				{ "aacheenc1", "lfeFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.lfeFlag), (void *) XDAS_FALSE },
				{ "aacheenc1", "outObjectType", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.outObjectType), (void *) AACHEENC1_OTYPE },
				{ "aacheenc1", "outFileFormat", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.outFileFormat), (void *) AACHEENC1_OFF },
				{ "aacheenc1", "useTns", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.useTns), (void *) AACENC_TRUE },
				{ "aacheenc1", "usePns", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.usePns), (void *) AACENC_TRUE },
				{ "aacheenc1", "downMixFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.downMixFlag), (void *) AACENC_FALSE },
				{ "aacheenc1", "bitRateMode", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.bitRateMode), (void *) 1 },
				{ "aacheenc1", "ancRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.ancRate), (void *) -1 },
				{ "aacheenc1", "dynamicparams.sampleRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.sampleRate), (void *) 44100 },
				{ "aacheenc1", "dynamicparams.bitRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.bitRate), (void *) 64000 },
				{ "aacheenc1", "dynamicparams.channelMode", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.channelMode), (void *) IAUDIO_2_0 },
				{ "aacheenc1", "dynamicparams.lfeFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.lfeFlag), (void *) XDAS_FALSE },
				{ "aacheenc1", "dynamicparams.dualMonoMode", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.dualMonoMode), (void *) IAUDIO_DUALMONO_LR },
				{ "aacheenc1", "dynamicparams.inputBitsPerSample", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.inputBitsPerSample), (void *) 16 },
				{ "aacheenc1", "dynamicparams.useTns", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.useTns), (void *) AACENC_TRUE },
				{ "aacheenc1", "dynamicparams.usePns", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.usePns), (void *) AACENC_TRUE },
				{ "aacheenc1", "dynamicparams.downMixFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.downMixFlag), (void *) AACENC_FALSE },
				{ "aacheenc1", "dynamicparams.ancFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.ancFlag), (void *) AACENC_TRUE },
				{ "aacheenc1", "dynamicparams.ancRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.ancRate), (void *) -1 },
 
				/* Parameters for AACHE Decoder 1.0 */
				{ "ac3dec1", "codec", DVEVM_ST_STR, G->ac3dec1.adecName, DEFAULT_AC3DEC1_NAME },
				{ "ac3dec1", "outputPCMWidth", DVEVM_ST_INT, &(G->ac3dec1.adecParams.auddec_params.outputPCMWidth), (void *) AUDDEC1_PCM_WIDTH },
				{ "ac3dec1", "pcmFormat", DVEVM_ST_INT, &(G->ac3dec1.adecParams.auddec_params.pcmFormat), (void *) IAUDIO_INTERLEAVED },
				{ "ac3dec1", "dataEndianness", DVEVM_ST_INT, &(G->ac3dec1.adecParams.auddec_params.dataEndianness), (void *) XDM_BYTE },
				{ "ac3dec1", "desiredChannelMode", DVEVM_ST_INT, &(G->ac3dec1.desiredChannelMode), (void *) IAUDIO_2_0 },
				{ "ac3dec1", "lfeFlag", DVEVM_ST_INT, &(G->ac3dec1.lfeflag), (void *) 0 },
				{ "ac3dec1", "aux", DVEVM_ST_INT, &(G->ac3dec1.aux), (void *) 0 },
				{ "ac3dec1", "sourceDual", DVEVM_ST_INT, &(G->ac3dec1.sourceDual), (void *) 0 },
				{ "ac3dec1", "sourceKaraoke", DVEVM_ST_INT, &(G->ac3dec1.sourceKaraoke), (void *) 3 },
				{ "ac3dec1", "downSampleSbrFlag", DVEVM_ST_INT, &(G->ac3dec1.adecDynParams.auddec_dynamicparams.downSampleSbrFlag), (void *) 0 },
				{ "ac3dec1", "operationMode", DVEVM_ST_INT, &(G->ac3dec1.adecDynParams.operationMode), (void *) 2},
				{ "ac3dec1", "dynrngScaleHiQ6", DVEVM_ST_INT, &(G->ac3dec1.adecDynParams.dynrngScaleHiQ6), (void *) 1},
				{ "ac3dec1", "dynrngScaleLoQ6", DVEVM_ST_INT, &(G->ac3dec1.adecDynParams.dynrngScaleLoQ6), (void *) 1 },
				{ "ac3dec1", "RFModeGainApply", DVEVM_ST_INT, &(G->ac3dec1.adecDynParams.RFModeGainApply), (void *) 0 },
				{ "ac3dec1", "dlgNormApply", DVEVM_ST_INT, &(G->ac3dec1.adecDynParams.dlgNormApply), (void *) 0},
				{ "ac3dec1", "stereomod", DVEVM_ST_INT, &(G->ac3dec1.adecDynParams.stereomod), (void *) 0},
				{ "ac3dec1", "adconvtyp", DVEVM_ST_INT, &(G->ac3dec1.adecDynParams.adconvtyp), (void *) 0},
				{ "ac3dec1", "inbufsize", DVEVM_ST_INT, &(G->ac3dec1.inBuf.bufSizes[0]), (void *) 4096 },
				{ "ac3dec1", "outbufsize", DVEVM_ST_INT, &(G->ac3dec1.outBuf.bufSizes[0]), (void *)  36864},

#endif

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
//				{ "jpegenc1", "COMMENT_startBuf", DVEVM_ST_CHAR, &(G->jpegenc1.ienc1DynParams.COMMENT_startBuf), (void *) 0 },
				{ "jpegenc1", "COMMENT_insert", DVEVM_ST_CHAR, &(G->jpegenc1.ienc1DynParams.COMMENT_insert), (void *) 0 },
				{ "jpegenc1", "Thumbnail_H_size_App1", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1DynParams.Thumbnail_H_size_App1), (void *) 0 },
				{ "jpegenc1", "Thumbnail_V_size_App1", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1DynParams.Thumbnail_V_size_App1), (void *) 0 },
				{ "jpegenc1", "Thumbnail_H_size_App0", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1DynParams.Thumbnail_H_size_App0), (void *) 0 },
				{ "jpegenc1", "Thumbnail_V_size_App0", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1DynParams.Thumbnail_V_size_App0), (void *) 0 },
				{ "jpegenc1", "Thumbnail_H_size_App13", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1DynParams.Thumbnail_H_size_App13), (void *) 0 },
				{ "jpegenc1", "Thumbnail_V_size_App13", DVEVM_ST_SHORT, &(G->jpegenc1.ienc1DynParams.Thumbnail_V_size_App13), (void *) 0 },
};

		DVEVM_CODEC_NUM = sizeof(dvevmStMapArr) / sizeof(DvevmStMapTable);
		MAP = (DvevmStMapTable *) calloc(DVEVM_CODEC_NUM, sizeof(DvevmStMapTable));
		if (MAP != NULL)
		{
			memcpy(MAP, dvevmStMapArr, DVEVM_CODEC_NUM * sizeof(DvevmStMapTable));
			valInitialized = DVEVM_ST_TRUE;
		}
	}
}
