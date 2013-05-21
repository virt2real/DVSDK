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
 *  Platform support for the evmDM357
 *
 *  This module implements xdc.platform.IPlatform and defines configuration
 *  parameters that correspond to this platform's Cpu's, Board's, etc.
 */

metaonly module Platform inherits xdc.platform.IPlatform
{
    readonly config xdc.platform.IPlatform.Board BOARD = {      
        id:             "0",
        boardName:      "evmDM357",
        boardFamily:    "evmDM357",
        boardRevision:  null,
    };
        
    readonly config xdc.platform.IExeContext.Cpu DSP = {        
        id:             "0",
        clockRate:      540.0,
        catalogName:    "ti.catalog.c6000",
        deviceName:     "TMS320DM357",
        revision:       "1.0",
    };
    
    readonly config xdc.platform.IExeContext.Cpu GPP = {
        id:             "1",
        clockRate:      270.0,
        catalogName:    "ti.catalog.arm",
        deviceName:     "TMS320DM357",
        revision:       "1.0",
    };

instance:

    override readonly config xdc.platform.IPlatform.Memory
        externalMemoryMap[string] = [
            ["DDR2", {name: "DDR2", base: 0x80000000, len: 0x10000000}],
        ];

    /* default segment for data sections */
    override config string dataMemory = "DDR2";

    /* default segment for stack sections */
    override config string stackMemory = "DDR2";
}
/*
 *  @(#) ti.platforms.evmDM357; 1, 0, 0,142; 2-23-2010 16:52:40; /db/ztree/library/trees/platform/platform-k32x/src/
 */

