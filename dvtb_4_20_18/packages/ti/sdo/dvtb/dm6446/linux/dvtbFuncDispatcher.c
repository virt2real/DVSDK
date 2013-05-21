/*
 * dvtbFuncDispatcher.c
 *
 * Func Dispatcher Functionality
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

#include "dvtbFuncDispatcher.h"
#include "dvtbThread.h"
#include "dvtbUtils.h"

//XDM 0.9 Base
#include "dvtbVidCapture.h"
#include "dvtbVidPlay.h"
#include "dvtbAudPlay.h"
#include "dvtbSphCapture.h"
#include "dvtbSphPlay.h"
#include "dvtbAudCapture.h"
#include "dvtbImgDisplay.h"
#include "dvtbImgCapture.h"

//XDM 0.9 Extended
#include "dvtbMP3BasePlay.h"

//XDM 1.0 Base
#include "dvtbVidCapture1.h"
#include "dvtbImgCapture1.h"
#include "dvtbImgDisplay1.h"
#include "dvtbAudCapture1.h"
#include "dvtbAudPlay1.h"
#include "dvtbSphCapture1.h"
#include "dvtbSphPlay1.h"

//XDM 1.0 Extended
#include "dvtbAACHECapture1.h"
#include "dvtbAACLCCapture1.h"
#include "dvtbMP3BasePlay1.h"

//XDM 1.2 Base
#include "dvtbVidPlay2.h"

//Application Specific
#include "dvtbVidLoopback1.h"

typedef enum dvevmStCmd
{
  VIDENC,
  VIDDEC,
  AUDDEC,
  SPHENC,
  SPHDEC,
  MP3BASEDEC,
  VIDENC1,
  IMGENC1,
  IMGDEC1,
  AUDENC1,
  AUDDEC1,
  SPHENC1,
  SPHDEC1,
  AACHEENC1,
  AACLCENC1,
  MP3BASEDEC1,
  VIDDEC2,
  VIDLOOPBACK1,
  AUDENC,
  IMGDEC,
  IMGENC,
  MAX_FUNC_CMDS
} DvevmStCmd;

typedef void * (* DvevmStFuncDispatcher)(void *T);

typedef struct
{
  char key[MAX_KEY_SIZE];
  DvevmStFuncDispatcher dptr;
} DvevmStFuncInfo;

static DvevmStFuncInfo dvevmStFuncCmdInfo[MAX_FUNC_CMDS] =
{
  {"videnc", (DvevmStFuncDispatcher) dvtb_VidEncCapture},
  {"viddec", (DvevmStFuncDispatcher) dvtb_VidDecPlay},
  {"auddec", (DvevmStFuncDispatcher) dvtb_AudDecPlay},
  {"mp3basedec", (DvevmStFuncDispatcher) dvtb_Mp3baseDecPlay},
  {"sphenc", (DvevmStFuncDispatcher) dvtb_SphEncCapture},
  {"sphdec", (DvevmStFuncDispatcher) dvtb_SphDecPlay},
  {"videnc1", (DvevmStFuncDispatcher) dvtb_VidEnc1Capture},
  {"imgenc1", (DvevmStFuncDispatcher) dvtb_ImgEnc1Capture},
  {"imgdec1", (DvevmStFuncDispatcher) dvtb_ImgDec1Display},
  {"audenc1", (DvevmStFuncDispatcher) dvtb_AudEnc1Capture},
  {"auddec1", (DvevmStFuncDispatcher) dvtb_AudDec1Play},
  {"mp3basedec1", (DvevmStFuncDispatcher) dvtb_Mp3baseDec1Play},
  {"sphenc1", (DvevmStFuncDispatcher) dvtb_SphEnc1Capture},
  {"sphdec1", (DvevmStFuncDispatcher) dvtb_SphDec1Play},
  {"aacheenc1", (DvevmStFuncDispatcher) dvtb_AacheEnc1Capture},
  {"aaclcenc1", (DvevmStFuncDispatcher) dvtb_AaclcEnc1Capture},
  {"viddec2", (DvevmStFuncDispatcher) dvtb_VidDec2Play},
  {"vidloopback1", (DvevmStFuncDispatcher) dvtb_VidLoopback1},
  {"audenc", (DvevmStFuncDispatcher) dvtb_AudEncCapture},
  {"imgdec", (DvevmStFuncDispatcher) dvtb_ImgDecDisplay},
  {"imgenc", (DvevmStFuncDispatcher) dvtb_ImgEncCapture},
};

DvevmStRetCode
dvtb_funcExecute(int numTokens, char **tokens)
{
  DvevmStRetCode retval=DVEVM_ST_FAIL;
  int i=0;
  unsigned int thIndex=0;
  int j=0;
  char *sourceFile=NULL;
  char *targetFile=NULL;
  DvevmStBool noAlgorithm=DVEVM_ST_FALSE;

  ASSERT(numTokens >= 1);

  for (i=0; i<MAX_FUNC_CMDS; i++)
  {
    if (0 == strcmp(*tokens, dvevmStFuncCmdInfo[i].key))
    {
      if (NULL == dvevmStFuncCmdInfo[i].dptr)
        return DVEVM_ST_NOTSUPPORTED;

      /* First token would be 'key'. Start from next token */

      for (j=1;j<numTokens;j++)
      {
        if (0 == strcmp(tokens[j], NODSP_OPTION))
          noAlgorithm=DVEVM_ST_TRUE;
        else if (0 == strcmp(tokens[j], SOURCE_FILE_OPTION))
          sourceFile=tokens[++j];
        else if (0 == strcmp(tokens[j], TARGET_FILE_OPTION))
          targetFile = tokens[++j];
      }

      if ((0 != strcmp(tokens[0], "vidloopback1")) && !sourceFile && !targetFile)
      {
        SYS_ERROR("Source/Target file has to be given as argument\n");
        return DVEVM_ST_FAIL;
      }

      SYS_OUT("Starting Thread for command <%s>\n", *tokens);
      if (DVEVM_ST_FAIL == dvtb_getFreeThr(&thIndex))
      {
        SYS_ERROR("MAX number of threads already started\n");
        return DVEVM_ST_FAIL;
      }

      TH[thIndex].useAlgorithm = !noAlgorithm;

      if(sourceFile)
      {
        if(targetFile)
        {
          if(strcmp(sourceFile, targetFile) == 0)
          {
            SYS_ERROR("Input & Output file names are same\n");
            return DVEVM_ST_FAIL;
          }
        }
      }

      TH[thIndex].sourceFp = NULL;
      if (sourceFile)
      {
        if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp, sourceFile, "r"))
        {
          SYS_ERROR("Unable to open source file : %s\n", sourceFile);
          dvtb_freeThr(&TH[thIndex]);
          return DVEVM_ST_FAIL;
        }

        fseek(TH[thIndex].sourceFp, 0, SEEK_END);
        if(ftell(TH[thIndex].sourceFp) <= 0 )
        {
          SYS_ERROR("Input file has nothing to process\n");
          if (TH[thIndex].sourceFp)
        	  fclose(TH[thIndex].sourceFp);
          dvtb_freeThr(&TH[thIndex]);
          return DVEVM_ST_FAIL;
        }
        else
        {
          rewind(TH[thIndex].sourceFp);
        }
      }

      TH[thIndex].targetFp = NULL;
      if (targetFile)
      {
        if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].targetFp, targetFile, "w"))
        {
          SYS_ERROR("Unable to open target file : %s\n", targetFile);
          if (TH[thIndex].sourceFp)
        	  fclose(TH[thIndex].sourceFp);
          dvtb_freeThr(&TH[thIndex]);
          return DVEVM_ST_FAIL;
        }
      }

      if ((0 != strcmp(tokens[0], "vidloopback1")) && !TH[thIndex].sourceFp && !TH[thIndex].targetFp)
      {
        SYS_ERROR("Both source and target files cannot be opened\n");
        dvtb_freeThr(&TH[thIndex]);
        return DVEVM_ST_FAIL;
      }

      retval = dvtb_threadCreate(&TH[thIndex].thrId, &TH[thIndex].attr, dvevmStFuncCmdInfo[i].dptr, &TH[thIndex]);

      if (DVEVM_ST_FAIL == retval)
      {
        SYS_ERROR("Unable to create a thread\n");
        dvtb_freeThr(&TH[thIndex]);
      }
      else
        retval = DVEVM_ST_PNDG;

      SYS_DEBUG("Returning %d\n", retval);
      return retval;
    }
  }

  SYS_ERROR("Command <%s> invalid\n", *tokens);
  return retval;
}
