xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('ti.sdoarch.standards.pkg');

/* ======== IMPORTS ======== */

    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.runtime');

/* ======== OBJECTS ======== */

// package ti.sdoarch.standards.pkg
    var pkg = $om.$$bind('ti.sdoarch.standards.pkg.Package', $$PObj());
    $om.$$bind('ti.sdoarch.standards.pkg', $$VObj('ti.sdoarch.standards.pkg', pkg));
// interface IVersion
    var po = $om.$$bind('ti.sdoarch.standards.pkg.IVersion.Module', $$PObj());
    var vo = $om.$$bind('ti.sdoarch.standards.pkg.IVersion', $$VObj('ti.sdoarch.standards.pkg.IVersion', po));
    pkg.$$bind('IVersion', vo);

/* ======== CONSTS ======== */

// interface IVersion

/* ======== CREATES ======== */

// interface IVersion

/* ======== FUNCTIONS ======== */

// fxn IVersion.getString
    var fxn = $om.$$bind('ti.sdoarch.standards.pkg.IVersion$$getString', $$PFxn($om['ti.sdoarch.standards.pkg.IVersion.Module'], null, 0, -1, false));

/* ======== SIZES ======== */

// interface IVersion

/* ======== TYPES ======== */

// interface IVersion
    var cap = $om.$$bind('ti.sdoarch.standards.pkg.IVersion$$capsule', xdc.loadCapsule('ti/sdoarch/standards/pkg/IVersion.xs'));
    var po = $om['ti.sdoarch.standards.pkg.IVersion.Module'].$$init('ti.sdoarch.standards.pkg.IVersion.Module', $om['xdc.runtime.IModule.Module']);
        po.$$fld('$hostonly', $$T_Num, 0, 'r');
        po.$$fld('MAJOR', $$T_CNum('(xdc_UInt16)'), undefined, 'rh');
        po.$$fld('MINOR', $$T_CNum('(xdc_UInt16)'), undefined, 'rh');
        po.$$fld('PATCH', $$T_CNum('(xdc_UInt16)'), undefined, 'rh');
        po.$$fld('WIDTH', $$T_CNum('(xdc_UInt16)'), undefined, 'rh');
if (__CFG__) {
} // __CFG__
        var fxn = cap['module$meta$init'];
        if (fxn) $om.$$bind('ti.sdoarch.standards.pkg.IVersion$$module$meta$init', true);
        if (fxn) po.$$fxn('module$meta$init', $$T_Met, fxn);
        var fxn = cap['module$static$init'];
        if (fxn) $om.$$bind('ti.sdoarch.standards.pkg.IVersion$$module$static$init', true);
        if (fxn) po.$$fxn('module$static$init', $$T_Met, fxn);
        var fxn = cap['module$validate'];
        if (fxn) $om.$$bind('ti.sdoarch.standards.pkg.IVersion$$module$validate', true);
        if (fxn) po.$$fxn('module$validate', $$T_Met, fxn);
        if (cap['getString']) po.$$fxn('getString', $om['ti.sdoarch.standards.pkg.IVersion$$getString'], cap['getString']);

/* ======== ROV ======== */

if (__ROV__) {

// interface IVersion
    var mod = $om['ti.sdoarch.standards.pkg.IVersion'];
    mod.$$bind('$scanHandle', function(iaddr) {
        return Program._decoder.scanInst($om['ti.sdoarch.standards.pkg.IVersion'], iaddr);
    });
    mod.$$bind('$scanObject', function(iobj) {
        Program._decoder.scanObj($om['ti.sdoarch.standards.pkg.IVersion'], iobj);
    });

} // __ROV__

/* ======== SINGLETONS ======== */

// package ti.sdoarch.standards.pkg
    var po = $om['ti.sdoarch.standards.pkg.Package'].$$init('ti.sdoarch.standards.pkg.Package', $om['xdc.IPackage.Module']);
    po.$$bind('$capsule', undefined);
    var pkg = $om['ti.sdoarch.standards.pkg'].$$init(po, 'ti.sdoarch.standards.pkg', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'ti.sdoarch.standards.pkg');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'ti.sdoarch.standards.pkg.');
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
// interface IVersion
    var vo = $om['ti.sdoarch.standards.pkg.IVersion'];
    var po = $om['ti.sdoarch.standards.pkg.IVersion.Module'];
    vo.$$init(po, 'ti.sdoarch.standards.pkg.IVersion', $$DEFAULT, false);
    vo.$$bind('Module', po);
    vo.$$bind('$category', 'Interface');
    vo.$$bind('$spec', xdc.$$ses.findUnit('ti.sdoarch.standards.pkg.IVersion'));
    vo.$$bind('$capsule', $om['ti.sdoarch.standards.pkg.IVersion$$capsule']);
    vo.$$bind('$package', $om['ti.sdoarch.standards.pkg']);
    vo.$$bind('$$tdefs', []);
    vo.$$bind('$$proxies', []);
    pkg.$interfaces.$add(vo);
    pkg.$$bind('IVersion', vo);
    pkg.$unitNames.$add('IVersion');
    vo.$seal();

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    pkg.init();
    $om['ti.sdoarch.standards.pkg.IVersion'].$$bless();
