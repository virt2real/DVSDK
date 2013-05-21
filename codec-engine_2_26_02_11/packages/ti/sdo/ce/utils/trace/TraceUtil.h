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
 *  ======== TraceUtil.h ========
 */
/**
 *  @file       ti/sdo/ce/utils/trace/TraceUtil.h
 *
 *  @brief      The Codec Engine utility module for trace.
 */
/**
 *  @defgroup   ti_sdo_ce_utils_trace_TraceUtil Codec Engine Tracing Utility
 */

#ifndef _TRACEUTIL_H
#define _TRACEUTIL_H

#include <ti/sdo/ce/Engine.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_sdo_ce_utils_trace_TraceUtil */
/*@{*/


#define TRACEUTIL_SUCCESS 0     /**< Success. */
#define TRACEUTIL_FAILURE -1    /**< General system error. */

/*
 *  ======== TraceUtil_start ========
 */
/**
 *  @brief      Begin using the TraceUtil module; create thread that
 *              periodically collects DSP trace
 *
 *  @param[in]  engineName      Name of the engine.  This uses the same
 *                              name conventions as Engine_open()'s name.
 *
 *  @retval     TRACEUTIL_SUCCESS       Success.
 *  @retval     TRACEUTIL_FAILURE       Failed to initialize the necessary
 *                                      tracing resources.
 *
 *  @sa         TraceUtil_stop()
 */
extern Int  TraceUtil_start(String engineName);

/*
 *  ======== TraceUtil_stop ========
 */
/**
 *  @brief      Finish using the TraceUtil module, stop the collecting thread
 *
 *  @retval     TRACEUTIL_SUCCESS       Success.
 *  @retval     TRACEUTIL_FAILURE       Failed to free the necessary
 *                                      tracing resources.
 *
 *  @sa         TraceUtil_start()
 */
extern Int  TraceUtil_stop(Void);

/** @cond INTERNAL */

extern Void TraceUtil_exit();
extern Void TraceUtil_init();

/** @endcond */

/*@}*/

#ifdef __cplusplus
}
#endif

#endif

/*
 *  @(#) ti.sdo.ce.utils.trace; 1, 0, 1,307; 12-2-2010 21:28:05; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

