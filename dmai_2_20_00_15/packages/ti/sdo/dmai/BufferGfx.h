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
 * @defgroup   ti_sdo_dmai_BufferGfx   BufferGfx
 *
 * @brief Describes a graphics buffer. The other DMAI modules perform
 *        graphics operations on instances of this module. This module is a
 *        submodule of the Buffer module, and all the Buffer module functions
 *        can also be used on a BufferGfx instance. Typical usage below
 *        for a D1 PAL sized buffer of color type UYVY (no error checking):
 *
 * @code
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/BufferGfx.h>
 *   BufferGfx_Handle hBuf;
 *   Int32 size;
 *   BufferGfx_Attrs gfxAttrs = BufferGfx_Attrs_DEFAULT;
 *
 *   Dmai_init();
 *   size = BufferGfx_calcSize(VideoStd_D1_PAL, ColorSpace_UYVY);
 *   BufferGfx_calcDimensions(VideoStd_D1_PAL, ColorSpace_UYVY, &gfxAttrs.dim);
 *   gfxAttrs.colorSpace = ColorSpace_UYVY;
 *   hBuf = Buffer_create(size, Buffer_getBufferAttrs(&gfxAttrs));
 *   // Operate on graphics Buffer
 *   Buffer_delete(hBuf);
 * @endcode
 */

#ifndef ti_sdo_dmai_BufferGfx_h_
#define ti_sdo_dmai_BufferGfx_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/VideoStd.h>
#include <ti/sdo/dmai/ColorSpace.h>

/** @ingroup    ti_sdo_dmai_BufferGfx */
/*@{*/

/**
 * @brief Describes the dimensions of a graphics Buffer.
 */
typedef struct BufferGfx_Dimensions {
    /** @brief The X position of the buffer relative to upper left corner. */
    Int32                   x;

    /** @brief The Y position of the buffer relative to upper left corner. */
    Int32                   y;

    /** @brief The width of the buffer. */
    Int32                   width;

    /** @brief The height of the buffer. */
    Int32                   height;

    /** @brief The line length (also called pitch) of the buffer. This is
      * defined as the number of bytes between lines in an image buffer.*/
    Int32                   lineLength;
} BufferGfx_Dimensions;

/**
 * @brief Describes the attributes used to create a BufferGfx instance.
 * @see BufferGfx_Attrs_DEFAULT
 */
typedef struct BufferGfx_Attrs {
    /** @brief The basic #Buffer_Attrs to use for creating the buffer. */
    Buffer_Attrs            bAttrs;

    /** @brief The #ColorSpace_Type of the buffer. */
    ColorSpace_Type         colorSpace;

    /** @brief The original dimensions of the buffer. */
    BufferGfx_Dimensions    dim;
} BufferGfx_Attrs;

/**
 * @brief The default #BufferGfx_Attrs used to create a BufferGfx instance.
 * @code
 * bAttrs       = {
 *     memParams     = Buffer_Memory_Params_DEFAULT
 *     type          = Buffer_Type_GRAPHICS,
 *     useMask       = 1
 * },
 * colorSpace   = ColorSpace_NOTSET,
 * dim          = { 0, 0, 0, 0, 0 }
 * @endcode
 */
extern const BufferGfx_Attrs BufferGfx_Attrs_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Get the basic #Buffer_Attrs of a #BufferGfx_Attrs structure.
 *
 * @param[in]   gfxAttrs        A #BufferGfx_Attrs pointer to the full
 *                              graphics attrs.
 *
 * @retval      Pointer to the basic #Buffer_Attrs.
 *
 * @remarks     This is used when calling #Buffer_create and is safer than
 *              type casting.
 */
extern Buffer_Attrs *BufferGfx_getBufferAttrs(BufferGfx_Attrs *gfxAttrs);

/**
 * @brief       Calculate the size of a Buffer given a #VideoStd_Type and
 *              a #ColorSpace_Type.
 *
 * @param[in]   videoStd        Video standard, see #VideoStd_Type.
 * @param[in]   colorSpace      Color space type, see #ColorSpace_Type.
 *
 * @retval      Size estimation in bytes of the graphics Buffer.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int32 BufferGfx_calcSize(VideoStd_Type videoStd,
                                ColorSpace_Type colorSpace);

/**
 * @brief       Calculate the size of a Buffer given #BufferGfx_Dimensions and
 *              a #ColorSpace_Type.
 *
 * @param[in]   dimPtr          Dimensions of the graphics Buffer.
 * @param[in]   colorSpace      Color space type, see #ColorSpace_Type.
 *
 * @retval      Size estimation in bytes of the graphics Buffer.
 */
extern Int32 BufferGfx_calcSizeDim(BufferGfx_Dimensions *dimPtr,
                                   ColorSpace_Type colorSpace);

/**
 * @brief       Calculate the dimensions of a Buffer given a #VideoStd_Type and
 *              a #ColorSpace_Type.
 *
 * @param[in]   videoStd        Video standard, see #VideoStd_Type.
 * @param[in]   colorSpace      Color space type, see #ColorSpace_Type.
 * @param[out]  dimPtr          Pointer to a #BufferGfx_Dimensions structure
 *                              to fill in with the calculate dimensions.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int BufferGfx_calcDimensions(VideoStd_Type videoStd,
                                    ColorSpace_Type colorSpace,
                                    BufferGfx_Dimensions *dimPtr);

/**
 * @brief       Calculate the line length (pitch) of a Buffer given a
 *              #ColorSpace_Type.
 *
 * @param[in]   colorSpace      Color space type, see #ColorSpace_Type.
 * @param[in]   width           The width to calculate the line length for.
 *
 * @retval      "Line length" as a result of the calculation.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int32 BufferGfx_calcLineLength(Int32 width, ColorSpace_Type colorSpace);

/**
 * @brief       Get the frame type of a BufferGfx instance.
 *
 * @param[in]   hBuf        Handle to the Buffer to get the frame type for.
 *
 * @retval      "Frame Type"
 *
 * @remarks     For more information on frame type, see IVIDEO_FrameType in
 *              the XDM documenation.
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Int32 BufferGfx_getFrameType(Buffer_Handle hBuf);

/**
 * @brief       Set the frame type of a BufferGfx instance,
 *
 * @param[in]   hBuf        Handle to the graphics Buffer to get the frame
 *                          type for.
 * @param[in]   frameType   Frane type to set the Buffer to.
 *
 * @remarks     For more information on frame type, see IVIDEO_FrameType in
 *              the XDM documenation.
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Void BufferGfx_setFrameType(Buffer_Handle hBuf, Int32 frameType);

/**
 * @brief       Get the #ColorSpace_Type of a BufferGfx instance.
 *
 * @param[in]   hBuf        Handle to the graphics Buffer to get the color
 *                          space type for
 *
 * @retval      Type of color space of Buffer (see #ColorSpace_Type).
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern ColorSpace_Type BufferGfx_getColorSpace(Buffer_Handle hBuf);

/**
 * @brief       Set the #ColorSpace_Type of a BufferGfx instance.
 *
 * @param[in]   hBuf        Handle to the graphics Buffer to set the color
 *                          space type for
 * @param[in]   colorSpace  #ColorSpace_Type to set the Buffer to.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Void BufferGfx_setColorSpace(Buffer_Handle hBuf,
                                    ColorSpace_Type colorSpace);

/**
 * @brief       Get the #BufferGfx_Dimensions of a BufferGfx instance. If
 *              the current dimensions are not set (all fields set to 0),
 *              the original dimensions will be returned, otherwise the
 *              current dimensions are returned.
 *
 * @param[in]   hBuf        Handle to the graphics Buffer to get the
 *                          dimensions for.
 * @param[out]  dimPtr      Dimensions of the graphics Buffer is returned here.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Void BufferGfx_getDimensions(Buffer_Handle hBuf,
                                    BufferGfx_Dimensions *dimPtr);

/**
 * @brief       Set the current #BufferGfx_Dimensions of a BufferGfx instance.
 *
 * @param[in]   hBuf        Handle to the graphics Buffer to set the
 *                          dimensions for.
 * @param[out]  dimPtr      Dimensions of the graphics Buffer to set.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Int BufferGfx_setDimensions(Buffer_Handle hBuf,
                                   BufferGfx_Dimensions *dimPtr);

/**
 * @brief       Reset the dimensions to the original create time dimensions.
 *
 * @param[in]   hBuf        Handle to the graphics Buffer to reset the
 *                          dimensions for.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Void BufferGfx_resetDimensions(Buffer_Handle hBuf);

/**
 * @brief       Set the maximum dimensions of a Buffer reference.
 *
 * @param[in]   hBuf        Handle to the graphics Buffer reference to set
 *                          the maximum dimensions of.
 * @param[in]   dimPtr      Maximum dimensions to set.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     The Buffer instance passed need to having been created as a
 *              reference, see #Buffer_Attrs.reference.
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Int BufferGfx_setMaxDimensions(Buffer_Handle hBuf,
                                      BufferGfx_Dimensions *dimPtr);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_BufferGfx_h_ */
