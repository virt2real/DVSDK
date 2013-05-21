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
/**
 *  @file       ti/sdo/fc/rman/examples/addrspace/ires_algorithm.c
 *
 *  @brief      Dummy implementation of the IRES interfaces by an algorithm
 *
 */

#include <xdc/std.h>
#include <string.h>
#include <stdio.h>

#include "ires_algorithm.h"

/*
 *  ======== IRES_ALGORITHM_numResourceDescriptors ========
 *  Returns number of different resource types the algorithm needs.
 *  Part of IRES interface
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int32 IRES_ALGORITHM_numResourceDescriptors(IALG_Handle handle)
{
    return (NUM_RESOURCES);
}


/*
 *  ======== IRES_ALGORITHM_activateResource ========
 *  Activate particular resource, identified by resource.
 *  Part of IRES interface
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_activateResource(IALG_Handle handle,
        IRES_Handle resource)
{
    DUMRES_TI_Handle alg = (DUMRES_TI_Handle)handle;
    Int              i = 0;

    for (i = 0; i < NUM_RESOURCES; i++) {
        if ((IRES_Handle)alg->resource[i] == resource) {
            if (alg->resourceState[0] == 0) {
                alg->resourceState[0] = 1;
                return (IRES_OK);
            }
            else {
                return (IRES_EINIT);
            }

        }
    }
    return (IRES_OK);
}


/*
 *  ======== IRES_ALGORITHM_activateAllResources ========
 *  Activate all resources. (Part of IRES interface )
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_activateAllResources(IALG_Handle handle)
{
    Int              i = 0;
    DUMRES_TI_Handle alg = (DUMRES_TI_Handle)handle;

    for (i = 0; i < NUM_RESOURCES; i++) {
        if (alg->resourceState[i] == 0) {
            alg->resourceState[i] = 1;
        }
        else {
            return (IRES_EINIT);
        }
    }
    return (IRES_OK);
}

/*
 *  ======== IRES_ALGORITHM_deactivateResource ========
 *  Call to deactivate a resource, identified by resource
 *  Part of IRES interface
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_deactivateResource(IALG_Handle handle,
        IRES_Handle resource)
{
    DUMRES_TI_Handle alg = (DUMRES_TI_Handle)handle;
    Int              i = 0;

    for (i = 0; i < NUM_RESOURCES; i++) {
        if ((IRES_Handle)alg->resource[i] == resource) {
            if (alg->resourceState[0] == 1) {
                alg->resourceState[0] = 0;
                return (IRES_OK);
            }
            else {
                return (IRES_ENORESOURCE);
            }
        }
    }
    return (IRES_OK);
}

/*
 *  ======== IRES_ALGORITHM_deactivateAllResources ========
 *  Call to deactivate all resources
 *  Part of IRES interface
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_deactivateAllResources(IALG_Handle handle)
{
    Int              i = 0;
    DUMRES_TI_Handle alg = (DUMRES_TI_Handle)handle;

    for (i = 0; i < NUM_RESOURCES; i++) {
        if (alg->resourceState[i] == 1) {
            alg->resourceState[i] = 0;
        }
        else {
            return (IRES_ENORESOURCE);
        }
    }
    return (IRES_OK);
}

/*
 *  ======== IRES_ALGORITHM_initResources ========
 *  Grant algorithm the resources it requested. (Part of IRES interface)
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_initResources(IALG_Handle handle,
    IRES_ResourceDescriptor * resDesc, IRES_YieldFxn  yieldFxn,
    IRES_YieldArgs yieldArgs)
{
    DUMRES_TI_Handle alg = (DUMRES_TI_Handle)handle;
    UInt32           val;
    UInt32           dummyVal = 0x12345678;
    UInt32          *addr;
    Int              i = 0;

    for (i = 0; i < NUM_RESOURCES; i++) {
        alg->resourceState[i] = 0;
        alg->resource[i] = (IRES_ADDRSPACE_Handle)resDesc[i].handle;
        printf("\nIRES_ALG_initRes: Resource number %d:\n", i);
        printf("IRES_ALG_initRes> Requested addr 0x%x, "
                "size 0x%x\n",alg->protocolArgs[i].addr,
                alg->protocolArgs[i].len);
        printf("IRES_ALG_initRes> Obtained  addr 0x%lx, size 0x%lx, "
                "blockBase 0x%lx.\n\n",
                (UInt32)(alg->resource[i]->addr),
                (UInt32)(alg->resource[i]->len));

        /*
         *  Read the value at mapped address and attempt to write a value to
         *  it. If this is the device ID register, it should not be writable.
         */
        addr = (UInt32 *)(alg->resource[i]->addr);
        val = *addr;
        printf("IRES_ALG_initRes> Value at 0x%p: 0x%lx\n", addr, val);
        printf("IRES_ALG_initRes> Writing dummy value 0x%lx to 0x%p\n",
                dummyVal, addr);
        *addr = dummyVal;

        /* If this is the device ID register, should see val, not dummyVal. */
        printf("IRES_ALG_initRes> Value read at 0x%p: 0x%lx\n", addr, *addr);
        printf("IRES_ALG_initRes> Restoring value 0x%lx to 0x%p\n", val, addr);
        *addr = val;
        printf("IRES_ALG_initRes> Value read at 0x%p: 0x%lx\n", addr, *addr);
    }
    return (IRES_OK);
}

/*
 *  ======== IRES_ALGORITHM_deinitResources ========
 *  Free resources that the algorithm had requested. (Part of IRES interface)
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_deinitResources(IALG_Handle handle,
        IRES_ResourceDescriptor * resDesc)
{
    Int              i = 0;
    DUMRES_TI_Handle alg = (DUMRES_TI_Handle)handle;

    for (i = 0; i < NUM_RESOURCES; i++) {
        alg->resourceState[i] = 0;
        alg->resource[i] = (IRES_ADDRSPACE_Handle)NULL;
    }
    return (IRES_OK);
}


/*
 *  ======== IRES_ALGORITHM_reinitResources ========
 *  Change resource holdings of a particular algorithm. Part of IRES interface
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_reinitResources(IALG_Handle handle,
        IRES_ResourceDescriptor * resDesc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs)
{
    DUMRES_TI_Handle alg = (DUMRES_TI_Handle)handle;
    Int              i = 0;

    for (i = 0; i < NUM_RESOURCES; i++) {
        alg->resourceState[i] = 0;
    }

    return (IRES_OK);
}


/*
 *  ======== IRES_ALGORITHM_getResourceDescriptors ========
 *  Query the resource requirements of an algoithm.
 *  Once granted the resources, this call will return the actual resouce
 *  handles of the algorithm. (Part of IRES interface)
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_getResourceDescriptors(IALG_Handle handle,
        IRES_ResourceDescriptor *resDesc)
{
    Int              i=0;
    DUMRES_TI_Handle alg = (DUMRES_TI_Handle)handle;

    for (i = 0; i < NUM_RESOURCES; i++) {
        resDesc[i].resourceName = IRES_ADDRSPACE_PROTOCOLNAME;
        resDesc[i].revision = &IRES_ADDRSPACE_PROTOCOLREVISION;
        alg->protocolArgs[i].base.size = sizeof(IRES_ADDRSPACE_ProtocolArgs);
        alg->protocolArgs[i].base.mode = IRES_PERSISTENT;
        alg->protocolArgs[i].attrib = IRES_ADDRSPACE_READ |
            IRES_ADDRSPACE_WRITE;

#ifdef xdc_target__os_WindowsCE
        if (i == 0) {
            alg->protocolArgs[i].len  = 0x100;
            alg->protocolArgs[i].addr  = 0x87000028;
        }
        else {
            alg->protocolArgs[i].len  = 0x2300;
            alg->protocolArgs[i].addr  = 0x87004010;
        }
#else
        if (i == 0) {
//            alg->protocolArgs[i].len  = 0x1150;
//            alg->protocolArgs[i].addr  = 0x80000040;
//            alg->protocolArgs[i].len  = 0x1000;
//            alg->protocolArgs[i].addr  = 0x80000000;
//            alg->protocolArgs[i].len  = 0x1000;
//            alg->protocolArgs[i].addr  = 0x8000ffff;
            /* This is a device ID register, and should not be writable */
            alg->protocolArgs[i].len  = 0x100;
            alg->protocolArgs[i].addr  = 0x01C40028;
        }
        else {
            alg->protocolArgs[i].len  = 0x2300;
            alg->protocolArgs[i].addr  = 0x80004010;
        }
#endif
        resDesc[i].protocolArgs = (IRES_ProtocolArgs *)&(alg->protocolArgs[i]);
        resDesc[i].handle = (IRES_Handle)alg->resource[i];
    }

    return(IRES_OK);
}

/*
 *  ======== DUMRES_TI_IRES ========
 *  IRES interface of the algorithm
 */
IRES_Fxns DUMRES_TI_IRES = {
    (void *)&DUMRES_TI_IRES,
    IRES_ALGORITHM_getResourceDescriptors,
    IRES_ALGORITHM_numResourceDescriptors,
    IRES_ALGORITHM_initResources,
    IRES_ALGORITHM_reinitResources,
    IRES_ALGORITHM_deinitResources,
    IRES_ALGORITHM_activateResource,
    IRES_ALGORITHM_activateAllResources,
    IRES_ALGORITHM_deactivateResource,
    IRES_ALGORITHM_deactivateAllResources
};

/*
 *  ======== IALG_ALGORITHM_Alloc ========
 *  Returns algorithms memory requirements in the memTab structure
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IALG_ALGORITHM_Alloc(const IALG_Params * params, IALG_Fxns ** fxns,
        IALG_MemRec memTab[])
{
    memTab[0].size = sizeof(DUMRES_TI_Obj);
    memTab[0].alignment = 4;
    memTab[0].space = IALG_DARAM0;
    memTab[0].attrs = IALG_PERSIST;

    return (NUM_ALLOC);
}

/*
 *  ======== IALG_ALGORITHM_Deactivate ========
 *  Deactivates the algorithm
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Void IALG_ALGORITHM_Deactivate(IALG_Handle handle)
{
    return;
}


/*
 *  ======== IALG_ALGORITHM_NumAlloc ========
 *  Returns the number of memTab structures required to specify algorithms
 *  memory requirements
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IALG_ALGORITHM_NumAlloc(Void)
{
    return (NUM_ALLOC);
}


/*
 *  ======== IALG_ALGORITHM_Control ========
 *  Control commands for the algorithm to perform certain tasks
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IALG_ALGORITHM_Control(IALG_Handle handle, IALG_Cmd cmd,
        IALG_Status *status)
{
    IRES_Properties props;
    DUMRES_TI_Handle alg = (DUMRES_TI_Handle)handle;

    (*(IRES_Handle)(alg->resource[0])).getStaticProperties(
        (IRES_Handle)alg->resource[0],
        (IRES_Properties *)&props);

    return (0);
}


/*
 *  ======== IALG_ALGORITHM_Activate ========
 *  Activate the algorithm
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Void IALG_ALGORITHM_Activate(IALG_Handle handle)
{
    return;
}

/*
 *  ======== IALG_ALGORITHM_Free ========
 *  Free the memory allocated to the algorithsm
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IALG_ALGORITHM_Free(IALG_Handle handle, IALG_MemRec * memrec)
{
    DUMRES_TI_Handle alg = (Void *)handle;

    memrec[0].base = alg;
    return (NUM_ALLOC);
}


/*
 *  ======== IALG_ALGORITHM_Init ========
 *  Initialize the algorithm
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IALG_ALGORITHM_Init(IALG_Handle handle1, const IALG_MemRec *memrecs,
        IALG_Handle handle2, const IALG_Params *params)
{
    return 0;
}


/*
 *  ======== IALG_ALGORITHM_Moved ========
 *  Indicates that the algoirthm has moved in memory, performs initializations
 *  as required
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Void IALG_ALGORITHM_Moved(IALG_Handle handle1, const IALG_MemRec *memrecs,
        IALG_Handle handle2, const IALG_Params *params)
{
    return;
}

#define IALGFXNS &DUMRES_TI_IALG,\
    IALG_ALGORITHM_Activate,    \
    IALG_ALGORITHM_Alloc,       \
    IALG_ALGORITHM_Control,     \
    IALG_ALGORITHM_Deactivate,  \
    IALG_ALGORITHM_Free,        \
    IALG_ALGORITHM_Init,        \
    IALG_ALGORITHM_Moved,       \
    IALG_ALGORITHM_NumAlloc

/*
 * TI's implementation of IDUMRES
 */
IDUMRES_Fxns DUMRES_TI_IDUMRES = {
    {
    IALGFXNS
    },
};

/*
 * DUMRES_TI_IALG
 * This structure defines TI's implementation of IALG interface
 */
#ifdef xdc_target__isaCompatible_64P
 asm("_DUMRES_TI_IALG .set _DUMRES_TI_IDUMRES");
#else
IALG_Fxns DUMRES_TI_IALG =  {
    IALGFXNS,
};
#endif

/*
 *  @(#) ti.sdo.fc.rman.examples.addrspace; 1, 0, 0,22; 12-1-2010 17:25:34; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

