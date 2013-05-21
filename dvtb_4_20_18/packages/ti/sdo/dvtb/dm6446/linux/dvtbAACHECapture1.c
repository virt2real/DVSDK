/*
 * dvtbAACHECapture1.c
 *
 * XDM1.0 AACHE Encode Functionality
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
#include "dvtbAACHEEnc1.h"
#include "dvtbAACHECapture1.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_aacheEnc1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int seconds)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("AACHE [Capture]+[Encode] completed for %d seconds\n",	seconds);
		else
			SYS_OUT("AACHE [Capture] completed for %d seconds\n", seconds);
	}
	else//File based
		SYS_OUT("AACHE [File Read]+[Encode] completed\n");
}

void
dvtb_aacheEnc1InitPtrs(DvevmStAacHeEnc1Info *aacheenc1)
{
	int i = 0;

	aacheenc1->ceHdl = NULL;
	aacheenc1->aacenc1Hdl = NULL;

	aacheenc1->inBuf.numBufs = 0;
	aacheenc1->outBuf.numBufs = 0;
	for(i=0; i<XDM_MAX_IO_BUFFERS; i++)
	{
		aacheenc1->inBuf.descs[i].buf  = NULL;
		aacheenc1->outBuf.descs[i].buf = NULL;
	}

	aacheenc1->ancBuf.start = NULL;
}

DvevmStRetCode
dvtb_aacheEnc1HanInit(DvevmStAacHeEnc1Info *aacheenc1, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &aacheenc1->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_aacheEnc1Init(aacheenc1))
		{
			SYS_ERROR("Unable to initialize Speech Encoder <%s>\n",	aacheenc1->aacenc1Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_aacheEnc1HanClose(DvevmStAacHeEnc1Info *aacheenc1, char *engName)
{
	dvtb_aacheEnc1Close(aacheenc1);
	SYS_OUT("Audio Encoder <%s> closed\n", aacheenc1->aacenc1Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&aacheenc1->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_aacheEnc1EncProcess(DvevmStAacHeEnc1Info *aacheenc1, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_aacheEnc1Encode(aacheenc1, encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		aacheenc1->aenc1Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_aacheEnc1Control(aacheenc1))
		{
			SYS_ERROR("Unable to get status info\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_aacheEnc1ReadInput(DvevmStAudioInfo *aud, DvevmStAacHeEnc1Info *aacheenc1, FILE *fp, DvevmStBool fileBased, int *nBytes)
{
	int bytesToRead = 0, capturedBytes = 0;
	char *buff = NULL;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	bytesToRead = (AUDENC1_FRAME_SIZE * (aacheenc1->aacenc1Params.audenc_params.channelMode + 1) * 2);
	buff = (char *)aacheenc1->inBuf.descs[0].buf;

	if (DVEVM_ST_FALSE != fileBased)
	{
		if (DVEVM_ST_FAIL == dvtb_fileRead(fp, buff, bytesToRead, nBytes))
		{
			SYS_ERROR("Error in file read \n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			aacheenc1->insamples = *nBytes / 2;
			aacheenc1->insamples = aacheenc1->insamples >> aacheenc1->aacenc1Params.audenc_params.channelMode;
		}
	}
	else
	{
		*nBytes = dvtb_audioIn(aud,(char *) buff, bytesToRead);
		if(DVEVM_ST_FAIL == *nBytes)
		{
			SYS_ERROR("Error in Getting Reading from Driver \n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			capturedBytes = bytesToRead;
			aacheenc1->insamples =  capturedBytes/2 ;
			aacheenc1->insamples = aacheenc1->insamples >> aacheenc1->aacenc1Params.audenc_params.channelMode;
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_aacheEnc1Flush(DvevmStAacHeEnc1Info *aacheenc1, int nBytes, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{

		if (nBytes < AUDENC1_FRAME_SIZE)
		{
			SYS_DEBUG("\tCALLING CONTROL WITH FLUSH\n");

			aacheenc1->aenc1Cmd = XDM_FLUSH;
			if (DVEVM_ST_FAIL == dvtb_aacheEnc1Control(aacheenc1))
			{
				SYS_ERROR("Unable to get status info\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}

		SYS_DEBUG("\tBytes read :%d\n", nBytes);

		if (0 == nBytes)
		{
			if (DVEVM_ST_FAIL == dvtb_aacheEnc1Encode(aacheenc1, encDuration))
			{
				SYS_ERROR("Unable to encode the input buffer\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}

		}
	}while(DVEVM_ST_FALSE);

	return retCode;

}

void
dvtb_AacheEnc1Capture(DvevmStThreadInfo *T)
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

	dvtb_startMessage(DVEVM_ST_ENCODE, "AACHE", T->useAlgorithm, fileBased);
	dvtb_aacheEnc1InitPtrs(&T->g.aacheenc1);

	// [Capture][Encode] scenario
	do
	{
		if (T->useAlgorithm)
		{
			if(DVEVM_ST_FAIL == dvtb_aacheEnc1HanInit(&T->g.aacheenc1, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Audio Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Audio Encoder <%s> initialized\n", T->g.aacheenc1.aacenc1Name);

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

			bytesToCapture = (T->g.aacheenc1.seconds) * (AUD_FRAME_SIZE(T->g.aud.sampleRate, T->g.aud.numChannels, T->g.aud.sampleSize));

		}

		while (1)
		{
			frames++;

			if (DVEVM_ST_FAIL == dvtb_aacheEnc1ReadInput(&T->g.aud, &T->g.aacheenc1, T->sourceFp, fileBased, &nBytes))
			{
				SYS_ERROR("Error in Read Input\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}


			if (DVEVM_ST_TRUE == fileBased)
			{
				if(DVEVM_ST_FAIL == dvtb_aacheEnc1Flush(&T->g.aacheenc1, nBytes, &encDuration))
				{
					SYS_ERROR("Unable to Flush\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				if (0 == nBytes)
				{
#ifdef PERF
					SYS_PERF("Thread, %x, Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, frames, T->g.aacheenc1.outsamples, encDuration);
#endif
					if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)T->g.aacheenc1.outBuf.descs[0].buf, T->g.aacheenc1.outsamples))
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

				count += (AUDENC1_FRAME_SIZE*(T->g.aacheenc1.aacenc1Params.audenc_params.channelMode+1)*2);
			}

			if (T->useAlgorithm)
			{
				if (DVEVM_ST_FAIL == dvtb_aacheEnc1EncProcess(&T->g.aacheenc1, &encDuration))
				{
					SYS_ERROR("Encode Process fails \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, frames, T->g.aacheenc1.outsamples, encDuration);
#endif
				SYS_DEBUG("\tBytes generated :%d\n", T->g.aacheenc1.outsamples);

			}


			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)T->g.aacheenc1.outBuf.descs[0].buf, T->g.aacheenc1.outsamples))
			{
				SYS_ERROR("Error in writing to file.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_aacheEnc1ProcessEndMessage(T->useAlgorithm, fileBased, T->g.aacheenc1.seconds);

	if (DVEVM_ST_TRUE == audioDeviceOpened)
	{
		dvtb_audioClose(&T->g.aud);
		SYS_OUT("Audio Device <%s> closed\n", T->g.aud.device);
	}

	if (T->useAlgorithm)
		dvtb_aacheEnc1HanClose(&T->g.aacheenc1, T->g.eng.name);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "AACHE", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
