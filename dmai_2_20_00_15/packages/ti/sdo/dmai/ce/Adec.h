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
 * @defgroup   ti_sdo_dmai_Adec      Adec
 *
 * @brief Provides a simple interface to AUDDEC (XDM 0.9) based algorithms.
 *        Typical usage (AAC, no error checking):
 *
 * @code
 *     #include <xdc/std.h>
 *     #include <ti/sdo/ce/Engine.h>
 *     #include <ti/sdo/ce/CERuntime.h>
 *     #include <ti/sdo/dmai/Dmai.h>
 *     #include <ti/sdo/dmai/Buffer.h>
 *     #include <ti/sdo/dmai/Loader.h>
 *     #include <ti/sdo/dmai/ce/Adec.h>
 *
 *     Adec_Handle hAd;
 *     Loader_Handle hLoader;
 *     Buffer_Handle hOutBuf;
 *     Engine_Handle hEngine;
 *     AUDDEC_Params params = Adec_Params_DEFAULT;
 *     AUDDEC_DynamicParams dynParams = Adec_DynamicParams_DEFAULT;
 *     Loader_Attrs lAttrs = Loader_Attrs_DEFAULT;
 *     Buffer_Attrs bAttrs = Buffer_Attrs_DEFAULT;
 *
 *     CERuntime_init();
 *     Dmai_init();
 *     hEngine = Engine_open("myengine", NULL, NULL);
 *     hAd = Adec_create(hEngine, "aacdec", &params, &dynParams);
 *     hOutBuf = Buffer_create(Adec_getOutBufSize(hAd), &bAttrs);
 *     lAttrs.readSize = Adec_getInBufSize(hAd);
 *     lAttrs.readBufSize = lAttrs.readSize * 2;
 *     hLoader = Loader_create("myfile.aac", &lAttrs);
 *     Loader_prime(hLoader, &hInBuf);
 *
 *     while (1) {
 *         Adec_process(hAd, hInBuf, hOutBuf);
 *         // Raw decoded samples now available in hOutBuf.
 *         Loader_getFrame(hLoader, hInBuf);
 *         if (Buffer_getUserPtr(hInBuf) == NULL) break;
 *     }
 *     Loader_delete(hLoader);
 *     Buffer_delete(hOutBuf);
 *     Adec_delete(hAd);
 *     Engine_close(hEngine);
 * @endcode
 */

#ifndef ti_sdo_dmai_ce_Adec_h_
#define ti_sdo_dmai_ce_Adec_h_

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/audio/auddec.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Adec */
/*@{*/

/**
 * @brief       Handle through which to reference an Audio Decode algorithm.
 */
typedef struct Adec_Object *Adec_Handle;

/**
 * @brief       Default XDM parameters for an Audio Decode algorithm.
 * @code
 *     size                 = sizeof(AUDDEC_Params),
 *     maxSampleRate        = 48000,
 *     maxBitrate           = 448000,
 *     maxNoOfCh            = IAUDIO_STEREO,
 *     dataEndianness       = XDM_BYTE,
 * @endcode
 */
extern const AUDDEC_Params Adec_Params_DEFAULT;

/**
 * @brief       Default XDM dynamic parameters for an Audio Decode algorithm.
 * @code
 *     size                 = sizeof(AUDDEC_DynamicParams),
 *     outputFormat         = IAUDIO_INTERLEAVED,
 * @endcode
 */
extern const AUDDEC_DynamicParams Adec_DynamicParams_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates an Audio Decode (XDM 0.9) algorithm instance.
 *
 * @param[in]   hEngine     An opened engine containing the algorithm to create.
 * @param[in]   codecName   The name of the algorithm to open. Corresponds to
 *                          the string name given in the .cfg file.
 * @param[in]   params      XDM parameters to use while creating the codec.
 * @param[in]   dynParams   XDM dynamic parameters to use while creating the
 *                          codec. 
 *
 * @retval      Handle for use in subsequent operations (see #Adec_Handle).
 * @retval      NULL for failure.
 */
extern Adec_Handle Adec_create(Engine_Handle hEngine,
                               Char *codecName,
                               AUDDEC_Params *params,
                               AUDDEC_DynamicParams *dynParams);

/**
 * @brief       Decodes an audio buffer.
 *
 * @param[in]   hAd         The #Adec_Handle to use for decoding.
 * @param[in]   hInBuf      The #Buffer_Handle for the buffer containing the
 *                          encoded data.
 * @param[in]   hOutBuf     The #Buffer_Handle for the buffer to fill with
 *                          decoded data.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Adec_create must be called before this function.
 */
extern Int Adec_process(Adec_Handle hAd, Buffer_Handle hInBuf,
                        Buffer_Handle hOutBuf);

/**
 * @brief       Deletes an Audio Decode algorithm instance.
 *
 * @param[in]   hAd         The #Adec_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Adec_create must be called before this function.
 */
extern Int Adec_delete(Adec_Handle hAd);

/**
 * @brief       Get the AUDDEC handle from the Adec module instance.
 *
 * @param[in]   hAd         The #Adec_Handle for which to get the AUDDEC handle.
 *
 * @retval      Handle to the audio decode algorithm, see the XDM documentation
 *              for AUDDEC.
 *
 * @remarks     #Adec_create must be called before this function.
 */
extern AUDDEC_Handle Adec_getVisaHandle(Adec_Handle hAd);

/**
 * @brief       Get the sample rate detected by the algorithm.
 *
 * @param[in]   hAd         The #Adec_Handle for which to get the sample rate.
 *
 * @retval      "Sample rate" detected in encoded stream.
 *
 * @remarks     #Adec_create must be called before this function.
 * @remarks     #Adec_process must be called before this function.
 */
extern Int Adec_getSampleRate(Adec_Handle hAd);

/**
 * @brief       Get the input buffer size required by the codec.
 *
 * @param[in]   hAd         The #Adec_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the input buffer required.
 *
 * @remarks     #Adec_create must be called before this function.
 */
extern Int32 Adec_getInBufSize(Adec_Handle hAd);

/**
 * @brief       Get the output buffer size required by the codec.
 *
 * @param[in]   hAd         The #Adec_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the output buffer required.
 *
 * @remarks     #Adec_create must be called before this function.
 */
extern Int32 Adec_getOutBufSize(Adec_Handle hAd);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_ce_Adec_h_ */
