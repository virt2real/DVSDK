/*
 * dvtbResizer.h
 *
 * Resizer Interface
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

#ifndef _DVEVM_ST_V4L2VPRSZ_H
#define _DVEVM_ST_V4L2VPRSZ_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <asm/types.h>

#include <linux/videodev.h>
#include <linux/omap_resizer.h>

#include "dvtbGlobal.h"
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ivideo.h>

#define VIDRESIZE_DEVICE        "/dev/omap-resizer"
#define ADDRESSALIGN 65536*32768
typedef struct
{
	char resizeDevice[MAX_NAME_LEN]; /* Name of the resizeDevice */
	struct rsz_params params;

	int rszEnable;
	int rszPixFmt; 
	int rszInWidth; 
	int rszInHeight; 
	int rszInPitch; 
	int rszOutWidth; 
	int rszOutHeight;
	int rszOutPitch;
	
	int rszInputFormat; 
	int rszFd; /* FD of the Resizer device */
} DvevmStResizerInfo;

DvevmStRetCode
dvtb_resizerSetup(DvevmStResizerInfo *vpRsz);

DvevmStRetCode
dvtb_resizerOutBuffAlloc(DvevmStResizerInfo *vpRsz, DvevmStXdmBuffer *rszBuf ,IVIDEO1_BufDescIn *rszBufDesc);

DvevmStRetCode
dvtb_configureResizer(DvevmStResizerInfo *vpRsz);

DvevmStRetCode
dvtb_resizeImage(DvevmStResizerInfo *vpRsz, IVIDEO1_BufDescIn *inBuff, IVIDEO1_BufDescIn *outBuff);

DvevmStRetCode
dvtb_resizeBuff(DvevmStResizerInfo *vpRsz, char *inBuff, int inBuffSize, char *outBuff, int outBuffSize);

DvevmStRetCode
dvtb_resizerClose(DvevmStResizerInfo *vpRsz);

#endif
