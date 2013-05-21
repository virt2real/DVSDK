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

var csd = String(xdc.csd()).replace(/\\/g,"/");
var fileModule = xdc.module('xdc.services.io.File');
var logic;
var wizard_constants;
var shared_gui;
var GROUPID_MAX = 19;  // dup

function setLogic(log)
{
    logic = log;
}

function setWizard_constants(wc)
{
    wizard_constants = wc;
}

function setShared_gui(sg)
{
    shared_gui = sg;
}

/**
 * Logic to save userInput to an XML file
 * @param userInput
 * @return text to be saved to XML file
/*
 *  ======== saveXml ========
 */
function saveXml(serverEnv)
{ 
    serverEnv = logic.argsValidation(serverEnv);
    try {
        var doc = <codec_engine_genserver_wizard/>;

        doc.version = serverEnv.wizardVersion;
        doc.serverName = serverEnv.serverName;
        doc.outputRepository = serverEnv.output;
        doc.platform = serverEnv.platform;
        doc.cgTools = serverEnv.cgTools;
        doc.xdaisInstall = serverEnv.xdaisInstall;
        doc.fcInstall = serverEnv.fcInstall;
        doc.biosInstall = serverEnv.biosInstall;
        doc.dsplinkInstall = serverEnv.dsplinkInstall;
        doc.cetoolsInstall = serverEnv.cetoolsInstall;
        doc.biosUtilsInstall = serverEnv.biosUtilsInstall;
        doc.edmaLldInstall = serverEnv.edmaLldInstall;
        doc.lpmInstall = serverEnv.lpmInstall;
        doc.genCCSProj = serverEnv.genCCSProj;
        doc.useRulesMake = serverEnv.useRulesMake == true ? 'true' : 'false';
        doc.useDMAN3 = serverEnv.useDMAN3 == true ? 'true' : 'false';
        doc.platformSupportsEdma = serverEnv.platformSupportsEdma == true ? 'true' : 'false';
        doc.configuresEdma3 = serverEnv.configuresEdma3 == true ? 'true' : 'false';
        doc.enablePwr = serverEnv.enablePwr == true ? 'true' : 'false';

        var searchPath = <codecSearchPath/>;
        for (var i = 0 ; i < serverEnv.searchPathArr.length; i++) {
            var repo = <repo>{serverEnv.searchPathArr[i]}</repo>;
            searchPath.appendChild(repo);
        }
        doc.appendChild(searchPath);

        var codecs = <codecs/>;

        for (var i = 0; i < serverEnv.cfgCodecs.length; i++) {
            var mod = <module/>;
            var qn = serverEnv.cfgCodecs[i];
            mod.@name = qn;
            if (serverEnv.reposMap[qn]) {
                var repo = <repo>{serverEnv.reposMap[qn]}</repo>;
                mod.appendChild(repo);
            }
            if (serverEnv.inheritsMap[qn]) {
                var inhers = <inherits/>;
                for each (var inname in serverEnv.inheritsMap[qn]) {
                    var iname = <name>{inname}</name>;
                    inhers.appendChild(iname);
                }
                mod.appendChild(inhers);
            }

            var algVals = serverEnv.algVals[qn];
            var alg = <alg/>;
            alg.name = algVals.name;
            alg.pri = algVals.pri;
            alg.stackMemId = algVals.stackMemId;
            alg.stackSize = algVals.stackSize;
            alg.groupId = algVals.groupId;
            alg.useDefaults = algVals.useDefaults;
            mod.appendChild(alg);

            codecs.appendChild(mod);
        }

        doc.appendChild(codecs);

        var groups = <groups/>;
        for (var i = 0; i < serverEnv.groups.length; i++) {
            if (serverEnv.groups[i]) {
                var group = <group/>;
                group.@id = i;
                group.@implsIdma3Fxns =
                    (serverEnv.groups[i].implsIdma3Fxns == true ) ?
                    'true' : 'false';
                group.@implsIresFxns =
                    (serverEnv.groups[i].implsIresFxns == true ) ?
                    'true' : 'false';
                group.@cfgDman3 =
                    (serverEnv.groups[i].cfgDman3 == true ) ?
                    'true' : 'false';
                group.@cfgEdma3 =
                    (serverEnv.groups[i].cfgEdma3 == true ) ?
                    'true' : 'false';
                var dskt2 = <dskt2/>
                dskt2.saram = serverEnv.groups[i].dskt2.saram;
                dskt2.daram = serverEnv.groups[i].dskt2.daram[serverEnv.platform];
                group.appendChild(dskt2);
                if (serverEnv.groups[i].cfgDman3) {
                    var dman3 = <dman3/>
                    dman3.numPaRam = serverEnv.groups[i].dman3.numPaRam;
                    dman3.numTccGroup = serverEnv.groups[i].dman3.numTccGroup[serverEnv.platform];
                    group.appendChild(dman3);
                }
                else if (serverEnv.groups[i].cfgEdma3) {
                    var edma3 = <edma3/>
                    edma3.maxPaRams = serverEnv.groups[i].edma3.maxPaRams;
                    edma3.maxTccs = serverEnv.groups[i].edma3.maxTccs;
                    edma3.maxEdmaChannels = serverEnv.groups[i].edma3.maxEdmaChannels;
                    edma3.maxQdmaChannels = serverEnv.groups[i].edma3.maxQdmaChannels;
                    group.appendChild(edma3);
                }
                groups.appendChild(group);
            }
        }
        doc.appendChild(groups);

        var mem = <memory/>;
        for (var i = 0; i < serverEnv.memConfig[serverEnv.platform].length; i++) {
            var section = <section/>            
            section.name = serverEnv.memConfig[serverEnv.platform][i].sect;
            section.base = serverEnv.memConfig[serverEnv.platform][i].base;
            section.length = serverEnv.memConfig[serverEnv.platform][i].len;
            mem.appendChild(section);
        }
        mem.align = serverEnv.memAlign[serverEnv.platform];
        mem.useDefault = serverEnv.defaultMem[serverEnv.platform];
        doc.appendChild(mem);

        var version = "<?xml version=\"1.0\"?>";
        return(version + doc.toXMLString());
    }
    catch (e) {
        print('exception ' + e.message);
        return ('');
    }
}



/**
 * Writes text to a file
 * @param {String} Output file location
 * @param {String} Text to be written to file 
 * @return {Integer} 0 for completion, 1 for error
 */
function textFileWriter( outputFileLocation, fileText ) {
    var file = fileModule.open(outputFileLocation, "w");
    var completed = file.writeLine(fileText.toString());
    file.close();
    if (completed == false) { 
        return 1;
    }
    return 0;
}

function textFileReader( inputFileLocation ) {
    var text = "";
    var file = fileModule.open(inputFileLocation, "r");
    var line;
    while ((line = file.readLine()) != null) {
          text += line + "\n";
    }
    file.close();    
    return text;
}

/**
* Logic to update userInput based on XML file
* @param XML file containing userInput data
* @return updated userInput based on XML file
*/ 
function loadXml(file, serverEnv)
{
    var readXml = textFileReader(file);
    var doc = new XML(readXml);         

    serverEnv.wizardVersion = String(doc.version);
    var vers_2_26_OK = doc.useDMAN3.length() > 0;
    if (!vers_2_26_OK && serverEnv.gui) {
        var msg = file + '\nwas created with Genserver Wizard version ' +
                  serverEnv.wizardVersion;
        
        if (!serverEnv.gui) {
            msg += '. Please review the generated server.cfg file for compatibility.';
        }
        else {
            msg += '. Previous group settings may not be available.';
            shared_gui.createMessageBox(msg, serverEnv);
        }
    }
    serverEnv.serverName = String(doc.serverName);
    serverEnv.output = String(doc.outputRepository);
    serverEnv.platform = String(doc.platform);
    serverEnv.cgTools = String(doc.cgTools);
    serverEnv.xdaisInstall = String(doc.xdaisInstall);
    serverEnv.fcInstall = String(doc.fcInstall);
    serverEnv.biosInstall = String(doc.biosInstall);
    serverEnv.dsplinkInstall = String(doc.dsplinkInstall);
    serverEnv.cetoolsInstall = String(doc.cetoolsInstall);
    serverEnv.biosUtilsInstall = String(doc.biosUtilsInstall);
    serverEnv.edmaLldInstall = String(doc.edmaLldInstall);
    serverEnv.lpmInstall = String(doc.lpmInstall);
    serverEnv.genCCSProj = (doc.genCCSProj == 'true') ? true : false;
    serverEnv.enablePwr = (doc.enablePwr == 'true') ? true : false;
    serverEnv.useRulesMake = doc.useRulesMake == 'true' ? true : false;
    
    if (doc.outputRepository!= "" && 
        doc.outputRepository!= "null") {
        var path = relativePathCheck(doc.outputRepository);
        if (path != "") {
            serverEnv.output = String(path);
        }
    }

    serverEnv.searchPathArr = [];
    for (var i = 0 ; i < doc.codecSearchPath.repo.length(); i++) {
        var path = relativePathCheck(doc.codecSearchPath.repo[i]);
        if (path != "") {
            serverEnv.searchPathArr.push(String(path));
        }
    }

    serverEnv.allCodecs = [];
    serverEnv.cfgCodecs = [];
    serverEnv.inheritsMap = [];
    serverEnv.reposMap = [];
    serverEnv.algVals = [];
    for (var i = 0; i < doc.codecs.module.length(); i++) {
        var qn = String(doc.codecs.module[i].@name);
        serverEnv.allCodecs.push(qn);
        serverEnv.cfgCodecs.push(qn);
        if (doc.codecs.module[i].repo.length()) {
            serverEnv.reposMap[qn] = String(doc.codecs.module[i].repo);
        }
        serverEnv.inheritsMap[qn] = [];
        for (var j = 0; j < doc.codecs.module[i].inherits.name.length(); j++) {
            serverEnv.inheritsMap[qn].push(String(doc.codecs.module[i].inherits.name[j]));
        }
        serverEnv.algVals[qn] = {};
        serverEnv.algVals[qn].name = String(doc.codecs.module[i].alg.name);
        serverEnv.algVals[qn].pri = Number(doc.codecs.module[i].alg.pri);
        serverEnv.algVals[qn].stackMemId = String(doc.codecs.module[i].alg.stackMemId);
        serverEnv.algVals[qn].stackSize = String(doc.codecs.module[i].alg.stackSize);
        serverEnv.algVals[qn].groupId = Number(doc.codecs.module[i].alg.groupId);
        serverEnv.algVals[qn].useDefaults = doc.codecs.module[i].alg.useDefaults == 'true' ? true : false;
    }

    /* backward compatibility */
    if (!vers_2_26_OK) {
        serverEnv = logic.getConfigsFromModules(serverEnv);

        if (serverEnv.gui) {
            /* previously, only non-6467 implemented dman3. Restore exact */
            /* settings only if override rules are met                */
            serverEnv.useDMAN3 = (serverEnv.platform != 'ti.platforms.evmDM6467' && 
                                  serverEnv.idma3Fxns != null &&
                                  serverEnv.iresFxns == null);
        }
        else {  /* for cmd line, generate the server as close to previous as possible */
            serverEnv.useDMAN3 = (serverEnv.platform != 'ti.platforms.evmDM6467' &&
                                  serverEnv.idma3Fxns != null);
        }

        serverEnv.platformSupportsEdma = true;  // make call to Gunjan's function
        serverEnv.configuresEdma3 = false;
    }
    else {
        serverEnv.useDMAN3 = doc.useDMAN3 == 'true' ? true : false;
        serverEnv.platformSupportsEdma = doc.platformSupportsEdma == 'true' ? true : false;
        serverEnv.configuresEdma3 = doc.configuresEdma3 == 'true' ? true : false;
    }

    serverEnv.groups = new Array(GROUPID_MAX + 1);
    for (var i = 0; i < doc.groups.group.length(); i++) {
        var groupId = Number(doc.groups.group[i].@id);
        logic.defaultGroup(serverEnv, groupId);
        if (vers_2_26_OK) {
            serverEnv.groups[groupId].implsIdma3Fxns = (doc.groups.group[i].@implsIdma3Fxns == 'true') ? true : false;
            serverEnv.groups[groupId].implsIresFxns = (doc.groups.group[i].@implsIresFxns == 'true') ? true : false;
            serverEnv.groups[groupId].cfgDman3 = (doc.groups.group[i].@cfgDman3 == 'true') ? true : false;
            serverEnv.groups[groupId].cfgEdma3 = (doc.groups.group[i].@cfgEdma3 == 'true') ? true : false;
        }
        else {
            serverEnv.groups[groupId].implsIdma3Fxns = logic.groupImplementsIdma3Fxns(groupId);
            serverEnv.groups[groupId].implsIresFxns = logic.groupImplementsIresFxns(groupId);

            if (serverEnv.gui) {
                serverEnv.groups[groupId].cfgDman3 = logic.groupConfiguresDman3(serverEnv, groupId);
                serverEnv.groups[groupId].cfgEdma3 = logic.groupConfiguresEdma3(serverEnv, groupId);
            }
            else {  /* for cmd line, generate the server as close to previous as possible */
                serverEnv.groups[groupId].cfgDman3 = serverEnv.useDMAN3;
                serverEnv.groups[groupId].cfgEdma3 = serverEnv.platform == 'ti.platforms.evmDM6467';
            }
            if (serverEnv.groups[groupId].cfgEdma3 && !serverEnv.configuresEdma3) {
                serverEnv.configuresEdma3 = true;
            }
        }

        var saram = String(doc.groups.group[i].dskt2.saram);
        var daram = String(doc.groups.group[i].dskt2.daram);
        if (!logic.isHexNumber(saram)) {
            saram = '0x' + Number(saram).toString(16).toUpperCase();
        }
        if (!logic.isHexNumber(daram)) {
            daram = '0x' + Number(daram).toString(16).toUpperCase();
        }
        serverEnv.groups[groupId].dskt2.saram = saram;
        serverEnv.groups[groupId].dskt2.daram[serverEnv.platform] = daram;
        if (serverEnv.groups[groupId].cfgDman3) {
            serverEnv.groups[groupId].dman3.numPaRam = String(doc.groups.group[i].dman3.numPaRam);
            serverEnv.groups[groupId].dman3.numTccGroup[serverEnv.platform] =
                    String(doc.groups.group[i].dman3.numTccGroup);
        }
        else if (serverEnv.groups[groupId].cfgEdma3) {
            serverEnv.groups[groupId].edma3.maxPaRams = String(doc.groups.group[i].edma3.maxPaRams);
            serverEnv.groups[groupId].edma3.maxTccs = String(doc.groups.group[i].edma3.maxTccs);
            serverEnv.groups[groupId].edma3.maxEdmaChannels = String(doc.groups.group[i].edma3.maxEdmaChannels);
            serverEnv.groups[groupId].edma3.maxQdmaChannels = String(doc.groups.group[i].edma3.maxQdmaChannels);
        }
    }

    serverEnv.memConfig = [];
    serverEnv.memConfig[serverEnv.platform] = new Array(doc.memory.section.length());
    for (var i = 0; i < doc.memory.section.length(); i++) {
        serverEnv.memConfig[serverEnv.platform][i] = {};
        serverEnv.memConfig[serverEnv.platform][i].sect = String(doc.memory.section[i].name);
        serverEnv.memConfig[serverEnv.platform][i].base = String(doc.memory.section[i].base);
        serverEnv.memConfig[serverEnv.platform][i].len = String(doc.memory.section[i].length);
    }
    serverEnv.memAlign = [];
    serverEnv.memAlign[serverEnv.platform] = String(doc.memory.align);
    serverEnv.defaultMem = [];
    serverEnv.defaultMem[serverEnv.platform] = (doc.memory.useDefault == 'true') ? true : false;


/*
    for (var i = 0; i < cfgCodecs.length; i++) {
        print('module ' + serverEnv.cfgCodecs[i]);
        print('alg:');
        print('  name ' + serverEnv.algVals[qn].name);
        print('  pri ' + serverEnv.algVals[qn].pri);
        print('  stackMemId ' + serverEnv.algVals[qn].stackMemId);
        print('  stackSize ' + serverEnv.algVals[qn].stackSize);
        print('  groupId ' + serverEnv.algVals[qn].groupId);
        print('  useDefaults ' + serverEnv.algVals[qn].useDefaults);
    }
*/
    return serverEnv;
}

/**
* A relative path in a saved XML file (used in the examples dir) must be 
* evaluated 
* @param {String} Exact string from XML file 
* @return {String} Canonical Path of Input 
*/            
function relativePathCheck(path)
{ 
    path = String(path);
    if (path.length) {
        if (!java.io.File(path).isAbsolute()) {
            var canonicalPath = csd + path.substring(1, path.length);
        }
        else {
            var canonicalPath = path;
        }
        canonicalPath = String(java.io.File(canonicalPath).getCanonicalPath());
        return (canonicalPath.replace(/\\/g,"/"));
    } 
    return ("");
}

/*
 *  @(#) ti.sdo.ce.wizards.genserver; 1, 0, 0,84; 12-2-2010 21:28:48; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

