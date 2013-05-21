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
 *  ======== universal.h ========
 */

/**
 *  @file       ti/sdo/ce/universal/universal.h
 *
 *  @brief      The "universal" algorithm interface.  Provides the user an
 *              interface to create and interact with XDAIS algorithms that are
 *              compliant with the XDM IUNIVERSAL interface.
 */
/**
 *  @defgroup   ti_sdo_ce_universal_UNIVERSAL    Universal Algorithm Interface
 *
 *  This is the "universal" algorithm interface.  Several of the data
 *  types in this API are specified by the XDM interface; please see
 *  the XDM documentation for those details.
 */

#ifndef ti_sdo_ce_universal_UNIVERSAL_
#define ti_sdo_ce_universal_UNIVERSAL_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/iuniversal.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_universal_UNIVERSAL */
/*@{*/

/** @copydoc IUNIVERSAL_EOK */
#define UNIVERSAL_EOK            IUNIVERSAL_EOK

/** @copydoc IUNIVERSAL_EFAIL */
#define UNIVERSAL_EFAIL          IUNIVERSAL_EFAIL

/** @copydoc IUNIVERSAL_EUNSUPPORTED */
#define UNIVERSAL_EUNSUPPORTED   IUNIVERSAL_EUNSUPPORTED

/**< @copydoc VISA_ETIMEOUT */
#define UNIVERSAL_ETIMEOUT VISA_ETIMEOUT

/**< @copydoc VISA_FOREVER */
#define UNIVERSAL_FOREVER  VISA_FOREVER

/**
 *  @brief      Opaque handle to a UNIVERSAL codec.
 */
typedef VISA_Handle UNIVERSAL_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a "universal" algorithm.
 */
typedef struct IUNIVERSAL_Params UNIVERSAL_Params;

/** @copydoc IUNIVERSAL_InArgs */
typedef IUNIVERSAL_InArgs  UNIVERSAL_InArgs;
/** @copydoc IUNIVERSAL_OutArgs */
typedef IUNIVERSAL_OutArgs UNIVERSAL_OutArgs;
/** @copydoc IUNIVERSAL_Cmd */
typedef IUNIVERSAL_Cmd     UNIVERSAL_Cmd;
/** @copydoc IUNIVERSAL_Status */
typedef IUNIVERSAL_Status  UNIVERSAL_Status;

/** @copydoc IUNIVERSAL_DynamicParams */
typedef IUNIVERSAL_DynamicParams UNIVERSAL_DynamicParams;


/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns UNIVERSAL_SKEL;

/**
 *  @brief      Implementation of the IUNIVERSAL interface that is run
 *              remotely.
 */
extern IUNIVERSAL_Fxns UNIVERSAL_STUBS;

/** @endcond */


/*
 *  ======== UNIVERSAL_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of a "universal"
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created universal algorithm instance.
 *  @param[in]  id      Command id for XDM control operation.
 *  @param[in]  params  Runtime control parameters used for the universal
 *                      algorithm instance.
 *  @param[out] status  Status info returned by the algorithm instance.
 *
 *  @pre        @c handle is a valid (non-NULL) universal algorithm handle
 *              and the universal algorithm instance is in the created state.
 *
 *  @retval     #UNIVERSAL_EOK           Success.
 *  @retval     #UNIVERSAL_EFAIL         Failure.
 *  @retval     #UNIVERSAL_EUNSUPPORTED  Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         UNIVERSAL_create()
 *  @sa         UNIVERSAL_delete()
 *  @sa         IUNIVERSAL_Fxns::control()
 */
extern Int32 UNIVERSAL_control(UNIVERSAL_Handle handle,
    UNIVERSAL_Cmd id, UNIVERSAL_DynamicParams *params,
    UNIVERSAL_Status *status);


/*
 *  ======== UNIVERSAL_create ========
 */
/**
 *  @brief      Create an instance of a universal algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via UNIVERSAL_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of universal
 *                      algorithm to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created universal
 *                              algorithm instance.
 *
 *  @remarks    @c params is optional.  If it's not supplied, codec-specific
 *              default params will be used.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the universal
 *              algorithm.
 *
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         UNIVERSAL_delete()
 */
extern UNIVERSAL_Handle UNIVERSAL_create(Engine_Handle e, String name,
    UNIVERSAL_Params *params);


/*
 *  ======== UNIVERSAL_delete ========
 */
/**
 *  @brief      Delete the instance of a universal algorithm.
 *
 *  @param[in]  handle  Handle to a created universal algorithm instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the universal
 *              algorithm.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the UNIVERSAL_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         UNIVERSAL_create()
 */
extern Void UNIVERSAL_delete(UNIVERSAL_Handle handle);


/*
 *  ======== UNIVERSAL_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a universal
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created universal algorithm instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in, out] inOutBufs A buffer descriptor containing in/out buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) universal algorithm handle
 *              and the universal algorithm instance is in the
 *              created state.
 *
 *  @retval     #UNIVERSAL_EOK           Success.
 *  @retval     #UNIVERSAL_EFAIL         Failure.
 *  @retval     #UNIVERSAL_EUNSUPPORTED  Unsupported request.
 *
 *  @remark     Since the UNIVERSAL algorithm contains support for
 *              asynchronous buffer submission and retrieval, this API
 *              becomes known as synchronous in nature.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to UNIVERSAL_process() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running
 *              on a remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         UNIVERSAL_create()
 *  @sa         UNIVERSAL_delete()
 *  @sa         UNIVERSAL_control()
 *  @sa         UNIVERSAL_processAsync()
 *  @sa         UNIVERSAL_processWait()
 *  @sa         IUNIVERSAL_Fxns::process()
 */
extern Int32 UNIVERSAL_process(UNIVERSAL_Handle handle,
        XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs,
        UNIVERSAL_InArgs *inArgs, UNIVERSAL_OutArgs *outArgs);

/*
 *  ======== UNIVERSAL_processAsync ========
 */
/**
 *  @brief      Perform asynchronous submission to this instance of a universal
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created universal algorithm instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in, out] inOutBufs A buffer descriptor containing in/out buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) universal algorithm handle
 *              and the universal algorithm instance is in the
 *              created state.
 *
 *  @retval     #UNIVERSAL_EOK         Success.
 *  @retval     #UNIVERSAL_EFAIL       Failure.
 *  @retval     #UNIVERSAL_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This API is the asynchronous counterpart to the process()
 *              method.  It allows for buffer and argument submission without
 *              waiting for retrieval.  A response is retrieved using the
 *              UNIVERSAL_processWait() API.
 *
 *  @remark     The buffers supplied to UNIVERSAL_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         UNIVERSAL_create()
 *  @sa         UNIVERSAL_delete()
 *  @sa         UNIVERSAL_control()
 *  @sa         UNIVERSAL_process()
 *  @sa         UNIVERSAL_processWait()
 *  @sa         IUNIVERSAL_Fxns::process()
 */
extern XDAS_Int32 UNIVERSAL_processAsync(UNIVERSAL_Handle handle,
        XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs,
        IUNIVERSAL_InArgs *inArgs, IUNIVERSAL_OutArgs *outArgs);

/*
 *  ======== UNIVERSAL_processWait ========
 */
/**
 *  @brief      Wait for a return message from a previous invocation of
 *              UNIVERSAL_processAsync() in this instance of a universal
 *              algorithm.
 *
 *  @param[in]  handle  Handle to a created universal algorithm instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in, out] inOutBufs A buffer descriptor containing in/out buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *  @param[in]  timeout Amount of "time" to wait (from 0 -> UNIVERSAL_FOREVER)
 *
 *  @pre        @c handle is a valid (non-NULL) universal algorithm handle
 *              and the universal algorithm instance is in the
 *              created state.
 *
 *  @retval     #UNIVERSAL_EOK         Success.
 *  @retval     #UNIVERSAL_EFAIL       Failure.
 *  @retval     #UNIVERSAL_EUNSUPPORTED Unsupported request.
 *  @retval     #UNIVERSAL_ETIMEOUT    Operation timed out.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     "Polling" is supported by using a timeout of 0.  Waiting
 *              forever is supported by using a timeout of UNIVERSAL_EFOREVER.
 *
 *  @remark     There must have previously been an invocation of the
 *              UNIVERSAL_processAsync() API.
 *
 *  @remark     The buffers supplied to UNIVERSAL_processAsync() may have
 *              constraints put on them.  For example, in dual-processor,
 *              shared memory architectures, where the codec is running on a
 *              remote processor, the buffers may need to be physically
 *              contiguous.  Additionally, the remote processor may place
 *              restrictions on buffer alignment.
 *
 *  @sa         UNIVERSAL_create()
 *  @sa         UNIVERSAL_delete()
 *  @sa         UNIVERSAL_control()
 *  @sa         UNIVERSAL_process()
 *  @sa         UNIVERSAL_processAsync()
 */
extern XDAS_Int32 UNIVERSAL_processWait(UNIVERSAL_Handle handle,
        XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs,
        IUNIVERSAL_InArgs *inArgs, IUNIVERSAL_OutArgs *outArgs, UInt timeout);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.universal; 1, 0, 0,141; 12-2-2010 21:27:56; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

