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
 *  ======== ires_algorithm_scpy.c ========
 */


#include <xdc/std.h>
#include <stdio.h>
#include "ires_algorithm.h"
#include <ti/sdo/fc/scpy/scpy.h>
#include <ti/sdo/linuxutils/cmem/include/cmem.h>

#define BUF_SIZE 4096
/*
 * TI's implementation of IALG
 */
Void IALG_ALGORITHM_Activate(IALG_Handle handle);
Int IALG_ALGORITHM_Alloc(const IALG_Params * params, IALG_Fxns ** fxns,
    IALG_MemRec memTab[]);
Int IALG_ALGORITHM_Control(IALG_Handle handle, IALG_Cmd cmd,
    IALG_Status *status);
Void IALG_ALGORITHM_Deactivate(IALG_Handle handle);
Int IALG_ALGORITHM_Free(IALG_Handle handle, IALG_MemRec * memrec);
Int IALG_ALGORITHM_Init(IALG_Handle handle1, const IALG_MemRec *memrecs,
    IALG_Handle handle2, const IALG_Params *params);
Void IALG_ALGORITHM_Moved(IALG_Handle handle1, const IALG_MemRec *memrecs,
    IALG_Handle handle2, const IALG_Params *params);
Int IALG_ALGORITHM_NumAlloc(Void);

static Void contextSave(IALG_Handle algHandle, Void *contextArgs);
static Void contextRestore(IALG_Handle algHandle, Void *contextArgs);

/* IALG_Fxns DUMALG_TI_IALG = */
#define IALGFXNS &DUMALG_TI_IALG,            \
    IALG_ALGORITHM_Activate,    \
    IALG_ALGORITHM_Alloc,       \
    IALG_ALGORITHM_Control,     \
    IALG_ALGORITHM_Deactivate,  \
    IALG_ALGORITHM_Free,        \
    IALG_ALGORITHM_Init,        \
    IALG_ALGORITHM_Moved,       \
    IALG_ALGORITHM_NumAlloc

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
    DUMALG_TI_Handle algHandle = (DUMALG_TI_Handle)handle;
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
    DUMALG_TI_Handle algHandle = (DUMALG_TI_Handle)handle;

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

    DUMALG_TI_Handle algHandle = (DUMALG_TI_Handle)handle;
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

    DUMALG_TI_Handle algHandle = (DUMALG_TI_Handle)handle;
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

    DUMALG_TI_Handle algHandle = (DUMALG_TI_Handle)handle;
    for (i = 0; i < NUM_RESOURCES; i++) {
        algHandle->resourceState[i] = 0;
        algHandle->resourceHandles[i] =
            (IRES_SDMA_Handle)resourceDescriptor[i].handle;
    }

    algHandle->yieldFxn =   yieldFxn;
    algHandle->yieldArgs =  yieldArgs;
    (algHandle->yieldContext).contextSave = contextSave;
    (algHandle->yieldContext).contextRestore = contextRestore;
    (algHandle->yieldContext).contextArgs = &(algHandle->contextArgs);
        (algHandle->yieldContext).algHandle = (IALG_Handle)algHandle;
        (algHandle->yieldContext).resourceHandle = (IRES_Handle)algHandle->resourceHandles[0];
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
    DUMALG_TI_Handle algHandle = (DUMALG_TI_Handle)handle;

    for (i = 0; i < NUM_RESOURCES; i++) {
        algHandle->resourceState[i] = 0;
        algHandle->resourceHandles[i] = (IRES_SDMA_Handle)NULL;
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
    DUMALG_TI_Handle algHandle = (DUMALG_TI_Handle)handle;

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
    DUMALG_TI_Handle algHandle = (DUMALG_TI_Handle)handle;

    for (i = 0; i < NUM_RESOURCES; i++) {

        resourceDescriptors[i].resourceName = IRES_SDMA_PROTOCOLNAME;
        resourceDescriptors[i].revision = &IRES_SDMA_PROTOCOLREVISION;

        algHandle->protocolArgs[i].base.size = sizeof(IRES_SDMA_ProtocolArgs);
        algHandle->protocolArgs[i].base.mode = IRES_SCRATCH;

        GT_1trace(ti_sdo_fc_rman_examples_sdma, GT_4CLASS,
                "IRES_ALGORITHM_getResourceDescriptors> Requested a Logical "
                "Channel in Descriptor %d\n", i);

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
IRES_Fxns DUMALG_TI_IRES = {
    (void *)&DUMALG_TI_IRES,
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
Int IALG_ALGORITHM_Alloc(const IALG_Params * algParams, IALG_Fxns ** fxns,
    IALG_MemRec memTab[])
{
    const IDUMALG_Params * params = (Void *)algParams;

    memTab[0].size = sizeof(DUMALG_TI_Obj);
    memTab[0].alignment = 4;
    memTab[0].space = IALG_DARAM0;
    memTab[0].attrs = IALG_PERSIST;

    if (NULL == params) {
        params = &IDUMALG_PARAMS;
    }

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
    DUMALG_TI_Handle algHandle = (DUMALG_TI_Handle)handle;
    GT_1trace(ti_sdo_fc_rman_examples_sdma, GT_4CLASS,
            "IALG_ALGORITHM_Deactivate> Called Deactivate for task %d\n",
            algHandle->taskId);
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
    IRES_SDMA_Properties resourceProperties;
    DUMALG_TI_Handle algHandle = (DUMALG_TI_Handle)handle;

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
    DUMALG_TI_Handle algHandle = (DUMALG_TI_Handle)handle;
    GT_1trace(ti_sdo_fc_rman_examples_sdma, GT_4CLASS,
            "IALG_ALGORITHM_Activate> Called Activate for task %d\n",
            algHandle->taskId);
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
    DUMALG_TI_Handle alg = (Void *)handle;
    memrec[0].base = alg;
    return (NUM_ALLOC);
}


/*
 * ===== IALG_ALGORITHM_Init ======
 *
 * Initialize the algorithm
 * We know there is only one resource request
 * Use the passed param to determine which SDMA resource the algorithm requires
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IALG_ALGORITHM_Init(IALG_Handle handle, const IALG_MemRec *memrecs,
    IALG_Handle parent, const IALG_Params *params)
{
    IDUMALG_Params * myParams  = (IDUMALG_Params *)params;
    DUMALG_TI_Handle dumHandle = (DUMALG_TI_Handle)handle;
    dumHandle->yieldFlag = myParams->yieldFlag;
    dumHandle->taskId = myParams->taskId;

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

/* IBUFALG functions */

IDUMALG_Params IDUMALG_PARAMS = {
    sizeof(IDUMALG_Params),
    (2) };

/*
 * ===== useSDMA ======
 *
 *
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int DUMALG_TI_useSDMA(IDUMALG_Handle handle,unsigned int Id)
{
    Int i;
    DUMALG_TI_Obj * dumalg = (DUMALG_TI_Handle)handle;
    IRES_SDMA_Properties properties;
    CMEM_AllocParams cmem_params;
    Int ret;
    unsigned *src_addr;
    unsigned *dest_addr;
    unsigned *dest2_addr;
    SCPY_AddrParams src = {OMAP_DMA_AMODE_POST_INC, 0, 0, 0};
    SCPY_AddrParams dest = {OMAP_DMA_AMODE_POST_INC, 0, 0, 0};
    SCPY_TransferParams trans_params = {OMAP_DMA_DATA_TYPE_S32, BUF_SIZE / 4, 1};
    SCPY_Params scpy_params;
    SCPY_AddrParams dest2 = {OMAP_DMA_AMODE_POST_INC, 0, 0, 0};
    SCPY_Params scpy2_params;

    cmem_params.type = CMEM_POOL;
    cmem_params.flags = CMEM_NONCACHED;

    ret = CMEM_init();

    src_addr = (unsigned *)CMEM_alloc(BUF_SIZE, &cmem_params);
    dest_addr = (unsigned *)CMEM_alloc(BUF_SIZE, &cmem_params);
    dest2_addr = (unsigned *)CMEM_alloc(BUF_SIZE, &cmem_params);

    for (i = 0; i < NUM_RESOURCES; i++) {

        GT_1trace(ti_sdo_fc_rman_examples_sdma, GT_4CLASS, "DUMALG_TI_useSDMA> "
                "Using Logical Channel %d\n",
                dumalg->resourceHandles[i]->channel->chanNum);

        (*(IRES_Handle)(dumalg->resourceHandles[i])).getStaticProperties(
                    (IRES_Handle)dumalg->resourceHandles[i],
                    (IRES_Properties *)&properties);

        GT_5trace(ti_sdo_fc_rman_examples_sdma, GT_4CLASS, "DUMALG_TI_useSDMA> "
                "Resource # %d Properties: DMA4_CCR 0x%x, DMA4_CLNK_CTRL 0x%x,"
                " ... DMA4_CSR 0x%x, DMA_COLOR 0x%x\n", i,
                properties.globalRegs->DMA4_CCR,
                properties.globalRegs->DMA4_CLNK_CTRL,
                properties.globalRegs->DMA4_CSR,
                properties.globalRegs->DMA4_COLOR);
    }


    for (i = 0; i < ((int)BUF_SIZE / 4); i++) {
        src_addr[i] = 0xC0FFEE00;
    }

    /* Fill buffer with DEADBEEF */
    for (i = 0; i < ((int)BUF_SIZE / 4); i++) {
        dest_addr[i] = 0xDEADBEEF;
    }

    /* Fill buffer with DEADBEEF */
    for (i = 0; i < ((int)BUF_SIZE / 4); i++) {
        dest2_addr[i] = 0xDEADBEEF;
    }


    src.addr = (unsigned)src_addr;
    dest.addr = (unsigned)dest_addr;
    scpy_params.src = &src;
    scpy_params.dst = &dest;
    scpy_params.transfer = &trans_params;

    dest2.addr = (unsigned)dest2_addr;
    scpy2_params.src = &src;
    scpy2_params.dst = &dest2;
    scpy2_params.transfer = &trans_params;

    SCPY_init();

    SCPY_configure(dumalg->resourceHandles[0], &scpy_params);
    SCPY_configure(dumalg->resourceHandles[1], &scpy2_params);

    /* Fill buffer with C0FFEE */
    SCPY_start(dumalg->resourceHandles[0]);
    SCPY_start(dumalg->resourceHandles[1]);


    SCPY_wait(dumalg->resourceHandles[0]);

    printf("Buffer 1 contents:\n");

    /* Check for C0FFEE */
    for(i = 0; i < ((int)BUF_SIZE / 4); i++) {
        printf("%x:%d\t", dest_addr[i], i);
    }

    /* Fill buffer with DEADBEEF */
    for (i = 0; i < ((int)BUF_SIZE / 4); i++) {
            dest_addr[i] = 0xDEADBEEF;
    }

    SCPY_configure(dumalg->resourceHandles[0], &scpy_params);

    /* Fill buffer with C0FFEE */
    SCPY_start(dumalg->resourceHandles[0]);

    SCPY_wait(dumalg->resourceHandles[0]);

    printf("Buffer 1 contents again:\n");
    /* Check for C0FFEE */
    for(i = 0; i < ((int)BUF_SIZE / 4); i++) {
        printf("%x:%d\t", dest_addr[i], i);
    }

    SCPY_wait(dumalg->resourceHandles[1]);

    printf("Buffer 2 contents:\n");

    /* Check for C0FFEE */
    for (i = 0; i < ((int)BUF_SIZE / 4); i++) {
            printf("%x:%d\t", dest2_addr[i], i);
    }

    SCPY_exit();

    CMEM_exit();

    return (0);
}

/* ARGSUSED - this line tells the compiler not to warn about unused args. */
static Void contextSave(IALG_Handle algHandle, Void *contextArgs)
{
    DUMALG_TI_Handle handle = (DUMALG_TI_Handle)algHandle;
    GT_1trace(ti_sdo_fc_rman_examples_sdma, GT_4CLASS,
            "contextSave> Saving SDMA context for task %d\n", handle->taskId);
}

/* ARGSUSED - this line tells the compiler not to warn about unused args. */
static Void contextRestore(IALG_Handle algHandle, Void *contextArgs)
{
    DUMALG_TI_Handle handle = (DUMALG_TI_Handle)algHandle;
    GT_1trace(ti_sdo_fc_rman_examples_sdma, GT_4CLASS,
            "contextRestore> Restoring SDMA context for task %d\n",
            handle->taskId);
}

/*
 * TI's implementation of IDUMALG
 */
IDUMALG_Fxns DUMALG_TI_IDUMALG = {
    {IALGFXNS},
    DUMALG_TI_useSDMA
};

/*
 * DUMALG_TI_IALG
 * This structure defines TI's implementation of IALG interface
 */
/*  asm("_DUMALG_TI_IALG .set _DUMALG_TI_IDUMALG");*/
IALG_Fxns DUMALG_TI_IALG =  {
    IALGFXNS,
};
/*
 *  @(#) ti.sdo.fc.rman.examples.sdma; 1, 0, 0,132; 12-1-2010 17:25:55; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

