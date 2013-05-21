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
 * @defgroup   ti_sdo_dmai_Venc    Venc
 *
 * @brief Provides a simple interface to VIDENC (XDM 0.9) based algorithms.
 *        For typical usage see the video_encode_io app.
 *
 */

#ifndef ti_sdo_dmai_ce_Venc_h_
#define ti_sdo_dmai_ce_Venc_h_

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/video/videnc.h>

#include <ti/sdo/dmai/Dmai.h>

/** @ingroup    ti_sdo_dmai_Venc */
/*@{*/

/**
 * @brief       Handle through which to reference a Video Encode algorithm.
 */
typedef struct Venc_Object *Venc_Handle;

/**
 * @brief       Default XDM parameters for a Video Encode algorithm.
 * @code
 *     size                     = sizeof(VIDENC_Params),
 *     encodingPreset           = XDM_DEFAULT,
 *     rateControlPreset        = IVIDEO_NONE,
 *     maxHeight                = 576,
 *     maxWidth                 = 720,
 *     maxFrameRate             = 30000,
 *     maxBitRate               = 0,
 *     dataEndianness           = XDM_BYTE,
 *     maxInterFrameInterval    = 0,
 *     inputChromaFormat        = XDM_YUV_422ILE,
 *     inputContentType         = IVIDEO_PROGRESSIVE
 * @endcode
 */
extern const VIDENC_Params Venc_Params_DEFAULT;

/**
 * @brief       Default XDM dynamic parameters for a Video Encode algorithm.
 * @code
 *     size                     = sizeof(VIDENC_DynamicParams),
 *     inputHeight              = 576,
 *     inputWidth               = 720,
 *     refFrameRate             = 30000,
 *     targetFrameRate          = 30000,
 *     targetBitRate            = 0,
 *     intraFrameInterval       = 30,
 *     generateHeader           = XDM_ENCODE_AU,
 *     captureWidth             = 0,
 *     forceIFrame              = 0
 * @endcode
 */
extern const VIDENC_DynamicParams Venc_DynamicParams_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Video Encode (XDM 0.9) algorithm instance.
 *
 * @param[in]   hEngine     An opened engine containing the algorithm to create.
 * @param[in]   codecName   The name of the algorithm to open. Corresponds to
 *                          the string name given in the .cfg file.
 * @param[in]   params      XDM parameters to use while creating the codec.
 * @param[in]   dynParams   XDM dynamic parameters to use while creating the
 *                          codec. 
 *
 * @retval      Handle for use in subsequent operations (see #Venc_Handle).
 * @retval      NULL for failure.
 */
extern Venc_Handle Venc_create(Engine_Handle hEngine,
                               Char *codecName,
                               VIDENC_Params *params,
                               VIDENC_DynamicParams *dynParams);

/**
 * @brief       Encodes a video buffer.
 *
 * @param[in]   hVe         The #Venc_Handle to use for encoding.
 * @param[in]   hInBuf      The #Buffer_Handle for the buffer containing the raw
 *                          data.
 * @param[in]   hOutBuf     The #Buffer_Handle for the buffer to fill with
 *                          encoded data.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Venc_create must be called before this function.
 *
 * @remarks     Due to the design of IVIDENC the lineLength setting in
 *              the input buffer will be ignored. The frame pitch has
 *              to be set using IVIDENC_DynamicParams::captureWidth instead.
 */
extern Int Venc_process(Venc_Handle hVe, Buffer_Handle hInBuf,
                        Buffer_Handle hOutBuf);

/**
 * @brief       Deletes a Video Encode algorithm instance.
 *
 * @param[in]   hVe         The #Venc_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Venc_create must be called before this function.
 */
extern Int Venc_delete(Venc_Handle hVe);

/**
 * @brief       After a #Venc_create call is made, this function can be
 *              called to figure out the min total size of the required input
 *              buffers.
 *
 * @param[in]   hVe         The #Venc_Handle to get the size for.
 *
 * @retval      Bytes in total for all input planes.
 *
 * @remarks     #Venc_create must be called before this function.
 */
extern Int32 Venc_getInBufSize(Venc_Handle hVe);

/**
 * @brief       After a #Venc_create call is made, this function can be
 *              called to figure out the min total size of the required output
 *              buffers.
 *
 * @param[in]   hVe         The #Venc_Handle to get the size for.
 *
 * @retval      Bytes in total for all output planes.
 *
 * @remarks     #Venc_create must be called before this function.
 */
extern Int32 Venc_getOutBufSize(Venc_Handle hVe);

/**
 * @brief       Get the VIDENC handle from the Venc module instance.
 *
 * @param[in]   hVe         The #Venc_Handle for which to get the
 *                          VIDENC handle.
 *
 * @retval      Handle to the audio decode algorithm, see the XDM documentation
 *              for VIDENC.
 *
 * @remarks     #Venc_create must be called before this function.
 */
extern VIDENC_Handle Venc_getVisaHandle(Venc_Handle hVe);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_ce_Venc_h_ */
