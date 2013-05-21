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

public class ti_sdo_ce_video
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.video.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.video", new Value.Obj("ti.sdo.ce.video", pkgP));
    }

    void VIDENCConfig$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video.VIDENCConfig.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video.VIDENCConfig", new Value.Obj("ti.sdo.ce.video.VIDENCConfig", po));
        pkgV.bind("VIDENCConfig", vo);
        // decls 
    }

    void VIDDECConfig$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video.VIDDECConfig.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video.VIDDECConfig", new Value.Obj("ti.sdo.ce.video.VIDDECConfig", po));
        pkgV.bind("VIDDECConfig", vo);
        // decls 
    }

    void IVIDDEC$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video.IVIDDEC.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video.IVIDDEC", new Value.Obj("ti.sdo.ce.video.IVIDDEC", po));
        pkgV.bind("IVIDDEC", vo);
        // decls 
    }

    void IVIDENC$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video.IVIDENC.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video.IVIDENC", new Value.Obj("ti.sdo.ce.video.IVIDENC", po));
        pkgV.bind("IVIDENC", vo);
        // decls 
    }

    void VIDENCConfig$$CONSTS()
    {
        // module VIDENCConfig
    }

    void VIDDECConfig$$CONSTS()
    {
        // module VIDDECConfig
    }

    void IVIDDEC$$CONSTS()
    {
        // interface IVIDDEC
    }

    void IVIDENC$$CONSTS()
    {
        // interface IVIDENC
    }

    void VIDENCConfig$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VIDDECConfig$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IVIDDEC$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IVIDENC$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VIDENCConfig$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VIDDECConfig$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IVIDDEC$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IVIDENC$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VIDENCConfig$$SIZES()
    {
    }

    void VIDDECConfig$$SIZES()
    {
    }

    void IVIDDEC$$SIZES()
    {
    }

    void IVIDENC$$SIZES()
    {
    }

    void VIDENCConfig$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video.VIDENCConfig.Module", "ti.sdo.ce.video");
        po.init("ti.sdo.ce.video.VIDENCConfig.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void VIDDECConfig$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video.VIDDECConfig.Module", "ti.sdo.ce.video");
        po.init("ti.sdo.ce.video.VIDDECConfig.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void IVIDDEC$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video.IVIDDEC.Module", "ti.sdo.ce.video");
        po.init("ti.sdo.ce.video.IVIDDEC.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.video"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "VIDDEC_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "VIDDEC_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 3L, "rh");
                po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
                po.addFld("manageInBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
                po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
                po.addFld("manageDisplayBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void IVIDENC$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video.IVIDENC.Module", "ti.sdo.ce.video");
        po.init("ti.sdo.ce.video.IVIDENC.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.video"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "VIDENC_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "VIDENC_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 3L, "rh");
                po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
                po.addFld("manageInBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
                po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
                po.addFld("manageReconBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void VIDENCConfig$$ROV()
    {
    }

    void VIDDECConfig$$ROV()
    {
    }

    void IVIDDEC$$ROV()
    {
    }

    void IVIDENC$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.video.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.video"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/video/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.video"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.video"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.video"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.video"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.video"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.video"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.video", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.video");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.video.");
        pkgV.bind("$vers", Global.newArray("1, 0, 3"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.video'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/release/video.av4TCE',\n");
            sb.append("'lib/release/video.a86U',\n");
            sb.append("'lib/debug/video.av4TCE',\n");
            sb.append("'lib/debug/video.a674',\n");
            sb.append("'lib/release/video.a470uC',\n");
            sb.append("'lib/release/video.av5T',\n");
            sb.append("'lib/debug/video.a470uC',\n");
            sb.append("'lib/debug/video.a64P',\n");
            sb.append("'lib/release/video.a674',\n");
            sb.append("'lib/release/video.a64P',\n");
            sb.append("'lib/debug/video.a86U',\n");
            sb.append("'lib/debug/video.av5T',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/release/video.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/release/video.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/video.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/video.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/video.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/video.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/video.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/video.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/video.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/video.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/video.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/video.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/release/video.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/release/video.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/video.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/video.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/video.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/video.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/video.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/video.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/video.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/video.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/video.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/video.av5T'].suffix = 'v5T';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void VIDENCConfig$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video.VIDENCConfig", "ti.sdo.ce.video");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video.VIDENCConfig.Module", "ti.sdo.ce.video");
        vo.init2(po, "ti.sdo.ce.video.VIDENCConfig", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video", "ti.sdo.ce.video"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.video")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.video.VIDENCConfig$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./VIDENCConfig.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./VIDENCConfig.xdt");
        pkgV.bind("VIDENCConfig", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VIDENCConfig");
    }

    void VIDDECConfig$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video.VIDDECConfig", "ti.sdo.ce.video");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video.VIDDECConfig.Module", "ti.sdo.ce.video");
        vo.init2(po, "ti.sdo.ce.video.VIDDECConfig", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video", "ti.sdo.ce.video"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.video")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.video.VIDDECConfig$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./VIDDECConfig.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./VIDDECConfig.xdt");
        pkgV.bind("VIDDECConfig", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VIDDECConfig");
    }

    void IVIDDEC$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video.IVIDDEC", "ti.sdo.ce.video");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video.IVIDDEC.Module", "ti.sdo.ce.video");
        vo.init2(po, "ti.sdo.ce.video.IVIDDEC", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video", "ti.sdo.ce.video"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IVIDDEC", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IVIDDEC");
        vo.seal(null);
    }

    void IVIDENC$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video.IVIDENC", "ti.sdo.ce.video");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video.IVIDENC.Module", "ti.sdo.ce.video");
        vo.init2(po, "ti.sdo.ce.video.IVIDENC", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video", "ti.sdo.ce.video"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IVIDENC", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IVIDENC");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.video.VIDENCConfig", "ti.sdo.ce.video"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.video.VIDDECConfig", "ti.sdo.ce.video"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.video.VIDENCConfig")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.video.VIDDECConfig")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.video.IVIDDEC")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.video.IVIDENC")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.video")).add(pkgV);
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
        VIDENCConfig$$OBJECTS();
        VIDDECConfig$$OBJECTS();
        IVIDDEC$$OBJECTS();
        IVIDENC$$OBJECTS();
        VIDENCConfig$$CONSTS();
        VIDDECConfig$$CONSTS();
        IVIDDEC$$CONSTS();
        IVIDENC$$CONSTS();
        VIDENCConfig$$CREATES();
        VIDDECConfig$$CREATES();
        IVIDDEC$$CREATES();
        IVIDENC$$CREATES();
        VIDENCConfig$$FUNCTIONS();
        VIDDECConfig$$FUNCTIONS();
        IVIDDEC$$FUNCTIONS();
        IVIDENC$$FUNCTIONS();
        VIDENCConfig$$SIZES();
        VIDDECConfig$$SIZES();
        IVIDDEC$$SIZES();
        IVIDENC$$SIZES();
        VIDENCConfig$$TYPES();
        VIDDECConfig$$TYPES();
        IVIDDEC$$TYPES();
        IVIDENC$$TYPES();
        if (isROV) {
            VIDENCConfig$$ROV();
            VIDDECConfig$$ROV();
            IVIDDEC$$ROV();
            IVIDENC$$ROV();
        }//isROV
        $$SINGLETONS();
        VIDENCConfig$$SINGLETONS();
        VIDDECConfig$$SINGLETONS();
        IVIDDEC$$SINGLETONS();
        IVIDENC$$SINGLETONS();
        $$INITIALIZATION();
    }
}
