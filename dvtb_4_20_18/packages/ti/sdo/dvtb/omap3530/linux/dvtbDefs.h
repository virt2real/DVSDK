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

#include "dvtbV4L2VPBEFeatures.h"
#include "dvtbV4L2VPBEOverride.h"

#define GETP_USAGE  SYS_ERROR("Usage: getp <videnc1|auddec1|mp3basedec1|imgdec1|sphenc1|sphdec1|imgenc1|viddec2|jpegdec1|pwrmanager|vidloopback1|h264enc1|h264dec2|mpeg4spenc1|mpeg4spdec2|mpeg2dec2> <option> \n")

#define DEFAULT_ENGINE_NAME     "encodedecode"

#define DEFAULT_VIDDEC_NAME     "mpeg4dec"
#define DEFAULT_IMGENC_NAME     "jpegenc"
#define DEFAULT_VIDENC_NAME     "mpeg4enc"
#define DEFAULT_IMGDEC_NAME     "jpegdec"

#define DEFAULT_IMGENC1_NAME    "jpegenc"
#define DEFAULT_AUDDEC1_NAME    "aachedec"
#define DEFAULT_VIDENC1_NAME    "h264enc"
#define DEFAULT_VIDDEC2_NAME    "mpeg2dec"
#define DEFAULT_SPHDEC1_NAME     "g711dec"
#define DEFAULT_SPHENC1_NAME     "g711enc"

#define DEFAULT_MP3BASEDEC1_NAME     "mp3dec"

#define DEFAULT_H264DEC2_NAME "h264dec" 
#define DEFAULT_H264ENC1_NAME "h264enc" 
#define DEFAULT_MPEG4DEC2_NAME "mpeg4dec" 
#define DEFAULT_MPEG4ENC1_NAME "mpeg4enc" 
#define DEFAULT_MPEG2DEC2_NAME "mpeg2dec"
#define PERF


//Exception: We need to remove it in the next release
#define V4L2_STD_720P_60 -1
#define V4L2_STD_1080I_60 -1

//Viddec2
#define VIDDEC2_MAX_FR           (30000)
#define VIDDEC2_MAX_BR           (10000000)//((VIDDEC2_MAX_FR/1000) * (VIDDEC2_MAX_HT) * (VIDDEC2_MAX_WD) * 2)
#define VIDDEC2_MAX_OUT_BUFFERS  17
#define VIDDEC2_PAD_WIDTH        (0)

//Videnc1
#define VIDENC1_MAX_WD           (720)
#define VIDENC1_MAX_HT           (480)
#define VIDENC1_MAX_FR           (30000)
#define VIDENC1_MAX_BR           2000000//((VIDENC1_MAX_FR) * (VIDENC1_MAX_HT) * (VIDENC1_MAX_WD) * 2)
#define VIDENC1_INTRA_FI         (30)
#define DEF_CAP_FRAMES           (30)

//Imgdec1
#define IMGDEC1_MAX_HT           (576)
#define IMGDEC1_MAX_WD           (720)
#define IMGDEC1_MAX_SCANS        (1)

//Auddec1
#define AUDDEC1_INBUF_SIZE       25600 //For normal audio decoding (1648), For wma decoding 25600
#define AUDDEC1_OUTBUF_SIZE      16384 //For normal audio decoding (8192), For wma decoding 16384
#define AUDDEC1_PCM_WIDTH        16

#define AUDENC1_FRAME_SIZE (2048)

#endif
