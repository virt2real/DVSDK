/*
 * dvtbDeInterlace.c 
 *
 * DeInterlacer implementation
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

#include "dvtbDeInterlace.h"
#include "dvtbMemory.h"

void
dvtb_deInterCleanup(DvevmStDeInterInfo *deinter)
{
	if (NULL != deinter->deinterHdl)
	{
		UNIVERSAL_delete(deinter->deinterHdl);
		deinter->deinterHdl = NULL;
	}
}

DvevmStRetCode
dvtb_deInterInit(DvevmStDeInterInfo *deinter)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(deinter != NULL);
	ASSERT(deinter->ceHdl != NULL);
	ASSERT(deinter->deinterName[0] != 0);


	
	if (NULL == (deinter->deinterHdl = UNIVERSAL_create(deinter->ceHdl, deinter->deinterName, (UNIVERSAL_Params *)&deinter->deinterParams)))
	{
		SYS_ERROR("Unable to initialize DeInterlacer\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{

		deinter->deinterInArgs.inObject.width  = deinter->deinterInWidth;
		deinter->deinterInArgs.inObject.height = deinter->deinterInHeight;
		deinter->deinterInArgs.inObject.pitch_cur_frame = (deinter->deinterInWidth << 1);
		deinter->deinterInArgs.inObject.pitch_cur_frame = (deinter->deinterInWidth << 1);
		deinter->deinterInArgs.inObject.pitch_out_frame = (deinter->deinterInWidth << 1);

		if(XDM_YUV_422ILE == deinter->deinterInputFormat)
		{
			deinter->deinterInArgs.inObject.imageFormat = II2P_FOUR22_ILE; // II2P_FOUR22_ILE =1
			deinter->outBuf.numBufs = 1;
			deinter->outBuf.bufSizes[0] = deinter->deinterInWidth * deinter->deinterInHeight * 2;
			if(DVEVM_ST_FAIL == dvtb_allocCmem(&deinter->outBuf))
			{
				SYS_ERROR("Unable to allocate out buffer for DeInterlacer \n");
				retCode = DVEVM_ST_FAIL;
			}
		}
		else
		{
			SYS_ERROR("Chroma format %d not supported \n",deinter->deinterInputFormat);
			retCode = DVEVM_ST_FAIL;
		}				
	}

	if (DVEVM_ST_FAIL == retCode)
		dvtb_deInterCleanup(deinter);

	return retCode;
}

DvevmStRetCode
dvtb_deInterEncode(DvevmStDeInterInfo *deinter, int* encDuration)
{
	XDAS_Int32 status = -1;
	int i = 0;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
        XDM1_BufDesc inBufDesc;
        XDM1_BufDesc outBufDesc;

	ASSERT(deinter != NULL);
	ASSERT(deinter->ceHdl != NULL);
	ASSERT(deinter->deinterHdl != NULL);
	ASSERT(deinter->inBuf.numBufs > 0);
	ASSERT(deinter->inBuf.numBufs > 0);
	
	outBufDesc.numBufs = deinter->outBuf.numBufs;
	for(i = 0 ; i < outBufDesc.numBufs; i++)
	{
		outBufDesc.descs[i].bufSize = deinter->outBuf.bufSizes[i];
		outBufDesc.descs[i].buf	= (XDAS_Int8 *)deinter->outBuf.bufs[i];
	}

	inBufDesc.numBufs = deinter->inBuf.numBufs;
	for(i = 0 ; i < inBufDesc.numBufs; i++)
	{
		inBufDesc.descs[i].bufSize = deinter->inBuf.bufSizes[i];
		inBufDesc.descs[i].buf     = (XDAS_Int8 *) deinter->inBuf.bufs[i];
	}

	timeStmpBfrEnc = dvtb_getTime();
	
	status = UNIVERSAL_process(deinter->deinterHdl, &inBufDesc, &outBufDesc, NULL, (UNIVERSAL_InArgs *)&deinter->deinterInArgs, (UNIVERSAL_OutArgs *)&deinter->deinterOutArgs);

	timeStmpAftrEnc = dvtb_getTime();

	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != UNIVERSAL_EOK )
	{
		SYS_ERROR("DeInterlacer Process failed (%d)\n", (int) status);
		retCode = DVEVM_ST_FAIL;
	}


	return retCode;
}

DvevmStRetCode
dvtb_deInterControl(DvevmStDeInterInfo *deinter)
{
	int status = -1;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	ASSERT(deinter != NULL);
	ASSERT(deinter->ceHdl != NULL);

	deinter->deinterStatus.size		= sizeof(UNIVERSAL_Status); 	
	deinter->deinterStatus.data.numBufs     = 0;
	status = UNIVERSAL_control(deinter->deinterHdl, deinter->deinterCmd,&deinter->deinterDynParams,&deinter->deinterStatus);
	if (UNIVERSAL_EOK != status)
	{
		SYS_ERROR("Error (%d), Codec Error (%d) in Video Encoder Control\n", status, (int) deinter->deinterStatus.extendedError);
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStRetCode
dvtb_deInterClose(DvevmStDeInterInfo *deinter)
{
	if (deinter->outBuf.numBufs > 0)
	{
		dvtb_freeCmem(&deinter->outBuf);
	}

	dvtb_deInterCleanup(deinter);

	return DVEVM_ST_SUCCESS;
}

