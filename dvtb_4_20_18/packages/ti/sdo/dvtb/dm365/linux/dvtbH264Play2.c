/*
 * dvtbH264Play2.c
 *
 * XDM1.2 H264 Decode Functionality
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

#include "dvtbH264Play2.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbH264Dec2.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"
#include "dvtbDM365Utils.h"

//#define DVTB_PERF

XDAS_UInt32 bytesConsumed = 0;
XDAS_UInt32 TotalbytesConsumed = 0;
XDAS_UInt32 nalPayloadBytesConsumed = 0;
XDAS_Int32 validBytes;
#define NUM_NALS_PER_CALBK 1
XDAS_Int32 g_nalStartCodeSize[IH264VDEC_TI_MAXNUMBLOCKS];
XDAS_UInt32 nalSize[IH264VDEC_TI_MAXNUMBLOCKS];
int nBytes = 0;
char *inputbuffer = NULL;
int inputbuffersize = 0;
int sliceFormat = 0;
FILE *sourceFile = NULL;

DvevmStRetCode
dvtb_h264Dec2HanInit(DvevmStH264Dec2Info *vd, char *engName)
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
		if (DVEVM_ST_FAIL == dvtb_h264Dec2Init(vd))
		{
			SYS_ERROR("Unable to initialize Video Decoder <%s>\n", vd->h264dec2Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	} while (DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

void
dvtb_h264Dec2HanClose(DvevmStH264Dec2Info *vd, char *engName)
{
	//Free the allocated Input Buffer
	if (0 < vd->inBuf.numBufs)
		dvtb_freeCmemSingleChunk(&vd->inBuf);

	//Free all the allocated output buffers

	dvtb_vidDec2DeInitOutBuffers_dm365(&vd->outBufArray, vd->totBuf);

	dvtb_h264Dec2Close(vd);
	SYS_OUT("Video Decoder <%s> closed\n", vd->h264dec2Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&vd->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_h264Dec2DecProcess(DvevmStThreadInfo *T, int nFrames, int *decDuration)
{
	int frameSize = 0;
	DvevmStBufElement *freeBufElement = NULL;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (!T->g.h264dec2.vdec2OutArgs.viddecOutArgs.outBufsInUseFlag)
		{
			freeBufElement = dvtb_vidDec2AllocOutBuffer_dm365(&T->g.h264dec2.outBufArray, T->g.h264dec2.totBuf, &T->g.h264dec2.buffIdSearchStart);
			if (freeBufElement == NULL)
			{
				SYS_ERROR("No more free buffers to allocate.\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}

			T->g.h264dec2.outBufDesc.numBufs = freeBufElement->buffer.numBufs;
			T->g.h264dec2.outBufDesc.bufSizes = (XDAS_Int32 *) freeBufElement->buffer.bufSizes;
			T->g.h264dec2.outBufDesc.bufs = (XDAS_Int8 **) freeBufElement->buffer.bufs;
			T->g.h264dec2.vdec2InArgs.viddecInArgs.inputID = freeBufElement->id;
		}

		// Make a Decode Process call
		if (DVEVM_ST_FAIL == dvtb_h264Dec2Decode(&T->g.h264dec2, nFrames, decDuration))
		{
			SYS_ERROR("Unable to decode <%s> frame # %d.\n", T->g.h264dec2.h264dec2Name, nFrames);

			T->g.h264dec2.vdec2Cmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_h264Dec2Control(&T->g.h264dec2))
				SYS_ERROR("Unable to get the status for frame # %d\n", nFrames);
			else
				SYS_ERROR("Codec Error = %d\n", (int) T->g.h264dec2.vdec2Status.viddecStatus.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

		frameSize = T->g.h264dec2.vdec2OutArgs.viddecOutArgs.bytesConsumed;
		if (0 != frameSize)
		{
			T->g.h264dec2.vdec2Cmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_h264Dec2Control(&T->g.h264dec2))
			{
				SYS_ERROR("Unable to get the status for frame # %d\n", nFrames);
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}
	} while (DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_h264Dec2Flush(DvevmStThreadInfo *T, int *nFrames)
{
	int decDuration = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		/* Add logic for flushing display buffers */
		T->g.h264dec2.vdec2Cmd = XDM_FLUSH;

		if (DVEVM_ST_FAIL == dvtb_h264Dec2Control(&T->g.h264dec2))
		{
			SYS_ERROR("Unable to set Flush mode.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		SYS_OUT("Flushing out frames held by Video Decoder\n");

		while ((*nFrames) <= T->g.h264dec2.numFrames)
		{
			if (DVEVM_ST_FAIL == dvtb_h264Dec2Decode(&T->g.h264dec2, (*nFrames), &decDuration))
			{
				SYS_ERROR("Process call returned error while flushing display buffers\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}

			T->g.h264dec2.vdec2Cmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_h264Dec2Control(&T->g.h264dec2))
			{
				SYS_ERROR("Unable to get the status of the decoder\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}

			if (0 == T->g.h264dec2.vdec2OutArgs.viddecOutArgs.outputID[0])
				break;

			/* O/p logic */
			if (DVEVM_ST_FAIL == dvtb_vidDec2ProcessOutBuff_dm365(&T->g.vpbe, &T->g.h264dec2.vdec2Status.viddecStatus, &T->g.h264dec2.vdec2OutArgs.viddecOutArgs, &T->g.h264dec2.vdec2InArgs.viddecInArgs, &T->g.h264dec2.vdec2Params.viddecParams, &T->g.h264dec2.vdec2DynParams.viddecDynamicParams, &T->g.h264dec2.dispBufArray, &T->g.h264dec2.outBufArray, T->targetFp, nFrames, 0))
			{
				SYS_ERROR("Unable to process output buffer \n");
				retCode = DVEVM_ST_FAIL;
				break;
			}

			if (DVEVM_ST_USERBUFFER!=T->g.vpbe.opMode)
			{
				dvtb_vidDec2ReleaseOutBuffers(&T->g.h264dec2.outBufArray, &T->g.h264dec2.vdec2OutArgs.viddecOutArgs.freeBufID);
			}

		}//end of while(displayFrame < (*nFrames))
	} while (DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_validateH264DEC2(DvevmStThreadInfo *T)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	/* Validate the i/p chroma format to supported formats */
	if ((T->g.h264dec2.vdec2Params.viddecParams.forceChromaFormat != XDM_YUV_420SP) && (T->g.h264dec2.vdec2Params.viddecParams.forceChromaFormat != XDM_YUV_422ILE) && (T->g.h264dec2.vdec2Params.viddecParams.forceChromaFormat != XDM_CHROMAFORMAT_DEFAULT))
	{
		SYS_ERROR("Invalid 'forceChromaFormat'!\n");
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStRetCode
dvtb_h264Dec2CompleteBuffInit(DvevmStThreadInfo *T)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		T->g.h264dec2.vdec2Cmd = XDM_GETBUFINFO;
		if (DVEVM_ST_FAIL == dvtb_h264Dec2Control(&T->g.h264dec2))
		{
			SYS_ERROR("Unable to get the buffer requirements for this input stream.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_USERBUFFER==T->g.vpbe.opMode)
		{
			if (T->g.h264dec2.vdec2Status.viddecStatus.maxNumDisplayBufs<MIN_DISPLAY_BUFFERS)
				T->g.h264dec2.vdec2Status.viddecStatus.maxNumDisplayBufs = MIN_DISPLAY_BUFFERS;

			T->g.h264dec2.vdec2Status.viddecStatus.maxNumDisplayBufs+=(MIN_DISPLAY_BUFFERS+1);

			if (T->g.h264dec2.vdec2Status.viddecStatus.maxNumDisplayBufs>VIDDEC2_PLAY_MAX_BUFFERS)
				T->g.h264dec2.vdec2Status.viddecStatus.maxNumDisplayBufs=VIDDEC2_PLAY_MAX_BUFFERS;
		}

		//Allocate and initialize all outBuffers
		if (DVEVM_ST_FAIL == dvtb_vidDec2InitAllOutBuffers_dm365(&T->g.h264dec2.outBufArray, &T->g.h264dec2.vdec2Status.viddecStatus, &T->g.h264dec2.totBuf, T->g.h264dec2.vdec2Status.viddecStatus.maxNumDisplayBufs))
		{
			SYS_ERROR("Unable to Initialize other out buffers.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		SYS_DEBUG("All Output buffers initialized.\n");
	} while (DVEVM_ST_FALSE);

	return retCode;
}

int
findNalStart(XDAS_UInt32 validBytesInBuffer, XDAS_UInt8 *nalStartAddrs[], XDAS_UInt32 *nalLength, XDAS_UInt8 streamFormat)
{
	XDAS_UInt8 *bufPtr = (XDAS_UInt8 *)inputbuffer + bytesConsumed;
	XDAS_UInt32 startCode = 0;
	XDAS_Int32 numNalUnit = 0;
	XDAS_UInt8 nalStartCodeLength, bufIndexMoved;
	XDAS_UInt8 *endBufPtr = (XDAS_UInt8 *)inputbuffer + nBytes;
	XDAS_UInt8 numNalsPerCallback = NUM_NALS_PER_CALBK;

	while (startCode != 0x000001)
	{
		startCode = (bufPtr[0] << 16) | (bufPtr[1] << 8) | bufPtr[2];
		bufPtr++;
		if (bufPtr >= endBufPtr)
		{
			SYS_ERROR("no valid NAL start code in this buffer\n");
			return -1;
		}
	}

	bufPtr += 2;

	if (*(bufPtr - 4) != 0)
	{
		nalStartCodeLength = 3;
	}
	else
	{
		nalStartCodeLength = 4;
	}
	
	do
	{
		if (streamFormat == IH264VDEC_TI_NALSTREAM)
		{
			nalStartAddrs[numNalUnit] = bufPtr;
			g_nalStartCodeSize[numNalUnit] = nalStartCodeLength;
		}
		else
		{
			nalStartAddrs[numNalUnit] = bufPtr - nalStartCodeLength;
		}

		startCode = 0;
		while (startCode != 0x000001)
		{
			startCode = (bufPtr[0] << 16) | (bufPtr[1] << 8) | bufPtr[2];
			bufPtr++;
			if (bufPtr > endBufPtr)
			{
				break;
			}
		}
		if (*(bufPtr - 2) != 0)
		{
			nalStartCodeLength = 3;
			bufIndexMoved = 1;
		}
		else
		{
			nalStartCodeLength = 4;
			bufIndexMoved = 2;
		}

		nalLength[numNalUnit] = (XDAS_UInt32) (bufPtr - nalStartAddrs[numNalUnit] - bufIndexMoved);

		bufPtr += 2;
		numNalUnit++;
		if (numNalUnit >= numNalsPerCallback)
		{
			break;
		}

	}while (bufPtr <= endBufPtr);
	
	return (numNalUnit);
}

XDAS_Int32 
dataSyncPutData( IH264VDEC_TI_DataSyncHandle dataSyncHandle, IH264VDEC_TI_DataSyncDesc * dataSyncDesc)
{
	XDAS_Int8 i, numNalUnits;
	XDAS_UInt8 *nalStartAddrs[IH264VDEC_TI_MAXNUMBLOCKS];

	for (i = 0; i < dataSyncDesc->numBlocks; i++)
	{
		bytesConsumed += dataSyncDesc->blockSizes[i];
		nalPayloadBytesConsumed += dataSyncDesc->blockSizes[i];
		validBytes = validBytes - dataSyncDesc->blockSizes[i];
		if (sliceFormat == IH264VDEC_TI_NALSTREAM)
		{
			bytesConsumed += g_nalStartCodeSize[i];
			validBytes -= g_nalStartCodeSize[i];
		}
	}
	TotalbytesConsumed += bytesConsumed;
	fseek(sourceFile, -(nBytes - bytesConsumed), SEEK_CUR);	
	bytesConsumed = 0;		
	if(DVEVM_ST_FAIL == dvtb_fileRead(sourceFile, inputbuffer, inputbuffersize, &nBytes))
	{
		SYS_ERROR("Error in file read \n");
	}
		
	validBytes = nBytes;
	numNalUnits = findNalStart (validBytes, nalStartAddrs, nalSize, sliceFormat);

	dataSyncDesc->numBlocks = numNalUnits;
	for (i = 0; i < numNalUnits; i++)
	{
		dataSyncDesc->baseAddr[i] = (XDAS_Int32 *) nalStartAddrs[i];
		dataSyncDesc->blockSizes[i] = nalSize[i];
	}

    	if (validBytes < 0)
        	validBytes = 0;

	return (XDM_EOK);
}

void
dvtb_H264Dec2Play(DvevmStThreadInfo *T)
{
#ifdef DVTB_PERF
	DvevmStTime timeStmpBfrDec, timeStmpAftrDec;
	unsigned int LoopdecDuration;
#endif

	int nTotalInputBytes = 0, nFrames = 1, frameSize = 0,  remainingBytes = 0, displayFrame = 1, numNalUnits = 0;
	unsigned int fileSize = 0;
	int decDuration = 0, i =0;
	DvevmStXdmBuffer *inbuf = NULL, *outbuf = NULL;
	DvevmStBool vpbeOpened = DVEVM_ST_FALSE, usecaseFailed = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;
	DvevmStBool firstProcessCall = DVEVM_ST_TRUE;
	XDAS_UInt8 *nalStartAddrs[IH264VDEC_TI_MAXNUMBLOCKS];

	T->g.vpbe.videoFd = 0;

	/* Quit if source file is not specified */
	if (!T->sourceFp)
	{
		SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
		dvtb_freeThr(T);
		pthread_exit(NULL);
	}

	/* Validate the use-case configuration */
	if (DVEVM_ST_FAIL == dvtb_validateH264DEC2(T))
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

	dvtb_vidDec2StartMessage(0, fileBased, T->g.h264dec2.h264dec2Name);

	// [Decode][Play] scenario
	do
	{
		inbuf = &T->g.h264dec2.inBuf;
		outbuf = &T->g.h264dec2.outBuf;
		if(IH264VDEC_TI_SLICEMODE == T->g.h264dec2.vdec2Params.inputDataMode)
		{
			T->g.h264dec2.vdec2DynParams.getDataFxn = dataSyncPutData;
			T->g.h264dec2.vdec2DynParams.dataSyncHandle = NULL;		
		}

		if (DVEVM_ST_FAIL == dvtb_h264Dec2HanInit(&T->g.h264dec2, (char *) T->g.eng.name))
		{
			SYS_ERROR("Unable to initialize Video Decoder Handle \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_vidDec2AllocInBuff(&T->g.h264dec2.inBuf, &T->g.h264dec2.inBufDesc, T->g.h264dec2.vdec2Status.viddecStatus.bufInfo.minNumInBufs))
		{
			SYS_ERROR("Error in allocating memory for input buffer\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}
		
		if(IH264VDEC_TI_SLICEMODE == T->g.h264dec2.vdec2Params.inputDataMode)
		{
			inputbuffer = (char *)inbuf->bufs[0];
			inputbuffersize = inbuf->bufSizes[0];
			sliceFormat = T->g.h264dec2.vdec2Params.sliceFormat;
			sourceFile = T->sourceFp;
		}

		//Allocate First Output Buffer
		if (DVEVM_ST_FAIL == dvtb_vidDec2InitFirstOutBuffer_dm365(&T->g.h264dec2.outBufArray, &T->g.h264dec2.vdec2Status.viddecStatus, &T->g.h264dec2.totBuf))
		{
			SYS_ERROR("Unable to Initialize 1st out buffer.\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		T->g.h264dec2.vdec2OutArgs.viddecOutArgs.outBufsInUseFlag = 0;

		SYS_OUT("Video Decoder <%s> initialized\n", T->g.h264dec2.h264dec2Name);

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
			if(IH264VDEC_TI_SLICEMODE == T->g.h264dec2.vdec2Params.inputDataMode)
			{
				numNalUnits = findNalStart(nBytes,nalStartAddrs,nalSize,T->g.h264dec2.vdec2Params.sliceFormat);
				
				for(i=0; i<numNalUnits; i++)
				{
					T->g.h264dec2.vdec2InArgs.viddecInArgs.numBytes = nBytes;
					T->g.h264dec2.inBufDesc.descs[i].buf = (XDAS_Int8 *) nalStartAddrs[i];
					T->g.h264dec2.vdec2InArgs.pNumBytesInDesc[i] = nalSize[i];	
				}
				
			}
			else
			{
				T->g.h264dec2.vdec2InArgs.viddecInArgs.numBytes = nBytes;
				T->g.h264dec2.inBufDesc.descs[0].buf = (XDAS_Int8 *) ((XDAS_Int32) T->g.h264dec2.inBuf.bufs[0]);
			}

			//Set dynamic parameters
			T->g.h264dec2.vdec2Cmd = XDM_SETPARAMS;
			if (DVEVM_ST_FAIL == dvtb_h264Dec2Control(&T->g.h264dec2))
			{
				SYS_ERROR("Unable to set the dynamic params\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_FAIL == dvtb_h264Dec2DecProcess(T, nFrames, &decDuration))
			{
				SYS_ERROR("Video decoder process fails\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			
			if(IH264VDEC_TI_SLICEMODE != T->g.h264dec2.vdec2Params.inputDataMode)	
			{
				frameSize = T->g.h264dec2.vdec2OutArgs.viddecOutArgs.bytesConsumed;
				if (0 == frameSize)
				{
					SYS_OUT("Video Decode Process generated 0 bytes. continue decode.\n");
					continue;
				}
				SYS_DEBUG("Bytes Consumed = %d.\n", frameSize);
#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Frame Size(bytes), %d, DecTime(us), %d\n", (unsigned int) T, nFrames, frameSize, decDuration);
#endif
				TotalbytesConsumed += frameSize;
				fseek(T->sourceFp, -(nBytes - frameSize), SEEK_CUR);
				remainingBytes -= frameSize;
			}
			else
			{				
				for (i = 0; i < T->g.h264dec2.vdec2OutArgs.numBlocksConsumed; i++)
				{
					bytesConsumed += nalSize[i];
					/*  Incase of NAL stream it is without nal header. In  */
					/* Bytes stream payload with headers                   */
					nalPayloadBytesConsumed += nalSize[i];
					validBytes = validBytes - nalSize[i];
					if (sliceFormat == IH264VDEC_TI_NALSTREAM)
					{
						bytesConsumed += g_nalStartCodeSize[i];
						validBytes -= g_nalStartCodeSize[i];
					}
				}
				TotalbytesConsumed += bytesConsumed;
				fseek(T->sourceFp, -(nBytes - bytesConsumed), SEEK_CUR);	
				bytesConsumed = 0;		
#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, DecTime(us), %d\n", (unsigned int) T, nFrames, decDuration);
#endif
			}

			SYS_OUT("Decoded Frame %d.\n", nFrames);


			/* Complete allocation of all out-buffers and initialize VPBE as per codec returned details */
			if (DVEVM_ST_TRUE == firstProcessCall)
			{
				if (DVEVM_ST_FAIL == dvtb_h264Dec2CompleteBuffInit(T))
				{
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				if (DVEVM_ST_FALSE != fileBased)
					SYS_OUT("H264 Video [Decode]+[Dump] usecase started\n");

				firstProcessCall = DVEVM_ST_FALSE;
			}

			if ((DVEVM_ST_FALSE == fileBased) && (DVEVM_ST_TRUE != vpbeOpened))
			{
				if (T->g.h264dec2.vdec2OutArgs.viddecOutArgs.outputID[0] > 0 || (T->g.h264dec2.vdec2DynParams.viddecDynamicParams.frameOrder && (0 == T->g.h264dec2.vdec2OutArgs.viddecOutArgs.outBufsInUseFlag)))
				{
					if (DVEVM_ST_FAIL == dvtb_vidDec2SetUpVPBE(&T->g.vpbe, &T->g.h264dec2.vdec2Status.viddecStatus, &T->g.h264dec2.vdec2OutArgs.viddecOutArgs, &T->g.h264dec2.vdec2InArgs.viddecInArgs, &T->g.h264dec2.vdec2Params.viddecParams, &T->g.h264dec2.vdec2DynParams.viddecDynamicParams, &T->g.h264dec2.dispBufArray))
					{
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					vpbeOpened = DVEVM_ST_TRUE;

					SYS_OUT("VPBE device <%s> initialized for display\n", T->g.vpbe.device);

					if(DVEVM_ST_USERBUFFER==T->g.vpbe.opMode)
						dvtb_registerOutBuffToFree(&T->g.h264dec2.dispBufArray, &T->g.h264dec2.vdec2OutArgs.viddecOutArgs.freeBufID);

					if(DVEVM_ST_USERBUFFER!=T->g.vpbe.opMode)
						dvtb_vidDec2ReleaseOutBuffers(&T->g.h264dec2.outBufArray, &T->g.h264dec2.vdec2OutArgs.viddecOutArgs.freeBufID);

					continue;
				}
			}

			/* O/p logic */
			if (DVEVM_ST_FAIL == dvtb_vidDec2ProcessOutBuff_dm365(&T->g.vpbe, &T->g.h264dec2.vdec2Status.viddecStatus, &T->g.h264dec2.vdec2OutArgs.viddecOutArgs, &T->g.h264dec2.vdec2InArgs.viddecInArgs, &T->g.h264dec2.vdec2Params.viddecParams, &T->g.h264dec2.vdec2DynParams.viddecDynamicParams, &T->g.h264dec2.dispBufArray, &T->g.h264dec2.outBufArray, T->targetFp, &displayFrame, 0))
			{
				SYS_ERROR("Unable to process output buffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_USERBUFFER!=T->g.vpbe.opMode)
				dvtb_vidDec2ReleaseOutBuffers(&T->g.h264dec2.outBufArray, &T->g.h264dec2.vdec2OutArgs.viddecOutArgs.freeBufID);

#ifdef DVTB_PERF
			timeStmpAftrDec = dvtb_getTime();
			LoopdecDuration = ((timeStmpAftrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrDec.tv_usec) - ((timeStmpBfrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrDec.tv_usec);
			SYS_OUT("Frame #, %d, DVTB DecTime(us), %d \n", nFrames, LoopdecDuration);
#endif
			nFrames++;
		} while ((nFrames <= T->g.h264dec2.numFrames) && (TotalbytesConsumed >= nTotalInputBytes));// end do-while

		//Flush the held frames only in the case where the usecase has not failed so far
		if (DVEVM_ST_FALSE == usecaseFailed)
		{
			if (DVEVM_ST_FAIL == dvtb_h264Dec2Flush(T, &displayFrame))
			{
				SYS_ERROR("Unable to Flush held frames buffers. \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop


	dvtb_vidDec2ProcessEndMessage_dm365(0, fileBased, displayFrame , T->g.h264dec2.h264dec2Name);

	if (DVEVM_ST_TRUE == vpbeOpened)
	{
		dvtb_vpbeClose(&T->g.vpbe);
		SYS_OUT("VPBE Device <%s> closed\n", T->g.vpbe.device);
	}

	dvtb_h264Dec2HanClose(&T->g.h264dec2, T->g.eng.name);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_vidDec2ExitMessage(0, fileBased, usecaseFailed , T->g.h264dec2.h264dec2Name);

	dvtb_freeThr(T);
	pthread_exit(NULL);
}

