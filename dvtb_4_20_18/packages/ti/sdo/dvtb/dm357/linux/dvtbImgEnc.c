/*
 * dvtbImgEnc.c
 *
 * XDM0.9 Image Encode Interface implementation
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

#include "dvtbImgEnc.h"
#include "dvtbMemory.h"

static void
dvtb_imgEncInitDebug(IMGENC_Params *iep)
{
  SYS_DEBUG("\n<======== Image Encoder Initialize Debug Start ==========>\n");
  SYS_DEBUG("Max Height         : %d\n", (int) iep->maxHeight);
  SYS_DEBUG("Max Width          : %d\n", (int) iep->maxWidth);
  SYS_DEBUG("Max Scans          : %d\n", (int) iep->maxScans);
  SYS_DEBUG("Data Endianness    : %d\n", (int) iep->dataEndianness);
  SYS_DEBUG("Force Chroma Format: %d\n", (int) iep->forceChromaFormat);
  SYS_DEBUG("\n<======== Image Encoder Initialize Debug End ============>\n\n");
}

static void
dvtb_imgEncProcessDebug(IMGENC_OutArgs *ieo)
{
  SYS_DEBUG("\n<======== Image Encoder Process Debug Start ==========>\n");
  SYS_DEBUG("Extended Error     : %d\n", (int) ieo->extendedError);
  SYS_DEBUG("Bytes Generated    : %d\n", (int) ieo->bytesGenerated);
  SYS_DEBUG("Current AU         : %d\n", (int) ieo->currentAU);
  SYS_DEBUG("\n<======== Image Encoder Process Debug End ============>\n\n");
}

static void
dvtb_imgEncControlDebug(IMGENC_Status *ies)
{
  int i=0;

  SYS_DEBUG("\n<======== Image Encoder Control Debug Start ==========>\n");
  SYS_DEBUG("Extended Error     : %d\n", (int) ies->extendedError);
  SYS_DEBUG("Total AU           : %d\n", (int) ies->totalAU);
  SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ies->bufInfo.minNumInBufs);
  SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ies->bufInfo.minNumOutBufs);

  for (i=0; i<ies->bufInfo.minNumInBufs; i++)
    SYS_DEBUG("BUF-Min In Size  [%d]  : %d\n", i, (int) ies->bufInfo.minInBufSize[i]);

  for (i=0; i<ies->bufInfo.minNumOutBufs; i++)
    SYS_DEBUG("BUF-Min Out Size  [%d] : %d\n", i, (int) ies->bufInfo.minOutBufSize[i]);

  SYS_DEBUG("\n<======== Image Encoder Control Debug End ============>\n");
}

static void
dvtb_imgEncCleanup(DvevmStImgEncInfo *ienc)
{
  if (NULL != ienc->iencHdl)
  {
    IMGENC_delete(ienc->iencHdl);
    ienc->iencHdl = NULL;
  }

  dvtb_freeCmem(&ienc->inBuf);
  dvtb_freeCmem(&ienc->outBuf);
}

DvevmStRetCode
dvtb_imgEncInit(DvevmStImgEncInfo *ienc)
{
  ASSERT(ienc != NULL);
  ASSERT(ienc->ceHdl != NULL);
  ASSERT(ienc->iencName[0] != 0);

  dvtb_imgEncInitDebug(&ienc->iencParams);
  if (NULL == (ienc->iencHdl = IMGENC_create(ienc->ceHdl, ienc->iencName, &ienc->iencParams)))
  {
    SYS_ERROR("Unable to initialize Image Encoder\n");
    return DVEVM_ST_FAIL;
  }

  ienc->iencCmd = XDM_SETPARAMS;

  if (DVEVM_ST_FAIL == dvtb_imgEncControl(ienc))
  {
    dvtb_imgEncCleanup(ienc);
    SYS_ERROR("Unable to set encoder dynamic parameters\n");
    return DVEVM_ST_FAIL;
  }

  ienc->iencCmd = XDM_GETBUFINFO;
  if (DVEVM_ST_FAIL == dvtb_imgEncControl(ienc))
  {
    dvtb_imgEncCleanup(ienc);
    SYS_ERROR("Unable to get buffer info\n");
    return DVEVM_ST_FAIL;
  }

  if (DVEVM_ST_FAIL == dvtb_allocCmem(&ienc->inBuf))
  {
    SYS_ERROR("Unable to allocate memory for input buffer\n");
  }
  else if (DVEVM_ST_FAIL == dvtb_allocCmem(&ienc->outBuf))
  {
    SYS_ERROR("Unable to allocate memory for output buffer\n");
  }
  else
  {
    SYS_DEBUG("Image Encoder <%s> initialized\n", ienc->iencName);
    dvtb_imgEncInitDebug(&ienc->iencParams);
    return DVEVM_ST_SUCCESS;
  }

  return DVEVM_ST_FAIL;
}

DvevmStRetCode
dvtb_imgEncEncode(DvevmStImgEncInfo *ienc)
{
  XDM_BufDesc                 inBufDesc;
  XDM_BufDesc                 outBufDesc;
  XDAS_Int32                  status;

  DvevmStTime timeStmpBfrEnc, timeStmpAftrEnc;
  int processTime=0;

  ASSERT(ienc != NULL);
  ASSERT(ienc->ceHdl != NULL);
  ASSERT(ienc->iencHdl != NULL);
  ASSERT(ienc->inBuf.numBufs > 0);
  ASSERT(ienc->outBuf.numBufs > 0);

  inBufDesc.numBufs = ienc->inBuf.numBufs;
  inBufDesc.bufSizes = (XDAS_Int32 *) ienc->inBuf.bufSizes;
  inBufDesc.bufs = (XDAS_Int8 **) ienc->inBuf.bufs;

  outBufDesc.numBufs = ienc->outBuf.numBufs;
  outBufDesc.bufSizes = (XDAS_Int32 *) ienc->outBuf.bufSizes;
  outBufDesc.bufs = (XDAS_Int8 **) ienc->outBuf.bufs;

  timeStmpBfrEnc = dvtb_getTime();
  status = IMGENC_process(ienc->iencHdl, &inBufDesc, &outBufDesc, &ienc->iencInArgs, &ienc->iencOutArgs);
  timeStmpAftrEnc = dvtb_getTime();
//  printDspTrace();
  processTime = ((timeStmpAftrEnc.tv_sec*NUM_MICROSECS_IN_SEC)+timeStmpAftrEnc.tv_usec)-((timeStmpBfrEnc.tv_sec*NUM_MICROSECS_IN_SEC)+timeStmpBfrEnc.tv_usec);

#ifdef PERF
  SYS_PERF("**encode**, <imgenc %d>, Frame #%d, FrameType, %s, ProcessTime, %d, BytesGenerated, %d\n", ienc->iencDynParams.inputWidth, nFrames, "NA", processTime, ienc->iencOutArgs.bytesGenerated);

  //SYS_OUT("**encode**, <imgenc %d>, Frame #%d, FrameType, %d, ProcessTime, %d, BytesGenerated, %d\n", ve->vencDynParams.videnc_dynamicparams.inputWidth, nFrames, ve->vencOutArgs.videnc_OutArgs.encodedFrameType, processTime, ve->vencOutArgs.videnc_OutArgs.bytesGenerated);

  SYS_OUT("**encode**, <imgenc %d>, Frame #%d, FrameType, %s, ProcessTime, %d, BytesGenerated, %d\n", ienc->iencDynParams.inputWidth, nFrames, "NA", processTime, ienc->iencOutArgs.bytesGenerated);

//  SYS_OUT("**encode**, <videnc %d>, Frame #%d, %d, %d, %d\n", ve->vencDynParams.videnc_dynamicparams.inputWidth, nFrames, ve->vencOutArgs.videnc_OutArgs.encodedFrameType, processTime, ve->vencOutArgs.videnc_OutArgs.bytesGenerated);
#endif

  if (status != IMGENC_EOK)
  {
    SYS_ERROR("Image Encode Process failed (%d), Codec Error : %d\n", (int)
        status, (int) ienc->iencOutArgs.extendedError);
    return DVEVM_ST_FAIL;
  }

  dvtb_imgEncProcessDebug(&ienc->iencOutArgs);

  return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_imgEncControl(DvevmStImgEncInfo *ienc)
{
  int status, i;

  ASSERT(ienc != NULL);
  ASSERT(ienc->ceHdl != NULL);
  ASSERT(ienc->iencHdl != NULL);

  status = IMGENC_control(ienc->iencHdl, ienc->iencCmd, &ienc->iencDynParams, &ienc->iencStatus);
  if (IMGENC_EOK != status)
  {
    SYS_ERROR("Error (%d), Codec Error (%d) in image Encoder Control\n", status, (int)ienc->iencStatus.extendedError);
    return DVEVM_ST_FAIL;
  }
  else
  {
    SYS_DEBUG("Image Encode Control => Command : %d\n", ienc->iencCmd);
    SYS_DEBUG("Num AU               : %d\n", (int) ienc->iencDynParams.numAU);
    SYS_DEBUG("Input Chroma Format  : %d\n", (int) ienc->iencDynParams.inputChromaFormat);
    SYS_DEBUG("Input Height         : %d\n", (int) ienc->iencDynParams.inputHeight);
    SYS_DEBUG("Input Width          : %d\n", (int) ienc->iencDynParams.inputWidth);
    SYS_DEBUG("Capture Width        : %d\n", (int) ienc->iencDynParams.captureWidth);
    SYS_DEBUG("Generate Header      : %d\n", (int) ienc->iencDynParams.generateHeader);
    SYS_DEBUG("Q Value              : %d\n", (int) ienc->iencDynParams.qValue);

    if (XDM_GETBUFINFO == ienc->iencCmd)
    {
      ienc->inBuf.numBufs = ienc->iencStatus.bufInfo.minNumInBufs;
      ienc->outBuf.numBufs = ienc->iencStatus.bufInfo.minNumOutBufs;

      for (i=0; i<ienc->inBuf.numBufs; i++)
      {
        ienc->inBuf.bufSizes[i] = ienc->iencStatus.bufInfo.minInBufSize[i];
      }

      for (i=0; i<ienc->outBuf.numBufs; i++)
      {
        ienc->outBuf.bufSizes[i] = ienc->iencStatus.bufInfo.minOutBufSize[i];
      }
    }

    dvtb_imgEncControlDebug(&ienc->iencStatus);
    return DVEVM_ST_SUCCESS;
  }
}

DvevmStRetCode
dvtb_imgEncClose(DvevmStImgEncInfo *ienc)
{
  dvtb_imgEncCleanup(ienc);
  return DVEVM_ST_SUCCESS;
}
