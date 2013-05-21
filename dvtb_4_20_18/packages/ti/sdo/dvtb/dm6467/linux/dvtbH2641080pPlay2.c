/*
 * dvtbH2641080pPlay2.c
 *
 * XDM1.2 H2641080p Decode Functionality
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

#include "dvtbH2641080pPlay2.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbH2641080pDec2.h"
#include "dvtbUtils.h"
#include "dvtbH2641080pPlay2Core.h"
#include "dvtbVidPlay2Core.h"

void
dvtb_H2641080pDec2Play(DvevmStThreadInfo *T)
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

	dvtb_startMessage(DVEVM_ST_DECODE, "H2641080p",T->useAlgorithm, fileBased);
	dvtb_h2641080pDec2InitPtrs(&T->g.h2641080pdec2);

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
			inbuf = &T->g.h2641080pdec2.inBuf;
			outbuf = &T->g.h2641080pdec2.outBuf;

			if (DVEVM_ST_FAIL == dvtb_h2641080pDec2HanInit(&T->g.h2641080pdec2, (char *)T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Video Decoder Handle. \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_FAIL == dvtb_vidDec2InBuffAlloc(&T->g.h2641080pdec2.inBuf, &T->g.h2641080pdec2.inBufDesc, T->g.h2641080pdec2.vdec2Status.viddecStatus.bufInfo.minNumInBufs))
			{
				SYS_ERROR("Error in allocating memory for input buffer.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Allocate First Output Buffer
			if(DVEVM_ST_FAIL == dvtb_h2641080pDec2InitFirstOutBuffer(&T->g.h2641080pdec2))
			{
				SYS_ERROR("Unable to Initialize 1st out buffer.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			T->g.h2641080pdec2.vdec2OutArgs.viddecOutArgs.outBufsInUseFlag = 0;

			SYS_OUT("Video Decoder <%s> initialized\n", T->g.h2641080pdec2.vdec2Name);
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
				T->g.h2641080pdec2.vdec2InArgs.viddecInArgs.numBytes = nBytes;
				T->g.h2641080pdec2.inBufDesc.descs[0].buf = (XDAS_Int8 *) ((XDAS_Int32) T->g.h2641080pdec2.inBuf.bufs[0]);

				if (DVEVM_ST_FAIL == dvtb_h2641080pDec2DecProcess(&T->g.h2641080pdec2, &decDuration))
				{
					SYS_ERROR("Video decoder process fails for frame # %d. \n",nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				frameSize = T->g.h2641080pdec2.vdec2OutArgs.viddecOutArgs.bytesConsumed;
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
					if(DVEVM_ST_FAIL == dvtb_h2641080pDec2InitAllOutBuffers(&T->g.h2641080pdec2))
					{
						SYS_ERROR("Unable to Initialize other out buffers.\n");
						dvtb_h2641080pDec2DeInitOutBuffers(&T->g.h2641080pdec2);
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					SYS_DEBUG("All Output buffers initialized.\n");
				}

				if (!T->g.h2641080pdec2.vdec2OutArgs.viddecOutArgs.outBufsInUseFlag)
				{
					//TBD
				}

				if (DVEVM_ST_FALSE == fileBased)
				{
					if(DVEVM_ST_FALSE == T->g.disvdce.vdceOpened)
					{
						validOutIds = 0;
						if (T->g.h2641080pdec2.vdec2DynParams.viddecDynamicParams.frameOrder)
						{
							if(0 == T->g.h2641080pdec2.vdec2OutArgs.viddecOutArgs.outBufsInUseFlag)
							{
								if(DVEVM_ST_FAIL == dvtb_vidDec2UtilitySetup(&T->g, &T->g.h2641080pdec2.vdec2OutArgs.viddecOutArgs.decodedBufs, 1))
								{
									SYS_ERROR("Failed to do setup utility device(s) \n");
									usecaseFailed = DVEVM_ST_TRUE;
									break;
								}
							}
						}
						else
						{
							if (T->g.h2641080pdec2.vdec2OutArgs.viddecOutArgs.outputID[validOutIds] > 0)
							{
								if(DVEVM_ST_FAIL == dvtb_vidDec2UtilitySetup(&T->g, &T->g.h2641080pdec2.vdec2OutArgs.viddecOutArgs.displayBufs[validOutIds], 1))
								{
									SYS_ERROR("Failed to do setup utility device(s) \n");
									usecaseFailed = DVEVM_ST_TRUE;
									break;
								}
							}
						}
					}
				}
				if(DVEVM_ST_FAIL == dvtb_h2641080pDec2ProcessOutBuff(&T->g,&T->g.h2641080pdec2, T->targetFp, fileBased, nFrames, &displayFrame))
				{
					SYS_ERROR("Unable to Process Out buffers. \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				dvtb_h2641080pDec2ReleaseBuffers(&T->g.h2641080pdec2, (unsigned int *)T->g.h2641080pdec2.vdec2OutArgs.viddecOutArgs.freeBufID);

				SYS_DEBUG("bytes consumed = %d, Totalbytes = %d\n", bytesConsumed, nTotalInputBytes);
			}
			else
			{
				//Do Nothing
			}
		} while ((nFrames <= T->g.h2641080pdec2.numFrames) && (bytesConsumed >= nTotalInputBytes));// end do-while

		//Flush the held frames only in the case where the usecase has not failed so far
		if (DVEVM_ST_FALSE == usecaseFailed && T->useAlgorithm)
		{
			if(DVEVM_ST_FAIL == dvtb_h2641080pDec2Flush(&T->g,&T->g.h2641080pdec2, T->targetFp, fileBased, nFrames, &displayFrame))
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
	dvtb_h2641080pDec2HanClose(&T->g.h2641080pdec2, T->g.eng.name);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_DECODE, "Video", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit( );
}
