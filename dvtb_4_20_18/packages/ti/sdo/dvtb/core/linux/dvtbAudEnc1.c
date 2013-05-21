/*
 * dvtbAudEnc1.c
 *
 * XDM1.0 Audio Encoder implementation
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

#include "dvtbAudEnc1.h"
#include "dvtbMemory.h"

void
dvtb_createDebug(DvevmStAudEnc1Info *aenc1)
{
	SYS_DEBUG("\tHandle  : %s\n", aenc1->audenc1Name);
	SYS_DEBUG("\tHandle  : %d\n", (int) aenc1->ceHdl);
	SYS_DEBUG("\tBase size  : %d\n", (int) aenc1->audenc1Params.size);
	SYS_DEBUG("\tBase sample Rate  : %d\n", (int) aenc1->audenc1Params.sampleRate);
	SYS_DEBUG("\tBase bitRate   :%d \n", (int) aenc1->audenc1Params.bitRate);
	SYS_DEBUG("\tBase channel Mode : %d\n", (int) aenc1->audenc1Params.channelMode);
	SYS_DEBUG("\tBase endianness : %d\n", (int) aenc1->audenc1Params.dataEndianness);
	SYS_DEBUG("\tBase encmode : %d\n", (int) aenc1->audenc1Params.encMode);
	SYS_DEBUG("\tBase input format : %d\n", (int) aenc1->audenc1Params.inputFormat);
	SYS_DEBUG("\tBase inp bits :%d\n", (int) aenc1->audenc1Params.inputBitsPerSample);
	SYS_DEBUG("\tBase maxbitrate : %d\n", (int) aenc1->audenc1Params.maxBitRate);
	SYS_DEBUG("\tBase dual mono :%d\n", (int) aenc1->audenc1Params.dualMonoMode);
	SYS_DEBUG("\tBase CRC flag : %d\n", (int) aenc1->audenc1Params.crcFlag);
	SYS_DEBUG("\tBase ancflag :%d\n", (int) aenc1->audenc1Params.ancFlag);
	SYS_DEBUG("\tBase lfe flag:%d\n", (int) aenc1->audenc1Params.lfeFlag);
	SYS_DEBUG("\tInbufsize :%d\n", (int) aenc1->inBuf.descs[0].bufSize);
	SYS_DEBUG("\tOutbufsize :%d\n", (int) aenc1->outBuf.descs[0].bufSize);
	SYS_DEBUG("\tEntering create\n");
}

void
dvtb_processDebug(DvevmStAudEnc1Info *aenc1)
{
	SYS_DEBUG("\enc name  : %s\n", aenc1->audenc1Name);
	SYS_DEBUG("\tHandle  : %d\n", (int) aenc1->ceHdl);
	SYS_DEBUG("\tBase size  : %d\n", (int) aenc1->audenc1Params.size);
	SYS_DEBUG("\tBase sample Rate  : %d\n", (int) aenc1->audenc1Params.sampleRate);
	SYS_DEBUG("\tBase bitRate   :%d \n", (int) aenc1->audenc1Params.bitRate);
	SYS_DEBUG("\tBase channel Mode : %d\n", (int) aenc1->audenc1Params.channelMode);
	SYS_DEBUG("\tBase endianness : %d\n", (int) aenc1->audenc1Params.dataEndianness);
	SYS_DEBUG("\tBase encmode : %d\n", (int) aenc1->audenc1Params.encMode);
	SYS_DEBUG("\tBase input format : %d\n", (int) aenc1->audenc1Params.inputFormat);
	SYS_DEBUG("\tBase inp bits :%d\n", (int) aenc1->audenc1Params.inputBitsPerSample);
	SYS_DEBUG("\tBase maxbitrate : %d\n", (int) aenc1->audenc1Params.maxBitRate);
	SYS_DEBUG("\tBase dual mono :%d\n", (int) aenc1->audenc1Params.dualMonoMode);
	SYS_DEBUG("\tBase CRC flag : %d\n", (int) aenc1->audenc1Params.crcFlag);
	SYS_DEBUG("\tBase ancflag :%d\n", (int) aenc1->audenc1Params.ancFlag);
	SYS_DEBUG("\tBase lfe flag:%d\n", (int) aenc1->audenc1Params.lfeFlag);
	SYS_DEBUG("\tancbufsize :%d\n", aenc1->ancBuf.size);
	SYS_DEBUG("\tHandle  : %d\n", (int) aenc1->audenc1Hdl);
	SYS_DEBUG("\tEntering process call\n");
}

void
dvtb_audEnc1Cleanup(DvevmStAudEnc1Info *aenc1)
{
	if (NULL != aenc1->audenc1Hdl)
		AUDENC1_delete(aenc1->audenc1Hdl);

	aenc1->audenc1Hdl = NULL;

	if(0 != aenc1->inBuf.numBufs)
		dvtb_freeCmemXdm1BufDesc(&aenc1->inBuf);

	if(0 != aenc1->outBuf.numBufs)
		dvtb_freeCmemXdm1BufDesc(&aenc1->outBuf);

	if(NULL != aenc1->ancBuf.start)
		dvtb_freeSingleBufCmem(aenc1->ancBuf.start, aenc1->ancBuf.size);

}

DvevmStRetCode
dvtb_audEnc1Init(DvevmStAudEnc1Info *aenc1)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(aenc1 != NULL);
	ASSERT(aenc1->ceHdl != NULL);
	ASSERT(aenc1->audenc1Name[0] != 0);

	dvtb_createDebug(aenc1);

	if (NULL == (aenc1->audenc1Hdl = AUDENC1_create(aenc1->ceHdl, aenc1->audenc1Name, &aenc1->audenc1Params)))
	{
		SYS_ERROR("Unable to initialize Audio Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		aenc1->ancBuf.size = 14;
		aenc1->audenc1Cmd = XDM_GETBUFINFO;
		if (DVEVM_ST_FAIL == dvtb_audEnc1Control(aenc1))
		{
			SYS_ERROR("Unable to get the input/output buffer information\n");
			retCode = DVEVM_ST_FAIL;
		}
		else if (DVEVM_ST_FAIL == dvtb_allocCmemXdm1BufDesc(&aenc1->inBuf))
		{
			SYS_ERROR("Unable to allocate memory for In Buffer\n");
			retCode = DVEVM_ST_FAIL;
		}
		else if (DVEVM_ST_FAIL == dvtb_allocCmemXdm1BufDesc(&aenc1->outBuf))
		{
			SYS_ERROR("Unable to allocate memory for Out Buffer\n");
			retCode = DVEVM_ST_FAIL;
		}
		else if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&aenc1->ancBuf.start, aenc1->ancBuf.size))
		{
			SYS_ERROR("Unable to allocate memory for Out Buffer\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			SYS_DEBUG("\tAudio Encoder %s initialized.\n", aenc1->audenc1Name);
			memcpy(aenc1->ancBuf.start, "DVTB Encoded", aenc1->ancBuf.size);
			SYS_DEBUG("\tancBuf.start :%x\n", (unsigned int) aenc1->ancBuf.start);
		}
	}

	if(DVEVM_ST_FAIL == retCode)
		dvtb_audEnc1Cleanup(aenc1);

	return retCode;
}

DvevmStRetCode
dvtb_audEnc1Encode(DvevmStAudEnc1Info *aenc1, int *encDuration)
{

	XDAS_Int32 status = -1;
	IAUDENC1_InArgs enc1InArgs;
	IAUDENC1_OutArgs enc1OutArgs;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(aenc1 != NULL);
	ASSERT(aenc1->ceHdl != NULL);
	ASSERT(aenc1->audenc1Hdl != NULL);

	enc1OutArgs.size = sizeof(IAUDENC1_OutArgs);

	enc1InArgs.size = sizeof(IAUDENC1_InArgs);
	enc1InArgs.numInSamples = aenc1->insamples;
	if (aenc1->audenc1Params.ancFlag)
	{
		enc1InArgs.ancData.bufSize = aenc1->ancBuf.size;
		enc1InArgs.ancData.buf = (XDAS_Int8 *) aenc1->ancBuf.start;
	}
	else
	{
		enc1InArgs.ancData.bufSize = 0;
		enc1InArgs.ancData.buf = NULL;
	}

	dvtb_processDebug(aenc1);
	
	timeStmpBfrEnc = dvtb_getTime( );
	status = AUDENC1_process(aenc1->audenc1Hdl, &aenc1->inBuf, &aenc1->outBuf, (IAUDENC1_InArgs *) &enc1InArgs, (IAUDENC1_OutArgs *) &enc1OutArgs);
	timeStmpAftrEnc = dvtb_getTime( );

	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	aenc1->Framenum++;

	SYS_DEBUG("\tCurr frame number : %d\n", aenc1->Framenum);

	aenc1->outsamples = enc1OutArgs.bytesGenerated;
	aenc1->consumedInsamples = enc1OutArgs.numInSamples;

	if (status != IAUDENC1_EOK)
	{
		SYS_ERROR("Error (%d) in Audio Encoder Process\n", (int) status);
		SYS_ERROR("Codec Error => %d\n", (int) enc1OutArgs.extendedError);

		retCode = DVEVM_ST_FAIL;
	}

	if(DVEVM_ST_FAIL != retCode)
	{
		aenc1->audenc1Cmd = XDM_GETSTATUS;

		if (DVEVM_ST_FAIL == dvtb_audEnc1Control(aenc1))
		{
			SYS_ERROR("Unable to get status info\n");
		}
		SYS_DEBUG("\tBytes Generated after STATUSCALL=> %d\n", (int) enc1OutArgs.bytesGenerated);
	}

	return retCode;
}

DvevmStRetCode
dvtb_audEnc1Control(DvevmStAudEnc1Info *aenc1)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	int status = -1, i = 0;

	ASSERT(aenc1 != NULL);
	ASSERT(aenc1->audenc1Hdl != NULL);

	status = AUDENC1_control(aenc1->audenc1Hdl, aenc1->audenc1Cmd, &aenc1->audenc1DynParams, &aenc1->audenc1Status);

	if (IAUDENC1_EOK != status)
	{
		SYS_ERROR("Audio Encode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{

		if (XDM_GETBUFINFO == aenc1->audenc1Cmd)
		{
			aenc1->inBuf.numBufs = aenc1->audenc1Status.bufInfo.minNumInBufs;
			aenc1->outBuf.numBufs = aenc1->audenc1Status.bufInfo.minNumOutBufs;

			for (i = 0; i < aenc1->inBuf.numBufs; i++)
				aenc1->inBuf.descs[i].bufSize = aenc1->audenc1Status.bufInfo.minInBufSize[i];

			for (i = 0; i < aenc1->outBuf.numBufs; i++)
				aenc1->outBuf.descs[i].bufSize = aenc1->audenc1Status.bufInfo.minOutBufSize[i];
		}

		SYS_DEBUG("Audio Encode Control => Command : %d\n", aenc1->audenc1Cmd);
	}

	return retCode;
}

DvevmStRetCode
dvtb_audEnc1Close(DvevmStAudEnc1Info *aenc1)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	dvtb_audEnc1Cleanup(aenc1);
	return retCode;
}
