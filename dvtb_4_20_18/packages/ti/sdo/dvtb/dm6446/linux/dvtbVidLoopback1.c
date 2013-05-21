/*
 * dvtbVidLoopback1.c
 *
 * XDM1.0 Video Loopback Functionality
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

#include "dvtbVidLoopback1.h"
#include "dvtbVidPlay2Core.h"
#include "dvtbVidCapture1Core.h"
#include "dvtbVidPlay2.h"
#include "dvtbVidEnc1.h"
#include "dvtbVidDec2.h"
#include "dvtbV4L2VPFE.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_loopBackVidDec2ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		SYS_OUT("Total # of frames captured, Encoded, Decoded & Displayed = %d.\n", nFrames - 1);
	}
	else //File based
		SYS_OUT("Total # of frames Read from file, Encoded, Decoded & dumped = %d.\n", nFrames - 1);
}

void
dvtb_VidLoopback1(DvevmStThreadInfo *T)
{
	int i = 0, maxFrames = 0, nFrames = 1, targetBytes = DEF_VIDFRAME_SIZE, width = 0, height = 0,
		encDuration = 0, frameSize = 0, decDuration = 0, displayFrame = 1, bytesConsumed = 0,
		remainingBytes = 0;

	DvevmStRetCode status = DVEVM_ST_FAIL;
	DvevmStBool firstProcessCall = DVEVM_ST_TRUE, usecaseFailed=DVEVM_ST_FALSE,
		vpbeOpened=DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE, vpfeOpened = DVEVM_ST_FALSE;


	T->g.vpbe.videoFd = 0;

	maxFrames = T->g.venc1.numFrames;
	if(T->g.vdec2.numFrames > maxFrames)
		maxFrames = T->g.vdec2.numFrames;

	if ((T->targetFp && (!T->sourceFp)) || (T->sourceFp && (!T->targetFp)))
	{
		SYS_ERROR("mandatory parameters: Either provide both source and target files or provide none \n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
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

	if ((!T->targetFp) && (!T->sourceFp))
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_ENCDEC, "Video Loopback", T->useAlgorithm, fileBased);
	dvtb_vidDec2InitPtrs(&T->g.vdec2);
	dvtb_vidEnc1InitPtrs(&T->g.venc1);

	/* Dummy loop to enable easy cleanup */
	do
	{
		if (DVEVM_ST_FALSE == fileBased)
		{
			T->g.vpbe.imageWidth = T->g.vpfe.capWidth;
			T->g.vpbe.imageHeight = T->g.vpfe.capHeight;

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
			SYS_OUT("VPBE device <%s> initialized for display\n", T->g.vpbe.device);

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

		width = T->g.venc1.venc1DynParams.inputWidth;
		height = T->g.venc1.venc1DynParams.inputHeight;

		// Video Encoder: Initialize
		if (DVEVM_ST_FAIL == dvtb_vidEnc1HanInit(&T->g.venc1, (char *)T->g.eng.name))
		{
			SYS_ERROR("Unable to initialize Video Encoder Handle \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		//Video Decoder: Initialize
		T->g.vdec2.ceHdl = T->g.venc1.ceHdl;
		if (DVEVM_ST_FAIL == dvtb_vidDec2Init(&T->g.vdec2))
		{
			SYS_ERROR("Unable to initialize Video Decoder <%s>\n", T->g.vdec2.vdec2Name);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		//Video Encoder: Allocate Input buffer
		T->g.venc1.inBufDesc.frameWidth =  T->g.venc1.venc1DynParams.inputWidth;
		T->g.venc1.inBufDesc.frameHeight = T->g.venc1.venc1DynParams.inputHeight;
		if (DVEVM_ST_FAIL == dvtb_vidEnc1InBuffAlloc(&T->g.venc1.inBuf, &T->g.venc1.inBufDesc, fileBased))
		{
			SYS_ERROR("Error in allocating memory for input buffer\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		//Video Encoder: Allocate Output buffer
		if (DVEVM_ST_FAIL == dvtb_vidEnc1OutBuffAlloc(&T->g.venc1.outBuf, &T->g.venc1.outBufDesc))
		{
			SYS_ERROR("Error in allocating memory for output buffer\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		//Video Decoder: Allocate First output buffer
		if(DVEVM_ST_FAIL == dvtb_vidDec2InitFirstOutBuffer(&T->g.vdec2))
		{
			SYS_ERROR("Unable to Initialize 1st out buffer.\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		T->g.vdec2.vdec2OutArgs.outBufsInUseFlag = 0;

		// point video decoder input buffer to the output buffer of video encoder
		T->g.vdec2.inBufDesc.numBufs = T->g.venc1.outBufDesc.numBufs;
		T->g.vdec2.inBuf.numBufs = T->g.venc1.outBufDesc.numBufs;
		for (i = 0; i < T->g.vdec2.inBufDesc.numBufs; i++)
		{
			T->g.vdec2.inBufDesc.descs[i].buf = T->g.venc1.outBufDesc.bufs[i];
			T->g.vdec2.inBufDesc.descs[i].bufSize = T->g.venc1.outBufDesc.bufSizes[i];
			T->g.vdec2.inBuf.bufs[i] = (char *) T->g.venc1.outBufDesc.bufs[i];
			T->g.vdec2.inBuf.bufSizes[i] = T->g.venc1.outBufDesc.bufSizes[i];
		}

		/* Start the [capture][encode] process */
		while (nFrames <= maxFrames)
		{
			//Video encoder : Read Input
			if(DVEVM_ST_FAIL == dvtb_vidEnc1ReadInput(&T->g.vpfe, T->sourceFp, &T->g.venc1.inBufDesc, fileBased))
			{
				SYS_ERROR("Error in Read Input \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_TRUE == fileBased)
			{
				if (feof(T->sourceFp))
				{
					SYS_DEBUG("End of source file reached. Exiting ...\n");
					break;
				}
			}

			//Video Encoder: Encode input buffer
			if(DVEVM_ST_FAIL == dvtb_vidEnc1EncProcess(&T->g.venc1, &encDuration))
			{
				SYS_ERROR("video encoder Process fails for frame # %d \n", nFrames);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			targetBytes = T->g.venc1.venc1OutArgs.bytesGenerated;
			targetBytes = T->g.venc1.venc1OutArgs.bytesGenerated;

			if (T->g.venc1.venc1OutArgs.inputFrameSkip)
				SYS_ERROR("Frame <%d> Skipped\n", nFrames);
			else
				SYS_OUT("Encoded Frame %d.\n", nFrames);

#ifdef PERF
			SYS_PERF("Thread, %x, Frame#, %d, Frame Type, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, nFrames, (int) T->g.venc1.venc1OutArgs.encodedFrameType, targetBytes, encDuration);
#endif
			if (T->g.venc1.venc1OutArgs.bytesGenerated)
			{

				T->g.vdec2.vdec2InArgs.numBytes = targetBytes;
				bytesConsumed = 0;
				remainingBytes = targetBytes;

			}
			else
			{
				if (DVEVM_ST_FALSE == fileBased)
					dvtb_vpfeReturnBuffer(&T->g.vpfe);
				continue;
			}

			if (DVEVM_ST_FAIL == dvtb_vidDec2DecProcess(&T->g.vdec2, &decDuration))
			{
				SYS_ERROR("Video decoder process fails for frame # %d. \n",nFrames);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			frameSize = T->g.vdec2.vdec2OutArgs.bytesConsumed;
			SYS_DEBUG("Bytes Consumed = %d.\n", frameSize);
			if (frameSize == 0)
			{
				SYS_ERROR("Video Decode Process returned bytesConsumed as 0. Exiting decoding.\n");
				break;
			}

			SYS_OUT("Decoded Frame %d.\n", nFrames);
#ifdef PERF
			SYS_PERF("Thread, %x, Decoded Frame#, %d ,Frame Size(bytes), %d, DecDuration(us), %d\n",(unsigned int) T, nFrames, frameSize, decDuration);
#endif

			bytesConsumed += frameSize;
			remainingBytes -= frameSize;

			if (firstProcessCall == DVEVM_ST_TRUE)
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

			if(DVEVM_ST_FAIL == dvtb_vidDec2ProcessOutBuff(&T->g,&T->g.vdec2, T->targetFp, fileBased, nFrames, &displayFrame))
			{
				SYS_ERROR("Unable to Process Out buffers. \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			dvtb_vidDec2ReleaseBuffers(&T->g.vdec2, (unsigned int *)T->g.vdec2.vdec2OutArgs.freeBufID);

			if (DVEVM_ST_FALSE == fileBased)
				dvtb_vpfeReturnBuffer(&T->g.vpfe);

			nFrames++;
		}

		//Flush the held frames only in the case where the usecase has not failed so far
		if(DVEVM_ST_FALSE == usecaseFailed && T->useAlgorithm)
		{
			if(DVEVM_ST_FAIL == dvtb_vidDec2Flush(&T->g,&T->g.vdec2, T->targetFp, fileBased, nFrames, &displayFrame))
			{
				SYS_ERROR("Unable to Flush Held frames buffers. \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
	} while (DVEVM_ST_FALSE);

	dvtb_loopBackVidDec2ProcessEndMessage(T->useAlgorithm, fileBased, displayFrame);

	//Video Decoder: Free all the allocated output buffers
	dvtb_vidDec2DeInitOutBuffers(&T->g.vdec2);

	//Video Decoder: close video decoder
	dvtb_vidDec2Close(&T->g.vdec2);
	SYS_OUT("Video Decoder <%s> closed.\n", T->g.vdec2.vdec2Name);

	//Video Encoder: close video encoder and engine
	dvtb_vidEnc1HanClose(&T->g.venc1, T->g.eng.name);

	if(DVEVM_ST_TRUE == vpbeOpened)
	{
		dvtb_vpbeClose(&T->g.vpbe);
		SYS_OUT("VPBE Device <%s> closed.\n", T->g.vpbe.device);
	}

	if (DVEVM_ST_TRUE == vpfeOpened)
	{
		dvtb_vpfeClose(&T->g.vpfe);
		SYS_OUT("VPFE Device <%s> closed\n", T->g.vpfe.device);
	}

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCDEC, "Video Loopback", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
