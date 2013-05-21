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
#include "dvtbDM365Utils.h"

void
dvtb_jpegEnc1StartMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased)
{
	if (DVEVM_ST_FALSE == fileBased)
	{
		if (useAlgorithm)
			SYS_OUT("JPEG [capture]+[encode] usecase started\n");
		else
			SYS_OUT("JPEG [capture] usecase started\n");
	}
	else
		SYS_OUT("JPEG [File Read]+[encode] usecase started\n");
}

void
dvtb_jpegEnc1ExitMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, DvevmStBool usecaseFailed)
{
	if (DVEVM_ST_TRUE == fileBased)//File based
	{
		if (DVEVM_ST_FALSE == usecaseFailed)
			SYS_OUT("JPEG [File Read]+[Encode] usecase completed successfully.\n");
		else
			SYS_OUT("JPEG [File Read]+[Encode] usecase completed with errors.\n");
	}
	else //Driver based
	{
		if (useAlgorithm)
		{
			if (DVEVM_ST_FALSE == usecaseFailed)
				SYS_OUT("JPEG [Capture]+[Encode] usecase completed successfully.\n");
			else
				SYS_OUT("JPEG [Capture]+[Encode] usecase completed with errors.\n");
		}
		else
		{
			if (DVEVM_ST_FALSE == usecaseFailed)
				SYS_OUT("JPEG [Capture] usecase completed successfully.\n");
			else
				SYS_OUT("JPEG [Capture] usecase completed with errors.\n");
		}
	}
}

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
				SYS_ERROR("Codec Error = %d\n", (int) ienc->ienc1Status.imgencStatus.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

		SYS_DEBUG("numAU(Dyaminc params) = %d, currentAU(Outargs) = %d, TotalAU(Status) = %d\n", (int) ienc->ienc1DynParams.imgencDynamicParams.numAU, (int) ienc->ienc1OutArgs.imgencOutArgs.currentAU, (int) ienc->ienc1Status.imgencStatus.totalAU);

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
	int targetBytes = DEF_VIDFRAME_SIZE, width = 0, height = 0, numAU = 0, encDuration = 0, nSlices = 0, sliceMode = 0, appBufferSize = 0, sliceWidth = 0, sliceHeight = 0, inputHeight = 0, captureWidth = 0, inputWidth = 0, forceChromaFormat = 0, inputChromaFormat = 0;

	char *targetBuff = NULL, *orgPictureY = NULL, *orgPictureCb = NULL, *orgPictureCr = NULL, *appBuffer = NULL;

	DvevmStXdmBuffer oldXdmBuf;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, vpfeOpened = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	/* Quit if target file is not specified */
	if (NULL == T->targetFp)
	{
		SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
		dvtb_freeThr(T);
		pthread_exit(NULL);
	}

	if (!T->sourceFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_jpegEnc1StartMessage(T->useAlgorithm, fileBased);
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
			if (DVEVM_ST_FAIL == dvtb_captureSetup(&T->g.vpfe, &T->g.vpPrvw, &T->g.vpRsz))
			{
				SYS_ERROR("Unable to initialize Video Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			vpfeOpened = DVEVM_ST_TRUE;
			SYS_OUT("VPFE device <%s> initialized for capture\n", T->g.vpfe.device);
		}
		else
		{
			width = T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.inputWidth;
			height = T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.inputHeight;
		}

		/* Initialize Jpeg Encoder if DSP is to be used */
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

		/* Start the [capture][encode] process */
		if (DVEVM_ST_FAIL == dvtb_jpegEnc1ReadInput(&T->g.vpfe, T->sourceFp, &T->g.jpegenc1.inBuf, fileBased))
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

		if (T->useAlgorithm)
		{
			//Store Y Cb Cr pointers
			orgPictureY = T->g.jpegenc1.inBuf.bufs[0];
			orgPictureCb = T->g.jpegenc1.inBuf.bufs[1];
			orgPictureCr = T->g.jpegenc1.inBuf.bufs[2];

			// Find slice mode: 0: sequential , 1: slice mode
			sliceMode = (T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.numAU != 0);
			memset(T->g.jpegenc1.outBuf.bufs[0], 0, T->g.jpegenc1.outBuf.bufSizes[0]);
			nSlices++;

			// First Encode process call is to generate headers only
			T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.generateHeader = XDM_GENERATE_HEADER;

			if (DVEVM_ST_FAIL == dvtb_jpegEnc1EncProcess(&T->g.jpegenc1, &encDuration))
			{
				SYS_ERROR("Image encoder Process fails for slice # %d \n", nSlices);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			targetBuff = T->g.jpegenc1.outBuf.bufs[0];
			targetBytes = T->g.jpegenc1.ienc1OutArgs.imgencOutArgs.bytesGenerated;

			// Update output buffer with Out pointer returned by codec
			T->g.jpegenc1.outBuf.bufs[0] = (char *) T->g.jpegenc1.ienc1OutArgs.curOutPtr;

			// Update output buffer size with number of bytes remained after encode process call
			T->g.jpegenc1.outBuf.bufSizes[0] -= T->g.jpegenc1.ienc1OutArgs.imgencOutArgs.bytesGenerated;

			T->g.jpegenc1.ienc1Cmd = XDM_SETPARAMS;

			// Set mode to encode Access units
			T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.generateHeader = JPEGENC_TI_ENCODE_AU_NOHEADER;

			SYS_OUT("Encoded Slice#, %d \n", nSlices);

#ifdef PERF
			SYS_PERF("Thread, %x, Slice#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, nSlices, (int) T->g.jpegenc1.ienc1OutArgs.imgencOutArgs.bytesGenerated, encDuration);
#endif
			T->g.jpegenc1.ienc1InArgs.sliceNum = 0;
			numAU = T->g.jpegenc1.ienc1Status.numAU;
			if (sliceMode)
			{
				// In case of 270 rotation, must point to right most slice of the image
				inputWidth = T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.inputWidth;
				inputHeight = T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.inputHeight;
				forceChromaFormat = T->g.jpegenc1.ienc1Params.imgencParams.forceChromaFormat;
				inputChromaFormat = T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.inputChromaFormat;
				captureWidth = T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.captureWidth;

				if (90 == T->g.jpegenc1.ienc1DynParams.rotation)
				{
					if (T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.inputChromaFormat == XDM_YUV_420SP)
					{
						sliceWidth = (numAU * 16 / inputHeight) * (8 << (XDM_YUV_420P == forceChromaFormat)); // Doesn't support 'forceChromaFormat' set to 420sp
						T->g.jpegenc1.inBuf.bufs[0] += (inputWidth - sliceWidth);
						T->g.jpegenc1.inBuf.bufs[1] += (inputWidth - sliceWidth);
					}
					else
					{
						sliceWidth = (numAU * 16 / inputHeight) * (8 << (XDM_YUV_420P == forceChromaFormat));
						T->g.jpegenc1.inBuf.bufs[0] += (inputChromaFormat == XDM_YUV_422ILE ? 2 : 1) * (inputWidth - sliceWidth);
						T->g.jpegenc1.inBuf.bufs[1] += (inputWidth / 2) - (sliceWidth / 2);
						T->g.jpegenc1.inBuf.bufs[2] += (inputWidth / 2) - (sliceWidth / 2);
					}
				}
				else if (180 == T->g.jpegenc1.ienc1DynParams.rotation)
				{
					sliceHeight = (numAU * 16 / inputWidth) * (8 << (XDM_YUV_420P == forceChromaFormat));

					if (T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.inputChromaFormat != XDM_YUV_420SP)
					{
						T->g.jpegenc1.inBuf.bufs[0] += captureWidth * (inputChromaFormat == XDM_YUV_422ILE ? 2 : 1) * (inputHeight - sliceHeight);
						T->g.jpegenc1.inBuf.bufs[1] += captureWidth * (inputHeight - sliceHeight) >> (1 + (inputChromaFormat == XDM_YUV_420P));
						T->g.jpegenc1.inBuf.bufs[2] += captureWidth * (inputHeight - sliceHeight) >> (1 + (inputChromaFormat == XDM_YUV_420P));
					}
					else
					{
						T->g.jpegenc1.inBuf.bufs[0] += captureWidth * (inputHeight - sliceHeight);
						T->g.jpegenc1.inBuf.bufs[1] += captureWidth * (inputHeight - sliceHeight) >> 1;
					}
				}
			}

			while (T->g.jpegenc1.ienc1OutArgs.imgencOutArgs.currentAU < T->g.jpegenc1.ienc1Status.imgencStatus.totalAU )
			{
				nSlices++;

				if (DVEVM_ST_FAIL == dvtb_jpegEnc1EncProcess(&T->g.jpegenc1, &encDuration))
				{
					SYS_ERROR("Jpeg encoder Process fails for slice # %d \n", nSlices);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				T->g.jpegenc1.ienc1InArgs.sliceNum++;
				//Update the In buffer with the In pointers from codec
				if (T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.inputChromaFormat == XDM_YUV_422ILE)
				{
					T->g.jpegenc1.inBuf.bufSizes[0] = (int) T->g.jpegenc1.ienc1OutArgs.curInPtrY - (int) T->g.jpegenc1.inBuf.bufs[0];
					T->g.jpegenc1.inBuf.bufs[0] = (char *) T->g.jpegenc1.ienc1OutArgs.curInPtrY;
				}
				else if (T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.inputChromaFormat == XDM_YUV_420SP)
				{
					T->g.jpegenc1.inBuf.bufSizes[0] = (int) T->g.jpegenc1.ienc1OutArgs.curInPtrY - (int) T->g.jpegenc1.inBuf.bufs[0];
					T->g.jpegenc1.inBuf.bufSizes[1] = (int) T->g.jpegenc1.ienc1OutArgs.curInPtrU - (int) T->g.jpegenc1.inBuf.bufs[1];

					T->g.jpegenc1.inBuf.bufs[0] = (char *) T->g.jpegenc1.ienc1OutArgs.curInPtrY;
					T->g.jpegenc1.inBuf.bufs[1] = (char *) T->g.jpegenc1.ienc1OutArgs.curInPtrU;
				}
				else
				{
					T->g.jpegenc1.inBuf.bufSizes[0] = (int) T->g.jpegenc1.ienc1OutArgs.curInPtrY - (int) T->g.jpegenc1.inBuf.bufs[0];
					T->g.jpegenc1.inBuf.bufSizes[1] = (int) T->g.jpegenc1.ienc1OutArgs.curInPtrU - (int) T->g.jpegenc1.inBuf.bufs[1];
					T->g.jpegenc1.inBuf.bufSizes[2] = (int) T->g.jpegenc1.ienc1OutArgs.curInPtrV - (int) T->g.jpegenc1.inBuf.bufs[2];

					T->g.jpegenc1.inBuf.bufs[0] = (char *) T->g.jpegenc1.ienc1OutArgs.curInPtrY;
					T->g.jpegenc1.inBuf.bufs[1] = (char *) T->g.jpegenc1.ienc1OutArgs.curInPtrU;
					T->g.jpegenc1.inBuf.bufs[2] = (char *) T->g.jpegenc1.ienc1OutArgs.curInPtrV;
				}

				//Update the out buffer with the out pointers from codec
				T->g.jpegenc1.outBuf.bufs[0] = (char *) T->g.jpegenc1.ienc1OutArgs.curOutPtr;
				T->g.jpegenc1.outBuf.bufSizes[0] -= T->g.jpegenc1.ienc1OutArgs.imgencOutArgs.bytesGenerated;

				targetBytes += T->g.jpegenc1.ienc1OutArgs.imgencOutArgs.bytesGenerated;

				if (!(T->g.jpegenc1.ienc1OutArgs.imgencOutArgs.currentAU < (T->g.jpegenc1.ienc1Status.imgencStatus.totalAU - numAU)))
				{
					//Last Slice
					if (sliceMode)
					{
						T->g.jpegenc1.ienc1InArgs.sliceNum = -1;
						T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.numAU = T->g.jpegenc1.ienc1Status.imgencStatus.totalAU - T->g.jpegenc1.ienc1OutArgs.imgencOutArgs.currentAU; //For last slice, re-adjust numAU.
						

						// In case of 270 rotation, last slice override values of inputBufDesc.bufs[0],[1],[2]
						// because values outArgs.curInPtrY, outArgs.curInPtrU,outArgs.curInPtrV
						// returned by codec was calculated assuming numAU value calculated before last slice at line 596.
						// For last slice inputBufDesc.bufs[0] just needs to be set to the beginning of frame.
#if 0
						if (270 == T->g.jpegenc1.ienc1DynParams.rotation)
						{
							T->g.jpegenc1.inBuf.bufs[0] = orgPictureY;
							if (IJPEGENC_YUV_420LINE == T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.inputChromaFormat)
							{
								T->g.jpegenc1.inBuf.bufs[1] = orgPictureY + inputWidth;
								T->g.jpegenc1.inBuf.bufs[2] = T->g.jpegenc1.inBuf.bufs[1] + (inputWidth * 3 / 2);
							}
							else if (XDM_YUV_422ILE != T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.inputChromaFormat)
							{
								T->g.jpegenc1.inBuf.bufs[1] = orgPictureCb;
								T->g.jpegenc1.inBuf.bufs[2] = orgPictureCr;
							}
							else if (XDM_YUV_420SP != T->g.jpegenc1.ienc1DynParams.imgencDynamicParams.inputChromaFormat)
							{
								T->g.jpegenc1.inBuf.bufs[1] = orgPictureCb;
							}

						}
#else
						if ( 90 == T->g.jpegenc1.ienc1DynParams.rotation )
						{
							T->g.jpegenc1.inBuf.bufs[0] = orgPictureY;
							T->g.jpegenc1.inBuf.bufs[1] = orgPictureCb;
							T->g.jpegenc1.inBuf.bufs[2] = orgPictureCr;

						}						

#endif
					}
				}
				SYS_OUT("Encoded Slice#, %d \n", nSlices);
#ifdef PERF
				SYS_PERF("Thread, %x, Slice#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, nSlices, (int) T->g.jpegenc1.ienc1OutArgs.imgencOutArgs.bytesGenerated, encDuration);
#endif
			}
			if (DVEVM_ST_TRUE == usecaseFailed)//Proceed only if use case is successful
				break;
		}
		else
		{
			memcpy(appBuffer, T->g.jpegenc1.inBuf.bufs[0], appBufferSize);
			targetBuff = appBuffer;
			targetBytes = appBufferSize;
			SYS_OUT("Captured Frame.\n");
		}

		if (DVEVM_ST_FALSE == fileBased)
		{
			dvtb_vpfeReturnBuffer(&T->g.vpfe);
		}

		/* Store the processed frame to target file */
		SYS_DEBUG("T->g.jpegenc1.outBuf.bufs[0] = %x, T->g.jpegenc1.outBuf.bufSizes[0] = %d\n", (unsigned int) T->g.jpegenc1.outBuf.bufs[0], (int) T->g.jpegenc1.outBuf.bufSizes[0]);
		SYS_DEBUG("T->g.jpegenc1.outBufDesc.descs[0].buf = %x, T->g.jpegenc1.outBufDesc.descs[0].bufSize = %d\n", (unsigned int) T->g.jpegenc1.outBufDesc.descs[0].buf, (int) T->g.jpegenc1.outBufDesc.descs[0].bufSize);
		SYS_DEBUG("targetBuff = %x, targetBytes = %d\n", (unsigned int) targetBuff, targetBytes);

		if (DVEVM_ST_FAIL == dvtb_fileWrite(T->targetFp, (char *) targetBuff, targetBytes))
		{
			SYS_ERROR("Error in writing to file.\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		/* Restore the backed-up XDM buffer */
		if ((DVEVM_ST_FALSE == fileBased) && T->useAlgorithm)
		{
			dvtb_copyXdmBuf(&oldXdmBuf, &T->g.jpegenc1.inBuf);
		}
	} while (DVEVM_ST_FALSE);

	dvtb_jpegEnc1ProcessEndMessage(T->useAlgorithm, fileBased, nSlices);

	/* Uninitialize and close */
	if (T->useAlgorithm)
	{
		dvtb_jpegEnc1HanClose(&T->g.jpegenc1, T->g.eng.name);
	}
	else
	{
		if (NULL != appBuffer)
			dvtb_freeSingleBufCmem(appBuffer, appBufferSize);
	}

	if (DVEVM_ST_TRUE == vpfeOpened)
	{
		dvtb_captureClose(&T->g.vpfe, &T->g.vpPrvw, &T->g.vpRsz);
		SYS_OUT("Capture module closed\n");
	}

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_jpegEnc1ExitMessage(T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	pthread_exit(NULL);
}
