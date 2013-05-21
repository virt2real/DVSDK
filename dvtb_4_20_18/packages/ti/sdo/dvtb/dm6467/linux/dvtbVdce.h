/*
 * dvtbVdce.h
 *
 * VDCE driver interface
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

#ifndef _DVEVM_ST_VDCE_H
#define _DVEVM_ST_VDCE_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <linux/davinci_vdce.h>

#include "dvtbGlobal.h"

#define VDCE_DEVICE             "/dev/DavinciHD_vdce"

typedef struct
{
	char device[MAX_NAME_LEN]; /* Name of the VDCE device */
	int videoFd; /* FD for the VDCE device */
	int inputHeight;
	int inputWidth;
	int inputPitch;
	int outputHeight;
	int outputWidth;
	int outputPitch;
	unsigned char *inputBuffer;
	int inputBufferSize;
	unsigned char *outputBuffer;
	int outputBufferSize;
	int inFormat; //1-> 420; 2-> 422
	int vdceOpened;
	vdce_address_start_t runtime_params;
} DvevmStVdceInfo;

DvevmStRetCode
dvtb_vdceSetup(DvevmStVdceInfo *vdce, int inputHeight, int inputWidth, int inputPitch, int inFormat);

DvevmStRetCode
dvtb_vdceopen(DvevmStVdceInfo *vdce);

DvevmStRetCode
dvtb_vdceConvert420to422(DvevmStVdceInfo *vdce);

DvevmStRetCode
dvtb_vdceConvert422to420(DvevmStVdceInfo *vdce);

DvevmStRetCode
dvtb_vdceClose(DvevmStVdceInfo *vdce);

#endif
