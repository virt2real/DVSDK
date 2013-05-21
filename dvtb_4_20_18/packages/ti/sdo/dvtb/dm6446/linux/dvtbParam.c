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
 * achieve this in a round about way */

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

			/* Parameters for ALSA audio device */
			{ "audio", "device", DVEVM_ST_STR, G->aud.device, DEF_SND_DEVICE },
			{ "audio", "format", DVEVM_ST_INT, &(G->aud.format), (void *) SND_PCM_FORMAT_S16_LE },
			{ "audio", "samplerate", DVEVM_ST_INT, &(G->aud.sampleRate), (void *) DEF_SAMPLE_RATE },
			{ "audio", "channels", DVEVM_ST_INT, &(G->aud.numChannels), (void *) DEF_NUM_CHANNELS },
			{ "audio", "type", DVEVM_ST_INT, &(G->aud.blocking_mode), 0 },

			/*V4L2 VPBE*/
			{ "vpbe", "device", DVEVM_ST_STR, G->vpbe.device, VID_DEVICE },
			{ "vpbe", "width", DVEVM_ST_INT, &(G->vpbe.imageWidth), (void *) D1_NTSC_WIDTH },
			{ "vpbe", "height", DVEVM_ST_INT, &(G->vpbe.imageHeight), (void *) D1_NTSC_HEIGHT },
			{ "vpbe", "std", DVEVM_ST_INT, &(G->vpbe.dispStd), (void *) DVEVM_ST_NTSC },
			{ "vpbe", "output", DVEVM_ST_INT, &(G->vpbe.dispOutput), (void *) DVEVM_ST_COMPOSITE },
			{ "vpbe", "bpp", DVEVM_ST_INT, &(G->vpbe.bpp), (void *) DEF_BPP },

			/* Parameters for VPFE device */
			{ "vpfe", "device", DVEVM_ST_STR, G->vpfe.device, VIDCAP_DEVICE },
			{ "vpfe", "standard", DVEVM_ST_INT, &(G->vpfe.capStd), (void *) VID_STD_AUTO },
			{ "vpfe", "format", DVEVM_ST_INT, &(G->vpfe.capFmt), (void *) VID_FMT_UYVY },
			{ "vpfe", "input", DVEVM_ST_INT, &(G->vpfe.input), (void *) 0 },
			{ "vpfe", "width", DVEVM_ST_INT, &(G->vpfe.capWidth), (void *) NTSC_WIDTH },
			{ "vpfe", "height", DVEVM_ST_INT, &(G->vpfe.capHeight), (void *) NTSC_HEIGHT },

			/* Parameters for Video Encoder */
			{ "videnc", "codec", DVEVM_ST_STR, G->venc.vencName, DEFAULT_VIDENC_NAME },
			{ "videnc", "encodingPreset", DVEVM_ST_INT, &(G->venc.vencParams.encodingPreset), (void *) XDM_DEFAULT },
			{ "videnc", "rateControlPreset", DVEVM_ST_INT, &(G->venc.vencParams.rateControlPreset), (void *) 1 },
			{ "videnc", "maxHeight", DVEVM_ST_INT, &(G->venc.vencParams.maxHeight), (void *) VIDENC_MAX_HT },
			{ "videnc", "maxWidth", DVEVM_ST_INT, &(G->venc.vencParams.maxWidth), (void *) VIDENC_MAX_WD },
			{ "videnc", "maxFrameRate", DVEVM_ST_INT, &(G->venc.vencParams.maxFrameRate), (void *) VIDENC_MAX_FR },
			{ "videnc", "maxBitRate", DVEVM_ST_INT, &(G->venc.vencParams.maxBitRate), (void *) VIDENC_MAX_BR },
			{ "videnc", "dataEndianness", DVEVM_ST_INT, &(G->venc.vencParams.dataEndianness), (void *) XDM_BYTE },
			{ "videnc", "maxInterFrameInterval", DVEVM_ST_INT, &(G->venc.vencParams.maxInterFrameInterval), (void *) 0 },
			{ "videnc", "inputChromaFormat", DVEVM_ST_INT, &(G->venc.vencParams.inputChromaFormat), (void *) XDM_YUV_422ILE },
			{ "videnc", "inputContentType", DVEVM_ST_INT, &(G->venc.vencParams.inputContentType), (void *) IVIDEO_PROGRESSIVE },
			{ "videnc", "inputHeight", DVEVM_ST_INT, &(G->venc.vencDynParams.inputHeight), (void *) VIDENC_MAX_HT },
			{ "videnc", "inputWidth", DVEVM_ST_INT, &(G->venc.vencDynParams.inputWidth), (void *) VIDENC_MAX_WD },
			{ "videnc", "refFrameRate", DVEVM_ST_INT, &(G->venc.vencDynParams.refFrameRate), (void *) VIDENC_MAX_FR },
			{ "videnc", "targetFrameRate", DVEVM_ST_INT, &(G->venc.vencDynParams.targetFrameRate), (void *) VIDENC_MAX_FR },
			{ "videnc", "targetBitRate", DVEVM_ST_INT, &(G->venc.vencDynParams.targetBitRate), (void *) VIDENC_MAX_BR },
			{ "videnc", "intraFrameInterval", DVEVM_ST_INT, &(G->venc.vencDynParams.intraFrameInterval), (void *) VIDENC_INTRA_FI },
			{ "videnc", "generateHeader", DVEVM_ST_INT, &(G->venc.vencDynParams.generateHeader), (void *) XDM_DECODE_AU },
			{ "videnc", "captureWidth", DVEVM_ST_INT, &(G->venc.vencDynParams.captureWidth), (void *) 0 },
			{ "videnc", "forceIFrame", DVEVM_ST_INT, &(G->venc.vencDynParams.forceIFrame), (void *) 0 },
			{ "videnc", "numFrames", DVEVM_ST_INT, &(G->venc.numFrames), (void *) DEF_CAP_FRAMES },

			/* Parameters for Video Decoder */
			{ "viddec", "codec", DVEVM_ST_STR, G->vdec.vdecName, DEFAULT_VIDDEC_NAME },
			{ "viddec", "maxHeight", DVEVM_ST_INT, &(G->vdec.vdecParams.maxHeight), (void *) VIDDEC_MAX_HT },
			{ "viddec", "maxWidth", DVEVM_ST_INT, &(G->vdec.vdecParams.maxWidth), (void *) VIDDEC_MAX_WD },
			{ "viddec", "maxFrameRate", DVEVM_ST_INT, &(G->vdec.vdecParams.maxFrameRate), (void *) VIDDEC_MAX_FR },
			{ "viddec", "maxBitRate", DVEVM_ST_INT, &(G->vdec.vdecParams.maxBitRate), (void *) VIDDEC_MAX_BR },
			{ "viddec", "dataEndianness", DVEVM_ST_INT, &(G->vdec.vdecParams.dataEndianness), (void *) XDM_BYTE },
			{ "viddec", "forceChromaFormat", DVEVM_ST_INT, &(G->vdec.vdecParams.forceChromaFormat), (void *) XDM_YUV_422ILE },
			{ "viddec", "decodeHeader", DVEVM_ST_INT, &(G->vdec.vdecDynParams.decodeHeader), (void *) XDM_DECODE_AU },
			{ "viddec", "displayWidth", DVEVM_ST_INT, &(G->vdec.vdecDynParams.displayWidth), (void *) XDM_DEFAULT },
			{ "viddec", "frameSkipMode", DVEVM_ST_INT, &(G->vdec.vdecDynParams.frameSkipMode), (void *) IVIDEO_NO_SKIP },
			{ "viddec", "numFrames", DVEVM_ST_INT, &(G->vdec.numFrames), (void *) 10 },

			/* Parameters for Audio Decoder */
			{ "auddec", "codec", DVEVM_ST_STR, G->adec.adecName, DEFAULT_AUDDEC_NAME },
			{ "auddec", "maxSampleRate", DVEVM_ST_INT, &(G->adec.adecParams.maxSampleRate), (void *) AUDDEC_MAX_SR },
			{ "auddec", "maxBitrate", DVEVM_ST_INT, &(G->adec.adecParams.maxBitrate), (void *) AUDDEC_MAX_BR },
			{ "auddec", "maxNoOfCh", DVEVM_ST_INT, &(G->adec.adecParams.maxNoOfCh), (void *) IAUDIO_STEREO },
			{ "auddec", "dataEndianness", DVEVM_ST_INT, &(G->adec.adecParams.dataEndianness), (void *) XDM_BYTE },
			{ "auddec", "outputFormat", DVEVM_ST_INT, &(G->adec.adecDynParams.outputFormat), (void *) IAUDIO_INTERLEAVED },
			{ "auddec", "inbufsize", DVEVM_ST_INT, &(G->adec.inBuf.size), (void *) AUDDEC_INBUF_SIZE },
			{ "auddec", "outbufsize", DVEVM_ST_INT, &(G->adec.outBuf.size), (void *) AUDDEC_OUTBUF_SIZE },

			/* Parameters for MP3 Base Audio Decoder */
			{ "mp3basedec", "codec", DVEVM_ST_STR, G->mp3basedec.adecName, "mp3dec" },
			{ "mp3basedec", "maxSampleRate", DVEVM_ST_INT, &(G->mp3basedec.adecParams.maxSampleRate), (void *) MP3BASEDEC_MAX_SR },
			{ "mp3basedec", "maxBitrate", DVEVM_ST_INT, &(G->mp3basedec.adecParams.maxBitrate), (void *) MP3BASEDEC_MAX_BR },
			{ "mp3basedec", "maxNoOfCh", DVEVM_ST_INT, &(G->mp3basedec.adecParams.maxNoOfCh), (void *) IAUDIO_STEREO },
			{ "mp3basedec", "dataEndianness", DVEVM_ST_INT, &(G->mp3basedec.adecParams.dataEndianness), (void *) XDM_BYTE },
			{ "mp3basedec", "outputFormat", DVEVM_ST_INT, &(G->mp3basedec.adecDynParams.outputFormat), (void *) IAUDIO_INTERLEAVED },
			{ "mp3basedec", "inbufsize", DVEVM_ST_INT, &(G->mp3basedec.inBuf.size), (void *) MP3BASEDEC_INBUF_SIZE },
			{ "mp3basedec", "outbufsize", DVEVM_ST_INT, &(G->mp3basedec.outBuf.size), (void *) MP3BASEDEC_OUTBUF_SIZE },

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
			{ "sphdec", "compandingLaw", DVEVM_ST_INT, &(G->sdec.sdecParams.compandingLaw), (void *) SPHDEC_CL },
			{ "sphdec", "packingType", DVEVM_ST_INT, &(G->sdec.sdecParams.packingType), (void *) SPHDEC_PT },
			{ "sphdec", "inbufsize", DVEVM_ST_INT, &(G->sdec.inBuf.size), (void *) SPHDEC_INBUF_SIZE },
			{ "sphdec", "outbufsize", DVEVM_ST_INT, &(G->sdec.outBuf.size), (void *) SPHDEC_OUTBUF_SIZE },

			/* Parameters for Audio Encoder */
			{ "audenc", "codec", DVEVM_ST_STR, G->aenc.aencName, DEFAULT_AUDENC_NAME },
			{ "audenc", "seconds", DVEVM_ST_INT, &(G->aenc.seconds), (void *) DEFAULT_AUDENC_TIME },
			{ "audenc", "encodingPreset", DVEVM_ST_INT, &(G->aenc.aencParams.encodingPreset), (void *) XDM_DEFAULT },
			{ "audenc", "maxSampleRate", DVEVM_ST_INT, &(G->aenc.aencParams.maxSampleRate), (void *) AUDENC_MAX_SR },
			{ "audenc", "maxBitrate", DVEVM_ST_INT, &(G->aenc.aencParams.maxBitrate), (void *) AUDENC_MAX_BR },
			{ "audenc", "maxNoOfCh", DVEVM_ST_INT, &(G->aenc.aencParams.maxNoOfCh), (void *) IAUDIO_MONO },
			{ "audenc", "dataEndianness", DVEVM_ST_INT, &(G->aenc.aencParams.dataEndianness), (void *) XDM_LE_16 },
			{ "audenc", "inputFormat", DVEVM_ST_INT, &(G->aenc.aencDynParams.inputFormat), (void *) IAUDIO_BLOCK },
			{ "audenc", "bitRate", DVEVM_ST_INT, &(G->aenc.aencDynParams.bitRate), (void *) AUDENC_MAX_BR },
			{ "audenc", "sampleRate", DVEVM_ST_INT, &(G->aenc.aencDynParams.sampleRate), (void *) AUDENC_MAX_SR },
			{ "audenc", "numChannels", DVEVM_ST_INT, &(G->aenc.aencDynParams.numChannels), (void *) IAUDIO_MONO },
			{ "audenc", "numLFEChannels", DVEVM_ST_INT, &(G->aenc.aencDynParams.numLFEChannels), (void *) 0 },
			{ "audenc", "inputBitsPerSample", DVEVM_ST_INT, &(G->aenc.aencDynParams.inputBitsPerSample), (void *) 16 },

			/* Parameters for Image Decoder */
			{ "imgdec", "codec", DVEVM_ST_STR, G->idec.idecName, DEFAULT_IMGDEC_NAME },
			{ "imgdec", "maxHeight", DVEVM_ST_INT, &(G->idec.idecParams.maxHeight), (void *) IMGDEC_MAX_HT },
			{ "imgdec", "maxWidth", DVEVM_ST_INT, &(G->idec.idecParams.maxWidth), (void *) IMGDEC_MAX_WD },
			{ "imgdec", "maxScans", DVEVM_ST_INT, &(G->idec.idecParams.maxScans), (void *) IMGDEC_MAX_SCANS },
			{ "imgdec", "dataEndianness", DVEVM_ST_INT, &(G->idec.idecParams.dataEndianness), (void *) XDM_BYTE },
			{ "imgdec", "forceChromaFormat", DVEVM_ST_INT, &(G->idec.idecParams.forceChromaFormat), (void *) XDM_YUV_422ILE },
			//{"imgdec", "numAU", DVEVM_ST_INT, &(G->idec.idecDynParams.numAU), (void *) XDM_DEFAULT },
			//{"imgdec", "decodeHeader", DVEVM_ST_INT, &(G->idec.idecDynParams.decodeHeader), (void *) XDM_DECODE_AU },
			{ "imgdec", "displayWidth", DVEVM_ST_INT, &(G->idec.idecDynParams.displayWidth), (void *) XDM_DEFAULT },
			//{"imgdec", "numBytes", DVEVM_ST_INT, &(G->idec.idecInArgs.numBytes), (void *) 0 },

			/* Parameters for Image Encoder */
			{ "imgenc", "codec", DVEVM_ST_STR, G->ienc.iencName, DEFAULT_IMGENC_NAME },
			{ "imgenc", "maxHeight", DVEVM_ST_INT, &(G->ienc.iencParams.maxHeight), (void *) IMGENC_MAX_HT },
			{ "imgenc", "maxWidth", DVEVM_ST_INT, &(G->ienc.iencParams.maxWidth), (void *) IMGENC_MAX_WD },
			{ "imgenc", "maxScans", DVEVM_ST_INT, &(G->ienc.iencParams.maxScans), (void *) IMGENC_MAX_SCANS },
			{ "imgenc", "dataEndianness", DVEVM_ST_INT, &(G->ienc.iencParams.dataEndianness), (void *) XDM_LE_32 },
			{ "imgenc", "forceChromaFormat", DVEVM_ST_INT, &(G->ienc.iencParams.forceChromaFormat), (void *) XDM_YUV_422P },
			{ "imgenc", "numAU", DVEVM_ST_INT, &(G->ienc.iencDynParams.numAU), (void *) XDM_DEFAULT },
			{ "imgenc", "inputChromaFormat", DVEVM_ST_INT, &(G->ienc.iencDynParams.inputChromaFormat), (void *) XDM_YUV_422ILE },
			{ "imgenc", "inputHeight", DVEVM_ST_INT, &(G->ienc.iencDynParams.inputHeight), (void *) IMGENC_MAX_HT },
			{ "imgenc", "inputWidth", DVEVM_ST_INT, &(G->ienc.iencDynParams.inputWidth), (void *) IMGENC_MAX_WD },
			{ "imgenc", "captureWidth", DVEVM_ST_INT, &(G->ienc.iencDynParams.captureWidth), (void *) IMGENC_MAX_WD },
			{ "imgenc", "generateHeader", DVEVM_ST_INT, &(G->ienc.iencDynParams.generateHeader), (void *) XDM_ENCODE_AU },
			{ "imgenc", "qValue", DVEVM_ST_INT, &(G->ienc.iencDynParams.qValue), (void *) 73 },

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
			{ "videnc1", "captureWidth", DVEVM_ST_INT, &(G->venc1.venc1DynParams.captureWidth), (void *) VIDENC1_MAX_WD },
			{ "videnc1", "forceFrame", DVEVM_ST_INT, &(G->venc1.venc1DynParams.forceFrame), (void *) 0 },
			{ "videnc1", "interFrameInterval", DVEVM_ST_INT, &(G->venc1.venc1DynParams.interFrameInterval), (void *) 0 },
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

			/* Parameters for MPEG2 Decoder XDM 1.0*/
			{ "viddec2", "codec", DVEVM_ST_STR, G->vdec2.vdec2Name, DEFAULT_VIDDEC1_NAME },
			{ "viddec2", "maxHeight", DVEVM_ST_INT, &(G->vdec2.vdec2Params.maxHeight), (void *) VIDDEC2_MAX_HT },
			{ "viddec2", "maxWidth", DVEVM_ST_INT, &(G->vdec2.vdec2Params.maxWidth), (void *) VIDDEC2_MAX_WD },
			{ "viddec2", "maxFrameRate", DVEVM_ST_INT, &(G->vdec2.vdec2Params.maxFrameRate), (void *) VIDDEC2_MAX_FR },
			{ "viddec2", "maxBitRate", DVEVM_ST_INT, &(G->vdec2.vdec2Params.maxBitRate), (void *) VIDDEC2_MAX_BR },
			{ "viddec2", "dataEndianness", DVEVM_ST_INT, &(G->vdec2.vdec2Params.dataEndianness), (void *) XDM_BYTE },
			{ "viddec2", "forceChromaFormat", DVEVM_ST_INT, &(G->vdec2.vdec2Params.forceChromaFormat), (void *) XDM_YUV_420P },
			{ "viddec2", "decodeHeader", DVEVM_ST_INT, &(G->vdec2.vdec2DynParams.decodeHeader), (void *) XDM_DECODE_AU },
			{ "viddec2", "displayWidth", DVEVM_ST_INT, &(G->vdec2.vdec2DynParams.displayWidth), (void *) XDM_DEFAULT },
			{ "viddec2", "frameSkipMode", DVEVM_ST_INT, &(G->vdec2.vdec2DynParams.frameSkipMode), (void *) IVIDEO_NO_SKIP },
			{ "viddec2", "frameOrder", DVEVM_ST_INT, &(G->vdec2.vdec2DynParams.frameOrder), (void *) 0 },
			{ "viddec2", "newFrameFlag", DVEVM_ST_INT, &(G->vdec2.vdec2DynParams.newFrameFlag), (void *) 0 },
			{ "viddec2", "mbDataFlag", DVEVM_ST_INT, &(G->vdec2.vdec2DynParams.mbDataFlag), (void *) 0 },
			{ "viddec2", "numFrames", DVEVM_ST_INT, &(G->vdec2.numFrames), (void *) 100 },

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

			{ "auddec1", "codec", DVEVM_ST_STR, G->adec1.adecName, "aachedec" },
			{ "auddec1", "outputPCMWidth", DVEVM_ST_INT, &(G->adec1.adecParams.outputPCMWidth), (void *) AUDDEC1_PCM_WIDTH },
			{ "auddec1", "pcmFormat", DVEVM_ST_INT, &(G->adec1.adecParams.pcmFormat), (void *) IAUDIO_INTERLEAVED },
			{ "auddec1", "dataEndianness", DVEVM_ST_INT, &(G->adec1.adecParams.dataEndianness), (void *) XDM_BYTE },
			{ "auddec1", "desiredChannelMode", DVEVM_ST_INT, &(G->adec1.desiredChannelMode), (void *) IAUDIO_2_0 },
			{ "auddec1", "downSampleSbrFlag", DVEVM_ST_INT, &(G->adec1.adecDynParams.downSampleSbrFlag), (void *) 0 },
			{ "auddec1", "inbufsize", DVEVM_ST_INT, &(G->adec1.inBuf.bufSizes[0]), (void *) 2048 },
			{ "auddec1", "outbufsize", DVEVM_ST_INT, &(G->adec1.outBuf.bufSizes[0]), (void *) 8192 },

			//XDM 1.0 MP3 Decoder Base Params
			{ "mp3basedec1", "codec", DVEVM_ST_STR, G->mp3basedec1.adecName, "mp3dec" },
			{ "mp3basedec1", "outputPCMWidth", DVEVM_ST_INT, &(G->mp3basedec1.adecParams.outputPCMWidth), (void *) MP3BASEDEC1_PCM_WIDTH },
			{ "mp3basedec1", "pcmFormat", DVEVM_ST_INT, &(G->mp3basedec1.adecParams.pcmFormat), (void *) IAUDIO_INTERLEAVED },
			{ "mp3basedec1", "dataEndianness", DVEVM_ST_INT, &(G->mp3basedec1.adecParams.dataEndianness), (void *) XDM_BYTE },
			{ "mp3basedec1", "downSampleSbrFlag", DVEVM_ST_INT, &(G->mp3basedec1.adecDynParams.downSampleSbrFlag), (void *) 0 },
			{ "mp3basedec1", "inbufsize", DVEVM_ST_INT, &(G->mp3basedec1.inBuf.size), (void *) 2880 },
			{ "mp3basedec1", "outbufsize", DVEVM_ST_INT, &(G->mp3basedec1.outBuf.size), (void *) 4608 },

			/* Parameters for xdm 1.0 Image Encoder */
			{ "imgenc1", "codec", DVEVM_ST_STR, G->ienc1.ienc1Name, DEFAULT_IMGENC1_NAME },
			{ "imgenc1", "maxHeight", DVEVM_ST_INT, &(G->ienc1.ienc1Params.maxHeight), (void *) IMGENC1_MAX_HT },
			{ "imgenc1", "maxWidth", DVEVM_ST_INT, &(G->ienc1.ienc1Params.maxWidth), (void *) IMGENC1_MAX_WD },
			{ "imgenc1", "maxScans", DVEVM_ST_INT, &(G->ienc1.ienc1Params.maxScans), (void *) IMGENC1_MAX_SCANS },
			{ "imgenc1", "dataEndianness", DVEVM_ST_INT, &(G->ienc1.ienc1Params.dataEndianness), (void *) XDM_BYTE },
			{ "imgenc1", "forceChromaFormat", DVEVM_ST_INT, &(G->ienc1.ienc1Params.forceChromaFormat), (void *) XDM_YUV_422P },
			{ "imgenc1", "numAU", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.numAU), (void *) XDM_DEFAULT },
			{ "imgenc1", "inputChromaFormat", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.inputChromaFormat), (void *) XDM_YUV_422ILE },
			{ "imgenc1", "inputHeight", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.inputHeight), (void *) IMGENC1_MAX_HT },
			{ "imgenc1", "inputWidth", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.inputWidth), (void *) IMGENC1_MAX_WD },
			{ "imgenc1", "captureWidth", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.captureWidth), (void *) IMGENC1_MAX_WD },
			{ "imgenc1", "generateHeader", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.generateHeader), (void *) XDM_ENCODE_AU },
			{ "imgenc1", "qValue", DVEVM_ST_INT, &(G->ienc1.ienc1DynParams.qValue), (void *) 73 },

			/* Parameters for xdm 1.0 Image Decoder */
			{ "imgdec1", "codec", DVEVM_ST_STR, G->idec1.idec1Name, DEFAULT_IMGDEC1_NAME },
			{ "imgdec1", "maxHeight", DVEVM_ST_INT, &(G->idec1.idec1Params.maxHeight), (void *) IMGDEC1_MAX_HT },
			{ "imgdec1", "maxWidth", DVEVM_ST_INT, &(G->idec1.idec1Params.maxWidth), (void *) IMGDEC1_MAX_WD },
			{ "imgdec1", "maxScans", DVEVM_ST_INT, &(G->idec1.idec1Params.maxScans), (void *) IMGDEC1_MAX_SCANS },
			{ "imgdec1", "dataEndianness", DVEVM_ST_INT, &(G->idec1.idec1Params.dataEndianness), (void *) XDM_BYTE },
			{ "imgdec1", "forceChromaFormat", DVEVM_ST_INT, &(G->idec1.idec1Params.forceChromaFormat), (void *) XDM_YUV_422ILE },
			{ "imgdec1", "numAU", DVEVM_ST_INT, &(G->idec1.idec1DynParams.numAU), (void *) XDM_DEFAULT },
			{ "imgdec1", "decodeHeader", DVEVM_ST_INT, &(G->idec1.idec1DynParams.decodeHeader), (void *) XDM_DECODE_AU },
			{ "imgdec1", "displayWidth", DVEVM_ST_INT, &(G->idec1.idec1DynParams.displayWidth), (void *) XDM_DEFAULT },

			/* Parameters for AAC HE Encoder XDM 1.0 Extended Params*/
			{ "aacheenc1", "codec", DVEVM_ST_STR, G->aacheenc1.aacenc1Name, "aacheenc" },
			{ "aacheenc1", "seconds", DVEVM_ST_INT, &(G->aacheenc1.seconds), (void *) DEFAULT_AACHEENC1_TIME },
			{ "aacheenc1", "sampleRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.sampleRate), (void *) 44100 },
			{ "aacheenc1", "bitRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.bitRate), (void *) 64000 },
			{ "aacheenc1", "channelMode", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.channelMode), (void *) 1 },
			{ "aacheenc1", "dataEndianness", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.dataEndianness), (void *) (XDAS_Int32)(XDM_LE_16) },
			{ "aacheenc1", "encMode", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.encMode), (void *) 0 },
			{ "aacheenc1", "inputFormat", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.inputFormat), (void *) 1 },
			{ "aacheenc1", "inputBitsPerSample", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.inputBitsPerSample), (void *) 16 },
			{ "aacheenc1", "maxBitRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.maxBitRate), (void *) 192000 },
			{ "aacheenc1", "dualMonoMode", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.dualMonoMode), (void *) 0 },
			{ "aacheenc1", "crcFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.crcFlag), (void *) 0 },
			{ "aacheenc1", "ancFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.ancFlag), (void *) 1 },
			{ "aacheenc1", "lfeFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.audenc_params.lfeFlag), (void *) 0 },
			{ "aacheenc1", "outObjectType", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.outObjectType), (void *) AACHEENC1_OTYPE },
			{ "aacheenc1", "outFileFormat", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.outFileFormat), (void *) AACHEENC1_OFF },
			{ "aacheenc1", "useTns", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.useTns), (void *) 1 },
			{ "aacheenc1", "usePns", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.usePns), (void *) 1 },
			{ "aacheenc1", "downMixFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.downMixFlag), (void *) AACHEENC1_DMIX },
			{ "aacheenc1", "bitRateMode", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.bitRateMode), (void *) AACHEENC1_BRM },
			{ "aacheenc1", "ancRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1Params.ancRate), (void *) AACHEENC1_ARATE },
			{ "aacheenc1", "dynamicparams.sampleRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.sampleRate), (void *) 44100 },
			{ "aacheenc1", "dynamicparams.bitRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.bitRate), (void *) 64000 },
			{ "aacheenc1", "dynamicparams.channelMode", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.channelMode), (void *) 1 },
			{ "aacheenc1", "dynamicparams.lfeFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.lfeFlag), (void *) 0 },
			{ "aacheenc1", "dynamicparams.dualMonoMode", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.dualMonoMode), (void *) 0 },
			{ "aacheenc1", "dynamicparams.inputBitsPerSample", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.audenc_dynamicparams.inputBitsPerSample), (void *) 16 },
			{ "aacheenc1", "dynamicparams.useTns", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.useTns), (void *) 1 },
			{ "aacheenc1", "dynamicparams.usePns", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.usePns), (void *) 1 },
			{ "aacheenc1", "dynamicparams.downMixFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.downMixFlag), (void *) AACHEENC1_DMIX },
			{ "aacheenc1", "dynamicparams.ancFlag", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.ancFlag), (void *) AACHEENC1_ANC },
			{ "aacheenc1", "dynamicparams.ancRate", DVEVM_ST_INT, &(G->aacheenc1.aacenc1DynParams.ancRate), (void *) AACHEENC1_ARATE },

			//Paramater initialisation for AACLCENCODER extended class
			{ "aaclcenc1", "codec", DVEVM_ST_STR, G->aaclcenc1.aacenc1Name, "aaclcenc" },
			{ "aaclcenc1", "sampleRate", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.audenc_params.sampleRate), (void *) AACLCENC1_SR },
			{ "aaclcenc1", "bitRate", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.audenc_params.bitRate), (void *) AACLCENC1_BR },
			{ "aaclcenc1", "channelMode", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.audenc_params.channelMode), (void *) IAUDIO_MONO },
			{ "aaclcenc1", "dataEndianness", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.audenc_params.dataEndianness), (void *) (XDAS_Int32)(XDM_LE_16) },
			{ "aaclcenc1", "encMode", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.audenc_params.encMode), (void *) AACLCENC1_MODE },
			{ "aaclcenc1", "inputFormat", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.audenc_params.inputFormat), (void *) IAUDIO_INTERLEAVED },
			{ "aaclcenc1", "inputBitsPerSample", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.audenc_params.inputBitsPerSample), (void *) AACLCENC1_BPS },
			{ "aaclcenc1", "maxBitRate", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.audenc_params.maxBitRate), (void *) AACLCENC1_MAX_BR },
			{ "aaclcenc1", "dualMonoMode", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.audenc_params.dualMonoMode), (void *) AACLCENC1_DMONO },
			{ "aaclcenc1", "crcFlag", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.audenc_params.crcFlag), (void *) AACLCENC1_CRC },
			{ "aaclcenc1", "ancFlag", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.audenc_params.ancFlag), (void *) AACLCENC1_ANC },
			{ "aaclcenc1", "lfeFlag", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.audenc_params.lfeFlag), (void *) AACLCENC1_LFE },
			{ "aaclcenc1", "outObjectType", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.outObjectType), (void *) AACLCENC1_OTYPE },
			{ "aaclcenc1", "outFileFormat", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.outFileFormat), (void *) AACLCENC1_OFF },
			{ "aaclcenc1", "useTns", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.useTns), (void *) 1 },
			{ "aaclcenc1", "usePns", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.usePns), (void *) 1 },
			{ "aaclcenc1", "downMixFlag", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.downMixFlag), (void *) AACLCENC1_DMIX },
			{ "aaclcenc1", "bitRateMode", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.bitRateMode), (void *) AACLCENC1_BRM },
			{ "aaclcenc1", "ancRate", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1Params.ancRate), (void *) AACLCENC1_ARATE },
			{ "aaclcenc1", "dynamicparams.sampleRate", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1DynParams.audenc_dynamicparams.sampleRate), (void *) AACLCENC1_SR },
			{ "aaclcenc1", "dynamicparams.bitRate", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1DynParams.audenc_dynamicparams.bitRate), (void *) AACLCENC1_BR },
			{ "aaclcenc1", "dynamicparams.channelMode", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1DynParams.audenc_dynamicparams.channelMode), (void *) IAUDIO_STEREO },
			{ "aaclcenc1", "dynamicparams.lfeFlag", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1DynParams.audenc_dynamicparams.lfeFlag), (void *) AACLCENC1_LFE },
			{ "aaclcenc1", "dynamicparams.dualMonoMode", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1DynParams.audenc_dynamicparams.dualMonoMode), (void *) AACLCENC1_DMONO },
			{ "aaclcenc1", "dynamicparams.inputBitsPerSample", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1DynParams.audenc_dynamicparams.inputBitsPerSample), (void *) AACLCENC1_BPS },
			{ "aaclcenc1", "dynamicparams.useTns", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1DynParams.useTns), (void *) 1 },
			{ "aaclcenc1", "dynamicparams.usePns", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1DynParams.usePns), (void *) 1 },
			{ "aaclcenc1", "dynamicparams.downMixFlag", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1DynParams.downMixFlag), (void *) AACLCENC1_DMIX },
			{ "aaclcenc1", "dynamicparams.outObjectType", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1DynParams.outObjectType), (void *) AACLCENC1_OTYPE },
			{ "aaclcenc1", "dynamicparams.outFileFormat", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1DynParams.outFileFormat), (void *) AACLCENC1_OFF },
			{ "aaclcenc1", "dynamicparams.ancFlag", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1DynParams.ancFlag), (void *) AACLCENC1_ANC },
			{ "aaclcenc1", "dynamicparams.ancRate", DVEVM_ST_INT, &(G->aaclcenc1.aacenc1DynParams.ancRate), (void *) AACLCENC1_ARATE },
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
