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
 *  @file       ivicp2codec1.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the VICP2CODEC1 algorithms.
 */
/**
 *  @defgroup   ti_ires_examples_codecs_vicp2codec1_IVICP2CODEC1   EdmaCodec1 
 *                                                               Interface
 *
 */

#ifndef ti_ires_examples_codecs_vicp2codec1_IVICP2CODEC1_
#define ti_ires_examples_codecs_vicp2codec1_IVICP2CODEC1_

#include <ti/xdais/ialg.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_ires_examples_codecs_vicp2codec1_IVICP2CODEC1 */
/*@{*/

#define IVICP2CODEC1_EOK      1              
#define IVICP2CODEC1_EFAIL    -1            
#define IVICP2CODEC1_EUNSUPPORTED -2 

/**
 *  @brief      This must be the first field of all IVICP2CODEC1
 *              instance objects.
 */
typedef struct IVICP2CODEC1_Obj {
    struct IVICP2CODEC1_Fxns *fxns;
} IVICP2CODEC1_Obj;


/**
 *  @brief      Opaque handle to an IVICP2CODEC1 objects.
 */
typedef struct IVICP2CODEC1_Obj  *IVICP2CODEC1_Handle;


/**
 *  @brief      Defines the creation time parameters for
 *              all IVICP2CODEC1 instance objects.
 *
 *  @extensibleStruct
 */
typedef struct IVICP2CODEC1_Params {
    Int size;
} IVICP2CODEC1_Params;

/**
 *  @brief      Defines all of the operations on IVICP2CODEC1 objects.
 */
typedef struct IVICP2CODEC1_Fxns{

    IALG_Fxns   ialg;             /**< xDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

    Int (*useVICP)(IVICP2CODEC1_Handle handle);

} IVICP2CODEC1_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_ires_examples_codecs_vicp2codec1_IVICP2CODEC1_ */
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.vicp2codec1; 1, 0, 0,32; 12-1-2010 17:25:10; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

