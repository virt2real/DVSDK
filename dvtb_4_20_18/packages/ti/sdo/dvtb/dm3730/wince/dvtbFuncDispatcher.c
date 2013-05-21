/*
 * dvtbFuncDispatcher.c
 *
 * Func Dispatcher
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
#include "dvtbThreadManager.h"
#include "dvtbUtils.h"
//XDM 1.0 Base
#include "dvtbAudPlay1.h"
#include "dvtbMP3BasePlay1.h"
#include "dvtbImgDisplay1.h"
#include "dvtbVidCapture1.h"
#include "dvtbImgCapture1.h"
#include "dvtbSphCapture1.h"
#include "dvtbSphPlay1.h"

//XDM 1.0 Extended
#include "dvtbJPEGDisplay1.h"

//XDM 1.2 Base
#include "dvtbVidPlay2.h"

//Application Specific
//#include "dvtbPwrManagerHan.h"
//#include "dvtbAudLoopback.h"
#include "dvtbVidLoopback1.h"


typedef enum dvtbCmd
{
  AUDDEC1,
  MP3BASEDEC1,
  AUDENC,
  IMGDEC1,
  VIDDEC2,
  SPHENC1,
  SPHDEC1,
  VIDENC1,
  IMGENC1,
  PWRMANAGER,
  AUDLOOPBACK,
  JPEGDEC1,
  VIDLOOPBACK1,
  MAX_FUNC_CMDS
} dvtbCmd;

// typedef DvevmStRetCode (* DvevmStFuncDispatcher)(DvevmStThreadInfo *T);
typedef void * (* DvevmStFuncDispatcher)(void *T);

typedef struct
{
  char key[MAX_KEY_SIZE];
  DvevmStFuncDispatcher dptr;
} dvtbFuncInfo;

static dvtbFuncInfo dvtbFuncCmdInfo[MAX_FUNC_CMDS] =
{
//  {"audloopback", (DvevmStFuncDispatcher) dvtb_AudLoopback},
  {"auddec1", (DvevmStFuncDispatcher) dvtb_AudDec1Play},
  {"mp3basedec1", (DvevmStFuncDispatcher) dvtb_Mp3baseDec1Play},
  {"imgdec1", (DvevmStFuncDispatcher) dvtb_ImgDec1Display},
  {"viddec2", (DvevmStFuncDispatcher) dvtb_VidDec2Play},
  {"sphenc1", (DvevmStFuncDispatcher) dvtb_SphEnc1Capture},
  {"sphdec1", (DvevmStFuncDispatcher) dvtb_SphDec1Play},
  {"videnc1", (DvevmStFuncDispatcher) dvtb_VidEnc1Capture},
  {"imgenc1", (DvevmStFuncDispatcher) dvtb_ImgEnc1Capture},
  {"jpegdec1", (DvevmStFuncDispatcher) dvtb_JpegDec1Display},
//  {"pwrmanager", (DvevmStFuncDispatcher) dvtb_PwrManager},
  {"vidloopback1", (DvevmStFuncDispatcher) dvtb_VidLoopback1},
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

  DVTBASSERT(numTokens >= 1);

  for (i=0; i<MAX_FUNC_CMDS; i++)
  {
    if (0 == strcmp(*tokens, dvtbFuncCmdInfo[i].key))
    {
      if (NULL == dvtbFuncCmdInfo[i].dptr)
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
#if 0
      if (!sourceFile && !targetFile)
      {
        SYS_ERROR("Source/Target file has to be given as argument\n");
        return DVEVM_ST_FAIL;
      }
#endif
      SYS_OUT("Starting Thread for command <%s>\n", *tokens);
      if (DVEVM_ST_FAIL == dvtb_getFreeThread(&thIndex))
      {
        SYS_ERROR("MAX number of threads already started\n");
        return DVEVM_ST_FAIL;
      }

      TH[thIndex].useAlgorithm = !noAlgorithm;
      TH[thIndex].sourceFp = NULL;

      if (sourceFile)
      	if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp, sourceFile, "rb"))
        {
          SYS_ERROR("Unable to open source file : %s\n", sourceFile);
          TH[thIndex].inUse = DVEVM_ST_STATUS_AVAILABLE;
          return DVEVM_ST_FAIL;
        }

       TH[thIndex].targetFp = NULL;
      if (targetFile)
        if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].targetFp, targetFile, "wb"))
        {
          SYS_ERROR("Unable to open target file : %s\n", targetFile);
          TH[thIndex].inUse = DVEVM_ST_STATUS_AVAILABLE;
          return DVEVM_ST_FAIL;
        }

#if 0
      if (!TH[thIndex].sourceFp && !TH[thIndex].targetFp)
      {
        SYS_ERROR("Both source and target files cannot be opened\n");
        dvtb_freeThread(&TH[thIndex]);
        return DVEVM_ST_FAIL;
      }
#endif
#if 0
      if (G->eng.enableTrace && !G->eng.traceOn)
      {
        //TraceUtil_start(G->eng.name);
        //G->eng.traceOn = TRUE;
        //TH[thIndex].traceOn = TRUE;
      }
#endif
	TH[thIndex].thrParams.arg = (IArg)&TH[thIndex];
	TH[thIndex].thrParams.name = dvtbFuncCmdInfo[i].key;
	TH[thIndex].thrParams.priority = Thread_Priority_ABOVE_NORMAL;

	retval = dvtb_createThread((Thread_RunFxn)dvtbFuncCmdInfo[i].dptr, &TH[thIndex].thrParams, &TH[thIndex].thrHandle);

	if (DVEVM_ST_FAIL == retval)
	{
		SYS_ERROR("Unable to create a thread\n");
		TH[thIndex].inUse = DVEVM_ST_STATUS_AVAILABLE;
	}
	else
	{
		retval = DVEVM_ST_PNDG;
		TH[thIndex].inUse = DVEVM_ST_STATUS_RUNNING;
	}

      SYS_DEBUG("Returning %d\n", retval);
      return retval;
    }
  }

  SYS_ERROR("Command <%s> invalid\n", *tokens);
  return retval;
}
