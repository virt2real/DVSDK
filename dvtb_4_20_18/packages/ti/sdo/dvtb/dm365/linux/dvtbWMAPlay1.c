/*
 * dvtbWMAPlay1.c
 *
 * XDM1.0 WMA Decode Functionality
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

#include "dvtbWMAPlay1.h"
#include "dvtbAudPlay1Core.h"
#include "dvtbWMAPlay1Core.h"
#include "dvtbMemory.h"
#include "dvtbDefs.h"
#include "dvtbUtils.h"

void
dvtb_WmaDec1Play(DvevmStThreadInfo *T)
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
		dvtb_threadExit( );
	}

	if (!T->targetFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_DECODE, "WMA", T->useAlgorithm, fileBased);
	dvtb_wmaDec1InitPtrs(&T->g.wmadec1);


	// [Decode][Play] scenario
	do
	{
		if (T->useAlgorithm)
		{
			if (DVEVM_ST_FAIL == dvtb_wmaDec1HanInit(&T->g.wmadec1, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Audio decode handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			SYS_OUT("Audio Decoder <%s> initialized\n", T->g.wmadec1.adecName);

			if (DVEVM_ST_FAIL == dvtb_audDec1OutBuffAlloc(&T->g.wmadec1.outBuf))
			{
				SYS_ERROR("Unable to Allocate output buffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}

		if (DVEVM_ST_FALSE == fileBased)
		{
			T->g.aud.framesize = T->g.wmadec1.outBuf.bufSizes[0];

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
		if (DVEVM_ST_FAIL == dvtb_audDec1ReadInput(inBuffer, &totalBytesConsumed, &bytesRemaining, buffsize, T->sourceFp, &nBytes))
		{
			SYS_ERROR("Error in Read Input\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		while (!feof(T->sourceFp) || bytesRemaining)
		{
			if (totalBytesConsumed > thresh_hold)
			{
				if (DVEVM_ST_FAIL == dvtb_audDec1ReadInput(inBuffer, &totalBytesConsumed, &bytesRemaining, buffsize, T->sourceFp, &nBytes))
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
			T->g.wmadec1.inBuf.bufs[0] = buff;

			if (T->useAlgorithm)
			{
				T->g.wmadec1.inFrameSize = nBytes;

				if(DVEVM_ST_FAIL == dvtb_wmaDec1DecProcess(&T->g.wmadec1, &decDuration))
				{
					SYS_ERROR("Unable to decode frame # %d\n",	nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}


				frameSize = T->g.wmadec1.decFrameSize;
				totalBytesConsumed += frameSize;
				bytesRemaining = hugeChunk - totalBytesConsumed;

				if (DVEVM_ST_FALSE == fileBased)
				{
					if(DVEVM_ST_FAIL == dvtb_audDec1SetSampleRate(&T->g.aud, T->g.wmadec1.adecStatus.auddec_status.sampleRate))
					{
						SYS_ERROR("Unable to Set Sample rate \n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}
				}

				buff = T->g.wmadec1.outBuf.bufs[0];

				nBytes = dvtb_audDec1getOutPutBytes(&T->g.wmadec1.adecStatus.auddec_status);

				SYS_DEBUG("Frame # %d: InBytes %d, BytesConsumed %d, OutputBytes %d\n", nFrames, T->g.wmadec1.inFrameSize, frameSize, nBytes);
#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Decoded Frame Size(bytes), %d, DecTime(us), %d\n", (unsigned int) T, nFrames, nBytes, decDuration);
#endif

			}
			else
			{
				totalBytesConsumed += nBytes;
				bytesRemaining = hugeChunk - totalBytesConsumed;
			}

			if(DVEVM_ST_FAIL == dvtb_audDec1ProcessOutBuff(&T->g.aud, fileBased, buff, nBytes, T->targetFp))
			{
				SYS_ERROR("Unable to Process output buffers \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_wmaDec1ProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

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
	{
		dvtb_audDec1OutBuffFree(&T->g.wmadec1.outBuf);
		dvtb_wmaDec1HanClose(&T->g.wmadec1, T->g.eng.name);
	}

	dvtb_fileClose(&T->sourceFp, &T->targetFp);
	dvtb_exitMessage(DVEVM_ST_DECODE, "Audio", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit( );
}
