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
#include "dvtbVidPlay2Core.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbVidDec2.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"
#include "dvtbDM365Utils.h"

//#define DVTB_PERF

/* Dummy function: Need to be removed later-on */
DvevmStRetCode
dvtb_vidDec2WriteOutputData(IVIDEO1_BufDesc *displayBuf, FILE *fOutFile, VIDDEC2_Status *vdec2Status)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	return retCode;
}
/* Dummy function: Need to be removed later-on */
DvevmStRetCode
dvtb_vidDec2UtilitySetup(DvevmStGlobalParams *g, IVIDEO1_BufDesc *displayBufs, int inFormat)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	return retCode;
}
/* Dummy function: Need to be removed later-on */
DvevmStRetCode
dvtb_vidDec2Copy(DvevmStGlobalParams *g, char *out_buff, char *in_buff, int size)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	return retCode;
}

DvevmStRetCode
dvtb_vidDec2HanInit_dm365(DvevmStVidDec2Info *vd, char *engName)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	vd->ceHdl = NULL;
	vd->vdec2Hdl = NULL;

	vd->inBuf.numBufs = 0;
	vd->outBuf.numBufs = 0;

	vd->buffIdSearchStart = 0;

	memset(&(vd->dispBufArray), 0x00, sizeof(DvevmStOutBuffsInUse)*VIDDEC2_PLAY_MAX_BUFFERS);

	for (i = 0; i < MAX_XDM_BUFS; i++)
	{
		vd->inBuf.bufs[i] = NULL;
		vd->outBuf.bufs[i] = NULL;
	}

	do //Dummy loop for easy clean up
	{
		// Initialize Engine
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &vd->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		//Initialize Codec Instance
		if (DVEVM_ST_FAIL == dvtb_vidDec2Init(vd))
		{
			SYS_ERROR("Unable to initialize Video Decoder <%s>\n", vd->vdec2Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	} while (DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

void
dvtb_vidDec2HanClose_dm365(DvevmStVidDec2Info *vd, char *engName)
{
	//Free the allocated Input Buffer
	if (0 < vd->inBuf.numBufs)
		dvtb_freeCmemSingleChunk(&vd->inBuf);

	//Free all the allocated output buffers

	dvtb_vidDec2DeInitOutBuffers_dm365(&vd->outBufArray, vd->totBuf);

	dvtb_vidDec2Close(vd);
	SYS_OUT("Video Decoder <%s> closed\n", vd->vdec2Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&vd->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_vidDec2Flush_dm365(DvevmStThreadInfo *T, int *nFrames)
{
	int decDuration = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		/* Add logic for flushing display buffers */
		T->g.vdec2.vdec2Cmd = XDM_FLUSH;

		if (DVEVM_ST_FAIL == dvtb_vidDec2Control(&T->g.vdec2))
		{
			SYS_ERROR("Unable to set Flush mode.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		SYS_OUT("Flushing out frames held by Video Decoder\n");

		while ((*nFrames) <= T->g.vdec2.numFrames)
		{
			if (DVEVM_ST_FAIL == dvtb_vidDec2Decode(&T->g.vdec2, &decDuration))
			{
				SYS_ERROR("Process call returned error while flushing display buffers\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}

			T->g.vdec2.vdec2Cmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_vidDec2Control(&T->g.vdec2))
			{
				SYS_ERROR("Unable to get the status of the decoder\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}

			if (0 == T->g.vdec2.vdec2OutArgs.outputID[0])
				break;

			/* O/p logic */
			if (DVEVM_ST_FAIL == dvtb_vidDec2ProcessOutBuff_dm365(&T->g.vpbe, &T->g.vdec2.vdec2Status, &T->g.vdec2.vdec2OutArgs, &T->g.vdec2.vdec2InArgs, &T->g.vdec2.vdec2Params, &T->g.vdec2.vdec2DynParams, &T->g.vdec2.dispBufArray, &T->g.vdec2.outBufArray, T->targetFp, nFrames, 0))
			{
				SYS_ERROR("Unable to process output buffer \n");
				retCode = DVEVM_ST_FAIL;
				break;
			}

			if (DVEVM_ST_USERBUFFER!=T->g.vpbe.opMode)
			{
				dvtb_vidDec2ReleaseOutBuffers(&T->g.vdec2.outBufArray, &T->g.vdec2.vdec2OutArgs.freeBufID);
			}

		}//end of while(displayFrame < (*nFrames))
	} while (DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_validateVIDDEC2(DvevmStThreadInfo *T)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	/* Validate the i/p chroma format to supported formats */
	if ((T->g.vdec2.vdec2Params.forceChromaFormat != XDM_YUV_420SP) && (T->g.vdec2.vdec2Params.forceChromaFormat != XDM_YUV_422ILE) && (T->g.vdec2.vdec2Params.forceChromaFormat != XDM_CHROMAFORMAT_DEFAULT))
	{
		SYS_ERROR("Invalid 'forceChromaFormat'!\n");
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStRetCode
dvtb_vidDec2CompleteBuffInit(DvevmStThreadInfo *T)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		T->g.vdec2.vdec2Cmd = XDM_GETBUFINFO;
		if (DVEVM_ST_FAIL == dvtb_vidDec2Control(&T->g.vdec2))
		{
			SYS_ERROR("Unable to get the buffer requirements for this input stream.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		/*
		 * Allocate more buffers for user-buffer mode to accomodate the buffers locked by driver.
		 */
		if (DVEVM_ST_USERBUFFER==T->g.vpbe.opMode)
		{
			if (T->g.vdec2.vdec2Status.maxNumDisplayBufs<MIN_DISPLAY_BUFFERS)
				T->g.vdec2.vdec2Status.maxNumDisplayBufs = MIN_DISPLAY_BUFFERS;

			T->g.vdec2.vdec2Status.maxNumDisplayBufs+=(MIN_DISPLAY_BUFFERS+1);

			if (T->g.vdec2.vdec2Status.maxNumDisplayBufs>VIDDEC2_PLAY_MAX_BUFFERS)
				T->g.vdec2.vdec2Status.maxNumDisplayBufs=VIDDEC2_PLAY_MAX_BUFFERS;
		}

		//Allocate and initialize all outBuffers
		if (DVEVM_ST_FAIL == dvtb_vidDec2InitAllOutBuffers_dm365(&T->g.vdec2.outBufArray, &T->g.vdec2.vdec2Status, &T->g.vdec2.totBuf, T->g.vdec2.vdec2Status.maxNumDisplayBufs))
		{
			SYS_ERROR("Unable to Initialize other out buffers.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		SYS_DEBUG("All Output buffers initialized.\n");
	} while (DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_VidDec2Play(DvevmStThreadInfo *T)
{
#ifdef DVTB_PERF
	DvevmStTime timeStmpBfrDec, timeStmpAftrDec;
	unsigned int LoopdecDuration;
#endif

	int nBytes = 0, nTotalInputBytes = 0, nFrames = 1, frameSize = 0, bytesConsumed = 0, remainingBytes = 0, displayFrames = 1;
	unsigned int fileSize = 0;
	int decDuration = 0;
	DvevmStXdmBuffer *inbuf = NULL, *outbuf = NULL;
	DvevmStBool vpbeOpened = DVEVM_ST_FALSE, usecaseFailed = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;
	DvevmStBool firstProcessCall = DVEVM_ST_TRUE;

	T->g.vpbe.videoFd = 0;

	/* Quit if source file is not specified */
	if (!T->sourceFp)
	{
		SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
		dvtb_freeThr(T);
		pthread_exit(NULL);
	}

	/* Validate the use-case configuration */
	if (DVEVM_ST_FAIL == dvtb_validateVIDDEC2(T))
	{
		dvtb_freeThr(T);
		pthread_exit(NULL);
	}

	if (NULL == T->targetFp)
	{
		fileBased = DVEVM_ST_FALSE;
	}
	else
		T->g.vpbe.opMode = -1;

	dvtb_vidDec2StartMessage(0, fileBased, T->g.vdec2.vdec2Name);

	// [Decode][Play] scenario
	do
	{
		inbuf = &T->g.vdec2.inBuf;
		outbuf = &T->g.vdec2.outBuf;

		if (DVEVM_ST_FAIL == dvtb_vidDec2HanInit_dm365(&T->g.vdec2, (char *) T->g.eng.name))
		{
			SYS_ERROR("Unable to initialize Video Decoder Handle \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_vidDec2AllocInBuff(&T->g.vdec2.inBuf, &T->g.vdec2.inBufDesc, T->g.vdec2.vdec2Status.bufInfo.minNumInBufs))
		{
			SYS_ERROR("Error in allocating memory for input buffer\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		//Allocate First Output Buffer
		if (DVEVM_ST_FAIL == dvtb_vidDec2InitFirstOutBuffer_dm365(&T->g.vdec2.outBufArray, &T->g.vdec2.vdec2Status, &T->g.vdec2.totBuf))
		{
			SYS_ERROR("Unable to Initialize 1st out buffer.\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		T->g.vdec2.vdec2OutArgs.outBufsInUseFlag = 0;

		SYS_OUT("Video Decoder <%s> initialized\n", T->g.vdec2.vdec2Name);

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
#ifdef DVTB_PERF
			timeStmpBfrDec = dvtb_getTime();
#endif

			if(DVEVM_ST_FAIL == dvtb_fileRead(T->sourceFp, (char *)inbuf->bufs[0], inbuf->bufSizes[0], &nBytes))
			{
				SYS_ERROR("Error in file read \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_DEBUG("Read request = %d; Read %d no of bytes. ErrorValue = %d\n", inbuf->bufSizes[0], nBytes, ferror(T->sourceFp));

			if (0 == nBytes)
			{
				SYS_DEBUG("End of source file reached.\n");
				break;
			}

			T->g.vdec2.vdec2InArgs.numBytes = nBytes;
			T->g.vdec2.inBufDesc.descs[0].buf = (XDAS_Int8 *) ((XDAS_Int32) T->g.vdec2.inBuf.bufs[0]);

			//Set dynamic parameters
			T->g.vdec2.vdec2Cmd = XDM_SETPARAMS;
			if (DVEVM_ST_FAIL == dvtb_vidDec2Control(&T->g.vdec2))
			{
				SYS_ERROR("Unable to set the dynamic params\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_FAIL == dvtb_vidDec2DecProcess(&T->g.vdec2, &decDuration))
			{
				SYS_ERROR("Video decoder process fails\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			frameSize = T->g.vdec2.vdec2OutArgs.bytesConsumed;
			if (0 == frameSize)
			{
				SYS_OUT("Video Decode Process generated 0 bytes. continue decode.\n");
				continue;
			}

			SYS_OUT("Decoded Frame %d.\n", nFrames);
			SYS_DEBUG("Bytes Consumed = %d.\n", frameSize);

#ifdef PERF
			SYS_PERF("Thread, %x, Frame#, %d, Frame Size(bytes), %d, DecTime(us), %d\n", (unsigned int) T, nFrames, frameSize, decDuration);
#endif

			bytesConsumed += frameSize;
			fseek(T->sourceFp, -(nBytes - frameSize), SEEK_CUR);
			remainingBytes -= frameSize;

			/* Complete allocation of all out-buffers and initialize VPBE as per codec returned details */
			if (DVEVM_ST_TRUE == firstProcessCall)
			{
				if (DVEVM_ST_FAIL == dvtb_vidDec2CompleteBuffInit(T))
				{
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}


				if (DVEVM_ST_FALSE != fileBased)
					SYS_OUT("Video [Decode]+[Dump] usecase started\n");

				firstProcessCall = DVEVM_ST_FALSE;
			}

			/*
			 * For driver based use-case, wait till one decoded buffer is ready for display.
			 */
			if ((DVEVM_ST_FALSE == fileBased) && (DVEVM_ST_TRUE != vpbeOpened))
			{
				if ((T->g.vdec2.vdec2OutArgs.outputID[0] > 0) || (T->g.vdec2.vdec2DynParams.frameOrder && (0 == T->g.vdec2.vdec2OutArgs.outBufsInUseFlag)) )
				{
					if (DVEVM_ST_FAIL == dvtb_vidDec2SetUpVPBE(&T->g.vpbe, &T->g.vdec2.vdec2Status, &T->g.vdec2.vdec2OutArgs, &T->g.vdec2.vdec2InArgs, &T->g.vdec2.vdec2Params, &T->g.vdec2.vdec2DynParams, &T->g.vdec2.dispBufArray))
					{
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					vpbeOpened = DVEVM_ST_TRUE;

					SYS_OUT("VPBE device <%s> initialized for display\n", T->g.vpbe.device);

					if(DVEVM_ST_USERBUFFER==T->g.vpbe.opMode)
						dvtb_registerOutBuffToFree(&T->g.vdec2.dispBufArray, &T->g.vdec2.vdec2OutArgs.freeBufID);

					if(DVEVM_ST_USERBUFFER!=T->g.vpbe.opMode)
						dvtb_vidDec2ReleaseOutBuffers(&T->g.vdec2.outBufArray, &T->g.vdec2.vdec2OutArgs.freeBufID);

					continue;
				}
			}

			/* O/p logic */
			if (DVEVM_ST_FAIL == dvtb_vidDec2ProcessOutBuff_dm365(&T->g.vpbe, &T->g.vdec2.vdec2Status, &T->g.vdec2.vdec2OutArgs, &T->g.vdec2.vdec2InArgs, &T->g.vdec2.vdec2Params, &T->g.vdec2.vdec2DynParams, &T->g.vdec2.dispBufArray, &T->g.vdec2.outBufArray, T->targetFp, &displayFrames, 0))
			{
				SYS_ERROR("Unable to process output buffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_USERBUFFER!=T->g.vpbe.opMode)
				dvtb_vidDec2ReleaseOutBuffers(&T->g.vdec2.outBufArray, &T->g.vdec2.vdec2OutArgs.freeBufID);

#ifdef DVTB_PERF
			timeStmpAftrDec = dvtb_getTime();
			LoopdecDuration = ((timeStmpAftrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrDec.tv_usec) - ((timeStmpBfrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrDec.tv_usec);
			SYS_OUT("Frame #, %d, DVTB DecTime(us), %d \n", nFrames, LoopdecDuration);
#endif
			nFrames++;
		} while ((nFrames <= T->g.vdec2.numFrames) && (bytesConsumed >= nTotalInputBytes));// end do-while

		//Flush the held frames only in the case where the usecase has not failed so far
		if (DVEVM_ST_FALSE == usecaseFailed)
		{
			if (DVEVM_ST_FAIL == dvtb_vidDec2Flush_dm365(T, &displayFrames))
			{
				SYS_ERROR("Unable to Flush held frames buffers. \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop


	dvtb_vidDec2ProcessEndMessage_dm365(0, fileBased, displayFrames , T->g.vdec2.vdec2Name);

	if (DVEVM_ST_TRUE == vpbeOpened)
	{
		dvtb_vpbeClose(&T->g.vpbe);
		SYS_OUT("VPBE Device <%s> closed\n", T->g.vpbe.device);
	}

	dvtb_vidDec2HanClose_dm365(&T->g.vdec2, T->g.eng.name);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_vidDec2ExitMessage(0, fileBased, usecaseFailed , T->g.vdec2.vdec2Name);

	dvtb_freeThr(T);
	pthread_exit(NULL);
}

