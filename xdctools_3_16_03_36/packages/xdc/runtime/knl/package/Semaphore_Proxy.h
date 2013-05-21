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
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
 *     CONVERTORS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef xdc_runtime_knl_Semaphore_Proxy__include
#define xdc_runtime_knl_Semaphore_Proxy__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_knl_Semaphore_Proxy__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_knl_Semaphore_Proxy___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <xdc/runtime/knl/package/package.defs.h>

#include <xdc/runtime/knl/ISemaphore.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* PendStatus */
typedef xdc_runtime_knl_ISemaphore_PendStatus xdc_runtime_knl_Semaphore_Proxy_PendStatus;

/* FOREVER */
#define xdc_runtime_knl_Semaphore_Proxy_FOREVER (~(0))

/* Mode */
typedef xdc_runtime_knl_ISemaphore_Mode xdc_runtime_knl_Semaphore_Proxy_Mode;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_knl_Semaphore_Proxy_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Module__diagsEnabled xdc_runtime_knl_Semaphore_Proxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_knl_Semaphore_Proxy_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Module__diagsIncluded xdc_runtime_knl_Semaphore_Proxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_knl_Semaphore_Proxy_Module__diagsMask;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Module__diagsMask xdc_runtime_knl_Semaphore_Proxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_knl_Semaphore_Proxy_Module__gateObj;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Module__gateObj xdc_runtime_knl_Semaphore_Proxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_knl_Semaphore_Proxy_Module__gatePrms;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Module__gatePrms xdc_runtime_knl_Semaphore_Proxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_knl_Semaphore_Proxy_Module__id;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Module__id xdc_runtime_knl_Semaphore_Proxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_knl_Semaphore_Proxy_Module__loggerDefined;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Module__loggerDefined xdc_runtime_knl_Semaphore_Proxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_knl_Semaphore_Proxy_Module__loggerObj;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Module__loggerObj xdc_runtime_knl_Semaphore_Proxy_Module__loggerObj__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_knl_Semaphore_Proxy_Module__loggerFxn4;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Module__loggerFxn4 xdc_runtime_knl_Semaphore_Proxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_knl_Semaphore_Proxy_Module__loggerFxn8;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Module__loggerFxn8 xdc_runtime_knl_Semaphore_Proxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_knl_Semaphore_Proxy_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Module__startupDoneFxn xdc_runtime_knl_Semaphore_Proxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_knl_Semaphore_Proxy_Object__count;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Object__count xdc_runtime_knl_Semaphore_Proxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_knl_Semaphore_Proxy_Object__heap;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Object__heap xdc_runtime_knl_Semaphore_Proxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_knl_Semaphore_Proxy_Object__sizeof;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Object__sizeof xdc_runtime_knl_Semaphore_Proxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_knl_Semaphore_Proxy_Object__table;
__extern __FAR__ const CT__xdc_runtime_knl_Semaphore_Proxy_Object__table xdc_runtime_knl_Semaphore_Proxy_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_knl_Semaphore_Proxy_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    xdc_runtime_knl_ISemaphore_Mode mode;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct xdc_runtime_knl_Semaphore_Proxy_Struct {
    const xdc_runtime_knl_Semaphore_Proxy_Fxns__* __fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_knl_Semaphore_Proxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*pend)(xdc_runtime_knl_Semaphore_Proxy_Handle, xdc_UInt, xdc_runtime_Error_Block*);
    xdc_Bool (*post)(xdc_runtime_knl_Semaphore_Proxy_Handle, xdc_runtime_Error_Block*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const xdc_runtime_knl_Semaphore_Proxy_Fxns__ xdc_runtime_knl_Semaphore_Proxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdc_runtime_knl_Semaphore_Proxy_Module_startup( state ) -1

/* Handle__label__S */
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_Handle__label__S, "xdc_runtime_knl_Semaphore_Proxy_Handle__label")
__extern xdc_runtime_Types_Label* xdc_runtime_knl_Semaphore_Proxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_Module__startupDone__S, "xdc_runtime_knl_Semaphore_Proxy_Module__startupDone")
__extern xdc_Bool xdc_runtime_knl_Semaphore_Proxy_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_Object__create__S, "xdc_runtime_knl_Semaphore_Proxy_Object__create")
__extern xdc_Ptr xdc_runtime_knl_Semaphore_Proxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_Object__delete__S, "xdc_runtime_knl_Semaphore_Proxy_Object__delete")
__extern xdc_Void xdc_runtime_knl_Semaphore_Proxy_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_Object__destruct__S, "xdc_runtime_knl_Semaphore_Proxy_Object__destruct")
__extern xdc_Void xdc_runtime_knl_Semaphore_Proxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_Object__get__S, "xdc_runtime_knl_Semaphore_Proxy_Object__get")
__extern xdc_Ptr xdc_runtime_knl_Semaphore_Proxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_Object__first__S, "xdc_runtime_knl_Semaphore_Proxy_Object__first")
__extern xdc_Ptr xdc_runtime_knl_Semaphore_Proxy_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_Object__next__S, "xdc_runtime_knl_Semaphore_Proxy_Object__next")
__extern xdc_Ptr xdc_runtime_knl_Semaphore_Proxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_Params__init__S, "xdc_runtime_knl_Semaphore_Proxy_Params__init")
__extern xdc_Void xdc_runtime_knl_Semaphore_Proxy_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_Proxy__abstract__S, "xdc_runtime_knl_Semaphore_Proxy_Proxy__abstract")
__extern xdc_Bool xdc_runtime_knl_Semaphore_Proxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_Proxy__delegate__S, "xdc_runtime_knl_Semaphore_Proxy_Proxy__delegate")
__extern xdc_Ptr xdc_runtime_knl_Semaphore_Proxy_Proxy__delegate__S( void );

/* pend__E */
#define xdc_runtime_knl_Semaphore_Proxy_pend xdc_runtime_knl_Semaphore_Proxy_pend__E
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_pend__E, "xdc_runtime_knl_Semaphore_Proxy_pend")
__extern xdc_Int xdc_runtime_knl_Semaphore_Proxy_pend__E( xdc_runtime_knl_Semaphore_Proxy_Handle __inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb );
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_pend__R, "xdc_runtime_knl_Semaphore_Proxy_pend")
__extern xdc_Int xdc_runtime_knl_Semaphore_Proxy_pend__R( xdc_runtime_knl_Semaphore_Proxy_Handle __inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb );

/* post__E */
#define xdc_runtime_knl_Semaphore_Proxy_post xdc_runtime_knl_Semaphore_Proxy_post__E
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_post__E, "xdc_runtime_knl_Semaphore_Proxy_post")
__extern xdc_Bool xdc_runtime_knl_Semaphore_Proxy_post__E( xdc_runtime_knl_Semaphore_Proxy_Handle __inst, xdc_runtime_Error_Block* eb );
xdc__CODESECT(xdc_runtime_knl_Semaphore_Proxy_post__R, "xdc_runtime_knl_Semaphore_Proxy_post")
__extern xdc_Bool xdc_runtime_knl_Semaphore_Proxy_post__R( xdc_runtime_knl_Semaphore_Proxy_Handle __inst, xdc_runtime_Error_Block* eb );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* pend_{FxnT,fxnP} */
typedef xdc_Int (*xdc_runtime_knl_Semaphore_Proxy_pend_FxnT)(void*, xdc_UInt, xdc_runtime_Error_Block*);
static inline xdc_runtime_knl_Semaphore_Proxy_pend_FxnT xdc_runtime_knl_Semaphore_Proxy_pend_fxnP( void )
{
    return (xdc_runtime_knl_Semaphore_Proxy_pend_FxnT)xdc_runtime_knl_Semaphore_Proxy_pend; 
}

/* post_{FxnT,fxnP} */
typedef xdc_Bool (*xdc_runtime_knl_Semaphore_Proxy_post_FxnT)(void*, xdc_runtime_Error_Block*);
static inline xdc_runtime_knl_Semaphore_Proxy_post_FxnT xdc_runtime_knl_Semaphore_Proxy_post_fxnP( void )
{
    return (xdc_runtime_knl_Semaphore_Proxy_post_FxnT)xdc_runtime_knl_Semaphore_Proxy_post; 
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_knl_ISemaphore_Module xdc_runtime_knl_Semaphore_Proxy_Module_upCast( void )
{
    return (xdc_runtime_knl_ISemaphore_Module)xdc_runtime_knl_Semaphore_Proxy_Proxy__delegate__S();
}

/* Module_to_xdc_runtime_knl_ISemaphore */
#define xdc_runtime_knl_Semaphore_Proxy_Module_to_xdc_runtime_knl_ISemaphore xdc_runtime_knl_Semaphore_Proxy_Module_upCast

/* Handle_upCast */
static inline xdc_runtime_knl_ISemaphore_Handle xdc_runtime_knl_Semaphore_Proxy_Handle_upCast( xdc_runtime_knl_Semaphore_Proxy_Handle i )
{
    return (xdc_runtime_knl_ISemaphore_Handle)i;
}

/* Handle_to_xdc_runtime_knl_ISemaphore */
#define xdc_runtime_knl_Semaphore_Proxy_Handle_to_xdc_runtime_knl_ISemaphore xdc_runtime_knl_Semaphore_Proxy_Handle_upCast

/* Handle_downCast */
static inline xdc_runtime_knl_Semaphore_Proxy_Handle xdc_runtime_knl_Semaphore_Proxy_Handle_downCast( xdc_runtime_knl_ISemaphore_Handle i )
{
    xdc_runtime_knl_ISemaphore_Handle i2 = (xdc_runtime_knl_ISemaphore_Handle)i;
if (xdc_runtime_knl_Semaphore_Proxy_Proxy__abstract__S()) return (xdc_runtime_knl_Semaphore_Proxy_Handle)i;
    return (void*)i2->__fxns == (void*)xdc_runtime_knl_Semaphore_Proxy_Proxy__delegate__S() ? (xdc_runtime_knl_Semaphore_Proxy_Handle)i : 0;
}

/* Handle_from_xdc_runtime_knl_ISemaphore */
#define xdc_runtime_knl_Semaphore_Proxy_Handle_from_xdc_runtime_knl_ISemaphore xdc_runtime_knl_Semaphore_Proxy_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdc_runtime_knl_Semaphore_Proxy_Module_startupDone() xdc_runtime_knl_Semaphore_Proxy_Module__startupDone__S()

/* Object_heap */
#define xdc_runtime_knl_Semaphore_Proxy_Object_heap() xdc_runtime_knl_Semaphore_Proxy_Object__heap__C

/* Module_heap */
#define xdc_runtime_knl_Semaphore_Proxy_Module_heap() xdc_runtime_knl_Semaphore_Proxy_Object__heap__C

/* Module_id */
static inline CT__xdc_runtime_knl_Semaphore_Proxy_Module__id xdc_runtime_knl_Semaphore_Proxy_Module_id( void ) 
{
    return xdc_runtime_knl_Semaphore_Proxy_Module__id__C;
}

/* Proxy_abstract */
#define xdc_runtime_knl_Semaphore_Proxy_Proxy_abstract() xdc_runtime_knl_Semaphore_Proxy_Proxy__abstract__S()

/* Proxy_delegate */
#define xdc_runtime_knl_Semaphore_Proxy_Proxy_delegate() ((xdc_runtime_knl_ISemaphore_Module)xdc_runtime_knl_Semaphore_Proxy_Proxy__delegate__S())

/* Params_init */
static inline void xdc_runtime_knl_Semaphore_Proxy_Params_init( xdc_runtime_knl_Semaphore_Proxy_Params* prms ) 
{
    if (prms) {
        xdc_runtime_knl_Semaphore_Proxy_Params__init__S(prms, 0, sizeof(xdc_runtime_knl_Semaphore_Proxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void xdc_runtime_knl_Semaphore_Proxy_Params_copy( xdc_runtime_knl_Semaphore_Proxy_Params* dst, const xdc_runtime_knl_Semaphore_Proxy_Params* src ) 
{
    if (dst) {
        xdc_runtime_knl_Semaphore_Proxy_Params__init__S(dst, (xdc_Ptr)src, sizeof(xdc_runtime_knl_Semaphore_Proxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* create */
static inline xdc_runtime_knl_Semaphore_Proxy_Handle xdc_runtime_knl_Semaphore_Proxy_create( const xdc_runtime_knl_Semaphore_Proxy_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    return (xdc_runtime_knl_Semaphore_Proxy_Handle)xdc_runtime_knl_Semaphore_Proxy_Object__create__S(0, 0, 0, (const xdc_UChar*)__prms, sizeof(xdc_runtime_knl_Semaphore_Proxy_Params), __eb);
}

/* delete */
static inline void xdc_runtime_knl_Semaphore_Proxy_delete( xdc_runtime_knl_Semaphore_Proxy_Handle* instp )
{
    xdc_runtime_knl_Semaphore_Proxy_Object__delete__S(instp);
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_knl_Semaphore_Proxy__top__
#undef __nested__
#endif

#endif /* xdc_runtime_knl_Semaphore_Proxy__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_knl_Semaphore_Proxy__nolocalnames)

/* module prefix */
#define Semaphore_Proxy_Instance xdc_runtime_knl_Semaphore_Proxy_Instance
#define Semaphore_Proxy_Handle xdc_runtime_knl_Semaphore_Proxy_Handle
#define Semaphore_Proxy_Module xdc_runtime_knl_Semaphore_Proxy_Module
#define Semaphore_Proxy_Object xdc_runtime_knl_Semaphore_Proxy_Object
#define Semaphore_Proxy_Struct xdc_runtime_knl_Semaphore_Proxy_Struct
#define Semaphore_Proxy_PendStatus xdc_runtime_knl_Semaphore_Proxy_PendStatus
#define Semaphore_Proxy_FOREVER xdc_runtime_knl_Semaphore_Proxy_FOREVER
#define Semaphore_Proxy_Mode xdc_runtime_knl_Semaphore_Proxy_Mode
#define Semaphore_Proxy_Params xdc_runtime_knl_Semaphore_Proxy_Params
#define Semaphore_Proxy_pend xdc_runtime_knl_Semaphore_Proxy_pend
#define Semaphore_Proxy_pend_fxnP xdc_runtime_knl_Semaphore_Proxy_pend_fxnP
#define Semaphore_Proxy_pend_FxnT xdc_runtime_knl_Semaphore_Proxy_pend_FxnT
#define Semaphore_Proxy_post xdc_runtime_knl_Semaphore_Proxy_post
#define Semaphore_Proxy_post_fxnP xdc_runtime_knl_Semaphore_Proxy_post_fxnP
#define Semaphore_Proxy_post_FxnT xdc_runtime_knl_Semaphore_Proxy_post_FxnT
#define Semaphore_Proxy_Module_name xdc_runtime_knl_Semaphore_Proxy_Module_name
#define Semaphore_Proxy_Module_id xdc_runtime_knl_Semaphore_Proxy_Module_id
#define Semaphore_Proxy_Module_startup xdc_runtime_knl_Semaphore_Proxy_Module_startup
#define Semaphore_Proxy_Module_startupDone xdc_runtime_knl_Semaphore_Proxy_Module_startupDone
#define Semaphore_Proxy_Module_hasMask xdc_runtime_knl_Semaphore_Proxy_Module_hasMask
#define Semaphore_Proxy_Module_getMask xdc_runtime_knl_Semaphore_Proxy_Module_getMask
#define Semaphore_Proxy_Module_setMask xdc_runtime_knl_Semaphore_Proxy_Module_setMask
#define Semaphore_Proxy_Object_heap xdc_runtime_knl_Semaphore_Proxy_Object_heap
#define Semaphore_Proxy_Module_heap xdc_runtime_knl_Semaphore_Proxy_Module_heap
#define Semaphore_Proxy_construct xdc_runtime_knl_Semaphore_Proxy_construct
#define Semaphore_Proxy_create xdc_runtime_knl_Semaphore_Proxy_create
#define Semaphore_Proxy_handle xdc_runtime_knl_Semaphore_Proxy_handle
#define Semaphore_Proxy_struct xdc_runtime_knl_Semaphore_Proxy_struct
#define Semaphore_Proxy_Handle_label xdc_runtime_knl_Semaphore_Proxy_Handle_label
#define Semaphore_Proxy_Handle_name xdc_runtime_knl_Semaphore_Proxy_Handle_name
#define Semaphore_Proxy_Instance_init xdc_runtime_knl_Semaphore_Proxy_Instance_init
#define Semaphore_Proxy_Object_count xdc_runtime_knl_Semaphore_Proxy_Object_count
#define Semaphore_Proxy_Object_get xdc_runtime_knl_Semaphore_Proxy_Object_get
#define Semaphore_Proxy_Object_first xdc_runtime_knl_Semaphore_Proxy_Object_first
#define Semaphore_Proxy_Object_next xdc_runtime_knl_Semaphore_Proxy_Object_next
#define Semaphore_Proxy_Object_sizeof xdc_runtime_knl_Semaphore_Proxy_Object_sizeof
#define Semaphore_Proxy_Params_copy xdc_runtime_knl_Semaphore_Proxy_Params_copy
#define Semaphore_Proxy_Params_init xdc_runtime_knl_Semaphore_Proxy_Params_init
#define Semaphore_Proxy_Instance_State xdc_runtime_knl_Semaphore_Proxy_Instance_State
#define Semaphore_Proxy_Proxy_abstract xdc_runtime_knl_Semaphore_Proxy_Proxy_abstract
#define Semaphore_Proxy_Proxy_delegate xdc_runtime_knl_Semaphore_Proxy_Proxy_delegate
#define Semaphore_Proxy_delete xdc_runtime_knl_Semaphore_Proxy_delete
#define Semaphore_Proxy_destruct xdc_runtime_knl_Semaphore_Proxy_destruct
#define Semaphore_Proxy_Module_upCast xdc_runtime_knl_Semaphore_Proxy_Module_upCast
#define Semaphore_Proxy_Module_to_xdc_runtime_knl_ISemaphore xdc_runtime_knl_Semaphore_Proxy_Module_to_xdc_runtime_knl_ISemaphore
#define Semaphore_Proxy_Handle_upCast xdc_runtime_knl_Semaphore_Proxy_Handle_upCast
#define Semaphore_Proxy_Handle_to_xdc_runtime_knl_ISemaphore xdc_runtime_knl_Semaphore_Proxy_Handle_to_xdc_runtime_knl_ISemaphore
#define Semaphore_Proxy_Handle_downCast xdc_runtime_knl_Semaphore_Proxy_Handle_downCast
#define Semaphore_Proxy_Handle_from_xdc_runtime_knl_ISemaphore xdc_runtime_knl_Semaphore_Proxy_Handle_from_xdc_runtime_knl_ISemaphore

#endif
