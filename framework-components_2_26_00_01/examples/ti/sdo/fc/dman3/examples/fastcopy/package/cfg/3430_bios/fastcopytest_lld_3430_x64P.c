/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-u12
 */

#define __nested__
#define __config__

#include <xdc/std.h>

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     MODULE INCLUDES
 *     
 *     <module-name> INTERNALS
 *     <module-name> INHERITS
 *     <module-name> VTABLE
 *     <module-name> PATCH TABLE
 *     <module-name> DECLARATIONS
 *     <module-name> OBJECT OFFSETS
 *     <module-name> TEMPLATES
 *     <module-name> INITIALIZERS
 *     <module-name> FUNCTION STUBS
 *     <module-name> PROXY BODY
 *     <module-name> OBJECT DESCRIPTOR
 *     <module-name> SYSTEM FUNCTIONS
 *     <module-name> PRAGMAS
 *     
 *     INITIALIZATION ENTRY POINT
 *     PROGRAM GLOBALS
 *     CLINK DIRECTIVES
 */


/*
 * ======== MODULE INCLUDES ========
 */



/*
 * ======== xdc.cfg.Program TEMPLATE ========
 */

/*
 *  ======== __ASM__ ========
 *  Define absolute path to program's assembly directory
 */
xdc__META(__ASM__, "@(#)__ASM__ = /db/atree/library/trees/fc/fc-p01x/src/ti/sdo/fc/dman3/examples/fastcopy/package/cfg/3430_bios/fastcopytest_lld_3430_x64P");

/*
 *  ======== __ISA__ ========
 *  Define the ISA of this executable.  This symbol is used by platform
 *  specific "exec" commands that support more than one ISA; e.g., gdb
 */
xdc__META(__ISA__, "@(#)__ISA__ = 64P");

/*
 *  ======== __PLAT__ ========
 *  Define the name of the platform that can run this executable.  This
 *  symbol is used by platform independent "exec" commands
 */
xdc__META(__PLAT__, "@(#)__PLAT__ = ti.platforms.sdp3430");

/*
 *  ======== __TARG__ ========
 *  Define the name of the target used to build this executable.
 */
xdc__META(__TARG__, "@(#)__TARG__ = ti.targets.C64P");

/*
 *  ======== __TRDR__ ========
 *  Define the name of the class that can read/parse this executable.
 */
xdc__META(__TRDR__, "@(#)__TRDR__ = ti.targets.omf.cof.Coff");


/*
 * ======== ti.sdo.fc.utils.gtinfra.GTINFRA TEMPLATE ========
 */


#include <ti/sdo/utils/trace/gt.h>
 

/*
 * ======== ti.sdo.utils.trace.GT TEMPLATE ========
 */




/*
 * C code contribution from ti/sdo/utils/GT.xdt 
 */
#include <xdc/std.h>
#include <ti/sdo/utils/trace/gt.h>

extern Void printfCaller(String fmt, ...); 
extern Ptr myMalloc(Int size);
 

GT_Config _ti_sdo_utils_trace_GT_params = {
    printfCaller,
    NULL,
    NULL,
    NULL,
    myMalloc,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL    
};

GT_Config *GT = &_ti_sdo_utils_trace_GT_params;

/*
 * ======== ti.sdo.fc.global.Settings TEMPLATE ========
 */

Bool ti_sdo_fc_multiProcess = TRUE;

/*
 * ======== ti.sdo.fc.dman3.DMAN3 TEMPLATE ========
 */


/* C code contribution from ti/sdo/fc/dman3/DMAN3.xdt */

#include <ti/sdo/fc/dman3/dman3.h>
#include <ti/sdo/fc/acpy3/acpy3.h>

#if 20 > DMAN3_MAXGROUPS
#error DMAN3 internal assertion:  const DMAN3.MAXGROUPS larger than header const
#endif

__FAR__ Bool ti_sdo_fc_dman3_DMAN3_useCustomDma = FALSE;

__FAR__ Uns ti_sdo_fc_dman3_DMAN3_numQdmaGroup[21] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
   0 /* For scratch id -1 */ 
};

__FAR__ Uns DMAN3_QDMA_CHANNELS[4] = {
    0,
    1,
    2,
    3
};

__FAR__ Uns DMAN3_QDMA_QUEUE_MAP[4] = {
    1,
    1,
    1,
    1
};

__FAR__ Uns DMAN3_QUEUE_TC_MAP[8] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7
};

__FAR__ Uns DMAN3_QUEUE_PRIORITIES[8] = {
    3,
    7,
    0,
    0,
    0,
    0,
    0,
    0
};

extern Void  _DMAN3_initInternal();
extern Void  _DMAN3_initImpl(Void);


/* Base key value for DMAN3 IPC objects */

/*
 *  ======== DMAN3_init  ========
 */
Void DMAN3_init(Void)
{
    extern __FAR__ DMAN3_Params DMAN3_PARAMS;

    /* BIOS heap labels */
    extern __FAR__ Int L1DHEAP;
    extern __FAR__ Int EXTERNALHEAP;

    DMAN3_PARAMS.heapInternal = L1DHEAP;
    DMAN3_PARAMS.heapExternal = EXTERNALHEAP;
    _DMAN3_initImpl();
}


/*
 *  ======== DMAN3_CE_init  ========
 *  Supplied to support legacy Codec Engine Frameworks. To be deprecated in the future.
 */
Void DMAN3_CE_init()
{
    DMAN3_init();
    ACPY3_init();
}

/*
 *  ======== DMAN3_CE_exit  ========
 *  Supplied to support legacy Codec Engine Frameworks. To be deprecated in the future.
 */
Void DMAN3_CE_exit()
{
    DMAN3_exit();
    ACPY3_exit();
}

/*
 *  ======== DMAN3_PARAMS ========
 *  Default module configuration structure for DMAN3 implementation.
 *  It is set at design time by the system integrator to adjust the behaviour
 *  of the module to be optimal for its execution environment.
 */
DMAN3_Params DMAN3_PARAMS = {

    /* qdmaPaRamBase: Physical base address for PARAM0 */
    (Uns *)0x1c04000,

    /* The maxPaRamEntries:  Total number of PARAM Table entries on the
     * hardware (eg, for IVA2 this is 128, for Himalaya, this is 256).
     */
    128,

    /*
     * paRamBaseIndex: (0>value>255) represents the first PARAM TABLE ENTRY
     * NUMBER that is assigned by configuration for exclusive DMAN3 allocation.
     */
    96,

    /*
     * numPaRamEntries:  number of PARAM Table entries starting at
     * DMAN3_PARAM_BASE_INDEX assigned by configuration for exclusive DMAN3
     * allocation.
     */
    32,


    /* maxQdmaChannels:  contains the total number of Physical QDMA channels
     * available on the hardware (eg, 8 for DaVinci, 4 for IVA2).
     */
    8,

    /*
     * numQdmaChannels: contains the number of Physical QDMA channels
     * that are assigned to DMAN3 via configuration.
     * qdmaChannels: array containing list of DMAN3_NUM_QDMA_CHANNELS
     * many Physical QDMA channels assigned to DMAN3 via configuration.
     */
    1,

    DMAN3_QDMA_CHANNELS,

    /*
     * tccAllocationMaskH and tccAllocationMaskL:  are 32-bit bitmasks
     * representing configuration provided list of TCCs for exclusive DMAN3
     * allocation.
     *
     * For example, for TCC's in the range 0-31 the Low Mask (tccAllocationMaskL)
     * is configured so that a '1' in bit position 'i' indicates the TCC 'i' is
     * assigned to DMAN3
     */
    0xffffffff,
    0x0,

     /*
      * heapInternal: BIOS Heap ID for dynamic allocation of DMAN3 objects
      * must be allocated in L1D Internal RAM.
      * heapExternal: BIOS Heap ID for dyn allocation of private DMAN3
      * data structures.
      *
      * A value of -1 indicates that the heap is NOT DEFINED.
      */
    -1, //L1DHEAP,
    0,  //EXTERNALHEAP,

    /* numTccGroup[DMAN3_MAXGROUPS] */
    {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
    },

    /* numPaRamGroup[DMAN3_MAXGROUPS] */
    {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
    },

    /* idma3Internal */
    1,

    /* scratchAllocFxn */
    NULL,

    /* scratchFreeFxn */
    NULL,

    /* nullPaRamIndex */
    0,

    /* maxTcs */
    8,

    DMAN3_QDMA_QUEUE_MAP,

    DMAN3_QUEUE_TC_MAP,

    DMAN3_QUEUE_PRIORITIES,

    /* allowUnshared */
    1,
};


/*
 * ======== ti.sdo.fc.acpy3.ACPY3 TEMPLATE ========
 */



/* C code contribution from ti/sdo/fc/acpy3/ACPY3.xdt */

#include <xdc/std.h>

#ifdef xdc_target__isaCompatible_64P

#include <ti/sdo/fc/acpy3/acpy3_qdma.h>
__FAR__ ACPY3_QDMA_Config ACPY3_QDMA; 
__FAR__ volatile ACPY3_QDMA_REG_Str *ACPY3_EDMA3BASE;
#else

#include <ti/sdo/fc/acpy3/acpy3_qdma_arm.h>
ACPY3_QDMA_Config ACPY3_QDMA; 
volatile ACPY3_QDMA_REG_Str *ACPY3_EDMA3BASE;
volatile UInt32 * ACPY3_QDMAPARAMBASE;  
#endif

extern UInt32 * _DMAN3_edma3Addr;
extern UInt32 _DMAN3_nullPaRam;
#ifndef xdc_target__isaCompatible_64P
extern UInt32 * _DMAN3_paRamAddr;
#endif

Void _ACPY3_qdmaInit() 
{
    ACPY3_QDMA.nullPaRamIndex = _DMAN3_nullPaRam; 
    ACPY3_EDMA3BASE = (ACPY3_QDMA_REG_Str *)_DMAN3_edma3Addr;
#ifndef xdc_target__isaCompatible_64P
    ACPY3_QDMAPARAMBASE = (UInt32 *)_DMAN3_paRamAddr;
#endif
}

/*
 * ======== ti.sdo.fc.dskt2.DSKT2 TEMPLATE ========
 */

/* C code contribution from ti/sdo/fc/DSKT2.xdt */

#include <xdc/std.h>
#include <ti/sdo/fc/dskt2/dskt2.h>

extern Void BCACHE_wbInv();

DSKT2_CacheWBInvFxn DSKT2_cacheWBInvFxn = (DSKT2_CacheWBInvFxn)BCACHE_wbInv;

Uns _DSKT2_ALLOW_EXTERNAL_SCRATCH = 1;

#if 20 > DSKT2_NUM_SCRATCH_GROUPS
#error too many values in DARAM_SCRATCH_SIZES array, please fix your .cfg
#endif

#if 20 > DSKT2_NUM_SCRATCH_GROUPS
#error too many values in SARAM_SCRATCH_SIZES array, please fix your .cfg
#endif

Uns _DSKT2_DARAM_SCRATCH_SIZES[ DSKT2_NUM_SCRATCH_GROUPS ] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

Uns _DSKT2_SARAM_SCRATCH_SIZES[ DSKT2_NUM_SCRATCH_GROUPS ] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};


/*
 * ======== ti.sdo.fc.edma3.Settings TEMPLATE ========
 */



/* C code contribution from ti/sdo/fc/edma3/Settings.xdt */

__FAR__ Uns ti_sdo_fc_edma3_EDMA3_physicalId = 0;


#include <xdc/std.h>

/* For BIOS based implementation of OS critical section protect functions */
#include <ti/bios/include/std.h>
#include <ti/bios/include/tsk.h>
#include <ti/bios/include/hwi.h>

#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/edma3/rm/edma3_rm.h>
#include <ti/sdo/fc/edma3/edma3_config.h>





/* Array of maximum scratch paRam requirements of all groups */
Uns EDMA3_paRamScratchSizes[EDMA3_MAXGROUPS] = {
    4,
    3,
    2,
    0,
    0,
    5,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

/* Array of maximum scratch edma channel requirements of all groups */
Uns EDMA3_edmaChanScratchSizes[EDMA3_MAXGROUPS] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

/* Array of maximum scratch qdma channel requirements of all groups */
Uns EDMA3_qdmaChanScratchSizes[EDMA3_MAXGROUPS] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

/* Array of maximum scratch tcc requirements of all groups */
Uns EDMA3_tccScratchSizes[EDMA3_MAXGROUPS] = {
    4,
    3,
    2,
    0,
    0,
    5,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

/*
 * Array of EDMA3 LLD RM configuration structure for all the scratch groups
 */
__FAR__ EDMA3_InstanceInitConfig EDMA3_scratchResourceConfig[EDMA3_MAXGROUPS];

/*
 * Declare semaphore related functions before using them
 */
extern RMAN_SemHandle mySemCreate(Int key, Int count);
extern Void mySemDelete(RMAN_SemHandle sem);
extern Int mySemPend(RMAN_SemHandle sem, UInt32 count);
extern Void mySemPost(RMAN_SemHandle sem);

/*
 * Declare alloc/Free functions before using them
 */
extern Bool DSKT2_allocPersistent(IALG_MemRec *memTab, Int numRecs);
extern Void DSKT2_freePersistent(IALG_MemRec *memTab, Int numRecs);

/*
 *  ======== EDMA3_semCreate ========
 *  Function to create a Semaphore given a key
 */
void * EDMA3_semCreate(Int key, Int count)
{
    /*
     * Call RMAN's configured semCreateFxn, cast the returned semaphore value
     * to the Semaphore type expected by EDMA3 RM.
     */
    return ((void *)mySemCreate(key, count));
}

/*
 *  ======== EDMA3_semDelete ========
 *  Function to delete a given Semaphore
 */
void EDMA3_semDelete(EDMA3_SemHandle hSem)
{
    mySemDelete((RMAN_SemHandle)hSem);
}

/*
 *  ======== edma3OsSemGive ========
 *  Function to Post a semaphore
 *  This function is called internally by the EDMA3 Low level Resource Manager
 */
EDMA3_Result edma3OsSemGive(EDMA3_SemHandle hSem)
{
    EDMA3_Result semGiveResult = EDMA3_SOK;
    if(NULL == hSem) {
        semGiveResult = EDMA3_E_INVALID_PARAM;
    }
    else {
        mySemPost((RMAN_SemHandle)hSem);
    }
    return (semGiveResult);
}

/*
 *  ======== edma3OsSemTake ========
 *  Function to Pend on a semaphore
 *  This function is called internally by the EDMA3 Low level Resource Manager
 */
EDMA3_Result edma3OsSemTake(EDMA3_SemHandle hSem, int mSecTimeout)
{
    EDMA3_Result semTakeResult = EDMA3_SOK;
    unsigned short semPendResult;

    if(NULL == hSem) {
        semTakeResult = EDMA3_E_INVALID_PARAM;
    }
    else {
        semPendResult = mySemPend((RMAN_SemHandle)hSem,
                (UInt32)mSecTimeout);
        if (semPendResult != 0) {
            semTakeResult = EDMA3_E_SEMAPHORE;
        }
    }

    return (semTakeResult);
}

/*
 *  ======== edma3OsProtectEntry ========
 *  OS critical section protect (Entry) function
 */
void edma3OsProtectEntry (unsigned int edma3InstanceId, int level, 
        unsigned int *intState)
{
    /* For now we ignore the instanceId */
/*      (void)edma3InstanceId;*/

    if (((level == EDMA3_OS_PROTECT_INTERRUPT)
        || (level == EDMA3_OS_PROTECT_INTERRUPT_TC_ERROR))
        && (intState == NULL)) {
        return;
    }
    else {
        switch (level) {
            /* Disable all (global) interrupts */
            case EDMA3_OS_PROTECT_INTERRUPT :
                *intState = HWI_disable();
                break;

            /* Disable scheduler */
            case EDMA3_OS_PROTECT_SCHEDULER :
                TSK_disable();
                break;

            /* Disable scheduler */
            case EDMA3_OS_PROTECT_INTERRUPT_XFER_COMPLETION :
                TSK_disable();
                break;

            /* Disable scheduler */
            case EDMA3_OS_PROTECT_INTERRUPT_CC_ERROR :
                TSK_disable();
                break;

            case EDMA3_OS_PROTECT_INTERRUPT_TC_ERROR :
                switch (*intState) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        /* Fall through... */
                        TSK_disable();
                        break;

                     default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}

/*
 *  ======== edma3OsProtectExit ========
 *  OS critical section protect (Exit) function
 */
void edma3OsProtectExit(unsigned int edma3InstanceId, int level, 
        unsigned int intState)
{
/*      (void)edma3InstanceId;*/

    switch (level) {
        /* Enable all (global) interrupts */
        case EDMA3_OS_PROTECT_INTERRUPT :
            HWI_restore(intState);
            break;

        /* Enable scheduler */
        case EDMA3_OS_PROTECT_SCHEDULER :
            break;

        case EDMA3_OS_PROTECT_INTERRUPT_XFER_COMPLETION :
            TSK_enable();
            break;

        case EDMA3_OS_PROTECT_INTERRUPT_CC_ERROR :
            TSK_enable();
            break;

        /* Enable EDMA3 TC error interrupt only */
        case EDMA3_OS_PROTECT_INTERRUPT_TC_ERROR :
            switch (intState)
                {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    /* Fall through... */
                    /* Enable the corresponding interrupt */
                    TSK_enable();
                    break;

                 default:
                    break;
                }

            break;

        default:
            break;
    }
}


/*
 *  ======== EDMA3_PARAMS ========
 *  EDMA3_PARAMS structure is created using the configured values
 */
EDMA3_Params EDMA3_PARAMS = {
   1,
   0,
   DSKT2_allocPersistent,
   DSKT2_freePersistent,
   NULL,
   NULL,
   20,
   1,
};

/*
 *  ======== EDMA3_createResourceManagerObject ========
 *  Creates a resource manager object based on the underlying SOC
 */
EDMA3_Result EDMA3_createResourceManagerObject()
{
    EDMA3_Result status;
    EDMA3_RM_MiscParam param = {NULL , NULL};

    param.isSlave = (EDMA3_PARAMS.globalInit == 1) ? 0 : 1;

    status = EDMA3_RM_create( ti_sdo_fc_edma3_EDMA3_physicalId,
            (EDMA3_RM_GblConfigParams *)(EDMA3_PARAMS.globalConfig), &param);

    return ((EDMA3_Result)status);
}

/*
 *  ======== EDMA3_deleteResourceManagerObject ========
 *  Deletes the resource manager object based on the underlying SOC
 */
EDMA3_Result EDMA3_deleteResourceManagerObject()
{
    EDMA3_Result status;

    status = EDMA3_RM_delete(ti_sdo_fc_edma3_EDMA3_physicalId, 
            (const void *)NULL);

    return (status);
}


/*
 * ======== ti.sdo.edma3.rm.RM TEMPLATE ========
 */





/* Resource Manager Internal Header Files */
#include <ti/sdo/edma3/rm/src/edma3resmgr.h>

/**
 * Maximum Resource Manager Instances supported by the EDMA3 Package.
 * USE THE SAME VALUE FOR BOTH THE #DEFINE AND CONST UNSIGNED INT BELOW.
 */

/**
 * Maximum Resource Manager Instances supported by the EDMA3 Package.
 * This #define is needed for array declarations.
 */
#define MAX_EDMA3_RM_INSTANCES 32

/* This const is required to access this constant in other header files */
const unsigned int EDMA3_MAX_RM_INSTANCES = 32;

EDMA3_RM_InstanceInitConfig userInstInitConfigArray[EDMA3_MAX_EDMA3_INSTANCES][MAX_EDMA3_RM_INSTANCES];
EDMA3_RM_Instance resMgrInstanceArray[EDMA3_MAX_EDMA3_INSTANCES][MAX_EDMA3_RM_INSTANCES];


/* These pointers will be used to refer the above mentioned arrays. */
EDMA3_RM_Instance *resMgrInstance = (EDMA3_RM_Instance *)resMgrInstanceArray;
EDMA3_RM_InstanceInitConfig *userInitConfig = (EDMA3_RM_InstanceInitConfig *)userInstInitConfigArray;

/* Pointer to the above mentioned 2-D arrays, used for address calculation purpose */
EDMA3_RM_Instance *ptrRMIArray = (EDMA3_RM_Instance *)resMgrInstanceArray;
EDMA3_RM_InstanceInitConfig *ptrInitCfgArray = (EDMA3_RM_InstanceInitConfig *)userInstInitConfigArray;





/*
 * ======== PROGRAM GLOBALS ========
 */


/*
 * ======== CLINK DIRECTIVES ========
 */

#ifdef __ti__
#define PRAGMA(x) _Pragma(#x)
#define xdc__clink_constant(var) \
PRAGMA(DATA_SECTION(var, ".const:" #var))  \
asm("   .sect \".const:" #var "\"\n"  \
  "   .clink\n"  \
  "   .sect \"[0].const:" #var "\"\n"  \
  "   .clink\n"  \
  "   .sect \"[1].const:" #var "\"\n"  \
  "   .clink")

#endif

