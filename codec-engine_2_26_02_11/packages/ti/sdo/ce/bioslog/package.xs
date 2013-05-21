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
//    print(this.$name + ".close() ...");

    /* if undefined, take profile from the Settings module */
    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.ce.global.Settings').profile;
    }

    if (this.LogServer.$used) {

        if (Program.build.target.suffix.match("64|674")) {

            /* BIOS C code and TCONF addition */

            /* add init code for the LogServer */
            var cer = xdc.useModule("ti.sdo.ce.CERuntime");
            cer.addInitCode(
                "    /* init code contribution from " + this.$name + " */\n" +
                "    {\n" +
                "        extern Void LogServer_initGenerated();\n" +
                "        LogServer_initGenerated();\n" +
                "    }\n",
                false   // meaning, don't add code early in init -- add it late
            );

            /* -------- add TCONF configuration for the LogServer -------- */

            /*
             *  Use time-stamp LOG for SoCrates
             */
            $$legacy.prog.module("LOG").TS = true;

            /*
             *  Enable trace and make a big LOG_system buffer.
             */
            $$legacy.prog.module("GBL").ENABLEALLTRC = true;
            $$legacy.prog.module("LOG").instance("LOG_system").bufLen = 32768;
            /* [dm]TODO: make all these numbers configurable */

            /*
             * EMIF performance log updated every 10 ms.
             */
            if (Program.cpu.deviceName.match(/DM6446$/)) {
                var trackPrd = $$legacy.prog.module("PRD").
                    create("ti_sdo_ce_bioslog_trackPrd");
                trackPrd.period = 10; /* 10ms, for default 1ms PRD frequency */
                trackPrd.fxn = $$legacy.prog.extern("LogTracker_track");
            }

            /*
             *  Initialize the create hook so we can track dynamic tasks
             */
            $$legacy.prog.module("TSK").CREATEFXN =
                     $$legacy.prog.extern("LogTracker_createHook");

            /*
             *  These LOGs are needed by modules in the ti.sdo.ce.bioslog package
             */
            var createLog =
                $$legacy.prog.module("LOG").create("ti_sdo_ce_bioslog_create");
            createLog.bufLen = 1024;
            createLog.dataType = "raw data";

            var synchLog =
                $$legacy.prog.module("LOG").create("ti_sdo_ce_bioslog_synch");
            synchLog.bufLen = 64;
            synchLog.logType = "fixed";
            synchLog.dataType = "raw data"

            var trackLog =
                $$legacy.prog.module("LOG").create("ti_sdo_ce_bioslog_track");
            trackLog.bufLen = 4096;
            trackLog.dataType = "raw data"

            // Must call prog.gen() to recreate the configuration model.
            $$legacy.prog.gen();
        }
        else {
            print('Warning:  ' + this.$name + '.LogServer module is enabled, ' +
                'but not supported on the ' + Program.build.target.suffix +
                'target');
        }
    }


    if (this.LogClient.$used) {
        if (Program.build.target.os == "Linux") {
            /* add init code for the LogClient */
            var cer = xdc.useModule( "ti.sdo.ce.CERuntime" );
            cer.addInitCode(
                "    /* init code contribution from " + this.$name + " */\n" +
                "    {\n" +
                "        extern Void LogClient_init();\n" +
                "        LogClient_init();\n" +
                "    }\n",
                false   // don't add code early in init -- add it late
            );
        }
        else {
            print('Warning:  ' + this.$name + '.LogClient module is enabled, ' +
                'but not supported on the ' + Program.build.target.os + 'OS');
        }
    }
}

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
    var name = "lib/release/bioslog";

    /* return the library name: name.a<arch> */
    var lib = name + ".a" + suffix;
    print("    will link with " + this.$name + ":" + lib);

    return (lib);
}
/*
 *  @(#) ti.sdo.ce.bioslog; 1, 0, 1,326; 12-2-2010 21:18:56; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

