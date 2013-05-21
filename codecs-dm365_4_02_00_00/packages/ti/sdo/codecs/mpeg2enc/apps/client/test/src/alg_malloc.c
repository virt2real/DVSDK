/*
 *  Copyright 2003 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) XDAS 2.51.00 11-29-2003 (xdas-2.50.00.9)
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

#pragma CODE_SECTION(ALG_init, ".text:init")
#pragma CODE_SECTION(ALG_exit, ".text:exit")
#pragma CODE_SECTION(_ALG_allocMemory, ".text:create")
#pragma CODE_SECTION(_ALG_freeMemory, ".text:create")

#include <xdc/std.h>
#include <ti/xdais/ialg.h>
//#include <alg.h>

#include <stdlib.h>     /* malloc/free declarations */
#include <string.h>     /* memset declaration */
#include <ti/sdo/linuxutils/cmem/include/cmem.h>
extern CMEM_AllocParams memParams;

#if defined (_54_) || (_55_) || (_28_)
void *mem_align(size_t alignment, size_t size);
void mem_free(void *ptr);
#define myMemalign  mem_align
#define myFree      mem_free
#else
#define myMemalign  memalign
#define myFree      free
#endif


Bool _ALG1_allocMemory(IALG_MemRec memTab[], Int n);
Void _ALG1_freeMemory(IALG_MemRec memTab[], Int n);

/*
 *  ======== ALG_activate ========
 */
#if 0
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


#endif
/*
 *  ======== _ALG_allocMemory ========
 */
Bool _ALG1_allocMemory(IALG_MemRec memTab[], Int n)
{
    Int i;

    for (i = 0; i < n; i++) {

#ifdef _DEBUG_IALG
		printf("MemTab = %d\t Size = %d\tSpace = %d\tAttrs = %d\n",i,memTab[i].size,memTab[i].space,memTab[i].attrs);
#endif

#ifdef ON_LINUX

        memTab[i].base = (void *)CMEM_alloc( memTab[i].size, &memParams);
#else
        memTab[i].base = (void *)myMemalign(memTab[i].alignment, memTab[i].size);
#endif
        if (memTab[i].base == NULL) {
            _ALG_freeMemory(memTab, i);
            return (FALSE);
        }
        /*------------------------------------------------------------------*/
		/* Recommended to work with out memset 0.                           */
		/*------------------------------------------------------------------*/
        //memset(memTab[i].base, 0, memTab[i].size);
    }

    return (TRUE);
}

/*
 *  ======== _ALG_freeMemory ========
 */
Void _ALG1_freeMemory(IALG_MemRec memTab[], Int n)
{
    Int i;

    for (i = 0; i < n; i++) {
        if (memTab[i].base != NULL) {
#ifdef ON_LINUX
            CMEM_free(memTab[i].base, &memParams);
#else
            myFree(memTab[i].base);
#endif
        }
    }
}
#if defined (_54_) || (_55_) || (_28_)
/*
 *  ======== mem_align ========
 */
void *mem_align(size_t alignment, size_t size)
{
    void     **mallocPtr;
    void     **retPtr;

    /* return if invalid size value */
    if (size <= 0) {
       return (0);
    }

    /*
     * If alignment is not a power of two, return what malloc returns. This is
     * how memalign behaves on the c6x.
     */
    if ((alignment & (alignment - 1)) || (alignment <= 1)) {
        if( (mallocPtr = malloc(size + sizeof(mallocPtr))) != NULL ) {
            *mallocPtr = mallocPtr;
            mallocPtr++;
        }
        return ((void *)mallocPtr);
    }

    /* allocate block of memory */
    if ( !(mallocPtr = malloc(alignment + size)) ) {
        return (0);
    }

    /* Calculate aligned memory address */
    retPtr = (void *)(((Uns)mallocPtr + alignment) & ~(alignment - 1));

    /* Set pointer to be used in the mem_free() fxn */
    retPtr[-1] = mallocPtr;

    /* return aligned memory */
    return ((void *)retPtr);
}

/*
 *  ======== mem_free ========
 */
Void mem_free(void *ptr)
{
    free((void *)((void **)ptr)[-1]);
}

#endif
