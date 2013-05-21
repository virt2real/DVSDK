/*
 * dvtbImgDisplay.c
 *
 * XDM0.9 Image Decode functionality
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

#include "dvtbImgDisplay.h"
#include "dvtbV4L2VPBE.h"
#include "dvtbImgDec.h"
#include "dvtbUtils.h"
#include "dvtbDefs.h"

void
dvtb_imgDecProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
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
dvtb_imgDecInitPtrs(DvevmStImgDecInfo *idec)
{
	int i = 0;

	idec->ceHdl = NULL;
	idec->idecHdl = NULL;

	idec->inBuf.numBufs = 0;
	idec->outBuf.numBufs = 0;
	for(i=0; i<MAX_XDM_BUFS; i++)
	{
		idec->inBuf.bufs[i] = NULL;
		idec->outBuf.bufs[i] = NULL;
	}
}

DvevmStRetCode
dvtb_imgDecHanInit(DvevmStImgDecInfo *idec, char *engName)
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
		if (DVEVM_ST_FAIL == dvtb_imgDecInit(idec))
		{
			SYS_ERROR("Unable to initialize Image Decoder <%s>\n", idec->idecName);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);// Dummy Loop

	return retCode;
}

void
dvtb_imgDecHanClose(DvevmStImgDecInfo *idec, char *engName)
{
	dvtb_imgDecClose(idec);
	SYS_OUT("Image Decoder <%s> closed\n", idec->idecName);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&idec->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_imgDecDecProcess(DvevmStImgDecInfo *idec, int *decDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_imgDecControl(idec))
		{
			SYS_ERROR("Unable to set the XDM_SETPARAMS\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_imgDecDecode(idec, decDuration))
		{
			SYS_ERROR("Unable to decode. Content <%s> size \n", idec->idecName);

			idec->idecCmd = XDM_GETSTATUS;
			if (DVEVM_ST_FAIL == dvtb_imgDecControl(idec))
				SYS_ERROR("Unable to get the status\n");
			else
				SYS_ERROR("Codec Error = %d\n", (int) idec->idecStatus.extendedError);

			retCode = DVEVM_ST_FAIL;
			break;
		}

	}while(DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_imgDecAllocBuffers(DvevmStImgDecInfo *idec)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if(0 != idec->inBuf.numBufs)
		dvtb_freeCmem(&idec->inBuf);

	if(0 != idec->outBuf.numBufs)
		dvtb_freeCmem(&idec->outBuf);

	do
	{
		//This GETSTATUS gets the actual buffer
		idec->idecCmd  = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_imgDecControl(idec))
		{
			SYS_ERROR("Unable to get the actual buffer size using XDM_GETSTATUS.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_allocCmem(&idec->inBuf))
		{
			SYS_ERROR("Unable to allocate memory for input buffer\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_allocCmem(&idec->outBuf))
		{
			SYS_ERROR("Unable to allocate memory for output buffer\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}
DvevmStRetCode
dvtb_imgDecProcessOutBuff(DvevmStVpbeInfo *vpbe, FILE *fp, DvevmStXdmBuffer *outbuf, DvevmStBool fileBased, int nFrames)
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
dvtb_ImgDecDisplay(DvevmStThreadInfo *T)
{
	int nBytes = DVEVM_ST_FAIL, bytes2Read = 0, bytesRemaining = 0, nFrames = 0, decDuration = 0;
	unsigned int ipFileLength = 0;

	DvevmStXdmBuffer *inbuf = NULL, *outbuf = NULL, dispBuff;
	DvevmStRetCode status = DVEVM_ST_FAIL;
	DvevmStBool vpbeSetup = DVEVM_ST_FALSE, usecaseFailed = DVEVM_ST_FALSE, fileBased = DVEVM_ST_TRUE;

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
	dvtb_imgDecInitPtrs(&T->g.idec);

	// [Decode][Display] scenario
	do
	{
		if(DVEVM_ST_FAIL == dvtb_getFileSize(T->sourceFp, &ipFileLength))
		{
			SYS_ERROR("Unable to Get File Size \n");
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}
		T->g.idec.idecInArgs.numBytes = ipFileLength;

		if (T->useAlgorithm)
		{
			if(DVEVM_ST_FAIL == dvtb_imgDecHanInit(&T->g.idec, (char *)T->g.eng.name))
			{
				SYS_ERROR("Unable to initialize Image Decoder Handle \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			SYS_OUT("Image Decoder <%s> initialized\n", T->g.idec.idecName);

			outbuf = &T->g.idec.outBuf;
			inbuf = &T->g.idec.inBuf;
		}
		else
		{
			dispBuff.numBufs = 1;
			dispBuff.bufSizes[0] = T->g.vpbe.imageWidth * T->g.vpbe.imageHeight * 2;

			if (DVEVM_ST_FAIL == dvtb_allocCmem(&dispBuff))
			{
				SYS_OUT("Unable to allocate memory for image display\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
			inbuf = outbuf = &dispBuff;
			memcpy(&T->g.idec.inBuf, &dispBuff, sizeof(T->g.idec.inBuf));
		}

		bytesRemaining = ipFileLength;
		bytes2Read = inbuf->bufSizes[0];

		do
		{
			if (DVEVM_ST_FAIL == dvtb_fileRead(T->sourceFp, (char *) T->g.idec.inBuf.bufs[0], bytes2Read, &nBytes))
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
				T->g.idec.idecInArgs.size = sizeof(T->g.idec.idecInArgs);
				T->g.idec.idecInArgs.numBytes = nBytes;

				//Call Process twice once with XDM Parse header and second with XDM
				//decode AU
				T->g.idec.idecDynParams.decodeHeader = XDM_PARSE_HEADER;
				T->g.idec.idecCmd = XDM_SETPARAMS;
				nFrames++;
				if(DVEVM_ST_FAIL == dvtb_imgDecDecProcess(&T->g.idec, &decDuration))
				{
					SYS_ERROR("Image decoder Process fails\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
				SYS_OUT("Decoded Slice#, %d \n", (int) nFrames);
#ifdef PERF
				SYS_PERF("Thread, %x, Slice#, %d, DecTime(us), %d\n", (unsigned int) T, (int) nFrames, (int) decDuration);
#endif

				if(DVEVM_ST_FAIL == dvtb_imgDecAllocBuffers(&T->g.idec))
				{
					SYS_ERROR("Unable to allocate buffers \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				fseek(T->sourceFp, 0L, SEEK_SET);
				memset(inbuf->bufs[0], 0, inbuf->bufSizes[0]);
				if (DVEVM_ST_FAIL == dvtb_fileRead(T->sourceFp, (char *)T->g.idec.inBuf.bufs[0], bytes2Read, &nBytes))
				{
					SYS_ERROR("Error in file read \n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				T->g.idec.idecInArgs.numBytes = nBytes;

				T->g.idec.idecDynParams.decodeHeader = XDM_DECODE_AU;
				T->g.idec.idecCmd = XDM_RESET;
				nFrames++;
				if(DVEVM_ST_FAIL == dvtb_imgDecDecProcess(&T->g.idec, &decDuration))
				{
					SYS_ERROR("Image decoder Process fails\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}
				SYS_OUT("Decoded Slice#, %d \n", (int) nFrames);
#ifdef PERF
				SYS_PERF("Thread, %x, Slice#, %d, DecTime(us), %d\n", (unsigned int) T, (int) nFrames, (int) decDuration);
#endif

				T->g.idec.idecCmd = XDM_GETSTATUS;
				if (DVEVM_ST_FAIL == dvtb_imgDecControl(&T->g.idec))
				{
					SYS_ERROR("Unable to get the status.\n");
					usecaseFailed = DVEVM_ST_TRUE;
					break;
				}

				T->g.vpbe.imageWidth = T->g.idec.idecStatus.outputWidth;
				T->g.vpbe.imageHeight = T->g.idec.idecStatus.outputHeight;

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
			}
			if(DVEVM_ST_FAIL == dvtb_imgDecProcessOutBuff(&T->g.vpbe, T->targetFp, outbuf, fileBased, nFrames))
			{
				SYS_ERROR("Unable to process output buffer \n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		} while (DVEVM_ST_FALSE);

	} while (DVEVM_ST_FALSE); // Dummy loop

	dvtb_imgDecProcessEndMessage(T->useAlgorithm, fileBased, nFrames);

	if (vpbeSetup == DVEVM_ST_TRUE)
	{
		sleep(2);
		dvtb_vpbeClose(&T->g.vpbe);
		SYS_OUT("VPBE Device <%s> closed\n", T->g.vpbe.device);
	}

	if (T->useAlgorithm)
	{
		dvtb_imgDecHanClose(&T->g.idec, T->g.eng.name);
	}
	else
		dvtb_freeCmem(&dispBuff);

	dvtb_fileClose(&T->sourceFp, &T->targetFp);

	dvtb_exitMessage(DVEVM_ST_DECODE, "Image", T->useAlgorithm, fileBased, usecaseFailed);

	dvtb_freeThr(T);
	dvtb_threadExit();
}

