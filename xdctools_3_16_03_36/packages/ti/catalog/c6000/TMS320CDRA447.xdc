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
 *  ======== TMS320CDRA447.xdc ========
 *
 */

/*!
 *  ======== TMS320CDRA447 ========
 *  The DRA447 device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is 
 *  used by platforms to obtain "data sheet" information about this device.
 */
metaonly module TMS320CDRA447 inherits ITMS320CDRA44x
{

    override config long cacheSizeL2[string] = [
        ["0k",  0x00000],
        ["32k", 0x08000],
        ["64k", 0x10000],
        ["128k", 0x20000]
    ];

    override readonly config ti.catalog.c6000.ICacheInfo.CacheDesc cacheMap[string] =  [
             ['l1PMode',{desc:"L1P Cache",
                         map : [["0k",0x0000],
                                ["4k",0x1000],
                                ["8k",0x2000],
                                ["16k",0x4000],
                                ["32k",0x8000]],
                         defaultValue: "0k",
                         memorySection: "L1PSRAM"}],
         
                 ['l1DMode',{desc:"L1D Cache",
                         map : [["0k",0x0000],
                                ["4k",0x1000],
                                ["8k",0x2000],
                                ["16k",0x4000],
                                ["32k",0x8000]],
                         defaultValue: "0k",
                         memorySection: "L1DSRAM"}],
                     
             ['l2Mode',{desc:"L2 Cache",
                         map : [["0k",0x0000],
                                ["32k",0x8000],
                                ["64k",0x10000],
                                ],
                         defaultValue: "0k",
                         memorySection: "IRAM"}], 

    ];

instance:

    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    override config xdc.platform.IPlatform.Memory memMap[string] = [
        ["IRAM", {
            comment:    "Internal 128KB UMAP0 memory",
            name:       "IRAM",
            base:       0x11800000,
            len:        0x00020000,
            space:      "code/data",
            access:     "RWX"
        }],
        
        ["L1PSRAM", {
            comment:    "Internal 32KB RAM/CACHE L1 program memory",
            name:       "L1PSRAM",
            base:       0x11E08000,
            len:        0x00008000,
            space:      "code",
            access:     "RWX"
        }],

        ["L1DSRAM", {
            comment:    "Internal 80KB RAM/CACHE L1 data memory",
            name:       "L1DSRAM",
            base:       0x11F04000,
            len:        0x00014000,
            space:      "data",
            access:     "RW"
        }],

        ["ARM_RAM", {
            comment:    "Internal ARM RAM memory",
            name:       "ARM_RAM",
            base:       0x10008000,
            len:        0x00004000,
            space:      "data",
            access:     "RW"
        }],
    ];

};
/*
 *  @(#) ti.catalog.c6000; 1, 0, 0, 0,226; 2-23-2010 16:50:40; /db/ztree/library/trees/platform/platform-k32x/src/
 */

