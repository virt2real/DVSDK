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
 * */
/*
 *  ======== package.xs ========
 */

/* No libs in this package */
function getLibs(prog)
{
    var lib = "rmanExample";
    var suffix = Program.build.target.findSuffix(this);

    if (null == suffix) {
        return (null);
    }

    var dir = "lib/" + this.profile;
    lib += ".a" + suffix;

    if (!java.io.File(this.packageBase + dir + "/" + lib ).exists()) {

        print(this.$name + ": Requested profile '" + this.profile + "' does"
                + " not exist.\n\tDefaulting to the 'release' profile");

        dir = "lib/release";
    }


    print("    will link with " + this.$name + ":" + dir + "/" + lib);
    return (dir + "/" + lib);
}

function close() {

    var isa = Program.build.target.isa; 

    if (isa.match(/x86/)) {

        /* The ARM 9t based implementation requires  
        /* The implementation of EDMA requires Shared memory from utils */
        xdc.loadPackage("ti.sdo.fc.utils");
    }

    if ((this.EXAMPLE.debug) || (this.EXAMPLE.trace)) {
        print(this + ": This module no longer supports the .debug "
                + "or the .trace config params. Set desired profile for all "
                + "FC modules as follows: "
                + "xdc.useModule\('ti.sdo.fc.global.Settings'\).profile = "
                + "\"debug\""
                + " or set profiles for individual packages like this: "
                + "xdc.loadPackage('"
                + this + "').profile = \"debug\"\;"
                + " .\n\tDefaulting to the 'release' profile");
    }

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }

}

function initializeGrouputilsWithAlgorithm(implementationPackage)
{
    print("Someone one called me !!\n");
    GUTILS = xdc.useModule("ti.sdo.fc.ires.grouputils.GROUPUTILS");

    GUTILS.lockScratchGroupFxn = "Algorithm_acquireLock";
    GUTILS.unlockScratchGroupFxn = "Algorithm_releaseLock";
    GUTILS.scratchFxnPackage = "ti.sdo.fc.rman.examples";
}
/*
 *  @(#) ti.sdo.fc.rman.examples; 1, 0, 0,123; 12-1-2010 17:25:37; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

