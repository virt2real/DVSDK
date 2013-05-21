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
var serverEnv = null;
var SearchPath = xdc.loadCapsule('searchPath.xs');
SearchPath.setGui(this);
var xmlOps = xdc.loadCapsule("xmlOps.xs");
var wizard_constants = xdc.loadCapsule("wizard_constants.xs");
var fileModule = xdc.module('xdc.services.io.File');
var logic = xdc.loadCapsule("logic.xs");
var shared_gui = xdc.loadCapsule("shared_gui.xs");
xmlOps.setLogic(logic);
xmlOps.setWizard_constants(wizard_constants);
xmlOps.setShared_gui(shared_gui);
var os = String(java.lang.System.getProperty('os.name'));
var isWin = (os.match(/^Windows/i) != null);
var SHELL_WIDTH = isWin ? 540 : 700;
var SHELL_HEIGHT = isWin ? 530 : 600;
var OFF_CHIP_MAX = 0x400000;
var OFF_CHIP_MAX_STR = '4mb';
var nextVisited = false;
var useEDMA3Check;

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

function setServerEnv(se)
{
    serverEnv = se;
}

function createPartControl(parent)
{
    main(serverEnv, parent);
}

var buttons = {
    backEnabled:      false,
    nextEnabled:      false,
    finishEnabled:    false,
    updated:          false
}

var pageFxns = [page0Fxn, page1Fxn, page2Fxn];
var numberOfPages = pageFxns.length;

var platformList = [];
var hoverTip = null;
var hoverLabel = null;

var SEARCH_CODECS = "Click 'Refresh Codec List' to populate";
var NO_CODECS_YET = SEARCH_CODECS + ' the codecs list';
var NO_CODECS_FOUND = 'No codecs found on Search Path';
var PLEASE_SELECT_CODECS = 'No codecs selected. Please select one or more codecs to place in the Server';
var DEFAULT_STACKMEMID = '0';
var PRIORITY_PRE = 'Priority: Server.MINPRI+';
var NO_DATA_STR = "no data";
var GROUPID_MIN = 0;
var GROUPID_MAX = 19;
var ICO_ERROR;
var ICO_WARNING;
var SERVER_NAME = "Server Package Name: ";
var filterExt = ['*.svrwiz', '*.xml', '*.*'];
var filterNames = ['Genserver Files (*.svrwiz)', 'Xml Files (*.xml)', 'All Files (*.*)'];
var searchPerformed = false;
var PACKAGE_DIR = 'Server package will be in: '


var VIDEO_GROUPID = wizard_constants.VIDEO_GROUPID;
var IMAGING_GROUPID = wizard_constants.IMAGING_GROUPID;
var AUDIO_SPEECH_GROUPID = wizard_constants.AUDIO_SPEECH_GROUPID;

var defaultAlgsValsMap = {
    'ti.sdo.ce.audio.IAUDDEC'              : {groupId: AUDIO_SPEECH_GROUPID, priority: 3},
    'ti.sdo.ce.audio.IAUDENC'              : {groupId: AUDIO_SPEECH_GROUPID, priority: 3},
    'ti.sdo.ce.audio1.IAUDDEC1'            : {groupId: AUDIO_SPEECH_GROUPID, priority: 3},
    'ti.sdo.ce.audio1.IAUDENC1'            : {groupId: AUDIO_SPEECH_GROUPID, priority: 3},
    'ti.sdo.ce.image.IIMGDEC'              : {groupId: IMAGING_GROUPID, priority: 2},
    'ti.sdo.ce.image.IIMGENC'              : {groupId: IMAGING_GROUPID, priority: 2},
    'ti.sdo.ce.image1.IIMGDEC1'            : {groupId: IMAGING_GROUPID, priority: 2},
    'ti.sdo.ce.image1.IIMGENC1'            : {groupId: IMAGING_GROUPID, priority: 2},
    'ti.sdo.ce.speech.ISPHDEC'             : {groupId: AUDIO_SPEECH_GROUPID, priority: 3},
    'ti.sdo.ce.speech.ISPHENC'             : {groupId: AUDIO_SPEECH_GROUPID, priority: 3},
    'ti.sdo.ce.speech1.ISPHDEC1'           : {groupId: AUDIO_SPEECH_GROUPID, priority: 3},
    'ti.sdo.ce.speech1.ISPHENC1'           : {groupId: AUDIO_SPEECH_GROUPID, priority: 3},
    'ti.sdo.ce.video.IVIDDEC'              : {groupId: VIDEO_GROUPID, priority: 1},
    'ti.sdo.ce.video.IVIDENC'              : {groupId: VIDEO_GROUPID, priority: 1},
    'ti.sdo.ce.video1.IVIDDEC1'            : {groupId: VIDEO_GROUPID, priority: 1},
    'ti.sdo.ce.video1.IVIDENC1'            : {groupId: VIDEO_GROUPID, priority: 1},
    'ti.sdo.ce.video2.IVIDDEC2'            : {groupId: VIDEO_GROUPID, priority: 1},
    'ti.sdo.ce.video2.split.IVIDDEC2BACK'  : {groupId: VIDEO_GROUPID, priority: 1},
    'ti.sdo.ce.video2.split.IVIDDEC2FRONT' : {groupId: VIDEO_GROUPID, priority: 1},
    'ti.sdo.ce.IVIDANALYTICS'              : {groupId:             2, priority: 1},
    'ti.sdo.ce.IVIDTRANSCODE'              : {groupId:             2, priority: 1},
    'ti.sdo.ce.IUNIVERSAL'                 : {groupId:             2, priority: 1},
    'ti.sdo.ce.examples.extensions.scale.ISCALE' : {groupId:       2, priority: 1}
};



function init(serverEnv, parent)
{
    if (parent) {
        display = parent.getDisplay();
    }
    else {
        display = new widgets.Display();
    }
    serverEnv.display = display;
    image = new graphics.Image(display, csd + "/img/tray.JPG");
    ICO_ERROR = graphics.Image(display, csd + "/img/error_tsk.gif");
    ICO_WARNING = graphics.Image(display, csd + "/img/warning_obj.gif");

    var shellLocation = graphics.Point(66,87);

    serverEnv.shellLocation = shellLocation;
/*
    var shell = new widgets.Shell(display, swt.SWT.DIALOG_TRIM |
                                  swt.SWT.APPLICATION_MODAL);

    shell.setImage(image);
    shell.setSize(200, 100);
    shell.setText("Loading...");

    if (serverEnv.shellLocation!=null) {
        shell.setLocation(serverEnv.shellLocation);
    }

    var grid = new layout.GridLayout(1, false);
    shell.setLayout(grid);

    var comp = new widgets.Composite(shell, swt.SWT.NONE);
    comp.setLayout(new layout.GridLayout());

    var text = new widgets.Text(comp, swt.SWT.WRAP | swt.SWT.READ_ONLY);
    text.setText(wizard_constants.INIT_MESSAGE);
    text.setLayoutData(new layout.GridData( 180, 50 ));

    var pb = new widgets.ProgressBar(comp, swt.SWT.HORIZONTAL);
    pb.setMinimum(0);
    pb.setMaximum(100);
    pb.setBounds(10, 10, 200, 20);
    shell.pack();
    shell.open();

    pb.setSelection(30);
*/
    platformList = getPlatforms(serverEnv);
//    platformList.push('<custom>');
    if (platformList.length) {
        serverEnv.searchPathArr = SearchPath.getPackagePath();
        logic.checkForCeAndXdc(serverEnv.searchPathArr);

        if (!serverEnv.xmlFile) {
            serverEnv.algVals = [];
            serverEnv.cfgCodecs = [];

            var searchObj = {};;
            serverEnv.allCodecs = [];
            serverEnv.inheritsMap = [];
            serverEnv.reposMap = [];
            serverEnv.groups = new Array(GROUPID_MAX + 1);
        }
    }
/*
    pb.setSelection(50);
    pb.setSelection(80);
    pb.setSelection(100);
    shell.dispose();
*/
}

function getPlatforms(serverEnv) {

    var p = environment['xdc.path'].split(';');
    var path = [];
    for (i=0; i<p.length; i++) {
        path.push(p[i]);
    }

    var pkgNames = [];
    var qualNames = [];

    var plats = ['ti.platforms.evm3530', 'ti.platforms.evmDM6446',
                  'ti.platforms.evmDM6467','ti.platforms.evmOMAPL137',
                  'ti.platforms.evmOMAPL138'];


    for each (var pl in plats) {
        try {
            var base = xdc.getPackageBase(pl);
            pkgNames.push(pl);
        }
        catch (e) {
        }
    }

    if (!pkgNames.length) {
        shared_gui.createMessageBox(
              "No valid platforms found on the XDC Path.  " +
              "Valid platforms are:\n  ti.platforms.evmDM6446\n" +
              "  ti.platforms.emvDM6467\n  ti.platforms.evm3530\n" +
              "  ti.platforms.evmOMAPL137\n  ti.platforms.evmOMAPL138\n" +
              "Please modify your XDC Path and restart the " +
              "GUI Codec Engine GenServer Wizard", serverEnv);
    }
    return pkgNames;
}

function page0Fxn(comp)
{
    var msgArr = [];
    var shell = comp.getShell();

    var errObj = createImageLabel2(comp, 2, 2);
    errObj.label2.addListener(swt.SWT.Selection,function(e) {
        showErrors();
    });

    /* required user input: codec module name(s)
       optional user input: serverName, output, platform */

    // Platform Drop-down ComboBox
    var platformLabel = new widgets.Label( comp, swt.SWT.NONE );
    var data = new layout.GridData();
    data.widthHint = 100;
    platformLabel.setLayoutData(data);
    platformLabel.setText("Platform: ");
    var platformComboBox = new widgets.Combo( comp, swt.SWT.DROP_DOWN |
        swt.SWT.READ_ONLY );
    for (var i = 0; i < platformList.length; i++) {
        platformComboBox.add(platformList[i]);
    }
    serverEnv.platformSupportsEdma = true;
    var dataCombo = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
    platformComboBox.setLayoutData(dataCombo);

    platformComboBox.addListener(swt.SWT.Selection,function(e) {
        platformSelectionChanged();
    });

/*
    var custom = new CustomBrowseButton(comp, shell, 190, 10);
    custom.setMessage( "Select Custom Platform Directory" );
    custom.addListener(['server.tcf', 'config.bld']);
    custom.btn.setEnabled(false);
    custom.textBox.setEnabled(false);
    function platformSelectionChanged() {
        var enabled = platformComboBox.getSelectionIndex() ==
                      platformList.length - 1;
        custom.btn.setEnabled(enabled);
        custom.textBox.setEnabled(enabled);
    }
*/
    function platformSelectionChanged() {
        var selection = platformComboBox.getSelectionIndex();
        if (selection != -1) {
            serverEnv.platform = platformList[selection];
        }
        else {
            serverEnv.platform = '';
        }
        setState();
    }

    var textServerName = createTextBox(comp, SERVER_NAME, 200);
    textServerName.addListener(swt.SWT.Modify, function(e) {
        setState();
    });

    textServerName.addListener(swt.SWT.Verify, function(e) {
        e.text = String(e.text).toLowerCase();
    });


    // Browse for output directory
    var output = new BrowseButton(comp, shell, 200);
    output.setMessage("Destination Directory");
    output.addListener("", "Please enter a valid package repository", false);
    output.btn.addListener(swt.SWT.Selection, function(additionalEvent) {
        setState();
    } );
    output.textBox.addListener(swt.SWT.Modify, function(e) {
        var outDir = output.textBox.getText() + '/' +
                     String(textServerName.getText()).replace(/\./g,"/");
        output.btn.setToolTipText(PACKAGE_DIR + outDir.replace(/\\/g, '/'));
        output.textBox.setToolTipText(PACKAGE_DIR + outDir.replace(/\\/g, '/'));
        setState();
    });

    // Browse for cgtools dir
    var cgTools = new BrowseButton(comp, shell, 200, 7);
    cgTools.setMessage("Set C6000 TI 'cgtools' Dir");
    cgTools.addListener("", "Please enter a valid TI CodeGen tools directory", false);
    cgTools.btn.addListener(swt.SWT.Selection, function(additionalEvent) {
    });
    cgTools.btn.setToolTipText(wizard_constants.CGTOOLS_DESC);
    cgTools.textBox.setToolTipText(wizard_constants.CGTOOLS_DESC);
    cgTools.textBox.addListener(swt.SWT.Modify, function(e) {
        setState();
    });

    var btnSearchPath = widgets.Button(comp, swt.SWT.PUSH );
    btnSearchPath.setText("   Set Search Path...   ");
    btnSearchPath.setToolTipText(wizard_constants.SEARCH_PATH_DESC);
    gridData = layout.GridData();
    gridData.widthHint = 200;
    gridData.verticalIndent = 8;
    gridData.horizontalSpan = 2;
    btnSearchPath.setLayoutData(gridData);

    btnSearchPath.addListener(swt.SWT.Selection, function(e) {
        var newPath = SearchPath.modifyPackageRepositorySearchPath(serverEnv,
                      display, shell, serverEnv.searchPathArr);
        if (newPath != null) {
            serverEnv.searchPathArr = newPath;
        }
        logic.checkForCeAndXdc(serverEnv.searchPathArr);
        setState();
    });

    var labelComp = widgets.Composite(comp, swt.SWT.NONE);
    labelCompLayout = layout.GridLayout();
    labelCompLayout.marginWidth = 0;
    labelComp.setLayout(labelCompLayout);
    var gridData = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING |
                                   layout.GridData.HORIZONTAL_ALIGN_FILL);
    gridData.widthHint = 200;
    labelComp.setLayoutData(gridData);

    var tableLabel = widgets.Label(labelComp, swt.SWT.NONE);
    tableLabel.setText('Codec Modules: ');

    widgets.Label(labelComp, swt.SWT.NONE); /* dummy */

    var btnSearch = widgets.Button(labelComp, swt.SWT.PUSH );
    btnSearch.setText('Refresh Codec List');
    btnSearch.setToolTipText(wizard_constants.SEARCH_DESC);
    gridData = layout.GridData();
    gridData.horizontalIndent = 10;
    gridData.widthHint = 190;
    btnSearch.setLayoutData(gridData);
    btnSearch.addListener(swt.SWT.Selection, function(e) {
        if (!searchPerformed) {
            searchPerformed = true;
        }
        serverEnv.algVals = [];
        serverEnv.cfgCodecs = [];
        var searchObj = searchCodecs(shell, serverEnv.searchPathArr);
        serverEnv.allCodecs = searchObj.codecsArr;
        serverEnv.inheritsMap = searchObj.inheritsMap;
        serverEnv.reposMap = searchObj.reposMap;
        populateCodecsTable();
        setState();
    });

    var codecsTable = widgets.Table(comp,
            swt.SWT.SINGLE|swt.SWT.CHECK|swt.SWT.BORDER|swt.SWT.V_SCROLL);
    var gridDataStretch = layout.GridData(layout.GridData.FILL_HORIZONTAL);
    gridDataStretch.verticalIndent = 8;
    gridDataStretch.heightHint = 120;
    codecsTable.setLayoutData(gridDataStretch);
    codecsTable.addListener(swt.SWT.Selection, function(e) {
        if (e.detail == swt.SWT.CHECK) {
            setState();
        }
    });
    addHoverListener(shell, codecsTable, true);

    /* for when child controls are disabled */
    comp.addListener(swt.SWT.MouseHover, function(e) {
        var rect = enablePwrCheck.getBounds();
        if (rect.contains(e.x, e.y)) {
            e.x -= rect.x;
            e.y -= rect.y;
            controlMouseOver(shell, enablePwrCheck, e);
        }
    });
    comp.addListener(swt.SWT.Dispose, function(e){ mouseLeave(e); });
    comp.addListener(swt.SWT.KeyDown, function(e){ mouseLeave(e); });
    comp.addListener(swt.SWT.MouseMove, function(e){ mouseLeave(e); });

    var enablePwrCheck = widgets.Button(comp, swt.SWT.CHECK);
    enablePwrCheck.setText('Enable Power Management');
    enablePwrCheck.setData(wizard_constants.ENABLE_POWER_HOVER);
    addHoverListener(shell, enablePwrCheck);
    enablePwrCheck.addListener(swt.SWT.Selection, function(e) {
        serverEnv.enablePwr = e.widget.getSelection() ? true : false;
        setState();
    });

    var CCSProjCheck = widgets.Button(comp, swt.SWT.CHECK);
    CCSProjCheck.setText('Generate CCS Eclipse project');
    var projData = new layout.GridData(layout.GridData.HORIZONTAL_ALIGN_END);
    CCSProjCheck.setLayoutData(projData);

    var rulesCheck = widgets.Button(comp, swt.SWT.CHECK);
    rulesCheck.setText("Don't check for build dependencies, I'll modify the generated makefile (e.g. Rules.make users)");
    var rulesData = new layout.GridData();
    rulesData.horizontalSpan = 2;
    rulesCheck.setLayoutData(rulesData);
    rulesCheck.addListener(swt.SWT.Selection, function(e) {
        serverEnv.useRulesMake = e.widget.getSelection() ? true : false;
        setState();
    });

    // Create menu bar with listeners
    var menuBar = createMenu(shell, 0);
    menuBar.getItem(0).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function (openListener) {
        serverEnv = readXmlFile(shell, image, serverEnv);
        populatePanel();
    } );
    menuBar.getItem(0).getMenu().addListener(swt.SWT.Show, function(e) {
        menuBar.getItem(0).getMenu().getItem(1).setEnabled(validateInput() && nextVisited);
    } );
    menuBar.getItem(0).getMenu().getItem(1).addListener(swt.SWT.Selection,
    function(saveListener) {
        collectInput();
        var complete = saveXmlFile(shell, serverEnv);
        if (complete==true) {
            shared_gui.createMessageBox("Save successful", serverEnv);
        }
    } );

    menuBar.getItem(1).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function (basicListener) {
        program.Program.launch(wizard_constants.BASIC_INFO_LINK);
    } );
    menuBar.getItem(1).getMenu().getItem(1).addListener(swt.SWT.Selection,
    function (faqListener) {
        program.Program.launch(wizard_constants.FAQ_LINK);
    } );

    function populateCodecsTable() {
        codecsTable.removeAll();
        if (serverEnv.allCodecs && serverEnv.allCodecs.length > 0) {
            for (var i = 0; i < serverEnv.allCodecs.length; i++) {
                var item = widgets.TableItem(codecsTable, 0);
                item.setText (serverEnv.allCodecs[i].
                              substr(serverEnv.allCodecs[i].lastIndexOf('.') + 1));
                item.setData(serverEnv.allCodecs[i]);
                if (serverEnv.cfgCodecs) {
                    for (var j = 0; j < serverEnv.cfgCodecs.length; j++) {
                        if (serverEnv.cfgCodecs[j] == serverEnv.allCodecs[i]) {
                            item.setChecked(true);
                        }
                    }
                }
            }
        }
        else {
            var item = widgets.TableItem(codecsTable, 0);
            if (!searchPerformed) {
                item.setText(SEARCH_CODECS);
            }
            else {
                item.setText(NO_CODECS_FOUND);
            }
        }
    }

    function populatePanel() {
        if (serverEnv.serverName != null) {
            textServerName.setText(serverEnv.serverName);
        }
        if (serverEnv.platform != null) {
            platformComboBox.setText(serverEnv.platform);
        }
        if (serverEnv.output != null && serverEnv.output != "null") {
            output.textBox.setText(serverEnv.output.replace(/\\/g,'/'));
        }
        if (serverEnv.cgTools != null) {
            cgTools.textBox.setText(serverEnv.cgTools.replace(/\\/g,'/'));
        }
        populateCodecsTable();
        CCSProjCheck.setSelection((serverEnv.genCCSProj == true) ? true : false);
        rulesCheck.setSelection((serverEnv.useRulesMake == true) ? true : false);
        enablePwrCheck.setSelection((serverEnv.enablePwr == true) ? true : false);
        setState();
    }

    populatePanel();

    function setState() {
        var valid = validateInput();
        enablePwrCheck.setEnabled(logic.platformSupportsPwrManagment(serverEnv.platform));
        buttons.nextEnabled = valid;
        buttons.backEnabled = false;
        buttons.finishEnabled = false;
        buttons.updated = true;
    }

    function validateInput() {

        msgArr = [];
        var notFoundArr = [];
        var warnMsg = null;
        var validOutput = true;
        var validCodecs = true;
        if (String(textServerName.getText()).length == 0 ||
            String(output.textBox.getText()).length == 0  ||
            String(cgTools.textBox.getText()).length == 0) {

            msgArr.push('One or more empty fields');
        }

        if (!java.io.File(output.textBox.getText()).isDirectory()) {
            msgArr.push('Invalid Destination Directory');
            validOutput = false;
        }
        if (!serverEnv.useRulesMake && 
            !logic.validCgToolsDir(cgTools.textBox.getText())) {

            msgArr.push("Invalid C6000 TI 'cgTools' Dir");
        }
        if (validOutput) {
            /* check for overwrite */
            var outDir = output.textBox.getText() + '/' +
                         String(textServerName.getText()).replace(/\./g,"/");
            outDir = outDir.replace(/\\/g, '/');
            var outf = java.io.File(outDir);
            if (outf.exists() && outf.list().length > 0) {
                warnMsg = 'Destination Directory is not empty -- files may be overwritten';
            }
        }
        var count = codecsTable.getItemCount();
        if (count == 1) {
            var txt = String(codecsTable.getItem(0).getText());
            if (txt == NO_CODECS_FOUND) {
                msgArr.push("No codecs found on Search Path. Modify the Search Path and 'Refresh Codec List'");
                validCodecs = false;
            }
            else if (txt == SEARCH_CODECS) {
                msgArr.push("Codec Modules list has not been populated yet. Click 'Refresh Codec List' to populate it");
                validCodecs = false;
            }
        }
        if (validCodecs) {
            var checked = false;
            for (var i = 0; i < codecsTable.getItemCount(); i++) {
                if (codecsTable.getItem(i).getChecked()) {
                    checked = true;
                    break;
                }
            }
            if (!checked) {
                msgArr.push(PLEASE_SELECT_CODECS);
            }
        }

        if (!serverEnv.useRulesMake) {
            notFoundArr = logic.checkForRequiredInstallDirs(serverEnv,
                                                                serverEnv.searchPathArr);
            if (notFoundArr.length > 1) {
                var str = 'The following install directories are required in the Search Path:';
                for each (var dir in notFoundArr) {
                    str += '\n       ' + dir;
                }
                msgArr.push(str)
            }
            else if (notFoundArr.length == 1) {
                msgArr.push(notFoundArr[0] + ' ' + 'install directory required in Search Path');
            }
        }
        if (msgArr.length > 0) {
            if (msgArr.length == 1 && notFoundArr.length <= 1 && !warnMsg) {
                setImageLabel2(errObj, ICO_ERROR, msgArr[0]);
            }
            else {
                var numErrors = msgArr.length;
                for (var i = 0; i < msgArr.length; i++) {
                    msgArr[i] = '  *' + msgArr[i];
                }
                var estr = 'Error';
                var emsg = numErrors + ' error';
                if (msgArr.length > 1) {
                    emsg += 's';
                    estr += 's';
                }
                msgArr.unshift(estr + ':');
                if (warnMsg) {
                    emsg += ' and 1 warning';
                    msgArr.push('\nWarning:');
                    msgArr.push('  *' + warnMsg);
                }
                setImageLabel2(errObj, ICO_ERROR, emsg, true);
            }
        }
        else if (warnMsg) {
            setImageLabel2(errObj, ICO_WARNING, warnMsg);
        }
        else {
            setImageLabel2(errObj, null, '');
        }
        return (msgArr.length == 0);
    }

    function collectInput() {
        serverEnv.serverName = "" + textServerName.getText();

        var selection = platformComboBox.getSelectionIndex();
        if (selection != -1) {
            serverEnv.platform = platformList[selection];
        }
        serverEnv.output = "" + output.textBox.getText();

        serverEnv.cfgCodecs = [];
        for (var i = 0; i < codecsTable.getItemCount(); i++) {
            if (codecsTable.getItem(i).getChecked()) {
                serverEnv.cfgCodecs.push(
                        String(codecsTable.getItem(i).getData()));
            }
        }
        serverEnv.cgTools = String(cgTools.textBox.getText());
        serverEnv.genCCSProj = CCSProjCheck.getSelection() ? true : false;
        if (enablePwrCheck.getEnabled()) {
            serverEnv.enablePwr = enablePwrCheck.getSelection() ? true : false;
        }
        else {
            serverEnv.enablePwr = false;
        }
    }

    function showErrors() {
        errorsList(shell, 'Errors/Warnings', msgArr);
    }

    return {
        title:              "Basic Server Information",
        composite:          comp,
        collectInputFxn:    collectInput
    };
}


function page1Fxn(comp)
{
    var codecsInput;
    var groupsInput;

    var shell = comp.getShell();
    var errObj = createImageLabel2(comp, 3, 2);
    var dirBtn = new widgets.Button(errObj.lblComp, swt.SWT.PUSH);
    dirBtn.setText(' ... ');
    dirBtn.setVisible(false);
    dirBtn.addListener(swt.SWT.Selection, function(e) {
        var dlg = widgets.DirectoryDialog(shell);
        dlg.setText('EDMALLD Install Directory');
        dlg.setMessage('Select EDMALLD Install Directory');
        while (true) {
            var dir = dlg.open();
            if (dir != null) {
                dir = logic.findEdmaLld([dir]);
                if (dir) {
                    serverEnv.edmaLldInstall = dir;
                    serverEnv.searchPathArr.unshift(dir + '/packages');
                    flagError(groupsTree.getSelection()[0], !validateInput());
                    break;
                }
                else {
                    shared_gui.createMessageBox("Invalid EDMALLD Install Directory",
                                                serverEnv );
                }
            }
            else {
                break;
            }
        }
    });

    var curSel = null;

    var outerGroups = widgets.Group(comp, swt.SWT.SHADOW_NONE);
    outerGroups.setText('Codecs');
    var layoutOuter = layout.GridLayout();
    outerGroups.setLayout(layoutOuter);
    var outerData = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|
                          layout.GridData.FILL_HORIZONTAL);
    outerData.heightHint = 340;
    outerGroups.setLayoutData(outerData);

    var grGroups = widgets.Composite(outerGroups, swt.SWT.NONE);
    var layoutGroups = layout.GridLayout();
    layoutGroups.numColumns = 2;
    grGroups.setLayout(layoutGroups);
    var grData = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|
                          layout.GridData.FILL_HORIZONTAL);
    grGroups.setLayoutData(grData);

    var compCol1 = widgets.Composite(grGroups, swt.SWT.NONE);
    var layoutcompCol1 = layout.GridLayout();
    layoutcompCol1.numColumns = 1;
    compCol1.setLayout(layoutcompCol1);
    var compCol1Data = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|
                                    layout.GridData.FILL_BOTH);
    compCol1.setLayoutData(compCol1Data);

    var groupsTree = widgets.Tree(compCol1, swt.SWT.SINGLE|swt.SWT.BORDER);
    var treeData = layout.GridData(
                 layout.GridData.VERTICAL_ALIGN_BEGINNING);
    treeData.widthHint = isWin ? 170 : 200;
    treeData.heightHint = 200;
    groupsTree.setLayoutData(treeData);

    groupsTree.addListener(swt.SWT.Selection, function(e) {
        var newSel = e.widget.getSelection()[0];
        if (curSel != newSel) {
            if (curSel && curSel.isDisposed()) {
                curSel = null;
            }
            var curSelIsGroup = curSel && curSel.getParentItem() == null;
            var curSelIsCodec = curSel && curSel.getParentItem() != null;
            var newSelIsGroup = newSel && newSel.getParentItem() == null;
            var newSelIsCodec = newSel && newSel.getParentItem() != null;

            if (curSelIsGroup) {
                if (newSelIsCodec) {
                    switchInputs(curSel);
                    enableInputs(true);
                    initInputs(newSel);
                }
                else if (newSelIsGroup) {
                    getInput(curSel);
                    enableInputs(true);
                    initInputs(newSel);
                }
                else if (!newSel) {
                    enableInputs(false);
                }
            }
            else if (curSelIsCodec) {
                if (newSelIsGroup) {
                    switchInputs(curSel);
                    enableInputs(true);
                    initInputs(newSel);
                }
                else if (newSelIsCodec) {
                    getInput(curSel);
                    initInputs(newSel);
                }
                else if (!newSel) {
                    enableInputs(false);
                }
            }
            else if (!curSel) {
                if (newSelIsGroup) {
                    if (inputIsCodecs()) {
                        switchInputs(curSel);
                    }
                    enableInputs(true);
                    initInputs(newSel);
                }
                else if (newSelIsCodec) {
                    if (inputIsGroups()) {
                        switchInputs(curSel);
                    }
                    enableInputs(true);
                    initInputs(newSel);
                }
            }
            curSel = newSel;
        }
    });

    addHoverListener(shell, groupsTree, true);
    groupsTree.addListener(swt.SWT.MouseDown, function(e) {
        mouseLeave(e);
        if (e.button == 3) { /* right button */
            var menu = groupsTree.getMenu();
            if (menu != null) { /* delete previous items, if any */
                var items = menu.getItems();
                for (var i = 0; i < items.length; i++) {
                    items[i].dispose();
                }
            }
            var ti =  groupsTree.getItem(graphics.Point(e.x, e.y));
            if (ti == null) {
                menu = widgets.Menu(groupsTree);
                groupsTree.setMenu(menu);
                menu.setVisible(true);
                var groupsItem = widgets.MenuItem(menu, swt.SWT.NULL);
                groupsItem.setText('&New group...');
                if (groupsTree.getItemCount() == GROUPID_MAX + 1) {
                    groupsItem.setEnabled(false);
                }
                groupsItem.addListener(swt.SWT.Selection, function(e){
                    var newId = getUnusedGroupId();
                    var newItem = widgets.TreeItem(groupsTree, swt.SWT.NULL);
                    newItem.setText('Group ' + newId);
                    groupsTree.showItem(newItem);
                    var selId = selectGroupIdDlg(shell, newItem, newId, true);
                    if (selId != -1 && selId != newId) {
                        newItem.setText('Group ' + selId);
                        //* now sort!!
                    }
                });
            }
            else {
                menu = widgets.Menu(groupsTree);
                groupsTree.setMenu(menu);
                menu.setVisible(true);
                if (ti.getParentItem() != null) { /* clicked on a codec */
                    var groupsItem = widgets.MenuItem(menu, swt.SWT.NULL);
                    groupsItem.setText('&Move to group...');
                    groupsItem.addListener(swt.SWT.Selection, function(e){
                        var id = selectGroupIdDlg(shell, ti, 0, false);
                        if (id != -1) {
                            var curId = getIdNum(ti);
                            if (id != curId) {
                                var text = ti.getText();
                                var data = ti.getData();
                                ti.dispose();
                                var destItem = getGroupItemFromId(id);
                                if (destItem == null) { /* doesn't exist, create it */
                                    destItem = widgets.TreeItem(groupsTree, swt.SWT.NULL);
                                    destItem.setText('Group ' + id);

                                }
                                var newTi = widgets.TreeItem(destItem, swt.SWT.NULL);
                                newTi.setText (text);
                                newTi.setData(data);
                                groupsTree.setSelection(newTi);
                            }
                        }
                    });
                }
                else {
                    var groupsItem = widgets.MenuItem(menu, swt.SWT.NULL);
                    groupsItem.setText('&Change groupId...');
                    if (groupsTree.getItemCount() == GROUPID_MAX + 1) {
                        groupsItem.setEnabled(false);
                    }
                    groupsItem.addListener(swt.SWT.Selection, function(e){
                        var curId = getIdNum(ti);
                        var newId = selectGroupIdDlg(shell, ti, curId, true);
                        if (newId != -1 && newId != curId) {
                            ti.setText('Group ' + newId);
                            //* now sort!!
                            if (serverEnv.groups[curId]) {
                                serverEnv.groups[newId] = serverEnv.groups[curId];
                                serverEnv.groups[curId] = null;
                            }
                        }
                    });
                    if (ti.getItemCount() == 0) {
                        var groupsItem = widgets.MenuItem(menu, swt.SWT.NULL);
                        groupsItem.setText('&Delete group...');
                        groupsItem.addListener(swt.SWT.Selection, function(e){
                            ti.dispose();
                        });
                    }
                }
            }
        }

    });

    var sysGroup = widgets.Group(outerGroups, swt.SWT.SHADOW_NONE);
    sysGroup.setText('System DMA settings');
    var sysLayout = layout.GridLayout();
    sysGroup.setLayout(sysLayout);
    var sysGroupData = layout.GridData();

    sysGroupData.horizontalIndent = 8;
    sysGroupData.verticalIndent = 10;
    sysGroupData.widthHint = isWin ? 275 : 360;
    sysGroupData.heightHint = 35;
    sysGroup.setLayoutData(sysGroupData);

    /* for when child controls are disabled */
    sysGroup.addListener(swt.SWT.MouseHover, function(e) {
        var rect = useEDMA3Check.getBounds();
        if (rect.contains(e.x, e.y)) {
            e.x -= rect.x;
            e.y -= rect.y;
            controlMouseOver(shell, useEDMA3Check, e);
        }
    });
    sysGroup.addListener(swt.SWT.Dispose, function(e){ mouseLeave(e); });
    sysGroup.addListener(swt.SWT.KeyDown, function(e){ mouseLeave(e); });
    sysGroup.addListener(swt.SWT.MouseMove, function(e){ mouseLeave(e); });

    useEDMA3Check = widgets.Button(sysGroup, swt.SWT.CHECK);
    useEDMA3Check.setText('Use EDMA3 LLD to manage all EDMA3 resources');
    var useEDMA3CheckData = layout.GridData();
    useEDMA3CheckData.verticalIndent = 5;
    useEDMA3CheckData.horizontalIndent = 8;
    useEDMA3Check.setLayoutData(useEDMA3CheckData);
    useEDMA3Check.setData(wizard_constants.USE_EDMA3_HOVER);
    useEDMA3Check.addListener(swt.SWT.Selection, function(e) {
        serverEnv.useDMAN3 = e.widget.getSelection() ? false : true;
        if (inputIsGroups()) {
            groupsInput.enableInputs(true);
        }
        flagError(groupsTree.getSelection()[0], !validateInput());
    });
    addHoverListener(shell, useEDMA3Check);

    codecsInput = new codecsInputComposite(grGroups, groupsTree, flagError);

    // hack to prevent hang in CCS on addListener calls
    if (serverEnv.tid == serverEnv.guiId) {
        initCodecDragSource(groupsTree, getInput);
        initCodecDropTarget(groupsTree);
    }

    // Create menu bar with listeners
    var menuBar = createMenu(shell, 1);
    menuBar.getItem(0).getMenu().addListener(swt.SWT.Show, function(e) {
        menuBar.getItem(0).getMenu().getItem(0).setEnabled(!hasInputErrors());
    } );
    menuBar.getItem(0).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function(saveListener) {
        collectInput();

        var complete = saveXmlFile( shell, serverEnv );
        if (complete==true) {
            shared_gui.createMessageBox( "Save successful", serverEnv);
        }
    } );

    menuBar.getItem(1).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function (algvalsListener) {
        program.Program.launch(wizard_constants.ALG_VALS_LINK);
    } );
    menuBar.getItem(1).getMenu().getItem(1).addListener(swt.SWT.Selection,
    function (groupidListener) {
        program.Program.launch(wizard_constants.GROUP_IDS_LINK);
    } );
    menuBar.getItem(1).getMenu().getItem(2).addListener(swt.SWT.Selection,
    function (dskt2Listener) {
        program.Program.launch(wizard_constants.DSKT2_MEM_LINK);
    } );
    menuBar.getItem(1).getMenu().getItem(3).addListener(swt.SWT.Selection,
    function (faqListener) {
        program.Program.launch(wizard_constants.FAQ_LINK);
    } );

    function populatePanel() {
        groupsTree.removeAll();
        var i;

        /* sort by increasing id, then build tree */
        var codecs = [];  /* holds cfgCodecs indexes */
        var groupIds = []; /* holds only the groupIds used */
        for (i = 0; i < serverEnv.cfgCodecs.length; i++) {
            var qn = serverEnv.cfgCodecs[i];
            if (serverEnv.algVals[qn]) {
                curId = serverEnv.algVals[qn].groupId;
            }
            else {
                curId = defaultGroupId(qn);
            }
            if (!codecs[curId]) {
                codecs[curId] = [];
                groupIds.push(Number(curId));
            }
            codecs[curId].push(i);
        }
        groupIds = groupIds.sort();

        for (i = 0; i < groupIds.length; i++) {
            var strId = String(groupIds[i]);
            var tiGroup = widgets.TreeItem(groupsTree, swt.SWT.NULL);
            tiGroup.setText('Group ' + strId);
            for each (var j in codecs[strId]) {
                var ti = widgets.TreeItem(tiGroup, swt.SWT.NULL);
                var pStr = serverEnv.cfgCodecs[j];
                ti.setText (pStr.substr(pStr.lastIndexOf('.') + 1));
                ti.setData(pStr);
            }
        }

        for (i = 0; i < groupsTree.getItemCount(); i++) {
            groupsTree.getItem(i).setExpanded(true);
        }
        var selItem = groupsTree.getItem(0).getItem(0);
        groupsTree.setSelection(selItem);
        curSel = selItem;
        initInputs(selItem);
        serverEnv = logic.getConfigsFromModules(serverEnv);
        useEDMA3Check.setSelection(serverEnv.useDMAN3 ? false : true);
        enableUseEDMA3Check(true);
        flagError(selItem, !validateInput());
    }

    populatePanel();

    function setState() {
        var pathError = false;
        var error = hasInputErrors();
        if (!error) {
            pathError = errObj.label1.getImage() != null;
        }
        buttons.nextEnabled = (error == false && pathError == false);
        buttons.backEnabled = (error == false);
        buttons.finishEnabled = (error == false && pathError == false);
        buttons.updated = true;
    }

    function hasInputErrors() {
        var has = false;
        for each (var item in groupsTree.getItems()) {
            if (item.getImage() != null) {
                has = true;
                break;
            }
        }
        return (has);
    }

    function validateInput() {
        if (inputIsCodecs()) {
            return (codecsInput.validateInput());
        }
        else if (inputIsGroups()) {
            return (groupsInput.validateInput());
        }
    }

    function enableInputs(enable) {
        enableUseEDMA3Check(enable);
        if (inputIsCodecs()) {
            codecsInput.enableInputs(enable);
        }
        else if (inputIsGroups()) {
            groupsInput.enableInputs(enable);
        }
    }

    function enableUseEDMA3Check(enable) {
        useEDMA3Check.setEnabled(!enable ? false :
            serverEnv.idma3Fxns != null && serverEnv.iresFxns == null);
    }

    function initInputs(newSel) {
        if (inputIsCodecs()) {
            codecsInput.initInputs(newSel);
        }
        else if (inputIsGroups()) {
            groupsInput.initInputs(newSel);
        }
    }

    function getInput(selItem) {
        if (inputIsCodecs()) {
            codecsInput.getInput(selItem);
        }
        else if (inputIsGroups()) {
            groupsInput.getInput(selItem);
        }
    }

    function switchInputs(selItem) {
        getInput(selItem);
        if (inputIsGroups()) {
            groupsInput.compMain.dispose();
            groupsInput = null;
            codecsInput = new codecsInputComposite(grGroups, groupsTree, flagError);
            grGroups.layout(true);
        }
        else if (inputIsCodecs()) {
            codecsInput.compMain.dispose();
            codecsInput = null;
            groupsInput = new groupsInputComposite(shell, grGroups, groupsTree, flagError);
            grGroups.layout(true);
        }
    }


    function flagError(selItem, hasError) {
        var msg;
        var hasEdmaError = false;
        var parItem = selItem.getParentItem();
        if (parItem == null) {
            parItem = selItem;
            var isGroup = true;
        }
        else {
            selItem.setImage(0, hasError ? ICO_ERROR : null);
            var isGroup = false;
        }
        if (!hasError) {
            if (parItem.getItemCount() > 1) {
                for each (var item in parItem.getItems()) {
                    if (item != selItem && item.getImage() != null) {
                        hasError = true;
                        break;
                    }
                }
            }
        }
        if (!isGroup && !hasError) {
            hasError = !validGroup(parItem);
        }
        parItem.setImage(0, hasError ? ICO_ERROR : null);
        setState();

        if (!hasError) {
            for each (var grItem in groupsTree.getItems()) {
                if (grItem.getImage() != null) {
                    hasError = true;
                    break;
                }
            }
        }
        if (hasError) {
            msg = 'Invalid value entered, select/expand flagged item to view';
        }
        else {
            /* check emda3 lld */
            if (!serverEnv.useDMAN3 && !serverEnv.useRulesMake) {
                var edmaLldFound = (serverEnv.edmaLldInstall || serverEnv.cetoolsInstall) ?
                                   true : logic.findEdmaLld(serverEnv.searchPathArr);
                if (!edmaLldFound) {
                    hasEdmaError = true;
                    msg = 'EDMA3 LLD or cetools install directory required to build your Server. Please select';
                }
            }
        }
        if (hasError || hasEdmaError) {
            setImageLabel2(errObj, ICO_ERROR, msg);
            if (hasEdmaError) {
                dirBtn.setVisible(true);
            }
            else {
                dirBtn.setVisible(false);
            }
        }
        else {
            setImageLabel2(errObj, null, '');
            dirBtn.setVisible(false);
        }
    }

    function collectInput() {

        if (inputIsCodecs()) {
            codecsInput.collectInput();
            verifyGroups(groupsTree);
        }
        else if (inputIsGroups()) {
            groupsInput.collectInput();
            verifyAlgVals(groupsTree);
        }
    }

    function defaultGroupId(qn) {
        var groupId = 2;
        if (serverEnv.inheritsMap[qn]) {
            for each (var inface in serverEnv.inheritsMap[qn]) {
                if (defaultAlgsValsMap[inface]) {
                    groupId = defaultAlgsValsMap[inface].groupId;
                    break;
                }
            }
        }
        return (groupId);
    }

    function inputIsCodecs() {
        return (codecsInput && !codecsInput.compMain.isDisposed());
    }

    function inputIsGroups() {
        return (groupsInput && !groupsInput.compMain.isDisposed());
    }

    function getUnusedGroupId() {

        var groupId = getIdNum(groupsTree.getItem(groupsTree.getItemCount() - 1));
        if (groupId == GROUPID_MAX) {
            var idsArr = currentGroupIds();
            for (var i = idsArr.length - 1; i > 0; --i) {
                if (idsArr[i - 1] + 1 != idsArr[i]) {
                    groupId = idsArr[i - 1] + 1;
                    break;
                }
            }
        }
        else {
            ++groupId;
        }
        return (groupId);
    }

    function getIdNum(item) {
        var text = String(item.getText());
        return(Number(text.substr(
               text.lastIndexOf(' ') + 1)));
    }

    function currentGroupIds() {
        var idsArr = [];
        for each (var item in groupsTree.getItems()) {
            idsArr.push(getIdNum(item));
        }
        return (idsArr);
    }

    function getGroupItemFromId(id) {
        var grItem = null;
        for each (var item in groupsTree.getItems()) {
            if (getIdNum(item) == id) {
                grItem = item;
                break;
            }
        }
        return (grItem);
    }

    function selectGroupIdDlg(shell, item, curId, unusedOnly) {
        var id = -1;
        var dlgWidth = 206;
        var dlgHeight = 50;
        var selectDlg = widgets.Shell(shell,
                        swt.SWT.BORDER | swt.SWT.APPLICATION_MODAL);
        selectDlg.setLayout(layout.GridLayout());
        selectDlg.setSize(dlgWidth, dlgHeight);

        var dlgComp = widgets.Composite(selectDlg, swt.SWT.NONE);
        var dlgLayout = layout.GridLayout();
        dlgLayout.numColumns = 5;
        dlgComp.setLayout(dlgLayout);

        var imgLabel = widgets.Label(dlgComp, swt.SWT.NONE);
        var labelData = layout.GridData();
        labelData.widthHint = 16;
        labelData.horizontalIndent = -2;
        imgLabel.setLayoutData(labelData);

        var label = widgets.Label(dlgComp, swt.SWT.NONE);
        label.setText('Group:');

        var scale = widgets.Spinner(dlgComp, swt.SWT.BORDER);
        scale.setMinimum(Number(GROUPID_MIN));
        scale.setMaximum(Number(GROUPID_MAX));
        scale.setIncrement(1);
        scale.setPageIncrement(1);
        scale.setSelection(curId);

        scale.addListener(swt.SWT.Modify, function() {
            if (unusedOnly) {
                var found = false;
                var selId = scale.getSelection();
                if (selId != curId) {
                    var idsArr = currentGroupIds();
                    for each (var i in idsArr) {
                        if (selId == i) {
                            found = true;
                            break;
                        }
                    }
                }
                imgLabel.setImage(found ? ICO_ERROR : null);
                okBtn.setEnabled(found == false);
            }
        });

        var okBtn = widgets.Button(dlgComp, swt.SWT.PUSH|swt.SWT.DEFAULT);
        okBtn.setText ("OK");
        okBtn.addListener(swt.SWT.Selection, function() {
            id = scale.getSelection();
            selectDlg.dispose();
        });

        var cancelBtn = widgets.Button(dlgComp, swt.SWT.PUSH);
        cancelBtn.setText ("Cancel");
        cancelBtn.addListener(swt.SWT.Selection, function() {
            selectDlg.dispose();
        });

        var rect = item.getBounds(0);
        var pt = groupsTree.toDisplay(rect.x + rect.width, rect.y);
        pt.y -= (dlgHeight - rect.height) / 2;  /* center on item vertically */

        selectDlg.setLocation(pt);

        selectDlg.open();
        while (!selectDlg.isDisposed()) {
            if (!display.readAndDispatch()) {
                display.sleep();
            }
        }
        return (id);
    }

    return {
        title:                    "Algorithm and Group configuration",
        composite:                comp,
        collectInputFxn:          collectInput
    };
}

function page2Fxn(comp)
{
    var inFunc = false;
    var LAST_ROW = 5;
    var ROW_COMBO_WIDTH = isWin ? 95 : 115;
    var ROW_TEXT_WIDTH = isWin ? 100 : 95;
    var SIZE_LABEL_WIDTH = isWin ? 50 : 55;
    var memList = logic.getMemSectionNames(serverEnv.platform);
    var offChipMax = {};
    offChipMax['DDR2'] = OFF_CHIP_MAX;
    offChipMax['SDRAM'] = OFF_CHIP_MAX;
    var offChipMaxStr = {};
    offChipMaxStr['DDR2'] = OFF_CHIP_MAX_STR;
    offChipMaxStr['SDRAM'] = OFF_CHIP_MAX_STR;

    var shell = comp.getShell();

    var grMem = widgets.Group(comp, swt.SWT.SHADOW_NONE);
    grMem.setText('Memory Map');
    var layoutMemory = layout.GridLayout();
    layoutMemory.numColumns = 4;
    grMem.setLayout(layoutMemory);
    var grData = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|
                 layout.GridData.FILL_HORIZONTAL);
    grMem.setLayoutData(grData);

    var errObj = createImageLabel2(grMem, 2, 4);

    var areaLabel = rowLabel(grMem, "Memory area",
            layout.GridData.HORIZONTAL_ALIGN_CENTER);
    var addrLabel = rowLabel(grMem, "Base Address",
            layout.GridData.HORIZONTAL_ALIGN_CENTER);
    var lengthLabel = rowLabel(grMem, "Length",
            layout.GridData.HORIZONTAL_ALIGN_CENTER);
    var sizeLabel = rowLabel(grMem, "Size",
            layout.GridData.HORIZONTAL_ALIGN_CENTER);

    function comboChanged(widget) {
        var i = Number(widget.getData());
        if (String(widget.getText()) == 'RESET_VECTOR') {
            rows[i].textLen.setText('0x00000080');
            rows[i].textLen.setEnabled(false);
        }
        else {
            rows[i].textLen.setEnabled(true);
            setState();
        }
    }

    function addressChanged(widget) {
        if (!inFunc && serverEnv.memAlign[serverEnv.platform] &&
            serverEnv.memAlign[serverEnv.platform] != 'none') {

            memAlign(serverEnv.memAlign[serverEnv.platform] == 'top');
        }
        showSize(labelTotal, getAddress(5) - getAddress(0));
        setState();
    }

    function lengthChanged(widget) {
        if (!inFunc && serverEnv.memAlign[serverEnv.platform] &&
            serverEnv.memAlign[serverEnv.platform] != 'none') {

            memAlign(serverEnv.memAlign[serverEnv.platform] == 'top');
        }
        var i = Number(widget.getData());
        showSize(rows[i].labelSize, getLength(i));
        showLast();
        showSize(labelTotal, getAddress(5) - getAddress(0));
        setState();
    }

    var rows = [];
    for (var i = 0; i < 4; i++) {
        var row = { combo      : rowCombo(grMem, memList),
                    textAddr   : rowText(grMem, ''),
                    textLen    : rowText(grMem, ''),
                    labelSize  : rowLabel(grMem, '',
                                 layout.GridData.HORIZONTAL_ALIGN_BEGINNING,
                                 SIZE_LABEL_WIDTH, swt.SWT.RIGHT)
        }
        row.combo.setData(i);
        row.combo.addListener(swt.SWT.Modify, function(e) { comboChanged(e.widget); });
        row.textAddr.setData(i);
        row.textAddr.addListener(swt.SWT.Modify, function(e) { addressChanged(e.widget); });
        row.textLen.setData(i);
        row.textLen.addListener(swt.SWT.Modify, function(e) { lengthChanged(e.widget); });
        rows.push(row);
    }

    var labelLast = widgets.Label(grMem, swt.SWT.NONE);
    var llastData = layout.GridData(layout.GridData.FILL_HORIZONTAL|
                                    layout.GridData.HORIZONTAL_ALIGN_END);
    labelLast.setLayoutData(llastData);
    labelLast.setText('Last address:');

    var textLast = rowText(grMem, '');
    textLast.addListener(swt.SWT.Modify, function(e) { addressChanged(e.widget); });
    var titleTotal = widgets.Label(grMem,  swt.SWT.NONE);
    titleTotal.setText('Total:');
    var ttData = layout.GridData(layout.GridData.HORIZONTAL_ALIGN_END);
    titleTotal.setLayoutData(ttData);

    var labelTotal = rowLabel(grMem, '',
                              layout.GridData.HORIZONTAL_ALIGN_BEGINNING,
                              SIZE_LABEL_WIDTH, swt.SWT.RIGHT);

    var defCheck = widgets.Button(grMem, swt.SWT.CHECK);
    defCheck.setText('Use defaults');
    defCheck.setLayoutData(layout.GridData(
                           layout.GridData.HORIZONTAL_ALIGN_CENTER));
    defCheck.addListener(swt.SWT.Selection, function(e) {
        if (defCheck.getSelection()) {
            serverEnv.memConfig[serverEnv.platform] = null;
            serverEnv.memConfig[serverEnv.platform] = logic.defaultMemConfig(serverEnv.platform);
            serverEnv.defaultMem[serverEnv.platform] = true;
            populateMemInputs();
            serverEnv.memAlign[serverEnv.platform] = 'none';
            memAlignTop.setSelection(false);
            memAlignBot.setSelection(false);
            memAlignNone.setSelection(true);
        }
        else {
            serverEnv.defaultMem[serverEnv.platform] = false;
        }
        enableInputs(!serverEnv.defaultMem[serverEnv.platform]);
        setState();
    });

    var alGroup = widgets.Group(grMem, swt.SWT.NONE);
    alGroup.setText('Auto align');
    var alLayout = layout.GridLayout();
    alLayout.numColumns = 3;
    alGroup.setLayout(alLayout);
    var alData = layout.GridData();
    alData.horizontalSpan = 2;
    alGroup.setLayoutData(alData);

    var memAlignTop = widgets.Button(alGroup, swt.SWT.RADIO);
    memAlignTop.setText('From top');
    memAlignTop.addListener(swt.SWT.Selection, function(e) { alignChanged('top'); });
    var memAlignBot = widgets.Button(alGroup, swt.SWT.RADIO);
    memAlignBot.setText('From bottom');
    memAlignBot.addListener(swt.SWT.Selection, function(e) { alignChanged('bottom'); });

    var memAlignNone = widgets.Button(alGroup, swt.SWT.RADIO);
    memAlignNone.setText('None');
    memAlignNone.addListener(swt.SWT.Selection, function(e) { alignChanged('none'); });

    function alignChanged(align) {
        serverEnv.memAlign[serverEnv.platform] = align;
        if (align == 'none') {
            for (var i = 0; i < 4; i++) {
                rows[i].textAddr.setEnabled(true);
            }
            textLast.setEnabled(true);
        }
        else {
            var isTop = align == 'top';
            rows[0].textAddr.setEnabled(isTop);
            for (var i = 1; i < 4; i++) {
                rows[i].textAddr.setEnabled(false);
            }
            textLast.setEnabled(!isTop);
            memAlign(isTop);
        }
    }

    function alignResetVector(addr, alignDown) {
        var res = addr & 0x000FFFFF;
        if (res > 0) {
            if (alignDown) {
                addr += (0x100000 - res);
            }
            else {
                addr -= res;
            }
        }
        return (addr);
    }

    function memAlign(top) {
        inFunc = true;
        if (top) {
            for (var i = 0; i < 3; i++) {
                var next = getAddress(i) + getLength(i);
                if (String(rows[i + 1].combo.getText()) == 'RESET_VECTOR') {
                    next = alignResetVector(next, true);
                }
                rows[i + 1].textAddr.setText('0x' + next.toString(16));
            }
            showLast();

        }
        else {
            var prev = getAddress(5) - getLength(3);
            if (String(rows[3].combo.getText()) == 'RESET_VECTOR') {
                prev = alignResetVector(prev, false);
            }
            rows[3].textAddr.setText('0x' + prev.toString(16));
            for (var i = 3; i > 0; --i) {
                var prev = getAddress(i) - getLength(i - 1);
                if (prev < 0) {
                    rows[i - 1].textAddr.setText(Number.NaN);
                }
                else {
                    if (String(rows[i - 1].combo.getText()) == 'RESET_VECTOR') {
                        prev = alignResetVector(prev, false);
                    }
                    rows[i - 1].textAddr.setText('0x' + prev.toString(16));
                }
            }
        }
        setState();
        inFunc = false;
    }

    function rowCombo(comp, initList) {
        var combo = new widgets.Combo(comp, swt.SWT.DROP_DOWN |
                                      swt.SWT.READ_ONLY);
        for (var i = 0; i < initList.length; i++) {
            combo.add(initList[i]);
        }
        var data = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
        data.widthHint = ROW_COMBO_WIDTH;
        combo.setLayoutData(data);
        return (combo);
    }

    function rowText(comp, str) {
        var text = new widgets.Text(comp, swt.SWT.BORDER);
        var data = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
        data.widthHint = ROW_TEXT_WIDTH;
        text.setLayoutData(data);
        text.setText(str);
        return (text);
    }
    defCheck.setLayoutData(layout.GridData(
                           layout.GridData.HORIZONTAL_ALIGN_CENTER));

    function enableInputs(enable) {
        for (var i = 0; i < 4; i++) {
            rows[i].combo.setEnabled(enable);
        }
        if (!enable) {
            for (var i = 0; i < 4; i++) {
                rows[i].textAddr.setEnabled(false);
                rows[i].textLen.setEnabled(false);
            }
            textLast.setEnabled(false);
        }
        else {
            for (var i = 0; i < 4; i++) {
                if (String(rows[i].combo.getText()) != 'RESET_VECTOR') {
                    rows[i].textLen.setEnabled(true);
                }
            }
            alignChanged(serverEnv.memAlign[serverEnv.platform]);
        }
        memAlignTop.setEnabled(enable);
        memAlignNone.setEnabled(enable);
        memAlignBot.setEnabled(enable);
        labelLast.setEnabled(enable);
    }

    // Create menu bar with listeners
    var menuBar = createMenu(shell, 2);
    menuBar.getItem(0).getMenu().addListener(swt.SWT.Show, function(e) {
        menuBar.getItem(0).getMenu().getItem(0).setEnabled(!hasError());
    } );
    menuBar.getItem(0).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function(saveListener) {
        collectInput();

        var complete = saveXmlFile(shell, serverEnv);
        if (complete == true) {
            shared_gui.createMessageBox("Save successful", serverEnv);
        }
    } );
    menuBar.getItem(1).getMenu().getItem(0).addListener(swt.SWT.Selection,
    function (memmapListener) {
        program.Program.launch(wizard_constants.MEMMAP_LINK);
    } );
    menuBar.getItem(1).getMenu().getItem(1).addListener(swt.SWT.Selection,
    function (faqListener) {
        program.Program.launch(wizard_constants.FAQ_LINK);
    } );

    function populatePanel() {
        populateMemInputs();
        if (!serverEnv.memAlign[serverEnv.platform]) {
            serverEnv.memAlign[serverEnv.platform] = 'bottom';
        }
        if (serverEnv.memAlign[serverEnv.platform] == 'top') {
            memAlignTop.setSelection(true);
        }
        else if(serverEnv.memAlign[serverEnv.platform] == 'bottom') {
            memAlignBot.setSelection(true);
        }
        else {
            memAlignNone.setSelection(true);
        }
        defCheck.setSelection(serverEnv.defaultMem[serverEnv.platform]);
        enableInputs(!serverEnv.defaultMem[serverEnv.platform]);
        setState();
    }

    function hasError() {
        return (errObj.label1.getImage() != null);
    }

    populatePanel();

    function populateMemInputs() {
        inFunc = true;
        if (!serverEnv.memConfig[serverEnv.platform]) {
            serverEnv.memConfig[serverEnv.platform] = logic.defaultMemConfig(serverEnv.platform);
        }
        if (!serverEnv.defaultMem[serverEnv.platform]) {
            serverEnv.defaultMem[serverEnv.platform] = false;
        }
        for (var i = 0; i < 4; i++) {
            rows[i].combo.setText(serverEnv.memConfig[serverEnv.platform][i].sect);
            rows[i].textAddr.setText(serverEnv.memConfig[serverEnv.platform][i].base);
            rows[i].textLen.setText(serverEnv.memConfig[serverEnv.platform][i].len);
            showSize(rows[i].labelSize, Number(serverEnv.memConfig[serverEnv.platform][i].len));
        }
        inFunc = false;
    }

    function getLength(index) {
        return (getHex(String(rows[index].textLen.getText())));
    }

    function getAddress(index) {
        if (index == LAST_ROW) {
            var addrstr = String(textLast.getText());
        }
        else {
            var addrstr = String(rows[index].textAddr.getText());
        }
        if (!addrstr.match(/^0x[a-f0-9]+$/i)) {
            var addr = Number.NaN;
        }
        else {
            var addr = Number(addrstr);
        }
        return (addr);
    }

    function showLast() {
        var lastAddr = getAddress(3) + getLength(3);
        textLast.setText('0x' + lastAddr.toString(16));
    }

    function setState() {
        var valid = validateInput();
        buttons.backEnabled = valid;
        buttons.nextEnabled = false;
        buttons.finishEnabled = valid;
        buttons.updated = true;
    }

    function enableAlignBtns(enable) {
        memAlignTop.setEnabled(enable);
        memAlignNone.setEnabled(enable);
        memAlignBot.setEnabled(enable);
    }

    function validateInput() {
        var valid = true;
        if (!defCheck.getSelection()) {

            /* bad number */
            var NaNObj = {};
            for (var i = 0; i < 4; i++) {
                if (isNaN(getAddress(i))) {
                    NaNObj.row = i;
                    NaNObj.col = ' address';
                    break;
                }
                else {
                    if (isNaN(getLength(i))) {
                        NaNObj.row = i;
                        NaNObj.col = ' length';
                        break;
                    }
                }
            }
            if (NaNObj.col) {
                valid = false;
            }
            else if (isNaN(getAddress(5))) {
                NaNObj.row = 5;
                NaNObj.col = ' address';
                valid = false;
            }

            if (valid) {
                /* duplicate sections */
                var dup = false;
                var dupIndex = 0;
                for (var i = 0; i < 3; i++) {
                    var str = String(rows[i].combo.getText());
                    for (j = i + 1; j < 4; j++) {
                        if (str == String(rows[j].combo.getText())) {
                            dup = true;
                            dupIndex = j;
                            break;
                        }
                    }
                }
                if (dup) {
                    valid = false;
                }
            }
            if (valid) {
                /* rest vector not on 1mb boundary  */
                var resetWrong = false;
                for (var i = 0; i < 4; i++) {
                    if (String(rows[i].combo.getText()) == 'RESET_VECTOR') {
                        if ((getAddress(i) & 0x000FFFFF) > 0) {
                            resetWrong = true;
                            break;
                        }
                    }
                }
                if (resetWrong) {
                    valid = false;
                }
            }
            if (valid) {
                /* section overlap  */
                var over = false;
                var over1Index = 0;
                var over2Index = 0;
                for (var i = 0; i < 3; i++) {
                    var beg1 = getAddress(i);
                    var end1 = beg1 + getLength(i);
                    j = i + i;
                    for (j = i + 1; j < 4; j++) {
                        var beg2 = getAddress(j);
                        var end2 = beg2 + getLength(j);
                        if ((beg2 >= beg1 && beg2 < end1) || (beg1 >= beg2 && beg1 < end2)) {
                            over = true;
                            over1Index = i;
                            over2Index = j;
                            break;
                        }
                    }
                    if (over) {
                        break;
                    }
                }
                if (over) {
                    valid = false;
                }
            }
            if (valid) {
                /* DDR2 or SDRAM larger than 4mb */
                var secTooBig = false;
                var secName = '';
                for (var i = 0; i < 4; i++) {
                    var sec = String(rows[i].combo.getText());
                    if (sec == 'DDR2' || sec == 'SDRAM') {
                        if ((getLength(i) > offChipMax[sec])) {
                            secTooBig = true;
                            secName = sec;
                            break;
                        }
                    }
                }
                if (secTooBig) {
                    valid = false;
                }
            }
        }
        if (valid) {
            setImageLabel2(errObj, null, '');
        }
        else {
            if (NaNObj.col) {
                if (NaNObj.row == LAST_ROW) {
                    var sect = 'Last';
                }
                else {
                    var sect = rows[NaNObj.row].combo.getText();
                }
                var msg = sect + NaNObj.col + ' is not a valid hex number';
            }
            else if (dup) {
                var msg = 'Duplicate memory areas ' + rows[dupIndex].combo.getText();
            }
            else if (resetWrong) {
                var msg = 'RESET_VECTOR must be on 1mb boundary';
            }
            else if (over) {
                var msg = 'Memory overlap ' + rows[over1Index].combo.getText() +
                          ', ' + rows[over2Index].combo.getText();
            }
            else if (secTooBig) {
                var msg = 'It is recommended that ' + secName + ' be ' +
                          offChipMaxStr[secName] + ' or less';
            }
            else {
                var msg = 'Invalid configuration';
            }
            if (secTooBig) {
                setImageLabel2(errObj, ICO_WARNING, msg);
                valid = true;
            }
            else {
                setImageLabel2(errObj, ICO_ERROR, msg);
            }
        }
        if (!serverEnv.defaultMem[serverEnv.platform]) {
            enableAlignBtns((dup || NaNObj.col) ? false : true);
        }
        return (valid);
    }

    function collectInput() {
        for (var i = 0; i < 4; i++) {
            serverEnv.memConfig[serverEnv.platform][i].sect = String(rows[i].combo.getText());
            serverEnv.memConfig[serverEnv.platform][i].base = String(rows[i].textAddr.getText());
            serverEnv.memConfig[serverEnv.platform][i].len = String(rows[i].textLen.getText());
        }
    }

    return {
        title:              "Configure Server Memory",
        composite:          comp,
        collectInputFxn:    collectInput
    };
}

function codecsInputComposite(grGroups, groupsTree, flagErrorFxn)
{
    var compMain = widgets.Composite(grGroups, swt.SWT.NONE);
    this.compMain = compMain;
    var layoutMain = layout.GridLayout();
    layoutMain.numColumns = 1;
    compMain.setLayout(layoutMain);
    var mainData = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|
                                    layout.GridData.FILL_HORIZONTAL);
    compMain.setLayoutData(mainData);

    var groupAttrsComm = createGroup(compMain, 'Common algorithm values');

    var nameObj = createImageLabelTextBox(groupAttrsComm, null, 'Name: ', 90);
    var textBoxName = nameObj.textBox;
    var imgName = nameObj.label2;

    var priScale = createScale(groupAttrsComm, PRIORITY_PRE, 1, 14, 1, 85)

    var groupAttrsOptional = createGroup(compMain, 'Optional algorithm values');
    var stackMemIdObj = createImageLabelTextBox(groupAttrsOptional, null,
                                                'StackMemId: ', 105);
    var textStackMemId = stackMemIdObj.textBox;
    var imgStackMemId = stackMemIdObj.label2;
    var stackSizeObj = createImageLabelTextBox(groupAttrsOptional, null,
                                               'StackSize: ', 105);
    var textStackSize = stackSizeObj.textBox;
    var imgStackSize = stackSizeObj.label2;


    var defCheck = widgets.Button(compMain, swt.SWT.CHECK);
    defCheck.setText('Use defaults');
    defCheck.setLayoutData(layout.GridData(
                           layout.GridData.HORIZONTAL_ALIGN_CENTER));
    defCheck.addListener(swt.SWT.Selection, function(e) {
        if (defCheck.getSelection()) {
            setDefaults(false);
        }
        else {
            priScale.scale.enabled = true;
            textStackMemId.enabled = true;
            textStackSize.enabled = true;
        }
    });

    function initInputs(selItem) {
        if (selItem && selItem.getParentItem() != null) {
            var qn = String(selItem.getData());
            if (serverEnv.algVals[qn]) {
                var algVals = serverEnv.algVals[qn];
                textBoxName.setText(algVals.name);
                if (serverEnv.algVals[qn].useDefaults) {
                    setDefaults(false);
                }
                else {
                    priScale.scale.setSelection(algVals.pri);
                    priScale.valLabel.setText(PRIORITY_PRE + String(algVals.pri));
                    textStackMemId.setText(algVals.stackMemId);
                    textStackSize.setText(String(algVals.stackSize));
                    defaultsOff();
                }
            }
            else {
                setDefaults(true);
            }
        }
    }
    this.initInputs = initInputs;

    function getInput(selItem) {
        if (selItem && selItem.getParentItem() != null) {
            var qn = String(selItem.getData());
            serverEnv.algVals[qn] = {};
            serverEnv.algVals[qn].name = String(textBoxName.getText());
            serverEnv.algVals[qn].pri = priScale.scale.getSelection();
            serverEnv.algVals[qn].stackMemId = String(textStackMemId.getText());
            serverEnv.algVals[qn].stackSize = String(textStackSize.getText());
            serverEnv.algVals[qn].useDefaults = defCheck.getSelection();
            serverEnv.algVals[qn].groupId = groupIdFromItem(selItem.getParentItem());
        }
    }
    this.getInput = getInput;

    function enableInputs(enable) {
        textBoxName.enabled = enable;
        defCheck.enabled = enable;
        if (defCheck.getSelection()) {
            priScale.scale.enabled = false;
            textStackMemId.enabled = false
            textStackSize.enabled = false;
        }
        else {
            priScale.scale.enabled = enable;
            textStackMemId.enabled = enable;
            textStackSize.enabled = enable;
        }
    }
    this.enableInputs = enableInputs;

    var inSet = false;
    function setDefaults(setName) {
        inSet = true;
        var selArr = groupsTree.getSelection();
        if (selArr.length) {
            if (setName) {
                textBoxName.setText(String(selArr[0].getText()).toLowerCase());
            }
            var qn = String(selArr[0].getData());
            var defPri = defaultPriority(qn);
            priScale.valLabel.setText(PRIORITY_PRE + defPri);
            priScale.scale.setSelection(defPri);
            textStackMemId.setText(DEFAULT_STACKMEMID);
            textStackSize.setText(wizard_constants.DEFAULT_STACKSIZE);
            defCheck.setSelection(true);
            priScale.scale.enabled = false;
            textStackMemId.enabled = false;
            textStackSize.enabled = false;
            flagErrorFxn(selArr[0], !validateInput());
        }
        inSet = false;
    }

    function validateInput() {
        var valid = true;
        if (String(textBoxName.getText()).length == 0) {
            imgName.setImage(ICO_ERROR);
            valid = false;
        }
        else {
            imgName.setImage(null);
        }
        if (!posNumberText(textStackMemId, imgStackMemId, true)) {
            valid = false;
        }
        var stackStr = String(textStackSize.getText());
        if (stackStr != wizard_constants.DEFAULT_STACKSIZE &&
           !isPosNumber(stackStr)) {

            imgStackSize.setImage(ICO_ERROR);
            valid = false;
        }
        else {
            imgStackSize.setImage(null);
        }
        return (valid);
    }
    this.validateInput = validateInput;

    function collectInput() {
        getInput(groupsTree.getSelection()[0]);
        verifyAlgVals(groupsTree);
    }
    this.collectInput = collectInput;


    function defaultsOff() {
        defCheck.setSelection(false);
        priScale.scale.enabled = true;
        textStackMemId.enabled = true;
        textStackSize.enabled = true;
    }

    textBoxName.addListener(swt.SWT.Modify, function(e) {
        if (!inSet) {
            flagErrorFxn(groupsTree.getSelection()[0], !validateInput());
        }
    });

    priScale.scale.addListener(swt.SWT.Selection, function(e) {
        if (!inSet) {
            defaultsOff();
        }
    });
    textStackMemId.addListener(swt.SWT.Modify, function(e) {
        if (!inSet) {
            defaultsOff();
            flagErrorFxn(groupsTree.getSelection()[0], !validateInput());
        }
    });
    textStackSize.addListener(swt.SWT.Modify, function(e) {
        if (!inSet) {
            defaultsOff();
            flagErrorFxn(groupsTree.getSelection()[0], !validateInput());
        }
    });
}

function groupsInputComposite(shell, grGroups, groupsTree, flagErrorFxn)
{
    var SIZE_LABEL_WIDTH = isWin ? 45 : 50;

    var compMain = widgets.Composite(grGroups, swt.SWT.NONE);
    this.compMain = compMain;
    var layoutMain = layout.GridLayout();
    layoutMain.numColumns = 1;
    compMain.setLayout(layoutMain);
    var mainData = layout.GridData(layout.GridData.VERTICAL_ALIGN_BEGINNING|
                                   layout.GridData.FILL_HORIZONTAL);
    compMain.setLayoutData(mainData);

    var groupDSKT2 = createGroup(compMain, 'DSKT2 Scratch Sizes', 3);
    groupDSKT2.setToolTipText(wizard_constants.SCRATCH_HOVER);

    var saramObj = createImageLabelTextBox(groupDSKT2, null, 'SARAM: ', 105);
    var textBoxSaram = saramObj.textBox;
    textBoxSaram.setToolTipText(wizard_constants.SCRATCH_HOVER);
    saramObj.label1.setToolTipText(wizard_constants.SCRATCH_HOVER);
    var imgSaram = saramObj.label2;
    var labelSaramSize  = rowLabel(groupDSKT2, '',
                 layout.GridData.HORIZONTAL_ALIGN_BEGINNING,
                 SIZE_LABEL_WIDTH, swt.SWT.RIGHT)
    var daramObj = createImageLabelTextBox(groupDSKT2, null, 'DARAM: ', 105);
    var textBoxDaram = daramObj.textBox;
    textBoxDaram.setToolTipText(wizard_constants.SCRATCH_HOVER);
    daramObj.label1.setToolTipText(wizard_constants.SCRATCH_HOVER);
    var imgDaram = daramObj.label2;
    var labelDaramSize  = rowLabel(groupDSKT2, '',
                 layout.GridData.HORIZONTAL_ALIGN_BEGINNING,
                 SIZE_LABEL_WIDTH, swt.SWT.RIGHT)
    var groupEDMA3 = createGroup(compMain, 'Group DMA Settings');

    var maxPaRamsObj = createImageLabelTextBox(groupEDMA3, null,
                                               'Params: ', 105);
    var textMaxPaRams = maxPaRamsObj.textBox;
    addDmaSpecificListener(maxPaRamsObj.label1,
                           wizard_constants.DMAN3_PARAM_HOVER,
                           wizard_constants.EDMA3_MAXPARAM_HOVER);

    var imgMaxPaRams = maxPaRamsObj.label2;

    /* for when control is disabled */
    addDmaSpecificListener(maxPaRamsObj.labelComp,
                           wizard_constants.DMAN3_PARAM_HOVER,
                           wizard_constants.EDMA3_MAXPARAM_HOVER);

    var maxTccsObj = createImageLabelTextBox(groupEDMA3, null,
                                             'TCCs: ', 105);
    var textMaxTccs = maxTccsObj.textBox;
    addDmaSpecificListener(maxTccsObj.label1,
                           wizard_constants.DMAN3_TCC_HOVER,
                           wizard_constants.EDMA3_MAXTCC_HOVER);

    var imgMaxTccs = maxTccsObj.label2;

    /* for when control is disabled */
    addDmaSpecificListener(maxTccsObj.labelComp,
                           wizard_constants.DMAN3_TCC_HOVER,
                           wizard_constants.EDMA3_MAXTCC_HOVER);


    var maxEdmaChannelsObj = createImageLabelTextBox(groupEDMA3, null,
                                                     'Edma Channels: ', 105);
    var textMaxEdmaChannels = maxEdmaChannelsObj.textBox;
    maxEdmaChannelsObj.label1.setData(wizard_constants.EDMA3_MAXEDMACHANS_HOVER);
    addHoverListener(shell, maxEdmaChannelsObj.label1);

    var imgMaxEdmaChannels = maxEdmaChannelsObj.label2;
    maxEdmaChannelsObj.labelComp.setData(wizard_constants.EDMA3_MAXEDMACHANS_HOVER);

    /* for when control is disabled */
    addHoverListener(shell, maxEdmaChannelsObj.labelComp);

    var maxQdmaChannelsObj = createImageLabelTextBox(groupEDMA3, null,
                                                     'Qdma Channels: ', 105);
    var textMaxQdmaChannels = maxQdmaChannelsObj.textBox;
    maxQdmaChannelsObj.label1.setData(wizard_constants.EDMA3_MAXQDMACHANS_HOVER);

    /* for when control is disabled */
    addHoverListener(shell, maxQdmaChannelsObj.label1);

    var imgMaxQdmaChannels = maxQdmaChannelsObj.label2;
    maxQdmaChannelsObj.labelComp.setData(wizard_constants.EDMA3_MAXQDMACHANS_HOVER);
    addHoverListener(shell, maxQdmaChannelsObj.labelComp);

    function addDmaSpecificListener(control, dman3Msg, edma3Msg) {
        control.addListener(swt.SWT.MouseHover, function(e) {
            control.setData(serverEnv.useDMAN3 ? dman3Msg : edma3Msg);
            controlMouseOver(shell, control, e);
        });
        control.addListener(swt.SWT.Dispose, function(e){ mouseLeave(e); });
        control.addListener(swt.SWT.KeyDown, function(e){ mouseLeave(e); });
        control.addListener(swt.SWT.MouseMove, function(e){ mouseLeave(e); });
    }

    function enableEDMA3(enable, idma3Fxns, iresFxns, useDMAN3) {
        if (!idma3Fxns && !iresFxns) {
            enable = false;
        }
        maxPaRamsObj.textBox.setEnabled(enable);
        maxPaRamsObj.label1.setEnabled(enable);
        maxTccsObj.textBox.setEnabled(enable);
        maxTccsObj.label1.setEnabled(enable);
        if (enable) {
            if (idma3Fxns) {
                var enableEdma = useDMAN3 ? false : iresFxns;
                maxEdmaChannelsObj.textBox.setEnabled(enableEdma);
                maxEdmaChannelsObj.label1.setEnabled(enableEdma);
                maxQdmaChannelsObj.textBox.setEnabled(!useDMAN3);
                maxQdmaChannelsObj.label1.setEnabled(!useDMAN3);
            }
            else {  /* iresFxns is true */
                maxEdmaChannelsObj.textBox.setEnabled(enable);
                maxEdmaChannelsObj.label1.setEnabled(enable);
                maxQdmaChannelsObj.textBox.setEnabled(enable);
                maxQdmaChannelsObj.label1.setEnabled(enable);
            }
        }
        else {
            maxEdmaChannelsObj.textBox.setEnabled(enable);
            maxEdmaChannelsObj.label1.setEnabled(enable);
            maxQdmaChannelsObj.textBox.setEnabled(enable);
            maxQdmaChannelsObj.label1.setEnabled(enable);
        }
    }
    this.enableEDMA3 = enableEDMA3;
    function initInputs(selItem) {
        if (selItem && selItem.getParentItem() == null) {
            var groupId = groupIdFromItem(selItem);
            if (!serverEnv.groups[groupId]) {
                logic.defaultGroup(serverEnv, groupId);
            }
            textBoxSaram.setText(serverEnv.groups[groupId].dskt2.saram);
            textBoxDaram.setText(serverEnv.groups[groupId].dskt2.daram[serverEnv.platform]);
            if (serverEnv.useDMAN3) {
                textMaxPaRams.setText(serverEnv.groups[groupId].dman3.numPaRam);
                textMaxTccs.setText(serverEnv.groups[groupId].dman3.numTccGroup[serverEnv.platform]);
            }
            else {
                textMaxPaRams.setText(serverEnv.groups[groupId].edma3.maxPaRams);
                textMaxTccs.setText(serverEnv.groups[groupId].edma3.maxTccs);
            }
            textMaxEdmaChannels.setText(serverEnv.groups[groupId].edma3.maxEdmaChannels);
            textMaxQdmaChannels.setText(serverEnv.groups[groupId].edma3.maxQdmaChannels);
       }
    }
    this.initInputs = initInputs;

    function getInput(selItem) {
        if (selItem && selItem.getParentItem() == null) {
            var groupId = groupIdFromItem(selItem);
            if (!serverEnv.groups[groupId]) {
                serverEnv.groups[groupId] = {};
            }
            if (!serverEnv.groups[groupId].dskt2) {
                serverEnv.groups[groupId].dskt2 = {};
            }
            serverEnv.groups[groupId].dskt2.saram =
                    String(textBoxSaram.getText());
            serverEnv.groups[groupId].dskt2.daram[serverEnv.platform] =
                    String(textBoxDaram.getText());

            if (!serverEnv.groups[groupId].edma3) {
                serverEnv.groups[groupId].edma3 = {};
            }
            serverEnv.groups[groupId].edma3.maxPaRams =
                    String(textMaxPaRams.getText());
            serverEnv.groups[groupId].edma3.maxTccs =
                    String(textMaxTccs.getText());
            serverEnv.groups[groupId].edma3.maxEdmaChannels =
                    String(textMaxEdmaChannels.getText());
            serverEnv.groups[groupId].edma3.maxQdmaChannels =
                    String(textMaxQdmaChannels.getText());
            if (!serverEnv.groups[groupId].dman3) {
                serverEnv.groups[groupId].dman3 = {};
                serverEnv.groups[groupId].dman3.numTccGroup = [];

            }
            serverEnv.groups[groupId].dman3.numPaRam =
                    String(textMaxPaRams.getText());
            serverEnv.groups[groupId].dman3.numTccGroup[serverEnv.platform] =
                    String(textMaxTccs.getText());
        }
    }
    this.getInput = getInput;

    function enableInputs(enable) {

        if (!enable) {
            enableEDMA3(false);
        }
        else {
            var sel = groupsTree.getSelection()[0];
            if (!useEDMA3Check.getEnabled()) {
                serverEnv.useDMAN3 = false;
            }
            else {
                serverEnv.useDMAN3 = serverEnv.useDMAN3 ? true : false;
            }
            enableEDMA3(serverEnv.platformSupportsEdma,
                        groupImplementsIdma3Fxns(sel),
                        groupImplementsIresFxns(sel), serverEnv.useDMAN3);
        }
    }
    this.enableInputs = enableInputs;

    function validateInput() {
        var valid = true;
        if (!hexNumberText(textBoxSaram, imgSaram)) {
            valid = false;
        }
        if (!hexNumberText(textBoxDaram, imgDaram)) {
            valid = false;
        }
        if (textMaxPaRams.getEnabled()) {
            if (!posNumberText(textMaxPaRams, imgMaxPaRams, true)) {
                valid = false;
            }
        }
        else {
            imgMaxPaRams.setImage(null);
        }
        if (textMaxTccs.getEnabled()) {
            if (!posNumberText(textMaxTccs, imgMaxTccs, true)) {
                valid = false;
            }
        }
        else {
            imgMaxTccs.setImage(null);
        }
        if (textMaxEdmaChannels.getEnabled()) {
            if (!posNumberText(textMaxEdmaChannels, imgMaxEdmaChannels, true)) {
                valid = false;
            }
        }
        else {
            imgMaxEdmaChannels.setImage(null);
        }
        if (textMaxQdmaChannels.getEnabled()) {
            if (!posNumberText(textMaxQdmaChannels, imgMaxQdmaChannels, true)) {
                valid = false;
            }
        }
        else {
            imgMaxQdmaChannels.setImage(null);
        }
        return (valid);
    }
    this.validateInput = validateInput;

    function collectInput() {
        getInput(groupsTree.getSelection()[0]);
        verifyGroups(groupsTree);
    }
    this.collectInput = collectInput;

    textBoxSaram.addListener(swt.SWT.Modify, function(e) {
        flagErrorFxn(groupsTree.getSelection()[0], !validateInput());
        if (imgSaram.getImage() == null) {
            showSize(labelSaramSize, getHex(String(textBoxSaram.getText())));
        }
        else {
            labelSaramSize.setText('');
        }
    });
    textBoxDaram.addListener(swt.SWT.Modify, function(e) {
        flagErrorFxn(groupsTree.getSelection()[0], !validateInput());
        if (imgDaram.getImage() == null) {
            showSize(labelDaramSize, getHex(String(textBoxDaram.getText())));
        }
        else {
            labelDaramSize.setText('');
        }
    });

    textMaxPaRams.addListener(swt.SWT.Modify, function(e) {
        flagErrorFxn(groupsTree.getSelection()[0], !validateInput());
    });
    textMaxTccs.addListener(swt.SWT.Modify, function(e) {
        flagErrorFxn(groupsTree.getSelection()[0], !validateInput());
    });
    textMaxEdmaChannels.addListener(swt.SWT.Modify, function(e) {
        flagErrorFxn(groupsTree.getSelection()[0], !validateInput());
    });
    textMaxQdmaChannels.addListener(swt.SWT.Modify, function(e) {
        flagErrorFxn(groupsTree.getSelection()[0], !validateInput());
    });
}

function rowLabel(comp, str, align, width, textAlign)
{
    var label = new widgets.Label(comp, swt.SWT.NONE);
    if (textAlign) {
        label.setAlignment(textAlign);
    }
    label.setText(str);
    var data = new layout.GridData(align);
    if (width) {
        data.widthHint = width;
    }
    label.setLayoutData(data);
    return (label);
}

function getHex(str)
{
    if (!logic.isHexNumber(str)) {
        var len = Number.NaN;
    }
    else {
        var len = Number(str);
    }
    return (len);
}

function posNumberText(textBox, img, zeroOk)
{
    var valid = true;
    if (!isPosNumber(textBox.getText(), zeroOk)) {
        img.setImage(ICO_ERROR);
        valid = false;
    }
    else {
        img.setImage(null);
    }
    return (valid);
}

function hexNumberText(textBox, img)
{
    var valid = true;

    if (isNaN(getHex(String(textBox.getText())))) {
        img.setImage(ICO_ERROR);
        valid = false;
    }
    else {
        img.setImage(null);
    }
    return (valid);
}

function validGroup(selItem)
{
    var valid = true;
    var groupId = groupIdFromItem(selItem);
    if (serverEnv.groups[groupId]) {
        valid = logic.isHexNumber(serverEnv.groups[groupId].dskt2.saram) &&
                logic.isHexNumber(serverEnv.groups[groupId].dskt2.daram[serverEnv.platform]);
        if (valid) {
            if (logic.groupConfiguresDman3(serverEnv, groupId)) {
                if (serverEnv.groups[groupId].dman3) {
                    valid = isPosNumber(serverEnv.groups[groupId].dman3.numPaRam, true) &&
                            isPosNumber(serverEnv.groups[groupId].dman3.numTccGroup[serverEnv.platform], true);
                }
                else {
                    valid = true;
                }
            }
            else if (logic.groupConfiguresEdma3(serverEnv, groupId)) {
                if (serverEnv.groups[groupId].edma3) {
                    valid = isPosNumber(serverEnv.groups[groupId].edma3.maxPaRams, true) &&
                            isPosNumber(serverEnv.groups[groupId].edma3.maxTccs, true) &&
                            isPosNumber(serverEnv.groups[groupId].edma3.maxEdmaChannels, true) &&
                            isPosNumber(serverEnv.groups[groupId].edma3.maxQdmaChannels, true);
                }
                else {
                    valid = true;
                }
            }
        }
    }
    return (valid);
}

function verifyGroups(groupsTree)
{
    serverEnv.configuresEdma3 = false;
    var grItems = groupsTree.getItems();
    for (var i = 0; i < grItems.length; i++) {
        var groupId = groupIdFromItem(grItems[i]);
        if (!serverEnv.groups[groupId]) {
            logic.defaultGroup(serverEnv, groupId);
        }
        serverEnv.groups[groupId].implsIdma3Fxns =
                groupImplementsIdma3Fxns(grItems[i]);
        serverEnv.groups[groupId].implsIresFxns =
                groupImplementsIresFxns(grItems[i]);
        serverEnv.groups[groupId].cfgDman3 =
            logic.groupConfiguresDman3(serverEnv, groupId);
        serverEnv.groups[groupId].cfgEdma3 =
                logic.groupConfiguresEdma3(serverEnv, groupId);
        if (serverEnv.groups[groupId].cfgEdma3 && 
            !serverEnv.configuresEdma3) {

            serverEnv.configuresEdma3 = true;
         }
    }
}

function verifyAlgVals(groupsTree)
{
    var grItems = groupsTree.getItems();
    for (var i = 0; i < grItems.length; i++) {
        var groupId = groupIdFromItem(grItems[i]);
        var groupNItems = grItems[i].getItems();
        for (var j = 0; j < groupNItems.length; j++) {
            var qn = String(groupNItems[j].getData());
            if (!serverEnv.algVals[qn]) {  /* use defaults */
                serverEnv.algVals[qn] = {};
                serverEnv.algVals[qn].name = String(groupNItems[j].getText()).toLowerCase();
                serverEnv.algVals[qn].pri = defaultPriority(qn);
                serverEnv.algVals[qn].stackMemId = DEFAULT_STACKMEMID;
                serverEnv.algVals[qn].stackSize =
                        wizard_constants.DEFAULT_STACKSIZE;
                serverEnv.algVals[qn].useDefaults = true;
            }
            serverEnv.algVals[qn].groupId = groupId;
        }
    }
}

function defaultPriority(qn)
{
    var pri = 3;
    if (serverEnv.inheritsMap[qn]) {
        for each (var inface in serverEnv.inheritsMap[qn]) {
            if (defaultAlgsValsMap[inface]) {
                var pri = defaultAlgsValsMap[inface].priority;
                break;
            }
        }
    }
    return (pri);
}

function groupIdFromItem(item)
{
    var groupId = String(item.getText());
    return(groupId.substr(groupId.indexOf(' ') + 1));
}

function showSize(label, len)
{
    if (len < 0x400) {
        label.setText(String(len) + '  B');
    }
    else if (len < 0x100000) {
        var size = len / 0x400;
        var flr = Math.floor(size);
        var text = String(flr) + ' KB';
        var toolTipText = null;
        if (size - flr > 0) {
            var rem = (size - flr) * 0x400;
            toolTipText = text + ' + ' +  rem + ' B';
            text = '~' + text;
        }
        label.setText(text);
        label.setToolTipText(toolTipText);
    }
    else {
        var size = len / 0x100000;
        var flr = Math.floor(size);
        var text = String(Math.floor(size)) + ' MB';
        var toolTipText = null;
        if (size - flr > 0) {
            toolTipText = text;
            text = '~' + text;
            var rem = (size - flr) * 0x100000;
            if (rem >= 0x400) {
                size = rem / 0x400;
                flr = Math.floor(size);
                toolTipText += ' + ' + String(flr) + ' KB';
                rem = (size - flr) * 0x400;
            }
            if (rem >= 0) {
                toolTipText += ' + ' + String(rem) + '  B';
            }
        }
        label.setText(text);
        label.setToolTipText(toolTipText);
    }
}

function createGroup(comp, text, numColumns)
{
    var group = widgets.Group(comp, swt.SWT.SHADOW_NONE);
    group.setText(text);
    var layoutGroup = layout.GridLayout();
    if (numColumns) {
        layoutGroup.numColumns = numColumns;
    }
    else {
        layoutGroup.numColumns = 2;
    }
    group.setLayout(layoutGroup);
    group.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    return (group);
}

function createScale(comp, message, min, max, init, width)
{
    var lblVal = widgets.Label(comp, swt.SWT.NONE);
    lblVal.setText(message + init);

    var gridData = layout.GridData(layout.GridData.FILL_HORIZONTAL);
    lblVal.setLayoutData(gridData);

    var scale = widgets.Scale(comp, swt.SWT.HORIZONTAL);
    scale.setMinimum(min);
    scale.setMaximum(max);
    scale.setIncrement(1);
    scale.setPageIncrement(1);
    scale.setSelection(init);
    var gridDataStretch = layout.GridData(layout.GridData.FILL_HORIZONTAL);
    if (width) {
        gridDataStretch.widthHint = width;
    }
    scale.setLayoutData(gridDataStretch);

    scale.addListener(swt.SWT.Selection, function(e) {
        lblVal.setText(message + scale.getSelection());
    });

    return {
        valLabel:  lblVal,
        scale: scale
    };
}


function createImageLabel(comp, image, message, width)
{
    var lblComp = widgets.Composite(comp, swt.SWT.NONE);
    var lblLayout = layout.GridLayout();
    lblLayout.marginWidth = 0;
    lblLayout.numColumns = 2;
    lblComp.setLayout(lblLayout);
    var lblCompData = layout.GridData();
    if (width) {
        lblCompData.widthHint = width;
    }
    else {
       lblCompData.verticalAlignment = layout.GridData.BEGINNING;
       lblCompData.horizontalAlignment = layout.GridData.FILL;
    }
    lblComp.setLayoutData(lblCompData);

    var label1 = widgets.Label(lblComp, swt.SWT.NONE);
    label1.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    label1.setText(message);

    var label2 = widgets.Label(lblComp, swt.SWT.NONE);
    label2Data = layout.GridData();
    label2Data.widthHint = 20;
    label2.setLayoutData(label2Data);
    label2.setImage(image);

    return {
        label1: label1,
        label2: label2,
        labelComp : lblComp
    };
}

function createImageLabelTextBox(comp, image, message, textWidth, labelWidth)
{
    var labelObj = createImageLabel(comp, image, message, labelWidth);

    var textBox = new widgets.Text( comp, swt.SWT.SINGLE | swt.SWT.BORDER);
    var gridDataStretch = new layout.GridData( layout.GridData.FILL_HORIZONTAL);
    if (textWidth) {
        gridDataStretch.widthHint = textWidth;
    }
    textBox.setLayoutData(gridDataStretch);

    return {
        label1: labelObj.label1,
        label2: labelObj.label2,
        textBox: textBox,
        labelComp : labelObj.labelComp
    };
}

/**
 * Displays a label and text box
 * @param {Composite} comp from page
 * @param {String} message
 * @return textBox
 */
function createTextBox(comp, message, labelWidth, readOnly)
{
    var lbl = new widgets.Label(comp, swt.SWT.NONE);
    lbl.setText(message);
    var gridData = new layout.GridData();
    if (labelWidth) {
        gridData.widthHint = labelWidth;
    }
    else {
        gridData.widthHint = 150;
    }
    lbl.setLayoutData(gridData);

    var style = swt.SWT.SINGLE | swt.SWT.BORDER;
    var textBox = new widgets.Text( comp, style);
    var gridDataStretch = new layout.GridData( layout.GridData.FILL_HORIZONTAL);
    textBox.setLayoutData( gridDataStretch );

    return (textBox);
}

/**
 */
function createLabels(comp, message, labelWidth)
{
    var lbl1 = new widgets.Label(comp, swt.SWT.NONE);
    lbl1.setText( message );
    var gridData = new layout.GridData();
    if (labelWidth) {
        gridData.widthHint = labelWidth;
    }
    else {
        gridData.widthHint = 150;
    }
    lbl1.setLayoutData(gridData);

    var lbl2 = new widgets.Label(comp, swt.SWT.NONE);
    var gridDataStretch = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
    lbl2.setLayoutData(gridDataStretch);
    return (lbl2);
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

    var fileItem = new widgets.MenuItem(menuBar, swt.SWT.CASCADE);
    fileItem.setText ("&File");

    var fileSubmenu = new widgets.Menu(shell, swt.SWT.DROP_DOWN);
    fileItem.setMenu(fileSubmenu);

    if (pageNum == 0) {
        var open = new widgets.MenuItem(fileSubmenu, swt.SWT.PUSH);
        open.setText("&Open");
        open.setAccelerator(swt.SWT.CTRL + 111); //111 is dec of o
        var save = new widgets.MenuItem(fileSubmenu, swt.SWT.PUSH);
        save.setText("&Save");
        save.setAccelerator(swt.SWT.CTRL + 115); //115 is dec of s
    }

    if (pageNum == 1) {
        var instructionsText = wizard_constants.INSTRUCTIONS1;
        var save = new widgets.MenuItem(fileSubmenu, swt.SWT.PUSH);
        save.setText("&Save");
        save.setAccelerator(swt.SWT.CTRL + 115); //115 is dec of s
    }

    if (pageNum == 2) {
        var instructionsText = wizard_constants.INSTRUCTIONS2;
        var save = new widgets.MenuItem(fileSubmenu, swt.SWT.PUSH);
        save.setText("&Save");
        save.setAccelerator(swt.SWT.CTRL + 115); //115 is dec of s
    }

    var helpItem = new widgets.MenuItem(menuBar, swt.SWT.CASCADE);
    helpItem.setText ("&Help");
    helpItem.setAccelerator(swt.SWT.CTRL + 104); //104 is dec of h

    var helpSubmenu = new widgets.Menu(shell, swt.SWT.DROP_DOWN);
    helpItem.setMenu(helpSubmenu);

    var faq;
    if (pageNum == 0) {
        var basic = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
        basic.setText("&Basic Server Information");
        basic.setAccelerator(swt.SWT.CTRL + 98); //98 is dec of b

        faq = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
        faq.setText("GenServer Wizard &FAQ");
        faq.setAccelerator(swt.SWT.CTRL + 102); //102 is dec of f
    }

    if (pageNum == 1) {
        var algvals = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
        algvals.setText("&Algorithm and Group configuration");
        algvals.setAccelerator(swt.SWT.CTRL + 115); //115 is dec of s

        faq = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
        faq.setText("GenServer Wizard &FAQ");
        faq.setAccelerator(swt.SWT.CTRL + 102); //102 is dec of f

        new widgets.MenuItem(helpSubmenu, swt.SWT.SEPARATOR);

        var groupIds = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
        groupIds.setText("&Codec Engine GroupIds");
        groupIds.setAccelerator(swt.SWT.CTRL + 99); //99 is dec of c

        var memManage = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
        memManage.setText("&Memory management in XDAIS with DSKT2");
        memManage.setAccelerator(swt.SWT.CTRL + 109); //109 is dec of m
    }

    if (pageNum == 2) {
        var memmap = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
        memmap.setText("&Memory Map");
        memmap.setAccelerator(swt.SWT.CTRL + 109); //109 is dec of m

        faq = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
        faq.setText("GenServer Wizard &FAQ");
        faq.setAccelerator(swt.SWT.CTRL + 102); //102 is dec of f
    }

    new widgets.MenuItem(helpSubmenu, swt.SWT.SEPARATOR);
    var about = new widgets.MenuItem(helpSubmenu, swt.SWT.PUSH);
    about.setText("About");
    about.addListener(swt.SWT.Selection, function (aboutListener) {
        var msg = wizard_constants.ABOUT_MESSAGE + '\n\n' + csd;
        shared_gui.createMessageBox(msg, serverEnv);
    } );

    return menuBar;
}

/**
 * Generates a button that when selected creates a file dialog
 * @param {Composite}
 * @param {Shell}
 */
function BrowseButton(comp, shell, width, vert) {

    this.comp = comp;
    this.shell = shell;

    var message = "";
    var errorMessage = "";
    var stringMatch = "";

    this.setMessage = function(message) {
        this.message = message;
        btn.setText(message);
    }

    var btn = new widgets.Button(comp, swt.SWT.PUSH);
    var data = new layout.GridData();
    data.widthHint = width;
    if (vert) {
        data.verticalIndent = vert;
    }
    btn.setLayoutData(data);
    this.btn = btn;

    this.addListener = function(stringMatch, errorMessage, fileBool) {
        if (fileBool==true) {
            btn.addListener(swt.SWT.Selection, function(event) {
                var dialog = new widgets.FileDialog(shell);
                dialog.setFilterPath( textBox.getText() );

                var file = dialog.open();
                if (file != null) {
                    file = file + "";
                    file = file.toString().replace(/\\/g,"/");
                    var suffix = file + "";
                    suffix = suffix.substring(
                        (suffix.lastIndexOf("/")+1), suffix.length);

                    if (suffix.match( stringMatch )!=null) {
                        textBox.setText(file);
                    }
                    else {
                        textBox.setText( "" );
                        shared_gui.createMessageBox(errorMessage,serverEnv);
                    }

                }
            } );
        }
        else {
            btn.addListener( swt.SWT.Selection, function( event ) {
                var dialog = new widgets.DirectoryDialog( shell );
                dialog.setFilterPath( textBox.getText() );

                var dir = dialog.open();
                if (dir != null) {
                    dir = dir + "";
                    dir = dir.toString().replace(/\\/g,"/");
                    var suffix = dir + "";
                    suffix = suffix.substring(
                        (suffix.lastIndexOf("/")+1), suffix.length);

                    if (suffix.match( stringMatch )!=null) {
                        textBox.setText(dir);
                    }
                    else {
                        textBox.setText( "" );
                        shared_gui.createMessageBox(errorMessage,serverEnv);
                    }
                }
            } );
        }
    }

    var textBox = new widgets.Text(comp, swt.SWT.SINGLE |
                                   swt.SWT.BORDER );
    var textdata = new layout.GridData(layout.GridData.FILL_HORIZONTAL);
    if (vert) {
        textdata.verticalIndent = vert;
    }
    textBox.setLayoutData(textdata);
    this.textBox = textBox;
}

/**
* GUI to save current serverEnv to user_specified_loc.xml
* @param {Shell}
* @param {serverEnv}
* @return Boolean: true if save successful, false otherwise
*/
function saveXmlFile( shell, serverEnv ) {

    /* create text for XML file from serverEnv */
    var xmlText = xmlOps.saveXml( serverEnv );

    /* get output location */
    var dialog = new widgets.FileDialog(shell, swt.SWT.SAVE);
    dialog.setFilterExtensions(filterExt);
    dialog.setFilterNames(filterNames);
    dialog.setFileName(serverEnv.serverName.replace(/\./g,'_')
        + '_wizard.svrwiz');
    var file = dialog.open();
    if (file != null) {
        try {
            if (java.io.File( file ).exists()) {
                var btnClicked = shared_gui.createYesNoBox(
                        file + " already exists! Do you want to overwrite it?",
                        serverEnv );
                if (btnClicked==1) {
                    var status = xmlOps.textFileWriter( file, xmlText );
                    if (status==-1) { return false; }
                    return true;
                }
            } else {
                var status = xmlOps.textFileWriter( file, xmlText );
                if (status==-1) { return false; }
                return true;
            }
        }
        catch(e) {
            shared_gui.createMessageBox( "Error occured writing XML file:\n" + e,
                serverEnv );
        }
    }
    return false;
}

/**
* GUI needed to read XML file
* @param image to be displayed on shell
* @param serverEnv to be modified based on XML file
* @param shellLocation
* @return updated serverEnv based on XML file
*/
function readXmlFile(shell, image, serverEnv) {

    var xshell = new widgets.Shell(shell, swt.SWT.DIALOG_TRIM |
                                          swt.SWT.RESIZE);
    xshell.setSize(100,100);
    if (serverEnv.shellLocation!=null) {
        xshell.setLocation(serverEnv.shellLocation);
    }
    xshell.setImage(image);
    var dialog = new widgets.FileDialog(shell);
    dialog.setFilterExtensions(filterExt);
    dialog.setFilterNames(filterNames);
    var file = dialog.open();
    if (file != null) {
        try {
            serverEnv = xmlOps.loadXml(file, serverEnv);
        }
        catch(e) {
            var mbox = widgets.MessageBox(shell, swt.SWT.ICON_INFORMATION);
            mbox.setText( "Server Wizard Message" );
            mbox.setMessage( "Error occured reading XML file: " + e );
            mbox.open();
        }
    }
    xshell.close();
    return serverEnv;
}

function controlMouseOver(shell, control, e)
{
    if (control.getData() != null) {
        var infoStr = String(control.getData());
        itemHover(shell, control, null, infoStr, graphics.Point(e.x, e.y));
    }
}

function treeItemMouseOver(shell, control, e)
{
    var item =  control.getItem(graphics.Point(e.x, e.y));
    if (item != null  && item.getData() != null) {
        var infoStr = String(item.getData());
        if (serverEnv.reposMap[infoStr]) {
            infoStr += "\n in " + serverEnv.reposMap[infoStr];
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
    if (item) {
        var rect = item.getBounds(0);
    }
    else {
        var rect = control.getBounds();
    }
    if (curPt) {
        pt = control.toDisplay(curPt.x, curPt.y);
    }
    else {
        pt = control.toDisplay(rect.x, rect.y);
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
    var shellHeight;

    while (true) {
        if (currentPage == 0) {
            shellHeight = SHELL_HEIGHT;
        }
        else {
            nextVisited = true;
        }

        var shell = new widgets.Shell(display, swt.SWT.DIALOG_TRIM |
            swt.SWT.RESIZE | swt.SWT.MIN);
        shell.setImage(image);
        shell.setLayout( new layout.FormLayout() );
        shell.setText( "Codec Engine GenServer Wizard" );
        shell.setMinimumSize(SHELL_WIDTH, shellHeight);
        shell.addListener( swt.SWT.Move, function(event) {
            try {
                serverEnv.shellLocation = shell.getLocation();
            }
            catch(e) {}
        } );
        serverEnv.shell = shell;

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

        var pageData = pageFxns[ currentPage ]( compMain );
        var point = pageData.composite.computeSize( swt.SWT.DEFAULT,
            swt.SWT.DEFAULT, false );
        labelTitle.setText(pageData.title);

        var formMain = new layout.FormData();
        formMain.top = new layout.FormAttachment( 0, 10 );
        formMain.left = new layout.FormAttachment( 0, 10 );
        formMain.right = new layout.FormAttachment( 100, -10 );
        compMain.setLayoutData(formMain);

        var compLine = new widgets.Composite( shell, swt.SWT.NONE );
        var layoutLine = new layout.RowLayout();
        layoutLine.pack = false;
        compLine.setLayout(layoutLine);
        var lbl = new widgets.Label( compLine, swt.SWT.SEPARATOR |
            swt.SWT.HORIZONTAL);
        lbl.setLayoutData( new layout.RowData( 1000, swt.SWT.DEFAULT ) );

        var comp = new widgets.Composite( shell, swt.SWT.NONE );
        var lay = new layout.RowLayout();
        lay.pack = false;
        comp.setLayout(lay);

        var btnBack = new widgets.Button( comp, swt.SWT.PUSH );
        btnBack.setText( "   < &Back   " );

        var btnNext = new widgets.Button( comp, swt.SWT.PUSH );
        btnNext.setText( "    &Next >    " );

        var btnFinish = new widgets.Button( comp, swt.SWT.PUSH );
        btnFinish.setText("   &Finish   " );

        var btnCancel = new widgets.Button( comp, swt.SWT.PUSH );
        btnCancel.setText("   &Cancel   ");

        var formRow = new layout.FormData();
        formRow.left = new layout.FormAttachment( 0, 50 );
        formRow.bottom = new layout.FormAttachment( 100, -10 );
        formRow.right = new layout.FormAttachment( 100, -10 );
        comp.setLayoutData(formRow);

        var formLine = new layout.FormData();
        formLine.left = new layout.FormAttachment( 0, 10 );
        formLine.right = new layout.FormAttachment( 100, -10 );
        formLine.bottom = new layout.FormAttachment( comp, -5, swt.SWT.TOP );
        compLine.setLayoutData(formLine);

        btnBack.enabled   = buttons.backEnabled;
        btnNext.enabled   = buttons.nextEnabled;
        btnFinish.enabled = buttons.finishEnabled;

        var eventBack   = false;
        var eventNext   = false;
        var eventFinish = false;
        var eventCancel = false;

        btnCancel.addListener( swt.SWT.Selection, function(e) {
            eventCancel = true;
        } );

        btnBack.addListener( swt.SWT.Selection, function(e) {
            eventBack = true;
        } );

        btnNext.addListener( swt.SWT.Selection, function(e) {
            eventNext = true;
        } );

        btnFinish.addListener( swt.SWT.Selection, function(e) {
            eventFinish = true;
        } );

        var displayRect = display.getBounds();
        if (serverEnv.shellLocation!=null) {
            shell.setLocation(serverEnv.shellLocation);
        }

        shell.setSize(SHELL_WIDTH, shellHeight);
        shell.open();
        buttons.updated = false;

        shell.addListener(swt.SWT.Close, function(e) {
              pageData.collectInputFxn();
              var btnClicked = shared_gui.createYesNoBox(
                  "Do you want to quit?", serverEnv );
              if (btnClicked == 1) {
                  print("Closing GUI Codec Engine GenServer Wizard now...");
                  shell.dispose();
                  eventCancel = true;
              }
        } );
        while(!shell.isDisposed()) {
            if (!display.readAndDispatch()) {
                java.lang.Thread.sleep( 50 );
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

                    var btnClicked = shared_gui.createYesNoBox(
                        "Would you like to save the values entered into "
                        + "the Codec Engine GenServer Wizard?", serverEnv );
                    if (btnClicked==1) {
                        var complete = saveXmlFile(shell, serverEnv);
                        if (complete == true) {
                            shared_gui.createMessageBox("Save successful",
                                                        serverEnv );
                        }
                    }
                    break;
                }
                if (eventCancel) {
                    pageData.collectInputFxn();
                    var btnClicked = shared_gui.createYesNoBox(
                        "Do you want to quit?", serverEnv);
                    if (btnClicked == 1) {
                        print("Closing GUI Codec Engine GenServer Wizard now...");
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
    return (eventFinish == true);
}

function main(serverEnv, parent) {
    print("\nStarting GUI Codec Engine GenServer Wizard now...");
    print('GUI Codec Engine GenServer Wizard user:\n'
          + 'You can ignore any warnings below about Mozilla this or that missing.');

    initSWT();

    init(serverEnv, parent);

    if (platformList.length) {
        this.serverEnv = serverEnv;
        var success = navigatePages(parent);
    }
    else {
        var success = false;
    }


    if (!success) {
        serverEnv.error = true;
    }
    return (serverEnv);
}

function searchCodecs(shell, searchPathArr)
{
    shell.setCursor(graphics.Cursor(display, swt.SWT.CURSOR_WAIT));
    var codecsArr = [];
    var inheritsMap = [];
    var reposMap = [];
    try {
        var il =  Packages.xdc.tools.sg.widgets.InterfaceList(searchPathArr);
        var impl = il.findImplementors('ti.sdo.ce.ICodec');
        for (var i = 0; i < impl.size(); i++) {
            var u = impl.get(i);
            if (u.isMod()) {
                var qn = String(u.getQualName());

                var rep = String(u.getParent().getBaseDir());
                reposMap[qn] = rep.substr(0,
                               rep.length - String(u.getPkgName()).length - 1);

                codecsArr.push(qn);
                inheritsMap[qn] = [];
                var inh = u.getInherits();
                for (var j = 0; j < inh.size(); j++) {
                    var interfaceQn = String(inh.get(j).getQualName());
                    if (interfaceQn != 'ti.sdo.ce.ICodec') {
                        inheritsMap[qn].push(interfaceQn);
                    }
                }
            }
        }
        codecsArr = codecsArr.sort();
    }
    catch (e) {
        shared_gui.createMessageBox("An error occured while searching for codecs:\n" +
                                    e, serverEnv );
        codecsArr = [];
        inheritsMap = [];
        reposMap = [];
    }
    shell.setCursor(null);
    return {
        codecsArr: codecsArr,
        inheritsMap: inheritsMap,
        reposMap: reposMap
    };
}

function codecDragStart(e, tree)
{
    var item = tree.getItem(graphics.Point(e.x, e.y));
    if (item && item.getParentItem() != null) {
        e.doit = true;
    }
    else {
        e.doit = false;
    }
}

function codecDragSetData(e, tree)
{
    var depType;
    e.data = NO_DATA_STR;
    var selArr = tree.getSelection();
    if (selArr.length) {
        e.data = selArr[0].getData();
    }
}


function groupDragOver(e, tree)
{
    e.detail = 0;
    if (dnd.TextTransfer.getInstance().isSupportedType(e.currentDataType)) {
        if (e.item != null && e.item.getParentItem() == null) {
            var selArr = tree.getSelection();
            if (selArr.length && selArr[0].getParentItem() != e.item) {

                e.detail = dnd.DND.DROP_COPY;
            }
        }
    }
}

function dataDroppedInGroup(e, tree)
{
    if (e.data == null) {
        e.detail = dnd.DND.DROP_NONE;
    }
    else if (dnd.TextTransfer.getInstance().
             isSupportedType(e.currentDataType)){

        var selArr = tree.getSelection();
        if (selArr.length) {
            selArr[0].dispose();
        }

        var ti = widgets.TreeItem(e.item, swt.SWT.NULL);
        ti.setText (e.data.substr(e.data.lastIndexOf('.') + 1));
        ti.setData(e.data);
        tree.setSelection(ti);
    }
}

function initCodecDragSource(tree, getInputFxn)
{
    var transfer = [dnd.TextTransfer.getInstance()];
    var dragSource = dnd.DragSource(tree, dnd.DND.DROP_COPY);
    dragSource.setTransfer(transfer);

    dragSource.addDragListener(new dnd.DragSourceListener({
        dragStart: function(e) { codecDragStart(e, tree); },
        dragSetData: function(e) { codecDragSetData(e, tree); },
        dragFinished: function(e) {}
    }));

}

function initCodecDropTarget(tree)
{
    var transfer = [dnd.TextTransfer.getInstance()];
    var dropTarget = dnd.DropTarget(tree, dnd.DND.DROP_COPY);
    dropTarget.setTransfer(transfer);
    dropTarget.addDropListener(new dnd.DropTargetListener({
        dragEnter: function(e) {},
        dragOver: function(e) { groupDragOver(e, tree); },
        dragOperationChanged: function(e) {},
        dragLeave: function(e) {},
        dropAccept: function(e) {},
        drop: function(e) { dataDroppedInGroup(e, tree); },
    }));
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
function InstructionBanner( comp ) {
    var text = "";

    var textBox = new widgets.Text( comp, swt.SWT.WRAP
        |swt.SWT.MULTI | swt.SWT.BORDER );
    textBox.setEditable(false);
    var gridHint = new layout.GridData( layout.GridData.FILL_HORIZONTAL);
    gridHint.horizontalSpan = 2;
    textBox.setLayoutData(gridHint);

    this.setText = function( text ) {
        this.text = text;
        textBox.setText( text );
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
                        shared_gui.createMessageBox(msg, serverEnv);
                    }
                }
                else {
                    break;
                }
            }
        } );
    }

    var textBox = new widgets.Text(comp, swt.SWT.SINGLE |
        swt.SWT.BORDER);
    textBox.setEditable(false);
    textBox.setLayoutData(layout.GridData(layout.GridData.FILL_HORIZONTAL));
    this.textBox = textBox;
}

function createImageLabel2(comp, cols, span)
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
    label1Data.heightHint = 15;
    label1.setLayoutData(label1Data);
    label1.setImage(null);

    var label2 = widgets.Link(lblComp, swt.SWT.NONE);
    label2.setLayoutData(layout.GridData(layout.GridData.FILL_BOTH));
    return {
        label1: label1,
        label2: label2,
        lblComp : lblComp
    };
}

function setImageLabel2(msgObj, img, msg, link)
{
    msgObj.label1.setImage(img);
    if (link) {
        msgObj.label2.setText('<A>' + msg + '</A>');
        msgObj.label2.setToolTipText('View all problems in a popup window');
    }
    else {
        msgObj.label2.setText(msg);
        msgObj.label2.setToolTipText(null);
    }
}

function groupImplementsIdma3Fxns(groupItem)
{
    if (serverEnv.idma3Fxns != null) {
        for (i = 0; i < groupItem.getItemCount(); i++) {
            if (serverEnv.idma3Fxns[String(groupItem.getItem(i).getData())]) {
                return (true);
            }
        }
    }
    return (false);
}

function groupImplementsIresFxns(groupItem)
{
    if (serverEnv.iresFxns != null) {
        for (i = 0; i < groupItem.getItemCount(); i++) {
            if (serverEnv.iresFxns[String(groupItem.getItem(i).getData())]) {
                return (true);
            }
        }
    }
    return (false);
}


function addHoverListener(shell, control, isTree)
{
    control.addListener(swt.SWT.MouseHover, function(e) {
        if (isTree) {
            treeItemMouseOver(shell, control, e);
        }
        else {
            controlMouseOver(shell, control, e);
        }
    });
    control.addListener(swt.SWT.Dispose, function(e){ mouseLeave(e); });
    control.addListener(swt.SWT.KeyDown, function(e){ mouseLeave(e); });
    control.addListener(swt.SWT.MouseMove, function(e){ mouseLeave(e); });
}


function errorsList(shell, title, arrErrors)
{
    var dlg = new widgets.Shell(shell, swt.SWT.DIALOG_TRIM | 
                                       swt.SWT.RESIZE |
                                       swt.SWT.APPLICATION_MODAL);
    if (serverEnv.shellLocation != null) {
        dlg.setLocation(serverEnv.shellLocation);
    }
    dlg.setSize(500, 350);
    dlg.setText(title);
    dlg.setImage(image);
    
    var grid = new layout.GridLayout(1, false);
    dlg.setLayout(grid);
    
    var comp = new widgets.Composite(dlg, swt.SWT.NONE);
    comp.setLayout(new layout.GridLayout());   
    var gridData = new layout.GridData(layout.GridData.FILL_BOTH);
    comp.setLayoutData(gridData); 

    var errObj = createImageLabel2(comp, 2, 1);
    setImageLabel2(errObj, ICO_ERROR, 'Problems');
            
    var text = new widgets.Text(comp, swt.SWT.WRAP|swt.SWT.BORDER|
                                swt.SWT.READ_ONLY|swt.SWT.MULTI|
                                swt.SWT.V_SCROLL);
    var str = arrErrors.join('\n');
    text.setText(str);
    text.setLayoutData(new layout.GridData(layout.GridData.FILL_BOTH));
    
    var closeBtn = new widgets.Button(comp, swt.SWT.PUSH);
    closeBtn.setText("  Close  ");
    var closeData = new layout.GridData(layout.GridData.HORIZONTAL_ALIGN_END);
    closeBtn.setLayoutData(closeData);
    
    closeBtn.addListener(swt.SWT.Selection, function (closeEvent) {
        dlg.dispose();
    });
    dlg.open(); 
}
/*
 *  @(#) ti.sdo.ce.wizards.genserver; 1, 0, 0,84; 12-2-2010 21:28:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

