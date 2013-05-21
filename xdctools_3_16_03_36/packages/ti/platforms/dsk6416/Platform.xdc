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

package ti.platforms.dsk6416;

/*!
 *  ======== Platform ========
 *  Platform support for the dsk6416
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
        boardName:      "dsk6416",
        boardFamily:    "dsk6416",
        boardRevision:  null,
    };
        
    readonly config xdc.platform.IExeContext.Cpu CPU = {        
        id:             "0",
        clockRate:      600.0,
        catalogName:    "ti.catalog.c6000",
        deviceName:     "TMS320C6416",
        revision:       "",
    };
    
instance:

    override readonly config xdc.platform.IPlatform.Memory
        externalMemoryMap[string] = [
            ["SDRAM",  {name: "SDRAM",  base: 0x80000000, len: 0x01000000}],
        ];

    /*!
     *  ======== ftpath ========
     *  Installation directory of the Foundational Tools Suite
     *
     *  The underlying simulation engine used to run executables produced
     *  using this platform is part of the Target Server / Foundational Tools
     *  product (http://www.hou.asp.ti.com/asp/sds/eft/projects/Foundation_Tools/Releases/index.html).
     */
    readonly config String ftpath;

    /*
     *  ======== sectMap ========
     *  Define a placement of compiler generated output sections into
     *  memory regions defined in the memTab above.
     */
    override config string codeMemory = "IRAM";
    
    override config string dataMemory = "SDRAM";

    override config string stackMemory = "SDRAM";
};
/*
 *  @(#) ti.platforms.dsk6416; 1, 0, 0,278; 2-23-2010 16:51:33; /db/ztree/library/trees/platform/platform-k32x/src/
 */

