/*
 * dvtbSphEnc1.c
 *
 * DVTB(wince) XDM1.0 Speech Encoder implementation
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

#include "dvtbSphEnc1.h"
#include "dvtbMemory.h"

void
dvtb_sphEnc1Cleanup(DvevmStSphEnc1Info *se)
{
	if (NULL != se->inBuf.start)
		dvtb_freeSingleBufCmem(se->inBuf.start, se->inBuf.size);

	if (NULL != se->outBuf.start)
		dvtb_freeSingleBufCmem(se->outBuf.start, se->outBuf.size);

	se->inBuf.start = NULL;
	se->outBuf.start = NULL;

	if (NULL != se->sencHdl)
	{
		SPHENC1_delete(se->sencHdl);
		se->sencHdl = NULL;
	}

}

DvevmStRetCode
dvtb_sphEnc1Init(DvevmStSphEnc1Info *se)
{
	XDAS_Int32 status = -1;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(se != NULL);
	ASSERT(se->ceHdl != NULL);
	ASSERT(se->sencName[0] != 0);

	if (NULL == (se->sencHdl = SPHENC1_create(se->ceHdl, se->sencName,&se->sencParams)))
	{
		SYS_ERROR("Unable to initialize Speech Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&se->inBuf.start, se->inBuf.size))
	{
		SYS_ERROR("Unable to allocate memory for In Buffer\n");
		retCode = DVEVM_ST_FAIL;
	}
	else if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&se->outBuf.start, se->outBuf.size * 2))
	{
		SYS_ERROR("Unable to allocate memory for Out Buffer\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("\tSpeech Encoder Name : %s\n", se->sencName);

		status = SPHENC1_control(se->sencHdl, XDM_SETPARAMS,&se->sencDynParams, &se->sencStatus);

		if (status != SPHENC1_EOK)
		{
			SYS_ERROR("control failed\n");
			retCode = DVEVM_ST_FAIL;
		}
	}

	if (DVEVM_ST_FAIL == retCode)
		dvtb_sphEnc1Cleanup(se);

	return retCode;
}

DvevmStRetCode
dvtb_sphEnc1Encode(DvevmStSphEnc1Info *se, int *encDuration)
{
	XDAS_Int32 status = -1;
	XDM1_SingleBufDesc inBufDesc, outBufDesc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(se != NULL);
	ASSERT(se->ceHdl != NULL);
	ASSERT(se->sencHdl != NULL);
	ASSERT(se->inBuf.start != NULL);
	ASSERT(se->outBuf.start != NULL);

	inBufDesc.buf = (XDAS_Int8 *) se->inBuf.start;
	inBufDesc.bufSize = se->inBuf.size;

	outBufDesc.buf = (XDAS_Int8 *) se->outBuf.start;
	outBufDesc.bufSize = se->outBuf.size;

	memset(&se->sencInArgs, 0, sizeof(se->sencInArgs));
	memset(&se->sencOutArgs, 0, sizeof(se->sencOutArgs));

	se->sencInArgs.size = sizeof(SPHENC1_InArgs);
	se->sencOutArgs.size = sizeof(SPHENC1_OutArgs);

	dvtb_timeReset(se->hTime);
	status = SPHENC1_process(se->sencHdl, &inBufDesc, &outBufDesc, &se->sencInArgs, &se->sencOutArgs);
	dvtb_timeDelta(se->hTime, encDuration);
	
	if (status != SPHENC1_EOK)
	{
		SYS_ERROR("Error (%d) in Speech Encoder Process\n", (int) status);
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStRetCode
dvtb_sphEnc1Control(DvevmStSphEnc1Info *se)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	return retCode;
}

DvevmStRetCode
dvtb_sphEnc1Close(DvevmStSphEnc1Info *se)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	dvtb_sphEnc1Cleanup(se);
	return retCode;
}
