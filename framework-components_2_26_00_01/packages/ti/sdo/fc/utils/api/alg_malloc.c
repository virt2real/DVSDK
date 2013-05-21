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
 *  ======== alg_malloc.c ========
 *  This module implements an algorithm memory management "policy" in which
 *  no memory is shared among algorithm objects.  Memory is, however
 *  reclaimed when objects are deleted.
 *
 *  preemption      sharing             object deletion
 *  ----------      -------             ---------------
 *  yes(*)          none                yes
 *
 *  Note 1: this module uses run-time support functions malloc() and free()
 *  to allocate and free memory.  Since these functions are *not* reentrant,
 *  either all object creation and deletion must be performed by a single
 *  thread or reentrant versions or these functions must be created.
 *
 *  Note 2: Memory alignment is supported for the c5000 targets with the
 *  memalign5000() function which allocates 'size + align' memory.  This
 *  is necessary since the compiler's run-time library does not
 *  support memalign().  This wastes 'align' extra memory.
 *
 */


#ifdef xdc_target__isaCompatible_64P
#pragma CODE_SECTION(ALG_init, ".text:init")
#pragma CODE_SECTION(ALG_exit, ".text:exit")
#pragma CODE_SECTION(_ALG_allocMemory, ".text:create")
#pragma CODE_SECTION(_ALG_freeMemory, ".text:create")
#endif

#include <xdc/std.h>
#include <alg.h>
#include <ti/xdais/ialg.h>

#include <stdlib.h>     /* malloc/free declarations */
#include <string.h>     /* memset declaration */

#if defined(xdc_target__os_Linux) || defined(xdc_target__os_WindowsCE)
#include <malloc.h>     
#endif

#if defined(xdc_target__os_WindowsCE)
/* Windows CE doesn't seem to have an _aligned_malloc() or memalign function */
static Ptr myMemalign(UInt32 size, UInt32 align);
#else
#define myMemalign  memalign
#endif

#define myFree      free


Bool _ALG_allocMemory(IALG_MemRec memTab[], Int n);
Void _ALG_freeMemory(IALG_MemRec memTab[], Int n);

/*
 *  ======== ALG_activate ========
 */
Void ALG_activate(ALG_Handle alg)
{
    /* restore all persistant shared memory */
        ;   /* nothing to do since memory allocation never shares any data */
    
    /* do app specific initialization of scratch memory */
    if (alg->fxns->algActivate != NULL) {
        alg->fxns->algActivate(alg);
    }
}

/*
 *  ======== ALG_deactivate ========
 */
Void ALG_deactivate(ALG_Handle alg)
{
    /* do app specific store of persistent data */
    if (alg->fxns->algDeactivate != NULL) {
        alg->fxns->algDeactivate(alg);
    }

    /* save all persistant shared memory */
        ;   /* nothing to do since memory allocation never shares any data */
    
}

/*
 *  ======== ALG_exit ========
 */
Void ALG_exit(Void)
{
}

/*
 *  ======== ALG_init ========
 */
Void ALG_init(Void)
{
}


/*
 *  ======== _ALG_allocMemory ========
 */
Bool _ALG_allocMemory(IALG_MemRec memTab[], Int n)
{
    Int i;
    
    for (i = 0; i < n; i++) {
        memTab[i].base = (void *)myMemalign(memTab[i].alignment, memTab[i].size);

        if (memTab[i].base == NULL) {
            _ALG_freeMemory(memTab, i);
            return (FALSE);
        }
        memset(memTab[i].base, 0, memTab[i].size);
    }

    return (TRUE);
}

/*
 *  ======== _ALG_freeMemory ========
 */
Void _ALG_freeMemory(IALG_MemRec memTab[], Int n)
{
    Int i;
    
    for (i = 0; i < n; i++) {
        if (memTab[i].base != NULL) {
            myFree(memTab[i].base);
        }
    }
}

#if defined(xdc_target__os_WindowsCE)

/*
 *  ======== myMemalign ========
 */
static Ptr myMemalign(UInt32 size, UInt32 align)
{
    UInt32     alignSize;
    UInt32     alignBytes;
    UInt32     remainBytes;
    Ptr        buf;
    Ptr        alignBuf;
    UInt32     tmpAlign;
    UInt32    *addrPtr;

    /*
     *  Must at least align on 32-bit boundary since we're storing the
     *  32-bit address of the malloc'd buffer.
     */
    alignBytes = (align < sizeof(UInt32)) ? sizeof(UInt32) : align;

    /*
     *  We will allocate a buffer larger than "size", to allow for alignment
     *  and to store the address and original size of the buffer returned by
     *  malloc() at the end of the buffer.
     *  Make size a multiple of 32-bits so it will be easier to find the
     *  address of the buffer returned by malloc(). 
     */
    alignSize = size;
    if ((remainBytes = alignSize & (sizeof(UInt32) - 1)) != 0) {
        /* size is not a multiple of 32-bits */
        alignSize += sizeof(UInt32) - remainBytes;
        remainBytes = sizeof(UInt32) - remainBytes;
    }

    /* Add 2 32-bit words to store address and original size of buffer */
    alignSize += sizeof(UInt32) * 2;

    alignSize += alignBytes;
    
    /* malloc the buffer! */
    if ((buf = malloc(alignSize)) == NULL) {
        return (NULL);
    }

    /* Get the aligned address */
    tmpAlign = (UInt32)buf & (alignBytes - 1);
    if (tmpAlign) {
        alignBuf = (Void *)((UInt32)buf + alignBytes - tmpAlign);
    }
    else {
        /* The buffer was already aligned */
        alignBuf = buf;
    }

    /* Store the malloc'd address and original size for freeing later. */
    addrPtr = (UInt32 *)((UInt32)alignBuf + size + remainBytes);
    *addrPtr = (UInt32)buf;
    *(addrPtr + 1) = alignSize;

    return (alignBuf);
}
#endif
/*
 *  @(#) ti.sdo.fc.utils.api; 1, 0, 0,264; 12-1-2010 17:26:05; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

