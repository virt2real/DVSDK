/*
 * dvtbH264Enc1.c
 *
 * XDM1.0 H264 Encode Interface implementation
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

#include "dvtbH264Enc1.h"
#include "dvtbMemory.h"
#define STATUSBUFSIZE 1024
void
dvtb_h264Enc1XDM1SingleBufDescDebug(XDM1_SingleBufDesc *sbd)
{
	SYS_DEBUG("\tbuf                   : %x\n", (int) sbd->buf);
	SYS_DEBUG("\tbufSize               : %d\n", (int) sbd->bufSize);
	SYS_DEBUG("\taccessMask            : %d\n", (int) sbd->accessMask);
}

void
dvtb_h264Enc1IVIDEO1_BufDescDebug(IVIDEO1_BufDesc *bd)
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
		dvtb_h264Enc1XDM1SingleBufDescDebug(&bd->bufDesc[i]);
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
dvtb_h264Enc1InitDebug(IH264VENC_Params *vep)
{
	SYS_DEBUG("\n<======== H264 Encoder Params Debug Start ==========>\n");
	SYS_DEBUG("Encoding Preset    : %d\n", (int) vep->videncParams.encodingPreset);
	SYS_DEBUG("Rate Ctrl Preset   : %d\n", (int) vep->videncParams.rateControlPreset);
	SYS_DEBUG("Max Height         : %d\n", (int) vep->videncParams.maxHeight);
	SYS_DEBUG("Max Width          : %d\n", (int) vep->videncParams.maxWidth);
	SYS_DEBUG("Max Frame Rate     : %d\n", (int) vep->videncParams.maxFrameRate);
	SYS_DEBUG("Max Bit Rate       : %d\n", (int) vep->videncParams.maxBitRate);
	SYS_DEBUG("Endianness         : %d\n", (int) vep->videncParams.dataEndianness);
	SYS_DEBUG("Max Inter Frame    : %d\n", (int) vep->videncParams.maxInterFrameInterval);
	SYS_DEBUG("Input Chroma Fmt   : %d\n", (int) vep->videncParams.inputChromaFormat);
	SYS_DEBUG("Input Content      : %d\n", (int) vep->videncParams.inputContentType);

	SYS_DEBUG("i4_size            : %d\n", (int) vep->s_ext.i4_size);
	SYS_DEBUG("i4_dsp_processing1 : %d\n", (int) vep->s_ext.i4_dsp_processing1);
	SYS_DEBUG("i4_dsp_processing2 : %d\n", (int) vep->s_ext.i4_dsp_processing2);
	SYS_DEBUG("i4_coding_tools1   : %d\n", (int) vep->s_ext.i4_coding_tools1);
	SYS_DEBUG("i4_coding_tools2   : %d\n", (int) vep->s_ext.i4_coding_tools2);
	SYS_DEBUG("i4_min_tgt_dimensions_xy : %d\n", (int) vep->s_ext.i4_min_tgt_dimensions_xy);
	SYS_DEBUG("i4_max_search_range_xy   : %d\n", (int) vep->s_ext.i4_max_search_range_xy);
	SYS_DEBUG("\n<======== H264 Encoder Params Debug End ============>\n\n");
}

void
dvtb_h264Enc1InArgsDebug(IH264VENC_InArgs *vei)
{
	SYS_DEBUG("\n<======== Video Encoder InArgs Debug Start ==========>\n");
	SYS_DEBUG("Size                 : %d\n", (int) vei->videncInArgs.size);
	SYS_DEBUG("inputID              : %d\n", (int) vei->videncInArgs.inputID);
	SYS_DEBUG("topFieldFirstFlag    : %d\n", (int) vei->videncInArgs.topFieldFirstFlag);
	SYS_DEBUG("\n<======== Video Encoder InArgs Debug End ============>\n");
}

void
dvtb_h264Enc1ProcessDebug(IH264VENC_OutArgs *veo)
{
	SYS_DEBUG("\n<======== Video Encoder OutArgs Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) veo->videncOutArgs.extendedError);
	SYS_DEBUG("Bytes Generated    : %d\n", (int) veo->videncOutArgs.bytesGenerated);
	SYS_DEBUG("Encoded Frame Type : %d\n", (int) veo->videncOutArgs.encodedFrameType);
	SYS_DEBUG("Input Frame Skip   : %d\n", (int) veo->videncOutArgs.inputFrameSkip);
	SYS_DEBUG("Output ID 		: %d\n", (int) veo->videncOutArgs.outputID);

	//XDM1_SingleBufDesc encodedBuf;
	SYS_DEBUG("encodedBuf            :\n");
	dvtb_h264Enc1XDM1SingleBufDescDebug(&veo->videncOutArgs.encodedBuf);

	//IVIDEO1_BufDesc reconBufs;
	SYS_DEBUG("reconBufs          :\n");
	dvtb_h264Enc1IVIDEO1_BufDescDebug(&veo->videncOutArgs.reconBufs);

	SYS_DEBUG("\n<======== Video Encoder OutArgs Debug End ============>\n");
}

void
dvtb_h264Enc1Cleanup(DvevmStH264Enc1Info *ve)
{
	if (NULL != ve->venc1Hdl)
	{
		VIDENC1_delete(ve->venc1Hdl);
		ve->venc1Hdl = NULL;
	}
}

DvevmStRetCode
dvtb_h264Enc1ExtControl(DvevmStH264Enc1Info *ve, int Cmd)
{
	int status = -1, processTime = 0;
	DvevmStTime timeStmpBfrCtrl, timeStmpAftrCtrl;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);

	timeStmpBfrCtrl = dvtb_getTime();

	status = VIDENC1_control(ve->venc1Hdl, Cmd, (IVIDENC1_DynamicParams *) &ve->venc1DynParams, (IVIDENC1_Status *) &ve->venc1Status);

	timeStmpAftrCtrl = dvtb_getTime();

	processTime = ((timeStmpAftrCtrl.tv_sec * NUM_MICROSECS_IN_SEC)	+ timeStmpAftrCtrl.tv_usec) - ((timeStmpBfrCtrl.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrCtrl.tv_usec);

	if (VIDENC1_EOK != status)
	{
		SYS_ERROR("Error (%d), Codec Error (%d) in MPEG4SP Encoder Control\n", status, (int) ve->venc1Status.videncStatus.extendedError);
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}


DvevmStRetCode
dvtb_h264Enc1SetRCOpt(DvevmStH264Enc1Info *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	ih264venc_ext_rc_otp_t rcOpt_param;
	int Cmd;

	Cmd = IH264VENC_GET_RC_OTP_PRMS;	      
	if (DVEVM_ST_FAIL == dvtb_h264Enc1ExtControl(ve,Cmd))
	{
		SYS_ERROR("Unable to get RC OPT Params \n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		memcpy(&rcOpt_param, ve->venc1Status.videncStatus.data.buf, sizeof(ih264venc_ext_rc_otp_t));
		memcpy(&ve->venc1DynParams.s_ext.i4_dyn_param[0], &ve->rcOptParams, sizeof(ih264venc_ext_rc_otp_t));

		Cmd = IH264VENC_SET_RC_OTP_PRMS;
		if (DVEVM_ST_FAIL == dvtb_h264Enc1ExtControl(ve,Cmd))
		{
			SYS_ERROR("Unable to set RC OPT Params \n");
			retCode = DVEVM_ST_FAIL;
		}		
	}

	return retCode;
	
}

DvevmStRetCode
dvtb_h264Enc1SetVUIOpt(DvevmStH264Enc1Info *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	ih264venc_ext_vui_otp_t vuiOpt_param;
	int Cmd;

	Cmd = IH264VENC_OTP_GET_VUI_PARAMS;	      
	if (DVEVM_ST_FAIL == dvtb_h264Enc1ExtControl(ve,Cmd))
	{
		SYS_ERROR("Unable to get VUI OPT Params \n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		memcpy(&vuiOpt_param, ve->venc1Status.videncStatus.data.buf, sizeof(ih264venc_ext_vui_otp_t));
		memcpy(&ve->venc1DynParams.s_ext.i4_dyn_param[0], &ve->vuiOptParams, sizeof(ih264venc_ext_vui_otp_t));

		Cmd = IH264VENC_OTP_SET_VUI_PARAMS;
		if (DVEVM_ST_FAIL == dvtb_h264Enc1ExtControl(ve,Cmd))
		{
			SYS_ERROR("Unable to set VUI OPT Params \n");
			retCode = DVEVM_ST_FAIL;
		}		
	}

	return retCode;
	
}

DvevmStRetCode
dvtb_h264Enc1SetCBR(DvevmStH264Enc1Info *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	ih264venc_ext_cbr_params_t cbr_param;
	int Cmd;

	Cmd = IH264VENC_GET_CBR_PARAMS;
	if (DVEVM_ST_FAIL == dvtb_h264Enc1ExtControl(ve,Cmd))
	{
		SYS_ERROR("Unable to get CBR Params \n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		memcpy(&cbr_param, ve->venc1Status.videncStatus.data.buf, sizeof(ih264venc_ext_cbr_params_t));
		memcpy(&ve->venc1DynParams.s_ext.i4_dyn_param[0], &ve->cbrParams, sizeof(ih264venc_ext_cbr_params_t));

		ve->venc1Cmd = IH264VENC_SET_CBR_PARAMS;
		if (DVEVM_ST_FAIL == dvtb_h264Enc1ExtControl(ve,Cmd))
		{
			SYS_ERROR("Unable to set CBR PArams \n");
			retCode = DVEVM_ST_FAIL;
		}		
	}

	return retCode;
	
}

DvevmStRetCode
dvtb_h264Enc1SetVBR(DvevmStH264Enc1Info *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	ih264venc_ext_vbr_params_t vbr_param;
	int Cmd;

	Cmd = IH264VENC_GET_VBR_PARAMS;
	if (DVEVM_ST_FAIL == dvtb_h264Enc1ExtControl(ve,Cmd))
	{
		SYS_ERROR("Unable to get VBR Params \n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		memcpy(&vbr_param, ve->venc1Status.videncStatus.data.buf, sizeof(ih264venc_ext_vbr_params_t));
		memcpy(&ve->venc1DynParams.s_ext.i4_dyn_param[0], &ve->vbrParams, sizeof(ih264venc_ext_vbr_params_t));

		Cmd = IH264VENC_SET_VBR_PARAMS;
		if (DVEVM_ST_FAIL == dvtb_h264Enc1ExtControl(ve,Cmd))
		{
			SYS_ERROR("Unable to set VBR Params \n");
			retCode = DVEVM_ST_FAIL;
		}		
	}

	return retCode;
}

DvevmStRetCode
dvtb_h264Enc1SetIIR(DvevmStH264Enc1Info *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	ih264venc_ext_iir_params_t iir_param;
	int Cmd;

	Cmd = IH264VENC_GET_IIR_PARAMS;
	if (DVEVM_ST_FAIL == dvtb_h264Enc1ExtControl(ve,Cmd))
	{
		SYS_ERROR("Unable to get IIR PArams \n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		memcpy(&iir_param, ve->venc1Status.videncStatus.data.buf, sizeof(ih264venc_ext_iir_params_t));
		memcpy(&ve->venc1DynParams.s_ext.i4_dyn_param[0], &ve->iirParams, sizeof(ih264venc_ext_iir_params_t));

		Cmd = IH264VENC_SET_IIR_PARAMS;
		if (DVEVM_ST_FAIL == dvtb_h264Enc1ExtControl(ve,Cmd))
		{
			SYS_ERROR("Unable to set IIR PArams \n");
			retCode = DVEVM_ST_FAIL;
		}		
	}

	return retCode;
	
}
DvevmStRetCode
dvtb_h264Enc1Init(DvevmStH264Enc1Info *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);
	ASSERT(ve->venc1Name[0] != 0);


	ve->venc1Status.videncStatus.data.buf = NULL;	

	dvtb_h264Enc1InitDebug(&ve->venc1Params);
	if (NULL == (ve->venc1Hdl = VIDENC1_create(ve->ceHdl, ve->venc1Name, (IVIDENC1_Params *) (&ve->venc1Params))))
	{
		dvtb_h264Enc1InitDebug(&ve->venc1Params);
		SYS_ERROR("Unable to initialize Video Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		ve->venc1Cmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_h264Enc1Control(ve))
		{
			SYS_ERROR("Unable to get status \n");
			retCode = DVEVM_ST_FAIL;
		}
		else
		{
			
			//Allocate buffer for status
			if(DVEVM_ST_SUCCESS !=  dvtb_allocSingleBufCmem( &ve->venc1Status.videncStatus.data.buf ,STATUSBUFSIZE))
			{
				SYS_ERROR("Unable to allocate videncStatus.data.buf of size %d \n",STATUSBUFSIZE);
				ve->venc1Status.videncStatus.data.buf = NULL;
				retCode = DVEVM_ST_FAIL;
			}	
			else
			{		
				ve->venc1Status.videncStatus.data.bufSize = STATUSBUFSIZE;

				ve->venc1Cmd = XDM_SETPARAMS;
				if (DVEVM_ST_FAIL == dvtb_h264Enc1Control(ve))
				{
					SYS_ERROR("Unable to set encoder dynamic parameters\n");
					retCode = DVEVM_ST_FAIL;
				}
				else
				{
		
					if(ve->venc1Params.s_ext.i4_coding_tools1 & 0x08)
					{
						if(DVEVM_ST_FAIL == dvtb_h264Enc1SetIIR(ve))
						{
							SYS_ERROR("Unable to set IIR \n");
							retCode = DVEVM_ST_FAIL;
						}
					}
					if(ve->venc1Params.s_ext.i4_coding_tools1 & 0x10)
					{
						if(DVEVM_ST_FAIL == dvtb_h264Enc1SetVUIOpt(ve))
						{
							SYS_ERROR("Unable to set VUI \n");
							retCode = DVEVM_ST_FAIL;
						}
					}
					printf("%d %d \n",ve->venc1Params.s_ext.i4_coding_tools1 & 0x08 , ve->venc1Params.s_ext.i4_coding_tools1 & 0x10);
					if(DVEVM_ST_FAIL != retCode)
					{
						switch(ve->venc1Params.videncParams.rateControlPreset)
						{
							case IVIDEO_STORAGE:
								if(DVEVM_ST_FAIL == dvtb_h264Enc1SetRCOpt(ve))
								{
									retCode = DVEVM_ST_FAIL;
								}
								else if (DVEVM_ST_FAIL == dvtb_h264Enc1SetVBR(ve))
								{
									retCode = DVEVM_ST_FAIL;
								}
								break;
							case IVIDEO_NONE:
								if(DVEVM_ST_FAIL == dvtb_h264Enc1SetRCOpt(ve))
								{
									retCode = DVEVM_ST_FAIL;
								}
								break;
							case IVIDEO_USER_DEFINED:
								if(DVEVM_ST_FAIL == dvtb_h264Enc1SetRCOpt(ve))
								{
									retCode = DVEVM_ST_FAIL;
								}
								else if (DVEVM_ST_FAIL == dvtb_h264Enc1SetCBR(ve))
								{
									retCode = DVEVM_ST_FAIL;
								}
								break;
							default:
								SYS_ERROR("Rae control preset %d is not supported \n",ve->venc1Params.videncParams.rateControlPreset);
								retCode = DVEVM_ST_FAIL;
						}
					}	
				}
			}
		}
	}


	if(DVEVM_ST_FAIL != retCode)
	{
		ve->venc1Cmd = XDM_GETBUFINFO;
		if (DVEVM_ST_FAIL == dvtb_h264Enc1Control(ve))
		{
			SYS_ERROR("Unable to get encoder buffer requirements\n");
			retCode = DVEVM_ST_FAIL;
		}
	}
	
	if(DVEVM_ST_FAIL == retCode)
		dvtb_h264Enc1Cleanup(ve);

	return retCode;
}

DvevmStRetCode
dvtb_h264Enc1Encode(DvevmStH264Enc1Info *ve, int* encDuration)
{
	XDAS_Int32 status = -1;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);
	ASSERT(ve->venc1Hdl != NULL);

	ve->venc1InArgs.videncInArgs.inputID = 1;
	ve->venc1InArgs.videncInArgs.size = sizeof(ve->venc1InArgs);
	ve->venc1InArgs.s_ext.i4_size  = sizeof(ih264venc_ext_inargs_t);
	ve->venc1OutArgs.videncOutArgs.size = sizeof(ve->venc1OutArgs);

	timeStmpBfrEnc = dvtb_getTime( );
	status = VIDENC1_process(ve->venc1Hdl, &ve->inBufDesc, &ve->outBufDesc, (IVIDENC1_InArgs *) (&ve->venc1InArgs), (IVIDENC1_OutArgs *) (&ve->venc1OutArgs));
	timeStmpAftrEnc = dvtb_getTime( );
	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != VIDENC1_EOK)
	{
		SYS_ERROR("Video Encode Process failed (%d), Codec Error : %d\n", (int) status, (int) ve->venc1OutArgs.videncOutArgs.extendedError);
		retCode = DVEVM_ST_FAIL;
	}

	if (DVEVM_ST_FAIL != retCode)
		dvtb_h264Enc1ProcessDebug(&ve->venc1OutArgs);

	return retCode;
}

DvevmStRetCode
dvtb_h264Enc1Control(DvevmStH264Enc1Info *ve)
{
	int status = -1, i = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);

	status = VIDENC1_control(ve->venc1Hdl, ve->venc1Cmd, (IVIDENC1_DynamicParams *) (&ve->venc1DynParams), (IVIDENC1_Status *) (&ve->venc1Status));
	if (VIDENC1_EOK != status)
	{
		SYS_ERROR("Error (%d), Codec Error (%d) in Video Encoder Control\n", status, (int) ve->venc1Status.videncStatus.extendedError);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		if (XDM_GETBUFINFO == ve->venc1Cmd)
		{
			ve->inBuf.numBufs = ve->venc1Status.videncStatus.bufInfo.minNumInBufs;
			for (i = 0; i < ve->inBuf.numBufs; i++)
				ve->inBuf.bufSizes[i] = ve->venc1Status.videncStatus.bufInfo.minInBufSize[i];

			ve->outBuf.numBufs = ve->venc1Status.videncStatus.bufInfo.minNumOutBufs;
			for (i = 0; i < ve->outBuf.numBufs; i++)
				ve->outBuf.bufSizes[i] = ve->venc1Status.videncStatus.bufInfo.minOutBufSize[i];
				
		}
		else if(XDM_GETSTATUS == ve->venc1Cmd)
		{
			if(ve->venc1Status.videncStatus.extendedError)
			{
				if(XDM_ISFATALERROR(ve->venc1Status.videncStatus.extendedError))
				{
					SYS_ERROR("Exiting: Encode Failed with a Codec fatal error 0x%x.\n", (int) ve->venc1Status.videncStatus.extendedError);
					retCode = DVEVM_ST_FAIL;
				}
				else
					SYS_ERROR("Continue: Codec generated an non fatal error 0x%x.\n", (int) ve->venc1Status.videncStatus.extendedError);
			}
		}
	}

	return retCode;
}

DvevmStRetCode
dvtb_h264Enc1Close(DvevmStH264Enc1Info *ve)
{
	if (ve->inBuf.numBufs > 0)
	{
		dvtb_freeCmem(&ve->inBuf);
	}

	if (ve->outBuf.numBufs > 0)
	{
		dvtb_freeCmem(&ve->outBuf);
	}

	dvtb_h264Enc1Cleanup(ve);
	if(ve->venc1Status.videncStatus.data.buf != NULL)
	{
		dvtb_freeSingleBufCmem(ve->venc1Status.videncStatus.data.buf, ve->venc1Status.videncStatus.data.bufSize);
		ve->venc1Status.videncStatus.data.buf = NULL;	
	}

	return DVEVM_ST_SUCCESS;
}

