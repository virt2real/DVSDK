/*
 * dvtbImgDisplay1.c
 *
 * XDM1.0 Image Decode Functionality
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

#include "dvtbImgDisplay1.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbImgDec1.h"
#include "dvtbMemory.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"
#include "dvtbDM365Utils.h"
#include "dvtbImgDisplay1Core.h"


DvevmStRetCode
dvtb_imgDec1ProcessOutBuff_dm365(DvevmStImgDec1Info *idec1, DvevmStVpbeInfo *vpbe, FILE * targetFp, int nFrames)
{
	void *tempDispBuf = NULL, *tempDispBuf2 = NULL;
	unsigned int imgSizeBuf0 = 0, imgSizeBuf1 = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (NULL != targetFp)
		{
			if (XDM_YUV_422ILE == idec1->idec1Status.outputChromaFormat)
			{
				imgSizeBuf0 = idec1->idec1Status.outputHeight * idec1->idec1Status.outputWidth * 2;
				if (DVEVM_ST_FAIL == dvtb_fileWrite(targetFp, (char *) idec1->outBuf.bufs[0], imgSizeBuf0))
				{
					SYS_ERROR("Error in writing to file.\n");
					retCode = DVEVM_ST_FAIL;
					break;
				}
			}
			else if (XDM_YUV_420SP == idec1->idec1Status.outputChromaFormat)
			{
				imgSizeBuf0 = idec1->idec1Status.outputHeight * idec1->idec1Status.outputWidth;
				imgSizeBuf1 = idec1->idec1Status.outputHeight * idec1->idec1Status.outputWidth / 2;
				if (DVEVM_ST_FAIL == dvtb_fileWrite(targetFp, (char *) idec1->outBuf.bufs[0], imgSizeBuf0))
				{
					SYS_ERROR("Error in writing to file.\n");
					retCode = DVEVM_ST_FAIL;
					break;
				}
				else if (DVEVM_ST_FAIL == dvtb_fileWrite(targetFp, (char *) idec1->outBuf.bufs[1], imgSizeBuf1))
				{
					SYS_ERROR("Error in writing to file.\n");
					retCode = DVEVM_ST_FAIL;
					break;
				}
			}

			SYS_OUT("Dumped Frame# %d.\n", nFrames);
		}
		else
		{
			tempDispBuf = dvtb_vpbeGetDisplayBuffer(vpbe);
			if (NULL == tempDispBuf)
			{
				SYS_ERROR("Unable to get the Display buffer.\n");
				retCode = DVEVM_ST_FAIL;
			}
			else if (XDM_YUV_422ILE == idec1->idec1Status.outputChromaFormat)
			{
				imgSizeBuf0 = idec1->idec1Status.outputHeight * idec1->idec1Status.outputWidth * 2;
				memcpy(tempDispBuf, idec1->outBuf.bufs[0], imgSizeBuf0);
			}
			else if (XDM_YUV_420SP == idec1->idec1Status.outputChromaFormat)
			{
				imgSizeBuf0 = idec1->idec1Status.outputHeight * idec1->idec1Status.outputWidth;
				imgSizeBuf1 = idec1->idec1Status.outputHeight * idec1->idec1Status.outputWidth / 2;
				memcpy(tempDispBuf, idec1->outBuf.bufs[0], imgSizeBuf0);
				memcpy(tempDispBuf + imgSizeBuf0, idec1->outBuf.bufs[1], imgSizeBuf1);
			}

			if (DVEVM_ST_SUCCESS != dvtb_vpbeDisplay(vpbe, tempDispBuf))
			{
				SYS_ERROR("Unable to Display.\n");
				retCode = DVEVM_ST_FAIL;
			}

			tempDispBuf2 = dvtb_vpbeGetDisplayBuffer(vpbe);
			if (NULL == tempDispBuf2)
			{
				SYS_ERROR("Unable to get the Display buffer.\n");
				retCode = DVEVM_ST_FAIL;
			}

			memcpy(tempDispBuf2, tempDispBuf, imgSizeBuf0);
			if (XDM_YUV_420SP == idec1->idec1Status.outputChromaFormat)
				memcpy(tempDispBuf2 + imgSizeBuf0, tempDispBuf + imgSizeBuf0, imgSizeBuf1);

			if (NULL == tempDispBuf2)
			{
				SYS_ERROR("Unable to get the Display buffer.\n");
				retCode = DVEVM_ST_FAIL;
			}

			if (DVEVM_ST_SUCCESS != dvtb_vpbeDisplay(vpbe, tempDispBuf2))
			{
				SYS_ERROR("Unable to Display.\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
				SYS_OUT("Displayed Frame# %d.\n", (nFrames));
		}
	} while (DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_ImgDec1Display(DvevmStThreadInfo *T)
{

	int nBytes = DVEVM_ST_FAIL, bytes2Read = 0, bytesRemaining = 0, nFrames = 0, decDuration = 0;

	unsigned int ipFileLength = 0;

	DvevmStXdmBuffer *inbuf = NULL, *outbuf = NULL, dispBuff;
	DvevmStBool vpbeSetup = DVEVM_ST_FALSE, usecaseFailed = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	/* Quit if source file is not specified */
	if (!T->sourceFp)
	{
		SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit();
	}

	if (!T->targetFp)
		fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_DECODE, "Image", T->useAlgorithm, fileBased);
	dvtb_imgDec1InitPtrs(&T->g.idec1);

	// [Decode][Display] scenario
	do
	{
		if(DVEVM_ST_FAIL == dvtb_getFileSize(T->sourceFp, &ipFileLength))
		{
			SYS_ERROR("Unable to Get File Size \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}
		T->g.idec1.idec1InArgs.numBytes = ipFileLength;

		if (T->useAlgorithm)
		{
			if (DVEVM_ST_FAIL == dvtb_imgDec1HanInit(&T->g.idec1, (char *) T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Image Decoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Image Decoder <%s> initialized\n", T->g.idec1.idec1Name);

			outbuf = &T->g.idec1.outBuf;
			inbuf = &T->g.idec1.inBuf;
		}
		else
		{
			dispBuff.numBufs = 1;
			dispBuff.bufSizes[0] = T->g.vpbe.imageWidth * T->g.vpbe.imageHeight * 2;

			if (DVEVM_ST_FAIL == dvtb_allocCmem(&dispBuff))
			{
				SYS_ERROR("Unable to allocate memory for image display\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			inbuf = outbuf = &dispBuff;
			memcpy(&T->g.idec1.inBuf, &dispBuff, sizeof(T->g.idec1.inBuf));
		}

		bytesRemaining = ipFileLength;
		bytes2Read = inbuf->bufSizes[0];

		do
		{
			if(DVEVM_ST_FAIL == dvtb_fileRead(T->sourceFp, (char *)T->g.idec1.inBuf.bufs[0], bytes2Read, &nBytes))
			{
				SYS_ERROR("Error in file read \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			nFrames++;

			SYS_DEBUG("Read %d bytes\n", nBytes);

			if (0 == nBytes)
			{
				SYS_OUT("End of source file reached. Exiting ...\n");
				break;
			}

			if (T->useAlgorithm)
			{
				T->g.idec1.idec1InArgs.numBytes = nBytes;

				if (DVEVM_ST_FAIL == dvtb_imgDec1DecProcess(&T->g.idec1, &decDuration))
				{
					SYS_ERROR("Image decoder Process fails\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
				SYS_OUT("Decoded Slice#, %d \n", (int) nFrames);

				if (T->g.idec1.idec1Params.forceChromaFormat != T->g.idec1.idec1Status.outputChromaFormat)
				{
					SYS_ERROR("'outputChromaFormat' not set as per 'forceChromaFormat'!\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

#ifdef PERF
				SYS_PERF("Thread, %x, Slice#, %d, Frame Size(bytes), %d, DecTime(us), %d\n", (unsigned int) T, (int) nFrames, (int) T->g.idec1.idec1OutArgs.bytesConsumed, (int) decDuration);
#endif
			}

			if (DVEVM_ST_FALSE == fileBased)
			{
				T->g.vpbe.opMode = DVEVM_ST_MMAP;
				// Update vpbe width and height with decoded image width and height
				T->g.vpbe.imageHeight = T->g.idec1.idec1Status.outputHeight;
				T->g.vpbe.imageWidth = T->g.idec1.idec1Status.imageWidth;

				T->g.vpbe.pixelformat = dvtb_getVidFmt(T->g.idec1.idec1Status.outputChromaFormat);

				if (XDM_YUV_420SP == T->g.idec1.idec1Status.outputChromaFormat)
					T->g.vpbe.imagePitch = T->g.idec1.idec1Status.outputWidth;
				else if (XDM_YUV_422ILE == T->g.idec1.idec1Status.outputChromaFormat)
					T->g.vpbe.imagePitch = T->g.idec1.idec1Status.outputWidth*2;

				if (DVEVM_ST_FAIL == dvtb_vpbeSetup(&T->g.vpbe))
				{
					SYS_ERROR("Unable to setup VPBE device <%s> for display\n", T->g.vpbe.device);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				if (DVEVM_ST_FAIL == dvtb_extendedVpbeSetup(&T->g.vpbe))
				{
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				if (DVEVM_ST_FAIL == dvtb_vpbeDisplayStart(&T->g.vpbe))
				{
					SYS_ERROR("Unable to STREAMON for VPBE device <%s> for display\n", T->g.vpbe.device);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				vpbeSetup = DVEVM_ST_TRUE;
				SYS_DEBUG("VPBE device <%s> initialized for display\n", T->g.vpbe.device);
			}

			if (DVEVM_ST_FAIL == dvtb_imgDec1ProcessOutBuff_dm365(&T->g.idec1, &T->g.vpbe, T->targetFp, nFrames))
			{
				SYS_ERROR("Unable to process output buffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		} while (DVEVM_ST_FALSE);
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_imgDec1ProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

	if (vpbeSetup == DVEVM_ST_TRUE)
	{
		sleep(6);
		dvtb_vpbeClose(&T->g.vpbe);
		SYS_OUT("VPBE Device <%s> closed\n", T->g.vpbe.device);
	}

	if (T->useAlgorithm)
	{
		dvtb_imgDec1HanClose(&T->g.idec1, T->g.eng.name);
	}
	else
		dvtb_freeCmem(&dispBuff);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_DECODE, "Image", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}

