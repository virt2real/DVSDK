/*
 * dvtbImgCapture.c
 *
 * XDM0.9 Image Encode Functionality
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

#include "dvtbImgCapture.h"
#include "dvtbImgEnc.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_imgEncProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
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
dvtb_imgEncInitPtrs(DvevmStImgEncInfo *ienc)
{
	int i = 0;

	ienc->ceHdl = NULL;
	ienc->iencHdl = NULL;

	ienc->inBuf.numBufs = 0;
	ienc->outBuf.numBufs = 0;
	for(i=0; i<MAX_XDM_BUFS; i++)
	{
		ienc->inBuf.bufs[i] = NULL;
		ienc->outBuf.bufs[i] = NULL;
	}
}

DvevmStRetCode
dvtb_imgEncHanInit(DvevmStImgEncInfo *ienc, char *engName)
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
		if (DVEVM_ST_FAIL == dvtb_imgEncInit(ienc))
		{
			SYS_ERROR("Unable to initialize Image Encoder <%s>\n", ienc->iencName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

	}while(DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

void
dvtb_imgEncHanClose(DvevmStImgEncInfo *ienc, char *engName)
{
	dvtb_imgEncClose(ienc);
	SYS_OUT("Image Encoder <%s> closed\n", ienc->iencName);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&ienc->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);

}

DvevmStRetCode
dvtb_imgEncEncProcess(DvevmStImgEncInfo *ienc, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_imgEncEncode(ienc, encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");

			ienc->iencCmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_imgEncControl(ienc))
				SYS_ERROR("Unable to get the status\n");
			else
				SYS_ERROR("Codec Error = %d\n", (int) ienc->iencStatus.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

		SYS_DEBUG("numAU(Dyaminc params) = %d, currentAU(Outargs) = %d, TotalAU(Status) = %d\n", (int) ienc->iencDynParams.numAU, (int) ienc->iencOutArgs.currentAU, (int) ienc->iencStatus.totalAU);

		ienc->iencCmd = XDM_GETSTATUS;

		if (DVEVM_ST_FAIL == dvtb_imgEncControl(ienc))
		{
			SYS_ERROR("Unable to get the status\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_imgEncReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, DvevmStXdmBuffer *inBuf, int fileBased)
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


void
dvtb_ImgEncCapture(DvevmStThreadInfo *T)
{
	int targetBytes = DEF_VIDFRAME_SIZE, width = 0, height = 0, nFrames = 0, encDuration = 0;
	char *targetBuff = NULL;
	unsigned int ipFileLength = 0;

	DvevmStXdmBuffer oldXdmBuf;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, vpfeOpened = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	SYS_DEBUG("Image Encoder [capture][encode] called with %s option\n", (T->useAlgorithm) ? "USE DSP" : "NO DSP");

	/* Quit if target file is not specified */
	if (!T->targetFp)
	{
		SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	if(!T->useAlgorithm)
	{
		SYS_ERROR("No DSP option is not supported \n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	if(!T->sourceFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_ENCODE, "Image", T->useAlgorithm, fileBased);
	dvtb_imgEncInitPtrs(&T->g.ienc);


	/* Dummy loop to enable easy cleanup */
	do
	{
		if (DVEVM_ST_TRUE == fileBased)
		{
			if(DVEVM_ST_FAIL == dvtb_getFileSize(T->sourceFp, &ipFileLength))
			{
				SYS_ERROR("Unable to Get File Size \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}

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

			targetBytes = T->g.vpfe.capSize;
			T->g.ienc.iencDynParams.inputWidth = width;
			T->g.ienc.iencDynParams.inputHeight = height;

			T->g.ienc.inBuf.numBufs = 1;
			T->g.ienc.inBuf.bufSizes[0] = T->g.ienc.iencParams.maxHeight * T->g.ienc.iencParams.maxWidth * 2;

			T->g.ienc.outBuf.numBufs = 1;
			T->g.ienc.outBuf.bufSizes[0] = T->g.ienc.iencParams.maxWidth * T->g.ienc.iencParams.maxHeight * T->g.ienc.iencParams.maxScans;
		}
		else
		{
			width = T->g.ienc.iencDynParams.inputWidth;
			height = T->g.ienc.iencDynParams.inputHeight;
		}

		/* Initialize Image Encoder if DSP is to be used */
		if (T->useAlgorithm)
		{
			if (DVEVM_ST_FAIL == dvtb_imgEncHanInit(&T->g.ienc, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Image Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			SYS_OUT("Image Encoder <%s> initialized\n", T->g.ienc.iencName);
		}

		/* Take a backup of allocated XDM buffer if VPFE is to be used */
		if ((DVEVM_ST_FALSE == fileBased) && T->useAlgorithm)
			dvtb_copyXdmBuf(&T->g.ienc.inBuf, &oldXdmBuf);

		/* Start the [capture][encode] process */
		if(DVEVM_ST_FAIL == dvtb_imgEncReadInput(&T->g.vpfe, T->sourceFp, &T->g.ienc.inBuf, fileBased))
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
			memset(T->g.ienc.outBuf.bufs[0], 0, T->g.ienc.outBuf.bufSizes[0]);
			nFrames++;

			if(DVEVM_ST_FAIL == dvtb_imgEncEncProcess(&T->g.ienc, &encDuration))
			{
				SYS_ERROR("Image encoder Process fails for slice # %d \n", nFrames);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			targetBuff = T->g.ienc.outBuf.bufs[0];
			targetBytes = T->g.ienc.iencOutArgs.bytesGenerated;
			SYS_OUT("Encoded Slice#, %d \n", nFrames);
#ifdef PERF
			SYS_PERF("Thread, %x, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, (int) T->g.ienc.iencOutArgs.bytesGenerated, encDuration);
#endif
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

		/* Restore the backed-up XDM buffer */
		if ((DVEVM_ST_FALSE == fileBased) && T->useAlgorithm)
			dvtb_copyXdmBuf(&oldXdmBuf, &T->g.ienc.inBuf);

	} while (DVEVM_ST_FALSE);


	/* Uninitialize and close */
	dvtb_imgEncProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

	if (T->useAlgorithm)
		dvtb_imgEncHanClose(&T->g.ienc, T->g.eng.name);

	if(DVEVM_ST_TRUE == vpfeOpened)
	{
		dvtb_vpfeClose(&T->g.vpfe);
		SYS_OUT("VPFE Device <%s> closed\n", T->g.vpbe.device);
	}

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "Image", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
