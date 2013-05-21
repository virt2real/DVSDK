/*
 * dvtbImgCapture1.c
 *
 * XDM1.0 Image Encode Functionality
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

#include "dvtbImgCapture1.h"
#include "dvtbImgCapture1Core.h"
#include "dvtbImgEnc1.h"
#include "dvtbV4L2VPFE.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"
#include "dvtbDM365Utils.h"

DvevmStRetCode
dvtb_imgEnc1ReadInput_dm365(DvevmStVpfeInfo *vpfe, FILE *fp, DvevmStXdmBuffer *inBuf, int fileBased)
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
		else if (VID_FMT_YUV420SP == vpfe->capFmt)
		{
			inBuf->bufs[0] = (char *) vpfe->buffers[vpfe->buf.index].start;
			inBuf->bufs[1] = (char *) vpfe->buffers[vpfe->buf.index].start + (vpfe->capWidth * vpfe->capHeight);
		}
		else if (VID_FMT_UYVY == vpfe->capFmt)
		{
			inBuf->bufs[0] = (char *) vpfe->buffers[vpfe->buf.index].start;
		}
		else
		{
			SYS_ERROR("Un-supported capture format selected!\n");
			retCode = DVEVM_ST_FAIL;
		}
	}
	else
	{
		for (i = 0; i < inBuf->numBufs; i++)
					if(DVEVM_ST_FAIL == dvtb_fileRead(fp, (char *)inBuf->bufs[i], inBuf->bufSizes[i], &nBytes))
			{
				SYS_ERROR("Error in file read \n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
	}

	return retCode;
}

void
dvtb_ImgEnc1Capture(DvevmStThreadInfo *T)
{
	int width = 0, height = 0, encDuration = 0, nFrames = 0, targetBytes = DEF_VIDFRAME_SIZE;

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
	if (!T->sourceFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_ENCODE, "Image", T->useAlgorithm, fileBased);
	dvtb_imgEnc1InitPtrs(&T->g.ienc1);

	/* Dummy loop to enable easy cleanup */
	do
	{
		/* If source file is not defined, initialize VPFE
		 * Else initialize the YUV source file to be encoded */
		if (DVEVM_ST_FALSE == fileBased)
		{
			width = T->g.vpfe.capWidth;
			height = T->g.vpfe.capHeight;
			if (DVEVM_ST_FAIL == dvtb_captureSetup(&T->g.vpfe, &T->g.vpPrvw, &T->g.vpRsz))
			{
				SYS_ERROR("Unable to initialize Video Encoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			vpfeOpened = DVEVM_ST_TRUE;
			SYS_OUT("VPFE device <%s> initialized for capture\n", T->g.vpfe.device);


		}
		else
		{
			width = T->g.ienc1.ienc1DynParams.inputWidth;
			height = T->g.ienc1.ienc1DynParams.inputHeight;
		}

		if (DVEVM_ST_FAIL == dvtb_imgEnc1HanInit(&T->g.ienc1, T->g.eng.name))
		{
			SYS_ERROR("Unable to initialize Image Encoder Handle \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}

		SYS_OUT("Image Encoder <%s> initialized\n", T->g.ienc1.ienc1Name);

		/* Take a backup of allocated XDM buffer if VPFE is to be used */
		if (DVEVM_ST_FALSE == fileBased)
		{
			dvtb_copyXdmBuf(&T->g.ienc1.inBuf, &oldXdmBuf);
		}

		do
		{

			/* Start the [capture][encode] process */
			if (DVEVM_ST_FAIL == dvtb_imgEnc1ReadInput_dm365(&T->g.vpfe, T->sourceFp, &T->g.ienc1.inBuf, fileBased))
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

			memset(T->g.ienc1.outBuf.bufs[0], 0, T->g.ienc1.outBuf.bufSizes[0]);
			nFrames++;

			if (DVEVM_ST_FAIL == dvtb_imgEnc1EncProcess(&T->g.ienc1, &encDuration))
			{
				SYS_ERROR("Image encoder Process fails for slice # %d \n", nFrames);
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			targetBuff = T->g.ienc1.outBuf.bufs[0];
			targetBytes = T->g.ienc1.ienc1OutArgs.bytesGenerated;

			SYS_OUT("Encoded Slice#, %d \n", nFrames);
#ifdef PERF
			SYS_PERF("Thread, %x, Slice#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", (unsigned int) T, nFrames, (int) T->g.ienc1.ienc1OutArgs.bytesGenerated, encDuration);
#endif

			if (DVEVM_ST_FALSE == fileBased)
				dvtb_vpfeReturnBuffer(&T->g.vpfe);

			SYS_DEBUG("T->g.ienc1.outBuf.bufs[0] = %x, T->g.ienc1.outBuf.bufSizes[0] = %d\n", (unsigned int) T->g.ienc1.outBuf.bufs[0], (int) T->g.ienc1.outBuf.bufSizes[0]);
			SYS_DEBUG("T->g.ienc1.outBufDesc.descs[0].buf = %x, T->g.ienc1.outBufDesc.descs[0].bufSize = %d\n", (unsigned int) T->g.ienc1.outBufDesc.descs[0].buf, (int) T->g.ienc1.outBufDesc.descs[0].bufSize);
			SYS_DEBUG("targetBuff = %x, targetBytes = %d\n", (unsigned int) targetBuff, targetBytes);

			if (DVEVM_ST_FAIL == dvtb_fileWrite(T->targetFp, (char *) targetBuff, targetBytes))
			{
				SYS_ERROR("Error in writing to file.\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		} while (DVEVM_ST_FALSE);

		/* Restore the backed-up XDM buffer */
		if (DVEVM_ST_FALSE == fileBased)
		{
			dvtb_copyXdmBuf(&oldXdmBuf, &T->g.ienc1.inBuf);
		}
	} while (DVEVM_ST_FALSE);

	dvtb_imgEnc1ProcessEndMessage(0, fileBased, nFrames);

	/* Uninitialize and close */
	dvtb_imgEnc1HanClose(&T->g.ienc1, T->g.eng.name);

	if (DVEVM_ST_TRUE == vpfeOpened)
	{
		dvtb_captureClose(&T->g.vpfe, &T->g.vpPrvw, &T->g.vpRsz);
		SYS_OUT("Capture module closed\n");
	}

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_ENCODE, "Image", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();

}
