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
 *  Return the xdc.platform.IPlatform.ExeContext object that will run the
 *  specified program prog.
 */
function getExeContext(prog)
{
    var ExeContext = xdc.useModule('xdc.platform.ExeContext');
    
    if (prog.build.target.$name.match("ti.targets")) {
        this.$module.$logError("This platform is intended to be used with "
            + "non-TI targets. Please use 'ti.platforms.generic' for TI "
            + "targets.", this, prog.build.target.$name);       
    }

    /* create a default ExeContext execution context */
    var cpu = ExeContext.create(this.$private.cpuAttrs, this.$module.BOARD);

    return (cpu);
}

/*
 *  ======== Platform.getExecCmd ========
 *  This Platform's implementation xdc.platform.IPlatform.getExecCmd.
 */
function getExecCmd(prog)
{
    return ("@$(ECHO) host.platforms.arm package does not know how to " +
        "execute " + prog.name + "\n");
}

/*
 *  ======== Platform.getLinkTemplate ========
 *  This is Platform's implementation xdc.platform.IPlatform.getLinkTemplate
 */
function getLinkTemplate(prog)
{
    /* use the target's linker command template */

    /* we compute the target because this same platform is supported by
     * many different tool chains; e.g., gnu.targets, microsoft.targets, ...
     */
    var tname = Program.build.target.$name;
    var tpkg = tname.substring(0, tname.lastIndexOf('.'));
    return (tpkg.replace(/\./g, "/") + "/linkcmd.xdt");
}

/*
 *  ======== Platform.Instance.init ========
 *  This function is called to initialize a newly created instance of a
 *  platform.  Platform instances are created just prior to running
 *  program configuration scripts.
 *
 *  Platform instances may also be created in the build domain.
 *
 *  name is the name used to identify this instance (without
 *  the package name prefix).
 */
function instance$meta$init(name)
{
    /*  cache the platform instance name for the methods above. */
    this.$private.name = name;

    /*  Determine an appropriate CPU to simulate
     */

    var cpuAttrs = new xdc.om['xdc.platform'].IExeContext.Cpu({clockRate: 0});

    if (this.deviceName != undefined) {
        if ((typeof this.deviceName) != "string") {
            this.$module.$logError(this.$package.$name + ": 'deviceName' must "
                + "be a string", this, this.deviceName);
        }
    }
    else {
        this.$module.$logError("Parameter deviceName must be specified for "
            + "'host.platforms.arm' platform.", this, this.deviceName); 
    }
        
    if (this.catalogName != undefined) {
        if ((typeof this.catalogName) != "string") {
            this.$module.$logError(this.$package.$name + ": catalog name must "
                + "be a string", this, this.catalogName);
        }

        /* this platform doesn't know the catalog package until now, so it
         * must dynamically import it here; "real" platforms would declare
         * its catalog package statically in their package.xdc file.
         */
        xdc.loadPackage(this.catalogName);

        if (!(this.deviceName in xdc.om[this.catalogName])) {
            this.$module.$logError("Device " + this.deviceName + " does not"
                + " exist in " + this.catalogName, this, this.deviceName);
        }
    }
    else {
        this.$module.$logError("Parameter catalogName must be specified for "
            + "'host.platforms.arm' platform.", this, this.deviceName); 
    }

    if (this.externalMemoryMap.length > 0 || this.customMemoryMap.length > 0 
        || this.renameMap.lenght > 0 || this.sectMap.length > 0
        || this.codeMemory != undefined || this.dataMemory != undefined
        || this.stackMemory != undefined) {
        this.$module.$logWarning("The platform 'host.platforms.arm' ignores "
            + "the following configuration parameters: 'sectMap',"
            + " 'customMemoryMap', 'renameMap', 'externalMemoryMap', "
            + " 'codeMemory', 'dataMemory' and 'stackMemory'.", this, null);
    }
        
    cpuAttrs.deviceName = this.deviceName;
    cpuAttrs.catalogName = this.catalogName;
    this.$private.cpuAttrs = cpuAttrs;
}
/*
 *  @(#) host.platforms.arm; 1, 0, 0, 0,25; 2-23-2010 16:58:36; /db/ztree/library/trees/platform/platform-k32x/src/
 */

