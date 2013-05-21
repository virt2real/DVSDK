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
 * @defgroup   ti_sdo_dmai_Smooth   Smooth
 *
 * @brief Reduces interlacing artifacts on a buffer. When capturing a frame
 *        from an interlaced medium, it actually consists of two fields 1/60s
 *        apart (D1 NTSC example). If an encoder that does not support
 *        interlaced frames, such as H.264 BP or MPEG4 SP is used on this
 *        buffer, suboptimal quality and performance will likely result. This
 *        Smooth module helps preprocess the buffer for use with such an
 *        encoder. Typical usage (no error checking):
 *
 * @code
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Dmai.h>
 *   #include <ti/sdo/dmai/Smooth.h>
 *   #include <ti/sdo/dmai/Buffer.h>
 *   #include <ti/sdo/dmai/Capture.h>
 *
 *   Capture_Attrs cAttrs = Capture_Attrs_DM6446_DM355_DEFAULT;
 *   Smooth_Attrs smAttrs = Smooth_Attrs_DEFAULT;
 *   Buffer_Attrs bAttrs = Buffer_Attrs_DEFAULT;
 *
 *   Dmai_init();
 *   Capture_Handle hCap = Capture_create(NULL, &cAttrs);
 *   hBuf = Buffer_clone(BufTab_getBuf(Capture_getBufTab(hCap), 0));
 *   Smooth_Handle hSmooth = Smooth_create(&smAttrs);
 *   Smooth_config(BufTab_getBuf(Capture_getBufTab(hCap), 0), hBuf);
 *   while (1) {
 *       Capture_get(hCap, &cBuf);
 *       Smooth_execute(cBuf, 0, hBuf, 0);
 *       // Further process the capture buffer, now smoothed in "hBuf"..
 *       Capture_put(hCap, cBuf);
 *   }
 *   Buffer_delete(hBuf);
 *   Smooth_delete(hSmooth);
 *   Capture_delete(hCap);
 * @endcode
 */

#ifndef ti_sdo_dmai_Smooth_h_
#define ti_sdo_dmai_Smooth_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Smooth */
/*@{*/

/**
 * @brief Handle through which to reference a Smooth job.
 */
typedef struct Smooth_Object *Smooth_Handle;

/**
 * @brief Attributes used to create a Smooth job.
 * @see Smooth_Attrs_DEFAULT.
 */
typedef struct Smooth_Attrs {
    /** @brief The rate of the resizer H/W to use.
      * @remarks Only applicable to DM6446 */
    Int rszRate;
} Smooth_Attrs;

/**
 * @brief Default attributes for a Smooth job.
 * @code
 *    rszRate   = 0xe
 * @endcode
 */
extern const Smooth_Attrs Smooth_Attrs_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Smooth job.
 *
 * @param[in]   attrs       #Smooth_Attrs to use for creating the Smooth job.
 *
 * @retval      Handle for use in subsequent operations (see #Smooth_Handle).
 * @retval      NULL for failure.
 */
extern Smooth_Handle Smooth_create(Smooth_Attrs *attrs);

/**
 * @brief       Configure a Smooth job.
 *
 * @param[in]   hSmooth     The #Smooth_Handle of the job to configure.
 * @param[in]   hSrcBuf     The source buffer to configure for. Note that only
 *                          the buffer properties are accessed, the pointers
 *                          are not used.
 * @param[in]   hDstBuf     The destination buffer to configure for. Note that
 *                          only the buffer properties are accessed, the
 *                          pointers are not used.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int Smooth_config(Smooth_Handle hSmooth,
                         Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf);

/**
 * @brief       Execute a Smooth job.
 *
 * @param[in]   hSmooth     The #Smooth_Handle of the job to execute.
 * @param[in]   hSrcBuf     The #Buffer_Handle of the source buffer to
 *                          copy from.
 * @param[in]   hDstBuf     The #Buffer_Handle of the destination buffer
 *                          to copy to.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int Smooth_execute(Smooth_Handle hSmooth,
                          Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf);

/**
 * @brief       Deletes a Smooth job.
 *
 * @param[in]   hSmooth     The #Smooth_Handle of the job to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int Smooth_delete(Smooth_Handle hSmooth);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Smooth_h_ */
