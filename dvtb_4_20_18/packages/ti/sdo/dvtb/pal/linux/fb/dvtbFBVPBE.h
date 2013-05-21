/*
 * dvtbFBVPBE.h
 *
 * Frame Buffer VPBE Interface
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

#ifndef _DVEVM_ST_VIDEO_H
#define _DVEVM_ST_VIDEO_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <linux/fb.h>

#include "dvtbGlobal.h"

#define OSD0_DEVICE             "/dev/fb/0"
#define OSD1_DEVICE             "/dev/fb/1"
#define ATTR_DEVICE             "/dev/fb/2"
#define VID0_DEVICE             "/dev/fb/3"

#define DEF_IMAGEWIDTH          (720)
#define DEF_IMAGEHEIGHT         (480)
#define D1_NTSC_WIDTH		  (720)
#define D1_NTSC_HEIGHT		  (480)
#define DEF_BPP                 (16)            /* Default Bits Per Pixel */

#define DEF_VIDFRAME_SIZE       VID_FRAME_SIZE(D1_NTSC_WIDTH, D1_NTSC_HEIGHT, DEF_BPP)

typedef struct
{
	char device[MAX_NAME_LEN]; /* Name of the VPBE device */

	int videoFd; /* FD for the VPBE device */
	int format;
	unsigned int screenWidth; /* Image x-resolution 	 */
	unsigned int screenHeight; /* Image y-resolution 	 */
	unsigned display_LineLength; /* Screen linelength 	*/
	unsigned display_yres_virtual; /* Screen y-resolution	*/
	unsigned int bpp; /* bits per pixel*/
	unsigned int imageWidth; /* Width of image to be displayed */
	unsigned int imageHeight; /* Height of image to be displayed */
	char *fbmap; /* mmap-ed pointer to the FB */
} DvevmStVpbeInfo;

DvevmStRetCode
(*dvtb_vpbeSetupPtr)(DvevmStVpbeInfo *vpbe); /* Function pointer for vpbe setup */

DvevmStRetCode
dvtb_vpbeSetup(DvevmStVpbeInfo *vpbe);

DvevmStRetCode
dvtb_vpbeDisplay(DvevmStVpbeInfo *vpbe, char *buff);

DvevmStRetCode
dvtb_vpbeClose(DvevmStVpbeInfo *vpbe);

#endif
