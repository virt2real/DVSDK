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
 * @defgroup   ti_sdo_dmai_Sdec1      Sdec1
 *
 * @brief Provides a simple interface to SPHDEC1 (XDM 1.0) based algorithms.
 *
 *       Release Support: 
 *       G711, G726, G729 and ILBC. Due to defect in ILBC Decoder v 1.10.002, 
 *       this release will not work with this version.
 *     
 *       Typical usage:
 *
 * @code
 *     #include <xdc/std.h>
 *     #include <ti/sdo/ce/Engine.h>
 *     #include <ti/sdo/ce/CERuntime.h>
 *     #include <ti/sdo/dmai/Dmai.h>
 *     #include <ti/sdo/dmai/Buffer.h>
 *     #include <ti/sdo/dmai/Loader.h>
 *     #include <ti/sdo/dmai/ce/Sdec1.h>
 *
 *     Sdec1_Handle hSd;
 *     Loader_Handle hLoader;
 *     Buffer_Handle hOutBuf, hInBuf;
 *     Engine_Handle hEngine;
 *     SPHDEC1_Params params = Sdec1_Params_DEFAULT;
 *     SPHDEC1_DynamicParams dynParams = Sdec1_DynamicParams_DEFAULT;
 *     Loader_Attrs lAttrs = Loader_Attrs_DEFAULT;
 *     Buffer_Attrs bAttrs = Buffer_Attrs_DEFAULT;
 *
 *     CERuntime_init();
 *     Dmai_init();
 *     hEngine = Engine_open("myengine", NULL, NULL);
 *     hSd = Sdec1_create(hEngine, "mydec", &params, &dynParams);
 *     hOutBuf = Buffer_create(Sdec1_getOutBufSize(hSd), &bAttrs);
 *     lAttrs.readSize = Sdec1_getInBufSize(hSd);
 *     lAttrs.readBufSize = lAttrs.readSize * 2;
 *     hLoader = Loader_create("myfile", &lAttrs);
 *     Loader_prime(hLoader, &hInBuf);
 *
 *     while (1) {
 *         Sdec1_process(hSd, hInBuf, hOutBuf);
 *         // Raw decoded samples now available in hOutBuf.
 *         Loader_getFrame(hLoader, hInBuf);
 *         if (Buffer_getUserPtr(hInBuf) == NULL) break;
 *     }
 *     Loader_delete(hLoader);
 *     Buffer_delete(hOutBuf);
 *     Sdec1_delete(hSd);
 *     Engine_close(hEngine);
 * @endcode
 */

#ifndef ti_sdo_dmai_ce_Sdec1_h_
#define ti_sdo_dmai_ce_Sdec1_h_

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/speech1/sphdec1.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Sdec1 */
/*@{*/

/**
 * @brief       Handle through which to reference a Speech Decode algorithm.
 */
typedef struct Sdec1_Object *Sdec1_Handle;

/**
 * @brief       Default XDM parameters for a Speech Decode algorithm.
 * @code
 *     size                 = sizeof(SPHDEC1_Params),
 *     compandingLaw        = ISPEECH1_PCM_COMPAND_ALAW,
 *     packingType          = 0,
 *     codecSelection       = 0,
 *     bitRate              = 0,
 *     reserved             = 0,
 *     **tablesPtr          = NULL,
 * @endcode
 */
extern const SPHDEC1_Params Sdec1_Params_DEFAULT;

/**
 * @brief       Default XDM dynamic parameters for a Speech Decode algorithm.
 * @code
 *     size                 = sizeof(SPHDEC1_DynamicParams),
 *     postFilter           = 0
 * @endcode
 */
extern const SPHDEC1_DynamicParams Sdec1_DynamicParams_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Speech Decode (XDM 1.0) algorithm instance.
 *
 * @param[in]   hEngine     An opened engine containing the algorithm to create.
 * @param[in]   codecName   The name of the algorithm to open. Corresponds to
 *                          the string name given in the .cfg file.
 * @param[in]   params      XDM parameters to use while creating the codec.
 * @param[in]   dynParams   XDM dynamic parameters to use while creating the
 *                          codec. 
 *
 * @retval      Handle for use in subsequent operations (see #Sdec1_Handle).
 * @retval      NULL for failure.
 */
extern Sdec1_Handle Sdec1_create(Engine_Handle hEngine,
                               Char *codecName,
                               SPHDEC1_Params *params,
                               SPHDEC1_DynamicParams *dynParams);

/**
 * @brief       Decodes a Speech buffer.
 *
 * @param[in]   hSd         The #Sdec1_Handle to use for decoding.
 * @param[in]   hInBuf      The #Buffer_Handle for the buffer containing the
 *                          encoded data.
 * @param[in]   hOutBuf     The #Buffer_Handle for the buffer to fill with
 *                          decoded data.
 *
 * @retval      DMAI_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Sdec1_create must be called before this function.
 */
extern Int Sdec1_process(Sdec1_Handle hSd, Buffer_Handle hInBuf,
                        Buffer_Handle hOutBuf);

/**
 * @brief       Deletes a Speech Decode algorithm instance.
 *
 * @param[in]   hSd         The #Sdec1_Handle to delete.
 *
 * @retval      DMAI_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Sdec1_create must be called before this function.
 */
extern Int Sdec1_delete(Sdec1_Handle hSd);

/**
 * @brief       Get the SPHDEC1 handle from the Sdec1 module instance.
 *
 * @param[in]   hSd         The #Sdec1_Handle for which to get the
 *                          SPHDEC1 handle.
 *
 * @retval      Handle to the speech1 decode algorithm, see the XDM
 *              documentation for SPHDEC1.
 *
 * @remarks     #Sdec1_create must be called before this function.
 */
extern SPHDEC1_Handle Sdec1_getVisaHandle(Sdec1_Handle hSd);

/**
 * @brief       Get the input buffer size required by the codec.
 *
 * @param[in]   hSd         The #Sdec1_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the input buffer required.
 *
 * @remarks     #Sdec1_create must be called before this function.
 */
extern Int32 Sdec1_getInBufSize(Sdec1_Handle hSd);

/**
 * @brief       Get the output buffer size required by the codec.
 *
 * @param[in]   hSd         The #Sdec1_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the output buffer required.
 *
 * @remarks     #Sdec1_create must be called before this function.
 */
extern Int32 Sdec1_getOutBufSize(Sdec1_Handle hSd);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_ce_Sdec1_h_ */
