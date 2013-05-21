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

    /* if undefined, take profile from the Settings module */
    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.ce.global.Settings').profile;
    }

    xdc.useModule('ti.sdo.winceutils.cmem.CMEM');
    var osalGlobal = xdc.useModule('ti.sdo.ce.osal.Global');

    /*
     * Set up GT trace infrastructure here
     */
    var gt = xdc.useModule("ti.sdo.utils.trace.GT");

    /*
     * TODO: Set up gt's LOCKFXN and MALLOC/FREEFXN
     *       through a common file here
     */
    gt.MALLOCFXN    = "GTConfig_malloc";
    gt.FREEFXN      = "GTConfig_free";
    gt.PRINTFXN     = "GTConfig_printf"; //"GTConfig_tracePrintf";
    gt.TIDFXN       = "GTConfig_threadId";
    gt.ERRORFXN     = "GTConfig_error";
    gt.TIMEFXN      = "GTConfig_gettimeofday";
    gt.LOCKFXN      = "GTConfig_threadLock";
    gt.UNLOCKFXN    = "GTConfig_threadUnlock";
    gt.INITFXN      = "GTConfig_init";
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var lib;

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

    if (this.Settings.debug) {
        print(this.$name + ".Settings.debug is deprecated and will be ignored.");
    }

    lib = "lib/" + this.profile + "/osal_wince.a" + suffix;

    /* check for library existance */
    var file = new java.io.File(this.packageBase + '/' + lib);
    if (!file.exists()) {
        /* the preferred profile doesn't exist, try "release" */
        trace(this.$name + ":  Requested profile '" +
                this.profile + "' does not exist.\n\tDefaulting to " +
                "the 'release' profile");


        lib = "lib/release/osal_wince.a" + suffix;
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
 *  @(#) ti.sdo.ce.osal.wince; 1, 0, 0,82; 12-2-2010 21:25:05; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

