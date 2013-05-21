/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-u17
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef xdc_runtime_Rta__include
#define xdc_runtime_Rta__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_Rta__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_Rta___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/package/package.defs.h>

#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Command */
enum  {
    xdc_runtime_Rta_Command_READ_MASK = 0,
    xdc_runtime_Rta_Command_WRITE_MASK = 1,
    xdc_runtime_Rta_Command_LOGGER_OFF = 2,
    xdc_runtime_Rta_Command_LOGGER_ON = 3,
    xdc_runtime_Rta_Command_GET_CPU_SPEED = 4,
    xdc_runtime_Rta_Command_RESET_LOGGER = 5,
    xdc_runtime_Rta_Command_CHANGE_PERIOD = 6
};
typedef xdc_Int xdc_runtime_Rta_Command;

/* CommandPacket */
struct xdc_runtime_Rta_CommandPacket {
    xdc_runtime_Rta_Command cmdId;
    xdc_UArg arg0;
    xdc_UArg arg1;
};

/* ResponsePacket */
struct xdc_runtime_Rta_ResponsePacket {
    xdc_runtime_Rta_Command cmdId;
    xdc_UArg resp0;
    xdc_UArg resp1;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Rta_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_runtime_Rta_Module__diagsEnabled xdc_runtime_Rta_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Rta_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_runtime_Rta_Module__diagsIncluded xdc_runtime_Rta_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Rta_Module__diagsMask;
__extern __FAR__ const CT__xdc_runtime_Rta_Module__diagsMask xdc_runtime_Rta_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Rta_Module__gateObj;
__extern __FAR__ const CT__xdc_runtime_Rta_Module__gateObj xdc_runtime_Rta_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Rta_Module__gatePrms;
__extern __FAR__ const CT__xdc_runtime_Rta_Module__gatePrms xdc_runtime_Rta_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Rta_Module__id;
__extern __FAR__ const CT__xdc_runtime_Rta_Module__id xdc_runtime_Rta_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Rta_Module__loggerDefined;
__extern __FAR__ const CT__xdc_runtime_Rta_Module__loggerDefined xdc_runtime_Rta_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Rta_Module__loggerObj;
__extern __FAR__ const CT__xdc_runtime_Rta_Module__loggerObj xdc_runtime_Rta_Module__loggerObj__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Rta_Module__loggerFxn4;
__extern __FAR__ const CT__xdc_runtime_Rta_Module__loggerFxn4 xdc_runtime_Rta_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Rta_Module__loggerFxn8;
__extern __FAR__ const CT__xdc_runtime_Rta_Module__loggerFxn8 xdc_runtime_Rta_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Rta_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__xdc_runtime_Rta_Module__startupDoneFxn xdc_runtime_Rta_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Rta_Object__count;
__extern __FAR__ const CT__xdc_runtime_Rta_Object__count xdc_runtime_Rta_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Rta_Object__heap;
__extern __FAR__ const CT__xdc_runtime_Rta_Object__heap xdc_runtime_Rta_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Rta_Object__sizeof;
__extern __FAR__ const CT__xdc_runtime_Rta_Object__sizeof xdc_runtime_Rta_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Rta_Object__table;
__extern __FAR__ const CT__xdc_runtime_Rta_Object__table xdc_runtime_Rta_Object__table__C;

/* LD_cmdRcvd */
#define xdc_runtime_Rta_LD_cmdRcvd (xdc_runtime_Rta_LD_cmdRcvd__C)
typedef xdc_runtime_Log_Event CT__xdc_runtime_Rta_LD_cmdRcvd;
__extern __FAR__ const CT__xdc_runtime_Rta_LD_cmdRcvd xdc_runtime_Rta_LD_cmdRcvd__C;

/* LD_writeMask */
#define xdc_runtime_Rta_LD_writeMask (xdc_runtime_Rta_LD_writeMask__C)
typedef xdc_runtime_Log_Event CT__xdc_runtime_Rta_LD_writeMask;
__extern __FAR__ const CT__xdc_runtime_Rta_LD_writeMask xdc_runtime_Rta_LD_writeMask__C;

/* A_invalidLogger */
#define xdc_runtime_Rta_A_invalidLogger (xdc_runtime_Rta_A_invalidLogger__C)
typedef xdc_runtime_Assert_Id CT__xdc_runtime_Rta_A_invalidLogger;
__extern __FAR__ const CT__xdc_runtime_Rta_A_invalidLogger xdc_runtime_Rta_A_invalidLogger__C;

/* E_badCommand */
#define xdc_runtime_Rta_E_badCommand (xdc_runtime_Rta_E_badCommand__C)
typedef xdc_runtime_Error_Id CT__xdc_runtime_Rta_E_badCommand;
__extern __FAR__ const CT__xdc_runtime_Rta_E_badCommand xdc_runtime_Rta_E_badCommand__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdc_runtime_Rta_Module_startup( state ) -1

/* Handle__label__S */
xdc__CODESECT(xdc_runtime_Rta_Handle__label__S, "xdc_runtime_Rta_Handle__label")
__extern xdc_runtime_Types_Label* xdc_runtime_Rta_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */
xdc__CODESECT(xdc_runtime_Rta_Module__startupDone__S, "xdc_runtime_Rta_Module__startupDone")
__extern xdc_Bool xdc_runtime_Rta_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(xdc_runtime_Rta_Object__create__S, "xdc_runtime_Rta_Object__create")
__extern xdc_Ptr xdc_runtime_Rta_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */
xdc__CODESECT(xdc_runtime_Rta_Object__delete__S, "xdc_runtime_Rta_Object__delete")
__extern xdc_Void xdc_runtime_Rta_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */
xdc__CODESECT(xdc_runtime_Rta_Object__destruct__S, "xdc_runtime_Rta_Object__destruct")
__extern xdc_Void xdc_runtime_Rta_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(xdc_runtime_Rta_Object__get__S, "xdc_runtime_Rta_Object__get")
__extern xdc_Ptr xdc_runtime_Rta_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(xdc_runtime_Rta_Object__first__S, "xdc_runtime_Rta_Object__first")
__extern xdc_Ptr xdc_runtime_Rta_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(xdc_runtime_Rta_Object__next__S, "xdc_runtime_Rta_Object__next")
__extern xdc_Ptr xdc_runtime_Rta_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(xdc_runtime_Rta_Params__init__S, "xdc_runtime_Rta_Params__init")
__extern xdc_Void xdc_runtime_Rta_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(xdc_runtime_Rta_Proxy__abstract__S, "xdc_runtime_Rta_Proxy__abstract")
__extern xdc_Bool xdc_runtime_Rta_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(xdc_runtime_Rta_Proxy__delegate__S, "xdc_runtime_Rta_Proxy__delegate")
__extern xdc_Ptr xdc_runtime_Rta_Proxy__delegate__S( void );

/* processCommand__E */
#define xdc_runtime_Rta_processCommand xdc_runtime_Rta_processCommand__E
xdc__CODESECT(xdc_runtime_Rta_processCommand__E, "xdc_runtime_Rta_processCommand")
__extern xdc_Void xdc_runtime_Rta_processCommand__E( xdc_runtime_Rta_CommandPacket* cmd, xdc_runtime_Rta_ResponsePacket* resp );
xdc__CODESECT(xdc_runtime_Rta_processCommand__F, "xdc_runtime_Rta_processCommand")
__extern xdc_Void xdc_runtime_Rta_processCommand__F( xdc_runtime_Rta_CommandPacket* cmd, xdc_runtime_Rta_ResponsePacket* resp );
__extern xdc_Void xdc_runtime_Rta_processCommand__R( xdc_runtime_Rta_CommandPacket* cmd, xdc_runtime_Rta_ResponsePacket* resp );

/* acknowledgeCmd__E */
#define xdc_runtime_Rta_acknowledgeCmd xdc_runtime_Rta_acknowledgeCmd__E
xdc__CODESECT(xdc_runtime_Rta_acknowledgeCmd__E, "xdc_runtime_Rta_acknowledgeCmd")
__extern xdc_Void xdc_runtime_Rta_acknowledgeCmd__E( xdc_runtime_Rta_ResponsePacket* resp );
xdc__CODESECT(xdc_runtime_Rta_acknowledgeCmd__F, "xdc_runtime_Rta_acknowledgeCmd")
__extern xdc_Void xdc_runtime_Rta_acknowledgeCmd__F( xdc_runtime_Rta_ResponsePacket* resp );
__extern xdc_Void xdc_runtime_Rta_acknowledgeCmd__R( xdc_runtime_Rta_ResponsePacket* resp );

/* readMask__E */
#define xdc_runtime_Rta_readMask xdc_runtime_Rta_readMask__E
xdc__CODESECT(xdc_runtime_Rta_readMask__E, "xdc_runtime_Rta_readMask")
__extern xdc_Void xdc_runtime_Rta_readMask__E( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg addr );
xdc__CODESECT(xdc_runtime_Rta_readMask__F, "xdc_runtime_Rta_readMask")
__extern xdc_Void xdc_runtime_Rta_readMask__F( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg addr );
__extern xdc_Void xdc_runtime_Rta_readMask__R( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg addr );

/* writeMask__E */
#define xdc_runtime_Rta_writeMask xdc_runtime_Rta_writeMask__E
xdc__CODESECT(xdc_runtime_Rta_writeMask__E, "xdc_runtime_Rta_writeMask")
__extern xdc_Void xdc_runtime_Rta_writeMask__E( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg addr, xdc_UArg val );
xdc__CODESECT(xdc_runtime_Rta_writeMask__F, "xdc_runtime_Rta_writeMask")
__extern xdc_Void xdc_runtime_Rta_writeMask__F( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg addr, xdc_UArg val );
__extern xdc_Void xdc_runtime_Rta_writeMask__R( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg addr, xdc_UArg val );

/* enableLog__E */
#define xdc_runtime_Rta_enableLog xdc_runtime_Rta_enableLog__E
xdc__CODESECT(xdc_runtime_Rta_enableLog__E, "xdc_runtime_Rta_enableLog")
__extern xdc_Void xdc_runtime_Rta_enableLog__E( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg log );
xdc__CODESECT(xdc_runtime_Rta_enableLog__F, "xdc_runtime_Rta_enableLog")
__extern xdc_Void xdc_runtime_Rta_enableLog__F( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg log );
__extern xdc_Void xdc_runtime_Rta_enableLog__R( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg log );

/* disableLog__E */
#define xdc_runtime_Rta_disableLog xdc_runtime_Rta_disableLog__E
xdc__CODESECT(xdc_runtime_Rta_disableLog__E, "xdc_runtime_Rta_disableLog")
__extern xdc_Void xdc_runtime_Rta_disableLog__E( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg log );
xdc__CODESECT(xdc_runtime_Rta_disableLog__F, "xdc_runtime_Rta_disableLog")
__extern xdc_Void xdc_runtime_Rta_disableLog__F( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg log );
__extern xdc_Void xdc_runtime_Rta_disableLog__R( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg log );

/* getCpuSpeed__E */
#define xdc_runtime_Rta_getCpuSpeed xdc_runtime_Rta_getCpuSpeed__E
xdc__CODESECT(xdc_runtime_Rta_getCpuSpeed__E, "xdc_runtime_Rta_getCpuSpeed")
__extern xdc_Void xdc_runtime_Rta_getCpuSpeed__E( xdc_runtime_Rta_ResponsePacket* resp );
xdc__CODESECT(xdc_runtime_Rta_getCpuSpeed__F, "xdc_runtime_Rta_getCpuSpeed")
__extern xdc_Void xdc_runtime_Rta_getCpuSpeed__F( xdc_runtime_Rta_ResponsePacket* resp );
__extern xdc_Void xdc_runtime_Rta_getCpuSpeed__R( xdc_runtime_Rta_ResponsePacket* resp );

/* resetLog__E */
#define xdc_runtime_Rta_resetLog xdc_runtime_Rta_resetLog__E
xdc__CODESECT(xdc_runtime_Rta_resetLog__E, "xdc_runtime_Rta_resetLog")
__extern xdc_Void xdc_runtime_Rta_resetLog__E( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg log );
xdc__CODESECT(xdc_runtime_Rta_resetLog__F, "xdc_runtime_Rta_resetLog")
__extern xdc_Void xdc_runtime_Rta_resetLog__F( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg log );
__extern xdc_Void xdc_runtime_Rta_resetLog__R( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg log );

/* changePeriod__E */
#define xdc_runtime_Rta_changePeriod xdc_runtime_Rta_changePeriod__E
xdc__CODESECT(xdc_runtime_Rta_changePeriod__E, "xdc_runtime_Rta_changePeriod")
__extern xdc_Void xdc_runtime_Rta_changePeriod__E( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg period );
xdc__CODESECT(xdc_runtime_Rta_changePeriod__F, "xdc_runtime_Rta_changePeriod")
__extern xdc_Void xdc_runtime_Rta_changePeriod__F( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg period );
__extern xdc_Void xdc_runtime_Rta_changePeriod__R( xdc_runtime_Rta_ResponsePacket* resp, xdc_UArg period );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdc_runtime_Rta_Module_startupDone() xdc_runtime_Rta_Module__startupDone__S()

/* Object_heap */
#define xdc_runtime_Rta_Object_heap() xdc_runtime_Rta_Object__heap__C

/* Module_heap */
#define xdc_runtime_Rta_Module_heap() xdc_runtime_Rta_Object__heap__C

/* Module_id */
static inline CT__xdc_runtime_Rta_Module__id xdc_runtime_Rta_Module_id( void ) 
{
    return xdc_runtime_Rta_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_Rta_Module_hasMask( void ) 
{
    return xdc_runtime_Rta_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_Rta_Module_getMask( void ) 
{
    return xdc_runtime_Rta_Module__diagsMask__C != NULL ? *xdc_runtime_Rta_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void xdc_runtime_Rta_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_Rta_Module__diagsMask__C != NULL) *xdc_runtime_Rta_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_Rta__top__
#undef __nested__
#endif

#endif /* xdc_runtime_Rta__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdc_runtime_Rta__internalaccess))

#ifndef xdc_runtime_Rta__include_state
#define xdc_runtime_Rta__include_state


#endif /* xdc_runtime_Rta__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_Rta__nolocalnames)

/* module prefix */
#define Rta_Command xdc_runtime_Rta_Command
#define Rta_CommandPacket xdc_runtime_Rta_CommandPacket
#define Rta_ResponsePacket xdc_runtime_Rta_ResponsePacket
#define Rta_Command_READ_MASK xdc_runtime_Rta_Command_READ_MASK
#define Rta_Command_WRITE_MASK xdc_runtime_Rta_Command_WRITE_MASK
#define Rta_Command_LOGGER_OFF xdc_runtime_Rta_Command_LOGGER_OFF
#define Rta_Command_LOGGER_ON xdc_runtime_Rta_Command_LOGGER_ON
#define Rta_Command_GET_CPU_SPEED xdc_runtime_Rta_Command_GET_CPU_SPEED
#define Rta_Command_RESET_LOGGER xdc_runtime_Rta_Command_RESET_LOGGER
#define Rta_Command_CHANGE_PERIOD xdc_runtime_Rta_Command_CHANGE_PERIOD
#define Rta_LD_cmdRcvd xdc_runtime_Rta_LD_cmdRcvd
#define Rta_LD_writeMask xdc_runtime_Rta_LD_writeMask
#define Rta_A_invalidLogger xdc_runtime_Rta_A_invalidLogger
#define Rta_E_badCommand xdc_runtime_Rta_E_badCommand
#define Rta_processCommand xdc_runtime_Rta_processCommand
#define Rta_acknowledgeCmd xdc_runtime_Rta_acknowledgeCmd
#define Rta_readMask xdc_runtime_Rta_readMask
#define Rta_writeMask xdc_runtime_Rta_writeMask
#define Rta_enableLog xdc_runtime_Rta_enableLog
#define Rta_disableLog xdc_runtime_Rta_disableLog
#define Rta_getCpuSpeed xdc_runtime_Rta_getCpuSpeed
#define Rta_resetLog xdc_runtime_Rta_resetLog
#define Rta_changePeriod xdc_runtime_Rta_changePeriod
#define Rta_Module_name xdc_runtime_Rta_Module_name
#define Rta_Module_id xdc_runtime_Rta_Module_id
#define Rta_Module_startup xdc_runtime_Rta_Module_startup
#define Rta_Module_startupDone xdc_runtime_Rta_Module_startupDone
#define Rta_Module_hasMask xdc_runtime_Rta_Module_hasMask
#define Rta_Module_getMask xdc_runtime_Rta_Module_getMask
#define Rta_Module_setMask xdc_runtime_Rta_Module_setMask
#define Rta_Object_heap xdc_runtime_Rta_Object_heap
#define Rta_Module_heap xdc_runtime_Rta_Module_heap

#endif
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

