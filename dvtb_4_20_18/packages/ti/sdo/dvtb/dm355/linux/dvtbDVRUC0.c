/*
 * dvtbDVRUC0.c
 *
 * XDM1.0 DVR Usecase 0 functionality (File based)
 * DVRUC0:2channels of D1 MPEG4, 30fps, 2Mbps each channel
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

#include "dvtbDVRUC0.h"
#include "dvtbDVRUC0Def.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

#define MVDUMP_1D1_FILE        "mvdump-1D1.txt"
#define MVDUMP_2D1_FILE        "mvdump-2D1.txt"

DvevmStRetCode
dvtb_DVRUC0Mpeg4spEnc1InBuffAlloc(DvevmStXdmBuffer *inBuf, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased)
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
dvtb_DVRUC0Mpeg4spEnc1OutBuffAlloc(DvevmStXdmBuffer *outBuf, XDM_BufDesc *outBufDesc)
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
dvtb_DVRUC0Mpeg4spEnc1InitPtrs(DvevmStMPEG4SPVEncInfo *ve)
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
dvtb_DVRUC0Mpeg4spEnc1ReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, IVIDEO1_BufDescIn *inBufDesc, int fileBased)
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
dvtb_DVRUC0Mpeg4spEnc1EncProcess(DvevmStMPEG4SPVEncInfo *ve , int *encDuration)
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
dvtb_DVRUC0Mpeg4spEnc1MVDump(DVRUC0_Motion_MBData *mbData, int frameCols, int frameRows, int nFrames, FILE *fMVFile)
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

/*
DVRUC0: DVR Use-case 0
2channels of D1 MPEG4, 30fps, 2Mbps each channel
*/
void
dvtb_DVRUC0(DvevmStThreadInfo *T)
{
	int maxFrames = 0, nFrames = 1, mb1D1Rows = 0, mb1D1Columns = 0, frameRows = 0,
		mb2D1Rows = 0, mb2D1Columns = 0, targetBytes = DEF_VIDFRAME_SIZE, frameCols = 0,
		encDuration1D1 = 0, encDuration2D1 = 0;

	char *targetBuff = NULL;

	FILE *enc2D1OutputFp = NULL, *fMV1D1File = NULL;
	FILE *enc1D1OutputFp = NULL, *fMV2D1File = NULL;

	DVRUC0_Motion_MBData *mbData = NULL;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE;

	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fMV1D1File, MVDUMP_1D1_FILE, "w"))
	{
		SYS_ERROR("Unable to open source file : %s\n", MVDUMP_1D1_FILE);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fMV2D1File, MVDUMP_2D1_FILE, "w"))	
	{
		SYS_ERROR("Unable to open source file : %s\n", MVDUMP_2D1_FILE);
		fclose(fMV1D1File);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	T->g.vpfe.capFd = 0;
	maxFrames = T->g.DVRUC0.numFrames;

	// Open output file (enc1D1Output.m4v) to store encoded stream of D1 resolution
	if (DVEVM_ST_FAIL == dvtb_fileOpen(&enc1D1OutputFp ,"enc1D1Output.m4v", "w"))
	{
		SYS_ERROR("Unable to open \"enc1D1Output.m4v\" file.\n");

		if (T->sourceFp1)
			fclose(T->sourceFp1);

		if (T->sourceFp2)
			fclose(T->sourceFp2);

		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	// Open output file (enc2D1Output.m4v) to store encoded stream of D1 resolution
	if (DVEVM_ST_FAIL == dvtb_fileOpen(&enc2D1OutputFp ,"enc2D1Output.m4v", "w"))
	{
		SYS_ERROR("Unable to open \"enc2D1Output.m4v\" file.\n");

		dvtb_fileClose(&T->sourceFp1, &enc1D1OutputFp);

		if (T->sourceFp2)
			fclose(T->sourceFp2);

		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	dvtb_startMessage(DVEVM_ST_ENCODE, "DVRUC0", DVEVM_ST_TRUE, DVEVM_ST_TRUE);
	SYS_DEBUG("Number of frames to encode : %d\n", maxFrames);


	dvtb_DVRUC0Mpeg4spEnc1InitPtrs(&T->g.DVRUC0.enc1D1);
	dvtb_DVRUC0Mpeg4spEnc1InitPtrs(&T->g.DVRUC0.enc2D1);

	/* Dummy loop to enable easy cleanup */
	do
	{
		/* Initialize Video Encoder */
		if (DVEVM_ST_FAIL == dvtb_ceInit(T->g.eng.name, &T->g.DVRUC0.ceHdl))
		{
			SYS_ERROR("Cannot initialize Engine <%s>\n", T->g.eng.name);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		T->g.DVRUC0.enc1D1.ceHdl = T->g.DVRUC0.ceHdl;
		T->g.DVRUC0.enc2D1.ceHdl = T->g.DVRUC0.ceHdl;

		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Init(&T->g.DVRUC0.enc1D1))
		{
			SYS_ERROR("Unable to initialize Video Encoder <%s> for 1D1 encoding\n", T->g.DVRUC0.enc1D1.venc1Name);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Init(&T->g.DVRUC0.enc2D1))
		{
			SYS_ERROR("Unable to initialize Video Encoder <%s> for 2D1 encoding\n", T->g.DVRUC0.enc2D1.venc1Name);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		//Allocate 1D1 input and output buffer
		if (DVEVM_ST_FAIL == dvtb_DVRUC0Mpeg4spEnc1InBuffAlloc(&T->g.DVRUC0.enc1D1.inBuf, &T->g.DVRUC0.enc1D1.inBufDesc, DVEVM_ST_TRUE))
		{
			SYS_ERROR("Error in allocating memory for input buffer for 1D1 Encoding \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_DVRUC0Mpeg4spEnc1OutBuffAlloc(&T->g.DVRUC0.enc1D1.outBuf, &T->g.DVRUC0.enc1D1.outBufDesc))
		{
			SYS_ERROR("Error in allocating memory for output buffer for 1D1 Encoding \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		//Allocate 2D1 input and output buffer
		if (DVEVM_ST_FAIL == dvtb_DVRUC0Mpeg4spEnc1InBuffAlloc(&T->g.DVRUC0.enc2D1.inBuf, &T->g.DVRUC0.enc2D1.inBufDesc, DVEVM_ST_TRUE))
		{
			SYS_ERROR("Error in allocating memory for input buffer for 2D1 Encoding \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_DVRUC0Mpeg4spEnc1OutBuffAlloc(&T->g.DVRUC0.enc2D1.outBuf, &T->g.DVRUC0.enc2D1.outBufDesc))
		{
			SYS_ERROR("Error in allocating memory for output buffer for 2D1 Encoding \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		SYS_OUT("Video Encoder 1D1 <%s> & 2D1 <%s> initialized\n", T->g.DVRUC0.enc1D1.venc1Name, T->g.DVRUC0.enc2D1.venc1Name);

		mb1D1Columns = T->g.DVRUC0.enc1D1.venc1DynParams.videncDynamicParams.inputWidth / 16;
		mb1D1Rows = T->g.DVRUC0.enc1D1.venc1DynParams.videncDynamicParams.inputHeight / 16;

		mb2D1Columns = T->g.DVRUC0.enc2D1.venc1DynParams.videncDynamicParams.inputWidth / 16;
		mb2D1Rows = T->g.DVRUC0.enc2D1.venc1DynParams.videncDynamicParams.inputHeight / 16;

		/* Start the [encode] process */
		while (nFrames <= maxFrames)
		{
			//Read 1D1 Input
			if(DVEVM_ST_FAIL == dvtb_DVRUC0Mpeg4spEnc1ReadInput(&T->g.vpfe, T->sourceFp1, &T->g.DVRUC0.enc1D1.inBufDesc, DVEVM_ST_TRUE))
			{
				SYS_ERROR("Error in Read Input For 1D1 Encoding \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (feof(T->sourceFp1))
			{
				SYS_DEBUG("End of 1D1 source file reached. Exiting ...\n");
				break;
			}

			//Read 2D1 Input
			if(DVEVM_ST_FAIL == dvtb_DVRUC0Mpeg4spEnc1ReadInput(&T->g.vpfe, T->sourceFp2, &T->g.DVRUC0.enc2D1.inBufDesc, DVEVM_ST_TRUE))
			{
				SYS_ERROR("Error in Read Input For 1D1 Encoding \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (feof(T->sourceFp2))
			{
				SYS_DEBUG("End of 2D1 source file reached. Exiting ...\n");
				break;
			}

			//Encode 1D1 frame
			if(DVEVM_ST_FAIL == dvtb_DVRUC0Mpeg4spEnc1EncProcess(&T->g.DVRUC0.enc1D1, &encDuration1D1))
			{
				SYS_ERROR("Unable to encode the 1D1 input buffer\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Encode 2D1 frame
			if(DVEVM_ST_FAIL == dvtb_DVRUC0Mpeg4spEnc1EncProcess(&T->g.DVRUC0.enc2D1, &encDuration2D1))
			{
				SYS_ERROR("Unable to encode the 2D1 input buffer\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Store 1D1 encoded content, Dump MV, Capture performance
			targetBuff = (char *) T->g.DVRUC0.enc1D1.outBufDesc.bufs[0];
			targetBytes = T->g.DVRUC0.enc1D1.venc1OutArgs.videncOutArgs.bytesGenerated;

			if (targetBytes <= 0)
				SYS_ERROR("&&&&&  ZERO bytes generated while encoding 1D1 Frame #%d &&&&&\n", nFrames);
			else
			{
				if (T->g.DVRUC0.enc1D1.venc1DynParams.mvDataEnable)
				{
					mbData = (DVRUC0_Motion_MBData *) T->g.DVRUC0.enc1D1.outBufDesc.bufs[1];
					frameCols = T->g.DVRUC0.enc1D1.venc1Params.subWindowWidth / 16;
					frameRows = T->g.DVRUC0.enc1D1.venc1Params.subWindowHeight / 16;

					dvtb_DVRUC0Mpeg4spEnc1MVDump(mbData, frameCols, frameRows, nFrames, fMV1D1File);

				}
			}
			SYS_OUT("Instance, 1D1, Frame#, %d\n", nFrames);

#ifdef PERF
			SYS_PERF("Instance, 1D1, Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", nFrames, targetBytes, encDuration1D1);
#endif

			/* Store the processed frame to target file */
			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(enc1D1OutputFp, (char *)targetBuff, targetBytes))
			{
				SYS_ERROR("Error in writing to file for 1D1 Encoding.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Store 2D1 encoded content, Dump MV, Capture performance
			targetBuff = (char *) T->g.DVRUC0.enc2D1.outBufDesc.bufs[0];
			targetBytes = T->g.DVRUC0.enc2D1.venc1OutArgs.videncOutArgs.bytesGenerated;

			if (targetBytes <= 0)
				SYS_ERROR("&&&&&  ZERO bytes generated while encoding 2D1 Frame #%d &&&&&\n", nFrames);
			else
			{
				if (T->g.DVRUC0.enc2D1.venc1DynParams.mvDataEnable)
				{
					mbData = (DVRUC0_Motion_MBData *) T->g.DVRUC0.enc2D1.outBufDesc.bufs[1];
					frameCols = T->g.DVRUC0.enc2D1.venc1Params.subWindowWidth / 16;
					frameRows = T->g.DVRUC0.enc2D1.venc1Params.subWindowHeight / 16;

					dvtb_DVRUC0Mpeg4spEnc1MVDump(mbData, frameCols, frameRows, nFrames, fMV2D1File);

				}
			}
			SYS_OUT("Instance, 2D1, Frame#, %d\n", nFrames);

#ifdef PERF
			SYS_PERF("Instance, 2D1, Frame#, %d, Frame Size(bytes), %d, , , EncTime(us), %d\n", nFrames, targetBytes, encDuration2D1);
#endif

			/* Store the processed frame to target file */
			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(enc2D1OutputFp, (char *)targetBuff, targetBytes))
			{
				SYS_ERROR("Error in writing to file for 2D1 Encoding.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			nFrames++;
		}
	} while (DVEVM_ST_FALSE);

	SYS_OUT("DVRUC0 completed for <%d> frames\n", nFrames - 1);

	/* Uninitialize and close */

	dvtb_mpeg4spEnc1Close(&T->g.DVRUC0.enc1D1);
	SYS_OUT("Video Encoder 1D1 <%s> closed\n", T->g.DVRUC0.enc1D1.venc1Name);

	dvtb_mpeg4spEnc1Close(&T->g.DVRUC0.enc2D1);
	SYS_OUT("Video Encoder 2D1 <%s> closed\n", T->g.DVRUC0.enc2D1.venc1Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&T->g.DVRUC0.ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", T->g.eng.name);
	else
		SYS_OUT("Engine <%s> closed\n", T->g.eng.name);

	dvtb_fileClose(&T->sourceFp1, &enc1D1OutputFp);
	dvtb_fileClose(&T->sourceFp2, &enc2D1OutputFp);

	if (fMV1D1File)
		fclose(fMV1D1File);

	if (fMV2D1File)
		fclose(fMV2D1File);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "DVRUC0", DVEVM_ST_TRUE, DVEVM_ST_TRUE, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
