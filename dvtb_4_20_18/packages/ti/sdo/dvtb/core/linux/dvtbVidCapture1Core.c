/*
 * dvtbVidCapture1Core.c
 *
 * XDM1.0 Video Encode related Core Functions
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

#include "dvtbVidCapture1Core.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
/*********************************************************************
 *	dvtb_vidEnc1ProcessEndMessage:
 *	Description: Prints "Number of frames" processed
 ********************************************************************/
void
dvtb_vidEnc1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Total # of frames Captured & Encoded = %d \n", nFrames - 1);
		else
			SYS_OUT("Total # of frames Captured = %d \n", nFrames - 1);
	}
	else//File based
		SYS_OUT("Total # of frames Read from File & Encoded = %d \n", nFrames - 1);
}

/*********************************************************************
 *	dvtb_vidEnc1InitPtrs:
 *	Description: Initialize elements of structure DvevmStVidEnc1Info
 ********************************************************************/
void
dvtb_vidEnc1InitPtrs(DvevmStVidEnc1Info *ve)
{
	int i = 0;

	//Initialize CE handle to NULL
	ve->ceHdl = NULL;

	//Initialize codec handle to NULL
	ve->venc1Hdl = NULL;

	// Initialize numBufs of inBuf and outBufs to zero
	ve->inBuf.numBufs = 0;
	ve->outBuf.numBufs = 0;

	// Initialize buffer pointers of inBuf and outBufs to NULL
	for(i=0; i<MAX_XDM_BUFS; i++)
	{
		ve->inBuf.bufs[i] = NULL;
		ve->outBuf.bufs[i] = NULL;
	}
}

/*********************************************************************
 *	dvtb_vidEnc1InitPtrs:
 *	Description: Initialize CE and codec instance
 ********************************************************************/
DvevmStRetCode
dvtb_vidEnc1HanInit(DvevmStVidEnc1Info *ve, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		// Initialize Engine
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &ve->ceHdl))
		{
			SYS_ERROR("Cannot initialize Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}
#ifdef FOR_DEBUGGING_AT_DSP_END
		SYS_DEBUG("Engine opened. Now hit enter to debug on the DSP end.");
		getchar();
#endif

		//Initialize Codec Instance
		if (DVEVM_ST_FAIL == dvtb_vidEnc1Init(ve))
		{
			SYS_ERROR("Unable to initialize Video Encoder <%s>\n", ve->venc1Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

/*********************************************************************
 *	dvtb_vidEnc1HanClose:
 *	Description: Close CE and codec instance
 ********************************************************************/
void
dvtb_vidEnc1HanClose(DvevmStVidEnc1Info *ve, char *engName)
{
	//Close codec instance
	dvtb_vidEnc1Close(ve);
	SYS_OUT("Video Encoder <%s> closed\n", ve->venc1Name);

	//Close CE
	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&ve->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

/*********************************************************************
 *	dvtb_vidEnc1InBuffAlloc:
 *	Description: Allocate input buffers
 ********************************************************************/
DvevmStRetCode
dvtb_vidEnc1InBuffAlloc(DvevmStXdmBuffer *inBuf, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		if(DVEVM_ST_TRUE == fileBased)
		{
			//Allocate inBuf
			if (DVEVM_ST_FAIL == dvtb_allocCmem(inBuf))
			{
				SYS_ERROR("Unable to allocate memory for input buffer\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
			//Fill input buffers with zeros
			for (i = 0; i < inBuf->numBufs; i++)
				memset(inBuf->bufs[i], 0, inBuf->bufSizes[i]);
		}
		else
		{
			// Set input buffers to NULL for driver based operation
			for(i = 0; i < inBuf->numBufs; i++)
				inBuf->bufs[i] = NULL;
		}

		//Assign the buffer pointers accordingly.
		inBufDesc->numBufs = inBuf->numBufs;

		for (i = 0; i < inBufDesc->numBufs; i++)
		{
			inBufDesc->bufDesc[i].bufSize = inBuf->bufSizes[i];
			inBufDesc->bufDesc[i].buf = (XDAS_Int8 *) inBuf->bufs[i];
		}

	}while(DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

/*********************************************************************
 *	dvtb_vidEnc1OutBuffAlloc:
 *	Description: Allocate output buffers
 ********************************************************************/
DvevmStRetCode
dvtb_vidEnc1OutBuffAlloc(DvevmStXdmBuffer *outBuf, XDM_BufDesc *outBufDesc)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	//Allocate outBuf
	if (DVEVM_ST_FAIL == dvtb_allocCmem(outBuf))
	{
		SYS_ERROR("Unable to allocate memory for output buffer\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		//Assign the buffer pointers accordingly.
		outBufDesc->numBufs = outBuf->numBufs;
		outBufDesc->bufSizes = (XDAS_Int32 *) outBuf->bufSizes;
		outBufDesc->bufs = (XDAS_Int8 **) outBuf->bufs;
	}

	return retCode;
}

/*********************************************************************
 *	dvtb_vidEnc1ReadInput:
 *	Description: Get input either from driver capture or file read
 ********************************************************************/
DvevmStRetCode
dvtb_vidEnc1ReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased)
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
		{
			//Copy returned driver buffer pointer to input buffer
			inBufDesc->bufDesc[0].buf = (XDAS_Int8 *) vpfe->buffers[vpfe->buf.index].start;
			if (1 != inBufDesc->numBufs)
			{
				SYS_ERROR("Error: In providing input to codec \n");
				SYS_ERROR("Number of input buffer required by codec is > 1 \n");
				retCode = DVEVM_ST_FAIL;
			}
		}
	}
	else
	{
		for(i = 0; i < inBufDesc->numBufs; i++)
		{
			// Read input from file
			if(DVEVM_ST_FAIL == dvtb_fileRead(fp, (char *)inBufDesc->bufDesc[i].buf, inBufDesc->bufDesc[i].bufSize, &nBytes))
			{
				SYS_ERROR("Error in file read \n");
				retCode = DVEVM_ST_FAIL;
			}
		}
	}

	return retCode;
}

/*********************************************************************
 *	dvtb_vidEnc1ReadInput:
 *	Description: Encode frame
 ********************************************************************/
DvevmStRetCode
dvtb_vidEnc1EncProcess(DvevmStVidEnc1Info *ve, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		// Make video encode process call
		if (DVEVM_ST_FAIL == dvtb_vidEnc1Encode(ve, encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");

			ve->venc1Cmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_vidEnc1Control(ve))
				SYS_ERROR("Unable to get the status\n");
			else
				SYS_ERROR("Codec Error = %d\n", (int) ve->venc1Status.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

		//Get codec status after frame encode
		ve->venc1Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_vidEnc1Control(ve))
		{
			SYS_ERROR("Unable to get the status\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

	}while(DVEVM_ST_FALSE);

	return retCode;
}

