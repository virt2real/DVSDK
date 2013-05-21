/*
 * dvtbImgEnc.c
 *
 * XDM0.9 Image Encode Interface implementation
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

#include "dvtbImgEnc.h"
#include "dvtbMemory.h"

void
dvtb_imgEncInitDebug(IMGENC_Params *iep)
{
	SYS_DEBUG("\n<======== Image Encoder Initialize Debug Start ==========>\n");
	SYS_DEBUG("Max Height         : %d\n", (int) iep->maxHeight);
	SYS_DEBUG("Max Width          : %d\n", (int) iep->maxWidth);
	SYS_DEBUG("Max Scans          : %d\n", (int) iep->maxScans);
	SYS_DEBUG("Data Endianness    : %d\n", (int) iep->dataEndianness);
	SYS_DEBUG("Force Chroma Format: %d\n", (int) iep->forceChromaFormat);
	SYS_DEBUG("\n<======== Image Encoder Initialize Debug End ============>\n\n");
}

void
dvtb_imgEncProcessDebug(IMGENC_OutArgs *ieo)
{
	SYS_DEBUG("\n<======== Image Encoder Process Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ieo->extendedError);
	SYS_DEBUG("Bytes Generated    : %d\n", (int) ieo->bytesGenerated);
	SYS_DEBUG("Current AU         : %d\n", (int) ieo->currentAU);
	SYS_DEBUG("\n<======== Image Encoder Process Debug End ============>\n\n");
}

void
dvtb_imgEncControlDebug(IMGENC_Status *ies)
{
	int i = 0;

	SYS_DEBUG("\n<======== Image Encoder Control Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ies->extendedError);
	SYS_DEBUG("Total AU           : %d\n", (int) ies->totalAU);
	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ies->bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ies->bufInfo.minNumOutBufs);

	for (i = 0; i < ies->bufInfo.minNumInBufs; i++)
		SYS_DEBUG("BUF-Min In Size  [%d]  : %d\n", i, (int) ies->bufInfo.minInBufSize[i]);

	for (i = 0; i < ies->bufInfo.minNumOutBufs; i++)
		SYS_DEBUG("BUF-Min Out Size  [%d] : %d\n", i, (int) ies->bufInfo.minOutBufSize[i]);

	SYS_DEBUG("\n<======== Image Encoder Control Debug End ============>\n");
}

void
dvtb_imgEncCleanup(DvevmStImgEncInfo *ienc)
{
	if (NULL != ienc->iencHdl)
	{
		IMGENC_delete(ienc->iencHdl);
		ienc->iencHdl = NULL;
	}

	if(0 != ienc->inBuf.numBufs)
		dvtb_freeCmem(&ienc->inBuf);

	if(0 != ienc->outBuf.numBufs)
		dvtb_freeCmem(&ienc->outBuf);
}

DvevmStRetCode
dvtb_imgEncInit(DvevmStImgEncInfo *ienc)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ienc != NULL);
	ASSERT(ienc->ceHdl != NULL);
	ASSERT(ienc->iencName[0] != 0);

	dvtb_imgEncInitDebug(&ienc->iencParams);
	if (NULL == (ienc->iencHdl = IMGENC_create(ienc->ceHdl, ienc->iencName, &ienc->iencParams)))
	{
		SYS_ERROR("Unable to initialize Image Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		ienc->iencCmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_imgEncControl(ienc))
		{

			SYS_ERROR("Unable to set encoder dynamic parameters\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			ienc->iencCmd = XDM_GETBUFINFO;
			if (DVEVM_ST_FAIL == dvtb_imgEncControl(ienc))
			{

				SYS_ERROR("Unable to get buffer info\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (DVEVM_ST_FAIL == dvtb_allocCmem(&ienc->inBuf))
			{
				SYS_ERROR("Unable to allocate memory for input buffer\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (DVEVM_ST_FAIL == dvtb_allocCmem(&ienc->outBuf))
			{
				SYS_ERROR("Unable to allocate memory for output buffer\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_DEBUG("Image Encoder <%s> initialized\n", ienc->iencName);
				dvtb_imgEncInitDebug(&ienc->iencParams);
			}
		}
	}

	if(DVEVM_ST_FAIL == retCode)
		dvtb_imgEncCleanup(ienc);

	return retCode;
}

DvevmStRetCode
dvtb_imgEncEncode(DvevmStImgEncInfo *ienc, int *encDuration)
{
	XDM_BufDesc inBufDesc, outBufDesc;
	XDAS_Int32 status = -1;

	IMGENC_InArgs encInArgs;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ienc != NULL);
	ASSERT(ienc->ceHdl != NULL);
	ASSERT(ienc->iencHdl != NULL);
	ASSERT(ienc->inBuf.numBufs > 0);
	ASSERT(ienc->outBuf.numBufs > 0);

	inBufDesc.numBufs = ienc->inBuf.numBufs;
	inBufDesc.bufSizes = (XDAS_Int32 *) ienc->inBuf.bufSizes;
	inBufDesc.bufs = (XDAS_Int8 **) ienc->inBuf.bufs;

	outBufDesc.numBufs = ienc->outBuf.numBufs;
	outBufDesc.bufSizes = (XDAS_Int32 *) ienc->outBuf.bufSizes;
	outBufDesc.bufs = (XDAS_Int8 **) ienc->outBuf.bufs;

	encInArgs.size = sizeof(encInArgs);
	ienc->iencOutArgs.size = sizeof(ienc->iencOutArgs);

	timeStmpBfrEnc = dvtb_getTime( );
	status = IMGENC_process(ienc->iencHdl, &inBufDesc, &outBufDesc, &encInArgs, &ienc->iencOutArgs);
	timeStmpAftrEnc = dvtb_getTime( );

	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != IMGENC_EOK)
	{
		SYS_ERROR("Image Encode Process failed (%d), Codec Error : %d\n", (int) status, (int) ienc->iencOutArgs.extendedError);
		retCode = DVEVM_ST_FAIL;
	}

	dvtb_imgEncProcessDebug(&ienc->iencOutArgs);

	return retCode;
}

DvevmStRetCode
dvtb_imgEncControl(DvevmStImgEncInfo *ienc)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ienc != NULL);
	ASSERT(ienc->ceHdl != NULL);
	ASSERT(ienc->iencHdl != NULL);
	status = IMGENC_control(ienc->iencHdl, ienc->iencCmd, &ienc->iencDynParams, &ienc->iencStatus);
	if (IMGENC_EOK != status)
	{
		SYS_ERROR("Error (%d), Codec Error (%d) in image Encoder Control\n", status, (int) ienc->iencStatus.extendedError);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Image Encode Control => Command : %d\n", ienc->iencCmd);
		SYS_DEBUG("Num AU               : %d\n", (int) ienc->iencDynParams.numAU);
		SYS_DEBUG("Input Chroma Format  : %d\n", (int) ienc->iencDynParams.inputChromaFormat);
		SYS_DEBUG("Input Height         : %d\n", (int) ienc->iencDynParams.inputHeight);
		SYS_DEBUG("Input Width          : %d\n", (int) ienc->iencDynParams.inputWidth);
		SYS_DEBUG("Capture Width        : %d\n", (int) ienc->iencDynParams.captureWidth);
		SYS_DEBUG("Generate Header      : %d\n", (int) ienc->iencDynParams.generateHeader);
		SYS_DEBUG("Q Value              : %d\n", (int) ienc->iencDynParams.qValue);

		if (XDM_GETBUFINFO == ienc->iencCmd)
		{
			ienc->inBuf.numBufs = ienc->iencStatus.bufInfo.minNumInBufs;
			ienc->outBuf.numBufs = ienc->iencStatus.bufInfo.minNumOutBufs;

			for (i = 0; i < ienc->inBuf.numBufs; i++)
				ienc->inBuf.bufSizes[i] = ienc->iencStatus.bufInfo.minInBufSize[i];

			for (i = 0; i < ienc->outBuf.numBufs; i++)
				ienc->outBuf.bufSizes[i] = ienc->iencStatus.bufInfo.minOutBufSize[i];
		}
		dvtb_imgEncControlDebug(&ienc->iencStatus);
	}

	return retCode;
}

DvevmStRetCode
dvtb_imgEncClose(DvevmStImgEncInfo *ienc)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	dvtb_imgEncCleanup(ienc);
	return retCode;
}
