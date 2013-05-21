/*
 * dvtbVidDec.h
 *
 * XDM0.9 Video Decode Interface
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

#ifndef _DVEVM_ST_VID_DEC_H
#define _DVEVM_ST_VID_DEC_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/video/viddec.h>

#define VIDDEC_MAX_WD           (720)
#define VIDDEC_MAX_HT           (480)
#define VIDDEC_MAX_FR           (30000)
#define VIDDEC_MAX_BR           (10000000)//((VIDDEC_MAX_FR/1000) * (VIDDEC_MAX_HT) * (VIDDEC_MAX_WD) * 2)
typedef struct
{
	char vdecName[MAX_NAME_LEN];

	VIDDEC_Params vdecParams;
	VIDDEC_Cmd vdecCmd;
	VIDDEC_DynamicParams vdecDynParams;
	VIDDEC_InArgs vdecInArgs;
	VIDDEC_OutArgs vdecOutArgs;
	VIDDEC_Status vdecStatus;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;

	Engine_Handle ceHdl;
	VIDDEC_Handle vdecHdl;

	DvevmStBool skipFrame;
	unsigned int numFrames;
} DvevmStVidDecInfo;

DvevmStRetCode
dvtb_vidDecInit(DvevmStVidDecInfo *vd);

DvevmStRetCode
dvtb_vidDecDecode(DvevmStVidDecInfo *vd, int *decDuration);

void
dvtb_vidDecCleanup(DvevmStVidDecInfo *vd);

DvevmStRetCode
dvtb_vidDecControl(DvevmStVidDecInfo *vd);

DvevmStRetCode
dvtb_vidDecClose(DvevmStVidDecInfo *vd);

#endif
