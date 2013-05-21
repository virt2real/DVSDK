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

    /* sanity check that we're in the config model - else we crash! */
    if (xdc.om.$name != "cfg") {
        /* sanity check that we're in the config model - else we crash! */
        return;
    }

    var Settings = this.Settings;

    /* establish dependency on OSAL */
    var osalGlobal = xdc.useModule('ti.sdo.ce.osal.Global');

    if (Program.build.target.name.match(/C64P|C674/)) {
        /* establish dependency on DSKT2 */
        var dskt2 = xdc.useModule('ti.sdo.fc.dskt2.DSKT2');
    }

    // ce/ServerDataSheet.html.xdt needs to have the dman3 package
    // loaded (otherwise we get the $$genflg error. Don't load the
    // module, or we'll get a link error _DMAN3_heapInternal,
    // _DMAN3_heapExternal undefined.  We need to bring in the
    // acpy3 library since some server cfg's configure DMAN3, but
    // don't use the ACPY3 module. Unfortunately, DMAN3_CE_init()
    // (coming from DMAN3.xdt) calls ACPY3_init().  Note, this
    // incorrect dependency is filed as SDSCM00003358
    try {
        xdc.loadPackage('ti.sdo.fc.dman3');
        xdc.loadPackage('ti.sdo.fc.acpy3');
    }
    catch (e) {
    }

    if (Settings.useIdma3) {
        /* establish dependency on DMAN3, ACPY3 */
        xdc.useModule('ti.sdo.fc.dman3.DMAN3');
        xdc.useModule('ti.sdo.fc.acpy3.ACPY3');
    }

    if (Settings.useIres) {
        /* establish dependency on RMAN */
        var rman = xdc.useModule('ti.sdo.fc.rman.RMAN');
        var mp = xdc.useModule('ti.sdo.fc.global.Settings').multiProcess;

        var sem = (mp == true) ? "SemMP" : "Sem";

        if (rman.semCreateFxn == null) {
            trace(this.$name + ".close(): RMAN.semCreateFxn null, setting " +
                    "to " + sem + "_create");
            rman.semCreateFxn = sem + "_create";
        }
        if (rman.semDeleteFxn == null) {
            trace(this.$name + ".close(): RMAN.semDeleteFxn null, setting " +
                    "to " + sem + "_delete");
            rman.semDeleteFxn = sem + "_delete";
        }
        if (rman.semPendFxn == null) {
            trace(this.$name + ".close(): RMAN.semPendFxn null, setting " +
                    "to " + sem + "_pend");
            rman.semPendFxn = sem + "_pend";
        }
        if (rman.semPostFxn == null) {
            trace(this.$name + ".close(): RMAN.semPostFxn null, setting " +
                    "to " + sem + "_post");
            rman.semPostFxn = sem + "_post";
        }

        if (!Program.build.target.name.match(/C64P|C674/)) {
            var GROUPUTILS =
                xdc.useModule('ti.sdo.fc.ires.grouputils.GROUPUTILS');
            if (GROUPUTILS.scratchFxnPackage == null) {
                print(this.$name + ".close(): Setting GROUPUTILS...");
                GROUPUTILS.scratchFxnPackage  = "ti.sdo.ce.alg"; 
                GROUPUTILS.lockScratchGroupFxn = "Algorithm_acquireLock"; 
                GROUPUTILS.unlockScratchGroupFxn = "Algorithm_releaseLock"; 
            }
        }
    }
}


/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var lib = "";

    if ("findSuffix" in prog.build.target) {
        var suffix = prog.build.target.findSuffix(this);
        if (suffix == null) {
            return ("");
        }
    }
    else {
        throw(this.$name + " requires a newer version of XDCtools.\n" +
                "\tPlease see the release notes for details.");
    }

    if (prog.build.target.name.match(/C64P|C674/)) {
        lib = "lib/" + this.profile + "/Algorithm_BIOS.a" + suffix;

        if (!java.io.File(this.packageBase + lib).exists()) {
            /* the suggested profile doesn't exist, try "release" */
            trace(this.$name + ":  Requested profile '" +
                    this.profile + "' does not exist.\n\tDefaulting to " +
                    "the 'release' profile");

            lib = "lib/release/Algorithm_BIOS.a" + suffix;
        }
    }
    else {
        lib1 = "lib/" + this.profile + "/Algorithm_noOS.a" + suffix;
        lib2 = "lib/" + this.profile + "/alg.a" + suffix;

        /* Just test for lib 1 rather than both */
        if (!java.io.File(this.packageBase + lib1).exists()) {
            /* the suggested profile doesn't exist, try "release" */
            trace(this.$name + ":  Requested profile '" +
                    this.profile + "' does not exist.\n\tDefaulting to " +
                    "the 'release' profile");

            lib1 = "lib/release/Algorithm_noOS.a" + suffix;
            lib2 = "lib/release/alg.a" + suffix;
        }

        /* return both libs */
        lib = lib1 + ";" + lib2;
    }

    /* return the library name: name.a<arch> */
    print("    will link with " + this.$name + ":" + lib);

    return (lib);
}

function trace(str)
{
//    print(str);
}
/*
 *  @(#) ti.sdo.ce.alg; 1, 0, 1,191; 12-2-2010 21:18:42; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

