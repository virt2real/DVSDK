/*
 * dvtbParam.h
 *
 * Interfaces for DVTB Handlers Initialization
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

#ifndef _DVEVM_ST_PARAM_H
#define _DVEVM_ST_PARAM_H

#include "dvtbGlobal.h"

#include "dvtbOSSAudio.h"
#include "dvtbFBVPBE.h"
#include "dvtbV4L2VPFE.h"

#include "dvtbVidDec.h"
#include "dvtbVidEnc.h"
#include "dvtbSphDec.h"
#include "dvtbSphEnc.h"
#include "dvtbImgDec.h"
#include "dvtbImgEnc.h"

typedef enum
{
  DVEVM_ST_INT = 0,
  DVEVM_ST_STR,
  DVEVM_ST_CHAR,
  DVEVM_ST_SHORT,
  DVEVM_ST_INVALID
}DvevmStType;

typedef struct
{
  DvevmStEngineInfo eng;                        // Codec Engine Info

  DvevmStAudioInfo aud;                         // Audio Driver Info

  DvevmStVpbeInfo vpbe;                         // VPBE Driver Info
  DvevmStVpfeInfo vpfe;                         // VPFE Driver Info

  DvevmStVidDecInfo vdec;                       // Video Decoder Info
  DvevmStVidEncInfo venc;                       // Video Encoder Info
  DvevmStSphDecInfo sdec;                       // Speech Decoder Info
  DvevmStSphEncInfo senc;                       // Speech Encoder Info
  DvevmStImgDecInfo idec;                       // Image Decoder Info
  DvevmStImgEncInfo ienc;                       // Image Encoder Info

} DvevmStGlobalParams;

typedef struct
{
  char className[MAX_KEY_SIZE];
  char fieldName[MAX_NAME_LEN];
  DvevmStType fieldType;
  void *value;
  void *defaultValue;
} DvevmStMapTable;

extern unsigned int DVEVM_CODEC_NUM;

extern DvevmStMapTable *MAP;
extern DvevmStGlobalParams *G;

void
dvtb_initValues();

#endif
