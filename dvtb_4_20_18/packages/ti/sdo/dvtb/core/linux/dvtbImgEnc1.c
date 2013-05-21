/*
 * dvtbImgEnc1.c
 *
 * XDM1.0 Image Encoder implementation
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

#include "dvtbImgEnc1.h"
#include "dvtbMemory.h"

void
dvtb_imgEnc1InitDebug(IMGENC1_Params *iep)
{
	SYS_DEBUG("\n<======== Image Encoder Params Debug Start ==========>\n");
	SYS_DEBUG("Max Height         : %d\n", (int) iep->maxHeight);
	SYS_DEBUG("Max Width          : %d\n", (int) iep->maxWidth);
	SYS_DEBUG("Max Scans          : %d\n", (int) iep->maxScans);
	SYS_DEBUG("Data Endianness    : %d\n", (int) iep->dataEndianness);
	SYS_DEBUG("Force Chroma Format: %d\n", (int) iep->forceChromaFormat);
	SYS_DEBUG("\n<======== Image Encoder Params Debug End ============>\n\n");
}

void
dvtb_imgEnc1ProcessDebug(IMGENC1_OutArgs *ieo)
{
	SYS_DEBUG("\n<======== Image Encoder OutArgs Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ieo->extendedError);
	SYS_DEBUG("Bytes Generated    : %d\n", (int) ieo->bytesGenerated);
	SYS_DEBUG("Current AU         : %d\n", (int) ieo->currentAU);
	SYS_DEBUG("\n<======== Image Encoder OutArgs Debug End ============>\n\n");
}

void
dvtb_imgEnc1ControlDebug(IMGENC1_Status *ies)
{
	int i = 0;

	SYS_DEBUG("\n<======== Image Encoder Status Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ies->extendedError);
	SYS_DEBUG("Total AU           : %d\n", (int) ies->totalAU);
	SYS_DEBUG("Data.buf           : %u\n", (int) ies->data.buf);
	SYS_DEBUG("Data.bufSize       : %d\n", (int) ies->data.bufSize);
	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ies->bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ies->bufInfo.minNumOutBufs);

	for (i = 0; i < ies->bufInfo.minNumInBufs; i++)
		SYS_DEBUG("BUF-Min In Size  [%d]  : %d\n", i, (int) ies->bufInfo.minInBufSize[i]);

	for (i = 0; i < ies->bufInfo.minNumOutBufs; i++)
		SYS_DEBUG("BUF-Min Out Size  [%d] : %d\n", i, (int) ies->bufInfo.minOutBufSize[i]);

	SYS_DEBUG("\n<======== Image Encoder Status Debug End ============>\n");
}

void
dvtb_imgEnc1Cleanup(DvevmStImgEnc1Info *ienc1)
{
	if (NULL != ienc1->ienc1Hdl)
	{
		IMGENC1_delete(ienc1->ienc1Hdl);
		ienc1->ienc1Hdl = NULL;
	}

}

DvevmStRetCode
dvtb_imgEnc1Init(DvevmStImgEnc1Info *ienc1)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ienc1 != NULL);
	ASSERT(ienc1->ceHdl != NULL);
	ASSERT(ienc1->ienc1Name[0] != 0);

	dvtb_imgEnc1InitDebug(&ienc1->ienc1Params);
	if (NULL == (ienc1->ienc1Hdl = IMGENC1_create(ienc1->ceHdl, ienc1->ienc1Name, &ienc1->ienc1Params)))
	{
		SYS_ERROR("Unable to initialize Image Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		ienc1->ienc1Cmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_imgEnc1Control(ienc1))
		{
			SYS_ERROR("Unable to set encoder dynamic parameters\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			ienc1->ienc1Cmd = XDM_GETBUFINFO;
			if (DVEVM_ST_FAIL == dvtb_imgEnc1Control(ienc1))
			{
				SYS_ERROR("Unable to get buffer info\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (DVEVM_ST_FAIL == dvtb_allocCmem(&ienc1->inBuf))
			{
				SYS_ERROR("Unable to allocate memory for input buffer\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (DVEVM_ST_FAIL == dvtb_allocCmem(&ienc1->outBuf))
			{
				SYS_ERROR("Unable to allocate memory for output buffer\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_DEBUG("Image Encoder <%s> initialized\n", ienc1->ienc1Name);
				dvtb_imgEnc1InitDebug(&ienc1->ienc1Params);
			}
		}
	}

	if(DVEVM_ST_FAIL == retCode)
		dvtb_imgEnc1Cleanup(ienc1);

	return retCode;
}

DvevmStRetCode
dvtb_imgEnc1Encode(DvevmStImgEnc1Info *ienc1, int *encDuration)
{
	int status = -1, i = 0;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ienc1 != NULL);
	ASSERT(ienc1->ceHdl != NULL);
	ASSERT(ienc1->ienc1Hdl != NULL);
	ASSERT(ienc1->inBuf.numBufs > 0);
	ASSERT(ienc1->outBuf.numBufs > 0);

	ienc1->inBufDesc.numBufs = ienc1->inBuf.numBufs;
	for (i = 0; i < ienc1->inBufDesc.numBufs; i++)
	{
		ienc1->inBufDesc.descs[i].bufSize = ienc1->inBuf.bufSizes[i];
		ienc1->inBufDesc.descs[i].buf = (XDAS_Int8 *) ienc1->inBuf.bufs[i];
	}

	ienc1->outBufDesc.numBufs = ienc1->outBuf.numBufs;
	for (i = 0; i < ienc1->outBufDesc.numBufs; i++)
	{
		ienc1->outBufDesc.descs[i].bufSize = ienc1->outBuf.bufSizes[i];
		ienc1->outBufDesc.descs[i].buf = (XDAS_Int8*) ienc1->outBuf.bufs[i];
	}

	timeStmpBfrEnc = dvtb_getTime( );
	status = IMGENC1_process(ienc1->ienc1Hdl, &ienc1->inBufDesc, &ienc1->outBufDesc, &ienc1->ienc1InArgs, &ienc1->ienc1OutArgs);
	timeStmpAftrEnc = dvtb_getTime( );
	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != IMGENC1_EOK)
	{
		SYS_ERROR("Image Encode Process failed (%d), OutArgs-Codec Error : %d\n", (int) status, (int) ienc1->ienc1OutArgs.extendedError);

		ienc1->ienc1Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_imgEnc1Control(ienc1))
			SYS_ERROR("Unable to get the status.\n");
		else
			SYS_ERROR("Codec Error from Status = %d\n", (int) ienc1->ienc1Status.extendedError);

		retCode = DVEVM_ST_FAIL;
	}

	if(DVEVM_ST_FAIL != retCode)
		dvtb_imgEnc1ProcessDebug(&ienc1->ienc1OutArgs);

	return retCode;
}

DvevmStRetCode 
dvtb_imgEnc1Control(DvevmStImgEnc1Info *ienc1)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ienc1 != NULL);
	ASSERT(ienc1->ceHdl != NULL);
	ASSERT(ienc1->ienc1Hdl != NULL);

	status = IMGENC1_control(ienc1->ienc1Hdl, ienc1->ienc1Cmd, &ienc1->ienc1DynParams, &ienc1->ienc1Status);
	if (IMGENC1_EOK != status)
	{
		SYS_ERROR("Error (%d), Codec Error (%d) in image Encoder Control\n", status, (int) ienc1->ienc1Status.extendedError);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Image Encode Control => Command : %d\n", ienc1->ienc1Cmd);
		SYS_DEBUG("Num AU               : %d\n", (int) ienc1->ienc1DynParams.numAU);
		SYS_DEBUG("Input Chroma Format  : %d\n", (int) ienc1->ienc1DynParams.inputChromaFormat);
		SYS_DEBUG("Input Height         : %d\n", (int) ienc1->ienc1DynParams.inputHeight);
		SYS_DEBUG("Input Width          : %d\n", (int) ienc1->ienc1DynParams.inputWidth);
		SYS_DEBUG("Capture Width        : %d\n", (int) ienc1->ienc1DynParams.captureWidth);
		SYS_DEBUG("Generate Header      : %d\n", (int) ienc1->ienc1DynParams.generateHeader);
		SYS_DEBUG("Q Value              : %d\n", (int) ienc1->ienc1DynParams.qValue);

		if (XDM_GETBUFINFO == ienc1->ienc1Cmd)
		{
			ienc1->inBuf.numBufs = ienc1->ienc1Status.bufInfo.minNumInBufs;
			ienc1->outBuf.numBufs = ienc1->ienc1Status.bufInfo.minNumOutBufs;

			for (i = 0; i < ienc1->inBuf.numBufs; i++)
				ienc1->inBuf.bufSizes[i] = ienc1->ienc1Status.bufInfo.minInBufSize[i];

			for (i = 0; i < ienc1->outBuf.numBufs; i++)
				ienc1->outBuf.bufSizes[i] = ienc1->ienc1Status.bufInfo.minOutBufSize[i];
		}

		dvtb_imgEnc1ControlDebug(&ienc1->ienc1Status);
	}

	return retCode;

}

DvevmStRetCode
dvtb_imgEnc1Close(DvevmStImgEnc1Info *ienc1)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (ienc1->inBuf.bufs[0] != NULL)
		dvtb_freeCmem(&ienc1->inBuf);

	if (ienc1->outBuf.bufs[0] != NULL)
		dvtb_freeCmem(&ienc1->outBuf);

	dvtb_imgEnc1Cleanup(ienc1);

	return retCode;
}
