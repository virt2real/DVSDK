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

public class ti_sdo_ce_examples_codecs_universal_copy
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
        Global.callFxn("loadPackage", xdcO, "ti.xdais.dm.examples.universal_copy");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.universal");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.examples.codecs.universal_copy.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.examples.codecs.universal_copy", new Value.Obj("ti.sdo.ce.examples.codecs.universal_copy", pkgP));
    }

    void UNIVERSAL_COPY$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY", new Value.Obj("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY", po));
        pkgV.bind("UNIVERSAL_COPY", vo);
        // decls 
    }

    void UNIVERSAL_COPY$$CONSTS()
    {
        // module UNIVERSAL_COPY
    }

    void UNIVERSAL_COPY$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void UNIVERSAL_COPY$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void UNIVERSAL_COPY$$SIZES()
    {
    }

    void UNIVERSAL_COPY$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/examples/codecs/universal_copy/UNIVERSAL_COPY.xs");
        om.bind("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY.Module", "ti.sdo.ce.examples.codecs.universal_copy");
        po.init("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY.Module", om.findStrict("ti.sdo.ce.universal.IUNIVERSAL.Module", "ti.sdo.ce.examples.codecs.universal_copy"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("ialgFxns", $$T_Str, "UNIVERSALCOPY_TI_IUNIVERSALCOPY", "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "getCreationStackSize");
                if (fxn != null) po.addFxn("getCreationStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getCreationStackSize", "ti.sdo.ce.examples.codecs.universal_copy"), fxn);
                fxn = Global.get(cap, "getDaramScratchSize");
                if (fxn != null) po.addFxn("getDaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getDaramScratchSize", "ti.sdo.ce.examples.codecs.universal_copy"), fxn);
                fxn = Global.get(cap, "getSaramScratchSize");
                if (fxn != null) po.addFxn("getSaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getSaramScratchSize", "ti.sdo.ce.examples.codecs.universal_copy"), fxn);
                fxn = Global.get(cap, "getStackSize");
                if (fxn != null) po.addFxn("getStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getStackSize", "ti.sdo.ce.examples.codecs.universal_copy"), fxn);
                fxn = Global.get(cap, "getUUID");
                if (fxn != null) po.addFxn("getUUID", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getUUID", "ti.sdo.ce.examples.codecs.universal_copy"), fxn);
    }

    void UNIVERSAL_COPY$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.examples.codecs.universal_copy.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.examples.codecs.universal_copy"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/examples/codecs/universal_copy/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.examples.codecs.universal_copy"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.examples.codecs.universal_copy"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.examples.codecs.universal_copy"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.examples.codecs.universal_copy"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.examples.codecs.universal_copy"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.examples.codecs.universal_copy"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.examples.codecs.universal_copy", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.examples.codecs.universal_copy");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.examples.codecs.universal_copy.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.xdais.dm.examples.universal_copy", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.examples.codecs.universal_copy'];\n");
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

    void UNIVERSAL_COPY$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY", "ti.sdo.ce.examples.codecs.universal_copy");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY.Module", "ti.sdo.ce.examples.codecs.universal_copy");
        vo.init2(po, "ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY$$capsule", "ti.sdo.ce.examples.codecs.universal_copy"));
        vo.bind("$package", om.findStrict("ti.sdo.ce.examples.codecs.universal_copy", "ti.sdo.ce.examples.codecs.universal_copy"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.examples.codecs.universal_copy")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("UNIVERSAL_COPY", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("UNIVERSAL_COPY");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY", "ti.sdo.ce.examples.codecs.universal_copy"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.examples.codecs.universal_copy")).add(pkgV);
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
        UNIVERSAL_COPY$$OBJECTS();
        UNIVERSAL_COPY$$CONSTS();
        UNIVERSAL_COPY$$CREATES();
        UNIVERSAL_COPY$$FUNCTIONS();
        UNIVERSAL_COPY$$SIZES();
        UNIVERSAL_COPY$$TYPES();
        if (isROV) {
            UNIVERSAL_COPY$$ROV();
        }//isROV
        $$SINGLETONS();
        UNIVERSAL_COPY$$SINGLETONS();
        $$INITIALIZATION();
    }
}
