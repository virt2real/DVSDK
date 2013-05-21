/*
 * dvtbSphDec.c
 *
 * XDM0.9 Speech Decoder implementation
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

#include "dvtbSphDec.h"
#include "dvtbMemory.h"

void
dvtb_sphDecCleanup(DvevmStSphDecInfo *sd)
{
	if (NULL != sd->sdecHdl)
		SPHDEC_delete(sd->sdecHdl);

	if (NULL != sd->inBuf.start)
		dvtb_freeSingleBufCmem(sd->inBuf.start, sd->inBuf.size);

	if (NULL != sd->outBuf.start)
		dvtb_freeSingleBufCmem(sd->outBuf.start, sd->outBuf.size);

	sd->inBuf.start = NULL;
	sd->outBuf.start = NULL;
}

DvevmStRetCode
dvtb_sphDecInit(DvevmStSphDecInfo *sd)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(sd != NULL);
	ASSERT(sd->ceHdl != NULL);
	ASSERT(sd->sdecName[0] != 0);

	sd->sdecCmd = XDM_SETPARAMS;
	if (NULL == (sd->sdecHdl = SPHDEC_create(sd->ceHdl, sd->sdecName, &sd->sdecParams)))
	{
		SYS_ERROR("Unable to initialize Speech Decoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		if (DVEVM_ST_FAIL == dvtb_sphDecControl(sd))
		{
			SYS_ERROR("Unable to set Dynamic parameter\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&sd->inBuf.start, sd->inBuf.size))
			{
				SYS_ERROR("Unable to allocate memory for In Buffer\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&sd->outBuf.start, sd->outBuf.size))
			{
				SYS_ERROR("Unable to allocate memory for Out Buffer\n");
				retCode = DVEVM_ST_FAIL;
			}
		}
	}

	if(DVEVM_ST_FAIL == retCode)
		dvtb_sphDecCleanup(sd);

	return retCode;
}

DvevmStRetCode
dvtb_sphDecDecode(DvevmStSphDecInfo *sd, int *decDuration)
{
	int i = 0, status = -1;

	XDAS_Int8 *src, *dst;
	XDM_BufDesc inBufDesc, outBufDesc;

	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	DvevmStTime timeStmpBfrDec, timeStmpAftrDec;

	ASSERT(sd != NULL);
	ASSERT(sd->ceHdl != NULL);
	ASSERT(sd->sdecHdl != NULL);
	ASSERT(sd->inBuf.start != NULL);
	ASSERT(sd->outBuf.start != NULL);

	src = (XDAS_Int8 *) sd->inBuf.start;
	dst = (XDAS_Int8 *) sd->outBuf.start;

	inBufDesc.numBufs = outBufDesc.numBufs = 1;
	inBufDesc.bufSizes = (XDAS_Int32 *) &sd->inBuf.size;
	outBufDesc.bufSizes = (XDAS_Int32 *) &sd->outBuf.size;

	inBufDesc.bufs = &src;
	outBufDesc.bufs = &dst;

	timeStmpBfrDec = dvtb_getTime();
	status = SPHDEC_process(sd->sdecHdl, &inBufDesc, &outBufDesc, &sd->sdecInArgs, &sd->sdecOutArgs);
	timeStmpAftrDec = dvtb_getTime();

	*decDuration = ((timeStmpAftrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrDec.tv_usec) - ((timeStmpBfrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrDec.tv_usec);

	if (status != SPHDEC_EOK)
	{
		SYS_ERROR("Error (%d) in Speech Decoder Process\n", (int) status);
		retCode = DVEVM_ST_FAIL;
	}

	if(DVEVM_ST_FAIL != retCode)
	{
		/* Expand mono to stereo */
		for (i = (sd->outBuf.size - 1); i >= 0; i--)
		{
			dst[4 * i] = dst[2 * i];
			dst[4 * i + 1] = dst[2 * i + 1];
			dst[4 * i + 2] = dst[2 * i];
			dst[4 * i + 3] = dst[2 * i + 1];
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_sphDecControl(DvevmStSphDecInfo *sd)
{
	int status = -1;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(sd != NULL);
	ASSERT(sd->sdecHdl != NULL);

	status = SPHDEC_control(sd->sdecHdl, sd->sdecCmd, &sd->sdecDynParams, &sd->sdecStatus);
	if (SPHDEC_EOK != status)
	{
		SYS_ERROR("Speech Decode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Speech Encode Control => Command : %d\n", sd->sdecCmd);

		if (XDM_GETBUFINFO == sd->sdecCmd)
		{
			sd->inBuf.size = sd->sdecStatus.bufInfo.minInBufSize[0];
			sd->outBuf.size = sd->sdecStatus.bufInfo.minOutBufSize[0];
		}
	}

	return retCode;
}

DvevmStRetCode dvtb_sphDecClose(DvevmStSphDecInfo *sd)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	dvtb_sphDecCleanup(sd);

	return retCode;
}
