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
 *  ======== rtcfg_rman.c ========
 *  RMAN configuration for non-RTSC config examples. Compile this file as is,
 *  with apps that don't use RMAN. For apps whose local codecs use RMAN, copy
 *  this file and modify as needed.
 */

#include <xdc/std.h>

#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/ires/iresman.h>


/*
 *  Set USE_RMAN to 1 if the app uses RMAN, otherwise set to 0. If USE_RMAN
 *  is set to 1, the user may need to modify the following:
 *
 *  RMAN_TABLE_SIZE
 *  RMAN_NUMAUTOREG
 *  RMANALLOCFXN
 *  RMANFREEFXN
 *  RMANYIELDFXN
 *  RMANYIELDSAMEPRIORITY
 *  RMAN_autoRegister()
 *
 *  See comments below for description of these elements.
 */
#define USE_RMAN 1


#if USE_RMAN

/*
 * ======== ti.sdo.fc.rman.RMAN configuration ========
 */

/*
 *  User configurable size for table of RMAN registered resources. This must
 *  be greater than or equal to the total number of resources that will be
 *  registered with RMAN. This includes both the statically registered
 *  resources that will be registered with RMAN_autoRegister() (function
 *  defined below), and dynamically registered resources. Most likely, this
 *  will not need to be modified.
 */
#define RMAN_TABLE_SIZE 10

/*
 *  Number of auto-registered resources. Set this to the number of resources
 *  that will be auto-registered in the RMAN_autoRegister() function below.
 */
#define RMAN_NUMAUTOREG 2

/*
 *  Declarations of user-supplied RMAN.persistentAllocFxn and
 *  persistentFreeFxn.
 */
extern Bool _ALG_allocMemory(IALG_MemRec *memTab, Int numRecs);
extern Void _ALG_freeMemory(IALG_MemRec *memTab, Int numRecs);

/*
 *  These defines will be used to fill in the RMAN_PARAMS structure. Change
 *  from the following default values, if needed.
 */
#define RMANALLOCFXN  _ALG_allocMemory
#define RMANFREEFXN _ALG_freeMemory
#define RMANYIELDFXN NULL
#define RMANYIELDSAMEPRIORITY FALSE

/*
 *  RMAN internal tables and data. (Do not modify these).
 */ 
__FAR__ IRESMAN_Fxns * RMAN_TABLE[RMAN_TABLE_SIZE + 1];
__FAR__ short RMAN_FREE_ENTRIES[RMAN_TABLE_SIZE + 1];
__FAR__ short RMAN_numRegistryEntries  = RMAN_NUMAUTOREG;
__FAR__ IRESMAN_Fxns ** RMAN_registryEntries = NULL;
__FAR__ IRESMAN_Params ** RMAN_registryResmanArgs = NULL;

/*
 *   ========== RMAN_PARAMS ===========
 *   Module configuration for RMAN implementation. (Do not modify)
 */
RMAN_Params RMAN_PARAMS = {
    RMAN_TABLE_SIZE + 1,     /* size of the registry table */
    RMANALLOCFXN,            /* persistentAllocFxn */
    RMANFREEFXN,             /* persistentFreeFxn */
    RMANYIELDFXN,            /* yieldFxn */
    RMANYIELDSAMEPRIORITY,   /* yield to same priority? */
};

/*
 *  Tables for auto-registered resources. (Do not modify)
 */
static __FAR__ IRESMAN_Fxns * _entries[RMAN_NUMAUTOREG + 1];
static __FAR__ IRESMAN_Params * _params[RMAN_NUMAUTOREG + 1];


/*
 * ======== ti.sdo.fc.ires.grouputils.GROUPUTILS Configuration ========
 */

#include <ti/sdo/fc/ires/grouputils/ires_grouputils.h>

/* Base key value for  GROUPUTILS Linux IPC objects */
UInt32 _GROUPUTILS_ipcKeyBase = 0x534c4954;

extern Void Algorithm_acquireLock(Int groupId, IALG_Handle alg);
extern Void Algorithm_releaseLock(Int groupId, IALG_Handle alg);

ti_sdo_fc_ires_grouputils_LockFxn ti_sdo_fc_ires_grouputils_lockGroup = 
        (ti_sdo_fc_ires_grouputils_LockFxn)(Algorithm_acquireLock);
ti_sdo_fc_ires_grouputils_LockFxn ti_sdo_fc_ires_grouputils_unlockGroup = 
        (ti_sdo_fc_ires_grouputils_LockFxn)(Algorithm_releaseLock);

typedef struct SemMP_Obj *_GROUPUTILS_SemHandle;
 
extern _GROUPUTILS_SemHandle SemMP_create(Int key, Int count);
extern Void SemMP_delete(_GROUPUTILS_SemHandle sem);
extern Int SemMP_pend(_GROUPUTILS_SemHandle sem, UInt32 count);
extern Void SemMP_post(_GROUPUTILS_SemHandle sem);

__FAR__ ti_sdo_fc_ires_grouputils_GROUPUTILS_SemCreateFxn 
        ti_sdo_fc_ires_grouputils_GROUPUTILS_semCreateFxn = 
        (ti_sdo_fc_ires_grouputils_GROUPUTILS_SemCreateFxn)SemMP_create;
__FAR__ ti_sdo_fc_ires_grouputils_GROUPUTILS_SemDeleteFxn 
        ti_sdo_fc_ires_grouputils_GROUPUTILS_semDeleteFxn = 
        (ti_sdo_fc_ires_grouputils_GROUPUTILS_SemDeleteFxn)SemMP_delete;
__FAR__ ti_sdo_fc_ires_grouputils_GROUPUTILS_SemPendFxn  
        ti_sdo_fc_ires_grouputils_GROUPUTILS_semPendFxn = 
        (ti_sdo_fc_ires_grouputils_GROUPUTILS_SemPendFxn)SemMP_pend;
__FAR__ ti_sdo_fc_ires_grouputils_GROUPUTILS_SemPostFxn 
        ti_sdo_fc_ires_grouputils_GROUPUTILS_semPostFxn = 
        (ti_sdo_fc_ires_grouputils_GROUPUTILS_SemPostFxn)SemMP_post;


/* Extern declarations for IRES resources */
#include <ti/sdo/fc/ires/bufres/bufres.h>

extern IRESMAN_Fxns * GROUPUTILS_getIresmanFxns();
extern IRESMAN_Params * GROUPUTILS_getDefaultParams();

extern IRESMAN_Fxns * BUFRES_getIresmanFxns();
extern IRESMAN_Params * BUFRES_getDefaultParams();

/* Buffer for BUFRES resource */
#define BUFLEN 0x400
Char buffer[BUFLEN];

/*
 *  ======== RMAN_autoRegister ========
 */
IRES_Status RMAN_autoRegister()
{
    IRES_Status status = IRES_OK;

    /*
     *  Populate the RMAN_registryEntries and args tables, to be able to do 
     *  static registration of these arguments
     */ 

    /*
     *  GROUPUTILS resource. If any IRES resource is used that supports
     *  late-acquire of its resources, GROUPUTILS must be included.
     *
     *  TODO: GROUPUTILS documentation needs to be improved.
     */
    _entries[0] = GROUPUTILS_getIresmanFxns(); 
    _params[0] = GROUPUTILS_getDefaultParams(); 

    _params[0]->allocFxn = RMAN_PARAMS.allocFxn;
    _params[0]->freeFxn = RMAN_PARAMS.freeFxn;

    /*
     *  BUFRES resource
     */
    _entries[1] = BUFRES_getIresmanFxns();
    _params[1] = BUFRES_getDefaultParams(); 

    _params[1]->allocFxn = RMAN_PARAMS.allocFxn;
    _params[1]->freeFxn = RMAN_PARAMS.freeFxn;

    /* BUFRES needs a few more config params than just the default */
    ((BUFRES_Params *)_params[1])->base = buffer;
    ((BUFRES_Params *)_params[1])->length = BUFLEN;

    RMAN_registryEntries = (IRESMAN_Fxns **)(&_entries);
    RMAN_registryResmanArgs = (IRESMAN_Params **)(&_params);

    return (status);
}

#else

/* PLEASE DO NOT MODIFY CODE BELOW */

/* If not using RMAN, the RMAN functions need to be stubbed out. */

#include <ti/xdais/ires.h>   /* for IRES types */

IRES_Status RMAN_activateAllResources(IALG_Handle algHandle,
        IRES_Fxns *resFxns, Int scratchId)
{
    return (IRES_OK);
}

IRES_Status RMAN_assignResources(IALG_Handle algHandle, IRES_Fxns *resFxns, 
        Int scratchGroupId)
{
    return (IRES_OK);
}

IRES_Status RMAN_deactivateAllResources(IALG_Handle algHandle, 
        IRES_Fxns * resFxns, Int scratchId)
{
    return (IRES_OK);
}

IRES_Status RMAN_freeResources(IALG_Handle algHandle, IRES_Fxns * resFxns, 
        Int scratchGroupId)
{
    return (IRES_OK);
}

IRES_Status RMAN_init(void)
{
    return (IRES_OK);
}

IRES_Status RMAN_exit(void)
{
    return (IRES_OK);
}

#endif
/*
 *  @(#) ti.sdo.ce.examples.apps.audio1_ires; 1,0,0,222; 12-2-2010 21:19:31; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

