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
 *  ======== TMS320CDM510.xdc ========
 *
 */

metaonly module TMS320CDM510 inherits ti.catalog.ICpuDataSheet
{
instance:
    override config string cpuCore           = "Arm9";
    override config string isa               = "v5T";
    override config string cpuCoreRevision   = "1.0";
    override config int    minProgUnitSize   = 1;
    override config int    minDataUnitSize   = 1;
    override config int    dataWordSize      = 4;

    /*!
     *  ======== memMap ========
     *  The memory map returned be getMemoryMap().
     */
    config xdc.platform.IPlatform.Memory memMap[string]  = [
        ["IRAM", {
            comment:    "Internal ARM Instruction RAM",
            name:       "IRAM",
            base:       0x00000004,
            len:        0x00007ffc,
            space:      "code",
            access:     "RWX"
        }],

        ["DRAM", {
            comment:    "Internal ARM Data RAM",
            name:       "DRAM",
            base:       0x00010004,
            len:        0x00007ffc,
            space:      "data",
            access:     "RW"
        }],
    ];
}
/*
 *  @(#) ti.catalog.arm; 1, 0, 1, 0,116; 2-23-2010 16:50:34; /db/ztree/library/trees/platform/platform-k32x/src/
 */

