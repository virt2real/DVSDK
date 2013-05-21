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

public class ti_targets_rts5500
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
        pkgP = (Proto.Obj)om.bind("ti.targets.rts5500.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.targets.rts5500", new Value.Obj("ti.targets.rts5500", pkgP));
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.targets.rts5500.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.targets.rts5500"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/rts5500/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.targets.rts5500"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.targets.rts5500"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.targets.rts5500"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.targets.rts5500"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.targets.rts5500"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.targets.rts5500"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.targets.rts5500", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.targets.rts5500");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.targets.rts5500.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.runtime", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.targets.rts5500'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/boot.a55',\n");
            sb.append("'lib/ti.targets.rts5500.a55',\n");
            sb.append("'lib/boot.a55Pw',\n");
            sb.append("'lib/boot.a55Pb',\n");
            sb.append("'lib/boot.a55H',\n");
            sb.append("'lib/ti.targets.rts5500.a55H',\n");
            sb.append("'lib/ti.targets.rts5500.a55Pw',\n");
            sb.append("'lib/boot.a55L',\n");
            sb.append("'lib/ti.targets.rts5500.a55L',\n");
            sb.append("'lib/ti.targets.rts5500.a55Pb',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/boot.a55', {target: 'ti.targets.C55'}],\n");
            sb.append("['lib/ti.targets.rts5500.a55', {target: 'ti.targets.C55'}],\n");
            sb.append("['lib/boot.a55Pw', {target: 'ti.targets.C55P_word'}],\n");
            sb.append("['lib/boot.a55Pb', {target: 'ti.targets.C55P_byte'}],\n");
            sb.append("['lib/boot.a55H', {target: 'ti.targets.C55_huge'}],\n");
            sb.append("['lib/ti.targets.rts5500.a55H', {target: 'ti.targets.C55_huge'}],\n");
            sb.append("['lib/ti.targets.rts5500.a55Pw', {target: 'ti.targets.C55P_word'}],\n");
            sb.append("['lib/boot.a55L', {target: 'ti.targets.C55_large'}],\n");
            sb.append("['lib/ti.targets.rts5500.a55L', {target: 'ti.targets.C55_large'}],\n");
            sb.append("['lib/ti.targets.rts5500.a55Pb', {target: 'ti.targets.C55P_byte'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/boot.a55'].suffix = '55';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts5500.a55'].suffix = '55';\n");
            sb.append("pkg.build.libDesc['lib/boot.a55Pw'].suffix = '55Pw';\n");
            sb.append("pkg.build.libDesc['lib/boot.a55Pb'].suffix = '55Pb';\n");
            sb.append("pkg.build.libDesc['lib/boot.a55H'].suffix = '55H';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts5500.a55H'].suffix = '55H';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts5500.a55Pw'].suffix = '55Pw';\n");
            sb.append("pkg.build.libDesc['lib/boot.a55L'].suffix = '55L';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts5500.a55L'].suffix = '55L';\n");
            sb.append("pkg.build.libDesc['lib/ti.targets.rts5500.a55Pb'].suffix = '55Pb';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Arr)om.findStrict("$packages", "ti.targets.rts5500")).add(pkgV);
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
