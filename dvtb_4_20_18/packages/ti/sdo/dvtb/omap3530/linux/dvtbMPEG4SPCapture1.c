/*
 * dvtbMPEG4SPCapture1.c
 *
 * XDM1.0 MPEG4 Encode SP Functionality
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

#include "dvtbMPEG4SPCapture1.h"
#include "dvtbMPEG4SPEnc1.h"
#include "dvtbV4L2VPFE.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"
#include "dvtbResizer.h"

void
dvtb_mpeg4spEnc1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
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
dvtb_mpeg4spEnc1InitPtrs(DvevmStMPEG4SPVEncInfo *ve)
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
dvtb_mpeg4spEnc1HanInit(DvevmStMPEG4SPVEncInfo *ve, char *engName)
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

		//Initialize Codec Instance
		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Init(ve))
		{
			SYS_ERROR("Unable to initialize Video Encoder <%s>\n", ve->venc1Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

void
dvtb_mpeg4spEnc1HanClose(DvevmStMPEG4SPVEncInfo *ve, char *engName)
{
	dvtb_mpeg4spEnc1Close(ve);
	SYS_OUT("Video Encoder <%s> closed\n", ve->venc1Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&ve->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}


DvevmStRetCode
dvtb_mpeg4spEnc1InBuffAlloc(DvevmStXdmBuffer *inBuf, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased)
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
dvtb_mpeg4spEnc1OutBuffAlloc(DvevmStXdmBuffer *outBuf, XDM_BufDesc *outBufDesc)
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
dvtb_mpeg4spEnc1ReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, IVIDEO1_BufDescIn *inBufDesc, int fileBased)
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
			inBufDesc->bufDesc[0].buf = (XDAS_Int8 *)vpfe->buffers[vpfe->buf.index].start;
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
dvtb_mpeg4spEnc1EncProcess(DvevmStMPEG4SPVEncInfo *ve , int *encDuration)
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
dvtb_mpeg4spEnc1MVDump(Motion_MBData *mbData, int frameCols, int frameRows, int nFrames, FILE *fMVFile)
{
	int i = 0, j = 0;

	fprintf(fMVFile,"*********************************************\n");
	fprintf(fMVFile,"        Frame number = %d                    \n", nFrames);
	fprintf(fMVFile,"*********************************************\n");
	for (i = 0; i < frameRows; i++)
	{
		for (j = 0; j < frameCols; j++)
		{
			fprintf(fMVFile,"Row:%d,Col:%d:: MVx:%d, MVy:%d, SSE:%d\n", i, j, mbData->MVx, mbData->MVy,	mbData->SSE);
			mbData++;
		}
	}

}

void
dvtb_Mpeg4spEnc1Capture(DvevmStThreadInfo *T)
{
	int i = 0, maxFrames = 0, nFrames = 1, mbRows = 0, mbColumns = 0,
		encDuration = 0, iteration = 0, targetBytes = DEF_VIDFRAME_SIZE,  appBufferSize = 0, insertSeqEnd = 0;

	char *targetBuff = NULL, *appBuffer = NULL;

	IVIDEO1_BufDescIn rszOutBufDesc;
	DvevmStXdmBuffer rszOutBuf;

#if 0
	FILE *fMVFile = NULL;
	Motion_MBData *mbData = NULL;
#endif
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, vpfeOpened = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE, rszOpened = DVEVM_ST_FALSE, deInterOpened = DVEVM_ST_FALSE;

#if 0
	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fMVFile, MVDUMP_FILE, "w"))
	{
		SYS_ERROR("Unable to open source file : %s\n", MVDUMP_FILE);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}
#endif
	maxFrames = T->g.mpeg4spenc1.numFrames;

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

	dvtb_startMessage(DVEVM_ST_ENCODE, "Mpeg4", T->useAlgorithm, fileBased);
	dvtb_mpeg4spEnc1InitPtrs(&T->g.mpeg4spenc1);

	if(T->g.vprsz.rszEnable)
	{
		rszOutBuf.numBufs = 0;
		for(i=0; i<MAX_XDM_BUFS; i++)
			rszOutBuf.bufs[i] = NULL;
	}
	memset(&rszOutBufDesc,0x00, sizeof(rszOutBufDesc));

	if(T->g.mpeg4spenc1.venc1DynParams.lastFrame)
	{// if last frame flag is enable then insert end sequence only for last frame.
		insertSeqEnd = 1;
		T->g.mpeg4spenc1.venc1DynParams.lastFrame = 0; 
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

			if(T->g.vprsz.rszEnable)
			{
				T->g.vprsz.rszInputFormat = T->g.mpeg4spenc1.venc1Params.videncParams.inputChromaFormat;
				T->g.vprsz.rszInWidth     = T->g.vpfe.capWidth;
				T->g.vprsz.rszInHeight    = T->g.vpfe.capHeight;
				T->g.vprsz.rszOutWidth    = T->g.mpeg4spenc1.venc1DynParams.videncDynamicParams.inputWidth;
				T->g.vprsz.rszOutHeight   = T->g.mpeg4spenc1.venc1DynParams.videncDynamicParams.inputHeight;

				if (DVEVM_ST_FAIL == dvtb_resizerSetup(&T->g.vprsz))
				{
					SYS_ERROR("Unable to initialize resizer \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
				rszOpened = DVEVM_ST_TRUE;

				if (DVEVM_ST_FAIL == dvtb_resizerOutBuffAlloc(&T->g.vprsz, &rszOutBuf, &rszOutBufDesc))
				{
					SYS_ERROR("Unable to Allocate buffers for resizer \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
			}
		}

		/* Initialize Video Encoder if DSP is to be used */
		if (T->useAlgorithm)
		{
			if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1HanInit(&T->g.mpeg4spenc1, (char *)T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Video Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			T->g.mpeg4spenc1.inBufDesc.frameWidth =  T->g.mpeg4spenc1.venc1DynParams.videncDynamicParams.inputWidth;
			T->g.mpeg4spenc1.inBufDesc.frameHeight = T->g.mpeg4spenc1.venc1DynParams.videncDynamicParams.inputHeight;
	
			if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1InBuffAlloc(&T->g.mpeg4spenc1.inBuf, &T->g.mpeg4spenc1.inBufDesc, fileBased))
			{
				SYS_ERROR("Error in allocating memory for input buffer\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1OutBuffAlloc(&T->g.mpeg4spenc1.outBuf, &T->g.mpeg4spenc1.outBufDesc))
			{
				SYS_ERROR("Error in allocating memory for output buffer\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("MPEG4 Encoder <%s> initialized\n",	T->g.mpeg4spenc1.venc1Name);
		
			if(T->g.vprsz.rszEnable)
			{
				rszOutBufDesc.frameWidth = T->g.mpeg4spenc1.inBufDesc.frameWidth;
				rszOutBufDesc.frameHeight = T->g.mpeg4spenc1.inBufDesc.frameHeight;
				rszOutBufDesc.framePitch = T->g.mpeg4spenc1.inBufDesc.framePitch;
			}	
			if (DVEVM_ST_FALSE == fileBased)
			{
				if(T->g.deinter.deinterEnable)
				{
					T->g.deinter.deinterInWidth     = T->g.vpfe.capWidth;
					T->g.deinter.deinterInHeight    = T->g.vpfe.capHeight;
					T->g.deinter.deinterInputFormat = T->g.mpeg4spenc1.venc1Params.videncParams.inputChromaFormat;
					T->g.deinter.ceHdl              = T->g.mpeg4spenc1.ceHdl;

					if (DVEVM_ST_FAIL == dvtb_deInterInit(&T->g.deinter))
					{
						SYS_ERROR("Unable to initialize DeInterlacer \n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}
					deInterOpened = DVEVM_ST_TRUE;
				}
			}
		}
		else
		{
			appBufferSize = T->g.vpfe.capWidth * T->g.vpfe.capHeight * 2;
			if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&appBuffer, appBufferSize))
			{
				SYS_ERROR("Unable to allocate memory for appBuffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			T->g.mpeg4spenc1.inBufDesc.numBufs = 1;
		}

		mbColumns = T->g.mpeg4spenc1.venc1DynParams.videncDynamicParams.inputWidth / 16;
		mbRows = T->g.mpeg4spenc1.venc1DynParams.videncDynamicParams.inputHeight	/ 16;

		/* Start the [capture][encode] process */
		while (nFrames <= maxFrames)
		{
			if( (nFrames == maxFrames) && insertSeqEnd )
			{ // last frame
				T->g.mpeg4spenc1.venc1DynParams.lastFrame = 1;
				T->g.mpeg4spenc1.venc1Cmd = XDM_SETPARAMS;
				if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Control(&T->g.mpeg4spenc1))
				{
					SYS_ERROR("Unable to set encoder dynamic parameters\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
			}
				
			if (DVEVM_ST_FALSE == fileBased)
			{
				if (!(T->g.mpeg4spenc1.venc1DynParams.videncDynamicParams.targetFrameRate <= 30000 && T->g.mpeg4spenc1.venc1DynParams.videncDynamicParams.targetFrameRate	> 0))
				{
					SYS_ERROR("Invalid Target Frame Rate\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
			}
			if(DVEVM_ST_FAIL == dvtb_mpeg4spEnc1ReadInput(&T->g.vpfe, T->sourceFp, &T->g.mpeg4spenc1.inBufDesc, fileBased))
			{
				SYS_ERROR("Error in Read Input \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			if (DVEVM_ST_TRUE == fileBased)
			{
				if (feof(T->sourceFp))
				{
					SYS_OUT("end of file reached.\n");
					if (++iteration < 2)
					{
						SYS_OUT("resetting input file.\n");
						fseek(T->sourceFp, 0L, SEEK_SET);
						continue;
					}
					else
					{
						SYS_OUT("End of source file reached. Exiting ...\n");
						if(insertSeqEnd)
							 SYS_OUT("Did not insert end of sequence as end of file reached ...\n");
						break;
					}
				}
			}

			if(DVEVM_ST_FALSE == fileBased)
			{
				if(T->g.deinter.deinterEnable)
				{
					if(DVEVM_ST_FAIL == dvtb_copyBufDescToBufs(&T->g.deinter.inBuf,&T->g.mpeg4spenc1.inBufDesc))
					{
						SYS_ERROR("Unable to copy from BufDesc To Bufs \n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}
					
					if(DVEVM_ST_FAIL == dvtb_deInterEncode(&T->g.deinter, &encDuration))
					{
						SYS_ERROR("Unable to deInterlace \n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}
					SYS_DEBUG("DeinterlaceTime %d \n",encDuration);

					if(DVEVM_ST_FAIL == dvtb_copyBufsToBufDesc(&T->g.mpeg4spenc1.inBufDesc,&T->g.deinter.outBuf))
					{
						SYS_ERROR("Unable to copy from Buf To BufDesc \n");
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}
				}

				if(T->g.vprsz.rszEnable)
				{
					if(DVEVM_ST_FAIL == dvtb_resizeImage(&T->g.vprsz, &T->g.mpeg4spenc1.inBufDesc, &rszOutBufDesc))
					{
						SYS_ERROR("Unable to resize \n");	
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}
					memcpy(&T->g.mpeg4spenc1.inBufDesc, &rszOutBufDesc, sizeof(rszOutBufDesc));
				}
			}
			

			if (T->useAlgorithm)
			{
				for (i = 0; i < T->g.mpeg4spenc1.outBuf.numBufs; i++)
					memset(T->g.mpeg4spenc1.outBuf.bufs[i], 0, T->g.mpeg4spenc1.outBuf.bufSizes[i]);

				if(DVEVM_ST_FAIL == dvtb_mpeg4spEnc1EncProcess(&T->g.mpeg4spenc1, &encDuration))
				{
					SYS_ERROR("video encoder Process fails for frame # %d \n", nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				targetBuff = (char *) T->g.mpeg4spenc1.outBuf.bufs[0];
				targetBytes	= T->g.mpeg4spenc1.venc1OutArgs.videncOutArgs.bytesGenerated;

				SYS_OUT("Encoded Frame %d.\n", nFrames);
#ifdef PERF
				SYS_PERF("Thread, %x, Frame#, %d, Frame Type, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, nFrames, (int) T->g.mpeg4spenc1.venc1OutArgs.videncOutArgs.encodedFrameType, targetBytes, encDuration);
#endif

				if (targetBytes <= 0)
					SYS_ERROR("&&&&&  ZERO bytes generated while encoding Frame #%d &&&&&\n", nFrames);
				else
				{
					// Motion Vector Dump
					if (T->g.mpeg4spenc1.venc1DynParams.MVDataEnable)
					{
#if 0
						mbData = (Motion_MBData *) T->g.mpeg4spenc1.outBuf.bufs[1];
						frameCols = T->g.mpeg4spenc1.venc1Params.subWindowWidth / 16;
						frameRows = T->g.mpeg4spenc1.venc1Params.subWindowHeight / 16;

						dvtb_mpeg4spEnc1MVDump(mbData, frameCols, frameRows, nFrames, fMVFile);
#endif
					}
				}
			}
			else
			{
				targetBuff = (char *)T->g.mpeg4spenc1.inBufDesc.bufDesc[0].buf;
				targetBytes = appBufferSize;
				memcpy(appBuffer, targetBuff, targetBytes);
				targetBuff = appBuffer;
				SYS_OUT("Captured Frame %d.\n", nFrames);
			}

			if (!T->sourceFp)
				dvtb_vpfeReturnBuffer(&T->g.vpfe);


			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)targetBuff, targetBytes))
			{
				SYS_ERROR("Error in writing to file.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			nFrames++;
		}
	} while (DVEVM_ST_FALSE);

	dvtb_mpeg4spEnc1ProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

	if(DVEVM_ST_TRUE == deInterOpened)
	{
		dvtb_deInterClose(&T->g.deinter);
		SYS_OUT("Deinterlacer <%s> closed\n", T->g.deinter.deinterName);
	}

	/* Uninitialize and close */
	if (T->useAlgorithm)
		dvtb_mpeg4spEnc1HanClose(&T->g.mpeg4spenc1, T->g.eng.name);
	else
	{
		if(NULL != appBuffer)
			dvtb_freeSingleBufCmem(appBuffer, appBufferSize);
	}

	if(T->g.vprsz.rszEnable)
	{
		if (rszOutBuf.numBufs > 0)
		{
			dvtb_freeCmem(&rszOutBuf);
			rszOutBuf.numBufs = 0;
		}
	}

	if(DVEVM_ST_TRUE == rszOpened)
	{
		dvtb_resizerClose(&T->g.vprsz);
		SYS_OUT("Resizer closed\n");
	}

	if (DVEVM_ST_TRUE == vpfeOpened)
	{
		dvtb_vpfeClose(&T->g.vpfe);
		SYS_OUT("VPFE Device <%s> closed\n", T->g.vpfe.device);
	}
#if 0
	if (fMVFile)
		fclose(fMVFile);
#endif

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "Mpeg4", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
