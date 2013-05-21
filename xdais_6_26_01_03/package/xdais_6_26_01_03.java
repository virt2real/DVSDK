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

public class xdais_6_26_01_03
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
        Global.callFxn("loadPackage", xdcO, "ti.sdoarch.standards.pkg");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("xdais_6_26_01_03.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("xdais_6_26_01_03", new Value.Obj("xdais_6_26_01_03", pkgP));
    }

    void Version$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdais_6_26_01_03.Version.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdais_6_26_01_03.Version", new Value.Obj("xdais_6_26_01_03.Version", po));
        pkgV.bind("Version", vo);
        // decls 
    }

    void Version$$CONSTS()
    {
        // module Version
        om.bind("xdais_6_26_01_03.Version.MAJOR", 6L);
        om.bind("xdais_6_26_01_03.Version.MINOR", 26L);
        om.bind("xdais_6_26_01_03.Version.PATCH", 01L);
        om.bind("xdais_6_26_01_03.Version.WIDTH", 2L);
    }

    void Version$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Version$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Version$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Version$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdais_6_26_01_03.Version.Module", "xdais_6_26_01_03");
        po.init("xdais_6_26_01_03.Version.Module", om.findStrict("ti.sdoarch.standards.pkg.IVersion.Module", "xdais_6_26_01_03"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("MAJOR", Proto.Elm.newCNum("(xdc_UInt16)"), 6L, "rh");
                po.addFld("MINOR", Proto.Elm.newCNum("(xdc_UInt16)"), 26L, "rh");
                po.addFld("PATCH", Proto.Elm.newCNum("(xdc_UInt16)"), 01L, "rh");
                po.addFld("WIDTH", Proto.Elm.newCNum("(xdc_UInt16)"), 2L, "rh");
        if (isCFG) {
        }//isCFG
                po.addFxn("getString", (Proto.Fxn)om.findStrict("ti.sdoarch.standards.pkg.IVersion$$getString", "xdais_6_26_01_03"), $$UNDEF);
    }

    void Version$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdais_6_26_01_03.Version", "xdais_6_26_01_03");
    }

    void $$SINGLETONS()
    {
        pkgP.init("xdais_6_26_01_03.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "xdais_6_26_01_03"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "xdais_6_26_01_03", Value.DEFAULT, false);
        pkgV.bind("$name", "xdais_6_26_01_03");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "xdais_6_26_01_03.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("*ti.xdais", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.viddec2_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.viddec1_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.videnc1_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.imgdec1_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.imgenc1_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.auddec_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.g711", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.sphdec1_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.sphenc1_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.auddec1_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.audenc1_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.vidtranscode_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.vidanalytics_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.viddec2split_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.examples.universal_copy", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.qualiti", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.wizards.genalg", Global.newArray()));
        imports.add(Global.newArray("*ti.xdais.dm.templates", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['xdais_6_26_01_03'];\n");
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

    void Version$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdais_6_26_01_03.Version", "xdais_6_26_01_03");
        po = (Proto.Obj)om.findStrict("xdais_6_26_01_03.Version.Module", "xdais_6_26_01_03");
        vo.init2(po, "xdais_6_26_01_03.Version", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdais_6_26_01_03", "xdais_6_26_01_03"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdais_6_26_01_03")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("$$fxntab", Global.newArray("xdais_6_26_01_03_Version_Handle__label__E", "xdais_6_26_01_03_Version_Module__startupDone__E", "xdais_6_26_01_03_Version_Object__create__E", "xdais_6_26_01_03_Version_Object__delete__E", "xdais_6_26_01_03_Version_Object__destruct__E", "xdais_6_26_01_03_Version_Object__get__E", "xdais_6_26_01_03_Version_Object__first__E", "xdais_6_26_01_03_Version_Object__next__E", "xdais_6_26_01_03_Version_Params__init__E", "xdais_6_26_01_03_Version_Proxy__abstract__E", "xdais_6_26_01_03_Version_Proxy__delegate__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Version", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Version");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdais_6_26_01_03.Version", "xdais_6_26_01_03"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("xdais_6_26_01_03.Version")).bless();
        ((Value.Arr)om.findStrict("$packages", "xdais_6_26_01_03")).add(pkgV);
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
        Version$$OBJECTS();
        Version$$CONSTS();
        Version$$CREATES();
        Version$$FUNCTIONS();
        Version$$SIZES();
        Version$$TYPES();
        if (isROV) {
            Version$$ROV();
        }//isROV
        $$SINGLETONS();
        Version$$SINGLETONS();
        $$INITIALIZATION();
    }
}
