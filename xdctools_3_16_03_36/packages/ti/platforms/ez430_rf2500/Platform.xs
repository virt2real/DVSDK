/* 
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */
/*
 *  ======== Platform.xs ========
 *! 17-Nov-2009 sg      Added use of Boot module.
 */

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    xdc.useModule('ti.catalog.msp430.init.Boot').watchdogAddress = 0x120;
    xdc.useModule('ti.catalog.msp430.init.Boot').disableWatchdog = true;
    xdc.useModule('ti.catalog.msp430.init.Boot').configureDCO = false;
}

/*
 *  ======== Platform.getCpuDataSheet ========
 *  This Platform's implementation xdc.platform.IPlatform.getCpuDataSheet.
 *
 *  Return the xdc.platform.ICpuDataSheet.Instance object that corresponds
 *  to the device that runs executables loaded on the specified cpuId.
 */
function getCpuDataSheet(cpuId)
{
    var Utils = xdc.useModule('xdc.platform.Utils');
    return (Utils.getCpuDataSheet(this.$private.cpuAttrs));
}

/*
 *  ======== Platform.getExeContext ========
 *  This Platform's implementation xdc.platform.IPlatform.getExeContext.
 *
 *  Return the xdc.platform.IExeContext.Instance object that will run the
 *  specified program prog.
 */
function getExeContext(prog)
{
    var Utils = xdc.module("xdc.platform.Utils");

    /* create a default ExeContext execution context */
    var ExeContext = xdc.useModule('xdc.platform.ExeContext');
    var cpu = ExeContext.create(this.$private.cpuAttrs, this.$module.BOARD);

    /* Set the initial memory map from the cpu datasheet. */
    cpu.memoryMap = Utils.assembleMemoryMap(cpu, this);

    /* check for the overlap in the memory map */
    var overlap = Utils.checkOverlap(cpu.memoryMap);

    if (overlap != null) {
        this.$module.$logError("Memory objects " + overlap + " overlap", this,
            overlap);
    }

    /* seal the cpu object so script can't accidently modify it */
    Utils.checkDefaults(this, cpu.memoryMap);
    this.$seal();

    return (cpu);
}

/*
 *  ======== Platform.getExecCmd ========
 *  Return the command necessary to load and run prog on this platform
 */
function getExecCmd(prog)
{
    var os = environment["xdc.hostOS"];
    if (os == "Windows") {
        var prefix = '';
        var suffix = '\n';
        if (this.dssPath != null) {
            prefix = '\"set DEBUGSERVER=' + this.dssPath + '&&';
            suffix = '\"\n';
        }

        return ("cmd /c " +  prefix + this.$package.packageBase + "/load.bat "
                + prog.name + suffix);
    }

    return ("$(SHELL) " + this.$package.packageBase + "/load.ksh "
        + prog.name + "\n");
}

/*
 *  ======== Platform.getLinkTemplate ========
 *  Return a linker command file template that is used to create the
 *  executable's linker command file.
 *
 *  This template is toolchain dependent.  We could (should) check this by
 *  looking at prog.build.target, but for simplicity we just assume that
 *  a TI toolchain is being used.
 */
function getLinkTemplate(prog)
{
    return (this.$private.pdir + "/linkcmd.xdt");
}

/*
 *  ======== Platform.Instance.init ========
 *  This function is called to initialize a newly created instance of a
 *  platform.  Platform instances are created just prior to running
 *  program configuration scripts.
 *
 *  Platform instances may also be created in the build domain.
 *
 *  name is the name used to identify this instance (without the package
 *  name prefix).
 */
function instance$meta$init(name)
{
    var IExeContext = xdc.module("xdc.platform.IExeContext");

    /* cache the platform instance name for the methods above. */
    this.$private.name = name;

    /* cache the package name directory prefix */
    this.$private.pdir = this.$package.$name.replace(/\./g, '/');

    /* create a copy of the default Cpu attributes declared in Platform.xdc */
    var cpuAttrs = new IExeContext.Cpu(this.$module.CPU);
    this.$private.cpuAttrs = cpuAttrs;

    if (this.externalMemoryMap.length != 0) {
        this.$module.$logError("External memory cannot be added to this " +
            "platform", this, null);
    }
}

/*
 *  @(#) ti.platforms.ez430_rf2500; 1, 0, 0, 1,13; 2-23-2010 17:00:56; /db/ztree/library/trees/platform/platform-k32x/src/
 */

