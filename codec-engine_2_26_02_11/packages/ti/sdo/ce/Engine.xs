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
 *  ======== Engine.xs ========
 */

var dumpCreateFromServerInfo = true;

var _engineNames = {};

var _freeLocalGroupIds;
var _freeRemoteGroupIds;

/*
 *  ======== Engine.Instance.init ========
 *  Create a Engine instance
 */
function instance$meta$init(name, algs, server)
{
    var remote = false;

//    print('  creating engine "' + name + '":');

    /* engine names must be unique */
    if (_engineNames[name] != null) {
        throw new Error("the engine named '" + name
                + "' was created more than once");
    }
    _engineNames[name] = 1;

    for (var i = 0; i < algs.length; i++) {
        var algDesc = algs[i];
        //  print('    "' + algDesc.name + '": ' + algDesc.mod.$name);
        //  _printISA('        ', algDesc.mod);
        if (algDesc.local != true) {
            remote = true;
        }
    }

    this.name = name;
    this.algs = algs;
    this.server = server;
    this.$private.requiresServer = remote;
    return (this);
}

/*
 *  ======== close ========
 */
function close()
{
    trace(this.$name + ".close()");

    // set osalGlobal.armDspLinkConfigs[] map from invididual engines' maps

    // get all engine instances
    var insts = this.$instances;
    var osalGlobal = xdc.module("ti.sdo.ce.osal.Global");

    //print(this.$name + ".close(): Num engines = " + insts.length);

    _freeLocalGroupIds = new Array(insts.length);
    _freeRemoteGroupIds = new Array(insts.length);

    for (i = 0; i < insts.length; i++) {
        /* create, and init, each engine's "free group id's" arrays */
        _freeLocalGroupIds[i] = new Array(this.MAXGROUPID);
        _freeRemoteGroupIds[i] = new Array(this.MAXGROUPID);

        for (var k = 0; k < this.MAXGROUPID; k++) {
            _freeLocalGroupIds[i][k] = true;
            _freeRemoteGroupIds[i][k] = true;
        }

        var eng = insts[i];
        var algs = eng.algs;
        //print(eng.name + ": Num algs = " + algs.length);

        for (var j = 0; j < algs.length; j++) {
            var alg = algs[j];
            if (alg.groupId != undefined) {
                /*
                 * NOTE: Need to validate the range here, since this function
                 * is called before validate().
                 */
                if ((alg.groupId < 0) || (alg.groupId >= this.MAXGROUPID)) {
                    /* failed the range check */
                    /* Note, we print here as a workaround to bugzilla 1058 */
                    print("ERROR:  The codec named \"" + alg.name +
                        "\" is configured with an invalid groupId (" +
                        alg.groupId + ") - must be a positive integer less " +
                        "than " + this.MAXGROUPID);
                    throw new Error("The codec named \"" + alg.name +
                        "\" is configured with an invalid groupId (" +
                        alg.groupId + ") - must be a positive integer less " +
                        "than " + this.MAXGROUPID);
                }

                /* Remove groupId from the free list. */
                if (alg.local) {
                    _freeLocalGroupIds[i][alg.groupId] = false;
                }
                else {
                    _freeRemoteGroupIds[i][alg.groupId] = false;
                }
            }
        }
    }

    // For each engine, set the groupId of any of its algs, if undefined
    for (i = 0; i < insts.length; i++) {
        var eng = insts[i];
        var algs = eng.algs;

        for (var j = 0; j < algs.length; j++) {
            var alg = algs[j];
            if (alg.groupId == undefined) {
                // Set groupId for algs where it is undefined
                alg.groupId = getFreeGroupId(this, i, alg);
                //print("alg: " + alg.name + " groupId undefined, setting to "
                //      + alg.groupId);
            }
        }
    }

    // Bring in the ipc module, since CE has dependencies on Comm and
    // Processor (CERuntime_init() call Comm_init())
    var ipcSettings = xdc.useModule("ti.sdo.ce.ipc.Settings");

    for (var i = 0; i < insts.length; i++) {
        var inst = insts[i];
        if (inst.server == null) {
            continue;        // only consider those that have a server
        }

        // One of the engines requires a server, so we need the dsplink ipc.

        // Check if ipc has not been configured.
        if (ipcSettings.ipc == undefined) {
            if (osalGlobal.runtimeEnv == undefined) {
                warn(this.$name + ".close()- " +
                        "WARNING: Your application .cfg script does not " +
                        "specify either the osal.Global.runtimeEnv or the " +
                        "ipc for this engine. Will set to the default, " +
                        "ti.sdo.ce.ipc.dsplink.Ipc, and use default memory " +
                        "maps. For example, if Linux, fix this warning by " +
                        "adding the following to your .cfg script: ");
                warn("var global = xdc.useModule(\'ti.sdo.ce.osal.Global\');");
                warn("global.runtimeEnv = global.DSPLINK_LINUX;");
            }

            // Set the ipc to dsplink.
            var ipc = xdc.useModule('ti.sdo.ce.ipc.dsplink.Ipc');

            /* Set up default memory maps */
            trace(this.$name + ".close()- Setting ipc to " +
                    "ti.sdo.ce.ipc.dsplink.Ipc");
            ipc.dspLinkCfg = xdc.useModule('ti.sdo.ce.ipc.dsplink.DspLinkCfg');
            ipcSettings.ipc = ipc;
        }

        if (inst.armDspLinkConfig.memTable.length == 0) {
            // TODO: Check first if dsplinkconfig is set the old, CE 1.20 way,
            // eg, the app set osal.Global.armDspLinkConfig and expects the
            // engine's armDspLinkConfig to be set to this one.
            var osalGlobal = xdc.module('ti.sdo.ce.osal.Global');
            if (osalGlobal.armDspLinkConfig.memTable.length != 0) {
                print(this.$name + ".close - WARNING: " +
                        "your application .cfg script specifies the DspLink " +
                        "configuration for the server '" + inst.server + "' " +
                        "in a deprecated way (that was used in CE 1.20). It " +
                        "currently sets the 'osalGlobal.armDspLinkConfig = " +
                        "...\' field and it should be changed to set " +
                        "'<yourEngine>.armDspLinkConfig = ...' field " +
                        "instead (the DspLink configuration is now specified "+
                        "per server, instead of globally), with the same " +
                        "value. We will apply the global setting to this " +
                        "server, but you should correct your .cfg script to " +
                        "avoid this warning.");
                inst.armDspLinkConfig = osalGlobal.armDspLinkConfig;
            }

            //print(this.$name + ".close(): setting inst.armDspLinkConfig " +
            //      "to default");

            // Get the name of the ipc module
            var ipcName = ipcSettings.ipc.$name;

            //print(this.$name + ".close(). Using default link " +
            //        "configuration from module: " + ipcName);

            // Get the dsplink module (it may be different from
            // ti.sdo.ce.ipc.dsplink) used by the application.
            var dsplink = xdc.useModule(ipcName);

            // First have to make sure dsplink.dspLinkCfg has been configured
            // before we use it.
            if (dsplink.dspLinkCfg == undefined) {
                warn(this.$name + ".close(): Warning: dsplink module [ " +
                      ipcName + " ] has unconfigured dspLinkCfg parameter." +
                      " Setting to default: ti.sdo.ce.ipc.dsplink.DspLinkCfg");
                dsplink.dspLinkCfg =
                    xdc.useModule('ti.sdo.ce.ipc.dsplink.DspLinkCfg');
            }

            var linkCfgName = dsplink.dspLinkCfg.$name;

            // Check again for memTable.length == 0, since armDspLinkConfig may
            // have been set to osalGlobal.armDspLinkConfig.
            if (inst.armDspLinkConfig.memTable.length == 0) {
                trace(this.$name + ".close(): Setting engine [ " + inst.name +
                        " ].armDspLinkConfig to " +
                        linkCfgName + ".DEFAULT_ARMDSPLINKCONFIG[" +
                        Program.cpu.deviceName + "]");

                inst.armDspLinkConfig = dsplink.dspLinkCfg.
                    DEFAULT_ARMDSPLINKCONFIG[Program.cpu.deviceName];
            }
        }
        else {
            //print(this.$name + ".close(): inst.armDspLinkConfig was set");
        }
        if (inst.armDspLinkConfig.memTable.length == 0) {
            throw "\nError: server memory table is empty. Check application "
            + "configuration file to make sure your engine armDspLinkConfig "
            + "has been assigned to a valid configuration. Make sure the "
            + "the DEFAULT_ARMDSPLINKCONFIG object has a property for the "
            + Program.cpu.deviceName + " device name.";
        }
        ipcSettings.ipc.linkConfigs[inst.server] = {
            serverName : inst.server,
            linkCfg : inst.armDspLinkConfig
        };
    }
}

/*
 *  ======== getFreeGroupId ========
 */
function getFreeGroupId(theEngine, engIndex, alg)
{
    /* find the first free group id, mark it used and return it */
    for (var i = 0; i < theEngine.MAXGROUPID; i++) {
        if (alg.local) {
            if (_freeLocalGroupIds[engIndex][i] == true) {
                _freeLocalGroupIds[engIndex][i] = false;
                //print("getFreeGroupId: Returning " + i + " for local");
                return (i);
            }
        }
        else {
            if (_freeRemoteGroupIds[engIndex][i] == true) {
                _freeRemoteGroupIds[engIndex][i] = false;
                //print("getFreeGroupId: Returning " + i + " for remote");
                return (i);
            }
        }
    }
    //print("getFreeGroupId: Returning error");
}

/*
 *  ======== getObjectFromServerInfoFile ========
 */
function getObjectFromServerInfoFile( serverExecutable, serverPackage, fxnName )
{
    if (serverPackage == undefined) {
        throw "\nError: you must specify the name of the server package " +
              "as the third argument to " +
              (fxnName != undefined ? fxnName : "getObjectFromServerInfoFile") +
              "().";
    }
    if (serverExecutable == undefined) {
        throw "Error: you must specify the path to the server executable " +
              "as the second argument to " +
              (fxnName != undefined ? fxnName : "getObjectFromServerInfoFile") +
              "(); the path is relative to the server package directory.";

    }
    var serverInfoFile = "";
    try {
        serverInfoFile = xdc.getPackageBase( serverPackage ) + "/package/info/";
    } catch(e) {
        throw "Error: cannot find server package '" + serverPackage + "' " +
              "specified as the third argument to " +
              (fxnName != undefined ? fxnName :
                                      "getObjectFromServerInfoFile") +
              "(), along the package path. Verify that the package name is " +
              "correct and that the package is in your package path. " +
              "Details: " + e;
    }
    serverInfoFile += serverExecutable + ".info.js";
    if (!java.io.File( serverInfoFile ).exists()) {
        throw "Error: server info file '" + serverInfoFile+"' does not exist; "+
              "specified serverExecutable='" + serverExecutable + "', " +
              "serverPackage='" + serverPackage  + "'; verify that your " +
              "server package has been properly built and released.";
    }
    return xdc.module( "ti.sdo.ce.osal.Global" ).parseInfoFile(serverInfoFile);
}

/*
 *  ======== createFromServer ========
 */
function createFromServer( engineName, serverExecutable, serverPackage )
{
    var srvrObj = getObjectFromServerInfoFile( serverExecutable, serverPackage,
                  "createFromServer" );
    var algs = [];
    CFS_trace("Info: Configuring engine named '" + engineName +
            "' from the info file for DSP server '" + serverExecutable +
            "',\n          located in package '" + serverPackage + "':");
    var exeFileName = ("" + serverExecutable).replace( /.*\//g, "");
    CFS_trace("      Target app will look for the DSP server image '" +
            exeFileName + "' in its current directory.");

    for (var i = 0; i < srvrObj["server algorithms"].algs.length; i++) {
        var alg = srvrObj["server algorithms"].algs[i];
        CFS_trace("      Adding codec '" + alg.name + "' (" + alg.mod + "), " +
               "scratch groupId=" + alg.groupId);
        var mod = xdc.useModule( alg.mod );
        if ((alg.ialgFxns           != mod.ialgFxns) ||
            (alg.rpcProtocolVersion != mod.rpcProtocolVersion) ||
            (alg.uuid               != mod.uuid)) {
            print("\n\n" +
                "WARNING: Codec '" + alg.name + "' from package '" + alg.pkg +
                "' found on your package path in directory '" +
                xdc.getPackageBase(alg.pkg) + "' " +
                "is different from the codec " +
                "that was used to build the server. You will NOT be able to " +
                "create and run this codec from your application. Details: \n" +
                "   module name: '" + alg.mod + "'\n" +
                "   ialgFxns:           server: '" + alg.ialgFxns +
                    "', app: '" + mod.ialgFxns + "'\n" +
                "   rpcProtocolVersion: server: " + alg.rpcProtocolVersion +
                    ", app: " + mod.rpcProtocolVersion + "\n" +
                "   uuid:               server: " + alg.uuid +
                    ", app: " + mod.uuid + "\n" +
                "   package version:    server: [" + alg.version +
                    "], app: [" + mod.$package.$vers + "]\n" +
                "\n\n" );
        }
        algs[algs.length] = {
            name:    alg.name,
            mod:     mod,
            local:   false,
            groupId: alg.groupId
        };
    }

    var eng = this.create( engineName, algs );

    var ipc = xdc.useModule('ti.sdo.ce.ipc.dsplink.Ipc');
    var armDspLinkConfig = {
        memTable : getDspMemTableFromServer(serverExecutable, serverPackage),
        doPowerControl : false,
        dspManagement : ipc.BootAndLoadDsp
    };

    if (Program.cpu.deviceName.match(/^OMAPL13[78]$/)) {
        armDspLinkConfig.doPowerControl = true;
    }

    /*
     * For WinCE DM644x, the [current] bootloader doesn't turn
     * on the DSP - so we set the default .doPowerControl field
     * to allow Link's power control code to turn on the DSP.
     *
     * Note that once LPM is supported, we may remove this and
     * restore the .doPowerControl to false, same as Linux.
     */
    if ((Program.cpu.deviceName.match(/^TMS320CDM6446$/)) &&
            (Program.build.target.os == "WindowsCE")) {
        armDspLinkConfig.doPowerControl = true;
    }

    eng.server = exeFileName;
    eng.armDspLinkConfig = armDspLinkConfig;
//    eng.armDspLinkConfig.memTable =
//        getDspMemTableFromServer( serverExecutable, serverPackage )
    return eng;
}


/*
 *  ======== getDspMemTableFromServer ========
 */
function getDspMemTableFromServer( serverExecutable, serverPackage )
{
    CFS_trace("Info: Reading DSP memory map from the info " +
           "file for DSP server '" + serverExecutable + "',\n" +
           "      located in package '" +
           serverPackage + "':");
    var srvrObj = getObjectFromServerInfoFile(serverExecutable, serverPackage,
                  "getDspMemTableFromServer");
    var oddCount = 0;
    var lastObj = null;
    if (!("DSP memory map" in srvrObj)) {
        throw new Error("ERROR: The DSP server has no memory map " +
              "information in the info.js file.");
    }
    for (var i = 0; i < srvrObj["DSP memory map"].length; i++) {
        var segObj = srvrObj["DSP memory map"][i];
        var segName = segObj[0];
        var segData = segObj[1];
        if (segData.nonstandard) {
            if (oddCount == 0) {
                print("Warning: DSP server '" + serverExecutable + "' has a " +
                    "non-standard memory segment, '" + segName + "'. " +
                    "You may not be able to load the DSP server. If so, you " +
                    "must define the <yourEngine>.armDspLinkConfig.memTable " +
                    "configuration field manually.");
            } else {
                print("Warning: another non-standard DSP memory segment: " +
                       "'" + segName + "'.");
            }
            delete segData.nonstandard;
            ++oddCount;
        }
    }
    return srvrObj[ "DSP memory map" ];
}


/*
 *  ======== validate ========
 *  Validate that all the engines are properly configured
 */
function validate()
{
    //print(this.$name + ".validate()");

    /* get all engine instances */
    var insts = this.$instances;

    /* check each engine instance */
    for (var i = 0; i < insts.length; i++) {
        var inst = insts[i];
        //  print("Engine '" + inst.name + "', server = " + inst.server);

        /* ensure that each engine with non-local algs has a server */
        if (inst.$private.requiresServer) {
            if (inst.server == null) {
                if (this.$package.Server.$used == 0) {
                    print("Warning: Engine " + inst.name +
                            " does not have a server");
                }
            }
            else {
                /* ensure that the server actually supports the specified
                 * algorithms
                 */
            }
        }

        var algs = inst.algs;

        /*
         *  Validate that the alg.groupIds are within legal limits. Also
         *  make sure the alg name does not include a ':', since this character
         *  is reserved for delimiting an overriding priority and a
         *  'use external heap' flag that can be appended to the alg name
         *  that is passed to Engine_open().
         */
        for (var j = 0; j < algs.length; j++) {
            var alg = algs[j];

            if (alg.name.indexOf(":") >= 0) {
                throw new Error("Codec name \'" + alg.name +
                        "\' cannot contain reservered character \':\'");
            }

            if (alg.groupId != undefined) {
                /* the alg specified a group Id.  Validate the range */
                if ((alg.groupId < 0) || (alg.groupId >= this.MAXGROUPID)) {
                    /* failed the range check */
                    /* Note, we print here as a workaround to bugzilla 1058 */
                    print("ERROR:  The codec named \"" + alg.name +
                        "\" is configured with an invalid groupId (" +
                        alg.groupId + ") - must be a positive integer less " +
                        "than " + this.MAXGROUPID);
                    throw new Error("The codec named \"" + alg.name +
                        "\" is configured with an invalid groupId (" +
                        alg.groupId + ") - must be a positive integer less " +
                        "than " + this.MAXGROUPID);
                }
            }
        }

        if (0) {
        /*
         *  For engine configuration, if there are multiple codecs of the
         *  same class but with different names (don't know why we would do
         *  that), we would open the right codec based on the name. So this
         *  code is zero'd out for now.
         */
        for (k = 0; k < algs.length; k++) {
            for (j = 0; j < k; j++) {
                if (algs[k].mod.getUUID() == algs[j].mod.getUUID()) {
                    throw("Error: \n" +
                            "    Two algs of same codec class: " +
                            algs[k].name + " and " + algs[j].name + ".\n" +
                            "    Please remove one of these from the Engine " +
                            "configuration.\n");
                }
            }
        }
        }

        // issue a warning if the engine instance has codecs with same names
        for (var j = 0; j < algs.length; j++) {
            for (var k = j + 1; k < algs.length; k++) {
                if (algs[j].name == algs[k].name) {
                    print( "WARNING: Engine '" + inst.name + "' has two " +
                        "codecs with the same name:" );
                    print( "    " +
                        (algs[j].local ? "local " : "remote") + " codec '"+
                        algs[j].name + "', module '" +
                        algs[j].mod.$name + "'" );
                    print( "    " +
                        (algs[k].local ? "local " : "remote") + " codec '"+
                        algs[k].name + "', module '" +
                        algs[k].mod.$name + "'" );
                    print( "    Only the first codec of the two above will be "+
                        "available.  To avoid the conflict, rename one of the "+
                        "codecs." );
                }
            }
        }

    }
}

/*
 *  ======== _printISA ========
 */
function _printISA(prefix, mod)
{
    var ICodec = xdc.om['ti.sdo.ce.ICodec'];
    var suffix = "";

    /* compute CRC32 as a 32-bit hash of the alg's unique name */
    var bytes = (new java.lang.String(mod.$name)).getBytes();
    var crc = new java.util.zip.CRC32();
    crc.update(bytes, 0, bytes.length);
    print(prefix + mod.$name + " hash = " + crc.getValue());

    if (!(mod instanceof ICodec.Module)) {
        print(prefix + "warning: " + mod.$name + "is not an ICodec");
    }

    for (var obj = mod.$orig.$super; obj != null; obj = obj.$super) {
        suffix += ' is a ' + obj.$type;
    }
    print(prefix + mod.$name + suffix);
}

/*
 *  ======== usesIDMA3 ========
 */
function usesIDMA3()
{
    /* get all engine instances */
    var insts = this.$instances;

    /* check each engine instance */
    for (var i = 0; i < insts.length; i++) {
        var inst = insts[i];
        var algs = inst.algs;

        for (var j = 0; j < algs.length; j++) {
            var alg = algs[j];

            if (alg.local) {
                if (alg.mod.idma3Fxns != null && alg.mod.idma3Fxns != "") {
                    return (true);
                }
            }
        }
    }

    return (false);
}

/*
 *  ======== usesIRES ========
 */
function usesIRES()
{
    /* get all engine instances */
    var insts = this.$instances;

    /* check each engine instance */
    for (var i = 0; i < insts.length; i++) {
        var inst = insts[i];
        var algs = inst.algs;

        for (var j = 0; j < algs.length; j++) {
            var alg = algs[j];

            if (alg.local) {
                if (alg.mod.iresFxns != null && alg.mod.iresFxns != "") {
                    return (true);
                }
            }
        }
    }

    return (false);
}

/*
 *  ======== hasServer ========
 *  Return true, if one of the Engine instances has a non-null server.
 */
function hasServer()
{
    /* get all engine instances */
    var insts = this.$instances;

    /* check each engine instance */
    for (var i = 0; i < insts.length; i++) {
        var inst = insts[i];
        /* Check if engine uses a server */
        if (inst.server != null) {
            //print("***Engine.hasServer(): Found server, returning true");
            return (true);
        }
    }

    //print("***Engine.hasServer(): returning false");
    return (false);
}

/*
 *  ======== warn ========
 *  For warnings that we may not really want to print. eg, for configurations
 *  with osal.Global.runtimeEnv set istead of osal.Global.os, or if the app
 *  .cfg has not configured ce.ipc.Settings.
 */
function warn(msg)
{
    print(msg);
}

/*
 *  ======== trace ========
 */
function trace(msg)
{
//    print("TRACE:  " + msg);
}

/*
 *  ======== CFS_trace ========
 *  CreateFromServer Trace
 */
function CFS_trace(msg)
{
    if (dumpCreateFromServerInfo) {
        print(msg);
    }
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,432; 12-2-2010 21:19:07; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

