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
 *  ======== sphdec.h ========
 */
/**
 *  @file       ti/sdo/ce/speech/sphdec.h
 *
 *  @brief      The SPHDEC speech decoder codec interface.  Provides the
 *              user an interface to create and interact with XDAIS algorithms
 *              that are compliant with the XDM ISPHDEC speech decoder
 *              interface.
 */
/**
 *  @defgroup   SPHDEC    SPHDEC Speech Decoder Interface
 *
 *  This is the SPHDEC speech decoder codec interface.  Several of the data
 *  types in this API are specified by the XDM interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_speech_SPHDEC_
#define ti_sdo_ce_speech_SPHDEC_

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
#include <ti/xdais/dm/isphdec.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    SPHDEC */
/*@{*/

typedef ISPHDEC_Status SPHDEC_Status;       /**< @copydoc ISPHDEC_Status */

#define SPHDEC_EOK      ISPHDEC_EOK         /**< @copydoc ISPHDEC_EOK */
#define SPHDEC_EFAIL    ISPHDEC_EFAIL       /**< @copydoc ISPHDEC_EFAIL */
#define SPHDEC_ERUNTIME ISPHDEC_ERUNTIME    /**< @copydoc ISPHDEC_ERUNTIME */
#define SPHDEC_ETIMEOUT VISA_ETIMEOUT       /**< @copydoc VISA_ETIMEOUT */
#define SPHDEC_FOREVER  VISA_FOREVER        /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a SPHDEC codec.
 */
typedef VISA_Handle SPHDEC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a speech decoder object.
 */
typedef struct ISPHDEC_Params SPHDEC_Params;

/**
 * @copydoc ISPHDEC_InArgs
 */
typedef ISPHDEC_InArgs          SPHDEC_InArgs;

/**
 * @copydoc ISPHDEC_OutArgs
 */
typedef ISPHDEC_OutArgs         SPHDEC_OutArgs;

/**
 * @copydoc ISPHDEC_Cmd
 */
typedef ISPHDEC_Cmd             SPHDEC_Cmd;

/**
 * @copydoc ISPHDEC_DynamicParams
 */
typedef ISPHDEC_DynamicParams   SPHDEC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns SPHDEC_SKEL;

/**
 *  @brief      Implementation of the ISPHDEC interface that is run remotely.
 */
extern ISPHDEC_Fxns SPHDEC_STUBS;

/** @endcond */

/*
 *  ======== SPHDEC_create ========
 */
/**
 *  @brief      Create an instance of a speech decoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via SPHDEC_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of speech decoder
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created speech decoder
 *                              instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the speech
 *              decoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         SPHDEC_delete()
 */
extern SPHDEC_Handle SPHDEC_create(Engine_Handle e, String name,
        SPHDEC_Params *params);


/*
 *  ======== SPHDEC_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a speech
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) speech decoder handle
 *              and the speech decoder is in the created state.
 *
 *  @retval     #SPHDEC_EOK         Success.
 *  @retval     #SPHDEC_EFAIL       Failure.
 *  @retval     #SPHDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     Since the SPHDEC decoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to SPHDEC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         SPHDEC_create()
 *  @sa         SPHDEC_delete()
 *  @sa         SPHDEC_control()
 *  @sa         SPHDEC_processAsync()
 *  @sa         SPHDEC_processWait()
 *  @sa         ISPHDEC_Fxns::process()
 */
extern Int32 SPHDEC_process(SPHDEC_Handle handle,
        XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
        SPHDEC_InArgs *inArgs, SPHDEC_OutArgs *outArgs);


/*
 *  ======== SPHDEC_control ========
 */
/**
 *  @brief      Execute the control method in this instance of a speech
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech decoder instance.
 *  @param[in]  id      Command id for XDM control operation.
 *  @param[in]  params  Runtime control parameters used for decoding.
 *  @param[out] status  Status info upon completion of decode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) speech decoder handle
 *              and the speech decoder is in the created state.
 *
 *  @retval     #SPHDEC_EOK         Success.
 *  @retval     #SPHDEC_EFAIL       Failure.
 *  @retval     #SPHDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         SPHDEC_create()
 *  @sa         SPHDEC_delete()
 *  @sa         ISPHDEC_Fxns::control()
 */
extern Int32 SPHDEC_control(SPHDEC_Handle handle, SPHDEC_Cmd id,
        SPHDEC_DynamicParams *params, SPHDEC_Status *status);


/*
 *  ======== SPHDEC_delete ========
 */
/**
 *  @brief      Delete the instance of a speech/voice decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech decoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the speech
 *              decoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the SPHDEC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         SPHDEC_create()
 */
extern Void SPHDEC_delete(SPHDEC_Handle handle);


/*
 *  ======== SPHDEC_processAsync ========
 */
/**
 *  @brief      Perform asynchronous submission to this instance of a speech
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) speech decoder handle
 *              and the speech decoder is in the created state.
 *
 *  @retval     #SPHDEC_EOK         Success.
 *  @retval     #SPHDEC_EFAIL       Failure.
 *  @retval     #SPHDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              SPHDEC_processWait() API.
 *
 *  @remark     The buffers supplied to SPHDEC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         SPHDEC_create()
 *  @sa         SPHDEC_delete()
 *  @sa         SPHDEC_control()
 *  @sa         SPHDEC_process()
 *  @sa         SPHDEC_processWait()
 *  @sa         ISPHDEC_Fxns::process()
 */
extern XDAS_Int32 SPHDEC_processAsync(SPHDEC_Handle handle, XDM_BufDesc *inBufs,
        XDM_BufDesc *outBufs, SPHDEC_InArgs *inArgs, SPHDEC_OutArgs *outArgs);


/*
 *  ======== SPHDEC_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              SPHDEC_processAsync() in this instance of an speech decoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created speech decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> SPHDEC_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) speech decoder handle
 *              and the speech decoder is in the created state.
 *
 *  @retval     #SPHDEC_EOK         Success.
 *  @retval     #SPHDEC_EFAIL       Failure.
 *  @retval     #SPHDEC_ERUNTIME    Internal Runtime Error.
 *  @retval     #SPHDEC_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of SPHDEC_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              SPHDEC_processAsync() API.
 *
 *  @remark     The buffers supplied to SPHDEC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         SPHDEC_create()
 *  @sa         SPHDEC_delete()
 *  @sa         SPHDEC_control()
 *  @sa         SPHDEC_process()
 *  @sa         SPHDEC_processAsync()
 */
extern XDAS_Int32 SPHDEC_processWait(SPHDEC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, SPHDEC_InArgs *inArgs, SPHDEC_OutArgs *outArgs,
    UInt timeout);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.speech; 1, 0, 2,416; 12-2-2010 21:25:16; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

