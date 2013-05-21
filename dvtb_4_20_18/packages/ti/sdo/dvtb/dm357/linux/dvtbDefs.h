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


#define DEFAULT_ENGINE_NAME     "decode"

#define DEFAULT_VIDDEC_NAME     "h264dec"
#define DEFAULT_IMGENC_NAME     "jpegenc"
#define DEFAULT_VIDENC_NAME     "h264enc"
#define DEFAULT_IMGDEC_NAME     "jpegdec"
#define DEFAULT_SPHDEC_NAME     "g711dec"
#define DEFAULT_SPHENC_NAME     "g711enc"

#define DEFAULT_IMGENC1_NAME    "jpegenc"
#define DEFAULT_AUDDEC1_NAME    "aachedec"
#define DEFAULT_VIDENC1_NAME    "h264enc"
#define DEFAULT_VIDDEC2_NAME    "mpeg2dec"
#define DEFAULT_SPHDEC1_NAME     "g711dec"
#define DEFAULT_SPHENC1_NAME     "g711enc"


#define DEFAULT_MP3BASEDEC1_NAME     "mp3dec"

#define PERF

#define AUDENC1_FRAME_SIZE (2048)

#endif
