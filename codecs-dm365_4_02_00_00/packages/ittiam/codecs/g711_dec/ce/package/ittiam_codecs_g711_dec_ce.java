/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-t50
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.*;

public class ittiam_codecs_g711_dec_ce
{
    static final String VERS = "@(#) xdc-t50\n";

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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.speech1");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "ittiam.codecs.g711_dec");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ittiam.codecs.g711_dec.ce.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ittiam.codecs.g711_dec.ce", new Value.Obj("ittiam.codecs.g711_dec.ce", pkgP));
    }

    void G711_DEC$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ittiam.codecs.g711_dec.ce.G711_DEC.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ittiam.codecs.g711_dec.ce.G711_DEC", new Value.Obj("ittiam.codecs.g711_dec.ce.G711_DEC", po));
        pkgV.bind("G711_DEC", vo);
        // decls 
    }

    void G711_DEC$$CONSTS()
    {
        // module G711_DEC
    }

    void G711_DEC$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void G711_DEC$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void G711_DEC$$SIZES()
    {
    }

    void G711_DEC$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ittiam/codecs/g711_dec/ce/G711_DEC.xs");
        om.bind("ittiam.codecs.g711_dec.ce.G711_DEC$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ittiam.codecs.g711_dec.ce.G711_DEC.Module", "ittiam.codecs.g711_dec.ce");
        po.init("ittiam.codecs.g711_dec.ce.G711_DEC.Module", om.findStrict("ti.sdo.ce.speech1.ISPHDEC1.Module", "ittiam.codecs.g711_dec.ce"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("alg", (Proto)om.findStrict("ittiam.codecs.g711_dec.G711_DEC.Module", "ittiam.codecs.g711_dec.ce"), om.find("ittiam.codecs.g711_dec.G711_DEC"), "rh");
                po.addFld("ialgFxns", $$T_Str, "G711DECODER_ITTIAM_IG711DECODER", "rh");
                po.addFld("iresFxns", $$T_Str, "AUDCDC_ITTIAM_IRES", "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ittiam.codecs.g711_dec.ce.G711_DEC$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ittiam.codecs.g711_dec.ce.G711_DEC$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ittiam.codecs.g711_dec.ce.G711_DEC$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "getCreationStackSize");
                if (fxn != null) po.addFxn("getCreationStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getCreationStackSize", "ittiam.codecs.g711_dec.ce"), fxn);
                fxn = Global.get(cap, "getDaramScratchSize");
                if (fxn != null) po.addFxn("getDaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getDaramScratchSize", "ittiam.codecs.g711_dec.ce"), fxn);
                fxn = Global.get(cap, "getSaramScratchSize");
                if (fxn != null) po.addFxn("getSaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getSaramScratchSize", "ittiam.codecs.g711_dec.ce"), fxn);
                fxn = Global.get(cap, "getStackSize");
                if (fxn != null) po.addFxn("getStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getStackSize", "ittiam.codecs.g711_dec.ce"), fxn);
                fxn = Global.get(cap, "getUUID");
                if (fxn != null) po.addFxn("getUUID", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getUUID", "ittiam.codecs.g711_dec.ce"), fxn);
    }

    void G711_DEC$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ittiam.codecs.g711_dec.ce.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ittiam.codecs.g711_dec.ce"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ittiam/codecs/g711_dec/ce/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ittiam.codecs.g711_dec.ce"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ittiam.codecs.g711_dec.ce"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ittiam.codecs.g711_dec.ce"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ittiam.codecs.g711_dec.ce"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ittiam.codecs.g711_dec.ce"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ittiam.codecs.g711_dec.ce"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ittiam.codecs.g711_dec.ce", Value.DEFAULT, false);
        pkgV.bind("$name", "ittiam.codecs.g711_dec.ce");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ittiam.codecs.g711_dec.ce.");
        pkgV.bind("$vers", Global.newArray());
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.ce.speech1", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ittiam.codecs.g711_dec.ce'];\n");
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

    void G711_DEC$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ittiam.codecs.g711_dec.ce.G711_DEC", "ittiam.codecs.g711_dec.ce");
        po = (Proto.Obj)om.findStrict("ittiam.codecs.g711_dec.ce.G711_DEC.Module", "ittiam.codecs.g711_dec.ce");
        vo.init2(po, "ittiam.codecs.g711_dec.ce.G711_DEC", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ittiam.codecs.g711_dec.ce.G711_DEC$$capsule", "ittiam.codecs.g711_dec.ce"));
        vo.bind("$package", om.findStrict("ittiam.codecs.g711_dec.ce", "ittiam.codecs.g711_dec.ce"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ittiam.codecs.g711_dec.ce")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ittiam.codecs.g711_dec.ce.G711_DEC$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("G711_DEC", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("G711_DEC");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ittiam.codecs.g711_dec.ce.G711_DEC", "ittiam.codecs.g711_dec.ce"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ittiam.codecs.g711_dec.ce.G711_DEC")).bless();
        ((Value.Arr)om.findStrict("$packages", "ittiam.codecs.g711_dec.ce")).add(pkgV);
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
        G711_DEC$$OBJECTS();
        G711_DEC$$CONSTS();
        G711_DEC$$CREATES();
        G711_DEC$$FUNCTIONS();
        G711_DEC$$SIZES();
        G711_DEC$$TYPES();
        if (isROV) {
            G711_DEC$$ROV();
        }//isROV
        $$SINGLETONS();
        G711_DEC$$SINGLETONS();
        $$INITIALIZATION();
    }
}
