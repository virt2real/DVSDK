/*
 * dvtbIPNCUC1Def.h
 *
 * Definitions for XDM1.0 IPNC Usecase 1
 * IPNCUC1:MPEG4, D1, 30fps, 2Mbps + MPEG4, SIF, 30fps, 0.5Mbps + JPEG, D1, 15 fps, QP=75
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

#ifndef _DVEVM_ST_IPNCUC1_DEF_H
#define _DVEVM_ST_IPNCUC1_DEF_H

#define IPNCUC1_VIDENCNAME_D1         "mpeg4enc"
#define IPNCUC1_VIDENCNAME_SIF        "mpeg4enc"
#define IPNCUC1_WIDTH_D1              720
#define IPNCUC1_HEIGHT_D1             480
#define IPNCUC1_WIDTH_SIF             352
#define IPNCUC1_HEIGHT_SIF            240
#define IPNCUC1_FR_D1                 30000
#define IPNCUC1_FR_SIF                30000
#define IPNCUC1_BR_D1                 2000000
#define IPNCUC1_BR_SIF                512000
#define IPNCUC1_FI_D1                 30
#define IPNCUC1_FI_SIF                30
#define IPNCUC1_ENCODING_PRESET_D1    3
#define IPNCUC1_RCP_D1                1
#define IPNCUC1_ENCODING_PRESET_SIF   3
#define IPNCUC1_RCP_SIF               1
#define IPNCUC1_IMGENCNAME_D1         "jpegenc"
#define IPNCUC1_WIDTH_JPEGD1          720
#define IPNCUC1_HEIGHT_JPEGD1         480
#define IPNCUC1_QVALUE_JPEGD1         75

typedef struct
{
	DvevmStMPEG4SPVEncInfo encD1;
	DvevmStMPEG4SPVEncInfo encSIF;
	DvevmStImgEnc1Info encJPEGD1;
	Engine_Handle ceHdl; // Codec Engine Handle
	int numFrames; // Number of frames to encode
} DvevmStIPNCUC1Info;

#endif

