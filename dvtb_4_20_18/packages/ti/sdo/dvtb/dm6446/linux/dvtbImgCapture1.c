/*
 * dvtbImgCapture1.c
 *
 * XDM1.0 Image Encode Functionality
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

#include "dvtbImgCapture1.h"
#include "dvtbImgCapture1Core.h"
#include "dvtbImgEnc1.h"
#include "dvtbV4L2VPFE.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_ImgEnc1Capture(DvevmStThreadInfo *T)
{
	int width = 0, height = 0, encDuration = 0,	nFrames = 0,
		targetBytes = DEF_VIDFRAME_SIZE, appBufferSize = 0;

	char *targetBuff = NULL, *appBuffer = NULL;

	DvevmStXdmBuffer oldXdmBuf;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, vpfeOpened = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	/* Quit if target file is not specified */
	if (!T->targetFp)
	{
		SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	if(!T->sourceFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_ENCODE, "Image", T->useAlgorithm, fileBased);
	dvtb_imgEnc1InitPtrs(&T->g.ienc1);

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

			targetBytes = T->g.vpfe.capSize;

			// Use vpfe widthxHeight as "input width"x"input height" for Jpeg encoder
			T->g.ienc1.ienc1DynParams.inputWidth = width;
			T->g.ienc1.ienc1DynParams.inputHeight = height;

			T->g.ienc1.inBuf.numBufs = 1;
			T->g.ienc1.inBuf.bufSizes[0] = T->g.ienc1.ienc1Params.maxHeight * T->g.ienc1.ienc1Params.maxWidth * 2;

			T->g.ienc1.outBuf.numBufs = 1;
			T->g.ienc1.outBuf.bufSizes[0] = T->g.ienc1.ienc1Params.maxWidth * T->g.ienc1.ienc1Params.maxHeight * T->g.ienc1.ienc1Params.maxScans;
		}
		else
		{
			width = T->g.ienc1.ienc1DynParams.inputWidth;
			height = T->g.ienc1.ienc1DynParams.inputHeight;
		}

		/* Initialize Image Encoder if DSP is to be used */
		if (T->useAlgorithm)
		{
			if (DVEVM_ST_FAIL == dvtb_imgEnc1HanInit(&T->g.ienc1, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Image Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Image Encoder <%s> initialized\n", T->g.ienc1.ienc1Name);
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
			dvtb_copyXdmBuf(&T->g.ienc1.inBuf, &oldXdmBuf);
		}

		do
		{
			/* Start the [capture][encode] process */
			if(DVEVM_ST_FAIL == dvtb_imgEnc1ReadInput(&T->g.vpfe, T->sourceFp, &T->g.ienc1.inBuf, fileBased))
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
				memset(T->g.ienc1.outBuf.bufs[0], 0, T->g.ienc1.outBuf.bufSizes[0]);
				nFrames++;

				if(DVEVM_ST_FAIL == dvtb_imgEnc1EncProcess(&T->g.ienc1, &encDuration))
				{
					SYS_ERROR("Image encoder Process fails for slice # %d \n", nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				targetBuff = T->g.ienc1.outBuf.bufs[0];
				targetBytes = T->g.ienc1.ienc1OutArgs.bytesGenerated;

				SYS_OUT("Encoded Slice#, %d \n", nFrames);
#ifdef PERF
				SYS_PERF("Thread, %x, Slice#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, nFrames, (int) T->g.ienc1.ienc1OutArgs.bytesGenerated, encDuration);
#endif
			}
			else
			{
				memcpy(appBuffer, T->g.ienc1.inBuf.bufs[0], appBufferSize);
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
			dvtb_copyXdmBuf(&oldXdmBuf, &T->g.ienc1.inBuf);
		}
	} while (DVEVM_ST_FALSE);

	dvtb_imgEnc1ProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

	/* Uninitialize and close */
	if (T->useAlgorithm)
	{
		dvtb_imgEnc1HanClose(&T->g.ienc1, T->g.eng.name);
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

	dvtb_exitMessage(DVEVM_ST_ENCODE, "Image", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();

}
