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
 *  ======== Boot.xs ========
 *
 */

var Boot = null;
var Program = null;

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }
    Boot = this;
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    Program = xdc.useModule('xdc.cfg.Program');

    if (Program.build.rtsName !== null) {

        /* Install Boot_init as one of Reset functions */
        var Reset = xdc.useModule('xdc.runtime.Reset');
        Reset.fxns[Reset.fxns.length++] = '&ti_catalog_c2800_init_Boot_init';

        /* 
         * Force the boot code into internal memory so that it 
         * can safely configure the XINTF
         */
        if (Program.sectMap[Boot.bootCodeSection] === undefined) {
            Program.sectMap[Boot.bootCodeSection] = new Program.SectionSpec();
            Program.sectMap[Boot.bootCodeSection].loadSegment = Program.platform.codeMemory;
        }
    }
}

/*
 *  ======== viewInitModule ========
 *  Display the module properties in ROV
 */
function viewInitModule(view, obj)
{
    var Program = xdc.useModule('xdc.rov.Program');
    var Boot = xdc.useModule('ti.catalog.c2800.init.Boot');
    var bootModConfig = Program.getModuleConfig(Boot.$name);

    view.disableWatchdog = bootModConfig.disableWatchdog;
    view.configurePll    = bootModConfig.configurePll;
    view.pllcrDIV = bootModConfig.pllcrDIV;
    view.pllstsDIVSEL = bootModConfig.pllstsDIVSEL;
}
/*
 *  @(#) ti.catalog.c2800.init; 1, 0, 0,77; 2-23-2010 16:50:25; /db/ztree/library/trees/platform/platform-k32x/src/
 */

