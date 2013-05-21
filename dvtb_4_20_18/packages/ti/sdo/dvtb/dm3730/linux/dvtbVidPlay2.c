/*
 * dvtbVidPlay2.c
 *
 * XDM1.2 Video Decode Functionality
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
#include "dvtbV4L2VPBEFeatures.h"
#include "dvtbVidDec2.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbVidPlay2Core.h"

/*********************************************************************
 *	dvtb_vidDec2Copy:
 *	Description: Copy data
 ********************************************************************/
DvevmStRetCode
dvtb_vidDec2Copy(DvevmStGlobalParams *g, char *out_buff, char *in_buff, int size)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	memcpy(out_buff, in_buff, size);

	return retCode;
}

/*********************************************************************
 *	dvtb_vidDec2WriteOutputData:
 *	Description: Write Output data in File
 ********************************************************************/
DvevmStRetCode
dvtb_vidDec2WriteOutputData(IVIDEO1_BufDesc *displayBuf, FILE *fOutFile, VIDDEC2_Status *vdec2Status)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	for (i = 0; i < displayBuf->numBufs; i++)
	{
		// Dump output in File
		if (DVEVM_ST_FAIL == dvtb_fileWrite(fOutFile, (char *) displayBuf->bufDesc[i].buf, displayBuf->bufDesc[i].bufSize))
		{
			SYS_ERROR("Error in writing to file.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

	}
	return retCode;
}

/*********************************************************************
 *	dvtb_vidDec2UtilitySetup:
 *	Description: SetUp Utility
 ********************************************************************/
DvevmStRetCode
dvtb_vidDec2UtilitySetup(DvevmStGlobalParams *g, IVIDEO1_BufDesc *displayBufs, int inFormat)
{
	// dummy function. No utility device(s) needed
	return DVEVM_ST_SUCCESS;
}

void
dvtb_vidDec2InitVpbeBuff(DvevmStVpbeInfo *vpbe)
{
	int i = 0;
	for (i = 0; i < MAX_USER_BUFFERS; i++)
		vpbe->userbufferptr[i] = NULL;
}

DvevmStRetCode
dvtb_vidDec2VpbeBuffAlloc(DvevmStVpbeInfo *vpbe, int buffSize)
{
	int i = 0, j = 0;
	char *buff = NULL;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (vpbe->opMode)
	{
		for (i = 0; i < vpbe->maxBuffers; i++)
		{
			if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&vpbe->userbufferptr[i], buffSize))
			{
				SYS_ERROR("Unable to allocate memory for driver buffer.\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
			vpbe->userbufferlen[i] = buffSize;
			buff = vpbe->userbufferptr[i];
			for(j =1 ; j< buffSize;j+=2)
			{
				buff[j-1] =  0x80;
				buff[j]   =  0x00;
			}

		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_vidDec2VpbeBuffFree(DvevmStVpbeInfo *vpbe)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (vpbe->opMode)
	{
		for (i = 0; i < MAX_USER_BUFFERS; i++)
		{
			if (NULL != vpbe->userbufferptr[i])
			{
				if (DVEVM_ST_FAIL == dvtb_freeSingleBufCmem(vpbe->userbufferptr[i], vpbe->userbufferlen[i]))
				{
					SYS_ERROR("Unable to Free driver buffer # %d.\n", i);
					retCode = DVEVM_ST_FAIL;
					break;
				}
			}
		}
	}

	return retCode;
}


void
dvtb_VidDec2Play(DvevmStThreadInfo *T)
{
	int nBytes = 0, nTotalInputBytes = 0, nFrames = 1, frameSize = 0, displayFrame = 1,
		decDuration = 0, bytesConsumed = 0, buffSize = 0, alreadyReadBytes = 0;
	unsigned int fileSize = 0, remainingBytes = 0;

	DvevmStRetCode status = DVEVM_ST_FAIL;
	DvevmStXdmBuffer *inbuf = NULL, *outbuf = NULL, dispBuff;
	DvevmStBool firstProcessCall=DVEVM_ST_TRUE, usecaseFailed=DVEVM_ST_FALSE,
			vpbeOpened=DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	T->g.vpbe.videoFd = 0;
	T->g.vpbe.opMode = DVEVM_ST_USERBUFFER;

	if (!T->sourceFp)
	{
		SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit( );
	}

	if (!T->targetFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_DECODE, "Video",T->useAlgorithm, fileBased);
	dvtb_vidDec2InitPtrs(&T->g.viddec2);
	dvtb_vidDec2InitVpbeBuff(&T->g.vpbe);

	// [Decode][Play] scenario
	do
	{
		if (T->useAlgorithm)
		{
			inbuf = &T->g.viddec2.inBuf;
			outbuf = &T->g.viddec2.outBuf;

			if (DVEVM_ST_FAIL == dvtb_vidDec2HanInit(&T->g.viddec2, (char *)T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Video Decoder Handle. \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_FAIL == dvtb_vidDec2InBuffAlloc(&T->g.viddec2.inBuf, &T->g.viddec2.inBufDesc, T->g.viddec2.vdec2Status.bufInfo.minNumInBufs))
			{
				SYS_ERROR("Error in allocating memory for input buffer.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Allocate First Output Buffer
			if(DVEVM_ST_FAIL == dvtb_vidDec2InitFirstOutBuffer(&T->g.viddec2))
			{
				SYS_ERROR("Unable to Initialize 1st out buffer.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}		

			buffSize = T->g.viddec2.outBufArray[0].buffer.bufSizes[0];

			T->g.viddec2.vdec2OutArgs.outBufsInUseFlag = 0;

			SYS_OUT("Video Decoder <%s> initialized\n", T->g.viddec2.vdec2Name);
		}
		else
		{
			dispBuff.numBufs = 1;
			dispBuff.bufSizes[0] = T->g.vpbe.imageWidth * T->g.vpbe.imageHeight * 2;
			if (DVEVM_ST_FAIL == dvtb_allocCmem(&dispBuff))
			{
				SYS_OUT("Unable to allocate memory for video playback\n");
				break;
			}
			inbuf = outbuf = &dispBuff;
			buffSize = dispBuff.bufSizes[0];
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
			SYS_OUT("VPBE device <%s> initialized for display\n", T->g.vpbe.device);
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

			SYS_DEBUG("Current File Position = %d\n", (int) ftell(T->sourceFp));

			if(DVEVM_ST_FAIL == dvtb_fileRead(T->sourceFp, (char *)inbuf->bufs[0], inbuf->bufSizes[0], &nBytes))
			{
				SYS_ERROR("Error in file read \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}


			SYS_DEBUG("Read request = %d; Read %d no of bytes. ErrorValue = %d\n", inbuf->bufSizes[0], nBytes, ferror(T->sourceFp));
			if (0 == nBytes || ( (nBytes <= 4) && (XDM_LE_32 == T->g.viddec2.vdec2Params.dataEndianness)))
			{
				SYS_OUT("End of source file reached. Exiting ...\n");
				break;
			}

			if (T->useAlgorithm)
			{
				T->g.viddec2.vdec2InArgs.numBytes = nBytes;
				T->g.viddec2.inBufDesc.descs[0].buf = (XDAS_Int8 *) ((XDAS_Int32) T->g.viddec2.inBuf.bufs[0]);

				if (DVEVM_ST_FAIL == dvtb_vidDec2DecProcess(&T->g.viddec2, &decDuration))
				{
					SYS_ERROR("Video decoder process fails for frame # %d. \n",nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				frameSize = T->g.viddec2.vdec2OutArgs.bytesConsumed;
				SYS_DEBUG("Bytes Consumed = %d.\n", frameSize);
				if (frameSize == 0)
				{
					SYS_ERROR("Video Decode Process returned bytesConsumed as 0. Exiting decoding.\n");
					break;
				}

				if(!T->g.viddec2.pEnable)
				{
					SYS_OUT("Decoded Frame %d.\n", nFrames);
#ifdef PERF
					SYS_PERF("Thread, %x, Decoded Frame#, %d ,Frame Size(bytes), %d, DecDuration(us), %d\n",(unsigned int) T, nFrames, frameSize, decDuration);
#endif
				}

				nFrames++;
				if(XDM_LE_32 == T->g.viddec2.vdec2Params.dataEndianness)
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

				if (firstProcessCall == DVEVM_ST_TRUE)
				{
					firstProcessCall = DVEVM_ST_FALSE;

					//Allocate and initialize all outBuffers once again
					if(DVEVM_ST_FAIL == dvtb_vidDec2InitAllOutBuffers(&T->g.viddec2))
					{
						SYS_ERROR("Unable to Initialize other out buffers.\n");
						dvtb_vidDec2DeInitOutBuffers(&T->g.viddec2);
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					SYS_DEBUG("All Output buffers initialized.\n");

				}

				if (!T->g.viddec2.vdec2OutArgs.outBufsInUseFlag)
				{
					//TBD
				}

				if(DVEVM_ST_FAIL == dvtb_vidDec2ProcessOutBuff(&T->g,&T->g.viddec2, T->targetFp, fileBased, nFrames, &displayFrame))
				{
					SYS_ERROR("Unable to Process Out buffers. \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				dvtb_vidDec2ReleaseBuffers(&T->g.viddec2, (unsigned int *)T->g.viddec2.vdec2OutArgs.freeBufID);

				SYS_DEBUG("bytes consumed = %d, Totalbytes = %d.\n",bytesConsumed,nTotalInputBytes);
			}
			else
			{
				if(DVEVM_ST_FAIL == dvtb_vidDec2DisplayOutputData(&T->g, (char *)inbuf->bufs[0], inbuf->bufSizes[0]))
				{
					SYS_ERROR("Unable to display frame # %d .\n",displayFrame);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
				SYS_OUT("Displayed Frame# %d.\n", displayFrame);
				nFrames++;
				displayFrame++;
			}
		} while ((nFrames <= T->g.viddec2.numFrames) && (bytesConsumed >= nTotalInputBytes));// end do-while

		//Flush the held frames only in the case where the usecase has not failed so far
		if(DVEVM_ST_FALSE == usecaseFailed && T->useAlgorithm)
		{
			if(DVEVM_ST_FAIL == dvtb_vidDec2Flush(&T->g,&T->g.viddec2, T->targetFp, fileBased, nFrames, &displayFrame))
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

	if (T->useAlgorithm)
	{
		dvtb_vidDec2HanClose(&T->g.viddec2, T->g.eng.name);
	}
	else
		dvtb_freeCmem(&dispBuff);

	if(DVEVM_ST_FAIL == dvtb_vidDec2VpbeBuffFree(&T->g.vpbe))
	{
		SYS_ERROR("Unable to Free VPBE buffers. \n");
		usecaseFailed = DVEVM_ST_TRUE;
	}

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_DECODE, "Video", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit( );
}
