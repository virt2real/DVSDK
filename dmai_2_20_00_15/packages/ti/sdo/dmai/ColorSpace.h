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

/**
 * @defgroup   ti_sdo_dmai_ColorSpace     ColorSpace
 *
 * @brief This module provides support for the different color spaces
 *        available to the Buffer_Objects
 *
 */

#ifndef ti_sdo_dmai_ColorSpace_h_
#define ti_sdo_dmai_ColorSpace_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>

/** @ingroup    ti_sdo_dmai_ColorSpace */
/*@{*/

/**
  * @brief Color formats.
  */
typedef enum {
    ColorSpace_NOTSET = -1,

    /**
      * @brief YUV 420 semi planar corresponding to V4L2_PIX_FMT_NV12 in v4l2.
      *        This format consists of two planes: one with the Y component
      *        and one with the CbCr components interleaved (hence semi).
      *        See the LSP documentation for a thorough description of this
      *        format.
      */
    ColorSpace_YUV420PSEMI = 0,

    /**
      * @brief YUV 422 semi planar corresponding to V4L2_PIX_FMT_YUV422UVP. This
      *        format was added to v4l2 by TI because the dm6467 VDCE and VPSS
      *        peripherals use this format. The format consists of two planes:
      *        one with the Y component and one with the CbCr components
      *        interleaved (hence semi) See the LSP VDCE documentation for a
      *        thorough description of this format.
      */
    ColorSpace_YUV422PSEMI,

    /** @brief YUV 422 interleaved corresponding to V4L2_PIX_FMT_UYVY in v4l2 */
    ColorSpace_UYVY,
    
    /** @brief RGB 888 packed corresponding to V4L2_PIX_FMT_RGB24 in v4l2 */
    ColorSpace_RGB888,

    /** @brief RGB 565 packed corresponding to V4L2_PIX_FMT_RGB565 in v4l2 */
    ColorSpace_RGB565,

    /**
      * @brief 2 bits per pixel. This is the format used by the VDCE for the
      *        bitmap while blending and is documented in the VDCE peripheral
      *        guide.
      */
    ColorSpace_2BIT,
    
    /**
      * @brief YUV 420 planar. The format consists of three planes:
      *        one with the Y component, one Cb, and one Cr component.
      */
    ColorSpace_YUV420P,
    
    /**
      * @brief YUV 422 planar. The format consists of three planes:
      *        one with the Y component, one Cb, and one Cr component.
      */
    ColorSpace_YUV422P,

    /**
      * @brief YUV 444 planar. The format consists of three planes:
      *        one with the Y component, one Cb, and one Cr component.
      */
    ColorSpace_YUV444P,
    
    /**
      * @brief Gray Scale. The format consist of single Luma plane
      *        ignoring the color plane components.      
      *             
      */
    ColorSpace_GRAY,

    ColorSpace_COUNT
} ColorSpace_Type;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Calculates the bits per pixel for a given color space format.
 *
 * @param[in]   colorSpace      The #ColorSpace_Type to calculate for.
 *
 * @retval      "Bits per pixel" for the given color space format.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int ColorSpace_getBpp(ColorSpace_Type colorSpace);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_ColorSpace_h_ */
