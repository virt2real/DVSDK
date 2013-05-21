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

public class ti_sdo_ce_examples_extensions_scale
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.examples.extensions.scale.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.examples.extensions.scale", new Value.Obj("ti.sdo.ce.examples.extensions.scale", pkgP));
    }

    void ISCALE$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.examples.extensions.scale.ISCALE.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.examples.extensions.scale.ISCALE", new Value.Obj("ti.sdo.ce.examples.extensions.scale.ISCALE", po));
        pkgV.bind("ISCALE", vo);
        // decls 
    }

    void ISCALE$$CONSTS()
    {
        // interface ISCALE
    }

    void ISCALE$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ISCALE$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void ISCALE$$SIZES()
    {
    }

    void ISCALE$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.examples.extensions.scale.ISCALE.Module", "ti.sdo.ce.examples.extensions.scale");
        po.init("ti.sdo.ce.examples.extensions.scale.ISCALE.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.examples.extensions.scale"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverFxns", $$T_Str, "SCALE_SKEL", "wh");
                po.addFld("stubFxns", $$T_Str, "SCALE_STUBS", "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
    }

    void ISCALE$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.examples.extensions.scale.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.examples.extensions.scale"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/examples/extensions/scale/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.examples.extensions.scale"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.examples.extensions.scale"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.examples.extensions.scale"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.examples.extensions.scale"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.examples.extensions.scale"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.examples.extensions.scale"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.examples.extensions.scale", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.examples.extensions.scale");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.examples.extensions.scale.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.examples.extensions.scale'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/scale_debug.a470uC',\n");
            sb.append("'lib/scale.a64P',\n");
            sb.append("'lib/scale_debug.a86U',\n");
            sb.append("'lib/scale_debug.av5T',\n");
            sb.append("'lib/scale.av4TCE',\n");
            sb.append("'lib/scale_debug.a674',\n");
            sb.append("'lib/scale.a470uC',\n");
            sb.append("'lib/scale.a86U',\n");
            sb.append("'lib/scale_debug.a64P',\n");
            sb.append("'lib/scale.av5T',\n");
            sb.append("'lib/scale_debug.av4TCE',\n");
            sb.append("'lib/scale.a674',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/scale_debug.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/scale.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/scale_debug.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/scale_debug.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/scale.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/scale_debug.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/scale.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/scale.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/scale_debug.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/scale.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/scale_debug.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/scale.a674', {target: 'ti.targets.C674'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/scale_debug.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/scale.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/scale_debug.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/scale_debug.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/scale.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/scale_debug.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/scale.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/scale.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/scale_debug.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/scale.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/scale_debug.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/scale.a674'].suffix = '674';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void ISCALE$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.examples.extensions.scale.ISCALE", "ti.sdo.ce.examples.extensions.scale");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.examples.extensions.scale.ISCALE.Module", "ti.sdo.ce.examples.extensions.scale");
        vo.init2(po, "ti.sdo.ce.examples.extensions.scale.ISCALE", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.examples.extensions.scale", "ti.sdo.ce.examples.extensions.scale"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ISCALE", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ISCALE");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.examples.extensions.scale.ISCALE")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.examples.extensions.scale")).add(pkgV);
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
        ISCALE$$OBJECTS();
        ISCALE$$CONSTS();
        ISCALE$$CREATES();
        ISCALE$$FUNCTIONS();
        ISCALE$$SIZES();
        ISCALE$$TYPES();
        if (isROV) {
            ISCALE$$ROV();
        }//isROV
        $$SINGLETONS();
        ISCALE$$SINGLETONS();
        $$INITIALIZATION();
    }
}
