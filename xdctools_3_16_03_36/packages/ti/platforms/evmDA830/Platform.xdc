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
 *  ======== Platform.xdc ========
 */

package ti.platforms.evmDA830;

/*!
 *  ======== Platform ========
 *  Platform support for the evmDA830
 *
 *  This module implements xdc.platform.IPlatform and defines configuration
 *  parameters that correspond to this platform's Cpu's, Board's, etc.
 *
 *  The configuration parameters are initialized in this package's
 *  configuration script (package.cfg) and "bound" to the TCOM object
 *  model.  Once they are part of the model, these parameters are
 *  queried by a program's configuration script.
 *
 *  This particular platform has a single Cpu, and therefore, only
 *  declares a single CPU configuration object.  Multi-CPU platforms
 *  would declare multiple Cpu configuration parameters (one per
 *  platform CPU).
 */
metaonly module Platform inherits xdc.platform.IPlatform
{
    readonly config xdc.platform.IPlatform.Board BOARD = {      
        id:             "0",
        boardName:      "evmDA830",
        boardFamily:    "evmDA830",
        boardRevision:  null,
    };
        
    readonly config xdc.platform.IExeContext.Cpu DSP = {        
        id:             "0",
        clockRate:      300.0,
        catalogName:    "ti.catalog.c6000",
        deviceName:     "TMS320DA830",
        revision:       "",
    };

    readonly config xdc.platform.IExeContext.Cpu GPP = {
        id:             "1",
        clockRate:      300.0,
        catalogName:    "ti.catalog.arm",
        deviceName:     "TMS320DA830",
        revision:       "1.0",
    };

instance:

    /* 
     *  SDRAM is 64MByte but we need to share it with Arm.
     *  Reserve 32MB for Arm/Linux (base: 0xC000000)
     *  16MB for shared Arm/DSP (base: 0xC2000000)
     *  16MB for DSP (base: 0xC3000000)
     */
    override readonly config xdc.platform.IPlatform.Memory
        externalMemoryMap[string] = [
            ["SDRAM",  {name: "SDRAM",  base: 0xC3000000, len: 0x01000000}],
        ];

    /*
     *  ======== sectMap ========
     *  Define a placement of compiler generated output sections into
     *  memory regions defined in the memTab above.
     */
    override config string codeMemory = "SDRAM";
    
    override config string dataMemory = "SDRAM";

    override config string stackMemory = "SDRAM";

    /*
     *  ======== l1PMode ========
     *  Define the amount of L1P RAM used for L1 Program Cache.
     *
     *  Check the device documentation for valid values.
     */
    config String l1PMode;
    
    /*
     *  ======== l1DMode ========
     *  Define the amount of L1D RAM used for L1 Data Cache.
     *
     *  Check the device documentation for valid values.
     */
    config String l1DMode;
    
    /*
     *  ======== l2Mode ========
     *  Define the amount of L2 RAM used for L2 Cache.
     *
     *  Check the device documentation for valid values.
     */
    config String l2Mode;
};
/*
 *  @(#) ti.platforms.evmDA830; 1, 0, 0,80; 2-23-2010 16:59:49; /db/ztree/library/trees/platform/platform-k32x/src/
 */

