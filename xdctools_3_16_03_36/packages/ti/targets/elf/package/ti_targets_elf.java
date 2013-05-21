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

public class ti_targets_elf
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
        Global.callFxn("loadPackage", xdcO, "ti.targets");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.targets.elf.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.targets.elf", new Value.Obj("ti.targets.elf", pkgP));
    }

    void ITarget$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.elf.ITarget.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.elf.ITarget", new Value.Obj("ti.targets.elf.ITarget", po));
        pkgV.bind("ITarget", vo);
        // decls 
        om.bind("ti.targets.elf.ITarget.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        om.bind("ti.targets.elf.ITarget.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        om.bind("ti.targets.elf.ITarget.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        om.bind("ti.targets.elf.ITarget.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        om.bind("ti.targets.elf.ITarget.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.ITarget.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.ITarget.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.ITarget.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.ITarget.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.ITarget.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        om.bind("ti.targets.elf.ITarget.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        om.bind("ti.targets.elf.ITarget.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        om.bind("ti.targets.elf.ITarget.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
    }

    void C64P$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.elf.C64P.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.elf.C64P", new Value.Obj("ti.targets.elf.C64P", po));
        pkgV.bind("C64P", vo);
        // decls 
        om.bind("ti.targets.elf.C64P.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
    }

    void C674$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.elf.C674.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.elf.C674", new Value.Obj("ti.targets.elf.C674", po));
        pkgV.bind("C674", vo);
        // decls 
        om.bind("ti.targets.elf.C674.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
    }

    void C64T$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.elf.C64T.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.elf.C64T", new Value.Obj("ti.targets.elf.C64T", po));
        pkgV.bind("C64T", vo);
        // decls 
        om.bind("ti.targets.elf.C64T.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
    }

    void C67P$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.elf.C67P.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.elf.C67P", new Value.Obj("ti.targets.elf.C67P", po));
        pkgV.bind("C67P", vo);
        // decls 
        om.bind("ti.targets.elf.C67P.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        om.bind("ti.targets.elf.C67P.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        om.bind("ti.targets.elf.C67P.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        om.bind("ti.targets.elf.C67P.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        om.bind("ti.targets.elf.C67P.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C67P.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C67P.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C67P.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C67P.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C67P.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        om.bind("ti.targets.elf.C67P.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        om.bind("ti.targets.elf.C67P.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        om.bind("ti.targets.elf.C67P.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
    }

    void C64P_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.elf.C64P_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.elf.C64P_big_endian", new Value.Obj("ti.targets.elf.C64P_big_endian", po));
        pkgV.bind("C64P_big_endian", vo);
        // decls 
        om.bind("ti.targets.elf.C64P_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64P_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
    }

    void C674_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.elf.C674_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.elf.C674_big_endian", new Value.Obj("ti.targets.elf.C674_big_endian", po));
        pkgV.bind("C674_big_endian", vo);
        // decls 
        om.bind("ti.targets.elf.C674_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        om.bind("ti.targets.elf.C674_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
    }

    void C64T_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.elf.C64T_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.elf.C64T_big_endian", new Value.Obj("ti.targets.elf.C64T_big_endian", po));
        pkgV.bind("C64T_big_endian", vo);
        // decls 
        om.bind("ti.targets.elf.C64T_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        om.bind("ti.targets.elf.C64T_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
    }

    void TMS470$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.elf.TMS470.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.elf.TMS470", new Value.Obj("ti.targets.elf.TMS470", po));
        pkgV.bind("TMS470", vo);
        // decls 
        om.bind("ti.targets.elf.TMS470.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        om.bind("ti.targets.elf.TMS470.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        om.bind("ti.targets.elf.TMS470.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        om.bind("ti.targets.elf.TMS470.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        om.bind("ti.targets.elf.TMS470.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.TMS470.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.TMS470.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.TMS470.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        om.bind("ti.targets.elf.TMS470.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        om.bind("ti.targets.elf.TMS470.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        om.bind("ti.targets.elf.TMS470.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        om.bind("ti.targets.elf.TMS470.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        om.bind("ti.targets.elf.TMS470.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
    }

    void ITarget$$CONSTS()
    {
        // interface ITarget
    }

    void C64P$$CONSTS()
    {
        // module C64P
    }

    void C674$$CONSTS()
    {
        // module C674
    }

    void C64T$$CONSTS()
    {
        // module C64T
    }

    void C67P$$CONSTS()
    {
        // module C67P
    }

    void C64P_big_endian$$CONSTS()
    {
        // module C64P_big_endian
    }

    void C674_big_endian$$CONSTS()
    {
        // module C674_big_endian
    }

    void C64T_big_endian$$CONSTS()
    {
        // module C64T_big_endian
    }

    void TMS470$$CONSTS()
    {
        // module TMS470
    }

    void ITarget$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C64P$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C674$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C64T$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C67P$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C64P_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C674_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void C64T_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TMS470$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ITarget$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C64P$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C674$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C64T$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C67P$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C64P_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C674_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void C64T_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS470$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void ITarget$$SIZES()
    {
    }

    void C64P$$SIZES()
    {
    }

    void C674$$SIZES()
    {
    }

    void C64T$$SIZES()
    {
    }

    void C67P$$SIZES()
    {
    }

    void C64P_big_endian$$SIZES()
    {
    }

    void C674_big_endian$$SIZES()
    {
    }

    void C64T_big_endian$$SIZES()
    {
    }

    void TMS470$$SIZES()
    {
    }

    void ITarget$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/elf/ITarget.xs");
        om.bind("ti.targets.elf.ITarget$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.targets.elf.ITarget.Module", "ti.targets.elf");
        po.init("ti.targets.elf.ITarget.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"), Global.newObject("shortEnums", true), "rh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "--symdebug:dwarf", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2 -mo"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf -mo"))})}), "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".ti.decompress", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".rodata", "data"}), Global.newArray(new Object[]{".neardata", "data"}), Global.newArray(new Object[]{".fardata", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"}), Global.newArray(new Object[]{".ti.handler_table", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("stdInclude", $$T_Str, "ti/targets/elf/std.h", "wh");
                po.addFld("binaryParser", $$T_Str, "ti.targets.omf.elf.Elf32", "wh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.targets.elf.ITarget$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.targets.elf.ITarget$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.targets.elf.ITarget$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.elf"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.elf"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.elf"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.elf"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.elf"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.elf"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.elf"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.elf"), fxn);
                fxn = Global.get(cap, "asmName");
                if (fxn != null) po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.elf"), fxn);
    }

    void C64P$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.elf.C64P.Module", "ti.targets.elf");
        po.init("ti.targets.elf.C64P.Module", om.findStrict("ti.targets.elf.ITarget.Module", "ti.targets.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C64P", "rh");
                po.addFld("suffix", $$T_Str, "e64P", "rh");
                po.addFld("isa", $$T_Str, "64P", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"), Global.newObject("endian", "little", "shortEnums", true), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.elf"), om.find("ti.targets.C62"), "rh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"", "e64", "e62"}), "wh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim6xxx:TMS320CDM420", "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-mv64p --abi=elfabi"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-mv64P --abi=elfabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "lnk6x", "opts", "--abi=elfabi"), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "$(ccOpts.prefix) -mo --no_compress", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts64plus_elf.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.elf"), $$UNDEF);
    }

    void C674$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.elf.C674.Module", "ti.targets.elf");
        po.init("ti.targets.elf.C674.Module", om.findStrict("ti.targets.elf.ITarget.Module", "ti.targets.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C674", "rh");
                po.addFld("suffix", $$T_Str, "e674", "rh");
                po.addFld("isa", $$T_Str, "674", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"), Global.newObject("endian", "little", "shortEnums", true), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.elf"), om.find("ti.targets.C62"), "rh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"e64P", "e64", "e62"}), "wh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.evmDA830", "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-mv6740 --abi=elfabi"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-mv6740 --abi=elfabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "lnk6x", "opts", "--abi=elfabi"), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "$(ccOpts.prefix) -mo --no_compress", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts6740_elf.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.elf"), $$UNDEF);
    }

    void C64T$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.elf.C64T.Module", "ti.targets.elf");
        po.init("ti.targets.elf.C64T.Module", om.findStrict("ti.targets.elf.ITarget.Module", "ti.targets.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C64T", "rh");
                po.addFld("suffix", $$T_Str, "e64T", "rh");
                po.addFld("isa", $$T_Str, "64T", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"), Global.newObject("endian", "little", "shortEnums", true), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.elf"), om.find("ti.targets.C62"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.qtTesla", "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-mv=tesla --abi=elfabi"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-mv=tesla --abi=elfabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "lnk6x", "opts", "--abi=elfabi"), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "$(ccOpts.prefix) -mo --no_compress", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rtstesla_le_elf.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.elf"), $$UNDEF);
    }

    void C67P$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.elf.C67P.Module", "ti.targets.elf");
        po.init("ti.targets.elf.C67P.Module", om.findStrict("ti.targets.elf.ITarget.Module", "ti.targets.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C67P", "rh");
                po.addFld("suffix", $$T_Str, "e67P", "rh");
                po.addFld("isa", $$T_Str, "67P", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"), Global.newObject("endian", "little", "shortEnums", true), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.elf"), om.find("ti.targets.C62"), "rh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"", "e67", "e62"}), "wh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim6xxx:TMS320C6727", "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-mv67p --abi=elfabi"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-mv67p --abi=elfabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "lnk6x", "opts", "--abi=elfabi"), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "$(ccOpts.prefix) -mo", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts67plus_elf.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 8L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int40", Global.newObject("size", 8L, "align", 8L), "t_Int64", Global.newObject("size", 8L, "align", 8L), "t_Long", Global.newObject("size", 8L, "align", 8L), "t_LDouble", Global.newObject("size", 8L, "align", 8L), "t_LLong", Global.newObject("size", 8L, "align", 8L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.elf"), $$UNDEF);
    }

    void C64P_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.elf.C64P_big_endian.Module", "ti.targets.elf");
        po.init("ti.targets.elf.C64P_big_endian.Module", om.findStrict("ti.targets.elf.ITarget.Module", "ti.targets.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C64P_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "e64Pe", "rh");
                po.addFld("isa", $$T_Str, "64P", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"), Global.newObject("endian", "big", "shortEnums", true), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.elf"), om.find("ti.targets.C62"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim6xxx:TMS320CDM420", "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv64p --abi=elfabi"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv64p --abi=elfabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "lnk6x", "opts", "--abi=elfabi"), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "$(ccOpts.prefix) -mo --no_compress", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts64pluse_elf.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.elf"), $$UNDEF);
    }

    void C674_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.elf.C674_big_endian.Module", "ti.targets.elf");
        po.init("ti.targets.elf.C674_big_endian.Module", om.findStrict("ti.targets.elf.ITarget.Module", "ti.targets.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C674_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "e674e", "rh");
                po.addFld("isa", $$T_Str, "674", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"), Global.newObject("endian", "big", "shortEnums", true), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.elf"), om.find("ti.targets.C62"), "rh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"e64Pe"}), "wh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.evmDA830", "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv6740 --abi=elfabi"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv6740 --abi=elfabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "lnk6x", "opts", " --abi=elfabi"), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "$(ccOpts.prefix) -mo --no_compress", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts6740e_elf.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.elf"), $$UNDEF);
    }

    void C64T_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.elf.C64T_big_endian.Module", "ti.targets.elf");
        po.init("ti.targets.elf.C64T_big_endian.Module", om.findStrict("ti.targets.elf.ITarget.Module", "ti.targets.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "C64T_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "e64Te", "rh");
                po.addFld("isa", $$T_Str, "64T", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"), Global.newObject("endian", "big", "shortEnums", true), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.elf"), om.find("ti.targets.C62"), "rh");
                po.addFld("rts", $$T_Str, "ti.targets.rts6000", "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.qtTesla", "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "ar6x", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv=tesla --abi=elfabi"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl6x -c", "opts", "-me -mv=tesla --abi=elfabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "lnk6x", "opts", "--abi=elfabi"), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "$(ccOpts.prefix) -mo --no_compress", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rtstesla_be_elf.lib"), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include", "wh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.elf"), $$UNDEF);
    }

    void TMS470$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.elf.TMS470.Module", "ti.targets.elf");
        po.init("ti.targets.elf.TMS470.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "TMS470", "rh");
                po.addFld("suffix", $$T_Str, "e470", "rh");
                po.addFld("isa", $$T_Str, "470", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"), Global.newObject("endian", "little", "shortEnums", true), "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim470xx", "wh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"7"}), "wh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "ar470", "opts", "rq"), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl470 -c", "opts", " -me -mv4 --abi=eabi"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl470", "opts", "-version"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "cl470 -c", "opts", " -me -mv4 --abi=eabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"), Global.newObject("cmd", "lnk470", "opts", " --abi=eabi"), "rh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "$(ccOpts.prefix) -ms", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("linkLib", $$T_Str, "rtsv4_T_le_eabi.lib", "wh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "-g", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2 -ms"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf -ms"))})}), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map "), "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include/rts -I$(rootDir)/include ", "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".intvecs", "code"}), Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".cinit", "code"}), Global.newArray(new Object[]{".const", "code"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".pinit", "code"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".args", "data"})}), "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 4L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 4L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.elf"), $$UNDEF);
    }

    void ITarget$$ROV()
    {
    }

    void C64P$$ROV()
    {
    }

    void C674$$ROV()
    {
    }

    void C64T$$ROV()
    {
    }

    void C67P$$ROV()
    {
    }

    void C64P_big_endian$$ROV()
    {
    }

    void C674_big_endian$$ROV()
    {
    }

    void C64T_big_endian$$ROV()
    {
    }

    void TMS470$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.targets.elf.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.targets.elf"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/elf/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.targets.elf"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.targets.elf"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.targets.elf"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.targets.elf"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.targets.elf"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.targets.elf"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.targets.elf", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.targets.elf");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.targets.elf.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.bld", Global.newArray(1, 0, 1)));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.targets.elf'];\n");
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

        vo = (Value.Obj)om.findStrict("ti.targets.elf.ITarget", "ti.targets.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.elf.ITarget.Module", "ti.targets.elf");
        vo.init2(po, "ti.targets.elf.ITarget", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", om.findStrict("ti.targets.elf.ITarget$$capsule", "ti.targets.elf"));
        vo.bind("$package", om.findStrict("ti.targets.elf", "ti.targets.elf"));
        tdefs.clear();
        proxies.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ITarget", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ITarget");
        vo.seal(null);
    }

    void C64P$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.elf.C64P", "ti.targets.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.elf.C64P.Module", "ti.targets.elf");
        vo.init2(po, "ti.targets.elf.C64P", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.elf", "ti.targets.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.elf.C64P$$instance$static$init", null) ? 1 : 0);
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

    void C674$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.elf.C674", "ti.targets.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.elf.C674.Module", "ti.targets.elf");
        vo.init2(po, "ti.targets.elf.C674", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.elf", "ti.targets.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.elf.C674$$instance$static$init", null) ? 1 : 0);
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

    void C64T$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.elf.C64T", "ti.targets.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.elf.C64T.Module", "ti.targets.elf");
        vo.init2(po, "ti.targets.elf.C64T", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.elf", "ti.targets.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.elf.C64T$$instance$static$init", null) ? 1 : 0);
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

    void C67P$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.elf.C67P", "ti.targets.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.elf.C67P.Module", "ti.targets.elf");
        vo.init2(po, "ti.targets.elf.C67P", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.elf", "ti.targets.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.elf.C67P$$instance$static$init", null) ? 1 : 0);
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

    void C64P_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.elf.C64P_big_endian", "ti.targets.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.elf.C64P_big_endian.Module", "ti.targets.elf");
        vo.init2(po, "ti.targets.elf.C64P_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.elf", "ti.targets.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.elf.C64P_big_endian$$instance$static$init", null) ? 1 : 0);
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

    void C674_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.elf.C674_big_endian", "ti.targets.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.elf.C674_big_endian.Module", "ti.targets.elf");
        vo.init2(po, "ti.targets.elf.C674_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.elf", "ti.targets.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.elf.C674_big_endian$$instance$static$init", null) ? 1 : 0);
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

    void C64T_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.elf.C64T_big_endian", "ti.targets.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.elf.C64T_big_endian.Module", "ti.targets.elf");
        vo.init2(po, "ti.targets.elf.C64T_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.elf", "ti.targets.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.elf.C64T_big_endian$$instance$static$init", null) ? 1 : 0);
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

    void TMS470$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.elf.TMS470", "ti.targets.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.elf.TMS470.Module", "ti.targets.elf");
        vo.init2(po, "ti.targets.elf.TMS470", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.elf", "ti.targets.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.elf.TMS470$$instance$static$init", null) ? 1 : 0);
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

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.elf.C64P", "ti.targets.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.elf.C674", "ti.targets.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.elf.C64T", "ti.targets.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.elf.C67P", "ti.targets.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.elf.C64P_big_endian", "ti.targets.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.elf.C674_big_endian", "ti.targets.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.elf.C64T_big_endian", "ti.targets.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.elf.TMS470", "ti.targets.elf"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.targets.elf.ITarget")).bless();
        ((Value.Obj)om.getv("ti.targets.elf.C64P")).bless();
        ((Value.Obj)om.getv("ti.targets.elf.C674")).bless();
        ((Value.Obj)om.getv("ti.targets.elf.C64T")).bless();
        ((Value.Obj)om.getv("ti.targets.elf.C67P")).bless();
        ((Value.Obj)om.getv("ti.targets.elf.C64P_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.elf.C674_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.elf.C64T_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.elf.TMS470")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.targets.elf")).add(pkgV);
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
        C64P$$OBJECTS();
        C674$$OBJECTS();
        C64T$$OBJECTS();
        C67P$$OBJECTS();
        C64P_big_endian$$OBJECTS();
        C674_big_endian$$OBJECTS();
        C64T_big_endian$$OBJECTS();
        TMS470$$OBJECTS();
        ITarget$$CONSTS();
        C64P$$CONSTS();
        C674$$CONSTS();
        C64T$$CONSTS();
        C67P$$CONSTS();
        C64P_big_endian$$CONSTS();
        C674_big_endian$$CONSTS();
        C64T_big_endian$$CONSTS();
        TMS470$$CONSTS();
        ITarget$$CREATES();
        C64P$$CREATES();
        C674$$CREATES();
        C64T$$CREATES();
        C67P$$CREATES();
        C64P_big_endian$$CREATES();
        C674_big_endian$$CREATES();
        C64T_big_endian$$CREATES();
        TMS470$$CREATES();
        ITarget$$FUNCTIONS();
        C64P$$FUNCTIONS();
        C674$$FUNCTIONS();
        C64T$$FUNCTIONS();
        C67P$$FUNCTIONS();
        C64P_big_endian$$FUNCTIONS();
        C674_big_endian$$FUNCTIONS();
        C64T_big_endian$$FUNCTIONS();
        TMS470$$FUNCTIONS();
        ITarget$$SIZES();
        C64P$$SIZES();
        C674$$SIZES();
        C64T$$SIZES();
        C67P$$SIZES();
        C64P_big_endian$$SIZES();
        C674_big_endian$$SIZES();
        C64T_big_endian$$SIZES();
        TMS470$$SIZES();
        ITarget$$TYPES();
        C64P$$TYPES();
        C674$$TYPES();
        C64T$$TYPES();
        C67P$$TYPES();
        C64P_big_endian$$TYPES();
        C674_big_endian$$TYPES();
        C64T_big_endian$$TYPES();
        TMS470$$TYPES();
        if (isROV) {
            ITarget$$ROV();
            C64P$$ROV();
            C674$$ROV();
            C64T$$ROV();
            C67P$$ROV();
            C64P_big_endian$$ROV();
            C674_big_endian$$ROV();
            C64T_big_endian$$ROV();
            TMS470$$ROV();
        }//isROV
        $$SINGLETONS();
        ITarget$$SINGLETONS();
        C64P$$SINGLETONS();
        C674$$SINGLETONS();
        C64T$$SINGLETONS();
        C67P$$SINGLETONS();
        C64P_big_endian$$SINGLETONS();
        C674_big_endian$$SINGLETONS();
        C64T_big_endian$$SINGLETONS();
        TMS470$$SINGLETONS();
        $$INITIALIZATION();
    }
}
