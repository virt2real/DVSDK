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
 *  ======== scale.h ========
 *  The scale API.
 */
/**
 *  @file       ti/sdo/ce/examples/extensions/scale/scale.h
 */
#ifndef ti_sdo_ce_examples_extensions_scale_SCALE_H_
#define ti_sdo_ce_examples_extensions_scale_SCALE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/sdo/ce/examples/codecs/scale/iscale.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>
#include <ti/xdais/xdas.h>

#define SCALE_EOK      ISCALE_EOK
#define SCALE_EFAIL    ISCALE_EFAIL
#define SCALE_ERUNTIME ISCALE_ERUNTIME

/**
 *  @brief      Opaque handle to a SCALE codec.
 */
typedef VISA_Handle SCALE_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a Scale object.
 */
typedef struct ISCALE_Params SCALE_Params;

extern SCALE_Params SCALE_PARAMS;   /**< Default instance parameters. */

/**
 * @copydoc ISCALE_InArgs
 */
typedef ISCALE_InArgs           SCALE_InArgs;

/**
 * @copydoc ISCALE_OutArgs
 */
typedef ISCALE_OutArgs          SCALE_OutArgs;

/**
 * @copydoc ISCALE_Cmd
 */
typedef ISCALE_Cmd              SCALE_Cmd;

#define SCALE_SETPARAMS 0       /* only cmd we support */

/**
 * @copydoc ISCALE_DynamicParams
 */
typedef ISCALE_DynamicParams    SCALE_DynamicParams;

/** @cond INTERNAL */


extern SKEL_Fxns SCALE_SKEL;

extern ISCALE_Fxns SCALE_STUBS;

/** @endcond */
/**
 *  @brief      Create an instance of an algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via SCALE_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the scale algorithm
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created image decoder
 *                              instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the algorithm.
 *
 *  @sa         Engine_open()
 */
extern SCALE_Handle SCALE_create(Engine_Handle e, String name,
    SCALE_Params *params);


/**
 *  @brief      Execute the "process" method in this instance of the algorithm.
 *
 *  @param[in]  handle  Handle to a created algorithm instance.
 *  @param[in]  inBuf   A buffer descriptor containing the input buffer.
 *  @param[out] outBuf  A buffer descriptor containing the output buffer.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) handle
 *              and the algorithm is in the created state.
 *
 *  @retval     #SCALE_EOK          Success.
 *  @retval     #SCALE_EFAIL        Failure.
 *  @retval     #SCALE_ERUNTIME     Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been processed.
 *
 *  @remark     The buffers supplied to SCALE_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         SCALE_create(), SCALE_delete(), SCALE_control()
 */
extern Int32 SCALE_process(SCALE_Handle handle,
    XDAS_Int8 *inBuf, XDAS_Int8 *outBuf,
    SCALE_InArgs *inArgs, SCALE_OutArgs *outArgs);

/*
 *  ======== SCALE_control ========
 */
/**
 *  @brief      Execute the "control" method in this algorithm instance.
 *
 *  @param[in]  handle  Handle to a created algorithm instance.
 *  @param[in]  id      Command id for control operation.
 *  @param[in]  params  Runtime control parameters.
 *
 *  @pre        @c handle is a valid (non-NULL) image decoder handle
 *              and the image decoder is in the created state.
 *
 *  @retval     #SCALE_EOK          Success.
 *  @retval     #SCALE_EFAIL        Failure.
 *  @retval     #SCALE_ERUNTIME     Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         SCALE_create(), SCALE_delete()
 */
extern Int32 SCALE_control(SCALE_Handle handle, SCALE_Cmd id,
    SCALE_DynamicParams *params);


/*
 *  ======== SCALE_delete ========
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
 *  @post       All resources allocated as part of the SCALE_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         SCALE_create()
 */
extern Void SCALE_delete(SCALE_Handle handle);

#ifdef __cplusplus
}
#endif

/*@}*/  /* ingroup */

#endif
/*
 *  @(#) ti.sdo.ce.examples.extensions.scale; 1, 0, 0,261; 12-2-2010 21:23:31; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

