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

public class ti_sdo_ce
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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.ipc");
        Global.callFxn("loadPackage", xdcO, "xdc.cfg");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce", new Value.Obj("ti.sdo.ce", pkgP));
    }

    void Engine$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.Engine.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.Engine", new Value.Obj("ti.sdo.ce.Engine", po));
        pkgV.bind("Engine", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ce.Engine$$AlgDesc", new Proto.Obj());
        om.bind("ti.sdo.ce.Engine.AlgDesc", new Proto.Str(spo, true));
        // insts 
        Object insP = om.bind("ti.sdo.ce.Engine.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ce.Engine$$Object", new Proto.Obj());
        Object objP = om.bind("ti.sdo.ce.Engine.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.sdo.ce.Engine$$Params", new Proto.Obj());
        om.bind("ti.sdo.ce.Engine.Params", new Proto.Str(po, true));
    }

    void Server$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.Server.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.Server", new Value.Obj("ti.sdo.ce.Server", po));
        pkgV.bind("Server", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ce.Server$$ThreadAttrs", new Proto.Obj());
        om.bind("ti.sdo.ce.Server.ThreadAttrs", new Proto.Str(spo, true));
        spo = (Proto.Obj)om.bind("ti.sdo.ce.Server$$AlgDesc", new Proto.Obj());
        om.bind("ti.sdo.ce.Server.AlgDesc", new Proto.Str(spo, true));
        om.bind("ti.sdo.ce.Server.SkelCachingPolicy", new Proto.Enm("ti.sdo.ce.Server.SkelCachingPolicy"));
    }

    void VISA$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.VISA.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.VISA", new Value.Obj("ti.sdo.ce.VISA", po));
        pkgV.bind("VISA", vo);
        // decls 
    }

    void CERuntime$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.CERuntime.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.CERuntime", new Value.Obj("ti.sdo.ce.CERuntime", po));
        pkgV.bind("CERuntime", vo);
        // decls 
    }

    void Settings$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.Settings.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.Settings", new Value.Obj("ti.sdo.ce.Settings", po));
        pkgV.bind("Settings", vo);
        // decls 
    }

    void ICodec$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.ICodec.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.ICodec", new Value.Obj("ti.sdo.ce.ICodec", po));
        pkgV.bind("ICodec", vo);
        // decls 
    }

    void Engine$$CONSTS()
    {
        // module Engine
        om.bind("ti.sdo.ce.Engine.MAXGROUPID", 20L);
    }

    void Server$$CONSTS()
    {
        // module Server
        om.bind("ti.sdo.ce.Server.LOCALBUFFERINVWB", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.Server.SkelCachingPolicy", "ti.sdo.ce"), "ti.sdo.ce.Server.LOCALBUFFERINVWB", xdc.services.intern.xsr.Enum.intValue(0L)+0));
        om.bind("ti.sdo.ce.Server.WBINVALL", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.Server.SkelCachingPolicy", "ti.sdo.ce"), "ti.sdo.ce.Server.WBINVALL", xdc.services.intern.xsr.Enum.intValue(1L)+0));
        om.bind("ti.sdo.ce.Server.NONE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.Server.SkelCachingPolicy", "ti.sdo.ce"), "ti.sdo.ce.Server.NONE", xdc.services.intern.xsr.Enum.intValue(2L)+0));
    }

    void VISA$$CONSTS()
    {
        // module VISA
    }

    void CERuntime$$CONSTS()
    {
        // module CERuntime
    }

    void Settings$$CONSTS()
    {
        // module Settings
    }

    void ICodec$$CONSTS()
    {
        // interface ICodec
    }

    void Engine$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.Engine$$create", new Proto.Fxn(om.findStrict("ti.sdo.ce.Engine.Module", "ti.sdo.ce"), om.findStrict("ti.sdo.ce.Engine.Instance", "ti.sdo.ce"), 3, 2, false));
                fxn.addArg(0, "name", $$T_Str, $$UNDEF);
                fxn.addArg(1, "algs", new Proto.Arr((Proto)om.findStrict("ti.sdo.ce.Engine.AlgDesc", "ti.sdo.ce"), false), $$DEFAULT);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sdo.ce.Engine.Params", "ti.sdo.ce"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$sdo$ce$Engine$$create = function( name, algs, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.sdo.ce.Engine'];\n");
            sb.append("var __inst = xdc.om['ti.sdo.ce.Engine.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ce']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {name:name, algs:algs});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.name = __mod.PARAMS.name;\n");
            sb.append("__inst.algs = __mod.PARAMS.algs;\n");
            sb.append("__inst.server = __mod.PARAMS.server;\n");
            sb.append("__inst.armDspLinkConfig = __mod.PARAMS.armDspLinkConfig;\n");
            sb.append("__inst.linkCfg = __mod.PARAMS.linkCfg;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [name, algs]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.Engine$$construct", new Proto.Fxn(om.findStrict("ti.sdo.ce.Engine.Module", "ti.sdo.ce"), null, 4, 2, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sdo.ce.Engine$$Object", "ti.sdo.ce"), null);
                fxn.addArg(1, "name", $$T_Str, $$UNDEF);
                fxn.addArg(2, "algs", new Proto.Arr((Proto)om.findStrict("ti.sdo.ce.Engine.AlgDesc", "ti.sdo.ce"), false), $$DEFAULT);
                fxn.addArg(3, "__params", (Proto)om.findStrict("ti.sdo.ce.Engine.Params", "ti.sdo.ce"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$sdo$ce$Engine$$construct = function( __obj, name, algs, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.sdo.ce.Engine'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {name:name, algs:algs});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.name = __mod.PARAMS.name;\n");
            sb.append("__inst.algs = __mod.PARAMS.algs;\n");
            sb.append("__inst.server = __mod.PARAMS.server;\n");
            sb.append("__inst.armDspLinkConfig = __mod.PARAMS.armDspLinkConfig;\n");
            sb.append("__inst.linkCfg = __mod.PARAMS.linkCfg;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Server$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VISA$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void CERuntime$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Settings$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ICodec$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Engine$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Engine.createFromServer
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.Engine$$createFromServer", new Proto.Fxn(om.findStrict("ti.sdo.ce.Engine.Module", "ti.sdo.ce"), null, 0, -1, false));
        // fxn Engine.getDspMemTableFromServer
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.Engine$$getDspMemTableFromServer", new Proto.Fxn(om.findStrict("ti.sdo.ce.Engine.Module", "ti.sdo.ce"), null, 0, -1, false));
        // fxn Engine.close
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.Engine$$close", new Proto.Fxn(om.findStrict("ti.sdo.ce.Engine.Module", "ti.sdo.ce"), null, 0, -1, false));
        // fxn Engine.validate
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.Engine$$validate", new Proto.Fxn(om.findStrict("ti.sdo.ce.Engine.Module", "ti.sdo.ce"), null, 0, -1, false));
        // fxn Engine.usesIDMA3
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.Engine$$usesIDMA3", new Proto.Fxn(om.findStrict("ti.sdo.ce.Engine.Module", "ti.sdo.ce"), $$T_Bool, 0, 0, false));
        // fxn Engine.usesIRES
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.Engine$$usesIRES", new Proto.Fxn(om.findStrict("ti.sdo.ce.Engine.Module", "ti.sdo.ce"), $$T_Bool, 0, 0, false));
        // fxn Engine.hasServer
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.Engine$$hasServer", new Proto.Fxn(om.findStrict("ti.sdo.ce.Engine.Module", "ti.sdo.ce"), $$T_Bool, 0, 0, false));
    }

    void Server$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Server.close
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.Server$$close", new Proto.Fxn(om.findStrict("ti.sdo.ce.Server.Module", "ti.sdo.ce"), null, 0, -1, false));
        // fxn Server.validate
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.Server$$validate", new Proto.Fxn(om.findStrict("ti.sdo.ce.Server.Module", "ti.sdo.ce"), null, 0, -1, false));
    }

    void VISA$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void CERuntime$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn CERuntime.addInitCode
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.CERuntime$$addInitCode", new Proto.Fxn(om.findStrict("ti.sdo.ce.CERuntime.Module", "ti.sdo.ce"), null, 2, 2, false));
                fxn.addArg(0, "initCodeLines", $$T_Str, $$UNDEF);
                fxn.addArg(1, "addEarly", $$T_Bool, $$UNDEF);
    }

    void Settings$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void ICodec$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn ICodec.getCreationStackSize
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.ICodec$$getCreationStackSize", new Proto.Fxn(om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce"), Proto.Elm.newCNum("(xdc_Int)"), 1, 1, false));
                fxn.addArg(0, "prog", (Proto)om.findStrict("xdc.cfg.Program.Module", "ti.sdo.ce"), $$UNDEF);
        // fxn ICodec.getDaramScratchSize
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.ICodec$$getDaramScratchSize", new Proto.Fxn(om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce"), Proto.Elm.newCNum("(xdc_Int)"), 1, 1, false));
                fxn.addArg(0, "prog", (Proto)om.findStrict("xdc.cfg.Program.Module", "ti.sdo.ce"), $$UNDEF);
        // fxn ICodec.getSaramScratchSize
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.ICodec$$getSaramScratchSize", new Proto.Fxn(om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce"), Proto.Elm.newCNum("(xdc_Int)"), 1, 1, false));
                fxn.addArg(0, "prog", (Proto)om.findStrict("xdc.cfg.Program.Module", "ti.sdo.ce"), $$UNDEF);
        // fxn ICodec.getStackSize
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.ICodec$$getStackSize", new Proto.Fxn(om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce"), Proto.Elm.newCNum("(xdc_Int)"), 1, 1, false));
                fxn.addArg(0, "prog", (Proto)om.findStrict("xdc.cfg.Program.Module", "ti.sdo.ce"), $$UNDEF);
        // fxn ICodec.getUUID
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.ICodec$$getUUID", new Proto.Fxn(om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce"), Proto.Elm.newCNum("(xdc_Int)"), 0, 0, false));
    }

    void Engine$$SIZES()
    {
    }

    void Server$$SIZES()
    {
    }

    void VISA$$SIZES()
    {
    }

    void CERuntime$$SIZES()
    {
    }

    void Settings$$SIZES()
    {
    }

    void ICodec$$SIZES()
    {
    }

    void Engine$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/Engine.xs");
        om.bind("ti.sdo.ce.Engine$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.Engine.Module", "ti.sdo.ce");
        po.init("ti.sdo.ce.Engine.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("MAXGROUPID", Proto.Elm.newCNum("(xdc_Int)"), 20L, "rh");
                po.addFld("local", (Proto)om.findStrict("ti.sdo.ce.Engine.Instance", "ti.sdo.ce"), $$UNDEF, "wh");
                po.addFld("noCommName", $$T_Bool, false, "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ce.Engine$$create", "ti.sdo.ce"), Global.get("ti$sdo$ce$Engine$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sdo.ce.Engine$$construct", "ti.sdo.ce"), Global.get("ti$sdo$ce$Engine$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.sdo.ce.Engine$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.sdo.ce.Engine$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.sdo.ce.Engine$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.sdo.ce.Engine$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("createFromServer", (Proto.Fxn)om.findStrict("ti.sdo.ce.Engine$$createFromServer", "ti.sdo.ce"), Global.get(cap, "createFromServer"));
                po.addFxn("getDspMemTableFromServer", (Proto.Fxn)om.findStrict("ti.sdo.ce.Engine$$getDspMemTableFromServer", "ti.sdo.ce"), Global.get(cap, "getDspMemTableFromServer"));
                po.addFxn("close", (Proto.Fxn)om.findStrict("ti.sdo.ce.Engine$$close", "ti.sdo.ce"), Global.get(cap, "close"));
                po.addFxn("validate", (Proto.Fxn)om.findStrict("ti.sdo.ce.Engine$$validate", "ti.sdo.ce"), Global.get(cap, "validate"));
                po.addFxn("usesIDMA3", (Proto.Fxn)om.findStrict("ti.sdo.ce.Engine$$usesIDMA3", "ti.sdo.ce"), Global.get(cap, "usesIDMA3"));
                po.addFxn("usesIRES", (Proto.Fxn)om.findStrict("ti.sdo.ce.Engine$$usesIRES", "ti.sdo.ce"), Global.get(cap, "usesIRES"));
                po.addFxn("hasServer", (Proto.Fxn)om.findStrict("ti.sdo.ce.Engine$$hasServer", "ti.sdo.ce"), Global.get(cap, "hasServer"));
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.Engine.Instance", "ti.sdo.ce");
        po.init("ti.sdo.ce.Engine.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("MAXGROUPID", Proto.Elm.newCNum("(xdc_Int)"), 20L, "rh");
                po.addFld("name", $$T_Str, $$UNDEF, "wh");
                po.addFld("algs", new Proto.Arr((Proto)om.findStrict("ti.sdo.ce.Engine.AlgDesc", "ti.sdo.ce"), false), $$DEFAULT, "wh");
                po.addFld("server", $$T_Str, $$UNDEF, "wh");
                po.addFld("armDspLinkConfig", (Proto)om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce"), $$DEFAULT, "wh");
                po.addFld("linkCfg", $$T_Str, $$UNDEF, "wh");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.Engine$$Params", "ti.sdo.ce");
        po.init("ti.sdo.ce.Engine.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("MAXGROUPID", Proto.Elm.newCNum("(xdc_Int)"), 20L, "rh");
                po.addFld("name", $$T_Str, $$UNDEF, "wh");
                po.addFld("algs", new Proto.Arr((Proto)om.findStrict("ti.sdo.ce.Engine.AlgDesc", "ti.sdo.ce"), false), $$DEFAULT, "wh");
                po.addFld("server", $$T_Str, $$UNDEF, "wh");
                po.addFld("armDspLinkConfig", (Proto)om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce"), $$DEFAULT, "wh");
                po.addFld("linkCfg", $$T_Str, $$UNDEF, "wh");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.Engine$$Object", "ti.sdo.ce");
        po.init("ti.sdo.ce.Engine.Object", om.findStrict("ti.sdo.ce.Engine.Instance", "ti.sdo.ce"));
        // struct Engine.AlgDesc
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.Engine$$AlgDesc", "ti.sdo.ce");
        po.init("ti.sdo.ce.Engine.AlgDesc", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("mod", (Proto)om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce"), $$UNDEF, "w");
                po.addFld("local", $$T_Bool, $$UNDEF, "w");
                po.addFld("groupId", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
    }

    void Server$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/Server.xs");
        om.bind("ti.sdo.ce.Server$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.Server.Module", "ti.sdo.ce");
        po.init("ti.sdo.ce.Server.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("MINPRI", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("MAXPRI", Proto.Elm.newCNum("(xdc_Int)"), 15L, "rh");
                po.addFld("threadAttrs", (Proto)om.findStrict("ti.sdo.ce.Server.ThreadAttrs", "ti.sdo.ce"), $$DEFAULT, "wh");
                po.addFld("algs", new Proto.Arr((Proto)om.findStrict("ti.sdo.ce.Server.AlgDesc", "ti.sdo.ce"), false), $$DEFAULT, "wh");
                po.addFld("stackSizePad", Proto.Elm.newCNum("(xdc_Int)"), 8192L, "wh");
                po.addFld("traceBufferSize", Proto.Elm.newCNum("(xdc_Int)"), 0L, "wh");
                po.addFld("autoGenScratchSizeArrays", $$T_Bool, 0L, "wh");
                po.addFld("skelCachingPolicy", (Proto)om.findStrict("ti.sdo.ce.Server.SkelCachingPolicy", "ti.sdo.ce"), $$UNDEF, "wh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.sdo.ce.Server$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.sdo.ce.Server$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.sdo.ce.Server$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("close", (Proto.Fxn)om.findStrict("ti.sdo.ce.Server$$close", "ti.sdo.ce"), Global.get(cap, "close"));
                po.addFxn("validate", (Proto.Fxn)om.findStrict("ti.sdo.ce.Server$$validate", "ti.sdo.ce"), Global.get(cap, "validate"));
        // struct Server.ThreadAttrs
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.Server$$ThreadAttrs", "ti.sdo.ce");
        po.init("ti.sdo.ce.Server.ThreadAttrs", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("stackSize", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("stackMemId", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("priority", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
        // struct Server.AlgDesc
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.Server$$AlgDesc", "ti.sdo.ce");
        po.init("ti.sdo.ce.Server.AlgDesc", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("mod", (Proto)om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce"), $$UNDEF, "w");
                po.addFld("threadAttrs", (Proto)om.findStrict("ti.sdo.ce.Server.ThreadAttrs", "ti.sdo.ce"), $$DEFAULT, "w");
                po.addFld("groupId", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
    }

    void VISA$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.VISA.Module", "ti.sdo.ce");
        po.init("ti.sdo.ce.VISA.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("localOnly", $$T_Bool, $$UNDEF, "wh");
    }

    void CERuntime$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/CERuntime.xs");
        om.bind("ti.sdo.ce.CERuntime$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.CERuntime.Module", "ti.sdo.ce");
        po.init("ti.sdo.ce.CERuntime.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.sdo.ce.CERuntime$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.sdo.ce.CERuntime$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.sdo.ce.CERuntime$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("addInitCode", (Proto.Fxn)om.findStrict("ti.sdo.ce.CERuntime$$addInitCode", "ti.sdo.ce"), Global.get(cap, "addInitCode"));
    }

    void Settings$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.Settings.Module", "ti.sdo.ce");
        po.init("ti.sdo.ce.Settings.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("checked", $$T_Bool, false, "wh");
    }

    void ICodec$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/ICodec.xs");
        om.bind("ti.sdo.ce.ICodec$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce");
        po.init("ti.sdo.ce.ICodec.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("isLocal", $$T_Bool, true, "wh");
                po.addFld("ialgFxns", $$T_Str, $$UNDEF, "rh");
                po.addFld("idma3Fxns", $$T_Str, $$UNDEF, "rh");
                po.addFld("iresFxns", $$T_Str, $$UNDEF, "rh");
                po.addFld("serverFxns", $$T_Str, $$UNDEF, "wh");
                po.addFld("stubFxns", $$T_Str, $$UNDEF, "wh");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "rh");
                po.addFld("uuid", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "wh");
                po.addFld("frameRate", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "rh");
                po.addFld("codecClassConfigurable", $$T_Bool, $$UNDEF, "rh");
                po.addFld("useCache", $$T_Bool, $$UNDEF, "wh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.sdo.ce.ICodec$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.sdo.ce.ICodec$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.sdo.ce.ICodec$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "getCreationStackSize");
                if (fxn != null) po.addFxn("getCreationStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getCreationStackSize", "ti.sdo.ce"), fxn);
                fxn = Global.get(cap, "getDaramScratchSize");
                if (fxn != null) po.addFxn("getDaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getDaramScratchSize", "ti.sdo.ce"), fxn);
                fxn = Global.get(cap, "getSaramScratchSize");
                if (fxn != null) po.addFxn("getSaramScratchSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getSaramScratchSize", "ti.sdo.ce"), fxn);
                fxn = Global.get(cap, "getStackSize");
                if (fxn != null) po.addFxn("getStackSize", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getStackSize", "ti.sdo.ce"), fxn);
                fxn = Global.get(cap, "getUUID");
                if (fxn != null) po.addFxn("getUUID", (Proto.Fxn)om.findStrict("ti.sdo.ce.ICodec$$getUUID", "ti.sdo.ce"), fxn);
    }

    void Engine$$ROV()
    {
    }

    void Server$$ROV()
    {
    }

    void VISA$$ROV()
    {
    }

    void CERuntime$$ROV()
    {
    }

    void Settings$$ROV()
    {
    }

    void ICodec$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.");
        pkgV.bind("$vers", Global.newArray("1, 0, 6"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/release/ce.a674',\n");
            sb.append("'lib/debug/ce.a64P',\n");
            sb.append("'lib/release/ce.a64P',\n");
            sb.append("'lib/debug/ce.av4TCE',\n");
            sb.append("'lib/debug/ce.a470uC',\n");
            sb.append("'lib/release/ce.av4TCE',\n");
            sb.append("'lib/debug/ce.a86U',\n");
            sb.append("'lib/release/ce.a86U',\n");
            sb.append("'lib/debug/ce.av5T',\n");
            sb.append("'lib/release/ce.a470uC',\n");
            sb.append("'lib/release/ce.av5T',\n");
            sb.append("'lib/debug/ce.a674',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/release/ce.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/ce.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/ce.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/ce.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/ce.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/ce.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/ce.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/ce.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/ce.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/ce.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/ce.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/ce.a674', {target: 'ti.targets.C674'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/release/ce.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/ce.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/ce.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/ce.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/ce.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/ce.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/ce.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/ce.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/ce.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/ce.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/ce.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/ce.a674'].suffix = '674';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Engine$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.Engine", "ti.sdo.ce");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.Engine.Module", "ti.sdo.ce");
        vo.init2(po, "ti.sdo.ce.Engine", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.Engine$$capsule", "ti.sdo.ce"));
        vo.bind("Instance", om.findStrict("ti.sdo.ce.Engine.Instance", "ti.sdo.ce"));
        vo.bind("Params", om.findStrict("ti.sdo.ce.Engine.Params", "ti.sdo.ce"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ce.Engine.Params", "ti.sdo.ce")).newInstance());
        vo.bind("$package", om.findStrict("ti.sdo.ce", "ti.sdo.ce"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("AlgDesc", om.findStrict("ti.sdo.ce.Engine.AlgDesc", "ti.sdo.ce"));
        tdefs.add(om.findStrict("ti.sdo.ce.Engine.AlgDesc", "ti.sdo.ce"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.Engine$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Engine.xdt");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ce.Engine.Object", "ti.sdo.ce"));
        vo.bind("TEMPLATE$", "./Engine.xdt");
        pkgV.bind("Engine", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Engine");
    }

    void Server$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.Server", "ti.sdo.ce");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.Server.Module", "ti.sdo.ce");
        vo.init2(po, "ti.sdo.ce.Server", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.Server$$capsule", "ti.sdo.ce"));
        vo.bind("$package", om.findStrict("ti.sdo.ce", "ti.sdo.ce"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("ThreadAttrs", om.findStrict("ti.sdo.ce.Server.ThreadAttrs", "ti.sdo.ce"));
        tdefs.add(om.findStrict("ti.sdo.ce.Server.ThreadAttrs", "ti.sdo.ce"));
        vo.bind("AlgDesc", om.findStrict("ti.sdo.ce.Server.AlgDesc", "ti.sdo.ce"));
        tdefs.add(om.findStrict("ti.sdo.ce.Server.AlgDesc", "ti.sdo.ce"));
        vo.bind("SkelCachingPolicy", om.findStrict("ti.sdo.ce.Server.SkelCachingPolicy", "ti.sdo.ce"));
        vo.bind("LOCALBUFFERINVWB", om.findStrict("ti.sdo.ce.Server.LOCALBUFFERINVWB", "ti.sdo.ce"));
        vo.bind("WBINVALL", om.findStrict("ti.sdo.ce.Server.WBINVALL", "ti.sdo.ce"));
        vo.bind("NONE", om.findStrict("ti.sdo.ce.Server.NONE", "ti.sdo.ce"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.Server$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Server.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Server.xdt");
        pkgV.bind("Server", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Server");
    }

    void VISA$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.VISA", "ti.sdo.ce");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.VISA.Module", "ti.sdo.ce");
        vo.init2(po, "ti.sdo.ce.VISA", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce", "ti.sdo.ce"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.VISA$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("VISA", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VISA");
    }

    void CERuntime$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.CERuntime", "ti.sdo.ce");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.CERuntime.Module", "ti.sdo.ce");
        vo.init2(po, "ti.sdo.ce.CERuntime", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.CERuntime$$capsule", "ti.sdo.ce"));
        vo.bind("$package", om.findStrict("ti.sdo.ce", "ti.sdo.ce"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.CERuntime$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./CERuntime.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./CERuntime.xdt");
        pkgV.bind("CERuntime", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("CERuntime");
    }

    void Settings$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.Settings", "ti.sdo.ce");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.Settings.Module", "ti.sdo.ce");
        vo.init2(po, "ti.sdo.ce.Settings", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce", "ti.sdo.ce"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.Settings$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Settings.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Settings.xdt");
        pkgV.bind("Settings", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Settings");
    }

    void ICodec$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.ICodec", "ti.sdo.ce");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce");
        vo.init2(po, "ti.sdo.ce.ICodec", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.ICodec$$capsule", "ti.sdo.ce"));
        vo.bind("$package", om.findStrict("ti.sdo.ce", "ti.sdo.ce"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ICodec", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ICodec");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.Engine", "ti.sdo.ce"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.Server", "ti.sdo.ce"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.VISA", "ti.sdo.ce"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.CERuntime", "ti.sdo.ce"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.Settings", "ti.sdo.ce"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.Engine")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.Server")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.VISA")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.CERuntime")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.Settings")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.ICodec")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce")).add(pkgV);
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
        Engine$$OBJECTS();
        Server$$OBJECTS();
        VISA$$OBJECTS();
        CERuntime$$OBJECTS();
        Settings$$OBJECTS();
        ICodec$$OBJECTS();
        Engine$$CONSTS();
        Server$$CONSTS();
        VISA$$CONSTS();
        CERuntime$$CONSTS();
        Settings$$CONSTS();
        ICodec$$CONSTS();
        Engine$$CREATES();
        Server$$CREATES();
        VISA$$CREATES();
        CERuntime$$CREATES();
        Settings$$CREATES();
        ICodec$$CREATES();
        Engine$$FUNCTIONS();
        Server$$FUNCTIONS();
        VISA$$FUNCTIONS();
        CERuntime$$FUNCTIONS();
        Settings$$FUNCTIONS();
        ICodec$$FUNCTIONS();
        Engine$$SIZES();
        Server$$SIZES();
        VISA$$SIZES();
        CERuntime$$SIZES();
        Settings$$SIZES();
        ICodec$$SIZES();
        Engine$$TYPES();
        Server$$TYPES();
        VISA$$TYPES();
        CERuntime$$TYPES();
        Settings$$TYPES();
        ICodec$$TYPES();
        if (isROV) {
            Engine$$ROV();
            Server$$ROV();
            VISA$$ROV();
            CERuntime$$ROV();
            Settings$$ROV();
            ICodec$$ROV();
        }//isROV
        $$SINGLETONS();
        Engine$$SINGLETONS();
        Server$$SINGLETONS();
        VISA$$SINGLETONS();
        CERuntime$$SINGLETONS();
        Settings$$SINGLETONS();
        ICodec$$SINGLETONS();
        $$INITIALIZATION();
    }
}
