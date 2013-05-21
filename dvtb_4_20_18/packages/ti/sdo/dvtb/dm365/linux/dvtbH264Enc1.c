/*
 * dvtbH264Enc1.c
 *
 * XDM1.0 H264 Encode Interface implementation
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

#include "dvtbH264Enc1.h"
#include "dvtbMemory.h"

void
dvtb_h264Enc1XDM1SingleBufDescDebug(XDM1_SingleBufDesc *sbd)
{
	SYS_DEBUG("\tbuf                   : %x\n", (int) sbd->buf);
	SYS_DEBUG("\tbufSize               : %d\n", (int) sbd->bufSize);
	SYS_DEBUG("\taccessMask            : %d\n", (int) sbd->accessMask);
}

void
dvtb_h264Enc1IVIDEO1_BufDescDebug(IVIDEO1_BufDesc *bd)
{
	int i = 0;

	SYS_DEBUG("\tNumBufs               : %d\n", (int) bd->numBufs);
	SYS_DEBUG("\tframeWidth            : %d\n", (int) bd->frameWidth);
	SYS_DEBUG("\tframeHeight           : %d\n", (int) bd->frameHeight);
	SYS_DEBUG("\tframePitch            : %d\n", (int) bd->framePitch);

	//The following loop is for XDM1_SingleBufDesc bufDesc[3];
	for (i = 0; i < 3; i++)
	{
		SYS_DEBUG("\tbufDesc[%d]             :\n", i);
		dvtb_h264Enc1XDM1SingleBufDescDebug(&bd->bufDesc[i]);
	}

	SYS_DEBUG("\textendedError         : %d\n", (int) bd->extendedError);
	SYS_DEBUG("\tframeType             : %d\n", (int) bd->frameType);
	SYS_DEBUG("\ttopFieldFirstFlag     : %d\n", (int) bd->topFieldFirstFlag);
	SYS_DEBUG("\trepeatFirstFieldFlag  : %d\n", (int) bd->repeatFirstFieldFlag);
	SYS_DEBUG("\tframeStatus           : %d\n", (int) bd->frameStatus);
	SYS_DEBUG("\trepeatFrame           : %d\n", (int) bd->repeatFrame);
	SYS_DEBUG("\tcontentType           : %d\n", (int) bd->contentType);
	SYS_DEBUG("\tchromaFormat          : %d\n", (int) bd->chromaFormat);
}

void
dvtb_h264Enc1InitDebug(IH264VENC_Params *vep)
{
	SYS_DEBUG("\n<======== Video Encoder Params Debug Start ==========>\n");
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
	SYS_DEBUG("Recon format       : %d\n", (int) vep->videncParams.reconChromaFormat);
	SYS_DEBUG("\n<======== Video Encoder Params Debug End ============>\n\n");
}

void
dvtb_h264Enc1InArgsDebug(IH264VENC_InArgs *vei)
{
	SYS_DEBUG("\n<======== Video Encoder InArgs Debug Start ==========>\n");
	SYS_DEBUG("Size                 : %d\n", (int) vei->videncInArgs.size);
	SYS_DEBUG("inputID              : %d\n", (int) vei->videncInArgs.inputID);
	SYS_DEBUG("topFieldFirstFlag    : %d\n", (int) vei->videncInArgs.topFieldFirstFlag);
	SYS_DEBUG("\n<======== Video Encoder InArgs Debug End ============>\n");
}

void
dvtb_h264Enc1ProcessDebug(IH264VENC_OutArgs *veo)
{
	SYS_DEBUG("\n<======== Video Encoder OutArgs Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) veo->videncOutArgs.extendedError);
	SYS_DEBUG("Bytes Generated    : %d\n", (int) veo->videncOutArgs.bytesGenerated);
	SYS_DEBUG("Encoded Frame Type : %d\n", (int) veo->videncOutArgs.encodedFrameType);
	SYS_DEBUG("Input Frame Skip   : %d\n", (int) veo->videncOutArgs.inputFrameSkip);
	SYS_DEBUG("Output ID 		: %d\n", (int) veo->videncOutArgs.outputID);

	//XDM1_SingleBufDesc encodedBuf;
	SYS_DEBUG("encodedBuf            :\n");
	dvtb_h264Enc1XDM1SingleBufDescDebug(&veo->videncOutArgs.encodedBuf);

	//IVIDEO1_BufDesc reconBufs;
	SYS_DEBUG("reconBufs          :\n");
	dvtb_h264Enc1IVIDEO1_BufDescDebug(&veo->videncOutArgs.reconBufs);

	SYS_DEBUG("\n<======== Video Encoder OutArgs Debug End ============>\n");
}

void
dvtb_h264Enc1ControlDebug(IH264VENC_Status *ves)
{
	int i = 0;

	SYS_DEBUG("\n<======== Video Encoder Status Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ves->videncStatus.extendedError);

	//XDM1_SingleBufDesc data;
	SYS_DEBUG("data            :\n");
	dvtb_h264Enc1XDM1SingleBufDescDebug(&ves->videncStatus.data);

	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ves->videncStatus.bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ves->videncStatus.bufInfo.minNumOutBufs);

	for (i = 0; i < ves->videncStatus.bufInfo.minNumInBufs; i++)
		SYS_DEBUG("BUF-Min In Size  [%d]  : %d\n", i, (int) ves->videncStatus.bufInfo.minInBufSize[i]);

	for (i = 0; i < ves->videncStatus.bufInfo.minNumOutBufs; i++)
		SYS_DEBUG("BUF-Min Out Size  [%d] : %d\n", i, (int) ves->videncStatus.bufInfo.minOutBufSize[i]);

	SYS_DEBUG("\n<======== Video Encoder Status Debug End ============>\n");
}

void
dvtb_h264Enc1Cleanup(DvevmStH264Enc1Info *ve)
{
	if (NULL != ve->venc1Hdl)
	{
		VIDENC1_delete((VIDENC1_Handle) ve->venc1Hdl);
		ve->venc1Hdl = NULL;
	}
}

DvevmStRetCode
dvtb_h264Enc1Init(DvevmStH264Enc1Info *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);
	ASSERT(ve->h264enc1Name[0] != 0);
	ve->venc1DynParams.VUI_Buffer = &VUIPARAMSBUFFER;
        ve->venc1DynParams.CustomScaleMatrix_Buffer = &CUSTOMSEQSCALEMATRICES;

	dvtb_h264Enc1InitDebug(&ve->venc1Params);

	if (NULL == (ve->venc1Hdl = (IH264VENC_Handle) VIDENC1_create(ve->ceHdl, ve->h264enc1Name, (VIDENC1_Params*) &ve->venc1Params)))
	{
		dvtb_h264Enc1InitDebug(&ve->venc1Params);
		SYS_ERROR("Unable to initialize Video Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Video Encode Instance created.\n");

		ve->venc1Cmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_h264Enc1Control(ve))
		{
			SYS_ERROR("Unable to set encoder dynamic parameters\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			ve->venc1Cmd = XDM_GETBUFINFO;

			if (DVEVM_ST_FAIL == dvtb_h264Enc1Control(ve))
			{
				SYS_ERROR("Unable to get buffer information.\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_DEBUG("Video Encoder <%s> initialized\n", ve->h264enc1Name);
				dvtb_h264Enc1InitDebug(&ve->venc1Params);
			}
		}
	}
	if (DVEVM_ST_FAIL == retCode)
		dvtb_h264Enc1Cleanup(ve);

	return retCode;
}

DvevmStRetCode
dvtb_h264Enc1Encode(DvevmStH264Enc1Info *ve, int* encDuration)
{
	XDAS_Int32 status = -1;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);
	ASSERT(ve->venc1Hdl != NULL);
	ASSERT(ve->inBufDesc.numBufs > 0);
	ASSERT(ve->outBufDesc.numBufs > 0);

	ve->venc1InArgs.videncInArgs.inputID = 1;

	ve->venc1OutArgs.numPackets = 0;

	timeStmpBfrEnc = dvtb_getTime();

	status = VIDENC1_process((VIDENC1_Handle) ve->venc1Hdl, &ve->inBufDesc, &ve->outBufDesc, (VIDENC1_InArgs*) &ve->venc1InArgs, (VIDENC1_OutArgs *) &ve->venc1OutArgs);

	timeStmpAftrEnc = dvtb_getTime();

	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != VIDENC1_EOK)
	{
		SYS_ERROR("Video Encode Process failed (%d), Codec Error : %d\n", (int) status, (int) ve->venc1OutArgs.videncOutArgs.extendedError);
		retCode = DVEVM_ST_FAIL;
	}

	if (DVEVM_ST_FAIL != retCode)
		dvtb_h264Enc1ProcessDebug(&ve->venc1OutArgs);

	return retCode;
}

DvevmStRetCode
dvtb_h264Enc1Control(DvevmStH264Enc1Info *ve)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);

	status = VIDENC1_control((VIDENC1_Handle) ve->venc1Hdl, ve->venc1Cmd, (VIDENC1_DynamicParams*) &ve->venc1DynParams, (VIDENC1_Status*) &ve->venc1Status);
	if (VIDENC1_EOK != status)
	{
		SYS_ERROR("Error (%d), Codec Error (%d) in Video Encoder Control\n", status, (int) ve->venc1Status.videncStatus.extendedError);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Video Encode Control => Command : %d\n", ve->venc1Cmd);
		SYS_DEBUG("Input Height     : %d\n", (int) ve->venc1DynParams.videncDynamicParams.inputHeight);
		SYS_DEBUG("Input Width      : %d\n", (int) ve->venc1DynParams.videncDynamicParams.inputWidth);
		SYS_DEBUG("Ref Frame Rate   : %d\n", (int) ve->venc1DynParams.videncDynamicParams.refFrameRate);
		SYS_DEBUG("Tgt Frame Rate   : %d\n", (int) ve->venc1DynParams.videncDynamicParams.targetFrameRate);
		SYS_DEBUG("Target Bit Rate  : %d\n", (int) ve->venc1DynParams.videncDynamicParams.targetBitRate);

		dvtb_h264Enc1ControlDebug(&ve->venc1Status);

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

	return retCode;
}

DvevmStRetCode
dvtb_h264Enc1Close(DvevmStH264Enc1Info *ve)
{
	if (ve->inBuf.bufs[0] != NULL)
	{
		dvtb_freeCmemSingleChunk(&ve->inBuf);
	}

	if (ve->outBuf.bufs[0] != NULL)
	{
		dvtb_freeCmemSingleChunk(&ve->outBuf);
	}

	dvtb_h264Enc1Cleanup(ve);

	return DVEVM_ST_SUCCESS;
}

