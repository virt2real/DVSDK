/*
 * dvtbSphEnc.c
 *
 * XDM0.9 Speech Encoder Interface implementation
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

#include "dvtbSphEnc.h"
#include "dvtbMemory.h"

void
dvtb_sphEncCleanup(DvevmStSphEncInfo *se)
{
	if (NULL != se->sencHdl)
		SPHENC_delete(se->sencHdl);

	if (NULL != se->inBuf.start)
		Memory_contigFree(se->inBuf.start, se->inBuf.size);

	if (NULL != se->outBuf.start)
		Memory_contigFree(se->outBuf.start, se->outBuf.size);

	se->sencHdl = NULL;
	se->inBuf.start = NULL;
	se->outBuf.start = NULL;
}

DvevmStRetCode
dvtb_sphEncInit(DvevmStSphEncInfo *se)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(se != NULL);
	ASSERT(se->ceHdl != NULL);
	ASSERT(se->sencName[0] != 0);

	se->sencCmd = XDM_SETPARAMS;
	if (NULL == (se->sencHdl = SPHENC_create(se->ceHdl, se->sencName, &se->sencParams)))
	{
		SYS_ERROR("Unable to initialize Speech Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else if (DVEVM_ST_FAIL == dvtb_sphEncControl(se))
	{
		SYS_ERROR("Unable to set Dynamic parameter\n");
		retCode = DVEVM_ST_FAIL;
	}
	else if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&se->inBuf.start, se->inBuf.size))
	{
		SYS_ERROR("Unable to allocate memory for In Buffer\n");
		retCode = DVEVM_ST_FAIL;
	}
	else if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&se->outBuf.start, se->outBuf.size))
	{
		SYS_ERROR("Unable to allocate memory for Out Buffer\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
		SYS_DEBUG("\tSpeech Encoder Name : %s\n", se->sencName);

	if(DVEVM_ST_FAIL == retCode)
		dvtb_sphEncCleanup(se);

	return retCode;
}

DvevmStRetCode
dvtb_sphEncEncode(DvevmStSphEncInfo *se, int *encDuration)
{
	XDAS_Int32 status = -1;
	XDM_BufDesc inBufDesc, outBufDesc;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	XDAS_Int8 *src = NULL, *dst = NULL;


	ASSERT(se != NULL);
	ASSERT(se->ceHdl != NULL);
	ASSERT(se->sencHdl != NULL);
	ASSERT(se->inBuf.start != NULL);
	ASSERT(se->outBuf.start != NULL);

	src = (XDAS_Int8 *) se->inBuf.start;
	dst = (XDAS_Int8 *) se->outBuf.start;

	inBufDesc.numBufs = outBufDesc.numBufs = 1;
	inBufDesc.bufSizes = (XDAS_Int32 *) &se->inBuf.size;
	outBufDesc.bufSizes = (XDAS_Int32 *) &se->inBuf.size;

	inBufDesc.bufs = &src;
	outBufDesc.bufs = &dst;

	timeStmpBfrEnc = dvtb_getTime( );
	status = SPHENC_process(se->sencHdl, &inBufDesc, &outBufDesc, &se->sencInArgs, &se->sencOutArgs);
	timeStmpAftrEnc = dvtb_getTime( );

	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != SPHENC_EOK)
	{
		SYS_ERROR("Error (%d) in Speech Encoder Process\n", (int) status);
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStRetCode
dvtb_sphEncControl(DvevmStSphEncInfo *se)
{
	int status = -1;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(se != NULL);
	ASSERT(se->sencHdl != NULL);

	status = SPHENC_control(se->sencHdl, se->sencCmd, &se->sencDynParams, &se->sencStatus);
	if (SPHENC_EOK != status)
	{
		SYS_ERROR("Speech Encode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Speech Encode Control => Command : %d\n", se->sencCmd);

		if (XDM_GETBUFINFO == se->sencCmd)
		{
			se->inBuf.size = se->sencStatus.bufInfo.minInBufSize[0];
			se->outBuf.size = se->sencStatus.bufInfo.minOutBufSize[0];
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_sphEncClose(DvevmStSphEncInfo *se)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	dvtb_sphEncCleanup(se);

	return retCode;
}