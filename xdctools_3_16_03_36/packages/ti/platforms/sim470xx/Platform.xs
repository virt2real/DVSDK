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
    var Utils = xdc.module("xdc.platform.Utils");

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
    cpu.memoryMap = Utils.assembleMemoryMap(cpu, this);

    // check for the overlap in the memory map
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
    var updateComment = "@$(ECHO) Check for updates to this package at:\n"
        + "@$(ECHO) https://www-a.ti.com/downloads/sds_support/targetcontent/rtsc/index.html"
        + "\n\t: ";

    if (os == "Solaris" || os == "Linux") {
        return (this.$package.packageBase + "/" + os + 
            "/load470.be8_coff -q " + prog.name);
    }
    else {
        try {
            var exec = xdc.loadPackage("ti.platforms.utils.exec");
        }
        catch (e) {
            return("@$(ECHO) sim470xx platform package does not know how to " +
            "execute " + prog.name + " on " + os + "\n" + updateComment);
        }
        if (this.ftpath == undefined || this.ftpath == null) {
            return("@$(ECHO) Path to FTSuite installation must be set in " +
                   "config.bld to execute programs on " + prog.platformName +
                   ".\n# ");
        }

        command = exec.Settings.getLibraryPath(os, this.ftpath);
        var executable = exec.Settings.getExecutable(os);

        var driverAPI = "tsi";
        var verbose = "-q";
        var timeout = 32000;
        /* check execArgs for options */
        if (prog.build.test.execArgs != undefined) {
            var opts = prog.build.test.execArgs.split(/\s+/);
            for (var i = 0; i < opts.length; i++) {
                if (opts[i] == "-v") {
                    verbose = opts[i];
                }
                if (opts[i] == "-t" && typeof(opts[i+1]) != undefined) {
                    timeout = opts[i+1] - 0;
                } 
            }
        }
    
        /* "user.dir" gets us a current working directory */
        var cwd = java.lang.System.getProperty("user.dir") + "";
        cwd = cwd.replace(/\\/g, "/");

        command += executable + " -a " + driverAPI;
        command += " -t " + timeout + " -r -n :ARM9 " + verbose;

        if (prog.endian == "little") {
            command += " -b " + cwd + "/package/cfg/" + prog.name +
                       ".Sim_ARM.xml";
        }
        else {
            command += " -b " + this.ftpath + "/targetdb/Sim_ARM.xml";
        }
        command += " -u 127.0.0.1";

        var dllExt = os == "Windows" ? ".dll" : ".so";
        var canPath = java.io.File(prog.name).getCanonicalPath() + "";
        canPath = canPath.replace(/\\/g, "/");

        command += " -x " + this.ftpath + "/target_server/bin/" + 
                   "ti_targetserver_dvr" + dllExt + " -e _abort " + canPath;
                   
        return (command);
    }
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
 *  name is the name used to identify this instance (without the package
 *  name prefix).
 *
 *  args is a deprecated parameter that shouldn't be used.
 */
function instance$meta$init(name, args)
{
    /*  cache the platform instance name for the methods above. */
    this.$private.name = name;                      /* instance name */

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

    if (this.externalMemoryMap.length != 0) {
        this.$module.$logError("External memory cannot be added to this " +
            "platform", this, null); 
    }
}

/*
 *  @(#) ti.platforms.sim470xx; 1, 0, 1, 1,25; 2-23-2010 17:01:41; /db/ztree/library/trees/platform/platform-k32x/src/
 */

