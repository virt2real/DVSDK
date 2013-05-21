/*
 * dvtbV4L2VPBEFeatures.c
 *
 * Platform Specific VPBE features
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

#include "dvtbV4L2VPBEFeatures.h"

#define SYSFS_CH0_OUTPUT          "/sys/class/davinci_display/ch0/output"
#define SYSFS_CH0_MODE            "/sys/class/davinci_display/ch0/mode"
#define DISPLAY_INTERFACE_COMPOSITE     "COMPOSITE"
#define DISPLAY_INTERFACE_COMPONENT     "COMPONENT"
#define DISPLAY_MODE_PAL        "PAL"
#define DISPLAY_MODE_NTSC       "NTSC"
#define DISPLAY_MODE_720P       "720P-60"
#define DISPLAY_MODE_1080I      "1080I-30"

DvevmStRetCode
dvtb_PreFmtConfiguration(DvevmStVpbeInfo *vpbe)
{
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        switch(vpbe->dispStd)
        {
                case DVEVM_ST_NTSC:
                        if( DVEVM_ST_FAIL == dvtb_writeSysFs(SYSFS_CH0_OUTPUT, DISPLAY_INTERFACE_COMPOSITE ))
                        {
                                retCode = DVEVM_ST_FAIL;
                                break;
                        }
                        if( DVEVM_ST_FAIL == dvtb_writeSysFs(SYSFS_CH0_MODE, DISPLAY_MODE_NTSC ))
                        {
                                retCode = DVEVM_ST_FAIL;
                                break;
                        }
                        break;

                case DVEVM_ST_PAL:
                        if( DVEVM_ST_FAIL == dvtb_writeSysFs(SYSFS_CH0_OUTPUT, DISPLAY_INTERFACE_COMPOSITE ))
                        {
                                retCode = DVEVM_ST_FAIL;
                                break;
                        }
                        if( DVEVM_ST_FAIL == dvtb_writeSysFs(SYSFS_CH0_MODE, DISPLAY_MODE_PAL ))
                        {
                                retCode = DVEVM_ST_FAIL;
                        }
                        break;
                case DVEVM_ST_720P_60:
                        if( DVEVM_ST_FAIL == dvtb_writeSysFs(SYSFS_CH0_OUTPUT, DISPLAY_INTERFACE_COMPONENT ))
                        {
                                retCode = DVEVM_ST_FAIL;
                                break;
                        }
                        if( DVEVM_ST_FAIL == dvtb_writeSysFs(SYSFS_CH0_MODE, DISPLAY_MODE_720P ))
                        {
                                retCode = DVEVM_ST_FAIL;
                        }
                        break;
                case DVEVM_ST_1080I_60:
                        if( DVEVM_ST_FAIL == dvtb_writeSysFs(SYSFS_CH0_OUTPUT, DISPLAY_INTERFACE_COMPONENT ))
                        {
                                retCode = DVEVM_ST_FAIL;
                                break;
                        }
                        if( DVEVM_ST_FAIL == dvtb_writeSysFs(SYSFS_CH0_MODE, DISPLAY_MODE_1080I ))
                        {
                                retCode = DVEVM_ST_FAIL;
                        }
                        break;
                default:
                        SYS_ERROR("Cannot display %d standard \n",vpbe->dispStd);
                        retCode = DVEVM_ST_FAIL;
        }

        return retCode;
}


DvevmStRetCode
dvtb_displayCropSetup(DvevmStVpbeInfo *vpbe)
{
	struct v4l2_cropcap cropCap;


	cropCap.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;

	if (DVEVM_ST_FAIL == ioctl(vpbe->videoFd, VIDIOC_CROPCAP, &cropCap))
	{
		SYS_PERROR("VIDIOC_CROPCAP failed for <%s>\n", vpbe->device);
	}

	if (DVEVM_ST_FAIL == ioctl(vpbe->videoFd, VIDIOC_S_CROP, &vpbe->crop))
	{
		SYS_PERROR("VIDIOC_S_CROP failed!\n");
		return DVEVM_ST_FAIL;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_displaySetOffSet(DvevmStVpbeInfo *vpbe)
{

	if (ioctl(vpbe->videoFd, VIDIOC_S_COFST, &vpbe->y_uv_buffOffset))
	{
		SYS_ERROR("VIDIOC_S_COFST failed: %d \n", vpbe->y_uv_buffOffset);
		return DVEVM_ST_FAIL;
	}

	return DVEVM_ST_SUCCESS;
}
