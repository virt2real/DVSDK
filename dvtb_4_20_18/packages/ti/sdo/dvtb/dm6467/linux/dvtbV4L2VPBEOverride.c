/*
 * dvtbV4L2VPBEOverride.c
 *
 * Platform Specific VPBE override functions
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

#include "dvtbV4L2VPBE.h"
#include "dvtbV4L2VPBEOverride.h"

DvevmStRetCode
dvtb_setV4l2OutputFmtOverride(void *ptrVpbe, void *ptrFmt)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	DvevmStVpbeInfo *vpbe = ptrVpbe;
	struct v4l2_format *fmt = ptrFmt;

	fmt->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	if (ioctl(vpbe->videoFd, VIDIOC_G_FMT, fmt) < 0)
	{
		SYS_PERROR("Unable to get video format \n");
		dvtb_close_vpbe(vpbe);
		return retval;
	}

	fmt->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	fmt->fmt.pix.width = vpbe->imageWidth;
	fmt->fmt.pix.height = vpbe->imageHeight;

	if (VID_FMT_YUV420SP == vpbe->pixelformat)
	{
		fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
		fmt->fmt.pix.bytesperline = fmt->fmt.pix.width;
	}
	else if (VID_FMT_UYVY == vpbe->pixelformat)
	{
		fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
		fmt->fmt.pix.bytesperline = fmt->fmt.pix.width * 2;
	}
	else if (VID_FMT_YUV422UVP == vpbe->pixelformat)
	{
//		fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_YUV422UVP;
		fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_NV16;
		fmt->fmt.pix.bytesperline = fmt->fmt.pix.width;
	}
	else
	{
		SYS_PERROR("Unsupported video pixel format\n");
		dvtb_close_vpbe(vpbe);
		return retval;
	}

	if (DVEVM_ST_720P_60 == vpbe->dispStd)
	{
		fmt->fmt.pix.field = V4L2_FIELD_NONE;
	}
	else if ((DVEVM_ST_NTSC == vpbe->dispStd) || (DVEVM_ST_PAL == vpbe->dispStd) || (DVEVM_ST_1080I_30 == vpbe->dispStd))
	{
		fmt->fmt.pix.field = V4L2_FIELD_INTERLACED;
	}
	else
	{
		fmt->fmt.pix.field = V4L2_FIELD_ANY;
	}

	if ((fmt->fmt.pix.sizeimage = dvtb_getV4l2ImgSize(fmt->fmt.pix.bytesperline, fmt->fmt.pix.height, vpbe->pixelformat)) == DVEVM_ST_FAIL)
	{
		SYS_ERROR("unable to calclate image size\n");
		return retval;
	}

	SYS_DEBUG("fmt.fmt.pix.width = %d\n", fmt->fmt.pix.width);
	SYS_DEBUG("fmt.fmt.pix.height = %d\n", fmt->fmt.pix.height);
	SYS_DEBUG("fmt.fmt.pix.bytesperline = %d\n", fmt->fmt.pix.bytesperline);
	SYS_DEBUG("fmt.fmt.pix.sizeimage = %d\n", fmt->fmt.pix.sizeimage);

	if (ioctl(vpbe->videoFd, VIDIOC_S_FMT, fmt) < 0)
	{
		SYS_PERROR("Unable to set video format \n");
		dvtb_close_vpbe(vpbe);
		return retval;
	}

	return DVEVM_ST_SUCCESS;
}

