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

package ti.platforms.sim64Pxx;

/*!
 *  ======== Platform ========
 *  Platform support for the sim64Pxx
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
        boardName:      "sim64Pxx",
        boardFamily:    "sim64Pxx",
        boardRevision:  null,
    };
        
    readonly config xdc.platform.IExeContext.Cpu CPU = {        
        id:             "0",
        clockRate:      1000,
        catalogName:    "ti.catalog.c6000",
        deviceName:     "TMS320CTCI6482",
        revision:       "",
    };
    
instance:

    override readonly config xdc.platform.IPlatform.Memory
        externalMemoryMap[string] = [
            ["DDR", {name: "DDR", base: 0x80000000, len: 0x10000000}],
        ];

    /*!
     *  ======== deviceName ========
     *  The CPU simulated by this simulator platform.
     *
     *  This parameter is optional. If it's not set, then the Platform module
     *  parameter CPU.deviceName is used.
     */
    config string deviceName;

    /*!
     *  ======== ftpath ========
     *  Installation directory of the Foundational Tools Suite
     *
     *  The underlying simulation engine used to run executables produced
     *  using this platform is part of the Target Server / Foundational Tools
     *  product (http://www.hou.asp.ti.com/asp/sds/eft/projects/Foundation_Tools/Releases/index.html).
     */
    readonly config String ftpath;

    override config string codeMemory = "DDR";
    
    override config string dataMemory = "DDR";

    override config string stackMemory = "DDR";
};
/*
 *  @(#) ti.platforms.sim64Pxx; 1, 0, 0,277; 2-23-2010 16:51:58; /db/ztree/library/trees/platform/platform-k32x/src/
 */

