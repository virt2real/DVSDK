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
 *  ======== ILM3Sx9xx.xdc ========
 *  
 */

/*!
 *  ======== ILM3Sx9xx.xdc ========
 *  The Stellaris device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is 
 *  used by platforms to obtain "data sheet" information about this device.
 *
 */

metaonly interface ILM3Sx9xx inherits ti.catalog.ICpuDataSheet
{

    struct Timer {
        string  name;
        UInt    baseAddr;
        UInt    intNum;
    };

instance:
    override config string cpuCore           = "CM3";
    override config string isa               = "v7M";
    override config string cpuCoreRevision   = "1.0";
    override config int    minProgUnitSize   = 1;
    override config int    minDataUnitSize   = 1;
    override config int    dataWordSize      = 4;

    /*!
     *  ======== memMap ========
     *  The memory map returned by getMemoryMap().
     */
    config xdc.platform.IPlatform.Memory memMap[string] = [
        ["FRAM", {
            comment: "256KB FRAM",
            name: "FRAM",
            base: 0x00000000, 
            len:  0x00040000
        }],

        ["IRAM", {
            comment: "64KB IRAM",
            name: "IRAM",
            base: 0x20000000, 
            len:  0x00010000
        }],
    ];

    config Timer timers[4] = [
        {
            name: "Timer 0",
            baseAddr: 0x40030000,
            intNum: 35
        },

        {
            name: "Timer 1",
            baseAddr: 0x40031000,
            intNum: 37
        },

        {
            name: "Timer 2",
            baseAddr: 0x40032000,
            intNum: 39
        },

        {
            name: "Timer 3",
            baseAddr: 0x40033000,
            intNum: 51
        },
    ];

};

/*
 *  @(#) ti.catalog.arm; 1, 0, 1, 0,116; 2-23-2010 16:50:33; /db/ztree/library/trees/platform/platform-k32x/src/
 */

