/*
 * dvtbSphPlay.c
 *
 * XDM0.9 Speech Decode functionality
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

#include "dvtbSphPlay.h"
#include "dvtbSphDec.h"
#include "dvtbOSSAudio.h"
#include "dvtbDefs.h"

void
dvtb_sphDecPlay(DvevmStThreadInfo *T)
{
  DvevmStRetCode status=DVEVM_ST_FAIL;
  int nBytes=DVEVM_ST_FAIL;
  char *buff=NULL;
  int nFrames=0;

  SYS_DEBUG("Speech [Decode][Play] called with %s option\n", (T->useAlgorithm)?"USE DSP":"NO DSP");
  // [Decode]+Play scenario

  if (!T->sourceFp)
  {
    SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
    dvtb_freeThr(T);
    dvtb_threadExit();
  }

  do
  {
    SYS_OUT("Speech [Decode][Play] started\n");

    if (!T->targetFp)
    {
      T->g.aud.sampleRate = DEF_SPH_SAMPLERATE;
      status = dvtb_audioSetup(&T->g.aud);
      if (DVEVM_ST_FAIL == status)
      {
        SYS_ERROR("Unable to setup Audio device <%s> for playback\n", T->g.aud.device);
        break;
      }
      else
        SYS_OUT("Audio device <%s> initialized for display\n", T->g.aud.device);
    }

    if (T->useAlgorithm)
    {
      if (DVEVM_ST_FAIL == dvtb_ceInit(T->g.eng.name, &T->g.sdec.ceHdl))
      {
        SYS_ERROR("Unable to initialize Codec Engine <%s>\n", T->g.eng.name);
        break;
      }
      else if (DVEVM_ST_FAIL == dvtb_sphDecInit(&T->g.sdec))
      {
        SYS_ERROR("Unable to initialize Speech Decoder <%s>\n", T->g.sdec.sdecName);
        break;
      }
      else
        SYS_OUT("Speech Decoder <%s> initialized\n", T->g.sdec.sdecName);
    }
    else
      T->g.sdec.inBuf.start = (char *)malloc(T->g.sdec.inBuf.size);

    while ( !feof(T->sourceFp) )
    {
      nFrames++;
      buff = T->g.sdec.inBuf.start;
      nBytes = fread(buff, 1, T->g.sdec.inBuf.size, T->sourceFp);

      if (nBytes < T->g.sdec.inBuf.size)
        break;

      if (T->useAlgorithm)
      {
        memset(T->g.sdec.outBuf.start, 0, T->g.sdec.outBuf.size);

        if (DVEVM_ST_FAIL == dvtb_sphDecDecode(&T->g.sdec))
        {
          SYS_ERROR("Unable to decode <%s> frame # %d\n", T->g.sdec.sdecName, nFrames);
          break;
        }

        buff = T->g.sdec.outBuf.start;
        nBytes = T->g.sdec.inBuf.size * 4;
        SYS_DEBUG("Frame #%d, Encoded Frame Size :%d, Decoded Frame Size :%d\n", nFrames, T->g.sdec.inBuf.size, nBytes);
      }

      if (T->targetFp)
        status = fwrite(buff, 1, nBytes, T->targetFp);
      else
        status = dvtb_audioOut(&T->g.aud, buff, nBytes);

      if (DVEVM_ST_FAIL == status)
      {
        SYS_ERROR("Unable to write into target device\n");
        break;
      }
    }

  } while (DVEVM_ST_FALSE); // Dummy loop

  SYS_DEBUG("Speech [Decode][Play] completed for <%d> frames\n", nFrames-1);

  if (!T->targetFp)
    dvtb_audioClose(&T->g.aud);

  if (T->useAlgorithm)
  {
    dvtb_sphDecClose(&T->g.sdec);
    SYS_OUT("Speech Decoder <%s> closed\n", T->g.sdec.sdecName);

    Engine_close(T->g.sdec.ceHdl);
    SYS_OUT("Engine <%s> closed\n", T->g.eng.name);
  }
  else
    free(T->g.sdec.inBuf.start);

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

  SYS_OUT("Speech play thread exiting\n");

  dvtb_freeThr(T);
  dvtb_threadExit();
}
