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
    var ipc = this.Ipc;
    var prog = Program;

    /* if undefined, take profile from the Settings module */
    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.ce.global.Settings').profile;
    }

    // This module requires osal.Global
    var osalGlobal = xdc.useModule('ti.sdo.ce.osal.Global');

    //print(this.$name + " loading dsplink.gpp package...");
    var linkGppPkg = xdc.loadPackage('dsplink.gpp');

    // If osalGlobal.os has been configured, determine whether it is
    // WinCE or Linux.
    var osPkg = null;
    if (osalGlobal.os != undefined) {
        osPkg = osalGlobal.os.$name;
        osPkg = osPkg.substring(0, osPkg.lastIndexOf("."));
        //print("os package name: " + osPkg);
    }

    if ((osalGlobal.runtimeEnv == osalGlobal.WINCE) ||
        (osalGlobal.runtimeEnv == osalGlobal.DSPLINK_WINCE) ||
            (osPkg == "ti.sdo.ce.osal.wince")) {
        xdc.useModule('ti.sdo.ce.osal.wince.Settings');

        linkGppPkg.Global.runtimeOS = linkGppPkg.Global.WINCE;

        /* load CMEM as well - TODO: do we depend on CMEM in this pkg? */
        //    print(this.$name + " loading cmem package...");
        xdc.loadPackage('ti.sdo.winceutils.cmem');
    }
    else {
        xdc.useModule('ti.sdo.ce.osal.linux.Settings');

        linkGppPkg.Global.runtimeOS = linkGppPkg.Global.LINUX;

        /* load CMEM as well - TODO: do we depend on CMEM in this pkg? */
        //    print(this.$name + " loading cmem package...");
        xdc.loadPackage('ti.sdo.linuxutils.cmem');
    }

    if ((osalGlobal.runtimeEnv == osalGlobal.WINCE) ||
            (osalGlobal.runtimeEnv == osalGlobal.DSPLINK_WINCE) ||
            (osalGlobal.runtimeEnv == osalGlobal.DSPLINK_LINUX)) {

        /*
         *  The app has used osal.Global.runtimeEnv to set the OS, so copy
         *  the dsplink settings from osal global.
         */
        ipc.armCommMsgSize = osalGlobal.armCommMsgSize;
        ipc.armCommNumMsgs = osalGlobal.armCommNumMsgs;
        ipc.commLocateRetries = osalGlobal.commLocateRetries;
        ipc.useLinkArbiter = osalGlobal.useLinkArbiter;
    }

    /* if unset by application config script, set default value here */
    if (ipc.usePowerManagement == undefined) {
        if (Program.cpu.deviceName.match(/^TMS320C3430$|^OMAP[23]530$/)) {
            ipc.usePowerManagement = true;
        }
        else {
            ipc.usePowerManagement = false;
        }
    }

    /* Optionally load and configure power management module */
    if (ipc.usePowerManagement) {
        var power = null;

        if (Program.cpu.deviceName.match(/^TMS320CDM6441$/)) {
            power = xdc.useModule('ti.bios.power.TMS320CDM6441GPP');
        }
        else if (Program.cpu.deviceName.match(/^TMS320CDM6446$/)) {
            power = xdc.useModule('ti.bios.power.TMS320CDM6446GPP');
        }
        else if (Program.cpu.deviceName.match(/^OMAP2530$/)) {
            power = xdc.useModule('ti.bios.power.OMAP2530GPP');
        }
        else if (Program.cpu.deviceName.match(/^TMS320C3430$/)) {
            power = xdc.useModule('ti.bios.power.TMS320C3430GPP');
        }
        else if (Program.cpu.deviceName.match(/^OMAP3530$/)) {
            power = xdc.useModule('ti.bios.power.OMAP3530GPP');
        }
        else {
            print("Warning: GPP ti.bios.power doesn't support: " +
                Program.cpu.deviceName + "\n");
        }

        if (power != null) {
            power.opersys = power.Opersys_Linux;
            power.transport = power.Transport_Link_Linux;
        }
    }

    /* optionally load the LAD communication wrapper module */
    if (ipc.useLinkArbiter) {
        var lad = xdc.loadPackage('ti.dsplink.utils.ladclient');
    }

//    print(this.$name + ".close() done!");
}

/*
 *  ======== Package.validate ========
 *  Verify the config params for this package; called after close()
 */
function validate()
{
    var settings = this.Ipc;
    for (var iserver = 0; iserver < settings.linkConfigs.length; iserver++ ) {
        var linkConfig = settings.linkConfigs[iserver];

        if ((linkConfig.linkCfg.doPowerControl == true) &&
            (linkConfig.linkCfg.dspManagement == settings.None)) {

            print(this.$name + ".validate() ...");
            throw "Error: invalid combination of doPowerControl=true and " +
                "dspManagement=None";
        }
    }
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var lib = "";
    var device = prog.cpu.deviceName;
    var isa = prog.build.target.isa;

    var suffix = prog.build.target.findSuffix(this);
    if (suffix == null) {
        return ("");
    }

    /* device = DM6446, cpu = ARM */
    if (device.match(/^TMS320CDM6446$/) && isa.match(/^v5T$|^v6$|^v4T$/i)) {
        lib = "lib/" + this.profile + "/ipc_dsplink_6446";
    }

    /* device = DM357, cpu = ARM */
    else if (device.match(/^TMS320DM357$/) && isa.match(/^v5T$|^v6$/i)) {
        lib = "lib/" + this.profile + "/ipc_dsplink_357";
    }

    /* device = DM6467, cpu = ARM */
    else if (device.match(/^TMS320CDM6467$/) && isa.match(/^v5T$|^v6$/i)) {
        lib = "lib/" + this.profile + "/ipc_dsplink_6467";
    }

    /* device = OMAPL137, cpu = ARM */
    else if (device.match(/^OMAPL137$/) && isa.match(/^v5T$|^v6$/i)) {
        lib = "lib/" + this.profile + "/ipc_dsplink_137";
    }

    /* device = OMAPL138, cpu = ARM */
    else if (device.match(/^OMAPL138$/) && isa.match(/^v5T$|^v6$/i)) {
        lib = "lib/" + this.profile + "/ipc_dsplink_138";
    }

    /* device = TMS320C2430, OMAP2530, cpu = ARM */
    else if (device.match(/^TMS320C2430$|^OMAP2530$/)
        && isa.match(/^v5T$|^v6$/i)) {
        lib = "lib/" + this.profile + "/ipc_dsplink_2530";
    }

    /* device = TMS320C3430, OMAP3530, cpu = ARM */
    else if (device.match(/^TMS320C3430$|^OMAP3530$/)
        && isa.match(/^v5T$|^v6$|^v4T$/i)) {
        lib = "lib/" + this.profile + "/ipc_dsplink_3530";
    }

    /* empty lib means this package has nothing to contribute */
    if (lib != "") {

        /* .findSuffix found a compatible library */
        lib += ".a" + suffix;

        /* return the library name: name.a<arch> */
        print("    will link with " + this.$name + ":" + lib);
    }

    return (lib);
}
/*
 *  @(#) ti.sdo.ce.ipc.dsplink; 2, 0, 1,182; 12-2-2010 21:24:24; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

