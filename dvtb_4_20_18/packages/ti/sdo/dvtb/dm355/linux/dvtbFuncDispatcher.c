/*
 * dvtbFuncDispatcher.c
 *
 * DVTB Func Dispatcher
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
#include "dvtbSphCapture.h"
#include "dvtbSphPlay.h"

//XDM 1.0 Base
#include "dvtbVidCapture1.h"
#include "dvtbImgCapture1.h"
#include "dvtbImgDisplay1.h"
#include "dvtbSphCapture1.h"
#include "dvtbSphPlay1.h"

//XDM 1.0 Extended
#include "dvtbMPEG4SPCapture1.h"
#include "dvtbJPEGCapture1.h"
#include "dvtbJPEGDisplay1.h"

//XDM 1.2 Base
#include "dvtbVidPlay2.h"

//XDM 1.2 Extended
#include "dvtbMPEG4SPPlay2.h"

//Application Specific
#include "dvtbIPNCUC0.h"
#include "dvtbIPNCUC1.h"
#include "dvtbIPNCUC2.h"
#include "dvtbDVRUC0.h"
#include "dvtbDVREnc.h"
#include "dvtbDVREncDec.h"

typedef enum dvevmStCmd
{
	SPHENC,
	SPHDEC,
	VIDENC1,
	IMGENC1,
	IMGDEC1,
	MPEG4SPENC1,
	JPEGENC1,
	JPEGDEC1,
	VIDDEC2,
	SPHENC1,
	SPHDEC1,
	MPEG4SPDEC2,
	IPNCUC0,
	IPNCUC1,
	IPNCUC2,
	DVRUC0,
	DVREnc,
	DVREncDec,
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
	{ "sphenc", (DvevmStFuncDispatcher) dvtb_SphEncCapture },
	{ "sphdec", (DvevmStFuncDispatcher) dvtb_SphDecPlay },
	{ "videnc1", (DvevmStFuncDispatcher) dvtb_VidEnc1Capture },
	{ "imgenc1", (DvevmStFuncDispatcher) dvtb_ImgEnc1Capture },
	{ "imgdec1", (DvevmStFuncDispatcher) dvtb_ImgDec1Display },
	{ "mpeg4spenc1", (DvevmStFuncDispatcher) dvtb_Mpeg4spEnc1Capture },
	{ "jpegenc1", (DvevmStFuncDispatcher) dvtb_JpegEnc1Capture },
	{ "jpegdec1", (DvevmStFuncDispatcher) dvtb_JpegDec1Display },
	{ "viddec2", (DvevmStFuncDispatcher) dvtb_VidDec2Play },
	{ "sphenc1", (DvevmStFuncDispatcher) dvtb_SphEnc1Capture },
	{ "sphdec1", (DvevmStFuncDispatcher) dvtb_SphDec1Play },
	{ "mpeg4spdec2", (DvevmStFuncDispatcher) dvtb_Mpeg4spDec2Play },
	{ "IPNCUC0", (DvevmStFuncDispatcher) dvtb_IPNCUC0 },
	{ "IPNCUC1", (DvevmStFuncDispatcher) dvtb_IPNCUC1 },
	{ "IPNCUC2", (DvevmStFuncDispatcher) dvtb_IPNCUC2 },
	{ "DVRUC0", (DvevmStFuncDispatcher) dvtb_DVRUC0 },
	{ "DVREnc", (DvevmStFuncDispatcher) dvtb_DVREnc },
	{ "DVREncDec", (DvevmStFuncDispatcher) dvtb_DVREncDec },
};

//Check whether it is app specific use case
DvevmStRetCode
dvtb_checkAppSpecific(char **tokens)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;

	if ((strcmp(tokens[0], "IPNCUC0") == 0))
		retval = DVEVM_ST_SUCCESS;
	else if ((strcmp(tokens[0], "IPNCUC1") == 0))
		retval = DVEVM_ST_SUCCESS;
	else if ((strcmp(tokens[0], "IPNCUC2") == 0))
		retval = DVEVM_ST_SUCCESS;
	else if ((strcmp(tokens[0], "DVRUC0") == 0))
		retval = DVEVM_ST_SUCCESS;
	else if ((strcmp(tokens[0], "DVRUC1") == 0))
		retval = DVEVM_ST_SUCCESS;
	else if ((strcmp(tokens[0], "DVRUC2") == 0))
		retval = DVEVM_ST_SUCCESS;

	return retval;
}

//Open files for Application specific use cases
DvevmStRetCode
dvtb_openAppSpecificFiles(int numTokens, char **tokens)
{
	int j = 0;
	char *sourceFile1 = NULL, *sourceFile2 = NULL, *sourceFile3 = NULL;
	unsigned int thIndex = 0;

	DvevmStRetCode retval = DVEVM_ST_SUCCESS;
	DvevmStBool noAlgorithm = DVEVM_ST_FALSE;

	ASSERT(numTokens >= 1);

	/* First token would be 'key'. Start from next token */
	for (j = 1; j < numTokens; j++)
	{
		if (0 == strcmp(tokens[j], NODSP_OPTION))
			noAlgorithm = DVEVM_ST_TRUE;
		else if (0 == strcmp(tokens[j], SOURCE_FILE1_OPTION))
			sourceFile1 = tokens[++j];
		else if (0 == strcmp(tokens[j], SOURCE_FILE2_OPTION))
			sourceFile2 = tokens[++j];
		else if (0 == strcmp(tokens[j], SOURCE_FILE3_OPTION))
			sourceFile3 = tokens[++j];
	}

	TH[thIndex].sourceFp1 = NULL;
	TH[thIndex].sourceFp2 = NULL;
	TH[thIndex].sourceFp3 = NULL;

	do
	{
		if ((strcmp(tokens[0], "IPNCUC0") == 0))
		{
			//IPNCUC0 UseCase: Open two source files one each for 720P mpeg4 enc and SIF mpeg4 encode

			TH[thIndex].capture = DVEVM_ST_FALSE;
			if ((NULL == sourceFile1) && (NULL == sourceFile2))
			{
				//set capture option
				TH[thIndex].capture = DVEVM_ST_TRUE;
			}
			else if ((NULL == sourceFile1) || (NULL == sourceFile2))
			{
				//Throw error stating that all three files should be specified.
				SYS_ERROR("Specify two input source files (1-720p YUV, 2-SIF YUV) for this usecase.\n");
				retval = DVEVM_ST_FAIL;
				break;
			}

			SYS_OUT("Starting Thread for command <%s>\n", *tokens);
			SYS_OUT("InputFile1 <%s> InputFile2 <%s>\n", sourceFile1, sourceFile2);
			if (DVEVM_ST_FAIL == dvtb_getFreeThr(&thIndex))
			{
				SYS_ERROR("MAX number of threads already started\n");
				retval = DVEVM_ST_FAIL;
				break;
			}

			TH[thIndex].useAlgorithm = !noAlgorithm;

			if ((NULL != sourceFile1) && (NULL != sourceFile2))
			{
				if (strcmp(sourceFile1, sourceFile2) == 0)
				{
					SYS_ERROR("Input File1 & Input File2 names are same\n");
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (sourceFile1)
			{
				if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp1, sourceFile1, "r"))
				{
					SYS_ERROR("Unable to open source file1 : %s\n", sourceFile1);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (TH[thIndex].sourceFp1)
			{
				fseek(TH[thIndex].sourceFp1, 0, SEEK_END);
				if (ftell(TH[thIndex].sourceFp1) <= 0)
				{
					SYS_ERROR("Input file1 has nothing to process\n");
					fclose(TH[thIndex].sourceFp1);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
				else
				{
					rewind(TH[thIndex].sourceFp1);
				}
			}

			if (sourceFile2)
			{
				if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp2, sourceFile2, "r"))
				{
					SYS_ERROR("*****Unable to open source file2 : %s\n", sourceFile2);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (TH[thIndex].sourceFp2)
			{
				fseek(TH[thIndex].sourceFp2, 0, SEEK_END);
				if (ftell(TH[thIndex].sourceFp2) <= 0)
				{
					SYS_ERROR("Input file2 has nothing to process\n");
					fclose(TH[thIndex].sourceFp2);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
				else
				{
					rewind(TH[thIndex].sourceFp2);
				}
			}
		}
		else if ((strcmp(tokens[0], "IPNCUC1") == 0))
		{
			//IPNCUC1 UseCase: Open three source files one each for D1 mpeg4 enc, SIF mpeg4 encode and D1 JPEG enc

			TH[thIndex].capture = DVEVM_ST_FALSE;
			if ((NULL == sourceFile1) && (NULL == sourceFile2) && (NULL == sourceFile3))
			{
				//set capture option
				TH[thIndex].capture = DVEVM_ST_TRUE;
			}
			else if ((NULL == sourceFile1) || (NULL == sourceFile2) || (NULL == sourceFile3))
			{
				//Throw error stating that all three files should be specified.
				SYS_ERROR("Specify all three input source files for this usecase.\n");
				retval = DVEVM_ST_FAIL;
				break;
			}

			SYS_OUT("Starting Thread for command <%s>\n", *tokens);
			if (DVEVM_ST_FAIL == dvtb_getFreeThr(&thIndex))
			{
				SYS_ERROR("MAX number of threads already started\n");
				retval = DVEVM_ST_FAIL;
				break;
			}

			TH[thIndex].useAlgorithm = !noAlgorithm;

			if ((NULL != sourceFile1) && (NULL != sourceFile2) && (NULL != sourceFile3))
			{
				if (strcmp(sourceFile1, sourceFile2) == 0)
				{
					SYS_ERROR("Input File1 & Input File2 names are same\n");
					retval = DVEVM_ST_FAIL;
					break;
				}
				if (strcmp(sourceFile1, sourceFile3) == 0)
				{
					SYS_ERROR("Input File1 & Input File3 names are same\n");
					retval = DVEVM_ST_FAIL;
					break;
				}
				if (strcmp(sourceFile2, sourceFile3) == 0)
				{
					SYS_ERROR("Input File2 & Input File3 names are same\n");
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (sourceFile1)
			{
				if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp1, sourceFile1, "r"))
				{
					SYS_ERROR("Unable to open source file1 : %s\n", sourceFile1);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (TH[thIndex].sourceFp1)
			{
				fseek(TH[thIndex].sourceFp1, 0, SEEK_END);
				if (ftell(TH[thIndex].sourceFp1) <= 0)
				{
					SYS_ERROR("Input file1 has nothing to process\n");
					fclose(TH[thIndex].sourceFp1);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
				else
				{
					rewind(TH[thIndex].sourceFp1);
				}
			}

			if (sourceFile2)
			{
				if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp2, sourceFile2, "r"))
				{
					SYS_ERROR("Unable to open source file2 : %s\n", sourceFile2);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (TH[thIndex].sourceFp2)
			{
				fseek(TH[thIndex].sourceFp2, 0, SEEK_END);
				if (ftell(TH[thIndex].sourceFp2) <= 0)
				{
					SYS_ERROR("Input file2 has nothing to process\n");
					fclose(TH[thIndex].sourceFp2);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
				else
				{
					rewind(TH[thIndex].sourceFp2);
				}
			}

			if (sourceFile3)
			{
				if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp3, sourceFile3, "r"))
				{
					SYS_ERROR("Unable to open source file3 : %s\n", sourceFile3);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (TH[thIndex].sourceFp3)
			{
				fseek(TH[thIndex].sourceFp3, 0, SEEK_END);
				if (ftell(TH[thIndex].sourceFp3) <= 0)
				{
					SYS_ERROR("Input file3 has nothing to process\n");
					fclose(TH[thIndex].sourceFp3);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
				else
				{
					rewind(TH[thIndex].sourceFp3);
				}
			}
		}
		else if ((strcmp(tokens[0], "IPNCUC2") == 0))
		{
			//IPNCUC3 UseCase: Open three source files one each for 720p mpeg4 enc, SIF mpeg4 encode and D1 JPEG enc

			TH[thIndex].capture = DVEVM_ST_FALSE;
			if ((NULL == sourceFile1) && (NULL == sourceFile2) && (NULL == sourceFile3))
			{
				//set capture option
				TH[thIndex].capture = DVEVM_ST_TRUE;
			}
			else if ((NULL == sourceFile1) || (NULL == sourceFile2) || (NULL == sourceFile3))
			{
				//Throw error stating that all three files should be specified.
				SYS_ERROR("Specify all three input source files for this usecase.\n");
				retval = DVEVM_ST_FAIL;
				break;
			}

			SYS_OUT("Starting Thread for command <%s>\n", *tokens);
			if (DVEVM_ST_FAIL == dvtb_getFreeThr(&thIndex))
			{
				SYS_ERROR("MAX number of threads already started\n");
				retval = DVEVM_ST_FAIL;
				break;
			}

			TH[thIndex].useAlgorithm = !noAlgorithm;

			if ((NULL != sourceFile1) && (NULL != sourceFile2) && (NULL != sourceFile3))
			{
				if (strcmp(sourceFile1, sourceFile2) == 0)
				{
					SYS_ERROR("Input File1 & Input File2 names are same\n");
					retval = DVEVM_ST_FAIL;
					break;
				}
				if (strcmp(sourceFile1, sourceFile3) == 0)
				{
					SYS_ERROR("Input File1 & Input File3 names are same\n");
					retval = DVEVM_ST_FAIL;
					break;
				}
				if (strcmp(sourceFile2, sourceFile3) == 0)
				{
					SYS_ERROR("Input File2 & Input File3 names are same\n");
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (sourceFile1)
			{
				if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp1, sourceFile1, "r"))
				{
					SYS_ERROR("Unable to open source file1 : %s\n", sourceFile1);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (TH[thIndex].sourceFp1)
			{
				fseek(TH[thIndex].sourceFp1, 0, SEEK_END);
				if (ftell(TH[thIndex].sourceFp1) <= 0)
				{
					SYS_ERROR("Input file1 has nothing to process\n");
					fclose(TH[thIndex].sourceFp1);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
				else
				{
					rewind(TH[thIndex].sourceFp1);
				}
			}

			if (sourceFile2)
			{
				if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp2, sourceFile2, "r"))
				{
					SYS_ERROR("Unable to open source file2 : %s\n", sourceFile2);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (TH[thIndex].sourceFp2)
			{
				fseek(TH[thIndex].sourceFp2, 0, SEEK_END);
				if (ftell(TH[thIndex].sourceFp2) <= 0)
				{
					SYS_ERROR("Input file2 has nothing to process\n");
					fclose(TH[thIndex].sourceFp2);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
				else
				{
					rewind(TH[thIndex].sourceFp2);
				}
			}

			if (sourceFile3)
			{
				if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp3, sourceFile3, "r"))
				{
					SYS_ERROR("Unable to open source file3 : %s\n", sourceFile3);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (TH[thIndex].sourceFp3)
			{
				fseek(TH[thIndex].sourceFp3, 0, SEEK_END);
				if (ftell(TH[thIndex].sourceFp3) <= 0)
				{
					SYS_ERROR("Input file3 has nothing to process\n");
					fclose(TH[thIndex].sourceFp3);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
				else
				{
					rewind(TH[thIndex].sourceFp3);
				}
			}
		}
		else if ((strcmp(tokens[0], "DVRUC0") == 0))
		{
			//DVRUC0 UseCase: Open source files for 2 channels of D1 mpeg4 enc

			TH[thIndex].capture = DVEVM_ST_FALSE;
			if ((NULL == sourceFile1) && (NULL == sourceFile2))
			{
				//set capture option
				TH[thIndex].capture = DVEVM_ST_TRUE;
			}
			else if ((NULL == sourceFile1) || (NULL == sourceFile2))
			{
				//Throw error stating that all three files should be specified.
				SYS_ERROR("Specify two input source files (1-D1 YUV, 2-D1 YUV) for this usecase.\n");
				retval = DVEVM_ST_FAIL;
				break;
			}

			SYS_OUT("Starting Thread for command <%s>\n", *tokens);
			SYS_OUT("InputFile1 <%s> InputFile2 <%s>\n", sourceFile1, sourceFile2);
			if (DVEVM_ST_FAIL == dvtb_getFreeThr(&thIndex))
			{
				SYS_ERROR("MAX number of threads already started\n");
				retval = DVEVM_ST_FAIL;
				break;
			}

			TH[thIndex].useAlgorithm = !noAlgorithm;

			if ((NULL != sourceFile1) && (NULL != sourceFile2))
			{
				if (strcmp(sourceFile1, sourceFile2) == 0)
				{
					SYS_ERROR("Input File1 & Input File2 names are same\n");
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (sourceFile1)
			{
				if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp1, sourceFile1, "r"))
				{
					SYS_ERROR("Unable to open source file1 : %s\n", sourceFile1);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (TH[thIndex].sourceFp1)
			{
				fseek(TH[thIndex].sourceFp1, 0, SEEK_END);
				if (ftell(TH[thIndex].sourceFp1) <= 0)
				{
					SYS_ERROR("Input file1 has nothing to process\n");
					fclose(TH[thIndex].sourceFp1);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
				else
				{
					rewind(TH[thIndex].sourceFp1);
				}
			}

			if (sourceFile2)
			{
				if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp2, sourceFile2, "r"))
				{
					SYS_ERROR("*****Unable to open source file2 : %s\n", sourceFile2);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
			}

			if (TH[thIndex].sourceFp2)
			{
				fseek(TH[thIndex].sourceFp2, 0, SEEK_END);
				if (ftell(TH[thIndex].sourceFp2) <= 0)
				{
					SYS_ERROR("Input file2 has nothing to process\n");
					fclose(TH[thIndex].sourceFp2);
					dvtb_freeThr(&TH[thIndex]);
					retval = DVEVM_ST_FAIL;
					break;
				}
				else
				{
					rewind(TH[thIndex].sourceFp2);
				}
			}
		}
		else if ((strcmp(tokens[0], "DVRUC1") == 0))
		{
			//DVRUC1 UseCase: files are opened in handler
		}
		else if ((strcmp(tokens[0], "DVRUC2") == 0))
		{
			//DVRUC2 UseCase: files are opened in handler
		}
	}while(DVEVM_ST_FALSE);

	return retval;
}

DvevmStRetCode
dvtb_funcExecute(int numTokens, char **tokens)
{
	int i = 0, j = 0;
	char *sourceFile = NULL, *targetFile = NULL;
	unsigned int thIndex = 0;

	DvevmStRetCode retval = DVEVM_ST_FAIL;
	DvevmStBool noAlgorithm = DVEVM_ST_FALSE;

	ASSERT(numTokens >= 1);

	for (i = 0; i < MAX_FUNC_CMDS; i++)
	{
		if (0 == strcmp(*tokens, dvevmStFuncCmdInfo[i].key))
		{
			if (NULL == dvevmStFuncCmdInfo[i].dptr)
				return DVEVM_ST_NOTSUPPORTED;

			/* First token would be 'key'. Start from next token */

			if(DVEVM_ST_SUCCESS == dvtb_checkAppSpecific(tokens))
			{
				if(DVEVM_ST_FAIL == dvtb_openAppSpecificFiles(numTokens, tokens))
				{
					SYS_ERROR("Unable to open files for App specific use cases \n");
					return DVEVM_ST_FAIL;
				}
			}
			else
			{
				for (j = 1; j < numTokens; j++)
				{
					if (0 == strcmp(tokens[j], NODSP_OPTION))
						noAlgorithm = DVEVM_ST_TRUE;
					else if (0 == strcmp(tokens[j], SOURCE_FILE_OPTION))
						sourceFile = tokens[++j];
					else if (0 == strcmp(tokens[j], TARGET_FILE_OPTION))
						targetFile = tokens[++j];
				}

				if (!sourceFile && !targetFile)
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
				if (sourceFile)
				{
					if (DVEVM_ST_FAIL == dvtb_fileOpen(&TH[thIndex].sourceFp, sourceFile, "r"))
					{
						SYS_ERROR("Unable to open source file : %s\n", sourceFile);
						dvtb_freeThr(&TH[thIndex]);
						return DVEVM_ST_FAIL;
					}

					fseek(TH[thIndex].sourceFp, 0, SEEK_END);
					if (ftell(TH[thIndex].sourceFp) <= 0)
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

				if (!TH[thIndex].sourceFp && !TH[thIndex].targetFp && (strcmp(tokens[0], "viddriverdisp") != 0))
				{
					SYS_ERROR("Both source and target files cannot be opened\n");
					dvtb_freeThr(&TH[thIndex]);
					return DVEVM_ST_FAIL;
				}
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
