/*
 * dvtbAACEnc.h
 *
 * XDM0.9 AAC Encode Interface
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

#ifndef _DVEVM_ST1
#define _DVEVM_ST1

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/audio/audenc.h>
//#include <ti/sdo/codecs/aacheenc/iaacenc.h>

#define AACENC_FRAME_SIZE          (80)
#define AACENC_MAX_SR              (48000)
#define AACENC_MAX_CH              (1) //IAUDIO_STEREO
#define AACENC_MAX_BR              288000
#define AACENC_INBUF_SIZE          (9192)
#define AACENC_OUTBUF_SIZE         (3744)
#define DEFAULT_AACENC_TIME        (10)

typedef struct
{
	AUDENC_Cmd aencCmd;
	char aencName[MAX_NAME_LEN];
	unsigned int seconds; /* Number of seconds for audio capture */
	unsigned int insamples;

//	IAACENC_Params aencParams;
//	IAACENC_DynamicParams aencDynParams;
//	IAACENC_Status aencStatus;
//	IAACENC_InArgs aencInArgs;
//	IAACENC_OutArgs aencOutArgs;

	DvevmStXdmBuffer inBuf;
	DvevmStXdmBuffer outBuf;
	unsigned int bytesGenerated;

	Engine_Handle ceHdl;
	AUDENC_Handle aencHdl;
} DvevmStAACEncInfo;

void
dvtb_aacEncCleanup(DvevmStAACEncInfo *ae);

DvevmStRetCode
dvtb_aacEncInit(DvevmStAACEncInfo *ae);

DvevmStRetCode
dvtb_aacEncEncode(DvevmStAACEncInfo *ae, int *encDuration);

DvevmStRetCode
dvtb_aacEncControl(DvevmStAACEncInfo *ae);

DvevmStRetCode
dvtb_aacEncClose(DvevmStAACEncInfo *ae);

#endif
