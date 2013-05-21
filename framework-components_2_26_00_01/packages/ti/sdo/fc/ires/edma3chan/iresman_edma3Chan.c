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
 *  ======== iresman_edma3Chan.c ========
 *  Implementation of the IRESMAN interface to acquire EDMA3CHAN resource 
 *  handles. 
 */

#include <xdc/std.h>
#include <ti/sdo/fc/utils/dbc.h>

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

/*
 *  ======== IRESMAN_Edma3Chan_InternalState ========
 *  Structure to hold the internal state information of the IRESMAN EDMA3CHAN 
 *  object that will be set once during INIT and then re-used while granting 
 *  resources. 
 */
typedef struct IRESMAN_Edma3Chan_InternalState {

    IRESMAN_PersistentAllocFxn * allocFxn;      /* Memory allocation Function */

    IRESMAN_PersistentFreeFxn * freeFxn;        /* Memory free Function */

    unsigned short dchmapExists;                /* Flag indicating if Channel
                                                   Mapping exists for this EDMA3
                                                   device */
    unsigned int initialized;                  
                                                /* Flag indicating if the 
                                                   resource manager is 
                                                   initialized */
    Int sharedMemId;

} IRESMAN_Edma3Chan_InternalState;

/*
 * Represents the IRES EDMA3 Resource manager
 */
static IRESMAN_Edma3Chan_InternalState _EDMA3CHAN_internalState;

static IRESMAN_Edma3Chan_InternalState  * _resmanInternalState = 
        &_EDMA3CHAN_internalState;
/*
 * Internal function to free allocated resources 
 */
static inline IRES_Status _freeResource(IALG_Handle algHandle, 
        Int scratchGroupId, short edma3Chan, short qdmaChan, short numPaRams, 
        short * paRamIndex, short numTccs, short * tccIndex); 

static Void setInternalState(Void * addr);

static void getInternalState(); 

static void freeInternalState(); 

/*
 *  ======== IRESMAN_EDMA3CHAN_getProtocolName ========
 *  Function to return the name of the protocol
 */
String IRESMAN_EDMA3CHAN_getProtocolName()
{
    if (0 == gtInit) {
        
        GT_create(&ti_sdo_fc_ires_edma3chan_GTMask, "ti.sdo.fc.ires.edma3Chan"); 
        GT_init();

        gtInit = 1;
    }

    GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_getProtocolName> Enter\n");

    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
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

    if (0 == gtInit) {
        
        GT_create(&ti_sdo_fc_ires_edma3chan_GTMask, "ti.sdo.fc.ires.edma3Chan"); 
        GT_init();

        gtInit = 1;
    }

    GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_getProtocolRevision> Enter\n");

    version = IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getRevision();

    GT_3trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
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

    if (0 == gtInit) {
        
        GT_create(&ti_sdo_fc_ires_edma3chan_GTMask, "ti.sdo.fc.ires.edma3Chan"); 
        GT_init();

        gtInit = 1;
    }

    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_init> Enter (initArgs=0x%x)\n", initArgs); 

    DBC_require(initArgs != NULL);
    GT_assert(ti_sdo_fc_ires_edma3chan_GTMask, initArgs != NULL);

    /* 
     *  Check if already initialized
     */
    getInternalState();
    if (_resmanInternalState->initialized) {

       GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
               "IRESMAN_EDMA3CHAN_init> Exit (status=IRES_EEXISTS)\n"); 

       freeInternalState();
       return (IRES_EEXISTS); 
    }

    /*
     * Information regarding the memory allocation/free functions
     * is stored as part of the internal state of the resource
     * manager
     */
    _resmanInternalState->allocFxn = resmanArgs->baseConfig.allocFxn;

    _resmanInternalState->freeFxn = resmanArgs->baseConfig.freeFxn;

    /*
     * Set Initalized flag to 1 if successful
     */
     _resmanInternalState->initialized = 1;

     GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER,
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

    GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_exit> Enter\n");
    
    /*
     * Check if initialized
     */
    if (!(_resmanInternalState->initialized)) {

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                "IRESMAN_EDMA3CHAN_exit> Exit (status=IRES_ENOINIT)\n");
    
        return (IRES_ENOINIT);
    }

    /*
     * Free up any memory that might be allocated in this module
     * Basically memory that has been used by the protocol implementation
     */

    /*
     * Set the initialized flag to zero again
     */
    _resmanInternalState->initialized = 0;

    GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_exit> Exit (status=IRES_OK)\n");

    GT_exit();
    
    freeInternalState(); 
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
    EDMA3_Result rmStatus; 
    
    short reqEdma = IRES_EDMA3CHAN_CHAN_NONE;
    short reqQdma = IRES_EDMA3CHAN_CHAN_NONE;
    short reqTcc[64];
    short numReqTccs = 0;

    short edma3Chan = IRES_EDMA3CHAN_CHAN_NONE;
    short qdmaChan = IRES_EDMA3CHAN_CHAN_NONE;
    short numPaRams = 0;
    short numTccs = 0;
    short toFreeParams = 0;
    short paRamArray[IRES_EDMA3CHAN_MAXPARAMS] = { IRES_EDMA3CHAN_PARAM_NONE };
    short tccArray[IRES_EDMA3CHAN_MAXTCCS] = { IRES_EDMA3CHAN_TCC_NONE };
    unsigned int cccfg = 0x0;
    int i = 0;
    IRESMAN_EDMA3CHAN_ConstructHandleArgs * constructArgs = NULL;
    IRES_Handle resourceHandle = NULL;

    /*
     * Cast the protocolArgs 
     */
    IRES_EDMA3CHAN_ProtocolArgs * configArgs = 
            (IRES_EDMA3CHAN_ProtocolArgs *) protocolArgs;

    DBC_require(protocolArgs);
    GT_assert(ti_sdo_fc_ires_edma3chan_GTMask, protocolArgs);

    GT_2trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_getHandles> Enter (protocolArgs=0x%x, "
            "scratchGroupId=%d)\n", protocolArgs, scratchGroupId);

    if (_resmanInternalState->initialized != 1) {

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> RMAN_register call has not "
                "happened successfully\n. Please register EDMA3CHAN resource "
                "with RMAN before assigning resources\n");

        *status =  IRES_ENORESOURCE;
        return (NULL);
    }

    if (configArgs->mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    } 
    
    rmHandle = EDMA3_getResourceManager(algHandle, scratchGroupId);

    if (NULL == rmHandle) {

        *status =  IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Error obtaining Low level "
                "Resource Manager Handle.\n");

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_ENORESOURCE)\n");

        return (NULL);
    }

    if (EDMA3_SOK != EDMA3_getCCRegister( rmHandle , 4, &cccfg)) {

        *status =  IRES_EFAIL;

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Error reading EDMA3's CCCFG "
                "Register.\n");

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_EFAIL)\n");

        if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
                scratchGroupId)) {

            *status = IRES_EFAIL; 

            GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                    "IRESMAN_EDMA3CHAN_getHandles> Error releasing Low level "
                    "Resource Manager Handle.\n");
        }

        return (NULL);
    }

    _resmanInternalState->dchmapExists = 
            IRES_EDMA3CHAN_EDMA3REGISTERLAYER_CHMAPEXIST(cccfg);

    if (_resmanInternalState->dchmapExists) {
        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_2CLASS,
                "IRESMAN_EDMA3CHAN_getHandles> DCHMAP exists on device \n"); 
    }

    numPaRams = configArgs->numPaRams;
    numTccs = configArgs->numTccs;
        GT_assert(ti_sdo_fc_ires_edma3chan_GTMask, 
            numPaRams <= IRES_EDMA3CHAN_MAXPARAMS);
        GT_assert(ti_sdo_fc_ires_edma3chan_GTMask, 
            numTccs <= IRES_EDMA3CHAN_MAXTCCS);
    DBC_require(numPaRams <= IRES_EDMA3CHAN_MAXPARAMS);
    DBC_require(numTccs <= IRES_EDMA3CHAN_MAXTCCS);

    reqEdma = configArgs->edmaChan;
    reqQdma = configArgs->qdmaChan;

        if ((reqEdma != IRES_EDMA3CHAN_EDMACHAN_ANY) && 
                        (reqEdma != IRES_EDMA3CHAN_CHAN_NONE) && 
                        ((reqEdma < 0) || 
                        (reqEdma >= 64 ))) {

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_6CLASS,
                "IRESMAN_EDMA3CHAN_getHandles> Bad request for EDMA channel. "
                "Will not grant request EDMA channel\n");

                reqEdma = IRES_EDMA3CHAN_CHAN_NONE;               
        }

        if ((reqQdma != IRES_EDMA3CHAN_QDMACHAN_ANY) && 
                        (reqQdma != IRES_EDMA3CHAN_CHAN_NONE) && 
                        ((reqQdma < 0) ||
                        (reqQdma >= 8))) {

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_6CLASS,
                "IRESMAN_QDMA3CHAN_getHandles> Bad request for EDMA channel. "
                "Will not grant request QDMA channel\n");

                reqQdma = IRES_EDMA3CHAN_CHAN_NONE;               
        }

    /* Check if the resources have been requested properly,
     * fail if there is an error */
    if ((numPaRams > 0) && (!(_resmanInternalState->dchmapExists))) {

        if ((numPaRams > 1) && 
                (IRES_EDMA3CHAN_CHAN_NONE != reqEdma)) {

            *status =  IRES_ENORESOURCE;

            GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                    "IRESMAN_EDMA3CHAN_getHandles> Cannot request multiple "
                    " paRams alongwith an EDMA3 channel when DCHMAP does not"
                    "exist. Request only one PaRam alongwith EDMA channel or "
                    "only multiple PaRams with no EDMA channel per handle\n");

            if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
                    scratchGroupId)) {

                *status = IRES_EFAIL; 

                GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                        "IRESMAN_EDMA3CHAN_getHandles> Error releasing Low "
                        "level Resource Manager Handle.\n");
            }

            GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                    "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                    "status=IRES_ENORESOURCE)\n");

            return (NULL);
        }
        
        if ((numPaRams == 1) && 
                (IRES_EDMA3CHAN_CHAN_NONE != reqEdma)) {

            /* 1 paRam requested alongwith an EDMA3 channel */ 
            if ((IRES_EDMA3CHAN_PARAM_ANY != configArgs->paRamIndex) && 
                    (IRES_EDMA3CHAN_EDMACHAN_ANY != reqEdma) &&
                    (reqEdma != configArgs->paRamIndex) ) {

                /* If specific channel requested doesn`t not match paRam 
                   requested, cannot allocate the resource */ 

                *status = IRES_ENORESOURCE;

                GT_2trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                        "IRESMAN_EDMA3CHAN_getHandles> Channel requested %d "
                        " has to match PaRam requested %d when DCHMAP does"
                        "not exist for this device\n", reqEdma,
                        configArgs->paRamIndex);

                if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
                        scratchGroupId)) {

                    *status = IRES_EFAIL; 

                    GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                            "IRESMAN_EDMA3CHAN_getHandles> Error releasing Low "
                            "level Resource Manager Handle.\n");
                }

                GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                        "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                        "status=IRES_ENORESOURCE)\n");

                return (NULL);
            }
        }
    }

    /*
     * Allocate PaRams at this time, only if DCHMAP exists 
     * Or if (No DCHMAP and ) No EDMA channel is requested.
     * If an EDMA channel is requested, need to allocate a logical channel 
     * so do it later 
     */
    if ( (numPaRams > 0) && 
            (_resmanInternalState->dchmapExists || 
            (IRES_EDMA3CHAN_CHAN_NONE == reqEdma)) ) {

        resObj.type = EDMA3_RES_PARAM_SET;

        if ((numPaRams > 1) && configArgs->contiguousAllocation) {

            GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_4CLASS,
                    "IRESMAN_EDMA3CHAN_getHandles> Contiguous PaRams "
                    "requested\n"); 

            resObj.resId = (configArgs->paRamIndex == 
                    IRES_EDMA3CHAN_PARAM_ANY)? EDMA3_RES_ANY: 
                    configArgs->paRamIndex;

            if (EDMA3_SOK != EDMA3_allocContiguousResource(
                    rmHandle, &resObj, numPaRams)) {
        
                _freeResource(algHandle, scratchGroupId,
                        edma3Chan, qdmaChan, 0, NULL, 0, NULL); 

                GT_2trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                        "IRESMAN_EDMA3CHAN_getHandles> Could not allocate %d "
                        "contiguous paRams starting from %d\n", numPaRams -1, 
                        resObj.resId);

                if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
                        scratchGroupId)) {

                    *status = IRES_EFAIL; 

                    GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                            "IRESMAN_EDMA3CHAN_getHandles> Error releasing Low "
                            "level Resource Manager Handle.\n");
                }

                *status =  IRES_ENORESOURCE;

                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                        "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                        "status=%d)\n", *status);

                return (NULL);
            }
            else {

                for (i = 0; i < numPaRams; i++) {
                    paRamArray[i] = resObj.resId + i;
                }

                toFreeParams = numPaRams;

                GT_2trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_4CLASS,
                        "IRESMAN_EDMA3CHAN_getHandles> Obtained %d PaRams "
                        "starting at %d \n", numPaRams, paRamArray[0]); 
            }
        }
        else {

            GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_4CLASS,
                    "IRESMAN_EDMA3CHAN_getHandles> Contiguous PaRams "
                    "NOT required\n"); 

            if (numPaRams == 1) {

                resObj.resId =(configArgs->paRamIndex == 
                        IRES_EDMA3CHAN_PARAM_ANY)? EDMA3_RES_ANY:
                        configArgs->paRamIndex;
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
    
                    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                            "IRESMAN_EDMA3CHAN_getHandles> Could not allocate "
                            "Param %d\n", resObj.resId);
    
                    _freeResource(algHandle, scratchGroupId,
                            edma3Chan, qdmaChan, i, paRamArray, 0, NULL); 
    
                    *status = IRES_ENORESOURCE;

                    if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
                            scratchGroupId)) {

                        *status = IRES_EFAIL; 

                        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                                "IRESMAN_EDMA3CHAN_getHandles> Error releasing "
                                "Low level Resource Manager Handle.\n");
                    }

                    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                            "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                            "status=%d)\n", *status);

                    return (NULL);
                }
                else {

                    paRamArray[i] = resObj.resId;
    
                    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_4CLASS, 
                            "IRESMAN_EDMA3CHAN_getHandles> Obtained Param %d\n"                            , paRamArray[i]);

                    resObj.resId = EDMA3_RES_ANY;
                }
            }
            toFreeParams = numPaRams;
        }
    }

    /* Obtain the TCCs if requested */
    if ((configArgs->numTccs > 0) && 
            (IRES_EDMA3CHAN_TCC_NONE != configArgs->tccIndex)) {

        resObj.type = EDMA3_RES_TCC;

        if (configArgs->numTccs > 1) {
            /* If requesting multiple TCCs then use ANY to request */
            resObj.resId = EDMA3_RES_ANY;
        }
        else {
            resObj.resId = (configArgs->tccIndex == IRES_EDMA3CHAN_TCC_ANY)?
                    EDMA3_RES_ANY:((unsigned int)configArgs->tccIndex);
        }
    
        for(i = 0 ; i <configArgs->numTccs; i++) {

            if (EDMA3_SOK != EDMA3_allocResource( rmHandle, &resObj)) {
                /*
                 * Error allocating tcc
                 * Free all resources and exit
                 */
                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS,
                        "IRESMAN_EDMA3CHAN_getHandles> Could not allocate Tcc "
                        "%d\n", resObj.resId);

               _freeResource(algHandle, scratchGroupId,
                        edma3Chan, qdmaChan, toFreeParams, paRamArray, 
                        i, tccArray ); 

                *status = IRES_ENORESOURCE;

                if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
                            scratchGroupId)) {

                    *status = IRES_EFAIL; 

                    GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                            "IRESMAN_EDMA3CHAN_getHandles> Error releasing "
                            "Low level Resource Manager Handle.\n");
                }

                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                        "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                        "status=%d)\n", *status);


                return (NULL);
            }

            tccArray[i] = resObj.resId;
                        resObj.resId = EDMA3_RES_ANY;

            GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_4CLASS,
                    "IRESMAN_EDMA3CHAN_getHandles> Obtained TCC %d\n", 
                    tccArray[i]); 
        }
    }

    /* 
     * Obtain the channel requirements qdma or edmaChan
     * In one handle, can request for either QDMA or EDMA channel 
     */

    if (IRES_EDMA3CHAN_CHAN_NONE != reqQdma) {

        /*
         * Request a qdma channel assign it to qdmaChan
         */
        resObj.type = EDMA3_RES_QDMA_CHANNEL;

        resObj.resId =(IRES_EDMA3CHAN_QDMACHAN_ANY == reqQdma)?
                EDMA3_RES_ANY:((unsigned int)reqQdma);

        if (EDMA3_SOK != EDMA3_allocResource( rmHandle, &resObj) ) {

            *status = IRES_ENORESOURCE;

            GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                    "IRESMAN_EDMA3CHAN_getHandles> Could not allocate QDMA "
                    "Channel %d\n", resObj.resId);

            _freeResource(algHandle, scratchGroupId,
                    edma3Chan, qdmaChan, toFreeParams, paRamArray, 
                    numTccs, tccArray);

            if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
                    scratchGroupId)) {

                *status = IRES_EFAIL; 

                GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                        "IRESMAN_EDMA3CHAN_getHandles> Error releasing "
                        "Low level Resource Manager Handle.\n");
            }

            GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                    "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                    "status=%d)\n", *status);

            return (NULL);
        }

        GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_4CLASS,
                "IRESMAN_EDMA3CHAN_getHandles> Obtained qdma channel %d\n", 
                resObj.resId); 

        qdmaChan = resObj.resId;
    } 

    if (IRES_EDMA3CHAN_CHAN_NONE != reqEdma) {

        /*
         * Request an edma channel assign it to edmaChan 
         */
        resObj.type = EDMA3_RES_DMA_CHANNEL;

        if (_resmanInternalState->dchmapExists) {

            GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_4CLASS, 
                    "IRESMAN_EDMA3CHAN_getHandles> DCHMAP exists on device\n");

            /*
             * If DCHMAP exists then any channel request can be satisfied by 
             * mapping it to the PaRam that has been allocated  
             */     
            if ((numTccs == 1) && 
                    (configArgs->tccIndex == IRES_EDMA3CHAN_TCC_ANY) && 
                    (reqEdma == IRES_EDMA3CHAN_EDMACHAN_ANY)) {

                GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_2CLASS, 
                        "IRESMAN_EDMA3CHAN_getHandles> EDMA Channel ANY "
                        "requested with 1 TCC ANY.\n");

                resObj.resId = tccArray[0];
            }  
            else {
                resObj.resId = (IRES_EDMA3CHAN_EDMACHAN_ANY == reqEdma)
                        ? EDMA3_RES_ANY:((unsigned int)reqEdma);
            }

            if (EDMA3_SOK != EDMA3_allocResource( rmHandle, &resObj) ) {

                if ((numTccs == 1) && 
                        (configArgs->tccIndex == IRES_EDMA3CHAN_TCC_ANY) && 
                        (reqEdma == IRES_EDMA3CHAN_EDMACHAN_ANY)) {

                    /*
                     * Resource probably failed because it was a special
                     * request for mapped Tcc and Edma channel. Allocate 
                     * another TCC and try to acquire a channel mapped to it
                     */ 
                    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_2CLASS, 
                            "IRESMAN_EDMA3CHAN_getHandles> Request for EDMA "
                            "channel %d failed. Try new EDMA:TCC allocation.\n",
                            resObj.resId);

                    resObj.type = EDMA3_RES_TCC;
                    resObj.resId = EDMA3_RES_ANY; 
            
                    rmStatus = EDMA3_allocResource(rmHandle, &resObj);

                    while(EDMA3_SOK == rmStatus) { 

                    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                            GT_2CLASS, "IRESMAN_EDMA3CHAN_getHandles> "
                            "Allocated New Tcc %d\n", resObj.resId);

                        resObj.type = EDMA3_RES_DMA_CHANNEL;

                        if (EDMA3_SOK == 
                                EDMA3_allocResource(rmHandle, &resObj)) {

                            reqTcc[numReqTccs] = tccArray[0];
                            numReqTccs++;

                            edma3Chan = resObj.resId;
                            tccArray[0] = resObj.resId;

                            GT_2trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                    GT_4CLASS, "IRESMAN_EDMA3CHAN_getHandles> "
                                    "Obtained EDMA channel %d and Tcc %d\n", 
                                    edma3Chan, tccArray[0]);

                            break;
                        } 
                        else {

                            reqTcc[numReqTccs] = resObj.resId;
                            numReqTccs++;

                            GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                    GT_2CLASS, "IRESMAN_EDMA3CHAN_getHandles> "
                                    "Could not allocate EDMA channel %d\n", 
                                    resObj.resId);

                            resObj.type = EDMA3_RES_TCC;
                            resObj.resId = EDMA3_RES_ANY; 

                            rmStatus = 
                                    EDMA3_allocResource(rmHandle, &resObj);
                        } 
                    }

                    if (numReqTccs > 0) {

                        /* Free all extra Tccs requested */
                        resObj.type = EDMA3_RES_TCC;

                        for (i = 0; i < numReqTccs; i++) {
            
                            resObj.resId = reqTcc[i]; 

                            GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                    GT_2CLASS, "IRESMAN_EDMA3CHAN_getHandles> "
                                    "Free Extra Tcc %d\n", resObj.resId);

                            if (EDMA3_SOK != 
                                    EDMA3_freeResource(rmHandle, & resObj)) {

                                *status = IRES_EFAIL;

                                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_7CLASS, 
                                        "IRESMAN_EDMA3CHAN_getHandles> Error "
                                        "freeing Tcc %d\n",resObj.resId);
                            }
                        }
                    }

                    /* 
                     * Check if we broke out because of success or failure
                     */ 
                    if (EDMA3_SOK != rmStatus) {

                        *status = IRES_ENORESOURCE;

                        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                                "IRESMAN_EDMA3CHAN_getHandles> Could not "
                                "allocate matching EDMA channel and Tcc.\n");

                        _freeResource(algHandle, scratchGroupId, edma3Chan, 
                                qdmaChan, toFreeParams, paRamArray, numTccs, 
                                tccArray);

                        if (EDMA3_SOK != EDMA3_releaseResourceManager(
                                algHandle, scratchGroupId)) {

                            *status = IRES_EFAIL; 

                            GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                    GT_7CLASS, "IRESMAN_EDMA3CHAN_getHandles> "
                                    "Error releasing Low level Resource Manager"
                                    " Handle.\n");
                        }

                        GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                                "IRESMAN_EDMA3CHAN_getHandles> Exit "
                                "(handle=NULL, status=%d)\n", *status);

                        return (NULL);
                    }
                }
                else {
                
                    *status = IRES_ENORESOURCE;

                    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                            "IRESMAN_EDMA3CHAN_getHandles> Could not allocate "
                            "EDMA Channel %d\n", resObj.resId);

                    _freeResource(algHandle, scratchGroupId, edma3Chan, 
                            qdmaChan, toFreeParams, paRamArray, numTccs, 
                            tccArray);

                    if (EDMA3_SOK != EDMA3_releaseResourceManager(
                                algHandle, scratchGroupId)) {

                        *status = IRES_EFAIL; 

                        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                GT_7CLASS, "IRESMAN_EDMA3CHAN_getHandles> "
                                "Error releasing Low level Resource Manager"
                                " Handle.\n");
                    }

                    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                            "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                            "status=%d)\n", *status);

                    return (NULL);
                }
            }
            else {
                edma3Chan = resObj.resId;

                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_4CLASS,
                        "IRESMAN_EDMA3CHAN_getHandles> Obtained Edma channel "
                        "%d\n", edma3Chan); 
            }
        }
        else {

            resObj.resId = (IRES_EDMA3CHAN_EDMACHAN_ANY == reqEdma)
                    ? EDMA3_RES_ANY:((unsigned int)reqEdma);

            GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_4CLASS, 
                    "IRESMAN_EDMA3CHAN_getHandles> DCHMAP does not exist on "
                    "device\n");

            if (numPaRams > 0 ) {

                if (numPaRams > 1) {

                    /* Multiple PaRams requested, and EDMA channel requested 
                       on an SOC where DCHMAP does not exist, assert error */   

                    GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                            "IRESMAN_EDMA3CHAN_getHandles> [Error] DCHMAP "
                            "does not exist, Multiple PaRams requested "
                            "alongwith an EDMA channel \n");

                    GT_assert(ti_sdo_fc_ires_edma3chan_GTMask, 0);
    
                    _freeResource( algHandle, scratchGroupId, edma3Chan, 
                            qdmaChan, 0, NULL, numTccs, tccArray);

                    *status = IRES_ENORESOURCE;

                    if (EDMA3_SOK != EDMA3_releaseResourceManager(
                                algHandle, scratchGroupId)) {

                        *status = IRES_EFAIL; 

                        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                GT_7CLASS, "IRESMAN_EDMA3CHAN_getHandles> "
                                "Error releasing Low level Resource Manager"
                                " Handle.\n");
                    }

                    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                            "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                            "status=%d)\n", *status);

                    return (NULL);
                }
                else {

                    /* TODO: Use allocLogical channel here */
                    if (EDMA3_RES_ANY == resObj.resId) {

                        if (IRES_EDMA3CHAN_PARAM_ANY == 
                                configArgs->paRamIndex) {

                            /* Allocate ANY PaRam and ANY Channel as long as 
                               they are mapped 
                               We request a Channel first and then the 
                               corresponding PaRam */

                            resObj.type = EDMA3_RES_DMA_CHANNEL;
                            
                            if (EDMA3_SOK != EDMA3_allocResource(
                                    rmHandle, &resObj)) {

                                GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_4CLASS, 
                                        "IRESMAN_EDMA3CHAN_getHandles> Channel"
                                        " ANY allocation failed\n");

                                *status = IRES_ENORESOURCE;

                                GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_7CLASS, 
                                        "IRESMAN_EDMA3CHAN_getHandles> "
                                        "Could not allocate EDMA Channel \n"); 

                                _freeResource(algHandle, scratchGroupId, 
                                        edma3Chan, qdmaChan, toFreeParams, 
                                        paRamArray, numTccs, tccArray);

                                if (EDMA3_SOK != 
                                        EDMA3_releaseResourceManager(algHandle,                                         scratchGroupId)) {

                                    *status = IRES_EFAIL; 

                                    GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                            GT_7CLASS, 
                                            "IRESMAN_EDMA3CHAN_getHandles> "
                                            "Error releasing Low level Resource"
                                            " Manager Handle.\n");
                                }

                                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_ENTER, 
                                        "IRESMAN_EDMA3CHAN_getHandles> Exit "
                                        "(handle=NULL, status=%d)\n", *status);

                                return (NULL);
                            }

                            edma3Chan = resObj.resId; 
                            resObj.type = EDMA3_RES_PARAM_SET;

                            if (EDMA3_SOK != EDMA3_allocResource(
                                    rmHandle, &resObj)) {

                                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_4CLASS, 
                                        "IRESMAN_EDMA3CHAN_getHandles> PaRam "
                                        " %d allocation failed\n",
                                        resObj.resId);

                                *status = IRES_ENORESOURCE;

                                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_7CLASS, 
                                        "IRESMAN_EDMA3CHAN_getHandles> "
                                        "Could not allocate paRam %d\n",
                                        resObj.resId); 

                                _freeResource( algHandle, scratchGroupId, 
                                        edma3Chan, qdmaChan, 
                                        toFreeParams, paRamArray, numTccs, 
                                        tccArray);

                                if (EDMA3_SOK != 
                                        EDMA3_releaseResourceManager(algHandle,                                         scratchGroupId)) {

                                    *status = IRES_EFAIL; 

                                    GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                            GT_7CLASS, 
                                            "IRESMAN_EDMA3CHAN_getHandles> "
                                            "Error releasing Low level Resource"
                                            " Manager Handle.\n");
                                }

                                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_ENTER, 
                                        "IRESMAN_EDMA3CHAN_getHandles> Exit "
                                        "(handle=NULL, status=%d)\n", *status);

                                return (NULL);
                            }
                            
                            paRamArray[0] = resObj.resId;
                        }
                        else {

                            /* PaRam number requested is fixed, EDMA channel
                             * ANY */
                            resObj.resId = configArgs->paRamIndex;
                            resObj.type = EDMA3_RES_PARAM_SET;

                            if (EDMA3_SOK != EDMA3_allocResource(
                                    rmHandle, &resObj)) {

                                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_4CLASS, 
                                        "IRESMAN_EDMA3CHAN_getHandles> PaRam "
                                        " %d allocation failed\n",
                                        resObj.resId);

                                *status = IRES_ENORESOURCE;

                                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_7CLASS, 
                                        "IRESMAN_EDMA3CHAN_getHandles> "
                                        "Could not allocate paRam %d\n",
                                        resObj.resId); 

                                _freeResource( algHandle, scratchGroupId, 
                                        edma3Chan, qdmaChan, toFreeParams, 
                                        paRamArray, numTccs, tccArray);

                                if (EDMA3_SOK != 
                                        EDMA3_releaseResourceManager(algHandle,                                         scratchGroupId)) {

                                    *status = IRES_EFAIL; 

                                    GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                            GT_7CLASS, 
                                            "IRESMAN_EDMA3CHAN_getHandles> "
                                            "Error releasing Low level Resource"
                                            " Manager Handle.\n");
                                }

                                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_ENTER, 
                                        "IRESMAN_EDMA3CHAN_getHandles> Exit "
                                        "(handle=NULL, status=%d)\n", *status);

                                return (NULL);
                            }
                    
                            paRamArray[0] = resObj.resId; 
                            resObj.type = EDMA3_RES_DMA_CHANNEL;
                            
                            if (EDMA3_SOK != EDMA3_allocResource(
                                    rmHandle, &resObj)) {

                                *status = IRES_ENORESOURCE;

                                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_7CLASS, 
                                        "IRESMAN_EDMA3CHAN_getHandles> "
                                        "Could not allocate EDMA Channel %d\n",
                                        resObj.resId); 

                                _freeResource( algHandle, scratchGroupId,
                                        edma3Chan, qdmaChan, toFreeParams, 
                                        paRamArray, numTccs, tccArray);

                                if (EDMA3_SOK != 
                                        EDMA3_releaseResourceManager(algHandle,                                         scratchGroupId)) {

                                    *status = IRES_EFAIL; 

                                    GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                            GT_7CLASS, 
                                            "IRESMAN_EDMA3CHAN_getHandles> "
                                            "Error releasing Low level Resource"
                                            " Manager Handle.\n");
                                }

                                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_ENTER, 
                                        "IRESMAN_EDMA3CHAN_getHandles> Exit "
                                        "(handle=NULL, status=%d)\n", *status);

                                return (NULL);

                            }
                            edma3Chan = resObj.resId;
                        }
                    }
                    else {

                        /* EDMA channel is fixed, allocate PaRam corresponding 
                         to that */   
                        resObj.resId = reqEdma;
                        resObj.type = EDMA3_RES_DMA_CHANNEL;
                            
                        if (EDMA3_SOK != EDMA3_allocResource(
                                    rmHandle, &resObj)) {

                            GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                    GT_4CLASS, 
                                    "IRESMAN_EDMA3CHAN_getHandles> Channel"
                                    " %d allocation failed, truly "
                                    "allocating ANY Channel\n", 
                                    resObj.resId);

                            *status = IRES_ENORESOURCE;

                            GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                    GT_7CLASS, "IRESMAN_EDMA3CHAN_getHandles> "
                                    "Could not allocate EDMA Channel \n"); 

                            _freeResource(algHandle, scratchGroupId, edma3Chan,                                     qdmaChan, toFreeParams, 
                                    paRamArray, numTccs, tccArray);

                            if (EDMA3_SOK != 
                                    EDMA3_releaseResourceManager(algHandle,
                                    scratchGroupId)) {

                                *status = IRES_EFAIL; 

                                GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_7CLASS, 
                                        "IRESMAN_EDMA3CHAN_getHandles> "
                                        "Error releasing Low level Resource"
                                        " Manager Handle.\n");
                            }

                            GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                    GT_ENTER, 
                                    "IRESMAN_EDMA3CHAN_getHandles> Exit "
                                    "(handle=NULL, status=%d)\n", *status);

                            return (NULL);

                        }

                        edma3Chan = resObj.resId; 
                        resObj.type = EDMA3_RES_PARAM_SET;

                        if (EDMA3_SOK != EDMA3_allocResource(
                                rmHandle, &resObj)) {

                            GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                    GT_4CLASS, 
                                    "IRESMAN_EDMA3CHAN_getHandles> PaRam "
                                    " %d allocation failed\n", resObj.resId);

                            *status = IRES_ENORESOURCE;

                            GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                    GT_7CLASS, "IRESMAN_EDMA3CHAN_getHandles> "
                                    "Could not allocate paRam %d\n",
                                    resObj.resId); 

                            _freeResource( algHandle, scratchGroupId, edma3Chan,                                    qdmaChan, toFreeParams, paRamArray, numTccs,                                    tccArray);

                            if (EDMA3_SOK != 
                                    EDMA3_releaseResourceManager(algHandle,
                                    scratchGroupId)) {

                                *status = IRES_EFAIL; 

                                GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                        GT_7CLASS, 
                                        "IRESMAN_EDMA3CHAN_getHandles> "
                                        "Error releasing Low level Resource"
                                        " Manager Handle.\n");
                            }

                            GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                    GT_ENTER, 
                                    "IRESMAN_EDMA3CHAN_getHandles> Exit "
                                    "(handle=NULL, status=%d)\n", *status);

                            return (NULL);
                        }

                        paRamArray[0] = resObj.resId;
                    }
                }

                toFreeParams = numPaRams;
            }
            else {

                /* No PaRams requested, allocate channel requested */

                if (EDMA3_SOK != EDMA3_allocResource(
                        rmHandle, &resObj)) {
                    *status = IRES_ENORESOURCE;

                    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                            "IRESMAN_EDMA3CHAN_getHandles> Could not allocate "
                            "EDMA Channel %d\n", resObj.resId);


                    _freeResource( algHandle, scratchGroupId, edma3Chan,
                            qdmaChan, 0, NULL, numTccs, tccArray); 

                    if (EDMA3_SOK != 
                            EDMA3_releaseResourceManager(algHandle,
                            scratchGroupId)) {

                        *status = IRES_EFAIL; 

                        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                GT_7CLASS, "IRESMAN_EDMA3CHAN_getHandles> "
                                "Error releasing Low level Resource Manager "
                                "Handle.\n");
                    }

                    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, 
                                GT_ENTER, "IRESMAN_EDMA3CHAN_getHandles> Exit "
                                "(handle=NULL, status=%d)\n", *status);

                    return (NULL);
                }
            
                GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_4CLASS,
                        "IRESMAN_EDMA3CHAN_getHandles> Obtained Edma channel "
                        "%d\n", resObj.resId); 

                edma3Chan = resObj.resId;
            }
        }
    }

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

    if (FALSE == _resmanInternalState->allocFxn(&constructHandleMemRec, 1)) {

        _freeResource(algHandle, scratchGroupId, edma3Chan, qdmaChan, numPaRams,                paRamArray, numTccs, tccArray); 

        GT_2trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Error allocating memory for "
                "constructing handle of size 0x%x, alignment 0x%x, space "
                "IALG_EXTERNAL, attrs IALG_PERSIST\n", 
                constructHandleMemRec.size, constructHandleMemRec.alignment);

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)\n");

        *status =  IRES_ENOMEM;

        if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
                scratchGroupId)) {

            *status = IRES_EFAIL; 

            GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                    "IRESMAN_EDMA3CHAN_getHandles> Error releasing Low level "
                    "Resource Manager Handle.\n");
        }

        GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, status=%d)\n",                *status);

        return (NULL);
    }

    DBC_require(IALG_EXTERNAL == constructHandleMemRec.space);
    constructArgs = constructHandleMemRec.base; 
    constructArgs->numPaRams = numPaRams;
    constructArgs->paRamIndex = paRamArray;
    constructArgs->edma3Chan = edma3Chan;
    constructArgs->qdmaChan = qdmaChan;
    constructArgs->tccIndex = tccArray;
        constructArgs->numTccs = numTccs;

    if (scratchGroupId == -1) { 
        constructArgs->persistent = TRUE;
    }
    else {
        constructArgs->persistent = FALSE;
    }

    if ( EDMA3_SOK != EDMA3_getBaseAddress(rmHandle, EDMA3_CC_PHY_ADDR,
            &(constructArgs->edma3CCBaseAddress))) {

        _freeResource(algHandle, scratchGroupId, edma3Chan, qdmaChan, numPaRams,                paRamArray, numTccs, tccArray); 

        _resmanInternalState->freeFxn(&constructHandleMemRec, 1); 

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Error obtaining EDMA3 base "
                "address\n");

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_EFAIL)\n");

        *status = IRES_EFAIL;

        if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
                scratchGroupId)) {

            *status = IRES_EFAIL; 

            GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                    "IRESMAN_EDMA3CHAN_getHandles> Error releasing Low level "
                    "Resource Manager Handle.\n");
        }

        return (NULL);
    }

    /*
     * Get IRES_EDMA3CHAN_RESOURCEPROTOCOL's memory requirements
     */
    numMemRecs = IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getNumMemRecs
            ((IRES_ProtocolArgs *) protocolArgs);

    DBC_require(numMemRecs <= IRESMAN_PROTOCOL_EDMA3CHAN_MAX_MEMRECS);

    /*
     * Get the memory requirements of the protocol in resMemRecs
     */
    IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, protocolMemRecs);

    /*
     * Allocate that memory 
     */
    if (FALSE == _resmanInternalState->allocFxn(protocolMemRecs, numMemRecs)) {

        _freeResource(algHandle, scratchGroupId, edma3Chan, qdmaChan, numPaRams,
                paRamArray, numTccs, tccArray); 

        GT_2trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Error allocating memory for "
                "constructing handle of size 0x%x, alignment 0x%x, space "
                "IALG_EXTERNAL, attrs IALG_PERSIST\n", protocolMemRecs->size, 
                protocolMemRecs->alignment);

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)\n");

        *status = IRES_ENOMEM;

        if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
                scratchGroupId)) {

            *status = IRES_EFAIL; 

            GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                    "IRESMAN_EDMA3CHAN_getHandles> Error releasing Low level "
                    "Resource Manager Handle.\n");
        }

        return (NULL);
    }
    
    for (i=0; i < numMemRecs; i++) {

        DBC_require(protocolMemRecs[i].space == IALG_EXTERNAL);
        GT_assert(ti_sdo_fc_ires_edma3chan_GTMask,
                protocolMemRecs[i].space == IALG_EXTERNAL);
    }

    /*
     * Construct the resource protocol handle
     */
    resourceHandle = IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.constructHandle(
             protocolArgs, protocolMemRecs, 
             (IRESMAN_ConstructArgs *)constructArgs, status); 

    DBC_require(resourceHandle != NULL);
    GT_assert(ti_sdo_fc_ires_edma3chan_GTMask, resourceHandle != NULL);

    /*
     * Free constructArgs memory, that was just to pass the arguments
     */

    _resmanInternalState->freeFxn(&constructHandleMemRec, 1); 

    if (IRES_OK != *status) {

        _freeResource(algHandle, scratchGroupId, edma3Chan, qdmaChan, numPaRams,
                paRamArray, numTccs, tccArray); 

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandles> Error freeing memory \n");

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_EFAIL)\n");

        *status = IRES_EFAIL;

        if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
                scratchGroupId)) {

            *status = IRES_EFAIL; 

            GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                    "IRESMAN_EDMA3CHAN_getHandles> Error releasing Low level "
                    "Resource Manager Handle.\n");
        }

        return (NULL);
    } 
    else {

        *status = IRES_OK;

        GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
                "IRESMAN_EDMA3CHAN_getHandles> Exit (handle=0x%x, "
                "status=IRES_OK)\n", resourceHandle);

        return (resourceHandle);
    }

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

    DBC_require(protocolArgs);
    DBC_require(algResourceHandle);
    GT_assert(ti_sdo_fc_ires_edma3chan_GTMask, protocolArgs);
    GT_assert(ti_sdo_fc_ires_edma3chan_GTMask, algResourceHandle);

    GT_3trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_freeHandle> Enter (handle=0x%x, "
            "protocolArgs=0x%x, scratchGroupId=%d)\n", algResourceHandle, 
            protocolArgs, scratchGroupId);

    if (_resmanInternalState->initialized != 1) {

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                "IRESMAN_EDMA3CHAN_getHandle> RMAN_register call has not "
                "happened successfully\n. Please register EDMA3CHAN resource "
                "with RMAN before requesting or releasing resources.\n");

        status =  IRES_ENORESOURCE;
        return (status);
    }

    if (protocolArgs->mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    } 

    /*
         * Don't need to free resources unless they were acquired persistently,          * as otherwise we will release this particular handle 
         */
        if (-1 == scratchGroupId) {

            status = _freeResource(algHandle, scratchGroupId,
                    resourceHandle->assignedEdmaChannelIndex,
                    resourceHandle->assignedQdmaChannelIndex,
                    resourceHandle->assignedNumPaRams,
                    resourceHandle->assignedPaRamIndices,
                    resourceHandle->assignedNumTccs,
                    resourceHandle->assignedTccIndices);
        }

    if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
            scratchGroupId)) {

        status = IRES_EFAIL; 

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
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
    _resmanInternalState->freeFxn(resourceMemRecs, numMemRecs); 

    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, 
            "IRESMAN_EDMA3CHAN_freeHandles> Exit (status=%d)\n", status);

    return (status); 
}

/*
 *  ======== _freeResource ========
 *  Actually free resources from the EDMA3 Low Level Resource Manager Handle
 */
static inline IRES_Status _freeResource(IALG_Handle algHandle, 
       Int scratchGroupId, short edma3Chan, short qdmaChan, 
       short numPaRams, short * paRamIndex, short numTccs, short * tccIndex) 
{

    EDMA3_ResDesc resObj;
    IRES_Status status = IRES_OK;
    EDMA3_Handle rmHandle;
    int i;

    GT_6trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, "_freeResource> Enter "
            "(algHandle=0x%x, scratchGroupId=%d, edma3Chan=%d, qdmaChan=%d, "
            "numPaRams=%d, numTccs=0x%x\n)",
            algHandle, scratchGroupId, edma3Chan, qdmaChan, numPaRams, numTccs);
    /*
     * Obtain Resource Manager handle corresponding to this algorithm in this 
     * scratch Group 
     */
    rmHandle = EDMA3_getResourceManager(algHandle, scratchGroupId);

     /*
      * Free all channel/param resources
      */
     if (IRES_EDMA3CHAN_CHAN_NONE != edma3Chan) {

         /*
          * Free allocated edma3 channel
          */
         resObj.type = EDMA3_RES_DMA_CHANNEL; 
         resObj.resId = edma3Chan;
         if (EDMA3_SOK != EDMA3_freeResource( rmHandle, &resObj)) {

                      GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_2CLASS, 
                      "_freeResource> Error releasing edma channel %d\n", 
                      edma3Chan);       

             status = IRES_EFAIL;
         }
     }
     
    if (IRES_EDMA3CHAN_CHAN_NONE != qdmaChan) {

        /*
         * Free allocated qdma channel
         */
        resObj.type = EDMA3_RES_QDMA_CHANNEL; 
        resObj.resId = qdmaChan;

        if (EDMA3_SOK != EDMA3_freeResource( rmHandle, &resObj)) {

            GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_7CLASS, 
                    "_freeResource> Error releasing qdma channel %d\n", 
                    qdmaChan);       
            status = IRES_EFAIL;
        }
    }

    resObj.type = EDMA3_RES_PARAM_SET;

    for (i = 0; i < numPaRams; i++) {

        /* 
         * Free the actual params back
         */
        resObj.resId = paRamIndex[i]; 

        if (EDMA3_SOK != EDMA3_freeResource( rmHandle, &resObj)) {

            GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_2CLASS, 
                    "_freeResource> Error releasing PaRam %d\n", 
                    paRamIndex[i]);       

            status = IRES_EFAIL;
        }
    }

    /*
     * Free Tcc
     */
    resObj.type = EDMA3_RES_TCC;
    for (i = 0; i < numTccs; i++) {

        resObj.resId = tccIndex[i];

        if (EDMA3_SOK != EDMA3_freeResource( rmHandle, &resObj)) {

                    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_2CLASS, 
                    "_freeResource> Error releasing tcc %d\n", tccIndex[i]);
        
            status = IRES_EFAIL;
        }
    }

    if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle, 
            scratchGroupId)) {

        status = IRES_EFAIL; 

        GT_0trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_2CLASS, 
                "_freeResource> Error releasing Low level "
                "Resource Manager Handle.\n");
    }

    GT_1trace(ti_sdo_fc_ires_edma3chan_GTMask, GT_ENTER, "_freeResource> Exit "
            "(status=%d)\n",status);

    return (status);
}

IRESMAN_Fxns IRESMAN_EDMA3CHAN =  {
    IRESMAN_EDMA3CHAN_getProtocolName,
    IRESMAN_EDMA3CHAN_getProtocolRevision,
    IRESMAN_EDMA3CHAN_init,
    IRESMAN_EDMA3CHAN_exit,
    IRESMAN_EDMA3CHAN_getHandles,
    IRESMAN_EDMA3CHAN_freeHandle
};

/*
 *  ======= setInternalState =======   
 */ 
static Void setInternalState(Void * addr)
{
    IRESMAN_Edma3Chan_InternalState * intState = 
            (IRESMAN_Edma3Chan_InternalState *)addr;

    intState->allocFxn = NULL; 
    intState->freeFxn = NULL; 
    intState->dchmapExists = 0;
    intState->initialized = FALSE;
}

/*
 *  ======== getInternalState ========
 */
static void getInternalState() 
{
    Int sharedMemId = -1;

    setInternalState(_resmanInternalState);
    _resmanInternalState->sharedMemId = sharedMemId;
}

/*
 *  ======== freeInternalState ========
 */
static void freeInternalState() 
{
}

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

