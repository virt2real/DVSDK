xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('xdc.tools.configuro.ccs');

/* ======== IMPORTS ======== */

    xdc.loadPackage('xdc.tools.configuro');
    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.tools');

/* ======== OBJECTS ======== */

// package xdc.tools.configuro.ccs
    var pkg = $om.$$bind('xdc.tools.configuro.ccs.Package', $$PObj());
    $om.$$bind('xdc.tools.configuro.ccs', $$VObj('xdc.tools.configuro.ccs', pkg));
// module Main
    var po = $om.$$bind('xdc.tools.configuro.ccs.Main.Module', $$PObj());
    var vo = $om.$$bind('xdc.tools.configuro.ccs.Main', $$VObj('xdc.tools.configuro.ccs.Main', po));
    pkg.$$bind('Main', vo);
    $om.$$bind('xdc.tools.configuro.ccs.Main.Instance', $$PObj());
    $om.$$bind('xdc.tools.configuro.ccs.Main$$Object', $$PObj());
    $om.$$bind('xdc.tools.configuro.ccs.Main.Object', $$PStr($om['xdc.tools.configuro.ccs.Main$$Object'], true));
    $om.$$bind('xdc.tools.configuro.ccs.Main$$Params', $$PObj());
    $om.$$bind('xdc.tools.configuro.ccs.Main.Params', $$PStr($om['xdc.tools.configuro.ccs.Main$$Params'], true));

/* ======== CONSTS ======== */

// module Main

/* ======== CREATES ======== */

// module Main
    var fxn = $om.$$bind('xdc.tools.configuro.ccs.Main$$create', $$PFxn($om['xdc.tools.configuro.ccs.Main.Module'], $om['xdc.tools.configuro.ccs.Main.Instance'], 1, 0, false));
        fxn.$$arg(0, '__params', $om['xdc.tools.configuro.ccs.Main.Params'], {});
    function Main$$create( __params ) {
        var __mod = $om['xdc.tools.configuro.ccs.Main'];
        var __inst = $om['xdc.tools.configuro.ccs.Main.Instance'].$$make();
        __inst.$$bind('$package', $om['xdc.tools.configuro.ccs']);
        __inst.$$bind('$index', __mod.$instances.length);
        __inst.$$bind('$category', 'Instance');
        __inst.$$bind('$args', {});
        __inst.$$bind('$module', __mod);
        __mod.$instances.$add(__inst);
        for (__p in __params) __inst[__p] = __params[__p];
        __mod.instance$meta$init.$fxn.apply(__inst, []);
        __inst.$$bless();
        return __inst;
    }
    var fxn = $om.$$bind('xdc.tools.configuro.ccs.Main$$construct', $$PFxn($om['xdc.tools.configuro.ccs.Main.Module'], null, 2, 0, false));
        fxn.$$arg(0, '__obj', $om['xdc.tools.configuro.ccs.Main$$Object'], null);
        fxn.$$arg(1, '__params', $om['xdc.tools.configuro.ccs.Main.Params'], {});
    function Main$$construct( __obj, __params ) {
        var __mod = $om['xdc.tools.configuro.ccs.Main'];
        var __inst = __obj;
        __inst.$$bind('$args', {});
        __inst.$$bind('$module', __mod);
        __mod.$objects.$add(__inst);
        for (__p in __params) __inst[__p] = __params[__p];
        __inst.$$bless();
        return null;
    }

/* ======== FUNCTIONS ======== */

// fxn Main.gen
    var fxn = $om.$$bind('xdc.tools.configuro.ccs.Main$$gen', $$PFxn($om['xdc.tools.configuro.ccs.Main.Instance'], $$T_CNum('(xdc_Int)'), 1, 1, false));
        fxn.$$arg(0, 'infile', $$T_Str, undefined);

/* ======== SIZES ======== */

// module Main

/* ======== TYPES ======== */

// module Main
    var cap = $om.$$bind('xdc.tools.configuro.ccs.Main$$capsule', xdc.loadCapsule('xdc/tools/configuro/ccs/Main.xs'));
    var po = $om['xdc.tools.configuro.ccs.Main.Module'].$$init('xdc.tools.configuro.ccs.Main.Module', $om['xdc.tools.ICmd.Module']);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('usage', $$PArr($$T_Str, false), $$SO(['[-v|--help]', '[-@ optionsfile] [--xp xdcpath]', '[-b config_bld | -c codegen_dir | --cb]', '[-t target] [-p platform[:instance]] [-r profile]', '[-Dname=value] [--tcf] [--bios5]', '[-w|-x regexp]', '[-o outdir] infile.cfg']), 'wh');
        po.$$fxn('create', $om['xdc.tools.configuro.ccs.Main$$create'], Main$$create);
        po.$$fxn('construct', $om['xdc.tools.configuro.ccs.Main$$construct'], Main$$construct);
        var fxn = cap['module$meta$init'];
        if (fxn) $om.$$bind('xdc.tools.configuro.ccs.Main$$module$meta$init', true);
        if (fxn) po.$$fxn('module$meta$init', $$T_Met, fxn);
        var fxn = cap['instance$meta$init'];
        if (fxn) $om.$$bind('xdc.tools.configuro.ccs.Main$$instance$meta$init', true);
        if (fxn) po.$$fxn('instance$meta$init', $$T_Met, fxn);
        if (cap['main']) po.$$fxn('main', $om['xdc.tools.ICmd$$main'], cap['main']);
        if (cap['exec']) po.$$fxn('exec', $om['xdc.tools.ICmd$$exec'], cap['exec']);
    var po = $om['xdc.tools.configuro.ccs.Main.Instance'].$$init('xdc.tools.configuro.ccs.Main.Instance', $om['xdc.tools.ICmd.Instance']);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('xdcPath', $$PArr($$T_Str, false), $$SO([]), 'wh');
        po.$$fld('xdcPathsFile', $$T_Str, null, 'wh');
        po.$$fld('hasTconf', $$T_Bool, false, 'wh');
        po.$$fld('bios5Incs', $$T_Bool, false, 'wh');
        po.$$fld('output', $$T_Str, null, 'wh');
        po.$$fld('configbld', $$T_Str, null, 'wh');
        po.$$fld('searchForConfigBld', $$T_Bool, false, 'wh');
        po.$$fld('target', $$T_Str, null, 'wh');
        po.$$fld('profile', $$T_Str, 'release', 'wh');
        po.$$fld('platform', $$T_Str, null, 'wh');
        po.$$fld('rootdir', $$T_Str, null, 'wh');
        po.$$fld('verbose', $$T_Bool, false, 'wh');
        po.$$fld('exclude', $$T_Str, null, 'wh');
        po.$$fld('warn', $$T_Bool, false, 'wh');
        po.$$fld('defines', $$PArr($$T_Str, false), $$SO([]), 'wh');
        if (cap['run']) po.$$fxn('run', $om['xdc.tools.ICmd$$run'], cap['run']);
        po.$$fxn('gen', $om['xdc.tools.configuro.ccs.Main$$gen'], cap['gen']);
    var po = $om['xdc.tools.configuro.ccs.Main$$Params'].$$init('xdc.tools.configuro.ccs.Main.Params', $om['xdc.tools.ICmd$$Params']);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('xdcPath', $$PArr($$T_Str, false), $$SO([]), 'wh');
        po.$$fld('xdcPathsFile', $$T_Str, null, 'wh');
        po.$$fld('hasTconf', $$T_Bool, false, 'wh');
        po.$$fld('bios5Incs', $$T_Bool, false, 'wh');
        po.$$fld('output', $$T_Str, null, 'wh');
        po.$$fld('configbld', $$T_Str, null, 'wh');
        po.$$fld('searchForConfigBld', $$T_Bool, false, 'wh');
        po.$$fld('target', $$T_Str, null, 'wh');
        po.$$fld('profile', $$T_Str, 'release', 'wh');
        po.$$fld('platform', $$T_Str, null, 'wh');
        po.$$fld('rootdir', $$T_Str, null, 'wh');
        po.$$fld('verbose', $$T_Bool, false, 'wh');
        po.$$fld('exclude', $$T_Str, null, 'wh');
        po.$$fld('warn', $$T_Bool, false, 'wh');
        po.$$fld('defines', $$PArr($$T_Str, false), $$SO([]), 'wh');
    var po = $om['xdc.tools.configuro.ccs.Main$$Object'].$$init('xdc.tools.configuro.ccs.Main.Object', $om['xdc.tools.configuro.ccs.Main.Instance']);
        if (cap['run']) po.$$fxn('run', $om['xdc.tools.ICmd$$run'], cap['run']);
        po.$$fxn('gen', $om['xdc.tools.configuro.ccs.Main$$gen'], cap['gen']);

/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package xdc.tools.configuro.ccs
    var po = $om['xdc.tools.configuro.ccs.Package'].$$init('xdc.tools.configuro.ccs.Package', $om['xdc.IPackage.Module']);
    po.$$bind('$capsule', undefined);
    var pkg = $om['xdc.tools.configuro.ccs'].$$init(po, 'xdc.tools.configuro.ccs', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'xdc.tools.configuro.ccs');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'xdc.tools.configuro.ccs.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', [1, 0, 0, 0]);
    pkg.$attr.$seal('length');
    pkg.$$bind('$imports', [
        ['xdc.tools.configuro', []],
    ]);
    var $PKG = pkg;
    pkg.build.libraries = [
    ];
    
    pkg.build.libDesc = [
    ];
// module Main
    var vo = $om['xdc.tools.configuro.ccs.Main'];
    var po = $om['xdc.tools.configuro.ccs.Main.Module'];
    vo.$$init(po, 'xdc.tools.configuro.ccs.Main', $$DEFAULT, false);
    vo.$$bind('Module', po);
    vo.$$bind('$category', 'Module');
    vo.$$bind('$spec', xdc.$$ses.findUnit('xdc.tools.configuro.ccs.Main'));
    vo.$$bind('$capsule', $om['xdc.tools.configuro.ccs.Main$$capsule']);
    vo.$$bind('Instance', $om['xdc.tools.configuro.ccs.Main.Instance']);
    vo.$$bind('Params', $om['xdc.tools.configuro.ccs.Main.Params']);
    vo.$$bind('PARAMS', new vo.Params);
    vo.$$bind('$package', $om['xdc.tools.configuro.ccs']);
    vo.$$bind('$$tdefs', []);
    vo.$$bind('$$mcfgs', []);
    vo.$$bind('$$proxies', []);
    pkg.$modules.$add(vo);
    $om.$modules.$add(vo);
    vo.$$bind('$$instflag', 1);
    vo.$$bind('$$iobjflag', 1);
    vo.$$bind('$$sizeflag', 1);
    vo.$$bind('$$dlgflag', 0);
    vo.$$bind('$$iflag', 1);
    if ('Module_State' in vo) vo.$$bind('$object', new vo.Module_State);
    vo.$$bind('$$meta_iobj', 0 + ('xdc.tools.configuro.ccs.Main$$instance$static$init' in $om));
    vo.$$bind('$$fxntab', []);
    vo.$$bind('$$logEvtCfgs', []);
    vo.$attr.$seal('length');
    vo.$$bind('Object', $om['xdc.tools.configuro.ccs.Main.Object']);
    pkg.$$bind('Main', vo);
    pkg.$unitNames.$add('Main');

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    pkg.Main.module$meta$init();
    pkg.init();
    pkg.Main.$$bless();
