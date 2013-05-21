/*
 * dvtbAACEnc.c
 *
 * XDM0.9 AAC Encode Interface implementation
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

#include "dvtbAACEnc.h"
#include "dvtbMemory.h"

#if 0
void
dvtb_aacEncInitDebug(IAACENC_Params *aep)
{
	SYS_DEBUG("\n<======== Audio Encoder Initialize Debug Start ==========>\n");
	SYS_DEBUG("\n<======== Audio Encoder Initialize Debug End ============>\n\n");
}

void
dvtb_aacEncDynDebug(IAACENC_DynamicParams *aep)
{
	SYS_DEBUG("\n<======== Audio Encoder Dynamic Debug Start ==========>\n");
	SYS_DEBUG("\n<======== Audio Encoder Dynamic Debug End ============>\n\n");
}

void
dvtb_aacEncControlDebug(IAACENC_Status *aes)
{

	SYS_DEBUG("\n<======== Audio Encoder Control Debug Start ==========>\n");
	SYS_DEBUG("\n<======== Audio Encoder Control Debug End ============>\n");
}
#endif
void
dvtb_aacEncCleanup(DvevmStAACEncInfo *ae)
{
#if 0
	if (NULL != ae->aencHdl)
		AUDENC_delete(ae->aencHdl);

	ae->aencHdl = NULL;

	if (ae->inBuf.numBufs > 0)
		dvtb_freeCmem(&ae->inBuf);

	if (ae->outBuf.numBufs > 0)
		dvtb_freeCmem(&ae->outBuf);
#endif
}

DvevmStRetCode
dvtb_aacEncInit(DvevmStAACEncInfo *ae)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
#if 0

	ASSERT(ae != NULL);
	ASSERT(ae->ceHdl != NULL);
	ASSERT(ae->aencName[0] != 0);

	dvtb_aacEncInitDebug(&ae->aencParams);
	if (NULL == (ae->aencHdl = AUDENC_create(ae->ceHdl, ae->aencName, (AUDENC_Params *) &ae->aencParams)))
	{
		SYS_ERROR("Unable to initialize Audio Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		ae->aencCmd = XDM_SETPARAMS;

		if (DVEVM_ST_FAIL == dvtb_aacEncControl(ae))
		{
			SYS_ERROR("Unable to set dynamic params\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			ae->aencCmd = XDM_GETBUFINFO;
			if (DVEVM_ST_FAIL == dvtb_aacEncControl(ae))
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
			{
				SYS_DEBUG("\tENC-Audio Encoder %s initialized.\n", ae->aencName);
			}
		}
	}
	if(DVEVM_ST_FAIL == retCode)
		dvtb_aacEncCleanup(ae);
#endif

	return retCode;
}

DvevmStRetCode
dvtb_aacEncEncode(DvevmStAACEncInfo *ae, int *encDuration)
{
#if 0
	XDAS_Int32 status = -1, i =0;
	XDM_BufDesc inBufDesc, outBufDesc;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
#endif
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

#if 0
	ASSERT(ae != NULL);
	ASSERT(ae->ceHdl != NULL);
	ASSERT(ae->aencHdl != NULL);

	for (i = 0; i < ae->inBuf.numBufs; i++)
	{
		ASSERT(ae->inBuf.bufs[i] != NULL);
	}
	inBufDesc.bufSizes = (XDAS_Int32 *) &ae->inBuf.bufSizes;

	for (i = 0; i < ae->outBuf.numBufs; i++)
	{
		ASSERT(ae->outBuf.bufs[i] != NULL);
	}
	outBufDesc.bufSizes = (XDAS_Int32 *) &ae->outBuf.bufSizes;

	inBufDesc.numBufs = ae->inBuf.numBufs;
	outBufDesc.numBufs = ae->outBuf.numBufs;

	inBufDesc.bufs = (XDAS_Int8 **) ae->inBuf.bufs;
	outBufDesc.bufs = (XDAS_Int8 **) ae->outBuf.bufs;

	ae->aencOutArgs.audenc_outArgs.extendedError = 0;
	timeStmpBfrEnc = dvtb_getTime( );
	status = AUDENC_process(ae->aencHdl, &inBufDesc, &outBufDesc, (AUDENC_InArgs *) &ae->aencInArgs, (AUDENC_OutArgs *) &ae->aencOutArgs);
	timeStmpAftrEnc = dvtb_getTime( );
	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != AUDENC_EOK)
	{
		SYS_ERROR("Error (%d) in Audio Encoder Process. Codec Error = %d\n", (int) status, (int) ae->aencOutArgs.audenc_outArgs.extendedError);
		retCode = DVEVM_ST_FAIL;
	}

	if(DVEVM_ST_FAIL != retCode)
		ae->bytesGenerated = ae->aencOutArgs.audenc_outArgs.bytesGenerated;
#endif
	return retCode;
}

DvevmStRetCode
dvtb_aacEncControl(DvevmStAACEncInfo *ae)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
#if 0
	int status = -1, i = 0;

	ASSERT(ae != NULL);
	ASSERT(ae->aencHdl != NULL);

	status = AUDENC_control(ae->aencHdl, ae->aencCmd, (AUDENC_DynamicParams *) &ae->aencDynParams, (AUDENC_Status *) &ae->aencStatus);
	if (AUDENC_EOK != status)
	{
		SYS_ERROR("Audio Encode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		if (XDM_GETBUFINFO == ae->aencCmd)
		{
			ae->inBuf.numBufs = ae->aencStatus.audenc_status.bufInfo.minNumInBufs;
			ae->outBuf.numBufs = ae->aencStatus.audenc_status.bufInfo.minNumOutBufs;

			for (i = 0; i < ae->inBuf.numBufs; i++)
			{
				ae->inBuf.bufSizes[i] = ae->aencStatus.audenc_status.bufInfo.minInBufSize[i];
			}

			for (i = 0; i < ae->outBuf.numBufs; i++)
			{
				ae->outBuf.bufSizes[i] = ae->aencStatus.audenc_status.bufInfo.minOutBufSize[i];
			}

			dvtb_aacEncControlDebug(&ae->aencStatus);
		}
		else if (XDM_SETPARAMS == ae->aencCmd)
		{
			dvtb_aacEncDynDebug(&ae->aencDynParams);
		}
		else if (XDM_GETSTATUS == ae->aencCmd)
		{
			dvtb_aacEncControlDebug(&ae->aencStatus);
		}

		SYS_DEBUG("Audio Encode Control => Command : %d\n", ae->aencCmd);
	}
#endif
	return retCode;
}

DvevmStRetCode
dvtb_aacEncClose(DvevmStAACEncInfo *ae)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
#if 0
	dvtb_aacEncCleanup(ae);
#endif
	return retCode;
}
