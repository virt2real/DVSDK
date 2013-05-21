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
    if ((this.RMAN.useDSKT2 == false) && 
            ((this.RMAN.persistentAllocFxn == null ) || 
            (this.RMAN.persistentFreeFxn == null))) {
       throw("\n\n  RMAN Error: Config parameter useDSKT2 set to false and "
            + "valid persistentAllocFxn and persistentFreeFxn not set. "
            + "Please re-configure RMAN to either set useDSKT2 to true"
            + " or set valid persistentAllocFxn and persistentFreeFxn.\n");
    }
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var suffix = Program.build.target.findSuffix(this);
    var isa = Program.build.target.isa;

    if (null == suffix) {
        return (null);
    }

    var lib = "rman";
    lib += ".a" +  suffix;

    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + lib ).exists()) {

        print(this.$name + ": Requested profile '" + this.profile + "' does"
                + " not exist.\n\tDefaulting to the 'release' profile");

        dir = "lib/release";
    }

    print("    will link with " + this.$name + ":" + dir + "/" + lib);

    return (dir + "/" + lib);
}


/*
 * ======== close ========
 */
function close() {
    var isa = Program.build.target.isa;

    xdc.loadPackage("ti.xdais");

    xdc.loadPackage("ti.sdo.fc.ires");

    /* Unconditionally, establish dependency on nullresource */
    xdc.loadPackage("ti.sdo.fc.ires.nullresource");

    if ((this.RMAN.debug) || (this.RMAN.trace)) {
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

    if (this.profile.match("trace")) {
        xdc.useModule("ti.sdo.utils.trace.GT");
    }

    /* Required to load the LockMP functions required for Linux */
    var fc = xdc.useModule("ti.sdo.fc.global.Settings");
    if (null != fc.osalPackage) {
        xdc.loadPackage(fc.osalPackage);
    }

    if ( (this.RMAN.lockFxn != null) &&
            (this.RMAN.lockFxn != "DSKT2_acquireLock")) {
        print("Warning - RMAN has deprecated configuration parameter "
                + "\"lockFxn\" set to something other than DSKT2 functions.\n"
                + "Cooperative Preemption support will be turned off.\n"
                + "Please use RMAN.useDSKT2 flag instead of deprecated"
                + " configuration parameters: lockFxn, unlockFxn, setContextFxn"
                + ", getContextFxn, yieldFxn.\n");
        this.RMAN.useDSKT2 = false;
    }

    if ( (this.RMAN.unlockFxn != null) &&
            (this.RMAN.unlockFxn != "DSKT2_releaseLock")) {
        print("Warning - RMAN has deprecated configuration parameter "
            + "\"unlockFxn\" set to something other than DSKT2 functions.\n"
            + "Cooperative Preemption support will be turned off.\n"
            + "Please use RMAN.useDSKT2 flag instead of deprecated"
            + " configuration parameters: lockFxn, unlockFxn, setContextFxn,"
            + "getContextFxn, yieldFxn.\n");
        this.RMAN.useDSKT2 = false;
    }

    if ( (this.RMAN.getContextFxn != null) &&
            (this.RMAN.getContextFxn != "DSKT2_getContext")) {
        print("Warning - RMAN has deprecated configuration parameter "
            + "\"getContext\" set to something other than DSKT2 functions.\n"
            + "Cooperative Preemption support will be turned off. "
            + "Please use RMAN.useDSKT2 flag instead of deprecated"
            + " configuration parameters: lockFxn, unlockFxn, setContextFxn,"
            + "getContextFxn, yieldFxn.\n");
        this.RMAN.useDSKT2 = false;
    }

    if ( (this.RMAN.setContextFxn != null) &&
            (this.RMAN.setContextFxn != "DSKT2_setContext")) {
        print("Warning - RMAN has deprecated configuration parameter "
            + "\"setContext\" set to something other than DSKT2 functions.\n"
            + "Cooperative Preemption support will be turned off.\n"
            + "Please use RMAN.useDSKT2 flag instead of deprecated "
            + "configuration parameters: lockFxn, unlockFxn, setContextFxn,"
            + "getContextFxn, yieldFxn.\n");
        this.RMAN.useDSKT2 = false;
    }

    if ( (this.RMAN.yieldFxn != null) &&
            (this.RMAN.yieldFxn != "TSK_yield")) {
        print("Warning - RMAN has deprecated configuration parameter "
            + "\"yieldFxn\".\n"
            + "Cooperative Preemption support will be turned off.\n"
            + "Please use RMAN.useDSKT2 flag instead of deprecated "
            + "configuration parameters: lockFxn, unlockFxn, setContextFxn,"
            + "getContextFxn, yieldFxn.\n");
        this.RMAN.useDSKT2 = false;
    }

    if (this.RMAN.useDSKT2 == true) {

        //Check if the target is C64, DSKT2 works only for that !
        if ((isa != "64P") && (isa != "674")) {

            //Not DSP, well are the alloc/free Fxns set properly ?! 
            if ((this.RMAN.persistentAllocFxn == "null") || 
                    (this.RMAN.persistentFreeFxn == "null")) {
                //Nope, not set, error !
                throw("\n\n  RMAN Error: Config parameter useDSKT2 set to true "
                        + "for a non-DSP target. Please set this to false and "
                        + "configure RMAN.persistentAllocFxn and "
                        + "RMAN.persistentFreeFxn instead.");
            }
            else {
                //Set, print warning and proceed 
                print("Warning - RMAN.useDSKT2 was set to true for a non-DSP " +
                        "target, this will be set to FALSE and " +
                        "RMAN.persistentAllocFxn and persistentFreeFxn will be "
                        + "used instead."); 

                this.RMAN.useDSKT2 = false;
            }
        }
    }

    if (this.RMAN.useDSKT2 == true) {

        xdc.useModule("ti.sdo.fc.dskt2.DSKT2");

        if (this.RMAN.persistentAllocFxn != null) {
            print("Warning - RMAN.persistentAllocFxn was assigned and " +
                    "RMAN.useDSKT2 was set true.  Previous assignment " +
                    "will be overridden with DSKT2_allocPersistent.\n");
        }
        this.RMAN.persistentAllocFxn = "DSKT2_allocPersistent";

        if (this.RMAN.persistentFreeFxn != null) {
            print("Warning - RMAN.persistentFreeFxn was assigned and " +
                    "RMAN.useDSKT2 was set true.  Previous assignment " +
                    "will be overridden with DSKT2_freePersistent.\n");
        }
        this.RMAN.persistentFreeFxn = "DSKT2_freePersistent";
    }

}
/*
 *  @(#) ti.sdo.fc.rman; 2, 0, 0,207; 12-1-2010 17:25:37; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

