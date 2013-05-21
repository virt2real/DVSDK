/*
 * dvtbAACHEDec1.c
 *
 * XDM1.0 AACHE Decode Interface implementation
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

#include "dvtbAACHEDec1.h"

void
dvtb_aacheDec1InitDebug(IAACDEC_Params *adp)
{
	SYS_DEBUG("\n<======== Audio Decoder Initialize Debug Start ==========>\n");
	SYS_DEBUG("OutPut PCM Width    : %d\n", (int) adp->auddec_params.outputPCMWidth);
	SYS_DEBUG("PCM Format          : %d\n", (int) adp->auddec_params.pcmFormat);
	SYS_DEBUG("Data Endianness     : %d\n", (int) adp->auddec_params.dataEndianness);
	SYS_DEBUG("Channel Mode        : %d\n", (int) adp->sixChannelMode);
	SYS_DEBUG("\n<======== Audio Decoder Initialize Debug End ============>\n\n");
}

void
dvtb_aacheDec1ProcessDebug(IAACDEC_OutArgs *ado)
{
	SYS_DEBUG("\n<======== Audio Decoder Process Debug Start ==========>\n");
	SYS_DEBUG("Extended Error               : %d\n", (int) ado->auddec_outArgs.extendedError);
	SYS_DEBUG("Bytes Consumed               : %d\n", (int) ado->auddec_outArgs.bytesConsumed);
	SYS_DEBUG("output samples per channel   : %d\n", (int) ado->auddec_outArgs.numSamples);
	SYS_DEBUG("Output Channel Configuration : %d\n", (int) ado->auddec_outArgs.channelMode);
	SYS_DEBUG("presence of LFE channel      : %d\n", (int) ado->auddec_outArgs.lfeFlag);
	SYS_DEBUG("Dual Mono                    : %d\n", (int) ado->auddec_outArgs.dualMonoMode);
	SYS_DEBUG("Sampling frequency           : %d\n", (int) ado->auddec_outArgs.sampleRate);
	SYS_DEBUG("\n<======== Audio Decoder Process Debug End ============>\n");
}

void
dvtb_aacheDec1ControlDebug(IAACDEC_Status *ads)
{
	SYS_DEBUG("\n<======== Audio Decoder Control Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ads->auddec_status.extendedError);
	SYS_DEBUG("Bit Rate           : %d\n", (int) ads->auddec_status.bitRate);
	SYS_DEBUG("Sample Rate        : %d\n", (int) ads->auddec_status.sampleRate);
	SYS_DEBUG("Valid Flag         : %d\n", (int) ads->auddec_status.validFlag);
	SYS_DEBUG("LFE Channels       : %d\n", (int) ads->auddec_status.lfeFlag);
	SYS_DEBUG("Channel Mode       : %d\n", (int) ads->auddec_status.channelMode);
	SYS_DEBUG("PCM Format         : %d\n", (int) ads->auddec_status.pcmFormat);
	SYS_DEBUG("Num Samples        : %d\n", (int) ads->auddec_status.numSamples);
	SYS_DEBUG("Dual Mono Mode     : %d\n", (int) ads->auddec_status.dualMonoMode);
	SYS_DEBUG("Output Bits/Sample : %d\n", (int) ads->auddec_status.outputBitsPerSample);
	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ads->auddec_status.bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ads->auddec_status.bufInfo.minNumOutBufs);
	SYS_DEBUG("BUF-Min In Size    : %d\n", (int) ads->auddec_status.bufInfo.minInBufSize[0]);
	SYS_DEBUG("BUF-Min Out Size   : %d\n", (int) ads->auddec_status.bufInfo.minOutBufSize[0]);
	SYS_DEBUG("Mpeg ID            : %d\n", (int) ads->mpegID);
	SYS_DEBUG("Original/Copy      : %d\n", (int) ads->original_copy);
	SYS_DEBUG("CopyRight          : %d\n", (int) ads->copyright);
	SYS_DEBUG("Tool Used          : %d\n", (int) ads->toolsUsed);
	SYS_DEBUG("PCE present        : %d\n", (int) ads->pcePresent);
	SYS_DEBUG("Channel Mode       : %d\n", (int) ads->sixChannelMode);
	SYS_DEBUG("DownMix            : %d\n", (int) ads->isARIBDownMixed);
	SYS_DEBUG("Surround Enable    : %d\n", (int) ads->pseudoSurroundEnable);
	SYS_DEBUG("SBR Present        : %d\n", (int) ads->sbrPresent);
	SYS_DEBUG("PS Present         : %d\n", (int) ads->psPresent);
	SYS_DEBUG("\n<======== Audio Decoder Control Debug End ============>\n");
}

void
dvtb_aacheDec1Cleanup(DvevmStAacheDec1Info *ad)
{
	if (NULL != ad->adecHdl)
		AUDDEC1_delete(ad->adecHdl);

	ad->adecHdl = NULL;
}

DvevmStRetCode
dvtb_aacheDec1Init(DvevmStAacheDec1Info *ad)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ad != NULL);
	ASSERT(ad->ceHdl != NULL);
	ASSERT(ad->adecName[0] != 0);

	if (NULL == (ad->adecHdl = AUDDEC1_create(ad->ceHdl, ad->adecName, (AUDDEC1_Params *)&ad->adecParams)))
	{
		SYS_ERROR("Unable to initialize Audio Decoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Audio Decoder <%s> initialized\n", ad->adecName);
		dvtb_aacheDec1InitDebug(&ad->adecParams);

		ad->adecCmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_aacheDec1Control(ad))
		{
			SYS_ERROR("Unable to set dynamic audio parameters using command <%d>\n", ad->adecCmd);
			retCode = DVEVM_ST_FAIL;
		}
	}

	if(DVEVM_ST_FAIL == retCode)
		dvtb_aacheDec1Cleanup(ad);

	return retCode;
}

DvevmStRetCode
dvtb_aacheDec1Decode(DvevmStAacheDec1Info *ad, int *decDuration)
{
	XDAS_Int32 status = -1;
	XDM1_BufDesc inBufDesc, outBufDesc;
	IAACDEC_InArgs decInArgs;
	IAACDEC_OutArgs decOutArgs;
	DvevmStTime timeStmpBfrDec, timeStmpAftrDec;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ad != NULL);
	ASSERT(ad->ceHdl != NULL);
	ASSERT(ad->adecHdl != NULL);

	ad->inBuf.numBufs = 1;
	ad->outBuf.numBufs = 1;

	inBufDesc.numBufs = 1;
	inBufDesc.descs[0].bufSize = ad->inBuf.bufSizes[0];
	inBufDesc.descs[0].buf = (XDAS_Int8 *)ad->inBuf.bufs[0];
	outBufDesc.numBufs = 1;
	outBufDesc.descs[0].bufSize = ad->outBuf.bufSizes[0];
	outBufDesc.descs[0].buf = (XDAS_Int8 *) ad->outBuf.bufs[0];

	decInArgs.auddec_inArgs.size = sizeof(decInArgs);
	decInArgs.auddec_inArgs.numBytes = ad->inFrameSize;
	decInArgs.auddec_inArgs.desiredChannelMode = ad->desiredChannelMode;
	decInArgs.auddec_inArgs.lfeFlag = 0;
	decOutArgs.auddec_outArgs.size = sizeof(decOutArgs);

	timeStmpBfrDec = dvtb_getTime( );
	status = AUDDEC1_process(ad->adecHdl, &inBufDesc, &outBufDesc,(AUDDEC1_InArgs *)&decInArgs,(AUDDEC1_OutArgs *)&decOutArgs);
	timeStmpAftrDec = dvtb_getTime( );
	*decDuration = ((timeStmpAftrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrDec.tv_usec) - ((timeStmpBfrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrDec.tv_usec);

	if (status != AUDDEC1_EOK)
	{
		if (XDM_ISFATALERROR(decOutArgs.auddec_outArgs.extendedError))
		{
			SYS_ERROR("Audio Decode Process failed with a fatal error (%d)\n", (int) status);
			SYS_ERROR("Codec Error => %d\n", (int) decOutArgs.auddec_outArgs.extendedError);
			retCode = DVEVM_ST_FAIL;
		}
		else if ((1 << XDM_INSUFFICIENTDATA) & decOutArgs.auddec_outArgs.extendedError)
		{
			SYS_ERROR("Audio Decode Process failed with ERROR: INSUFFICIENTDATA \n");
			SYS_DEBUG("Number of bytes remained: %d \n", (int) ad->inFrameSize - (int) decOutArgs.auddec_outArgs.bytesConsumed);
			retCode = DVEVM_ST_FAIL;

		}

		SYS_ERROR("Audio Decode Process failed (%d)\n", (int) status);
		SYS_ERROR("Codec Error => %d\n", (int) decOutArgs.auddec_outArgs.extendedError);
	}
	if(DVEVM_ST_FAIL != retCode)
	{
		dvtb_aacheDec1ProcessDebug(&decOutArgs);
		ad->decFrameSize = decOutArgs.auddec_outArgs.bytesConsumed;
	}

	return retCode;
}

DvevmStRetCode
dvtb_aacheDec1Control(DvevmStAacheDec1Info *ad)
{
	int status = -1, i =0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ad != NULL);
	ASSERT(ad->adecHdl != NULL);

	status = AUDDEC1_control(ad->adecHdl, ad->adecCmd, (AUDDEC1_DynamicParams *)&ad->adecDynParams, (AUDDEC1_Status *)&ad->adecStatus);
	if (AUDDEC1_EOK != status)
	{
		SYS_ERROR("Audio Decode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Audio Decode Control => Command : %d\n", ad->adecCmd);
		dvtb_aacheDec1ControlDebug(&ad->adecStatus);

		if (XDM_GETBUFINFO == ad->adecCmd)
		{
			ad->inBuf.numBufs = ad->adecStatus.auddec_status.bufInfo.minNumInBufs;
			ad->outBuf.numBufs = ad->adecStatus.auddec_status.bufInfo.minNumOutBufs;

			for (i = 0; i < ad->inBuf.numBufs; i++)
			{
				ad->inBuf.bufSizes[i] = ad->adecStatus.auddec_status.bufInfo.minInBufSize[i];
			}
			for (i = 0; i < ad->outBuf.numBufs; i++)
			{
				ad->outBuf.bufSizes[i] = ad->adecStatus.auddec_status.bufInfo.minOutBufSize[i];
			}
		}
	}
	return retCode;
}

DvevmStRetCode
dvtb_aacheDec1Close(DvevmStAacheDec1Info *ad)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	dvtb_aacheDec1Cleanup(ad);

	return retCode;
}
