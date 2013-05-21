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

public class gnu_targets
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
        Global.callFxn("loadPackage", xdcO, "xdc.bld");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("gnu.targets.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("gnu.targets", new Value.Obj("gnu.targets", pkgP));
    }

    void ITarget$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("gnu.targets.ITarget.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("gnu.targets.ITarget", new Value.Obj("gnu.targets.ITarget", po));
        pkgV.bind("ITarget", vo);
        // decls 
        om.bind("gnu.targets.ITarget.Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        om.bind("gnu.targets.ITarget.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        om.bind("gnu.targets.ITarget.Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        om.bind("gnu.targets.ITarget.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        om.bind("gnu.targets.ITarget.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        om.bind("gnu.targets.ITarget.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        om.bind("gnu.targets.ITarget.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        om.bind("gnu.targets.ITarget.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        om.bind("gnu.targets.ITarget.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        om.bind("gnu.targets.ITarget.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        om.bind("gnu.targets.ITarget.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        spo = (Proto.Obj)om.bind("gnu.targets.ITarget$$Command", new Proto.Obj());
        om.bind("gnu.targets.ITarget.Command", new Proto.Str(spo, true));
        spo = (Proto.Obj)om.bind("gnu.targets.ITarget$$Options", new Proto.Obj());
        om.bind("gnu.targets.ITarget.Options", new Proto.Str(spo, true));
    }

    void Sparc$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("gnu.targets.Sparc.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("gnu.targets.Sparc", new Value.Obj("gnu.targets.Sparc", po));
        pkgV.bind("Sparc", vo);
        // decls 
        om.bind("gnu.targets.Sparc.Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        om.bind("gnu.targets.Sparc.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        om.bind("gnu.targets.Sparc.Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        om.bind("gnu.targets.Sparc.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        om.bind("gnu.targets.Sparc.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        om.bind("gnu.targets.Sparc.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        om.bind("gnu.targets.Sparc.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        om.bind("gnu.targets.Sparc.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        om.bind("gnu.targets.Sparc.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        om.bind("gnu.targets.Sparc.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        om.bind("gnu.targets.Sparc.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        om.bind("gnu.targets.Sparc.Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        om.bind("gnu.targets.Sparc.Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
    }

    void Linux86$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("gnu.targets.Linux86.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("gnu.targets.Linux86", new Value.Obj("gnu.targets.Linux86", po));
        pkgV.bind("Linux86", vo);
        // decls 
        om.bind("gnu.targets.Linux86.Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        om.bind("gnu.targets.Linux86.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        om.bind("gnu.targets.Linux86.Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        om.bind("gnu.targets.Linux86.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        om.bind("gnu.targets.Linux86.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        om.bind("gnu.targets.Linux86.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        om.bind("gnu.targets.Linux86.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        om.bind("gnu.targets.Linux86.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        om.bind("gnu.targets.Linux86.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        om.bind("gnu.targets.Linux86.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        om.bind("gnu.targets.Linux86.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        om.bind("gnu.targets.Linux86.Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        om.bind("gnu.targets.Linux86.Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
    }

    void Mingw$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("gnu.targets.Mingw.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("gnu.targets.Mingw", new Value.Obj("gnu.targets.Mingw", po));
        pkgV.bind("Mingw", vo);
        // decls 
        om.bind("gnu.targets.Mingw.Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        om.bind("gnu.targets.Mingw.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        om.bind("gnu.targets.Mingw.Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        om.bind("gnu.targets.Mingw.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        om.bind("gnu.targets.Mingw.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        om.bind("gnu.targets.Mingw.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        om.bind("gnu.targets.Mingw.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        om.bind("gnu.targets.Mingw.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        om.bind("gnu.targets.Mingw.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        om.bind("gnu.targets.Mingw.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        om.bind("gnu.targets.Mingw.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        om.bind("gnu.targets.Mingw.Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        om.bind("gnu.targets.Mingw.Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
    }

    void MVArm9$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("gnu.targets.MVArm9.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("gnu.targets.MVArm9", new Value.Obj("gnu.targets.MVArm9", po));
        pkgV.bind("MVArm9", vo);
        // decls 
        om.bind("gnu.targets.MVArm9.Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        om.bind("gnu.targets.MVArm9.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        om.bind("gnu.targets.MVArm9.Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        om.bind("gnu.targets.MVArm9.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        om.bind("gnu.targets.MVArm9.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        om.bind("gnu.targets.MVArm9.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        om.bind("gnu.targets.MVArm9.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        om.bind("gnu.targets.MVArm9.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        om.bind("gnu.targets.MVArm9.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        om.bind("gnu.targets.MVArm9.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        om.bind("gnu.targets.MVArm9.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        om.bind("gnu.targets.MVArm9.Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        om.bind("gnu.targets.MVArm9.Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
    }

    void UCArm9$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("gnu.targets.UCArm9.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("gnu.targets.UCArm9", new Value.Obj("gnu.targets.UCArm9", po));
        pkgV.bind("UCArm9", vo);
        // decls 
        om.bind("gnu.targets.UCArm9.Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        om.bind("gnu.targets.UCArm9.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        om.bind("gnu.targets.UCArm9.Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        om.bind("gnu.targets.UCArm9.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        om.bind("gnu.targets.UCArm9.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        om.bind("gnu.targets.UCArm9.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        om.bind("gnu.targets.UCArm9.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        om.bind("gnu.targets.UCArm9.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        om.bind("gnu.targets.UCArm9.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        om.bind("gnu.targets.UCArm9.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        om.bind("gnu.targets.UCArm9.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        om.bind("gnu.targets.UCArm9.Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        om.bind("gnu.targets.UCArm9.Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
    }

    void ITarget$$CONSTS()
    {
        // interface ITarget
    }

    void Sparc$$CONSTS()
    {
        // module Sparc
    }

    void Linux86$$CONSTS()
    {
        // module Linux86
    }

    void Mingw$$CONSTS()
    {
        // module Mingw
    }

    void MVArm9$$CONSTS()
    {
        // module MVArm9
    }

    void UCArm9$$CONSTS()
    {
        // module UCArm9
    }

    void ITarget$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Sparc$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Linux86$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Mingw$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void MVArm9$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void UCArm9$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ITarget$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Sparc$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Linux86$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Mingw$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void MVArm9$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void UCArm9$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void ITarget$$SIZES()
    {
    }

    void Sparc$$SIZES()
    {
    }

    void Linux86$$SIZES()
    {
    }

    void Mingw$$SIZES()
    {
    }

    void MVArm9$$SIZES()
    {
    }

    void UCArm9$$SIZES()
    {
    }

    void ITarget$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "gnu/targets/ITarget.xs");
        om.bind("gnu.targets.ITarget$$capsule", cap);
        po = (Proto.Obj)om.findStrict("gnu.targets.ITarget.Module", "gnu.targets");
        po.init("gnu.targets.ITarget.Module", om.findStrict("xdc.bld.ITarget.Module", "gnu.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("stdInclude", $$T_Str, "gnu/targets/std.h", "rh");
                po.addFld("dllExt", $$T_Str, ".so", "wh");
                po.addFld("GCCVERS", $$T_Str, null, "wh");
                po.addFld("version", $$T_Str, $$UNDEF, "wh");
                po.addFld("GCCTARG", $$T_Str, null, "wh");
                po.addFld("LONGNAME", $$T_Str, "/bin/gcc", "wh");
                po.addFld("CYGWIN", $$T_Bool, false, "rh");
                po.addFld("noStdLinkScript", $$T_Bool, false, "wh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "-g", "defs", "-D_DEBUG_=1"), "linkOpts", "-g")}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"), "linkOpts", "")}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "-g -pg"), "linkOpts", "-pg")}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "-fprofile-arcs -ftest-coverage"), "linkOpts", "-fprofile-arcs -ftest-coverage")})}), "wh");
                po.addFld("versionMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{"gcc3.2", "1,0,3.2,0"})}), "wh");
                po.addFld("remoteHost", $$T_Str, $$UNDEF, "wh");
                po.addFld("ar", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"), Global.newObject("cmd", "$(rootDir)/$(GCCTARG)/bin/ar", "opts", "cr"), "rh");
                po.addFld("arOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "", "suffix", ""), "wh");
                po.addFld("lnk", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"), Global.newObject("cmd", "$(rootDir)/$(LONGNAME)", "opts", ""), "rh");
                po.addFld("lnkOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "", "suffix", ""), "wh");
                po.addFld("cc", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"), Global.newObject("cmd", "$(rootDir)/$(LONGNAME) -c -MD -MF $@.dep", "opts", ""), "rh");
                po.addFld("ccOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "", "suffix", ""), "wh");
                po.addFld("asm", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"), Global.newObject("cmd", "$(rootDir)/$(LONGNAME) -c -x assembler", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "", "suffix", ""), "wh");
                po.addFld("includeOpts", $$T_Str, "", "wh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("gnu.targets.ITarget$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("gnu.targets.ITarget$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("gnu.targets.ITarget$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "gnu.targets"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "gnu.targets"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "gnu.targets"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "gnu.targets"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "gnu.targets"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "gnu.targets"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "gnu.targets"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "gnu.targets"), fxn);
        // struct ITarget.Command
        po = (Proto.Obj)om.findStrict("gnu.targets.ITarget$$Command", "gnu.targets");
        po.init("gnu.targets.ITarget.Command", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cmd", $$T_Str, $$UNDEF, "w");
                po.addFld("opts", $$T_Str, $$UNDEF, "w");
        // struct ITarget.Options
        po = (Proto.Obj)om.findStrict("gnu.targets.ITarget$$Options", "gnu.targets");
        po.init("gnu.targets.ITarget.Options", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("prefix", $$T_Str, $$UNDEF, "w");
                po.addFld("suffix", $$T_Str, $$UNDEF, "w");
    }

    void Sparc$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("gnu.targets.Sparc.Module", "gnu.targets");
        po.init("gnu.targets.Sparc.Module", om.findStrict("gnu.targets.ITarget.Module", "gnu.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "Sparc", "rh");
                po.addFld("os", $$T_Str, "Solaris", "rh");
                po.addFld("suffix", $$T_Str, "5", "rh");
                po.addFld("isa", $$T_Str, "sparc", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"), Global.newObject("endian", "big"), "rh");
                po.addFld("rts", $$T_Str, "gnu.targets.rts5", "rh");
                po.addFld("platform", $$T_Str, "host.platforms.SUN", "wh");
                po.addFld("ar", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"), Global.newObject("cmd", "$(rootDir)/bin/ar", "opts", "cr"), "rh");
                po.addFld("cc", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"), Global.newObject("cmd", "$(rootDir)/bin/gcc -c -MD -MF $@.dep", "opts", "-B$(rootDir)/lib/gcc/$(GCCTARG)/$(GCCVERS)/ -B$(rootDir)/lib/gcc-lib/$(GCCTARG)/$(GCCVERS)/"), "rh");
                po.addFld("ccOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "-fPIC -m32 -Wunused", "suffix", "-Dfar="), "wh");
                po.addFld("asm", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"), Global.newObject("cmd", "$(rootDir)/bin/gcc -c -x assembler", "opts", "-B$(rootDir)/lib/gcc/$(GCCTARG)/$(GCCVERS)/ -B$(rootDir)/lib/gcc-lib/$(GCCTARG)/$(GCCVERS)/"), "rh");
                po.addFld("lnkOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "", "suffix", "-lstdc++ -L$(rootDir)/lib"), "wh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 16L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "gnu.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "gnu.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "gnu.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "gnu.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "gnu.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "gnu.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "gnu.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "gnu.targets"), $$UNDEF);
    }

    void Linux86$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "gnu/targets/Linux86.xs");
        om.bind("gnu.targets.Linux86$$capsule", cap);
        po = (Proto.Obj)om.findStrict("gnu.targets.Linux86.Module", "gnu.targets");
        po.init("gnu.targets.Linux86.Module", om.findStrict("gnu.targets.ITarget.Module", "gnu.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "Linux86", "rh");
                po.addFld("os", $$T_Str, "Linux", "rh");
                po.addFld("suffix", $$T_Str, "86U", "rh");
                po.addFld("isa", $$T_Str, "i686", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("rts", $$T_Str, "gnu.targets.rts86U", "rh");
                po.addFld("platform", $$T_Str, "host.platforms.PC", "wh");
                po.addFld("ar", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"), Global.newObject("cmd", "$(rootDir)/bin/ar", "opts", "cr"), "rh");
                po.addFld("ccOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "-fPIC -Wunused", "suffix", "-Dfar="), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "", "suffix", "-lstdc++ -L$(rootDir)/lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-isystem $(rootDir)/include", "wh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 4L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 12L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 4L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("gnu.targets.Linux86$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("gnu.targets.Linux86$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("gnu.targets.Linux86$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "gnu.targets"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "gnu.targets"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "gnu.targets"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "gnu.targets"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "gnu.targets"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "gnu.targets"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "gnu.targets"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "gnu.targets"), fxn);
    }

    void Mingw$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "gnu/targets/Mingw.xs");
        om.bind("gnu.targets.Mingw$$capsule", cap);
        po = (Proto.Obj)om.findStrict("gnu.targets.Mingw.Module", "gnu.targets");
        po.init("gnu.targets.Mingw.Module", om.findStrict("gnu.targets.ITarget.Module", "gnu.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "Mingw", "rh");
                po.addFld("os", $$T_Str, "Windows", "rh");
                po.addFld("suffix", $$T_Str, "86GW", "rh");
                po.addFld("isa", $$T_Str, "x86", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("rts", $$T_Str, "gnu.targets.rts86GW", "rh");
                po.addFld("platform", $$T_Str, "host.platforms.PC", "wh");
                po.addFld("LONGNAME", $$T_Str, "/bin/mingw32-gcc.exe", "wh");
                po.addFld("cmdPrefix", $$T_Str, "", "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "-Wunused", "suffix", "-Dfar= "), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "", "suffix", "-lstdc++ -L$(rootDir)/lib"), "wh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 4L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 12L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 4L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("gnu.targets.Mingw$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("gnu.targets.Mingw$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("gnu.targets.Mingw$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "gnu.targets"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "gnu.targets"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "gnu.targets"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "gnu.targets"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "gnu.targets"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "gnu.targets"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "gnu.targets"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "gnu.targets"), fxn);
    }

    void MVArm9$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "gnu/targets/MVArm9.xs");
        om.bind("gnu.targets.MVArm9$$capsule", cap);
        po = (Proto.Obj)om.findStrict("gnu.targets.MVArm9.Module", "gnu.targets");
        po.init("gnu.targets.MVArm9.Module", om.findStrict("gnu.targets.ITarget.Module", "gnu.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "MVArm9", "rh");
                po.addFld("os", $$T_Str, "Linux", "rh");
                po.addFld("suffix", $$T_Str, "470MV", "rh");
                po.addFld("isa", $$T_Str, "v5T", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("rts", $$T_Str, "gnu.targets.rts470MV", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.evmDM6446", "wh");
                po.addFld("LONGNAME", $$T_Str, "bin/arm_v5t_le-gcc", "wh");
                po.addFld("CYGWIN", $$T_Bool, true, "rh");
                po.addFld("ccOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "-fPIC -Wunused", "suffix", "-Dfar= "), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "", "suffix", "-lstdc++ -L$(rootDir)/$(GCCTARG)/lib"), "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"v5T", "v5t"}), "wh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 4L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 4L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("gnu.targets.MVArm9$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("gnu.targets.MVArm9$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("gnu.targets.MVArm9$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "gnu.targets"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "gnu.targets"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "gnu.targets"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "gnu.targets"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "gnu.targets"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "gnu.targets"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "gnu.targets"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "gnu.targets"), fxn);
    }

    void UCArm9$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "gnu/targets/UCArm9.xs");
        om.bind("gnu.targets.UCArm9$$capsule", cap);
        po = (Proto.Obj)om.findStrict("gnu.targets.UCArm9.Module", "gnu.targets");
        po.init("gnu.targets.UCArm9.Module", om.findStrict("gnu.targets.ITarget.Module", "gnu.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "UCArm9", "rh");
                po.addFld("os", $$T_Str, "Linux", "rh");
                po.addFld("suffix", $$T_Str, "470uC", "rh");
                po.addFld("isa", $$T_Str, "v5T", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("rts", $$T_Str, "gnu.targets.rts470uC", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.evmDM6446", "wh");
                po.addFld("LONGNAME", $$T_Str, "/bin/arm-linux-gcc", "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "-Wunused", "suffix", "-Dfar= "), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"), Global.newObject("prefix", "-static", "suffix", "-L$(rootDir)/lib"), "wh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "-g", "defs", "-D_DEBUG_=1"), "linkOpts", "-g")}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"), "linkOpts", "")}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "-g -pg"), "linkOpts", "-pg")}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "-fprofile-arcs -ftest-coverage"), "linkOpts", "-fprofile-arcs -ftest-coverage")})}), "wh");
                po.addFld("versionMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{"gcc3.2", "1,0,3.2,0"})}), "wh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 4L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 4L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("gnu.targets.UCArm9$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("gnu.targets.UCArm9$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("gnu.targets.UCArm9$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "gnu.targets"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "gnu.targets"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "gnu.targets"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "gnu.targets"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "gnu.targets"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "gnu.targets"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "gnu.targets"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "gnu.targets"), fxn);
    }

    void ITarget$$ROV()
    {
    }

    void Sparc$$ROV()
    {
    }

    void Linux86$$ROV()
    {
    }

    void Mingw$$ROV()
    {
    }

    void MVArm9$$ROV()
    {
    }

    void UCArm9$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("gnu.targets.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "gnu.targets"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "gnu/targets/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "gnu.targets"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "gnu.targets"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "gnu.targets"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "gnu.targets"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "gnu.targets"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "gnu.targets"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "gnu.targets", Value.DEFAULT, false);
        pkgV.bind("$name", "gnu.targets");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "gnu.targets.");
        pkgV.bind("$vers", Global.newArray("1, 0, 1"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.bld", Global.newArray(1, 0, 1)));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['gnu.targets'];\n");
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

    void ITarget$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("gnu.targets.ITarget", "gnu.targets");
        po = (Proto.Obj)om.findStrict("gnu.targets.ITarget.Module", "gnu.targets");
        vo.init2(po, "gnu.targets.ITarget", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", om.findStrict("gnu.targets.ITarget$$capsule", "gnu.targets"));
        vo.bind("$package", om.findStrict("gnu.targets", "gnu.targets"));
        tdefs.clear();
        proxies.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "gnu.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        vo.bind("Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        vo.bind("Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ITarget", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ITarget");
        vo.seal(null);
    }

    void Sparc$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("gnu.targets.Sparc", "gnu.targets");
        po = (Proto.Obj)om.findStrict("gnu.targets.Sparc.Module", "gnu.targets");
        vo.init2(po, "gnu.targets.Sparc", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("gnu.targets", "gnu.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "gnu.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        vo.bind("Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        vo.bind("Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "gnu.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("gnu.targets.Sparc$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("Sparc", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Sparc");
    }

    void Linux86$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("gnu.targets.Linux86", "gnu.targets");
        po = (Proto.Obj)om.findStrict("gnu.targets.Linux86.Module", "gnu.targets");
        vo.init2(po, "gnu.targets.Linux86", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("gnu.targets.Linux86$$capsule", "gnu.targets"));
        vo.bind("$package", om.findStrict("gnu.targets", "gnu.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "gnu.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        vo.bind("Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        vo.bind("Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "gnu.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("gnu.targets.Linux86$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("Linux86", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Linux86");
    }

    void Mingw$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("gnu.targets.Mingw", "gnu.targets");
        po = (Proto.Obj)om.findStrict("gnu.targets.Mingw.Module", "gnu.targets");
        vo.init2(po, "gnu.targets.Mingw", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("gnu.targets.Mingw$$capsule", "gnu.targets"));
        vo.bind("$package", om.findStrict("gnu.targets", "gnu.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "gnu.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        vo.bind("Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        vo.bind("Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "gnu.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("gnu.targets.Mingw$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("Mingw", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Mingw");
    }

    void MVArm9$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("gnu.targets.MVArm9", "gnu.targets");
        po = (Proto.Obj)om.findStrict("gnu.targets.MVArm9.Module", "gnu.targets");
        vo.init2(po, "gnu.targets.MVArm9", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("gnu.targets.MVArm9$$capsule", "gnu.targets"));
        vo.bind("$package", om.findStrict("gnu.targets", "gnu.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "gnu.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        vo.bind("Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        vo.bind("Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "gnu.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("gnu.targets.MVArm9$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("MVArm9", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("MVArm9");
    }

    void UCArm9$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("gnu.targets.UCArm9", "gnu.targets");
        po = (Proto.Obj)om.findStrict("gnu.targets.UCArm9.Module", "gnu.targets");
        vo.init2(po, "gnu.targets.UCArm9", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("gnu.targets.UCArm9$$capsule", "gnu.targets"));
        vo.bind("$package", om.findStrict("gnu.targets", "gnu.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "gnu.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "gnu.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets"));
        vo.bind("Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Command", "gnu.targets"));
        vo.bind("Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Options", "gnu.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "gnu.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("gnu.targets.UCArm9$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("UCArm9", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("UCArm9");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("gnu.targets.Sparc", "gnu.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("gnu.targets.Linux86", "gnu.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("gnu.targets.Mingw", "gnu.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("gnu.targets.MVArm9", "gnu.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("gnu.targets.UCArm9", "gnu.targets"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("gnu.targets.ITarget")).bless();
        ((Value.Obj)om.getv("gnu.targets.Sparc")).bless();
        ((Value.Obj)om.getv("gnu.targets.Linux86")).bless();
        ((Value.Obj)om.getv("gnu.targets.Mingw")).bless();
        ((Value.Obj)om.getv("gnu.targets.MVArm9")).bless();
        ((Value.Obj)om.getv("gnu.targets.UCArm9")).bless();
        ((Value.Arr)om.findStrict("$packages", "gnu.targets")).add(pkgV);
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
        ITarget$$OBJECTS();
        Sparc$$OBJECTS();
        Linux86$$OBJECTS();
        Mingw$$OBJECTS();
        MVArm9$$OBJECTS();
        UCArm9$$OBJECTS();
        ITarget$$CONSTS();
        Sparc$$CONSTS();
        Linux86$$CONSTS();
        Mingw$$CONSTS();
        MVArm9$$CONSTS();
        UCArm9$$CONSTS();
        ITarget$$CREATES();
        Sparc$$CREATES();
        Linux86$$CREATES();
        Mingw$$CREATES();
        MVArm9$$CREATES();
        UCArm9$$CREATES();
        ITarget$$FUNCTIONS();
        Sparc$$FUNCTIONS();
        Linux86$$FUNCTIONS();
        Mingw$$FUNCTIONS();
        MVArm9$$FUNCTIONS();
        UCArm9$$FUNCTIONS();
        ITarget$$SIZES();
        Sparc$$SIZES();
        Linux86$$SIZES();
        Mingw$$SIZES();
        MVArm9$$SIZES();
        UCArm9$$SIZES();
        ITarget$$TYPES();
        Sparc$$TYPES();
        Linux86$$TYPES();
        Mingw$$TYPES();
        MVArm9$$TYPES();
        UCArm9$$TYPES();
        if (isROV) {
            ITarget$$ROV();
            Sparc$$ROV();
            Linux86$$ROV();
            Mingw$$ROV();
            MVArm9$$ROV();
            UCArm9$$ROV();
        }//isROV
        $$SINGLETONS();
        ITarget$$SINGLETONS();
        Sparc$$SINGLETONS();
        Linux86$$SINGLETONS();
        Mingw$$SINGLETONS();
        MVArm9$$SINGLETONS();
        UCArm9$$SINGLETONS();
        $$INITIALIZATION();
    }
}
