/*
 * dvtbSphCapture.c
 *
 * XDM0.9 Speech Encode functionality
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

#include "dvtbALSAAudio.h"
#include "dvtbSphCapture.h"
#include "dvtbSphCaptureCore.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_SphEncCapture(DvevmStThreadInfo *T)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	int nBytes = DVEVM_ST_FAIL, bytesToCapture = 0,	count = 0, frameCount = 0, encDuration = 0;

	char tempBuff[SPHENC_FRAME_SIZE * 4], *buff = NULL;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, audioDeviceOpened =	DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	if (!T->targetFp)
	{
		SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	if(!T->sourceFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_ENCODE, "Speech", T->useAlgorithm, fileBased);
	dvtb_sphEncInitPtrs(&T->g.senc);


	// [Capture][Encode] scenario
	do
	{
		if (T->useAlgorithm)
		{
			T->g.aud.sampleRate = 8000;
			T->g.senc.inBuf.size = SPHENC_FRAME_SIZE * 2;
			T->g.senc.outBuf.size = SPHENC_FRAME_SIZE;

			if(DVEVM_ST_FAIL == dvtb_sphEncHanInit(&T->g.senc, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Speech Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Speech Encoder <%s> initialized\n", T->g.senc.sencName);

		}
		else
		{
			T->g.senc.inBuf.size = SPHENC_FRAME_SIZE * 4 * 2;
			if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&T->g.senc.inBuf.start, T->g.senc.inBuf.size))
			{
				SYS_ERROR("Unable to allocate memory for appBuffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}

		if (DVEVM_ST_FALSE == fileBased)
		{
			T->g.aud.mode = DVEVM_ST_CAPTURE;
			retval = dvtb_audioSetup(&T->g.aud);
			if (DVEVM_ST_FAIL == retval)
			{
				SYS_ERROR("Unable to initialize Audio device <%s> for capture\n", T->g.aud.device);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			audioDeviceOpened = DVEVM_ST_TRUE;
			SYS_DEBUG("Audio Device <%s> initialized for capture\n", T->g.aud.device);
			bytesToCapture = (T->g.senc.seconds) * (AUD_FRAME_SIZE(T->g.aud.sampleRate, T->g.aud.numChannels, T->g.aud.sampleSize));
		}

		while (1)
		{
			buff = tempBuff;

			if(DVEVM_ST_FAIL == dvtb_sphEncReadInput(&T->g.aud, buff, T->sourceFp, SPHENC_FRAME_SIZE * 4, fileBased, &nBytes))
			{
				SYS_ERROR("Read Input fails \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_TRUE == fileBased)
			{
				if (0 == nBytes || feof(T->sourceFp))
				{
					SYS_OUT("End of source file reached. Exiting ...\n");
					break;
				}
			}
			else
			{
				if (count >= bytesToCapture)
				{
					break;
				}

				count += SPHENC_FRAME_SIZE * 4;
			}

			if (T->useAlgorithm)
			{
				if (DVEVM_ST_FAIL == dvtb_sphEncEncProcess(&T->g.senc, buff, &encDuration))
				{
					SYS_ERROR("Encode Process fails \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
				buff = T->g.senc.outBuf.start;
			}
			else
				T->g.senc.outBuf.size = SPHENC_FRAME_SIZE * 4;

			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)buff, T->g.senc.outBuf.size))
			{
				SYS_ERROR("Error in writing to file.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			frameCount++;
#ifdef PERF
			SYS_PERF("Thread, %x, Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, frameCount, T->g.senc.outBuf.size, encDuration);
#endif

		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_sphEncProcessEndMessage(T->useAlgorithm, fileBased, T->g.senc.seconds);

	if (DVEVM_ST_TRUE == audioDeviceOpened)
	{
		dvtb_audioClose(&T->g.aud);
		SYS_OUT("Audio Device <%s> closed\n", T->g.aud.device);
	}


	if (T->useAlgorithm)
		dvtb_sphEncHanClose(&T->g.senc, T->g.eng.name);
	else
	{
		if (NULL != T->g.senc.inBuf.start)
			dvtb_freeSingleBufCmem(T->g.senc.inBuf.start, T->g.senc.inBuf.size);
	}

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "Speech", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
