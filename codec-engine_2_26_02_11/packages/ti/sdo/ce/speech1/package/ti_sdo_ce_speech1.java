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

public class ti_sdo_ce_speech1
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.speech1.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.speech1", new Value.Obj("ti.sdo.ce.speech1", pkgP));
    }

    void ISPHENC1$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.speech1.ISPHENC1.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.speech1.ISPHENC1", new Value.Obj("ti.sdo.ce.speech1.ISPHENC1", po));
        pkgV.bind("ISPHENC1", vo);
        // decls 
    }

    void ISPHDEC1$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.speech1.ISPHDEC1.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.speech1.ISPHDEC1", new Value.Obj("ti.sdo.ce.speech1.ISPHDEC1", po));
        pkgV.bind("ISPHDEC1", vo);
        // decls 
    }

    void ISPHENC1$$CONSTS()
    {
        // interface ISPHENC1
    }

    void ISPHDEC1$$CONSTS()
    {
        // interface ISPHDEC1
    }

    void ISPHENC1$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ISPHDEC1$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ISPHENC1$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void ISPHDEC1$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void ISPHENC1$$SIZES()
    {
    }

    void ISPHDEC1$$SIZES()
    {
    }

    void ISPHENC1$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.speech1.ISPHENC1.Module", "ti.sdo.ce.speech1");
        po.init("ti.sdo.ce.speech1.ISPHENC1.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.speech1"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "SPHENC1_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "SPHENC1_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
    }

    void ISPHDEC1$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.speech1.ISPHDEC1.Module", "ti.sdo.ce.speech1");
        po.init("ti.sdo.ce.speech1.ISPHDEC1.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.speech1"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "SPHDEC1_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "SPHDEC1_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
    }

    void ISPHENC1$$ROV()
    {
    }

    void ISPHDEC1$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.speech1.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.speech1"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/speech1/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.speech1"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.speech1"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.speech1"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.speech1"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.speech1"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.speech1"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.speech1", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.speech1");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.speech1.");
        pkgV.bind("$vers", Global.newArray("1, 0, 1"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.speech1'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/release/sphenc1.a86U',\n");
            sb.append("'lib/release/sphenc1.av5T',\n");
            sb.append("'lib/release/sphenc1.a674',\n");
            sb.append("'lib/release/sphdec1.a64P',\n");
            sb.append("'lib/debug/sphdec1.av4TCE',\n");
            sb.append("'lib/debug/sphdec1.a470uC',\n");
            sb.append("'lib/debug/sphenc1.av4TCE',\n");
            sb.append("'lib/debug/sphdec1.a64P',\n");
            sb.append("'lib/debug/sphenc1.a64P',\n");
            sb.append("'lib/debug/sphenc1.a470uC',\n");
            sb.append("'lib/release/sphdec1.a86U',\n");
            sb.append("'lib/release/sphdec1.av4TCE',\n");
            sb.append("'lib/release/sphdec1.av5T',\n");
            sb.append("'lib/release/sphdec1.a674',\n");
            sb.append("'lib/release/sphdec1.a470uC',\n");
            sb.append("'lib/release/sphenc1.av4TCE',\n");
            sb.append("'lib/debug/sphenc1.a86U',\n");
            sb.append("'lib/debug/sphdec1.a86U',\n");
            sb.append("'lib/debug/sphdec1.av5T',\n");
            sb.append("'lib/debug/sphenc1.av5T',\n");
            sb.append("'lib/release/sphenc1.a64P',\n");
            sb.append("'lib/debug/sphenc1.a674',\n");
            sb.append("'lib/debug/sphdec1.a674',\n");
            sb.append("'lib/release/sphenc1.a470uC',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/release/sphenc1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/sphenc1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/sphenc1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/sphdec1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/sphdec1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/sphdec1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/sphenc1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/sphdec1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/sphenc1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/sphenc1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/sphdec1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/sphdec1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/release/sphdec1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/sphdec1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/sphdec1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/sphenc1.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/sphenc1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/sphdec1.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/sphdec1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/sphenc1.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/sphenc1.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/sphenc1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/sphdec1.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/sphenc1.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/release/sphenc1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/sphenc1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/sphenc1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/sphdec1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/sphdec1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/sphdec1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/sphenc1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/sphdec1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/sphenc1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/sphenc1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/sphdec1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/sphdec1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/release/sphdec1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/sphdec1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/sphdec1.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/sphenc1.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/sphenc1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/sphdec1.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/sphdec1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/sphenc1.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/sphenc1.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/sphenc1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/sphdec1.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/sphenc1.a470uC'].suffix = '470uC';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void ISPHENC1$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.speech1.ISPHENC1", "ti.sdo.ce.speech1");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.speech1.ISPHENC1.Module", "ti.sdo.ce.speech1");
        vo.init2(po, "ti.sdo.ce.speech1.ISPHENC1", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.speech1", "ti.sdo.ce.speech1"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ISPHENC1", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ISPHENC1");
        vo.seal(null);
    }

    void ISPHDEC1$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.speech1.ISPHDEC1", "ti.sdo.ce.speech1");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.speech1.ISPHDEC1.Module", "ti.sdo.ce.speech1");
        vo.init2(po, "ti.sdo.ce.speech1.ISPHDEC1", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.speech1", "ti.sdo.ce.speech1"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ISPHDEC1", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ISPHDEC1");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.speech1.ISPHENC1")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.speech1.ISPHDEC1")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.speech1")).add(pkgV);
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
        ISPHENC1$$OBJECTS();
        ISPHDEC1$$OBJECTS();
        ISPHENC1$$CONSTS();
        ISPHDEC1$$CONSTS();
        ISPHENC1$$CREATES();
        ISPHDEC1$$CREATES();
        ISPHENC1$$FUNCTIONS();
        ISPHDEC1$$FUNCTIONS();
        ISPHENC1$$SIZES();
        ISPHDEC1$$SIZES();
        ISPHENC1$$TYPES();
        ISPHDEC1$$TYPES();
        if (isROV) {
            ISPHENC1$$ROV();
            ISPHDEC1$$ROV();
        }//isROV
        $$SINGLETONS();
        ISPHENC1$$SINGLETONS();
        ISPHDEC1$$SINGLETONS();
        $$INITIALIZATION();
    }
}
