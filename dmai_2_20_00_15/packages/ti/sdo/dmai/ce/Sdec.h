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
 * @defgroup   ti_sdo_dmai_Sdec      Sdec
 *
 * @brief Provides a simple interface to SPHDEC (XDM 0.9) based algorithms.
 *        Currently only works for TI:s G711 decoder due to assumptions made.
 *        Typical usage (G.711, no error checking):
 *
 * @code
 *     #include <xdc/std.h>
 *     #include <ti/sdo/ce/Engine.h>
 *     #include <ti/sdo/ce/CERuntime.h>
 *     #include <ti/sdo/dmai/Dmai.h>
 *     #include <ti/sdo/dmai/Buffer.h>
 *     #include <ti/sdo/dmai/Loader.h>
 *     #include <ti/sdo/dmai/ce/Sdec.h>
 *
 *     Sdec_Handle hSd;
 *     Loader_Handle hLoader;
 *     Buffer_Handle hOutBuf;
 *     Engine_Handle hEngine;
 *     SPHDEC_Params params = Sdec_Params_DEFAULT;
 *     SPHDEC_DynamicParams dynParams = Sdec_DynamicParams_DEFAULT;
 *     Loader_Attrs lAttrs = Loader_Attrs_DEFAULT;
 *     Buffer_Attrs bAttrs = Buffer_Attrs_DEFAULT;
 *
 *     CERuntime_init();
 *     Dmai_init();
 *     hEngine = Engine_open("myengine", NULL, NULL);
 *     hSd = Sdec_create(hEngine, "g711dec", &params, &dynParams);
 *     hOutBuf = Buffer_create(Sdec_getOutBufSize(hSd), &bAttrs);
 *     lAttrs.readSize = Sdec_getInBufSize(hSd);
 *     lAttrs.readBufSize = lAttrs.readSize * 2;
 *     hLoader = Loader_create("myfile.g711", &lAttrs);
 *     Loader_prime(hLoader, &hInBuf);
 *
 *     while (1) {
 *         Sdec_process(hSd, hInBuf, hOutBuf);
 *         // Raw decoded samples now available in hOutBuf.
 *         Loader_getFrame(hLoader, hInBuf);
 *         if (Buffer_getUserPtr(hInBuf) == NULL) break;
 *     }
 *     Loader_delete(hLoader);
 *     Buffer_delete(hOutBuf);
 *     Sdec_delete(hSd);
 *     Engine_close(hEngine);
 * @endcode
 */

#ifndef ti_sdo_dmai_ce_Sdec_h_
#define ti_sdo_dmai_ce_Sdec_h_

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/speech/sphdec.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Sdec */
/*@{*/

/**
 * @brief       Handle through which to reference a Speech Decode algorithm.
 */
typedef struct Sdec_Object *Sdec_Handle;

/**
 * @brief       Default XDM parameters for a Speech Decode algorithm.
 * @code
 *     size                 = sizeof(SPHDEC_Params),
 *     dataEnable           = 0,
 *     compandingLaw        = ISPEECH_ALAW,
 *     packingType          = 0
 * @endcode
 */
extern const SPHDEC_Params Sdec_Params_DEFAULT;

/**
 * @brief       Default XDM dynamic parameters for a Speech Decode algorithm.
 * @code
 *     size                 = sizeof(SPHDEC_DynamicParams),
 *     postFilter           = 0
 * @endcode
 */
extern const SPHDEC_DynamicParams Sdec_DynamicParams_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Speech Decode (XDM 0.9) algorithm instance.
 *
 * @param[in]   hEngine     An opened engine containing the algorithm to create.
 * @param[in]   codecName   The name of the algorithm to open. Corresponds to
 *                          the string name given in the .cfg file.
 * @param[in]   params      XDM parameters to use while creating the codec.
 * @param[in]   dynParams   XDM dynamic parameters to use while creating the
 *                          codec. 
 *
 * @retval      Handle for use in subsequent operations (see #Sdec_Handle).
 * @retval      NULL for failure.
 */
extern Sdec_Handle Sdec_create(Engine_Handle hEngine,
                               Char *codecName,
                               SPHDEC_Params *params,
                               SPHDEC_DynamicParams *dynParams);

/**
 * @brief       Decodes a Speech buffer.
 *
 * @param[in]   hSd         The #Sdec_Handle to use for decoding.
 * @param[in]   hInBuf      The #Buffer_Handle for the buffer containing the
 *                          encoded data.
 * @param[in]   hOutBuf     The #Buffer_Handle for the buffer to fill with
 *                          decoded data.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Sdec_create must be called before this function.
 */
extern Int Sdec_process(Sdec_Handle hSd, Buffer_Handle hInBuf,
                        Buffer_Handle hOutBuf);

/**
 * @brief       Deletes a Speech Decode algorithm instance.
 *
 * @param[in]   hSd         The #Sdec_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Sdec_create must be called before this function.
 */
extern Int Sdec_delete(Sdec_Handle hSd);

/**
 * @brief       Get the SPHDEC handle from the Sdec module instance.
 *
 * @param[in]   hSd         The #Sdec_Handle for which to get the SPHDEC handle.
 *
 * @retval      Handle to the speech decode algorithm, see the XDM documentation
 *              for SPHDEC.
 *
 * @remarks     #Sdec_create must be called before this function.
 */
extern SPHDEC_Handle Sdec_getVisaHandle(Sdec_Handle hSd);

/**
 * @brief       Get the input buffer size required by the codec.
 *
 * @param[in]   hSd         The #Sdec_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the input buffer required.
 *
 * @remarks     #Sdec_create must be called before this function.
 */
extern Int32 Sdec_getInBufSize(Sdec_Handle hSd);

/**
 * @brief       Get the output buffer size required by the codec.
 *
 * @param[in]   hSd         The #Sdec_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the output buffer required.
 *
 * @remarks     #Sdec_create must be called before this function.
 */
extern Int32 Sdec_getOutBufSize(Sdec_Handle hSd);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_ce_Sdec_h_ */
