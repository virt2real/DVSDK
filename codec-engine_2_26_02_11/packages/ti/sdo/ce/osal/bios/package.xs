/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

/*
 *  ======== Package.close ========
 *  Close this package; optionally (re)set other config parameters in the
 *  model
 */
function close()
{
    trace(this.$name + ".close() ...");
    var prog = Program;
    var Settings = this.Settings;

    /* if undefined, take profile from the Settings module */
    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.ce.global.Settings').profile;
    }

    /* if the OS is DSP/BIOS, with or without dsplink, check for segment
     * names and assign default ones if left undefined by the user
     */
    /* get the names of all instances */
    var memInsts = $$legacy.prog.module("MEM").instances();

    /* record the name of the segment "DDR" or "DDR2" if found */
    var segmentNamedLikeDdr = null;
    for (var i = 0; i < memInsts.length; i++) {
        if (memInsts[i].name == "DDR" || memInsts[i].name == "DDR2" ||
            memInsts[i].name == "SDRAM") {
            segmentNamedLikeDdr = memInsts[i].name;
        }
    }

    var osalGlobal = xdc.module('ti.sdo.ce.osal.Global');

    if (osalGlobal.runtimeEnv != undefined) {
        /*
         *  If someone has modified the settings from the default values,
         *  and has also set osal.Global.runtimeEnv, print a warning.
         */
        var defaultTraceBufferSize = 32768;
        var defaultEnableLogging = true;
        var defaultLogName = "ti_sdo_ce_osal_LOG_Buffer";
        var defaultLogSize = 256;
        var defaultLogType = "circular";

        if (Settings.traceBufferSize != defaultTraceBufferSize) {
            warn(this.$name + ".close(). Since osal.Global.runtimeEnv has " +
                    "been set, use oasl.Global.traceBufferSize to set the " +
                    "trace buffer size. The current config value will not " +
                    "take effect.");
        }
        if (Settings.enableLogging != defaultEnableLogging) {
            warn(this.$name + ".close(). Since osal.Global.runtimeEnv has " +
                    "been set, use oasl.Global.enableLogging. " +
                    "The current config value will not take effect.");
        }
        if (Settings.logName != defaultLogName) {
            warn(this.$name + ".close(). Since osal.Global.runtimeEnv has " +
                    "been set, use oasl.Global.logName to set the log name." +
                    "The current config value will not take effect.");
        }
        if (Settings.logSize != defaultLogSize) {
            warn(this.$name + ".close(). Since osal.Global.runtimeEnv has " +
                    "been set, use oasl.Global.logSize to set the log size." +
                    "The current config value will not take effect.");
        }
        if (Settings.logType != defaultLogType) {
            warn(this.$name + ".close(). Since osal.Global.runtimeEnv has " +
                    "been set, use oasl.Global.logType to set the log type." +
                    "The current config value will not take effect.");
        }
        if (Settings.defaultMemSegId != null) {
            warn(this.$name + ".close(). Since osal.Global.runtimeEnv has " +
                    "been set, use oasl.Global.defaultMemSegId to set the " +
                    "default memory segment for allocation. The current " +
                    "config value will not take effect.");
        }
        if (Settings.logSeg != null) {
            warn(this.$name + ".close(). Since osal.Global.runtimeEnv has " +
                    "been set, use oasl.Global.logSeg to set the log memory " +
                    "segment. The current config value will not take effect.");
        }

        // If the user didn't assign these, use osal.Global config params.
        trace(this.$name + ".close() - Getting config param values from " +
             "ce.osal.Global.");
        if (Settings.defaultMemSegId == null) {
            /* User didn't set this, use osalGlobal's assignment as a backup */
            Settings.defaultMemSegId = osalGlobal.defaultMemSegId;
        }
        Settings.traceBufferSize = osalGlobal.traceBufferSize;
        Settings.enableLogging = osalGlobal.enableLogging;
        Settings.logName = osalGlobal.logName;
        Settings.logSize = osalGlobal.logSize;
        Settings.logType = osalGlobal.logType;
        Settings.logSeg = osalGlobal.logSeg;
    }

    /* if the user hasn't specified the default name, use the likely one */
    if (Settings.defaultMemSegId == null) {

        if (segmentNamedLikeDdr != null) {
            Settings.defaultMemSegId = segmentNamedLikeDdr;
            trace( "Note: ti.sdo.ce.osal.bios.defaultMemSegId is " +
                    "null, setting it to \""
                    + segmentNamedLikeDdr + "\"." );
        } else {
            throw("\nError: [from ti.sdo.ce.osal] " +
                    "your DSP configuration file (.cfg) does not " +
                    "specify which segment to use for default memory " +
                    "allocations. You must specify the line \"" +
                    "osal.bios.defaultMemSegId = '<memory segment name>';" +
                    "\" in your .cfg file, where <memory segment name> is " +
                    "a valid TCONF-defined BIOS MEM segment " +
                    "(typically one that contains all the static code/data)."
                  );
        }
    }

    /* now verify that all are correct */
    var found = false;
    for (var i = 0; i < memInsts.length; i++) {
        if (memInsts[i].name == Settings.defaultMemSegId) {
            found = true;
            break;
        }
    }
    if (!found) {
        throw "\nError: [from ti.sdo.ce.osal] field Settings.defaultMemSegId"
            + " is set to a non-existing BIOS MEM segment ('" +
            Settings.defaultMemSegId + "'). You must assign to this " +
            "filed a name of a valid TCONF-defined memory segment " +
            "(typically one that contains all the static code/data)."
            ;
    }

    /* for other segments left undefined, use the default segment */
    if (Settings.logSeg == null) {
        Settings.logSeg = Settings.defaultMemSegId;
    }

    /* if the OS is DSP/BIOS make sure this package is imported; otherwise
     * the generated linker command file will not be correct
     */
    xdc.loadPackage('ti.bios');
    xdc.useModule('ti.bios.utils.Load');

    /* get BIOS config object (so we can config BIOS) */
    var prog = config.boards()[0].cpus()[0].programs()[0];

    /* check if the user's .tcf still has HAL_init call for the old link */
    if ($$legacy.prog.module("GBL").USERINITFXN ==
            $$legacy.prog.extern("HAL_init")) {
        print( "Warning: your TCONF script sets GBL.USERINITFXN to " +
                "'HAL_init'; that setting is obsolete and will be " +
                "undone here in the OSAL package configuration. " +
                "To avoid this warning, please remove " +
                "GBL.CALLUSERINITFXN = 1; and " +
                "GBL.USERINITFXN = \"HAL_init\"; lines from your " +
                ".tcf script." );
        $$legacy.prog.module("GBL").USERINITFXN =
            $$legacy.prog.extern("FXN_F_nop");
    }

    /* Create LOG object for Socrates, if enabled and in a BIOS-based env. */
    if (Settings.enableLogging) {
        var name = Settings.logName;
        var bufSeg = Settings.logSeg;
        var log = $$legacy.prog.module("LOG").create(name);
        log.bufLen = Settings.logSize;
        log.logType = Settings.logType;
        log.bufSeg = $$legacy.prog.get(bufSeg);
        log.dataType = "printf";
        $$legacy.prog.module("LOG").TS = true; /* enable 8-word logs */

        // Must call prog.gen() to recreate the configuration model.
        $$legacy.prog.gen();
    }

    /*
     * Set up GT trace infrastructure here
     */
    var gt = xdc.useModule("ti.sdo.utils.trace.GT");

    /*
     * TODO: Set up gt's LOCKFXN and MALLOC/FREEFXN
     *       through a common file here
     *   gt.MALLOCFXN    = "GTConfig_memCalloc";
     *   gt.FREEFXN      = "GTConfig_memFree";
     *   gt.MALLOCFXN    = "GTConfig_malloc";
     *   gt.FREEFXN      = "GTConfig_free";
     */
    gt.MALLOCFXN    = "GTConfig_biosMemAlloc";
    gt.FREEFXN      = "GTConfig_biosMemFree";
    gt.PRINTFXN     = "GTConfig_sysPrintf";
    gt.TIDFXN       = "GTConfig_tskId";
    gt.ERRORFXN     = "GTConfig_sysPrintfError";
    gt.TIMEFXN      = "GTConfig_getTime";
    gt.LOCKFXN      = "GTConfig_semPend";
    gt.UNLOCKFXN    = "GTConfig_semPost";
    gt.INITFXN      = "GTConfig_biosInit";
}

/*
 *  ======== Package.validate ========
 *  Verify the config params for this package; called after close()
 */
function validate()
{
    //print(this.$name + ".validate() ...");
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var Settings = this.Settings;
    var platLib = "";
    var libs = new Array();
    var lib;
    var useLoadPWRM = 0;

    var suffix = prog.build.target.findSuffix(this);
    if (suffix == null) {
        return ("");
    }

    /* unfortunately, currently 2 ways to get the debug libs */
    if (Settings.debug || this.profile == "debug") {
        lib = "lib/osal_bios_debug" + ".a" + suffix;
        libs.push(lib);
        print("    will link with " + this.$name + ":" + lib);
    }
    else {
        lib = "lib/osal_bios" + ".a" + suffix;
        libs.push(lib);
        print("    will link with " + this.$name + ":" + lib);
    }

    if ($$legacy.prog.module("PWRM") !== undefined) {
        if ($$legacy.prog.module("PWRM").ENABLE == 1) {
            if ($$legacy.prog.module("PWRM").IDLECPU == 1) {
                useLoadPWRM = 1;
            }
        }
    }

    if (Settings.debug || this.profile == "debug") {
        if (useLoadPWRM) {
            lib = "lib/osal_bios_pwrm_debug" + ".a" + suffix;
        }
        else {
            lib = "lib/osal_bios_load_debug" + ".a" + suffix;
        }
        libs.push(lib);
        print("    will link with " + this.$name + ":" + lib);
    }
    else {
        if (useLoadPWRM) {
            lib = "lib/osal_bios_pwrm" + ".a" + suffix;
        }
        else {
            lib = "lib/osal_bios_load" + ".a" + suffix;
        }
        libs.push(lib);
        print("    will link with " + this.$name + ":" + lib);
    }

    return libs.join(";");
}


/*
 *  ======== getSects ========
 */
function getSects()
{
    /* there is a linker command file for BIOS flavors */
    return (this.$name.replace(/\./g, "/") + "/link.xdt");
}


/*
 *  ======== warn ========
 *  For warnings that we may not really want to print.
 */
function warn(msg)
{
    print("WARNING:  " + msg);
}

/*
 *  ======== trace ========
 */
function trace(msg)
{
//    print("TRACE:  " + msg);
}
/*
 *  @(#) ti.sdo.ce.osal.bios; 2, 0, 1,182; 12-2-2010 21:24:44; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

