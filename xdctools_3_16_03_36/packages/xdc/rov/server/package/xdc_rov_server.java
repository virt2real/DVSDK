/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-u17
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.*;

public class xdc_rov_server
{
    static final String VERS = "@(#) xdc-u17\n";

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
        Global.callFxn("loadPackage", xdcO, "xdc.tools");
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("xdc.rov.server.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("xdc.rov.server", new Value.Obj("xdc.rov.server", pkgP));
    }

    void Main$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.rov.server.Main.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.rov.server.Main", new Value.Obj("xdc.rov.server.Main", po));
        pkgV.bind("Main", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.rov.server.Main.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.rov.server.Main$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.rov.server.Main.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("xdc.rov.server.Main$$Params", new Proto.Obj());
        om.bind("xdc.rov.server.Main.Params", new Proto.Str(po, true));
    }

    void CoreDumpImage$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.rov.server.CoreDumpImage.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.rov.server.CoreDumpImage", new Value.Obj("xdc.rov.server.CoreDumpImage", po));
        pkgV.bind("CoreDumpImage", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.rov.server.CoreDumpImage.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.rov.server.CoreDumpImage$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.rov.server.CoreDumpImage.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("xdc.rov.server.CoreDumpImage$$Params", new Proto.Obj());
        om.bind("xdc.rov.server.CoreDumpImage.Params", new Proto.Str(po, true));
    }

    void SymbolsViaOfd$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.rov.server.SymbolsViaOfd.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.rov.server.SymbolsViaOfd", new Value.Obj("xdc.rov.server.SymbolsViaOfd", po));
        pkgV.bind("SymbolsViaOfd", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.rov.server.SymbolsViaOfd.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.rov.server.SymbolsViaOfd$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.rov.server.SymbolsViaOfd.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("xdc.rov.server.SymbolsViaOfd$$Params", new Proto.Obj());
        om.bind("xdc.rov.server.SymbolsViaOfd.Params", new Proto.Str(po, true));
    }

    void DSSymbolReader$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.rov.server.DSSymbolReader.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.rov.server.DSSymbolReader", new Value.Obj("xdc.rov.server.DSSymbolReader", po));
        pkgV.bind("DSSymbolReader", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.rov.server.DSSymbolReader.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.rov.server.DSSymbolReader$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.rov.server.DSSymbolReader.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("xdc.rov.server.DSSymbolReader$$Params", new Proto.Obj());
        om.bind("xdc.rov.server.DSSymbolReader.Params", new Proto.Str(po, true));
    }

    void DSCallBack$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.rov.server.DSCallBack.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.rov.server.DSCallBack", new Value.Obj("xdc.rov.server.DSCallBack", po));
        pkgV.bind("DSCallBack", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.rov.server.DSCallBack.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.rov.server.DSCallBack$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.rov.server.DSCallBack.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("xdc.rov.server.DSCallBack$$Params", new Proto.Obj());
        om.bind("xdc.rov.server.DSCallBack.Params", new Proto.Str(po, true));
    }

    void Main$$CONSTS()
    {
        // module Main
    }

    void CoreDumpImage$$CONSTS()
    {
        // module CoreDumpImage
    }

    void SymbolsViaOfd$$CONSTS()
    {
        // module SymbolsViaOfd
    }

    void DSSymbolReader$$CONSTS()
    {
        // module DSSymbolReader
    }

    void DSCallBack$$CONSTS()
    {
        // module DSCallBack
    }

    void Main$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("xdc.rov.server.Main$$create", new Proto.Fxn(om.findStrict("xdc.rov.server.Main.Module", "xdc.rov.server"), om.findStrict("xdc.rov.server.Main.Instance", "xdc.rov.server"), 1, 0, false));
                fxn.addArg(0, "__params", (Proto)om.findStrict("xdc.rov.server.Main.Params", "xdc.rov.server"), Global.newObject());
        sb = new StringBuilder();
        sb.append("xdc$rov$server$Main$$create = function( __params ) {\n");
            sb.append("var __mod = xdc.om['xdc.rov.server.Main'];\n");
            sb.append("var __inst = xdc.om['xdc.rov.server.Main.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['xdc.rov.server']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("xdc.rov.server.Main$$construct", new Proto.Fxn(om.findStrict("xdc.rov.server.Main.Module", "xdc.rov.server"), null, 2, 0, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("xdc.rov.server.Main$$Object", "xdc.rov.server"), null);
                fxn.addArg(1, "__params", (Proto)om.findStrict("xdc.rov.server.Main.Params", "xdc.rov.server"), Global.newObject());
        sb = new StringBuilder();
        sb.append("xdc$rov$server$Main$$construct = function( __obj, __params ) {\n");
            sb.append("var __mod = xdc.om['xdc.rov.server.Main'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void CoreDumpImage$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("xdc.rov.server.CoreDumpImage$$create", new Proto.Fxn(om.findStrict("xdc.rov.server.CoreDumpImage.Module", "xdc.rov.server"), om.findStrict("xdc.rov.server.CoreDumpImage.Instance", "xdc.rov.server"), 2, 1, false));
                fxn.addArg(0, "xmlFile", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("xdc.rov.server.CoreDumpImage.Params", "xdc.rov.server"), Global.newObject());
        sb = new StringBuilder();
        sb.append("xdc$rov$server$CoreDumpImage$$create = function( xmlFile, __params ) {\n");
            sb.append("var __mod = xdc.om['xdc.rov.server.CoreDumpImage'];\n");
            sb.append("var __inst = xdc.om['xdc.rov.server.CoreDumpImage.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['xdc.rov.server']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {xmlFile:xmlFile});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [xmlFile]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("xdc.rov.server.CoreDumpImage$$construct", new Proto.Fxn(om.findStrict("xdc.rov.server.CoreDumpImage.Module", "xdc.rov.server"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("xdc.rov.server.CoreDumpImage$$Object", "xdc.rov.server"), null);
                fxn.addArg(1, "xmlFile", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("xdc.rov.server.CoreDumpImage.Params", "xdc.rov.server"), Global.newObject());
        sb = new StringBuilder();
        sb.append("xdc$rov$server$CoreDumpImage$$construct = function( __obj, xmlFile, __params ) {\n");
            sb.append("var __mod = xdc.om['xdc.rov.server.CoreDumpImage'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {xmlFile:xmlFile});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void SymbolsViaOfd$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("xdc.rov.server.SymbolsViaOfd$$create", new Proto.Fxn(om.findStrict("xdc.rov.server.SymbolsViaOfd.Module", "xdc.rov.server"), om.findStrict("xdc.rov.server.SymbolsViaOfd.Instance", "xdc.rov.server"), 3, 2, false));
                fxn.addArg(0, "exeFile", $$T_Str, $$UNDEF);
                fxn.addArg(1, "ofdExe", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("xdc.rov.server.SymbolsViaOfd.Params", "xdc.rov.server"), Global.newObject());
        sb = new StringBuilder();
        sb.append("xdc$rov$server$SymbolsViaOfd$$create = function( exeFile, ofdExe, __params ) {\n");
            sb.append("var __mod = xdc.om['xdc.rov.server.SymbolsViaOfd'];\n");
            sb.append("var __inst = xdc.om['xdc.rov.server.SymbolsViaOfd.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['xdc.rov.server']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {exeFile:exeFile, ofdExe:ofdExe});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [exeFile, ofdExe]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("xdc.rov.server.SymbolsViaOfd$$construct", new Proto.Fxn(om.findStrict("xdc.rov.server.SymbolsViaOfd.Module", "xdc.rov.server"), null, 4, 2, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("xdc.rov.server.SymbolsViaOfd$$Object", "xdc.rov.server"), null);
                fxn.addArg(1, "exeFile", $$T_Str, $$UNDEF);
                fxn.addArg(2, "ofdExe", $$T_Str, $$UNDEF);
                fxn.addArg(3, "__params", (Proto)om.findStrict("xdc.rov.server.SymbolsViaOfd.Params", "xdc.rov.server"), Global.newObject());
        sb = new StringBuilder();
        sb.append("xdc$rov$server$SymbolsViaOfd$$construct = function( __obj, exeFile, ofdExe, __params ) {\n");
            sb.append("var __mod = xdc.om['xdc.rov.server.SymbolsViaOfd'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {exeFile:exeFile, ofdExe:ofdExe});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void DSSymbolReader$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("xdc.rov.server.DSSymbolReader$$create", new Proto.Fxn(om.findStrict("xdc.rov.server.DSSymbolReader.Module", "xdc.rov.server"), om.findStrict("xdc.rov.server.DSSymbolReader.Instance", "xdc.rov.server"), 2, 1, false));
                fxn.addArg(0, "index", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("xdc.rov.server.DSSymbolReader.Params", "xdc.rov.server"), Global.newObject());
        sb = new StringBuilder();
        sb.append("xdc$rov$server$DSSymbolReader$$create = function( index, __params ) {\n");
            sb.append("var __mod = xdc.om['xdc.rov.server.DSSymbolReader'];\n");
            sb.append("var __inst = xdc.om['xdc.rov.server.DSSymbolReader.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['xdc.rov.server']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {index:index});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [index]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("xdc.rov.server.DSSymbolReader$$construct", new Proto.Fxn(om.findStrict("xdc.rov.server.DSSymbolReader.Module", "xdc.rov.server"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("xdc.rov.server.DSSymbolReader$$Object", "xdc.rov.server"), null);
                fxn.addArg(1, "index", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("xdc.rov.server.DSSymbolReader.Params", "xdc.rov.server"), Global.newObject());
        sb = new StringBuilder();
        sb.append("xdc$rov$server$DSSymbolReader$$construct = function( __obj, index, __params ) {\n");
            sb.append("var __mod = xdc.om['xdc.rov.server.DSSymbolReader'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {index:index});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void DSCallBack$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("xdc.rov.server.DSCallBack$$create", new Proto.Fxn(om.findStrict("xdc.rov.server.DSCallBack.Module", "xdc.rov.server"), om.findStrict("xdc.rov.server.DSCallBack.Instance", "xdc.rov.server"), 2, 1, false));
                fxn.addArg(0, "index", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("xdc.rov.server.DSCallBack.Params", "xdc.rov.server"), Global.newObject());
        sb = new StringBuilder();
        sb.append("xdc$rov$server$DSCallBack$$create = function( index, __params ) {\n");
            sb.append("var __mod = xdc.om['xdc.rov.server.DSCallBack'];\n");
            sb.append("var __inst = xdc.om['xdc.rov.server.DSCallBack.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['xdc.rov.server']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {index:index});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [index]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("xdc.rov.server.DSCallBack$$construct", new Proto.Fxn(om.findStrict("xdc.rov.server.DSCallBack.Module", "xdc.rov.server"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("xdc.rov.server.DSCallBack$$Object", "xdc.rov.server"), null);
                fxn.addArg(1, "index", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("xdc.rov.server.DSCallBack.Params", "xdc.rov.server"), Global.newObject());
        sb = new StringBuilder();
        sb.append("xdc$rov$server$DSCallBack$$construct = function( __obj, index, __params ) {\n");
            sb.append("var __mod = xdc.om['xdc.rov.server.DSCallBack'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {index:index});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Main$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void CoreDumpImage$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void SymbolsViaOfd$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void DSSymbolReader$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void DSCallBack$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Main$$SIZES()
    {
    }

    void CoreDumpImage$$SIZES()
    {
    }

    void SymbolsViaOfd$$SIZES()
    {
    }

    void DSSymbolReader$$SIZES()
    {
    }

    void DSCallBack$$SIZES()
    {
    }

    void Main$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/rov/server/Main.xs");
        om.bind("xdc.rov.server.Main$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.Main.Module", "xdc.rov.server");
        po.init("xdc.rov.server.Main.Module", om.findStrict("xdc.tools.ICmd.Module", "xdc.rov.server"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("usage", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{" ", "Usage", "[-v version] [-e executable] [-i ROV Controller Index]", "[--help]", " "}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.rov.server.Main$$create", "xdc.rov.server"), Global.get("xdc$rov$server$Main$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("xdc.rov.server.Main$$construct", "xdc.rov.server"), Global.get("xdc$rov$server$Main$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.rov.server.Main$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.rov.server.Main$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("xdc.rov.server.Main$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.rov.server.Main$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "main");
                if (fxn != null) po.addFxn("main", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$main", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "exec");
                if (fxn != null) po.addFxn("exec", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$exec", "xdc.rov.server"), fxn);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.Main.Instance", "xdc.rov.server");
        po.init("xdc.rov.server.Main.Instance", om.findStrict("xdc.tools.ICmd.Instance", "xdc.rov.server"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverVers", Proto.Elm.newCNum("(xdc_Int)"), 4L, "wh");
                po.addFld("version", $$T_Str, "", "wh");
                po.addFld("executable", $$T_Str, "", "wh");
                po.addFld("controllerIndex", Proto.Elm.newCNum("(xdc_Int)"), Global.eval("-1"), "wh");
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$run", "xdc.rov.server"), fxn);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.Main$$Params", "xdc.rov.server");
        po.init("xdc.rov.server.Main.Params", om.findStrict("xdc.tools.ICmd$$Params", "xdc.rov.server"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverVers", Proto.Elm.newCNum("(xdc_Int)"), 4L, "wh");
                po.addFld("version", $$T_Str, "", "wh");
                po.addFld("executable", $$T_Str, "", "wh");
                po.addFld("controllerIndex", Proto.Elm.newCNum("(xdc_Int)"), Global.eval("-1"), "wh");
        po = (Proto.Obj)om.findStrict("xdc.rov.server.Main$$Object", "xdc.rov.server");
        po.init("xdc.rov.server.Main.Object", om.findStrict("xdc.rov.server.Main.Instance", "xdc.rov.server"));
                fxn = Global.get(cap, "run");
                if (fxn != null) po.addFxn("run", (Proto.Fxn)om.findStrict("xdc.tools.ICmd$$run", "xdc.rov.server"), fxn);
    }

    void CoreDumpImage$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/rov/server/CoreDumpImage.xs");
        om.bind("xdc.rov.server.CoreDumpImage$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.CoreDumpImage.Module", "xdc.rov.server");
        po.init("xdc.rov.server.CoreDumpImage.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.rov.server.CoreDumpImage$$create", "xdc.rov.server"), Global.get("xdc$rov$server$CoreDumpImage$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("xdc.rov.server.CoreDumpImage$$construct", "xdc.rov.server"), Global.get("xdc$rov$server$CoreDumpImage$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.rov.server.CoreDumpImage$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.rov.server.CoreDumpImage$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("xdc.rov.server.CoreDumpImage$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.rov.server.CoreDumpImage$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.CoreDumpImage.Instance", "xdc.rov.server");
        po.init("xdc.rov.server.CoreDumpImage.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po = (Proto.Obj)om.findStrict("xdc.rov.server.CoreDumpImage$$Params", "xdc.rov.server");
        po.init("xdc.rov.server.CoreDumpImage.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po = (Proto.Obj)om.findStrict("xdc.rov.server.CoreDumpImage$$Object", "xdc.rov.server");
        po.init("xdc.rov.server.CoreDumpImage.Object", om.findStrict("xdc.rov.server.CoreDumpImage.Instance", "xdc.rov.server"));
    }

    void SymbolsViaOfd$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/rov/server/SymbolsViaOfd.xs");
        om.bind("xdc.rov.server.SymbolsViaOfd$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.SymbolsViaOfd.Module", "xdc.rov.server");
        po.init("xdc.rov.server.SymbolsViaOfd.Module", om.findStrict("xdc.rov.ISymbolTable.Module", "xdc.rov.server"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.rov.server.SymbolsViaOfd$$create", "xdc.rov.server"), Global.get("xdc$rov$server$SymbolsViaOfd$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("xdc.rov.server.SymbolsViaOfd$$construct", "xdc.rov.server"), Global.get("xdc$rov$server$SymbolsViaOfd$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.rov.server.SymbolsViaOfd$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.rov.server.SymbolsViaOfd$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("xdc.rov.server.SymbolsViaOfd$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.rov.server.SymbolsViaOfd$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.SymbolsViaOfd.Instance", "xdc.rov.server");
        po.init("xdc.rov.server.SymbolsViaOfd.Instance", om.findStrict("xdc.rov.ISymbolTable.Instance", "xdc.rov.server"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                fxn = Global.get(cap, "getSymbolValue");
                if (fxn != null) po.addFxn("getSymbolValue", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$getSymbolValue", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "lookupDataSymbol");
                if (fxn != null) po.addFxn("lookupDataSymbol", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$lookupDataSymbol", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "lookupFuncName");
                if (fxn != null) po.addFxn("lookupFuncName", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$lookupFuncName", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "getISA");
                if (fxn != null) po.addFxn("getISA", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$getISA", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "getJavaImp");
                if (fxn != null) po.addFxn("getJavaImp", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$getJavaImp", "xdc.rov.server"), fxn);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.SymbolsViaOfd$$Params", "xdc.rov.server");
        po.init("xdc.rov.server.SymbolsViaOfd.Params", om.findStrict("xdc.rov.ISymbolTable$$Params", "xdc.rov.server"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po = (Proto.Obj)om.findStrict("xdc.rov.server.SymbolsViaOfd$$Object", "xdc.rov.server");
        po.init("xdc.rov.server.SymbolsViaOfd.Object", om.findStrict("xdc.rov.server.SymbolsViaOfd.Instance", "xdc.rov.server"));
                fxn = Global.get(cap, "getSymbolValue");
                if (fxn != null) po.addFxn("getSymbolValue", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$getSymbolValue", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "lookupDataSymbol");
                if (fxn != null) po.addFxn("lookupDataSymbol", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$lookupDataSymbol", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "lookupFuncName");
                if (fxn != null) po.addFxn("lookupFuncName", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$lookupFuncName", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "getISA");
                if (fxn != null) po.addFxn("getISA", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$getISA", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "getJavaImp");
                if (fxn != null) po.addFxn("getJavaImp", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$getJavaImp", "xdc.rov.server"), fxn);
    }

    void DSSymbolReader$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/rov/server/DSSymbolReader.xs");
        om.bind("xdc.rov.server.DSSymbolReader$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.DSSymbolReader.Module", "xdc.rov.server");
        po.init("xdc.rov.server.DSSymbolReader.Module", om.findStrict("xdc.rov.ISymbolTable.Module", "xdc.rov.server"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.rov.server.DSSymbolReader$$create", "xdc.rov.server"), Global.get("xdc$rov$server$DSSymbolReader$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("xdc.rov.server.DSSymbolReader$$construct", "xdc.rov.server"), Global.get("xdc$rov$server$DSSymbolReader$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.rov.server.DSSymbolReader$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.rov.server.DSSymbolReader$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("xdc.rov.server.DSSymbolReader$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.rov.server.DSSymbolReader$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.DSSymbolReader.Instance", "xdc.rov.server");
        po.init("xdc.rov.server.DSSymbolReader.Instance", om.findStrict("xdc.rov.ISymbolTable.Instance", "xdc.rov.server"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                fxn = Global.get(cap, "getSymbolValue");
                if (fxn != null) po.addFxn("getSymbolValue", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$getSymbolValue", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "lookupDataSymbol");
                if (fxn != null) po.addFxn("lookupDataSymbol", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$lookupDataSymbol", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "lookupFuncName");
                if (fxn != null) po.addFxn("lookupFuncName", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$lookupFuncName", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "getISA");
                if (fxn != null) po.addFxn("getISA", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$getISA", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "getJavaImp");
                if (fxn != null) po.addFxn("getJavaImp", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$getJavaImp", "xdc.rov.server"), fxn);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.DSSymbolReader$$Params", "xdc.rov.server");
        po.init("xdc.rov.server.DSSymbolReader.Params", om.findStrict("xdc.rov.ISymbolTable$$Params", "xdc.rov.server"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po = (Proto.Obj)om.findStrict("xdc.rov.server.DSSymbolReader$$Object", "xdc.rov.server");
        po.init("xdc.rov.server.DSSymbolReader.Object", om.findStrict("xdc.rov.server.DSSymbolReader.Instance", "xdc.rov.server"));
                fxn = Global.get(cap, "getSymbolValue");
                if (fxn != null) po.addFxn("getSymbolValue", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$getSymbolValue", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "lookupDataSymbol");
                if (fxn != null) po.addFxn("lookupDataSymbol", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$lookupDataSymbol", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "lookupFuncName");
                if (fxn != null) po.addFxn("lookupFuncName", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$lookupFuncName", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "getISA");
                if (fxn != null) po.addFxn("getISA", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$getISA", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "getJavaImp");
                if (fxn != null) po.addFxn("getJavaImp", (Proto.Fxn)om.findStrict("xdc.rov.ISymbolTable$$getJavaImp", "xdc.rov.server"), fxn);
    }

    void DSCallBack$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/rov/server/DSCallBack.xs");
        om.bind("xdc.rov.server.DSCallBack$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.DSCallBack.Module", "xdc.rov.server");
        po.init("xdc.rov.server.DSCallBack.Module", om.findStrict("xdc.rov.ICallBack.Module", "xdc.rov.server"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.rov.server.DSCallBack$$create", "xdc.rov.server"), Global.get("xdc$rov$server$DSCallBack$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("xdc.rov.server.DSCallBack$$construct", "xdc.rov.server"), Global.get("xdc$rov$server$DSCallBack$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.rov.server.DSCallBack$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.rov.server.DSCallBack$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("xdc.rov.server.DSCallBack$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.rov.server.DSCallBack$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.DSCallBack.Instance", "xdc.rov.server");
        po.init("xdc.rov.server.DSCallBack.Instance", om.findStrict("xdc.rov.ICallBack.Instance", "xdc.rov.server"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                fxn = Global.get(cap, "updateStartupProgress");
                if (fxn != null) po.addFxn("updateStartupProgress", (Proto.Fxn)om.findStrict("xdc.rov.ICallBack$$updateStartupProgress", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "getAbortFlag");
                if (fxn != null) po.addFxn("getAbortFlag", (Proto.Fxn)om.findStrict("xdc.rov.ICallBack$$getAbortFlag", "xdc.rov.server"), fxn);
        po = (Proto.Obj)om.findStrict("xdc.rov.server.DSCallBack$$Params", "xdc.rov.server");
        po.init("xdc.rov.server.DSCallBack.Params", om.findStrict("xdc.rov.ICallBack$$Params", "xdc.rov.server"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po = (Proto.Obj)om.findStrict("xdc.rov.server.DSCallBack$$Object", "xdc.rov.server");
        po.init("xdc.rov.server.DSCallBack.Object", om.findStrict("xdc.rov.server.DSCallBack.Instance", "xdc.rov.server"));
                fxn = Global.get(cap, "updateStartupProgress");
                if (fxn != null) po.addFxn("updateStartupProgress", (Proto.Fxn)om.findStrict("xdc.rov.ICallBack$$updateStartupProgress", "xdc.rov.server"), fxn);
                fxn = Global.get(cap, "getAbortFlag");
                if (fxn != null) po.addFxn("getAbortFlag", (Proto.Fxn)om.findStrict("xdc.rov.ICallBack$$getAbortFlag", "xdc.rov.server"), fxn);
    }

    void Main$$ROV()
    {
    }

    void CoreDumpImage$$ROV()
    {
    }

    void SymbolsViaOfd$$ROV()
    {
    }

    void DSSymbolReader$$ROV()
    {
    }

    void DSCallBack$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("xdc.rov.server.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "xdc.rov.server"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "xdc.rov.server", Value.DEFAULT, false);
        pkgV.bind("$name", "xdc.rov.server");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "xdc.rov.server.");
        pkgV.bind("$vers", Global.newArray("1, 1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.tools", Global.newArray()));
        imports.add(Global.newArray("xdc.rov", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['xdc.rov.server'];\n");
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

    void Main$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.rov.server.Main", "xdc.rov.server");
        po = (Proto.Obj)om.findStrict("xdc.rov.server.Main.Module", "xdc.rov.server");
        vo.init2(po, "xdc.rov.server.Main", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.rov.server.Main$$capsule", "xdc.rov.server"));
        vo.bind("Instance", om.findStrict("xdc.rov.server.Main.Instance", "xdc.rov.server"));
        vo.bind("Params", om.findStrict("xdc.rov.server.Main.Params", "xdc.rov.server"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.rov.server.Main.Params", "xdc.rov.server")).newInstance());
        vo.bind("$package", om.findStrict("xdc.rov.server", "xdc.rov.server"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.rov.server")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("xdc.rov.server.Main$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.rov.server.Main.Object", "xdc.rov.server"));
        pkgV.bind("Main", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Main");
    }

    void CoreDumpImage$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.rov.server.CoreDumpImage", "xdc.rov.server");
        po = (Proto.Obj)om.findStrict("xdc.rov.server.CoreDumpImage.Module", "xdc.rov.server");
        vo.init2(po, "xdc.rov.server.CoreDumpImage", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.rov.server.CoreDumpImage$$capsule", "xdc.rov.server"));
        vo.bind("Instance", om.findStrict("xdc.rov.server.CoreDumpImage.Instance", "xdc.rov.server"));
        vo.bind("Params", om.findStrict("xdc.rov.server.CoreDumpImage.Params", "xdc.rov.server"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.rov.server.CoreDumpImage.Params", "xdc.rov.server")).newInstance());
        vo.bind("$package", om.findStrict("xdc.rov.server", "xdc.rov.server"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.rov.server")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("xdc.rov.server.CoreDumpImage$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.rov.server.CoreDumpImage.Object", "xdc.rov.server"));
        pkgV.bind("CoreDumpImage", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("CoreDumpImage");
    }

    void SymbolsViaOfd$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.rov.server.SymbolsViaOfd", "xdc.rov.server");
        po = (Proto.Obj)om.findStrict("xdc.rov.server.SymbolsViaOfd.Module", "xdc.rov.server");
        vo.init2(po, "xdc.rov.server.SymbolsViaOfd", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.rov.server.SymbolsViaOfd$$capsule", "xdc.rov.server"));
        vo.bind("Instance", om.findStrict("xdc.rov.server.SymbolsViaOfd.Instance", "xdc.rov.server"));
        vo.bind("Params", om.findStrict("xdc.rov.server.SymbolsViaOfd.Params", "xdc.rov.server"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.rov.server.SymbolsViaOfd.Params", "xdc.rov.server")).newInstance());
        vo.bind("$package", om.findStrict("xdc.rov.server", "xdc.rov.server"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.rov.server")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("xdc.rov.server.SymbolsViaOfd$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.rov.server.SymbolsViaOfd.Object", "xdc.rov.server"));
        pkgV.bind("SymbolsViaOfd", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("SymbolsViaOfd");
    }

    void DSSymbolReader$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.rov.server.DSSymbolReader", "xdc.rov.server");
        po = (Proto.Obj)om.findStrict("xdc.rov.server.DSSymbolReader.Module", "xdc.rov.server");
        vo.init2(po, "xdc.rov.server.DSSymbolReader", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.rov.server.DSSymbolReader$$capsule", "xdc.rov.server"));
        vo.bind("Instance", om.findStrict("xdc.rov.server.DSSymbolReader.Instance", "xdc.rov.server"));
        vo.bind("Params", om.findStrict("xdc.rov.server.DSSymbolReader.Params", "xdc.rov.server"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.rov.server.DSSymbolReader.Params", "xdc.rov.server")).newInstance());
        vo.bind("$package", om.findStrict("xdc.rov.server", "xdc.rov.server"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.rov.server")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("xdc.rov.server.DSSymbolReader$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.rov.server.DSSymbolReader.Object", "xdc.rov.server"));
        pkgV.bind("DSSymbolReader", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("DSSymbolReader");
    }

    void DSCallBack$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.rov.server.DSCallBack", "xdc.rov.server");
        po = (Proto.Obj)om.findStrict("xdc.rov.server.DSCallBack.Module", "xdc.rov.server");
        vo.init2(po, "xdc.rov.server.DSCallBack", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.rov.server.DSCallBack$$capsule", "xdc.rov.server"));
        vo.bind("Instance", om.findStrict("xdc.rov.server.DSCallBack.Instance", "xdc.rov.server"));
        vo.bind("Params", om.findStrict("xdc.rov.server.DSCallBack.Params", "xdc.rov.server"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.rov.server.DSCallBack.Params", "xdc.rov.server")).newInstance());
        vo.bind("$package", om.findStrict("xdc.rov.server", "xdc.rov.server"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.rov.server")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("xdc.rov.server.DSCallBack$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.rov.server.DSCallBack.Object", "xdc.rov.server"));
        pkgV.bind("DSCallBack", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("DSCallBack");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.rov.server.Main", "xdc.rov.server"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.rov.server.CoreDumpImage", "xdc.rov.server"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.rov.server.SymbolsViaOfd", "xdc.rov.server"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.rov.server.DSSymbolReader", "xdc.rov.server"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.rov.server.DSCallBack", "xdc.rov.server"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("xdc.rov.server.Main")).bless();
        ((Value.Obj)om.getv("xdc.rov.server.CoreDumpImage")).bless();
        ((Value.Obj)om.getv("xdc.rov.server.SymbolsViaOfd")).bless();
        ((Value.Obj)om.getv("xdc.rov.server.DSSymbolReader")).bless();
        ((Value.Obj)om.getv("xdc.rov.server.DSCallBack")).bless();
        ((Value.Arr)om.findStrict("$packages", "xdc.rov.server")).add(pkgV);
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
        Main$$OBJECTS();
        CoreDumpImage$$OBJECTS();
        SymbolsViaOfd$$OBJECTS();
        DSSymbolReader$$OBJECTS();
        DSCallBack$$OBJECTS();
        Main$$CONSTS();
        CoreDumpImage$$CONSTS();
        SymbolsViaOfd$$CONSTS();
        DSSymbolReader$$CONSTS();
        DSCallBack$$CONSTS();
        Main$$CREATES();
        CoreDumpImage$$CREATES();
        SymbolsViaOfd$$CREATES();
        DSSymbolReader$$CREATES();
        DSCallBack$$CREATES();
        Main$$FUNCTIONS();
        CoreDumpImage$$FUNCTIONS();
        SymbolsViaOfd$$FUNCTIONS();
        DSSymbolReader$$FUNCTIONS();
        DSCallBack$$FUNCTIONS();
        Main$$SIZES();
        CoreDumpImage$$SIZES();
        SymbolsViaOfd$$SIZES();
        DSSymbolReader$$SIZES();
        DSCallBack$$SIZES();
        Main$$TYPES();
        CoreDumpImage$$TYPES();
        SymbolsViaOfd$$TYPES();
        DSSymbolReader$$TYPES();
        DSCallBack$$TYPES();
        if (isROV) {
            Main$$ROV();
            CoreDumpImage$$ROV();
            SymbolsViaOfd$$ROV();
            DSSymbolReader$$ROV();
            DSCallBack$$ROV();
        }//isROV
        $$SINGLETONS();
        Main$$SINGLETONS();
        CoreDumpImage$$SINGLETONS();
        SymbolsViaOfd$$SINGLETONS();
        DSSymbolReader$$SINGLETONS();
        DSCallBack$$SINGLETONS();
        $$INITIALIZATION();
    }
}
