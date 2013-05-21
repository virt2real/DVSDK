xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('xdc.tools.xgconf.modeldata');

/* ======== IMPORTS ======== */

    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');

/* ======== OBJECTS ======== */

// package xdc.tools.xgconf.modeldata
    var pkg = $om.$$bind('xdc.tools.xgconf.modeldata.Package', $$PObj());
    $om.$$bind('xdc.tools.xgconf.modeldata', $$VObj('xdc.tools.xgconf.modeldata', pkg));

/* ======== CONSTS ======== */


/* ======== CREATES ======== */


/* ======== FUNCTIONS ======== */


/* ======== SIZES ======== */


/* ======== TYPES ======== */


/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package xdc.tools.xgconf.modeldata
    var po = $om['xdc.tools.xgconf.modeldata.Package'].$$init('xdc.tools.xgconf.modeldata.Package', $om['xdc.IPackage.Module']);
    po.$$bind('$capsule', undefined);
    var pkg = $om['xdc.tools.xgconf.modeldata'].$$init(po, 'xdc.tools.xgconf.modeldata', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'xdc.tools.xgconf.modeldata');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'xdc.tools.xgconf.modeldata.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', [1, 0, 0, 0]);
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
    

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    pkg.init();
