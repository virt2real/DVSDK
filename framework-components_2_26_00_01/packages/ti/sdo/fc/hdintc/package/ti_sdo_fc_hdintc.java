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

public class ti_sdo_fc_hdintc
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
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.fc.hdintc.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.fc.hdintc", new Value.Obj("ti.sdo.fc.hdintc", pkgP));
    }

    void HDINTC$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.hdintc.HDINTC.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.hdintc.HDINTC", new Value.Obj("ti.sdo.fc.hdintc.HDINTC", po));
        pkgV.bind("HDINTC", vo);
        // decls 
    }

    void HDINTC$$CONSTS()
    {
        // module HDINTC
    }

    void HDINTC$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void HDINTC$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void HDINTC$$SIZES()
    {
    }

    void HDINTC$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.fc.hdintc.HDINTC.Module", "ti.sdo.fc.hdintc");
        po.init("ti.sdo.fc.hdintc.HDINTC.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("interruptVectorId_0", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
                po.addFld("interruptVectorId_1", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
                po.addFld("hdvicpInterruptEventNo_0", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
                po.addFld("hdvicpInterruptEventNo_1", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
                po.addFld("biosInterruptVectorId_0", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
                po.addFld("biosInterruptVectorId_1", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
                po.addFld("biosInterruptEventNo_0", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
                po.addFld("biosInterruptEventNo_1", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
                po.addFld("debug", $$T_Bool, false, "wh");
                po.addFld("trace", $$T_Bool, false, "wh");
                po.addFld("spinloop", $$T_Bool, false, "wh");
    }

    void HDINTC$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.fc.hdintc.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.fc.hdintc"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/hdintc/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.fc.hdintc"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.fc.hdintc"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.fc.hdintc"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.fc.hdintc"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.fc.hdintc"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.fc.hdintc"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.fc.hdintc", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.fc.hdintc");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.fc.hdintc.");
        pkgV.bind("$vers", Global.newArray("1, 0, 4"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.fc.hdintc'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug_trace/hdintc_fc.a64P',\n");
            sb.append("'lib/debug/hdintc_fc.a64P',\n");
            sb.append("'lib/trace/hdintc_fc.a64P',\n");
            sb.append("'lib/debug/hdintc_spinloop_fc.a64P',\n");
            sb.append("'lib/release/hdintc_fc.a64P',\n");
            sb.append("'lib/trace/hdintc_spinloop_fc.a64P',\n");
            sb.append("'lib/debug_trace/hdintc_spinloop_fc.a64P',\n");
            sb.append("'lib/release/hdintc_spinloop_fc.a64P',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug_trace/hdintc_fc.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/hdintc_fc.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/trace/hdintc_fc.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/hdintc_spinloop_fc.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/hdintc_fc.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/trace/hdintc_spinloop_fc.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug_trace/hdintc_spinloop_fc.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/hdintc_spinloop_fc.a64P', {target: 'ti.targets.C64P'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/hdintc_fc.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/hdintc_fc.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/trace/hdintc_fc.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/hdintc_spinloop_fc.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/hdintc_fc.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/trace/hdintc_spinloop_fc.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/hdintc_spinloop_fc.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/hdintc_spinloop_fc.a64P'].suffix = '64P';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void HDINTC$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.hdintc.HDINTC", "ti.sdo.fc.hdintc");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.hdintc.HDINTC.Module", "ti.sdo.fc.hdintc");
        vo.init2(po, "ti.sdo.fc.hdintc.HDINTC", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.fc.hdintc", "ti.sdo.fc.hdintc"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.hdintc")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.hdintc.HDINTC$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./HDINTC.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./HDINTC.xdt");
        pkgV.bind("HDINTC", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("HDINTC");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.hdintc.HDINTC", "ti.sdo.fc.hdintc"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.fc.hdintc.HDINTC")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.fc.hdintc")).add(pkgV);
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
        HDINTC$$OBJECTS();
        HDINTC$$CONSTS();
        HDINTC$$CREATES();
        HDINTC$$FUNCTIONS();
        HDINTC$$SIZES();
        HDINTC$$TYPES();
        if (isROV) {
            HDINTC$$ROV();
        }//isROV
        $$SINGLETONS();
        HDINTC$$SINGLETONS();
        $$INITIALIZATION();
    }
}
