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
 *     CREATE ARGS
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

#ifndef xdc_runtime_knl_SemProcess__include
#define xdc_runtime_knl_SemProcess__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_knl_SemProcess__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_knl_SemProcess___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <xdc/runtime/knl/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/knl/ISemaphore.h>
#include <xdc/runtime/knl/package/SemProcess_Proxy.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* PendStatus */
typedef xdc_runtime_knl_ISemaphore_PendStatus xdc_runtime_knl_SemProcess_PendStatus;

/* FOREVER */
#define xdc_runtime_knl_SemProcess_FOREVER (~(0))

/* Mode */
typedef xdc_runtime_knl_ISemaphore_Mode xdc_runtime_knl_SemProcess_Mode;

/* PendStatus_ERROR */
#define xdc_runtime_knl_SemProcess_PendStatus_ERROR xdc_runtime_knl_ISemaphore_PendStatus_ERROR

/* PendStatus_TIMEOUT */
#define xdc_runtime_knl_SemProcess_PendStatus_TIMEOUT xdc_runtime_knl_ISemaphore_PendStatus_TIMEOUT

/* PendStatus_SUCCESS */
#define xdc_runtime_knl_SemProcess_PendStatus_SUCCESS xdc_runtime_knl_ISemaphore_PendStatus_SUCCESS

/* Mode_COUNTING */
#define xdc_runtime_knl_SemProcess_Mode_COUNTING xdc_runtime_knl_ISemaphore_Mode_COUNTING

/* Mode_BINARY */
#define xdc_runtime_knl_SemProcess_Mode_BINARY xdc_runtime_knl_ISemaphore_Mode_BINARY


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct xdc_runtime_knl_SemProcess_Args__create {
    xdc_Int count;
    xdc_UInt32 key;
} xdc_runtime_knl_SemProcess_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_knl_SemProcess_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Module__diagsEnabled xdc_runtime_knl_SemProcess_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_knl_SemProcess_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Module__diagsIncluded xdc_runtime_knl_SemProcess_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_knl_SemProcess_Module__diagsMask;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Module__diagsMask xdc_runtime_knl_SemProcess_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_knl_SemProcess_Module__gateObj;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Module__gateObj xdc_runtime_knl_SemProcess_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_knl_SemProcess_Module__gatePrms;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Module__gatePrms xdc_runtime_knl_SemProcess_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_knl_SemProcess_Module__id;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Module__id xdc_runtime_knl_SemProcess_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_knl_SemProcess_Module__loggerDefined;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Module__loggerDefined xdc_runtime_knl_SemProcess_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_knl_SemProcess_Module__loggerObj;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Module__loggerObj xdc_runtime_knl_SemProcess_Module__loggerObj__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_knl_SemProcess_Module__loggerFxn4;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Module__loggerFxn4 xdc_runtime_knl_SemProcess_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_knl_SemProcess_Module__loggerFxn8;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Module__loggerFxn8 xdc_runtime_knl_SemProcess_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_knl_SemProcess_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Module__startupDoneFxn xdc_runtime_knl_SemProcess_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_knl_SemProcess_Object__count;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Object__count xdc_runtime_knl_SemProcess_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_knl_SemProcess_Object__heap;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Object__heap xdc_runtime_knl_SemProcess_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_knl_SemProcess_Object__sizeof;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Object__sizeof xdc_runtime_knl_SemProcess_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_knl_SemProcess_Object__table;
__extern __FAR__ const CT__xdc_runtime_knl_SemProcess_Object__table xdc_runtime_knl_SemProcess_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_knl_SemProcess_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    xdc_runtime_knl_ISemaphore_Mode mode;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct xdc_runtime_knl_SemProcess_Struct {
    const xdc_runtime_knl_SemProcess_Fxns__* __fxns;
    xdc_runtime_knl_SemProcess_Proxy_Handle __f0;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_knl_SemProcess_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*pend)(xdc_runtime_knl_SemProcess_Handle, xdc_UInt, xdc_runtime_Error_Block*);
    xdc_Bool (*post)(xdc_runtime_knl_SemProcess_Handle, xdc_runtime_Error_Block*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const xdc_runtime_knl_SemProcess_Fxns__ xdc_runtime_knl_SemProcess_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdc_runtime_knl_SemProcess_Module_startup( state ) -1

/* Instance_init__F */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Instance_init__F, "xdc_runtime_knl_SemProcess_Instance_init")
__extern int xdc_runtime_knl_SemProcess_Instance_init__F( xdc_runtime_knl_SemProcess_Object*, xdc_Int count, xdc_UInt32 key, const xdc_runtime_knl_SemProcess_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__F */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Instance_finalize__F, "xdc_runtime_knl_SemProcess_Instance_finalize")
__extern void xdc_runtime_knl_SemProcess_Instance_finalize__F( xdc_runtime_knl_SemProcess_Object* , int );

/* Instance_init__R */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Instance_init__R, "xdc_runtime_knl_SemProcess_Instance_init")
__extern int xdc_runtime_knl_SemProcess_Instance_init__R( xdc_runtime_knl_SemProcess_Object*, xdc_Int count, xdc_UInt32 key, const xdc_runtime_knl_SemProcess_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__R */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Instance_finalize__R, "xdc_runtime_knl_SemProcess_Instance_finalize")
__extern void xdc_runtime_knl_SemProcess_Instance_finalize__R( xdc_runtime_knl_SemProcess_Object* , int );

/* Handle__label__S */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Handle__label__S, "xdc_runtime_knl_SemProcess_Handle__label")
__extern xdc_runtime_Types_Label* xdc_runtime_knl_SemProcess_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Module__startupDone__S, "xdc_runtime_knl_SemProcess_Module__startupDone")
__extern xdc_Bool xdc_runtime_knl_SemProcess_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Object__create__S, "xdc_runtime_knl_SemProcess_Object__create")
__extern xdc_Ptr xdc_runtime_knl_SemProcess_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Object__delete__S, "xdc_runtime_knl_SemProcess_Object__delete")
__extern xdc_Void xdc_runtime_knl_SemProcess_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Object__destruct__S, "xdc_runtime_knl_SemProcess_Object__destruct")
__extern xdc_Void xdc_runtime_knl_SemProcess_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Object__get__S, "xdc_runtime_knl_SemProcess_Object__get")
__extern xdc_Ptr xdc_runtime_knl_SemProcess_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Object__first__S, "xdc_runtime_knl_SemProcess_Object__first")
__extern xdc_Ptr xdc_runtime_knl_SemProcess_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Object__next__S, "xdc_runtime_knl_SemProcess_Object__next")
__extern xdc_Ptr xdc_runtime_knl_SemProcess_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Params__init__S, "xdc_runtime_knl_SemProcess_Params__init")
__extern xdc_Void xdc_runtime_knl_SemProcess_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Proxy__abstract__S, "xdc_runtime_knl_SemProcess_Proxy__abstract")
__extern xdc_Bool xdc_runtime_knl_SemProcess_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(xdc_runtime_knl_SemProcess_Proxy__delegate__S, "xdc_runtime_knl_SemProcess_Proxy__delegate")
__extern xdc_Ptr xdc_runtime_knl_SemProcess_Proxy__delegate__S( void );

/* pend__E */
#define xdc_runtime_knl_SemProcess_pend xdc_runtime_knl_SemProcess_pend__E
xdc__CODESECT(xdc_runtime_knl_SemProcess_pend__E, "xdc_runtime_knl_SemProcess_pend")
__extern xdc_Int xdc_runtime_knl_SemProcess_pend__E( xdc_runtime_knl_SemProcess_Handle __inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb );
xdc__CODESECT(xdc_runtime_knl_SemProcess_pend__F, "xdc_runtime_knl_SemProcess_pend")
__extern xdc_Int xdc_runtime_knl_SemProcess_pend__F( xdc_runtime_knl_SemProcess_Object* __inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb );
__extern xdc_Int xdc_runtime_knl_SemProcess_pend__R( xdc_runtime_knl_SemProcess_Handle __inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb );

/* post__E */
#define xdc_runtime_knl_SemProcess_post xdc_runtime_knl_SemProcess_post__E
xdc__CODESECT(xdc_runtime_knl_SemProcess_post__E, "xdc_runtime_knl_SemProcess_post")
__extern xdc_Bool xdc_runtime_knl_SemProcess_post__E( xdc_runtime_knl_SemProcess_Handle __inst, xdc_runtime_Error_Block* eb );
xdc__CODESECT(xdc_runtime_knl_SemProcess_post__F, "xdc_runtime_knl_SemProcess_post")
__extern xdc_Bool xdc_runtime_knl_SemProcess_post__F( xdc_runtime_knl_SemProcess_Object* __inst, xdc_runtime_Error_Block* eb );
__extern xdc_Bool xdc_runtime_knl_SemProcess_post__R( xdc_runtime_knl_SemProcess_Handle __inst, xdc_runtime_Error_Block* eb );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* pend_{FxnT,fxnP} */
typedef xdc_Int (*xdc_runtime_knl_SemProcess_pend_FxnT)(void*, xdc_UInt, xdc_runtime_Error_Block*);
static inline xdc_runtime_knl_SemProcess_pend_FxnT xdc_runtime_knl_SemProcess_pend_fxnP( void )
{
    return (xdc_runtime_knl_SemProcess_pend_FxnT)xdc_runtime_knl_SemProcess_pend; 
}

/* post_{FxnT,fxnP} */
typedef xdc_Bool (*xdc_runtime_knl_SemProcess_post_FxnT)(void*, xdc_runtime_Error_Block*);
static inline xdc_runtime_knl_SemProcess_post_FxnT xdc_runtime_knl_SemProcess_post_fxnP( void )
{
    return (xdc_runtime_knl_SemProcess_post_FxnT)xdc_runtime_knl_SemProcess_post; 
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_knl_ISemaphore_Module xdc_runtime_knl_SemProcess_Module_upCast( void )
{
    return (xdc_runtime_knl_ISemaphore_Module)&xdc_runtime_knl_SemProcess_Module__FXNS__C;
}

/* Module_to_xdc_runtime_knl_ISemaphore */
#define xdc_runtime_knl_SemProcess_Module_to_xdc_runtime_knl_ISemaphore xdc_runtime_knl_SemProcess_Module_upCast

/* Handle_upCast */
static inline xdc_runtime_knl_ISemaphore_Handle xdc_runtime_knl_SemProcess_Handle_upCast( xdc_runtime_knl_SemProcess_Handle i )
{
    return (xdc_runtime_knl_ISemaphore_Handle)i;
}

/* Handle_to_xdc_runtime_knl_ISemaphore */
#define xdc_runtime_knl_SemProcess_Handle_to_xdc_runtime_knl_ISemaphore xdc_runtime_knl_SemProcess_Handle_upCast

/* Handle_downCast */
static inline xdc_runtime_knl_SemProcess_Handle xdc_runtime_knl_SemProcess_Handle_downCast( xdc_runtime_knl_ISemaphore_Handle i )
{
    xdc_runtime_knl_ISemaphore_Handle i2 = (xdc_runtime_knl_ISemaphore_Handle)i;
    return (void*)i2->__fxns == (void*)&xdc_runtime_knl_SemProcess_Module__FXNS__C ? (xdc_runtime_knl_SemProcess_Handle)i : 0;
}

/* Handle_from_xdc_runtime_knl_ISemaphore */
#define xdc_runtime_knl_SemProcess_Handle_from_xdc_runtime_knl_ISemaphore xdc_runtime_knl_SemProcess_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdc_runtime_knl_SemProcess_Module_startupDone() xdc_runtime_knl_SemProcess_Module__startupDone__S()

/* Object_heap */
#define xdc_runtime_knl_SemProcess_Object_heap() xdc_runtime_knl_SemProcess_Object__heap__C

/* Module_heap */
#define xdc_runtime_knl_SemProcess_Module_heap() xdc_runtime_knl_SemProcess_Object__heap__C

/* Module_id */
static inline CT__xdc_runtime_knl_SemProcess_Module__id xdc_runtime_knl_SemProcess_Module_id( void ) 
{
    return xdc_runtime_knl_SemProcess_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_knl_SemProcess_Module_hasMask( void ) 
{
    return xdc_runtime_knl_SemProcess_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_knl_SemProcess_Module_getMask( void ) 
{
    return xdc_runtime_knl_SemProcess_Module__diagsMask__C != NULL ? *xdc_runtime_knl_SemProcess_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void xdc_runtime_knl_SemProcess_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_knl_SemProcess_Module__diagsMask__C != NULL) *xdc_runtime_knl_SemProcess_Module__diagsMask__C = mask;
}

/* Params_init */
static inline void xdc_runtime_knl_SemProcess_Params_init( xdc_runtime_knl_SemProcess_Params* prms ) 
{
    if (prms) {
        xdc_runtime_knl_SemProcess_Params__init__S(prms, 0, sizeof(xdc_runtime_knl_SemProcess_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void xdc_runtime_knl_SemProcess_Params_copy( xdc_runtime_knl_SemProcess_Params* dst, const xdc_runtime_knl_SemProcess_Params* src ) 
{
    if (dst) {
        xdc_runtime_knl_SemProcess_Params__init__S(dst, (xdc_Ptr)src, sizeof(xdc_runtime_knl_SemProcess_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define xdc_runtime_knl_SemProcess_Object_count() xdc_runtime_knl_SemProcess_Object__count__C

/* Object_sizeof */
#define xdc_runtime_knl_SemProcess_Object_sizeof() xdc_runtime_knl_SemProcess_Object__sizeof__C

/* Object_get */
static inline xdc_runtime_knl_SemProcess_Handle xdc_runtime_knl_SemProcess_Object_get( xdc_runtime_knl_SemProcess_Instance_State* oarr, int i ) 
{
    return (xdc_runtime_knl_SemProcess_Handle)xdc_runtime_knl_SemProcess_Object__get__S(oarr, i);
}

/* Object_first */
static inline xdc_runtime_knl_SemProcess_Handle xdc_runtime_knl_SemProcess_Object_first( void )
{
    return (xdc_runtime_knl_SemProcess_Handle)xdc_runtime_knl_SemProcess_Object__first__S();
}

/* Object_next */
static inline xdc_runtime_knl_SemProcess_Handle xdc_runtime_knl_SemProcess_Object_next( xdc_runtime_knl_SemProcess_Object* obj )
{
    return (xdc_runtime_knl_SemProcess_Handle)xdc_runtime_knl_SemProcess_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label* xdc_runtime_knl_SemProcess_Handle_label( xdc_runtime_knl_SemProcess_Handle inst, xdc_runtime_Types_Label* lab )
{
    return xdc_runtime_knl_SemProcess_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline String xdc_runtime_knl_SemProcess_Handle_name( xdc_runtime_knl_SemProcess_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return xdc_runtime_knl_SemProcess_Handle__label__S(inst, &lab)->iname;
}

/* create */
static inline xdc_runtime_knl_SemProcess_Handle xdc_runtime_knl_SemProcess_create( xdc_Int count, xdc_UInt32 key, const xdc_runtime_knl_SemProcess_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    xdc_runtime_knl_SemProcess_Args__create __args;
    __args.count = count;
    __args.key = key;
    return (xdc_runtime_knl_SemProcess_Handle)xdc_runtime_knl_SemProcess_Object__create__S(0, 0, &__args, (const xdc_UChar*)__prms, sizeof(xdc_runtime_knl_SemProcess_Params), __eb);
}

/* construct */
static inline void xdc_runtime_knl_SemProcess_construct( xdc_runtime_knl_SemProcess_Struct* __obj, xdc_Int count, xdc_UInt32 key, const xdc_runtime_knl_SemProcess_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    xdc_runtime_knl_SemProcess_Args__create __args;
    __args.count = count;
    __args.key = key;
    xdc_runtime_knl_SemProcess_Object__create__S(__obj, sizeof (xdc_runtime_knl_SemProcess_Struct), &__args, (const xdc_UChar*)__prms, sizeof(xdc_runtime_knl_SemProcess_Params), __eb);
}

/* delete */
static inline void xdc_runtime_knl_SemProcess_delete( xdc_runtime_knl_SemProcess_Handle* instp )
{
    xdc_runtime_knl_SemProcess_Object__delete__S(instp);
}

/* destruct */
static inline void xdc_runtime_knl_SemProcess_destruct( xdc_runtime_knl_SemProcess_Struct* obj )
{
    xdc_runtime_knl_SemProcess_Object__destruct__S(obj);
}

/* handle */
static inline xdc_runtime_knl_SemProcess_Handle xdc_runtime_knl_SemProcess_handle( xdc_runtime_knl_SemProcess_Struct* str )
{
    return (xdc_runtime_knl_SemProcess_Handle)str;
}

/* struct */
static inline xdc_runtime_knl_SemProcess_Struct* xdc_runtime_knl_SemProcess_struct( xdc_runtime_knl_SemProcess_Handle inst )
{
    return (xdc_runtime_knl_SemProcess_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_knl_SemProcess__top__
#undef __nested__
#endif

#endif /* xdc_runtime_knl_SemProcess__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdc_runtime_knl_SemProcess__internalaccess))

#ifndef xdc_runtime_knl_SemProcess__include_state
#define xdc_runtime_knl_SemProcess__include_state

/* Object */
struct xdc_runtime_knl_SemProcess_Object {
    const xdc_runtime_knl_SemProcess_Fxns__* __fxns;
    xdc_runtime_knl_SemProcess_Proxy_Handle proxyHandle;
};

#endif /* xdc_runtime_knl_SemProcess__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_knl_SemProcess__nolocalnames)

/* module prefix */
#define SemProcess_Instance xdc_runtime_knl_SemProcess_Instance
#define SemProcess_Handle xdc_runtime_knl_SemProcess_Handle
#define SemProcess_Module xdc_runtime_knl_SemProcess_Module
#define SemProcess_Object xdc_runtime_knl_SemProcess_Object
#define SemProcess_Struct xdc_runtime_knl_SemProcess_Struct
#define SemProcess_PendStatus xdc_runtime_knl_SemProcess_PendStatus
#define SemProcess_FOREVER xdc_runtime_knl_SemProcess_FOREVER
#define SemProcess_Mode xdc_runtime_knl_SemProcess_Mode
#define SemProcess_Instance_State xdc_runtime_knl_SemProcess_Instance_State
#define SemProcess_PendStatus_ERROR xdc_runtime_knl_SemProcess_PendStatus_ERROR
#define SemProcess_PendStatus_TIMEOUT xdc_runtime_knl_SemProcess_PendStatus_TIMEOUT
#define SemProcess_PendStatus_SUCCESS xdc_runtime_knl_SemProcess_PendStatus_SUCCESS
#define SemProcess_Mode_COUNTING xdc_runtime_knl_SemProcess_Mode_COUNTING
#define SemProcess_Mode_BINARY xdc_runtime_knl_SemProcess_Mode_BINARY
#define SemProcess_Params xdc_runtime_knl_SemProcess_Params
#define SemProcess_pend xdc_runtime_knl_SemProcess_pend
#define SemProcess_pend_fxnP xdc_runtime_knl_SemProcess_pend_fxnP
#define SemProcess_pend_FxnT xdc_runtime_knl_SemProcess_pend_FxnT
#define SemProcess_post xdc_runtime_knl_SemProcess_post
#define SemProcess_post_fxnP xdc_runtime_knl_SemProcess_post_fxnP
#define SemProcess_post_FxnT xdc_runtime_knl_SemProcess_post_FxnT
#define SemProcess_Module_name xdc_runtime_knl_SemProcess_Module_name
#define SemProcess_Module_id xdc_runtime_knl_SemProcess_Module_id
#define SemProcess_Module_startup xdc_runtime_knl_SemProcess_Module_startup
#define SemProcess_Module_startupDone xdc_runtime_knl_SemProcess_Module_startupDone
#define SemProcess_Module_hasMask xdc_runtime_knl_SemProcess_Module_hasMask
#define SemProcess_Module_getMask xdc_runtime_knl_SemProcess_Module_getMask
#define SemProcess_Module_setMask xdc_runtime_knl_SemProcess_Module_setMask
#define SemProcess_Object_heap xdc_runtime_knl_SemProcess_Object_heap
#define SemProcess_Module_heap xdc_runtime_knl_SemProcess_Module_heap
#define SemProcess_construct xdc_runtime_knl_SemProcess_construct
#define SemProcess_create xdc_runtime_knl_SemProcess_create
#define SemProcess_handle xdc_runtime_knl_SemProcess_handle
#define SemProcess_struct xdc_runtime_knl_SemProcess_struct
#define SemProcess_Handle_label xdc_runtime_knl_SemProcess_Handle_label
#define SemProcess_Handle_name xdc_runtime_knl_SemProcess_Handle_name
#define SemProcess_Instance_init xdc_runtime_knl_SemProcess_Instance_init
#define SemProcess_Object_count xdc_runtime_knl_SemProcess_Object_count
#define SemProcess_Object_get xdc_runtime_knl_SemProcess_Object_get
#define SemProcess_Object_first xdc_runtime_knl_SemProcess_Object_first
#define SemProcess_Object_next xdc_runtime_knl_SemProcess_Object_next
#define SemProcess_Object_sizeof xdc_runtime_knl_SemProcess_Object_sizeof
#define SemProcess_Params_copy xdc_runtime_knl_SemProcess_Params_copy
#define SemProcess_Params_init xdc_runtime_knl_SemProcess_Params_init
#define SemProcess_Instance_finalize xdc_runtime_knl_SemProcess_Instance_finalize
#define SemProcess_delete xdc_runtime_knl_SemProcess_delete
#define SemProcess_destruct xdc_runtime_knl_SemProcess_destruct
#define SemProcess_Module_upCast xdc_runtime_knl_SemProcess_Module_upCast
#define SemProcess_Module_to_xdc_runtime_knl_ISemaphore xdc_runtime_knl_SemProcess_Module_to_xdc_runtime_knl_ISemaphore
#define SemProcess_Handle_upCast xdc_runtime_knl_SemProcess_Handle_upCast
#define SemProcess_Handle_to_xdc_runtime_knl_ISemaphore xdc_runtime_knl_SemProcess_Handle_to_xdc_runtime_knl_ISemaphore
#define SemProcess_Handle_downCast xdc_runtime_knl_SemProcess_Handle_downCast
#define SemProcess_Handle_from_xdc_runtime_knl_ISemaphore xdc_runtime_knl_SemProcess_Handle_from_xdc_runtime_knl_ISemaphore

/* proxies */
#include <xdc/runtime/knl/package/SemProcess_Proxy.h>

#endif
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,46; 2-22-2010 10:33:52; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

