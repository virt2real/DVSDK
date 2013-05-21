/*
 * dvtbJPEGDisplay1.c
 *
 * XDM1.0 JPEG Decode Functionality
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

#include "dvtbJPEGDisplay1.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbV4L2VPBEFeatures.h"
#include "dvtbJPEGDec1.h"
#include "dvtbMemory.h"
#include "dvtbDefs.h"
#include "dvtbUtils.h"

void
dvtb_jpegDec1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
	if ((DVEVM_ST_FALSE == fileBased))//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Total # of slices Decoded and Displayed = %d  \n", nFrames);
		else
			SYS_OUT("Image Displayed \n");
	}
	else//File based
		SYS_OUT("Total # of slices Decoded = %d \n", nFrames);
}

void
dvtb_jpegDec1InitPtrs(DvevmStJpegDec1Info *idec)
{
	int i = 0;

	idec->ceHdl = NULL;
	idec->idec1Hdl = NULL;

	idec->inBuf.numBufs = 0;
	idec->outBuf.numBufs = 0;
	for(i=0; i<MAX_XDM_BUFS; i++)
	{
		idec->inBuf.bufs[i] = NULL;
		idec->outBuf.bufs[i] = NULL;
	}
}

DvevmStRetCode
dvtb_jpegDec1HanInit(DvevmStJpegDec1Info *idec, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		// Initialize Engine
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &idec->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		//Initialize Codec Instance
		if (DVEVM_ST_FAIL == dvtb_jpegDec1Init(idec))
		{
			SYS_ERROR("Unable to initialize Image Decoder <%s>\n", idec->idec1Name);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);// Dummy Loop

	return retCode;
}

void
dvtb_jpegDec1HanClose(DvevmStJpegDec1Info *idec, char *engName)
{
	dvtb_jpegDec1Close(idec);
	SYS_OUT("Jpeg Decoder <%s> closed\n", idec->idec1Name);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&idec->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_jpegDec1DecProcess(DvevmStJpegDec1Info *idec, int *decDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		idec->idec1Cmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_jpegDec1Control(idec))
		{
			SYS_ERROR("Unable to set the XDM_SETPARAMS\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		idec->idec1Cmd = XDM_GETBUFINFO;
		if (DVEVM_ST_FAIL == dvtb_jpegDec1Control(idec))
		{
			SYS_ERROR("Unable to get the actual buffer size using XDM_GETSTATUS.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		//First decode call is made with Parse Header.
		if (DVEVM_ST_FAIL == dvtb_jpegDec1Decode(idec, decDuration))
		{
			SYS_ERROR("Unable to decode. Content <%s> \n", idec->idec1Name);

			idec->idec1Cmd = XDM_GETSTATUS;

			if (DVEVM_ST_FAIL == dvtb_jpegDec1Control(idec))
				SYS_ERROR("Unable to get the status\n");
			else
				SYS_ERROR("Codec Error = %d\n", (int) idec->idec1Status.imgdecStatus.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

		//This GETSTATUS gets the actual buffer
		idec->idec1Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_jpegDec1Control(idec))
		{
			SYS_ERROR("Unable to get the actual buffer size using XDM_GETSTATUS.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

	}while(DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_jpegDec1ProcessOutBuff(DvevmStVpbeInfo *vpbe, FILE *fp, DvevmStXdmBuffer *outbuf, DvevmStBool fileBased, int nFrames)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_TRUE == fileBased)
	{
		for (i = 0; i < outbuf->numBufs; i++)
		{
			if(DVEVM_ST_FAIL ==  dvtb_fileWrite(fp, (char *)outbuf->bufs[i], outbuf->bufSizes[i]))
			{
				SYS_ERROR("Error in writing to file.\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}

		if(DVEVM_ST_SUCCESS == retCode)
			SYS_OUT("Dumped Frame# %d.\n", nFrames);
	}
	else
	{
		if(DVEVM_ST_FAIL ==  dvtb_displayBuffer(vpbe, (char *)outbuf->bufs[0], outbuf->bufSizes[0]))
		{
			SYS_ERROR("Unable to display Frame# %d\n", nFrames);
			retCode = DVEVM_ST_FAIL;
		}
		else
			SYS_OUT("Displayed Frame# %d.\n", nFrames);
	}

	return retCode;
}

void
dvtb_JpegDec1Display(DvevmStThreadInfo *T)
{
	int nBytes = DVEVM_ST_FAIL, bytes2Read =0, bytesRemaining = 0, decDuration = 0, nFrames = 0, i = 0;

	unsigned int ipFileLength = 0;

	DvevmStRetCode status = DVEVM_ST_FAIL;
	DvevmStXdmBuffer *inbuf = NULL, *outbuf = NULL, dispBuff;
	DvevmStXdmBuffer freeIn, freeOut;
	DvevmStBool vpbeSetup = DVEVM_ST_FALSE, usecaseFailed = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

	/* Quit if source file is not specified */
	if (!T->sourceFp)
	{
		SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit( );
	}

	if (!T->targetFp)
			fileBased = DVEVM_ST_FALSE;

	dvtb_startMessage(DVEVM_ST_DECODE, "Jpeg", T->useAlgorithm, fileBased);
	dvtb_jpegDec1InitPtrs(&T->g.jpegdec1);

	// [Decode][Display] scenario
	do
	{
		if(DVEVM_ST_FAIL == dvtb_getFileSize(T->sourceFp, &ipFileLength))
		{
			SYS_ERROR("Unable to Get File Size \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}
		T->g.jpegdec1.idec1InArgs.imgdecInArgs.numBytes = ipFileLength;
		T->g.jpegdec1.idec1DynParams.frame_numbytes = T->g.jpegdec1.idec1InArgs.imgdecInArgs.numBytes;

		if (T->useAlgorithm)
		{
			if(DVEVM_ST_FAIL == dvtb_jpegDec1HanInit(&T->g.jpegdec1, T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize jpeg handle\n");
				usecaseFailed = DVEVM_ST_TRUE;
				memcpy(&freeIn, &T->g.jpegdec1.inBuf, sizeof(freeIn));
				memcpy(&freeOut, &T->g.jpegdec1.outBuf, sizeof(freeOut));
				break;
			}

			SYS_OUT("JPEG Decoder <%s> initialized\n", T->g.jpegdec1.idec1Name);

			outbuf = &T->g.jpegdec1.outBuf;
			inbuf = &T->g.jpegdec1.inBuf;

			// Store In and Out buffer
			memcpy(&freeIn, &T->g.jpegdec1.inBuf, sizeof(freeIn));
			memcpy(&freeOut, &T->g.jpegdec1.outBuf, sizeof(freeOut));
		}
		else
		{
			dispBuff.numBufs = 1;
			dispBuff.bufSizes[0] = T->g.vpbe.imageWidth * T->g.vpbe.imageHeight * 2;

			if (DVEVM_ST_FAIL == dvtb_allocCmem(&dispBuff))
			{
				SYS_OUT("Unable to allocate memory for Jpeg display\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			inbuf = outbuf = &dispBuff;
			memcpy(&T->g.jpegdec1.inBuf, &dispBuff, sizeof(T->g.jpegdec1.inBuf));
			memcpy(&freeOut, outbuf, sizeof(freeOut));
		}

		bytesRemaining = ipFileLength;
		bytes2Read = inbuf->bufSizes[0];
		do
		{
			if(DVEVM_ST_FAIL == dvtb_fileRead(T->sourceFp, (char *)T->g.jpegdec1.inBuf.bufs[0], bytes2Read, &nBytes))
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
				memset(outbuf->bufs[0], 0, outbuf->bufSizes[0]);
				T->g.jpegdec1.idec1InArgs.imgdecInArgs.numBytes = nBytes;
				T->g.jpegdec1.idec1DynParams.frame_numbytes = T->g.jpegdec1.idec1InArgs.imgdecInArgs.numBytes;

				if(DVEVM_ST_FAIL == dvtb_jpegDec1DecProcess(&T->g.jpegdec1, &decDuration))
				{
					SYS_ERROR("Image decoder process fails for slice # %d\n", nFrames);
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				SYS_OUT("Decoded Slice#, %d \n", (int) nFrames);
#ifdef PERF
				SYS_PERF("Thread, %x, Slice#, %d, Frame Size(bytes), %d, DecTime(us), %d\n", (unsigned int) T, (int) nFrames, (int) T->g.jpegdec1.idec1OutArgs.imgdecOutArgs.bytesConsumed, (int) decDuration);
#endif

				T->g.vpbe.imageHeight = T->g.jpegdec1.idec1Status.imgdecStatus.outputHeight;
				T->g.vpbe.imageWidth = T->g.jpegdec1.idec1Status.imgdecStatus.outputWidth;

				if(XDM_PARSE_HEADER == T->g.jpegdec1.idec1DynParams.imgdecDynamicParams.decodeHeader)
					break;

				while (1 != T->g.jpegdec1.idec1Status.end_of_seq)
				{
					nFrames++;
					T->g.jpegdec1.idec1InArgs.imgdecInArgs.numBytes = nBytes;

					if(DVEVM_ST_FAIL == dvtb_jpegDec1DecProcess(&T->g.jpegdec1, &decDuration))
					{
						SYS_ERROR("Image decoder process fails for slice # %d\n", nFrames);
						usecaseFailed = DVEVM_ST_TRUE;
						break;
					}

					SYS_OUT("Decoded Slice#, %d \n", (int) nFrames);
#ifdef PERF
					SYS_PERF("Thread, %x, Slice#, %d, Frame Size(bytes), %d, DecTime(us), %d\n", (unsigned int) T, (int) nFrames, (int) T->g.jpegdec1.idec1OutArgs.imgdecOutArgs.bytesConsumed, (int) decDuration);
#endif
				}
				if(DVEVM_ST_TRUE == usecaseFailed)// Display/Dump decoded image only if use case is successful
					break;
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
				SYS_OUT("VPBE device <%s> initialized for display\n", T->g.vpbe.device);
			}

			if (T->useAlgorithm)
			{
				dispBuff.numBufs = T->g.jpegdec1.idec1Status.imgdecStatus.bufInfo.minNumOutBufs;
				for (i = 0; i < dispBuff.numBufs; i++)
				{
					dispBuff.bufs[i] = outbuf->bufs[i];
					dispBuff.bufSizes[i] = T->g.jpegdec1.idec1Status.imgdecStatus.bufInfo.minOutBufSize[i];
				}
			}

			if(DVEVM_ST_FAIL == dvtb_jpegDec1ProcessOutBuff(&T->g.vpbe, T->targetFp, &dispBuff, fileBased, nFrames))
			{
				SYS_ERROR("Unable to process output buffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		} while (DVEVM_ST_FALSE);
	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_jpegDec1ProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

	if (vpbeSetup == DVEVM_ST_TRUE)
	{
		sleep(2);
		dvtb_vpbeClose(&T->g.vpbe);
		SYS_OUT("VPBE Device <%s> closed\n", T->g.vpbe.device);
	}

	if (T->useAlgorithm)
	{
		// Reset In and Out buffer to original values
		memcpy(&T->g.jpegdec1.inBuf, &freeIn, sizeof(freeIn));
		memcpy(&T->g.jpegdec1.outBuf, &freeOut, sizeof(freeOut));

		dvtb_jpegDec1HanClose(&T->g.jpegdec1, (char *)T->g.eng.name);
	}
	else
		dvtb_freeCmem(&dispBuff);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_DECODE, "Jpeg", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit( );
}

