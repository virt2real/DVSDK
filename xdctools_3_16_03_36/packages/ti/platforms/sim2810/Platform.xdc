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

package ti.platforms.sim2810;

/*!
 *  ======== Platform ========
 *  Simulation-based Platform support for 2810 platforms
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
        boardName:      "sim2810",
        boardFamily:    "sim2810",
        boardRevision:  null
    };

    /*!
     *  ======== CPU ========
     *  The CPU simulated by this platform.
     *
     */
    readonly config xdc.platform.IExeContext.Cpu   CPU = {      
        id:             "0",
        clockRate:      150.0,
        catalogName:    "ti.catalog.c2800",
        deviceName:     "TMS320C2810",
        revision:       null,
    };
    
instance:

    override config string codeMemory = "H0SARAM";
    
    override config string dataMemory = "LSARAM";

    override config string stackMemory = "MSARAM";
};
/*
 *  @(#) ti.platforms.sim2810; 1, 0, 0,278; 2-23-2010 17:01:32; /db/ztree/library/trees/platform/platform-k32x/src/
 */

