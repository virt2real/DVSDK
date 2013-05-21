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

package ti.platforms.evm5515;

/*!
 *  ======== Platform ========
 *  Platform support for the evm5515. 
 *
 *  This module implements xdc.platform.IPlatform and defines configuration
 *  parameters that correspond to this platform's Cpu's, Board's, etc.
 *
 *  The configuration parameters are initialized in this package's
 *  configuration script (package.xs) and "bound" to the TCOM object
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
        boardName:      "evm5515",
        boardFamily:    "evm5515",
        boardRevision:  null
    };
    
    readonly config xdc.platform.IExeContext.Cpu CPU = { 
        id:             "0",
        clockRate:      100.0,
        catalogName:    "ti.catalog.c5500",
        deviceName:     "TMS320C5515",
        revision:       "",
    };

instance:

    override readonly config xdc.platform.IPlatform.MemoryMap
        externalMemoryMap = [
            ["NOR",   {name: "NOR",  base: 0x800000,   len: 0x400000}],
            ["NAND",  {name: "NAND", base: 0xe00000,   len: 0x100000}],
            ["SRAM",  {name: "SRAM", base: 0x050000,   len: 0x7b0000}]
        ];

    override config string codeMemory = "SARAM";
    
    override config string dataMemory = "DARAM";

    override config string stackMemory = "DARAM";
};
/*
 *  @(#) ti.platforms.evm5515; 1, 0, 0,6; 2-23-2010 16:59:30; /db/ztree/library/trees/platform/platform-k32x/src/
 */

