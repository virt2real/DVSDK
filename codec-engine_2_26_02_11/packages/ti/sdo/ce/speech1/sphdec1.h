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
 *  ======== sphdec1.h ========
 */

/**
 *  @file       ti/sdo/ce/speech1/sphdec1.h
 *
 *  @brief      The SPHDEC1 decoder codec interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM ISPHDEC1 speech decoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_speech1_SPHDEC1 Speech decoder codec interface
 *
 *  This is the SPHDEC1 speech decoder codec interface.  Several of the data
 *  types in this API are specified by the XDM interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_speech1_SPHDEC1_
#define ti_sdo_ce_speech1_SPHDEC1_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/isphdec1.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_speech1_SPHDEC1 */
/*@{*/

#define SPHDEC1_EOK      ISPHDEC1_EOK       /**< @copydoc ISPHDEC1_EOK */
#define SPHDEC1_EFAIL    ISPHDEC1_EFAIL     /**< @copydoc ISPHDEC1_EFAIL */

/** @copydoc ISPHDEC1_EUNSUPPORTED */
#define SPHDEC1_EUNSUPPORTED ISPHDEC1_EUNSUPPORTED

#define SPHDEC1_ETIMEOUT VISA_ETIMEOUT        /**< @copydoc VISA_ETIMEOUT */
#define SPHDEC1_FOREVER  VISA_FOREVER         /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a SPHDEC1 codec.
 */
typedef VISA_Handle SPHDEC1_Handle;

/* The following are just wrapper typedefs */

/** @copydoc ISPHDEC1_Params */
typedef ISPHDEC1_Params SPHDEC1_Params;

/** @copydoc ISPHDEC1_InArgs */
typedef ISPHDEC1_InArgs  SPHDEC1_InArgs;

/** @copydoc ISPHDEC1_OutArgs */
typedef ISPHDEC1_OutArgs SPHDEC1_OutArgs;

/**< @copydoc ISPHDEC1_Cmd */
typedef ISPHDEC1_Cmd     SPHDEC1_Cmd;

/** @copydoc ISPHDEC1_DynamicParams */
typedef ISPHDEC1_DynamicParams SPHDEC1_DynamicParams;

/**< @copydoc ISPHDEC1_Status */
typedef ISPHDEC1_Status SPHDEC1_Status;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns SPHDEC1_SKEL;

/**
 *  @brief      Implementation of the ISPHDEC1 interface that is run remotely.
 */
extern ISPHDEC1_Fxns SPHDEC1_STUBS;

/** @endcond */


/*
 *  ======== SPHDEC1_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of a speech
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
 *  @retval     #SPHDEC1_EOK         Success.
 *  @retval     #SPHDEC1_EFAIL       Failure.
 *  @retval     #SPHDEC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         SPHDEC1_create()
 *  @sa         SPHDEC1_delete()
 *  @sa         ISPHDEC1_Fxns()::control()
 */
extern Int32 SPHDEC1_control(SPHDEC1_Handle handle, SPHDEC1_Cmd id,
    SPHDEC1_DynamicParams *params, SPHDEC1_Status *status);


/*
 *  ======== SPHDEC1_create ========
 */
/**
 *  @brief      Create an instance of a speech decoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via SPHDEC1_create()) or
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
 *  @remarks    @c params is optional.  If it's not supplied, codec-specific
 *              default params will be used.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the speech1
 *              decoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         SPHDEC1_delete()
 */
extern SPHDEC1_Handle SPHDEC1_create(Engine_Handle e, String name,
    SPHDEC1_Params *params);


/*
 *  ======== SPHDEC1_delete ========
 */
/**
 *  @brief      Delete the instance of a speech decoder algorithm.
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
 *  @post       All resources allocated as part of the SPHDEC1_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         SPHDEC1_create()
 */
extern Void SPHDEC1_delete(SPHDEC1_Handle handle);


/*
 *  ======== SPHDEC1_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a speech
 *              decoder algorithm.
 *
 *  @param[in]  handle          Handle to a created speech decoder instance.
 *  @param[in]  inBuf           A buffer descriptor containing an input buffer.
 *  @param[out] outBuf          A buffer descriptor containing an output buffer.
 *  @param[in]  inArgs          Input Arguments.
 *  @param[out] outArgs         Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) speech decoder handle
 *              and the speech decoder is in the created state.
 *
 *  @retval     #SPHDEC1_EOK         Success.
 *  @retval     #SPHDEC1_EFAIL       Failure.
 *  @retval     #SPHDEC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     Since the SPHDEC1 decoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to SPHDEC1_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         SPHDEC1_create()
 *  @sa         SPHDEC1_delete()
 *  @sa         SPHDEC1_control()
 *  @sa         SPHDEC1_processAsync()
 *  @sa         SPHDEC1_processWait()
 *  @sa         ISPHDEC1_Fxns()::process()
 */
extern Int32 SPHDEC1_process(SPHDEC1_Handle handle,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    SPHDEC1_InArgs *inArgs, SPHDEC1_OutArgs *outArgs);


/*
 *  ======== SPHDEC1_processAsync ========
 */
/**
 *  @brief      Perform asynchronous submission to this instance of a speech
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech decoder instance.
 *  @param[in]  inBuf   A buffer descriptor containing the input buffer.
 *  @param[out] outBuf  A buffer descriptor containing the output buffer.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) speech decoder handle
 *              and the speech decoder is in the created state.
 *
 *  @retval     #SPHDEC1_EOK         Success.
 *  @retval     #SPHDEC1_EFAIL       Failure.
 *  @retval     #SPHDEC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              SPHDEC1_processWait() API.
 *
 *  @remark     The buffers supplied to SPHDEC1_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         SPHDEC1_create()
 *  @sa         SPHDEC1_delete()
 *  @sa         SPHDEC1_control()
 *  @sa         SPHDEC1_process()
 *  @sa         SPHDEC1_processWait()
 *  @sa         ISPHDEC1_Fxns::process()
 */
extern XDAS_Int32 SPHDEC1_processAsync(SPHDEC1_Handle handle,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    SPHDEC1_InArgs *inArgs, SPHDEC1_OutArgs *outArgs);

/*
 *  ======== SPHDEC1_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              SPHDEC1_processAsync() in this instance of an speech decoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created speech decoder instance.
 *  @param[in]  inBuf   A buffer descriptor containing the input buffer.
 *  @param[out] outBuf  A buffer descriptor containing the output buffer.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> SPHDEC1_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) speech decoder handle
 *              and the speech decoder is in the created state.
 *
 *  @retval     #SPHDEC1_EOK         Success.
 *  @retval     #SPHDEC1_EFAIL       Failure.
 *  @retval     #SPHDEC1_EUNSUPPORTED Unsupported request.
 *  @retval     #SPHDEC1_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of SPHDEC1_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              SPHDEC1_processAsync() API.
 *
 *  @remark     The buffers supplied to SPHDEC1_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         SPHDEC1_create()
 *  @sa         SPHDEC1_delete()
 *  @sa         SPHDEC1_control()
 *  @sa         SPHDEC1_process()
 *  @sa         SPHDEC1_processAsync()
 */
extern XDAS_Int32 SPHDEC1_processWait(SPHDEC1_Handle handle,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    SPHDEC1_InArgs *inArgs, SPHDEC1_OutArgs *outArgs, UInt timeout);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.speech1; 1, 0, 1,276; 12-2-2010 21:25:21; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

