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
 *  ======== ITMS320C64_1M.xdc ========
 *
 */
package ti.catalog.c6000;

/*!
 *  ======== ITMS320C64_1M ========
 *  An interface implemented by all TMS320C64xx devices with 1MB of internal
 *  memory.
 *
 *  This interface is defined to factor common data about this family into
 *  a single place; all TMS320C64xx devices with 1MB of internal
 *  memory extend this interface.
 */
metaonly interface ITMS320C64_1M inherits ti.catalog.ICpuDataSheet
{

    config long cacheSize[string] = [
        ["4-way cache (0k)",   0x00000],
        ["4-way cache (32k)",  0x08000],
        ["4-way cache (64k)",  0x10000],
        ["4-way cache (128k)", 0x20000],
        ["4-way cache (256k)", 0x40000],
    ];

    readonly config ti.catalog.c6000.ICacheInfo.CacheDesc cacheMap[string] =  [
         ['l2Mode',{desc:"L2 Cache",
                     map : [["4-way cache (0k)",0x0000],
                            ["4-way cache (32k)",0x8000],
                            ["4-way cache (64k)",0x10000],
                            ["4-way cache (128k)",0x20000],
                            ["4-way cache (256k)",0x40000]],
                     defaultValue: "4-way cache (0k)",
                     memorySection: "IRAM"}]
    ];


instance:
    override config int     minProgUnitSize = 1;
    override config int     minDataUnitSize = 1;    
    override config int     dataWordSize    = 4;
    
    override config string   cpuCore        = "6400";
    override config string   isa = "64";
    override config string   cpuCoreRevision = "1.0";

    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    config xdc.platform.IPlatform.Memory memMap[string]  = [
        ["IRAM", {
            name:       "IRAM",
            comment:    "Internal L2 memory",
            base:       0x000000,
            len:        0x100000,
            space:      "code/data",
            access:     "RWX"
        }],
    ];
}
/*
 *  @(#) ti.catalog.c6000; 1, 0, 0, 0,226; 2-23-2010 16:50:38; /db/ztree/library/trees/platform/platform-k32x/src/
 */

