/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-t56
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.*;

public class ti_sdo_codecs_mpeg4dec_ce
{
    static final String VERS = "@(#) xdc-t56\n";

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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.video2");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.codecs.mpeg4dec");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.codecs.mpeg4dec.ce.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.codecs.mpeg4dec.ce", new Value.Obj("ti.sdo.codecs.mpeg4dec.ce", pkgP));
    }

    void MPEG4DEC$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC", new Value.Obj("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC", po));
        pkgV.bind("MPEG4DEC", vo);
        // decls 
    }

    void MPEG4DEC$$CONSTS()
    {
        // module MPEG4DEC
    }

    void MPEG4DEC$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void MPEG4DEC$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void MPEG4DEC$$SIZES()
    {
    }

    void MPEG4DEC$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/codecs/mpeg4dec/ce/MPEG4DEC.xs");
        om.bind("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC.Module", "ti.sdo.codecs.mpeg4dec.ce");
        po.init("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC.Module", om.findStrict("ti.sdo.ce.video2.IVIDDEC2.Module", "ti.sdo.codecs.mpeg4dec.ce"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("alg", (Proto)om.findStrict("ti.sdo.codecs.mpeg4dec.MPEG4DEC.Module", "ti.sdo.codecs.mpeg4dec.ce"), om.find("ti.sdo.codecs.mpeg4dec.MPEG4DEC"), "rh");
                po.addFld("ialgFxns", $$T_Str, "MP4VDEC_TI_IMP4VDEC", "rh");
                po.addFld("iresFxns", $$T_Str, "MP4VDEC_TI_IRES", "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "getCreationStackSize");
                if (fxn != null) po.addFxn("getCreationStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getCreationStackSize", "ti.sdo.codecs.mpeg4dec.ce"), fxn);
                fxn = Global.get(cap, "getDaramScratchSize");
                if (fxn != null) po.addFxn("getDaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getDaramScratchSize", "ti.sdo.codecs.mpeg4dec.ce"), fxn);
                fxn = Global.get(cap, "getSaramScratchSize");
                if (fxn != null) po.addFxn("getSaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getSaramScratchSize", "ti.sdo.codecs.mpeg4dec.ce"), fxn);
                fxn = Global.get(cap, "getStackSize");
                if (fxn != null) po.addFxn("getStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getStackSize", "ti.sdo.codecs.mpeg4dec.ce"), fxn);
                fxn = Global.get(cap, "getUUID");
                if (fxn != null) po.addFxn("getUUID", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getUUID", "ti.sdo.codecs.mpeg4dec.ce"), fxn);
    }

    void MPEG4DEC$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.codecs.mpeg4dec.ce.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.codecs.mpeg4dec.ce"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "ti.sdo.codecs.mpeg4dec.ce", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.codecs.mpeg4dec.ce");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.codecs.mpeg4dec.ce.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.ce.video2", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.codecs.mpeg4dec", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.codecs.mpeg4dec.ce'];\n");
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

    void MPEG4DEC$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC", "ti.sdo.codecs.mpeg4dec.ce");
        po = (Proto.Obj)om.findStrict("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC.Module", "ti.sdo.codecs.mpeg4dec.ce");
        vo.init2(po, "ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC$$capsule", "ti.sdo.codecs.mpeg4dec.ce"));
        vo.bind("$package", om.findStrict("ti.sdo.codecs.mpeg4dec.ce", "ti.sdo.codecs.mpeg4dec.ce"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.codecs.mpeg4dec.ce")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("MPEG4DEC", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("MPEG4DEC");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC", "ti.sdo.codecs.mpeg4dec.ce"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.codecs.mpeg4dec.ce.MPEG4DEC")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.codecs.mpeg4dec.ce")).add(pkgV);
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
        MPEG4DEC$$OBJECTS();
        MPEG4DEC$$CONSTS();
        MPEG4DEC$$CREATES();
        MPEG4DEC$$FUNCTIONS();
        MPEG4DEC$$SIZES();
        MPEG4DEC$$TYPES();
        if (isROV) {
            MPEG4DEC$$ROV();
        }//isROV
        $$SINGLETONS();
        MPEG4DEC$$SINGLETONS();
        $$INITIALIZATION();
    }
}
