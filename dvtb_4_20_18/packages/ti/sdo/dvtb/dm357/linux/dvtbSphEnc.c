/*
 * dvtbSphEnc.c
 *
 * XDM0.9 Speech Encode Interface implementation
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

#include "dvtbSphEnc.h"
#include "dvtbMemory.h"

static void
dvtb_sphEncCleanup(DvevmStSphEncInfo *se)
{
  if (NULL != se->sencHdl)
    SPHENC_delete(se->sencHdl);

  if (NULL != se->inBuf.start)
    Memory_contigFree(se->inBuf.start, se->inBuf.size);

  if (NULL != se->outBuf.start)
    Memory_contigFree(se->outBuf.start, se->outBuf.size);

  se->inBuf.start = NULL;
  se->outBuf.start = NULL;
}

DvevmStRetCode
dvtb_sphEncInit(DvevmStSphEncInfo *se)
{
  ASSERT(se != NULL);
  ASSERT(se->ceHdl != NULL);
  ASSERT(se->sencName[0] != 0);

  if (NULL == (se->sencHdl = SPHENC_create(se->ceHdl, se->sencName, &se->sencParams)))
  {
    SYS_ERROR("Unable to initialize Speech Encoder\n");
  }
  else if (NULL == (se->inBuf.start = Memory_contigAlloc(se->inBuf.size, Memory_DEFAULTALIGNMENT)))
  {
    SYS_ERROR("Unable to allocate memory for In Buffer\n");
  }
  else if (NULL == (se->outBuf.start = Memory_contigAlloc(se->outBuf.size, Memory_DEFAULTALIGNMENT)))
  {
    SYS_ERROR("Unable to allocate memory for Out Buffer\n");
  }
  else
  {
    SYS_DEBUG("\tSpeech Encoder Name : %s\n", se->sencName);
    //SYS_DEBUG("\tIn Buffer Address : 0x%x\n", (unsigned int) Memory_getPhysicalAddress(se->inBuf.start));
    //SYS_DEBUG("\tOut Buffer Address : 0x%x\n", (unsigned int) Memory_getPhysicalAddress(se->inBuf.start));

    return DVEVM_ST_SUCCESS;
  }

  dvtb_sphEncCleanup(se);
  return DVEVM_ST_FAIL;
}

DvevmStRetCode
dvtb_sphEncEncode(DvevmStSphEncInfo *se)
{
  XDM_BufDesc                 inBufDesc;
  XDM_BufDesc                 outBufDesc;
  XDAS_Int32                  status;

  ASSERT(se != NULL);
  ASSERT(se->ceHdl != NULL);
  ASSERT(se->sencHdl != NULL);
  ASSERT(se->inBuf.start != NULL);
  ASSERT(se->outBuf.start != NULL);

  XDAS_Int8 *src = (XDAS_Int8 *) se->inBuf.start;
  XDAS_Int8 *dst = (XDAS_Int8 *) se->outBuf.start;


  inBufDesc.bufs = &src;
  inBufDesc.numBufs = outBufDesc.numBufs = 1;
  inBufDesc.bufSizes = (XDAS_Int32 *) &se->inBuf.size;

  outBufDesc.bufs = &dst;
  outBufDesc.bufSizes = (XDAS_Int32 *) &se->outBuf.size;

  status = SPHENC_process(se->sencHdl, &inBufDesc, &outBufDesc, &se->sencInArgs, &se->sencOutArgs);

  if (status != SPHENC_EOK)
  {
    SYS_ERROR("Error (%d) in Speech Encoder Process\n", (int) status);
    return DVEVM_ST_FAIL;
  }

  return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_sphEncControl(DvevmStSphEncInfo *se)
{
  return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_sphEncClose(DvevmStSphEncInfo *se)
{
  dvtb_sphEncCleanup(se);
  return DVEVM_ST_SUCCESS;
}
