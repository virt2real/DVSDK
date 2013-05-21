/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-u17
 */

#ifndef xdc_runtime_System__INTERNAL__
#define xdc_runtime_System__INTERNAL__

#ifndef xdc_runtime_System__internalaccess
#define xdc_runtime_System__internalaccess
#endif

#include <xdc/runtime/System.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* abort */
#undef xdc_runtime_System_abort
#define xdc_runtime_System_abort xdc_runtime_System_abort__F

/* atexit */
#undef xdc_runtime_System_atexit
#define xdc_runtime_System_atexit xdc_runtime_System_atexit__F

/* exit */
#undef xdc_runtime_System_exit
#define xdc_runtime_System_exit xdc_runtime_System_exit__F

/* putch */
#undef xdc_runtime_System_putch
#define xdc_runtime_System_putch xdc_runtime_System_putch__F

/* flush */
#undef xdc_runtime_System_flush
#define xdc_runtime_System_flush xdc_runtime_System_flush__F

/* printf */
#undef xdc_runtime_System_printf_va
#define xdc_runtime_System_printf_va xdc_runtime_System_printf_va__F

/* aprintf */
#undef xdc_runtime_System_aprintf_va
#define xdc_runtime_System_aprintf_va xdc_runtime_System_aprintf_va__F

/* sprintf */
#undef xdc_runtime_System_sprintf_va
#define xdc_runtime_System_sprintf_va xdc_runtime_System_sprintf_va__F

/* asprintf */
#undef xdc_runtime_System_asprintf_va
#define xdc_runtime_System_asprintf_va xdc_runtime_System_asprintf_va__F

/* vprintf */
#undef xdc_runtime_System_vprintf
#define xdc_runtime_System_vprintf xdc_runtime_System_vprintf__F

/* avprintf */
#undef xdc_runtime_System_avprintf
#define xdc_runtime_System_avprintf xdc_runtime_System_avprintf__F

/* vsprintf */
#undef xdc_runtime_System_vsprintf
#define xdc_runtime_System_vsprintf xdc_runtime_System_vsprintf__F

/* avsprintf */
#undef xdc_runtime_System_avsprintf
#define xdc_runtime_System_avsprintf xdc_runtime_System_avsprintf__F

/* printfExtend */
#define System_printfExtend xdc_runtime_System_printfExtend__I

/* doPrint */
#define System_doPrint xdc_runtime_System_doPrint__I

/* formatNum */
#define System_formatNum xdc_runtime_System_formatNum__I

/* putchar */
#define System_putchar xdc_runtime_System_putchar__I

/* rtsExit */
#define System_rtsExit xdc_runtime_System_rtsExit__I

/* Module_startup */
#undef xdc_runtime_System_Module_startup
#define xdc_runtime_System_Module_startup xdc_runtime_System_Module_startup__F

/* Instance_init */
#undef xdc_runtime_System_Instance_init
#define xdc_runtime_System_Instance_init xdc_runtime_System_Instance_init__F

/* Instance_finalize */
#undef xdc_runtime_System_Instance_finalize
#define xdc_runtime_System_Instance_finalize xdc_runtime_System_Instance_finalize__F

/* module */
#define System_module ((xdc_runtime_System_Module_State *)(xdc__MODOBJADDR__(xdc_runtime_System_Module__state__V)))
#if !defined(__cplusplus) || !defined(xdc_runtime_System__cplusplus)
#define module ((xdc_runtime_System_Module_State *)(xdc__MODOBJADDR__(xdc_runtime_System_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_System_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_System_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_System_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_System_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_System_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_System_Module__loggerObj__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_System_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_System_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_System_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_System_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_System_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_System_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_System_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_System_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_System_Module_GateProxy_query


#endif /* xdc_runtime_System__INTERNAL____ */
