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
 *  ======== close ========
 */
function close()
{
//    print(this.$name + ".close()");

    var Server = this;
    var Engine = xdc.useModule('ti.sdo.ce.Engine');

    if (Server.$used) {
        // print(this.$name + ".close(): using IPC");
        /* Load ipc - This causes ipc.Settings code to get generated */
        var ipcSettings = xdc.useModule('ti.sdo.ce.ipc.Settings');
        if (ipcSettings.commType != undefined) {
            if (ipcSettings.commType == ipcSettings.COMM_DSPLINKBIOS) {
                print(this.$name + ".close(): WARNING: ipc Using " +
                        "deprecated commType to set ipc. This may not " +
                        "be supported in future releases. Please add the " +
                        "following lines of code to eliminate this warning:");
                print("/**************** Set ipc ****************/");
                print("var ipcSettings = xdc.useModule(\'ti.sdo.ce.ipc.Settings\');");
                print("ipcSettings.ipc = xdc.useModule(\'ti.sdo.ce.ipc.bios.Ipc\');");
                print("xdc.useModule(\'ti.sdo.ce.ipc.dsplink.dsp\');");
                print("/*****************************************/");

                var biosIpc = xdc.useModule('ti.sdo.ce.ipc.bios.Ipc');
                print(this.$name + ".close(): setting ipc to bios");
                ipcSettings.ipc = biosIpc;

                print(this.$name + ".close(): using ipc.dsplink.dsp" +
                        ".Settings to pull in link libraries");
                xdc.useModule('ti.sdo.ce.ipc.dsplink.dsp.Settings');

                /* Transfer ipc settings to bios settings */
                biosIpc.armCommMsgSize = ipcSettings.armCommMsgSize;
                biosIpc.dspConfigureMsgqAndPool =
                    ipcSettings.dspConfigureMsgqAndPool;
                biosIpc.dspUseMsgqAndPool = ipcSettings.dspUseMsgqAndPool;
                biosIpc.dspCommUseExactMatch =
                    ipcSettings.dspCommUseExactMatch;
                biosIpc.dspCommMsgSize = ipcSettings.dspCommMsgSize;
                biosIpc.dspCommNumMsgs = ipcSettings.dspCommNumMsgs;
                if (ipcSettings.usePowerManagement != undefined) {
                    biosIpc.usePowerManagement = ipcSettings.usePowerManagement;
                }
                biosIpc.powerSaveMemoryBlockName =
                    ipcSettings.powerSaveMemoryBlockName;
            }
            else {
                var commType = "Unknown commType";
                var modName = "";
                if (ipcSettings.commType == ipcSettings.COMM_DSPLINK) {
                    commType = "COMM_DSPLINK";
                    modName = "ti.sdo.ce.ipc.dsplink";
                }
                else if (ipcSettings.commType == ipcSettings.COMM_POSIX) {
                    commType = "COMM_POSIX";
                    modName = "ti.sdo.ce.ipc.linux";
                }
                else if (ipcSettings.commType == ipcSettings.COMM_BIOS) {
                    commType = "COMM_BIOS";
                    modName = "ti.sdo.ce.ipc.bios";
                }
                else if (ipcSettings.commType == ipcSettings.COMM_NONE) {
                    commType = "COMM_NONE";
                    modName = "ti.sdo.ce.ipc.noOS";
                }
                print("WARNING: Using deprecated \'ipc.Settings.commType\'. " +
                        "Will not attempt to set ipc based on " +
                        "deprecated commType: ipc.Settings." + commType);
                print("Your application may fail to build or run correctly.");

                if (modName != "") {
                    print("Please try adding the following code to your " +
                          "cfg script to fix this problem: ");
                    print("/**************** Set ipc ****************/");
                    print("var ipcSettings = xdc.useModule(\'ti.sdo.ce.ipc.Settings\');");
                    print("ipcSettings.ipc = xdc.useModule(\'" + modName +
                          ".Ipc\');");
                    print("/*****************************************/");
                }
            }
        }
        // TODO: Fix this. It does not work if running on a single processor
        // using a server.
        ipcSettings.usesServer = true;
    }

    /* create default groupIds based on specified thread priorities */
    var pri2id = {};
    var id = 0;

    // make this object available for our friend ServerDataSheet.html.xdt
    this.$private.pri2id = pri2id;

    // Temp var for later...
    var i = 0;

    /* Create an array of "free" groupIds, and init them all to true (free) */
    var freeGroupIds = new Array(Engine.MAXGROUPID);
    for (i = 0; i < Engine.MAXGROUPID; i++) {
        freeGroupIds[i] = true;
    }

    /*
     * Walk the alg array, marking the explicitly requested groupId's used.
     * Also, assign default priority, if necessary.
     */
    for (i = 0; i < this.algs.length; i++) {
        var alg = this.algs[i];

        if (alg.groupId != undefined) {
            freeGroupIds[alg.groupId] = false;
        }

        /* assign a default priority, if necessary */
        if (alg.threadAttrs.priority == null) {
            print ('Remark:  Alg "' + alg.name + '" threadAttrs.priority ' +
                'was not set.  Assigning default priority of ' +
                (this.MINPRI + 1) + '.');

            alg.threadAttrs.priority = this.MINPRI + 1;
        }
    }

    for (i = 0; i < this.algs.length; i++) {
        var alg = this.algs[i];

        /* don't waste a free group id on algs which set it */
        if (alg.groupId == undefined) {
            /* create mapping between priority and a group id */
            if (pri2id[alg.threadAttrs.priority] == null) {
                while ((freeGroupIds[id] == false) &&
                    (id < Engine.MAXGROUPID)) {
                    id++;
                }
                pri2id[alg.threadAttrs.priority] = id;
                freeGroupIds[id] = false;
                id++;
            }
        }
    }

    /* create an array of algorithms for the default local engine */
    var engineAlgs = [];
    for (i = 0; i < this.algs.length; i++) {
        var alg = this.algs[i];

        var myGroupId = ((alg.groupId == undefined) ?
            pri2id[alg.threadAttrs.priority] : alg.groupId);

//        print("myGroupId:  " + myGroupId);

        engineAlgs.push({
            name: alg.name,
            mod: alg.mod,
            local: true,
            groupId: myGroupId
        });
    }

    /* create local engine and make it the default engine */
    Engine.local = Engine.create("local", engineAlgs);

    /* validate or auto-generate scratch config arrays */
    if (Program.build.target.suffix.match("64|674") != null) {
        var DSKT2 = xdc.loadPackage('ti.sdo.fc.dskt2').DSKT2;

        for (i = 0; i < this.algs.length; i++) {
            var alg = this.algs[i];

            var dScr = alg.mod.getDaramScratchSize(xdc.om['xdc.cfg.Program']);
            var sScr = alg.mod.getSaramScratchSize(xdc.om['xdc.cfg.Program']);
            var groupId = ((alg.groupId == undefined) ?
                pri2id[alg.threadAttrs.priority] : alg.groupId);
            var dCfg = DSKT2.DARAM_SCRATCH_SIZES[groupId];
            var sCfg = DSKT2.SARAM_SCRATCH_SIZES[groupId];

            if (this.autoGenScratchSizeArrays) {
                if (dScr > dCfg) {
                    DSKT2.DARAM_SCRATCH_SIZES[groupId] = dScr;
                }
                if (sScr > sCfg) {
                    DSKT2.SARAM_SCRATCH_SIZES[groupId] = sScr;
                }
            }

            else {
                if (dCfg < dScr) {
                    print ("Warning:  Alg \"" + alg.name +
                        "\" DARAM scratch size exceeds engine configuration" +
                        " for groupId " + groupId);
                }
                if (sCfg < sScr) {
                    print ("Warning:  Alg \"" + alg.name +
                        "\" SARAM scratch size exceeds engine configuration" +
                        " for groupId " + groupId);
                }
            }

        }
    }

    /* establish default RMS server thread attrs */
    if (this.threadAttrs.stackMemId == null) {
        this.threadAttrs.stackMemId = 0;
    }
    if (this.threadAttrs.stackSize == null) {
        /* Apply padding to "default" stack size of 1024 */
        this.threadAttrs.stackSize = 1024 + this.stackSizePad;
    }
    if (this.threadAttrs.priority == null) {
        this.threadAttrs.priority = this.MINPRI;
    }

    /*
     *  Use the default cache policy for the skels (invalidate input buffers,
     *  writeback output buffers) if not yet set.
     */
    if (this.skelCachingPolicy == undefined) {
        this.skelCachingPolicy = this.LOCALBUFFERINVWB;
    }
}

/*
 *  ======== validate ========
 *  Validate that all the Servers are properly configured
 */
function validate()
{
//    print(this.$name + ".validate()");

    var Server = this;
    var Engine = xdc.om['ti.sdo.ce'].Engine;
    var i = 0; // temp var for later

    for (i = 0; i < this.algs.length; i++) {
        var alg = this.algs[i];

        if ((alg.groupId < 0) || (alg.groupId > Engine.MAXGROUPID)) {
            throw ("Error:  Alg \"" + alg.name + "\" groupId out of range:  " +
                alg.groupId);
        }

        if ((alg.threadAttrs.priority < this.MINPRI) ||
            (alg.threadAttrs.priority > this.MAXPRI)) {
            throw ("Error:  Alg \"" + alg.name + "\" priority out of range:  " +
                alg.threadAttrs.priority);

        }
    }

    // dump the server configuration info into the program Info file
    var serverCfg = {};
    serverCfg.programName = Program.name;
    serverCfg.algs = [];
    for (i = 0; i < this.algs.length; i++) {
        var alg = this.algs[i];
        serverCfg.algs[i] = {
            name:               alg.name,
            pkg:                alg.mod.$package.$name,
            pkgVersion:         alg.mod.$package.$vers,
            mod:                alg.mod.$name,
            threadAttrs: {
                priority:       alg.threadAttrs.priority,
                stackSize:      alg.threadAttrs.stackSize
            },
            groupId:            alg.groupId,
            ialgFxns:           alg.mod.ialgFxns,
            idma3Fxns:          alg.mod.idma3Fxns,
            iresFxns:           alg.mod.iresFxns,
            serverFxns:         alg.mod.serverFxns,
            stubFxns:           alg.mod.stubFxns,
            rpcProtocolVersion: alg.mod.rpcProtocolVersion,
            uuid:               alg.mod.uuid
        };
    }

    /* Make sure there are no duplicate UUIDs */
    var algs = this.algs;
    for (i = 0; i < algs.length; i++) {
        for (j = 0; j < i; j++) {
            if (algs[i].mod.getUUID() == algs[j].mod.getUUID()) {
                throw("Error: \n" +
                      "    Two algs of the same codec class: " +
                        algs[i].name + " and " + algs[j].name + ".\n" +
                        "    Please remove one of these from the Server " +
                        "configuration.\n");
            }
        }
    }

    var osalGlobal = xdc.module('ti.sdo.ce.osal.Global');
    osalGlobal.addObjectToProgramInfoFile("server algorithms", serverCfg);

    // create server data sheet, but only if there are server algs
    if ((Program.build.target.suffix.match("64|674") != null) &&
        (Server.algs != undefined) &&
        (Server.algs.length > 0)) {
        var t = xdc.loadTemplate( "ti/sdo/ce/ServerDataSheet.html.xdt" );
        try {
            var outFileName = "./package/info/" + Program.name + ".DataSheet.html";
            print("\nNOTE: You can find the complete server data sheet in " +
                   outFileName);
            print(  "-----------------------------------------------------" +
                   outFileName.replace( /./g, "-" ) + "\n" );
            t.genFile(outFileName, this);
        }
        catch(e) {
            var message = "Server.xs Warning: Could not create Server data sheet"+
                " '" + outFileName + "'.\n\n" + "Details: " + e + "\n\n";
            print(message);
        }
    }
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,432; 12-2-2010 21:19:08; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

