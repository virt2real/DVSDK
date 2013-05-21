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

public class ti_targets_rts6000
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
        pkgP = (Proto.Obj)om.bind("ti.targets.rts6000.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.targets.rts6000", new Value.Obj("ti.targets.rts6000", pkgP));
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.targets.rts6000.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.targets.rts6000"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/rts6000/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.targets.rts6000"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.targets.rts6000"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.targets.rts6000"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.targets.rts6000"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.targets.rts6000"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.targets.rts6000"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.targets.rts6000", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.targets.rts6000");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.targets.rts6000.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.runtime", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.targets.rts6000'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/ti.targets.rts6000.ae64T',\n");
            sb.append("'lib/ti.targets.rts6000.a67e',\n");
            sb.append("'lib/ti.targets.rts6000.a64e',\n");
            sb.append("'lib/boot.ae67P',\n");
            sb.append("'lib/boot.ae64P',\n");
            sb.append("'lib/boot.a674',\n");
            sb.append("'lib/boot.ae64T',\n");
            sb.append("'lib/ti.targets.rts6000.a62',\n");
            sb.append("'lib/ti.targets.rts6000.a64',\n");
            sb.append("'lib/ti.targets.rts6000.a67',\n");
            sb.append("'lib/ti.targets.rts6000.a64Pe',\n");
            sb.append("'lib/boot.a67P',\n");
            sb.append("'lib/boot.a64P',\n");
            sb.append("'lib/ti.targets.rts6000.a62e',\n");
            sb.append("'lib/boot.a64T',\n");
            sb.append("'lib/ti.targets.rts6000.ae64Pe',\n");
            sb.append("'lib/boot.a64Pe',\n");
            sb.append("'lib/ti.targets.rts6000.a674',\n");
            sb.append("'lib/boot.a62',\n");
            sb.append("'lib/ti.targets.rts6000.a674e',\n");
            sb.append("'lib/boot.a64',\n");
            sb.append("'lib/boot.ae64Pe',\n");
            sb.append("'lib/boot.a67e',\n");
            sb.append("'lib/boot.a67',\n");
            sb.append("'lib/boot.a64e',\n");
            sb.append("'lib/ti.targets.rts6000.ae674',\n");
            sb.append("'lib/ti.targets.rts6000.a64Te',\n");
            sb.append("'lib/ti.targets.rts6000.ae674e',\n");
            sb.append("'lib/boot.a674e',\n");
            sb.append("'lib/boot.ae674',\n");
            sb.append("'lib/ti.targets.rts6000.ae64Te',\n");
            sb.append("'lib/boot.a64Te',\n");
            sb.append("'lib/ti.targets.rts6000.a67P',\n");
            sb.append("'lib/boot.ae674e',\n");
            sb.append("'lib/ti.targets.rts6000.a64P',\n");
            sb.append("'lib/ti.targets.rts6000.a64T',\n");
            sb.append("'lib/boot.ae64Te',\n");
            sb.append("'lib/ti.targets.rts6000.ae67P',\n");
            sb.append("'lib/ti.targets.rts6000.ae64P',\n");
            sb.append("'lib/boot.a62e',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/ti.targets.rts6000.ae64T', {target: 'ti.targets.elf.C64T'}],\n");
            sb.append("['lib/ti.targets.rts6000.a67e', {target: 'ti.targets.C67_big_endian'}],\n");
            sb.append("['lib/ti.targets.rts6000.a64e', {target: 'ti.targets.C64_big_endian'}],\n");
            sb.append("['lib/boot.ae67P', {target: 'ti.targets.elf.C67P'}],\n");
            sb.append("['lib/boot.ae64P', {target: 'ti.targets.elf.C64P'}],\n");
            sb.append("['lib/boot.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/boot.ae64T', {target: 'ti.targets.elf.C64T'}],\n");
            sb.append("['lib/ti.targets.rts6000.a62', {target: 'ti.targets.C62'}],\n");
            sb.append("['lib/ti.targets.rts6000.a64', {target: 'ti.targets.C64'}],\n");
            sb.append("['lib/ti.targets.rts6000.a67', {target: 'ti.targets.C67'}],\n");
            sb.append("['lib/ti.targets.rts6000.a64Pe', {target: 'ti.targets.C64P_big_endian'}],\n");
            sb.append("['lib/boot.a67P', {target: 'ti.targets.C67P'}],\n");
            sb.append("['lib/boot.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/ti.targets.rts6000.a62e', {target: 'ti.targets.C62_big_endian'}],\n");
            sb.append("['lib/boot.a64T', {target: 'ti.targets.C64T'}],\n");
            sb.append("['lib/ti.targets.rts6000.ae64Pe', {target: 'ti.targets.elf.C64P_big_endian'}],\n");
            sb.append("['lib/boot.a64Pe', {target: 'ti.targets.C64P_big_endian'}],\n");
            sb.append("['lib/ti.targets.rts6000.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/boot.a62', {target: 'ti.targets.C62'}],\n");
            sb.append("['lib/ti.targets.rts6000.a674e', {target: 'ti.targets.C674_big_endian'}],\n");
            sb.append("['lib/boot.a64', {target: 'ti.targets.C64'}],\n");
            sb.append("['lib/boot.ae64Pe', {target: 'ti.targets.elf.C64P_big_endian'}],\n");
            sb.append("['lib/boot.a67e', {target: 'ti.targets.C67_big_endian'}],\n");
            sb.append("['lib/boot.a67', {target: 'ti.targets.C67'}],\n");
            sb.append("['lib/boot.a64e', {target: 'ti.targets.C64_big_endian'}],\n");
            sb.append("['lib/ti.targets.rts6000.ae674', {target: 'ti.targets.elf.C674'}],\n");
            sb.append("['lib/ti.targets.rts6000.a64Te', {target: 'ti.targets.C64T_big_endian'}],\n");
            sb.append("['lib/ti.targets.rts6000.ae674e', {target: 'ti.targets.elf.C674_big_endian'}],\n");
            sb.append("['lib/boot.a674e', {target: 'ti.targets.C674_big_endian'}],\n");
            sb.append("['lib/boot.ae674', {target: 'ti.targets.elf.C674'}],\n");
            sb.append("['lib/ti.targets.rts6000.ae64Te', {target: 'ti.targets.elf.C64T_big_endian'}],\n");
            sb.append("['lib/boot.a64Te', {target: 'ti.targets.C64T_big_endian'}],\n");
            sb.append("['lib/ti.targets.rts6000.a67P', {target: 'ti.targets.C67P'}],\n");
            sb.append("['lib/boot.ae674e', {target: 'ti.targets.elf.C674_big_endian'}],\n");
            sb.append("['lib/ti.targets.rts6000.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/ti.targets.rts6000.a64T', {target: 'ti.targets.C64T'}],\n");
            sb.append("['lib/boot.ae64Te', {target: 'ti.targets.elf.C64T_big_endian'}],\n");
            sb.append("['lib/ti.targets.rts6000.ae67P', {target: 'ti.targets.elf.C67P'}],\n");
            sb.append("['lib/ti.targets.rts6000.ae64P', {target: 'ti.targets.elf.C64P'}],\n");
            sb.append("['lib/boot.a62e', {target: 'ti.targets.C62_big_endian'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.ae64T'].suffix = 'e64T';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.a67e'].suffix = '67e';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.a64e'].suffix = '64e';\n");
            sb.append("pkg.build.libDesc['lib/boot.ae67P'].suffix = 'e67P';\n");
            sb.append("pkg.build.libDesc['lib/boot.ae64P'].suffix = 'e64P';\n");
            sb.append("pkg.build.libDesc['lib/boot.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/boot.ae64T'].suffix = 'e64T';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.a62'].suffix = '62';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.a64'].suffix = '64';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.a67'].suffix = '67';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.a64Pe'].suffix = '64Pe';\n");
            sb.append("pkg.build.libDesc['lib/boot.a67P'].suffix = '67P';\n");
            sb.append("pkg.build.libDesc['lib/boot.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.a62e'].suffix = '62e';\n");
            sb.append("pkg.build.libDesc['lib/boot.a64T'].suffix = '64T';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.ae64Pe'].suffix = 'e64Pe';\n");
            sb.append("pkg.build.libDesc['lib/boot.a64Pe'].suffix = '64Pe';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/boot.a62'].suffix = '62';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.a674e'].suffix = '674e';\n");
            sb.append("pkg.build.libDesc['lib/boot.a64'].suffix = '64';\n");
            sb.append("pkg.build.libDesc['lib/boot.ae64Pe'].suffix = 'e64Pe';\n");
            sb.append("pkg.build.libDesc['lib/boot.a67e'].suffix = '67e';\n");
            sb.append("pkg.build.libDesc['lib/boot.a67'].suffix = '67';\n");
            sb.append("pkg.build.libDesc['lib/boot.a64e'].suffix = '64e';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.ae674'].suffix = 'e674';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.a64Te'].suffix = '64Te';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.ae674e'].suffix = 'e674e';\n");
            sb.append("pkg.build.libDesc['lib/boot.a674e'].suffix = '674e';\n");
            sb.append("pkg.build.libDesc['lib/boot.ae674'].suffix = 'e674';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.ae64Te'].suffix = 'e64Te';\n");
            sb.append("pkg.build.libDesc['lib/boot.a64Te'].suffix = '64Te';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.a67P'].suffix = '67P';\n");
            sb.append("pkg.build.libDesc['lib/boot.ae674e'].suffix = 'e674e';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.a64T'].suffix = '64T';\n");
            sb.append("pkg.build.libDesc['lib/boot.ae64Te'].suffix = 'e64Te';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.ae67P'].suffix = 'e67P';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts6000.ae64P'].suffix = 'e64P';\n");
            sb.append("pkg.build.libDesc['lib/boot.a62e'].suffix = '62e';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Arr)om.findStrict("$packages", "ti.targets.rts6000")).add(pkgV);
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
