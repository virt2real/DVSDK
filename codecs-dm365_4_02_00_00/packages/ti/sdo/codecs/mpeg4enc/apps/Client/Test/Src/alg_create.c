/* ========================================================================== */
/*                                                                            */
/*  TEXAS INSTRUMENTS, INC.                                                   */
/*                                                                            */
/*  NAME                                                                      */
/*     alg_create.c                                                           */
/*                                                                            */
/*  DESCRIPTION                                                               */
/*    This file contains a simple implementation of the ALG_create API        */
/*    operation.                                                              */
/*                                                                            */
/*  COPYRIGHT NOTICES                                                         */
/*   Copyright (C) 1996, MPEG Software Simulation Group. All Rights           */
/*   Reserved.                                                                */
/*                                                                            */
/*   Copyright (c) 2001-2003 Texas Instruments Inc.  All rights reserved.     */
/*   Exclusive property of the Video & Imaging Products, Emerging End         */
/*   Equipment group of Texas Instruments India Limited. Any handling,        */
/*   use, disclosure, reproduction, duplication, transmission, or storage     */
/*   of any part of this work by any means is subject to restrictions and     */
/*   prior written permission set forth in TI's program license agreements    */
/*   and associated software documentation.                                   */
/*                                                                            */
/*   This copyright notice, restricted rights legend, or other proprietary    */
/*   markings must be reproduced without modification in any authorized       */
/*   copies of any part of this work.  Removal or modification of any part    */
/*   of this notice is prohibited.                                            */
/*                                                                            */
/*   U.S. Patent Nos. 5,283,900  5,392,448                                    */
/* -------------------------------------------------------------------------- */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.             */
/*                           All Rights Reserved.                             */
/* ========================================================================== */
/* "@(#) XDAS 2.12 05-21-01 (__imports)" */

#if defined(SETUP_DAVINCI) || defined(SETUP_DM642) || defined (OMAP2430_SPECIFIC)
/* -------------------------------------------------------------------------- */
/* Assigning text section to allow better control on placing function in      */
/* memory of our choice and our alignment. The details about placement of     */
/* these section can be obtained from the linker command file "mpeg4enc.cmd". */
/* -------------------------------------------------------------------------- */
#pragma CODE_SECTION(ALG_create, ".text:create")
#pragma CODE_SECTION(ALG_delete, ".text:delete")
#endif

#include <alg.h>
#include <stdlib.h>

#include <_alg.h>
#if 1
extern Bool _ALG1_allocMemory(IALG_MemRec memTab[], Int n);
extern Void _ALG1_freeMemory(IALG_MemRec memTab[], Int n);
/*
 *  ======== ALG_create ========
 */
ALG_Handle ALG_create(IALG_Fxns * fxns, IALG_Handle p,
                      IALG_Params * params)
{
    IALG_MemRec *memTab;
    Int n;
    ALG_Handle alg;
    IALG_Fxns *fxnsPtr;
    //printf("Alg create\n");
    if (fxns != NULL) {
        n = fxns->algNumAlloc !=
            NULL ? fxns->algNumAlloc() : IALG_DEFMEMRECS;

        if ((memTab = (IALG_MemRec *) malloc(n * sizeof(IALG_MemRec)))) {
            //printf("Alg alloc\n");
            n = fxns->algAlloc(params, &fxnsPtr, memTab);
            //printf("n %d\n", n);
            if (n <= 0) {
                printf("NULL");
                return (NULL);
            }

            if (_ALG1_allocMemory(memTab, n)) {
                alg = (IALG_Handle) memTab[0].base;
                alg->fxns = fxns;
                //printf("Call Alg Init\n");
                if (fxns->algInit(alg, memTab, p, params) == IALG_EOK) {
                    free(memTab);
                    return (alg);
                }
                //printf("Free mem.. Failed\n");
                fxns->algFree(alg, memTab);
                _ALG1_freeMemory(memTab, n);
            }
            //printf("n=%d\n",n);
            //printf("Free Mem\n");
            free(memTab);
        }
    }

    return (NULL);
}

/*
 *  ======== ALG_delete ========
 */
Void ALG_delete(ALG_Handle alg)
{
    IALG_MemRec *memTab;
    Int n;
    IALG_Fxns *fxns;

    if (alg != NULL && alg->fxns != NULL) {
        fxns = alg->fxns;
        n = fxns->algNumAlloc !=
            NULL ? fxns->algNumAlloc() : IALG_DEFMEMRECS;

        if ((memTab = (IALG_MemRec *) malloc(n * sizeof(IALG_MemRec)))) {
            memTab[0].base = alg;
            n = fxns->algFree(alg, memTab);
            _ALG1_freeMemory(memTab, n);

            free(memTab);
        }
    }
}
#endif
/* ========================================================================== */
/* End of file : alg_create.c                                                 */
/* -------------------------------------------------------------------------- */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.             */
/*                           All Rights Reserved.                             */
/* ========================================================================== */
