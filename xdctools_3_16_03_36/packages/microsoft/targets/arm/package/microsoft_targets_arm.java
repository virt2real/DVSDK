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

public class microsoft_targets_arm
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
        Global.callFxn("loadPackage", xdcO, "microsoft.targets");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "xdc.bld");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("microsoft.targets.arm.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("microsoft.targets.arm", new Value.Obj("microsoft.targets.arm", pkgP));
    }

    void WinCE$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("microsoft.targets.arm.WinCE.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("microsoft.targets.arm.WinCE", new Value.Obj("microsoft.targets.arm.WinCE", po));
        pkgV.bind("WinCE", vo);
        // decls 
        om.bind("microsoft.targets.arm.WinCE.Model", om.findStrict("xdc.bld.ITarget.Model", "microsoft.targets.arm"));
        om.bind("microsoft.targets.arm.WinCE.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "microsoft.targets.arm"));
        om.bind("microsoft.targets.arm.WinCE.Extension", om.findStrict("xdc.bld.ITarget.Extension", "microsoft.targets.arm"));
        om.bind("microsoft.targets.arm.WinCE.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "microsoft.targets.arm"));
        om.bind("microsoft.targets.arm.WinCE.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "microsoft.targets.arm"));
        om.bind("microsoft.targets.arm.WinCE.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "microsoft.targets.arm"));
        om.bind("microsoft.targets.arm.WinCE.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "microsoft.targets.arm"));
        om.bind("microsoft.targets.arm.WinCE.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "microsoft.targets.arm"));
        om.bind("microsoft.targets.arm.WinCE.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "microsoft.targets.arm"));
        om.bind("microsoft.targets.arm.WinCE.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "microsoft.targets.arm"));
        om.bind("microsoft.targets.arm.WinCE.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "microsoft.targets.arm"));
        om.bind("microsoft.targets.arm.WinCE.Command", om.findStrict("microsoft.targets.ITarget.Command", "microsoft.targets.arm"));
        om.bind("microsoft.targets.arm.WinCE.Options", om.findStrict("microsoft.targets.ITarget.Options", "microsoft.targets.arm"));
        om.bind("microsoft.targets.arm.WinCE.EntryPoint", new Proto.Enm("microsoft.targets.arm.WinCE.EntryPoint"));
    }

    void WinCE$$CONSTS()
    {
        // module WinCE
        om.bind("microsoft.targets.arm.WinCE.UNDEFINED", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("microsoft.targets.arm.WinCE.EntryPoint", "microsoft.targets.arm"), "microsoft.targets.arm.WinCE.UNDEFINED", 0));
        om.bind("microsoft.targets.arm.WinCE.mainCRTStartup", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("microsoft.targets.arm.WinCE.EntryPoint", "microsoft.targets.arm"), "microsoft.targets.arm.WinCE.mainCRTStartup", 1));
        om.bind("microsoft.targets.arm.WinCE.WinMainCRTStartup", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("microsoft.targets.arm.WinCE.EntryPoint", "microsoft.targets.arm"), "microsoft.targets.arm.WinCE.WinMainCRTStartup", 2));
        om.bind("microsoft.targets.arm.WinCE._DllMainCRTStartup", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("microsoft.targets.arm.WinCE.EntryPoint", "microsoft.targets.arm"), "microsoft.targets.arm.WinCE._DllMainCRTStartup", 3));
    }

    void WinCE$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void WinCE$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void WinCE$$SIZES()
    {
    }

    void WinCE$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "microsoft/targets/arm/WinCE.xs");
        om.bind("microsoft.targets.arm.WinCE$$capsule", cap);
        po = (Proto.Obj)om.findStrict("microsoft.targets.arm.WinCE.Module", "microsoft.targets.arm");
        po.init("microsoft.targets.arm.WinCE.Module", om.findStrict("microsoft.targets.ITarget.Module", "microsoft.targets.arm"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "WinCE", "rh");
                po.addFld("os", $$T_Str, "WindowsCE", "rh");
                po.addFld("suffix", $$T_Str, "v4TCE", "rh");
                po.addFld("isa", $$T_Str, "v4T", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "microsoft.targets.arm"), Global.newObject("endian", "little"), "rh");
                po.addFld("stdInclude", $$T_Str, "microsoft/targets/arm/std.h", "rh");
                po.addFld("rts", $$T_Str, "microsoft.targets.arm.rts", "rh");
                po.addFld("platform", $$T_Str, "host.platforms.PC", "wh");
                po.addFld("execExt", $$T_Str, ".exe", "wh");
                po.addFld("strictANSI", $$T_Bool, false, "wh");
                po.addFld("remoteInitScript", $$T_Str, $$UNDEF, "wh");
                po.addFld("projectRoot", $$T_Str, $$UNDEF, "wh");
                po.addFld("sysGenIsa", $$T_Str, "ARMV4I", "wh");
                po.addFld("entryPoint", (Proto)om.findStrict("microsoft.targets.arm.WinCE.EntryPoint", "microsoft.targets.arm"), om.find("microsoft.targets.arm.WinCE.mainCRTStartup"), "wh");
                po.addFld("path", $$T_Str, "$(rootDir)/sdk/bin/i386;$(rootDir)/sdk/bin/i386/arm", "rh");
                po.addFld("ar", (Proto)om.findStrict("microsoft.targets.ITarget.Command", "microsoft.targets.arm"), Global.newObject("cmd", "$(rootDir)/sdk/bin/i386/arm/link.exe -lib -nologo", "opts", "-ignore:4001"), "rh");
                po.addFld("cc", (Proto)om.findStrict("microsoft.targets.ITarget.Command", "microsoft.targets.arm"), Global.newObject("cmd", "$(rootDir)/sdk/bin/i386/arm/cl.exe -nologo -c", "opts", "-Gy -GF -D_CRT_SECURE_NO_DEPRECATE -D_USE_32BIT_TIME_T -DUNICODE  -D_UNICODE -DUNDER_CE=600 -D_WIN32_WCE=0x600 -DWIN32 -DSTRICT -DARM -DARMV4I  -D_ARM_ -DINTERNATIONAL -DINTLMSG_CODEPAGE=1252 -Zc:wchar_t- -Zc:forScope- -wd4867 -wd4430 -MT -U_MT -W3 /GR- -QRarch4T -DTHUMBSUPPORT -QRimplicit-import- -QRinterwork-return /GS"), "rh");
                po.addFld("asm", (Proto)om.findStrict("microsoft.targets.ITarget.Command", "microsoft.targets.arm"), Global.newObject("cmd", "$(rootDir)/sdk/bin/i386/arm/armasm.exe -nologo", "opts", "-arch 4T"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("microsoft.targets.ITarget.Command", "microsoft.targets.arm"), Global.newObject("cmd", "$(rootDir)/sdk/bin/i386/arm/link -nologo", "opts", "-base:0x00010000 -MERGE:.rdata=.text -MERGE:.astart=.text -align:4096 -ignore:4001,4070,4078,4086,4089,4096,4099,4108,4229 /STACK:65536,4096 /LARGEADDRESSAWARE -incremental:no /opt:ref -SUBSYSTEM:WINDOWSCE,6.00"), "rh");
                po.addFld("ccOpts", (Proto)om.findStrict("microsoft.targets.ITarget.Options", "microsoft.targets.arm"), Global.newObject("prefix", "", "suffix", ""), "wh");
                po.addFld("includeOpts", $$T_Str, " ", "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("microsoft.targets.ITarget.Options", "microsoft.targets.arm"), Global.newObject("prefix", "-stack:65536,4096", "suffix", "-map:$(XDCCFGDIR)/$@.map -pdb:$(XDCCFGDIR)/$@.pdb -nodefaultlib"), "wh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "microsoft.targets.arm")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "-Od -Z7", "defs", "-D_DEBUG, -DDEBUG"), "linkOpts", "-debug -debugtype:cv,fixup coredll.lib corelibc.lib")}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2", "defs", "-DNDEBUG=1"), "linkOpts", "coredll.lib corelibc.lib")})}), "wh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("microsoft.targets.arm.WinCE$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("microsoft.targets.arm.WinCE$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("microsoft.targets.arm.WinCE$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "microsoft.targets.arm"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "microsoft.targets.arm"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "microsoft.targets.arm"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "microsoft.targets.arm"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "microsoft.targets.arm"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "microsoft.targets.arm"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "microsoft.targets.arm"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "microsoft.targets.arm"), fxn);
                fxn = Global.get(cap, "setPath");
                if (fxn != null) po.addFxn("setPath", (Proto.Fxn)om.findStrict("microsoft.targets.ITarget$$setPath", "microsoft.targets.arm"), fxn);
    }

    void WinCE$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("microsoft.targets.arm.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "microsoft.targets.arm"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "microsoft.targets.arm", Value.DEFAULT, false);
        pkgV.bind("$name", "microsoft.targets.arm");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "microsoft.targets.arm.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("microsoft.targets", Global.newArray(1, 0, 2)));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['microsoft.targets.arm'];\n");
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

    void WinCE$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("microsoft.targets.arm.WinCE", "microsoft.targets.arm");
        po = (Proto.Obj)om.findStrict("microsoft.targets.arm.WinCE.Module", "microsoft.targets.arm");
        vo.init2(po, "microsoft.targets.arm.WinCE", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("microsoft.targets.arm.WinCE$$capsule", "microsoft.targets.arm"));
        vo.bind("$package", om.findStrict("microsoft.targets.arm", "microsoft.targets.arm"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "microsoft.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "microsoft.targets.arm"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "microsoft.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "microsoft.targets.arm"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "microsoft.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "microsoft.targets.arm"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "microsoft.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "microsoft.targets.arm"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "microsoft.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "microsoft.targets.arm"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "microsoft.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "microsoft.targets.arm"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "microsoft.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "microsoft.targets.arm"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "microsoft.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "microsoft.targets.arm"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "microsoft.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "microsoft.targets.arm"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "microsoft.targets.arm"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "microsoft.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "microsoft.targets.arm"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "microsoft.targets.arm"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "microsoft.targets.arm"));
        vo.bind("Command", om.findStrict("microsoft.targets.ITarget.Command", "microsoft.targets.arm"));
        tdefs.add(om.findStrict("microsoft.targets.ITarget.Command", "microsoft.targets.arm"));
        vo.bind("Options", om.findStrict("microsoft.targets.ITarget.Options", "microsoft.targets.arm"));
        tdefs.add(om.findStrict("microsoft.targets.ITarget.Options", "microsoft.targets.arm"));
        vo.bind("EntryPoint", om.findStrict("microsoft.targets.arm.WinCE.EntryPoint", "microsoft.targets.arm"));
        vo.bind("UNDEFINED", om.findStrict("microsoft.targets.arm.WinCE.UNDEFINED", "microsoft.targets.arm"));
        vo.bind("mainCRTStartup", om.findStrict("microsoft.targets.arm.WinCE.mainCRTStartup", "microsoft.targets.arm"));
        vo.bind("WinMainCRTStartup", om.findStrict("microsoft.targets.arm.WinCE.WinMainCRTStartup", "microsoft.targets.arm"));
        vo.bind("_DllMainCRTStartup", om.findStrict("microsoft.targets.arm.WinCE._DllMainCRTStartup", "microsoft.targets.arm"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "microsoft.targets.arm")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("microsoft.targets.arm.WinCE$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("WinCE", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("WinCE");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("microsoft.targets.arm.WinCE", "microsoft.targets.arm"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("microsoft.targets.arm.WinCE")).bless();
        ((Value.Arr)om.findStrict("$packages", "microsoft.targets.arm")).add(pkgV);
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
        WinCE$$OBJECTS();
        WinCE$$CONSTS();
        WinCE$$CREATES();
        WinCE$$FUNCTIONS();
        WinCE$$SIZES();
        WinCE$$TYPES();
        if (isROV) {
            WinCE$$ROV();
        }//isROV
        $$SINGLETONS();
        WinCE$$SINGLETONS();
        $$INITIALIZATION();
    }
}
