/*
 * dvtbJPEGCapture1.c
 *
 * XDM1.0 JPEG Encode Functionality
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

#include "dvtbJPEGCapture1.h"
#include "dvtbJPEGEnc1.h"
#include "dvtbV4L2VPFE.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_jpegEnc1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
	if (DVEVM_ST_FALSE == fileBased) //Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Total # of Slices Encoded = %d \n", nFrames);
		else
			SYS_OUT("Image Captured \n");
	}
	else
		// File based
		SYS_OUT("Total # of Slices Encoded = %d \n", nFrames);
}

void
dvtb_jpegEnc1InitPtrs(DvevmStJpegEnc1Info *ienc)
{
	int i = 0;

	ienc->ceHdl = NULL;
	ienc->ienc1Hdl = NULL;

	ienc->inBuf.numBufs = 0;
	ienc->outBuf.numBufs = 0;
	for (i = 0; i < MAX_XDM_BUFS; i++)
	{
		ienc->inBuf.bufs[i] = NULL;
		ienc->outBuf.bufs[i] = NULL;
	}
}

DvevmStRetCode
dvtb_jpegEnc1HanInit(DvevmStJpegEnc1Info *ienc, char *engName)
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
		if (DVEVM_ST_FAIL == dvtb_jpegEnc1Init(ienc))
		{
			SYS_ERROR("Unable to initialize Jpeg Encoder <%s>\n", ienc->ienc1Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	} while (DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

void
dvtb_jpegEnc1HanClose(DvevmStJpegEnc1Info *ienc, char *engName)
{
	dvtb_jpegEnc1Close(ienc);
	SYS_OUT("Jpeg Encoder <%s> closed\n", ienc->ienc1Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&ienc->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_jpegEnc1EncProcess(DvevmStJpegEnc1Info *ienc, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		ienc->ienc1Cmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_jpegEnc1Control(ienc))
		{
			SYS_ERROR("Unable to set the Dynamic params\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_jpegEnc1Encode(ienc, encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");
			ienc->ienc1Cmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_jpegEnc1Control(ienc))
				SYS_ERROR("Unable to get the status\n");
			else
				SYS_ERROR("Codec Error = %d\n", (int) ienc->ienc1Status.status.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

		SYS_DEBUG("numAU(Dyaminc params) = %d, currentAU(Outargs) = %d, TotalAU(Status) = %d\n", (int) ienc->ienc1DynParams.params.numAU, (int) ienc->ienc1OutArgs.outArgs.currentAU, (int) ienc->ienc1Status.status.totalAU);

		ienc->ienc1Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_jpegEnc1Control(ienc))
		{
			SYS_ERROR("Unable to get the status\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	} while (DVEVM_ST_FALSE);

	return retCode;

}

DvevmStRetCode
dvtb_jpegEnc1ReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, DvevmStXdmBuffer *inBuf, int fileBased)
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
		else if (VID_FMT_YUV420SP == vpfe->capFmt)
		{
			inBuf->bufs[0] = (char *) vpfe->buffers[vpfe->buf.index].start;
			inBuf->bufs[1] = (char *) vpfe->buffers[vpfe->buf.index].start + (vpfe->capWidth * vpfe->capHeight);
		}
		else if (VID_FMT_UYVY == vpfe->capFmt)
		{
			inBuf->bufs[0] = (char *) vpfe->buffers[vpfe->buf.index].start;
		}
		else
		{
			SYS_ERROR("Un-supported capture format selected!\n");
			retCode = DVEVM_ST_FAIL;
		}
	}
	else
	{
		for (i = 0; i < inBuf->numBufs; i++)
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


void
dvtb_JpegEnc1Capture(DvevmStThreadInfo *T)
{
	int width = 0, height = 0, encDuration = 0,	nFrames = 0, targetBytes = DEF_VIDFRAME_SIZE,
		appBufferSize = 0;

	char *targetBuff = NULL, *appBuffer = NULL;

	DvevmStXdmBuffer oldXdmBuf;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, vpfeOpened = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	/* Quit if target file is not specified */
	if (!T->targetFp)
	{
		SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit( );
	}

	if(!T->sourceFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_ENCODE, "JPEG", T->useAlgorithm, fileBased);
	dvtb_jpegEnc1InitPtrs(&T->g.jpegenc1);

	/* Dummy loop to enable easy cleanup */
	do
	{
		/* If source file is not defined, initialize VPFE
		 * Else initialize the YUV source file to be encoded */
		if (DVEVM_ST_FALSE == fileBased)
		{
			width = T->g.vpfe.capWidth;
			height = T->g.vpfe.capHeight;
			if (DVEVM_ST_FAIL == dvtb_vpfeSetup(&T->g.vpfe))
			{
				SYS_ERROR("Unable to initialize VPFE device <%s>\n", T->g.vpfe.device);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			if (DVEVM_ST_FAIL == dvtb_vpfeCaptureStart(&T->g.vpfe))
			{
				SYS_ERROR("Unable to start VPFE device <%s>\n", T->g.vpfe.device);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			vpfeOpened = DVEVM_ST_TRUE;
			SYS_OUT("VPFE device <%s> initialized for capture\n", T->g.vpfe.device);
		}
		else
		{
			width = T->g.jpegenc1.ienc1DynParams.params.inputWidth;
			height = T->g.jpegenc1.ienc1DynParams.params.inputHeight;
		}

		/* Initialize Image Encoder if DSP is to be used */
		if (T->useAlgorithm)
		{
			if (DVEVM_ST_FAIL == dvtb_jpegEnc1HanInit(&T->g.jpegenc1, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Jpeg Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Jpeg Encoder <%s> initialized\n", T->g.jpegenc1.ienc1Name);

		}
		else
		{
			appBufferSize = T->g.vpfe.capWidth * T->g.vpfe.capHeight * 2;
			if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&appBuffer, appBufferSize))
			{
				SYS_ERROR("Unable to allocate memory for appBuffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}

		/* Take a backup of allocated XDM buffer if VPFE is to be used */
		if ((DVEVM_ST_FALSE == fileBased) && T->useAlgorithm)
		{
			dvtb_copyXdmBuf(&T->g.jpegenc1.inBuf, &oldXdmBuf);
		}

		do
		{
			
			/* Start the [capture][encode] process */
			if(DVEVM_ST_FAIL == dvtb_jpegEnc1ReadInput(&T->g.vpfe, T->sourceFp, &T->g.jpegenc1.inBuf, fileBased))
			{
				SYS_ERROR("Error in Read Input \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if(DVEVM_ST_TRUE == fileBased)
			{
				if (feof(T->sourceFp))
				{
					SYS_OUT("End of source file reached. Exiting ...\n");
					break;
				}
			}

			if (T->useAlgorithm)
			{
				memset(T->g.jpegenc1.outBuf.bufs[0], 0, T->g.jpegenc1.outBuf.bufSizes[0]);
				nFrames++;

				if(DVEVM_ST_FAIL == dvtb_jpegEnc1EncProcess(&T->g.jpegenc1, &encDuration))
				{
					SYS_ERROR("Image encoder Process fails for slice # %d \n", nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				targetBuff = T->g.jpegenc1.outBuf.bufs[0];
				targetBytes = T->g.jpegenc1.ienc1OutArgs.outArgs.bytesGenerated;

				SYS_OUT("Encoded Slice#, %d \n", nFrames);
#ifdef PERF
				SYS_PERF("Thread, %x, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, (int) T->g.jpegenc1.ienc1OutArgs.outArgs.bytesGenerated, encDuration);
#endif
				if(XDM_GENERATE_HEADER != T->g.jpegenc1.ienc1DynParams.params.generateHeader)	
				{
					while (T->g.jpegenc1.ienc1OutArgs.outArgs.currentAU < T->g.jpegenc1.ienc1Status.status.totalAU)
					{
						/* Store the processed frame to target file */
						if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)targetBuff, targetBytes))
						{
							SYS_ERROR("Error in writing to file.\n");
							usecaseFailed = DVEVM_ST_TRUE;
							break;
						}
	
						nFrames++;
						if (DVEVM_ST_FAIL == dvtb_jpegEnc1EncProcess(&T->g.jpegenc1, &encDuration))
						{
							SYS_ERROR("Jpeg encoder Process fails for slice # %d \n", nFrames);
							usecaseFailed = DVEVM_ST_TRUE;
							break;
						}
						targetBuff = T->g.jpegenc1.outBuf.bufs[0];
						targetBytes = T->g.jpegenc1.ienc1OutArgs.outArgs.bytesGenerated;
						SYS_OUT("Encoded Slice#, %d \n", nFrames);
#ifdef PERF
                                	SYS_PERF("Thread, %x, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, (int) T->g.jpegenc1.ienc1OutArgs.outArgs.bytesGenerated, encDuration);
#endif
					}
				}
				
				
			}
			else
			{
				memcpy(appBuffer, T->g.jpegenc1.inBuf.bufs[0], appBufferSize);
				targetBuff = appBuffer;
				targetBytes = appBufferSize;
				SYS_OUT("Captured Frame.\n");
			}

			if (DVEVM_ST_FALSE == fileBased)
				dvtb_vpfeReturnBuffer(&T->g.vpfe);

			/* Store the processed frame to target file */
			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)targetBuff, targetBytes))
			{
				SYS_ERROR("Error in writing to file.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		} while (DVEVM_ST_FALSE);
		
		/* Restore the backed-up XDM buffer */
		if ((DVEVM_ST_FALSE == fileBased) && T->useAlgorithm)
		{
			dvtb_copyXdmBuf(&oldXdmBuf, &T->g.jpegenc1.inBuf);
		}

	} while (DVEVM_ST_FALSE);

	
	dvtb_jpegEnc1ProcessEndMessage(T->useAlgorithm, fileBased, nFrames);
	
	/* Uninitialize and close */
	if (T->useAlgorithm)
	{
		dvtb_jpegEnc1HanClose(&T->g.jpegenc1, T->g.eng.name);
	}
	else
	{
		if(NULL != appBuffer)
			dvtb_freeSingleBufCmem(appBuffer, appBufferSize);
	}

	if(DVEVM_ST_TRUE == vpfeOpened)
	{
		dvtb_vpfeClose(&T->g.vpfe);
		SYS_OUT("VPFE Device <%s> closed\n", T->g.vpbe.device);
	}

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "JPEG", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit( );

}
