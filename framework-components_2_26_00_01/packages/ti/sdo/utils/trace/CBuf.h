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
 *  ======== CBuf.h ========
 */
#ifndef ti_sdo_ce_trace_CBuf_
#define ti_sdo_ce_trace_CBuf_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>     /* for size_t */

/*
 *  ======== CBuf_Handle ========
 */
typedef struct CBuf_Obj *CBuf_Handle;

/*
 *  ======== CBuf_Attrs ========
 */
typedef struct CBuf_Attrs {
    Int dummy;
} CBuf_Attrs;

extern CBuf_Attrs CBuf_ATTRS;

/*
 *  ======== CBuf_create ========
 *  Create a circular buffer object.
 *
 *  size must be the size of the buffer pointed to by buf
 *
 *  buf must be large enough to contain *both* the internal state object
 *  CBuf_Obj as well as the character buffer managed by this module.
 */
extern CBuf_Handle CBuf_create(Char *buf, UInt size, CBuf_Attrs *attrs);

/*
 *  ======== CBuf_delete ========
 */
extern Void CBuf_delete(CBuf_Handle trace);

/*
 *  ======== CBuf_empty ========
 */
extern Bool CBuf_empty(CBuf_Handle trace);

/*
 *  ======== CBuf_get ========
 */
extern size_t CBuf_get(CBuf_Handle trace,
    Char *buf, size_t size, size_t *avail);

/*
 *  ======== CBuf_getSize ========
 */
extern UInt CBuf_getSize(CBuf_Handle trace);

/*
 *  ======== CBuf_init ========
 */
extern Void CBuf_init(Void);

/*
 *  ======== CBuf_lost ========
 */
extern UInt CBuf_lost(CBuf_Handle trace);

/*
 *  ======== CBuf_putc ========
 */
extern Void CBuf_putc(CBuf_Handle trace, Char c);

/*
 *  ======== CBuf_puts ========
 */
extern Void CBuf_puts(CBuf_Handle trace, String s);

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.utils.trace; 1, 0, 0,186; 12-1-2010 17:26:17; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

