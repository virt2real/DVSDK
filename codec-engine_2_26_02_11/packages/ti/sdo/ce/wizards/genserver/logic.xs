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

var xmlOps = xdc.loadCapsule("xmlOps.xs");
var shared_gui = xdc.loadCapsule("shared_gui.xs");
var wizard_constants = xdc.loadCapsule("wizard_constants.xs");
var mkpkg = xdc.module("xdc.tools.mkpkg.Main");
var csd = String(xdc.csd()).replace(/\\/g,"/");
var os = String(java.lang.System.getProperty('os.name'));
var isWin = (os.match(/^Windows/i) != null);

var memComment = [];
memComment['RESET_VECTOR'] =
    'RESET_VECTOR: off-chip memory for the reset vector table';
memComment['DSPLINKMEM'] =
    'DSPLINK: off-chip memory reserved for DSPLINK code and data';
memComment['DDRALGHEAP'] =
    'DDRALGHEAP: off-chip memory for dynamic algmem allocation';
memComment['DDR2'] =
    'DDR2: off-chip memory for application code and data';
memComment['SDRAM'] =
    'SDRAM: off-chip memory for application code and data';

/*
 *  Currently supported platforms/targets
 *
 *    ti.targets.C64P:
 *       ti.platforms.evm3530
 *       ti.platforms.evmDM6446
 *       ti.platforms.evmDM6467
 *
 *    ti.targets.C674:
 *       ti.platforms.evmOMAPL137
 *       ti.platforms.evmOMAPL138
 *
 */
function iresImpl(platform)
{
    /* all currently supported platforms support the following resource managers: */
    var iresImpl = ['addrspace', 'bufres', 'nullresource'];

    if (platform == 'ti.platforms.evmDM6467') {
        iresImpl = iresImpl.concat('hdvicp', 'vicp');
    }
    return (iresImpl);
}

function defaultMemConfig(platform)
{
    var memConfig = [];
    if (platform == 'ti.platforms.evm3530') {
        memConfig = [
            { sect : 'RESET_VECTOR', base : '0x87300000', len : '0x00000080'},
            { sect : 'DSPLINKMEM',   base : '0x87301000', len : '0x000FF000'},
            { sect : 'DDRALGHEAP',   base : '0x87400000', len : '0x00900000'},
            { sect : 'DDR2',         base : '0x87D00000', len : '0x00300000'}
        ];
    }
    else if (platform == 'ti.platforms.evmDM6446') {
        memConfig = [
            { sect : 'DDRALGHEAP',   base : '0x88000000', len : '0x07A00000'},
            { sect : 'DDR2',         base : '0x8FA00000', len : '0x00400000'},
            { sect : 'DSPLINKMEM',   base : '0x8FE00000', len : '0x00100000'},
            { sect : 'RESET_VECTOR', base : '0x8FF00000', len : '0x00000080'}
        ];
    }
    else if (platform == 'ti.platforms.evmDM6467') {
        memConfig = [
            { sect : 'DDRALGHEAP',   base : '0x88000000', len : '0x07A00000'},
            { sect : 'DDR2',         base : '0x8FA00000', len : '0x00400000'},
            { sect : 'DSPLINKMEM',   base : '0x8FE00000', len : '0x00100000'},
            { sect : 'RESET_VECTOR', base : '0x8FF00000', len : '0x00000080'}
        ];
    }
    else if (platform == 'ti.platforms.evmOMAPL137') {
        memConfig = [
            { sect : 'SDRAM',        base : '0xC2C00000', len : '0x00300000'},
            { sect : 'RESET_VECTOR', base : '0xC2F00000', len : '0x00000080'},
            { sect : 'DSPLINKMEM',   base : '0xC2F01000', len : '0x000FF000'},
            { sect : 'DDRALGHEAP',   base : '0xC3000000', len : '0x01000000'}

        ];
    }
    else if (platform == 'ti.platforms.evmOMAPL138') {
        memConfig = [
            { sect : 'DDR2',         base : '0xC2C00000', len : '0x00300000'},
            { sect : 'RESET_VECTOR', base : '0xC2F00000', len : '0x00000080'},
            { sect : 'DSPLINKMEM',   base : '0xC2F01000', len : '0x000FF000'},
            { sect : 'DDRALGHEAP',   base : '0xC3000000', len : '0x01000000'}

        ];
    }
    return (memConfig);
}

function defaultMem()
{
    var def = [];
    def['ti.platforms.evm3530'] = true;
    def['ti.platforms.evmDM6446'] = true;
    def['ti.platforms.evmDM6467'] = true;
    def['ti.platforms.evmOMAPL137'] = true;
    def['ti.platforms.evmOMAPL138'] = true;
    return (def);
}
function getMemSectionNames(platform)
{
    var memList = ['RESET_VECTOR', 'DSPLINKMEM', 'DDRALGHEAP'];
    if (platform == 'ti.platforms.evmOMAPL137') {
        memList.push('SDRAM');
    }
    else {
        memList.push('DDR2');
    }
    return (memList);
}

function argsValidation(serverEnv)
{

    var proot = csd + '/..';
    var pn = 'ti.sdo.ce.wizards.genserver';
    for (var i = 0; (i = pn.indexOf('.', i) + 1) > 0; ) {
        proot += '/..';
    }
    proot = String(java.io.File(proot).getCanonicalPath()).replace(/\\/g, '/');

    if (serverEnv.xmlFile != null && serverEnv.xmlFile != "null") {
        if (java.io.File(serverEnv.xmlFile).exists()) {
            try {
                serverEnv = xmlOps.loadXml(serverEnv.xmlFile, serverEnv);
            }
            catch(e) {
                gprint("Error: " + e, serverEnv);
                if (!serverEnv.gui) {
                    serverEnv.error = true;
                    return (serverEnv);
                }
            }
        }
        else {
            gprint("XML File, " + serverEnv.xmlFile + ", not found. "
                + "Wizard starting without loading XML File...",
                serverEnv);
            serverEnv.xmlFile = "null";
            if (!serverEnv.gui) {
                serverEnv.error = true;
                return (serverEnv);;
            }

        }
    }
    if (!serverEnv.platform) {
        serverEnv.platform = 'ti.platforms.evmDM6446';
    }
    if (!serverEnv.serverName) {
        serverEnv.serverName = 'mycompany.mygroup.servers.servercom';
    }

    if (serverEnv.output == null || serverEnv.output == 'null') {
        serverEnv.output = wizard_constants.ENTER_OUTREPO;
    }

    if (!serverEnv.memConfig || !serverEnv.memConfig[serverEnv.platform]) {
        if (!serverEnv.memConfig) {
            serverEnv.memConfig = [];
        }
        serverEnv.memConfig[serverEnv.platform] = defaultMemConfig(serverEnv.platform);
        if (!serverEnv.defaultMem) {
            serverEnv.defaultMem = [];
        }
        //serverEnv.defaultMem[serverEnv.platform] = true;
        serverEnv.defaultMem[serverEnv.platform] = false;
    }
    serverEnv.memComment = memComment;
    if (!serverEnv.memAlign || !serverEnv.memAlign[serverEnv.platform]) {
        if (!serverEnv.memAlign) {
            serverEnv.memAlign = [];
        }
        //serverEnv.memAlign[serverEnv.platform] = 'none';
        serverEnv.memAlign[serverEnv.platform] = 'bottom';
    }


    if (serverEnv.genCCSProj != true && serverEnv.genCCSProj != false) {
        serverEnv.genCCSProj = true;
    }

    serverEnv.inst.cmdr.info('Checking XDCPATH for product install directories');
    serverEnv.inst.cmdr.info('XDCPATH: ' + environment['xdc.path']);
    if (!serverEnv.ceInstall ||
        !java.io.File(serverEnv.ceInstall).exists()) {

        serverEnv.ceInstall = proot.replace(/\/packages$/, '');
    }

    if (java.io.File(serverEnv.ceInstall + '/cetools').exists()) {

        serverEnv.cetoolsInstall = serverEnv.ceInstall + '/cetools';
    }
    else {
        serverEnv.cetoolsInstall = '';
    }
    serverEnv.inst.cmdr.info('cetools install dir: ' + (serverEnv.cetoolsInstall ? serverEnv.cetoolsInstall : 'not found'));
    if (!serverEnv.xdaisInstall ||
        !java.io.File(serverEnv.xdaisInstall).exists()) {
        try {
            serverEnv.xdaisInstall = xdc.getPackageBase('ti.xdais.dm');
            serverEnv.xdaisInstall = serverEnv.xdaisInstall.replace(/\\/g, '/');
            serverEnv.xdaisInstall = serverEnv.xdaisInstall.replace(/\/+$/, '');
            serverEnv.xdaisInstall = serverEnv.xdaisInstall.replace(/\/packages\/ti\/xdais\/dm$/, '');
        }
        catch (e) {
            serverEnv.xdaisInstall = '';
        }
    }
    serverEnv.inst.cmdr.info('XDAIS install dir: ' + (serverEnv.xdaisInstall ? serverEnv.xdaisInstall : 'not found'));
    if (!serverEnv.fcInstall ||
        !java.io.File(serverEnv.fcInstall).exists()) {
        try {
            serverEnv.fcInstall = xdc.getPackageBase('ti.sdo.fc.dskt2');
            serverEnv.fcInstall = serverEnv.fcInstall.replace(/\\/g, '/');
            serverEnv.fcInstall = serverEnv.fcInstall.replace(/\/+$/, '');
            serverEnv.fcInstall = serverEnv.fcInstall.replace(/\/packages\/ti\/sdo\/fc\/dskt2$/, '');
        }
        catch (e) {
            serverEnv.fcInstall = '';
        }
    }
    serverEnv.inst.cmdr.info('Framework Components install dir: ' + (serverEnv.fcInstall ? serverEnv.fcInstall : 'not found'));
    if (!serverEnv.dsplinkInstall ||
        !java.io.File(serverEnv.dsplinkInstall).exists()) {
        try {
            serverEnv.dsplinkInstall = xdc.getPackageBase('dsplink.gpp');
            serverEnv.dsplinkInstall = serverEnv.dsplinkInstall.replace(/\\/g, '/');
            serverEnv.dsplinkInstall = serverEnv.dsplinkInstall.replace(/\/+$/, '');
            if (java.io.File(serverEnv.dsplinkInstall + '/packages').exists()) {
                serverEnv.dsplinkInstall = serverEnv.dsplinkInstall.replace(/\/packages\/dsplink\/gpp$/, '');
            }
            else {
                serverEnv.dsplinkInstall = serverEnv.dsplinkInstall.replace(/\/dsplink\/gpp$/, '');
            }
        }
        catch (e) {
            serverEnv.dsplinkInstall = '';
        }
    }
    serverEnv.inst.cmdr.info('Dsplink install dir: ' + (serverEnv.dsplinkInstall ? serverEnv.dsplinkInstall : 'not found'));
    if (!serverEnv.biosInstall ||
        !java.io.File(serverEnv.biosInstall).exists()) {
        try {
            serverEnv.biosInstall = xdc.getPackageBase('ti.bios.config.gconf');
            serverEnv.biosInstall = serverEnv.biosInstall.replace(/\\/g, '/');
            serverEnv.biosInstall = serverEnv.biosInstall.replace(/\/+$/, '');
            serverEnv.biosInstall = serverEnv.biosInstall.replace(/\/packages\/ti\/bios\/config\/gconf$/, '');
        }
        catch (e) {
            serverEnv.biosInstall = '';
        }
    }
    serverEnv.inst.cmdr.info('DSP/BIOS install dir: ' + (serverEnv.biosInstall ? serverEnv.biosInstall : 'not found'));
    if (!serverEnv.xdcInstall ||
        !java.io.File(serverEnv.xdcInstall).exists()) {
        try {
            serverEnv.xdcInstall = xdc.getPackageBase('xdc');
            serverEnv.xdcInstall = serverEnv.xdcInstall.replace(/\\/g, '/');
            serverEnv.xdcInstall = serverEnv.xdcInstall.replace(/\/+$/, '');
            serverEnv.xdcInstall = serverEnv.xdcInstall.replace(/\/packages\/xdc$/, '');
        }
        catch (e) {
            serverEnv.xdcInstall = '';
        }
    }
    serverEnv.inst.cmdr.info('XDC Tools install dir: ' + (serverEnv.xdcInstall ? serverEnv.xdcInstall : 'not found'));
    if (!serverEnv.cgTools) {
        var cgTools = serverEnv.xdcInstall + '/../ccsv4/tools/compiler/c6000';
        var validCgTools = validCgToolsDir(cgTools);
        if (!validCgTools && java.io.File(serverEnv.xdaisInstall).exists()) {
            cgTools = serverEnv.xdaisInstall + '/../ccsv4/tools/compiler/c6000';
            validCgTools = validCgToolsDir(cgTools);
        }
        if (validCgTools) {
            serverEnv.cgTools =
                String(java.io.File(cgTools).getCanonicalPath()).replace(/\\/g, '/');
        }
        else {
            serverEnv.cgTools = wizard_constants.ENTER_CGTOOLS
        }
    }

    if (!serverEnv.lpmInstall ||
        !java.io.File(serverEnv.lpmInstall).exists()) {
        try {
            serverEnv.lpmInstall = xdc.getPackageBase('ti.bios.power');
            serverEnv.lpmInstall = serverEnv.lpmInstall.replace(/\\/g, '/');
            serverEnv.lpmInstall = serverEnv.lpmInstall.replace(/\/+$/, '');
            serverEnv.lpmInstall = serverEnv.lpmInstall.replace(/\/packages\/ti\/bios\/power$/, '');
        }
        catch (e) {
            serverEnv.lpmInstall = '';
        }
    }
    serverEnv.inst.cmdr.info('Local Power Manager install dir: ' + (serverEnv.lpmInstall ? serverEnv.lpmInstall : 'not found'));
    if (!serverEnv.edmaLldInstall ||
        !java.io.File(serverEnv.edmaLldInstall).exists()) {
        try {
            serverEnv.edmaLldInstall = xdc.getPackageBase('ti.sdo.edma3.rm');
            serverEnv.edmaLldInstall = serverEnv.edmaLldInstall.replace(/\\/g, '/');
            serverEnv.edmaLldInstall = serverEnv.edmaLldInstall.replace(/\/+$/, '');
            serverEnv.edmaLldInstall = serverEnv.edmaLldInstall.replace(/\/packages\/ti\/sdo\/edma3\/rm$/, '');
        }
        catch (e) {
            serverEnv.edmaLldInstall = '';
        }
    }
    serverEnv.inst.cmdr.info('EDMALLD install dir: ' + (serverEnv.edmaLldInstall ? serverEnv.edmaLldInstall : 'not found'));
    if (!serverEnv.biosUtilsInstall ||
        !java.io.File(serverEnv.biosUtilsInstall).exists()) {
        try {
            serverEnv.biosUtilsInstall = xdc.getPackageBase('ti.bios.utils');
            serverEnv.biosUtilsInstall = serverEnv.biosUtilsInstall.replace(/\\/g, '/');
            serverEnv.biosUtilsInstall = serverEnv.biosUtilsInstall.replace(/\/+$/, '');
            serverEnv.biosUtilsInstall = serverEnv.biosUtilsInstall.replace(/\/packages\/ti\/bios\/utils$/, '');
        }
        catch (e) {
            serverEnv.biosUtilsInstall = '';
        }
    }
    serverEnv.inst.cmdr.info('BIOS Utils install dir: ' + (serverEnv.biosUtilsInstall ? serverEnv.biosUtilsInstall : 'not found'));
    return serverEnv;
}

function gprint(message, serverEnv) {
    if (serverEnv.gui == true) {
        shared_gui.createMessageBox(message, serverEnv);
    }
    else{
        print(message);
    }
}

function createFiles(serverEnv) {

    var status = 0;
    serverEnv = argsValidation(serverEnv);

    /* find configs within codecs */
    serverEnv = getConfigsFromModules(serverEnv);

    serverEnv.iresImpl = iresImpl(serverEnv.platform);

    var outputDir = "" + (serverEnv.output+"") + "/"
        + (serverEnv.serverName+"").replace(/\./g,"/");
    outputDir = outputDir.replace("//", "/");
    outputDir = outputDir.replace(/\\/g,"/");

    if ( java.io.File( outputDir ).exists() ) {
        var list = java.io.File( outputDir ).list();
        if (list.length!=0) {
            if (!serverEnv.gui ) {
                gprint("\nWarning: " + outputDir + " is not empty--files may be "
                    + "overwritten... Would you like to continue? y/n",
                    serverEnv);
                var isr = new java.io.InputStreamReader(
                    java.lang.System["in"] );
                var br = new java.io.BufferedReader( isr );

                try{
                    var output = br.readLine();
                }
                catch(e) {}

                if (output == "n") {
                    gprint("Quitting now...", serverEnv);
                    status = 1;
                }
                else if(output != "y") {
                    gprint("Invalid selection. Quitting now...", serverEnv);
                    status = 1;
                }
            }
        }
    }

    if (status == 0) {
        reviewPaths(serverEnv);

        /* function mkpkg(template_dir, output, args) */
        try {
            mkpkg.mkpkg("ti/sdo/ce/wizards/genserver/templates", outputDir,
                        serverEnv);

            if (serverEnv.genCCSProj) {
                mkpkg.mkpkg("ti/sdo/ce/wizards/genserver/templates/ccsv4", outputDir,
                            serverEnv);
            }
        }
        catch (e) {
            gprint("An error while creating package " +
                    serverEnv.serverName + ":\n" + e, serverEnv);
            status = 1;
        }
    }
    return(status);
}

function reviewPaths(serverEnv)
{

    /* check dsplink and for install dirs with no
      '/packages', and correct them */

    var i;
    var dir;
    for each (i = 0; i < serverEnv.searchPathArr.length; i++) {
        if (serverEnv.searchPathArr[i].match(/dsplink/i)) {
            dir = findDspLink([serverEnv.searchPathArr[i]]);
            if (dir) {
                if (java.io.File(dir + '/packages').exists()) {
                    dir += '/packages';
                }
                serverEnv.searchPathArr[i] = dir;
            }
            break;
        }
    }
    for each (i = 0; i < serverEnv.searchPathArr.length; i++) {
        dir = findBios([serverEnv.searchPathArr[i]]);
        if (dir) {
            serverEnv.searchPathArr[i] = dir + '/packages';
            break;
        }
    }
    for each (i = 0; i < serverEnv.searchPathArr.length; i++) {
        dir = findXdais([serverEnv.searchPathArr[i]]);
        if (dir) {
            serverEnv.searchPathArr[i] = dir + '/packages';
            break;
        }
    }
    for each (i = 0; i < serverEnv.searchPathArr.length; i++) {
        dir = findFC([serverEnv.searchPathArr[i]]);
        if (dir) {
            serverEnv.searchPathArr[i] = dir + '/packages';
            break;
        }
    }
    for each (i = 0; i < serverEnv.searchPathArr.length; i++) {
        dir = findLPM([serverEnv.searchPathArr[i]]);
        if (dir) {
            serverEnv.searchPathArr[i] = dir + '/packages';
            break;
        }
    }
    for each (i = 0; i < serverEnv.searchPathArr.length; i++) {
        dir = findEdmaLld([serverEnv.searchPathArr[i]]);
        if (dir) {
            serverEnv.searchPathArr[i] = dir + '/packages';
            break;
        }
    }
    for each (i = 0; i < serverEnv.searchPathArr.length; i++) {
        dir = findBiosUtils([serverEnv.searchPathArr[i]]);
        if (dir) {
            serverEnv.searchPathArr[i] = dir + '/packages';
            break;
        }
    }

    /* check for empty installs, populate them from serverEnv.searchPathArr */

    if (!serverEnv.biosInstall) {
        var dir = findBios(serverEnv.searchPathArr);
        if (dir) {
            serverEnv.biosInstall = dir;
        }
    }
    if (!serverEnv.dsplinkInstall) {
        var dir = findDspLink(serverEnv.searchPathArr);
        if (dir) {
            serverEnv.dsplinkInstall = dir;
        }
    }
    if (!serverEnv.xdaisInstall) {
        var dir = findXdais(serverEnv.searchPathArr);
        if (dir && !dir.match(/cetools/)) {
            serverEnv.xdaisInstall = dir;
        }
    }
    if (!serverEnv.fcInstall) {
        var dir = findFC(serverEnv.searchPathArr);
        if (dir && !dir.match(/cetools/)) {
            serverEnv.fcInstall = dir;
        }
    }
    if (!serverEnv.lpmInstall) {
        var dir = findLPM(serverEnv.searchPathArr);
        if (dir && !dir.match(/cetools/)) {
            serverEnv.lpmInstall = dir;
        }
    }
    if (!serverEnv.biosUtilsInstall) {
        var dir = findBiosUtils(serverEnv.searchPathArr);
        if (dir && !dir.match(/cetools/)) {
            serverEnv.biosUtilsInstall = dir;
        }
    }
    if (!serverEnv.edmaLldInstall) {
        var dir = findEdmaLld(serverEnv.searchPathArr);
        if (dir && !dir.match(/cetools/)) {
            serverEnv.edmaLldInstall = dir;
        }
    }
    if (!serverEnv.cetoolsInstall) {
        var dir = findXdais(serverEnv.searchPathArr);
        if (dir && dir.match(/cetools/)) {
            serverEnv.cetoolsInstall = dir;
        }
    }

    serverEnv.inst.cmdr.info('The XDCPATH for this server is: ' + serverEnv.searchPathArr.join(';'));
    serverEnv.inst.cmdr.info('cetools install dir: ' + (serverEnv.cetoolsInstall ? serverEnv.cetoolsInstall : 'not assigned'));
    serverEnv.inst.cmdr.info('XDAIS install dir: ' + (serverEnv.xdaisInstall ? serverEnv.xdaisInstall : 'not assigned'));
    serverEnv.inst.cmdr.info('Framework Components install dir: ' + (serverEnv.fcInstall ? serverEnv.fcInstall : 'not assigned'));
    serverEnv.inst.cmdr.info('Dsplink install dir: ' + (serverEnv.dsplinkInstall ? serverEnv.dsplinkInstall : 'not assigned'));
    serverEnv.inst.cmdr.info('DSP/BIOS install dir: ' + (serverEnv.biosInstall ? serverEnv.biosInstall : 'not assigned'));
    serverEnv.inst.cmdr.info('XDC Tools install dir: ' + (serverEnv.xdcInstall ? serverEnv.xdcInstall : 'not assigned'));
    serverEnv.inst.cmdr.info('Local Power Manager install dir: ' + (serverEnv.lpmInstall ? serverEnv.lpmInstall : 'not assigned'));
    serverEnv.inst.cmdr.info('EDMALLD install dir: ' + (serverEnv.edmaLldInstall ? serverEnv.edmaLldInstall : 'not assigned'));

    /* check for product installs in search path and remove them if found */
    /* this is all done to make the makefile look nice                    */
    var i = findFileInArr(serverEnv.searchPathArr,
                          java.io.File(serverEnv.ceInstall + '/packages'));
    if (i != -1) {
        serverEnv.searchPathArr.splice(i, 1);
    }
    var i = findFileInArr(serverEnv.searchPathArr,
                          java.io.File(serverEnv.xdcInstall + '/packages'));
    if (i != -1) {
        serverEnv.searchPathArr.splice(i, 1);
    }
    if (serverEnv.biosInstall) {
        var i = findFileInArr(serverEnv.searchPathArr,
                              java.io.File(serverEnv.biosInstall + '/packages'));
        if (i != -1) {
            serverEnv.searchPathArr.splice(i, 1);
        }
    }
    if (serverEnv.dsplinkInstall) {
        var linkRepo = serverEnv.dsplinkInstall;
        if (java.io.File(linkRepo + '/packages').exists()) {
            linkRepo += '/packages';
        }
        i = findFileInArr(serverEnv.searchPathArr, java.io.File(linkRepo));
        if (i != -1) {
            serverEnv.searchPathArr.splice(i, 1);
        }
    }
    if (serverEnv.fcInstall) {
        i = findFileInArr(serverEnv.searchPathArr,
                          java.io.File(serverEnv.fcInstall + '/packages'));
        if (i != -1) {
            serverEnv.searchPathArr.splice(i, 1);
        }
    }
    if (serverEnv.xdaisInstall) {
        i = findFileInArr(serverEnv.searchPathArr,
                          java.io.File(serverEnv.xdaisInstall + '/packages'));
        if (i != -1) {
            serverEnv.searchPathArr.splice(i, 1);
        }
    }

    if (serverEnv.lpmInstall) {
        i = findFileInArr(serverEnv.searchPathArr,
                          java.io.File(serverEnv.lpmInstall + '/packages'));
        if (i != -1) {
            serverEnv.searchPathArr.splice(i, 1);
        }
    }
    if (serverEnv.biosUtilsInstall) {
        i = findFileInArr(serverEnv.searchPathArr,
                          java.io.File(serverEnv.biosUtilsInstall + '/packages'));
        if (i != -1) {
            serverEnv.searchPathArr.splice(i, 1);
        }
    }
    if (serverEnv.edmaLldInstall) {
        i = findFileInArr(serverEnv.searchPathArr,
                          java.io.File(serverEnv.edmaLldInstall + '/packages'));
        if (i != -1) {
            serverEnv.searchPathArr.splice(i, 1);
        }
    }
    if (serverEnv.cetoolsInstall) {
        i = findFileInArr(serverEnv.searchPathArr,
                          java.io.File(serverEnv.cetoolsInstall + '/packages'));
        if (i != -1) {
            serverEnv.searchPathArr.splice(i, 1);
        }
    }
    for (var i = 0; i < serverEnv.searchPathArr.length; i++) {
            serverEnv.searchPathArr[i] =
                    serverEnv.searchPathArr[i].replace(/\\/g,'/');
    }
    if (serverEnv.cgTools) {
        serverEnv.cgTools = serverEnv.cgTools.replace(/\\/g,'/');
    }
    if (serverEnv.useRulesMake) {
        serverEnv.xdcInstall = '___Add_your_xdc_tools_install_dir_here___';
        serverEnv.cgTools = '___Add_your_cgtools_here___';
        serverEnv.xdaisInstall = '___Add_your__XDAIS_install_dir_here___';
        serverEnv.biosInstall = '___Add_your__DSP/BIOS_install_dir_here___';
        serverEnv.dsplinkInstall = '___Add_your__DSP_Link_install_dir_here___';
        serverEnv.fcInstall = '___Add_your__Framework_Components_install_dir_here___';
        serverEnv.lpmInstall = '___Add_your__Local_Power_Manager_install_dir_here___';
        serverEnv.biosUtilsInstall = '___Add_your__Bios_Utils_install_dir_here___';
        serverEnv.edmaLldInstall = '___Add_your__EDMA_LLD_install_dir_here___';
        serverEnv.cetoolsInstall = '___Add_your__CE_Tools_install_dir_here___';
    }
}

function findFileInArr(arr, file)
{
    var found = false;
    for (var i = 0; i < arr.length; i++) {
        if (file.equals(java.io.File(arr[i]))) {
            found = true;
            break;
        }
    }
    return (found ? i : -1);
}

/**
* Parses ICodec using xdc.services.spec
* @return Declaration nodes sorted by kind
*/
function getConfigsFromModules(serverEnv)
{
    var defSeg = (serverEnv.platform == 'ti.platforms.evmOMAPL137') ?
                 'SDRAM' : 'DDR2';
    var algSectInit = [];
    algSectInit['codeSection'] = 
    algSectInit['dataSection'] = 
    algSectInit['udataSection'] = defSeg;

    serverEnv.configs = [];
    serverEnv.cePackages = [];
    serverEnv.ceModules = [];
    serverEnv.idma3Fxns = null;
    serverEnv.iresFxns = null;
    serverEnv.algSectInit= [];

    try {
        /* create a BrowserSession with a private package path */
        var env = new Packages.xdc.services.global.Env();
        var bs = Packages.xdc.services.spec.BrowserSession(serverEnv.searchPathArr, env);
    }
    catch (e) {
        gprint("Error creating browser session\n" + e, serverEnv);
        configsObj = {};
        serverEnv.configs.push(configsObj);
        return (serverEnv);
    }

    for (var i = 0; i < serverEnv.cfgCodecs.length; i++) {
        try {
            var unit = bs.loadUnit(serverEnv.cfgCodecs[i]);
            if (unit == null) {
                gprint("Error loading module " + serverEnv.cfgCodecs[i],
                       serverEnv);
                continue;
            }
            var configsObj = {};
            var configNames = [];
            var configTypes = [];
            var configValues = [];
            var declList = unit.getDecls();

            /* loop through all decls and map to name */
            /* this will make sure that the final override  */
            /* of any dups will go in the map */
            var decls = {};
            var d;
            for (var j = 0; j < declList.size(); j++) {
                d = declList.get(j);
                decls[String(d.getName())] = d;
            }

            for each (var decl in decls) {
                var kind = String(decl.getXmlTag());
                var name = String(decl.getName());
                if (name == 'idma3Fxns') {
                    if (String(Packages.xdc.services.spec.Expr.toText(
                               decl.getInit())).length) {
                        if (!serverEnv.idma3Fxns) {
                            serverEnv.idma3Fxns = [];
                        }
                        serverEnv.idma3Fxns[serverEnv.cfgCodecs[i]] = true;
                    }
                }
                if (!serverEnv.iresFxns && name == 'iresFxns') {
                    if (String(Packages.xdc.services.spec.Expr.toText(
                               decl.getInit())).length) {
                        if (!serverEnv.iresFxns) {
                            serverEnv.iresFxns = [];
                        }
                        serverEnv.iresFxns[serverEnv.cfgCodecs[i]] = true;
                    }
                }
                var readonly = String(decl.isReadonly());
                if (kind == "config" && (readonly == "false" || name == "alg")) {
                    if (name == 'uuid' || name == 'isLocal' || name == 'useCache') {
                        continue;
                    }
                    var isAlg = name == "alg";
                    var configs = unit.getConfigs();
                    var bspec = _find(configs, serverEnv.cfgCodecs[i] + '.' +
                                      name);
                    if (!isAlg) {
                        configNames.push(name);
                    }
                    if (bspec != undefined) {
                        var typename =  String(_getTypeName(bspec)); // returns Bool, String
                        if (!isAlg) {
                            configTypes.push(typename);
                        }
                    }
                    else if (!isAlg) {
                        configTypes.push('');
                    }
                    if (isAlg) { /* get configs from alg module */
                        var algMod = typename.substr(0, typename.lastIndexOf(':Module'));
                        var algUnit = bs.loadUnit(algMod);
                        if (algUnit == null) {
                            gprint("Error loading module " + algUnit, serverEnv);
                        }
                        else {
                            var algDeclsList = algUnit.getDecls();
                            for (var k = 0; k < algDeclsList.size(); k++) {
                                var algDecl = algDeclsList.get(k);
                                kind = String(algDecl.getXmlTag());
                                readonly = String(algDecl.isReadonly());
                                if (kind == "config" && readonly == "false") {
                                    name = String(algDecl.getName());
                                    configs = unit.getConfigs();
                                    bspec = _find(configs, algMod + '.' + name);
                                    configNames.push('alg.' + name);
                                    if (bspec != undefined) {
                                        typename =  String(_getTypeName(bspec));
                                        configTypes.push(typename);
                                    }
                                    else {
                                        configTypes.push('');
                                    }
                                    var init = String(Packages.xdc.
                                            services.spec.Expr.
                                                toText(algDecl.getInit()));
                                    if ((name == 'codeSection' ||
                                          name == 'udataSection' ||
                                          name == 'dataSection') &&
                                          init.length == 0) {
                                          serverEnv.algSectInit[name] = algSectInit[name];
                                          init = name;
                                    }
                                    configValues.push(init);
                                }
                            }
                        }
                        serverEnv.cePackages.push(algMod.substr(0, algMod.lastIndexOf('.')));
                        serverEnv.ceModules.push(algMod.substr(algMod.lastIndexOf('.') + 1));
                    }
                    else {
                        configValues.push(String(Packages.xdc.services.spec.
                                          Expr.toText(decl.getInit())));
                    }
                }
            }
            configsObj.configNames = configNames;
            configsObj.configTypes = configTypes;
            configsObj.configValues = configValues;
        }
        catch(e) {
            gprint("Error finding config params from module: " +
                   serverEnv.cfgCodecs[i] + "\n" + e, serverEnv);

            configsObj = {};
        }

        serverEnv.configs.push(configsObj);
    }
    return serverEnv;
}

function _getTypeName(spec) {
    var type = spec.getType().xmlsig();
    var n = type;
        if (type != null) {
            if (type.startsWith("T!") || type.startsWith("K!")) {
                var s1 = type.split("!");
                n = s1[1];
            }
        }
    return(n);
}



/**
 * Return the named element from the list.
 *
 * @param list List of Node-derived objects
 * @param name of object to retrieve
 * @return Node named object if found, null if not
 */

function _find(list, name) {
    var o = null;
    var it = list.iterator();
    while (it.hasNext()) {
        var n = it.next();
        if (n.getName().compareTo(name) == 0) {
            o = n;
            break;
        } else if (n.getQualName().compareTo(name.replace('\/', '.')) == 0) {
            o = n;
            break;
        }
    }
    return (o);
}

function defaultGroup(serverEnv, groupId)
{
    serverEnv.groups[groupId] = {};
    serverEnv.groups[groupId].dskt2 = {};
    serverEnv.groups[groupId].edma3 = {};
    serverEnv.groups[groupId].dman3 = {};
    platformSpecificDefault(serverEnv.groups[groupId], groupId)

    if (groupId == wizard_constants.VIDEO_GROUPID) {

        serverEnv.groups[groupId].dskt2.saram = '0x8000';

        serverEnv.groups[groupId].edma3.maxPaRams = '384';
        serverEnv.groups[groupId].edma3.maxTccs = '26';
        serverEnv.groups[groupId].edma3.maxEdmaChannels = '24';

        /* Gunjan: For only idma3 based codecs, the maxQdmaChannels[] */
        /* should have zero entries for all the groups        */
        if (serverEnv.idma3Fxns != null && serverEnv.iresFxns == null) {
            serverEnv.groups[groupId].edma3.maxQdmaChannels = '0';
        }
        else {
            serverEnv.groups[groupId].edma3.maxQdmaChannels = '4';
        }

        serverEnv.groups[groupId].dman3.numPaRam = '48';
    }
    else {
        if (groupId == wizard_constants.IMAGING_GROUPID) {
            serverEnv.groups[groupId].dskt2.saram = '0x2000';
        }
        else {
            serverEnv.groups[groupId].dskt2.saram = '0x0000';
        }

        serverEnv.groups[groupId].edma3.maxPaRams = '0';
        serverEnv.groups[groupId].edma3.maxTccs = '0';
        serverEnv.groups[groupId].edma3.maxEdmaChannels = '0';
        serverEnv.groups[groupId].edma3.maxQdmaChannels = '0';

        serverEnv.groups[groupId].dman3.numPaRam = '0';
    }
}


function platformSpecificDefault(obj, groupId)
{
    var daram = [];
    var numTccGroup = [];
    if (groupId == wizard_constants.VIDEO_GROUPID) {
        daram['ti.platforms.evm3530'] = '0x10000';
        daram['ti.platforms.evmDM6446'] = '0x8000';
        daram['ti.platforms.evmDM6467'] = '0x8000';
        daram['ti.platforms.evmOMAPL137'] = '0x8000';
        daram['ti.platforms.evmOMAPL138'] = '0x8000';

        numTccGroup['ti.platforms.evm3530'] = '32';
        numTccGroup['ti.platforms.evmDM6446'] = '32';
        numTccGroup['ti.platforms.evmDM6467'] = '32';
        numTccGroup['ti.platforms.evmOMAPL137'] = '16';
        numTccGroup['ti.platforms.evmOMAPL138'] = '16';
    }
     else {
        if (groupId == wizard_constants.IMAGING_GROUPID) {
            daram['ti.platforms.evm3530'] = '0x2000';
            daram['ti.platforms.evmDM6446'] = '0x2000';
            daram['ti.platforms.evmDM6467'] = '0x2000';
            daram['ti.platforms.evmOMAPL137'] = '0x2000';
            daram['ti.platforms.evmOMAPL138'] = '0x2000';
        }
        else {
            daram['ti.platforms.evm3530'] = '0x0000';
            daram['ti.platforms.evmDM6446'] = '0x0000';
            daram['ti.platforms.evmDM6467'] = '0x0000';
            daram['ti.platforms.evmOMAPL137'] = '0x0000'
            daram['ti.platforms.evmOMAPL138'] = '0x0000'
        }
        numTccGroup['ti.platforms.evm3530'] = '0';
        numTccGroup['ti.platforms.evmDM6446'] = '0';
        numTccGroup['ti.platforms.evmDM6467'] = '0';
        numTccGroup['ti.platforms.evmOMAPL137'] = '0';
        numTccGroup['ti.platforms.evmOMAPL138'] = '0';
    }
    obj.dskt2.daram = daram;
    obj.dman3.numTccGroup = numTccGroup;
}


/*
 *  ======== getPackageBase ========
 */
function getPackageBase(pname, path)
{
    var fname = String(pname).replace(/\./g, '/');
    var psf = "/package.xdc";

    var base = utils.findFile(fname + psf, path, ';');
    if (base != null) {
        var apath = String(java.io.File(base).getCanonicalPath());
        var len = psf.length - 1;
        apath = apath.substring(0, apath.length - len).replace(/\\/g, '/');
        return (apath);
    }
    return (null);
};

/*
 *  ======== findDspLink ========
 */
function findDspLink(pathArr)
{
    var linkDir = null;
    for each (var dir in pathArr) {
        if (dir.length != 0) {
            if (dir.match(/dsplink/i)) {
                var chkDir = java.io.File(dir);
                if (chkDir.exists()) {
                    linkDir = String(chkDir.getCanonicalPath());
                    linkDir = linkDir.replace(/\\/g, '/');
                    break;
                }
            }
        }
    }
    if (linkDir) {
        var hasPackages = linkDir.match(/\/packages$/);
        var base = getPackageBase('dsplink.gpp', linkDir)
        if (!base) {
            if (hasPackages) {
                linkDir = linkDir.replace(/\/packages$/, '');
                hasPackages = false;
            }
            else {
                linkDir += '/packages';
                hasPackages = true;
            }
            base = getPackageBase('dsplink.gpp', linkDir);
        }
        if (base) {
            base = base.replace(/\\/g, '/');
            base = base.replace(/\/+$/, '');
            if (hasPackages) {
                base = base.replace(/\/packages\/dsplink\/gpp$/, '');
            }
            else {
                base = base.replace(/\/dsplink\/gpp$/, '');
            }
        }
        linkDir = base;
    }
    return (linkDir);
}

/*
 *  ======== findBios ========
 */
function findBios(pathArr)
{
    var base = findPackageInPath('ti.bios.config.gconf', pathArr)
    if (base) {
        base = base.replace(/\/packages\/ti\/bios\/config\/gconf$/, '');
    }
    return (base);
}

/*
 *  ======== findLPM ========
 */
function findLPM(pathArr)
{
    var base = findPackageInPath('ti.bios.power', pathArr)
    if (base) {
        base = base.replace(/\/packages\/ti\/bios\/power$/, '');
    }
    return (base);
}

/*
 *  ======== findXdais ========
 */
function findXdais(pathArr)
{
    var base = findPackageInPath('ti.xdais.dm', pathArr)
    if (base) {
        base = base.replace(/\/packages\/ti\/xdais\/dm$/, '');
    }
    return (base);
}

/*
 *  ======== findFC ========
 */
function findFC(pathArr)
{
    var base = findPackageInPath('ti.sdo.fc.dskt2', pathArr)
    if (base) {
        base = base.replace(/\/packages\/ti\/sdo\/fc\/dskt2$/, '');
    }
    return (base);
}

/*
 *  ======== findBiosUtils ========
 */
function findBiosUtils(pathArr)
{
    var base = findPackageInPath('ti.bios.utils', pathArr)
    if (base) {
        base = base.replace(/\/packages\/ti\/bios\/utils$/, '');
    }
    return (base);
}

/*
 *  ======== findEdmaLld ========
 */
function findEdmaLld(pathArr)
{
    var base = findPackageInPath('ti.sdo.edma3.rm', pathArr)
    if (base) {
        base = base.replace(/\/packages\/ti\/sdo\/edma3\/rm$/, '');
    }
    return (base);
}

/*
 *  ======== checkForCeAndXdc ========
 */
function checkForCeAndXdc(searchPathArr)
{
    /* test path for ce, xdais, fc and xdc, if not found, add their repos */
    var pathStr = searchPathArr.join(';');
    if (!getPackageBase('ti.sdo.ce', pathStr)) {
        searchPathArr.push(serverEnv.ceInstall + '/packages');
    }
    if (!getPackageBase('xdc', pathStr)) {
        searchPathArr.push(serverEnv.xdcInstall + '/packages');
    }
}

function validCgToolsDir(dir)
{
    if (!String(dir).length) {
        return (false);
    }
    var valid = true;
    var clFile = 'cl6x';
    if (isWin) {
        clFile += '.exe';
    }
    if (!java.io.File(dir + '/bin/' + clFile).exists()) {
        valid = false;
    }
    return (valid);
}

function compatibleWizardVersion(versStr)
{
    var vers = Number(versStr.replace(/\./g, ''));
    var curVers = Number(wizard_constants.wizardVersion.replace(/\./g, ''));
    return (vers >= curVers);
}

function groupConfiguresDman3(serverEnv, groupId)
{
    return (serverEnv.groups[groupId].implsIdma3Fxns &&
            serverEnv.iresFxns == null && serverEnv.useDMAN3);
}

function groupConfiguresEdma3(serverEnv, groupId)
{
    return ((serverEnv.groups[groupId].implsIresFxns ||

            (serverEnv.groups[groupId].implsIdma3Fxns &&
            serverEnv.iresFxns != null) ||

            (serverEnv.groups[groupId].implsIdma3Fxns &&
            serverEnv.iresFxns == null && !serverEnv.useDMAN3)) &&

            serverEnv.platformSupportsEdma);
}

function groupImplementsIdma3Fxns(groupId)
{
    if (serverEnv.idma3Fxns != null) {
        for (var i = 0; i < serverEnv.cfgCodecs.length; i++) {
            var qn = serverEnv.cfgCodecs[i];
            if (serverEnv.algVals[qn].groupId == groupId &&
                serverEnv.idma3Fxns[qn]) {

                return (true);
            }
        }
    }
    return (false);
}

function groupImplementsIresFxns(groupId)
{
    if (serverEnv.iresFxns != null) {
        for (var i = 0; i < serverEnv.cfgCodecs.length; i++) {
            var qn = serverEnv.cfgCodecs[i];
            if (serverEnv.algVals[qn].groupId == groupId &&
                serverEnv.iresFxns[qn]) {

                return (true);
            }
        }
    }
    return (false);
}

function isHexNumber(str)
{
    return (str.match(/^0x[a-f0-9]+$/i) ? true : false);
}

function platformSupportsPwrManagment(platform)
{
    return (platform == 'ti.platforms.evm3530' ||
            platform == 'ti.platforms.evmDM6446');
}

/*
 *  ======== findPackageInPath ========
 */
function findPackageInPath(pkgName, pathArr)
{
    var base = null;
    for each (var dir in pathArr) {
        if (dir.length != 0) {
            var chkDir = java.io.File(dir);
            if (chkDir.exists()) {
                dir = String(chkDir.getCanonicalPath());
                dir = dir.replace(/\\/g, '/');
                dir = dir.replace(/\/+$/, '');
                base = getPackageBase(pkgName, dir)
                if (!base) {
                    if (!dir.match(/\/packages$/)) {
                        dir += '/packages';
                        base = getPackageBase(pkgName, dir);
                    }   
                }
                if (base) {
                    base = base.replace(/\\/g, '/');
                    base = base.replace(/\/+$/, '');
                    break;
                }
            }
        }
    }
    return (base);
}

/*
 *  ======== checkForRequiredInstallDirs ========
 */
function checkForRequiredInstallDirs(serverEnv, pathArr)
{
    var notFoundArr = [];
    var found = (serverEnv.xdaisInstall || serverEnv.cetoolsInstall) ? true :
                findXdais(pathArr);
    if (!found) {
        notFoundArr.push('XDAIS or cetools');
    }
    found = (serverEnv.fcInstall || serverEnv.cetoolsInstall) ? true :
            findFC(pathArr);
    if (!found) {
        notFoundArr.push('Framework Components or cetools');
    }
    found = serverEnv.dsplinkInstall ? true : findDspLink(pathArr);
    if (!found) {
        notFoundArr.push('DSP Link ');
    }
    found = serverEnv.biosInstall ? true : findBios(pathArr);
    if (!found) {
        notFoundArr.push('DSP/BIOS 5.x');
    }
    found = (serverEnv.biosUtilsInstall || serverEnv.cetoolsInstall) ? true :
            findBiosUtils(pathArr);
    if (!found) {
        notFoundArr.push('BIOSUTILS or cetools');
    }
    if (serverEnv.enablePwr) {
        found = (serverEnv.lpmInstall || serverEnv.cetoolsInstall) ? true :
                findLPM(pathArr);
        if (!found) {
            notFoundArr.push('Local Power Manager or cetools');
        }
    }
    return (notFoundArr);
}
/*
 *  @(#) ti.sdo.ce.wizards.genserver; 1, 0, 0,84; 12-2-2010 21:28:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

