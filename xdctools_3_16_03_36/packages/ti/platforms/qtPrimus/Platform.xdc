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

package ti.platforms.qtPrimus;

/*!
 *  ======== Platform ========
 *  Platform support for the qtPrimus
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
        boardName:      "qtPrimus",
        boardFamily:    "qtPrimus",
        boardRevision:  null,
    };
        
    readonly config xdc.platform.IExeContext.Cpu DSP = {        
        id:             "0",
        clockRate:      300.0,
        catalogName:    "ti.catalog.c6000",
        deviceName:     "TMS320DA830",
        revision:       "1.0",
    };
    
    readonly config xdc.platform.IExeContext.Cpu GPP = {
        id:             "1",
        clockRate:      300.0,
        catalogName:    "ti.catalog.arm",
        deviceName:     "TMS320DA830",
        revision:       "1.0",
    };

instance:

    /*
     *  ======== l1PMode ========
     *  Define the amount of L1P RAM used for L1 Program Cache.
     *
     *  Check the device documentation for valid values.
     */
    config String l1PMode;
    
    /*
     *  ======== l1DMode ========
     *  Define the amount of L1D RAM used for L1 Data Cache.
     *
     *  Check the device documentation for valid values.
     */
    config String l1DMode;
    
    /*
     *  ======== l2Mode ========
     *  Define the amount of L2 RAM used for L2 Cache.
     *
     *  Check the device documentation for valid values.
     */
    config String l2Mode;

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
 *  @(#) ti.platforms.qtPrimus; 1, 0, 0, 0,105; 2-23-2010 17:01:24; /db/ztree/library/trees/platform/platform-k32x/src/
 */

