/*
 * dvtbDVREncDecDef.h
 *
 * Definitions for XDM1.0 DVR Encode Decode
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

#ifndef _DVEVM_ST_DVREncDec_DEF_H
#define _DVEVM_ST_DVREncDec_DEF_H

#define MAX_DVRENCDEC_MPEG4_INSTANCES       4

#define DVREncDec_VIDENCNAME               "mpeg4enc"
#define DVREncDec_VIDDECNAME               "mpeg4dec"
#define DVREncDec_WIDTH_SIF                352
#define DVREncDec_HEIGHT_SIF               240
#define DVREncDec_FR_SIF                   30000
#define DVREncDec_BR_SIF                   512000
#define DVREncDec_FI_SIF                   30
#define DVREncDec_EP_SIF                   3
#define DVREncDec_RCP_SIF                  1

typedef struct
{
	DvevmStMPEG4SPVEncInfo enc[MAX_DVRENCDEC_MPEG4_INSTANCES]; //Max 4 instances
	DvevmStMPEG4SPDecInfo dec[MAX_DVRENCDEC_MPEG4_INSTANCES]; //Max 4 instances
	Engine_Handle ceHdl; // Codec Engine Handle
	int numFrames; // Number of frames to encode
} DvevmStDVREncDecInfo;

#endif

