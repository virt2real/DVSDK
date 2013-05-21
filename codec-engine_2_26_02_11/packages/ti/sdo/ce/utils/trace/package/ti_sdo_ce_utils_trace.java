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

public class ti_sdo_ce_utils_trace
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.utils.trace.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.utils.trace", new Value.Obj("ti.sdo.ce.utils.trace", pkgP));
    }

    void TraceUtil$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.utils.trace.TraceUtil.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.utils.trace.TraceUtil", new Value.Obj("ti.sdo.ce.utils.trace.TraceUtil", po));
        pkgV.bind("TraceUtil", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ce.utils.trace.TraceUtil$$PipeCmdAlias", new Proto.Obj());
        om.bind("ti.sdo.ce.utils.trace.TraceUtil.PipeCmdAlias", new Proto.Str(spo, true));
        spo = (Proto.Obj)om.bind("ti.sdo.ce.utils.trace.TraceUtil$$Attrs", new Proto.Obj());
        om.bind("ti.sdo.ce.utils.trace.TraceUtil.Attrs", new Proto.Str(spo, true));
    }

    void TraceUtil$$CONSTS()
    {
        // module TraceUtil
        om.bind("ti.sdo.ce.utils.trace.TraceUtil.NO_TRACING", Global.newObject("localTraceMask", "*=", "localTraceFile", null, "dsp0TraceMask", "*=", "dsp0TraceFile", null, "dsp0BiosFile", null, "traceFileFlags", null, "refreshPeriod", 0L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})));
        om.bind("ti.sdo.ce.utils.trace.TraceUtil.DEFAULT_TRACING", Global.newObject("localTraceMask", "*=67", "localTraceFile", null, "dsp0TraceMask", "*=67", "dsp0TraceFile", null, "dsp0BiosFile", null, "traceFileFlags", null, "refreshPeriod", 300L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})));
        om.bind("ti.sdo.ce.utils.trace.TraceUtil.SOCRATES_TRACING", Global.newObject("localTraceMask", "*=67", "localTraceFile", "/tmp/cearmlog.txt", "dsp0TraceMask", "*=67", "dsp0TraceFile", "/tmp/cedsp0log.txt", "dsp0BiosFile", "/tmp/bioslog.dat", "traceFileFlags", "w", "refreshPeriod", 0L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{Global.newObject("alias", "socrates=on", "cmds", Global.newArray(new Object[]{"tracemask=*+5", "dsp0tracemask=*+5,ti.bios+3", "refreshperiod=200"})), Global.newObject("alias", "socrates=off", "cmds", Global.newArray(new Object[]{"tracemask=*-5", "refreshperiod=0", "dsp0tracemask=*-5,ti.bios-3"}))})));
        om.bind("ti.sdo.ce.utils.trace.TraceUtil.FULL_TRACING", Global.newObject("localTraceMask", "*=01234567", "localTraceFile", "trace/cearmlog.txt", "dsp0TraceMask", "*=01234567,ti.bios=01324567", "dsp0TraceFile", "trace/cedsp0log.txt", "dsp0BiosFile", "trace/bioslog.dat", "traceFileFlags", "w", "refreshPeriod", 100L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})));
    }

    void TraceUtil$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TraceUtil$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TraceUtil$$SIZES()
    {
    }

    void TraceUtil$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Module", "ti.sdo.ce.utils.trace");
        po.init("ti.sdo.ce.utils.trace.TraceUtil.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("NO_TRACING", (Proto)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"), Global.newObject("localTraceMask", "*=", "localTraceFile", null, "dsp0TraceMask", "*=", "dsp0TraceFile", null, "dsp0BiosFile", null, "traceFileFlags", null, "refreshPeriod", 0L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})), "rh");
                po.addFld("DEFAULT_TRACING", (Proto)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"), Global.newObject("localTraceMask", "*=67", "localTraceFile", null, "dsp0TraceMask", "*=67", "dsp0TraceFile", null, "dsp0BiosFile", null, "traceFileFlags", null, "refreshPeriod", 300L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})), "rh");
                po.addFld("SOCRATES_TRACING", (Proto)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"), Global.newObject("localTraceMask", "*=67", "localTraceFile", "/tmp/cearmlog.txt", "dsp0TraceMask", "*=67", "dsp0TraceFile", "/tmp/cedsp0log.txt", "dsp0BiosFile", "/tmp/bioslog.dat", "traceFileFlags", "w", "refreshPeriod", 0L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{Global.newObject("alias", "socrates=on", "cmds", Global.newArray(new Object[]{"tracemask=*+5", "dsp0tracemask=*+5,ti.bios+3", "refreshperiod=200"})), Global.newObject("alias", "socrates=off", "cmds", Global.newArray(new Object[]{"tracemask=*-5", "refreshperiod=0", "dsp0tracemask=*-5,ti.bios-3"}))})), "rh");
                po.addFld("FULL_TRACING", (Proto)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"), Global.newObject("localTraceMask", "*=01234567", "localTraceFile", "trace/cearmlog.txt", "dsp0TraceMask", "*=01234567,ti.bios=01324567", "dsp0TraceFile", "trace/cedsp0log.txt", "dsp0BiosFile", "trace/bioslog.dat", "traceFileFlags", "w", "refreshPeriod", 100L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})), "rh");
                po.addFld("attrs", (Proto)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"), Global.newObject("localTraceMask", "*=67", "localTraceFile", null, "dsp0TraceMask", "*=67", "dsp0TraceFile", null, "dsp0BiosFile", null, "traceFileFlags", null, "refreshPeriod", 300L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})), "wh");
        // struct TraceUtil.PipeCmdAlias
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil$$PipeCmdAlias", "ti.sdo.ce.utils.trace");
        po.init("ti.sdo.ce.utils.trace.TraceUtil.PipeCmdAlias", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("alias", $$T_Str, $$UNDEF, "w");
                po.addFld("cmds", new Proto.Arr($$T_Str, false), $$DEFAULT, "w");
        // struct TraceUtil.Attrs
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil$$Attrs", "ti.sdo.ce.utils.trace");
        po.init("ti.sdo.ce.utils.trace.TraceUtil.Attrs", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("localTraceMask", $$T_Str, $$UNDEF, "w");
                po.addFld("localTraceFile", $$T_Str, $$UNDEF, "w");
                po.addFld("dsp0TraceMask", $$T_Str, $$UNDEF, "w");
                po.addFld("dsp0TraceFile", $$T_Str, $$UNDEF, "w");
                po.addFld("dsp0BiosFile", $$T_Str, $$UNDEF, "w");
                po.addFld("traceFileFlags", $$T_Str, $$UNDEF, "w");
                po.addFld("refreshPeriod", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("cmdPipeFile", $$T_Str, $$UNDEF, "w");
                po.addFld("cmdAliases", new Proto.Arr((Proto)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.PipeCmdAlias", "ti.sdo.ce.utils.trace"), false), $$DEFAULT, "w");
    }

    void TraceUtil$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.utils.trace.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.utils.trace"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/utils/trace/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.utils.trace"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.utils.trace"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.utils.trace"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.utils.trace"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.utils.trace"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.utils.trace"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.utils.trace", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.utils.trace");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.utils.trace.");
        pkgV.bind("$vers", Global.newArray("1, 0, 1"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.utils.trace'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/TraceUtil.a86U',\n");
            sb.append("'lib/release/TraceUtil.a86U',\n");
            sb.append("'lib/release/TraceUtil.a470uC',\n");
            sb.append("'lib/debug/TraceUtil.av5T',\n");
            sb.append("'lib/release/TraceUtil.av5T',\n");
            sb.append("'lib/debug/TraceUtil.a470uC',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/TraceUtil.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/TraceUtil.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/TraceUtil.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/TraceUtil.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/TraceUtil.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/TraceUtil.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/debug/TraceUtil.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/TraceUtil.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/TraceUtil.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/TraceUtil.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/TraceUtil.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/TraceUtil.a470uC'].suffix = '470uC';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TraceUtil$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil", "ti.sdo.ce.utils.trace");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Module", "ti.sdo.ce.utils.trace");
        vo.init2(po, "ti.sdo.ce.utils.trace.TraceUtil", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.utils.trace", "ti.sdo.ce.utils.trace"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("PipeCmdAlias", om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.PipeCmdAlias", "ti.sdo.ce.utils.trace"));
        tdefs.add(om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.PipeCmdAlias", "ti.sdo.ce.utils.trace"));
        vo.bind("Attrs", om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"));
        tdefs.add(om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.utils.trace")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.utils.trace.TraceUtil$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./TraceUtil.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./TraceUtil.xdt");
        pkgV.bind("TraceUtil", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TraceUtil");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil", "ti.sdo.ce.utils.trace"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.utils.trace.TraceUtil")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.utils.trace")).add(pkgV);
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
        TraceUtil$$OBJECTS();
        TraceUtil$$CONSTS();
        TraceUtil$$CREATES();
        TraceUtil$$FUNCTIONS();
        TraceUtil$$SIZES();
        TraceUtil$$TYPES();
        if (isROV) {
            TraceUtil$$ROV();
        }//isROV
        $$SINGLETONS();
        TraceUtil$$SINGLETONS();
        $$INITIALIZATION();
    }
}
