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
 * @defgroup   ti_sdo_dmai_Ienc    Ienc
 *
 * @brief Provides a simple interface to IMGENC (XDM 0.9) based algorithms.
 *        
 */
#ifndef ti_sdo_dmai_ce_Ienc_h_
#define ti_sdo_dmai_ce_Ienc_h_

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/image/imgenc.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Ienc */
/*@{*/

/**
 * @brief       Handle through which to reference an Image Encode algorithm.
 */
typedef struct Ienc_Object *Ienc_Handle;

/**
 * @brief       Default XDM parameters for an Image Encode algorithm.
 * @code
 *     size                     = sizeof (IMGENC_Params),
 *     maxHeight                = 0,
 *     maxWidth                 = 0,
 *     maxScans                 = XDM_DEFAULT, 
 *     dataEndianness           = XDM_LE_32,
 *     forceChromaFormat        = XDM_YUV_422P
 * @endcode
 */
extern const IMGENC_Params Ienc_Params_DEFAULT;

/**
 * @brief       Default XDM dynamic parameters for an Image Encode algorithm. 
 * @code
 *  size                        = sizeof(IMGENC_DynamicParams),
 *  numAU                       = XDM_DEFAULT,
 *  inputChromaFormat           = XDM_YUV_422ILE,
 *  inputHeight                 = 0, 
 *  inputWidth                  = 0,
 *  captureWidth                = 0,
 *  generateHeader              = XDM_ENCODE_AU,
 *  qValue                            = 75
 * @endcode
 */
extern const IMGENC_DynamicParams Ienc_DynamicParams_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates an Image Encode (XDM 0.9) algorithm instance.
 *
 * @param[in]   hEngine     An opened engine containing the algorithm to create.
 * @param[in]   codecName   The name of the algorithm to open. Corresponds to
 *                          the string name given in the .cfg file.
 * @param[in]   params      XDM parameters to use while creating the codec.
 * @param[in]   dynParams   XDM dynamic parameters to use while creating the
 *                          codec. 
 *
 * @retval      Handle for use in subsequent operations (see #Ienc_Handle).
 * @retval      NULL for failure.
 */
extern Ienc_Handle Ienc_create(Engine_Handle hEngine,
                               Char *codecName,
                               IMGENC_Params *params,
                               IMGENC_DynamicParams *dynParams);

/**
 * @brief       Encodes an image buffer.
 *
 * @param[in]   hIe         The #Ienc_Handle to use for encoding.
 * @param[in]   hInBuf      The #Buffer_Handle for the buffer containing the raw
 *                          data.
 * @param[in]   hOutBuf     The #Buffer_Handle for the buffer to fill with
 *                          encoded data.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Ienc_create must be called before this function.
 */
extern Int Ienc_process(Ienc_Handle hIe, Buffer_Handle hInBuf,
                        Buffer_Handle hOutBuf);

/**
 * @brief       Deletes an Image Encode algorithm instance.
 *
 * @param[in]   hIe         The #Ienc_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Ienc_create must be called before this function.
 */
extern Int Ienc_delete(Ienc_Handle hIe);

/**
 * @brief       Get the IMGENC handle from the Ienc module instance.
 *
 * @param[in]   hIe         The #Ienc_Handle for which to get the IMGENC handle.
 *
 * @retval      Handle to the image encode algorithm, see the XDM documentation
 *              for IMGENC.
 *
 * @remarks     #Ienc_create must be called before this function.
 */
extern IMGENC_Handle Ienc_getVisaHandle(Ienc_Handle hIe);

/**
 * @brief       Get the input buffer size required by the codec.
 *
 * @param[in]   hIe         The #Ienc_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the input buffer required.
 *
 * @remarks     #Ienc_create must be called before this function.
 */
extern Int32 Ienc_getInBufSize(Ienc_Handle hIe);

/**
 * @brief       Get the output buffer size required by the codec.
 *
 * @param[in]   hIe         The #Ienc_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the output buffer required.
 *
 * @remarks     #Ienc_create must be called before this function.
 */
extern Int32 Ienc_getOutBufSize(Ienc_Handle hIe);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_ce_Ienc_h_ */
