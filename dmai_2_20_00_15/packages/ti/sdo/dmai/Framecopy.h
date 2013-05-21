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
 * @defgroup   ti_sdo_dmai_Framecopy    Framecopy
 *
 * @brief Copies a frame buffer from source to destination, either
 *        accelerated (resizer on DM6446 or DMA) or using the CPU. Typical
 *        usage (no error checking):
 *
 * @code
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Dmai.h>
 *   #include <ti/sdo/dmai/Capture.h>
 *   #include <ti/sdo/dmai/Display.h>
 *   #include <ti/sdo/dmai/Framecopy.h>
 *
 *   Capture_Attrs cAttrs = Capture_Attrs_DM6467_DEFAULT;
 *   Display_Attrs dAttrs = Display_Attrs_DM6467_VID_DEFAULT;
 *   Framecopy_Attrs fcAttrs = Framecopy_Attrs_DEFAULT;
 *
 *   Dmai_init();
 *   Capture_Handle hCap = Capture_create(NULL, &cAttrs);
 *   dAttrs.videoStd = Capture_getVideoStd(hCap);
 *   Display_Handle hDis = Display_create(NULL, &dAttrs);
 *   Framecopy_Handle hFc = Framecopy_create(&fcAttrs);
 *   Framecopy_config(BufTab_getBuf(Capture_getBufTab(hCap), 0),
 *                    BufTab_getBuf(Display_getBufTab(hDis), 0));
 *
 *   while (1) {
 *       Capture_get(hCap, &cBuf);
 *       Display_get(hDis, &dBuf);
 *       Framecopy_execute(hFc, cBuf, 0, hBuf, 0);
 *       Capture_put(hCap, cBuf);
 *       Display_put(hDis, dBuf);
 *   }
 *
 *   Framecopy_delete(hFc);
 *   Capture_delete(hCap);
 *   Display_delete(hDis);
 * @endcode
 */

#ifndef ti_sdo_dmai_Framecopy_h_
#define ti_sdo_dmai_Framecopy_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Framecopy */
/*@{*/

/**
 * @brief       Attributes used to create a Framecopy job.
 * @see         Framecopy_Attrs_DEFAULT.
 */
typedef struct Framecopy_Attrs {
    /** @brief TRUE if H/W acceleration is to be used */
    Int accel;

    /** @brief The rate of the resizer H/W to use.
      * @remarks Only applicable on DM6446 and OMAP3530 Linux */
    Int rszRate;

    /** @brief Use SDMA for framecopy acceleration
      * @remarks Only applicable on OMAP3530/DM3730 Linux */
    Int sdma;
} Framecopy_Attrs;

/**
 * @brief       Default attributes for a Framecopy job.
 * @code
 *     accel    = FALSE,
 *     rszRate  = 0xe,
 *     sdma     = FALSE
 * @endcode
 */
extern const Framecopy_Attrs Framecopy_Attrs_DEFAULT;

/**
 * @brief       Handle through which to reference a Framecopy job.
 */
typedef struct Framecopy_Object *Framecopy_Handle;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Framecopy job.
 *
 * @param[in]   attrs       #Framecopy_Attrs to use for creating the
 *                          Framecopy job.
 *
 * @retval      Handle for use in subsequent operations (see #Framecopy_Handle).
 * @retval      NULL for failure.
 */
extern Framecopy_Handle Framecopy_create(Framecopy_Attrs *attrs);

/**
 * @brief       Configure a Framecopy job.
 *
 * @param[in]   hFramecopy  The #Framecopy_Handle of the job to configure.
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
 * @remarks     #Framecopy_create must be called before this function.
 */
extern Int Framecopy_config(Framecopy_Handle hFramecopy,
                            Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf);

/**
 * @brief       Execute a Framecopy job.
 *
 * @param[in]   hFramecopy  The #Framecopy_Handle of the job to execute.
 * @param[in]   hSrcBuf     The #Buffer_Handle of the source buffer to
 *                          copy from.
 * @param[in]   hDstBuf     The #Buffer_Handle of the destination buffer
 *                          to copy to.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Framecopy_create must be called before this function.
 * @remarks     #Framecopy_config must be called before this function.
 */
extern Int Framecopy_execute(Framecopy_Handle hFramecopy,
                             Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf);

/**
 * @brief       Deletes a Framecopy job.
 *
 * @param[in]   hFramecopy  The #Framecopy_Handle of the job to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Framecopy_create must be called before this function.
 */
extern Int Framecopy_delete(Framecopy_Handle hFramecopy);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Framecopy_h_ */
