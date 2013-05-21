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

#ifndef xdc_runtime_System__include
#define xdc_runtime_System__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_System__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_System___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/package/package.defs.h>

#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/ISystemSupport.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/IModule.h>
#include <xdc/runtime/package/System_SupportProxy.h>
#include <xdc/runtime/package/System_Module_GateProxy.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* AtexitHandler */
typedef xdc_Void (*xdc_runtime_System_AtexitHandler)(xdc_Int);

/* STATUS_UNKNOWN */
#define xdc_runtime_System_STATUS_UNKNOWN (0xCAFE)


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* ParseData */
struct xdc_runtime_System_ParseData {
    xdc_Int width;
    xdc_Bool lFlag;
    xdc_Bool lJust;
    xdc_Int precis;
    xdc_Int len;
    xdc_Int zpad;
    xdc_Char* end;
    xdc_Bool aFlag;
    xdc_Char* ptr;
};

/* ExtendFxn */
typedef xdc_Int (*xdc_runtime_System_ExtendFxn)(xdc_Char**, xdc_Char**, xdc_VaList*, xdc_runtime_System_ParseData*);

/* Module_State */
typedef xdc_runtime_System_AtexitHandler __T1_xdc_runtime_System_Module_State__atexitHandlers;
typedef xdc_runtime_System_AtexitHandler *__ARRAY1_xdc_runtime_System_Module_State__atexitHandlers;
typedef __ARRAY1_xdc_runtime_System_Module_State__atexitHandlers __TA_xdc_runtime_System_Module_State__atexitHandlers;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_System_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_runtime_System_Module__diagsEnabled xdc_runtime_System_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_System_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_runtime_System_Module__diagsIncluded xdc_runtime_System_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_System_Module__diagsMask;
__extern __FAR__ const CT__xdc_runtime_System_Module__diagsMask xdc_runtime_System_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_System_Module__gateObj;
__extern __FAR__ const CT__xdc_runtime_System_Module__gateObj xdc_runtime_System_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_System_Module__gatePrms;
__extern __FAR__ const CT__xdc_runtime_System_Module__gatePrms xdc_runtime_System_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_System_Module__id;
__extern __FAR__ const CT__xdc_runtime_System_Module__id xdc_runtime_System_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_System_Module__loggerDefined;
__extern __FAR__ const CT__xdc_runtime_System_Module__loggerDefined xdc_runtime_System_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_System_Module__loggerObj;
__extern __FAR__ const CT__xdc_runtime_System_Module__loggerObj xdc_runtime_System_Module__loggerObj__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_System_Module__loggerFxn4;
__extern __FAR__ const CT__xdc_runtime_System_Module__loggerFxn4 xdc_runtime_System_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_System_Module__loggerFxn8;
__extern __FAR__ const CT__xdc_runtime_System_Module__loggerFxn8 xdc_runtime_System_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_System_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__xdc_runtime_System_Module__startupDoneFxn xdc_runtime_System_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_System_Object__count;
__extern __FAR__ const CT__xdc_runtime_System_Object__count xdc_runtime_System_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_System_Object__heap;
__extern __FAR__ const CT__xdc_runtime_System_Object__heap xdc_runtime_System_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_System_Object__sizeof;
__extern __FAR__ const CT__xdc_runtime_System_Object__sizeof xdc_runtime_System_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_System_Object__table;
__extern __FAR__ const CT__xdc_runtime_System_Object__table xdc_runtime_System_Object__table__C;

/* A_cannotFitIntoArg */
#define xdc_runtime_System_A_cannotFitIntoArg (xdc_runtime_System_A_cannotFitIntoArg__C)
typedef xdc_runtime_Assert_Id CT__xdc_runtime_System_A_cannotFitIntoArg;
__extern __FAR__ const CT__xdc_runtime_System_A_cannotFitIntoArg xdc_runtime_System_A_cannotFitIntoArg__C;

/* maxAtexitHandlers */
#define xdc_runtime_System_maxAtexitHandlers (xdc_runtime_System_maxAtexitHandlers__C)
typedef xdc_Int CT__xdc_runtime_System_maxAtexitHandlers;
__extern __FAR__ const CT__xdc_runtime_System_maxAtexitHandlers xdc_runtime_System_maxAtexitHandlers__C;

/* extendFxn */
#define xdc_runtime_System_extendFxn (xdc_runtime_System_extendFxn__C)
typedef xdc_runtime_System_ExtendFxn CT__xdc_runtime_System_extendFxn;
__extern __FAR__ const CT__xdc_runtime_System_extendFxn xdc_runtime_System_extendFxn__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdc_runtime_System_Module_startup xdc_runtime_System_Module_startup__E
xdc__CODESECT(xdc_runtime_System_Module_startup__E, "xdc_runtime_System_Module_startup")
__extern xdc_Int xdc_runtime_System_Module_startup__E( xdc_Int state );
xdc__CODESECT(xdc_runtime_System_Module_startup__F, "xdc_runtime_System_Module_startup")
__extern xdc_Int xdc_runtime_System_Module_startup__F( xdc_Int state );
xdc__CODESECT(xdc_runtime_System_Module_startup__R, "xdc_runtime_System_Module_startup")
__extern xdc_Int xdc_runtime_System_Module_startup__R( xdc_Int state );

/* Handle__label__S */
xdc__CODESECT(xdc_runtime_System_Handle__label__S, "xdc_runtime_System_Handle__label")
__extern xdc_runtime_Types_Label* xdc_runtime_System_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */
xdc__CODESECT(xdc_runtime_System_Module__startupDone__S, "xdc_runtime_System_Module__startupDone")
__extern xdc_Bool xdc_runtime_System_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(xdc_runtime_System_Object__create__S, "xdc_runtime_System_Object__create")
__extern xdc_Ptr xdc_runtime_System_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */
xdc__CODESECT(xdc_runtime_System_Object__delete__S, "xdc_runtime_System_Object__delete")
__extern xdc_Void xdc_runtime_System_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */
xdc__CODESECT(xdc_runtime_System_Object__destruct__S, "xdc_runtime_System_Object__destruct")
__extern xdc_Void xdc_runtime_System_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(xdc_runtime_System_Object__get__S, "xdc_runtime_System_Object__get")
__extern xdc_Ptr xdc_runtime_System_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(xdc_runtime_System_Object__first__S, "xdc_runtime_System_Object__first")
__extern xdc_Ptr xdc_runtime_System_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(xdc_runtime_System_Object__next__S, "xdc_runtime_System_Object__next")
__extern xdc_Ptr xdc_runtime_System_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(xdc_runtime_System_Params__init__S, "xdc_runtime_System_Params__init")
__extern xdc_Void xdc_runtime_System_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(xdc_runtime_System_Proxy__abstract__S, "xdc_runtime_System_Proxy__abstract")
__extern xdc_Bool xdc_runtime_System_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(xdc_runtime_System_Proxy__delegate__S, "xdc_runtime_System_Proxy__delegate")
__extern xdc_Ptr xdc_runtime_System_Proxy__delegate__S( void );

/* abort__E */
#define xdc_runtime_System_abort xdc_runtime_System_abort__E
xdc__CODESECT(xdc_runtime_System_abort__E, "xdc_runtime_System_abort")
__extern xdc_Void xdc_runtime_System_abort__E( xdc_String str );
xdc__CODESECT(xdc_runtime_System_abort__F, "xdc_runtime_System_abort")
__extern xdc_Void xdc_runtime_System_abort__F( xdc_String str );
__extern xdc_Void xdc_runtime_System_abort__R( xdc_String str );

/* atexit__E */
#define xdc_runtime_System_atexit xdc_runtime_System_atexit__E
xdc__CODESECT(xdc_runtime_System_atexit__E, "xdc_runtime_System_atexit")
__extern xdc_Bool xdc_runtime_System_atexit__E( xdc_runtime_System_AtexitHandler handler );
xdc__CODESECT(xdc_runtime_System_atexit__F, "xdc_runtime_System_atexit")
__extern xdc_Bool xdc_runtime_System_atexit__F( xdc_runtime_System_AtexitHandler handler );
__extern xdc_Bool xdc_runtime_System_atexit__R( xdc_runtime_System_AtexitHandler handler );

/* exit__E */
#define xdc_runtime_System_exit xdc_runtime_System_exit__E
xdc__CODESECT(xdc_runtime_System_exit__E, "xdc_runtime_System_exit")
__extern xdc_Void xdc_runtime_System_exit__E( xdc_Int stat );
xdc__CODESECT(xdc_runtime_System_exit__F, "xdc_runtime_System_exit")
__extern xdc_Void xdc_runtime_System_exit__F( xdc_Int stat );
__extern xdc_Void xdc_runtime_System_exit__R( xdc_Int stat );

/* putch__E */
#define xdc_runtime_System_putch xdc_runtime_System_putch__E
xdc__CODESECT(xdc_runtime_System_putch__E, "xdc_runtime_System_putch")
__extern xdc_Void xdc_runtime_System_putch__E( xdc_Char ch );
xdc__CODESECT(xdc_runtime_System_putch__F, "xdc_runtime_System_putch")
__extern xdc_Void xdc_runtime_System_putch__F( xdc_Char ch );
__extern xdc_Void xdc_runtime_System_putch__R( xdc_Char ch );

/* flush__E */
#define xdc_runtime_System_flush xdc_runtime_System_flush__E
xdc__CODESECT(xdc_runtime_System_flush__E, "xdc_runtime_System_flush")
__extern xdc_Void xdc_runtime_System_flush__E( void );
xdc__CODESECT(xdc_runtime_System_flush__F, "xdc_runtime_System_flush")
__extern xdc_Void xdc_runtime_System_flush__F( void );
__extern xdc_Void xdc_runtime_System_flush__R( void );

/* printf__E */
#define xdc_runtime_System_printf xdc_runtime_System_printf__E
xdc__CODESECT(xdc_runtime_System_printf__E, "xdc_runtime_System_printf")
__extern xdc_Int xdc_runtime_System_printf__E( xdc_String fmt, ... );
xdc__CODESECT(xdc_runtime_System_printf_va__E, "xdc_runtime_System_printf")
__extern xdc_Int xdc_runtime_System_printf_va__E( xdc_String fmt, va_list _va );
xdc__CODESECT(xdc_runtime_System_printf_va__F, "xdc_runtime_System_printf")
__extern xdc_Int xdc_runtime_System_printf_va__F( xdc_String fmt, va_list _va );
__extern xdc_Int xdc_runtime_System_printf_va__R( xdc_String fmt, va_list _va );

/* aprintf__E */
#define xdc_runtime_System_aprintf xdc_runtime_System_aprintf__E
xdc__CODESECT(xdc_runtime_System_aprintf__E, "xdc_runtime_System_aprintf")
__extern xdc_Int xdc_runtime_System_aprintf__E( xdc_String fmt, ... );
xdc__CODESECT(xdc_runtime_System_aprintf_va__E, "xdc_runtime_System_aprintf")
__extern xdc_Int xdc_runtime_System_aprintf_va__E( xdc_String fmt, va_list _va );
xdc__CODESECT(xdc_runtime_System_aprintf_va__F, "xdc_runtime_System_aprintf")
__extern xdc_Int xdc_runtime_System_aprintf_va__F( xdc_String fmt, va_list _va );
__extern xdc_Int xdc_runtime_System_aprintf_va__R( xdc_String fmt, va_list _va );

/* sprintf__E */
#define xdc_runtime_System_sprintf xdc_runtime_System_sprintf__E
xdc__CODESECT(xdc_runtime_System_sprintf__E, "xdc_runtime_System_sprintf")
__extern xdc_Int xdc_runtime_System_sprintf__E( xdc_Char buf[], xdc_String fmt, ... );
xdc__CODESECT(xdc_runtime_System_sprintf_va__E, "xdc_runtime_System_sprintf")
__extern xdc_Int xdc_runtime_System_sprintf_va__E( xdc_Char buf[], xdc_String fmt, va_list _va );
xdc__CODESECT(xdc_runtime_System_sprintf_va__F, "xdc_runtime_System_sprintf")
__extern xdc_Int xdc_runtime_System_sprintf_va__F( xdc_Char buf[], xdc_String fmt, va_list _va );
__extern xdc_Int xdc_runtime_System_sprintf_va__R( xdc_Char buf[], xdc_String fmt, va_list _va );

/* asprintf__E */
#define xdc_runtime_System_asprintf xdc_runtime_System_asprintf__E
xdc__CODESECT(xdc_runtime_System_asprintf__E, "xdc_runtime_System_asprintf")
__extern xdc_Int xdc_runtime_System_asprintf__E( xdc_Char buf[], xdc_String fmt, ... );
xdc__CODESECT(xdc_runtime_System_asprintf_va__E, "xdc_runtime_System_asprintf")
__extern xdc_Int xdc_runtime_System_asprintf_va__E( xdc_Char buf[], xdc_String fmt, va_list _va );
xdc__CODESECT(xdc_runtime_System_asprintf_va__F, "xdc_runtime_System_asprintf")
__extern xdc_Int xdc_runtime_System_asprintf_va__F( xdc_Char buf[], xdc_String fmt, va_list _va );
__extern xdc_Int xdc_runtime_System_asprintf_va__R( xdc_Char buf[], xdc_String fmt, va_list _va );

/* vprintf__E */
#define xdc_runtime_System_vprintf xdc_runtime_System_vprintf__E
xdc__CODESECT(xdc_runtime_System_vprintf__E, "xdc_runtime_System_vprintf")
__extern xdc_Int xdc_runtime_System_vprintf__E( xdc_String fmt, xdc_VaList va );
xdc__CODESECT(xdc_runtime_System_vprintf__F, "xdc_runtime_System_vprintf")
__extern xdc_Int xdc_runtime_System_vprintf__F( xdc_String fmt, xdc_VaList va );
__extern xdc_Int xdc_runtime_System_vprintf__R( xdc_String fmt, xdc_VaList va );

/* avprintf__E */
#define xdc_runtime_System_avprintf xdc_runtime_System_avprintf__E
xdc__CODESECT(xdc_runtime_System_avprintf__E, "xdc_runtime_System_avprintf")
__extern xdc_Int xdc_runtime_System_avprintf__E( xdc_String fmt, xdc_VaList va );
xdc__CODESECT(xdc_runtime_System_avprintf__F, "xdc_runtime_System_avprintf")
__extern xdc_Int xdc_runtime_System_avprintf__F( xdc_String fmt, xdc_VaList va );
__extern xdc_Int xdc_runtime_System_avprintf__R( xdc_String fmt, xdc_VaList va );

/* vsprintf__E */
#define xdc_runtime_System_vsprintf xdc_runtime_System_vsprintf__E
xdc__CODESECT(xdc_runtime_System_vsprintf__E, "xdc_runtime_System_vsprintf")
__extern xdc_Int xdc_runtime_System_vsprintf__E( xdc_Char buf[], xdc_String fmt, xdc_VaList va );
xdc__CODESECT(xdc_runtime_System_vsprintf__F, "xdc_runtime_System_vsprintf")
__extern xdc_Int xdc_runtime_System_vsprintf__F( xdc_Char buf[], xdc_String fmt, xdc_VaList va );
__extern xdc_Int xdc_runtime_System_vsprintf__R( xdc_Char buf[], xdc_String fmt, xdc_VaList va );

/* avsprintf__E */
#define xdc_runtime_System_avsprintf xdc_runtime_System_avsprintf__E
xdc__CODESECT(xdc_runtime_System_avsprintf__E, "xdc_runtime_System_avsprintf")
__extern xdc_Int xdc_runtime_System_avsprintf__E( xdc_Char buf[], xdc_String fmt, xdc_VaList va );
xdc__CODESECT(xdc_runtime_System_avsprintf__F, "xdc_runtime_System_avsprintf")
__extern xdc_Int xdc_runtime_System_avsprintf__F( xdc_Char buf[], xdc_String fmt, xdc_VaList va );
__extern xdc_Int xdc_runtime_System_avsprintf__R( xdc_Char buf[], xdc_String fmt, xdc_VaList va );

/* printfExtend__I */
#define xdc_runtime_System_printfExtend xdc_runtime_System_printfExtend__I
xdc__CODESECT(xdc_runtime_System_printfExtend__I, "xdc_runtime_System_printfExtend")
__extern xdc_Int xdc_runtime_System_printfExtend__I( xdc_Char** bufp, xdc_Char** fmt, xdc_VaList* va, xdc_runtime_System_ParseData* parse );

/* doPrint__I */
#define xdc_runtime_System_doPrint xdc_runtime_System_doPrint__I
xdc__CODESECT(xdc_runtime_System_doPrint__I, "xdc_runtime_System_doPrint")
__extern xdc_Int xdc_runtime_System_doPrint__I( xdc_Char buf[], xdc_String fmt, xdc_VaList va, xdc_Bool aFlag );

/* formatNum__I */
#define xdc_runtime_System_formatNum xdc_runtime_System_formatNum__I
xdc__CODESECT(xdc_runtime_System_formatNum__I, "xdc_runtime_System_formatNum")
__extern xdc_Char* xdc_runtime_System_formatNum__I( xdc_Char* ptr, xdc_UInt32 n, xdc_Int zpad, xdc_Int base );

/* putchar__I */
#define xdc_runtime_System_putchar xdc_runtime_System_putchar__I
xdc__CODESECT(xdc_runtime_System_putchar__I, "xdc_runtime_System_putchar")
__extern xdc_Void xdc_runtime_System_putchar__I( xdc_Char** bufp, xdc_Char ch );

/* rtsExit__I */
#define xdc_runtime_System_rtsExit xdc_runtime_System_rtsExit__I
xdc__CODESECT(xdc_runtime_System_rtsExit__I, "xdc_runtime_System_rtsExit")
__extern xdc_Void xdc_runtime_System_rtsExit__I( void );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdc_runtime_System_Module_startupDone() xdc_runtime_System_Module__startupDone__S()

/* Object_heap */
#define xdc_runtime_System_Object_heap() xdc_runtime_System_Object__heap__C

/* Module_heap */
#define xdc_runtime_System_Module_heap() xdc_runtime_System_Object__heap__C

/* Module_id */
static inline CT__xdc_runtime_System_Module__id xdc_runtime_System_Module_id( void ) 
{
    return xdc_runtime_System_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_System_Module_hasMask( void ) 
{
    return xdc_runtime_System_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_System_Module_getMask( void ) 
{
    return xdc_runtime_System_Module__diagsMask__C != NULL ? *xdc_runtime_System_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void xdc_runtime_System_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_System_Module__diagsMask__C != NULL) *xdc_runtime_System_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_System__top__
#undef __nested__
#endif

#endif /* xdc_runtime_System__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdc_runtime_System__internalaccess))

#ifndef xdc_runtime_System__include_state
#define xdc_runtime_System__include_state

/* Module_State */
struct xdc_runtime_System_Module_State {
    __TA_xdc_runtime_System_Module_State__atexitHandlers atexitHandlers;
    xdc_Int numAtexitHandlers;
    xdc_Int exitStatus;
};

/* Module__state__V */
#ifdef __config__
extern struct xdc_runtime_System_Module_State__ xdc_runtime_System_Module__state__V;
#else
extern xdc_runtime_System_Module_State xdc_runtime_System_Module__state__V;
#endif

#endif /* xdc_runtime_System__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_System__nolocalnames)

/* module prefix */
#define System_AtexitHandler xdc_runtime_System_AtexitHandler
#define System_STATUS_UNKNOWN xdc_runtime_System_STATUS_UNKNOWN
#define System_ParseData xdc_runtime_System_ParseData
#define System_ExtendFxn xdc_runtime_System_ExtendFxn
#define System_Module_State xdc_runtime_System_Module_State
#define System_A_cannotFitIntoArg xdc_runtime_System_A_cannotFitIntoArg
#define System_maxAtexitHandlers xdc_runtime_System_maxAtexitHandlers
#define System_extendFxn xdc_runtime_System_extendFxn
#define System_abort xdc_runtime_System_abort
#define System_atexit xdc_runtime_System_atexit
#define System_exit xdc_runtime_System_exit
#define System_putch xdc_runtime_System_putch
#define System_flush xdc_runtime_System_flush
#define System_printf xdc_runtime_System_printf
#define System_printf_va xdc_runtime_System_printf_va
#define System_aprintf xdc_runtime_System_aprintf
#define System_aprintf_va xdc_runtime_System_aprintf_va
#define System_sprintf xdc_runtime_System_sprintf
#define System_sprintf_va xdc_runtime_System_sprintf_va
#define System_asprintf xdc_runtime_System_asprintf
#define System_asprintf_va xdc_runtime_System_asprintf_va
#define System_vprintf xdc_runtime_System_vprintf
#define System_avprintf xdc_runtime_System_avprintf
#define System_vsprintf xdc_runtime_System_vsprintf
#define System_avsprintf xdc_runtime_System_avsprintf
#define System_Module_name xdc_runtime_System_Module_name
#define System_Module_id xdc_runtime_System_Module_id
#define System_Module_startup xdc_runtime_System_Module_startup
#define System_Module_startupDone xdc_runtime_System_Module_startupDone
#define System_Module_hasMask xdc_runtime_System_Module_hasMask
#define System_Module_getMask xdc_runtime_System_Module_getMask
#define System_Module_setMask xdc_runtime_System_Module_setMask
#define System_Object_heap xdc_runtime_System_Object_heap
#define System_Module_heap xdc_runtime_System_Module_heap

/* proxies */
#include <xdc/runtime/package/System_SupportProxy.h>

/* proxies */
#include <xdc/runtime/package/System_Module_GateProxy.h>

#endif
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

