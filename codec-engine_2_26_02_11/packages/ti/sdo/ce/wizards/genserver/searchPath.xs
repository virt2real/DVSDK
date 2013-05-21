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

var PathEditor = xdc.module('xdc.tools.sg.widgets.PathEditor');
var logic = xdc.loadCapsule("logic.xs");
var custom;
var graphics;
var layout;
var widgets;
var SWT;
var GD;

var EDIT_PATH_STR = "Edit Search Path";
var SEARCH_PATH_STR = "Search Path";
var ERROR_STR = "Error";
var INVALID_DIR_STR = "Invalid directory: ";
var gui;
var swtInited;
var msgArr = [];

function initSWT() {
    custom = xdc.jre.org.eclipse.swt.custom;
    graphics = xdc.jre.org.eclipse.swt.graphics;
    layout = xdc.jre.org.eclipse.swt.layout;
    widgets = xdc.jre.org.eclipse.swt.widgets;
    SWT = xdc.jre.org.eclipse.swt.SWT;
    GD = layout.GridData;
}

function setGui(g)
{
    gui = g;
}

/*
 *  ======== _editSearchPathGui ========
 */
function _editSearchPathGui(serverEnv, display, shell, pathArr)
{

    if (!swtInited) {
        initSWT();
        swtInited = true;
    }

    var enterDlg = widgets.Shell(shell,
        SWT.DIALOG_TRIM | SWT.RESIZE | SWT.APPLICATION_MODAL);
    enterDlg.setLayout(layout.GridLayout());
    enterDlg.setSize(420, 300);
    enterDlg.setText('Edit ' + SEARCH_PATH_STR);

    var errObj = gui.createImageLabel2(enterDlg, 2, 2);
    errObj.label2.addListener(SWT.Selection,function(e) {
        showErrors();
    });

    function showErrors() {
        gui.errorsList(enterDlg, 'Warnings', msgArr);
    }

    var enterLabel = widgets.Label(enterDlg, SWT.NONE);
    enterLabel.setLayoutData(layout.GridData(GD.FILL_HORIZONTAL));
    enterLabel.setText(SEARCH_PATH_STR + ':');

    /* create GUI editor for user editable portion of the package path */
    var enterGui = PathEditor.create(enterDlg);
    enterGui.addXDCRepositories = false;
    var enterGuiControl = enterGui.control;
    enterGuiControl.setLayoutData(GD(GD.FILL_BOTH));

    /* create text editor for same */
    var enterText = widgets.Text(enterDlg, SWT.LEFT | SWT.SINGLE | SWT.BORDER);
    enterText.setLayoutData(layout.GridData(GD.FILL_HORIZONTAL));

    /* functions to update text in Gui and Text widgets */
    function setGuiPath(pathArr) {
        enterGui.setUserPath(pathArr);
    }
    function setTextPath(pathStr) {
        enterText.setText(pathStr);
        enterText.selectAll();
    }

    /* functions to retrieve text from Gui and Text widgets */
    function getGuiPath() {
        return (enterGui.getUserPath());
    }
    function getTextPath() {
        return (String(enterText.getText()).split(';'));
    }

    /* initialize the Gui and Text widgets */
    setGuiPath(pathArr);
    setTextPath(pathArr.join(';'));

    /* synchronize the Gui and Text widgets */
    var inProgress = false;
    enterText.addModifyListener(function () {
        if (!inProgress) {
            inProgress = true;
            setGuiPath(getTextPath());
            inProgress = false;
            checkInstallDirs(serverEnv, getGuiPath(), errObj);
        }
    });
    enterGuiControl.addListener(PathEditor.PATH_CHANGED, function () {
        if (!inProgress) {
            inProgress = true;
            setTextPath(getGuiPath().join(';'));
            inProgress = false;
            checkInstallDirs(serverEnv, getGuiPath(), errObj);
        }
    });

    /* create OK and Cancel buttons */
    var btnComposite = widgets.Composite(enterDlg, SWT.NONE); 
    var btnLayout = layout.GridLayout();
    btnLayout.numColumns = 2;   
    btnComposite.setLayout(btnLayout);

    var okBtn = widgets.Button(btnComposite, SWT.PUSH | SWT.DEFAULT);
    okBtn.setText ("OK");
    okBtn.addListener(SWT.Selection, function(e) {
        var error = _validatePath(enterDlg, getGuiPath().join(';'));
        if (!error) {
            pathArr = getGuiPath();
            enterDlg.dispose();
        }
        else {
            pathArr = [];
            enterText.setFocus();
            enterText.selectAll();
        }
    });

    var cancelBtn = widgets.Button(btnComposite, SWT.PUSH);
    cancelBtn.setText ("Cancel");
    cancelBtn.addListener(SWT.Selection, function(e) {
        enterDlg.dispose();
    });
    enterDlg.open();
    checkInstallDirs(serverEnv, getGuiPath(), errObj);
    while (!enterDlg.isDisposed()) {
        if (!display.readAndDispatch()) {
            display.sleep();
        }
    }
    return (pathArr);
}

/*
 *  ======== checkInstallDirs ========
 */
function checkInstallDirs(serverEnv, pathArr, errObj)
{
    if (serverEnv.useRulesMake) {
        gui.setImageLabel2(errObj, null, '');
        return;
    }
    msgArr = [];
    var notFoundArr = logic.checkForRequiredInstallDirs(serverEnv, pathArr);
    if (notFoundArr.length > 1) {
        var str = 'The following install directories are required to build your Server:';
        for each (var dir in notFoundArr) {
            str += '\n       ' + dir;
        }
        msgArr.push(str)
        gui.setImageLabel2(errObj, gui.ICO_WARNING,
                           notFoundArr.length + ' warnings', true);
    }
    else if (notFoundArr.length == 1) {
        gui.setImageLabel2(errObj, gui.ICO_WARNING,
                           notFoundArr[0] + ' ' +
                           'install directory required to build your Server');
    }
    else {
        gui.setImageLabel2(errObj, null, '');
    }
}

/*
 *  ======== filterDirs ========
 *
 *  filter duplicates and dirs that don't exist
 *
 */
function filterDirs(pathArr)
{
    var newPath = [];

    var dirs={};
    for (var i = 0 ; i < pathArr.length; i++) {
        if (String(pathArr[i]) != '') {
            var f = java.io.File(pathArr[i]);
            if (f.exists()) {
                dirs[String(f.getCanonicalPath())] = true;
            }
        }
    }

    for (i in dirs) {
        newPath.push(i.replace(/\\/g, '/'));
    }
    return (newPath);
}

/*
 *  ======== getPackagePath ========
 */
function getPackagePath()
{
    return(filterDirs(Packages.xdc.services.global.Path.getPath()));
}

/*
 *  ======== modifyPackageRepositorySearchPath ========
 */
function modifyPackageRepositorySearchPath(serverEnv, display, shell,
                                           curPathArr)
{
    
    return (_editSearchPathGui(serverEnv,display, shell, curPathArr));
}

/*
 *  ======== _validatePath ========
 */
function _validatePath(shell, path)
{
    var error = false;
    path = String(path).replace(/;{1,}/g, ';');  /* remove dup ';'s */

    /* Verify existence of directories */
    var chkDir;
    var pathArr = path.split(';');
    for each (var dir in pathArr) {
        if (dir.length != 0) {
            chkDir = java.io.File(dir);
            if (!chkDir.exists()) {
                var msgBox = widgets.MessageBox(shell,
                    SWT.OK | SWT.ICON_WARNING);
                msgBox.setText(ERROR_STR);
                msgBox.setMessage(INVALID_DIR_STR + dir);
                msgBox.open();
                error = true;
                break;
            }
        }
    }
    return (error);
}


/*
 *  @(#) ti.sdo.ce.wizards.genserver; 1, 0, 0,84; 12-2-2010 21:28:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

