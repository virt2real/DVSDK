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
 *  Platform support for the osk5912
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
    readonly config xdc.platform.IPlatform.Board BOARD = {      
        id:             "0",
        boardName:      "osk5912",
        boardFamily:    "osk5912",
        boardRevision:  null,
    };
        
    readonly config xdc.platform.IExeContext.Cpu DSP = {        
        id:             "0",
        clockRate:      192.0,
        catalogName:    "ti.catalog.c5500",
        deviceName:     "TMS320C5912",
        revision:       "1.0",
    };
    
    readonly config xdc.platform.IExeContext.Cpu GPP = {
        id:             "1",
        id:             "0",
        clockRate:      192.0,
        catalogName:    "ti.catalog.arm",
        deviceName:     "TMS320C5912",
        revision:       "1.0",
    };

instance:

    /*
     *  ======== memTab ========
     *  Define the osk5912 memory map
     */
    override readonly config xdc.platform.IPlatform.MemoryMap
        externalMemoryMap = [];
}
/*
 *  @(#) ti.platforms.osk5912; 1, 0, 1, 0,276; 2-23-2010 16:53:32; /db/ztree/library/trees/platform/platform-k32x/src/
 */

