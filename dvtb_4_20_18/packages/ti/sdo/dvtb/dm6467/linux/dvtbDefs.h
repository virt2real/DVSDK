/*
 * dvtbDefs.h
 *
 * Platform specific definitions
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

#ifndef DVEVM_ST_DEFS_H
#define DVEVM_ST_DEFS_H

#include <media/davinci/videohd.h>

#include "dvtbV4L2VPBEOverride.h"

#define GETP_USAGE  SYS_ERROR("Usage: getp <auddec|sphenc|sphdec|aacenc|videnc1|audenc1|auddec1|sphenc1|sphdec1|h264enc1|aachedec1|aacheenc1|viddec2|h264dec2|mpeg2dec2|vidloopback1|mpeg4enc> <option> \n")

#define DEFAULT_ENGINE_NAME     "encodedecode"

#define DEFAULT_VIDDEC_NAME     "mpeg2dec"
#define DEFAULT_VIDENC_NAME     "mpeg4enc"
#define DEFAULT_SPHENC_NAME     "g711enc"
#define DEFAULT_SPHDEC_NAME     "g711dec"
#define DEFAULT_AUDDEC_NAME     "aachedec"
#define DEFAULT_AUDENC_NAME     "aaclcenc"
#define DEFAULT_IMGDEC_NAME     "jpegdec"

#define DEFAULT_AC3DEC1_NAME "dolbyac3dec"
#define DEFAULT_MP3BASEDEC1_NAME "mp3dec"
#define DEFAULT_H2641080pDEC2_NAME "h2641080p60vdec"
#define DEFAULT_IMGENC1_NAME    "jpegenc"
#define DEFAULT_VIDDEC2_NAME     "h264dec"
#define DEFAULT_MPEG2DEC2_NAME   "mpeg2dec"
#define DEFAULT_H264DEC2_NAME    "h264dec"
#define DEFAULT_MPEG4DEC2_NAME   "mpeg4dec"
#define DEFAULT_MPEG4ENC1_NAME "mpeg4enc"
#define DEFAULT_VIDENC1_NAME     "h264enc"
#define DEFAULT_AUDDEC1_NAME     "aachedec"
#define DEFAULT_AUDENC1_NAME     "aacheenc"
#define DEFAULT_SPHDEC1_NAME     "g711dec"
#define DEFAULT_SPHENC1_NAME     "g711enc"
#define DEFAULT_H264FHDENC1_NAME "h264fhdvenc"

#define PERF

//Viddec2
#define VIDDEC2_MAX_WD           (1920)
#define VIDDEC2_MAX_HT           (1088)
#define VIDDEC2_MAX_FR           (30000)
#define VIDDEC2_MAX_BR           (10000000)//((VIDDEC2_MAX_FR/1000) * (VIDDEC2_MAX_HT) * (VIDDEC2_MAX_WD) * 2)
#define VIDDEC2_MAX_OUT_BUFFERS 17
#define VIDDEC2_PAD_WIDTH (48)

//Videnc1
#define VIDENC1_DMAI_DEFAULT_WD  (1280)
#define VIDENC1_MAX_WD           (720)
#define VIDENC1_MAX_HT           (576)
#define VIDENC1_MAX_FR           (30000)
#define VIDENC1_MAX_BR           2000000//((VIDENC1_MAX_FR) * (VIDENC1_MAX_HT) * (VIDENC1_MAX_WD) * 2)
#define VIDENC1_INTRA_FI         (30)
#define DEF_CAP_FRAMES           (30)

//Auddec1
#define AUDDEC1_MAX_SR              (48000)
#define AUDDEC1_MAX_CH              (2)
#define AUDDEC1_MAX_BR              (448000)//(MP3BASEDEC_MAX_SR*MP3BASEDEC_MAX_CH*4)  /* Assuming 16 bits per sample */
#define AUDDEC1_INBUF_SIZE          (2048)//(4096)
#define AUDDEC1_OUTBUF_SIZE         (8192)//(4608)
#define AUDDEC1_PCM_WIDTH		    (16)

//Imgdec1
#define IMGDEC1_MAX_HT           (576)
#define IMGDEC1_MAX_WD           (720)
#define IMGDEC1_MAX_SCANS        (1)

#define AUDENC1_FRAME_SIZE (2048)

#endif
