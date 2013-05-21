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
 *  ======== edma3_configArm.c ========
 */

/* TODO: Might be redundancy in the numOpens etc */
/* TODO: Optimize for persistent resources */


#include <xdc/std.h>

#ifdef xdc_target__os_Linux

#include <sys/shm.h>
#include <sys/ipc.h>
#include <ti/sdo/fc/utils/sharedMem.h>
#include <ti/sdo/fc/utils/lock.h>

#else

#include <stdlib.h>
#endif

#include <ti/sdo/linuxutils/edma/include/edma.h>
#include <ti/xdais/ialg.h>
#include <ti/sdo/fc/memutils/memutils.h>

#include "edma3_config.h"
#include "_edma3Arm.h"

#include <ti/sdo/utils/trace/gt.h>

GT_Mask ti_sdo_fc_edma3_GTMask;

#define EDMA3_MAXEDMAREQUESTS ti_sdo_fc_edma3_EDMA3_MAXEDMAREQUESTS


#define RESLIST(scratchIndex) (EDMA3_AllocUnit *)((unsigned int)pResTable +\
        EDMA3_MAXEDMAREQUESTS * (scratchIndex) )  

#define RESOURCE(scratchIndex,index) (EDMA3_AllocUnit *)\
        ((unsigned int)pResTable + sizeof(EDMA3_AllocUnit) * \
        (EDMA3_MAXEDMAREQUESTS * (scratchIndex)  + (index)))

#define EDMA3_PERSISTENTINDEX (EDMA3_MAXGROUPS) 
#define EDMA3_LATEACQUIREINDEX ((EDMA3_MAXGROUPS) + 1)

extern Int ti_sdo_fc_edma3_EDMA3_MAXEDMAREQUESTS;

/** To maintain the state of the EDMA3 Resource Manager Object */
typedef enum {
    EDMA3_DELETED   = 0,                 /** Object deleted */
    EDMA3_CREATED   = 1,                 /** Object Created */
    EDMA3_OPENED    = 2,                 /** Object Opened */
    EDMA3_CLOSED    = 3                  /** Object Closed */
} EDMA3_ObjState;

typedef struct EDMA3_AllocUnit {

    int busy;                              /* Bool value indicating if unit is
                                              busy or has been freed */
    int devId;                             /* EDMA #|EDMA_EDMAANY|
                                              EDMA_QDMA(0 -> 7)|EDMA_QDMAANY|
                                              EDMA_PARAMANY */
    int channel;                           /* EDMA or QDMA channel number */
    int param;                             /* PARAM number */
    int tcc;
    int nParams;                           /* number of PaRams */
    IALG_Handle alg;
} EDMA3_AllocUnit;

typedef struct EDMA3_ScratchInfo {
    int scratchId;
    int numHandles;                         /* Number of handle opened by this
                                               scratch group */
    //EDMA3_AllocUnit resources[EDMA3_MAXEDMAREQUESTS];
                                            /* Keep track of resources allocated
                                               as a unit, by this scratch grp */
    int numResources;                       /* Number of resource units
                                               allocated */
    IALG_Handle alg;                        /* Last algorithm to allocate this
                                               unit */
} EDMA3_ScratchInfo;


/* Global EDMA3 object shared among processes */
typedef struct EDMA3_Obj {

    unsigned int phyCntrllerInstId;         /* Physical ID of EDMA3 Controller*/
    EDMA3_ObjState state;                /* State of the Resource Manager */
    void * info;                            /* Info from the linuxutils module*/
    int sharedMemId;                        /* shared memory Id  */
    EDMA3_ScratchInfo group[EDMA3_MAXGROUPS + 2]; /* Scratch group info */
    int numOpens;                           /* Reference count for this module*/
} EDMA3_Obj;

/* Static handle held by each process */
static EDMA3_Obj * pResMgrObj = NULL;
static EDMA3_AllocUnit * pResTable = NULL;

#ifndef xdc_target__os_Linux

static EDMA3_Obj _EDMA3_resMgrObj;

#else

/* Static handle to the EDMA3 per process Lock  */
static LockMP_Handle _EDMA3_lock = NULL;
#endif

/* Number of times process opens handle returned */
static unsigned int _EDMA3_pOpens = 0;

/* Base address for the EDMA3 device */
static unsigned int _EDMA3_baseAddress = 0x0;

/* Function to initialize the pResMgrObj above */
static Void setInternalState(Void * addr);

static EDMA3_Result allocResource(int scratch, IALG_Handle alg,
        EDMA3_ResDesc *resObj, int num, int *pParam, int *tcc);

/* Funtion to construct the call to LSP and save resource scratch info */
static Bool allocAndSaveResource(int index, IALG_Handle alg, int devId,
        int *tcc, int *channel, int *param, int nParams);

/* Find if resource already exists in scratch group */
static Bool findResource(int scratch, IALG_Handle alg,
        EDMA3_ResDesc * resObj, int *param, int *tcc, int nParams);

/* Free the resource */
static Bool freeResource(int index, const EDMA3_ResDesc * resObj, int num);

static int resToDev(const EDMA3_ResDesc * resObj);

static Void devToRes(EDMA3_ResDesc * resObj, int devId, int tcc, int channel,
        int param,  int nParams);

/* Find an empty entry in the resource table for a particular scratch group */
static Int getEmptyTrack(int resTableIndex); 

/**
 *  @brief      Function to create the EDMA3  Resource Manager object
 *
 *  @retval     EDMA3_SOK or EDMA3_RM Error Code
 *
 */
EDMA3_Result EDMA3_createResourceManagerObject()
{
    int sharedMemId = -1;
    int status;

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
          "EDMA3_createResourceManagerObject> Enter\n");

    status = EDMA_init();

    if (status == -1) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "EDMA3_createResourceManagerObject> Failed to initialize "
                "ti.sdo.fc.linuxutils.edma module.\n");

        return (EDMA3_E_INVALID_PARAM);

    }

#ifdef xdc_target__os_Linux
    if (NULL == _EDMA3_lock) {

        /* Create a per process lock */
        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                "EDMA3_createResourceManagerObject> Creating a lock\n");

        _EDMA3_lock = LockMP_create(_EDMA3_LOCKID);

        if (_EDMA3_lock == NULL) {

            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                    "EDMA3_createResourceManagerObject> Failed to create IPC "
                    "lock, key = 0x%x\n", _EDMA3_LOCKID);

            return (EDMA3_E_INVALID_PARAM);
        }
    }

    /* Obtain shared memory for the pResMgrObj */
    pResMgrObj = (EDMA3_Obj *)SHM_getObj(
            _EDMA3_lock, sizeof(EDMA3_Obj) + (sizeof(EDMA3_AllocUnit) * 
            EDMA3_MAXEDMAREQUESTS * (EDMA3_MAXGROUPS + 2)), _EDMA3_LOCKID, 
            &setInternalState, &sharedMemId);
    pResTable = (EDMA3_AllocUnit *) ((unsigned int)pResMgrObj + 
            sizeof(EDMA3_Obj));
#else

        pResMgrObj = &_EDMA3_resMgrObj;
    pResTable = (EDMA3_AllocUnit *)malloc(sizeof(EDMA3_AllocUnit) *
            EDMA3_MAXEDMAREQUESTS * (EDMA3_MAXGROUPS + 2));
        setInternalState((void *)pResMgrObj);
        sharedMemId = 0;
#endif

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "EDMA3_createResourceManagerObject> Access shared memory "
            "segment to store internal state.\n", pResMgrObj);

    if (NULL == pResMgrObj) {

        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "EDMA3_createResourceManagerObject> Could not access shared "
                "memory.\n", pResMgrObj);

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_createResourceManagerObject> Exit"
                "(status=EDMA3_E_OBJ_NOT_OPENED)\n");

#ifdef xdc_target__os_Linux
        LockMP_delete(_EDMA3_lock);

        _EDMA3_lock = NULL;
#endif

        return (EDMA3_E_OBJ_NOT_OPENED);
    }

    pResMgrObj->sharedMemId = sharedMemId;

    if (pResMgrObj->numOpens == 0) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                "EDMA3_createResourceManagerObject> Initialize Linux kernel "
                "module\n");

        GT_assert(ti_sdo_fc_edma3_GTMask, _EDMA3_pOpens == 0);
    }

    if (pResMgrObj->state == EDMA3_DELETED) {

       pResMgrObj->state = EDMA3_CREATED;

    }

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_createResourceManagerObject> Exit(status=EDMA3_SOK)\n");

    return (EDMA3_SOK);
}

/**
 *  @brief      Function to delete the EDMA3  Resource Manager object
 *
 *  @retval     EDMA3_SOK or EDMA3_RM Error Code
 *
 */
EDMA3_Result EDMA3_deleteResourceManagerObject()
{
    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_deleteResourceManagerObject> Enter\n");

    GT_assert(ti_sdo_fc_edma3_GTMask, _EDMA3_pOpens == 0);

    GT_assert(ti_sdo_fc_edma3_GTMask, pResMgrObj != NULL);

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "EDMA3_deleteResourceManagerObject> Free shared memory segment"
            " at 0x%x\n", pResMgrObj);

    if (pResMgrObj->numOpens == 0) {

        GT_assert(ti_sdo_fc_edma3_GTMask, pResMgrObj->state == EDMA3_CLOSED);

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                "EDMA3_deleteResourceManagerObject> Last process to call "
                "delete, so call EDMA3_exit()\n");

        /* TODO: Check return value */
        EDMA_exit();

    }

#ifdef xdc_target__os_Linux
    SHM_freeObj(_EDMA3_lock, pResMgrObj, pResMgrObj->sharedMemId);

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "EDMA3_deleteResourceManagerObject> Deleting process lock\n");

    LockMP_delete(_EDMA3_lock);

    _EDMA3_lock = NULL;
#endif

    pResMgrObj = NULL;

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_deleteResourceManagerObject> Exit (status=EDMA3_SOK)\n");

    return (EDMA3_SOK);
}

/**
 *  @brief      Function to obtain a handle to the EDMA3  Resource
 *              Manager instance corresponding to a particular algorithm in a
 *              scratch group.
 *  @param[in]  algHandle       Algorithm Handle
 *  @param[in]  scratchGroupId  Scratch Group Id
 *
 *  @retval     NULL or valid handle
 */
EDMA3_Handle EDMA3_getResourceManager(IALG_Handle algHandle,
        int scratchGroupId)
{
    int index = 0;
    Void * addr = (Void *)algHandle;

    if (0 == _EDMA3_pOpens) {

        GT_init();

        GT_create(&ti_sdo_fc_edma3_GTMask, EDMA3_GTNAME);

        GT_2trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_getResourceManager> Enter (alg=0x%x, scratchId=%d)\n",
                algHandle, scratchGroupId);

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                "EDMA3_getResourceManager> First time handle is requested, "
                "create Resource Manager object\n");

        /* Create the resource manager object once */
        if (EDMA3_SOK != EDMA3_createResourceManagerObject()) {

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                    "EDMA3_getResourceManager> Resource Manager object "
                    "could not be created.\n");

            return (NULL);
        }

        GT_assert(ti_sdo_fc_edma3_GTMask, pResMgrObj != NULL);
    }
     else {

        GT_2trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_getResourceManager> Enter (alg=0x%x, scratchId=%d)\n",
                algHandle, scratchGroupId);
    }

    GT_assert(ti_sdo_fc_edma3_GTMask, ((pResMgrObj->state == EDMA3_CREATED)
            || (pResMgrObj->state == EDMA3_OPENED)));

    _EDMA3_pOpens++;

    pResMgrObj->numOpens++;


    GT_2trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "EDMA3_getResourceManager> Number of calls:- process %d, overall %d"
            "\n", _EDMA3_pOpens, pResMgrObj->numOpens);

    if (scratchGroupId == -1) {

        //index = EDMA3_MAXGROUPS;
        index = EDMA3_PERSISTENTINDEX;
    }
    else if (scratchGroupId == EDMA3_LATEACQUIREGROUP) {
        index = EDMA3_LATEACQUIREINDEX;
    }
    else {

        index = scratchGroupId;
    }

    pResMgrObj->group[index].numHandles++;

    if (algHandle != NULL) {
        addr = MEMUTILS_getPhysicalAddr((Ptr)algHandle);
    }

    /* Stow away the alg for now, will use in allocRes calls */
    pResMgrObj->group[index].alg = addr;

    pResMgrObj->state = EDMA3_OPENED;

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_getResourceManagerObject> Exit (handle=0x%x)\n",
            scratchGroupId);

    return ((EDMA3_Handle)&(pResMgrObj->group[index]));
}

/**
 *  @brief      Function to release the EDMA3  Resource Manager handle
 *              corresponding to a particular algorithm in a scratch group.
 *
 *  @param[in]  algHandle       Algorithm Handle
 *  @param[in]  scratchGroupId  Scratch Group Id
 *  @retval     EDMA3_SOK or EDMA3_RM Error Code
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
EDMA3_Result EDMA3_releaseResourceManager(IALG_Handle algHandle,
        int scratchGroupId)
{
    int index = -1;
    int lch = -1;
    EDMA3_AllocUnit * track = NULL;
    int nResources = -1;
    int i;

    GT_2trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_releaseResourceManagerObject> Enter (algHandle=0x%x, "
            "scratchId=%d)\n", algHandle, scratchGroupId);

    if (scratchGroupId == -1) {
        //index = EDMA3_MAXGROUPS;
        index = EDMA3_PERSISTENTINDEX;
    }
    else if (scratchGroupId == EDMA3_LATEACQUIREGROUP) {
        index = EDMA3_LATEACQUIREINDEX;
    }
    else {
        index = scratchGroupId;
    }

    pResMgrObj->group[index].numHandles--;

    _EDMA3_pOpens--;

    pResMgrObj->numOpens--;

    GT_2trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "EDMA3_releaseResourceManager> Number of calls:- process %d, "
            "overall %d\n", _EDMA3_pOpens, pResMgrObj->numOpens);

    /* If all handles in a particular scratch group are released, free all
       resources held by that scratch group */
    if (0 == pResMgrObj->group[index].numHandles) {

        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_4CLASS,
                "EDMA3_releaseResourceManagerObject> Freeing all resources "
                "held by this scratch group %d\n", scratchGroupId);

        /* Free all resources */
        nResources = pResMgrObj->group[index].numResources;

        for (i = 0; i < nResources; i++) {

            //track = &(pResMgrObj->group[index].resources[i]);
            track = RESOURCE(index, i); 

            if (track->busy) {

                lch = track->channel;

/* TODO: If we use unregister mechanism, maybe there should be nothing here ?!*/
                GT_2trace(ti_sdo_fc_edma3_GTMask, GT_4CLASS,
                        "EDMA3_releaseResourceManagerObject> Free logical "
                        "channel %d with %d params\n", lch, track->nParams);

                if (EDMA_OK == EDMA_freeResource(lch, track->nParams)) {
                    track->alg = NULL;
                    track->devId = -1;
                    track->param = -1;
                    track->nParams = -1;
                    track->busy = 0;
                    track->channel = -1;
                }
                else {
                    /* Print warning, but continue to free */
                    GT_2trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                            "EDMA3_releaseResourceManagerObject> Error freeing "
                            "logical channel %d with %d params\n", lch,
                            track->nParams);
                }
            }
        }
        pResMgrObj->group[index].numResources = 0;
    }

    if (0 == pResMgrObj->numOpens) {
        pResMgrObj->state = EDMA3_CLOSED;
    }

    if (0 == _EDMA3_pOpens) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                "EDMA3_releaseResourceManagerObject> Delete resource manager "
                "object.\n");

        EDMA3_deleteResourceManagerObject();
    }

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_releaseResourceManagerObject> Exit "
            "(status=EDMA3_SOK)\n") ;

    return (EDMA3_SOK);
}

/*
 *  ======== EDMA3_allocResource ========
 *  Allocate resource
 */
EDMA3_Result EDMA3_allocResource (EDMA3_Handle hEdmaResMgr,
        EDMA3_ResDesc *resObj)
{
    int scratch = (int)(((EDMA3_ScratchInfo *)hEdmaResMgr)->scratchId);
    int param = EDMA_PARAMANY;
    int tcc = -1;
    IALG_Handle alg = (IALG_Handle)(((EDMA3_ScratchInfo *)hEdmaResMgr)->alg);
    EDMA3_Result status = EDMA3_SOK;

    GT_4trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_allocResource> Enter (hEdmaResMgr=0x%x, resObj->resId=%d"
            " resObj->type=%d, scratch=%d)\n", hEdmaResMgr, resObj->resId,
            resObj->type, scratch);

    if (resObj->type == EDMA3_RES_PARAM_SET) {

        /* No TCC is required for PaRam requests */
        tcc = -1;

        /* Check for bad requests */
        if ((resObj->resId != EDMA3_RES_ANY) && (resObj->resId >= 64)) {

           GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                   "EDMA3_allocResource> Bad request for PaRam %d, "
                   "cannot request PaRams > 64 by number. Must request "
                   "as ANY.\n", resObj->resId);

           status = EDMA3_E_INVALID_PARAM;

           GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                   "EDMA3_allocResource> Exit (status=%d)\n", status);

            return (status);
        }
    }
    else {
         if ((resObj->type == EDMA3_RES_DMA_CHANNEL) ||
                (resObj->type == EDMA3_RES_TCC)) {
            /* If request is for an EDMA channel, change this to TCC SYMM */
            tcc = EDMA_TCCSYMM;
        }
        else {
            tcc = EDMA_TCCANY;
        }
    }

    status = allocResource(scratch, alg, resObj, 1, (int *)&param, (int *)&tcc);

    if (status == EDMA3_SOK)  {

        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_4CLASS,
                "EDMA3_allocResource> Alloced Channel %d \n" ,
                resObj->resId);
    }

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_allocResource> Exit (status=%d)\n", status);

    return (status);
}

EDMA3_Result EDMA3_allocLogicalChannel(EDMA3_Handle hEdmaResMgr,
        EDMA3_ResDesc *lChObj, unsigned int *pParam, unsigned int *pTcc)
{
    /* Only requests for logical channel #N or logical channel ANY where
       all resources are the same number, are supported */
    /* Assert that ! */
    EDMA3_Result status = EDMA3_SOK;
    int scratch = (int)(((EDMA3_ScratchInfo *)hEdmaResMgr)->scratchId);
    IALG_Handle alg = (IALG_Handle)(((EDMA3_ScratchInfo *)hEdmaResMgr)->alg);

    GT_6trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_allocLogicalChannel> Enter (hEdmaResMgr=0x%x,"
            "resObj->resId=%d, resObj->type=%d, *pParam=%d, *pTcc=%d, "
            "scratch=%d)\n", hEdmaResMgr, lChObj->resId, lChObj->type,
            *pParam, *pTcc, scratch);

    /* Assert that that *pParam is IRES_EDMA3CHAN_PARAMANY */
    GT_assert(ti_sdo_fc_edma3_GTMask,
            ((*pParam == EDMA3_RES_ANY) || (*pParam == lChObj->resId)));

    *pParam = EDMA_PARAMANY;

    if (*pTcc ==EDMA3_RES_ANY) {

        if (lChObj->type == EDMA3_RES_DMA_CHANNEL) {
            /* If request is for an EDMA channel, change this to TCC SYMM */
            *pTcc = EDMA_TCCSYMM;
        }
        else {
            *pTcc = EDMA_TCCANY;
        }

    }

    status = allocResource(scratch, alg, lChObj, 1, (int *)pParam,
            (int *)pTcc);

    GT_3trace(ti_sdo_fc_edma3_GTMask, GT_4CLASS,
            "EDMA3_allocLogicalChannel> Allocd Channel %d Param %d Tcc %d\n"
            ,lChObj->resId, *pParam, *pTcc);

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_allocLogicalChannel> Exit (status=%d)\n", status);

    return (status);
}

EDMA3_Result EDMA3_freeContiguousResource(EDMA3_Handle hEdmaResMgr,
        EDMA3_ResDesc *resObj, unsigned int num)
{
    int scratch = (int)(((EDMA3_ScratchInfo *)hEdmaResMgr)->scratchId);
    int index = scratch;

    GT_4trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_freeContiguousResource> Enter (hEdmaResMgr=0x%x, "
                    "resObj->type=%d resObj->resId=%d num=%d)\n", hEdmaResMgr, 
                    resObj->type, resObj->resId, num);

    if (-1 == scratch) {
        index = EDMA3_PERSISTENTINDEX;
    }
    else if (EDMA3_LATEACQUIREGROUP == scratch) {
        index = EDMA3_LATEACQUIREINDEX;
    }

    if (TRUE == freeResource(index, resObj, num)) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_freeContiguousResource> Exit "
                "(status=EDMA3_SOK)\n");

        return (EDMA3_SOK);
    }

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_freeContiguousResource> Exit "
                    "(status=EDMA3_E_RES_NOT_OWNED)\n");

    return (EDMA3_E_RES_NOT_OWNED);

}

EDMA3_Result EDMA3_freeResource(EDMA3_Handle hEdmaResMgr,
        const EDMA3_ResDesc *resObj)
{
    int scratch = (int)(((EDMA3_ScratchInfo *)hEdmaResMgr)->scratchId);
    int index = scratch;

    GT_3trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_freeResource> Enter (hEdmaResMgr=0x%x, resObj->type=%d"
            "resObj->resId=%d)\n", hEdmaResMgr, resObj->type, resObj->resId);

    if (-1 == scratch) {
        index = EDMA3_PERSISTENTINDEX;
    }
    else if (EDMA3_LATEACQUIREGROUP == scratch) {
        index = EDMA3_LATEACQUIREINDEX;
    }

    if (TRUE == freeResource(index, resObj, 1)) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_freeResource> Exit "
                "(status=EDMA3_SOK)\n");

        return (EDMA3_SOK);
    }

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_freeResource> Exit (status=EDMA3_E_RES_NOT_OWNED)\n");

    return (EDMA3_E_RES_NOT_OWNED);
}

EDMA3_Result EDMA3_allocContiguousResource(EDMA3_Handle hEdmaResMgr,
        EDMA3_ResDesc *firstResIdObj, unsigned int numResources)
{
    int scratch = (int)(((EDMA3_ScratchInfo *)hEdmaResMgr)->scratchId);
    EDMA3_Result status = EDMA3_SOK;
    int param = -1;
    int tcc = -1;
    IALG_Handle alg = (IALG_Handle)(((EDMA3_ScratchInfo *)hEdmaResMgr)->alg);

    GT_4trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_allocContiguousResource> Enter (hEdmaResMgr=0x%x, "
            "resObj->type=%d, resObj->resId=%d,  numResource=%d)\n",
            hEdmaResMgr, firstResIdObj->type, firstResIdObj->resId,
            numResources);

    GT_assert(ti_sdo_fc_edma3_GTMask, firstResIdObj->type ==
            EDMA3_RES_PARAM_SET);

    if (firstResIdObj->type != EDMA3_RES_PARAM_SET) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "EDMA3_allocContiguousResource> Contiguous requests "
                "supported only for PaRams.\n");

        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_allocContiguousResource> Exit (status=%d)\n", status);

        return (EDMA3_E_RES_NOT_ALLOCATED);
    }

    /* Can check and refuse if request is for anything other than PaRams */
    status = allocResource(scratch, alg, firstResIdObj, numResources,
            (int *)&param, (int *)&tcc );

    GT_2trace(ti_sdo_fc_edma3_GTMask, GT_4CLASS,
            "EDMA3_allocContiguousResource> Alloced %d Params starting "
            "from %d\n", numResources, firstResIdObj->resId);

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_allocContiguousResource> Exit (status=%d)\n", status);

    return (status);
}

EDMA3_Result EDMA3_getCCRegister(EDMA3_Handle hEdmaResMgr,
        unsigned int regOffset, unsigned int *regValue)
{
    EDMA3_Result status = EDMA3_SOK;
    unsigned int regPhyAddr;

    GT_2trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_getCCRegister> Enter (hEdmaResMgr=0x%x, "
            "regOffset=%d)\n", hEdmaResMgr, regOffset);

    if (((hEdmaResMgr == NULL) || (regValue == NULL))
            || ((regOffset % 4u) != 0)) {

        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_getCCRegister> Exit (status=%d)\n",
                EDMA3_E_INVALID_PARAM);

        return (EDMA3_E_INVALID_PARAM);
    }

    if (0x0 == _EDMA3_baseAddress) {

        status = EDMA3_getBaseAddress(hEdmaResMgr, (EDMA3_Cntrlr_PhyAddr)
                                ti_sdo_fc_edma3_EDMA3_physicalId, 
                (unsigned int *)&_EDMA3_baseAddress);

        if (EDMA3_SOK != status) {

            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                    "EDMA3_getCCRegister> Exit (status=%d)\n", status);

            return (status);
        }

    }

    regPhyAddr = (unsigned int)(_EDMA3_baseAddress) + regOffset;

    *regValue = *(unsigned int *)regPhyAddr;

    GT_2trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_getCCRegister> Exit (status=%d, *regValue =0x%x)\n",
            status, *regValue);

    return (EDMA3_SOK);
}

/* ARGSUSED - this line tells the compiler not to warn about unused args. */
EDMA3_Result EDMA3_getBaseAddress(EDMA3_Handle hEdmaResMgr,
        EDMA3_Cntrlr_PhyAddr controllerId, unsigned int *phyAddress)
{
/* Assert the controller id */
/* TODO: Check if this is alright */

    unsigned int * addr = (unsigned int *)&_EDMA3_baseAddress;
    EDMA3_Result status = EDMA3_SOK;

    GT_2trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_getBaseRegister> Enter (hEdmaResMgr=0x%x, "
            "controllerId=%d)\n", hEdmaResMgr, controllerId);

    if (0x0 == *addr) {

        status = EDMA_mapBaseAddress((void **)addr);

        if (status != EDMA_OK) {

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "EDMA3_getCCRegister> Error obtaining base address from"
                " ti.sdo.linuxutils.edma\n");

            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_getCCRegister> Exit (status=%d)\n", status);

            return (EDMA3_E_INVALID_STATE);
        }
    }

    *phyAddress = _EDMA3_baseAddress;

    GT_2trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_getCCRegister> Exit (status=%d, *phyAddress =0x%x)\n",
            status, *phyAddress);

    return (EDMA3_SOK);
}

EDMA3_Result EDMA3_freeLogicalChannel(EDMA3_Handle hEdmaResMgr,
        EDMA3_ResDesc *lChObj)
{
    int scratch = (int)(((EDMA3_ScratchInfo *)hEdmaResMgr)->scratchId);
    int index = scratch;

    GT_3trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_freeLogicalChannel> Enter (hEdmaResMgr=0x%x, "
            "resObj->type=%d, resObj->resId=%d)n", hEdmaResMgr, lChObj->type,
            lChObj->resId);

    if (-1 == scratch) {
        index = EDMA3_PERSISTENTINDEX;
    }
    else if (EDMA3_LATEACQUIREGROUP == scratch) {
        index = EDMA3_LATEACQUIREINDEX;
    }

    if (TRUE == freeResource(index, lChObj, 1)) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_freeLogicalChannel> Exit (status=EDMA3_SOK)\n");

        return (EDMA3_SOK);
    }

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_freeLogicalChannel> Exit "
            "(status=EDMA3_E_RES_NOT_OWNED)\n");

    return (EDMA3_E_RES_NOT_OWNED);
}

/*
 *  ======= setinternalState =======
 */
static Void setInternalState(Void * addr)
{
    EDMA3_Obj * rmObj = (EDMA3_Obj *)addr;
    int i = 0;
    int j = 0;
#ifdef xdc_target__os_Linux
    EDMA3_AllocUnit * unit = (EDMA3_AllocUnit *)((unsigned int)addr + 
            sizeof(EDMA3_Obj));
#else
    EDMA3_AllocUnit * unit = (EDMA3_AllocUnit *)pResTable;
#endif

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "setInternalState> Enter (addr=0x%x)\n", addr);

    if (NULL != rmObj) {
        rmObj->phyCntrllerInstId = ti_sdo_fc_edma3_EDMA3_physicalId;
        rmObj->state = EDMA3_DELETED;
        rmObj->numOpens = 0;
        rmObj->sharedMemId = -1;
        rmObj->info = NULL;

     /* Initialize the scratch group information */

        for (i = 0; i < EDMA3_MAXGROUPS + 2; i++) {

            rmObj->group[i].numHandles = 0;
            rmObj->group[i].numResources = 0;
            rmObj->group[i].scratchId = i;
            rmObj->group[i].alg = NULL;
            /*
            for (j = 0; j < EDMA3_MAXEDMAREQUESTS; j++) {
                rmObj->group[i].resources[j].busy = 0;
            }
            */
        }

        rmObj->group[EDMA3_PERSISTENTINDEX].scratchId = -1;
        rmObj->group[EDMA3_LATEACQUIREINDEX].scratchId = EDMA3_LATEACQUIREGROUP;

        for (j = 0; j < (EDMA3_MAXGROUPS + 2) * EDMA3_MAXEDMAREQUESTS; j++) {
            unit[j].busy = 0;
        }
    }

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "setInternalState> Exit\n");
}

/*
 * If request for scratch resources, tries to find an existing request that
 * satisfies the request (findResource), else allocates it from LSP
 * (allocAndSave)
 * If request is for persistent resources, then allocates it from LSP
 * (allocAndSave)
 */
static EDMA3_Result allocResource(int scratch, IALG_Handle alg,
        EDMA3_ResDesc *resObj, int num, int * pParam, int * pTcc)
{
    EDMA3_Result status = EDMA3_SOK;
    int devId = -1;
    int channel = EDMA_EDMAANY;
    int nParams = num;
    int index;

    GT_6trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "allocResource> Enter (scratch=%d, resObj->type=%d, resObj->resId"
            "=%d, numP=%d, *pParam=%d, pTcc=%d)\n", scratch, resObj->type,
            resObj->resId, num, *pParam, *pTcc);

    devId = resToDev(resObj);

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "allocResource> Equivalent devId %d\n", devId);

    if (-1 == scratch) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                "allocResource> Persistent resource\n");

        index = EDMA3_PERSISTENTINDEX;
    }
    else {

        if (scratch == EDMA3_LATEACQUIREGROUP) {
            index = EDMA3_LATEACQUIREINDEX;
        }
        else {
            index = scratch;
        }

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                "allocResource> Scratch resource\n");

        /* Check requested resource in resources for index */
        if (TRUE == findResource(index, alg, resObj, pParam, pTcc, nParams)) {

            /* If available, return OK */
            GT_3trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                    "allocResource> Found resource, scratch group %d resObj "
                    "type %d Id %d\n", scratch, resObj->type, resObj->resId);

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                    "allocResource> Exit (status=EDMA3_SOK)\n");

            return (status);
        }
    }

    if (TRUE == (allocAndSaveResource(index, alg, devId, pTcc, &channel, pParam,
            nParams))) {

        GT_5trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                "allocResource> Allocated new resource %d, channel %d, tcc %d"
                " param %d numParams %d\n", devId, channel, *pTcc, *pParam,                     nParams);

        /* Convert resource to resObj */
        devToRes(resObj, devId, (int)*pTcc, channel, (int)*pParam, nParams);

        GT_2trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                "allocResource> Returning resource resObj->type %d "
                "resObj->resId %d\n", resObj->type, resObj->resId);
    }
    else {

       GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
               "allocResource> Resource allocation failed\n");

       status = EDMA3_E_RES_NOT_OWNED;
    }

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "allocResource> Exit (status=%d)\n", status);

   return  (status);
}

static Bool allocAndSaveResource(int index, IALG_Handle alg, int devId,
        int *tcc, int *channel, int *param, int nParams)
{
    EDMA3_AllocUnit * track = NULL;
    int nResources = -1;
    int tabIndex = nResources;

    GT_6trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "allocAndSaveResource> Enter (index=%d, devId=%d, channel=%d, "
            "*tcc=%d, *param=%d, nParams=%d)\n", index, devId, channel, *tcc,
            *param, nParams);

    nResources = pResMgrObj->group[index].numResources;

    /*
    GT_assert(ti_sdo_fc_edma3_GTMask, nResources !=
            EDMA3_MAXEDMAREQUESTS);
    */

    if (nResources == EDMA3_MAXEDMAREQUESTS) {
        /* Find an empty entry to use */
        tabIndex = getEmptyTrack(index);
    }
    else {
        tabIndex = nResources;
    }

    if (tabIndex == EDMA3_MAXEDMAREQUESTS) {

         GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "allocAndSaveResource> Number of resource requests exceeded "
                "configured maxRequests = %d\n", EDMA3_MAXEDMAREQUESTS);

         GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "allocAndSaveResource>  Exit (status=FALSE)\n");

        return (FALSE);
    }

    /* Get resource from LSP */
    if (EDMA_OK != EDMA_getResource(devId, tcc, channel, param, nParams)) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "allocAndSaveResource>  Exit (status=FALSE)\n");

        return (FALSE);
    }

    GT_5trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
           "allocAndSaveResource>  Obtained resource (devId = %d, channel = %d,"
            "tcc = %d, param = %d, numParams = %d), save in Internal State"
            "\n", devId, *channel, *tcc, *param, nParams);

    /* Save the resource info */
    //track = &(pResMgrObj->group[index].resources[tabIndex]);
    track = RESOURCE(index, tabIndex);

    /* Store entire contents as-is */
    track->devId = devId;           /* Specific QDMA/EDMA number of ANY */
    track->channel = *channel;      /* Specific EDMA/QDMA/PARAM number */
    track->param = *param;          /* Param number */
    track->tcc = *tcc;              /* Tcc number or -1 */
    track->nParams = nParams;
    track->busy = 1;
    track->alg = alg;
    if ((tabIndex +1) > pResMgrObj->group[index].numResources) {
        /* We used up a new entry, so increment numResources */
        pResMgrObj->group[index].numResources = tabIndex + 1;
    }

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "allocAndSaveResource> Exit (status=TRUE)\n");

    return (TRUE);
}

static Bool findResource(int index, IALG_Handle alg, EDMA3_ResDesc * resObj,
        int *param, int *tcc, int nParams)
{
    EDMA3_AllocUnit * track = NULL;
    Bool found = FALSE;
    int i = 0;
    Int devId = -1;
    EDMA3_ResDesc tccObj = {(unsigned int)-1, EDMA3_RES_TCC};
    int nResources = pResMgrObj->group[index].numResources;

    GT_4trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "findResource> Enter (index=%d, alg=0x%x, resObj->type=%d, "
            "resObj->resId=%d)\n", index, alg, resObj->type, resObj->resId);

    GT_3trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "findResource> Enter (*tcc=%d, *param=%d, nParams=%d)\n", *tcc,
            *param, nParams);

    if (0 == nResources) {
        return (FALSE);
    }

    /* Assert that index != -1 */

    devId = resToDev(resObj);

    if (devId == -1) {
        return (FALSE);
    }

    switch(devId) {

        case EDMA_EDMAANY:
            /* track to anything that has an EDMA */
            GT_assert(ti_sdo_fc_edma3_GTMask, nParams == 1);

            for (i = 0; i < nResources; i++) {

                //track  = &(pResMgrObj->group[index].resources[i]);
                track  = RESOURCE(index,i);
                /* Looking for existing resources alloc-ed by other algs */

                if ((track->busy) && (track->alg != alg)) {
                    if (((track->devId == EDMA_EDMAANY) ||
                            (track->devId < 64)))  {

                        resObj->resId = track->channel;
                        GT_assert(ti_sdo_fc_edma_GTMask, track->channel ==
                                track->param);
                        GT_assert(ti_sdo_fc_edma_GTMask, track->channel ==
                                track->tcc);
                        *param = track->param;
                        *tcc = track->tcc;
                        found = TRUE;
                        break;
                    }
                }
            }
        break;
        case EDMA_QDMAANY:

            GT_assert(ti_sdo_fc_edma3_GTMask, nParams == 1);

            /* track to anything that has a QDMA */
            for (i = 0; i < nResources; i++) {

                //track  = &(pResMgrObj->group[index].resources[i]);
                track  = RESOURCE(index,i);

                /* Looking for existing resources alloc-ed by other algs */
                if ((track->busy) && (track->alg != alg)) {
                    if ((track->devId == EDMA_QDMAANY) ||
                            ((track->devId >= EDMA_QDMA(0)) &&
                            (track->devId <= EDMA_QDMA(7)))) {

                        /* Any QDMA channel may be requested with a fixed tcc */
                        if ((*tcc == -1) || (*tcc == EDMA_TCCANY)) {
                            /* Don't care for TCC */
                            *tcc = track->tcc;
                            found = TRUE;
                        }
                        else {
                            /* Specific tcc requested */
                            if (*tcc != track->tcc) {

                                /* Doesn't match the tcc found here */
                                tccObj.resId = *tcc;

                                /* Try searchign for it in other entries */
                                found = findResource(index, alg, &tccObj,
                                        param, tcc, 1);
                                /* If found tcc is updated with the tcc
                                   required, else tcc is don't care  */
                            }
                            else {
                                found = TRUE;
                            }
                        }
                        resObj->resId = EDMA_QDMA2NUM(track->channel);
                        *param = track->param;
                        break;
                    }
                }
            }
        break;

        case EDMA_PARAMANY:

            /* track to anything that has a PaRam */
            for (i = 0; i < nResources; i++) {

                //track  = &(pResMgrObj->group[index].resources[i]);
                track  = RESOURCE(index, i);

                /* Looking for existing resources alloc-ed by other algs */
                if ((track->busy) && (track->alg != alg)) {
                    if ((track->devId == EDMA_PARAMANY) ||
                            ((track->param >= 64) && (track->param < 512))) {
                        if (nParams > track->nParams) {

                            /* If more params requested than part of this unit,                                give up */
/* TODO: Eventually could search for adjacent numbered params   */
                                continue;
                        }
                        else {
                            /* If params required are all here , great !*/
                            resObj->resId = track->param;
                            found = TRUE;
                            break;
                        }
                    }
                }
            }
        break;

        default:

            /* Looking for a specific EDMA or QDMA channel or Param */
            for (i = 0; i < nResources; i++) {

                //track  = &(pResMgrObj->group[index].resources[i]);
                track  = RESOURCE(index, i);

                /* Looking for existing resources alloc-ed by other algs */
                if ((track->busy) && (track->alg != alg)) {

                    if (devId < 64) {
                        if (((track->devId == EDMA_EDMAANY) &&
                                (track->channel == devId)) ||
                                ((track->devId == devId))) {
                            if (nParams > track->nParams) {
                                /* Could be a request for EDMA channel or Param
                                   if its < 64 */
                                continue;
                            }
                            *param = track->param;
                            *tcc = track->tcc;
                            resObj->resId = track->channel;
                            found = TRUE;
                            break;
                        }
                        else {
                            continue;
                        }
                    }
                    else if ((devId >= EDMA_QDMA0) && (devId <= EDMA_QDMA7)) {

                        if (((track->devId == EDMA_QDMAANY) &&
                                (track->channel == devId)) ||
                                ((track->devId == devId))) {
                            if ((*tcc == -1) || (*tcc == EDMA_TCCANY)) {
                                /* Don't care for TCC */
                                *tcc = track->tcc;
                                found = TRUE;
                            }
                            else {

                                /* Specific tcc requested */
                                if (*tcc != track->tcc) {

                                    /* Doesn't match the tcc found here */
                                    tccObj.resId = *tcc;

                                    /* Try searchign for it in other entries */
                                    found = findResource(index, alg, &tccObj,
                                            param, tcc, 1);
                                }
                                else {
                                    found = TRUE;
                                }
                            }
                            *param = track->param;
                            resObj->resId = EDMA_QDMA2NUM(track->channel);
                            break;
                        }
                        else {
                            continue;
                        }
                    }
                    else if (devId < 512) {

                        /* Request for a specific PaRam  (>= 64) */
                         if ((((track->devId == EDMA_PARAMANY) &&
                                (track->param == devId)) ||
                                ((track->devId == devId))) &&
                                (nParams <= track->nParams)) {
                            resObj->resId = track->param;
                            *param = track->param;
                            *tcc = -1;
                            resObj->resId = *param;
                            found = TRUE;
                       }
                    }
                    else {
                        GT_assert(ti_sdo_fc_edma3_GTMask, 0);
                    }
                }
            }
        break;
    }

    if (found) {
        track->alg = alg;
        
        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "findResource> Calling "
            "register on %d\n",track->devId);

        EDMA_registerResource(track->channel);
        track->busy++;
    }

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "findResource> Exit (found=%d)"
            "\n",found);
    return (found);
}

static Bool freeResource(int index, const EDMA3_ResDesc * resObj, int num)
{
    EDMA3_AllocUnit * track = NULL;
    Bool freeRes = FALSE;
    Bool status = FALSE;
    int nResources = pResMgrObj->group[index].numResources;
    int i;

    /* Find the EDMA channel or QDMA channel you are trying to free */
    int devId = resToDev(resObj);

    GT_4trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "freeResource> Enter (index=%d"
            ", resObj->type=%d, resObj->resId=%d, num=%d)\n", index,
            resObj->type, resObj->resId, num);

    GT_assert(ti_sdo_fc_edma3_GTMask, index <= EDMA3_LATEACQUIREINDEX);

    switch (resObj->type) {

        case EDMA3_RES_DMA_CHANNEL:
        case EDMA3_RES_TCC:
            GT_assert(ti_sdo_fc_edma3_GTMask, devId < 64);
            for (i = 0; i < nResources; i++) {
                //track  = &(pResMgrObj->group[index].resources[i]);
                track  = RESOURCE(index, i);
                if (track->busy)
                    if ((track->devId == devId) ||
                            (track->channel == devId)) {
                        /* Free resource */
        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "freeResource> Calling "
            "unregister on %d\n",devId);

                        EDMA_unregister(devId, 0);
                        track->busy--;
                        track->alg = NULL;
                        freeRes = TRUE;
                        status = TRUE;
                        break;
                    }
            }
        break;

        case EDMA3_RES_QDMA_CHANNEL:
            GT_assert(ti_sdo_fc_edma3_GTMask, ((devId >= EDMA_QDMA(0)) &&
                    (devId <= EDMA_QDMA(7))));
            for (i = 0; i < nResources; i++) {
                //track  = &(pResMgrObj->group[index].resources[i]);
                track  = RESOURCE(index,i);
                if (track->busy)
                    if ((track->devId == devId) || (track->channel == devId)) {
                        /* Free resource */
                        EDMA_unregister(devId, 0);
        
        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "freeResource> Calling "
            "unregister on %d\n",devId);

                        track->busy--;
                        track->alg = NULL;
                        freeRes = TRUE;
                        status = TRUE;
                        break;
                    }
            }
        break;

        case EDMA3_RES_PARAM_SET:

            if (resObj->resId < 64) {

                for (i = 0; i < nResources; i++) {

                    //track  = &(pResMgrObj->group[index].resources[i]);
                    track  = RESOURCE(index, i);

                    if (track->busy)
                        if ((track->devId == devId) ||
                                (track->channel == devId)) {
                            /* Free resource */
                            EDMA_unregister(devId, 0);
        
        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "freeResource> Calling "
            "unregister on %d\n",devId);

                            track->busy--;
                            track->alg = NULL;
                            freeRes = TRUE;
                            status = TRUE;
                            break;
                        }
                }
            }
            else {
                GT_assert(ti_sdo_fc_edma3_GTMask, devId < 512);
                for (i = 0; i < nResources; i++) {

                    //track  = &(pResMgrObj->group[index].resources[i]);
                    track  = RESOURCE(index, i);

                    if (track->busy)
                        if ((track->devId == EDMA_PARAMANY) &&
                                (devId == track->param)) {
                            if (num > track->nParams) {

                                /* If freeRes a match, but more params are being
                                   freed, complain */

                                break;
                            }
                            else if (num == track->nParams) {
                                /* If all the params are being freed, great !*/
        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "freeResource> Calling "
            "unregister on %d\n",devId);

                                EDMA_unregister(devId,num);
                                track->busy--;
                                track->alg = NULL;
                                freeRes = TRUE;
                                status = TRUE;
                                break;
                            }
                            else {
/* TODO: Tricky one, this is the same track, so one less user, but fewer params
         are being freed than were requested the first time, so we still
         decrease the number of processes using this track */
        
        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "freeResource> Calling "
            "unregister on %d\n",devId);

                                EDMA_unregister(devId,num);
                                status = TRUE;
                                track->alg =  NULL;
                                track->busy--;
                            }
                        }
                   }
            }
        break;
    }

    /* Need to re-init this entry if everyone has freed it */  
    if ((TRUE == freeRes) && (track->busy == 0)) {
        /* Remove entry from list */
        track->devId = -1;
        track->channel = -1;
        track->param = -1;
        track->nParams = -1;
        track->alg = NULL;
    }

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "freeResource> Exit (status=%d)"
            "\n",status);

    return (status);
}

static int resToDev(const EDMA3_ResDesc * resObj)
{
    int devId;

    GT_2trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "resToDev> Enter "
            "(resObj->type=%d, resObj->resId=%d)\n", resObj->type,
            resObj->resId);

    switch(resObj->type) {

        case EDMA3_RES_DMA_CHANNEL:
            if (resObj->resId == EDMA3_RES_ANY) {
                devId = EDMA_EDMAANY;
            }
            else {
                GT_assert(ti_sdo_fc_edma3_GTMask, resObj->resId < 64);
                devId = resObj->resId;
            }
            break;
        case EDMA3_RES_QDMA_CHANNEL:
            if (resObj->resId == EDMA3_RES_ANY) {
                devId = EDMA_QDMAANY;
            }
            else {
                GT_assert(ti_sdo_fc_edma3_GTMask, (resObj->resId < 8));
                devId = EDMA_QDMA(resObj->resId);
            }
            break;
        case EDMA3_RES_TCC:
        /* LSP doesn't allow requests for TCC, so convert it to
           request for the same EDMA channel */
            if (resObj->resId == EDMA3_RES_ANY) {
                devId = EDMA_EDMAANY;
            }
            else {
                GT_assert(ti_sdo_fc_edma3_GTMask, resObj->resId < 64);
                devId = resObj->resId;
            }
            break;
        case EDMA3_RES_PARAM_SET:
            if (resObj->resId == EDMA3_RES_ANY) {
                devId = EDMA_PARAMANY;
            }
            else {
                GT_assert(ti_sdo_fc_edma3_GTMask, resObj->resId < 512);
                devId = resObj->resId;
            }
            break;

        default:
            /* Unknown resource type! */
            GT_assert(ti_sdo_fc_edma3_GTMask, FALSE);
            devId = -1;

            break;
    }

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "resToDev> Exit "
            "(devId=%d)\n", devId);

    return (devId);
}

/* ARGSUSED - this line tells the compiler not to warn about unused args. */
static Void devToRes(EDMA3_ResDesc * resObj, int devId, int tcc, int channel,
        int param,  int nParams)
{

    GT_5trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "devToRes> Enter "
            "(devId=%d, tcc=%d, channel=%d, param=%d, nParams=%d)\n", devId,
                        tcc, channel, param, nParams);


    switch(resObj->type) {
        case EDMA3_RES_DMA_CHANNEL:
            if (resObj->resId == EDMA3_RES_ANY) {
                resObj->resId = channel;
            }
            else {
/* TODO: Assert the value of channel */
            }
        break;

        case EDMA3_RES_QDMA_CHANNEL:
            if (resObj->resId == EDMA3_RES_ANY) {
                resObj->resId = EDMA_QDMA2NUM(channel);
            }
            else {
/* TODO: Assert the value of channel */
            }
        break;

        case EDMA3_RES_TCC:
/* LSP doesn't allow requests for TCC, so convert it to request for the same
   EDMA channel */
             if (resObj->resId == EDMA3_RES_ANY) {
                /* Converted this request into a request for channel */
                resObj->resId = channel;
            }
            else {
/* TODO: Assert the value of *channel */
            }
        break;

        case EDMA3_RES_PARAM_SET:
              if (resObj->resId == EDMA3_RES_ANY) {
                  resObj->resId = param;
              }
              else {
                if (resObj->resId >= 64) {
                    resObj->resId = param;
                }
                else {
                    /* If a param < 64 was requeted, LSP thought it was a
                       request for a channel !*/
                    resObj->resId = channel;
                }
              }
        break;
    }

    GT_2trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "resToDev> Exit "
            "(resObj->type=%d, resObj->resId=%d)\n", resObj->type,
            resObj->resId);
}


static Int getEmptyTrack(int resTableIndex) 
{
    int tabIndex = EDMA3_MAXEDMAREQUESTS;
    int count = pResMgrObj->group[resTableIndex].numResources;
    EDMA3_AllocUnit * track = NULL;
    int i = -1;

    for (i = 0; i < count; i++) {
        //track = &(pResMgrObj->group[resTableIndex].resources[i]);
        track  = RESOURCE(resTableIndex, i);
        if (!(track->busy)) {
            tabIndex = i;
            break;
        }
    }
    return (tabIndex);
}
/*
 *  @(#) ti.sdo.fc.edma3; 3, 0, 0,152; 12-1-2010 17:24:42; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

