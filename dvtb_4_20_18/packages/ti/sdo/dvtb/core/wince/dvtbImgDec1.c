/*
 * dvtbImgDec1.c
 *
 * DVTB(wince) XDM1.0 Image Decoder implementation
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

#include "dvtbImgDec1.h"
#include "dvtbMemory.h"

void
dvtb_imgDec1InitDebug(IMGDEC1_Params *idp)
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
dvtb_imgDec1ProcessDebug(IMGDEC1_OutArgs *ido)
{
	SYS_DEBUG("\n<======== Image Decoder Process Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ido->extendedError);
	SYS_DEBUG("Bytes Consumed     : %d\n", (int) ido->bytesConsumed);
	SYS_DEBUG("Current AU         : %d\n", (int) ido->currentAU);
	SYS_DEBUG("Current Scan       : %d\n", (int) ido->currentScan);
	SYS_DEBUG("\n<======== Image Decoder Process Debug End ============>\n");
}

void
dvtb_imgDec1ControlDebug(IMGDEC1_Status *ids)
{
	int i;
	SYS_DEBUG("\n<======== Image Decoder Control Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ids->extendedError);
	SYS_DEBUG("Output Height      : %d\n", (int) ids->outputHeight);
	SYS_DEBUG("Output Width       : %d\n", (int) ids->outputWidth);
	SYS_DEBUG("Image Width        : %d\n", (int) ids->imageWidth);
	SYS_DEBUG("Chroma Format      : %d\n", (int) ids->outputChromaFormat);
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
dvtb_imgDec1Cleanup(DvevmStImgDec1Info *idec)
{
	if (NULL != idec->idec1Hdl)
	{
		IMGDEC1_delete(idec->idec1Hdl);
		idec->idec1Hdl = NULL;
	}

}

DvevmStRetCode
dvtb_imgDec1Init(DvevmStImgDec1Info *idec)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(idec != NULL);
	ASSERT(idec->ceHdl != NULL);
	ASSERT(idec->idec1Name[0] != 0);

	idec->idec1Cmd = XDM_SETPARAMS;

	dvtb_imgDec1InitDebug(&idec->idec1Params);
	if (NULL == (idec->idec1Hdl = IMGDEC1_create(idec->ceHdl, idec->idec1Name, &idec->idec1Params)))
	{
		SYS_ERROR("Unable to initialize Image Decoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		if (DVEVM_ST_FAIL == dvtb_imgDec1Control(idec))
		{
			SYS_ERROR("Unable to set dynamic parameters\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			idec->idec1Cmd = XDM_GETBUFINFO;
			if (DVEVM_ST_FAIL == dvtb_imgDec1Control(idec))
			{
				SYS_ERROR("Unable to get the input/output buffer information\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (DVEVM_ST_FAIL == idec->dvtb_ptrAllocCmem(&idec->inBuf))
			{
				SYS_ERROR("Unable to allocate memory for input buffer\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (DVEVM_ST_FAIL == idec->dvtb_ptrAllocCmem(&idec->outBuf))
			{
				SYS_ERROR("Unable to allocate memory for output buffer\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_DEBUG("Image Decoder <%s> initialized\n", idec->idec1Name);
				dvtb_imgDec1InitDebug(&idec->idec1Params);

			}
		}
	}

	if(DVEVM_ST_FAIL == retCode)
		dvtb_imgDec1Cleanup(idec);

	return retCode;
}

DvevmStRetCode
dvtb_imgDec1Decode(DvevmStImgDec1Info *idec, int *decDuration)
{
	int status = -1, i = 0;
	XDM1_BufDesc inBufDesc, outBufDesc;

	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(idec != NULL);
	ASSERT(idec->idec1Hdl != NULL);
	ASSERT(idec->inBuf.bufs[0] != NULL);
	ASSERT(idec->outBuf.bufs[0] != NULL);

	inBufDesc.numBufs = idec->inBuf.numBufs;
	for (i = 0; i < inBufDesc.numBufs; i++)
	{
		inBufDesc.descs[i].bufSize = idec->inBuf.bufSizes[i];
		inBufDesc.descs[i].buf = (XDAS_Int8 *) idec->inBuf.bufs[i];

		SYS_DEBUG("inBufDesc.descs[i].bufSize = %d\n", (int) inBufDesc.descs[i].bufSize);
		SYS_DEBUG("inBufDesc.descs[i].buf = %x\n", (unsigned int) inBufDesc.descs[i].buf);
	}

	outBufDesc.numBufs = idec->outBuf.numBufs;
	for (i = 0; i < outBufDesc.numBufs; i++)
	{
		outBufDesc.descs[i].bufSize = idec->outBuf.bufSizes[i];
		outBufDesc.descs[i].buf = (XDAS_Int8 *) idec->outBuf.bufs[i];

		SYS_DEBUG("outBufDesc.descs[i].bufSize = %d\n", (int) outBufDesc.descs[i].bufSize);
		SYS_DEBUG("outBufDesc.descs[i].buf = %x\n", (unsigned int) outBufDesc.descs[i].buf);
	}

	SYS_DEBUG("idec->idec1InArgs.size = %d\n", (int) idec->idec1InArgs.size);
	SYS_DEBUG("idec->idec1InArgs.numBytes  = %d\n", (int) idec->idec1InArgs.numBytes);

	dvtb_timeReset(idec->hTime);
	status = IMGDEC1_process(idec->idec1Hdl, &inBufDesc, &outBufDesc, &idec->idec1InArgs, &idec->idec1OutArgs);
	dvtb_timeDelta(idec->hTime, decDuration);

	if (status != IMGDEC1_EOK)
	{
		SYS_ERROR("Image Decode Process Failed (%d).", (int) status);
		SYS_ERROR("Codec Error : %d\n", (int) idec->idec1OutArgs.extendedError);
		retCode = DVEVM_ST_FAIL;
	}

	if(DVEVM_ST_FAIL != retCode)
		dvtb_imgDec1ProcessDebug(&idec->idec1OutArgs);

	return retCode;
}

DvevmStRetCode
dvtb_imgDec1Control(DvevmStImgDec1Info *idec)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(idec != NULL);
	ASSERT(idec->idec1Hdl != NULL);

	status = IMGDEC1_control(idec->idec1Hdl, idec->idec1Cmd, &idec->idec1DynParams, &idec->idec1Status);
	if (IMGDEC1_EOK != status)
	{
		SYS_ERROR("Image Decode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Image Decode Control => Command : %d\n", idec->idec1Cmd);
		dvtb_imgDec1ControlDebug(&idec->idec1Status);

		if (XDM_GETBUFINFO == idec->idec1Cmd)
		{
			idec->inBuf.numBufs = idec->idec1Status.bufInfo.minNumInBufs;
			idec->outBuf.numBufs = idec->idec1Status.bufInfo.minNumOutBufs;

			for (i = 0; i < (int)idec->inBuf.numBufs; i++)
			{
				idec->inBuf.bufSizes[i] = idec->idec1Status.bufInfo.minInBufSize[i];
			}

			for (i = 0; i < (int)idec->outBuf.numBufs; i++)
			{
				idec->outBuf.bufSizes[i] = idec->idec1Status.bufInfo.minOutBufSize[i];
			}
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_imgDec1Close(DvevmStImgDec1Info *idec)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (idec->inBuf.bufs[0] != NULL)
		idec->dvtb_ptrFreeCmem(&idec->inBuf);

	if (idec->outBuf.bufs[0] != NULL)
		idec->dvtb_ptrFreeCmem(&idec->outBuf);

	dvtb_imgDec1Cleanup(idec);

	return retCode;
}
