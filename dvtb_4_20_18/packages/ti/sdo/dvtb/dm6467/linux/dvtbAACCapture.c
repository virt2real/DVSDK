/*
 * dvtbAACCapture.c
 *
 * XDM0.9 AAC Encode Functionality
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
#include "dvtbAACEnc.h"
#include "dvtbAACCapture.h"
#include "dvtbDefs.h"
#include "dvtbUtils.h"

void
dvtb_aacEncProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int seconds)
{
#if 0
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("AAC [Capture]+[Encode] completed for %d seconds\n",	seconds);
		else
			SYS_OUT("AAC [Capture] completed for %d seconds\n", seconds);
	}
	else//File based
		SYS_OUT("AAC [File Read]+[Encode] completed\n");
#endif
}

void
dvtb_aacEncInitPtrs(DvevmStAACEncInfo *aenc)
{
#if 0
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
#endif
}

DvevmStRetCode
dvtb_aacEncHanInit(DvevmStAACEncInfo *aenc, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

#if 0
	do
	{
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &aenc->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_aacEncInit(aenc))
		{
			SYS_ERROR("Unable to initialize Speech Encoder <%s>\n",	aenc->aencName);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

#endif
	return retCode;
}

void
dvtb_aacEncHanClose(DvevmStAACEncInfo *aenc, char *engName)
{
#if 0
	dvtb_aacEncClose(aenc);
	SYS_OUT("Audio Encoder <%s> closed\n", aenc->aencName);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&aenc->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
#endif
}

DvevmStRetCode
dvtb_aacEncEncProcess(DvevmStAACEncInfo *aenc, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

#if 0
	do
	{
		if (DVEVM_ST_FAIL == dvtb_aacEncEncode(aenc, encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		aenc->aencCmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_aacEncControl(aenc))
		{
			SYS_ERROR("Unable to get status info\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);
#endif

	return retCode;
}

DvevmStRetCode
dvtb_aacEncReadInput(DvevmStAudioInfo *aud, DvevmStAACEncInfo *aenc, FILE *fp, DvevmStBool fileBased, int *nBytes, int *noOfChannels, int read_capture)
{
#if 0
	int bytesToRead = 0, capturedBytes = 0;
	char *buff = NULL;
#endif
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
#if 0
	bytesToRead = aenc->inBuf.bufSizes[0];
	buff = (char *)aenc->inBuf.bufs[0];

	if (DVEVM_ST_FALSE != fileBased)
	{
		if (DVEVM_ST_FAIL == dvtb_fileRead(fp, buff, bytesToRead, nBytes))
		{
			SYS_ERROR("Error in file read \n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			switch (aud->numChannels)
			{
				case IAUDIO_MONO:
					*noOfChannels = 1;
					break;

				case IAUDIO_STEREO:
					*noOfChannels = 2;
					break;

				default:
					SYS_ERROR("Unsupported number of Channels\n");
					retCode = DVEVM_ST_FAIL;
					break;
			}

			aenc->insamples = *nBytes / ((aenc->aencDynParams.audenc_dynamicparams.inputBitsPerSample / 8) * (*noOfChannels));//16bits per sample, two channels
		}
	}
	else
	{
		*nBytes = dvtb_audioIn(aud,(char *) buff, read_capture);
		if(DVEVM_ST_FAIL == *nBytes)
		{
			SYS_ERROR("Error in Getting Reading from Driver \n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			capturedBytes = read_capture;
			switch (aud->numChannels)
			{
				case IAUDIO_MONO:
					*noOfChannels = 1;
					break;

				case IAUDIO_STEREO:
					*noOfChannels = 2;
					break;

				default:
					SYS_ERROR("Unsupported number of Channels\n");
					break;
			}

			aenc->insamples = capturedBytes / ((aenc->aencDynParams.audenc_dynamicparams.inputBitsPerSample / 8) * (*noOfChannels));//16bits per sample, two channels
		}
	}
#endif
	return retCode;
}

DvevmStRetCode
dvtb_aacEncFlush(DvevmStAACEncInfo *aenc, int nBytes, int *lastFrame, int *flushDone)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
#if 0

	do
	{
		if (nBytes < 1024)
		{
			*lastFrame = DVEVM_ST_TRUE;
			aenc->aencCmd = XDM_FLUSH;
			if (DVEVM_ST_FAIL == dvtb_aacEncControl(aenc))
			{
				SYS_ERROR("Unable to get status info\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}

		if (DVEVM_ST_FALSE == *flushDone)
		{
			aenc->aencCmd = XDM_FLUSH;
			if (DVEVM_ST_FAIL == dvtb_aacEncControl(aenc))
			{
				SYS_ERROR("Unable to Flush.\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
			SYS_DEBUG("flush\n");
			*flushDone = DVEVM_ST_TRUE;
		}
	}while(DVEVM_ST_FALSE);
#endif

	return retCode;

}

void
dvtb_AacEncCapture(DvevmStThreadInfo *T)
{
#if 0
	int frameLen = 1024, encDuration = 0, read_capture = 0,	bytesToCapture = 0, count = 0, frameNo = -1,
		i = 0, totalBytes = 0,	noOfChannels = 0, nBytes = 0, lastFrame = DVEVM_ST_FALSE, flushDone = DVEVM_ST_FALSE;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, audioDeviceOpened =	DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	char *buff = NULL;

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
	dvtb_aacEncInitPtrs(&T->g.aacenc);

	// [Capture][Encode] scenario
	do
	{
		if (T->useAlgorithm)
		{

			if(DVEVM_ST_FAIL == dvtb_aacEncHanInit(&T->g.aacenc, T->g.eng.name))
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

			bytesToCapture = (T->g.aacenc.seconds) * (AUD_FRAME_SIZE(T->g.aud.sampleRate, T->g.aud.numChannels, T->g.aud.sampleSize));

		}

		read_capture = T->g.aacenc.inBuf.bufSizes[0];

		while (1)
		{
			if (DVEVM_ST_FAIL == dvtb_aacEncReadInput(&T->g.aud, &T->g.aacenc, T->sourceFp, fileBased, &nBytes, &noOfChannels, read_capture))
			{
				SYS_ERROR("Error in Read Input\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_TRUE == fileBased)
			{
				if (0 == nBytes && lastFrame == TRUE)
				{
					SYS_OUT("End of file reached. Exiting ...\n");
					break;
				}

				if(DVEVM_ST_FAIL == dvtb_aacEncFlush(&T->g.aacenc, nBytes, &lastFrame, &flushDone))
				{
					SYS_ERROR("Unable to Flush\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
			}
			else
			{
				if (count >= bytesToCapture)
					break;

				count += read_capture;
			}

			if (T->useAlgorithm)
			{
				for (i = 0; i < T->g.aacenc.outBuf.numBufs; i++)
					memset(T->g.aacenc.outBuf.bufs[i], 0, T->g.aacenc.outBuf.bufSizes[i]);

				if (DVEVM_ST_FAIL == dvtb_aacEncEncProcess(&T->g.aacenc, &encDuration))
				{
					SYS_ERROR("Encode Process fails \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, frameNo, T->g.aacenc.bytesGenerated, encDuration);
#endif

				if (DVEVM_ST_TRUE == fileBased)
				{
					fseek(T->sourceFp, -(nBytes - (frameLen * (T->g.aacenc.aencDynParams.audenc_dynamicparams.inputBitsPerSample / 8) * noOfChannels)), SEEK_CUR);
				}
				else
				{
					read_capture = T->g.aacenc.inBuf.bufSizes[0] - (frameLen * (T->g.aacenc.aencDynParams.audenc_dynamicparams.inputBitsPerSample / 8) * noOfChannels);
					if (read_capture < 0)
					{
						SYS_ERROR("read_capture should not be -ve.\n");
						break;
					}
					memcpy(T->g.aacenc.inBuf.bufs[0], (T->g.aacenc.inBuf.bufs[0] + T->g.aacenc.inBuf.bufSizes[0] - read_capture), read_capture);
					read_capture = T->g.aacenc.inBuf.bufSizes[0] - read_capture;
				}

				buff = T->g.aacenc.outBuf.bufs[0];
			}

			if (T->g.aacenc.bytesGenerated > 0)
			{
				SYS_DEBUG("*** %d bytes generated for frame %d\n", T->g.aacenc.bytesGenerated, frameNo);
				SYS_DEBUG("Written %d no of bytes for frame %d\n", T->g.aacenc.bytesGenerated, frameNo);
				totalBytes += T->g.aacenc.bytesGenerated;

				if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)buff, T->g.aacenc.bytesGenerated))
				{
					SYS_ERROR("Error in writing to file.\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
			}
			else
			{
				SYS_DEBUG("*** 0 bytes generated.\n");
				if (lastFrame == TRUE)
					break;
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_aacEncProcessEndMessage(T->useAlgorithm, fileBased, T->g.aacenc.seconds);

	if (DVEVM_ST_TRUE == audioDeviceOpened)
	{
		dvtb_audioClose(&T->g.aud);
		SYS_OUT("Audio Device <%s> closed\n", T->g.aud.device);
	}

	if (T->useAlgorithm)
		dvtb_aacEncHanClose(&T->g.aacenc, T->g.eng.name);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "AAC", T->useAlgorithm, fileBased, usecaseFailed);

#endif

	dvtb_freeThr(T);
	dvtb_threadExit( );
}
