/*
 * dvtbMpeg4Capture1.c
 *
 * XDM1.0 MPEG4 Encode Functionality
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

#include "dvtbMpeg4Capture1.h"
#include "dvtbMpeg4Enc1.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbV4L2VPFE.h"
#include "dvtbVdce.h"
#include "dvtbMemory.h"
#include "dvtbDefs.h"
#include "dvtbUtils.h"

//#define FOR_DEBUGGING_AT_DSP_END
//#define DUMP_RECON_BUF

void
dvtb_MPEG4Enc1ConvertInputToFrame(DvevmStXdmBuffer *pubInYUV, IVIDEO1_BufDescIn *inBufDesc)
{
	// Variables declared here
	unsigned short j = 0, k = 0;
	unsigned int width = 0, height = 0;
	char *pubSrcY = NULL, *pubSrcU = NULL, *pubSrcV = NULL, *pubDst = NULL;

	// Code starts here
	/*-------------------------------------------------------------------------*/
	/*                           CONVERT LUMINANCE DATA                        */
	/*-------------------------------------------------------------------------*/
	width = inBufDesc->frameWidth;
	height = inBufDesc->frameHeight;
	pubDst = (char *)inBufDesc->bufDesc[0].buf;

	for (j = 0; j < height; j++)
	{
		pubSrcY = (char *)(pubInYUV->bufs[0] + (j * width));

		memcpy(pubDst, pubSrcY, width);

		// Update the destination pointer
		pubDst += width;
	}

	/*-------------------------------------------------------------------------*/
	/*                           CONVERT CHROMINANCE DATA                      */
	/*-------------------------------------------------------------------------*/
	height >>= 1;
	width >>= 1;

	pubDst = (char *)inBufDesc->bufDesc[1].buf;

	for (j = 0; j < height; j++)
	{
		pubSrcU = (char *)(pubInYUV->bufs[1] + (j * width));
		pubSrcV = (char *)(pubInYUV->bufs[2] + (j * width));

		for (k = 0; k < width; k++)
		{
			*pubDst++ = *pubSrcU++;
			*pubDst++ = *pubSrcV++;
		}
	}
}

void
dvtb_MPEG4Enc1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Total # of frames Captured & Encoded = %d \n", nFrames - 1);
		else
			SYS_OUT("Total # of frames Captured = %d \n", nFrames - 1);
	}
	else//File based
		SYS_OUT("Total # of frames Read from File & Encoded = %d \n", nFrames - 1);
}

void
dvtb_MPEG4Enc1InitPtrs(DvevmStMPEG4Enc1Info *ve)
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
dvtb_MPEG4Enc1HanInit(DvevmStMPEG4Enc1Info *ve, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		// Initialize Engine
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &ve->ceHdl))
		{
			SYS_ERROR("Cannot initialize Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}
#ifdef FOR_DEBUGGING_AT_DSP_END
		SYS_DEBUG("Engine opened. Now hit enter to debug on the DSP end.");
		getchar();
#endif

		//Initialize Codec Instance
		if (DVEVM_ST_FAIL == dvtb_MPEG4Enc1Init(ve))
		{
			SYS_ERROR("Unable to initialize Video Encoder <%s>\n", ve->venc1Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

void
dvtb_MPEG4Enc1HanClose(DvevmStMPEG4Enc1Info *ve, char *engName)
{
	dvtb_MPEG4Enc1Close(ve);
	SYS_OUT("Video Encoder <%s> closed\n", ve->venc1Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&ve->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_MPEG4Enc1InBuffAlloc(DvevmStXdmBuffer *inBuf, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased)
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
dvtb_MPEG4Enc1OutBuffAlloc(DvevmStXdmBuffer *outBuf, XDM_BufDesc *outBufDesc)
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

DvevmStRetCode
dvtb_MPEG4Enc1ReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased)
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
		{
			inBufDesc->bufDesc[0].buf = (XDAS_Int8 *) vpfe->buffers[vpfe->buf.index].start;
			if (1 != inBufDesc->numBufs)
			{
				SYS_ERROR("Error: In providing input to codec \n");
				SYS_ERROR("Number of input buffer required by codec is > 1 \n");
				retCode = DVEVM_ST_FAIL;
			}
		}
	}
	else
	{
		for(i = 0; i < inBufDesc->numBufs; i++)
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
dvtb_MPEG4Enc1EncProcess(DvevmStMPEG4Enc1Info *ve, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		// Make video encode process call
		if (DVEVM_ST_FAIL == dvtb_MPEG4Enc1Encode(ve, encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");

			ve->venc1Cmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_MPEG4Enc1Control(ve))
				SYS_ERROR("Unable to get the status\n");
			else
				SYS_ERROR("Codec Error = %d\n", (int) ve->venc1Status.videncStatus.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

		ve->venc1Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_MPEG4Enc1Control(ve))
		{
			SYS_ERROR("Unable to get the status\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

	}while(DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_MPEG4Enc1ConvertFormat(DvevmStThreadInfo *T, DvevmStXdmBuffer *pubInYUVBuff, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_TRUE == fileBased)
	{
		dvtb_MPEG4Enc1ConvertInputToFrame(pubInYUVBuff, inBufDesc);
	}
	else
	{
		T->g.capvdce.inputBuffer = T->g.vpfe.buffers[T->g.vpfe.buf.index].start;
		T->g.capvdce.outputBuffer = T->g.vpfe.buffers[T->g.vpfe.buf.index].start;

		if (DVEVM_ST_FAIL == dvtb_vdceConvert422to420(&T->g.capvdce))
		{
			SYS_ERROR("Chrominance Conversion (420 to 422) Failed\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			inBufDesc->bufDesc[0].buf = (XDAS_Int8 *) T->g.capvdce.outputBuffer;
			inBufDesc->bufDesc[1].buf = (XDAS_Int8 *) &(T->g.capvdce.outputBuffer[T->g.vpfe.capWidth * T->g.vpfe.capHeight]);
		}
	}

	return retCode;
}

void
dvtb_mpeg4Enc1MVDump(Motion_MBData *mbData, int frameCols, int frameRows, int nFrames, FILE *fMVFile)
{
	int i = 0, j = 0;
	fprintf(fMVFile,"*********************************************\n");
	fprintf(fMVFile,"        Frame number = %d                    \n", nFrames);
	fprintf(fMVFile,"*********************************************\n");
	for (i = 0; i < frameRows; i++)
	{
		for (j = 0; j < frameCols; j++)
		{
			fprintf(fMVFile,"Row:%d,Col:%d:: MVx:%d, MVy:%d, SAD:%d\n", i, j, mbData->MVx, mbData->MVy,     mbData->SAD);
			mbData++;
		}
	}
}


void
dvtb_MPEG4Enc1Capture(DvevmStThreadInfo *T)
{
	int i = 0, maxFrames = 0, nFrames = 0, targetBytes = DEF_VIDFRAME_SIZE, width = 0, height = 0,
		encDuration = 0, insertSeqEnd = 0, mbRows = 0, mbColumns = 0;

	char *targetBuff = NULL;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, vpfeOpened = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;
	IVIDEO1_BufDescIn pubInYUVBufDesc;
	DvevmStXdmBuffer pubInYUVBuff;

	FILE *fMVFile = NULL;
	Motion_MBData *mbData = NULL;
	if(DVEVM_ST_FAIL == dvtb_fileOpen(&fMVFile, "mpeg4MVDump.txt", "wb"))
	{
		SYS_ERROR("can not open mpeg4MVDump.txt \n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit( );
	}


	maxFrames = T->g.mpeg4enc1.numFrames;

	/* Quit if target file is not specified */
	if (!T->targetFp)
	{
		SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit( );
		if(fMVFile)
			fclose(fMVFile);
	}

	if(!T->useAlgorithm)
	{
		SYS_ERROR("No DSP option is not supported \n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit();
		if(fMVFile)
			fclose(fMVFile);

	}

	if(!T->sourceFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_ENCODE, "MPEG4", T->useAlgorithm, fileBased);
	dvtb_MPEG4Enc1InitPtrs(&T->g.mpeg4enc1);

	//pubInYUVBuff: Initialize
	pubInYUVBuff.numBufs = 0;
	for(i=0; i<MAX_XDM_BUFS; i++)
		pubInYUVBuff.bufs[i] = NULL;

	if(T->g.mpeg4enc1.venc1DynParams.Insert_End_Seq_code)
	{// if last frame flag is enable then insert end sequence only for last frame.
		insertSeqEnd = 1;
		T->g.mpeg4enc1.venc1DynParams.Insert_End_Seq_code = 0;
	}


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

			if(DVEVM_ST_FAIL == dvtb_vdceSetup(&T->g.capvdce, T->g.vpfe.capHeight, T->g.vpfe.capWidth, T->g.vpfe.capWidth, 2))
			{
				SYS_ERROR("Unable to setup VDCE device \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("VDCE device  <%s> initialized \n", T->g.capvdce.device);
		}

		width = T->g.mpeg4enc1.venc1DynParams.videncDynamicParams.inputWidth;
		height = T->g.mpeg4enc1.venc1DynParams.videncDynamicParams.inputHeight;

		if (DVEVM_ST_FAIL == dvtb_MPEG4Enc1HanInit(&T->g.mpeg4enc1, (char *)T->g.eng.name))
		{
			SYS_ERROR("Unable to initialize Video Encoder Handle \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		T->g.mpeg4enc1.inBufDesc.frameWidth =  T->g.mpeg4enc1.venc1DynParams.videncDynamicParams.inputWidth;
		T->g.mpeg4enc1.inBufDesc.frameHeight = T->g.mpeg4enc1.venc1DynParams.videncDynamicParams.inputHeight;
		// Allocate memory for codec input buffers
		if (DVEVM_ST_FAIL == dvtb_MPEG4Enc1InBuffAlloc(&T->g.mpeg4enc1.inBuf, &T->g.mpeg4enc1.inBufDesc, fileBased))
		{
			SYS_ERROR("Error in allocating memory for input buffer\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_MPEG4Enc1OutBuffAlloc(&T->g.mpeg4enc1.outBuf, &T->g.mpeg4enc1.outBufDesc))
		{
			SYS_ERROR("Error in allocating memory for output buffer\n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_TRUE == fileBased)
		{
			// Allocate memory & Update pubInYUVBuff and pubInYUVBufDesc for "File Read"
			pubInYUVBuff.numBufs = 3;
			pubInYUVBuff.bufSizes[0] = width * height;
			pubInYUVBuff.bufSizes[1] = width * height / 4;
			pubInYUVBuff.bufSizes[2] = width * height / 4;

			if (DVEVM_ST_FAIL == dvtb_MPEG4Enc1InBuffAlloc(&pubInYUVBuff, &pubInYUVBufDesc, DVEVM_ST_TRUE))
			{
				SYS_ERROR("Cannot allocate memory for file read\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
		else
		{
			// Update pubInYUVBufDesc for "capture from driver"
			pubInYUVBufDesc.numBufs = 1;
		}

		/* Start the [capture][encode] process */
		while (nFrames++ < maxFrames)
		{
			if( (nFrames == maxFrames) && insertSeqEnd )
			{ // last frame
				T->g.mpeg4enc1.venc1DynParams.Insert_End_Seq_code = 1;
				T->g.mpeg4enc1.venc1Cmd = XDM_SETPARAMS;
				if (DVEVM_ST_FAIL == dvtb_MPEG4Enc1Control(&T->g.mpeg4enc1))
				{
					SYS_ERROR("Unable to set encoder dynamic parameters\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
			}

			if(DVEVM_ST_FAIL == dvtb_MPEG4Enc1ReadInput(&T->g.vpfe, T->sourceFp, &pubInYUVBufDesc, fileBased))
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
			if(DVEVM_ST_FAIL == dvtb_MPEG4Enc1ConvertFormat(T, &pubInYUVBuff, &T->g.mpeg4enc1.inBufDesc, fileBased))
			{
				SYS_ERROR("Failed to change the input format \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if(DVEVM_ST_FAIL == dvtb_MPEG4Enc1EncProcess(&T->g.mpeg4enc1, &encDuration))
			{
				SYS_ERROR("video encoder Process fails for frame # %d \n", nFrames);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			targetBuff = (char *) T->g.mpeg4enc1.outBufDesc.bufs[0];
			targetBytes = T->g.mpeg4enc1.venc1OutArgs.videncOutArgs.bytesGenerated;

			if(targetBytes > 0)
			{
				if (T->g.mpeg4enc1.venc1DynParams.MVaccessFlag)
				{
					mbData = (Motion_MBData *) T->g.mpeg4enc1.outBuf.bufs[1];
					mbRows = T->g.mpeg4enc1.venc1DynParams.videncDynamicParams.inputWidth / 16;
					mbColumns = T->g.mpeg4enc1.venc1DynParams.videncDynamicParams.inputHeight / 16;
					dvtb_mpeg4Enc1MVDump(mbData, mbColumns, mbRows, nFrames, fMVFile);
				}
			}


			if (T->g.mpeg4enc1.venc1OutArgs.videncOutArgs.inputFrameSkip)
				SYS_ERROR("Frame <%d> Skipped\n", nFrames);
			else
				SYS_OUT("Encoded Frame %d.\n", nFrames);

#ifdef PERF
			SYS_PERF("Thread, %x, Frame#, %d, Frame Type, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, nFrames, (int) T->g.mpeg4enc1.venc1OutArgs.videncOutArgs.encodedFrameType, targetBytes, encDuration);
#endif

			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)targetBuff, targetBytes))
			{
				SYS_ERROR("Error in writing to file.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			

			T->g.mpeg4enc1.venc1OutArgs.videncOutArgs.inputFrameSkip = 0;

			if (DVEVM_ST_FALSE == fileBased)
				dvtb_vpfeReturnBuffer(&T->g.vpfe);
		}
	} while (DVEVM_ST_FALSE);

	dvtb_MPEG4Enc1ProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

	if (pubInYUVBuff.numBufs > 0)
	{
		dvtb_freeCmem(&pubInYUVBuff);
	}

	dvtb_MPEG4Enc1HanClose(&T->g.mpeg4enc1, T->g.eng.name);

	if (DVEVM_ST_TRUE == vpfeOpened)
	{
		dvtb_vpfeClose(&T->g.vpfe);
		SYS_OUT("VPFE Device <%s> closed\n", T->g.vpfe.device);
	}

	if (DVEVM_ST_TRUE == T->g.capvdce.vdceOpened)
	{
		dvtb_vdceClose(&T->g.capvdce);
		SYS_OUT("VDCE Device <%s> closed\n",T->g.capvdce.device);
	}

	if(fMVFile)
		fclose(fMVFile);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "MPEG4", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit( );
}
