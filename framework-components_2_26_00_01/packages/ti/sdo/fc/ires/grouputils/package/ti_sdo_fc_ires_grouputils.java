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

public class ti_sdo_fc_ires_grouputils
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.fc.ires.grouputils.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.fc.ires.grouputils", new Value.Obj("ti.sdo.fc.ires.grouputils", pkgP));
    }

    void GROUPUTILS$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.ires.grouputils.GROUPUTILS.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.ires.grouputils.GROUPUTILS", new Value.Obj("ti.sdo.fc.ires.grouputils.GROUPUTILS", po));
        pkgV.bind("GROUPUTILS", vo);
        // decls 
    }

    void GROUPUTILS$$CONSTS()
    {
        // module GROUPUTILS
        om.bind("ti.sdo.fc.ires.grouputils.GROUPUTILS.autoRegister", true);
    }

    void GROUPUTILS$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void GROUPUTILS$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void GROUPUTILS$$SIZES()
    {
    }

    void GROUPUTILS$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.grouputils.GROUPUTILS.Module", "ti.sdo.fc.ires.grouputils");
        po.init("ti.sdo.fc.ires.grouputils.GROUPUTILS.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("autoRegister", $$T_Bool, true, "rh");
                po.addFld("ipcKeyBase", Proto.Elm.newCNum("(xdc_UInt)"), 0x534C4954L, "wh");
                po.addFld("debug", $$T_Bool, false, "wh");
                po.addFld("trace", $$T_Bool, false, "wh");
                po.addFld("lockScratchGroupFxn", $$T_Str, null, "wh");
                po.addFld("unlockScratchGroupFxn", $$T_Str, null, "wh");
                po.addFld("scratchFxnPackage", $$T_Str, null, "wh");
                po.addFld("semCreateFxn", $$T_Str, null, "wh");
                po.addFld("semDeleteFxn", $$T_Str, null, "wh");
                po.addFld("semPendFxn", $$T_Str, null, "wh");
                po.addFld("semPostFxn", $$T_Str, null, "wh");
    }

    void GROUPUTILS$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.fc.ires.grouputils.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.fc.ires.grouputils"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/ires/grouputils/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.fc.ires.grouputils"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.fc.ires.grouputils"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.fc.ires.grouputils"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.fc.ires.grouputils"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.fc.ires.grouputils"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.fc.ires.grouputils"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.fc.ires.grouputils", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.fc.ires.grouputils");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.fc.ires.grouputils.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.fc.ires.grouputils'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/release/grouputils.a470uC',\n");
            sb.append("'lib/release/grouputils.a470MV',\n");
            sb.append("'lib/trace/grouputils.a470uC',\n");
            sb.append("'lib/trace/grouputils.a470MV',\n");
            sb.append("'lib/debug_trace/grouputils.a470uC',\n");
            sb.append("'lib/debug_trace/grouputils.a470MV',\n");
            sb.append("'lib/release/grouputils.a86U',\n");
            sb.append("'lib/release/grouputils.av5T',\n");
            sb.append("'lib/debug/grouputils.a9t',\n");
            sb.append("'lib/trace/grouputils.a86U',\n");
            sb.append("'lib/trace/grouputils.av5T',\n");
            sb.append("'lib/trace/grouputils.a9t',\n");
            sb.append("'lib/debug_trace/grouputils.a86U',\n");
            sb.append("'lib/debug_trace/grouputils.av5T',\n");
            sb.append("'lib/debug_trace/grouputils.a9t',\n");
            sb.append("'lib/debug/grouputils.a470uC',\n");
            sb.append("'lib/release/grouputils.a9t',\n");
            sb.append("'lib/debug/grouputils.a86U',\n");
            sb.append("'lib/debug/grouputils.a470MV',\n");
            sb.append("'lib/debug/grouputils.av5T',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/release/grouputils.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/grouputils.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/trace/grouputils.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/trace/grouputils.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug_trace/grouputils.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug_trace/grouputils.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/release/grouputils.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/grouputils.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/grouputils.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/trace/grouputils.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/trace/grouputils.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/trace/grouputils.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/debug_trace/grouputils.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug_trace/grouputils.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug_trace/grouputils.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/debug/grouputils.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/grouputils.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/debug/grouputils.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/grouputils.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug/grouputils.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/release/grouputils.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/grouputils.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/trace/grouputils.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/trace/grouputils.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/grouputils.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/grouputils.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/release/grouputils.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/grouputils.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/grouputils.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/trace/grouputils.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/trace/grouputils.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/trace/grouputils.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/grouputils.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/grouputils.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/grouputils.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/debug/grouputils.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/grouputils.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/debug/grouputils.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/grouputils.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug/grouputils.av5T'].suffix = 'v5T';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void GROUPUTILS$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.ires.grouputils.GROUPUTILS", "ti.sdo.fc.ires.grouputils");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.ires.grouputils.GROUPUTILS.Module", "ti.sdo.fc.ires.grouputils");
        vo.init2(po, "ti.sdo.fc.ires.grouputils.GROUPUTILS", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.fc.ires.grouputils", "ti.sdo.fc.ires.grouputils"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.ires.grouputils")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.ires.grouputils.GROUPUTILS$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./GROUPUTILS.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./GROUPUTILS.xdt");
        pkgV.bind("GROUPUTILS", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GROUPUTILS");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.ires.grouputils.GROUPUTILS", "ti.sdo.fc.ires.grouputils"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.fc.ires.grouputils.GROUPUTILS")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.fc.ires.grouputils")).add(pkgV);
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
        GROUPUTILS$$OBJECTS();
        GROUPUTILS$$CONSTS();
        GROUPUTILS$$CREATES();
        GROUPUTILS$$FUNCTIONS();
        GROUPUTILS$$SIZES();
        GROUPUTILS$$TYPES();
        if (isROV) {
            GROUPUTILS$$ROV();
        }//isROV
        $$SINGLETONS();
        GROUPUTILS$$SINGLETONS();
        $$INITIALIZATION();
    }
}
