/*
 * dvtbMPEG4SPPlay2.c
 *
 * XDM1.2 MPEG4 SP Decode Functionality
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

#include "dvtbMPEG4SPPlay2.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbMPEG4SPDec2.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"
#include "dvtbVidPlay2.h"
//#define FOR_DEBUGGING_AT_DSP_END

#define MAX_NUMBER_BUFFER 17
#define PAD_WIDTH (48)

void
dvtb_mpeg4spDec2ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Total # of frames Decoded & Displayed = %d \n", nFrames - 1);
		else
			SYS_OUT("Total # of frames Displayed = %d \n", nFrames - 1);
	}
	else//File based
		SYS_OUT("Total # of frames Decoded & Dumped = %d \n", nFrames - 1);
}


void
dvtb_mpeg4spDec2InitPtrs(DvevmStMPEG4SPDecInfo *vd)
{
	int i = 0, j = 0;

	vd->ceHdl = NULL;
	vd->vdec2Hdl = NULL;

	vd->inBuf.numBufs = 0;
	vd->outBuf.numBufs = 0;
	for(i=0; i<MAX_XDM_BUFS; i++)
	{
		vd->inBuf.bufs[i] = NULL;
		vd->outBuf.bufs[i] = NULL;
	}

	vd->totBuf = 1;

	for(i=0; i<XDM_MAX_BUFFERS; i++)
	{
		vd->outBufArray[i].buffer.numBufs = 0;
		for(j=0; j<MAX_XDM_BUFS; j++)
			vd->outBufArray[i].buffer.bufs[j] = NULL;

		vd->outBufArray[i].isFree = DVEVM_ST_TRUE;
		vd->outBufArray[i].id = i+1;
	}

}

DvevmStRetCode
dvtb_mpeg4spDec2HanInit(DvevmStMPEG4SPDecInfo *vd, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		// Initialize Engine
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &vd->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>.\n",engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

#ifdef FOR_DEBUGGING_AT_DSP_END
		SYS_DEBUG("Engine opened. Now hit enter to debug on the DSP end.");
		getchar();
#endif

		//Initialize Codec Instance
		if (DVEVM_ST_FAIL == dvtb_mpeg4spDec2Init(vd))
		{
			SYS_ERROR("Unable to initialize Video Decoder <%s>.\n",vd->vdec2Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spDec2DeInitOutBuffers(DvevmStMPEG4SPDecInfo *vd)
{
	unsigned int i=0;

	for(i=0; i<vd->totBuf; i++)
	{
		if(0 < vd->outBufArray[i].buffer.numBufs)
			dvtb_freeCmem(&vd->outBufArray[i].buffer);
	}

	return DVEVM_ST_SUCCESS;
}

void
dvtb_mpeg4spDec2HanClose(DvevmStMPEG4SPDecInfo *vd, char *engName)
{
	//Free the allocated Input Buffer
	if(0 < vd->inBuf.numBufs )
		dvtb_freeCmem(&vd->inBuf);

	//Free all the allocated output buffers
	dvtb_mpeg4spDec2DeInitOutBuffers(vd);

	dvtb_mpeg4spDec2Close(vd);
	SYS_OUT("Video Decoder <%s> closed.\n", vd->vdec2Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&vd->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>.\n", engName);
	else
		SYS_OUT("Engine <%s> closed.\n", engName);
}

DvevmStRetCode
dvtb_mpeg4spDec2InBuffAlloc(DvevmStXdmBuffer *inBuf, XDM1_BufDesc *inBufDesc, int minNumInBufs)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		//Allocate the contig memory for inBuf
		if (DVEVM_ST_FAIL == dvtb_allocCmem(inBuf))
		{
			SYS_ERROR("Unable to allocate memory for input buffer. \n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		//Assign the buffer pointers accordingly.
		inBufDesc->numBufs = inBuf->numBufs;

		for (i = 0; i < minNumInBufs; i++)
		{
			inBufDesc->descs[i].buf = (XDAS_Int8 *) inBuf->bufs[i];
			inBufDesc->descs[i].bufSize = inBuf->bufSizes[i];
		}
	}while(DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

DvevmStMPEG4Dec2BufElement*
dvtb_mpeg4spDec2AllocOutBuffer(DvevmStMPEG4SPDecInfo *vd)
{
	unsigned int i=0;

	for(i=0; i<vd->totBuf; i++)
	{
		if(vd->outBufArray[i].isFree == DVEVM_ST_TRUE)
		{
			vd->outBufArray[i].isFree = DVEVM_ST_FALSE;
			return &vd->outBufArray[i];
		}
	}

	return NULL;
}

DvevmStRetCode
dvtb_mpeg4spDec2DecProcess(DvevmStMPEG4SPDecInfo *vd, int *decDuration)
{
	int frameSize = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	DvevmStMPEG4Dec2BufElement *freeBufElement=NULL;

	do
	{
		if(!vd->mpeg4sp_vdecOutArgs.viddecOutArgs.outBufsInUseFlag)
		{
			freeBufElement = dvtb_mpeg4spDec2AllocOutBuffer(vd);
			if(NULL == freeBufElement)
			{
				SYS_ERROR("No more free out buffers in the pool that can be allocated for processing.\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}

			vd->outBufDesc.numBufs = freeBufElement->buffer.numBufs;
			vd->outBufDesc.bufSizes = (XDAS_Int32 *) freeBufElement->buffer.bufSizes;
			vd->outBufDesc.bufs = (XDAS_Int8 **) freeBufElement->buffer.bufs;
			vd->mpeg4sp_vdecInArgs.viddecInArgs.inputID = freeBufElement->id;
		}

		// Make a Decode Process call
		if (DVEVM_ST_FAIL == dvtb_mpeg4spDec2Decode(vd, decDuration))
		{
			SYS_ERROR("Unable to decode <%s>. \n",vd->vdec2Name);

			vd->vdecCmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_mpeg4spDec2Control(vd))
				SYS_ERROR("Unable to get the status. \n");
			else
				SYS_ERROR("Codec Error = %d.\n", (int) vd->mpeg4sp_vdecStatus.viddecStatus.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

		frameSize = vd->mpeg4sp_vdecOutArgs.viddecOutArgs.bytesConsumed;
		if (0 != frameSize)
		{
			vd->vdecCmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_mpeg4spDec2Control(vd))
			{
				SYS_ERROR("Unable to get the status. \n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spDec2Copy(DvevmStThreadInfo *T, char *out_buff, char *in_buff, int size)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	memcpy(out_buff, in_buff, size);

	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spDec2DisplayOutputData(DvevmStThreadInfo *T, char *in_buff, int size)
{
	void *displayBuffer=NULL;
	DvevmStVpbeInfo *vpbe = &T->g.vpbe;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	displayBuffer = dvtb_vpbeGetDisplayBuffer(vpbe);
	if(NULL == displayBuffer)
	{
		SYS_ERROR("Unable to get the Display buffer.\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2Copy(T, (char *)displayBuffer, in_buff, size))
		{
			SYS_ERROR("Unable to copy in display buffer.\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			if(DVEVM_ST_FAIL == dvtb_vpbeDisplay(vpbe, displayBuffer))
			{
				SYS_ERROR("Unable to display output buffer.\n");
				retCode = DVEVM_ST_FAIL;
			}
		}
	}
	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spDec2WriteOutputData(IVIDEO1_BufDesc *displayBuf, FILE *fOutFile)
{
	int i=0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	for(i=0; i<displayBuf->numBufs; i++)
	{
		if(DVEVM_ST_FAIL ==  dvtb_fileWrite(fOutFile, (char *)displayBuf->bufDesc[i].buf, displayBuf->bufDesc[i].bufSize))
		{
			SYS_ERROR("Error in writing to file.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

	}
	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spDec2ProcessOutBuff(DvevmStThreadInfo *T, DvevmStMPEG4SPDecInfo *vd, FILE *fp, DvevmStBool fileBased, int nFrames, int *displayFrame)
{
	int validOutIds = 0, frames = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	frames = *displayFrame;
	//Check for Frame ready via outputID array and display buffer pointers
	validOutIds = 0;

	if(vd->mpeg4sp_vdecDynParams.viddecDynamicParams.frameOrder)
	{
		if(DVEVM_ST_TRUE == fileBased)
		{
			if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2WriteOutputData(&vd->mpeg4sp_vdecOutArgs.viddecOutArgs.decodedBufs, fp))
			{
				SYS_ERROR("Unable to Dump frame # %d. \n",frames);
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_OUT("Dumped Frame# <%d>.\n", frames);
				frames++;
			}
		}
		else
		{
			if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2DisplayOutputData(T, (char *)vd->mpeg4sp_vdecOutArgs.viddecOutArgs.decodedBufs.bufDesc[0].buf, vd->mpeg4sp_vdecOutArgs.viddecOutArgs.decodedBufs.bufDesc[0].bufSize))
			{
				SYS_ERROR("Unable to display frame # %d .\n",frames);
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_OUT("Displayed Frame# %d.\n", frames);
				frames++;
			}
		}
	}
	else
	{
		while(vd->mpeg4sp_vdecOutArgs.viddecOutArgs.outputID[validOutIds] > 0)
		{
			SYS_DEBUG("Valid output id = %d\n",validOutIds);

			if(DVEVM_ST_TRUE == fileBased)
			{
				SYS_DEBUG("Frame #%d, OutputId %d.\n", nFrames, (int)vd->mpeg4sp_vdecOutArgs.viddecOutArgs.outputID[validOutIds]);
				if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2WriteOutputData(&vd->mpeg4sp_vdecOutArgs.viddecOutArgs.displayBufs[validOutIds], fp))
				{
					SYS_ERROR("Unable to Dump frame # %d. \n",frames);
					retCode = DVEVM_ST_FAIL;
					break;
				}
				SYS_OUT("Dumped Frame# <%d>.\n", frames);
				frames++;
			}
			else
			{
				if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2DisplayOutputData(T, (char *)vd->mpeg4sp_vdecOutArgs.viddecOutArgs.displayBufs[validOutIds].bufDesc[0].buf, vd->mpeg4sp_vdecOutArgs.viddecOutArgs.displayBufs[validOutIds].bufDesc[0].bufSize))
				{
					SYS_ERROR("Unable to display frame # %d .\n",frames);
					retCode = DVEVM_ST_FAIL;
					break;
				}
	
				SYS_OUT("Displayed Frame# %d.\n", frames);
				frames++;
			}
	
			validOutIds++;
		}
	}

	*displayFrame = frames;
	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spDec2Flush(DvevmStThreadInfo *T, DvevmStMPEG4SPDecInfo *vd, FILE *fp, DvevmStBool fileBased, int nFrames, int *displayFrame)
{
	int decDuration = 0, validOutIds = 0, frames = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	frames = *displayFrame;
	do
	{
		/* Add logic for flushing display buffers */
		vd->vdecCmd = XDM_FLUSH;

		if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2Control(vd))
		{
			SYS_ERROR("Unable to set Flush mode.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		SYS_OUT("Flushing out frames held by Video Decoder.\n");

		validOutIds = 0;
		while(frames < nFrames)
		{
			if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2Decode(vd, &decDuration))
			{
				SYS_ERROR("Process call returned error while flushing display buffers.\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}

			vd->vdecCmd = XDM_GETSTATUS;
			if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2Control(vd))
			{
				SYS_ERROR("Unable to get the status of the decoder.\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}

			if(0 == vd->mpeg4sp_vdecOutArgs.viddecOutArgs.outputID[validOutIds])
				break;

			if(DVEVM_ST_TRUE == fileBased)
			{
				SYS_DEBUG("Held Frame, OutputId %d.\n", (int)vd->mpeg4sp_vdecOutArgs.viddecOutArgs.outputID[validOutIds]);
				if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2WriteOutputData(&vd->mpeg4sp_vdecOutArgs.viddecOutArgs.displayBufs[validOutIds], fp))
				{
					SYS_ERROR("Unable to Dump frame # %d. \n",frames);
					retCode = DVEVM_ST_FAIL;
					break;
				}
				SYS_OUT("Dumped Frame# <%d>.\n", frames);
			}
			else
			{
				if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2DisplayOutputData(T, (char *)vd->mpeg4sp_vdecOutArgs.viddecOutArgs.displayBufs[validOutIds].bufDesc[0].buf, vd->mpeg4sp_vdecOutArgs.viddecOutArgs.displayBufs[validOutIds].bufDesc[0].bufSize))
				{
					SYS_ERROR("Unable to display frame # %d .\n",frames);
					retCode = DVEVM_ST_FAIL;
					break;
				}

				SYS_OUT("Displayed Frame# %d.\n", frames);
			}
			frames++;
		}
	}while (DVEVM_ST_FALSE);

	*displayFrame = frames;
	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spDec2InitFirstOutBuffer(DvevmStMPEG4SPDecInfo *vd)
{
	int i=0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	vd->outBufArray[0].buffer.numBufs = vd->mpeg4sp_vdecStatus.viddecStatus.bufInfo.minNumOutBufs;
	for(i=0; i<vd->mpeg4sp_vdecStatus.viddecStatus.bufInfo.minNumOutBufs; i++)
		vd->outBufArray[0].buffer.bufSizes[i] = vd->mpeg4sp_vdecStatus.viddecStatus.bufInfo.minOutBufSize[i];

	if(DVEVM_ST_FAIL == dvtb_allocCmem(&vd->outBufArray[0].buffer))
	{
		SYS_ERROR("Unable to allocate memory for 1st outBuf in the outBuf pool\n");
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spDec2InitAllOutBuffers(DvevmStMPEG4SPDecInfo *vd)
{
	unsigned int i = 0, j = 0;
	int maxBufs = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	vd->vdecCmd = XDM_GETBUFINFO;
	if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2Control(vd))
	{
		SYS_ERROR("Unable to get the buffer requirements for this input stream.\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		maxBufs = vd->mpeg4sp_vdecStatus.viddecStatus.maxNumDisplayBufs;
		SYS_DEBUG("maxBufs = %d.\n",maxBufs);

		for(j=1; j<maxBufs; j++)
		{
			vd->outBufArray[j].buffer.numBufs = vd->mpeg4sp_vdecStatus.viddecStatus.bufInfo.minNumOutBufs;
		    for(i=0; i<vd->mpeg4sp_vdecStatus.viddecStatus.bufInfo.minNumOutBufs; i++)
		    	vd->outBufArray[j].buffer.bufSizes[i] = vd->mpeg4sp_vdecStatus.viddecStatus.bufInfo.minOutBufSize[i];
		}

		for(i=1; i<maxBufs; i++)
		{
			if(DVEVM_ST_FAIL == dvtb_allocCmem(&vd->outBufArray[i].buffer))
			{
				SYS_ERROR("Unable to allocate memory for <%d> outBuf in the outBuf pool\n", i);
				retCode = DVEVM_ST_FAIL;
			}
		}
		vd->totBuf = maxBufs;

	}

	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spDec2ReleaseBuffers(DvevmStMPEG4SPDecInfo *vd, unsigned int freeBufIds[])
{
	unsigned int i=0, id=0;

	for(i=0; i<vd->totBuf; i++)
	{
		id = freeBufIds[i];

		/*
		 * Check if the buffer Id = 0 condition has reached. zero is not a
		 * valid buffer Id hence that value is used to identify the end of
		 * buffer array
		 */
		if(id == 0)
			break;

		/*
		 * convert the buffer-Id to its corresponding index in the global
		 * array
		 */
		id--;
		// Set the status of the buffer to FREE
		vd->outBufArray[id].isFree = DVEVM_ST_TRUE;
	}

	return DVEVM_ST_SUCCESS;
}

void
dvtb_Mpeg4spDec2Play(DvevmStThreadInfo *T)
{
	int nBytes = 0, nTotalInputBytes = 0, nFrames = 1, frameSize = 0, displayFrame = 1,
		bytesConsumed = 0, decDuration = 0, buffSize = 0, alreadyReadBytes = 0;
	unsigned int fileSize = 0,remainingBytes = 0;

	DvevmStRetCode status = DVEVM_ST_FAIL;
	DvevmStXdmBuffer *inbuf = NULL, *outbuf = NULL, dispBuff;
	DvevmStBool vpbeSetup = DVEVM_ST_FALSE, usecaseFailed = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE,
		firstProcessCall = DVEVM_ST_TRUE;

	T->g.vpbe.videoFd = 0;

	/* Quit if source file is not specified */
	if (!T->sourceFp)
	{
		SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	if (!T->targetFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_DECODE, "Mpeg4", T->useAlgorithm, fileBased);
	dvtb_mpeg4spDec2InitPtrs(&T->g.mpeg4spdec2);
	dvtb_vidDec2InitVpbeBuff(&T->g.vpbe);

	// [Decode][Play] scenario
	do
	{
		if (T->useAlgorithm)
		{
			inbuf = (DvevmStXdmBuffer *) &T->g.mpeg4spdec2.inBuf;
			outbuf = (DvevmStXdmBuffer *) &T->g.mpeg4spdec2.outBuf;

			if (DVEVM_ST_FAIL == dvtb_mpeg4spDec2HanInit(&T->g.mpeg4spdec2, (char *)T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Video Decoder Play \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_FAIL == dvtb_mpeg4spDec2InBuffAlloc(&T->g.mpeg4spdec2.inBuf, &T->g.mpeg4spdec2.inBufDesc, T->g.mpeg4spdec2.mpeg4sp_vdecStatus.viddecStatus.bufInfo.minNumInBufs))
			{
				SYS_ERROR("Error in allocating memory for input buffer\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Allocate First Output Buffer
			if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2InitFirstOutBuffer(&T->g.mpeg4spdec2))
			{
				SYS_ERROR("Unable to Initialize 1st out buffer.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			T->g.mpeg4spdec2.mpeg4sp_vdecOutArgs.viddecOutArgs.outBufsInUseFlag	= 0;
			buffSize = T->g.mpeg4spdec2.outBufArray[0].buffer.bufSizes[0];

			SYS_OUT("Video Decoder <%s> initialized\n",	T->g.mpeg4spdec2.vdec2Name);
		}
		else
		{
			dispBuff.numBufs = 1;
			dispBuff.bufSizes[0] = T->g.vpbe.imageWidth * T->g.vpbe.imageHeight	* 2;

			if (DVEVM_ST_FAIL == dvtb_allocCmem(&dispBuff))
			{
				SYS_ERROR("Unable to allocate memory for video playback\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			inbuf = outbuf = &dispBuff;
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
				SYS_ERROR("Unable to setup VPBE device <%s> for display\n",	T->g.vpbe.device);
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


			vpbeSetup = DVEVM_ST_TRUE;
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
			if(DVEVM_ST_FAIL == dvtb_fileRead(T->sourceFp, (char *)inbuf->bufs[0], inbuf->bufSizes[0], &nBytes))
			{
				SYS_ERROR("Error in file read \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}


			SYS_DEBUG("Read request = %d; Read %d no of bytes. ErrorValue = %d\n", inbuf->bufSizes[0], nBytes, ferror(T->sourceFp));

			if (0 == nBytes|| ( (nBytes <= 4) && (XDM_LE_32 == T->g.mpeg4spdec2.mpeg4sp_vdecParams.viddecParams.dataEndianness)))
			{
				SYS_OUT("End of source file reached. Exiting ...\n");
				break;
			}

			if (T->useAlgorithm)
			{
				T->g.mpeg4spdec2.mpeg4sp_vdecInArgs.viddecInArgs.numBytes = nBytes;
				T->g.mpeg4spdec2.inBufDesc.descs[0].buf = (XDAS_Int8 *) ((XDAS_Int32) T->g.mpeg4spdec2.inBuf.bufs[0]);

				if (DVEVM_ST_FAIL == dvtb_mpeg4spDec2DecProcess(&T->g.mpeg4spdec2, &decDuration))
				{
					SYS_ERROR("Video decoder process fails for frame # %d \n", nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				frameSize = T->g.mpeg4spdec2.mpeg4sp_vdecOutArgs.viddecOutArgs.bytesConsumed;
				if (0 == frameSize)
				{
					SYS_OUT( "Video Decode Process generated 0 bytes. continue decode.\n");
					continue;
				}
				SYS_OUT("Decoded Frame %d\n", nFrames);
#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Frame Size(bytes), %d, DecTime(us), %d\n",(unsigned int) T, nFrames, frameSize, decDuration);
#endif

				nFrames++;
				SYS_DEBUG("Bytes Consumed = %d.\n", frameSize);
				if(XDM_LE_32 == T->g.mpeg4spdec2.mpeg4sp_vdecParams.viddecParams.dataEndianness)
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
					if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2InitAllOutBuffers(&T->g.mpeg4spdec2))
					{
						SYS_ERROR("Unable to Initialize other out buffers.\n");
						dvtb_mpeg4spDec2DeInitOutBuffers(&T->g.mpeg4spdec2);
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					SYS_DEBUG("All Output buffers initialized.\n");
				}

				if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2ProcessOutBuff(T, &T->g.mpeg4spdec2, T->targetFp, fileBased, nFrames, &displayFrame))
				{
					SYS_ERROR("Unable to Process Out buffers. \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}


				dvtb_mpeg4spDec2ReleaseBuffers(&T->g.mpeg4spdec2, (unsigned int *)T->g.mpeg4spdec2.mpeg4sp_vdecOutArgs.viddecOutArgs.freeBufID);

			}
			else
			{
				if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2DisplayOutputData(T, (char *)inbuf->bufs[0], inbuf->bufSizes[0]))
				{
					SYS_ERROR("Unable to display frame # %d .\n",displayFrame);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
				SYS_OUT("Displayed Frame# %d.\n", displayFrame);
				nFrames++;
				displayFrame++;
			}

		} while ((nFrames <= T->g.mpeg4spdec2.numFrames) && (bytesConsumed >= nTotalInputBytes));// end do-while

		//Flush the held frames only in the case where the usecase has not failed so far
		if(DVEVM_ST_FALSE == usecaseFailed && T->useAlgorithm)
		{
			if(DVEVM_ST_FAIL == dvtb_mpeg4spDec2Flush(T, &T->g.mpeg4spdec2, T->targetFp, fileBased, nFrames, &displayFrame))
			{
				SYS_ERROR("Unable to Flush Held frames buffers. \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_mpeg4spDec2ProcessEndMessage(T->useAlgorithm, fileBased, displayFrame);

	if (DVEVM_ST_TRUE == vpbeSetup)
	{
		dvtb_vpbeClose(&T->g.vpbe);
		SYS_OUT("VPBE Device <%s> closed\n", T->g.vpbe.device);
	}


	if (T->useAlgorithm)
	{
		dvtb_mpeg4spDec2HanClose(&T->g.mpeg4spdec2, T->g.eng.name);
	}
	else
		dvtb_freeCmem(&dispBuff);

	if(DVEVM_ST_FAIL == dvtb_vidDec2VpbeBuffFree(&T->g.vpbe))
	{
		SYS_ERROR("Unable to Free VPBE buffers. \n");
		usecaseFailed = DVEVM_ST_TRUE;
	}


	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_DECODE, "Mpeg4", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}

