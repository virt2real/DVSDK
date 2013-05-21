/*
 * dvtbAudEnc.c
 *
 * XDM0.9 Audio Encode Interface implementation
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

#include "dvtbAudEnc.h"
#include "dvtbMemory.h"

void
dvtb_audEncCleanup(DvevmStAudEncInfo *ae)
{
	if (NULL != ae->aencHdl)
		AUDENC_delete(ae->aencHdl);

	if (0 != ae->inBuf.numBufs)
		dvtb_freeCmem(&ae->inBuf);

	if (0 != ae->outBuf.numBufs)
		dvtb_freeCmem(&ae->outBuf);
}

DvevmStRetCode
dvtb_audEncInit(DvevmStAudEncInfo *ae)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ae != NULL);
	ASSERT(ae->ceHdl != NULL);
	ASSERT(ae->aencName[0] != 0);

	if (NULL == (ae->aencHdl = AUDENC_create(ae->ceHdl, ae->aencName, &ae->aencParams)))
	{
		SYS_ERROR("Unable to initialize Audio Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}

	ae->aencCmd = XDM_GETBUFINFO;
	if (DVEVM_ST_FAIL == dvtb_audEncControl(ae))
	{
		SYS_ERROR("Unable to get the input/output buffer information\n");
		retCode = DVEVM_ST_FAIL;
	}
	else if (DVEVM_ST_FAIL == dvtb_allocCmem(&ae->inBuf))
	{
		SYS_ERROR("Unable to allocate memory for Out Buffer\n");
		retCode = DVEVM_ST_FAIL;
	}
	else if (DVEVM_ST_FAIL == dvtb_allocCmem(&ae->outBuf))
	{
		SYS_ERROR("Unable to allocate memory for Out Buffer\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
		SYS_DEBUG("\tAudio Encoder %s initialized.\n", ae->aencName);

	if(DVEVM_ST_FAIL == retCode)
		dvtb_audEncCleanup(ae);

	return DVEVM_ST_FAIL;
}

DvevmStRetCode
dvtb_audEncEncode(DvevmStAudEncInfo *ae, int *encDuration)
{
	int i = 0;
	XDM_BufDesc inBufDesc, outBufDesc;
	XDAS_Int32 status = -1;

	IAUDENC_InArgs encInArgs;
	IAUDENC_OutArgs encOutArgs;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ae != NULL);
	ASSERT(ae->ceHdl != NULL);
	ASSERT(ae->aencHdl != NULL);

	for (i = 0; i < ae->inBuf.numBufs; i++)
		ASSERT(ae->inBuf.bufs[i] != NULL);

	inBufDesc.bufSizes = (XDAS_Int32 *) &ae->inBuf.bufSizes;

	for (i = 0; i < ae->outBuf.numBufs; i++)
		ASSERT(ae->outBuf.bufs[i] != NULL);

	outBufDesc.bufSizes = (XDAS_Int32 *) &ae->outBuf.bufSizes;

	inBufDesc.numBufs = ae->inBuf.numBufs;
	outBufDesc.numBufs = ae->outBuf.numBufs;

	inBufDesc.bufs = (XDAS_Int8 **) ae->inBuf.bufs;
	outBufDesc.bufs = (XDAS_Int8 **) ae->outBuf.bufs;

	encInArgs.size = sizeof(encInArgs);
	encOutArgs.size = sizeof(encOutArgs);

	timeStmpBfrEnc = dvtb_getTime( );
	status = AUDENC_process(ae->aencHdl, &inBufDesc, &outBufDesc, &encInArgs, &encOutArgs);
	timeStmpAftrEnc = dvtb_getTime( );

	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != AUDENC_EOK)
	{
		SYS_ERROR("Error (%d) in Audio Encoder Process\n", (int) status);
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStRetCode
dvtb_audEncControl(DvevmStAudEncInfo *ae)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ae != NULL);
	ASSERT(ae->aencHdl != NULL);
	status = AUDENC_control(ae->aencHdl, ae->aencCmd, &ae->aencDynParams, &ae->aencStatus);
	if (AUDENC_EOK != status)
	{
		SYS_ERROR("Audio Encode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		if (XDM_GETBUFINFO == ae->aencCmd)
		{
			ae->inBuf.numBufs = ae->aencStatus.bufInfo.minNumInBufs;
			ae->outBuf.numBufs = ae->aencStatus.bufInfo.minNumOutBufs;

			for (i = 0; i < ae->inBuf.numBufs; i++)
			{
				ae->inBuf.bufSizes[i] = ae->aencStatus.bufInfo.minInBufSize[i];
			}

			for (i = 0; i < ae->outBuf.numBufs; i++)
			{
				ae->outBuf.bufSizes[i] = ae->aencStatus.bufInfo.minOutBufSize[i];
			}
		}
		SYS_DEBUG("Audio Encode Control => Command : %d\n", ae->aencCmd);
	}
	return retCode;
}

DvevmStRetCode
dvtb_audEncClose(DvevmStAudEncInfo *ae)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	dvtb_audEncCleanup(ae);
	return retCode;
}
