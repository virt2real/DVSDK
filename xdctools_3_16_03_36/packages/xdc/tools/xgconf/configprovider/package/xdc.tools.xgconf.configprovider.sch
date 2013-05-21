xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('xdc.tools.xgconf.configprovider');

/* ======== IMPORTS ======== */

    xdc.loadPackage('xdc.tools');
    xdc.loadPackage('xdc.shelf');
    xdc.loadPackage('xdc.tools.xgconf.modeldata');
    xdc.loadPackage('xdc.services.spec');
    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');

/* ======== OBJECTS ======== */

// package xdc.tools.xgconf.configprovider
    var pkg = $om.$$bind('xdc.tools.xgconf.configprovider.Package', $$PObj());
    $om.$$bind('xdc.tools.xgconf.configprovider', $$VObj('xdc.tools.xgconf.configprovider', pkg));
// module ConfigProvider
    var po = $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider.Module', $$PObj());
    var vo = $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider', $$VObj('xdc.tools.xgconf.configprovider.ConfigProvider', po));
    pkg.$$bind('ConfigProvider', vo);
    $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider.Ops', $$PEnm('xdc.tools.xgconf.configprovider.ConfigProvider.Ops'));
    $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider.Instance', $$PObj());
    $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider$$Object', $$PObj());
    $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider.Object', $$PStr($om['xdc.tools.xgconf.configprovider.ConfigProvider$$Object'], true));
    $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider$$Params', $$PObj());
    $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider.Params', $$PStr($om['xdc.tools.xgconf.configprovider.ConfigProvider$$Params'], true));
// module Main
    var po = $om.$$bind('xdc.tools.xgconf.configprovider.Main.Module', $$PObj());
    var vo = $om.$$bind('xdc.tools.xgconf.configprovider.Main', $$VObj('xdc.tools.xgconf.configprovider.Main', po));
    pkg.$$bind('Main', vo);
    $om.$$bind('xdc.tools.xgconf.configprovider.Main.Instance', $$PObj());
    $om.$$bind('xdc.tools.xgconf.configprovider.Main$$Object', $$PObj());
    $om.$$bind('xdc.tools.xgconf.configprovider.Main.Object', $$PStr($om['xdc.tools.xgconf.configprovider.Main$$Object'], true));
    $om.$$bind('xdc.tools.xgconf.configprovider.Main$$Params', $$PObj());
    $om.$$bind('xdc.tools.xgconf.configprovider.Main.Params', $$PStr($om['xdc.tools.xgconf.configprovider.Main$$Params'], true));
// module Contrib
    var po = $om.$$bind('xdc.tools.xgconf.configprovider.Contrib.Module', $$PObj());
    var vo = $om.$$bind('xdc.tools.xgconf.configprovider.Contrib', $$VObj('xdc.tools.xgconf.configprovider.Contrib', po));
    pkg.$$bind('Contrib', vo);

/* ======== CONSTS ======== */

// module ConfigProvider
    $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider.OP_GETVALUES', $$Enum($om['xdc.tools.xgconf.configprovider.ConfigProvider.Ops'], 'xdc.tools.xgconf.configprovider.ConfigProvider.OP_GETVALUES', 0));
    $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider.OP_VALIDATE', $$Enum($om['xdc.tools.xgconf.configprovider.ConfigProvider.Ops'], 'xdc.tools.xgconf.configprovider.ConfigProvider.OP_VALIDATE', 1));
// module Main
// module Contrib

/* ======== CREATES ======== */

// module ConfigProvider
    var fxn = $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider$$create', $$PFxn($om['xdc.tools.xgconf.configprovider.ConfigProvider.Module'], $om['xdc.tools.xgconf.configprovider.ConfigProvider.Instance'], 5, 4, false));
        fxn.$$arg(0, 'fileName', $$T_Str, undefined);
        fxn.$$arg(1, 'exeName', $$T_Str, undefined);
        fxn.$$arg(2, 'pkgName', $$T_Str, undefined);
        fxn.$$arg(3, 'cfgScript', $$T_Str, undefined);
        fxn.$$arg(4, '__params', $om['xdc.tools.xgconf.configprovider.ConfigProvider.Params'], {});
    function ConfigProvider$$create( fileName, exeName, pkgName, cfgScript, __params ) {
        var __mod = $om['xdc.tools.xgconf.configprovider.ConfigProvider'];
        var __inst = $om['xdc.tools.xgconf.configprovider.ConfigProvider.Instance'].$$make();
        __inst.$$bind('$package', $om['xdc.tools.xgconf.configprovider']);
        __inst.$$bind('$index', __mod.$instances.length);
        __inst.$$bind('$category', 'Instance');
        __inst.$$bind('$args', {fileName:fileName, exeName:exeName, pkgName:pkgName, cfgScript:cfgScript});
        __inst.$$bind('$module', __mod);
        __mod.$instances.$add(__inst);
        for (__p in __params) __inst[__p] = __params[__p];
        var save = $om.$curpkg;
        $om.$$bind('$curpkg', __mod.$package.$name);
        __mod.instance$meta$init.$fxn.apply(__inst, [fileName, exeName, pkgName, cfgScript]);
        $om.$$bind('$curpkg', save);
        __inst.$$bless();
        return __inst;
    }
    var fxn = $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider$$construct', $$PFxn($om['xdc.tools.xgconf.configprovider.ConfigProvider.Module'], null, 6, 4, false));
        fxn.$$arg(0, '__obj', $om['xdc.tools.xgconf.configprovider.ConfigProvider$$Object'], null);
        fxn.$$arg(1, 'fileName', $$T_Str, undefined);
        fxn.$$arg(2, 'exeName', $$T_Str, undefined);
        fxn.$$arg(3, 'pkgName', $$T_Str, undefined);
        fxn.$$arg(4, 'cfgScript', $$T_Str, undefined);
        fxn.$$arg(5, '__params', $om['xdc.tools.xgconf.configprovider.ConfigProvider.Params'], {});
    function ConfigProvider$$construct( __obj, fileName, exeName, pkgName, cfgScript, __params ) {
        var __mod = $om['xdc.tools.xgconf.configprovider.ConfigProvider'];
        var __inst = __obj;
        __inst.$$bind('$args', {fileName:fileName, exeName:exeName, pkgName:pkgName, cfgScript:cfgScript});
        __inst.$$bind('$module', __mod);
        __mod.$objects.$add(__inst);
        for (__p in __params) __inst[__p] = __params[__p];
        __inst.$$bless();
        return null;
    }
// module Main
    var fxn = $om.$$bind('xdc.tools.xgconf.configprovider.Main$$create', $$PFxn($om['xdc.tools.xgconf.configprovider.Main.Module'], $om['xdc.tools.xgconf.configprovider.Main.Instance'], 1, 0, false));
        fxn.$$arg(0, '__params', $om['xdc.tools.xgconf.configprovider.Main.Params'], {});
    function Main$$create( __params ) {
        var __mod = $om['xdc.tools.xgconf.configprovider.Main'];
        var __inst = $om['xdc.tools.xgconf.configprovider.Main.Instance'].$$make();
        __inst.$$bind('$package', $om['xdc.tools.xgconf.configprovider']);
        __inst.$$bind('$index', __mod.$instances.length);
        __inst.$$bind('$category', 'Instance');
        __inst.$$bind('$args', {});
        __inst.$$bind('$module', __mod);
        __mod.$instances.$add(__inst);
        for (__p in __params) __inst[__p] = __params[__p];
        var save = $om.$curpkg;
        $om.$$bind('$curpkg', __mod.$package.$name);
        __mod.instance$meta$init.$fxn.apply(__inst, []);
        $om.$$bind('$curpkg', save);
        __inst.$$bless();
        return __inst;
    }
    var fxn = $om.$$bind('xdc.tools.xgconf.configprovider.Main$$construct', $$PFxn($om['xdc.tools.xgconf.configprovider.Main.Module'], null, 2, 0, false));
        fxn.$$arg(0, '__obj', $om['xdc.tools.xgconf.configprovider.Main$$Object'], null);
        fxn.$$arg(1, '__params', $om['xdc.tools.xgconf.configprovider.Main.Params'], {});
    function Main$$construct( __obj, __params ) {
        var __mod = $om['xdc.tools.xgconf.configprovider.Main'];
        var __inst = __obj;
        __inst.$$bind('$args', {});
        __inst.$$bind('$module', __mod);
        __mod.$objects.$add(__inst);
        for (__p in __params) __inst[__p] = __params[__p];
        __inst.$$bless();
        return null;
    }
// module Contrib

/* ======== FUNCTIONS ======== */

// fxn ConfigProvider.loadCfgModel
    var fxn = $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider$$loadCfgModel', $$PFxn($om['xdc.tools.xgconf.configprovider.ConfigProvider.Instance'], $$T_Obj, 0, 0, false));
// fxn ConfigProvider.runCFFxn
    var fxn = $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider$$runCFFxn', $$PFxn($om['xdc.tools.xgconf.configprovider.ConfigProvider.Instance'], $$T_Obj, 6, 6, false));
        fxn.$$arg(0, 'mobjId', $$T_Str, undefined);
        fxn.$$arg(1, 'modinst', $$T_CNum('(xdc_Int)'), undefined);
        fxn.$$arg(2, 'fxn', $$T_Str, undefined);
        fxn.$$arg(3, 'op', $$T_CNum('(xdc_Int)'), undefined);
        fxn.$$arg(4, 'cfgparam', $$T_Str, undefined);
        fxn.$$arg(5, 'value', $$T_Str, undefined);
// fxn ConfigProvider.eval
    var fxn = $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider$$eval', $$PFxn($om['xdc.tools.xgconf.configprovider.ConfigProvider.Instance'], $$T_Obj, 1, 1, false));
        fxn.$$arg(0, 'expr', $$T_Str, undefined);
// fxn ConfigProvider._getValidateResults
    var fxn = $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider$$_getValidateResults', $$PFxn($om['xdc.tools.xgconf.configprovider.ConfigProvider.Instance'], $$T_Obj, 0, 0, false));
// fxn Main.addXGConfJars
    var fxn = $om.$$bind('xdc.tools.xgconf.configprovider.Main$$addXGConfJars', $$PFxn($om['xdc.tools.xgconf.configprovider.Main.Instance'], null, 0, 0, false));
// fxn Contrib.execConfig
    var fxn = $om.$$bind('xdc.tools.xgconf.configprovider.Contrib$$execConfig', $$PFxn($om['xdc.tools.xgconf.configprovider.Contrib.Module'], null, 0, -1, false));

/* ======== SIZES ======== */


/* ======== TYPES ======== */

// module ConfigProvider
    var cap = $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider$$capsule', xdc.loadCapsule('xdc/tools/xgconf/configprovider/ConfigProvider.xs'));
    var po = $om['xdc.tools.xgconf.configprovider.ConfigProvider.Module'].$$init('xdc.tools.xgconf.configprovider.ConfigProvider.Module', $$Module);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fxn('create', $om['xdc.tools.xgconf.configprovider.ConfigProvider$$create'], ConfigProvider$$create);
        po.$$fxn('construct', $om['xdc.tools.xgconf.configprovider.ConfigProvider$$construct'], ConfigProvider$$construct);
        var fxn = cap['module$meta$init'];
        if (fxn) $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider$$module$meta$init', true);
        if (fxn) po.$$fxn('module$meta$init', $$T_Met, fxn);
        var fxn = cap['instance$meta$init'];
        if (fxn) $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider$$instance$meta$init', true);
        if (fxn) po.$$fxn('instance$meta$init', $$T_Met, fxn);
    var po = $om['xdc.tools.xgconf.configprovider.ConfigProvider.Instance'].$$init('xdc.tools.xgconf.configprovider.ConfigProvider.Instance', $$Instance);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('breakAfterUserScript', $$T_Bool, false, 'wh');
        po.$$fxn('loadCfgModel', $om['xdc.tools.xgconf.configprovider.ConfigProvider$$loadCfgModel'], cap['loadCfgModel']);
        po.$$fxn('runCFFxn', $om['xdc.tools.xgconf.configprovider.ConfigProvider$$runCFFxn'], cap['runCFFxn']);
        po.$$fxn('eval', $om['xdc.tools.xgconf.configprovider.ConfigProvider$$eval'], cap['eval']);
        po.$$fxn('_getValidateResults', $om['xdc.tools.xgconf.configprovider.ConfigProvider$$_getValidateResults'], cap['_getValidateResults']);
    var po = $om['xdc.tools.xgconf.configprovider.ConfigProvider$$Params'].$$init('xdc.tools.xgconf.configprovider.ConfigProvider.Params', $$Params);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('breakAfterUserScript', $$T_Bool, false, 'wh');
    var po = $om['xdc.tools.xgconf.configprovider.ConfigProvider$$Object'].$$init('xdc.tools.xgconf.configprovider.ConfigProvider.Object', $om['xdc.tools.xgconf.configprovider.ConfigProvider.Instance']);
        po.$$fxn('loadCfgModel', $om['xdc.tools.xgconf.configprovider.ConfigProvider$$loadCfgModel'], cap['loadCfgModel']);
        po.$$fxn('runCFFxn', $om['xdc.tools.xgconf.configprovider.ConfigProvider$$runCFFxn'], cap['runCFFxn']);
        po.$$fxn('eval', $om['xdc.tools.xgconf.configprovider.ConfigProvider$$eval'], cap['eval']);
        po.$$fxn('_getValidateResults', $om['xdc.tools.xgconf.configprovider.ConfigProvider$$_getValidateResults'], cap['_getValidateResults']);
// typedef ConfigProvider.CFGFILTERFXN
    $om.$$bind('xdc.tools.xgconf.configprovider.ConfigProvider.CFGFILTERFXN', $$PAdr('xdc_Any(*)(xdc_Int,xdc_String,xdc_String)', 'PFa'));
// module Main
    var cap = $om.$$bind('xdc.tools.xgconf.configprovider.Main$$capsule', xdc.loadCapsule('xdc/tools/xgconf/configprovider/Main.xs'));
    var po = $om['xdc.tools.xgconf.configprovider.Main.Module'].$$init('xdc.tools.xgconf.configprovider.Main.Module', $om['xdc.tools.ICmd.Module']);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('usage', $$PArr($$T_Str, false), $$SO(['[-e executableName] [-s script] [-f fileName] packagename']), 'wh');
        po.$$fxn('create', $om['xdc.tools.xgconf.configprovider.Main$$create'], Main$$create);
        po.$$fxn('construct', $om['xdc.tools.xgconf.configprovider.Main$$construct'], Main$$construct);
        var fxn = cap['module$meta$init'];
        if (fxn) $om.$$bind('xdc.tools.xgconf.configprovider.Main$$module$meta$init', true);
        if (fxn) po.$$fxn('module$meta$init', $$T_Met, fxn);
        var fxn = cap['instance$meta$init'];
        if (fxn) $om.$$bind('xdc.tools.xgconf.configprovider.Main$$instance$meta$init', true);
        if (fxn) po.$$fxn('instance$meta$init', $$T_Met, fxn);
        if (cap['main']) po.$$fxn('main', $om['xdc.tools.ICmd$$main'], cap['main']);
        if (cap['exec']) po.$$fxn('exec', $om['xdc.tools.ICmd$$exec'], cap['exec']);
    var po = $om['xdc.tools.xgconf.configprovider.Main.Instance'].$$init('xdc.tools.xgconf.configprovider.Main.Instance', $om['xdc.tools.ICmd.Instance']);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('executableName', $$T_Str, null, 'wh');
        po.$$fld('cfgFileName', $$T_Str, null, 'wh');
        po.$$fld('cfgScript', $$T_Str, null, 'wh');
        if (cap['run']) po.$$fxn('run', $om['xdc.tools.ICmd$$run'], cap['run']);
        po.$$fxn('addXGConfJars', $om['xdc.tools.xgconf.configprovider.Main$$addXGConfJars'], cap['addXGConfJars']);
    var po = $om['xdc.tools.xgconf.configprovider.Main$$Params'].$$init('xdc.tools.xgconf.configprovider.Main.Params', $om['xdc.tools.ICmd$$Params']);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('executableName', $$T_Str, null, 'wh');
        po.$$fld('cfgFileName', $$T_Str, null, 'wh');
        po.$$fld('cfgScript', $$T_Str, null, 'wh');
    var po = $om['xdc.tools.xgconf.configprovider.Main$$Object'].$$init('xdc.tools.xgconf.configprovider.Main.Object', $om['xdc.tools.xgconf.configprovider.Main.Instance']);
        if (cap['run']) po.$$fxn('run', $om['xdc.tools.ICmd$$run'], cap['run']);
        po.$$fxn('addXGConfJars', $om['xdc.tools.xgconf.configprovider.Main$$addXGConfJars'], cap['addXGConfJars']);
// module Contrib
    var cap = $om.$$bind('xdc.tools.xgconf.configprovider.Contrib$$capsule', xdc.loadCapsule('xdc/tools/xgconf/configprovider/Contrib.xs'));
    var po = $om['xdc.tools.xgconf.configprovider.Contrib.Module'].$$init('xdc.tools.xgconf.configprovider.Contrib.Module', $$Module);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('breakAfterUserScript', $$T_Bool, false, 'wh');
        var fxn = cap['module$meta$init'];
        if (fxn) $om.$$bind('xdc.tools.xgconf.configprovider.Contrib$$module$meta$init', true);
        if (fxn) po.$$fxn('module$meta$init', $$T_Met, fxn);
        po.$$fxn('execConfig', $om['xdc.tools.xgconf.configprovider.Contrib$$execConfig'], cap['execConfig']);

/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package xdc.tools.xgconf.configprovider
    var po = $om['xdc.tools.xgconf.configprovider.Package'].$$init('xdc.tools.xgconf.configprovider.Package', $om['xdc.IPackage.Module']);
    po.$$bind('$capsule', undefined);
    var pkg = $om['xdc.tools.xgconf.configprovider'].$$init(po, 'xdc.tools.xgconf.configprovider', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'xdc.tools.xgconf.configprovider');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'xdc.tools.xgconf.configprovider.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', [1, 0, 0, 0]);
    pkg.$attr.$seal('length');
    pkg.$$bind('$imports', [
        ['xdc.tools', []],
        ['xdc.shelf', []],
        ['xdc.tools.xgconf.modeldata', []],
        ['xdc.services.spec', []],
    ]);
    if (pkg.$vers.length >= 3) {
        pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));
    }
    
    pkg.build.libraries = [
    ];
    
    pkg.build.libDesc = [
    ];
    if ('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {
    }
    
// module ConfigProvider
    var vo = $om['xdc.tools.xgconf.configprovider.ConfigProvider'];
    var po = $om['xdc.tools.xgconf.configprovider.ConfigProvider.Module'];
    vo.$$init(po, 'xdc.tools.xgconf.configprovider.ConfigProvider', $$DEFAULT, false);
    vo.$$bind('Module', po);
    vo.$$bind('$category', 'Module');
    vo.$$bind('$spec', xdc.$$ses.findUnit('xdc.tools.xgconf.configprovider.ConfigProvider'));
    vo.$$bind('$capsule', $om['xdc.tools.xgconf.configprovider.ConfigProvider$$capsule']);
    vo.$$bind('Instance', $om['xdc.tools.xgconf.configprovider.ConfigProvider.Instance']);
    vo.$$bind('Params', $om['xdc.tools.xgconf.configprovider.ConfigProvider.Params']);
    vo.$$bind('PARAMS', new vo.Params);
    vo.$$bind('$package', $om['xdc.tools.xgconf.configprovider']);
    vo.$$bind('$$tdefs', []);
    vo.$$bind('$$proxies', []);
    vo.$$bind('$$mcfgs', []);
    vo.$$bind('Ops', $om['xdc.tools.xgconf.configprovider.ConfigProvider.Ops']);
    vo.$$bind('CFGFILTERFXN', $om['xdc.tools.xgconf.configprovider.ConfigProvider.CFGFILTERFXN']);
    vo.$$bind('OP_GETVALUES', $om['xdc.tools.xgconf.configprovider.ConfigProvider.OP_GETVALUES']);
    vo.$$bind('OP_VALIDATE', $om['xdc.tools.xgconf.configprovider.ConfigProvider.OP_VALIDATE']);
    pkg.$modules.$add(vo);
    $om.$modules.$add(vo);
    vo.$$bind('$$instflag', 1);
    vo.$$bind('$$iobjflag', 1);
    vo.$$bind('$$sizeflag', 1);
    vo.$$bind('$$dlgflag', 0);
    vo.$$bind('$$iflag', 0);
    vo.$$bind('$$romcfgs', '|');
    if ('Module_State' in vo) vo.$$bind('$object', new vo.Module_State);
    vo.$$bind('$$meta_iobj', 0 + ('xdc.tools.xgconf.configprovider.ConfigProvider$$instance$static$init' in $om));
    vo.$$bind('$$fxntab', []);
    vo.$$bind('$$logEvtCfgs', []);
    vo.$$bind('$$errorDescCfgs', []);
    vo.$$bind('$$assertDescCfgs', []);
    vo.$attr.$seal('length');
    vo.$$bind('Object', $om['xdc.tools.xgconf.configprovider.ConfigProvider.Object']);
    pkg.$$bind('ConfigProvider', vo);
    pkg.$unitNames.$add('ConfigProvider');
// module Main
    var vo = $om['xdc.tools.xgconf.configprovider.Main'];
    var po = $om['xdc.tools.xgconf.configprovider.Main.Module'];
    vo.$$init(po, 'xdc.tools.xgconf.configprovider.Main', $$DEFAULT, false);
    vo.$$bind('Module', po);
    vo.$$bind('$category', 'Module');
    vo.$$bind('$spec', xdc.$$ses.findUnit('xdc.tools.xgconf.configprovider.Main'));
    vo.$$bind('$capsule', $om['xdc.tools.xgconf.configprovider.Main$$capsule']);
    vo.$$bind('Instance', $om['xdc.tools.xgconf.configprovider.Main.Instance']);
    vo.$$bind('Params', $om['xdc.tools.xgconf.configprovider.Main.Params']);
    vo.$$bind('PARAMS', new vo.Params);
    vo.$$bind('$package', $om['xdc.tools.xgconf.configprovider']);
    vo.$$bind('$$tdefs', []);
    vo.$$bind('$$proxies', []);
    vo.$$bind('$$mcfgs', []);
    pkg.$modules.$add(vo);
    $om.$modules.$add(vo);
    vo.$$bind('$$instflag', 1);
    vo.$$bind('$$iobjflag', 1);
    vo.$$bind('$$sizeflag', 1);
    vo.$$bind('$$dlgflag', 0);
    vo.$$bind('$$iflag', 1);
    vo.$$bind('$$romcfgs', '|');
    if ('Module_State' in vo) vo.$$bind('$object', new vo.Module_State);
    vo.$$bind('$$meta_iobj', 0 + ('xdc.tools.xgconf.configprovider.Main$$instance$static$init' in $om));
    vo.$$bind('$$fxntab', []);
    vo.$$bind('$$logEvtCfgs', []);
    vo.$$bind('$$errorDescCfgs', []);
    vo.$$bind('$$assertDescCfgs', []);
    vo.$attr.$seal('length');
    vo.$$bind('Object', $om['xdc.tools.xgconf.configprovider.Main.Object']);
    pkg.$$bind('Main', vo);
    pkg.$unitNames.$add('Main');
// module Contrib
    var vo = $om['xdc.tools.xgconf.configprovider.Contrib'];
    var po = $om['xdc.tools.xgconf.configprovider.Contrib.Module'];
    vo.$$init(po, 'xdc.tools.xgconf.configprovider.Contrib', $$DEFAULT, false);
    vo.$$bind('Module', po);
    vo.$$bind('$category', 'Module');
    vo.$$bind('$spec', xdc.$$ses.findUnit('xdc.tools.xgconf.configprovider.Contrib'));
    vo.$$bind('$capsule', $om['xdc.tools.xgconf.configprovider.Contrib$$capsule']);
    vo.$$bind('$package', $om['xdc.tools.xgconf.configprovider']);
    vo.$$bind('$$tdefs', []);
    vo.$$bind('$$proxies', []);
    vo.$$bind('$$mcfgs', []);
    pkg.$modules.$add(vo);
    $om.$modules.$add(vo);
    vo.$$bind('$$instflag', 0);
    vo.$$bind('$$iobjflag', 1);
    vo.$$bind('$$sizeflag', 1);
    vo.$$bind('$$dlgflag', 0);
    vo.$$bind('$$iflag', 0);
    vo.$$bind('$$romcfgs', '|');
    if ('Module_State' in vo) vo.$$bind('$object', new vo.Module_State);
    vo.$$bind('$$meta_iobj', 0 + ('xdc.tools.xgconf.configprovider.Contrib$$instance$static$init' in $om));
    vo.$$bind('$$fxntab', []);
    vo.$$bind('$$logEvtCfgs', []);
    vo.$$bind('$$errorDescCfgs', []);
    vo.$$bind('$$assertDescCfgs', []);
    vo.$attr.$seal('length');
    pkg.$$bind('Contrib', vo);
    pkg.$unitNames.$add('Contrib');

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    $om['xdc.tools.xgconf.configprovider.ConfigProvider'].module$meta$init();
    $om['xdc.tools.xgconf.configprovider.Main'].module$meta$init();
    $om['xdc.tools.xgconf.configprovider.Contrib'].module$meta$init();
    pkg.init();
    $om['xdc.tools.xgconf.configprovider.ConfigProvider'].$$bless();
    $om['xdc.tools.xgconf.configprovider.Main'].$$bless();
    $om['xdc.tools.xgconf.configprovider.Contrib'].$$bless();
