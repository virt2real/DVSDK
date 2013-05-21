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
 *  Platform support for the evmDRA446
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
        boardName:      "evmDRA446",
        boardFamily:    "evmDRA446",
        boardRevision:  null,
    };
        
    readonly config xdc.platform.IExeContext.Cpu CPU = {        
        id:             "0",
        clockRate:      552,
        catalogName:    "ti.catalog.c6000",
        deviceName:     "TMS320CDRA446",
        revision:       "",
    };
    
instance:

    override readonly config xdc.platform.IPlatform.Memory
        externalMemoryMap[string] = [
            ["EMIFA", {name: "EMIFA", base: 0x40000000, len: 0x8000000}],
            ["EMIFB", {name: "EMIFB", base: 0x60000000, len: 0x8000000}],
        ];

    override config string codeMemory = "EMIFA";
    
    override config string dataMemory = "EMIFA";

    override config string stackMemory = "EMIFA";
};
/*
 *  @(#) ti.platforms.evmDRA446; 1, 0, 0,247; 2-23-2010 16:52:21; /db/ztree/library/trees/platform/platform-k32x/src/
 */

