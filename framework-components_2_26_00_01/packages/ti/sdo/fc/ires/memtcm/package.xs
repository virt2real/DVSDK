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
 *  ======== validate ========
 */
function validate()
{
    /* TODO: validate the range of all the config params */
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var suffix = Program.build.target.findSuffix(this);

    if (suffix == null) {
        return (null);
    }

    var lib = "memtcm" ;
    lib += ".a" + suffix;

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
 *  ======== close ========
 */

function close() 
{

    xdc.loadPackage("ti.sdo.fc.ires");


    xdc.loadPackage("ti.sdo.linuxutils.cmem");
    xdc.loadPackage("ti.sdo.fc.utils");

    if (this.MEMTCM.cmemBlockId == undefined) {
        throw("\n\nMEMTCM: Did not set config parameter \"cmemBlockId\" to a valid"
                + " block. Set this to the CMEM block# that was used to insmod "
                + "the ARM TCM memory block\n"); 
    }
    
    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }
}

/*
 *  ======== getSects ========
 */
function getSects() {
   return (null);
}

/*
 *  @(#) ti.sdo.fc.ires.memtcm; 1, 0, 0,45; 12-1-2010 17:25:17; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

