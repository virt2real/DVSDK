/*
 * dvtbImgDec.c
 *
 * XDM0.9 Image Decode Interface implementation
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

#include "dvtbImgDec.h"

void
dvtb_imgDecInitDebug(IMGDEC_Params *idp)
{
	SYS_DEBUG("\n<======== Image Decoder Initialize Debug Start ==========>\n");
	SYS_DEBUG("Max Height         : %d\n", (int) idp->maxHeight);
	SYS_DEBUG("Max Width          : %d\n", (int) idp->maxWidth);
	SYS_DEBUG("Max Scans          : %d\n", (int) idp->maxScans);
	SYS_DEBUG("Endianness         : %d\n", (int) idp->dataEndianness);
	SYS_DEBUG("Chroma Format      : %d\n", (int) idp->forceChromaFormat);
	SYS_DEBUG("\n<======== Image Decoder Initialize Debug End ============>\n\n");
}

void
dvtb_imgDecProcessDebug(IMGDEC_OutArgs *ido)
{
	SYS_DEBUG("\n<======== Image Decoder Process Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ido->extendedError);
	SYS_DEBUG("Bytes Consumed     : %d\n", (int) ido->bytesconsumed);
	SYS_DEBUG("Current AU         : %d\n", (int) ido->currentAU);
	SYS_DEBUG("Current Scan       : %d\n", (int) ido->currentScan);
	SYS_DEBUG("\n<======== Image Decoder Process Debug End ============>\n");
}

void
dvtb_imgDecControlDebug(IMGDEC_Status *ids)
{
	int i;
	SYS_DEBUG("\n<======== Image Decoder Control Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ids->extendedError);
	SYS_DEBUG("Output Height      : %d\n", (int) ids->outputHeight);
	SYS_DEBUG("Output Width       : %d\n", (int) ids->outputWidth);
	SYS_DEBUG("Image Width        : %d\n", (int) ids->imageWidth);
	SYS_DEBUG("Chroma Format      : %d\n", (int) ids->outChromaformat);
	SYS_DEBUG("Total AU           : %d\n", (int) ids->totalAU);
	SYS_DEBUG("Total Scan         : %d\n", (int) ids->totalScan);
	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ids->bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ids->bufInfo.minNumOutBufs);

	if (ids->bufInfo.minNumInBufs > 0 && ids->bufInfo.minNumInBufs <= 3)
	{
		for (i = 0; i < ids->bufInfo.minNumInBufs; i++)
			SYS_DEBUG("BUF-Min In Size[%d]    : %d\n", i, (int) ids->bufInfo.minInBufSize[i]);
	}

	if (ids->bufInfo.minNumOutBufs > 0 && ids->bufInfo.minNumOutBufs <= 3)
	{
		for (i = 0; i < ids->bufInfo.minNumOutBufs; i++)
			SYS_DEBUG("BUF-Min Out Size[%d]    : %d\n", i, (int) ids->bufInfo.minOutBufSize[i]);
	}

	SYS_DEBUG("\n<======== Image Decoder Control Debug End ============>\n");
}

void
dvtb_imgDecCleanup(DvevmStImgDecInfo *idec)
{
	if (NULL != idec->idecHdl)
	{
		IMGDEC_delete(idec->idecHdl);
		idec->idecHdl = NULL;
	}

	if(0 != idec->inBuf.numBufs)
		dvtb_freeCmem(&idec->inBuf);

	if(0 != idec->outBuf.numBufs)
		dvtb_freeCmem(&idec->outBuf);
}

DvevmStRetCode
dvtb_imgDecInit(DvevmStImgDecInfo *idec)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(idec != NULL);
	ASSERT(idec->ceHdl != NULL);
	ASSERT(idec->idecName[0] != 0);

	idec->inBuf.numBufs = 0;
	idec->outBuf.numBufs = 0;
	idec->idecDynParams.decodeHeader = XDM_PARSE_HEADER;
	idec->idecCmd = XDM_SETPARAMS;

	if (NULL == (idec->idecHdl = IMGDEC_create(idec->ceHdl, idec->idecName, &idec->idecParams)))
	{
		SYS_ERROR("Unable to initialize Image Decoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else if (DVEVM_ST_FAIL == dvtb_imgDecControl(idec))
	{
		SYS_ERROR("Unable to set dynamic parameters\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		idec->idecCmd = XDM_GETBUFINFO;
		if (DVEVM_ST_FAIL == dvtb_imgDecControl(idec))
		{
			SYS_ERROR("Unable to get the input/output buffer information\n");
			retCode = DVEVM_ST_FAIL;
		}
		else if (DVEVM_ST_FAIL == dvtb_allocCmem(&idec->inBuf))
		{
			SYS_ERROR("Unable to allocate memory for input buffer\n");
			retCode = DVEVM_ST_FAIL;
		}
		else if (DVEVM_ST_FAIL == dvtb_allocCmem(&idec->outBuf))
		{
			SYS_ERROR("Unable to allocate memory for output buffer\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			idec->idecCmd = XDM_SETPARAMS;
			idec->idecDynParams.decodeHeader = XDM_DECODE_AU;
			if (DVEVM_ST_FAIL == dvtb_imgDecControl(idec))
			{
				SYS_ERROR("Unable to set dynamic parameters\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_DEBUG("Image Decoder <%s> initialized\n", idec->idecName);
				dvtb_imgDecInitDebug(&idec->idecParams);

			}
		}
	}

	if(DVEVM_ST_FAIL == retCode)
		dvtb_imgDecCleanup(idec);

	return retCode;
}

DvevmStRetCode
dvtb_imgDecDecode(DvevmStImgDecInfo *idec, int *decDuration)
{
	XDAS_Int32 status = -1;
	XDM_BufDesc inBufDesc, outBufDesc;
	DvevmStTime timeStmpBfrDec, timeStmpAftrDec;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;


	ASSERT(idec != NULL);
	ASSERT(idec->idecHdl != NULL);
	ASSERT(idec->inBuf.bufs[0] != NULL);
	ASSERT(idec->outBuf.bufs[0] != NULL);

	inBufDesc.numBufs = idec->inBuf.numBufs;
	inBufDesc.bufSizes = (XDAS_Int32 *) idec->inBuf.bufSizes;
	inBufDesc.bufs = (XDAS_Int8 **) idec->inBuf.bufs;

	outBufDesc.numBufs = idec->outBuf.numBufs;
	outBufDesc.bufSizes = (XDAS_Int32 *) idec->outBuf.bufSizes;
	outBufDesc.bufs = (XDAS_Int8 **) idec->outBuf.bufs;

	idec->idecOutArgs.size = sizeof(idec->idecOutArgs);

	timeStmpBfrDec = dvtb_getTime( );
	status = IMGDEC_process(idec->idecHdl, &inBufDesc, &outBufDesc, &idec->idecInArgs, &idec->idecOutArgs);
	timeStmpAftrDec = dvtb_getTime( );
	*decDuration = ((timeStmpAftrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrDec.tv_usec) - ((timeStmpBfrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrDec.tv_usec);

	if (status != IMGDEC_EOK)
	{
		SYS_ERROR("Image Decode Process Failed (%d)\n", (int) status);
		SYS_ERROR("Codec Error : %d\n", (int) idec->idecOutArgs.extendedError);
		retCode = DVEVM_ST_FAIL;
	}

	if(DVEVM_ST_FAIL != retCode)
		dvtb_imgDecProcessDebug(&idec->idecOutArgs);

	return retCode;
}

DvevmStRetCode
dvtb_imgDecControl(DvevmStImgDecInfo *idec)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(idec != NULL);
	ASSERT(idec->idecHdl != NULL);

	idec->idecDynParams.numAU = XDM_DEFAULT;
	idec->idecDynParams.decodeHeader = XDM_DECODE_AU;
	idec->idecDynParams.displayWidth = XDM_DEFAULT;

	status = IMGDEC_control(idec->idecHdl, idec->idecCmd, &idec->idecDynParams, &idec->idecStatus);
	if (IMGDEC_EOK != status)
	{
		SYS_ERROR("Image Decode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Image Decode Control => Command : %d\n", idec->idecCmd);
		dvtb_imgDecControlDebug(&idec->idecStatus);

		if (XDM_GETBUFINFO == idec->idecCmd || XDM_GETSTATUS == idec->idecCmd)
		{
			idec->inBuf.numBufs = idec->idecStatus.bufInfo.minNumInBufs;
			idec->outBuf.numBufs = idec->idecStatus.bufInfo.minNumOutBufs;

			for (i = 0; i < idec->inBuf.numBufs; i++)
				idec->inBuf.bufSizes[i] = idec->idecInArgs.numBytes;

			for (i = 0; i < idec->outBuf.numBufs; i++)
				idec->outBuf.bufSizes[i] = idec->idecStatus.bufInfo.minOutBufSize[i];
		}
	}
	return retCode;
}

DvevmStRetCode dvtb_imgDecClose(DvevmStImgDecInfo *idec)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	dvtb_imgDecCleanup(idec);
	return retCode;
}
