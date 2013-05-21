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
#include "dvtbMemory.h"

void
dvtb_mp3basedec1InitDebug(IAUDDEC1_Params *adp)
{

	SYS_DEBUG("outputpcmwidth     : %d\n", (int) adp->outputPCMWidth);
	SYS_DEBUG("pcmformat          : %d\n", (int) adp->pcmFormat);
	SYS_DEBUG("dataEndianness     : %d\n", (int) adp->dataEndianness);

	SYS_DEBUG("\n<======== Audio Decoder Initialize Debug End ============>\n\n");
}

void
dvtb_mp3basedec1ControlDebug(IAUDDEC1_Status *ads)
{
	SYS_DEBUG("\n<======== Audio Decoder Control Debug Start ==========>\n");

	SYS_DEBUG("Extended Error     : %d\n", (int) ads->extendedError);
	SYS_DEBUG("validFlag          : %d\n", (int) ads->validFlag);
	SYS_DEBUG("lfeFlag            : %d\n", (int) ads->lfeFlag);
	SYS_DEBUG("bitRate            : %d\n", (int) ads->bitRate);
	SYS_DEBUG("sampleRate         : %d\n", (int) ads->sampleRate);
	SYS_DEBUG("channelMode        : %d\n", (int) ads->channelMode);
	SYS_DEBUG("pcmFormat          : %d\n", (int) ads->pcmFormat);
	SYS_DEBUG("numSamples         : %d\n", (int) ads->numSamples);
	SYS_DEBUG("outputBitsPerSample : %d\n", (int) ads->outputBitsPerSample);
	SYS_DEBUG("dualMonoMode   : %d\n", (int) ads->dualMonoMode);

	SYS_DEBUG("\n<======== Audio Decoder Control Debug End ============>\n");
}

void
dvtb_mp3basedec1Cleanup(DvevmStMP3BaseDec1Info *ad)
{
	if (NULL != ad->adecHdl)
		AUDDEC1_delete(ad->adecHdl);

	if (NULL != ad->outBuf.start)
		dvtb_freeSingleBufCmem(ad->outBuf.start, ad->outBuf.size);

	ad->inBuf.start = NULL;
	ad->outBuf.start = NULL;
}

DvevmStRetCode
dvtb_mp3basedec1Init(DvevmStMP3BaseDec1Info *ad)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ad != NULL);
	ASSERT(ad->ceHdl != NULL);
	ASSERT(ad->adecName[0] != 0);

	dvtb_mp3basedec1InitDebug(&ad->adecParams);
	if (NULL == (ad->adecHdl = AUDDEC1_create(ad->ceHdl, ad->adecName, &ad->adecParams)))
	{
		SYS_ERROR("Unable to initialize Audio Decoder-create failed\n");
		retCode = DVEVM_ST_FAIL;
	}
	else if (NULL == (ad->outBuf.start = Memory_contigAlloc(ad->outBuf.size, Memory_DEFAULTALIGNMENT)))
	{
		SYS_ERROR("Unable to allocate memory for Out Buffer\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Audio Decoder <%s> initialized\n", ad->adecName);
		SYS_DEBUG("Configured In Buf Size : %d\n", ad->inBuf.size);
		SYS_DEBUG("Configured Out Buf Size : %d\n", ad->outBuf.size);
		dvtb_mp3basedec1InitDebug(&ad->adecParams);

		ad->adecCmd = XDM_RESET;
		if (DVEVM_ST_FAIL == dvtb_mp3basedec1Control(ad))
		{
			SYS_ERROR("Unable to set dynamic audio parameters using command <%d>\n", ad->adecCmd);
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			ad->adecCmd = XDM_SETDEFAULT;
			if (DVEVM_ST_FAIL == dvtb_mp3basedec1Control(ad))
			{
				SYS_ERROR("Unable to set dynamic audio parameters using command <%d>\n", ad->adecCmd);
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				ad->adecCmd = XDM_SETPARAMS;
				if (DVEVM_ST_FAIL == dvtb_mp3basedec1Control(ad))
				{
					SYS_ERROR("Unable to set dynamic audio parameters using command <%d>\n", ad->adecCmd);
					retCode = DVEVM_ST_FAIL;
				}
			}
		}
	}

	if(DVEVM_ST_FAIL == retCode)
		dvtb_mp3basedec1Cleanup(ad);

	return retCode;
}

DvevmStRetCode
dvtb_mp3basedec1Decode(DvevmStMP3BaseDec1Info *ad, int *decDuration)
{
	XDM1_BufDesc inBufDesc, outBufDesc;
	XDAS_Int32 status = -1;
	IAUDDEC1_InArgs decInArgs;
	IAUDDEC1_OutArgs decOutArgs;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	DvevmStTime timeStmpBfrDec, timeStmpAftrDec;

	ASSERT(ad != NULL);
	ASSERT(ad->ceHdl != NULL);
	ASSERT(ad->adecHdl != NULL);
	ASSERT(ad->inBuf.start != NULL);
	ASSERT(ad->outBuf.start != NULL);

	inBufDesc.numBufs = 1;
	inBufDesc.descs[0].bufSize = ad->inBuf.size;// We have to declare 2 Global buffers
	outBufDesc.numBufs = 1;
	outBufDesc.descs[0].bufSize = ad->outBuf.size;

	inBufDesc.descs[0].buf = (XDAS_Int8*) ad->inBuf.start;
	outBufDesc.descs[0].buf = (XDAS_Int8*) ad->outBuf.start;

	decInArgs.size = sizeof(decInArgs);
	decInArgs.numBytes = ad->inFrameSize;
	decInArgs.desiredChannelMode = 1;
	decInArgs.lfeFlag = 0;

	decOutArgs.size = sizeof(decOutArgs);

	SYS_DEBUG("In Fraeme size : %d\n", ad->inFrameSize);
	SYS_DEBUG("InArgs size : %d\n", (int) decInArgs.size);
	SYS_DEBUG("OutArgs size : %d\n", (int) decOutArgs.size);
	SYS_DEBUG("desiredChannelMode : %d\n", (int) decInArgs.desiredChannelMode);
	SYS_DEBUG("lfeFlag : %d\n", (int) decInArgs.lfeFlag);

	SYS_DEBUG("pcmbeforeprocess : %d\n", (int) ad->adecParams.pcmFormat);
	SYS_DEBUG("Entering process\n");

	timeStmpBfrDec = dvtb_getTime( );
	status = AUDDEC1_process(ad->adecHdl, &inBufDesc, &outBufDesc, &decInArgs, &decOutArgs);
	timeStmpAftrDec = dvtb_getTime( );

	*decDuration = ((timeStmpAftrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrDec.tv_usec) - ((timeStmpBfrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrDec.tv_usec);
	if (status != IAUDDEC1_EOK)
	{
		if (XDM_ISFATALERROR(decOutArgs.extendedError))
		{
			SYS_ERROR("Audio Decode Process failed (%d) with a Codec fatal error (0x%x)\n", (int) status, (int) decOutArgs.extendedError);
			retCode = DVEVM_ST_FAIL;
		}
		else if ((1 << XDM_INSUFFICIENTDATA) & decOutArgs.extendedError)
		{
			SYS_ERROR("Audio Decode Process failed with ERROR: INSUFFICIENTDATA \n");
			SYS_DEBUG("Number of bytes remained: %ld \n", (int) ad->inFrameSize - decOutArgs.bytesConsumed);
			retCode = DVEVM_ST_FAIL;
		}

		SYS_ERROR("Audio Decode Process Failed (%d)\n", (int) status);
		SYS_ERROR("Codec Error : %d\n", (int) decOutArgs.extendedError);
	}

	if(DVEVM_ST_FAIL != retCode)
	{
		SYS_DEBUG("Leaving process\n");
		ad->decFrameSize = decOutArgs.bytesConsumed;
	}

	return retCode;
}

DvevmStRetCode
dvtb_mp3basedec1Control(DvevmStMP3BaseDec1Info *ad)
{
	int status = -1;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ad != NULL);
	ASSERT(ad->adecHdl != NULL);
	ad->adecCmd = XDM_GETSTATUS;

	status = AUDDEC1_control(ad->adecHdl, ad->adecCmd, &ad->adecDynParams, &ad->adecStatus);

	SYS_DEBUG("pcmformatafterGETSTATUS : %d\n", (int) ad->adecStatus.pcmFormat);

	if (IAUDDEC1_EOK != status)
	{
		SYS_ERROR("Audio Decode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Audio Decode Control => Command : %d\n", ad->adecCmd);
		dvtb_mp3basedec1ControlDebug(&ad->adecStatus);
	}

	return retCode;
}

DvevmStRetCode dvtb_mp3basedec1Close(DvevmStMP3BaseDec1Info *ad)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	dvtb_mp3basedec1Cleanup(ad);
	return retCode;
}
