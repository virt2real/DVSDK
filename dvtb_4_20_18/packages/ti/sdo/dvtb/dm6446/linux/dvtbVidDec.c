/*
 * dvtbVidDec.c
 *
 * XDM0.9 Video Decode Interface implementation
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

#include "dvtbVidDec.h"
#include <ti/xdais/dm/ividdec.h>
#include <ti/xdais/dm/xdm.h>

void
dvtb_vidDecInitDebug(VIDDEC_Params *vdp)
{
	SYS_DEBUG("\n<======== Video Decoder Initialize Debug Start ==========>\n");
	SYS_DEBUG("Max Height         : %d\n", (int) vdp->maxHeight);
	SYS_DEBUG("Max Width          : %d\n", (int) vdp->maxWidth);
	SYS_DEBUG("Max Frame Rate     : %d\n", (int) vdp->maxFrameRate);
	SYS_DEBUG("Max Bit Rate       : %d\n", (int) vdp->maxBitRate);
	SYS_DEBUG("Endianness         : %d\n", (int) vdp->dataEndianness);
	SYS_DEBUG("Chroma Format      : %d\n", (int) vdp->forceChromaFormat);
	SYS_DEBUG("\n<======== Video Decoder Initialize Debug End ============>\n\n");
}

void
dvtb_vidDecProcessDebug(VIDDEC_OutArgs *vdo)
{
	SYS_DEBUG("\n<======== Video Decoder Process Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) vdo->extendedError);
	SYS_DEBUG("Bytes Consumed     : %d\n", (int) vdo->bytesConsumed);
	SYS_DEBUG("Decoded Frame Type : %d\n", (int) vdo->decodedFrameType);
	SYS_DEBUG("Output Id          : %d\n", (int) vdo->outputID);
	SYS_DEBUG("BUF-Display Num    : %d\n", (int) vdo->displayBufs.numBufs);
	SYS_DEBUG("BUF-Display Width  : %d\n", (int) vdo->displayBufs.width);
	SYS_DEBUG("BUF-Display Size   : %d\n", (int) vdo->displayBufs.bufSizes[0]);
	SYS_DEBUG("\n<======== Video Decoder Process Debug End ============>\n");
}

void
dvtb_vidDecControlDebug(VIDDEC_Status *vds)
{
	SYS_DEBUG("\n<======== Video Decoder Control Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) vds->extendedError);
	SYS_DEBUG("Output Height      : %d\n", (int) vds->outputHeight);
	SYS_DEBUG("Output Width       : %d\n", (int) vds->outputWidth);
	SYS_DEBUG("Avg Frame Rate     : %d\n", (int) vds->frameRate);
	SYS_DEBUG("Avg Bit Rate       : %d\n", (int) vds->bitRate);
	SYS_DEBUG("Content Type       : %d\n", (int) vds->contentType);
	SYS_DEBUG("Chroma Format      : %d\n", (int) vds->outputChromaFormat);
	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) vds->bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) vds->bufInfo.minNumOutBufs);
	SYS_DEBUG("BUF-Min In Size    : %d\n", (int) vds->bufInfo.minInBufSize[0]);
	SYS_DEBUG("BUF-Min Out Size   : %d\n", (int) vds->bufInfo.minOutBufSize[0]);
	SYS_DEBUG("\n<======== Video Decoder Control Debug End ============>\n");
}

void
dvtb_vidDecCleanup(DvevmStVidDecInfo *vd)
{
	if (NULL != vd->vdecHdl)
	{
		VIDDEC_delete(vd->vdecHdl);
		vd->vdecHdl = NULL;
	}
}

DvevmStRetCode
dvtb_vidDecInit(DvevmStVidDecInfo *vd)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(vd != NULL);
	ASSERT(vd->ceHdl != NULL);
	ASSERT(vd->vdecName[0] != 0);

	vd->vdecCmd = XDM_SETPARAMS;
	if (NULL == (vd->vdecHdl = VIDDEC_create(vd->ceHdl, vd->vdecName, &vd->vdecParams)))
	{
		SYS_ERROR("Unable to initialize Video Decoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else if (DVEVM_ST_FAIL == dvtb_vidDecControl(vd))
	{
		SYS_ERROR("Unable to set dynamic parameters\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		vd->vdecCmd = XDM_GETBUFINFO;
		if (DVEVM_ST_FAIL == dvtb_vidDecControl(vd))
		{
			SYS_ERROR("Unable to get the input/output buffer information\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			SYS_DEBUG("Video Decoder <%s> initialized\n", vd->vdecName);
			dvtb_vidDecInitDebug(&vd->vdecParams);
		}
	}
	if(DVEVM_ST_FAIL == retCode)
		dvtb_vidDecCleanup(vd);

	return retCode;
}

DvevmStRetCode
dvtb_vidDecDecode(DvevmStVidDecInfo *vd, int *decDuration)
{
	XDAS_Int32 status = -1;
	XDM_BufDesc inBufDesc, outBufDesc;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(vd != NULL);
	ASSERT(vd->vdecHdl != NULL);
	ASSERT(vd->inBuf.bufs[0] != NULL);
	ASSERT(vd->outBuf.bufs[0] != NULL);

	inBufDesc.numBufs = vd->inBuf.numBufs;
	inBufDesc.bufSizes = (XDAS_Int32 *) vd->inBuf.bufSizes;
	inBufDesc.bufs = (XDAS_Int8 **) vd->inBuf.bufs;

	outBufDesc.numBufs = vd->outBuf.numBufs;
	outBufDesc.bufSizes = (XDAS_Int32 *) vd->outBuf.bufSizes;
	outBufDesc.bufs = (XDAS_Int8 **) vd->outBuf.bufs;

	vd->skipFrame = DVEVM_ST_FALSE;
	timeStmpBfrEnc = dvtb_getTime( );
	status = VIDDEC_process(vd->vdecHdl, &inBufDesc, &outBufDesc, &vd->vdecInArgs, &vd->vdecOutArgs);
	timeStmpAftrEnc = dvtb_getTime( );
	*decDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != VIDDEC_EOK)
	{
		if (XDM_ISFATALERROR(vd->vdecOutArgs.extendedError))
		{
			SYS_ERROR("Video Decode Process failed (%d) with a Codec fatal error (0x%x)\n", (int) status, (int) vd->vdecOutArgs.extendedError);
			retCode = DVEVM_ST_FAIL;
		}

		SYS_DEBUG("Video Decode Process Failed (%d)\n", (int) status);
		SYS_DEBUG("Codec Error : %d\n", (int) vd->vdecOutArgs.extendedError);
	}

	if(DVEVM_ST_FAIL != retCode)
		dvtb_vidDecProcessDebug(&vd->vdecOutArgs);

	return retCode;
}

DvevmStRetCode
dvtb_vidDecControl(DvevmStVidDecInfo *vd)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(vd != NULL);
	ASSERT(vd->vdecHdl != NULL);

	status = VIDDEC_control(vd->vdecHdl, vd->vdecCmd, &vd->vdecDynParams, &vd->vdecStatus);
	if (VIDDEC_EOK != status)
	{
		SYS_ERROR("Video Decode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Video Decode Control => Command : %d\n", vd->vdecCmd);
		dvtb_vidDecControlDebug(&vd->vdecStatus);

		if (XDM_GETBUFINFO == vd->vdecCmd)
		{
			vd->inBuf.numBufs = vd->vdecStatus.bufInfo.minNumInBufs;
			vd->outBuf.numBufs = vd->vdecStatus.bufInfo.minNumOutBufs;

			for (i = 0; i < vd->inBuf.numBufs; i++)
				vd->inBuf.bufSizes[i] = vd->vdecStatus.bufInfo.minInBufSize[i];

			for (i = 0; i < vd->outBuf.numBufs; i++)
				vd->outBuf.bufSizes[i] = vd->vdecStatus.bufInfo.minOutBufSize[i];
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_vidDecClose(DvevmStVidDecInfo *vd)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	dvtb_vidDecCleanup(vd);
	return retCode;
}
