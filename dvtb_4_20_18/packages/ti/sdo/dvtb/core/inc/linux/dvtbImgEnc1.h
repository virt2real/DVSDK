/*
 * dvtbImgEnc1.h
 *
 * DVTB(linux) XDM1.0 Image Encoder Interface
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

#ifndef _DVEVM_ST_IMG_ENC1_H
#define _DVEVM_ST_IMG_ENC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/image1/imgenc1.h>

#define IMGENC1_MAX_HT      (480)
#define IMGENC1_MAX_WD      (720)
#define IMGENC1_MAX_SCANS   (0)

typedef struct
{
	char ienc1Name[MAX_NAME_LEN]; // Codec Name

	IMGENC1_Params ienc1Params; // Encoder parameters

	IMGENC1_Cmd ienc1Cmd; // Codec control Command
	IMGENC1_DynamicParams ienc1DynParams; // Dynamic Parameters
	IMGENC1_Status ienc1Status; // Status of encode process
	IMGENC1_InArgs ienc1InArgs;
	IMGENC1_OutArgs ienc1OutArgs; // Output arguments

	DvevmStXdmBuffer inBuf; // Input XDM Buffer
	DvevmStXdmBuffer outBuf; // Output XDM Buffer
	XDM1_BufDesc inBufDesc;
	XDM1_BufDesc outBufDesc;

	Engine_Handle ceHdl; // Codec Engine Handle
	IMGENC1_Handle ienc1Hdl; // Encoder Handle

} DvevmStImgEnc1Info;

DvevmStRetCode
dvtb_imgEnc1Init(DvevmStImgEnc1Info *ienc);

DvevmStRetCode
dvtb_imgEnc1Encode(DvevmStImgEnc1Info *ienc, int *encDuration);

DvevmStRetCode
dvtb_imgEnc1Control(DvevmStImgEnc1Info *ienc);

DvevmStRetCode
dvtb_imgEnc1Close(DvevmStImgEnc1Info *ienc);

void
dvtb_imgEnc1Cleanup(DvevmStImgEnc1Info *ienc1);

#endif
