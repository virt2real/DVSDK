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

public class ti_sdo_ce_video2_split
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.video2.split.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.video2.split", new Value.Obj("ti.sdo.ce.video2.split", pkgP));
    }

    void VIDDEC2BACKConfig$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video2.split.VIDDEC2BACKConfig.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video2.split.VIDDEC2BACKConfig", new Value.Obj("ti.sdo.ce.video2.split.VIDDEC2BACKConfig", po));
        pkgV.bind("VIDDEC2BACKConfig", vo);
        // decls 
    }

    void IVIDDEC2FRONT$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video2.split.IVIDDEC2FRONT.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video2.split.IVIDDEC2FRONT", new Value.Obj("ti.sdo.ce.video2.split.IVIDDEC2FRONT", po));
        pkgV.bind("IVIDDEC2FRONT", vo);
        // decls 
    }

    void IVIDDEC2BACK$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video2.split.IVIDDEC2BACK.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video2.split.IVIDDEC2BACK", new Value.Obj("ti.sdo.ce.video2.split.IVIDDEC2BACK", po));
        pkgV.bind("IVIDDEC2BACK", vo);
        // decls 
    }

    void VIDDEC2BACKConfig$$CONSTS()
    {
        // module VIDDEC2BACKConfig
    }

    void IVIDDEC2FRONT$$CONSTS()
    {
        // interface IVIDDEC2FRONT
    }

    void IVIDDEC2BACK$$CONSTS()
    {
        // interface IVIDDEC2BACK
        om.bind("ti.sdo.ce.video2.split.IVIDDEC2BACK.XDM_MAX_CONTEXT_BUFFERS", 32L);
    }

    void VIDDEC2BACKConfig$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IVIDDEC2FRONT$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IVIDDEC2BACK$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VIDDEC2BACKConfig$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IVIDDEC2FRONT$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IVIDDEC2BACK$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VIDDEC2BACKConfig$$SIZES()
    {
    }

    void IVIDDEC2FRONT$$SIZES()
    {
    }

    void IVIDDEC2BACK$$SIZES()
    {
    }

    void VIDDEC2BACKConfig$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.split.VIDDEC2BACKConfig.Module", "ti.sdo.ce.video2.split");
        po.init("ti.sdo.ce.video2.split.VIDDEC2BACKConfig.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void IVIDDEC2FRONT$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.split.IVIDDEC2FRONT.Module", "ti.sdo.ce.video2.split");
        po.init("ti.sdo.ce.video2.split.IVIDDEC2FRONT.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.video2.split"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "VIDDEC2FRONT_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "VIDDEC2FRONT_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
    }

    void IVIDDEC2BACK$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.split.IVIDDEC2BACK.Module", "ti.sdo.ce.video2.split");
        po.init("ti.sdo.ce.video2.split.IVIDDEC2BACK.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.video2.split"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("XDM_MAX_CONTEXT_BUFFERS", Proto.Elm.newCNum("(xdc_Int)"), 32L, "rh");
                po.addFld("serverFxns", $$T_Str, "VIDDEC2BACK_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "VIDDEC2BACK_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
                po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
                po.addFld("manageInBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(32L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
                po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(32L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
                po.addFld("manageIntermediateBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(32L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void VIDDEC2BACKConfig$$ROV()
    {
    }

    void IVIDDEC2FRONT$$ROV()
    {
    }

    void IVIDDEC2BACK$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.video2.split.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.video2.split"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/video2/split/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.video2.split"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.video2.split"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.video2.split"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.video2.split"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.video2.split"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.video2.split"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.video2.split", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.video2.split");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.video2.split.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.video2.split'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/viddec2front.a470uC',\n");
            sb.append("'lib/viddec2front.a470uC',\n");
            sb.append("'lib/debug/viddec2back.a64P',\n");
            sb.append("'lib/viddec2back.a64P',\n");
            sb.append("'lib/debug/viddec2back.av4TCE',\n");
            sb.append("'lib/viddec2back.av4TCE',\n");
            sb.append("'lib/viddec2back.a86U',\n");
            sb.append("'lib/debug/viddec2back.a86U',\n");
            sb.append("'lib/debug/viddec2front.a64P',\n");
            sb.append("'lib/viddec2back.av5T',\n");
            sb.append("'lib/debug/viddec2back.av5T',\n");
            sb.append("'lib/debug/viddec2back.a470uC',\n");
            sb.append("'lib/viddec2back.a674',\n");
            sb.append("'lib/viddec2front.a64P',\n");
            sb.append("'lib/debug/viddec2back.a674',\n");
            sb.append("'lib/viddec2back.a470uC',\n");
            sb.append("'lib/viddec2front.av4TCE',\n");
            sb.append("'lib/debug/viddec2front.a86U',\n");
            sb.append("'lib/debug/viddec2front.av5T',\n");
            sb.append("'lib/viddec2front.a86U',\n");
            sb.append("'lib/debug/viddec2front.a674',\n");
            sb.append("'lib/viddec2front.av5T',\n");
            sb.append("'lib/debug/viddec2front.av4TCE',\n");
            sb.append("'lib/viddec2front.a674',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/viddec2front.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/viddec2front.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/viddec2back.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/viddec2back.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/viddec2back.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/viddec2back.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/viddec2back.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/viddec2back.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/viddec2front.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/viddec2back.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/viddec2back.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/viddec2back.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/viddec2back.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/viddec2front.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/viddec2back.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/viddec2back.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/viddec2front.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/viddec2front.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/viddec2front.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/viddec2front.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/viddec2front.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/viddec2front.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/viddec2front.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/viddec2front.a674', {target: 'ti.targets.C674'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2front.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/viddec2front.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2back.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/viddec2back.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2back.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/viddec2back.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/viddec2back.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2back.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2front.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/viddec2back.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2back.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2back.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/viddec2back.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/viddec2front.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2back.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/viddec2back.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/viddec2front.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2front.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2front.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/viddec2front.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2front.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/viddec2front.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2front.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/viddec2front.a674'].suffix = '674';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void VIDDEC2BACKConfig$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video2.split.VIDDEC2BACKConfig", "ti.sdo.ce.video2.split");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.split.VIDDEC2BACKConfig.Module", "ti.sdo.ce.video2.split");
        vo.init2(po, "ti.sdo.ce.video2.split.VIDDEC2BACKConfig", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video2.split", "ti.sdo.ce.video2.split"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.video2.split")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.video2.split.VIDDEC2BACKConfig$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./VIDDEC2BACKConfig.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./VIDDEC2BACKConfig.xdt");
        pkgV.bind("VIDDEC2BACKConfig", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VIDDEC2BACKConfig");
    }

    void IVIDDEC2FRONT$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video2.split.IVIDDEC2FRONT", "ti.sdo.ce.video2.split");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.split.IVIDDEC2FRONT.Module", "ti.sdo.ce.video2.split");
        vo.init2(po, "ti.sdo.ce.video2.split.IVIDDEC2FRONT", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video2.split", "ti.sdo.ce.video2.split"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IVIDDEC2FRONT", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IVIDDEC2FRONT");
        vo.seal(null);
    }

    void IVIDDEC2BACK$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video2.split.IVIDDEC2BACK", "ti.sdo.ce.video2.split");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.split.IVIDDEC2BACK.Module", "ti.sdo.ce.video2.split");
        vo.init2(po, "ti.sdo.ce.video2.split.IVIDDEC2BACK", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video2.split", "ti.sdo.ce.video2.split"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IVIDDEC2BACK", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IVIDDEC2BACK");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.video2.split.VIDDEC2BACKConfig", "ti.sdo.ce.video2.split"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.video2.split.VIDDEC2BACKConfig")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.video2.split.IVIDDEC2FRONT")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.video2.split.IVIDDEC2BACK")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.video2.split")).add(pkgV);
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
        VIDDEC2BACKConfig$$OBJECTS();
        IVIDDEC2FRONT$$OBJECTS();
        IVIDDEC2BACK$$OBJECTS();
        VIDDEC2BACKConfig$$CONSTS();
        IVIDDEC2FRONT$$CONSTS();
        IVIDDEC2BACK$$CONSTS();
        VIDDEC2BACKConfig$$CREATES();
        IVIDDEC2FRONT$$CREATES();
        IVIDDEC2BACK$$CREATES();
        VIDDEC2BACKConfig$$FUNCTIONS();
        IVIDDEC2FRONT$$FUNCTIONS();
        IVIDDEC2BACK$$FUNCTIONS();
        VIDDEC2BACKConfig$$SIZES();
        IVIDDEC2FRONT$$SIZES();
        IVIDDEC2BACK$$SIZES();
        VIDDEC2BACKConfig$$TYPES();
        IVIDDEC2FRONT$$TYPES();
        IVIDDEC2BACK$$TYPES();
        if (isROV) {
            VIDDEC2BACKConfig$$ROV();
            IVIDDEC2FRONT$$ROV();
            IVIDDEC2BACK$$ROV();
        }//isROV
        $$SINGLETONS();
        VIDDEC2BACKConfig$$SINGLETONS();
        IVIDDEC2FRONT$$SINGLETONS();
        IVIDDEC2BACK$$SINGLETONS();
        $$INITIALIZATION();
    }
}
