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
 *  ======== getLibs ========
 */
function getLibs(prog)
{

    var suffix = null;

    if ("findSuffix" in prog.build.target) {
        suffix = prog.build.target.findSuffix(this);
    }
    else {
        /* older XDCtools - not recommended, but we'll try to support it */
        suffix = prog.build.target.suffix;
    }

    if ((null == suffix) || (this.MEMUTILS.noLib == true)) {
        return (null);
    }

    /* If we're here, we have a valid suffix, and need to return a lib */

    var lib = "lib/" + this.profile + "/memutils";

    /* TODO - is there a better way to do this suffix check? */
    if ((this.MEMUTILS.noOS) || (suffix == "86U") || (suffix == "9t")) {
        lib += "_std";
    }

    lib += ".a" +  suffix;

    print("    will link with " + this.$name + ":" + lib);
    return (lib);
}


/*
 * ======== close ========
 */
function close()
{

    var isa = Program.build.target.isa;

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }

    if (this.profile.match("trace")) {
        xdc.useModule("ti.sdo.utils.trace.GT");
    }

    if (!this.MEMUTILS.noOS) {
        if ((Program.build.target.os == undefined) && (!isa.match(/v5T/))) {
            xdc.loadPackage("ti.bios");
        }
        else {
            if (Program.build.target.os == "Linux") {
                xdc.loadPackage("ti.sdo.linuxutils.cmem");
            }
        }
    }
}

/*
 *  @(#) ti.sdo.fc.memutils; 1, 0, 0,121; 12-1-2010 17:25:29; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

