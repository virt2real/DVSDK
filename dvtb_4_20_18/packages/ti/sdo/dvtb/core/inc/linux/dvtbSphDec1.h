/*
 * dvtbSphDec1.h
 *
 * DVTB(linux) XDM1.0 Speech Decoder Interface
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

#ifndef _DVEVM_ST_SPH_DEC1_H
#define _DVEVM_ST_SPH_DEC1_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/speech1/sphdec1.h>

#define DEF_SPHFRAME_SIZE       (8192)
#define DEF_SPH_SAMPLERATE      (8000)

#define PRM_SIZE_20  38
#define PRM_SIZE_30  50

#define SPHDEC1_DE               (0)/* ON=1, OFF=0*/
#define SPHDEC1_CL               (1)
#define SPHDEC1_PT               (1)

#define SPHDEC1_INBUF_SIZE       (80)
#define SPHDEC1_OUTBUF_SIZE      (SPHDEC1_INBUF_SIZE*4)
/* Constants for frame types */
#define NO_TX_FRAME_TYPE      0  /* No transmission frame */
#define SPEECH_FRAME_TYPE     1  /* Active speech frame */
#define SID_FRAME_TYPE        2  /* Silence Insertion Description frame */
#define ERASURE_FRAME_TYPE    3  /* frame erasure case */

typedef struct
{
	char sdecName[MAX_NAME_LEN];

	SPHDEC1_Params sdecParams;
	SPHDEC1_Status sdecStatus;
	SPHDEC1_DynamicParams sdecDynParams;
	SPHDEC1_InArgs sdecInArgs;
	SPHDEC1_OutArgs sdecOutArgs;

	DvevmStBuffer inBuf;
	DvevmStBuffer outBuf;

	Engine_Handle ceHdl;
	SPHDEC1_Handle sdecHdl;
} DvevmStSphDec1Info;

DvevmStRetCode
dvtb_sphDec1Init(DvevmStSphDec1Info *sd);

DvevmStRetCode
dvtb_sphDec1Decode(DvevmStSphDec1Info *sd, int *decDuration);

DvevmStRetCode
dvtb_sphDec1Control1(DvevmStSphDec1Info *sd);

DvevmStRetCode
dvtb_sphDec1Control(DvevmStSphDec1Info *sd);

void
dvtb_sphDec1Cleanup(DvevmStSphDec1Info *sd);

DvevmStRetCode
dvtb_sphDec1Close(DvevmStSphDec1Info *sd);

#endif
