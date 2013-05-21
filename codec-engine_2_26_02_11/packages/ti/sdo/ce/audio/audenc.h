/* 
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
 * 
 */
/*
 *  ======== audenc.h ========
 */
/**
 *  @file       ti/sdo/ce/audio/audenc.h
 *
 *  @brief      The AUDENC audio encoder interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM-defined IAUDENC audio encoder interface.
 */
/**
 *  @defgroup   AUDENC    AUDENC Audio Encoder Interface
 *
 *  This is the AUDENC audio encoder codec interface.  Several of the data
 *  types in this API are specified by the XDM interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_audio_AUDENC_
#define ti_sdo_ce_audio_AUDENC_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * By definition, this interface is 0.9 XDM.  Before including xdm.h,
 * define XDM_INCLUDE_DOT9_SUPPORT
 */
#ifndef XDM_INCLUDE_DOT9_SUPPORT
#define XDM_INCLUDE_DOT9_SUPPORT
#endif
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/iaudenc.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    AUDENC */
/*@{*/

typedef IAUDENC_Status AUDENC_Status;       /**< @copydoc IAUDENC_Status */

#define AUDENC_EOK      IAUDENC_EOK         /**< @copydoc IAUDENC_EOK */
#define AUDENC_EFAIL    IAUDENC_EFAIL       /**< @copydoc IAUDENC_EFAIL */
#define AUDENC_ERUNTIME IAUDENC_ERUNTIME    /**< @copydoc IAUDENC_ERUNTIME */
#define AUDENC_ETIMEOUT VISA_ETIMEOUT       /**< @copydoc VISA_ETIMEOUT */
#define AUDENC_FOREVER  VISA_FOREVER        /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a AUDENC codec.
 */
typedef VISA_Handle AUDENC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a Audio Encoder object.
 */
typedef struct IAUDENC_Params AUDENC_Params;

/**
 * @copydoc IAUDENC_InArgs
 */
typedef IAUDENC_InArgs          AUDENC_InArgs;

/**
 * @copydoc IAUDENC_OutArgs
 */
typedef IAUDENC_OutArgs         AUDENC_OutArgs;

/**
 * @copydoc IAUDENC_Cmd
 */
typedef IAUDENC_Cmd             AUDENC_Cmd;

/**
 * @copydoc IAUDENC_DynamicParams
 */
typedef IAUDENC_DynamicParams   AUDENC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns AUDENC_SKEL;

/**
 *  @brief      Implementation of the IAUDENC interface that is run remotely.
 */
extern IAUDENC_Fxns AUDENC_STUBS;

/** @endcond */


/*
 *  ======== AUDENC_create ========
 */
/**
 *  @brief      Create an instance of an audio encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via AUDENC_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of audio encoder.
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created audio encoder
 *                              instance.
 *
 *  @remarks    @c params is optional.  If it's not supplied, codec-specific
 *              default params will be used.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the audio
 *              encoder.
 *
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         AUDENC_delete()
 */
extern AUDENC_Handle AUDENC_create(Engine_Handle e, String name,
        AUDENC_Params *params);


/*
 *  ======== AUDENC_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of an audio
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio encoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) audio encoder handle
 *              and the audio encoder is in the created state.
 *
 *  @retval     #AUDENC_EOK         Success.
 *  @retval     #AUDENC_EFAIL       Failure.
 *  @retval     #AUDENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     Since the AUDENC encoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to AUDENC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @remark     If an error is returned, @c outArgs->extendedError may
 *              indicate further details about the error.  See
 *              #AUDENC_OutArgs::extendedError for details.
 *
 *  @sa         AUDENC_create()
 *  @sa         AUDENC_delete()
 *  @sa         AUDENC_control()
 *  @sa         AUDENC_processAsync()
 *  @sa         AUDENC_processWait()
 *  @sa         IAUDENC_Fxns::process()  - the reflected algorithm interface,
 *                                         which may contain further usage
 *                                         details.
 */
extern Int32 AUDENC_process(AUDENC_Handle handle,
        XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
        AUDENC_InArgs *inArgs, AUDENC_OutArgs *outArgs);


/*
 *  ======== AUDENC_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of an audio
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio encoder instance.
 *  @param[in]  id      Command id for XDM control operation.
 *  @param[in]  params  Runtime control parameters used for encoding.
 *  @param[out] status  Status info upon completion of encode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) audio encoder handle
 *              and the audio encoder is in the created state.
 *
 *  @retval     #AUDENC_EOK         Success.
 *  @retval     #AUDENC_EFAIL       Failure.
 *  @retval     #AUDENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @remark     If an error is returned, @c status->extendedError may
 *              indicate further details about the error.  See
 *              #AUDDEC_Status::extendedError for details.
 *
 *  @sa         AUDENC_create()
 *  @sa         AUDENC_delete()
 *  @sa         IAUDENC_Fxns::control()  - the reflected algorithm interface,
 *                                         which may contain further usage
 *                                         details.
 */
extern Int32 AUDENC_control(AUDENC_Handle handle, AUDENC_Cmd id,
        AUDENC_DynamicParams *params, AUDENC_Status *status);


/*
 *  ======== AUDENC_delete ========
 */
/**
 *  @brief      Delete the instance of an audio encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio encoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the audio
 *              encoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the AUDENC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         AUDENC_create()
 */
extern Void AUDENC_delete(AUDENC_Handle handle);


/*
 *  ======== AUDENC_processAsync ========
 */
/**
 *  @brief      Perform asynchronous submission to this instance of a audio
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio encoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) audio encoder handle
 *              and the audio encoder is in the created state.
 *
 *  @retval     #AUDENC_EOK         Success.
 *  @retval     #AUDENC_EFAIL       Failure.
 *  @retval     #AUDENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              AUDENC_processWait() API.
 *
 *  @remark     The buffers supplied to AUDENC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         AUDENC_create()
 *  @sa         AUDENC_delete()
 *  @sa         AUDENC_control()
 *  @sa         AUDENC_process()
 *  @sa         AUDENC_processWait()
 *  @sa         IAUDENC_Fxns::process()
 *  @sa         IAUDENC_Fxns::process()  - the reflected algorithm interface,
 *                                         which may contain further usage
 *                                         details.
 */
extern XDAS_Int32 AUDENC_processAsync(AUDENC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IAUDENC_InArgs *inArgs, IAUDENC_OutArgs *outArgs);


/*
 *  ======== AUDENC_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              AUDENC_processAsync() in this instance of an audio encoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created audio encoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> AUDENC_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) audio encoder handle
 *              and the audio encoder is in the created state.
 *
 *  @retval     #AUDENC_EOK         Success.
 *  @retval     #AUDENC_EFAIL       Failure.
 *  @retval     #AUDENC_ERUNTIME    Internal Runtime Error.
 *  @retval     #AUDENC_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of AUDENC_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              AUDENC_processAsync() API.
 *
 *  @remark     The buffers supplied to AUDENC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         AUDENC_create()
 *  @sa         AUDENC_delete()
 *  @sa         AUDENC_control()
 *  @sa         AUDENC_process()
 *  @sa         AUDENC_processAsync()
 */
extern XDAS_Int32 AUDENC_processWait(AUDENC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IAUDENC_InArgs *inArgs, IAUDENC_OutArgs *outArgs,
    UInt timeout);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.audio; 1, 0, 2,409; 12-2-2010 21:18:54; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

