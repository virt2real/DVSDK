/*
 * dvtbDVREnc.c
 *
 * XDM1.0 DVR Encoding functionality
 * DVRENC:8 channels of CIF, MPEG4, 30fps, bitrate appropriately scaled down, using 2Mbps at D1 as reference.
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

#include "dvtbDVREnc.h"
#include "dvtbDVREncDef.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

DvevmStRetCode
dvtb_DVREncMpeg4spEnc1InBuffAlloc(DvevmStXdmBuffer *inBuf, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased)
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
dvtb_DVREncMpeg4spEnc1OutBuffAlloc(DvevmStXdmBuffer *outBuf, XDM_BufDesc *outBufDesc)
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
dvtb_DVREncMpeg4spEnc1InitPtrs(DvevmStMPEG4SPVEncInfo *ve)
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
dvtb_DVREncMpeg4spEnc1ReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, IVIDEO1_BufDescIn *inBufDesc, int fileBased)
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

void
dvtb_DVREncMpeg4spEnc1MVDump(DVREnc_Motion_MBData *mbData, int frameCols, int frameRows, int nFrames, FILE *fMVFile)
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

DvevmStRetCode
dvtb_DVREncMpeg4spEnc1EncProcess(DvevmStMPEG4SPVEncInfo *ve , int *encDuration)
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

/*
DVREnc: DVR Use-case 1
8 channels of CIF, MPEG4, 30fps, bitrate appropriately scaled down, using 2Mbps at D1 as reference
*/
void
dvtb_DVREnc(DvevmStThreadInfo *T)
{
	int i = 0, j = 0, maxFrames = 0, nFrames = 1, frameRows = 0, frameCols = 0,
		targetBytes = DEF_VIDFRAME_SIZE,instanceCount = MAX_MPEG4_INSTANCES,
		encDuration[MAX_MPEG4_INSTANCES] = { 0 };

	char *targetBuff = NULL, mvFile[MAX_MPEG4_INSTANCES][20];

	FILE *fMVFile[MAX_MPEG4_INSTANCES];
	FILE *sourceFp[MAX_MPEG4_INSTANCES], *encOutputFp[MAX_MPEG4_INSTANCES];

	DVREnc_Motion_MBData *mbData = NULL;
	DvevmStRetCode retVal = DVEVM_ST_SUCCESS;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE;

	retVal = dvtb_openSrcTrgFromInputFile(T->sourceFp, sourceFp, encOutputFp, MAX_MPEG4_INSTANCES);


	if (DVEVM_ST_FAIL == retVal)
	{
		SYS_ERROR("Improper Input File. Exiting...\n");
		for (j = 0; j < MAX_MPEG4_INSTANCES; j++)
		{
			dvtb_fileClose(&sourceFp[j], &encOutputFp[j]);
		}

		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	dvtb_startMessage(DVEVM_ST_ENCODE, "DVREnc", DVEVM_ST_TRUE, DVEVM_ST_TRUE);

	T->g.vpfe.capFd = 0;
	maxFrames = T->g.DVREnc.numFrames;

	SYS_DEBUG("DVREnc started\n");
	SYS_DEBUG("Number of frames to encode : %d\n", maxFrames);

	for (i = 0; i < instanceCount; i++)
		dvtb_DVREncMpeg4spEnc1InitPtrs(&T->g.DVREnc.enc[i]);

	/* Dummy loop to enable easy cleanup */
	do
	{
		for (i = 0; i < instanceCount; i++)
		{
			sprintf(mvFile[i], "mvdump-%d.txt", i);
			if(DVEVM_ST_FAIL == dvtb_fileOpen(&fMVFile[i] , mvFile[i], "w"))
			{
				SYS_ERROR("dvtb File Open failed for <%s>\n", mvFile[i]);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
		if (DVEVM_ST_FAIL == dvtb_ceInit(T->g.eng.name, &T->g.DVREnc.ceHdl))
		{
			SYS_ERROR("Cannot initialize Engine <%s>\n", T->g.eng.name);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		/* Initialize Video Encoder */
		for (i = 0; i < instanceCount; i++)
		{
			T->g.DVREnc.enc[i].ceHdl = T->g.DVREnc.ceHdl;

			if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Init(&T->g.DVREnc.enc[i]))
			{
				SYS_ERROR("Unable to initialize Video Encoder <%s> for EncoderInstance# %d\n", T->g.DVREnc.enc[i].venc1Name, i);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
		if(DVEVM_ST_TRUE == usecaseFailed)//Proceed only if usecase is successful
			break;


		//Allocate input and output buffer
		for (j = 0; j < instanceCount; j++)
		{
			SYS_DEBUG("Instance# %d: InBuf.NumBufs %d\n", j, (int) T->g.DVREnc.enc[j].inBufDesc.numBufs);

			if (DVEVM_ST_FAIL == dvtb_DVREncMpeg4spEnc1InBuffAlloc(&T->g.DVREnc.enc[j].inBuf, &T->g.DVREnc.enc[j].inBufDesc, DVEVM_ST_TRUE))
			{
				SYS_ERROR("Error in allocating memory for input buffer for EncoderInstance# %d \n",j);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_DEBUG("Instance# %d: OutBuf.NumBufs %d\n", j, (int) T->g.DVREnc.enc[j].outBufDesc.numBufs);
			if (DVEVM_ST_FAIL == dvtb_DVREncMpeg4spEnc1OutBuffAlloc(&T->g.DVREnc.enc[j].outBuf, &T->g.DVREnc.enc[j].outBufDesc))
			{
				SYS_ERROR("Error in allocating memory for output buffer for EncoderInstance# %d \n", j);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
		if(DVEVM_ST_TRUE == usecaseFailed)//Proceed only if usecase is successful
			break;

		SYS_OUT("Video Encoders <TotalInstances %d> initialized\n", instanceCount);

		/* Start the [capture][encode] process */
		while (nFrames <= maxFrames)
		{
			for (j = 0; j < instanceCount; j++)
			{
				//Read Input
				if(DVEVM_ST_FAIL == dvtb_DVREncMpeg4spEnc1ReadInput(NULL, sourceFp[j], &T->g.DVREnc.enc[j].inBufDesc, DVEVM_ST_TRUE))
				{
					SYS_ERROR("Error in Read Input For Instance # %d \n", j);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				if (feof(sourceFp[j]))
				{
					SYS_DEBUG("End of source file reached for EncoderInstance# %d.  Exiting ...\n", j);
					break;
				}

				SYS_DEBUG("Instance# %d: Read Input for Frame# %d\n", j, nFrames);

				//Encode frame
				if(DVEVM_ST_FAIL == dvtb_DVREncMpeg4spEnc1EncProcess(&T->g.DVREnc.enc[j], &encDuration[j]))
				{
					SYS_ERROR("EncoderInstance# %d: Unable to encode the input buffer.\n", j);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				SYS_DEBUG("Instance# %d: Encoded Frame# %d\n", j, nFrames);

				//Store encoded content, Dump MV, Capture performance
				targetBuff = (char *) T->g.DVREnc.enc[j].outBufDesc.bufs[0];
				targetBytes = T->g.DVREnc.enc[j].venc1OutArgs.videncOutArgs.bytesGenerated;

				if (targetBytes <= 0)
					SYS_ERROR("&&&&&  ZERO bytes generated while Encoding Frame #%d for EncoderInstance# %d &&&&&\n", nFrames, j);
				else
				{
					if (T->g.DVREnc.enc[j].venc1DynParams.mvDataEnable)
					{
						mbData = (DVREnc_Motion_MBData *) T->g.DVREnc.enc[j].outBufDesc.bufs[1];
						frameCols = T->g.DVREnc.enc[j].venc1Params.subWindowWidth / 16;
						frameRows = T->g.DVREnc.enc[j].venc1Params.subWindowHeight / 16;

						dvtb_DVREncMpeg4spEnc1MVDump(mbData, frameCols, frameRows, nFrames, fMVFile[j]);

					}
				}

				SYS_OUT("Instance, %d, Frame#, %d\n", j, nFrames);
#ifdef PERF
				SYS_PERF("Instance, %d, Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", j, nFrames, targetBytes, encDuration[j]);

#endif

				if(DVEVM_ST_FAIL ==  dvtb_fileWrite(encOutputFp[j], (char *)targetBuff, targetBytes))
				{
					SYS_ERROR("Instance, %d, Error in writing to file.\n",j);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
			}
			if(DVEVM_ST_TRUE == usecaseFailed)//Proceed only if usecase is successful
				break;
			nFrames++;
		}
	} while (DVEVM_ST_FALSE);

	SYS_OUT("DVREnc completed for <%d> frames\n", nFrames - 1);

	/* Uninitialize and close */
	for (i = 0; i < instanceCount; i++)
	{
		dvtb_mpeg4spEnc1Close(&T->g.DVREnc.enc[i]);
		SYS_OUT("Video EncoderInstance# %d <%s> closed\n", i, T->g.DVREnc.enc[i].venc1Name);
	}

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&T->g.DVREnc.ceHdl))
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
		dvtb_fileClose(&sourceFp[i], &encOutputFp[i]);

		if (fMVFile[i])
			fclose(fMVFile[i]);
	}

	dvtb_exitMessage(DVEVM_ST_ENCODE, "DVREnc", DVEVM_ST_TRUE, DVEVM_ST_TRUE, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
