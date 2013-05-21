/*
 * dvtbMP3Dec1.h
 *
 * XDM1.0 MP3 Decode Interface
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

#ifndef _DVEVM_ST_MP3_DEC1_H
#define _DVEVM_ST_MP3_DEC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include "dvtbDefs.h"
#include <ti/sdo/ce/audio1/auddec1.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/iauddec1.h>

typedef struct ITTIAM_MP3DEC_Params 
{
	IAUDDEC1_Params auddec_params;
	XDAS_Int32 i_frame_synch_check;
}ITTIAM_MP3DEC_Params;

typedef struct ITTIAM_MP3DEC_DynamicParams
{
	IAUDDEC1_DynamicParams auddec_dynamicparams;
}ITTIAM_MP3DEC_DynamicParams;


typedef struct ITTIAM_MP3DEC_Status 
{
	IAUDDEC1_Status  auddec_status;
	XDAS_Int32 i_num_layer;
}ITTIAM_MP3DEC_Status;

typedef struct ITTIAM_MP3DEC_InArgs 
{
	IAUDDEC1_InArgs auddec_inArgs;
}ITTIAM_MP3DEC_InArgs;

typedef struct ITTIAM_MP3DEC_OutArgs 
{
	IAUDDEC1_OutArgs  auddec_outArgs;
	XDAS_Int32 i_init_done; 
	XDAS_Int32 i_exec_done; 
	XDAS_Int32 i_ittiam_err_code ; 
	XDAS_Int32 i_output_bits_per_sample; 
	XDAS_Int32 i_num_channels; 
	XDAS_Int32 i_channel_mask;
}ITTIAM_MP3DEC_OutArgs;

typedef struct
{
	char adecName[MAX_NAME_LEN];
	ITTIAM_MP3DEC_Params adecParams;

	IAUDDEC1_Cmd adecCmd;
	ITTIAM_MP3DEC_DynamicParams adecDynParams;
	ITTIAM_MP3DEC_Status adecStatus;
	ITTIAM_MP3DEC_InArgs adecInArgs;
	ITTIAM_MP3DEC_OutArgs adecOutArgs;

	int desiredChannelMode;
	int inFrameSize;
	int decFrameSize;
	unsigned int pEnable;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;

	Engine_Handle ceHdl;
	AUDDEC1_Handle adecHdl;
} DvevmStMp3Dec1Info;

DvevmStRetCode
dvtb_mp3Dec1Init(DvevmStMp3Dec1Info *ad);

DvevmStRetCode
dvtb_mp3Dec1Decode(DvevmStMp3Dec1Info *ad, int *decDuration);

DvevmStRetCode
dvtb_mp3Dec1Control(DvevmStMp3Dec1Info *ad);

void
dvtb_mp3Dec1Cleanup(DvevmStMp3Dec1Info *ad);

DvevmStRetCode
dvtb_mp3Dec1Close(DvevmStMp3Dec1Info *ad);

#endif
