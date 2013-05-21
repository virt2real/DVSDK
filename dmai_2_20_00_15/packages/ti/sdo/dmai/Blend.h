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
 * @defgroup   ti_sdo_dmai_Blend        Blend
 *
 * @brief This module implements the blending of a bitmap buffer with a video
 *        buffer. Typical usage (2 bit in place blending of a 120x240 bitmap
 *        to a VGA sized 420Psemi buffer, no error checking):
 *
 * @code
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Dmai.h>
 *   #include <ti/sdo/dmai/Blend.h>
 *   #include <ti/sdo/dmai/BufferGfx.h>
 *
 *   BufferGfx_Attrs gfxAttrs;
 *   Blend_Attrs blAttrs = Blend_Attrs_DEFAULT;
 *   Blend_Config_Params bConfigParams = Blend_Config_Params_DEFAULT;
 *   Buffer_Handle hBmpBuf, hBuf;
 *   Blend_Handle hBlend;
 *   Int32 bufSize;
 *
 *   Dmai_init();
 *   gfxAttrs = BufferGfx_Attrs_DEFAULT;
 *   gfxAttrs.colorSpace     = ColorSpace_2BIT;
 *   gfxAttrs.dim.width      = 120;
 *   gfxAttrs.dim.height     = 240;
 *   gfxAttrs.dim.lineLength = BufferGfx_calcLineLength(gfxAttrs.dim.width,
 *                                                      ColorSpace_2BIT);
 *   bufSize = gfxAttrs.dim.lineLength * gfxAttrs.dim.height;
 *   hBmpBuf = Buffer_create(bufSize, BufferGfx_getBufferAttrs(&gfxAttrs)); 
 *
 *   gfxAttrs = BufferGfx_Attrs_DEFAULT;
 *   gfxAttrs.colorSpace     = ColorSpace_422Psemi;
 *   gfxAttrs.dim.width      = 640;
 *   gfxAttrs.dim.height     = 480;
 *   gfxAttrs.dim.lineLength = BufferGfx_calcLineLength(gfxAttrs.dim.width
 *                                                      ColorSpace_422Psemi);
 *   bufSize = gfxAttrs.dim.lineLength * gfxAttrs.dim.height;
 *   hBuf = Buffer_create(bufSize, BufferGfx_getBufferAttrs(&gfxAttrs)); 
 *
 *   hBlend = Blend_create(&blAttrs);
 *   Blend_config(hBlend, NULL, hBmpBuf, hBuf, hBuf, &bConfigParams);
 *   Blend_execute(hBlend, hBmpBuf, hBuf, 0, hBuf, 0);
 *
 *   Blend_delete(hBlend);
 *   Buffer_delete(hBuf);
 *   Buffer_delete(hBmpBuf);
 * @endcode
 */
#ifndef ti_sdo_dmai_Blend_h_
#define ti_sdo_dmai_Blend_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Ccv.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Blend */
/*@{*/

/**
 * @brief       Attributes used to create a Blending job.
 * @see         Blend_Attrs_DEFAULT.
 */
typedef struct Blend_Attrs {
    /** @brief Currently no attributes for this module, but this may change. */
    Int dummy;
} Blend_Attrs;

/**
 * @brief       Configuration parameters used for configuring the Blending job.
 * @see         Blend_Config_Params_DEFAULT.
 */
typedef struct Blend_Config_Params {
    /** @brief The X position of the bitmap buffer in the video buffer */
    Int32   bmpXpos;

    /** @brief The Y position of the bitmap buffer in the video buffer */
    Int32   bmpYpos;

    /** @brief The VDCE palette to use for the bitmap */
    Int8    palette[4][4];
} Blend_Config_Params;

/**
 * @brief       Default configuration for a Blending job.
 * @code
 *     bmpXpos      = 0,
 *     bmpYpos      = 0,
 *     palette      = {
 *          { 0xf0, 0x5a, 0x51, 0xff, },
 *          { 0x22, 0x36, 0x91, 0xc0, },
 *          { 0x6e, 0xf0, 0x29, 0x80, },
 *          { 0xde, 0xca, 0x6a, 0x40, },
 *     }
 * @endcode
 */
extern const Blend_Config_Params Blend_Config_Params_DEFAULT;

/**
 * @brief       Default attributes for a Blending job.
 */
extern const Blend_Attrs Blend_Attrs_DEFAULT;

/**
 * @brief       Handle through which to reference a Blending job.
 */
typedef struct Blend_Object *Blend_Handle;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Blending job.
 *
 * @param[in]   attrs       #Blend_Attrs to use for creating the Blending job.
 *
 * @retval      Handle for use in subsequent operations (see #Blend_Handle).
 * @retval      NULL for failure.
 */
extern Blend_Handle Blend_create(Blend_Attrs *attrs);

/**
 * @brief       Configure a Blending job.
 *
 * @param[in]   hBlend      The #Blend_Handle of the job to configure.
 * @param[in]   hCcv        On dm6467 a Color Conversion job and a Blend job
 *                          can be done with one pass of the VDCE. If you pass
 *                          in a previously configured #Ccv_Handle here, the
 *                          Blend and Color conversion job will be done in one
 *                          pass, both of which will be invoked using
 *                          #Blend_execute (so don't use #Ccv_execute
 *                          separately). If this is not required, pass in NULL
 *                          and a separate VDCE pass will be used for blending.
 * @param[in]   hBmpBuf     The #Buffer_Handle of the bitmap buffer to configure
 *                          for. Note that only the buffer properties are
 *                          accessed, the pointers are not used.
 * @param[in]   hSrcBuf     The #Buffer_Handle of the source buffer to configure
 *                          for. Note that only the buffer properties are
 *                          accessed, the pointers are not used.
 * @param[in]   hDstBuf     The #Buffer_Handle of the destination buffer to
 *                          configure for. Note that only the buffer properties
 *                          are accessed, the pointers are not used.
 * @param[in]   params      A pointer to the #Blend_Config_Params to use while
 *                          configuring this Blending job.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int Blend_config(Blend_Handle hBlend,
                        Ccv_Handle hCcv,
                        Buffer_Handle hBmpBuf,
                        Buffer_Handle hSrcBuf,
                        Buffer_Handle hDstBuf,
                        Blend_Config_Params *params);

/**
 * @brief       Execute a Blending job.
 *
 * @param[in]   hBlend      The #Blend_Handle of the job to execute.
 * @param[in]   hBmpBuf     The bitmap buffer to blend in to hSrcBuf before
 *                          storing the result in hDstBuf.
 * @param[in]   hSrcBuf     The source buffer to blend in to.
 * @param[in]   hDstBuf     The destination buffer to store the result.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int Blend_execute(Blend_Handle hBlend, Buffer_Handle hBmpBuf,
                         Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf);

/**
 * @brief       Deletes a Blending job.
 *
 * @param[in]   hBlend      The #Blend_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int Blend_delete(Blend_Handle hBlend);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Blend_h_ */
