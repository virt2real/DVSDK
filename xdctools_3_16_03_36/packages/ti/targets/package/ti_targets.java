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

public class ti_targets
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
        Global.callFxn("loadPackage", xdcO, "xdc.bld");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.targets.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.targets", new Value.Obj("ti.targets", pkgP));
    }

    void ITarget$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.ITarget.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.ITarget", new Value.Obj("ti.targets.ITarget", po));
        pkgV.bind("ITarget", vo);
        // decls 
        om.bind("ti.targets.ITarget.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.ITarget.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.ITarget.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.ITarget.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.ITarget.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.ITarget.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.ITarget.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.ITarget.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.ITarget.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.ITarget.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.ITarget.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        spo = (Proto.Obj)om.bind("ti.targets.ITarget$$Command", new Proto.Obj());
        om.bind("ti.targets.ITarget.Command", new Proto.Str(spo, true));
        spo = (Proto.Obj)om.bind("ti.targets.ITarget$$Options", new Proto.Obj());
        om.bind("ti.targets.ITarget.Options", new Proto.Str(spo, true));
    }

    void C62$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C62.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C62", new Value.Obj("ti.targets.C62", po));
        pkgV.bind("C62", vo);
        // decls 
        om.bind("ti.targets.C62.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C62.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C62.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C62.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C62.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C62.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C62.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C62.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C62.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C62.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C62.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C62.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C62.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C62_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C62_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C62_big_endian", new Value.Obj("ti.targets.C62_big_endian", po));
        pkgV.bind("C62_big_endian", vo);
        // decls 
        om.bind("ti.targets.C62_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C62_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C62_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C62_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C62_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C62_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C62_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C62_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C62_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C62_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C62_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C62_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C62_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C64$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C64.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C64", new Value.Obj("ti.targets.C64", po));
        pkgV.bind("C64", vo);
        // decls 
        om.bind("ti.targets.C64.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C64.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C64.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C64.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C64.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C64.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C64.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C64.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C64.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C64.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C64.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C64.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C64.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C64_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C64_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C64_big_endian", new Value.Obj("ti.targets.C64_big_endian", po));
        pkgV.bind("C64_big_endian", vo);
        // decls 
        om.bind("ti.targets.C64_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C64_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C64_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C64_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C64_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C64_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C64_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C64_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C64_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C64_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C64_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C64_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C64_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C64P$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C64P.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C64P", new Value.Obj("ti.targets.C64P", po));
        pkgV.bind("C64P", vo);
        // decls 
        om.bind("ti.targets.C64P.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C64P.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C64P.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C64P.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C64P.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C64P.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C64P.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C64P.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C64P.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C64P.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C64P.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C64P.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C64P.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C64P_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C64P_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C64P_big_endian", new Value.Obj("ti.targets.C64P_big_endian", po));
        pkgV.bind("C64P_big_endian", vo);
        // decls 
        om.bind("ti.targets.C64P_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C64P_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C64P_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C64P_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C64P_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C64P_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C64P_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C64P_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C64P_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C64P_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C64P_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C64P_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C64P_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C674$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C674.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C674", new Value.Obj("ti.targets.C674", po));
        pkgV.bind("C674", vo);
        // decls 
        om.bind("ti.targets.C674.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C674.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C674.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C674.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C674.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C674.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C674.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C674.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C674.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C674.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C674.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C674.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C674.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C674_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C674_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C674_big_endian", new Value.Obj("ti.targets.C674_big_endian", po));
        pkgV.bind("C674_big_endian", vo);
        // decls 
        om.bind("ti.targets.C674_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C674_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C674_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C674_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C674_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C674_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C674_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C674_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C674_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C674_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C674_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C674_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C674_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C67$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C67.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C67", new Value.Obj("ti.targets.C67", po));
        pkgV.bind("C67", vo);
        // decls 
        om.bind("ti.targets.C67.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C67.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C67.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C67.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C67.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C67.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C67.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C67.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C67.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C67.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C67.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C67.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C67.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C67_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C67_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C67_big_endian", new Value.Obj("ti.targets.C67_big_endian", po));
        pkgV.bind("C67_big_endian", vo);
        // decls 
        om.bind("ti.targets.C67_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C67_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C67_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C67_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C67_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C67_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C67_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C67_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C67_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C67_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C67_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C67_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C67_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C67P$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C67P.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C67P", new Value.Obj("ti.targets.C67P", po));
        pkgV.bind("C67P", vo);
        // decls 
        om.bind("ti.targets.C67P.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C67P.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C67P.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C67P.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C67P.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C67P.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C67P.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C67P.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C67P.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C67P.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C67P.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C67P.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C67P.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C64T$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C64T.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C64T", new Value.Obj("ti.targets.C64T", po));
        pkgV.bind("C64T", vo);
        // decls 
        om.bind("ti.targets.C64T.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C64T.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C64T.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C64T.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C64T.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C64T.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C64T.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C64T.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C64T.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C64T.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C64T.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C64T.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C64T.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C64T_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C64T_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C64T_big_endian", new Value.Obj("ti.targets.C64T_big_endian", po));
        pkgV.bind("C64T_big_endian", vo);
        // decls 
        om.bind("ti.targets.C64T_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C64T_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C64T_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C64T_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C64T_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C64T_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C64T_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C64T_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C64T_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C64T_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C64T_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C64T_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C64T_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C54$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C54.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C54", new Value.Obj("ti.targets.C54", po));
        pkgV.bind("C54", vo);
        // decls 
        om.bind("ti.targets.C54.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C54.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C54.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C54.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C54.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C54.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C54.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C54.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C54.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C54.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C54.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C54.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C54.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C54_far$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C54_far.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C54_far", new Value.Obj("ti.targets.C54_far", po));
        pkgV.bind("C54_far", vo);
        // decls 
        om.bind("ti.targets.C54_far.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C54_far.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C54_far.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C54_far.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C54_far.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C54_far.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C54_far.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C54_far.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C54_far.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C54_far.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C54_far.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C54_far.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C54_far.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C55$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C55.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C55", new Value.Obj("ti.targets.C55", po));
        pkgV.bind("C55", vo);
        // decls 
        om.bind("ti.targets.C55.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C55.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C55.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C55.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C55.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C55.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C55.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C55.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C55.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C55.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C55.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C55.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C55.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C55_large$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C55_large.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C55_large", new Value.Obj("ti.targets.C55_large", po));
        pkgV.bind("C55_large", vo);
        // decls 
        om.bind("ti.targets.C55_large.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C55_large.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C55_large.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C55_large.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C55_large.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C55_large.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C55_large.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C55_large.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C55_large.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C55_large.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C55_large.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C55_large.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C55_large.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C55_huge$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C55_huge.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C55_huge", new Value.Obj("ti.targets.C55_huge", po));
        pkgV.bind("C55_huge", vo);
        // decls 
        om.bind("ti.targets.C55_huge.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C55_huge.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C55_huge.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C55_huge.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C55_huge.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C55_huge.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C55_huge.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C55_huge.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C55_huge.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C55_huge.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C55_huge.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C55_huge.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C55_huge.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C55P_word$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C55P_word.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C55P_word", new Value.Obj("ti.targets.C55P_word", po));
        pkgV.bind("C55P_word", vo);
        // decls 
        om.bind("ti.targets.C55P_word.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C55P_word.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C55P_word.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C55P_word.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C55P_word.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C55P_word.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C55P_word.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C55P_word.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C55P_word.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C55P_word.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C55P_word.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C55P_word.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C55P_word.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C55P_byte$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C55P_byte.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C55P_byte", new Value.Obj("ti.targets.C55P_byte", po));
        pkgV.bind("C55P_byte", vo);
        // decls 
        om.bind("ti.targets.C55P_byte.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C55P_byte.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C55P_byte.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C55P_byte.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C55P_byte.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C55P_byte.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C55P_byte.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C55P_byte.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C55P_byte.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C55P_byte.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C55P_byte.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C55P_byte.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C55P_byte.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C28$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C28.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C28", new Value.Obj("ti.targets.C28", po));
        pkgV.bind("C28", vo);
        // decls 
        om.bind("ti.targets.C28.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C28.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C28.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C28.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C28.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C28.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C28.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C28.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C28.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C28.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C28.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C28.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C28.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C28_large$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C28_large.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C28_large", new Value.Obj("ti.targets.C28_large", po));
        pkgV.bind("C28_large", vo);
        // decls 
        om.bind("ti.targets.C28_large.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C28_large.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C28_large.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C28_large.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C28_large.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C28_large.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C28_large.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C28_large.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C28_large.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C28_large.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C28_large.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C28_large.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C28_large.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void C28_float$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.C28_float.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.C28_float", new Value.Obj("ti.targets.C28_float", po));
        pkgV.bind("C28_float", vo);
        // decls 
        om.bind("ti.targets.C28_float.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.C28_float.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.C28_float.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.C28_float.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.C28_float.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.C28_float.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.C28_float.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.C28_float.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.C28_float.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.C28_float.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.C28_float.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.C28_float.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.C28_float.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void TMS470$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.TMS470.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.TMS470", new Value.Obj("ti.targets.TMS470", po));
        pkgV.bind("TMS470", vo);
        // decls 
        om.bind("ti.targets.TMS470.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.TMS470.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.TMS470.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.TMS470.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.TMS470.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.TMS470.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.TMS470.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.TMS470.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.TMS470.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.TMS470.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.TMS470.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.TMS470.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.TMS470.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void TMS470_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.TMS470_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.TMS470_big_endian", new Value.Obj("ti.targets.TMS470_big_endian", po));
        pkgV.bind("TMS470_big_endian", vo);
        // decls 
        om.bind("ti.targets.TMS470_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.TMS470_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.TMS470_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.TMS470_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.TMS470_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.TMS470_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.TMS470_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.TMS470_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.TMS470_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.TMS470_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.TMS470_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.TMS470_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.TMS470_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void MSP430$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.MSP430.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.MSP430", new Value.Obj("ti.targets.MSP430", po));
        pkgV.bind("MSP430", vo);
        // decls 
        om.bind("ti.targets.MSP430.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.MSP430.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.MSP430.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.MSP430.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.MSP430.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.MSP430.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.MSP430.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.MSP430.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.MSP430.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.MSP430.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.MSP430.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.MSP430.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.MSP430.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void MSP430_large_code$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.MSP430_large_code.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.MSP430_large_code", new Value.Obj("ti.targets.MSP430_large_code", po));
        pkgV.bind("MSP430_large_code", vo);
        // decls 
        om.bind("ti.targets.MSP430_large_code.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.MSP430_large_code.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.MSP430_large_code.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.MSP430_large_code.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.MSP430_large_code.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.MSP430_large_code.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.MSP430_large_code.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.MSP430_large_code.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.MSP430_large_code.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.MSP430_large_code.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.MSP430_large_code.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.MSP430_large_code.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.MSP430_large_code.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void MSP430_large_data$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.MSP430_large_data.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.MSP430_large_data", new Value.Obj("ti.targets.MSP430_large_data", po));
        pkgV.bind("MSP430_large_data", vo);
        // decls 
        om.bind("ti.targets.MSP430_large_data.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        om.bind("ti.targets.MSP430_large_data.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        om.bind("ti.targets.MSP430_large_data.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        om.bind("ti.targets.MSP430_large_data.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        om.bind("ti.targets.MSP430_large_data.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        om.bind("ti.targets.MSP430_large_data.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        om.bind("ti.targets.MSP430_large_data.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        om.bind("ti.targets.MSP430_large_data.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        om.bind("ti.targets.MSP430_large_data.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        om.bind("ti.targets.MSP430_large_data.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        om.bind("ti.targets.MSP430_large_data.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        om.bind("ti.targets.MSP430_large_data.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        om.bind("ti.targets.MSP430_large_data.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
    }

    void ITarget$$CONSTS()
    {
        // interface ITarget
    }

    void C62$$CONSTS()
    {
        // module C62
    }

    void C62_big_endian$$CONSTS()
    {
        // module C62_big_endian
    }

    void C64$$CONSTS()
    {
        // module C64
    }

    void C64_big_endian$$CONSTS()
    {
        // module C64_big_endian
    }

    void C64P$$CONSTS()
    {
        // module C64P
    }

    void C64P_big_endian$$CONSTS()
    {
        // module C64P_big_endian
    }

    void C674$$CONSTS()
    {
        // module C674
    }

    void C674_big_endian$$CONSTS()
    {
        // module C674_big_endian
    }

    void C67$$CONSTS()
    {
        // module C67
    }

    void C67_big_endian$$CONSTS()
    {
        // module C67_big_endian
    }

    void C67P$$CONSTS()
    {
        // module C67P
    }

    void C64T$$CONSTS()
    {
        // module C64T
    }

    void C64T_big_endian$$CONSTS()
    {
        // module C64T_big_endian
    }

    void C54$$CONSTS()
    {
        // module C54
    }

    void C54_far$$CONSTS()
    {
        // module C54_far
    }

    void C55$$CONSTS()
    {
        // module C55
    }

    void C55_large$$CONSTS()
    {
        // module C55_large
    }

    void C55_huge$$CONSTS()
    {
        // module C55_huge
    }

    void C55P_word$$CONSTS()
    {
        // module C55P_word
    }

    void C55P_byte$$CONSTS()
    {
        // module C55P_byte
    }

    void C28$$CONSTS()
    {
        // module C28
    }

    void C28_large$$CONSTS()
    {
        // module C28_large
    }

    void C28_float$$CONSTS()
    {
        // module C28_float
    }

    void TMS470$$CONSTS()
    {
        // module TMS470
    }

    void TMS470_big_endian$$CONSTS()
    {
        // module TMS470_big_endian
    }

    void MSP430$$CONSTS()
    {
        // module MSP430
    }

    void MSP430_large_code$$CONSTS()
    {
        // module MSP430_large_code
    }

    void MSP430_large_data$$CONSTS()
    {
        // module MSP430_large_data
    }

    void ITarget$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C62$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C62_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C64$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C64_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C64P$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C64P_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C674$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C674_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C67$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C67_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C67P$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C64T$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C64T_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C54$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C54_far$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C55$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C55_large$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C55_huge$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C55P_word$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C55P_byte$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C28$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C28_large$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C28_float$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TMS470$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TMS470_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void MSP430$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void MSP430_large_code$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void MSP430_large_data$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ITarget$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn ITarget.asmName
        fxn = (Proto.Fxn)om.bind("ti.targets.ITarget$$asmName", new Proto.Fxn(om.findStrict("ti.targets.ITarget.Module", "ti.targets"), $$T_Str, 1, 1, false));
                fxn.addArg(0, "CName", $$T_Str, $$UNDEF);
    }

    void C62$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C62_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C64$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C64_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C64P$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C64P_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C674$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C674_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C67$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C67_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C67P$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C64T$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C64T_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C54$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C54_far$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C55$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C55_large$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C55_huge$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C55P_word$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C55P_byte$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C28$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C28_large$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C28_float$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS470$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS470_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void MSP430$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void MSP430_large_code$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void MSP430_large_data$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void ITarget$$SIZES()
    {
    }

    void C62$$SIZES()
    {
    }

    void C62_big_endian$$SIZES()
    {
    }

    void C64$$SIZES()
    {
    }

    void C64_big_endian$$SIZES()
    {
    }

    void C64P$$SIZES()
    {
    }

    void C64P_big_endian$$SIZES()
    {
    }

    void C674$$SIZES()
    {
    }

    void C674_big_endian$$SIZES()
    {
    }

    void C67$$SIZES()
    {
    }

    void C67_big_endian$$SIZES()
    {
    }

    void C67P$$SIZES()
    {
    }

    void C64T$$SIZES()
    {
    }

    void C64T_big_endian$$SIZES()
    {
    }

    void C54$$SIZES()
    {
    }

    void C54_far$$SIZES()
    {
    }

    void C55$$SIZES()
    {
    }

    void C55_large$$SIZES()
    {
    }

    void C55_huge$$SIZES()
    {
    }

    void C55P_word$$SIZES()
    {
    }

    void C55P_byte$$SIZES()
    {
    }

    void C28$$SIZES()
    {
    }

    void C28_large$$SIZES()
    {
    }

    void C28_float$$SIZES()
    {
    }

    void TMS470$$SIZES()
    {
    }

    void TMS470_big_endian$$SIZES()
    {
    }

    void MSP430$$SIZES()
    {
    }

    void MSP430_large_code$$SIZES()
    {
    }

    void MSP430_large_data$$SIZES()
    {
    }

    void ITarget$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/ITarget.xs");
        om.bind("ti.targets.ITarget$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.targets.ITarget.Module", "ti.targets");
        po.init("ti.targets.ITarget.Module", om.findStrict("xdc.bld.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("stdInclude", $$T_Str, "ti/targets/std.h", "rh");
                po.addFld("binDir", $$T_Str, "$(rootDir)/bin/", "wh");
                po.addFld("pathPrefix", $$T_Str, "", "wh");
                po.addFld("binaryParser", $$T_Str, "ti.targets.omf.cof.Coff", "wh");
                po.addFld("debugGen", (Proto)om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"), Global.newObject("execTemplate", "ti/targets/ccs_exec.xdt", "execPattern", "$(cfgDir)$(cfgName).pjt", "packageTemplate", "ti/targets/ccs_package.xdt", "packagePattern", "package/$(pkgName).pjt"), "wh");
                po.addFld("extensions", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.Extension", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{".asm", Global.newObject("suf", ".asm", "typ", "asm")}), Global.newArray(new Object[]{".c", Global.newObject("suf", ".c", "typ", "c")}), Global.newArray(new Object[]{".cpp", Global.newObject("suf", ".cpp", "typ", "cpp")}), Global.newArray(new Object[]{".cxx", Global.newObject("suf", ".cxx", "typ", "cpp")}), Global.newArray(new Object[]{".C", Global.newObject("suf", ".C", "typ", "cpp")}), Global.newArray(new Object[]{".cc", Global.newObject("suf", ".cc", "typ", "cpp")})}), "wh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "-g", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2 -mo"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf -mo"))})}), "wh");
                po.addFld("versionMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{"TMS320C6x_4.32", "1,0,4.32,0"}), Global.newArray(new Object[]{"TMS320C55x_2.56", "1,0,2.56,0"}), Global.newArray(new Object[]{"TMS320C54x_3.83", "1,0,3.83,0"}), Global.newArray(new Object[]{"TMS320C2000_3.07", "1,0,3.07,0"})}), "wh");
                po.addFld("alignDirectiveSupported", $$T_Bool, true, "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), $$DEFAULT, "rh");
                po.addFld("arOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "", "suffix", ""), "wh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), $$DEFAULT, "rh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "", "suffix", ""), "wh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), $$DEFAULT, "rh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix) -mo", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), $$DEFAULT, "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "", "suffix", ""), "wh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), $$DEFAULT, "rh");
                po.addFld("version", $$T_Str, $$UNDEF, "wh");
                po.addFld("includeOpts", $$T_Str, $$UNDEF, "wh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.targets.ITarget$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.targets.ITarget$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.targets.ITarget$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), fxn);
                fxn = Global.get(cap, "asmName");
                if (fxn != null) po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), fxn);
        // struct ITarget.Command
        po = (Proto.Obj)om.findStrict("ti.targets.ITarget$$Command", "ti.targets");
        po.init("ti.targets.ITarget.Command", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cmd", $$T_Str, $$UNDEF, "w");
                po.addFld("opts", $$T_Str, $$UNDEF, "w");
        // struct ITarget.Options
        po = (Proto.Obj)om.findStrict("ti.targets.ITarget$$Options", "ti.targets");
        po.init("ti.targets.ITarget.Options", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("prefix", $$T_Str, $$UNDEF, "w");
                po.addFld("suffix", $$T_Str, $$UNDEF, "w");
    }

    void C62$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C62.Module", "ti.targets");
        po.init("ti.targets.C62.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C62", "rh");
                po.addFld("suffix", $$T_Str, "62", "rh");
                po.addFld("isa", $$T_Str, "62", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim6xxx:TMS320C6211", "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", ""), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", ""), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk6x", "opts", ""), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts6200.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C62_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C62_big_endian.Module", "ti.targets");
        po.init("ti.targets.C62_big_endian.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C62_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "62e", "rh");
                po.addFld("isa", $$T_Str, "62", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "big"), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C62"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim6xxx:TMS320C6211", "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-me"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-me"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk6x", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts6200e.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C64$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C64.Module", "ti.targets");
        po.init("ti.targets.C64.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C64", "rh");
                po.addFld("suffix", $$T_Str, "64", "rh");
                po.addFld("isa", $$T_Str, "64", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C62"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim6xxx:TMS320C6416", "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"62"}), "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-mv6400"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-mv6400"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk6x", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts6400.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C64_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C64_big_endian.Module", "ti.targets");
        po.init("ti.targets.C64_big_endian.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C64_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "64e", "rh");
                po.addFld("isa", $$T_Str, "64", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "big"), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C62"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim6xxx:TMS320C6416", "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"62e"}), "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv6400"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv6400"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk6x", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts6400e.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C64P$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C64P.Module", "ti.targets");
        po.init("ti.targets.C64P.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C64P", "rh");
                po.addFld("suffix", $$T_Str, "64P", "rh");
                po.addFld("isa", $$T_Str, "64P", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C62"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim6xxx:TMS320CDM420", "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"64", "62"}), "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-mv64p"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-mv64p"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk6x", "opts", ""), "rh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "--symdebug:dwarf", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2 -mo"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf -mo"))})}), "wh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix) -mo --no_compress", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts64plus.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C64P_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C64P_big_endian.Module", "ti.targets");
        po.init("ti.targets.C64P_big_endian.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C64P_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "64Pe", "rh");
                po.addFld("isa", $$T_Str, "64P", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "big"), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C62"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim6xxx:TMS320CDM420", "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"64e", "62e"}), "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv64p"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv64p"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk6x", "opts", ""), "rh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "--symdebug:dwarf", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2 -mo"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf -mo"))})}), "wh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix) -mo --no_compress", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts64pluse.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C674$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C674.Module", "ti.targets");
        po.init("ti.targets.C674.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C674", "rh");
                po.addFld("suffix", $$T_Str, "674", "rh");
                po.addFld("isa", $$T_Str, "674", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C62"), "rh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"64P", "64", "62"}), "wh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.evmDA830", "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-mv6740"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-mv6740"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk6x", "opts", ""), "rh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "--symdebug:dwarf", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2 -mo"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf -mo"))})}), "wh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix) -mo --no_compress", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts6740.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C674_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C674_big_endian.Module", "ti.targets");
        po.init("ti.targets.C674_big_endian.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C674_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "674e", "rh");
                po.addFld("isa", $$T_Str, "674", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "big"), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C62"), "rh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"64Pe", "64e", "62e"}), "wh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.evmDA830", "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv6740"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv6740"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk6x", "opts", ""), "rh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "--symdebug:dwarf", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2 -mo"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf -mo"))})}), "wh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix) -mo --no_compress", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts6740e.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C67$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C67.Module", "ti.targets");
        po.init("ti.targets.C67.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C67", "rh");
                po.addFld("suffix", $$T_Str, "67", "rh");
                po.addFld("isa", $$T_Str, "67", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C62"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim6xxx:TMS320C6713", "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"62"}), "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-mv6700"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-mv6700"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk6x", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts6700.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C67_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C67_big_endian.Module", "ti.targets");
        po.init("ti.targets.C67_big_endian.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C67_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "67e", "rh");
                po.addFld("isa", $$T_Str, "67", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "big"), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C62"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim6xxx:TMS320C6713", "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"62e"}), "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv6700"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv6700"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk6x", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts6700e.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C67P$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C67P.Module", "ti.targets");
        po.init("ti.targets.C67P.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C67P", "rh");
                po.addFld("suffix", $$T_Str, "67P", "rh");
                po.addFld("isa", $$T_Str, "67P", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C62"), "rh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"67", "62"}), "wh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim6xxx:TMS320C6727", "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-mv67p"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-mv67p"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk6x", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts67plus.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C64T$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C64T.Module", "ti.targets");
        po.init("ti.targets.C64T.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C64T", "rh");
                po.addFld("suffix", $$T_Str, "64T", "rh");
                po.addFld("isa", $$T_Str, "64T", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C62"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.qtTesla", "wh");
                po.addFld("stdInclude", $$T_Str, "ti/targets/std.h", "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-mv=tesla --abi=coffabi"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-mv=tesla --abi=coffabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk6x", "opts", "--abi=coffabi"), "rh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "--symdebug:dwarf", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2 -mo"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf -mo"))})}), "wh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix) -mo --no_compress", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rtstesla_le_coff.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C64T_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C64T_big_endian.Module", "ti.targets");
        po.init("ti.targets.C64T_big_endian.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C64T_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "64Te", "rh");
                po.addFld("isa", $$T_Str, "64T", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "big"), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C62"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.qtTesla", "wh");
                po.addFld("stdInclude", $$T_Str, "ti/targets/std.h", "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv=tesla --abi=coffabi"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv=tesla --abi=coffabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk6x", "opts", "--abi=coffabi"), "rh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "--symdebug:dwarf", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2 -mo"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf -mo"))})}), "wh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix) -mo --no_compress", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rtstesla_be_coff.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C54$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C54.Module", "ti.targets");
        po.init("ti.targets.C54.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C54", "rh");
                po.addFld("suffix", $$T_Str, "54", "rh");
                po.addFld("isa", $$T_Str, "54", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject(), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts5400", "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar500", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl500 -c", "opts", ""), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl500", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl500 -c", "opts", ""), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk500", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix)", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts500.lib"), "wh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "-g", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf"))})}), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".switch", "code"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 2L, "align", 2L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 2L, "align", 2L), "t_Float", Global.newObject("size", 2L, "align", 2L), "t_Fxn", Global.newObject("size", 1L, "align", 1L), "t_Int", Global.newObject("size", 1L, "align", 1L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 1L, "align", 1L), "t_Int32", Global.newObject("size", 2L, "align", 2L), "t_Long", Global.newObject("size", 2L, "align", 2L), "t_LDouble", Global.newObject("size", 2L, "align", 2L), "t_Ptr", Global.newObject("size", 1L, "align", 1L), "t_Short", Global.newObject("size", 1L, "align", 1L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 16L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C54_far$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C54_far.Module", "ti.targets");
        po.init("ti.targets.C54_far.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C54_far", "rh");
                po.addFld("suffix", $$T_Str, "54f", "rh");
                po.addFld("isa", $$T_Str, "54", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("codeModel", "far"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts5400", "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C54"), "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar500", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl500 -c", "opts", "-mf -v548"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl500", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl500 -c", "opts", "-mf -v548"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk500", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix)", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts500EXT.lib"), "wh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "-g", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf"))})}), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".switch", "code"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 2L, "align", 2L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 2L, "align", 2L), "t_Float", Global.newObject("size", 2L, "align", 2L), "t_Fxn", Global.newObject("size", 2L, "align", 2L), "t_Int", Global.newObject("size", 1L, "align", 1L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 1L, "align", 1L), "t_Int32", Global.newObject("size", 2L, "align", 2L), "t_Long", Global.newObject("size", 2L, "align", 2L), "t_LDouble", Global.newObject("size", 2L, "align", 2L), "t_Ptr", Global.newObject("size", 1L, "align", 1L), "t_Short", Global.newObject("size", 1L, "align", 1L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 16L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C55$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C55.Module", "ti.targets");
        po.init("ti.targets.C55.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C55", "rh");
                po.addFld("suffix", $$T_Str, "55", "rh");
                po.addFld("isa", $$T_Str, "55", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "big"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts5500", "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar55", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55 -c", "opts", ""), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55", "opts", ""), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55 -c", "opts", ""), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk55", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225 -Dfar= ", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts55.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".sysstack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".cio", "code"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "code"}), Global.newArray(new Object[]{".sysmem", "code"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{"vectors", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 2L, "align", 2L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 2L, "align", 2L), "t_Float", Global.newObject("size", 2L, "align", 2L), "t_Fxn", Global.newObject("size", 2L, "align", 2L), "t_Int", Global.newObject("size", 1L, "align", 1L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 1L, "align", 1L), "t_Int32", Global.newObject("size", 2L, "align", 2L), "t_Int40", Global.newObject("size", 4L, "align", 2L), "t_Long", Global.newObject("size", 2L, "align", 2L), "t_LDouble", Global.newObject("size", 2L, "align", 2L), "t_LLong", Global.newObject("size", 4L, "align", 2L), "t_Ptr", Global.newObject("size", 1L, "align", 1L), "t_Short", Global.newObject("size", 1L, "align", 1L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 16L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C55_large$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C55_large.Module", "ti.targets");
        po.init("ti.targets.C55_large.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C55_large", "rh");
                po.addFld("suffix", $$T_Str, "55L", "rh");
                po.addFld("isa", $$T_Str, "55", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "big", "dataModel", "large"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts5500", "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C55"), "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar55", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55 -c", "opts", "-ml"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55", "opts", ""), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55 -c", "opts", "-ml"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk55", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225 -Dfar= ", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts55x.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".sysstack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".cio", "code"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "code"}), Global.newArray(new Object[]{".sysmem", "code"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{"vectors", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 2L, "align", 2L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 2L, "align", 2L), "t_Float", Global.newObject("size", 2L, "align", 2L), "t_Fxn", Global.newObject("size", 2L, "align", 2L), "t_Int", Global.newObject("size", 1L, "align", 1L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 1L, "align", 1L), "t_Int32", Global.newObject("size", 2L, "align", 2L), "t_Int40", Global.newObject("size", 4L, "align", 2L), "t_Long", Global.newObject("size", 2L, "align", 2L), "t_LDouble", Global.newObject("size", 2L, "align", 2L), "t_LLong", Global.newObject("size", 4L, "align", 2L), "t_Ptr", Global.newObject("size", 2L, "align", 2L), "t_Short", Global.newObject("size", 1L, "align", 1L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 16L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C55_huge$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C55_huge.Module", "ti.targets");
        po.init("ti.targets.C55_huge.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C55_huge", "rh");
                po.addFld("suffix", $$T_Str, "55H", "rh");
                po.addFld("isa", $$T_Str, "55", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "big", "dataModel", "huge"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts5500", "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.C55"), "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar55", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55 -c", "opts", "--memory_model=huge"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55", "opts", ""), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55 -c", "opts", "--memory_model=huge"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk55", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -vcore:3", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -vcore:3 -pdsw225 -Dfar= ", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts55h.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".sysstack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".cio", "code"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "code"}), Global.newArray(new Object[]{".sysmem", "code"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{"vectors", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 2L, "align", 2L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 2L, "align", 2L), "t_Float", Global.newObject("size", 2L, "align", 2L), "t_Fxn", Global.newObject("size", 2L, "align", 2L), "t_Int", Global.newObject("size", 1L, "align", 1L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 1L, "align", 1L), "t_Int32", Global.newObject("size", 2L, "align", 2L), "t_Int40", Global.newObject("size", 4L, "align", 2L), "t_Long", Global.newObject("size", 2L, "align", 2L), "t_LDouble", Global.newObject("size", 2L, "align", 2L), "t_LLong", Global.newObject("size", 4L, "align", 2L), "t_Ptr", Global.newObject("size", 2L, "align", 2L), "t_Short", Global.newObject("size", 1L, "align", 1L), "t_Size", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 16L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C55P_word$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C55P_word.Module", "ti.targets");
        po.init("ti.targets.C55P_word.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C55P_word", "rh");
                po.addFld("suffix", $$T_Str, "55Pw", "rh");
                po.addFld("isa", $$T_Str, "55P", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts5500", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "big", "dataModel", "huge"), "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar55", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55 -c", "opts", "--memory_model=huge"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55", "opts", ""), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55 -c", "opts", "--memory_model=huge"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk55", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-vcore+ -qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-vcore+ -qq -pdsw225 -Dfar= ", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts55ph.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".sysstack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".cio", "code"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "code"}), Global.newArray(new Object[]{".sysmem", "code"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{"vectors", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 2L, "align", 2L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 2L, "align", 2L), "t_Float", Global.newObject("size", 2L, "align", 2L), "t_Fxn", Global.newObject("size", 2L, "align", 2L), "t_Int", Global.newObject("size", 1L, "align", 1L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 1L, "align", 1L), "t_Int32", Global.newObject("size", 2L, "align", 2L), "t_Int40", Global.newObject("size", 4L, "align", 2L), "t_Long", Global.newObject("size", 2L, "align", 2L), "t_LDouble", Global.newObject("size", 2L, "align", 2L), "t_LLong", Global.newObject("size", 4L, "align", 2L), "t_Ptr", Global.newObject("size", 2L, "align", 2L), "t_Short", Global.newObject("size", 1L, "align", 1L), "t_Size", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 16L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C55P_byte$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C55P_byte.Module", "ti.targets");
        po.init("ti.targets.C55P_byte.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C55P_byte", "rh");
                po.addFld("suffix", $$T_Str, "55Pb", "rh");
                po.addFld("isa", $$T_Str, "55P", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts5500", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "big", "dataModel", "huge"), "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar55", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55 -c", "opts", "--memory_model=huge --byte_mode"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55", "opts", ""), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl55 -c", "opts", "--memory_model=huge --byte_mode"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk55", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-vcore+ -qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-vcore+ -qq -pdsw225 -Dfar= ", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts55phb.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".sysstack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".cio", "code"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".switch", "code"}), Global.newArray(new Object[]{".sysmem", "code"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{"vectors", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 4L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 2L, "align", 2L), "t_Int8", Global.newObject("size", 2L, "align", 2L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 4L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C28$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C28.Module", "ti.targets");
        po.init("ti.targets.C28.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C28", "rh");
                po.addFld("suffix", $$T_Str, "28", "rh");
                po.addFld("isa", $$T_Str, "28", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts2800", "rh");
                po.addFld("alignDirectiveSupported", $$T_Bool, false, "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar2000", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl2000 -c", "opts", "-v28"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl2000", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl2000 -c", "opts", "-v28"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk2000", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts2800.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".ebss", "data"}), Global.newArray(new Object[]{".econst", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".esysmem", "data"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"}), Global.newArray(new Object[]{".reset", "code"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 2L, "align", 2L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 2L, "align", 2L), "t_Float", Global.newObject("size", 2L, "align", 2L), "t_Fxn", Global.newObject("size", 2L, "align", 1L), "t_Int", Global.newObject("size", 1L, "align", 1L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 1L, "align", 1L), "t_Int32", Global.newObject("size", 2L, "align", 2L), "t_Int64", Global.newObject("size", 4L, "align", 2L), "t_Long", Global.newObject("size", 2L, "align", 2L), "t_LDouble", Global.newObject("size", 2L, "align", 2L), "t_LLong", Global.newObject("size", 4L, "align", 2L), "t_Ptr", Global.newObject("size", 1L, "align", 1L), "t_Short", Global.newObject("size", 1L, "align", 1L), "t_Size", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 16L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C28_large$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C28_large.Module", "ti.targets");
        po.init("ti.targets.C28_large.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C28_large", "rh");
                po.addFld("suffix", $$T_Str, "28L", "rh");
                po.addFld("isa", $$T_Str, "28", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("dataModel", "large", "endian", "little"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts2800", "rh");
                po.addFld("alignDirectiveSupported", $$T_Bool, false, "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar2000", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl2000 -c", "opts", "-v28 -DLARGE_MODEL=1 -ml"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl2000", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl2000 -c", "opts", "-v28 -ml -DLARGE_MODEL=1"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk2000", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225 -Dfar= ", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts2800_ml.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".ebss", "data"}), Global.newArray(new Object[]{".econst", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".esysmem", "data"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"}), Global.newArray(new Object[]{".reset", "code"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 2L, "align", 2L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 2L, "align", 2L), "t_Float", Global.newObject("size", 2L, "align", 2L), "t_Fxn", Global.newObject("size", 2L, "align", 2L), "t_Int", Global.newObject("size", 1L, "align", 1L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 1L, "align", 1L), "t_Int32", Global.newObject("size", 2L, "align", 2L), "t_Int64", Global.newObject("size", 4L, "align", 2L), "t_Long", Global.newObject("size", 2L, "align", 2L), "t_LDouble", Global.newObject("size", 2L, "align", 2L), "t_LLong", Global.newObject("size", 4L, "align", 2L), "t_Ptr", Global.newObject("size", 2L, "align", 2L), "t_Short", Global.newObject("size", 1L, "align", 1L), "t_Size", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 16L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void C28_float$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.C28_float.Module", "ti.targets");
        po.init("ti.targets.C28_float.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C28_float", "rh");
                po.addFld("suffix", $$T_Str, "28FP", "rh");
                po.addFld("isa", $$T_Str, "28FP", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("dataModel", "large", "endian", "little"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts2800", "rh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"28L"}), "wh");
                po.addFld("alignDirectiveSupported", $$T_Bool, false, "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar2000", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl2000 -c", "opts", "-v28 -DLARGE_MODEL=1 -ml --float_support=fpu32"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl2000", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl2000 -c", "opts", "-v28 -ml -DLARGE_MODEL=1 --float_support=fpu32"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk2000", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225 -Dfar= ", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts2800_fpu32.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".ebss", "data"}), Global.newArray(new Object[]{".econst", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".esysmem", "data"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"}), Global.newArray(new Object[]{".reset", "code"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 2L, "align", 2L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 2L, "align", 2L), "t_Float", Global.newObject("size", 2L, "align", 2L), "t_Fxn", Global.newObject("size", 2L, "align", 2L), "t_Int", Global.newObject("size", 1L, "align", 1L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 1L, "align", 1L), "t_Int32", Global.newObject("size", 2L, "align", 2L), "t_Int64", Global.newObject("size", 4L, "align", 2L), "t_Long", Global.newObject("size", 2L, "align", 2L), "t_LDouble", Global.newObject("size", 2L, "align", 2L), "t_LLong", Global.newObject("size", 4L, "align", 2L), "t_Ptr", Global.newObject("size", 2L, "align", 2L), "t_Short", Global.newObject("size", 1L, "align", 1L), "t_Size", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 16L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void TMS470$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.TMS470.Module", "ti.targets");
        po.init("ti.targets.TMS470.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "TMS470", "rh");
                po.addFld("suffix", $$T_Str, "470", "rh");
                po.addFld("isa", $$T_Str, "470", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts470", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim470xx", "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"7"}), "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar470", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl470 -c", "opts", " -me -mv4"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl470", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl470 -c", "opts", " -me -mv4"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk470", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix) -ms", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("linkLib", $$T_Str, "rts16e.lib", "wh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "-g", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2 -ms"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf -ms"))})}), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map "), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include/rts -I$(rootDir)/include ", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".intvecs", "code"}), Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".const", "code"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".args", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 4L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 4L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void TMS470_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.TMS470_big_endian.Module", "ti.targets");
        po.init("ti.targets.TMS470_big_endian.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "TMS470_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "470e", "rh");
                po.addFld("isa", $$T_Str, "470", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts470", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "big"), "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim470xx", "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"7e"}), "wh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets"), om.find("ti.targets.TMS470"), "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar470", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl470 -c", "opts", "-mv4"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl470", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl470 -c", "opts", "-mv4"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk470", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix) -ms", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "-g", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2 -ms"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf -ms"))})}), "wh");
                po.addFld("linkLib", $$T_Str, "rts16.lib", "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map "), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include/rts -I$(rootDir)/include ", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".intvecs", "code"}), Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".const", "code"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".args", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 4L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 4L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), $$UNDEF);
    }

    void MSP430$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/MSP430.xs");
        om.bind("ti.targets.MSP430$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.targets.MSP430.Module", "ti.targets");
        po.init("ti.targets.MSP430.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "MSP430", "rh");
                po.addFld("suffix", $$T_Str, "430", "rh");
                po.addFld("isa", $$T_Str, "430", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts430", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "little"), "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar430", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl430 -c", "opts", " -vmsp"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl430", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl430 -c", "opts", " -vmsp"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk430", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix)", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("linkLib", $$T_Str, "rts430.lib", "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map "), "wh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "-g", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf"))})}), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include ", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".const", "code"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"}), Global.newArray(new Object[]{".reset", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 2L, "align", 2L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 4L, "align", 2L), "t_Float", Global.newObject("size", 4L, "align", 2L), "t_Fxn", Global.newObject("size", 2L, "align", 2L), "t_Int", Global.newObject("size", 2L, "align", 2L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 2L), "t_Long", Global.newObject("size", 4L, "align", 2L), "t_LDouble", Global.newObject("size", 4L, "align", 2L), "t_LLong", Global.newObject("size", 4L, "align", 2L), "t_Ptr", Global.newObject("size", 2L, "align", 2L), "t_Short", Global.newObject("size", 2L, "align", 2L), "t_Size", Global.newObject("size", 2L, "align", 2L)), "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.targets.MSP430$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.targets.MSP430$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.targets.MSP430$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), fxn);
                fxn = Global.get(cap, "asmName");
                if (fxn != null) po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), fxn);
    }

    void MSP430_large_code$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/MSP430_large_code.xs");
        om.bind("ti.targets.MSP430_large_code$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.targets.MSP430_large_code.Module", "ti.targets");
        po.init("ti.targets.MSP430_large_code.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "MSP430_large_code", "rh");
                po.addFld("suffix", $$T_Str, "430X", "rh");
                po.addFld("isa", $$T_Str, "430", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts430", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "little", "codeModel", "large"), "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar430", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl430 -c", "opts", " -vmspx"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl430", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl430 -c", "opts", " -vmspx"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk430", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix)", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("linkLib", $$T_Str, "rts430x.lib", "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map "), "wh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "-g", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf"))})}), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include ", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".const", "code"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"}), Global.newArray(new Object[]{".reset", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 2L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 4L, "align", 2L), "t_Float", Global.newObject("size", 4L, "align", 2L), "t_Fxn", Global.newObject("size", 4L, "align", 2L), "t_Int", Global.newObject("size", 2L, "align", 2L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 2L), "t_Long", Global.newObject("size", 4L, "align", 2L), "t_LDouble", Global.newObject("size", 4L, "align", 2L), "t_LLong", Global.newObject("size", 4L, "align", 2L), "t_Ptr", Global.newObject("size", 2L, "align", 2L), "t_Short", Global.newObject("size", 2L, "align", 2L), "t_Size", Global.newObject("size", 2L, "align", 2L)), "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.targets.MSP430_large_code$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.targets.MSP430_large_code$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.targets.MSP430_large_code$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), fxn);
                fxn = Global.get(cap, "asmName");
                if (fxn != null) po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), fxn);
    }

    void MSP430_large_data$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/MSP430_large_data.xs");
        om.bind("ti.targets.MSP430_large_data$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.targets.MSP430_large_data.Module", "ti.targets");
        po.init("ti.targets.MSP430_large_data.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "MSP430_large_data", "rh");
                po.addFld("suffix", $$T_Str, "430XL", "rh");
                po.addFld("isa", $$T_Str, "430", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts430", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets"), Global.newObject("endian", "little", "dataModel", "large", "codeModel", "large"), "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "ar430", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl430 -c", "opts", " -vmspx -ml"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl430", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "cl430 -c", "opts", " -vmspx -ml"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets"), Global.newObject("cmd", "lnk430", "opts", ""), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "$(ccOpts.prefix)", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("linkLib", $$T_Str, "rts430xl.lib", "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map "), "wh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "-g", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "-gp"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf"))})}), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include ", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".const", "code"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"}), Global.newArray(new Object[]{".reset", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 2L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 4L, "align", 2L), "t_Float", Global.newObject("size", 4L, "align", 2L), "t_Fxn", Global.newObject("size", 4L, "align", 2L), "t_Int", Global.newObject("size", 2L, "align", 2L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 2L), "t_Long", Global.newObject("size", 4L, "align", 2L), "t_LDouble", Global.newObject("size", 4L, "align", 2L), "t_LLong", Global.newObject("size", 4L, "align", 2L), "t_Ptr", Global.newObject("size", 4L, "align", 2L), "t_Short", Global.newObject("size", 2L, "align", 2L), "t_Size", Global.newObject("size", 4L, "align", 2L)), "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.targets.MSP430_large_data$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.targets.MSP430_large_data$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.targets.MSP430_large_data$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets"), fxn);
                fxn = Global.get(cap, "asmName");
                if (fxn != null) po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets"), fxn);
    }

    void ITarget$$ROV()
    {
    }

    void C62$$ROV()
    {
    }

    void C62_big_endian$$ROV()
    {
    }

    void C64$$ROV()
    {
    }

    void C64_big_endian$$ROV()
    {
    }

    void C64P$$ROV()
    {
    }

    void C64P_big_endian$$ROV()
    {
    }

    void C674$$ROV()
    {
    }

    void C674_big_endian$$ROV()
    {
    }

    void C67$$ROV()
    {
    }

    void C67_big_endian$$ROV()
    {
    }

    void C67P$$ROV()
    {
    }

    void C64T$$ROV()
    {
    }

    void C64T_big_endian$$ROV()
    {
    }

    void C54$$ROV()
    {
    }

    void C54_far$$ROV()
    {
    }

    void C55$$ROV()
    {
    }

    void C55_large$$ROV()
    {
    }

    void C55_huge$$ROV()
    {
    }

    void C55P_word$$ROV()
    {
    }

    void C55P_byte$$ROV()
    {
    }

    void C28$$ROV()
    {
    }

    void C28_large$$ROV()
    {
    }

    void C28_float$$ROV()
    {
    }

    void TMS470$$ROV()
    {
    }

    void TMS470_big_endian$$ROV()
    {
    }

    void MSP430$$ROV()
    {
    }

    void MSP430_large_code$$ROV()
    {
    }

    void MSP430_large_data$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.targets.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.targets"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.targets"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.targets"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.targets"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.targets"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.targets"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.targets"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.targets", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.targets");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.targets.");
        pkgV.bind("$vers", Global.newArray("1, 0, 3"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.bld", Global.newArray(1, 0, 1)));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.targets'];\n");
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

    void ITarget$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.ITarget", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.ITarget.Module", "ti.targets");
        vo.init2(po, "ti.targets.ITarget", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", om.findStrict("ti.targets.ITarget$$capsule", "ti.targets"));
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ITarget", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ITarget");
        vo.seal(null);
    }

    void C62$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C62", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C62.Module", "ti.targets");
        vo.init2(po, "ti.targets.C62", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C62$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C62", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C62");
    }

    void C62_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C62_big_endian", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C62_big_endian.Module", "ti.targets");
        vo.init2(po, "ti.targets.C62_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C62_big_endian$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C62_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C62_big_endian");
    }

    void C64$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C64", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C64.Module", "ti.targets");
        vo.init2(po, "ti.targets.C64", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C64$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C64", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C64");
    }

    void C64_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C64_big_endian", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C64_big_endian.Module", "ti.targets");
        vo.init2(po, "ti.targets.C64_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C64_big_endian$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C64_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C64_big_endian");
    }

    void C64P$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C64P", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C64P.Module", "ti.targets");
        vo.init2(po, "ti.targets.C64P", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C64P$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C64P", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C64P");
    }

    void C64P_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C64P_big_endian", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C64P_big_endian.Module", "ti.targets");
        vo.init2(po, "ti.targets.C64P_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C64P_big_endian$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C64P_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C64P_big_endian");
    }

    void C674$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C674", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C674.Module", "ti.targets");
        vo.init2(po, "ti.targets.C674", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C674$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C674", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C674");
    }

    void C674_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C674_big_endian", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C674_big_endian.Module", "ti.targets");
        vo.init2(po, "ti.targets.C674_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C674_big_endian$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C674_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C674_big_endian");
    }

    void C67$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C67", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C67.Module", "ti.targets");
        vo.init2(po, "ti.targets.C67", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C67$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C67", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C67");
    }

    void C67_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C67_big_endian", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C67_big_endian.Module", "ti.targets");
        vo.init2(po, "ti.targets.C67_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C67_big_endian$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C67_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C67_big_endian");
    }

    void C67P$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C67P", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C67P.Module", "ti.targets");
        vo.init2(po, "ti.targets.C67P", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C67P$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C67P", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C67P");
    }

    void C64T$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C64T", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C64T.Module", "ti.targets");
        vo.init2(po, "ti.targets.C64T", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C64T$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C64T", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C64T");
    }

    void C64T_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C64T_big_endian", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C64T_big_endian.Module", "ti.targets");
        vo.init2(po, "ti.targets.C64T_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C64T_big_endian$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C64T_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C64T_big_endian");
    }

    void C54$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C54", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C54.Module", "ti.targets");
        vo.init2(po, "ti.targets.C54", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C54$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C54", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C54");
    }

    void C54_far$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C54_far", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C54_far.Module", "ti.targets");
        vo.init2(po, "ti.targets.C54_far", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C54_far$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C54_far", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C54_far");
    }

    void C55$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C55", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C55.Module", "ti.targets");
        vo.init2(po, "ti.targets.C55", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C55$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C55", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C55");
    }

    void C55_large$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C55_large", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C55_large.Module", "ti.targets");
        vo.init2(po, "ti.targets.C55_large", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C55_large$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C55_large", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C55_large");
    }

    void C55_huge$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C55_huge", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C55_huge.Module", "ti.targets");
        vo.init2(po, "ti.targets.C55_huge", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C55_huge$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C55_huge", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C55_huge");
    }

    void C55P_word$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C55P_word", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C55P_word.Module", "ti.targets");
        vo.init2(po, "ti.targets.C55P_word", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C55P_word$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C55P_word", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C55P_word");
    }

    void C55P_byte$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C55P_byte", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C55P_byte.Module", "ti.targets");
        vo.init2(po, "ti.targets.C55P_byte", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C55P_byte$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C55P_byte", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C55P_byte");
    }

    void C28$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C28", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C28.Module", "ti.targets");
        vo.init2(po, "ti.targets.C28", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C28$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C28", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C28");
    }

    void C28_large$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C28_large", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C28_large.Module", "ti.targets");
        vo.init2(po, "ti.targets.C28_large", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C28_large$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C28_large", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C28_large");
    }

    void C28_float$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.C28_float", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.C28_float.Module", "ti.targets");
        vo.init2(po, "ti.targets.C28_float", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.C28_float$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("C28_float", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("C28_float");
    }

    void TMS470$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.TMS470", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.TMS470.Module", "ti.targets");
        vo.init2(po, "ti.targets.TMS470", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.TMS470$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("TMS470", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS470");
    }

    void TMS470_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.TMS470_big_endian", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.TMS470_big_endian.Module", "ti.targets");
        vo.init2(po, "ti.targets.TMS470_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.TMS470_big_endian$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("TMS470_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS470_big_endian");
    }

    void MSP430$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.MSP430", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.MSP430.Module", "ti.targets");
        vo.init2(po, "ti.targets.MSP430", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.targets.MSP430$$capsule", "ti.targets"));
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.MSP430$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("MSP430", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("MSP430");
    }

    void MSP430_large_code$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.MSP430_large_code", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.MSP430_large_code.Module", "ti.targets");
        vo.init2(po, "ti.targets.MSP430_large_code", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.targets.MSP430_large_code$$capsule", "ti.targets"));
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.MSP430_large_code$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("MSP430_large_code", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("MSP430_large_code");
    }

    void MSP430_large_data$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.MSP430_large_data", "ti.targets");
        po = (Proto.Obj)om.findStrict("ti.targets.MSP430_large_data.Module", "ti.targets");
        vo.init2(po, "ti.targets.MSP430_large_data", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.targets.MSP430_large_data$$capsule", "ti.targets"));
        vo.bind("$package", om.findStrict("ti.targets", "ti.targets"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.MSP430_large_data$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("MSP430_large_data", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("MSP430_large_data");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C62", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C62_big_endian", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C64", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C64_big_endian", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C64P", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C64P_big_endian", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C674", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C674_big_endian", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C67", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C67_big_endian", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C67P", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C64T", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C64T_big_endian", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C54", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C54_far", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C55", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C55_large", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C55_huge", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C55P_word", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C55P_byte", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C28", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C28_large", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.C28_float", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.TMS470", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.TMS470_big_endian", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.MSP430", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.MSP430_large_code", "ti.targets"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.MSP430_large_data", "ti.targets"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.targets.ITarget")).bless();
        ((Value.Obj)om.getv("ti.targets.C62")).bless();
        ((Value.Obj)om.getv("ti.targets.C62_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.C64")).bless();
        ((Value.Obj)om.getv("ti.targets.C64_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.C64P")).bless();
        ((Value.Obj)om.getv("ti.targets.C64P_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.C674")).bless();
        ((Value.Obj)om.getv("ti.targets.C674_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.C67")).bless();
        ((Value.Obj)om.getv("ti.targets.C67_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.C67P")).bless();
        ((Value.Obj)om.getv("ti.targets.C64T")).bless();
        ((Value.Obj)om.getv("ti.targets.C64T_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.C54")).bless();
        ((Value.Obj)om.getv("ti.targets.C54_far")).bless();
        ((Value.Obj)om.getv("ti.targets.C55")).bless();
        ((Value.Obj)om.getv("ti.targets.C55_large")).bless();
        ((Value.Obj)om.getv("ti.targets.C55_huge")).bless();
        ((Value.Obj)om.getv("ti.targets.C55P_word")).bless();
        ((Value.Obj)om.getv("ti.targets.C55P_byte")).bless();
        ((Value.Obj)om.getv("ti.targets.C28")).bless();
        ((Value.Obj)om.getv("ti.targets.C28_large")).bless();
        ((Value.Obj)om.getv("ti.targets.C28_float")).bless();
        ((Value.Obj)om.getv("ti.targets.TMS470")).bless();
        ((Value.Obj)om.getv("ti.targets.TMS470_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.MSP430")).bless();
        ((Value.Obj)om.getv("ti.targets.MSP430_large_code")).bless();
        ((Value.Obj)om.getv("ti.targets.MSP430_large_data")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.targets")).add(pkgV);
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
        ITarget$$OBJECTS();
        C62$$OBJECTS();
        C62_big_endian$$OBJECTS();
        C64$$OBJECTS();
        C64_big_endian$$OBJECTS();
        C64P$$OBJECTS();
        C64P_big_endian$$OBJECTS();
        C674$$OBJECTS();
        C674_big_endian$$OBJECTS();
        C67$$OBJECTS();
        C67_big_endian$$OBJECTS();
        C67P$$OBJECTS();
        C64T$$OBJECTS();
        C64T_big_endian$$OBJECTS();
        C54$$OBJECTS();
        C54_far$$OBJECTS();
        C55$$OBJECTS();
        C55_large$$OBJECTS();
        C55_huge$$OBJECTS();
        C55P_word$$OBJECTS();
        C55P_byte$$OBJECTS();
        C28$$OBJECTS();
        C28_large$$OBJECTS();
        C28_float$$OBJECTS();
        TMS470$$OBJECTS();
        TMS470_big_endian$$OBJECTS();
        MSP430$$OBJECTS();
        MSP430_large_code$$OBJECTS();
        MSP430_large_data$$OBJECTS();
        ITarget$$CONSTS();
        C62$$CONSTS();
        C62_big_endian$$CONSTS();
        C64$$CONSTS();
        C64_big_endian$$CONSTS();
        C64P$$CONSTS();
        C64P_big_endian$$CONSTS();
        C674$$CONSTS();
        C674_big_endian$$CONSTS();
        C67$$CONSTS();
        C67_big_endian$$CONSTS();
        C67P$$CONSTS();
        C64T$$CONSTS();
        C64T_big_endian$$CONSTS();
        C54$$CONSTS();
        C54_far$$CONSTS();
        C55$$CONSTS();
        C55_large$$CONSTS();
        C55_huge$$CONSTS();
        C55P_word$$CONSTS();
        C55P_byte$$CONSTS();
        C28$$CONSTS();
        C28_large$$CONSTS();
        C28_float$$CONSTS();
        TMS470$$CONSTS();
        TMS470_big_endian$$CONSTS();
        MSP430$$CONSTS();
        MSP430_large_code$$CONSTS();
        MSP430_large_data$$CONSTS();
        ITarget$$CREATES();
        C62$$CREATES();
        C62_big_endian$$CREATES();
        C64$$CREATES();
        C64_big_endian$$CREATES();
        C64P$$CREATES();
        C64P_big_endian$$CREATES();
        C674$$CREATES();
        C674_big_endian$$CREATES();
        C67$$CREATES();
        C67_big_endian$$CREATES();
        C67P$$CREATES();
        C64T$$CREATES();
        C64T_big_endian$$CREATES();
        C54$$CREATES();
        C54_far$$CREATES();
        C55$$CREATES();
        C55_large$$CREATES();
        C55_huge$$CREATES();
        C55P_word$$CREATES();
        C55P_byte$$CREATES();
        C28$$CREATES();
        C28_large$$CREATES();
        C28_float$$CREATES();
        TMS470$$CREATES();
        TMS470_big_endian$$CREATES();
        MSP430$$CREATES();
        MSP430_large_code$$CREATES();
        MSP430_large_data$$CREATES();
        ITarget$$FUNCTIONS();
        C62$$FUNCTIONS();
        C62_big_endian$$FUNCTIONS();
        C64$$FUNCTIONS();
        C64_big_endian$$FUNCTIONS();
        C64P$$FUNCTIONS();
        C64P_big_endian$$FUNCTIONS();
        C674$$FUNCTIONS();
        C674_big_endian$$FUNCTIONS();
        C67$$FUNCTIONS();
        C67_big_endian$$FUNCTIONS();
        C67P$$FUNCTIONS();
        C64T$$FUNCTIONS();
        C64T_big_endian$$FUNCTIONS();
        C54$$FUNCTIONS();
        C54_far$$FUNCTIONS();
        C55$$FUNCTIONS();
        C55_large$$FUNCTIONS();
        C55_huge$$FUNCTIONS();
        C55P_word$$FUNCTIONS();
        C55P_byte$$FUNCTIONS();
        C28$$FUNCTIONS();
        C28_large$$FUNCTIONS();
        C28_float$$FUNCTIONS();
        TMS470$$FUNCTIONS();
        TMS470_big_endian$$FUNCTIONS();
        MSP430$$FUNCTIONS();
        MSP430_large_code$$FUNCTIONS();
        MSP430_large_data$$FUNCTIONS();
        ITarget$$SIZES();
        C62$$SIZES();
        C62_big_endian$$SIZES();
        C64$$SIZES();
        C64_big_endian$$SIZES();
        C64P$$SIZES();
        C64P_big_endian$$SIZES();
        C674$$SIZES();
        C674_big_endian$$SIZES();
        C67$$SIZES();
        C67_big_endian$$SIZES();
        C67P$$SIZES();
        C64T$$SIZES();
        C64T_big_endian$$SIZES();
        C54$$SIZES();
        C54_far$$SIZES();
        C55$$SIZES();
        C55_large$$SIZES();
        C55_huge$$SIZES();
        C55P_word$$SIZES();
        C55P_byte$$SIZES();
        C28$$SIZES();
        C28_large$$SIZES();
        C28_float$$SIZES();
        TMS470$$SIZES();
        TMS470_big_endian$$SIZES();
        MSP430$$SIZES();
        MSP430_large_code$$SIZES();
        MSP430_large_data$$SIZES();
        ITarget$$TYPES();
        C62$$TYPES();
        C62_big_endian$$TYPES();
        C64$$TYPES();
        C64_big_endian$$TYPES();
        C64P$$TYPES();
        C64P_big_endian$$TYPES();
        C674$$TYPES();
        C674_big_endian$$TYPES();
        C67$$TYPES();
        C67_big_endian$$TYPES();
        C67P$$TYPES();
        C64T$$TYPES();
        C64T_big_endian$$TYPES();
        C54$$TYPES();
        C54_far$$TYPES();
        C55$$TYPES();
        C55_large$$TYPES();
        C55_huge$$TYPES();
        C55P_word$$TYPES();
        C55P_byte$$TYPES();
        C28$$TYPES();
        C28_large$$TYPES();
        C28_float$$TYPES();
        TMS470$$TYPES();
        TMS470_big_endian$$TYPES();
        MSP430$$TYPES();
        MSP430_large_code$$TYPES();
        MSP430_large_data$$TYPES();
        if (isROV) {
            ITarget$$ROV();
            C62$$ROV();
            C62_big_endian$$ROV();
            C64$$ROV();
            C64_big_endian$$ROV();
            C64P$$ROV();
            C64P_big_endian$$ROV();
            C674$$ROV();
            C674_big_endian$$ROV();
            C67$$ROV();
            C67_big_endian$$ROV();
            C67P$$ROV();
            C64T$$ROV();
            C64T_big_endian$$ROV();
            C54$$ROV();
            C54_far$$ROV();
            C55$$ROV();
            C55_large$$ROV();
            C55_huge$$ROV();
            C55P_word$$ROV();
            C55P_byte$$ROV();
            C28$$ROV();
            C28_large$$ROV();
            C28_float$$ROV();
            TMS470$$ROV();
            TMS470_big_endian$$ROV();
            MSP430$$ROV();
            MSP430_large_code$$ROV();
            MSP430_large_data$$ROV();
        }//isROV
        $$SINGLETONS();
        ITarget$$SINGLETONS();
        C62$$SINGLETONS();
        C62_big_endian$$SINGLETONS();
        C64$$SINGLETONS();
        C64_big_endian$$SINGLETONS();
        C64P$$SINGLETONS();
        C64P_big_endian$$SINGLETONS();
        C674$$SINGLETONS();
        C674_big_endian$$SINGLETONS();
        C67$$SINGLETONS();
        C67_big_endian$$SINGLETONS();
        C67P$$SINGLETONS();
        C64T$$SINGLETONS();
        C64T_big_endian$$SINGLETONS();
        C54$$SINGLETONS();
        C54_far$$SINGLETONS();
        C55$$SINGLETONS();
        C55_large$$SINGLETONS();
        C55_huge$$SINGLETONS();
        C55P_word$$SINGLETONS();
        C55P_byte$$SINGLETONS();
        C28$$SINGLETONS();
        C28_large$$SINGLETONS();
        C28_float$$SINGLETONS();
        TMS470$$SINGLETONS();
        TMS470_big_endian$$SINGLETONS();
        MSP430$$SINGLETONS();
        MSP430_large_code$$SINGLETONS();
        MSP430_large_data$$SINGLETONS();
        $$INITIALIZATION();
    }
}
