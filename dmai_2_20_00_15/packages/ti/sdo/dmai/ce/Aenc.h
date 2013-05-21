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
 * @defgroup   ti_sdo_dmai_Aenc      Aenc
 *
 * @brief Provides a simple interface to AUDENC (XDM 0.9) based algorithms.
 *        Typical example below (AAC, no error checking):
 *
 * @code
 *     #include <xdc/std.h>
 *     #include <ti/sdo/ce/Engine.h>
 *     #include <ti/sdo/ce/CERuntime.h>
 *     #include <ti/sdo/dmai/Dmai.h>
 *     #include <ti/sdo/dmai/Buffer.h>
 *     #include <ti/sdo/dmai/ce/Aenc.h>
 *
 *     Aenc_Handle hAe;
 *     Buffer_Handle hOutBuf;
 *     Engine_Handle hEngine;
 *     AUDENC_Params params = Aenc_Params_DEFAULT;
 *     AUDENC_DynamicParams dynParams = Aenc_DynamicParams_DEFAULT;
 *     Buffer_Attrs bAttrs = Buffer_Attrs_DEFAULT;
 *
 *     CERuntime_init();
 *     Dmai_init();
 *     hEngine = Engine_open("myengine", NULL, NULL);
 *     hAe = Aenc_create(hEngine, "aacenc", &params, &dynParams);
 *     hOutBuf = Buffer_create(Aenc_getOutBufSize(hAd), &bAttrs);
 *     hInBuf = Buffer_create(Aenc_getInBufSize(hAd), &bAttrs);
 *
 *     // Fill hInBuf with raw samples
 *     Aenc_process(hAe, hInBuf, hOutBuf);
 *     // encoded data now available in hOutBuf.
 *
 *     Buffer_delete(hOutBuf);
 *     Buffer_delete(hInBuf);
 *     Aenc_delete(hAe);
 *     Engine_close(hEngine);
 * @endcode
 */
#ifndef ti_sdo_dmai_ce_Aenc_h_
#define ti_sdo_dmai_ce_Aenc_h_

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/audio/audenc.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Aenc */
/*@{*/

/**
 * @brief       Handle through which to reference an Audio Encode algorithm.
 */
typedef struct Aenc_Object *Aenc_Handle;

/**
 * @brief       Default XDM params for an Audio Encode algorithm.
 * @code
 *     size                     = sizeof(AUDENC_Params),
 *     encodingPreset           = XDM_DEFAULT,
 *     maxSampleRate            = 48000,
 *     maxBitrate               = 288000,
 *     maxNoOfCh                = IAUDIO_STEREO,
 *     dataEndianness           = XDM_LE_16
 * @endcode
 */
extern const AUDENC_Params Aenc_Params_DEFAULT;

/**
 * @brief       Default XDM dynamic params for an Audio Encode algorithm.
 * @code
 *     size                     = sizeof(AUDENC_DynamicParams),
 *     inputFormat              = IAUDIO_INTERLEAVED,
 *     bitRate                  = 288000,
 *     sampleRate               = 48000,
 *     numChannels              = IAUDIO_STEREO,
 *     numLFEChannels           = 0,
 *     inputBitsPerSample       = 16
 * @endcode
 */
extern const AUDENC_DynamicParams Aenc_DynamicParams_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates an Audio Encode (XDM 0.9) algorithm instance.
 *
 * @param[in]   hEngine     An opened engine containing the algorithm to create.
 * @param[in]   codecName   The name of the algorithm to open. Corresponds to
 *                          the string name given in the .cfg file.
 * @param[in]   params      XDM parameters to use while creating the codec.
 * @param[in]   dynParams   XDM dynamic parameters to use while creating the
 *                          codec. 
 *
 * @retval      Handle for use in subsequent operations (see #Aenc_Handle).
 * @retval      NULL for failure.
 */
extern Aenc_Handle Aenc_create(Engine_Handle hEngine,
                               Char *codecName,
                               AUDENC_Params *params,
                               AUDENC_DynamicParams *dynParams);

/**
 * @brief       Encodes an audio buffer.
 *
 * @param[in]   hAe         The #Aenc_Handle to use for encoding.
 * @param[in]   hInBuf      The #Buffer_Handle for the buffer containing the raw
 *                          data.
 * @param[in]   hOutBuf     The #Buffer_Handle for the buffer to fill with
 *                          decoded data.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Aenc_create must be called before this function.
 */
extern Int Aenc_process(Aenc_Handle hAe, Buffer_Handle hInBuf,
                        Buffer_Handle hOutBuf);

/**
 * @brief       Deletes an Audio Encode algorithm instance.
 *
 * @param[in]   hAe         The #Aenc_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Aenc_create must be called before this function.
 */
extern Int Aenc_delete(Aenc_Handle hAe);

/**
 * @brief       Get the AUDENC handle from the Aenc module instance.
 *
 * @param[in]   hAe         The #Aenc_Handle for which to get the AUDENC handle.
 *
 * @retval      Handle to the audio encode algorithm, see the XDM documentation
 *              for AUDENC.
 *
 * @remarks     #Aenc_create must be called before this function.
 */
extern AUDENC_Handle Aenc_getVisaHandle(Aenc_Handle hAe);

/**
 * @brief       Get the input buffer size required by the codec.
 *
 * @param[in]   hAe         The #Aenc_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the input buffer required.
 *
 * @remarks     #Aenc_create must be called before this function.
 */
extern Int32 Aenc_getInBufSize(Aenc_Handle hAe);

/**
 * @brief       Get the output buffer size required by the codec.
 *
 * @param[in]   hAe         The #Aenc_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the output buffer required.
 *
 * @remarks     #Aenc_create must be called before this function.
 */
extern Int32 Aenc_getOutBufSize(Aenc_Handle hAe);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_ce_Aenc_h_ */
