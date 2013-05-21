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

public class xdc_cfg
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
        Global.callFxn("loadPackage", xdcO, "xdc.services.global");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "xdc.platform");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("xdc.cfg.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("xdc.cfg", new Value.Obj("xdc.cfg", pkgP));
    }

    void Program$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.cfg.Program.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.cfg.Program", new Value.Obj("xdc.cfg.Program", po));
        pkgV.bind("Program", vo);
        // decls 
        spo = (Proto.Obj)om.bind("xdc.cfg.Program$$GenerationOptions", new Proto.Obj());
        om.bind("xdc.cfg.Program.GenerationOptions", new Proto.Str(spo, true));
        spo = (Proto.Obj)om.bind("xdc.cfg.Program$$SectionSpec", new Proto.Obj());
        om.bind("xdc.cfg.Program.SectionSpec", new Proto.Str(spo, true));
    }

    void Main$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.cfg.Main.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.cfg.Main", new Value.Obj("xdc.cfg.Main", po));
        pkgV.bind("Main", vo);
        // decls 
    }

    void Program$$CONSTS()
    {
        // module Program
    }

    void Main$$CONSTS()
    {
        // module Main
    }

    void Program$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Main$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Program$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Program.exportModule
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Program$$exportModule", new Proto.Fxn(om.findStrict("xdc.cfg.Program.Module", "xdc.cfg"), null, 1, 1, false));
                fxn.addArg(0, "modName", $$T_Str, $$UNDEF);
        // fxn Program.freezeRomConfig
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Program$$freezeRomConfig", new Proto.Fxn(om.findStrict("xdc.cfg.Program.Module", "xdc.cfg"), null, 2, 2, false));
                fxn.addArg(0, "modName", $$T_Str, $$UNDEF);
                fxn.addArg(1, "cfgName", $$T_Str, $$UNDEF);
        // fxn Program.freezeRomParams
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Program$$freezeRomParams", new Proto.Fxn(om.findStrict("xdc.cfg.Program.Module", "xdc.cfg"), null, 1, 1, false));
                fxn.addArg(0, "modName", $$T_Str, $$UNDEF);
        // fxn Program.frozenRomConfig
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Program$$frozenRomConfig", new Proto.Fxn(om.findStrict("xdc.cfg.Program.Module", "xdc.cfg"), $$T_Bool, 2, 2, false));
                fxn.addArg(0, "modName", $$T_Str, $$UNDEF);
                fxn.addArg(1, "cfgName", $$T_Str, $$UNDEF);
        // fxn Program.getSectMap
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Program$$getSectMap", new Proto.Fxn(om.findStrict("xdc.cfg.Program.Module", "xdc.cfg"), null, 0, -1, false));
        // fxn Program.importAssembly
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Program$$importAssembly", new Proto.Fxn(om.findStrict("xdc.cfg.Program.Module", "xdc.cfg"), null, 1, 1, false));
                fxn.addArg(0, "asmName", $$T_Str, $$UNDEF);
        // fxn Program.importRomAssembly
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Program$$importRomAssembly", new Proto.Fxn(om.findStrict("xdc.cfg.Program.Module", "xdc.cfg"), null, 1, 1, false));
                fxn.addArg(0, "romAsmName", $$T_Str, $$UNDEF);
        // fxn Program.patchRomFxn
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Program$$patchRomFxn", new Proto.Fxn(om.findStrict("xdc.cfg.Program.Module", "xdc.cfg"), null, 3, 3, false));
                fxn.addArg(0, "modName", $$T_Str, $$UNDEF);
                fxn.addArg(1, "fxnName", $$T_Str, $$UNDEF);
                fxn.addArg(2, "patchSym", $$T_Str, $$UNDEF);
        // fxn Program.targetModules
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Program$$targetModules", new Proto.Fxn(om.findStrict("xdc.cfg.Program.Module", "xdc.cfg"), null, 0, -1, false));
    }

    void Main$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Main.init
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Main$$init", new Proto.Fxn(om.findStrict("xdc.cfg.Main.Module", "xdc.cfg"), null, 0, 0, false));
        // fxn Main.setExecutable
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Main$$setExecutable", new Proto.Fxn(om.findStrict("xdc.cfg.Main.Module", "xdc.cfg"), $$T_Str, 2, 2, false));
                fxn.addArg(0, "cfgScript", $$T_Str, $$UNDEF);
                fxn.addArg(1, "pkgName", $$T_Str, $$UNDEF);
        // fxn Main.runStringCfg
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Main$$runStringCfg", new Proto.Fxn(om.findStrict("xdc.cfg.Main.Module", "xdc.cfg"), $$T_Str, 1, 1, false));
                fxn.addArg(0, "userScript", $$T_Str, $$UNDEF);
        // fxn Main.runCfg
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Main$$runCfg", new Proto.Fxn(om.findStrict("xdc.cfg.Main.Module", "xdc.cfg"), $$T_Str, 0, 0, false));
        // fxn Main.validate
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Main$$validate", new Proto.Fxn(om.findStrict("xdc.cfg.Main.Module", "xdc.cfg"), $$T_Str, 0, 0, false));
        // fxn Main.genFiles
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Main$$genFiles", new Proto.Fxn(om.findStrict("xdc.cfg.Main.Module", "xdc.cfg"), null, 2, 2, false));
                fxn.addArg(0, "executable", $$T_Obj, $$UNDEF);
                fxn.addArg(1, "prefix", $$T_Str, $$UNDEF);
        // fxn Main.main
        fxn = (Proto.Fxn)om.bind("xdc.cfg.Main$$main", new Proto.Fxn(om.findStrict("xdc.cfg.Main.Module", "xdc.cfg"), null, 0, -1, false));
    }

    void Program$$SIZES()
    {
    }

    void Main$$SIZES()
    {
    }

    void Program$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/cfg/Program.xs");
        om.bind("xdc.cfg.Program$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.cfg.Program.Module", "xdc.cfg");
        po.init("xdc.cfg.Program.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("gen", (Proto)om.findStrict("xdc.cfg.Program.GenerationOptions", "xdc.cfg"), $$DEFAULT, "wh");
                po.addFld("globalSection", $$T_Str, null, "wh");
                po.addFld("sysStack", Proto.Elm.newCNum("(xdc_UInt)"), 0x1000L, "wh");
                po.addFld("stack", Proto.Elm.newCNum("(xdc_UInt)"), 0x1000L, "wh");
                po.addFld("heap", Proto.Elm.newCNum("(xdc_UInt)"), 0x1000L, "wh");
                po.addFld("argSize", Proto.Elm.newCNum("(xdc_UInt)"), 0x200L, "wh");
                po.addFld("execCmd", $$T_Str, $$UNDEF, "wh");
                po.addFld("linkTemplate", $$T_Str, null, "wh");
                po.addFld("main", new Proto.Adr("xdc_Int(*)(xdc_Int,xdc_Char*[])", "PFn"), $$UNDEF, "wh");
                po.addFld("sectMap", new Proto.Map($$T_Obj), $$DEFAULT, "wh");
                po.addFld("system", $$T_Obj, $$UNDEF, "wh");
                po.addFld("name", $$T_Str, $$UNDEF, "wh");
                po.addFld("buildPackage", $$T_Str, $$UNDEF, "wh");
                po.addFld("endian", $$T_Str, null, "wh");
                po.addFld("codeModel", $$T_Str, null, "wh");
                po.addFld("dataModel", $$T_Str, null, "wh");
                po.addFld("build", $$T_Obj, $$UNDEF, "wh");
                po.addFld("cpu", (Proto)om.findStrict("xdc.platform.IExeContext.Instance", "xdc.cfg"), $$UNDEF, "wh");
                po.addFld("platformName", $$T_Str, $$UNDEF, "wh");
                po.addFld("platform", (Proto)om.findStrict("xdc.platform.IPlatform.Instance", "xdc.cfg"), $$UNDEF, "wh");
                po.addFld("global", new Proto.Map($$T_Obj), $$DEFAULT, "wh");
                po.addFld("symbol", new Proto.Map($$T_Obj), $$DEFAULT, "wh");
                po.addFld("fixedCodeAddr", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "wh");
                po.addFld("fixedDataAddr", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "wh");
                po.addFld("loadFixedDataAddr", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
                po.addFld("loadRom", $$T_Bool, false, "wh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.cfg.Program$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.cfg.Program$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.cfg.Program$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("exportModule", (Proto.Fxn)om.findStrict("xdc.cfg.Program$$exportModule", "xdc.cfg"), Global.get(cap, "exportModule"));
                po.addFxn("freezeRomConfig", (Proto.Fxn)om.findStrict("xdc.cfg.Program$$freezeRomConfig", "xdc.cfg"), Global.get(cap, "freezeRomConfig"));
                po.addFxn("freezeRomParams", (Proto.Fxn)om.findStrict("xdc.cfg.Program$$freezeRomParams", "xdc.cfg"), Global.get(cap, "freezeRomParams"));
                po.addFxn("frozenRomConfig", (Proto.Fxn)om.findStrict("xdc.cfg.Program$$frozenRomConfig", "xdc.cfg"), Global.get(cap, "frozenRomConfig"));
                po.addFxn("getSectMap", (Proto.Fxn)om.findStrict("xdc.cfg.Program$$getSectMap", "xdc.cfg"), Global.get(cap, "getSectMap"));
                po.addFxn("importAssembly", (Proto.Fxn)om.findStrict("xdc.cfg.Program$$importAssembly", "xdc.cfg"), Global.get(cap, "importAssembly"));
                po.addFxn("importRomAssembly", (Proto.Fxn)om.findStrict("xdc.cfg.Program$$importRomAssembly", "xdc.cfg"), Global.get(cap, "importRomAssembly"));
                po.addFxn("patchRomFxn", (Proto.Fxn)om.findStrict("xdc.cfg.Program$$patchRomFxn", "xdc.cfg"), Global.get(cap, "patchRomFxn"));
                po.addFxn("targetModules", (Proto.Fxn)om.findStrict("xdc.cfg.Program$$targetModules", "xdc.cfg"), Global.get(cap, "targetModules"));
        // struct Program.GenerationOptions
        po = (Proto.Obj)om.findStrict("xdc.cfg.Program$$GenerationOptions", "xdc.cfg");
        po.init("xdc.cfg.Program.GenerationOptions", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("debuggerFiles", $$T_Bool, $$UNDEF, "w");
        // struct Program.SectionSpec
        po = (Proto.Obj)om.findStrict("xdc.cfg.Program$$SectionSpec", "xdc.cfg");
        po.init("xdc.cfg.Program.SectionSpec", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("runSegment", $$T_Str, $$UNDEF, "w");
                po.addFld("loadSegment", $$T_Str, $$UNDEF, "w");
                po.addFld("runAddress", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("loadAddress", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("runAlign", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("loadAlign", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("type", $$T_Str, $$UNDEF, "w");
                po.addFld("fill", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
    }

    void Main$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/cfg/Main.xs");
        om.bind("xdc.cfg.Main$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.cfg.Main.Module", "xdc.cfg");
        po.init("xdc.cfg.Main.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.cfg.Main$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.cfg.Main$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.cfg.Main$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("init", (Proto.Fxn)om.findStrict("xdc.cfg.Main$$init", "xdc.cfg"), Global.get(cap, "init"));
                po.addFxn("setExecutable", (Proto.Fxn)om.findStrict("xdc.cfg.Main$$setExecutable", "xdc.cfg"), Global.get(cap, "setExecutable"));
                po.addFxn("runStringCfg", (Proto.Fxn)om.findStrict("xdc.cfg.Main$$runStringCfg", "xdc.cfg"), Global.get(cap, "runStringCfg"));
                po.addFxn("runCfg", (Proto.Fxn)om.findStrict("xdc.cfg.Main$$runCfg", "xdc.cfg"), Global.get(cap, "runCfg"));
                po.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.cfg.Main$$validate", "xdc.cfg"), Global.get(cap, "validate"));
                po.addFxn("genFiles", (Proto.Fxn)om.findStrict("xdc.cfg.Main$$genFiles", "xdc.cfg"), Global.get(cap, "genFiles"));
                po.addFxn("main", (Proto.Fxn)om.findStrict("xdc.cfg.Main$$main", "xdc.cfg"), Global.get(cap, "main"));
    }

    void Program$$ROV()
    {
    }

    void Main$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("xdc.cfg.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "xdc.cfg"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/cfg/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "xdc.cfg"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "xdc.cfg"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "xdc.cfg"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "xdc.cfg"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "xdc.cfg"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "xdc.cfg"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "xdc.cfg", Value.DEFAULT, false);
        pkgV.bind("$name", "xdc.cfg");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "xdc.cfg.");
        pkgV.bind("$vers", Global.newArray("1, 0, 2, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.services.global", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['xdc.cfg'];\n");
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

    void Program$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.cfg.Program", "xdc.cfg");
        po = (Proto.Obj)om.findStrict("xdc.cfg.Program.Module", "xdc.cfg");
        vo.init2(po, "xdc.cfg.Program", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.cfg.Program$$capsule", "xdc.cfg"));
        vo.bind("$package", om.findStrict("xdc.cfg", "xdc.cfg"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("GenerationOptions", om.findStrict("xdc.cfg.Program.GenerationOptions", "xdc.cfg"));
        tdefs.add(om.findStrict("xdc.cfg.Program.GenerationOptions", "xdc.cfg"));
        vo.bind("SectionSpec", om.findStrict("xdc.cfg.Program.SectionSpec", "xdc.cfg"));
        tdefs.add(om.findStrict("xdc.cfg.Program.SectionSpec", "xdc.cfg"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.cfg")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("xdc.cfg.Program$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Program.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Program.xdt");
        pkgV.bind("Program", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Program");
    }

    void Main$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.cfg.Main", "xdc.cfg");
        po = (Proto.Obj)om.findStrict("xdc.cfg.Main.Module", "xdc.cfg");
        vo.init2(po, "xdc.cfg.Main", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.cfg.Main$$capsule", "xdc.cfg"));
        vo.bind("$package", om.findStrict("xdc.cfg", "xdc.cfg"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.cfg")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("xdc.cfg.Main$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Main", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Main");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.cfg.Program", "xdc.cfg"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.cfg.Main", "xdc.cfg"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("xdc.cfg.Program")).bless();
        ((Value.Obj)om.getv("xdc.cfg.Main")).bless();
        ((Value.Arr)om.findStrict("$packages", "xdc.cfg")).add(pkgV);
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
        Program$$OBJECTS();
        Main$$OBJECTS();
        Program$$CONSTS();
        Main$$CONSTS();
        Program$$CREATES();
        Main$$CREATES();
        Program$$FUNCTIONS();
        Main$$FUNCTIONS();
        Program$$SIZES();
        Main$$SIZES();
        Program$$TYPES();
        Main$$TYPES();
        if (isROV) {
            Program$$ROV();
            Main$$ROV();
        }//isROV
        $$SINGLETONS();
        Program$$SINGLETONS();
        Main$$SINGLETONS();
        $$INITIALIZATION();
    }
}
