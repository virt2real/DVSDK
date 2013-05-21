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

/*
 *  ======== Settings.xdc ========
 */

/*!
 *  ======== Settings ========
 *  Global configuration settings for all Codec Engine packages
 *
 *  This module provides high-level configuration settings for all
 *  Codec Engine packages.
 *
 *  @a(Linking with Codec Engine Libraries)
 *
 *  When linking an executable, this module's profile config param is
 *  used to select which libraries are used. See the {@link #profile}
 *  config param below. There are three typical use-cases.
 *
 *  1. Link with Codec Engine libraries of a specific profile. Add the
 *  following to your application cfg script.
 *
 *  @p(code)
 *  // set all codec engine libraries to the given profile
 *  xdc.useModule('ti.sdo.ce.global.Settings').profile = "debug";
 *  @p
 *
 *  2. Link with Codec Engine libraries using the program's profile. Add
 *  the following to your application cfg script.
 *
 *  @p(code)
 *  // use the program's profile
 *  var Program = xdc.useModule('xdc.cfg.Program');
 *  xdc.useModule('ti.sdo.ce.global.Settings').profile = Program.build.profile;
 *  @p
 *
 *  3. Specify a profile on a per-package basis.
 *
 *  @p(code)
 *  // specify the profile for some select packages
 *  xdc.loadPackage('ti.sdo.ce').profile = "debug";
 *  xdc.loadPackage('ti.sdo.ce.video').profile = "debug";
 *  xdc.loadPackage('ti.sdo.ce.image').profile = "debug";
 *  xdc.loadPackage('ti.sdo.ce.speech').profile = "debug";
 *  xdc.loadPackage('ti.sdo.ce.audio').profile = "debug";
 *  @p
 *
 *  Note that the third method above does not actually use the `profile`
 *  config param. It sets the package's profile config param directly.
 *
 *  The default value for the `profile` config param is `release`.
 *  Thus, even when building your executable using a debug profile, the
 *  Codec Engine release libraries will be used. This helps to keep the
 *  executable size smaller when you want to debug the application code.
 */
metaonly module Settings
{
    /*!
     *  ======== profile ========
     *  Name the library profile to use at link time
     *
     *  If the Codec Engine libraries have been built using the profile
     *  named by this config param, then these libraries will be used
     *  when linking the final executable. Otherwise, a substitute
     *  library will be used. For example, if this config param is set to
     *  debug but there are only release libraries available, then the
     *  release library is used.
     */
    config String profile = "release";
}
/*
 *  @(#) ti.sdo.ce.global; 1, 0, 0,103; 12-2-2010 21:23:49; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

