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
 *  ======== viddec.h ========
 */
/**
 *  @file       ti/sdo/ce/video/viddec.h
 *
 *  @brief      The VIDDEC video decoder codec interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM IVIDDEC video decoder interface.
 */
/**
 *  @defgroup   VIDDEC    VIDDEC Video Decoder Interface
 *
 *  This is the VIDDEC video decoder codec interface.  Several of the data
 *  types in this API are specified by the XDM interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_video_VIDDEC_
#define ti_sdo_ce_video_VIDDEC_

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
#include <ti/xdais/dm/ividdec.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    VIDDEC */
/*@{*/

typedef IVIDDEC_Status VIDDEC_Status;       /**< @copydoc IVIDDEC_Status */

#define VIDDEC_EOK      IVIDDEC_EOK         /**< @copydoc IVIDDEC_EOK */
#define VIDDEC_EFAIL    IVIDDEC_EFAIL       /**< @copydoc IVIDDEC_EFAIL */
#define VIDDEC_ERUNTIME IVIDDEC_ERUNTIME    /**< @copydoc IVIDDEC_ERUNTIME */
#define VIDDEC_ETIMEOUT VISA_ETIMEOUT       /**< @copydoc VISA_ETIMEOUT */
#define VIDDEC_FOREVER  VISA_FOREVER        /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a VIDDEC codec.
 */
typedef VISA_Handle VIDDEC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a video decoder object.
 */
typedef struct IVIDDEC_Params VIDDEC_Params;

/**
 * @copydoc IVIDDEC_InArgs
 */
typedef IVIDDEC_InArgs          VIDDEC_InArgs;

/**
 * @copydoc IVIDDEC_OutArgs
 */
typedef IVIDDEC_OutArgs         VIDDEC_OutArgs;

/**
 * @copydoc IVIDDEC_Cmd
 */
typedef IVIDDEC_Cmd             VIDDEC_Cmd;

/**
 * @copydoc IVIDDEC_DynamicParams
 */
typedef IVIDDEC_DynamicParams   VIDDEC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns VIDDEC_SKEL;

/**
 *  @brief      Implementation of the IVIDDEC interface that is run remotely.
 */
extern IVIDDEC_Fxns VIDDEC_STUBS;

/** @endcond */

/**
 *  @brief      Definition of VIDDEC codec class configurable parameters
 *
 *  @sa         VISA_getCodecClassConfig()
 */
typedef struct IVIDDEC_CodecClassConfig {
    /**
     *  @brief      Indicates how to manage the inBuf cache
     *
     *  @remarks    Array of Bools, indicating whether a particular inBuf
     *              should be invalidated prior to calling the codec's
     *              process() method.
     */
    Bool manageInBufsCache     [ XDM_MAX_IO_BUFFERS ];
    /**
     *  @brief      Indicates how to manage the outBuf cache
     *
     *  @remarks    Array of Bools, indicating whether a particular outBuf
     *              should be invalidated prior to calling the codec's
     *              process() method, and written back after.
     */
    Bool manageOutBufsCache    [ XDM_MAX_IO_BUFFERS ];
    /**
     *  @brief      Indicates how to manage the displayBuf cache
     *
     *  @remarks    Array of Bools, indicating whether a particular displayBuf
     *              should be writeback invalidated after calling the codec's
     *              process() method.
     */
    Bool manageDisplayBufsCache[ XDM_MAX_IO_BUFFERS ];
} IVIDDEC_CodecClassConfig;

/*
 *  ======== VIDDEC_create ========
 */
/**
 *  @brief      Create an instance of a video decoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via VIDDEC_create) or
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
 *  @sa         VIDDEC_delete()
 */
extern VIDDEC_Handle VIDDEC_create(Engine_Handle e, String name,
    VIDDEC_Params *params);


/*
 *  ======== VIDDEC_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a video
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
 *  @retval     #VIDDEC_EOK         Success.
 *  @retval     #VIDDEC_EFAIL       Failure.
 *  @retval     #VIDDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     Since the VIDDEC decoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to VIDDEC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         VIDDEC_create()
 *  @sa         VIDDEC_delete()
 *  @sa         VIDDEC_control()
 *  @sa         VIDDEC_processAsync()
 *  @sa         VIDDEC_processWait()
 *  @sa         IVIDDEC_Fxns::process()
 */
extern Int32 VIDDEC_process(VIDDEC_Handle handle,
        XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
        VIDDEC_InArgs *inArgs, VIDDEC_OutArgs *outArgs);


/*
 *  ======== VIDDEC_control ========
 */
/**
 *  @brief      Execute the "control" method in this instance of a video
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
 *  @retval     #VIDDEC_EOK         Success.
 *  @retval     #VIDDEC_EFAIL       Failure.
 *  @retval     #VIDDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         VIDDEC_create()
 *  @sa         VIDDEC_delete()
 *  @sa         IVIDDEC_Fxns::control()
 */
extern Int32 VIDDEC_control(VIDDEC_Handle handle, VIDDEC_Cmd id,
        VIDDEC_DynamicParams *params, VIDDEC_Status *status);


/*
 *  ======== VIDDEC_delete ========
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
 *  @post       All resources allocated as part of the VIDDEC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         VIDDEC_create()
 */
extern Void VIDDEC_delete(VIDDEC_Handle handle);


/*
 *  ======== VIDDEC_processAsync ========
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
 *  @retval     #VIDDEC_EOK         Success.
 *  @retval     #VIDDEC_EFAIL       Failure.
 *  @retval     #VIDDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              VIDDEC_processWait() API.
 *
 *  @remark     The buffers supplied to VIDDEC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDDEC_create()
 *  @sa         VIDDEC_delete()
 *  @sa         VIDDEC_control()
 *  @sa         VIDDEC_process()
 *  @sa         VIDDEC_processWait()
 *  @sa         IVIDDEC_Fxns::process()
 */
extern XDAS_Int32 VIDDEC_processAsync(VIDDEC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, VIDDEC_InArgs *inArgs, VIDDEC_OutArgs *outArgs);


/*
 *  ======== VIDDEC_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              VIDDEC_processAsync() in this instance of an video decoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> VIDDEC_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) video decoder handle
 *              and the video decoder is in the created state.
 *
 *  @retval     #VIDDEC_EOK         Success.
 *  @retval     #VIDDEC_EFAIL       Failure.
 *  @retval     #VIDDEC_ERUNTIME    Internal Runtime Error.
 *  @retval     #VIDDEC_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of VIDDEC_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              VIDDEC_processAsync() API.
 *
 *  @remark     The buffers supplied to VIDDEC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDDEC_create()
 *  @sa         VIDDEC_delete()
 *  @sa         VIDDEC_control()
 *  @sa         VIDDEC_process()
 *  @sa         VIDDEC_processAsync()
 */
extern XDAS_Int32 VIDDEC_processWait(VIDDEC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, VIDDEC_InArgs *inArgs, VIDDEC_OutArgs *outArgs,
    UInt timeout);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.video; 1, 0, 3,408; 12-2-2010 21:28:15; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

