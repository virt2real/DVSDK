/*
 * dvtbH264fhdEnc1.c
 *
 * XDM1.0 H264fhd Encode Interface implementation
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

#include "dvtbH264fhdEnc1.h"
#include "dvtbMemory.h"

void
dvtb_h264fhdEnc1XDM1SingleBufDescDebug(XDM1_SingleBufDesc *sbd)
{
	SYS_DEBUG("\tbuf                   : %x\n", (int) sbd->buf);
	SYS_DEBUG("\tbufSize               : %d\n", (int) sbd->bufSize);
	SYS_DEBUG("\taccessMask            : %d\n", (int) sbd->accessMask);
}

void
dvtb_h264fhdEnc1IVIDEO1_BufDescDebug(IVIDEO1_BufDesc *bd)
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
		dvtb_h264fhdEnc1XDM1SingleBufDescDebug(&bd->bufDesc[i]);
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
dvtb_h264fhdEnc1InitDebug(IH264FHDVENC_Params *vep)
{
	SYS_DEBUG("\n<======== H264FHD Encoder Params Debug Start ==========>\n");
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
	SYS_DEBUG("profileIdc      	: %d\n", (int) vep->profileIdc);
	SYS_DEBUG("levelIdc	        : %d\n", (int) vep->levelIdc);
	SYS_DEBUG("EntropyCodingMode  : %d\n", (int) vep->EntropyCodingMode);
	SYS_DEBUG("\n<======== H264FHD Encoder Params Debug End ============>\n\n");
}

void
dvtb_h264fhdEnc1InArgsDebug(IH264FHDVENC_InArgs *vei)
{
	SYS_DEBUG("\n<======== Video Encoder InArgs Debug Start ==========>\n");
	SYS_DEBUG("Size                 : %d\n", (int) vei->videncInArgs.size);
	SYS_DEBUG("inputID              : %d\n", (int) vei->videncInArgs.inputID);
	SYS_DEBUG("topFieldFirstFlag    : %d\n", (int) vei->videncInArgs.topFieldFirstFlag);
	SYS_DEBUG("\n<======== Video Encoder InArgs Debug End ============>\n");
}

void
dvtb_h264fhdEnc1ProcessDebug(IH264FHDVENC_OutArgs *veo)
{
	SYS_DEBUG("\n<======== Video Encoder OutArgs Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) veo->videncOutArgs.extendedError);
	SYS_DEBUG("Bytes Generated    : %d\n", (int) veo->videncOutArgs.bytesGenerated);
	SYS_DEBUG("Encoded Frame Type : %d\n", (int) veo->videncOutArgs.encodedFrameType);
	SYS_DEBUG("Input Frame Skip   : %d\n", (int) veo->videncOutArgs.inputFrameSkip);
	SYS_DEBUG("Output ID 		: %d\n", (int) veo->videncOutArgs.outputID);

	//XDM1_SingleBufDesc encodedBuf;
	SYS_DEBUG("encodedBuf            :\n");
	dvtb_h264fhdEnc1XDM1SingleBufDescDebug(&veo->videncOutArgs.encodedBuf);

	//IVIDEO1_BufDesc reconBufs;
	SYS_DEBUG("reconBufs          :\n");
	dvtb_h264fhdEnc1IVIDEO1_BufDescDebug(&veo->videncOutArgs.reconBufs);

	SYS_DEBUG("\n<======== Video Encoder OutArgs Debug End ============>\n");
}

void
dvtb_h264fhdEnc1Cleanup(DvevmStH264fhdEnc1Info *ve)
{
	if (NULL != ve->venc1Hdl)
	{
		VIDENC1_delete(ve->venc1Hdl);
		ve->venc1Hdl = NULL;
	}
}

DvevmStRetCode
dvtb_h264fhdEnc1Init(DvevmStH264fhdEnc1Info *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);
	ASSERT(ve->venc1Name[0] != 0);

	dvtb_h264fhdEnc1InitDebug(&ve->venc1Params);
	if (NULL == (ve->venc1Hdl = VIDENC1_create(ve->ceHdl, ve->venc1Name, (IVIDENC1_Params *) (&ve->venc1Params))))
	{
		dvtb_h264fhdEnc1InitDebug(&ve->venc1Params);
		SYS_ERROR("Unable to initialize Video Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		ve->venc1Cmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_h264fhdEnc1Control(ve))
		{
			SYS_ERROR("Unable to set encoder dynamic parameters\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			ve->venc1Cmd = XDM_GETBUFINFO;
			if (DVEVM_ST_FAIL == dvtb_h264fhdEnc1Control(ve))
			{
				SYS_ERROR("Unable to get encoder buffer requirements\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_DEBUG("Video Encoder <%s> initialized\n", ve->venc1Name);
				dvtb_h264fhdEnc1InitDebug(&ve->venc1Params);
			}
		}
	}
	if(DVEVM_ST_FAIL == retCode)
		dvtb_h264fhdEnc1Cleanup(ve);

	return retCode;
}

DvevmStRetCode
dvtb_h264fhdEnc1Encode(DvevmStH264fhdEnc1Info *ve, int* encDuration)
{
	XDAS_Int32 status = -1;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);
	ASSERT(ve->venc1Hdl != NULL);

	timeStmpBfrEnc = dvtb_getTime( );
	status = VIDENC1_process(ve->venc1Hdl, &ve->inBufDesc, &ve->outBufDesc, (IVIDENC1_InArgs *) (&ve->venc1InArgs), (IVIDENC1_OutArgs *) (&ve->venc1OutArgs));
	timeStmpAftrEnc = dvtb_getTime( );
	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != VIDENC1_EOK)
	{
		SYS_ERROR("Video Encode Process failed (%d), Codec Error : %d\n", (int) status, (int) ve->venc1OutArgs.videncOutArgs.extendedError);
		retCode = DVEVM_ST_FAIL;
	}

	if (DVEVM_ST_FAIL != retCode)
		dvtb_h264fhdEnc1ProcessDebug(&ve->venc1OutArgs);

	return retCode;
}

DvevmStRetCode
dvtb_h264fhdEnc1Control(DvevmStH264fhdEnc1Info *ve)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);

	status = VIDENC1_control(ve->venc1Hdl, ve->venc1Cmd, (IVIDENC1_DynamicParams *) (&ve->venc1DynParams), (IVIDENC1_Status *) (&ve->venc1Status));
	if (VIDENC1_EOK != status)
	{
		SYS_ERROR("Error (%d), Codec Error (%d) in Video Encoder Control\n", status, (int) ve->venc1Status.videncStatus.extendedError);
		retCode = DVEVM_ST_FAIL;
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
		else if(XDM_GETSTATUS == ve->venc1Cmd)
		{
			if(ve->venc1Status.videncStatus.extendedError)
			{
				if(XDM_ISFATALERROR(ve->venc1Status.videncStatus.extendedError))
				{
					SYS_ERROR("Exiting: Encode Failed with a Codec fatal error %x.\n", (int) ve->venc1Status.videncStatus.extendedError);
					retCode = DVEVM_ST_FAIL;
				}
				else
					SYS_ERROR("Continue: Codec generated an non fatal error %x.\n", (int) ve->venc1Status.videncStatus.extendedError);
			}
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_h264fhdEnc1Close(DvevmStH264fhdEnc1Info *ve)
{
	if (ve->inBuf.numBufs > 0)
	{
		dvtb_freeCmem(&ve->inBuf);
	}

	if (ve->outBuf.numBufs > 0)
	{
		dvtb_freeCmem(&ve->outBuf);
	}

	dvtb_h264fhdEnc1Cleanup(ve);

	return DVEVM_ST_SUCCESS;
}

