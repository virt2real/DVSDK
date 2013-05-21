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
serverEnv = {};
var logic = xdc.loadCapsule("logic.xs");
var wizard_constants = xdc.loadCapsule("wizard_constants.xs");
var gui;

/*
 *  ======== run ========
 */
function run( cmdr, args )
{
    var inst = this.$private
    inst.self = this;


    for (p in inst.self) inst[p] = inst.self[p];

    inst.cmdr = cmdr;
    inst.args = args;

    /* for each module in this package ... */
    for each (var mod in this.$package.$modules) {
        var cap = mod.$capsule;
        if (cap && "createPartControl" in cap) {
            gui = cap;
            break;
        }
    }

    if (!gui) {
        print("\nCannot start Codec Engine GenServer Wizard. Please " +
              "make sure the package ti.sdo.ce.wizards.genserver " +
              "is completely built.");
        return;
    }

    serverEnv.wizardVersion = wizard_constants.wizardVersion;

    /* store the cmd line params in our data structure
        all arguments are optional unless otherwise noted */
    serverEnv.xmlFile = inst.xmlFile;
    serverEnv.gui = inst.gui ? inst.gui : !serverEnv.xmlFile;
    serverEnv.shellLocation;

    serverEnv.argvArgs = [];
    for each (var a in inst.args) {
        serverEnv.argvArgs.push(a);
    }

    if (serverEnv.xmlFile) {
        /* replace since user can enter backward slashes on command line */
        serverEnv.xmlFile = (serverEnv.xmlFile + "").replace(/\\/g,"/");
    }
    inst.cmdr.verbose(inst.debugFlag);
    serverEnv.debug = inst.debugFlag;
    serverEnv.inst = inst;

    try {
        if (cmdr.tid) {
            serverEnv.tid = cmdr.tid;
            serverEnv.guiId = cmdr.tid + 1;
        }
        else {
            serverEnv.tid = 0;
            serverEnv.guiId = 0;
        }
    }
    catch (e) {
        serverEnv.tid = 0;
        serverEnv.guiId = 0;
    }

    if (serverEnv.tid != serverEnv.guiId) {
        serverEnv = logic.argsValidation(serverEnv);
        gui.setServerEnv(serverEnv);

        /* create an instance of IWorkbenchPart and send it */
        /* back to the server to call gui.createPartControl */
        var wbp = new Packages.org.eclipse.ui.IWorkbenchPart(gui);
        cmdr.socket.giveToClient(wbp);

        /* wait for gui to close */
        var val = cmdr.socket.takeFromClient();
    }
    else {
        if (serverEnv.gui) {
            serverEnv = logic.argsValidation(serverEnv);

            /* inst overrides logic defaults */
            if (inst.cgTools) {
                serverEnv.cgTools = inst.cgTools;
            }
            if (inst.destDir) {
                serverEnv.output = inst.destDir;
            }

            gui.setServerEnv(serverEnv);
            serverEnv = gui.main(serverEnv);

        }
        else if (serverEnv.xmlFile == "null") {
            print("\nCommand Line Version requires XML File! "
                + "See xs ti.sdo.ce.wizards.genserver --help for more information.");
            serverEnv.gui = true;
            serverEnv = logic.argsValidation(serverEnv);

            /* inst overrides logic defaults */
            if (inst.cgTools) {
                serverEnv.cgTools = inst.cgTools;
            }
            if (inst.destDir) {
                serverEnv.output = inst.destDir;
            }
            serverEnv = gui.main(serverEnv);
        }
        else {
            print("\nStarting Command Line Codec Engine GenServer Wizard now...");
            serverEnv = logic.argsValidation(serverEnv);

            /* inst overrides both xml and logic defaults */
            if (inst.cgTools) {
                serverEnv.cgTools = inst.cgTools;
            }
            if (inst.destDir) {
                serverEnv.output = inst.destDir;
            }
        }
    }
    if (!serverEnv.error && logic.createFiles(serverEnv) == 0) {
        var output = (serverEnv.output+"")
             + "/" + (serverEnv.serverName+"").replace(/\./g,"/");
        output = output.replace("//", "/");
        output = output.replace(/\\/g,"/");

        logic.gprint( "\nServer creation successful...\n"
            + "Files output to " + output
            + "\n\nDon't forget to edit codec.cfg and server.cfg "
            + "to assign and modify config parameters. See "
            + "ti/sdo/ce/wizards/genserver/readme.txt "
            + "file for syntax information.",
            serverEnv);
    }
    else {
        logic.gprint("\nServer creation unsuccessful.", serverEnv);
    }
}


/*
 *  @(#) ti.sdo.ce.wizards.genserver; 1, 0, 0,84; 12-2-2010 21:28:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

