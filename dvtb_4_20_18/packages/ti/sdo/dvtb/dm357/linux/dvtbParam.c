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
#include "dvtbDefs.h"

DvevmStMapTable *MAP = NULL;
unsigned int DVEVM_CODEC_NUM=0;

static DvevmStBool valInitialized=DVEVM_ST_FALSE;

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
      {"engine", "name", DVEVM_ST_STR, G->eng.name, DEFAULT_ENGINE_NAME},

      /* Parameters for audio device */
      {"audio", "device", DVEVM_ST_STR, G->aud.device, DEF_SND_DEVICE},
      {"audio", "samplesize", DVEVM_ST_INT, &(G->aud.sampleSize), (void *) DEF_SAMPLE_SIZE},
      {"audio", "samplerate", DVEVM_ST_INT, &(G->aud.sampleRate), (void *) DEF_SAMPLE_RATE},
      {"audio", "channels", DVEVM_ST_INT, &(G->aud.numChannels), (void *) DEF_NUM_CHANNELS},
      {"audio", "source", DVEVM_ST_INT, &(G->aud.src), (void *) MIC},

      /* Parameters for VPBE device */
      {"vpbe", "device", DVEVM_ST_STR, G->vpbe.device, VID0_DEVICE},
      {"vpbe", "imageWidth", DVEVM_ST_INT, &(G->vpbe.imageWidth), (void *) DEF_IMAGEWIDTH},
      {"vpbe", "imageHeight", DVEVM_ST_INT, &(G->vpbe.imageHeight), (void *) DEF_IMAGEHEIGHT},
      {"vpbe", "screenWidth", DVEVM_ST_INT, &(G->vpbe.screenWidth), (void *) D1_NTSC_WIDTH},
      {"vpbe", "screenHeight", DVEVM_ST_INT, &(G->vpbe.screenHeight), (void *) D1_NTSC_HEIGHT},
      {"vpbe", "bpp", DVEVM_ST_INT, &(G->vpbe.bpp), (void *) DEF_BPP},

      /* Parameters for VPFE device */
      {"vpfe", "device", DVEVM_ST_STR, G->vpfe.device, VIDCAP_DEVICE},
      {"vpfe", "standard", DVEVM_ST_INT, &(G->vpfe.capStd), (void *) VID_STD_AUTO},
      {"vpfe", "format", DVEVM_ST_INT, &(G->vpfe.capFmt), (void *) VID_FMT_UYVY},
      {"vpfe", "input", DVEVM_ST_INT, &(G->vpfe.input), (void *) TVP5146_AMUX_COMPOSITE},
      {"vpfe", "width", DVEVM_ST_INT, &(G->vpfe.capWidth), (void *) NTSC_WIDTH},
      {"vpfe", "height", DVEVM_ST_INT, &(G->vpfe.capHeight), (void *) NTSC_HEIGHT},

      /* Parameters for Video Decoder */
      {"viddec", "codec", DVEVM_ST_STR, G->vdec.vdecName, DEFAULT_VIDDEC_NAME},
      {"viddec", "maxHeight", DVEVM_ST_INT, &(G->vdec.vdecParams.maxHeight), (void *) VIDDEC_MAX_HT },
      {"viddec", "maxWidth", DVEVM_ST_INT, &(G->vdec.vdecParams.maxWidth), (void *) VIDDEC_MAX_WD },
      {"viddec", "maxFrameRate", DVEVM_ST_INT, &(G->vdec.vdecParams.maxFrameRate), (void *) VIDDEC_MAX_FR },
      {"viddec", "maxBitRate", DVEVM_ST_INT, &(G->vdec.vdecParams.maxBitRate), (void *) VIDDEC_MAX_BR },
      {"viddec", "dataEndianness", DVEVM_ST_INT, &(G->vdec.vdecParams.dataEndianness), (void *) XDM_BYTE },
      {"viddec", "forceChromaFormat", DVEVM_ST_INT, &(G->vdec.vdecParams.forceChromaFormat), (void *) XDM_YUV_422ILE },
      {"viddec", "decodeHeader", DVEVM_ST_INT, &(G->vdec.vdecDynParams.decodeHeader), (void *) XDM_DECODE_AU },
      {"viddec", "displayWidth", DVEVM_ST_INT, &(G->vdec.vdecDynParams.displayWidth), (void *) XDM_DEFAULT },
      {"viddec", "frameSkipMode", DVEVM_ST_INT, &(G->vdec.vdecDynParams.frameSkipMode), (void *) IVIDEO_NO_SKIP },
      {"viddec", "numFrames", DVEVM_ST_INT, &(G->vdec.numFrames), (void *) 10 },

      /* Parameters for Video Encoder */
      {"videnc", "codec", DVEVM_ST_STR, G->venc.vencName, DEFAULT_VIDENC_NAME},
      {"videnc", "encodingPreset", DVEVM_ST_INT, &(G->venc.vencParams.encodingPreset), (void *) XDM_DEFAULT},
      {"videnc", "rateControlPreset", DVEVM_ST_INT, &(G->venc.vencParams.rateControlPreset), (void *) 1},
      {"videnc", "maxHeight", DVEVM_ST_INT, &(G->venc.vencParams.maxHeight), (void *) VIDENC_MAX_HT},
      {"videnc", "maxWidth", DVEVM_ST_INT, &(G->venc.vencParams.maxWidth), (void *) VIDENC_MAX_WD},
      {"videnc", "maxFrameRate", DVEVM_ST_INT, &(G->venc.vencParams.maxFrameRate), (void *) VIDENC_MAX_FR},
      {"videnc", "maxBitRate", DVEVM_ST_INT, &(G->venc.vencParams.maxBitRate), (void *) VIDENC_MAX_BR},
      {"videnc", "dataEndianness", DVEVM_ST_INT, &(G->venc.vencParams.dataEndianness), (void *) XDM_BYTE},
      {"videnc", "maxInterFrameInterval", DVEVM_ST_INT, &(G->venc.vencParams.maxInterFrameInterval), (void *) 0},
      {"videnc", "inputChromaFormat", DVEVM_ST_INT, &(G->venc.vencParams.inputChromaFormat), (void *) XDM_YUV_422ILE},
      {"videnc", "inputContentType", DVEVM_ST_INT, &(G->venc.vencParams.inputContentType), (void *) IVIDEO_PROGRESSIVE},
      {"videnc", "inputHeight", DVEVM_ST_INT, &(G->venc.vencDynParams.inputHeight), (void *) VIDENC_MAX_HT},
      {"videnc", "inputWidth", DVEVM_ST_INT, &(G->venc.vencDynParams.inputWidth), (void *) VIDENC_MAX_WD},
      {"videnc", "refFrameRate", DVEVM_ST_INT, &(G->venc.vencDynParams.refFrameRate), (void *) VIDENC_MAX_FR},
      {"videnc", "targetFrameRate", DVEVM_ST_INT, &(G->venc.vencDynParams.targetFrameRate), (void *) VIDENC_MAX_FR},
      {"videnc", "targetBitRate", DVEVM_ST_INT, &(G->venc.vencDynParams.targetBitRate), (void *) VIDENC_MAX_BR},
      {"videnc", "intraFrameInterval", DVEVM_ST_INT, &(G->venc.vencDynParams.intraFrameInterval), (void *) VIDENC_INTRA_FI},
      {"videnc", "generateHeader", DVEVM_ST_INT, &(G->venc.vencDynParams.generateHeader), (void *) XDM_DECODE_AU},
      {"videnc", "captureWidth", DVEVM_ST_INT, &(G->venc.vencDynParams.captureWidth), (void *) 0},
      {"videnc", "forceIFrame", DVEVM_ST_INT, &(G->venc.vencDynParams.forceIFrame), (void *) 0},
      {"videnc", "numFrames", DVEVM_ST_INT, &(G->venc.numFrames), (void *) DEF_CAP_FRAMES},

      /* Parameters for Speech Decoder */
      {"sphdec", "codec", DVEVM_ST_STR, G->sdec.sdecName, DEFAULT_SPHDEC_NAME},
      {"sphdec", "dataEnable", DVEVM_ST_INT, &(G->sdec.sdecParams.dataEnable), (void *) SPHDEC_DE },
      {"sphdec", "compandingLaw", DVEVM_ST_INT,&(G->sdec.sdecParams.compandingLaw), (void *) SPHDEC_CL },
      {"sphdec", "packingType", DVEVM_ST_INT, &(G->sdec.sdecParams.packingType), (void *) SPHDEC_PT },
      {"sphdec", "inbufsize", DVEVM_ST_INT, &(G->sdec.inBuf.size), (void *) SPHDEC_INBUF_SIZE},
      {"sphdec", "outbufsize", DVEVM_ST_INT, &(G->sdec.outBuf.size), (void *) SPHDEC_OUTBUF_SIZE},

      /* Parameters for Speech Encoder */
      {"sphenc", "codec", DVEVM_ST_STR, G->senc.sencName, DEFAULT_SPHENC_NAME},
      {"sphenc", "seconds", DVEVM_ST_INT, &(G->senc.seconds), (void *) DEFAULT_SPHENC_TIME},
      {"sphenc", "frameSize", DVEVM_ST_INT,&(G->senc.sencParams.frameSize), (void *) SPHENC_FRAME_SIZE },
      {"sphenc", "compandingLaw", DVEVM_ST_INT, &(G->senc.sencParams.compandingLaw), (void *) SPHENC_CL },
      {"sphenc", "packingType", DVEVM_ST_INT, &(G->senc.sencParams.packingType), (void *) SPHENC_PT},
      {"sphenc", "vadSelection", DVEVM_ST_INT, &(G->senc.sencParams.vadSelection),(void *) SPHENC_VS},
      {"sphenc", "inbufsize", DVEVM_ST_INT, &(G->senc.inBuf.size), (void *) (SPHENC_FRAME_SIZE*2)},
      {"sphenc", "outbufsize", DVEVM_ST_INT, &(G->senc.outBuf.size), (void *) SPHENC_FRAME_SIZE},

      /* Parameters for Image Decoder */
      {"imgdec", "codec", DVEVM_ST_STR, G->idec.idecName, DEFAULT_IMGDEC_NAME},
      {"imgdec", "maxHeight", DVEVM_ST_INT, &(G->idec.idecParams.maxHeight), (void *) IMGDEC_MAX_HT },
      {"imgdec", "maxWidth", DVEVM_ST_INT, &(G->idec.idecParams.maxWidth), (void *) IMGDEC_MAX_WD },
      {"imgdec", "maxScans", DVEVM_ST_INT, &(G->idec.idecParams.maxScans), (void *) IMGDEC_MAX_SCANS },
      {"imgdec", "dataEndianness", DVEVM_ST_INT, &(G->idec.idecParams.dataEndianness), (void *) XDM_BYTE },
      {"imgdec", "forceChromaFormat", DVEVM_ST_INT, &(G->idec.idecParams.forceChromaFormat), (void *) XDM_YUV_422ILE },
      //{"imgdec", "numAU", DVEVM_ST_INT, &(G->idec.idecDynParams.numAU), (void *) XDM_DEFAULT },
      //{"imgdec", "decodeHeader", DVEVM_ST_INT, &(G->idec.idecDynParams.decodeHeader), (void *) XDM_DECODE_AU },
      {"imgdec", "displayWidth", DVEVM_ST_INT, &(G->idec.idecDynParams.displayWidth), (void *) XDM_DEFAULT },
      //{"imgdec", "numBytes", DVEVM_ST_INT, &(G->idec.idecInArgs.numBytes), (void *) 0 },

      /* Parameters for Image Encoder */
      {"imgenc", "codec", DVEVM_ST_STR, G->ienc.iencName, DEFAULT_IMGENC_NAME},
      {"imgenc", "maxHeight", DVEVM_ST_INT, &(G->ienc.iencParams.maxHeight), (void *) IMGENC_MAX_HT},
      {"imgenc", "maxWidth", DVEVM_ST_INT, &(G->ienc.iencParams.maxWidth), (void *) IMGENC_MAX_WD},
      {"imgenc", "maxScans", DVEVM_ST_INT, &(G->ienc.iencParams.maxScans), (void *) IMGENC_MAX_SCANS},
      {"imgenc", "dataEndianness", DVEVM_ST_INT, &(G->ienc.iencParams.dataEndianness), (void *) XDM_LE_32},
      {"imgenc", "forceChromaFormat", DVEVM_ST_INT, &(G->ienc.iencParams.forceChromaFormat), (void *) XDM_YUV_422P},
      {"imgenc", "numAU", DVEVM_ST_INT, &(G->ienc.iencDynParams.numAU), (void *) XDM_DEFAULT },
      {"imgenc", "inputChromaFormat", DVEVM_ST_INT, &(G->ienc.iencDynParams.inputChromaFormat), (void *) XDM_YUV_422ILE},
      {"imgenc", "inputHeight", DVEVM_ST_INT, &(G->ienc.iencDynParams.inputHeight), (void *) IMGENC_MAX_HT},
      {"imgenc", "inputWidth", DVEVM_ST_INT, &(G->ienc.iencDynParams.inputWidth), (void *) IMGENC_MAX_WD},
      {"imgenc", "captureWidth", DVEVM_ST_INT, &(G->ienc.iencDynParams.captureWidth), (void *) IMGENC_MAX_WD},
      {"imgenc", "generateHeader", DVEVM_ST_INT, &(G->ienc.iencDynParams.generateHeader), (void *) XDM_ENCODE_AU},
      {"imgenc", "qValue", DVEVM_ST_INT, &(G->ienc.iencDynParams.qValue), (void *) 73}

    };

    DVEVM_CODEC_NUM = sizeof(dvevmStMapArr) / sizeof(DvevmStMapTable);
    MAP = (DvevmStMapTable *)calloc( DVEVM_CODEC_NUM, sizeof(DvevmStMapTable) );
    if (MAP != NULL)
    {
      memcpy(MAP, dvevmStMapArr, DVEVM_CODEC_NUM * sizeof(DvevmStMapTable) );
      valInitialized = DVEVM_ST_TRUE;
    }
  }
}
