/*
 * dvtbDM365Utils.h
 *
 * DM365 Specific utility function interfaces
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

#ifndef DM365_UTILS_H
#define DM365_UTILS_H

#include <stdio.h>
#include "dvtbGlobal.h"
#include "dvtbMain.h"
#include "dvtbParam.h"
#include "dvtbMemory.h"
#include <pthread.h>
#include "dvtbV4L2VPBEFeatures.h"
#include "dvtbV4L2VPFEFeatures.h"

DvevmStRetCode
dvtb_mMap_displayBuffer(DvevmStVpbeInfo *vpbe, int outputChromaFormat, IVIDEO1_BufDesc *vdo, int numBufs);

int
dvtb_getXdmFmt(DvevmStVidFmt fmt);

int
dvtb_getVidFmt(int fmt);

DvevmStRetCode
dvtb_extendedVpbeSetup(DvevmStVpbeInfo *vpbe);

DvevmStRetCode
dvtb_extendedVpfeSetup(DvevmStVpfeInfo *vpfe);

void
dvtb_captureClose(DvevmStVpfeInfo *vpfe, DvtbPreviewerInfo *vpPrvw, DvtbResizerInfo *vpRsz);

DvevmStRetCode
dvtb_captureSetup(DvevmStVpfeInfo *vpfe, DvtbPreviewerInfo *vpPrvw, DvtbResizerInfo *vpRsz);

DvevmStRetCode
dvtb_userBuffPtr_displayBuffer(DvevmStVpbeInfo *vpbe, int outputChromaFormat, IVIDEO1_BufDesc *vdo, int numBufs);

DvevmStRetCode
dvtb_userBuffPtr_queueBuffer(DvevmStVpbeInfo *vpbe, int outputChromaFormat, IVIDEO1_BufDesc *vdo, int numBufs);

void
dvtb_setOutBuffInUse(DvevmStOutBuffsInUse (*dispBufArray)[], int outputID, void * buf);

void
dvtb_registerOutBuffToFree(DvevmStOutBuffsInUse (*dispBufArray)[], XDAS_Int32 (*freeBufID)[]);

void
dvtb_clearOutBuffInUse(DvevmStOutBuffsInUse (*dispBufArray)[], DvevmStBufElement (*outBufArray)[], void * address);

void
dvtb_freeOutBuffInUse(DvevmStOutBuffsInUse (*dispBufArray)[], DvevmStBufElement (*outBufArray)[]);

DvevmStRetCode
dvtb_vidDec2DeInitOutBuffers_dm365(DvevmStBufElement (*outBufArray)[], int totBuf);

DvevmStBufElement*
dvtb_vidDec2AllocOutBuffer_dm365(DvevmStBufElement (*outBufArray)[], int totBuf, int *buffIdSearchStart);

DvevmStRetCode
dvtb_vidDec2ReleaseOutBuffers(DvevmStBufElement (*outBufArray)[], XDAS_Int32 (*freeBufID)[]);

DvevmStRetCode
dvtb_vidDec2AllocInBuff(DvevmStXdmBuffer *inBuf, XDM1_BufDesc *inBufDesc, int minNumInBufs);

DvevmStRetCode
dvtb_vidDec2InitFirstOutBuffer_dm365(DvevmStBufElement (*outBufArray)[], VIDDEC2_Status *viddecStatus, int *totBuf);

DvevmStRetCode
dvtb_vidDec2InitAllOutBuffers_dm365(DvevmStBufElement (*outBufArray)[], VIDDEC2_Status *viddecStatus, int *totBuf, int maxBufs);

DvevmStRetCode
dvtb_vidDec2SetUpVPBE(DvevmStVpbeInfo *vpbe, VIDDEC2_Status *viddecStatus, VIDDEC2_OutArgs *viddecOutArgs, VIDDEC2_InArgs *viddecInArgs, VIDDEC2_Params* viddecParams, VIDDEC2_DynamicParams *viddecDynParams, DvevmStOutBuffsInUse (*dispBufArray)[]);

DvevmStRetCode
dvtb_vidDec2ProcessOutBuff_dm365(DvevmStVpbeInfo *vpbe, VIDDEC2_Status *viddecStatus, VIDDEC2_OutArgs *viddecOutArgs, VIDDEC2_InArgs *viddecInArgs, VIDDEC2_Params* viddecParams, VIDDEC2_DynamicParams *viddecDynParams, DvevmStOutBuffsInUse (*dispBufArray)[], DvevmStBufElement (*outBufArray)[], FILE * targetFp, int *nFrames, int rotated);

void
dvtb_vidDec2StartMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, char *str);

void
dvtb_vidDec2ProcessEndMessage_dm365(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames, char *str);

void
dvtb_vidDec2ExitMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, DvevmStBool usecaseFailed, char *str);

DvevmStRetCode
dvtb_vidEnc1ReadInput_dm365(DvevmStVpfeInfo *vpfe, FILE *fp, IVIDEO1_BufDescIn *inBufDesc, int fileBased);

DvevmStRetCode
dvtb_writeOutputData(IVIDEO1_BufDesc *displayBuf, int width, int height, FILE *fOutFile);

#endif

