/*
 * dvtbWMADec1.h
 *
 * XDM1.2 WMA Decode Interface
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

#ifndef _DVEVM_ST_WMA_DEC1_H
#define _DVEVM_ST_WMA_DEC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include "dvtbDefs.h"
#include <ti/sdo/ce/audio1/auddec1.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/iauddec1.h>

typedef struct ITTIAM_WMADEC_Params
{
	IAUDDEC1_Params auddec_params;
	XDAS_Int32 i_constant_output; 
	XDAS_Int32 i_use_full_output_buff;
}ITTIAM_WMADEC_Params;

typedef struct ITTIAM_WMADEC_DynamicParams
{
	IAUDDEC1_DynamicParams auddec_dynamicparams;
}ITTIAM_WMADEC_DynamicParams;

typedef struct ITTIAM_WMADEC_Status 
{
	IAUDDEC1_Status  auddec_status;
}ITTIAM_WMADEC_Status;

typedef struct ITTIAM_WMADEC_InArgs 
{
	IAUDDEC1_InArgs auddec_inArgs;
}ITTIAM_WMADEC_InArgs;

typedef struct ITTIAM_WMADEC_OutArgs
{
	IAUDDEC1_OutArgs  auddec_outArgs;
	XDAS_Int32 i_exec_done; 
}ITTIAM_WMADEC_OutArgs;

typedef struct
{
	char adecName[MAX_NAME_LEN];
	ITTIAM_WMADEC_Params adecParams;

	IAUDDEC1_Cmd adecCmd;
	ITTIAM_WMADEC_DynamicParams adecDynParams;
	ITTIAM_WMADEC_Status adecStatus;
	ITTIAM_WMADEC_InArgs adecInArgs;
	ITTIAM_WMADEC_OutArgs adecOutArgs;

	int desiredChannelMode;
	int inFrameSize;
	int decFrameSize;
	unsigned int pEnable;
	int lfeFlag;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;

	Engine_Handle ceHdl;
	AUDDEC1_Handle adecHdl;
} DvevmStWmaDec1Info;

DvevmStRetCode
dvtb_wmaDec1Init(DvevmStWmaDec1Info *ad);

DvevmStRetCode
dvtb_wmaDec1Decode(DvevmStWmaDec1Info *ad, int *decDuration);

DvevmStRetCode
dvtb_wmaDec1Control(DvevmStWmaDec1Info *ad);

void
dvtb_wmaDec1Cleanup(DvevmStWmaDec1Info *ad);

DvevmStRetCode
dvtb_wmaDec1Close(DvevmStWmaDec1Info *ad);

#endif
