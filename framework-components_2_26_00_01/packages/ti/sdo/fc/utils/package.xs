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
 *  ======== validate ========
 */
function validate()
{
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var os = Program.build.target.os;
    var isa = Program.build.target.isa;
    var dir = "lib/"; 
    var suffix  = Program.build.target.findSuffix(this);

    if (null == suffix) {
        return (null);
    } 

    var libs = new Array();

    libName = "rmm";

    libName += ".a" + suffix;

    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + libName ).exists()) {
        print(this.$name + ": Requested profile '" + this.profile + "' does "
                + "not exist.\n\tDefaulting to the 'release' profile");
 
       dir = "lib/release";
 
    }
    
    libs.push(dir + "/" + libName);

    libName = "smgr";

    libName += ".a" + suffix;

    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + libName ).exists()) {
        print(this.$name + ": Requested profile '" + this.profile + "' does "
                + "not exist.\n\tDefaulting to the 'release' profile");
 
       dir = "lib/release";
 
    }

    libs.push(dir + "/" + libName);

    var libName = "rmmp";
    
    libName += ".a" + suffix;

    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + libName ).exists()) {
        print(this.$name + ": Requested profile '" + this.profile + "' does"
        + " not exist.\n\tDefaulting to the 'release' profile");
        dir = "lib/release";
 
    }

    libs.push(dir + "/" + libName);

    /* The multiprocess libs required for Arm only (not dsp) */ 
    if (isa.match(/v5T/)) {
        libName = "smgrmp"; 
        libName += ".a" +  suffix;
     
        var dir = "lib/" + this.profile;

        if (!java.io.File(this.packageBase + dir + "/" + libName ).exists()) {
            print(this.$name + ": Requested profile '" + this.profile + "' does"
                + " not exist.\n\tDefaulting to the 'release' profile");
 
            dir = "lib/release";
 
        }
    
        libs.push(dir + "/" + libName);
    
        if (os  == "Linux") {

            libName = "shm";
            libName += ".a" +  suffix;
       
            var dir = "lib/" + this.profile;

            if (!java.io.File(this.packageBase + dir + "/" + libName).exists()){
                print(this.$name + ": Requested profile '" + this.profile + 
                        "' does not exist.\n\tDefaulting to the 'release' "
                        + "profile");
 
                dir = "lib/release";
 
            }
            libs.push(dir + "/" + libName);
        }
    }

    print("will link with " + libs.join(";"));

    return libs.join(";");
}

/*
 *  ======== getSects ========
 */
function getSects() {
   return (null);
}

/*
 * ======== close ========
 */
function close() {

    var isa = Program.build.target.isa;

    xdc.loadPackage("ti.xdais");

    var fc = xdc.useModule("ti.sdo.fc.global.Settings");
    if (null != fc.osalPackage) {
        xdc.loadPackage(fc.osalPackage);
    }

    if ((this.RMMP.debug) || (this.RMMP.trace) ||
            (this.SHM.debug) || (this.SHM.trace) ||
            (this.RMM.debug) || (this.RMM.trace) ||
            (this.SMGR.debug) || (this.SMGR.trace) ||
            (this.SMGRMP.debug) || (this.SMGRMP.trace)) {
        print(this + ": This module no longer supports the .debug "
                + "or the .trace config params. Set desired profile for all "
                + "FC modules as follows: "
                + "xdc.useModule\('ti.sdo.fc.global.Settings'\).profile = "
                + "\"debug\""
                + " or set profiles for individual packages like this: "
                + "xdc.loadPackage('" 
                + this + "').profile = \"debug\"\;"
                + " .\n\tWill default to the 'release' profile if not set.");
    } 

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }

    if (this.profile.match("trace")) {
        xdc.useModule("ti.sdo.utils.trace.GT");
    }

    if ((Program.build.target.os == undefined)  && (!isa.match(/v5T/))) {
        /* Assume bios */
        xdc.loadPackage("ti.bios");
    }
    
    xdc.loadPackage("ti.sdo.fc.memutils");
} 

/*
 *  @(#) ti.sdo.fc.utils; 1, 0, 2,286; 12-1-2010 17:26:08; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

