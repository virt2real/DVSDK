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

public class ti_sdo_ce_audio
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.audio.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.audio", new Value.Obj("ti.sdo.ce.audio", pkgP));
    }

    void IAUDENC$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.audio.IAUDENC.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.audio.IAUDENC", new Value.Obj("ti.sdo.ce.audio.IAUDENC", po));
        pkgV.bind("IAUDENC", vo);
        // decls 
    }

    void IAUDDEC$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.audio.IAUDDEC.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.audio.IAUDDEC", new Value.Obj("ti.sdo.ce.audio.IAUDDEC", po));
        pkgV.bind("IAUDDEC", vo);
        // decls 
    }

    void IAUDENC$$CONSTS()
    {
        // interface IAUDENC
    }

    void IAUDDEC$$CONSTS()
    {
        // interface IAUDDEC
    }

    void IAUDENC$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IAUDDEC$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IAUDENC$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IAUDDEC$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IAUDENC$$SIZES()
    {
    }

    void IAUDDEC$$SIZES()
    {
    }

    void IAUDENC$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.audio.IAUDENC.Module", "ti.sdo.ce.audio");
        po.init("ti.sdo.ce.audio.IAUDENC.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.audio"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "AUDENC_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "AUDENC_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 3L, "rh");
    }

    void IAUDDEC$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.audio.IAUDDEC.Module", "ti.sdo.ce.audio");
        po.init("ti.sdo.ce.audio.IAUDDEC.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.audio"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "AUDDEC_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "AUDDEC_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 3L, "rh");
    }

    void IAUDENC$$ROV()
    {
    }

    void IAUDDEC$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.audio.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.audio"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/audio/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.audio"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.audio"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.audio"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.audio"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.audio"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.audio"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.audio", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.audio");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.audio.");
        pkgV.bind("$vers", Global.newArray("1, 0, 2"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.audio'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/release/audio.av4TCE',\n");
            sb.append("'lib/debug/audio.av4TCE',\n");
            sb.append("'lib/debug/audio.a86U',\n");
            sb.append("'lib/release/audio.a470uC',\n");
            sb.append("'lib/debug/audio.a470uC',\n");
            sb.append("'lib/debug/audio.av5T',\n");
            sb.append("'lib/release/audio.a86U',\n");
            sb.append("'lib/debug/audio.a674',\n");
            sb.append("'lib/release/audio.av5T',\n");
            sb.append("'lib/debug/audio.a64P',\n");
            sb.append("'lib/release/audio.a674',\n");
            sb.append("'lib/release/audio.a64P',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/release/audio.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/audio.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/audio.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/audio.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/audio.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/audio.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/audio.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/audio.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/audio.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/audio.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/audio.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/audio.a64P', {target: 'ti.targets.C64P'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/release/audio.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/audio.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/audio.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/audio.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/audio.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/audio.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/audio.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/audio.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/audio.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/audio.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/audio.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/audio.a64P'].suffix = '64P';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void IAUDENC$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.audio.IAUDENC", "ti.sdo.ce.audio");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.audio.IAUDENC.Module", "ti.sdo.ce.audio");
        vo.init2(po, "ti.sdo.ce.audio.IAUDENC", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.audio", "ti.sdo.ce.audio"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IAUDENC", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IAUDENC");
        vo.seal(null);
    }

    void IAUDDEC$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.audio.IAUDDEC", "ti.sdo.ce.audio");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.audio.IAUDDEC.Module", "ti.sdo.ce.audio");
        vo.init2(po, "ti.sdo.ce.audio.IAUDDEC", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.audio", "ti.sdo.ce.audio"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IAUDDEC", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IAUDDEC");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.audio.IAUDENC")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.audio.IAUDDEC")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.audio")).add(pkgV);
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
        IAUDENC$$OBJECTS();
        IAUDDEC$$OBJECTS();
        IAUDENC$$CONSTS();
        IAUDDEC$$CONSTS();
        IAUDENC$$CREATES();
        IAUDDEC$$CREATES();
        IAUDENC$$FUNCTIONS();
        IAUDDEC$$FUNCTIONS();
        IAUDENC$$SIZES();
        IAUDDEC$$SIZES();
        IAUDENC$$TYPES();
        IAUDDEC$$TYPES();
        if (isROV) {
            IAUDENC$$ROV();
            IAUDDEC$$ROV();
        }//isROV
        $$SINGLETONS();
        IAUDENC$$SINGLETONS();
        IAUDDEC$$SINGLETONS();
        $$INITIALIZATION();
    }
}
