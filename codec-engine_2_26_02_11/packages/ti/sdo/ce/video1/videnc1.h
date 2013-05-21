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
 *  ======== videnc1.h ========
 */
/**
 *  @file       ti/sdo/ce/video1/videnc1.h
 *
 *  @brief      The VIDENC1 video encoder codec interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM IVIDENC1 video encoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_video1_VIDENC1    Video encoder codec interface
 *
 *  This is the VIDENC1 video encoder codec interface.  Several of the data
 *  types in this API are specified by the XDM IVIDENC1 interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_video1_VIDENC1_
#define ti_sdo_ce_video1_VIDENC1_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ividenc1.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_video1_VIDENC1 */
/*@{*/

typedef IVIDENC1_Status VIDENC1_Status;       /**< @copydoc IVIDENC1_Status */

#define VIDENC1_EOK      IVIDENC1_EOK         /**< @copydoc IVIDENC1_EOK */
#define VIDENC1_EFAIL    IVIDENC1_EFAIL       /**< @copydoc IVIDENC1_EFAIL */

/**< @copydoc IVIDENC1_EUNSUPPORTED */
#define VIDENC1_EUNSUPPORTED IVIDENC1_EUNSUPPORTED

#define VIDENC1_ETIMEOUT VISA_ETIMEOUT        /**< @copydoc VISA_ETIMEOUT */
#define VIDENC1_FOREVER  VISA_FOREVER         /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a VIDENC1 codec.
 */
typedef VISA_Handle VIDENC1_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a VIDENC1-based video encoder.
 */
typedef struct IVIDENC1_Params VIDENC1_Params;

/**
 * @copydoc IVIDENC1_InArgs
 */
typedef IVIDENC1_InArgs          VIDENC1_InArgs;

/**
 * @copydoc IVIDENC1_OutArgs
 */
typedef IVIDENC1_OutArgs         VIDENC1_OutArgs;

/**
 * @copydoc IVIDENC1_Cmd
 */
typedef IVIDENC1_Cmd             VIDENC1_Cmd;

/**
 * @copydoc IVIDENC1_DynamicParams
 */
typedef IVIDENC1_DynamicParams   VIDENC1_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns VIDENC1_SKEL;

/**
 *  @brief      Implementation of the IVIDENC1 interface that is run remotely.
 */
extern IVIDENC1_Fxns VIDENC1_STUBS;

/**
 *  @brief      Definition of IVIDENC1 codec class configurable parameters
 */
typedef struct IVIDENC1_CodecClassConfig {
    Bool manageInBufsCache     [ XDM_MAX_IO_BUFFERS ];
    Bool manageOutBufsCache    [ XDM_MAX_IO_BUFFERS ];
} IVIDENC1_CodecClassConfig;

/** @endcond */

/*
 *  ======== VIDENC1_create ========
 */
/**
 *  @brief      Create an instance of a video encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via VIDENC1_create) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of video encoder
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created video encoder
 *                              instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the video
 *              encoder.
 *
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 */
extern VIDENC1_Handle VIDENC1_create(Engine_Handle e, String name,
    VIDENC1_Params *params);


/*
 *  ======== VIDENC1_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a video
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video encoder instance.
 *  @param[in]  inBufs  A buffer describer containing input buffers.
 *  @param[out] outBufs A buffer describer containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) video encoder handle
 *              and the video encoder is in the created state.
 *
 *  @retval     #VIDENC1_EOK         Success.
 *  @retval     #VIDENC1_EFAIL       Failure.
 *
 *  @remark     Since the VIDENC1 decoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to VIDENC1_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         VIDENC1_create()
 *  @sa         VIDENC1_delete()
 *  @sa         VIDENC1_control()
 *  @sa         VIDENC1_processAsync()
 *  @sa         VIDENC1_processWait()
 *  @sa         IVIDENC1_Fxns::process()
 */
extern Int32 VIDENC1_process(VIDENC1_Handle handle, IVIDEO1_BufDescIn *inBufs,
    XDM_BufDesc *outBufs, VIDENC1_InArgs *inArgs, VIDENC1_OutArgs *outArgs);


/*
 *  ======== VIDENC1_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of a video
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video encoder instance.
 *  @param[in]  id      Command id for XDM control operation.
 *  @param[in]  params  Runtime control parameters used for encoding.
 *  @param[out] status  Status info upon completion of encode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) video encoder handle
 *              and the video encoder is in the created state.
 *
 *  @retval     #VIDENC1_EOK         Success.
 *  @retval     #VIDENC1_EFAIL       Failure.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @remark     If #VIDENC1_EFAIL is returned, @c status->extendedError may
 *              indicate further details about the error.  See #XDM_ErrorBit
 *              for details.
 *
 *  @sa         VIDENC1_create()
 *  @sa         VIDENC1_delete()
 *  @sa         IVIDENC1_Fxns::process()
 *  @sa         XDM_ErrorBit
 */
extern Int32 VIDENC1_control(VIDENC1_Handle handle, VIDENC1_Cmd id,
    VIDENC1_DynamicParams *params, VIDENC1_Status *status);


/*
 *  ======== VIDENC1_delete ========
 */
/**
 *  @brief      Delete the instance of a video encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video encoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the video
 *              encoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the VIDENC1_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         VIDENC1_create()
 */
extern Void VIDENC1_delete(VIDENC1_Handle handle);

/*
 *  ======== VIDENC1_processAsync ========
 */
/**
 *  @brief      Perform asynchronous submission to this instance of a video
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) video decoder handle
 *              and the video decoder is in the created state.
 *
 *  @retval     #VIDENC1_EOK         Success.
 *  @retval     #VIDENC1_EFAIL       Failure.
 *  @retval     #VIDENC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              VIDENC1_processWait() API.
 *
 *  @remark     The buffers supplied to VIDENC1_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDENC1_create()
 *  @sa         VIDENC1_delete()
 *  @sa         VIDENC1_control()
 *  @sa         VIDENC1_process()
 *  @sa         VIDENC1_processWait()
 *  @sa         IVIDENC1_Fxns::process()
 */
extern XDAS_Int32 VIDENC1_processAsync(VIDENC1_Handle handle,
    IVIDEO1_BufDescIn *inBufs, XDM_BufDesc *outBufs,
    IVIDENC1_InArgs *inArgs, IVIDENC1_OutArgs *outArgs);

/*
 *  ======== VIDENC1_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              VIDENC1_processAsync() in this instance of an video decoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> VIDENC1_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) video decoder handle
 *              and the video decoder is in the created state.
 *
 *  @retval     #VIDENC1_EOK         Success.
 *  @retval     #VIDENC1_EFAIL       Failure.
 *  @retval     #VIDENC1_EUNSUPPORTED Unsupported request.
 *  @retval     #VIDENC1_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of VIDENC1_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              VIDENC1_processAsync() API.
 *
 *  @remark     The buffers supplied to VIDENC1_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDENC1_create()
 *  @sa         VIDENC1_delete()
 *  @sa         VIDENC1_control()
 *  @sa         VIDENC1_process()
 *  @sa         VIDENC1_processAsync()
 */
extern XDAS_Int32 VIDENC1_processWait(VIDENC1_Handle handle,
    IVIDEO1_BufDescIn *inBufs, XDM_BufDesc *outBufs,
    IVIDENC1_InArgs *inArgs, IVIDENC1_OutArgs *outArgs, UInt timeout);

/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.video1; 1, 0, 2,269; 12-2-2010 21:28:27; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

