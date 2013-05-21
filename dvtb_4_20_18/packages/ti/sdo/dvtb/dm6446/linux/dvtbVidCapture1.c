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
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_VidEnc1Capture(DvevmStThreadInfo *T)
{
	int maxFrames = 0, nFrames = 1, targetBytes = DEF_VIDFRAME_SIZE, 
		encDuration = 0;

	char *targetBuff = NULL;

	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, vpfeOpened = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	maxFrames = T->g.venc1.numFrames;

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

	dvtb_startMessage(DVEVM_ST_ENCODE, "Video", T->useAlgorithm, fileBased);
	dvtb_vidEnc1InitPtrs(&T->g.venc1);

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
		}

		/* Initialize Video Encoder if Use Algorithm option is selected */
		if (T->useAlgorithm)
		{
			if (DVEVM_ST_FAIL == dvtb_vidEnc1HanInit(&T->g.venc1, (char *)T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Video Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			T->g.venc1.inBufDesc.frameWidth =  T->g.venc1.venc1DynParams.inputWidth;
			T->g.venc1.inBufDesc.frameHeight = T->g.venc1.venc1DynParams.inputHeight;

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

			SYS_OUT("Video Encoder <%s> initialized\n",	T->g.venc1.venc1Name);
		}
		else
		{
			T->g.venc1.inBufDesc.numBufs = 1;
		}

		/* Start the [capture][encode] process */
		while (nFrames <= maxFrames)
		{
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
					SYS_OUT("End of source file reached. Exiting ...\n");
					break;
				}
			}

			if (T->useAlgorithm)
			{
				if(DVEVM_ST_FAIL == dvtb_vidEnc1EncProcess(&T->g.venc1, &encDuration))
				{
					SYS_ERROR("video encoder Process fails for frame # %d \n", nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				targetBuff = T->g.venc1.outBuf.bufs[0];
				targetBytes = T->g.venc1.venc1OutArgs.bytesGenerated;

				if (T->g.venc1.venc1OutArgs.inputFrameSkip)
					SYS_ERROR("Frame <%d> Skipped\n", nFrames);
				else
					SYS_OUT("Encoded Frame %d.\n", nFrames);
#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Frame Type, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, nFrames, (int) T->g.venc1.venc1OutArgs.encodedFrameType, targetBytes, encDuration);
#endif
			}
			else
			{
				targetBuff = (char *)T->g.venc1.inBufDesc.bufDesc[0].buf;
				targetBytes = T->g.vpfe.capWidth * T->g.vpfe.capHeight * 2;

			}

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

	if (T->useAlgorithm)
		dvtb_vidEnc1HanClose(&T->g.venc1, T->g.eng.name);

	if (DVEVM_ST_TRUE == vpfeOpened)
	{
		dvtb_vpfeClose(&T->g.vpfe);
		SYS_OUT("VPFE Device <%s> closed\n", T->g.vpfe.device);
	}

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "Video", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
