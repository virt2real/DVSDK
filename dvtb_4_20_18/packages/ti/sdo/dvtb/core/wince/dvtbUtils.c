/*
 * dvtbUtils.c
 *
 * DVTB(wince) Utility functions Implementation
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

#include "dvtbUtils.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_SWITCH_LENGTH       4
#define MAX_SWITCHES            2
#define MAX_IO_TOKENS           (MAX_SWITCHES*2)

DvevmStRetCode
dvtb_getFileSize(FILE *fp, unsigned int *fileSize)
{
	int size = 0;
	DVTBASSERT(fp);

	fseek(fp, 0L, SEEK_END);
	*fileSize = ftell(fp);
	size = (int) *fileSize;
	fseek(fp, -size, SEEK_CUR);

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_fileRead(FILE *fp, char *buff, int readData, int *nBytes)
{
	DVTBASSERT(fp);
	DVTBASSERT(buff);

	*nBytes = fread(buff, 1, readData, fp);

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_fileWrite(FILE *fp, char *buff, int writeData)
{
	DVTBASSERT(buff);

	fwrite(buff, 1, writeData, fp);

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_fileOpen(FILE **fp, const char *restrict filename, const char *restrict mode)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	
	if (NULL == filename)
	{
		SYS_ERROR("File open failed: file name is NULL\n");
		*fp = NULL;
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		*fp = fopen(filename, mode);
		if(NULL == *fp)
		{
			SYS_ERROR("File open failed\n");
			retCode = DVEVM_ST_FAIL;
		}
	}

	return retCode;
}

void
dvtb_fileClose(FILE **sourceFp, FILE **targetFp)
{
	if (*sourceFp)
	{
		fclose(*sourceFp);
		*sourceFp = NULL;
	}

	if (*targetFp)
	{
		fclose(*targetFp);
		*targetFp = NULL;
	}
}

#if 0
DvevmStRetCode
dvtb_displayBuffer(DvevmStVpbeInfo *vpbe, char *buff, int buffSize)
{
	void *tempDispBuf = NULL;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	DVTBASSERT(vpbe);
	DVTBASSERT(buff);

	tempDispBuf = dvtb_vpbeGetDisplayBuffer(vpbe);
	if (NULL == tempDispBuf)
	{
		SYS_ERROR("Unable to get the Display buffer.\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		memcpy(tempDispBuf, buff, buffSize);

		if(DVEVM_ST_SUCCESS != dvtb_vpbeDisplay(vpbe, tempDispBuf))
		{
			SYS_ERROR("Unable to Display.\n");
			retCode = DVEVM_ST_FAIL;
		}
	}

	return retCode;
}
#endif

DvevmStRetCode
dvtb_byteSwapBitStream(char *inout_p, short size)
{
	short i = 0;
	char tempr = 0;

	DVTBASSERT(inout_p);

	for (i = 0; i < size; i++) {
		tempr = inout_p[i];
		inout_p[i] = inout_p[i + 1];
		inout_p[i + 1] = tempr;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_stereoToMono(short *in_stereoSamples, short *out_monoSamples, int numSamples)
{
	int i = 0, val = 0;

	DVTBASSERT(in_stereoSamples);
	DVTBASSERT(out_monoSamples);

	for (i = 0; i < numSamples; i++)
	{
		val = *in_stereoSamples++;
		*out_monoSamples++ = (val + *in_stereoSamples++) / 2;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_inputFileToProcessbuff(char *in_samples, char *out_processbuff, int numSamples)
{
	int i = 0;

	DVTBASSERT(in_samples);
	DVTBASSERT(out_processbuff);

	for (i = 0; i < numSamples; i++)
	{
		out_processbuff[i] = in_samples[i];
	}
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_inputFileToG722Processbuff(short *in_samples, short *out_processbuff, int numSamples)
{
	int i;

	DVTBASSERT(in_samples);
	DVTBASSERT(out_processbuff);

	for (i = 0; i < numSamples; i++)
	{
		out_processbuff[i] = in_samples[i];
		out_processbuff[i] = out_processbuff[i] >> 1;
	}

	return DVEVM_ST_SUCCESS;
}

void
dvtb_convert420pTo420sp(unsigned char *inBuf, unsigned char *outBuf, int width, int height)
{
	int resolution = 0, i = 0, chromaSize = 0;
	unsigned char *inBufCb = NULL, *inBufCr = NULL;

	resolution = width * height;
	chromaSize = (resolution >> 2);
	memset(outBuf, 0, ((resolution * 3) >> 1));
	memcpy(outBuf, inBuf, resolution);
	inBufCb = inBuf + resolution;
	inBufCr = inBufCb + chromaSize;
	outBuf += resolution;
	for (i = 0; i < chromaSize; i++)
	{
		outBuf[(i << 1)] = inBufCb[i];
		outBuf[(i << 1) + 1] = inBufCr[i];
	}
}

void
dvtb_convert420spTo420p(unsigned char *inBuf, unsigned char *outBuf, int width, int height)
{
	int resolution = 0, i = 0, chromaSize = 0;
	unsigned char *outBufCb = NULL, *outBufCr = NULL;

	resolution = width * height;
	chromaSize = (resolution >> 2);
	memset(outBuf, 0, ((resolution * 3) >> 1));
	memcpy(outBuf, inBuf, resolution);
	outBufCb = outBuf + resolution;
	outBufCr = outBufCb + chromaSize;
	inBuf += resolution;
	for (i = 0; i < chromaSize; i++)
	{
		outBufCb[i] = inBuf[(i << 1)];
		outBufCr[i] = inBuf[(i << 1) + 1];
	}
}

void
dvtb_convert422pTo422sp(unsigned char *inBuf, unsigned char *outBuf, int width, int height)
{
	int resolution = 0, i = 0, chromaSize = 0;
	unsigned char *inBufCb = NULL, *inBufCr = NULL;

	resolution = width * height;
	chromaSize = (resolution >> 1);
	memset(outBuf, 0, (resolution << 1));
	memcpy(outBuf, inBuf, resolution);
	inBufCb = inBuf + resolution;
	inBufCr = inBufCb + chromaSize;
	outBuf += resolution;
	for (i = 0; i < chromaSize; i++)
	{
		outBuf[(i << 1)] = inBufCb[i];
		outBuf[(i << 1) + 1] = inBufCr[i];
	}
}

void
dvtb_convert422spTo422p(unsigned char *inBuf, unsigned char *outBuf, int width, int height)
{
	int resolution = 0, i = 0, chromaSize = 0;
	unsigned char *outBufCb = NULL, *outBufCr = NULL;

	resolution = width * height;
	chromaSize = (resolution >> 1);
	memset(outBuf, 0, (resolution << 1));
	memcpy(outBuf, inBuf, resolution);
	outBufCb = outBuf + resolution;
	outBufCr = outBufCb + chromaSize;
	inBuf += resolution;
	for (i = 0; i < chromaSize; i++)
	{
		outBufCb[i] = inBuf[(i << 1)];
		outBufCr[i] = inBuf[(i << 1) + 1];
	}
}

void
dvtb_convert420spTo422sp(unsigned char *inBuf, unsigned char *outBuf, int width, int height)
{
	int resolution = 0, i = 0;

	resolution = width * height;
	memset(outBuf, 0, (resolution << 1));
	memcpy(outBuf, inBuf, resolution);
	inBuf += resolution;
	outBuf += resolution;
	for (i = 0; i < height; i += 2)
	{
		memcpy(outBuf, inBuf, width);
		outBuf += width;
		memcpy(outBuf, inBuf, width);
		inBuf += width;
		outBuf += width;
	}
}

void
dvtb_convert422spTo420sp(unsigned char *inBuf, unsigned char *outBuf, int width, int height)
{
	int resolution = 0, i = 0;

	resolution = width * height;
	memset(outBuf, 0, ((resolution * 3) >> 1));
	memcpy(outBuf, inBuf, resolution);
	inBuf += resolution;
	outBuf += resolution;
	for (i = 0; i < height; i += 2)
	{
		memcpy(outBuf, inBuf, width);
		inBuf += (width << 1);
		outBuf += width;
	}
}

void
dvtb_convertSplit420spTo422sp(unsigned char *inBufLuma, unsigned char *inBufChroma, unsigned char *outBuf, int width, int height, int pitch)
{
	int resolution = 0, i = 0;
	unsigned char *outBufChroma;

	resolution = width * height;
	outBufChroma = outBuf + resolution;

	for (i = 0; i < height; i += 2)
	{
		memcpy(outBuf, inBufLuma, width);
		outBuf += width;
		inBufLuma += pitch;

		memcpy(outBuf, inBufLuma, width);
		outBuf += width;
		inBufLuma += pitch;

		memcpy(outBufChroma, inBufChroma, width);
		outBufChroma += width;

		memcpy(outBufChroma, inBufChroma, width);
		outBufChroma += width;

		inBufChroma += pitch;
	}
}

DvevmStRetCode
dvtb_separateCbCrPixels(XDAS_Int8 *CbCr_data, XDAS_Int8 *Chroma_buf[2], XDAS_Int32 height, XDAS_Int32 width, XDAS_UInt16 pitch)
{
	XDAS_UInt32 i, j;
	XDAS_UInt32 pix_count = 0;
	XDAS_Int8* Cb_data;
	XDAS_Int8* Cr_data;
	XDAS_Int8* CbCr_buf;

	DVTBASSERT(Chroma_buf[0]);
	DVTBASSERT(Chroma_buf[1]);
	DVTBASSERT(CbCr_data);

	Cb_data = Chroma_buf[0];
	Cr_data = Chroma_buf[1];
	CbCr_buf = CbCr_data;

	for (i = 0; i < (XDAS_UInt32)height; i++)
	{
		for (j = 0; j < (XDAS_UInt32)width; j += 2)
		{
			Cb_data[pix_count] = CbCr_buf[j];
			Cr_data[pix_count] = CbCr_buf[j + 1];
			pix_count++;
		}
		CbCr_buf += pitch;
	}

	return DVEVM_ST_SUCCESS;
}

void
dvtb_startMessage(int classType, char *string, DvevmStBool useAlgorithm, DvevmStBool fileBased)
{
	switch (classType)
	{
		case DVEVM_ST_ENCODE:

			if (DVEVM_ST_FALSE == fileBased)
			{
				if (useAlgorithm)
					SYS_OUT("%s [capture]+[encode] usecase started\n",string);
				else
					SYS_OUT("%s [capture] usecase started\n",string);
			}
			else
				SYS_OUT("%s [File Read]+[encode] usecase started\n",string);

			break;

		case DVEVM_ST_DECODE:

			if (DVEVM_ST_FALSE == fileBased)
			{
				if (useAlgorithm)
					SYS_OUT("%s [Decode]+[Play] usecase started.\n",string);
				else
					SYS_OUT("%s [Play] usecase started.\n",string);
			}
			else
				SYS_OUT("%s [Decode]+[Dump] usecase started.\n",string);

			break;

		case DVEVM_ST_ENCDEC:
			if (DVEVM_ST_FALSE == fileBased)
			{
				if (useAlgorithm)
					SYS_OUT("%s [Capture]+[Encode]+[Decode]+[Play] usecase started.\n",string);
				else
					SYS_OUT("%s [Capture]+[Play] usecase started.\n",string);
			}
			else
			{
				if(useAlgorithm)
					SYS_OUT("%s [File Read]+[Encode]+[Decode]+[Dump] usecase started.\n",string);
				else
					SYS_OUT("%s [File Read]+[Dump] usecase started.\n",string);
			}

			break;

		default:
			SYS_OUT("Unknown usecase <%s> started.\n",string);

	}
}

void
dvtb_exitMessage(int classType, char *string, DvevmStBool useAlgorithm, DvevmStBool fileBased, DvevmStBool usecaseFailed)
{
	switch (classType)
	{
		case DVEVM_ST_ENCODE:

			if (DVEVM_ST_TRUE == fileBased)//File based
			{
				if (DVEVM_ST_FALSE == usecaseFailed)
					SYS_OUT("%s [File Read]+[Encode] usecase completed successfully.\n", string);
				else
					SYS_OUT("%s [File Read]+[Encode] usecase completed with errors.\n", string);
			}
			else //Driver based
			{
				if (useAlgorithm)
				{
					if (DVEVM_ST_FALSE == usecaseFailed)
						SYS_OUT("%s [Capture]+[Encode] usecase completed successfully.\n", string);
					else
						SYS_OUT("%s [Capture]+[Encode] usecase completed with errors.\n", string);
				}
				else
				{
					if (DVEVM_ST_FALSE == usecaseFailed)
						SYS_OUT("%s [Capture] usecase completed successfully.\n", string);
					else
						SYS_OUT("%s [Capture] usecase completed with errors.\n", string);
				}
			}

			break;

		case DVEVM_ST_DECODE:

			if (DVEVM_ST_TRUE == fileBased)//File based
			{
				if (DVEVM_ST_FALSE == usecaseFailed)
					SYS_OUT("%s [Decode]+[Dump] usecase completed successfully.\n", string);
				else
					SYS_OUT("%s [Decode]+[Dump] usecase completed with errors.\n", string);
			}
			else
			{
				if (useAlgorithm)
				{
					if (DVEVM_ST_FALSE == usecaseFailed)
						SYS_OUT("%s [Decode]+[Play] usecase completed successfully.\n", string);
					else
						SYS_OUT("%s [Decode]+[Play] usecase completed with errors.\n", string);
				}
				else
				{
					if (DVEVM_ST_FALSE == usecaseFailed)
						SYS_OUT("%s [Play] usecase completed successfully.\n", string);
					else
						SYS_OUT("%s [Play] usecase completed with errors.\n", string);
				}
			}
			break;

		case DVEVM_ST_ENCDEC:

			if (DVEVM_ST_FALSE == fileBased)//File based
			{
				if(useAlgorithm)
				{
					if (DVEVM_ST_FALSE == usecaseFailed)
						SYS_OUT("%s [Capture]+[Encode]+[Decode]+[Play] usecase completed successfully.\n", string);
					else
						SYS_OUT("%s [Capture]+[Encode]+[Decode]+[Play] usecase completed with errors.\n", string);
				}
				else
				{
					if (DVEVM_ST_FALSE == usecaseFailed)
						SYS_OUT("%s [Capture]+[Play] usecase completed successfully.\n", string);
					else
						SYS_OUT("%s [Capture]+[Play] usecase completed with errors.\n", string);

				}
			}
			else
			{
				if(useAlgorithm)
				{
					if (DVEVM_ST_FALSE == usecaseFailed)
						SYS_OUT("%s [File Read]+[Encode]+[Decode]+[Dump] usecase completed successfully.\n", string);
					else
						SYS_OUT("%s [File Read]+[Encode]+[Decode]+[Dump] usecase completed with errors.\n", string);
				}
				else
				{
					if (DVEVM_ST_FALSE == usecaseFailed)
						SYS_OUT("%s [File Read]+[Dump] usecase completed successfully.\n", string);
					else
						SYS_OUT("%s [File Read]+[Dump] usecase completed with errors.\n", string);
				}
			}

			break;

		default:

			if(DVEVM_ST_TRUE == usecaseFailed)
				SYS_OUT("Unknown usecase completed with error\n");
			else
				SYS_OUT("Unknown usecase completed successfully\n");
	}
}

DvevmStRetCode
dvtb_openSrcTrgFromInputFile(FILE *in_inputFile, FILE **out_sourceFp, FILE **out_targetFp, int in_maxinstances)
{
	int i = 0, nBytes = 0, numTokens = 0, instanceCount = 0;
	char buff[MAX_LINE_SIZE], *parsedTokens[MAX_IO_TOKENS], sourceSwitch[MAX_SWITCH_LENGTH],
		targetSwitch[MAX_SWITCH_LENGTH];

	DvevmStRetCode retVal = DVEVM_ST_SUCCESS;

	while (i < in_maxinstances)
	{
		memset(buff, 0, MAX_LINE_SIZE);
		nBytes = dvtb_readFile(in_inputFile, buff);

		if (DVEVM_ST_FAIL == nBytes)
			break;

		if ('#' == buff[0] || 0 == nBytes || 0 == buff[0])
			continue;

		numTokens = dvtb_tokenize(buff, parsedTokens, MAX_IO_TOKENS);
		if (0 == numTokens)
			continue;

		sprintf(sourceSwitch, "-s%d", i);
		sprintf(targetSwitch, "-t%d", i);

		if (0 == strcmp(parsedTokens[0], sourceSwitch))
		{
			SYS_ERROR("Source File not specified for instance# %d\n", i);
			retVal = DVEVM_ST_FAIL;
			break;
		}

		if (0 == strcmp(parsedTokens[2], targetSwitch))
		{
			SYS_ERROR("Target File not specified for instance# %d\n", i);
			retVal = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_fileOpen(&out_sourceFp[i] , parsedTokens[1], "r"))
		{
			SYS_ERROR("Unable to open Source File \"%s\" for instance# %d \n", parsedTokens[1], i);
			retVal = DVEVM_ST_FAIL;
			break;
		}

		fseek(out_sourceFp[i], 0, SEEK_END);
		if (ftell(out_sourceFp[i]) <= 0)
		{
			SYS_ERROR("Source file \"%s\" for instance# %d has nothing to process\n", parsedTokens[1], i);
			retVal = DVEVM_ST_FAIL;
			break;
		}
		else
		{

			fseek(out_sourceFp[i], 0,SEEK_SET);
		}

		if(DVEVM_ST_FAIL == dvtb_fileOpen(&out_targetFp[i] ,parsedTokens[3], "w"))
		{
			SYS_ERROR("Unable to open target file \"%s\" file for instance# %d.\n", parsedTokens[3], i);
			retVal = DVEVM_ST_FAIL;
			break;
		}

		instanceCount++;
		i++;
	}

	return retVal;
}

