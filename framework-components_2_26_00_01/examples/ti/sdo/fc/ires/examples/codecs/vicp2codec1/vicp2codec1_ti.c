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
 *  ======== vicp2codec1_ti.c ========
 *  This file contains an implementation of the IVICP2CODEC1_Fxns interface, for
 *  a "copy" algorithm that uses the example IRES VICP2 resource.
 *  This algorithm implements the IRES_Fxns to allow the resources it uses
 *  to be granted and used by the algorithm. The IRES_Fxns implementation
 *  is in its own source file, separate from this file.
 */
#include <xdc/std.h>
#include <string.h>

#include "ivicp2codec1.h"

#include <ti/xdais/ires.h>

/* This define  is to get rid of warnings related to unused static variable 
   IRES_VICP2_PROTOCOLREVISION in the ires_edma3Chan.h header */
#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "vicp2codec1_ti.h"
#include "vicp2codec1_ti_priv.h"

extern IALG_Fxns VICP2CODEC1_TI_IALG;

#define IALGFXNS  \
    &VICP2CODEC1_TI_IALG,       /* module ID */                         \
    NULL,                       /* activate */                          \
    VICP2CODEC1_TI_alloc,       /* alloc */                             \
    NULL,                       /* control (NULL => no control ops) */  \
    NULL,                       /* deactivate */                        \
    VICP2CODEC1_TI_free,        /* free */                              \
    VICP2CODEC1_TI_initObj,     /* init */                              \
    NULL,                       /* moved */                             \
    NULL                        /* numAlloc (NULL => IALG_MAXMEMRECS) */

Int VICP2CODEC1_TI_useVICP(IVICP2CODEC1_Handle handle);

/*
 *  ======== VICP2CODEC1_TI_CODECIRES ========
 *  This structure defines TI's implementation of the IVICP2CODEC1 interface
 *  for the VICP2CODEC1_TI module.
 */
IVICP2CODEC1_Fxns VICP2CODEC1_TI_CODECIRES = {    /* module_vendor_interface */
    {IALGFXNS},
    VICP2CODEC1_TI_useVICP
};

/*
 *  ======== VICP2CODEC1_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VICP2CODEC1_TI module.
 */
#ifdef xdc_target__isaCompatible_64P

asm("_VICP2CODEC1_TI_IALG .set _VICP2CODEC1_TI_CODECIRES");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run on non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VICP2CODEC1_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IVICP2CODEC1_Params VICP2CODEC1_TI_PARAMS = {
    sizeof(IVICP2CODEC1_Params),
};

/*
 *  ======== VICP2CODEC1_TI_alloc ========
 */
/* ARGSUSED */
Int VICP2CODEC1_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(VICP2CODEC1_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}

/*
 *  ======== VICP2CODEC1_TI_free ========
 */
/* ARGSUSED */
Int VICP2CODEC1_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    return (VICP2CODEC1_TI_alloc(NULL, NULL, memTab));
}

/*
 *  ======== VICP2CODEC1_TI_initObj ========
 */
/* ARGSUSED */
Int VICP2CODEC1_TI_initObj(IALG_Handle alg, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    VICP2CODEC1_TI_Obj *handle = (VICP2CODEC1_TI_Obj *)alg;
    const IVICP2CODEC1_Params *params = (IVICP2CODEC1_Params *)algParams;

    /*
     * In lieu of xDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &VICP2CODEC1_TI_PARAMS;
    }

    /* 
     * Also save the context save restore functions in the algorithm instance 
     * This can be done any time after the algorithm instance is created.
     * Not necessary to do it here 
     */ 

    return (IALG_EOK);
}

/* ARGSUSED */
static Void contextSave(IALG_Handle algHandle, Void *contextArgs)
{
    /* VICP2CODEC1_TI_Obj  *alg = (VICP2CODEC1_TI_Obj *)algHandle;*/
    /* VICP2CODEC1_TI_CtxtArgs *ctxt = (VICP2CODEC1_TI_CtxtArgs *)contextArgs;*/
    /* 
     * Add code here to save context of the algorithm object
     * Could involve something like copying scratch Memory contents into 
     * permanent etc
     * Contents will depend on where in algorithms execution it "yields" to  
     * another algorithm
     */ 
}

/* ARGSUSED */
Int VICP2CODEC1_TI_useVICP(IVICP2CODEC1_Handle handle)
{
    /* Extract channel granted to this alg */ 
    VICP2CODEC1_TI_Obj * dumalg = (VICP2CODEC1_TI_Obj *)handle;  
    IRES_GROUPUTILS_Handle grouputils = dumalg->grouputils;
    IRES_VICP2_Handle vicp = NULL;
    IALG_Handle physalg = NULL;
    int i;
    CMEM_init();

    physalg = (IALG_Handle)CMEM_getPhys(dumalg);

        for (i = 0; i < ALGNUM_VICPRESOURCES; i++) {

        vicp = dumalg->resourceHandles[i];

        if (i == 1) { //Late acquired resource !!

            printf("Using scratch resources\n");   
            sleep(3);  

            printf("0x%x Trying to lock LATE acquired resources\n", physalg); 

            grouputils->lockLateAcquireResources((IALG_Handle)
                    handle, grouputils); 

            printf("0x%x Locked LATE acquired resources\n", physalg); 

            printf("About to release scratch group lock, at this time, "
                    "the other alg can get activated !!\n");

            grouputils->releaseGroupLock((IALG_Handle)handle,
                    grouputils);  

            printf("0x%x Released scratch resources\n",physalg); 

            printf("0x%x Busy using the LATE resources\n", physalg); 
            sleep(3);  
            printf("0x%x Done using the LATE resources\n", physalg); 

            grouputils->unlockLateAcquireResources((IALG_Handle)handle, 
                    grouputils);

            printf("0x%x Unlocked LATE acquired resources\n", physalg); 

            printf("0x%x Trying to reacquire scratch resources\n", physalg); 

            grouputils->reacquireGroupLock((IALG_Handle)handle, grouputils);  

            printf("0x%x Reacquired scratch resources\n", physalg); 
            sleep(2);  
        } 
        }
    return (1);
}
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.vicp2codec1; 1, 0, 0,32; 12-1-2010 17:25:11; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

