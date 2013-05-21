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
 *  @file       ti/sdo/ce/vidtranscode/vidtranscode.h
 *
 *  @brief      The video transcoder codec interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM video transcoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_vidtranscode_VIDTRANSCODE    Video Transcoder Codec Interface
 *
 *  This is the video transcoder codec interface.  Several of the data
 *  types in this API are specified by the XDM interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_vidtranscode_VIDTRANSCODE_
#define ti_sdo_ce_vidtranscode_VIDTRANSCODE_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ividtranscode.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_vidtranscode_VIDTRANSCODE */
/*@{*/

/** @copydoc IVIDTRANSCODE_EOK */
#define VIDTRANSCODE_EOK            IVIDTRANSCODE_EOK

/** @copydoc IVIDTRANSCODE_EFAIL */
#define VIDTRANSCODE_EFAIL          IVIDTRANSCODE_EFAIL

/** @copydoc IVIDTRANSCODE_EUNSUPPORTED */
#define VIDTRANSCODE_EUNSUPPORTED   IVIDTRANSCODE_EUNSUPPORTED

/**< @copydoc VISA_ETIMEOUT */
#define VIDTRANSCODE_ETIMEOUT VISA_ETIMEOUT

/**< @copydoc VISA_FOREVER */
#define VIDTRANSCODE_FOREVER  VISA_FOREVER


/**
 *  @brief      Opaque handle to a VIDTRANSCODE codec.
 */
typedef VISA_Handle VIDTRANSCODE_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a video transcoder.
 */
typedef struct IVIDTRANSCODE_Params VIDTRANSCODE_Params;

/** @copydoc IVIDTRANSCODE_InArgs */
typedef IVIDTRANSCODE_InArgs  VIDTRANSCODE_InArgs;
/** @copydoc IVIDTRANSCODE_OutArgs */
typedef IVIDTRANSCODE_OutArgs VIDTRANSCODE_OutArgs;
/** @copydoc IVIDTRANSCODE_Cmd */
typedef IVIDTRANSCODE_Cmd     VIDTRANSCODE_Cmd;
/** @copydoc IVIDTRANSCODE_Status */
typedef IVIDTRANSCODE_Status  VIDTRANSCODE_Status;

/** @copydoc IVIDTRANSCODE_DynamicParams */
typedef IVIDTRANSCODE_DynamicParams VIDTRANSCODE_DynamicParams;


/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns VIDTRANSCODE_SKEL;

/**
 *  @brief      Implementation of the IVIDTRANSCODE interface that is run
 *              remotely.
 */
extern IVIDTRANSCODE_Fxns VIDTRANSCODE_STUBS;

/** @endcond */


/*
 *  ======== VIDTRANSCODE_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of a video
 *              transcoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video transcoder instance.
 *  @param[in]  id      Command id for XDM control operation.
 *  @param[in]  params  Runtime control parameters used for the video
 *                      transcoder.
 *  @param[out] status  Status info returned by the video transcoder instance.
 *
 *  @pre        @c handle is a valid (non-NULL) video transcoder handle
 *              and the video transcoder is in the created state.
 *
 *  @retval     #VIDTRANSCODE_EOK           Success.
 *  @retval     #VIDTRANSCODE_EFAIL         Failure.
 *  @retval     #VIDTRANSCODE_EUNSUPPORTED  Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         VIDTRANSCODE_create()
 *  @sa         VIDTRANSCODE_delete()
 *  @sa         IVIDTRANSCODE_Fxns::control()
 */
extern Int32 VIDTRANSCODE_control(VIDTRANSCODE_Handle handle,
    VIDTRANSCODE_Cmd id, VIDTRANSCODE_DynamicParams *params,
    VIDTRANSCODE_Status *status);


/*
 *  ======== VIDTRANSCODE_create ========
 */
/**
 *  @brief      Create an instance of a video transcoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via VIDTRANSCODE_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of video transcoder.
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created video transcoder
 *                              instance.
 *
 *  @remarks    @c params is optional.  If it's not supplied, codec-specific
 *              default params will be used.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the video
 *              transcoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         VIDTRANSCODE_delete()
 */
extern VIDTRANSCODE_Handle VIDTRANSCODE_create(Engine_Handle e, String name,
    VIDTRANSCODE_Params *params);


/*
 *  ======== VIDTRANSCODE_delete ========
 */
/**
 *  @brief      Delete the instance of a video transcoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video transcoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the video
 *              transcoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the VIDTRANSCODE_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         VIDTRANSCODE_create()
 */
extern Void VIDTRANSCODE_delete(VIDTRANSCODE_Handle handle);


/*
 *  ======== VIDTRANSCODE_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a video
 *              transcoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video transcoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) video transcoder handle
 *              and the video transcoder is in the created state.
 *
 *  @retval     #VIDTRANSCODE_EOK           Success.
 *  @retval     #VIDTRANSCODE_EFAIL         Failure.
 *  @retval     #VIDTRANSCODE_EUNSUPPORTED  Unsupported request.
 *
 *  @remark     Since the VIDTRANSCODE transcoder contains support for
 *              asynchronous buffer submission and retrieval, this API
 *              becomes known as synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to VIDTRANSCODE_process() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDTRANSCODE_create()
 *  @sa         VIDTRANSCODE_delete()
 *  @sa         VIDTRANSCODE_control()
 *  @sa         VIDTRANSCODE_processAsync()
 *  @sa         VIDTRANSCODE_processWait()
 *  @sa         IVIDTRANSCODE_Fxns::process()
 */
extern Int32 VIDTRANSCODE_process(VIDTRANSCODE_Handle handle,
    XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDTRANSCODE_InArgs *inArgs,
    VIDTRANSCODE_OutArgs *outArgs);

/*
 *  ======== VIDTRANSCODE_processAsync ========
 */
/**
 *  @brief      Perform asynchronous submission to this instance of a video
 *              transcoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video transcoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) video transcoder handle
 *              and the video transcoder is in the created state.
 *
 *  @retval     #VIDTRANSCODE_EOK         Success.
 *  @retval     #VIDTRANSCODE_EFAIL       Failure.
 *  @retval     #VIDTRANSCODE_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              VIDTRANSCODE_processWait() API.
 *
 *  @remark     The buffers supplied to VIDTRANSCODE_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDTRANSCODE_create()
 *  @sa         VIDTRANSCODE_delete()
 *  @sa         VIDTRANSCODE_control()
 *  @sa         VIDTRANSCODE_process()
 *  @sa         VIDTRANSCODE_processWait()
 *  @sa         IVIDTRANSCODE_Fxns::process()
 */
extern XDAS_Int32 VIDTRANSCODE_processAsync(VIDTRANSCODE_Handle handle,
    XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDTRANSCODE_InArgs *inArgs,
    IVIDTRANSCODE_OutArgs *outArgs);

/*
 *  ======== VIDTRANSCODE_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              VIDTRANSCODE_processAsync() in this instance of an video
 *              transcoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video transcoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> VIDTRANSCODE_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) video transcoder handle
 *              and the video transcoder is in the created state.
 *
 *  @retval     #VIDTRANSCODE_EOK         Success.
 *  @retval     #VIDTRANSCODE_EFAIL       Failure.
 *  @retval     #VIDTRANSCODE_EUNSUPPORTED Unsupported request.
 *  @retval     #VIDTRANSCODE_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of
 *              VIDTRANSCODE_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              VIDTRANSCODE_processAsync() API.
 *
 *  @remark     The buffers supplied to VIDTRANSCODE_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDTRANSCODE_create()
 *  @sa         VIDTRANSCODE_delete()
 *  @sa         VIDTRANSCODE_control()
 *  @sa         VIDTRANSCODE_process()
 *  @sa         VIDTRANSCODE_processAsync()
 */
extern XDAS_Int32 VIDTRANSCODE_processWait(VIDTRANSCODE_Handle handle,
    XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDTRANSCODE_InArgs *inArgs,
    IVIDTRANSCODE_OutArgs *outArgs, UInt timeout);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.vidtranscode; 1, 0, 1,227; 12-2-2010 21:28:34; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

