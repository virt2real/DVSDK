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

public class ti_sdo_fc_utils
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
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.fc.utils.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.fc.utils", new Value.Obj("ti.sdo.fc.utils", pkgP));
    }

    void SHM$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.utils.SHM.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.utils.SHM", new Value.Obj("ti.sdo.fc.utils.SHM", po));
        pkgV.bind("SHM", vo);
        // decls 
    }

    void RMM$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.utils.RMM.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.utils.RMM", new Value.Obj("ti.sdo.fc.utils.RMM", po));
        pkgV.bind("RMM", vo);
        // decls 
    }

    void SMGR$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.utils.SMGR.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.utils.SMGR", new Value.Obj("ti.sdo.fc.utils.SMGR", po));
        pkgV.bind("SMGR", vo);
        // decls 
    }

    void RMMP$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.utils.RMMP.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.utils.RMMP", new Value.Obj("ti.sdo.fc.utils.RMMP", po));
        pkgV.bind("RMMP", vo);
        // decls 
    }

    void SMGRMP$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.utils.SMGRMP.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.utils.SMGRMP", new Value.Obj("ti.sdo.fc.utils.SMGRMP", po));
        pkgV.bind("SMGRMP", vo);
        // decls 
    }

    void SHM$$CONSTS()
    {
        // module SHM
    }

    void RMM$$CONSTS()
    {
        // module RMM
    }

    void SMGR$$CONSTS()
    {
        // module SMGR
    }

    void RMMP$$CONSTS()
    {
        // module RMMP
    }

    void SMGRMP$$CONSTS()
    {
        // module SMGRMP
    }

    void SHM$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void RMM$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void SMGR$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void RMMP$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void SMGRMP$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void SHM$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void RMM$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void SMGR$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void RMMP$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void SMGRMP$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void SHM$$SIZES()
    {
    }

    void RMM$$SIZES()
    {
    }

    void SMGR$$SIZES()
    {
    }

    void RMMP$$SIZES()
    {
    }

    void SMGRMP$$SIZES()
    {
    }

    void SHM$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.fc.utils.SHM.Module", "ti.sdo.fc.utils");
        po.init("ti.sdo.fc.utils.SHM.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("debug", $$T_Bool, false, "wh");
                po.addFld("trace", $$T_Bool, false, "wh");
    }

    void RMM$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.fc.utils.RMM.Module", "ti.sdo.fc.utils");
        po.init("ti.sdo.fc.utils.RMM.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("debug", $$T_Bool, false, "wh");
                po.addFld("trace", $$T_Bool, false, "wh");
    }

    void SMGR$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.fc.utils.SMGR.Module", "ti.sdo.fc.utils");
        po.init("ti.sdo.fc.utils.SMGR.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("debug", $$T_Bool, false, "wh");
                po.addFld("trace", $$T_Bool, false, "wh");
    }

    void RMMP$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.fc.utils.RMMP.Module", "ti.sdo.fc.utils");
        po.init("ti.sdo.fc.utils.RMMP.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("debug", $$T_Bool, false, "wh");
                po.addFld("trace", $$T_Bool, false, "wh");
    }

    void SMGRMP$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.fc.utils.SMGRMP.Module", "ti.sdo.fc.utils");
        po.init("ti.sdo.fc.utils.SMGRMP.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("debug", $$T_Bool, false, "wh");
                po.addFld("trace", $$T_Bool, false, "wh");
    }

    void SHM$$ROV()
    {
    }

    void RMM$$ROV()
    {
    }

    void SMGR$$ROV()
    {
    }

    void RMMP$$ROV()
    {
    }

    void SMGRMP$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.fc.utils.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.fc.utils"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/utils/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.fc.utils"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.fc.utils"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.fc.utils"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.fc.utils"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.fc.utils"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.fc.utils"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.fc.utils", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.fc.utils");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.fc.utils.");
        pkgV.bind("$vers", Global.newArray("1, 0, 2"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.fc.utils'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/shm.a86U',\n");
            sb.append("'lib/debug/rmmp.a470MV',\n");
            sb.append("'lib/debug/smgrmp.a470MV',\n");
            sb.append("'lib/debug_trace/smgr.a64P',\n");
            sb.append("'lib/trace/rmm.av5T',\n");
            sb.append("'lib/debug_trace/smgr.a9t',\n");
            sb.append("'lib/release/smgrmp.av5T',\n");
            sb.append("'lib/debug_trace/rmmp.a470uC',\n");
            sb.append("'lib/trace/smgrmp.a470MV',\n");
            sb.append("'lib/trace/rmmp.a674',\n");
            sb.append("'lib/trace/rmm.a9t',\n");
            sb.append("'lib/debug/rmmp.a9t',\n");
            sb.append("'lib/trace/smgr.av5T',\n");
            sb.append("'lib/release/rmm.a64P',\n");
            sb.append("'lib/release/smgr.a9t',\n");
            sb.append("'lib/debug_trace/smgrmp.av5T',\n");
            sb.append("'lib/trace/rmm.a470uC',\n");
            sb.append("'lib/debug_trace/smgrmp.a470uC',\n");
            sb.append("'lib/debug_trace/shm.a86U',\n");
            sb.append("'lib/trace/rmmp.a86U',\n");
            sb.append("'lib/debug/rmm.av5T',\n");
            sb.append("'lib/debug/shm.a470uC',\n");
            sb.append("'lib/release/rmm.a470uC',\n");
            sb.append("'lib/debug_trace/rmm.a64P',\n");
            sb.append("'lib/debug_trace/rmmp.av5T',\n");
            sb.append("'lib/debug_trace/smgr.a470MV',\n");
            sb.append("'lib/trace/rmm.a674',\n");
            sb.append("'lib/debug/rmmp.a64P',\n");
            sb.append("'lib/release/shm.a86U',\n");
            sb.append("'lib/debug_trace/smgr.av5T',\n");
            sb.append("'lib/release/rmmp.a9t',\n");
            sb.append("'lib/trace/smgr.a674',\n");
            sb.append("'lib/release/smgrmp.a9t',\n");
            sb.append("'lib/trace/rmm.a86U',\n");
            sb.append("'lib/debug/smgr.a64P',\n");
            sb.append("'lib/trace/rmmp.a470uC',\n");
            sb.append("'lib/debug_trace/shm.a470MV',\n");
            sb.append("'lib/release/smgrmp.a86U',\n");
            sb.append("'lib/debug/rmm.a674',\n");
            sb.append("'lib/debug_trace/rmmp.a9t',\n");
            sb.append("'lib/release/rmmp.a64P',\n");
            sb.append("'lib/release/rmm.av5T',\n");
            sb.append("'lib/debug_trace/rmmp.a674',\n");
            sb.append("'lib/trace/smgr.a86U',\n");
            sb.append("'lib/trace/smgrmp.av5T',\n");
            sb.append("'lib/debug_trace/smgrmp.a86U',\n");
            sb.append("'lib/debug/rmm.a470uC',\n");
            sb.append("'lib/trace/smgrmp.a9t',\n");
            sb.append("'lib/debug/rmm.a86U',\n");
            sb.append("'lib/debug_trace/rmm.av5T',\n");
            sb.append("'lib/release/smgrmp.a470MV',\n");
            sb.append("'lib/release/smgr.a64P',\n");
            sb.append("'lib/trace/smgr.a470MV',\n");
            sb.append("'lib/debug_trace/smgr.a674',\n");
            sb.append("'lib/debug_trace/rmmp.a86U',\n");
            sb.append("'lib/debug/rmmp.av5T',\n");
            sb.append("'lib/release/smgr.a470uC',\n");
            sb.append("'lib/debug/rmmp.a470uC',\n");
            sb.append("'lib/debug/smgrmp.a470uC',\n");
            sb.append("'lib/debug_trace/smgr.a86U',\n");
            sb.append("'lib/release/rmm.a674',\n");
            sb.append("'lib/debug/smgr.av5T',\n");
            sb.append("'lib/trace/smgrmp.a470uC',\n");
            sb.append("'lib/debug_trace/rmm.a470MV',\n");
            sb.append("'lib/debug/smgrmp.av5T',\n");
            sb.append("'lib/release/rmmp.av5T',\n");
            sb.append("'lib/debug_trace/rmm.a674',\n");
            sb.append("'lib/trace/shm.a470MV',\n");
            sb.append("'lib/release/rmm.a86U',\n");
            sb.append("'lib/debug/rmmp.a674',\n");
            sb.append("'lib/debug/smgr.a470MV',\n");
            sb.append("'lib/release/shm.a470MV',\n");
            sb.append("'lib/trace/smgrmp.a86U',\n");
            sb.append("'lib/debug_trace/smgr.a470uC',\n");
            sb.append("'lib/debug/smgrmp.a9t',\n");
            sb.append("'lib/release/smgr.av5T',\n");
            sb.append("'lib/debug_trace/rmm.a86U',\n");
            sb.append("'lib/trace/shm.av5T',\n");
            sb.append("'lib/debug/smgr.a674',\n");
            sb.append("'lib/debug/rmmp.a86U',\n");
            sb.append("'lib/release/rmmp.a470MV',\n");
            sb.append("'lib/release/rmmp.a674',\n");
            sb.append("'lib/debug_trace/rmmp.a470MV',\n");
            sb.append("'lib/debug_trace/shm.a470uC',\n");
            sb.append("'lib/debug/smgr.a86U',\n");
            sb.append("'lib/debug/smgrmp.a86U',\n");
            sb.append("'lib/release/smgr.a674',\n");
            sb.append("'lib/release/rmmp.a86U',\n");
            sb.append("'lib/trace/rmmp.a64P',\n");
            sb.append("'lib/trace/rmm.a470MV',\n");
            sb.append("'lib/debug_trace/smgrmp.a470MV',\n");
            sb.append("'lib/trace/smgr.a9t',\n");
            sb.append("'lib/debug/shm.a470MV',\n");
            sb.append("'lib/release/rmm.a470MV',\n");
            sb.append("'lib/release/smgrmp.a470uC',\n");
            sb.append("'lib/trace/smgr.a470uC',\n");
            sb.append("'lib/release/smgr.a86U',\n");
            sb.append("'lib/debug/shm.av5T',\n");
            sb.append("'lib/trace/shm.a86U',\n");
            sb.append("'lib/trace/rmm.a64P',\n");
            sb.append("'lib/debug_trace/rmm.a470uC',\n");
            sb.append("'lib/trace/rmmp.a470MV',\n");
            sb.append("'lib/trace/smgr.a64P',\n");
            sb.append("'lib/debug_trace/shm.av5T',\n");
            sb.append("'lib/trace/rmmp.av5T',\n");
            sb.append("'lib/trace/shm.a470uC',\n");
            sb.append("'lib/debug/rmm.a9t',\n");
            sb.append("'lib/debug/smgr.a470uC',\n");
            sb.append("'lib/release/shm.a470uC',\n");
            sb.append("'lib/debug/rmm.a470MV',\n");
            sb.append("'lib/debug/rmm.a64P',\n");
            sb.append("'lib/debug/smgr.a9t',\n");
            sb.append("'lib/debug_trace/rmm.a9t',\n");
            sb.append("'lib/debug_trace/rmmp.a64P',\n");
            sb.append("'lib/trace/rmmp.a9t',\n");
            sb.append("'lib/release/shm.av5T',\n");
            sb.append("'lib/release/rmm.a9t',\n");
            sb.append("'lib/debug_trace/smgrmp.a9t',\n");
            sb.append("'lib/release/smgr.a470MV',\n");
            sb.append("'lib/release/rmmp.a470uC',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/shm.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/rmmp.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug/smgrmp.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug_trace/smgr.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/trace/rmm.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug_trace/smgr.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/release/smgrmp.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug_trace/rmmp.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/trace/smgrmp.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/trace/rmmp.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/trace/rmm.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/debug/rmmp.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/trace/smgr.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/rmm.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/smgr.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/debug_trace/smgrmp.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/trace/rmm.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug_trace/smgrmp.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug_trace/shm.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/trace/rmmp.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/rmm.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/shm.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/rmm.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug_trace/rmm.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug_trace/rmmp.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug_trace/smgr.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/trace/rmm.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/rmmp.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/shm.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug_trace/smgr.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/rmmp.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/trace/smgr.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/smgrmp.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/trace/rmm.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/smgr.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/trace/rmmp.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug_trace/shm.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/release/smgrmp.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/rmm.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug_trace/rmmp.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/release/rmmp.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/rmm.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug_trace/rmmp.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/trace/smgr.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/trace/smgrmp.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug_trace/smgrmp.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/rmm.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/trace/smgrmp.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/debug/rmm.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug_trace/rmm.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/smgrmp.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/release/smgr.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/trace/smgr.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug_trace/smgr.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug_trace/rmmp.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/rmmp.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/smgr.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/rmmp.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/smgrmp.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug_trace/smgr.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/rmm.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/smgr.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/trace/smgrmp.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug_trace/rmm.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug/smgrmp.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/rmmp.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug_trace/rmm.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/trace/shm.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/release/rmm.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/rmmp.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/smgr.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/release/shm.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/trace/smgrmp.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug_trace/smgr.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/smgrmp.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/release/smgr.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug_trace/rmm.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/trace/shm.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/smgr.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/rmmp.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/rmmp.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/release/rmmp.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug_trace/rmmp.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug_trace/shm.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/smgr.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/smgrmp.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/smgr.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/rmmp.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/trace/rmmp.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/trace/rmm.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug_trace/smgrmp.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/trace/smgr.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/debug/shm.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/release/rmm.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/release/smgrmp.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/trace/smgr.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/smgr.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/shm.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/trace/shm.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/trace/rmm.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug_trace/rmm.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/trace/rmmp.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/trace/smgr.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug_trace/shm.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/trace/rmmp.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/trace/shm.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/rmm.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/debug/smgr.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/shm.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/rmm.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug/rmm.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/smgr.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/debug_trace/rmm.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/debug_trace/rmmp.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/trace/rmmp.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/release/shm.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/rmm.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/debug_trace/smgrmp.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/release/smgr.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/release/rmmp.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/debug/shm.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmmp.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug/smgrmp.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/smgr.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmm.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/smgr.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/release/smgrmp.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmmp.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/trace/smgrmp.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmmp.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmm.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmmp.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/trace/smgr.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/rmm.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/smgr.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/smgrmp.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmm.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/smgrmp.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/shm.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmmp.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmm.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/shm.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/rmm.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmm.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmmp.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/smgr.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmm.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmmp.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/shm.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/smgr.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/rmmp.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/trace/smgr.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/smgrmp.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmm.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/smgr.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmmp.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/shm.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/release/smgrmp.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmm.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmmp.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/release/rmmp.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/rmm.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmmp.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/trace/smgr.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/trace/smgrmp.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/smgrmp.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmm.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/trace/smgrmp.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmm.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmm.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/smgrmp.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/release/smgr.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/trace/smgr.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/smgr.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmmp.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmmp.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/smgr.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmmp.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/smgrmp.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/smgr.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/rmm.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/smgr.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/trace/smgrmp.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmm.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug/smgrmp.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/rmmp.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmm.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/trace/shm.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/release/rmm.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmmp.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/smgr.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/release/shm.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/trace/smgrmp.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/smgr.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/smgrmp.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/release/smgr.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmm.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/trace/shm.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/smgr.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmmp.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/rmmp.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/release/rmmp.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmmp.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/shm.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/smgr.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/smgrmp.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/smgr.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/rmmp.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmmp.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmm.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/smgrmp.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/trace/smgr.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/debug/shm.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/release/rmm.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/release/smgrmp.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/trace/smgr.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/smgr.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/shm.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/trace/shm.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmm.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmm.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmmp.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/trace/smgr.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/shm.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmmp.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/trace/shm.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmm.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/debug/smgr.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/shm.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmm.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug/rmm.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/smgr.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmm.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/rmmp.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/trace/rmmp.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/release/shm.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/rmm.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/smgrmp.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/release/smgr.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/release/rmmp.a470uC'].suffix = '470uC';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void SHM$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.utils.SHM", "ti.sdo.fc.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.utils.SHM.Module", "ti.sdo.fc.utils");
        vo.init2(po, "ti.sdo.fc.utils.SHM", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.fc.utils", "ti.sdo.fc.utils"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.utils")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.utils.SHM$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("SHM", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("SHM");
    }

    void RMM$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.utils.RMM", "ti.sdo.fc.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.utils.RMM.Module", "ti.sdo.fc.utils");
        vo.init2(po, "ti.sdo.fc.utils.RMM", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.fc.utils", "ti.sdo.fc.utils"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.utils")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.utils.RMM$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("RMM", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("RMM");
    }

    void SMGR$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.utils.SMGR", "ti.sdo.fc.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.utils.SMGR.Module", "ti.sdo.fc.utils");
        vo.init2(po, "ti.sdo.fc.utils.SMGR", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.fc.utils", "ti.sdo.fc.utils"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.utils")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.utils.SMGR$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("SMGR", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("SMGR");
    }

    void RMMP$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.utils.RMMP", "ti.sdo.fc.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.utils.RMMP.Module", "ti.sdo.fc.utils");
        vo.init2(po, "ti.sdo.fc.utils.RMMP", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.fc.utils", "ti.sdo.fc.utils"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.utils")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.utils.RMMP$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("RMMP", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("RMMP");
    }

    void SMGRMP$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.utils.SMGRMP", "ti.sdo.fc.utils");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.utils.SMGRMP.Module", "ti.sdo.fc.utils");
        vo.init2(po, "ti.sdo.fc.utils.SMGRMP", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.fc.utils", "ti.sdo.fc.utils"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.utils")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.utils.SMGRMP$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("SMGRMP", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("SMGRMP");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.utils.SHM", "ti.sdo.fc.utils"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.utils.RMM", "ti.sdo.fc.utils"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.utils.SMGR", "ti.sdo.fc.utils"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.utils.RMMP", "ti.sdo.fc.utils"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.utils.SMGRMP", "ti.sdo.fc.utils"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.fc.utils.SHM")).bless();
        ((Value.Obj)om.getv("ti.sdo.fc.utils.RMM")).bless();
        ((Value.Obj)om.getv("ti.sdo.fc.utils.SMGR")).bless();
        ((Value.Obj)om.getv("ti.sdo.fc.utils.RMMP")).bless();
        ((Value.Obj)om.getv("ti.sdo.fc.utils.SMGRMP")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.fc.utils")).add(pkgV);
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
        SHM$$OBJECTS();
        RMM$$OBJECTS();
        SMGR$$OBJECTS();
        RMMP$$OBJECTS();
        SMGRMP$$OBJECTS();
        SHM$$CONSTS();
        RMM$$CONSTS();
        SMGR$$CONSTS();
        RMMP$$CONSTS();
        SMGRMP$$CONSTS();
        SHM$$CREATES();
        RMM$$CREATES();
        SMGR$$CREATES();
        RMMP$$CREATES();
        SMGRMP$$CREATES();
        SHM$$FUNCTIONS();
        RMM$$FUNCTIONS();
        SMGR$$FUNCTIONS();
        RMMP$$FUNCTIONS();
        SMGRMP$$FUNCTIONS();
        SHM$$SIZES();
        RMM$$SIZES();
        SMGR$$SIZES();
        RMMP$$SIZES();
        SMGRMP$$SIZES();
        SHM$$TYPES();
        RMM$$TYPES();
        SMGR$$TYPES();
        RMMP$$TYPES();
        SMGRMP$$TYPES();
        if (isROV) {
            SHM$$ROV();
            RMM$$ROV();
            SMGR$$ROV();
            RMMP$$ROV();
            SMGRMP$$ROV();
        }//isROV
        $$SINGLETONS();
        SHM$$SINGLETONS();
        RMM$$SINGLETONS();
        SMGR$$SINGLETONS();
        RMMP$$SINGLETONS();
        SMGRMP$$SINGLETONS();
        $$INITIALIZATION();
    }
}
