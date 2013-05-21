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

package ti.platforms.evmTMS570PSF762;

/*!
 *  ======== Platform ========
 *  Simulation-based Platform support for TI Arm (470x) platforms
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
        boardName:      "evmTMS570PSF762",
        boardFamily:    "evmTMS570",
        boardRevision:  null
    };

    /*!
     *  ======== CPU ========
     *  The  Cortex R4 core
     */
    readonly config xdc.platform.IExeContext.Cpu CPU = {        
        id:             "0",
        clockRate:      150.0,
        catalogName:    "ti.catalog.arm",
        deviceName:     "TMS570PSF762",
        revision:       "",
    };

instance:

    /*!
     *  ======== flash_lo ========
     *  Determines which of two flash/iram configurations to use.
     *  
     *  if true, then FLASH memory occupies low memory and IRAM occupies high memory.
     *  if false, then FLASH memory occupies high memory and IRAM occupies low memory.
     */
    config Bool flash_lo = true;

    /*!
     *  ======== deviceName ========
     *  The CPU simulated by this simulator platform.
     *
     *  This parameter is optional. If it's not set, then the Platform module
     *  parameter CPU.deviceName is used.
     */
    config string deviceName;

    override config string codeMemory = "FLASH";
    override config string dataMemory = "IRAM";
    override config string stackMemory = "IRAM";
};
/*
 *  @(#) ti.platforms.evmTMS570PSF762; 1, 0, 1, 1,17; 2-23-2010 17:00:40; /db/ztree/library/trees/platform/platform-k32x/src/
 */

