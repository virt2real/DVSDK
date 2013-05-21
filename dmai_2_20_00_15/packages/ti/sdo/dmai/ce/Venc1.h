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
 * @defgroup   ti_sdo_dmai_Venc1   Venc1
 *
 * @brief Provides a simple interface to VIDENC1 (XDM 1.0) based algorithms.
 *        For typical usage see the video_encode_io1 app.
 */

#ifndef ti_sdo_dmai_ce_Venc1_h_
#define ti_sdo_dmai_ce_Venc1_h_

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/video1/videnc1.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Venc1 */
/*@{*/

/**
 * @brief       Handle through which to reference a Video Encode algorithm.
 */
typedef struct Venc1_Object *Venc1_Handle;

/**
 * @brief       Default XDM parameters for a Video Encode algorithm.
 * @code
 *     size                     = sizeof(VIDENC1_Params),
 *     encodingPreset           = XDM_DEFAULT,
 *     rateControlPreset        = IVIDEO_LOW_DELAY,
 *     maxHeight                = 720,
 *     maxWidth                 = 1280,
 *     maxFrameRate             = 30000,
 *     maxBitRate               = 6000000,
 *     dataEndianness           = XDM_BYTE,
 *     maxInterFrameInterval    = 0,
 *     inputChromaFormat        = XDM_YUV_420P,
 *     inputContentType         = IVIDEO_PROGRESSIVE,
 *     reconChromaFormat        = XDM_CHROMA_NA
 * @endcode
 */
extern const VIDENC1_Params Venc1_Params_DEFAULT;

/**
 * @brief       Default XDM dynamic parameters for a Video Encode algorithm.
 * @code
 *     size                     = sizeof(IVIDENC1_DynamicParams),
 *     inputHeight              = 720,
 *     inputWidth               = 1280,
 *     refFrameRate             = 30000,
 *     targetFrameRate          = 30000,
 *     targetBitRate            = 6000000,
 *     intraFrameInterval       = 30,
 *     generateHeader           = XDM_DECODE_AU,
 *     captureWidth             = 0,
 *     forceFrame               = IVIDEO_NA_FRAME,
 *     interFrameInterval       = 1,
 *     mbDataFlag               = 0
 * @endcode
 */
extern const VIDENC1_DynamicParams Venc1_DynamicParams_DEFAULT;

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
 * @retval      Handle for use in subsequent operations (see #Venc1_Handle).
 * @retval      NULL for failure.
 */
extern Venc1_Handle Venc1_create(Engine_Handle hEngine,
                                 Char *codecName,
                                 VIDENC1_Params *params,
                                 VIDENC1_DynamicParams *dynParams);

/**
 * @brief       Encodes a video buffer.
 *
 * @param[in]   hVe         The #Venc1_Handle to use for encoding.
 * @param[in]   hInBuf      The #Buffer_Handle for the buffer containing the raw
 *                          data.
 * @param[in]   hOutBuf     The #Buffer_Handle for the buffer to fill with
 *                          encoded data.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Venc1_create must be called before this function.
 *
 * @remarks     The lineLength setting in the input buffer will be passed as
 *              the framePitch in the IVIDEO1_BufDescIn parameter to
 *              VIDENC1_process.  However, not the codecs may not recognize
 *              or use this framePitch setting.
 *              See IVIDENC1_DynamicParams::captureWidth for setting the frame
 *              pitch, and refer to your encoder user's guide for more
 *              information on area encode operations.
 */
extern Int Venc1_process(Venc1_Handle hVe, Buffer_Handle hInBuf,
                         Buffer_Handle hOutBuf);

/**
 * @brief       Deletes a Video Encode algorithm instance.
 *
 * @param[in]   hVe         The #Venc1_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int Venc1_delete(Venc1_Handle hVe);

/**
 * @brief       After a #Venc1_create call is made, this function can be
 *              called to figure out the total size of the required input
 *              buffer.
 *
 * @param[in]   hVe         The #Venc1_Handle to get the size for.
 *
 * @retval      Size in bytes of the input buffer.
 *
 * @remarks     #Venc1_create must be called before this function.
 */
extern Int32 Venc1_getInBufSize(Venc1_Handle hVe);

/**
 * @brief       After a #Venc1_create call is made, this function can be
 *              called to figure out the min total size of the required output
 *              buffers.
 *
 * @param[in]   hVe         The #Venc1_Handle to get the size for.
 *
 * @retval      Bytes in total for all output planes.
 *
 * @remarks     #Venc1_create must be called before this function.
 */
extern Int32 Venc1_getOutBufSize(Venc1_Handle hVe);

/**
 * @brief       Get the VIDENC1 handle from the Venc module instance.
 *
 * @param[in]   hVe         The #Venc1_Handle for which to get the
 *                          VIDENC1 handle.
 *
 * @retval      Handle to the audio decode algorithm, see the XDM documentation
 *              for VIDENC1.
 *
 * @remarks     #Venc1_create must be called before this function.
 */
extern VIDENC1_Handle Venc1_getVisaHandle(Venc1_Handle hVe);

/**
 * @brief       Get the reconstructed frame buffers created during the call
 *              to Venc1_process.
 *
 * @param[in]   hVe         The #Venc1_Handle for which to get the
 *                          VIDENC1 handle.
 *
 * @retval      Pointer to the IVIDEO1_BufDesc object that contains information
 *              about reconstructed frames.  This is equivalent to the
 *              outArgs.reconBufs member created during VIDENC1_process.
 *
 * @remarks     #Venc1_process must be called before this function.  The object
 *              pointed to by the return value becomes invalid after any
 *              subsequent call to #Venc1_process.
 */
extern IVIDEO1_BufDesc* Venc1_getReconBufs(Venc1_Handle hVe);

/**
 * @brief       After a #Venc1_process call is made, this function should be
 *              called to obtain the freed raw buffers.
 *
 * @param[in]   hVe         The #Venc1_Handle to obtain display buffers from.
 *
 * @retval      Handle to a free Buffer (see #Buffer_Handle).
 * @retval      NULL if no more Buffers are available.
 *
 * @remarks     #Venc1_create must be called before this function.
 * @remarks     #Venc1_process must be called before this function.
 */
extern Buffer_Handle Venc1_getFreeBuf(Venc1_Handle hVe);

/**
 * @brief       After a #Venc1_create call is made, this function should be
 *              called to hand a #BufTab_Handle to the video encoder instance.
 *              Because of B-frames, the input buffer given may not be
 *              the same as the input buffer returned, so the Venc1 class
 *              needs a full array of input buffers to work with.
 *
 * @param[in]   hVe         The #Venc1_Handle to set the BufTab for.
 * @param[in]   hBufTab     The #BufTab_Handle to give to the video encoder.
 *
 * @remarks     #Venc1_create must be called before this function.
 */

extern Void Venc1_setBufTab(Venc1_Handle hVe, BufTab_Handle hBufTab);

/**
 * @brief       Get the BufTab previously set using #Venc1_setBufTab.
 *
 * @param[in]   hVe         The #Venc1_Handle for which to get the BufTab.
 *
 * @retval      Handle to the BufTab managing the codec buffers
 *              (see #BufTab_Handle).
 *
 * @remarks     #Venc1_create must be called before this function.
 * @remarks     #Venc1_setBufTab must be called before this function.
 */

extern BufTab_Handle Venc1_getBufTab(Venc1_Handle hVe);

/**
 * @brief       Flushes the codec. Call #Venc1_process after this call
 *
 * @param[in]   hVe         The #Venc1_Handle to the encoder to flush.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Venc1_create must be called before this function.
 */

extern Int Venc1_flush(Venc1_Handle hVe);


#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_ce_Venc1_h_ */
