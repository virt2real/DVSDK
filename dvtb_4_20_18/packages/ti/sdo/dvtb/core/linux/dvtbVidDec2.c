/*
 * dvtbVidDec2.c
 *
 * XDM1.0 Video Decoder implementation
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

#include "dvtbVidDec2.h"

//#define FOR_DEBUGGING_AT_DSP_END

void
dvtb_vidDec2XDM1SingleBufDescDebug(XDM1_SingleBufDesc *sbd)
{
	SYS_DEBUG("\tbuf                   : %x\n", (int) sbd->buf);
	SYS_DEBUG("\tbufSize               : %d\n", (int) sbd->bufSize);
	SYS_DEBUG("\taccessMask            : %d\n", (int) sbd->accessMask);
}

void
dvtb_vidDec2IVIDEO2_BufDescDebug(IVIDEO1_BufDesc *bd)
{
	int i = 0;
	SYS_DEBUG("\tNumBufs               : %d\n", (int) bd->numBufs);
	SYS_DEBUG("\tframeWidth            : %d\n", (int) bd->frameWidth);
	SYS_DEBUG("\tframeHeight           : %d\n", (int) bd->frameHeight);
	SYS_DEBUG("\tframePitch            : %d\n", (int) bd->framePitch);

	//The following loop is for XDM1_SingleBufDesc bufDesc[3];
	for (i = 0; i < 3; i++)
	{
		SYS_DEBUG("\tbufDesc[%d]             :\n", i);
		dvtb_vidDec2XDM1SingleBufDescDebug(&bd->bufDesc[i]);
	}
	SYS_DEBUG("\textendedError         : %d\n", (int) bd->extendedError);
	SYS_DEBUG("\tframeType             : %d\n", (int) bd->frameType);
	SYS_DEBUG("\ttopFieldFirstFlag     : %d\n", (int) bd->topFieldFirstFlag);
	SYS_DEBUG("\trepeatFirstFieldFlag  : %d\n", (int) bd->repeatFirstFieldFlag);
	SYS_DEBUG("\tframeStatus           : %d\n", (int) bd->frameStatus);
	SYS_DEBUG("\trepeatFrame           : %d\n", (int) bd->repeatFrame);
	SYS_DEBUG("\tcontentType           : %d\n", (int) bd->contentType);
	SYS_DEBUG("\tchromaFormat          : %d\n", (int) bd->chromaFormat);
}

void
dvtb_vidDec2InitDebug(VIDDEC2_Params *vdp)
{
	SYS_DEBUG("\n<======== Video Decoder Params Debug Start ==========>\n");
	SYS_DEBUG("Size               : %d\n", (int) vdp->size);
	SYS_DEBUG("Max Height         : %d\n", (int) vdp->maxHeight);
	SYS_DEBUG("Max Width          : %d\n", (int) vdp->maxWidth);
	SYS_DEBUG("Max Frame Rate     : %d\n", (int) vdp->maxFrameRate);
	SYS_DEBUG("Max Bit Rate       : %d\n", (int) vdp->maxBitRate);
	SYS_DEBUG("Endianness         : %d\n", (int) vdp->dataEndianness);
	SYS_DEBUG("Chroma Format      : %d\n", (int) vdp->forceChromaFormat);
	SYS_DEBUG("\n<======== Video Decoder Params Debug End ============>\n\n");
}

void
dvtb_vidDec2InArgsDebug(VIDDEC2_InArgs *vdi)
{
	SYS_DEBUG("\n<======== Video Decoder InArgs Debug Start ==========>\n");
	SYS_DEBUG("Size                 : %d\n", (int) vdi->size);
	SYS_DEBUG("numBytes             : %d\n", (int) vdi->numBytes);
	SYS_DEBUG("inputID              : %d\n", (int) vdi->inputID);
	SYS_DEBUG("\n<======== Video Decoder InArgs Debug End ============>\n");
}

void
dvtb_vidDec2OutArgsDebug(VIDDEC2_OutArgs *vdo)
{
	int i = 0;
	SYS_DEBUG("\n<======== Video Decoder OutArgs Debug Start ==========>\n");
	SYS_DEBUG("Size                 : %d\n", (int) vdo->size);
	SYS_DEBUG("Bytes Consumed       : %d\n", (int) vdo->bytesConsumed);
	for (i = 0; i < VIDDEC2_PLAY_MAX_BUFFERS; i++)
		SYS_DEBUG("OuputId[%d]          : %d\n", i, (int) vdo->outputID[i]);

	//IVIDEO2_BufDesc decodedBufs;
	SYS_DEBUG("decodedBufs          :\n");
	dvtb_vidDec2IVIDEO2_BufDescDebug(&vdo->decodedBufs);

	//IVIDEO2_BufDesc displayBufs[16];
	for (i = 0; i < VIDDEC2_PLAY_MAX_BUFFERS; i++)
	{
		SYS_DEBUG("displayBufs[%d]      :\n", i);
		dvtb_vidDec2IVIDEO2_BufDescDebug(&vdo->displayBufs[i]);
	}

	SYS_DEBUG("OutputMBDataId       : %d\n", (int) vdo->outputMbDataID);

	//XDM1_SingleBufDesc mbDataBuf;
	SYS_DEBUG("mbDataBuf            :\n");
	dvtb_vidDec2XDM1SingleBufDescDebug(&vdo->mbDataBuf);

	for (i = 0; i < VIDDEC2_PLAY_MAX_BUFFERS; i++)
		SYS_DEBUG("FreeBufId[%d]        : %d\n", i, (int) vdo->freeBufID[i]);
	SYS_DEBUG("OutBufsInUseFlag     : %d\n", (int) vdo->outBufsInUseFlag);
	SYS_DEBUG("\n<======== Video Decoder OutArgs Debug End ============>\n");
}

void
dvtb_vidDec2ControlDebug(VIDDEC2_Status *vds)
{
	int i = 0;
	SYS_DEBUG("\n<======== Video Decoder Status Debug Start ==========>\n");
	SYS_DEBUG("Size               : %d\n", (int) vds->size);
	SYS_DEBUG("Extended Error     : %d\n", (int) vds->extendedError);

	//XDM1_SingleBufDesc data;
	SYS_DEBUG("data               :\n");
	dvtb_vidDec2XDM1SingleBufDescDebug(&vds->data);

	SYS_DEBUG("Max Display BUFF   : %d\n", (int) vds->maxNumDisplayBufs);
	SYS_DEBUG("Output Height      : %d\n", (int) vds->outputHeight);
	SYS_DEBUG("Output Width       : %d\n", (int) vds->outputWidth);
	SYS_DEBUG("Avg Frame Rate     : %d\n", (int) vds->frameRate);
	SYS_DEBUG("Avg Bit Rate       : %d\n", (int) vds->bitRate);
	SYS_DEBUG("Content Type       : %d\n", (int) vds->contentType);
	SYS_DEBUG("Chroma Format      : %d\n", (int) vds->outputChromaFormat);
	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) vds->bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) vds->bufInfo.minNumOutBufs);
	for (i = 0; i < vds->bufInfo.minNumInBufs; i++)
	{
		SYS_DEBUG("BUF-Min In[%d] Size = %d    : %d\n", i, (int) vds->bufInfo.minInBufSize[i], i);
	}
	for (i = 0; i < vds->bufInfo.minNumOutBufs; i++)
	{
		SYS_DEBUG("BUF-Min Out[%d] Size = %d    : %d\n", i, (int) vds->bufInfo.minOutBufSize[i], i);
	}
	SYS_DEBUG("\n<======== Video Decoder Status Debug End ============>\n");
}

void
dvtb_vidDec2Cleanup(DvevmStVidDec2Info *vd)
{
	if (NULL != vd->vdec2Hdl)
	{
		VIDDEC2_delete(vd->vdec2Hdl);
		vd->vdec2Hdl = NULL;
	}
}

DvevmStRetCode
dvtb_vidDec2Init(DvevmStVidDec2Info *vd)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(vd != NULL);
	ASSERT(vd->ceHdl != NULL);
	ASSERT(vd->vdec2Name[0] != 0);

	SYS_DEBUG("Codec Instance Init: Engine Handle 0x%x\n", (unsigned int) vd->ceHdl);
	SYS_DEBUG("Codec Instance Init: vdec name \"%s\"\n", vd->vdec2Name);

	dvtb_vidDec2InitDebug(&vd->vdec2Params);

	if (NULL == (vd->vdec2Hdl = VIDDEC2_create(vd->ceHdl, vd->vdec2Name, &vd->vdec2Params)))
	{
		SYS_ERROR("Unable to initialize Video Decoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Video Decoder Instance created.\n");

		vd->vdec2Cmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_vidDec2Control(vd))
		{
			SYS_ERROR("Unable to set dynamic params\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			vd->vdec2Cmd = XDM_GETBUFINFO;
			if (DVEVM_ST_FAIL == dvtb_vidDec2Control(vd))
			{
				SYS_ERROR("Unable to get the input/output buffer information\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_DEBUG("Video Decoder <%s> initialized\n", vd->vdec2Name);
				dvtb_vidDec2InitDebug(&vd->vdec2Params);
			}
		}
	}

	if (DVEVM_ST_FAIL == retCode)
		dvtb_vidDec2Cleanup(vd);

	return retCode;
}

DvevmStRetCode
dvtb_vidDec2Decode(DvevmStVidDec2Info *vd, int *decDuration)
{
	int status = -1;
	DvevmStTime timeStmpBfrDec, timeStmpAftrDec;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(vd != NULL);
	ASSERT(vd->vdec2Hdl != NULL);

	vd->skipFrame = DVEVM_ST_FALSE;

	timeStmpBfrDec = dvtb_getTime( );
	status = VIDDEC2_process(vd->vdec2Hdl, &vd->inBufDesc, &vd->outBufDesc, &vd->vdec2InArgs, &vd->vdec2OutArgs);
	timeStmpAftrDec = dvtb_getTime( );
	*decDuration = ((timeStmpAftrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrDec.tv_usec) - ((timeStmpBfrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrDec.tv_usec);
	
	if (status != VIDDEC2_EOK)
	{
		SYS_ERROR("Video Decode Process Failed (%d)\n", (int) status);
		vd->vdec2Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_vidDec2Control(vd))
		{
			SYS_ERROR("Unable to get the status \n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			SYS_ERROR("Codec Error = %d\n", (int) vd->vdec2Status.extendedError);

			if (XDM_ISFATALERROR(vd->vdec2Status.extendedError))
			{
				SYS_ERROR("Video Decode Process failed (%d) with a Codec fatal error %x.  Exiting.\n", (int) status, (int) vd->vdec2Status.extendedError);
				retCode = DVEVM_ST_FAIL;
			}

			SYS_ERROR("Video Decode Process failed (%d) with a Codec non fatal error %x.  Continuing.\n", (int) status, (int) vd->vdec2Status.extendedError);
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_vidDec2Control(DvevmStVidDec2Info *vd)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(vd != NULL);
	ASSERT(vd->vdec2Hdl != NULL);

	vd->vdec2Status.data.buf = NULL;

	status = VIDDEC2_control(vd->vdec2Hdl, vd->vdec2Cmd, &vd->vdec2DynParams, &vd->vdec2Status);
	if (VIDDEC2_EOK != status)
	{
		SYS_ERROR("Video Decode Control failed (%d)\n", status);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Video Decode Control => Command : %d\n", vd->vdec2Cmd);

		if (XDM_GETBUFINFO == vd->vdec2Cmd)
		{
			vd->inBuf.numBufs = vd->vdec2Status.bufInfo.minNumInBufs;
			for (i = 0; i < vd->inBuf.numBufs; i++)
				vd->inBuf.bufSizes[i] = vd->vdec2Status.bufInfo.minInBufSize[i];

			vd->outBuf.numBufs = vd->vdec2Status.bufInfo.minNumOutBufs;
			for (i = 0; i < vd->outBuf.numBufs; i++)
				vd->outBuf.bufSizes[i] = vd->vdec2Status.bufInfo.minOutBufSize[i];

			dvtb_vidDec2ControlDebug(&vd->vdec2Status);
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_vidDec2Close(DvevmStVidDec2Info *vd)
{
	dvtb_vidDec2Cleanup(vd);
	return DVEVM_ST_SUCCESS;
}

