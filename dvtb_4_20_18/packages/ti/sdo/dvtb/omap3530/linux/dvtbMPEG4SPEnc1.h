/*
 * dvtbMPEG4SPEnc1.h
 *
 * XDM1.0 MPEG4 SP Encode Interface
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

#ifndef _DVEVM_ST_MPEG4SP_ENC_H
#define _DVEVM_ST_MPEG4SP_ENC_H

#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#include <ti/sdo/codecs/mpeg4enc/imp4venc.h>
#include <ti/sdo/ce/video1/videnc1.h>

/* Macro definitions for constants and Buffer sizes*/
#define MPEG4SPENC_IMAGE_WIDTH         1280        //!< Width of the Display Buffer
#define MPEG4SPENC_IMAGE_HEIGHT        (960)    //!< Height of the Display Buffer
#define MPEG4SPENC_INPUT_BUFFER_SIZE   (MPEG4SPENC_IMAGE_WIDTH*MPEG4SPENC_IMAGE_HEIGHT*2)        //!< Input Buf Size

typedef struct {
        char venc1Name[MAX_NAME_LEN]; // Codec Name

        IMP4VENC_Params venc1Params; // Encoder parameters
        IMP4VENC_DynamicParams venc1DynParams; // Encoder - Dynamic Parameters

        VIDENC1_Cmd venc1Cmd; // Codec control Command

        IMP4VENC_Status venc1Status; // Status of encode process

        IMP4VENC_InArgs venc1InArgs; // Video Encoder input arguments
        IMP4VENC_OutArgs venc1OutArgs; // Video Encoder output arguments

        DvevmStXdmBuffer inBuf;
        DvevmStXdmBuffer outBuf;
        IVIDEO1_BufDescIn inBufDesc; // Input XDM Buffer
        XDM_BufDesc outBufDesc; // Output XDM Buffer

        Engine_Handle ceHdl; // Codec Engine Handle
        VIDENC1_Handle venc1Hdl; // Encoder Handle

        int numFrames; // Number of frames to encode
} DvevmStMPEG4SPVEncInfo;


DvevmStRetCode
dvtb_mpeg4spEnc1Init(DvevmStMPEG4SPVEncInfo *ve);

DvevmStRetCode
dvtb_mpeg4spEnc1Encode(DvevmStMPEG4SPVEncInfo *ve, int *encDuration);

DvevmStRetCode
dvtb_mpeg4spEnc1Control(DvevmStMPEG4SPVEncInfo *ve);

void
dvtb_mpeg4spEncCleanup(DvevmStMPEG4SPVEncInfo *ve);

DvevmStRetCode
dvtb_mpeg4spEnc1Close(DvevmStMPEG4SPVEncInfo *ve);

#endif
