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

public class ti_sdo_ce_ipc_dsplink
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
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.ipc.dsplink.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.ipc.dsplink", new Value.Obj("ti.sdo.ce.ipc.dsplink", pkgP));
    }

    void Ipc$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.ipc.dsplink.Ipc.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.ipc.dsplink.Ipc", new Value.Obj("ti.sdo.ce.ipc.dsplink.Ipc", po));
        pkgV.bind("Ipc", vo);
        // decls 
        om.bind("ti.sdo.ce.ipc.dsplink.Ipc.ArmDspLinkConfigMemTableEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", "ti.sdo.ce.ipc.dsplink"));
        om.bind("ti.sdo.ce.ipc.dsplink.Ipc.DspManagement", om.findStrict("ti.sdo.ce.ipc.IIpc.DspManagement", "ti.sdo.ce.ipc.dsplink"));
        om.bind("ti.sdo.ce.ipc.dsplink.Ipc.ArmDspLinkConfig", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc.dsplink"));
        om.bind("ti.sdo.ce.ipc.dsplink.Ipc.LinkConfigEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", "ti.sdo.ce.ipc.dsplink"));
    }

    void IDspLinkCfg$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.ipc.dsplink.IDspLinkCfg.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.ipc.dsplink.IDspLinkCfg", new Value.Obj("ti.sdo.ce.ipc.dsplink.IDspLinkCfg", po));
        pkgV.bind("IDspLinkCfg", vo);
        // decls 
    }

    void DspLinkCfg$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.ipc.dsplink.DspLinkCfg.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.ipc.dsplink.DspLinkCfg", new Value.Obj("ti.sdo.ce.ipc.dsplink.DspLinkCfg", po));
        pkgV.bind("DspLinkCfg", vo);
        // decls 
    }

    void Ipc$$CONSTS()
    {
        // module Ipc
    }

    void IDspLinkCfg$$CONSTS()
    {
        // interface IDspLinkCfg
    }

    void DspLinkCfg$$CONSTS()
    {
        // module DspLinkCfg
    }

    void Ipc$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IDspLinkCfg$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void DspLinkCfg$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Ipc$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IDspLinkCfg$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void DspLinkCfg$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Ipc$$SIZES()
    {
    }

    void IDspLinkCfg$$SIZES()
    {
    }

    void DspLinkCfg$$SIZES()
    {
    }

    void Ipc$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.dsplink.Ipc.Module", "ti.sdo.ce.ipc.dsplink");
        po.init("ti.sdo.ce.ipc.dsplink.Ipc.Module", om.findStrict("ti.sdo.ce.ipc.IIpc.Module", "ti.sdo.ce.ipc.dsplink"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("maxTimeout", Proto.Elm.newCNum("(xdc_UInt32)"), 0xffffffffL, "wh");
                po.addFld("dspLinkCfg", (Proto)om.findStrict("ti.sdo.ce.ipc.dsplink.IDspLinkCfg.Module", "ti.sdo.ce.ipc.dsplink"), $$UNDEF, "wh");
                po.addFld("armCommMsgSize", Proto.Elm.newCNum("(xdc_UInt32)"), Global.eval("4 * 1024"), "wh");
                po.addFld("armCommNumMsgs", Proto.Elm.newCNum("(xdc_UInt32)"), 64L, "wh");
                po.addFld("commLocateRetries", Proto.Elm.newCNum("(xdc_Int)"), 20L, "wh");
                po.addFld("useLinkArbiter", $$T_Bool, false, "wh");
                po.addFld("usePowerManagement", $$T_Bool, $$UNDEF, "wh");
                po.addFld("debug", $$T_Bool, false, "wh");
    }

    void IDspLinkCfg$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/ipc/dsplink/IDspLinkCfg.xs");
        om.bind("ti.sdo.ce.ipc.dsplink.IDspLinkCfg$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.dsplink.IDspLinkCfg.Module", "ti.sdo.ce.ipc.dsplink");
        po.init("ti.sdo.ce.ipc.dsplink.IDspLinkCfg.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("DEFAULT_ARMDSPLINKCONFIG", new Proto.Map((Proto)om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc.dsplink")), $$DEFAULT, "rh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.sdo.ce.ipc.dsplink.IDspLinkCfg$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.sdo.ce.ipc.dsplink.IDspLinkCfg$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.sdo.ce.ipc.dsplink.IDspLinkCfg$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void DspLinkCfg$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.dsplink.DspLinkCfg.Module", "ti.sdo.ce.ipc.dsplink");
        po.init("ti.sdo.ce.ipc.dsplink.DspLinkCfg.Module", om.findStrict("ti.sdo.ce.ipc.dsplink.IDspLinkCfg.Module", "ti.sdo.ce.ipc.dsplink"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("DEFAULT_ARMDSPLINKCONFIG", new Proto.Map((Proto)om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc.dsplink")), Global.newArray(new Object[]{Global.newArray(new Object[]{"TMS320CDM6446", Global.newObject("memTable", Global.newArray(new Object[]{Global.newArray(new Object[]{"DDRALGHEAP", Global.newObject("addr", 0x88000000L, "size", 0x07A00000L, "type", "other")}), Global.newArray(new Object[]{"DDR2", Global.newObject("addr", 0x8FA00000L, "size", 0x00400000L, "type", "main")}), Global.newArray(new Object[]{"DSPLINKMEM", Global.newObject("addr", 0x8FE00000L, "size", 0x00100000L, "type", "link")}), Global.newArray(new Object[]{"RESETCTRL", Global.newObject("addr", 0x8FF00000L, "size", 0x00000080L, "type", "reset")})}), "doPowerControl", false, "dspManagement", om.find("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp"))}), Global.newArray(new Object[]{"TMS320DM357", Global.newObject("memTable", Global.newArray(new Object[]{Global.newArray(new Object[]{"DDRALGHEAP", Global.newObject("addr", 0x88000000L, "size", 0x07A00000L, "type", "other")}), Global.newArray(new Object[]{"DDR2", Global.newObject("addr", 0x8FA00000L, "size", 0x00400000L, "type", "main")}), Global.newArray(new Object[]{"DSPLINKMEM", Global.newObject("addr", 0x8FE00000L, "size", 0x00100000L, "type", "link")}), Global.newArray(new Object[]{"RESETCTRL", Global.newObject("addr", 0x8FF00000L, "size", 0x00000080L, "type", "reset")})}), "doPowerControl", false, "dspManagement", om.find("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp"))}), Global.newArray(new Object[]{"TMS320CDM6467", Global.newObject("memTable", Global.newArray(new Object[]{Global.newArray(new Object[]{"DDRALGHEAP", Global.newObject("addr", 0x88000000L, "size", 0x07A00000L, "type", "other")}), Global.newArray(new Object[]{"DDR2", Global.newObject("addr", 0x8FA00000L, "size", 0x00400000L, "type", "main")}), Global.newArray(new Object[]{"DSPLINKMEM", Global.newObject("addr", 0x8FE00000L, "size", 0x00100000L, "type", "link")}), Global.newArray(new Object[]{"RESETCTRL", Global.newObject("addr", 0x8FF00000L, "size", 0x00000080L, "type", "reset")})}), "doPowerControl", false, "dspManagement", om.find("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp"))}), Global.newArray(new Object[]{"TMS320C3430", Global.newObject("memTable", Global.newArray(new Object[]{Global.newArray(new Object[]{"L4CORE", Global.newObject("addr", 0x48000000L, "size", 0x01000000L, "type", "other")}), Global.newArray(new Object[]{"L4PER", Global.newObject("addr", 0x49000000L, "size", 0x00100000L, "type", "other")}), Global.newArray(new Object[]{"CMEM", Global.newObject("addr", 0x85000000L, "size", 0x01000000L, "type", "other")}), Global.newArray(new Object[]{"DDRALGHEAP", Global.newObject("addr", 0x86000000L, "size", 0x01800000L, "type", "other")}), Global.newArray(new Object[]{"DDR2", Global.newObject("addr", 0x87800000L, "size", 0x00600000L, "type", "main")}), Global.newArray(new Object[]{"DSPLINKMEM", Global.newObject("addr", 0x87E00000L, "size", 0x00100000L, "type", "link")}), Global.newArray(new Object[]{"RESETCTRL", Global.newObject("addr", 0x87F00000L, "size", 0x00001000L, "type", "reset")})}), "doPowerControl", false, "dspManagement", om.find("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp"))}), Global.newArray(new Object[]{"OMAP3530", Global.newObject("memTable", Global.newArray(new Object[]{Global.newArray(new Object[]{"L4CORE", Global.newObject("addr", 0x48000000L, "size", 0x01000000L, "type", "other")}), Global.newArray(new Object[]{"L4PER", Global.newObject("addr", 0x49000000L, "size", 0x00100000L, "type", "other")}), Global.newArray(new Object[]{"CMEM", Global.newObject("addr", 0x85000000L, "size", 0x01000000L, "type", "other")}), Global.newArray(new Object[]{"DDRALGHEAP", Global.newObject("addr", 0x86000000L, "size", 0x01800000L, "type", "other")}), Global.newArray(new Object[]{"DDR2", Global.newObject("addr", 0x87800000L, "size", 0x00600000L, "type", "main")}), Global.newArray(new Object[]{"DSPLINKMEM", Global.newObject("addr", 0x87E00000L, "size", 0x00100000L, "type", "link")}), Global.newArray(new Object[]{"RESETCTRL", Global.newObject("addr", 0x87F00000L, "size", 0x00001000L, "type", "reset")})}), "doPowerControl", false, "dspManagement", om.find("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp"))}), Global.newArray(new Object[]{"OMAP2530", Global.newObject("memTable", Global.newArray(new Object[]{Global.newArray(new Object[]{"L4CORE", Global.newObject("addr", 0x48000000L, "size", 0x01000000L, "type", "other")}), Global.newArray(new Object[]{"L4WAKEUP", Global.newObject("addr", 0x49000000L, "size", 0x00800000L, "type", "other")}), Global.newArray(new Object[]{"CMEM", Global.newObject("addr", 0x82400000L, "size", 0x00800000L, "type", "other")}), Global.newArray(new Object[]{"DDR2", Global.newObject("addr", 0x82C00000L, "size", 0x00300000L, "type", "main")}), Global.newArray(new Object[]{"DSPLINKMEM", Global.newObject("addr", 0x82F00000L, "size", 0x000FF000L, "type", "link")}), Global.newArray(new Object[]{"RESETCTRL", Global.newObject("addr", 0x82FFF000L, "size", 0x00001000L, "type", "reset")}), Global.newArray(new Object[]{"DDRALGHEAP", Global.newObject("addr", 0x83000000L, "size", 0x01000000L, "type", "other")})}), "doPowerControl", false, "dspManagement", om.find("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp"))}), Global.newArray(new Object[]{"TMS320C2430", Global.newObject("memTable", Global.newArray(new Object[]{Global.newArray(new Object[]{"L4CORE", Global.newObject("addr", 0x48000000L, "size", 0x01000000L, "type", "other")}), Global.newArray(new Object[]{"L4WAKEUP", Global.newObject("addr", 0x49000000L, "size", 0x00800000L, "type", "other")}), Global.newArray(new Object[]{"CMEM", Global.newObject("addr", 0x85800000L, "size", 0x00800000L, "type", "other")}), Global.newArray(new Object[]{"DDRALGHEAP", Global.newObject("addr", 0x86000000L, "size", 0x01800000L, "type", "other")}), Global.newArray(new Object[]{"DDR2", Global.newObject("addr", 0x87800000L, "size", 0x00600000L, "type", "main")}), Global.newArray(new Object[]{"DSPLINKMEM", Global.newObject("addr", 0x87E00000L, "size", 0x00100000L, "type", "link")}), Global.newArray(new Object[]{"RESETCTRL", Global.newObject("addr", 0x87F00000L, "size", 0x00001000L, "type", "reset")})}), "doPowerControl", false, "dspManagement", om.find("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp"))}), Global.newArray(new Object[]{"OMAPL137", Global.newObject("memTable", Global.newArray(new Object[]{Global.newArray(new Object[]{"DDRALGHEAP", Global.newObject("addr", 0xC3000000L, "size", 0x01000000L, "type", "other")}), Global.newArray(new Object[]{"DDR2", Global.newObject("addr", 0xC2C00000L, "size", 0x00300000L, "type", "main")}), Global.newArray(new Object[]{"DSPLINKMEM", Global.newObject("addr", 0xC2F01000L, "size", 0x00100000L, "type", "link")}), Global.newArray(new Object[]{"RESETCTRL", Global.newObject("addr", 0xC2F00000L, "size", 0x00001000L, "type", "reset")})}), "doPowerControl", true, "dspManagement", om.find("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp"))}), Global.newArray(new Object[]{"OMAPL138", Global.newObject("memTable", Global.newArray(new Object[]{Global.newArray(new Object[]{"DDRALGHEAP", Global.newObject("addr", 0xC3000000L, "size", 0x01000000L, "type", "other")}), Global.newArray(new Object[]{"DDR2", Global.newObject("addr", 0xC2C00000L, "size", 0x00300000L, "type", "main")}), Global.newArray(new Object[]{"DSPLINKMEM", Global.newObject("addr", 0xC2F01000L, "size", 0x00100000L, "type", "link")}), Global.newArray(new Object[]{"RESETCTRL", Global.newObject("addr", 0xC2F00000L, "size", 0x00001000L, "type", "reset")})}), "doPowerControl", true, "dspManagement", om.find("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp"))})}), "rh");
    }

    void Ipc$$ROV()
    {
    }

    void IDspLinkCfg$$ROV()
    {
    }

    void DspLinkCfg$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.ipc.dsplink.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.ipc.dsplink"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/ipc/dsplink/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.ipc.dsplink"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.ipc.dsplink"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.ipc.dsplink"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.ipc.dsplink"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.ipc.dsplink"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.ipc.dsplink"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.ipc.dsplink", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.ipc.dsplink");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.ipc.dsplink.");
        pkgV.bind("$vers", Global.newArray("2, 0, 1"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.ipc.dsplink'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/release/ipc_dsplink_357.av5T',\n");
            sb.append("'lib/debug/ipc_dsplink_2530.av5T',\n");
            sb.append("'lib/debug/ipc_dsplink_138.av5T',\n");
            sb.append("'lib/release/ipc_dsplink_6446.a470uC',\n");
            sb.append("'lib/release/ipc_dsplink_3530.av4TCE',\n");
            sb.append("'lib/debug/ipc_dsplink_138.a470uC',\n");
            sb.append("'lib/debug/ipc_dsplink_137.av5T',\n");
            sb.append("'lib/release/ipc_dsplink_6467.a470uC',\n");
            sb.append("'lib/release/ipc_dsplink_137.a470uC',\n");
            sb.append("'lib/release/ipc_dsplink_3530.a470uC',\n");
            sb.append("'lib/debug/ipc_dsplink_357.av5T',\n");
            sb.append("'lib/debug/ipc_dsplink_6467.a470uC',\n");
            sb.append("'lib/release/ipc_dsplink_6446.av5T',\n");
            sb.append("'lib/release/ipc_dsplink_2530.a470uC',\n");
            sb.append("'lib/release/ipc_dsplink_357.a470uC',\n");
            sb.append("'lib/release/ipc_dsplink_2530.av5T',\n");
            sb.append("'lib/debug/ipc_dsplink_3530.av5T',\n");
            sb.append("'lib/release/ipc_dsplink_6446.av4TCE',\n");
            sb.append("'lib/debug/ipc_dsplink_2530.a470uC',\n");
            sb.append("'lib/release/ipc_dsplink_3530.av5T',\n");
            sb.append("'lib/debug/ipc_dsplink_6446.av4TCE',\n");
            sb.append("'lib/debug/ipc_dsplink_137.a470uC',\n");
            sb.append("'lib/release/ipc_dsplink_138.a470uC',\n");
            sb.append("'lib/release/ipc_dsplink_138.av5T',\n");
            sb.append("'lib/debug/ipc_dsplink_6446.a470uC',\n");
            sb.append("'lib/debug/ipc_dsplink_3530.av4TCE',\n");
            sb.append("'lib/debug/ipc_dsplink_357.a470uC',\n");
            sb.append("'lib/debug/ipc_dsplink_6467.av5T',\n");
            sb.append("'lib/release/ipc_dsplink_137.av5T',\n");
            sb.append("'lib/debug/ipc_dsplink_3530.a470uC',\n");
            sb.append("'lib/debug/ipc_dsplink_6446.av5T',\n");
            sb.append("'lib/release/ipc_dsplink_6467.av5T',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/release/ipc_dsplink_357.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/ipc_dsplink_2530.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/ipc_dsplink_138.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/ipc_dsplink_6446.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/ipc_dsplink_3530.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/ipc_dsplink_138.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/ipc_dsplink_137.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/ipc_dsplink_6467.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/ipc_dsplink_137.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/ipc_dsplink_3530.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/ipc_dsplink_357.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/ipc_dsplink_6467.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/ipc_dsplink_6446.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/ipc_dsplink_2530.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/ipc_dsplink_357.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/ipc_dsplink_2530.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/ipc_dsplink_3530.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/ipc_dsplink_6446.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/ipc_dsplink_2530.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/ipc_dsplink_3530.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/ipc_dsplink_6446.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/ipc_dsplink_137.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/ipc_dsplink_138.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/release/ipc_dsplink_138.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/ipc_dsplink_6446.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/ipc_dsplink_3530.av4TCE', {target: 'microsoft.targets.arm.WinCE'}],\n");
            sb.append("['lib/debug/ipc_dsplink_357.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/ipc_dsplink_6467.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/ipc_dsplink_137.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/debug/ipc_dsplink_3530.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/debug/ipc_dsplink_6446.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/release/ipc_dsplink_6467.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_357.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_2530.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_138.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_6446.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_3530.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_138.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_137.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_6467.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_137.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_3530.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_357.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_6467.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_6446.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_2530.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_357.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_2530.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_3530.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_6446.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_2530.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_3530.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_6446.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_137.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_138.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_138.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_6446.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_3530.av4TCE'].suffix = 'v4TCE';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_357.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_6467.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_137.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_3530.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/debug/ipc_dsplink_6446.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/release/ipc_dsplink_6467.av5T'].suffix = 'v5T';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Ipc$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.ipc.dsplink.Ipc", "ti.sdo.ce.ipc.dsplink");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.dsplink.Ipc.Module", "ti.sdo.ce.ipc.dsplink");
        vo.init2(po, "ti.sdo.ce.ipc.dsplink.Ipc", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.ipc.dsplink", "ti.sdo.ce.ipc.dsplink"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("ArmDspLinkConfigMemTableEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", "ti.sdo.ce.ipc.dsplink"));
        tdefs.add(om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", "ti.sdo.ce.ipc.dsplink"));
        vo.bind("DspManagement", om.findStrict("ti.sdo.ce.ipc.IIpc.DspManagement", "ti.sdo.ce.ipc.dsplink"));
        vo.bind("ArmDspLinkConfig", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc.dsplink"));
        tdefs.add(om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc.dsplink"));
        vo.bind("LinkConfigEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", "ti.sdo.ce.ipc.dsplink"));
        tdefs.add(om.findStrict("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", "ti.sdo.ce.ipc.dsplink"));
        vo.bind("BootAndLoadDsp", om.findStrict("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp", "ti.sdo.ce.ipc.dsplink"));
        vo.bind("BootDspAutonomously", om.findStrict("ti.sdo.ce.ipc.IIpc.BootDspAutonomously", "ti.sdo.ce.ipc.dsplink"));
        vo.bind("None", om.findStrict("ti.sdo.ce.ipc.IIpc.None", "ti.sdo.ce.ipc.dsplink"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.ipc.dsplink")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.ipc.dsplink.Ipc$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Ipc.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Ipc.xdt");
        pkgV.bind("Ipc", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Ipc");
    }

    void IDspLinkCfg$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.ipc.dsplink.IDspLinkCfg", "ti.sdo.ce.ipc.dsplink");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.dsplink.IDspLinkCfg.Module", "ti.sdo.ce.ipc.dsplink");
        vo.init2(po, "ti.sdo.ce.ipc.dsplink.IDspLinkCfg", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.ipc.dsplink.IDspLinkCfg$$capsule", "ti.sdo.ce.ipc.dsplink"));
        vo.bind("$package", om.findStrict("ti.sdo.ce.ipc.dsplink", "ti.sdo.ce.ipc.dsplink"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IDspLinkCfg", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IDspLinkCfg");
        vo.seal(null);
    }

    void DspLinkCfg$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.ipc.dsplink.DspLinkCfg", "ti.sdo.ce.ipc.dsplink");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.dsplink.DspLinkCfg.Module", "ti.sdo.ce.ipc.dsplink");
        vo.init2(po, "ti.sdo.ce.ipc.dsplink.DspLinkCfg", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.ipc.dsplink", "ti.sdo.ce.ipc.dsplink"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.ipc.dsplink")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.ipc.dsplink.DspLinkCfg$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("DspLinkCfg", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("DspLinkCfg");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.ipc.dsplink.Ipc", "ti.sdo.ce.ipc.dsplink"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.ipc.dsplink.DspLinkCfg", "ti.sdo.ce.ipc.dsplink"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.ipc.dsplink.Ipc")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.ipc.dsplink.IDspLinkCfg")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.ipc.dsplink.DspLinkCfg")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.ipc.dsplink")).add(pkgV);
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
        Ipc$$OBJECTS();
        IDspLinkCfg$$OBJECTS();
        DspLinkCfg$$OBJECTS();
        Ipc$$CONSTS();
        IDspLinkCfg$$CONSTS();
        DspLinkCfg$$CONSTS();
        Ipc$$CREATES();
        IDspLinkCfg$$CREATES();
        DspLinkCfg$$CREATES();
        Ipc$$FUNCTIONS();
        IDspLinkCfg$$FUNCTIONS();
        DspLinkCfg$$FUNCTIONS();
        Ipc$$SIZES();
        IDspLinkCfg$$SIZES();
        DspLinkCfg$$SIZES();
        Ipc$$TYPES();
        IDspLinkCfg$$TYPES();
        DspLinkCfg$$TYPES();
        if (isROV) {
            Ipc$$ROV();
            IDspLinkCfg$$ROV();
            DspLinkCfg$$ROV();
        }//isROV
        $$SINGLETONS();
        Ipc$$SINGLETONS();
        IDspLinkCfg$$SINGLETONS();
        DspLinkCfg$$SINGLETONS();
        $$INITIALIZATION();
    }
}
