/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-u12
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.*;

public class ti_sdo_ce_wizards_genserver
{
    static final String VERS = "@(#) xdc-u12\n";

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
        Global.callFxn("loadPackage", xdcO, "xdc.tools.sg.widgets");
        Global.callFxn("loadPackage", xdcO, "xdc.tools");
        Global.callFxn("loadPackage", xdcO, "xdc.tools.mkpkg");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.wizards.genserver.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.wizards.genserver", new Value.Obj("ti.sdo.ce.wizards.genserver", pkgP));
    }

    void Main$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.wizards.genserver.Main.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.wizards.genserver.Main", new Value.Obj("ti.sdo.ce.wizards.genserver.Main", po));
        pkgV.bind("Main", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.sdo.ce.wizards.genserver.Main.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ce.wizards.genserver.Main$$Object", new Proto.Obj());
        Object objP = om.bind("ti.sdo.ce.wizards.genserver.Main.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.sdo.ce.wizards.genserver.Main$$Params", new Proto.Obj());
        om.bind("ti.sdo.ce.wizards.genserver.Main.Params", new Proto.Str(po, true));
    }

    void Gui$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.wizards.genserver.Gui.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.wizards.genserver.Gui", new Value.Obj("ti.sdo.ce.wizards.genserver.Gui", po));
        pkgV.bind("Gui", vo);
        // decls 
    }

    void Main$$CONSTS()
    {
        // module Main
    }

    void Gui$$CONSTS()
    {
        // module Gui
    }

    void Main$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.wizards.genserver.Main$$create", new Proto.Fxn(om.findStrict("ti.sdo.ce.wizards.genserver.Main.Module", "ti.sdo.ce.wizards.genserver"), om.findStrict("ti.sdo.ce.wizards.genserver.Main.Instance", "ti.sdo.ce.wizards.genserver"), 1, 0, false));
                fxn.addArg(0, "__params", (Proto)om.findStrict("ti.sdo.ce.wizards.genserver.Main.Params", "ti.sdo.ce.wizards.genserver"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$sdo$ce$wizards$genserver$Main$$create = function( __params ) {\n");
            sb.append("var __mod = xdc.om['ti.sdo.ce.wizards.genserver.Main'];\n");
            sb.append("var __inst = xdc.om['ti.sdo.ce.wizards.genserver.Main.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ce.wizards.genserver']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.wizards.genserver.Main$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ce.wizards.genserver.Main.Module", "ti.sdo.ce.wizards.genserver"), null, 2, 0, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ce.wizards.genserver.Main$$Object", "ti.sdo.ce.wizards.genserver"), null);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.sdo.ce.wizards.genserver.Main.Params", "ti.sdo.ce.wizards.genserver"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$sdo$ce$wizards$genserver$Main$$construct = function( __obj, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.sdo.ce.wizards.genserver.Main'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Gui$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Main$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Gui$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Gui.createPartControl
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.wizards.genserver.Gui$$createPartControl", new Proto.Fxn(om.findStrict("ti.sdo.ce.wizards.genserver.Gui.Module", "ti.sdo.ce.wizards.genserver"), null, 0, -1, false));
    }

    void Main$$SIZES()
    {
    }

    void Gui$$SIZES()
    {
    }

    void Main$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/wizards/genserver/Main.xs");
        om.bind("ti.sdo.ce.wizards.genserver.Main$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.wizards.genserver.Main.Module", "ti.sdo.ce.wizards.genserver");
        po.init("ti.sdo.ce.wizards.genserver.Main.Module", om.findStrict("xdc.tools.ICmd.Module", "ti.sdo.ce.wizards.genserver"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("usage", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"[-g] [-f <file> | --xml <file>] [--cgtools <cgtools dir>] [-d <destination dir>]"}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ce.wizards.genserver.Main$$create", "ti.sdo.ce.wizards.genserver"), Global.get("ti$sdo$ce$wizards$genserver$Main$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ce.wizards.genserver.Main$$construct", "ti.sdo.ce.wizards.genserver"), Global.get("ti$sdo$ce$wizards$genserver$Main$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.sdo.ce.wizards.genserver.Main$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.sdo.ce.wizards.genserver.Main$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.sdo.ce.wizards.genserver.Main$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.sdo.ce.wizards.genserver.Main$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "main");
                if (fxn != null) po.addFxn("main", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$main", "ti.sdo.ce.wizards.genserver"), fxn);
                fxn = Global.get(cap, "exec");
                if (fxn != null) po.addFxn("exec", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$exec", "ti.sdo.ce.wizards.genserver"), fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.wizards.genserver.Main.Instance", "ti.sdo.ce.wizards.genserver");
        po.init("ti.sdo.ce.wizards.genserver.Main.Instance", om.findStrict("xdc.tools.ICmd.Instance", "ti.sdo.ce.wizards.genserver"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("gui", $$T_Bool, false, "wh");
                po.addFld("cgTools", $$T_Str, null, "wh");
                po.addFld("destDir", $$T_Str, null, "wh");
                po.addFld("xmlFile", $$T_Str, null, "wh");
                po.addFld("debugFlag", $$T_Bool, false, "wh");
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$run", "ti.sdo.ce.wizards.genserver"), fxn);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.wizards.genserver.Main$$Params", "ti.sdo.ce.wizards.genserver");
        po.init("ti.sdo.ce.wizards.genserver.Main.Params", om.findStrict("xdc.tools.ICmd$$Params", "ti.sdo.ce.wizards.genserver"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("gui", $$T_Bool, false, "wh");
                po.addFld("cgTools", $$T_Str, null, "wh");
                po.addFld("destDir", $$T_Str, null, "wh");
                po.addFld("xmlFile", $$T_Str, null, "wh");
                po.addFld("debugFlag", $$T_Bool, false, "wh");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.wizards.genserver.Main$$Object", "ti.sdo.ce.wizards.genserver");
        po.init("ti.sdo.ce.wizards.genserver.Main.Object", om.findStrict("ti.sdo.ce.wizards.genserver.Main.Instance", "ti.sdo.ce.wizards.genserver"));
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$run", "ti.sdo.ce.wizards.genserver"), fxn);
    }

    void Gui$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/wizards/genserver/Gui.xs");
        om.bind("ti.sdo.ce.wizards.genserver.Gui$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.wizards.genserver.Gui.Module", "ti.sdo.ce.wizards.genserver");
        po.init("ti.sdo.ce.wizards.genserver.Gui.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.sdo.ce.wizards.genserver.Gui$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.sdo.ce.wizards.genserver.Gui$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.sdo.ce.wizards.genserver.Gui$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("createPartControl", (Proto.Fxn)om.findStrict("ti.sdo.ce.wizards.genserver.Gui$$createPartControl", "ti.sdo.ce.wizards.genserver"), Global.get(cap, "createPartControl"));
    }

    void Main$$ROV()
    {
    }

    void Gui$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.wizards.genserver.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.wizards.genserver"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "ti.sdo.ce.wizards.genserver", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.wizards.genserver");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.wizards.genserver.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.tools.sg.widgets", Global.newArray()));
        imports.add(Global.newArray("xdc.tools", Global.newArray()));
        imports.add(Global.newArray("xdc.tools.mkpkg", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.wizards.genserver'];\n");
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

    void Main$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.wizards.genserver.Main", "ti.sdo.ce.wizards.genserver");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.wizards.genserver.Main.Module", "ti.sdo.ce.wizards.genserver");
        vo.init2(po, "ti.sdo.ce.wizards.genserver.Main", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.wizards.genserver.Main$$capsule", "ti.sdo.ce.wizards.genserver"));
        vo.bind("Instance", om.findStrict("ti.sdo.ce.wizards.genserver.Main.Instance", "ti.sdo.ce.wizards.genserver"));
        vo.bind("Params", om.findStrict("ti.sdo.ce.wizards.genserver.Main.Params", "ti.sdo.ce.wizards.genserver"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ce.wizards.genserver.Main.Params", "ti.sdo.ce.wizards.genserver")).newInstance());
        vo.bind("$package", om.findStrict("ti.sdo.ce.wizards.genserver", "ti.sdo.ce.wizards.genserver"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.wizards.genserver")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.wizards.genserver.Main$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ce.wizards.genserver.Main.Object", "ti.sdo.ce.wizards.genserver"));
        pkgV.bind("Main", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Main");
    }

    void Gui$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.wizards.genserver.Gui", "ti.sdo.ce.wizards.genserver");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.wizards.genserver.Gui.Module", "ti.sdo.ce.wizards.genserver");
        vo.init2(po, "ti.sdo.ce.wizards.genserver.Gui", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.wizards.genserver.Gui$$capsule", "ti.sdo.ce.wizards.genserver"));
        vo.bind("$package", om.findStrict("ti.sdo.ce.wizards.genserver", "ti.sdo.ce.wizards.genserver"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.wizards.genserver")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.wizards.genserver.Gui$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Gui", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Gui");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.wizards.genserver.Main", "ti.sdo.ce.wizards.genserver"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.wizards.genserver.Gui", "ti.sdo.ce.wizards.genserver"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.wizards.genserver.Main")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.wizards.genserver.Gui")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.wizards.genserver")).add(pkgV);
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
        Main$$OBJECTS();
        Gui$$OBJECTS();
        Main$$CONSTS();
        Gui$$CONSTS();
        Main$$CREATES();
        Gui$$CREATES();
        Main$$FUNCTIONS();
        Gui$$FUNCTIONS();
        Main$$SIZES();
        Gui$$SIZES();
        Main$$TYPES();
        Gui$$TYPES();
        if (isROV) {
            Main$$ROV();
            Gui$$ROV();
        }//isROV
        $$SINGLETONS();
        Main$$SINGLETONS();
        Gui$$SINGLETONS();
        $$INITIALIZATION();
    }
}
