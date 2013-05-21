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
 * */

var os = String(java.lang.System.getProperty('os.name'));
var isWin = (os.match(/^Windows/i) != null);

var targetList = ['ti.targets.C64P', 'ti.targets.C674'];

function getMVI(libFile, codecPkgEnv)
{
    var mvi = { module : null,
                inface : null,
                vendor : null
              };
    var cmd = [];
    
    var cmdStr = checkCommand(codecPkgEnv.xdaisInstall + '/packages/ti/xdais/qualiti/cgtools/bin/nm6x');
    cmd.push(cmdStr);
    cmd.push('-g');
    cmd.push(libFile);

    // execute the command line
    var attrs = {};
    attrs.cwd = codecPkgEnv.xdaisInstall;
    var status = execute(cmd, attrs);
    if (status.exitStatus) {
        throw new Error(status.output);
    }

    var ialgName = ''
    var pre = '';
    var stdoutLines = status.output.split('\n');
    for (var i = 0; i < stdoutLines.length; i++) {
        if (!stdoutLines[i].match(/ [BD] /)) {
            continue;
        }
        var symName = stdoutLines[i].substr(11);    // "_FIR_TI_free"
        if (symName == '') {
            continue;
        }
        if (symName.charAt(0) == '_') {
            symName = symName.substr(1); // eat the underscore
        }
        if (symName.match(/_IALG$/)) {
            mvi.module = symName.substr(0, symName.indexOf('_'));
            var venIndex = symName.indexOf('_') + 1;
            mvi.vendor = symName.substr(venIndex,
                         symName.lastIndexOf('_') - venIndex);
            pre = symName.substr(0, symName.lastIndexOf('_') + 2);
            ialgName = symName;
            break;
        }
    }
    if (!mvi.module) {
        return (mvi);
    }
    for (var i = 0; i < stdoutLines.length; i++) {
        if (!stdoutLines[i].match(/ [BD] /)) {
            continue;
        }
        var symName = stdoutLines[i].substr(11);
        if (symName.charAt(0) == '_') {
            symName = symName.substr(1); // eat the underscore
        }
        if (symName != ialgName && symName.substr(0, pre.length) == pre) {
            mvi.inface = symName.substr(symName.lastIndexOf('_') + 1);
            break;
        }
    }
    return (mvi);
}


function execute(command, attrs)
{
    var status = {}; 
    xdc.exec(command, attrs, status);
    return status; 
}

function checkCommand(command)
{
    if (isWin) {
        command += ".exe";
    }
    return command;
}

/*
 *  ======== getLibFileInfo ========
 */
function getLibFileInfo(libFile, codecPkgEnv)
{
    var foundArch = false;
    var foundEndian = false;
    var foundFormat = false;
    var cmd = [];
    var libInfo = {
        arch       : null,
        target     : null,
        targname   : null,
        targsuffix : null,
        format     : null,
        endian     : null
    };

    var cmdStr = checkCommand(codecPkgEnv.xdaisInstall + '/packages/ti/xdais/qualiti/cgtools/bin/ofd6x');    
    cmd.push(cmdStr);
    cmd.push('--obj_display=none,header');
    cmd.push(libFile);

    // execute the command line
    var attrs = {};
    attrs.cwd = codecPkgEnv.xdaisInstall;
    var status = execute(cmd, attrs);
    if (status.exitStatus) {
        throw new Error(status.output);
    }

    var arch = '';
    var stdoutLines = status.output.split('\n');
    for (var i = 0; i < stdoutLines.length; i++) {
        var line = stdoutLines[i];
        if (!foundArch && line.match(/CPU Generation:/)) {
            if (line.match(/C6400+/)) {
                foundArch = true;
                libInfo.arch = 'C64P';
                libInfo.target = 'ti.targets.C64P';
            }
            else if (line.match(/C674/)) {
                foundArch = true;
                libInfo.arch = 'C674';
                libInfo.target = 'ti.targets.C674';
            }
        }
        if (!foundArch && line.match(/Machine:/)) {
            if (line.match(/ARM/)) {    /* no other info than 'ARM' in dump */
                foundArch = true;
                libInfo.arch = 'ARM';
            }
        }
        if (!foundEndian && line.match(/Machine Endian:/)) {
            if (line.match(/little/)) {
                libInfo.endian = 'little';
                foundEndian = true;
            }
            else if (line.match(/big/)) {
                libInfo.endian = 'big';
                foundEndian = true;
            }
        }
        if (!foundFormat && line.match(/Format:/)) {
            if (line.match(/COFF/)) {
                libInfo.format = 'coff';
                foundFormat = true;
            }
            else if (line.match(/ELF/)) {
                libInfo.format = 'elf';
                foundFormat = true;
            }
        }
        if(foundArch && foundEndian && foundFormat) {
            break;
        }
    }
    if (foundArch && libInfo.arch != 'ARM') {
        try {
            var tmod = xdc.useModule(libInfo.target);
            var base = String(tmod.$super.base);
            libInfo.targname = tmod.name;
            libInfo.targsuffix = tmod.suffix;
        }
        catch (e) {
            libInfo.targname = null;
            libInfo.targsuffix = null;
        }
    }
    return (libInfo);
}


function ofd6xVersion(toolsDir)
{
    var cmd = [];
    var vers = '';

    var cmdStr = checkCommand(toolsDir + '/bin/ofd6x');    
    cmd.push(cmdStr);

    var attrs = {};
    attrs.cwd = toolsDir;
    var status = execute(cmd, attrs);
    var stdoutLines = status.output.split('\n');
    for (var i = 0; i < stdoutLines.length; i++) {
        var line = stdoutLines[i];
        if (line.match(/TMS320C6x Object File Display/)) {
            var versIndex = line.indexOf('v');
            if (versIndex != -1) {
                vers = line.substr(versIndex + 1);
            }
            break;
        }
    }
    return (vers);
}


/*
 *  @(#) ti.sdo.ce.wizards.gencodecpkg; 1, 0, 0, 0,57; 12-2-2010 21:28:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

