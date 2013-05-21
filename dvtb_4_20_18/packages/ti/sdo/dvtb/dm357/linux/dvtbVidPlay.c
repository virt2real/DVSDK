/*
 * dvtbVidPlay.c
 *
 * XDM0.9 Video Decode functionality
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

#include "dvtbVidPlay.h"
#include "dvtbFBVPBE.h"
#include "dvtbVidDec.h"
#include "dvtbMemory.h"
#include "dvtbDefs.h"

void
dvtb_vidDecPlay(DvevmStThreadInfo *T)
{
  DvevmStRetCode status=DVEVM_ST_FAIL;
  DvevmStXdmBuffer *inbuf=NULL, *outbuf=NULL, dispBuff;
  int nBytes=DVEVM_ST_FAIL;
  int i=0, j=0, nFrames=0, frameSize=0;
  DvevmStVidDecOutBufs outBufs[MAX_VIDDEC_OUTBUFS];
#if 0
  DvevmStBool oddField=DVEVM_ST_FALSE;
#endif
  int decDuration;

  SYS_DEBUG("Video [Decode][Play] with <%s> option\n", (T->useAlgorithm)?"USE DSP":"NO DSP");

  if(!T->sourceFp)
  {
    SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
    dvtb_freeThr(T);
    dvtb_threadExit();
  }

  // [Decode][Play] scenario
  do
  {
    SYS_OUT("Video [Decode][Play] started\n");
    if(!T->targetFp)
    {
      status = (*dvtb_vpbeSetupPtr)(&T->g.vpbe);
      if(DVEVM_ST_FAIL == status)
      {
        SYS_ERROR("Unable to setup VPBE device <%s> for display\n", T->g.vpbe.device);
        break;
      }
      else
        SYS_OUT("VPBE device <%s> initialized for display\n", T->g.vpbe.device);
    }

    if(T->useAlgorithm)
    {
      inbuf = &T->g.vdec.inBuf;
      outbuf = &T->g.vdec.outBuf;

      inbuf->numBufs=0;
      outbuf->numBufs = 0;

      T->g.vdec.vdecInArgs.size = sizeof(T->g.vdec.vdecInArgs);
      T->g.vdec.vdecOutArgs.size = sizeof(T->g.vdec.vdecOutArgs);

      if (DVEVM_ST_FAIL == dvtb_ceInit(T->g.eng.name, &T->g.vdec.ceHdl))
      {
        SYS_ERROR("Unable to initialize Codec Engine <%s>\n", T->g.eng.name);
        break;
      }
      else if (DVEVM_ST_FAIL == dvtb_vidDecInit(&T->g.vdec))
      {
        SYS_ERROR("Unable to initialize Video Decoder <%s>\n", T->g.vdec.vdecName);
        break;
      }
      else if (DVEVM_ST_FAIL == dvtb_allocCmem(&T->g.vdec.inBuf))
      {
        SYS_ERROR("Unable to allocate memory for input buffer \n");
        break;
      }
      else
      {
        for (i=0; i<MAX_VIDDEC_OUTBUFS; i++)
        {
          outBufs[i].xdmBuf.numBufs = 0;
        }

        for (i=0; i<MAX_VIDDEC_OUTBUFS; i++)
        {
          outBufs[i].isFree = DVEVM_ST_TRUE;
          outBufs[i].xdmBuf.numBufs = outbuf->numBufs;

          for (j=0; j<outbuf->numBufs; j++)
          {
            outBufs[i].xdmBuf.bufSizes[j] = outbuf->bufSizes[j];
          }

          if (DVEVM_ST_FAIL == dvtb_allocCmem(&outBufs[i].xdmBuf))
          {
            SYS_ERROR("Unable to allocate memory for output buffer [%d]\n", i);
            status = DVEVM_ST_FAIL;
            break;
          }

          status = DVEVM_ST_SUCCESS;
        }

        if (DVEVM_ST_FAIL == status)
        {
          break;
        }

        for (i=0; i<outbuf->numBufs; i++)
        {
          outbuf->bufs[i] = outBufs[0].xdmBuf.bufs[i];
        }
        outBufs[0].isFree = DVEVM_ST_FALSE;
        outBufs[0].outputId = T->g.vdec.vdecInArgs.inputID = 0;

        SYS_OUT("Video Decoder <%s> initialized\n", T->g.vdec.vdecName);
      }

    }
    else
    {
      dispBuff.numBufs = 1;
      dispBuff.bufSizes[0] = T->g.vpbe.imageWidth * T->g.vpbe.imageHeight * (T->g.vpbe.bpp /8 ); // supports 16 bpp and 24 bpp

      if (DVEVM_ST_FAIL == dvtb_allocCmem(&dispBuff))
      {
        SYS_OUT("Unable to allocate memory for video playback\n");
        break;
      }

      inbuf = outbuf = &dispBuff;
    }

    while ( !feof(T->sourceFp) && nFrames < T->g.vdec.numFrames)
    {
      nBytes = fread(inbuf->bufs[0], 1, inbuf->bufSizes[0], T->sourceFp);

      if (0 == nBytes)
        break;

      if(T->useAlgorithm)
      {
        T->g.vdec.vdecInArgs.numBytes = nBytes;
        if (DVEVM_ST_FAIL == dvtb_vidDecDecode(&T->g.vdec, nFrames+1, &decDuration))
        {
          SYS_ERROR("Unable to decode <%s> frame # %d, size (%d) bytes\n", T->g.vdec.vdecName, nFrames+1, nBytes);
          break;
        }

        frameSize = T->g.vdec.vdecOutArgs.bytesConsumed;

        if (0 == frameSize)
        {
          continue;
        }

        if (DVEVM_ST_FAIL == fseek(T->sourceFp, -(nBytes-frameSize), SEEK_CUR))
        {
          SYS_ERROR("Cannot set the file pointer to next frame position\n");
          break;
        }

#if 0
        if (T->g.vdec.skipFrame)
        {
          continue;
        }
#endif

        T->g.vdec.vdecCmd = XDM_GETSTATUS;
        if (DVEVM_ST_FAIL == dvtb_vidDecControl(&T->g.vdec))
        {
          SYS_ERROR("Unable to get the status for frame # %d\n", nFrames+1);
          break;
        }

        // If its interlaced content, repeat the same decode call again
#if 0
#ifdef TWO_CALL_INTERLACED_CONTENT_DECODING
        if (IVIDEO_INTERLACED == T->g.vdec.vdecStatus.contentType)
        {
          oddField = !oddField;

          if (oddField)
          {
            continue;
          }
        }
#endif
#endif

        SYS_DEBUG("Frame #%d, Encoded Frame Size :%d, Decoded Frame Size(s) : ", nFrames+1, frameSize);

#ifdef PERF
      SYS_PERF("Frame#, %d, Decoded Frame Size(bytes), %d, DecTime(us), %d\n", nFrames+1, frameSize, decDuration);
      SYS_OUT("Frame#, %d, Decoded Frame Size(bytes), %d, DecTime(us), %d\n", nFrames+1, frameSize, decDuration);
#endif

#ifdef _DVEVM_ST_DEBUG_
        for (i=0; i<outbuf->numBufs; i++)
          SYS_PRINTF("%d ,", (int) T->g.vdec.vdecOutArgs.displayBufs.bufSizes[i]);

        SYS_PRINTF("\n");
#endif
      }

      nFrames++;

      if(T->useAlgorithm)
      {
        // Check if a frame is ready to be displayed
        SYS_DEBUG("displayable buffer %x\n", (unsigned int) T->g.vdec.vdecOutArgs.displayBufs.bufs[0]);
        if (NULL != T->g.vdec.vdecOutArgs.displayBufs.bufs[0])
        {
          outbuf = NULL;
          for (i=0; i<MAX_VIDDEC_OUTBUFS; i++)
          {
            if (!outBufs[i].isFree && (outBufs[i].outputId == T->g.vdec.vdecOutArgs.outputID))
            {
              outbuf = &outBufs[i].xdmBuf;
              outBufs[i].isFree = DVEVM_ST_TRUE;
              break;
            }
          }
          if (NULL == outbuf)
          {
            SYS_ERROR("Unable to find decoded output buffer <%d> for display\n", (int)T->g.vdec.vdecOutArgs.outputID);
            break;
          }
          T->g.vpbe.imageWidth = T->g.vdec.vdecStatus.outputWidth;
          T->g.vpbe.imageHeight = T->g.vdec.vdecStatus.outputHeight;

          if(T->targetFp)
          {
            for (i=0; i<outbuf->numBufs; i++)
            {
              status = fwrite(outbuf->bufs[i], 1, T->g.vdec.vdecOutArgs.displayBufs.bufSizes[i], T->targetFp);

              if (DVEVM_ST_FAIL == status)
                break;
            }
          }
          else
            status = dvtb_vpbeDisplay(&T->g.vpbe, outbuf->bufs[0]);

          if (DVEVM_ST_FAIL == status)
          {
            SYS_ERROR("Unable to write into target device\n");
            break;
          }
        }
      }
      else
      {
        if(T->targetFp)
        {
          for (i=0; i<outbuf->numBufs; i++)
          {
            status = fwrite(outbuf->bufs[i], 1, nBytes, T->targetFp);
            if (DVEVM_ST_FAIL == status)
              break;
          }
        }
        else
          status = dvtb_vpbeDisplay(&T->g.vpbe, outbuf->bufs[0]);

        if (DVEVM_ST_FAIL == status)
        {
          SYS_ERROR("Unable to write into target device\n");
          break;
        }
      }

      // Allocate next free buffer to output buffer
      if(T->useAlgorithm)
      {
        for (i=0; i<MAX_VIDDEC_OUTBUFS; i++)
        {
          if (outBufs[i].isFree)
          {
            for (j=0; j<outBufs[i].xdmBuf.numBufs; j++)
            {
              T->g.vdec.outBuf.bufs[j] = outBufs[i].xdmBuf.bufs[j];
            }
            outBufs[i].isFree = DVEVM_ST_FALSE;
            outBufs[i].outputId = ++T->g.vdec.vdecInArgs.inputID;
            break;
          }
        }
        if (i>MAX_VIDDEC_OUTBUFS)
        {
          SYS_ERROR("All output buffers full. Unable to allocate output buffer for frame # <%d>\n", nFrames+1);
          break;
        }
      }

    } // end while !feof

  } while (DVEVM_ST_FALSE); // Dummy loop

  SYS_DEBUG("Video Playback <%s> : Resolution %dx%d\n", T->g.vdec.vdecName, T->g.vpbe.imageWidth, T->g.vpbe.imageHeight);
  SYS_OUT("Video [Decode][Play] completed for <%d> frames\n", nFrames);

  if (!T->targetFp)
  {
    dvtb_vpbeClose(&T->g.vpbe);
    SYS_OUT("VPBE Device <%s> closed\n", T->g.vpbe.device);
  }

  if (T->useAlgorithm)
  {
    for (i=0; i<MAX_VIDDEC_OUTBUFS; i++)
    {
      dvtb_freeCmem(&outBufs[i].xdmBuf);
    }

    dvtb_freeCmem(inbuf);
    dvtb_vidDecClose(&T->g.vdec);
    SYS_OUT("Video Decoder <%s> closed\n", T->g.vdec.vdecName);

    Engine_close(T->g.vdec.ceHdl);
    SYS_OUT("Engine <%s> closed\n", T->g.eng.name);
  }
  else
    dvtb_freeCmem(&dispBuff);

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

  SYS_OUT("Video Play thread exiting\n");

  dvtb_freeThr(T);
  dvtb_threadExit();
}
