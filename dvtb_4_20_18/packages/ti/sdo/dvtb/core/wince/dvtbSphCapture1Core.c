/*
 * dvtbSphCapture1Core.c
 *
 * DVTB(wince) XDM1.0 Speech Encode related Core Functions
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

#include "dvtbSphCapture1Core.h"
#include "dvtbUtils.h"

void
dvtb_sphEnc1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int seconds)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Speech [Capture]+[Encode] completed for %d seconds\n",	seconds);
		else
			SYS_OUT("Speech [Capture] completed for %d seconds\n", seconds);
	}
	else//File based
		SYS_OUT("Speech [File Read]+[Encode] completed\n");
}

void
dvtb_sphEnc1InitPtrs(DvevmStSphEnc1Info *se)
{
	se->hTime = NULL;
	se->ceHdl = NULL;
	se->sencHdl = NULL;

	se->inBuf.start = NULL;
	se->outBuf.start = NULL;
}

DvevmStRetCode
dvtb_sphEnc1HanInit(DvevmStSphEnc1Info *se, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	se->inBuf.size = SPHENC1_FRAME_SIZE * 2;
	se->outBuf.size = SPHENC1_FRAME_SIZE;

	if (!(strcmp(se->sencName, "g722enc")))
	{
		if (se->sencParams.codecSelection == 1)
		{
			se->sencParams.frameSize = SPHENC1_FRAME_SIZE * 2;
			se->inBuf.size = SPHENC1_FRAME_SIZE * 2;
			se->outBuf.size = SPHENC1_FRAME_SIZE * 2;
		}
		else
		{
			se->sencParams.frameSize = (se->inBuf.size) * 2; //SPHENC1_FRAME_SIZE * 4;
			se->sencParams.bitRate = se->sencParams.bitRate;
			se->inBuf.size = (se->inBuf.size) * 2; //SPHENC1_FRAME_SIZE * 4;
			se->outBuf.size = (se->outBuf.size) * 2; // SPHENC1_FRAME_SIZE;
		}
	}

	if (!(strcmp(se->sencName, "ilbcenc")))
	{
		if (se->sencParams.codecSelection == 0)
			se->inBuf.size = SPHENC1_FRAME_SIZE * 4; //80*4
		else
			se->inBuf.size = SPHENC1_FRAME_SIZE * 6; //80*6
	}

	do
	{
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName,	&se->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_sphEnc1Init(se))
		{
			SYS_ERROR("Unable to initialize Speech Encoder <%s>\n",	se->sencName);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_sphEnc1HanClose(DvevmStSphEnc1Info *se, char *engName)
{
	dvtb_sphEnc1Close(se);
	SYS_OUT("Speech Encoder <%s> closed\n", se->sencName);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&se->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

int
dvtb_sphEnc1GetInputBuffSize(DvevmStSphEnc1Info *se, DvevmStBool fileBased)
{
	int nBytes = DVEVM_ST_FAIL;

	if (!(strcmp(se->sencName, "g722enc")))
		nBytes = SPHENC1_FRAME_SIZE * 4;
	else if (!(strcmp(se->sencName, "ilbcenc")))
	{
		if (se->sencParams.codecSelection == 0)
			nBytes = SPHENC1_FRAME_SIZE * 4;
		else
			nBytes = SPHENC1_FRAME_SIZE * 6;
	}
	else if (DVEVM_ST_FALSE == fileBased)
		nBytes = SPHENC1_FRAME_SIZE * 4;
	else
		nBytes = SPHENC1_FRAME_SIZE * 2;

	return nBytes;
}

#if 0
DvevmStRetCode
dvtb_sphEnc1ReadInput(DvevmStAudioInfo *aud, char *buff, FILE *fp, int bytesToRead, DvevmStBool fileBased, int *nBytes)
{
	DvevmStRetCode retval = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_TRUE == fileBased)
	{
		if(DVEVM_ST_FAIL == dvtb_fileRead(fp, buff, bytesToRead, nBytes))
		{
			SYS_ERROR("Error in file read \n");
			retval = DVEVM_ST_FAIL;
		}
	}
	else
	{
		*nBytes = dvtb_audioIn(aud, buff, bytesToRead);

		if(DVEVM_ST_FAIL == *nBytes)
			retval = DVEVM_ST_FAIL;
	}

	return retval;
}
#else
DvevmStRetCode
dvtb_sphEnc1ReadInput(char *buff, FILE *fp, int bytesToRead, DvevmStBool fileBased, int *nBytes)
{
	DvevmStRetCode retval = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_TRUE == fileBased)
	{
		if(DVEVM_ST_FAIL == dvtb_fileRead(fp, buff, bytesToRead, nBytes))
		{
			SYS_ERROR("Error in file read \n");
			retval = DVEVM_ST_FAIL;
		}
	}
	else
	{
		retval = DVEVM_ST_FAIL;
	}

	return retval;
}

#endif

int
dvtb_sphEnc1BytesToRead(DvevmStSphEnc1Info *se, DvevmStBool fileBased)
{
	int bytesToRead = 0;

	if (DVEVM_ST_TRUE == fileBased)
	{
		if (!(strcmp(se->sencName, "g722enc")))
		{
			if (se->sencParams.codecSelection == 1)
				bytesToRead = SPHENC1_FRAME_SIZE * 2;
			else
				bytesToRead = (se->inBuf.size) * 2;
		}
		else if (!(strcmp(se->sencName, "ilbcenc")))
		{
			if (se->sencParams.codecSelection == 0)
				bytesToRead = SPHENC1_FRAME_SIZE * 4;
			else
				bytesToRead = (se->inBuf.size) * 6;
		}
		else
			bytesToRead = SPHENC1_FRAME_SIZE * 2;
	}
	else
		bytesToRead = SPHENC1_FRAME_SIZE * 4;


	return bytesToRead;
}

DvevmStRetCode
dvtb_sphEnc1EncProcess(DvevmStSphEnc1Info *se, char *buff, DvevmStBool fileBased, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (!(strcmp(se->sencName, "g722enc")))
		{
			if (se->sencParams.codecSelection == 1)
			{
				if (DVEVM_ST_FAIL == dvtb_inputFileToG722Processbuff((short *) buff, (short *) se->inBuf.start, SPHENC1_FRAME_SIZE * 2))
				{
					SYS_ERROR("Unable to copy input file to G722 Process buff  \n");
					retCode = DVEVM_ST_FAIL;
					break;
				}
			}
			else
			{
				if (DVEVM_ST_FAIL == dvtb_inputFileToProcessbuff((char *) buff, (char *) se->inBuf.start, (se->inBuf.size) * 2))
				{
					SYS_ERROR("Unable to copy input file to process buff  \n");
					retCode = DVEVM_ST_FAIL;
					break;
				}
			}
		}
		else if (!(strcmp(se->sencName, "ilbcenc")))
		{
			if (se->sencParams.codecSelection == 0)
			{
				if (DVEVM_ST_FAIL == dvtb_inputFileToProcessbuff((char *) buff, (char *) se->inBuf.start, SPHENC1_FRAME_SIZE * 4))
				{
					SYS_ERROR("Unable to copy input file to process buff  \n");
					retCode = DVEVM_ST_FAIL;
					break;
				}
			}
			else
			{
				if (DVEVM_ST_FAIL == dvtb_inputFileToProcessbuff((char *) buff, (char *) se->inBuf.start, SPHENC1_FRAME_SIZE * 6))
				{
					SYS_ERROR("Unable to copy input file to process buff  \n");
					retCode = DVEVM_ST_FAIL;
					break;
				}
			}
		}
		else if (DVEVM_ST_FALSE == fileBased)
		{
			if (DVEVM_ST_FAIL == dvtb_stereoToMono((short *) buff, (short *) se->inBuf.start, SPHENC1_FRAME_SIZE * 2))
			{
				SYS_ERROR("Unable to convert stereo to mono \n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}
		else
		{
			if (DVEVM_ST_FAIL == dvtb_inputFileToProcessbuff((char *) buff, (char *) se->inBuf.start, SPHENC1_FRAME_SIZE * 2))
			{
				SYS_ERROR("Unable to copy input file to process buff  \n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}

		memset(se->outBuf.start, 0, se->outBuf.size);

		if (DVEVM_ST_FAIL == dvtb_sphEnc1Encode(se, encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	} while (DVEVM_ST_FALSE);

	return retCode;
}

