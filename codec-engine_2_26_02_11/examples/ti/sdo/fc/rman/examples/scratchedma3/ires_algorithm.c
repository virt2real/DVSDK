/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 */

/* 
 * Copyright (c) 2009, Texas Instruments Incorporated
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
 *  @file       ti/sdo/fc/rman/examples/dummyEdma3/ires_algorithm.c 
 *
 *  @brief      Dummy implementation of the IRES interfaces by an algorithm  
 *
 */

#include <xdc/std.h>
#include <string.h>
#include <stdio.h>

#include "ires_algorithm.h"

/*
 * ===== IRES_ALGORITHM_numResourceDescriptors =====
 *
 * Returns number of different resource types the algorithm needs.
 * Part of IRES interface 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int32 IRES_ALGORITHM_numResourceDescriptors(IALG_Handle handle) 
{
#ifdef DM6446
    return (2);
#else
    return (NUM_RESOURCES);
#endif
}


/*
 * ===== IRES_ALGORITHM_activateResource =====
 *
 * Call to activate particular resource, identified by resourceHandle 
 * Part of IRES interface 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_activateResource(IALG_Handle handle, 
        IRES_Handle resourceHandle)
{
    DUMRES_TI_Handle algHandle = (DUMRES_TI_Handle)handle;
    Int i = 0;

    for (i = 0; i < NUM_RESOURCES; i++) {
        if ((IRES_Handle)algHandle->resourceHandles[i] == resourceHandle) {
            if (algHandle->resourceState[0] == 0) {
                algHandle->resourceState[0] = 1;
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
 * ===== IRES_ALGORITHM_activateAllResources =====
 *
 * Call to activate all resources
 * Part of IRES interface 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_activateAllResources(IALG_Handle handle)
{
    Int i = 0;
    DUMRES_TI_Handle algHandle = (DUMRES_TI_Handle)handle;
    
    for (i = 0; i < NUM_RESOURCES; i++) {
    
        if (algHandle->resourceState[i] == 0) {
            algHandle->resourceState[i] = 1;
        }
        else {
            return (IRES_EINIT);
        }
    }
    return (IRES_OK);
}

/*
 * ===== IRES_ALGORITHM_deactivateResource =====
 *
 * Call to deactivate a resource, identified by resourceHandle
 * Part of IRES interface 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_deactivateResource(IALG_Handle handle, 
        IRES_Handle resourceHandle) 
{

    DUMRES_TI_Handle algHandle = (DUMRES_TI_Handle)handle;
    Int i = 0;

    for (i = 0; i < NUM_RESOURCES; i++) {
        if ((IRES_Handle)algHandle->resourceHandles[i] == resourceHandle) {
            if (algHandle->resourceState[0] == 1) {
                algHandle->resourceState[0] = 0;
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
 * ===== IRES_ALGORITHM_deactivateAllResources =====
 *
 * Call to deactivate all resources
 * Part of IRES interface 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_deactivateAllResources(IALG_Handle handle) 
{
    Int i = 0;

    DUMRES_TI_Handle algHandle = (DUMRES_TI_Handle)handle;
    for (i = 0; i < NUM_RESOURCES; i++) {
        if (algHandle->resourceState[i] == 1) {
            algHandle->resourceState[i] = 0;
        }
        else {
            return (IRES_ENORESOURCE);
        }
    }
    return (IRES_OK);
}


/*
 * ===== IRES_ALGORITHM_initResources =====
 *
 * Call to grant algorithm the resources it requested 
 * Part of IRES interface 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_initResources(IALG_Handle handle,
    IRES_ResourceDescriptor * resourceDescriptor, IRES_YieldFxn  yieldFxn,
    IRES_YieldArgs yieldArgs)
{
    Int i = 0, j = 0;
    IRES_EDMA3CHAN_Handle h = NULL; 

    DUMRES_TI_Handle algHandle = (DUMRES_TI_Handle)handle;
    for (i = 0; i < NUM_RESOURCES; i++) {
        algHandle->resourceState[i] = 0;
        algHandle->resourceHandles[i] =
            (IRES_EDMA3CHAN_Handle)resourceDescriptor[i].handle;
        h = (IRES_EDMA3CHAN_Handle)resourceDescriptor[i].handle;
        /* Print out resource descriptor */         
        printf("Resource descriptor: %d\n",i);
        printf("Assigned PaRams: ");
        for (j = 0; j < h->assignedNumPaRams; j++) {
            printf("%d ", h->assignedPaRamIndices[j]);
        } 
        printf("\nAssigned Tccs: ");
        for (j = 0; j < h->assignedNumTccs; j++) {
            printf("%d ", h->assignedTccIndices[j]);
        } 
        printf("\nAssigned Qdma channel %d\n",h->assignedQdmaChannelIndex); 
        printf("Assigned Edma channel %d\n\n",h->assignedEdmaChannelIndex); 
    }
    return (IRES_OK);
}


/*
 * ===== IRES_ALGORITHM_deinitResources =====
 *
 * Call to free resources that the algorithm had requested 
 * Part of IRES interface 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_deinitResources(IALG_Handle handle,
    IRES_ResourceDescriptor * resourceDescriptor)
{
    Int i = 0;
    DUMRES_TI_Handle algHandle = (DUMRES_TI_Handle)handle;
    
    for (i = 0; i < NUM_RESOURCES; i++) {
        algHandle->resourceState[i] = 0;
        algHandle->resourceHandles[i] = (IRES_EDMA3CHAN_Handle)NULL;
    }
    return (IRES_OK);
}


/*
 * ===== IRES_ALGORITHM_reinitResources =====
 *
 * Call to change resource holdings of a particular algorithm 
 * Part of IRES interface 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_reinitResources(IALG_Handle handle,
    IRES_ResourceDescriptor * resourceDescriptor,
    IRES_YieldFxn  yieldFxn, IRES_YieldArgs yieldArgs)
{
    Int i = 0;
    DUMRES_TI_Handle algHandle = (DUMRES_TI_Handle)handle;
    
    for (i = 0; i < NUM_RESOURCES; i++) {
        algHandle->resourceState[i] = 0;
    }

    return (IRES_OK);
}


/*
 * ===== IRES_ALGORITHM_getResourceDescriptors =====
 *
 * Call to query the resource requirements of an algoithm.
 * Once granted the resources, this call will return also the actual resouce
 * handles of the algorithm  
 * Part of IRES interface 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_ALGORITHM_getResourceDescriptors(IALG_Handle handle, 
    IRES_ResourceDescriptor *resourceDescriptors)
{
    Int i=0;
    short numParams = 5; 
    DUMRES_TI_Handle algHandle = (DUMRES_TI_Handle)handle;
    int algNumber = algHandle->algId;
    static short tcc = IRES_EDMA3CHAN_TCC_ANY;
    static short edma = IRES_EDMA3CHAN_EDMACHAN_ANY;
    int count = NUM_RESOURCES;
    printf("Granting resources for alg# %d 0x%x\n",algNumber, algHandle);

    for (i = 0; i < numParams; i++) {
        algHandle->paRamArray[i] =  IRES_EDMA3CHAN_PARAM_ANY;
    }

    resourceDescriptors[0].resourceName = IRES_EDMA3CHAN_PROTOCOLNAME;
    resourceDescriptors[0].revision = &IRES_EDMA3CHAN_PROTOCOLREVISION;

    algHandle->protocolArgs[0].size = sizeof(IRES_EDMA3CHAN_ProtocolArgs);

/*      if (tcc == IRES_EDMA3CHAN_TCC_NONE) {*/
    if (0x2 == algNumber) {
        algHandle->protocolArgs[0].numTccs = 0; 
        tcc = IRES_EDMA3CHAN_TCC_NONE;    
    }
    else {
#ifdef DM6446
            count = 2;
        /* Don't allocate any TCCs, allocate channels only. Since no DCHMAP
           these will give you Channel = TCC = PARAM */ 
        algHandle->protocolArgs[0].numTccs = 0; 
        tcc = IRES_EDMA3CHAN_TCC_NONE;    
#else
        algHandle->protocolArgs[0].numTccs = 2; 
        tcc = IRES_EDMA3CHAN_TCC_ANY;
#endif
    }
    algHandle->protocolArgs[0].tccIndex = tcc;
    algHandle->protocolArgs[0].contiguousAllocation = 0;
#ifdef DM6446
    algHandle->protocolArgs[0].edmaChan = IRES_EDMA3CHAN_EDMACHAN_ANY;
    algHandle->protocolArgs[0].numPaRams = 0; 
#else
    algHandle->protocolArgs[0].edmaChan = IRES_EDMA3CHAN_CHAN_NONE;
    algHandle->protocolArgs[0].numPaRams = 4; 
#endif
    algHandle->protocolArgs[0].paRamIndex = IRES_EDMA3CHAN_PARAM_ANY;
    algHandle->protocolArgs[0].qdmaChan = IRES_EDMA3CHAN_CHAN_NONE;
    algHandle->protocolArgs[0].mode = IRES_SCRATCH;  
    resourceDescriptors[0].protocolArgs =
            (IRES_ProtocolArgs *)&(algHandle->protocolArgs[0]);
    resourceDescriptors[0].handle = 
            (IRES_Handle)algHandle->resourceHandles[0];
    printf("Request for resources by alg 0x%x\n", algHandle);
    printf("0: Tccs %d, Params %d, Edma %d, Qdma %d\n", 
            algHandle->protocolArgs[0].numTccs,
            algHandle->protocolArgs[0].numPaRams, 
            algHandle->protocolArgs[0].edmaChan,
            algHandle->protocolArgs[0].qdmaChan);


    for (i = 1; i < count; i++) {
        resourceDescriptors[i].resourceName = IRES_EDMA3CHAN_PROTOCOLNAME;
        resourceDescriptors[i].revision = &IRES_EDMA3CHAN_PROTOCOLREVISION;
        algHandle->protocolArgs[i].size = sizeof(IRES_EDMA3CHAN_ProtocolArgs);
/*
 * Number of PaRams requested has to be <= 1, if an EDMA channel is ALSO 
 * requested on a device where DCHMAP doesn't exist
 */
        if (tcc == IRES_EDMA3CHAN_TCC_NONE) {
            algHandle->protocolArgs[0].numTccs = 0; 
        }
        else {
            algHandle->protocolArgs[i].numTccs = 1; 
        }
        algHandle->protocolArgs[i].tccIndex = tcc;
        algHandle->protocolArgs[i].contiguousAllocation = 0;
/*         algHandle->protocolArgs[i].contiguousAllocation = (i%2);*/
#ifdef DM6446
        if (i ==0) {
            /* An edma channel */  
            algHandle->protocolArgs[i].edmaChan = edma;
            algHandle->protocolArgs[i].numPaRams = 0; 
            algHandle->protocolArgs[i].qdmaChan = IRES_EDMA3CHAN_CHAN_NONE;
        }
        else {
            /* A qdma channel with Params (ACPY3 like) */
            algHandle->protocolArgs[i].edmaChan = IRES_EDMA3CHAN_CHAN_NONE;
            algHandle->protocolArgs[i].numPaRams = 4; 
            if (algNumber == 0x2) {
                algHandle->protocolArgs[i].qdmaChan = IRES_EDMA3CHAN_CHAN_NONE;
            }
            else {
#ifdef NOQDMA
                algHandle->protocolArgs[i].qdmaChan = 
                        IRES_EDMA3CHAN_CHAN_NONE;
#else
                algHandle->protocolArgs[i].qdmaChan = 
                        IRES_EDMA3CHAN_QDMACHAN_ANY;
#endif
            }
            algHandle->protocolArgs[i].numTccs = 4; 
            algHandle->protocolArgs[i].tccIndex = IRES_EDMA3CHAN_TCC_ANY;
        }
        algHandle->protocolArgs[i].paRamIndex = IRES_EDMA3CHAN_PARAM_ANY;
#else
        algHandle->protocolArgs[i].edmaChan = edma;
        algHandle->protocolArgs[i].numPaRams = 0; 
        algHandle->protocolArgs[i].paRamIndex = IRES_EDMA3CHAN_PARAM_ANY;
#ifdef NOQDMA
        algHandle->protocolArgs[i].qdmaChan = IRES_EDMA3CHAN_CHAN_NONE;
#else
        algHandle->protocolArgs[i].qdmaChan = ((i == 0) ? 
                IRES_EDMA3CHAN_QDMACHAN_ANY: IRES_EDMA3CHAN_CHAN_NONE);
#endif
#endif
        algHandle->protocolArgs[i].mode = IRES_SCRATCH;  
        resourceDescriptors[i].protocolArgs =
                    (IRES_ProtocolArgs *)&(algHandle->protocolArgs[i]);
        resourceDescriptors[i].handle = 
                (IRES_Handle)algHandle->resourceHandles[i];
        printf("%d: Tccs %d, Params %d, Edma %d, Qdma %d\n", i, 
                algHandle->protocolArgs[i].numTccs,
                algHandle->protocolArgs[i].numPaRams, 
                algHandle->protocolArgs[i].edmaChan,
                algHandle->protocolArgs[i].qdmaChan);
    }

    edma = IRES_EDMA3CHAN_CHAN_NONE;
    return(IRES_OK);
}

/*
 * IRES interface of the algorithm
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
 * ===== IALG_ALGORITHM_Alloc ======
 *
 * Returns algorithms memory requirements in the memTab structure   
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
 * ===== IALG_ALGORITHM_Deactivate ======
 *
 * Deactivates the algorithm 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Void IALG_ALGORITHM_Deactivate(IALG_Handle handle)
{
    return;
}


/*
 * ===== IALG_ALGORITHM_NumAlloc ======
 *
 * Returns the number of memTab structures required to specify algorithms
 * memory requirements 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IALG_ALGORITHM_NumAlloc(Void)
{
        return (NUM_ALLOC);
}


/*
 * ===== IALG_ALGORITHM_Control ======
 *
 * Control commands for the algorithm to perform certain tasks 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IALG_ALGORITHM_Control(IALG_Handle handle, IALG_Cmd cmd,
    IALG_Status *status) 
{
    IRES_EDMA3CHAN_Properties resourceProperties;
    DUMRES_TI_Handle algHandle = (DUMRES_TI_Handle)handle;

    (*(IRES_Handle)(algHandle->resourceHandles[0])).getStaticProperties(
            (IRES_Handle)algHandle->resourceHandles[0],
                    (IRES_Properties *)&resourceProperties);
        
    return (0);
}


/*
 * ===== IALG_ALGORITHM_Activate ======
 *
 * Activate the algorithm 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Void IALG_ALGORITHM_Activate(IALG_Handle handle)
{
    return;
}

/*
 * ===== IALG_ALGORITHM_Free ======
 *
 * Free the memory allocated to the algorithsm  
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IALG_ALGORITHM_Free(IALG_Handle handle, IALG_MemRec * memrec)
{
    DUMRES_TI_Handle alg = (Void *)handle; 
    memrec[0].base = alg;
    return (NUM_ALLOC);
}


/*
 * ===== IALG_ALGORITHM_Init ======
 *
 * Initialize the algorithm 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IALG_ALGORITHM_Init(IALG_Handle handle1, const IALG_MemRec *memrecs,
    IALG_Handle handle2, const IALG_Params *params)
{
    DUMRES_TI_Handle alg = (DUMRES_TI_Handle)memrecs[0].base;
    alg->algId = ((IDUMRES_Params *)params)->algNum;
    return 0;
}


/*
 * ===== IALG_ALGORITHM_Moved ======
 *
 * Indicates that the algoirthm has moved in memory, performs initializations
 * as required
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Void IALG_ALGORITHM_Moved(IALG_Handle handle1, const IALG_MemRec *memrecs,
    IALG_Handle handle2, const IALG_Params *params)
{
    return;
} 

IALG_Fxns DUMRES_TI_IALG = {
    (Void *)&DUMRES_TI_IALG,
    IALG_ALGORITHM_Activate,
    IALG_ALGORITHM_Alloc,
    IALG_ALGORITHM_Control,
    IALG_ALGORITHM_Deactivate,
    IALG_ALGORITHM_Free,
    IALG_ALGORITHM_Init,
    IALG_ALGORITHM_Moved,
    IALG_ALGORITHM_NumAlloc
};
/*
 *  @(#) ti.sdo.fc.rman.examples.scratchedma3; 1, 0, 0,30; 12-1-2010 17:25:52; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

