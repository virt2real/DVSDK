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
 * @defgroup   ti_sdo_dmai_Senc      Senc
 *
 * @brief Provides a simple interface to SPHENC (XDM 0.9) based algorithms.
 *        Currently only works for TI:s G711 encoder due to assumptions made.
 *        Typical example below (G.711, no error checking):
 *
 * @code
 *     #include <xdc/std.h>
 *     #include <ti/sdo/ce/Engine.h>
 *     #include <ti/sdo/ce/CERuntime.h>
 *     #include <ti/sdo/dmai/Dmai.h>
 *     #include <ti/sdo/dmai/Buffer.h>
 *     #include <ti/sdo/dmai/ce/Senc.h>
 *
 *     Senc_Handle hSe;
 *     Buffer_Handle hOutBuf;
 *     Engine_Handle hEngine;
 *     SPHENC_Params params = Senc_Params_DEFAULT;
 *     SPHENC_DynamicParams dynParams = Senc_DynamicParams_DEFAULT;
 *     Buffer_Attrs bAttrs = Buffer_Attrs_DEFAULT;
 *
 *     CERuntime_init();
 *     Dmai_init();
 *     hEngine = Engine_open("myengine", NULL, NULL);
 *     hSe = Senc_create(hEngine, "aacenc", &params, &dynParams);
 *     hOutBuf = Buffer_create(Senc_getOutBufSize(hSe), &bAttrs);
 *     hInBuf = Buffer_create(Senc_getInBufSize(hSe), &bAttrs);
 *
 *     // Fill hInBuf with raw samples
 *     Senc_process(hSe, hInBuf, hOutBuf);
 *     // encoded data now available in hOutBuf.
 *
 *     Buffer_delete(hOutBuf);
 *     Buffer_delete(hInBuf);
 *     Senc_delete(hSe);
 *     Engine_close(hEngine);
 * @endcode
 */

#ifndef ti_sdo_dmai_ce_Senc_h_
#define ti_sdo_dmai_ce_Senc_h_

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/speech/sphenc.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Senc */
/*@{*/

/**
 * @brief       Handle through which to reference a Speech Encode algorithm.
 */
typedef struct Senc_Object *Senc_Handle;

/**
 * @brief       Default XDM parameters for a Speech Encode algorithm.
 * @code
 *     size                     = sizeof(SPHENC_Params),
 *     frameSize                = 80,
 *     compandingLaw            = ISPEECH_ALAW,
 *     packingType              = 0,
 *     vadSelection             = 0
 * @endcode
 */
extern const SPHENC_Params Senc_Params_DEFAULT;

/**
 * @brief       Default XDM dynamic parameters for a Speech Encode algorithm.
 * @code
 *     size                     = sizeof(ISPHENC_DynamicParams),
 *     frameSize                = 80,
 *     bitRate                  = 0,
 *     mode                     = 0,
 *     vadFlag                  = 0,
 *     noiseSuppressionMode     = 0,
 *     ttyTddMode               = 0,
 *     dtmfMode                 = 0,
 *     dataTransmit             = 1,
 *     homingMode               = 0
 * @endcode
 */
extern const SPHENC_DynamicParams Senc_DynamicParams_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Speech Encode (XDM 0.9) algorithm instance.
 *
 * @param[in]   hEngine     An opened engine containing the algorithm to create.
 * @param[in]   codecName   The name of the algorithm to open. Corresponds to
 *                          the string name given in the .cfg file.
 * @param[in]   params      XDM parameters to use while creating the codec.
 * @param[in]   dynParams   XDM dynamic parameters to use while creating the
 *                          codec. 
 *
 * @retval      Handle for use in subsequent operations (see #Senc_Handle).
 * @retval      NULL for failure.
 */
extern Senc_Handle Senc_create(Engine_Handle hEngine,
                               Char *codecName,
                               SPHENC_Params *params,
                               SPHENC_DynamicParams *dynParams);

/**
 * @brief       Encodes a speech buffer.
 *
 * @param[in]   hSe         The #Senc_Handle to use for encoding.
 * @param[in]   hInBuf      The #Buffer_Handle for the buffer containing the raw
 *                          data.
 * @param[in]   hOutBuf     The #Buffer_Handle for the buffer to fill with
 *                          encoded data.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Senc_create must be called before this function.
 */
extern Int Senc_process(Senc_Handle hSe, Buffer_Handle hInBuf,
                        Buffer_Handle hOutBuf);

/**
 * @brief       Deletes a Speech Encode algorithm instance.
 *
 * @param[in]   hSe         The #Senc_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Senc_create must be called before this function.
 */
extern Int Senc_delete(Senc_Handle hSe);

/**
 * @brief       Get the SPHENC handle from the Senc module instance.
 *
 * @param[in]   hSe         The #Senc_Handle for which to get the SPHENC handle.
 *
 * @retval      Handle to the speech encode algorithm, see the XDM documentation
 *              for SPHENC.
 *
 * @remarks     #Senc_create must be called before this function.
 */
extern SPHENC_Handle Senc_getVisaHandle(Senc_Handle hSe);

/**
 * @brief       Get the input buffer size required by the codec.
 *
 * @param[in]   hSe         The #Senc_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the input buffer required.
 *
 * @remarks     #Senc_create must be called before this function.
 */
extern Int32 Senc_getInBufSize(Senc_Handle hSe);

/**
 * @brief       Get the output buffer size required by the codec.
 *
 * @param[in]   hSe         The #Senc_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the output buffer required.
 *
 * @remarks     #Senc_create must be called before this function.
 */
extern Int32 Senc_getOutBufSize(Senc_Handle hSe);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_ce_Senc_h_ */
