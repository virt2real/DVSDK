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
 *  ======== iresman_edma3ChanLsp.c ========
 *  Implementation of the IRESMAN interface to acquire EDMA3CHAN resource 
 *  handles. 
 */

#include <xdc/std.h>

static int gtInit = 0;

/*
 * Define this, before including ires_edma3Chan.h, as that checks for this 
 * define to avoid multiple inclusion of the static Protocol Version definition
 * of IRES_EDMA3CHAN_PROTOCOLREVISION from the header file. 
 */
#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "_edma3Chan.h"
#include <ti/sdo/fc/edma3/edma3_config.h>
#include "iresman_edma3Chan.h"
#include "ires_edma3Chan.h"

#include <ti/sdo/utils/trace/gt.h>
GT_Mask ti_sdo_fc_ires_edma3chan_GTMask;

#define CURTRACE ti_sdo_fc_ires_edma3chan_GTMask

static IRESMAN_PersistentAllocFxn * _allocFxn = NULL;  
                                               /* Memory allocation Function */

static IRESMAN_PersistentFreeFxn * _freeFxn = NULL;    
                                               /* Memory free Function */

static unsigned short _dchmapExists = 0;       /* Flag indicating if Channel
                                                  Mapping exists for this EDMA3
                                                  device */
static unsigned int _initialized = 0;           /* Flag indicating if this RM
                                                   has been initialized */

/*
 * Internal function to free allocated resources 
 */
static inline IRES_Status _freeResource(IALG_Handle algHandle, 
        Int scratchGroupId, short edma3Chan, short qdmaChan, short numPaRams, 
        short * paRamIndex, short numTccs, short * tccIndex, Bool contig); 

Bool _checkContig(short * paRams, short num);
/*
 *  ======== IRESMAN_EDMA3CHAN_getProtocolName ========
 *  Function to return the name of the protocol
 */
String IRESMAN_EDMA3CHAN_getProtocolName()
{

    if (0 == gtInit) {

        GT_init();

        GT_create(&CURTRACE, "ti.sdo.fc.ires.edma3Chan");
    
        gtInit = 1;
    }

    GT_0trace(CURTRACE, GT_ENTER,
            "IRESMAN_EDMA3CHAN_getProtocolName> Enter\n");

    GT_1trace(CURTRACE, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_getProtocolName> Exit (name=%s)\n",
            IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getName());

    return (IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getName());
}

/*
 *  ======== IRESMAN_EDMA3CHAN_getProtocolRevision ========
 * Function to return the revision of the protocol
 */
IRES_ProtocolRevision * IRESMAN_EDMA3CHAN_getProtocolRevision()
{
    IRES_ProtocolRevision * version;

    if ( 0 == gtInit) {

        GT_init();

        GT_create(&CURTRACE, "ti.sdo.fc.ires.edma3Chan");
    
        gtInit = 1;
    }

    GT_0trace(CURTRACE, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_getProtocolRevision> Enter\n");

    version = IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getRevision();

    GT_3trace(CURTRACE, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_getProtocolRevision> Exit (version=(%d.%d.%d))"
            "\n", version->Major, version->Source, version->Radius);

    return (version);
}

/*
 *  ======== IRESMAN_EDMA3CHAN_init ========
 * Function to initialize the device specific resource manager implementation
 */
IRES_Status IRESMAN_EDMA3CHAN_init(IRESMAN_Params * initArgs) 
{
    IRESMAN_Edma3ChanParams * resmanArgs = (IRESMAN_Edma3ChanParams *)initArgs;

    if ( 0 == gtInit) {

        GT_init();

        GT_create(&CURTRACE, "ti.sdo.fc.ires.edma3Chan");
    
        gtInit = 1;
    }

    GT_1trace(CURTRACE, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_init> Enter (initArgs=0x%x)\n", initArgs); 

    GT_assert(CURTRACE, initArgs != NULL);

    /*
     * Information regarding the memory allocation/free functions
     * is stored as part of the internal state of the resource
     * manager
     */
    _allocFxn = resmanArgs->baseConfig.allocFxn;
    
    _freeFxn = resmanArgs->baseConfig.freeFxn;
    

    if (!(_initialized)) {

       /*
         * Set Initalized flag to 1 if successful
         */
         _initialized = 1;
     }

     GT_0trace(CURTRACE, GT_ENTER,
            "IRESMAN_EDMA3CHAN_init> Exit (status=IRES_OK)\n"); 

     return (IRES_OK);
}

/*
 *  ======== IRESMAN_EDMA3CHAN_exit ========
 *  Function called when RESMAN is no longer needed. Use it to free memory 
 *  allocated etc
 */
IRES_Status IRESMAN_EDMA3CHAN_exit() 
{

    GT_0trace(CURTRACE, GT_ENTER, "IRESMAN_EDMA3CHAN_exit> Enter\n");
    
    /*
     * Check if initialized
     */
    if (!(_initialized)) {

        GT_0trace(CURTRACE, GT_ENTER, 
                "IRESMAN_EDMA3CHAN_exit> Exit (status=IRES_ENOINIT)\n");
    
        return (IRES_ENOINIT);
    }

    GT_0trace(CURTRACE, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_exit> Exit (status=IRES_OK)\n");

    return (IRES_OK);
}

/*
 *  ======== IRESMAN_EDMA3CHAN_getHandles ========
 *  Function that returns the IRES_Handle to the resource requested using the 
 *  IRES_ResourceProtocolArgs
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Handle IRESMAN_EDMA3CHAN_getHandles( IALG_Handle algHandle,
        IRES_ProtocolArgs * protocolArgs, Int scratchGroupId,
        IRES_Status * status)
{
    EDMA3_ResDesc resObj;
    IALG_MemRec protocolMemRecs[IRESMAN_PROTOCOL_EDMA3CHAN_MAX_MEMRECS];
    IALG_MemRec constructHandleMemRec;
    Int numMemRecs;
    EDMA3_Handle rmHandle;
    
    short reqEdma = IRES_EDMA3CHAN_CHAN_NONE;
    short reqQdma = IRES_EDMA3CHAN_CHAN_NONE;

    short edma3Chan = IRES_EDMA3CHAN_CHAN_NONE;
    short qdmaChan = IRES_EDMA3CHAN_CHAN_NONE;
    short numPaRams = 0;
    short numTccs = 0;
    short paRamArray[IRES_EDMA3CHAN_MAXPARAMS] = { EDMA3_RES_ANY };
    short tccArray[IRES_EDMA3CHAN_MAXTCCS] = { EDMA3_RES_ANY };
    short toFreeTccs = 0;
    short toFreeParams = 0;
    short reqParam = IRES_EDMA3CHAN_PARAM_NONE;
    short reqTcc = IRES_EDMA3CHAN_TCC_NONE;
    unsigned int cccfg = 0x0;
    int i = 0;

    IRESMAN_EDMA3CHAN_ConstructHandleArgs * constructArgs = NULL;
    IRES_Handle resourceHandle = NULL;

    /*
     * Cast the protocolArgs 
     */
    IRES_EDMA3CHAN_ProtocolArgs * configArgs = 
            (IRES_EDMA3CHAN_ProtocolArgs *) protocolArgs;

    GT_assert(CURTRACE, protocolArgs);

    GT_2trace(CURTRACE, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_getHandles> Enter (protocolArgs=0x%x, "
            "scratchGroupId=%d)\n", protocolArgs, scratchGroupId);

    if (_initialized != 1) {

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> RMAN_register call has not "
                "happened successfully\n. Please register EDMA3CHAN resource "
                "with RMAN before assigning resources\n");

        *status =  IRES_ENORESOURCE;
        return (NULL);
    }

    if (configArgs->mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    } else if (configArgs->mode == IRES_LATEACQUIRE) {
        //Set to MAX SCRATCH GROUPS
        scratchGroupId = EDMA3_LATEACQUIREGROUP;  
        GT_0trace(CURTRACE, GT_4CLASS,
                "IRESMAN_EDMA3CHAN_getHandles> Requested IRES_LATEACQUIRE "
                "HDVICP resources. Ensure you \"lock\" resources using "
                "IRES RESUTILS API before using them for correct operation\n");

    } 
    
    rmHandle = EDMA3_getResourceManager(algHandle, scratchGroupId);

    if (NULL == rmHandle) {

        *status =  IRES_ENORESOURCE;

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Error obtaining Low level "
                "Resource Manager Handle.\n");

        GT_0trace(CURTRACE, GT_ENTER, 
                "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_ENORESOURCE)\n");

        return (NULL);
    }

    if (EDMA3_SOK != EDMA3_getCCRegister( rmHandle , 4, &cccfg)) {

        *status =  IRES_EFAIL;

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Error reading EDMA3's CCCFG "
                "Register.\n");

        GT_0trace(CURTRACE, GT_ENTER, 
                "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_EFAIL)\n");

        if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
                scratchGroupId)) {

            *status = IRES_EFAIL; 

            GT_0trace(CURTRACE, GT_7CLASS, 
                    "IRESMAN_EDMA3CHAN_getHandles> Error releasing Low level "
                    "Resource Manager Handle.\n");
        }

        return (NULL);
    }

    _dchmapExists = IRES_EDMA3CHAN_EDMA3REGISTERLAYER_CHMAPEXIST(cccfg);

    if (_dchmapExists) {

        GT_0trace(CURTRACE, GT_2CLASS,
                "IRESMAN_EDMA3CHAN_getHandles> DCHMAP exists on device ??\n"); 

        GT_assert(CURTRACE, 0);
    }

    numPaRams = configArgs->numPaRams;
    numTccs = configArgs->numTccs;

        GT_assert(CURTRACE, numPaRams <= IRES_EDMA3CHAN_MAXPARAMS);
        GT_assert(CURTRACE, numTccs <= IRES_EDMA3CHAN_MAXTCCS);

    reqEdma = configArgs->edmaChan;
    reqQdma = configArgs->qdmaChan;

    if (configArgs->numPaRams != 0) { 
        reqParam = configArgs->paRamIndex;
    }

    if (configArgs->numTccs != 0) {
        reqTcc = configArgs->tccIndex;
    }

    if (IRES_EDMA3CHAN_TCC_NONE == reqTcc) {
        GT_assert(CURTRACE, numTccs == 0);
    } 

    if (IRES_EDMA3CHAN_PARAM_NONE == reqParam) {
        GT_assert(CURTRACE, numPaRams == 0);
    } 

        if ((reqEdma != IRES_EDMA3CHAN_EDMACHAN_ANY) && 
                        (reqEdma != IRES_EDMA3CHAN_CHAN_NONE) && 
                        ((reqEdma < 0) || 
                        (reqEdma >= 64 ))) {

        GT_0trace(CURTRACE, GT_6CLASS,
                "IRESMAN_EDMA3CHAN_getHandles> Bad request for EDMA channel. "
                "Will not grant request EDMA channel\n");

                reqEdma = IRES_EDMA3CHAN_CHAN_NONE;               
        }

        if ((reqQdma != IRES_EDMA3CHAN_QDMACHAN_ANY) && 
                        (reqQdma != IRES_EDMA3CHAN_CHAN_NONE) && 
                        ((reqQdma < 0) ||
                        (reqQdma >= 8))) {

        GT_0trace(CURTRACE, GT_6CLASS,
                "IRESMAN_QDMA3CHAN_getHandles> Bad request for EDMA channel. "
                "Will not grant request QDMA channel\n");

                reqQdma = IRES_EDMA3CHAN_CHAN_NONE;               
        }

/*
  1. Couple request into Logical EDMA channel request 
  2. Couple request into Logical QDMA channel request
  3. Couple request  for multiple (or the rest of the paRams) into contigPaRams
     request
  4. Request rest of the QDMA channels required -> will waste resources
  5. Request rest of the TCCs required  -> will waste resources
*/

    if ((numPaRams > 0) && (numTccs > 0)) {

        /* 1. */
        if (IRES_EDMA3CHAN_CHAN_NONE != reqEdma) {

            /* If request is for EDMA N, then PaRam and TCC should be requested                of the same number or ANY */
            if ((reqEdma != IRES_EDMA3CHAN_EDMACHAN_ANY) && 
                    ((IRES_EDMA3CHAN_PARAM_ANY == reqParam) || 
                     (reqEdma == reqParam)) && 
                    ((IRES_EDMA3CHAN_TCC_ANY == reqTcc) || 
                     (reqEdma == reqTcc))) {
    
                /* Allocate Logical E Channel N and decrement numTccs and 
                   numPaRams and change reqEdma to NONE ? */ 
                resObj.type = EDMA3_RES_DMA_CHANNEL; 
                resObj.resId = reqEdma;
                tccArray[toFreeTccs] = reqEdma;  /* Requesting tcc == edma */ 
                paRamArray[toFreeParams] = reqEdma;
    
                if (EDMA3_SOK != EDMA3_allocLogicalChannel(rmHandle, 
                        &resObj, (unsigned int *)&paRamArray[toFreeParams], 
                        (unsigned int *)&tccArray[toFreeTccs])) {

                    *status =  IRES_ENORESOURCE;
                    goto getResmanHandleFail;
                }
                edma3Chan = resObj.resId;
                toFreeParams++;
                toFreeTccs++;
                numPaRams--;
                numTccs--;
                reqEdma = IRES_EDMA3CHAN_CHAN_NONE;
            }

            /* If request is for EDMA ANY and P N or ANY and TCC N or any */
            else if ((IRES_EDMA3CHAN_TCC_ANY == reqTcc) || 
                    (reqParam == IRES_EDMA3CHAN_PARAM_ANY) ||
                    (reqParam == reqTcc)) {
    
                /* Allocate logical E Channel #"TCC/PaRAM/ANY" and decrement 
                   numTccs and numPaRams */
                resObj.type = EDMA3_RES_DMA_CHANNEL; 
                resObj.resId = ((IRES_EDMA3CHAN_PARAM_ANY == 
                        reqParam) ?  
                        ((IRES_EDMA3CHAN_TCC_ANY == reqTcc) ? 
                        EDMA3_RES_ANY : reqTcc) : 
                        reqParam);
                tccArray[toFreeTccs] = resObj.resId; /* Requesting tcc = edma */
                paRamArray[toFreeParams] = resObj.resId;
                
                if (EDMA3_SOK != EDMA3_allocLogicalChannel(rmHandle, 
                        &resObj, (unsigned int *)&paRamArray[toFreeParams], 
                        (unsigned int *)&tccArray[toFreeTccs])) {

                    *status =  IRES_ENORESOURCE;
                    goto getResmanHandleFail;
                }
                edma3Chan = resObj.resId;
                toFreeParams++;
                toFreeTccs++;
                numPaRams--;
                numTccs--;
                reqEdma = IRES_EDMA3CHAN_CHAN_NONE;
                /* If a logical channel was requested, then any other param 
                   request cannot have a specific param number */ 
                reqParam = IRES_EDMA3CHAN_PARAM_ANY;
                reqTcc = IRES_EDMA3CHAN_TCC_ANY;
            }
        }
        /* 2. */
        else if (IRES_EDMA3CHAN_CHAN_NONE != reqQdma) {
            
            /* If request is for QDMA N  or QDMA Any, P should be ANY */
            if (IRES_EDMA3CHAN_PARAM_ANY == reqParam) {
    
                 /* Allocate Logical Q Channel N and decrement numTccs and 
                    numPaRams */ 
                resObj.type = EDMA3_RES_QDMA_CHANNEL; 
                resObj.resId = ((IRES_EDMA3CHAN_QDMACHAN_ANY == reqQdma) ?  
                        EDMA3_RES_ANY : reqQdma);
                /* Requesting tcc as required*/ 
                tccArray[toFreeTccs] = 
                        (IRES_EDMA3CHAN_TCC_ANY == reqTcc) ? 
                        EDMA3_RES_ANY : reqTcc; 

                paRamArray[toFreeParams] = EDMA3_RES_ANY; 
                if (EDMA3_SOK != EDMA3_allocLogicalChannel(rmHandle, 
                        &resObj, (unsigned int *)&paRamArray[toFreeParams], 
                        (unsigned int *)&tccArray[toFreeTccs])) {

                    *status =  IRES_ENORESOURCE;
                    goto getResmanHandleFail;
                }
                qdmaChan = resObj.resId;
                toFreeParams++;
                toFreeTccs++;
                numPaRams--;
                numTccs--;
                reqQdma = IRES_EDMA3CHAN_CHAN_NONE;
                /* If a logical channel was requested, then any other param 
                   request cannot have a specific param number */ 
                reqParam = IRES_EDMA3CHAN_PARAM_ANY;
                reqTcc = IRES_EDMA3CHAN_TCC_ANY;
            }
        }
    }

    /* 3. */
    /* Alloc contiguous or Not P */
    if (numPaRams > 0) {

        resObj.type = EDMA3_RES_PARAM_SET;

        if ((numPaRams > 1) && configArgs->contiguousAllocation) {

            GT_0trace(CURTRACE, GT_4CLASS,
                    "IRESMAN_EDMA3CHAN_getHandles> Contiguous PaRams "
                    "requested\n"); 

            resObj.resId = (reqParam == 
                    IRES_EDMA3CHAN_PARAM_ANY)? EDMA3_RES_ANY: 
                    reqParam;

            if (EDMA3_SOK != EDMA3_allocContiguousResource(
                    rmHandle, &resObj, numPaRams)) {

                    *status =  IRES_ENORESOURCE;
                    goto getResmanHandleFail;
            }
            else {

                for (i = 0; i < numPaRams; i++) {
                    paRamArray[i+toFreeParams] = resObj.resId + i;
                }

                GT_2trace(CURTRACE, GT_4CLASS,
                        "IRESMAN_EDMA3CHAN_getHandles> Obtained %d PaRams "
                        "starting at %d \n", numPaRams, 
                        paRamArray[toFreeParams]); 

                toFreeParams += numPaRams;
            }

            numPaRams = 0; 
        }
        else {

            GT_0trace(CURTRACE, GT_4CLASS,
                    "IRESMAN_EDMA3CHAN_getHandles> Contiguous PaRams "
                    "NOT required\n"); 

            if (numPaRams == 1) {

                resObj.resId =(reqParam == 
                        IRES_EDMA3CHAN_PARAM_ANY)? EDMA3_RES_ANY:
                        reqParam;
            }
            else {
                /* Multiple non-contig PaRams should always be requested as
                   ANY */
                resObj.resId = EDMA3_RES_ANY;
            }

            /*
             * Allocate the PaRams individually
             */
            for (i = 0; i < numPaRams; i++) {

                if (EDMA3_SOK != EDMA3_allocResource( rmHandle,&resObj)) {

                    *status =  IRES_ENORESOURCE;
                    goto getResmanHandleFail;
                }
                else {

                    paRamArray[toFreeParams] = resObj.resId;
    
                    GT_1trace(CURTRACE, GT_4CLASS, 
                            "IRESMAN_EDMA3CHAN_getHandles> Obtained Param %d\n"
                            , paRamArray[toFreeParams]);

                    toFreeParams++;
                    resObj.resId = EDMA3_RES_ANY;
                }
            }
            numPaRams = 0;
        }
    }

    /* 4 */
    if (IRES_EDMA3CHAN_CHAN_NONE != reqEdma) {

        resObj.type = EDMA3_RES_DMA_CHANNEL;
        resObj.resId = ( IRES_EDMA3CHAN_EDMACHAN_ANY == reqEdma) ? 
                EDMA3_RES_ANY: reqEdma; 

        GT_1trace(CURTRACE, GT_2CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Requesting individual EDMA "
                "channel %d, might cause resource wastage !\n", resObj.resId);

        if (EDMA3_SOK != EDMA3_allocResource( rmHandle,&resObj)) {

            *status =  IRES_ENORESOURCE;
            goto getResmanHandleFail;
        }
        reqEdma = IRES_EDMA3CHAN_CHAN_NONE;
        edma3Chan = resObj.resId;
            
    }

    if (IRES_EDMA3CHAN_CHAN_NONE != reqQdma) {

        resObj.type = EDMA3_RES_QDMA_CHANNEL;
        resObj.resId = (IRES_EDMA3CHAN_QDMACHAN_ANY == reqQdma) ? 
                EDMA3_RES_ANY: reqQdma; 

        GT_1trace(CURTRACE, GT_2CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Requesting individual Qdma "
                "channel %d, might cause resource wastage !\n", resObj.resId);

        if (EDMA3_SOK != EDMA3_allocResource( rmHandle,&resObj)) {

            *status =  IRES_ENORESOURCE;
            goto getResmanHandleFail;
        }

        reqQdma = IRES_EDMA3CHAN_CHAN_NONE;
        qdmaChan = resObj.resId;
    }

    if (numTccs > 0) {

         resObj.type = EDMA3_RES_TCC;

        if ((toFreeTccs > 0) || (numTccs > 1)) {
            /* If requesting multiple TCCs then use ANY to request */
            resObj.resId = EDMA3_RES_ANY;
        }
        else {
            resObj.resId = ((reqTcc == IRES_EDMA3CHAN_TCC_ANY)?
                    EDMA3_RES_ANY:((unsigned int)reqTcc));
        }
    
        GT_1trace(CURTRACE, GT_2CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Requesting %d individual Tcc(s),"
                "might cause resource wastage !\n", numTccs);

        for(i = 0 ; i < numTccs; i++) {

            if (EDMA3_SOK != EDMA3_allocResource( rmHandle, &resObj)) {

                *status =  IRES_ENORESOURCE;
                goto getResmanHandleFail;
            }

            tccArray[toFreeTccs] = resObj.resId;
                        resObj.resId = EDMA3_RES_ANY;

            GT_1trace(CURTRACE, GT_4CLASS,
                    "IRESMAN_EDMA3CHAN_getHandles> Obtained TCC %d\n", 
                    tccArray[toFreeTccs]); 

            toFreeTccs++;
        }

        numTccs = 0;
    }


    /* Do construct handle stuff here */
    /*
     * To call the Construct handle protocol interface, first construct the 
     * arguments that need to be passed IRES_EDMA3CHAN_ConstructHandleArgs
     * This has the list of actual params that need to be sent back as handle 
     */

    /*
     * Allocate memory for the constructHandle Arguments
     */
    constructHandleMemRec.size = sizeof(IRESMAN_EDMA3CHAN_ConstructHandleArgs);
    constructHandleMemRec.alignment = 4;
    constructHandleMemRec.space = IALG_EXTERNAL;
    constructHandleMemRec.attrs = IALG_PERSIST;

    if (FALSE == _allocFxn(&constructHandleMemRec, 1)) {

        *status =  IRES_ENOMEM;

        GT_1trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Memory allocation for size 0x%x,"
                " of Persistent External memory failed\n",  
                constructHandleMemRec.size);

        goto getResmanHandleFail;
    }
    GT_assert(CURTRACE, IALG_EXTERNAL == constructHandleMemRec.space);

    constructArgs = constructHandleMemRec.base; 
    constructArgs->numPaRams = toFreeParams;
    constructArgs->paRamIndex = paRamArray;
    constructArgs->edma3Chan = edma3Chan;
    constructArgs->qdmaChan = qdmaChan;
    constructArgs->tccIndex = tccArray;
        constructArgs->numTccs = toFreeTccs;

    if (scratchGroupId == -1) { 
        constructArgs->persistent = TRUE;
    }
    else {
        constructArgs->persistent = FALSE;
    }

    if ( EDMA3_SOK != EDMA3_getBaseAddress(rmHandle, EDMA3_CC_PHY_ADDR,
            &(constructArgs->edma3CCBaseAddress))) {

        _freeFxn(&constructHandleMemRec, 1); 

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Call to obtain base address "
                "of EDMA3 device failed\n");  

        *status =  IRES_EFAIL;

        goto getResmanHandleFail;
    }

    /*
     * Get IRES_EDMA3CHAN_RESOURCEPROTOCOL's memory requirements
     */
    numMemRecs = IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getNumMemRecs
            ((IRES_ProtocolArgs *) protocolArgs);

    GT_assert(CURTRACE, numMemRecs <= IRESMAN_PROTOCOL_EDMA3CHAN_MAX_MEMRECS);

    /*
     * Get the memory requirements of the protocol in resMemRecs
     */
    IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, protocolMemRecs);

    /*
     * Allocate that memory 
     */
    if (FALSE == _allocFxn(protocolMemRecs, numMemRecs)) {

        _freeFxn(&constructHandleMemRec, 1); 

        *status = IRES_ENOMEM;

        GT_1trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Memory allocation for size 0x%x,"
                " of Persistent External memory failed\n",  
                protocolMemRecs[0].size);

        goto getResmanHandleFail;
    }

    for (i=0; i < numMemRecs; i++) {
        GT_assert(CURTRACE, protocolMemRecs[i].space == IALG_EXTERNAL);
    }

    /*
     * Construct the resource protocol handle
     */
    resourceHandle = IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.constructHandle(
             protocolArgs, protocolMemRecs, 
             (IRESMAN_ConstructArgs *)constructArgs, status); 

    GT_assert(CURTRACE, resourceHandle != NULL);

    /*
     * Free constructArgs memory, that was just to pass the arguments
     */
    _freeFxn(&constructHandleMemRec, 1); 

    *status = IRES_OK;

    GT_1trace(CURTRACE, GT_ENTER, 
           "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=0x%x, "
           "status=IRES_OK)\n", resourceHandle);

    /* return */
    return (resourceHandle);

getResmanHandleFail:

    /* fail code comes here, free resources and leave */
    _freeResource(algHandle, scratchGroupId, edma3Chan, qdmaChan, toFreeParams, 
            paRamArray, toFreeTccs, tccArray, configArgs->contiguousAllocation);

    GT_2trace(CURTRACE, GT_7CLASS, 
            "IRESMAN_EDMA3CHAN_getHandles> Could not allocate requested "
            "resource of type %d Id %d\n", resObj.type, resObj.resId);

    if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
        scratchGroupId)) {

        *status = IRES_EFAIL; 

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Error releasing Low "
                "level Resource Manager Handle.\n");
    }

    *status =  IRES_ENORESOURCE;

    GT_1trace(CURTRACE, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, status=%d)\n", 
            *status);

    return (NULL);
}

/*
 *  ======== IRESMAN_EDMA3CHAN_freeHandle ========
 *  Frees handles back to the resource pool resources to free
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Status IRESMAN_EDMA3CHAN_freeHandle(IALG_Handle algHandle, IRES_Handle
        algResourceHandle, IRES_ProtocolArgs * protocolArgs, 
                Int scratchGroupId) 
{
    IALG_MemRec resourceMemRecs[IRESMAN_PROTOCOL_EDMA3CHAN_MAX_MEMRECS];
    Int numMemRecs;
    IRES_Status status = IRES_OK;


    IRES_EDMA3CHAN_Handle resourceHandle = (IRES_EDMA3CHAN_Handle) 
            algResourceHandle;

    GT_assert(CURTRACE, protocolArgs);
    GT_assert(CURTRACE, algResourceHandle);

    GT_3trace(CURTRACE, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_freeHandle> Enter (handle=0x%x, "
            "protocolArgs=0x%x, scratchGroupId=%d)\n", algResourceHandle, 
            protocolArgs, scratchGroupId);

    if (_initialized != 1) {

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandle> RMAN_register call has not "
                "happened successfully\n. Please register EDMA3CHAN resource "
                "with RMAN before requesting or releasing resources.\n");

        status =  IRES_ENORESOURCE;
        return (status);
    }

    if (protocolArgs->mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    }
    else if (protocolArgs->mode == IRES_LATEACQUIRE) {
        //Set to MAX SCRATCH GROUPS
        scratchGroupId = EDMA3_LATEACQUIREGROUP;  
    } 

    /*
         * Don't need to free resources unless they were acquired persistently,          * as otherwise we will release this particular handle 
         */
    //if (-1 == scratchGroupId) {

            status = _freeResource(algHandle, scratchGroupId,
                    resourceHandle->assignedEdmaChannelIndex,
                    resourceHandle->assignedQdmaChannelIndex,
                    resourceHandle->assignedNumPaRams,
                    resourceHandle->assignedPaRamIndices,
                    resourceHandle->assignedNumTccs,
                    resourceHandle->assignedTccIndices,
                ((IRES_EDMA3CHAN_ProtocolArgs *)protocolArgs)
                ->contiguousAllocation);
    //}

    if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
            scratchGroupId)) {

        status = IRES_EFAIL; 

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_freeHandle> Error releasing Low level "
                "Resource Manager Handle.\n");
    }

    /*
     * Obtain memory resources to free and free them
     */
    numMemRecs = IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getNumMemRecs
            ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    resourceMemRecs[0].base = algResourceHandle;

    /*
     * Use IRES_EDMA3CHAN_RESOURCEPROTOCOL to de-init the resource protocol
     * if required
     */
    IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.destructHandle(algResourceHandle);

    /*
     * Free the memory for the handles
     */
    _freeFxn(resourceMemRecs, numMemRecs); 

    GT_1trace(CURTRACE, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_freeHandles> Exit (status=%d)\n", status);

    return (status); 
}

/*
 *  ======== _freeResource ========
 *  Actually free resources from the EDMA3 Low Level Resource Manager Handle
 */
static inline IRES_Status _freeResource(IALG_Handle algHandle, 
       Int scratchGroupId, short edma3Chan, short qdmaChan, 
       short numPaRams, short * paRamIndex, short numTccs, short * tccIndex,
       Bool contigRequest) 
{

    EDMA3_ResDesc resObj;
    IRES_Status status = IRES_OK;
    EDMA3_Result result = EDMA3_SOK;
    EDMA3_Handle rmHandle;
    int i;
    short toFreeTccs = 0;
    short toFreeParams = 0;
    Bool contig = FALSE;

/* TODO: Don't need to do anything for scratchGroupId != -1 */

    GT_6trace(CURTRACE, GT_ENTER, "_freeResource> Enter "
            "(algHandle=0x%x, scratchGroupId=%d, edma3Chan=%d, qdmaChan=%d, "
            "numPaRams=%d, numTccs=0x%x\n)",
            algHandle, scratchGroupId, edma3Chan, qdmaChan, numPaRams, numTccs);
    /*
     * Obtain Resource Manager handle corresponding to this algorithm in this 
     * scratch Group 
     */
    rmHandle = EDMA3_getResourceManager(algHandle, scratchGroupId);
/*
  1. Couple request into Logical EDMA channel request 
  2. Couple request into Logical QDMA channel request
  3. Couple request  for multiple (or the rest of the paRams) into contigPaRams
     request
  4. Request rest of the QDMA channels required -> will waste resources
  5. Request rest of the TCCs required  -> will waste resources
*/
    if ((numPaRams > 0) && (numTccs > 0)) {

        /* 1. */
        if (IRES_EDMA3CHAN_CHAN_NONE != edma3Chan) {

            /* If free request is for EDMA N, 
               then PaRam and TCC should be of the same number */
/* TODO: Assuming ordering of resources, maybe should search instead */         
            if ((edma3Chan == tccIndex[toFreeTccs]) && 
                    (edma3Chan == paRamIndex[toFreeParams])) {
    
                resObj.type = EDMA3_RES_DMA_CHANNEL; 
                resObj.resId = edma3Chan;
                tccIndex[toFreeTccs] = edma3Chan;  /* Requesting tcc == edma */ 
    
                if (EDMA3_SOK != EDMA3_freeLogicalChannel(rmHandle, 
                        &resObj)) {
                    //TODO: Blind release of logical channel, double check
                    //, (unsigned int *)&paRamArray[toFreeParams], 
                    // (unsigned int *)&tccIndex[toFreeTccs]))

                    status =  IRES_EFAIL;
                    goto freeResourceFail;
                }
                toFreeParams++;
                toFreeTccs++;
                numPaRams--;
                numTccs--;
                edma3Chan = IRES_EDMA3CHAN_CHAN_NONE;
            }
        }
        /* 2. */
        else if (IRES_EDMA3CHAN_CHAN_NONE != qdmaChan) {
            
            /* If request is for QDMA N  or QDMA Any, P should be ANY */
            /* TO check: Basically coupling QDMA channel with first PaRam and  
                         Tcc */
            
                    
    
                resObj.type = EDMA3_RES_QDMA_CHANNEL; 
                resObj.resId = qdmaChan; 

                if (EDMA3_SOK != EDMA3_freeLogicalChannel(rmHandle, 
                        &resObj)) {
                    //TODO: Blind release of logical channel, double check
                    //, (unsigned int *)&paRamArray[toFreeParams], 
                    // (unsigned int *)&tccIndex[toFreeTccs])) 

                    status =  IRES_EFAIL;
                    goto freeResourceFail;
                }
                toFreeParams++;
                toFreeTccs++;
                numPaRams--;
                numTccs--;
                qdmaChan = IRES_EDMA3CHAN_CHAN_NONE;
        }
    }

    /* 3. */

    /* Alloc contiguous or Not P */
    if (numPaRams > 0) {

        resObj.type = EDMA3_RES_PARAM_SET;


        /*
         * Check if params are contiguous 
         */
        contig = _checkContig(&paRamIndex[toFreeParams], numPaRams);
        
        /*
         * Check if they were requested contiguously
         */
        contig &= contigRequest;
        
        if (!contig) {
    
            /*
             * Free the PaRams individually
             */
            for (i = 0; i < numPaRams; i++) {
        
                resObj.resId = paRamIndex[toFreeParams];
                if (EDMA3_SOK != EDMA3_freeResource( rmHandle,&resObj)) {
        
                    status =  IRES_EFAIL;
                    goto freeResourceFail;
                }
                else {
        
                    toFreeParams++;
                }
            }
    
        }
        else {
            resObj.resId = paRamIndex[toFreeParams];
            if (EDMA3_SOK != EDMA3_freeContiguousResource(rmHandle,
                    &resObj, numPaRams)) {
        
                status =  IRES_EFAIL;
                goto freeResourceFail;
            }
            else {
                    toFreeParams += numPaRams;
            }
            numPaRams = 0;
        }
    }

    /* 4 */
    if (IRES_EDMA3CHAN_CHAN_NONE != edma3Chan) {

        resObj.type = EDMA3_RES_DMA_CHANNEL;
        resObj.resId = edma3Chan; 

        GT_1trace(CURTRACE, GT_2CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Freeing individual EDMA "
                "channel %d, might cause other resources to be freed!\n", 
                resObj.resId);

        if (EDMA3_SOK != EDMA3_freeResource( rmHandle,&resObj)) {

            status =  IRES_EFAIL;
            goto freeResourceFail;
        }
        edma3Chan = IRES_EDMA3CHAN_CHAN_NONE;
    }

    if (IRES_EDMA3CHAN_CHAN_NONE != qdmaChan) {

        resObj.type = EDMA3_RES_QDMA_CHANNEL;
        resObj.resId = qdmaChan; 

        GT_1trace(CURTRACE, GT_2CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Freeing individual Qdma "
                "channel %d, might cause other resources to be freed !\n", 
                resObj.resId);

        if (EDMA3_SOK != EDMA3_freeResource(rmHandle, &resObj)) {

            status =  IRES_EFAIL;
            goto freeResourceFail;
        }

        qdmaChan = IRES_EDMA3CHAN_CHAN_NONE;
    }

    if (numTccs > 0) {

        resObj.type = EDMA3_RES_TCC;

        GT_1trace(CURTRACE, GT_2CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Freeing %d individual Tcc(s),"
                "might cause other resources to be freed!\n", numTccs);

        for(i = 0 ; i < numTccs; i++) {

            resObj.resId = tccIndex[toFreeTccs];

            if (EDMA3_SOK != EDMA3_freeResource( rmHandle, &resObj)) {

                status =  IRES_EFAIL;
                goto freeResourceFail;
            }

            GT_1trace(CURTRACE, GT_4CLASS,
                    "IRESMAN_EDMA3CHAN_getHandles> Freed TCC %d\n", 
                    tccIndex[toFreeTccs]); 

            toFreeTccs++;
        }

        numTccs = 0;
    }

freeResourceFail:
    result = EDMA3_releaseResourceManager(algHandle, scratchGroupId);

    if (result != EDMA3_SOK) {
        status = IRES_EFAIL; 
    }

    GT_1trace(CURTRACE, GT_ENTER, "_freeResource> Exit "
            "(status=%d)\n",status);

    return (status);
}


Bool _checkContig(short * paRams, short num)
{
    int i = 0;
    for (i = 1; i < num; i++) {
        if ((paRams[i] - paRams[i-1]) != 1) {
            return (FALSE);
        } 
    }
    return (TRUE);
}

IRESMAN_Fxns IRESMAN_EDMA3CHAN =  {
    IRESMAN_EDMA3CHAN_getProtocolName,
    IRESMAN_EDMA3CHAN_getProtocolRevision,
    IRESMAN_EDMA3CHAN_init,
    IRESMAN_EDMA3CHAN_exit,
    IRESMAN_EDMA3CHAN_getHandles,
    IRESMAN_EDMA3CHAN_freeHandle
};

IRESMAN_Edma3ChanParams IRESMAN_EDMA3CHAN_DEFAULTPARAM;

IRESMAN_Fxns * EDMA3CHAN_getIresmanFxns()
{
    return ((Void *)(&IRESMAN_EDMA3CHAN));
}


IRESMAN_Params * EDMA3CHAN_getDefaultParams()
{
    IRESMAN_EDMA3CHAN_DEFAULTPARAM.baseConfig.size = 
            sizeof(IRESMAN_Params);

    return ((IRESMAN_Params *)&IRESMAN_EDMA3CHAN_DEFAULTPARAM);
}

/*
 *  @(#) ti.sdo.fc.ires.edma3chan; 1, 0, 0,177; 12-1-2010 17:25:02; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

