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
 * @defgroup   ti_sdo_dmai_Vdec2    Vdec2
 *
 * @brief Provides a simple interface to VIDDEC2 (XDM 1.2) based algorithms.
 *        For typical usage see the video_decode_io2 app.
 */

#ifndef ti_sdo_dmai_ce_Vdec2_h_
#define ti_sdo_dmai_ce_Vdec2_h_

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/video2/viddec2.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufTab.h>

/** @ingroup    ti_sdo_dmai_Vdec2 */
/*@{*/

/**
 * @brief       Handle through which to reference a Video Decode algorithm.
 */
typedef struct Vdec2_Object *Vdec2_Handle;

/**
 * @brief       Default XDM parameters for a Video Decode (XDM 1.2) algorithm.
 * @code
 *     size                 = sizeof(VIDDEC2_Params),
 *     maxHeight            = 576,
 *     maxWidth             = 720,
 *     maxFrameRate         = 30000,
 *     maxBitRate           = 6000000,
 *     dataEndianness       = XDM_BYTE,
 *     forceChromaFormat    = XDM_YUV_420P
 * @endcode
 */
extern const VIDDEC2_Params Vdec2_Params_DEFAULT;

/**
 * @brief       Default XDM dynamic parameters for a Video Decode (XDM 1.2)
 *              algorithm.
 * @code
 *     size                 = sizeof(VIDDEC2_DynamicParams),
 *     decodeHeader         = XDM_DECODE_AU,
 *     displayWidth         = 0,
 *     frameSkipMode        = IVIDEO_NO_SKIP,
 *     frameOrder           = IVIDDEC2_DISPLAY_ORDER,
 *     newFrameFlag         = 0,
 *     mbDataFlag           = 0
 * @endcode
 */
extern const VIDDEC2_DynamicParams Vdec2_DynamicParams_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Video Decode (XDM 1.2) algorithm instance.
 *
 * @param[in]   hEngine     An opened engine containing the algorithm to create.
 * @param[in]   codecName   The name of the algorithm to open. Corresponds to
 *                          the string name given in the .cfg file.
 * @param[in]   params      XDM parameters to use while creating the codec.
 * @param[in]   dynParams   XDM dynamic parameters to use while creating the
 *                          codec. 
 *
 * @retval      Handle for use in subsequent operations (see #Vdec2_Handle).
 * @retval      NULL for failure.
 */
extern Vdec2_Handle Vdec2_create(Engine_Handle hEngine,
                                 Char *codecName,
                                 VIDDEC2_Params *params,
                                 VIDDEC2_DynamicParams *dynParams);


/**
 * @brief       Flushes the codec. Call #Vdec2_process (hInBuf is ignored)
 *              after this call and then #Vdec2_getDisplayBuf to obtain
 *              display buffers display, and #Vdec2_getFreeBuf to obtain
 *              buffers to free.
 *
 * @param[in]   hVd         The #Vdec2_Handle to of the decoder to flush.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Vdec2_create must be called before this function.
 */
extern Int Vdec2_flush(Vdec2_Handle hVd);

/**
 * @brief       Decodes a video buffer. Call #Vdec2_getDisplayBuf after
 *              this call to obtain buffers to display, and #Vdec2_getFreeBuf
 *              to obtain buffers to free.
 *
 * @param[in]   hVd         The #Vdec2_Handle to use for decoding.
 * @param[in]   hInBuf      The #Buffer_Handle of the buffer containing the
 *                          encoded data.
 * @param[in]   hDstBuf     The #Buffer_Handle of the buffer passed to the
 *                          decoder to be filled with data.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Vdec2_create must be called before this function.
 * @remarks     #Vdec2_setBufTab must be called before this function.
 *
 * @remarks     Due to the design of IVIDDEC2 the lineLength setting in
 *              the destination buffer will be ignored. The frame pitch has
 *              to be set using IVIDDEC2_DynamicParams::displayWidth instead.
 */
extern Int Vdec2_process(Vdec2_Handle hVd,
                         Buffer_Handle hInBuf,
                         Buffer_Handle hDstBuf);

/**
 * @brief       Deletes a Video Decode algorithm instance.
 *
 * @param[in]   hVd         The #Vdec2_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Vdec2_create must be called before this function.
 */
extern Int Vdec2_delete(Vdec2_Handle hVd);

/**
 * @brief       Figures out the actual output buffer requirements of the codec
 *              after the first #Vdec2_process call. Also updates the buffer
 *              requirements for subsequent #Vdec2_getInBufSize and
 *              #Vdec2_getOutBufSize calls.
 *
 * @param[in]   hVd         The #Vdec2_Handle to use for decoding.
 *
 * @retval      Number of required output buffers on success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Vdec2_create must be called before this function.
 * @remarks     #Vdec2_process must be called before this function.
 */
extern Int32 Vdec2_getMinOutBufs(Vdec2_Handle hVd);

/**
 * @brief       After a #Vdec2_create call is made, this function should be
 *              called to hand a #BufTab_Handle to the video decoder instance.
 *              Because of B-frames, the destination buffer given may not be
 *              the same as the output buffer returned, so the Vdec2 class
 *              needs a full array of buffers to work with.
 *
 * @param[in]   hVd         The #Vdec2_Handle to set the BufTab for.
 * @param[in]   hBufTab     The #BufTab_Handle to give to the video decoder.
 *
 * @remarks     #Vdec2_create must be called before this function.
 */
extern Void Vdec2_setBufTab(Vdec2_Handle hVd, BufTab_Handle hBufTab);

/**
 * @brief       Get the BufTab previously set using #Vdec2_setBufTab.
 *
 * @param[in]   hVd         The #Vdec2_Handle for which to get the BufTab.
 *
 * @retval      Handle to the BufTab managing the codec buffers
 *              (see #BufTab_Handle).
 *
 * @remarks     #Vdec2_create must be called before this function.
 * @remarks     #Vdec2_setBufTab must be called before this function.
 */
extern BufTab_Handle Vdec2_getBufTab(Vdec2_Handle hVd);

/**
 * @brief       Get the VIDDEC2 handle from the Vdec2 module instance.
 *
 * @param[in]   hVd         The #Vdec2_Handle for which to get the
 *                          VIDDEC2 handle.
 *
 * @retval      Handle to the audio decode algorithm, see the XDM documentation
 *              for VIDDEC2.
 *
 * @remarks     #Vdec2_create must be called before this function.
 */
extern VIDDEC2_Handle Vdec2_getVisaHandle(Vdec2_Handle hVd);

/**
 * @brief       Get the input buffer size required by the codec.
 *
 * @param[in]   hVd         The #Vdec2_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the input buffer required.
 *
 * @remarks     #Vdec2_create must be called before this function.
 */
extern Int32 Vdec2_getInBufSize(Vdec2_Handle hVd);

/**
 * @brief       Get the output buffer size required by the codec.
 *
 * @param[in]   hVd         The #Vdec2_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the output buffer required.
 *
 * @remarks     #Vdec2_create must be called before this function.
 */
extern Int32 Vdec2_getOutBufSize(Vdec2_Handle hVd);

/**
 * @brief       After a #Vdec2_process call is made, this function should be
 *              called to obtain buffers to display. This function should be
 *              called consecutively until no more buffers are returned.
 *
 * @param[in]   hVd         The #Vdec2_Handle to obtain display buffers from.
 *
 * @retval      Handle to a Buffer to display (see #Buffer_Handle).
 * @retval      NULL if no more Buffers are available.
 *
 * @remarks     #Vdec2_create must be called before this function.
 * @remarks     #Vdec2_process must be called before this function.
 */
extern Buffer_Handle Vdec2_getDisplayBuf(Vdec2_Handle hVd);

/**
 * @brief       After a #Vdec2_process call is made, this function should be
 *              called to obtain buffers to free. This function should be
 *              called consecutively until no more buffers are returned.
 *
 * @param[in]   hVd         The #Vdec2_Handle to obtain free buffers from.
 *
 * @retval      Handle to a Buffer to free (see #Buffer_Handle).
 * @retval      NULL if no more Buffers are available.
 *
 * @remarks     #Vdec2_create must be called before this function.
 * @remarks     #Vdec2_process must be called before this function.
 */
extern Buffer_Handle Vdec2_getFreeBuf(Vdec2_Handle hVd);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_ce_Vdec2_h_ */
