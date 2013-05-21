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
 *  ======== TMS320DM357.xdc ========
 *
 */

metaonly module TMS320DM357 inherits ti.catalog.ICpuDataSheet
{
instance:
    override config string cpuCore           = "Arm926EJ-S";
    override config string isa               = "v5T";
    override config string cpuCoreRevision   = "1.0";
    override config int    minProgUnitSize   = 1;
    override config int    minDataUnitSize   = 1;
    override config int    dataWordSize      = 4;

    /*!
     *  ======== memMap ========
     *  The memory map returned be getMemoryMap().
     */
    config xdc.platform.IPlatform.Memory memMap[string] = [
        ["IRAM0", {
            comment:    "Internal ARM Instruction RAM0",
            name:       "IRAM0",
            base:       0x00000000,
            len:        0x00004000,
            space:      "code",
            access:     "RWX"
        }],

        ["IRAM1", {
            comment:    "Internal ARM Instruction RAM1",
            name:       "IRAM1",
            base:       0x00004000,
            len:        0x00004000,
            space:      "code",
            access:     "RWX"
        }],

        ["DRAM0", {
            comment:    "Internal ARM Data RAM0",
            name:       "DRAM0",
            base:       0x00010000,
            len:        0x00004000,
            space:      "data",
            access:     "RW"
        }],

        ["DRAM1", {
            comment:    "Internal ARM Data RAM1",
            name:       "DRAM1",
            base:       0x00014000,
            len:        0x00004000,
            space:      "data",
            access:     "RW"
        }],
    ];
}
/*
 *  @(#) ti.catalog.arm; 1, 0, 1, 0,116; 2-23-2010 16:50:34; /db/ztree/library/trees/platform/platform-k32x/src/
 */

