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

/*!
 *  ======== Platform ========
 *  Platform support for the evmDM365
 *
 *  This module implements xdc.platform.IPlatform and defines configuration
 *  parameters that correspond to this platform's Cpu's, Board's, etc.
 *
 *  The configuration parameters are initialized in this package's
 *  configuration script (package.cfg) and "bound" to the XDC object
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
    /*!
     *  ======== BOARD ========
     *  This platform's board attributes
     */
    readonly config xdc.platform.IPlatform.Board BOARD = { 
        id:             "0",
        boardName:      "evmDM365",
        boardFamily:    "evmDM365",
        boardRevision:  null
    };
    
    readonly config xdc.platform.IExeContext.Cpu CPU = { 
        id:             "0",
        clockRate:      216.0,
        catalogName:    "ti.catalog.arm",
        deviceName:     "TMS320DM365",
        revision:       "",
    };

instance:

    override readonly config xdc.platform.IPlatform.MemoryMap
        externalMemoryMap = [
            ["DDR",  {name: "DDR",  base: 0x80000000, len: 0x1000000}],
        ];

    /*
     *  ======== sectMap ========
     *  Define a placement of compiler generated output sections into
     *  memory regions defined in the memTab above.
     */
    override config string codeMemory = "DDR";
    override config string dataMemory = "DDR";
    override config string stackMemory = "DDR";
};
/*
 *  @(#) ti.platforms.evmDM365; 1, 0, 0,134; 2-23-2010 16:51:42; /db/ztree/library/trees/platform/platform-k32x/src/
 */

