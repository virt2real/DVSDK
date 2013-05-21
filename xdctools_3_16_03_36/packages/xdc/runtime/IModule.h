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
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef xdc_runtime_IModule__include
#define xdc_runtime_IModule__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_IModule__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_IModule___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/package/package.defs.h>

#include <xdc/runtime/Types.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Error.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_IModule_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base xdc_runtime_IModule_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* Module_id */
static inline xdc_runtime_Types_ModuleId xdc_runtime_IModule_Module_id( xdc_runtime_IModule_Module mod )
{
    return mod->__sysp->__mid;
}


/*
 * ======== FUNCTION SELECTORS ========
 */


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_IModule__top__
#undef __nested__
#endif

#endif /* xdc_runtime_IModule__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_IModule__nolocalnames)

/* module prefix */
#define IModule_Module xdc_runtime_IModule_Module
#define IModule_Module_name xdc_runtime_IModule_Module_name

#endif
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

