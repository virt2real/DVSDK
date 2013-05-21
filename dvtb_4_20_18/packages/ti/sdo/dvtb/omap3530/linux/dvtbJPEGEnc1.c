/*
 * dvtbJPEGEnc1.c
 *
 * XDM1.0 JPEG Encode Interface implementation
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

#include "dvtbJPEGEnc1.h"
#include "dvtbMemory.h"

void
dvtb_jpegEnc1InitDebug(IDMJPGE_TIGEM_Params *iep)
{
	SYS_DEBUG("\n<======== JPEG Encoder Params Debug Start ==========>\n");
	SYS_DEBUG("Max Height         : %d\n", (int) iep->params.maxHeight);
	SYS_DEBUG("Max Width          : %d\n", (int) iep->params.maxWidth);
	SYS_DEBUG("Max Scans          : %d\n", (int) iep->params.maxScans);
	SYS_DEBUG("Data Endianness    : %d\n", (int) iep->params.dataEndianness);
	SYS_DEBUG("Force Chroma Format: %d\n", (int) iep->params.forceChromaFormat);
	SYS_DEBUG("\n<======== JPEG Encoder Params Debug End ============>\n\n");
}

void
dvtb_jpegEnc1ProcessDebug(IDMJPGE_TIGEM_OutArgs *ieo)
{
	SYS_DEBUG("\n<======== JPEG Encoder OutArgs Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ieo->outArgs.extendedError);
	SYS_DEBUG("Bytes Generated    : %d\n", (int) ieo->outArgs.bytesGenerated);
	SYS_DEBUG("Current AU         : %d\n", (int) ieo->outArgs.currentAU);
	SYS_DEBUG("\n<======== JPEG Encoder OutArgs Debug End ============>\n\n");
}

void
dvtb_jpegEnc1ControlDebug(IDMJPGE_TIGEM_Status *ies)
{
	int i = 0;

	SYS_DEBUG("\n<======== JPEG Encoder Status Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ies->status.extendedError);
	SYS_DEBUG("Total AU           : %d\n", (int) ies->status.totalAU);
	SYS_DEBUG("Data.buf           : %u\n", (int) ies->status.data.buf);
	SYS_DEBUG("Data.bufSize       : %d\n", (int) ies->status.data.bufSize);
	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ies->status.bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ies->status.bufInfo.minNumOutBufs);

	for (i = 0; i < ies->status.bufInfo.minNumInBufs; i++)
		SYS_DEBUG("BUF-Min In Size  [%d]  : %d\n", i, (int) ies->status.bufInfo.minInBufSize[i]);

	for (i = 0; i < ies->status.bufInfo.minNumOutBufs; i++)
		SYS_DEBUG("BUF-Min Out Size  [%d] : %d\n", i, (int) ies->status.bufInfo.minOutBufSize[i]);

	SYS_DEBUG("\n<======== JPEG Encoder Status Debug End ============>\n");
}

void
dvtb_jpegEnc1Cleanup(DvevmStJpegEnc1Info *jpeg1)
{
	if (NULL != jpeg1->ienc1Hdl)
	{
		IMGENC1_delete(jpeg1->ienc1Hdl);
		jpeg1->ienc1Hdl = NULL;
	}
}

DvevmStRetCode
dvtb_jpegEnc1Init(DvevmStJpegEnc1Info *jpeg1)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(jpeg1 != NULL);
	ASSERT(jpeg1->ceHdl != NULL);
	ASSERT(jpeg1->ienc1Name[0] != 0);

	dvtb_jpegEnc1InitDebug(&(jpeg1->ienc1Params));

	if (NULL == (jpeg1->ienc1Hdl = IMGENC1_create(jpeg1->ceHdl, jpeg1->ienc1Name, (IIMGENC1_Params *) &jpeg1->ienc1Params)))
	{
		SYS_ERROR("Unable to initialize Image Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		jpeg1->ienc1Cmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_jpegEnc1Control(jpeg1))
		{
			SYS_ERROR("Unable to set encoder dynamic parameters\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			jpeg1->ienc1Cmd = XDM_GETBUFINFO;
			if (DVEVM_ST_FAIL == dvtb_jpegEnc1Control(jpeg1))
			{
				SYS_ERROR("Unable to get buffer info\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				if (DVEVM_ST_FAIL == dvtb_allocCmemSingleChunk(&jpeg1->inBuf))
				{
					SYS_ERROR("Unable to allocate memory for input buffer\n");
					retCode = DVEVM_ST_FAIL;
				}
				else
				{
					memcpy(&jpeg1->startInBuf, &jpeg1->inBuf, sizeof(jpeg1->inBuf));

					if (DVEVM_ST_FAIL == dvtb_allocCmemSingleChunk(&jpeg1->outBuf))
					{
						SYS_ERROR("Unable to allocate memory for output buffer\n");
						retCode = DVEVM_ST_FAIL;
					}
					else
					{
						memcpy(&jpeg1->startOutBuf, &jpeg1->outBuf, sizeof(jpeg1->outBuf));

						SYS_DEBUG("Image Encoder <%s> initialized\n", jpeg1->ienc1Name);
						dvtb_jpegEnc1InitDebug(&jpeg1->ienc1Params);

					}
				}
			}
		}
	}

	if (DVEVM_ST_FAIL == retCode)
		dvtb_jpegEnc1Cleanup(jpeg1);

	return retCode;
}

DvevmStRetCode
dvtb_jpegEnc1Encode(DvevmStJpegEnc1Info *jpeg1, int *encDuration)
{
	int i = 0;
	XDAS_Int32 status = -1;

	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(jpeg1 != NULL);
	ASSERT(jpeg1->ceHdl != NULL);
	ASSERT(jpeg1->ienc1Hdl != NULL);
	ASSERT(jpeg1->inBuf.numBufs > 0);
	ASSERT(jpeg1->outBuf.numBufs > 0);

	jpeg1->inBufDesc.numBufs = jpeg1->inBuf.numBufs;
	for (i = 0; i < jpeg1->inBufDesc.numBufs; i++)
	{
		jpeg1->inBufDesc.descs[i].bufSize = jpeg1->inBuf.bufSizes[i];
		jpeg1->inBufDesc.descs[i].buf = (XDAS_Int8 *) jpeg1->inBuf.bufs[i];
	}

	jpeg1->outBufDesc.numBufs = jpeg1->outBuf.numBufs;
	for (i = 0; i < jpeg1->outBufDesc.numBufs; i++)
	{
		jpeg1->outBufDesc.descs[i].bufSize = jpeg1->outBuf.bufSizes[i];
		jpeg1->outBufDesc.descs[i].buf = (XDAS_Int8 *) jpeg1->outBuf.bufs[i];
	}

	timeStmpBfrEnc = dvtb_getTime();
	status = IMGENC1_process(jpeg1->ienc1Hdl, &jpeg1->inBufDesc, &jpeg1->outBufDesc, (IMGENC1_InArgs *) (&jpeg1->ienc1InArgs), (IMGENC1_OutArgs *) (&jpeg1->ienc1OutArgs));
	timeStmpAftrEnc = dvtb_getTime();
	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != IMGENC1_EOK)
	{
		SYS_ERROR("Image Encode Process failed (%d), Codec Error : %d\n", (int) status, (int) jpeg1->ienc1OutArgs.outArgs.extendedError);
		retCode = DVEVM_ST_FAIL;
	}

	if (DVEVM_ST_FAIL != retCode)
		dvtb_jpegEnc1ProcessDebug(&(jpeg1->ienc1OutArgs));

	return retCode;
}

DvevmStRetCode
dvtb_jpegEnc1Control(DvevmStJpegEnc1Info *jpeg1)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(jpeg1 != NULL);
	ASSERT(jpeg1->ceHdl != NULL);
	ASSERT(jpeg1->ienc1Hdl != NULL);

	status = IMGENC1_control(jpeg1->ienc1Hdl, jpeg1->ienc1Cmd, (IIMGENC1_DynamicParams *) &jpeg1->ienc1DynParams, (IIMGENC1_Status *) &jpeg1->ienc1Status);
	if (IMGENC1_EOK != status)
	{
		SYS_ERROR("Error (%d), Codec Error (%d) in image Encoder Control\n", status, (int) jpeg1->ienc1Status.status.extendedError);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Image Encode Control => Command : %d\n", jpeg1->ienc1Cmd);
		SYS_DEBUG("Num AU               : %d\n", (int) jpeg1->ienc1DynParams.params.numAU);
		SYS_DEBUG("Input Chroma Format  : %d\n", (int) jpeg1->ienc1DynParams.params.inputChromaFormat);
		SYS_DEBUG("Input Height         : %d\n", (int) jpeg1->ienc1DynParams.params.inputHeight);
		SYS_DEBUG("Input Width          : %d\n", (int) jpeg1->ienc1DynParams.params.inputWidth);
		SYS_DEBUG("Capture Width        : %d\n", (int) jpeg1->ienc1DynParams.params.captureWidth);
		SYS_DEBUG("Generate Header      : %d\n", (int) jpeg1->ienc1DynParams.params.generateHeader);
		SYS_DEBUG("Q Value              : %d\n", (int) jpeg1->ienc1DynParams.params.qValue);

		if (XDM_GETBUFINFO == jpeg1->ienc1Cmd)
		{
			jpeg1->inBuf.numBufs = jpeg1->ienc1Status.status.bufInfo.minNumInBufs;
			jpeg1->outBuf.numBufs = jpeg1->ienc1Status.status.bufInfo.minNumOutBufs;

			for (i = 0; i < jpeg1->inBuf.numBufs; i++)
			{
				jpeg1->inBuf.bufSizes[i] = jpeg1->ienc1Status.status.bufInfo.minInBufSize[i];
			}

			for (i = 0; i < jpeg1->outBuf.numBufs; i++)
			{
				jpeg1->outBuf.bufSizes[i] = jpeg1->ienc1Status.status.bufInfo.minOutBufSize[i];
			}
		}

		dvtb_jpegEnc1ControlDebug(&jpeg1->ienc1Status);
	}

	return retCode;
}

DvevmStRetCode
dvtb_jpegEnc1Close(DvevmStJpegEnc1Info *jpeg1)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (jpeg1->inBuf.bufs[0] != NULL)
	{
		dvtb_freeCmemSingleChunk(&jpeg1->startInBuf);
	}

	if (jpeg1->outBuf.bufs[0] != NULL)
	{
		dvtb_freeCmemSingleChunk(&jpeg1->startOutBuf);
	}

	dvtb_jpegEnc1Cleanup(jpeg1);

	return retCode;
}
