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

    /* if undefined, take profile from the Settings module */
    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.ce.global.Settings').profile;
    }

    /* establish dependency on XDAIS and NODE since we #include their headers */
    xdc.loadPackage('ti.xdais');
    xdc.loadPackage('ti.sdo.ce.node');

    /* if there's a Server in the system, we need the NODE module */
    if (this.Server.$used) {
        xdc.useModule('ti.sdo.ce.node.NODE');
    }
    this.Server.close();
    this.Engine.close();

    var osalGlobal = xdc.useModule('ti.sdo.ce.osal.Global');

    /*
     *  CE requires ipc to be set (CERuntime_init() calls Processor_init()
     *  and Comm_init()). If ce.ipc.Settings.ipc has not been set, try to
     *  set it here.
     */
    var ipcSettings = xdc.useModule('ti.sdo.ce.ipc.Settings');
    if (ipcSettings.ipc == undefined) {
        var ipcName = null;

        /*
         *  If osal.Global.runtimeEnv has been set, use that to
         *  determine which ipc to use. (Note: There is no WINCE only
         *  ipc).
         */
        if (osalGlobal.runtimeEnv == osalGlobal.WINCE) {
            /* Use noOS ipc, or async tests will not build for WinCE. */
            ipcName = "ti.sdo.ce.ipc.noOS.Ipc";
        }
        else if ((osalGlobal.runtimeEnv == osalGlobal.DSPLINK_WINCE) ||
                (osalGlobal.runtimeEnv == osalGlobal.DSPLINK_LINUX)) {
            ipcName = "ti.sdo.ce.ipc.dsplink.Ipc";
        }
        else if (osalGlobal.runtimeEnv == osalGlobal.DSPLINK_BIOS) {
            ipcName = "ti.sdo.ce.ipc.bios.Ipc";
            xdc.useModule('ti.sdo.ce.ipc.dsplink.dsp.Settings');
        }
        else if (osalGlobal.runtimeEnv == osalGlobal.DSPBIOS) {
            ipcName = "ti.sdo.ce.ipc.bios.Ipc";
        }
        else if (osalGlobal.runtimeEnv == osalGlobal.LINUX) {
            ipcName = "ti.sdo.ce.ipc.linux.Ipc";
        }

        if (ipcName != null) {
            ipcSettings.ipc = xdc.useModule(ipcName);
        }
        else {
            /*
             *  Neither osal.Global.runtimeEnv nor ipc.Settings.ipc have
             *  been set. Try to figure out which ipc to plug in based on
             *  target os or name.
             */
            if (prog.build.target.os == "Linux") {
                // NOTE: Engine.close() would have already set ipc to dsplink
                // if there were remote algorithms, so we wouldn't be here
                // in that case.
                ipcName = "ti.sdo.ce.ipc.linux.Ipc";
            }
            else {
                // Q: what makes a DSP target? A: name starts with "C".
                // may not be true in the future, but this is just to
                // forgive those who didn't set ipc.Settings.ipc anyway.
                if ((prog.build.target.name + "").match(/^C/) != null) {
                    ipcName = "ti.sdo.ce.ipc.bios.Ipc";

                    if (osalGlobal.runtimeEnv == osalGlobal.DSPLINK_BIOS) {
                        // Bring in this module for DSPLink
                        xdc.useModule('ti.sdo.ce.ipc.dsplink.dsp.Settings');
                    }
                }
                else {
                    ipcName = "ti.sdo.ce.ipc.noOS.Ipc";
                }
            }

            /*
             *  Warn the user about which ipc we're plugging in.
             */
            warn(this.$name + ".close()- " +
                    "WARNING: Your application .cfg script does not specify " +
                    "the ipc for this engine. Will set to *** " + ipcName +
                    " ***. You should set the ipc in your cfg file, if this " +
                    "is not what you want. eg, Add the following to your " +
                    ".cfg script: ");
            warn("var ipcSettings = xdc.useModule(\'ti.sdo.ce.ipc.Settings\');");
            warn("ipcSettings.ipc = xdc.useModule(\'" + ipcName + "\');");

            warn("Setting ipc to " + ipcName);
            ipcSettings.ipc = xdc.useModule(ipcName);
        }
    }

    /* unconditionally establish a dependency on 'ti.sdo.ce.alg' */
    var algSettings = xdc.useModule('ti.sdo.ce.alg.Settings');

    // For all local algorithms, set algSettings.groupUsed[i] = true, if the
    // alg's groupId is i.
    var engines = this.Engine.$instances;
    //print(this.$name + ".close(): Num engines = " + engines.length);
    for (var i = 0; i < engines.length; i++) {
        var eng = engines[i];
        var algs = eng.algs;

        //print(eng.name + ": Num algs = " + algs.length);
        for (var j = 0; j < algs.length; j++) {
            var alg = algs[j];
            if (alg.local) {
                if (algs[j].groupId == undefined) {
                    //print("Local alg " + alg.name + " groupId undefined.");
                }
                if ((alg.groupId >= 0) &&
                         (alg.groupId < algSettings.MAXGROUPID)) {
                    //print("Setting alg.Setting.groupUsed[" + alg.groupId +
                    //        "] to true");
                    algSettings.groupUsed[alg.groupId] = true;
                }
            }
        }
    }

    if (this.Engine.usesIDMA3()) {
        trace("THIS APP USES IDMA3 AND MUST BE BUILT WITH FC");
        algSettings.useIdma3 = true;
    }
    else {
        algSettings.useIdma3 = false;
    }

    if (this.Engine.usesIRES()) {
        trace("THIS APP USES IRES AND MUST BE BUILT WITH FC");
        algSettings.useIres = true;
    }
    else {
        algSettings.useIres = false;
    }

    xdc.loadPackage('ti.sdo.ce.utils.xdm');

    xdc.useModule('ti.sdo.ce.Settings');

    if (this.Server.traceBufferSize != 0) {
        var osalGlobal = xdc.useModule( 'ti.sdo.ce.osal.Global' );
        osalGlobal.traceBufferSize = this.Server.traceBufferSize;

        print( "\nWarning: [ti.sdo.ce/package.xs] Configuring server's trace " +
               "buffer size by writing to Server's traceBufferSize field " +
               "is being deprecated; please set the server trace buffer size " +
               "by setting the traceBufferSize field in the " +
               "ti.sdo.ce.osal.Global module (e.g.: " +
               "xdc.useModule('ti.sdo.ce.osal.Global').traceBufferSize = " +
               this.Server.traceBufferSize + "; ) to avoid this warning and " +
               "a possible error with the future releases of Codec Engine. " );
    }
}

/*
 *  ======== Package.validate ========
 *  Verify the config params for this package; called after close()
 */
function validate()
{
    trace(this.$name + ".validate() ...");

    this.Server.validate();
    this.Engine.validate();
}

/*
 *  ======== Package.init ========
 *  Initialize this package.
 */
function init ()
{
    trace(this.$name + ".init() ...");

    xdc.useModule('ti.sdo.ce.CERuntime');
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var suffix = prog.build.target.findSuffix(this);
    if (suffix == null) {
        trace("Unable to find a supported suffix!");
        return ("");
    }

    /* "mangle" program build attrs into an appropriate directory name */
    var name = this.profile == "debug" ? "lib/debug/ce" : "lib/release/ce";

    /* return the library name: name.a<arch> */
    var lib = name + ".a" + suffix;
    print("    will link with " + this.$name + ":" + lib);

    return (lib);
}

/*
 *  ======== warn ========
 *  For warnings that we may not really want to print. eg, for configurations
 *  with osal.Global.runtimeEnv set istead of osal.Global.os, or if the app
 *  .cfg has not configured ce.ipc.Settings.
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
 *  @(#) ti.sdo.ce; 1, 0, 6,432; 12-2-2010 21:19:09; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

