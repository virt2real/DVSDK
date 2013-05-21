/*
 * dvtbUtils.h
 *
 * DVTB(wince) Utility interfaces
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

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "dvtbGlobal.h"
#include "dvtbMain.h"
#include "dvtbParam.h"

DvevmStRetCode
dvtb_getFileSize(FILE *fp, unsigned int *fileSize);

DvevmStRetCode
dvtb_fileRead(FILE *fp, char *buff, int readData, int *nBytes);

DvevmStRetCode
dvtb_fileWrite(FILE *fp, char *buff, int writeData);

DvevmStRetCode
dvtb_fileOpen(FILE **fp, const char *restrict filename, const char *restrict mode);

void
dvtb_fileClose(FILE **sourceFp, FILE **targetFp);

//DvevmStRetCode
//dvtb_displayBuffer(DvevmStVpbeInfo *vpbe, char *buff, int buffSize);

DvevmStRetCode
dvtb_byteSwapBitStream(char *inout_p, short size);

DvevmStRetCode
dvtb_stereoToMono(short *in_stereoSamples, short *out_monoSamples, int numSamples);

DvevmStRetCode
dvtb_inputFileToProcessbuff(char *in_samples, char *out_processbuff, int numSamples);

DvevmStRetCode
dvtb_inputFileToG722Processbuff(short *in_samples, short *out_processbuff, int numSamples);

void
dvtb_convert420pTo420sp(unsigned char *inBuf, unsigned char *outBuf, int width, int height);

void
dvtb_convert420spTo420p(unsigned char *inBuf, unsigned char *outBuf, int width, int height);

void
dvtb_convert422pTo422sp(unsigned char *inBuf, unsigned char *outBuf, int width, int height);
void
dvtb_convert422spTo422p(unsigned char *inBuf, unsigned char *outBuf, int width, int height);

void
dvtb_convert420spTo422sp(unsigned char *inBuf, unsigned char *outBuf, int width, int height);
void
dvtb_convert422spTo420sp(unsigned char *inBuf, unsigned char *outBuf, int width, int height);

void
dvtb_convertSplit420spTo422sp(unsigned char *inBufLuma, unsigned char *inBufChroma, unsigned char *outBuf, int width, int height, int pitch);

DvevmStRetCode
dvtb_separateCbCrPixels(XDAS_Int8 *CbCr_data, XDAS_Int8 *Chroma_buf[2], XDAS_Int32 height, XDAS_Int32 width, XDAS_UInt16 pitch);

void
dvtb_startMessage(int classType, char *string, DvevmStBool useAlgorithm, DvevmStBool fileBased);

void
dvtb_exitMessage(int classType, char *string, DvevmStBool useAlgorithm, DvevmStBool fileBased, DvevmStBool usecaseFailed);

DvevmStRetCode
dvtb_openSrcTrgFromInputFile(FILE *in_inputFile, FILE **out_sourceFp, FILE **out_targetFp, int in_maxinstances);

#endif

