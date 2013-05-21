/*
 * dvtbH264Capture1.c
 *
 * XDM1.0 H264 Encode Functionality
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

#include "dvtbH264Capture1.h"
#include "dvtbH264Enc1.h"
#include "dvtbV4L2VPFE.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDM365Utils.h"
#include "dvtbPreviewer.h"
#include "dvtbResizer.h"
#include "dvtbDefs.h"

extern int errno;
int sliceformat;
FILE *outbitstreamfile = NULL;
XDM_BufDesc *outobj = NULL;

#ifndef H264_MVDUMP_FILE
#define H264_MVDUMP_FILE            "h264-mv-dump.txt"
#endif


void
dvtb_h264Enc1ProcessEndMessage(DvevmStBool fileBased, int nFrames)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		SYS_OUT("Total # of frames Captured & Encoded = %d \n", nFrames - 1);
	}
	else
		//File based
		SYS_OUT("Total # of frames Read from File & Encoded = %d \n", nFrames - 1);
}

DvevmStRetCode
dvtb_h264Enc1HanInit(DvevmStH264Enc1Info *ve, char *engName)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ve->ceHdl = NULL;
	ve->venc1Hdl = NULL;
	
	ve->inBuf.numBufs = 0;
	ve->outBuf.numBufs = 0;
	for (i = 0; i < MAX_XDM_BUFS; i++)
	{
		ve->inBuf.bufs[i] = NULL;
		ve->outBuf.bufs[i] = NULL;
	}

	do //Dummy loop for easy clean up
	{
		// Initialize Engine
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &ve->ceHdl))
		{
			SYS_ERROR("Cannot initialize Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		//Initialize Codec Instance
		if (DVEVM_ST_FAIL == dvtb_h264Enc1Init(ve))
		{
			SYS_ERROR("Unable to initialize Video Encoder <%s>\n", ve->h264enc1Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	} while (DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

void
dvtb_h264Enc1HanClose(DvevmStH264Enc1Info *ve, char *engName)
{
	dvtb_h264Enc1Close(ve);
	SYS_OUT("Video Encoder <%s> closed\n", ve->h264enc1Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&ve->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

void
dvtb_h264Enc1InBuffFree(IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased)
{
	int i = 0;
	IVIDEO1_BufDescIn *tempInBufDesc = inBufDesc;

	for (i = 0; i < tempInBufDesc->numBufs; i++)
	{
		if ((NULL != tempInBufDesc->bufDesc[i].buf) && (DVEVM_ST_TRUE == fileBased))
			Memory_contigFree(tempInBufDesc->bufDesc[i].buf, tempInBufDesc->bufDesc[i].bufSize);

		tempInBufDesc->bufDesc[i].bufSize = 0;
	}
	tempInBufDesc->numBufs = 0;

	return;
}

DvevmStRetCode
dvtb_h264Enc1InBuffAlloc(IVIDEO1_BufDescIn *inBufDesc, DvevmStH264Enc1Info *venc1, DvevmStBool fileBased)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	IVIDEO1_BufDescIn *tempInBufDesc = inBufDesc;

	do //Dummy loop for easy clean up
	{
		tempInBufDesc->numBufs = venc1->inBuf.numBufs;
		tempInBufDesc->frameWidth = venc1->venc1DynParams.videncDynamicParams.inputWidth;
		tempInBufDesc->frameHeight = venc1->venc1DynParams.videncDynamicParams.inputHeight;

		for (i = 0; i < tempInBufDesc->numBufs; i++)
		{
			tempInBufDesc->bufDesc[i].bufSize = venc1->inBuf.bufSizes[i];

			if (DVEVM_ST_TRUE == fileBased)
			{
				tempInBufDesc->bufDesc[i].buf = Memory_contigAlloc(tempInBufDesc->bufDesc[i].bufSize, Memory_DEFAULTALIGNMENT);

				if (!tempInBufDesc->bufDesc[i].buf)
				{
					SYS_ERROR("Unable to allocate memory for input buffer[%d]\n", i);
					retCode = DVEVM_ST_FAIL;
					break;
				}
			}
			else
				tempInBufDesc->bufDesc[i].buf = NULL;
		}
	} while (DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

void
dvtb_h264Enc1OutBuffFree(XDM_BufDesc *outBufDesc)
{
	int i = 0;
	XDM_BufDesc *tempOutBufDesc = outBufDesc;

	for (i = 0; i < tempOutBufDesc->numBufs; i++)
	{
		if (NULL != tempOutBufDesc->bufs[i])
			Memory_contigFree(tempOutBufDesc->bufs[i], tempOutBufDesc->bufSizes[i]);
		tempOutBufDesc->bufSizes[i] = 0;
	}

	if (NULL != tempOutBufDesc->bufs)
		Memory_contigFree(tempOutBufDesc->bufs, tempOutBufDesc->numBufs * sizeof(XDAS_Int8 *));
	if (NULL != tempOutBufDesc->bufSizes)
		Memory_contigFree(tempOutBufDesc->bufSizes, tempOutBufDesc->numBufs * sizeof(XDAS_Int32));

	tempOutBufDesc->numBufs = 0;

	return;
}

DvevmStRetCode
dvtb_h264Enc1OutBuffAlloc(DvevmStXdmBuffer *outBuf, XDM_BufDesc *outBufDesc)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	XDM_BufDesc *tempOutBufDesc = outBufDesc;

	tempOutBufDesc->numBufs = outBuf->numBufs;

	do
	{
		/* initialize outBuf */
		tempOutBufDesc->bufSizes = Memory_contigAlloc(tempOutBufDesc->numBufs * sizeof(XDAS_Int32), Memory_DEFAULTALIGNMENT);
		if (!tempOutBufDesc->bufSizes)
		{
			SYS_ERROR("Unable to allocate memory for 'outbuf->bufSizes'\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		tempOutBufDesc->bufs = Memory_contigAlloc(tempOutBufDesc->numBufs * sizeof(XDAS_Int8 *), Memory_DEFAULTALIGNMENT);
		if (!tempOutBufDesc->bufs)
		{
			SYS_ERROR("Unable to allocate memory for 'outbuf->bufs'\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		for (i = 0; i < tempOutBufDesc->numBufs; i++)
		{
			tempOutBufDesc->bufSizes[i] = outBuf->bufSizes[i];
			tempOutBufDesc->bufs[i] = Memory_contigAlloc(tempOutBufDesc->bufSizes[i], Memory_DEFAULTALIGNMENT);

			if (!tempOutBufDesc->bufs[i])
			{
				SYS_ERROR("Cannot allocate memory for output buffer[%d]\n", i);
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}
	} while (DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_h264Enc1EncProcess(DvevmStThreadInfo *T, int nFrames)
{
	int encDuration = 0, targetBytes = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		// Make Video encode process call
		if (DVEVM_ST_FAIL == dvtb_h264Enc1Encode(&T->g.h264enc1, &encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");

			T->g.h264enc1.venc1Cmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_h264Enc1Control(&T->g.h264enc1))
				SYS_ERROR("Unable to get the status\n");
			else
				SYS_ERROR("Codec Error = %d\n", (int) T->g.h264enc1.venc1Status.videncStatus.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

		T->g.h264enc1.venc1Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_h264Enc1Control(&T->g.h264enc1))
		{
			SYS_ERROR("Unable to get the status\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
		SYS_OUT("Encoded Frame %d.\n", nFrames);
		targetBytes = T->g.h264enc1.venc1OutArgs.videncOutArgs.bytesGenerated;

#ifdef PERF
		SYS_PERF("Thread, %x, Frame#, %d, Frame Type, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, nFrames, (int) T->g.h264enc1.venc1OutArgs.videncOutArgs.encodedFrameType, targetBytes, encDuration);
#endif
	} while (DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_h264enc1MVDump(DvevmStH264Enc1Info *venc1, int nFrames, FILE *fMVFile)
{

	XDAS_Int32 *puiSadMVinfo = NULL;
	XDAS_UInt32 cntRow, cntCol, cnt;
	unsigned int frameHeight = venc1->venc1DynParams.videncDynamicParams.inputHeight;
	unsigned int frameWidth = venc1->venc1DynParams.videncDynamicParams.inputWidth;

	if( 0==venc1->venc1DynParams.sliceSize )
	{
		puiSadMVinfo = (XDAS_Int32*)venc1->outBufDesc.bufs[1];
	}
	else
	{
		puiSadMVinfo =  (XDAS_Int32*)venc1->outBufDesc.bufs[2];
	}
	if(venc1->venc1Params.entropyMode || !(venc1->venc1Params.encQuality))
	{
		puiSadMVinfo = (XDAS_Int32*)venc1->outBufDesc.bufs[1];
	}

	fprintf(fMVFile, "*********************************************\n");
	fprintf(fMVFile, "        Frame number = %d                    \n", nFrames);
	fprintf(fMVFile, "*********************************************\n");

	for(cntRow = 0; cntRow < (frameHeight >> 4); cntRow++)
	{
		cnt = cntRow * 2 * (frameWidth >> 4);
		for(cntCol = 0; cntCol < 2 * (frameWidth >> 4); cntCol+=2)
		{
			fprintf(fMVFile, "SAD = %d, MVx = %d, MVy = %d\n",
			(int)(*((XDAS_Int32 *)(puiSadMVinfo) + cnt + cntCol + 1)), (short)(puiSadMVinfo[cnt + cntCol] & 0x0000FFFF),
			(int)(puiSadMVinfo[cnt + cntCol] >> 16));
		}
	}

	return;
}

int
getEncodedSliceProvideSpace( IH264VENC_TI_DataSyncHandle dataSyncHandle, IH264VENC_TI_DataSyncDesc *dataSyncDesc)
{
	int i, numBlocks;
	unsigned int startCodePattern = 0x01000000;
	numBlocks = dataSyncDesc->numBlocks;
	
	for (i = 0; i < numBlocks; i++)
	{
		if(sliceformat == IH264VENC_TI_NALSTREAM)
		{
			if (DVEVM_ST_FAIL == dvtb_fileWrite(outbitstreamfile, (char *) &startCodePattern, 4))
			{
				SYS_ERROR("Error in writing to file.\n");
				return -1;				
			}
		}
		if (DVEVM_ST_FAIL == dvtb_fileWrite(outbitstreamfile, (char *) dataSyncDesc->baseAddr[i], dataSyncDesc->blockSizes[i]))
		{
			SYS_ERROR("Error in writing to file.\n");
			return -1;				
		}
	}
	dataSyncDesc->numBlocks = 1;
	dataSyncDesc->baseAddr[0]   = (XDAS_Int32 *)outobj->bufs[0];
	dataSyncDesc->blockSizes[0] = outobj->bufSizes[0];
	return(0);
}

void
dvtb_H264Enc1Capture(DvevmStThreadInfo *T)
{
	int maxFrames = 0, nFrames = 1, targetBytes = DEF_VIDFRAME_SIZE;
	char *targetBuff = NULL;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, vpfeOpened = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;
	int numPackets = 0;
	XDAS_Int32 *packetSizes = NULL;
	FILE *fMVFile = NULL;

	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fMVFile, H264_MVDUMP_FILE, "w"))
	{
		SYS_ERROR("Unable to open source file : %s\n", H264_MVDUMP_FILE);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	T->g.vpfe.capFd = 0;
	T->g.h264enc1.inBuf.bufs[0] = NULL;
	T->g.h264enc1.outBuf.bufs[0] = NULL;
	maxFrames = T->g.h264enc1.numFrames;
	T->g.h264enc1.venc1InArgs.numOutputDataUnits = 0;

	/* Quit if target file is not specified */
	if (!T->targetFp)
	{
		SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	if (!T->sourceFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_ENCODE, "Video", 0, fileBased);

	/* Dummy loop to enable easy cleanup */
	do
	{
		/* If source file is not defined, initialize VPFE
		 * Else initialize the YUV source file to be encoded */
		if (DVEVM_ST_FALSE == fileBased)
		{
			if (DVEVM_ST_FAIL == dvtb_captureSetup(&T->g.vpfe, &T->g.vpPrvw, &T->g.vpRsz))
			{
				SYS_ERROR("Unable to initialize Video Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			vpfeOpened = DVEVM_ST_TRUE;
			SYS_OUT("VPFE device <%s> initialized for capture\n", T->g.vpfe.device);
		}
		if(IH264VENC_TI_ENTIREFRAME != T->g.h264enc1.venc1Params.outputDataMode)
		{
			//set global variables
			sliceformat = T->g.h264enc1.venc1Params.sliceFormat;
			outbitstreamfile = T->targetFp;
			T->g.h264enc1.venc1DynParams.putDataGetSpaceFxn = getEncodedSliceProvideSpace;
			T->g.h264enc1.venc1DynParams.dataSyncHandle = NULL;
			// dump every slice
			T->g.h264enc1.venc1InArgs.numOutputDataUnits = 1;
			
		}

		/* Initialize Video Encoder if DSP is to be used */
		if (DVEVM_ST_FAIL == dvtb_h264Enc1HanInit(&T->g.h264enc1, (char *) T->g.eng.name))
		{
			SYS_ERROR("Unable to initialize Video Encoder Handle \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_h264Enc1InBuffAlloc(&T->g.h264enc1.inBufDesc, &T->g.h264enc1, fileBased))
		{
			SYS_ERROR("Error in allocating memory for input buffer\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_h264Enc1OutBuffAlloc(&T->g.h264enc1.outBuf, &T->g.h264enc1.outBufDesc))
		{
			SYS_ERROR("Error in allocating memory for output buffer\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}
		if(IH264VENC_TI_ENTIREFRAME != T->g.h264enc1.venc1Params.outputDataMode)
		{
			outobj = &T->g.h264enc1.outBufDesc;
			
		}

		SYS_OUT("Video Encoder <%s> initialized\n", T->g.h264enc1.h264enc1Name);

		/* Start the [capture][encode] process */
		while (nFrames <= maxFrames)
		{
			if (DVEVM_ST_FAIL == dvtb_vidEnc1ReadInput_dm365(&T->g.vpfe, T->sourceFp, &T->g.h264enc1.inBufDesc, fileBased))
			{
				if (DVEVM_ST_TRUE == fileBased)
				{
					if (feof(T->sourceFp))
					{
						SYS_DEBUG("End of source file reached. Exiting ...\n");
						break;
					}
				}

				SYS_ERROR("Error in Read Input \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_FAIL == dvtb_h264Enc1EncProcess(T, nFrames))
			{
				SYS_ERROR("Video encoder Process fails \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			targetBuff = (char *) T->g.h264enc1.outBufDesc.bufs[0];
			targetBytes = T->g.h264enc1.venc1OutArgs.videncOutArgs.bytesGenerated;

			if (DVEVM_ST_FALSE == fileBased)
				dvtb_vpfeReturnBuffer(&T->g.vpfe);

			if( T->g.h264enc1.venc1DynParams.sliceSize )
			{
				packetSizes = (XDAS_Int32 *) T->g.h264enc1.outBufDesc.bufs[1];

				for(numPackets = 0; numPackets < T->g.h264enc1.venc1OutArgs.numPackets; numPackets++)
				{
					SYS_OUT("Packet No.%4d: Size:%8d\n", numPackets, (int)packetSizes[numPackets]);

					if((packetSizes[numPackets] << 3) > T->g.h264enc1.venc1DynParams.sliceSize)
					{
						SYS_OUT("Packet Size exceeded for the prev packet\n");
					}
				}
			}

			if(IH264VENC_TI_ENTIREFRAME == T->g.h264enc1.venc1Params.outputDataMode)
			{
				if (DVEVM_ST_FAIL == dvtb_fileWrite(T->targetFp, (char *) targetBuff, targetBytes))
				{
					SYS_ERROR("Error in writing to file.\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
				else if (DVEVM_ST_TRUE==T->g.h264enc1.venc1DynParams.mvSADoutFlag)
				{
					dvtb_h264enc1MVDump(&T->g.h264enc1, nFrames, fMVFile);
				}
			}
	
			nFrames++;
		}
	} while (DVEVM_ST_FALSE);

	dvtb_h264Enc1ProcessEndMessage(fileBased, nFrames);

	/* Uninitialize and close */
	dvtb_h264Enc1HanClose(&T->g.h264enc1, T->g.eng.name);

	if (DVEVM_ST_TRUE == vpfeOpened)
	{
		dvtb_captureClose(&T->g.vpfe, &T->g.vpPrvw, &T->g.vpRsz);
		SYS_OUT("Capture module closed\n");
	}

	dvtb_h264Enc1OutBuffFree(&T->g.h264enc1.outBufDesc);
	dvtb_h264Enc1InBuffFree(&T->g.h264enc1.inBufDesc, fileBased);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);
	if (fMVFile)
	{
		fclose(fMVFile);
	}

	dvtb_exitMessage(DVEVM_ST_ENCODE, "H264", 0, fileBased, usecaseFailed);
	dvtb_freeThr(T);
	dvtb_threadExit();
}
