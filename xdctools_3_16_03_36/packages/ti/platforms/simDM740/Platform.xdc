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
 *  Platform support for simDM740
 *
 */

package ti.platforms.simDM740;

/*!
 *  ======== Platform ========
 *  Platform support for the simDM740
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
        boardName:      "simDM740",
        boardFamily:    "simDM740",
        boardRevision:  null,
    };

    /* C674 GEM */      
    readonly config xdc.platform.IExeContext.Cpu GEM = {        
        id:             "0",
        clockRate:      800.0,
        catalogName:    "ti.catalog.c6000",
        deviceName:     "TMS320CDM740",
        revision:       "",
    };

    /* Ducati Subsystem */
    readonly config xdc.platform.IExeContext.Cpu DSS = {        
        id:             "0",
        clockRate:      250.0,
        catalogName:    "ti.catalog.arm",
        deviceName:     "TMS320CDM740",
        revision:       "1.0",
    };

instance:

    override readonly config xdc.platform.IPlatform.Memory
        externalMemoryMap[string] = [

            ["EXT_RAM", {
                comment: "External RAM",
                name: "EXT_RAM",
                base: 0x80000000, 
                len:  0x10000000
            }],

        ];

    override config string codeMemory = "EXT_RAM";
    override config string dataMemory = "EXT_RAM";
    override config string stackMemory = "EXT_RAM";

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
 *  @(#) ti.platforms.simDM740; 1, 0, 0,98; 2-23-2010 16:52:52; /db/ztree/library/trees/platform/platform-k32x/src/
 */

