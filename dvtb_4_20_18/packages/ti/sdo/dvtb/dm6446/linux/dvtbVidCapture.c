/*
 * dvtbVidCapture.c
 *
 * XDM0.9 Video Encode functionality
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

#include "dvtbVidCapture.h"
#include "dvtbVidEnc.h"
#include "dvtbV4L2VPFE.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_vidEncProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
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
dvtb_vidEncInitPtrs(DvevmStVidEncInfo *ve)
{
	int i = 0;

	ve->ceHdl = NULL;
	ve->vencHdl = NULL;

	ve->inBuf.numBufs = 0;
	ve->outBuf.numBufs = 0;
	for(i=0; i<MAX_XDM_BUFS; i++)
	{
		ve->inBuf.bufs[i] = NULL;
		ve->outBuf.bufs[i] = NULL;
	}
}

DvevmStRetCode
dvtb_vidEncHanInit(DvevmStVidEncInfo *ve, char *engName)
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
		if (DVEVM_ST_FAIL == dvtb_vidEncInit(ve))
		{
			SYS_ERROR("Unable to initialize Video Encoder <%s>\n", ve->vencName);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

void
dvtb_vidEncHanClose(DvevmStVidEncInfo *ve, char *engName)
{
	dvtb_vidEncClose(ve);
	SYS_OUT("Video Encoder <%s> closed\n", ve->vencName);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&ve->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_vidEncReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, DvevmStXdmBuffer *inBuf, int fileBased)
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
			inBuf->bufs[0] = vpfe->buffers[vpfe->buf.index].start;
			if (1 != inBuf->numBufs)
			{
				SYS_ERROR("Error: In providing input to codec \n");
				SYS_ERROR("Number of input buffer required by codec is > 1 \n");
				retCode = DVEVM_ST_FAIL;
			}

		}
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

void
dvtb_VidEncCapture(DvevmStThreadInfo *T)
{
	int maxFrames = 0, nFrames = 0, targetBytes = DEF_VIDFRAME_SIZE, width = 0, height = 0,
		encDuration = 0;
	char *targetBuff = NULL;
	DvevmStXdmBuffer oldXdmBuf;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, vpfeOpened = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

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

	dvtb_startMessage(DVEVM_ST_ENCODE, "Video", T->useAlgorithm, fileBased);
	dvtb_vidEncInitPtrs(&T->g.venc);

	maxFrames = T->g.venc.numFrames;

	/* Dummy loop to enable easy cleanup */
	do
	{
		/* If source file is not defined, initialize VPFE
		 * Else initialize the YUV source file to be encoded */
		if (!T->sourceFp)
		{
			width = T->g.vpfe.capWidth;
			height = T->g.vpfe.capHeight;

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

			targetBytes = T->g.vpfe.capSize;
			T->g.venc.vencDynParams.inputWidth = width;
			T->g.venc.vencDynParams.inputHeight = height;

			T->g.venc.inBuf.numBufs = 1;
			T->g.venc.inBuf.bufSizes[0] = VID_FRAME_SIZE(width, height, DEF_BPP);

			T->g.venc.outBuf.numBufs = 1;
			T->g.venc.outBuf.bufSizes[0] = VID_FRAME_SIZE(width, height, DEF_BPP);
		}
		else
		{
			width = T->g.venc.vencDynParams.inputWidth;
			height = T->g.venc.vencDynParams.inputHeight;

			/* Set buffer requirements to support YUV 422/420P encoding */
			if (XDM_YUV_422ILE == T->g.venc.vencParams.inputChromaFormat)
			{
				T->g.venc.inBuf.numBufs = 1;
				T->g.venc.inBuf.bufSizes[0] = VID_FRAME_SIZE(width, height, DEF_BPP);
			}
			else if (XDM_YUV_420P == T->g.venc.vencParams.inputChromaFormat)
			{
				T->g.venc.inBuf.numBufs = 3;
				T->g.venc.inBuf.bufSizes[0] = width * height;
				T->g.venc.inBuf.bufSizes[1] = T->g.venc.inBuf.bufSizes[0] / 4;
				T->g.venc.inBuf.bufSizes[2] = T->g.venc.inBuf.bufSizes[0] / 4;
			}

			T->g.venc.outBuf.numBufs = 1;
			T->g.venc.outBuf.bufSizes[0] = VID_FRAME_SIZE(width, height, DEF_BPP);
		}

		/* Initialize Video Encoder if DSP is to be used */
		if (T->useAlgorithm)
		{
			if (DVEVM_ST_FAIL == dvtb_vidEncHanInit(&T->g.venc, (char *)T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Video Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Video Encoder <%s> initialized\n", T->g.venc.vencName);
		}

		/* Take a backup of allocated XDM buffer if VPFE is to be used */
		if ((DVEVM_ST_FALSE == fileBased) && T->useAlgorithm)
			dvtb_copyXdmBuf(&T->g.venc.inBuf, &oldXdmBuf);

		/* Start the [capture][encode] process */
		while (nFrames++ < maxFrames)
		{
			if(DVEVM_ST_FAIL == dvtb_vidEncReadInput(&T->g.vpfe, T->sourceFp, &T->g.venc.inBuf, fileBased))
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

			if (T->useAlgorithm)
			{
				memset(T->g.venc.outBuf.bufs[0], 0, T->g.venc.outBuf.bufSizes[0]);
				if (DVEVM_ST_FAIL == dvtb_vidEncEncode(&T->g.venc, &encDuration))
				{
					SYS_ERROR("Unable to encode the input buffer\n");
					break;
				}

				targetBuff = T->g.venc.outBuf.bufs[0];
				targetBytes = T->g.venc.vencOutArgs.bytesGenerated;
			}
			else
			{
				targetBuff = T->g.venc.inBuf.bufs[0];
			}

			if (!T->sourceFp)
			{
				dvtb_vpfeReturnBuffer(&T->g.vpfe);
			}

			/* Store the processed frame to target file */
			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(T->targetFp, (char *)targetBuff, targetBytes))
			{
				SYS_ERROR("Error in writing to file.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", nFrames, targetBytes, encDuration);
#ifdef PERF
			SYS_PERF("Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", nFrames, targetBytes, encDuration);
#endif
		}

		/* Restore the backed-up XDM buffer */
		if ((DVEVM_ST_FALSE == fileBased) && T->useAlgorithm)
			dvtb_copyXdmBuf(&oldXdmBuf, &T->g.venc.inBuf);

	} while (DVEVM_ST_FALSE);

	dvtb_vidEncProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

	/* Uninitialize and close */
	if (DVEVM_ST_TRUE == vpfeOpened)
	{
		dvtb_vpfeClose(&T->g.vpfe);
		SYS_OUT("VPFE Device <%s> closed\n", T->g.vpfe.device);
	}

	if (T->useAlgorithm)
		dvtb_vidEncHanClose(&T->g.venc, T->g.eng.name);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "Video", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}
