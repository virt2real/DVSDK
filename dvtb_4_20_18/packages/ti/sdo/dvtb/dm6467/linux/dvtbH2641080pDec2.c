/*
 * dvtbH2641080pDec2.c
 *
 * XDM1.2 H2641080p Decode Interface implementation
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
#include "dvtbH2641080pDec2.h"
//#define FOR_DEBUGGING_AT_DSP_END

void
dvtb_h2641080pDec2InitDebug(IH2641080P60VDEC_Params *vdp)
{
	SYS_DEBUG("\n<======== H264 Decoder Params Debug Start ==========>\n");
	SYS_DEBUG("Size                  : %d\n", (int) vdp->viddecParams.size);
	SYS_DEBUG("Max Height            : %d\n", (int) vdp->viddecParams.maxHeight);
	SYS_DEBUG("Max Width             : %d\n", (int) vdp->viddecParams.maxWidth);
	SYS_DEBUG("Max Frame Rate        : %d\n", (int) vdp->viddecParams.maxFrameRate);
	SYS_DEBUG("Max Bit Rate          : %d\n", (int) vdp->viddecParams.maxBitRate);
	SYS_DEBUG("Endianness            : %d\n", (int) vdp->viddecParams.dataEndianness);
	SYS_DEBUG("Chroma Format         : %d\n", (int) vdp->viddecParams.forceChromaFormat);
	SYS_DEBUG("Ext Display Delay     : %d\n", (int) vdp->displayDelay);
	SYS_DEBUG("Ext Preset Level      : %d\n", (int) vdp->presetLevelIdc);
	SYS_DEBUG("Ext Preset Profile    : %d\n", (int) vdp->presetProfileIdc);
	SYS_DEBUG("Ext Temporal Dir Mode : %d\n", (int) vdp->temporalDirModePred);
	SYS_DEBUG("\n<======== H264 Decoder Params Debug End ============>\n\n");
}

void
dvtb_h2641080pDec2InArgsDebug(IH2641080P60VDEC_InArgs *vdi)
{
	SYS_DEBUG("\n<======== H264 Decoder InArgs Debug Start ==========>\n");
	SYS_DEBUG("Size                  : %d\n", (int) vdi->viddecInArgs.size);
	SYS_DEBUG("numBytes              : %d\n", (int) vdi->viddecInArgs.numBytes);
	SYS_DEBUG("inputID               : %d\n", (int) vdi->viddecInArgs.inputID);
	SYS_DEBUG("Ext Skip Input Frame  : %d\n", (int) vdi->skipNonRefPicture);
	SYS_DEBUG("\n<======== H264 Decoder InArgs Debug End ============>\n");
}

void
dvtb_h2641080pDec2OutArgsDebug(IH2641080P60VDEC_OutArgs *vdo)
{
	int i = 0;
	SYS_DEBUG("\n<======== H264 Decoder OutArgs Debug Start ==========>\n");
	SYS_DEBUG("Size                 : %d\n", (int) vdo->viddecOutArgs.size);
	SYS_DEBUG("Bytes Consumed       : %d\n", (int) vdo->viddecOutArgs.bytesConsumed);
	for (i = 0; i < VIDDEC2_PLAY_MAX_BUFFERS; i++)
		SYS_DEBUG("OuputId[%d]          : %d\n", i, (int) vdo->viddecOutArgs.outputID[i]);

	//IVIDEO2_BufDesc decodedBufs;
	SYS_DEBUG("decodedBufs          :\n");
	dvtb_vidDec2IVIDEO2_BufDescDebug(&vdo->viddecOutArgs.decodedBufs);

	//IVIDEO2_BufDesc displayBufs[16];
	for (i = 0; i < VIDDEC2_PLAY_MAX_BUFFERS; i++)
	{
		SYS_DEBUG("displayBufs[%d]      :\n", i);
		dvtb_vidDec2IVIDEO2_BufDescDebug(&vdo->viddecOutArgs.displayBufs[i]);
	}

	SYS_DEBUG("OutputMBDataId       : %d\n", (int) vdo->viddecOutArgs.outputMbDataID);

	//XDM1_SingleBufDesc mbDataBuf;
	SYS_DEBUG("mbDataBuf            :\n");
	dvtb_vidDec2XDM1SingleBufDescDebug(&vdo->viddecOutArgs.mbDataBuf);

	for (i = 0; i < VIDDEC2_PLAY_MAX_BUFFERS; i++)
		SYS_DEBUG("FreeBufId[%d]        : %d\n", i, (int) vdo->viddecOutArgs.freeBufID[i]);
	SYS_DEBUG("OutBufsInUseFlag     : %d\n", (int) vdo->viddecOutArgs.outBufsInUseFlag);
	SYS_DEBUG("Ext SEI Parsed Flag     : %d\n", (int) vdo->seiVuiParams.parsed_flag);
	SYS_DEBUG("Ext Curr Pic Skipped     : %d\n", (int) vdo->currPicSkipped);
	SYS_DEBUG("\n<======== H264 Decoder OutArgs Debug End ============>\n");
}

void
dvtb_h2641080pDec2ControlDebug(IH2641080P60VDEC_Status *vds)
{
	int i = 0;
	SYS_DEBUG("\n<======== Video Decoder Status Debug Start ==========>\n");
	SYS_DEBUG("Size               : %d\n", (int) vds->viddecStatus.size);
	SYS_DEBUG("Extended Error     : %d\n", (int) vds->viddecStatus.extendedError);

	//XDM1_SingleBufDesc data;
	SYS_DEBUG("data               :\n");
	dvtb_vidDec2XDM1SingleBufDescDebug(&vds->viddecStatus.data);

	SYS_DEBUG("Output Height      : %d\n", (int) vds->viddecStatus.outputHeight);
	SYS_DEBUG("Output Width       : %d\n", (int) vds->viddecStatus.outputWidth);
	SYS_DEBUG("Avg Frame Rate     : %d\n", (int) vds->viddecStatus.frameRate);
	SYS_DEBUG("Avg Bit Rate       : %d\n", (int) vds->viddecStatus.bitRate);
	SYS_DEBUG("Content Type       : %d\n", (int) vds->viddecStatus.contentType);
	SYS_DEBUG("Chroma Format      : %d\n", (int) vds->viddecStatus.outputChromaFormat);
	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) vds->viddecStatus.bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) vds->viddecStatus.bufInfo.minNumOutBufs);
	for (i = 0; i < vds->viddecStatus.bufInfo.minNumInBufs; i++)
	{
		SYS_DEBUG("BUF-Min In[%d] Size = %d    : %d\n", i, (int) vds->viddecStatus.bufInfo.minInBufSize[i], i);
	}
	for (i = 0; i < vds->viddecStatus.bufInfo.minNumOutBufs; i++)
	{
		SYS_DEBUG("BUF-Min Out[%d] Size = %d    : %d\n", i, (int) vds->viddecStatus.bufInfo.minOutBufSize[i], i);
	}
	SYS_DEBUG("\n<======== Video Decoder Status Debug End ============>\n");
}

void
dvtb_h2641080pDec2Cleanup(DvevmStH2641080pDec2Info *vd)
{
	if (NULL != vd->vdec2Hdl)
	{
		VIDDEC2_delete(vd->vdec2Hdl);
		vd->vdec2Hdl = NULL;
	}
}

DvevmStRetCode
dvtb_h2641080pDec2Init(DvevmStH2641080pDec2Info *vd)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(vd != NULL);
	ASSERT(vd->ceHdl != NULL);
	ASSERT(vd->vdec2Name[0] != 0);

	SYS_DEBUG("Codec Instance Init: Engine Handle 0x%x\n", (unsigned int) vd->ceHdl);
	SYS_DEBUG("Codec Instance Init: vdec name \"%s\"\n", vd->vdec2Name);

	dvtb_h2641080pDec2InitDebug(&vd->vdec2Params);

	if (NULL == (vd->vdec2Hdl = VIDDEC2_create(vd->ceHdl, vd->vdec2Name,(VIDDEC2_Params *)&vd->vdec2Params)))
	{
		SYS_ERROR("Unable to initialize Video Decoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Video Decoder Instance created.\n");

		vd->vdec2Cmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_h2641080pDec2Control(vd))
		{
			SYS_ERROR("Unable to set dynamic params\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			vd->vdec2Cmd = XDM_GETBUFINFO;
			if (DVEVM_ST_FAIL == dvtb_h2641080pDec2Control(vd))
			{
				SYS_ERROR("Unable to get the input/output buffer information\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_DEBUG("Video Decoder <%s> initialized\n", vd->vdec2Name);
				dvtb_h2641080pDec2InitDebug(&vd->vdec2Params);
			}
		}
	}

	if (DVEVM_ST_FAIL == retCode)
		dvtb_h2641080pDec2Cleanup(vd);

	return retCode;
}

DvevmStRetCode
dvtb_h2641080pDec2Decode(DvevmStH2641080pDec2Info *vd, int *decDuration)
{
	int status = -1;
	DvevmStTime timeStmpBfrDec, timeStmpAftrDec;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(vd != NULL);
	ASSERT(vd->vdec2Hdl != NULL);

	vd->skipFrame = DVEVM_ST_FALSE;
	vd->vdec2InArgs.skipNonRefPicture = 0; //Do not skip the pictures

	timeStmpBfrDec = dvtb_getTime( );
	status = VIDDEC2_process(vd->vdec2Hdl, &vd->inBufDesc, &vd->outBufDesc,(VIDDEC2_InArgs *)&vd->vdec2InArgs,(VIDDEC2_OutArgs *)&vd->vdec2OutArgs);
	timeStmpAftrDec = dvtb_getTime( );
	*decDuration = ((timeStmpAftrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrDec.tv_usec) - ((timeStmpBfrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrDec.tv_usec);

	if (status != VIDDEC2_EOK)
	{
		SYS_ERROR("Video Decode Process Failed (%d)\n", (int) status);
		vd->vdec2Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_h2641080pDec2Control(vd))
		{
			SYS_ERROR("Unable to get the status \n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			SYS_ERROR("Codec Error = %d\n", (int) vd->vdec2Status.viddecStatus.extendedError);

			if (XDM_ISFATALERROR(vd->vdec2Status.viddecStatus.extendedError))
			{
				SYS_ERROR("Video Decode Process failed (%d) with a Codec fatal error %x.  Exiting.\n", (int) status, (int) vd->vdec2Status.viddecStatus.extendedError);
				retCode = DVEVM_ST_FAIL;
			}

			SYS_ERROR("Video Decode Process failed (%d) with a Codec non fatal error %x.  Continuing.\n", (int) status, (int) vd->vdec2Status.viddecStatus.extendedError);
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_h2641080pDec2Control(DvevmStH2641080pDec2Info *vd)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(vd != NULL);
	ASSERT(vd->vdec2Hdl != NULL);

	vd->vdec2Status.viddecStatus.data.buf = NULL;

	status = VIDDEC2_control(vd->vdec2Hdl, vd->vdec2Cmd,(VIDDEC2_DynamicParams *)&vd->vdec2DynParams,(VIDDEC2_Status *)&vd->vdec2Status);
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
			vd->inBuf.numBufs = vd->vdec2Status.viddecStatus.bufInfo.minNumInBufs;
			for (i = 0; i < vd->inBuf.numBufs; i++)
				vd->inBuf.bufSizes[i] = vd->vdec2Status.viddecStatus.bufInfo.minInBufSize[i];

			vd->outBuf.numBufs = vd->vdec2Status.viddecStatus.bufInfo.minNumOutBufs;
			for (i = 0; i < vd->outBuf.numBufs; i++)
				vd->outBuf.bufSizes[i] = vd->vdec2Status.viddecStatus.bufInfo.minOutBufSize[i];

			dvtb_h2641080pDec2ControlDebug(&vd->vdec2Status);
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_h2641080pDec2Close(DvevmStH2641080pDec2Info *vd)
{
	dvtb_h2641080pDec2Cleanup(vd);
	return DVEVM_ST_SUCCESS;
}

