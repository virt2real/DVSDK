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

public class ti_sdo_ce_image1
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.image1.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.image1", new Value.Obj("ti.sdo.ce.image1", pkgP));
    }

    void IMGDEC1Config$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.image1.IMGDEC1Config.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.image1.IMGDEC1Config", new Value.Obj("ti.sdo.ce.image1.IMGDEC1Config", po));
        pkgV.bind("IMGDEC1Config", vo);
        // decls 
    }

    void IMGENC1Config$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.image1.IMGENC1Config.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.image1.IMGENC1Config", new Value.Obj("ti.sdo.ce.image1.IMGENC1Config", po));
        pkgV.bind("IMGENC1Config", vo);
        // decls 
    }

    void IIMGENC1$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.image1.IIMGENC1.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.image1.IIMGENC1", new Value.Obj("ti.sdo.ce.image1.IIMGENC1", po));
        pkgV.bind("IIMGENC1", vo);
        // decls 
    }

    void IIMGDEC1$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.image1.IIMGDEC1.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.image1.IIMGDEC1", new Value.Obj("ti.sdo.ce.image1.IIMGDEC1", po));
        pkgV.bind("IIMGDEC1", vo);
        // decls 
    }

    void IMGDEC1Config$$CONSTS()
    {
        // module IMGDEC1Config
    }

    void IMGENC1Config$$CONSTS()
    {
        // module IMGENC1Config
    }

    void IIMGENC1$$CONSTS()
    {
        // interface IIMGENC1
    }

    void IIMGDEC1$$CONSTS()
    {
        // interface IIMGDEC1
    }

    void IMGDEC1Config$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IMGENC1Config$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IIMGENC1$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IIMGDEC1$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IMGDEC1Config$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IMGENC1Config$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IIMGENC1$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IIMGDEC1$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IMGDEC1Config$$SIZES()
    {
    }

    void IMGENC1Config$$SIZES()
    {
    }

    void IIMGENC1$$SIZES()
    {
    }

    void IIMGDEC1$$SIZES()
    {
    }

    void IMGDEC1Config$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image1.IMGDEC1Config.Module", "ti.sdo.ce.image1");
        po.init("ti.sdo.ce.image1.IMGDEC1Config.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void IMGENC1Config$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image1.IMGENC1Config.Module", "ti.sdo.ce.image1");
        po.init("ti.sdo.ce.image1.IMGENC1Config.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void IIMGENC1$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image1.IIMGENC1.Module", "ti.sdo.ce.image1");
        po.init("ti.sdo.ce.image1.IIMGENC1.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.image1"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "IMGENC1_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "IMGENC1_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
                po.addFld("manageInBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
                po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void IIMGDEC1$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image1.IIMGDEC1.Module", "ti.sdo.ce.image1");
        po.init("ti.sdo.ce.image1.IIMGDEC1.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.image1"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "IMGDEC1_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "IMGDEC1_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
                po.addFld("manageInBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
                po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void IMGDEC1Config$$ROV()
    {
    }

    void IMGENC1Config$$ROV()
    {
    }

    void IIMGENC1$$ROV()
    {
    }

    void IIMGDEC1$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.image1.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.image1"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/image1/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.image1"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.image1"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.image1"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.image1"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.image1"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.image1"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.image1", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.image1");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.image1.");
        pkgV.bind("$vers", Global.newArray("1, 0, 1"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.image1'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/imgdec1.av5T',\n");
            sb.append("'lib/debug/imgenc1.av5T',\n");
            sb.append("'lib/release/imgdec1.a470uC',\n");
            sb.append("'lib/release/imgenc1.a64P',\n");
            sb.append("'lib/debug/imgenc1.a674',\n");
            sb.append("'lib/debug/imgdec1.a674',\n");
            sb.append("'lib/debug/imgenc1.av4TCE',\n");
            sb.append("'lib/debug/imgenc1.a470uC',\n");
            sb.append("'lib/release/imgenc1.a86U',\n");
            sb.append("'lib/release/imgenc1.av5T',\n");
            sb.append("'lib/release/imgenc1.a674',\n");
            sb.append("'lib/release/imgdec1.a64P',\n");
            sb.append("'lib/release/imgenc1.av4TCE',\n");
            sb.append("'lib/debug/imgdec1.av4TCE',\n");
            sb.append("'lib/release/imgenc1.a470uC',\n");
            sb.append("'lib/debug/imgenc1.a64P',\n");
            sb.append("'lib/debug/imgdec1.a64P',\n");
            sb.append("'lib/debug/imgdec1.a470uC',\n");
            sb.append("'lib/release/imgdec1.a86U',\n");
            sb.append("'lib/release/imgdec1.av5T',\n");
            sb.append("'lib/release/imgdec1.a674',\n");
            sb.append("'lib/release/imgdec1.av4TCE',\n");
            sb.append("'lib/debug/imgenc1.a86U',\n");
            sb.append("'lib/debug/imgdec1.a86U',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/imgdec1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/imgenc1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/imgdec1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/imgenc1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/imgenc1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/imgdec1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/imgenc1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/imgenc1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/imgenc1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/imgenc1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/imgenc1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/imgdec1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/imgenc1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/imgdec1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/release/imgenc1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/imgenc1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/imgdec1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/imgdec1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/imgdec1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/imgdec1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/imgdec1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/imgdec1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/imgenc1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/imgdec1.a86U', {target: 'gnu.targets.Linux86'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/debug/imgdec1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/imgenc1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/imgdec1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/imgenc1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/imgenc1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/imgdec1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/imgenc1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/imgenc1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/imgenc1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/imgenc1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/imgenc1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/imgdec1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/imgenc1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/imgdec1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/release/imgenc1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/imgenc1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/imgdec1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/imgdec1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/imgdec1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/imgdec1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/imgdec1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/imgdec1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/imgenc1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/imgdec1.a86U'].suffix = '86U';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void IMGDEC1Config$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.image1.IMGDEC1Config", "ti.sdo.ce.image1");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image1.IMGDEC1Config.Module", "ti.sdo.ce.image1");
        vo.init2(po, "ti.sdo.ce.image1.IMGDEC1Config", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.image1", "ti.sdo.ce.image1"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.image1")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.image1.IMGDEC1Config$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./IMGDEC1Config.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./IMGDEC1Config.xdt");
        pkgV.bind("IMGDEC1Config", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IMGDEC1Config");
    }

    void IMGENC1Config$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.image1.IMGENC1Config", "ti.sdo.ce.image1");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image1.IMGENC1Config.Module", "ti.sdo.ce.image1");
        vo.init2(po, "ti.sdo.ce.image1.IMGENC1Config", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.image1", "ti.sdo.ce.image1"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.image1")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.image1.IMGENC1Config$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./IMGENC1Config.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./IMGENC1Config.xdt");
        pkgV.bind("IMGENC1Config", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IMGENC1Config");
    }

    void IIMGENC1$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.image1.IIMGENC1", "ti.sdo.ce.image1");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image1.IIMGENC1.Module", "ti.sdo.ce.image1");
        vo.init2(po, "ti.sdo.ce.image1.IIMGENC1", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.image1", "ti.sdo.ce.image1"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IIMGENC1", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IIMGENC1");
        vo.seal(null);
    }

    void IIMGDEC1$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.image1.IIMGDEC1", "ti.sdo.ce.image1");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image1.IIMGDEC1.Module", "ti.sdo.ce.image1");
        vo.init2(po, "ti.sdo.ce.image1.IIMGDEC1", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.image1", "ti.sdo.ce.image1"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IIMGDEC1", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IIMGDEC1");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.image1.IMGDEC1Config", "ti.sdo.ce.image1"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.image1.IMGENC1Config", "ti.sdo.ce.image1"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.image1.IMGDEC1Config")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.image1.IMGENC1Config")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.image1.IIMGENC1")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.image1.IIMGDEC1")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.image1")).add(pkgV);
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
        IMGDEC1Config$$OBJECTS();
        IMGENC1Config$$OBJECTS();
        IIMGENC1$$OBJECTS();
        IIMGDEC1$$OBJECTS();
        IMGDEC1Config$$CONSTS();
        IMGENC1Config$$CONSTS();
        IIMGENC1$$CONSTS();
        IIMGDEC1$$CONSTS();
        IMGDEC1Config$$CREATES();
        IMGENC1Config$$CREATES();
        IIMGENC1$$CREATES();
        IIMGDEC1$$CREATES();
        IMGDEC1Config$$FUNCTIONS();
        IMGENC1Config$$FUNCTIONS();
        IIMGENC1$$FUNCTIONS();
        IIMGDEC1$$FUNCTIONS();
        IMGDEC1Config$$SIZES();
        IMGENC1Config$$SIZES();
        IIMGENC1$$SIZES();
        IIMGDEC1$$SIZES();
        IMGDEC1Config$$TYPES();
        IMGENC1Config$$TYPES();
        IIMGENC1$$TYPES();
        IIMGDEC1$$TYPES();
        if (isROV) {
            IMGDEC1Config$$ROV();
            IMGENC1Config$$ROV();
            IIMGENC1$$ROV();
            IIMGDEC1$$ROV();
        }//isROV
        $$SINGLETONS();
        IMGDEC1Config$$SINGLETONS();
        IMGENC1Config$$SINGLETONS();
        IIMGENC1$$SINGLETONS();
        IIMGDEC1$$SINGLETONS();
        $$INITIALIZATION();
    }
}
