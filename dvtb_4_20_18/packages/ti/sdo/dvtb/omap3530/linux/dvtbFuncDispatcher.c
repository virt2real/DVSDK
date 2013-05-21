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
#include "dvtbThread.h"
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
#include "dvtbH264Capture1.h"
#include "dvtbMPEG4SPCapture1.h"
#include "dvtbAACHEPlay1.h"
#include "dvtbJPEGCapture1.h"

//XDM 1.2 Base
#include "dvtbVidPlay2.h"

//XDM 1.2 Extended
#include "dvtbH264Play2.h"
#include "dvtbMPEG4SPPlay2.h"
#include "dvtbMpeg2Play2.h"

//Application Specific
#include "dvtbPwrManagerHan.h"
#include "dvtbAudLoopback.h"
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
  H264DEC2,
  H264ENC1,
  MPEG4ENC1,	
  MPEG4DEC2,
  MPEG2DEC2,
  AACHEDEC1,
  JPEGENC1,
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
  {"audloopback", (DvevmStFuncDispatcher) dvtb_AudLoopback},
  {"auddec1", (DvevmStFuncDispatcher) dvtb_AudDec1Play},
  {"mp3basedec1", (DvevmStFuncDispatcher) dvtb_Mp3baseDec1Play},
  {"imgdec1", (DvevmStFuncDispatcher) dvtb_ImgDec1Display},
  {"viddec2", (DvevmStFuncDispatcher) dvtb_VidDec2Play},
  {"sphenc1", (DvevmStFuncDispatcher) dvtb_SphEnc1Capture},
  {"sphdec1", (DvevmStFuncDispatcher) dvtb_SphDec1Play},
  {"videnc1", (DvevmStFuncDispatcher) dvtb_VidEnc1Capture},
  {"imgenc1", (DvevmStFuncDispatcher) dvtb_ImgEnc1Capture},
  {"h264enc1", (DvevmStFuncDispatcher) dvtb_H264Enc1Capture },
  {"mpeg4spenc1", (DvevmStFuncDispatcher) dvtb_Mpeg4spEnc1Capture },
  {"jpegdec1", (DvevmStFuncDispatcher) dvtb_JpegDec1Display},
  {"pwrmanager", (DvevmStFuncDispatcher) dvtb_PwrManager},
  {"h264dec2", (DvevmStFuncDispatcher) dvtb_H264Dec2Play },
  {"mpeg4spdec2", (DvevmStFuncDispatcher) dvtb_Mpeg4spDec2Play },
  {"mpeg2dec2", (DvevmStFuncDispatcher) dvtb_Mpeg2Dec2Play },
  {"aachedec1", (DvevmStFuncDispatcher)dvtb_AacheDec1Play},
  {"jpegenc1", (DvevmStFuncDispatcher) dvtb_JpegEnc1Capture },
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

  ASSERT(numTokens >= 1);

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
      if (DVEVM_ST_FAIL == dvtb_getFreeThr(&thIndex))
      {
        SYS_ERROR("MAX number of threads already started\n");
        return DVEVM_ST_FAIL;
      }

      TH[thIndex].useAlgorithm = !noAlgorithm;
      TH[thIndex].sourceFp = NULL;
      if (sourceFile)
        if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp, sourceFile, "r"))
        {
          SYS_ERROR("Unable to open source file : %s\n", sourceFile);
          dvtb_freeThr(&TH[thIndex]);
          return DVEVM_ST_FAIL;
        }

      TH[thIndex].targetFp = NULL;
      if (targetFile)
        if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].targetFp, targetFile, "w"))
        {
          SYS_ERROR("Unable to open target file : %s\n", targetFile);
          return DVEVM_ST_FAIL;
        }

#if 0
      if (!TH[thIndex].sourceFp && !TH[thIndex].targetFp)
      {
        SYS_ERROR("Both source and target files cannot be opened\n");
        dvtb_freeThr(&TH[thIndex]);
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
      retval = dvtb_threadCreate(&TH[thIndex].thrId, &TH[thIndex].attr, dvtbFuncCmdInfo[i].dptr, &TH[thIndex]);

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
