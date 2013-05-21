/* --COPYRIGHT--,BSD
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/


#ifndef ti_sdo_dai_linux_priv__VideoBuf_h_
#define ti_sdo_dai_linux_priv__VideoBuf_h_

#include <linux/videodev.h>
#include <linux/videodev2.h>

#include <ti/sdo/dmai/BufferGfx.h>

/* Used for internal buffer management */
typedef struct _VideoBufDesc {
    struct v4l2_buffer v4l2buf;
    Buffer_Handle      hBuf;
    Int                used;
} _VideoBufDesc;

/******************************************************************************
 * getUsedIdx
 ******************************************************************************/
static inline Int getUsedIdx(_VideoBufDesc *bufDescs, Int numBufDescs)
{
    Int idx;

    for (idx = 0; idx < numBufDescs; idx++) {
        if (bufDescs[idx].used == TRUE) {
            break;
        }
    }

    if (idx == numBufDescs) {
        return -1;
    }

    return idx;
}

extern Void _Dmai_blackFill(Buffer_Handle hBuf);

extern Int _Dmai_v4l2UserAlloc(Int fd, Int numBufs, enum v4l2_buf_type type,
                               struct _VideoBufDesc **bufDescsPtr,
                               BufTab_Handle hBufTab, Int topOffset,
                               ColorSpace_Type colorSpace, Int queueBuffers);

extern Int _Dmai_v4l2DriverAlloc(Int fd, Int numBufs, enum v4l2_buf_type type,
                                 struct _VideoBufDesc **bufDescsPtr,
                                 BufTab_Handle *hBufTabPtr, Int topOffset,
                                 ColorSpace_Type colorSpace);

#endif // ti_sdo_dai_linux_priv__VideoBuf_h_

