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
 *  Codec Engine encode-decode example which utilizes speech codecs that
 *  implement the 0.9 xDM speech interfaces.
 *
 *  This example is a modified version of the general speech_copy example,
 *  built specifically for the MVArm9 and UCArm9 targets, which uses the Link
 *  Abiter Daemon, (LAD), for shared access of a DSP server.
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
 *      - `remote.cfg`
 *          The XDC configuration file for this executable, when configured
 *          to run "remote" codecs.  This is the typical configuration for
 *          multiple processor execution environments.
 *      - `app.c`
 *          The primary source file for this executable.
 *      - `main_native.c`
 *          The execution runtime-specific entry point for this executable.
 *          This isolates any runtime-specific startup code from the generic
 *          application.
 */
package ti.sdo.ce.examples.apps.speech_copy_LAD [1, 0, 0] {
}
/*
 *  @(#) ti.sdo.ce.examples.apps.speech_copy_LAD; 1, 0, 0,224; 12-2-2010 21:20:31; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

