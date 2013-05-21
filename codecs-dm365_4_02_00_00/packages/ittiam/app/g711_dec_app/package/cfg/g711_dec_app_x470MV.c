/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-t50
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
xdc__META(__ASM__, "@(#)__ASM__ = /home/ITTIAM/100200/audio_speech/release_process/release_out/g711_dec_2_0_00_production_dm365_mvl/packages-production/ittiam/app/g711_dec_app/package/cfg/g711_dec_app_x470MV");

/*
 *  ======== __ISA__ ========
 *  Define the ISA of this executable.  This symbol is used by platform
 *  specific "exec" commands that support more than one ISA; e.g., gdb
 */
xdc__META(__ISA__, "@(#)__ISA__ = v5T");

/*
 *  ======== __PLAT__ ========
 *  Define the name of the platform that can run this executable.  This
 *  symbol is used by platform independent "exec" commands
 */
xdc__META(__PLAT__, "@(#)__PLAT__ = ti.platforms.evmDM365");

/*
 *  ======== __TARG__ ========
 *  Define the name of the target used to build this executable.
 */
xdc__META(__TARG__, "@(#)__TARG__ = gnu.targets.MVArm9");


/*
 * ======== ti.sdo.ce.ipc.Settings TEMPLATE ========
 */


/*
 * ======== ti.sdo.ce.osal.Global TEMPLATE ========
 */



/*
 *  ======== Global Configuration ========
 *  Do not modify the following; it is automatically generated from the template
 *  Server.xdt in the ti.sdo.ce package and will be overwritten next time the
 *  executable is configured
 */
#include <ti/sdo/ce/osal/Log.h>

Log_Handle ti_sdo_ce_dvtLog = NULL; 

Bool Memory_skipVirtualAddressTranslation = FALSE;


/* List of all packages and their versions and paths, for diagnostics */
String Global_buildInfo[] = {
    "    package gnu.targets.rts470MV (/home/dm365/dvsdk_2_10_01_18/xdctools_3_15_01_59/packages/gnu/targets/rts470MV/) [1, 0, 0, 0]",
    "    package ti.xdais (/home/dm365/dvsdk_2_10_01_18/xdais_6_24/packages/ti/xdais/) [1, 2.0, 1]",
    "    package ti.sdo.fc.ires (/home/dm365/dvsdk_2_10_01_18/framework_components_2_24/packages/ti/sdo/fc/ires/) [1, 0, 0]",
    "    package ti.sdo.fc.global (/home/dm365/dvsdk_2_10_01_18/framework_components_2_24/packages/ti/sdo/fc/global/) [1, 0, 0]",
    "    package ti.sdo.fc.ires.nullresource (/home/dm365/dvsdk_2_10_01_18/framework_components_2_24/packages/ti/sdo/fc/ires/nullresource/) [1, 0, 0]",
    "    package ti.sdo.fc.rman (/home/dm365/dvsdk_2_10_01_18/framework_components_2_24/packages/ti/sdo/fc/rman/) [2, 0, 0]",
    "    package ti.sdo.ce.global (/home/dm365/dvsdk_2_10_01_18/codec_engine_2_24/packages/ti/sdo/ce/global/) [1, 0, 0]",
    "    package ti.sdo.utils.trace (/home/dm365/dvsdk_2_10_01_18/framework_components_2_24/packages/ti/sdo/utils/trace/) [1, 0, 0]",
    "    package ti.sdo.linuxutils.cmem (/home/dm365/dvsdk_2_10_01_18/framework_components_2_24/fctools/packages/ti/sdo/linuxutils/cmem/) [2, 2, 0]",
    "    package ti.sdo.fc.memutils (/home/dm365/dvsdk_2_10_01_18/framework_components_2_24/packages/ti/sdo/fc/memutils/) [1, 0, 0]",
    "    package ti.sdo.fc.utils (/home/dm365/dvsdk_2_10_01_18/framework_components_2_24/packages/ti/sdo/fc/utils/) [1, 0, 2]",
    "    package ti.sdo.fc.dman3 (/home/dm365/dvsdk_2_10_01_18/framework_components_2_24/packages/ti/sdo/fc/dman3/) [1, 0, 4]",
    "    package ti.sdo.fc.acpy3 (/home/dm365/dvsdk_2_10_01_18/framework_components_2_24/packages/ti/sdo/fc/acpy3/) [1, 0, 4]",
    "    package ti.sdo.fc.ires.addrspace (/home/dm365/dvsdk_2_10_01_18/framework_components_2_24/packages/ti/sdo/fc/ires/addrspace/) [1, 0, 0]",
    "    package ittiam.codecs.g711_dec (/home/ITTIAM/100200/audio_speech/release_process/release_out/g711_dec_2_0_00_production_dm365_mvl/packages-production/ittiam/codecs/g711_dec/) []",
    "    package ti.xdais.dm (/home/dm365/dvsdk_2_10_01_18/xdais_6_24/packages/ti/xdais/dm/) [1, 0, 5]",
    "    package ti.sdo.ce.node (/home/dm365/dvsdk_2_10_01_18/codec_engine_2_24/packages/ti/sdo/ce/node/) [1, 0, 0]",
    "    package ti.sdo.ce.utils.xdm (/home/dm365/dvsdk_2_10_01_18/codec_engine_2_24/packages/ti/sdo/ce/utils/xdm/) [1, 0, 2]",
    "    package gnu.targets (/home/dm365/dvsdk_2_10_01_18/xdctools_3_15_01_59/packages/gnu/targets/) [1, 0, 1]",
    "    package ti.catalog.arm (/home/dm365/dvsdk_2_10_01_18/xdctools_3_15_01_59/packages/ti/catalog/arm/) [1, 0, 1, 0]",
    "    package ti.catalog (/home/dm365/dvsdk_2_10_01_18/xdctools_3_15_01_59/packages/ti/catalog/) [1, 0, 0]",
    "    package ti.platforms.evmDM365 (/home/dm365/dvsdk_2_10_01_18/xdctools_3_15_01_59/packages/ti/platforms/evmDM365/) [1, 0, 0]",
    "    package ti.sdo.ce.osal (/home/dm365/dvsdk_2_10_01_18/codec_engine_2_24/packages/ti/sdo/ce/osal/) [2, 0, 2]",
    "    package ti.sdo.ce.osal.linux (/home/dm365/dvsdk_2_10_01_18/codec_engine_2_24/packages/ti/sdo/ce/osal/linux/) [2, 0, 1]",
    "    package ti.sdo.ce.ipc (/home/dm365/dvsdk_2_10_01_18/codec_engine_2_24/packages/ti/sdo/ce/ipc/) [2, 0, 1]",
    "    package ti.sdo.ce.alg (/home/dm365/dvsdk_2_10_01_18/codec_engine_2_24/packages/ti/sdo/ce/alg/) [1, 0, 1]",
    "    package ti.sdo.ce.ipc.linux (/home/dm365/dvsdk_2_10_01_18/codec_engine_2_24/packages/ti/sdo/ce/ipc/linux/) [2, 0, 1]",
    "    package ti.sdo.ce (/home/dm365/dvsdk_2_10_01_18/codec_engine_2_24/packages/ti/sdo/ce/) [1, 0, 6]",
    "    package ti.sdo.ce.speech1 (/home/dm365/dvsdk_2_10_01_18/codec_engine_2_24/packages/ti/sdo/ce/speech1/) [1, 0, 1]",
    "    package ittiam.codecs.g711_dec.ce (/home/ITTIAM/100200/audio_speech/release_process/release_out/g711_dec_2_0_00_production_dm365_mvl/packages-production/ittiam/codecs/g711_dec/ce/) []",
    "    package ittiam.app.g711_dec_app (/home/ITTIAM/100200/audio_speech/release_process/release_out/g711_dec_2_0_00_production_dm365_mvl/packages-production/ittiam/app/g711_dec_app/) []",
    NULL
};

/*
 * ======== ti.sdo.ce.Engine TEMPLATE ========
 */

/*
 *  ======== Engine Configuration ========
 *  Do not modify following; it is automatically generated from the template
 *  Engine.xdt in the ti.sdo.ce package and will be overwritten next time the
 *  executable is configured
 */
#include <ti/sdo/ce/Engine.h>
#include <ti/xdais/ialg.h>

#include <ti/xdais/idma3.h>

#include <ti/xdais/ires.h>

/* type tables for algorithms */
extern IALG_Fxns G711DECODER_ITTIAM_IG711DECODER;
static String typeTab_G711DECODER_ITTIAM_IG711DECODER[] = {
    "ti.sdo.ce.speech1.ISPHDEC1",
    NULL
};


/* tables of engine algorithms */
extern IALG_Fxns G711DECODER_ITTIAM_IG711DECODER;
extern IRES_Fxns AUDCDC_ITTIAM_IRES;

/* algorithm-specific stub/skeleton config data objects */

static Engine_AlgDesc engineAlgs0[] = {
    {
        "g711_dec",       /* name */
        {1538374278U},   /* uuid */
        &G711DECODER_ITTIAM_IG711DECODER,             /* fxns */
        NULL,        /* idma3Fxns */
        typeTab_G711DECODER_ITTIAM_IG711DECODER,              /* typeTab */
        TRUE,          /* isLocal */
        0,        /* groupId */
        0,      /* protocol */
        &AUDCDC_ITTIAM_IRES,         /* iresFxns */
        NULL                /* stub/skel config params  */
    },
    {NULL},
};
static Engine_AlgDesc engineAlgs1[] = {
    {NULL},
};

/* table of all engines available in this application */
static Engine_Desc engineTab[] = {
    {"g711_dec_engine",      /* engine name */
      engineAlgs0,    /* alg table */
      NULL,         /* (optional) server name */
      NULL,        /* (optional) Link config ID */
      1 /* number of algs in alg table */
    },
    {"local",      /* engine name */
      engineAlgs1,    /* alg table */
      NULL,         /* (optional) server name */
      NULL,        /* (optional) Link config ID */
      0 /* number of algs in alg table */
    },
    {NULL, NULL, NULL, 0}       /* NULL-terminate the engine table */
};

Engine_Config Engine_config = {
    engineTab,              /* table of all engines */
    "local"   /* local RMS engine name */
};

/*
 * ======== ti.sdo.ce.CERuntime TEMPLATE ========
 */


#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Sem.h>
#include <ti/sdo/ce/osal/SemMP.h>
#include <ti/sdo/ce/osal/Thread.h>
#include <ti/sdo/ce/ipc/Processor.h>
#include <ti/sdo/ce/alg/Algorithm.h>
#include <ti/sdo/ce/osal/Lock.h>
#include <ti/sdo/ce/osal/LockMP.h>
#include <ti/sdo/ce/Server.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/rms.h>
#include <ti/sdo/ce/utils/xdm/XdmUtils.h>

#include <ti/sdo/utils/trace/gt.h>

/* This symbol is referenced by Server_init() */
Int Global_useLinkArbiter = FALSE;

/*
 *  ======== CERuntime_init ========
 */
Void CERuntime_init(Void)
{

    GT_init();


    /* if CE_DEBUG is set, turn on tracing and DSP auto trace collection */
    if (Global_getenv("CE_DEBUG") != NULL) {
        extern Bool   Engine_alwaysCollectDspTrace;
        extern String Engine_ceDebugDspTraceMask;

        Engine_alwaysCollectDspTrace = TRUE;



        if (Global_getenv("CE_DEBUG")[0] == '1') {
            GT_set("*+67,CE-3,GT_time=0,GT_prefix=1235");
            Engine_ceDebugDspTraceMask = "*+67,GT_prefix=1235,GT_time=3";
        }
        else if (Global_getenv("CE_DEBUG")[0] == '2') {
            GT_set(
                "*+01234567,CE-3,ti.sdo.ce.osal.SemMP=67,OG=467,OM=4567,OC=67,GT_time=0,GT_prefix=1235");
            Engine_ceDebugDspTraceMask =
                "*+01234567,CR=67,ti.sdo.fc.dman3-2,ti.sdo.fc.dskt2-2,GT_prefix=1235,GT_time=3";
        } else {
            GT_set("*+01234567,CE-3,GT_time=0,GT_prefix=12345");
            Engine_ceDebugDspTraceMask = "*+01234567,GT_prefix=12345,GT_time=3";
        }
    }
    
    if (Global_getenv("CE_CHECK") != NULL) {
        extern Bool VISA_checked;
        
        /*
         * Currently just change _this_ processor's value... perhaps we should
         * enable remote processors as well?
         */
        if (Global_getenv("CE_CHECK")[0] == '1') {
            VISA_checked = TRUE;
        } else if (Global_getenv("CE_CHECK")[0] == '0') {
            VISA_checked = FALSE;
        } else {
            /* leave it whatever it was... maybe we should drop a warning? */
        }
    }

    /* allow user to over-ride via CE_TRACE. */
    GT_set(Global_getenv("CE_TRACE"));
//% print("CERuntime.xdt: Engine.hasServer() = " + Engine.hasServer() +
//%       " Server.$used = " + Server.$used);
    Global_init();

    Sem_init();
    SemMP_init();


    Memory_init();
    Comm_init();
    Thread_init();
    Processor_init();
    LockMP_init();  /* Must be called before DMAN3_init() */
    Algorithm_init();
    XdmUtils_init();
    Lock_init();

    Engine_init();
    Server_init();

}

/*
 *  ======== CERuntime_exit ========
 */
Void CERuntime_exit(Void)
{
    Global_exit();
}

/* for backward compatibility with xdc-m based tools */
Void ti_sdo_ce_CERuntime_init__F(Void) {
    CERuntime_init();
}

/*
 * ======== ti.sdo.ce.Settings TEMPLATE ========
 */

/*
 *  ======== ti.sdo.ce Settings Configuration ========
 *  Do not modify following; it is automatically generated from the template
 *  Settings.xdt in the ti.sdo.ce package and will be overwritten next time the
 *  executable is configured
 */
Bool VISA_checked = FALSE;

/*
 * ======== ti.sdo.ce.alg.Settings TEMPLATE ========
 */

unsigned int ti_sdo_ce_osal_alg_ALG_useHeap = FALSE;
unsigned int ti_sdo_ce_osal_alg_ALG_useCache = TRUE;

UInt32 ti_sdo_ce_alg_ipcKey = 0x4f474c41;

int _ALG_groupUsed[20] = {
     1,
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
};

// No IDMA3 using algs in the system, and DMAN3 is not configured into the
// system.  Stub out these fxn calls.
Void DMAN3_CE_init()
{
}
Void DMAN3_CE_exit()
{
}

int DMAN3_grantDmaChannels(int groupId, void *algHandles, void *dmaFxns,
        int numAlgs)
{
    /* TODO:M  Should assert(false) here.  Should never be called */
    return (0);
}

int DMAN3_releaseDmaChannels(void *algHandles, void * dmaFxns, int numAlgs)
{
    /* TODO:M  Should assert(false) here.  Should never be called */
    return (0);
}


/*
 * ======== ti.sdo.fc.rman.RMAN TEMPLATE ========
 */

/* C code contribution from ti/sdo/fc/rman/RMAN.xdt */
 
#include <ti/sdo/fc/rman/rman.h>


        /* declaration of user-supplied RMAN.persistentAllocFxn */
        extern Bool _ALG_allocMemory(IALG_MemRec *memTab, Int numRecs);
        extern Void _ALG_freeMemory(IALG_MemRec *memTab, Int numRecs);





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

extern IRESMAN_Fxns * ADDRSPACE_getIresmanFxns();
extern IRESMAN_Params * ADDRSPACE_getDefaultParams();


static __FAR__ IRESMAN_Fxns * _entries[1 + 1];
static __FAR__ IRESMAN_Params * _params[1 + 1];

IRES_Status RMAN_autoRegister()
{
    /* Populate the RMAN_registryEntries etc tables, to be able to do 
       static registration of these arguments */ 
    IRES_Status status = IRES_OK;
    
    RMAN_numRegistryEntries = 1;


    _entries[0] = ADDRSPACE_getIresmanFxns(); 
    _params[0] = ADDRSPACE_getDefaultParams(); 

    _params[0]->allocFxn = RMAN_PARAMS.allocFxn;
    _params[0]->freeFxn = RMAN_PARAMS.freeFxn;


    RMAN_registryEntries = (IRESMAN_Fxns **)(&_entries);
    RMAN_registryResmanArgs = (IRESMAN_Params **)(&_params);

    return (status);
}

/*
 * ======== ti.sdo.fc.global.Settings TEMPLATE ========
 */

Bool ti_sdo_fc_multiProcess = TRUE;

/*
 * ======== ti.sdo.utils.trace.GT TEMPLATE ========
 */




/*
 * C code contribution from ti/sdo/utils/GT.xdt 
 */
#include <xdc/std.h>
#include <ti/sdo/utils/trace/gt.h>

extern Void GTConfig_tracePrintf(String fmt, ...); 
extern Ptr GTConfig_libcMalloc(Int size);
 
extern Int GTConfig_threadId(void);
extern void GTConfig_error(String fmt, ...);
extern void GTConfig_libcFree(Ptr, Int);
extern UInt32 GTConfig_gettimeofday(void);
extern Int GTConfig_pthreadLock(void);
extern Int GTConfig_pthreadUnlock(void);
extern Int GTConfig_posixInit(void);

GT_Config _ti_sdo_utils_trace_GT_params = {
    GTConfig_tracePrintf,
    NULL,
    GTConfig_threadId,
    GTConfig_error,
    GTConfig_libcMalloc,
    GTConfig_libcFree,
    GTConfig_gettimeofday,
    GTConfig_pthreadLock,
    GTConfig_pthreadUnlock,
    GTConfig_posixInit    
};

GT_Config *GT = &_ti_sdo_utils_trace_GT_params;

/*
 * ======== ti.sdo.fc.ires.addrspace.ADDRSPACE TEMPLATE ========
 */

    
Bool ADDRSPACE_noTranslation = FALSE;

/*
 * ======== ti.sdo.ce.ipc.linux.Ipc TEMPLATE ========
 */



Void IPC_generatedInit()
{
}

/*
 * ======== ti.sdo.ce.osal.linux.Settings TEMPLATE ========
 */

UInt32 ti_sdo_ce_osal_linux_SemMP_ipcKey = 0x4c41534f;

UInt32 Memory_maxCbListSize = 100;


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

