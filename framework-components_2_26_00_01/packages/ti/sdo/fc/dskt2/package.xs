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

function su(segName) { /* "strip underscore" */
        return (segName.charAt(0) == "_") ? segName.substr( 1 ) : segName;
}


/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var suffix = Program.build.target.findSuffix(this);

    if (null == suffix) {
        return (null);
    }

    var libs = "dskt2";

    libs += ".a" + suffix;

    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + libs ).exists()) {
        print(this.$name + ": Requested profile '" + this.profile + "' does "
                + "not exist.\n\tDefaulting to the 'release' profile");

       dir = "lib/release";

    }

    print("    will link with " + this.$name + ":" + dir + "/" + libs);
    return (dir + "/" + libs);
}

/*
 *  ======== getSects ========
 */
function getSects() {
   if (this.DSKT2.$used) {
       return (this.$name.replace( /\./g, "/" ) + "/DSKT2.link.xdt");
   }

   return (null);
}

/*
 * ======== close ========
 */
function close() {

    xdc.loadPackage('ti.bios');

    xdc.loadPackage("ti.xdais");

    if ((this.DSKT2.debug) || (this.DSKT2.trace)) {
        print(this + ": This module no longer supports the .debug "
                + "or the .trace config params. Set desired profile for all "
                + "FC modules as follows: "
                + "xdc.useModule\('ti.sdo.fc.global.Settings'\).profile = "
                + "\"debug\""
                + " or set profiles for individual packages like this: "
                + "xdc.loadPackage('"
                + this + "').profile = \"debug\"\;"
                + " .\n\tWill default the 'release' profile, if no other set");
    }

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }

    if (this.profile.search("trace")) {
        xdc.useModule("ti.sdo.utils.trace.GT");
    }
}

/*
 * ======== validate ========
 * TODO: Make separate module for the check below in validate
 *       (verifyValidBiosHeap). Can be used to check DMAN3.heapInternal and
 *       DMAN3.heapExternal as well.
 */
function validate() {

    var list = new Array();
    var memHeaps = new Array();
    var j = 0;

    if ($$legacy.prog.module("MEM") == undefined) {
        throw("DSKT2 validation failed - DSP/BIOS is not configured " +
            "correctly");
    }

    var memObjs = $$legacy.prog.module("MEM").instances();

    for (i = 0; i < memObjs.length; i++) {
        if (memObjs[i].createHeap == true) {
            if (memObjs[i].enableHeapLabel == true) {
                memHeaps[j] = su(memObjs[i].heapLabel.name);
                j++;
            }
            memHeaps[j] = memObjs[i].name;
            j++;
        }
    }

    list[0] = su(this.DSKT2.DARAM0);
    list[1] = su(this.DSKT2.DARAM1);
    list[2] = su(this.DSKT2.DARAM2);
    list[3] = su(this.DSKT2.SARAM0);
    list[4] = su(this.DSKT2.SARAM1);
    list[5] = su(this.DSKT2.SARAM2);
    list[6] = su(this.DSKT2.ESDATA);
    list[7] = su(this.DSKT2.IPROG);
    list[8] = su(this.DSKT2.EPROG);
    list[9] = su(this.DSKT2.DSKT2_HEAP);


    var returnVal  = checkSegForHeap(list,memHeaps);

    if (returnVal < 10) {
        var memorySeg;
        switch (returnVal) {
            case 0:
                memorySeg = "DARAM0";
                break;
            case 1:
                memorySeg = "DARAM1";
                break;
            case 2:
                memorySeg = "DARAM2";
                break;
            case 3:
                memorySeg = "SARAM0";
                break;
            case 4:
                memorySeg = "SARAM1";
                break;
            case 5:
                memorySeg = "SARAM2";
                break;
            case 6:
                memorySeg = "ESDATA";
                break;
            case 7:
                memorySeg = "IPROG";
                break;
            case 8:
                memorySeg = "EPROG";
                break;
            case 9:
                memorySeg = "DSKT2_HEAP";
                break;
        }

        throw("\n\n DSKT2 configuration Error: Memory space " + memorySeg + " is configured to \"" + list[returnVal] + "\", which is not a valid heap. Please reconfigure DSKT2." + memorySeg + " or to a valid heap or enable heap creation in \"" + list[returnVal] + "\".\n");
    }
}

function checkSegForHeap(list,memHeaps) {

    var found = 10;

    for (j = 0; j < list.length; j++) {
        for (i = 0; i < memHeaps.length; i++) {
            if (list[j] == memHeaps[i]) {
                break;
            }
        }
        if (i == memHeaps.length) {
            found = j;
            return (found);
        }
    }
    return (found);
}
/*
 *  @(#) ti.sdo.fc.dskt2; 1, 0, 4,300; 12-1-2010 17:24:36; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

