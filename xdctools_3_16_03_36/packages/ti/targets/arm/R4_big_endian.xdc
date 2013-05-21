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
import ti.targets.ITarget;

/*!
 *  ======== R4_big_endian.xdc ========
 *  Cortex R4 big endian thumb2 target
 */
metaonly module R4_big_endian inherits ti.targets.arm.IR4_big_endian {
    override readonly config string name        = "R4_big_endian";
    override readonly config string suffix      = "r4e";
    override readonly config string rts         = "ti.targets.arm.rtsarm";

    override readonly config xdc.bld.ITarget.Model model = {
        endian: "big",
    };

    override readonly config ti.targets.ITarget.Command cc = {
        cmd:  "cl470 -c",
        opts: "--endian=big -mv7R4 --abi=ti_arm9_abi"
    };

    override readonly config ti.targets.ITarget.Command asm = {
        cmd:  "cl470 -c",
        opts: "--endian=big -mv7R4 --abi=ti_arm9_abi"
    };

    /*!
     *  ======== linkLib ========
     *  Default TMS470 cgtools runtime library to link with executable
     *  (comes from $rootDir/lib)
     */
    config string linkLib = "rtsv7R4_A_be_tiarm9.lib";
}
/*
 *  @(#) ti.targets.arm; 2, 0, 1, 0,202; 2-24-2010 16:24:12; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

