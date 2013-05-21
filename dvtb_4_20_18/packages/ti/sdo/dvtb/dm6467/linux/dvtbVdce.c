/*
 * dvtbVdce.c
 *
 * VDCE driver interface implementation
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

#include "dvtbVdce.h"

DvevmStRetCode
dvtb_vdceSetup(DvevmStVdceInfo *vdce, int inputHeight, int inputWidth, int inputPitch, int inFormat)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	ASSERT(vdce);

	vdce->inputHeight = inputHeight;
	vdce->inputWidth  = inputWidth;
	vdce->inputPitch  = inputPitch;
	vdce->inFormat    = inFormat;

	SYS_DEBUG("T->g.vdce.inputHeight = %d, T->g.vdce.inputWidth = %d, T->g.vdce.inputPitch = %d\n", vdce->inputHeight, vdce->inputWidth, vdce->inputPitch);

	if (DVEVM_ST_FAIL == dvtb_vdceopen(vdce))
	{
		SYS_ERROR("Unable to setup VDCE device <%s> for Chrominace Conversion\n", vdce->device);
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		vdce->vdceOpened = DVEVM_ST_TRUE;
		SYS_DEBUG("VDCE device  <%s> initialized \n", vdce->device);
	}

	return retCode;
}

DvevmStRetCode
dvtb_vdceopen(DvevmStVdceInfo *vdce)
{
	ASSERT(vdce != NULL);

	strcpy(vdce->device, VDCE_DEVICE);

	/* Open the VDCE channel */
	vdce->videoFd = open(vdce->device, O_RDWR);
	if (vdce->videoFd <= 0)
	{
		SYS_PERROR("Unable to initialize video device : %s\n", vdce->device);
		vdce->videoFd = -1;
		return DVEVM_ST_FAIL;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_vdceConvert420to422(DvevmStVdceInfo *vdce)
{
	vdce_params_t vdce_params;

	vdce_params.vdce_mode = VDCE_OPERATION_CHROMINANCE_CONVERSION;
	if (ioctl(vdce->videoFd, VDCE_GET_DEFAULT, &vdce_params) < 0)
	{
		SYS_PERROR("Unable to get Default parameters\n");
		return DVEVM_ST_FAIL;
	}

	/* Conversion Mode */
	vdce_params.vdce_mode_params.ccv_params.conversion_type = VDCE_CCV_MODE_420_422;
	vdce_params.common_params.src_hsz_luminance = vdce->inputWidth;
	vdce_params.common_params.src_vsz_luminance = vdce->inputHeight;

	/* Set output size  */
	vdce_params.common_params.dst_hsz_luminance = vdce->inputWidth;
	vdce_params.common_params.dst_vsz_luminance = (vdce->inputHeight > 1080) ? 1080 : vdce->inputHeight;

	/* Set frame type */
	vdce_params.common_params.src_processing_mode = VDCE_PROGRESSIVE;
	vdce_params.common_params.src_mode = VDCE_FRAME_MODE;
	vdce_params.common_params.res_mode = VDCE_FRAME_MODE;

	/* Set the all parameters to VDCE*/
	if (ioctl(vdce->videoFd, VDCE_SET_PARAMS, &vdce_params) < 0)
	{
		SYS_PERROR("Unable to SET params\n");
		return DVEVM_ST_FAIL;
	}

	/* Configuring input buffer */
	vdce->runtime_params.buffers[VDCE_BUF_IN].buf_type = VDCE_BUF_IN;
	vdce->runtime_params.buffers[VDCE_BUF_IN].index = -1;
	vdce->runtime_params.buffers[VDCE_BUF_IN].offset = (int) vdce->inputBuffer;
	vdce->runtime_params.buffers[VDCE_BUF_IN].size = ((vdce->inputHeight * vdce->inputPitch * 3) >> 1);

	/* Configuring output buffer */
	vdce->runtime_params.buffers[VDCE_BUF_OUT].buf_type = VDCE_BUF_OUT;
	vdce->runtime_params.buffers[VDCE_BUF_OUT].index = -1;
	vdce->runtime_params.buffers[VDCE_BUF_OUT].offset = (int) vdce->outputBuffer;
	vdce->runtime_params.buffers[VDCE_BUF_OUT].size = MAX_PITCH * MAX_HEIGHT * 2;

	vdce->runtime_params.src_horz_pitch = vdce->inputPitch;
	vdce->runtime_params.res_horz_pitch = MAX_PITCH;

	if (ioctl(vdce->videoFd, VDCE_START, &vdce->runtime_params) < 0)
	{
		SYS_PERROR("Unable to Start GE\n");
		return DVEVM_ST_FAIL;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_vdceConvert422to420(DvevmStVdceInfo *vdce)
{
	vdce_params_t vdce_params;

	vdce_params.vdce_mode = VDCE_OPERATION_CHROMINANCE_CONVERSION;
	if (ioctl(vdce->videoFd, VDCE_GET_DEFAULT, &vdce_params) < 0)
	{
		SYS_PERROR("Unable to get Default parameters\n");
		return DVEVM_ST_FAIL;
	}

	/* Conversion Mode */
	vdce_params.vdce_mode_params.ccv_params.conversion_type = VDCE_CCV_MODE_422_420;
	vdce_params.common_params.src_hsz_luminance = vdce->inputWidth;
	vdce_params.common_params.src_vsz_luminance = vdce->inputHeight;

	/* Set output size  */
	vdce_params.common_params.dst_hsz_luminance = vdce->inputWidth;
	vdce_params.common_params.dst_vsz_luminance = vdce->inputHeight;

	/* Set frame type */
	vdce_params.common_params.src_processing_mode = VDCE_PROGRESSIVE;
	vdce_params.common_params.src_mode = VDCE_FRAME_MODE;
	vdce_params.common_params.res_mode = VDCE_FRAME_MODE;

	/* Set the all parameters to VDCE*/
	if (ioctl(vdce->videoFd, VDCE_SET_PARAMS, &vdce_params) < 0)
	{
		SYS_PERROR("Unable to SET params\n");
		return DVEVM_ST_FAIL;
	}

	/* Configuring input buffer */
	vdce->runtime_params.buffers[VDCE_BUF_IN].buf_type = VDCE_BUF_IN;
	vdce->runtime_params.buffers[VDCE_BUF_IN].index = -1;
	vdce->runtime_params.buffers[VDCE_BUF_IN].offset = (int) vdce->inputBuffer;
	vdce->runtime_params.buffers[VDCE_BUF_IN].size = MAX_PITCH * MAX_HEIGHT * 2;

	/* Configuring output buffer */
	vdce->runtime_params.buffers[VDCE_BUF_OUT].buf_type = VDCE_BUF_OUT;
	vdce->runtime_params.buffers[VDCE_BUF_OUT].index = -1;
	vdce->runtime_params.buffers[VDCE_BUF_OUT].offset = (int) vdce->outputBuffer;
	vdce->runtime_params.buffers[VDCE_BUF_OUT].size = ((vdce->inputWidth * vdce->inputHeight * 3) >> 1);

	vdce->runtime_params.src_horz_pitch = vdce->inputWidth;
	vdce->runtime_params.res_horz_pitch = vdce->inputWidth;

	if (ioctl(vdce->videoFd, VDCE_START, &vdce->runtime_params) < 0)
	{
		SYS_PERROR("Unable to Start GE\n");
		return DVEVM_ST_FAIL;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_vdceClose(DvevmStVdceInfo *vdce)
{
	close(vdce->videoFd);
	vdce->videoFd = -1;
	return DVEVM_ST_SUCCESS;
}
