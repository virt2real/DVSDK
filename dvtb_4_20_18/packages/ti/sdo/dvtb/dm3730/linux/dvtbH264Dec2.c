/*
 * dvtbH264Dec2.c
 *
 * XDM1.2 H264 Decoder Interface implementation
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
#include "dvtbH264Dec2.h"
#include "dvtbMemory.h"
//#define FOR_DEBUGGING_AT_DSP_END

void
dvtb_h264Dec2InitDebug(IH264VDEC_Params *vdp)
{
	SYS_DEBUG("\n<======== H264 Decoder Params Debug Start ==========>\n");
	SYS_DEBUG("Size                  : %d\n", (int) vdp->viddecParams.size);
	SYS_DEBUG("Max Height            : %d\n", (int) vdp->viddecParams.maxHeight);
	SYS_DEBUG("Max Width             : %d\n", (int) vdp->viddecParams.maxWidth);
	SYS_DEBUG("Max Frame Rate        : %d\n", (int) vdp->viddecParams.maxFrameRate);
	SYS_DEBUG("Max Bit Rate          : %d\n", (int) vdp->viddecParams.maxBitRate);
	SYS_DEBUG("Endianness            : %d\n", (int) vdp->viddecParams.dataEndianness);
	SYS_DEBUG("Chroma Format         : %d\n", (int) vdp->viddecParams.forceChromaFormat);
        SYS_DEBUG("Num Ref Frames        : %d\n", (int) vdp->i4_num_ref_frames);
	SYS_DEBUG("Num Reorder Frames    : %d\n", (int) vdp->i4_num_reorder_frames);
	SYS_DEBUG("\n<======== H264 Decoder Params Debug End ============>\n\n");
}

void
dvtb_h264Dec2InArgsDebug(IH264VDEC_InArgs *vdi)
{
	SYS_DEBUG("\n<======== H264 Decoder InArgs Debug Start ==========>\n");
	SYS_DEBUG("Size                  : %d\n", (int) vdi->viddecInArgs.size);
	SYS_DEBUG("numBytes              : %d\n", (int) vdi->viddecInArgs.numBytes);
	SYS_DEBUG("inputID               : %d\n", (int) vdi->viddecInArgs.inputID);
	SYS_DEBUG("\n<======== H264 Decoder InArgs Debug End ============>\n");
}

void
dvtb_h264Dec2OutArgsDebug(IH264VDEC_OutArgs *vdo)
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
        SYS_DEBUG("Buf ID               : %d\n", (int) vdo->i4_buf_id);
	SYS_DEBUG("\n<======== H264 Decoder OutArgs Debug End ============>\n");
}

void
dvtb_h264Dec2ControlDebug(IH264VDEC_Status *vds)
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
dvtb_h264Dec2Cleanup(DvevmStH264Dec2Info *vd)
{
	if (NULL != vd->vdec2Hdl)
	{
		VIDDEC2_delete(vd->vdec2Hdl);
		vd->vdec2Hdl = NULL;
	}
#if 0
	if(NULL != vd->sei_vui_buffer)	
	{
		dvtb_freeSingleBufCmem((char *)vd->sei_vui_buffer,sizeof(sSeiVuiParams_t));
	}
#endif
}

DvevmStRetCode
dvtb_h264Dec2Init(DvevmStH264Dec2Info *vd)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(vd != NULL);
	ASSERT(vd->ceHdl != NULL);
	ASSERT(vd->vdec2Name[0] != 0);

	SYS_DEBUG("Codec Instance Init: Engine Handle 0x%x\n", (unsigned int) vd->ceHdl);
	SYS_DEBUG("Codec Instance Init: vdec name \"%s\"\n", vd->vdec2Name);

	dvtb_h264Dec2InitDebug(&vd->vdec2Params);

	if (NULL == (vd->vdec2Hdl = VIDDEC2_create(vd->ceHdl, vd->vdec2Name,(VIDDEC2_Params *)&vd->vdec2Params)))
	{
		SYS_ERROR("Unable to initialize Video Decoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Video Decoder Instance created.\n");

		vd->vdec2Cmd = XDM_SETPARAMS;
		if (DVEVM_ST_FAIL == dvtb_h264Dec2Control(vd))
		{
			SYS_ERROR("Unable to set dynamic params\n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			vd->vdec2Cmd = XDM_GETBUFINFO;
			if (DVEVM_ST_FAIL == dvtb_h264Dec2Control(vd))
			{
				SYS_ERROR("Unable to get the input/output buffer information\n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				SYS_DEBUG("Video Decoder <%s> initialized\n", vd->vdec2Name);
				dvtb_h264Dec2InitDebug(&vd->vdec2Params);
			}
		}
	}

	if (DVEVM_ST_FAIL == retCode)
		dvtb_h264Dec2Cleanup(vd);

	return retCode;
}
void
dvtb_h264UpdateSEIVUIBuffers(DvevmStH264Dec2Info *vd)
{
#if 0
	if(vd->vdec2DynParams.mbErrorBufFlag)
	{
		if(XDM_YUV_420P == vd->vdec2Params.viddecParams.forceChromaFormat)
		{
			memset(vd->outBufDesc.bufs[3], 0x00,vd->outBufDesc.bufSizes[3]);
			if(vd->vdec2DynParams.Sei_Vui_parse_flag)
			{
				vd->sei_vui_buffer = (sSeiVuiParams_t *)vd->outBufDesc.bufs[4];
//				memset(vd->sei_vui_buffer, 0x00, sizeof(sSeiVuiParams_t));
			}
		}
		else if(XDM_YUV_422ILE == vd->vdec2Params.viddecParams.forceChromaFormat)
		{
                        memset(vd->outBufDesc.bufs[1], 0x00,vd->outBufDesc.bufSizes[1]);
			if(vd->vdec2DynParams.Sei_Vui_parse_flag)
			{
				vd->sei_vui_buffer = (sSeiVuiParams_t *)vd->outBufDesc.bufs[2];
//				memset(vd->sei_vui_buffer, 0x00, sizeof(sSeiVuiParams_t));
			}
		}
	}
	else if(vd->vdec2DynParams.Sei_Vui_parse_flag)
	{
		if(XDM_YUV_420P == vd->vdec2Params.viddecParams.forceChromaFormat)
		{
			vd->sei_vui_buffer = (sSeiVuiParams_t *)vd->outBufDesc.bufs[3];
			vd->outBufDesc.bufs[4] = vd->outBufDesc.bufs[3];
			vd->outBufDesc.bufs[3] = NULL;
			vd->outBufDesc.bufSizes[4] = vd->outBufDesc.bufSizes[3];
//			memset(vd->sei_vui_buffer, 0x00, sizeof(sSeiVuiParams_t));
		}
		else if(XDM_YUV_422ILE == vd->vdec2Params.viddecParams.forceChromaFormat)
		{
			vd->sei_vui_buffer = (sSeiVuiParams_t *)vd->outBufDesc.bufs[1];
			vd->outBufDesc.bufs[2] = vd->outBufDesc.bufs[1];
			vd->outBufDesc.bufs[1] = NULL;
			vd->outBufDesc.bufSizes[2] = vd->outBufDesc.bufSizes[1];
//			memset(vd->sei_vui_buffer, 0x00, sizeof(sSeiVuiParams_t));
		}
	}


	if(vd->vdec2DynParams.Sei_Vui_parse_flag)
	{
//		vd->sei_vui_buffer->parsed_flag = 1;
//		vd->sei_vui_buffer->vui_params.parsed_flag = 1;
//		vd->sei_vui_buffer->sei_messages.parsed_flag = 1;
//		vd->sei_vui_buffer->vui_params.aspect_ratio_info_present_flag = 1;
//		vd->sei_vui_buffer->vui_params.overscan_info_present_flag = 1;
//		vd->sei_vui_buffer->vui_params.video_signal_type_present_flag = 1;
//		vd->sei_vui_buffer->vui_params.colour_description_present_flag = 1;
//		vd->sei_vui_buffer->vui_params.chroma_location_info_present_flag = 1;
//		vd->sei_vui_buffer->vui_params.timing_info_present_flag = 1;
//		vd->sei_vui_buffer->vui_params.nal_hrd_parameters_present_flag = 1;
//		vd->sei_vui_buffer->vui_params.vcl_hrd_parameters_present_flag = 1;
//		vd->sei_vui_buffer->vui_params.bitstream_restriction_flag = 1;
//		vd->sei_vui_buffer->vui_params. = 1;
//		vd->sei_vui_buffer->
//		vd->sei_vui_buffer->
//		vd->sei_vui_buffer->
		
	}
#else
#if 0
	if(vd->vdec2DynParams.mbErrorBufFlag)
	{
		if(XDM_YUV_420P == vd->vdec2Params.viddecParams.forceChromaFormat)
                        memset(vd->outBufDesc.bufs[3], 0x00,vd->outBufDesc.bufSizes[3]);
                else if(XDM_YUV_422ILE == vd->vdec2Params.viddecParams.forceChromaFormat)
			memset(vd->outBufDesc.bufs[1], 0x00,vd->outBufDesc.bufSizes[1]);
        }
	else
	{
		if(XDM_YUV_420P == vd->vdec2Params.viddecParams.forceChromaFormat)
		{
			vd->outBufDesc.bufs[3] = NULL;
			vd->outBufDesc.bufSizes[3] = 0;
		}
		else if(XDM_YUV_422ILE == vd->vdec2Params.viddecParams.forceChromaFormat)
		{
			vd->outBufDesc.bufs[1] = NULL;
			vd->outBufDesc.bufSizes[1] = 0;
		}
	}
        
	if(vd->vdec2DynParams.Sei_Vui_parse_flag)
	{
		vd->outBufDesc.numBufs += 1;
		if(XDM_YUV_420P == vd->vdec2Params.viddecParams.forceChromaFormat)
		{
			vd->outBufDesc.bufs[4] = (XDAS_Int8 *)vd->sei_vui_buffer;
			vd->outBufDesc.bufSizes[4] = sizeof(sSeiVuiParams_t);
		}
		else if(XDM_YUV_422ILE == vd->vdec2Params.viddecParams.forceChromaFormat)
		{
			vd->outBufDesc.bufs[2] = (XDAS_Int8 *)vd->sei_vui_buffer;
			vd->outBufDesc.bufSizes[2] = sizeof(sSeiVuiParams_t);
		}
        }
#endif	
#endif	
	
}

DvevmStRetCode
dvtb_h264Dec2Decode(DvevmStH264Dec2Info *vd, int *decDuration)
{
	int status = -1;
	DvevmStTime timeStmpBfrDec, timeStmpAftrDec;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(vd != NULL);
	ASSERT(vd->vdec2Hdl != NULL);

	vd->skipFrame = DVEVM_ST_FALSE;
	
	dvtb_h264UpdateSEIVUIBuffers(vd);
	
	timeStmpBfrDec = dvtb_getTime( );
	status = VIDDEC2_process(vd->vdec2Hdl, &vd->inBufDesc, &vd->outBufDesc,(VIDDEC2_InArgs *)&vd->vdec2InArgs,(VIDDEC2_OutArgs *)&vd->vdec2OutArgs);
	timeStmpAftrDec = dvtb_getTime( );
	*decDuration = ((timeStmpAftrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrDec.tv_usec) - ((timeStmpBfrDec.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrDec.tv_usec);

	if (status != VIDDEC2_EOK)
	{
		SYS_ERROR("Video Decode Process Failed (%d)\n", (int) status);
		vd->vdec2Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_h264Dec2Control(vd))
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
#if 0
	if(vd->vdec2DynParams.Sei_Vui_parse_flag)
	{
		if(XDM_YUV_420P == vd->vdec2Params.viddecParams.forceChromaFormat)
		{
				vd->outBufDesc.bufs[4] = NULL;
				vd->outBufDesc.bufSizes[4] = 0;
		}
		else if(XDM_YUV_422ILE == vd->vdec2Params.viddecParams.forceChromaFormat)
		{
				vd->outBufDesc.bufs[2] = NULL;
				vd->outBufDesc.bufSizes[2] = 0;
		}
	}
#endif
	return retCode;
}

DvevmStRetCode
dvtb_h264Dec2Control(DvevmStH264Dec2Info *vd)
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
			do
			{
				vd->inBuf.numBufs = vd->vdec2Status.viddecStatus.bufInfo.minNumInBufs;
				for (i = 0; i < vd->inBuf.numBufs; i++)
					vd->inBuf.bufSizes[i] = vd->vdec2Status.viddecStatus.bufInfo.minInBufSize[i];

#if 0
#if 1
				if(vd->vdec2DynParams.Sei_Vui_parse_flag)
				{
					vd->vdec2Status.viddecStatus.bufInfo.minNumOutBufs -= 1;
//					vd->vdec2Status.viddecStatus.bufInfo.minOutBufSize[vd->vdec2Status.viddecStatus.bufInfo.minNumOutBufs] = 0;
					if(DVEVM_ST_FAIL ==  dvtb_allocSingleBufCmem((char **)&vd->sei_vui_buffer,sizeof(sSeiVuiParams_t)) )
					{
						SYS_ERROR("Unable to allocate memory for sei_vui_buffer of size %d \n",sizeof(sSeiVuiParams_t));
						retCode = DVEVM_ST_FAIL;
						break;
					}
					memset(vd->sei_vui_buffer, 0x00, sizeof(sSeiVuiParams_t));
				}
#else
				if(vd->vdec2DynParams.Sei_Vui_parse_flag)
				{
	
					vd->vdec2Status.viddecStatus.bufInfo.minOutBufSize[vd->vdec2Status.viddecStatus.bufInfo.minNumOutBufs-1] = sizeof(sSeiVuiParams_t);
				}
#endif
#endif
				vd->outBuf.numBufs = vd->vdec2Status.viddecStatus.bufInfo.minNumOutBufs;
				for (i = 0; i < vd->outBuf.numBufs; i++)
				{
					vd->outBuf.bufSizes[i] = vd->vdec2Status.viddecStatus.bufInfo.minOutBufSize[i];
					
				}
				dvtb_h264Dec2ControlDebug(&vd->vdec2Status);
			}while(0);
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_h264Dec2Close(DvevmStH264Dec2Info *vd)
{
	dvtb_h264Dec2Cleanup(vd);
	return DVEVM_ST_SUCCESS;
}

