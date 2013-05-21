/*
 * dvtbFBVPBE.c
 *
 * Frame Buffer VPBE Interface implementation
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

#include "dvtbFBVPBE.h"
#include <video/davincifb_ioctl.h>
#define UYVY_BLACK               0x10801080

struct fb_var_screeninfo fb_backup = { 0 };

static void
dvtb_vpbeCleanup(DvevmStVpbeInfo *vpbe)
{

	if (vpbe->fbmap != NULL)
		munmap(vpbe->fbmap, vpbe->display_LineLength * vpbe->display_yres_virtual);

	if (vpbe->videoFd != DVEVM_ST_FAIL)
	{
		/* Restore original screen info */
		if (ioctl(vpbe->videoFd, FBIOPUT_VSCREENINFO, &fb_backup) == -1)
		{
			SYS_PERROR("Failed FBIOPUT_VSCREENINFO, Can't restore original screen info\n");
		}
		memset(&fb_backup, 0, sizeof(struct fb_var_screeninfo));
		close(vpbe->videoFd);
	}

	vpbe->fbmap = NULL;
	vpbe->videoFd = DVEVM_ST_FAIL;
}

DvevmStRetCode
dvtb_vpbeSetup(DvevmStVpbeInfo *vpbe)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	struct fb_var_screeninfo fb;
	struct fb_fix_screeninfo fb_fix;
	int osd;
	ASSERT(vpbe != NULL);

	/* Disable osd0, osd1 devices */
	osd = open(OSD0_DEVICE, O_RDWR);
	ioctl(osd, FBIOBLANK, 1);
	close(osd);

	osd = open(OSD1_DEVICE, O_RDWR);
	ioctl(osd, FBIOBLANK, 1);
	close(osd);

	if (0 == vpbe->device[0])
		strcpy(vpbe->device, VID0_DEVICE);

	if (DVEVM_ST_FAIL == (vpbe->videoFd = open(vpbe->device, O_RDWR)))
	{
		SYS_PERROR("Unable to initialize video device : %s\n", vpbe->device);
		return DVEVM_ST_FAIL;
	}

	if (DVEVM_ST_FAIL == ioctl(vpbe->videoFd, FBIOGET_VSCREENINFO, &fb))
	{
		SYS_PERROR("Unable to get variable screen information for device : %s\n", vpbe->device);
		return DVEVM_ST_FAIL;
	}

	fb_backup = fb;

	fb.xres = vpbe->screenWidth; /* D1_width*/
	fb.yres = vpbe->screenHeight; /* D1_height*/
	fb.bits_per_pixel = vpbe->bpp;
	fb.xres_virtual = vpbe->screenWidth;
	fb.yres_virtual = vpbe->screenHeight;
	fb.nonstd = 1;

	if (ioctl(vpbe->videoFd, FBIOPUT_VSCREENINFO, &fb) == -1)
	{
		SYS_PERROR("Failed FBIOPUT_VSCREENINFO\n");
		return DVEVM_ST_FAIL;
	}

	if (fb.xres != vpbe->screenWidth || fb.yres != vpbe->screenHeight || fb.bits_per_pixel != vpbe->bpp)
	{
		SYS_PERROR("Failed to get the requested screen size:\n");
		return DVEVM_ST_FAIL;
	}

	if (DVEVM_ST_FAIL == ioctl(vpbe->videoFd, FBIOGET_FSCREENINFO, &fb_fix))
	{
		SYS_PERROR("Unable to get fixed screen information for device : %s\n", vpbe->device);
		return DVEVM_ST_FAIL;
	}

	vpbe->display_LineLength = fb_fix.line_length;
	vpbe->display_yres_virtual = fb.yres_virtual;
	if (DVEVM_ST_FAIL == (int) (vpbe->fbmap = mmap(NULL, vpbe->display_LineLength * vpbe->display_yres_virtual, PROT_READ | PROT_WRITE, MAP_SHARED, vpbe->videoFd, 0)))
	{
		SYS_PERROR("Unable to map Frame Buffer memory to user pointer\n");
		printf("\nErrno = %d\n", errno);
		dvtb_vpbeCleanup(vpbe);
	}
	else
	{
		retval = DVEVM_ST_SUCCESS;
	}

	/*initialise screen as BLACK*/
	memset(vpbe->fbmap, UYVY_BLACK, vpbe->display_LineLength * vpbe->display_yres_virtual);

	return retval;
}

/* Display one frame onto the frame buffer
 * Caller is expected to set vpbe->width and vpbe->height */

DvevmStRetCode
dvtb_vpbeDisplay(DvevmStVpbeInfo *vpbe, char *buff)
{
	unsigned int arg = 0;
	char * dst;
	ASSERT(vpbe->videoFd != DVEVM_ST_FAIL);
	ASSERT(vpbe->fbmap != NULL);

	if (DVEVM_ST_FAIL == ioctl(vpbe->videoFd, FBIO_WAITFORVSYNC, &arg))
	{
		SYS_PERROR("Unable to wait for VSYNC for VPBE device <%s>\n", vpbe->device);
		return DVEVM_ST_FAIL;
	}

	int xoffset = (vpbe->screenWidth - vpbe->imageWidth) / 2 * (vpbe->bpp / 8);
	int yoffset = ((vpbe->screenHeight - vpbe->imageHeight) / 2) & ~1;
	int lineno;

	/* Truncate if frame buffer higher than display buffer */
	if (yoffset < 0)
	{
		yoffset = 0;
	}

	dst = vpbe->fbmap;
	dst += yoffset * vpbe->display_LineLength + xoffset;

	for (lineno = 0; lineno < vpbe->imageHeight && lineno < vpbe->screenHeight; lineno++)
	{
		memcpy(dst, buff, vpbe->imageWidth * (vpbe->bpp / 8));
		dst += vpbe->display_LineLength;
		buff += vpbe->imageWidth * (vpbe->bpp / 8);
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_vpbeClose(DvevmStVpbeInfo *vpbe)
{
	ASSERT(vpbe != NULL);
	dvtb_vpbeCleanup(vpbe);

	return DVEVM_ST_SUCCESS;
}
