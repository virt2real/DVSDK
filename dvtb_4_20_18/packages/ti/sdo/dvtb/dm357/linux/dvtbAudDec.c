/*
 * dvtbAudDec.c
 *
 * XDM0.9 Audio Decode Interface
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

#include "dvtbAudDec.h"
#include "dvtbMemory.h"

static void
dvtb_audDecInitDebug(AUDDEC_Params *adp)
{
  SYS_DEBUG("\n<======== Audio Decoder Initialize Debug Start ==========>\n");
  SYS_DEBUG("Max Sample Rate    : %d\n", (int) adp->maxSampleRate);
  SYS_DEBUG("Max Bit Rate       : %d\n", (int) adp->maxBitrate);
  SYS_DEBUG("Max No of Channels : %d\n", (int) adp->maxNoOfCh);
  SYS_DEBUG("Data Endianness    : %d\n", (int) adp->dataEndianness);
  SYS_DEBUG("\n<======== Audio Decoder Initialize Debug End ============>\n\n");
}

static void
dvtb_audDecProcessDebug(AUDDEC_OutArgs *ado)
{
  SYS_DEBUG("\n<======== Audio Decoder Process Debug Start ==========>\n");
  SYS_DEBUG("Extended Error     : %d\n", (int) ado->extendedError);
  SYS_DEBUG("Bytes Consumed     : %d\n", (int) ado->bytesConsumed);
  SYS_DEBUG("\n<======== Audio Decoder Process Debug End ============>\n");
}

static void
dvtb_audDecControlDebug(AUDDEC_Status *ads)
{
  SYS_DEBUG("\n<======== Audio Decoder Control Debug Start ==========>\n");
  SYS_DEBUG("Extended Error     : %d\n", (int) ads->extendedError);
  SYS_DEBUG("Bit Rate           : %d\n", (int) ads->bitRate);
  SYS_DEBUG("Sample Rate        : %d\n", (int) ads->sampleRate);
  SYS_DEBUG("Num Channels       : %d\n", (int) ads->numChannels);
  SYS_DEBUG("Num LFE Channels   : %d\n", (int) ads->numLFEChannels);
  SYS_DEBUG("Output Format      : %d\n", (int) ads->outputFormat);
  SYS_DEBUG("Auto Position      : %d\n", (int) ads->autoPosition);
  SYS_DEBUG("Fast Fwd Len       : %d\n", (int) ads->fastFwdLen);
  SYS_DEBUG("Frame Len          : %d\n", (int) ads->frameLen);
  SYS_DEBUG("Output Bits/Sample : %d\n", (int) ads->outputBitsPerSample);
  SYS_DEBUG("BUF-Min In Bufs    : %d\n", (int) ads->bufInfo.minNumInBufs);
  SYS_DEBUG("BUF-Min Out Bufs   : %d\n", (int) ads->bufInfo.minNumOutBufs);
  SYS_DEBUG("BUF-Min In Size    : %d\n", (int) ads->bufInfo.minInBufSize[0]);
  SYS_DEBUG("BUF-Min Out Size   : %d\n", (int) ads->bufInfo.minOutBufSize[0]);
  SYS_DEBUG("\n<======== Audio Decoder Control Debug End ============>\n");
}

static void
dvtb_audDecCleanup(DvevmStAudDecInfo *ad)
{
  if (NULL != ad->adecHdl)
    AUDDEC_delete(ad->adecHdl);

  if (NULL != ad->inBuf.start)
    Memory_contigFree(ad->inBuf.start, ad->inBuf.size);

  if (NULL != ad->outBuf.start)
    Memory_contigFree(ad->outBuf.start, ad->outBuf.size);

  ad->inBuf.start = NULL;
  ad->outBuf.start = NULL;
}

DvevmStRetCode
dvtb_audDecInit(DvevmStAudDecInfo *ad)
{
  ASSERT(ad != NULL);
  ASSERT(ad->ceHdl != NULL);
  ASSERT(ad->adecName[0] != 0);

  if (NULL == (ad->adecHdl = AUDDEC_create(ad->ceHdl, ad->adecName, &ad->adecParams)))
  {
    SYS_ERROR("Unable to initialize Audio Decoder\n");
  }
  else if (NULL == (ad->inBuf.start = Memory_contigAlloc(ad->inBuf.size, Memory_DEFAULTALIGNMENT)))
  {
    SYS_ERROR("Unable to allocate memory for In Buffer\n");
  }
  else if (NULL == (ad->outBuf.start = Memory_contigAlloc(ad->outBuf.size, Memory_DEFAULTALIGNMENT)))
  {
    SYS_ERROR("Unable to allocate memory for Out Buffer\n");
  }
  else
  {
    SYS_DEBUG("Audio Decoder <%s> initialized\n", ad->adecName);
    SYS_DEBUG("Configured In Buf Size : %d\n", ad->inBuf.size);
    SYS_DEBUG("Configured Out Buf Size : %d\n", ad->outBuf.size);
    dvtb_audDecInitDebug(&ad->adecParams);

/*    ad->adecCmd = XDM_RESET;
    if (DVEVM_ST_FAIL == dvtb_audDecControl(ad))
    {
      SYS_ERROR("Unable to set dynamic audio parameters using command <%d>\n", ad->adecCmd);
      goto initClean;
    }*/

    ad->adecCmd = XDM_SETDEFAULT;
    if (DVEVM_ST_FAIL == dvtb_audDecControl(ad))
    {
      SYS_ERROR("Unable to set dynamic audio parameters using command <%d>\n", ad->adecCmd);
      goto initClean;
    }

    ad->adecCmd = XDM_SETPARAMS;
    if (DVEVM_ST_FAIL == dvtb_audDecControl(ad))
    {
      SYS_ERROR("Unable to set dynamic audio parameters using command <%d>\n", ad->adecCmd);
      goto initClean;
    }

    return DVEVM_ST_SUCCESS;
  }

initClean:
  dvtb_audDecCleanup(ad);
  return DVEVM_ST_FAIL;
}

DvevmStRetCode
dvtb_audDecDecode(DvevmStAudDecInfo *ad)
{
  XDM_BufDesc                 inBufDesc;
  XDM_BufDesc                 outBufDesc;
  XDAS_Int32                  status;

  IAUDDEC_InArgs              decInArgs;
  IAUDDEC_OutArgs             decOutArgs;

  ASSERT(ad != NULL);
  ASSERT(ad->ceHdl != NULL);
  ASSERT(ad->adecHdl != NULL);
  ASSERT(ad->inBuf.start != NULL);
  ASSERT(ad->outBuf.start != NULL);

  XDAS_Int8 *src = (XDAS_Int8 *) ad->inBuf.start;
  XDAS_Int8 *dst = (XDAS_Int8 *) ad->outBuf.start;

  inBufDesc.numBufs = outBufDesc.numBufs = 1;
  inBufDesc.bufSizes = (XDAS_Int32 *)&ad->inFrameSize;
  outBufDesc.bufSizes = (XDAS_Int32 *)&ad->outBuf.size;

  inBufDesc.bufs = &src;
  outBufDesc.bufs = &dst;

  decInArgs.size = sizeof(decInArgs);
  decInArgs.numBytes = ad->inFrameSize;
  decOutArgs.size = sizeof(decOutArgs);

  //SYS_DEBUG("Audio Decode Process => Input Frame Size : %d\n", ad->inFrameSize);
  status = AUDDEC_process(ad->adecHdl, &inBufDesc, &outBufDesc, &decInArgs, &decOutArgs);

  if (status != AUDDEC_EOK)
  {
    SYS_ERROR("Audio Decode Process failed (%d)\n", (int) status);
    SYS_ERROR("Codec Error => %d\n", (int) decOutArgs.extendedError);
    return DVEVM_ST_FAIL;
  }

  dvtb_audDecProcessDebug(&decOutArgs);
  ad->decFrameSize = decOutArgs.bytesConsumed;

  return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_audDecControl(DvevmStAudDecInfo *ad)
{
  int status;
  ASSERT(ad != NULL);
  ASSERT(ad->adecHdl != NULL);
  status = AUDDEC_control(ad->adecHdl, ad->adecCmd, &ad->adecDynParams,&ad->adecStatus);
  if (AUDDEC_EOK != status)
  {
    SYS_ERROR("Audio Decode Control failed (%d)\n", status);
    return DVEVM_ST_FAIL;
  }
  else
  {
    SYS_DEBUG("Audio Decode Control => Command : %d\n", ad->adecCmd);
    dvtb_audDecControlDebug(&ad->adecStatus);
    return DVEVM_ST_SUCCESS;
  }
}

DvevmStRetCode
dvtb_audDecClose(DvevmStAudDecInfo *ad)
{
  dvtb_audDecCleanup(ad);
  return DVEVM_ST_SUCCESS;
}
