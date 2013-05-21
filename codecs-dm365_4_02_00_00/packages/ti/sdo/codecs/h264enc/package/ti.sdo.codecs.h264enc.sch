xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('ti.sdo.codecs.h264enc');

/* ======== IMPORTS ======== */

    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');

/* ======== OBJECTS ======== */

// package ti.sdo.codecs.h264enc
    var pkg = $om.$$bind('ti.sdo.codecs.h264enc.Package', $$PObj());
    $om.$$bind('ti.sdo.codecs.h264enc', $$VObj('ti.sdo.codecs.h264enc', pkg));
// module H264ENC
    var po = $om.$$bind('ti.sdo.codecs.h264enc.H264ENC.Module', $$PObj());
    var vo = $om.$$bind('ti.sdo.codecs.h264enc.H264ENC', $$VObj('ti.sdo.codecs.h264enc.H264ENC', po));
    pkg.$$bind('H264ENC', vo);

/* ======== CONSTS ======== */

// module H264ENC

/* ======== CREATES ======== */

// module H264ENC

/* ======== FUNCTIONS ======== */


/* ======== SIZES ======== */


/* ======== TYPES ======== */

// module H264ENC
    var po = $om['ti.sdo.codecs.h264enc.H264ENC.Module'].$$init('ti.sdo.codecs.h264enc.H264ENC.Module', $$Module);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('watermark', $$T_Bool, false, 'wh');
        po.$$fld('codeSection', $$T_Str, undefined, 'wh');
        po.$$fld('udataSection', $$T_Str, undefined, 'wh');
        po.$$fld('dataSection', $$T_Str, undefined, 'wh');

/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package ti.sdo.codecs.h264enc
    var po = $om['ti.sdo.codecs.h264enc.Package'].$$init('ti.sdo.codecs.h264enc.Package', $om['xdc.IPackage.Module']);
    var cap = $om.$$bind('xdc.IPackage$$capsule', xdc.loadCapsule('ti/sdo/codecs/h264enc/package.xs'));
        if (cap['init']) po.$$fxn('init', $om['xdc.IPackage$$init'], cap['init']);
        if (cap['close']) po.$$fxn('close', $om['xdc.IPackage$$close'], cap['close']);
        if (cap['validate']) po.$$fxn('validate', $om['xdc.IPackage$$validate'], cap['validate']);
        if (cap['exit']) po.$$fxn('exit', $om['xdc.IPackage$$exit'], cap['exit']);
        if (cap['getLibs']) po.$$fxn('getLibs', $om['xdc.IPackage$$getLibs'], cap['getLibs']);
        if (cap['getSects']) po.$$fxn('getSects', $om['xdc.IPackage$$getSects'], cap['getSects']);
    po.$$bind('$capsule', cap);
    var pkg = $om['ti.sdo.codecs.h264enc'].$$init(po, 'ti.sdo.codecs.h264enc', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'ti.sdo.codecs.h264enc');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'ti.sdo.codecs.h264enc.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', [1, 0, 0]);
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
    
// module H264ENC
    var vo = $om['ti.sdo.codecs.h264enc.H264ENC'];
    var po = $om['ti.sdo.codecs.h264enc.H264ENC.Module'];
    vo.$$init(po, 'ti.sdo.codecs.h264enc.H264ENC', $$DEFAULT, false);
    vo.$$bind('Module', po);
    vo.$$bind('$category', 'Module');
    vo.$$bind('$spec', xdc.$$ses.findUnit('ti.sdo.codecs.h264enc.H264ENC'));
    vo.$$bind('$capsule', undefined);
    vo.$$bind('$package', $om['ti.sdo.codecs.h264enc']);
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
    vo.$$bind('$$meta_iobj', 0 + ('ti.sdo.codecs.h264enc.H264ENC$$instance$static$init' in $om));
    vo.$$bind('$$fxntab', []);
    vo.$$bind('$$logEvtCfgs', []);
    vo.$$bind('$$errorDescCfgs', []);
    vo.$$bind('$$assertDescCfgs', []);
    vo.$attr.$seal('length');
    pkg.$$bind('H264ENC', vo);
    pkg.$unitNames.$add('H264ENC');

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    $om['ti.sdo.codecs.h264enc.H264ENC'].module$meta$init();
    pkg.init();
    $om['ti.sdo.codecs.h264enc.H264ENC'].$$bless();
