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
 *  ======== Trace.c ========
 */
#include <xdc/std.h>
#include <ti/sdo/utils/trace/CBuf.h>

#include <stdio.h>
#include <stdarg.h>

#include "Trace.h"

#define MAXLINE 128

#ifdef WIN32
#define VSNPRINTF  _vsnprintf_s
#else
#define VSNPRINTF  vsnprintf
#endif

CBuf_Handle Trace_system = NULL;

/*
 *  ======== Trace_bind ========
 */
Void Trace_bind(CBuf_Handle trace)
{
    Trace_system = trace;
}

/*
 *  ======== Trace_getTrace ========
 */
CBuf_Handle Trace_getTrace(Void)
{
    return (Trace_system);
}

/*
 *  ======== Trace_init ========
 */
Void Trace_init(Void)
{
}

/*
 *  ======== Trace_print ========
 */
Void Trace_print(String fmt, ...)
{
    va_list va;

    va_start(va, fmt);
    Trace_vprint(fmt, va);
    va_end(va);
}

/*
 *  ======== Trace_putc ========
 */
Void Trace_putc(Char c)
{
    if (Trace_system != NULL) {
        CBuf_putc(Trace_system, c);
    }
}

/*
 *  ======== Trace_vprint ========
 */
Void Trace_vprint(String fmt, va_list va)
{
    Char buf[MAXLINE];

    if (Trace_system != NULL) {

        /* generate formated output into buf */
#ifdef WIN32
        VSNPRINTF(buf, sizeof(buf), MAXLINE - 1, fmt, va);
#else
        VSNPRINTF(buf, sizeof(buf), fmt, va);
#endif
        buf[MAXLINE - 1] = '\0';
    
        /* copy to circular buffer */
        CBuf_puts(Trace_system, buf);
    }
}
/*
 *  @(#) ti.sdo.fc.utils.gtinfra; 1, 0, 0,187; 12-1-2010 17:26:11; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

