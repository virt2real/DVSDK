/*
 * dvtbSphDec1.c
 *
 * XDM1.0 Speech Decoder implementation
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

#include "dvtbSphDec1.h"
#include "dvtbMemory.h"

void
dvtb_sphDec1Cleanup(DvevmStSphDec1Info *sd)
{
	if (NULL != sd->sdecHdl)
		SPHDEC1_delete(sd->sdecHdl);

	if (NULL != sd->inBuf.start)
		dvtb_freeSingleBufCmem(sd->inBuf.start, sd->inBuf.size);

	if (NULL != sd->outBuf.start)
		dvtb_freeSingleBufCmem(sd->outBuf.start, sd->outBuf.size);

	sd->sdecHdl = NULL;
	sd->inBuf.start = NULL;
	sd->outBuf.start = NULL;
}

DvevmStRetCode
dvtb_sphDec1Init(DvevmStSphDec1Info *sd)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(sd != NULL);
	ASSERT(sd->ceHdl != NULL);
	ASSERT(sd->sdecName[0] != 0);

	if (NULL == (sd->sdecHdl = SPHDEC1_create(sd->ceHdl, sd->sdecName, &sd->sdecParams)))
	{
		SYS_ERROR("Unable to initialize Speech Decoder\n");
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

	if (DVEVM_ST_FAIL == retCode)
		dvtb_sphDec1Cleanup(sd);

	return retCode;
}


DvevmStRetCode
dvtb_sphDec1Decode(DvevmStSphDec1Info *sd, int *decDuration)
{
	XDAS_Int32 status = -1;

	XDM1_SingleBufDesc inBufDesc, outBufDesc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	DvevmStTime timeStmpBfrDec, timeStmpAftrDec;

	ASSERT(sd != NULL);
	ASSERT(sd->ceHdl != NULL);
	ASSERT(sd->sdecHdl != NULL);
	ASSERT(sd->inBuf.start != NULL);
	ASSERT(sd->outBuf.start != NULL);

	inBufDesc.bufSize = sd->inBuf.size;
	outBufDesc.bufSize = sd->outBuf.size;

	inBufDesc.buf = (XDAS_Int8 *) sd->inBuf.start;
	outBufDesc.buf = (XDAS_Int8 *) sd->outBuf.start;

	memset(&sd->sdecInArgs, 0, sizeof(sd->sdecInArgs));
	memset(&sd->sdecOutArgs, 0, sizeof(sd->sdecOutArgs));

	sd->sdecInArgs.size = sizeof(SPHDEC1_InArgs);
	sd->sdecOutArgs.size = sizeof(SPHDEC1_OutArgs);

	sd->sdecInArgs.frameType = 0; //ISPHDEC1_FTYPE_SPEECHGOOD;

	timeStmpBfrDec = dvtb_getTime( );
	status = SPHDEC1_process(sd->sdecHdl, &inBufDesc, &outBufDesc, &sd->sdecInArgs, &sd->sdecOutArgs);
	timeStmpAftrDec = dvtb_getTime( );

	*decDuration = ((timeStmpAftrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrDec.tv_usec) - ((timeStmpBfrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrDec.tv_usec);

	if (status != SPHDEC1_EOK)
	{
		SYS_ERROR("Error (%d) in Speech Decoder Process\n", (int) status);
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStRetCode
dvtb_sphDec1Control1(DvevmStSphDec1Info *sd)
{

	int status = -1;

	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(sd != NULL);
	ASSERT(sd->ceHdl != NULL);
	ASSERT(sd->sdecHdl != NULL);

	sd->sdecDynParams.size = sizeof(SPHDEC1_DynamicParams);
	sd->sdecDynParams.postFilter = 1;

	status = SPHDEC1_control(sd->sdecHdl, 1, &sd->sdecDynParams, &sd->sdecStatus);

	if (SPHDEC1_EOK != status)
	{
		SYS_ERROR("Speech Decode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStRetCode
dvtb_sphDec1Control2(DvevmStSphDec1Info *sd)
{
	int status = -1;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(sd != NULL);
	ASSERT(sd->ceHdl != NULL);
	ASSERT(sd->sdecHdl != NULL);

	status = SPHDEC1_control(sd->sdecHdl, 0, &sd->sdecDynParams, &sd->sdecStatus);

	if (SPHDEC1_EOK != status)
	{
		SYS_ERROR("Speech Decoder Control GETSTATUS failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStRetCode
dvtb_sphDec1Control(DvevmStSphDec1Info *sd)
{
	int status = -1;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(sd != NULL);
	ASSERT(sd->ceHdl != NULL);
	ASSERT(sd->sdecHdl != NULL);

	status = SPHDEC1_control(sd->sdecHdl, 2, &sd->sdecDynParams, &sd->sdecStatus);

	if (SPHDEC1_EOK != status)
	{
		SYS_ERROR("Speech Decoder Control Reset failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStRetCode
dvtb_sphDec1Close(DvevmStSphDec1Info *sd)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	dvtb_sphDec1Cleanup(sd);
	return retCode;
}
