/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/*!
 *  ======== package.xdc ========
 *  Codec Engine speech encoder example which utilizes a speech encoder
 *  codec which implements the ISPHENC XDM speech interface.
 *
 *  This example builds using the XDC build tools, and is portable to
 *  several execution environments.  The following files are
 *  included in this package:
 *  @p(dlist)
 *      - `package.xdc`
 *          This file is required to declare a globally unique name for this
 *          package.
 *      - `package.bld`
 *          This file is the build script describing the application to the
 *          XDC built tools.
 *      - `makefile`
 *          A usability makefile wrapper around the XDC build tools.
 *      - `local.cfg`
 *          The XDC configuration file for this executable, when configured
 *          to run "local" codecs.  This is the typical configuration for
 *          single processor excution environments.
 *      - `local.tcf`
 *          The BIOS configuration file for this executable.  This file is
 *          only necessary when building for a BIOS runtime environment.
 *          It's base name must match that of the XDC config file.
 *      - `remote.cfg`
 *          The XDC configuration file for this executable, when configured
 *          to run "remote" codecs.  This is the typical configuration for
 *          multiple processor excution environments.
 *      - `app.c`
 *          The primary source file for this executable.
 *      - `main_BIOS.c` and `main_native.c`
 *          The execution runtime-specific entry point for this executable.
 *          This isolates any runtime-specific startup code from the generic
 *          application.
 */
package ti.sdo.ce.examples.apps.speech [1, 0, 0] {
}
/*
 *  @(#) ti.sdo.ce.examples.apps.speech; 1, 0, 0,77; 12-2-2010 21:20:24; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

