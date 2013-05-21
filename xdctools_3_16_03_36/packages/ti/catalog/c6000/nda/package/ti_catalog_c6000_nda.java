/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-u15
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.*;

public class ti_catalog_c6000_nda
{
    static final String VERS = "@(#) xdc-u15\n";

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
        Global.callFxn("loadPackage", xdcO, "xdc.platform");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "ti.catalog");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.catalog.c6000.nda.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.catalog.c6000.nda", new Value.Obj("ti.catalog.c6000.nda", pkgP));
    }

    void Tesla$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c6000.nda.Tesla.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c6000.nda.Tesla", new Value.Obj("ti.catalog.c6000.nda.Tesla", po));
        pkgV.bind("Tesla", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c6000.nda.Tesla.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c6000.nda.Tesla$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c6000.nda.Tesla.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c6000.nda.Tesla$$Params", new Proto.Obj());
        om.bind("ti.catalog.c6000.nda.Tesla.Params", new Proto.Str(po, true));
    }

    void Tesla$$CONSTS()
    {
        // module Tesla
    }

    void Tesla$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c6000.nda.Tesla$$create", new Proto.Fxn(om.findStrict("ti.catalog.c6000.nda.Tesla.Module", "ti.catalog.c6000.nda"), om.findStrict("ti.catalog.c6000.nda.Tesla.Instance", "ti.catalog.c6000.nda"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c6000.nda.Tesla.Params", "ti.catalog.c6000.nda"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c6000$nda$Tesla$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c6000.nda.Tesla'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c6000.nda.Tesla.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c6000.nda']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c6000.nda.Tesla$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c6000.nda.Tesla.Module", "ti.catalog.c6000.nda"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c6000.nda.Tesla$$Object", "ti.catalog.c6000.nda"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c6000.nda.Tesla.Params", "ti.catalog.c6000.nda"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c6000$nda$Tesla$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c6000.nda.Tesla'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Tesla$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Tesla$$SIZES()
    {
    }

    void Tesla$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c6000/nda/Tesla.xs");
        om.bind("ti.catalog.c6000.nda.Tesla$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c6000.nda.Tesla.Module", "ti.catalog.c6000.nda");
        po.init("ti.catalog.c6000.nda.Tesla.Module", om.findStrict("ti.catalog.ICpuDataSheet.Module", "ti.catalog.c6000.nda"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c6000.nda.Tesla$$create", "ti.catalog.c6000.nda"), Global.get("ti$catalog$c6000$nda$Tesla$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c6000.nda.Tesla$$construct", "ti.catalog.c6000.nda"), Global.get("ti$catalog$c6000$nda$Tesla$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c6000.nda.Tesla$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c6000.nda.Tesla$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c6000.nda.Tesla$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c6000.nda.Tesla$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c6000.nda.Tesla.Instance", "ti.catalog.c6000.nda");
        po.init("ti.catalog.c6000.nda.Tesla.Instance", om.findStrict("ti.catalog.ICpuDataSheet.Instance", "ti.catalog.c6000.nda"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("minProgUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
                po.addFld("minDataUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
                po.addFld("dataWordSize", Proto.Elm.newCNum("(xdc_Int)"), 4L, "wh");
                po.addFld("cpuCore", $$T_Str, "Tesla", "wh");
                po.addFld("isa", $$T_Str, "64T", "wh");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c6000.nda")), Global.newArray(new Object[]{Global.newArray(new Object[]{"L2SRAM", Global.newObject("comment", "Shared 256KB SRAM", "name", "L2SRAM", "base", 0x10900000L, "len", 0x00040000L, "space", "code/data", "access", "RWX")})}), "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c6000.nda"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c6000.nda"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c6000.nda.Tesla$$Params", "ti.catalog.c6000.nda");
        po.init("ti.catalog.c6000.nda.Tesla.Params", om.findStrict("ti.catalog.ICpuDataSheet$$Params", "ti.catalog.c6000.nda"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("minProgUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
                po.addFld("minDataUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
                po.addFld("dataWordSize", Proto.Elm.newCNum("(xdc_Int)"), 4L, "wh");
                po.addFld("cpuCore", $$T_Str, "Tesla", "wh");
                po.addFld("isa", $$T_Str, "64T", "wh");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c6000.nda")), Global.newArray(new Object[]{Global.newArray(new Object[]{"L2SRAM", Global.newObject("comment", "Shared 256KB SRAM", "name", "L2SRAM", "base", 0x10900000L, "len", 0x00040000L, "space", "code/data", "access", "RWX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c6000.nda.Tesla$$Object", "ti.catalog.c6000.nda");
        po.init("ti.catalog.c6000.nda.Tesla.Object", om.findStrict("ti.catalog.c6000.nda.Tesla.Instance", "ti.catalog.c6000.nda"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c6000.nda"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c6000.nda"), fxn);
    }

    void Tesla$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.catalog.c6000.nda.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.catalog.c6000.nda"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c6000/nda/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.catalog.c6000.nda"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.catalog.c6000.nda"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.catalog.c6000.nda"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.catalog.c6000.nda"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.catalog.c6000.nda"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.catalog.c6000.nda"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.catalog.c6000.nda", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.catalog.c6000.nda");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.catalog.c6000.nda.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.platform", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.catalog.c6000.nda'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Tesla$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c6000.nda.Tesla", "ti.catalog.c6000.nda");
        po = (Proto.Obj)om.findStrict("ti.catalog.c6000.nda.Tesla.Module", "ti.catalog.c6000.nda");
        vo.init2(po, "ti.catalog.c6000.nda.Tesla", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c6000.nda.Tesla$$capsule", "ti.catalog.c6000.nda"));
        vo.bind("Instance", om.findStrict("ti.catalog.c6000.nda.Tesla.Instance", "ti.catalog.c6000.nda"));
        vo.bind("Params", om.findStrict("ti.catalog.c6000.nda.Tesla.Params", "ti.catalog.c6000.nda"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c6000.nda.Tesla.Params", "ti.catalog.c6000.nda")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c6000.nda", "ti.catalog.c6000.nda"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c6000.nda")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c6000.nda.Tesla$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c6000.nda.Tesla.Object", "ti.catalog.c6000.nda"));
        pkgV.bind("Tesla", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Tesla");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c6000.nda.Tesla", "ti.catalog.c6000.nda"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.catalog.c6000.nda.Tesla")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.catalog.c6000.nda")).add(pkgV);
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
        Tesla$$OBJECTS();
        Tesla$$CONSTS();
        Tesla$$CREATES();
        Tesla$$FUNCTIONS();
        Tesla$$SIZES();
        Tesla$$TYPES();
        if (isROV) {
            Tesla$$ROV();
        }//isROV
        $$SINGLETONS();
        Tesla$$SINGLETONS();
        $$INITIALIZATION();
    }
}
