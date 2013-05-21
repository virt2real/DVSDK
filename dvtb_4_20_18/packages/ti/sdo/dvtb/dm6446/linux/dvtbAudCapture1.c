/*
 * dvtbAudCapture1.c
 *
 * XDM1.0 Audio Encode Functionality
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

#include "dvtbAudCapture1.h"
#include "dvtbAudCapture1Core.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_AudEnc1Capture(DvevmStThreadInfo *T)
{
	int nBytes = DVEVM_ST_FAIL, bytesToCapture = 0, count = 0, frames = 0, encDuration = 0;
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, audioDeviceOpened =	DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	if (!T->targetFp)
	{
		SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
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

	if(!T->sourceFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_ENCODE, "Audio", T->useAlgorithm, fileBased);
	dvtb_audEnc1InitPtrs(&T->g.aenc1);

	// [Capture][Encode] scenario
	do
	{
		if (T->useAlgorithm)
		{

			if(DVEVM_ST_FAIL == dvtb_audEnc1HanInit(&T->g.aenc1, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Audio Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Audio Encoder <%s> initialized\n", T->g.aenc1.audenc1Name);

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

			bytesToCapture = (T->g.aenc1.seconds) * (AUD_FRAME_SIZE(T->g.aud.sampleRate, T->g.aud.numChannels, T->g.aud.sampleSize));

		}

		while (1)
		{
			frames++;

			if (DVEVM_ST_FAIL == dvtb_audEnc1ReadInput(&T->g.aud, &T->g.aenc1, T->sourceFp, fileBased, &nBytes))
			{
				SYS_ERROR("Error in Read Input\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_TRUE == fileBased)
			{

				if(DVEVM_ST_FAIL == dvtb_audEnc1Flush(&T->g.aenc1, nBytes, &encDuration))
				{
					SYS_ERROR("Unable to Flush\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				if (0 == nBytes)
				{
#ifdef PERF
					SYS_PERF("Thread, %x, Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, frames, T->g.aenc1.outsamples, encDuration);
#endif
					if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)T->g.aenc1.outBuf.descs[0].buf, T->g.aenc1.outsamples))
					{
						SYS_ERROR("Error in writing to file.\n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					SYS_OUT("End of file reached. Exiting ...\n");
					break;
				}
			}
			else
			{
				if(count >= bytesToCapture)
					break;

				count += (AUDENC1_FRAME_SIZE*(T->g.aenc1.audenc1Params.channelMode+1)*2);
			}

			if (T->useAlgorithm)
			{
				if (DVEVM_ST_FAIL == dvtb_audEnc1EncProcess(&T->g.aenc1, &encDuration))
				{
					SYS_ERROR("Encode Process fails \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, frames, T->g.aenc1.outsamples, encDuration);
#endif

				SYS_DEBUG("\tBytes generated :%d\n", T->g.aenc1.outsamples);
			}



			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)T->g.aenc1.outBuf.descs[0].buf, T->g.aenc1.outsamples))
			{
				SYS_ERROR("Error in writing to file.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_audEnc1ProcessEndMessage(T->useAlgorithm, fileBased, T->g.aenc1.seconds);

	if (DVEVM_ST_TRUE == audioDeviceOpened)
	{
		dvtb_audioClose(&T->g.aud);
		SYS_OUT("Audio Device <%s> closed\n", T->g.aud.device);
	}

	if (T->useAlgorithm)
		dvtb_audEnc1HanClose(&T->g.aenc1, T->g.eng.name);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "Audio", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
