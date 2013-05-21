/*
 * dvtbImgDisplay1Core.c
 *
 * DVTB(wince) XDM1.0 Image Decode related Core Functions
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

#include "dvtbImgDisplay1Core.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"

void
dvtb_imgDec1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
	if ((DVEVM_ST_FALSE == fileBased))//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Total # of slices Decoded and Displayed = %d  \n", nFrames);
		else
			SYS_OUT("Image Displayed \n");
	}
	else//File based
		SYS_OUT("Total # of slices Decoded = %d \n", nFrames);
}

void
dvtb_imgDec1InitPtrs(DvevmStImgDec1Info *idec)
{
	int i = 0;

	idec->hTime = NULL;
	idec->ceHdl = NULL;
	idec->idec1Hdl = NULL;

	idec->inBuf.numBufs = 0;
	idec->outBuf.numBufs = 0;
	for(i=0; i<MAX_XDM_BUFS; i++)
	{
		idec->inBuf.bufs[i] = NULL;
		idec->outBuf.bufs[i] = NULL;
	}
}

DvevmStRetCode
dvtb_imgDec1HanInit(DvevmStImgDec1Info *idec, char *engName)
{

	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		// Initialize Engine
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &idec->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		//Initialize Codec Instance
		if (DVEVM_ST_FAIL == dvtb_imgDec1Init(idec))
		{
			SYS_ERROR("Unable to initialize Image Decoder <%s>\n", idec->idec1Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);// Dummy Loop

	return retCode;
}

void
dvtb_imgDec1HanClose(DvevmStImgDec1Info *idec, char *engName)
{
	dvtb_imgDec1Close(idec);
	SYS_OUT("Image Decoder <%s> closed\n", idec->idec1Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&idec->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_imgDec1DecProcess(DvevmStImgDec1Info *idec, int *decDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	idec->idec1Cmd = XDM_SETPARAMS;
	do
	{
		if (DVEVM_ST_FAIL == dvtb_imgDec1Control(idec))
		{
			SYS_ERROR("Unable to set the XDM_SETPARAMS\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_imgDec1Decode(idec, decDuration))
		{
			SYS_ERROR("Unable to decode. Content <%s> size \n", idec->idec1Name);

			idec->idec1Cmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_imgDec1Control(idec))
				SYS_ERROR("Unable to get the status\n");
			else
				SYS_ERROR("Codec Error = %d\n", (int) idec->idec1Status.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

		//This GETSTATUS gets the actual buffer
		idec->idec1Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_imgDec1Control(idec))
		{
			SYS_ERROR("Unable to get the actual buffer size using XDM_GETSTATUS.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

	}while(DVEVM_ST_FALSE);

	return retCode;
}

#if 0
DvevmStRetCode
dvtb_imgDec1ProcessOutBuff(DvevmStVpbeInfo *vpbe, FILE *fp, DvevmStXdmBuffer *outbuf, DvevmStBool fileBased, int nFrames)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_TRUE == fileBased)
	{
		for (i = 0; i < outbuf->numBufs; i++)
		{
			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(fp, (char *)outbuf->bufs[i], outbuf->bufSizes[i]))
			{
				SYS_ERROR("Error in writing to file.\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}

		if(DVEVM_ST_SUCCESS == retCode)
			SYS_OUT("Dumped Frame# %d.\n", nFrames);
	}
	else
	{
		if(DVEVM_ST_FAIL ==  dvtb_displayBuffer(vpbe, (char *)outbuf->bufs[0], outbuf->bufSizes[0]))
		{
			SYS_ERROR("Unable to display Frame# %d\n", nFrames);
			retCode = DVEVM_ST_FAIL;
		}
		else
			SYS_OUT("Displayed Frame# %d.\n", nFrames);
	}

	return retCode;
}
#else
DvevmStRetCode
dvtb_imgDec1ProcessOutBuff(FILE *fp, DvevmStXdmBuffer *outbuf, DvevmStBool fileBased, int nFrames)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_TRUE == fileBased)
	{
		for (i = 0; i < (int)outbuf->numBufs; i++)
		{
			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(fp, (char *)outbuf->bufs[i], outbuf->bufSizes[i]))
			{
				SYS_ERROR("Error in writing to file.\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}

		if(DVEVM_ST_SUCCESS == retCode)
			SYS_OUT("Dumped Frame# %d.\n", nFrames);
	}
	else
	{
	}

	return retCode;
}
#endif

