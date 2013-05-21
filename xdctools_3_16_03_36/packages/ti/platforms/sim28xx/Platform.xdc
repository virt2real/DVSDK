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

package ti.platforms.sim28xx;

/*!
 *  ======== Platform ========
 *  Simulation-based Platform support for 28xx platforms
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
        boardName:      "sim28xx",
        boardFamily:    "sim28xx",
        boardRevision:  null
    };

    /*!
     *  ======== CPU ========
     *  The CPU simulated by this platform.
     *
     *  The device simulated is determined by the platform instance name
     *  or if this does not name a ti.catalog.c2800 module, then we 
     *  simulate a TMS320C2812.
     */
    readonly config xdc.platform.IExeContext.Cpu   CPU = {      
        id:             "0",
        clockRate:      150.0,
        catalogName:    "ti.catalog.c2800",
        deviceName:     "TMS320C2812",
        revision:       null,
    };
    
instance:

    /*!
     *  ======== deviceName ========
     *  The CPU simulated by this simulator platform.
     *
     *  This parameter is optional. If it's not set, then the Platform module
     *  parameter CPU.deviceName is used.
     */
    config string deviceName;

    override readonly config xdc.platform.IPlatform.Memory externalMemoryMap[string] = [
    /* The base address and length of SRAM on ezdsp2812.
     */
        ["SRAM",
            {
                name: "SRAM",
                base: 0x100000,
                len:  0x10000,
                page: 0,
                space: "code/data"
            }
        ],
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

    override config string codeMemory = "SRAM";
    
    override config string dataMemory = "SRAM";

    override config string stackMemory = "LSARAM";
};
/*
 *  @(#) ti.platforms.sim28xx; 1, 0, 1, 1,25; 2-23-2010 17:01:37; /db/ztree/library/trees/platform/platform-k32x/src/
 */

