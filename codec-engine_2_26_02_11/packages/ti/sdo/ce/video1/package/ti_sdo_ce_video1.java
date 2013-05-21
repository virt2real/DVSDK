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

public class ti_sdo_ce_video1
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
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.video1.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.video1", new Value.Obj("ti.sdo.ce.video1", pkgP));
    }

    void VIDENC1Config$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video1.VIDENC1Config.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video1.VIDENC1Config", new Value.Obj("ti.sdo.ce.video1.VIDENC1Config", po));
        pkgV.bind("VIDENC1Config", vo);
        // decls 
    }

    void VIDDEC1Config$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video1.VIDDEC1Config.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video1.VIDDEC1Config", new Value.Obj("ti.sdo.ce.video1.VIDDEC1Config", po));
        pkgV.bind("VIDDEC1Config", vo);
        // decls 
    }

    void IVIDDEC1$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video1.IVIDDEC1.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video1.IVIDDEC1", new Value.Obj("ti.sdo.ce.video1.IVIDDEC1", po));
        pkgV.bind("IVIDDEC1", vo);
        // decls 
    }

    void IVIDENC1$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video1.IVIDENC1.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video1.IVIDENC1", new Value.Obj("ti.sdo.ce.video1.IVIDENC1", po));
        pkgV.bind("IVIDENC1", vo);
        // decls 
    }

    void VIDENC1Config$$CONSTS()
    {
        // module VIDENC1Config
    }

    void VIDDEC1Config$$CONSTS()
    {
        // module VIDDEC1Config
    }

    void IVIDDEC1$$CONSTS()
    {
        // interface IVIDDEC1
    }

    void IVIDENC1$$CONSTS()
    {
        // interface IVIDENC1
    }

    void VIDENC1Config$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VIDDEC1Config$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IVIDDEC1$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IVIDENC1$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VIDENC1Config$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VIDDEC1Config$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IVIDDEC1$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IVIDENC1$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VIDENC1Config$$SIZES()
    {
    }

    void VIDDEC1Config$$SIZES()
    {
    }

    void IVIDDEC1$$SIZES()
    {
    }

    void IVIDENC1$$SIZES()
    {
    }

    void VIDENC1Config$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video1.VIDENC1Config.Module", "ti.sdo.ce.video1");
        po.init("ti.sdo.ce.video1.VIDENC1Config.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void VIDDEC1Config$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video1.VIDDEC1Config.Module", "ti.sdo.ce.video1");
        po.init("ti.sdo.ce.video1.VIDDEC1Config.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void IVIDDEC1$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video1.IVIDDEC1.Module", "ti.sdo.ce.video1");
        po.init("ti.sdo.ce.video1.IVIDDEC1.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.video1"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "VIDDEC1_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "VIDDEC1_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
                po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
                po.addFld("manageInBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
                po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void IVIDENC1$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video1.IVIDENC1.Module", "ti.sdo.ce.video1");
        po.init("ti.sdo.ce.video1.IVIDENC1.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.video1"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "VIDENC1_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "VIDENC1_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
                po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
                po.addFld("manageInBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
                po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void VIDENC1Config$$ROV()
    {
    }

    void VIDDEC1Config$$ROV()
    {
    }

    void IVIDDEC1$$ROV()
    {
    }

    void IVIDENC1$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.video1.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.video1"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/video1/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.video1"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.video1"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.video1"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.video1"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.video1"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.video1"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.video1", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.video1");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.video1.");
        pkgV.bind("$vers", Global.newArray("1, 0, 2"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.video1'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/videnc1.a470uC',\n");
            sb.append("'lib/release/viddec1.av4TCE',\n");
            sb.append("'lib/release/videnc1.a86U',\n");
            sb.append("'lib/release/viddec1.a86U',\n");
            sb.append("'lib/release/viddec1.av5T',\n");
            sb.append("'lib/release/videnc1.av5T',\n");
            sb.append("'lib/release/viddec1.a674',\n");
            sb.append("'lib/release/videnc1.a674',\n");
            sb.append("'lib/release/viddec1.a470uC',\n");
            sb.append("'lib/release/videnc1.av4TCE',\n");
            sb.append("'lib/debug/videnc1.a86U',\n");
            sb.append("'lib/debug/videnc1.av5T',\n");
            sb.append("'lib/debug/videnc1.a674',\n");
            sb.append("'lib/release/videnc1.a470uC',\n");
            sb.append("'lib/debug/viddec1.a64P',\n");
            sb.append("'lib/debug/viddec1.a86U',\n");
            sb.append("'lib/debug/viddec1.av4TCE',\n");
            sb.append("'lib/debug/viddec1.av5T',\n");
            sb.append("'lib/release/viddec1.a64P',\n");
            sb.append("'lib/release/videnc1.a64P',\n");
            sb.append("'lib/debug/viddec1.a674',\n");
            sb.append("'lib/debug/viddec1.a470uC',\n");
            sb.append("'lib/debug/videnc1.av4TCE',\n");
            sb.append("'lib/debug/videnc1.a64P',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/videnc1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/viddec1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/release/videnc1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/viddec1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/viddec1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/videnc1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/viddec1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/videnc1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/viddec1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/videnc1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/videnc1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/videnc1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/videnc1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/videnc1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/viddec1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/viddec1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/viddec1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/viddec1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/viddec1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/videnc1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/viddec1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/viddec1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/videnc1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/videnc1.a64P', {target: 'ti.targets.C64P'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/debug/videnc1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/viddec1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/release/videnc1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/viddec1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/viddec1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/videnc1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/viddec1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/videnc1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/viddec1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/videnc1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/videnc1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/videnc1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/videnc1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/videnc1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/viddec1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/videnc1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/videnc1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/videnc1.a64P'].suffix = '64P';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void VIDENC1Config$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video1.VIDENC1Config", "ti.sdo.ce.video1");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video1.VIDENC1Config.Module", "ti.sdo.ce.video1");
        vo.init2(po, "ti.sdo.ce.video1.VIDENC1Config", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video1", "ti.sdo.ce.video1"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.video1")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.video1.VIDENC1Config$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./VIDENC1Config.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./VIDENC1Config.xdt");
        pkgV.bind("VIDENC1Config", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VIDENC1Config");
    }

    void VIDDEC1Config$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video1.VIDDEC1Config", "ti.sdo.ce.video1");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video1.VIDDEC1Config.Module", "ti.sdo.ce.video1");
        vo.init2(po, "ti.sdo.ce.video1.VIDDEC1Config", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video1", "ti.sdo.ce.video1"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.video1")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.video1.VIDDEC1Config$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./VIDDEC1Config.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./VIDDEC1Config.xdt");
        pkgV.bind("VIDDEC1Config", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VIDDEC1Config");
    }

    void IVIDDEC1$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video1.IVIDDEC1", "ti.sdo.ce.video1");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video1.IVIDDEC1.Module", "ti.sdo.ce.video1");
        vo.init2(po, "ti.sdo.ce.video1.IVIDDEC1", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video1", "ti.sdo.ce.video1"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IVIDDEC1", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IVIDDEC1");
        vo.seal(null);
    }

    void IVIDENC1$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video1.IVIDENC1", "ti.sdo.ce.video1");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video1.IVIDENC1.Module", "ti.sdo.ce.video1");
        vo.init2(po, "ti.sdo.ce.video1.IVIDENC1", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video1", "ti.sdo.ce.video1"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IVIDENC1", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IVIDENC1");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.video1.VIDENC1Config", "ti.sdo.ce.video1"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.video1.VIDDEC1Config", "ti.sdo.ce.video1"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.video1.VIDENC1Config")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.video1.VIDDEC1Config")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.video1.IVIDDEC1")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.video1.IVIDENC1")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.video1")).add(pkgV);
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
        VIDENC1Config$$OBJECTS();
        VIDDEC1Config$$OBJECTS();
        IVIDDEC1$$OBJECTS();
        IVIDENC1$$OBJECTS();
        VIDENC1Config$$CONSTS();
        VIDDEC1Config$$CONSTS();
        IVIDDEC1$$CONSTS();
        IVIDENC1$$CONSTS();
        VIDENC1Config$$CREATES();
        VIDDEC1Config$$CREATES();
        IVIDDEC1$$CREATES();
        IVIDENC1$$CREATES();
        VIDENC1Config$$FUNCTIONS();
        VIDDEC1Config$$FUNCTIONS();
        IVIDDEC1$$FUNCTIONS();
        IVIDENC1$$FUNCTIONS();
        VIDENC1Config$$SIZES();
        VIDDEC1Config$$SIZES();
        IVIDDEC1$$SIZES();
        IVIDENC1$$SIZES();
        VIDENC1Config$$TYPES();
        VIDDEC1Config$$TYPES();
        IVIDDEC1$$TYPES();
        IVIDENC1$$TYPES();
        if (isROV) {
            VIDENC1Config$$ROV();
            VIDDEC1Config$$ROV();
            IVIDDEC1$$ROV();
            IVIDENC1$$ROV();
        }//isROV
        $$SINGLETONS();
        VIDENC1Config$$SINGLETONS();
        VIDDEC1Config$$SINGLETONS();
        IVIDDEC1$$SINGLETONS();
        IVIDENC1$$SINGLETONS();
        $$INITIALIZATION();
    }
}
