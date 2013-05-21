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

package ti.platforms.dsk5416;

/*!
 *  ======== Platform ========
 *  Platform support for the dsk5416
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
        boardName:      "dsk5416",
        boardFamily:    "dsk5416",
        boardRevision:  null,
    };
    
    readonly config xdc.platform.IExeContext.Cpu CPU = {
        id:             "0",
        clockRate:      160.0,
        catalogName:    "ti.catalog.c5400",
        deviceName:     "TMS320C5416",
        revision:       "",
    };

instance:
    /*
     *  ======== memTab ========
     */
    override readonly config xdc.platform.IPlatform.Memory
        externalMemoryMap[string] = [
            ["EPROG0", {name: "EPROG0", page: 0, base: 0x8000,  len: 0x7f80}],
            ["VECT",   {name: "VECT",   page: 0, base: 0xff80,  len: 0x80}],
            ["EPROG1", {name: "EPROG1", page: 1, base: 0x10000, len: 0x8000}],
            ["EPROG2", {name: "EPROG2", page: 1, base: 0x18000, len: 0x8000}],
        ];

    override config string codeMemory = "EPROG0";
    
    override config string dataMemory = "D_DARAM03";

    override config string stackMemory = "D_DARAM03";
};
/*
 *  @(#) ti.platforms.dsk5416; 1, 0, 0,277; 2-23-2010 16:53:13; /db/ztree/library/trees/platform/platform-k32x/src/
 */

