/*
 * dvtbIPNCUC0Def.h
 *
 * Definitions for XDM1.0 IPNC Usecase 0
 * IPNCUC0:MPEG4 encode (720P 30 fps 6 Mbps + SIF 30 fps 512 Kbps)
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

#ifndef _DVEVM_ST_IPNCUC0_DEF_H
#define _DVEVM_ST_IPNCUC0_DEF_H

#define IPNCUC0_VIDENCNAME_720P        "mpeg4enc"
#define IPNCUC0_VIDENCNAME_SIF         "mpeg4enc"
#define IPNCUC0_WIDTH_720P              1280
#define IPNCUC0_HEIGHT_720P             720
#define IPNCUC0_WIDTH_SIF               352
#define IPNCUC0_HEIGHT_SIF              240
#define IPNCUC0_FR_720P                 30000
#define IPNCUC0_FR_SIF                  30000
#define IPNCUC0_BR_720P                 6000000
#define IPNCUC0_BR_SIF                  512000
#define IPNCUC0_FI_720P                 30
#define IPNCUC0_FI_SIF                  30
#define IPNCUC0_ENCODING_PRESET_720P    3
#define IPNCUC0_RCP_720P                1
#define IPNCUC0_ENCODING_PRESET_SIF     3
#define IPNCUC0_RCP_SIF                 1

typedef struct
{
	DvevmStMPEG4SPVEncInfo enc720p;
	DvevmStMPEG4SPVEncInfo encSIF;
	Engine_Handle ceHdl; // Codec Engine Handle
	int numFrames; // Number of frames to encode
} DvevmStIPNCUC0Info;

#endif

