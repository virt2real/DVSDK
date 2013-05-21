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
 *
 */

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
    var Utils = xdc.module('xdc.platform.Utils');

    /* create a default ExeContext execution context */
    var ExeContext = xdc.useModule('xdc.platform.ExeContext');
    var cpu = ExeContext.create(this.$private.cpuAttrs, this.$module.BOARD);

    /* Set the initial memory map from the cpu datasheet. Check if the user
     * tried to set cpuArgs, and if it's the case print a deprecation
     * warning message.
     */
    if (prog.build.cpuArgs != null) {
        this.$module.$logWarning(
            "The parameter 'cpuArgs' in xdc.bld.Executable.Attrs " +
            "is deprecated and will not be supported in future releases. " +
            "Please, use corresponding platform instance parameters to set " +
            "the initial register settings.", this.$module, null);
        
        for (var prop in prog.build.cpuArgs) {
            if (prop in this) {
                this[prop] = prog.build.cpuArgs[prop];
            }
        }
    }
        
    if (this.pmst == undefined) {
        this.$module.$logError("The config parameter 'pmst' must be defined.",
            this, this.pmst);
    }
    
    /* Start from the maximum sized external memory map and then reduce it
     * according to 'pmst'.
     */
    var maxMemoryMap = new xdc.om['xdc.platform.IPlatform'].MemoryMap;
    maxMemoryMap["EPROG0"] =
        {name: "EPROG0",  page: 0, base: 0x8000,  len: 0x7f80};
    maxMemoryMap["EPROG1"] =
        {name: "EPROG1",  page: 1, base: 0x10000, len: 0x8000};
    maxMemoryMap["EPROG2"] =
        {name: "EPROG2",  page: 1, base: 0x18000, len: 0x8000};
    maxMemoryMap["EDATA"] =
        {name: "EDATA",  page: 1, base: 0x8000,  len: 0x8000};
    maxMemoryMap["VECT"] =
        {name: "VECT",   page: 0, base: 0xff80,  len: 0x80};

    var drommask = 0x8;
    var ovlymask = 0x20;
    var mpnmcmask = 0x40;

    var drombit = this.pmst & drommask;
    var ovlybit = this.pmst & ovlymask;
    var mpnmcbit = this.pmst & mpnmcmask;
    
    if (drombit != 0) {
        delete maxMemoryMap["EDATA"];
    }
    if (ovlybit != 0) {
        delete maxMemoryMap["EPROG1"];
    }
    if (mpnmcbit == 0) {
        maxMemoryMap["EPROG0"].len = 0x4000;
        delete maxMemoryMap["VECT"];
        delete maxMemoryMap["EPROG2"];
    }

    if (this.externalMemoryMap.length == 0) {
        for (var p in maxMemoryMap) {
            this.externalMemoryMap[p] = maxMemoryMap[p];
        }
    }
    else {
        if (!Utils.checkFit(maxMemoryMap, this.externalMemoryMap)) {
            this.$module.$logError("External memory map is not compatible " +
                "with the value of 'pmst'.", this, this.customMemoryMap);
        }
    }        

    cpu.memoryMap = Utils.assembleMemoryMap(cpu, this);

    /* check for the overlap in the memory map */
    var overlap = Utils.checkOverlap(cpu.memoryMap);

    if (overlap != null) {
        this.$module.$logError("Memory objects " + overlap + " overlap", this,
            overlap);
    }

    Utils.checkDefaults(this, cpu.memoryMap);
    this.$seal();
    return (cpu);
}

/*
 *  ======== Platform.getExecCmd ========
 *  This Platform's implementation xdc.platform.IPlatform.getExecCmd.
 */
function getExecCmd(prog)
{
    var os = environment["xdc.hostOS"];
    var updateComment = "@$(ECHO) Check for updates to this package at:\n" +
    "@$(ECHO) https://www-a.ti.com/downloads/sds_support/targetcontent/rtsc/index.html"
     + "\n\t: ";

    return("@$(ECHO) sim54xx platform package does not know how to " +
        "execute " + prog.name + " on " + os + "\n" + updateComment);
}

/*
 *  ======== Platform.getLinkTemplate ========
 *  This is Platform's implementation xdc.platform.IPlatform.getLinkTemplate
 */
function getLinkTemplate(prog)
{
    return ("ti/targets/linkcmd.xdt");
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
 *
 *  args is a deprecated parameter that shouldn't be used.
 */
function instance$meta$init(name, args)
{
    this.$private.name = name;

    /*  Determine an appropriate CPU to simulate
     *
     *  First check to see if the platform instance name is the name of a
     *  chip.  If so, use this as the CPU to simulate; otherwise, use the
     *  default specified in this module's CPU config parameter.
     */

    /* create a copy of the default Cpu attributes declared in Platform.xdc */
    var cpuAttrs = new xdc.om["xdc.platform"].IExeContext.Cpu(this.$module.CPU);

    if (name in xdc.om[cpuAttrs.catalogName]) {
        cpuAttrs.deviceName = name;
    }

    this.$private.cpuAttrs = cpuAttrs;

    if (this.deviceName != undefined) {
        if (!(this.deviceName in xdc.om[cpuAttrs.catalogName])) {
            this.$module.$logError("Device " + this.deviceName + " does not " +
                "exist in " + cpuAttrs.catalogName, this, this.deviceName);     
        }
        else {
            this.$private.cpuAttrs.deviceName = this.deviceName;        
        }
    }
}

/*
 *  @(#) ti.platforms.sim54xx; 1, 0, 1, 1,25; 2-23-2010 17:01:47; /db/ztree/library/trees/platform/platform-k32x/src/
 */

