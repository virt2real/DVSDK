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

#include <xdc/std.h>
#include <ti/sdo/dmai/VideoStd.h>

#define MODULE_NAME     "VideoStd"

Int VideoStd_getResolution(VideoStd_Type videoStd,
                           Int32 *widthPtr, Int32 *heightPtr)
{
    assert(widthPtr);
    assert(heightPtr);

    switch (videoStd) {
        case VideoStd_QVGA:
            *widthPtr  = VideoStd_QVGA_WIDTH;
            *heightPtr = VideoStd_QVGA_HEIGHT;
            break;
        case VideoStd_CIF:
            *widthPtr  = VideoStd_CIF_WIDTH;
            *heightPtr = VideoStd_CIF_HEIGHT;
            break;
        case VideoStd_SIF_NTSC:
            *widthPtr  = VideoStd_SIF_WIDTH;
            *heightPtr = VideoStd_SIF_NTSC_HEIGHT;
            break;
        case VideoStd_SIF_PAL:
            *widthPtr  = VideoStd_SIF_WIDTH;
            *heightPtr = VideoStd_SIF_PAL_HEIGHT;
            break;
        case VideoStd_VGA:
            *widthPtr = VideoStd_VGA_WIDTH;
            *heightPtr = VideoStd_VGA_HEIGHT;
            break;
        case VideoStd_D1_NTSC:
        case VideoStd_480P:
            *widthPtr = VideoStd_D1_WIDTH;
            *heightPtr = VideoStd_D1_NTSC_HEIGHT;
            break;
        case VideoStd_D1_PAL:
        case VideoStd_576P:
            *widthPtr = VideoStd_D1_WIDTH;
            *heightPtr = VideoStd_D1_PAL_HEIGHT;
            break;
        case VideoStd_720P_30:
        case VideoStd_720P_50:
        case VideoStd_720P_60:
            *widthPtr = VideoStd_720P_WIDTH;
            *heightPtr = VideoStd_720P_HEIGHT;
            break;
        case VideoStd_1080I_25:
        case VideoStd_1080I_30:
        case VideoStd_1080I_60:
        case VideoStd_1080P_24:
        case VideoStd_1080P_25:
        case VideoStd_1080P_30:
        case VideoStd_1080P_60:
        case VideoStd_1080P_50:            
            *widthPtr = VideoStd_1080I_WIDTH;
            *heightPtr = VideoStd_1080I_HEIGHT;
            break;
        default:
            Dmai_err1("Unknown video standard (%d)\n", videoStd);
            return Dmai_EINVAL;
    }

    return Dmai_EOK;
}

