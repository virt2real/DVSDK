/*
 * dvtbVidCapture1.c
 *
 * XDM1.0 Video Encode Functionality
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

#include "dvtbVidCapture1.h"
#include "dvtbVidCapture1Core.h"
#include "dvtbVidEnc1.h"
#include "dvtbV4L2VPFE.h"
#include "dvtbMemory.h"
#include "dvtbVdce.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_vidEnc1ConvertInputToFrame(DvevmStXdmBuffer *pubInYUV, IVIDEO1_BufDescIn *inBufDesc)
{
	unsigned short j = 0, k = 0;
	unsigned int width = 0, height = 0;
	char *pubSrcY = NULL, *pubSrcU = NULL, *pubSrcV = NULL, *pubDst = NULL;

	// Convert Luminance Data
	width = inBufDesc->frameWidth;
	height = inBufDesc->frameHeight;
	pubDst = (char *)inBufDesc->bufDesc[0].buf;

	for (j = 0; j < height; j++)
	{
		pubSrcY = (char *)(pubInYUV->bufs[0] + (j * width));

		memcpy(pubDst, pubSrcY, width);

		// Update the destination pointer
		pubDst += width;
	}

	// Convert Chrominance Data
	height >>= 1;
	width >>= 1;

	pubDst = (char *)inBufDesc->bufDesc[1].buf;

	for (j = 0; j < height; j++)
	{
		pubSrcU = (char *)(pubInYUV->bufs[1] + (j * width));
		pubSrcV = (char *)(pubInYUV->bufs[2] + (j * width));

		for (k = 0; k < width; k++)
		{
			*pubDst++ = *pubSrcU++;
			*pubDst++ = *pubSrcV++;
		}
	}
}

DvevmStRetCode
dvtb_vidEnc1ConvertFormat(DvevmStThreadInfo *T, DvevmStXdmBuffer *pubInYUVBuff, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_TRUE == fileBased)
	{
		dvtb_vidEnc1ConvertInputToFrame(pubInYUVBuff, inBufDesc);
	}
	else
	{
		T->g.capvdce.inputBuffer = T->g.vpfe.buffers[T->g.vpfe.buf.index].start;
		T->g.capvdce.outputBuffer = T->g.vpfe.buffers[T->g.vpfe.buf.index].start;

		if (DVEVM_ST_FAIL == dvtb_vdceConvert422to420(&T->g.capvdce))
		{
			SYS_ERROR("Chrominance Conversion (420 to 422) Failed\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			inBufDesc->bufDesc[0].buf = (XDAS_Int8 *) T->g.capvdce.outputBuffer;
			inBufDesc->bufDesc[1].buf = (XDAS_Int8 *) &(T->g.capvdce.outputBuffer[T->g.vpfe.capWidth * T->g.vpfe.capHeight]);
		}
	}

	return retCode;
}

void
dvtb_VidEnc1Capture(DvevmStThreadInfo *T)
{
	int i = 0, maxFrames = 0, nFrames = 1, targetBytes = DEF_VIDFRAME_SIZE, width = 0, height = 0,
		encDuration = 0;

	char *targetBuff = NULL;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, vpfeOpened = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;
	IVIDEO1_BufDescIn pubInYUVBufDesc;
	DvevmStXdmBuffer pubInYUVBuff;

	maxFrames = T->g.venc1.numFrames;

	/* Quit if target file is not specified */
	if (!T->targetFp)
	{
		SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit( );
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

	dvtb_startMessage(DVEVM_ST_ENCODE, "Video", T->useAlgorithm, fileBased);
	dvtb_vidEnc1InitPtrs(&T->g.venc1);

	//pubInYUVBuff: Initialize
	pubInYUVBuff.numBufs = 0;
	for(i=0; i<MAX_XDM_BUFS; i++)
		pubInYUVBuff.bufs[i] = NULL;

	/* Dummy loop to enable easy cleanup */
	do
	{
		/* If source file is not defined, initialize VPFE
		 * Else initialize the YUV source file to be encoded */
		if (DVEVM_ST_FALSE == fileBased)
		{
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

			if(DVEVM_ST_FAIL == dvtb_vdceSetup(&T->g.capvdce, T->g.vpfe.capHeight, T->g.vpfe.capWidth, T->g.vpfe.capWidth, 2))
			{
				SYS_ERROR("Unable to setup VDCE device \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("VDCE device  <%s> initialized \n", T->g.capvdce.device);
		}

		width = T->g.venc1.venc1DynParams.inputWidth;
		height = T->g.venc1.venc1DynParams.inputHeight;

		if (DVEVM_ST_FAIL == dvtb_vidEnc1HanInit(&T->g.venc1, (char *)T->g.eng.name))
		{
			SYS_ERROR("Unable to initialize Video Encoder Handle \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		T->g.venc1.inBufDesc.frameWidth =  T->g.venc1.venc1DynParams.inputWidth;
		T->g.venc1.inBufDesc.frameHeight = T->g.venc1.venc1DynParams.inputHeight;
		// Allocate memory for codec input buffers
		if (DVEVM_ST_FAIL == dvtb_vidEnc1InBuffAlloc(&T->g.venc1.inBuf, &T->g.venc1.inBufDesc, fileBased))
		{
			SYS_ERROR("Error in allocating memory for input buffer\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_vidEnc1OutBuffAlloc(&T->g.venc1.outBuf, &T->g.venc1.outBufDesc))
		{
			SYS_ERROR("Error in allocating memory for output buffer\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}


		if (DVEVM_ST_TRUE == fileBased)
		{
			// Allocate memory & Update pubInYUVBuff and pubInYUVBufDesc for "File Read"
			pubInYUVBuff.numBufs = 3;
			pubInYUVBuff.bufSizes[0] = width * height;
			pubInYUVBuff.bufSizes[1] = width * height / 4;
			pubInYUVBuff.bufSizes[2] = width * height / 4;

			if (DVEVM_ST_FAIL == dvtb_vidEnc1InBuffAlloc(&pubInYUVBuff, &pubInYUVBufDesc, DVEVM_ST_TRUE))
			{
				SYS_ERROR("Cannot allocate memory for file read\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
		else
		{
			// Update pubInYUVBufDesc for "capture from driver"
			pubInYUVBufDesc.numBufs = 1;
		}

		/* Start the [capture][encode] process */
		while (nFrames <= maxFrames)
		{
			if(DVEVM_ST_FAIL == dvtb_vidEnc1ReadInput(&T->g.vpfe, T->sourceFp, &pubInYUVBufDesc, fileBased))
			{
				SYS_ERROR("Error in Read Input \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_TRUE == fileBased)
			{
				if (feof(T->sourceFp))
				{
					SYS_OUT("End of source file reached. Exiting ...\n");
					break;
				}
			}

			if(DVEVM_ST_FAIL == dvtb_vidEnc1ConvertFormat(T, &pubInYUVBuff, &T->g.venc1.inBufDesc, fileBased))
			{
				SYS_ERROR("Failed to change the input format \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}


			if(DVEVM_ST_FAIL == dvtb_vidEnc1EncProcess(&T->g.venc1, &encDuration))
			{
				SYS_ERROR("video encoder Process fails for frame # %d \n", nFrames);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			targetBuff = (char *) T->g.venc1.outBufDesc.bufs[0];
			targetBytes = T->g.venc1.venc1OutArgs.bytesGenerated;

			if (T->g.venc1.venc1OutArgs.inputFrameSkip)
				SYS_ERROR("Frame <%d> Skipped\n", nFrames);
			else
				SYS_OUT("Encoded Frame %d.\n", nFrames);

#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Frame Type, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, nFrames, (int) T->g.venc1.venc1OutArgs.encodedFrameType, targetBytes, encDuration);
#endif

			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)targetBuff, targetBytes))
			{
				SYS_ERROR("Error in writing to file.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_FALSE == fileBased)
				dvtb_vpfeReturnBuffer(&T->g.vpfe);

			nFrames++;
		}
	} while (DVEVM_ST_FALSE);

	dvtb_vidEnc1ProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

	if (pubInYUVBuff.numBufs > 0)
	{
		dvtb_freeCmem(&pubInYUVBuff);
	}

	dvtb_vidEnc1HanClose(&T->g.venc1, T->g.eng.name);

	if (DVEVM_ST_TRUE == vpfeOpened)
	{
		dvtb_vpfeClose(&T->g.vpfe);
		SYS_OUT("VPFE Device <%s> closed\n", T->g.vpfe.device);
	}

	if (DVEVM_ST_TRUE == T->g.capvdce.vdceOpened)
	{
		dvtb_vdceClose(&T->g.capvdce);
		SYS_OUT("VDCE Device <%s> closed\n",T->g.capvdce.device);
	}

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "Video", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit( );
}
