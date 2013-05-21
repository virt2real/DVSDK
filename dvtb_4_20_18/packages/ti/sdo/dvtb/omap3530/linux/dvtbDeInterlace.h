/*
 * dvtbDeInterlace.h 
 *
 * DVTB(linux) DeInterlacer Interface
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

#ifndef _DVEVM_ST_DE_INTERLACE_H
#define _DVEVM_ST_DE_INTERLACE_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/universal/universal.h>
#include <ti/sdo/codecs/deinterlacer/ii2p_ti.h>

typedef struct
{
	char deinterName[MAX_NAME_LEN];

	UNIVERSAL_Cmd deinterCmd;
	II2P_Params deinterParams;
	UNIVERSAL_DynamicParams deinterDynParams;
	IDEINTER_InArgs deinterInArgs;
	IDEINTER_OutArgs deinterOutArgs;
	UNIVERSAL_Status deinterStatus;

	int deinterEnable;
	int deinterInWidth;
	int deinterInHeight;
	int deinterInputFormat;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;

	Engine_Handle ceHdl;
	UNIVERSAL_Handle deinterHdl;

} DvevmStDeInterInfo;

DvevmStRetCode
dvtb_deInterInit(DvevmStDeInterInfo *deinter);

DvevmStRetCode
dvtb_deInterEncode(DvevmStDeInterInfo *deinter, int* encDuration);

DvevmStRetCode
dvtb_deInterControl(DvevmStDeInterInfo *deinter);

void
dvtb_deInterCleanup(DvevmStDeInterInfo *deinter);

DvevmStRetCode
dvtb_deInterClose(DvevmStDeInterInfo *deinter);

#endif
