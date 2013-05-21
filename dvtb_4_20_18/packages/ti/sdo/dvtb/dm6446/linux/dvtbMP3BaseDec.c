/*
 * dvtbMP3BaseDec.c
 *
 * XDM0.9 MP3Base Decode Interface implementation
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

#include "dvtbMP3BaseDec.h"
#include "dvtbMemory.h"

void
dvtb_mp3baseDecInitDebug(AUDDEC_Params *adp)
{
	SYS_DEBUG("\n<======== Audio Decoder Initialize Debug Start ==========>\n");
	SYS_DEBUG("Max Sample Rate    : %d\n", (int) adp->maxSampleRate);
	SYS_DEBUG("Max Bit Rate       : %d\n", (int) adp->maxBitrate);
	SYS_DEBUG("Max No of Channels : %d\n", (int) adp->maxNoOfCh);
	SYS_DEBUG("Data Endianness    : %d\n", (int) adp->dataEndianness);
	SYS_DEBUG("\n<======== Audio Decoder Initialize Debug End ============>\n\n");
}

void
dvtb_mp3baseDecControlDebug(AUDDEC_Status *ads)
{
	SYS_DEBUG("\n<======== Audio Decoder Control Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ads->extendedError);
	SYS_DEBUG("Bit Rate           : %d\n", (int) ads->bitRate);
	SYS_DEBUG("Sample Rate        : %d\n", (int) ads->sampleRate);
	SYS_DEBUG("Num Channels       : %d\n", (int) ads->numChannels);
	SYS_DEBUG("Num LFE Channels   : %d\n", (int) ads->numLFEChannels);
	SYS_DEBUG("Output Format      : %d\n", (int) ads->outputFormat);
	SYS_DEBUG("Auto Position      : %d\n", (int) ads->autoPosition);
	SYS_DEBUG("Fast Fwd Len       : %d\n", (int) ads->fastFwdLen);
	SYS_DEBUG("Frame Len          : %d\n", (int) ads->frameLen);
	SYS_DEBUG("Output Bits/Sample : %d\n", (int) ads->outputBitsPerSample);
	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ads->bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ads->bufInfo.minNumOutBufs);
	SYS_DEBUG("BUF-Min In Size    : %d\n", (int) ads->bufInfo.minInBufSize[0]);
	SYS_DEBUG("BUF-Min Out Size   : %d\n", (int) ads->bufInfo.minOutBufSize[0]);
	SYS_DEBUG("\n<======== Audio Decoder Control Debug End ============>\n");
}

void
dvtb_mp3baseDecCleanup(DvevmStMP3BaseDecInfo *ad)
{
	if (NULL != ad->adecHdl)
		AUDDEC_delete(ad->adecHdl);


	if (NULL != ad->outBuf.start)
	{
		SYS_DEBUG("Freeing OutBuffer %x of size %d\n", (unsigned int) ad->outBuf.start, ad->outBuf.size);
		dvtb_freeSingleBufCmem(ad->outBuf.start, ad->outBuf.size);
	}

	ad->outBuf.start = NULL;
}

DvevmStRetCode
dvtb_mp3baseDecInit(DvevmStMP3BaseDecInfo *ad)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ad != NULL);
	ASSERT(ad->ceHdl != NULL);
	ASSERT(ad->adecName[0] != 0);

	if (NULL == (ad->adecHdl = AUDDEC_create(ad->ceHdl, ad->adecName, &ad->adecParams)))
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
		SYS_DEBUG("Allocated InBuffer %x of size %d, OutBuffer %x of size %d\n", (unsigned int) ad->inBuf.start, ad->inBuf.size, (unsigned int) ad->outBuf.start, ad->outBuf.size);
		SYS_DEBUG("Audio Decoder <%s> initialized\n", ad->adecName);
		SYS_DEBUG("Configured In Buf Size : %d\n", ad->inBuf.size);
		SYS_DEBUG("Configured Out Buf Size : %d\n", ad->outBuf.size);
		dvtb_mp3baseDecInitDebug(&ad->adecParams);

		ad->adecCmd = XDM_RESET;
		if (DVEVM_ST_FAIL == dvtb_mp3baseDecControl(ad))
		{
			SYS_ERROR("Unable to set dynamic audio parameters using command <%d>\n", ad->adecCmd);
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			ad->adecCmd = XDM_SETDEFAULT;
			if (DVEVM_ST_FAIL == dvtb_mp3baseDecControl(ad))
			{
				SYS_ERROR("Unable to set dynamic audio parameters using command <%d>\n", ad->adecCmd);
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				ad->adecCmd = XDM_SETPARAMS;
				if (DVEVM_ST_FAIL == dvtb_mp3baseDecControl(ad))
				{
					SYS_ERROR("Unable to set dynamic audio parameters using command <%d>\n", ad->adecCmd);
					retCode = DVEVM_ST_FAIL;
				}
			}
		}
	}

	if(DVEVM_ST_FAIL == retCode)
		dvtb_mp3baseDecCleanup(ad);

	return retCode;
}

DvevmStRetCode
dvtb_mp3baseDecDecode(DvevmStMP3BaseDecInfo *ad, int *decDuration)
{

	XDAS_Int32 status = -1;
	IAUDDEC_InArgs decInArgs;
	IAUDDEC_OutArgs decOutArgs;

	XDM_BufDesc inBufDesc, outBufDesc;
	XDAS_Int32 inBufSizeArray[1], outBufSizeArray[1];

	DvevmStTime timeStmpBfrDec, timeStmpAftrDec;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;



	ASSERT(ad != NULL);
	ASSERT(ad->ceHdl != NULL);
	ASSERT(ad->adecHdl != NULL);
	ASSERT(ad->inBuf.start != NULL);
	ASSERT(ad->outBuf.start != NULL);

	XDAS_Int8 *src = (XDAS_Int8 *) ad->inBuf.start;
	XDAS_Int8 *dst = (XDAS_Int8 *) ad->outBuf.start;

	inBufDesc.numBufs = outBufDesc.numBufs = 1;
	inBufSizeArray[0] = ad->inFrameSize;
	outBufSizeArray[0] = ad->outBuf.size;
	inBufDesc.bufSizes = inBufSizeArray;
	outBufDesc.bufSizes = outBufSizeArray;

	inBufDesc.bufs = &src;
	outBufDesc.bufs = &dst;

	decInArgs.size = sizeof(decInArgs);
	decInArgs.numBytes = ad->inFrameSize;
	decOutArgs.size = sizeof(decOutArgs);

	timeStmpBfrDec = dvtb_getTime( );
	status = AUDDEC_process(ad->adecHdl, &inBufDesc, &outBufDesc, &decInArgs, &decOutArgs);
	timeStmpAftrDec = dvtb_getTime( );

	*decDuration = ((timeStmpAftrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrDec.tv_usec) - ((timeStmpBfrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrDec.tv_usec);
	if (status != AUDDEC_EOK)
	{
		SYS_ERROR("Audio Decode Process failed (%d)\n", (int) status);
		SYS_ERROR("Codec Error => %d\n", (int) decOutArgs.extendedError);
		retCode = DVEVM_ST_FAIL;
	}

	if(DVEVM_ST_FAIL != retCode)
		ad->decFrameSize = decOutArgs.bytesConsumed;

	return retCode;
}

DvevmStRetCode
dvtb_mp3baseDecControl(DvevmStMP3BaseDecInfo *ad)
{
	int status = -1;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ad != NULL);
	ASSERT(ad->adecHdl != NULL);

	status = AUDDEC_control(ad->adecHdl, ad->adecCmd, &ad->adecDynParams, &ad->adecStatus);
	if (AUDDEC_EOK != status)
	{
		SYS_ERROR("Audio Decode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Audio Decode Control => Command : %d\n", ad->adecCmd);
		dvtb_mp3baseDecControlDebug(&ad->adecStatus);
	}

	return retCode;
}

DvevmStRetCode
dvtb_mp3baseDecClose(DvevmStMP3BaseDecInfo *ad)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	dvtb_mp3baseDecCleanup(ad);
	return retCode;
}
