/*
 * dvtbVidPlay2.c
 *
 * XDM1.0 Video Decode Functionality
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

#include "dvtbVidPlay2.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbVidDec2.h"
#include "dvtbUtils.h"
#include "dvtbVidPlay2Core.h"

DvevmStRetCode
dvtb_vidDec2Copy(DvevmStGlobalParams *g, char *out_buff, char *in_buff, int size)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	g->disvdce.inputBuffer = (unsigned char *) in_buff;

	g->disvdce.outputBuffer = (unsigned char *)out_buff;

	if (DVEVM_ST_FAIL == dvtb_vdceConvert420to422(&g->disvdce))
	{
		SYS_ERROR("Chrominance Conversion (420 to 422) Failed\n");
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStRetCode
dvtb_vidDec2WriteOutputData(IVIDEO1_BufDesc *displayBuf, FILE *fOutFile, VIDDEC2_Status *vdec2Status)
{
	int height = 0;
	XDAS_Int32 picSize = 0;
	XDAS_Int8 *cbcrSeparate[2] = { NULL, NULL }, *lumaData = NULL, *cbcrData = NULL;

	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	//Ensure VIDDEC2_MAX_WD is 1920 and VIDDEC2_MAX_HT is 1088
	XDAS_Int8 chromaSeparate[VIDDEC2_MAX_WD * VIDDEC2_MAX_HT / 2];

	picSize = displayBuf->frameWidth * displayBuf->frameHeight;

	//Init input subPic_buf with  outArgs
	lumaData = displayBuf->bufDesc[0].buf;
	cbcrData = displayBuf->bufDesc[1].buf;

	//Init output yuv_buffer with global pointer fullPic
	cbcrSeparate[0] = chromaSeparate;
	cbcrSeparate[1] = cbcrSeparate[0] + (picSize >> 2);

	//This function separates out the Cb and Cr component
	if (DVEVM_ST_FAIL == dvtb_separateCbCrPixels(cbcrData, cbcrSeparate, (displayBuf->frameHeight >> 1), displayBuf->frameWidth, displayBuf->framePitch))
	{
		SYS_ERROR("Unable to separate CbCr Pixels.\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		//Write YUV data to File
		for (height = 0; height < displayBuf->frameHeight; height++)
		{
			if (DVEVM_ST_FAIL == dvtb_fileWrite(fOutFile, (char *) lumaData, displayBuf->frameWidth))
			{
				SYS_ERROR("Error in writing to file.\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
			lumaData += displayBuf->framePitch;
		}

		if (DVEVM_ST_FAIL != retCode)
		{
			if (DVEVM_ST_FAIL == dvtb_fileWrite(fOutFile, (char *) cbcrSeparate[0], picSize >> 2))
			{
				SYS_ERROR("Error in writing to file.\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (DVEVM_ST_FAIL == dvtb_fileWrite(fOutFile, (char *) cbcrSeparate[1], picSize >> 2))
			{
				SYS_ERROR("Error in writing to file.\n");
				retCode = DVEVM_ST_FAIL;
			}
		}

		fflush((FILE *) fOutFile);
	}
	return retCode;
}

DvevmStRetCode
dvtb_vidDec2UtilitySetup(DvevmStGlobalParams *g, IVIDEO1_BufDesc *displayBufs, int inFormat)
{
	int inputHeight = 0, inputWidth = 0, inputPitch = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if(DVEVM_ST_FALSE == g->disvdce.vdceOpened)
	{
		inputHeight = displayBufs->frameHeight;
		inputWidth  = displayBufs->frameWidth;
		inputPitch  = displayBufs->framePitch;
		// VDCE device is opened when first output buffer is available
		if(DVEVM_ST_FAIL == dvtb_vdceSetup(&g->disvdce, inputHeight, inputWidth, inputPitch, inFormat))
		{
			SYS_ERROR("Unable to setup utility device: VDCE \n");
						retCode = DVEVM_ST_FAIL;
		}
	}

	return retCode;
}

void
dvtb_VidDec2Play(DvevmStThreadInfo *T)
{
	int nBytes = 0, nTotalInputBytes = 0, nFrames = 1, displayFrame = 1, decDuration = 0,
		bytesConsumed = 0, frameSize = 0, remainingBytes = 0, validOutIds = 0;

	unsigned int fileSize = 0;

	DvevmStRetCode status = DVEVM_ST_FAIL;
	DvevmStXdmBuffer *inbuf = NULL, *outbuf = NULL;

	DvevmStBool firstProcessCall = DVEVM_ST_TRUE, usecaseFailed = DVEVM_ST_FALSE,
		vpbeOpened = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	T->g.vpbe.videoFd = 0;

	if (!T->sourceFp)
	{
		SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	if(!T->useAlgorithm)
	{
		SYS_ERROR("Option not supported \n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	T->g.disvdce.vdceOpened = DVEVM_ST_FALSE;

	if (!T->targetFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_DECODE, "Video",T->useAlgorithm, fileBased);
	dvtb_vidDec2InitPtrs(&T->g.vdec2);

	// [Decode][Play] scenario
	do
	{
		// If target file is not defined, initialize VPBE
		if (DVEVM_ST_FALSE == fileBased)
		{
			status = (*dvtb_vpbeSetupPtr)(&T->g.vpbe);
			if (DVEVM_ST_FAIL == status)
			{
				SYS_ERROR("Unable to setup VPBE device <%s> for display\n", T->g.vpbe.device);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			status = dvtb_vpbeDisplayStart(&T->g.vpbe);
			if (DVEVM_ST_FAIL == status)
			{
				SYS_ERROR("Unable to sart display device <%s>.\n", T->g.vpbe.device);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			vpbeOpened = DVEVM_ST_TRUE;
			SYS_OUT("VPBE Device <%s> initialized for display\n", T->g.vpbe.device);
		}

		if (T->useAlgorithm)
		{
			inbuf = &T->g.vdec2.inBuf;
			outbuf = &T->g.vdec2.outBuf;

			if (DVEVM_ST_FAIL == dvtb_vidDec2HanInit(&T->g.vdec2, (char *)T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Video Decoder Handle. \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_FAIL == dvtb_vidDec2InBuffAlloc(&T->g.vdec2.inBuf, &T->g.vdec2.inBufDesc, T->g.vdec2.vdec2Status.bufInfo.minNumInBufs))
			{
				SYS_ERROR("Error in allocating memory for input buffer.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Allocate First Output Buffer
			if(DVEVM_ST_FAIL == dvtb_vidDec2InitFirstOutBuffer(&T->g.vdec2))
			{
				SYS_ERROR("Unable to Initialize 1st out buffer.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			T->g.vdec2.vdec2OutArgs.outBufsInUseFlag = 0;

			SYS_OUT("Video Decoder <%s> initialized\n", T->g.vdec2.vdec2Name);
		}
		else
		{
			//Do Nothing
		}

		if(DVEVM_ST_FAIL == dvtb_getFileSize(T->sourceFp, &fileSize))
		{
			SYS_ERROR("Unable to Get File Size \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}
		remainingBytes = fileSize;
		SYS_DEBUG("Input File Size = %d.\n", fileSize);

		do
		{
			if(DVEVM_ST_FAIL == dvtb_fileRead(T->sourceFp, (char *)inbuf->bufs[0], inbuf->bufSizes[0], &nBytes))
			{
				SYS_ERROR("Error in file read \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_DEBUG("Read request = %d; Read %d no of bytes. ErrorValue = %d\n", inbuf->bufSizes[0], nBytes, ferror(T->sourceFp));

			if (0 == nBytes)
			{
				SYS_OUT("End of source file reached. Exiting ...\n");
				break;
			}

			if (T->useAlgorithm)
			{
				T->g.vdec2.vdec2InArgs.numBytes = nBytes;
				T->g.vdec2.inBufDesc.descs[0].buf = (XDAS_Int8 *) ((XDAS_Int32) T->g.vdec2.inBuf.bufs[0]);

				if (DVEVM_ST_FAIL == dvtb_vidDec2DecProcess(&T->g.vdec2, &decDuration))
				{
					SYS_ERROR("Video decoder process fails for frame # %d. \n",nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				frameSize = T->g.vdec2.vdec2OutArgs.bytesConsumed;
				if (0 == frameSize)
				{
					SYS_ERROR("Video Decode Process returned bytesConsumed as 0. Exiting decoding.\n");
					break;
				}

				SYS_OUT("Decoded Frame %d\n", nFrames);

#ifdef PERF
				SYS_PERF("Thread, %x, Decoded Frame#, %d, Frame Size(bytes), %d, DecTime(us), %d\n", (unsigned int) T, nFrames, frameSize, decDuration);
#endif

				nFrames++;

				bytesConsumed += frameSize;
				fseek(T->sourceFp, -(nBytes - frameSize), SEEK_CUR);
				remainingBytes -= frameSize;

				if(DVEVM_ST_TRUE == firstProcessCall)
				{
					firstProcessCall = DVEVM_ST_FALSE;

					//Allocate and initialize all outBuffers once again
					if(DVEVM_ST_FAIL == dvtb_vidDec2InitAllOutBuffers(&T->g.vdec2))
					{
						SYS_ERROR("Unable to Initialize other out buffers.\n");
						dvtb_vidDec2DeInitOutBuffers(&T->g.vdec2);
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					SYS_DEBUG("All Output buffers initialized.\n");
				}

				if (!T->g.vdec2.vdec2OutArgs.outBufsInUseFlag)
				{
					//TBD
				}

				if (DVEVM_ST_FALSE == fileBased)
				{
					if(DVEVM_ST_FALSE == T->g.disvdce.vdceOpened)
					{
						validOutIds = 0;
						if (T->g.vdec2.vdec2DynParams.frameOrder)
						{
							if(0 == T->g.vdec2.vdec2OutArgs.outBufsInUseFlag)
							{
								if(DVEVM_ST_FAIL == dvtb_vidDec2UtilitySetup(&T->g, &T->g.vdec2.vdec2OutArgs.decodedBufs, 1))
								{
									SYS_ERROR("Failed to do setup utility device(s) \n");
									usecaseFailed = DVEVM_ST_TRUE;
									break;
								}
							}
						}
						else
						{
							if (T->g.vdec2.vdec2OutArgs.outputID[validOutIds] > 0)
							{
								if(DVEVM_ST_FAIL == dvtb_vidDec2UtilitySetup(&T->g, &T->g.vdec2.vdec2OutArgs.displayBufs[validOutIds], 1))
								{
									SYS_ERROR("Failed to do setup utility device(s) \n");
									usecaseFailed = DVEVM_ST_TRUE;
									break;
								}
							}
						}
					}
				}

				if(DVEVM_ST_FAIL == dvtb_vidDec2ProcessOutBuff(&T->g,&T->g.vdec2, T->targetFp, fileBased, nFrames, &displayFrame))
				{
					SYS_ERROR("Unable to Process Out buffers. \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				dvtb_vidDec2ReleaseBuffers(&T->g.vdec2, (unsigned int *)T->g.vdec2.vdec2OutArgs.freeBufID);

				SYS_DEBUG("bytes consumed = %d, Totalbytes = %d\n", bytesConsumed, nTotalInputBytes);
			}
			else
			{
				//Do Nothing
			}
		} while ((nFrames <= T->g.vdec2.numFrames) && (bytesConsumed >= nTotalInputBytes));// end do-while

		//Flush the held frames only in the case where the usecase has not failed so far
		if (DVEVM_ST_FALSE == usecaseFailed && T->useAlgorithm)
		{
			if(DVEVM_ST_FAIL == dvtb_vidDec2Flush(&T->g,&T->g.vdec2, T->targetFp, fileBased, nFrames, &displayFrame))
			{
				SYS_ERROR("Unable to Flush Held frames buffers. \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_vidDec2ProcessEndMessage(T->useAlgorithm, fileBased, displayFrame);

	if (DVEVM_ST_TRUE == T->g.disvdce.vdceOpened)
	{
		dvtb_vdceClose(&T->g.disvdce);
		SYS_OUT("VDCE Device <%s> closed.\n",T->g.disvdce.device);
	}

	if(DVEVM_ST_TRUE == vpbeOpened)
	{
		dvtb_vpbeClose(&T->g.vpbe);
		SYS_OUT("VPBE Device <%s> closed.\n", T->g.vpbe.device);
	}
	dvtb_vidDec2HanClose(&T->g.vdec2, T->g.eng.name);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_DECODE, "Video", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit( );
}
