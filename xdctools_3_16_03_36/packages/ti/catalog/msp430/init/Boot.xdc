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
 *  ======== Boot.xdc ========
 *
 */

package ti.catalog.msp430.init;

import xdc.rov.ViewInfo;

@Template("./Boot.xdt")

metaonly module Boot
{
    metaonly struct ModuleView {
        Bool         disableWatchdog;
        UInt         watchdogAddress;
        Bool         configureDCO;
    }

    @Facet
    metaonly config ViewInfo.Instance rovViewInfo = 
        ViewInfo.create({
            viewMap: [
            [
                'Module',
                {
                    type: ViewInfo.MODULE,
                    viewInitFxn: 'viewInitModule',
                    structName: 'ModuleView'
                }
            ],
            ]
        });
    
    /*! 
     *  Watchdog disable flag; default is true.
     *
     *  Set to false to not automatically disable the watchdog timer.
     */
    config Bool disableWatchdog = true;

    /*! 
     *  Watchdog control register address; default for MSP430F54xx.
     *
     *  Change for other (non-F54xx) devices.
     */
    config UInt watchdogAddress = 0x15c;

    /*! 
     *  Configure DCO flag; default is false.
     *
     *  Set to true to initialize DCO at boot.
     */
    config Bool configureDCO = false;

    /*! 
     *  Code section that Boot module code is in.
     *
     *  To place this section into a memory segment yourself, add the 
     *  following to your configuration file: 
     *
     *  @p(code)
     *  Program.sectMap[Boot.bootCodeSection] = new Program.SectionSpec();
     *  Program.sectMap[Boot.bootCodeSection].loadSegment = "yourBootCodeMemorySegment";
     *  @p
     *
     *  or to place the code at a specific address: 
     *
     *  @p(code)
     *  Program.sectMap[Boot.bootCodeSection] = new Program.SectionSpec();
     *  Program.sectMap[Boot.bootCodeSection].loadAdress = yourBootCodeAddress;
     *  @p
     *
     */
    readonly config String bootCodeSection = ".bootCodeSection";
    
};
/*
 *  @(#) ti.catalog.msp430.init; 1, 0, 0,17; 2-23-2010 16:50:25; /db/ztree/library/trees/platform/platform-k32x/src/
 */

