/*
 * dvtbVidPlay.c
 *
 * XDM0.9 Video Decode functionality
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

#include "dvtbVidPlay.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbVidDec.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_vidDecProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Total # of frames Decoded & Displayed = %d.\n", nFrames - 1);
		else
			SYS_OUT("Total # of frames Displayed = %d. \n", nFrames - 1);
	}
	else //File based
		SYS_OUT("Total # of frames Decoded & Dumped = %d. \n", nFrames - 1);
}

void
dvtb_vidDecInitPtrs(DvevmStVidDecInfo *vd, DvevmStVidDecOutBufs *outBufs)
{
	int i = 0, j = 0;

	vd->ceHdl = NULL;
	vd->vdecHdl = NULL;

	vd->inBuf.numBufs = 0;
	vd->outBuf.numBufs = 0;
	for (i = 0; i < MAX_XDM_BUFS; i++)
	{
		vd->inBuf.bufs[i] = NULL;
		vd->outBuf.bufs[i] = NULL;
	}

	for (i = 0; i < MAX_VIDDEC_OUTBUFS; i++)
	{
		outBufs[i].isFree = DVEVM_ST_FALSE;

		outBufs[i].xdmBuf.numBufs = 0;
		for (j = 0; j < MAX_XDM_BUFS; j++)
		{
			outBufs[i].xdmBuf.bufs[j] = NULL;
		}
	}
}

DvevmStRetCode
dvtb_vidDecHanInit(DvevmStVidDecInfo *vd, char *engName, DvevmStVidDecOutBufs *outBufs)
{
	int i = 0, j = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		// Initialize Engine
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &vd->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>.\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

#ifdef FOR_DEBUGGING_AT_DSP_END
		SYS_DEBUG("Engine opened. Now hit enter to debug on the DSP end.");
		getchar();
#endif

		//Initialize Codec Instance
		if (DVEVM_ST_FAIL == dvtb_vidDecInit(vd))
		{
			SYS_ERROR("Unable to initialize Video Decoder <%s>.\n", vd->vdecName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		//Allocate Input Buffers
		if (DVEVM_ST_FAIL == dvtb_allocCmem(&vd->inBuf))
		{
			SYS_ERROR("Unable to allocate memory for input buffer \n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		//Allocate output Buffers
		for (i = 0; i < MAX_VIDDEC_OUTBUFS; i++)
		{
			outBufs[i].isFree = DVEVM_ST_TRUE;
			outBufs[i].xdmBuf.numBufs = vd->outBuf.numBufs;

			for (j = 0; j < vd->outBuf.numBufs; j++)
				outBufs[i].xdmBuf.bufSizes[j] = vd->outBuf.bufSizes[j];

			if (DVEVM_ST_FAIL == dvtb_allocCmem(&outBufs[i].xdmBuf))
			{
				SYS_ERROR("Unable to allocate memory for output buffer [%d]\n", i);
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}
		for (i = 0; i < vd->outBuf.numBufs; i++)
			vd->outBuf.bufs[i] = outBufs[0].xdmBuf.bufs[i];

		outBufs[0].isFree = DVEVM_ST_FALSE;
		outBufs[0].outputId = vd->vdecInArgs.inputID = 0;

	} while (DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

void
dvtb_vidDecHanClose(DvevmStVidDecInfo *vd, char *engName, DvevmStVidDecOutBufs *outBufs)
{
	int i = 0;

	// Free OutPut Buffers
	for (i = 0; i < MAX_VIDDEC_OUTBUFS; i++)
	{
		if(0 < outBufs[i].xdmBuf.numBufs)
			dvtb_freeCmem(&outBufs[i].xdmBuf);
	}

	//Free the allocated Input Buffer
	if (0 < vd->inBuf.numBufs)
		dvtb_freeCmem(&vd->inBuf);

	dvtb_vidDecClose(vd);
	SYS_OUT("Video Decoder <%s> closed.\n", vd->vdecName);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&vd->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>.\n", engName);
	else
		SYS_OUT("Engine <%s> closed.\n", engName);
}

DvevmStRetCode
dvtb_vidDecDecProcess(DvevmStVidDecInfo *vd, int *decDuration)
{
	int frameSize = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		// Make a Decode Process call
		if (DVEVM_ST_FAIL == dvtb_vidDecDecode(vd, decDuration))
		{
			SYS_ERROR("Unable to decode <%s>. \n", vd->vdecName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		frameSize = vd->vdecOutArgs.bytesConsumed;
		if (0 != frameSize)
		{
			vd->vdecCmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_vidDecControl(vd))
			{
				SYS_ERROR("Unable to get the status. \n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}
	} while (DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_vidDecProcessOutBuff(DvevmStVpbeInfo *vpbe, DvevmStXdmBuffer *outbuf, int *bufSizes, FILE *fp, DvevmStBool fileBased)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_TRUE == fileBased)
	{
		for (i = 0; i < outbuf->numBufs; i++)
		{
			if (DVEVM_ST_FAIL == dvtb_fileWrite(fp, (char *)outbuf->bufs[i], bufSizes[i]))
			{
				SYS_ERROR("Error in writing to file.\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}
	}
	else
	{
		if(DVEVM_ST_FAIL ==  dvtb_displayBuffer(vpbe, (char *)outbuf->bufs[0], bufSizes[0]))
		{
			SYS_ERROR("Unable to display Frame \n");
			retCode = DVEVM_ST_FAIL;
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_vidDecFindFreeBuffer(DvevmStVidDecOutBufs *outBufs, DvevmStVidDecInfo *vd)
{
	int i = 0, j = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	for (i = 0; i < MAX_VIDDEC_OUTBUFS; i++)
	{
		if (outBufs[i].isFree)
		{
			for (j = 0; j < outBufs[i].xdmBuf.numBufs; j++)
			{
				vd->outBuf.bufs[j] = outBufs[i].xdmBuf.bufs[j];
			}
			outBufs[i].isFree = DVEVM_ST_FALSE;
			outBufs[i].outputId = ++vd->vdecInArgs.inputID;
			break;
		}
	}
	if (i >= MAX_VIDDEC_OUTBUFS)
	{
		SYS_ERROR("All output buffers full. Unable to allocate output buffer\n");
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStXdmBuffer
*dvtb_vidDecGetDisplayBuffer(DvevmStVidDecOutBufs *outBufs, int outputID)
{
	int i = 0;
	DvevmStXdmBuffer *outbuf = NULL;

	for (i = 0; i < MAX_VIDDEC_OUTBUFS; i++)
	{
		if (!outBufs[i].isFree && (outBufs[i].outputId == outputID))
		{
			outbuf = &outBufs[i].xdmBuf;
			outBufs[i].isFree = DVEVM_ST_TRUE;
			break;
		}
	}

	return outbuf;
}


void
dvtb_VidDecPlay(DvevmStThreadInfo *T)
{
	int nBytes = DVEVM_ST_FAIL, i = 0, nFrames = 0, frameSize = 0, decDuration = 0,
		bufSizes[XDM_MAX_IO_BUFFERS];

	DvevmStRetCode status = DVEVM_ST_FAIL;
	DvevmStXdmBuffer *inbuf = NULL, *outbuf = NULL, dispBuff;
	DvevmStVidDecOutBufs outBufs[MAX_VIDDEC_OUTBUFS];
	DvevmStBool usecaseFailed=DVEVM_ST_FALSE, vpbeOpened=DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;


	SYS_DEBUG("Video [Decode][Play] with <%s> option\n", (T->useAlgorithm) ? "USE DSP" : "NO DSP");

	if (!T->sourceFp)
	{
		SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	if (!T->targetFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_DECODE, "Video",T->useAlgorithm, fileBased);
	dvtb_vidDecInitPtrs(&T->g.vdec, outBufs);

	// [Decode][Play] scenario
	do
	{
		// If target file is not defined, initialize VPBE
		if (DVEVM_ST_FALSE == fileBased)
		{
			status = (*dvtb_vpbeSetupPtr)(&T->g.vpbe);
			if (DVEVM_ST_FAIL == status)
			{
				SYS_ERROR("Unable to setup VPBE device <%s> for display\n", T->g.vpbe.device);
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


			vpbeOpened = DVEVM_ST_TRUE;
			SYS_OUT("VPBE device <%s> initialized for display\n", T->g.vpbe.device);
		}

		if (T->useAlgorithm)
		{
			inbuf = &T->g.vdec.inBuf;
			outbuf = &T->g.vdec.outBuf;

			if (DVEVM_ST_FAIL == dvtb_vidDecHanInit(&T->g.vdec, (char *)T->g.eng.name, outBufs))
			{
				SYS_ERROR("Unable to initialize Video Decoder Handle. \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Video Decoder <%s> initialized\n", T->g.vdec.vdecName);
		}
		else
		{
			dispBuff.numBufs = 1;
			dispBuff.bufSizes[0] = T->g.vpbe.imageWidth * T->g.vpbe.imageHeight * (T->g.vpbe.bpp / 8); // supports 16 bpp and 24 bpp

			if (DVEVM_ST_FAIL == dvtb_allocCmem(&dispBuff))
			{
				SYS_OUT("Unable to allocate memory for video playback\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			inbuf = outbuf = &dispBuff;
		}

		while (!feof(T->sourceFp) && nFrames < T->g.vdec.numFrames)
		{
			if(DVEVM_ST_FAIL == dvtb_fileRead(T->sourceFp, (char *)inbuf->bufs[0], inbuf->bufSizes[0], &nBytes))
			{
				SYS_ERROR("Error in file read \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			if (0 == nBytes)
			{
				SYS_OUT("End of source file reached. Exiting ...\n");
				break;
			}

			if (T->useAlgorithm)
			{
				T->g.vdec.vdecInArgs.numBytes = nBytes;

				if (DVEVM_ST_FAIL == dvtb_vidDecDecProcess(&T->g.vdec, &decDuration))
				{
					SYS_ERROR("Video decoder process fails for frame # %d. \n",nFrames+1);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				frameSize = T->g.vdec.vdecOutArgs.bytesConsumed;
				if (0 == frameSize)
				{
					SYS_ERROR("Video Decode Process returned bytesConsumed as 0. Continue decoding.\n");
					continue;
				}

				if (DVEVM_ST_FAIL == fseek(T->sourceFp, -(nBytes - frameSize), SEEK_CUR))
				{
					SYS_ERROR("Cannot set the file pointer to next frame position\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				SYS_OUT("Decoded Frame %d.\n", nFrames+1);
#ifdef PERF
				SYS_PERF("Frame#, %d, Decoded Frame Size(bytes), %d, DecTime(us), %d\n", nFrames + 1, frameSize, decDuration);
#endif

			}

			nFrames++;

			if (T->useAlgorithm)
			{
				// Check if a frame is ready to be displayed
				SYS_DEBUG("displayable buffer %x\n", (unsigned int) T->g.vdec.vdecOutArgs.displayBufs.bufs[0]);
				if (NULL != T->g.vdec.vdecOutArgs.displayBufs.bufs[0])
				{
					if (NULL == (outbuf = dvtb_vidDecGetDisplayBuffer(outBufs, T->g.vdec.vdecOutArgs.outputID)))
					{
						SYS_ERROR("Unable to find decoded output buffer <%d> for display\n", (int) T->g.vdec.vdecOutArgs.outputID);
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}
					T->g.vpbe.imageWidth = T->g.vdec.vdecStatus.outputWidth;
					T->g.vpbe.imageHeight = T->g.vdec.vdecStatus.outputHeight;

					for(i = 0; i < outbuf->numBufs; i++)
						bufSizes[i] = T->g.vdec.vdecOutArgs.displayBufs.bufSizes[i];
				}
			}
			else
			{
				bufSizes[0] = nBytes;
			}

			if(DVEVM_ST_FAIL == dvtb_vidDecProcessOutBuff(&T->g.vpbe, outbuf, bufSizes, T->targetFp, fileBased))
			{
				SYS_ERROR("Unable to process output buffer for frame# %d \n", nFrames);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			// Allocate next free buffer to output buffer
			if (T->useAlgorithm)
			{
				if(DVEVM_ST_FAIL == dvtb_vidDecFindFreeBuffer(outBufs, &T->g.vdec))
				{
					SYS_ERROR("Unable to Find next buffer for frame# %d \n", nFrames+1);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
			}
		} // end while !feof

	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_vidDecProcessEndMessage(T->useAlgorithm, fileBased, nFrames+1);

	if(DVEVM_ST_TRUE == vpbeOpened)
	{
		dvtb_vpbeClose(&T->g.vpbe);
		SYS_OUT("VPBE Device <%s> closed.\n", T->g.vpbe.device);
	}

	if (T->useAlgorithm)
		dvtb_vidDecHanClose(&T->g.vdec, T->g.eng.name, outBufs);
	else
		dvtb_freeCmem(&dispBuff);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_DECODE, "Video", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
