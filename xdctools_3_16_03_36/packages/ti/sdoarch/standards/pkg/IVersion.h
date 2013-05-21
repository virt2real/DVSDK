/*
 *  ======== ti/sdoarch/standards/pkg/IVersion.h ========
 *
 *  DO NOT MODIFY THIS FILE
 *
 *  It is generated from ti/sdoarch/standards/pkg/IVersion.xdc and any changes may be overwritten.
 */

#ifdef ti_sdoarch_standards_pkg_IVersion___EXTERNAL_SYNOPSIS
#error do not compile!!


    #include <ti/sdoarch/standards/pkg/IVersion.h>

    /* -------- constants -------- */

    static const UInt16 IVersion_MAJOR;
    static const UInt16 IVersion_MINOR;
    static const UInt16 IVersion_PATCH;
    static const UInt16 IVersion_WIDTH;

    /* -------- module-wide configs -------- */



#endif /* ti_sdoarch_standards_pkg_IVersion___EXTERNAL_SYNOPSIS */







#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#ifndef xdc_std__include
#ifndef __nested__
#define __nested__
#include <xdc/std.h>
#undef __nested__
#else
#include <xdc/std.h>
#endif
#endif

#ifndef XDC__
#include <xdc/runtime/xdc.h>
#endif
#ifndef xdc_runtime_Types__include
#ifndef __nested__
#define __nested__
#include <xdc/runtime/Types.h>
#undef __nested__
#else
#include <xdc/runtime/Types.h>
#endif
#endif

#ifndef ti_sdoarch_standards_pkg_IVersion__include
#define ti_sdoarch_standards_pkg_IVersion__include

#ifndef ti_sdoarch_standards_pkg__
#include <ti/sdoarch/standards/pkg/package/package.defs.h>
#endif

#ifndef xdc_runtime_IModule__include
#ifndef __nested__
#define __nested__
#include <xdc/runtime/IModule.h>
#undef __nested__
#else
#include <xdc/runtime/IModule.h>
#endif
#endif


/* auxiliary definitions */

/* virtual functions */
struct ti_sdoarch_standards_pkg_IVersion_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns* __sysp;
    xdc_runtime_Types_SysFxns __sfxns;
};
__extern const xdc_runtime_Types_Base ti_sdoarch_standards_pkg_IVersion_Interface__BASE__C;

/* function stubs */
static inline xdc_runtime_Types_ModuleId ti_sdoarch_standards_pkg_IVersion_Module_id( ti_sdoarch_standards_pkg_IVersion_Module mod ) {
    return mod->__sysp->__mid; }

/* function selectors */

#endif /* ti_sdoarch_standards_pkg_IVersion__include */

/* __prefix alises */
#if !defined(__nested__) && !defined(ti_sdoarch_standards_pkg_IVersion__nolocalnames)
#define IVersion_Module ti_sdoarch_standards_pkg_IVersion_Module
#define IVersion_MAJOR ti_sdoarch_standards_pkg_IVersion_MAJOR
#define IVersion_MINOR ti_sdoarch_standards_pkg_IVersion_MINOR
#define IVersion_PATCH ti_sdoarch_standards_pkg_IVersion_PATCH
#define IVersion_WIDTH ti_sdoarch_standards_pkg_IVersion_WIDTH
#define IVersion_Module_name ti_sdoarch_standards_pkg_IVersion_Module_name
#endif



/* @(#) ti.sdoarch.standards.pkg; 1, 0, 0; Thu, 16 Jul 2009 21:28:29 GMT; /db/ztree/library/trees/ps-b05x/src  */
