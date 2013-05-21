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

public class ti_sdo_ce_examples_codecs_g711
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
        Global.callFxn("loadPackage", xdcO, "ti.xdais.dm.examples.g711");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.speech1");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.examples.codecs.g711.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.examples.codecs.g711", new Value.Obj("ti.sdo.ce.examples.codecs.g711", pkgP));
    }

    void G711ENC$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.examples.codecs.g711.G711ENC.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.examples.codecs.g711.G711ENC", new Value.Obj("ti.sdo.ce.examples.codecs.g711.G711ENC", po));
        pkgV.bind("G711ENC", vo);
        // decls 
    }

    void G711DEC$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.examples.codecs.g711.G711DEC.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.examples.codecs.g711.G711DEC", new Value.Obj("ti.sdo.ce.examples.codecs.g711.G711DEC", po));
        pkgV.bind("G711DEC", vo);
        // decls 
    }

    void G711ENC$$CONSTS()
    {
        // module G711ENC
    }

    void G711DEC$$CONSTS()
    {
        // module G711DEC
    }

    void G711ENC$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void G711DEC$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void G711ENC$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void G711DEC$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void G711ENC$$SIZES()
    {
    }

    void G711DEC$$SIZES()
    {
    }

    void G711ENC$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/examples/codecs/g711/G711ENC.xs");
        om.bind("ti.sdo.ce.examples.codecs.g711.G711ENC$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.examples.codecs.g711.G711ENC.Module", "ti.sdo.ce.examples.codecs.g711");
        po.init("ti.sdo.ce.examples.codecs.g711.G711ENC.Module", om.findStrict("ti.sdo.ce.speech1.ISPHENC1.Module", "ti.sdo.ce.examples.codecs.g711"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("ialgFxns", $$T_Str, "G711ENC_SUN_IG711ENC", "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.sdo.ce.examples.codecs.g711.G711ENC$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.sdo.ce.examples.codecs.g711.G711ENC$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.sdo.ce.examples.codecs.g711.G711ENC$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "getCreationStackSize");
                if (fxn != null) po.addFxn("getCreationStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getCreationStackSize", "ti.sdo.ce.examples.codecs.g711"), fxn);
                fxn = Global.get(cap, "getDaramScratchSize");
                if (fxn != null) po.addFxn("getDaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getDaramScratchSize", "ti.sdo.ce.examples.codecs.g711"), fxn);
                fxn = Global.get(cap, "getSaramScratchSize");
                if (fxn != null) po.addFxn("getSaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getSaramScratchSize", "ti.sdo.ce.examples.codecs.g711"), fxn);
                fxn = Global.get(cap, "getStackSize");
                if (fxn != null) po.addFxn("getStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getStackSize", "ti.sdo.ce.examples.codecs.g711"), fxn);
                fxn = Global.get(cap, "getUUID");
                if (fxn != null) po.addFxn("getUUID", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getUUID", "ti.sdo.ce.examples.codecs.g711"), fxn);
    }

    void G711DEC$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/examples/codecs/g711/G711DEC.xs");
        om.bind("ti.sdo.ce.examples.codecs.g711.G711DEC$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.examples.codecs.g711.G711DEC.Module", "ti.sdo.ce.examples.codecs.g711");
        po.init("ti.sdo.ce.examples.codecs.g711.G711DEC.Module", om.findStrict("ti.sdo.ce.speech1.ISPHDEC1.Module", "ti.sdo.ce.examples.codecs.g711"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("ialgFxns", $$T_Str, "G711DEC_SUN_IG711DEC", "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.sdo.ce.examples.codecs.g711.G711DEC$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.sdo.ce.examples.codecs.g711.G711DEC$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.sdo.ce.examples.codecs.g711.G711DEC$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "getCreationStackSize");
                if (fxn != null) po.addFxn("getCreationStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getCreationStackSize", "ti.sdo.ce.examples.codecs.g711"), fxn);
                fxn = Global.get(cap, "getDaramScratchSize");
                if (fxn != null) po.addFxn("getDaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getDaramScratchSize", "ti.sdo.ce.examples.codecs.g711"), fxn);
                fxn = Global.get(cap, "getSaramScratchSize");
                if (fxn != null) po.addFxn("getSaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getSaramScratchSize", "ti.sdo.ce.examples.codecs.g711"), fxn);
                fxn = Global.get(cap, "getStackSize");
                if (fxn != null) po.addFxn("getStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getStackSize", "ti.sdo.ce.examples.codecs.g711"), fxn);
                fxn = Global.get(cap, "getUUID");
                if (fxn != null) po.addFxn("getUUID", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getUUID", "ti.sdo.ce.examples.codecs.g711"), fxn);
    }

    void G711ENC$$ROV()
    {
    }

    void G711DEC$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.examples.codecs.g711.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.examples.codecs.g711"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/examples/codecs/g711/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.examples.codecs.g711"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.examples.codecs.g711"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.examples.codecs.g711"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.examples.codecs.g711"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.examples.codecs.g711"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.examples.codecs.g711"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.examples.codecs.g711", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.examples.codecs.g711");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.examples.codecs.g711.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.xdais.dm.examples.g711", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.examples.codecs.g711'];\n");
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

    void G711ENC$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.examples.codecs.g711.G711ENC", "ti.sdo.ce.examples.codecs.g711");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.examples.codecs.g711.G711ENC.Module", "ti.sdo.ce.examples.codecs.g711");
        vo.init2(po, "ti.sdo.ce.examples.codecs.g711.G711ENC", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.examples.codecs.g711.G711ENC$$capsule", "ti.sdo.ce.examples.codecs.g711"));
        vo.bind("$package", om.findStrict("ti.sdo.ce.examples.codecs.g711", "ti.sdo.ce.examples.codecs.g711"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.examples.codecs.g711")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.examples.codecs.g711.G711ENC$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("G711ENC", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("G711ENC");
    }

    void G711DEC$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.examples.codecs.g711.G711DEC", "ti.sdo.ce.examples.codecs.g711");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.examples.codecs.g711.G711DEC.Module", "ti.sdo.ce.examples.codecs.g711");
        vo.init2(po, "ti.sdo.ce.examples.codecs.g711.G711DEC", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.examples.codecs.g711.G711DEC$$capsule", "ti.sdo.ce.examples.codecs.g711"));
        vo.bind("$package", om.findStrict("ti.sdo.ce.examples.codecs.g711", "ti.sdo.ce.examples.codecs.g711"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.examples.codecs.g711")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.examples.codecs.g711.G711DEC$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("G711DEC", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("G711DEC");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.examples.codecs.g711.G711ENC", "ti.sdo.ce.examples.codecs.g711"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.examples.codecs.g711.G711DEC", "ti.sdo.ce.examples.codecs.g711"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.examples.codecs.g711.G711ENC")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.examples.codecs.g711.G711DEC")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.examples.codecs.g711")).add(pkgV);
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
        G711ENC$$OBJECTS();
        G711DEC$$OBJECTS();
        G711ENC$$CONSTS();
        G711DEC$$CONSTS();
        G711ENC$$CREATES();
        G711DEC$$CREATES();
        G711ENC$$FUNCTIONS();
        G711DEC$$FUNCTIONS();
        G711ENC$$SIZES();
        G711DEC$$SIZES();
        G711ENC$$TYPES();
        G711DEC$$TYPES();
        if (isROV) {
            G711ENC$$ROV();
            G711DEC$$ROV();
        }//isROV
        $$SINGLETONS();
        G711ENC$$SINGLETONS();
        G711DEC$$SINGLETONS();
        $$INITIALIZATION();
    }
}
