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
 *  ======== auddec.h ========
 */
/**
 *  @file       ti/sdo/ce/audio/auddec.h
 *
 *  @brief      The AUDDEC audio decoder interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM-defined IAUDDEC audio decoder interface.
 */
/**
 *  @defgroup   AUDDEC    AUDDEC Audio Decoder Interface
 *
 *  This is the AUDDEC audio decoder interface.  Several of the data
 *  types in this API are specified by the XDM interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_audio_AUDDEC_
#define ti_sdo_ce_audio_AUDDEC_

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
#include <ti/xdais/dm/iauddec.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    AUDDEC */
/*@{*/

typedef IAUDDEC_Status AUDDEC_Status;       /**< @copydoc IAUDDEC_Status */

#define AUDDEC_EOK      IAUDDEC_EOK         /**< @copydoc IAUDDEC_EOK */
#define AUDDEC_EFAIL    IAUDDEC_EFAIL       /**< @copydoc IAUDDEC_EFAIL */
#define AUDDEC_ERUNTIME IAUDDEC_ERUNTIME    /**< @copydoc IAUDDEC_ERUNTIME */
#define AUDDEC_ETIMEOUT VISA_ETIMEOUT       /**< @copydoc VISA_ETIMEOUT */
#define AUDDEC_FOREVER  VISA_FOREVER        /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a AUDDEC codec.
 */
typedef VISA_Handle AUDDEC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a IAUDDEC-compliant audio decoder.
 */
typedef struct IAUDDEC_Params AUDDEC_Params;

/**
 * @copydoc IAUDDEC_InArgs
 */
typedef IAUDDEC_InArgs          AUDDEC_InArgs;

/**
 * @copydoc IAUDDEC_OutArgs
 */
typedef IAUDDEC_OutArgs         AUDDEC_OutArgs;

/**
 * @copydoc IAUDDEC_Cmd
 */
typedef IAUDDEC_Cmd             AUDDEC_Cmd;

/**
 * @copydoc IAUDDEC_DynamicParams
 */
typedef IAUDDEC_DynamicParams   AUDDEC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns AUDDEC_SKEL;

/**
 *  @brief      Implementation of the IAUDDEC interface that is run remotely.
 */
extern IAUDDEC_Fxns AUDDEC_STUBS;

/** @endcond */


/*
 *  ======== AUDDEC_create ========
 */
/**
 *  @brief      Create an instance of a audio decoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via AUDDEC_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of audio decoder.
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created audio decoder
 *                              instance.
 *
 *  @remarks    @c params is optional.  If it's not supplied, codec-specific
 *              default params will be used.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the audio
 *              decoder.
 *
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         AUDDEC_delete()
 */
extern AUDDEC_Handle AUDDEC_create(Engine_Handle e, String name,
    AUDDEC_Params *params);


/*
 *  ======== AUDDEC_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of an audio
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) audio decoder handle
 *              and the audio decoder is in the created state.
 *
 *  @retval     #AUDDEC_EOK         Success.
 *  @retval     #AUDDEC_EFAIL       Failure.
 *  @retval     #AUDDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     Since the AUDDEC decoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to AUDDEC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         AUDDEC_create()
 *  @sa         AUDDEC_delete()
 *  @sa         AUDDEC_control()
 *  @sa         AUDDEC_processAsync()
 *  @sa         AUDDEC_processWait()
 *  @sa         IAUDDEC_Fxns::process()
 */
extern Int32 AUDDEC_process(AUDDEC_Handle handle,
        XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
        AUDDEC_InArgs *inArgs, AUDDEC_OutArgs *outArgs);


/*
 *  ======== AUDDEC_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of an audio
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio decoder instance.
 *  @param[in]  id      Command id for XDM control operation.
 *  @param[in]  params  Runtime control parameters used for decoding.
 *  @param[out] status  Status info upon completion of decode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) audio decoder handle
 *              and the audio decoder is in the created state.
 *
 *  @retval     #AUDDEC_EOK         Success.
 *  @retval     #AUDDEC_EFAIL       Failure.
 *  @retval     #AUDDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         AUDDEC_create()
 *  @sa         AUDDEC_delete()
 *  @sa         IAUDDEC_Fxns::control()
 */
extern Int32 AUDDEC_control(AUDDEC_Handle handle, AUDDEC_Cmd id,
        AUDDEC_DynamicParams *params, AUDDEC_Status *status);


/*
 *  ======== AUDDEC_delete ========
 */
/**
 *  @brief      Delete the instance of an audio decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio decoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the audio
 *              decoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the AUDDEC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         AUDDEC_create()
 */
extern Void AUDDEC_delete(AUDDEC_Handle handle);


/*
 *  ======== AUDDEC_processAsync ========
 */
/**
 *  @brief      Perform asynchronous submission to this instance of a audio
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) audio decoder handle
 *              and the audio decoder is in the created state.
 *
 *  @retval     #AUDDEC_EOK         Success.
 *  @retval     #AUDDEC_EFAIL       Failure.
 *  @retval     #AUDDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              AUDDEC_processWait() API.
 *
 *  @remark     The buffers supplied to AUDDEC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         AUDDEC_create()
 *  @sa         AUDDEC_delete()
 *  @sa         AUDDEC_control()
 *  @sa         AUDDEC_process()
 *  @sa         AUDDEC_processWait()
 *  @sa         IAUDDEC_Fxns::process()
 */
extern XDAS_Int32 AUDDEC_processAsync(AUDDEC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, AUDDEC_InArgs *inArgs, AUDDEC_OutArgs *outArgs);


/*
 *  ======== AUDDEC_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              AUDDEC_processAsync() in this instance of an audio decoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created audio decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> AUDDEC_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) audio decoder handle
 *              and the audio decoder is in the created state.
 *
 *  @retval     #AUDDEC_EOK         Success.
 *  @retval     #AUDDEC_EFAIL       Failure.
 *  @retval     #AUDENC_ERUNTIME    Internal Runtime Error.
 *  @retval     #AUDDEC_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of AUDDEC_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              AUDDEC_processAsync() API.
 *
 *  @remark     The buffers supplied to AUDDEC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         AUDDEC_create()
 *  @sa         AUDDEC_delete()
 *  @sa         AUDDEC_control()
 *  @sa         AUDDEC_process()
 *  @sa         AUDDEC_processAsync()
 */
extern XDAS_Int32 AUDDEC_processWait(AUDDEC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, AUDDEC_InArgs *inArgs, AUDDEC_OutArgs *outArgs,
    UInt timeout);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.audio; 1, 0, 2,409; 12-2-2010 21:18:54; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

