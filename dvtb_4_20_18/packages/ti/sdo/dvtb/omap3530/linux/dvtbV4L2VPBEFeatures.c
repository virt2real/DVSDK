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

#include "dvtbV4L2VPBE.h"
#include "dvtbV4L2VPBEFeatures.h"
#include <linux/fb.h>

#define MAX_BUFFERS             3
#define DSSFILE "/sys/devices/platform/omapdss/%s"
#define FBDEV_OSD "/dev/fb0"
#define WRITETODSS(x,y) \
        sprintf(fmt, DSSFILE, (x)); \
        if (dvtb_writeSysFs(fmt, (y)) == DVEVM_ST_FAIL) return DVEVM_ST_FAIL

DvevmStRetCode
dvtb_ioctlSetupOsd(int width, int height)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	struct fb_var_screeninfo varInfo;
	int fd;

	if (-1 == (fd = open(FBDEV_OSD, O_RDWR)))
	{
		SYS_ERROR("Unable to open %s \n",FBDEV_OSD);
		return retval;
	}
	if(-1 == ioctl(fd, FBIOGET_VSCREENINFO, &varInfo))
	{
		SYS_ERROR("Failed FBIOGET_VSCREENINFO on %s \n",FBDEV_OSD);
		return retval;
	}

	/* Change the resolution */
	varInfo.xres            = width;
	varInfo.yres            = height;
	varInfo.xres_virtual    = width;
	varInfo.yres_virtual    = height;

	if( 0 > ioctl(fd, FBIOPUT_VSCREENINFO, &varInfo))
	{
		SYS_ERROR("Failed FBIOPUT_VSCREENINFO on %s \n",FBDEV_OSD);
		return retval;
	}
	return DVEVM_ST_SUCCESS;	
}

DvevmStRetCode
dvtb_ioctlV4l2SetDisplayOutput(void *ptrVpbe)
{
	char fmt[200];
	DvevmStVpbeInfo *vpbe = ptrVpbe;
	DvevmStRetCode retval = DVEVM_ST_FAIL;

	WRITETODSS((char *) "overlay0/enabled", (char *) "0");
	WRITETODSS((char *) "overlay1/enabled", (char *) "0");
	WRITETODSS((char *) "overlay2/enabled", (char *) "0");

	system("echo \"\" > /sys/devices/platform/omapdss/overlay0/manager");
	system("echo \"\" > /sys/devices/platform/omapdss/overlay1/manager");
	system("echo \"\" > /sys/devices/platform/omapdss/overlay2/manager");

	WRITETODSS((char *) "display0/enabled", (char *) "0");
	WRITETODSS((char *) "display1/enabled", (char *) "0");
	WRITETODSS((char *) "display2/enabled", (char *) "0");

	switch (vpbe->outputDevice)
	{
		case DVEVM_ST_LCD:
			if(!strcmp("VGA",vpbe->ch_mode))
			{
				if (dvtb_ioctlSetupOsd(480,640) != DVEVM_ST_SUCCESS)
					return retval;
			}
			else
			{
				SYS_ERROR("Only VGA is supported for LCD \n");
				return retval;
			}
			WRITETODSS((char *) "overlay0/manager", (char *) "lcd");
			WRITETODSS((char *) "overlay1/manager", (char *) "lcd");
			WRITETODSS((char *) "overlay2/manager", (char *) "lcd");
			WRITETODSS((char *) "manager0/display", (char *) "lcd");
			WRITETODSS((char *) "display0/enabled", (char *) "1");
//			WRITETODSS((char *) "overlay0/enabled", (char *) "1");
			
			
		break;
		case DVEVM_ST_TV:
			if(!strcmp("NTSC",vpbe->ch_mode))
			{
				if (dvtb_ioctlSetupOsd(720,480) != DVEVM_ST_SUCCESS)
					return retval;
			}
			else if(!strcmp("PAL",vpbe->ch_mode))
			{
				if (dvtb_ioctlSetupOsd(720,576) != DVEVM_ST_SUCCESS)
					return retval;
				
			}
			else
			{
				SYS_ERROR("Only NTSC and PAL is supported for TV \n");
				return retval;				
			}
			WRITETODSS((char *) "overlay0/manager", (char *) "tv");
			WRITETODSS((char *) "overlay1/manager", (char *) "tv");
			WRITETODSS((char *) "overlay2/manager", (char *) "tv");
			WRITETODSS((char *) "display1/enabled", (char *) "1");
//			WRITETODSS((char *) "overlay0/enabled", (char *) "1");
			
		break;
		case DVEVM_ST_DVI:
			if(!strcmp("480P",vpbe->ch_mode))
			{
				if (dvtb_ioctlSetupOsd(720,480) != DVEVM_ST_SUCCESS)
					return retval;
			}
			else if(!strcmp("720P",vpbe->ch_mode))
			{
				if (dvtb_ioctlSetupOsd(1280,720) != DVEVM_ST_SUCCESS)
					return retval;
				
			}
			else
			{
				SYS_ERROR("Only 480 and 720P is supported for DVI \n");
				return retval;				
			}
			WRITETODSS((char *) "manager0/display", (char *) "dvi");
			WRITETODSS((char *) "overlay0/manager", (char *) "lcd");
			WRITETODSS((char *) "overlay1/manager", (char *) "lcd");
			WRITETODSS((char *) "overlay2/manager", (char *) "lcd");
//			WRITETODSS((char *) "overlay0/enabled", (char *) "1");
			WRITETODSS((char *) "display2/enabled", (char *) "1");
		break;
	}
	return DVEVM_ST_SUCCESS;	

}

DvevmStRetCode
dvtb_ioctlV4l2OutputSetControl(void *ptrVpbe, void *value)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	DvevmStVpbeInfo *vpbe = ptrVpbe;
	struct v4l2_control control;
	int err;

	ASSERT(vpbe != NULL);
	ASSERT(value != NULL);

	control.id = *(unsigned int *) value;
	switch(control.id)
	{
//		case V4L2_CID_ROTATION:
		case V4L2_CID_ROTATE:
		{
			control.value = vpbe->rotate;

			if ((err = ioctl(vpbe->videoFd, VIDIOC_S_CTRL, &control)) < 0)
			{
				SYS_PERROR("Unable to set rotation %d errno %d %s\n", err, errno, strerror(errno));
				return retval;
			}

			//get the degree by which rotation is set
//			control.id = V4L2_CID_ROTATION;
			control.id = V4L2_CID_ROTATE;
			if ((err = ioctl(vpbe->videoFd, VIDIOC_G_CTRL, &control)) < 0)
			{
				SYS_PERROR("Unable to set rotation %d errno %d %s\n", err, errno, strerror(errno));
				return retval;
			}
			SYS_DEBUG("Rotation set to degree: %d\n", control.value);
		}
		break;

		default:
			SYS_ERROR("Un-supported controlId set!!!");
			return retval;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_ioctlV4l2OutputFrameBuff(DvevmStVpbeInfo *vpbe, void *value)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	struct v4l2_framebuffer framebuffer;
	int err;

	ASSERT(vpbe != NULL);
	ASSERT(value != NULL);

	switch(DVEVM_ST_TRUE)
	{
		case DVEVM_ST_TRUE:
			// Fetch the value of v4l2 framebuffer flags
			if ((err = ioctl(vpbe->videoFd, VIDIOC_G_FBUF, &framebuffer)) < 0)
			{
				SYS_ERROR("Unable to get the framebuffer flags\n");
				return retval;
			}

			// Disabling the alpha blend
			framebuffer.flags &= ~V4L2_FBUF_FLAG_LOCAL_ALPHA;
			if ((err = ioctl(vpbe->videoFd, VIDIOC_S_FBUF, &framebuffer)) < 0)
			{
				SYS_ERROR("Unable to disable the alphablending\n");
				return retval;
			}

			break;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_vpbeScaling(void *ptrVpbe)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	DvevmStVpbeInfo *vpbe = ptrVpbe;
	struct v4l2_crop crop;
	struct v4l2_format fmt;

	ASSERT(vpbe != NULL);

	if (vpbe->scaling)
	{
		memset(&fmt, 0, sizeof(fmt));
		fmt.type = V4L2_BUF_TYPE_VIDEO_OVERLAY;
		fmt.fmt.win.w.left = 0;
		fmt.fmt.win.w.top = 0;
		crop.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		crop.c.left = 0;
		crop.c.top = 0;
		crop.c.width = vpbe->imageWidth;
		crop.c.height = vpbe->imageHeight;

		switch (vpbe->outputDevice)
		{
			case DVEVM_ST_LCD:
				fmt.fmt.win.w.width = VGA_XRES;
				fmt.fmt.win.w.height = VGA_YRES;
				break;

			case DVEVM_ST_DVI:
				fmt.fmt.win.w.width = DVI_XRES;
				fmt.fmt.win.w.height = DVI_YRES;
				break;

			case DVEVM_ST_TV:
				fmt.fmt.win.w.width = D1_PAL_XRES;
				fmt.fmt.win.w.height = D1_PAL_YRES;
				break;

			default:
				SYS_PERROR("Output device is not supported \n");
				fmt.fmt.win.w.width = VGA_XRES;
				fmt.fmt.win.w.height = VGA_YRES;
				SYS_PERROR("Image is scalled to %d x %d \n", fmt.fmt.win.w.width, fmt.fmt.win.w.height);
				break;
		}

		if (ioctl(vpbe->videoFd, VIDIOC_S_FMT, &fmt) < 0)
		{
			SYS_PERROR("Unable to get video format \n");
			return retval;
		}

		if (ioctl(vpbe->videoFd, VIDIOC_S_CROP, &crop) < 0)
		{
			SYS_PERROR("Unable to get video format \n");
			return retval;
		}
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_setV4l2PostFmtConfiguration(void *ptrVpbe)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	DvevmStVpbeInfo *vpbe = ptrVpbe;

	ASSERT(vpbe != NULL);
	
	if (vpbe->scaling)
	{
		if (DVEVM_ST_SUCCESS != dvtb_vpbeScaling(ptrVpbe))
		{
			SYS_ERROR("Unable to set scaling \n");
			dvtb_close_vpbe(vpbe);
			return retval;
		}
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_setV4l2PreFmtConfiguration(void *ptrVpbe)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	DvevmStVpbeInfo *vpbe = ptrVpbe;
	unsigned int value = 1;
	  
	ASSERT(vpbe != NULL);
	ASSERT(value != NULL);

	if (DVEVM_ST_SUCCESS != dvtb_ioctlV4l2SetDisplayOutput(vpbe))
	{
		SYS_ERROR("Unable to set Display output \n");
		dvtb_close_vpbe(vpbe);
		return retval;
	}

	value = 1; // Currently, don't care setting for Alpha belnding
	if (DVEVM_ST_SUCCESS != dvtb_ioctlV4l2OutputFrameBuff(vpbe, &value ))
	{
		SYS_ERROR("Unable to set Disable Alpha blend to %d \n", vpbe->rotate);
		dvtb_close_vpbe(vpbe);
		return retval;
	}

//	value = V4L2_CID_ROTATION;
	value = V4L2_CID_ROTATE;
	if (DVEVM_ST_SUCCESS != dvtb_ioctlV4l2OutputSetControl(vpbe, &value))
	{
		SYS_ERROR("Unable to set Rotation to %d \n", vpbe->rotate);
		dvtb_close_vpbe(vpbe);
		return retval;
	}

	return DVEVM_ST_SUCCESS;
}
