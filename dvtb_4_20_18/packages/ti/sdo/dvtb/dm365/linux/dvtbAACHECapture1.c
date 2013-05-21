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
#include "dvtbDefs.h"
#include "dvtbUtils.h"

void
dvtb_aacheEnc1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int seconds)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("AAC [Capture]+[Encode] completed for %d seconds\n",	seconds);
		else
			SYS_OUT("AAC [Capture] completed for %d seconds\n", seconds);
	}
	else//File based
		SYS_OUT("AAC [File Read]+[Encode] completed\n");
}

void
dvtb_aacheEnc1InitPtrs(DvevmStAacHeEnc1Info *aenc1)
{
	int i = 0;

	aenc1->ceHdl = NULL;
	aenc1->aacenc1Hdl = NULL;

	aenc1->inBuf.numBufs = 0;
	aenc1->outBuf.numBufs = 0;
	for(i=0; i<XDM_MAX_IO_BUFFERS; i++)
	{
		aenc1->inBuf.descs[i].buf  = NULL;
		aenc1->outBuf.descs[i].buf = NULL;
	}

	aenc1->ancBuf.start = NULL;
	aenc1->executionDone = 0;
}

DvevmStRetCode
dvtb_aacheEnc1HanInit(DvevmStAacHeEnc1Info *aenc1, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &aenc1->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_aacheEnc1Init(aenc1))
		{
			SYS_ERROR("Unable to initialize AAC Encoder <%s>\n",	aenc1->aacenc1Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_aacheEnc1HanClose(DvevmStAacHeEnc1Info *aenc1, char *engName)
{
	dvtb_aacheEnc1Close(aenc1);
	SYS_OUT("Audio Encoder <%s> closed\n", aenc1->aacenc1Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&aenc1->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_aacheEnc1EncProcess(DvevmStAacHeEnc1Info *aenc1, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_aacheEnc1Encode(aenc1, encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		aenc1->aenc1Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_aacheEnc1Control(aenc1))
		{
			SYS_ERROR("Unable to get status info\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}
DvevmStRetCode
dvtb_aacheEnc1numChannels(int channelMode, int *numChannels)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	switch(channelMode)
	{
		case IAUDIO_1_0:
			*numChannels = 1;
			break;
		case IAUDIO_2_0:
			*numChannels = 2;
			break;
		case IAUDIO_11_0:
			*numChannels = 2;
			break;
		default:
			SYS_ERROR("channel mode %d is not supported \n ",channelMode);
			*numChannels = 2;
			retCode = DVEVM_ST_FAIL;
	}
	return retCode;
}

DvevmStRetCode
dvtb_aacheEnc1ReadInput(DvevmStAudioInfo *aud, DvevmStAacHeEnc1Info *aenc1, FILE *fp, DvevmStBool fileBased, int *nBytes)
{
	int bytesToRead = 0, capturedBytes = 0, bytesPerSample = 0;
	char *buff = NULL;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		bytesPerSample = aenc1->aacenc1DynParams.audenc_dynamicparams.inputBitsPerSample >> 3;
		
		bytesToRead = (aenc1->framesize * aenc1->numChannels * bytesPerSample);

		buff = (char *)aenc1->inBuf.descs[0].buf;
	
		if (DVEVM_ST_FALSE != fileBased)
		{
			if (DVEVM_ST_FAIL == dvtb_fileRead(fp, buff, bytesToRead, nBytes))
			{
				SYS_ERROR("Error in file read \n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				aenc1->insamples = *nBytes / bytesPerSample;
				aenc1->insamples = aenc1->insamples >> (aenc1->numChannels-1);
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
				aenc1->insamples =  capturedBytes / bytesPerSample ;
				aenc1->insamples = aenc1->insamples >> aenc1->aacenc1Params.audenc_params.channelMode;
			}
		}
	}while(0);	

	return retCode;
}

DvevmStRetCode
dvtb_aacheEnc1Flush(DvevmStAacHeEnc1Info *aenc1, int nBytes, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	int bytesToRead = 0, bytesPerSample = 0;
	
	do
	{
		bytesPerSample = aenc1->aacenc1DynParams.audenc_dynamicparams.inputBitsPerSample >> 3;
		bytesToRead = (aenc1->framesize * aenc1->numChannels * bytesPerSample);

		if (nBytes < bytesToRead)
		{
			SYS_DEBUG("\tCALLING CONTROL WITH FLUSH\n");

			aenc1->aenc1Cmd = XDM_FLUSH;
			if (DVEVM_ST_FAIL == dvtb_aacheEnc1Control(aenc1))
			{
				SYS_ERROR("Unable to get status info\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}

			SYS_DEBUG("\tBytes read :%d\n", nBytes);
	
			if (0 != nBytes)
			{
				if (DVEVM_ST_FAIL == dvtb_aacheEnc1Encode(aenc1, encDuration))
				{
					SYS_ERROR("Unable to encode the input buffer\n");
					retCode = DVEVM_ST_FAIL;
					break;
				}

			}
		}
	}while(DVEVM_ST_FALSE);

	return retCode;

}

void
dvtb_aacheEnc1InitFrameSize(DvevmStAacHeEnc1Info *aenc1)
{
	switch(aenc1->outObjectType)
	{
		case AACENC_OBJ_TYP_LC:
			aenc1->framesize = AACLCENC1_FRAME_SIZE;
			break;

		case AACENC_OBJ_TYP_HEAAC:
			aenc1->framesize = AACHEENC1_FRAME_SIZE;
			break;

		case AACENC_OBJ_TYP_PS:
			aenc1->framesize = AACHEENC1_FRAME_SIZE;
			break;

		default :
			SYS_ERROR("Unknown outObjectType: setting to AACENC_OBJ_TYP_HEAAC \n");
			aenc1->framesize = AACHEENC1_FRAME_SIZE;
	}
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

	dvtb_startMessage(DVEVM_ST_ENCODE, "AAC", T->useAlgorithm, fileBased);
	dvtb_aacheEnc1InitPtrs(&T->g.aacheenc1);
	dvtb_aacheEnc1InitFrameSize(&T->g.aacheenc1);

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
		
		if(DVEVM_ST_FAIL == dvtb_aacheEnc1numChannels(T->g.aacheenc1.aacenc1Params.audenc_params.channelMode,&T->g.aacheenc1.numChannels))
		{
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		while (1)
		{
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

				count += (T->g.aacheenc1.framesize*T->g.aacheenc1.numChannels*2);
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
			if(T->g.aacheenc1.executionDone)
				break;
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

	dvtb_exitMessage(DVEVM_ST_ENCODE, "AAC", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit( );
}
