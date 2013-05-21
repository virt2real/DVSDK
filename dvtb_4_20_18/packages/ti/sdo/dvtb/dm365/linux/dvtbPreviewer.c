/*
 * dvtbPreviewer.c
 *
 * Preview Interface implementation
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

#include "dvtbPreviewer.h"

DvevmStRetCode
dvtb_previewerSetup(DvtbPreviewerInfo *vpPrvw)
{
	unsigned int oper_mode, user_mode = IMP_MODE_CONTINUOUS;
	struct prev_channel_config prev_chan_config;
	struct prev_continuous_config prev_cont_config; // continuous mode

	vpPrvw->preview_fd = DVEVM_ST_FAIL;

	vpPrvw->preview_fd = open((const char *) vpPrvw->previewDevice, O_RDWR);
	if (DVEVM_ST_FAIL == vpPrvw->preview_fd)
	{
		SYS_ERROR("Cannot open previewer device\n");
		return DVEVM_ST_FAIL;
	}

	if (ioctl(vpPrvw->preview_fd, PREV_S_OPER_MODE, &user_mode) < 0)
	{
		SYS_ERROR("Can't set operation mode\n");
		dvtb_previewerClose(vpPrvw);
		return DVEVM_ST_FAIL;
	}

	if (ioctl(vpPrvw->preview_fd, PREV_G_OPER_MODE, &oper_mode) < 0)
	{
		SYS_ERROR("Can't get operation mode\n");
		dvtb_previewerClose(vpPrvw);
		return DVEVM_ST_FAIL;
	}

	if (oper_mode == user_mode)
		SYS_DEBUG("Operating mode changed successfully to continuous in previewer");
	else
	{
		SYS_ERROR("failed to set mode to continuous in resizer\n");
		dvtb_previewerClose(vpPrvw);
		return DVEVM_ST_FAIL;
	}

	SYS_DEBUG("Setting default configuration in previewer\n");
	prev_chan_config.oper_mode = oper_mode;
	prev_chan_config.len = 0;
	prev_chan_config.config = NULL; // to set defaults in driver 
	if (ioctl(vpPrvw->preview_fd, PREV_S_CONFIG, &prev_chan_config) < 0)
	{
		SYS_ERROR("Error in setting default configuration\n");
		dvtb_previewerClose(vpPrvw);
		return DVEVM_ST_FAIL;
	}

	SYS_DEBUG("default configuration setting in previewer successfull\n");
	prev_chan_config.oper_mode = oper_mode;
	prev_chan_config.len = sizeof(struct prev_continuous_config);
	prev_chan_config.config = &prev_cont_config;

	if (ioctl(vpPrvw->preview_fd, PREV_G_CONFIG, &prev_chan_config) < 0)
	{
		SYS_ERROR("Error in getting configuration from driver\n");
		dvtb_previewerClose(vpPrvw);
		return DVEVM_ST_FAIL;
	}

	prev_chan_config.oper_mode = oper_mode;
	prev_chan_config.len = sizeof(struct prev_continuous_config);
	prev_chan_config.config = &prev_cont_config;

	if (ioctl(vpPrvw->preview_fd, PREV_S_CONFIG, &prev_chan_config) < 0)
	{
		SYS_ERROR("Error in setting default configuration\n");
		dvtb_previewerClose(vpPrvw);
		return DVEVM_ST_FAIL;
	}

	SYS_OUT("Previewer initialized, fd = %d\n", vpPrvw->preview_fd);

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_previewerClose(DvtbPreviewerInfo *vpPrvw)
{
	ASSERT(vpPrvw != NULL);

	if (vpPrvw->preview_fd > 0)
	{
		close(vpPrvw->preview_fd);
		vpPrvw->preview_fd = DVEVM_ST_FAIL;
	}

	return DVEVM_ST_SUCCESS;
}
