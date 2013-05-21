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
var swt;
var browser;
var custom;
var graphics;
var layout;
var widgets;
var events;

var base = String(xdc.csd()).replace(/\\/g,"/");

function initSWT() {
    swt = xdc.jre.org.eclipse.swt;
    browser = xdc.jre.org.eclipse.swt.browser;
    custom = xdc.jre.org.eclipse.swt.custom;
    graphics = xdc.jre.org.eclipse.swt.graphics;
    layout = xdc.jre.org.eclipse.swt.layout;
    widgets = xdc.jre.org.eclipse.swt.widgets;
    events = xdc.jre.org.eclipse.swt.events;
}

/**
* Opens a new message box widget
* @param {String} message This message will be displayed in the message box
* @param {codecPkgEnv} 
*/            
function createMessageBox(message, codecPkgEnv)
{ 
    if (codecPkgEnv.tid != codecPkgEnv.guiId) {
         _syncExecMessageBox(message, codecPkgEnv);
    }
    else {
        _createMessageBox(message, codecPkgEnv);
    }
}

function _createMessageBox(message, codecPkgEnv)
{ 
    initSWT();

    if (codecPkgEnv.shell && !codecPkgEnv.shell.isDisposed()) {
        var shellMessage = codecPkgEnv.shell;
    }
    else if (codecPkgEnv.display && !codecPkgEnv.display.isDisposed()) {
        var shellMessage = new widgets.Shell(codecPkgEnv.display, 
                                             swt.SWT.APPLICATION_MODAL);
    }
    else {
        var shellMessage = new widgets.Shell();
    }
    if (codecPkgEnv.shellLocation != null) {
        shellMessage.setLocation(codecPkgEnv.shellLocation);
    }
    var msgBox = widgets.MessageBox(shellMessage, swt.SWT.OK);
    msgBox.setText("Codec Engine GenCodecPkg Wizard");
    msgBox.setMessage(message);
    msgBox.open();
}

function _syncExecMessageBox(message, codecPkgEnv)
{
    if (!codecPkgEnv.display.isDisposed()) {
        try {
            codecPkgEnv.display.syncExec(
                new java.lang.Runnable() {
                    run: function() {
                        try {
                            retVal = _createMessageBox(message, codecPkgEnv);
                        }
                        catch (e) {}
                    }
            });
        }
        catch (e) {}
    }
}

/**
* Opens a new message box widget with yes and no options
* @param {String} message This message will be displayed in the message box
* @param {codecPkgEnv}
*/            
function createYesNoBox(message, codecPkgEnv)
{ 
    if (codecPkgEnv.tid != codecPkgEnv.guiId) {
        var retVal = _syncExecYesNoBox(message, codecPkgEnv);
    }
    else {
        var retVal = _createYesNoBox(message, codecPkgEnv);
    }
    return (retVal);
}

function _createYesNoBox(message, codecPkgEnv)
{ 
    initSWT();

    if (codecPkgEnv.shell && !codecPkgEnv.shell.isDisposed()) {
        var shellMessage = codecPkgEnv.shell;
    }
    else if (codecPkgEnv.display && !codecPkgEnv.display.isDisposed()) {
        var shellMessage = new widgets.Shell(codecPkgEnv.display, 
                                             swt.SWT.APPLICATION_MODAL);
    }
    else {
        var shellMessage = new widgets.Shell();
    }
    if (codecPkgEnv.shellLocation!=null) {
        shellMessage.setLocation(codecPkgEnv.shellLocation);
    }
    var msgBox = widgets.MessageBox(shellMessage, swt.SWT.YES|swt.SWT.NO);
    msgBox.setText("Codec Engine GenCodecPkg Wizard");
    msgBox.setMessage(message);
    var retVal = msgBox.open();
    return (retVal == swt.SWT.YES) ? 1 : 2;
}


function _syncExecYesNoBox(message, codecPkgEnv)
{
    var retVal = 2;
    if (!codecPkgEnv.display.isDisposed()) {
        try {
            codecPkgEnv.display.syncExec(
                new java.lang.Runnable() {
                    run: function() {
                        try {
                            retVal = _createYesNoBox(message, codecPkgEnv);
                        }
                        catch (e) {}
                    }
            });
        }
        catch (e) {}
    }
    return (retVal);
}

/*
 *  @(#) ti.sdo.ce.wizards.gencodecpkg; 1, 0, 0, 0,57; 12-2-2010 21:28:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

