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

public class ti_sdo_ce_audio1
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.audio1.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.audio1", new Value.Obj("ti.sdo.ce.audio1", pkgP));
    }

    void IAUDENC1$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.audio1.IAUDENC1.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.audio1.IAUDENC1", new Value.Obj("ti.sdo.ce.audio1.IAUDENC1", po));
        pkgV.bind("IAUDENC1", vo);
        // decls 
    }

    void IAUDDEC1$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.audio1.IAUDDEC1.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.audio1.IAUDDEC1", new Value.Obj("ti.sdo.ce.audio1.IAUDDEC1", po));
        pkgV.bind("IAUDDEC1", vo);
        // decls 
    }

    void IAUDENC1$$CONSTS()
    {
        // interface IAUDENC1
    }

    void IAUDDEC1$$CONSTS()
    {
        // interface IAUDDEC1
    }

    void IAUDENC1$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IAUDDEC1$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IAUDENC1$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IAUDDEC1$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IAUDENC1$$SIZES()
    {
    }

    void IAUDDEC1$$SIZES()
    {
    }

    void IAUDENC1$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.audio1.IAUDENC1.Module", "ti.sdo.ce.audio1");
        po.init("ti.sdo.ce.audio1.IAUDENC1.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.audio1"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "AUDENC1_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "AUDENC1_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
    }

    void IAUDDEC1$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.audio1.IAUDDEC1.Module", "ti.sdo.ce.audio1");
        po.init("ti.sdo.ce.audio1.IAUDDEC1.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.audio1"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "AUDDEC1_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "AUDDEC1_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
    }

    void IAUDENC1$$ROV()
    {
    }

    void IAUDDEC1$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.audio1.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.audio1"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/audio1/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.audio1"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.audio1"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.audio1"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.audio1"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.audio1"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.audio1"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.audio1", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.audio1");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.audio1.");
        pkgV.bind("$vers", Global.newArray("1, 0, 1"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.audio1'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/release/audenc1.a674',\n");
            sb.append("'lib/release/auddec1.a64P',\n");
            sb.append("'lib/release/audenc1.av4TCE',\n");
            sb.append("'lib/debug/auddec1.av4TCE',\n");
            sb.append("'lib/debug/audenc1.a64P',\n");
            sb.append("'lib/debug/auddec1.a64P',\n");
            sb.append("'lib/release/audenc1.a470uC',\n");
            sb.append("'lib/debug/auddec1.a470uC',\n");
            sb.append("'lib/release/auddec1.a86U',\n");
            sb.append("'lib/release/auddec1.av5T',\n");
            sb.append("'lib/release/auddec1.a674',\n");
            sb.append("'lib/release/auddec1.av4TCE',\n");
            sb.append("'lib/debug/audenc1.a86U',\n");
            sb.append("'lib/debug/auddec1.a86U',\n");
            sb.append("'lib/debug/auddec1.av5T',\n");
            sb.append("'lib/debug/audenc1.av5T',\n");
            sb.append("'lib/release/audenc1.a64P',\n");
            sb.append("'lib/debug/audenc1.a674',\n");
            sb.append("'lib/release/auddec1.a470uC',\n");
            sb.append("'lib/debug/auddec1.a674',\n");
            sb.append("'lib/debug/audenc1.av4TCE',\n");
            sb.append("'lib/release/audenc1.a86U',\n");
            sb.append("'lib/debug/audenc1.a470uC',\n");
            sb.append("'lib/release/audenc1.av5T',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/release/audenc1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/auddec1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/audenc1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/auddec1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/audenc1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/auddec1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/audenc1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/auddec1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/auddec1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/auddec1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/auddec1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/auddec1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/audenc1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/auddec1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/auddec1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/audenc1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/audenc1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/audenc1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/auddec1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/auddec1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/audenc1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/release/audenc1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/audenc1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/audenc1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/release/audenc1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/auddec1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/audenc1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/auddec1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/audenc1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/auddec1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/audenc1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/auddec1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/auddec1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/auddec1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/auddec1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/auddec1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/audenc1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/auddec1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/auddec1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/audenc1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/audenc1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/audenc1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/auddec1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/auddec1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/audenc1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/release/audenc1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/audenc1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/audenc1.av5T'].suffix = 'v5T';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void IAUDENC1$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.audio1.IAUDENC1", "ti.sdo.ce.audio1");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.audio1.IAUDENC1.Module", "ti.sdo.ce.audio1");
        vo.init2(po, "ti.sdo.ce.audio1.IAUDENC1", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.audio1", "ti.sdo.ce.audio1"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IAUDENC1", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IAUDENC1");
        vo.seal(null);
    }

    void IAUDDEC1$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.audio1.IAUDDEC1", "ti.sdo.ce.audio1");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.audio1.IAUDDEC1.Module", "ti.sdo.ce.audio1");
        vo.init2(po, "ti.sdo.ce.audio1.IAUDDEC1", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.audio1", "ti.sdo.ce.audio1"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IAUDDEC1", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IAUDDEC1");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.audio1.IAUDENC1")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.audio1.IAUDDEC1")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.audio1")).add(pkgV);
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
        IAUDENC1$$OBJECTS();
        IAUDDEC1$$OBJECTS();
        IAUDENC1$$CONSTS();
        IAUDDEC1$$CONSTS();
        IAUDENC1$$CREATES();
        IAUDDEC1$$CREATES();
        IAUDENC1$$FUNCTIONS();
        IAUDDEC1$$FUNCTIONS();
        IAUDENC1$$SIZES();
        IAUDDEC1$$SIZES();
        IAUDENC1$$TYPES();
        IAUDDEC1$$TYPES();
        if (isROV) {
            IAUDENC1$$ROV();
            IAUDDEC1$$ROV();
        }//isROV
        $$SINGLETONS();
        IAUDENC1$$SINGLETONS();
        IAUDDEC1$$SINGLETONS();
        $$INITIALIZATION();
    }
}
