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
 *  ======== videnc.h ========
 */
/**
 *  @file       ti/sdo/ce/video/videnc.h
 *
 *  @brief      The VIDENC video encoder codec interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM IVIDENC video encoder interface.
 */
/**
 *  @defgroup   VIDENC    VIDENC Video Encoder Interface
 *
 *  This is the VIDENC video encoder codec interface.  Several of the data
 *  types in this API are specified by the XDM interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_video_VIDENC_
#define ti_sdo_ce_video_VIDENC_

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
#include <ti/xdais/dm/ividenc.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    VIDENC */
/*@{*/

typedef IVIDENC_Status VIDENC_Status;       /**< @copydoc IVIDENC_Status */

#define VIDENC_EOK      IVIDENC_EOK         /**< @copydoc IVIDENC_EOK */
#define VIDENC_EFAIL    IVIDENC_EFAIL       /**< @copydoc IVIDENC_EFAIL */
#define VIDENC_ERUNTIME IVIDENC_ERUNTIME    /**< @copydoc IVIDENC_ERUNTIME */
#define VIDENC_ETIMEOUT VISA_ETIMEOUT       /**< @copydoc VISA_ETIMEOUT */
#define VIDENC_FOREVER  VISA_FOREVER        /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a VIDENC codec.
 */
typedef VISA_Handle VIDENC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a video encoder object.
 */
typedef struct IVIDENC_Params VIDENC_Params;

/**
 * @copydoc IVIDENC_InArgs
 */
typedef IVIDENC_InArgs          VIDENC_InArgs;

/**
 * @copydoc IVIDENC_OutArgs
 */
typedef IVIDENC_OutArgs         VIDENC_OutArgs;

/**
 * @copydoc IVIDENC_Cmd
 */
typedef IVIDENC_Cmd             VIDENC_Cmd;

/**
 * @copydoc IVIDENC_DynamicParams
 */
typedef IVIDENC_DynamicParams   VIDENC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns VIDENC_SKEL;

/**
 *  @brief      Implementation of the IVIDENC interface that is run remotely.
 */
extern IVIDENC_Fxns VIDENC_STUBS;

/** @endcond */

/**
 *  @brief      Definition of IVIDENC codec class configurable parameters
 *
 *  @sa         VISA_getCodecClassConfig()
 */
typedef struct IVIDENC_CodecClassConfig {
    Bool manageInBufsCache   [ XDM_MAX_IO_BUFFERS ];
    Bool manageOutBufsCache  [ XDM_MAX_IO_BUFFERS ];
    Bool manageReconBufsCache[ XDM_MAX_IO_BUFFERS ];
} IVIDENC_CodecClassConfig;

/*
 *  ======== VIDENC_create ========
 */
/**
 *  @brief      Create an instance of a video encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via VIDENC_create) or
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
 *  @remark     Depending on the configuration of the engine opened, this call
 *              may create a local or remote instance of the video encoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         VIDENC_delete()
 */
extern VIDENC_Handle VIDENC_create(Engine_Handle e, String name,
    VIDENC_Params *params);


/*
 *  ======== VIDENC_process ========
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
 *  @retval     #VIDENC_EOK         Success.
 *  @retval     #VIDENC_EFAIL       Failure.
 *  @retval     #VIDENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     Since the VIDENC decoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to VIDENC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         VIDENC_create()
 *  @sa         VIDENC_delete()
 *  @sa         VIDENC_control()
 *  @sa         VIDENC_processAsync()
 *  @sa         VIDENC_processWait()
 *  @sa         IVIDENC_Fxns::process()
 */
extern Int32 VIDENC_process(VIDENC_Handle handle,
        XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
        VIDENC_InArgs *inArgs, VIDENC_OutArgs *outArgs);


/*
 *  ======== VIDENC_control ========
 */
/**
 *  @brief      Execute the "control" method in this instance of a video
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
 *  @retval     #VIDENC_EOK         Success.
 *  @retval     #VIDENC_EFAIL       Failure.
 *  @retval     #VIDENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         VIDENC_create()
 *  @sa         VIDENC_delete()
 *  @sa         IVIDENC_Fxns::process()
 */
extern Int32 VIDENC_control(VIDENC_Handle handle, VIDENC_Cmd id,
        VIDENC_DynamicParams *params, VIDENC_Status *status);


/*
 *  ======== VIDENC_delete ========
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
 *  @post       All resources allocated as part of the VIDENC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         VIDENC_create()
 */
extern Void VIDENC_delete(VIDENC_Handle handle);


/*
 *  ======== VIDENC_processAsync ========
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
 *  @retval     #VIDENC_EOK         Success.
 *  @retval     #VIDENC_EFAIL       Failure.
 *  @retval     #VIDENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              VIDENC_processWait() API.
 *
 *  @remark     The buffers supplied to VIDENC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDENC_create()
 *  @sa         VIDENC_delete()
 *  @sa         VIDENC_control()
 *  @sa         VIDENC_process()
 *  @sa         VIDENC_processWait()
 *  @sa         IVIDENC_Fxns::process()
 */
extern XDAS_Int32 VIDENC_processAsync(VIDENC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDENC_InArgs *inArgs, IVIDENC_OutArgs *outArgs);


/*
 *  ======== VIDENC_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              VIDENC_processAsync() in this instance of an video decoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> VIDENC_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) video decoder handle
 *              and the video decoder is in the created state.
 *
 *  @retval     #VIDENC_EOK         Success.
 *  @retval     #VIDENC_EFAIL       Failure.
 *  @retval     #VIDENC_ERUNTIME    Internal Runtime Error.
 *  @retval     #VIDENC_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of VIDENC_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              VIDENC_processAsync() API.
 *
 *  @remark     The buffers supplied to VIDENC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDENC_create()
 *  @sa         VIDENC_delete()
 *  @sa         VIDENC_control()
 *  @sa         VIDENC_process()
 *  @sa         VIDENC_processAsync()
 */
extern XDAS_Int32 VIDENC_processWait(VIDENC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDENC_InArgs *inArgs, IVIDENC_OutArgs *outArgs,
    UInt timeout);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.video; 1, 0, 3,408; 12-2-2010 21:28:15; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

