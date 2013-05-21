/*
 * dvtbMP3BaseDec1.c
 *
 * XDM1.0 MP3Base Decode Interface implementation
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

#include "dvtbMP3BaseDec1.h"

void
dvtb_mp3baseDec1InitDebug(AUDDEC1_Params *adp)
{
	SYS_DEBUG("\n<======== Audio Decoder Initialize Debug Start ==========>\n");
	SYS_DEBUG("OutPut PCM Width    : %d\n", (int) adp->outputPCMWidth);
	SYS_DEBUG("PCM Format          : %d\n", (int) adp->pcmFormat);
	SYS_DEBUG("Data Endianness     : %d\n", (int) adp->dataEndianness);
	SYS_DEBUG("\n<======== Audio Decoder Initialize Debug End ============>\n\n");
}

void
dvtb_mp3baseDec1ProcessDebug(AUDDEC1_OutArgs *ado)
{
	SYS_DEBUG("\n<======== Audio Decoder Process Debug Start ==========>\n");
	SYS_DEBUG("Extended Error               : %d\n", (int) ado->extendedError);
	SYS_DEBUG("Bytes Consumed               : %d\n", (int) ado->bytesConsumed);
	SYS_DEBUG("output samples per channel   : %d\n", (int) ado->numSamples);
	SYS_DEBUG("Output Channel Configuration : %d\n", (int) ado->channelMode);
	SYS_DEBUG("presence of LFE channel      : %d\n", (int) ado->lfeFlag);
	SYS_DEBUG("Dual Mono                    : %d\n", (int) ado->dualMonoMode);
	SYS_DEBUG("Sampling frequency           : %d\n", (int) ado->sampleRate);
	SYS_DEBUG("\n<======== Audio Decoder Process Debug End ============>\n");
}

void
dvtb_mp3baseDec1ControlDebug(AUDDEC1_Status *ads)
{
	SYS_DEBUG("\n<======== Audio Decoder Control Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ads->extendedError);
	SYS_DEBUG("Bit Rate           : %d\n", (int) ads->bitRate);
	SYS_DEBUG("Sample Rate        : %d\n", (int) ads->sampleRate);
	SYS_DEBUG("Valid Flag         : %d\n", (int) ads->validFlag);
	SYS_DEBUG("LFE Channels       : %d\n", (int) ads->lfeFlag);
	SYS_DEBUG("Channel Mode       : %d\n", (int) ads->channelMode);
	SYS_DEBUG("PCM Format         : %d\n", (int) ads->pcmFormat);
	SYS_DEBUG("Num Samples        : %d\n", (int) ads->numSamples);
	SYS_DEBUG("Dual Mono Mode     : %d\n", (int) ads->dualMonoMode);
	SYS_DEBUG("Output Bits/Sample : %d\n", (int) ads->outputBitsPerSample);
	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ads->bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ads->bufInfo.minNumOutBufs);
	SYS_DEBUG("BUF-Min In Size    : %d\n", (int) ads->bufInfo.minInBufSize[0]);
	SYS_DEBUG("BUF-Min Out Size   : %d\n", (int) ads->bufInfo.minOutBufSize[0]);
	SYS_DEBUG("\n<======== Audio Decoder Control Debug End ============>\n");
}

void
dvtb_mp3baseDec1Cleanup(DvevmStMP3BaseDec1Info *ad)
{
	if (NULL != ad->adecHdl)
		AUDDEC1_delete(ad->adecHdl);

	ad->adecHdl = NULL;
}

DvevmStRetCode
dvtb_mp3baseDec1Init(DvevmStMP3BaseDec1Info *ad)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ad != NULL);
	ASSERT(ad->ceHdl != NULL);
	ASSERT(ad->adecName[0] != 0);

	if (NULL == (ad->adecHdl = AUDDEC1_create(ad->ceHdl, ad->adecName, &ad->adecParams)))
	{
		SYS_ERROR("Unable to initialize MP3 Decoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Audio Decoder <%s> initialized\n", ad->adecName);
		dvtb_mp3baseDec1InitDebug(&ad->adecParams);

		ad->adecCmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_mp3baseDec1Control(ad))
		{
			SYS_ERROR("Unable to set dynamic audio parameters using command <%d>\n", ad->adecCmd);
			retCode = DVEVM_ST_FAIL;
		}
	}

	if(DVEVM_ST_FAIL == retCode)
		dvtb_mp3baseDec1Cleanup(ad);

	return retCode;
}

DvevmStRetCode
dvtb_mp3baseDec1Decode(DvevmStMP3BaseDec1Info *ad, int *decDuration)
{
	XDAS_Int32 status = -1;
	XDM1_BufDesc inBufDesc, outBufDesc;
	IAUDDEC1_InArgs decInArgs;
	IAUDDEC1_OutArgs decOutArgs;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ad != NULL);
	ASSERT(ad->ceHdl != NULL);
	ASSERT(ad->adecHdl != NULL);

	ad->inBuf.numBufs = 1;
	ad->outBuf.numBufs = 1;

	inBufDesc.numBufs = 1;
	inBufDesc.descs[0].bufSize = ad->inBuf.bufSizes[0];
	inBufDesc.descs[0].buf = (XDAS_Int8 *) ad->inBuf.bufs[0];

	outBufDesc.numBufs = 1;
	outBufDesc.descs[0].bufSize = ad->outBuf.bufSizes[0];
	outBufDesc.descs[0].buf = (XDAS_Int8 *) ad->outBuf.bufs[0];

	decInArgs.size = sizeof(decInArgs);
	decInArgs.numBytes = ad->inFrameSize;
	decInArgs.desiredChannelMode = IAUDIO_11_0;// IAUDIO_11_0;
	decInArgs.lfeFlag = 0;
	decOutArgs.size = sizeof(decOutArgs);

	dvtb_timeReset(ad->hTime);
	status = AUDDEC1_process(ad->adecHdl, &inBufDesc, &outBufDesc, &decInArgs, &decOutArgs);
	dvtb_timeDelta(ad->hTime, decDuration);

	if (status != AUDDEC1_EOK)
	{
		if (XDM_ISFATALERROR(decOutArgs.extendedError))
		{
			SYS_ERROR("Audio Decode Process failed with a Codec fatal error (%d)\n", (int) status);
			SYS_ERROR("Codec Error => %d\n", (int) decOutArgs.extendedError);
			retCode = DVEVM_ST_FAIL;
		}
		SYS_ERROR("Audio Decode Process failed (%d)\n", (int) status);
		SYS_ERROR("Codec Error => %d\n", (int) decOutArgs.extendedError);
	}
	else if ((1 << XDM_INSUFFICIENTDATA) & decOutArgs.extendedError)
	{
		SYS_ERROR("Audio Decode Process failed with ERROR: INSUFFICIENTDATA \n");
		SYS_DEBUG("Number of bytes remained: %d \n", (int) ad->inFrameSize - (int) decOutArgs.bytesConsumed);
		retCode = DVEVM_ST_FAIL;
	}

	if(DVEVM_ST_FAIL != retCode)
	{
		dvtb_mp3baseDec1ProcessDebug(&decOutArgs);
		ad->decFrameSize = decOutArgs.bytesConsumed;
	}

	return retCode;
}

DvevmStRetCode
dvtb_mp3baseDec1Control(DvevmStMP3BaseDec1Info *ad)
{
	int status = -1, i =0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ad != NULL);
	ASSERT(ad->adecHdl != NULL);

	status = AUDDEC1_control(ad->adecHdl, ad->adecCmd, &ad->adecDynParams, &ad->adecStatus);
	if (AUDDEC1_EOK != status)
	{
		SYS_ERROR("Image Decode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Image Decode Control => Command : %d\n", ad->adecCmd);
		dvtb_mp3baseDec1ControlDebug(&ad->adecStatus);

		if (XDM_GETBUFINFO == ad->adecCmd)
		{
			ad->inBuf.numBufs = ad->adecStatus.bufInfo.minNumInBufs;
			ad->outBuf.numBufs = ad->adecStatus.bufInfo.minNumOutBufs;

			for (i = 0; i < (int)ad->inBuf.numBufs; i++)
			{
				ad->inBuf.bufSizes[i] = ad->adecStatus.bufInfo.minInBufSize[i];
			}
			for (i = 0; i < (int)ad->outBuf.numBufs; i++)
			{
				ad->outBuf.bufSizes[i] = ad->adecStatus.bufInfo.minOutBufSize[i];
			}
		}
	}
	return retCode;
}


DvevmStRetCode
dvtb_mp3baseDec1Close(DvevmStMP3BaseDec1Info *ad)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	dvtb_mp3baseDec1Cleanup(ad);
	return retCode;
}
