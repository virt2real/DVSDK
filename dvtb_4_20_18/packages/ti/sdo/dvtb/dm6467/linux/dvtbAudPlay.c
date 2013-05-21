/*
 * dvtbAudPlay.c
 *
 * XDM0.9 Audio Decode Functionality
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

#include "dvtbAudPlay.h"
#include "dvtbALSAAudio.h"
#include "dvtbAudDec.h"
#include "dvtbDefs.h"
#include "dvtbUtils.h"
#include "dvtbMemory.h"

#include <ti/sdo/ce/trace/gt.h>

void
dvtb_audDecProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Audio [Decode]+[Play] completed for <%d> frames\n", nFrames - 1);
		else
			SYS_OUT("Audio [Play] completed for <%d> frames\n", nFrames - 1);
	}
	else//File based
		SYS_OUT("Audio [Decode]+[dump] completed for <%d> frames\n", nFrames - 1);
}

void
dvtb_audDecInitPtrs(DvevmStAudDecInfo *ad)
{
	ad->ceHdl = NULL;
	ad->adecHdl = NULL;

	ad->inBuf.start = NULL;
	ad->outBuf.start = NULL;
}

DvevmStRetCode
dvtb_audDecHanInit(DvevmStAudDecInfo *ad, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &ad->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}


		if (DVEVM_ST_FAIL == dvtb_audDecInit(ad))
		{
			SYS_ERROR("Unable to initialize Audio Decoder <%s>\n", ad->adecName);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_audDecHanClose(DvevmStAudDecInfo *ad, char *engName)
{
	dvtb_audDecClose(ad);
	SYS_OUT("Audio Decoder <%s> closed\n", ad->adecName);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&ad->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

int
dvtb_audDecSetSampleRate(DvevmStAudioInfo *aud, int sampleRate)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (aud->sampleRate != sampleRate)
	{
		aud->sampleRate = sampleRate;
		if (DVEVM_ST_FAIL == dvtb_audioControl(aud))
		{
			SYS_ERROR("Unable to set the sample rate\n");
			retCode = DVEVM_ST_FAIL;
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_audDecProcessOutBuff(DvevmStAudioInfo *aud, DvevmStBool fileBased, char *buff, int nBytes, FILE *fp)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_TRUE == fileBased)
	{
		if(DVEVM_ST_FAIL ==  dvtb_fileWrite(fp, buff, nBytes))
		{
			SYS_ERROR("Error in writing to file.\n");
			retCode = DVEVM_ST_FAIL;
		}
	}
	else
	{
		if (DVEVM_ST_FAIL == dvtb_audioOut(aud, buff, nBytes))
		{
			SYS_ERROR("Unable to write into target device\n");
			retCode = DVEVM_ST_FAIL;
		}
	}

	return retCode;
}

int
dvtb_audDecgetOutPutBytes(AUDDEC_Status *adecStatus)
{
	int nBytes = 0, noOfOutChannels = 0;

	switch (adecStatus->numChannels)
	{
	case IAUDIO_MONO:
		noOfOutChannels = 1;
		break;

	case IAUDIO_STEREO:
		noOfOutChannels = 2;
		break;

	default:
		SYS_OUT("&&&&&&&&&&&&&&&& ********** Default *************\n");
		noOfOutChannels = 2;
		break;
	}
	nBytes = adecStatus->frameLen * adecStatus->outputBitsPerSample / 8 * noOfOutChannels;

	return nBytes;
}

DvevmStRetCode
dvtb_audDecDecProcess(DvevmStAudDecInfo *ad, int *decDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_audDecDecode(ad, decDuration))
		{
			SYS_ERROR("Unable to decode <%s> \n", ad->adecName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		ad->adecCmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_audDecControl(ad))
		{
			SYS_ERROR("Unable to get the status \n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_AudDecPlay(DvevmStThreadInfo *T)
{
	int nBytes = DVEVM_ST_FAIL, nFrames = 0, frameSize = 0, decDuration = 0;
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

	dvtb_startMessage(DVEVM_ST_DECODE, "Audio", T->useAlgorithm, fileBased);
	dvtb_audDecInitPtrs(&T->g.adec);

	// [Decode][Play] scenario
	do
	{
		if (DVEVM_ST_FALSE == fileBased)
		{
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
			if (DVEVM_ST_FAIL == dvtb_audDecHanInit(&T->g.adec, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Speech decode handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Audio Decoder <%s> initialized\n", T->g.adec.adecName);
		}
		else
		{
			if(DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&T->g.adec.inBuf.start, T->g.adec.inBuf.size))
			{
				SYS_ERROR("Unable to allocate memory for In Buffer\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}

		while (!feof(T->sourceFp))
		{
			nFrames++;
			buff = T->g.adec.inBuf.start;

			if (DVEVM_ST_FAIL == dvtb_fileRead(T->sourceFp, buff, T->g.adec.inBuf.size, &nBytes))
			{
				SYS_ERROR("Error in file read \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (0 == nBytes)
			{
				SYS_OUT("End of file reached. Exiting...\n");
				break;
			}

			if (T->useAlgorithm)
			{
				T->g.adec.inFrameSize = nBytes;
				memset(T->g.adec.outBuf.start, 0, T->g.adec.outBuf.size);

				if(DVEVM_ST_FAIL == dvtb_audDecDecProcess(&T->g.adec, &decDuration))
				{
					SYS_ERROR("Unable to decode frame # %d\n",	nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				frameSize = T->g.adec.decFrameSize;
				if (DVEVM_ST_FAIL == fseek(T->sourceFp, -(nBytes - frameSize), SEEK_CUR))
				{
					SYS_ERROR("Cannot set the file pointer to next frame position\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				if (DVEVM_ST_FALSE == fileBased)
				{
					SYS_OUT("Sample rate from codec is not same as what is set in driver. Driver: %d, Codec: %d\n", (int) T->g.aud.sampleRate, (int) T->g.adec.adecStatus.sampleRate);
					SYS_OUT("Resetting sample rate to %d\n", (int) T->g.adec.adecStatus.sampleRate);

					if(DVEVM_ST_FAIL == dvtb_audDecSetSampleRate(&T->g.aud, T->g.adec.adecStatus.sampleRate))
					{
						SYS_ERROR("Unable to Set Sample rate \n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}
				}

				buff = T->g.adec.outBuf.start;

				nBytes = dvtb_audDecgetOutPutBytes(&T->g.adec.adecStatus);
#ifdef PERF
				SYS_PERF("Frame#, %d, Frame Size(bytes), %d, DecTime(us), %d\n",nFrames, frameSize, decDuration);
#endif

			}

			if(DVEVM_ST_FAIL == dvtb_audDecProcessOutBuff(&T->g.aud, fileBased, buff, nBytes, T->targetFp))
			{
				SYS_ERROR("Unable to Process output buffers \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_audDecProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

	if (DVEVM_ST_TRUE == audioDeviceOpened)
	{
		dvtb_audioClose(&T->g.aud);
		SYS_OUT("Audio Device <%s> closed\n", T->g.aud.device);
	}

	if (T->useAlgorithm)
		dvtb_audDecHanClose(&T->g.adec, T->g.eng.name);
	else
		dvtb_freeSingleBufCmem(T->g.adec.inBuf.start, T->g.adec.inBuf.size);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_DECODE, "Audio", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit( );
}
