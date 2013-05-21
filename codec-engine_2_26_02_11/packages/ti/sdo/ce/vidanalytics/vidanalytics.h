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
 *  ======== vidtranscode.h ========
 */

/**
 *  @file       ti/sdo/ce/vidanalytics/vidanalytics.h
 *
 *  @brief      The video analytics codec interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM video analytics interface.
 */
/**
 *  @defgroup   ti_sdo_ce_vidanalytics_VIDANALYTICS    Video Analytics Algorithm Interface
 *
 *  This is the video analytics codec interface.  Several of the data
 *  types in this API are specified by the XDM interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_vidanalytics_VIDANALYTICS_
#define ti_sdo_ce_vidanalytics_VIDANALYTICS_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ividanalytics.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_vidanalytics_VIDANALYTICS */
/*@{*/

/** @copydoc IVIDANALYTICS_EOK */
#define VIDANALYTICS_EOK            IVIDANALYTICS_EOK

/** @copydoc IVIDANALYTICS_EFAIL */
#define VIDANALYTICS_EFAIL          IVIDANALYTICS_EFAIL

/** @copydoc IVIDANALYTICS_EUNSUPPORTED */
#define VIDANALYTICS_EUNSUPPORTED   IVIDANALYTICS_EUNSUPPORTED

/**< @copydoc VISA_ETIMEOUT */
#define VIDANALYTICS_ETIMEOUT VISA_ETIMEOUT

/**< @copydoc VISA_FOREVER */
#define VIDANALYTICS_FOREVER  VISA_FOREVER

/**
 *  @brief      Opaque handle to a VIDANALYTICS codec.
 */
typedef VISA_Handle VIDANALYTICS_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a video analytics algorithm.
 */
typedef struct IVIDANALYTICS_Params VIDANALYTICS_Params;

/** @copydoc IVIDANALYTICS_InArgs */
typedef IVIDANALYTICS_InArgs  VIDANALYTICS_InArgs;
/** @copydoc IVIDANALYTICS_OutArgs */
typedef IVIDANALYTICS_OutArgs VIDANALYTICS_OutArgs;
/** @copydoc IVIDANALYTICS_Cmd */
typedef IVIDANALYTICS_Cmd     VIDANALYTICS_Cmd;
/** @copydoc IVIDANALYTICS_Status */
typedef IVIDANALYTICS_Status  VIDANALYTICS_Status;

/** @copydoc IVIDANALYTICS_DynamicParams */
typedef IVIDANALYTICS_DynamicParams VIDANALYTICS_DynamicParams;


/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns VIDANALYTICS_SKEL;

/**
 *  @brief      Implementation of the IVIDANALYTICS interface that is run
 *              remotely.
 */
extern IVIDANALYTICS_Fxns VIDANALYTICS_STUBS;

/** @endcond */


/*
 *  ======== VIDANALYTICS_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of a video
 *              analytics algorithm.
 *
 *  @param[in]  handle  Handle to a created video analytics instance.
 *  @param[in]  id      Command id for XDM control operation.
 *  @param[in]  params  Runtime control parameters used for the video
 *                      analytics instance.
 *  @param[out] status  Status info returned by the video analytics instance.
 *
 *  @pre        @c handle is a valid (non-NULL) video analytics handle
 *              and the video analytics instance is in the created state.
 *
 *  @retval     #VIDANALYTICS_EOK           Success.
 *  @retval     #VIDANALYTICS_EFAIL         Failure.
 *  @retval     #VIDANALYTICS_EUNSUPPORTED  Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         VIDANALYTICS_create()
 *  @sa         VIDANALYTICS_delete()
 *  @sa         IVIDANALYTICS_Fxns::control()
 */
extern Int32 VIDANALYTICS_control(VIDANALYTICS_Handle handle,
    VIDANALYTICS_Cmd id, VIDANALYTICS_DynamicParams *params,
    VIDANALYTICS_Status *status);


/*
 *  ======== VIDANALYTICS_create ========
 */
/**
 *  @brief      Create an instance of a video analytics algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via VIDANALYTICS_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of video analytics
 *                      algorithm to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created video analytics
 *                              instance.
 *
 *  @remarks    @c params is optional.  If it's not supplied, codec-specific
 *              default params will be used.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the video
 *              analytics algorithm.
 *
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         VIDANALYTICS_delete()
 */
extern VIDANALYTICS_Handle VIDANALYTICS_create(Engine_Handle e, String name,
    VIDANALYTICS_Params *params);


/*
 *  ======== VIDANALYTICS_delete ========
 */
/**
 *  @brief      Delete the instance of a video analytics algorithm.
 *
 *  @param[in]  handle  Handle to a created video analytics instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the video
 *              analytics algorithm.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the VIDANALYTICS_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         VIDANALYTICS_create()
 */
extern Void VIDANALYTICS_delete(VIDANALYTICS_Handle handle);


/*
 *  ======== VIDANALYTICS_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a video
 *              analytics algorithm.
 *
 *  @param[in]  handle  Handle to a created video analytics instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) video analytics handle
 *              and the video analytics algorithm instance is in the
 *              created state.
 *
 *  @retval     #VIDANALYTICS_EOK           Success.
 *  @retval     #VIDANALYTICS_EFAIL         Failure.
 *  @retval     #VIDANALYTICS_EUNSUPPORTED  Unsupported request.
 *
 *  @remark     Since the VIDANALYTICS algorithm contains support for
 *              asynchronous buffer submission and retrieval, this API
 *              becomes known as synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to VIDANALYTICS_process() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running
 *              on a remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDANALYTICS_create()
 *  @sa         VIDANALYTICS_delete()
 *  @sa         VIDANALYTICS_control()
 *  @sa         VIDANALYTICS_processAsync()
 *  @sa         VIDANALYTICS_processWait()
 *  @sa         IVIDANALYTICS_Fxns::process()
 */
extern Int32 VIDANALYTICS_process(VIDANALYTICS_Handle handle,
    XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, VIDANALYTICS_InArgs *inArgs,
    VIDANALYTICS_OutArgs *outArgs);

/*
 *  ======== VIDANALYTICS_processAsync ========
 */
/**
 *  @brief      Perform asynchronous submission to this instance of a video
 *              analytics algorithm.
 *
 *  @param[in]  handle  Handle to a created video analytics instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) video analytics handle
 *              and the video analytics algorithm instance is in the
 *              created state.
 *
 *  @retval     #VIDANALYTICS_EOK         Success.
 *  @retval     #VIDANALYTICS_EFAIL       Failure.
 *  @retval     #VIDANALYTICS_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              VIDANALYTICS_processWait() API.
 *
 *  @remark     The buffers supplied to VIDANALYTICS_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDANALYTICS_create()
 *  @sa         VIDANALYTICS_delete()
 *  @sa         VIDANALYTICS_control()
 *  @sa         VIDANALYTICS_process()
 *  @sa         VIDANALYTICS_processWait()
 *  @sa         IVIDANALYTICS_Fxns::process()
 */
extern XDAS_Int32 VIDANALYTICS_processAsync(VIDANALYTICS_Handle handle,
    XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IVIDANALYTICS_InArgs *inArgs,
    IVIDANALYTICS_OutArgs *outArgs);

/*
 *  ======== VIDANALYTICS_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              VIDANALYTICS_processAsync() in this instance of an video
 *              analytics algorithm.
 *
 *  @param[in]  handle  Handle to a created video analytics instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> VIDANALYTICS_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) video analytics handle
 *              and the video analytics algorithm instance is in the
 *              created state.
 *
 *  @retval     #VIDANALYTICS_EOK         Success.
 *  @retval     #VIDANALYTICS_EFAIL       Failure.
 *  @retval     #VIDANALYTICS_EUNSUPPORTED Unsupported request.
 *  @retval     #VIDANALYTICS_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of VIDANALYTICS_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              VIDANALYTICS_processAsync() API.
 *
 *  @remark     The buffers supplied to VIDANALYTICS_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDANALYTICS_create()
 *  @sa         VIDANALYTICS_delete()
 *  @sa         VIDANALYTICS_control()
 *  @sa         VIDANALYTICS_process()
 *  @sa         VIDANALYTICS_processAsync()
 */
extern XDAS_Int32 VIDANALYTICS_processWait(VIDANALYTICS_Handle handle,
    XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IVIDANALYTICS_InArgs *inArgs,
    IVIDANALYTICS_OutArgs *outArgs, UInt timeout);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.vidanalytics; 1, 0, 1,209; 12-2-2010 21:28:16; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

