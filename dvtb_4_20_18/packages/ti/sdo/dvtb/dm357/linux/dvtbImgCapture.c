/*
 * dvtbImgCapture.c
 *
 * XDM0.9 Image Encode Functionality
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

#include "dvtbImgCapture.h"
#include "dvtbImgEnc.h"
#include "dvtbMemory.h"
#include "dvtbDefs.h"

void
dvtb_imgEncCapture(DvevmStThreadInfo *T)
{
  DvevmStXdmBuffer oldXdmBuf;
  int i=0;

  char *targetBuff=NULL;
  int targetBytes=DEF_VIDFRAME_SIZE;
  int width, height;
  int nBytesRead;
  int ipFileLength=0;

  SYS_DEBUG("Image Encoder [capture][encode] called with %s option\n", (T->useAlgorithm)?"USE DSP":"NO DSP");

  /* Quit if target file is not specified */
  if (!T->targetFp)
  {
    SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
    dvtb_freeThr(T);
    dvtb_threadExit();
  }

  if(T->sourceFp)
  {
    fseek(T->sourceFp, 0L, SEEK_END);
    ipFileLength = ftell(T->sourceFp);
    fseek(T->sourceFp, -ipFileLength, SEEK_END);
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
      T->g.ienc.iencDynParams.inputWidth = width;
      T->g.ienc.iencDynParams.inputHeight = height;

      T->g.ienc.inBuf.numBufs = 1;
      T->g.ienc.inBuf.bufSizes[0] = T->g.ienc.iencParams.maxHeight*T->g.ienc.iencParams.maxWidth*2;

      T->g.ienc.outBuf.numBufs = 1;
      T->g.ienc.outBuf.bufSizes[0] = T->g.ienc.iencParams.maxWidth*T->g.ienc.iencParams.maxHeight*T->g.ienc.iencParams.maxScans;
    }
    else
    {
      width = T->g.ienc.iencDynParams.inputWidth;
      height = T->g.ienc.iencDynParams.inputHeight;

#if 0
      /* Set buffer requirements to support YUV 422/420P encoding */
      if (XDM_YUV_422ILE == T->g.ienc.iencDynParams.inputChromaFormat ||
          XDM_GRAY == T->g.ienc.iencDynParams.inputChromaFormat)
      {
        T->g.ienc.inBuf.numBufs = 1;
        T->g.ienc.inBuf.bufSizes[0] = T->g.ienc.iencParams.maxHeight*T->g.ienc.iencParams.maxWidth*2;
      }
      else if (XDM_YUV_420P == T->g.ienc.iencDynParams.inputChromaFormat)
      {
        unitSize = ipFileLength/12;
        T->g.ienc.inBuf.numBufs = 3;
        T->g.ienc.inBuf.bufSizes[0] = unitSize*8;
        T->g.ienc.inBuf.bufSizes[1] = unitSize*2;
        T->g.ienc.inBuf.bufSizes[2] = unitSize*2;
      }
      else if (XDM_YUV_422P == T->g.ienc.iencDynParams.inputChromaFormat)
      {
        unitSize = ipFileLength/16;
        T->g.ienc.inBuf.numBufs = 3;
        T->g.ienc.inBuf.bufSizes[0] = unitSize*8;
        T->g.ienc.inBuf.bufSizes[1] = unitSize*4;
        T->g.ienc.inBuf.bufSizes[2] = unitSize*4;
      }
      else if (XDM_YUV_444P == T->g.ienc.iencDynParams.inputChromaFormat)
      {
        unitSize = ipFileLength/24;
        T->g.ienc.inBuf.numBufs = 3;
        T->g.ienc.inBuf.bufSizes[0] = unitSize*8;
        T->g.ienc.inBuf.bufSizes[1] = unitSize*8;
        T->g.ienc.inBuf.bufSizes[2] = unitSize*8;
      }
      else if (XDM_YUV_411P == T->g.ienc.iencDynParams.inputChromaFormat)
      {
        unitSize = ipFileLength/12;
        T->g.ienc.inBuf.numBufs = 3;
        T->g.ienc.inBuf.bufSizes[0] = unitSize*8;
        T->g.ienc.inBuf.bufSizes[1] = unitSize*2;
        T->g.ienc.inBuf.bufSizes[2] = unitSize*2;
      }
      else
      {
        SYS_ERROR("Unknown force chroma format\n");
        break;
      }

      T->g.ienc.outBuf.numBufs = 1;
      T->g.ienc.outBuf.bufSizes[0] = T->g.ienc.iencParams.maxWidth*T->g.ienc.iencParams.maxHeight*T->g.ienc.iencParams.maxScans;
#endif
    }

    /* Initialize Image Encoder if DSP is to be used */
    if (T->useAlgorithm)
    {
      if (DVEVM_ST_FAIL == dvtb_ceInit(T->g.eng.name, &T->g.ienc.ceHdl))
      {
        SYS_ERROR("Cannot initialize Engine <%s>\n", T->g.eng.name);
        break;
      }
      else if (DVEVM_ST_FAIL == dvtb_imgEncInit(&T->g.ienc))
      {
        SYS_ERROR("Unable to initialize Image Encoder <%s>\n", T->g.ienc.iencName);
        break;
      }
      else
        SYS_OUT("Image Encoder <%s> initialized\n", T->g.ienc.iencName);
    }

    /* Take a backup of allocated XDM buffer if VPFE is to be used */
    if (!T->sourceFp && T->useAlgorithm)
    {
      dvtb_copyXdmBuf(&T->g.ienc.inBuf, &oldXdmBuf);
    }

    /* Start the [capture][encode] process */

    do//dummy loop
    {
      if (!T->sourceFp)
      {
        if (dvtb_vpfeGetNextBuffer(&T->g.vpfe) < 0)
        {
          SYS_ERROR("Error while reading image input\n");
          break;
        }
#if 0
        /* If we don't read twice we get interlaced image */
        dvtb_vpfeReturnBuffer(&T->g.vpfe);

        if (dvtb_vpfeGetNextBuffer(&T->g.vpfe) < 0)
        {
          SYS_ERROR("Error while reading image input\n");
          break;
        }
#endif
        targetBuff = T->g.vpfe.buffers[T->g.vpfe.buf.index].start;
        T->g.ienc.inBuf.bufs[0] = targetBuff;
        break;
      }
      else
      {
        for (i=0; i<T->g.ienc.inBuf.numBufs; i++)
        {
          nBytesRead = fread(T->g.ienc.inBuf.bufs[i], 1, T->g.ienc.inBuf.bufSizes[i], T->sourceFp);
        }

        if (feof(T->sourceFp))
        {
          SYS_DEBUG("End of source file reached. Exiting ...\n");
          break;
        }
      }
    }while(DVEVM_ST_FAIL);

    if (T->useAlgorithm)
    {
      memset(T->g.ienc.outBuf.bufs[0], 0, T->g.ienc.outBuf.bufSizes[0]);
      if (DVEVM_ST_FAIL == dvtb_imgEncEncode(&T->g.ienc))
      {
        SYS_ERROR("Unable to encode the input buffer\n");
        break;
      }

      T->g.ienc.iencCmd = XDM_GETSTATUS;
      if (DVEVM_ST_FAIL == dvtb_imgEncControl(&T->g.ienc))
      {
        SYS_ERROR("Unable to get the status\n");
        break;
      }

      targetBuff = T->g.ienc.outBuf.bufs[0];
      targetBytes = T->g.ienc.iencOutArgs.bytesGenerated;
    }

    if (!T->sourceFp)
    {
      dvtb_vpfeReturnBuffer(&T->g.vpfe);
    }

      /* Store the processed frame to target file */
    fwrite(targetBuff, 1, targetBytes, T->targetFp);


    /* Restore the backed-up XDM buffer */
    if (!T->sourceFp && T->useAlgorithm)
    {
      dvtb_copyXdmBuf(&oldXdmBuf, &T->g.ienc.inBuf);
    }
  } while (DVEVM_ST_FALSE);

  SYS_OUT("Image [capture][encode] completed.\n");

  /* Uninitialize and close */
  if (!T->sourceFp)
  {
    dvtb_vpfeClose(&T->g.vpfe);
    SYS_OUT("VPFE Device <%s> closed\n", T->g.vpfe.device);
  }

  if (T->useAlgorithm)
  {
    dvtb_imgEncClose(&T->g.ienc);
    SYS_OUT("Image Encoder <%s> closed\n", T->g.ienc.iencName);

    Engine_close(T->g.ienc.ceHdl);
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
