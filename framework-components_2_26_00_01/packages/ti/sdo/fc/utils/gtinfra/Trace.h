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
/*
 *  ======== Trace.h ========
 */
#ifndef ti_sdo_ce_osal_Trace_
#define ti_sdo_ce_osal_Trace_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <ti/sdo/utils/trace/CBuf.h>

/*
 *  ======== Trace_bind ========
 *  Bind a circular buffer to this module.
 *
 *  All output is written to the specified trace buffer.  If trace is NULL,
 *  output is simply dropped.  Similarily, if an output function is called
 *  before Trace_bind(), output will be dropped.
 */
extern Void Trace_bind(CBuf_Handle trace);

/*
 *  ======== Trace_getTrace ========
 *  Returns the circular buffer that was bound to this module via Trace_bind.
 */
extern CBuf_Handle Trace_getTrace(Void);

/*
 *  ======== Trace_init ========
 */
extern Void Trace_init(Void);

/*
 *  ======== Trace_print ========
 */
extern Void Trace_print(String fmt, ...);

/*
 *  ======== Trace_putc ========
 */
extern Void Trace_putc(Char c);

/*
 *  ======== Trace_vprint ========
 */
extern Void Trace_vprint(String fmt, va_list va);

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.fc.utils.gtinfra; 1, 0, 0,187; 12-1-2010 17:26:11; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

