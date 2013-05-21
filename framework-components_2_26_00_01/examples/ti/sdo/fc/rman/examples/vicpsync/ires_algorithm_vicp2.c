/* 
 *  Copyright 2010
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * 
 */
/**
 *  @file       ti/sdo/fc/ires/vicp/test/ires_algorithm_vicp2.c 
 *
 *  @brief      Dummy implementation of the IRES interfaces by an algorithm  
 *
 */

#include <xdc/std.h>
#include <string.h>
#include <stdio.h>

#include "ires_algorithm_vicp2.h"
#include <ti/sdo/linuxutils/cmem/include/cmem.h>
#include <ti/sdo/fc/vicpsync/vicpsync.h>

/*
 * ===== IRES_ALGORITHM_numResourceDescriptors =====
 *
 * Returns number of different resource types the algorithm needs.
 * Part of IRES interface 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int32 IRES_ALGORITHM_numResourceDescriptors(IALG_Handle handle) 
{
    return (NUM_RESOURCES);
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
    Int i = 0;
    Int j = 0;
    unsigned int addr;
    unsigned int numBufs;
    IRES_VICP2_Handle res;
#ifdef xdc_target__os_Linux
    unsigned int tempAddr = 0x0;
    CMEM_init();
#endif

    DUMRES_TI_Handle algHandle = (DUMRES_TI_Handle)handle;
    for (i = 0; i < NUM_RESOURCES; i++) {
        res = ((IRES_VICP2_Handle)resourceDescriptor[i].handle);
        algHandle->resourceState[i] = 0;
        algHandle->resourceHandles[i] = res;
        /* Print resources granted */
        for (j = 0; j < IRES_VICP2_NUMBUFFERS; j++) {
            addr = res->assignedIMCOPBuffers[j];
            if (addr != 0xFFFFFFFF) {

                printf("Resource #%d: VICP2 Buffer #%d: Addr 0x%x\n",i,j,addr);

#ifdef xdc_target__os_Linux
                tempAddr = (unsigned long)CMEM_getPhys((void *)addr);
                printf("Resource #%d: VICP2 Buffer #%d: PHY Addr 0x%x\n",i,j,
                        tempAddr);
#endif
            }
        }

        numBufs = res->numMemBufs;
        for (j = 0; j < numBufs; j++) {

            printf("Resource #%d: Mem Buffer #%d: Addr 0x%x Size 0x%x\n", i, j, 
                    res->assignedMemAddrs[j], res->assignedMemSizes[j]); 
#ifdef xdc_target__os_Linux
            tempAddr = (unsigned long) CMEM_getPhys((void *)
                    (res->assignedMemAddrs[j]));
            printf("Resource #%d: VICP2 Buffer #%d: PHY Addr 0x%x\n",
                    i,j, tempAddr);
#endif
        } 
    }
#ifdef xdc_target__os_Linux
    CMEM_exit();
#endif
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
        algHandle->resourceHandles[i] = (IRES_VICP2_Handle)NULL;
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
    Int j = 0;
    DUMRES_TI_Handle algHandle = (DUMRES_TI_Handle)handle;
    unsigned int bufreq = 0x0;

    for (i = 0; i < NUM_RESOURCES; i++) {

        bufreq = 0;
        resourceDescriptors[i].resourceName = IRES_VICP2_PROTOCOLNAME;
        resourceDescriptors[i].revision = &IRES_VICP2_PROTOCOLREVISION;
        algHandle->protocolArgs[i].size = sizeof(IRES_VICP2_ProtocolArgs);
        algHandle->protocolArgs[i].mode = IRES_SCRATCH; 
        algHandle->protocolArgs[i].requestIMX0 = 1;
#ifdef DM365
        algHandle->protocolArgs[i].requestIMX1 = 1; //IMX1 for DM365 only
#else
        algHandle->protocolArgs[i].requestIMX1 = 0; 
#endif
        algHandle->protocolArgs[i].requestMJCP = (i%2);
#ifdef DM365
        algHandle->protocolArgs[i].requestNSF = 1;  //NSF only for DM365
#else
        algHandle->protocolArgs[i].requestNSF = 0;  
#endif

        if (algHandle->protocolArgs[i].requestIMX0) {
            printf("Res #%d, Requested IMXO \n", i);
        }
        if (algHandle->protocolArgs[i].requestIMX1) {
            printf("Res #%d, Requested IMX1 \n", i);
        }
        if (algHandle->protocolArgs[i].requestMJCP) {
            printf("Res #%d, Requested MJCP \n", i);
        }
        if (algHandle->protocolArgs[i].requestNSF) {
            printf("Res #%d, Requested NSF \n", i);
        }

        /* Request specific buffers */

        if (!(i%2)) {

            bufreq |= (0x1 << IMCOP_BUFFER_IMGBUF_A);
            bufreq |= (0x1 << IMCOP_BUFFER_IMGBUF_E);
            bufreq |= (0x1 << IMCOP_BUFFER_SEQUENCERPMEM);
            bufreq |= (0x1 << IMCOP_BUFFER_IMGBUF_B);
            bufreq |= (0x1 << IMCOP_BUFFER_IMGBUF_D);
            bufreq |= (0x1 << IMCOP_BUFFER_IMX0CMDBUF);
            algHandle->protocolArgs[i].requestIMCOPBuffers = bufreq;
    
            printf("Res #%d, request VICP2 Buffers 0x%x\n", i, bufreq);
            algHandle->protocolArgs[i].numMemoryRequests = 0;
        }
        else {

            algHandle->protocolArgs[i].requestIMCOPBuffers = bufreq;
            /* Request memory chunks */ 
            algHandle->protocolArgs[i].numMemoryRequests = 3;
            algHandle->protocolArgs[i].memRequestSizes[0] = 0x1000; 
            algHandle->protocolArgs[i].memRequestSizes[1] = 0x0500; 
            algHandle->protocolArgs[i].memRequestSizes[2] = 0x0111; 
    
            for (j = 0; j < algHandle->protocolArgs[i].numMemoryRequests; j++) {
                printf("Res #%d, request Mem Buffers of size 0x%x\n", i, 
                        algHandle->protocolArgs[i].memRequestSizes[j]);
            }  
    
        }
        resourceDescriptors[i].protocolArgs =
                    (IRES_ProtocolArgs *)&(algHandle->protocolArgs[i]);
        resourceDescriptors[i].handle = 
                (IRES_Handle)algHandle->resourceHandles[i];
    }

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
    IRES_VICP2_Properties resourceProperties;
    DUMRES_TI_Handle algHandle = (DUMRES_TI_Handle)handle;

    VICPSYNC_Status vicpStat;
    VICPSYNC_ResourceType res = VICPSYNC_MJCP;
    VICPSYNC_InterruptType intType = VICPSYNC_IRQ;
    VICPSYNC_InterruptLine intLine = VICPSYNC_FIXED;
    Int doneCount = 20;

    Bool done = FALSE;

    (*(IRES_Handle)(algHandle->resourceHandles[0])).getStaticProperties(
            (IRES_Handle)algHandle->resourceHandles[0],
            (IRES_Properties *)&resourceProperties);

#ifdef DM365
/* For DM365 only */
    printf("Testing for IMX1 , flexible, IRQ on res# 0\n"); 
    res = VICPSYNC_IMX1;
    intLine = VICPSYNC_FLEXIBLE;
    vicpStat = VICPSYNC_start(handle, res, intType, intLine, 
            algHandle->resourceHandles[0]);
    if (vicpStat != VICPSYNC_OK) {
        printf("Error configuring IMX1, IRQ on Res 0\n");
    }
/* DOn't know how to trigger this */
/*      VICPSYNC_wait(algHandle->resourceHandles[0], res);*/
    
    /* Test fixed line */
    printf("Testing for NSF, fixed, IRQ on res# 0\n"); 
    res = VICPSYNC_NSF;
    intLine = VICPSYNC_FIXED;
    vicpStat = VICPSYNC_start(handle, res, intType, intLine, 
            algHandle->resourceHandles[0]);

    if (vicpStat != VICPSYNC_OK) {
        printf("Error configuring NSF, IRQ on Res 0\n");
    }
 
/* DOn't know how to trigger this */
/*      VICPSYNC_wait(algHandle->resourceHandles[0], res);*/

    printf("Testing for IMX0 , fixed, IRQ on res# 1\n");
    res = VICPSYNC_IMX0;
    vicpStat = VICPSYNC_start(handle, res, intType, intLine, 
            algHandle->resourceHandles[1]);

    if (vicpStat != VICPSYNC_OK) {
        printf("Error configuring IMX0, IRQ on Res 1\n");
    }
 
/* DOn't know how to trigger this */
/*      VICPSYNC_wait(algHandle->resourceHandles[1], res);*/
#endif

    printf("Testing for MJCP, fixed, IRQ on res# 1\n");
    res = VICPSYNC_MJCP;
    vicpStat = VICPSYNC_start(handle, res, intType, intLine, 
            algHandle->resourceHandles[1]);

    if (vicpStat != VICPSYNC_OK) {
        printf("Error configuring MJCP, IRQ on Res 1\n");
    }
 
    printf("TRIGGER MJCP INTERRUPT NOW... \n"); 
    VICPSYNC_wait(algHandle->resourceHandles[1], res);
      
    printf("Test bad flexible line (should be rejected by VICPSYNC)\n");
    res = VICPSYNC_MJCP;
    intLine = VICPSYNC_FLEXIBLE;
    vicpStat = VICPSYNC_start(handle, res, intType, intLine, 
            algHandle->resourceHandles[1]);
    /* This should be a bad status */
    if (vicpStat == VICPSYNC_OK) {
        printf("Error should not be able to configure MJCP, IRQ, FLEX on "
                "Res 1\n");
    }

    printf("Test multiple calls to a busy line, should block etc \n");
    res = VICPSYNC_MJCP;
    intLine = VICPSYNC_FIXED;
    vicpStat = VICPSYNC_start(handle, res, intType, intLine, 
            algHandle->resourceHandles[1]);

    if (vicpStat != VICPSYNC_OK) {
        printf("Error configuring MJCP, IRQ on Res 1\n");
    }

    /* Check with Rob, if this is the way to do it !*/
    
    printf("TRIGGER MJCP INTERRUPT NOW... \n"); 
    VICPSYNC_wait(algHandle->resourceHandles[1], res);

    printf("Test call to a resource not owned \n");
    //MJCP not owned by resourceHandle[0]
    vicpStat = VICPSYNC_start(handle, VICPSYNC_MJCP, intType, intLine, 
            algHandle->resourceHandles[0]);

    /* This should be a bad status */    
    if (vicpStat == VICPSYNC_OK) {
        printf("Error should not be able to configure IMX0, IRQ on Res 0\n");
    }

    res = VICPSYNC_MJCP;        
    printf("Test done call ?!\n"); 
    vicpStat = VICPSYNC_start(handle, res, intType, intLine, 
            algHandle->resourceHandles[1]);

    if (vicpStat != VICPSYNC_OK) {
        printf("Error configuring MJCP, IRQ on Res 1\n");
    }

    while (!(done)) {
        done = VICPSYNC_done(algHandle->resourceHandles[1], res);
        if (!(doneCount)) {
            printf("TRIGGER MJCP INTERRUPT NOW... (and press enter) \n"); 
            getchar();
        }
        doneCount--;
    }

/* Don't know how to trigger this one */
    printf("Test flexible line\n"); 
    res = VICPSYNC_NSF;
    intLine = VICPSYNC_FLEXIBLE;

/* This will block, as we haven't triggered the first one yet
    vicpStat = VICPSYNC_start(handle, res, intType, intLine, 
            algHandle->resourceHandles[1]);
*/

    if (vicpStat != VICPSYNC_OK) {
        printf("Error configuring NSF, IRQ, FLEX on Res 1\n");
    }
    
    /* Don't know how to trigger this */
/*      VICPSYNC_wait(algHandle->resourceHandles[1], res);*/
 
 
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
 *  @(#) ti.sdo.fc.rman.examples.vicpsync; 1, 0, 0,101; 12-1-2010 17:26:01; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

