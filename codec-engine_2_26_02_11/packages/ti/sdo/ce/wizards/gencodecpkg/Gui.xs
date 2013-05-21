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

var swt;
var browser;
var custom;
var graphics;
var layout;
var widgets;
var events;
var dnd;
var program;

var display;
var image;
var codecPkgEnv = null;

var xmlOps = xdc.loadCapsule("xmlOps.xs");
var wizard_constants = xdc.loadCapsule("wizard_constants.xs");
xmlOps.setWizardConstants(wizard_constants);
var fileModule = xdc.module('xdc.services.io.File');
var logic = xdc.loadCapsule("logic.xs");
var shared_gui = xdc.loadCapsule("shared_gui.xs");
var libParser = xdc.loadCapsule('libparser.xs');
xmlOps.setLogic(logic);
var os = String(java.lang.System.getProperty('os.name'));
var isWin = (os.match(/^Windows/i) != null);
var SHELL_WIDTH = isWin ? 625 : 670;
var SHELL_HEIGHT = isWin ? 400 : 435;
var libFileLoaded = false;
var page1_1Displayed = false;
var page1_2Displayed = false;
var ICO_ERROR;
var ICO_ENTER;
var ICO_GENALG_FILE;
var ICO_LIB_FILE;
var CUR_WAIT;
var FINISH_BTN = 0;
var CANCEL_BTN = 1;
var XDCVERS_MSG = 'The version of xdctools is older than 3.16. Either restart '
+'GenCodecPkg Wizard with xdctools 3.16 or higher, or modify the generated '
+'makefile to point at a newer version of xdctools.';

var EXPERT_HOVER = 'When left unchecked, the Interface and Package Name '
+'fields will be read-only\nand will be automatically generated based '
+'on Module and Vendor';

function initSWT() {
    swt = xdc.jre.org.eclipse.swt;
    browser = xdc.jre.org.eclipse.swt.browser;
    custom = xdc.jre.org.eclipse.swt.custom;
    graphics = xdc.jre.org.eclipse.swt.graphics;
    layout = xdc.jre.org.eclipse.swt.layout;
    widgets = xdc.jre.org.eclipse.swt.widgets;
    events = xdc.jre.org.eclipse.swt.events;
    dnd = xdc.jre.org.eclipse.swt.dnd;
    program = xdc.jre.org.eclipse.swt.program;
}

function setCodecPkgEnv(cpe)
{
    codecPkgEnv = cpe;
}

function createPartControl(parent)
{
    main(codecPkgEnv, parent);
}

var buttons = {
    backEnabled:      false,
    nextEnabled:      false,
    finishEnabled:    false,
    updated:          false
}

var pageFxns = [page0Fxn, page1Fxn1];
var numberOfPages = pageFxns.length;

var hoverTip = null;
var hoverLabel = null;

var openGencodecPkg = {
    title : 'Open your .gencodecpkg file',
    filterExt : ['*.gencodecpkg', '*.*'],
    filterNames : ['GenCodecPkg Files (*.gencodecpkg)', 'All Files (*.*)']
}

var openGenAlg = {
    title : 'Open your .genalg file',
    filterExt : ['*.genalg', '*.*'],
    filterNames : ['GenAlg Files (*.genalg)', 'All Files (*.*)']
}

var libFilterExt = ['*.*','*.l64*;*.a64*','*.l674;*.a674*'];
var libFilterNames = ['C64P Libraries (*.a64P)', 'C674 Libraries (*.a674)', 'All Files (*.*)'];

function init(codecPkgEnv, parent)
{
    if (parent) {
        display = parent.getDisplay();
    }
    else {
        display = new widgets.Display();
    }
    codecPkgEnv.display = display;
    image = new graphics.Image(display, csd + "/img/tray.JPG");
    ICO_ERROR = graphics.Image(display, csd + "/img/error_tsk.gif");
    ICO_ENTER = graphics.Image(display, csd + "/img/neweditor.gif");
    ICO_GENALG_FILE = graphics.Image(display, csd + "/img/newxml.gif");
    ICO_LIB_FILE = graphics.Image(display, csd + "/img/newlib.gif");
    CUR_WAIT = graphics.Cursor(display, swt.SWT.CURSOR_WAIT);
    ICO_WARNING = graphics.Image(display, csd + "/img/warning.gif");

    var shellLocation = graphics.Point(66,87);

    codecPkgEnv.shellLocation = shellLocation;
/*
    var shell = new widgets.Shell(display, swt.SWT.DIALOG_TRIM |
                                  swt.SWT.APPLICATION_MODAL);

    shell.setImage(image);
    shell.setSize(200, 100);
    shell.setText("Loading...");

    if (codecPkgEnv.shellLocation!=null) {
        shell.setLocation(codecPkgEnv.shellLocation);
    }

    var grid = new layout.GridLayout(1, false);
    shell.setLayout(grid);

    var comp = new widgets.Composite(shell, swt.SWT.NONE);
    comp.setLayout(new layout.GridLayout());

    var text = new widgets.Text(comp, swt.SWT.WRAP | swt.SWT.READ_ONLY);
    text.setText(wizard_constants.INIT_MESSAGE);
    text.setLayoutData(new layout.GridData(180, 50));

    var pb = new widgets.ProgressBar(comp, swt.SWT.HORIZONTAL);
    pb.setMinimum(0);
    pb.setMaximum(100);
    pb.setBounds(10, 10, 200, 20);
    shell.pack();
    shell.open();

    pb.setSelection(30);

    pb.setSelection(50);
    pb.setSelection(80);
    pb.setSelection(100);
    shell.dispose();
*/
}


function page0Fxn(comp)
{
    var shell = comp.getShell();

    var errObj = createImageLabel(comp, 2, 2);

    var boxComp = widgets.Composite(comp, swt.SWT.NONE);
    var boxLayout = layout.GridLayout();
    boxLayout.numColumns = 2;

    boxComp.setLayout(boxLayout);
    var gridHint = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
    gridHint.horizontalSpan = 2;
    boxComp.setLayoutData(gridHint);

    var useAlgImg = widgets.Composite(boxComp, swt.SWT.BORDER);
    useAlgImg.setBackgroundImage(ICO_GENALG_FILE);
    useAlgImg.setToolTipText(wizard_constants.OPEN_GENALG_HOVER);
    var useAlgData = layout.GridData();
    useAlgData.minimumWidth = 32;
    useAlgData.widthHint = 32;
    useAlgData.minimumHeight = 32;
    useAlgData.heightHint = 32;
    useAlgImg.setLayoutData(useAlgData);
    var useAlgPkg = widgets.Button(boxComp, swt.SWT.RADIO);
    useAlgPkg.setText('I have a .genalg ' +
            'file previously created using the XDAIS GenAlg Wizard');
    useAlgPkg.setToolTipText(wizard_constants.OPEN_GENALG_HOVER);
    useAlgPkg.addListener(swt.SWT.Selection,
    function(e) {
        codecPkgEnv.useGenAlg = true;
        codecPkgEnv.useLib = false;
        codecPkgEnv.useInput = false;
        pageFxns[1] = page1Fxn1;
        setState();
    });

    var useLibImg = widgets.Composite(boxComp, swt.SWT.BORDER);
    useLibImg.setBackgroundImage(ICO_LIB_FILE);
    useLibImg.setToolTipText(wizard_constants.OPEN_LIB_HOVER);
    var useLibData = layout.GridData();
    useLibData.minimumWidth = 32;
    useLibData.widthHint = 32;
    useLibData.minimumHeight = 32;
    useLibData.heightHint = 32;
    useLibImg.setLayoutData(useLibData);
    var useLibFile = widgets.Button(boxComp, swt.SWT.RADIO);
    useLibFile.setText('I have an existing XDAIS library file');
    useLibFile.setToolTipText(wizard_constants.OPEN_LIB_HOVER);
    useLibFile.addListener(swt.SWT.Selection,
    function(e) {
        codecPkgEnv.useGenAlg = false;
        codecPkgEnv.useLib = true;
        codecPkgEnv.useInput = false;
        pageFxns[1] = page1Fxn2;
        setState();
    });

    var useEnterImg = widgets.Composite(boxComp, swt.SWT.BORDER);
    useEnterImg.setBackgroundImage(ICO_ENTER);
    useEnterImg.setToolTipText(wizard_constants.ENTER_INFO_HOVER);
    var useEnterData = layout.GridData();
    useEnterData.minimumWidth = 32;
    useEnterData.widthHint = 32;
    useEnterData.minimumHeight = 32;
    useEnterData.heightHint = 32;
    useEnterImg.setLayoutData(useEnterData);

    var enterInfo = widgets.Button(boxComp, swt.SWT.RADIO);
    enterInfo.setText('I want to create an algorithm from scratch, ' +
        ' including starter codec sources');
    enterInfo.setToolTipText(wizard_constants.ENTER_INFO_HOVER);
    enterInfo.addListener(swt.SWT.Selection,
    function(e) {
        codecPkgEnv.useGenAlg = false;
        codecPkgEnv.useLib = false;
        codecPkgEnv.useInput = true;
        pageFxns[1] = page1Fxn3;
        setState();
    });

    // Browse for xdais dir
    var xdaisInstall = new BrowseButton(comp, shell, isWin ? 165 : 185);
    xdaisInstall.setMessage("Set XDAIS Install Dir");
    xdaisInstall.addListener("", "Please enter a valid XDAIS install directory", false);
    xdaisInstall.btn.addListener(swt.SWT.Selection, function(additionalEvent) {
    });
    xdaisInstall.textBox.addListener(swt.SWT.Modify, function(e) {
        setState();
    });
    xdaisInstall.btn.setToolTipText(wizard_constants.XDAIS_DESC);
    xdaisInstall.textBox.setToolTipText(wizard_constants.XDAIS_DESC);

    // Create menu bar with listeners
    var menuBar = createMenu(shell, 0);
/*
    menuBar.getItem(0).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function (openListener) {
        openEvent();
    });

    function openEvent() {
        codecPkgEnv = readXmlFile(shell, image, codecPkgEnv, 
                                  openGencodecPkg);
        populatePanel();
    }
*/
    menuBar.getItem(0).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function (whatTypeListener) {
        program.Program.launch(wizard_constants.WHAT_TYPE_LINK);
    } );
    menuBar.getItem(0).getMenu().getItem(1).addListener(swt.SWT.Selection,
    function (faqListener) {
        program.Program.launch(wizard_constants.FAQ_LINK);
    } );

    populatePanel();

    function populatePanel() {
        if (codecPkgEnv.useGenAlg) {
            useAlgPkg.setSelection(true);
            pageFxns[1] = page1Fxn1;
        }
        else if (codecPkgEnv.useLib) {
            useLibFile.setSelection(true);
            pageFxns[1] = page1Fxn2;
        }
        else if (codecPkgEnv.useInput) {
            enterInfo.setSelection(true);
            pageFxns[1] = page1Fxn3;
        }
        if (codecPkgEnv.xdaisInstall != null) {
            xdaisInstall.textBox.setText(codecPkgEnv.xdaisInstall);
        }
        setState();
    }

    function setState() {
        xdaisInstall.btn.setEnabled(!codecPkgEnv.useGenAlg);
        xdaisInstall.textBox.setEditable(!codecPkgEnv.useGenAlg);
        valid = validateInput();
        buttons.nextEnabled = valid;
        buttons.backEnabled = false;
        buttons.finishEnabled = false;
        buttons.updated = true;
    }

    function validateInput() {
        var valid = true;
        var msg = null;
        if (!codecPkgEnv.useGenAlg) {
            valid = validateXdaisInstall(xdaisInstall.textBox.getText());
            if (!valid) {
                msg = "Please enter valid 'XDAIS Install Dir'";
            }
        }
        if (valid) {
            setImageLabel(errObj, null, '');
        }
        else {
            setImageLabel(errObj, ICO_ERROR, msg);
        }
        return (valid);
    }

    function collectInput() {
        codecPkgEnv.xdaisInstall = String(xdaisInstall.textBox.getText());
    }

    return {
        title:              "What type of Codec package would you like to create?",
        composite:          comp,
        collectInputFxn:    collectInput
    };

}

function page1Fxn1(comp)
{

    var initFxn;

    var shell = comp.getShell();

    var errObj = createImageLabel(comp, 3, 2);
    errObj.btn.addListener(swt.SWT.Selection,
    function (e) {
        selectAlgPackageRepo();
    });

    var col1Comp = widgets.Composite(comp, swt.SWT.BORDER);
    var col1Layout = layout.GridLayout();
    col1Layout.numColumns = 2;
    col1Comp.setLayout(col1Layout);
    var col1Data = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|layout.GridData.FILL_HORIZONTAL);
    col1Data.minimumWidth = 175;
    col1Data.widthHint = 175;

    col1Comp.setLayoutData(col1Data);

    var lbl = widgets.Label(col1Comp, swt.SWT.NONE);
    lbl.setText('Module:');
    lbl.setToolTipText(wizard_constants.GENALG_MODULE_HOVER);
    var textModuleName = widgets.Text(col1Comp, swt.SWT.BORDER|swt.SWT.READ_ONLY);
    textModuleName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));

    var lbl = widgets.Label(col1Comp, swt.SWT.NONE);
    lbl.setText('Vendor:');
    lbl.setToolTipText(wizard_constants.GENALG_VENDOR_HOVER);
    var textVendorName = widgets.Text(col1Comp, swt.SWT.BORDER|swt.SWT.READ_ONLY);
    textVendorName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));

    var lbl = widgets.Label(col1Comp, swt.SWT.NONE);
    lbl.setText('Interface:');
    lbl.setToolTipText(wizard_constants.GENALG_INTERFACE_HOVER);
    var textInterfaceName = widgets.Text(col1Comp, swt.SWT.BORDER|swt.SWT.READ_ONLY);
    textInterfaceName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));

    var col2Comp = widgets.Composite(comp, swt.SWT.NONE);
    var col2Layout = layout.GridLayout();
    col2Layout.numColumns = 2;
    col2Comp.setLayout(col2Layout);
    var col2Data = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|layout.GridData.FILL_HORIZONTAL);
    col2Data.minimumWidth = 400;
    col2Data.widthHint = 400;

    col2Comp.setLayoutData(col2Data);

    var lbl = widgets.Label(col2Comp, swt.SWT.NONE);
    lbl.setText('XDM Algorithm Package Name:');
    lbl.setToolTipText(wizard_constants.GENALG_XDM_ALG_PKG_HOVER);
    var textXdaisPackageName = widgets.Text(col2Comp, swt.SWT.BORDER|swt.SWT.READ_ONLY);
    textXdaisPackageName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));

    var lbl = widgets.Label(col2Comp, swt.SWT.NONE);
    lbl.setText('Codec Package Name:');
    lbl.setToolTipText(wizard_constants.GENALG_CODEC_PKG_HOVER);
    var textPackageName = widgets.Text(col2Comp, swt.SWT.BORDER);
    textPackageName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    textPackageName.addListener(swt.SWT.Modify, function(e) {
        setState();
    });
    textPackageName.addListener(swt.SWT.Verify, function(e) {
        e.text = String(e.text).toLowerCase();
    });
    addSelectAllListener(textPackageName);

    var lbl = widgets.Label(col2Comp, swt.SWT.NONE);
    var lblData = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING);
    lblData.verticalIndent = 4;
    lbl.setLayoutData(lblData);
    lbl.setText("Targets: ");
    lbl.setToolTipText(wizard_constants.GENALG_TARGET);

    var targetTable = widgets.Table(col2Comp,
            swt.SWT.SINGLE|swt.SWT.BORDER|swt.SWT.V_SCROLL);
    var gridDataStretch = layout.GridData(layout.GridData.FILL_HORIZONTAL);
    gridDataStretch.verticalIndent = 8;
    gridDataStretch.heightHint = 30;
    targetTable.setLayoutData(gridDataStretch);

    targetTable.addListener(swt.SWT.MouseHover, function(e) {
        controlMouseOver(shell, targetTable, e);
    });
    targetTable.addListener(swt.SWT.Dispose, function(e){ mouseLeave(e); });
    targetTable.addListener(swt.SWT.KeyDown, function(e){ mouseLeave(e); });
    targetTable.addListener(swt.SWT.MouseMove, function(e){ mouseLeave(e); });

    /* populate target table */
    function populateTargetTable(targetsObj) {
        targetTable.removeAll();
        for (var i = 0; i < codecPkgEnv.genAlg.targets.length; i++) {
            var targIndex = logic.getTargetIndex(codecPkgEnv.genAlg.targets[i].target);
            if (targIndex == -1) {
                continue;
            }
            var item = widgets.TableItem(targetTable, 0);
            item.setText(wizard_constants.targetDesc[targIndex]);
            var data = {};
            data.target = codecPkgEnv.genAlg.targets[i].target;
            data.targname = codecPkgEnv.genAlg.targets[i].targname;
            data.targsuffix = codecPkgEnv.genAlg.targets[i].targsuffix;
            data.ccOpts = codecPkgEnv.genAlg.targets[i].ccOpts;
            data.cgTools = codecPkgEnv.genAlg.targets[i].cgTools;
            data.hover = codecPkgEnv.genAlg.targets[i].target;
            item.setData(data);
            item.setChecked(true);
        }
    }

    var iresCheck = widgets.Button(col2Comp, swt.SWT.CHECK);
    iresCheck.setText('Add IRES Interface');
    var iresData = new layout.GridData();
    iresData.verticalIndent = -4;
    iresCheck.setLayoutData(iresData);
    iresCheck.setEnabled(false);

    var row2Comp = widgets.Composite(comp, swt.SWT.NONE);
    var row2Layout = layout.GridLayout();
    row2Layout.numColumns = 2;
    row2Comp.setLayout(row2Layout);
    var row2Data = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
    row2Data.horizontalSpan = 2;
    row2Comp.setLayoutData(row2Data);

    // Browse for output directory
    var output = new BrowseButton(row2Comp, shell, isWin ? 165 : 185);
    output.setMessage("Set Destination Directory");
    output.btn.setToolTipText(wizard_constants.OUTPUT_HOVER);
    output.addListener("", "Please enter a valid package directory", false);
    output.btn.addListener(swt.SWT.Selection, function(additionalEvent) {
    });
    output.textBox.addListener(swt.SWT.Modify, function(e) {
        setState();
    });

    var CCSProjCheck = widgets.Button(comp, swt.SWT.CHECK);
    CCSProjCheck.setText('Generate CCS Eclipse project');
    var projCheckData = new layout.GridData(layout.GridData.HORIZONTAL_ALIGN_END);
    projCheckData.horizontalSpan = 2;
    CCSProjCheck.setLayoutData(projCheckData);

    // Create menu bar with listeners
    var menuBar = createMenu(shell, 1);
    menuBar.getItem(0).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function (openListener) {
        openEvent();
    });
    menuBar.getItem(1).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function (fromGenalgListener) {
        program.Program.launch(wizard_constants.FROM_GENALG_LINK);
    } );
    menuBar.getItem(1).getMenu().getItem(1).addListener(swt.SWT.Selection,
    function (faqListener) {
        program.Program.launch(wizard_constants.FAQ_LINK);
    } );

    function openEvent() {
        codecPkgEnv = readXmlFile(shell, image, codecPkgEnv,
                                  openGenAlg);
        populatePanel();
    }

    function populatePanel() {
        if (codecPkgEnv.xdaisPackage != null) {
            textXdaisPackageName.setText(codecPkgEnv.xdaisPackage);
        }
        if (codecPkgEnv.genAlg.packageName != null) {
            textPackageName.setText(codecPkgEnv.genAlg.packageName);
        }
        if (codecPkgEnv.genAlg.moduleName != null) {
            textModuleName.setText(codecPkgEnv.genAlg.moduleName);
        }
        if (codecPkgEnv.genAlg.vendorName != null) {
            textVendorName.setText(codecPkgEnv.genAlg.vendorName);
        }
        if (codecPkgEnv.genAlg.interfaceName != null) {
            textInterfaceName.setText(codecPkgEnv.genAlg.interfaceName);
        }
        if (codecPkgEnv.output != null && codecPkgEnv.output != "null") {
            output.textBox.setText(codecPkgEnv.output);
        }
        if (codecPkgEnv.genAlgFileLoaded) {
            populateTargetTable(codecPkgEnv.genAlg.targets);
        }
        iresCheck.setSelection((codecPkgEnv.genAlg.ires == true) ? true : false);
        CCSProjCheck.setSelection((codecPkgEnv.genCCSProj == true) ? true : false);
        setState();
    }

    populatePanel();

    function hasError() {
        return (errObj.label1.getImage() != null);
    }

    function setState() {
        valid = validateInput();
        buttons.nextEnabled = false;
        buttons.backEnabled = true;
        buttons.finishEnabled = valid;
        buttons.updated = true;
    }

    function validPackageRepo(packageName, repoName) {

        /* see if the proposed repoName is on package path already */
        var pathArr = String(xdc.curPath()).split(';');
        var algRepoFile = java.io.File(repoName);
        var found = false;
        for (var i = 0; i < pathArr.length; i++) {
            if (algRepoFile.equals(java.io.File(pathArr[i]))) {
                found = true;
                break;
            }
        }
        if (!found) {
            var newPath = xdc.curPath() + ';' + repoName;
            Packages.xdc.services.global.Path.setPath(newPath.split(";"));
        }
        var repo = null;
        try {
            var base = xdc.getPackageBase(packageName);
            repo = base.substr(0, base.length - (packageName.length + 2));
        }
        catch (e) {
            repo = null;
        }
        return (repo);
    }

    function validateInput() {
        var warnMsg = null;
        var msg;
        var valid = true;
        var validAlgPkg = true;
        if (!codecPkgEnv.genAlgFileLoaded) {
            valid = false;
            msg = 'Please open a .genalg file';
        }
        if (valid) {
            var repo = validPackageRepo(codecPkgEnv.xdaisPackage, codecPkgEnv.algRepo);
            if (repo == null) {
                valid = false;
                validAlgPkg = false;
                msg = 'Cannot find package ' + codecPkgEnv.xdaisPackage +
                      '. Select the directory containing this package.';
            }
            else if (!java.io.File(repo).equals(java.io.File(codecPkgEnv.algRepo))) {
                codecPkgEnv.algRepo = repo;
            }
        }
        if (valid) {
            if (String(textPackageName.getText()).length == 0) {

                valid = false;
                msg = 'One or more empty fields';
            }
        }
        if (valid) {
            var outdir = String(output.textBox.getText());
            if (!outdir.length || !java.io.File(outdir).isDirectory()) {
                valid = false;
                msg = "Please enter a valid Destination Directory";
            }
            if (valid) {
                /* check for overwrite */
                outdir = outdir + '/' +
                         String(textPackageName.getText()).replace(/\./g,'/');
                outdir = outdir.replace(/\\/g, '/');
                var outf = java.io.File(outdir);
                if (outf.exists() && outf.list().length > 0) {
                    warnMsg = 'Destination Directory is not empty--files may be overwritten';
                }
            }
        }
        if (!valid) {
            setImageLabel(errObj, ICO_ERROR, msg);
            errObj.btn.setVisible(!validAlgPkg);
        }
        else if (warnMsg) {
            setImageLabel(errObj, ICO_WARNING, warnMsg);
            errObj.btn.setVisible(false);
        }
        else {
            setImageLabel(errObj, null, '');
            errObj.btn.setVisible(false);
        }
        return (valid);
    }

    function selectAlgPackageRepo() {
        var dialog = new widgets.DirectoryDialog(shell);
        dialog.setText('Select package directory');
        var dir = dialog.open();
        if (dir != null) {
            dir = String(dir).replace(/\\/g,"/");
            if (dir.length > codecPkgEnv.xdaisPackage.length) {
                var re = new RegExp(codecPkgEnv.xdaisPackage + '$', 'i');
                var tst = dir.replace(/\//, '.');
                if (tst.match(re)) {
                    dir = dir.substr(0, dir.length - (codecPkgEnv.xdaisPackage.length + 1));
                }
            }
            codecPkgEnv.algRepo = dir;
        }
        setState();
    }

    function collectInput() {
        codecPkgEnv.xdaisPackage = String(textXdaisPackageName.getText());
        codecPkgEnv.genAlg.packageName = String(textPackageName.getText());
        codecPkgEnv.genAlg.moduleName = String(textModuleName.getText());
        codecPkgEnv.genAlg.vendorName = String(textVendorName.getText());
        codecPkgEnv.genAlg.interfaceName = String(textInterfaceName.getText());
        codecPkgEnv.output = String(output.textBox.getText());
        codecPkgEnv.genAlg.targets = [];
        for (var i = 0; i < targetTable.getItemCount(); i++) {
            codecPkgEnv.genAlg.targets.push(targetTable.getItem(i).getData());
        }
        codecPkgEnv.genCCSProj = CCSProjCheck.getSelection() ? true : false;
    }

    if (!page1_1Displayed) {
        page1_1Displayed = true;
        if (!codecPkgEnv.xmlFile) {
            initFxn = openEvent;
        }
        else {
            codecPkgEnv.genAlgFileLoaded = true;
            initFxn= null;
        }
    }
    else {
        initFxn= null;
    }

    return {
        title:              "  Create a Codec Package From a .genalg File",
        composite:          comp,
        collectInputFxn:    collectInput,
        initFxn:            initFxn
    };
}


function page1Fxn2(comp)
{
    var initFxn;

    var shell = comp.getShell();

    var errObj = createImageLabel(comp, 2, 2);

    var col1Comp = widgets.Composite(comp, swt.SWT.BORDER);
    var col1Layout = layout.GridLayout();
    col1Layout.numColumns = 2;
    col1Comp.setLayout(col1Layout);
    var col1Data = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|layout.GridData.FILL_HORIZONTAL);
    col1Data.minimumWidth = 200;
    col1Data.widthHint = 200;

    col1Comp.setLayoutData(col1Data);

    var lbl = widgets.Label(col1Comp, swt.SWT.NONE);
    lbl.setText('Module:');
    lbl.setToolTipText(wizard_constants.LIB_MODULE_HOVER);
    var textModuleName = widgets.Text(col1Comp, swt.SWT.BORDER|swt.SWT.READ_ONLY);
    textModuleName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));

    var lbl = widgets.Label(col1Comp, swt.SWT.NONE);
    lbl.setText('Vendor:');
    lbl.setToolTipText(wizard_constants.LIB_VENDOR_HOVER);
    var textVendorName = widgets.Text(col1Comp, swt.SWT.BORDER|swt.SWT.READ_ONLY);
    textVendorName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));

    var lbl = widgets.Label(col1Comp, swt.SWT.NONE);
    lbl.setText('Interface:');
    lbl.setToolTipText(wizard_constants.LIB_INTERFACE_HOVER);
    var textInterfaceName = widgets.Text(col1Comp, swt.SWT.BORDER|swt.SWT.READ_ONLY);
    textInterfaceName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));

    var col2Comp = widgets.Composite(comp, swt.SWT.NONE);
    var col2Layout = layout.GridLayout();
    col2Layout.numColumns = 2;
    col2Comp.setLayout(col2Layout);
    var col2Data = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|layout.GridData.FILL_HORIZONTAL);
    col2Data.minimumWidth = 300;
    col2Data.widthHint = 300;

    col2Comp.setLayoutData(col2Data);

    var libComp = widgets.Composite(col2Comp, swt.SWT.NONE);
    var libLayout = layout.GridLayout();
    libLayout.numColumns = 4;
    libComp.setLayout(libLayout);
    var libData = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
    libData.horizontalSpan = 2;
    libComp.setLayoutData(libData);

    var libBtn = widgets.Button(libComp, swt.SWT.PUSH);
    libBtn.setText('Library...');
    var libBtnData = new layout.GridData();
    libBtnData.widthHint = 80;
    libBtn.setLayoutData(libBtnData);
    var libTextBox = widgets.Text(libComp, swt.SWT.SINGLE|swt.SWT.BORDER|
                                           swt.SWT.READ_ONLY);
    libTextBox.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    libBtn.addListener(swt.SWT.Selection,
    function (e) {
        selectLibFile();
    });

    var lblSuffix = widgets.Label(libComp, swt.SWT.NONE);
    lblSuffix.setText('Suffix:');
    lblSuffix.setToolTipText(wizard_constants.LIB_SUFFIX_HOVER);
    var textSuffix = widgets.Text(libComp, swt.SWT.SINGLE |
                                  swt.SWT.BORDER);
    var suffixData = new layout.GridData(layout.GridData.HORIZONTAL_ALIGN_END);
    suffixData.widthHint = 25;
    textSuffix.setLayoutData(suffixData);
    textSuffix.addListener(swt.SWT.Modify, function(e) {
        setState();
    });
    addSelectAllListener(textSuffix);

    var lblCodecPkgName = widgets.Label(col2Comp, swt.SWT.NONE);
    lblCodecPkgName.setText("My alg's CE Package Name:");
    lblCodecPkgName.setToolTipText(wizard_constants.LIB_ALGS_CE_PKG);
    var textCodecPkgName = widgets.Text(col2Comp, swt.SWT.BORDER);
    textCodecPkgName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    textCodecPkgName.addListener(swt.SWT.Modify, function(e) {
        setState();
    });
    addSelectAllListener(textCodecPkgName);

    // Templates Drop-down ComboBox
    var lbl = new widgets.Label(col2Comp, swt.SWT.NONE);
    lbl.setText("Base Interface: ");
    lbl.setToolTipText(wizard_constants.LIB_BASE_INTERFACE);
    var templateComboBox = new widgets.Combo(col2Comp, swt.SWT.DROP_DOWN |
        swt.SWT.READ_ONLY);
    templateComboBox.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    function updateTemplatesCombo() {
        var tFile = java.io.File(codecPkgEnv.templatesDir);
        templateComboBox.removeAll();
        // save/try to restore previous
        for each (var f in tFile.listFiles()) {
            if (f.isDirectory() &&
                java.io.File(f.getCanonicalPath() + '/mkpkg.xdt').exists()) {
                templateComboBox.add(f.getName());
            }
        }
        if (templateComboBox.getItemCount()) {
            if (templateComboBox.indexOf(codecPkgEnv.lib.templateName) == -1) {
                var index = templateComboBox.indexOf('IUNIVERSAL');
                if (index == -1) {
                    index = 0;
                }
                codecPkgEnv.lib.templateName = String(templateComboBox.getItem(index));
            }
            templateComboBox.setText(codecPkgEnv.lib.templateName);
        }
    }

    var row2Comp = widgets.Composite(comp, swt.SWT.NONE);
    var row2Layout = layout.GridLayout();
    row2Layout.numColumns = 2;
    row2Comp.setLayout(row2Layout);
    var row2Data = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
    row2Data.horizontalSpan = 2;
    row2Comp.setLayoutData(row2Data);

    // Browse for output directory
    var output = new BrowseButton(row2Comp, shell, isWin ? 165 : 185);
    output.setMessage("Set Destination Directory");
    output.btn.setToolTipText(wizard_constants.OUTPUT_HOVER);
    output.addListener("", "Please enter a valid package directory", false);
    output.btn.addListener(swt.SWT.Selection, function(additionalEvent) {
    });
    output.textBox.addListener(swt.SWT.Modify, function(e) {
        setState();
    });

    var CCSProjCheck = widgets.Button(comp, swt.SWT.CHECK);
    CCSProjCheck.setText('Generate CCSv4 project');
    var projCheckData = new layout.GridData(layout.GridData.HORIZONTAL_ALIGN_END);
    projCheckData.horizontalSpan = 2;
    CCSProjCheck.setLayoutData(projCheckData);


    // Create menu bar with listeners
    var menuBar = createMenu(shell, 1);
    menuBar.getItem(0).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function (openListener) {
        selectLibFile();
    });
    menuBar.getItem(0).getMenu().getItem(2).addListener(swt.SWT.Selection,
    function() {
        var dialog = new widgets.DirectoryDialog(shell);
        dialog.setFilterPath(codecPkgEnv.templatesDir);
        var dir = dialog.open();
        if (dir != null) {
            codecPkgEnv.templatesDir = String(dir).replace(/\\/g,"/");
            updateTemplatesCombo();
            setState();
        }
    });
    menuBar.getItem(1).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function (ffomLibListener) {
        program.Program.launch(wizard_constants.FROM_LIB_LINK);
    } );
    menuBar.getItem(1).getMenu().getItem(1).addListener(swt.SWT.Selection,
    function (faqListener) {
        program.Program.launch(wizard_constants.FAQ_LINK);
    } );

    function selectLibFile () {
        codecPkgEnv  = readLibFile(shell, image, codecPkgEnv);
        if (codecPkgEnv.libFile.length) {
            libTextBox.setText('lib/' + java.io.File(codecPkgEnv.libFile).getName());
            libTextBox.setData(codecPkgEnv.libFile);
            libTextBox.setToolTipText(codecPkgEnv.libFile);
        }
        else {
            libTextBox.setText('');
            libTextBox.setData('');
            libTextBox.setToolTipText('');
        }
        if (codecPkgEnv.lib.moduleName) {
            textModuleName.setText(codecPkgEnv.lib.moduleName);
        }
        else {
            textModuleName.setText('');
        }
        if (codecPkgEnv.lib.vendorName) {
            textVendorName.setText(codecPkgEnv.lib.vendorName);
        }
        else {
            textVendorName.setText('');
        }
        if (codecPkgEnv.lib.interfaceName) {
            textInterfaceName.setText(codecPkgEnv.lib.interfaceName);
        }
        else {
            textInterfaceName.setText('');
        }
        if (codecPkgEnv.lib.packageName) {
            textCodecPkgName.setText(codecPkgEnv.lib.packageName);
        }
        else {
            textCodecPkgName.setText('');
        }
        if(codecPkgEnv.lib.targsuffix) {
            textSuffix.setText(codecPkgEnv.lib.targsuffix);
        }
        else {
            textSuffix.setText('');
        }
        setState();
    }

    function populatePanel() {
        if (codecPkgEnv.lib.packageName != null) {
            textCodecPkgName.setText(codecPkgEnv.lib.packageName);
        }
        if (codecPkgEnv.lib.moduleName != null) {
            textModuleName.setText(codecPkgEnv.lib.moduleName);
        }
        if (codecPkgEnv.lib.vendorName != null) {
            textVendorName.setText(codecPkgEnv.lib.vendorName);
        }
        if (codecPkgEnv.lib.interfaceName != null) {
            textInterfaceName.setText(codecPkgEnv.lib.interfaceName);
        }
        if (codecPkgEnv.lib.templateName != null) {
            templateComboBox.setText(codecPkgEnv.lib.templateName);
        }
        if (codecPkgEnv.libFile != null) {
            if (codecPkgEnv.libFile.length) {
                libTextBox.setText('lib/' + java.io.File(codecPkgEnv.libFile).getName());
                libTextBox.setData(codecPkgEnv.libFile);
                libTextBox.setToolTipText(codecPkgEnv.libFile);
            }
        }
        if (codecPkgEnv.lib.targsuffix != null) {
            textSuffix.setText(codecPkgEnv.lib.targsuffix);
        }
        if (codecPkgEnv.output != null && codecPkgEnv.output != "null") {
            output.textBox.setText(codecPkgEnv.output);
        }

        CCSProjCheck.setSelection((codecPkgEnv.genCCSProj == true) ? true : false);
        setState();
    }

    if (!codecPkgEnv.templatesDir.length) {
        codecPkgEnv.templatesDir = codecPkgEnv.xdaisInstall +
                                   '/packages/ti/xdais/dm/templates';
    }
    updateTemplatesCombo();
    populatePanel();

    function setState() {
        valid = validateInput();
        buttons.nextEnabled = false;
        buttons.backEnabled = true;
        buttons.finishEnabled = valid;
        buttons.updated = true;
    }

    function validateInput() {
        var warnMsg = null;
        var msg;
        var valid = true;

        if (codecPkgEnv.lib.arch == 'ARM') {
            valid = false;
            msg = 'ARM libraries are not currently supported';
        }
        if (valid) {
            if (String(libTextBox.getText()).length == 0 ||
                String(textModuleName.getText()).length == 0 ||
                String(textVendorName.getText()).length == 0 ||
                String(textInterfaceName.getText()).length == 0) {

                valid = false;
                msg = 'Please select a valid library file';
            }
        }
        if (valid) {
            if (String(textCodecPkgName.getText()).length == 0 ||
                String(textSuffix.getText()).length == 0) {

                valid = false;
                msg = 'One or more empty fields';
            }
        }
        if (valid) {
            var outdir = String(output.textBox.getText());
            if (!outdir.length || !java.io.File(outdir).isDirectory()) {
                valid = false;
                msg = "Please enter a valid Destination Directory";
            }
            if (valid) {
                /* check for overwrite */
                outdir = outdir + '/' +
                         String(textCodecPkgName.getText()).replace(/\./g,'/');
                outdir = outdir.replace(/\\/g, '/');
                var outf = java.io.File(outdir);
                if (outf.exists() && outf.list().length > 0) {
                    warnMsg = 'Destination Directory is not empty--files may be overwritten';
                }
            }

        }
        if (!valid) {
            setImageLabel(errObj, ICO_ERROR, msg);
        }
        else if (warnMsg) {
            setImageLabel(errObj, ICO_WARNING, warnMsg);
        }
        else {
            setImageLabel(errObj, null, '');
        }
        return (valid);
    }

    function collectInput() {
        codecPkgEnv.libFile = String(libTextBox.getText()).length ?
                              String(libTextBox.getData()) : String(libTextBox.getText());
        codecPkgEnv.lib.targsuffix = String(textSuffix.getText());
        codecPkgEnv.lib.packageName = String(textCodecPkgName.getText());
        codecPkgEnv.lib.moduleName = String(textModuleName.getText());
        codecPkgEnv.lib.vendorName = String(textVendorName.getText());
        codecPkgEnv.lib.interfaceName = String(textInterfaceName.getText());
        codecPkgEnv.lib.templateName = String(templateComboBox.getText());
        codecPkgEnv.output = String(output.textBox.getText());
        codecPkgEnv.genCCSProj = CCSProjCheck.getSelection() ? true : false;
    }

    if (!page1_2Displayed) {
        page1_2Displayed = true;
        initFxn = selectLibFile;
    }
    else {
        initFxn= null;
    }

    return {
        title:              "  Create a Codec Package From an XDM Algorithm Library",
        composite:          comp,
        collectInputFxn:    collectInput,
        initFxn:            initFxn
    };
}

function page1Fxn3(comp)
{
    /* required user input:
       optional user input: */

    var targMsg = 'Please select one or more targets';
    var shell = comp.getShell();

    var errObj = createImageLabel(comp, 2, 2);

    var col1Comp = widgets.Composite(comp, swt.SWT.NONE);
    var col1Layout = layout.GridLayout();
    col1Layout.numColumns = 2;
    col1Comp.setLayout(col1Layout);
    var col1Data = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|layout.GridData.FILL_HORIZONTAL);
    col1Data.minimumWidth = 200;
    col1Data.widthHint = 200;
    col1Comp.setLayoutData(col1Data);

    var mviComp = widgets.Composite(col1Comp, swt.SWT.BORDER);
    var mviLayout = layout.GridLayout();
    mviLayout.numColumns = 2;
    mviComp.setLayout(mviLayout);
    var mviData = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|layout.GridData.FILL_HORIZONTAL);
    mviData.horizontalSpan = 2;
    mviComp.setLayoutData(mviData);

    var lbl = widgets.Label(mviComp, swt.SWT.NONE);
    lbl.setText('Module:');
    lbl.setToolTipText(wizard_constants.ENTER_MODULE_HOVER);
    var textModuleName = widgets.Text(mviComp, swt.SWT.BORDER);
    textModuleName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    textModuleName.addListener(swt.SWT.Modify, function(e) {
        textInterfaceName.setText('I' + textModuleName.getText());
        if (!expertCheck.getSelection()) {
            textPackageName.setText(textVendorName.getText() + '.' +
                                    textModuleName.getText());
        }
        setState();
    });
    textModuleName.addListener(swt.SWT.Verify, function(e) {
        e.text = String(e.text).toUpperCase();
    });
    addSelectAllListener(textModuleName);

    var lbl = widgets.Label(mviComp, swt.SWT.NONE);
    lbl.setText('Vendor:');
    lbl.setToolTipText(wizard_constants.ENTER_VENDOR_HOVER);
    var textVendorName = widgets.Text(mviComp, swt.SWT.BORDER);
    textVendorName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    textVendorName.addListener(swt.SWT.Modify, function(e) {
        if (!expertCheck.getSelection()) {
            textPackageName.setText(textVendorName.getText() + '.' +
                                    textModuleName.getText());
        }
        setState();
    });
    textVendorName.addListener(swt.SWT.Verify, function(e) {
        e.text = String(e.text).toUpperCase();
    });
    addSelectAllListener(textVendorName);

    var lbl = widgets.Label(mviComp, swt.SWT.NONE);
    lbl.setText('Interface:');
    lbl.setToolTipText(wizard_constants.ENTER_INTERFACE_HOVER);
    var textInterfaceName = widgets.Text(mviComp, swt.SWT.BORDER);
    textInterfaceName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    textInterfaceName.addListener(swt.SWT.Modify, function(e) {
        setState();
    });
    textInterfaceName.addListener(swt.SWT.Verify, function(e) {
        e.text = String(e.text).toUpperCase();
    });
    addSelectAllListener(textInterfaceName);

    // Templates Drop-down ComboBox
    var lbl = new widgets.Label(col1Comp, swt.SWT.NONE);
    lbl.setText("Base Interface: ");
    lbl.setToolTipText(wizard_constants.ENTER_BASE_INTERFACE_HOVER);
    var templateComboBox = new widgets.Combo(col1Comp, swt.SWT.DROP_DOWN |
        swt.SWT.READ_ONLY);
    templateComboBox.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));

    function updateTemplatesCombo() {
        var tFile = java.io.File(codecPkgEnv.templatesDir);
        templateComboBox.removeAll();
        // save/try to restore previous
        for each (var f in tFile.listFiles()) {
            if (f.isDirectory() &&
                java.io.File(f.getCanonicalPath() + '/mkpkg.xdt').exists()) {
                templateComboBox.add(f.getName());
            }
        }
        if (templateComboBox.getItemCount()) {
            if (templateComboBox.indexOf(codecPkgEnv.input.templateName) == -1) {
                var index = templateComboBox.indexOf('IUNIVERSAL');
                if (index == -1) {
                    index = 0;
                }
                codecPkgEnv.input.templateName = String(templateComboBox.getItem(index));
            }
            templateComboBox.setText(codecPkgEnv.lib.templateName);
        }
    }

    var col2Comp = widgets.Composite(comp, swt.SWT.NONE);
    var col2Layout = layout.GridLayout();
    col2Layout.numColumns = 2;
    col2Comp.setLayout(col2Layout);
    var col2Data = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|layout.GridData.FILL_HORIZONTAL);
    col2Data.minimumWidth = 300;
    col2Data.widthHint = 300;
    col2Comp.setLayoutData(col2Data);

    var lbl = widgets.Label(col2Comp, swt.SWT.NONE);
    lbl.setText('Package Name:');
    lbl.setToolTipText(wizard_constants.ENTER_PACKAGE_NAME_HOVER);
    var textPackageName = widgets.Text(col2Comp, swt.SWT.BORDER);
    textPackageName.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    textPackageName.addListener(swt.SWT.Modify, function(e) {
        setState();
    });
    textPackageName.addListener(swt.SWT.Verify, function(e) {
        e.text = String(e.text).toLowerCase();
    });
    addSelectAllListener(textPackageName);

    // Targets table
    var lbl = new widgets.Label(col2Comp, swt.SWT.NONE );
    var lblData = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING);
    lblData.verticalIndent = 4;
    lbl.setLayoutData(lblData);
    lbl.setText("Targets: ");
    lbl.setToolTipText(wizard_constants.GENALG_TARGET);

    var targetTable = widgets.Table(col2Comp,
            swt.SWT.SINGLE|swt.SWT.CHECK|swt.SWT.BORDER|swt.SWT.V_SCROLL);
    var gridDataStretch = layout.GridData(layout.GridData.FILL_HORIZONTAL);
    gridDataStretch.verticalIndent = 8;
    gridDataStretch.heightHint = 35;
    targetTable.setLayoutData(gridDataStretch);
    targetTable.addListener(swt.SWT.Selection, function(e) {
        if (e.detail == swt.SWT.CHECK) {
            setState();
        }
    });

    targetTable.addListener(swt.SWT.MouseHover, function(e) {
        controlMouseOver(shell, targetTable, e);
    });
    targetTable.addListener(swt.SWT.Dispose, function(e){ mouseLeave(e); });
    targetTable.addListener(swt.SWT.KeyDown, function(e){ mouseLeave(e); });
    targetTable.addListener(swt.SWT.MouseMove, function(e){ mouseLeave(e); });

    /* TODO: handle INVALID TARGET! */
    /* populate and init target table */
    function populateTargetTable(targetsObj) {
        targetTable.removeAll();
        for (var i = 0; i < wizard_constants.targetList.length; i++) {
            var item = widgets.TableItem(targetTable, 0);
            item.setText(wizard_constants.targetDesc[i]);
            var invalidTarget = false;
            var invalidBase = false;
            try {
                var targ = wizard_constants.targetList[i];
                var tmod = xdc.useModule(targ);
                var base = String(tmod.$super.base);

                var data = {};
                data.target = wizard_constants.targetList[i];
                data.targname = tmod.name;
                data.targsuffix = tmod.suffix;
                data.ccOpts = wizard_constants.ccOpts[i];
                data.cgTools = wizard_constants.cgTools[i];
                data.hover = wizard_constants.targetList[i];
                item.setData(data);

                if (base.indexOf('xdc.bld.ITarget') == -1) {
                    invalidBase = true;
                }
            }
            catch (e) {
                invalidTarget = true;
            }
            if (targetsObj && !invalidTarget) {
                for (var j = 0; j < targetsObj.length; j++) {
                    if (targetsObj[j].target == wizard_constants.targetList[i]) {
                        item.setChecked(true);
                    }
                }
            }
        }
    }

    var iresCheck = widgets.Button(col2Comp, swt.SWT.CHECK);
    iresCheck.setText('Add IRES Interface');
    iresCheck.setToolTipText(wizard_constants.IRES_HOVER);

    var row2Comp = widgets.Composite(comp, swt.SWT.NONE);
    var row2Layout = layout.GridLayout();
    row2Layout.numColumns = 2;
    row2Comp.setLayout(row2Layout);
    var row2Data = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
    row2Data.horizontalSpan = 2;
    row2Comp.setLayoutData(row2Data);

    // Browse for output directory
    var output = new BrowseButton(row2Comp, shell, isWin ? 200 : 230);
    output.setMessage("Set Destination Directory");
    output.btn.setToolTipText(wizard_constants.OUTPUT_HOVER);
    output.addListener("", "Please enter a valid package directory", false);
    output.btn.addListener(swt.SWT.Selection, function(additionalEvent) {
    });
    output.textBox.addListener(swt.SWT.Modify, function(e) {
        setState();
    });

    var cgToolsGroup = createGroup(row2Comp, "'cgTools' Directories");
    var cgToolsGroupLayout = layout.GridLayout();
    cgToolsGroupLayout.numColumns = 2;
    cgToolsGroup.setLayout(cgToolsGroupLayout);
    var cgToolsGroupData = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
    cgToolsGroupData.horizontalSpan = 2;
    cgToolsGroupData.horizontalIndent = -5;
    cgToolsGroup.setLayoutData(cgToolsGroupData);


    var cgTabFolder = widgets.TabFolder(cgToolsGroup, swt.SWT.NONE);
    var dataF = layout.GridData(layout.GridData.FILL_HORIZONTAL);
    cgTabFolder.setLayoutData(dataF);

    var tiC6000 = createTabItem(cgTabFolder, "C6000");

    // Browse for C6000 cgtools dir
    var cgTools = new BrowseButton(tiC6000.comp, shell, 0, true);
    cgTools.setMessage("Set C6000 TI 'cgtools' Dir");
    cgTools.btn.setToolTipText(wizard_constants.CGTOOLS_DESC);
    cgTools.textBox.setToolTipText(wizard_constants.CGTOOLS_DESC);
    cgTools.addListener("", "Please enter a valid TI CodeGen tools directory", false);
    cgTools.btn.addListener(swt.SWT.Selection, function(additionalEvent) {
    });
    cgTools.textBox.addListener(swt.SWT.Modify, function(e) {
        setState();
    });
    tiC6000.item.setControl(tiC6000.comp);

    var tiV5T = createTabItem(cgTabFolder, "v5T");

    // Browse for Linux ARM cgtools dir
    var v5TcgTools = new BrowseButton(tiV5T.comp, shell, 0, true);
    v5TcgTools.setMessage("Set ARM v5T GCC Linux 'cgtools' Dir");
    v5TcgTools.btn.setToolTipText(wizard_constants.ARM_CGTOOLS_DESC);
    v5TcgTools.textBox.setToolTipText(wizard_constants.ARM_CGTOOLS_DESC);
    v5TcgTools.addListener("", "Please enter a valid ARM v5T GCC Linux CodeGen tools directory", false);
    v5TcgTools.btn.addListener(swt.SWT.Selection, function(additionalEvent) {
    });
    v5TcgTools.textBox.addListener(swt.SWT.Modify, function(e) {
        setState();
    });
    tiV5T.item.setControl(tiV5T.comp);

    var expertCheck = widgets.Button(comp, swt.SWT.CHECK);
    expertCheck.setText('Expert Mode');
    var expCheckData = new layout.GridData();
    expCheckData.horizontalIndent = 6;
    expertCheck.setLayoutData(expCheckData);
    expertCheck.setToolTipText(EXPERT_HOVER);
    expertCheck.addListener(swt.SWT.Selection, function(e) {
        codecPkgEnv.expertCheck = e.widget.getSelection() ? true : false;
        if (!codecPkgEnv.expertCheck) {
            textPackageName.setText(textVendorName.getText() + '.' +
                                    textModuleName.getText());
        }
        setState();
    });

    var CCSProjCheck = widgets.Button(comp, swt.SWT.CHECK);
    CCSProjCheck.setText('Generate CCSv4 project');
    var projCheckData = new layout.GridData(layout.GridData.HORIZONTAL_ALIGN_END);
    CCSProjCheck.setLayoutData(projCheckData);

    var rulesCheck = widgets.Button(comp, swt.SWT.CHECK);
    rulesCheck.setText("Don't check for build dependencies, I'll modify the generated makefile (e.g. Rules.make users)");
    var rulesCheckData = new layout.GridData();
    rulesCheckData.verticalIndent = 8;
    rulesCheckData.horizontalIndent = 6;
    rulesCheckData.horizontalSpan = 2;
    rulesCheck.setLayoutData(rulesCheckData);
    rulesCheck.addListener(swt.SWT.Selection, function(e) {
        codecPkgEnv.rulesCheck = e.widget.getSelection() ? true : false;
        setState();
    });

    if (!codecPkgEnv.xdcVersOK) {
        var msgComp = widgets.Composite(comp, swt.SWT.NONE);
        var msgLayout = layout.GridLayout();
        msgLayout.numColumns = 2;
        msgComp.setLayout(msgLayout);
        var compData = layout.GridData(layout.GridData.FILL_HORIZONTAL);
        compData.horizontalSpan = 2;
        msgComp.setLayoutData(compData);

        var imgLabel = widgets.Label(msgComp, swt.SWT.NONE);
        imgData = layout.GridData();
        imgData.widthHint = 15;
        imgLabel.setLayoutData(imgData);
        imgLabel.setImage(ICO_WARNING);

        var textBox = new widgets.Text(msgComp, swt.SWT.WRAP|swt.SWT.MULTI|
                                                swt.SWT.READ_ONLY);
        var gridHint = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
        textBox.setLayoutData(gridHint);
        textBox.setText(XDCVERS_MSG);
    }

    // Create menu bar with listeners
    var menuBar = createMenu(shell, 1);
    menuBar.getItem(0).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function() {
        var dialog = new widgets.DirectoryDialog(shell);
        dialog.setFilterPath(codecPkgEnv.templatesDir);
        var dir = dialog.open();
        if (dir != null) {
            codecPkgEnv.templatesDir = String(dir).replace(/\\/g,"/");
            updateTemplatesCombo();
            setState();
        }
    });
    menuBar.getItem(1).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function (enterInfoListener) {
        program.Program.launch(wizard_constants.ENTER_INFO_LINK);
    } );
    menuBar.getItem(1).getMenu().getItem(1).addListener(swt.SWT.Selection,
    function (faqListener) {
        program.Program.launch(wizard_constants.FAQ_LINK);
    } );


    function populatePanel() {
        if (codecPkgEnv.input.packageName != null) {
            textPackageName.setText(codecPkgEnv.input.packageName);
        }
        if (codecPkgEnv.input.vendorName != null) {
            textVendorName.setText(codecPkgEnv.input.vendorName);
        }
        if (codecPkgEnv.input.interfaceName != null) {
            textInterfaceName.setText(codecPkgEnv.input.interfaceName);
        }
        if (codecPkgEnv.input.moduleName != null) {
            textModuleName.setText(codecPkgEnv.input.moduleName);
        }
        if (codecPkgEnv.input.templateName != null) {
            templateComboBox.setText(codecPkgEnv.input.templateName);
        }
        populateTargetTable(codecPkgEnv.input.targets);
        if (codecPkgEnv.output != null && codecPkgEnv.output != "null") {
            output.textBox.setText(codecPkgEnv.output);
        }
        if (codecPkgEnv.cgTools != null) {
            cgTools.textBox.setText(codecPkgEnv.cgTools.replace(/\\/g,'/'));
        }
        if (codecPkgEnv.v5TcgTools != null) {
            v5TcgTools.textBox.setText(codecPkgEnv.v5TcgTools.replace(/\\/g,'/'));
        }
        iresCheck.setSelection((codecPkgEnv.input.ires == true) ? true : false);
        CCSProjCheck.setSelection((codecPkgEnv.genCCSProj == true) ? true : false);
        expertCheck.setSelection((codecPkgEnv.expertCheck == true) ? true : false);
        rulesCheck.setSelection((codecPkgEnv.rulesCheck == true) ? true : false);
        setState();
    }

    if (!codecPkgEnv.templatesDir.length) {
        codecPkgEnv.templatesDir = codecPkgEnv.xdaisInstall +
                                   '/packages/ti/xdais/dm/templates';
    }
    updateTemplatesCombo();
    populatePanel();

    function hasError() {
        return (errObj.label1.getImage() != null);
    }

    function setState() {
        textInterfaceName.setEditable(codecPkgEnv.expertCheck ? true : false);
        textPackageName.setEditable(codecPkgEnv.expertCheck ? true : false);
        var C6x = false;
        var v5T = false;
        for (var i = 0; i < targetTable.getItemCount(); i++) {
            if (targetTable.getItem(i).getChecked()) {
                if (!C6x && (wizard_constants.cgTools[i] == 'C64P' || wizard_constants.cgTools[i] == 'C674')) {
                    C6x = true;
                }
                else if (!v5T && wizard_constants.cgTools[i] == 'v5T') {
                    v5T = true;
                }
            }
            if (C6x && v5T) {
                break;
            }
        }
        cgTools.textBox.setEnabled(C6x);
        v5TcgTools.textBox.setEnabled(v5T);
        var valid = validateInput();
        buttons.nextEnabled = false;
        buttons.backEnabled = true;
        buttons.finishEnabled = valid;
        buttons.updated = true;
    }

    function validateInput() {
        var warnMsg = null;
        var msg;
        var valid = true;
        var validOutput = true;
        var validCgTools = true;
        var validv5TcgTools = true;

        if (String(textPackageName.getText()).length == 0 ||
            String(textModuleName.getText()).length == 0  ||
            String(textVendorName.getText()).length == 0  ||
            String(textInterfaceName.getText()).length == 0) {

            valid = false;
            msg = 'One or more empty fields';
        }
        else if (String(templateComboBox.getText()).length == 0) {
            valid = false;
            msg = 'No templates';
        }
        if (valid) {
            var checked = false;
            for (var i = 0; i < targetTable.getItemCount(); i++) {
                if (targetTable.getItem(i).getChecked()) {
                    checked = true;
                    break;
                }
            }
            if (!checked) {
                valid = false;
                msg = targMsg;
            }
        }
        if (valid) {
            var outdir = String(output.textBox.getText());
            if (!outdir.length || !java.io.File(outdir).isDirectory()) {
                valid = validOutput = false;
                msg = "Please enter a valid Destination Directory";
            }
            if (valid) {
                /* check for overwrite */
                outdir = outdir + '/' +
                         String(textPackageName.getText()).replace(/\./g,'/');
                outdir = outdir.replace(/\\/g, '/');
                var outf = java.io.File(outdir);
                if (outf.exists() && outf.list().length > 0) {
                    warnMsg = 'Destination Directory is not empty--files may be overwritten';
                }
            }
            if (!rulesCheck.getSelection()) {
                if (cgTools.textBox.getEnabled() &&
                    !logic.validCgToolsDir(cgTools.textBox.getText())) {

                    valid = validCgTools = false;
                    cgTabFolder.setSelection(0);
                }
                if (v5TcgTools.textBox.getEnabled() &&
                         !logic.validv5TcgToolsDir(v5TcgTools.textBox.getText())) {
                    valid = validv5TcgTools = false;
                    if (validCgTools) {
                        cgTabFolder.setSelection(1);
                    }
                }
            }
            if (!valid) {
                msg = "Please enter valid ";
                if (!validOutput) {
                    msg += 'Destination Directory';
                    if (!validCgTools && !validv5TcgTools) {
                        msg += ', ';
                    }
                    else if (!validCgTools || !validv5TcgTools) {
                        msg += ' and ';
                    }
                }
                if (!validCgTools) {
                    msg += "C6000 TI 'cgTools' Dir";
                    if (!validv5TcgTools) {
                        msg += ' and ';
                    }
                }
                if (!validv5TcgTools) {
                    msg += "ARM v5T GCC Linux 'cgTools' Dir";
                }
            }
        }
        if (!valid) {
            setImageLabel(errObj, ICO_ERROR, msg);
        }
        else if (warnMsg) {
            setImageLabel(errObj, ICO_WARNING, warnMsg);
        }
        else {
            setImageLabel(errObj, null, '');
        }
        return (valid);
    }

    function collectInput() {
        codecPkgEnv.input.packageName = String(textPackageName.getText());
        codecPkgEnv.input.moduleName = String(textModuleName.getText());
        codecPkgEnv.input.vendorName = String(textVendorName.getText());
        codecPkgEnv.input.interfaceName = String(textInterfaceName.getText());
        codecPkgEnv.input.templateName = String(templateComboBox.getText());
        codecPkgEnv.output = String(output.textBox.getText());
        codecPkgEnv.input.targets = [];
        for (var i = 0; i < targetTable.getItemCount(); i++) {
            if (targetTable.getItem(i).getChecked()) {
                codecPkgEnv.input.targets.push(targetTable.getItem(i).getData());
            }
        }
        if (cgTools.textBox.getEnabled()) {
            codecPkgEnv.cgTools = String(cgTools.textBox.getText());
        }
        if (v5TcgTools.textBox.getEnabled()) {
            codecPkgEnv.v5TcgTools = String(v5TcgTools.textBox.getText());
        }
        codecPkgEnv.input.ires = iresCheck.getSelection() ? true : false;
        codecPkgEnv.genCCSProj = CCSProjCheck.getSelection() ? true : false;
    }

    return {
        title:              "  Create an XDM Algorithm and Codec Package",
        composite:          comp,
        collectInputFxn:    collectInput
    };
}

function validateXdaisInstall(dir)
{
    dir = String(dir);
    if (!dir.length) {
        return (false);
    }
    var valid = true;
    var name = String(java.io.File(dir).getName());
    if (!java.io.File(dir + '/packages/ti/xdais/package.xdc').exists()) {
        valid = false;
    }
    if (valid) {
        if (!java.io.File(dir + '/packages/ti/xdais/wizards/genalg').exists()) {
            valid = false;
        }
    }
    if (valid) {
        if (!java.io.File(dir + '/packages/ti/xdais/dm/templates').exists()) {
            valid = false;
        }
    }
    return (valid);
}



/**
 * Creates the menu bar at the top of each panel
 * @param {Shell}
 * @param {String} Message to display when user clicks on Instructions
 * @return menuBar
 */
function createMenu(shell, pageNum)
{
    var menuBar = new widgets.Menu(shell, swt.SWT.BAR);
    shell.setMenuBar(menuBar);

    var instructionsText;
    if (pageNum == 0) {
/*
        var fileItem = new widgets.MenuItem(menuBar, swt.SWT.CASCADE);
        fileItem.setText ("&File");

        var fileSubmenu = new widgets.Menu(shell, swt.SWT.DROP_DOWN);
        fileItem.setMenu(fileSubmenu);

        var open = new widgets.MenuItem(fileSubmenu, swt.SWT.PUSH);
        open.setText("&Open");
        open.setAccelerator(swt.SWT.CTRL + 111); //111 is dec of o
*/
    }
    if (pageNum == 1) {
        var fileItem = new widgets.MenuItem(menuBar, swt.SWT.CASCADE);
        fileItem.setText ("&File");

        var fileSubmenu = new widgets.Menu(shell, swt.SWT.DROP_DOWN);
        fileItem.setMenu(fileSubmenu);

        if (pageFxns[1] == page1Fxn1 || pageFxns[1] == page1Fxn2) {
            var open = new widgets.MenuItem(fileSubmenu, swt.SWT.PUSH);
            open.setText("&Open");
            open.setAccelerator(swt.SWT.CTRL + 111); //111 is dec of o
        }
        if (pageFxns[1] == page1Fxn2 || pageFxns[1] == page1Fxn3) {
            if (pageFxns[1] == page1Fxn2) {
                new widgets.MenuItem(fileSubmenu, swt.SWT.SEPARATOR);
            }
            var templatesDir = new widgets.MenuItem(fileSubmenu, swt.SWT.PUSH);
            templatesDir.setText("Set &Templates Directory...");
            templatesDir.setAccelerator(swt.SWT.CTRL + 116); //116 is dec of t
        }
    }

    var helpItem = new widgets.MenuItem(menuBar, swt.SWT.CASCADE);
    helpItem.setText ("&Help");
    helpItem.setAccelerator(swt.SWT.CTRL + 104); //104 is dec of h

    var helpSubmenu = new widgets.Menu(shell, swt.SWT.DROP_DOWN);
    helpItem.setMenu(helpSubmenu);

    var faq;
    if (pageNum == 0) {
        var whatType = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
        whatType.setText("&What type of Codec package would you like to create?");
        whatType.setAccelerator(swt.SWT.CTRL + 98); // 119 is dec of w

        faq = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
        faq.setText("GenCodecPkg Wizard &FAQ");
        faq.setAccelerator(swt.SWT.CTRL + 102); //102 is dec of f
    }

    if (pageNum == 1) {
        if (pageFxns[1] == page1Fxn1) {
            var fromGenalg = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
            fromGenalg.setText("Create a Codec Package From a .&genalg File");
            fromGenalg.setAccelerator(swt.SWT.CTRL + 102); // 103 is dec of g
        }
        if (pageFxns[1] == page1Fxn2) {
            var fromLib = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
            fromLib.setText("Create a Codec Package From an XDM Algorithm &Library");
            fromLib.setAccelerator(swt.SWT.CTRL + 108); // 108 is dec of l
        }
        if (pageFxns[1] == page1Fxn3) {
            var fromLib = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
            fromLib.setText("&Create an XDM Algorithm and Codec Package");
            fromLib.setAccelerator(swt.SWT.CTRL + 99); // 99 is dec of c

        }

        faq = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
        faq.setText("GenCodecPkg Wizard &FAQ");
        faq.setAccelerator(swt.SWT.CTRL + 102); //102 is dec of f
    }

    new widgets.MenuItem(helpSubmenu, swt.SWT.SEPARATOR);
    var about = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
    about.setText("About");
    about.addListener(swt.SWT.Selection, function (aboutListener) {
        var msg = wizard_constants.ABOUT_MESSAGE + '\n\n' + csd;
        shared_gui.createMessageBox(msg, codecPkgEnv);
    });

    return menuBar;
}

/**
 * Generates a button that when selected creates a file dialog
 * @param {Composite}
 * @param {Shell}
 */
function BrowseButton(comp, shell, width, ellipsis) {

    this.comp = comp;
    this.shell = shell;

    var message = "";
    var errorMessage = "";
    var stringMatch = "";

    this.setMessage = function(message) {
        this.message = message;
        if (!this.ellipsis) {
            btn.setText(message);
        }
    }

    if (!ellipsis) {
        var btn = new widgets.Button(comp, swt.SWT.PUSH);
        var data = new layout.GridData();
        data.widthHint = width;
        btn.setLayoutData(data);
        this.btn = btn;
    }

    this.addListener = function(stringMatch, errorMessage, fileBool) {
        if (fileBool == true) {
            btn.addListener(swt.SWT.Selection, function(event) {
                var dialog = new widgets.FileDialog(shell);
                dialog.setFilterPath(textBox.getText());

                var file = dialog.open();
                if (file != null) {
                    file = String(file).replace(/\\/g,"/");
                    var suffix = file + "";
                    suffix = suffix.substring(
                        (suffix.lastIndexOf("/")+1), suffix.length);

                    if (suffix.match(stringMatch)!=null) {
                        textBox.setText(file);
                    }
                    else {
                        textBox.setText("");
                        shared_gui.createMessageBox(errorMessage, codecPkgEnv);
                    }

                }
            });
        }
        else {
            btn.addListener(swt.SWT.Selection, function(event) {
                var dialog = new widgets.DirectoryDialog(shell);
                var dfile = java.io.File(textBox.getText());
                if (dfile.exists()) {
                    dialog.setFilterPath(dfile.getCanonicalPath());
                }
                var dir = dialog.open();
                if (dir != null) {
                    dir = String(dir).replace(/\\/g,"/");
                   var suffix = dir;
                    suffix = suffix.substring(
                        (suffix.lastIndexOf("/")+1), suffix.length);

                    if (suffix.match(stringMatch)!=null) {
                        textBox.setText(dir);
                    }
                    else {
                        textBox.setText("");
                        shared_gui.createMessageBox(errorMessage, codecPkgEnv);
                    }
                }
            });
        }
    }

    var textBox = new widgets.Text(comp, swt.SWT.SINGLE |
                                         swt.SWT.BORDER);
    textBox.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    addSelectAllListener(textBox);
    this.textBox = textBox;
    if (ellipsis) {
        var btn = new widgets.Button(comp, swt.SWT.PUSH);
        btn.setText(' ... ');
        this.btn = btn;
    }
    this.ellipsis = ellipsis;
}

/**
* GUI to save current codecPkgEnv to user_specified_loc.xml
* @param {Shell}
* @param {codecPkgEnv}
* @return Boolean: true if save successful, false otherwise
*/
function saveXmlFile(shell, codecPkgEnv) {

}

/**
* GUI needed to read XML file
* @param image to be displayed on shell
* @param codecPkgEnv to be modified based on XML file
* @param shellLocation
* @return updated codecPkgEnv based on XML file
*/
function readXmlFile(shell, image, codecPkgEnv, openType)
{

    var dialog = new widgets.FileDialog(shell);
    dialog.setText(openType.title);
    dialog.setFilterExtensions(openType.filterExt);
    dialog.setFilterNames(openType.filterNames);
    var file = dialog.open();
    if (file != null) {
        try {
            codecPkgEnv = xmlOps.loadXml(file, codecPkgEnv);
            codecPkgEnv.genAlgFileLoaded = true;
        }
        catch(e) {
            var mbox = widgets.MessageBox(shell, swt.SWT.ICON_INFORMATION);
            mbox.setText("GenCodecPkg Wizard Message");
            mbox.setMessage("Error occured reading .genalg file: " + e);
            mbox.open();
        }
    }
    return codecPkgEnv;
}

function readLibFile(shell, image, codecPkgEnv)
{

    var dialog = new widgets.FileDialog(shell);
    dialog.setText('Open a library file');
    dialog.setFilterExtensions(libFilterExt);
    dialog.setFilterNames([]);
    codecPkgEnv.libFile = '';
    var file = dialog.open();
    if (file != null) {
        try {
            shell.setCursor(CUR_WAIT);
            var libInfo = libParser.getLibFileInfo(file, codecPkgEnv);
            var mvi = libParser.getMVI(file, codecPkgEnv);
            libFileLoaded = true;
            codecPkgEnv.libFile = String(file).replace(/\\/g, '/');
            codecPkgEnv.lib.moduleName = mvi.module;
            codecPkgEnv.lib.vendorName = mvi.vendor;
            codecPkgEnv.lib.interfaceName = mvi.inface;
            codecPkgEnv.lib.packageName = (mvi.vendor + '.' + mvi.module + '.ce').toLowerCase();
            codecPkgEnv.lib.arch = libInfo.arch;
            codecPkgEnv.lib.target = libInfo.target;
            codecPkgEnv.lib.targname = libInfo.targname;
            codecPkgEnv.lib.targsuffix = libInfo.targsuffix;
            codecPkgEnv.lib.format = libInfo.format;
            codecPkgEnv.lib.endian = libInfo.endian;
            shell.setCursor(null);
        }
        catch(e) {
            shell.setCursor(null);
            var mbox = widgets.MessageBox(shell, swt.SWT.ICON_INFORMATION);
            mbox.setText("GenCodecPkg Wizard Message");
            mbox.setMessage("Error occured reading library file: " + e);
            mbox.open();
            codecPkgEnv.libFile = '';
            codecPkgEnv.lib.moduleName = '';
            codecPkgEnv.lib.vendorName = '';
            codecPkgEnv.lib.interfaceName = '';
            codecPkgEnv.lib.arch = '';
            codecPkgEnv.lib.target = '';
            codecPkgEnv.lib.targname = '';
            codecPkgEnv.lib.targsuffix = '';
            codecPkgEnv.lib.format = '';
            codecPkgEnv.lib.endian = '';
        }
    }
    return codecPkgEnv;
}

function controlMouseOver(shell, control, e)
{
    var item =  control.getItem(graphics.Point(e.x, e.y));
    if (item != null  && item.getData() != null) {
        var infoStr = '';
        var idata = item.getData();
        if (idata.hover) {
            infoStr = String(idata.hover);
        }
        else {
            infoStr = String(item.getData());
            if (codecPkgEnv.reposMap[infoStr]) {
                infoStr += "\n in " + codecPkgEnv.reposMap[infoStr];
            }
        }
        itemHover(shell, control, item, infoStr, graphics.Point(e.x, e.y));
    }
}

function itemHover(shell, control, item, text, curPt)
{
    var pt;

    if (hoverTip != null  && !hoverTip.isDisposed()) {
        hoverTip.dispose();
    }
    hoverTip = widgets.Shell(shell, swt.SWT.ON_TOP|swt.SWT.NO_FOCUS|swt.SWT.TOOL);
    hoverTip.setBackground (display.getSystemColor (swt.SWT.COLOR_INFO_BACKGROUND));
    var lo = layout.FillLayout();
    lo.marginWidth = 2;
    hoverTip.setLayout(lo);
    hoverLabel = widgets.Label(hoverTip, swt.SWT.NONE);
    hoverLabel.setForeground(display.getSystemColor(swt.SWT.COLOR_INFO_FOREGROUND));
    hoverLabel.setBackground(display.getSystemColor(swt.SWT.COLOR_INFO_BACKGROUND));
    hoverLabel.setText(text);
    hoverLabel.addListener(swt.SWT.MouseExit, function(e) { mouseLeave(e); });
    hoverLabel.addListener(swt.SWT.MouseDown, function(e) { mouseLeave(e); });
    var size = hoverTip.computeSize(swt.SWT.DEFAULT, swt.SWT.DEFAULT);
    var rect = item.getBounds(0);
    if (curPt == undefined) {
        pt = control.toDisplay(rect.x, rect.y);
    }
    else {
        pt = control.toDisplay(curPt.x, curPt.y);
    }
    var monRect = display.getPrimaryMonitor().getClientArea();
    var left = (pt.x + size.x <= monRect.width) ? pt.x :
               pt.x - size.x;

    var top = (pt.y + rect.height + 4 + size.y <= monRect.height) ?
              pt.y + rect.height + 4 : pt.y - size.y - 4;
    if (top < 0) {
        top = 0;
    }
    hoverTip.setBounds(left, top, size.x, size.y);
    hoverTip.setVisible(true);
}

function mouseLeave(e)
{
    if (hoverTip != null) {
        hoverTip.dispose();
        hoverTip = null;
        hoverLabel = null;
    }
}

function navigatePages(parent)
{
    var currentPage = 0;

    while (true) {

        if (pageFxns[currentPage] == page1Fxn3) {
            if (isWin) {
                shellHeight = SHELL_HEIGHT + 80;
            }
            else {
                shellHeight = SHELL_HEIGHT + 125;
            }
        }
        else {
            shellHeight = SHELL_HEIGHT;
        }
        var shell = new widgets.Shell(display, swt.SWT.DIALOG_TRIM |
            swt.SWT.RESIZE | swt.SWT.MIN);
        shell.setImage(image);
        shell.setLayout(new layout.FormLayout());
        shell.setText("Codec Engine GenCodecPkg Wizard");
        shell.setMinimumSize(SHELL_WIDTH, shellHeight);
        shell.addListener(swt.SWT.Move, function(event) {
            try {
                codecPkgEnv.shellLocation = shell.getLocation();
            }
            catch(e) {}
        });
        codecPkgEnv.shell = shell;

        var compMain = new widgets.Composite(shell, swt.SWT.NONE);
        var layoutMain = new layout.GridLayout();
        layoutMain.numColumns = 2;
        layoutMain.horizontalSpacing = 15;
        compMain.setLayout(layoutMain);

        var labelTitle = new widgets.Label(compMain, swt.SWT.WRAP);
        var fillLabelTitle = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
        fillLabelTitle.horizontalSpan = 2;
        labelTitle.setLayoutData(fillLabelTitle);

        var space = new widgets.Label(compMain, swt.SWT.SEPARATOR |
            swt.SWT.HORIZONTAL);
        fillLabelTitle = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
        fillLabelTitle.horizontalSpan = 2;
        space.setLayoutData(fillLabelTitle);

        var pageData = pageFxns[ currentPage ](compMain);
        var point = pageData.composite.computeSize(swt.SWT.DEFAULT,
            swt.SWT.DEFAULT, false);
        labelTitle.setText(pageData.title);

        var formMain = new layout.FormData();
        formMain.top = new layout.FormAttachment(0, 10);
        formMain.left = new layout.FormAttachment(0, 10);
        formMain.right = new layout.FormAttachment(100, -10);
        compMain.setLayoutData(formMain);

        var compLine = new widgets.Composite(shell, swt.SWT.NONE);
        var layoutLine = new layout.RowLayout();
        layoutLine.pack = false;
        compLine.setLayout(layoutLine);
        var lbl = new widgets.Label(compLine, swt.SWT.SEPARATOR |
            swt.SWT.HORIZONTAL);
        lbl.setLayoutData(new layout.RowData(1000, swt.SWT.DEFAULT));

        var comp = new widgets.Composite(shell, swt.SWT.NONE);
        var lay = new layout.RowLayout();
        lay.pack = false;
        comp.setLayout(lay);

        var btnBack = new widgets.Button(comp, swt.SWT.PUSH);
        btnBack.setText("   < &Back   ");

        var btnNext = new widgets.Button(comp, swt.SWT.PUSH);
        btnNext.setText("    &Next >    ");

        var btnFinish = new widgets.Button(comp, swt.SWT.PUSH);
        btnFinish.setText("   &Finish   ");

        var btnCancel = new widgets.Button(comp, swt.SWT.PUSH);
        btnCancel.setText("   &Cancel   ");

        var formRow = new layout.FormData();
        formRow.left = new layout.FormAttachment(0, 50);
        formRow.bottom = new layout.FormAttachment(100, -10);
        formRow.right = new layout.FormAttachment(100, -10);
        comp.setLayoutData(formRow);

        var formLine = new layout.FormData();
        formLine.left = new layout.FormAttachment(0, 10);
        formLine.right = new layout.FormAttachment(100, -10);
        formLine.bottom = new layout.FormAttachment(comp, -5, swt.SWT.TOP);
        compLine.setLayoutData(formLine);

        btnBack.enabled   = buttons.backEnabled;
        btnNext.enabled   = buttons.nextEnabled;
        btnFinish.enabled = buttons.finishEnabled;

        var eventBack   = false;
        var eventNext   = false;
        var eventFinish = false;
        var eventCancel = false;

        btnCancel.addListener(swt.SWT.Selection, function(e) {
            eventCancel = true;
        });

        btnBack.addListener(swt.SWT.Selection, function(e) {
            eventBack = true;
        });

        btnNext.addListener(swt.SWT.Selection, function(e) {
            eventNext = true;
        });

        btnFinish.addListener(swt.SWT.Selection, function(e) {
            eventFinish = true;
        });

        var displayRect = display.getBounds();
        if (codecPkgEnv.shellLocation!=null) {
            shell.setLocation(codecPkgEnv.shellLocation);
        }

        shell.setSize(SHELL_WIDTH, shellHeight);
        shell.open();
        buttons.updated = false;

        shell.addListener(swt.SWT.Close, function(e) {
              pageData.collectInputFxn();
              var btnClicked = shared_gui.createYesNoBox(
                  "Do you want to quit?", codecPkgEnv);
              if (btnClicked == 1) {
                  print("Closing Codec Engine GenCodecPkg Wizard now...");
                  shell.dispose();
                  eventCancel = true;
              }
        });
        if (pageData.initFxn) {
            pageData.initFxn();
        }
        while(!shell.isDisposed()) {
            if (!display.readAndDispatch()) {
                java.lang.Thread.sleep(50);
                if (eventBack) {
                    pageData.collectInputFxn();
                    --currentPage;
                    break;
                }
                if (eventNext) {
                    pageData.collectInputFxn();
                    ++currentPage;
                    break;
                }
                if (eventFinish) {
                    pageData.collectInputFxn();
/*
                    var btnClicked = shared_gui.createYesNoBox(
                        "Would you like to save the values entered into "
                        + "the Codec Engine GenCodecPkg Wizard?", codecPkgEnv);
                    if (btnClicked == 1) {
                        var complete = saveXmlFile(shell, codecPkgEnv);
                        if (complete == true) {
                            shared_gui.createMessageBox("Save successful",
                                                        codecPkgEnv);
                        }
                    }
*/
                    break;
                }
                if (eventCancel) {
                    pageData.collectInputFxn();
                    var btnClicked = shared_gui.createYesNoBox(
                        "Do you want to quit?", codecPkgEnv);
                    if (btnClicked == 1) {
                        print("Closing Codec Engine GenCodecPkg Wizard now...");
                    }
                    else {
                        eventCancel = false;
                    }
                    break;
                }
                if (buttons.updated) {
                    buttons.updated   = false;
                    btnBack.enabled   = buttons.backEnabled;
                    btnNext.enabled   = buttons.nextEnabled;
                    btnFinish.enabled = buttons.finishEnabled;
                }
            }
            try {
                shellLocation = shell.getLocation();
            }
            catch(e) {}
        }
        if (!shell.isDisposed()) {
            shell.dispose();
        }
        if (eventFinish || eventCancel) {
            break;
        }
    }
    if (!parent) {
        display.dispose();
    }
    return (eventFinish == true ? FINISH_BTN : CANCEL_BTN);
}

function main(codecPkgEnv, parent) {
    print("\nStarting Codec Engine GenCodecPkg Wizard now...");
    print('Codec Engine GenCodecPkg Wizard user:\n'
          + 'You can ignore any warnings below about Mozilla this or that missing.');

    initSWT();

    init(codecPkgEnv, parent);


    this.codecPkgEnv = codecPkgEnv;

    var result = navigatePages(parent);


    if (result == FINISH_BTN) {
        codecPkgEnv.finish = true;
        codecPkgEnv.cancel = false;
    }
    else {
        codecPkgEnv.finish = false;
        codecPkgEnv.cancel = true;
    }
    return (codecPkgEnv);
}


function isPosNumber(text, zeroOK)
{
    var ret = false;

    text = String(text);
    if (text.length > 0) {
        if (!text.match(/\D/g)) {
            if ((zeroOK && Number(text) >= 0) ||
                Number(text) > 0) {

                ret = true;
            }
        }
    }
    return (ret);
}


/**
 * Creates a banner of instructions at the top of each panel
 * @param {Shell}
 * @param {String} Message to display at top of panel
 */
function InstructionBanner(comp) {
    var text = "";

    var textBox = new widgets.Text(comp, swt.SWT.WRAP
        |swt.SWT.MULTI|swt.SWT.BORDER|swt.SWT.READ_ONLY);
    var gridHint = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
    gridHint.horizontalSpan = 2;
    textBox.setLayoutData(gridHint);

    this.setText = function(text) {
        this.text = text;
        textBox.setText(text);
    }
}




function CustomBrowseButton(comp, shell, width, indent)
{
    this.comp = comp;
    this.shell = shell;

    var message = "";

    this.setMessage = function(message) {
        this.message = message;
        btn.setText(message);
    }

    var btn = new widgets.Button(comp, swt.SWT.PUSH);
    var data = new layout.GridData();
    data.widthHint = width;
    if (indent) {
        data.horizontalIndent = 10;
    }
    btn.setLayoutData(data);
    this.btn = btn;

    this.addListener = function(fileList) {
        btn.addListener(swt.SWT.Selection, function(event) {
            var dialog = new widgets.DirectoryDialog(shell);
            dialog.setFilterPath(textBox.getText());

            while (true) {
                var dir = dialog.open();
                if (dir != null) {
                    var notFoundList = [];
                    var dirList = java.io.File(dir).list();
                    for each (var src in fileList) {
                        var found = false;
                        for each (var dest in dirList) {
                            if (String(dest) == src) {
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            notFoundList.push(src);
                        }
                    }
                    if (notFoundList.length == 0) {
                        textBox.setText(dir);
                    }
                    else {
                        textBox.setText('');
                        var msg = 'Not found: ';
                        for each (var nf in notFoundList) {
                            msg += ' ' + nf;
                        }
                        shared_gui.createMessageBox(msg, codecPkgEnv);
                    }
                }
                else {
                    break;
                }
            }
        });
    }

    var textBox = new widgets.Text(comp, swt.SWT.SINGLE|swt.SWT.BORDER|
                                         swt.SWT.READ_ONLY);
    textBox.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    this.textBox = textBox;
}


function createImageLabel(comp, cols, span)
{
    var lblComp = widgets.Composite(comp, swt.SWT.NONE);
    var lblLayout = layout.GridLayout();
    lblLayout.numColumns = cols;
    lblComp.setLayout(lblLayout);
    var compData = layout.GridData(layout.GridData.FILL_HORIZONTAL);
    compData.horizontalSpan = span;
    lblComp.setLayoutData(compData);

    var label1 = widgets.Label(lblComp, swt.SWT.NONE);
    label1Data = layout.GridData();
    label1Data.widthHint = 15;
    label1Data.heightHint = 16;
    label1.setLayoutData(label1Data);
    label1.setImage(null);

    var label2 = widgets.Label(lblComp, swt.SWT.NONE);
    label2.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));

    var btn;
    if (cols == 3) {
        btn = widgets.Button(lblComp, swt.SWT.PUSH);
        btn.setText('...');
        btn.setVisible(false);
    }

    return {
        label1: label1,
        label2: label2,
        btn:   btn
    };
}

function setImageLabel(msgObj, img, msg)
{
    msgObj.label1.setImage(img);
    msgObj.label2.setText(msg);
}

function boldFont(label)
{
    var fData = label.getFont().getFontData()[0];
    fData.setStyle(swt.SWT.BOLD);
    label.setFont(graphics.Font(display, fData));
}

function selectAllListener(e)
{
    if (e.widget.getEditable()) {
        e.widget.setSelection(0, String(e.widget.getText()).length);
    }
}

function addSelectAllListener(text)
{
    text.addListener(swt.SWT.FocusIn, selectAllListener);
}

function createGroup(comp, text)
{
    var group = widgets.Group(comp, swt.SWT.SHADOW_NONE);
    group.setText(text);
    var layoutGroup = layout.GridLayout();
    layoutGroup.numColumns = 2;
    group.setLayout(layoutGroup);
    group.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    return (group);
}

function createTabItem(tabFolder, text)
{
    var item = widgets.TabItem(tabFolder, swt.SWT.NONE);
    item.setText(text);
    var comp = widgets.Composite(tabFolder, swt.SWT.NONE);
    comp.setBackground(display.getSystemColor(swt.SWT.COLOR_WIDGET_BACKGROUND));
    var itemLayout = new layout.GridLayout()
    itemLayout.numColumns = 2;
    comp.setLayout(itemLayout);
    var compData = layout.GridData(layout.GridData.FILL_BOTH);
    comp.setLayoutData(compData);
    return ({ item : item, comp : comp });
}
/*
 *  @(#) ti.sdo.ce.wizards.gencodecpkg; 1, 0, 0, 0,57; 12-2-2010 21:28:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

