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
 * @defgroup   ti_sdo_dmai_Resize   Resize
 *
 * @brief This module implements resizing an image between two resolutions.
 *        Typical example below (dm6467 resizing from a 720P buffer to a
 *        D1 sized buffer):
 *
 * @remark Following resizer functions are not supported in DM365. 
 *         The resizer is chained with capture device always and not available  
 *         for single shot mode. Following functions requires resizer to be in
 *         single shot mode. To use the resizer in single_shot_mode, 
 *         change captureChainMode = FALSE in Capture.c.
 *
 * @code
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Dmai.h>
 *   #include <ti/sdo/dmai/Resize.h>
 *   #include <ti/sdo/dmai/BufferGfx.h>
 *
 *   BufferGfx_Attrs gfxAttrs = BufferGfx_Attrs_DEFAULT;
 *   Resize_Attrs rszAttrs = Resize_Attrs_DEFAULT;
 *   Buffer_Handle inBuf, outBuf;
 *   Capture_Handle hCap;
 *   Resize_Handle hResize;
 *   Int32 bufSize;
 *
 *   Dmai_init();
 *   bufSize = BufferGfx_calcSize(VideoStd_D1_NTSC,
 *                                ColorSpace_420P);
 *   BufferGfx_calcDimensions(VideoStd_D1_NTSC,
 *                            ColorSpace_420P, &gfxAttrs.dim);
 *   gfxAttrs.colorSpace = ColorSpace_420P;
 *   outBuf = Buffer_create(bufSize, Buffer_getBufferAttrs(&gfxAttrs));
 *
 *   bufSize = BufferGfx_calcSize(VideoStd_720P,
 *                                ColorSpace_420P);
 *   BufferGfx_calcDimensions(VideoStd_720P,
 *                            ColorSpace_420P, &gfxAttrs.dim);
 *   gfxAttrs.colorSpace = ColorSpace_420P;
 *   inBuf = Buffer_create(bufSize, Buffer_getBufferAttrs(&gfxAttrs));
 *
 *   Resize_create(&rszAttrs);
 *   Resize_config(hInBuf, hOutBuf);
 *   // Fill hInBuf with video data
 *   Resize_execute(hResize, inBuf, outBuf);
 *
 *   Buffer_delete(inBuf);
 *   Buffer_delete(outBuf);
 *   Resize_delete(hResize);
 * @endcode
 */

#ifndef ti_sdo_dmai_Resize_h_
#define ti_sdo_dmai_Resize_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufferGfx.h>

/** @ingroup    ti_sdo_dmai_Resize */
/*@{*/

/**
 * @brief The window types supported for coefficient calculation.
 * @remarks Only applicable on dm6446 linux.
 */
typedef enum {
    Resize_WindowType_HANN = 0,
    Resize_WindowType_BLACKMAN,
    Resize_WindowType_TRIANGULAR,
    Resize_WindowType_RECTANGULAR
} Resize_WindowType;

/**
 * @brief The filter types supported for coefficient calculation.
 * @remarks Only applicable on dm6446 linux.
 */
typedef enum {
    Resize_FilterType_BILINEAR = 0,
    Resize_FilterType_BICUBIC,
    Resize_FilterType_LOWPASS
} Resize_FilterType;

/**
 * @brief       Handle through which to reference a Resize job.
 */
typedef struct Resize_Object *Resize_Handle;

/**
 * @brief       Attributes used to create a Resize job.
 * @see         Resize_Attrs_DEFAULT.
 */
typedef struct Resize_Attrs {
    /**
     * @brief Horizontal window type.
     * @remarks Only applicable on dm6446 linux.
     */
    Resize_WindowType   hWindowType;

    /**
     * @brief Vertical window type.
     * @remarks Only applicable on dm6446 linux.
     */
    Resize_WindowType   vWindowType;

    /**
     * @brief Horizontal filter type.
     * @remarks Only applicable on dm6446 linux.
     */
    Resize_FilterType   hFilterType;

    /**
     * @brief Vertical filter type.
     * @remarks Only applicable on dm6446 linux.
     */
    Resize_FilterType   vFilterType;

    /** @brief The rate of the resizer H/W to use.
      * @remarks Only applicable on dm6446 Linux */
    Int                 rszRate;
} Resize_Attrs;

/**
 * @brief       Default attributes for a Resize job.
 * @code
 * hWindowType      = Resize_WindowType_BLACKMAN,
 * vWindowType      = Resize_WindowType_BLACKMAN,
 * hFilterType      = Resize_FilterType_LOWPASS,
 * vFilterType      = Resize_FilterType_LOWPASS,
 * rszRate          = 0xe
 * @endcode
 */
extern const Resize_Attrs Resize_Attrs_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Resize job.
 *
 * @param[in]   attrs       #Resize_Attrs to use for creating the Resize job.
 *
 * @retval      Handle for use in subsequent operations (see #Resize_Handle).
 * @retval      NULL for failure.
 */
extern Resize_Handle Resize_create(Resize_Attrs *attrs);

/**
 * @brief       Configure a Resize job.
 *
 * @param[in]   hResize     The #Resize_Handle of the job to configure.
 * @param[in]   hSrcBuf     The source buffer to configure for. Note that only
 *                          the buffer properties are accessed, the pointers
 *                          are not used.
 * @param[in]   hDstBuf     The destination buffer to configure for. Note that
 *                          only the buffer properties are accessed, the
 *                          pointers are not used.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Resize_create must be called before this function.
 */
extern Int Resize_config(Resize_Handle hResize,
                         Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf);

/**
 * @brief       Execute a Resize job.
 *
 * @param[in]   hResize     The #Resize_Handle of the job to execute.
 * @param[in]   hSrcBuf     The #Buffer_Handle of the source buffer to
 *                          copy from.
 * @param[in]   hDstBuf     The #Buffer_Handle of the destination buffer
 *                          to copy to.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Resize_create must be called before this function.
 * @remarks     #Resize_config must be called before this function.
 */
extern Int Resize_execute(Resize_Handle hResize,
                          Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf);

/**
 * @brief       Deletes a Resize job.
 *
 * @param[in]   hResize     The #Resize_Handle of the job to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Resize_create must be called before this function.
 */
extern Int Resize_delete(Resize_Handle hResize);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Resize_h_ */
