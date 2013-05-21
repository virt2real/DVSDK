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
 *  ======== imgenc1.h ========
 */

/**
 *  @file       ti/sdo/ce/image1/imgenc1.h
 *
 *  @brief      The IMGENC1 image encoder codec interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM IIMGENC1 image encoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_image1_IMGENC1    Image encoder codec interface
 *
 *  This is the IMGENC1 image encoder codec interface.  Several of the data
 *  types in this API are specified by the XDM IIMGENC1 interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_image1_IMGENC1_
#define ti_sdo_ce_image1_IMGENC1_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/iimgenc1.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_image1_IMGENC1 */
/*@{*/

#define IMGENC1_EOK      IIMGENC1_EOK         /**< @copydoc IIMGENC1_EOK */
#define IMGENC1_EFAIL    IIMGENC1_EFAIL       /**< @copydoc IIMGENC1_EFAIL */

/** @copydoc IIMGENC1_EUNSUPPORTED */
#define IMGENC1_EUNSUPPORTED IIMGENC1_EUNSUPPORTED

#define IMGENC1_ETIMEOUT VISA_ETIMEOUT        /**< @copydoc VISA_ETIMEOUT */
#define IMGENC1_FOREVER  VISA_FOREVER         /**< @copydoc VISA_FOREVER */

/**
 *  @brief      Opaque handle to a IMGENC1 codec.
 */
typedef VISA_Handle IMGENC1_Handle;

/* The following are just wrapper typedefs */

/** @copydoc IIMGENC1_Params */
typedef struct IIMGENC1_Params IMGENC1_Params;

/** @copydoc IIMGENC1_InArgs */
typedef IIMGENC1_InArgs  IMGENC1_InArgs;

/** @copydoc IIMGENC1_OutArgs */
typedef IIMGENC1_OutArgs IMGENC1_OutArgs;

/** @copydoc IIMGENC1_Cmd */
typedef IIMGENC1_Cmd     IMGENC1_Cmd;

/** @copydoc IIMGENC1_DynamicParams */
typedef IIMGENC1_DynamicParams IMGENC1_DynamicParams;

/**< @copydoc IIMGENC1_Status */
typedef IIMGENC1_Status  IMGENC1_Status;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns IMGENC1_SKEL;

/**
 *  @brief      Implementation of the IIMGENC1 interface that is run remotely.
 */
extern IIMGENC1_Fxns IMGENC1_STUBS;

/** @endcond */

/**
 *  @brief      Definition of IIMGENC1 codec class configurable parameters
 */
typedef struct IIMGENC1_CodecClassConfig {
    Bool manageInBufsCache [ XDM_MAX_IO_BUFFERS ];
    Bool manageOutBufsCache[ XDM_MAX_IO_BUFFERS ];
} IIMGENC1_CodecClassConfig;


/*
 *  ======== IMGENC1_control ========
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
 *  @retval     #IMGENC1_EOK         Success.
 *  @retval     #IMGENC1_EFAIL       Failure.
 *  @retval     #IMGENC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         IMGENC1_create()
 *  @sa         IMGENC1_delete()
 *  @sa         IIMGENC1_Fxns::control()
 */
extern Int32 IMGENC1_control(IMGENC1_Handle handle, IMGENC1_Cmd id,
    IMGENC1_DynamicParams *params, IMGENC1_Status *status);


/*
 *  ======== IMGENC1_create ========
 */
/**
 *  @brief      Create an instance of an image encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via IMGENC1_create()) or
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
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         IMGENC1_delete()
 */
extern IMGENC1_Handle IMGENC1_create(Engine_Handle e, String name,
    IMGENC1_Params *params);


/*
 *  ======== IMGENC1_delete ========
 */
/**
 *  @brief      Delete the instance of a image encoder algorithm.
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
 *  @post       All resources allocated as part of the IMGENC1_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         IMGENC1_create()
 */
extern Void IMGENC1_delete(IMGENC1_Handle handle);


/*
 *  ======== IMGENC1_process ========
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
 *  @retval     #IMGENC1_EOK         Success.
 *  @retval     #IMGENC1_EFAIL       Failure.
 *  @retval     #IMGENC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     Since the IMGENC1 encoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to IMGENC1_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         IMGENC1_create()
 *  @sa         IMGENC1_delete()
 *  @sa         IMGENC1_control()
 *  @sa         IMGENC1_processAsync()
 *  @sa         IMGENC1_processWait()
 *  @sa         IIMGENC1_Fxns::process()
 */
extern Int32 IMGENC1_process(IMGENC1_Handle handle, XDM1_BufDesc *inBufs,
    XDM1_BufDesc *outBufs, IMGENC1_InArgs *inArgs, IMGENC1_OutArgs *outArgs);


/*
 *  ======== IMGENC1_processAsync ========
 */
/**
 *  @brief      Perform asynchronous submission to this instance of a image
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
 *  @retval     #IMGENC1_EOK         Success.
 *  @retval     #IMGENC1_EFAIL       Failure.
 *  @retval     #IMGENC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              IMGENC1_processWait() API.
 *
 *  @remark     The buffers supplied to IMGENC1_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         IMGENC1_create()
 *  @sa         IMGENC1_delete()
 *  @sa         IMGENC1_control()
 *  @sa         IMGENC1_process()
 *  @sa         IMGENC1_processWait()
 *  @sa         IIMGENC1_Fxns::process()
 */
extern XDAS_Int32 IMGENC1_processAsync(IMGENC1_Handle handle,
    XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs,
    IIMGENC1_InArgs *inArgs, IIMGENC1_OutArgs *outArgs);

/*
 *  ======== IMGENC1_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              IMGENC1_processAsync() in this instance of an image encoder
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created image encoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> IMGENC1_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) image encoder handle
 *              and the image encoder is in the created state.
 *
 *  @retval     #IMGENC1_EOK         Success.
 *  @retval     #IMGENC1_EFAIL       Failure.
 *  @retval     #IMGENC1_EUNSUPPORTED Unsupported request.
 *  @retval     #IMGENC1_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of IMGENC1_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              IMGENC1_processAsync() API.
 *
 *  @remark     The buffers supplied to IMGENC1_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         IMGENC1_create()
 *  @sa         IMGENC1_delete()
 *  @sa         IMGENC1_control()
 *  @sa         IMGENC1_process()
 *  @sa         IMGENC1_processAsync()
 */
extern XDAS_Int32 IMGENC1_processWait(IMGENC1_Handle handle,
    XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs,
    IIMGENC1_InArgs *inArgs, IIMGENC1_OutArgs *outArgs, UInt timeout);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.image1; 1, 0, 1,276; 12-2-2010 21:24:04; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

