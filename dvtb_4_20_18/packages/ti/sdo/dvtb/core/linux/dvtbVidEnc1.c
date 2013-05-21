/*
 * dvtbVidEnc1.c
 *
 * XDM1.0 Video Encoder implementation
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

#include "dvtbVidEnc1.h"
#include "dvtbMemory.h"

void
dvtb_vidEnc1XDM1SingleBufDescDebug(XDM1_SingleBufDesc *sbd)
{
	SYS_DEBUG("\tbuf                   : %x\n", (int) sbd->buf);
	SYS_DEBUG("\tbufSize               : %d\n", (int) sbd->bufSize);
	SYS_DEBUG("\taccessMask            : %d\n", (int) sbd->accessMask);
}

void
dvtb_vidEnc1IVIDEO1_BufDescDebug(IVIDEO1_BufDesc *bd)
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
		dvtb_vidEnc1XDM1SingleBufDescDebug(&bd->bufDesc[i]);
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
dvtb_vidEnc1InitDebug(VIDENC1_Params *vep)
{
	SYS_DEBUG("\n<======== Video Encoder Params Debug Start ==========>\n");
	SYS_DEBUG("Encoding Preset    : %d\n", (int) vep->encodingPreset);
	SYS_DEBUG("Rate Ctrl Preset   : %d\n", (int) vep->rateControlPreset);
	SYS_DEBUG("Max Height         : %d\n", (int) vep->maxHeight);
	SYS_DEBUG("Max Width          : %d\n", (int) vep->maxWidth);
	SYS_DEBUG("Max Frame Rate     : %d\n", (int) vep->maxFrameRate);
	SYS_DEBUG("Max Bit Rate       : %d\n", (int) vep->maxBitRate);
	SYS_DEBUG("Endianness         : %d\n", (int) vep->dataEndianness);
	SYS_DEBUG("Max Inter Frame    : %d\n", (int) vep->maxInterFrameInterval);
	SYS_DEBUG("Input Chroma Fmt   : %d\n", (int) vep->inputChromaFormat);
	SYS_DEBUG("Input Content      : %d\n", (int) vep->inputContentType);
	SYS_DEBUG("Recon format       : %d\n", (int) vep->reconChromaFormat);
	SYS_DEBUG("\n<======== Video Encoder Params Debug End ============>\n\n");
}

void
dvtb_vidEnc1InArgsDebug(VIDENC1_InArgs *vei)
{
	SYS_DEBUG("\n<======== Video Encoder InArgs Debug Start ==========>\n");
	SYS_DEBUG("Size                 : %d\n", (int) vei->size);
	SYS_DEBUG("inputID              : %d\n", (int) vei->inputID);
	SYS_DEBUG("topFieldFirstFlag    : %d\n", (int) vei->topFieldFirstFlag);
	SYS_DEBUG("\n<======== Video Encoder InArgs Debug End ============>\n");
}

void
dvtb_vidEnc1ProcessDebug(VIDENC1_OutArgs *veo)
{
	SYS_DEBUG("\n<======== Video Encoder OutArgs Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) veo->extendedError);
	SYS_DEBUG("Bytes Generated    : %d\n", (int) veo->bytesGenerated);
	SYS_DEBUG("Encoded Frame Type : %d\n", (int) veo->encodedFrameType);
	SYS_DEBUG("Input Frame Skip   : %d\n", (int) veo->inputFrameSkip);
	SYS_DEBUG("Output ID 		: %d\n", (int) veo->outputID);

	//XDM1_SingleBufDesc encodedBuf;
	SYS_DEBUG("encodedBuf            :\n");
	dvtb_vidEnc1XDM1SingleBufDescDebug(&veo->encodedBuf);

	//IVIDEO1_BufDesc reconBufs;
	SYS_DEBUG("reconBufs          :\n");
	dvtb_vidEnc1IVIDEO1_BufDescDebug(&veo->reconBufs);

	SYS_DEBUG("\n<======== Video Encoder OutArgs Debug End ============>\n");
}

void
dvtb_vidEnc1ControlDebug(VIDENC1_Status *ves)
{
	int i = 0;

	SYS_DEBUG("\n<======== Video Encoder Status Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ves->extendedError);

	//XDM1_SingleBufDesc data;
	SYS_DEBUG("data            :\n");
	dvtb_vidEnc1XDM1SingleBufDescDebug(&ves->data);

	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ves->bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ves->bufInfo.minNumOutBufs);

	for (i = 0; i < ves->bufInfo.minNumInBufs; i++)
		SYS_DEBUG("BUF-Min In Size  [%d]  : %d\n", i, (int) ves->bufInfo.minInBufSize[i]);

	for (i = 0; i < ves->bufInfo.minNumOutBufs; i++)
		SYS_DEBUG("BUF-Min Out Size  [%d] : %d\n", i, (int) ves->bufInfo.minOutBufSize[i]);

	SYS_DEBUG("\n<======== Video Encoder Status Debug End ============>\n");
}

void
dvtb_vidEnc1Cleanup(DvevmStVidEnc1Info *ve)
{
	if (NULL != ve->venc1Hdl)
	{
		VIDENC1_delete(ve->venc1Hdl);
		ve->venc1Hdl = NULL;
	}
}

DvevmStRetCode
dvtb_vidEnc1Init(DvevmStVidEnc1Info *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);
	ASSERT(ve->venc1Name[0] != 0);

	dvtb_vidEnc1InitDebug(&ve->venc1Params);

	if (NULL == (ve->venc1Hdl = VIDENC1_create(ve->ceHdl, ve->venc1Name, &ve->venc1Params)))
	{
		dvtb_vidEnc1InitDebug(&ve->venc1Params);
		SYS_ERROR("Unable to initialize Video Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Video Encode Instance created.\n");

		ve->venc1Cmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_vidEnc1Control(ve))
		{
			SYS_ERROR("Unable to set encoder dynamic parameters\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			ve->venc1Cmd = XDM_GETBUFINFO;

			if (DVEVM_ST_FAIL == dvtb_vidEnc1Control(ve))
			{
				SYS_ERROR("Unable to get buffer information.\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_DEBUG("Video Encoder <%s> initialized\n", ve->venc1Name);
				dvtb_vidEnc1InitDebug(&ve->venc1Params);
			}
		}
	}
	if (DVEVM_ST_FAIL == retCode)
		dvtb_vidEnc1Cleanup(ve);

	return retCode;
}

DvevmStRetCode
dvtb_vidEnc1Encode(DvevmStVidEnc1Info *ve, int* encDuration)
{
	XDAS_Int32 status = -1;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);
	ASSERT(ve->venc1Hdl != NULL);
	ASSERT(ve->inBufDesc.numBufs > 0);
	ASSERT(ve->outBufDesc.numBufs > 0);

	ve->venc1InArgs.inputID = 1;

	timeStmpBfrEnc = dvtb_getTime();
	
	status = VIDENC1_process(ve->venc1Hdl, &ve->inBufDesc, &ve->outBufDesc, &ve->venc1InArgs, &ve->venc1OutArgs);

	timeStmpAftrEnc = dvtb_getTime();

	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != VIDENC1_EOK)
	{
		SYS_ERROR("Video Encode Process failed (%d), Codec Error : %d\n", (int) status, (int) ve->venc1OutArgs.extendedError);
		retCode = DVEVM_ST_FAIL;
	}

	if (DVEVM_ST_FAIL != retCode)
		dvtb_vidEnc1ProcessDebug(&ve->venc1OutArgs);

	return retCode;
}

DvevmStRetCode
dvtb_vidEnc1Control(DvevmStVidEnc1Info *ve)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);

	status = VIDENC1_control(ve->venc1Hdl, ve->venc1Cmd, &ve->venc1DynParams, &ve->venc1Status);
	if (VIDENC1_EOK != status)
	{
		SYS_ERROR("Error (%d), Codec Error (%d) in Video Encoder Control\n", status, (int) ve->venc1Status.extendedError);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Video Encode Control => Command : %d\n", ve->venc1Cmd);
		SYS_DEBUG("Input Height     : %d\n", (int) ve->venc1DynParams.inputHeight);
		SYS_DEBUG("Input Width      : %d\n", (int) ve->venc1DynParams.inputWidth);
		SYS_DEBUG("Ref Frame Rate   : %d\n", (int) ve->venc1DynParams.refFrameRate);
		SYS_DEBUG("Tgt Frame Rate   : %d\n", (int) ve->venc1DynParams.targetFrameRate);
		SYS_DEBUG("Target Bit Rate  : %d\n", (int) ve->venc1DynParams.targetBitRate);

		dvtb_vidEnc1ControlDebug(&ve->venc1Status);

		if (XDM_GETBUFINFO == ve->venc1Cmd)
		{
			ve->inBuf.numBufs = ve->venc1Status.bufInfo.minNumInBufs;
			for (i = 0; i < ve->inBuf.numBufs; i++)
				ve->inBuf.bufSizes[i] = ve->venc1Status.bufInfo.minInBufSize[i];

			ve->outBuf.numBufs = ve->venc1Status.bufInfo.minNumOutBufs;
			for (i = 0; i < ve->outBuf.numBufs; i++)
				ve->outBuf.bufSizes[i] = ve->venc1Status.bufInfo.minOutBufSize[i];

		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_vidEnc1Close(DvevmStVidEnc1Info *ve)
{
	if (ve->inBuf.numBufs > 0)
	{
		dvtb_freeCmem(&ve->inBuf);
	}

	if (ve->outBuf.numBufs > 0)
	{
		dvtb_freeCmem(&ve->outBuf);
	}

	dvtb_vidEnc1Cleanup(ve);

	return DVEVM_ST_SUCCESS;
}

