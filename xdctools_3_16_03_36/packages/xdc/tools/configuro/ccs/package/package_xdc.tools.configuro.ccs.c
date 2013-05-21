#ifndef __config__
char __dummy__;
#define __xdc_PKGVERS 1, 0, 0, 0
#define __xdc_PKGNAME xdc.tools.configuro.ccs
#define __xdc_PKGPREFIX xdc_tools_configuro_ccs_
#ifdef __xdc_bld_pkg_c__
#define __stringify(a) #a
#define __local_include(a) __stringify(a)
#include __local_include(__xdc_bld_pkg_c__)
#endif

#else
#include <string.h>

#ifndef xdc_runtime_System__include
#ifndef __nested__
#define __nested__
#include <xdc/runtime/System.h>
#undef __nested__
#else
#include <xdc/runtime/System.h>
#endif
#endif

#ifndef xdc_runtime_Memory__include
#ifndef __nested__
#define __nested__
#include <xdc/runtime/Memory.h>
#undef __nested__
#else
#include <xdc/runtime/Memory.h>
#endif
#endif

#ifndef xdc_runtime_Error__include
#ifndef __nested__
#define __nested__
#include <xdc/runtime/Error.h>
#undef __nested__
#else
#include <xdc/runtime/Error.h>
#endif
#endif


#endif
