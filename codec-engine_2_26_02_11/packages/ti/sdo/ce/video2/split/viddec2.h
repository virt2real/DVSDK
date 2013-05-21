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
 *  ======== viddec2.h ========
 */
/**
 *  @file       ti/sdo/ce/video2/split/viddec2.h
 *
 *  @brief      The VIDDEC2 split video decoder codec interface.  Provides
 *              the user an interface to create and interact with XDAIS
 *              algorithms that are compliant with the XDM IVIDDEC2FRONT or
 *              IVIDDEC2BACK video decoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_video2_split_VIDDEC2   Split video decoder interface
 *
 *  This is the split VIDDEC2 video decoder codec interface.  Several
 *  of the data types in this API are specified by the XDM interface;
 *  please see the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_video2_split_VIDDEC2_
#define ti_sdo_ce_video2_split_VIDDEC2_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/split/ividdec2.h>


#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>
#include <ti/sdo/ce/video2/viddec2.h>

/** @ingroup    ti_sdo_ce_video2_split_VIDDEC2 */
/*@{*/

/**
 *  @copydoc IVIDDEC2_Status
 */
typedef IVIDDEC2FRONT_Status VIDDEC2FRONT_Status;


/**
 *  @brief      Opaque handle to a VIDDEC2FRONT codec.
 */
typedef VISA_Handle VIDDEC2FRONT_Handle;


/**
 *  @brief      Opaque handle to a VIDDEC2BACK codec.
 */
typedef VISA_Handle VIDDEC2BACK_Handle;


/**
 * @copydoc IVIDDEC2FRONT_OutArgs
 */
typedef IVIDDEC2FRONT_OutArgs    VIDDEC2FRONT_OutArgs;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns VIDDEC2FRONT_SKEL;

/**
 *  @brief      Implementation of the IVIDDEC2FRONT interface that is
 *              run remotely.
 */
extern IVIDDEC2FRONT_Fxns VIDDEC2FRONT_STUBS;

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns VIDDEC2BACK_SKEL;

/**
 *  @brief      Implementation of the IVIDDEC2BACK interface that is
 *              run remotely.
 */
extern IVIDDEC2BACK_Fxns VIDDEC2BACK_STUBS;

/** @endcond */

/**
 *  @brief      Definition of IVIDDEC2BACK codec class configurable parameters
 */
typedef struct IVIDDEC2BACK_CodecClassConfig {
    Bool manageInBufsCache          [ XDM_MAX_CONTEXT_BUFFERS ];
    Bool manageOutBufsCache         [ XDM_MAX_CONTEXT_BUFFERS ];
    Bool manageIntermediateBufsCache[ XDM_MAX_CONTEXT_BUFFERS ];
} IVIDDEC2BACK_CodecClassConfig;

/*
 *  ======== VIDDEC2BACK_create ========
 */
/**
 *  @brief      Create an instance of the BACK end of a split video decoder
 *              algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via VIDDEC2BACK_create) or
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
extern VIDDEC2BACK_Handle VIDDEC2BACK_create(Engine_Handle e, String name,
    VIDDEC2_Params *params);


/*
 *  ======== VIDDEC2BACK_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a BACK side
 *              split video decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *  @param[in,out] context Context provided to, and managed by, the split codec.
 *  @param[out] outArgs Output results.  This is a required parameter
 *
 *  @pre        @c handle is a valid (non-NULL) video decoder handle
 *              and the video decoder is in the created state.
 *
 *  @retval     #VIDDEC2_EOK         Success.
 *  @retval     #VIDDEC2_EFAIL       Failure.
 *
 *  @remark     Since the VIDDEC2BACK decoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to VIDDEC2BACK_process() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDDEC2BACK_create()
 *  @sa         VIDDEC2BACK_delete()
 *  @sa         VIDDEC2BACK_control()
 *  @sa         VIDDEC2BACK_processAsync()
 *  @sa         VIDDEC2BACK_processWait()
 *  @sa         IVIDDEC2BACK_Fxns::process()
 *  @sa         VIDDEC2FRONT_create()
 *  @sa         VIDDEC2FRONT_delete()
 *  @sa         VIDDEC2FRONT_control()
 *  @sa         IVIDDEC2FRONT_Fxns::process()
 */
extern Int32 VIDDEC2BACK_process(VIDDEC2BACK_Handle handle,
        XDM_Context *context, VIDDEC2_OutArgs *outArgs);


/*
 *  ======== VIDDEC2BACK_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of a video
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *  @param[in,out] context Context provided to, and managed by, the split codec.
 *  @param[out] status  Status info upon completion of decode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) video decoder handle
 *              and the video decoder is in the created state.
 *
 *  @retval     #VIDDEC2_EOK         Success.
 *  @retval     #VIDDEC2_EFAIL       Failure.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         VIDDEC2FRONT_create()
 *  @sa         VIDDEC2FRONT_delete()
 *  @sa         IVIDDEC2FRONT_Fxns::process()
 *  @sa         VIDDEC2BACK_create()
 *  @sa         VIDDEC2BACK_delete()
 *  @sa         IVIDDEC2BACK_Fxns::process()
 */
extern Int32 VIDDEC2BACK_control(VIDDEC2BACK_Handle handle,
        XDM_Context *context, VIDDEC2_Status *status);

/*
 *  ======== VIDDEC2BACK_delete ========
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
 *  @post       All resources allocated as part of the VIDDEC2BACK_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         VIDDEC2BACK_create()
 */
extern Void VIDDEC2BACK_delete(VIDDEC2BACK_Handle handle);


/*
 *  ======== VIDDEC2FRONT_create ========
 */
/**
 *  @brief      Create an instance of the FRONT end of a split video decoder
 *              algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via VIDDEC2FRONT_create) or
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
extern VIDDEC2FRONT_Handle VIDDEC2FRONT_create(Engine_Handle e, String name,
    VIDDEC2_Params *params);


/*
 *  ======== VIDDEC2FRONT_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a FRONT side
 *              split video decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[in,out] context Context provided to, and managed by, the split codec.
 *  @param[out] outArgs Output results.  This is a required parameter
 *
 *  @pre        @c handle is a valid (non-NULL) video decoder handle
 *              and the video decoder is in the created state.
 *
 *  @retval     #VIDDEC2_EOK         Success.
 *  @retval     #VIDDEC2_EFAIL       Failure.
 *
 *  @remark     Since the VIDDEC2FRONT decoder contains support for asynchronous
 *              buffer submission and retrieval, this API becomes known as
 *              synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to VIDDEC2FRONT_process() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         VIDDEC2FRONT_create()
 *  @sa         VIDDEC2FRONT_delete()
 *  @sa         VIDDEC2FRONT_control()
 *  @sa         IVIDDEC2FRONT_Fxns::process()
 *  @sa         VIDDEC2BACK_create()
 *  @sa         VIDDEC2BACK_delete()
 *  @sa         VIDDEC2BACK_control()
 *  @sa         VIDDEC2BACK_processAsync()
 *  @sa         VIDDEC2BACK_processWait()
 *  @sa         IVIDDEC2BACK_Fxns::process()
 */
extern Int32 VIDDEC2FRONT_process(VIDDEC2FRONT_Handle handle,
        VIDDEC2_InArgs *inArgs, XDM_Context *context,
        VIDDEC2FRONT_OutArgs *outArgs);


/*
 *  ======== VIDDEC2FRONT_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of a video
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *  @param[in]  id      Command id for XDM control operation.
 *  @param[in]  params  Runtime control parameters used for decoding.
 *  @param[in,out] context Context provided to, and managed by, the split codec.
 *  @param[out] status  Status info upon completion of decode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) video decoder handle
 *              and the video decoder is in the created state.
 *
 *  @retval     #VIDDEC2_EOK         Success.
 *  @retval     #VIDDEC2_EFAIL       Failure.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         VIDDEC2FRONT_create()
 *  @sa         VIDDEC2FRONT_delete()
 *  @sa         IVIDDEC2FRONT_Fxns::process()
 *  @sa         VIDDEC2BACK_create()
 *  @sa         VIDDEC2BACK_delete()
 *  @sa         IVIDDEC2BACK_Fxns::process()
 */
extern Int32 VIDDEC2FRONT_control(VIDDEC2FRONT_Handle handle, VIDDEC2_Cmd id,
        VIDDEC2_DynamicParams *params, XDM_Context *context,
        VIDDEC2FRONT_Status *status);


/*
 *  ======== VIDDEC2FRONT_delete ========
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
 *  @post       All resources allocated as part of the VIDDEC2FRONT_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         VIDDEC2FRONT_create()
 */
extern Void VIDDEC2FRONT_delete(VIDDEC2FRONT_Handle handle);


/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.video2.split; 1, 0, 0,165; 12-2-2010 21:28:41; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

