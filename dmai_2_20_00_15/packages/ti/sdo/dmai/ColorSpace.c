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
#include <ti/sdo/dmai/ColorSpace.h>

#define MODULE_NAME     "ColorSpace"

/******************************************************************************
 * ColorSpace_getBpp
 ******************************************************************************/
Int ColorSpace_getBpp(ColorSpace_Type colorSpace)
{
    Int bpp;

    switch (colorSpace) {
        case ColorSpace_RGB888:
            bpp = 32;
            break;

        case ColorSpace_YUV444P: 
            bpp = 24;
            break;

        case ColorSpace_RGB565:
        case ColorSpace_UYVY:
            bpp = 16;
            break;

        case ColorSpace_GRAY:             
        case ColorSpace_YUV422P: 
        case ColorSpace_YUV420P:
        case ColorSpace_YUV420PSEMI:
        case ColorSpace_YUV422PSEMI:
            bpp = 8;
            break;
            
        case ColorSpace_2BIT:
            bpp = 2;
            break;

        default:
            Dmai_err1("Unknown color space format (%d)\n", colorSpace);
            return Dmai_EINVAL;
    }

    return bpp;
}
