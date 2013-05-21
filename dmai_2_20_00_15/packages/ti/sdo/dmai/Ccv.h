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
 * @defgroup   ti_sdo_dmai_Ccv      Ccv
 *
 * @brief This module implements color conversion from a source to a destination
 *        buffer. The color conversion can either be H/W accelerated (if
 *        supported) or performed by the CPU. Typical usage (Convert from
 *        420Psemi to 422Psemi, no error checks):
 *
 * @code
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Ccv.h>
 *   #include <ti/sdo/dmai/Dmai.h>
 *   #include <ti/sdo/dmai/Capture.h>
 *   #include <ti/sdo/dmai/BufferGfx.h>
 *
 *   Ccv_Attrs ccvAttrs = Ccv_Attrs_DEFAULT;
 *   BufferGfx_Attrs gfxAttrs = BufferGfx_Attrs_DEFAULT;
 *   Buffer_Handle hInBuf, hOutBuf;
 *   Ccv_Handle hCcv;
 *   Int32 bufSize;
 *
 *   Dmai_init();
 *   gfxAttrs = BufferGfx_Attrs_DEFAULT;
 *   gfxAttrs.colorSpace     = ColorSpace_420Psemi;
 *   gfxAttrs.dim.width      = 720;
 *   gfxAttrs.dim.height     = 480;
 *   gfxAttrs.dim.lineLength = BufferGfx_calcLineLength(gfxAttrs.dim.width,
 *                                                      ColorSpace_420Psemi);
 *   bufSize = gfxAttrs.dim.lineLength * gfxAttrs.dim.height;
 *   hInBuf = Buffer_create(bufSize, BufferGfx_getBufferAttrs(&gfxAttrs)); 
 *
 *   gfxAttrs = BufferGfx_Attrs_DEFAULT;
 *   gfxAttrs.colorSpace     = ColorSpace_422Psemi;
 *   gfxAttrs.dim.width      = 720;
 *   gfxAttrs.dim.height     = 480;
 *   gfxAttrs.dim.lineLength = BufferGfx_calcLineLength(gfxAttrs.dim.width
 *                                                      ColorSpace_422Psemi);
 *   bufSize = gfxAttrs.dim.lineLength * gfxAttrs.dim.height;
 *   hOutBuf = Buffer_create(bufSize, BufferGfx_getBufferAttrs(&gfxAttrs)); 
 *
 *   hCcv = Ccv_create(&ccvAttrs);
 *   Ccv_config(hCcv, hInBuf, hOutBuf);
 *
 *   Ccv_execute(hCcv, hInBuf, 0, hOutBuf, 0);
 *
 *   Buffer_delete(hInBuf);
 *   Buffer_delete(hOutBuf);
 *   Ccv_delete(hCcv);
 * @endcode
 */

#ifndef ti_sdo_dmai_Ccv_h_
#define ti_sdo_dmai_Ccv_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Ccv */
/*@{*/

/**
 * @brief       Different modes of Color Conversion.
 * @see         ColorSpace_Type
 */
typedef enum {
    /** @brief From 420Psemi to 422Psemi */
    Ccv_Mode_YUV420SEMI_YUV422SEMI =0,

    /** @brief From 422Psemi to 420Psemi */
    Ccv_Mode_YUV422SEMI_YUV420SEMI,

    /** @brief From 420P to RGB565 */
    Ccv_Mode_YUV420P_RGB565,

    /** @brief From 422Psemi to RGB565 */
    Ccv_Mode_YUV422PSEMI_RGB565,

    Ccv_Mode_COUNT
} Ccv_Mode;

/**
 * @brief       Attributes used to create a Color Conversion job.
 * @see         Ccv_Attrs_DEFAULT.
 */
typedef struct Ccv_Attrs {
    /** @brief TRUE if H/W acceleration is to be used */
    Int      accel;
} Ccv_Attrs;

/**
 * @brief       Default attributes for a Color Conversion job.
 * @code
 *     accel    = FALSE
 * @endcode
 */
extern const Ccv_Attrs Ccv_Attrs_DEFAULT;

/**
 * @brief       Handle through which to reference a Color Conversion job.
 */
typedef struct Ccv_Object *Ccv_Handle;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Color Conversion job.
 *
 * @param[in]   attrs       #Ccv_Attrs to use for creating the
 *                          Color Conversion job.
 *
 * @retval      #Ccv_Handle for use in subsequent operations (see #Ccv_Handle).
 * @retval      NULL for failure.
 */
extern Ccv_Handle Ccv_create(Ccv_Attrs *attrs);

/**
 * @brief       Configure a Color Conversion job.
 *
 * @param[in]   hCcv        The #Ccv_Handle of the job to configure.
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
 * @remarks     #Ccv_create must be called before this function.
 */
extern Int Ccv_config(Ccv_Handle hCcv,
                      Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf);

/**
 * @brief       Execute a Color Conversion job.
 *
 * @param[in]   hCcv        The #Ccv_Handle of the job to execute.
 * @param[in]   hSrcBuf     The source buffer to convert from.
 * @param[in]   hDstBuf     The destination buffer to convert to.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Ccv_create must be called before this function.
 * @remarks     #Ccv_config must be called before this function.
 */
extern Int Ccv_execute(Ccv_Handle hCcv,
                       Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf);

/**
 * @brief       Gets the mode of a configured color conversion job.
 *
 * @param[in]   hCcv        The #Ccv_Handle to get the mode of.
 *
 * @retval      Mode of color conversion job (see #Ccv_Mode).
 *
 * @remarks     #Ccv_create must be called before this function.
 * @remarks     #Ccv_config must be called before this function.
 */
extern Ccv_Mode Ccv_getMode(Ccv_Handle hCcv);

/**
 * @brief       Deletes a Color Conversion job.
 *
 * @param[in]   hCcv        The #Ccv_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Ccv_create must be called before this function.
 */
extern Int Ccv_delete(Ccv_Handle hCcv);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Ccv_h_ */
