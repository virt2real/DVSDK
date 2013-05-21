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
 *  ======== dman3_api.c ========
 *  DMA Resource manager and utilities for granting logical channel
 *  resources to algorithms.
 */

#include <xdc/std.h>


#include "dman3.h"
#include "dman3_impl.h"
#include "rmm.h"


#ifdef xdc_target__isaCompatible_64P

#include <ti/sdo/fc/utils/dbc.h>
#include <ti/bios/include/mem.h>

#else
#include "bios_rts.h"
#endif

#include <ti/xdais/idma3.h>
#include <ti/sdo/fc/utils/gtinfra/gt_dais.h>

#ifdef __TI_COMPILER_VERSION__

#pragma CODE_SECTION(DMAN3_grantDmaChannels, ".text:DMAN3_grantDmaChannels");
#pragma CODE_SECTION(DMAN3_releaseDmaChannels,".text:DMAN3_releaseDmaChannels");

#pragma CODE_SECTION(DMAN3_createChannels, ".text:DMAN3_createChannels");
#pragma CODE_SECTION(DMAN3_freeChannels, ".text:DMAN3_freeChannels");

#endif

extern Uint32 *_DMAN3_paRamAddr;
extern Int _DMAN3_initStatus;

/*
 *  Number of words and MAUs in one PaRam entry. PARAMSIZEMAUS should be
 *  sizeof(ACPY3_PaRamRegs), but use #define since we can't include ACPY3
 *  header file here.
 */
#define PARAMSIZE 8
#define PARAMSIZEMAUS (PARAMSIZE * sizeof(Int))

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


static Int  createChannels(DMAN3_Context context, IALG_Handle alg, Int groupId,
                           IDMA3_ChannelRec dmaTab[], Int numChans);
static Int  createContext(DMAN3_Context *pContext, Int groupId, Int nTccs,
                       Int nPaRams, Int scratchId);
static Void freeChannels(IDMA3_ChannelRec dmaTab[], Int numChan);
static Void freeContext(DMAN3_Context context);
static Void freeScratch(Int groupId, IALG_MemRec memTab[], Int numRecs);
static Int  getContext(DMAN3_Context *pContext, Int groupId, Int nTccs,
                       Int nPaRams);
static Bool initHandle(IDMA3_Handle handle, IDMA3_ChannelRec *dmaTab,
                       Uint8 *tccList, Uns qdmaChannel,
                       Int16 envSize, Void *env, Void *scratchEnv, Int envSeg,
                       DMAN3_Context context);


/*
 *  ======== DMAN3_createChannels ========
 *  Allocate and initialize memory for channel handle.
 */
Int DMAN3_createChannels(Int groupId, IDMA3_ChannelRec dmaTab[], Int numChans)
{
    Int             i, j;
    DMAN3_Context   context;
    Int             maxWaits = 0;
    Int             maxTransfers = 0;
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

    if (!(_DMAN3_initStatus)) {

        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                "DMAN3_createChannels> DMAN3 initialization failed.\n");

        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
                "DMAN3_createChannels> Exit (status=DMAN3_EFAIL)\n");
        return (DMAN3_EFAIL);
    }

    /*
     *  Get the maximum number of waits and transfers to see how many
     *  PaRams and TCCs are needed.
     */
    for (i = 0; i < numChans; i++) {
        DBC_require(dmaTab[i].numWaits >= 0);
        DBC_require(dmaTab[i].numTransfers > 0);
        GT_assert(ti_sdo_fc_dman3_GTMask, dmaTab[i].numWaits >= 0);
        GT_assert(ti_sdo_fc_dman3_GTMask, dmaTab[i].numTransfers > 0);

        dmaTab[i].handle = NULL;
        maxWaits += dmaTab[i].numWaits;
        maxTransfers += dmaTab[i].numTransfers;
    }

    GT_3trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS, "DMAN3_createChannels> "
            "Total Qdma channels requested %d, PaRams requested %d, "
            "Tccs requested %d\n", numChans, maxTransfers, maxWaits);

#ifdef _MULTI_PROCESS_
    /* Enter critical section */
    LockMP_acquire(_DMAN3_lock);
#endif
    /* Get the context for this group ID, or create a new one. */
    status = getContext(&context, groupId, maxWaits, maxTransfers);

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "DMAN3_createChannels> "
            "Context 0x%x\n", context );

    /* Now create the channels */
    if (status == DMAN3_SOK) {
        status = createChannels(context, NULL, groupId, dmaTab, numChans);
    }

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

#ifdef _MULTI_PROCESS_
    /* Exit critical section */
    LockMP_release(_DMAN3_lock);
#endif

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_createChannels> Exit "
            "(returnVal=%d)\n",status);

    return (status);
}

/*
 *  ======== DMAN3_grantDmaChannels ========
 *  Add an algorithm to the DMA Manager.  The DMA Manager will grant DMA
 *  resources to the algorithm as a result.  This function is called when
 *  initializing an algorithm instance.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int DMAN3_grantDmaChannels(Int groupId, IALG_Handle algHandle[],
        IDMA3_Fxns *dmaFxnsArray[], Int numAlgs)
{
    Uns              numChans;
    Int              i, j, k;
    IALG_Handle      alg;
    IDMA3_Fxns      *dmaFxns;
    IDMA3_ChannelRec *dmaTab;
    Int              maxWaits = 0;
    Int              maxTransfers = 0;
    DMAN3_Context    context;
    Int              status = DMAN3_EFAIL;
    Uns             *gtPaRamAddr = NULL;

    DBC_require(algHandle != NULL);
    DBC_require(dmaFxnsArray != NULL);
    DBC_require(numAlgs > 0);
    DBC_require(groupId < DMAN3_MAXGROUPS);
    GT_assert(ti_sdo_fc_dman3_GTMask, algHandle != NULL);
    GT_assert(ti_sdo_fc_dman3_GTMask, dmaFxnsArray != NULL);
    GT_assert(ti_sdo_fc_dman3_GTMask, numAlgs > 0);
    GT_assert(ti_sdo_fc_dman3_GTMask, groupId < DMAN3_MAXGROUPS);

    GT_4trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_grantDmaChannels> "
            "Enter (groupId=%d, algHandle=0x%x, dmaFxns=0x%x, numAlgs=%d)\n",
            groupId, algHandle, dmaFxnsArray, numAlgs);

    if (!(_DMAN3_initStatus)) {

        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                "DMAN3_grantDmaChannels> DMAN3 initialization failed.\n");

        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
                "DMAN3_grantDmaChannels> Exit (status=DMAN3_EFAIL)\n");
        return (DMAN3_EFAIL);
    }

    /* use dynamic allocation instead of stack to avoid large array on stack */
    dmaTab = (IDMA3_ChannelRec *)MEM_calloc(_DMAN3_heapExt,
        sizeof(IDMA3_ChannelRec) * _DMAN3_numAssignedTccs, sizeof(Int));

    if (dmaTab == MEM_ILLEGAL) {

        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
                "DMAN3_grantDmaChannels> Exit (status=DMAN3_EOUTOFMEMORY)\n");
        return (DMAN3_EOUTOFMEMORY);
    }

    /*
     *  Determine the maximum number of TCCs and PaRams that will be needed
     *  by this group of algorithms.
     */
    for (i = 0; i < numAlgs; i++) {

        alg = algHandle[i];
        dmaFxns = dmaFxnsArray[i];

        DBC_require(alg != NULL);
        DBC_require(dmaFxns != NULL);
        GT_assert(ti_sdo_fc_dman3_GTMask, alg != NULL);
        GT_assert(ti_sdo_fc_dman3_GTMask, dmaFxns != NULL);

        /*  alg and idma2 fxns must be from same implementation */
        DBC_require(dmaFxns->implementationId == alg->fxns->implementationId);
        GT_assert(ti_sdo_fc_dman3_GTMask,
                dmaFxns->implementationId == alg->fxns->implementationId);

        /*
         * Verify that algo is not using two many buffers,
         * in release build trust that contract is respected
         */

        numChans = dmaFxns->dmaGetChannels(alg, dmaTab);


        /* TODO:L  should additionally dump dmaTab? */
        for (j = 0; j < numChans; j++) {

            dmaTab[j].handle = NULL;
            DBC_require(dmaTab[j].numWaits >= 0);
            DBC_require(dmaTab[j].numTransfers > 0);
            GT_assert(ti_sdo_fc_dman3_GTMask, dmaTab[j].numWaits >= 0);
            GT_assert(ti_sdo_fc_dman3_GTMask, dmaTab[j].numTransfers > 0);

            maxWaits += dmaTab[j].numWaits;
            maxTransfers += dmaTab[j].numTransfers;
        }


        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                "DMAN3_grantDmaChannels> Alg 0x%x:\n", alg);

        GT_3trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS, "DMAN3_grantDmaChannels> "
                "Total Channels requested %d, PaRams requested %d, "
                "Tccs requested %d\n", numChans, maxTransfers, maxWaits);

        /*
         * Note, we check tccs here, but can't check PaRams because it's a
         * more complex check... and it's done in getContext().
         */
        if (maxWaits > _DMAN3_numAssignedTccs) {

            MEM_free(_DMAN3_heapExt, dmaTab,
                    sizeof(IDMA3_ChannelRec) * _DMAN3_numAssignedTccs);
            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
                    "DMAN3_grantDmaChannels> Exit (status=EOUTOFTCCS)\n");
            return (DMAN3_EOUTOFTCCS);
        }
    }

#ifdef _MULTI_PROCESS_
    /* Enter critical section */
    LockMP_acquire(_DMAN3_lock);
#endif

    /* Get the context for this group, or create a new one. */
    status = getContext(&context, groupId, maxWaits, maxTransfers);

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "DMAN3_grantDmaChannels> "
            "Context 0x%x\n", context);

    if (status == DMAN3_SOK) {
        for (i = 0; i < numAlgs; i++) {
            alg = algHandle[i];
            dmaFxns = dmaFxnsArray[i];

            DBC_require(alg != NULL);
            DBC_require(dmaFxns != NULL);
            GT_assert(ti_sdo_fc_dman3_GTMask, alg != NULL);
            GT_assert(ti_sdo_fc_dman3_GTMask, dmaFxns != NULL);

            /*  alg and idma3 fxns must be from same implementation */
            DBC_require(dmaFxns->implementationId ==
                    alg->fxns->implementationId);
            GT_assert(ti_sdo_fc_dman3_GTMask,
                    dmaFxns->implementationId == alg->fxns->implementationId);

            numChans = dmaFxns->dmaGetChannels(alg, dmaTab);

            status = createChannels(context, alg, groupId, dmaTab, numChans);

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
                                    PARAMSIZEMAUS,
                                    gtPaRamAddr);

                            gtPaRamAddr -= (PARAMSIZE);
                        }

                        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                                "DMAN3_createChannels> Assigned Tcc(s):\n");

                        for(j = 0; j < dmaTab[k].handle->numTccs; j++) {

                            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                                    "DMAN3_createChannels> %d\n",
                                    dmaTab[k].handle->tccTable[j]);
                        }
                    }
                }
            }

            if (status != DMAN3_SOK) {
                /* Free channels allocated for alg[0],...,alg[i-1] */
                for (j = 0; j < i; j++) {
                    alg = algHandle[j];
                    dmaFxns = dmaFxnsArray[j];
                    numChans = dmaFxns->dmaGetChannels(alg, dmaTab);

                    /* freeChannels frees context if refCount goes to 0 */
                    freeChannels(dmaTab, numChans);

                    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                            "DMAN3_grantDmaChannels> Alg 0x%x Freeing channel "
                            "resources\n", alg);

                }
                break;
            }
        }
    }

#ifdef _MULTI_PROCESS_
        /* Exit critical section */
        LockMP_release(_DMAN3_lock);
#endif

    MEM_free(_DMAN3_heapExt, dmaTab,
        sizeof(IDMA3_ChannelRec) * _DMAN3_numAssignedTccs);

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_grantDmaChannels> Exit"
            " (status=%d)\n",status);

    return (status);
}

/*
 *  ======== DMAN3_freeChannels ========
 *  Free memory for channel handles in dmaTab[].
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int DMAN3_freeChannels(IDMA3_Handle channelTab[], Int numChan)
{
    Int             i;
    IDMA3_Handle    chan;
    DMAN3_Context   context;
    DMAN3_Channel   dmanChan;
    Void           *scratchEnv;
    //Int             status = DMAN3_SOK;
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

        /* Free DMAN3 channel object memory */
#if DBC_ASSERTS
        fRet = MEM_free(_DMAN3_heapIdma3, chan, sizeof(DMAN3_ChannelObj));
        DBC_assert(fRet);
#else
        MEM_free(_DMAN3_heapIdma3, chan, sizeof(DMAN3_ChannelObj));
#endif

#ifdef _MULTI_PROCESS_
        /* Enter critical section: for non-64P, context is in shared memory */
        LockMP_acquire(_DMAN3_lock);
#endif
        context->refCount--;

        /* Free the context object if the refCount is 0 */
        if (context->refCount == 0) {
            freeContext(context);
        }
#ifdef _MULTI_PROCESS_
        /* Exit critical section */
        LockMP_release(_DMAN3_lock);
#endif
    }

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_freeChannels> Exit "
            "(status=DMAN3_SOK)\n");

    return (DMAN3_SOK);
}


/*
 *  ======== DMAN3_releaseDmaChannels ========
 *  Remove logical channel resources from an algorithm instance
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int DMAN3_releaseDmaChannels(IALG_Handle algs[], IDMA3_Fxns *dmaFxnsArray[],
        Int numAlgs)
{
    IALG_Handle         alg;
    IDMA3_Fxns         *dmaFxns;
    IDMA3_ChannelRec    *dmaTab;
    Uns                 nChans;
    Int                 i;
    Int                 heap;
    Int                 numTccs;

    DBC_require(algs != NULL);
    DBC_require(dmaFxnsArray != NULL);
    DBC_require(numAlgs > 0);
    GT_assert(ti_sdo_fc_dman3_GTMask, algs != NULL);
    GT_assert(ti_sdo_fc_dman3_GTMask, dmaFxnsArray != NULL);
    GT_assert(ti_sdo_fc_dman3_GTMask, numAlgs > 0);

    GT_3trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_releaseDmaChannels> "
            "Enter (algs=0x%x, dmaFxnsArray=0x%x, numAlgs=%d)\n", algs,
            dmaFxnsArray, numAlgs);

    /*
     *  Save these values for freeing dmaTab, since for Linux, _DMAN3_heapExt
     *  and _DMAN3_numAssignedTccs are part of the DMAN3 shared object that
     *  could be freed in DMAN3_freeChannels(), if the reference count goes
     *  to 0.
     */
    heap = _DMAN3_heapExt;
    numTccs = _DMAN3_numAssignedTccs;

    /* use dynamic allocation instead of stack to avoid large array on stack */
    dmaTab = (IDMA3_ChannelRec *)MEM_calloc(heap,
            sizeof(IDMA3_ChannelRec) * numTccs, sizeof(Int));

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

        if (nChans > _DMAN3_numAssignedTccs) {
            MEM_free(_DMAN3_heapExt, dmaTab,
                    sizeof(IDMA3_ChannelRec) * _DMAN3_numAssignedTccs);
            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
                    "DMAN3_releaseDmaChannels> Exit "
                    "(status=DMAN3_EOUTOFTCCS\n");
            return (DMAN3_EOUTOFTCCS);
        }

        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                "DMAN3_releaseDmaChannels> Free %d channels\n", nChans);

        freeChannels(dmaTab, nChans);

    }

    MEM_free(heap, dmaTab, sizeof(IDMA3_ChannelRec) * numTccs);

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_releaseDmaChannels> "
            "Exit (status=DMAN3_SOK)\n");

    return (DMAN3_SOK);
}


/*
 *  ======== createChannels ========
 */
static Int createChannels(DMAN3_Context context, IALG_Handle alg, Int groupId,
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
    Uns             qDmaChan;
    Uint8          *tccTablePtr;
    Uns            *paRamAddr;
    Bool            fRet;
    Int             status = DMAN3_SOK;
    Uns             * gtPaRamAddr = NULL;

    DBC_assert(dmaTab != NULL);

    GT_5trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "createChannels> Enter "
            "(context=0x%x, alg=0x%x, groupId=%d, dmaTab=0x%x, numChans=%d)\n",
            context, alg, groupId, dmaTab, numChans);

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
        /* Check the context refCount to see if it should be freed. */
        if (context->refCount == 0) {
            freeContext(context);
        }
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

        dmaTab[i].handle = (IDMA3_Obj *)MEM_calloc(_DMAN3_heapIdma3,
                sizeof(DMAN3_ChannelObj), sizeof(Int));

        if (dmaTab[i].handle == MEM_ILLEGAL) {

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels> "
                    "Error allocating memory for channel %d\n", i);

            /*
             *  If we failed to create the first channel, then freeChannels()
             *  will not get called to free the context if its ref count is 0.
             *  This can only happen when i = 0.
             */
            if (context->refCount == 0) {

                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels>"
                        " Freeing context 0x%x\n",context);

                freeContext(context);
            }

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
            /* Assert that Physical DMA resources can be provided */
            DBC_assert(context->nextFreeTccIdx + dmaTab[i].numWaits <=
                    context->tccBase + context->numTccs);
            DBC_assert(context->numAssignedPaRams + dmaTab[i].numTransfers <=
                    context->numPaRams);

            GT_5trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS, "createChannels> "
                    "IDMA3 Object Allocated mem[%d]: size=0x%x, align=0x%x, "
                    "heapId=%d, base=0x%x\n", i, sizeof(DMAN3_ChannelObj), 
                    sizeof(Int), _DMAN3_heapIdma3, dmaTab[i].handle);

            /* Assign QDMA Channel in a roundrobin fashion */
            qDmaChan = DMAN3_PARAMS.qdmaChannels[(context->nextQdmaChannel++
                    - context->qdmaBase) % context->numQdmas + 
                    context->qdmaBase];

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels> "
                    "Assigning qdmaChannel %d\n",qDmaChan);

            /* Assign TCCs sequentially from a free list */
            tccTablePtr = &_DMAN3_tccAllocationTable[context->nextFreeTccIdx];
            context->nextFreeTccIdx += dmaTab[i].numWaits;

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
                context->refCount++;

                if (envSize > 0) {

                    GT_5trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS,
                            "createChannels> "
                            "Env Allocated memTab[%d]: size=0x%x, "
                            "align=0x%x, heapId=%d, base=0x%x\n", i, envSize,
                            align, seg, env);
                }

                GT_0trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels>"
                        " Initializing IDMA3_handle\n");

                /*
                 * Initialize the IDMA3_Handle handle with resource allocation
                 * & channel state
                 */
                fRet = initHandle(dmaTab[i].handle, &dmaTab[i], tccTablePtr,
                        qDmaChan, envSize, env, scratchEnv, seg, context);

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

                    /* Update paRamAddr for next channel */
                    paRamAddr = ((Uns *)context->nextFreePaRamAddr) +
                        (PARAMSIZE * dmaTab[i].numTransfers);

                    /* Set free ptr to next entry */
                    context->nextFreePaRamAddr = ((Uns *)paRamAddr);
                    context->numAssignedPaRams += dmaTab[i].numTransfers;

                    /* Reference count the channels */
                }
            }
            else {

                GT_0trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createChannels> "
                        "Error allocating environment memory, freeing Channel "
                        "objects\n");

                /* Couldn't allocate env */
                MEM_free(_DMAN3_heapIdma3, dmaTab[i].handle,
                        sizeof(DMAN3_ChannelObj));

                /*
                 *  Check the context refCount to see if it should be freed
                 *  (ie, if this were the first channel we attempted to
                 *  create).
                 */
                if (context->refCount == 0) {

                    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                            "createChannels> Free context 0x%x\n",context);

                    freeContext(context);
                }

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
static Int createContext(DMAN3_Context *pContext, Int groupId, Int nTccs,
        Int nPaRams, Int scratchId)
{
    Int             maxTccs;
    Int             maxPaRams;
    Int             paRamBaseIndex;
    DMAN3_Context   context;
    Int             status = DMAN3_SOK;

    GT_4trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "createContext> Enter "
            "(pContext=0x%x, groupId=%d, nTccs=%d, nPaRams=%d)\n", pContext,
            groupId, nTccs, nPaRams);

    *pContext = NULL;

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createContext> Allocate "
            "memory for the context\n");

    if (_DMAN3_numQdmaGroup(scratchId) <= 0) {
        //Better bail now, no point proceeding with 0 channels in your group   
        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createContext> Can't  "
                "create handle, no QDMA channels configured for scratch group ",
                scratchId);

        return(DMAN3_EFAIL);
    }

    if (groupId < 0) {
        context = (DMAN3_Context)MEM_calloc(_DMAN3_heapExt,
                sizeof(DMAN3_ContextObj), sizeof(Int));
    }
    else {
        /* Use the pre-allocated context object */
        context = _DMAN3_groupContext(groupId);
    }

    if (context == MEM_ILLEGAL) {
        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createContext> Could "
                "not allocate memory for the context\n");
        status = DMAN3_EOUTOFMEMORY;
    }
    else {
        /* Initialize the context object */
        context->groupId = groupId;
        context->refCount = 0;
        context->numTccs = 0;
        context->numPaRams = 0;
        context->tccBase = -1;  /* Initialize, in case maxTccs = 0 */

        context->qdmaBase = _DMAN3_qdma(scratchId);
        context->numQdmas = _DMAN3_numQdmaGroup(scratchId);

        if (ti_sdo_fc_dman3_DMAN3_useCustomDma) {

            if (scratchId == -1) {
                //If original request was for persistent resources, need to
                //allocate discrete resources 
                //Mark those resources are persistently "used"
                _DMAN3_data->qdmaPersistentNum--;  
                _DMAN3_data->qdmaPersistentBase++;
            }
        }

        maxTccs = nTccs;
        maxPaRams = nPaRams;

        if (groupId >= 0) {
            /*
             *  Allocate the maximum of nTccs and the number of TCCs
             *  configured for this groupId.
             */
            maxTccs = (_DMAN3_numTccGroup[groupId] > maxTccs) ?
                _DMAN3_numTccGroup[groupId] : maxTccs;

            /*
             *  Allocate the maximum of nPaRams and the number of PaRams
             *  configured for this groupId.
             */
            maxPaRams = (_DMAN3_numPaRamGroup[groupId] > maxPaRams) ?
                _DMAN3_numPaRamGroup[groupId] : maxPaRams;
        }

        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createContext> Allocate"
                " %d tccs\n", maxTccs);

        /* Allocate the TCCs */
        if ((maxTccs > 0) && !RMM_alloc(_DMAN3_rmmTccs, maxTccs,
                    (Uint32 *)&(context->tccBase))) {

            freeContext(context);

            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "createContext> Exit"
                    " (status=DMAN3_OUTOFTCCS)\n");

            return (DMAN3_EOUTOFTCCS);
        }
        else {
            context->numTccs = maxTccs;
            context->nextFreeTccIdx = context->tccBase;

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createContext> Next "
                    "free tcc index %d\n", context->nextFreeTccIdx);

        }

        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createContext> Allocate"
                " %d paRams\n", maxPaRams);

        /* Allocate the PaRam */
        if (!RMM_alloc(_DMAN3_rmmPaRams, maxPaRams, (Uint32 *)&paRamBaseIndex)){

            freeContext(context);

            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "createContext> Exit"
                    " (status=DMAN3_OUTOFPARAMS)\n");

            return (DMAN3_EOUTOFPARAMS);
        }
        else {
            context->numPaRams = maxPaRams;
            context->paRamBaseIdx = paRamBaseIndex; /* For freeing later */

            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "createContext> Next"
                    "paRam index %d\n", context->paRamBaseIdx);

        }

        /* If successful allocation of TCCs and PaRam... */
#ifndef _DMAN3_CPUCOPY_
        DBC_assert(_DMAN3_paRamAddr != NULL);
#endif
        context->paRamBase = (Uns *)((Uns)_DMAN3_paRamAddr +
                (paRamBaseIndex * PARAMSIZEMAUS));
        context->nextFreePaRamAddr = context->paRamBase;
        context->numAssignedPaRams = 0;

        context->nextQdmaChannel = context->qdmaBase;
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
#if DBC_ASSERTS
    Bool    fRet;
#endif

    DBC_require(context->refCount == 0);
    GT_assert(ti_sdo_fc_dman3_GTMask, context->refCount == 0);

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "_freeContext> Enter "
            "(context=0x%x)\n", context);

    /* Free the TCCs */
    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "freeContext> Freeing "
            "%d tccs\n", context->numTccs);

    /* TODO:M should we 'invalidate' context->tccBase even if !DBC_ASSERTS? */
#if DBC_ASSERTS
    if (context->numTccs > 0) {
        fRet = RMM_free(_DMAN3_rmmTccs, context->tccBase, context->numTccs);
        context->tccBase = -1;
        DBC_assert(fRet);
    }
#else
    if (context->numTccs > 0) {
        RMM_free(_DMAN3_rmmTccs, context->tccBase, context->numTccs);
    }
#endif

    /* Free the PaRams */
    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "freeContext> Freeing "
            "%d params\n", context->numPaRams);

#if DBC_ASSERTS
    if (context->numPaRams > 0) {
        fRet = RMM_free(_DMAN3_rmmPaRams, context->paRamBaseIdx,
                context->numPaRams);
        context->paRamBaseIdx = -1;
        DBC_assert(fRet);
    }
#else
    if (context->numPaRams > 0) {
        RMM_free(_DMAN3_rmmPaRams, context->paRamBaseIdx, context->numPaRams);
    }
#endif


    if (context->groupId < 0) {
        MEM_free(_DMAN3_heapExt, context, sizeof(DMAN3_ContextObj));
    }

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
 */
static Int getContext(DMAN3_Context *pContext, Int groupId, Int nTccs,
        Int nPaRams)
{
    Int           scratchId = groupId;
    DMAN3_Context context = NULL;
    Int status = DMAN3_SOK;

    GT_4trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "getContext> Enter "
            "(pContext=0x%x, groupId=%d, nTccs=%d, nPaRams=%d)\n", pContext,
            groupId, nTccs, nPaRams);

    *pContext = NULL;

    if (groupId >= 0) {
#ifdef xdc_target__isaCompatible_64P
        /*
         *  If allowUnshared is FALSE, don't allow channels to be created
         *  if the number of TCCs or PaRams needed is more than the number
         *  configured for the given scratch group.
         */
        if (DMAN3_PARAMS.allowUnshared == FALSE) {
            if (_DMAN3_numTccGroup[groupId] < nTccs) {
                return (DMAN3_ETCCCONFIG);
            }

            if (_DMAN3_numPaRamGroup[groupId] < nPaRams) {
                return (DMAN3_EPARAMCONFIG);
            }
        }
#endif
        context = _DMAN3_groupContext(groupId);

        GT_2trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "getContext> Context "
                "exists for groupId %d, context 0x%x\n",groupId, context);

        /*
         *  Need to allocate a new context if one exists for the given
         *  groupId, but does not have enough PaRam or TCCs.
         *  Note: For non-64P targets where group contexts are pre-defined
         *  (and therefore never NULL), we need to check that the context
         *  reference count is > 0 before accessing the other fields.
         */
        if (context && (context->refCount > 0) && (
                (nPaRams > context->numPaRams) ||
                (nTccs > context->numTccs))) {
            /*
             *  The context for this groupId has been created with too few
             *  tccs or PaRams, so it cannot be used for this channel
             *  allocation. In this case, we will need to allocate a new
             *  context which will not share its tccs and PaRams.
             */
            GT_3trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                    "getContext> "
                    "Existing context has insufficient tccs and PaRams: "
                    "params: %d, tccs: %d, refCount: %d\n",
                    context->numPaRams, context->numTccs, context->refCount);

            groupId = -1;
            context = NULL;
        }
    }

    /*
     *  Create the context handle if not using any sharing group, or if
     *  using a sharing group but the context for that group has not yet
     *  been allocated, or, if not enough TCCs or PaRams are available.
     */
    if ((context == NULL) || (context->refCount == 0)) {

        GT_3trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "getContext> Creating "
                "context for group %d Tccs %d PaRams %d\n", groupId, nTccs,
                nPaRams);

        status = createContext(&context, groupId, nTccs, nPaRams, scratchId);
        if (status != DMAN3_SOK) {
            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "getContext> Exit "
                    "(status=%d)\n", status);
            return (status);

        }
        context->scratchId = scratchId;
    }

    DBC_assert(context != NULL);

    /*
     *  Re-initialize next available TCC and PaRam back to the beginning.
     *  The channels allocated in this call will not share TCCs, PaRam.
     */
    context->nextFreeTccIdx = context->tccBase;
    context->nextFreePaRamAddr = context->paRamBase;
    context->numAssignedPaRams = 0;
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
        Uint8 *tccList, Uns qdmaChannel, Int16 envSize, Void *env,
        Void *scratchEnv, Int seg, DMAN3_Context context)
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

    GT_4trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "initHandle> Initializing "
            "IDMA3 handle with %d tccs, %d PaRams, qdmaChannel %d, env 0x%x\n",
            handle->numTccs, handle->numPaRams, handle->qdmaChan, env);

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
    handle->paRamAddr = ((Uns *)context->nextFreePaRamAddr) +
        (PARAMSIZE * (dmaTab->numTransfers - 1));

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
/*
 *  @(#) ti.sdo.fc.dman3; 1, 0, 4,300; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

