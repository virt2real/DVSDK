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

public class ti_sdo_fc_dman3
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.fc.dman3.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.fc.dman3", new Value.Obj("ti.sdo.fc.dman3", pkgP));
    }

    void DMAN3$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.fc.dman3.DMAN3.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.fc.dman3.DMAN3", new Value.Obj("ti.sdo.fc.dman3.DMAN3", po));
        pkgV.bind("DMAN3", vo);
        // decls 
    }

    void DMAN3$$CONSTS()
    {
        // module DMAN3
        om.bind("ti.sdo.fc.dman3.DMAN3.MAXGROUPS", 20L);
    }

    void DMAN3$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void DMAN3$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void DMAN3$$SIZES()
    {
    }

    void DMAN3$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.fc.dman3.DMAN3.Module", "ti.sdo.fc.dman3");
        po.init("ti.sdo.fc.dman3.DMAN3.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("MAXGROUPS", Proto.Elm.newCNum("(xdc_Int)"), 20L, "rh");
                po.addFld("customDmaLib", $$T_Bool, $$UNDEF, "wh");
                po.addFld("heapInternal", $$T_Str, "DMAN3_heapInternal_undefined", "wh");
                po.addFld("heapExternal", $$T_Str, "DMAN3_heapExternal_undefined", "wh");
                po.addFld("scratchAllocFxn", $$T_Str, null, "wh");
                po.addFld("scratchFreeFxn", $$T_Str, null, "wh");
                po.addFld("idma3Internal", $$T_Bool, true, "wh");
                po.addFld("cpu", $$T_Bool, false, "wh");
                po.addFld("useExternalRM", $$T_Bool, false, "wh");
                po.addFld("numQdmaChannels", Proto.Elm.newCNum("(xdc_UInt)"), 4L, "wh");
                po.addFld("qdmaPaRamBase", new Proto.Adr("xdc_Ptr", "Pv"), 0x01C04000L, "wh");
                po.addFld("maxPaRamEntries", Proto.Elm.newCNum("(xdc_UInt)"), 128L, "wh");
                po.addFld("maxQdmaChannels", Proto.Elm.newCNum("(xdc_UInt)"), 8L, "wh");
                po.addFld("maxTCs", Proto.Elm.newCNum("(xdc_UInt)"), 8L, "wh");
                po.addFld("paRamBaseIndex", Proto.Elm.newCNum("(xdc_UInt)"), 96L, "wh");
                po.addFld("numPaRamEntries", Proto.Elm.newCNum("(xdc_UInt)"), 32L, "wh");
                po.addFld("nullPaRamIndex", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "wh");
                po.addFld("qdmaChannels", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false), Global.newArray(new Object[]{0L, 1L, 2L, 3L}), "wh");
                po.addFld("tccAllocationMaskH", Proto.Elm.newCNum("(xdc_UInt)"), 0xffffffffL, "wh");
                po.addFld("tccAllocationMaskL", Proto.Elm.newCNum("(xdc_UInt)"), 0x00000000L, "wh");
                po.addFld("qdmaQueueMap", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false), Global.newArray(new Object[]{1L, 1L, 1L, 1L, 1L, 1L, 1L, 1L}), "wh");
                po.addFld("queueTCMap", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false), Global.newArray(new Object[]{0L, 1L, 2L, 3L, 4L, 5L, 6L, 7L}), "wh");
                po.addFld("queuePri", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false), Global.newArray(new Object[]{3L, 7L, 0L, 0L, 0L, 0L, 0L, 0L}), "wh");
                po.addFld("numTccGroup", new Proto.Arr(Proto.Elm.newCNum("(xdc_Int)"), false, xdc.services.intern.xsr.Enum.intValue(20L)), Global.newArray(new Object[]{0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L}), "wh");
                po.addFld("numPaRamGroup", new Proto.Arr(Proto.Elm.newCNum("(xdc_Int)"), false, xdc.services.intern.xsr.Enum.intValue(20L)), Global.newArray(new Object[]{0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L}), "wh");
                po.addFld("numQdmaGroup", new Proto.Arr(Proto.Elm.newCNum("(xdc_Int)"), false, xdc.services.intern.xsr.Enum.intValue(20L)), $$DEFAULT, "wh");
                po.addFld("debug", $$T_Bool, false, "wh");
                po.addFld("trace", $$T_Bool, false, "wh");
                po.addFld("ipcKeyBase", Proto.Elm.newCNum("(xdc_UInt)"), 0x4e414d44L, "wh");
                po.addFld("allowUnshared", $$T_Bool, true, "wh");
    }

    void DMAN3$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.fc.dman3.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.fc.dman3"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/fc/dman3/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.fc.dman3"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.fc.dman3"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.fc.dman3"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.fc.dman3"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.fc.dman3"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.fc.dman3"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.fc.dman3", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.fc.dman3");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.fc.dman3.");
        pkgV.bind("$vers", Global.newArray("1, 0, 4"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.fc.dman3'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/release/dman3Cfg.a470MV',\n");
            sb.append("'lib/debug/dman3.a470uC',\n");
            sb.append("'lib/debug/dman3Cfgcpu.a674',\n");
            sb.append("'lib/debug_trace/dman3RMCfg.a64P',\n");
            sb.append("'lib/debug_trace/dman3.av4TCE',\n");
            sb.append("'lib/release/dman3.av4TCE',\n");
            sb.append("'lib/debug_trace/dman3.a470MV',\n");
            sb.append("'lib/debug/dman3Cfgcpu.a86U',\n");
            sb.append("'lib/release/dman3.a470MV',\n");
            sb.append("'lib/release/dman3.a64P',\n");
            sb.append("'lib/release/dman3cpu.a674',\n");
            sb.append("'lib/release/dman3Cfg.a64P',\n");
            sb.append("'lib/debug_trace/dman3cpu.a64P',\n");
            sb.append("'lib/trace/dman3.a470uC',\n");
            sb.append("'lib/debug/dman3Cfg.a674',\n");
            sb.append("'lib/trace/dman3Cfg.a674',\n");
            sb.append("'lib/debug_trace/dman3.a674',\n");
            sb.append("'lib/debug/dman3RMCfg.a674',\n");
            sb.append("'lib/release/dman3cpu.a86U',\n");
            sb.append("'lib/trace/dman3cpu.a470MV',\n");
            sb.append("'lib/trace/dman3RM.a64P',\n");
            sb.append("'lib/trace/dman3.a64P',\n");
            sb.append("'lib/release/dman3cpu.a470uC',\n");
            sb.append("'lib/trace/dman3RMCfg.a674',\n");
            sb.append("'lib/debug/dman3cpu.a470MV',\n");
            sb.append("'lib/debug/dman3RM.a674',\n");
            sb.append("'lib/trace/dman3Cfgcpu.a674',\n");
            sb.append("'lib/trace/dman3Cfg.av4TCE',\n");
            sb.append("'lib/debug_trace/dman3cpu.a470MV',\n");
            sb.append("'lib/release/dman3Cfgcpu.a64P',\n");
            sb.append("'lib/debug_trace/dman3Cfgcpu.a64P',\n");
            sb.append("'lib/debug_trace/dman3RMCfg.a674',\n");
            sb.append("'lib/debug/dman3Cfg.av4TCE',\n");
            sb.append("'lib/trace/dman3Cfg.a470MV',\n");
            sb.append("'lib/trace/dman3Cfgcpu.a86U',\n");
            sb.append("'lib/release/dman3Cfg.a470uC',\n");
            sb.append("'lib/debug_trace/dman3Cfg.av4TCE',\n");
            sb.append("'lib/debug/dman3Cfg.a470MV',\n");
            sb.append("'lib/debug/dman3.a64P',\n");
            sb.append("'lib/debug_trace/dman3Cfg.a470MV',\n");
            sb.append("'lib/debug/dman3cpu.a64P',\n");
            sb.append("'lib/release/dman3.a674',\n");
            sb.append("'lib/debug_trace/dman3.a470uC',\n");
            sb.append("'lib/trace/dman3cpu.a64P',\n");
            sb.append("'lib/release/dman3.a470uC',\n");
            sb.append("'lib/release/dman3Cfg.a674',\n");
            sb.append("'lib/debug_trace/dman3cpu.a674',\n");
            sb.append("'lib/debug_trace/dman3Cfg.a64P',\n");
            sb.append("'lib/debug_trace/dman3RM.a64P',\n");
            sb.append("'lib/debug/dman3.av4TCE',\n");
            sb.append("'lib/release/dman3RM.a64P',\n");
            sb.append("'lib/release/dman3RMCfg.a64P',\n");
            sb.append("'lib/trace/dman3RM.a674',\n");
            sb.append("'lib/trace/dman3.a674',\n");
            sb.append("'lib/debug_trace/dman3cpu.a86U',\n");
            sb.append("'lib/debug/dman3.a470MV',\n");
            sb.append("'lib/trace/dman3cpu.a470uC',\n");
            sb.append("'lib/debug/dman3Cfgcpu.a64P',\n");
            sb.append("'lib/release/dman3Cfgcpu.a674',\n");
            sb.append("'lib/debug/dman3cpu.a470uC',\n");
            sb.append("'lib/debug_trace/dman3Cfgcpu.a674',\n");
            sb.append("'lib/debug_trace/dman3cpu.a470uC',\n");
            sb.append("'lib/release/dman3Cfgcpu.a86U',\n");
            sb.append("'lib/debug_trace/dman3Cfgcpu.a86U',\n");
            sb.append("'lib/trace/dman3Cfg.a470uC',\n");
            sb.append("'lib/trace/dman3.a470MV',\n");
            sb.append("'lib/debug/dman3.a674',\n");
            sb.append("'lib/release/dman3cpu.a64P',\n");
            sb.append("'lib/debug/dman3cpu.a674',\n");
            sb.append("'lib/debug/dman3Cfg.a470uC',\n");
            sb.append("'lib/trace/dman3.av4TCE',\n");
            sb.append("'lib/debug/dman3Cfg.a64P',\n");
            sb.append("'lib/trace/dman3cpu.a674',\n");
            sb.append("'lib/release/dman3cpu.a470MV',\n");
            sb.append("'lib/trace/dman3Cfg.a64P',\n");
            sb.append("'lib/debug_trace/dman3Cfg.a470uC',\n");
            sb.append("'lib/debug_trace/dman3.a64P',\n");
            sb.append("'lib/debug_trace/dman3Cfg.a674',\n");
            sb.append("'lib/debug/dman3RMCfg.a64P',\n");
            sb.append("'lib/debug_trace/dman3RM.a674',\n");
            sb.append("'lib/debug/dman3cpu.a86U',\n");
            sb.append("'lib/release/dman3RM.a674',\n");
            sb.append("'lib/release/dman3RMCfg.a674',\n");
            sb.append("'lib/trace/dman3cpu.a86U',\n");
            sb.append("'lib/trace/dman3RMCfg.a64P',\n");
            sb.append("'lib/release/dman3Cfg.av4TCE',\n");
            sb.append("'lib/debug/dman3RM.a64P',\n");
            sb.append("'lib/trace/dman3Cfgcpu.a64P',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/release/dman3Cfg.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug/dman3.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/dman3Cfgcpu.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug_trace/dman3RMCfg.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug_trace/dman3.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/release/dman3.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug_trace/dman3.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug/dman3Cfgcpu.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/dman3.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/release/dman3.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/dman3cpu.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/dman3Cfg.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug_trace/dman3cpu.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/trace/dman3.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/dman3Cfg.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/trace/dman3Cfg.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug_trace/dman3.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/dman3RMCfg.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/dman3cpu.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/trace/dman3cpu.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/trace/dman3RM.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/trace/dman3.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/dman3cpu.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/trace/dman3RMCfg.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/dman3cpu.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug/dman3RM.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/trace/dman3Cfgcpu.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/trace/dman3Cfg.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug_trace/dman3cpu.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/release/dman3Cfgcpu.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug_trace/dman3Cfgcpu.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug_trace/dman3RMCfg.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/dman3Cfg.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/trace/dman3Cfg.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/trace/dman3Cfgcpu.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/dman3Cfg.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug_trace/dman3Cfg.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/dman3Cfg.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug/dman3.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug_trace/dman3Cfg.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug/dman3cpu.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/dman3.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug_trace/dman3.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/trace/dman3cpu.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/dman3.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/dman3Cfg.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug_trace/dman3cpu.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug_trace/dman3Cfg.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug_trace/dman3RM.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/dman3.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/release/dman3RM.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/dman3RMCfg.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/trace/dman3RM.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/trace/dman3.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug_trace/dman3cpu.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug/dman3.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/trace/dman3cpu.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/dman3Cfgcpu.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/dman3Cfgcpu.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/dman3cpu.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug_trace/dman3Cfgcpu.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug_trace/dman3cpu.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/dman3Cfgcpu.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/debug_trace/dman3Cfgcpu.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/trace/dman3Cfg.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/trace/dman3.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/debug/dman3.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/dman3cpu.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug/dman3cpu.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/dman3Cfg.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/trace/dman3.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/dman3Cfg.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/trace/dman3cpu.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/dman3cpu.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/trace/dman3Cfg.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug_trace/dman3Cfg.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug_trace/dman3.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug_trace/dman3Cfg.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/dman3RMCfg.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/debug_trace/dman3RM.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/debug/dman3cpu.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/release/dman3RM.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/release/dman3RMCfg.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/trace/dman3cpu.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/trace/dman3RMCfg.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/release/dman3Cfg.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/dman3RM.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/trace/dman3Cfgcpu.a64P', {target: 'ti.targets.C64P'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/release/dman3Cfg.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3Cfgcpu.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3RMCfg.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3Cfgcpu.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3cpu.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3Cfg.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3cpu.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3Cfg.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3Cfg.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3RMCfg.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3cpu.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3cpu.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3RM.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3cpu.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3RMCfg.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3cpu.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3RM.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3Cfgcpu.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3Cfg.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3cpu.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3Cfgcpu.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3Cfgcpu.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3RMCfg.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3Cfg.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3Cfg.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3Cfgcpu.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3Cfg.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3Cfg.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3Cfg.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3Cfg.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3cpu.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3cpu.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3Cfg.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3cpu.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3Cfg.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3RM.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3RM.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3RMCfg.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3RM.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3cpu.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3cpu.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3Cfgcpu.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3Cfgcpu.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3cpu.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3Cfgcpu.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3cpu.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3Cfgcpu.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3Cfgcpu.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3Cfg.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3cpu.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3cpu.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3Cfg.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3Cfg.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3cpu.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3cpu.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3Cfg.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3Cfg.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3Cfg.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3RMCfg.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/debug_trace/dman3RM.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3cpu.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3RM.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3RMCfg.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3cpu.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3RMCfg.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/release/dman3Cfg.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/dman3RM.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/trace/dman3Cfgcpu.a64P'].suffix = '64P';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void DMAN3$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.fc.dman3.DMAN3", "ti.sdo.fc.dman3");
        po = (Proto.Obj)om.findStrict("ti.sdo.fc.dman3.DMAN3.Module", "ti.sdo.fc.dman3");
        vo.init2(po, "ti.sdo.fc.dman3.DMAN3", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.fc.dman3", "ti.sdo.fc.dman3"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.fc.dman3")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.fc.dman3.DMAN3$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./DMAN3.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./DMAN3.xdt");
        pkgV.bind("DMAN3", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("DMAN3");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.fc.dman3.DMAN3", "ti.sdo.fc.dman3"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.fc.dman3.DMAN3")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.fc.dman3")).add(pkgV);
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
        DMAN3$$OBJECTS();
        DMAN3$$CONSTS();
        DMAN3$$CREATES();
        DMAN3$$FUNCTIONS();
        DMAN3$$SIZES();
        DMAN3$$TYPES();
        if (isROV) {
            DMAN3$$ROV();
        }//isROV
        $$SINGLETONS();
        DMAN3$$SINGLETONS();
        $$INITIALIZATION();
    }
}
