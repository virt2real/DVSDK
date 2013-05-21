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

public class ti_sdo_ce_image
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.image.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.image", new Value.Obj("ti.sdo.ce.image", pkgP));
    }

    void IMGDECConfig$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.image.IMGDECConfig.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.image.IMGDECConfig", new Value.Obj("ti.sdo.ce.image.IMGDECConfig", po));
        pkgV.bind("IMGDECConfig", vo);
        // decls 
    }

    void IMGENCConfig$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.image.IMGENCConfig.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.image.IMGENCConfig", new Value.Obj("ti.sdo.ce.image.IMGENCConfig", po));
        pkgV.bind("IMGENCConfig", vo);
        // decls 
    }

    void IIMGDEC$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.image.IIMGDEC.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.image.IIMGDEC", new Value.Obj("ti.sdo.ce.image.IIMGDEC", po));
        pkgV.bind("IIMGDEC", vo);
        // decls 
    }

    void IIMGENC$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.image.IIMGENC.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.image.IIMGENC", new Value.Obj("ti.sdo.ce.image.IIMGENC", po));
        pkgV.bind("IIMGENC", vo);
        // decls 
    }

    void IMGDECConfig$$CONSTS()
    {
        // module IMGDECConfig
    }

    void IMGENCConfig$$CONSTS()
    {
        // module IMGENCConfig
    }

    void IIMGDEC$$CONSTS()
    {
        // interface IIMGDEC
    }

    void IIMGENC$$CONSTS()
    {
        // interface IIMGENC
    }

    void IMGDECConfig$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IMGENCConfig$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IIMGDEC$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IIMGENC$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IMGDECConfig$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IMGENCConfig$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IIMGDEC$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IIMGENC$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IMGDECConfig$$SIZES()
    {
    }

    void IMGENCConfig$$SIZES()
    {
    }

    void IIMGDEC$$SIZES()
    {
    }

    void IIMGENC$$SIZES()
    {
    }

    void IMGDECConfig$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image.IMGDECConfig.Module", "ti.sdo.ce.image");
        po.init("ti.sdo.ce.image.IMGDECConfig.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void IMGENCConfig$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image.IMGENCConfig.Module", "ti.sdo.ce.image");
        po.init("ti.sdo.ce.image.IMGENCConfig.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void IIMGDEC$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image.IIMGDEC.Module", "ti.sdo.ce.image");
        po.init("ti.sdo.ce.image.IIMGDEC.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.image"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "IMGDEC_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "IMGDEC_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 3L, "rh");
                po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
                po.addFld("manageInBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
                po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void IIMGENC$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image.IIMGENC.Module", "ti.sdo.ce.image");
        po.init("ti.sdo.ce.image.IIMGENC.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.image"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "IMGENC_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "IMGENC_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 3L, "rh");
                po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
                po.addFld("manageInBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
                po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void IMGDECConfig$$ROV()
    {
    }

    void IMGENCConfig$$ROV()
    {
    }

    void IIMGDEC$$ROV()
    {
    }

    void IIMGENC$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.image.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.image"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/image/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.image"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.image"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.image"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.image"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.image"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.image"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.image", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.image");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.image.");
        pkgV.bind("$vers", Global.newArray("1, 0, 3"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.image'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/image.av5T',\n");
            sb.append("'lib/release/image.a86U',\n");
            sb.append("'lib/release/image.av4TCE',\n");
            sb.append("'lib/debug/image.a674',\n");
            sb.append("'lib/debug/image.av4TCE',\n");
            sb.append("'lib/release/image.av5T',\n");
            sb.append("'lib/release/image.a470uC',\n");
            sb.append("'lib/debug/image.a64P',\n");
            sb.append("'lib/debug/image.a470uC',\n");
            sb.append("'lib/release/image.a674',\n");
            sb.append("'lib/release/image.a64P',\n");
            sb.append("'lib/debug/image.a86U',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/image.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/image.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/image.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/image.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/image.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/release/image.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/image.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/image.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/image.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/image.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/image.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/image.a86U', {target: 'gnu.targets.Linux86'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/debug/image.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/image.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/image.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/image.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/image.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/release/image.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/image.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/image.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/image.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/image.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/image.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/image.a86U'].suffix = '86U';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void IMGDECConfig$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.image.IMGDECConfig", "ti.sdo.ce.image");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image.IMGDECConfig.Module", "ti.sdo.ce.image");
        vo.init2(po, "ti.sdo.ce.image.IMGDECConfig", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.image", "ti.sdo.ce.image"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.image")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.image.IMGDECConfig$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./IMGDECConfig.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./IMGDECConfig.xdt");
        pkgV.bind("IMGDECConfig", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IMGDECConfig");
    }

    void IMGENCConfig$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.image.IMGENCConfig", "ti.sdo.ce.image");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image.IMGENCConfig.Module", "ti.sdo.ce.image");
        vo.init2(po, "ti.sdo.ce.image.IMGENCConfig", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.image", "ti.sdo.ce.image"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.image")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.image.IMGENCConfig$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./IMGENCConfig.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./IMGENCConfig.xdt");
        pkgV.bind("IMGENCConfig", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IMGENCConfig");
    }

    void IIMGDEC$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.image.IIMGDEC", "ti.sdo.ce.image");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image.IIMGDEC.Module", "ti.sdo.ce.image");
        vo.init2(po, "ti.sdo.ce.image.IIMGDEC", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.image", "ti.sdo.ce.image"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IIMGDEC", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IIMGDEC");
        vo.seal(null);
    }

    void IIMGENC$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.image.IIMGENC", "ti.sdo.ce.image");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.image.IIMGENC.Module", "ti.sdo.ce.image");
        vo.init2(po, "ti.sdo.ce.image.IIMGENC", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.image", "ti.sdo.ce.image"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IIMGENC", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IIMGENC");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.image.IMGDECConfig", "ti.sdo.ce.image"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.image.IMGENCConfig", "ti.sdo.ce.image"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.image.IMGDECConfig")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.image.IMGENCConfig")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.image.IIMGDEC")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.image.IIMGENC")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.image")).add(pkgV);
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
        IMGDECConfig$$OBJECTS();
        IMGENCConfig$$OBJECTS();
        IIMGDEC$$OBJECTS();
        IIMGENC$$OBJECTS();
        IMGDECConfig$$CONSTS();
        IMGENCConfig$$CONSTS();
        IIMGDEC$$CONSTS();
        IIMGENC$$CONSTS();
        IMGDECConfig$$CREATES();
        IMGENCConfig$$CREATES();
        IIMGDEC$$CREATES();
        IIMGENC$$CREATES();
        IMGDECConfig$$FUNCTIONS();
        IMGENCConfig$$FUNCTIONS();
        IIMGDEC$$FUNCTIONS();
        IIMGENC$$FUNCTIONS();
        IMGDECConfig$$SIZES();
        IMGENCConfig$$SIZES();
        IIMGDEC$$SIZES();
        IIMGENC$$SIZES();
        IMGDECConfig$$TYPES();
        IMGENCConfig$$TYPES();
        IIMGDEC$$TYPES();
        IIMGENC$$TYPES();
        if (isROV) {
            IMGDECConfig$$ROV();
            IMGENCConfig$$ROV();
            IIMGDEC$$ROV();
            IIMGENC$$ROV();
        }//isROV
        $$SINGLETONS();
        IMGDECConfig$$SINGLETONS();
        IMGENCConfig$$SINGLETONS();
        IIMGDEC$$SINGLETONS();
        IIMGENC$$SINGLETONS();
        $$INITIALIZATION();
    }
}
