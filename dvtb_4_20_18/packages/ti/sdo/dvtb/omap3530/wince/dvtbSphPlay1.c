/*
 * dvtbSphPlay1.c
 *
 * XDM1.0 Speech Decode functionality
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

#include "dvtbSphPlay1.h"
#include "dvtbSphPlay1Core.h"
#include "dvtbSphDec1.h"
//#include "dvtbALSAAudio.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_SphDec1Play(DvevmStThreadInfo *T)
{
	int nBytes = DVEVM_ST_FAIL, nFrames = 0, decDuration = 0;

	char *buff = NULL;
	long rem_size = 0, setpos = 0;
	unsigned int size = 0;

	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, audioDeviceOpened =	DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;
	DvevmStRetCode status = DVEVM_ST_FAIL;

	// [Decode]+Play scenario
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

	if (!T->targetFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_DECODE, "Speech", T->useAlgorithm, fileBased);
	dvtb_sphDec1InitPtrs(&T->g.sdec1);

	do
	{
		T->g.sdec1.hTime = dvtb_timeCreate();
		if(NULL == T->g.sdec1.hTime)
		{
			SYS_ERROR("Unable to create Time handle. \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FALSE == fileBased)
		{
#if 0
			if (T->useAlgorithm)
				T->g.aud.sampleRate = DEF_SPH_SAMPLERATE;

			status = dvtb_audioSetup(&T->g.aud);
			if (DVEVM_ST_FAIL == status)
			{
				SYS_ERROR("Unable to setup Audio device <%s> for playback\n", T->g.aud.device);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			audioDeviceOpened = DVEVM_ST_TRUE;

			SYS_OUT("Audio device <%s> initialized for playback\n",	T->g.aud.device);
#endif
		}

		T->g.sdec1.sdecParams.tablesPtr = NULL;

		if (T->useAlgorithm)
		{
			if (DVEVM_ST_FAIL == dvtb_sphDec1HanInit(&T->g.sdec1, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Speech decode handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Speech Decoder <%s> initialized\n", T->g.sdec1.sdecName);
		}
		else
		{
			if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&T->g.sdec1.inBuf.start, T->g.sdec1.inBuf.size))
			{
				SYS_ERROR("Unable to allocate memory for appBuffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}

		/* last frame size mismatch  */
		if ((!(strcmp(T->g.sdec1.sdecName, "g711dec"))) || (!(strcmp(T->g.sdec1.sdecName, "g722dec"))))
		{
			if(DVEVM_ST_FAIL == dvtb_getFileSize(T->sourceFp, &size))
			{
				SYS_ERROR("Unable to Get File Size \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			rem_size = size % (T->g.sdec1.inBuf.size);
		}

		while (!feof(T->sourceFp))
		{
			nFrames++;
			buff = T->g.sdec1.inBuf.start;

			if(DVEVM_ST_FAIL == dvtb_sphDec1ReadInput(&T->g.sdec1, T->g.sdec1.inBuf.size, T->sourceFp, &nBytes))
			{
				SYS_ERROR("Error in Read Input \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (nBytes < (int)T->g.sdec1.inBuf.size)
			{
				SYS_OUT("End of source file reached. Exiting ...\n");
				break;
			}

			if (T->useAlgorithm)
			{
				memset(T->g.sdec1.outBuf.start, 0, T->g.sdec1.outBuf.size);

				if(DVEVM_ST_FAIL == dvtb_sphDec1DecProcess(&T->g.sdec1, (int)T->g.sdec1.inBuf.size,  &decDuration))
				{
					SYS_ERROR("Unable to decode frame # %d\n",	nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				buff = T->g.sdec1.outBuf.start;

				nBytes = dvtb_sphDec1GetOutputBytes(&T->g.sdec1, T->g.sdec1.inBuf.size);

				SYS_DEBUG("Frame #%d, Decoded Frame Size :%d, Decoded Frame Size :%d\n", nFrames, T->g.sdec1.inBuf.size, nBytes);
#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Decoded Frame Size(bytes), %d, DecTime(us), %d\n", (unsigned int) T, nFrames, nBytes, decDuration);
#endif
			}
#if 0
			if(DVEVM_ST_FAIL == dvtb_sphDec1ProcessOutBuff(&T->g.aud, T->targetFp, (char *)buff, nBytes, fileBased))
			{
				SYS_ERROR("Unable to process output buffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
#else
			if(DVEVM_ST_FAIL == dvtb_sphDec1ProcessOutBuff(T->targetFp, (char *)buff, nBytes, fileBased))
			{
				SYS_ERROR("Unable to process output buffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
#endif
		}

		if (DVEVM_ST_TRUE == usecaseFailed) // Proceed only if usecase is successful
			break;

		/* last frame size mismatch  */
		if ((!(strcmp(T->g.sdec1.sdecName, "g711dec"))) || (!(strcmp(T->g.sdec1.sdecName, "g722dec"))))
		{
			if (rem_size != 0 && T->useAlgorithm)
			{
				setpos = size - rem_size;
				fseek(T->sourceFp, setpos, SEEK_SET);
				buff = T->g.sdec1.inBuf.start;

				if(DVEVM_ST_FAIL == dvtb_sphDec1ReadInput(&T->g.sdec1, rem_size, T->sourceFp, &nBytes))
				{
					SYS_ERROR("Error in Read Input \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				if (nBytes < rem_size)
					break;

				if (T->useAlgorithm)
				{

					if(DVEVM_ST_FAIL == dvtb_sphDec1DecProcess(&T->g.sdec1, (int)rem_size, &decDuration))
					{
						SYS_ERROR("Unable to decode frame # %d\n",	nFrames);
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					buff = T->g.sdec1.outBuf.start;

					nBytes = dvtb_sphDec1GetOutputBytes(&T->g.sdec1, rem_size);

#ifdef PERF
					SYS_PERF("Thread, %x, Frame#, %d, Decoded Frame Size(bytes), %d, DecTime(us), %d\n", (unsigned int) T, nFrames, nBytes, decDuration);
#endif
				}
#if 0
				if(DVEVM_ST_FAIL == dvtb_sphDec1ProcessOutBuff(&T->g.aud, T->targetFp, buff, nBytes, fileBased))
				{
					SYS_ERROR("Unable to process output buffer \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
#else
				if(DVEVM_ST_FAIL == dvtb_sphDec1ProcessOutBuff(T->targetFp, buff, nBytes, fileBased))
				{
					SYS_ERROR("Unable to process output buffer \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

#endif
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_sphDec1ProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

#if 0
	if (DVEVM_ST_TRUE == audioDeviceOpened)
	{
		dvtb_audioClose(&T->g.aud);
		SYS_OUT("Audio Device <%s> closed\n", T->g.aud.device);
	}
#endif

	if (T->useAlgorithm)
	{
		dvtb_sphDec1HanClose(&T->g.sdec1, T->g.eng.name);
	}
	else
	{
		if (NULL != T->g.sdec1.inBuf.start)
			dvtb_freeSingleBufCmem(T->g.sdec1.inBuf.start, T->g.sdec1.inBuf.size);
	}

	dvtb_fileClose(&T->sourceFp, &T->targetFp);
	dvtb_timeDelete(T->g.sdec1.hTime);
	dvtb_exitMessage(DVEVM_ST_DECODE, "Speech",T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThread(T);
	dvtb_waitThread();
}
