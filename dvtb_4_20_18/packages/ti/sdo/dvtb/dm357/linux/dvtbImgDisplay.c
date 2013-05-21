/*
 * dvtbImgDisplay.c
 *
 * XDM0.9 Image Decode functionality
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

#include "dvtbImgDisplay.h"
#include "dvtbFBVPBE.h"
#include "dvtbImgDec.h"
#include "dvtbMemory.h"
#include "dvtbDefs.h"

void
dvtb_imgDecDisplay(DvevmStThreadInfo *T)
{
  DvevmStRetCode status=DVEVM_ST_FAIL;
  DvevmStXdmBuffer *inbuf=NULL, *outbuf=NULL, dispBuff;
  int i, nBytes=DVEVM_ST_FAIL, bytes2Read, bytesRemaining=0;
  long int ipFileLength;

  SYS_DEBUG("Image [Decode][Display] with <%s> option\n", (T->useAlgorithm)?"USE DSP":"NO DSP");

  if (!T->sourceFp)
  {
    SYS_ERROR("Source file cannot be opened. It is a mandatory parameter\n");
    dvtb_freeThr(T);
    dvtb_threadExit();
  }
  else
  {
    fseek(T->sourceFp, 0L, SEEK_END);
    T->g.idec.idecInArgs.numBytes = ipFileLength = ftell(T->sourceFp);
    fseek(T->sourceFp, -ipFileLength, SEEK_END);
  }

  // [Decode][Display] scenario
  do
  {
    SYS_OUT("Image [Decode][Display] started\n");

    if (T->useAlgorithm)
    {
      if (DVEVM_ST_FAIL == dvtb_ceInit(T->g.eng.name, &T->g.idec.ceHdl))
      {
        SYS_ERROR("Unable to initialize Codec Engine <%s>\n", T->g.eng.name);
        break;
      }
      else if (DVEVM_ST_FAIL == dvtb_imgDecInit(&T->g.idec))
      {
        SYS_ERROR("Unable to initialize Image Decoder <%s>\n", T->g.idec.idecName);
        break;
      }
      else
        SYS_OUT("Image Decoder <%s> initialized\n", T->g.idec.idecName);

      outbuf = &T->g.idec.outBuf;
      inbuf = &T->g.idec.inBuf;
    }
    else
    {
      dispBuff.numBufs = 1;
      dispBuff.bufSizes[0] = T->g.vpbe.imageWidth * T->g.vpbe.imageHeight * 2;

      if (DVEVM_ST_FAIL == dvtb_allocCmem(&dispBuff))
      {
        SYS_OUT("Unable to allocate memory for image display\n");
        break;
      }

      inbuf = outbuf = &dispBuff;
    }

    bytesRemaining = ipFileLength;
    bytes2Read = inbuf->bufSizes[0];

    do
    {
      nBytes = fread(inbuf->bufs[0], 1, bytes2Read, T->sourceFp);

      if (0 == nBytes)
        break;

      if (T->useAlgorithm)
      {
        T->g.idec.idecInArgs.size = sizeof(T->g.idec.idecInArgs);
        T->g.idec.idecInArgs.numBytes = nBytes;

        //Call Process twice once with XDM Parse header and second with XDM
        //decode AU
        T->g.idec.idecDynParams.decodeHeader = XDM_PARSE_HEADER;
        T->g.idec.idecCmd = XDM_SETPARAMS;
        if (DVEVM_ST_FAIL == dvtb_imgDecControl(&T->g.idec))
        {
          SYS_ERROR("Unable to set the XDM_PARSE_HEADER using XDM_SETPARAMS\n");
          break;
        }

        if (DVEVM_ST_FAIL == dvtb_imgDecDecode(&T->g.idec))
        {
          SYS_ERROR("Unable to decode Header. Content <%s> size (%d) bytes\n",T->g.idec.idecName, nBytes);
          break;
        }

        dvtb_freeCmem(&T->g.idec.inBuf);
        dvtb_freeCmem(&T->g.idec.outBuf);

        //This GETSTATUS gets the actual buffer
        T->g.idec.idecCmd = XDM_GETSTATUS;
        if (DVEVM_ST_FAIL == dvtb_imgDecControl(&T->g.idec))
        {
          SYS_ERROR("Unable to get the actual buffer size using XDM_GETSTATUS.\n");
          break;
        }

        T->g.idec.idecDynParams.decodeHeader = XDM_DECODE_AU;
        T->g.idec.idecCmd = XDM_RESET;
        if (DVEVM_ST_FAIL == dvtb_imgDecControl(&T->g.idec))
        {
          SYS_ERROR("Unable to set dynamic parameters\n");
          break;
        }

        if (DVEVM_ST_FAIL == dvtb_allocCmem(&T->g.idec.inBuf))
        {
          SYS_ERROR("Unable to allocate memory for input buffer\n");
          break;
        }

        if (DVEVM_ST_FAIL == dvtb_allocCmem(&T->g.idec.outBuf))
        {
          SYS_ERROR("Unable to allocate memory for output buffer\n");
          break;
        }

        fseek(T->sourceFp, 0L, SEEK_SET);
        memset(inbuf->bufs[0], 0, inbuf->bufSizes[0]);
        nBytes = fread(inbuf->bufs[0], 1, inbuf->bufSizes[0], T->sourceFp);
        T->g.idec.idecInArgs.numBytes = nBytes;

        if (DVEVM_ST_FAIL == dvtb_imgDecDecode(&T->g.idec))
        {
          SYS_ERROR("Unable to decode <%s> size (%d) bytes\n",T->g.idec.idecName, nBytes);
          break;
        }

        T->g.idec.idecCmd = XDM_GETSTATUS;
        if (DVEVM_ST_FAIL == dvtb_imgDecControl(&T->g.idec))
        {
          SYS_ERROR("Unable to get the status.\n");
          break;
        }

        T->g.vpbe.imageWidth = T->g.idec.idecStatus.outputWidth;
        T->g.vpbe.imageHeight = T->g.idec.idecStatus.outputHeight;

        if (T->targetFp)
        {
          for (i=0; i<outbuf->numBufs; i++)
          {
            status = fwrite(outbuf->bufs[i], 1, outbuf->bufSizes[i], T->targetFp);

            if (DVEVM_ST_FAIL == status)
              break;
          }
        }
        else
        {
          status = (*dvtb_vpbeSetupPtr)(&T->g.vpbe);
          if (DVEVM_ST_FAIL == status)
          {
            SYS_ERROR("Unable to setup VPBE device <%s> for display\n", T->g.vpbe.device);
            break;
          }
          else
            SYS_OUT("VPBE device <%s> initialized for display\n", T->g.vpbe.device);

          status = dvtb_vpbeDisplay(&T->g.vpbe, outbuf->bufs[0]);
        }

        if (DVEVM_ST_FAIL == status)
        {
          SYS_ERROR("Unable to write into target device\n");
          break;
        }
      }
    }while(DVEVM_ST_FALSE);

  } while (DVEVM_ST_FALSE); // Dummy loop

  SYS_OUT("Image [Decode][Display] completed\n");

  if (!T->targetFp)
  {
	  /*Wait for 3 Secs before going blank so that image displayed can be viewed. */
	    sleep(3);
	    dvtb_vpbeClose(&T->g.vpbe);
	    SYS_OUT("VPBE Device <%s> closed\n", T->g.vpbe.device);
  }

  if (T->useAlgorithm)
  {
    dvtb_imgDecClose(&T->g.idec);
    SYS_OUT("Image Decoder <%s> closed\n", T->g.idec.idecName);

    Engine_close(T->g.idec.ceHdl);
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

  SYS_OUT("Image Display thread exiting\n");

  dvtb_freeThr(T);
  dvtb_threadExit();
}

