/*
 * dvtbWMAEnc1.c
 *
 * XDM1.0 WMA Encode Interface implementation
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

#include "dvtbWMAEnc1.h"
#include "dvtbMemory.h"

void
dvtb_wmaCreateDebug(DvevmStWmaEnc1Info *ae)
{
	SYS_DEBUG("\tHandle  : %s\n", ae->aenc1Name);
	SYS_DEBUG("\tHandle  : %d\n", (int) ae->ceHdl);
	SYS_DEBUG("\tBase size  : %d\n", (int) ae->aenc1Params.audenc_params.size);
	SYS_DEBUG("\tBase sample Rate  : %d\n", (int) ae->aenc1Params.audenc_params.sampleRate);
	SYS_DEBUG("\tBase bitRate   :%d \n", (int) ae->aenc1Params.audenc_params.bitRate);
	SYS_DEBUG("\tBase channel Mode : %d\n", (int) ae->aenc1Params.audenc_params.channelMode);
	SYS_DEBUG("\tBase endianness : %d\n", (int) ae->aenc1Params.audenc_params.dataEndianness);
	SYS_DEBUG("\tBase encmode : %d\n", (int) ae->aenc1Params.audenc_params.encMode);
	SYS_DEBUG("\tBase input format : %d\n", (int) ae->aenc1Params.audenc_params.inputFormat);
	SYS_DEBUG("\tBase inp bits :%d\n", (int) ae->aenc1Params.audenc_params.inputBitsPerSample);
	SYS_DEBUG("\tBase maxbitrate : %d\n", (int) ae->aenc1Params.audenc_params.maxBitRate);
	SYS_DEBUG("\tBase dual mono :%d\n", (int) ae->aenc1Params.audenc_params.dualMonoMode);
	SYS_DEBUG("\tBase CRC flag : %d\n", (int) ae->aenc1Params.audenc_params.crcFlag);
	SYS_DEBUG("\tBase ancflag :%d\n", (int) ae->aenc1Params.audenc_params.ancFlag);
	SYS_DEBUG("\tBase lfe flag:%d\n", (int) ae->aenc1Params.audenc_params.lfeFlag);
	SYS_DEBUG("\tExt iBitRate_var:%d\n", (int) ae->aenc1Params.iBitRate_var);
	SYS_DEBUG("\tInbufsize :%d\n", (int) ae->inBuf.descs[0].bufSize);
	SYS_DEBUG("\tOutbufsize :%d\n", (int) ae->outBuf.descs[0].bufSize);
	SYS_DEBUG("\tEntering create\n");
}

void
dvtb_wmaProcessDebug(DvevmStWmaEnc1Info *ae)
{
	SYS_DEBUG("\enc name  : %s\n", ae->aenc1Name);
	SYS_DEBUG("\tHandle  : %d\n", (int) ae->ceHdl);
	SYS_DEBUG("\tBase size  : %d\n", (int) ae->aenc1Params.audenc_params.size);
	SYS_DEBUG("\tBase sample Rate  : %d\n", (int) ae->aenc1Params.audenc_params.sampleRate);
	SYS_DEBUG("\tBase bitRate   :%d \n", (int) ae->aenc1Params.audenc_params.bitRate);
	SYS_DEBUG("\tBase channel Mode : %d\n", (int) ae->aenc1Params.audenc_params.channelMode);
	SYS_DEBUG("\tBase endianness : %d\n", (int) ae->aenc1Params.audenc_params.dataEndianness);
	SYS_DEBUG("\tBase encmode : %d\n", (int) ae->aenc1Params.audenc_params.encMode);
	SYS_DEBUG("\tBase input format : %d\n", (int) ae->aenc1Params.audenc_params.inputFormat);
	SYS_DEBUG("\tBase inp bits :%d\n", (int) ae->aenc1Params.audenc_params.inputBitsPerSample);
	SYS_DEBUG("\tBase maxbitrate : %d\n", (int) ae->aenc1Params.audenc_params.maxBitRate);
	SYS_DEBUG("\tBase dual mono :%d\n", (int) ae->aenc1Params.audenc_params.dualMonoMode);
	SYS_DEBUG("\tBase CRC flag : %d\n", (int) ae->aenc1Params.audenc_params.crcFlag);
	SYS_DEBUG("\tBase ancflag :%d\n", (int) ae->aenc1Params.audenc_params.ancFlag);
	SYS_DEBUG("\tBase lfe flag:%d\n", (int) ae->aenc1Params.audenc_params.lfeFlag);
	SYS_DEBUG("\tExt iBitRate_var:%d\n",(int) ae->aenc1Params.iBitRate_var);
	SYS_DEBUG("\tHandle  : %d\n", (int) ae->aenc1Hdl);
	SYS_DEBUG("\tEntering process call\n");
}

void
dvtb_wmacontrolenterDebug(DvevmStWmaEnc1Info *ae)
{
	SYS_DEBUG("################ENTERING CONTROL CALL#########################\n");

	SYS_DEBUG("\enc name  : %s\n", ae->aenc1Name);
	SYS_DEBUG("\tHandle  : %d\n", (int) ae->ceHdl);
	SYS_DEBUG("\tBase size  : %d\n", (int) ae->aenc1Params.audenc_params.size);
	SYS_DEBUG("\tBase sample Rate  : %d\n", (int) ae->aenc1Params.audenc_params.sampleRate);
	SYS_DEBUG("\tBase bitRate   :%d \n", (int) ae->aenc1Params.audenc_params.bitRate);
	SYS_DEBUG("\tBase channel Mode : %d\n", (int) ae->aenc1Params.audenc_params.channelMode);
	SYS_DEBUG("\tBase endianness : %d\n", (int) ae->aenc1Params.audenc_params.dataEndianness);
	SYS_DEBUG("\tBase encmode : %d\n", (int) ae->aenc1Params.audenc_params.encMode);
	SYS_DEBUG("\tBase input format : %d\n", (int) ae->aenc1Params.audenc_params.inputFormat);
	SYS_DEBUG("\tBase inp bits :%d\n", (int) ae->aenc1Params.audenc_params.inputBitsPerSample);
	SYS_DEBUG("\tBase maxbitrate : %d\n", (int) ae->aenc1Params.audenc_params.maxBitRate);
	SYS_DEBUG("\tBase dual mono :%d\n", (int) ae->aenc1Params.audenc_params.dualMonoMode);
	SYS_DEBUG("\tBase CRC flag : %d\n", (int) ae->aenc1Params.audenc_params.crcFlag);
	SYS_DEBUG("\tBase ancflag :%d\n", (int) ae->aenc1Params.audenc_params.ancFlag);
	SYS_DEBUG("\tBase lfe flag:%d\n", (int) ae->aenc1Params.audenc_params.lfeFlag);
	SYS_DEBUG("\tExt iBitRate_var:%d\n",(int) ae->aenc1Params.iBitRate_var);
	SYS_DEBUG("\tInbufsize :%d\n", (int) ae->inBuf.descs[0].bufSize);
	SYS_DEBUG("\tOutbufsize :%d\n", (int) ae->outBuf.descs[0].bufSize);
	SYS_DEBUG("\tCmd id :%d\n", ae->aenc1Cmd);
}
void
dvtb_wmacontrolexitDebug(DvevmStWmaEnc1Info *ae)
{
	SYS_DEBUG("################LEFT CONTROL CALL#########################\n");

	SYS_DEBUG("\t#####STATUS##########################\n");
	SYS_DEBUG("\tsize:%d\n", (int) ae->aenc1Status.audenc_status.size);
	SYS_DEBUG("\tEerror:%d\n", (int) ae->aenc1Status.audenc_status.extendedError);
	SYS_DEBUG("\tvalidflag:%d\n", (int) ae->aenc1Status.audenc_status.validFlag);
	SYS_DEBUG("\tlfeflag:%d\n", (int) ae->aenc1Status.audenc_status.lfeFlag);
	SYS_DEBUG("\tbitRate:%d\n", (int) ae->aenc1Status.audenc_status.bitRate);
	SYS_DEBUG("\tsampleRate:%d\n", (int) ae->aenc1Status.audenc_status.sampleRate);
	SYS_DEBUG("\tchannelMode:%d\n", (int) ae->aenc1Status.audenc_status.channelMode);
	SYS_DEBUG("\tnMaxSamplesPerPacket:%d\n", (int) ae->aenc1Status.nMaxSamplesPerPacket);
	SYS_DEBUG("\tnBlockAlign:%d\n", (int) ae->aenc1Status.nBlockAlign);
	SYS_DEBUG("\twEncodeOptions:%d\n", (int) ae->aenc1Status.wEncodeOptions);
	SYS_DEBUG("\tiBitRateVar:%d\n", (int) ae->aenc1Status.iBitRateVar);
	SYS_DEBUG("\tiFramesPerPacket:%d\n", (int) ae->aenc1Status.iFramesPerPacket);
	SYS_DEBUG("\tiSamplesPerFrame:%d\n", (int) ae->aenc1Status.iSamplesPerFrame);
	SYS_DEBUG("Minimum inBufs :%d\n", (int) ae->aenc1Status.audenc_status.bufInfo.minNumInBufs);
	SYS_DEBUG("Minimum outBufs :%d\n", (int) ae->aenc1Status.audenc_status.bufInfo.minNumOutBufs);
	SYS_DEBUG("Minimum inBuf size :%d\n", (int) ae->aenc1Status.audenc_status.bufInfo.minInBufSize[0]);
	SYS_DEBUG("Minimum outBuf size :%d\n", (int) ae->aenc1Status.audenc_status.bufInfo.minOutBufSize[0]);
	SYS_DEBUG("\t#####END OF STATUS##########################\n");
}

void
dvtb_wmaEnc1Cleanup(DvevmStWmaEnc1Info *ae)
{
	if (NULL != ae->aenc1Hdl)
		AUDENC1_delete((AUDENC1_Handle) ae->aenc1Hdl);

	ae->aenc1Hdl = NULL;

	if (ae->inBuf.numBufs > 0)
		dvtb_freeCmemXdm1BufDesc(&ae->inBuf);

	if (ae->outBuf.numBufs > 0)
		dvtb_freeCmemXdm1BufDesc(&ae->outBuf);

	if (NULL != ae->ancBuf.start)
		dvtb_freeSingleBufCmem(ae->ancBuf.start, ae->ancBuf.size);
}

DvevmStRetCode
dvtb_wmaEnc1Init(DvevmStWmaEnc1Info *ae)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	ASSERT(ae != NULL);
	ASSERT(ae->ceHdl != NULL);
	ASSERT(ae->aenc1Name[0] != 0);

	ae->ancBuf.start = NULL;
	ae->inBuf.numBufs = 0;
	ae->outBuf.numBufs = 0;

	dvtb_wmaCreateDebug(ae);
	if (NULL == (ae->aenc1Hdl = (AUDENC1_Handle) AUDENC1_create(ae->ceHdl, ae->aenc1Name, (IAUDENC1_Params *) &ae->aenc1Params)))
	{
		SYS_ERROR("Unable to initialize Audio Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		ae->ancBuf.size = 14;

#if 1
		ae->aenc1Cmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_wmaEnc1Control(ae))
		{
			SYS_ERROR("Unable to set the dynamic parameters \n");
			retCode = DVEVM_ST_FAIL;
		}
		else
#endif
		{
			ae->aenc1Cmd = XDM_GETBUFINFO;
			if (DVEVM_ST_FAIL == dvtb_wmaEnc1Control(ae))
			{
				SYS_ERROR("Unable to get the input/output buffer information\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (DVEVM_ST_FAIL == dvtb_allocCmemXdm1BufDesc(&ae->inBuf))
			{
				SYS_ERROR("Unable to allocate memory for In Buffer\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (DVEVM_ST_FAIL == dvtb_allocCmemXdm1BufDesc(&ae->outBuf))
			{
				SYS_ERROR("Unable to allocate memory for Out Buffer\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (NULL == (ae->ancBuf.start = Memory_contigAlloc(ae->ancBuf.size, Memory_DEFAULTALIGNMENT)))
			{
				SYS_ERROR("Unable to allocate memory for Out Buffer\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_DEBUG("\tAudio Encoder %s initialized.\n", ae->aenc1Name);
				memcpy(ae->ancBuf.start, "DVTB Encoded", ae->ancBuf.size);
				SYS_DEBUG("\tancBuf.start :%x\n", (unsigned int) ae->ancBuf.start);
			}
		}
	}
	if(DVEVM_ST_FAIL == retCode)
		dvtb_wmaEnc1Cleanup(ae);
	return retCode;
}

DvevmStRetCode
dvtb_wmaEnc1Encode(DvevmStWmaEnc1Info *ae, int *encDuration)
{
	XDAS_Int32 status = -1;
	ITTIAM_WMAENC_InArgs enc1InArgs;
	ITTIAM_WMAENC_OutArgs enc1OutArgs;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	ASSERT(ae != NULL);
	ASSERT(ae->ceHdl != NULL);
	ASSERT(ae->aenc1Hdl != NULL);

	enc1OutArgs.audenc_outArgs.size = sizeof(ITTIAM_WMAENC_OutArgs);

	enc1InArgs.audenc_inArgs.size = sizeof(ITTIAM_WMAENC_InArgs);
	enc1InArgs.audenc_inArgs.numInSamples = ae->insamples;
	if (ae->aenc1Params.audenc_params.ancFlag)
	{
		enc1InArgs.audenc_inArgs.ancData.bufSize = ae->ancBuf.size;
		enc1InArgs.audenc_inArgs.ancData.buf = (XDAS_Int8 *) ae->ancBuf.start;
	}
	else
	{
		enc1InArgs.audenc_inArgs.ancData.bufSize = 0;
		enc1InArgs.audenc_inArgs.ancData.buf = NULL;
	}

	dvtb_wmaProcessDebug(ae);

	timeStmpBfrEnc = dvtb_getTime( );
	status = AUDENC1_process((AUDENC1_Handle) ae->aenc1Hdl, &ae->inBuf, &ae->outBuf, (IAUDENC1_InArgs *) &enc1InArgs, (IAUDENC1_OutArgs *) &enc1OutArgs);
	timeStmpAftrEnc = dvtb_getTime( );

	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	ae->Framenum++;

	SYS_DEBUG("\tCurr frame number : %d\n", ae->Framenum);

	ae->outsamples = enc1OutArgs.audenc_outArgs.bytesGenerated;

	if (status != IAUDENC1_EOK)
	{
		SYS_ERROR("Error (%d) in Audio Encoder Process\n", (int) status);
		SYS_ERROR("Codec Error => %d\n", (int) enc1OutArgs.audenc_outArgs.extendedError);
		SYS_ERROR("End of execution                => %d\n", (int) enc1OutArgs.i_exec_done);
		SYS_ERROR("i_num_samples_in_packet         => %d\n", (int) enc1OutArgs.i_num_samples_in_packet);

		retCode = DVEVM_ST_FAIL;
	}
	if (DVEVM_ST_FAIL != retCode)
	{

		ae->aenc1Cmd = XDM_GETSTATUS;

		if (DVEVM_ST_FAIL == dvtb_wmaEnc1Control(ae))
		{
			SYS_ERROR("Unable to get status info\n");
		}
		SYS_DEBUG("\tBytes Generated after STATUSCALL=> %d\n", (int) enc1OutArgs.audenc_outArgs.bytesGenerated);
		SYS_DEBUG("\tEnd of execution                => %d\n", (int) enc1OutArgs.i_exec_done);
		ae->consumedSamples = enc1OutArgs.audenc_outArgs.numInSamples;

	}

	return retCode;
}

DvevmStRetCode
dvtb_wmaEnc1Control(DvevmStWmaEnc1Info *ae)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	int status = -1, i = 0;

	ASSERT(ae != NULL);
	ASSERT(ae->aenc1Hdl != NULL);
	dvtb_wmacontrolenterDebug(ae);

	status = AUDENC1_control((AUDENC1_Handle) ae->aenc1Hdl, ae->aenc1Cmd, (IAUDENC1_DynamicParams *) &ae->aenc1DynParams, (IAUDENC1_Status *) &ae->aenc1Status);
	if (IAUDENC1_EOK != status)
	{
		SYS_ERROR("Audio Encode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		if (XDM_GETBUFINFO == ae->aenc1Cmd)
		{
			ae->inBuf.numBufs = ae->aenc1Status.audenc_status.bufInfo.minNumInBufs;
			ae->outBuf.numBufs = ae->aenc1Status.audenc_status.bufInfo.minNumOutBufs;

			for (i = 0; i < ae->inBuf.numBufs; i++)
				ae->inBuf.descs[i].bufSize = ae->aenc1Status.audenc_status.bufInfo.minInBufSize[i];

			for (i = 0; i < ae->outBuf.numBufs; i++)
				ae->outBuf.descs[i].bufSize = ae->aenc1Status.audenc_status.bufInfo.minOutBufSize[i];
		}

		SYS_DEBUG("Audio Encode Control => Command : %d\n", ae->aenc1Cmd);
		dvtb_wmacontrolexitDebug(ae);
	}
	return retCode;
}

DvevmStRetCode
dvtb_wmaEnc1Close(DvevmStWmaEnc1Info *ae)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	dvtb_wmaEnc1Cleanup(ae);
	return retCode;
}
