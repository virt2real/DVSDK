/*
 * dvtbApisDispatcher.c
 *
 * APIs Dispatcher
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

//XDM 1.0 Base
#include "dvtbAudDec1.h"
#if 0
#include "dvtbMP3BaseDec1.h"
#include "dvtbImgDec1.h"
#endif
#include "dvtbVidEnc1.h"
#if 0
#include "dvtbImgEnc1.h"
#include "dvtbSphEnc1.h"
#include "dvtbSphDec1.h"


//XDM 1.0 Extended
#include "dvtbJPEGDec1.h"
#endif
//XDM 1.2 Base
#include "dvtbVidDec2.h"


DvevmStApiTable *API = NULL;
unsigned int DVEVM_CE_NUM=0;

DvevmStRetCode
dvtb_apisInit()
{
  DvevmStApiTable dvtbApiArr[] =
  {
    /*Api for Codec Engine*/
    {"engine", "runtime", (DvevmStApiFunction) dvtb_ceRuntimeInit, &G->eng},
    {"engine", "open", (DvevmStApiFunction) dvtb_ceOpen, &G->eng},
    {"engine", "getmem", (DvevmStApiFunction) dvtb_ceMem, &G->eng},
    {"engine", "getcpu", (DvevmStApiFunction) dvtb_ceCpu, &G->eng},
    {"engine", "close", (DvevmStApiFunction) dvtb_ceClose, &G->eng},
    /************************************************************************************************/
    /***********     XDM 0.9 Base     ***************************************************************/
    /************************************************************************************************/


    /************************************************************************************************/

    /************************************************************************************************/
    /***********     XDM 1.0 Base     ***************************************************************/
    /************************************************************************************************/
    /* Api for Video Encoder XDM 1.0*/
    {"videnc1", "create", (DvevmStApiFunction) dvtb_vidEnc1Init, &G->venc1},
    {"videnc1", "process", (DvevmStApiFunction) dvtb_vidEnc1Encode, &G->venc1},
    {"videnc1", "control", (DvevmStApiFunction) dvtb_vidEnc1Control, &G->venc1},
    {"videnc1", "delete", (DvevmStApiFunction) dvtb_vidEnc1Close, &G->venc1},

    /* Api for image Decoder XDM 1.0*/
    {"imgdec1", "create", (DvevmStApiFunction) dvtb_imgDec1Init, &G->idec1},
    {"imgdec1", "process", (DvevmStApiFunction) dvtb_imgDec1Decode, &G->idec1},
    {"imgdec1", "control", (DvevmStApiFunction) dvtb_imgDec1Control, &G->idec1},
    {"imgdec1", "delete", (DvevmStApiFunction) dvtb_imgDec1Close, &G->idec1},

    /* Api for Audio1 Decoder */
    {"auddec1", "create", (DvevmStApiFunction) dvtb_audDec1Init, &G->adec1},
    {"auddec1", "process", (DvevmStApiFunction) dvtb_audDec1Decode, &G->adec1},
    {"auddec1", "control", (DvevmStApiFunction) dvtb_audDec1Control, &G->adec1},
    {"auddec1", "delete", (DvevmStApiFunction) dvtb_audDec1Close, &G->adec1},

    /* Api for Image Encoder XDM 1.0*/
    {"imgenc1", "create", (DvevmStApiFunction) dvtb_imgEnc1Init, &G->ienc1},
    {"imgenc1", "process", (DvevmStApiFunction) dvtb_imgEnc1Encode, &G->ienc1},
    {"imgenc1", "control", (DvevmStApiFunction) dvtb_imgEnc1Control, &G->ienc1},
    {"imgenc1", "delete", (DvevmStApiFunction) dvtb_imgEnc1Close, &G->ienc1},
    /* Api for Audio1 Decoder */
    {"mp3basedec1", "create", (DvevmStApiFunction) dvtb_mp3baseDec1Init, &G->mp3basedec1},
    {"mp3basedec1", "process", (DvevmStApiFunction) dvtb_mp3baseDec1Decode, &G->mp3basedec1},
    {"mp3basedec1", "control", (DvevmStApiFunction) dvtb_mp3baseDec1Control, &G->mp3basedec1},
    {"mp3basedec1", "delete", (DvevmStApiFunction) dvtb_mp3baseDec1Close, &G->mp3basedec1},
    /* Api for Speech Encoder */
    {"sphenc1", "create", (DvevmStApiFunction) dvtb_sphEnc1Init, &G->senc1},
    {"sphenc1", "process", (DvevmStApiFunction) dvtb_sphEnc1Encode,&G->senc1},
    {"sphenc1", "control", (DvevmStApiFunction) dvtb_sphEnc1Control,&G->senc1},
    {"sphenc1", "delete", (DvevmStApiFunction) dvtb_sphEnc1Close, &G->senc1},
    /* Api for Speech Decoder */
    {"sphdec1", "create", (DvevmStApiFunction) dvtb_sphDec1Init, &G->sdec1},
    {"sphdec1", "process", (DvevmStApiFunction) dvtb_sphDec1Decode, &G->sdec1},
    {"sphdec1", "control", (DvevmStApiFunction) dvtb_sphDec1Control, &G->sdec1},
    {"sphdec1", "delete", (DvevmStApiFunction) dvtb_sphDec1Close, &G->sdec1},
    /************************************************************************************************/

    /************************************************************************************************/
    /***********     XDM 1.0 Extended     ***********************************************************/
    /************************************************************************************************/
    /* Api for jpeg Decoder XDM1.0 */
    {"jpegdec1", "create", (DvevmStApiFunction) dvtb_jpegDec1Init, &G->jpegdec1},
    {"jpegdec1", "process", (DvevmStApiFunction) dvtb_jpegDec1Decode, &G->jpegdec1},
    {"jpegdec1", "control", (DvevmStApiFunction) dvtb_jpegDec1Control, &G->jpegdec1},
    {"jpegdec1", "delete", (DvevmStApiFunction) dvtb_jpegDec1Close, &G->jpegdec1},
    /************************************************************************************************/

    /************************************************************************************************/
    /***********     XDM 1.2 Base     ***************************************************************/
    /************************************************************************************************/
    /* Api for Video Decoder XDM 1.2*/
    {"viddec2", "create", (DvevmStApiFunction) dvtb_vidDec2Init, &G->viddec2},
    {"viddec2", "process", (DvevmStApiFunction) dvtb_vidDec2Decode, &G->viddec2},
    {"viddec2", "control", (DvevmStApiFunction) dvtb_vidDec2Control, &G->viddec2},
    {"viddec2", "delete", (DvevmStApiFunction) dvtb_vidDec2Close, &G->viddec2}
    /************************************************************************************************/

  };

  DVEVM_CE_NUM = sizeof(dvtbApiArr) / sizeof(DvevmStApiTable);
  API = (DvevmStApiTable *)calloc( DVEVM_CE_NUM, sizeof(DvevmStApiTable) );
  if (API != NULL)
  {
    memcpy(API, dvtbApiArr, DVEVM_CE_NUM *sizeof(DvevmStApiTable) );
  }

  return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_apisExecute(int numTokens, char **tokens)
{
  unsigned int i=0;

  DvevmStRetCode retval=DVEVM_ST_FAIL;

  if((numTokens != 2))
  {
    SYS_ERROR("\nUsage: apis <engine|auddec|sphenc|sphdec|videnc|viddec> \n");
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
