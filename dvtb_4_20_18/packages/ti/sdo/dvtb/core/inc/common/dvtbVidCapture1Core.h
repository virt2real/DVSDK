/*
 * dvtbVidCapture1Core.h
 *
 * Interfaces for DVTB(Common) XDM1.0 Video Encode related Core Functions
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

#ifndef _DVEVM_ST_VID_CAP1_CORE_H
#define _DVEVM_ST_VID_CAP1_CORE_H

#include "dvtbGlobal.h"
#include "dvtbVidEnc1.h"
#include "dvtbDefs.h"
#include "dvtbV4L2VPFE.h"

//Prints "Number of frames" processed
void
dvtb_vidEnc1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames);

//Initialize elements of structure DvevmStVidEnc1Info
void
dvtb_vidEnc1InitPtrs(DvevmStVidEnc1Info *ve);

//Initialize CE and codec instance
DvevmStRetCode
dvtb_vidEnc1HanInit(DvevmStVidEnc1Info *ve, char *engName);

//Close CE and codec instance
void
dvtb_vidEnc1HanClose(DvevmStVidEnc1Info *ve, char *engName);

//Allocate input buffers
DvevmStRetCode
dvtb_vidEnc1InBuffAlloc(DvevmStXdmBuffer *inBuf, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased);

//Allocate output buffers
DvevmStRetCode
dvtb_vidEnc1OutBuffAlloc(DvevmStXdmBuffer *outBuf, XDM_BufDesc *outBufDesc);

//Get input either from driver capture or file read
DvevmStRetCode
dvtb_vidEnc1ReadInput(DvevmStVpfeInfo *vpfe, FILE *fp, IVIDEO1_BufDescIn *inBufDesc, DvevmStBool fileBased);

//Encode frame
DvevmStRetCode
dvtb_vidEnc1EncProcess(DvevmStVidEnc1Info *ve, int *encDuration);

#endif

