/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 */

#define __nested__
#define __config__

#include <xdc/std.h>

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     SPECIAL SYMBOLS
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
 * ======== SPECIAL SYMBOLS ========
 */


/*
 * ======== MODULE INCLUDES ========
 */



/*
 * ======== xdc.cfg.Program TEMPLATE ========
 */

/*
 *  ======== __ASM__ ========
 *  Define this program's package-path relative assembly directory
 */
__FAR__ char *__ASM__ = "@(#)__ASM__ = /db/swcoe_asp/DM360/Kaleido/dm360/mpeg4_decoder/Client/Test/Src/mp4vdecTestApp/package/cfg/mp4vdecTestApp_x470MV";

/*
 *  ======== __ISA__ ========
 *  Define the ISA of this executable.  This symbol is used by platform
 *  specific "exec" commands that support more than one ISA; e.g., gdb
 */
__FAR__ char *__ISA__ = "@(#)__ISA__ = v5T";

/*
 *  ======== __PLAT__ ========
 *  Define the name of the platform that can run this executable.  This
 *  symbol is used by platform independent "exec" commands
 */
__FAR__ char *__PLAT__ = "@(#)__PLAT__ = ti.platforms.evmDM365";

/*
 *  ======== __TARG__ ========
 *  Define the name of the target used to build this executable.
 */
__FAR__ char *__TARG__ = "@(#)__TARG__ = gnu.targets.MVArm9";


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
 * ======== ti.sdo.fc.rman.RMAN TEMPLATE ========
 */

/* C code contribution from ti/sdo/fc/rman/RMAN.xdt */
 
#include <ti/sdo/fc/rman/rman.h>


        /* declaration of user-supplied RMAN.persistentAllocFxn */
        extern Bool _ALG_allocMemory(IALG_MemRec *memTab, Int numRecs);
        extern Void _ALG_freeMemory(IALG_MemRec *memTab, Int numRecs);

extern RMAN_SemHandle Sem_create(Int key, Int count);

extern Void Sem_delete(RMAN_SemHandle sem);

extern Int Sem_pend(RMAN_SemHandle sem, UInt32 count);

extern Void Sem_post(RMAN_SemHandle sem);

/* Table of user-configured size to store the registration entries */ 
__FAR__ IRESMAN_Fxns * RMAN_TABLE[11];

/* Table of user-configured size to store the freed entries */ 
__FAR__ short RMAN_FREE_ENTRIES[11];

/*
 * Number of entries statically configured for the Resource Registry table
 */
__FAR__ short RMAN_numRegistryEntries  = 0;
 
/*
 * Static configuration entries for the table
 */
__FAR__ IRESMAN_Fxns ** RMAN_registryEntries = NULL;
 
/*
 * Initialization arguments for the entries to be registered
 */
__FAR__ IRESMAN_Params ** RMAN_registryResmanArgs = NULL;

/*
 *   ========== RMAN_PARAMS ===========
 *   Module configuration for RMAN implementation
 *   It is set at design time by system integrator to adjust the behavior of 
 *   module to be optimal for its execution environment
 */
RMAN_Params RMAN_PARAMS = {
 
    /* size of the registry table */ 
    11,

    /* persistentAllocFxn */
    _ALG_allocMemory,
 
    /* persistentFreeFxn */
    _ALG_freeMemory,
  
    /* yieldFxn */
    NULL,

    /* flag indicating if yield to same priority is allowed */
    FALSE,
};



static __FAR__ IRESMAN_Fxns * _entries[0 + 1];
static __FAR__ IRESMAN_Params * _params[0 + 1];

IRES_Status RMAN_autoRegister()
{
    /* Populate the RMAN_registryEntries etc tables, to be able to do 
       static registration of these arguments */ 
    IRES_Status status = IRES_OK;
    
    RMAN_numRegistryEntries = 0;


    RMAN_registryEntries = (IRESMAN_Fxns **)(&_entries);
    RMAN_registryResmanArgs = (IRESMAN_Params **)(&_params);

    return (status);
}

/*
 * ======== ti.sdo.fc.edma3.Settings TEMPLATE ========
 */



/* C code contribution from ti/sdo/fc/edma3/Settings.xdt */


#include <xdc/std.h>
#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/edma3/edma3_config.h>

/*
 * Declare alloc/Free functions before using them
 */
extern Bool _ALG_allocMemory(IALG_MemRec *memTab, Int numRecs);
extern Void _ALG_freeMemory(IALG_MemRec *memTab, Int numRecs);

/*
 *  ======== EDMA3_PARAMS ========
 *  EDMA3_PARAMS structure is created using the configured values
 */
EDMA3_Params EDMA3_PARAMS = {
   1,
    0,
   _ALG_allocMemory,
   _ALG_freeMemory,
    NULL,
    NULL,
    0,
   1,
};

/* Base key value for DMAN3 Linux IPC objects */
UInt32 _EDMA3_ipcKeyBase = 0x33414d44;


/*
 * ======== ti.sdo.fc.ires.vicp.VICP2 TEMPLATE ========
 */



/* Generated code from ti.sdo.fc.ires.vicp.VICP2.xdt */
unsigned int _VICP2_imcopConfigBase = (unsigned int)30015488;

/* Base key value for VICP2 Linux IPC objects */
UInt32 _VICP2_ipcKeyBase = 0x50434956;

/* Device is TMS320DM365 */
Bool _VICP2_dm355 = 0;
Bool _VICP2_dm365 = 1;

/*
 * ======== ti.sdo.fc.rman.examples.EXAMPLE TEMPLATE ========
 */


/*
 * ======== ti.sdo.fc.utils.SHM TEMPLATE ========
 */

 

/*
 * ======== ti.sdo.fc.utils.SMGRMP TEMPLATE ========
 */

 

/*
 * ======== ti.sdo.fc.vicpsync.VICPSYNC TEMPLATE ========
 */

 

/* Device is TMS320DM365 */
Bool _VICPSYNC_dm355 = 0; 
Bool _VICPSYNC_dm365 = 1; 

/*
 * ======== ti.sdo.fc.ires.edma3chan.EDMA3CHAN TEMPLATE ========
 */

 

/*
 * ======== ti.sdo.fc.ires.addrspace.ADDRSPACE TEMPLATE ========
 */

    
Bool ADDRSPACE_noTranslation = FALSE;

/*
 * ======== ti.sdo.fc.global.Settings TEMPLATE ========
 */

Bool ti_sdo_fc_multiProcess = TRUE;

/*
 * ======== PROGRAM GLOBALS ========
 */


/*
 * ======== CLINK DIRECTIVES ========
 */

