/*
 * dvtbImgCapture1Core.c
 *
 * DVTB(wince) XDM1.0 Image Encode related Core Functions
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

#include "dvtbImgCapture1Core.h"
#include "dvtbImgEnc1.h"
#include "dvtbUtils.h"

void
dvtb_imgEnc1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
	if (DVEVM_ST_FALSE == fileBased) //Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Total # of Slices Encoded = %d \n", nFrames);
		else
			SYS_OUT("Image Captured \n");
	}
	else // File based
		SYS_OUT("Total # of Slices Encoded = %d \n", nFrames);
}

void
dvtb_imgEnc1InitPtrs(DvevmStImgEnc1Info *ienc)
{
	int i = 0;

	ienc->hTime = NULL;
	ienc->ceHdl = NULL;
	ienc->ienc1Hdl = NULL;

	ienc->inBuf.numBufs = 0;
	ienc->outBuf.numBufs = 0;
	for(i=0; i<MAX_XDM_BUFS; i++)
	{
		ienc->inBuf.bufs[i] = NULL;
		ienc->outBuf.bufs[i] = NULL;
	}
}

DvevmStRetCode
dvtb_imgEnc1HanInit(DvevmStImgEnc1Info *ienc, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		// Initialize Engine
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &ienc->ceHdl))
		{
			SYS_ERROR("Cannot initialize Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		//Initialize Codec Instance
		if (DVEVM_ST_FAIL == dvtb_imgEnc1Init(ienc))
		{
			SYS_ERROR("Unable to initialize Image Encoder <%s>\n", ienc->ienc1Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}

	}while(DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

void
dvtb_imgEnc1HanClose(DvevmStImgEnc1Info *ienc, char *engName)
{
	dvtb_imgEnc1Close(ienc);
	SYS_OUT("Image Encoder <%s> closed\n", ienc->ienc1Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&ienc->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);

}

DvevmStRetCode
dvtb_imgEnc1EncProcess(DvevmStImgEnc1Info *ienc, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_imgEnc1Encode(ienc, encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");

			ienc->ienc1Cmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_imgEnc1Control(ienc))
				SYS_ERROR("Unable to get the status\n");
			else
				SYS_ERROR("Codec Error = %d\n", (int) ienc->ienc1Status.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

		SYS_DEBUG("numAU(Dyaminc params) = %d, currentAU(Outargs) = %d, TotalAU(Status) = %d\n", (int) ienc->ienc1DynParams.numAU, (int) ienc->ienc1OutArgs.currentAU, (int) ienc->ienc1Status.totalAU);

		ienc->ienc1Cmd = XDM_GETSTATUS;

		if (DVEVM_ST_FAIL == dvtb_imgEnc1Control(ienc))
		{
			SYS_ERROR("Unable to get the status\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;

}

#ifndef VPFENOTSUPPORTED
DvevmStRetCode
dvtb_imgEnc1ReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, DvevmStXdmBuffer *inBuf, int fileBased)
{
	int i = 0, nBytes = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_FALSE == fileBased)
	{
		// Get YUV from driver
		if (dvtb_vpfeGetNextBuffer(vpfe) < 0)
		{
			SYS_ERROR("Error while reading video input\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
			inBuf->bufs[0] = (char *)vpfe->buffers[vpfe->buf.index].start;
	}
	else
	{
		for(i=0; i < inBuf->numBufs; i++)
		{
			if(DVEVM_ST_FAIL == dvtb_fileRead(fp, (char *)inBuf->bufs[i], inBuf->bufSizes[i], &nBytes))
			{
				SYS_ERROR("Error in file read \n");
				retCode = DVEVM_ST_FAIL;
			}
		}

	}

	return retCode;
}
#endif

