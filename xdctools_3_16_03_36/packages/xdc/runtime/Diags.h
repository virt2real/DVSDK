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

#ifndef xdc_runtime_Diags__include
#define xdc_runtime_Diags__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_Diags__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_Diags___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Diags__prologue.h>
#include <xdc/runtime/package/package.defs.h>

#include <xdc/runtime/Types.h>
#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Mask */
typedef xdc_Bits16 xdc_runtime_Diags_Mask;

/* ENTRY */
#define xdc_runtime_Diags_ENTRY (0x0001)

/* EXIT */
#define xdc_runtime_Diags_EXIT (0x0002)

/* LIFECYCLE */
#define xdc_runtime_Diags_LIFECYCLE (0x0004)

/* INTERNAL */
#define xdc_runtime_Diags_INTERNAL (0x0008)

/* ASSERT */
#define xdc_runtime_Diags_ASSERT (0x0010)

/* USER1 */
#define xdc_runtime_Diags_USER1 (0x0100)

/* USER2 */
#define xdc_runtime_Diags_USER2 (0x0200)

/* USER3 */
#define xdc_runtime_Diags_USER3 (0x0400)

/* USER4 */
#define xdc_runtime_Diags_USER4 (0x0800)

/* USER5 */
#define xdc_runtime_Diags_USER5 (0x1000)

/* USER6 */
#define xdc_runtime_Diags_USER6 (0x2000)

/* USER7 */
#define xdc_runtime_Diags_USER7 (0x4000)

/* USER8 */
#define xdc_runtime_Diags_USER8 (0x8000)

/* ALL */
#define xdc_runtime_Diags_ALL (0xFFFF)


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* DictElem */
struct xdc_runtime_Diags_DictElem {
    xdc_runtime_Types_ModuleId modId;
    xdc_Bits16* maskAddr;
};


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Diags_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_runtime_Diags_Module__diagsEnabled xdc_runtime_Diags_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Diags_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_runtime_Diags_Module__diagsIncluded xdc_runtime_Diags_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Diags_Module__diagsMask;
__extern __FAR__ const CT__xdc_runtime_Diags_Module__diagsMask xdc_runtime_Diags_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Diags_Module__gateObj;
__extern __FAR__ const CT__xdc_runtime_Diags_Module__gateObj xdc_runtime_Diags_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Diags_Module__gatePrms;
__extern __FAR__ const CT__xdc_runtime_Diags_Module__gatePrms xdc_runtime_Diags_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Diags_Module__id;
__extern __FAR__ const CT__xdc_runtime_Diags_Module__id xdc_runtime_Diags_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Diags_Module__loggerDefined;
__extern __FAR__ const CT__xdc_runtime_Diags_Module__loggerDefined xdc_runtime_Diags_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Diags_Module__loggerObj;
__extern __FAR__ const CT__xdc_runtime_Diags_Module__loggerObj xdc_runtime_Diags_Module__loggerObj__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Diags_Module__loggerFxn4;
__extern __FAR__ const CT__xdc_runtime_Diags_Module__loggerFxn4 xdc_runtime_Diags_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Diags_Module__loggerFxn8;
__extern __FAR__ const CT__xdc_runtime_Diags_Module__loggerFxn8 xdc_runtime_Diags_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Diags_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__xdc_runtime_Diags_Module__startupDoneFxn xdc_runtime_Diags_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Diags_Object__count;
__extern __FAR__ const CT__xdc_runtime_Diags_Object__count xdc_runtime_Diags_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Diags_Object__heap;
__extern __FAR__ const CT__xdc_runtime_Diags_Object__heap xdc_runtime_Diags_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Diags_Object__sizeof;
__extern __FAR__ const CT__xdc_runtime_Diags_Object__sizeof xdc_runtime_Diags_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Diags_Object__table;
__extern __FAR__ const CT__xdc_runtime_Diags_Object__table xdc_runtime_Diags_Object__table__C;

/* setMaskEnabled */
#define xdc_runtime_Diags_setMaskEnabled (xdc_runtime_Diags_setMaskEnabled__C)
typedef xdc_Bool CT__xdc_runtime_Diags_setMaskEnabled;
__extern __FAR__ const CT__xdc_runtime_Diags_setMaskEnabled xdc_runtime_Diags_setMaskEnabled__C;

/* dictBase */
#define xdc_runtime_Diags_dictBase (xdc_runtime_Diags_dictBase__C)
typedef xdc_runtime_Diags_DictElem* CT__xdc_runtime_Diags_dictBase;
__extern __FAR__ const CT__xdc_runtime_Diags_dictBase xdc_runtime_Diags_dictBase__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdc_runtime_Diags_Module_startup( state ) -1

/* Handle__label__S */
xdc__CODESECT(xdc_runtime_Diags_Handle__label__S, "xdc_runtime_Diags_Handle__label")
__extern xdc_runtime_Types_Label* xdc_runtime_Diags_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */
xdc__CODESECT(xdc_runtime_Diags_Module__startupDone__S, "xdc_runtime_Diags_Module__startupDone")
__extern xdc_Bool xdc_runtime_Diags_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(xdc_runtime_Diags_Object__create__S, "xdc_runtime_Diags_Object__create")
__extern xdc_Ptr xdc_runtime_Diags_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */
xdc__CODESECT(xdc_runtime_Diags_Object__delete__S, "xdc_runtime_Diags_Object__delete")
__extern xdc_Void xdc_runtime_Diags_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */
xdc__CODESECT(xdc_runtime_Diags_Object__destruct__S, "xdc_runtime_Diags_Object__destruct")
__extern xdc_Void xdc_runtime_Diags_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(xdc_runtime_Diags_Object__get__S, "xdc_runtime_Diags_Object__get")
__extern xdc_Ptr xdc_runtime_Diags_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(xdc_runtime_Diags_Object__first__S, "xdc_runtime_Diags_Object__first")
__extern xdc_Ptr xdc_runtime_Diags_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(xdc_runtime_Diags_Object__next__S, "xdc_runtime_Diags_Object__next")
__extern xdc_Ptr xdc_runtime_Diags_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(xdc_runtime_Diags_Params__init__S, "xdc_runtime_Diags_Params__init")
__extern xdc_Void xdc_runtime_Diags_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(xdc_runtime_Diags_Proxy__abstract__S, "xdc_runtime_Diags_Proxy__abstract")
__extern xdc_Bool xdc_runtime_Diags_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(xdc_runtime_Diags_Proxy__delegate__S, "xdc_runtime_Diags_Proxy__delegate")
__extern xdc_Ptr xdc_runtime_Diags_Proxy__delegate__S( void );

/* setMask__E */
#define xdc_runtime_Diags_setMask xdc_runtime_Diags_setMask__E
xdc__CODESECT(xdc_runtime_Diags_setMask__E, "xdc_runtime_Diags_setMask")
__extern xdc_Void xdc_runtime_Diags_setMask__E( xdc_String control );
xdc__CODESECT(xdc_runtime_Diags_setMask__F, "xdc_runtime_Diags_setMask")
__extern xdc_Void xdc_runtime_Diags_setMask__F( xdc_String control );
__extern xdc_Void xdc_runtime_Diags_setMask__R( xdc_String control );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdc_runtime_Diags_Module_startupDone() xdc_runtime_Diags_Module__startupDone__S()

/* Object_heap */
#define xdc_runtime_Diags_Object_heap() xdc_runtime_Diags_Object__heap__C

/* Module_heap */
#define xdc_runtime_Diags_Module_heap() xdc_runtime_Diags_Object__heap__C

/* Module_id */
static inline CT__xdc_runtime_Diags_Module__id xdc_runtime_Diags_Module_id( void ) 
{
    return xdc_runtime_Diags_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_Diags_Module_hasMask( void ) 
{
    return xdc_runtime_Diags_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_Diags_Module_getMask( void ) 
{
    return xdc_runtime_Diags_Module__diagsMask__C != NULL ? *xdc_runtime_Diags_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void xdc_runtime_Diags_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_Diags_Module__diagsMask__C != NULL) *xdc_runtime_Diags_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#include <xdc/runtime/Diags__epilogue.h>

#ifdef xdc_runtime_Diags__top__
#undef __nested__
#endif

#endif /* xdc_runtime_Diags__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdc_runtime_Diags__internalaccess))

#ifndef xdc_runtime_Diags__include_state
#define xdc_runtime_Diags__include_state


#endif /* xdc_runtime_Diags__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_Diags__nolocalnames)

/* module prefix */
#define Diags_Mask xdc_runtime_Diags_Mask
#define Diags_ENTRY xdc_runtime_Diags_ENTRY
#define Diags_EXIT xdc_runtime_Diags_EXIT
#define Diags_LIFECYCLE xdc_runtime_Diags_LIFECYCLE
#define Diags_INTERNAL xdc_runtime_Diags_INTERNAL
#define Diags_ASSERT xdc_runtime_Diags_ASSERT
#define Diags_USER1 xdc_runtime_Diags_USER1
#define Diags_USER2 xdc_runtime_Diags_USER2
#define Diags_USER3 xdc_runtime_Diags_USER3
#define Diags_USER4 xdc_runtime_Diags_USER4
#define Diags_USER5 xdc_runtime_Diags_USER5
#define Diags_USER6 xdc_runtime_Diags_USER6
#define Diags_USER7 xdc_runtime_Diags_USER7
#define Diags_USER8 xdc_runtime_Diags_USER8
#define Diags_ALL xdc_runtime_Diags_ALL
#define Diags_DictElem xdc_runtime_Diags_DictElem
#define Diags_setMaskEnabled xdc_runtime_Diags_setMaskEnabled
#define Diags_dictBase xdc_runtime_Diags_dictBase
#define Diags_query xdc_runtime_Diags_query
#define Diags_setMask xdc_runtime_Diags_setMask
#define Diags_Module_name xdc_runtime_Diags_Module_name
#define Diags_Module_id xdc_runtime_Diags_Module_id
#define Diags_Module_startup xdc_runtime_Diags_Module_startup
#define Diags_Module_startupDone xdc_runtime_Diags_Module_startupDone
#define Diags_Module_hasMask xdc_runtime_Diags_Module_hasMask
#define Diags_Module_getMask xdc_runtime_Diags_Module_getMask
#define Diags_Module_setMask xdc_runtime_Diags_Module_setMask
#define Diags_Object_heap xdc_runtime_Diags_Object_heap
#define Diags_Module_heap xdc_runtime_Diags_Module_heap

#endif
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:57; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

