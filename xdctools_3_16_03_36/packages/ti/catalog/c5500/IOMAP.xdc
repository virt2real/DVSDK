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
 *  ======== IOMAP.xdc ========
 *
 */
package ti.catalog.c5500;

/*!
 *  ======== IOMAP ========
 *  An interface implemented by all OMAP devices.
 *
 *  This interface is defined to factor common data about this family into
 *  a single place; all OMAP devices extend this interface.
 */
metaonly interface IOMAP inherits ti.catalog.ICpuDataSheet
{
instance:
    override config string   cpuCore        = "5500";
    override config string   isa            = "55";
    override config int     minProgUnitSize = 2;
    override config int     minDataUnitSize = 1;    
    override config int     dataWordSize    = 2;

    /*!
     *  ======== memMap ========
     *  The default memory map for OMAP device. For 1510 and like devices,
     *  this memory map doesn't change, but for 1710, 2420, 594x and some
     *  others, it needs to be overridden.
     */
    config xdc.platform.IPlatform.Memory memMap[string]  = [
        ["DARAM", {
            comment: "8 blocks of 8K bytes",
            name: "DARAM",
            base: 0x000000,
            len:  0x010000,
            space: "code/data",
            access: "RWX"
        }],
    
        ["SARAM", {
            comment: "12 blocks of 8K bytes",
            name: "SARAM",
            base: 0x010000,
            len:  0x018000,
            space: "code/data",
            access: "RWX"
        }],

        ["PDROM", {
            comment: "32K bytes On-Chip ROM",
            name: "PDROM",
            base: 0xff8000,
            len:  0x008000,
            space: "code/data",
            access: "RX"
        }],
    ];

};
/*
 *  @(#) ti.catalog.c5500; 1, 0, 0, 0,226; 2-23-2010 16:53:06; /db/ztree/library/trees/platform/platform-k32x/src/
 */

