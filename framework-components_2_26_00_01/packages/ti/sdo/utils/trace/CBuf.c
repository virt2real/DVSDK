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
 *  ======== CBuf.c ========
 */
#include <xdc/std.h>
#include <string.h>

#include "CBuf.h"

/*
 *  ======== CBuf_Obj ========
 */
typedef struct CBuf_Obj {
    UInt    curw;       /* offset to next character to be written */
    size_t  sizem1;     /* phys size of the buffer - 1 */
    size_t  avail;      /* number of unread characters */
    Char    *beg;       /* the buffer itself */
    Char    *end;       /* one BEYOND end of buffer */
    UInt    lost;       /* some data lost due to wraparound */
} CBuf_Obj;

CBuf_Attrs CBuf_ATTRS;

/*
 *  ======== CBuf_create ========
 */
CBuf_Handle CBuf_create(Char *buf, UInt size, CBuf_Attrs *attrs)
{
    CBuf_Handle trace;

    if (attrs == NULL) {
        attrs = &CBuf_ATTRS;
    }

    if (size <= sizeof (CBuf_Obj)) {
        return (NULL);
    }

    trace = (CBuf_Handle)buf;
    trace->beg = buf + sizeof (CBuf_Obj);
    size -= sizeof (CBuf_Obj);
    
    trace->curw = 0;
    trace->avail = 0;
    trace->sizem1 = size - 1;
    trace->end = trace->beg + size;
    trace->lost = 0;

    return (trace);
}

/*
 *  ======== CBuf_delete ========
 */
/* ARGSUSED */ 
Void CBuf_delete(CBuf_Handle trace)
{
}

/*
 *  ======== CBuf_empty ========
 */
Bool CBuf_empty(CBuf_Handle trace)
{
    return (trace->avail > 0 ? TRUE : FALSE);
}

/*
 *  ======== CBuf_get ========
 */
UInt CBuf_get(CBuf_Handle trace, Char *buf, size_t size, size_t *avail)
{
    UInt curr;      /* offset to next character to read */
    Char *start;    /* pointer to next character to read */
    size_t max;     /* max forward read possible */

    /* don't read more than what's available */
    if (size > trace->avail) {
        size = trace->avail;
    }

    /* get pointer to oldest character in buffer (start) */
    if (trace->curw >= trace->avail) {
        curr = trace->curw - trace->avail;
    }
    else {
        curr = trace->sizem1 + 1 - (trace->avail - trace->curw);
    }
    start = trace->beg + curr;

    trace->avail -= size;

    /* if size wraps we need two copies */
    max = trace->end - start;
    if (size > max) {
        /* read to end of trace->beg */
        memcpy(buf, start, max);

        /* read remainder from beginning of trace->beg */
        memcpy(buf + max, trace->beg, size - max);
    }
    else {
        memcpy(buf, start, size);
    }

    /* optionally return the number of unread characters */
    if (avail != NULL) {
        *avail = trace->avail;
    }

    /* since we've made space available, we reset the lost count */
    trace->lost = 0;

    return (size);
}

/*
 *  ======== CBuf_getSize ========
 */
UInt CBuf_getSize(CBuf_Handle trace)
{
    return (trace->sizem1 + 1);
}

/*
 *  ======== CBuf_init ========
 */
Void CBuf_init(Void)
{
}

/*
 *  ======== CBuf_lost ========
 */
UInt CBuf_lost(CBuf_Handle trace)
{
    return (trace->lost);
}

/*
 *  ======== CBuf_putc ========
 */
Void CBuf_putc(CBuf_Handle trace, Char c)
{
    trace->beg[trace->curw] = c;

    /* trace->curw always points to the next character to be written */
    if (trace->curw >= trace->sizem1) {
        trace->curw = 0;
    }
    else {
        trace->curw++;
    }

    /* trace->avail never exceeds the size of the trace buffer */
    if (trace->avail <= trace->sizem1) {
        trace->avail++;
    }
    else {
        trace->lost++;
    }
}

/*
 *  ======== CBuf_puts ========
 */
Void CBuf_puts(CBuf_Handle trace, String s)
{
    Char *cp = s;

    while (*cp != '\0') {
        CBuf_putc(trace, *cp++);
    }
}
/*
 *  @(#) ti.sdo.utils.trace; 1, 0, 0,186; 12-1-2010 17:26:17; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

