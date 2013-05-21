/*
 * dvtbV4L2VPBE.c
 *
 * V4L2 VPBE driver Interface implementation
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
#include "dvtbUtils.h"

int
dvtb_getV4l2ImgSize(unsigned int pitch, unsigned int height, DvevmStVidFmt fmt)
{
	int v4l2ImgSize = 0;
	switch (fmt)
	{
		case VID_FMT_UYVY:
			v4l2ImgSize = pitch * height;
			break;

		case VID_FMT_YUV420SP:
			v4l2ImgSize = (pitch * height * 3) / 2;
			break;

		case VID_FMT_YUV422UVP:
			v4l2ImgSize = pitch * height;
			break;

		default:
			v4l2ImgSize = DVEVM_ST_FAIL;
	}
	v4l2ImgSize = ALIGN(v4l2ImgSize,4096);

	return v4l2ImgSize;
}

DvevmStRetCode
dvtb_writeSysFs(char *fileName, char *val)
{
	FILE *fp;
	char *valString;

	valString = malloc(strlen(val) + 1);

	if (NULL == valString)
	{
		SYS_ERROR("Failed to allocate memory for temporary string\n");
		return DVEVM_ST_FAIL;
	}

	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fp, fileName, "w"))
	{
		SYS_ERROR("Failed to open %s for writing\n", fileName);
		free(valString);
		return DVEVM_ST_FAIL;
	}

	if (1 != fwrite(val, strlen(val) + 1, 1, fp))
	{
		SYS_ERROR("Failed to write sysfs variable %s to %s\n", fileName, val);
		fclose(fp);
		free(valString);
		return DVEVM_ST_FAIL;
	}

	fclose(fp);

	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fp, fileName, "r"))
	{
		SYS_ERROR("Failed to open %s for reading\n", fileName);
		free(valString);
		return DVEVM_ST_FAIL;
	}


	fread(valString, 1, strlen(val) + 1, fp);

	if (0 != ferror(fp))
	{
		SYS_ERROR("Failed to read sysfs value from %s\n", fileName);
		fclose(fp);
		free(valString);
		return DVEVM_ST_FAIL;
	}

	fclose(fp);

	valString[strlen(val)] = 0;

	if (0 != strcmp(valString, val))
	{
		SYS_ERROR("Failed to verify sysfs variable %s to %s (is %s)\n", fileName, val, valString);
		free(valString);
		return DVEVM_ST_FAIL;
	}

	free(valString);

	return DVEVM_ST_SUCCESS;
}

void
dvtb_close_vpbe(DvevmStVpbeInfo *vpbe)
{
	if (vpbe->videoFd != -1)
		close(vpbe->videoFd);

	if (vpbe->osd0Fd != -1)
		close(vpbe->osd0Fd);

	if (vpbe->osd1Fd != -1)
		close(vpbe->osd1Fd);

	vpbe->videoFd = -1;
	vpbe->osd0Fd = -1;
	vpbe->osd1Fd = -1;

	return;
}

void
dvtb_vpbeCleanup(DvevmStVpbeInfo *vpbe)
{
	int j = 0;

//	ASSERT(vpbe != NULL);

	if (DVEVM_ST_MMAP==vpbe->opMode)
	{
		for (j = 0; j < vpbe->req.count; j++)
		{
			if (NULL != vpbe->buff_info[j].start)
			{
				munmap(vpbe->buff_info[j].start, vpbe->buff_info[j].length);
				vpbe->buff_info[j].start = NULL;
			}
		}
		vpbe->req.count = 0;
	}

	dvtb_close_vpbe(vpbe);

	return;
}

DvevmStRetCode
dvtb_initV4l2OutputUserBuffs(DvevmStVpbeInfo *vpbe)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;

	ASSERT(vpbe != NULL);

	vpbe->req.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	vpbe->req.count = MIN_DISPLAY_BUFFERS;
	vpbe->req.memory = V4L2_MEMORY_USERPTR;

	if (ioctl(vpbe->videoFd, VIDIOC_REQBUFS, &vpbe->req) < 0)
	{
		SYS_PERROR("'VIDIOC_REQBUFS' control call failed\n");
		dvtb_close_vpbe(vpbe);
		return retval;
	}

	vpbe->buf.length = dvtb_getV4l2ImgSize(vpbe->imagePitch, vpbe->imageHeight, vpbe->pixelformat);

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_initV4l2OutputMmapBuffs(DvevmStVpbeInfo *vpbe)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	int receivedBufsCount = 0;
	int i , j;
	char *buff = NULL;

	ASSERT(vpbe != NULL);
	
	/* Allocate the buffers */
	vpbe->req.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	vpbe->req.count = MAX_DISPLAY_MMAP_BUFFERS;
	vpbe->req.memory = V4L2_MEMORY_MMAP;
	if (ioctl(vpbe->videoFd, VIDIOC_REQBUFS, &vpbe->req) < 0)
	{
		SYS_PERROR("Unable to get required buffer count from driver\n");
		dvtb_close_vpbe(vpbe);
		return retval;
	}

	receivedBufsCount = vpbe->req.count;
	SYS_DEBUG("Received buf count = %d\n", receivedBufsCount);

	/* Get the buffer information and mmap them */
	for (i = 0; i < vpbe->req.count; i++)
	{
		vpbe->buf.index = i;
		if (ioctl(vpbe->videoFd, VIDIOC_QUERYBUF, &vpbe->buf) < 0)
		{
			SYS_PERROR("Unable to query buffer\n");
			dvtb_close_vpbe(vpbe);
			return retval;
		}

		SYS_DEBUG("Size of the buffer = %d\n", vpbe->buf.length);
		vpbe->buff_info[i].length = vpbe->buf.length;
		vpbe->buff_info[i].index = i;
		vpbe->buff_info[i].start = mmap(NULL, vpbe->buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, vpbe->videoFd, vpbe->buf.m.offset);
		
		if (vpbe->buff_info[i].start == MAP_FAILED)
		{
			SYS_PERROR("Unable to mmap = %d buffer\n", i);
			for (j = 0; j < i; j++)
			{
				munmap(vpbe->buff_info[j].start, vpbe->buff_info[j].length);
				vpbe->buff_info[j].start = NULL;
			}
			dvtb_close_vpbe(vpbe);
			return retval;
		}
		buff = (char *)vpbe->buff_info[i].start;
		for(j = 1; j < vpbe->buf.length ; j+=2)
		{
			buff[j-1] =  0x80;
			buff[j]   =  0x00;
		}
	}

	for (i = 0; i < vpbe->req.count; i++)
	{
		vpbe->buf.index = i;
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
dvtb_setV4l2OutputDac(DvevmStVpbeInfo *vpbe)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	char outputName[10];

	ASSERT(vpbe != NULL);

	switch (vpbe->dispOutput)
	{
		case DVEVM_ST_OUTPUT_NA:
			break;
		case DVEVM_ST_COMPOSITE:
			strcpy(outputName, "COMPOSITE");
			SYS_OUT("Setting Display Output as <%s>\n", outputName);
			if (DVEVM_ST_SUCCESS != dvtb_writeSysFs(SYSFS_OUTPUT, outputName))
			{
				SYS_ERROR("Unable to set the Display Output as <%s> in the driver.\n", outputName);
				dvtb_close_vpbe(vpbe);
				return retval;
			}
			break;

		case DVEVM_ST_COMPONENT:
			strcpy(outputName, "COMPONENT");
			SYS_OUT("Setting Display Output as <%s>\n", outputName);
			if (DVEVM_ST_SUCCESS != dvtb_writeSysFs(SYSFS_OUTPUT, outputName))
			{
				SYS_ERROR("Unable to set the Display Output as <%s> in the driver.\n", outputName);
				dvtb_close_vpbe(vpbe);
				return retval;
			}
			break;

		case DVEVM_ST_SVIDEO:
			strcpy(outputName, "SVIDEO");
			SYS_OUT("Setting Display Output as <%s>\n", outputName);
			if (DVEVM_ST_SUCCESS != dvtb_writeSysFs(SYSFS_OUTPUT, outputName))
			{
				SYS_ERROR("Unable to set the Display Output as <%s> in the driver.\n", outputName);
				dvtb_close_vpbe(vpbe);
				return retval;
			}
			break;

		default:
			SYS_ERROR("Invalid Display Output. Setting it to COMPOSITE by default.\n");
			strcpy(outputName, "COMPOSITE");
			SYS_OUT("Setting Display Output as <%s>\n", outputName);
			if (DVEVM_ST_SUCCESS != dvtb_writeSysFs(SYSFS_OUTPUT, outputName))
			{
				SYS_ERROR("Unable to set the Display Output as <%s> in the driver.\n", outputName);
				dvtb_close_vpbe(vpbe);
				return retval;
			}
			break;
	}
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_setV4l2OutputSandard(DvevmStVpbeInfo *vpbe)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	char stdName[10];

	ASSERT(vpbe != NULL);

	switch (vpbe->dispStd)
	{
		case DVEVM_ST_STANDARD_NA:
			break;
		case DVEVM_ST_NTSC:
			strcpy(stdName, "NTSC");
			SYS_OUT("Setting Display Standard as <%s>\n", stdName);
			if (DVEVM_ST_SUCCESS != dvtb_writeSysFs(SYSFS_STANDARD, stdName))
			{
				SYS_ERROR("Unable to set the Display Standard as <%s> in the driver.\n", stdName);
				dvtb_close_vpbe(vpbe);
				return retval;
			}
			break;

		case DVEVM_ST_PAL:
			strcpy(stdName, "PAL");
			SYS_OUT("Setting Display Standard as <%s>\n", stdName);
			if (DVEVM_ST_SUCCESS != dvtb_writeSysFs(SYSFS_STANDARD, stdName))
			{
				SYS_ERROR("Unable to set the Display Standard as <%s> in the driver.\n", stdName);
				dvtb_close_vpbe(vpbe);
				return retval;
			}
			break;

		case DVEVM_ST_720P_60:
			strcpy(stdName, "720P-60");
			SYS_OUT("Setting Display Standard as <%s>\n", stdName);
			if (DVEVM_ST_SUCCESS != dvtb_writeSysFs(SYSFS_STANDARD, stdName))
			{
				SYS_ERROR("Unable to set the Display Standard as <%s> in the driver.\n", stdName);
				dvtb_close_vpbe(vpbe);
				return retval;
			}
			break;

		case DVEVM_ST_720P_50:
			strcpy(stdName, "720P-50");
			SYS_OUT("Setting Display Standard as <%s>\n", stdName);
			if (DVEVM_ST_SUCCESS != dvtb_writeSysFs(SYSFS_STANDARD, stdName))
			{
				SYS_ERROR("Unable to set the Display Standard as <%s> in the driver.\n", stdName);
				dvtb_close_vpbe(vpbe);
				return retval;
			}
			break;

		case DVEVM_ST_1080I_30:
			strcpy(stdName, "1080I-30");
			SYS_OUT("Setting Display Standard as <%s>\n", stdName);
			if (DVEVM_ST_SUCCESS != dvtb_writeSysFs(SYSFS_STANDARD, stdName))
			{
				SYS_ERROR("Unable to set the Display Standard as <%s> in the driver.\n", stdName);
				dvtb_close_vpbe(vpbe);
				return retval;
			}
			break;

		case DVEVM_ST_1080I_25:
			strcpy(stdName, "1080I-25");
			SYS_OUT("Setting Display Standard as <%s>\n", stdName);
			if (DVEVM_ST_SUCCESS != dvtb_writeSysFs(SYSFS_STANDARD, stdName))
			{
				SYS_ERROR("Unable to set the Display Standard as <%s> in the driver.\n", stdName);
				dvtb_close_vpbe(vpbe);
				return retval;
			}
			break;

		case DVEVM_ST_480P_60:
			strcpy(stdName, "480P-60");
			SYS_OUT("Setting Display Standard as <%s>\n", stdName);
			if (DVEVM_ST_SUCCESS != dvtb_writeSysFs(SYSFS_STANDARD, stdName))
			{
				SYS_ERROR("Unable to set the Display Standard as <%s> in the driver.\n", stdName);
				dvtb_close_vpbe(vpbe);
				return retval;
			}
			break;

		case DVEVM_ST_576P_50:
			strcpy(stdName, "576P-50");
			SYS_OUT("Setting Display Standard as <%s>\n", stdName);
			if (DVEVM_ST_SUCCESS != dvtb_writeSysFs(SYSFS_STANDARD, stdName))
			{
				SYS_ERROR("Unable to set the Display Standard as <%s> in the driver.\n", stdName);
				dvtb_close_vpbe(vpbe);
				return retval;
			}
			break;

		default:
			SYS_ERROR("Invalid Display Std. Setting it to NTSC by default.\n");
			strcpy(stdName, "NTSC");
			SYS_OUT("Setting Display Standard as <%s>\n", stdName);
			if (DVEVM_ST_SUCCESS != dvtb_writeSysFs(SYSFS_STANDARD, stdName))
			{
				SYS_ERROR("Unable to set the Display Standard as <%s> in the driver.\n", stdName);
				dvtb_close_vpbe(vpbe);
				return retval;
			}
			break;
	}
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_openV4l2Osd(DvevmStVpbeInfo *vpbe)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;

	ASSERT(vpbe != NULL);

	/* Just open FB channels and disable them */
	if (DVEVM_ST_FAIL == (vpbe->osd0Fd = open(OSD0_DEVICE, O_RDWR)))
	{
		SYS_PERROR("Unable to initialize OSD0_DEVICE(%s) \n", OSD0_DEVICE);
		return retval;
	}

	if (DVEVM_ST_FAIL == (vpbe->osd1Fd = open(OSD1_DEVICE, O_RDWR)))
	{
		SYS_PERROR("Unable to initialize OSD1_DEVICE device\n");
		return retval;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_ioctlV4l2Osd(DvevmStVpbeInfo *vpbe, unsigned int cmd, void *value)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;

	ASSERT(vpbe != NULL);
	ASSERT(value != NULL);

	switch(cmd)
	{
		case FBIOBLANK:
			if (ioctl(vpbe->osd0Fd, FBIOBLANK, *(int *)value) < 0)
			{
				SYS_PERROR("'FBIOBLANK' control call failed for device <%s>\n", OSD0_DEVICE);
				return retval;
			}
			else if (ioctl(vpbe->osd1Fd, FBIOBLANK, *(int *)value) < 0)
			{
				SYS_PERROR("'FBIOBLANK' control call failed for device <%s>\n", OSD1_DEVICE);
				return retval;
			}
			break;

		default:
			break;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_setV4l2OutputFmt(DvevmStVpbeInfo *vpbe, struct v4l2_format *fmt)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;

	ASSERT(vpbe != NULL);
	ASSERT(fmt != NULL);

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
	fmt->fmt.pix.bytesperline = vpbe->imagePitch;

	if (VID_FMT_YUV420SP == vpbe->pixelformat)
	{
		fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
	}
	else if (VID_FMT_UYVY == vpbe->pixelformat)
	{
		fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	}
	else if (VID_FMT_YUV422UVP == vpbe->pixelformat)
	{
//		fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_YUV422UVP;
		fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_NV16;
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
dvtb_vpbeSetup(DvevmStVpbeInfo *vpbe)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	struct v4l2_format fmt;
	struct v4l2_capability capability;
	unsigned int value = 1;

	ASSERT(vpbe != NULL);
	vpbe->buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	vpbe->videoFd = -1;
	vpbe->osd0Fd = -1;
	vpbe->osd1Fd = -1;
	
	/* Open OSD module if supported */
	if(NULL!=vpbe->setupFxn.openV4l2Osd)
	{
		if (DVEVM_ST_SUCCESS != vpbe->setupFxn.openV4l2Osd(vpbe))
		{
			SYS_PERROR("Unable to open OSD module\n");
			dvtb_close_vpbe(vpbe);
			return retval;
		}
	}

	/* Configure OSD module if supported*/
	if(NULL!=vpbe->setupFxn.ioctlV4l2Osd)
	{
		value = 1;
		if (DVEVM_ST_SUCCESS != vpbe->setupFxn.ioctlV4l2Osd(vpbe, FBIOBLANK, &value))
		{
			SYS_PERROR("Failed to blank FBIO!!!\n");
			dvtb_close_vpbe(vpbe);
			return retval;
		}
	}

	/* Open the VPBE channel */
	if (0 == vpbe->device[0])
		strcpy(vpbe->device, VID_DEVICE);
	if (DVEVM_ST_FAIL == (vpbe->videoFd = open(vpbe->device, O_RDWR, 0)))
	{
		SYS_PERROR("Unable to initialize video device : %s\n", vpbe->device);
		dvtb_close_vpbe(vpbe);
		return retval;
	}

	/* Query VPBE channel capabilities */
	if (ioctl(vpbe->videoFd, VIDIOC_QUERYCAP, &capability) < 0)
	{
		SYS_PERROR("Unable to query capability \n");
		dvtb_close_vpbe(vpbe);
		return retval;
	}
	else
	{
		if (!(capability.capabilities & V4L2_CAP_VIDEO_OUTPUT))
		{
			SYS_PERROR("Display Device is not capable to display output\n");
			dvtb_close_vpbe(vpbe);
			return retval;
		}

		if (!(capability.capabilities & V4L2_CAP_STREAMING))
		{
			SYS_PERROR("Display Device is not capable of streaming.\n");
			dvtb_close_vpbe(vpbe);
			return retval;
		}
	}

	/* Setup VPBE output */
	if (DVEVM_ST_SUCCESS != dvtb_setV4l2OutputDac(vpbe))
	{
		SYS_ERROR("Unable to set the Display Output in the driver.\n");
		dvtb_close_vpbe(vpbe);
		return retval;
	}

	/* Setup VPBE standard */
	if (DVEVM_ST_SUCCESS != dvtb_setV4l2OutputSandard(vpbe))
	{
		SYS_ERROR("Unable to set the Display Standard in the driver.\n");
		dvtb_close_vpbe(vpbe);
		return retval;
	}

	/* Setup VPBE any platform specific pre-format settings if applicable */
	if(NULL!=vpbe->setupFxn.setV4l2PreFmtConfiguration)
	{
		if (DVEVM_ST_SUCCESS != vpbe->setupFxn.setV4l2PreFmtConfiguration(vpbe))
		{
			dvtb_close_vpbe(vpbe);
			return retval;
		}
	}

	/* Setup VPBE output format */
	if (DVEVM_ST_SUCCESS != vpbe->setupFxn.setV4l2Fmt(vpbe, &fmt))
	{
		SYS_ERROR("Unable to set the Display format in the driver.\n");
		dvtb_close_vpbe(vpbe);
		return retval;
	}

	/* Setup VPBE any platform specific pre-format settings if applicable */
	if(NULL!=vpbe->setupFxn.setV4l2PostFmtConfiguration)
	{
		if (DVEVM_ST_SUCCESS != vpbe->setupFxn.setV4l2PostFmtConfiguration(vpbe))
		{
			dvtb_close_vpbe(vpbe);
			return retval;
		}
	}

	SYS_DEBUG("QuerDisWid %d, QuerDispHeight %d, QuerDispBytesPerLine %d, sizeimage = %u\n", fmt.fmt.pix.width, fmt.fmt.pix.height, fmt.fmt.pix.bytesperline, fmt.fmt.pix.sizeimage);

	switch (vpbe->opMode)
	{
		case DVEVM_ST_MMAP:
			vpbe->buf.memory = V4L2_MEMORY_MMAP;
			vpbe->qBuffFxn.setV4l2BuffConfig = vpbe->qBuffFxn.setV4l2MmapBuffConfig;
			vpbe->dqBuffFxn.getV4l2Buff      = vpbe->dqBuffFxn.getV4l2MmapBuff;

			if (DVEVM_ST_SUCCESS != vpbe->setupFxn.initV4l2OutputMmapBuffs(vpbe))
			{
				SYS_ERROR("Unable to initialize MMAP buffers\n");
				return retval;
			}

			break;

		case DVEVM_ST_USERBUFFER:
			vpbe->buf.memory = V4L2_MEMORY_USERPTR;
			vpbe->qBuffFxn.setV4l2BuffConfig = vpbe->qBuffFxn.setV4l2UserBuffConfig;
			vpbe->dqBuffFxn.getV4l2Buff      = vpbe->dqBuffFxn.getV4l2UserBuff;

			if (DVEVM_ST_SUCCESS != vpbe->setupFxn.initV4l2OutputUserBuffs(vpbe))
			{
				SYS_ERROR("Unable to initialize User buffers\n");
				return retval;
			}

			break;

		default:
			SYS_ERROR("Invalid Memory Allocation Mode!!!\n");
			return retval;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_vpbeDisplayStart(DvevmStVpbeInfo *vpbe)
{
	DvevmStRetCode retval = DVEVM_ST_SUCCESS;

	ASSERT(vpbe != NULL);

	if (ioctl(vpbe->videoFd, VIDIOC_STREAMON, &vpbe->buf.type) < 0)
	{
		SYS_PERROR("Unable to STREAMON video\n");
		dvtb_vpbeCleanup(vpbe);
		retval = DVEVM_ST_FAIL;
	}

	return retval;
}

void *
dvtb_getV4l2MmapBuff (DvevmStVpbeInfo *vpbe)
{
	return (vpbe->buff_info[vpbe->buf.index].start);
}

void *
dvtb_getV4l2UserBuff (DvevmStVpbeInfo *vpbe)
{
	return ((void *)vpbe->buf.m.userptr);
}

void *
dvtb_vpbeGetDisplayBuffer(DvevmStVpbeInfo *vpbe)
{
//	ASSERT(vpbe != NULL);

	if ((void *) vpbe->videoFd == NULL)
	{
		SYS_ERROR("Video display device is NULL\n");
		return NULL;
	}

	/* Get the empty buffer */
	if (ioctl(vpbe->videoFd, VIDIOC_DQBUF, &vpbe->buf) < 0)
	{
		SYS_PERROR("Unable to DQBUF.\n");
		dvtb_vpbeClose(vpbe);
	}
	else
	{
		return vpbe->dqBuffFxn.getV4l2Buff(vpbe);
	}

	return NULL;

}

DvevmStRetCode
dvtb_setV4l2MmapBuffConfig(DvevmStVpbeInfo *vpbe, void *buff)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	int i = 0, index = -1;

	vpbe->buf.m.offset = (unsigned long)buff;

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
	vpbe->buf.length = dvtb_getV4l2ImgSize(vpbe->imageWidth, vpbe->imageHeight, vpbe->pixelformat);

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_setV4l2UserBuffConfig(DvevmStVpbeInfo *vpbe, void *buff)
{
	vpbe->buf.m.offset = (unsigned long) buff;
	vpbe->buf.length = dvtb_getV4l2ImgSize(vpbe->imagePitch, vpbe->imageHeight, vpbe->pixelformat);

	return DVEVM_ST_SUCCESS;
}

/* Display one frame onto the frame buffer
 * Caller is expected to set vpbe->width and vpbe->height */
DvevmStRetCode
dvtb_vpbeDisplay(DvevmStVpbeInfo *vpbe, void *buff)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;

	ASSERT(vpbe != NULL);
	ASSERT(buff != NULL);

	if ( NULL == (void *)vpbe->videoFd )
	{
		SYS_ERROR("Video display device is NULL\n");
		return retval;
	}

	/* Configure buffer structure */
	if (DVEVM_ST_SUCCESS != vpbe->qBuffFxn.setV4l2BuffConfig(vpbe, buff))
	{
		dvtb_vpbeClose(vpbe);
		return retval;
	}
	
	/* Enqueue buffer */
	if (ioctl(vpbe->videoFd, VIDIOC_QBUF, &vpbe->buf) < 0)
	{
		SYS_PERROR("Unable to QBUF.\n");
		dvtb_vpbeClose(vpbe);
		return retval;
	}

	return DVEVM_ST_SUCCESS;
}


DvevmStRetCode
dvtb_vpbeClose(DvevmStVpbeInfo *vpbe)
{
	ASSERT(vpbe != NULL);

	if (-1 != vpbe->videoFd)
		if (ioctl(vpbe->videoFd, VIDIOC_STREAMOFF, &vpbe->buf.type) < 0)
		{
			SYS_PERROR("Unable to stream off video\n");
		}

	dvtb_vpbeCleanup(vpbe);

	return DVEVM_ST_SUCCESS;
}
