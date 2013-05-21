/*
 * dvtbDM365Utils.c
 *
 * DM365 Specific utility functions
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

#include "dvtbUtils.h"
#include "dvtbDM365Utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_SWITCH_LENGTH       4
#define MAX_SWITCHES            2
#define MAX_IO_TOKENS           (MAX_SWITCHES*2)

/*
 * Utility function to queue in the buffer and update the index accordingly. The Initialization of the index 'freeBuffIndex' is responsibility of the calling module.
 */
DvevmStRetCode
dvtb_userBuffPtr_queueBuffer(DvevmStVpbeInfo *vpbe, int outputChromaFormat, IVIDEO1_BufDesc *vdo, int numBufs)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (XDM_YUV_420SP == outputChromaFormat)
		vpbe->y_uv_buffOffset = vdo->bufDesc[1].buf - vdo->bufDesc[0].buf;
	else
		vpbe->y_uv_buffOffset = 0;

	do
	{
		if(vpbe->y_uv_buffOffset)
		{
			if (DVEVM_ST_FAIL == dvtb_displaySetOffSet(vpbe))
			{
				SYS_ERROR("Unable to set Y-UV buffer Offset for VPBE device <%s>\n", vpbe->device);
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}

		vpbe->buf.index = vpbe->freeBuffIndex;

		if (DVEVM_ST_SUCCESS != dvtb_vpbeDisplay(vpbe, vdo->bufDesc[0].buf))
		{
			SYS_ERROR("Unable to Display.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		vpbe->freeBuffIndex++;

		if(MIN_DISPLAY_BUFFERS <= vpbe->freeBuffIndex)
			vpbe->freeBuffIndex = 0;
	}
	while(DVEVM_ST_FALSE);

	return retCode;
}

/*
 * Utility function to queue in the latest buffer, update the index accordingly, set the Y-UV buffer-offset and deQueue the oldest buffer.
 */
DvevmStRetCode
dvtb_userBuffPtr_displayBuffer(DvevmStVpbeInfo *vpbe, int outputChromaFormat, IVIDEO1_BufDesc *vdo, int numBufs)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (XDM_YUV_420SP == outputChromaFormat)
		vpbe->y_uv_buffOffset = vdo->bufDesc[1].buf - vdo->bufDesc[0].buf;
	else
		vpbe->y_uv_buffOffset = 0;

	do
	{
		vpbe->buf.index = vpbe->freeBuffIndex;

                if (DVEVM_ST_SUCCESS != dvtb_vpbeDisplay(vpbe, vdo->bufDesc[0].buf))
                {
                        SYS_ERROR("Unable to Display.\n");
                        retCode = DVEVM_ST_FAIL;
                        break;
                }

		if (NULL==(vpbe->userbufferptr[0] = (char *)dvtb_vpbeGetDisplayBuffer(vpbe)))
		{
			SYS_ERROR("Unable to get display buffer.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if(vpbe->y_uv_buffOffset)
		{
			if (DVEVM_ST_FAIL == dvtb_displaySetOffSet(vpbe))
			{
				SYS_ERROR("Unable to set Y-UV buffer Offset for VPBE device <%s>\n", vpbe->device);
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}

		vpbe->freeBuffIndex++;

		if(MIN_DISPLAY_BUFFERS <= vpbe->freeBuffIndex)
			vpbe->freeBuffIndex = 0;
	}
	while(DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_mMap_displayBuffer(DvevmStVpbeInfo *vpbe, int outputChromaFormat, IVIDEO1_BufDesc *vdo, int numBufs)
{
	int i = 0;
	void *tempDispBuf = NULL;
	void *tempPtr = NULL;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	tempDispBuf = dvtb_vpbeGetDisplayBuffer(vpbe);
	if (NULL == tempDispBuf)
	{
		SYS_ERROR("Unable to get the Display buffer.\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		tempPtr = tempDispBuf;

		for (i = 0; i < numBufs; i++)
		{
			memcpy(tempPtr, vdo->bufDesc[i].buf, vdo->bufDesc[i].bufSize);

			if (XDM_YUV_420SP == outputChromaFormat)
				tempPtr+=vdo->framePitch*vdo->frameHeight;
		}

		if (DVEVM_ST_SUCCESS != dvtb_vpbeDisplay(vpbe, tempDispBuf))
		{
			SYS_ERROR("Unable to Display.\n");
			retCode = DVEVM_ST_FAIL;
		}
	}

	return retCode;
}

int
dvtb_getXdmFmt(DvevmStVidFmt fmt)
{
	int v4l2Fmt = XDM_YUV_420SP;

	switch (fmt)
	{
		case VID_FMT_UYVY:
			v4l2Fmt = XDM_YUV_422ILE;
			break;
		case VID_FMT_YUV420SP:
			v4l2Fmt = XDM_YUV_420SP;
			break;
		default:
			v4l2Fmt = DVEVM_ST_FAIL;
	}

	return v4l2Fmt;
}

int
dvtb_getVidFmt(int fmt)
{
	int v4l2Fmt = VID_FMT_YUV420SP;

	switch (fmt)
	{
		case XDM_YUV_422ILE:
			v4l2Fmt = VID_FMT_UYVY;
			break;
		case XDM_YUV_420SP:
			v4l2Fmt = VID_FMT_YUV420SP;
			break;
		default:
			v4l2Fmt = DVEVM_ST_FAIL;
	}

	return v4l2Fmt;
}

DvevmStRetCode
dvtb_extendedVpbeSetup(DvevmStVpbeInfo *vpbe)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (vpbe->cropEnable)
		{
			if (DVEVM_ST_FAIL == dvtb_displayCropSetup(vpbe))
			{
				SYS_ERROR("Unable to configure VPBE extended settings for 'Crop' functionality\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}
	} while (DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_extendedVpfeSetup(DvevmStVpfeInfo *vpfe)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (vpfe->cropEnable)
		{
			if (DVEVM_ST_FAIL == dvtb_captureCropSetup(vpfe))
			{
				SYS_ERROR("Unable to configure VPFE extended settings for 'Crop' functionality\n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}

		if (DVEVM_ST_FAIL == dvtb_configHdCaptureFps(vpfe))
		{
			SYS_ERROR("Unable to configure VPFE extended settings for 'stream configuration'\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	} while (DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_captureClose(DvevmStVpfeInfo *vpfe, DvtbPreviewerInfo *vpPrvw, DvtbResizerInfo *vpRsz)
{
	dvtb_vpfeClose(vpfe);
	SYS_OUT("VPFE Device <%s> closed\n", vpfe->device);

	dvtb_previewerClose(vpPrvw);
	SYS_OUT("Preview Device <%s> closed\n", vpPrvw->previewDevice);

	dvtb_resizerClose(vpRsz);
	SYS_OUT("Resize Device <%s> closed\n", vpRsz->resizeDevice);

	return;
}

DvevmStRetCode
dvtb_captureSetup(DvevmStVpfeInfo *vpfe, DvtbPreviewerInfo *vpPrvw, DvtbResizerInfo *vpRsz)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	vpPrvw->preview_fd = -1;
	vpRsz->rsz_fd = -1;
	vpfe->capFd = -1;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_resizerSetup(vpRsz))
		{
			SYS_ERROR("Unable to initialize Resizer device <%s>\n", vpRsz->resizeDevice);
			dvtb_resizerClose(vpRsz);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_previewerSetup(vpPrvw))
		{
			SYS_ERROR("Unable to initialize Previewer device <%s>\n", vpPrvw->previewDevice);
			dvtb_previewerClose(vpPrvw);
			dvtb_resizerClose(vpRsz);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_vpfeSetup(vpfe))
		{
			SYS_ERROR("Unable to initialize VPFE device <%s>\n", vpfe->device);
			dvtb_vpfeClose(vpfe);
			dvtb_previewerClose(vpPrvw);
			dvtb_resizerClose(vpRsz);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_extendedVpfeSetup(vpfe))
		{
			SYS_ERROR("Unable to setup VPFE\n");
			dvtb_vpfeClose(vpfe);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_vpfeCaptureStart(vpfe))
		{
			SYS_ERROR("Unable to start VPFE capture\n");
			dvtb_vpfeClose(vpfe);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	} while (DVEVM_ST_FALSE);

	return retCode;
}

/*
 * Lock the buffers being queued into teh driver.
 */
void
dvtb_setOutBuffInUse(DvevmStOutBuffsInUse (*dispBufArray)[], int outputID, void * buf)
{
	int id = outputID;

	if(DVEVM_ST_TRUE==(*dispBufArray)[id-1].outBufInUseFlag)
	{
		SYS_OUT("WARNING: DVEVM_ST_TRUE==vdec2->dispBufArray[id-1].outBufInUseFlag\n");
		return;
	}

	(*dispBufArray)[id-1].bufID = id;
	(*dispBufArray)[id-1].displayBufs = (unsigned char *)buf;
	(*dispBufArray)[id-1].outBufInUseFlag = DVEVM_ST_TRUE;

	return;
}

/*
 * Keep track of the buffers that are released by codec. They shall be released when they are not in use by driver.
 */
void
dvtb_registerOutBuffToFree(DvevmStOutBuffsInUse (*dispBufArray)[], XDAS_Int32 (*freeBufID)[])
{
	int i=0;

	for (i=0;(0!=(*freeBufID)[i])&&i<VIDDEC2_PLAY_MAX_BUFFERS;i++)
	{
		(*dispBufArray)[(*freeBufID)[i]-1].freeIt = DVEVM_ST_TRUE;
	}

	return;
}

void
dvtb_freeOutBuffInUse(DvevmStOutBuffsInUse (*dispBufArray)[], DvevmStBufElement (*outBufArray)[])
{
	int i=0;

	for (i=0;i<VIDDEC2_PLAY_MAX_BUFFERS;i++)
	{
		if((DVEVM_ST_TRUE==(*dispBufArray)[i].freeIt)&&
		   (DVEVM_ST_FALSE==(*dispBufArray)[i].outBufInUseFlag))
		{
			(*outBufArray)[i].isFree  = DVEVM_ST_TRUE;
			(*dispBufArray)[i].freeIt = DVEVM_ST_FALSE;
			(*dispBufArray)[i].displayBufs = NULL;
			(*dispBufArray)[i].bufID = 0;
		}
	}

	return;
}

/*
 * Unlock the buffer release by driver 'Q' and free the applicable buffers.
 */
void
dvtb_clearOutBuffInUse(DvevmStOutBuffsInUse (*dispBufArray)[], DvevmStBufElement (*outBufArray)[], void * address)
{
	int i=0;

	for (i=0;i<VIDDEC2_PLAY_MAX_BUFFERS;i++)
	{
		if(address==(*dispBufArray)[i].displayBufs)
		{
			(*dispBufArray)[i].outBufInUseFlag = DVEVM_ST_FALSE;

			break;
		}
	}

	dvtb_freeOutBuffInUse(dispBufArray, outBufArray);

	return;
}


DvevmStRetCode
dvtb_vidDec2DeInitOutBuffers_dm365(DvevmStBufElement (*outBufArray)[], int totBuf)
{
	int i = 0;

	for (i = 0; i < totBuf; i++)
	{
		dvtb_freeCmemSingleChunk(&((*outBufArray)[i].buffer));
	}
	return DVEVM_ST_SUCCESS;
}

DvevmStBufElement*
dvtb_vidDec2AllocOutBuffer_dm365(DvevmStBufElement (*outBufArray)[], int totBuf, int *buffIdSearchStart)
{
	unsigned int i = (*buffIdSearchStart);
	unsigned int freeIdFound=0;

	do
	{
		if ((*outBufArray)[i].isFree == DVEVM_ST_TRUE)
		{
			(*outBufArray)[i].isFree = DVEVM_ST_FALSE;
			freeIdFound =1;
			break;
		}

		i++;

		if(i>=totBuf)
			i=0;

	}while((*buffIdSearchStart)!=i);

	if (freeIdFound)
	{
		(*buffIdSearchStart)=i+1;
		if((*buffIdSearchStart)>=totBuf)
			(*buffIdSearchStart)=0;

		return &((*outBufArray)[i]);
	}

	return NULL;
}

DvevmStRetCode
dvtb_vidDec2ReleaseOutBuffers(DvevmStBufElement (*outBufArray)[], XDAS_Int32 (*freeBufID)[])
{
	unsigned int i = 0, id = 0;

	for (i = 0; i < VIDDEC2_PLAY_MAX_BUFFERS; i++)
	{
		id = (*freeBufID)[i];

		/*
		 * Check if the buffer Id = 0 condition has reached. zero is not a
		 * valid buffer Id hence that value is used to identify the end of
		 * buffer array
		 */
		if (id == 0)
			break;

		/*
		 * convert the buffer-Id to its corresponding index in the global
		 * array
		 */
		id--;
		// Set the status of the buffer to FREE
		(*outBufArray)[id].isFree = DVEVM_ST_TRUE;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_vidDec2AllocInBuff(DvevmStXdmBuffer *inBuf, XDM1_BufDesc *inBufDesc, int minNumInBufs)
{
	int i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		//Allocate the contig memory for inBuf
		if (DVEVM_ST_FAIL == dvtb_allocCmemSingleChunk(inBuf))
		{
			SYS_ERROR("Unable to allocate memory for input buffer \n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		//Assign the buffer pointers accordingly.
		inBufDesc->numBufs = inBuf->numBufs;

		for (i = 0; i < minNumInBufs; i++)
		{
			inBufDesc->descs[i].buf = (XDAS_Int8 *) inBuf->bufs[i];
			inBufDesc->descs[i].bufSize = inBuf->bufSizes[i];
		}
	} while (DVEVM_ST_FALSE); // Dummy Loop

	return retCode;
}

DvevmStRetCode
dvtb_vidDec2InitFirstOutBuffer_dm365(DvevmStBufElement (*outBufArray)[], VIDDEC2_Status *viddecStatus, int *totBuf)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	int i = 0;

	(*outBufArray)[0].id = 1;
	(*outBufArray)[0].isFree = DVEVM_ST_TRUE;

	(*outBufArray)[0].buffer.numBufs = viddecStatus->bufInfo.minNumOutBufs;

	ASSERT((*outBufArray)[0].buffer.numBufs > 0);

	for (i = 0; i < viddecStatus->bufInfo.minNumOutBufs; i++)
	{
		(*outBufArray)[0].buffer.bufs[i] = NULL;
		(*outBufArray)[0].buffer.bufSizes[i] = viddecStatus->bufInfo.minOutBufSize[i];
	}

	if (DVEVM_ST_FAIL == dvtb_allocCmemSingleChunk(&(*outBufArray)[0].buffer))
	{
		retCode = DVEVM_ST_FAIL;
		SYS_ERROR("Unable to allocate memory for 1st outBuf in the outBuf pool\n");
	}

	if (retCode == DVEVM_ST_SUCCESS)
		(*totBuf) = 1;

	return retCode;
}

DvevmStRetCode
dvtb_vidDec2InitAllOutBuffers_dm365(DvevmStBufElement (*outBufArray)[], VIDDEC2_Status *viddecStatus, int *totBuf, int maxBufs)
{
	int i = 0, j = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	SYS_DEBUG("maxNumDisplayBufs=%d,\n minNumPlaneBufs=%d\n", (int) maxBufs, (int) viddecStatus->bufInfo.minNumOutBufs);

	do
	{
		// Initialize rest of the out-buffers
		for (j = 1; j < maxBufs; j++)
		{
			(*outBufArray)[j].buffer.numBufs = viddecStatus->bufInfo.minNumOutBufs;

			for (i = 0; i < viddecStatus->bufInfo.minNumOutBufs; i++)
			{
				(*outBufArray)[j].buffer.bufs[i] = NULL;
				(*outBufArray)[j].buffer.bufSizes[i] = viddecStatus->bufInfo.minOutBufSize[i];
			}

			(*outBufArray)[j].isFree = DVEVM_ST_TRUE;
			(*outBufArray)[j].id = j + 1;
		}

		for (i = 1; i < maxBufs; i++)
		{
			if (DVEVM_ST_FAIL == dvtb_allocCmemSingleChunk(&(*outBufArray)[i].buffer))
			{
				(*totBuf) = i;
				dvtb_vidDec2DeInitOutBuffers_dm365(&(*outBufArray), (*totBuf));
				retCode = DVEVM_ST_FAIL;
				SYS_ERROR("Unable to allocate memory for <%d> outBuf in the outBuf pool\n", i);

				break;
			}
		}

		if (retCode == DVEVM_ST_SUCCESS)
			(*totBuf) = maxBufs;
	} while (DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_vidDec2SetUpVPBE(DvevmStVpbeInfo *vpbe, VIDDEC2_Status *viddecStatus, VIDDEC2_OutArgs *viddecOutArgs, VIDDEC2_InArgs *viddecInArgs, VIDDEC2_Params* viddecParams, VIDDEC2_DynamicParams *viddecDynParams, DvevmStOutBuffsInUse (*dispBufArray)[])
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	int i=0;

	do
	{
		/* Configure VPBE */
		if(viddecDynParams->frameOrder)
		{
			vpbe->imagePitch = viddecOutArgs->decodedBufs.framePitch;
			vpbe->imageWidth = viddecOutArgs->decodedBufs.frameWidth;
			vpbe->imageHeight = viddecOutArgs->decodedBufs.frameHeight;
		}
		else
		{
			vpbe->imagePitch = viddecOutArgs->displayBufs[0].framePitch;
			vpbe->imageWidth = viddecOutArgs->displayBufs[0].frameWidth;
			vpbe->imageHeight = viddecOutArgs->displayBufs[0].frameHeight;
		}

		if (DVEVM_ST_USERBUFFER==vpbe->opMode)
		{
			vpbe->freeBuffIndex=0;
			
			if(viddecDynParams->frameOrder)
			{
				if (XDM_YUV_420SP == viddecStatus->outputChromaFormat)
					vpbe->y_uv_buffOffset = viddecOutArgs->decodedBufs.bufDesc[1].buf - viddecOutArgs->decodedBufs.bufDesc[0].buf;
				else
					vpbe->y_uv_buffOffset = 0;
			}
			else
			{
				if (XDM_YUV_420SP == viddecStatus->outputChromaFormat)
					vpbe->y_uv_buffOffset = viddecOutArgs->displayBufs[0].bufDesc[1].buf - viddecOutArgs->displayBufs[0].bufDesc[0].buf;
				else
					vpbe->y_uv_buffOffset = 0;
			}
		}

		if (viddecStatus->outputChromaFormat != viddecParams->forceChromaFormat)
		{
			SYS_ERROR("'outputChromaFormat' not set as per 'forceChromaFormat'!\n");
			SYS_ERROR("\nActual chroma format=%d \nExpected chroma format=%d\n", (int) viddecStatus->outputChromaFormat, (int) viddecParams->forceChromaFormat);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		vpbe->pixelformat = dvtb_getVidFmt(viddecStatus->outputChromaFormat);

		/* Set-up VPBE */
		if (DVEVM_ST_FAIL == dvtb_vpbeSetup(vpbe))
		{
			SYS_ERROR("Unable to setup VPBE device <%s> for display\n", vpbe->device);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		/* Complete platform specific configurations if any */
		if (DVEVM_ST_FAIL == dvtb_extendedVpbeSetup(vpbe))
		{
			retCode = DVEVM_ST_FAIL;
			break;
		}

		/*
		 * Queue the first buffer twice and lock the buffer.
		 */
		if (DVEVM_ST_USERBUFFER==vpbe->opMode)
		{
			if(viddecDynParams->frameOrder)
			{
				dvtb_setOutBuffInUse(dispBufArray, viddecInArgs->inputID, viddecOutArgs->decodedBufs.bufDesc[0].buf);
				for(i=0; i<(MIN_DISPLAY_BUFFERS-1);i++)
				{
					if (DVEVM_ST_FAIL == dvtb_userBuffPtr_queueBuffer(vpbe, viddecStatus->outputChromaFormat, &viddecOutArgs->decodedBufs, viddecOutArgs->decodedBufs.numBufs))
					{
						SYS_ERROR("Unable to display Frame# %d\n", i);
						retCode = DVEVM_ST_FAIL;
						break;
					}
				}
			}
			else
			{
				dvtb_setOutBuffInUse(dispBufArray, viddecOutArgs->outputID[0], viddecOutArgs->displayBufs[0].bufDesc[0].buf);

				for(i=0; i<(MIN_DISPLAY_BUFFERS-1);i++)
				{
					if (DVEVM_ST_FAIL == dvtb_userBuffPtr_queueBuffer(vpbe, viddecStatus->outputChromaFormat, &viddecOutArgs->displayBufs[0], viddecOutArgs->displayBufs[0].numBufs))
					{
						SYS_ERROR("Unable to display Frame# %d\n", i);
						retCode = DVEVM_ST_FAIL;
						break;
					}
				}
			}
		}

		if (DVEVM_ST_FAIL == dvtb_vpbeDisplayStart(vpbe))
		{
			SYS_ERROR("Unable to STREAMON for VPBE device <%s> for display\n", vpbe->device);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	} while(DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_vidDec2ProcessOutBuff_dm365(DvevmStVpbeInfo *vpbe, VIDDEC2_Status *viddecStatus, VIDDEC2_OutArgs *viddecOutArgs, VIDDEC2_InArgs *viddecInArgs, VIDDEC2_Params* viddecParams, VIDDEC2_DynamicParams *viddecDynParams, DvevmStOutBuffsInUse (*dispBufArray)[], DvevmStBufElement (*outBufArray)[], FILE * targetFp, int *nFrames, int rotated)
{
	int validOutIds = 0, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	/*
	 * Track the buffers to be freed. Used in User-buffer mode.
	 * Conditional statement is deliberately removed (no effect in file/MMap mode).
	 */
	dvtb_registerOutBuffToFree(dispBufArray, &viddecOutArgs->freeBufID);

	if(viddecDynParams->frameOrder)
	{
		if (viddecStatus->outputChromaFormat != viddecParams->forceChromaFormat)
		{
			SYS_ERROR("'outputChromaFormat' not set as per 'forceChromaFormat'!\n");
			SYS_ERROR("\nActual chroma format=%d \nExpected chroma format=%d\n", (int) viddecStatus->outputChromaFormat, (int) viddecParams->forceChromaFormat);
			retCode = DVEVM_ST_FAIL;
		}
		else if (NULL != targetFp)
		{
			if (XDM_YUV_422ILE == viddecStatus->outputChromaFormat)
			{
				if ((1 != viddecOutArgs->decodedBufs.numBufs))
				{
					SYS_ERROR("Invalid number of decoded numBufs for 422ILE format\n");
					retCode = DVEVM_ST_FAIL;
				}
				else if (DVEVM_ST_FAIL == dvtb_fileWrite(targetFp, (char *) viddecOutArgs->decodedBufs.bufDesc[0].buf, viddecOutArgs->decodedBufs.bufDesc[0].bufSize))
				{
					SYS_ERROR("Error in writing to file.\n");
					retCode = DVEVM_ST_FAIL;
				}
			}
			else if (XDM_YUV_420SP == viddecStatus->outputChromaFormat)
			{
				//If o/p not rotated, convert from 420SP to 420P format and file dump.
				if(!rotated)
				{
					if (DVEVM_ST_FAIL == dvtb_writeOutputData(&viddecOutArgs->decodedBufs, viddecStatus->outputWidth, viddecStatus->outputHeight, targetFp))
					{
						SYS_ERROR("Error in writing to file.\n");
						retCode = DVEVM_ST_FAIL;
					}
				}
				else
				{
					for (i = 0; i < viddecOutArgs->decodedBufs.numBufs; i++)
					{
						if (DVEVM_ST_FAIL == dvtb_fileWrite(targetFp, (char *) viddecOutArgs->decodedBufs.bufDesc[i].buf, viddecOutArgs->decodedBufs.bufDesc[i].bufSize))
						{
							SYS_ERROR("Error in writing to file.\n");
							retCode = DVEVM_ST_FAIL;
							break;
						}
					}
				}				
			}
			else
			{
				SYS_ERROR(" Un-supported 'outputChromaFormat'\n");
				retCode = DVEVM_ST_FAIL;
			}

			if (DVEVM_ST_SUCCESS == retCode)
				SYS_OUT("Dumped Frame# %d.\n", (*nFrames));
		}	
		else
		{
			if( DVEVM_ST_USERBUFFER==vpbe->opMode )
			{
				if (DVEVM_ST_FAIL == dvtb_userBuffPtr_displayBuffer(vpbe, viddecStatus->outputChromaFormat, &viddecOutArgs->decodedBufs, viddecOutArgs->decodedBufs.numBufs))
				{
					SYS_ERROR("Unable to display Frame# %d\n", (*nFrames));
					retCode = DVEVM_ST_FAIL;
				}
				else
				{
					dvtb_setOutBuffInUse(dispBufArray, viddecInArgs->inputID, viddecOutArgs->decodedBufs.bufDesc[0].buf);

					// First buffer is inserted twice. Wait till the first frame is displayed twice.
					if(1!=*nFrames)
						dvtb_clearOutBuffInUse(dispBufArray, outBufArray, vpbe->userbufferptr[0]);
				}
			}
			else
			{
				if (DVEVM_ST_FAIL == dvtb_mMap_displayBuffer(vpbe, viddecStatus->outputChromaFormat, &viddecOutArgs->decodedBufs, viddecOutArgs->decodedBufs.numBufs))
				{
					SYS_ERROR("Unable to display Frame# %d\n", (*nFrames));
					retCode = DVEVM_ST_FAIL;
				}
			}
			if(DVEVM_ST_FAIL != retCode)
				SYS_OUT("Displayed Frame# %d.\n", (*nFrames));
		}
		(*nFrames)++;
	}
	else
	{
		//Check for Frame ready via display buffer pointers
		while (viddecOutArgs->outputID[validOutIds] > 0)
		{
			if (viddecStatus->outputChromaFormat != viddecParams->forceChromaFormat)
			{
				SYS_ERROR("'outputChromaFormat' not set as per 'forceChromaFormat'!\n");
				SYS_ERROR("\nActual chroma format=%d \nExpected chroma format=%d\n", (int) viddecStatus->outputChromaFormat, (int) viddecParams->forceChromaFormat);
				retCode = DVEVM_ST_FAIL;
				break;
			}
			else if (NULL != targetFp)
			{
				if (XDM_YUV_422ILE == viddecStatus->outputChromaFormat)
				{
					if ((1 != viddecOutArgs->displayBufs[validOutIds].numBufs))
					{
						SYS_ERROR("Invalid number of display numBufs for 422ILE format\n");
						retCode = DVEVM_ST_FAIL;
						break;
					}
	
					if (DVEVM_ST_FAIL == dvtb_fileWrite(targetFp, (char *) viddecOutArgs->displayBufs[validOutIds].bufDesc[0].buf, viddecOutArgs->displayBufs[validOutIds].bufDesc[0].bufSize))
					{
						SYS_ERROR("Error in writing to file.\n");
						retCode = DVEVM_ST_FAIL;
						break;
					}					
				}
				else if (XDM_YUV_420SP == viddecStatus->outputChromaFormat)
				{
					/*
					 * If o/p not rotated, convert from 420SP to 420P format and file dump.
					 */
					if(!rotated)
					{
						if (DVEVM_ST_FAIL == dvtb_writeOutputData(&viddecOutArgs->displayBufs[validOutIds], viddecStatus->outputWidth, viddecStatus->outputHeight, targetFp))
						{
							SYS_ERROR("Error in writing to file.\n");
							retCode = DVEVM_ST_FAIL;
							break;
						}
					}
					else
					{
						for (i = 0; i < viddecOutArgs->displayBufs[validOutIds].numBufs; i++)
						{
							if (DVEVM_ST_FAIL == dvtb_fileWrite(targetFp, (char *) viddecOutArgs->displayBufs[validOutIds].bufDesc[i].buf, viddecOutArgs->displayBufs[validOutIds].bufDesc[i].bufSize))
							{
								SYS_ERROR("Error in writing to file.\n");
								retCode = DVEVM_ST_FAIL;
								break;
							}
						}
					}
				}
				else
				{
					SYS_ERROR(" Un-supported 'outputChromaFormat'\n");
					retCode = DVEVM_ST_FAIL;
					break;
				}

				if (DVEVM_ST_SUCCESS == retCode)
					SYS_OUT("Dumped Frame# %d.\n", (*nFrames));
			}
			else
			{
				if( DVEVM_ST_USERBUFFER==vpbe->opMode )
				{
					if (DVEVM_ST_FAIL == dvtb_userBuffPtr_displayBuffer(vpbe, viddecStatus->outputChromaFormat, &viddecOutArgs->displayBufs[validOutIds], viddecOutArgs->displayBufs[validOutIds].numBufs))
					{
						SYS_ERROR("Unable to display Frame# %d\n", (*nFrames));
						retCode = DVEVM_ST_FAIL;
						break;
					}
					dvtb_setOutBuffInUse(dispBufArray, viddecOutArgs->outputID[validOutIds], viddecOutArgs->displayBufs[validOutIds].bufDesc[0].buf);

					/*
					 * First buffer is inserted twice. Wait till the first frame is displayed twice.
					 */
					if(1!=*nFrames)
						dvtb_clearOutBuffInUse(dispBufArray, outBufArray, vpbe->userbufferptr[0]);

				}
				else
				{
					if (DVEVM_ST_FAIL == dvtb_mMap_displayBuffer(vpbe, viddecStatus->outputChromaFormat, &viddecOutArgs->displayBufs[validOutIds], viddecOutArgs->displayBufs[validOutIds].numBufs))
					{
						SYS_ERROR("Unable to display Frame# %d\n", (*nFrames));
						retCode = DVEVM_ST_FAIL;
						break;
					}
				}

				SYS_OUT("Displayed Frame# %d.\n", (*nFrames));
			}

			validOutIds++;

			(*nFrames)++;
		}
	}

	return retCode;
}

void
dvtb_vidDec2StartMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, char *str)
{
	if (DVEVM_ST_FALSE == fileBased)
	{
		if (useAlgorithm)
			SYS_OUT("%s [Decode]+[Display] usecase started\n", str);
		else
			SYS_OUT("Video [Display] usecase started\n");
	}
	else
		SYS_OUT("%s [Decode]+[Dump] usecase started\n", str);
}

void
dvtb_vidDec2ProcessEndMessage_dm365(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames, char *str)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Total # of %s frames Decoded & Displayed = %d.\n", str, nFrames - 1);
		else
			SYS_OUT("Total # of frames Displayed = %d. \n", nFrames - 1);
	}
	else
		//File based
		SYS_OUT("Total # of %s frames Decoded & Dumped = %d. \n", str, nFrames - 1);
}

void
dvtb_vidDec2ExitMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, DvevmStBool usecaseFailed, char *str)
{
	if (DVEVM_ST_TRUE == fileBased)//File based
	{
		if (DVEVM_ST_FALSE == usecaseFailed)
			SYS_OUT("%s [Decode]+[Dump] usecase completed successfully.\n", str);
		else
			SYS_OUT("Video [Decode]+[Dump] usecase completed with errors.\n");
	}
	else
	{
		if (useAlgorithm)
		{
			if (DVEVM_ST_FALSE == usecaseFailed)
				SYS_OUT("%s [Decode]+[Display] usecase completed successfully.\n", str);
			else
				SYS_OUT("Video [Decode]+[Display] usecase completed with errors.\n");
		}
		else
		{
			if (DVEVM_ST_FALSE == usecaseFailed)
				SYS_OUT("%s [Display] usecase completed successfully.\n", str);
			else
				SYS_OUT("%s [Display] usecase completed with errors.\n", str);
		}
	}
}

DvevmStRetCode
dvtb_vidEnc1ReadInput_dm365(DvevmStVpfeInfo *vpfe, FILE *fp, IVIDEO1_BufDescIn *inBufDesc, int fileBased)
{
	int i = 0, bytesRead = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_FALSE == fileBased)
	{
		// Get YUV from driver
		if (dvtb_vpfeGetNextBuffer(vpfe) < 0)
		{
			SYS_ERROR("Error while reading Video input\n");
			retCode = DVEVM_ST_FAIL;
		}
		else if (VID_FMT_YUV420SP == vpfe->capFmt)
		{
			/*
			 * UV buffers are disposed after the Y buffer at 1 Frame size byte count.
			 */
			inBufDesc->bufDesc[0].buf = (XDAS_Int8 *) vpfe->buffers[vpfe->buf.index].start;
			inBufDesc->bufDesc[1].buf = inBufDesc->bufDesc[0].buf + (vpfe->capWidth * vpfe->capHeight);
		}
		else if (VID_FMT_UYVY == vpfe->capFmt)
		{
			inBufDesc->bufDesc[0].buf = (XDAS_Int8 *) vpfe->buffers[vpfe->buf.index].start;
		}
		else if (VID_FMT_YUV420 == vpfe->capFmt)
		{
			inBufDesc->bufDesc[0].buf = (XDAS_Int8 *) vpfe->buffers[vpfe->buf.index].start;
			inBufDesc->bufDesc[1].buf = inBufDesc->bufDesc[0].buf + (vpfe->capWidth * vpfe->capHeight);
			inBufDesc->bufDesc[2].buf = inBufDesc->bufDesc[1].buf + ((vpfe->capWidth * vpfe->capHeight) / 2);
		}
		else
		{
			SYS_ERROR("Un-supported capture format selected!\n");
			retCode = DVEVM_ST_FAIL;
		}
	}
	else
	{
		for (i = 0; i < inBufDesc->numBufs; i++)
		{
			if(DVEVM_ST_FAIL == dvtb_fileRead(fp, (char *)inBufDesc->bufDesc[i].buf, inBufDesc->bufDesc[i].bufSize, &bytesRead))
			{
				SYS_ERROR("Error in file read \n");
				retCode = DVEVM_ST_FAIL;
				break;
			}


			if (0 == bytesRead)
			{
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}
	}
	return retCode;
}

/*
 * Function to extract active-video, covert data format from 420SP to 420P format and write to file.
 */
DvevmStRetCode
dvtb_writeOutputData(IVIDEO1_BufDesc *displayBuf, int width, int height, FILE * fOutFile)
{
	XDAS_Int32 pic_size;
	XDAS_Int8 *CbCr_seperate[2];
	XDAS_Int8 *Luma_data;
	XDAS_Int8 *CbCr_data;
	XDAS_Int8 Chroma_separate[HD1080_YRES * HD1080_XRES];

	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	pic_size = width * height;
	/*----------------------------------------------------------------*/
	/* Init input subPic_buf with  outArgs                            */
	/*----------------------------------------------------------------*/
	Luma_data = displayBuf->bufDesc[0].buf; /*Init for Y*/
	CbCr_data = displayBuf->bufDesc[1].buf; /*Init for CbCr*/

	/*----------------------------------------------------------------*/
	/* Init output yuv_buffer with global pointer fullPic             */
	/*----------------------------------------------------------------*/
	CbCr_seperate[0] = Chroma_separate; /*Init for Cb*/
	CbCr_seperate[1] = CbCr_seperate[0] + (pic_size >> 2); /*Init for Cr*/

	/*----------------------------------------------------------------*/
	/* This function seperated out the Cb and Cr component            */
	/*----------------------------------------------------------------*/
	dvtb_separateCbCrPixels(CbCr_data, CbCr_seperate, (height >> 1), width, displayBuf->framePitch);

	/*----------------------------------------------------------------*/
	/* Write YUV data to File                                         */
	/*----------------------------------------------------------------*/
	for (height = 0; height < displayBuf->frameHeight; height++)
	{
		if (DVEVM_ST_FAIL == dvtb_fileWrite(fOutFile, (char *) Luma_data, displayBuf->frameWidth))
		{
			SYS_ERROR("Error in writing to file.\n");
			retCode = DVEVM_ST_FAIL;
			break;
		}

		Luma_data += displayBuf->framePitch;
	}

	if (DVEVM_ST_SUCCESS == retCode)
	{

		if (DVEVM_ST_FAIL == dvtb_fileWrite(fOutFile, (char *) CbCr_seperate[0], pic_size >> 2))
		{
			SYS_ERROR("Error in writing to file.\n");
			retCode = DVEVM_ST_FAIL;
		}
		else if (DVEVM_ST_FAIL == dvtb_fileWrite(fOutFile, (char *) CbCr_seperate[1], pic_size >> 2))
		{
			SYS_ERROR("Error in writing to file.\n");
			retCode = DVEVM_ST_FAIL;
		}
	}

	return retCode;
}

