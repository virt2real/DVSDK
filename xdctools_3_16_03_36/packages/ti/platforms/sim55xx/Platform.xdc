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

package ti.platforms.sim55xx;

/*!
 *  ======== Platform ========
 *  A simulation platform for C55xx-based platforms
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
        boardName:      "sim55xx",
        boardFamily:    "sim55xx",
        boardRevision:  null
    };

    /*!
     *  ======== CPU ========
     *  The CPU simulated by this platform.
     *
     *  The device simulated is determined by the platform instance name
     *  or if this does not name a ti.catalog.c5500 module, then we 
     *  simulate a TMS320C5510.
     */
    readonly config xdc.platform.IExeContext.Cpu CPU = {        
        id:             "0",
        clockRate:      200.0,
        catalogName:    "ti.catalog.c5500",
        deviceName:     "TMS320C5510",
        revision:       "",
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

    /*!
     *  ======== ftpath ========
     *  Installation directory of the Foundational Tools Suite
     *
     *  The underlying simulation engine used to run executables produced
     *  using this platform is part of the Target Server / Foundational Tools
     *  product (http://www.hou.asp.ti.com/asp/sds/eft/projects/Foundation_Tools/Releases/index.html).
     */
    readonly config String ftpath;

    override config string codeMemory = "SARAM";
    
    override config string dataMemory = "DARAM";

    override config string stackMemory = "DARAM";

    /*!
     *  ======== st3_55 ========
     *  The value of the MP/MC bit in the register ST3_55.
     *
     *  This parameter determines memory map. If the configuration parameter
     *  `{@link ti.platforms.sim55xx.Platform#customMemoryMap}` is set, the
     *  memory addresses and sizes must fit within address spaces defined by
     *  `st3_55`. Complete description of the ST3_55 register and the memory
     *  maps for 55xx based devices and platforms is available in device
     *  datasheets.
     */
    config Bool st3_55 = true;
};
/*
 *  @(#) ti.platforms.sim55xx; 1, 0, 1, 1,25; 2-23-2010 17:01:51; /db/ztree/library/trees/platform/platform-k32x/src/
 */

