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

/*!
 *  ======== Platform ========
 *  Platform support for the evmDM6446
 *
 *  This module implements xdc.platform.IPlatform and defines configuration
 *  parameters that correspond to this platform's Cpu's, Board's, etc.
 *
 *  The configuration parameters are initialized in this package's
 *  configuration script (package.cfg) and "bound" to the TCOM object
 *  model.  Once they are part of the model, these parameters are
 *  queried by a program's configuration script.
 */

metaonly module Platform inherits xdc.platform.IPlatform
{
    enum RuntimeEnv {
        STDIO,
        POSIX,
        BIOS
    };
    
    readonly config xdc.platform.IPlatform.Board BOARD = {      
        id:             "0",
        boardName:      "evmDM6446",
        boardFamily:    "evmDM6446",
        boardRevision:  null,
    };
        
    readonly config xdc.platform.IExeContext.Cpu DSP = {        
        id:             "0",
        clockRate:      567.0,
        catalogName:    "ti.catalog.c6000",
        deviceName:     "TMS320CDM6446",
        revision:       "1.0",
    };
    
    readonly config xdc.platform.IExeContext.Cpu GPP = {
        id:             "1",
        clockRate:      300.0,
        catalogName:    "ti.catalog.arm",
        deviceName:     "TMS320CDM6446",
        revision:       "1.0",
    };

instance:

    override readonly config xdc.platform.IPlatform.Memory
        externalMemoryMap[string] = [
            ["DDR2", {name: "DDR2", base: 0x80000000, len: 0x10000000}],
        ];

    /* default segment for code sections */
    override config string codeMemory = "DDR2";

    /* default segment for data sections */
    override config string dataMemory = "DDR2";

    /* default segment for stack sections */
    override config string stackMemory = "DDR2";

    /*!
     *  ======== runTime ========
     *  The runtime environment available to executables
     */
    config RuntimeEnv runTime = STDIO;

    /*!
     *  ======== singleCore ========
     *  no longer used!
     * @_nodoc
     */
    config Bool singleCore = true;
}
/*
 *  @(#) ti.platforms.evmDM6446; 1, 0, 0, 1,262; 2-23-2010 16:52:14; /db/ztree/library/trees/platform/platform-k32x/src/
 */

