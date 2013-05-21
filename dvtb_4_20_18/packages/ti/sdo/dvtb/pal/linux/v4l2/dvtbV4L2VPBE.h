/*
 * dvtbV4L2VPBE.h
 *
 * V4L2 VPBE driver Interface
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

#ifndef _DVEVM_ST_V4L2VPBE_H
#define _DVEVM_ST_V4L2VPBE_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

/* Kernel header file, prefix path comes from makefile */

//#include <video/davincifb_ioctl.h>
#include <linux/fb.h>
#include <linux/videodev.h>
#include <linux/videodev2.h>

#include "dvtbGlobal.h"
#include "dvtbDefs.h"

#define MIN_DISPLAY_BUFFERS MIN_USER_BUFFER_DISPLAY_BUFFERS
#define MAX_USER_BUFFERS 16
#define VID_DEVICE              "/dev/video2"
#define VID1_DEVICE             "/dev/video3"
#define OSD0_DEVICE             "/dev/fb0"
#define OSD1_DEVICE             "/dev/fb2"

#define SYSFS_STANDARD          "/sys/class/davinci_display/ch0/mode"
#define SYSFS_OUTPUT            "/sys/class/davinci_display/ch0/output"

#define D1_NTSC_WIDTH		(720)
#define D1_NTSC_HEIGHT	(480)
#define DEF_BPP         (16)            /* Default Bits Per Pixel */

#define MAX_DISPLAY_MMAP_BUFFERS 3

#define DEF_XRES                (1920)          /* Default X resolution */
#define DEF_YRES                (1080)          /* Default Y resolution */
#define DEF_VIDFRAME_SIZE       VID_FRAME_SIZE(DEF_XRES, DEF_YRES, DEF_BPP)

typedef enum
{
	DVEVM_ST_TV = 1,
	DVEVM_ST_LCD = 2,
	DVEVM_ST_DVI = 3
} DvevmStOutputDevice;

struct buf_info
{
	int index, length;
	void *start;
};

/*
 * Application should initialize the below function pointers either
 * to defaults OR platform specific implementation.
 * If a particular implementation is not applicable to the platform,
 * it should be initialized to NULL, unless specified otherwise.
 */
typedef struct VPBE_SetUp_Fxns
{
	DvevmStRetCode (*openV4l2Osd)(void *vpbe);
	DvevmStRetCode (*ioctlV4l2Osd)(void *vpbe, unsigned int cmd, void *value);
	DvevmStRetCode (*setV4l2PreFmtConfiguration)(void *vpbe);
	DvevmStRetCode (*setV4l2Fmt)(void *vpbe, void *fmt);
	DvevmStRetCode (*setV4l2PostFmtConfiguration)(void *vpbe);
	DvevmStRetCode (*initV4l2OutputMmapBuffs)(void *vpbe);
	DvevmStRetCode (*initV4l2OutputUserBuffs)(void *vpbe);
}VPBE_SetUp_Fxns;

typedef struct VPBE_Q_Buff_Fxns
{
	/* Platform specific implementation can override the below two functions */
	DvevmStRetCode (*setV4l2MmapBuffConfig)(void *vpbe, void *buff);
	DvevmStRetCode (*setV4l2UserBuffConfig)(void *vpbe, void *buff);

	/* VPBE configured function pointer. Need not be initialized */
	DvevmStRetCode (*setV4l2BuffConfig)(void *vpbe, void *buff);
}VPBE_Q_Buff_Fxns;

typedef struct VPBE_DQ_Buff_Fxns
{
	/* Platform specific implementation can override the below two functions */
	void * (*getV4l2MmapBuff)(void *vpbe);
	void * (*getV4l2UserBuff)(void *vpbe);

	/* VPBE configured function pointer. Need not be initialized */
	void * (*getV4l2Buff)(void *vpbe);
}VPBE_DQ_Buff_Fxns;

typedef struct
{
	char device[MAX_NAME_LEN]; /* Name of the VPBE device */

	int videoFd; /* FD for the VPBDE device */
	int osd0Fd;
	int osd1Fd; /* OSD Fds just to be diabled */

	unsigned int xres; /* FrameBuffer X resolution */
	unsigned int yres; /* FrameBuffer Y resolution */
	unsigned int bpp; /* BPP */
	unsigned int fbsize; /* Size in bytes of FrameBuffer/Video frame */

	unsigned int imageWidth; /* Width of image to be displayed */
	unsigned int imageHeight; /* Height of image to be displayed */
	unsigned int imagePitch; /* Pitch of image to be displayed */

	unsigned int maxBuffers;

	int cropEnable; /* set to 1 to enable croping feature */
	struct v4l2_crop crop; /* v4l2 structure for configuring crop capabilities */

	unsigned int y_uv_buffOffset; /* This indicates the offset between Y buffer and UV buffer. Used in User-buffer pointer implementation */
	unsigned int freeBuffIndex; /* Gives the free index value to Q using 'struct v4l2_buffer' type. Used in User-buffer pointer implementation */

	int rotate;
	int pixelformat;
	int scaling;
	char ch_mode[MAX_NAME_LEN];
	int output_idx;

	DvevmStDisplayStd dispStd; /* Display standard */
	DvevmStDisplayOutput dispOutput; /* Output type; composite/component/S-video etc */
	DvevmStOutputDevice outputDevice; /* Output to; TV/LCD etc */

	struct v4l2_requestbuffers req; /* VPBE format configuration structure */
	struct v4l2_buffer buf; /* VPBE buffer configuration structure */

	struct buf_info buff_info[20];

	DvevmStOperationMode opMode; /* Operation Mode 0: MMAP, 1: Userbuffer */
	char *userbufferptr[MAX_USER_BUFFERS]; /* Points to the user buffer arrays */
	unsigned int userbufferlen[MAX_USER_BUFFERS]; /* Size of user buffers */

	VPBE_SetUp_Fxns setupFxn;
	VPBE_Q_Buff_Fxns qBuffFxn;
	VPBE_DQ_Buff_Fxns dqBuffFxn;

} DvevmStVpbeInfo;

/*
 * VPBE Setup function pointer.
 * OMAP3530 has a platform specific setup implementation.
 */
DvevmStRetCode
(*dvtb_vpbeSetupPtr)(DvevmStVpbeInfo *vpbe); /* Function pointer for vpbe setup */

/* Default VPBE API functions */
DvevmStRetCode
dvtb_vpbeSetup(DvevmStVpbeInfo *vpbe);

void *
dvtb_vpbeGetDisplayBuffer(DvevmStVpbeInfo *vpbe);

DvevmStRetCode
dvtb_vpbeDisplay(DvevmStVpbeInfo *vpbe, void *buff);

DvevmStRetCode
dvtb_vpbeClose(DvevmStVpbeInfo *vpbe);

DvevmStRetCode
dvtb_vpbeDisplayStart(DvevmStVpbeInfo *vpbe);

/* Default VPBE Utility functions */
DvevmStRetCode
dvtb_initV4l2OutputUserBuffs(DvevmStVpbeInfo *vpbe);

DvevmStRetCode
dvtb_initV4l2OutputMmapBuffs(DvevmStVpbeInfo *vpbe);

DvevmStRetCode
dvtb_openV4l2Osd(DvevmStVpbeInfo *vpbe);

DvevmStRetCode
dvtb_ioctlV4l2Osd(DvevmStVpbeInfo *vpbe, unsigned int cmd, void *value);

DvevmStRetCode
dvtb_setV4l2OutputFmt(DvevmStVpbeInfo *vpbe, struct v4l2_format *fmt);

int
dvtb_getV4l2ImgSize(unsigned int pitch, unsigned int height, DvevmStVidFmt fmt);

void
dvtb_close_vpbe(DvevmStVpbeInfo *vpbe);

void *
dvtb_getV4l2MmapBuff (DvevmStVpbeInfo *vpbe);

void *
dvtb_getV4l2UserBuff (DvevmStVpbeInfo *vpbe);

DvevmStRetCode
dvtb_setV4l2MmapBuffConfig(DvevmStVpbeInfo *vpbe, void *buff);

DvevmStRetCode
dvtb_setV4l2UserBuffConfig(DvevmStVpbeInfo *vpbe, void *buff);

DvevmStRetCode
dvtb_writeSysFs(char *fileName, char *val);

#endif
