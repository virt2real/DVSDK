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
 *  ======== imgdec1.h ========
 */

/**
 *  @file       ti/sdo/ce/image1/imgdec1.h
 *
 *  @brief      The IMGDEC1 image decoder codec interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM IIMGDEC1 image decoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_image1_IMGDEC1  Image decoder codec interface
 *
 *  This is the IMGDEC1 image decoder codec interface.  Several of the data
 *  types in this API are specified by the XDM IIMGDEC1 interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_image1_IMGDEC1_
#define ti_sdo_ce_image1_IMGDEC1_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/iimgdec1.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_image1_IMGDEC1 */
/*@{*/

#define IMGDEC1_EOK      IIMGDEC1_EOK         /**< @copydoc IIMGDEC1_EOK */
#define IMGDEC1_EFAIL    IIMGDEC1_EFAIL       /**< @copydoc IIMGDEC1_EFAIL */

/** @copydoc IIMGDEC1_EUNSUPPORTED */
#define IMGDEC1_EUNSUPPORTED IIMGDEC1_EUNSUPPORTED

#define IMGDEC1_ETIMEOUT VISA_ETIMEOUT        /**< @copydoc VISA_ETIMEOUT */
#define IMGDEC1_FOREVER  VISA_FOREVER         /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a IMGDEC1 codec.
 */
typedef VISA_Handle IMGDEC1_Handle;

/* The following are just wrapper typedefs */

/** @copydoc IIMGDEC1_Params */
typedef IIMGDEC1_Params IMGDEC1_Params;

/** @copydoc IIMGDEC1_InArgs */
typedef IIMGDEC1_InArgs  IMGDEC1_InArgs;

/** @copydoc IIMGDEC1_OutArgs */
typedef IIMGDEC1_OutArgs IMGDEC1_OutArgs;

/** @copydoc IIMGDEC1_Cmd */
typedef IIMGDEC1_Cmd     IMGDEC1_Cmd;

/** @copydoc IIMGDEC1_DynamicParams */
typedef IIMGDEC1_DynamicParams IMGDEC1_DynamicParams;

/** @copydoc IIMGDEC1_Status */
typedef IIMGDEC1_Status  IMGDEC1_Status;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns IMGDEC1_SKEL;

/**
 *  @brief      Implementation of the IIMGDEC1 interface that is run remotely.
 */
extern IIMGDEC1_Fxns IMGDEC1_STUBS;

/** @endcond */

/**
 *  @brief      Definition of IIMGDEC1 codec class configurable parameters
 */
typedef struct IIMGDEC1_CodecClassConfig {
    Bool manageInBufsCache [ XDM_MAX_IO_BUFFERS ];
    Bool manageOutBufsCache[ XDM_MAX_IO_BUFFERS ];
} IIMGDEC1_CodecClassConfig;


/*
 *  ======== IMGDEC1_control ========
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
 *  @retval     #IMGDEC1_EOK         Success.
 *  @retval     #IMGDEC1_EFAIL       Failure.
 *  @retval     #IMGDEC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         IMGDEC1_create()
 *  @sa         IMGDEC1_delete()
 *  @sa         IIMGDEC1_Fxns()::control()
 */
extern Int32 IMGDEC1_control(IMGDEC1_Handle handle, IMGDEC1_Cmd id,
    IMGDEC1_DynamicParams *params, IMGDEC1_Status *status);


/*
 *  ======== IMGDEC1_create ========
 */
/**
 *  @brief      Create an instance of an image decoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via IMGDEC1_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of image decoder
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
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         IMGDEC1_delete()
 */
extern IMGDEC1_Handle IMGDEC1_create(Engine_Handle e, String name,
    IMGDEC1_Params *params);


/*
 *  ======== IMGDEC1_delete ========
 */
/**
 *  @brief      Delete the instance of an image decoder algorithm.
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
 *  @post       All resources allocated as part of the IMGDEC1_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         IMGDEC1_create()
 */
extern Void IMGDEC1_delete(IMGDEC1_Handle handle);


/*
 *  ======== IMGDEC1_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of an image
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
 *  @retval     #IMGDEC1_EOK         Success.
 *  @retval     #IMGDEC1_EFAIL       Failure.
 *  @retval     #IMGDEC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     Since the IMGDEC1 decoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to IMGDEC1_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         IMGDEC1_create()
 *  @sa         IMGDEC1_delete()
 *  @sa         IMGDEC1_control()
 *  @sa         IMGDEC1_processAsync()
 *  @sa         IMGDEC1_processWait()
 *  @sa         IIMGDEC1_Fxns()::process()
 */
extern Int32 IMGDEC1_process(IMGDEC1_Handle handle, XDM1_BufDesc *inBufs,
    XDM1_BufDesc *outBufs, IMGDEC1_InArgs *inArgs, IMGDEC1_OutArgs *outArgs);


/*
 *  ======== IMGDEC1_processAsync ========
 */
/**
 *  @brief      Perform asynchronous submission to this instance of a image
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
 *  @retval     #IMGDEC1_EOK         Success.
 *  @retval     #IMGDEC1_EFAIL       Failure.
 *  @retval     #IMGDEC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              IMGDEC1_processWait() API.
 *
 *  @remark     The buffers supplied to IMGDEC1_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         IMGDEC1_create()
 *  @sa         IMGDEC1_delete()
 *  @sa         IMGDEC1_control()
 *  @sa         IMGDEC1_process()
 *  @sa         IMGDEC1_processWait()
 *  @sa         IIMGDEC1_Fxns::process()
 */
extern XDAS_Int32 IMGDEC1_processAsync(IMGDEC1_Handle handle,
    XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs,
    IMGDEC1_InArgs *inArgs, IMGDEC1_OutArgs *outArgs);

/*
 *  ======== IMGDEC1_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              IMGDEC1_processAsync() in this instance of an image decoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created image decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> IMGDEC1_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) image decoder handle
 *              and the image decoder is in the created state.
 *
 *  @retval     #IMGDEC1_EOK         Success.
 *  @retval     #IMGDEC1_EFAIL       Failure.
 *  @retval     #IMGDEC1_EUNSUPPORTED Unsupported request.
 *  @retval     #IMGDEC1_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of IMGDEC1_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              IMGDEC1_processAsync() API.
 *
 *  @remark     The buffers supplied to IMGDEC1_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         IMGDEC1_create()
 *  @sa         IMGDEC1_delete()
 *  @sa         IMGDEC1_control()
 *  @sa         IMGDEC1_process()
 *  @sa         IMGDEC1_processAsync()
 */
extern XDAS_Int32 IMGDEC1_processWait(IMGDEC1_Handle handle,
    XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs,
    IMGDEC1_InArgs *inArgs, IMGDEC1_OutArgs *outArgs, UInt timeout);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.image1; 1, 0, 1,276; 12-2-2010 21:24:03; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

