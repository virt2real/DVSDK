xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('mp4vdecTestApp');

/* ======== IMPORTS ======== */

    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');

/* ======== OBJECTS ======== */

// package mp4vdecTestApp
    var pkg = $om.$$bind('mp4vdecTestApp.Package', $$PObj());
    $om.$$bind('mp4vdecTestApp', $$VObj('mp4vdecTestApp', pkg));

/* ======== CONSTS ======== */


/* ======== CREATES ======== */


/* ======== FUNCTIONS ======== */


/* ======== SIZES ======== */


/* ======== TYPES ======== */


/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package mp4vdecTestApp
    var po = $om['mp4vdecTestApp.Package'].$$init('mp4vdecTestApp.Package', $om['xdc.IPackage.Module']);
    var cap = $om.$$bind('xdc.IPackage$$capsule', xdc.loadCapsule('mp4vdecTestApp/package.xs'));
        if (cap['init']) po.$$fxn('init', $om['xdc.IPackage$$init'], cap['init']);
        if (cap['close']) po.$$fxn('close', $om['xdc.IPackage$$close'], cap['close']);
        if (cap['validate']) po.$$fxn('validate', $om['xdc.IPackage$$validate'], cap['validate']);
        if (cap['exit']) po.$$fxn('exit', $om['xdc.IPackage$$exit'], cap['exit']);
        if (cap['getLibs']) po.$$fxn('getLibs', $om['xdc.IPackage$$getLibs'], cap['getLibs']);
        if (cap['getSects']) po.$$fxn('getSects', $om['xdc.IPackage$$getSects'], cap['getSects']);
    po.$$bind('$capsule', cap);
    var pkg = $om['mp4vdecTestApp'].$$init(po, 'mp4vdecTestApp', $$DEFAULT, false);
    pkg.$$bind('$name', 'mp4vdecTestApp');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'mp4vdecTestApp.');
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
    

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    pkg.init();
    $om.$packages.$add(pkg);
