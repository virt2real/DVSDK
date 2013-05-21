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
 *
 */

/*!
 *  ======== Platform ========
 *  Platform support for the dsk6455
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
        boardName:      "dsk6455",
        boardFamily:    "dsk6455",
        boardRevision:  null,
    };
        
    readonly config xdc.platform.IExeContext.Cpu CPU = {        
        id:             "0",
        clockRate:      1000,
        catalogName:    "ti.catalog.c6000",
        deviceName:     "TMS320C6455",
        revision:       "",
    };
    
instance:

    /*
     *  ======== memTab ========
     *  Define the dsk6455 memory map
     */
    override readonly config xdc.platform.IPlatform.Memory
        externalMemoryMap[string] = [
            ["DDR2", {name: "DDR2", base: 0xE0000000, len: 0x10000000}],
        ];

    override config string codeMemory = "IRAM";
    
    override config string dataMemory = "DDR2";

    override config string stackMemory = "DDR2";
};
/*
 *  @(#) ti.platforms.dsk6455; 1, 0, 0,263; 2-23-2010 16:52:11; /db/ztree/library/trees/platform/platform-k32x/src/
 */

