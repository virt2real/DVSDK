/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-u17
 */

#ifndef xdc_runtime_LoggerBuf__INTERNAL__
#define xdc_runtime_LoggerBuf__INTERNAL__

#ifndef xdc_runtime_LoggerBuf__internalaccess
#define xdc_runtime_LoggerBuf__internalaccess
#endif

#include <xdc/runtime/LoggerBuf.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* write4 */
#undef xdc_runtime_LoggerBuf_write4
#define xdc_runtime_LoggerBuf_write4 xdc_runtime_LoggerBuf_write4__F

/* write8 */
#undef xdc_runtime_LoggerBuf_write8
#define xdc_runtime_LoggerBuf_write8 xdc_runtime_LoggerBuf_write8__F

/* flushAll */
#undef xdc_runtime_LoggerBuf_flushAll
#define xdc_runtime_LoggerBuf_flushAll xdc_runtime_LoggerBuf_flushAll__F

/* flushAllInternal */
#undef xdc_runtime_LoggerBuf_flushAllInternal
#define xdc_runtime_LoggerBuf_flushAllInternal xdc_runtime_LoggerBuf_flushAllInternal__F

/* enable */
#undef xdc_runtime_LoggerBuf_enable
#define xdc_runtime_LoggerBuf_enable xdc_runtime_LoggerBuf_enable__F

/* disable */
#undef xdc_runtime_LoggerBuf_disable
#define xdc_runtime_LoggerBuf_disable xdc_runtime_LoggerBuf_disable__F

/* reset */
#undef xdc_runtime_LoggerBuf_reset
#define xdc_runtime_LoggerBuf_reset xdc_runtime_LoggerBuf_reset__F

/* flush */
#undef xdc_runtime_LoggerBuf_flush
#define xdc_runtime_LoggerBuf_flush xdc_runtime_LoggerBuf_flush__F

/* getNextEntry */
#undef xdc_runtime_LoggerBuf_getNextEntry
#define xdc_runtime_LoggerBuf_getNextEntry xdc_runtime_LoggerBuf_getNextEntry__F

/* Module_startup */
#undef xdc_runtime_LoggerBuf_Module_startup
#define xdc_runtime_LoggerBuf_Module_startup xdc_runtime_LoggerBuf_Module_startup__F

/* Instance_init */
#undef xdc_runtime_LoggerBuf_Instance_init
#define xdc_runtime_LoggerBuf_Instance_init xdc_runtime_LoggerBuf_Instance_init__F

/* Instance_finalize */
#undef xdc_runtime_LoggerBuf_Instance_finalize
#define xdc_runtime_LoggerBuf_Instance_finalize xdc_runtime_LoggerBuf_Instance_finalize__F

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_LoggerBuf_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_LoggerBuf_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_LoggerBuf_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_LoggerBuf_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_LoggerBuf_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_LoggerBuf_Module__loggerObj__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_LoggerBuf_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_LoggerBuf_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_LoggerBuf_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_LoggerBuf_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_LoggerBuf_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_LoggerBuf_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_LoggerBuf_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_LoggerBuf_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_LoggerBuf_Module_GateProxy_query

/* Object__sizingError */
#line 1 "Error_inconsistent_object_size_in_xdc.runtime.LoggerBuf"
typedef char xdc_runtime_LoggerBuf_Object__sizingError[sizeof(xdc_runtime_LoggerBuf_Object) > sizeof(xdc_runtime_LoggerBuf_Struct) ? -1 : 1];


#endif /* xdc_runtime_LoggerBuf__INTERNAL____ */
