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
//    print(this.$name + ".close() ...");

    if (Program.build.target.os == "WindowsCE") {
        //print(this.$name + " loading dsplink.gpp package...");
        var linkGppPkg = xdc.loadPackage('dsplink.gpp');
        linkGppPkg.Global.runtimeOS = linkGppPkg.Global.WINCE;

        /*
         *  Need Reg functions. Since this will cause osal.Global to be
         *  pulled in, we need to set osal.Global.os to osal.wince.Settings.
         *  Otherwise, we will end up linking in both osal_wince and osal_noOS
         *  libraries, giving multiply defined symbol errors.
         */

        /*
         *  Can't do this because many cfg files set osal.Global.runtimeEnv,
         *  and we can't do both.
         */
        var os = xdc.useModule('ti.sdo.ce.osal.wince.Settings');
        //xdc.useModule('ti.sdo.ce.osal.Global').os = os;

        /* Bring in the lad library */
        xdc.loadPackage('ti.dsplink.utils.lad');
    }
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var isa = prog.build.target.isa;
    var device = prog.cpu.deviceName;
    var suffix = prog.build.target.findSuffix(this);
    if (suffix == null) {
        return ("");
    }

    
    if (prog.build.target.os == "WindowsCE") {
        var name;

        /* device = DM6446, cpu = ARM */
        if (device.match(/^TMS320CDM6446$/) && isa.match(/^v4T$/i)) {
            name = "lib/" + this.profile + "/ladclient_6446";
        }

        /* device = TMS320C3430, OMAP3530, cpu = ARM */
        else if (device.match(/^TMS320C3430$|^OMAP3530$/)
                && isa.match(/^v5T$|^v6$|^v4T$/i)) {
            name = "lib/" + this.profile + "/ladclient_3530";
        }
    }
    else {
        /* "mangle" program build attrs into an appropriate directory name */
        var name = this.profile == "debug" ? "lib/debug/ladclient" :
            "lib/release/ladclient";
    }

    /* return the library name: name.a<arch> */
    var lib = name + ".a" + suffix;
    print("    will link with " + this.$name + ":" + lib);

    return (lib);
}
/*
 *  @(#) ti.dsplink.utils.ladclient; 1, 0, 0,239; 12-2-2010 21:18:40; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

