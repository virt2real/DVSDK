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

#ifndef xdc_runtime_Error__include
#define xdc_runtime_Error__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_Error__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_Error___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Error__prologue.h>
#include <xdc/runtime/package/package.defs.h>

#include <xdc/runtime/Types.h>
#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Policy */
enum xdc_runtime_Error_Policy {
    xdc_runtime_Error_TERMINATE,
    xdc_runtime_Error_UNWIND
};
typedef enum xdc_runtime_Error_Policy xdc_runtime_Error_Policy;

/* Id */

/* NUMARGS */
#define xdc_runtime_Error_NUMARGS (2)

/* Data */
typedef xdc_IArg __T1_xdc_runtime_Error_Data__arg;
typedef xdc_IArg __ARRAY1_xdc_runtime_Error_Data__arg[2];
typedef __ARRAY1_xdc_runtime_Error_Data__arg __TA_xdc_runtime_Error_Data__arg;
struct xdc_runtime_Error_Data {
    __TA_xdc_runtime_Error_Data__arg arg;
};

/* Block */
typedef xdc_IArg __T1_xdc_runtime_Error_Block__xtra;
typedef xdc_IArg __ARRAY1_xdc_runtime_Error_Block__xtra[4];
typedef __ARRAY1_xdc_runtime_Error_Block__xtra __TA_xdc_runtime_Error_Block__xtra;
struct xdc_runtime_Error_Block {
    xdc_UInt16 unused;
    xdc_runtime_Error_Data data;
    xdc_runtime_Error_Id id;
    xdc_String msg;
    xdc_runtime_Types_Site site;
    __TA_xdc_runtime_Error_Block__xtra xtra;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Error_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_runtime_Error_Module__diagsEnabled xdc_runtime_Error_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Error_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_runtime_Error_Module__diagsIncluded xdc_runtime_Error_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Error_Module__diagsMask;
__extern __FAR__ const CT__xdc_runtime_Error_Module__diagsMask xdc_runtime_Error_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Error_Module__gateObj;
__extern __FAR__ const CT__xdc_runtime_Error_Module__gateObj xdc_runtime_Error_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Error_Module__gatePrms;
__extern __FAR__ const CT__xdc_runtime_Error_Module__gatePrms xdc_runtime_Error_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Error_Module__id;
__extern __FAR__ const CT__xdc_runtime_Error_Module__id xdc_runtime_Error_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Error_Module__loggerDefined;
__extern __FAR__ const CT__xdc_runtime_Error_Module__loggerDefined xdc_runtime_Error_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Error_Module__loggerObj;
__extern __FAR__ const CT__xdc_runtime_Error_Module__loggerObj xdc_runtime_Error_Module__loggerObj__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Error_Module__loggerFxn4;
__extern __FAR__ const CT__xdc_runtime_Error_Module__loggerFxn4 xdc_runtime_Error_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Error_Module__loggerFxn8;
__extern __FAR__ const CT__xdc_runtime_Error_Module__loggerFxn8 xdc_runtime_Error_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Error_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__xdc_runtime_Error_Module__startupDoneFxn xdc_runtime_Error_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Error_Object__count;
__extern __FAR__ const CT__xdc_runtime_Error_Object__count xdc_runtime_Error_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Error_Object__heap;
__extern __FAR__ const CT__xdc_runtime_Error_Object__heap xdc_runtime_Error_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Error_Object__sizeof;
__extern __FAR__ const CT__xdc_runtime_Error_Object__sizeof xdc_runtime_Error_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Error_Object__table;
__extern __FAR__ const CT__xdc_runtime_Error_Object__table xdc_runtime_Error_Object__table__C;

/* E_generic */
#define xdc_runtime_Error_E_generic (xdc_runtime_Error_E_generic__C)
typedef xdc_runtime_Error_Id CT__xdc_runtime_Error_E_generic;
__extern __FAR__ const CT__xdc_runtime_Error_E_generic xdc_runtime_Error_E_generic__C;

/* E_memory */
#define xdc_runtime_Error_E_memory (xdc_runtime_Error_E_memory__C)
typedef xdc_runtime_Error_Id CT__xdc_runtime_Error_E_memory;
__extern __FAR__ const CT__xdc_runtime_Error_E_memory xdc_runtime_Error_E_memory__C;

/* policy */
#define xdc_runtime_Error_policy (xdc_runtime_Error_policy__C)
typedef xdc_runtime_Error_Policy CT__xdc_runtime_Error_policy;
__extern __FAR__ const CT__xdc_runtime_Error_policy xdc_runtime_Error_policy__C;

/* raiseHook */
#define xdc_runtime_Error_raiseHook (xdc_runtime_Error_raiseHook__C)
typedef xdc_Void (*CT__xdc_runtime_Error_raiseHook)(xdc_runtime_Error_Block*);
__extern __FAR__ const CT__xdc_runtime_Error_raiseHook xdc_runtime_Error_raiseHook__C;

/* maxDepth */
#define xdc_runtime_Error_maxDepth (xdc_runtime_Error_maxDepth__C)
typedef xdc_UInt16 CT__xdc_runtime_Error_maxDepth;
__extern __FAR__ const CT__xdc_runtime_Error_maxDepth xdc_runtime_Error_maxDepth__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdc_runtime_Error_Module_startup( state ) -1

/* Handle__label__S */
xdc__CODESECT(xdc_runtime_Error_Handle__label__S, "xdc_runtime_Error_Handle__label")
__extern xdc_runtime_Types_Label* xdc_runtime_Error_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */
xdc__CODESECT(xdc_runtime_Error_Module__startupDone__S, "xdc_runtime_Error_Module__startupDone")
__extern xdc_Bool xdc_runtime_Error_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(xdc_runtime_Error_Object__create__S, "xdc_runtime_Error_Object__create")
__extern xdc_Ptr xdc_runtime_Error_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */
xdc__CODESECT(xdc_runtime_Error_Object__delete__S, "xdc_runtime_Error_Object__delete")
__extern xdc_Void xdc_runtime_Error_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */
xdc__CODESECT(xdc_runtime_Error_Object__destruct__S, "xdc_runtime_Error_Object__destruct")
__extern xdc_Void xdc_runtime_Error_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(xdc_runtime_Error_Object__get__S, "xdc_runtime_Error_Object__get")
__extern xdc_Ptr xdc_runtime_Error_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(xdc_runtime_Error_Object__first__S, "xdc_runtime_Error_Object__first")
__extern xdc_Ptr xdc_runtime_Error_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(xdc_runtime_Error_Object__next__S, "xdc_runtime_Error_Object__next")
__extern xdc_Ptr xdc_runtime_Error_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(xdc_runtime_Error_Params__init__S, "xdc_runtime_Error_Params__init")
__extern xdc_Void xdc_runtime_Error_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(xdc_runtime_Error_Proxy__abstract__S, "xdc_runtime_Error_Proxy__abstract")
__extern xdc_Bool xdc_runtime_Error_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(xdc_runtime_Error_Proxy__delegate__S, "xdc_runtime_Error_Proxy__delegate")
__extern xdc_Ptr xdc_runtime_Error_Proxy__delegate__S( void );

/* check__E */
#define xdc_runtime_Error_check xdc_runtime_Error_check__E
xdc__CODESECT(xdc_runtime_Error_check__E, "xdc_runtime_Error_check")
__extern xdc_Bool xdc_runtime_Error_check__E( xdc_runtime_Error_Block* eb );
xdc__CODESECT(xdc_runtime_Error_check__F, "xdc_runtime_Error_check")
__extern xdc_Bool xdc_runtime_Error_check__F( xdc_runtime_Error_Block* eb );
__extern xdc_Bool xdc_runtime_Error_check__R( xdc_runtime_Error_Block* eb );

/* getData__E */
#define xdc_runtime_Error_getData xdc_runtime_Error_getData__E
xdc__CODESECT(xdc_runtime_Error_getData__E, "xdc_runtime_Error_getData")
__extern xdc_runtime_Error_Data* xdc_runtime_Error_getData__E( xdc_runtime_Error_Block* eb );
xdc__CODESECT(xdc_runtime_Error_getData__F, "xdc_runtime_Error_getData")
__extern xdc_runtime_Error_Data* xdc_runtime_Error_getData__F( xdc_runtime_Error_Block* eb );
__extern xdc_runtime_Error_Data* xdc_runtime_Error_getData__R( xdc_runtime_Error_Block* eb );

/* getCode__E */
#define xdc_runtime_Error_getCode xdc_runtime_Error_getCode__E
xdc__CODESECT(xdc_runtime_Error_getCode__E, "xdc_runtime_Error_getCode")
__extern xdc_UInt16 xdc_runtime_Error_getCode__E( xdc_runtime_Error_Block* eb );
xdc__CODESECT(xdc_runtime_Error_getCode__F, "xdc_runtime_Error_getCode")
__extern xdc_UInt16 xdc_runtime_Error_getCode__F( xdc_runtime_Error_Block* eb );
__extern xdc_UInt16 xdc_runtime_Error_getCode__R( xdc_runtime_Error_Block* eb );

/* getId__E */
#define xdc_runtime_Error_getId xdc_runtime_Error_getId__E
xdc__CODESECT(xdc_runtime_Error_getId__E, "xdc_runtime_Error_getId")
__extern xdc_runtime_Error_Id xdc_runtime_Error_getId__E( xdc_runtime_Error_Block* eb );
xdc__CODESECT(xdc_runtime_Error_getId__F, "xdc_runtime_Error_getId")
__extern xdc_runtime_Error_Id xdc_runtime_Error_getId__F( xdc_runtime_Error_Block* eb );
__extern xdc_runtime_Error_Id xdc_runtime_Error_getId__R( xdc_runtime_Error_Block* eb );

/* getMsg__E */
#define xdc_runtime_Error_getMsg xdc_runtime_Error_getMsg__E
xdc__CODESECT(xdc_runtime_Error_getMsg__E, "xdc_runtime_Error_getMsg")
__extern xdc_String xdc_runtime_Error_getMsg__E( xdc_runtime_Error_Block* eb );
xdc__CODESECT(xdc_runtime_Error_getMsg__F, "xdc_runtime_Error_getMsg")
__extern xdc_String xdc_runtime_Error_getMsg__F( xdc_runtime_Error_Block* eb );
__extern xdc_String xdc_runtime_Error_getMsg__R( xdc_runtime_Error_Block* eb );

/* getSite__E */
#define xdc_runtime_Error_getSite xdc_runtime_Error_getSite__E
xdc__CODESECT(xdc_runtime_Error_getSite__E, "xdc_runtime_Error_getSite")
__extern xdc_runtime_Types_Site* xdc_runtime_Error_getSite__E( xdc_runtime_Error_Block* eb );
xdc__CODESECT(xdc_runtime_Error_getSite__F, "xdc_runtime_Error_getSite")
__extern xdc_runtime_Types_Site* xdc_runtime_Error_getSite__F( xdc_runtime_Error_Block* eb );
__extern xdc_runtime_Types_Site* xdc_runtime_Error_getSite__R( xdc_runtime_Error_Block* eb );

/* init__E */
#define xdc_runtime_Error_init xdc_runtime_Error_init__E
xdc__CODESECT(xdc_runtime_Error_init__E, "xdc_runtime_Error_init")
__extern xdc_Void xdc_runtime_Error_init__E( xdc_runtime_Error_Block* eb );
xdc__CODESECT(xdc_runtime_Error_init__F, "xdc_runtime_Error_init")
__extern xdc_Void xdc_runtime_Error_init__F( xdc_runtime_Error_Block* eb );
__extern xdc_Void xdc_runtime_Error_init__R( xdc_runtime_Error_Block* eb );

/* print__E */
#define xdc_runtime_Error_print xdc_runtime_Error_print__E
xdc__CODESECT(xdc_runtime_Error_print__E, "xdc_runtime_Error_print")
__extern xdc_Void xdc_runtime_Error_print__E( xdc_runtime_Error_Block* eb );
xdc__CODESECT(xdc_runtime_Error_print__F, "xdc_runtime_Error_print")
__extern xdc_Void xdc_runtime_Error_print__F( xdc_runtime_Error_Block* eb );
__extern xdc_Void xdc_runtime_Error_print__R( xdc_runtime_Error_Block* eb );

/* raiseX__E */
#define xdc_runtime_Error_raiseX xdc_runtime_Error_raiseX__E
xdc__CODESECT(xdc_runtime_Error_raiseX__E, "xdc_runtime_Error_raiseX")
__extern xdc_Void xdc_runtime_Error_raiseX__E( xdc_runtime_Error_Block* eb, xdc_runtime_Types_ModuleId mod, xdc_String file, xdc_Int line, xdc_runtime_Error_Id id, xdc_IArg arg1, xdc_IArg arg2 );
xdc__CODESECT(xdc_runtime_Error_raiseX__F, "xdc_runtime_Error_raiseX")
__extern xdc_Void xdc_runtime_Error_raiseX__F( xdc_runtime_Error_Block* eb, xdc_runtime_Types_ModuleId mod, xdc_String file, xdc_Int line, xdc_runtime_Error_Id id, xdc_IArg arg1, xdc_IArg arg2 );
__extern xdc_Void xdc_runtime_Error_raiseX__R( xdc_runtime_Error_Block* eb, xdc_runtime_Types_ModuleId mod, xdc_String file, xdc_Int line, xdc_runtime_Error_Id id, xdc_IArg arg1, xdc_IArg arg2 );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdc_runtime_Error_Module_startupDone() xdc_runtime_Error_Module__startupDone__S()

/* Object_heap */
#define xdc_runtime_Error_Object_heap() xdc_runtime_Error_Object__heap__C

/* Module_heap */
#define xdc_runtime_Error_Module_heap() xdc_runtime_Error_Object__heap__C

/* Module_id */
static inline CT__xdc_runtime_Error_Module__id xdc_runtime_Error_Module_id( void ) 
{
    return xdc_runtime_Error_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_Error_Module_hasMask( void ) 
{
    return xdc_runtime_Error_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_Error_Module_getMask( void ) 
{
    return xdc_runtime_Error_Module__diagsMask__C != NULL ? *xdc_runtime_Error_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void xdc_runtime_Error_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_Error_Module__diagsMask__C != NULL) *xdc_runtime_Error_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#include <xdc/runtime/Error__epilogue.h>

#ifdef xdc_runtime_Error__top__
#undef __nested__
#endif

#endif /* xdc_runtime_Error__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdc_runtime_Error__internalaccess))

#ifndef xdc_runtime_Error__include_state
#define xdc_runtime_Error__include_state

/* Module_State */
struct xdc_runtime_Error_Module_State {
    xdc_UInt16 count;
};

/* Module__state__V */
#ifdef __config__
extern struct xdc_runtime_Error_Module_State__ xdc_runtime_Error_Module__state__V;
#else
extern xdc_runtime_Error_Module_State xdc_runtime_Error_Module__state__V;
#endif

#endif /* xdc_runtime_Error__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_Error__nolocalnames)

/* module prefix */
#define Error_Policy xdc_runtime_Error_Policy
#define Error_Id xdc_runtime_Error_Id
#define Error_NUMARGS xdc_runtime_Error_NUMARGS
#define Error_Data xdc_runtime_Error_Data
#define Error_Block xdc_runtime_Error_Block
#define Error_Module_State xdc_runtime_Error_Module_State
#define Error_TERMINATE xdc_runtime_Error_TERMINATE
#define Error_UNWIND xdc_runtime_Error_UNWIND
#define Error_E_generic xdc_runtime_Error_E_generic
#define Error_E_memory xdc_runtime_Error_E_memory
#define Error_policy xdc_runtime_Error_policy
#define Error_raiseHook xdc_runtime_Error_raiseHook
#define Error_maxDepth xdc_runtime_Error_maxDepth
#define Error_check xdc_runtime_Error_check
#define Error_getData xdc_runtime_Error_getData
#define Error_getCode xdc_runtime_Error_getCode
#define Error_getId xdc_runtime_Error_getId
#define Error_getMsg xdc_runtime_Error_getMsg
#define Error_getSite xdc_runtime_Error_getSite
#define Error_idToCode xdc_runtime_Error_idToCode
#define Error_init xdc_runtime_Error_init
#define Error_print xdc_runtime_Error_print
#define Error_raise xdc_runtime_Error_raise
#define Error_raiseX xdc_runtime_Error_raiseX
#define Error_Module_name xdc_runtime_Error_Module_name
#define Error_Module_id xdc_runtime_Error_Module_id
#define Error_Module_startup xdc_runtime_Error_Module_startup
#define Error_Module_startupDone xdc_runtime_Error_Module_startupDone
#define Error_Module_hasMask xdc_runtime_Error_Module_hasMask
#define Error_Module_getMask xdc_runtime_Error_Module_getMask
#define Error_Module_setMask xdc_runtime_Error_Module_setMask
#define Error_Object_heap xdc_runtime_Error_Object_heap
#define Error_Module_heap xdc_runtime_Error_Module_heap

#endif
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

