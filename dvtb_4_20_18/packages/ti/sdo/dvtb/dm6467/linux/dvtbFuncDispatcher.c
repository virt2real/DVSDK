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
#include "dvtbAudPlay.h"
#include "dvtbSphCapture.h"
#include "dvtbSphPlay.h"

//XDM 0.9 Extended
#include "dvtbAACCapture.h"

//XDM 1.0 Base
#include "dvtbVidCapture1.h"
#include "dvtbMP3BasePlay1.h"
#include "dvtbAudCapture1.h"
#include "dvtbAudPlay1.h"
#include "dvtbSphCapture1.h"
#include "dvtbSphPlay1.h"
#include "dvtbImgDisplay1.h"
#include "dvtbImgCapture1.h"

//XDM 1.0 Extended
#include "dvtbH264Capture1.h"
#include "dvtbH264fhdCapture1.h"
#include "dvtbMpeg4Capture1.h"
#include "dvtbAACHEPlay1.h"
#include "dvtbJPEGDisplay1.h"
#include "dvtbJPEGCapture1.h"

//XDM 1.2 Base
#include "dvtbVidPlay2.h"

//XDM 1.2 Extended
#include "dvtbMpeg2Play2.h"
#include "dvtbMpeg4Play2.h"

//XDM 1.2 Extended
#ifdef _DVTB_H264DEC_
#include "dvtbH264Play2.h"
#endif

#ifdef _DVTB_H2641080p60VDEC_
#include "dvtbH2641080pPlay2.h"
#endif

//Application Specific
#include "dvtbVidLoopback1.h"

#ifdef _DVTB_NONTSPA_
//XDM 1.0 Extended
#include "dvtbAACHECapture1.h"
#include "dvtbAC3Play1.h"
#endif

typedef enum dvevmStCmd
{
	AUDDEC,
	SPHENC,
	SPHDEC,
	AACENC,
	VIDENC1,
	AUDENC1,
	AUDDEC1,
	SPHENC1,
	SPHDEC1,
	H264ENC1,
	H264FHDENC1,
	AACHEENC1,
	AACHEDEC1,
	AC3DEC1,
	VIDDEC2,
	H264DEC2,
	H2641080PDEC2,
	MPEG2DEC2,
	MPEG4DEC2,
	IMGDEC1,
	IMGENC1,
	JPEGDEC1,
	JPEGENC1,
	MPEG4ENC1,
	VIDLOOPBACK1,
	MP3BASEDEC1,
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
	{ "auddec", (DvevmStFuncDispatcher) dvtb_AudDecPlay },
	{ "sphenc", (DvevmStFuncDispatcher) dvtb_SphEncCapture },
	{ "sphdec", (DvevmStFuncDispatcher) dvtb_SphDecPlay },
	{ "aacenc", (DvevmStFuncDispatcher) dvtb_AacEncCapture },
	{ "mp3basedec1", (DvevmStFuncDispatcher) dvtb_Mp3baseDec1Play},
	{ "videnc1", (DvevmStFuncDispatcher) dvtb_VidEnc1Capture },
	{ "audenc1", (DvevmStFuncDispatcher) dvtb_AudEnc1Capture },
	{ "auddec1", (DvevmStFuncDispatcher) dvtb_Auddec1Play },
	{ "sphenc1", (DvevmStFuncDispatcher) dvtb_SphEnc1Capture },
	{ "sphdec1", (DvevmStFuncDispatcher) dvtb_SphDec1Play },
	{ "imgdec1", (DvevmStFuncDispatcher) dvtb_ImgDec1Display},
	{ "imgenc1", (DvevmStFuncDispatcher) dvtb_ImgEnc1Capture},
	{ "jpegdec1", (DvevmStFuncDispatcher) dvtb_JpegDec1Display},
	{ "h264enc1", (DvevmStFuncDispatcher) dvtb_H264Enc1Capture },	
	{ "h264fhdenc1", (DvevmStFuncDispatcher) dvtb_H264fhdEnc1Capture },
	{ "mpeg4enc1", (DvevmStFuncDispatcher) dvtb_MPEG4Enc1Capture },
	{ "aachedec1", (DvevmStFuncDispatcher)dvtb_AacheDec1Play},
	{ "viddec2", (DvevmStFuncDispatcher) dvtb_VidDec2Play },
#ifdef _DVTB_H264DEC_
	{ "h264dec2", (DvevmStFuncDispatcher) dvtb_H264Dec2Play },
#endif
#ifdef _DVTB_H2641080p60VDEC_
	{ "h2641080pdec2", (DvevmStFuncDispatcher) dvtb_H2641080pDec2Play },
#endif
	{ "mpeg2dec2", (DvevmStFuncDispatcher) dvtb_Mpeg2Dec2Play },
	{ "mpeg4dec2", (DvevmStFuncDispatcher) dvtb_Mpeg4Dec2Play },
	{"jpegenc1", (DvevmStFuncDispatcher) dvtb_JpegEnc1Capture },
	{ "vidloopback1", (DvevmStFuncDispatcher) dvtb_VidLoopback1 },

#ifdef _DVTB_NONTSPA_
	{ "aacheenc1", (DvevmStFuncDispatcher) dvtb_AacheEnc1Capture },	
	{ "ac3dec1", (DvevmStFuncDispatcher)dvtb_AC3Dec1Play},
#endif
};

DvevmStRetCode
dvtb_funcExecute(int numTokens, char **tokens)
{
	int i = 0, j = 0;
	char *sourceFile = NULL, *targetFile = NULL;
	unsigned int thIndex = 0;

	DvevmStBool noAlgorithm = DVEVM_ST_FALSE;
	DvevmStRetCode retval = DVEVM_ST_FAIL;

	ASSERT(numTokens >= 1);

	for (i = 0; i < MAX_FUNC_CMDS; i++)
	{
		if (0 == strcmp(*tokens, dvevmStFuncCmdInfo[i].key))
		{
			if (NULL == dvevmStFuncCmdInfo[i].dptr)
				return DVEVM_ST_NOTSUPPORTED;

			/* First token would be 'key'. Start from next token */

			for (j = 1; j < numTokens; j++)
			{
				if (0 == strcmp(tokens[j], NODSP_OPTION))
					noAlgorithm = DVEVM_ST_TRUE;
				else if (0 == strcmp(tokens[j], SOURCE_FILE_OPTION))
					sourceFile = tokens[++j];
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

			if (sourceFile)
			{
				if (targetFile)
				{
					if (strcmp(sourceFile, targetFile) == 0)
					{
						SYS_ERROR("Input & Output file names are same\n");
						return DVEVM_ST_FAIL;
					}
				}
			}

			TH[thIndex].sourceFp = NULL;
			TH[thIndex].targetFp = NULL;
			if (sourceFile)
			{
				if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp, sourceFile, "rb"))
				{
					SYS_ERROR("Unable to open source file : %s\n", sourceFile);
					dvtb_freeThr(&TH[thIndex]);
					return DVEVM_ST_FAIL;
				}
			}

			if (targetFile)
			{
				if(DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].targetFp, targetFile, "wb"))
				{
					SYS_ERROR("Unable to open target file : %s\n", targetFile);
					if(NULL != TH[thIndex].sourceFp)
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

				if(NULL != TH[thIndex].sourceFp)
					fclose(TH[thIndex].sourceFp);

				if(NULL != TH[thIndex].targetFp)
					fclose(TH[thIndex].targetFp);

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
