/*
 * dvtbApisDispatcher.c
 *
 * DVTB APIs Dispatcher
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

#include "dvtbApisDispatcher.h"
#include "dvtbParam.h"
#include "dvtbEngine.h"

//XDM 0.9 Base
#include "dvtbSphDec.h"
#include "dvtbSphEnc.h"
#include "dvtbVidDec.h"
#include "dvtbVidEnc.h"
#include "dvtbImgEnc.h"
#include "dvtbImgDec.h"


DvevmStApiTable *API = NULL;
unsigned int DVEVM_CE_NUM=0;

DvevmStRetCode
dvtb_apisInit()
{
  DvevmStApiTable dvevmStApiArr[] =
  {
    /*Api for Codec Engine*/
    {"engine", "runtime", (DvevmStApiFunction) dvtb_ceRuntimeInit, &G->eng},
    {"engine", "open", (DvevmStApiFunction) dvtb_ceOpen, &G->eng},
    {"engine", "getmem", (DvevmStApiFunction) dvtb_ceMem, &G->eng},
    {"engine", "getcpu", (DvevmStApiFunction) dvtb_ceCpu, &G->eng},
    {"engine", "close", (DvevmStApiFunction) dvtb_ceClose, &G->eng},

    /* Api for Video Encoder */
    {"videnc", "create", (DvevmStApiFunction) dvtb_vidEncInit, &G->venc},
    {"videnc", "process", (DvevmStApiFunction) dvtb_vidEncEncode, &G->venc},
    {"videnc", "control", (DvevmStApiFunction) dvtb_vidEncControl, &G->venc},
    {"videnc", "delete", (DvevmStApiFunction) dvtb_vidEncClose, &G->venc},

    /* Api for Video Decoder */
    {"viddec", "create", (DvevmStApiFunction) dvtb_vidDecInit, &G->vdec},
    {"viddec", "process", (DvevmStApiFunction) dvtb_vidDecDecode, &G->vdec},
    {"viddec", "control", (DvevmStApiFunction) dvtb_vidDecControl, &G->vdec},
    {"viddec", "delete", (DvevmStApiFunction) dvtb_vidDecClose, &G->vdec},

    /* Api for Speech Encoder */
    {"sphenc", "create", (DvevmStApiFunction) dvtb_sphEncInit, &G->senc},
    {"sphenc", "process", (DvevmStApiFunction) dvtb_sphEncEncode, &G->senc},
    {"sphenc", "control", (DvevmStApiFunction) dvtb_sphEncControl, &G->senc},
    {"sphenc", "delete", (DvevmStApiFunction) dvtb_sphEncClose, &G->senc},

    /* Api for Speech Decoder */
    {"sphdec", "create", (DvevmStApiFunction) dvtb_sphDecInit, &G->sdec},
    {"sphdec", "process", (DvevmStApiFunction) dvtb_sphDecDecode, &G->sdec},
    {"sphdec", "control", (DvevmStApiFunction) dvtb_sphDecControl, &G->sdec},
    {"sphdec", "delete", (DvevmStApiFunction) dvtb_sphDecClose, &G->sdec},

    /* Api for Image Decoder */
    {"imgdec", "create", (DvevmStApiFunction) dvtb_imgDecInit, &G->idec},
    {"imgdec", "process", (DvevmStApiFunction) dvtb_imgDecDecode, &G->idec},
    {"imgdec", "control", (DvevmStApiFunction) dvtb_imgDecControl, &G->idec},
    {"imgdec", "delete", (DvevmStApiFunction) dvtb_imgDecClose, &G->idec},

    /* Api for Image Encoder */
    {"imgenc", "create", (DvevmStApiFunction) dvtb_imgEncInit, &G->ienc},
    {"imgenc", "process", (DvevmStApiFunction) dvtb_imgEncEncode, &G->ienc},
    {"imgenc", "control", (DvevmStApiFunction) dvtb_imgEncControl, &G->ienc},
    {"imgenc", "delete", (DvevmStApiFunction) dvtb_imgEncClose, &G->ienc}
  };

  DVEVM_CE_NUM = sizeof(dvevmStApiArr) / sizeof(DvevmStApiTable);
  API = (DvevmStApiTable *)calloc( DVEVM_CE_NUM, sizeof(DvevmStApiTable) );
  if (API != NULL)
  {
    memcpy(API, dvevmStApiArr, DVEVM_CE_NUM *sizeof(DvevmStApiTable) );
  }

  return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_apisExecute(int numTokens, char **tokens)
{
  int i=0;

  DvevmStRetCode retval=DVEVM_ST_FAIL;

  if((numTokens != 2))
  {
    SYS_ERROR("\nUsage: apis <engine|sphenc|sphdec|videnc|viddec|imgdec|imgenc> \n");
  }
  else
  {
    for (i=0; i< DVEVM_CE_NUM; i++)
    {
      if (0 == strcmp(*tokens, API[i].codecName))
      {
        if( 0 == strcmp(tokens[1],API[i].apiName))
          retval = API[i].apiptr(API[i].param);
      }
    }
  }

  return retval;
}
