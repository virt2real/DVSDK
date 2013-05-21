/*
 * dvtbVidEnc.h
 *
 * XDM0.9 Video Encode Interface
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

#ifndef _DVEVM_ST_VID_ENC_H
#define _DVEVM_ST_VID_ENC_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/ce/video/videnc.h>

#define VIDENC_MAX_HT   (480)
#define VIDENC_MAX_WD   (720)
#define VIDENC_MAX_FR   (30000)
#define VIDENC_MAX_BR   (4000000)
#define VIDENC_INTRA_FI (30)

#define DEF_CAP_FRAMES  (30)

typedef struct
{
  char vencName[MAX_NAME_LEN];                  // Codec Name
  VIDENC_Params vencParams;                     // Encoder parameters

  VIDENC_Cmd vencCmd;                           // Codec control Command
  VIDENC_DynamicParams vencDynParams;           // Encoder - Dynamic Parameters
  VIDENC_Status vencStatus;                     // Status of encode process
  VIDENC_InArgs vencInArgs;                   // Video Encoder output arguments
  VIDENC_OutArgs vencOutArgs;                   // Video Encoder output arguments

  DvevmStXdmBuffer inBuf;                       // Input XDM Buffer
  DvevmStXdmBuffer outBuf;                      // Output XDM Buffer

  Engine_Handle ceHdl;                          // Codec Engine Handle
  VIDENC_Handle vencHdl;                        // Encoder Handle

  int numFrames;                                // Number of frames to encode
} DvevmStVidEncInfo;

DvevmStRetCode
dvtb_vidEncInit(DvevmStVidEncInfo *ve);

DvevmStRetCode
dvtb_vidEncEncode(DvevmStVidEncInfo *ve, int* encDuration);

DvevmStRetCode
dvtb_vidEncControl(DvevmStVidEncInfo *ve);

DvevmStRetCode
dvtb_vidEncClose(DvevmStVidEncInfo *ve);

#endif
