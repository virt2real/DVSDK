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

public class ti_targets_arm_elf
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
        Global.callFxn("loadPackage", xdcO, "ti.targets.arm");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.targets.arm.elf.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.targets.arm.elf", new Value.Obj("ti.targets.arm.elf", pkgP));
    }

    void IArm$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.IArm.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.IArm", new Value.Obj("ti.targets.arm.elf.IArm", po));
        pkgV.bind("IArm", vo);
        // decls 
        om.bind("ti.targets.arm.elf.IArm.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IArm.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IArm.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IArm.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IArm.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IArm.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IArm.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IArm.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IArm.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IArm.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IArm.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IArm.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IArm.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void Arm7$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.Arm7.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.Arm7", new Value.Obj("ti.targets.arm.elf.Arm7", po));
        pkgV.bind("Arm7", vo);
        // decls 
        om.bind("ti.targets.arm.elf.Arm7.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void Arm7_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.Arm7_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.Arm7_big_endian", new Value.Obj("ti.targets.arm.elf.Arm7_big_endian", po));
        pkgV.bind("Arm7_big_endian", vo);
        // decls 
        om.bind("ti.targets.arm.elf.Arm7_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm7_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void Arm9$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.Arm9.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.Arm9", new Value.Obj("ti.targets.arm.elf.Arm9", po));
        pkgV.bind("Arm9", vo);
        // decls 
        om.bind("ti.targets.arm.elf.Arm9.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void Arm9t$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.Arm9t.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.Arm9t", new Value.Obj("ti.targets.arm.elf.Arm9t", po));
        pkgV.bind("Arm9t", vo);
        // decls 
        om.bind("ti.targets.arm.elf.Arm9t.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9t.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9t.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9t.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9t.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9t.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9t.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9t.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9t.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9t.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9t.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9t.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.Arm9t.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void IM3$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.IM3.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.IM3", new Value.Obj("ti.targets.arm.elf.IM3", po));
        pkgV.bind("IM3", vo);
        // decls 
        om.bind("ti.targets.arm.elf.IM3.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void M3$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.M3.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.M3", new Value.Obj("ti.targets.arm.elf.M3", po));
        pkgV.bind("M3", vo);
        // decls 
        om.bind("ti.targets.arm.elf.M3.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void IM3_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.IM3_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.IM3_big_endian", new Value.Obj("ti.targets.arm.elf.IM3_big_endian", po));
        pkgV.bind("IM3_big_endian", vo);
        // decls 
        om.bind("ti.targets.arm.elf.IM3_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IM3_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void M3_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.M3_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.M3_big_endian", new Value.Obj("ti.targets.arm.elf.M3_big_endian", po));
        pkgV.bind("M3_big_endian", vo);
        // decls 
        om.bind("ti.targets.arm.elf.M3_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.M3_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void IR4$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.IR4.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.IR4", new Value.Obj("ti.targets.arm.elf.IR4", po));
        pkgV.bind("IR4", vo);
        // decls 
        om.bind("ti.targets.arm.elf.IR4.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void R4$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.R4.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.R4", new Value.Obj("ti.targets.arm.elf.R4", po));
        pkgV.bind("R4", vo);
        // decls 
        om.bind("ti.targets.arm.elf.R4.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void IR4_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.IR4_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.IR4_big_endian", new Value.Obj("ti.targets.arm.elf.IR4_big_endian", po));
        pkgV.bind("IR4_big_endian", vo);
        // decls 
        om.bind("ti.targets.arm.elf.IR4_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.IR4_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void R4_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.R4_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.R4_big_endian", new Value.Obj("ti.targets.arm.elf.R4_big_endian", po));
        pkgV.bind("R4_big_endian", vo);
        // decls 
        om.bind("ti.targets.arm.elf.R4_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void R4t$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.R4t.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.R4t", new Value.Obj("ti.targets.arm.elf.R4t", po));
        pkgV.bind("R4t", vo);
        // decls 
        om.bind("ti.targets.arm.elf.R4t.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void R4t_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.R4t_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.R4t_big_endian", new Value.Obj("ti.targets.arm.elf.R4t_big_endian", po));
        pkgV.bind("R4t_big_endian", vo);
        // decls 
        om.bind("ti.targets.arm.elf.R4t_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4t_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void R4F$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.R4F.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.R4F", new Value.Obj("ti.targets.arm.elf.R4F", po));
        pkgV.bind("R4F", vo);
        // decls 
        om.bind("ti.targets.arm.elf.R4F.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void R4F_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.R4F_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.R4F_big_endian", new Value.Obj("ti.targets.arm.elf.R4F_big_endian", po));
        pkgV.bind("R4F_big_endian", vo);
        // decls 
        om.bind("ti.targets.arm.elf.R4F_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4F_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void R4Ft$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.R4Ft.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.R4Ft", new Value.Obj("ti.targets.arm.elf.R4Ft", po));
        pkgV.bind("R4Ft", vo);
        // decls 
        om.bind("ti.targets.arm.elf.R4Ft.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void R4Ft_big_endian$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.elf.R4Ft_big_endian.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.elf.R4Ft_big_endian", new Value.Obj("ti.targets.arm.elf.R4Ft_big_endian", po));
        pkgV.bind("R4Ft_big_endian", vo);
        // decls 
        om.bind("ti.targets.arm.elf.R4Ft_big_endian.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft_big_endian.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft_big_endian.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft_big_endian.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft_big_endian.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft_big_endian.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft_big_endian.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft_big_endian.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft_big_endian.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft_big_endian.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft_big_endian.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft_big_endian.Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        om.bind("ti.targets.arm.elf.R4Ft_big_endian.Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
    }

    void IArm$$CONSTS()
    {
        // interface IArm
    }

    void Arm7$$CONSTS()
    {
        // module Arm7
    }

    void Arm7_big_endian$$CONSTS()
    {
        // module Arm7_big_endian
    }

    void Arm9$$CONSTS()
    {
        // module Arm9
    }

    void Arm9t$$CONSTS()
    {
        // module Arm9t
    }

    void IM3$$CONSTS()
    {
        // interface IM3
    }

    void M3$$CONSTS()
    {
        // module M3
    }

    void IM3_big_endian$$CONSTS()
    {
        // interface IM3_big_endian
    }

    void M3_big_endian$$CONSTS()
    {
        // module M3_big_endian
    }

    void IR4$$CONSTS()
    {
        // interface IR4
    }

    void R4$$CONSTS()
    {
        // module R4
    }

    void IR4_big_endian$$CONSTS()
    {
        // interface IR4_big_endian
    }

    void R4_big_endian$$CONSTS()
    {
        // module R4_big_endian
    }

    void R4t$$CONSTS()
    {
        // module R4t
    }

    void R4t_big_endian$$CONSTS()
    {
        // module R4t_big_endian
    }

    void R4F$$CONSTS()
    {
        // module R4F
    }

    void R4F_big_endian$$CONSTS()
    {
        // module R4F_big_endian
    }

    void R4Ft$$CONSTS()
    {
        // module R4Ft
    }

    void R4Ft_big_endian$$CONSTS()
    {
        // module R4Ft_big_endian
    }

    void IArm$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Arm7$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Arm7_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Arm9$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Arm9t$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IM3$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void M3$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IM3_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void M3_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IR4$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void R4$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IR4_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void R4_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void R4t$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void R4t_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void R4F$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void R4F_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void R4Ft$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void R4Ft_big_endian$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IArm$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Arm7$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Arm7_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Arm9$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Arm9t$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IM3$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void M3$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IM3_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void M3_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IR4$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void R4$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IR4_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void R4_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void R4t$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void R4t_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void R4F$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void R4F_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void R4Ft$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void R4Ft_big_endian$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IArm$$SIZES()
    {
    }

    void Arm7$$SIZES()
    {
    }

    void Arm7_big_endian$$SIZES()
    {
    }

    void Arm9$$SIZES()
    {
    }

    void Arm9t$$SIZES()
    {
    }

    void IM3$$SIZES()
    {
    }

    void M3$$SIZES()
    {
    }

    void IM3_big_endian$$SIZES()
    {
    }

    void M3_big_endian$$SIZES()
    {
    }

    void IR4$$SIZES()
    {
    }

    void R4$$SIZES()
    {
    }

    void IR4_big_endian$$SIZES()
    {
    }

    void R4_big_endian$$SIZES()
    {
    }

    void R4t$$SIZES()
    {
    }

    void R4t_big_endian$$SIZES()
    {
    }

    void R4F$$SIZES()
    {
    }

    void R4F_big_endian$$SIZES()
    {
    }

    void R4Ft$$SIZES()
    {
    }

    void R4Ft_big_endian$$SIZES()
    {
    }

    void IArm$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/arm/elf/IArm.xs");
        om.bind("ti.targets.arm.elf.IArm$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.IArm.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.IArm.Module", om.findStrict("ti.targets.ITarget.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("stdInclude", $$T_Str, "ti/targets/arm/elf/std.h", "wh");
                po.addFld("platform", $$T_Str, "ti.platforms.sim470xx", "wh");
                po.addFld("includeOpts", $$T_Str, "-I$(rootDir)/include/rts -I$(rootDir)/include ", "wh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("shortEnums", true), "rh");
                po.addFld("ar", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "ar470", "opts", "rq"), "rh");
                po.addFld("vers", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470", "opts", "-version"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "lnk470", "opts", ""), "rh");
                po.addFld("ccOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"), Global.newObject("prefix", "-qq -pdsw225", "suffix", ""), "wh");
                po.addFld("ccConfigOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"), Global.newObject("prefix", "$(ccOpts.prefix) -ms", "suffix", "$(ccOpts.suffix)"), "wh");
                po.addFld("asmOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"), Global.newObject("prefix", "-qq", "suffix", ""), "wh");
                po.addFld("lnkOpts", (Proto)om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"), Global.newObject("prefix", "-w -q -u _c_int00", "suffix", "-c -m $(XDCCFGDIR)/$@.map "), "wh");
                po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "--symdebug:dwarf", "defs", "-D_DEBUG_=1"))}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", "-O2"))}), Global.newArray(new Object[]{"profile", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"coverage", Global.newObject("compileOpts", Global.newObject("copts", "--gen_profile_info"))}), Global.newArray(new Object[]{"whole_program", Global.newObject("compileOpts", Global.newObject("copts", "-oe -O2 -ms"))}), Global.newArray(new Object[]{"whole_program_debug", Global.newObject("compileOpts", Global.newObject("copts", "-oe --symdebug:dwarf -ms"))})}), "wh");
                po.addFld("sectMap", new Proto.Map($$T_Str), Global.newArray(new Object[]{Global.newArray(new Object[]{".text", "code"}), Global.newArray(new Object[]{".stack", "stack"}), Global.newArray(new Object[]{".bss", "data"}), Global.newArray(new Object[]{".cinit", "data"}), Global.newArray(new Object[]{".pinit", "data"}), Global.newArray(new Object[]{".const", "data"}), Global.newArray(new Object[]{".data", "data"}), Global.newArray(new Object[]{".rodata", "data"}), Global.newArray(new Object[]{".neardata", "data"}), Global.newArray(new Object[]{".fardata", "data"}), Global.newArray(new Object[]{".switch", "data"}), Global.newArray(new Object[]{".sysmem", "data"}), Global.newArray(new Object[]{".far", "data"}), Global.newArray(new Object[]{".args", "data"}), Global.newArray(new Object[]{".cio", "data"})}), "rh");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFld("stdTypes", (Proto)om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"), Global.newObject("t_IArg", Global.newObject("size", 4L, "align", 4L), "t_Char", Global.newObject("size", 1L, "align", 1L), "t_Double", Global.newObject("size", 8L, "align", 4L), "t_Float", Global.newObject("size", 4L, "align", 4L), "t_Fxn", Global.newObject("size", 4L, "align", 4L), "t_Int", Global.newObject("size", 4L, "align", 4L), "t_Int8", Global.newObject("size", 1L, "align", 1L), "t_Int16", Global.newObject("size", 2L, "align", 2L), "t_Int32", Global.newObject("size", 4L, "align", 4L), "t_Int64", Global.newObject("size", 8L, "align", 4L), "t_Long", Global.newObject("size", 4L, "align", 4L), "t_LDouble", Global.newObject("size", 8L, "align", 4L), "t_LLong", Global.newObject("size", 8L, "align", 4L), "t_Ptr", Global.newObject("size", 4L, "align", 4L), "t_Short", Global.newObject("size", 2L, "align", 2L)), "rh");
                po.addFld("binaryParser", $$T_Str, "ti.targets.omf.elf.Elf32", "wh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.targets.arm.elf.IArm$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.targets.arm.elf.IArm$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.targets.arm.elf.IArm$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), fxn);
                fxn = Global.get(cap, "asmName");
                if (fxn != null) po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), fxn);
    }

    void Arm7$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.Arm7.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.Arm7.Module", om.findStrict("ti.targets.arm.elf.IArm.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "Arm7", "rh");
                po.addFld("suffix", $$T_Str, "e7", "rh");
                po.addFld("isa", $$T_Str, "v4T", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "little", "shortEnums", true), "rh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"470"}), "wh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", " -me -mv4 --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", " -me -mv4 --abi=eabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "lnk470", "opts", "--silicon_version=4 --strict_compatibility=on"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv4_A_le_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void Arm7_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.Arm7_big_endian.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.Arm7_big_endian.Module", om.findStrict("ti.targets.arm.elf.IArm.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "Arm7_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "e7e", "rh");
                po.addFld("isa", $$T_Str, "v4T", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "big", "shortEnums", true), "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.arm.elf"), om.find("ti.targets.arm.elf.Arm7"), "rh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"470e"}), "wh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "-mv4 --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "-mv4 --abi=eabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "lnk470", "opts", "--silicon_version=4 --strict_compatibility=on"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv4_A_be_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void Arm9$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.Arm9.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.Arm9.Module", om.findStrict("ti.targets.arm.elf.IArm.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "Arm9", "rh");
                po.addFld("suffix", $$T_Str, "e9", "rh");
                po.addFld("isa", $$T_Str, "v5T", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.arm.elf"), om.find("ti.targets.TMS470"), "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "little", "shortEnums", true), "rh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"7", "470", "9t"}), "wh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "-me -mv5e --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "-me -mv5e --abi=eabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "lnk470", "opts", "--silicon_version=5e --strict_compatibility=on"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv5_A_le_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void Arm9t$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.Arm9t.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.Arm9t.Module", om.findStrict("ti.targets.arm.elf.IArm.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "Arm9t", "rh");
                po.addFld("suffix", $$T_Str, "e9t", "rh");
                po.addFld("isa", $$T_Str, "v5T", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.arm.elf"), om.find("ti.targets.arm.Arm9"), "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "little", "codeModel", "thumb", "shortEnums", true), "rh");
                po.addFld("compatibleSuffixes", new Proto.Arr($$T_Str, false), Global.newArray(new Object[]{"9", "7", "470"}), "wh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "-me -mt -mv5e --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", " -me -mt -mv5e --abi=eabi"), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "lnk470", "opts", "--silicon_version=5e --strict_compatibility=on"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv5_T_le_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void IM3$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.IM3.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.IM3.Module", om.findStrict("ti.targets.arm.elf.IArm.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("isa", $$T_Str, "v7M", "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.arm.elf"), om.find("ti.targets.arm.Arm9"), "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.simDucati", "wh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "little", "codeModel", "thumb2", "shortEnums", true), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "lnk470", "opts", "--silicon_version=7M3 --strict_compatibility=on"), "rh");
    }

    void M3$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.M3.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.M3.Module", om.findStrict("ti.targets.arm.elf.IM3.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "M3", "rh");
                po.addFld("suffix", $$T_Str, "em3", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "--endian=little -mv7M3 --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "--endian=little -mv7M3 --abi=eabi"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv7M3_T_le_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void IM3_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.IM3_big_endian.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.IM3_big_endian.Module", om.findStrict("ti.targets.arm.elf.IArm.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("isa", $$T_Str, "v7M", "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.arm.elf"), om.find("ti.targets.arm.Arm9"), "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.simDucati", "wh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "big", "codeModel", "thumb2", "shortEnums", true), "rh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "lnk470", "opts", "--be32 --silicon_version=7M3 --strict_compatibility=on"), "rh");
    }

    void M3_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.M3_big_endian.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.M3_big_endian.Module", om.findStrict("ti.targets.arm.elf.IM3_big_endian.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "M3_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "em3e", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "--endian=big -mv7M3 --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "--endian=big -mv7M3 --abi=eabi"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv7M3_T_be_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void IR4$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.IR4.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.IR4.Module", om.findStrict("ti.targets.arm.elf.IArm.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("isa", $$T_Str, "v7R", "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.arm.elf"), om.find("ti.targets.arm.Arm9"), "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.evmTMS570", "wh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "lnk470", "opts", "--silicon_version=7R4 --strict_compatibility=on"), "rh");
    }

    void R4$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.R4.Module", om.findStrict("ti.targets.arm.elf.IR4.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "R4", "rh");
                po.addFld("suffix", $$T_Str, "er4", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "little", "shortEnums", true), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "--endian=little -mv7R4 --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "--endian=little -mv7R4 --abi=eabi"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv7R4_A_le_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void IR4_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.IR4_big_endian.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.IR4_big_endian.Module", om.findStrict("ti.targets.arm.elf.IArm.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("isa", $$T_Str, "v7R", "rh");
                po.addFld("base", (Proto)om.findStrict("xdc.bld.ITarget.Module", "ti.targets.arm.elf"), om.find("ti.targets.arm.Arm9"), "rh");
                po.addFld("platform", $$T_Str, "ti.platforms.evmTMS570", "wh");
                po.addFld("lnk", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "lnk470", "opts", "--abi=eabi --be32 --silicon_version=7R4 --strict_compatibility=on"), "rh");
    }

    void R4_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4_big_endian.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.R4_big_endian.Module", om.findStrict("ti.targets.arm.elf.IR4_big_endian.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "R4_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "er4e", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "big", "shortEnums", true), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "--endian=big -mv7R4 --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "--endian=big -mv7R4 --abi=eabi"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv7R4_A_be_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void R4t$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4t.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.R4t.Module", om.findStrict("ti.targets.arm.elf.IR4.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "R4t", "rh");
                po.addFld("suffix", $$T_Str, "er4t", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "little", "codeModel", "thumb2", "shortEnums", true), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "-mt --endian=little -mv7R4 --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "-mt --endian=little -mv7R4 --abi=eabi"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv7R4_T_le_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void R4t_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4t_big_endian.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.R4t_big_endian.Module", om.findStrict("ti.targets.arm.elf.IR4_big_endian.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "R4t_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "er4te", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "big", "codeModel", "thumb2", "shortEnums", true), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "-mt --endian=big -mv7R4 --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "-mt --endian=big -mv7R4 --abi=eabi"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv7R4_T_be_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void R4F$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4F.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.R4F.Module", om.findStrict("ti.targets.arm.elf.IR4.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "R4F", "rh");
                po.addFld("suffix", $$T_Str, "er4f", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "little", "shortEnums", true), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "--float_support=vfpv3d16 --endian=little -mv7R4 --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "--float_support=vfpv3d16 --endian=little -mv7R4 --abi=eabi"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv7R4_A_le_v3D16_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void R4F_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4F_big_endian.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.R4F_big_endian.Module", om.findStrict("ti.targets.arm.elf.IR4_big_endian.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "R4F_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "er4fe", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "big", "shortEnums", true), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "--float_support=vfpv3d16 --endian=big -mv7R4 --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "--float_support=vfpv3d16 --endian=big -mv7R4 --abi=eabi"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv7R4_A_be_v3D16_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void R4Ft$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4Ft.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.R4Ft.Module", om.findStrict("ti.targets.arm.elf.IR4.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "R4Ft", "rh");
                po.addFld("suffix", $$T_Str, "er4ft", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "little", "codeModel", "thumb2", "shortEnums", true), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "-mt --float_support=vfpv3d16 --endian=little -mv7R4 --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "-mt --float_support=vfpv3d16 --endian=little -mv7R4 --abi=eabi"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv7R4_T_le_v3D16_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void R4Ft_big_endian$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4Ft_big_endian.Module", "ti.targets.arm.elf");
        po.init("ti.targets.arm.elf.R4Ft_big_endian.Module", om.findStrict("ti.targets.arm.elf.IR4_big_endian.Module", "ti.targets.arm.elf"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, "R4Ft_big_endian", "rh");
                po.addFld("suffix", $$T_Str, "er4fte", "rh");
                po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
                po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"), Global.newObject("endian", "big", "codeModel", "thumb2", "shortEnums", true), "rh");
                po.addFld("cc", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "-mt --float_support=vfpv3d16 --endian=big -mv7R4 --abi=eabi"), "rh");
                po.addFld("asm", (Proto)om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"), Global.newObject("cmd", "cl470 -c", "opts", "-mt --float_support=vfpv3d16 --endian=big -mv7R4 --abi=eabi"), "rh");
                po.addFld("linkLib", $$T_Str, "rtsv7R4_T_be_v3D16_eabi.lib", "wh");
                po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.elf"), $$UNDEF);
                po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.elf"), $$UNDEF);
    }

    void IArm$$ROV()
    {
    }

    void Arm7$$ROV()
    {
    }

    void Arm7_big_endian$$ROV()
    {
    }

    void Arm9$$ROV()
    {
    }

    void Arm9t$$ROV()
    {
    }

    void IM3$$ROV()
    {
    }

    void M3$$ROV()
    {
    }

    void IM3_big_endian$$ROV()
    {
    }

    void M3_big_endian$$ROV()
    {
    }

    void IR4$$ROV()
    {
    }

    void R4$$ROV()
    {
    }

    void IR4_big_endian$$ROV()
    {
    }

    void R4_big_endian$$ROV()
    {
    }

    void R4t$$ROV()
    {
    }

    void R4t_big_endian$$ROV()
    {
    }

    void R4F$$ROV()
    {
    }

    void R4F_big_endian$$ROV()
    {
    }

    void R4Ft$$ROV()
    {
    }

    void R4Ft_big_endian$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.targets.arm.elf.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.targets.arm.elf"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/arm/elf/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.targets.arm.elf"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.targets.arm.elf"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.targets.arm.elf"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.targets.arm.elf"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.targets.arm.elf"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.targets.arm.elf"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.targets.arm.elf", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.targets.arm.elf");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.targets.arm.elf.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.bld", Global.newArray(1, 0, 1)));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.targets.arm.elf'];\n");
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

    void IArm$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.IArm", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.IArm.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.IArm", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", om.findStrict("ti.targets.arm.elf.IArm$$capsule", "ti.targets.arm.elf"));
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IArm", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IArm");
        vo.seal(null);
    }

    void Arm7$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.Arm7", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.Arm7.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.Arm7", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.Arm7$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("Arm7", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Arm7");
    }

    void Arm7_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.Arm7_big_endian", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.Arm7_big_endian.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.Arm7_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.Arm7_big_endian$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("Arm7_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Arm7_big_endian");
    }

    void Arm9$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.Arm9", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.Arm9.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.Arm9", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.Arm9$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("Arm9", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Arm9");
    }

    void Arm9t$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.Arm9t", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.Arm9t.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.Arm9t", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.Arm9t$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("Arm9t", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Arm9t");
    }

    void IM3$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.IM3", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.IM3.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.IM3", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IM3", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IM3");
        vo.seal(null);
    }

    void M3$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.M3", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.M3.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.M3", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.M3$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("M3", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("M3");
    }

    void IM3_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.IM3_big_endian", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.IM3_big_endian.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.IM3_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IM3_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IM3_big_endian");
        vo.seal(null);
    }

    void M3_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.M3_big_endian", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.M3_big_endian.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.M3_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.M3_big_endian$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("M3_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("M3_big_endian");
    }

    void IR4$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.IR4", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.IR4.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.IR4", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IR4", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IR4");
        vo.seal(null);
    }

    void R4$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.R4", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.R4", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.R4$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("R4", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("R4");
    }

    void IR4_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.IR4_big_endian", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.IR4_big_endian.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.IR4_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IR4_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IR4_big_endian");
        vo.seal(null);
    }

    void R4_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.R4_big_endian", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4_big_endian.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.R4_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.R4_big_endian$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("R4_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("R4_big_endian");
    }

    void R4t$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.R4t", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4t.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.R4t", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.R4t$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("R4t", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("R4t");
    }

    void R4t_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.R4t_big_endian", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4t_big_endian.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.R4t_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.R4t_big_endian$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("R4t_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("R4t_big_endian");
    }

    void R4F$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.R4F", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4F.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.R4F", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.R4F$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("R4F", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("R4F");
    }

    void R4F_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.R4F_big_endian", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4F_big_endian.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.R4F_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.R4F_big_endian$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("R4F_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("R4F_big_endian");
    }

    void R4Ft$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.R4Ft", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4Ft.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.R4Ft", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.R4Ft$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("R4Ft", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("R4Ft");
    }

    void R4Ft_big_endian$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.elf.R4Ft_big_endian", "ti.targets.arm.elf");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.elf.R4Ft_big_endian.Module", "ti.targets.arm.elf");
        vo.init2(po, "ti.targets.arm.elf.R4Ft_big_endian", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.targets.arm.elf", "ti.targets.arm.elf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.elf"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.elf"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.elf"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.elf"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.elf"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.elf"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.elf"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.elf"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.elf"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.elf"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.elf"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.elf"));
        vo.bind("Command", om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Command", "ti.targets.arm.elf"));
        vo.bind("Options", om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        tdefs.add(om.findStrict("ti.targets.ITarget.Options", "ti.targets.arm.elf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.elf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.elf.R4Ft_big_endian$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("R4Ft_big_endian", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("R4Ft_big_endian");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.Arm7", "ti.targets.arm.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.Arm7_big_endian", "ti.targets.arm.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.Arm9", "ti.targets.arm.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.Arm9t", "ti.targets.arm.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.M3", "ti.targets.arm.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.M3_big_endian", "ti.targets.arm.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.R4", "ti.targets.arm.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.R4_big_endian", "ti.targets.arm.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.R4t", "ti.targets.arm.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.R4t_big_endian", "ti.targets.arm.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.R4F", "ti.targets.arm.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.R4F_big_endian", "ti.targets.arm.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.R4Ft", "ti.targets.arm.elf"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.elf.R4Ft_big_endian", "ti.targets.arm.elf"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.targets.arm.elf.IArm")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.Arm7")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.Arm7_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.Arm9")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.Arm9t")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.IM3")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.M3")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.IM3_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.M3_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.IR4")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.R4")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.IR4_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.R4_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.R4t")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.R4t_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.R4F")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.R4F_big_endian")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.R4Ft")).bless();
        ((Value.Obj)om.getv("ti.targets.arm.elf.R4Ft_big_endian")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.targets.arm.elf")).add(pkgV);
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
        IArm$$OBJECTS();
        Arm7$$OBJECTS();
        Arm7_big_endian$$OBJECTS();
        Arm9$$OBJECTS();
        Arm9t$$OBJECTS();
        IM3$$OBJECTS();
        M3$$OBJECTS();
        IM3_big_endian$$OBJECTS();
        M3_big_endian$$OBJECTS();
        IR4$$OBJECTS();
        R4$$OBJECTS();
        IR4_big_endian$$OBJECTS();
        R4_big_endian$$OBJECTS();
        R4t$$OBJECTS();
        R4t_big_endian$$OBJECTS();
        R4F$$OBJECTS();
        R4F_big_endian$$OBJECTS();
        R4Ft$$OBJECTS();
        R4Ft_big_endian$$OBJECTS();
        IArm$$CONSTS();
        Arm7$$CONSTS();
        Arm7_big_endian$$CONSTS();
        Arm9$$CONSTS();
        Arm9t$$CONSTS();
        IM3$$CONSTS();
        M3$$CONSTS();
        IM3_big_endian$$CONSTS();
        M3_big_endian$$CONSTS();
        IR4$$CONSTS();
        R4$$CONSTS();
        IR4_big_endian$$CONSTS();
        R4_big_endian$$CONSTS();
        R4t$$CONSTS();
        R4t_big_endian$$CONSTS();
        R4F$$CONSTS();
        R4F_big_endian$$CONSTS();
        R4Ft$$CONSTS();
        R4Ft_big_endian$$CONSTS();
        IArm$$CREATES();
        Arm7$$CREATES();
        Arm7_big_endian$$CREATES();
        Arm9$$CREATES();
        Arm9t$$CREATES();
        IM3$$CREATES();
        M3$$CREATES();
        IM3_big_endian$$CREATES();
        M3_big_endian$$CREATES();
        IR4$$CREATES();
        R4$$CREATES();
        IR4_big_endian$$CREATES();
        R4_big_endian$$CREATES();
        R4t$$CREATES();
        R4t_big_endian$$CREATES();
        R4F$$CREATES();
        R4F_big_endian$$CREATES();
        R4Ft$$CREATES();
        R4Ft_big_endian$$CREATES();
        IArm$$FUNCTIONS();
        Arm7$$FUNCTIONS();
        Arm7_big_endian$$FUNCTIONS();
        Arm9$$FUNCTIONS();
        Arm9t$$FUNCTIONS();
        IM3$$FUNCTIONS();
        M3$$FUNCTIONS();
        IM3_big_endian$$FUNCTIONS();
        M3_big_endian$$FUNCTIONS();
        IR4$$FUNCTIONS();
        R4$$FUNCTIONS();
        IR4_big_endian$$FUNCTIONS();
        R4_big_endian$$FUNCTIONS();
        R4t$$FUNCTIONS();
        R4t_big_endian$$FUNCTIONS();
        R4F$$FUNCTIONS();
        R4F_big_endian$$FUNCTIONS();
        R4Ft$$FUNCTIONS();
        R4Ft_big_endian$$FUNCTIONS();
        IArm$$SIZES();
        Arm7$$SIZES();
        Arm7_big_endian$$SIZES();
        Arm9$$SIZES();
        Arm9t$$SIZES();
        IM3$$SIZES();
        M3$$SIZES();
        IM3_big_endian$$SIZES();
        M3_big_endian$$SIZES();
        IR4$$SIZES();
        R4$$SIZES();
        IR4_big_endian$$SIZES();
        R4_big_endian$$SIZES();
        R4t$$SIZES();
        R4t_big_endian$$SIZES();
        R4F$$SIZES();
        R4F_big_endian$$SIZES();
        R4Ft$$SIZES();
        R4Ft_big_endian$$SIZES();
        IArm$$TYPES();
        Arm7$$TYPES();
        Arm7_big_endian$$TYPES();
        Arm9$$TYPES();
        Arm9t$$TYPES();
        IM3$$TYPES();
        M3$$TYPES();
        IM3_big_endian$$TYPES();
        M3_big_endian$$TYPES();
        IR4$$TYPES();
        R4$$TYPES();
        IR4_big_endian$$TYPES();
        R4_big_endian$$TYPES();
        R4t$$TYPES();
        R4t_big_endian$$TYPES();
        R4F$$TYPES();
        R4F_big_endian$$TYPES();
        R4Ft$$TYPES();
        R4Ft_big_endian$$TYPES();
        if (isROV) {
            IArm$$ROV();
            Arm7$$ROV();
            Arm7_big_endian$$ROV();
            Arm9$$ROV();
            Arm9t$$ROV();
            IM3$$ROV();
            M3$$ROV();
            IM3_big_endian$$ROV();
            M3_big_endian$$ROV();
            IR4$$ROV();
            R4$$ROV();
            IR4_big_endian$$ROV();
            R4_big_endian$$ROV();
            R4t$$ROV();
            R4t_big_endian$$ROV();
            R4F$$ROV();
            R4F_big_endian$$ROV();
            R4Ft$$ROV();
            R4Ft_big_endian$$ROV();
        }//isROV
        $$SINGLETONS();
        IArm$$SINGLETONS();
        Arm7$$SINGLETONS();
        Arm7_big_endian$$SINGLETONS();
        Arm9$$SINGLETONS();
        Arm9t$$SINGLETONS();
        IM3$$SINGLETONS();
        M3$$SINGLETONS();
        IM3_big_endian$$SINGLETONS();
        M3_big_endian$$SINGLETONS();
        IR4$$SINGLETONS();
        R4$$SINGLETONS();
        IR4_big_endian$$SINGLETONS();
        R4_big_endian$$SINGLETONS();
        R4t$$SINGLETONS();
        R4t_big_endian$$SINGLETONS();
        R4F$$SINGLETONS();
        R4F_big_endian$$SINGLETONS();
        R4Ft$$SINGLETONS();
        R4Ft_big_endian$$SINGLETONS();
        $$INITIALIZATION();
    }
}
