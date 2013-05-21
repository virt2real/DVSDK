/*
 * dvtbAudCapture1Core.c
 *
 * XDM1.0 Audio Encode related Core Functions
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

#include "dvtbAudCapture1Core.h"
#include "dvtbUtils.h"

void
dvtb_audEnc1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int seconds)
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
dvtb_audEnc1InitPtrs(DvevmStAudEnc1Info *aenc1)
{
	int i = 0;

	aenc1->ceHdl = NULL;
	aenc1->audenc1Hdl = NULL;

	aenc1->inBuf.numBufs = 0;
	aenc1->outBuf.numBufs = 0;
	for(i=0; i<XDM_MAX_IO_BUFFERS; i++)
	{
		aenc1->inBuf.descs[i].buf  = NULL;
		aenc1->outBuf.descs[i].buf = NULL;
	}

	aenc1->ancBuf.start = NULL;
}

DvevmStRetCode
dvtb_audEnc1HanInit(DvevmStAudEnc1Info *aenc1, char *engName)
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

		if (DVEVM_ST_FAIL == dvtb_audEnc1Init(aenc1))
		{
			SYS_ERROR("Unable to initialize Audio Encoder <%s>\n",	aenc1->audenc1Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_audEnc1HanClose(DvevmStAudEnc1Info *aenc1, char *engName)
{
	dvtb_audEnc1Close(aenc1);
	SYS_OUT("Audio Encoder <%s> closed\n", aenc1->audenc1Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&aenc1->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_audEnc1EncProcess(DvevmStAudEnc1Info *aenc1, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_audEnc1Encode(aenc1, encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		aenc1->audenc1Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_audEnc1Control(aenc1))
		{
			SYS_ERROR("Unable to get status info\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

//		aenc1->audenc1Cmd = XDM_SETPARAMS;
//		if (DVEVM_ST_FAIL == dvtb_audEnc1Control(aenc1))
//		{
//			SYS_ERROR("Unable to get status info\n");
//			retCode = DVEVM_ST_FAIL;
//			break;
//		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_audEnc1numChannels(int channelMode, int *numChannels)
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
dvtb_audEnc1ReadInput(DvevmStAudioInfo *aud, DvevmStAudEnc1Info *aenc1, FILE *fp, DvevmStBool fileBased, int *nBytes)
{
	int bytesToRead = 0, capturedBytes = 0, bytesPerSample = 0;
	char *buff = NULL;

	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	bytesPerSample = aenc1->audenc1DynParams.inputBitsPerSample >> 3;

	bytesToRead = (aenc1->InSamplesPerChannel * aenc1->numChannels *bytesPerSample);
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
			aenc1->insamples = aenc1->insamples >> (aenc1->numChannels -1);
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_audEnc1Flush(DvevmStAudEnc1Info *aenc1, int nBytes, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{

		if (nBytes < aenc1->InSamplesPerChannel)
		{
			SYS_DEBUG("\tCALLING CONTROL WITH FLUSH\n");

			aenc1->audenc1Cmd = XDM_FLUSH;
			if (DVEVM_ST_FAIL == dvtb_audEnc1Control(aenc1))
			{
				SYS_ERROR("Unable to get status info\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}

			SYS_DEBUG("\tBytes read :%d\n", nBytes);

			if (0 != nBytes)
			{
				if (DVEVM_ST_FAIL == dvtb_audEnc1Encode(aenc1, encDuration))
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
