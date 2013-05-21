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
 *  ======== Package.close ========
 *  Close this package; optionally (re)set other config parameters in the
 *  model
 */
function close()
{
    trace(this.$name + ".close() ...");
    var settings = this.Settings;
    var prog = Program;

    /* if undefined, take profile from the Settings module */
    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.ce.global.Settings').profile;
    }

//    trace(this.$name + ".close() useLinkArbiter: " +settings.useLinkArbiter);

    var global = xdc.useModule('ti.sdo.ce.osal.Global');

    // NOTE: if CE is used, and settings.ipc was not set by the app, then
    // CE package.close() would have set it (CE depends on ipc, since
    // CERuntime_init() calls Processor_init() and Comm_init()).

    trace(this.$name + ".close()- Settings.ipc = " + settings.ipc);

    /*
     *  If osal.Global.runtimeEnv has been used to set the ipc and os,
     *  figure out which ipc to plug in.
     */
    if ((settings.ipc == undefined) && (global.runtimeEnv != undefined)) {
        //
        //  The OS is configured through osal.Global.runtimeEnv, so use that
        //  to set ipc.
        //
        if (global.runtimeEnv == global.DSPLINK_LINUX) {
            // This may not work. In some cases, ipc.dsplink.close()
            // is happening before ipc.close() (eg, if the app .cfg file
            // uses the dsplink.Ipc module.)
            trace(this.$name + ".close(): setting ipc to dsplink");
            var dsplinkIpc = xdc.useModule('ti.sdo.ce.ipc.dsplink.Ipc');
            settings.ipc = dsplinkIpc;
        }
        else if ((global.runtimeEnv == global.DSPLINK_WINCE)) {
            trace(this.$name + ".close(): setting ipc to dsplink");
            var dsplinkIpc = xdc.useModule('ti.sdo.ce.ipc.dsplink.Ipc');
            settings.ipc = dsplinkIpc;
        }
        else if ((global.runtimeEnv == global.DSPLINK_BIOS) ||
                (global.runtimeEnv == global.DSPBIOS)) {

            trace(this.$name + ".close(): setting ipc to bios");
            var biosIpc = xdc.useModule('ti.sdo.ce.ipc.bios.Ipc');
            settings.ipc = biosIpc;

            if (global.runtimeEnv == global.DSPLINK_BIOS) {
                var link = xdc.useModule('ti.sdo.ce.ipc.dsplink.dsp.Settings');
            }
        }
        else if (global.runtimeEnv == global.LINUX) {
            trace(this.$name + ".close(): setting ipc to linux");
            var linuxIpc = xdc.useModule('ti.sdo.ce.ipc.linux.Ipc');
            settings.ipc = linuxIpc;
        }
        else if (global.runtimeEnv == global.NONE) {
            trace(this.$name + ".close(): setting ipc to noOS");
            var noOSIpc = xdc.useModule('ti.sdo.ce.ipc.noOS.Ipc');
            settings.ipc = noOSIpc;
        }
        else if (global.runtimeEnv == global.WINCE) {
            trace(this.$name + ".close(): setting ipc to noOS");
            var noOSIpc = xdc.useModule('ti.sdo.ce.ipc.noOS.Ipc');
            settings.ipc = noOSIpc;
        }
    }

    // If settings.ipc is undefined, just leave it. Osal.Global has a
    // dependency in Ipc, since it uses the type ipc.IIpc.ArmDspLinkConfig
    // for its DEFAULT_ARMDSPLINKCONFIG, which is needed for backwards
    // compatibility with CE 1.20. However, if we set settings.ipc to
    // one of the ipcs (eg ipc.linux), that will bring in the ipc library,
    // even when not used (eg, an osal memory test). Therefore, don't set
    // the ipc, to make it easier for osal porters to build osal tests
    // that don't require ports or re-builds of an ipc library.
    if (settings.ipc == undefined) {
        // Don't throw an exception, but may want to print warning.
        warn(this.$name + ": ipc undefined");
    }

    trace(this.$name + ".close() done!");
}

/*
 *  ======== Package.validate ========
 *  Verify the config params for this package; called after close()
 */
function validate()
{
    trace(this.$name + ".validate() ...");

}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    return (null);
}


/*
 *  ======== warn ========
 *  For warnings that we may not really want to print.
 */
function warn(msg)
{
    print("WARNING:  " + msg);
}

/*
 *  ======== trace ========
 */
function trace(msg)
{
    //print("TRACE:  " + msg);
}
/*
 *  @(#) ti.sdo.ce.ipc; 2, 0, 1,183; 12-2-2010 21:24:07; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

