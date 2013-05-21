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
 *  ======== sphenc1.h ========
 */

/**
 *  @file       ti/sdo/ce/speech1/sphenc1.h
 *
 *  @brief      The Speech 1.0 Encoder Codec Interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM 1.0 Speech Encoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_speech1_SPHENC1 Speech 1.0 Encoder Codec Interface
 *
 *  This is the Speech 1.0 Encoder Codec Interface.  Several of the data
 *  types in this API are specified by the XDM 1.0 interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_speech1_SPHENC1_
#define ti_sdo_ce_speech1_SPHENC1_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/isphenc1.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_speech1_SPHENC1 */
/*@{*/

#define SPHENC1_EOK      ISPHENC1_EOK         /**< @copydoc ISPHENC1_EOK */
#define SPHENC1_EFAIL    ISPHENC1_EFAIL       /**< @copydoc ISPHENC1_EFAIL */

/** @copydoc ISPHENC1_EUNSUPPORTED */
#define SPHENC1_EUNSUPPORTED ISPHENC1_EUNSUPPORTED

#define SPHENC1_ETIMEOUT VISA_ETIMEOUT        /**< @copydoc VISA_ETIMEOUT */
#define SPHENC1_FOREVER  VISA_FOREVER         /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a SPHENC1 codec.
 */
typedef VISA_Handle SPHENC1_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a speech encoder.
 */
typedef struct ISPHENC1_Params SPHENC1_Params;


typedef ISPHENC1_InArgs  SPHENC1_InArgs;    /**< @copydoc ISPHENC1_InArgs */
typedef ISPHENC1_OutArgs SPHENC1_OutArgs;   /**< @copydoc ISPHENC1_OutArgs */
typedef ISPHENC1_Cmd     SPHENC1_Cmd;       /**< @copydoc ISPHENC1_Cmd */
typedef ISPHENC1_Status SPHENC1_Status;     /**< @copydoc ISPHENC1_Status */

/** @copydoc ISPHENC1_DynamicParams */
typedef ISPHENC1_DynamicParams SPHENC1_DynamicParams;


/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns SPHENC1_SKEL;

/**
 *  @brief      Implementation of the ISPHENC1 interface that is run remotely.
 */
extern ISPHENC1_Fxns SPHENC1_STUBS;

/** @endcond */


/*
 *  ======== SPHENC1_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of a speech
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
 *  @retval     #SPHENC1_EOK         Success.
 *  @retval     #SPHENC1_EFAIL       Failure.
 *  @retval     #SPHENC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         SPHENC1_create()
 *  @sa         SPHENC1_delete()
 *  @sa         ISPHENC1_Fxns::control()
 */
extern Int32 SPHENC1_control(SPHENC1_Handle handle, SPHENC1_Cmd id,
    SPHENC1_DynamicParams *params, SPHENC1_Status *status);


/*
 *  ======== SPHENC1_create ========
 */
/**
 *  @brief      Create an instance of a speech encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via SPHENC1_create()) or
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
 *  @remarks    @c params is optional.  If it's not supplied, codec-specific
 *              default params will be used.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the speech1
 *              encoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         SPHENC_delete()
 */
extern SPHENC1_Handle SPHENC1_create(Engine_Handle e, String name,
    SPHENC1_Params *params);


/*
 *  ======== SPHENC1_delete ========
 */
/**
 *  @brief      Delete the instance of a speech encoder algorithm.
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
 *  @post       All resources allocated as part of the SPHENC1_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         SPHENC1_create()
 */
extern Void SPHENC1_delete(SPHENC1_Handle handle);


/*
 *  ======== SPHENC1_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a speech
 *              encoder algorithm.
 *
 *  @param[in]  handle          Handle to a created speech encoder instance.
 *  @param[in,out] inBuf        A buffer descriptor containing an input buffer.
 *  @param[out] outBuf          A buffer descriptor containing an output buffer.
 *  @param[in]  inArgs          Input Arguments.
 *  @param[out] outArgs         Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) speech encoder handle
 *              and the speech encoder is in the created state.
 *
 *  @retval     #SPHENC1_EOK         Success.
 *  @retval     #SPHENC1_EFAIL       Failure.
 *  @retval     #SPHENC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     Since the SPHENC1 encoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to SPHENC1_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         SPHENC1_create()
 *  @sa         SPHENC1_delete()
 *  @sa         SPHENC1_control()
 *  @sa         SPHENC1_processAsync()
 *  @sa         SPHENC1_processWait()
 *  @sa         ISPHENC1_Fxns::process()
 */
extern Int32 SPHENC1_process(SPHENC1_Handle handle,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    SPHENC1_InArgs *inArgs, SPHENC1_OutArgs *outArgs);

/*
 *  ======== SPHENC1_processAsync ========
 */
/**
 *  @brief      Perform asynchronous submission to this instance of a speech
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech encoder instance.
 *  @param[in]  inBuf   A buffer descriptor containing the input buffer.
 *  @param[out] outBuf  A buffer descriptor containing the output buffer.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) speech encoder handle
 *              and the speech encoder is in the created state.
 *
 *  @retval     #SPHENC1_EOK         Success.
 *  @retval     #SPHENC1_EFAIL       Failure.
 *  @retval     #SPHENC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              SPHENC1_processWait() API.
 *
 *  @remark     The buffers supplied to SPHENC1_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         SPHENC1_create()
 *  @sa         SPHENC1_delete()
 *  @sa         SPHENC1_control()
 *  @sa         SPHENC1_process()
 *  @sa         SPHENC1_processWait()
 *  @sa         ISPHENC1_Fxns::process()
 */
extern XDAS_Int32 SPHENC1_processAsync(SPHENC1_Handle handle,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    SPHENC1_InArgs *inArgs, SPHENC1_OutArgs *outArgs);

/*
 *  ======== SPHENC1_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              SPHENC1_processAsync() in this instance of an speech encoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created speech encoder instance.
 *  @param[in]  inBuf   A buffer descriptor containing the input buffer.
 *  @param[out] outBuf  A buffer descriptor containing the output buffer.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> SPHENC1_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) speech encoder handle
 *              and the speech encoder is in the created state.
 *
 *  @retval     #SPHENC1_EOK         Success.
 *  @retval     #SPHENC1_EFAIL       Failure.
 *  @retval     #SPHENC1_EUNSUPPORTED Unsupported request.
 *  @retval     #SPHENC1_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of SPHENC1_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              SPHENC1_processAsync() API.
 *
 *  @remark     The buffers supplied to SPHENC1_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         SPHENC1_create()
 *  @sa         SPHENC1_delete()
 *  @sa         SPHENC1_control()
 *  @sa         SPHENC1_process()
 *  @sa         SPHENC1_processAsync()
 */
extern XDAS_Int32 SPHENC1_processWait(SPHENC1_Handle handle,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    SPHENC1_InArgs *inArgs, SPHENC1_OutArgs *outArgs, UInt timeout);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.speech1; 1, 0, 1,276; 12-2-2010 21:25:22; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

