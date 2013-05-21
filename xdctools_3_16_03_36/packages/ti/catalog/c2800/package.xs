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
 *  ======== package.xs ========
 *
 *! 27-Aug-2008 sasha   skip the stack base address check if BIOS 5 is present
 *! 31-May-2007 sasha   added check for stack base address (CQ13032)
 */

/*
 *  ======== Package.close ========
 *  This function is called when this package is closed
 */
function close()
{

    /* Nothing to do, unless we are in Config Object Model */
    if (xdc.om.$name != "cfg") {
        return;
    }

    /* If this package is accidently loaded when some other architecture is
     * actually used, we don't want to look into stack segment.
     */
    if (Program.build.target.isa != "28") {
        return;
    }

    /* If BIOS 5 is also configured, then BIOS 5 is in control of section
     * allocations, so the check for stack not going over 64K is handled
     * there.
     */
    if (Program.build.cfgScript != null
        && Program.build.cfgScript.match(/\.tcf$/) != null) {
        return;
    }
    
    var stackSegName = Program.getSectMap()[".stack"].loadSegment;
    if (stackSegName == undefined) {
        Program.platform.$module.$logError("The section .stack must be " +
            "placed within low 64K of data memory", Program.platform, null);
        return;    
    }

    /* sectMap entry may include 'page' description, so we need only the
     * first token until a first whitespace is found.
     */
    var stackSegNameArr = stackSegName.split(/\s+/);
    stackSegName = stackSegNameArr[0];

    /* look for the stack memory object and find out its base + len address.
     * It mustn't go over 64K.
     */
    var stackSeg = Program.cpu.memoryMap[stackSegName];
    
    if (stackSeg.base + stackSeg.len > 0x10000) {
        Program.platform.$module.$logError("The section .stack must be " +
            "placed within low 64K of data memory", Program.platform, null);
    }
        
}

/*
 *  ======== Package.getLibs ========
 *  Get this package's libraries (This package's implementation of
 *  xdc.IPackage.getLibs)
 */
function getLibs()
{
    return (null);    /* no libraries for this package */
}
/*
 *  @(#) ti.catalog.c2800; 1, 0, 0, 0,227; 2-23-2010 16:58:49; /db/ztree/library/trees/platform/platform-k32x/src/
 */

