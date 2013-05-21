/* --COPYRIGHT--,EPL
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * --/COPYRIGHT--*/

var ProdQuery;
function module$meta$init()
{
    
/* Modules */

/* System Providers Sub Group Modules */

    this.xdc_runtime_SysMin.elemName = "SysMin";
    this.xdc_runtime_SysMin.moduleName = "xdc.runtime.SysMin";
    this.xdc_runtime_SysMin.iconFileName = "icons/sys.ico";

    this.xdc_runtime_SysStd.elemName = "SysStd";
    this.xdc_runtime_SysStd.moduleName = "xdc.runtime.SysStd";
    this.xdc_runtime_SysStd.iconFileName = "icons/sys.ico";

/* System Group Modules */

    this.xdc_cfg_Program.elemName = "Program";
    this.xdc_cfg_Program.moduleName = "xdc.cfg.Program";
    this.xdc_cfg_Program.iconFileName = "icons/cfg.ico";

    this.xdc_runtime_Main.elemName = "Main";
    this.xdc_runtime_Main.moduleName = "xdc.runtime.Main";
    this.xdc_runtime_Main.iconFileName = "icons/cfg.ico";

    this.xdc_runtime_Defaults.elemName = "Defaults";
    this.xdc_runtime_Defaults.moduleName = "xdc.runtime.Defaults";
    this.xdc_runtime_Defaults.iconFileName = "icons/prj.ico";
        
    this.xdc_runtime_System.elemName = "System";
    this.xdc_runtime_System.moduleName = "xdc.runtime.System";
    this.xdc_runtime_System.iconFileName = "icons/sys.ico";

    this.xdc_runtime_Startup.elemName = "Startup";
    this.xdc_runtime_Startup.moduleName = "xdc.runtime.Startup";
    this.xdc_runtime_Startup.iconFileName = "icons/ACCEL.ico";

/* Loggers Sub Group Modules */

    this.xdc_runtime_LoggerBuf.elemName = "LoggerBuf";
    this.xdc_runtime_LoggerBuf.moduleName = "xdc.runtime.LoggerBuf";
    this.xdc_runtime_LoggerBuf.iconFileName = "icons/log.ico";

    this.xdc_runtime_LoggerSys.elemName = "LoggerSys";
    this.xdc_runtime_LoggerSys.moduleName = "xdc.runtime.LoggerSys";
    this.xdc_runtime_LoggerSys.iconFileName = "icons/log.ico";

/* Diagnostics Group Modules */

    this.xdc_runtime_Log.elemName = "Log";
    this.xdc_runtime_Log.moduleName = "xdc.runtime.Log";
    this.xdc_runtime_Log.iconFileName = "icons/log.ico";
    
    this.xdc_runtime_Assert.elemName = "Assert";
    this.xdc_runtime_Assert.moduleName = "xdc.runtime.Assert";
    this.xdc_runtime_Assert.iconFileName = "icons/err.ico";

    this.xdc_runtime_Diags.elemName = "Diags";
    this.xdc_runtime_Diags.moduleName = "xdc.runtime.Diags";
    this.xdc_runtime_Diags.iconFileName = "icons/sts.ico";

    this.xdc_runtime_Error.elemName = "Error";
    this.xdc_runtime_Error.moduleName = "xdc.runtime.Error";
    this.xdc_runtime_Error.iconFileName = "icons/err.ico";

    this.xdc_runtime_Timestamp.elemName = "Timestamp";
    this.xdc_runtime_Timestamp.moduleName = "xdc.runtime.Timestamp";
    this.xdc_runtime_Timestamp.iconFileName = "icons/rtc.ico";

    this.xdc_runtime_Text.elemName = "Text";
    this.xdc_runtime_Text.moduleName = "xdc.runtime.Text";
    this.xdc_runtime_Text.iconFileName = "icons/txt.ico";

/* Timestamp Providers Sub Group Modules */

    this.xdc_runtime_TimestampNull.elemName = "TimestampNull";
    this.xdc_runtime_TimestampNull.moduleName = "xdc.runtime.TimestampNull";
    this.xdc_runtime_TimestampNull.iconFileName = "icons/rtc.ico";

    this.xdc_runtime_TimestampStd.elemName = "TimestampStd";
    this.xdc_runtime_TimestampStd.moduleName = "xdc.runtime.TimestampStd";
    this.xdc_runtime_TimestampStd.iconFileName = "icons/rtc.ico";

/* Heaps Sub Group Modules */

    this.xdc_runtime_HeapMin.elemName = "HeapMin";
    this.xdc_runtime_HeapMin.moduleName = "xdc.runtime.HeapMin";
    this.xdc_runtime_HeapMin.iconFileName = "icons/mem.ico";

    this.xdc_runtime_HeapStd.elemName = "HeapStd";
    this.xdc_runtime_HeapStd.moduleName = "xdc.runtime.HeapStd";
    this.xdc_runtime_HeapStd.iconFileName = "icons/mem.ico";

/* Memory Management Group Modules */

    this.xdc_runtime_Memory.elemName = "Memory";
    this.xdc_runtime_Memory.moduleName = "xdc.runtime.Memory";
    this.xdc_runtime_Memory.iconFileName = "icons/mem.ico";

/* Gates Sub Group Modules */

    this.xdc_runtime_GateNull.elemName = "GateNull";
    this.xdc_runtime_GateNull.moduleName = "xdc.runtime.GateNull";
    this.xdc_runtime_GateNull.iconFileName = "icons/lck.ico";

/* Syncs Sub Group Modules */

    this.xdc_runtime_knl_SyncGeneric.elemName = "SyncGeneric";
    this.xdc_runtime_knl_SyncGeneric.moduleName = "xdc.runtime.knl.SyncGeneric";
    this.xdc_runtime_knl_SyncGeneric.iconFileName = "icons/sem.ico";

/* Sub Groups */

    this.systemProvidersGroup.elemName = "System Providers";
    this.systemProvidersGroup.moduleName = null;
    this.systemProvidersGroup.iconFileName = "icons/hst_fldr.ico";
    this.systemProvidersGroup.elemArray = [
        this.xdc_runtime_SysMin,
        this.xdc_runtime_SysStd
    ];

    this.timestampProvidersGroup.elemName = "Timestamp Providers";
    this.timestampProvidersGroup.moduleName = null;
    this.timestampProvidersGroup.iconFileName = "icons/rtc_fldr.ico";
    this.timestampProvidersGroup.elemArray = [
        this.xdc_runtime_TimestampNull,
        this.xdc_runtime_TimestampStd
    ];

    this.loggersGroup.elemName = "Loggers";
    this.loggersGroup.moduleName = null;
    this.loggersGroup.iconFileName = "icons/log_fldr.ico";
    this.loggersGroup.elemArray = [
        this.xdc_runtime_LoggerBuf,
        this.xdc_runtime_LoggerSys,
    ];

    this.heapsGroup.elemName = "Heaps";
    this.heapsGroup.moduleName = null;
    this.heapsGroup.iconFileName = "icons/mem_fldr.ico";
    this.heapsGroup.elemArray = [
        this.xdc_runtime_HeapMin,
        this.xdc_runtime_HeapStd,
    ];

    this.syncsGroup.elemName = "Syncs";
    this.syncsGroup.moduleName = null;
    this.syncsGroup.iconFileName = "icons/sem_fldr.ico";
    this.syncsGroup.elemArray = [
        this.xdc_runtime_knl_SyncGeneric,
    ];

    this.gatesGroup.elemName = "Gates";
    this.gatesGroup.moduleName = null;
    this.gatesGroup.iconFileName = "icons/lck_fldr.ico";
    this.gatesGroup.elemArray = [
        this.xdc_runtime_GateNull,
    ];

/* Groups */

    this.systemGroup.elemName = "System";
    this.systemGroup.moduleName = null;
    this.systemGroup.iconFileName = "icons/gbl_fldr.ico";
    this.systemGroup.elemArray = [
        this.xdc_cfg_Program,
        this.xdc_runtime_Main,
        this.xdc_runtime_Defaults,
        this.xdc_runtime_System,
        this.systemProvidersGroup,
        this.xdc_runtime_Startup
    ];

    this.diagnosticsGroup.elemName = "Diagnostics";
    this.diagnosticsGroup.moduleName = null;
    this.diagnosticsGroup.iconFileName = "icons/sdb.ico";
    this.diagnosticsGroup.elemArray = [
        this.xdc_runtime_Log,        
        this.loggersGroup,
        this.xdc_runtime_Diags,
        this.xdc_runtime_Assert,
        this.xdc_runtime_Error,
        this.xdc_runtime_Text,
        this.xdc_runtime_Timestamp,
	this.timestampProvidersGroup
    ];

    this.memoryGroup.elemName = "Memory Management";
    this.memoryGroup.moduleName = null;
    this.memoryGroup.iconFileName = "icons/mem_fldr.ico";
    this.memoryGroup.elemArray = [
        this.xdc_runtime_Memory,
        this.heapsGroup
    ];

    this.synchronizationGroup.elemName = "Synchronization";
    this.synchronizationGroup.moduleName = null;
    this.synchronizationGroup.iconFileName = "icons/sem_fldr.ico";
    this.synchronizationGroup.elemArray = [
        this.gatesGroup,
        this.syncsGroup
    ];

/* product */

    this.xdctoolsProduct.elemName = "XDCtools";
    this.xdctoolsProduct.moduleName = null;
    this.xdctoolsProduct.iconFileName = "icons/xdc.gif";
    this.xdctoolsProduct.elemArray = [
        this.systemGroup,
        this.diagnosticsGroup,
        this.memoryGroup,
        this.synchronizationGroup,
    ]; 
}

/*
 *  ======== getProductDescriptor ========
 */
function getProductDescriptor() 
{
    return this.xdctoolsProduct;
}
/*
 *  @(#) xdc.productview; 1,0,0,36; 2-22-2010 10:33:29; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

