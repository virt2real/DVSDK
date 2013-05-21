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

public class ti_sdo_ce_ipc_noOS
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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.ipc");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.ipc.noOS.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.ipc.noOS", new Value.Obj("ti.sdo.ce.ipc.noOS", pkgP));
    }

    void Ipc$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.ipc.noOS.Ipc.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.ipc.noOS.Ipc", new Value.Obj("ti.sdo.ce.ipc.noOS.Ipc", po));
        pkgV.bind("Ipc", vo);
        // decls 
        om.bind("ti.sdo.ce.ipc.noOS.Ipc.ArmDspLinkConfigMemTableEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", "ti.sdo.ce.ipc.noOS"));
        om.bind("ti.sdo.ce.ipc.noOS.Ipc.DspManagement", om.findStrict("ti.sdo.ce.ipc.IIpc.DspManagement", "ti.sdo.ce.ipc.noOS"));
        om.bind("ti.sdo.ce.ipc.noOS.Ipc.ArmDspLinkConfig", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc.noOS"));
        om.bind("ti.sdo.ce.ipc.noOS.Ipc.LinkConfigEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", "ti.sdo.ce.ipc.noOS"));
    }

    void Ipc$$CONSTS()
    {
        // module Ipc
    }

    void Ipc$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Ipc$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Ipc$$SIZES()
    {
    }

    void Ipc$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.noOS.Ipc.Module", "ti.sdo.ce.ipc.noOS");
        po.init("ti.sdo.ce.ipc.noOS.Ipc.Module", om.findStrict("ti.sdo.ce.ipc.IIpc.Module", "ti.sdo.ce.ipc.noOS"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("debug", $$T_Bool, false, "wh");
    }

    void Ipc$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.ipc.noOS.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.ipc.noOS"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/ipc/noOS/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.ipc.noOS"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.ipc.noOS"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.ipc.noOS"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.ipc.noOS"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.ipc.noOS"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.ipc.noOS"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.ipc.noOS", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.ipc.noOS");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.ipc.noOS.");
        pkgV.bind("$vers", Global.newArray("2, 0, 1"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.ipc.noOS'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/release/ipc_noOS.av5T',\n");
            sb.append("'lib/debug/ipc_noOS.a86U',\n");
            sb.append("'lib/release/ipc_noOS.av4TCE',\n");
            sb.append("'lib/debug/ipc_noOS.av4TCE',\n");
            sb.append("'lib/release/ipc_noOS.a86U',\n");
            sb.append("'lib/release/ipc_noOS.a470uC',\n");
            sb.append("'lib/debug/ipc_noOS.a470uC',\n");
            sb.append("'lib/debug/ipc_noOS.av5T',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/release/ipc_noOS.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/ipc_noOS.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/ipc_noOS.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/ipc_noOS.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/release/ipc_noOS.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/ipc_noOS.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/ipc_noOS.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/ipc_noOS.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_noOS.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_noOS.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_noOS.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_noOS.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_noOS.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_noOS.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_noOS.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_noOS.av5T'].suffix = 'v5T';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Ipc$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.ipc.noOS.Ipc", "ti.sdo.ce.ipc.noOS");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.noOS.Ipc.Module", "ti.sdo.ce.ipc.noOS");
        vo.init2(po, "ti.sdo.ce.ipc.noOS.Ipc", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.ipc.noOS", "ti.sdo.ce.ipc.noOS"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("ArmDspLinkConfigMemTableEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", "ti.sdo.ce.ipc.noOS"));
        tdefs.add(om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", "ti.sdo.ce.ipc.noOS"));
        vo.bind("DspManagement", om.findStrict("ti.sdo.ce.ipc.IIpc.DspManagement", "ti.sdo.ce.ipc.noOS"));
        vo.bind("ArmDspLinkConfig", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc.noOS"));
        tdefs.add(om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc.noOS"));
        vo.bind("LinkConfigEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", "ti.sdo.ce.ipc.noOS"));
        tdefs.add(om.findStrict("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", "ti.sdo.ce.ipc.noOS"));
        vo.bind("BootAndLoadDsp", om.findStrict("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp", "ti.sdo.ce.ipc.noOS"));
        vo.bind("BootDspAutonomously", om.findStrict("ti.sdo.ce.ipc.IIpc.BootDspAutonomously", "ti.sdo.ce.ipc.noOS"));
        vo.bind("None", om.findStrict("ti.sdo.ce.ipc.IIpc.None", "ti.sdo.ce.ipc.noOS"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.ipc.noOS")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.ipc.noOS.Ipc$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Ipc.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Ipc.xdt");
        pkgV.bind("Ipc", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Ipc");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.ipc.noOS.Ipc", "ti.sdo.ce.ipc.noOS"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.ipc.noOS.Ipc")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.ipc.noOS")).add(pkgV);
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
        Ipc$$OBJECTS();
        Ipc$$CONSTS();
        Ipc$$CREATES();
        Ipc$$FUNCTIONS();
        Ipc$$SIZES();
        Ipc$$TYPES();
        if (isROV) {
            Ipc$$ROV();
        }//isROV
        $$SINGLETONS();
        Ipc$$SINGLETONS();
        $$INITIALIZATION();
    }
}
