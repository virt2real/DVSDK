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

public class gnu_targets_codesourcery
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
        Global.callFxn("loadPackage", xdcO, "gnu.targets");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "xdc.bld");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("gnu.targets.codesourcery.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("gnu.targets.codesourcery", new Value.Obj("gnu.targets.codesourcery", pkgP));
    }

    void GCArmv5T$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("gnu.targets.codesourcery.GCArmv5T.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("gnu.targets.codesourcery.GCArmv5T", new Value.Obj("gnu.targets.codesourcery.GCArmv5T", po));
        pkgV.bind("GCArmv5T", vo);
        // decls 
        om.bind("gnu.targets.codesourcery.GCArmv5T.Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv5T.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv5T.Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv5T.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv5T.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv5T.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv5T.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv5T.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv5T.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv5T.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv5T.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv5T.Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv5T.Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.codesourcery"));
    }

    void GCArmv6$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("gnu.targets.codesourcery.GCArmv6.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("gnu.targets.codesourcery.GCArmv6", new Value.Obj("gnu.targets.codesourcery.GCArmv6", po));
        pkgV.bind("GCArmv6", vo);
        // decls 
        om.bind("gnu.targets.codesourcery.GCArmv6.Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv6.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv6.Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv6.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv6.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv6.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv6.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv6.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv6.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv6.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv6.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv6.Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.codesourcery"));
        om.bind("gnu.targets.codesourcery.GCArmv6.Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.codesourcery"));
    }

    void GCArmv5T$$CONSTS()
    {
        // module GCArmv5T
    }

    void GCArmv6$$CONSTS()
    {
        // module GCArmv6
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

    void GCArmv5T$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GCArmv6$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GCArmv5T$$SIZES()
    {
    }

    void GCArmv6$$SIZES()
    {
    }

    void GCArmv5T$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("gnu.targets.codesourcery.GCArmv5T.Module", "gnu.targets.codesourcery");
        po.init("gnu.targets.codesourcery.GCArmv5T.Module", om.findStrict("gnu.targets.ITarget.Module", "gnu.targets.codesourcery"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "GCArmv5T", "rh");
                po.addFld("os", $$T_Str, "Linux", "rh");
                po.addFld("suffix", $$T_Str, "470MV", "rh");
                po.addFld("isa", $$T_Str, "v5T", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.codesourcery"), Global.newObject("endian", "little"), "rh");
                po.addFld("rts", $$T_Str, "gnu.targets.codesourcery.rtsv5T", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.evm2530", "wh");
                po.addFld("LONGNAME", $$T_Str, "/bin/arm-none-linux-gnueabi-gcc", "wh");
                po.addFld("CYGWIN", $$T_Bool, true, "rh");
                po.addFld("stdInclude", $$T_Str, "gnu/targets/codesourcery/std.h", "rh");
                po.addFld("ccOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.codesourcery"), Global.newObject("prefix", "-fPIC -Wunused", "suffix", "-Dfar= "), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.codesourcery"), Global.newObject("prefix", "", "suffix", "-lstdc++ -L$(rootDir)/$(GCCTARG)/lib"), "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"v5T", "v5t"}), "wh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.codesourcery"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 4L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 4L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "gnu.targets.codesourcery"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "gnu.targets.codesourcery"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "gnu.targets.codesourcery"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "gnu.targets.codesourcery"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "gnu.targets.codesourcery"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "gnu.targets.codesourcery"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "gnu.targets.codesourcery"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "gnu.targets.codesourcery"), $$UNDEF);
    }

    void GCArmv6$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "gnu/targets/codesourcery/GCArmv6.xs");
        om.bind("gnu.targets.codesourcery.GCArmv6$$capsule", cap);
        po = (Proto.Obj)om.findStrict("gnu.targets.codesourcery.GCArmv6.Module", "gnu.targets.codesourcery");
        po.init("gnu.targets.codesourcery.GCArmv6.Module", om.findStrict("gnu.targets.ITarget.Module", "gnu.targets.codesourcery"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "GCArmv6", "rh");
                po.addFld("os", $$T_Str, "Linux", "rh");
                po.addFld("suffix", $$T_Str, "v6", "rh");
                po.addFld("isa", $$T_Str, "v6", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.codesourcery"), Global.newObject("endian", "little"), "rh");
                po.addFld("rts", $$T_Str, "gnu.targets.codesourcery.rtsv6", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.evm2530", "wh");
                po.addFld("LONGNAME", $$T_Str, "/bin/arm-none-linux-gnueabi-gcc", "wh");
                po.addFld("CYGWIN", $$T_Bool, true, "rh");
                po.addFld("stdInclude", $$T_Str, "gnu/targets/codesourcery/std.h", "rh");
                po.addFld("cc", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.codesourcery"), Global.newObject("cmd", "$(rootDir)/$(LONGNAME) -c -MD -MF $@.dep", "opts", "-march=armv6"), "rh");
                po.addFld("asm", (Proto)om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.codesourcery"), Global.newObject("cmd", "$(rootDir)/$(LONGNAME) -c -x assembler", "opts", "-march=armv6"), "rh");
                po.addFld("ccOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.codesourcery"), Global.newObject("prefix", "-fPIC -Wunused", "suffix", "-Dfar= "), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.codesourcery"), Global.newObject("prefix", "", "suffix", "-lstdc++ -L$(rootDir)/$(GCCTARG)/lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "", "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"v5T", "470MV", "v5t"}), "wh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.codesourcery"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 4L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 4L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("gnu.targets.codesourcery.GCArmv6$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("gnu.targets.codesourcery.GCArmv6$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("gnu.targets.codesourcery.GCArmv6$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "gnu.targets.codesourcery"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "gnu.targets.codesourcery"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "gnu.targets.codesourcery"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "gnu.targets.codesourcery"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "gnu.targets.codesourcery"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "gnu.targets.codesourcery"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "gnu.targets.codesourcery"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "gnu.targets.codesourcery"), fxn);
    }

    void GCArmv5T$$ROV()
    {
    }

    void GCArmv6$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("gnu.targets.codesourcery.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "gnu.targets.codesourcery"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "gnu/targets/codesourcery/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "gnu.targets.codesourcery"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "gnu.targets.codesourcery"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "gnu.targets.codesourcery"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "gnu.targets.codesourcery"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "gnu.targets.codesourcery"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "gnu.targets.codesourcery"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "gnu.targets.codesourcery", Value.DEFAULT, false);
        pkgV.bind("$name", "gnu.targets.codesourcery");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "gnu.targets.codesourcery.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("gnu.targets", Global.newArray(1, 0, 1)));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['gnu.targets.codesourcery'];\n");
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

        vo = (Value.Obj)om.findStrict("gnu.targets.codesourcery.GCArmv5T", "gnu.targets.codesourcery");
        po = (Proto.Obj)om.findStrict("gnu.targets.codesourcery.GCArmv5T.Module", "gnu.targets.codesourcery");
        vo.init2(po, "gnu.targets.codesourcery.GCArmv5T", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("gnu.targets.codesourcery", "gnu.targets.codesourcery"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.codesourcery"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.codesourcery"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.codesourcery"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.codesourcery"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.codesourcery"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.codesourcery"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.codesourcery"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.codesourcery"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.codesourcery"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "gnu.targets.codesourcery"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.codesourcery"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.codesourcery"));
        vo.bind("Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.codesourcery"));
        vo.bind("Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.codesourcery"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "gnu.targets.codesourcery")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("gnu.targets.codesourcery.GCArmv5T$$instance$static$init", null) ? 1 : 0);
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

        vo = (Value.Obj)om.findStrict("gnu.targets.codesourcery.GCArmv6", "gnu.targets.codesourcery");
        po = (Proto.Obj)om.findStrict("gnu.targets.codesourcery.GCArmv6.Module", "gnu.targets.codesourcery");
        vo.init2(po, "gnu.targets.codesourcery.GCArmv6", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("gnu.targets.codesourcery.GCArmv6$$capsule", "gnu.targets.codesourcery"));
        vo.bind("$package", om.findStrict("gnu.targets.codesourcery", "gnu.targets.codesourcery"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "gnu.targets.codesourcery"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "gnu.targets.codesourcery"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "gnu.targets.codesourcery"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "gnu.targets.codesourcery"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "gnu.targets.codesourcery"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "gnu.targets.codesourcery"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "gnu.targets.codesourcery"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "gnu.targets.codesourcery"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "gnu.targets.codesourcery"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "gnu.targets.codesourcery"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "gnu.targets.codesourcery"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "gnu.targets.codesourcery"));
        vo.bind("Command", om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Command", "gnu.targets.codesourcery"));
        vo.bind("Options", om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.codesourcery"));
        tdefs.add(om.findStrict("gnu.targets.ITarget.Options", "gnu.targets.codesourcery"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "gnu.targets.codesourcery")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("gnu.targets.codesourcery.GCArmv6$$instance$static$init", null) ? 1 : 0);
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

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("gnu.targets.codesourcery.GCArmv5T", "gnu.targets.codesourcery"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("gnu.targets.codesourcery.GCArmv6", "gnu.targets.codesourcery"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("gnu.targets.codesourcery.GCArmv5T")).bless();
        ((Value.Obj)om.getv("gnu.targets.codesourcery.GCArmv6")).bless();
        ((Value.Arr)om.findStrict("$packages", "gnu.targets.codesourcery")).add(pkgV);
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
        GCArmv5T$$CONSTS();
        GCArmv6$$CONSTS();
        GCArmv5T$$CREATES();
        GCArmv6$$CREATES();
        GCArmv5T$$FUNCTIONS();
        GCArmv6$$FUNCTIONS();
        GCArmv5T$$SIZES();
        GCArmv6$$SIZES();
        GCArmv5T$$TYPES();
        GCArmv6$$TYPES();
        if (isROV) {
            GCArmv5T$$ROV();
            GCArmv6$$ROV();
        }//isROV
        $$SINGLETONS();
        GCArmv5T$$SINGLETONS();
        GCArmv6$$SINGLETONS();
        $$INITIALIZATION();
    }
}
