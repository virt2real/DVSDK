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

#ifndef xdc_runtime_Log__include
#define xdc_runtime_Log__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_Log__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_Log___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Log__prologue.h>
#include <xdc/runtime/package/package.defs.h>

#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Text.h>
#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* NUMARGS */
#define xdc_runtime_Log_NUMARGS (8)

/* PRINTFID */
#define xdc_runtime_Log_PRINTFID (0)

/* EventRec */
typedef xdc_IArg __T1_xdc_runtime_Log_EventRec__arg;
typedef xdc_IArg __ARRAY1_xdc_runtime_Log_EventRec__arg[8];
typedef __ARRAY1_xdc_runtime_Log_EventRec__arg __TA_xdc_runtime_Log_EventRec__arg;
struct xdc_runtime_Log_EventRec {
    xdc_runtime_Types_Timestamp64 tstamp;
    xdc_Bits32 serial;
    xdc_runtime_Types_Event evt;
    __TA_xdc_runtime_Log_EventRec__arg arg;
};

/* Event */

/* EventId */
typedef xdc_runtime_Types_RopeId xdc_runtime_Log_EventId;


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Log_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_runtime_Log_Module__diagsEnabled xdc_runtime_Log_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Log_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_runtime_Log_Module__diagsIncluded xdc_runtime_Log_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Log_Module__diagsMask;
__extern __FAR__ const CT__xdc_runtime_Log_Module__diagsMask xdc_runtime_Log_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Log_Module__gateObj;
__extern __FAR__ const CT__xdc_runtime_Log_Module__gateObj xdc_runtime_Log_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Log_Module__gatePrms;
__extern __FAR__ const CT__xdc_runtime_Log_Module__gatePrms xdc_runtime_Log_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Log_Module__id;
__extern __FAR__ const CT__xdc_runtime_Log_Module__id xdc_runtime_Log_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Log_Module__loggerDefined;
__extern __FAR__ const CT__xdc_runtime_Log_Module__loggerDefined xdc_runtime_Log_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Log_Module__loggerObj;
__extern __FAR__ const CT__xdc_runtime_Log_Module__loggerObj xdc_runtime_Log_Module__loggerObj__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Log_Module__loggerFxn4;
__extern __FAR__ const CT__xdc_runtime_Log_Module__loggerFxn4 xdc_runtime_Log_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Log_Module__loggerFxn8;
__extern __FAR__ const CT__xdc_runtime_Log_Module__loggerFxn8 xdc_runtime_Log_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Log_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__xdc_runtime_Log_Module__startupDoneFxn xdc_runtime_Log_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Log_Object__count;
__extern __FAR__ const CT__xdc_runtime_Log_Object__count xdc_runtime_Log_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Log_Object__heap;
__extern __FAR__ const CT__xdc_runtime_Log_Object__heap xdc_runtime_Log_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Log_Object__sizeof;
__extern __FAR__ const CT__xdc_runtime_Log_Object__sizeof xdc_runtime_Log_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Log_Object__table;
__extern __FAR__ const CT__xdc_runtime_Log_Object__table xdc_runtime_Log_Object__table__C;

/* L_construct */
#define xdc_runtime_Log_L_construct (xdc_runtime_Log_L_construct__C)
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_construct;
__extern __FAR__ const CT__xdc_runtime_Log_L_construct xdc_runtime_Log_L_construct__C;

/* L_create */
#define xdc_runtime_Log_L_create (xdc_runtime_Log_L_create__C)
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_create;
__extern __FAR__ const CT__xdc_runtime_Log_L_create xdc_runtime_Log_L_create__C;

/* L_destruct */
#define xdc_runtime_Log_L_destruct (xdc_runtime_Log_L_destruct__C)
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_destruct;
__extern __FAR__ const CT__xdc_runtime_Log_L_destruct xdc_runtime_Log_L_destruct__C;

/* L_delete */
#define xdc_runtime_Log_L_delete (xdc_runtime_Log_L_delete__C)
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_delete;
__extern __FAR__ const CT__xdc_runtime_Log_L_delete xdc_runtime_Log_L_delete__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdc_runtime_Log_Module_startup( state ) -1

/* Handle__label__S */
xdc__CODESECT(xdc_runtime_Log_Handle__label__S, "xdc_runtime_Log_Handle__label")
__extern xdc_runtime_Types_Label* xdc_runtime_Log_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */
xdc__CODESECT(xdc_runtime_Log_Module__startupDone__S, "xdc_runtime_Log_Module__startupDone")
__extern xdc_Bool xdc_runtime_Log_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(xdc_runtime_Log_Object__create__S, "xdc_runtime_Log_Object__create")
__extern xdc_Ptr xdc_runtime_Log_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */
xdc__CODESECT(xdc_runtime_Log_Object__delete__S, "xdc_runtime_Log_Object__delete")
__extern xdc_Void xdc_runtime_Log_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */
xdc__CODESECT(xdc_runtime_Log_Object__destruct__S, "xdc_runtime_Log_Object__destruct")
__extern xdc_Void xdc_runtime_Log_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(xdc_runtime_Log_Object__get__S, "xdc_runtime_Log_Object__get")
__extern xdc_Ptr xdc_runtime_Log_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(xdc_runtime_Log_Object__first__S, "xdc_runtime_Log_Object__first")
__extern xdc_Ptr xdc_runtime_Log_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(xdc_runtime_Log_Object__next__S, "xdc_runtime_Log_Object__next")
__extern xdc_Ptr xdc_runtime_Log_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(xdc_runtime_Log_Params__init__S, "xdc_runtime_Log_Params__init")
__extern xdc_Void xdc_runtime_Log_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(xdc_runtime_Log_Proxy__abstract__S, "xdc_runtime_Log_Proxy__abstract")
__extern xdc_Bool xdc_runtime_Log_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(xdc_runtime_Log_Proxy__delegate__S, "xdc_runtime_Log_Proxy__delegate")
__extern xdc_Ptr xdc_runtime_Log_Proxy__delegate__S( void );

/* doPrint__E */
#define xdc_runtime_Log_doPrint xdc_runtime_Log_doPrint__E
xdc__CODESECT(xdc_runtime_Log_doPrint__E, "xdc_runtime_Log_doPrint")
__extern xdc_Void xdc_runtime_Log_doPrint__E( xdc_runtime_Log_EventRec* evRec );
xdc__CODESECT(xdc_runtime_Log_doPrint__F, "xdc_runtime_Log_doPrint")
__extern xdc_Void xdc_runtime_Log_doPrint__F( xdc_runtime_Log_EventRec* evRec );
__extern xdc_Void xdc_runtime_Log_doPrint__R( xdc_runtime_Log_EventRec* evRec );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdc_runtime_Log_Module_startupDone() xdc_runtime_Log_Module__startupDone__S()

/* Object_heap */
#define xdc_runtime_Log_Object_heap() xdc_runtime_Log_Object__heap__C

/* Module_heap */
#define xdc_runtime_Log_Module_heap() xdc_runtime_Log_Object__heap__C

/* Module_id */
static inline CT__xdc_runtime_Log_Module__id xdc_runtime_Log_Module_id( void ) 
{
    return xdc_runtime_Log_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_Log_Module_hasMask( void ) 
{
    return xdc_runtime_Log_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_Log_Module_getMask( void ) 
{
    return xdc_runtime_Log_Module__diagsMask__C != NULL ? *xdc_runtime_Log_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void xdc_runtime_Log_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_Log_Module__diagsMask__C != NULL) *xdc_runtime_Log_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#include <xdc/runtime/Log__epilogue.h>

#ifdef xdc_runtime_Log__top__
#undef __nested__
#endif

#endif /* xdc_runtime_Log__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdc_runtime_Log__internalaccess))

#ifndef xdc_runtime_Log__include_state
#define xdc_runtime_Log__include_state


#endif /* xdc_runtime_Log__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_Log__nolocalnames)

/* module prefix */
#define Log_NUMARGS xdc_runtime_Log_NUMARGS
#define Log_PRINTFID xdc_runtime_Log_PRINTFID
#define Log_EventRec xdc_runtime_Log_EventRec
#define Log_Event xdc_runtime_Log_Event
#define Log_EventId xdc_runtime_Log_EventId
#define Log_L_construct xdc_runtime_Log_L_construct
#define Log_L_create xdc_runtime_Log_L_create
#define Log_L_destruct xdc_runtime_Log_L_destruct
#define Log_L_delete xdc_runtime_Log_L_delete
#define Log_getMask xdc_runtime_Log_getMask
#define Log_getRope xdc_runtime_Log_getRope
#define Log_getEventId xdc_runtime_Log_getEventId
#define Log_print0 xdc_runtime_Log_print0
#define Log_print1 xdc_runtime_Log_print1
#define Log_print2 xdc_runtime_Log_print2
#define Log_print3 xdc_runtime_Log_print3
#define Log_print4 xdc_runtime_Log_print4
#define Log_print5 xdc_runtime_Log_print5
#define Log_print6 xdc_runtime_Log_print6
#define Log_put4 xdc_runtime_Log_put4
#define Log_put8 xdc_runtime_Log_put8
#define Log_write0 xdc_runtime_Log_write0
#define Log_write1 xdc_runtime_Log_write1
#define Log_write2 xdc_runtime_Log_write2
#define Log_write3 xdc_runtime_Log_write3
#define Log_write4 xdc_runtime_Log_write4
#define Log_write5 xdc_runtime_Log_write5
#define Log_write6 xdc_runtime_Log_write6
#define Log_write7 xdc_runtime_Log_write7
#define Log_write8 xdc_runtime_Log_write8
#define Log_doPrint xdc_runtime_Log_doPrint
#define Log_Module_name xdc_runtime_Log_Module_name
#define Log_Module_id xdc_runtime_Log_Module_id
#define Log_Module_startup xdc_runtime_Log_Module_startup
#define Log_Module_startupDone xdc_runtime_Log_Module_startupDone
#define Log_Module_hasMask xdc_runtime_Log_Module_hasMask
#define Log_Module_getMask xdc_runtime_Log_Module_getMask
#define Log_Module_setMask xdc_runtime_Log_Module_setMask
#define Log_Object_heap xdc_runtime_Log_Object_heap
#define Log_Module_heap xdc_runtime_Log_Module_heap

#endif
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

