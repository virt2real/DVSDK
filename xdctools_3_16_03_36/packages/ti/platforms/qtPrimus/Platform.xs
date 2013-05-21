/*
 *  Copyright (c) 2010 by Texas Instruments and others.
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
 *  Platform support for the qtPrimus
 *
 */

/*
 *  ======== Platform.getExeContext ========
 *  This Platform's implementation xdc.platform.IPlatform.getExeContext.
 *
 *  Return the xdc.platform.IPlatform.ExeContext object that will run the 
 *  specified program prog.
 */
function getExeContext(prog)
{
    var Utils = xdc.module("xdc.platform.Utils");
        
    var args = this.$private.args;

    var ExeContext = xdc.useModule('xdc.platform.ExeContext');

    /* create a default ExeContext execution context */
    var cpu;
    
    if (args.core == "DSP") {
        xdc.loadPackage(this.$module.DSP.catalogName);
        cpu = ExeContext.create(this.$module.DSP, this.$module.BOARD);
    }
    else {
        xdc.loadPackage(this.$module.GPP.catalogName);
        cpu = ExeContext.create(this.$module.GPP, this.$module.BOARD);
    }
    
    /* Set the initial memory map from the cpu datasheet. Check if the user
     * tried to set cpuArgs, and if it's the case print a deprecation
     * warning message.
     */
    if (prog.build.cpuArgs != null) {
        this.$module.$logWarning("The parameter 'cpuArgs' in xdc.bld.Executable " +
            "is deprecated and will not be supported in future releases. " +
            "Please, use corresponding platform instance parameters to set " +
            "the initial register settings.", this.$module, null);
        
        for (var prop in prog.build.cpuArgs) {
            if (!(prop in this.$private.args)) {
                this.$private.args[prop] = prog.build.cpuArgs[prop];
            }
        }
    }
    cpu.memoryMap = Utils.assembleMemoryMap(cpu, this);

    // check for the overlap in the memory map
    var overlap = Utils.checkOverlap(cpu.memoryMap);

    if (overlap != null) {
        this.$module.$logError("Memory objects " + overlap + " overlap", this,
            overlap);
    }

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
    "@$(ECHO) https://www-a.ti.com/downloads/sds_support/targetcontent/rtsc/index.html";

     return("@$(ECHO) " + this.$package.$name + " platform package cannot " +
         "execute " + prog.name + " on " + os + "\n" + updateComment + "\n\t:");
}

/*
 *  ======== Platform.getLinkTemplate ========
 *  This is Platform's implementation xdc.platform.IPlatform.getLinkTemplate
 */
function getLinkTemplate(prog)
{
    /* use the target's linker command template */
    /* we compute the target because this same platform is supported by
     * many different tool chains; e.g., ti.targets, gnu.targets, ...
     */
    var tname = prog.build.target.$name;
    var tpkg = tname.substring(0, tname.lastIndexOf('.'));
    var templateName = tpkg.replace(/\./g, "/") + "/linkcmd.xdt"; 

    if (xdc.findFile(templateName) != null) {
        return (templateName);
    }
    else if (tname.indexOf("ti.targets.") == 0) {
        return ("ti/targets/linkcmd.xdt");
    }
    else {
        throw new Packages.xdc.services.global.XDCException(
            this.$package.$name + ".LINK_TEMPLATE_ERROR",
            "Target package " + tpkg + " does not contain linker command "
            + "template 'linkcmd.xdt'.");
    }
}

/*
 *  ======== Platform.Instance.init ========
 *  This function is called to initialize a newly created instance of a
 *  platform.  Platform instances are created just prior to running
 *  program configuration scripts.
 *
 *  Platform instances may also be created in the build domain.
 *
 *  this.$args.args is the object configured in config.bld via
 *  Build.platformTable.  This is an untyped object that may specify
 *  platform specific parameters.
 *
 *  this.$args.name is the name used to identify this instance (without
 *  the package name prefix).
 */
function instance$meta$init(name, args)
{
    var thisMod = this.$module;

    /* cache the platform creation args and platform instance name for the
     * getExeContext method above.
     */
    this.$private.name = name;      /* instance name */

    if (args == null) {
        args = {};
    }
    this.$private.args = args;      /* instance args */

    if (args.core == null) {
        /* We need to add v5t, v5T, v5TE because of several changes we made for
         * the name of that architecture.
         */
        var armChain = ["470", "v4T", "v5T", "v5TE", "v5t"];
        var dspChain = ["62", "64", "64P", "674"];
        for (var i = 0; i < dspChain.length; i++) {
            if (dspChain[i] == prog.build.target.isa) {
                args.core = "DSP";
            }
        }
        for (var i = 0; i < armChain.length; i++) {
            if (armChain[i] == prog.build.target.isa) {
                args.core = "GPP";
            }
        }
    }

    if (args.core == null) {
        if (args.runtime == thisMod.POSIX) {
            args.core = "GPP";
        }
        else if (args.runtime == thisMod.BIOS) {
            args.core = "DSP";
        }
        else {
            args.core = "DSP";
        }
    }


    if (args.core == "GPP") {
        /* define DDR2 and SRAM sections */
        this.externalMemoryMap["SDRAM0"] = 
            {name: "SDRAM0", base: 0x40000000, len: 0x04000000};
        this.externalMemoryMap["SDRAM1"] = 
            {name: "SDRAM1", base: 0xC0000000, len: 0x08000000};

        /* default segment for code sections */
        this.codeMemory = "SDRAM0";

        /* default segment for data sections */
        this.dataMemory = "SDRAM0";

        /* default segment for stack sections */
        this.stackMemory = "SDRAM0";
    }
    else {
        this.externalMemoryMap["SDRAM0"] = 
            {name: "SDRAM0", base: 0x40000000, len: 0x04000000};
        this.externalMemoryMap["SDRAM1"] = 
            {name: "SDRAM1", base: 0xC0000000, len: 0x08000000};

        /* default segment for code sections */
        this.codeMemory = "IRAM";

        /* default segment for data sections */
        this.dataMemory = "SDRAM1";

        /* default segment for stack sections */
        this.stackMemory = "SDRAM1";
    }

    if (args.runTime == null) {
        args.runTime = thisMod.STDIO;

        if (args.core == "DSP"
            && prog.build.cfgScript != null
            && prog.build.cfgScript.match(/\.tcf$/) != null) {
            args.runTime = thisMod.BIOS;
        }
    }

    if ("sectMap" in args) {
        this.sectMap = args.sectMap;
    }

    if ("customMemoryMap" in args) {
        this.customMemoryMap = args.customMemoryMap;
    }
        
    if ("renameMap" in args) {
        this.renameMap = args.renameMap;
    }
        
    if ("externalMemoryMap" in args) {
        this.$module.$logError("External memory cannot be changed on " +
            "this platform", this, null); 
    }
        
    if ("ftpath" in args) {
        this.ftpath = args.ftpath;
    }
        
    if ("codeMemory" in args) {
        this.codeMemory = args.codeMemory;      
    }

    if ("dataMemory" in args) {
        this.dataMemory = args.dataMemory;      
    }

    if ("stackMemory" in args) {
        this.stackMemory = args.stackMemory;
    }

    if ("l1PMode" in args) {
        this.l1PMode = args.l1PMode;
    }

    if ("l1DMode" in args) {
        this.l1DMode = args.l1DMode;
    }

    if ("l2Mode" in args) {
        this.l2Mode = args.l2Mode;
    }
}
/*
 *  @(#) ti.platforms.qtPrimus; 1, 0, 0, 0,105; 2-23-2010 17:01:24; /db/ztree/library/trees/platform/platform-k32x/src/
 */

