/*
 * dvtbVidPlay2Core.c
 *
 * DVTB(wince) XDM1.0 Video Decode related Core Functions
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

#include "dvtbVidPlay2Core.h"

/*********************************************************************
 *	dvtb_vidDec2ProcessEndMessage:
 *	Description: Print Number of frames processed
 ********************************************************************/
void
dvtb_vidDec2ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
        if (DVEVM_ST_FALSE == fileBased)//Driver based
        {
                if (useAlgorithm)
                        SYS_OUT("Total # of frames Decoded & Displayed = %d.\n", nFrames - 1);
                else
                        SYS_OUT("Total # of frames Displayed = %d. \n", nFrames - 1);
        }
        else//File based
                SYS_OUT("Total # of frames Decoded & Dumped = %d. \n", nFrames - 1);
}

/*********************************************************************
 *	dvtb_vidDec2InitPtrs:
 *	Description: Initialize elements of DvevmStVidDec2Info
 ********************************************************************/
void
dvtb_vidDec2InitPtrs(DvevmStVidDec2Info *vd)
{
        int i = 0, j = 0;

        vd->hTime = NULL;

	//Initialize CE handle to NULL
        vd->ceHdl = NULL;
	//Initialize CE handle to NULL
        vd->vdec2Hdl = NULL;

	//Initialize numBufs of inBufs, outBuf and firstBuffer to zero
        vd->inBuf.numBufs = 0;
        vd->outBuf.numBufs = 0;
        vd->firstBuffer.numBufs = 0;

	//Initialize all buffer pointers of inBufs, outBuf and firstBuffer to NULL
        for(i=0; i<MAX_XDM_BUFS; i++)
        {
                vd->inBuf.bufs[i] = NULL;
                vd->outBuf.bufs[i] = NULL;
                vd->firstBuffer.bufs[i] = NULL;
        }

        vd->totBuf = 1;

        for(i=0; i<VIDDEC2_PLAY_MAX_BUFFERS; i++)
        {
		//Initialize numBufs to zero and all buffer pointers to NULL
                vd->outBufArray[i].buffer.numBufs = 0;
                for(j=0; j<MAX_XDM_BUFS; j++)
                        vd->outBufArray[i].buffer.bufs[j] = NULL;

		// Set the status of the buffer to FREE
                vd->outBufArray[i].isFree = DVEVM_ST_TRUE;
		// Set the id of the buffer
                vd->outBufArray[i].id = i+1;
        }
}

/*********************************************************************
 *	dvtb_vidDec2HanInit:
 *	Description: Initialize CE and Codec Instance
 ********************************************************************/
DvevmStRetCode
dvtb_vidDec2HanInit(DvevmStVidDec2Info *vd, char *engName)
{
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        do //Dummy loop for easy clean up
        {
                // Initialize Engine
                if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &vd->ceHdl))
                {
                        SYS_ERROR("Unable to initialize Codec Engine <%s>.\n",engName);
                        retCode = DVEVM_ST_FAIL;
                        break;
                }

#ifdef FOR_DEBUGGING_AT_DSP_END
                SYS_DEBUG("Engine opened. Now hit enter to debug on the DSP end.");
                getchar();
#endif

                //Initialize Codec Instance
                if (DVEVM_ST_FAIL == dvtb_vidDec2Init(vd))
                {
                        SYS_ERROR("Unable to initialize Video Decoder <%s>.\n",vd->vdec2Name);
                        retCode = DVEVM_ST_FAIL;
                        break;
                }
        }while(DVEVM_ST_FALSE); // Dummy Loop

        return retCode;
}

/*********************************************************************
 *	dvtb_vidDec2DeInitOutBuffers:
 *	Description: Release memory from output buffers
 ********************************************************************/
DvevmStRetCode
dvtb_vidDec2DeInitOutBuffers(DvevmStVidDec2Info *vd)
{
        unsigned int i=0;

        //Free first buffer
        if (0 < vd->firstBuffer.numBufs)
                dvtb_freeCmemSingleChunk(&vd->firstBuffer);

        //Free remaining buffers
        for (i = 1; (int)i < vd->totBuf; i++)
        {
                if(0 < vd->outBufArray[i].buffer.numBufs)
                        dvtb_freeCmemSingleChunk(&vd->outBufArray[i].buffer);
        }

        return DVEVM_ST_SUCCESS;
}


/*********************************************************************
 *	dvtb_vidDec2DeInitOutBuffers:
 *	Description: Release memory,  Close Codec instance and CE
 ********************************************************************/
void
dvtb_vidDec2HanClose(DvevmStVidDec2Info *vd, char *engName)
{
        //Free the allocated Input Buffer
        if(0 < vd->inBuf.numBufs )
                dvtb_freeCmem(&vd->inBuf);

        //Free all the allocated output buffers
        dvtb_vidDec2DeInitOutBuffers(vd);

	//Close Codec Instance
        dvtb_vidDec2Close(vd);
        SYS_OUT("Video Decoder <%s> closed.\n", vd->vdec2Name);

	//Close CE
        if (DVEVM_ST_FAIL == dvtb_ceDeInit(&vd->ceHdl))
                SYS_ERROR("Unable to close Engine <%s>.\n", engName);
        else
                SYS_OUT("Engine <%s> closed.\n", engName);
}

/*********************************************************************
 *	dvtb_vidDec2InBuffAlloc:
 *	Description: Allocate memory for input Buffer
 ********************************************************************/
DvevmStRetCode
dvtb_vidDec2InBuffAlloc(DvevmStXdmBuffer *inBuf, XDM1_BufDesc *inBufDesc, int minNumInBufs)
{
        int i = 0;
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        do //Dummy loop for easy clean up
        {
                //Allocate the contig memory for inBuf
                if (DVEVM_ST_FAIL == dvtb_allocCmem(inBuf))
                {
                        SYS_ERROR("Unable to allocate memory for input buffer. \n");
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
        }while(DVEVM_ST_FALSE); // Dummy Loop

        return retCode;
}

/*********************************************************************
 *	dvtb_vidDec2AllocOutBuffer:
 *	Description: Finds Available output buffer
 ********************************************************************/
DvevmStBufElement*
dvtb_vidDec2AllocOutBuffer(DvevmStVidDec2Info *vd)
{
        unsigned int i=0;

        for(i=0; (int)i<vd->totBuf; i++)
        {
		//Find Available buffer
                if(vd->outBufArray[i].isFree == DVEVM_ST_TRUE)
                {
			//Mark buffer as in use
                        vd->outBufArray[i].isFree = DVEVM_ST_FALSE;

			//Return buffer
                        return &vd->outBufArray[i];
                }
        }

        return NULL;
}

/*********************************************************************
 *	dvtb_vidDec2DecProcess:
 *	Description: Decode frame/field
 ********************************************************************/
DvevmStRetCode
dvtb_vidDec2DecProcess(DvevmStVidDec2Info *vd, int *decDuration)
{
        int frameSize = 0;
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
        DvevmStBufElement *freeBufElement=NULL;
	do//Dummy loop for easy clean up
        {
                if(!vd->vdec2OutArgs.outBufsInUseFlag)
                {
			// Get free output buffer
                        freeBufElement = dvtb_vidDec2AllocOutBuffer(vd);
                        if(NULL == freeBufElement)
                        {
                                SYS_ERROR("No more free out buffers in the pool that can be allocated for processing.\n");
                                retCode = DVEVM_ST_FAIL;
                                break;
                        }

                        vd->outBufDesc.numBufs = freeBufElement->buffer.numBufs;
                        vd->outBufDesc.bufSizes = (XDAS_Int32 *) freeBufElement->buffer.bufSizes;
                        vd->outBufDesc.bufs = (XDAS_Int8 **) freeBufElement->buffer.bufs;
                        vd->vdec2InArgs.inputID = freeBufElement->id;
                }

                // Make a Decode Process call
                if (DVEVM_ST_FAIL == dvtb_vidDec2Decode(vd, decDuration))
                {
                        SYS_ERROR("Unable to decode <%s>. \n",vd->vdec2Name);

                        vd->vdec2Cmd = XDM_GETSTATUS;
                        if (DVEVM_ST_FAIL == dvtb_vidDec2Control(vd))
                                SYS_ERROR("Unable to get the status. \n");
                        else
                                SYS_ERROR("Codec Error = %d.\n", (int) vd->vdec2Status.extendedError);

                        retCode = DVEVM_ST_FAIL;
                        break;
                }

		//Get status of video decoder
                frameSize = vd->vdec2OutArgs.bytesConsumed;
                if (0 != frameSize)
                {
                        vd->vdec2Cmd = XDM_GETSTATUS;
                        if (DVEVM_ST_FAIL == dvtb_vidDec2Control(vd))
                        {
                                SYS_ERROR("Unable to get the status. \n");
                                retCode = DVEVM_ST_FAIL;
                                break;
                        }
                }
        }while(DVEVM_ST_FALSE);
        return retCode;
}
#if 0
DvevmStRetCode
dvtb_vidDec2DisplayOutputData(DvevmStGlobalParams *g, char *in_buff, int size)
{
        void *displayBuffer=NULL;
        DvevmStVpbeInfo *vpbe = &g->vpbe;
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	// Get display buffer from diver
        displayBuffer = dvtb_vpbeGetDisplayBuffer(vpbe);
        if(NULL == displayBuffer)
        {
                SYS_ERROR("Unable to get the Display buffer.\n");
                retCode = DVEVM_ST_FAIL;
        }
        else
        {
		// Copy output in display buffer
                if(DVEVM_ST_FAIL == dvtb_vidDec2Copy(g, (char *)displayBuffer, in_buff, size))
                {
                        SYS_ERROR("Unable to copy in display buffer.\n");
                        retCode = DVEVM_ST_FAIL;
                }
                else
                {
			// Give display buffer to driver
                        if(DVEVM_ST_FAIL == dvtb_vpbeDisplay(vpbe, displayBuffer))
                        {
                                SYS_ERROR("Unable to display output buffer.\n");
                                retCode = DVEVM_ST_FAIL;
                        }
                }
        }
        return retCode;
}
#endif

/*********************************************************************
 *	dvtb_vidDec2ProcessOutBuff:
 *	Description: Process output of decoder
 ********************************************************************/
DvevmStRetCode
dvtb_vidDec2ProcessOutBuff(DvevmStGlobalParams *g, DvevmStVidDec2Info *vd, FILE *fp, DvevmStBool fileBased, int nFrames, int *displayFrame)
{
        int validOutIds = 0, frames = 0;
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        frames = *displayFrame;
        //Check for Frame ready via outputID array and display buffer pointers
        validOutIds = 0;
        while(vd->vdec2OutArgs.outputID[validOutIds] > 0)//loop to display/dump all output buffers
        {
                SYS_DEBUG("Valid output id = %d\n",validOutIds);

                if(DVEVM_ST_TRUE == fileBased)
                {
			// Dump output in file
                        SYS_DEBUG("Frame #%d, OutputId %d.\n", nFrames, (int)vd->vdec2OutArgs.outputID[validOutIds]);
                        if(DVEVM_ST_FAIL == dvtb_vidDec2WriteOutputData(&vd->vdec2OutArgs.displayBufs[validOutIds], fp, &vd->vdec2Status))
                        {
                                SYS_ERROR("Unable to Dump frame # %d. \n",frames);
                                retCode = DVEVM_ST_FAIL;
                                break;
                        }
                        SYS_OUT("Dumped Frame# <%d>.\n", frames);
                        frames++;
                }
                else
                {
#if 0
			// Give output to driver for display
                        if(DVEVM_ST_FAIL == dvtb_vidDec2DisplayOutputData(g, (char *)vd->vdec2OutArgs.displayBufs[validOutIds].bufDesc[0].buf, vd->vdec2OutArgs.displayBufs[validOutIds].bufDesc[0].bufSize))
                        {
                                SYS_ERROR("Unable to display frame # %d .\n",frames);
                                retCode = DVEVM_ST_FAIL;
                                break;
                        }

                        SYS_OUT("Displayed Frame# %d.\n", frames);
                        frames++;
#endif
                }

                validOutIds++;
        }

        *displayFrame = frames;
        return retCode;
}

/*********************************************************************
 *	dvtb_vidDec2Flush:
 *	Description: Flush display buffer of codec
 ********************************************************************/
DvevmStRetCode
dvtb_vidDec2Flush(DvevmStGlobalParams *g, DvevmStVidDec2Info *vd, FILE *fp, DvevmStBool fileBased, int nFrames, int *displayFrame)
{
        int decDuration = 0, validOutIds = 0, frames = 0;
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        frames = *displayFrame;
        do
        {
		// Set Flush Mode
                vd->vdec2Cmd = XDM_FLUSH;

                if(DVEVM_ST_FAIL == dvtb_vidDec2Control(vd))
                {
                        SYS_ERROR("Unable to set Flush mode.\n");
                        retCode = DVEVM_ST_FAIL;
                        break;
                }

                SYS_OUT("Flushing out frames held by Video Decoder.\n");

                validOutIds = 0;
                while(frames < nFrames)
                {
			//Make decode process call in flush mode
                        if(DVEVM_ST_FAIL == dvtb_vidDec2Decode(vd, &decDuration))
                        {
                                SYS_ERROR("Process call returned error while flushing display buffers.\n");
                                retCode = DVEVM_ST_FAIL;
                                break;
                        }

			//Get status of decoder
                        vd->vdec2Cmd = XDM_GETSTATUS;
                        if(DVEVM_ST_FAIL == dvtb_vidDec2Control(vd))
                        {
                                SYS_ERROR("Unable to get the status of the decoder.\n");
                                retCode = DVEVM_ST_FAIL;
                                break;
                        }

			//break if there is no output buffer to display/dump
                        if(0 == vd->vdec2OutArgs.outputID[validOutIds])
                                break;
                        if(DVEVM_ST_TRUE == fileBased)
                        {
				// Dump output in File
                                SYS_DEBUG("Held Frame, OutputId %d.\n", (int)vd->vdec2OutArgs.outputID[validOutIds]);
                                if(DVEVM_ST_FAIL == dvtb_vidDec2WriteOutputData(&vd->vdec2OutArgs.displayBufs[validOutIds], fp, &vd->vdec2Status))
                                {
                                        SYS_ERROR("Unable to Dump frame # %d. \n",frames);
                                        retCode = DVEVM_ST_FAIL;
                                        break;
                                }
                                SYS_OUT("Dumped Frame# <%d>.\n", frames);
                        }
                        else
                        {
#if 0
                                if(DVEVM_ST_FAIL == dvtb_vidDec2UtilitySetup(g, &vd->vdec2OutArgs.displayBufs[validOutIds], 1))
                                {
                                        SYS_ERROR("Failed to do Utility setup \n");
                                        retCode = DVEVM_ST_FAIL;
                                        break;
                                }

				// Give output to driver for display
                                if(DVEVM_ST_FAIL == dvtb_vidDec2DisplayOutputData(g, (char *)vd->vdec2OutArgs.displayBufs[validOutIds].bufDesc[0].buf, vd->vdec2OutArgs.displayBufs[validOutIds].bufDesc[0].bufSize))
                                {
                                        SYS_ERROR("Unable to display frame # %d .\n",frames);
                                        retCode = DVEVM_ST_FAIL;
                                        break;
                                }

                                SYS_OUT("Displayed Frame# %d.\n", frames);
#endif
                        }
                        frames++;
                }
        }while (DVEVM_ST_FALSE);

        *displayFrame = frames;
        return retCode;
}

/*********************************************************************
 *	dvtb_vidDec2InitFirstOutBuffer:
 *	Description: Allocate memory for first out buffer
 ********************************************************************/
DvevmStRetCode
dvtb_vidDec2InitFirstOutBuffer(DvevmStVidDec2Info *vd)
{
        int i=0;
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        vd->outBufArray[0].buffer.numBufs = vd->vdec2Status.bufInfo.minNumOutBufs;
        for(i=0; i<vd->vdec2Status.bufInfo.minNumOutBufs; i++)
                vd->outBufArray[0].buffer.bufSizes[i] = vd->vdec2Status.bufInfo.minOutBufSize[i];

	// PAD last buffer with PAD_WIDTH
        vd->outBufArray[0].buffer.bufSizes[i-1] += VIDDEC2_PAD_WIDTH;

	// Alocate memory for first output buffer
        if (DVEVM_ST_FAIL == dvtb_allocCmemSingleChunk(&vd->outBufArray[0].buffer))
        {
                SYS_ERROR("Unable to allocate memory for 1st outBuf in the outBuf pool\n");
                retCode = DVEVM_ST_FAIL;
        }

	// first buffer in outBufArray
        dvtb_copyXdmBuf(&vd->outBufArray[0].buffer, &vd->firstBuffer);

        return retCode;
}

DvevmStRetCode
dvtb_vidDec2InitAllOutBuffers(DvevmStVidDec2Info *vd)
{
        unsigned int i = 0, j = 0;
        int maxBufs = 0;
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        vd->vdec2Cmd = XDM_GETBUFINFO;
        if(DVEVM_ST_FAIL == dvtb_vidDec2Control(vd))
        {
                SYS_ERROR("Unable to get the buffer requirements for this input stream.\n");
                retCode = DVEVM_ST_FAIL;
        }
        else
        {
                maxBufs = vd->vdec2Status.maxNumDisplayBufs;
                SYS_DEBUG("maxBufs = %d.\n",maxBufs);

                //Update buffsizes of All buffers
                for (j = 0; (int)j < maxBufs; j++)
                {
                    vd->outBufArray[j].buffer.numBufs = vd->vdec2Status.bufInfo.minNumOutBufs;
                    for(i=0; (int)i<vd->vdec2Status.bufInfo.minNumOutBufs; i++)
                        vd->outBufArray[j].buffer.bufSizes[i] = vd->vdec2Status.bufInfo.minOutBufSize[i];

                        vd->outBufArray[j].buffer.bufSizes[i-1] += VIDDEC2_PAD_WIDTH;
                }

                for(i=1; (int)i<maxBufs; i++)
                {
                        if (DVEVM_ST_FAIL == dvtb_allocCmemSingleChunk(&vd->outBufArray[i].buffer))
                        {
                                SYS_ERROR("Unable to allocate memory for <%d> outBuf in the outBuf pool\n", i);
                                retCode = DVEVM_ST_FAIL;
                                break;
                        }
                }

                //Make first buffer contiguous
                for (i = 1; (int)i < vd->vdec2Status.bufInfo.minNumOutBufs; i++)
                        vd->outBufArray[0].buffer.bufs[i] = vd->outBufArray[0].buffer.bufs[i - 1] + vd->outBufArray[0].buffer.bufSizes[i - 1];


                vd->totBuf = maxBufs;

        }

        return retCode;
}

DvevmStRetCode
dvtb_vidDec2ReleaseBuffers(DvevmStVidDec2Info *vd, unsigned int freeBufIds[])
{
        unsigned int i=0, id=0;

        for(i=0; (int)i<vd->totBuf; i++)
        {
                id = freeBufIds[i];

                /*
                 * Check if the buffer Id = 0 condition has reached. zero is not a
                 * valid buffer Id hence that value is used to identify the end of
                 * buffer array
                 */
                if(id == 0)
                        break;

                /*
                 * convert the buffer-Id to its corresponding index in the global
                 * array
                 */
                id--;
                // Set the status of the buffer to FREE
                vd->outBufArray[id].isFree = DVEVM_ST_TRUE;
        }

        return DVEVM_ST_SUCCESS;
}

