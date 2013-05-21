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
 *
 */

package host.platforms.arm;

/*!
 *  ======== Platform ========
 *  ARM-on-Linux platform support
 *
 *  This module implements xdc.platform.IPlatform and defines configuration
 *  parameters that correspond to this platform's Cpu's, Board's, etc.
 */

metaonly module Platform inherits xdc.platform.IPlatform
{
    /*!
     *  ======== BOARD ========
     *  @_nodoc
     *  this structure exists to satisfy the
     *  IPlatform interface requirements; these fields are largely
     *  unnecessary for host platforms.
     */
    readonly config xdc.platform.IPlatform.Board BOARD = {      
        id:             "0",
        boardName:      "ARM",
        boardFamily:    "ARM",
        boardRevision:  null
    };

instance:

    /*!
     *  ======== deviceName ========
     *  The CPU simulated by this platform.
     *
     *  This parameter is required.
     */
    config string deviceName = "TMS320CDM6446";

    /*!
     *  ======== catalogName ========
     *  The name of the package that contains the module 'deviceName'.
     *
     *  This parameter is required.
     */
    config string catalogName = "ti.catalog.arm";
}
/*
 *  @(#) host.platforms.arm; 1, 0, 0, 0,25; 2-23-2010 16:58:36; /db/ztree/library/trees/platform/platform-k32x/src/
 */

