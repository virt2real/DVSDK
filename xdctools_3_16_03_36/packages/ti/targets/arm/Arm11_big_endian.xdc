/* 
 *  Copyright (c) 2009 Texas Instruments and others.
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
 *  ======== Arm11_big_endian.xdc ========
 *
 */

import ti.targets.ITarget;

/*!
 *  ======== Arm11_big_endian.xdc ========
 *  TI Arm11 big endian target
 */
metaonly module Arm11_big_endian inherits ti.targets.arm.IArm {
    override readonly config string name        ="Arm11_big_endian"; 
    override readonly config string suffix      = "11e";
    override readonly config string isa         = "v6";    
    override readonly config string rts         = "ti.targets.arm.rtsarm";
    override readonly config xdc.bld.ITarget.Model model = {
        endian: "big"
    };
    override readonly config xdc.bld.ITarget.Module base = ti.targets.arm.Arm11;

    /*
     *  ======== compatibleSuffixes ========
     */
    override config String compatibleSuffixes[] = ["470e", "7e", "9e"];

    override readonly config ITarget.Command cc = {
        cmd:  "cl470 -c",
        opts: "-mv6 --abi=ti_arm9_abi"
    };

    override readonly config ITarget.Command asm = {
        cmd:  "cl470 -c",
        opts: "-mv6 --abi=ti_arm9_abi"
    };

    override readonly config ITarget.Command lnk = {
        cmd:  "lnk470",
        opts: "--silicon_version=6 --strict_compatibility=on"
    };

    /*!
     *  ======== linkLib ========
     *  Default Arm7 cgtools runtime library to link with 
     *  (options: rts16.lib, rts32.lib)
     */
    config string linkLib = "rtsv5_A_be_tiarm9.lib";
}
/*
 *  @(#) ti.targets.arm; 2, 0, 1, 0,202; 2-24-2010 16:24:12; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

