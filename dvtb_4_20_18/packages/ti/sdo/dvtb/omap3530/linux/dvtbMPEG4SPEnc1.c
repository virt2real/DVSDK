/*
 * dvtbMPEG4SPEnc1.c
 *
 * XDM1.0 MPEG4 SP Encode Interface implementation
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

#include "dvtbMPEG4SPEnc1.h"
#include "dvtbMemory.h"

static XDAS_Int32 outBufSize[XDM_MAX_IO_BUFFERS];

void
dvtb_mpeg4spEncInitDebug(IMP4VENC_Params *vep)
{
	SYS_DEBUG("\n<======== MPEG4SP Encoder Initialize Debug Start ==========>\n");
	SYS_DEBUG("Encoding Preset    : %d\n", (int) vep->videncParams.encodingPreset);
	SYS_DEBUG("Rate Ctrl Preset   : %d\n", (int) vep->videncParams.rateControlPreset);
	SYS_DEBUG("Max Height         : %d\n", (int) vep->videncParams.maxHeight);
	SYS_DEBUG("Max Width          : %d\n", (int) vep->videncParams.maxWidth);
	SYS_DEBUG("Max Frame Rate     : %d\n", (int) vep->videncParams.maxFrameRate);
	SYS_DEBUG("Max Bit Rate       : %d\n", (int) vep->videncParams.maxBitRate);
	SYS_DEBUG("Endianness         : %d\n", (int) vep->videncParams.dataEndianness);
	SYS_DEBUG("Max Inter Frame    : %d\n", (int) vep->videncParams.maxInterFrameInterval);
	SYS_DEBUG("Input Chroma Fmt   : %d\n", (int) vep->videncParams.inputChromaFormat);
	SYS_DEBUG("Input Content      : %d\n", (int) vep->videncParams.inputContentType);
	SYS_DEBUG("encodeMode         : %d\n", (int) vep->encodeMode);
	SYS_DEBUG("levelIdc           : %d\n", (int) vep->levelIdc);
	SYS_DEBUG("numFrames          : %d\n", (int) vep->numFrames);
	SYS_DEBUG("rcAlgo             : %d\n", (int) vep->rcAlgo);
	SYS_DEBUG("vbvBufferSize      : %d\n", (int) vep->vbvBufferSize);
	SYS_DEBUG("vbvParamEnable     : %d\n", (int) vep->vbvParamEnable);
	SYS_DEBUG("useVOS             : %d\n", (int) vep->useVOS);
	SYS_DEBUG("useGOV             : %d\n", (int) vep->useGOV);
	SYS_DEBUG("useDataPartition   : %d\n", (int) vep->useDataPartition);
	SYS_DEBUG("useRVLC            : %d\n", (int) vep->useRVLC);
	SYS_DEBUG("maxDelay           : %d\n", (int) vep->maxDelay);
	SYS_DEBUG("h263SliceMode      : %d\n", (int) vep->h263SliceMode);
	SYS_DEBUG("\n<======== MPEG4SP Encoder Initialize Debug End ============>\n\n");

}

void
dvtb_mpeg4spEncProcessDebug(IMP4VENC_OutArgs *veo)
{
	SYS_DEBUG("\n<======== MPEG4SP Encoder Process Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) veo->videncOutArgs.extendedError);
	SYS_DEBUG("Bytes Generated    : %d\n", (int) veo->videncOutArgs.bytesGenerated);
	SYS_DEBUG("Encoded Frame Type : %d\n", (int) veo->videncOutArgs.encodedFrameType);
	SYS_DEBUG("Input Frame Skip   : %d\n", (int) veo->videncOutArgs.inputFrameSkip);
	SYS_DEBUG("\n<======== MPEG4SP Encoder Process Debug End ============>\n");
}

void
dvtb_mpeg4spEncControlDebug(IMP4VENC_Status *ves)
{
	int i = 0;

	SYS_DEBUG("\n<======== MPEG4SP Encoder Control Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ves->videncStatus.extendedError);
	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ves->videncStatus.bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ves->videncStatus.bufInfo.minNumOutBufs);

	for (i = 0; i < ves->videncStatus.bufInfo.minNumInBufs; i++)
		SYS_DEBUG("BUF-Min In Size  [%d]  : %d\n", i, (int) ves->videncStatus.bufInfo.minInBufSize[i]);

	for (i = 0; i < ves->videncStatus.bufInfo.minNumOutBufs; i++)
		SYS_DEBUG("BUF-Min Out Size  [%d] : %d\n", i,
				(int) ves->videncStatus.bufInfo.minOutBufSize[i]);

	SYS_DEBUG("mvDataSize      : %d\n", (int) ves->mvDataSize);
	SYS_DEBUG("numPacketse     : %d\n", (int) ves->numPackets);

	SYS_DEBUG("\n<======== MPEG4SP Encoder Control Debug End ============>\n");
}

void
dvtb_mpeg4spEncCleanup(DvevmStMPEG4SPVEncInfo *ve)
{
	if (NULL != ve->venc1Hdl) {
		VIDENC1_delete(ve->venc1Hdl);
		ve->venc1Hdl = NULL;
	}

}

DvevmStRetCode
dvtb_mpeg4spEnc1Init(DvevmStMPEG4SPVEncInfo *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);
	ASSERT(ve->venc1Name[0] != 0);

	ve->outBufDesc.bufSizes = (XDAS_Int32 *) outBufSize;
//		SYS_OUT("videnc_params.size : %d\n", (int) ve->venc1Params.videncParams.size);
//		SYS_OUT("encodeMode         : %d\n", (int) ve->venc1Params.encodeMode);
//		SYS_OUT("levelIdc           : %d\n", (int) ve->venc1Params.levelIdc);
//		SYS_OUT("numFrames          : %d\n", (int) ve->venc1Params.numFrames);
//		SYS_OUT("rcAlgo             : %d\n", (int) ve->venc1Params.rcAlgo);
//		SYS_OUT("vbvBufferSize      : %d\n", (int) ve->venc1Params.vbvBufferSize);
//		SYS_OUT("vbvParamEnable     : %d\n", (int) ve->venc1Params.vbvParamEnable);
//		SYS_OUT("useVOS             : %d\n", (int) ve->venc1Params.useVOS);
//		SYS_OUT("useGOV             : %d\n", (int) ve->venc1Params.useGOV);
//		SYS_OUT("useDataPartition   : %d\n", (int) ve->venc1Params.useDataPartition);
//		SYS_OUT("useRVLC            : %d\n", (int) ve->venc1Params.useRVLC);
//		SYS_OUT("maxDelay           : %d\n", (int) ve->venc1Params.maxDelay);
//		SYS_OUT("h263SliceMode      : %d\n", (int) ve->venc1Params.h263SliceMode);

	if (NULL == (ve->venc1Hdl = VIDENC1_create(ve->ceHdl, ve->venc1Name, (IVIDENC1_Params *) &ve->venc1Params)))
	{
		SYS_ERROR("Unable to initialize MPEG4SP Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Encoder initialised\n");
		dvtb_mpeg4spEncInitDebug(&ve->venc1Params);

		ve->venc1Cmd = XDM_SETPARAMS;

		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Control(ve))
		{
			SYS_ERROR("Unable to set encoder dynamic parameters\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			ve->venc1Cmd = XDM_GETBUFINFO;
			if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Control(ve))
			{
				SYS_ERROR("Unable to get buffer information\n");
				retCode = DVEVM_ST_FAIL;
			}
		}
	}

	if(DVEVM_ST_FAIL == retCode)
		dvtb_mpeg4spEncCleanup(ve);

	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spEnc1Encode(DvevmStMPEG4SPVEncInfo *ve, int *encDuration)
{
	XDAS_Int32 status = -1;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);
	ASSERT(ve->venc1Hdl != NULL);
	ASSERT(ve->inBufDesc.numBufs > 0);
	ASSERT(ve->outBufDesc.numBufs > 0);

	ve->venc1InArgs.videncInArgs.size = sizeof(ve->venc1InArgs);
	ve->venc1OutArgs.videncOutArgs.size = sizeof(ve->venc1OutArgs);

	timeStmpBfrEnc = dvtb_getTime();

	status = VIDENC1_process(ve->venc1Hdl, &(ve->inBufDesc), &(ve->outBufDesc), (IVIDENC1_InArgs *) &(ve->venc1InArgs), (IVIDENC1_OutArgs *) &(ve->venc1OutArgs));

	timeStmpAftrEnc = dvtb_getTime();

	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != VIDENC1_EOK)
	{
		SYS_ERROR("MPEG4SP Encode Process failed (%d), Codec Error : %d\n",
				(int) status, (int) ve->venc1OutArgs.videncOutArgs.extendedError);

		if((1 << XDM_PARAMSCHANGE) & ve->venc1OutArgs.videncOutArgs.extendedError )
		{
			SYS_ERROR("Error: Sequence Parameters Change \n");
		}
		if((1 << XDM_APPLIEDCONCEALMENT) & ve->venc1OutArgs.videncOutArgs.extendedError )
                {
                        SYS_ERROR("Error: Applied concealment \n");
                }
                if((1 << XDM_INSUFFICIENTDATA) & ve->venc1OutArgs.videncOutArgs.extendedError )
                {
                        SYS_ERROR("Error: Insufficient data\n");
                }
                if((1 << XDM_CORRUPTEDDATA ) & ve->venc1OutArgs.videncOutArgs.extendedError )
                {
                        SYS_ERROR("Error: Data problem/corruption\n");
                }
                if((1 << XDM_CORRUPTEDHEADER ) & ve->venc1OutArgs.videncOutArgs.extendedError )
                {
                        SYS_ERROR("Error: Header problem/corruption\n");
                }
		if((1 << XDM_UNSUPPORTEDINPUT ) & ve->venc1OutArgs.videncOutArgs.extendedError )
                {
                        SYS_ERROR("Error: Unsupported feature/parameter in input\n");
                }
                if((1 << XDM_UNSUPPORTEDPARAM ) & ve->venc1OutArgs.videncOutArgs.extendedError )
                {
                        SYS_ERROR("Error: Unsupported input parameter or configuration \n");
		}
                if((1 << XDM_FATALERROR ) & ve->venc1OutArgs.videncOutArgs.extendedError )
                {
                        SYS_ERROR("Fatal Error \n");
			retCode = DVEVM_ST_FAIL;
                }
		else
		{
			 SYS_ERROR("NON Error  \n");
		}
	}

	if(DVEVM_ST_FAIL != retCode)
		dvtb_mpeg4spEncProcessDebug(&ve->venc1OutArgs);

	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spEnc1Control(DvevmStMPEG4SPVEncInfo *ve)
{
	int status = -1, i = 0,processTime = 0;
	DvevmStTime timeStmpBfrCtrl, timeStmpAftrCtrl;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);
//	SYS_OUT("videncDynamicParams.size : %d\n", (int) ve->venc1DynParams.videncDynamicParams.size);
//	SYS_OUT("fcode                    : %d\n", (int) ve->venc1DynParams.fCode);

	timeStmpBfrCtrl = dvtb_getTime();

	status = VIDENC1_control(ve->venc1Hdl, ve->venc1Cmd, (IVIDENC1_DynamicParams *) &ve->venc1DynParams, (IVIDENC1_Status *) &ve->venc1Status);

	timeStmpAftrCtrl = dvtb_getTime();

	processTime = ((timeStmpAftrCtrl.tv_sec * NUM_MICROSECS_IN_SEC)	+ timeStmpAftrCtrl.tv_usec) - ((timeStmpBfrCtrl.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrCtrl.tv_usec);

	if (VIDENC1_EOK != status)
	{
		SYS_ERROR("Error (%d), Codec Error (%d) in MPEG4SP Encoder Control\n", status, (int) ve->venc1Status.videncStatus.extendedError);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		if (XDM_SETPARAMS == ve->venc1Cmd)
		{
			SYS_DEBUG("MPEG4SP Encode Control => Command : %d\n", ve->venc1Cmd);
			SYS_DEBUG("Input Height     : %d\n", (int) ve->venc1DynParams.videncDynamicParams.inputHeight);
			SYS_DEBUG("Input Width      : %d\n", (int) ve->venc1DynParams.videncDynamicParams.inputWidth);
			SYS_DEBUG("Ref Frame Rate   : %d\n", (int) ve->venc1DynParams.videncDynamicParams.refFrameRate);
			SYS_DEBUG("Tgt Frame Rate   : %d\n", (int) ve->venc1DynParams.videncDynamicParams.targetFrameRate);
			SYS_DEBUG("Target Bit Rate  : %d\n", (int) ve->venc1DynParams.videncDynamicParams.targetBitRate);
		}
		else
		{
			if (XDM_GETBUFINFO == ve->venc1Cmd)
			{

				ve->inBuf.numBufs = ve->venc1Status.videncStatus.bufInfo.minNumInBufs;
				for (i = 0; i < ve->inBuf.numBufs; i++)
					ve->inBuf.bufSizes[i] = ve->venc1Status.videncStatus.bufInfo.minInBufSize[i];

				ve->outBuf.numBufs = ve->venc1Status.videncStatus.bufInfo.minNumOutBufs;
				for (i = 0; i < ve->outBuf.numBufs; i++)
					ve->outBuf.bufSizes[i] = ve->venc1Status.videncStatus.bufInfo.minOutBufSize[i];
			}
		}
	}

	if(DVEVM_ST_FAIL != retCode)
		dvtb_mpeg4spEncControlDebug(&ve->venc1Status);

	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spEnc1Close(DvevmStMPEG4SPVEncInfo *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	/* free buffers */
	if (ve->inBuf.numBufs > 0)
	{
		dvtb_freeCmem(&ve->inBuf);
	}

	if (ve->outBuf.numBufs > 0)
	{
		dvtb_freeCmem(&ve->outBuf);
	}

	dvtb_mpeg4spEncCleanup(ve);

	return retCode;
}
