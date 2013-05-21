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
 *  ======== imgdec.h ========
 */
/**
 *  @file       ti/sdo/ce/image/imgdec.h
 *
 *  @brief      The IMGDEC image decoder interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM-defined IIMGDEC image decoder interface.
 */
/**
 *  @defgroup   IMGDEC    IMGDEC Image Decoder Interface
 *
 *  This is the IMGDEC image decoder interface.  Several of the data
 *  types in this API are specified by the XDM interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_image_IMGDEC_
#define ti_sdo_ce_image_IMGDEC_

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
#include <ti/xdais/dm/iimgdec.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    IMGDEC */
/*@{*/

typedef IIMGDEC_Status IMGDEC_Status;       /**< @copydoc IIMGDEC_Status */

#define IMGDEC_EOK      IIMGDEC_EOK         /**< @copydoc IIMGDEC_EOK */
#define IMGDEC_EFAIL    IIMGDEC_EFAIL       /**< @copydoc IIMGDEC_EFAIL */
#define IMGDEC_ERUNTIME IIMGDEC_ERUNTIME    /**< @copydoc IIMGDEC_ERUNTIME */
#define IMGDEC_ETIMEOUT VISA_ETIMEOUT       /**< @copydoc VISA_ETIMEOUT */
#define IMGDEC_FOREVER  VISA_FOREVER        /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a IMGDEC codec.
 */
typedef VISA_Handle IMGDEC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a image decoder object.
 */
typedef struct IIMGDEC_Params IMGDEC_Params;

/**
 * @copydoc IIMGDEC_InArgs
 */
typedef IIMGDEC_InArgs          IMGDEC_InArgs;

/**
 * @copydoc IIMGDEC_OutArgs
 */
typedef IIMGDEC_OutArgs         IMGDEC_OutArgs;

/**
 * @copydoc IIMGDEC_Cmd
 */
typedef IIMGDEC_Cmd             IMGDEC_Cmd;

/**
 * @copydoc IIMGDEC_DynamicParams
 */
typedef IIMGDEC_DynamicParams   IMGDEC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns IMGDEC_SKEL;

/**
 *  @brief      Implementation of the IIMGDEC interface that is run remotely.
 */
extern IIMGDEC_Fxns IMGDEC_STUBS;

/** @endcond */

/**
 *  @brief      Definition of IIMGDEC codec class configurable parameters
 *
 *  @sa         VISA_getCodecClassConfig()
 */
typedef struct IIMGDEC_CodecClassConfig {
    Bool manageInBufsCache [ XDM_MAX_IO_BUFFERS ];
    Bool manageOutBufsCache[ XDM_MAX_IO_BUFFERS ];
} IIMGDEC_CodecClassConfig;

/*
 *  ======== IMGDEC_create ========
 */
/**
 *  @brief      Create an instance of an image decoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via IMGDEC_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of image decoder.
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created image decoder
 *                              instance.
 *
 *  @remarks    @c params is optional.  If it's not supplied, codec-specific
 *              default params will be used.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the image
 *              decoder.
 *
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         IMGDEC_delete()
 */
extern IMGDEC_Handle IMGDEC_create(Engine_Handle e, String name,
        IMGDEC_Params *params);


/*
 *  ======== IMGDEC_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a image
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) image decoder handle
 *              and the image decoder is in the created state.
 *
 *  @retval     #IMGDEC_EOK         Success.
 *  @retval     #IMGDEC_EFAIL       Failure.
 *  @retval     #IMGDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     Since the IMGDEC decoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to IMGDEC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @remark     If an error is returned, @c outArgs->extendedError may
 *              indicate further details about the error.  See
 *              #IMGDEC_OutArgs::extendedError for details.
 *
 *  @sa         IMGDEC_create()
 *  @sa         IMGDEC_delete()
 *  @sa         IMGDEC_control()
 *  @sa         IMGDEC_processAsync()
 *  @sa         IMGDEC_processWait()
 *  @sa         IIMGDEC_Fxns::process()  - the reflected algorithm interface,
 *                                         which may contain further usage
 *                                         details.
 */
extern Int32 IMGDEC_process(IMGDEC_Handle handle,
        XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
        IMGDEC_InArgs *inArgs, IMGDEC_OutArgs *outArgs);


/*
 *  ======== IMGDEC_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of an image
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image decoder instance.
 *  @param[in]  id      Command id for XDM control operation.
 *  @param[in]  params  Runtime control parameters used for decoding.
 *  @param[out] status  Status info upon completion of decode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) image decoder handle
 *              and the image decoder is in the created state.
 *
 *  @retval     #IMGDEC_EOK         Success.
 *  @retval     #IMGDEC_EFAIL       Failure.
 *  @retval     #IMGDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @remark     If an error is returned, @c status->extendedError may
 *              indicate further details about the error.  See
 *              #IMGDEC_Status::extendedError for details.
 *
 *  @sa         IMGDEC_create()
 *  @sa         IMGDEC_delete()
 *  @sa         IIMGDEC_Fxns::control()
 */
extern Int32 IMGDEC_control(IMGDEC_Handle handle, IMGDEC_Cmd id,
        IMGDEC_DynamicParams *params, IMGDEC_Status *status);


/*
 *  ======== IMGDEC_delete ========
 */
/**
 *  @brief      Delete the instance of a image decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image decoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the image
 *              decoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the IMGDEC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         IMGDEC_create()
 */
extern Void IMGDEC_delete(IMGDEC_Handle handle);


/*
 *  ======== IMGDEC_processAsync ========
 */
/**
 *  @brief      Perform asynchronous submission to this instance of an image
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) image decoder handle
 *              and the image decoder is in the created state.
 *
 *  @retval     #IMGDEC_EOK         Success.
 *  @retval     #IMGDEC_EFAIL       Failure.
 *  @retval     #IMGDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              IMGDEC_processWait() API.
 *
 *  @remark     The buffers supplied to IMGDEC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         IMGDEC_create()
 *  @sa         IMGDEC_delete()
 *  @sa         IMGDEC_control()
 *  @sa         IMGDEC_process()
 *  @sa         IMGDEC_processWait()
 *  @sa         IIMGDEC_Fxns::process()
 */
extern XDAS_Int32 IMGDEC_processAsync(IMGDEC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IMGDEC_InArgs *inArgs, IMGDEC_OutArgs *outArgs);


/*
 *  ======== IMGDEC_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              IMGDEC_processAsync() in this instance of an image decoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created image decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> IMGDEC_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) image decoder handle
 *              and the image decoder is in the created state.
 *
 *  @retval     #IMGDEC_EOK         Success.
 *  @retval     #IMGDEC_EFAIL       Failure.
 *  @retval     #IMGDEC_ERUNTIME    Internal Runtime Error.
 *  @retval     #IMGDEC_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of IMGDEC_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              IMGDEC_processAsync() API.
 *
 *  @remark     The buffers supplied to IMGDEC_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         IMGDEC_create()
 *  @sa         IMGDEC_delete()
 *  @sa         IMGDEC_control()
 *  @sa         IMGDEC_process()
 *  @sa         IMGDEC_processAsync()
 */
extern XDAS_Int32 IMGDEC_processWait(IMGDEC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IMGDEC_InArgs *inArgs, IMGDEC_OutArgs *outArgs,
    UInt timeout);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.image; 1, 0, 3,352; 12-2-2010 21:23:58; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

