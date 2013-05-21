import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.*;

public class ti_sdo_codecs_mpeg4enc
{
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.codecs.mpeg4enc.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.codecs.mpeg4enc", new Value.Obj("ti.sdo.codecs.mpeg4enc", pkgP));
    }

    void MPEG4ENC$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.codecs.mpeg4enc.MPEG4ENC.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.codecs.mpeg4enc.MPEG4ENC", new Value.Obj("ti.sdo.codecs.mpeg4enc.MPEG4ENC", po));
        pkgV.bind("MPEG4ENC", vo);
        // decls 
    }

    void MPEG4ENC$$CONSTS()
    {
        // module MPEG4ENC
    }

    void MPEG4ENC$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void MPEG4ENC$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void MPEG4ENC$$SIZES()
    {
    }

    void MPEG4ENC$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.find("ti.sdo.codecs.mpeg4enc.MPEG4ENC.Module");
        po.init("ti.sdo.codecs.mpeg4enc.MPEG4ENC.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("watermark", $$T_Bool, false, "wh");
                po.addFld("codeSection", $$T_Str, $$UNDEF, "wh");
                po.addFld("udataSection", $$T_Str, $$UNDEF, "wh");
                po.addFld("dataSection", $$T_Str, $$UNDEF, "wh");
    }

    void MPEG4ENC$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.codecs.mpeg4enc.Package", (Proto.Obj)om.find("xdc.IPackage.Module"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/codecs/mpeg4enc/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.find("xdc.IPackage$$init"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.find("xdc.IPackage$$close"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.find("xdc.IPackage$$validate"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.find("xdc.IPackage$$exit"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.find("xdc.IPackage$$getLibs"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.find("xdc.IPackage$$getSects"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.codecs.mpeg4enc", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.codecs.mpeg4enc");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.codecs.mpeg4enc.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.codecs.mpeg4enc'];\n");
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

    void MPEG4ENC$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.find("ti.sdo.codecs.mpeg4enc.MPEG4ENC");
        po = (Proto.Obj)om.find("ti.sdo.codecs.mpeg4enc.MPEG4ENC.Module");
        vo.init2(po, "ti.sdo.codecs.mpeg4enc.MPEG4ENC", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.find("ti.sdo.codecs.mpeg4enc"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.find("$modules")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.codecs.mpeg4enc.MPEG4ENC$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("MPEG4ENC", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("MPEG4ENC");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.find("ti.sdo.codecs.mpeg4enc.MPEG4ENC"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.codecs.mpeg4enc.MPEG4ENC")).bless();
        ((Value.Arr)om.find("$packages")).add(pkgV);
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
        MPEG4ENC$$OBJECTS();
        MPEG4ENC$$CONSTS();
        MPEG4ENC$$CREATES();
        MPEG4ENC$$FUNCTIONS();
        MPEG4ENC$$SIZES();
        MPEG4ENC$$TYPES();
        if (isROV) {
            MPEG4ENC$$ROV();
        }//isROV
        $$SINGLETONS();
        MPEG4ENC$$SINGLETONS();
        $$INITIALIZATION();
    }
}
