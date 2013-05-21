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
 * */
/**
 *  @file       itemplate.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the TEMPLATE  algorithms.
 */
/**
 *  @defgroup   ti_ires_examples_codecs_ITEMPLATE   Template Interface
 *
 */

#ifndef ti_ires_examples_codecs_ITEMPLATE_
#define ti_ires_examples_codecs_ITEMPLATE_

#include <ti/xdais/ialg.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_ires_examples_codecs_ITEMPLATE */
/*@{*/

#define ITEMPLATE_EOK      1              
#define ITEMPLATE_EFAIL    -1            
#define ITEMPLATE_EUNSUPPORTED -2 

/**
 *  @brief      This must be the first field of all ITEMPLATE
 *              instance objects.
 */
typedef struct ITEMPLATE_Obj {
    struct ITEMPLATE_Fxns *fxns;
} ITEMPLATE_Obj;


/**
 *  @brief      Opaque handle to an ITEMPLATE objects.
 */
typedef struct ITEMPLATE_Obj  *ITEMPLATE_Handle;


/**
 *  @brief      Defines the creation time parameters for
 *              all ITEMPLATE instance objects.
 *
 *  @extensibleStruct
 */
typedef struct ITEMPLATE_Params {
    Int size;
} ITEMPLATE_Params;


/**
 *  @brief      This structure defines the codec parameters that can be
 *              modified after creation via control() calls.
 *
 *  @remarks    It is not necessary that a given implementation support all
 *              dynamic parameters to be configurable at run time.  If a
 *              particular algorithm does not support run-time updates to
 *              a parameter that the application is attempting to change
 *              at runtime, it may indicate this as an error.
 *
 *  @extensibleStruct
 *
 *  @sa         ITEMPLATE_Fxns::control()
 */
typedef struct ITEMPLATE_DynamicParams {
    Int size;
} ITEMPLATE_DynamicParams;


/**
 *  @brief      Defines the input arguments for all ITEMPLATE instance
 *              process function.
 *
 *  @extensibleStruct
 *
 *  @sa         ITEMPLATE_Fxns::process()
 */
typedef struct ITEMPLATE_InArgs {
    Int size;
} ITEMPLATE_InArgs;


/**
 *  @brief      Defines instance status parameters (read-only).
 *
 *  @extensibleStruct
 *
 *  @sa         ITEMPLATE_Fxns::control()
 */
typedef struct ITEMPLATE_Status {
    Int status;
} ITEMPLATE_Status;


/**
 *  @brief      Defines the run time output arguments for
 *              all ITEMPLATE instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         ITEMPLATE_Fxns::process()
 */
typedef struct ITEMPLATE_OutArgs {
    Int size;
} ITEMPLATE_OutArgs;


/**
 *  @brief      Defines the control commands for the ITEMPLATE module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         ITEMPLATE_Fxns::control()
 */
typedef  IALG_Cmd ITEMPLATE_Cmd;


/**
 *  @brief      Defines all of the operations on ITEMPLATE objects.
 */
typedef struct ITEMPLATE_Fxns{
    IALG_Fxns   ialg;             /**< xDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

/**
 *  @brief      Basic algorithm processing call 
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *                              may modify the output buffer pointers.
 *  @param[in]  inArgs          Input arguments.  This is a required
 *                              parameter.
 *  @param[out] outArgs         Ouput results.  This is a required parameter.
 *
 *  @remarks    process() is a blocking call.  When process() returns, the
 *              algorithm's processing is complete.
 *
 *  @pre        @c handle must be a valid algorithm instance handle.
 *
 *  @pre        @c inArgs must not be NULL, and must point to a valid
 *              ITEMPLATE_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              ITEMPLATE_OutArgs structure.

 *  @post       The algorithm <b>must not</b> modify the contents of @c inArgs.
 *
 *
 *  @retval     ITEMPLATE_EOK            @copydoc ITEMPLATE_EOK
 *  @retval     ITEMPLATE_EFAIL          @copydoc ITEMPLATE_EFAIL
 *                                      See ITEMPLATE_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     ITEMPLATE_EUNSUPPORTED   @copydoc ITEMPLATE_EUNSUPPORTED
 */
    Int (*process)(ITEMPLATE_Handle handle, ITEMPLATE_InArgs *inArgs,
        ITEMPLATE_OutArgs *outArgs);


/**
 *  @brief      Control behaviour of an algorithm.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in]  id              Command id.  See #XDM_CmdId.
 *  @param[in]  params          Dynamic parameters.  This is a required
 *                              parameter.
 *  @param[out] status          Output results.  This is a required parameter.
 *
 *  @pre        @c handle must be a valid algorithm instance handle.
 *
 *  @pre        @c params must not be NULL, and must point to a valid
 *              ITEMPLATE_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              ITEMPLATE_Status structure.
 *
 *  @pre        If a buffer is provided in the @c status->data field,
 *              it must be physically contiguous and owned by the calling
 *              application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c params.
 *              That is, the data pointed to by this parameter must be
 *              treated as read-only.
 *
 *  @post       If a buffer was provided in the @c status->data field,
 *              it is owned by the calling application.
 *
 *  @retval     ITEMPLATE_EOK            @copydoc ITEMPLATE_EOK
 *  @retval     ITEMPLATE_EFAIL          @copydoc ITEMPLATE_EFAIL
 *                                      See ITEMPLATE_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     ITEMPLATE_EUNSUPPORTED   @copydoc ITEMPLATE_EUNSUPPORTED
 */
    Int   (*control)(ITEMPLATE_Handle handle, ITEMPLATE_Cmd id,
        ITEMPLATE_DynamicParams *params, ITEMPLATE_Status *status);

} ITEMPLATE_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_ires_examples_codecs_ITEMPLATE_ */
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.template; 1, 0, 0,170; 12-1-2010 17:25:09; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

