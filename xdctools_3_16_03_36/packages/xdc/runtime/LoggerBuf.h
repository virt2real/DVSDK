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
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
 *     CONVERTORS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef xdc_runtime_LoggerBuf__include
#define xdc_runtime_LoggerBuf__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_LoggerBuf__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_LoggerBuf___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <xdc/runtime/package/package.defs.h>

#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/ITimestampClient.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/ILogger.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/package/LoggerBuf_TimestampProxy.h>
#include <xdc/runtime/package/LoggerBuf_Module_GateProxy.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* BufType */
enum xdc_runtime_LoggerBuf_BufType {
    xdc_runtime_LoggerBuf_BufType_CIRCULAR,
    xdc_runtime_LoggerBuf_BufType_FIXED
};
typedef enum xdc_runtime_LoggerBuf_BufType xdc_runtime_LoggerBuf_BufType;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* FULL */
#define xdc_runtime_LoggerBuf_FULL (-1)

/* WRAP */
#define xdc_runtime_LoggerBuf_WRAP (0)

/* NEXT */
#define xdc_runtime_LoggerBuf_NEXT (1)

/* Entry */
struct xdc_runtime_LoggerBuf_Entry {
    xdc_runtime_Types_Timestamp64 tstamp;
    xdc_Bits32 serial;
    xdc_runtime_Types_Event evt;
    xdc_IArg arg1;
    xdc_IArg arg2;
    xdc_IArg arg3;
    xdc_IArg arg4;
};

/* Instance_State */
typedef xdc_runtime_LoggerBuf_Entry __T1_xdc_runtime_LoggerBuf_Instance_State__entryArr;
typedef xdc_runtime_LoggerBuf_Entry *__ARRAY1_xdc_runtime_LoggerBuf_Instance_State__entryArr;
typedef __ARRAY1_xdc_runtime_LoggerBuf_Instance_State__entryArr __TA_xdc_runtime_LoggerBuf_Instance_State__entryArr;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_LoggerBuf_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__diagsEnabled xdc_runtime_LoggerBuf_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_LoggerBuf_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__diagsIncluded xdc_runtime_LoggerBuf_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_LoggerBuf_Module__diagsMask;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__diagsMask xdc_runtime_LoggerBuf_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_LoggerBuf_Module__gateObj;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__gateObj xdc_runtime_LoggerBuf_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_LoggerBuf_Module__gatePrms;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__gatePrms xdc_runtime_LoggerBuf_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_LoggerBuf_Module__id;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__id xdc_runtime_LoggerBuf_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_LoggerBuf_Module__loggerDefined;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__loggerDefined xdc_runtime_LoggerBuf_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_LoggerBuf_Module__loggerObj;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__loggerObj xdc_runtime_LoggerBuf_Module__loggerObj__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_LoggerBuf_Module__loggerFxn4;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__loggerFxn4 xdc_runtime_LoggerBuf_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_LoggerBuf_Module__loggerFxn8;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__loggerFxn8 xdc_runtime_LoggerBuf_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_LoggerBuf_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__startupDoneFxn xdc_runtime_LoggerBuf_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_LoggerBuf_Object__count;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Object__count xdc_runtime_LoggerBuf_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_LoggerBuf_Object__heap;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Object__heap xdc_runtime_LoggerBuf_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_LoggerBuf_Object__sizeof;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Object__sizeof xdc_runtime_LoggerBuf_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_LoggerBuf_Object__table;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Object__table xdc_runtime_LoggerBuf_Object__table__C;

/* enableFlush */
#define xdc_runtime_LoggerBuf_enableFlush (xdc_runtime_LoggerBuf_enableFlush__C)
typedef xdc_Bool CT__xdc_runtime_LoggerBuf_enableFlush;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_enableFlush xdc_runtime_LoggerBuf_enableFlush__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_LoggerBuf_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    xdc_Int numEntries;
    xdc_runtime_LoggerBuf_BufType bufType;
    xdc_Bool exitFlush;
    xdc_runtime_IHeap_Handle bufHeap;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct xdc_runtime_LoggerBuf_Struct {
    const xdc_runtime_LoggerBuf_Fxns__* __fxns;
    xdc_runtime_IHeap_Handle __f0;
    __TA_xdc_runtime_LoggerBuf_Instance_State__entryArr __f1;
    xdc_runtime_LoggerBuf_Entry* __f2;
    xdc_runtime_LoggerBuf_Entry* __f3;
    xdc_runtime_LoggerBuf_Entry* __f4;
    xdc_Bits32 __f5;
    xdc_Int16 __f6;
    xdc_Int8 __f7;
    xdc_Bool __f8;
    xdc_Bool __f9;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_LoggerBuf_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Void (*write4)(xdc_runtime_LoggerBuf_Handle, xdc_runtime_Types_Event, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg);
    xdc_Void (*write8)(xdc_runtime_LoggerBuf_Handle, xdc_runtime_Types_Event, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const xdc_runtime_LoggerBuf_Fxns__ xdc_runtime_LoggerBuf_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdc_runtime_LoggerBuf_Module_startup xdc_runtime_LoggerBuf_Module_startup__E
xdc__CODESECT(xdc_runtime_LoggerBuf_Module_startup__E, "xdc_runtime_LoggerBuf_Module_startup")
__extern xdc_Int xdc_runtime_LoggerBuf_Module_startup__E( xdc_Int state );
xdc__CODESECT(xdc_runtime_LoggerBuf_Module_startup__F, "xdc_runtime_LoggerBuf_Module_startup")
__extern xdc_Int xdc_runtime_LoggerBuf_Module_startup__F( xdc_Int state );
xdc__CODESECT(xdc_runtime_LoggerBuf_Module_startup__R, "xdc_runtime_LoggerBuf_Module_startup")
__extern xdc_Int xdc_runtime_LoggerBuf_Module_startup__R( xdc_Int state );

/* Instance_init__F */
xdc__CODESECT(xdc_runtime_LoggerBuf_Instance_init__F, "xdc_runtime_LoggerBuf_Instance_init")
__extern int xdc_runtime_LoggerBuf_Instance_init__F( xdc_runtime_LoggerBuf_Object*, const xdc_runtime_LoggerBuf_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__F */
xdc__CODESECT(xdc_runtime_LoggerBuf_Instance_finalize__F, "xdc_runtime_LoggerBuf_Instance_finalize")
__extern void xdc_runtime_LoggerBuf_Instance_finalize__F( xdc_runtime_LoggerBuf_Object* , int );

/* Instance_init__R */
xdc__CODESECT(xdc_runtime_LoggerBuf_Instance_init__R, "xdc_runtime_LoggerBuf_Instance_init")
__extern int xdc_runtime_LoggerBuf_Instance_init__R( xdc_runtime_LoggerBuf_Object*, const xdc_runtime_LoggerBuf_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__R */
xdc__CODESECT(xdc_runtime_LoggerBuf_Instance_finalize__R, "xdc_runtime_LoggerBuf_Instance_finalize")
__extern void xdc_runtime_LoggerBuf_Instance_finalize__R( xdc_runtime_LoggerBuf_Object* , int );

/* Handle__label__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Handle__label__S, "xdc_runtime_LoggerBuf_Handle__label")
__extern xdc_runtime_Types_Label* xdc_runtime_LoggerBuf_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Module__startupDone__S, "xdc_runtime_LoggerBuf_Module__startupDone")
__extern xdc_Bool xdc_runtime_LoggerBuf_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Object__create__S, "xdc_runtime_LoggerBuf_Object__create")
__extern xdc_Ptr xdc_runtime_LoggerBuf_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Object__delete__S, "xdc_runtime_LoggerBuf_Object__delete")
__extern xdc_Void xdc_runtime_LoggerBuf_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Object__destruct__S, "xdc_runtime_LoggerBuf_Object__destruct")
__extern xdc_Void xdc_runtime_LoggerBuf_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Object__get__S, "xdc_runtime_LoggerBuf_Object__get")
__extern xdc_Ptr xdc_runtime_LoggerBuf_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Object__first__S, "xdc_runtime_LoggerBuf_Object__first")
__extern xdc_Ptr xdc_runtime_LoggerBuf_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Object__next__S, "xdc_runtime_LoggerBuf_Object__next")
__extern xdc_Ptr xdc_runtime_LoggerBuf_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Params__init__S, "xdc_runtime_LoggerBuf_Params__init")
__extern xdc_Void xdc_runtime_LoggerBuf_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Proxy__abstract__S, "xdc_runtime_LoggerBuf_Proxy__abstract")
__extern xdc_Bool xdc_runtime_LoggerBuf_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Proxy__delegate__S, "xdc_runtime_LoggerBuf_Proxy__delegate")
__extern xdc_Ptr xdc_runtime_LoggerBuf_Proxy__delegate__S( void );

/* write4__E */
#define xdc_runtime_LoggerBuf_write4 xdc_runtime_LoggerBuf_write4__E
xdc__CODESECT(xdc_runtime_LoggerBuf_write4__E, "xdc_runtime_LoggerBuf_write4")
__extern xdc_Void xdc_runtime_LoggerBuf_write4__E( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Types_Event evt, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4 );
xdc__CODESECT(xdc_runtime_LoggerBuf_write4__F, "xdc_runtime_LoggerBuf_write4")
__extern xdc_Void xdc_runtime_LoggerBuf_write4__F( xdc_runtime_LoggerBuf_Object* __inst, xdc_runtime_Types_Event evt, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4 );
__extern xdc_Void xdc_runtime_LoggerBuf_write4__R( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Types_Event evt, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4 );

/* write8__E */
#define xdc_runtime_LoggerBuf_write8 xdc_runtime_LoggerBuf_write8__E
xdc__CODESECT(xdc_runtime_LoggerBuf_write8__E, "xdc_runtime_LoggerBuf_write8")
__extern xdc_Void xdc_runtime_LoggerBuf_write8__E( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Types_Event evt, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8 );
xdc__CODESECT(xdc_runtime_LoggerBuf_write8__F, "xdc_runtime_LoggerBuf_write8")
__extern xdc_Void xdc_runtime_LoggerBuf_write8__F( xdc_runtime_LoggerBuf_Object* __inst, xdc_runtime_Types_Event evt, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8 );
__extern xdc_Void xdc_runtime_LoggerBuf_write8__R( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Types_Event evt, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8 );

/* flushAll__E */
#define xdc_runtime_LoggerBuf_flushAll xdc_runtime_LoggerBuf_flushAll__E
xdc__CODESECT(xdc_runtime_LoggerBuf_flushAll__E, "xdc_runtime_LoggerBuf_flushAll")
__extern xdc_Void xdc_runtime_LoggerBuf_flushAll__E( void );
xdc__CODESECT(xdc_runtime_LoggerBuf_flushAll__F, "xdc_runtime_LoggerBuf_flushAll")
__extern xdc_Void xdc_runtime_LoggerBuf_flushAll__F( void );
__extern xdc_Void xdc_runtime_LoggerBuf_flushAll__R( void );

/* flushAllInternal__E */
#define xdc_runtime_LoggerBuf_flushAllInternal xdc_runtime_LoggerBuf_flushAllInternal__E
xdc__CODESECT(xdc_runtime_LoggerBuf_flushAllInternal__E, "xdc_runtime_LoggerBuf_flushAllInternal")
__extern xdc_Void xdc_runtime_LoggerBuf_flushAllInternal__E( xdc_Int stat );
xdc__CODESECT(xdc_runtime_LoggerBuf_flushAllInternal__F, "xdc_runtime_LoggerBuf_flushAllInternal")
__extern xdc_Void xdc_runtime_LoggerBuf_flushAllInternal__F( xdc_Int stat );
__extern xdc_Void xdc_runtime_LoggerBuf_flushAllInternal__R( xdc_Int stat );

/* enable__E */
#define xdc_runtime_LoggerBuf_enable xdc_runtime_LoggerBuf_enable__E
xdc__CODESECT(xdc_runtime_LoggerBuf_enable__E, "xdc_runtime_LoggerBuf_enable")
__extern xdc_Bool xdc_runtime_LoggerBuf_enable__E( xdc_runtime_LoggerBuf_Handle __inst );
xdc__CODESECT(xdc_runtime_LoggerBuf_enable__F, "xdc_runtime_LoggerBuf_enable")
__extern xdc_Bool xdc_runtime_LoggerBuf_enable__F( xdc_runtime_LoggerBuf_Object* __inst );
__extern xdc_Bool xdc_runtime_LoggerBuf_enable__R( xdc_runtime_LoggerBuf_Handle __inst );

/* disable__E */
#define xdc_runtime_LoggerBuf_disable xdc_runtime_LoggerBuf_disable__E
xdc__CODESECT(xdc_runtime_LoggerBuf_disable__E, "xdc_runtime_LoggerBuf_disable")
__extern xdc_Bool xdc_runtime_LoggerBuf_disable__E( xdc_runtime_LoggerBuf_Handle __inst );
xdc__CODESECT(xdc_runtime_LoggerBuf_disable__F, "xdc_runtime_LoggerBuf_disable")
__extern xdc_Bool xdc_runtime_LoggerBuf_disable__F( xdc_runtime_LoggerBuf_Object* __inst );
__extern xdc_Bool xdc_runtime_LoggerBuf_disable__R( xdc_runtime_LoggerBuf_Handle __inst );

/* reset__E */
#define xdc_runtime_LoggerBuf_reset xdc_runtime_LoggerBuf_reset__E
xdc__CODESECT(xdc_runtime_LoggerBuf_reset__E, "xdc_runtime_LoggerBuf_reset")
__extern xdc_Void xdc_runtime_LoggerBuf_reset__E( xdc_runtime_LoggerBuf_Handle __inst );
xdc__CODESECT(xdc_runtime_LoggerBuf_reset__F, "xdc_runtime_LoggerBuf_reset")
__extern xdc_Void xdc_runtime_LoggerBuf_reset__F( xdc_runtime_LoggerBuf_Object* __inst );
__extern xdc_Void xdc_runtime_LoggerBuf_reset__R( xdc_runtime_LoggerBuf_Handle __inst );

/* flush__E */
#define xdc_runtime_LoggerBuf_flush xdc_runtime_LoggerBuf_flush__E
xdc__CODESECT(xdc_runtime_LoggerBuf_flush__E, "xdc_runtime_LoggerBuf_flush")
__extern xdc_Void xdc_runtime_LoggerBuf_flush__E( xdc_runtime_LoggerBuf_Handle __inst );
xdc__CODESECT(xdc_runtime_LoggerBuf_flush__F, "xdc_runtime_LoggerBuf_flush")
__extern xdc_Void xdc_runtime_LoggerBuf_flush__F( xdc_runtime_LoggerBuf_Object* __inst );
__extern xdc_Void xdc_runtime_LoggerBuf_flush__R( xdc_runtime_LoggerBuf_Handle __inst );

/* getNextEntry__E */
#define xdc_runtime_LoggerBuf_getNextEntry xdc_runtime_LoggerBuf_getNextEntry__E
xdc__CODESECT(xdc_runtime_LoggerBuf_getNextEntry__E, "xdc_runtime_LoggerBuf_getNextEntry")
__extern xdc_Int xdc_runtime_LoggerBuf_getNextEntry__E( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Log_EventRec* evtRec );
xdc__CODESECT(xdc_runtime_LoggerBuf_getNextEntry__F, "xdc_runtime_LoggerBuf_getNextEntry")
__extern xdc_Int xdc_runtime_LoggerBuf_getNextEntry__F( xdc_runtime_LoggerBuf_Object* __inst, xdc_runtime_Log_EventRec* evtRec );
__extern xdc_Int xdc_runtime_LoggerBuf_getNextEntry__R( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Log_EventRec* evtRec );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* write4_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_LoggerBuf_write4_FxnT)(void*, xdc_runtime_Types_Event, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg);
static inline xdc_runtime_LoggerBuf_write4_FxnT xdc_runtime_LoggerBuf_write4_fxnP( void )
{
    return (xdc_runtime_LoggerBuf_write4_FxnT)xdc_runtime_LoggerBuf_write4; 
}

/* write8_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_LoggerBuf_write8_FxnT)(void*, xdc_runtime_Types_Event, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg);
static inline xdc_runtime_LoggerBuf_write8_FxnT xdc_runtime_LoggerBuf_write8_fxnP( void )
{
    return (xdc_runtime_LoggerBuf_write8_FxnT)xdc_runtime_LoggerBuf_write8; 
}

/* enable_{FxnT,fxnP} */
typedef xdc_Bool (*xdc_runtime_LoggerBuf_enable_FxnT)(void*);
static inline xdc_runtime_LoggerBuf_enable_FxnT xdc_runtime_LoggerBuf_enable_fxnP( void )
{
    return (xdc_runtime_LoggerBuf_enable_FxnT)xdc_runtime_LoggerBuf_enable; 
}

/* disable_{FxnT,fxnP} */
typedef xdc_Bool (*xdc_runtime_LoggerBuf_disable_FxnT)(void*);
static inline xdc_runtime_LoggerBuf_disable_FxnT xdc_runtime_LoggerBuf_disable_fxnP( void )
{
    return (xdc_runtime_LoggerBuf_disable_FxnT)xdc_runtime_LoggerBuf_disable; 
}

/* reset_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_LoggerBuf_reset_FxnT)(void*);
static inline xdc_runtime_LoggerBuf_reset_FxnT xdc_runtime_LoggerBuf_reset_fxnP( void )
{
    return (xdc_runtime_LoggerBuf_reset_FxnT)xdc_runtime_LoggerBuf_reset; 
}

/* flush_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_LoggerBuf_flush_FxnT)(void*);
static inline xdc_runtime_LoggerBuf_flush_FxnT xdc_runtime_LoggerBuf_flush_fxnP( void )
{
    return (xdc_runtime_LoggerBuf_flush_FxnT)xdc_runtime_LoggerBuf_flush; 
}

/* getNextEntry_{FxnT,fxnP} */
typedef xdc_Int (*xdc_runtime_LoggerBuf_getNextEntry_FxnT)(void*, xdc_runtime_Log_EventRec*);
static inline xdc_runtime_LoggerBuf_getNextEntry_FxnT xdc_runtime_LoggerBuf_getNextEntry_fxnP( void )
{
    return (xdc_runtime_LoggerBuf_getNextEntry_FxnT)xdc_runtime_LoggerBuf_getNextEntry; 
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_ILogger_Module xdc_runtime_LoggerBuf_Module_upCast( void )
{
    return (xdc_runtime_ILogger_Module)&xdc_runtime_LoggerBuf_Module__FXNS__C;
}

/* Module_to_xdc_runtime_ILogger */
#define xdc_runtime_LoggerBuf_Module_to_xdc_runtime_ILogger xdc_runtime_LoggerBuf_Module_upCast

/* Handle_upCast */
static inline xdc_runtime_ILogger_Handle xdc_runtime_LoggerBuf_Handle_upCast( xdc_runtime_LoggerBuf_Handle i )
{
    return (xdc_runtime_ILogger_Handle)i;
}

/* Handle_to_xdc_runtime_ILogger */
#define xdc_runtime_LoggerBuf_Handle_to_xdc_runtime_ILogger xdc_runtime_LoggerBuf_Handle_upCast

/* Handle_downCast */
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Handle_downCast( xdc_runtime_ILogger_Handle i )
{
    xdc_runtime_ILogger_Handle i2 = (xdc_runtime_ILogger_Handle)i;
    return (void*)i2->__fxns == (void*)&xdc_runtime_LoggerBuf_Module__FXNS__C ? (xdc_runtime_LoggerBuf_Handle)i : 0;
}

/* Handle_from_xdc_runtime_ILogger */
#define xdc_runtime_LoggerBuf_Handle_from_xdc_runtime_ILogger xdc_runtime_LoggerBuf_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdc_runtime_LoggerBuf_Module_startupDone() xdc_runtime_LoggerBuf_Module__startupDone__S()

/* Object_heap */
#define xdc_runtime_LoggerBuf_Object_heap() xdc_runtime_LoggerBuf_Object__heap__C

/* Module_heap */
#define xdc_runtime_LoggerBuf_Module_heap() xdc_runtime_LoggerBuf_Object__heap__C

/* Module_id */
static inline CT__xdc_runtime_LoggerBuf_Module__id xdc_runtime_LoggerBuf_Module_id( void ) 
{
    return xdc_runtime_LoggerBuf_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_LoggerBuf_Module_hasMask( void ) 
{
    return xdc_runtime_LoggerBuf_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_LoggerBuf_Module_getMask( void ) 
{
    return xdc_runtime_LoggerBuf_Module__diagsMask__C != NULL ? *xdc_runtime_LoggerBuf_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void xdc_runtime_LoggerBuf_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_LoggerBuf_Module__diagsMask__C != NULL) *xdc_runtime_LoggerBuf_Module__diagsMask__C = mask;
}

/* Params_init */
static inline void xdc_runtime_LoggerBuf_Params_init( xdc_runtime_LoggerBuf_Params* prms ) 
{
    if (prms) {
        xdc_runtime_LoggerBuf_Params__init__S(prms, 0, sizeof(xdc_runtime_LoggerBuf_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void xdc_runtime_LoggerBuf_Params_copy( xdc_runtime_LoggerBuf_Params* dst, const xdc_runtime_LoggerBuf_Params* src ) 
{
    if (dst) {
        xdc_runtime_LoggerBuf_Params__init__S(dst, (xdc_Ptr)src, sizeof(xdc_runtime_LoggerBuf_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define xdc_runtime_LoggerBuf_Object_count() xdc_runtime_LoggerBuf_Object__count__C

/* Object_sizeof */
#define xdc_runtime_LoggerBuf_Object_sizeof() xdc_runtime_LoggerBuf_Object__sizeof__C

/* Object_get */
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Object_get( xdc_runtime_LoggerBuf_Instance_State* oarr, int i ) 
{
    return (xdc_runtime_LoggerBuf_Handle)xdc_runtime_LoggerBuf_Object__get__S(oarr, i);
}

/* Object_first */
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Object_first( void )
{
    return (xdc_runtime_LoggerBuf_Handle)xdc_runtime_LoggerBuf_Object__first__S();
}

/* Object_next */
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Object_next( xdc_runtime_LoggerBuf_Object* obj )
{
    return (xdc_runtime_LoggerBuf_Handle)xdc_runtime_LoggerBuf_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label* xdc_runtime_LoggerBuf_Handle_label( xdc_runtime_LoggerBuf_Handle inst, xdc_runtime_Types_Label* lab )
{
    return xdc_runtime_LoggerBuf_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline String xdc_runtime_LoggerBuf_Handle_name( xdc_runtime_LoggerBuf_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return xdc_runtime_LoggerBuf_Handle__label__S(inst, &lab)->iname;
}

/* create */
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_create( const xdc_runtime_LoggerBuf_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    return (xdc_runtime_LoggerBuf_Handle)xdc_runtime_LoggerBuf_Object__create__S(0, 0, 0, (const xdc_UChar*)__prms, sizeof(xdc_runtime_LoggerBuf_Params), __eb);
}

/* construct */
static inline void xdc_runtime_LoggerBuf_construct( xdc_runtime_LoggerBuf_Struct* __obj, const xdc_runtime_LoggerBuf_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    xdc_runtime_LoggerBuf_Object__create__S(__obj, sizeof (xdc_runtime_LoggerBuf_Struct), 0, (const xdc_UChar*)__prms, sizeof(xdc_runtime_LoggerBuf_Params), __eb);
}

/* delete */
static inline void xdc_runtime_LoggerBuf_delete( xdc_runtime_LoggerBuf_Handle* instp )
{
    xdc_runtime_LoggerBuf_Object__delete__S(instp);
}

/* destruct */
static inline void xdc_runtime_LoggerBuf_destruct( xdc_runtime_LoggerBuf_Struct* obj )
{
    xdc_runtime_LoggerBuf_Object__destruct__S(obj);
}

/* handle */
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_handle( xdc_runtime_LoggerBuf_Struct* str )
{
    return (xdc_runtime_LoggerBuf_Handle)str;
}

/* struct */
static inline xdc_runtime_LoggerBuf_Struct* xdc_runtime_LoggerBuf_struct( xdc_runtime_LoggerBuf_Handle inst )
{
    return (xdc_runtime_LoggerBuf_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_LoggerBuf__top__
#undef __nested__
#endif

#endif /* xdc_runtime_LoggerBuf__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdc_runtime_LoggerBuf__internalaccess))

#ifndef xdc_runtime_LoggerBuf__include_state
#define xdc_runtime_LoggerBuf__include_state

/* Object */
struct xdc_runtime_LoggerBuf_Object {
    const xdc_runtime_LoggerBuf_Fxns__* __fxns;
    xdc_runtime_IHeap_Handle bufHeap;
    __TA_xdc_runtime_LoggerBuf_Instance_State__entryArr entryArr;
    xdc_runtime_LoggerBuf_Entry* curEntry;
    xdc_runtime_LoggerBuf_Entry* endEntry;
    xdc_runtime_LoggerBuf_Entry* readEntry;
    xdc_Bits32 serial;
    xdc_Int16 numEntries;
    xdc_Int8 advance;
    xdc_Bool enabled;
    xdc_Bool flush;
};

#endif /* xdc_runtime_LoggerBuf__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_LoggerBuf__nolocalnames)

/* module prefix */
#define LoggerBuf_Instance xdc_runtime_LoggerBuf_Instance
#define LoggerBuf_Handle xdc_runtime_LoggerBuf_Handle
#define LoggerBuf_Module xdc_runtime_LoggerBuf_Module
#define LoggerBuf_Object xdc_runtime_LoggerBuf_Object
#define LoggerBuf_Struct xdc_runtime_LoggerBuf_Struct
#define LoggerBuf_BufType xdc_runtime_LoggerBuf_BufType
#define LoggerBuf_FULL xdc_runtime_LoggerBuf_FULL
#define LoggerBuf_WRAP xdc_runtime_LoggerBuf_WRAP
#define LoggerBuf_NEXT xdc_runtime_LoggerBuf_NEXT
#define LoggerBuf_Entry xdc_runtime_LoggerBuf_Entry
#define LoggerBuf_Instance_State xdc_runtime_LoggerBuf_Instance_State
#define LoggerBuf_BufType_CIRCULAR xdc_runtime_LoggerBuf_BufType_CIRCULAR
#define LoggerBuf_BufType_FIXED xdc_runtime_LoggerBuf_BufType_FIXED
#define LoggerBuf_enableFlush xdc_runtime_LoggerBuf_enableFlush
#define LoggerBuf_Params xdc_runtime_LoggerBuf_Params
#define LoggerBuf_write4 xdc_runtime_LoggerBuf_write4
#define LoggerBuf_write4_fxnP xdc_runtime_LoggerBuf_write4_fxnP
#define LoggerBuf_write4_FxnT xdc_runtime_LoggerBuf_write4_FxnT
#define LoggerBuf_write8 xdc_runtime_LoggerBuf_write8
#define LoggerBuf_write8_fxnP xdc_runtime_LoggerBuf_write8_fxnP
#define LoggerBuf_write8_FxnT xdc_runtime_LoggerBuf_write8_FxnT
#define LoggerBuf_flushAll xdc_runtime_LoggerBuf_flushAll
#define LoggerBuf_flushAllInternal xdc_runtime_LoggerBuf_flushAllInternal
#define LoggerBuf_enable xdc_runtime_LoggerBuf_enable
#define LoggerBuf_enable_fxnP xdc_runtime_LoggerBuf_enable_fxnP
#define LoggerBuf_enable_FxnT xdc_runtime_LoggerBuf_enable_FxnT
#define LoggerBuf_disable xdc_runtime_LoggerBuf_disable
#define LoggerBuf_disable_fxnP xdc_runtime_LoggerBuf_disable_fxnP
#define LoggerBuf_disable_FxnT xdc_runtime_LoggerBuf_disable_FxnT
#define LoggerBuf_reset xdc_runtime_LoggerBuf_reset
#define LoggerBuf_reset_fxnP xdc_runtime_LoggerBuf_reset_fxnP
#define LoggerBuf_reset_FxnT xdc_runtime_LoggerBuf_reset_FxnT
#define LoggerBuf_flush xdc_runtime_LoggerBuf_flush
#define LoggerBuf_flush_fxnP xdc_runtime_LoggerBuf_flush_fxnP
#define LoggerBuf_flush_FxnT xdc_runtime_LoggerBuf_flush_FxnT
#define LoggerBuf_getNextEntry xdc_runtime_LoggerBuf_getNextEntry
#define LoggerBuf_getNextEntry_fxnP xdc_runtime_LoggerBuf_getNextEntry_fxnP
#define LoggerBuf_getNextEntry_FxnT xdc_runtime_LoggerBuf_getNextEntry_FxnT
#define LoggerBuf_Module_name xdc_runtime_LoggerBuf_Module_name
#define LoggerBuf_Module_id xdc_runtime_LoggerBuf_Module_id
#define LoggerBuf_Module_startup xdc_runtime_LoggerBuf_Module_startup
#define LoggerBuf_Module_startupDone xdc_runtime_LoggerBuf_Module_startupDone
#define LoggerBuf_Module_hasMask xdc_runtime_LoggerBuf_Module_hasMask
#define LoggerBuf_Module_getMask xdc_runtime_LoggerBuf_Module_getMask
#define LoggerBuf_Module_setMask xdc_runtime_LoggerBuf_Module_setMask
#define LoggerBuf_Object_heap xdc_runtime_LoggerBuf_Object_heap
#define LoggerBuf_Module_heap xdc_runtime_LoggerBuf_Module_heap
#define LoggerBuf_construct xdc_runtime_LoggerBuf_construct
#define LoggerBuf_create xdc_runtime_LoggerBuf_create
#define LoggerBuf_handle xdc_runtime_LoggerBuf_handle
#define LoggerBuf_struct xdc_runtime_LoggerBuf_struct
#define LoggerBuf_Handle_label xdc_runtime_LoggerBuf_Handle_label
#define LoggerBuf_Handle_name xdc_runtime_LoggerBuf_Handle_name
#define LoggerBuf_Instance_init xdc_runtime_LoggerBuf_Instance_init
#define LoggerBuf_Object_count xdc_runtime_LoggerBuf_Object_count
#define LoggerBuf_Object_get xdc_runtime_LoggerBuf_Object_get
#define LoggerBuf_Object_first xdc_runtime_LoggerBuf_Object_first
#define LoggerBuf_Object_next xdc_runtime_LoggerBuf_Object_next
#define LoggerBuf_Object_sizeof xdc_runtime_LoggerBuf_Object_sizeof
#define LoggerBuf_Params_copy xdc_runtime_LoggerBuf_Params_copy
#define LoggerBuf_Params_init xdc_runtime_LoggerBuf_Params_init
#define LoggerBuf_Instance_finalize xdc_runtime_LoggerBuf_Instance_finalize
#define LoggerBuf_delete xdc_runtime_LoggerBuf_delete
#define LoggerBuf_destruct xdc_runtime_LoggerBuf_destruct
#define LoggerBuf_Module_upCast xdc_runtime_LoggerBuf_Module_upCast
#define LoggerBuf_Module_to_xdc_runtime_ILogger xdc_runtime_LoggerBuf_Module_to_xdc_runtime_ILogger
#define LoggerBuf_Handle_upCast xdc_runtime_LoggerBuf_Handle_upCast
#define LoggerBuf_Handle_to_xdc_runtime_ILogger xdc_runtime_LoggerBuf_Handle_to_xdc_runtime_ILogger
#define LoggerBuf_Handle_downCast xdc_runtime_LoggerBuf_Handle_downCast
#define LoggerBuf_Handle_from_xdc_runtime_ILogger xdc_runtime_LoggerBuf_Handle_from_xdc_runtime_ILogger

/* proxies */
#include <xdc/runtime/package/LoggerBuf_TimestampProxy.h>

/* proxies */
#include <xdc/runtime/package/LoggerBuf_Module_GateProxy.h>

#endif
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

