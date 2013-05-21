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
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var suffix = prog.build.target.findSuffix(this);
    if (suffix == null) {
        return ("");
    }

    /* "mangle" program build attrs into an appropriate directory name */
    var lib = "lib/" + this.profile + "/TraceUtil.a" + suffix;

    print("    will link with " + this.$name + ":" + lib);

    return (lib);
}


/*
 *  ======== close ========
 */
function close()
{
//    print(this.$name + ".close() ...");

    /* if undefined, take profile from the Settings module */
    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.ce.global.Settings').profile;
    }

    // TODO: Does OS have to be Linux? How do we check that?
    var osalGlobal = xdc.useModule( 'ti.sdo.ce.osal.Global' );
    var ipc = xdc.useModule('ti.sdo.ce.ipc.Settings');
    //var os = xdc.useModule('ti.sdo.ce.osal.linux.Settings');

    // TODO: Fix this check.
    if (false && (ipc.commType != ipc.COMM_DSPLINK)) {
        if (ipc.commType != ipc.COMM_DSPLINK) {
            throw("ipc.commType [" + ipc.commType + "]" +
                 "must be set to COMM_DSPLINK to use TraceUtil.\n");
        }
        /* Try the old way of setting the OS */
        if (osalGlobal.runtimeEnv != osalGlobal.DSPLINK_LINUX) {
            throw("Error: Global.os must be set to linux and ipc must " +
                    "be set to DSPLINK to use" +
                    " TraceUtil.\n");
        }
    }

    if (this.TraceUtil.$used) {

        /* load the LogClient module */
        var LogClient = xdc.useModule( "ti.sdo.ce.bioslog.LogClient" );

        /* add init code for the TraceUtil */
        var cer = xdc.useModule( "ti.sdo.ce.CERuntime" );
        cer.addInitCode(
            "    /* init code contribution from " + this.$name + " */\n" +
            "    {\n" +
            "        extern Void TraceUtil_init();\n" +
            "        TraceUtil_init();\n" +
            "    }\n",
            true    // add this code early in the init
        );

    }
}
/*
 *  @(#) ti.sdo.ce.utils.trace; 1, 0, 1,307; 12-2-2010 21:28:07; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

