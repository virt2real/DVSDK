/*
 * dvtbMP3BasePlay1.c
 *
 * XDM1.0 MP3Base Decode functionality
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

#include "dvtbMP3BasePlay1.h"
#include "dvtbALSAAudio.h"
#include "dvtbMP3BaseDec1.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include <ti/sdo/ce/trace/gt.h>
#include "dvtbDefs.h"

void
dvtb_mp3baseDec1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("MP3 [Decode]+[Play] completed for <%d> frames\n", nFrames - 1);
		else
			SYS_OUT("MP3 [Play] completed for <%d> frames\n", nFrames - 1);
	}
	else//File based
		SYS_OUT("MP3 [Decode]+[dump] completed for <%d> frames\n", nFrames - 1);
}

void
dvtb_mp3baseDec1InitPtrs(DvevmStMP3BaseDec1Info *ad)
{
	ad->ceHdl = NULL;
	ad->adecHdl = NULL;

	ad->inBuf.start = NULL;
	ad->outBuf.start = NULL;
}

DvevmStRetCode
dvtb_mp3baseDec1HanInit(DvevmStMP3BaseDec1Info *ad, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &ad->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}


		if (DVEVM_ST_FAIL == dvtb_mp3basedec1Init(ad))
		{
			SYS_ERROR("Unable to initialize Audio Decoder <%s>\n", ad->adecName);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_mp3baseDec1HanClose(DvevmStMP3BaseDec1Info *ad, char *engName)
{
	dvtb_mp3basedec1Close(ad);
	SYS_OUT("Audio Decoder <%s> closed\n", ad->adecName);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&ad->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_mp3baseDec1DecProcess(DvevmStMP3BaseDec1Info *ad, int *decDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_mp3basedec1Decode(ad, decDuration))
		{
			SYS_ERROR("Unable to decode <%s> \n", ad->adecName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		ad->adecCmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_mp3basedec1Control(ad))
		{
			SYS_ERROR("Unable to get the status \n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_mp3baseDec1ProcessOutBuff(DvevmStAudioInfo *aud, DvevmStBool fileBased, char *buff, int nBytes, FILE *fp)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_TRUE == fileBased)
	{
		if(DVEVM_ST_FAIL ==  dvtb_fileWrite(fp, buff, nBytes))
		{
			SYS_ERROR("Error in writing to file.\n");
			retCode = DVEVM_ST_FAIL;
		}
	}
	else
	{
		if (DVEVM_ST_FAIL == dvtb_audioOut(aud, buff, nBytes))
		{
			SYS_ERROR("Unable to write into target device\n");
			retCode = DVEVM_ST_FAIL;
		}
	}

	return retCode;

}

int
dvtb_mp3baseDec1SetSampleRate(DvevmStAudioInfo *aud, int sampleRate)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (aud->sampleRate != sampleRate)
	{
		aud->sampleRate = sampleRate;
		if (DVEVM_ST_FAIL == dvtb_audioControl(aud))
		{
			SYS_ERROR("Unable to set the sample rate\n");
			retCode = DVEVM_ST_FAIL;
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_mp3baseDec1ReadInput(char *inBuffer, int *totalBytesConsumed, int *bytesRemaining, int buffsize, FILE *fp, int *nBytes)
{
	DvevmStRetCode retval = DVEVM_ST_SUCCESS;

	if(*bytesRemaining)
		memcpy(&inBuffer[0], &inBuffer[*totalBytesConsumed], *bytesRemaining);

	if (DVEVM_ST_FAIL == dvtb_fileRead(fp, &inBuffer[*bytesRemaining], buffsize - *bytesRemaining, nBytes))
	{
		SYS_ERROR("Error in file read \n");
		retval = DVEVM_ST_FAIL;
	}
	else
	{
		*nBytes += *bytesRemaining;
		*bytesRemaining = *nBytes;
		*totalBytesConsumed = 0;
	}

	return retval;
}


void
dvtb_Mp3baseDec1Play(DvevmStThreadInfo *T)
{
	int nBytes = DVEVM_ST_FAIL, nFrames = 0, frameSize = 0, totalBytesConsumed = 0, bytesRemaining = 0,
		buffsize = 1000000, thresh_hold = 900000, hugeChunk = 0, decDuration = 0;
	char *buff = NULL, *inBuffer = NULL;
	unsigned int inputFileSize = 0;

	DvevmStRetCode status = DVEVM_ST_FAIL;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, audioDeviceOpened =	DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	if (!T->sourceFp)
	{
		SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}
	if(!T->useAlgorithm)
	{
		SYS_ERROR("No DSP option is not supported \n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}


	if (!T->targetFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_DECODE, "MP3", T->useAlgorithm, fileBased);
	dvtb_mp3baseDec1InitPtrs(&T->g.mp3basedec1);

	// [Decode][Play] scenario
	do
	{
		if (T->useAlgorithm)
		{
			if (DVEVM_ST_FAIL == dvtb_mp3baseDec1HanInit(&T->g.mp3basedec1, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Speech decode handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Audio Decoder <%s> initialized\n", T->g.mp3basedec1.adecName);
		}

		if (DVEVM_ST_FALSE == fileBased)
		{
			T->g.aud.framesize = T->g.mp3basedec1.outBuf.size;
			status = dvtb_audioSetup(&T->g.aud);
			if (DVEVM_ST_FAIL == status)
			{
				SYS_ERROR("Unable to setup Audio device <%s> for playback\n", T->g.aud.device);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			audioDeviceOpened = DVEVM_ST_TRUE;
			SYS_OUT("Audio device <%s> initialized for playback\n", T->g.aud.device);
		}

		hugeChunk = buffsize;
		//Get file Size
		if (DVEVM_ST_FAIL == dvtb_getFileSize(T->sourceFp, &inputFileSize))
		{
			SYS_ERROR("Unable to Get file size\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}
		//If input file size is less than huge chunk than set hugeChunk to input file Size
		if (inputFileSize < hugeChunk)
			hugeChunk = inputFileSize;

		if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&inBuffer, buffsize))
		{
			SYS_ERROR("Unable to allocate memory for In Buffer\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		bytesRemaining = 0;
		if (DVEVM_ST_FAIL == dvtb_mp3baseDec1ReadInput(inBuffer, &totalBytesConsumed, &bytesRemaining, buffsize, T->sourceFp, &nBytes))
		{
			SYS_ERROR("Error in Read Input\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		while (!feof(T->sourceFp) || bytesRemaining)
		{
			if (totalBytesConsumed > thresh_hold)
			{
				if (DVEVM_ST_FAIL == dvtb_mp3baseDec1ReadInput(inBuffer, &totalBytesConsumed, &bytesRemaining, buffsize, T->sourceFp, &nBytes))
				{
					SYS_ERROR("Error in Read Input\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				hugeChunk = nBytes;
				if (nBytes == 0)
				{
					SYS_OUT("End of file reached. Exiting...\n");
					break;
				}
			}
			nFrames++;

			if (bytesRemaining < 2880)
				nBytes = bytesRemaining;
			else
				nBytes = 2880;

			buff = &inBuffer[totalBytesConsumed];
			T->g.mp3basedec1.inBuf.start = buff;

			if (T->useAlgorithm)
			{
				T->g.mp3basedec1.inFrameSize = nBytes;

				if(DVEVM_ST_FAIL == dvtb_mp3baseDec1DecProcess(&T->g.mp3basedec1, &decDuration))
				{
					SYS_ERROR("Unable to decode frame # %d\n",	nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				frameSize = T->g.mp3basedec1.decFrameSize;
				totalBytesConsumed += frameSize;
				bytesRemaining = hugeChunk - totalBytesConsumed;

				if (DVEVM_ST_FALSE == fileBased)
				{
					if(DVEVM_ST_FAIL == dvtb_mp3baseDec1SetSampleRate(&T->g.aud, T->g.mp3basedec1.adecStatus.sampleRate))
					{
						SYS_ERROR("Unable to Set Sample rate \n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}
				}

				buff = T->g.mp3basedec1.outBuf.start;

				nBytes = T->g.mp3basedec1.adecStatus.numSamples * 4;

				SYS_DEBUG("Frame # %d: InBytes %d, BytesConsumed %d, OutputBytes %d\n", nFrames, T->g.mp3basedec1.inFrameSize, frameSize, nBytes);
#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Decoded Frame Size(bytes), %d, DecTime(us), %d\n", (unsigned int) T, nFrames, nBytes, decDuration);
#endif
				if(DVEVM_ST_FAIL == dvtb_mp3baseDec1ProcessOutBuff(&T->g.aud, fileBased, buff, nBytes, T->targetFp))
				{
					SYS_ERROR("Unable to Process output buffers \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
			}

		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_mp3baseDec1ProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

	if (DVEVM_ST_TRUE == audioDeviceOpened)
	{
		dvtb_audioClose(&T->g.aud);
		SYS_OUT("Audio Device <%s> closed\n", T->g.aud.device);
	}

	if (NULL != inBuffer)
	{
		dvtb_freeSingleBufCmem(inBuffer, buffsize);
		inBuffer = NULL;
	}

	if (T->useAlgorithm)
		dvtb_mp3baseDec1HanClose(&T->g.mp3basedec1, T->g.eng.name);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);
	dvtb_exitMessage(DVEVM_ST_DECODE, "MP3", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
