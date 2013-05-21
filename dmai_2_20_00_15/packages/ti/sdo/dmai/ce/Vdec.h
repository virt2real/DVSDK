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
 * @defgroup   ti_sdo_dmai_Vdec    Vdec
 *
 * @brief Provides a simple interface to VIDDEC (XDM 0.9) based algorithms.
 *        For typical usage see the video_decode_io app.
 */

#ifndef ti_sdo_dmai_ce_Vdec_h_
#define ti_sdo_dmai_ce_Vdec_h_

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/video/viddec.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufTab.h>

/** @ingroup    ti_sdo_dmai_Vdec */
/*@{*/

/**
 * @brief       Handle through which to reference a Video Decode algorithm.
 */
typedef struct Vdec_Object *Vdec_Handle;

/**
 * @brief       Default XDM parameters for a Video Decode algorithm.
 * @code
 *     size                 = sizeof(VIDDEC_Params),
 *     maxHeight            = 576,
 *     maxWidth             = 720,
 *     maxFrameRate         = 0,
 *     maxBitRate           = 0,
 *     dataEndianness       = XDM_BYTE,
 *     forceChromaFormat    = XDM_YUV_422ILE,
 * @endcode
 */
extern const VIDDEC_Params Vdec_Params_DEFAULT;

/**
 * @brief       Default XDM dynamic parameters for a Video Decode algorithm.
 * @code
 *     size                 = sizeof(VIDDEC_DynamicParams),
 *     decodeHeader         = XDM_DECODE_AU,
 *     displayWidth         = XDM_DEFAULT,
 *     frameSkipMode        = IVIDEO_NO_SKIP,
 * @endcode
 */
extern const VIDDEC_DynamicParams Vdec_DynamicParams_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Video Decode (XDM 0.9) algorithm instance.
 *
 * @param[in]   hEngine     An opened engine containing the algorithm to create.
 * @param[in]   codecName   The name of the algorithm to open. Corresponds to
 *                          the string name given in the .cfg file.
 * @param[in]   params      XDM parameters to use while creating the codec.
 * @param[in]   dynParams   XDM dynamic parameters to use while creating the
 *                          codec. 
 *
 * @retval      Handle for use in subsequent operations (see #Vdec_Handle).
 * @retval      NULL for failure.
 */
extern Vdec_Handle Vdec_create(Engine_Handle hEngine,
                               Char *codecName,
                               VIDDEC_Params *params,
                               VIDDEC_DynamicParams *dynParams);

/**
 * @brief       Flushes the codec. Call #Vdec_process (hInBuf is ignored)
 *              after this call and then #Vdec_getDisplayBuf to obtain
 *              display buffers display.
 *
 * @param[in]   hVd         The #Vdec_Handle to of the decoder to flush.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Vdec_create must be called before this function.
 */
extern Int Vdec_flush(Vdec_Handle hVd);

/**
 * @brief       Decodes a video buffer.
 *
 * @param[in]   hVd         The #Vdec_Handle to use for decoding.
 * @param[in]   hInBuf      The #Buffer_Handle for the buffer containing the
 *                          encoded data.
 * @param[in]   hDstBuf     The #Buffer_Handle of the buffer passed to the
 *                          decoder to be filled with data. Depending on buffer
 *                          reordering due to B-frames, this may or may not be
 *                          the same buffer returned in subsequent
 *                          #Vdec_getDisplayBuf calls.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Vdec_create must be called before this function.
 * @remarks     #Vdec_setBufTab must be called before this function.
 *
 * @remarks     Due to the design of IVIDDEC the lineLength setting in
 *              the input buffer will be ignored. The frame pitch has
 *              to be set using IVIDDEC_DynamicParams::displayWidth instead.
 */
extern Int Vdec_process(Vdec_Handle hVd,
                        Buffer_Handle hInBuf,
                        Buffer_Handle hDstBuf);

/**
 * @brief       Deletes a Video Decode algorithm instance.
 *
 * @param[in]   hVd         The #Vdec_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Vdec_create must be called before this function.
 */
extern Int Vdec_delete(Vdec_Handle hVd);

/**
 * @brief       After a #Vdec_create call is made, this function should be
 *              called to hand a #BufTab_Handle to the video decoder instance
 *              to be used to hold output buffers. Because of B-frames, the
 *              destination buffer given in the process call may not be the
 *              same as the output buffer to be displayed.
 *
 * @param[in]   hVd         The #Vdec_Handle to set the BufTab for.
 * @param[in]   hBufTab     The #BufTab_Handle to give to the video decoder.
 *
 * @remarks     #Vdec_create must be called before this function.
 */
extern Void Vdec_setBufTab(Vdec_Handle hVd, BufTab_Handle hBufTab);

/**
 * @brief       Get the BufTab previously set using #Vdec_setBufTab.
 *
 * @param[in]   hVd         The #Vdec_Handle for which to get the BufTab.
 *
 * @retval      Handle to the BufTab managing the codec buffers
 *              (see #BufTab_Handle).
 *
 * @remarks     #Vdec_create must be called before this function.
 * @remarks     #Vdec_setBufTab must be called before this function.
 */
extern BufTab_Handle Vdec_getBufTab(Vdec_Handle hVd);

/**
 * @brief       After a #Vdec_create call is made, this function can be
 *              called to figure out the min total size of the required input
 *              buffers.
 *
 * @param[in]   hVd         The #Vdec_Handle to get the size for.
 *
 * @retval      Bytes in total for all input planes.
 *
 * @remarks     #Vdec_create must be called before this function.
 */
extern Int32 Vdec_getInBufSize(Vdec_Handle hVd);

/**
 * @brief       After a #Vdec_create call is made, this function can be
 *              called to figure out the min total size of the required output
 *              buffers.
 *
 * @param[in]   hVd         The #Vdec_Handle to get the size for.
 *
 * @retval      Bytes in total for all output planes.
 *
 * @remarks     #Vdec_create must be called before this function.
 */
extern Int32 Vdec_getOutBufSize(Vdec_Handle hVd);

/**
 * @brief       After a #Vdec_process call is made, this function should be
 *              called to obtain buffers to display. This function should be
 *              called consecutively until no more buffers are returned.
 *
 * @param[in]   hVd         The #Vdec_Handle to obtain display buffers from.
 *
 * @retval      Handle to a Buffer to display (see #Buffer_Handle).
 * @retval      NULL if no more Buffers are available.
 *
 * @remarks     #Vdec_create must be called before this function.
 * @remarks     #Vdec_process must be called before this function.
 */
extern Buffer_Handle Vdec_getDisplayBuf(Vdec_Handle hVd);

/**
 * @brief       Get the VIDDEC handle from the Vdec module instance.
 *
 * @param[in]   hVd         The #Vdec_Handle for which to get the
 *                          VIDDEC handle.
 *
 * @retval      Handle to the video decode algorithm, see the XDM documentation
 *              for VIDDEC.
 *
 * @remarks     #Vdec_create must be called before this function.
 */
extern VIDDEC_Handle Vdec_getVisaHandle(Vdec_Handle hVd);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_ce_Vdec_h_ */
