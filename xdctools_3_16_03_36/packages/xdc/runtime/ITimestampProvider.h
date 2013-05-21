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
 *     CONVERTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef xdc_runtime_ITimestampProvider__include
#define xdc_runtime_ITimestampProvider__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_ITimestampProvider__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_ITimestampProvider___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/package/package.defs.h>

#include <xdc/runtime/ITimestampClient.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_ITimestampProvider_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bits32 (*get32)(void);
    xdc_Void (*get64)(xdc_runtime_Types_Timestamp64*);
    xdc_Void (*getFreq)(xdc_runtime_Types_FreqHz*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base xdc_runtime_ITimestampProvider_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* Module_id */
static inline xdc_runtime_Types_ModuleId xdc_runtime_ITimestampProvider_Module_id( xdc_runtime_ITimestampProvider_Module mod )
{
    return mod->__sysp->__mid;
}

/* get32 */
static inline xdc_Bits32 xdc_runtime_ITimestampProvider_get32( xdc_runtime_ITimestampProvider_Module __inst )
{
    return __inst->get32();
}

/* get64 */
static inline xdc_Void xdc_runtime_ITimestampProvider_get64( xdc_runtime_ITimestampProvider_Module __inst, xdc_runtime_Types_Timestamp64* result )
{
    __inst->get64(result);
}

/* getFreq */
static inline xdc_Void xdc_runtime_ITimestampProvider_getFreq( xdc_runtime_ITimestampProvider_Module __inst, xdc_runtime_Types_FreqHz* freq )
{
    __inst->getFreq(freq);
}


/*
 * ======== FUNCTION SELECTORS ========
 */

/* get32_{FxnT,fxnP} */
typedef xdc_Bits32 (*xdc_runtime_ITimestampProvider_get32_FxnT)(void);
static inline xdc_runtime_ITimestampProvider_get32_FxnT xdc_runtime_ITimestampProvider_get32_fxnP( xdc_runtime_ITimestampProvider_Module __inst )
{
    return (xdc_runtime_ITimestampProvider_get32_FxnT)__inst->get32;
}

/* get64_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_ITimestampProvider_get64_FxnT)(xdc_runtime_Types_Timestamp64*);
static inline xdc_runtime_ITimestampProvider_get64_FxnT xdc_runtime_ITimestampProvider_get64_fxnP( xdc_runtime_ITimestampProvider_Module __inst )
{
    return (xdc_runtime_ITimestampProvider_get64_FxnT)__inst->get64;
}

/* getFreq_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_ITimestampProvider_getFreq_FxnT)(xdc_runtime_Types_FreqHz*);
static inline xdc_runtime_ITimestampProvider_getFreq_FxnT xdc_runtime_ITimestampProvider_getFreq_fxnP( xdc_runtime_ITimestampProvider_Module __inst )
{
    return (xdc_runtime_ITimestampProvider_getFreq_FxnT)__inst->getFreq;
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_ITimestampClient_Module xdc_runtime_ITimestampProvider_Module_upCast( xdc_runtime_ITimestampProvider_Module m )
{
    return(xdc_runtime_ITimestampClient_Module)m;
}

/* Module_to_xdc_runtime_ITimestampClient */
#define xdc_runtime_ITimestampProvider_Module_to_xdc_runtime_ITimestampClient xdc_runtime_ITimestampProvider_Module_upCast

/* Module_downCast */
static inline xdc_runtime_ITimestampProvider_Module xdc_runtime_ITimestampProvider_Module_downCast( xdc_runtime_ITimestampClient_Module m )
{
    xdc_runtime_Types_Base* b; for (b = m->__base; b; b = b->base) {
        if (b == &xdc_runtime_ITimestampProvider_Interface__BASE__C) return (xdc_runtime_ITimestampProvider_Module)m;
    } return 0;
}

/* Module_from_xdc_runtime_ITimestampClient */
#define xdc_runtime_ITimestampProvider_Module_from_xdc_runtime_ITimestampClient xdc_runtime_ITimestampProvider_Module_downCast


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_ITimestampProvider__top__
#undef __nested__
#endif

#endif /* xdc_runtime_ITimestampProvider__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_ITimestampProvider__nolocalnames)

/* module prefix */
#define ITimestampProvider_Module xdc_runtime_ITimestampProvider_Module
#define ITimestampProvider_get32 xdc_runtime_ITimestampProvider_get32
#define ITimestampProvider_get32_fxnP xdc_runtime_ITimestampProvider_get32_fxnP
#define ITimestampProvider_get32_FxnT xdc_runtime_ITimestampProvider_get32_FxnT
#define ITimestampProvider_get64 xdc_runtime_ITimestampProvider_get64
#define ITimestampProvider_get64_fxnP xdc_runtime_ITimestampProvider_get64_fxnP
#define ITimestampProvider_get64_FxnT xdc_runtime_ITimestampProvider_get64_FxnT
#define ITimestampProvider_getFreq xdc_runtime_ITimestampProvider_getFreq
#define ITimestampProvider_getFreq_fxnP xdc_runtime_ITimestampProvider_getFreq_fxnP
#define ITimestampProvider_getFreq_FxnT xdc_runtime_ITimestampProvider_getFreq_FxnT
#define ITimestampProvider_Module_name xdc_runtime_ITimestampProvider_Module_name
#define ITimestampProvider_Module_upCast xdc_runtime_ITimestampProvider_Module_upCast
#define ITimestampProvider_Module_to_xdc_runtime_ITimestampClient xdc_runtime_ITimestampProvider_Module_to_xdc_runtime_ITimestampClient
#define ITimestampProvider_Module_downCast xdc_runtime_ITimestampProvider_Module_downCast
#define ITimestampProvider_Module_from_xdc_runtime_ITimestampClient xdc_runtime_ITimestampProvider_Module_from_xdc_runtime_ITimestampClient

#endif
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

