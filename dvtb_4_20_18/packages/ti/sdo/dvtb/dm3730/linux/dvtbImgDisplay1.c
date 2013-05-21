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
#include "dvtbImgDisplay1Core.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbV4L2VPBEFeatures.h"
#include "dvtbImgDec1.h"
#include "dvtbMemory.h"
#include "dvtbDefs.h"
#include "dvtbUtils.h"

void
dvtb_ImgDec1Display(DvevmStThreadInfo *T)
{
	int nBytes = DVEVM_ST_FAIL, bytes2Read = 0, bytesRemaining = 0,	nFrames = 0,
		decDuration = 0, i = 0;

	unsigned int ipFileLength = 0;

	DvevmStRetCode status = DVEVM_ST_FAIL;
	DvevmStXdmBuffer *inbuf = NULL, *outbuf = NULL, dispBuff;
	DvevmStBool vpbeSetup = DVEVM_ST_FALSE, usecaseFailed = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	if (!T->sourceFp)
	{
		SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit( );
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
			if(DVEVM_ST_FAIL == dvtb_imgDec1HanInit(&T->g.idec1, (char *)T->g.eng.name))
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

				if(DVEVM_ST_FAIL == dvtb_imgDec1DecProcess(&T->g.idec1, &decDuration))
				{
					SYS_ERROR("Image decoder Process fails\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				SYS_OUT("Decoded Slice#, %d \n", (int) nFrames);
#ifdef PERF
				SYS_PERF("Thread, %x, Slice#, %d, Frame Size(bytes), %d, DecTime(us), %d\n", (unsigned int) T, (int) nFrames, (int) T->g.idec1.idec1OutArgs.bytesConsumed, (int) decDuration);
#endif
				SYS_DEBUG("T->g.idec1.idec1DynParams.numAU = %d, T->g.idec1.idec1OutArgs.currentAU = %d, T->g.idec1.idec1Status.totalAU = %d", (int) T->g.idec1.idec1DynParams.numAU, (int) T->g.idec1.idec1OutArgs.currentAU, (int) T->g.idec1.idec1Status.totalAU);

				// Update vpbe width and height with decoded image width and height
				T->g.vpbe.imageHeight = T->g.idec1.idec1Status.outputHeight;
				T->g.vpbe.imageWidth = T->g.idec1.idec1Status.outputWidth;
			}

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


				vpbeSetup = DVEVM_ST_TRUE;
				SYS_DEBUG("VPBE device <%s> initialized for display\n", T->g.vpbe.device);
			}

			if (T->useAlgorithm)
			{
				dispBuff.numBufs = T->g.idec1.idec1Status.bufInfo.minNumOutBufs;
				for (i = 0; i < dispBuff.numBufs; i++)
				{
					dispBuff.bufs[i] = outbuf->bufs[i];
					dispBuff.bufSizes[i] = T->g.idec1.idec1Status.bufInfo.minOutBufSize[i];
				}
			}

			if(DVEVM_ST_FAIL == dvtb_imgDec1ProcessOutBuff(&T->g.vpbe, T->targetFp, &dispBuff, fileBased, nFrames))
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
		sleep(2);
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
	dvtb_threadExit( );
}

