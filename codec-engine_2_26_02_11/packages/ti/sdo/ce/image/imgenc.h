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
 *  ======== imgenc.h ========
 */
/**
 *  @file       ti/sdo/ce/image/imgenc.h
 *
 *  @brief      The IMGENC image encoder interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM-defined IIMGENC image encoder interface.
 */
/**
 *  @defgroup   IMGENC    IMGENC Image Encoder Interface
 *
 *  This is the IMGENC image encoder interface.  Several of the data
 *  types in this API are specified by the XDM interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_image_IMGENC_
#define ti_sdo_ce_image_IMGENC_

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
#include <ti/xdais/dm/iimgenc.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    IMGENC */
/*@{*/

typedef IIMGENC_Status IMGENC_Status;       /**< @copydoc IIMGENC_Status */

#define IMGENC_EOK      IIMGENC_EOK         /**< @copydoc IIMGENC_EOK */
#define IMGENC_EFAIL    IIMGENC_EFAIL       /**< @copydoc IIMGENC_EFAIL */
#define IMGENC_ERUNTIME IIMGENC_ERUNTIME    /**< @copydoc IIMGENC_ERUNTIME */
#define IMGENC_ETIMEOUT VISA_ETIMEOUT       /**< @copydoc VISA_ETIMEOUT */
#define IMGENC_FOREVER  VISA_FOREVER        /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a IMGENC codec.
 */
typedef VISA_Handle IMGENC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of an image encoder object.
 */
typedef struct IIMGENC_Params IMGENC_Params;

/**
 * @copydoc IIMGENC_InArgs
 */
typedef IIMGENC_InArgs          IMGENC_InArgs;

/**
 * @copydoc IIMGENC_OutArgs
 */
typedef IIMGENC_OutArgs         IMGENC_OutArgs;

/**
 * @copydoc IIMGENC_Cmd
 */
typedef IIMGENC_Cmd             IMGENC_Cmd;

/**
 * @copydoc IIMGENC_DynamicParams
 */
typedef IIMGENC_DynamicParams   IMGENC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns IMGENC_SKEL;

/**
 *  @brief      Implementation of the IIMGENC interface that is run remotely.
 */
extern IIMGENC_Fxns IMGENC_STUBS;

/** @endcond */

/**
 *  @brief      Definition of IIMGENC codec class configurable parameters
 *
 *  @sa         VISA_getCodecClassConfig()
 */
typedef struct IIMGENC_CodecClassConfig {
    Bool manageInBufsCache [ XDM_MAX_IO_BUFFERS ];
    Bool manageOutBufsCache[ XDM_MAX_IO_BUFFERS ];
} IIMGENC_CodecClassConfig;

/*
 *  ======== IMGENC_create ========
 */
/**
 *  @brief      Create an instance of an image encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via IMGENC_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of image encoder
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created image encoder
 *                              instance.
 *
 *  @remarks    @c params is optional.  If it's not supplied, codec-specific
 *              default params will be used.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the image
 *              encoder.
 *
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         IMGENC_delete()
 */
extern IMGENC_Handle IMGENC_create(Engine_Handle e, String name,
        IMGENC_Params *params);


/*
 *  ======== IMGENC_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of an image
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image encoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) image encoder handle
 *              and the image encoder is in the created state.
 *
 *  @retval     #IMGENC_EOK         Success.
 *  @retval     #IMGENC_EFAIL       Failure.
 *  @retval     #IMGENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     Since the IMGENC encoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to IMGENC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @remark     If an error is returned, @c outArgs->extendedError may
 *              indicate further details about the error.  See
 *              #IMGENC_OutArgs::extendedError for details.
 *
 *  @sa         IMGENC_create()
 *  @sa         IMGENC_delete()
 *  @sa         IMGENC_control()
 *  @sa         IMGENC_processAsync()
 *  @sa         IMGENC_processWait()
 *  @sa         IIMGENC_Fxns::process()  - the reflected algorithm interface,
 *                                         which may contain further usage
 *                                         details.
 */
extern Int32 IMGENC_process(IMGENC_Handle handle,
        XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
        IMGENC_InArgs *inArgs, IMGENC_OutArgs *outArgs);


/*
 *  ======== IMGENC_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of an image
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image encoder instance.
 *  @param[in]  id      Command id for XDM control operation.
 *  @param[in]  params  Runtime control parameters used for encoding.
 *  @param[out] status  Status info upon completion of encode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) image encoder handle
 *              and the image encoder is in the created state.
 *
 *  @retval     #IMGENC_EOK         Success.
 *  @retval     #IMGENC_EFAIL       Failure.
 *  @retval     #IMGENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @remark     If an error is returned, @c status->extendedError may
 *              indicate further details about the error.  See
 *              #IMGENC_Status::extendedError for details.
 *
 *  @sa         IMGENC_create()
 *  @sa         IMGENC_delete()
 *  @sa         IIMGENC_Fxns::control()  - the reflected algorithm interface,
 *                                         which may contain further usage
 *                                         details.
 */
extern Int32 IMGENC_control(IMGENC_Handle handle, IMGENC_Cmd id,
        IMGENC_DynamicParams *params, IMGENC_Status *status);


/*
 *  ======== IMGENC_delete ========
 */
/**
 *  @brief      Delete the instance of an image encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image encoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the image
 *              encoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the IMGENC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         IMGENC_create()
 */
extern Void IMGENC_delete(IMGENC_Handle handle);


/*
 *  ======== IMGENC_processAsync ========
 */
/**
 *  @brief      Perform asynchronous submission to this instance of an image
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image encoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) image encoder handle
 *              and the image encoder is in the created state.
 *
 *  @retval     #IMGENC_EOK         Success.
 *  @retval     #IMGENC_EFAIL       Failure.
 *  @retval     #IMGENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              IMGENC_processWait() API.
 *
 *  @remark     The buffers supplied to IMGENC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         IMGENC_create()
 *  @sa         IMGENC_delete()
 *  @sa         IMGENC_control()
 *  @sa         IMGENC_process()
 *  @sa         IMGENC_processWait()
 *  @sa         IIMGENC_Fxns::process()  - the reflected algorithm interface,
 *                                         which may contain further usage
 *                                         details.
 */
extern XDAS_Int32 IMGENC_processAsync(IMGENC_Handle handle, XDM_BufDesc *inBufs,
        XDM_BufDesc *outBufs, IIMGENC_InArgs *inArgs, IIMGENC_OutArgs *outArgs);


/*
 *  ======== IMGENC_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              IMGENC_processAsync() in this instance of an image encoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created image encoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> IMGENC_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) image encoder handle
 *              and the image encoder is in the created state.
 *
 *  @retval     #IMGENC_EOK         Success.
 *  @retval     #IMGENC_EFAIL       Failure.
 *  @retval     #IMGENC_ERUNTIME    Internal Runtime Error.
 *  @retval     #IMGENC_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of IMGENC_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              IMGENC_processAsync() API.
 *
 *  @remark     The buffers supplied to IMGENC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         IMGENC_create()
 *  @sa         IMGENC_delete()
 *  @sa         IMGENC_control()
 *  @sa         IMGENC_process()
 *  @sa         IMGENC_processAsync()
 */
extern XDAS_Int32 IMGENC_processWait(IMGENC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IIMGENC_InArgs *inArgs, IIMGENC_OutArgs *outArgs,
    UInt timeout);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.image; 1, 0, 3,352; 12-2-2010 21:23:58; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

