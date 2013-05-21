/*
 * dvtbSphPlay.c
 *
 * XDM0.9 Speech Decode functionality
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

#include "dvtbSphPlay.h"
#include "dvtbSphPlayCore.h"
#include "dvtbSphDec.h"
#include "dvtbALSAAudio.h"
#include "dvtbDefs.h"
#include "dvtbUtils.h"
#include "dvtbMemory.h"

void
dvtb_SphDecPlay(DvevmStThreadInfo *T)
{
	int nBytes = DVEVM_ST_FAIL, nFrames = 0, decDuration = 0;
	char *buff = NULL;

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

	dvtb_startMessage(DVEVM_ST_DECODE, "Speech", T->useAlgorithm, fileBased);
	dvtb_sphDecInitPtrs(&T->g.sdec);

	do
	{
		if (DVEVM_ST_FALSE == fileBased)
		{
			T->g.aud.sampleRate = DEF_SPH_SAMPLERATE;
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

		if (T->useAlgorithm)
		{
			if (DVEVM_ST_FAIL == dvtb_sphDecHanInit(&T->g.sdec, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Speech decode handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			SYS_OUT("Speech Decoder <%s> initialized\n", T->g.sdec.sdecName);
		}
		else
		{
			if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&T->g.sdec.inBuf.start, T->g.sdec.inBuf.size))
			{
				SYS_ERROR("Unable to allocate memory for appBuffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}

		while (!feof(T->sourceFp))
		{
			nFrames++;
			buff = T->g.sdec.inBuf.start;
			if(DVEVM_ST_FAIL == dvtb_fileRead(T->sourceFp, (char *)T->g.sdec.inBuf.start, T->g.sdec.inBuf.size, &nBytes))
			{
				SYS_ERROR("Error in file read \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (nBytes < T->g.sdec.inBuf.size)
			{
				SYS_OUT("End of source file reached. Exiting ...\n");
				break;
			}

			if (T->useAlgorithm)
			{
				if(DVEVM_ST_FAIL == dvtb_sphDecDecProcess(&T->g.sdec, &decDuration))
				{
					SYS_ERROR("Unable to decode frame # %d\n",	nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				buff = T->g.sdec.outBuf.start;
				nBytes = T->g.sdec.inBuf.size * 4;
				SYS_DEBUG("Thread, %x, Frame #%d, Encoded Frame Size :%d, Decoded Frame Size :%d\n", (unsigned int) T, nFrames, T->g.sdec.inBuf.size, nBytes);
#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Decoded Frame Size(bytes), %d, DecTime(us), %d\n", (unsigned int) T, nFrames, nBytes, decDuration);
#endif
			}

			if(DVEVM_ST_FAIL == dvtb_sphDecProcessOutBuff(&T->g.aud, T->targetFp, (char *)buff, nBytes, fileBased))
			{
				SYS_ERROR("Unable to process output buffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}

	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_sphDecProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

	if (DVEVM_ST_TRUE == audioDeviceOpened)
	{
		dvtb_audioClose(&T->g.aud);
		SYS_OUT("Audio Device <%s> closed\n", T->g.aud.device);
	}

	if (T->useAlgorithm)
	{
		dvtb_sphDecHanClose(&T->g.sdec, T->g.eng.name);
	}
	else
	{
		if (NULL != T->g.sdec1.inBuf.start)
			dvtb_freeSingleBufCmem(T->g.sdec.inBuf.start, T->g.sdec1.inBuf.size);
	}


	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_DECODE, "Speech",T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit( );
}
