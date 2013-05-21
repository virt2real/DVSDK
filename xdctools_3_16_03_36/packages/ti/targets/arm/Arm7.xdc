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
 *  ======== Arm7.xdc ========
 *
 */

import ti.targets.ITarget;

/*!
 *  ======== Arm7.xdc ========
 *  TI Arm7 little endian target
 */
metaonly module Arm7 inherits ti.targets.arm.IArm {
    override readonly config string name             = "Arm7"; 
    override readonly config string suffix           = "7";
    override readonly config string isa              = "v4T";    
    override readonly config string rts              = "ti.targets.arm.rtsarm";
    override readonly config xdc.bld.ITarget.Model model = {
        endian: "little"
    };

    /*
     *  ======== compatibleSuffixes ========
     */
    override config String compatibleSuffixes[] = ["470"];

    override readonly config ITarget.Command cc = {
        cmd:  "cl470 -c",
        opts: " -me -mv4 --abi=ti_arm9_abi"
    };

    override readonly config ITarget.Command asm = {
        cmd:  "cl470 -c",
        opts: " -me -mv4 --abi=ti_arm9_abi"
    };

    override readonly config ITarget.Command lnk = {
        cmd:  "lnk470",
        opts: "--silicon_version=4 --strict_compatibility=on"
    };

    /*!
     *  ======== linkLib ========
     *  Default Arm7 cgtools runtime library to link with 
     *  (options: rts16e.lib, rts32e.lib)
     */
    config string linkLib = "rts32e.lib";
    
}
/*
 *  @(#) ti.targets.arm; 2, 0, 1, 0,202; 2-24-2010 16:24:12; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

