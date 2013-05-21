/*
 * dvtbSphDec.h
 *
 * XDM0.9 Speech Decode Interface
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

#ifndef _DVEVM_ST_SPH_DEC_H
#define _DVEVM_ST_SPH_DEC_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/speech/sphdec.h>

#define DEF_SPHFRAME_SIZE       (8192)
#define DEF_SPH_SAMPLERATE      (8000)

#define SPHDEC_DE               (0)/* ON=1, OFF=0*/
#define SPHDEC_CL               (1)
#define SPHDEC_PT               (1)

#define SPHDEC_INBUF_SIZE       (80)
#define SPHDEC_OUTBUF_SIZE      (SPHDEC_INBUF_SIZE*4)

typedef struct
{
  char sdecName[MAX_NAME_LEN];
  SPHDEC_Params sdecParams;
  SPHDEC_Status sdecStatus;
  SPHDEC_DynamicParams sdecDynParams;
  SPHDEC_InArgs sdecInArgs;
  SPHDEC_OutArgs sdecOutArgs;

  DvevmStBuffer inBuf;
  DvevmStBuffer outBuf;

  Engine_Handle ceHdl;
  SPHDEC_Handle sdecHdl;
} DvevmStSphDecInfo;

DvevmStRetCode
dvtb_sphDecInit(DvevmStSphDecInfo *sd);

DvevmStRetCode
dvtb_sphDecDecode(DvevmStSphDecInfo *sd);

DvevmStRetCode
dvtb_sphDecControl(DvevmStSphDecInfo *sd);

DvevmStRetCode
dvtb_sphDecClose(DvevmStSphDecInfo *sd);

#endif
