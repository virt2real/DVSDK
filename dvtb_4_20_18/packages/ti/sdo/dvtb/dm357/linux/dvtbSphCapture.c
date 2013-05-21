/*
 * dvtbSphCapture.c
 *
 * XDM0.9 Speech Encode functionality
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
#include "dvtbSphCapture.h"
#include "dvtbDefs.h"

static void
stereoToMono(short *stereoSamples, short *monoSamples, int numSamples)
{
  int i;
  int val;

  for (i=0; i<numSamples; i++)
  {
    val = *stereoSamples++;
    *monoSamples++ = (val + *stereoSamples++) / 2;
  }
}

void
dvtb_sphEncCapture(DvevmStThreadInfo *T)
{
  DvevmStRetCode retval=DVEVM_ST_FAIL;
  int nBytes=DVEVM_ST_FAIL;
  char *buff=NULL;
  int bytesToCapture=0, count=0;
  char tempBuff[SPHENC_FRAME_SIZE*4];

  SYS_DEBUG("Speech [capture][encode] called with %s option\n", (T->useAlgorithm)?"USE DSP":"NO DSP");
  SYS_DEBUG("Number of seconds to [capture][encode] : %d\n", T->g.senc.seconds);

  if ( !T->targetFp )
  {
    SYS_ERROR("Target file cannot be opened. It is a mandatory parameter\n");
    dvtb_freeThr(T);
    dvtb_threadExit();
  }

  // [Capture][Encode] scenario
  do
  {
    SYS_OUT("Speech [capture][encode] started for %d seconds\n", T->g.senc.seconds);

    if (T->useAlgorithm)
    {
      T->g.aud.sampleRate = 8000;
      T->g.senc.inBuf.size = SPHENC_FRAME_SIZE * 2;
      T->g.senc.outBuf.size = SPHENC_FRAME_SIZE;
      if (DVEVM_ST_FAIL == dvtb_ceInit(T->g.eng.name, &T->g.senc.ceHdl))
      {
        SYS_ERROR("Unable to initialize Codec Engine <%s>\n", T->g.eng.name);
        break;
      }
      else if (DVEVM_ST_FAIL == dvtb_sphEncInit(&T->g.senc))
      {
        SYS_ERROR("Unable to initialize Speech Encoder <%s>\n", T->g.senc.sencName);
        break;
      }
      else
        SYS_OUT("Speech Encoder <%s> initialized\n", T->g.senc.sencName);
    }
    else
    {
      T->g.senc.inBuf.size = SPHENC_FRAME_SIZE*4*2;
      T->g.senc.inBuf.start = (char *)malloc(T->g.senc.inBuf.size);
    }

    if (!T->sourceFp)
    {
      T->g.aud.mode = DVEVM_ST_CAPTURE;
      retval = dvtb_audioSetup(&T->g.aud);
      if (DVEVM_ST_FAIL == retval)
      {
        SYS_ERROR("Unable to initialize Audio device <%s> for capture\n", T->g.aud.device);
        break;
      }
      else
      {
        SYS_DEBUG("Audio Device <%s> initialized for capture\n", T->g.aud.device);
        bytesToCapture = (T->g.senc.seconds)*(AUD_FRAME_SIZE(T->g.aud.sampleRate, T->g.aud.numChannels, T->g.aud.sampleSize));
      }
    }
    while (1)
    {
      buff = tempBuff;

      if (T->sourceFp)
      {
        nBytes = fread(buff, 1, SPHENC_FRAME_SIZE*4, T->sourceFp);
        if (0==nBytes || feof(T->sourceFp))
        {
          SYS_DEBUG("End of file reached. Exiting ...\n");
          break;
	}
      }
      else
      {
        nBytes = dvtb_audioIn(&T->g.aud, buff, SPHENC_FRAME_SIZE*4);
        if (DVEVM_ST_FAIL == nBytes || count >= bytesToCapture)
          break;

        count += SPHENC_FRAME_SIZE*4;
      }

      if (T->useAlgorithm)
      {
        stereoToMono( (short *)buff, (short *)T->g.senc.inBuf.start, SPHENC_FRAME_SIZE);
        buff = T->g.senc.inBuf.start;

        memset(T->g.senc.outBuf.start, 0, T->g.senc.outBuf.size);
        if (DVEVM_ST_FAIL == dvtb_sphEncEncode(&T->g.senc))
        {
          SYS_ERROR("Unable to encode the input buffer\n");
          break;
        }
        buff = T->g.senc.outBuf.start;
        fwrite(buff, 1, T->g.senc.outBuf.size, T->targetFp);
      }
      else
      {
      //  stereoToMono( (short *)buff, (short *)T->g.senc.inBuf.start, SPHENC_FRAME_SIZE);
      //  buff = T->g.senc.inBuf.start;
          fwrite(buff, 1, SPHENC_FRAME_SIZE*4, T->targetFp);
      }

    }
  } while (DVEVM_ST_FALSE); // Dummy loop

  SYS_OUT("Speech [capture][encode] completed\n");

  if (!T->sourceFp)
    dvtb_audioClose(&T->g.aud);

  if (T->useAlgorithm)
  {
    dvtb_sphEncClose(&T->g.senc);
    SYS_OUT("Speech Encoder <%s> closed\n", T->g.senc.sencName);

    Engine_close(T->g.senc.ceHdl);
    SYS_OUT("Engine <%s> closed\n", T->g.eng.name);
  }
  else
    free(T->g.senc.inBuf.start);

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

  SYS_OUT("Speech Capture thread exiting\n");

  dvtb_freeThr(T);
  dvtb_threadExit();
}
