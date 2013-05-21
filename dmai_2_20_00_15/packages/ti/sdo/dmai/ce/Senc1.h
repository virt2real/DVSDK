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
 * @defgroup   ti_sdo_dmai_Senc1      Senc1
 *
 * @brief Provides a simple interface to SPHENC1 (XDM 1.0) based algorithms.
 *
 *       Release Support: 
 *       G711, G726, G729 and ILBC. Due to defects in G711 Encoder v 1.11.001
 *       and ILBC Encoder v 1.10.002, this release will not work with these
 *       versions.
 *     
 *       Typical usage:
 *
 * @code
 *     #include <xdc/std.h>
 *     #include <ti/sdo/ce/Engine.h>
 *     #include <ti/sdo/ce/CERuntime.h>
 *     #include <ti/sdo/dmai/Dmai.h>
 *     #include <ti/sdo/dmai/Buffer.h>
 *     #include <ti/sdo/dmai/ce/Senc1.h>
 *
 *     Senc1_Handle hSe1;
 *     Buffer_Handle hOutBuf;
 *     Buffer_Handle hInBuf;
 *     Engine_Handle hEngine;
 *     SPHENC1_Params params = Senc1_Params_DEFAULT;
 *     SPHENC1_DynamicParams dynParams = Senc1_DynamicParams_DEFAULT;
 *     Buffer_Attrs bAttrs = Buffer_Attrs_DEFAULT;
 *
 *     CERuntime_init();
 *     Dmai_init();
 *     hEngine = Engine_open("myengine", NULL, NULL);
 *     hSe1 = Senc1_create(hEngine, "mycodec", &params, &dynParams);
 *     hOutBuf = Buffer_create(Senc1_getOutBufSize(hSe), &bAttrs);
 *     hInBuf = Buffer_create(Senc1_getInBufSize(hSe), &bAttrs);
 *
 *     // Fill hInBuf with raw samples
 *     Senc1_process(hSe1, hInBuf, hOutBuf);
 *     // encoded data now available in hOutBuf.
 *
 *     Buffer_delete(hOutBuf);
 *     Buffer_delete(hInBuf);
 *     Senc1_delete(hSe);
 *     Engine_close(hEngine);
 *
 * @endcode
 */

#ifndef ti_sdo_dmai_ce_Senc1_h_
#define ti_sdo_dmai_ce_Senc1_h_

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/speech1/sphenc1.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Senc1 */
/*@{*/

/**
 * @brief       Handle through which to reference a Speech Encode algorithm.
 */
typedef struct Senc1_Object *Senc1_Handle;

/**
 * @brief       Default XDM parameters for a Speech Encode algorithm.
 * @code
 *     size                 = sizeof(SPHENC1_Params),
 *     frameSize            = 160,
 *     compandingLaw        = 1,
 *     packingType          = 0,
 *     vadSelection         = 0,
 *     codecSelection       = 0,
 *     bitRate              = 0,
 *     reserved             = 0,
 *     **tablesPtr          = NULL,
 * @endcode
 */
extern const SPHENC1_Params Senc1_Params_DEFAULT;

/**
 * @brief       Default XDM dynamic parameters for a Speech Decode algorithm.
 * @code
 *     size                 = sizeof(SPHENC1_DynamicParams),
 *     frameSize            = 0,
 *     bitRate              = 0,
 *     mode                 = 0,
 *     vadFlag              = ISPEECH1_VADFLAG_DEFAULT,
 *     noiseSuppressionMode = 0,
 *     ttyTddMode           = 0,
 *     dtmfMode             = 0,
 *     dataTransmit         = 0,
 *     reserved             = 0,
 * @endcode
 */
extern const SPHENC1_DynamicParams Senc1_DynamicParams_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Speech Encode (XDM 1.0) algorithm instance.
 *
 * @param[in]   hEngine     An opened engine containing the algorithm to create.
 * @param[in]   codecName   The name of the algorithm to open. Corresponds to
 *                          the string name given in the .cfg file.
 * @param[in]   params      XDM parameters to use while creating the codec.
 * @param[in]   dynParams   XDM dynamic parameters to use while creating the
 *                          codec. 
 *
 * @retval      Handle for use in subsequent operations (see #Senc1_Handle).
 * @retval      NULL for failure.
 */
extern Senc1_Handle Senc1_create(Engine_Handle hEngine,
                                 Char *codecName,
                                 SPHENC1_Params *params,
                                 SPHENC1_DynamicParams *dynParams);

/**
 * @brief       Encodes a Speech buffer.
 *
 * @param[in]   hSe1        The #Senc1_Handle to use for decoding.
 * @param[in]   hInBuf      The #Buffer_Handle for the buffer containing the
 *                          raw data.
 * @param[in]   hOutBuf     The #Buffer_Handle for the buffer to fill with
 *                          encoded data.
 *
 * @retval      DMAI_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Senc1_create must be called before this function.
 */
extern Int Senc1_process(Senc1_Handle hSe1, Buffer_Handle hInBuf,
                         Buffer_Handle hOutBuf);

/**
 * @brief       Deletes a Speech Encode algorithm instance.
 *
 * @param[in]   hSe1        The #Senc1_Handle to delete.
 *
 * @retval      DMAI_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Senc1_create must be called before this function.
 */
extern Int Senc1_delete(Senc1_Handle hSe1);

/**
 * @brief       Get the SPHENC1 handle from the Senc1 module instance.
 *
 * @param[in]   hSe1        The #Senc1_Handle for which to get the
 *                          SPHENC1 handle.
 *
 * @retval      Handle to the speech1 encode algorithm, see the XDM
 *              documentation for SPHENC1.
 *
 * @remarks     #Senc1_create must be called before this function.
 */
extern SPHENC1_Handle Senc1_getVisaHandle(Senc1_Handle hSe1);

/**
 * @brief       Get the input buffer size required by the codec.
 *
 * @param[in]   hSe1        The #Senc1_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the input buffer required.
 *
 * @remarks     #Senc1_create must be called before this function.
 */
extern Int32 Senc1_getInBufSize(Senc1_Handle hSe1);

/**
 * @brief       Get the output buffer size required by the codec.
 *
 * @param[in]   hSe1        The #Senc1_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the output buffer required.
 *
 * @remarks     #Senc1_create must be called before this function.
 */
extern Int32 Senc1_getOutBufSize(Senc1_Handle hSe1);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_ce_Senc1_h_ */
