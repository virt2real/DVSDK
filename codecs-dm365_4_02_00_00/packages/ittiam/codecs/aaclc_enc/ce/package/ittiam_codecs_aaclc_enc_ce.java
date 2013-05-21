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

public class ittiam_codecs_aaclc_enc_ce
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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.audio1");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "ittiam.codecs.aaclc_enc");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ittiam.codecs.aaclc_enc.ce.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ittiam.codecs.aaclc_enc.ce", new Value.Obj("ittiam.codecs.aaclc_enc.ce", pkgP));
    }

    void AACLC_ENC$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ittiam.codecs.aaclc_enc.ce.AACLC_ENC.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ittiam.codecs.aaclc_enc.ce.AACLC_ENC", new Value.Obj("ittiam.codecs.aaclc_enc.ce.AACLC_ENC", po));
        pkgV.bind("AACLC_ENC", vo);
        // decls 
    }

    void AACLC_ENC$$CONSTS()
    {
        // module AACLC_ENC
    }

    void AACLC_ENC$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void AACLC_ENC$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void AACLC_ENC$$SIZES()
    {
    }

    void AACLC_ENC$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ittiam/codecs/aaclc_enc/ce/AACLC_ENC.xs");
        om.bind("ittiam.codecs.aaclc_enc.ce.AACLC_ENC$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ittiam.codecs.aaclc_enc.ce.AACLC_ENC.Module", "ittiam.codecs.aaclc_enc.ce");
        po.init("ittiam.codecs.aaclc_enc.ce.AACLC_ENC.Module", om.findStrict("ti.sdo.ce.audio1.IAUDENC1.Module", "ittiam.codecs.aaclc_enc.ce"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("alg", (Proto)om.findStrict("ittiam.codecs.aaclc_enc.AACLC_ENC.Module", "ittiam.codecs.aaclc_enc.ce"), om.find("ittiam.codecs.aaclc_enc.AACLC_ENC"), "rh");
                po.addFld("ialgFxns", $$T_Str, "EAACPLUSENCODER_ITTIAM_IEAACPLUSENCODER", "rh");
                po.addFld("iresFxns", $$T_Str, "AUDCDC_ITTIAM_IRES", "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ittiam.codecs.aaclc_enc.ce.AACLC_ENC$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ittiam.codecs.aaclc_enc.ce.AACLC_ENC$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ittiam.codecs.aaclc_enc.ce.AACLC_ENC$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "getCreationStackSize");
                if (fxn != null) po.addFxn("getCreationStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getCreationStackSize", "ittiam.codecs.aaclc_enc.ce"), fxn);
                fxn = Global.get(cap, "getDaramScratchSize");
                if (fxn != null) po.addFxn("getDaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getDaramScratchSize", "ittiam.codecs.aaclc_enc.ce"), fxn);
                fxn = Global.get(cap, "getSaramScratchSize");
                if (fxn != null) po.addFxn("getSaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getSaramScratchSize", "ittiam.codecs.aaclc_enc.ce"), fxn);
                fxn = Global.get(cap, "getStackSize");
                if (fxn != null) po.addFxn("getStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getStackSize", "ittiam.codecs.aaclc_enc.ce"), fxn);
                fxn = Global.get(cap, "getUUID");
                if (fxn != null) po.addFxn("getUUID", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getUUID", "ittiam.codecs.aaclc_enc.ce"), fxn);
    }

    void AACLC_ENC$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ittiam.codecs.aaclc_enc.ce.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ittiam.codecs.aaclc_enc.ce"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ittiam/codecs/aaclc_enc/ce/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ittiam.codecs.aaclc_enc.ce"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ittiam.codecs.aaclc_enc.ce"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ittiam.codecs.aaclc_enc.ce"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ittiam.codecs.aaclc_enc.ce"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ittiam.codecs.aaclc_enc.ce"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ittiam.codecs.aaclc_enc.ce"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ittiam.codecs.aaclc_enc.ce", Value.DEFAULT, false);
        pkgV.bind("$name", "ittiam.codecs.aaclc_enc.ce");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ittiam.codecs.aaclc_enc.ce.");
        pkgV.bind("$vers", Global.newArray());
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.ce.audio1", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ittiam.codecs.aaclc_enc.ce'];\n");
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

    void AACLC_ENC$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ittiam.codecs.aaclc_enc.ce.AACLC_ENC", "ittiam.codecs.aaclc_enc.ce");
        po = (Proto.Obj)om.findStrict("ittiam.codecs.aaclc_enc.ce.AACLC_ENC.Module", "ittiam.codecs.aaclc_enc.ce");
        vo.init2(po, "ittiam.codecs.aaclc_enc.ce.AACLC_ENC", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ittiam.codecs.aaclc_enc.ce.AACLC_ENC$$capsule", "ittiam.codecs.aaclc_enc.ce"));
        vo.bind("$package", om.findStrict("ittiam.codecs.aaclc_enc.ce", "ittiam.codecs.aaclc_enc.ce"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ittiam.codecs.aaclc_enc.ce")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ittiam.codecs.aaclc_enc.ce.AACLC_ENC$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("AACLC_ENC", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("AACLC_ENC");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ittiam.codecs.aaclc_enc.ce.AACLC_ENC", "ittiam.codecs.aaclc_enc.ce"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ittiam.codecs.aaclc_enc.ce.AACLC_ENC")).bless();
        ((Value.Arr)om.findStrict("$packages", "ittiam.codecs.aaclc_enc.ce")).add(pkgV);
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
        AACLC_ENC$$OBJECTS();
        AACLC_ENC$$CONSTS();
        AACLC_ENC$$CREATES();
        AACLC_ENC$$FUNCTIONS();
        AACLC_ENC$$SIZES();
        AACLC_ENC$$TYPES();
        if (isROV) {
            AACLC_ENC$$ROV();
        }//isROV
        $$SINGLETONS();
        AACLC_ENC$$SINGLETONS();
        $$INITIALIZATION();
    }
}
