/*
 * dvtbMpeg2Play2.c
 *
 * XDM1.2 MPEG2 Decode Functionality
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

#include "dvtbMpeg2Play2.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbMpeg2Dec2.h"
#include "dvtbUtils.h"
#include "dvtbMpeg2Play2Core.h"
#include "dvtbVidPlay2Core.h"
#include "dvtbVidPlay2.h"

void
dvtb_Mpeg2Dec2Play(DvevmStThreadInfo *T)
{
	int nBytes = 0, nTotalInputBytes = 0, nFrames = 1, displayFrame = 1, decDuration = 0,
		bytesConsumed = 0, frameSize = 0, remainingBytes = 0, buffSize = 0, alreadyReadBytes = 0;
	
#if 0
	int  validOutIds = 0;
#endif

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

	if (!T->targetFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_DECODE, "MPEG2",T->useAlgorithm, fileBased);
	dvtb_mpeg2Dec2InitPtrs(&T->g.mpeg2dec2);
	dvtb_vidDec2InitVpbeBuff(&T->g.vpbe);

	// [Decode][Play] scenario
	do
	{
		if (T->useAlgorithm)
		{
			inbuf = &T->g.mpeg2dec2.inBuf;
			outbuf = &T->g.mpeg2dec2.outBuf;

			if (DVEVM_ST_FAIL == dvtb_mpeg2Dec2HanInit(&T->g.mpeg2dec2, (char *)T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Video Decoder Handle. \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_FAIL == dvtb_vidDec2InBuffAlloc(&T->g.mpeg2dec2.inBuf, &T->g.mpeg2dec2.inBufDesc, T->g.mpeg2dec2.vdec2Status.viddecStatus.bufInfo.minNumInBufs))
			{
				SYS_ERROR("Error in allocating memory for input buffer.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Allocate First Output Buffer
			if(DVEVM_ST_FAIL == dvtb_mpeg2Dec2InitFirstOutBuffer(&T->g.mpeg2dec2))
			{
				SYS_ERROR("Unable to Initialize 1st out buffer.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			T->g.mpeg2dec2.vdec2OutArgs.viddecOutArgs.outBufsInUseFlag = 0;
			buffSize = T->g.mpeg2dec2.outBufArray[0].buffer.bufSizes[0];

			SYS_OUT("Video Decoder <%s> initialized\n", T->g.mpeg2dec2.vdec2Name);
		}
		else
		{
			//Do Nothing
		}
		
		// If target file is not defined, initialize VPBE
		if (DVEVM_ST_FALSE == fileBased)
		{

                        //Allocate buffers for driver(when used in user buffer pointer Mode)
                        if (DVEVM_ST_FAIL == dvtb_vidDec2VpbeBuffAlloc(&T->g.vpbe, buffSize))
                        {
                                SYS_ERROR("Error in allocating memory for VPBE buffer(User buffer mode).\n");
                                usecaseFailed = DVEVM_ST_TRUE;
                                break;
                        }


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

			if ((0 == nBytes) || ( (nBytes <= 4) && (XDM_LE_32 == T->g.mpeg2dec2.vdec2Params.viddecParams.dataEndianness)))
			{
				SYS_OUT("End of source file reached. Exiting ...\n");
				break;
			}

			if (T->useAlgorithm)
			{
				T->g.mpeg2dec2.vdec2InArgs.viddecInArgs.numBytes = nBytes;
				T->g.mpeg2dec2.inBufDesc.descs[0].buf = (XDAS_Int8 *) ((XDAS_Int32) T->g.mpeg2dec2.inBuf.bufs[0]);

				if (DVEVM_ST_FAIL == dvtb_mpeg2Dec2DecProcess(&T->g.mpeg2dec2, &decDuration))
				{
					SYS_ERROR("Video decoder process fails for frame # %d. \n",nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				frameSize = T->g.mpeg2dec2.vdec2OutArgs.viddecOutArgs.bytesConsumed;
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
				if(XDM_LE_32 == T->g.mpeg2dec2.vdec2Params.viddecParams.dataEndianness)
				{
					alreadyReadBytes = frameSize>>2;
					bytesConsumed += frameSize<<2;
					fseek(T->sourceFp, -(nBytes - (alreadyReadBytes<<2)), SEEK_CUR);
					remainingBytes -= frameSize;					
				}
				else
				{
					bytesConsumed += frameSize;
					fseek(T->sourceFp, -(nBytes - frameSize), SEEK_CUR);
					remainingBytes -= frameSize;
				}

				if(DVEVM_ST_TRUE == firstProcessCall)
				{
					firstProcessCall = DVEVM_ST_FALSE;

					//Allocate and initialize all outBuffers once again
					if(DVEVM_ST_FAIL == dvtb_mpeg2Dec2InitAllOutBuffers(&T->g.mpeg2dec2))
					{
						SYS_ERROR("Unable to Initialize other out buffers.\n");
						dvtb_mpeg2Dec2DeInitOutBuffers(&T->g.mpeg2dec2);
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					SYS_DEBUG("All Output buffers initialized.\n");
				}

				if (!T->g.mpeg2dec2.vdec2OutArgs.viddecOutArgs.outBufsInUseFlag)
				{
					//TBD
				}
				
				if(DVEVM_ST_FAIL == dvtb_mpeg2Dec2ProcessOutBuff(&T->g,&T->g.mpeg2dec2, T->targetFp, fileBased, nFrames, &displayFrame))
				{
					SYS_ERROR("Unable to Process Out buffers. \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				dvtb_mpeg2Dec2ReleaseBuffers(&T->g.mpeg2dec2, (unsigned int *)T->g.mpeg2dec2.vdec2OutArgs.viddecOutArgs.freeBufID);

				SYS_DEBUG("bytes consumed = %d, Totalbytes = %d\n", bytesConsumed, nTotalInputBytes);
			}
			else
			{
				//Do Nothing
			}
		} while ((nFrames <= T->g.mpeg2dec2.numFrames) && (bytesConsumed >= nTotalInputBytes));// end do-while

		//Flush the held frames only in the case where the usecase has not failed so far
		if (DVEVM_ST_FALSE == usecaseFailed && T->useAlgorithm && (XDM_PARSE_HEADER != T->g.mpeg2dec2.vdec2DynParams.viddecDynamicParams.decodeHeader))
		{
			if(DVEVM_ST_FAIL == dvtb_mpeg2Dec2Flush(&T->g,&T->g.mpeg2dec2, T->targetFp, fileBased, nFrames, &displayFrame))
			{
				SYS_ERROR("Unable to Flush Held frames buffers. \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_vidDec2ProcessEndMessage(T->useAlgorithm, fileBased, displayFrame);

	if(DVEVM_ST_TRUE == vpbeOpened)
	{
		dvtb_vpbeClose(&T->g.vpbe);
		SYS_OUT("VPBE Device <%s> closed.\n", T->g.vpbe.device);
	}
	dvtb_mpeg2Dec2HanClose(&T->g.mpeg2dec2, T->g.eng.name);

	if(DVEVM_ST_FAIL == dvtb_vidDec2VpbeBuffFree(&T->g.vpbe))
	{
		SYS_ERROR("Unable to Free VPBE buffers. \n");
		usecaseFailed = DVEVM_ST_TRUE;
	}

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_DECODE, "Mpeg2", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit( );
}
