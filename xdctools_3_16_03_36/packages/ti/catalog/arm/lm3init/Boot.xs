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

    /* only install Boot_init if using XDC runtime */
    if (Program.build.rtsName === null) {
        return;
    }

    /* Install Boot_init as one of Reset functions */
    var Reset = xdc.useModule('xdc.runtime.Reset');
    Reset.fxns[Reset.fxns.length++] = '&ti_catalog_arm_lm3init_Boot_init';

    /* 
     * Force the boot code into internal memory so that it 
     * can safely configure the XINTF
     */
    if (Program.sectMap[Boot.bootCodeSection] === undefined) {
        Program.sectMap[Boot.bootCodeSection] = new Program.SectionSpec();
        Program.sectMap[Boot.bootCodeSection].loadSegment = Program.platform.codeMemory;
    }

    if (Boot.configureClock == false) {
        return;
    }

    /* Compute ulConfig based on config settings */

    /* enable PLL Output */
    if (Boot.pllOutEnable) {
        Boot.ulConfig = 0x00001000;
    }

    Boot.ulConfig |= Boot.sysClockDiv;

    Boot.ulConfig |= Boot.pwmClockDiv;

    Boot.ulConfig |= Boot.xtal;

    Boot.ulConfig |= Boot.oscSrc;

    if (Boot.pllBypass) {
        Boot.ulConfig |= 0x00000800;
    }

    if (Boot.ioscDisable) {
        Boot.ulConfig |= 0x00000002;
    }

    if (Boot.moscDisable) {
        Boot.ulConfig |= 0x00000001;
    }
}
/*
 *  ======== getEnumString ========
 *  Get the enum value string name, not 0, 1, 2 or 3, etc.  For an enumeration
 *  type property.
 *
 *  Example usage:
 *  if obj contains an enumeration type property "Enum enumProp"
 *
 *  view.enumString = getEnumString(obj.enumProp);
 *
 */
function getEnumString(enumProperty)
{
    /*
     *  Split the string into tokens in order to get rid of the huge package
     *  path that precedes the enum string name. Return the last 2 tokens
     *  concatenated with "_" 
     */
    var enumStrArray = String(enumProperty).split(".");
    var len = enumStrArray.length;
    return (enumStrArray[len - 1]);
}

/*
 *  ======== viewInitModule ========
 *  Display the module properties in ROV
 */
function viewInitModule(view, obj)
{
    var Program = xdc.useModule('xdc.rov.Program');
    var Boot = xdc.useModule('ti.catalog.arm.lm3init.Boot');
    var modCfg = Program.getModuleConfig(Boot.$name);

    view.pllDiv = modCfg.pllDiv;
    view.configureClock         = modCfg.configureClock;
    view.sysClockDivEnable      = modCfg.sysClockDivEnable;
    view.sysClockDiv            = getEnumString(modCfg.sysClockDiv);
    view.pwmClockDivEnable      = modCfg.pwmClockDivEnable;
    view.pwmClockDiv            = getEnumString(modCfg.pwmClockDiv);
    view.xtal                   = getEnumString(modCfg.xtal);
    view.oscSrc                 = getEnumString(modCfg.oscSrc);
    view.pllBypass              = modCfg.pllBypass;
    view.pllOutEnable           = modCfg.pllOutEnable;
    view.ioscDisable            = modCfg.ioscDisable;
    view.moscDisable            = modCfg.moscDisable;
    view.configureLdo           = modCfg.configureLdo;
    view.ldoOut                 = getEnumString(modCfg.ldoOut);
}
/*
 *  @(#) ti.catalog.arm.lm3init; 1, 0, 0,40; 2-23-2010 16:50:33; /db/ztree/library/trees/platform/platform-k32x/src/
 */

