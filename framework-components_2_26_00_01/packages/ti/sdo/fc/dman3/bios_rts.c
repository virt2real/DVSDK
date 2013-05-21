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
 *  ======== bios_rts.c ========
 *
 *  This file contains Implementation of non-BIOS versions of MEM functions,
 *  MEM_valloc() and MEM_free(), TSK functions used by DMAN3. This is needed
 *  for Linux version of DMAN3 library.
 */


#include <xdc/std.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "bios_rts.h"

#define PTRSIZE sizeof(Void *)

/*
 *  ======== MEM_alloc ========
 */
Void * MEM_alloc(Int segid, size_t size, size_t align)
{
    return (MEM_valloc(segid, size, align, 0));
}


/*
 *  ======== MEM_free ========
 *
 *  Note - segid is not supported.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Bool MEM_free(Int segid, Void * alignBuf, size_t size)
{
    Uint32 *addrPtr;
    Void   *buf;
    Uns     remainBytes = 0;

    if ((PTRSIZE - 1) & size) {
        remainBytes = PTRSIZE - ((PTRSIZE - 1) & size);
    }

    addrPtr = (Uint32 *)((Uint32)alignBuf + size + remainBytes);
    buf = (Void *)*addrPtr;

    free(buf);

    return (TRUE);
}

/*
 *  ======== MEM_valloc ========
 *
 *  Note - segid is not supported.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Void * MEM_valloc(Int segid, size_t size, size_t align, Char val)
{
    Uns     alignSize;
    Uns     alignBytes;
    Uns     remainBytes;
    Void   *buf;
    Void   *alignBuf;
    Uns     tmpAlign;
    Uint32 *addrPtr;


    /*
     *  Must at least align on 32-bit boundary since we're storing the
     *  32-bit address of the malloc'd buffer.
     */
    alignBytes = (align < PTRSIZE) ? PTRSIZE : align;

    /* alignment must be a power of 2 */
    // DBC_require((alignBytes & (alignBytes - 1)) == 0);
    if ((alignBytes & (alignBytes - 1)) != 0) {
        return (NULL);
    }

    /*
     *  We will allocate a buffer larger than "size", to allow for alignment
     *  and to hold the address of the buffer returned by malloc() at the
     *  end of the buffer.
     *  Make size a multiple of 32-bits so it will be easier to find the
     *  address of the buffer returned by malloc(). 
     */
    alignSize = size;
    if ((remainBytes = alignSize & (PTRSIZE - 1)) != 0) {
        /* size is not a multiple of 32-bits */
        alignSize += PTRSIZE - remainBytes;
        remainBytes = PTRSIZE - remainBytes;
    }

    /* Add 32-bits to store pointer of allocated buffer */
    alignSize += PTRSIZE;

    alignSize += alignBytes;
    buf = malloc(alignSize);

    tmpAlign = (Uns)buf & (alignBytes - 1);
    if (tmpAlign) {
        alignBuf = (Void *)((Uns)buf + alignBytes - tmpAlign);
    }
    else {
        alignBuf = buf;
    }

    /* Store the malloc'd address for freeing later. */
    addrPtr = (Uint32 *)((Uint32)alignBuf + size + remainBytes);
    *addrPtr = (Uint32)buf;

    /* Initialize the aligned buffer with 'val' */
    memset(alignBuf, val, size);

    //DBC_ensure(!((Uint32)alignBuf & (alignBytes - 1)));

    return (alignBuf);
}

/*
 *  ======== TSK_enable ========
 */
Void TSK_enable(Void)
{
}

/*
 *  ======== TSK_disable ========
 */
Void TSK_disable(Void)
{
}

/*
 *  ======== SYS_abort ========
 */
Void SYS_abort(char * fmt, ...)
{
    /* TODO: This should be configurable */
    va_list ap;
 
    va_start(ap, fmt);

    /* TODO:M This should probably be GT rather than stdio */
    vfprintf(stderr, fmt, ap);
    va_end(ap);
 
    exit(3);
}
/*
 *  @(#) ti.sdo.fc.dman3; 1, 0, 4,300; 12-1-2010 17:24:24; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

