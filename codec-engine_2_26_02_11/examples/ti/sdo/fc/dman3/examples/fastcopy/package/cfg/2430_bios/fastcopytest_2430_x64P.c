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
xdc__META(__ASM__, "@(#)__ASM__ = /db/atree/library/trees/fc/fc-p01x/src/ti/sdo/fc/dman3/examples/fastcopy/package/cfg/2430_bios/fastcopytest_2430_x64P");

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
xdc__META(__PLAT__, "@(#)__PLAT__ = ti.platforms.sdp2430");

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

__FAR__ Uns DMAN3_QDMA_CHANNELS[8] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7
};

__FAR__ Uns DMAN3_QDMA_QUEUE_MAP[8] = {
    1,
    1,
    1,
    1,
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
    78,

    /*
     * numPaRamEntries:  number of PARAM Table entries starting at
     * DMAN3_PARAM_BASE_INDEX assigned by configuration for exclusive DMAN3
     * allocation.
     */
    48,


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
    8,

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
    },

    /* numPaRamGroup[DMAN3_MAXGROUPS] */
    {
    4,
    4,
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
    },

    /* idma3Internal */
    1,

    /* scratchAllocFxn */
    NULL,

    /* scratchFreeFxn */
    NULL,

    /* nullPaRamIndex */
    127,

    /* maxTcs */
    2,

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

