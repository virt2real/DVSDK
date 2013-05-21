/*
 * dvtbDefs.h
 *
 * Platform specific defines
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

#include "dvtbV4L2VPBEOverride.h"

#include <media/davinci/videohd.h>

#define GETP_USAGE  SYS_ERROR("Usage: getp <sphenc|sphdec|videnc1|imgenc1|imgdec1|mpeg4spenc1|jpegenc1|jpegdec1|viddec2|sphenc1|sphdec1|mpeg4spdec2|IPNCUC0|IPNCUC1|IPNCUC2|DVRUC0|DVREnc|DVREncDec> <option> \n")

#define DEFAULT_ENGINE_NAME     "encodedecode"

#define DEFAULT_VIDDEC_NAME     "mpeg4dec"
#define DEFAULT_VIDENC_NAME     "mpeg4enc"
#define DEFAULT_IMGENC_NAME     "jpegenc"
#define DEFAULT_IMGDEC_NAME     "jpegdec"
#define DEFAULT_SPHENC_NAME     "g711enc"
#define DEFAULT_SPHDEC_NAME     "g711dec"
#define DEFAULT_AUDDEC_NAME     "aachedec"
#define DEFAULT_AUDENC_NAME     "aaclcenc"

#define DEFAULT_VIDDEC1_NAME     "mpeg4dec"
#define DEFAULT_VIDENC1_NAME     "mpeg4enc"
#define DEFAULT_AUDDEC1_NAME     "aachedec"
#define DEFAULT_AUDENC1_NAME     "aacheenc"
#define DEFAULT_SPHDEC1_NAME     "g711dec"
#define DEFAULT_SPHENC1_NAME     "g711enc"
#define DEFAULT_IMGENC1_NAME     "jpegenc"
#define DEFAULT_IMGDEC1_NAME     "jpegdec"

#define MAX_MPEG4_INSTANCES             8
#define MAX_DVRENCDEC_MPEG4_INSTANCES   4

#define PERF
//Viddec2
#define VIDDEC2_MAX_WD           (720)
#define VIDDEC2_MAX_HT           (480)
#define VIDDEC2_MAX_FR           (30000)
#define VIDDEC2_MAX_BR           (10000000)//((VIDDEC2_MAX_FR/1000) * (VIDDEC2_MAX_HT) * (VIDDEC2_MAX_WD) * 2)
#define VIDDEC2_MAX_OUT_BUFFERS 17
#define VIDDEC2_PAD_WIDTH (0)

//Viddec2
#define VIDENC1_MAX_WD           (720)
#define VIDENC1_MAX_HT           (480)
#define VIDENC1_MAX_FR           (30000)
#define VIDENC1_MAX_BR           2000000//((VIDENC1_MAX_FR) * (VIDENC1_MAX_HT) * (VIDENC1_MAX_WD) * 2)
#define VIDENC1_INTRA_FI         (30)
#define DEF_CAP_FRAMES           (30)

//Imgdec1
#define IMGDEC1_MAX_HT           (480)
#define IMGDEC1_MAX_WD           (720)
#define IMGDEC1_MAX_SCANS        (1)

#define AUDENC1_FRAME_SIZE (2048)

#endif
