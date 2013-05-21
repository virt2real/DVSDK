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
 *  ======== dman3_externalRM_api.c ========
 *  DMA Resource manager and utilities for granting logical channel
 *  resources to algorithms.
 */

#include <xdc/std.h>

#include <ti/bios/include/std.h>
#include <ti/bios/include/mem.h>
#include <ti/bios/include/lck.h>

#include <ti/sdo/fc/utils/dbc.h>
#include <ti/sdo/edma3/rm/edma3_rm.h>
#include <ti/sdo/fc/edma3/edma3_config.h>

#include "dman3.h"
#include "dman3_externalRM_impl.h"
#include "rmm.h"

#include <ti/xdais/idma3.h>
#include <ti/sdo/fc/utils/gtinfra/gt_dais.h>

#include <ti/sdo/edma3/rm/edma3_rm.h>
#include <ti/sdo/fc/edma3/edma3_config.h>

#define QCHMAPOFFSET 0x200

#pragma CODE_SECTION(DMAN3_grantDmaChannels, ".text:DMAN3_grantDmaChannels");
#pragma CODE_SECTION(DMAN3_releaseDmaChannels,".text:DMAN3_releaseDmaChannels");

#pragma CODE_SECTION(DMAN3_createChannels, ".text:DMAN3_createChannels");
#pragma CODE_SECTION(DMAN3_freeChannels, ".text:DMAN3_freeChannels");

extern LCK_Handle _DMAN3_lock;
extern EDMA3_RM_Handle _DMAN3_systemRMHandle;

extern Uint32 *_DMAN3_paRamAddr;
extern UInt32 *_DMAN3_edma3Addr;
extern UInt32 _DMAN3_nullPaRam;

/*
 *  ======== DMAN3_ChannelObj ========
 *  Structure to store a handle to the DMAN3 context object that
 *  was used to create the IDMA3 channel.
 */
typedef struct DMAN3_ChannelObj {
    IDMA3_Obj           idmaChan;
    DMAN3_Context       context;
    Int                 segEnv;  /* segment id where env is allocated */
    Uint16              sizeEnv; /* size of env */
} DMAN3_ChannelObj, *DMAN3_Channel;

/* Tracks if the external RM has been suitably and successfully iniitalized 
   or not */ 
static Int externalRMInit = 0; 
static Int initialized = 0;
static inline Int finalizeExternalRM(); 
static inline Int initializeExternalRM();

static Int  createChannels(IALG_Handle alg, Int groupId,
                           IDMA3_ChannelRec dmaTab[], Int numChans);
static Int createContext(DMAN3_Context *pContext, Int groupId);
static Void freeChannels(IDMA3_ChannelRec dmaTab[], Int numChan);
static Void freeContext(DMAN3_Context context);
static Void freeScratch(Int groupId, IALG_MemRec memTab[], Int numRecs);
static Int  getContext(DMAN3_Context *pContext, Int groupId, IALG_Handle alg);
static Bool initHandle(IDMA3_Handle handle, IDMA3_ChannelRec *dmaTab,
        Uint8 *tccList, Uns paRamAddr, Uns qdmaChannel, Int16 envSize, 
        Void *env, Void *scratchEnv, Int seg, DMAN3_Context context);
static Void freeResource(EDMA3_RM_Handle rmHandle, Uns qDmaChan, Uns numWaits, 
        unsigned char * tccTablePtr, Uns numPaRams, Uns paRamIndex);
static inline Void freeResourceManager (EDMA3_RM_Handle rmHandle, 
        IALG_Handle algHandle, Int groupId);

/*
 *  ======== DMAN3_createChannels ========
 *  Allocate and initialize memory for channel handle.
 *  What do I do in this case, algHandle is now NULL and groupId could be > 0
 *  Could store the algorithm as NULL  
 *  Allocate resources from the same handle for all dmaTab(s) in this call ?  
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int DMAN3_createChannels(Int groupId, IDMA3_ChannelRec dmaTab[], Int numChans)
{
    Int             i, j;
    Int             status = DMAN3_SOK;
    Uns             * gtPaRamAddr = NULL;

    DBC_require(groupId < DMAN3_MAXGROUPS);
    DBC_require(numChans >= 0);
    DBC_require((dmaTab != NULL) || (numChans == 0));
    GT_assert(ti_sdo_fc_dman3_GTMask, groupId < DMAN3_MAXGROUPS);
    GT_assert(ti_sdo_fc_dman3_GTMask, numChans >= 0);
    GT_assert(ti_sdo_fc_dman3_GTMask, (dmaTab != NULL) || (numChans == 0));

    GT_3trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_createChannels> Enter "
            "(groupId=%d, dmaTab=0x%x, numChans=%d\n", groupId, dmaTab,
            numChans);

    for (i = 0; i < numChans; i++) {
        dmaTab[i].handle = NULL;
    }


    if (0 == externalRMInit) {

        status = initializeExternalRM(); 

        if (status != DMAN3_SOK) {

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                    "DMAN3_createChannels> Error initializing Resource "
                    "Manager and allocating initial resources\n",status);

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
                    "DMAN3_createChannels> (status=%d)\n",status);

            return (status);
        }
    } 

    /* Now create the channels */
    status = createChannels(NULL, groupId, dmaTab, numChans);

    if (status == DMAN3_SOK) {

        for (i = 0; i < numChans; i++) {

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                    "DMAN3_createChannels> Assigned Qdma: %d\n",
                    dmaTab[i].handle->qdmaChan);

            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                    "DMAN3_createChannels> Assigned PaRam(s):\n");

            gtPaRamAddr = dmaTab[i].handle->paRamAddr;

            GT_2trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                    "DMAN3_createChannels> dmaTab[%d].handle's "
                    "paRamAddr 0x%x\n", i, gtPaRamAddr);

            for(j = 0; j < dmaTab[i].handle->numPaRams; j++) {

                GT_2trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                        "DMAN3_createChannels> %d (Addr 0x%x)\n",
                        ((Uns)gtPaRamAddr - (Uns)_DMAN3_paRamAddr) /
                        PARAMSIZEMAUS,
                        gtPaRamAddr);

                gtPaRamAddr -= (PARAMSIZE);
            }

            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                    "DMAN3_createChannels> Assigned Tcc(s):\n");

            for(j = 0; j < dmaTab[i].handle->numTccs; j++) {

                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                        "DMAN3_createChannels> %d\n",
                        dmaTab[i].handle->tccTable[j]);
            }
        }
    }

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_createChannels> Exit "
            "(returnVal=%d)\n",status);

    return (status);
}

/*
 *  ======== DMAN3_grantDmaChannels ========
 *  Add an algorithm to the DMA Manager.  The DMA Manager will grant DMA
 *  resources to the algorithm as a result.  This function is called when
 *  initializing an algorithm instance.
 *  Supporting this for only 1 algorithm (numAlgs = 1)
 */
/* ARGSUSED - Directive to compiler to not complain about unused args */
Int DMAN3_grantDmaChannels(Int groupId, IALG_Handle algHandle[],
        IDMA3_Fxns *dmaFxnsArray[], Int numAlgs)
{
    Uns              numChans;
    Int              j, k;
    IALG_Handle      alg;
    IDMA3_Fxns      *dmaFxns;
    IDMA3_ChannelRec *dmaTab;
    Int              maxChans = _DMAN3_MAXCHANS;
    Int              status = DMAN3_EFAIL;
    Uns             *gtPaRamAddr = NULL;

    DBC_require(algHandle != NULL);
    DBC_require(dmaFxnsArray != NULL);
    DBC_require(numAlgs == 1);
    DBC_require(groupId < DMAN3_MAXGROUPS);
    GT_assert(ti_sdo_fc_dman3_GTMask, algHandle != NULL);
    GT_assert(ti_sdo_fc_dman3_GTMask, dmaFxnsArray != NULL);
    GT_assert(ti_sdo_fc_dman3_GTMask, numAlgs == 1);
    GT_assert(ti_sdo_fc_dman3_GTMask, groupId < DMAN3_MAXGROUPS);

    GT_4trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_grantDmaChannels> "
            "Enter (groupId=%d, algHandle=0x%x, dmaFxns=0x%x, numAlgs=%d)\n",
            groupId, algHandle, dmaFxnsArray, numAlgs);

    if (1 != numAlgs) {
        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                "DMAN3_grantDmaChannels> API supported only for 1 algorithm at"
                " time when using an external Resource Manager.\n");
        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
                "DMAN3_grantDmaChannels> Exit (status=DMAN3_EOUTOFMEMORY)\n");
        return (DMAN3_EFAIL);
    }


    if (0 == externalRMInit) {


        status = initializeExternalRM(); 

        if (status != DMAN3_SOK) {

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                    "DMAN3_grantDmaChannels> Error initializing Resource "
                    "Manager and allocating initial resources\n",status);

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
                    "DMAN3_grantDmaChannels> (status=%d)\n",status);

            return (status);
        }
    } 

    /* use dynamic allocation instead of stack to avoid large array on stack */
    dmaTab = (IDMA3_ChannelRec *)MEM_calloc(_DMAN3_heapExt,
            sizeof(IDMA3_ChannelRec) * maxChans, sizeof(Int));


    if (dmaTab == MEM_ILLEGAL) {

        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
                "DMAN3_grantDmaChannels> Exit (status=DMAN3_EOUTOFMEMORY)\n");
        return (DMAN3_EOUTOFMEMORY);
    }

    alg = algHandle[0];
    dmaFxns = dmaFxnsArray[0];

    DBC_require(alg != NULL);
    DBC_require(dmaFxns != NULL);
    GT_assert(ti_sdo_fc_dman3_GTMask, alg != NULL);
    GT_assert(ti_sdo_fc_dman3_GTMask, dmaFxns != NULL);

    /*  alg and idma3 fxns must be from same implementation */
    DBC_require(dmaFxns->implementationId == alg->fxns->implementationId);
    GT_assert(ti_sdo_fc_dman3_GTMask, dmaFxns->implementationId ==
            alg->fxns->implementationId);
    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
            "DMAN3_grantDmaChannels> Alg 0x%x:\n", alg);

    GT_assert(ti_sdo_fc_dman3_GTMask,
            dmaFxns->implementationId == alg->fxns->implementationId);

    numChans = dmaFxns->dmaGetChannels(alg, dmaTab);

    status = createChannels(alg, groupId, dmaTab, numChans);

    if ((status == DMAN3_SOK)) {

        if ((status = dmaFxns->dmaInit(alg, dmaTab)) != IALG_EOK) {

            /* If dmaInit fails, free channel resources for alg[i] */
            freeChannels(dmaTab, numChans);

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                    "DMAN3_grantDmaChannels> Alg 0x%x dmaInit failed, "
                    "freeing channel resources\n", alg);

            status = DMAN3_EFAIL;
        }
        else {

            for (k = 0; k < numChans; k++) {

                /* Print out trace information */
                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                        "DMAN3_createChannels> Assigned Qdma: %d\n",
                        dmaTab[k].handle->qdmaChan);

                GT_0trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                        "DMAN3_createChannels> Assigned PaRam(s):\n");

                gtPaRamAddr = dmaTab[k].handle->paRamAddr;

                GT_2trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                        "DMAN3_createChannels> dmaTab[%d].handle's "
                        "paRamAddr 0x%x\n", k, gtPaRamAddr);

                for (j = 0; j < dmaTab[k].handle->numPaRams; j++) {

                    GT_2trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                            "DMAN3_createChannels> %d (Addr 0x%x)\n",
                            ((Uns)gtPaRamAddr - (Uns)_DMAN3_paRamAddr) /
                            PARAMSIZEMAUS, gtPaRamAddr);

                    gtPaRamAddr -= (PARAMSIZE);
                }

                GT_0trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                        "DMAN3_createChannels> Assigned Tcc(s):\n");

                for( j = 0; j < dmaTab[k].handle->numTccs; j++) {

                    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                            "DMAN3_createChannels> %d\n",
                            dmaTab[k].handle->tccTable[j]);
                }
            }
        }
    }

    MEM_free(_DMAN3_heapExt, dmaTab,
            sizeof(IDMA3_ChannelRec) * maxChans);

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_grantDmaChannels> Exit "
            "(status=%d)\n",status);

    return (status);
}

/*
 *  ======== DMAN3_freeChannels ========
 *  Free memory for channel handles in dmaTab[].
 */
/* ARGSUSED - Directive to compiler to not complain about unused args */
Int DMAN3_freeChannels(IDMA3_Handle channelTab[], Int numChan)
{
    Int             status = DMAN3_SOK;
    Int             i;
    IDMA3_Handle    chan;
    DMAN3_Context   context;
    DMAN3_Channel   dmanChan;
    Void           *scratchEnv;
    Uns             paRamAddr;
    Uns             paRamIndex;
#if DBC_ASSERTS
    Bool            fRet;
#endif

    DBC_require(numChan >= 0);
    DBC_require((channelTab != NULL) || (numChan == 0));
    GT_assert(ti_sdo_fc_dman3_GTMask, numChan >= 0);
    GT_assert(ti_sdo_fc_dman3_GTMask, (channelTab != NULL) || (numChan == 0));

    GT_2trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_freeChannels> Enter "
            " (channelTab=0x%x, numChan=%d)\n",channelTab, numChan);

    for (i = 0; i < numChan; i++) {

        chan = channelTab[i];
        DBC_require(chan != NULL);
        GT_assert(ti_sdo_fc_dman3_GTMask, chan != NULL);

        dmanChan = (DMAN3_Channel)chan;
        context = dmanChan->context;
        DBC_assert(context != NULL);
        GT_assert(ti_sdo_fc_dman3_GTMask, context != NULL);

        /* De-init the environment */
        if (chan->protocol && chan->protocol->deInitHandle) {

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "DMAN3_freeChannels> "
                    "Calling deinit on protocol on Channel %d\n", i);

#if DBC_ASSERTS
            fRet = chan->protocol->deInitHandle(chan);
            DBC_assert(fRet);
            GT_assert(ti_sdo_fc_dman3_GTMask, fRet);
#else
            chan->protocol->deInitHandle(chan);
#endif
        }

        /* Free 'env' buffer, but only if it has been allocated. */
        if ((dmanChan->sizeEnv > 0) && (chan->env != NULL)) {

            /*
             *  Free scratchEnv if it has been allocated. The deInit() function
             *  must put the scratch pointer back at the beginning of the env
             *  address.
             */
            scratchEnv = (Void *)(*(Uint32 *)(chan->env));

            if ((scratchEnv != NULL) && (_DMAN3_freeScratch != NULL)) {

                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                        "DMAN3_freeChannels> Free scratchEnv 0x%x\n",
                        scratchEnv);

                (_DMAN3_freeScratch)(context->scratchId, scratchEnv,
                        dmanChan->sizeEnv);
            }
            /* Get the memory segment for the environment */

#if DBC_ASSERTS
            fRet = MEM_free(dmanChan->segEnv, chan->env, dmanChan->sizeEnv);
            DBC_assert(fRet);
#else
            MEM_free(dmanChan->segEnv, chan->env, dmanChan->sizeEnv);
#endif

        }

        if (context->rmHandle != NULL) { 

            paRamAddr = (Uns)(chan->paRamAddr);
            
            paRamIndex = ((paRamAddr - (Uns)_DMAN3_paRamAddr)/PARAMSIZEMAUS) - 
                    chan->numPaRams + 1;

            freeResource(context->rmHandle, chan->qdmaChan, 
                    chan->numTccs, chan->tccTable, chan->numPaRams, paRamIndex);

            freeResourceManager(context->rmHandle, context->algHandle, 
                    context->groupId);

            context->rmHandle = NULL;
        }


        /* Release memory allocated for tcc Array and paRam array */ 
        MEM_free(_DMAN3_heapExt, chan->tccTable, chan->numTccs *  
                sizeof(unsigned char));

        /* Free DMAN3 channel object memory */
#if DBC_ASSERTS
        fRet = MEM_free(_DMAN3_heapIdma3, chan, sizeof(DMAN3_ChannelObj));
        DBC_assert(fRet);
#else
        MEM_free(_DMAN3_heapIdma3, chan, sizeof(DMAN3_ChannelObj));
#endif

        freeContext(context);

    }

    externalRMInit -= numChan; 

    if (0 == externalRMInit) {

        status = finalizeExternalRM(); 
    }

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_freeChannels> Exit "
            "(status=%d)\n", status);

    return (DMAN3_SOK);
}


/*
 *  ======== DMAN3_releaseDmaChannels ========
 *  Remove logical channel resources from an algorithm instance
 */
/* ARGSUSED - Directive to compiler to not complain about unused args */
Int DMAN3_releaseDmaChannels(IALG_Handle algs[], IDMA3_Fxns *dmaFxnsArray[],
        Int numAlgs)
{
    IALG_Handle         alg;
    IDMA3_Fxns         *dmaFxns;
    IDMA3_ChannelRec    *dmaTab;
    Uns                 nChans;
    Int                 i;
    Int                 maxChans = _DMAN3_MAXCHANS;

    DBC_require(algs != NULL);
    DBC_require(dmaFxnsArray != NULL);
    DBC_require(numAlgs > 0);
    GT_assert(ti_sdo_fc_dman3_GTMask, algs != NULL);
    GT_assert(ti_sdo_fc_dman3_GTMask, dmaFxnsArray != NULL);
    GT_assert(ti_sdo_fc_dman3_GTMask, numAlgs > 0);

    GT_3trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_releaseDmaChannels> "
            "Enter (algs=0x%x, dmaFxnsArray=0x%x, numAlgs=%d)\n", algs,
            dmaFxnsArray, numAlgs);

    /* use dynamic allocation instead of stack to avoid large array on stack */
    dmaTab = (IDMA3_ChannelRec *)MEM_calloc(_DMAN3_heapExt,
            sizeof(IDMA3_ChannelRec) * maxChans, sizeof(Int));

    if (dmaTab == MEM_ILLEGAL) {
        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
                "DMAN3_releaseDmaChannels> Exit (status=DMAN3_EOUTOFMEMORY\n");
        return (DMAN3_EOUTOFMEMORY);
    }

    for (i = 0; i < numAlgs; i++) {
        dmaFxns = dmaFxnsArray[i];
        alg = algs[i];

        DBC_require(dmaFxns->implementationId == alg->fxns->implementationId);
        GT_assert(ti_sdo_fc_dman3_GTMask,
                dmaFxns->implementationId == alg->fxns->implementationId);

        /*
         * In debug build verify that algo is not using two many buffers,
         * in release build trust that contract is respected
         */

        nChans = dmaFxns->dmaGetChannels(alg, dmaTab);


        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                "DMAN3_releaseDmaChannels> Free %d channels\n", nChans);

        freeChannels(dmaTab, nChans);

    }

    MEM_free(_DMAN3_heapExt, dmaTab,
        sizeof(IDMA3_ChannelRec) * maxChans);
    
    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_releaseDmaChannels> "
            "Exit (status=DMAN3_SOK)\n");

    return (DMAN3_SOK);
}


/*
 *  ======== createChannels ========
 *  One algorithm, multiple dmaTab(s). 
 */
static Int  createChannels(IALG_Handle alg, Int groupId,
        IDMA3_ChannelRec dmaTab[], Int numChans)
{
    Void           *env;
    Void           *scratchEnv;
    Int             envSize;
    Int             seg;
    Int             align;
    IDMA3_MemRec    memRec;
    IALG_MemRec    *memTab = NULL;
    IALG_MemAttrs   memType;
    Int             i, j;
    Uns             qDmaChan = (Uns)-1;
    Uint8          *tccTablePtr;
    Uns            paRamAddr;
    Bool            fRet;
    Int             status = DMAN3_SOK;
    Uns             * gtPaRamAddr = NULL;
    DMAN3_Context   context;
    Bool            scratch = TRUE;


    EDMA3_RM_Handle rmHandle = NULL;
    EDMA3_RM_Result rmStatus;
    EDMA3_RM_ResDesc resObj;

    Uns             qeesr = 0x0;
    Uns             *addr = 0x0;

    DBC_assert(dmaTab != NULL);

    GT_4trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "createChannels> Enter "
            "(alg=0x%x, groupId=%d, dmaTab=0x%x, numChans=%d)\n", alg, groupId,
            dmaTab, numChans);

    if (NULL == _DMAN3_systemRMHandle) {
        return (DMAN3_EFAIL);
    }

    /*
     *  Allocate array of memTab to be used if env can be allocated from
     *  shared scratch memory. Scratch memory for the alg has to be allocated
     *  all at once, so we need to collect the env memory requirements for
     *  each of the alg's channels. All sizes are initialized to 0 here.
     */

    memTab = (IALG_MemRec *)MEM_calloc(_DMAN3_heapExt,
            sizeof(IALG_MemRec) * numChans, sizeof(Int));

    if (memTab == MEM_ILLEGAL) {
        status = DMAN3_EOUTOFMEMORY;
    }
    else {

        /* Type of memory for env allocated in internal memory */
        memType = (_DMAN3_allocScratch != NULL) ? IALG_SCRATCH : IALG_PERSIST;

        /* Fill in memTab with each channels' env memory requirements */
        for (i = 0; i < numChans; i++) {

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels> "
                    "Channel %d\n", i);

            memTab[i].attrs = IALG_PERSIST;

            if (dmaTab[i].protocol && dmaTab[i].protocol->getEnvMemRec) {

                dmaTab[i].protocol->getEnvMemRec(&dmaTab[i], &memRec);
                memTab[i].size = memRec.size;
                memTab[i].alignment = memRec.align;

                /*
                 *  If memRec.memType = IDMA3_INTERNAL, we arbitrarily set the
                 *  space to IALG_DARAM0.
                 */
                if (memRec.memType == IDMA3_INTERNAL) {
                    memTab[i].space = IALG_DARAM0;
                    memTab[i].attrs = memType;
                }
                else {
                    memTab[i].space = IALG_EXTERNAL;
                }

                GT_5trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS, "createChannels>"
                        " Env Requested memTab[%d]: size=0x%x, align=0x%x, "
                        "space=%s, attrs=%s\n",i, memTab[i].size,
                        memTab[i].alignment, gt_MemAttrs(memTab[i].attrs),
                        gt_MemSpace(memTab[i].space));
            }
        }

        /* Allocate scratch env */
        if ((_DMAN3_allocScratch != NULL) &&
                !_DMAN3_allocScratch(alg, groupId, memTab, numChans)) {
            /*
             *  Don't fail if allocation in scratch memory failed. We will
             *  try to allocate in persistent memory.
             */
            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels> "
                    "Scratch Allocation failed\n");

            for (i = 0; i < numChans; i++) {
                memTab[i].attrs = IALG_PERSIST;
                memTab[i].base = MEM_ILLEGAL;
            }
        }
                else {
                        if ((_DMAN3_allocScratch != NULL) && (dmaTab[i].protocol)) {

                for (i = 0; i < numChans; i++) {

                                    GT_6trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS, 
                            "createChannels> Scratch Env Allocated memTab[%d]: "
                            "size=0x%x, align=0x%x, space=%s, attrs=%s, "
                            "base=0x%x\n",i, memTab[i].size,
                                        memTab[i].alignment, gt_MemAttrs(memTab[i].attrs),
                                        gt_MemSpace(memTab[i].space), memTab[i].base);
                                }
                        }
                }
    }

    if (status != DMAN3_SOK) {
        return (status);
    }

    /* Now we can start creating channels */
    for (i = 0; i < numChans; i++) {

        envSize = memTab[i].size;
        seg = (memTab[i].space == IALG_EXTERNAL) ? _DMAN3_heapExt :
                                                   _DMAN3_heapInt;
        align = memTab[i].alignment;
        scratchEnv = memTab[i].base; /* NULL unless allocated in scratch */

        GT_4trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels> "
                "Creating channel %d, size 0x%x, align 0x%x, scratchEnv 0x%x\n",
                i, envSize, align, scratchEnv);

        /*
         *  Align on word boundary to simplify accesses of IDMA3_Obj
         *  fields by assembly implementations of ACPY3. Allocate more
         *  than IDMA3_Obj, so we can store the context associated with
         *  this channel.
         */

        GT_4trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS, "createChannels> "
                "IDMA3 Object Requested mem[%d]: size=0x%x, align=0x%x "
                "heapId=%d\n", i, sizeof(DMAN3_ChannelObj), sizeof(Int),
                _DMAN3_heapIdma3);

        /* Get a new context. One is embedded in each handle. */
        status = getContext(&context, groupId, alg);

        dmaTab[i].handle = (IDMA3_Obj *)MEM_calloc(_DMAN3_heapIdma3,
                sizeof(DMAN3_ChannelObj), sizeof(Int));

        if (dmaTab[i].handle == MEM_ILLEGAL) {

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels> "
                    "Error allocating memory for channel %d\n", i);

            /*
             *  If we failed to create the first channel, then freeChannels()
             */
            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels>"
                        " Freeing context 0x%x\n",context);

            freeContext(context);

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels> "
                    "Freeing channels %d\n", i);

            /* Free up the channels that were already allocated. */
            freeChannels(dmaTab, i);

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels> "
                    "Freeing scratch memory of group %d\n", groupId);

            /* Free scratch memory not freed in call to freeChannels(). */
            freeScratch(groupId, memTab + i, numChans - i);

            status = DMAN3_EOUTOFMEMORY;
            break;
        }
        else {

                        ((DMAN3_ChannelObj *)(dmaTab[i].handle))->context = context;    

            /* If persistent handles are requested, use system handle,
               if scratch group resources are requested, obtain RM handle */
            if ((dmaTab[i].persistent == TRUE) ||( groupId == -1)) {
                rmHandle = _DMAN3_systemRMHandle;
                scratch = FALSE;
            }
            else {
                rmHandle = EDMA3_getResourceManager(alg, groupId);
            }

            if (NULL == rmHandle) {

                status = DMAN3_EFAIL;

                GT_2trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                        "createChannels> Error obtaining resource manager "
                        "handle for alg 0x%x and group %d\n", alg, groupId);

                /* Couldn't alloc RM resource or obtain RM handle */
                MEM_free(_DMAN3_heapIdma3, dmaTab[i].handle,
                        sizeof(DMAN3_ChannelObj));


                freeContext(context);

                /* free the channels created so far, including this one */
                freeChannels(dmaTab, i);

                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                        "createChannels> Free remaining scratch from "
                        "group %d\n", groupId);

                freeScratch(groupId, memTab + i, numChans - i);

                goto createChannelsEnd;
            }

            j = ((context->nextQdmaChannel++ - context->qdmaBase) % 
                    context->numQdmas) + context->qdmaBase;
            qDmaChan = DMAN3_QDMA[j].index; 


            /* Enabling the QDMA event corresponding to this channel */
            qeesr = 0x0;
            qeesr |= (0x1 << qDmaChan);
            addr = (UInt32 *)((UInt32)_DMAN3_edma3Addr + QEESROFFSET);

            /* Queue Event Enable Set register */
            (*addr) = qeesr;

            resObj.type = EDMA3_RM_RES_TCC;

            /* TODO check for error here */
            tccTablePtr = (Uint8 *)MEM_calloc(_DMAN3_heapExt,
                    sizeof(Uint8) * dmaTab[i].numWaits, sizeof(Int));

            for (j = 0; j < dmaTab[i].numWaits; j++) {

                resObj.resId = EDMA3_RM_RES_ANY;

                rmStatus = EDMA3_RM_allocResource(rmHandle, &resObj);

                if (EDMA3_RM_SOK != rmStatus) {

                    status = DMAN3_EOUTOFTCCS;

                    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                            "createChannels> Error allocating %d Tccs\n",
                            dmaTab[i].numWaits);                            

                    freeResource(rmHandle, qDmaChan, j, tccTablePtr, 
                            (Uns)-1, (Uns) -1);

                    MEM_free(_DMAN3_heapExt, tccTablePtr, 
                            sizeof(Uint8) * dmaTab[i].numWaits);

                    /* Release the RM Handle */
                    freeResourceManager(rmHandle, context->algHandle, 
                            context->groupId);

                    /* Couldn't alloc RM resource or obtain RM handle */
                    MEM_free(_DMAN3_heapIdma3, dmaTab[i].handle,
                            sizeof(DMAN3_ChannelObj));

                    freeContext(context);

                    /* free the channels created so far, including this one */
                    freeChannels(dmaTab, i);

                    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                            "createChannels> Free remaining scratch from "
                            "group %d\n", groupId);

                    freeScratch(groupId, memTab + i, numChans - i);

    
                    goto createChannelsEnd;
                }

                tccTablePtr[j] = resObj.resId;
            }

            resObj.type = EDMA3_RM_RES_PARAM_SET;
            resObj.resId = EDMA3_RM_RES_ANY;

            rmStatus = EDMA3_RM_allocContiguousResource(rmHandle, &resObj,
                    dmaTab[i].numTransfers);

            if (EDMA3_RM_SOK != rmStatus) {

                status = DMAN3_EOUTOFPARAMS;

                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                        "createChannels> Error allocating %d PaRams\n",
                        dmaTab[i].numTransfers);

                freeResource(rmHandle, qDmaChan, dmaTab[i].numWaits, 
                        tccTablePtr, (Uns)-1, (Uns)-1);

                /* Release the RM Handle */
                freeResourceManager(rmHandle, context->algHandle, 
                        context->groupId);

                MEM_free(_DMAN3_heapExt, tccTablePtr, 
                        sizeof(Uint8) * dmaTab[i].numWaits);

                /* Couldn't alloc RM resource or obtain RM handle */
                MEM_free(_DMAN3_heapIdma3, dmaTab[i].handle,
                        sizeof(DMAN3_ChannelObj));

                freeContext(context);

                /* free the channels created so far, including this one */
                freeChannels(dmaTab, i);

                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                        "createChannels> Free remaining scratch from "
                        "group %d\n", groupId);

                freeScratch(groupId, memTab + i, numChans - i);


                goto createChannelsEnd;
            }

            if (EDMA3_RM_SOK != EDMA3_RM_getPaRAMPhyAddr(rmHandle, &resObj,
                    &paRamAddr)) {

                status = DMAN3_EFAIL;

                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                        "createChannels> Error obtaining physical address of "
                        "allocated PaRam %d\n", resObj.resId);

                /* Note:- freeResource expects a paRam Index, not a PaRam 
                          Address */
                freeResource(rmHandle, qDmaChan, dmaTab[i].numWaits, 
                        tccTablePtr, dmaTab[i].numTransfers, resObj.resId);

                /* Release the RM Handle */
                freeResourceManager(rmHandle, context->algHandle, 
                        context->groupId);

                MEM_free(_DMAN3_heapExt, tccTablePtr, 
                        sizeof(Uint8) * dmaTab[i].numWaits);

                /* Couldn't alloc RM resource or obtain RM handle */
                MEM_free(_DMAN3_heapIdma3, dmaTab[i].handle,
                        sizeof(DMAN3_ChannelObj));

                freeContext(context);

                /* free the channels created so far, including this one */
                freeChannels(dmaTab, i);

                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                        "createChannels> Free remaining scratch from "
                        "group %d\n", groupId);

                freeScratch(groupId, memTab + i, numChans - i);


                goto createChannelsEnd;
            } 

            /* Allocate the 'env' buffer only when requested (i.e. > 0) */
            if ((envSize > 0)) {

                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels>"
                        " Env buffer of size 0x%x requested\n",envSize);

                /*
                 *  If we have env allocated in scratch, we need to allocate
                 *  a persistent copy in external memory.
                 */
                if (scratchEnv != NULL) {
                    seg = _DMAN3_heapExt;
                }

                env = MEM_calloc(seg, envSize, align);

            }
            else {

                env = NULL;
            }

            if ((envSize <= 0) || (env != MEM_ILLEGAL)) {
                //TODO: need for atomicity when reading/writing context? (nd)

                if (envSize > 0) {

                    GT_5trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                            "createChannels> Env Allocated memTab[%d]: "
                            "size=0x%x, align=0x%x, heapId=%d, base=0x%x\n", 
                            i, envSize, align, seg, env);
                }

                GT_0trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels>"
                        " Initializing IDMA3_handle\n");


                /*
                 * Initialize the IDMA3_Handle handle with resource allocation
                 * & channel state
                 */
                fRet = initHandle(dmaTab[i].handle, &dmaTab[i], tccTablePtr,
                        paRamAddr, qDmaChan, envSize, env, scratchEnv, 
                        seg, context);

                if (!fRet) {

                    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                            "createChannels> Error initializing IDMA3_handle, "
                            "freeChannels %d\n", i+1);

                    /* free the channels created so far, including this one */
                    freeChannels(dmaTab, i + 1);

                    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                            "createChannels> Free remaining scratch from "
                            "group %d\n", groupId);

                    /* Free remaining scratch */
                    freeScratch(groupId, memTab + i + 1, numChans - i - 1);

                    status = DMAN3_EFAIL;
                    break;
                }
                else {

                    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                            "createChannels> Assigned Qdma Channel(s):%d\n",
                            qDmaChan);

                    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                            "createChannels> Assigned PaRam(s):\n");

                    gtPaRamAddr = dmaTab[i].handle->paRamAddr;

                    GT_2trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                            "createChannels> dmaTab[%d].handle's "
                            "paRamAddr 0x%x\n", i, gtPaRamAddr);

                    for(j = 0; j < dmaTab[i].handle->numPaRams; j++) {

                        GT_2trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                                "createChannels> %d (Addr 0x%x)\n",
                                ((Uns)gtPaRamAddr - (Uns)_DMAN3_paRamAddr) /
                                PARAMSIZEMAUS,
                                gtPaRamAddr);

                        gtPaRamAddr -= (PARAMSIZE);
                    }

                    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                            "createChannels> Assigned Tcc(s):\n");

                    for (j = 0; j < dmaTab[i].handle->numTccs; j++) {
                        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                                "createChannels> %d\n",
                                dmaTab[i].handle->tccTable[j]);

                    }

                    context->rmHandle = rmHandle; 

                    externalRMInit ++;

                }
            }
            else {

                GT_0trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels> "
                        "Error allocating environment memory, freeing Channel "
                        "objects\n");

                /* Couldn't allocate env */
                MEM_free(_DMAN3_heapIdma3, dmaTab[i].handle,
                        sizeof(DMAN3_ChannelObj));

                freeResource(rmHandle, qDmaChan, dmaTab[i].numWaits, 
                        tccTablePtr, dmaTab[i].numTransfers, resObj.resId);

                /* Release the RM Handle */
                freeResourceManager(rmHandle, context->algHandle, 
                        context->groupId);

                MEM_free(_DMAN3_heapExt, tccTablePtr, 
                        sizeof(Uint8) * dmaTab[i].numWaits);

                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                        "createChannels> Free context 0x%x\n",context);

                freeContext(context);

                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                        "createChannels> Free Channels %d\n", i);

                freeChannels(dmaTab, i);

                /* Free remaining scratch */
                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                        "createChannels> Free scratch from group %d\n",
                        groupId);

                freeScratch(groupId, memTab + i, numChans - i);
                status = DMAN3_EOUTOFMEMORY;
                break;
            }
        }
    }

createChannelsEnd:

    if (memTab) {
        MEM_free(_DMAN3_heapExt, memTab, sizeof(IALG_MemRec) * numChans);
    }

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "createChannels> Exit "
            "(status=%d)\n",status);

    return (status);
}


/*
 *  ======== createContext ========
 */
static Int createContext(DMAN3_Context *pContext, Int groupId)
{
    DMAN3_Context   context;
    Int             status = DMAN3_SOK;

    GT_2trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "createContext> Enter "
            "(pContext=0x%x, groupId=%d)\n", pContext, groupId);

    *pContext = NULL;

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createContext> Allocate "
            "memory for the context\n");

    context = (DMAN3_Context)MEM_calloc(_DMAN3_heapExt,
            sizeof(DMAN3_ContextObj), sizeof(Int));

    if (context == MEM_ILLEGAL) {
        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createContext> Could "
                "not allocate memory for the context\n");
        status = DMAN3_EOUTOFMEMORY;
    }
    else {
        /* Initialize the context object */
        context->groupId = groupId;
        context->qdmaBase = _DMAN3_qdma(groupId); 
        context->numQdmas =  _DMAN3_numQdmaGroup(groupId);
        if (ti_sdo_fc_dman3_DMAN3_useCustomDma) {
            if (groupId == -1) {
                //If original request was for persistent resources, need to
                //allocate discrete resources 
                //Cannot reuse those resources
                ti_sdo_fc_dman3_DMAN3_numQdmaGroup[DMAN3_MAXGROUPS]--;
                _DMAN3_qdmaBase[DMAN3_MAXGROUPS]++;
            }
        }
        context->nextQdmaChannel = _DMAN3_qdmaCounter(groupId);
        _DMAN3_qdmaCounter(groupId)++;
        
        *pContext = context;
    }

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "createContext> Exit "
            "(status=%d)\n", status);

    return (status);
}


/*
 *  ======== freeChannels ========
 *  Free memory for channel handles in dmaTab[].
 */
static Void freeChannels(IDMA3_ChannelRec dmaTab[], Int numChan)
{
    Int             i;
    IDMA3_Handle    chan;

    GT_2trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "freeChannels> Enter "
            "(dmaTab=0x%x, numChan=%d)\n", dmaTab, numChan);

    for (i = 0; i < numChan; i++) {

        if ((chan = dmaTab[i].handle) != MEM_ILLEGAL) {

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "_freeChannels> "
                    "Freeing channel %d\n", chan);

            DMAN3_freeChannels(&chan, 1);

            dmaTab[i].handle = NULL;
        }
    }

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "freeChannels> Exit\n");
}


/*
 *  ======== freeContext ========
 *  Free context handle object that was used to start allocating from a fresh
 *  scratch allocation context.
 */
static Void freeContext(DMAN3_Context context)
{

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "_freeContext> Enter "
            "(context=0x%x)\n", context);


    MEM_free(_DMAN3_heapExt, context, sizeof(DMAN3_ContextObj));

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "freeContext> Freeing "
            "context memory size 0x%x\n", sizeof(DMAN3_ContextObj));

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "freeContext> Exit\n");
}


/*
 *  ======== freeScratch ========
 */
/**
 *  Free any scratch memory in memTab[].
 */
static Void freeScratch(Int groupId, IALG_MemRec memTab[], Int numRecs)
{
    Int             i;

    GT_3trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "freeScratch> Enter "
            "(groupId=%d, memTab=0x%x, numRecs=%d)\n", groupId, memTab,
            numRecs);

    if (_DMAN3_freeScratch != NULL) {


        for (i = 0; i < numRecs; i++) {
            if ((memTab[i].attrs == IALG_SCRATCH) && (memTab[i].size > 0)) {

                GT_2trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "freeScratch> "
                        "Freeing scratch memory 0x%x of size 0x%x\n",
                        memTab[i].base, memTab[i].size);

                _DMAN3_freeScratch(groupId, memTab[i].base, memTab[i].size);
                memTab[i].base = MEM_ILLEGAL;
            }
        }
    }

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "freeScratch> Exit\n");

}


/*
 *  ======== getContext ========
 *  Get context handle for groupId. (In the future, we might have a linked
 *  list of contexts for a given groupId, with varying amounts of TCCs and
 *  PaRams. Therefore, we pass nTccs and nPaRams to this function).
 * Cannot support allowUnShared here 
 */
static Int getContext(DMAN3_Context *pContext, Int groupId, 
        IALG_Handle algHandle)
{
    Int           scratchId = groupId;
    DMAN3_Context context   = NULL;
    Int status              = DMAN3_SOK;

    GT_2trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "getContext> Enter "
            "(pContext=0x%x, groupId=%d)\n", pContext, groupId);

    *pContext = NULL;

    status = createContext(&context, groupId);

    if (status != DMAN3_SOK) {

        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "getContext> Exit "
                "(status=%d)\n", status);
        return (status);
    }

    context->scratchId = scratchId;
    context->algHandle = algHandle;
    context->rmHandle = NULL;

    DBC_assert(context != NULL);

    *pContext = context;

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "getContext> Exit "
            "(status=DMAN3_SOK)\n");

    return (DMAN3_SOK);
}

/*
 *  ======== initHandle ========
 *  Initialize the IDMA3_Handle handle with resource allocation/channel state.
 */
static Bool initHandle(IDMA3_Handle handle, IDMA3_ChannelRec *dmaTab,
        Uint8 *tccList, Uns paRamAddr, Uns qdmaChannel, Int16 envSize, 
        Void *env, Void *scratchEnv, Int seg, DMAN3_Context context)
{
    Bool          fRet = TRUE;

    GT_6trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "initHandle> Enter "
            "(handle=0x%x, dmaTab=0x%x, qdmaChannel=%d, env=0x%x, "
            "scratchEnv=0x%x, context=0x%x)\n", handle, dmaTab, qdmaChannel,
            env, scratchEnv, context);

    handle->numTccs = dmaTab->numWaits;
    handle->numPaRams = dmaTab->numTransfers;
    handle->qdmaChan  = qdmaChannel;
    handle->env  = env;

    GT_5trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "initHandle> Initializing "
            "IDMA3 handle with %d tccs, %d PaRams, qdmaChannel %d, env 0x%x"
            "rmhandle 0x%x\n",
            handle->numTccs, handle->numPaRams, handle->qdmaChan, env,
            context->rmHandle);

    if (env) {

        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "initHandle> Non-zero "
                "env handle\n");

        DBC_assert(envSize > 0);
        *(Uint32 *)handle->env = (Uint32)scratchEnv;
    }

    handle->protocol = dmaTab->protocol;

    /* Keep these for when we free the channel */
    ((DMAN3_Channel)handle)->context = context;
    ((DMAN3_Channel)handle)->sizeEnv = envSize;
    ((DMAN3_Channel)handle)->segEnv = seg;

    /*
     *  Assign Physical PARAM Blocks:
     *  Grant "numTransfers" many PARAM blocks, but initialize handle with the
     *  address of the "last" PARAM block.
     */
        handle->paRamAddr = (Uns *)((paRamAddr) + 
            (PARAMSIZEMAUS * (dmaTab->numTransfers - 1)));
    /* handle->paRamAddr = (Uns *)paRamAddr;  */

    /* Note: TccTable is provided by the framework. */
    handle->tccTable = tccList;

    /* until first transfer gets started there is no transfer to wait. */
    handle->transferPending = 0;

    GT_2trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "initHandle> paRam block "
            "0x%x, tcc Table 0x%x\n", handle->paRamAddr, handle->tccTable);

    /* Call the protocol's init function. */
    if (dmaTab->protocol && dmaTab->protocol->initHandle) {

        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "initHandle> Call "
                "protocol Init function\n");

        fRet = dmaTab->protocol->initHandle(handle);
    }

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "initHandle> Exit "
            "(status=%d)\n", fRet);

    return (fRet);
}


static Void freeResource(EDMA3_RM_Handle rmHandle, Uns qdmaChan, Uns numTccs, 
        unsigned char * tccTable, Uns numPaRams, Uns paRamIndex)
{
    Int j = 0;

    EDMA3_RM_ResDesc resObj;
    EDMA3_RM_Result rmStatus = EDMA3_RM_SOK;


    /* Release PaRams */
    if (numPaRams != (Uns)-1) {

        resObj.type  = EDMA3_RM_RES_PARAM_SET;
        
        /* The channel handle points to the last PaRam assigned to this handle*/
        resObj.resId = paRamIndex; 
        rmStatus = EDMA3_RM_freeContiguousResource(rmHandle, &resObj, 
                numPaRams);
    
        DBC_assert(EDMA3_RM_SOK == rmStatus);
        GT_assert(ti_sdo_fc_dman3_GTMask, EDMA3_RM_SOK == rmStatus);
        
        if (EDMA3_RM_SOK != rmStatus) {
    
            /* Report error */
            GT_2trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                    "freeResource> Could not free %d PaRams starting "
                    "at %d\n", numPaRams, resObj.resId);
        }
    }

    if (numTccs != (Uns)-1) {

        resObj.type  = EDMA3_RM_RES_TCC;
    
        for (j = 0; j < numTccs; j++) {
    
            resObj.resId = tccTable[j]; 
    
            rmStatus = EDMA3_RM_freeResource(rmHandle, &resObj); 
    
            DBC_assert(EDMA3_RM_SOK == rmStatus);
            GT_assert(ti_sdo_fc_dman3_GTMask, EDMA3_RM_SOK == rmStatus);
    
            if (EDMA3_RM_SOK != rmStatus) {
    
                /* Report error */
                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                        "freeResource> Could not free TCC %d\n",
                        resObj.resId);
            }
        }
    }
}


static inline Void freeResourceManager (EDMA3_RM_Handle rmHandle, 
        IALG_Handle algHandle, Int groupId)
{
    EDMA3_RM_Result rmStatus = EDMA3_RM_SOK;

    /* Don't release the system handle, that is required to acquire/release 
       RM resources. */ 
    if (_DMAN3_systemRMHandle != rmHandle) {


        /* Release the RM Handle */
        rmStatus = EDMA3_releaseResourceManager(algHandle, groupId); 


        DBC_assert(EDMA3_RM_SOK == rmStatus);
        GT_assert(ti_sdo_fc_dman3_GTMask, EDMA3_RM_SOK == rmStatus);

        if (EDMA3_RM_SOK != rmStatus) {

            /* Report error */
            GT_2trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                    "freeResourceManager> Could not free Resource "
                "Manager handle corresponding to alg 0x%x in group %d"
                "\n", algHandle, groupId );
        }
    }
}

static inline Int finalizeExternalRM() 
{
    Int status; 

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "finalizeExternalRM> Enter\n");

    MEM_free(_DMAN3_heapExt, DMAN3_QDMA,
            sizeof(DMAN3_QdmaObj) * DMAN3_PARAMS.numQdmaChannels);

    if (EDMA3_SOK == EDMA3_releaseResourceManager(NULL, -1)) {
        status = DMAN3_SOK;
    }    
    else {
        status = DMAN3_EFAIL;
    }
    
    _DMAN3_systemRMHandle = NULL;

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "finalizeExternalRM> Exit "
            "(status=%d)\n", status);
    
    initialized = 0;

    return (status);
}

static inline Int initializeExternalRM()
{
    EDMA3_RM_ResDesc resObj;
    EDMA3_RM_Result  rmStatus = EDMA3_RM_SOK;
    Int i, chan;
    Uns cccfg = 0x0;
    Uns numQdma = 0;
    volatile Uns   *qchmap;
    Uns            *paRam;

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "initializeExternalRM> Enter\n"
            );

    _DMAN3_heapInt = DMAN3_PARAMS.heapInternal;
    _DMAN3_heapExt = DMAN3_PARAMS.heapExternal;

    _DMAN3_heapInt = (_DMAN3_heapInt == -1) ?
            _DMAN3_heapExt : _DMAN3_heapInt;
    _DMAN3_heapExt = (_DMAN3_heapExt == -1) ?
            _DMAN3_heapInt : _DMAN3_heapExt;
    _DMAN3_heapIdma3 = (DMAN3_PARAMS.idma3Internal) ?
            _DMAN3_heapInt : _DMAN3_heapExt;

    /* This is a fatal configuration error. */
    DBC_assert(_DMAN3_heapInt != -1);
    GT_assert(ti_sdo_fc_dman3_GTMask, _DMAN3_heapInt != -1);

    LCK_pend(_DMAN3_lock, -1);
        
    if (!(initialized)) {

        if (NULL != _DMAN3_systemRMHandle) {
    
            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS, "initializeExternalRM>"
                    " DMAN3_systemRMHandle should be NULL when first alg is " 
                    " granted resources!\n");
    
            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "initializeExternalRM>"
                    " (status=DMAN3_EFAIL)\n");
    
            LCK_post(_DMAN3_lock);
                
            return (DMAN3_EFAIL);
        } 
    
        _DMAN3_systemRMHandle = EDMA3_getResourceManager(NULL, -1);
    
        if (NULL == _DMAN3_systemRMHandle) {
    
            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS, "initializeExternalRM>"
                    " DMAN3_systemRMHandle could not be opened\n"); 
    
            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "initializeExternalRM> "
                    "(status=DMAN3_EFAIL)\n");

            LCK_post(_DMAN3_lock);
    
            return (DMAN3_EFAIL);
        }
    
        EDMA3_RM_getBaseAddress(_DMAN3_systemRMHandle, EDMA3_RM_CC_PHY_ADDR, 
                (unsigned int *)(&_DMAN3_edma3Addr)); 
    
        if (_DMAN3_edma3Addr == NULL) {
    
            LCK_post(_DMAN3_lock);

            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS, "initializeExternalRM>"
                    " DMAN3 base address could not be determined\n"); 
    
            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "initializeExternalRM> "
                    "(status=DMAN3_EFAIL)\n");
    
            return (DMAN3_EFAIL);
        }
    
        _DMAN3_paRamAddr = (Uns *)((Uns)_DMAN3_edma3Addr + PARAMOFFSET);
    
        /* Acquire a PaRam that will be the nullPaRamIndex */  
        resObj.type = EDMA3_RM_RES_PARAM_SET;
        resObj.resId = EDMA3_RM_RES_ANY;
    
        rmStatus = EDMA3_RM_allocResource(_DMAN3_systemRMHandle, &resObj);
    
        if (EDMA3_RM_SOK != rmStatus) {
    
            LCK_post(_DMAN3_lock);
    
            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS, "initializeExternalRM>"
                    " EDMA3 LLD-RM could not allocate the NULL PaRam Index."
                    " Resource not available !\n");
    
            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "initializeExternalRM> "
                    "(status=DMAN3_EFAIL)\n");
    
            return (DMAN3_EFAIL);
        }
    
        _DMAN3_nullPaRam = resObj.resId;
    
        DMAN3_QDMA = (DMAN3_QdmaObj *)MEM_calloc(_DMAN3_heapExt,
                sizeof(DMAN3_QdmaObj) * DMAN3_PARAMS.numQdmaChannels, 
                sizeof(Int));
    
        resObj.type = EDMA3_RM_RES_QDMA_CHANNEL;
        resObj.resId = EDMA3_RM_RES_ANY;
    
        for (i = 0; i < DMAN3_PARAMS.numQdmaChannels; i++) {
            resObj.resId = EDMA3_RM_RES_ANY;
            rmStatus = EDMA3_RM_allocResource(_DMAN3_systemRMHandle, &resObj);
    
            if (EDMA3_RM_SOK != rmStatus) {
    
                LCK_post(_DMAN3_lock);
    
                GT_0trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS, 
                        "initializeExternalRM> EDMA3 LLD-RM could not allocate "
                        "QDMA channels. Resource not available !\n");
    
                GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, 
                        "initializeExternalRM> (status=DMAN3_EFAIL)\n");
    
                        
                return (DMAN3_EFAIL);
            }
    
            DMAN3_QDMA[i].index = resObj.resId;
            DMAN3_QDMA[i].available = TRUE;
    
            /* Value of 0 implies this can be used as scratch or persistent 
               Value of >=1 implies it is being used as scratch */
            DMAN3_QDMA[i].scratch = 0;
        }
    
        /* Set qchmap to address of first QCHMAP register */
        qchmap = (volatile Uns *)((Uns)_DMAN3_edma3Addr + QCHMAPOFFSET);
    
        /* If channel belongs to DMAN3, point it to null param */ 
        for (i = 0; i < DMAN3_PARAMS.numQdmaChannels; i++) {
            chan = DMAN3_QDMA[i].index;
            qchmap[chan] = (Uns)(_DMAN3_nullPaRam << 5); 
        }
    
        /* CC configuration register */
        cccfg = _DMAN3_edma3Addr[1];
    
        /* Maximum number of QDMA channels on this device */
        numQdma = ((cccfg >>4) & 0x7) << 0x1;
    
        for (i = 0; i < numQdma; i++) {
            /* Even if channel doesnt' belong to DMAN3, but points to null param
               change trigger word to # 7 */ 
            if (_DMAN3_nullPaRam == ((*qchmap >> 5 ) & 0x1FF)) {
                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                        "_DMAN3_initImpl> Qdma channel %d is pointing to "
                        "the nullPaRam. Change its trigger word bit to 0x7 so "
                        "it doesn't get triggered when we modify the null "
                        "PaRam\n", i);
                *qchmap = *qchmap | (0x7 << 2);
            }
            qchmap++;
        }
    
        /*
         *  Set the static bit of opts field of the null PaRam, since
         *  QCHMAP may get set to this PaRam when the channel is
         *  activated/deactivated. (The opts field is the first word of the
         *  PaRam entry).
         */
        paRam = (Uns *)((Uns)_DMAN3_paRamAddr +
                (_DMAN3_nullPaRam * PARAMENTRYSIZE * sizeof(UInt32)));
    
        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "_DMAN3_initImpl> "
                "Setting static bit of null paRam (address = 0x%x)\n", paRam);
        *paRam |= 0x8;

        initialized = 1;
    }
         
    LCK_post(_DMAN3_lock);

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "initializeExternalRM> Exit "
            "(status=DMAN3_SOK)\n");

    return (DMAN3_SOK);
}
/*
 *  @(#) ti.sdo.fc.dman3; 1, 0, 4,300; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

