/*
 * dvtbIPNCUC1.c
 *
 * XDM1.0 IPNC Usecase 1 functionality
 * IPNCUC1:MPEG4, D1, 30fps, 2Mbps + MPEG4, SIF, 30fps, 0.5Mbps + JPEG, D1, 15 fps, QP=75
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

#include "dvtbIPNCUC1.h"
#include "dvtbIPNCUC1Def.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

#define MVDUMP_D1_FILE        "mvdump-D1.txt"
#define MVDUMP_SIF_FILE       "mvdump-SIF.txt"

DvevmStRetCode
dvtb_IPNCUC1Mpeg4spEnc1InBuffAlloc(DvevmStXdmBuffer *inBuf, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased)
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
dvtb_IPNCUC1Mpeg4spEnc1OutBuffAlloc(DvevmStXdmBuffer *outBuf, XDM_BufDesc *outBufDesc)
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
dvtb_IPNCUC1Mpeg4spEnc1InitPtrs(DvevmStMPEG4SPVEncInfo *ve)
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
dvtb_IPNCUC1Mpeg4spEnc1ReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, IVIDEO1_BufDescIn *inBufDesc, int fileBased)
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
dvtb_IPNCUC1Mpeg4spEnc1EncProcess(DvevmStMPEG4SPVEncInfo *ve , int *encDuration)
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
dvtb_IPNCUC1Mpeg4spEnc1MVDump(IPNCUC1_Motion_MBData *mbData, int frameCols, int frameRows, int nFrames, FILE *fMVFile)
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
dvtb_IPNCUC1ImgEnc1InitPtrs(DvevmStImgEnc1Info *ienc)
{
	int i = 0;

	ienc->ceHdl = NULL;
	ienc->ienc1Hdl = NULL;

	ienc->inBuf.numBufs = 0;
	ienc->outBuf.numBufs = 0;
	for(i=0; i<MAX_XDM_BUFS; i++)
	{
		ienc->inBuf.bufs[i] = NULL;
		ienc->outBuf.bufs[i] = NULL;
	}
}

DvevmStRetCode
dvtb_IPNCUC1ImgEnc1EncProcess(DvevmStImgEnc1Info *ienc, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_imgEnc1Encode(ienc, encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");

			ienc->ienc1Cmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_imgEnc1Control(ienc))
				SYS_ERROR("Unable to get the status\n");
			else
				SYS_ERROR("Codec Error = %d\n", (int) ienc->ienc1Status.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

		SYS_DEBUG("numAU(Dyaminc params) = %d, currentAU(Outargs) = %d, TotalAU(Status) = %d\n", (int) ienc->ienc1DynParams.numAU, (int) ienc->ienc1OutArgs.currentAU, (int) ienc->ienc1Status.totalAU);

		ienc->ienc1Cmd = XDM_GETSTATUS;

		if (DVEVM_ST_FAIL == dvtb_imgEnc1Control(ienc))
		{
			SYS_ERROR("Unable to get the status\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;

}

DvevmStRetCode
dvtb_IPNCUC1ImgEnc1ReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, DvevmStXdmBuffer *inBuf, int fileBased)
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
			inBuf->bufs[0] = (char *)vpfe->buffers[vpfe->buf.index].start;
	}
	else
	{
		for(i=0; i < inBuf->numBufs; i++)
		{
			if(DVEVM_ST_FAIL == dvtb_fileRead(fp, (char *)inBuf->bufs[i], inBuf->bufSizes[i], &nBytes))
			{
				SYS_ERROR("Error in file read \n");
				retCode = DVEVM_ST_FAIL;
			}
		}

	}

	return retCode;
}

/*
IPNCUC1: IPNC Use-case 1
MPEG4, D1, 30fps, 2Mbps + MPEG4, SIF, 30fps, 0.5Mbps + JPEG,D1, 15 fps, QP=75
*/
void
dvtb_IPNCUC1(DvevmStThreadInfo *T)
{
	int maxFrames = 0, nFrames = 1, mbD1Rows = 0, mbD1Columns = 0, frameRows = 0,
		mbSIFRows = 0, mbSIFColumns = 0, targetBytes = DEF_VIDFRAME_SIZE, frameCols = 0,
		encDurationD1 = 0, encDurationJPEGD1 = 0, encDurationSIF = 0;

	char *targetBuff = NULL, encJPEGD1OutputFileName[32];

	FILE *encD1OutputFp = NULL, *fMVD1File = NULL;
	FILE *encSIFOutputFp = NULL, *fMVSIFFile = NULL;
	FILE *encJPEGD1OutputFp = NULL;

	IPNCUC1_Motion_MBData *mbData = NULL;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE;

	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fMVD1File, MVDUMP_D1_FILE, "w"))
	{
		SYS_ERROR("Unable to open source file : %s\n", MVDUMP_D1_FILE);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fMVSIFFile, MVDUMP_SIF_FILE, "w"))
	{
		SYS_ERROR("Unable to open source file : %s\n", MVDUMP_SIF_FILE);
		fclose(fMVD1File);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	T->g.vpfe.capFd = 0;
	maxFrames = T->g.IPNCUC1.numFrames;

	// Open output file (encD1Output.m4v) to store encoded stream of D1 resolution
	if (DVEVM_ST_FAIL == dvtb_fileOpen(&encD1OutputFp, "encD1Output.m4v", "w"))
	{
		SYS_ERROR("Unable to open \"encD1Output.m4v\" file.\n");

		if (T->sourceFp1)
			fclose(T->sourceFp1);

		if (T->sourceFp2)
			fclose(T->sourceFp2);

		if (T->sourceFp3)
			fclose(T->sourceFp3);

		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	// Open output file (encSIFOutput.m4v) to store encoded stream of SIF resolution
	if (DVEVM_ST_FAIL == dvtb_fileOpen(&encSIFOutputFp, "encSIFOutput.m4v", "w"))
	{
		SYS_ERROR("Unable to open \"encSIFOutput.m4v\" file.\n");

		if (T->sourceFp1)
			fclose(T->sourceFp1);

		if (T->sourceFp2)
			fclose(T->sourceFp2);

		if (T->sourceFp3)
			fclose(T->sourceFp3);

		if (encD1OutputFp)
			fclose(encD1OutputFp);

		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	dvtb_startMessage(DVEVM_ST_ENCODE, "IPNCUC1", DVEVM_ST_TRUE, DVEVM_ST_TRUE);
	SYS_DEBUG("Number of frames to encode : %d\n", maxFrames);

	dvtb_IPNCUC1Mpeg4spEnc1InitPtrs(&T->g.IPNCUC1.encD1);
	dvtb_IPNCUC1Mpeg4spEnc1InitPtrs(&T->g.IPNCUC1.encSIF);
	dvtb_IPNCUC1ImgEnc1InitPtrs(&T->g.IPNCUC1.encJPEGD1);

	/* Dummy loop to enable easy cleanup */
	do
	{
		/* Initialize Video Encoder */

		if (DVEVM_ST_FAIL == dvtb_ceInit(T->g.eng.name, &T->g.IPNCUC1.ceHdl))
		{
			SYS_ERROR("Cannot initialize Engine <%s>\n", T->g.eng.name);
			break;
		}

		T->g.IPNCUC1.encD1.ceHdl = T->g.IPNCUC1.ceHdl;
		T->g.IPNCUC1.encSIF.ceHdl = T->g.IPNCUC1.ceHdl;
		T->g.IPNCUC1.encJPEGD1.ceHdl = T->g.IPNCUC1.ceHdl;

		//Initialize Codec Instance for video encoding of D1 resolution
		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Init(&T->g.IPNCUC1.encD1))
		{
			SYS_ERROR("Unable to initialize Video Encoder <%s> for D1 encoding\n", T->g.IPNCUC1.encD1.venc1Name);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		//Initialize Codec Instance for video encoding of SIF resolution
		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Init(&T->g.IPNCUC1.encSIF))
		{
			SYS_ERROR("Unable to initialize Video Encoder <%s> for SIF encoding\n", T->g.IPNCUC1.encSIF.venc1Name);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		//Initialize Codec Instance for Image encoding of D1 size
		if (DVEVM_ST_FAIL == dvtb_imgEnc1Init(&T->g.IPNCUC1.encJPEGD1))
		{
			SYS_ERROR("Unable to initialize Image Encoder <%s> for D1 encoding\n", T->g.IPNCUC1.encJPEGD1.ienc1Name);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		//Allocate D1 input and output buffer for video encoder
		if (DVEVM_ST_FAIL == dvtb_IPNCUC1Mpeg4spEnc1InBuffAlloc(&T->g.IPNCUC1.encD1.inBuf, &T->g.IPNCUC1.encD1.inBufDesc, DVEVM_ST_TRUE))
		{
			SYS_ERROR("Error in allocating memory for input buffer for D1 Encoding \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_IPNCUC1Mpeg4spEnc1OutBuffAlloc(&T->g.IPNCUC1.encD1.outBuf, &T->g.IPNCUC1.encD1.outBufDesc))
		{
			SYS_ERROR("Error in allocating memory for output buffer for D1 Encoding \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		//Allocate SIF input and output buffer for video encoder
		if (DVEVM_ST_FAIL == dvtb_IPNCUC1Mpeg4spEnc1InBuffAlloc(&T->g.IPNCUC1.encSIF.inBuf, &T->g.IPNCUC1.encSIF.inBufDesc, DVEVM_ST_TRUE))
		{
			SYS_ERROR("Error in allocating memory for input buffer for SIF Encoding \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_IPNCUC1Mpeg4spEnc1OutBuffAlloc(&T->g.IPNCUC1.encSIF.outBuf, &T->g.IPNCUC1.encSIF.outBufDesc))
		{
			SYS_ERROR("Error in allocating memory for output buffer for SIF Encoding \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		SYS_OUT("MPEG4 Enc D1 <%s> , MPEG4 Enc SIF <%s> & JPEG Enc D1 <%s> initialized\n", T->g.IPNCUC1.encD1.venc1Name, T->g.IPNCUC1.encSIF.venc1Name, T->g.IPNCUC1.encJPEGD1.ienc1Name);

		mbD1Columns = T->g.IPNCUC1.encD1.venc1DynParams.videncDynamicParams.inputWidth / 16;
		mbD1Rows = T->g.IPNCUC1.encD1.venc1DynParams.videncDynamicParams.inputHeight / 16;

		mbSIFColumns = T->g.IPNCUC1.encSIF.venc1DynParams.videncDynamicParams.inputWidth / 16;
		mbSIFRows = T->g.IPNCUC1.encSIF.venc1DynParams.videncDynamicParams.inputHeight / 16;

		/* Start the [encode] process */
		while (nFrames <= maxFrames)
		{
			//Read D1 Input for video encoding
			if(DVEVM_ST_FAIL == dvtb_IPNCUC1Mpeg4spEnc1ReadInput(NULL, T->sourceFp1, &T->g.IPNCUC1.encD1.inBufDesc, DVEVM_ST_TRUE))
			{
				SYS_ERROR("Error in Read Input For D1 Encoding \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (feof(T->sourceFp1))
			{
				SYS_DEBUG("End of D1 source file reached. Exiting ...\n");
				break;
			}

			//Read SIF Input for video encoding
			if(DVEVM_ST_FAIL == dvtb_IPNCUC1Mpeg4spEnc1ReadInput(NULL, T->sourceFp2, &T->g.IPNCUC1.encSIF.inBufDesc, DVEVM_ST_TRUE))
			{
				SYS_ERROR("Error in Read Input For SIF Encoding \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (feof(T->sourceFp2))
			{
				SYS_DEBUG("End of SIF source file reached. Exiting ...\n");
				break;
			}

			//Read JPEG D1 Input only for alternate iterations to achieve 15 fps
			if (0 != (nFrames % 2))
			{
				if(DVEVM_ST_FAIL == dvtb_IPNCUC1ImgEnc1ReadInput(NULL, T->sourceFp3, &T->g.IPNCUC1.encJPEGD1.inBuf, DVEVM_ST_TRUE))
				{
					SYS_ERROR("Error in Read Input for jpeg Encoding \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				if (feof(T->sourceFp3))
				{
					SYS_DEBUG("End of JPEG source file reached. Exiting ...\n");
					break;
				}
			}

			//Video Encode D1 frame
			if(DVEVM_ST_FAIL == dvtb_IPNCUC1Mpeg4spEnc1EncProcess(&T->g.IPNCUC1.encD1, &encDurationD1))
			{
				SYS_ERROR("Unable to encode the D1 input buffer\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Video Encode SIF frame
			if(DVEVM_ST_FAIL == dvtb_IPNCUC1Mpeg4spEnc1EncProcess(&T->g.IPNCUC1.encSIF, &encDurationSIF))
			{
				SYS_ERROR("Unable to encode the SIF input buffer\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Encode JPEG
			if (0 != (nFrames % 2))
			{
				if(DVEVM_ST_FAIL == dvtb_IPNCUC1ImgEnc1EncProcess(&T->g.IPNCUC1.encJPEGD1, &encDurationJPEGD1))
				{
					SYS_ERROR("Unable to encode the JPEG D1 Input buffer\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				SYS_DEBUG("numAU(Dyaminc params) = %d, currentAU(Outargs) = %d, TotalAU(Status) = %d\n", (int) T->g.IPNCUC1.encJPEGD1.ienc1DynParams.numAU, (int) T->g.IPNCUC1.encJPEGD1.ienc1OutArgs.currentAU, (int) T->g.IPNCUC1.encJPEGD1.ienc1Status.totalAU);

			}

			//Store D1 encoded content, Dump MV, Capture performance
			targetBuff = (char *) T->g.IPNCUC1.encD1.outBufDesc.bufs[0];
			targetBytes = T->g.IPNCUC1.encD1.venc1OutArgs.videncOutArgs.bytesGenerated;

			if (targetBytes <= 0)
				SYS_ERROR("&&&&&  ZERO bytes generated while encoding D1 Frame #%d &&&&&\n", nFrames);
			else
			{
				if (T->g.IPNCUC1.encD1.venc1DynParams.mvDataEnable)
				{
					mbData = (IPNCUC1_Motion_MBData *) T->g.IPNCUC1.encD1.outBufDesc.bufs[1];
					frameCols = T->g.IPNCUC1.encD1.venc1Params.subWindowWidth / 16;
					frameRows = T->g.IPNCUC1.encD1.venc1Params.subWindowHeight / 16;

					dvtb_IPNCUC1Mpeg4spEnc1MVDump(mbData, frameCols, frameRows, nFrames, fMVD1File);
				}
			}
			SYS_OUT("Instance, D1, Frame#, %d\n", nFrames);
#ifdef PERF
			SYS_PERF("Instance, D1, Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", nFrames, targetBytes, encDurationD1);
#endif

			// Store the D1 processed frame to target file
			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(encD1OutputFp, (char *)targetBuff, targetBytes))
			{
				SYS_ERROR("Error in writing to file for D1 Encoding.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Store SIF encoded content, Dump MV, Capture performance
			targetBuff = (char *) T->g.IPNCUC1.encSIF.outBufDesc.bufs[0];
			targetBytes = T->g.IPNCUC1.encSIF.venc1OutArgs.videncOutArgs.bytesGenerated;

			if (targetBytes <= 0)
				SYS_ERROR("&&&&&  ZERO bytes generated while encoding SIF Frame #%d &&&&&\n", nFrames);
			else
			{
				if (T->g.IPNCUC1.encSIF.venc1DynParams.mvDataEnable)
				{
					mbData = (IPNCUC1_Motion_MBData *) T->g.IPNCUC1.encSIF.outBufDesc.bufs[1];
					frameCols = T->g.IPNCUC1.encSIF.venc1Params.subWindowWidth / 16;
					frameRows = T->g.IPNCUC1.encSIF.venc1Params.subWindowHeight / 16;

					dvtb_IPNCUC1Mpeg4spEnc1MVDump(mbData, frameCols, frameRows, nFrames, fMVSIFFile);
				}
			}

			SYS_OUT("Instance, SIF, Frame#, %d\n", nFrames);
#ifdef PERF
			SYS_PERF("Instance, SIF, Frame#, %d, Frame Size(bytes), %d, , , EncTime(us), %d\n", nFrames, targetBytes, encDurationSIF);
#endif

			// Store the processed SIF frame to target file
			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(encSIFOutputFp, (char *)targetBuff, targetBytes))
			{
				SYS_ERROR("Error in writing to file for SIF Encoding.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Store the JPEG Frame
			if (0 != (nFrames % 2))
			{
				targetBuff = T->g.IPNCUC1.encJPEGD1.outBuf.bufs[0];
				targetBytes = T->g.IPNCUC1.encJPEGD1.ienc1OutArgs.bytesGenerated;

				sprintf(encJPEGD1OutputFileName, "encJPEGD1Output%d.jpg", nFrames / 2);
				if (DVEVM_ST_FAIL == dvtb_fileOpen(&encJPEGD1OutputFp, encJPEGD1OutputFileName, "w"))
				{
					SYS_ERROR("Unable to open \"%s\" file.\n", encJPEGD1OutputFileName);

					dvtb_freeThr(T);
					dvtb_threadExit();
				}
				SYS_OUT("Instance, JPEG D1, Frame#, %d\n", nFrames);
#ifdef PERF
				SYS_PERF("Instance, JPEG D1, Frame#, %d, Frame Size(bytes), %d, , , , , EncTime(us), %d\n", nFrames, (int) T->g.IPNCUC1.encJPEGD1.ienc1OutArgs.bytesGenerated, encDurationJPEGD1);
#endif

				if(DVEVM_ST_FAIL ==  dvtb_fileWrite(encJPEGD1OutputFp, (char *)targetBuff, targetBytes))
				{
					SYS_ERROR("Error in writing to file for JPEG encoding.\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				if (encJPEGD1OutputFp)
				{
					fclose(encJPEGD1OutputFp);
					encJPEGD1OutputFp = NULL;
				}
			}
			nFrames++;
		}
	} while (DVEVM_ST_FALSE);

	SYS_OUT("IPNCUC1 completed for <%d> frames\n", nFrames - 1);

	/* Uninitialize and close */
	dvtb_mpeg4spEnc1Close(&T->g.IPNCUC1.encD1);
	SYS_OUT("Video Encoder D1 <%s> closed\n", T->g.IPNCUC1.encD1.venc1Name);

	dvtb_mpeg4spEnc1Close(&T->g.IPNCUC1.encSIF);
	SYS_OUT("Video Encoder SIF <%s> closed\n", T->g.IPNCUC1.encSIF.venc1Name);

	dvtb_imgEnc1Close(&T->g.IPNCUC1.encJPEGD1);
	SYS_OUT("Image Encoder D1 <%s> closed\n", T->g.IPNCUC1.encJPEGD1.ienc1Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&T->g.IPNCUC1.ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", T->g.eng.name);
	else
		SYS_OUT("Engine <%s> closed\n", T->g.eng.name);


	dvtb_fileClose(&T->sourceFp1, &encD1OutputFp);
	dvtb_fileClose(&T->sourceFp2, &encSIFOutputFp);
	dvtb_fileClose(&T->sourceFp3, &encJPEGD1OutputFp);

	if (fMVD1File)
		fclose(fMVD1File);

	if (fMVSIFFile)
		fclose(fMVSIFFile);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "IPNCUC1", DVEVM_ST_TRUE, DVEVM_ST_TRUE, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
