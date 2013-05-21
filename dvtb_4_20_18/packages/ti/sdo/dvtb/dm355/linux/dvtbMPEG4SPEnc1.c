/*
 * dvtbMPEG4SPEnc1.c
 *
 * XDM1.0 MPEG4 SP Encode interface implementation
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
	SYS_DEBUG("subWindowHeight    : %d\n", (int) vep->subWindowHeight);
	SYS_DEBUG("subWindowWidth     : %d\n", (int) vep->subWindowWidth);
	SYS_DEBUG("SVH                : %d\n", (int) vep->svhMode);
	SYS_DEBUG("rotation           : %d\n", (int) vep->rotation);

	SYS_DEBUG("IFrameBitRateBiasFactor : %d\n", (int) vep->IFrameBitRateBiasFactor);
	SYS_DEBUG("PFrameBitRateBiasFactor : %d\n", (int) vep->PFrameBitRateBiasFactor);
	SYS_DEBUG("peakBufWindow      : %d\n", (int) vep->peakBufWindow);
	SYS_DEBUG("minBitRate         : %d\n", (int) vep->minBitRate);

	SYS_DEBUG("VBVSize            : %d\n", (int) vep->vbvSize);

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

	ve->venc1InArgs.insertUserData = 0;
	ve->venc1InArgs.lengthUserData = 0;
	ve->venc1InArgs.subWindowHozOfst = 0;
	ve->venc1InArgs.subWindowVerOfst = 0;

	timeStmpBfrEnc = dvtb_getTime();

	status = VIDENC1_process(ve->venc1Hdl, &(ve->inBufDesc), &(ve->outBufDesc), (IVIDENC1_InArgs *) &(ve->venc1InArgs), (IVIDENC1_OutArgs *) &(ve->venc1OutArgs));

	timeStmpAftrEnc = dvtb_getTime();

	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != VIDENC1_EOK)
	{
		SYS_ERROR("MPEG4SP Encode Process failed (%d), Codec Error : %d\n",
				(int) status, (int) ve->venc1OutArgs.videncOutArgs.extendedError);
		retCode = DVEVM_ST_FAIL;
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
