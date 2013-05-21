/*
 * dvtbAudPlay1.c
 *
 * XDM1.0 Audio Decode Functionality
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

#include "dvtbAudPlay1.h"
//#include "dvtbALSAAudio.h"
#include "dvtbAudDec1.h"
#include "dvtbMemory.h"
#include "dvtbDefs.h"
#include "dvtbUtils.h"
#include "dvtbAudPlay1Core.h"

/***************************************************Play Thread Start **********************************************************/

//#define TEST_SEM

AudioBufDesc audioDesc[AUD_OUTBUF_COUNT];

static PlayTskState tskPlayState = DELETED;
static int availableInBuff = 0;

static SemThread_Handle sem_in;
static SemThread_Handle sem_out;
static SemThread_Handle sem_block;

void
dvtb_audPlay(DvevmStThreadInfo *T)
{
	int aud_outBuffer_index = 0;
	int status = DVEVM_ST_SUCCESS;
	int nBytes;

	while (1)
	{
		SemThread_pend(sem_in, SemThread_FOREVER);
		if ((tskPlayState == EXITING) && (0 == availableInBuff))
			break;

		SemThread_pend(sem_block, SemThread_FOREVER);
		availableInBuff -= 1;
		SemThread_post(sem_block);

		if (T->useAlgorithm)
			nBytes = audioDesc[aud_outBuffer_index].aud_bufSize;
		else
			nBytes = AUD_FRAME_BUFF_SIZE;

#ifdef TEST_SEM
		status =  dvtb_fileWrite(T->targetFp, audioDesc[aud_outBuffer_index].aud_outBuffer, nBytes);
#else
//		status = dvtb_audioOut(&T->g.aud, audioDesc[aud_outBuffer_index].aud_outBuffer, nBytes);
#endif

		if (DVEVM_ST_FAIL == status)
		{
			SYS_ERROR("Audio play-back failed\n");
		}

		aud_outBuffer_index++;
		if (AUD_OUTBUF_COUNT <= aud_outBuffer_index)
			aud_outBuffer_index = 0;

		SemThread_post(sem_out);
	}
	tskPlayState = DELETED;
	dvtb_waitThread();
}
/***************************************************Play Thread End **********************************************************/

DvevmStRetCode
dvtb_audDec1SemOpen(SemThread_Handle *sem_in, int valIn, SemThread_Handle *sem_out, int valOut, SemThread_Handle *sem_block, int valBlock)
{
	DvevmStRetCode retval = DVEVM_ST_SUCCESS;

	SemThread_Params semParams;

	SemThread_Params_init(&semParams);
	semParams.mode = SemThread_Mode_COUNTING;
	semParams.name = "Sem_In";
	*sem_in = SemThread_create(valIn, &semParams);

	SemThread_Params_init(&semParams);
	semParams.mode = SemThread_Mode_COUNTING;
	semParams.name = "Sem_Out";
	*sem_out = SemThread_create(valOut, &semParams);

	SemThread_Params_init(&semParams);
	semParams.mode = SemThread_Mode_BINARY;
	semParams.name = "Sem_Block";
	*sem_block = SemThread_create(valBlock, &semParams);

	if ((NULL == *sem_in) || (NULL == *sem_out) || (NULL == *sem_block))
	{
		SYS_ERROR("sem_open() FAILED\n");
		retval = DVEVM_ST_FAIL;
	}

	return retval;
}

void
dvtb_audDec1SemClose(SemThread_Handle *sem_in, SemThread_Handle *sem_out, SemThread_Handle *sem_block)
{
	SemThread_delete(sem_in);
	SemThread_delete(sem_out);
	SemThread_delete(sem_block);
}

void
dvtb_audDec1InitThread(Thread_Params *params)
{
	Thread1_Params_init(params);
}

DvevmStRetCode
dvtb_audDec1AllocPlayThreadBuffs(AudioBufDesc *audioDesc, int size, int numBuff)
{
	int i = 0;
	DvevmStRetCode retval = DVEVM_ST_SUCCESS;

	for (i = 0; i < numBuff; i++)
	{
		if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&audioDesc[i].aud_outBuffer, size))
		{
			SYS_ERROR("Unable to allocate memory for Out Buffer %d\n", i);
			retval = DVEVM_ST_FAIL;
			break;
		}
	}

	return retval;
}

void
dvtb_audDec1InitPlayThreadBuffs(AudioBufDesc *audioDesc, int numBuff)
{
	int i = 0;
	for (i = 0; i < numBuff; i++)
		audioDesc[i].aud_outBuffer = NULL;
}

void
dvtb_audDec1FreePlayThreadBuffs(AudioBufDesc *audioDesc, int size, int numBuff)
{
	int i =0;

	for (i = 0; i < numBuff; ++i)
	{
		if(NULL != audioDesc[i].aud_outBuffer)
			dvtb_freeSingleBufCmem(audioDesc[i].aud_outBuffer, size);
	}
}
void
dvtb_AudDec1Play(DvevmStThreadInfo *T)
{
	int nBytes = DVEVM_ST_FAIL, nFrames = 0, frameSize = 0, totalBytesConsumed = 0, bytesRemaining = 0,
		buffsize = 1000000, thresh_hold = 900000, hugeChunk = 0, decDuration = 0, aud_outBuffer_index = 0,
		noOfOutChannels = 0, inFrameSize =0;
	char *buff = NULL, *inBuffer = NULL;
	unsigned int inputFileSize = 0;

	Thread_Handle thrHandle = NULL;
	Thread_Params thrParams;

	DvevmStRetCode status = DVEVM_ST_FAIL;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, audioDeviceOpened =	DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;


	if (!T->sourceFp)
	{
		SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThread(T);
		dvtb_waitThread();
	}

	if (!T->targetFp)
	{
		SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThread(T);
		dvtb_waitThread();
	}

	if (DVEVM_ST_FAIL == dvtb_audDec1SemOpen(&sem_in, 0, &sem_out, AUD_OUTBUF_COUNT-2, &sem_block, 1))
	{
		SYS_ERROR("sem_open() FAILED\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThread(T);
		dvtb_waitThread();

	}

//	dvtb_audDec1SemInit(sem_in, 0, sem_out, AUD_OUTBUF_COUNT-2, sem_block, 1);

	if (!T->targetFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_DECODE, "Audio", T->useAlgorithm, fileBased);
	dvtb_audDec1InitPtrs(&T->g.adec1);
	dvtb_audDec1InitPlayThreadBuffs(audioDesc, AUD_OUTBUF_COUNT);


	// [Decode][Play] scenario
	do
	{
		T->g.adec1.hTime = dvtb_timeCreate();
		if(NULL == T->g.adec1.hTime)
		{
			SYS_ERROR("Unable to Create Time handle. \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (T->useAlgorithm)
		{
			if (DVEVM_ST_FAIL == dvtb_audDec1HanInit(&T->g.adec1, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Audio decode handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			SYS_OUT("Audio Decoder <%s> initialized\n", T->g.adec1.adecName);
		}

		if (DVEVM_ST_FALSE == fileBased)
		{
			if (!T->useAlgorithm)
			{
#if 0
				T->g.aud.mode = SND_PCM_STREAM_PLAYBACK;
				status = dvtb_audioSetup(&T->g.aud);
				if (DVEVM_ST_FAIL == status)
				{
					SYS_ERROR("Unable to setup Audio device <%s> for playback\n", T->g.aud.device);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				audioDeviceOpened = DVEVM_ST_TRUE;
				SYS_OUT("Audio device <%s> initialized for playback\n", T->g.aud.device);
#endif
			}

			dvtb_audDec1InitThread(&thrParams);
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
		if ((int)inputFileSize < hugeChunk)
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

		if (DVEVM_ST_FAIL == dvtb_audDec1AllocPlayThreadBuffs(audioDesc, T->g.adec1.outBuf.bufSizes[0], AUD_OUTBUF_COUNT))
		{
			SYS_ERROR("Unable to allocate Buffers for play thread \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		aud_outBuffer_index = 0;
		T->g.adec1.outBuf.bufs[0] = audioDesc[aud_outBuffer_index].aud_outBuffer;
		if (T->useAlgorithm)
		{
			inFrameSize = T->g.adec1.inBuf.bufSizes[0];
		}
		else
			inFrameSize = AUD_FRAME_BUFF_SIZE;

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

			if (bytesRemaining < inFrameSize)
				nBytes = bytesRemaining;
			else
				nBytes = inFrameSize;

			buff = &inBuffer[totalBytesConsumed];
			T->g.adec1.inBuf.bufs[0] = buff;

			if (T->useAlgorithm)
			{
				T->g.adec1.inFrameSize = nBytes;
				if(DVEVM_ST_FAIL == dvtb_audDec1DecProcess(&T->g.adec1, &decDuration))
				{
					SYS_ERROR("Unable to decode frame # %d\n",	nFrames);
					if (DVEVM_ST_FALSE == fileBased)
					{
						tskPlayState = EXITING;
						SemThread_post(sem_in);
					}
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				frameSize = T->g.adec1.decFrameSize;
				totalBytesConsumed += frameSize;
				bytesRemaining = hugeChunk - totalBytesConsumed;

				buff = T->g.adec1.outBuf.bufs[0];

				nBytes = dvtb_audDec1getOutPutBytes(&T->g.adec1.adecStatus);
				audioDesc[aud_outBuffer_index].aud_bufSize = nBytes;

#if 0
				if (T->g.aud.sampleRate != T->g.adec1.adecStatus.sampleRate)
					T->g.aud.sampleRate = T->g.adec1.adecStatus.sampleRate;
#endif

				noOfOutChannels = (T->g.adec1.adecStatus.channelMode == 0) ? 1 : 2;


#ifdef PERF
				if(!T->g.adec1.pEnable)
				{
					SYS_PERF("Thread, %x, Frame#, %d, Decoded Frame Size(bytes), %d, DecTime(us), %d\n", (unsigned int) T, nFrames, nBytes, decDuration);
					SYS_DEBUG("Frame#, %d, Frame Size(bytes), %d, DecTime(us), %d\n", nFrames, frameSize, decDuration);
				}
#endif
			}
			else
			{
				memcpy(audioDesc[aud_outBuffer_index].aud_outBuffer, buff, nBytes);
				totalBytesConsumed += nBytes;
				bytesRemaining = hugeChunk - totalBytesConsumed;
			}
#ifndef TEST_SEM
			if (DVEVM_ST_TRUE == fileBased)
			{
				if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, buff, nBytes))
				{
					SYS_ERROR("Error in writing to file.\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
			}
			else
#endif
			{
#if 0
				if (T->useAlgorithm && (noOfOutChannels != T->g.aud.numChannels))
				{
					SYS_ERROR("No of channels of audio driver is not set correctly \n");
					SYS_ERROR("Decoder: number of channels %d \n", noOfOutChannels);
					SYS_ERROR("Driver: number of channels %d \n", T->g.aud.numChannels);
					usecaseFailed = DVEVM_ST_TRUE;
					tskPlayState = EXITING;
					SemThread_post(sem_in);
					break;
				}
#endif
				SemThread_post(sem_in);

				SemThread_pend(sem_block, SemThread_FOREVER);
				availableInBuff += 1;
				SemThread_post(sem_block);

				status = DVEVM_ST_SUCCESS;
				//status = dvtb_audioOut(&T->g.aud, buff, nBytes);
				SemThread_pend(sem_out, SemThread_FOREVER);
			}

			aud_outBuffer_index++;

			if (AUD_OUTBUF_COUNT == aud_outBuffer_index)
				aud_outBuffer_index = 0;

			T->g.adec1.outBuf.bufs[0] = audioDesc[aud_outBuffer_index].aud_outBuffer;
			if (nFrames == (AUD_OUTBUF_COUNT-2))
			{
#ifndef TEST_SEM
				if ((DVEVM_ST_FALSE == fileBased))
#endif
				{
					if(T->useAlgorithm)
					{
#if 0
						T->g.aud.mode = SND_PCM_STREAM_PLAYBACK;
						T->g.aud.framesize = T->g.adec1.outBuf.bufSizes[0];
						status = dvtb_audioSetup(&T->g.aud);
						if (DVEVM_ST_FAIL == status)
						{
							SYS_ERROR("Unable to setup Audio device <%s> for playback\n", T->g.aud.device);
							usecaseFailed = DVEVM_ST_TRUE;
							break;
						}
						audioDeviceOpened = DVEVM_ST_TRUE;
						SYS_OUT("Audio device <%s> initialized for playback\n", T->g.aud.device);
#endif
					}

						tskPlayState = RUNNING;
		        		thrParams.arg = (IArg)T;
				        thrParams.name = "dvtb_audPlay";
				        thrParams.priority = Thread_Priority_HIGHEST;

				        if (DVEVM_ST_FAIL == dvtb_createThread((Thread_RunFxn) dvtb_audPlay, &thrParams, &thrHandle))
				        {
						SYS_ERROR("Unable to create a thread\n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
		        		}
				}
			}

		}

#ifdef TEST_SEM
		if (DVEVM_ST_FALSE == fileBased)
#endif
		{
			if (EXITING > tskPlayState)
			{
				tskPlayState = EXITING;
				SemThread_post(sem_in);
			}
			if(NULL != thrHandle)
			{
				while (DELETED != tskPlayState)
				{
					dvtb_sleepThread(1);
				}
				dvtb_deleteThread(&thrHandle);
			}

		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_audDec1ProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

#if 0
	if (DVEVM_ST_TRUE == audioDeviceOpened)
	{
		dvtb_audioClose(&T->g.aud);
		SYS_OUT("Audio Device <%s> closed\n", T->g.aud.device);
	}
#endif

	if (NULL != inBuffer)
	{
		dvtb_freeSingleBufCmem(inBuffer, buffsize);
		inBuffer = NULL;
	}

	if (T->useAlgorithm)
		dvtb_audDec1HanClose(&T->g.adec1, T->g.eng.name);

	dvtb_audDec1FreePlayThreadBuffs(audioDesc, T->g.adec1.inBuf.bufSizes[0], AUD_OUTBUF_COUNT);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_audDec1SemClose(&sem_in, &sem_out, &sem_block);
	dvtb_timeDelete(T->g.adec1.hTime);
	dvtb_exitMessage(DVEVM_ST_DECODE, "Audio", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThread(T);
	dvtb_waitThread();
}
