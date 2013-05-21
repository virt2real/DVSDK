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

package ti.platforms.sim54xx;

/*!
 *  ======== Platform ========
 *  Simulation-based Platform support for 54xx platforms
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
        boardName:      "sim54xx",
        boardFamily:    "sim54xx",
        boardRevision:  null
    };

    /*!
     *  ======== CPU ========
     *  The CPU simulated by this platform.
     *
     *  The device simulated is determined by the platform instance name
     *  or if this does not name a ti.catalog.c5400 module, then we 
     *  simulate a TMS320C5416.
     */
    readonly config xdc.platform.IExeContext.Cpu   CPU = {      
        id:             "0",
        clockRate:      100.0,
        catalogName:    "ti.catalog.c5400",
        deviceName:     "TMS320C5416",
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

    override config string codeMemory = "EPROG0";
    
    override config string dataMemory = "D_DARAM03";

    override config string stackMemory = "D_DARAM03";
    
    /*!
     *  ======== pmst ========
     *  The value of the register PMST.
     *
     *  This parameter determines memory map. If the configuration parameters
     *  `{@link ti.platforms.sim54xx.Platform#externalMemoryMap}` or
     *  `{@link ti.platforms.sim54xx.Platform#customMemoryMap}` are set, the
     *  memory addresses and sizes must fit within address spaces defined by
     *  `pmst`. Complete description of the PMST register and the memory maps
     *  for 54xx based devices and platforms is available in datasheets for
     *  54xx devices.
     */
    config Bits32 pmst = 0xffe0;
};
/*
 *  @(#) ti.platforms.sim54xx; 1, 0, 1, 1,25; 2-23-2010 17:01:46; /db/ztree/library/trees/platform/platform-k32x/src/
 */

