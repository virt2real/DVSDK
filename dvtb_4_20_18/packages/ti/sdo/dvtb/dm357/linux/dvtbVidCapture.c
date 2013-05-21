/*
 * dvtbVidCapture.c
 *
 * XDM0.9 Video Encode functionality
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

#include "dvtbVidCapture.h"
#include "dvtbVidEnc.h"
#include "dvtbMemory.h"
#include "dvtbDefs.h"

void
dvtb_vidEncCapture(DvevmStThreadInfo *T)
{
  DvevmStXdmBuffer oldXdmBuf;
  int i=0, maxFrames=0, nFrames=0;

  char *targetBuff = NULL;
  int targetBytes=DEF_VIDFRAME_SIZE;
  int width, height;
  int encDuration;

  maxFrames = T->g.venc.numFrames;
  SYS_DEBUG("Video Encoder [capture][encode] called with %s option\n", (T->useAlgorithm)?"USE DSP":"NO DSP");
  SYS_DEBUG("Number of frames to [capture][encode] : %d\n", maxFrames);

  /* Quit if target file is not specified */
  if (!T->targetFp)
  {
    SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
    dvtb_freeThr(T);
    dvtb_threadExit();
  }

  /* Dummy loop to enable easy cleanup */
  do
  {
    /* If source file is not defined, initialize VPFE
     * Else initialize the YUV source file to be encoded */
    if (!T->sourceFp)
    {
      width = T->g.vpfe.capWidth;
      height = T->g.vpfe.capHeight;

      if (DVEVM_ST_FAIL == dvtb_vpfeSetup(&T->g.vpfe))
      {
        SYS_ERROR("Unable to initialize VPFE device <%s>\n", T->g.vpfe.device);
        break;
      }
      if (DVEVM_ST_FAIL == dvtb_vpfeCaptureStart(&T->g.vpfe))
      {
        SYS_ERROR("Unable to start VPFE device <%s>\n", T->g.vpfe.device);
        break;
      }

      SYS_OUT("VPFE device <%s> initialized for capture\n", T->g.vpfe.device);

      targetBytes = T->g.vpfe.capSize;
      T->g.venc.vencDynParams.inputWidth = width;
      T->g.venc.vencDynParams.inputHeight = height;

      T->g.venc.inBuf.numBufs = 1;
      T->g.venc.inBuf.bufSizes[0] = VID_FRAME_SIZE(width, height, DEF_BPP);

      T->g.venc.outBuf.numBufs = 1;
      T->g.venc.outBuf.bufSizes[0] = VID_FRAME_SIZE(width, height, DEF_BPP);
    }
    else
    {
      width = T->g.venc.vencDynParams.inputWidth;
      height = T->g.venc.vencDynParams.inputHeight;

      /* Set buffer requirements to support YUV 422/420P encoding */
      if (XDM_YUV_422ILE == T->g.venc.vencParams.inputChromaFormat)
      {
        T->g.venc.inBuf.numBufs = 1;
        T->g.venc.inBuf.bufSizes[0] = VID_FRAME_SIZE(width, height, DEF_BPP);
      }
      else if (XDM_YUV_420P == T->g.venc.vencParams.inputChromaFormat)
      {
        T->g.venc.inBuf.numBufs = 3;
        T->g.venc.inBuf.bufSizes[0] = width * height;
        T->g.venc.inBuf.bufSizes[1] = T->g.venc.inBuf.bufSizes[0] / 4;
        T->g.venc.inBuf.bufSizes[2] = T->g.venc.inBuf.bufSizes[0] / 4;
      }

      T->g.venc.outBuf.numBufs = 1;
      T->g.venc.outBuf.bufSizes[0] = VID_FRAME_SIZE(width, height, DEF_BPP);
    }

    /* Initialize Video Encoder if DSP is to be used */
    if (T->useAlgorithm)
    {
      if (DVEVM_ST_FAIL == dvtb_ceInit(T->g.eng.name, &T->g.venc.ceHdl))
      {
        SYS_ERROR("Cannot initialize Engine <%s>\n", T->g.eng.name);
        break;
      }
      else if (DVEVM_ST_FAIL == dvtb_vidEncInit(&T->g.venc))
      {
        SYS_ERROR("Unable to initialize Video Encoder <%s>\n", T->g.venc.vencName);
        break;
      }
      else
        SYS_OUT("Video Encoder <%s> initialized\n", T->g.venc.vencName);
    }

    /* Take a backup of allocated XDM buffer if VPFE is to be used */
    if (!T->sourceFp && T->useAlgorithm)
    {
      dvtb_copyXdmBuf(&T->g.venc.inBuf, &oldXdmBuf);
    }

    /* Start the [capture][encode] process */
    while (nFrames++ < maxFrames)
    {
      if (!T->sourceFp)
      {
        if (dvtb_vpfeGetNextBuffer(&T->g.vpfe) < 0)
        {
          SYS_ERROR("Error while reading video input\n");
          break;
        }

        targetBuff = T->g.vpfe.buffers[T->g.vpfe.buf.index].start;
        T->g.venc.inBuf.bufs[0] = targetBuff;
      }
      else
      {
        for (i=0; i<T->g.venc.inBuf.numBufs; i++)
        {
          fread(T->g.venc.inBuf.bufs[i], 1, T->g.venc.inBuf.bufSizes[i], T->sourceFp);
        }
        if (feof(T->sourceFp))
        {
          SYS_DEBUG("End of source file reached. Exiting ...\n");
          break;
        }
      }

      if (T->useAlgorithm)
      {
        memset(T->g.venc.outBuf.bufs[0], 0, T->g.venc.outBuf.bufSizes[0]);
        if (DVEVM_ST_FAIL == dvtb_vidEncEncode(&T->g.venc, &encDuration))
        {
          SYS_ERROR("Unable to encode the input buffer\n");
          break;
        }

        targetBuff = T->g.venc.outBuf.bufs[0];
        targetBytes = T->g.venc.vencOutArgs.bytesGenerated;
      }

      if (!T->sourceFp)
      {
        dvtb_vpfeReturnBuffer(&T->g.vpfe);
      }

      /* Store the processed frame to target file */
      fwrite(targetBuff, 1, targetBytes, T->targetFp);
#ifdef PERF
      SYS_PERF("Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", nFrames, targetBytes, encDuration);
      SYS_OUT("Frame#, %d, Frame Size(bytes), %d, EncTime(us), %d\n", nFrames, targetBytes, encDuration);
#endif
    }

    /* Restore the backed-up XDM buffer */
    if (!T->sourceFp && T->useAlgorithm)
    {
      dvtb_copyXdmBuf(&oldXdmBuf, &T->g.venc.inBuf);
    }

  } while (DVEVM_ST_FALSE);

  SYS_OUT("Video [capture][encode] completed for <%d> frames\n", nFrames-1);

  /* Uninitialize and close */
  if (!T->sourceFp)
  {
    dvtb_vpfeClose(&T->g.vpfe);
  }

  if (T->useAlgorithm)
  {
    dvtb_vidEncClose(&T->g.venc);
    SYS_OUT("Video Encoder <%s> closed\n", T->g.venc.vencName);

    Engine_close(T->g.venc.ceHdl);
    SYS_OUT("Engine <%s> closed\n", T->g.eng.name);
  }

  if (T->sourceFp)
  {
    fclose(T->sourceFp);
    T->sourceFp = NULL;
  }

  if (T->targetFp)
  {
    fclose(T->targetFp);
    T->targetFp = NULL;
  }

  dvtb_freeThr(T);
  dvtb_threadExit();
}
