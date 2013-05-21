/*
 * dvtbDVRUC0Def.h
 *
 * Definitions for XDM1.0 DVR Usecase 0
 * DVRUC0:2channels of D1 MPEG4, 30fps, 2Mbps each channel
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

#ifndef _DVEVM_ST_DVRUC0_DEF_H
#define _DVEVM_ST_DVRUC0_DEF_H

#define DVRUC0_VIDENCNAME_1D1         "mpeg4enc"
#define DVRUC0_VIDENCNAME_2D1         "mpeg4enc"
#define DVRUC0_WIDTH_1D1              720
#define DVRUC0_HEIGHT_1D1             480
#define DVRUC0_WIDTH_2D1              720
#define DVRUC0_HEIGHT_2D1             480
#define DVRUC0_FR_1D1                 30000
#define DVRUC0_FR_2D1                 30000
#define DVRUC0_BR_1D1                 2000000
#define DVRUC0_BR_2D1                 2000000
#define DVRUC0_FI_1D1                 30
#define DVRUC0_FI_2D1                 30
#define DVRUC0_ENCODING_PRESET_1D1    3
#define DVRUC0_RCP_1D1                1
#define DVRUC0_ENCODING_PRESET_2D1    3
#define DVRUC0_RCP_2D1                1

typedef struct
{
	DvevmStMPEG4SPVEncInfo enc1D1;
	DvevmStMPEG4SPVEncInfo enc2D1;
	Engine_Handle ceHdl; // Codec Engine Handle
	int numFrames; // Number of frames to encode
} DvevmStDVRUC0Info;

#endif

