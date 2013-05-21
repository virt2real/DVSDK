xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('xdc.tools.xgconf.productview');

/* ======== IMPORTS ======== */

    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');
    xdc.loadPackage('xdc.tools');

/* ======== OBJECTS ======== */

// package xdc.tools.xgconf.productview
    var pkg = $om.$$bind('xdc.tools.xgconf.productview.Package', $$PObj());
    $om.$$bind('xdc.tools.xgconf.productview', $$VObj('xdc.tools.xgconf.productview', pkg));
// module Main
    var po = $om.$$bind('xdc.tools.xgconf.productview.Main.Module', $$PObj());
    var vo = $om.$$bind('xdc.tools.xgconf.productview.Main', $$VObj('xdc.tools.xgconf.productview.Main', po));
    pkg.$$bind('Main', vo);
    $om.$$bind('xdc.tools.xgconf.productview.Main.Instance', $$PObj());
    $om.$$bind('xdc.tools.xgconf.productview.Main$$Object', $$PObj());
    $om.$$bind('xdc.tools.xgconf.productview.Main.Object', $$PStr($om['xdc.tools.xgconf.productview.Main$$Object'], true));
    $om.$$bind('xdc.tools.xgconf.productview.Main$$Params', $$PObj());
    $om.$$bind('xdc.tools.xgconf.productview.Main.Params', $$PStr($om['xdc.tools.xgconf.productview.Main$$Params'], true));

/* ======== CONSTS ======== */

// module Main

/* ======== CREATES ======== */

// module Main
    var fxn = $om.$$bind('xdc.tools.xgconf.productview.Main$$create', $$PFxn($om['xdc.tools.xgconf.productview.Main.Module'], $om['xdc.tools.xgconf.productview.Main.Instance'], 1, 0, false));
        fxn.$$arg(0, '__params', $om['xdc.tools.xgconf.productview.Main.Params'], {});
    function Main$$create( __params ) {
        var __mod = $om['xdc.tools.xgconf.productview.Main'];
        var __inst = $om['xdc.tools.xgconf.productview.Main.Instance'].$$make();
        __inst.$$bind('$package', $om['xdc.tools.xgconf.productview']);
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
    var fxn = $om.$$bind('xdc.tools.xgconf.productview.Main$$construct', $$PFxn($om['xdc.tools.xgconf.productview.Main.Module'], null, 2, 0, false));
        fxn.$$arg(0, '__obj', $om['xdc.tools.xgconf.productview.Main$$Object'], null);
        fxn.$$arg(1, '__params', $om['xdc.tools.xgconf.productview.Main.Params'], {});
    function Main$$construct( __obj, __params ) {
        var __mod = $om['xdc.tools.xgconf.productview.Main'];
        var __inst = __obj;
        __inst.$$bind('$args', {});
        __inst.$$bind('$module', __mod);
        __mod.$objects.$add(__inst);
        for (__p in __params) __inst[__p] = __params[__p];
        __inst.$$bless();
        return null;
    }

/* ======== FUNCTIONS ======== */


/* ======== SIZES ======== */


/* ======== TYPES ======== */

// module Main
    var cap = $om.$$bind('xdc.tools.xgconf.productview.Main$$capsule', xdc.loadCapsule('xdc/tools/xgconf/productview/Main.xs'));
    var po = $om['xdc.tools.xgconf.productview.Main.Module'].$$init('xdc.tools.xgconf.productview.Main.Module', $om['xdc.tools.ICmd.Module']);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('usage', $$PArr($$T_Str, false), $$SO(['xs xdc.tools.xgconf.productview --packagePath <package_path> <productview module0> .. <productview moduleN>']), 'wh');
        po.$$fxn('create', $om['xdc.tools.xgconf.productview.Main$$create'], Main$$create);
        po.$$fxn('construct', $om['xdc.tools.xgconf.productview.Main$$construct'], Main$$construct);
        var fxn = cap['module$meta$init'];
        if (fxn) $om.$$bind('xdc.tools.xgconf.productview.Main$$module$meta$init', true);
        if (fxn) po.$$fxn('module$meta$init', $$T_Met, fxn);
        var fxn = cap['instance$meta$init'];
        if (fxn) $om.$$bind('xdc.tools.xgconf.productview.Main$$instance$meta$init', true);
        if (fxn) po.$$fxn('instance$meta$init', $$T_Met, fxn);
        if (cap['main']) po.$$fxn('main', $om['xdc.tools.ICmd$$main'], cap['main']);
        if (cap['exec']) po.$$fxn('exec', $om['xdc.tools.ICmd$$exec'], cap['exec']);
    var po = $om['xdc.tools.xgconf.productview.Main.Instance'].$$init('xdc.tools.xgconf.productview.Main.Instance', $om['xdc.tools.ICmd.Instance']);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('packagePath', $$T_Str, null, 'wh');
        if (cap['run']) po.$$fxn('run', $om['xdc.tools.ICmd$$run'], cap['run']);
    var po = $om['xdc.tools.xgconf.productview.Main$$Params'].$$init('xdc.tools.xgconf.productview.Main.Params', $om['xdc.tools.ICmd$$Params']);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('packagePath', $$T_Str, null, 'wh');
    var po = $om['xdc.tools.xgconf.productview.Main$$Object'].$$init('xdc.tools.xgconf.productview.Main.Object', $om['xdc.tools.xgconf.productview.Main.Instance']);
        if (cap['run']) po.$$fxn('run', $om['xdc.tools.ICmd$$run'], cap['run']);

/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package xdc.tools.xgconf.productview
    var po = $om['xdc.tools.xgconf.productview.Package'].$$init('xdc.tools.xgconf.productview.Package', $om['xdc.IPackage.Module']);
    po.$$bind('$capsule', undefined);
    var pkg = $om['xdc.tools.xgconf.productview'].$$init(po, 'xdc.tools.xgconf.productview', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'xdc.tools.xgconf.productview');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'xdc.tools.xgconf.productview.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', []);
    pkg.$attr.$seal('length');
    pkg.$$bind('$imports', [
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
    
// module Main
    var vo = $om['xdc.tools.xgconf.productview.Main'];
    var po = $om['xdc.tools.xgconf.productview.Main.Module'];
    vo.$$init(po, 'xdc.tools.xgconf.productview.Main', $$DEFAULT, false);
    vo.$$bind('Module', po);
    vo.$$bind('$category', 'Module');
    vo.$$bind('$spec', xdc.$$ses.findUnit('xdc.tools.xgconf.productview.Main'));
    vo.$$bind('$capsule', $om['xdc.tools.xgconf.productview.Main$$capsule']);
    vo.$$bind('Instance', $om['xdc.tools.xgconf.productview.Main.Instance']);
    vo.$$bind('Params', $om['xdc.tools.xgconf.productview.Main.Params']);
    vo.$$bind('PARAMS', new vo.Params);
    vo.$$bind('$package', $om['xdc.tools.xgconf.productview']);
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
    vo.$$bind('$$meta_iobj', 0 + ('xdc.tools.xgconf.productview.Main$$instance$static$init' in $om));
    vo.$$bind('$$fxntab', []);
    vo.$$bind('$$logEvtCfgs', []);
    vo.$$bind('$$errorDescCfgs', []);
    vo.$$bind('$$assertDescCfgs', []);
    vo.$attr.$seal('length');
    vo.$$bind('Object', $om['xdc.tools.xgconf.productview.Main.Object']);
    pkg.$$bind('Main', vo);
    pkg.$unitNames.$add('Main');

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    $om['xdc.tools.xgconf.productview.Main'].module$meta$init();
    pkg.init();
    $om['xdc.tools.xgconf.productview.Main'].$$bless();
