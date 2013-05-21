/*
 * dvtbAudCapture.c
 *
 * XDM0.9 Audio Encode Functionality
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
#include "dvtbAudEnc.h"
#include "dvtbAudCapture.h"
#include "dvtbDefs.h"
#include "dvtbUtils.h"

void
dvtb_audEncProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int seconds)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Audio [Capture]+[Encode] completed for %d seconds\n",	seconds);
		else
			SYS_OUT("Audio [Capture] completed for %d seconds\n", seconds);
	}
	else//File based
		SYS_OUT("Audio [File Read]+[Encode] completed\n");
}

void
dvtb_audEncInitPtrs(DvevmStAudEncInfo *aenc)
{
	int i = 0;

	aenc->ceHdl = NULL;
	aenc->aencHdl = NULL;

	aenc->inBuf.numBufs = 0;
	aenc->outBuf.numBufs = 0;
	for(i=0; i<MAX_XDM_BUFS; i++)
	{
		aenc->inBuf.bufs[i]  = NULL;
		aenc->outBuf.bufs[i] = NULL;
	}
}

DvevmStRetCode
dvtb_audEncHanInit(DvevmStAudEncInfo *aenc, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &aenc->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_audEncInit(aenc))
		{
			SYS_ERROR("Unable to initialize Speech Encoder <%s>\n",	aenc->aencName);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_audEncHanClose(DvevmStAudEncInfo *aenc, char *engName)
{
	dvtb_audEncClose(aenc);
	SYS_OUT("Audio Encoder <%s> closed\n", aenc->aencName);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&aenc->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

void
dvtb_AudEncCapture(DvevmStThreadInfo *T)
{
	int i = 0, nBytes = DVEVM_ST_FAIL, bytesToCapture = 0, count = 0, frames = 0, encDuration =0;
	char *buff = NULL, tempBuff[AUDENC_FRAME_SIZE * 4];
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, audioDeviceOpened =	DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	if (!T->targetFp)
	{
		SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit( );
	}

	if(!T->useAlgorithm)
	{
		SYS_ERROR("No DSP option is not supported \n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	if(!T->sourceFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_ENCODE, "Audio", T->useAlgorithm, fileBased);
	dvtb_audEncInitPtrs(&T->g.aenc);

	// [Capture][Encode] scenario
	do
	{
		if (T->useAlgorithm)
		{
			if(DVEVM_ST_FAIL == dvtb_audEncHanInit(&T->g.aenc, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Audio Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Audio Encoder <%s> initialized\n", T->g.aenc.aencName);
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

			SYS_OUT("Audio Device <%s> initialized for capture\n", T->g.aud.device);

			bytesToCapture = (T->g.aenc.seconds) * (AUD_FRAME_SIZE(T->g.aud.sampleRate, T->g.aud.numChannels, T->g.aud.sampleSize));
		}

		while (1)
		{
			frames++;
			buff = tempBuff;

			if (DVEVM_ST_TRUE == fileBased)
			{
				if (DVEVM_ST_FAIL == dvtb_fileRead(T->sourceFp, buff, T->g.aenc.inBuf.bufSizes[0], &nBytes))
				{
					SYS_ERROR("Error in file read \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				if (0 == nBytes || feof(T->sourceFp))
				{
					SYS_OUT("End of file reached. Exiting ...\n");
					break;
				}
			}
			else
			{
				nBytes = dvtb_audioIn(&T->g.aud, buff, AUDENC_FRAME_SIZE * 4);

				if (DVEVM_ST_FAIL == nBytes || count >= bytesToCapture)
					break;

				count += AUDENC_FRAME_SIZE * 2;
			}

			if (T->useAlgorithm)
			{
				buff = T->g.aenc.inBuf.bufs[0];

				for (i = 0; i < T->g.aenc.outBuf.numBufs; i++)
					memset(T->g.aenc.outBuf.bufs[i], 0, T->g.aenc.outBuf.bufSizes[i]);

				if (DVEVM_ST_FAIL == dvtb_audEncEncode(&T->g.aenc, &encDuration))
				{
					SYS_ERROR("Unable to encode the input buffer\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, frames, T->g.aenc.outBuf.bufSizes[0], encDuration);
#endif

				buff = T->g.aenc.outBuf.bufs[0];
			}

			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)buff, T->g.aenc.outBuf.bufSizes[0]))
			{
				SYS_ERROR("Error in writing to file.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_audEncProcessEndMessage(T->useAlgorithm, fileBased, T->g.aenc.seconds);

	if (DVEVM_ST_TRUE == audioDeviceOpened)
	{
		dvtb_audioClose(&T->g.aud);
		SYS_OUT("Audio Device <%s> closed\n", T->g.aud.device);
	}

	if (T->useAlgorithm)
		dvtb_audEncHanClose(&T->g.aenc, T->g.eng.name);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "Audio", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit( );
}
