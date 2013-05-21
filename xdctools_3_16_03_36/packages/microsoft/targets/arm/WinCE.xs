/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== WinCE.compile ========
 */
function compile(goal) {

    if (this.projectRoot == undefined) {
        throw new Packages.xdc.services.global.XDCException(
            "xdc.bld.TARGET_CONFIG_ERROR", "The parameter 'projectRoot' must be"
            + " defined for the target microsoft.targets.arm.WinCE.");
    }

    if (goal.opts.incs != undefined) {
        goal.opts.incs += "-I" + this.projectRoot + "/cesysgen/sdk/inc";
    }
    else {
        goal.opts.incs = "-I" + this.projectRoot + "/cesysgen/sdk/inc";
    }

    return (this.$super.compile.$fxn.call(this, goal));
}

/*
 *  ======== WinCE.link ========
 */
function link(goal) {

    var entry;
    switch (this.entryPoint) {
        case this.mainCRTStartup:
            entry = " -entry:mainCRTStartup";
            break;
        case this.WinMainCRTStartup:
            entry = " -entry:WinMainCRTStartup";
            break;
        case this._DllMainCRTStartup:
            entry = " -entry:_DllMainCRTStartup";
            break;
        default:
            entry = "";
            break;
    }
    this.lnkOpts.suffix += entry;

    /* Set up WinCE profiles to include the right lib directories */
    if (this.projectRoot == undefined) {
        throw new Packages.xdc.services.global.XDCException(
            "xdc.bld.TARGET_CONFIG_ERROR", "The parameter 'projectRoot' must be"
            + " defined for the target microsoft.targets.arm.WinCE.");
    }

    var libDir = "/retail";
    if (goal.profile == "debug") {
        libDir = "/debug";
    }

    this.lnkOpts.prefix = "-libpath:" + this.projectRoot + "/cesysgen/sdk/lib/"
        + this.sysGenIsa + libDir + " " + this.lnkOpts.prefix;

    return (this.$super.link.$fxn.call(this, goal));

}
/*
 *  @(#) microsoft.targets.arm; 1, 0, 0, 0,140; 2-24-2010 16:24:11; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

