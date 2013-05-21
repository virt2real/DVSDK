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

public class gnu_targets_arm
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
        Global.callFxn("loadPackage", xdcO, "gnu.targets");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("gnu.targets.arm.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("gnu.targets.arm", new Value.Obj("gnu.targets.arm", pkgP));
    }

    void GCArmv5T$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("gnu.targets.arm.GCArmv5T.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("gnu.targets.arm.GCArmv5T", new Value.Obj("gnu.targets.arm.GCArmv5T", po));
        pkgV.bind("GCArmv5T", vo);
        // decls 
        om.bind("gnu.targets.arm.GCArmv5T.Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv5T.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv5T.Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv5T.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv5T.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv5T.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv5T.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv5T.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv5T.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv5T.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv5T.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv5T.Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv5T.Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"));
    }

    void GCArmv6$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("gnu.targets.arm.GCArmv6.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("gnu.targets.arm.GCArmv6", new Value.Obj("gnu.targets.arm.GCArmv6", po));
        pkgV.bind("GCArmv6", vo);
        // decls 
        om.bind("gnu.targets.arm.GCArmv6.Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv6.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv6.Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv6.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv6.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv6.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv6.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv6.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv6.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv6.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv6.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv6.Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv6.Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"));
    }

    void GCArmv7A$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("gnu.targets.arm.GCArmv7A.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("gnu.targets.arm.GCArmv7A", new Value.Obj("gnu.targets.arm.GCArmv7A", po));
        pkgV.bind("GCArmv7A", vo);
        // decls 
        om.bind("gnu.targets.arm.GCArmv7A.Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv7A.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv7A.Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv7A.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv7A.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv7A.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv7A.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv7A.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv7A.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv7A.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv7A.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv7A.Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"));
        om.bind("gnu.targets.arm.GCArmv7A.Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"));
    }

    void GCArmv5T$$CONSTS()
    {
        // module GCArmv5T
    }

    void GCArmv6$$CONSTS()
    {
        // module GCArmv6
    }

    void GCArmv7A$$CONSTS()
    {
        // module GCArmv7A
    }

    void GCArmv5T$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void GCArmv6$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void GCArmv7A$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void GCArmv5T$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GCArmv6$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GCArmv7A$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GCArmv5T$$SIZES()
    {
    }

    void GCArmv6$$SIZES()
    {
    }

    void GCArmv7A$$SIZES()
    {
    }

    void GCArmv5T$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("gnu.targets.arm.GCArmv5T.Module", "gnu.targets.arm");
        po.init("gnu.targets.arm.GCArmv5T.Module", om.findStrict("gnu.targets.ITarget.Module", "gnu.targets.arm"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "GCArmv5T", "rh");
                po.addFld("os", $$T_Str, "Linux", "rh");
                po.addFld("suffix", $$T_Str, "v5T", "rh");
                po.addFld("isa", $$T_Str, "v5T", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.arm"), Global.newObject("endian", "little"), "rh");
                po.addFld("rts", $$T_Str, "gnu.targets.arm.rtsv5T", "rh");
                po.addFld("platform", $$T_Str, "host.platforms.arm", "wh");
                po.addFld("LONGNAME", $$T_Str, $$UNDEF, "wh");
                po.addFld("stdInclude", $$T_Str, "gnu/targets/arm/std.h", "rh");
                po.addFld("cc", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"), Global.newObject("cmd", "$(rootDir)/$(LONGNAME) -c -MD -MF $@.dep", "opts", "-march=armv5t"), "rh");
                po.addFld("ccOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"), Global.newObject("prefix", "-fPIC -Wunused", "suffix", "-Dfar= "), "wh");
                po.addFld("asm", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"), Global.newObject("cmd", "$(rootDir)/$(LONGNAME) -c -x assembler", "opts", "-march=armv5t"), "rh");
                po.addFld("lnkOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"), Global.newObject("prefix", "", "suffix", "-lstdc++ -L$(rootDir)/$(GCCTARG)/lib"), "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"470MV", "v5t"}), "wh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.arm"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 4L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 4L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "gnu.targets.arm"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "gnu.targets.arm"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "gnu.targets.arm"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "gnu.targets.arm"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "gnu.targets.arm"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "gnu.targets.arm"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "gnu.targets.arm"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "gnu.targets.arm"), $$UNDEF);
    }

    void GCArmv6$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "gnu/targets/arm/GCArmv6.xs");
        om.bind("gnu.targets.arm.GCArmv6$$capsule", cap);
        po = (Proto.Obj)om.findStrict("gnu.targets.arm.GCArmv6.Module", "gnu.targets.arm");
        po.init("gnu.targets.arm.GCArmv6.Module", om.findStrict("gnu.targets.ITarget.Module", "gnu.targets.arm"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "GCArmv6", "rh");
                po.addFld("os", $$T_Str, "Linux", "rh");
                po.addFld("suffix", $$T_Str, "v6", "rh");
                po.addFld("isa", $$T_Str, "v6", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.arm"), Global.newObject("endian", "little"), "rh");
                po.addFld("rts", $$T_Str, "gnu.targets.arm.rtsv6", "rh");
                po.addFld("platform", $$T_Str, "host.platforms.arm", "wh");
                po.addFld("LONGNAME", $$T_Str, $$UNDEF, "wh");
                po.addFld("stdInclude", $$T_Str, "gnu/targets/arm/std.h", "rh");
                po.addFld("cc", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"), Global.newObject("cmd", "$(rootDir)/$(LONGNAME) -c -MD -MF $@.dep", "opts", "-march=armv6"), "rh");
                po.addFld("ccOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"), Global.newObject("prefix", "-fPIC -Wunused", "suffix", "-Dfar= "), "wh");
                po.addFld("asm", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"), Global.newObject("cmd", "$(rootDir)/$(LONGNAME) -c -x assembler", "opts", "-march=armv6"), "rh");
                po.addFld("lnkOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"), Global.newObject("prefix", "", "suffix", "-lstdc++ -L$(rootDir)/$(GCCTARG)/lib"), "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"v5T", "470MV", "v5t"}), "wh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.arm"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 4L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 4L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("gnu.targets.arm.GCArmv6$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("gnu.targets.arm.GCArmv6$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("gnu.targets.arm.GCArmv6$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "gnu.targets.arm"), fxn);
    }

    void GCArmv7A$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "gnu/targets/arm/GCArmv7A.xs");
        om.bind("gnu.targets.arm.GCArmv7A$$capsule", cap);
        po = (Proto.Obj)om.findStrict("gnu.targets.arm.GCArmv7A.Module", "gnu.targets.arm");
        po.init("gnu.targets.arm.GCArmv7A.Module", om.findStrict("gnu.targets.ITarget.Module", "gnu.targets.arm"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "GCArmv7A", "rh");
                po.addFld("os", $$T_Str, "Linux", "rh");
                po.addFld("suffix", $$T_Str, "v7A", "rh");
                po.addFld("isa", $$T_Str, "v7A", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.arm"), Global.newObject("endian", "little"), "rh");
                po.addFld("rts", $$T_Str, "gnu.targets.arm.rtsv7A", "rh");
                po.addFld("platform", $$T_Str, "host.platforms.arm", "wh");
                po.addFld("LONGNAME", $$T_Str, $$UNDEF, "wh");
                po.addFld("stdInclude", $$T_Str, "gnu/targets/arm/std.h", "rh");
                po.addFld("cc", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"), Global.newObject("cmd", "$(rootDir)/$(LONGNAME) -c -MD -MF $@.dep", "opts", "-march=armv7-a"), "rh");
                po.addFld("ccOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"), Global.newObject("prefix", "-fPIC -Wunused", "suffix", "-Dfar= "), "wh");
                po.addFld("asm", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"), Global.newObject("cmd", "$(rootDir)/$(LONGNAME) -c -x assembler", "opts", "-march=armv7-a"), "rh");
                po.addFld("lnkOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"), Global.newObject("prefix", "", "suffix", "-lstdc++ -L$(rootDir)/$(GCCTARG)/lib"), "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"v6", "v5T", "470MV", "v5t"}), "wh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.arm"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 4L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 4L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("gnu.targets.arm.GCArmv7A$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("gnu.targets.arm.GCArmv7A$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("gnu.targets.arm.GCArmv7A$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "gnu.targets.arm"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "gnu.targets.arm"), fxn);
    }

    void GCArmv5T$$ROV()
    {
    }

    void GCArmv6$$ROV()
    {
    }

    void GCArmv7A$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("gnu.targets.arm.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "gnu.targets.arm"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "gnu.targets.arm", Value.DEFAULT, false);
        pkgV.bind("$name", "gnu.targets.arm");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "gnu.targets.arm.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.bld", Global.newArray(1, 0, 1)));
        imports.add(Global.newArray("gnu.targets", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['gnu.targets.arm'];\n");
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

    void GCArmv5T$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("gnu.targets.arm.GCArmv5T", "gnu.targets.arm");
        po = (Proto.Obj)om.findStrict("gnu.targets.arm.GCArmv5T.Module", "gnu.targets.arm");
        vo.init2(po, "gnu.targets.arm.GCArmv5T", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("gnu.targets.arm", "gnu.targets.arm"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.arm"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.arm"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.arm"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.arm"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.arm"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.arm"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.arm"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.arm"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.arm"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "gnu.targets.arm"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.arm"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.arm"));
        vo.bind("Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"));
        vo.bind("Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "gnu.targets.arm")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("gnu.targets.arm.GCArmv5T$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("GCArmv5T", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GCArmv5T");
    }

    void GCArmv6$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("gnu.targets.arm.GCArmv6", "gnu.targets.arm");
        po = (Proto.Obj)om.findStrict("gnu.targets.arm.GCArmv6.Module", "gnu.targets.arm");
        vo.init2(po, "gnu.targets.arm.GCArmv6", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("gnu.targets.arm.GCArmv6$$capsule", "gnu.targets.arm"));
        vo.bind("$package", om.findStrict("gnu.targets.arm", "gnu.targets.arm"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.arm"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.arm"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.arm"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.arm"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.arm"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.arm"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.arm"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.arm"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.arm"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "gnu.targets.arm"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.arm"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.arm"));
        vo.bind("Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"));
        vo.bind("Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "gnu.targets.arm")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("gnu.targets.arm.GCArmv6$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("GCArmv6", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GCArmv6");
    }

    void GCArmv7A$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("gnu.targets.arm.GCArmv7A", "gnu.targets.arm");
        po = (Proto.Obj)om.findStrict("gnu.targets.arm.GCArmv7A.Module", "gnu.targets.arm");
        vo.init2(po, "gnu.targets.arm.GCArmv7A", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("gnu.targets.arm.GCArmv7A$$capsule", "gnu.targets.arm"));
        vo.bind("$package", om.findStrict("gnu.targets.arm", "gnu.targets.arm"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.arm"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.arm"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.arm"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.arm"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.arm"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.arm"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.arm"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.arm"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.arm"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "gnu.targets.arm"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.arm"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.arm"));
        vo.bind("Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.arm"));
        vo.bind("Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.arm"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "gnu.targets.arm")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("gnu.targets.arm.GCArmv7A$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("GCArmv7A", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GCArmv7A");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("gnu.targets.arm.GCArmv5T", "gnu.targets.arm"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("gnu.targets.arm.GCArmv6", "gnu.targets.arm"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("gnu.targets.arm.GCArmv7A", "gnu.targets.arm"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("gnu.targets.arm.GCArmv5T")).bless();
        ((Value.Obj)om.getv("gnu.targets.arm.GCArmv6")).bless();
        ((Value.Obj)om.getv("gnu.targets.arm.GCArmv7A")).bless();
        ((Value.Arr)om.findStrict("$packages", "gnu.targets.arm")).add(pkgV);
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
        GCArmv5T$$OBJECTS();
        GCArmv6$$OBJECTS();
        GCArmv7A$$OBJECTS();
        GCArmv5T$$CONSTS();
        GCArmv6$$CONSTS();
        GCArmv7A$$CONSTS();
        GCArmv5T$$CREATES();
        GCArmv6$$CREATES();
        GCArmv7A$$CREATES();
        GCArmv5T$$FUNCTIONS();
        GCArmv6$$FUNCTIONS();
        GCArmv7A$$FUNCTIONS();
        GCArmv5T$$SIZES();
        GCArmv6$$SIZES();
        GCArmv7A$$SIZES();
        GCArmv5T$$TYPES();
        GCArmv6$$TYPES();
        GCArmv7A$$TYPES();
        if (isROV) {
            GCArmv5T$$ROV();
            GCArmv6$$ROV();
            GCArmv7A$$ROV();
        }//isROV
        $$SINGLETONS();
        GCArmv5T$$SINGLETONS();
        GCArmv6$$SINGLETONS();
        GCArmv7A$$SINGLETONS();
        $$INITIALIZATION();
    }
}
