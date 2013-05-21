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
 *  ======== sphenc.h ========
 */
/**
 *  @file       ti/sdo/ce/speech/sphenc.h
 *
 *  @brief      The SPHENC speech encoder codec interface.  Provides the
 *              user an interface to create and interact with XDAIS algorithms
 *              that are compliant with the XDM ISPHENC speech encoder
 *              interface.
 */
/**
 *  @defgroup   SPHENC    SPHENC Speech Encoder Interface
 *
 *  This is the SPHENC speech encoder codec interface.  Several of the data
 *  types in this API are specified by the XDM interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_speech_SPHENC_
#define ti_sdo_ce_speech_SPHENC_

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
#include <ti/xdais/dm/isphenc.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    SPHENC */
/*@{*/

typedef ISPHENC_Status SPHENC_Status;       /**< @copydoc ISPHENC_Status */

#define SPHENC_EOK      ISPHENC_EOK         /**< @copydoc ISPHENC_EOK */
#define SPHENC_EFAIL    ISPHENC_EFAIL       /**< @copydoc ISPHENC_EFAIL */
#define SPHENC_ERUNTIME ISPHENC_ERUNTIME    /**< @copydoc ISPHENC_ERUNTIME */
#define SPHENC_ETIMEOUT VISA_ETIMEOUT       /**< @copydoc VISA_ETIMEOUT */
#define SPHENC_FOREVER  VISA_FOREVER        /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a SPHENC codec.
 */
typedef VISA_Handle SPHENC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a Speech/Voice Encoder object.
 */
typedef struct ISPHENC_Params SPHENC_Params;

/**
 * @copydoc ISPHENC_InArgs
 */
typedef ISPHENC_InArgs          SPHENC_InArgs;

/**
 * @copydoc ISPHENC_OutArgs
 */
typedef ISPHENC_OutArgs         SPHENC_OutArgs;

/**
 * @copydoc ISPHENC_Cmd
 */
typedef ISPHENC_Cmd             SPHENC_Cmd;

/**
 * @copydoc ISPHENC_DynamicParams
 */
typedef ISPHENC_DynamicParams   SPHENC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns SPHENC_SKEL;

/**
 *  @brief      Implementation of the ISPHENC interface that is run remotely.
 */
extern ISPHENC_Fxns SPHENC_STUBS;

/** @endcond */

/*
 *  ======== SPHENC_create ========
 */
/**
 *  @brief      Create an instance of a speech encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via SPHENC_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of speech encoder
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created speech encoder
 *                              instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the speech
 *              encoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         SPHENC_delete()
 */
extern SPHENC_Handle SPHENC_create(Engine_Handle e, String name,
        SPHENC_Params *params);


/*
 *  ======== SPHENC_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a speech
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech encoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) speech encoder handle
 *              and the speech encoder is in the created state.
 *
 *  @retval     #SPHENC_EOK         Success.
 *  @retval     #SPHENC_EFAIL       Failure.
 *  @retval     #SPHENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     Since the SPHENC decoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to SPHENC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         SPHENC_create()
 *  @sa         SPHENC_delete()
 *  @sa         SPHENC_control()
 *  @sa         SPHENC_processAsync()
 *  @sa         SPHENC_processWait()
 *  @sa         ISPHENC_Fxns::process()
 */
extern Int32 SPHENC_process(SPHENC_Handle handle,
        XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
        SPHENC_InArgs *inArgs, SPHENC_OutArgs *outArgs);


/*
 *  ======== SPHENC_control ========
 */
/**
 *  @brief      Execute the control method in this instance of a speech
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech encoder instance.
 *  @param[in]  id      Command id for XDM control operation.
 *  @param[in]  params  Runtime control parameters used for encoding.
 *  @param[out] status  Status info upon completion of encode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) speech encoder handle
 *              and the speech encoder is in the created state.
 *
 *  @retval     #SPHENC_EOK         Success.
 *  @retval     #SPHENC_EFAIL       Failure.
 *  @retval     #SPHENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         SPHENC_create()
 *  @sa         SPHENC_delete()
 *  @sa         ISPHENC_Fxns::control()
 */
extern Int32 SPHENC_control(SPHENC_Handle handle, SPHENC_Cmd id,
       SPHENC_DynamicParams *params, SPHENC_Status *status);


/*
 *  ======== SPHENC_delete ========
 */
/**
 *  @brief      Delete the instance of a speech/voice encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech encoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the speech
 *              encoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the SPHENC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         SPHENC_create()
 */
extern Void SPHENC_delete(SPHENC_Handle handle);


/*
 *  ======== SPHENC_processAsync ========
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
 *  @retval     #SPHENC_EOK         Success.
 *  @retval     #SPHENC_EFAIL       Failure.
 *  @retval     #SPHENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              SPHENC_processWait() API.
 *
 *  @remark     The buffers supplied to SPHENC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         SPHENC_create()
 *  @sa         SPHENC_delete()
 *  @sa         SPHENC_control()
 *  @sa         SPHENC_process()
 *  @sa         SPHENC_processWait()
 *  @sa         ISPHENC_Fxns::process()
 */
extern XDAS_Int32 SPHENC_processAsync(SPHENC_Handle handle, XDM_BufDesc *inBufs,
        XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs);


/*
 *  ======== SPHENC_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              SPHENC_processAsync() in this instance of an speech decoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created speech decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> SPHENC_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) speech decoder handle
 *              and the speech decoder is in the created state.
 *
 *  @retval     #SPHENC_EOK         Success.
 *  @retval     #SPHENC_EFAIL       Failure.
 *  @retval     #SPHENC_ERUNTIME    Internal Runtime Error.
 *  @retval     #SPHENC_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of SPHENC_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              SPHENC_processAsync() API.
 *
 *  @remark     The buffers supplied to SPHENC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         SPHENC_create()
 *  @sa         SPHENC_delete()
 *  @sa         SPHENC_control()
 *  @sa         SPHENC_process()
 *  @sa         SPHENC_processAsync()
 */
extern XDAS_Int32 SPHENC_processWait(SPHENC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs,
    UInt timeout);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.speech; 1, 0, 2,416; 12-2-2010 21:25:17; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

