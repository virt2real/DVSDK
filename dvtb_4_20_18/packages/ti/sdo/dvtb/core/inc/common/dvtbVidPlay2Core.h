/*
 * dvtbVidPlay2Core.h
 *
 * Interfaces for DVTB(Common) XDM1.0 Video Decode related Core Functions
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

#ifndef _DVEVM_ST_VID_PLAY2_CORE_H
#define _DVEVM_ST_VID_PLAY2_CORE_H

#include "dvtbGlobal.h"
#include "dvtbParam.h"
#include "dvtbMemory.h"
#include "dvtbVidPlay2.h"

//Prints "Number of frames" processed
void
dvtb_vidDec2ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames);

//Initialize elements of DvevmStVidDec2Info structure
void
dvtb_vidDec2InitPtrs(DvevmStVidDec2Info *vd);

//Initialize CE and Codec Instance
DvevmStRetCode
dvtb_vidDec2HanInit(DvevmStVidDec2Info *vd, char *engName);

//Free output buffers
DvevmStRetCode
dvtb_vidDec2DeInitOutBuffers(DvevmStVidDec2Info *vd);

//Free Allocated buffers, Close Codec instance and CE
void
dvtb_vidDec2HanClose(DvevmStVidDec2Info *vd, char *engName);

//Allocate input Buffer
DvevmStRetCode
dvtb_vidDec2InBuffAlloc(DvevmStXdmBuffer *inBuf, XDM1_BufDesc *inBufDesc, int minNumInBufs);

//Find Available output buffer
DvevmStBufElement*
dvtb_vidDec2AllocOutBuffer(DvevmStVidDec2Info *vd);

//Decode frame/field
DvevmStRetCode
dvtb_vidDec2DecProcess(DvevmStVidDec2Info *vd, int *decDuration);

//Allocate first out buffer
DvevmStRetCode
dvtb_vidDec2InitFirstOutBuffer(DvevmStVidDec2Info *vd);

//Allocate and Initialize output buffers
DvevmStRetCode
dvtb_vidDec2InitAllOutBuffers(DvevmStVidDec2Info *vd);

//Release output buffers based on the free ID
DvevmStRetCode
dvtb_vidDec2ReleaseBuffers(DvevmStVidDec2Info *vd, unsigned int freeBufIds[]);

//Display output frame
DvevmStRetCode
dvtb_vidDec2DisplayOutputData(DvevmStGlobalParams *g, char *in_buff, int size);

//Process output of decoder
DvevmStRetCode
dvtb_vidDec2ProcessOutBuff(DvevmStGlobalParams *g, DvevmStVidDec2Info *vd, FILE *fp, DvevmStBool fileBased, int nFrames, int *displayFrame);

//Get remaining displayable frames from codec
DvevmStRetCode
dvtb_vidDec2Flush(DvevmStGlobalParams *g, DvevmStVidDec2Info *vd, FILE *fp, DvevmStBool fileBased, int nFrames, int *displayFrame);

#endif

