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
 *  Platform support for the sim62xx
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
        boardName:      "sim62xx",
        boardFamily:    "sim62xx",
        boardRevision:  null,
    };
        
    readonly config xdc.platform.IExeContext.Cpu CPU = {        
        id:             "0",
        clockRate:      200.0,
        catalogName:    "ti.catalog.c6000",
        deviceName:     "TMS320C6204",
        revision:       "",
    };
    
instance:

    override readonly config xdc.platform.IPlatform.Memory
        externalMemoryMap[string] = [
            ["SBSRAM",  {name: "SBSRAM",  base: 0x0400000, len: 0x040000}],
            ["SDRAM0",  {name: "SDRAM0",  base: 0x2000000, len: 0x400000}],
            ["SDRAM1",  {name: "SDRAM1",  base: 0x3000000, len: 0x400000}],
        ];

    override config string codeMemory = "IPRAM";
    
    override config string dataMemory = "SDRAM0";

    override config string stackMemory = "SDRAM0";
};
/*
 *  @(#) ti.platforms.sim62xx; 1, 0, 0,277; 2-23-2010 16:51:56; /db/ztree/library/trees/platform/platform-k32x/src/
 */

