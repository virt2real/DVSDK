/*
 * dvtbSphDec.c
 *
 * XDM0.9 Speech Decode Interface implementation
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

#include "dvtbSphDec.h"
#include "dvtbMemory.h"

static void
dvtb_sphDecCleanup(DvevmStSphDecInfo *sd)
{
  if (NULL != sd->sdecHdl)
    SPHDEC_delete(sd->sdecHdl);

  if (NULL != sd->inBuf.start)
    Memory_contigFree(sd->inBuf.start, sd->inBuf.size);

  if (NULL != sd->outBuf.start)
    Memory_contigFree(sd->outBuf.start, sd->outBuf.size);

  sd->inBuf.start = NULL;
  sd->outBuf.start = NULL;
}

DvevmStRetCode
dvtb_sphDecInit(DvevmStSphDecInfo *sd)
{
  ASSERT(sd != NULL);
  ASSERT(sd->ceHdl != NULL);
  ASSERT(sd->sdecName[0] != 0);

  if (NULL == (sd->sdecHdl = SPHDEC_create(sd->ceHdl, sd->sdecName, &sd->sdecParams)))
  {
    SYS_ERROR("Unable to initialize Speech Decoder\n");
  }
  else if (NULL == (sd->inBuf.start = Memory_contigAlloc(sd->inBuf.size, Memory_DEFAULTALIGNMENT)))
  {
    dvtb_sphDecCleanup(sd);
    SYS_ERROR("Unable to allocate memory for In Buffer\n");
  }
  else if (NULL == (sd->outBuf.start = Memory_contigAlloc(sd->outBuf.size, Memory_DEFAULTALIGNMENT)))
  {
    dvtb_sphDecCleanup(sd);
    SYS_ERROR("Unable to allocate memory for Out Buffer\n");
  }
  else
  {
    return DVEVM_ST_SUCCESS;
  }

  return DVEVM_ST_FAIL;
}

DvevmStRetCode
dvtb_sphDecDecode(DvevmStSphDecInfo *sd)
{
  int i=0;

  XDM_BufDesc                 inBufDesc;
  XDM_BufDesc                 outBufDesc;
  XDAS_Int32                  status;

  SPHDEC_InArgs               decInArgs;
  SPHDEC_OutArgs              decOutArgs;

  ASSERT(sd != NULL);
  ASSERT(sd->ceHdl != NULL);
  ASSERT(sd->sdecHdl != NULL);
  ASSERT(sd->inBuf.start != NULL);
  ASSERT(sd->outBuf.start != NULL);

  XDAS_Int8 *src = (XDAS_Int8 *) sd->inBuf.start;
  XDAS_Int8 *dst = (XDAS_Int8 *) sd->outBuf.start;

  inBufDesc.numBufs = outBufDesc.numBufs = 1;
  inBufDesc.bufSizes = (XDAS_Int32 *) &sd->inBuf.size;
  outBufDesc.bufSizes = (XDAS_Int32 *) &sd->outBuf.size;

  inBufDesc.bufs = &src;
  outBufDesc.bufs = &dst;
  decInArgs.size = sizeof(decInArgs);
  decOutArgs.size = sizeof(decOutArgs);

  status = SPHDEC_process(sd->sdecHdl, &inBufDesc, &outBufDesc, &decInArgs, &decOutArgs);

  if (status != SPHDEC_EOK)
  {
    SYS_ERROR("Error (%d) in Speech Decoder Process\n", (int) status);
    return DVEVM_ST_FAIL;
  }

  /* Expand mono to stereo */
  for (i=(sd->outBuf.size-1); i >= 0; i--)
  {
    dst[4*i] = dst[2*i];
    dst[4*i+1] = dst[2*i+1];
    dst[4*i+2] = dst[2*i];
    dst[4*i+3] = dst[2*i+1];
  }

  return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_sphDecControl(DvevmStSphDecInfo *sd)
{
  return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_sphDecClose(DvevmStSphDecInfo *sd)
{
  dvtb_sphDecCleanup(sd);
  return DVEVM_ST_SUCCESS;
}
