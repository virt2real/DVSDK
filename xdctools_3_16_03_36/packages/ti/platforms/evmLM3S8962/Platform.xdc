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
 *  Platform support for evmLM3S8962
 *
 */

package ti.platforms.evmLM3S8962;

/*!
 *  ======== Platform ========
 *  Platform support for the evmLM3S8962
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
        boardName:      "evmLM3S8962",
        boardFamily:    "evmLM3S8962",
        boardRevision:  null,
    };

    /* M3 Subsystem */
    readonly config xdc.platform.IExeContext.Cpu M3 = { 
        id:             "0",
        clockRate:      50.0,
        catalogName:    "ti.catalog.arm",
        deviceName:     "LM3S8962",
        revision:       "1.0",
    };

instance:
    override config string codeMemory = "FRAM";
    override config string dataMemory = "IRAM";
    override config string stackMemory = "IRAM";
};
/*
 *  @(#) ti.platforms.evmLM3S8962; 1, 0, 0,40; 2-23-2010 16:52:58; /db/ztree/library/trees/platform/platform-k32x/src/
 */

