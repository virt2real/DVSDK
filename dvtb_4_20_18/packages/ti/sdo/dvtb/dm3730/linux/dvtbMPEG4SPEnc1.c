/*
 * dvtbMPEG4SPEnc1.c
 *
 * XDM1.0 MPEG4 SP Encode Interface implementation
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

#include "dvtbMPEG4SPEnc1.h"
#include "dvtbMemory.h"

static XDAS_Int32 outBufSize[XDM_MAX_IO_BUFFERS];
#define STATUSBUFSIZE 1024
void
dvtb_mpeg4spEncInitDebug(IMPEG4VENC_Params *vep)
{

	SYS_DEBUG("\n<======== MPEG4SP Encoder Initialize Debug Start ==========>\n");
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
	SYS_DEBUG("\n<======== MPEG4SP Encoder Initialize Debug End ============>\n\n");

}


void
dvtb_mpeg4spEncProcessDebug(IMPEG4VENC_OutArgs *veo)
{

	SYS_DEBUG("\n<======== MPEG4SP Encoder Process Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) veo->videncOutArgs.extendedError);
	SYS_DEBUG("Bytes Generated    : %d\n", (int) veo->videncOutArgs.bytesGenerated);
	SYS_DEBUG("Encoded Frame Type : %d\n", (int) veo->videncOutArgs.encodedFrameType);
	SYS_DEBUG("Input Frame Skip   : %d\n", (int) veo->videncOutArgs.inputFrameSkip);
	SYS_DEBUG("\n<======== MPEG4SP Encoder Process Debug End ============>\n");

}

void
dvtb_mpeg4spEncControlDebug(IMPEG4VENC_Status *ves)
{

	int i = 0;

	SYS_DEBUG("\n<======== MPEG4SP Encoder Control Debug Start ==========>\n");
	SYS_DEBUG("Extended Error     : %d\n", (int) ves->videncStatus.extendedError);
	SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ves->videncStatus.bufInfo.minNumInBufs);
	SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ves->videncStatus.bufInfo.minNumOutBufs);

	for (i = 0; i < ves->videncStatus.bufInfo.minNumInBufs; i++)
		SYS_DEBUG("BUF-Min In Size  [%d]  : %d\n", i, (int) ves->videncStatus.bufInfo.minInBufSize[i]);

	for (i = 0; i < ves->videncStatus.bufInfo.minNumOutBufs; i++)
		SYS_DEBUG("BUF-Min Out Size  [%d] : %d\n", i,
				(int) ves->videncStatus.bufInfo.minOutBufSize[i]);

	SYS_DEBUG("\n<======== MPEG4SP Encoder Control Debug End ============>\n");

}

void
dvtb_mpeg4spEncCleanup(DvevmStMPEG4SPVEncInfo *ve)
{
	if (NULL != ve->venc1Hdl) {
		VIDENC1_delete(ve->venc1Hdl);
		ve->venc1Hdl = NULL;
	}

}
DvevmStRetCode
dvtb_mpeg4spEnc1ExtControl(DvevmStMPEG4SPVEncInfo *ve, int Cmd)
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
dvtb_mpeg4spEnc1SetRCOpt(DvevmStMPEG4SPVEncInfo *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	impeg4venc_ext_rc_otp_t rcOpt_param;
	int Cmd;

	Cmd = IMPEG4VENC_GET_RC_OTP_PRMS;	      
	if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1ExtControl(ve,Cmd))
	{
		SYS_ERROR("Unable to get RC OPT Params \n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		memcpy(&rcOpt_param, ve->venc1Status.videncStatus.data.buf, sizeof(impeg4venc_ext_rc_otp_t));
		memcpy(&ve->venc1DynParams.s_ext.i4_dyn_param[0], &ve->rcOptParams, sizeof(impeg4venc_ext_rc_otp_t));

		Cmd = IMPEG4VENC_SET_RC_OTP_PRMS;
		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1ExtControl(ve,Cmd))
		{
			SYS_ERROR("Unable to set RC OPT Params \n");
			retCode = DVEVM_ST_FAIL;
		}		
	}

	return retCode;
	
}

DvevmStRetCode
dvtb_mpeg4spEnc1SetCBR(DvevmStMPEG4SPVEncInfo *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	impeg4venc_ext_cbr_params_t cbr_param;
	int Cmd;

	Cmd = IMPEG4VENC_GET_CBR_PARAMS;
	if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1ExtControl(ve,Cmd))
	{
		SYS_ERROR("Unable to get CBR Params \n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		memcpy(&cbr_param, ve->venc1Status.videncStatus.data.buf, sizeof(impeg4venc_ext_cbr_params_t));
		memcpy(&ve->venc1DynParams.s_ext.i4_dyn_param[0], &ve->cbrParams, sizeof(impeg4venc_ext_cbr_params_t));

		ve->venc1Cmd = IMPEG4VENC_SET_CBR_PARAMS;
		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1ExtControl(ve,Cmd))
		{
			SYS_ERROR("Unable to set CBR PArams \n");
			retCode = DVEVM_ST_FAIL;
		}		
	}

	return retCode;
	
}
DvevmStRetCode
dvtb_mpeg4spEnc1SetVBR(DvevmStMPEG4SPVEncInfo *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	impeg4venc_ext_vbr_params_t vbr_param;
	int Cmd;

	Cmd = IMPEG4VENC_GET_VBR_PARAMS;
	if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1ExtControl(ve,Cmd))
	{
		SYS_ERROR("Unable to get VBR Params \n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		memcpy(&vbr_param, ve->venc1Status.videncStatus.data.buf, sizeof(impeg4venc_ext_vbr_params_t));
		memcpy(&ve->venc1DynParams.s_ext.i4_dyn_param[0], &ve->vbrParams, sizeof(impeg4venc_ext_vbr_params_t));

		Cmd = IMPEG4VENC_SET_VBR_PARAMS;
		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1ExtControl(ve,Cmd))
		{
			SYS_ERROR("Unable to set VBR Params \n");
			retCode = DVEVM_ST_FAIL;
		}		
	}

	return retCode;
	
}

DvevmStRetCode
dvtb_mpeg4spEnc1SetIIR(DvevmStMPEG4SPVEncInfo *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	impeg4venc_ext_iir_params_t iir_param;
	int Cmd;

	Cmd = IMPEG4VENC_GET_IIR_PARAMS;
	if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1ExtControl(ve,Cmd))
	{
		SYS_ERROR("Unable to get IIR PArams \n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		memcpy(&iir_param, ve->venc1Status.videncStatus.data.buf, sizeof(impeg4venc_ext_iir_params_t));
		memcpy(&ve->venc1DynParams.s_ext.i4_dyn_param[0], &ve->iirParams, sizeof(impeg4venc_ext_iir_params_t));

		Cmd = IMPEG4VENC_SET_IIR_PARAMS;
		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1ExtControl(ve,Cmd))
		{
			SYS_ERROR("Unable to set IIR PArams \n");
			retCode = DVEVM_ST_FAIL;
		}		
	}

	return retCode;
	
}

DvevmStRetCode
dvtb_mpeg4spEnc1Init(DvevmStMPEG4SPVEncInfo *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);
	ASSERT(ve->venc1Name[0] != 0);

	ve->outBufDesc.bufSizes = (XDAS_Int32 *) outBufSize;
	ve->venc1Status.videncStatus.data.buf = NULL;	

	if (NULL == (ve->venc1Hdl = VIDENC1_create(ve->ceHdl, ve->venc1Name, (IVIDENC1_Params *) &ve->venc1Params)))
	{
		SYS_ERROR("Unable to initialize MPEG4SP Encoder\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Encoder initialised\n");	
		dvtb_mpeg4spEncInitDebug(&ve->venc1Params);
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

	        	if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Control(ve))
	        	{
	        		SYS_ERROR("Unable to set encoder dynamic parameters\n");
        			retCode = DVEVM_ST_FAIL;
        		}
        		else
        		{
				
				if(ve->venc1Params.s_ext.i4_coding_tools1 & 0x01)
				{
					if(DVEVM_ST_FAIL == dvtb_mpeg4spEnc1SetIIR(ve))
					{
						SYS_ERROR("Unable to set IIR \n");
						retCode = DVEVM_ST_FAIL;
					}
				}
				if(DVEVM_ST_FAIL != retCode)
				{
					switch(ve->venc1Params.videncParams.rateControlPreset)
					{
						case IVIDEO_STORAGE:
							if(DVEVM_ST_FAIL == dvtb_mpeg4spEnc1SetRCOpt(ve))
							{
								retCode = DVEVM_ST_FAIL;
							}
							else if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1SetVBR(ve))
							{
								retCode = DVEVM_ST_FAIL;
							}
							break;
						case IVIDEO_NONE:
							if(DVEVM_ST_FAIL == dvtb_mpeg4spEnc1SetRCOpt(ve))
							{
								retCode = DVEVM_ST_FAIL;
							}
							break;
						case IVIDEO_USER_DEFINED:
							if(DVEVM_ST_FAIL == dvtb_mpeg4spEnc1SetRCOpt(ve))
							{
								retCode = DVEVM_ST_FAIL;
							}
							else if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1SetCBR(ve))
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
							
	if(DVEVM_ST_FAIL != retCode)
	{
		ve->venc1Cmd = XDM_GETBUFINFO;
		if (DVEVM_ST_FAIL == dvtb_mpeg4spEnc1Control(ve))
		{
			SYS_ERROR("Unable to get buffer information\n");
			retCode = DVEVM_ST_FAIL;
		}
	}

	if(DVEVM_ST_FAIL == retCode)
		dvtb_mpeg4spEncCleanup(ve);

	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spEnc1Encode(DvevmStMPEG4SPVEncInfo *ve, int *encDuration)
{
	XDAS_Int32 status = -1;
	DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);
	ASSERT(ve->venc1Hdl != NULL);
	ASSERT(ve->inBufDesc.numBufs > 0);
	ASSERT(ve->outBufDesc.numBufs > 0);

	ve->venc1InArgs.videncInArgs.inputID = 1;
	ve->venc1InArgs.videncInArgs.size = sizeof(ve->venc1InArgs);
	ve->venc1InArgs.s_ext.i4_size  = sizeof(impeg4venc_ext_inargs_t);
        SYS_DEBUG("size                :%d \n",ve->venc1InArgs.videncInArgs.size);
        SYS_DEBUG("inputID             :%d \n",ve->venc1InArgs.videncInArgs.inputID);
        SYS_DEBUG("topFieldFirstFlag   :%d \n",ve->venc1InArgs.videncInArgs.topFieldFirstFlag);
        SYS_DEBUG("i4_size             :%d \n",ve->venc1InArgs.s_ext.i4_size);
        SYS_DEBUG("i4_delta_time_stamp :%d \n",ve->venc1InArgs.s_ext.i4_delta_time_stamp);

	ve->venc1OutArgs.videncOutArgs.size = sizeof(ve->venc1OutArgs);

	timeStmpBfrEnc = dvtb_getTime();

	status = VIDENC1_process(ve->venc1Hdl, &(ve->inBufDesc), &(ve->outBufDesc), (IVIDENC1_InArgs *) &(ve->venc1InArgs), (IVIDENC1_OutArgs *) &(ve->venc1OutArgs));

	timeStmpAftrEnc = dvtb_getTime();

	*encDuration = ((timeStmpAftrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpAftrEnc.tv_usec) - ((timeStmpBfrEnc.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrEnc.tv_usec);

	if (status != VIDENC1_EOK)
	{
		SYS_ERROR("MPEG4SP Encode Process failed (%d), Codec Error : %d\n",(int) status, (int) ve->venc1OutArgs.videncOutArgs.extendedError);
		
                if((1 << XDM_FATALERROR ) & ve->venc1OutArgs.videncOutArgs.extendedError )
                {
                        SYS_ERROR("Fatal Error \n");
			retCode = DVEVM_ST_FAIL;
                }
		else
		{
			 SYS_ERROR("NON FATAL Error  \n");
		}
	}

	if(DVEVM_ST_FAIL != retCode)
		dvtb_mpeg4spEncProcessDebug(&ve->venc1OutArgs);
	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spEnc1Control(DvevmStMPEG4SPVEncInfo *ve)
{
	int status = -1, i = 0,processTime = 0;
	DvevmStTime timeStmpBfrCtrl, timeStmpAftrCtrl;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(ve != NULL);
	ASSERT(ve->ceHdl != NULL);

	timeStmpBfrCtrl = dvtb_getTime();

	status = VIDENC1_control(ve->venc1Hdl, ve->venc1Cmd, (IVIDENC1_DynamicParams *) &ve->venc1DynParams, (IVIDENC1_Status *) &ve->venc1Status);

	timeStmpAftrCtrl = dvtb_getTime();

	processTime = ((timeStmpAftrCtrl.tv_sec * NUM_MICROSECS_IN_SEC)	+ timeStmpAftrCtrl.tv_usec) - ((timeStmpBfrCtrl.tv_sec * NUM_MICROSECS_IN_SEC) + timeStmpBfrCtrl.tv_usec);

	if (VIDENC1_EOK != status)
	{
		SYS_ERROR("Error (%d), Codec Error (%d) in MPEG4SP Encoder Control\n", status, (int) ve->venc1Status.videncStatus.extendedError);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		if (XDM_SETPARAMS == ve->venc1Cmd)
		{
			SYS_DEBUG("MPEG4SP Encode Control => Command : %d\n", ve->venc1Cmd);
			SYS_DEBUG("Input Height     : %d\n", (int) ve->venc1DynParams.videncDynamicParams.inputHeight);
			SYS_DEBUG("Input Width      : %d\n", (int) ve->venc1DynParams.videncDynamicParams.inputWidth);
			SYS_DEBUG("Ref Frame Rate   : %d\n", (int) ve->venc1DynParams.videncDynamicParams.refFrameRate);
			SYS_DEBUG("Tgt Frame Rate   : %d\n", (int) ve->venc1DynParams.videncDynamicParams.targetFrameRate);
			SYS_DEBUG("Target Bit Rate  : %d\n", (int) ve->venc1DynParams.videncDynamicParams.targetBitRate);
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
		}
	}

	if(DVEVM_ST_FAIL != retCode)
		dvtb_mpeg4spEncControlDebug(&ve->venc1Status);

	return retCode;
}

DvevmStRetCode
dvtb_mpeg4spEnc1Close(DvevmStMPEG4SPVEncInfo *ve)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	/* free buffers */
	if (ve->inBuf.numBufs > 0)
	{
		dvtb_freeCmem(&ve->inBuf);
	}

	if (ve->outBuf.numBufs > 0)
	{
		dvtb_freeCmem(&ve->outBuf);
	}
	
	dvtb_mpeg4spEncCleanup(ve);

	if(ve->venc1Status.videncStatus.data.buf != NULL)
	{
		dvtb_freeSingleBufCmem(ve->venc1Status.videncStatus.data.buf, ve->venc1Status.videncStatus.data.bufSize);
		ve->venc1Status.videncStatus.data.buf = NULL;	
	}

	return retCode;
}


