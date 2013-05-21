/*
 * dvtbIPNCUC0.c
 *
 * XDM1.0 IPNC Usecase 0 functionality (File based)
 * IPNCUC0:MPEG4 encode (720P 30 fps 6 Mbps + SIF 30 fps 512 Kbps)
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

#include "dvtbIPNCUC0.h"
#include "dvtbIPNCUC0Def.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

#define MVDUMP_720P_FILE        "mvdump-720p.txt"
#define MVDUMP_SIF_FILE         "mvdump-SIF.txt"

DvevmStRetCode
dvtb_IPNCUC0Mpeg4spEnc1InBuffAlloc(DvevmStXdmBuffer *inBuf, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased)
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
dvtb_IPNCUC0Mpeg4spEnc1OutBuffAlloc(DvevmStXdmBuffer *outBuf, XDM_BufDesc *outBufDesc)
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
dvtb_IPNCUC0Mpeg4spEnc1InitPtrs(DvevmStMPEG4SPVEncInfo *ve)
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
dvtb_IPNCUC0Mpeg4spEnc1ReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, IVIDEO1_BufDescIn *inBufDesc, int fileBased)
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
dvtb_IPNCUC0Mpeg4spEnc1EncProcess(DvevmStMPEG4SPVEncInfo *ve , int *encDuration)
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
dvtb_IPNCUC0Mpeg4spEnc1MVDump(IPNCUC0_Motion_MBData *mbData, int frameCols, int frameRows, int nFrames, FILE *fMVFile)
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
IPNCUC0: IPNC Use-case 0
MPEG4 encode (720P 30 fps 6 Mbps + SIF 30 fps 512 Kbps)
*/
void
dvtb_IPNCUC0(DvevmStThreadInfo *T)
{
	int maxFrames = 0, nFrames = 1, mb720pRows = 0, mb720pColumns = 0, frameRows = 0,
		mbSIFRows = 0, mbSIFColumns = 0, targetBytes = DEF_VIDFRAME_SIZE, frameCols = 0,
		encDuration720p = 0, encDurationSIF = 0;


	char *targetBuff = NULL;

	FILE *enc720pOutputFp = NULL, *fMV720pFile = NULL;
	FILE *encSIFOutputFp = NULL, *fMVSIFFile = NULL;

	IPNCUC0_Motion_MBData *mbData = NULL;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE;

	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fMV720pFile, MVDUMP_720P_FILE,"w"))
	{
		SYS_ERROR("Unable to open source file : %s\n", MVDUMP_720P_FILE);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fMVSIFFile, MVDUMP_SIF_FILE,"w"))
	{
		SYS_ERROR("Unable to open source file : %s\n", MVDUMP_SIF_FILE);
		fclose(fMV720pFile);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	T->g.vpfe.capFd = 0;
	maxFrames = T->g.IPNCUC0.numFrames;

	// Open output file (enc720pOutput.m4v) to store encoded stream of 720p resolution
	if (DVEVM_ST_FAIL == dvtb_fileOpen(&enc720pOutputFp, "enc720pOutput.m4v", "w"))
	{
		SYS_ERROR("Unable to open \"enc720pOutput.m4v\" file.\n");

		if (T->sourceFp1)
			fclose(T->sourceFp1);

		if (T->sourceFp2)
			fclose(T->sourceFp2);

		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	// Open output file (encSIFOutput.m4v) to store encoded stream of SIF resolution
	if (DVEVM_ST_FAIL == dvtb_fileOpen(&encSIFOutputFp, "encSIFOutput.m4v", "w"))
	{
		SYS_ERROR("Unable to open \"encSIFOutput.m4v\" file.\n");

		dvtb_fileClose(&T->sourceFp1, &enc720pOutputFp);

		if (T->sourceFp2)
			fclose(T->sourceFp2);

		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	dvtb_startMessage(DVEVM_ST_ENCODE, "IPNCUC0", DVEVM_ST_TRUE, DVEVM_ST_TRUE);
	SYS_DEBUG("Number of frames to encode : %d\n", maxFrames);

	dvtb_IPNCUC0Mpeg4spEnc1InitPtrs(&T->g.IPNCUC0.enc720p);
	dvtb_IPNCUC0Mpeg4spEnc1InitPtrs(&T->g.IPNCUC0.encSIF);

	/* Dummy loop to enable easy cleanup */
	do
	{
		/* Initialize Video Encoder */

		if (DVEVM_ST_FAIL == dvtb_ceInit(T->g.eng.name, &T->g.IPNCUC0.ceHdl))
		{
			SYS_ERROR("Cannot initialize Engine <%s>\n", T->g.eng.name);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		T->g.IPNCUC0.enc720p.ceHdl = T->g.IPNCUC0.ceHdl;
		T->g.IPNCUC0.encSIF.ceHdl = T->g.IPNCUC0.ceHdl;

		//Initialize Codec Instance for 720p encoding
		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Init(&T->g.IPNCUC0.enc720p))
		{
			SYS_ERROR("Unable to initialize Video Encoder <%s> for 720p encoding\n", T->g.IPNCUC0.enc720p.venc1Name);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		//Initialize Codec Instance for SIF encoding
		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Init(&T->g.IPNCUC0.encSIF))
		{
			SYS_ERROR("Unable to initialize Video Encoder <%s> for SIF encoding\n", T->g.IPNCUC0.encSIF.venc1Name);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}


		//Allocate 720p input and output buffer
		if (DVEVM_ST_FAIL == dvtb_IPNCUC0Mpeg4spEnc1InBuffAlloc(&T->g.IPNCUC0.enc720p.inBuf, &T->g.IPNCUC0.enc720p.inBufDesc, DVEVM_ST_TRUE))
		{
			SYS_ERROR("Error in allocating memory for input buffer for 720p Encoding \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_IPNCUC0Mpeg4spEnc1OutBuffAlloc(&T->g.IPNCUC0.enc720p.outBuf, &T->g.IPNCUC0.enc720p.outBufDesc))
		{
			SYS_ERROR("Error in allocating memory for output buffer for 720p Encoding \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		//Allocate SIF input and output buffer
		if (DVEVM_ST_FAIL == dvtb_IPNCUC0Mpeg4spEnc1InBuffAlloc(&T->g.IPNCUC0.encSIF.inBuf, &T->g.IPNCUC0.encSIF.inBufDesc, DVEVM_ST_TRUE))
		{
			SYS_ERROR("Error in allocating memory for input buffer for SIF Encoding \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_IPNCUC0Mpeg4spEnc1OutBuffAlloc(&T->g.IPNCUC0.encSIF.outBuf, &T->g.IPNCUC0.encSIF.outBufDesc))
		{
			SYS_ERROR("Error in allocating memory for output buffer for SIF Encoding \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		SYS_OUT("Video Encoder 720p <%s> & SIF <%s> initialized\n", T->g.IPNCUC0.enc720p.venc1Name, T->g.IPNCUC0.encSIF.venc1Name);

		mb720pColumns = T->g.IPNCUC0.enc720p.venc1DynParams.videncDynamicParams.inputWidth / 16;
		mb720pRows = T->g.IPNCUC0.enc720p.venc1DynParams.videncDynamicParams.inputHeight / 16;

		mbSIFColumns = T->g.IPNCUC0.encSIF.venc1DynParams.videncDynamicParams.inputWidth / 16;
		mbSIFRows = T->g.IPNCUC0.encSIF.venc1DynParams.videncDynamicParams.inputHeight / 16;

		/* Start the [encode] process */
		while (nFrames <= maxFrames)
		{
			//Read 720p Input
			if(DVEVM_ST_FAIL == dvtb_IPNCUC0Mpeg4spEnc1ReadInput(NULL, T->sourceFp1, &T->g.IPNCUC0.enc720p.inBufDesc, DVEVM_ST_TRUE))
			{
				SYS_ERROR("Error in Read Input For 720p Encoding \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (feof(T->sourceFp1))
			{
				SYS_DEBUG("End of 720p source file reached. Exiting ...\n");
				break;
			}


			//Read SIF Input
			if(DVEVM_ST_FAIL == dvtb_IPNCUC0Mpeg4spEnc1ReadInput(NULL, T->sourceFp2, &T->g.IPNCUC0.encSIF.inBufDesc, DVEVM_ST_TRUE))
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

			//Encode 720p frame
			if(DVEVM_ST_FAIL == dvtb_IPNCUC0Mpeg4spEnc1EncProcess(&T->g.IPNCUC0.enc720p, &encDuration720p))
			{
				SYS_ERROR("Unable to encode the 720p input buffer\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Encode SIF frame
			if(DVEVM_ST_FAIL == dvtb_IPNCUC0Mpeg4spEnc1EncProcess(&T->g.IPNCUC0.encSIF, &encDurationSIF))
			{
				SYS_ERROR("Unable to encode the SIF input buffer\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			//Store 720p encoded content, Dump MV, Capture performance
			targetBuff = (char *) T->g.IPNCUC0.enc720p.outBufDesc.bufs[0];
			targetBytes = T->g.IPNCUC0.enc720p.venc1OutArgs.videncOutArgs.bytesGenerated;

			if (targetBytes <= 0)
				SYS_ERROR("&&&&&  ZERO bytes generated while encoding 720p Frame #%d &&&&&\n", nFrames);
			else
			{
				if (T->g.IPNCUC0.enc720p.venc1DynParams.mvDataEnable)
				{
					mbData = (IPNCUC0_Motion_MBData *) T->g.IPNCUC0.enc720p.outBufDesc.bufs[1];
					frameCols = T->g.IPNCUC0.enc720p.venc1Params.subWindowWidth / 16;
					frameRows = T->g.IPNCUC0.enc720p.venc1Params.subWindowHeight / 16;

					dvtb_IPNCUC0Mpeg4spEnc1MVDump(mbData, frameCols, frameRows, nFrames, fMV720pFile);
				}
			}
			SYS_OUT("Instance, 720p, Frame#, %d \n", nFrames);

#ifdef PERF
			SYS_PERF("Instance, 720p, Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", nFrames, targetBytes, encDuration720p);
#endif

			/* Store the processed frame to target file */
			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(enc720pOutputFp, (char *)targetBuff, targetBytes))
			{
				SYS_ERROR("Error in writing to file for 720P Encoding.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}


			//Store SIF encoded content, Dump MV, Capture performance
			targetBuff = (char *) T->g.IPNCUC0.encSIF.outBufDesc.bufs[0];
			targetBytes = T->g.IPNCUC0.encSIF.venc1OutArgs.videncOutArgs.bytesGenerated;

			if (targetBytes <= 0)
				SYS_ERROR("&&&&&  ZERO bytes generated while encoding SIF Frame #%d &&&&&\n", nFrames);
			else
			{
				if (T->g.IPNCUC0.encSIF.venc1DynParams.mvDataEnable)
				{
					mbData = (IPNCUC0_Motion_MBData *) T->g.IPNCUC0.encSIF.outBufDesc.bufs[1];
					frameCols = T->g.IPNCUC0.encSIF.venc1Params.subWindowWidth / 16;
					frameRows = T->g.IPNCUC0.encSIF.venc1Params.subWindowHeight / 16;

					dvtb_IPNCUC0Mpeg4spEnc1MVDump(mbData, frameCols, frameRows, nFrames, fMVSIFFile);
				}
			}

			SYS_OUT("Instance, SIF, Frame#, %d\n", nFrames);
#ifdef PERF
			SYS_PERF("Instance, SIF, Frame#, %d, Frame Size(bytes), %d, , , EncTime(us), %d\n", nFrames, targetBytes, encDurationSIF);
#endif

			/* Store the processed frame to target file */
			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(encSIFOutputFp, (char *)targetBuff, targetBytes))
			{
				SYS_ERROR("Error in writing to file for SIF Encoding.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			nFrames++;
		}
	} while (DVEVM_ST_FALSE);

	SYS_OUT("IPNCUC0 completed for <%d> frames\n", nFrames - 1);

	/* Uninitialize and close */
	dvtb_mpeg4spEnc1Close(&T->g.IPNCUC0.enc720p);
	SYS_OUT("Video Encoder 720p <%s> closed\n", T->g.IPNCUC0.enc720p.venc1Name);

	dvtb_mpeg4spEnc1Close(&T->g.IPNCUC0.encSIF);
	SYS_OUT("Video Encoder SIF <%s> closed\n", T->g.IPNCUC0.encSIF.venc1Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&T->g.IPNCUC0.ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", T->g.eng.name);
	else
		SYS_OUT("Engine <%s> closed\n", T->g.eng.name);

	dvtb_fileClose(&T->sourceFp1, &enc720pOutputFp);
	dvtb_fileClose(&T->sourceFp2, &encSIFOutputFp);

	if (fMV720pFile)
		fclose(fMV720pFile);

	if (fMVSIFFile)
		fclose(fMVSIFFile);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "IPNCUC0", DVEVM_ST_TRUE, DVEVM_ST_TRUE, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
