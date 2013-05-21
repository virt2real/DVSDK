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
 *  ======== Package.getLibs ========
 *  This package's implementation of xdc.IPackage.getLibs.
 */
function getLibs()
{
    return (null);    /* no library required for this package */
}

/*
 *  ======== Package.init ========
 *  This function is called when this package is included
 */
function init()
{
}

/*
 *  ======== Package.close ========
 */
function close()
{

    /* Only in cfg step, there is a Program object. */
    if (xdc.om.$name != "cfg") {
        return;
    }

    /* XML file is created from a template because the original XML file
     * from FTSuite 1.0.5 uses bigEndian model, so if we need littleEndian,
     * we need a different XML file. 
     */
    if (Program.platform.$private.ftpath != undefined &&
        Program.endian == "little") {
        var cwd = java.lang.System.getProperty("user.dir") + "";
        cwd = cwd.replace(/\\/g, "/");
        var filename = cwd + "/package/cfg/" + Program.name + ".Sim_ARM.xml";

        var file = new java.io.File(filename);
        file["delete"]();
        var fos = new java.io.PrintStream(file);

        var xmlTemp = xdc.loadTemplate(this.packageBase + "Sim_ARM.xml.xdt");
        xmlTemp.genStream(fos, Program.platform, null);
        fos.close();
    }
}

/*
 *  @(#) ti.platforms.sim470xx; 1, 0, 1, 1,25; 2-23-2010 17:01:41; /db/ztree/library/trees/platform/platform-k32x/src/
 */

