/*
 * dvtbResizer.c
 *
 * Resizer Interface implementation
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

#include "dvtbResizer.h"

DvevmStRetCode
dvtb_resizerSetup(DvtbResizerInfo *vpRsz)
{
	int user_mode = IMP_MODE_CONTINUOUS;
	unsigned int oper_mode;
	struct rsz_channel_config rsz_chan_config;
	struct rsz_continuous_config rsz_cont_config; // continuous mode

	vpRsz->rsz_fd = DVEVM_ST_FAIL;

	SYS_DEBUG("opening resize device\n");
	vpRsz->rsz_fd = open((const char *) vpRsz->resizeDevice, O_RDWR);
	if (DVEVM_ST_FAIL == vpRsz->rsz_fd)
	{
		SYS_ERROR("Cannot open resize device \n");
		return DVEVM_ST_FAIL;
	}

	if (ioctl(vpRsz->rsz_fd, RSZ_S_OPER_MODE, &user_mode) < 0)
	{
		SYS_ERROR("Can't set operation mode\n");
		dvtb_resizerClose(vpRsz);
		return DVEVM_ST_FAIL;
	}

	if (ioctl(vpRsz->rsz_fd, RSZ_G_OPER_MODE, &oper_mode) < 0)
	{
		SYS_ERROR("Can't get operation mode\n");
		dvtb_resizerClose(vpRsz);
		return DVEVM_ST_FAIL;
	}

	if (oper_mode == user_mode)
		SYS_DEBUG("Successfully set mode to continuous in resizer\n");
	else
	{
		SYS_ERROR("failed to set mode to continuous in resizer\n");
		dvtb_resizerClose(vpRsz);
		return DVEVM_ST_FAIL;
	}

	// set configuration to chain resizer
	rsz_chan_config.oper_mode = user_mode;
	rsz_chan_config.chain = 1;
	rsz_chan_config.len = 0;
	rsz_chan_config.config = NULL; // to set defaults in driver 
	if (ioctl(vpRsz->rsz_fd, RSZ_S_CONFIG, &rsz_chan_config) < 0)
	{
		SYS_ERROR("Error in setting default configuration in resizer\n");
		dvtb_resizerClose(vpRsz);
		return DVEVM_ST_FAIL;
	}

	SYS_DEBUG("default configuration setting in Resizer successfull\n");
	bzero(&rsz_cont_config, sizeof(struct rsz_continuous_config));
	rsz_chan_config.oper_mode = user_mode;
	rsz_chan_config.chain = 1;
	rsz_chan_config.len = sizeof(struct rsz_continuous_config);
	rsz_chan_config.config = &rsz_cont_config;

	if (ioctl(vpRsz->rsz_fd, RSZ_G_CONFIG, &rsz_chan_config) < 0)
	{
		SYS_ERROR("Error in getting resizer channel configuration from driver\n");
		dvtb_resizerClose(vpRsz);
		return DVEVM_ST_FAIL;
	}

	rsz_cont_config.output1.enable = 1;
	rsz_cont_config.output2.enable = 0;
	rsz_chan_config.len = sizeof(struct rsz_continuous_config);
	rsz_chan_config.config = &rsz_cont_config;

	if (ioctl(vpRsz->rsz_fd, RSZ_S_CONFIG, &rsz_chan_config) < 0)
	{
		SYS_ERROR("Error in setting configuration in resizer\n");
		dvtb_resizerClose(vpRsz);
		return DVEVM_ST_FAIL;
	}
	SYS_OUT("Resizer initialized, fd = %d\n", vpRsz->rsz_fd);
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_resizerClose(DvtbResizerInfo *vpRsz)
{
	ASSERT(vpRsz != NULL);

	if (vpRsz->rsz_fd > 0)
	{
		close(vpRsz->rsz_fd);
		vpRsz->rsz_fd = DVEVM_ST_FAIL;
	}

	return DVEVM_ST_SUCCESS;
}

