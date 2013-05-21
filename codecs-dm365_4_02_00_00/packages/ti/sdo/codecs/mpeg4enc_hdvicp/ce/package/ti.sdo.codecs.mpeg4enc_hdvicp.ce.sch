xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('ti.sdo.codecs.mpeg4enc_hdvicp.ce');

/* ======== IMPORTS ======== */

    xdc.loadPackage('ti.sdo.ce.video1');
    xdc.loadPackage('ti.sdo.codecs.mpeg4enc_hdvicp');
    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');

/* ======== OBJECTS ======== */

// package ti.sdo.codecs.mpeg4enc_hdvicp.ce
    var pkg = $om.$$bind('ti.sdo.codecs.mpeg4enc_hdvicp.ce.Package', $$PObj());
    $om.$$bind('ti.sdo.codecs.mpeg4enc_hdvicp.ce', $$VObj('ti.sdo.codecs.mpeg4enc_hdvicp.ce', pkg));
// module MPEG4ENC_HDVICP
    var po = $om.$$bind('ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP.Module', $$PObj());
    var vo = $om.$$bind('ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP', $$VObj('ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP', po));
    pkg.$$bind('MPEG4ENC_HDVICP', vo);

/* ======== CONSTS ======== */

// module MPEG4ENC_HDVICP

/* ======== CREATES ======== */

// module MPEG4ENC_HDVICP

/* ======== FUNCTIONS ======== */


/* ======== SIZES ======== */


/* ======== TYPES ======== */

// module MPEG4ENC_HDVICP
    var cap = $om.$$bind('ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP$$capsule', xdc.loadCapsule('ti/sdo/codecs/mpeg4enc_hdvicp/ce/MPEG4ENC_HDVICP.xs'));
    var po = $om['ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP.Module'].$$init('ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP.Module', $om['ti.sdo.ce.video1.IVIDENC1.Module']);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('alg', $om['ti.sdo.codecs.mpeg4enc_hdvicp.MPEG4ENC_HDVICP.Module'], $om['ti.sdo.codecs.mpeg4enc_hdvicp.MPEG4ENC_HDVICP'], 'rh');
        po.$$fld('ialgFxns', $$T_Str, "MPEG4VENC_TI_IMPEG4VENC", 'rh');
        po.$$fld('iresFxns', $$T_Str, "MPEG4VENC_TI_IRES", 'rh');
        var fxn = cap['module$meta$init'];
        if (fxn) $om.$$bind('ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP$$module$meta$init', true);
        if (fxn) po.$$fxn('module$meta$init', $$T_Met, fxn);
        if (cap['getCreationStackSize']) po.$$fxn('getCreationStackSize', $om['ti.sdo.ce.ICodec$$getCreationStackSize'], cap['getCreationStackSize']);
        if (cap['getDaramScratchSize']) po.$$fxn('getDaramScratchSize', $om['ti.sdo.ce.ICodec$$getDaramScratchSize'], cap['getDaramScratchSize']);
        if (cap['getSaramScratchSize']) po.$$fxn('getSaramScratchSize', $om['ti.sdo.ce.ICodec$$getSaramScratchSize'], cap['getSaramScratchSize']);
        if (cap['getStackSize']) po.$$fxn('getStackSize', $om['ti.sdo.ce.ICodec$$getStackSize'], cap['getStackSize']);
        if (cap['getUUID']) po.$$fxn('getUUID', $om['ti.sdo.ce.ICodec$$getUUID'], cap['getUUID']);

/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package ti.sdo.codecs.mpeg4enc_hdvicp.ce
    var po = $om['ti.sdo.codecs.mpeg4enc_hdvicp.ce.Package'].$$init('ti.sdo.codecs.mpeg4enc_hdvicp.ce.Package', $om['xdc.IPackage.Module']);
    po.$$bind('$capsule', undefined);
    var pkg = $om['ti.sdo.codecs.mpeg4enc_hdvicp.ce'].$$init(po, 'ti.sdo.codecs.mpeg4enc_hdvicp.ce', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'ti.sdo.codecs.mpeg4enc_hdvicp.ce');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'ti.sdo.codecs.mpeg4enc_hdvicp.ce.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', [1, 0, 0]);
    pkg.$attr.$seal('length');
    pkg.$$bind('$imports', [
        ['ti.sdo.ce.video1', []],
        ['ti.sdo.codecs.mpeg4enc_hdvicp', []],
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
    
// module MPEG4ENC_HDVICP
    var vo = $om['ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP'];
    var po = $om['ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP.Module'];
    vo.$$init(po, 'ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP', $$DEFAULT, false);
    vo.$$bind('Module', po);
    vo.$$bind('$category', 'Module');
    vo.$$bind('$spec', xdc.$$ses.findUnit('ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP'));
    vo.$$bind('$capsule', $om['ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP$$capsule']);
    vo.$$bind('$package', $om['ti.sdo.codecs.mpeg4enc_hdvicp.ce']);
    vo.$$bind('$$tdefs', []);
    vo.$$bind('$$proxies', []);
    vo.$$bind('$$mcfgs', []);
    pkg.$modules.$add(vo);
    $om.$modules.$add(vo);
    vo.$$bind('$$instflag', 0);
    vo.$$bind('$$iobjflag', 1);
    vo.$$bind('$$sizeflag', 1);
    vo.$$bind('$$dlgflag', 0);
    vo.$$bind('$$iflag', 1);
    vo.$$bind('$$romcfgs', '|');
    if ('Module_State' in vo) vo.$$bind('$object', new vo.Module_State);
    vo.$$bind('$$meta_iobj', 0 + ('ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP$$instance$static$init' in $om));
    vo.$$bind('$$fxntab', []);
    vo.$$bind('$$logEvtCfgs', []);
    vo.$$bind('$$errorDescCfgs', []);
    vo.$$bind('$$assertDescCfgs', []);
    vo.$attr.$seal('length');
    pkg.$$bind('MPEG4ENC_HDVICP', vo);
    pkg.$unitNames.$add('MPEG4ENC_HDVICP');

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    $om['ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP'].module$meta$init();
    pkg.init();
    $om['ti.sdo.codecs.mpeg4enc_hdvicp.ce.MPEG4ENC_HDVICP'].$$bless();
