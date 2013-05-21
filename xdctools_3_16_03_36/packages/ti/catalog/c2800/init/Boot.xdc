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

package ti.catalog.c2800.init;

import xdc.rov.ViewInfo;

@Template("./Boot.xdt")

metaonly module Boot
{
    metaonly struct ModuleView {
        Bool         disableWatchdog;
        Bool         configurePll;
        UInt         pllcrDIV;
        UInt         pllstsDIVSEL;
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
     *  Watchdog disable flag, default is false.
     *
     *  Set to true to automatically disabled the watchdog timer.
     */
    config Bool disableWatchdog = false;

    /*! 
     *  PLL configuration flag, default is false.
     *
     *  Set to true to automatically configure the PLL.
     */
    config Bool configurePll = false;

    /*! 
     *  PLLCR[DIV] value. Default is 10.
     *
     *  This is the actual value written to the DIV bits in 
     *  the PLL Control Register (PLLCR)
     */
    config UInt pllcrDIV = 10;

    /*! 
     *  PLLSTS[DIVSEL] value. Default is 2.
     *
     *  This is the actual value written to the DIVSEL bits in 
     *  the PLL Status Register (PLLSTS)
     */
    config UInt pllstsDIVSEL = 2;

    /*! 
     *  Code section that Boot module code is in.
     *
     *  To place this section into a memory segment yourself, add the 
     *  following to you configuration file: 
     *
     *  @p(code)
     *  Program.sectMap[Boot.bootCodeSection] = new Program.SectionSpec();
     *  Program.sectMap[Boot.bootCodeSection].loadSegment = "yourBootCodeMemorySegment";
     *  @p
     *
     *  or to place the code at a specific adress: 
     *
     *  @p(code)
     *  Program.sectMap[Boot.bootCodeSection] = new Program.SectionSpec();
     *  Program.sectMap[Boot.bootCodeSection].loadAdress = yourBootCodeAddress;
     *  @p
     *
     */
    readonly config String bootCodeSection = ".bootCodeSection";
    
    /*!
     * @_nodoc
     * Configure the external memory interface (XINTF) for the eZdsp283xx
     * devices.
     *
     * This will eventually be replaced by a more generic API for configuring
     * the XINTF on any 28x device.
     */
    config Bool enableEzdspXintfConfig = false;
};
/*
 *  @(#) ti.catalog.c2800.init; 1, 0, 0,77; 2-23-2010 16:50:25; /db/ztree/library/trees/platform/platform-k32x/src/
 */

