/*
 * dvtbJPEGDec1.c
 *
 * XDM1.0 JPEG Decode Interface implementation
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

#include "dvtbJPEGDec1.h"
#include "dvtbMemory.h"

void
dvtb_jpegDec1InitDebug(IJPEGDEC_Params *idp)
{
	SYS_DEBUG("\n<======== JPEG Decoder Params Debug Start ==========>\n");
	SYS_DEBUG("Size               : %d\n", (int) idp->imgdecParams.size);
	SYS_DEBUG("Max Height         : %d\n", (int) idp->imgdecParams.maxHeight);
	SYS_DEBUG("Max Width          : %d\n", (int) idp->imgdecParams.maxWidth);
	SYS_DEBUG("Max Scans          : %d\n", (int) idp->imgdecParams.maxScans);
	SYS_DEBUG("Data Endianness    : %d\n", (int) idp->imgdecParams.dataEndianness);
	SYS_DEBUG("Force Chroma Format: %d\n", (int) idp->imgdecParams.forceChromaFormat);
	SYS_DEBUG("ProgressiveDecFlag : %d\n", (int) idp->progressiveDecFlag);
	SYS_DEBUG("outImgRes          : %d\n", (int) idp->outImgRes);
	SYS_DEBUG("\n<======== JPEG Decoder Params Debug End ============>\n\n");
}

void
dvtb_jpegDec1ProcessDebug(IJPEGDEC_OutArgs *ido)
{
	SYS_DEBUG("\n<======== JPEG Decoder OutArgs Debug Start ==========>\n");
	SYS_DEBUG("Size               : %d\n", (int) ido->imgdecOutArgs.size);
	SYS_DEBUG("Extended Error     : %d\n", (int) ido->imgdecOutArgs.extendedError);
	SYS_DEBUG("Bytes Consumed     : %d\n", (int) ido->imgdecOutArgs.bytesConsumed);
	SYS_DEBUG("Current AU         : %d\n", (int) ido->imgdecOutArgs.currentAU);
	SYS_DEBUG("Current Scan       : %d\n", (int) ido->imgdecOutArgs.currentScan);
	SYS_DEBUG("\n<======== JPEG Decoder OutArgs Debug End ============>\n\n");
}

void
dvtb_jpegDec1ControlDebug(IJPEGDEC_Status *ids)
{
	int i = 0;

	SYS_DEBUG("\n<======== JPEG Decoder Status Debug Start ==========>\n");
	SYS_DEBUG("Size               : %d\n", (int) ids->imgdecStatus.size);
	SYS_DEBUG("Extended Error     : %d\n", (int) ids->imgdecStatus.extendedError);
	SYS_DEBUG("Data.buf           : %u\n", (int) ids->imgdecStatus.data.buf);
	SYS_DEBUG("Data.bufSize       : %d\n", (int) ids->imgdecStatus.data.bufSize);
	SYS_DEBUG("outputHeight       : %d\n", (int) ids->imgdecStatus.outputHeight);
	SYS_DEBUG("outputWidth        : %d\n", (int) ids->imgdecStatus.outputWidth);
	SYS_DEBUG("ImageWidth         : %d\n", (int) ids->imgdecStatus.imageWidth);
	SYS_DEBUG("outputChromaFormat : %d\n", (int) ids->imgdecStatus.outputChromaFormat);
	SYS_DEBUG("totalAU            : %d\n", (int) ids->imgdecStatus.totalAU);
	SYS_DEBUG("totalScan          : %d\n", (int) ids->imgdecStatus.totalScan);
	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ids->imgdecStatus.bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ids->imgdecStatus.bufInfo.minNumOutBufs);

	for (i = 0; i < ids->imgdecStatus.bufInfo.minNumInBufs; i++)
		SYS_DEBUG("BUF-Min In Size  [%d]  : %d\n", i, (int) ids->imgdecStatus.bufInfo.minInBufSize[i]);

	for (i = 0; i < ids->imgdecStatus.bufInfo.minNumOutBufs; i++)
		SYS_DEBUG("BUF-Min Out Size  [%d] : %d\n", i, (int) ids->imgdecStatus.bufInfo.minOutBufSize[i]);

	SYS_DEBUG("mode               : %d\n", (int) ids->mode);
	SYS_DEBUG("imageHeight        : %d\n", (int) ids->imageHeight);
	SYS_DEBUG("decImageSize       : %x\n", (int) ids->decImageSize);
	SYS_DEBUG("lastMCU            : %d\n", (int) ids->lastMCU);
	SYS_DEBUG("H sampling Freq    : %d\n", (int) ids->hSampleFreq);
	SYS_DEBUG("V sampling Freq    : %d\n", (int) ids->hSampleFreq);
	SYS_DEBUG("End of sequence    : %d\n", (int) ids->end_of_seq);
	SYS_DEBUG("End of Scan        : %x\n", (int) ids->end_of_scan);
	SYS_DEBUG("bytesgenerated[0]  : %d\n", (int) ids->bytesgenerated[0]);
	SYS_DEBUG("bytesgenerated[1]  : %d\n", (int) ids->bytesgenerated[1]);
	SYS_DEBUG("bytesgenerated[2]  : %d\n", (int) ids->bytesgenerated[2]);

	SYS_DEBUG("\n<======== JPEG Decoder Status Debug End ============>\n");
}

void
dvtb_jpegDec1Cleanup(DvevmStJpegDec1Info *jpeg1)
{
	if (NULL != jpeg1->idec1Hdl)
	{
		IMGDEC1_delete(jpeg1->idec1Hdl);
		jpeg1->idec1Hdl = NULL;
	}
}

DvevmStRetCode
dvtb_jpegDec1Init(DvevmStJpegDec1Info *jpeg1)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(jpeg1 != NULL);
	ASSERT(jpeg1->ceHdl != NULL);
	ASSERT(jpeg1->idec1Name[0] != 0);

	jpeg1->idec1Cmd = XDM_SETPARAMS;

	dvtb_jpegDec1InitDebug(&jpeg1->idec1Params);

	if (NULL == (jpeg1->idec1Hdl = IMGDEC1_create(jpeg1->ceHdl, jpeg1->idec1Name, (IIMGDEC1_Params *) &jpeg1->idec1Params)))
	{
		SYS_ERROR("Unable to initialize JPEG Decoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		if (DVEVM_ST_FAIL == dvtb_jpegDec1Control(jpeg1))
		{
			SYS_ERROR("Unable to set JPEG Decoder dynamic parameters\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			jpeg1->idec1Cmd = XDM_GETBUFINFO;
			if (DVEVM_ST_FAIL == dvtb_jpegDec1Control(jpeg1))
			{
				SYS_ERROR("Unable to get buffer info\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (DVEVM_ST_FAIL == dvtb_allocCmem(&jpeg1->inBuf))
			{
				SYS_ERROR("Unable to allocate memory for input buffer\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (DVEVM_ST_FAIL == dvtb_allocCmem(&jpeg1->outBuf))
			{
				SYS_ERROR("Unable to allocate memory for output buffer\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_DEBUG("JPEG Decoder <%s> initialized\n", jpeg1->idec1Name);
				dvtb_jpegDec1InitDebug(&jpeg1->idec1Params);
			}
		}
	}

	if(DVEVM_ST_FAIL == retCode)
		dvtb_jpegDec1Cleanup(jpeg1);

	return retCode;
}

DvevmStRetCode
dvtb_jpegDec1Decode(DvevmStJpegDec1Info *jpeg1, int *decDuration)
{
	int i = 0, status = -1;
	XDM1_BufDesc inBufDesc, outBufDesc;

	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(jpeg1 != NULL);
	ASSERT(jpeg1->idec1Hdl != NULL);
	ASSERT(jpeg1->inBuf.bufs[0] != NULL);
	ASSERT(jpeg1->outBuf.bufs[0] != NULL);

	inBufDesc.numBufs = jpeg1->inBuf.numBufs;
	for (i = 0; i < inBufDesc.numBufs; i++)
	{
		inBufDesc.descs[i].bufSize = jpeg1->inBuf.bufSizes[i];
		inBufDesc.descs[i].buf = (XDAS_Int8 *) jpeg1->inBuf.bufs[i];
		SYS_DEBUG("inBufDesc.descs[i].bufSize = %d\n", (int) inBufDesc.descs[i].bufSize);
		SYS_DEBUG("inBufDesc.descs[i].buf = %x\n", (unsigned int) inBufDesc.descs[i].buf);
	}

	outBufDesc.numBufs = jpeg1->outBuf.numBufs;
	for (i = 0; i < outBufDesc.numBufs; i++)
	{
		outBufDesc.descs[i].bufSize = jpeg1->outBuf.bufSizes[i];
		outBufDesc.descs[i].buf = (XDAS_Int8 *) jpeg1->outBuf.bufs[i];
		SYS_DEBUG("outBufDesc.descs[i].bufSize = %d\n", (int) outBufDesc.descs[i].bufSize);
		SYS_DEBUG("outBufDesc.descs[i].buf = %x\n", (unsigned int) outBufDesc.descs[i].buf);
	}

	SYS_DEBUG("jpeg1->idec1InArgs.imgdecInArgs.size = %d\n", (int) jpeg1->idec1InArgs.imgdecInArgs.size);
	SYS_DEBUG("jpeg1->idec1InArgs.imgdecInArgs.numBytes  = %d\n", (int) jpeg1->idec1InArgs.imgdecInArgs.numBytes);

	dvtb_timeReset(jpeg1->hTime);
	status = IMGDEC1_process(jpeg1->idec1Hdl, &inBufDesc, &outBufDesc, (IIMGDEC1_InArgs *) &jpeg1->idec1InArgs, (IIMGDEC1_OutArgs *) &jpeg1->idec1OutArgs);
	dvtb_timeDelta(jpeg1->hTime, decDuration);
	
	if (status != IMGDEC1_EOK)
	{
		SYS_ERROR("JPEG Decode Process Failed (%d).", (int) status);
		SYS_ERROR("Codec Error : %d\n", (int) jpeg1->idec1OutArgs.imgdecOutArgs.extendedError);
		retCode = DVEVM_ST_FAIL;
	}

	if(DVEVM_ST_FAIL != retCode)
		dvtb_jpegDec1ProcessDebug(&jpeg1->idec1OutArgs);

	return retCode;

}

DvevmStRetCode
dvtb_jpegDec1Control(DvevmStJpegDec1Info *jpeg1)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(jpeg1 != NULL);
	ASSERT(jpeg1->idec1Hdl != NULL);

	status = IMGDEC1_control(jpeg1->idec1Hdl, jpeg1->idec1Cmd, (IIMGDEC1_DynamicParams *) &jpeg1->idec1DynParams, (IIMGDEC1_Status *) &jpeg1->idec1Status);
	if (IMGDEC1_EOK != status)
	{
		SYS_ERROR("JPEG Decode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("JPEG Decode Control => Command : %d\n", jpeg1->idec1Cmd);
		dvtb_jpegDec1ControlDebug(&jpeg1->idec1Status);

		if (XDM_GETBUFINFO == jpeg1->idec1Cmd)
		{
			jpeg1->inBuf.numBufs = jpeg1->idec1Status.imgdecStatus.bufInfo.minNumInBufs;
			jpeg1->outBuf.numBufs = jpeg1->idec1Status.imgdecStatus.bufInfo.minNumOutBufs;

			for (i = 0; i < (int)jpeg1->inBuf.numBufs; i++)
			{
				jpeg1->inBuf.bufSizes[i] = jpeg1->idec1Status.imgdecStatus.bufInfo.minInBufSize[i];
			}

			for (i = 0; i < (int)jpeg1->outBuf.numBufs; i++)
			{
				jpeg1->outBuf.bufSizes[i] = jpeg1->idec1Status.imgdecStatus.bufInfo.minOutBufSize[i];
			}
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_jpegDec1Close(DvevmStJpegDec1Info *jpeg)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (jpeg->inBuf.bufs[0] != NULL)
	{
		dvtb_freeCmem(&jpeg->inBuf);
	}

	if (jpeg->outBuf.bufs[0] != NULL)
	{
		dvtb_freeCmem(&jpeg->outBuf);
	}

	dvtb_jpegDec1Cleanup(jpeg);

	return retCode;
}
