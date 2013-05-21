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
 *  ======== viddec1.h ========
 */

/**
 *  @file       ti/sdo/ce/video1/viddec1.h
 *
 *  @brief      The 1.0 video decoder codec interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM 1.0 video decoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_video1_VIDDEC1    Video 1.0 decoder codec interface
 *
 *  This is the 1.0 video decoder codec interface.  Several of the data
 *  types in this API are specified by the XDM 1.0 interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_video1_VIDDEC1_
#define ti_sdo_ce_video1_VIDDEC1_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ividdec1.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_video1_VIDDEC1 */
/*@{*/

typedef IVIDDEC1_Status VIDDEC1_Status;       /**< @copydoc IVIDDEC1_Status */

#define VIDDEC1_EOK      IVIDDEC1_EOK         /**< @copydoc IVIDDEC1_EOK */
#define VIDDEC1_EFAIL    IVIDDEC1_EFAIL       /**< @copydoc IVIDDEC1_EFAIL */

/**< @copydoc IVIDDEC1_EUNSUPPORTED */
#define VIDDEC1_EUNSUPPORTED IVIDDEC1_EUNSUPPORTED

#define VIDDEC1_ETIMEOUT VISA_ETIMEOUT        /**< @copydoc VISA_ETIMEOUT */
#define VIDDEC1_FOREVER  VISA_FOREVER         /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a VIDDEC1 codec.
 */
typedef VISA_Handle VIDDEC1_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a Video Decoder object.
 */
typedef struct IVIDDEC1_Params VIDDEC1_Params;

/**
 * @copydoc IVIDDEC1_InArgs
 */
typedef IVIDDEC1_InArgs          VIDDEC1_InArgs;

/**
 * @copydoc IVIDDEC1_OutArgs
 */
typedef IVIDDEC1_OutArgs         VIDDEC1_OutArgs;

/**
 * @copydoc IVIDDEC1_Cmd
 */
typedef IVIDDEC1_Cmd             VIDDEC1_Cmd;

/**
 * @copydoc IVIDDEC1_DynamicParams
 */
typedef IVIDDEC1_DynamicParams   VIDDEC1_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns VIDDEC1_SKEL;

/**
 *  @brief      Implementation of the IVIDDEC1 interface that is run remotely.
 */
extern IVIDDEC1_Fxns VIDDEC1_STUBS;

/** @endcond */

/**
 *  @brief      Definition of IVIDDEC1 codec class configurable parameters
 */
typedef struct IVIDDEC1_CodecClassConfig {
    Bool manageInBufsCache     [ XDM_MAX_IO_BUFFERS ];
    Bool manageOutBufsCache    [ XDM_MAX_IO_BUFFERS ];
} IVIDDEC1_CodecClassConfig;

/*
 *  ======== VIDDEC1_create ========
 */
/**
 *  @brief      Create an instance of a video decoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via VIDDEC1_create) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of video decoder
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created video decoder
 *                              instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the video
 *              decoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 */
extern VIDDEC1_Handle VIDDEC1_create(Engine_Handle e, String name,
    VIDDEC1_Params *params);


/*
 *  ======== VIDDEC1_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a video
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *  @param[in]  inBufs  A buffer describer containing input buffers.
 *  @param[out] outBufs A buffer describer containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) video decoder handle
 *              and the video decoder is in the created state.
 *
 *  @retval     #VIDDEC1_EOK         Success.
 *  @retval     #VIDDEC1_EFAIL       Failure.
 *
 *  @remark     Since the VIDDEC1 decoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to VIDDEC1_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         VIDDEC1_create()
 *  @sa         VIDDEC1_delete()
 *  @sa         VIDDEC1_control()
 *  @sa         VIDDEC1_processAsync()
 *  @sa         VIDDEC1_processWait()
 *  @sa         IVIDDEC1_Fxns::process()
 */
extern Int32 VIDDEC1_process(VIDDEC1_Handle handle, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, VIDDEC1_InArgs *inArgs, VIDDEC1_OutArgs *outArgs);


/*
 *  ======== VIDDEC1_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of a video
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *  @param[in]  id      Command id for XDM control operation.
 *  @param[in]  params  Runtime control parameters used for decoding.
 *  @param[out] status  Status info upon completion of decode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) video decoder handle
 *              and the video decoder is in the created state.
 *
 *  @retval     #VIDDEC1_EOK         Success.
 *  @retval     #VIDDEC1_EFAIL       Failure.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         VIDDEC1_create()
 *  @sa         VIDDEC1_delete()
 *  @sa         IVIDDEC1_Fxns::process()
 */
extern Int32 VIDDEC1_control(VIDDEC1_Handle handle, VIDDEC1_Cmd id,
    VIDDEC1_DynamicParams *params, VIDDEC1_Status *status);


/*
 *  ======== VIDDEC1_delete ========
 */
/**
 *  @brief      Delete the instance of a video decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the video
 *              decoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the VIDDEC1_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         VIDDEC1_create()
 */
extern Void VIDDEC1_delete(VIDDEC1_Handle handle);

/*
 *  ======== VIDDEC1_processAsync ========
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
 *  @retval     #VIDDEC1_EOK         Success.
 *  @retval     #VIDDEC1_EFAIL       Failure.
 *  @retval     #VIDDEC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              VIDDEC1_processWait() API.
 *
 *  @remark     The buffers supplied to VIDDEC1_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDDEC1_create()
 *  @sa         VIDDEC1_delete()
 *  @sa         VIDDEC1_control()
 *  @sa         VIDDEC1_process()
 *  @sa         VIDDEC1_processWait()
 *  @sa         IVIDDEC1_Fxns::process()
 */
extern XDAS_Int32 VIDDEC1_processAsync(VIDDEC1_Handle handle,
    XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs,
    VIDDEC1_InArgs *inArgs, VIDDEC1_OutArgs *outArgs);

/*
 *  ======== VIDDEC1_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              VIDDEC1_processAsync() in this instance of an video decoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> VIDDEC1_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) video decoder handle
 *              and the video decoder is in the created state.
 *
 *  @retval     #VIDDEC1_EOK         Success.
 *  @retval     #VIDDEC1_EFAIL       Failure.
 *  @retval     #VIDDEC1_EUNSUPPORTED Unsupported request.
 *  @retval     #VIDDEC1_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of VIDDEC1_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              VIDDEC1_processAsync() API.
 *
 *  @remark     The buffers supplied to VIDDEC1_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDDEC1_create()
 *  @sa         VIDDEC1_delete()
 *  @sa         VIDDEC1_control()
 *  @sa         VIDDEC1_process()
 *  @sa         VIDDEC1_processAsync()
 */
extern XDAS_Int32 VIDDEC1_processWait(VIDDEC1_Handle handle,
    XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs,
    VIDDEC1_InArgs *inArgs, VIDDEC1_OutArgs *outArgs, UInt timeout);

/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.video1; 1, 0, 2,269; 12-2-2010 21:28:27; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

