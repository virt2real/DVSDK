/*
 * dvtbSphCapture1.c
 *
 * XDM1.0 Speech Encode functionality
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
#include "dvtbSphCapture1.h"
#include "dvtbSphCapture1Core.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_SphEnc1Capture(DvevmStThreadInfo *T)
{
	int nBytes = DVEVM_ST_FAIL, appBuffSize, appBuffFilled, bytesToCapture = 0,
		count = 0, frames = 0, inBuffSize = 0, bytesToRead = 0, encDuration = 0;

	long rem_size = 0, setpos = 0;
	unsigned int size = 0;

	char *buff = NULL, *appBuff = NULL, *appBuffPtr = NULL, *inBuff = NULL;

	DvevmStRetCode retval = DVEVM_ST_FAIL;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, audioDeviceOpened =	DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	T->g.senc1.sencParams.tablesPtr = NULL;
	appBuffPtr = appBuff;

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
	dvtb_sphEnc1InitPtrs(&T->g.senc1);

	// [Capture][Encode] scenario
	do
	{
		if (T->useAlgorithm)
		{
			appBuffFilled = 0;
			appBuffSize = (SPHENC1_FRAME_SIZE * 4) * 5;

			if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&appBuff, appBuffSize))
			{
				SYS_ERROR("Unable to allocate memory for appBuffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			appBuffPtr = appBuff;
			T->g.aud.sampleRate = 8000;

			if(DVEVM_ST_FAIL == dvtb_sphEnc1HanInit(&T->g.senc1, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Speech Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Speech Encoder <%s> initialized\n", T->g.senc1.sencName);
		}
		else
		{
			appBuffFilled = 0;
			appBuffSize = (SPHENC1_FRAME_SIZE * 4) * 10;

			if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&appBuff, appBuffSize))
			{
				SYS_ERROR("Unable to allocate memory for appBuffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			appBuffPtr = appBuff;
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

			bytesToCapture = (T->g.senc1.seconds) * (AUD_FRAME_SIZE(T->g.aud.sampleRate, T->g.aud.numChannels, T->g.aud.sampleSize));
		}
		else
		{
			if (!(strcmp(T->g.senc1.sencName, "g711enc")))
			{
				if(DVEVM_ST_FAIL == dvtb_getFileSize(T->sourceFp, &size))
				{
					SYS_ERROR("Unable to Get File Size \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				rem_size = size % (T->g.senc1.inBuf.size);
			}
		}

		inBuffSize = dvtb_sphEnc1GetInputBuffSize(&T->g.senc1, fileBased);
		if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&inBuff, inBuffSize))
		{
			SYS_ERROR("Unable to allocate memory for Input Buffer \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		bytesToRead = dvtb_sphEnc1BytesToRead(&T->g.senc1, fileBased);

		while (1)
		{
			buff = inBuff;

			frames++;

			if (DVEVM_ST_FAIL == dvtb_sphEnc1ReadInput(&T->g.aud, buff, T->sourceFp, bytesToRead, fileBased, &nBytes))
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

				count += SPHENC1_FRAME_SIZE * 4;
			}

			if (T->useAlgorithm)
			{
				if (DVEVM_ST_FAIL == dvtb_sphEnc1EncProcess(&T->g.senc1, buff, fileBased, &encDuration))
				{
					SYS_ERROR("Encode Process fails \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				buff = T->g.senc1.outBuf.start;

#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, frames, T->g.senc1.outBuf.size, encDuration);
#endif
			}
			else
				T->g.senc1.outBuf.size = SPHENC1_FRAME_SIZE * 4;

			if (!(strcmp(T->g.senc1.sencName, "ilbcenc")))
			{
				if (T->g.senc1.sencParams.codecSelection == 0)
					fwrite(buff, 1, PRM_SIZE_20, T->targetFp);
				else
					fwrite(buff, 1, PRM_SIZE_30, T->targetFp);
			}
			else if (!(strcmp(T->g.senc1.sencName, "g722enc")))
				fwrite(buff, 1, (T->g.senc1.outBuf.size) * 2, T->targetFp);
			else
			{
				memcpy(appBuffPtr, buff, T->g.senc1.outBuf.size);
				appBuffPtr += T->g.senc1.outBuf.size;
				appBuffFilled += T->g.senc1.outBuf.size;

				if (appBuffFilled == appBuffSize)
				{
					/* Store the processed frame to target file */
					if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)appBuff, appBuffSize))
					{
						SYS_ERROR("Error in writing to file.\n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					appBuffPtr = appBuff;
					appBuffFilled = 0;
				}
			}
		}

		if (DVEVM_ST_TRUE == usecaseFailed)// Proceed only when use case is successful
			break;

		if (!(strcmp(T->g.senc1.sencName, "g711enc")))
		{
			if (DVEVM_ST_TRUE == fileBased)
			{
				if (rem_size != 0)
				{
					SYS_OUT("ENTERED rem_size %ld\n", rem_size);
					setpos = size - rem_size;
					buff = inBuff;

					fseek(T->sourceFp, setpos, SEEK_SET);

					if(DVEVM_ST_FAIL == dvtb_sphEnc1ReadInput(NULL, buff, T->sourceFp, rem_size, DVEVM_ST_TRUE, &nBytes))
					{
						SYS_ERROR("Read Input fails \n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					if(DVEVM_ST_FAIL == dvtb_inputFileToProcessbuff((char *) buff, (char *) T->g.senc1.inBuf.start, rem_size))
					{
						SYS_ERROR("Unable to copy input file to process buff  \n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					memset(T->g.senc1.outBuf.start, 0, rem_size);

					if (DVEVM_ST_FAIL == dvtb_sphEnc1Encode(&T->g.senc1, &encDuration))
					{
						SYS_ERROR("Unable to encode the input2 buffer\n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

#ifdef PERF
					SYS_PERF("Thread, %x, Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, frames, T->g.senc1.outBuf.size, encDuration);
#endif

					buff = T->g.senc1.outBuf.start;
					memcpy(appBuffPtr, buff, (rem_size / 2));
					appBuffPtr += T->g.senc1.outBuf.size;
					appBuffFilled += (rem_size / 2);

					/* Store the processed frame to target file */
					if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)appBuff, appBuffFilled))
					{
						SYS_ERROR("Error in writing to file.\n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					appBuffPtr = appBuff;
					appBuffFilled = 0;
				}
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_sphEnc1ProcessEndMessage(T->useAlgorithm, fileBased, T->g.senc1.seconds);

	if (DVEVM_ST_TRUE == audioDeviceOpened)
	{
		dvtb_audioClose(&T->g.aud);
		SYS_OUT("Audio Device <%s> closed\n", T->g.aud.device);
	}

	if (T->useAlgorithm)
		dvtb_sphEnc1HanClose(&T->g.senc1, T->g.eng.name);

	if(NULL != appBuff)
		dvtb_freeSingleBufCmem(appBuff, appBuffSize);

	if(NULL != inBuff)
		dvtb_freeSingleBufCmem(inBuff, inBuffSize);


	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "Speech", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
