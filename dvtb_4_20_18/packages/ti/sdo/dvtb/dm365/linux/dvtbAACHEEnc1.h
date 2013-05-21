/*
 * dvtbAACHEEnc1.h
 *
 * XDM1.0 AACHE Encoder Interface
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

#ifndef _DVEVM_ST_AACHE_ENC1_H
#define _DVEVM_ST_AACHE_ENC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/xdais/dm/xdm.h>
#include <ti/sdo/ce/audio1/audenc1.h>

#define AACHEENC1_MAX_SR              (64000) //(16000)
#define AACHEENC1_BR                  (48000)
#define AACHEENC1_SR                  (44100)
#define AACHEENC1_MAX_BR              (192000)
#define AACHEENC1_MODE                (0)
#define AACHEENC1_BPS                 (16)
#define AACHEENC1_DMONO               (0)
#define AACHEENC1_CRC                 (0)
#define AACHEENC1_ANC                 (1)
#define AACHEENC1_LFE                 (0)
#define AACHEENC1_MAX_CH              (2) //(1)
#define AACHEENC1_MAX_BR              (192000) //(AACENC_MAX_SR*AACENC_MAX_CH*16)  /* Assuming 16bits per sample */
#define AACHEENC1_INBUF_SIZE          (8192)//(1648)//(4096)
#define AACHEENC1_OUTBUF_SIZE         (3000)
#define AACHEENC1_OUTBUF_SIZE         (3000)
#define DEFAULT_AACHEENC1_TIME        (10)

#define AACHEENC1_DMIX (0)
#define AACHEENC1_OTYPE ( AACENC_OBJ_TYP_HEAAC )
#define AACHEENC1_OFF   (AACENC_TT_ADTS)
#define AACHEENC1_ARATE  (-1)
#define AACHEENC1_BRM    (0)
#define AACHEENC1_FRAME_SIZE (2048)
#define AACLCENC1_FRAME_SIZE (1024)

typedef enum
{
  AACENC_OBJ_TYP_LC           = 2,   /*!< AAC Low Complexity  */
  AACENC_OBJ_TYP_HEAAC        = 5,   /*!< HE AAC              */
  AACENC_OBJ_TYP_PS           = 29   /*!< AAC LC + SBR + PS   */
} AACENC_OBJ_TYP;

typedef struct ITTIAM_EAACPLUSENC_Params
{
	IAUDENC1_Params audenc_params;
	XDAS_Int32 noChannels; 
	XDAS_Int32 aacClassic; 
	XDAS_Int32 psEnable; 
	XDAS_Int32 dualMono; 
	XDAS_Int32 downmix; 
	XDAS_Int32 useSpeechConfig; 
	XDAS_Int32 fNoStereoPreprocessing; 
	XDAS_Int32 invQuant; 
	XDAS_Int32 useTns; 
	XDAS_Int32 use_ADTS; 
	XDAS_Int32 use_ADIF; 
	XDAS_Int32 full_bandwidth; 
	XDAS_Int32 i_channels_mask;
	XDAS_Int32 i_num_coupling_chan; 
	XDAS_Int32 write_program_config_element;
}ITTIAM_EAACPLUSENC_Params;

typedef struct ITTIAM_EAACPLUSENC_DynamicParams 
{
	IAUDENC1_DynamicParams audenc_dynamicparams;
}ITTIAM_EAACPLUSENC_DynamicParams;

typedef struct ITTIAM_EAACPLUSENC_Status 
{
	IAUDENC1_Status  audenc_status;
}ITTIAM_EAACPLUSENC_Status;

typedef struct ITTIAM_EAACPLUSENC_InArgs 
{
	IAUDENC1_InArgs audenc_inArgs;
}ITTIAM_EAACPLUSENC_InArgs;

typedef struct ITTIAM_EAACPLUSENC_OutArgs 
{
	IAUDENC1_OutArgs audenc_outArgs;
	XDAS_Int32 i_exec_done; 
	XDAS_Int32 i_ittiam_err_code;
}ITTIAM_EAACPLUSENC_OutArgs;

typedef struct
{
	IAUDENC1_Cmd aenc1Cmd;
	char aacenc1Name[MAX_NAME_LEN];
	unsigned int seconds; /* Number of seconds for audio capture */
	unsigned int outsamples;
	unsigned int insamples;
	volatile int Framenum;
	int framesize;
	int numChannels;
	int executionDone;
	ITTIAM_EAACPLUSENC_Params aacenc1Params;
	ITTIAM_EAACPLUSENC_DynamicParams aacenc1DynParams;
	ITTIAM_EAACPLUSENC_Status aacenc1Status;
	ITTIAM_EAACPLUSENC_InArgs aacenc1InArgs;
	ITTIAM_EAACPLUSENC_OutArgs aacenc1OutArgs;
	XDM1_BufDesc inBuf;
	XDM1_BufDesc outBuf;

	DvevmStBuffer ancBuf;
	AACENC_OBJ_TYP  outObjectType;

	Engine_Handle ceHdl;
	AUDENC1_Handle aacenc1Hdl;
} DvevmStAacHeEnc1Info;

void
dvtb_aacheEnc1Cleanup(DvevmStAacHeEnc1Info *aace);

DvevmStRetCode
dvtb_aacheEnc1Init(DvevmStAacHeEnc1Info *aace);

DvevmStRetCode
dvtb_aacheEnc1Encode(DvevmStAacHeEnc1Info *aace, int *encDuration);

DvevmStRetCode
dvtb_aacheEnc1Control(DvevmStAacHeEnc1Info *aace);

DvevmStRetCode
dvtb_aacheEnc1Close(DvevmStAacHeEnc1Info *aace);

#endif
