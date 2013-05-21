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

public class ti_sdo_ce_video2
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.video2.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.video2", new Value.Obj("ti.sdo.ce.video2", pkgP));
    }

    void VIDDEC2Config$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video2.VIDDEC2Config.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video2.VIDDEC2Config", new Value.Obj("ti.sdo.ce.video2.VIDDEC2Config", po));
        pkgV.bind("VIDDEC2Config", vo);
        // decls 
    }

    void IVIDDEC2$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video2.IVIDDEC2.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video2.IVIDDEC2", new Value.Obj("ti.sdo.ce.video2.IVIDDEC2", po));
        pkgV.bind("IVIDDEC2", vo);
        // decls 
    }

    void VIDDEC2Config$$CONSTS()
    {
        // module VIDDEC2Config
    }

    void IVIDDEC2$$CONSTS()
    {
        // interface IVIDDEC2
    }

    void VIDDEC2Config$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IVIDDEC2$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VIDDEC2Config$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IVIDDEC2$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VIDDEC2Config$$SIZES()
    {
    }

    void IVIDDEC2$$SIZES()
    {
    }

    void VIDDEC2Config$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.VIDDEC2Config.Module", "ti.sdo.ce.video2");
        po.init("ti.sdo.ce.video2.VIDDEC2Config.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void IVIDDEC2$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.IVIDDEC2.Module", "ti.sdo.ce.video2");
        po.init("ti.sdo.ce.video2.IVIDDEC2.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.video2"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "VIDDEC2_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "VIDDEC2_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
                po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
                po.addFld("manageInBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
                po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void VIDDEC2Config$$ROV()
    {
    }

    void IVIDDEC2$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.video2.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.video2"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/video2/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.video2"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.video2"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.video2"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.video2"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.video2"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.video2"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.video2", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.video2");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.video2.");
        pkgV.bind("$vers", Global.newArray("1, 0, 2"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.video2'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/release/viddec2.a470uC',\n");
            sb.append("'lib/release/viddec2.a86U',\n");
            sb.append("'lib/debug/viddec2.a86U',\n");
            sb.append("'lib/release/viddec2.av5T',\n");
            sb.append("'lib/debug/viddec2.av5T',\n");
            sb.append("'lib/debug/viddec2.av4TCE',\n");
            sb.append("'lib/release/viddec2.a674',\n");
            sb.append("'lib/debug/viddec2.a674',\n");
            sb.append("'lib/debug/viddec2.a470uC',\n");
            sb.append("'lib/release/viddec2.a64P',\n");
            sb.append("'lib/debug/viddec2.a64P',\n");
            sb.append("'lib/release/viddec2.av4TCE',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/release/viddec2.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/viddec2.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/viddec2.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/viddec2.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/viddec2.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/viddec2.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/release/viddec2.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/viddec2.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/viddec2.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/viddec2.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/viddec2.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/viddec2.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/release/viddec2.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/viddec2.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/viddec2.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/release/viddec2.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/viddec2.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/viddec2.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/viddec2.av4TCE'].suffix = 'v4TCE';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void VIDDEC2Config$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video2.VIDDEC2Config", "ti.sdo.ce.video2");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.VIDDEC2Config.Module", "ti.sdo.ce.video2");
        vo.init2(po, "ti.sdo.ce.video2.VIDDEC2Config", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video2", "ti.sdo.ce.video2"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.video2")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.video2.VIDDEC2Config$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./VIDDEC2Config.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./VIDDEC2Config.xdt");
        pkgV.bind("VIDDEC2Config", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VIDDEC2Config");
    }

    void IVIDDEC2$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video2.IVIDDEC2", "ti.sdo.ce.video2");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.IVIDDEC2.Module", "ti.sdo.ce.video2");
        vo.init2(po, "ti.sdo.ce.video2.IVIDDEC2", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video2", "ti.sdo.ce.video2"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IVIDDEC2", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IVIDDEC2");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.video2.VIDDEC2Config", "ti.sdo.ce.video2"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.video2.VIDDEC2Config")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.video2.IVIDDEC2")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.video2")).add(pkgV);
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
        VIDDEC2Config$$OBJECTS();
        IVIDDEC2$$OBJECTS();
        VIDDEC2Config$$CONSTS();
        IVIDDEC2$$CONSTS();
        VIDDEC2Config$$CREATES();
        IVIDDEC2$$CREATES();
        VIDDEC2Config$$FUNCTIONS();
        IVIDDEC2$$FUNCTIONS();
        VIDDEC2Config$$SIZES();
        IVIDDEC2$$SIZES();
        VIDDEC2Config$$TYPES();
        IVIDDEC2$$TYPES();
        if (isROV) {
            VIDDEC2Config$$ROV();
            IVIDDEC2$$ROV();
        }//isROV
        $$SINGLETONS();
        VIDDEC2Config$$SINGLETONS();
        IVIDDEC2$$SINGLETONS();
        $$INITIALIZATION();
    }
}
