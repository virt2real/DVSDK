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
 *  ======== ITMS320CTCI6486.xdc ========
 *
 */

/*!
 *  ======== ITMS320CTCI6486 ========
 *  An interface implemented by TCI6486 like devices
 *
 */
metaonly interface ITMS320CTCI6486 inherits ti.catalog.ICpuDataSheet
{
    config long cacheSizeL1[string] = [
        ["0k",  0x0000],
        ["4k",  0x1000],
        ["8k",  0x2000],
        ["16k", 0x4000],
        ["32k", 0x8000],
    ];

    config long cacheSizeL2[string] = [
        ["0k",   0x00000],
        ["32k",  0x08000],
        ["64k",  0x10000],
        ["128k", 0x20000],
        ["256k", 0x40000]
    ];

    readonly config ti.catalog.c6000.ICacheInfo.CacheDesc cacheMap[string] =

        [
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
                                ["128k",0x20000],
                                ["256k",0x40000]],
                             defaultValue: "0k",
                             memorySection: "LL2RAM"}], 

        ];

instance:

    override config string   cpuCore        = "64x+";
    override config string   isa="64P";
    override config string   cpuCoreRevision = "1.0";

    override config int     minProgUnitSize = 1;
    override config int     minDataUnitSize = 1;    
    override config int     dataWordSize    = 4;

    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    config xdc.platform.IPlatform.Memory memMap[string]  = [
        ["LL2RAM", {
            comment:    "608K Local L2 RAM/CACHE memory",
            name:       "LL2RAM",
            base:       0x00800000,
            len:        0x00098000,
            space:      "code/data",
            access:     "RWX"
        }],

        ["L1PSRAM", {
            comment:    "Internal 32KB RAM/CACHE L1 program memory",
            name:       "L1PSRAM",
            base:       0xE00000,
            len:        0x008000,
            space:      "code",
            access:     "RWX"
        }],

        ["L1DSRAM", {
            comment:    "Internal 32KB RAM/CACHE L1 data memory",
            name:       "L1DSRAM",
            base:       0xF00000,
            len:        0x008000,
            space:      "data",
            access:     "RW"
        }],

        ["SL2RAM", {
            comment:    "768K Shared L2 RAM memory",
            name:       "SL2RAM",
            base:       0x00200000,
            len:        0x000C0000,
            space:      "code/data",
            access:     "RWX"
        }],
    ];
};
/*
 *  @(#) ti.catalog.c6000; 1, 0, 0, 0,226; 2-23-2010 16:50:38; /db/ztree/library/trees/platform/platform-k32x/src/
 */

