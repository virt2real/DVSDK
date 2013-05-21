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
#include "dvtbV4L2VPBEFeatures.h"
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

DvevmStRetCode
dvtb_initV4l2OutputUserBuffsOverride(void *ptrVpbe)
{
	DvevmStVpbeInfo *vpbe = ptrVpbe;
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	int receivedBufsCount = 0;
	int i = 0, j = 0;
	char *buff = NULL;

	ASSERT(vpbe != NULL);

	vpbe->req.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	vpbe->req.count = vpbe->maxBuffers;
	vpbe->req.memory = V4L2_MEMORY_USERPTR;
	SYS_OUT("Max buffer %d \n", vpbe->req.count);
	if (ioctl(vpbe->videoFd, VIDIOC_REQBUFS, &vpbe->req) < 0)
	{
		SYS_PERROR("Unable to query required number of buffers from driver\n");
		dvtb_close_vpbe(vpbe);
		return retval;
	}
	if (vpbe->req.count < 2) // Driver should allocate minimum two buffers
	{
		SYS_PERROR("Driver allocated only %d buffers, it should allocate at lease 2 buffer \n", vpbe->req.count);
		dvtb_close_vpbe(vpbe);
		return retval;
	}
	receivedBufsCount = vpbe->req.count;

	for (i = 0; i < vpbe->req.count; i++)
	{
		vpbe->buff_info[i].length = vpbe->userbufferlen[i];
		vpbe->buff_info[i].index = i;
		vpbe->buff_info[i].start = (char *) vpbe->userbufferptr[i];

		buff = (char *)vpbe->buff_info[i].start;
		for(j = 1; j < vpbe->buf.length ; j+=2)
		{
			buff[j-1] =  0x80;
			buff[j]   =  0x00;
		}
		
		vpbe->buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		vpbe->buf.memory = V4L2_MEMORY_USERPTR;
		vpbe->buf.index = i;
		vpbe->buf.index = i;
		vpbe->buf.m.userptr = (unsigned long) vpbe->userbufferptr[i];
		vpbe->buf.length = vpbe->userbufferlen[i];
		if (ioctl(vpbe->videoFd, VIDIOC_QBUF, &vpbe->buf) < 0)
		{
			SYS_PERROR("Unable to queue the %d th buffer\n", i);
			for (j = 0; j < vpbe->req.count; j++)
			{
				munmap(vpbe->buff_info[j].start, vpbe->buff_info[j].length);
			}
			dvtb_close_vpbe(vpbe);
			return retval;
		}
	}
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_setV4l2UserBuffConfigOverride(void *ptrVpbe, void *buff)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	DvevmStVpbeInfo *vpbe = ptrVpbe;
	int i = 0, index = -1;

	vpbe->buf.m.offset = (unsigned long) buff;

	for (i = 0; i < vpbe->req.count; i++)
	{
		if (buff == vpbe->buff_info[i].start)
		{
			index = vpbe->buff_info[i].index;
			break;
		}
	}

	if (vpbe->req.count<=i)
	{
		SYS_ERROR("Unable to get the buffer index!!!\n");
		return retval;
	}

	SYS_DEBUG("****** Index = %d ******\n", index);

	vpbe->buf.index = index;
	vpbe->buf.length = vpbe->userbufferlen[index];

	return DVEVM_ST_SUCCESS;
}
