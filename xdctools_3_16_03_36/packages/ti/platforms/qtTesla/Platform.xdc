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
 *  Platform support for the qtTesla
 */
metaonly module Platform inherits xdc.platform.IPlatform
{
    readonly config xdc.platform.IPlatform.Board BOARD = {      
        id:             "0",
        boardName:      "qtTesla",
        boardFamily:    "qtTesla",
        boardRevision:  null,
    };
        
    readonly config xdc.platform.IExeContext.Cpu CPU = {        
        id:             "0",
        clockRate:      466,
        catalogName:    "ti.catalog.c6000.nda",
        deviceName:     "Tesla",
        revision:       "",
    };
    
instance:

    override config string codeMemory = "L2SRAM";
    
    override config string dataMemory = "L2SRAM";

    override config string stackMemory = "L2SRAM";
};
/*
 *  @(#) ti.platforms.qtTesla; 1, 0, 0, 0,81; 2-23-2010 17:01:28; /db/ztree/library/trees/platform/platform-k32x/src/
 */

