/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-u12
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
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

#ifndef xdais_6_26_01_03_Version__include
#define xdais_6_26_01_03_Version__include

#ifndef __nested__
#define __nested__
#define xdais_6_26_01_03_Version__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdais_6_26_01_03_Version___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdais_6_26_01_03/package/package.defs.h>

#include <ti/sdoarch/standards/pkg/IVersion.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* MAJOR */
#define xdais_6_26_01_03_Version_MAJOR (6)

/* MINOR */
#define xdais_6_26_01_03_Version_MINOR (26)

/* PATCH */
#define xdais_6_26_01_03_Version_PATCH (01)

/* WIDTH */
#define xdais_6_26_01_03_Version_WIDTH (2)


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdais_6_26_01_03_Version_Module__diagsEnabled;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Module__diagsEnabled xdais_6_26_01_03_Version_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdais_6_26_01_03_Version_Module__diagsIncluded;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Module__diagsIncluded xdais_6_26_01_03_Version_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdais_6_26_01_03_Version_Module__diagsMask;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Module__diagsMask xdais_6_26_01_03_Version_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdais_6_26_01_03_Version_Module__gateObj;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Module__gateObj xdais_6_26_01_03_Version_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdais_6_26_01_03_Version_Module__gatePrms;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Module__gatePrms xdais_6_26_01_03_Version_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdais_6_26_01_03_Version_Module__id;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Module__id xdais_6_26_01_03_Version_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdais_6_26_01_03_Version_Module__loggerDefined;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Module__loggerDefined xdais_6_26_01_03_Version_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdais_6_26_01_03_Version_Module__loggerObj;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Module__loggerObj xdais_6_26_01_03_Version_Module__loggerObj__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdais_6_26_01_03_Version_Module__loggerFxn4;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Module__loggerFxn4 xdais_6_26_01_03_Version_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdais_6_26_01_03_Version_Module__loggerFxn8;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Module__loggerFxn8 xdais_6_26_01_03_Version_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdais_6_26_01_03_Version_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Module__startupDoneFxn xdais_6_26_01_03_Version_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdais_6_26_01_03_Version_Object__count;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Object__count xdais_6_26_01_03_Version_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdais_6_26_01_03_Version_Object__heap;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Object__heap xdais_6_26_01_03_Version_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdais_6_26_01_03_Version_Object__sizeof;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Object__sizeof xdais_6_26_01_03_Version_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdais_6_26_01_03_Version_Object__table;
__extern __FAR__ const CT__xdais_6_26_01_03_Version_Object__table xdais_6_26_01_03_Version_Object__table__C;


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdais_6_26_01_03_Version_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const xdais_6_26_01_03_Version_Fxns__ xdais_6_26_01_03_Version_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdais_6_26_01_03_Version_Module_startup( state ) -1

/* Handle__label__S */
xdc__CODESECT(xdais_6_26_01_03_Version_Handle__label__S, "xdais_6_26_01_03_Version_Handle__label")
__extern xdc_runtime_Types_Label* xdais_6_26_01_03_Version_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */
xdc__CODESECT(xdais_6_26_01_03_Version_Module__startupDone__S, "xdais_6_26_01_03_Version_Module__startupDone")
__extern xdc_Bool xdais_6_26_01_03_Version_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(xdais_6_26_01_03_Version_Object__create__S, "xdais_6_26_01_03_Version_Object__create")
__extern xdc_Ptr xdais_6_26_01_03_Version_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */
xdc__CODESECT(xdais_6_26_01_03_Version_Object__delete__S, "xdais_6_26_01_03_Version_Object__delete")
__extern xdc_Void xdais_6_26_01_03_Version_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */
xdc__CODESECT(xdais_6_26_01_03_Version_Object__destruct__S, "xdais_6_26_01_03_Version_Object__destruct")
__extern xdc_Void xdais_6_26_01_03_Version_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(xdais_6_26_01_03_Version_Object__get__S, "xdais_6_26_01_03_Version_Object__get")
__extern xdc_Ptr xdais_6_26_01_03_Version_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(xdais_6_26_01_03_Version_Object__first__S, "xdais_6_26_01_03_Version_Object__first")
__extern xdc_Ptr xdais_6_26_01_03_Version_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(xdais_6_26_01_03_Version_Object__next__S, "xdais_6_26_01_03_Version_Object__next")
__extern xdc_Ptr xdais_6_26_01_03_Version_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(xdais_6_26_01_03_Version_Params__init__S, "xdais_6_26_01_03_Version_Params__init")
__extern xdc_Void xdais_6_26_01_03_Version_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(xdais_6_26_01_03_Version_Proxy__abstract__S, "xdais_6_26_01_03_Version_Proxy__abstract")
__extern xdc_Bool xdais_6_26_01_03_Version_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(xdais_6_26_01_03_Version_Proxy__delegate__S, "xdais_6_26_01_03_Version_Proxy__delegate")
__extern xdc_Ptr xdais_6_26_01_03_Version_Proxy__delegate__S( void );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdoarch_standards_pkg_IVersion_Module xdais_6_26_01_03_Version_Module_upCast( void )
{
    return (ti_sdoarch_standards_pkg_IVersion_Module)&xdais_6_26_01_03_Version_Module__FXNS__C;
}

/* Module_to_ti_sdoarch_standards_pkg_IVersion */
#define xdais_6_26_01_03_Version_Module_to_ti_sdoarch_standards_pkg_IVersion xdais_6_26_01_03_Version_Module_upCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdais_6_26_01_03_Version_Module_startupDone() xdais_6_26_01_03_Version_Module__startupDone__S()

/* Object_heap */
#define xdais_6_26_01_03_Version_Object_heap() xdais_6_26_01_03_Version_Object__heap__C

/* Module_heap */
#define xdais_6_26_01_03_Version_Module_heap() xdais_6_26_01_03_Version_Object__heap__C

/* Module_id */
static inline CT__xdais_6_26_01_03_Version_Module__id xdais_6_26_01_03_Version_Module_id( void ) 
{
    return xdais_6_26_01_03_Version_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdais_6_26_01_03_Version_Module_hasMask( void ) 
{
    return xdais_6_26_01_03_Version_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 xdais_6_26_01_03_Version_Module_getMask( void ) 
{
    return xdais_6_26_01_03_Version_Module__diagsMask__C != NULL ? *xdais_6_26_01_03_Version_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void xdais_6_26_01_03_Version_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdais_6_26_01_03_Version_Module__diagsMask__C != NULL) *xdais_6_26_01_03_Version_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdais_6_26_01_03_Version__top__
#undef __nested__
#endif

#endif /* xdais_6_26_01_03_Version__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdais_6_26_01_03_Version__internalaccess))

#ifndef xdais_6_26_01_03_Version__include_state
#define xdais_6_26_01_03_Version__include_state


#endif /* xdais_6_26_01_03_Version__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdais_6_26_01_03_Version__nolocalnames)

/* module prefix */
#define Version_MAJOR xdais_6_26_01_03_Version_MAJOR
#define Version_MINOR xdais_6_26_01_03_Version_MINOR
#define Version_PATCH xdais_6_26_01_03_Version_PATCH
#define Version_WIDTH xdais_6_26_01_03_Version_WIDTH
#define Version_Module_name xdais_6_26_01_03_Version_Module_name
#define Version_Module_id xdais_6_26_01_03_Version_Module_id
#define Version_Module_startup xdais_6_26_01_03_Version_Module_startup
#define Version_Module_startupDone xdais_6_26_01_03_Version_Module_startupDone
#define Version_Module_hasMask xdais_6_26_01_03_Version_Module_hasMask
#define Version_Module_getMask xdais_6_26_01_03_Version_Module_getMask
#define Version_Module_setMask xdais_6_26_01_03_Version_Module_setMask
#define Version_Object_heap xdais_6_26_01_03_Version_Object_heap
#define Version_Module_heap xdais_6_26_01_03_Version_Module_heap
#define Version_Module_upCast xdais_6_26_01_03_Version_Module_upCast
#define Version_Module_to_ti_sdoarch_standards_pkg_IVersion xdais_6_26_01_03_Version_Module_to_ti_sdoarch_standards_pkg_IVersion

#endif
/*
 *  @(#) xdais_6_26_01_03; 1, 0, 0,1; 9-18-2010 14:49:13; /db/wtree/library/trees/dais/dais-t03x/src/ xlibrary

 */

