/* 
 *  Copyright (c) 2008 Texas Instruments and others.
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

package ti.platforms.sim6xxx;

/*!
 *  ======== Platform ========
 *  Simulation-based Platform support for 6xxx platforms
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
    /*!
     *  ======== BOARD ========
     *  This platform's board attributes
     */
    readonly config xdc.platform.IPlatform.Board BOARD = {
        id:             "0",
        boardName:      "sim6xxx",
        boardFamily:    "sim6xxx",
        boardRevision:  null
    };

    /*!
     *  ======== CPU ========
     *  The CPU simulated by this platform.
     *
     *  The device simulated is determined by the platform instance name
     *  or if this does not name a ti.catalog.c6000 module, we simulate
     *  a TMS320C6416.
     */
    readonly config xdc.platform.IExeContext.Cpu CPU = {        
        id:             "0",
        clockRate:      600.0,
        catalogName:    "ti.catalog.c6000",
        deviceName:     "TMS320C6416",
        revision:       "",
    };

instance:

    /*!
     *  ======== externalMemoryMap ========
     *  A mapping of memory names to memory objects for external memory.
     *
     *  This parameter defines the external portion of the platform's memory
     *  map.
     */
    override readonly config xdc.platform.IPlatform.Memory externalMemoryMap[string] = [
        ["SDRAM",
            {
                name: "SDRAM",
                base: 0x80000000,
                len: 0x01000000,
                space: "code/data",
            }
        ],
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
    config String ftpath;

    config String l1PMode;
    
    config String l1DMode;
    
    config String l2Mode;

    override config string codeMemory = "IRAM";
    
    override config string dataMemory = "SDRAM";
    
    override config string stackMemory = "SDRAM";
};
/*
 *  @(#) ti.platforms.sim6xxx; 1, 0, 1, 1,25; 2-23-2010 17:02:01; /db/ztree/library/trees/platform/platform-k32x/src/
 */

