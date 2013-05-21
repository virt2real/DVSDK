/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-u17
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.*;

public class ti_targets_arm_rtsarm
{
    static final String VERS = "@(#) xdc-u17\n";

    static final Proto.Elm $$T_Bool = Proto.Elm.newBool();
    static final Proto.Elm $$T_Num = Proto.Elm.newNum();
    static final Proto.Elm $$T_Str = Proto.Elm.newStr();
    static final Proto.Elm $$T_Obj = Proto.Elm.newObj();

    static final Proto.Fxn $$T_Met = new Proto.Fxn(null, null, 0, -1, false);
    static final Proto.Map $$T_Map = new Proto.Map($$T_Obj);
    static final Proto.Arr $$T_Vec = new Proto.Arr($$T_Obj);

    static final XScriptO $$DEFAULT = Value.DEFAULT;
    static final Object $$UNDEF = Undefined.instance;

    static final Proto.Obj $$Package = (Proto.Obj)Global.get("$$Package");
    static final Proto.Obj $$Module = (Proto.Obj)Global.get("$$Module");
    static final Proto.Obj $$Instance = (Proto.Obj)Global.get("$$Instance");
    static final Proto.Obj $$Params = (Proto.Obj)Global.get("$$Params");

    static final Object $$objFldGet = Global.get("$$objFldGet");
    static final Object $$objFldSet = Global.get("$$objFldSet");
    static final Object $$proxyGet = Global.get("$$proxyGet");
    static final Object $$proxySet = Global.get("$$proxySet");
    static final Object $$delegGet = Global.get("$$delegGet");
    static final Object $$delegSet = Global.get("$$delegSet");

    Scriptable xdcO;
    Session ses;
    Value.Obj om;

    boolean isROV;
    boolean isCFG;

    Proto.Obj pkgP;
    Value.Obj pkgV;

    ArrayList<Object> imports = new ArrayList<Object>();
    ArrayList<Object> loggables = new ArrayList<Object>();
    ArrayList<Object> mcfgs = new ArrayList<Object>();
    ArrayList<Object> proxies = new ArrayList<Object>();
    ArrayList<Object> sizes = new ArrayList<Object>();
    ArrayList<Object> tdefs = new ArrayList<Object>();

    void $$IMPORTS()
    {
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.targets.arm.rtsarm.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.targets.arm.rtsarm", new Value.Obj("ti.targets.arm.rtsarm", pkgP));
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.targets.arm.rtsarm.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.targets.arm.rtsarm"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/arm/rtsarm/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.targets.arm.rtsarm"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.targets.arm.rtsarm"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.targets.arm.rtsarm"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.targets.arm.rtsarm"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.targets.arm.rtsarm"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.targets.arm.rtsarm"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.targets.arm.rtsarm", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.targets.arm.rtsarm");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.targets.arm.rtsarm.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.runtime", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.targets.arm.rtsarm'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/boot.aer4ft',\n");
            sb.append("'lib/boot.am3e',\n");
            sb.append("'lib/boot.ae470',\n");
            sb.append("'lib/boot.ae7',\n");
            sb.append("'lib/auto_init.ae7e',\n");
            sb.append("'lib/auto_init.ar4t',\n");
            sb.append("'lib/boot.ae9',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.a11',\n");
            sb.append("'lib/auto_init.ae7',\n");
            sb.append("'lib/auto_init.ae9',\n");
            sb.append("'lib/boot.ar4',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.aer4e',\n");
            sb.append("'lib/auto_init.ar4',\n");
            sb.append("'lib/boot.aer4te',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.aer4',\n");
            sb.append("'lib/boot.a9t',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.aer4t',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.ar4te',\n");
            sb.append("'lib/auto_init.a9t',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.a11e',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.aer4fe',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.ae9t',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.a7e',\n");
            sb.append("'lib/boot.am3',\n");
            sb.append("'lib/boot.ar4e',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.a7',\n");
            sb.append("'lib/auto_init.aem3e',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.a9',\n");
            sb.append("'lib/auto_init.aer4',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.aer4ft',\n");
            sb.append("'lib/auto_init.am3',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.aem3',\n");
            sb.append("'lib/boot.ar4t',\n");
            sb.append("'lib/boot.ae7e',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.ae470',\n");
            sb.append("'lib/auto_init.a11e',\n");
            sb.append("'lib/boot.aem3e',\n");
            sb.append("'lib/auto_init.ae9t',\n");
            sb.append("'lib/boot.a7',\n");
            sb.append("'lib/boot.a9',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.am3e',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.ae7',\n");
            sb.append("'lib/auto_init.aem3',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.ae9',\n");
            sb.append("'lib/boot.a11',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.aer4te',\n");
            sb.append("'lib/auto_init.aer4fe',\n");
            sb.append("'lib/auto_init.a11',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.ar4',\n");
            sb.append("'lib/auto_init.am3e',\n");
            sb.append("'lib/auto_init.aer4e',\n");
            sb.append("'lib/boot.aer4fte',\n");
            sb.append("'lib/auto_init.aer4ft',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.a9t',\n");
            sb.append("'lib/boot.aer4',\n");
            sb.append("'lib/auto_init.aer4t',\n");
            sb.append("'lib/auto_init.ar4te',\n");
            sb.append("'lib/boot.aer4e',\n");
            sb.append("'lib/boot.a11e',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.am3',\n");
            sb.append("'lib/boot.ae9t',\n");
            sb.append("'lib/boot.a7e',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.ar4e',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.aem3e',\n");
            sb.append("'lib/boot.aer4t',\n");
            sb.append("'lib/boot.ar4te',\n");
            sb.append("'lib/auto_init.a7e',\n");
            sb.append("'lib/auto_init.aer4te',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.ar4t',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.ae7e',\n");
            sb.append("'lib/ti.targets.arm.rtsarm.aer4fte',\n");
            sb.append("'lib/auto_init.aer4fte',\n");
            sb.append("'lib/boot.aem3',\n");
            sb.append("'lib/auto_init.ae470',\n");
            sb.append("'lib/boot.aer4fe',\n");
            sb.append("'lib/auto_init.a7',\n");
            sb.append("'lib/auto_init.a9',\n");
            sb.append("'lib/auto_init.ar4e',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/boot.aer4ft', {target: 'ti.targets.arm.elf.R4Ft'}],\n");
            sb.append("['lib/boot.am3e', {target: 'ti.targets.arm.M3_big_endian'}],\n");
            sb.append("['lib/boot.ae470', {target: 'ti.targets.elf.TMS470'}],\n");
            sb.append("['lib/boot.ae7', {target: 'ti.targets.arm.elf.Arm7'}],\n");
            sb.append("['lib/auto_init.ae7e', {target: 'ti.targets.arm.elf.Arm7_big_endian'}],\n");
            sb.append("['lib/auto_init.ar4t', {target: 'ti.targets.arm.R4t'}],\n");
            sb.append("['lib/boot.ae9', {target: 'ti.targets.arm.elf.Arm9'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.a11', {target: 'ti.targets.arm.Arm11'}],\n");
            sb.append("['lib/auto_init.ae7', {target: 'ti.targets.arm.elf.Arm7'}],\n");
            sb.append("['lib/auto_init.ae9', {target: 'ti.targets.arm.elf.Arm9'}],\n");
            sb.append("['lib/boot.ar4', {target: 'ti.targets.arm.R4'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.aer4e', {target: 'ti.targets.arm.elf.R4_big_endian'}],\n");
            sb.append("['lib/auto_init.ar4', {target: 'ti.targets.arm.R4'}],\n");
            sb.append("['lib/boot.aer4te', {target: 'ti.targets.arm.elf.R4t_big_endian'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.aer4', {target: 'ti.targets.arm.elf.R4'}],\n");
            sb.append("['lib/boot.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.aer4t', {target: 'ti.targets.arm.elf.R4t'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.ar4te', {target: 'ti.targets.arm.R4t_big_endian'}],\n");
            sb.append("['lib/auto_init.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.a11e', {target: 'ti.targets.arm.Arm11_big_endian'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.aer4fe', {target: 'ti.targets.arm.elf.R4F_big_endian'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.ae9t', {target: 'ti.targets.arm.elf.Arm9t'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.a7e', {target: 'ti.targets.arm.Arm7_big_endian'}],\n");
            sb.append("['lib/boot.am3', {target: 'ti.targets.arm.M3'}],\n");
            sb.append("['lib/boot.ar4e', {target: 'ti.targets.arm.R4_big_endian'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.a7', {target: 'ti.targets.arm.Arm7'}],\n");
            sb.append("['lib/auto_init.aem3e', {target: 'ti.targets.arm.elf.M3_big_endian'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.a9', {target: 'ti.targets.arm.Arm9'}],\n");
            sb.append("['lib/auto_init.aer4', {target: 'ti.targets.arm.elf.R4'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.aer4ft', {target: 'ti.targets.arm.elf.R4Ft'}],\n");
            sb.append("['lib/auto_init.am3', {target: 'ti.targets.arm.M3'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.aem3', {target: 'ti.targets.arm.elf.M3'}],\n");
            sb.append("['lib/boot.ar4t', {target: 'ti.targets.arm.R4t'}],\n");
            sb.append("['lib/boot.ae7e', {target: 'ti.targets.arm.elf.Arm7_big_endian'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.ae470', {target: 'ti.targets.elf.TMS470'}],\n");
            sb.append("['lib/auto_init.a11e', {target: 'ti.targets.arm.Arm11_big_endian'}],\n");
            sb.append("['lib/boot.aem3e', {target: 'ti.targets.arm.elf.M3_big_endian'}],\n");
            sb.append("['lib/auto_init.ae9t', {target: 'ti.targets.arm.elf.Arm9t'}],\n");
            sb.append("['lib/boot.a7', {target: 'ti.targets.arm.Arm7'}],\n");
            sb.append("['lib/boot.a9', {target: 'ti.targets.arm.Arm9'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.am3e', {target: 'ti.targets.arm.M3_big_endian'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.ae7', {target: 'ti.targets.arm.elf.Arm7'}],\n");
            sb.append("['lib/auto_init.aem3', {target: 'ti.targets.arm.elf.M3'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.ae9', {target: 'ti.targets.arm.elf.Arm9'}],\n");
            sb.append("['lib/boot.a11', {target: 'ti.targets.arm.Arm11'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.aer4te', {target: 'ti.targets.arm.elf.R4t_big_endian'}],\n");
            sb.append("['lib/auto_init.aer4fe', {target: 'ti.targets.arm.elf.R4F_big_endian'}],\n");
            sb.append("['lib/auto_init.a11', {target: 'ti.targets.arm.Arm11'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.ar4', {target: 'ti.targets.arm.R4'}],\n");
            sb.append("['lib/auto_init.am3e', {target: 'ti.targets.arm.M3_big_endian'}],\n");
            sb.append("['lib/auto_init.aer4e', {target: 'ti.targets.arm.elf.R4_big_endian'}],\n");
            sb.append("['lib/boot.aer4fte', {target: 'ti.targets.arm.elf.R4Ft_big_endian'}],\n");
            sb.append("['lib/auto_init.aer4ft', {target: 'ti.targets.arm.elf.R4Ft'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/boot.aer4', {target: 'ti.targets.arm.elf.R4'}],\n");
            sb.append("['lib/auto_init.aer4t', {target: 'ti.targets.arm.elf.R4t'}],\n");
            sb.append("['lib/auto_init.ar4te', {target: 'ti.targets.arm.R4t_big_endian'}],\n");
            sb.append("['lib/boot.aer4e', {target: 'ti.targets.arm.elf.R4_big_endian'}],\n");
            sb.append("['lib/boot.a11e', {target: 'ti.targets.arm.Arm11_big_endian'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.am3', {target: 'ti.targets.arm.M3'}],\n");
            sb.append("['lib/boot.ae9t', {target: 'ti.targets.arm.elf.Arm9t'}],\n");
            sb.append("['lib/boot.a7e', {target: 'ti.targets.arm.Arm7_big_endian'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.ar4e', {target: 'ti.targets.arm.R4_big_endian'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.aem3e', {target: 'ti.targets.arm.elf.M3_big_endian'}],\n");
            sb.append("['lib/boot.aer4t', {target: 'ti.targets.arm.elf.R4t'}],\n");
            sb.append("['lib/boot.ar4te', {target: 'ti.targets.arm.R4t_big_endian'}],\n");
            sb.append("['lib/auto_init.a7e', {target: 'ti.targets.arm.Arm7_big_endian'}],\n");
            sb.append("['lib/auto_init.aer4te', {target: 'ti.targets.arm.elf.R4t_big_endian'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.ar4t', {target: 'ti.targets.arm.R4t'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.ae7e', {target: 'ti.targets.arm.elf.Arm7_big_endian'}],\n");
            sb.append("['lib/ti.targets.arm.rtsarm.aer4fte', {target: 'ti.targets.arm.elf.R4Ft_big_endian'}],\n");
            sb.append("['lib/auto_init.aer4fte', {target: 'ti.targets.arm.elf.R4Ft_big_endian'}],\n");
            sb.append("['lib/boot.aem3', {target: 'ti.targets.arm.elf.M3'}],\n");
            sb.append("['lib/auto_init.ae470', {target: 'ti.targets.elf.TMS470'}],\n");
            sb.append("['lib/boot.aer4fe', {target: 'ti.targets.arm.elf.R4F_big_endian'}],\n");
            sb.append("['lib/auto_init.a7', {target: 'ti.targets.arm.Arm7'}],\n");
            sb.append("['lib/auto_init.a9', {target: 'ti.targets.arm.Arm9'}],\n");
            sb.append("['lib/auto_init.ar4e', {target: 'ti.targets.arm.R4_big_endian'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/boot.aer4ft'].suffix = 'er4ft';\n");
            sb.append("pkg.build.libDesc['lib/boot.am3e'].suffix = 'm3e';\n");
            sb.append("pkg.build.libDesc['lib/boot.ae470'].suffix = 'e470';\n");
            sb.append("pkg.build.libDesc['lib/boot.ae7'].suffix = 'e7';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.ae7e'].suffix = 'e7e';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.ar4t'].suffix = 'r4t';\n");
            sb.append("pkg.build.libDesc['lib/boot.ae9'].suffix = 'e9';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.a11'].suffix = '11';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.ae7'].suffix = 'e7';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.ae9'].suffix = 'e9';\n");
            sb.append("pkg.build.libDesc['lib/boot.ar4'].suffix = 'r4';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.aer4e'].suffix = 'er4e';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.ar4'].suffix = 'r4';\n");
            sb.append("pkg.build.libDesc['lib/boot.aer4te'].suffix = 'er4te';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.aer4'].suffix = 'er4';\n");
            sb.append("pkg.build.libDesc['lib/boot.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.aer4t'].suffix = 'er4t';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.ar4te'].suffix = 'r4te';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.a11e'].suffix = '11e';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.aer4fe'].suffix = 'er4fe';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.ae9t'].suffix = 'e9t';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.a7e'].suffix = '7e';\n");
            sb.append("pkg.build.libDesc['lib/boot.am3'].suffix = 'm3';\n");
            sb.append("pkg.build.libDesc['lib/boot.ar4e'].suffix = 'r4e';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.a7'].suffix = '7';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.aem3e'].suffix = 'em3e';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.a9'].suffix = '9';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.aer4'].suffix = 'er4';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.aer4ft'].suffix = 'er4ft';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.am3'].suffix = 'm3';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.aem3'].suffix = 'em3';\n");
            sb.append("pkg.build.libDesc['lib/boot.ar4t'].suffix = 'r4t';\n");
            sb.append("pkg.build.libDesc['lib/boot.ae7e'].suffix = 'e7e';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.ae470'].suffix = 'e470';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.a11e'].suffix = '11e';\n");
            sb.append("pkg.build.libDesc['lib/boot.aem3e'].suffix = 'em3e';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.ae9t'].suffix = 'e9t';\n");
            sb.append("pkg.build.libDesc['lib/boot.a7'].suffix = '7';\n");
            sb.append("pkg.build.libDesc['lib/boot.a9'].suffix = '9';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.am3e'].suffix = 'm3e';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.ae7'].suffix = 'e7';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.aem3'].suffix = 'em3';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.ae9'].suffix = 'e9';\n");
            sb.append("pkg.build.libDesc['lib/boot.a11'].suffix = '11';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.aer4te'].suffix = 'er4te';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.aer4fe'].suffix = 'er4fe';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.a11'].suffix = '11';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.ar4'].suffix = 'r4';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.am3e'].suffix = 'm3e';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.aer4e'].suffix = 'er4e';\n");
            sb.append("pkg.build.libDesc['lib/boot.aer4fte'].suffix = 'er4fte';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.aer4ft'].suffix = 'er4ft';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/boot.aer4'].suffix = 'er4';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.aer4t'].suffix = 'er4t';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.ar4te'].suffix = 'r4te';\n");
            sb.append("pkg.build.libDesc['lib/boot.aer4e'].suffix = 'er4e';\n");
            sb.append("pkg.build.libDesc['lib/boot.a11e'].suffix = '11e';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.am3'].suffix = 'm3';\n");
            sb.append("pkg.build.libDesc['lib/boot.ae9t'].suffix = 'e9t';\n");
            sb.append("pkg.build.libDesc['lib/boot.a7e'].suffix = '7e';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.ar4e'].suffix = 'r4e';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.aem3e'].suffix = 'em3e';\n");
            sb.append("pkg.build.libDesc['lib/boot.aer4t'].suffix = 'er4t';\n");
            sb.append("pkg.build.libDesc['lib/boot.ar4te'].suffix = 'r4te';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.a7e'].suffix = '7e';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.aer4te'].suffix = 'er4te';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.ar4t'].suffix = 'r4t';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.ae7e'].suffix = 'e7e';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.arm.rtsarm.aer4fte'].suffix = 'er4fte';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.aer4fte'].suffix = 'er4fte';\n");
            sb.append("pkg.build.libDesc['lib/boot.aem3'].suffix = 'em3';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.ae470'].suffix = 'e470';\n");
            sb.append("pkg.build.libDesc['lib/boot.aer4fe'].suffix = 'er4fe';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.a7'].suffix = '7';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.a9'].suffix = '9';\n");
            sb.append("pkg.build.libDesc['lib/auto_init.ar4e'].suffix = 'r4e';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Arr)om.findStrict("$packages", "ti.targets.arm.rtsarm")).add(pkgV);
    }

    public void exec( Scriptable xdcO, Session ses )
    {
        this.xdcO = xdcO;
        this.ses = ses;
        om = (Value.Obj)xdcO.get("om", null);

        Object o = om.geto("$name");
        String s = o instanceof String ? (String)o : null;
        isCFG = s != null && s.equals("cfg");
        isROV = s != null && s.equals("rov");

        $$IMPORTS();
        $$OBJECTS();
        if (isROV) {
        }//isROV
        $$SINGLETONS();
        $$INITIALIZATION();
    }
}
