/*
 * dvtbV4L2VPFE.c
 *
 * V4L2 VPFE driver Interface implementation
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

#include "dvtbV4L2VPFE.h"
#include "dvtbMemory.h"

static unsigned int
dvtb_getV4l2Fmt(DvevmStVidFmt fmt)
{
	unsigned int v4l2Fmt = V4L2_PIX_FMT_YUYV;

	switch (fmt)
	{
		case VID_FMT_UYVY:
			v4l2Fmt = V4L2_PIX_FMT_UYVY;
			break;

		case VID_FMT_YUYV:
			v4l2Fmt = V4L2_PIX_FMT_YUYV;
			break;

		case VID_FMT_YUV420:
			v4l2Fmt = V4L2_PIX_FMT_YUV420;
			break;

		case VID_FMT_YUV422P:
			v4l2Fmt = V4L2_PIX_FMT_YUV422P;
			break;

		case VID_FMT_YUV410:
			v4l2Fmt = V4L2_PIX_FMT_YUV410;
			break;

		case VID_FMT_YVU420:
			v4l2Fmt = V4L2_PIX_FMT_YVU420;
			break;

		case VID_FMT_RGB565:
			v4l2Fmt = V4L2_PIX_FMT_RGB565;
			break;
		case VID_FMT_YUV422UVP:
//			v4l2Fmt = V4L2_PIX_FMT_YUV422UVP;
			v4l2Fmt = V4L2_PIX_FMT_NV16;
			break;
		case VID_FMT_YUV420SP:
			v4l2Fmt = V4L2_PIX_FMT_NV12;
			break;
		default:
			v4l2Fmt = DVEVM_ST_FAIL;
			break;
	}

	return v4l2Fmt;
}

static v4l2_std_id
dvtb_getV4l2Std(DvevmStVidStd std)
{
	v4l2_std_id v4l2Std = V4L2_STD_NTSC;

	switch (std)
	{
		case VID_STD_AUTO:
			v4l2Std = VPFE_STD_AUTO;
			break;

		case VID_STD_NTSC:
			v4l2Std = V4L2_STD_NTSC;
			break;

		case VID_STD_PAL:
			v4l2Std = V4L2_STD_PAL;
			break;

		case VID_STD_SECAM:
			v4l2Std = V4L2_STD_SECAM;
			break;
		case VID_STD_720SP_60:
			v4l2Std = V4L2_STD_720P_60;
			break;
		case VID_STD_1080I_60:
			v4l2Std = V4L2_STD_1080I_60;
			break;
		default:
			v4l2Std = DVEVM_ST_FAIL;
	}

	return v4l2Std;
}

DvevmStRetCode
dvtb_vpfeDeviceClose(DvevmStVpfeInfo *vpfe)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if(DVEVM_ST_FAIL != vpfe->capFd)
	{
		if (DVEVM_ST_FAIL == close(vpfe->capFd))
		{
			SYS_PERROR("Failed to close capture device\n");
			retCode = DVEVM_ST_FAIL;
		}
	}
	vpfe->capFd = DVEVM_ST_FAIL;

	return retCode;
}

DvevmStRetCode
dvtb_v4l2MmapAlloc(DvevmStVpfeInfo *vpfe, int count)
{

	int i = 0, numBufs = 0;
	struct v4l2_buffer buf;

	numBufs = count;
	for (i = 0; i < count; i++)
	{
		// query the details of the buffer like phys address
		ZERO(buf);
		buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index  = i;
		if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_QUERYBUF, &buf))
		{
			SYS_ERROR("VPFE device <%s> VIDIOC_QUERYBUF failed for %d buffer\n", vpfe->device, buf.index);
			vpfe->numBufs = i;
			dvtb_vpfeClose(vpfe);
			return DVEVM_ST_FAIL;
		}

		vpfe->buffers[i].length = buf.length;
		vpfe->buffers[i].start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, vpfe->capFd, buf.m.offset);

		if (MAP_FAILED == vpfe->buffers[i].start)
		{
			SYS_PERROR("Failed to mmap buffer on <%s>\n", vpfe->device);
			vpfe->numBufs = i;
			dvtb_vpfeClose(vpfe);
			return DVEVM_ST_FAIL;
		}

		memset(vpfe->buffers[i].start, 0x80, vpfe->buffers[i].length);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.index = i;
		buf.memory = V4L2_MEMORY_MMAP;
		if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_QBUF, &buf))
		{
			SYS_PERROR("VIODIOC_QBUF failed on <%s>\n", vpfe->device);
			vpfe->numBufs = i;
			dvtb_vpfeClose(vpfe);
			return DVEVM_ST_FAIL;
		}
	}
	vpfe->numBufs = numBufs;
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_v4l2UserAlloc(DvevmStVpfeInfo *vpfe, int count)
{
	int i = 0, numBufs = 0;
        struct v4l2_buffer buf;
	
	//Allocate buffer
        numBufs = count;
	for(i = 0; i < count; i++)
	{
		vpfe->buffers[i].length = ALIGN(vpfe->capSize,4096);
		if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem((char **)&vpfe->buffers[i].start, vpfe->buffers[i].length))
		{
			SYS_ERROR("Unable to allocate memory for Capture buffer. \n");	
			vpfe->numBufs = i;
			dvtb_vpfeClose(vpfe);
			return DVEVM_ST_FAIL;
		} 	
	}
	vpfe->numBufs = numBufs;
	
        for (i = 0; i < count; i++)
        {
		// query the details of the buffer like phys address
                ZERO(buf);
                buf.type      = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory    = V4L2_MEMORY_USERPTR;
		buf.index     = i;
		buf.m.userptr = (unsigned int)vpfe->buffers[i].start;
		buf.length    = vpfe->buffers[i].length;

		memset(vpfe->buffers[i].start, 0x80, vpfe->buffers[i].length);
		if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_QBUF, &buf))
		{
			SYS_PERROR("VIODIOC_QBUF failed on <%s>  \n", vpfe->device);
			dvtb_vpfeClose(vpfe);
			return DVEVM_ST_FAIL;
		}
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_vpfeSetup(DvevmStVpfeInfo *vpfe)
{
	struct v4l2_requestbuffers req;
	struct v4l2_capability cap;
	struct v4l2_format fmt;
	static v4l2_std_id capture_std;
	
	ASSERT(vpfe != NULL);

	vpfe->capFd = DVEVM_ST_FAIL;
	vpfe->buffers = NULL;
	vpfe->isStreamOn = DVEVM_ST_FALSE;

	vpfe->capFd = open(vpfe->device, O_RDWR | O_NONBLOCK, 0);
	if (DVEVM_ST_FAIL == vpfe->capFd)
	{
		SYS_PERROR("Unable to initialize VPFE device <%s>\n", vpfe->device);
		return DVEVM_ST_FAIL;
	}

	// Query device capabilities
	if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_QUERYCAP, &cap))
	{
		if (EINVAL == errno)
		{
			SYS_ERROR("< %s> is not a V4L2 device\n", vpfe->device);
			dvtb_vpfeDeviceClose(vpfe);
			return DVEVM_ST_FAIL;
		}

		SYS_PERROR("Failed VIDIOC_QUERYCAP on <%s>\n", vpfe->device);
		dvtb_vpfeDeviceClose(vpfe);
		return DVEVM_ST_FAIL;
	}

	if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
	{
		SYS_ERROR("<%s> is not a video capture device\n", vpfe->device);
		dvtb_vpfeDeviceClose(vpfe);
		return DVEVM_ST_FAIL;
	}

	if (!(cap.capabilities & V4L2_CAP_STREAMING))
	{
		SYS_ERROR("VPFE device <%s> does not support streaming\n", vpfe->device);
		dvtb_vpfeDeviceClose(vpfe);
		return DVEVM_ST_FAIL;
	}

	if(VID_STD_NA != vpfe->capStd)
	{
		capture_std = dvtb_getV4l2Std(vpfe->capStd);
		if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_S_STD, &capture_std))
		{
			SYS_PERROR("VIDIOC_S_STD failed for <%d> format for <%s>\n", vpfe->capStd, vpfe->device);
			dvtb_vpfeDeviceClose(vpfe);
			return DVEVM_ST_FAIL;
		}

		if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_S_INPUT, &vpfe->input))
		{
			SYS_PERROR("Unable to set video input of <%s> to <%d>\n", vpfe->device, vpfe->input);
			dvtb_vpfeDeviceClose(vpfe);
			return DVEVM_ST_FAIL;
		}
	}
	else
	{
		if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_S_INPUT, &vpfe->input))
		{
			SYS_PERROR("Unable to set video input of <%s> to <%d>\n", vpfe->device, vpfe->input);
			dvtb_vpfeDeviceClose(vpfe);
			return DVEVM_ST_FAIL;
		}
		if (DVEVM_ST_FAIL ==  ioctl(vpfe->capFd, VIDIOC_QUERYSTD, &capture_std))
		{
			SYS_ERROR("VPFE device <%s> VIDIOC_QUERYSTD failed \n", vpfe->device);
			dvtb_vpfeDeviceClose(vpfe);
			return DVEVM_ST_FAIL;
		}
		SYS_DEBUG("Capture std = %llx\n",capture_std);
	}

	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_G_FMT, &fmt))
	{
		SYS_PERROR("VIDIOC_G_FMT failed on <%s>\n", vpfe->device);
		dvtb_vpfeDeviceClose(vpfe);
		return DVEVM_ST_FAIL;
	}

	SYS_DEBUG("Width  = %d \t Height = %d\n", fmt.fmt.pix.width, fmt.fmt.pix.height);
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = vpfe->capWidth;
	fmt.fmt.pix.height = vpfe->capHeight;
	fmt.fmt.pix.pixelformat = dvtb_getV4l2Fmt(vpfe->capFmt);

	if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_S_FMT, &fmt))
	{
		SYS_PERROR("VIDIOC_S_FMT failed for <%s>\n", vpfe->device);
		dvtb_vpfeDeviceClose(vpfe);
		return DVEVM_ST_FAIL;
	}
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_G_FMT, &fmt))
	{
		SYS_PERROR("VIDIOC_G_FMT failed on <%s>\n", vpfe->device);
		dvtb_vpfeDeviceClose(vpfe);
		return DVEVM_ST_FAIL;
	}

	switch (vpfe->opMode)
	{
		case DVEVM_ST_MMAP:
			vpfe->capSize = fmt.fmt.pix.sizeimage;
			ZERO(req);
			req.count = 3;
			req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			req.memory = V4L2_MEMORY_MMAP;
			break;

		case DVEVM_ST_USERBUFFER:
			vpfe->capSize = fmt.fmt.pix.sizeimage;
			ZERO(req);
			req.count = 3;
			req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			req.memory = V4L2_MEMORY_USERPTR;
			break;

		default:
			SYS_ERROR("VPFE device <%s>: operation mode %d is not supported \n",vpfe->device, vpfe->opMode);
			dvtb_vpfeDeviceClose(vpfe);
			return DVEVM_ST_FAIL;

	}

	if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_REQBUFS, &req))
	{
		SYS_ERROR("VPFE device <%s> VIDIOC_REQBUFS failed \n", vpfe->device);
		dvtb_vpfeDeviceClose(vpfe);
		return DVEVM_ST_FAIL;
	}


	if (req.count < MIN_CAP_BUFS)
	{
		SYS_ERROR("Insufficient buffer memory on <%s>\n", vpfe->device);
		dvtb_vpfeDeviceClose(vpfe);
		return DVEVM_ST_FAIL;
	}

	vpfe->buffers = calloc(req.count, sizeof(VideoBuffer));

	if (!vpfe->buffers)
	{
		SYS_ERROR("Failed to allocate memory for capture buffer structs.\n");
		dvtb_vpfeDeviceClose(vpfe);
		return DVEVM_ST_FAIL;
	}

	switch (vpfe->opMode)
	{
		case DVEVM_ST_MMAP:
			if(DVEVM_ST_FAIL == dvtb_v4l2MmapAlloc(vpfe,req.count))
			{
				SYS_ERROR("VPFE device <%s>: operation mode %d : V4L2 MMAP Alloc failed \n",vpfe->device, vpfe->opMode);
				dvtb_vpfeClose(vpfe);
				return DVEVM_ST_FAIL;
			}
			break;

		case DVEVM_ST_USERBUFFER:
			if(DVEVM_ST_FAIL == dvtb_v4l2UserAlloc(vpfe,req.count))
			{
				SYS_ERROR("VPFE device <%s>: operation mode %d : V4L2 User Alloc failed \n",vpfe->device, vpfe->opMode);
				dvtb_vpfeClose(vpfe);
				return DVEVM_ST_FAIL;
			}

			break;

		default:
			SYS_ERROR("VPFE device <%s>: operation mode %d is not supported \n",vpfe->device, vpfe->opMode);
			dvtb_vpfeDeviceClose(vpfe);
			return DVEVM_ST_FAIL;
	}

		
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_G_FMT, &fmt))
	{
		SYS_PERROR("VIDIOC_G_FMT failed on <%s>\n", vpfe->device);
		dvtb_vpfeClose(vpfe);
		return DVEVM_ST_FAIL;
	}

	SYS_DEBUG("Width  = %d \t Height = %d\n", fmt.fmt.pix.width, fmt.fmt.pix.height);

	//  vpfe->capSize = vpfe->capWidth * vpfe->capHeight * 2;

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_vpfeCaptureStart(DvevmStVpfeInfo *vpfe)
{
	enum v4l2_buf_type type;

	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_STREAMON, &type))
	{
		SYS_PERROR("VIDIOC_STREAMON failed on <%s>\n", vpfe->device);
		return DVEVM_ST_FAIL;
	}
	vpfe->isStreamOn = DVEVM_ST_TRUE;

	SYS_DEBUG("V4L2 device <%s> initialized\n", vpfe->device);
	SYS_DEBUG("Video Standard     : %d\n", vpfe->capStd);
	SYS_DEBUG("Video Format       : %d\n", vpfe->capFmt);
	SYS_DEBUG("Capture Width      : %d\n", vpfe->capWidth);
	SYS_DEBUG("Capture Height     : %d\n", vpfe->capHeight);
	SYS_DEBUG("Capture Frame Size : %d\n", vpfe->capSize);
	SYS_DEBUG("Num Capture Buffs  : %d\n", vpfe->numBufs);

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_vpfeGetNextBuffer(DvevmStVpfeInfo *vpfe)
{
	ZERO(vpfe->buf);
	vpfe->buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	while (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_DQBUF, &vpfe->buf))
	{
		if (EAGAIN == errno)
		{
			SYS_DEBUG("Can not DQBUF: try again \n");
			continue;
		}
		SYS_PERROR("VIDIOC_DQBUF failed \n");
		return DVEVM_ST_FAIL;
	}
	
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_vpfeReturnBuffer(DvevmStVpfeInfo *vpfe)
{
	ASSERT(vpfe != NULL);
	
	if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_QBUF, &vpfe->buf))
	{
		SYS_PERROR("VIDIOC_QBUF failed\n");
		return DVEVM_ST_FAIL;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_vpfeClose(DvevmStVpfeInfo *vpfe)
{
	enum v4l2_buf_type type;
	unsigned int i;

	ASSERT(vpfe != NULL);

	if (vpfe->capFd > 0)
	{
		/* Shut off the video capture */

		if(DVEVM_ST_TRUE == vpfe->isStreamOn)
		{
			type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			if (DVEVM_ST_FAIL == ioctl(vpfe->capFd, VIDIOC_STREAMOFF, &type))
			{
				SYS_PERROR("VIDIOC_STREAMOFF failed\n");
			}
			vpfe->isStreamOn = DVEVM_ST_FALSE;
		}
		if (DVEVM_ST_FAIL == dvtb_vpfeDeviceClose(vpfe))
		{
			SYS_PERROR("Failed in vpfe Device close \n");
		}

	        switch (vpfe->opMode)
        	{
                	case DVEVM_ST_MMAP:

				for (i = 0; i < vpfe->numBufs; i++)
				{
					if (munmap(vpfe->buffers[i].start, vpfe->buffers[i].length) == -1)
					{
						SYS_ERROR("Failed to unmap capture buffer %d\n", i);
					}
					SYS_DEBUG("munmap done for buffer = %d\n", i);
				}
				break;

			case DVEVM_ST_USERBUFFER:
				for(i = 0; i < vpfe->numBufs; i++)
				{
					dvtb_freeSingleBufCmem(vpfe->buffers[i].start, vpfe->buffers[i].length);
					vpfe->buffers[i].start = NULL;
				}
				break;
		}
		free(vpfe->buffers);
		SYS_DEBUG("buffers free done\n");
	}

	return DVEVM_ST_SUCCESS;
}
