/*
 * dvtbDVREncDec.c
 *
 * XDM1.0 DVR Encode Decode functionality
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

#include "dvtbDVREncDec.h"
#include "dvtbDVREncDecDef.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

DvevmStRetCode
dvtb_DVREncDecMpeg4spEnc1InBuffAlloc(DvevmStXdmBuffer *inBuf, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		if(DVEVM_ST_TRUE == fileBased)
		{
			//Allocate the contig memory for inBuf
			if (DVEVM_ST_FAIL == dvtb_allocCmem(inBuf))
			{
				SYS_ERROR("Unable to allocate memory for input buffer\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
			for (i = 0; i < inBuf->numBufs; i++)
				memset(inBuf->bufs[i], 0, inBuf->bufSizes[i]);
		}
		else
		{
			for(i = 0; i < inBuf->numBufs; i++)
				inBuf->bufs[i] = NULL;
		}

		//Assign the buffer pointers accordingly.
		inBufDesc->numBufs = inBuf->numBufs;

		for (i = 0; i < inBufDesc->numBufs; i++)
		{
			inBufDesc->bufDesc[i].bufSize = inBuf->bufSizes[i];
			inBufDesc->bufDesc[i].buf = (XDAS_Int8 *) inBuf->bufs[i];
		}

	}while(DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

DvevmStRetCode
dvtb_DVREncDecMpeg4spEnc1OutBuffAlloc(DvevmStXdmBuffer *outBuf, XDM_BufDesc *outBufDesc)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_FAIL == dvtb_allocCmem(outBuf))
	{
		SYS_ERROR("Unable to allocate memory for output buffer\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		outBufDesc->numBufs = outBuf->numBufs;
		outBufDesc->bufSizes = (XDAS_Int32 *) outBuf->bufSizes;
		outBufDesc->bufs = (XDAS_Int8 **) outBuf->bufs;
	}

	return retCode;
}

void
dvtb_DVREncDecMpeg4spEnc1InitPtrs(DvevmStMPEG4SPVEncInfo *ve)
{
	int i = 0;

	ve->ceHdl = NULL;
	ve->venc1Hdl = NULL;

	ve->inBuf.numBufs = 0;
	ve->outBuf.numBufs = 0;
	for(i=0; i<MAX_XDM_BUFS; i++)
	{
		ve->inBuf.bufs[i] = NULL;
		ve->outBuf.bufs[i] = NULL;
	}
}

DvevmStRetCode
dvtb_DVREncDecMpeg4spEnc1ReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, IVIDEO1_BufDescIn *inBufDesc, int fileBased)
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
		else
			inBufDesc->bufDesc[0].buf = (XDAS_Int8 *)vpfe->buffers[vpfe->buf.index].start;
	}
	else
	{
		for(i=0; i < inBufDesc->numBufs; i++)
		{
			if(DVEVM_ST_FAIL == dvtb_fileRead(fp, (char *)inBufDesc->bufDesc[i].buf, inBufDesc->bufDesc[i].bufSize, &nBytes))
			{
				SYS_ERROR("Error in file read \n");
				retCode = DVEVM_ST_FAIL;
			}
		}

	}

	return retCode;
}

DvevmStRetCode
dvtb_DVREncDecMpeg4spEnc1EncProcess(DvevmStMPEG4SPVEncInfo *ve , int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		// Make video encode process call
		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Encode(ve, encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");

			ve->venc1Cmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Control(ve))
				SYS_ERROR("Unable to get the status\n");
			else
				SYS_ERROR("Codec Error = %d\n", (int) ve->venc1Status.videncStatus.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

		ve->venc1Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Control(ve))
		{
			SYS_ERROR("Unable to get the status\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_DVREncDecMpeg4spDec2InitPtrs(DvevmStMPEG4SPDecInfo *vd)
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
dvtb_DVREncDecMpeg4spDec2DeInitOutBuffers(DvevmStMPEG4SPDecInfo *vd)
{
	unsigned int i=0;

	for(i=0; i<vd->totBuf; i++)
	{
		if(0 < vd->outBufArray[i].buffer.numBufs)
			dvtb_freeCmem(&vd->outBufArray[i].buffer);
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_DVREncDecMpeg4spDec2InBuffAlloc(DvevmStXdmBuffer *inBuf, XDM1_BufDesc *inBufDesc, int minNumInBufs)
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
dvtb_DVREncDecMpeg4spDec2AllocOutBuffer(DvevmStMPEG4SPDecInfo *vd)
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
dvtb_DVREncDecMpeg4spDec2DecProcess(DvevmStMPEG4SPDecInfo *vd, int *decDuration)
{
	int frameSize = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	DvevmStMPEG4Dec2BufElement *freeBufElement=NULL;

	do
	{
		if(!vd->mpeg4sp_vdecOutArgs.viddecOutArgs.outBufsInUseFlag)
		{
			freeBufElement = dvtb_DVREncDecMpeg4spDec2AllocOutBuffer(vd);
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
dvtb_DVREncDecMpeg4spDec2Copy(DvevmStThreadInfo *T, char *out_buff, char *in_buff, int size)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	memcpy(out_buff, in_buff, size);

	return retCode;
}

DvevmStRetCode
dvtb_DVREncDecMpeg4spDec2DisplayOutputData(DvevmStThreadInfo *T, char *in_buff, int size)
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
		if(DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spDec2Copy(T, (char *)displayBuffer, in_buff, size))
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
dvtb_DVREncDecMpeg4spDec2WriteOutputData(IVIDEO1_BufDesc *displayBuf, FILE *fOutFile)
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
dvtb_DVREncDecMpeg4spDec2ProcessOutBuff(DvevmStThreadInfo *T, DvevmStMPEG4SPDecInfo *vd, FILE *fp, DvevmStBool fileBased, int nFrames, int *displayFrame)
{
	int validOutIds = 0, frames = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	frames = *displayFrame;
	//Check for Frame ready via outputID array and display buffer pointers
	validOutIds = 0;
	while(vd->mpeg4sp_vdecOutArgs.viddecOutArgs.outputID[validOutIds] > 0)
	{
		SYS_DEBUG("Valid output id = %d\n",validOutIds);

		if(DVEVM_ST_TRUE == fileBased)
		{
			SYS_DEBUG("Frame #%d, OutputId %d.\n", nFrames, (int)vd->mpeg4sp_vdecOutArgs.viddecOutArgs.outputID[validOutIds]);
			if(DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spDec2WriteOutputData(&vd->mpeg4sp_vdecOutArgs.viddecOutArgs.displayBufs[validOutIds], fp))
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
			if(DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spDec2DisplayOutputData(T, (char *)vd->mpeg4sp_vdecOutArgs.viddecOutArgs.displayBufs[validOutIds].bufDesc[0].buf, vd->mpeg4sp_vdecOutArgs.viddecOutArgs.displayBufs[validOutIds].bufDesc[0].bufSize))
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

	*displayFrame = frames;
	return retCode;
}

DvevmStRetCode
dvtb_DVREncDecMpeg4spDec2Flush(DvevmStThreadInfo *T, DvevmStMPEG4SPDecInfo *vd, FILE *fp, DvevmStBool fileBased, int nFrames, int *displayFrame)
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
				if(DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spDec2WriteOutputData(&vd->mpeg4sp_vdecOutArgs.viddecOutArgs.displayBufs[validOutIds], fp))
				{
					SYS_ERROR("Unable to Dump frame # %d. \n",frames);
					retCode = DVEVM_ST_FAIL;
					break;
				}
				SYS_OUT("Dumped Frame# <%d>.\n", frames);
			}
			else
			{
				if(DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spDec2DisplayOutputData(T, (char *)vd->mpeg4sp_vdecOutArgs.viddecOutArgs.displayBufs[validOutIds].bufDesc[0].buf, vd->mpeg4sp_vdecOutArgs.viddecOutArgs.displayBufs[validOutIds].bufDesc[0].bufSize))
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
dvtb_DVREncDecMpeg4spDec2InitFirstOutBuffer(DvevmStMPEG4SPDecInfo *vd)
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
dvtb_DVREncDecMpeg4spDec2InitAllOutBuffers(DvevmStMPEG4SPDecInfo *vd)
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
dvtb_DVREncDecMpeg4spDec2ReleaseBuffers(DvevmStMPEG4SPDecInfo *vd, unsigned int freeBufIds[])
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

/*
DVREncDec: DVR Use-case 2
4 channels of SIF (enc + dec)
*/
void
dvtb_DVREncDec(DvevmStThreadInfo *T)
{

	int i = 0, j = 0, maxFrames = 0, nFrames = 1, frameSize = 0, displayFrame = 1,
		nBytes = 0, instanceCount = MAX_DVRENCDEC_MPEG4_INSTANCES,
		encDuration[MAX_DVRENCDEC_MPEG4_INSTANCES] = { 0 },
		decDuration[MAX_DVRENCDEC_MPEG4_INSTANCES] = { 0 };

	char mvFile[MAX_DVRENCDEC_MPEG4_INSTANCES][20];

	FILE *fMVFile[MAX_DVRENCDEC_MPEG4_INSTANCES];
	FILE *sourceFp[MAX_DVRENCDEC_MPEG4_INSTANCES], *decOutputFp[MAX_DVRENCDEC_MPEG4_INSTANCES];

	DvevmStXdmBuffer *inbuf[MAX_DVRENCDEC_MPEG4_INSTANCES] = { NULL },
		*outbuf[MAX_DVRENCDEC_MPEG4_INSTANCES] = { NULL };

	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, firstProcessCall[MAX_DVRENCDEC_MPEG4_INSTANCES];
	DvevmStRetCode retVal = DVEVM_ST_SUCCESS;

	retVal = dvtb_openSrcTrgFromInputFile(T->sourceFp, sourceFp, decOutputFp, MAX_DVRENCDEC_MPEG4_INSTANCES);

	if (DVEVM_ST_FAIL == retVal)
	{
		SYS_ERROR("Improper Input File. Exiting...\n");
		for (j = 0; j < MAX_DVRENCDEC_MPEG4_INSTANCES; j++)
		{
			dvtb_fileClose(&sourceFp[j], &decOutputFp[j]);
		}

		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	dvtb_startMessage(DVEVM_ST_ENCDEC, "DVREncDec", DVEVM_ST_TRUE, DVEVM_ST_TRUE);

	T->g.vpfe.capFd = 0;
	maxFrames = T->g.DVREncDec.numFrames;

	SYS_DEBUG("DVREncDec started\n");
	SYS_DEBUG("Number of frames to encode + decode: %d\n", maxFrames);

	for (i = 0; i < instanceCount; i++)
	{
		dvtb_DVREncDecMpeg4spEnc1InitPtrs(&T->g.DVREncDec.enc[i]);
		dvtb_DVREncDecMpeg4spDec2InitPtrs(&T->g.DVREncDec.dec[i]);
		firstProcessCall[i] = DVEVM_ST_TRUE;
	}

	/* Dummy loop to enable easy cleanup */
	do
	{
		for (i = 0; i < instanceCount; i++)
		{
			sprintf(mvFile[i], "mvdump-%d.txt", i);
			if( DVEVM_ST_FAIL == dvtb_fileOpen(&fMVFile[i], mvFile[i], "w"))
			{
				SYS_ERROR("DVTB file open failed for <%s>\n", mvFile[i]);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}

		if (DVEVM_ST_FAIL == dvtb_ceInit(T->g.eng.name, &T->g.DVREncDec.ceHdl))
		{
			SYS_ERROR("Cannot initialize Engine <%s>\n", T->g.eng.name);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		/* Initialize Video Encoder */
		for (i = 0; i < instanceCount; i++)
		{
			T->g.DVREncDec.enc[i].ceHdl = T->g.DVREncDec.ceHdl;

			if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Init(&T->g.DVREncDec.enc[i]))
			{
				SYS_ERROR("Unable to initialize Video Encoder <%s> for EncDecInstance# %d\n", T->g.DVREncDec.enc[i].venc1Name, i);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
		if(DVEVM_ST_TRUE == usecaseFailed)//Proceed only if usecase is successful
			break;

		//Initialize decoders in and out bufs.
		for (j = 0; j < instanceCount; j++)
		{
			inbuf[j] = (DvevmStXdmBuffer *) &T->g.DVREncDec.dec[j].inBuf;
			outbuf[j] = (DvevmStXdmBuffer *) &T->g.DVREncDec.dec[j].outBuf;

			inbuf[j]->numBufs = 0;
			outbuf[j]->numBufs = 0;

			T->g.DVREncDec.dec[j].mpeg4sp_vdecInArgs.viddecInArgs.size = sizeof(T->g.DVREncDec.dec[j].mpeg4sp_vdecInArgs);
			T->g.DVREncDec.dec[j].mpeg4sp_vdecOutArgs.viddecOutArgs.size = sizeof(T->g.DVREncDec.dec[j].mpeg4sp_vdecOutArgs);
		}

		/* Initialize Video Decoder */
		for (i = 0; i < instanceCount; i++)
		{
			T->g.DVREncDec.dec[i].ceHdl = T->g.DVREncDec.ceHdl;

			if (DVEVM_ST_FAIL == dvtb_mpeg4spDec2Init(&T->g.DVREncDec.dec[i]))
			{
				SYS_ERROR("Unable to initialize Video Decoder <%s> for EncDecInstance# %d\n", T->g.DVREncDec.enc[i].venc1Name, i);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
		if(DVEVM_ST_TRUE == usecaseFailed)//Proceed only if usecase is successful
			break;

		//Allocate input and output buffer
		for (j = 0; j < instanceCount; j++)
		{
			SYS_DEBUG("Instance# %d: T->g.DVREncDec.enc[j].inBuf.NumBufs %d\n", j, (int) T->g.DVREncDec.enc[j].inBufDesc.numBufs);

			if (DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spEnc1InBuffAlloc(&T->g.DVREncDec.enc[j].inBuf, &T->g.DVREncDec.enc[j].inBufDesc, DVEVM_ST_TRUE))
			{
				SYS_ERROR("Error in allocating memory for Encoder input buffer for EncDec Instance# %d \n",j);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_DEBUG("Instance# %d: T->g.DVREncDec.enc[j].outBuf.NumBufs %d\n", j, (int) T->g.DVREncDec.enc[j].outBufDesc.numBufs);
			if (DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spEnc1OutBuffAlloc(&T->g.DVREncDec.enc[j].outBuf, &T->g.DVREncDec.enc[j].outBufDesc))
			{
				SYS_ERROR("Error in allocating memory for Encoder output buffer for EncDec Instance# %d \n", j);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Allocate First Output Buffer
			if(DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spDec2InitFirstOutBuffer(&T->g.DVREncDec.dec[j]))
			{
				SYS_ERROR("Unable to Initialize 1st out buffer.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			T->g.DVREncDec.dec[j].mpeg4sp_vdecOutArgs.viddecOutArgs.outBufsInUseFlag = 0;
		}
		if(DVEVM_ST_TRUE == usecaseFailed)//Proceed only if usecase is successful
			break;

		SYS_OUT("Video Encoders & Decoders <TotalInstances %d> initialized\n", instanceCount);


		/* Start the [capture][encode] process */
		while (nFrames <= maxFrames)
		{
			for (j = 0; j < instanceCount; j++)
			{
				//Read Input
				if(DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spEnc1ReadInput(NULL, sourceFp[j], &T->g.DVREncDec.enc[j].inBufDesc, DVEVM_ST_TRUE))
				{
					SYS_ERROR("Error in Read Input For Instance # %d \n", j);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				if (feof(sourceFp[j]))
				{
					SYS_DEBUG("End of source file reached for EncDecInstance# %d.  Exiting ...\n", j);
					break;
				}

				SYS_DEBUG("Instance# %d: Read Input for Frame# %d\n", j, nFrames);

				//Encode frame
				if(DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spEnc1EncProcess(&T->g.DVREncDec.enc[j], &encDuration[j]))
				{
					SYS_ERROR("EncDecInstance# %d: Unable to encode the input buffer.\n", j);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				SYS_DEBUG("Instance# %d: Encoded Frame# %d\n", j, nFrames);
				SYS_DEBUG("Instance# %d: Bytes Generated %d\n", j, (int) T->g.DVREncDec.enc[j].venc1OutArgs.videncOutArgs.bytesGenerated);

				//Assign input for decoder
				nBytes = T->g.DVREncDec.enc[j].venc1OutArgs.videncOutArgs.bytesGenerated;
				if (0 == nBytes)
				{
					SYS_OUT(" Generated bytes from Encoder is zero: Exiting.\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
				T->g.DVREncDec.dec[j].mpeg4sp_vdecInArgs.viddecInArgs.numBytes = nBytes;
				T->g.DVREncDec.dec[j].inBufDesc.descs[0].buf = (XDAS_Int8 *) ((XDAS_Int32) T->g.DVREncDec.enc[j].outBufDesc.bufs[0]);


				//Decode
				if (DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spDec2DecProcess(&T->g.DVREncDec.dec[j], &decDuration[j]))
				{
					SYS_ERROR("Instance# %d: Video decoder process fails for frame # %d \n",j, nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				SYS_DEBUG("Instance# %d: Decoded Frame# %d.\n", j, nFrames);

				frameSize = T->g.DVREncDec.dec[j].mpeg4sp_vdecOutArgs.viddecOutArgs.bytesConsumed;
				SYS_DEBUG("Instance# %d: Bytes Consumed = %d.\n", j, frameSize);
				if (0 == frameSize)
				{
					continue;
				}

				SYS_OUT("Instance#, %d, Frame#, %d \n", j, nFrames);
#ifdef PERF
				SYS_PERF("Instance#, %d, Frame#, %d, EncTime(us), %d, DecTime(us), %d\n", j, nFrames, encDuration[j], decDuration[j]);
#endif

				if(DVEVM_ST_TRUE == firstProcessCall[j])
				{
					firstProcessCall[j] = DVEVM_ST_FALSE;

					//Allocate and initialize all outBuffers once again
					if(DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spDec2InitAllOutBuffers(&T->g.DVREncDec.dec[j]))
					{
						SYS_ERROR("Unable to Initialize other out buffers.\n");
						dvtb_DVREncDecMpeg4spDec2DeInitOutBuffers(&T->g.DVREncDec.dec[j]);
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					SYS_DEBUG("All Output buffers initialized.\n");
				}

				//Store decoded content
				if (NULL != decOutputFp[j])
				{
					if(DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spDec2ProcessOutBuff(T, &T->g.DVREncDec.dec[j], decOutputFp[j], DVEVM_ST_TRUE, nFrames, &displayFrame))
					{
						SYS_ERROR("Unable to Process Out buffers. \n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}
				}

				dvtb_DVREncDecMpeg4spDec2ReleaseBuffers(&T->g.DVREncDec.dec[j], (unsigned int *)T->g.DVREncDec.dec[j].mpeg4sp_vdecOutArgs.viddecOutArgs.freeBufID);

			}
			if(DVEVM_ST_TRUE == usecaseFailed)//Proceed only if usecase is successful
				break;
			nFrames++;
		}

		//Flush the held frames only in the case where the usecase has not failed so far
		for (j = 0; j < instanceCount; j++)
		{
			if(DVEVM_ST_FALSE == usecaseFailed && T->useAlgorithm)
			{
				SYS_OUT("Instance#, %d, \n",j);
				if(DVEVM_ST_FAIL == dvtb_DVREncDecMpeg4spDec2Flush(T, &T->g.DVREncDec.dec[j], decOutputFp[j], DVEVM_ST_TRUE, nFrames, &displayFrame))
				{
					SYS_ERROR("Unable to Flush Held frames buffers. \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
			}
		}
	} while (DVEVM_ST_FALSE);

	SYS_OUT("DVREncDec completed for <%d> frames\n", nFrames - 1);

	/* Uninitialize and close */
	for (i = 0; i < instanceCount; i++)
	{
		//Free all the allocated output buffers
		dvtb_DVREncDecMpeg4spDec2DeInitOutBuffers(&T->g.DVREncDec.dec[i]);

		dvtb_mpeg4spEnc1Close(&T->g.DVREncDec.enc[i]);
		dvtb_mpeg4spDec2Close(&T->g.DVREncDec.dec[i]);
		SYS_OUT("Video EncDecInstance# %d <%s> <%s> closed\n", i, T->g.DVREncDec.enc[i].venc1Name,T->g.DVREncDec.dec[i].vdec2Name);
	}

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&T->g.DVREncDec.ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", T->g.eng.name);
	else
		SYS_OUT("Engine <%s> closed\n", T->g.eng.name);

	if (T->sourceFp)
	{
		fclose(T->sourceFp);
		T->sourceFp = NULL;
	}

	for (i = 0; i < instanceCount; i++)
	{
		dvtb_fileClose(&sourceFp[i], &decOutputFp[i]);

		if (fMVFile[i])
			fclose(fMVFile[i]);
	}

	dvtb_exitMessage(DVEVM_ST_ENCDEC, "DVREncDec", DVEVM_ST_TRUE, DVEVM_ST_TRUE, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
