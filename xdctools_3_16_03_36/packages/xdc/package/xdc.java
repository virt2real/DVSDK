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

public class xdc
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
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("xdc.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("xdc", new Value.Obj("xdc", pkgP));
    }

    void IPackage$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.IPackage.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.IPackage", new Value.Obj("xdc.IPackage", po));
        pkgV.bind("IPackage", vo);
        // decls 
        spo = (Proto.Obj)om.bind("xdc.IPackage$$LibDesc", new Proto.Obj());
        om.bind("xdc.IPackage.LibDesc", new Proto.Str(spo, true));
        spo = (Proto.Obj)om.bind("xdc.IPackage$$BuildAttrs", new Proto.Obj());
        om.bind("xdc.IPackage.BuildAttrs", new Proto.Str(spo, true));
    }

    void IPackage$$CONSTS()
    {
        // interface IPackage
    }

    void IPackage$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IPackage$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn IPackage.init
        fxn = (Proto.Fxn)om.bind("xdc.IPackage$$init", new Proto.Fxn(om.findStrict("xdc.IPackage.Module", "xdc"), null, 0, -1, false));
        // fxn IPackage.close
        fxn = (Proto.Fxn)om.bind("xdc.IPackage$$close", new Proto.Fxn(om.findStrict("xdc.IPackage.Module", "xdc"), null, 0, -1, false));
        // fxn IPackage.validate
        fxn = (Proto.Fxn)om.bind("xdc.IPackage$$validate", new Proto.Fxn(om.findStrict("xdc.IPackage.Module", "xdc"), null, 0, -1, false));
        // fxn IPackage.exit
        fxn = (Proto.Fxn)om.bind("xdc.IPackage$$exit", new Proto.Fxn(om.findStrict("xdc.IPackage.Module", "xdc"), null, 0, -1, false));
        // fxn IPackage.getLibs
        fxn = (Proto.Fxn)om.bind("xdc.IPackage$$getLibs", new Proto.Fxn(om.findStrict("xdc.IPackage.Module", "xdc"), null, 0, -1, false));
        // fxn IPackage.getSects
        fxn = (Proto.Fxn)om.bind("xdc.IPackage$$getSects", new Proto.Fxn(om.findStrict("xdc.IPackage.Module", "xdc"), null, 0, -1, false));
    }

    void IPackage$$SIZES()
    {
    }

    void IPackage$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/IPackage.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.IPackage.Module", "xdc");
        po.init("xdc.IPackage.Module", $$Package);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("packageBase", $$T_Str, $$UNDEF, "wh");
                po.addFld("packageRepository", $$T_Str, $$UNDEF, "wh");
                po.addFld("build", (Proto)om.findStrict("xdc.IPackage.BuildAttrs", "xdc"), $$DEFAULT, "wh");
                po.addFld("profile", $$T_Str, $$UNDEF, "wh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.IPackage$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.IPackage$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.IPackage$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "init");
                if (fxn != null) po.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "xdc"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) po.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "xdc"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) po.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "xdc"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) po.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "xdc"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) po.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "xdc"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) po.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "xdc"), fxn);
        // struct IPackage.LibDesc
        po = (Proto.Obj)om.findStrict("xdc.IPackage$$LibDesc", "xdc");
        po.init("xdc.IPackage.LibDesc", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("target", $$T_Str, $$UNDEF, "w");
                po.addFld("suffix", $$T_Str, $$UNDEF, "w");
        // struct IPackage.BuildAttrs
        po = (Proto.Obj)om.findStrict("xdc.IPackage$$BuildAttrs", "xdc");
        po.init("xdc.IPackage.BuildAttrs", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("libraries", new Proto.Arr($$T_Str, false), $$DEFAULT, "w");
                po.addFld("libDesc", new Proto.Map((Proto)om.findStrict("xdc.IPackage.LibDesc", "xdc")), $$DEFAULT, "w");
                po.addFld("getLibs", $$T_Obj, $$UNDEF, "w");
    }

    void IPackage$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("xdc.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "xdc"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "xdc"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "xdc"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "xdc"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "xdc"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "xdc"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "xdc"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "xdc", Value.DEFAULT, false);
        pkgV.bind("$name", "xdc");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "xdc.");
        pkgV.bind("$vers", Global.newArray("1, 1, 1"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['xdc'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void IPackage$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.IPackage", "xdc");
        po = (Proto.Obj)om.findStrict("xdc.IPackage.Module", "xdc");
        vo.init2(po, "xdc.IPackage", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", om.findStrict("xdc.IPackage$$capsule", "xdc"));
        vo.bind("$package", om.findStrict("xdc", "xdc"));
        tdefs.clear();
        proxies.clear();
        vo.bind("LibDesc", om.findStrict("xdc.IPackage.LibDesc", "xdc"));
        tdefs.add(om.findStrict("xdc.IPackage.LibDesc", "xdc"));
        vo.bind("BuildAttrs", om.findStrict("xdc.IPackage.BuildAttrs", "xdc"));
        tdefs.add(om.findStrict("xdc.IPackage.BuildAttrs", "xdc"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IPackage", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IPackage");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("xdc.IPackage")).bless();
        ((Value.Arr)om.findStrict("$packages", "xdc")).add(pkgV);
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
        IPackage$$OBJECTS();
        IPackage$$CONSTS();
        IPackage$$CREATES();
        IPackage$$FUNCTIONS();
        IPackage$$SIZES();
        IPackage$$TYPES();
        if (isROV) {
            IPackage$$ROV();
        }//isROV
        $$SINGLETONS();
        IPackage$$SINGLETONS();
        $$INITIALIZATION();
    }
}
