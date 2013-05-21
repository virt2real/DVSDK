/*
 * dvtbV4L2VPFE.h
 *
 * V4L2 VPFE driver Interface
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

#ifndef _DVEVM_ST_V4L2VPFE_H
#define _DVEVM_ST_V4L2VPFE_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <linux/fb.h>
#include <asm/types.h>

/* Kernel header file, prefix path comes from makefile */
#include <linux/videodev2.h>
//#include <media/davinci/videohd.h>
#define VPFE_STD_AUTO           ((v4l2_std_id)(0x1000000000000000ULL))


#include "dvtbGlobal.h"
#include "dvtbDefs.h"

#define VIDCAP_DEVICE           "/dev/video0"

#define DEF_BPP                 (16)        /* Default Bits Per Pixel */

#define NTSC_WIDTH              (720)
#define NTSC_HEIGHT             (480)
#define PAL_WIDTH               (720)
#define PAL_HEIGHT              (576)

#define MIN_CAP_BUFS            (2)     /* Minimum number of capture buffers */

/* Describes a capture frame buffer */
typedef struct VideoBuffer
{
	void *start;
	size_t length;
	int offset;
	int index;
} VideoBuffer;

typedef enum
{
	VID_STD_AUTO,
	VID_STD_NTSC,
	VID_STD_PAL,
	VID_STD_SECAM,
	VID_STD_NA,
	VID_STD_720SP_60,
	VID_STD_1080I_60,
} DvevmStVidStd;

typedef struct
{
	char device[MAX_NAME_LEN]; /* Name of the VPFE device */

	int capFd; /* FD of the VPFE device */

	DvevmStVidStd capStd; /* Display standard of input video */
	DvevmStVidFmt capFmt; /* Vpfe format to capture to */
	int input; /* Video input: composite or s-video */
	int field;

	int cropEnable; /* set to 1 to enable croping feature */
	struct v4l2_crop crop; /* v4l2 structure for configuring crop capabilities */

	int hdCapStdIndex; /* HD video standard index: driver/platform dependent */
	int hdCaptureFactor; /* factors the capture rate by the given field value */

	int capWidth; /* Width of frame to be captured */
	int capHeight; /* Height of frame to be captured */

	int capSize; /* Size of frame captured */

	int numBufs; /* Number of buffers mmap-ed */
	int opMode; 	// 0: MMAp
			// 1: User Pointer
	DvevmStBool isStreamOn;

	VideoBuffer *buffers; /* Buffers for captured frames */
	struct v4l2_buffer buf; /* Information about the next frame */
} DvevmStVpfeInfo;

DvevmStRetCode
dvtb_vpfeSetup(DvevmStVpfeInfo *vpfe);

DvevmStRetCode
dvtb_vpfeGetNextBuffer(DvevmStVpfeInfo *vpfe);

DvevmStRetCode
dvtb_vpfeReturnBuffer(DvevmStVpfeInfo *vpfe);

DvevmStRetCode
dvtb_vpfeClose(DvevmStVpfeInfo *vpfe);

DvevmStRetCode
dvtb_vpfeCaptureStart(DvevmStVpfeInfo *vpfe);

DvevmStRetCode
dvtb_v4l2UserAlloc(DvevmStVpfeInfo *vpfe, int count);

DvevmStRetCode
dvtb_v4l2MmapAlloc(DvevmStVpfeInfo *vpfe, int count);
#endif
