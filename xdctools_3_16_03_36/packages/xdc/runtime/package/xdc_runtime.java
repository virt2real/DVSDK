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

public class xdc_runtime
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
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("xdc.runtime.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("xdc.runtime", new Value.Obj("xdc.runtime", pkgP));
    }

    void IModule$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.IModule.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.IModule", new Value.Obj("xdc.runtime.IModule", po));
        pkgV.bind("IModule", vo);
        // decls 
    }

    void Assert$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Assert.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Assert", new Value.Obj("xdc.runtime.Assert", po));
        pkgV.bind("Assert", vo);
        // decls 
        spo = (Proto.Obj)om.bind("xdc.runtime.Assert$$Desc", new Proto.Obj());
        om.bind("xdc.runtime.Assert.Desc", new Proto.Str(spo, false));
        om.bind("xdc.runtime.Assert$$Id", new Proto.Tel());
    }

    void Core$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Core.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Core", new Value.Obj("xdc.runtime.Core", po));
        pkgV.bind("Core", vo);
        // decls 
        spo = (Proto.Obj)om.bind("xdc.runtime.Core$$ObjDesc", new Proto.Obj());
        om.bind("xdc.runtime.Core.ObjDesc", new Proto.Str(spo, false));
    }

    void Defaults$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Defaults.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Defaults", new Value.Obj("xdc.runtime.Defaults", po));
        pkgV.bind("Defaults", vo);
        // decls 
    }

    void Diags$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Diags.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Diags", new Value.Obj("xdc.runtime.Diags", po));
        pkgV.bind("Diags", vo);
        // decls 
        om.bind("xdc.runtime.Diags.Mode", new Proto.Enm("xdc.runtime.Diags.Mode"));
        spo = (Proto.Obj)om.bind("xdc.runtime.Diags$$DictElem", new Proto.Obj());
        om.bind("xdc.runtime.Diags.DictElem", new Proto.Str(spo, false));
    }

    void Error$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Error.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Error", new Value.Obj("xdc.runtime.Error", po));
        pkgV.bind("Error", vo);
        // decls 
        om.bind("xdc.runtime.Error.Policy", new Proto.Enm("xdc.runtime.Error.Policy"));
        spo = (Proto.Obj)om.bind("xdc.runtime.Error$$Desc", new Proto.Obj());
        om.bind("xdc.runtime.Error.Desc", new Proto.Str(spo, false));
        om.bind("xdc.runtime.Error$$Id", new Proto.Tel());
        spo = (Proto.Obj)om.bind("xdc.runtime.Error$$Data", new Proto.Obj());
        om.bind("xdc.runtime.Error.Data", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Error$$Block", new Proto.Obj());
        om.bind("xdc.runtime.Error.Block", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Error$$Module_State", new Proto.Obj());
        om.bind("xdc.runtime.Error.Module_State", new Proto.Str(spo, false));
    }

    void Gate$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Gate.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Gate", new Value.Obj("xdc.runtime.Gate", po));
        pkgV.bind("Gate", vo);
        // decls 
        om.bind("xdc.runtime.Gate$$Ref", new Proto.Tel());
    }

    void IGateProvider$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.IGateProvider.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.IGateProvider", new Value.Obj("xdc.runtime.IGateProvider", po));
        pkgV.bind("IGateProvider", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.runtime.IGateProvider.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.runtime.IGateProvider$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.runtime.IGateProvider.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.IGateProvider$$Params", new Proto.Obj());
        om.bind("xdc.runtime.IGateProvider.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.IGateProvider$$Instance_State", new Proto.Obj());
        om.bind("xdc.runtime.IGateProvider.Instance_State", new Proto.Str(po, false));
        om.bind("xdc.runtime.IGateProvider.Handle", insP);
        if (isROV) {
            om.bind("xdc.runtime.IGateProvider.Object", om.findStrict("xdc.runtime.IGateProvider.Instance_State", "xdc.runtime"));
        }//isROV
    }

    void GateNull$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.GateNull.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.GateNull", new Value.Obj("xdc.runtime.GateNull", po));
        pkgV.bind("GateNull", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.runtime.GateNull.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.runtime.GateNull$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.runtime.GateNull.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.GateNull$$Params", new Proto.Obj());
        om.bind("xdc.runtime.GateNull.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.GateNull$$Instance_State", new Proto.Obj());
        om.bind("xdc.runtime.GateNull.Instance_State", new Proto.Str(po, false));
        om.bind("xdc.runtime.GateNull.Handle", insP);
        if (isROV) {
            om.bind("xdc.runtime.GateNull.Object", om.findStrict("xdc.runtime.GateNull.Instance_State", "xdc.runtime"));
        }//isROV
    }

    void Log$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Log.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Log", new Value.Obj("xdc.runtime.Log", po));
        pkgV.bind("Log", vo);
        // decls 
        spo = (Proto.Obj)om.bind("xdc.runtime.Log$$EventDesc", new Proto.Obj());
        om.bind("xdc.runtime.Log.EventDesc", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Log$$EventRec", new Proto.Obj());
        om.bind("xdc.runtime.Log.EventRec", new Proto.Str(spo, false));
        om.bind("xdc.runtime.Log$$Event", new Proto.Tel());
    }

    void ILogger$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.ILogger.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.ILogger", new Value.Obj("xdc.runtime.ILogger", po));
        pkgV.bind("ILogger", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.runtime.ILogger.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.runtime.ILogger$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.runtime.ILogger.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.ILogger$$Params", new Proto.Obj());
        om.bind("xdc.runtime.ILogger.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.ILogger$$Instance_State", new Proto.Obj());
        om.bind("xdc.runtime.ILogger.Instance_State", new Proto.Str(po, false));
        om.bind("xdc.runtime.ILogger.Handle", insP);
        if (isROV) {
            om.bind("xdc.runtime.ILogger.Object", om.findStrict("xdc.runtime.ILogger.Instance_State", "xdc.runtime"));
        }//isROV
    }

    void LoggerBuf$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.LoggerBuf.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.LoggerBuf", new Value.Obj("xdc.runtime.LoggerBuf", po));
        pkgV.bind("LoggerBuf", vo);
        // decls 
        om.bind("xdc.runtime.LoggerBuf.BufType", new Proto.Enm("xdc.runtime.LoggerBuf.BufType"));
        spo = (Proto.Obj)om.bind("xdc.runtime.LoggerBuf$$BasicView", new Proto.Obj());
        om.bind("xdc.runtime.LoggerBuf.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.LoggerBuf$$RecordView", new Proto.Obj());
        om.bind("xdc.runtime.LoggerBuf.RecordView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.LoggerBuf$$StopModeData", new Proto.Obj());
        om.bind("xdc.runtime.LoggerBuf.StopModeData", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.LoggerBuf$$Entry", new Proto.Obj());
        om.bind("xdc.runtime.LoggerBuf.Entry", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.LoggerBuf$$Instance_State", new Proto.Obj());
        om.bind("xdc.runtime.LoggerBuf.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("xdc.runtime.LoggerBuf.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.runtime.LoggerBuf$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.runtime.LoggerBuf.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.LoggerBuf$$Params", new Proto.Obj());
        om.bind("xdc.runtime.LoggerBuf.Params", new Proto.Str(po, false));
        om.bind("xdc.runtime.LoggerBuf.Handle", insP);
        if (isROV) {
            om.bind("xdc.runtime.LoggerBuf.Object", om.findStrict("xdc.runtime.LoggerBuf.Instance_State", "xdc.runtime"));
        }//isROV
    }

    void LoggerSys$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.LoggerSys.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.LoggerSys", new Value.Obj("xdc.runtime.LoggerSys", po));
        pkgV.bind("LoggerSys", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.runtime.LoggerSys.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.runtime.LoggerSys$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.runtime.LoggerSys.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.LoggerSys$$Params", new Proto.Obj());
        om.bind("xdc.runtime.LoggerSys.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.LoggerSys$$Instance_State", new Proto.Obj());
        om.bind("xdc.runtime.LoggerSys.Instance_State", new Proto.Str(po, false));
        om.bind("xdc.runtime.LoggerSys.Handle", insP);
        if (isROV) {
            om.bind("xdc.runtime.LoggerSys.Object", om.findStrict("xdc.runtime.LoggerSys.Instance_State", "xdc.runtime"));
        }//isROV
    }

    void Main$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Main.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Main", new Value.Obj("xdc.runtime.Main", po));
        pkgV.bind("Main", vo);
        // decls 
    }

    void Memory$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Memory.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Memory", new Value.Obj("xdc.runtime.Memory", po));
        pkgV.bind("Memory", vo);
        // decls 
        spo = (Proto.Obj)om.bind("xdc.runtime.Memory$$Stats", new Proto.Obj());
        om.bind("xdc.runtime.Memory.Stats", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Memory$$Module_View", new Proto.Obj());
        om.bind("xdc.runtime.Memory.Module_View", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Memory$$Module_State", new Proto.Obj());
        om.bind("xdc.runtime.Memory.Module_State", new Proto.Str(spo, false));
    }

    void IHeap$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.IHeap.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.IHeap", new Value.Obj("xdc.runtime.IHeap", po));
        pkgV.bind("IHeap", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.runtime.IHeap.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.runtime.IHeap$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.runtime.IHeap.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.IHeap$$Params", new Proto.Obj());
        om.bind("xdc.runtime.IHeap.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.IHeap$$Instance_State", new Proto.Obj());
        om.bind("xdc.runtime.IHeap.Instance_State", new Proto.Str(po, false));
        om.bind("xdc.runtime.IHeap.Handle", insP);
        if (isROV) {
            om.bind("xdc.runtime.IHeap.Object", om.findStrict("xdc.runtime.IHeap.Instance_State", "xdc.runtime"));
        }//isROV
    }

    void HeapMin$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.HeapMin.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.HeapMin", new Value.Obj("xdc.runtime.HeapMin", po));
        pkgV.bind("HeapMin", vo);
        // decls 
        spo = (Proto.Obj)om.bind("xdc.runtime.HeapMin$$Instance_View", new Proto.Obj());
        om.bind("xdc.runtime.HeapMin.Instance_View", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.HeapMin$$Instance_State", new Proto.Obj());
        om.bind("xdc.runtime.HeapMin.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("xdc.runtime.HeapMin.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.runtime.HeapMin$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.runtime.HeapMin.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.HeapMin$$Params", new Proto.Obj());
        om.bind("xdc.runtime.HeapMin.Params", new Proto.Str(po, false));
        om.bind("xdc.runtime.HeapMin.Handle", insP);
        if (isROV) {
            om.bind("xdc.runtime.HeapMin.Object", om.findStrict("xdc.runtime.HeapMin.Instance_State", "xdc.runtime"));
        }//isROV
    }

    void HeapStd$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.HeapStd.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.HeapStd", new Value.Obj("xdc.runtime.HeapStd", po));
        pkgV.bind("HeapStd", vo);
        // decls 
        spo = (Proto.Obj)om.bind("xdc.runtime.HeapStd$$Instance_View", new Proto.Obj());
        om.bind("xdc.runtime.HeapStd.Instance_View", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.HeapStd$$Module_State", new Proto.Obj());
        om.bind("xdc.runtime.HeapStd.Module_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.HeapStd$$Instance_State", new Proto.Obj());
        om.bind("xdc.runtime.HeapStd.Instance_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("xdc.runtime.HeapStd.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.runtime.HeapStd$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.runtime.HeapStd.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.HeapStd$$Params", new Proto.Obj());
        om.bind("xdc.runtime.HeapStd.Params", new Proto.Str(po, false));
        om.bind("xdc.runtime.HeapStd.Handle", insP);
        if (isROV) {
            om.bind("xdc.runtime.HeapStd.Object", om.findStrict("xdc.runtime.HeapStd.Instance_State", "xdc.runtime"));
        }//isROV
    }

    void Rta$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Rta.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Rta", new Value.Obj("xdc.runtime.Rta", po));
        pkgV.bind("Rta", vo);
        // decls 
        om.bind("xdc.runtime.Rta.Command", new Proto.Enm("xdc.runtime.Rta.Command"));
        spo = (Proto.Obj)om.bind("xdc.runtime.Rta$$CommandPacket", new Proto.Obj());
        om.bind("xdc.runtime.Rta.CommandPacket", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Rta$$ResponsePacket", new Proto.Obj());
        om.bind("xdc.runtime.Rta.ResponsePacket", new Proto.Str(spo, false));
    }

    void Startup$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Startup.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Startup", new Value.Obj("xdc.runtime.Startup", po));
        pkgV.bind("Startup", vo);
        // decls 
        spo = (Proto.Obj)om.bind("xdc.runtime.Startup$$Module_State", new Proto.Obj());
        om.bind("xdc.runtime.Startup.Module_State", new Proto.Str(spo, false));
    }

    void Reset$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Reset.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Reset", new Value.Obj("xdc.runtime.Reset", po));
        pkgV.bind("Reset", vo);
        // decls 
    }

    void System$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.System.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.System", new Value.Obj("xdc.runtime.System", po));
        pkgV.bind("System", vo);
        // decls 
        spo = (Proto.Obj)om.bind("xdc.runtime.System$$Module_View", new Proto.Obj());
        om.bind("xdc.runtime.System.Module_View", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.System$$ParseData", new Proto.Obj());
        om.bind("xdc.runtime.System.ParseData", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.System$$Module_State", new Proto.Obj());
        om.bind("xdc.runtime.System.Module_State", new Proto.Str(spo, false));
    }

    void ISystemSupport$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.ISystemSupport.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.ISystemSupport", new Value.Obj("xdc.runtime.ISystemSupport", po));
        pkgV.bind("ISystemSupport", vo);
        // decls 
    }

    void SysStd$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.SysStd.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.SysStd", new Value.Obj("xdc.runtime.SysStd", po));
        pkgV.bind("SysStd", vo);
        // decls 
    }

    void SysMin$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.SysMin.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.SysMin", new Value.Obj("xdc.runtime.SysMin", po));
        pkgV.bind("SysMin", vo);
        // decls 
        spo = (Proto.Obj)om.bind("xdc.runtime.SysMin$$ModuleView", new Proto.Obj());
        om.bind("xdc.runtime.SysMin.ModuleView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.SysMin$$BufferEntryView", new Proto.Obj());
        om.bind("xdc.runtime.SysMin.BufferEntryView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.SysMin$$Module_State", new Proto.Obj());
        om.bind("xdc.runtime.SysMin.Module_State", new Proto.Str(spo, false));
    }

    void Text$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Text.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Text", new Value.Obj("xdc.runtime.Text", po));
        pkgV.bind("Text", vo);
        // decls 
        spo = (Proto.Obj)om.bind("xdc.runtime.Text$$Module_View", new Proto.Obj());
        om.bind("xdc.runtime.Text.Module_View", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Text$$Node", new Proto.Obj());
        om.bind("xdc.runtime.Text.Node", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Text$$MatchVisState", new Proto.Obj());
        om.bind("xdc.runtime.Text.MatchVisState", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Text$$PrintVisState", new Proto.Obj());
        om.bind("xdc.runtime.Text.PrintVisState", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Text$$Module_State", new Proto.Obj());
        om.bind("xdc.runtime.Text.Module_State", new Proto.Str(spo, false));
    }

    void ITimestampClient$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.ITimestampClient.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.ITimestampClient", new Value.Obj("xdc.runtime.ITimestampClient", po));
        pkgV.bind("ITimestampClient", vo);
        // decls 
    }

    void Timestamp$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Timestamp.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Timestamp", new Value.Obj("xdc.runtime.Timestamp", po));
        pkgV.bind("Timestamp", vo);
        // decls 
    }

    void ITimestampProvider$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.ITimestampProvider.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.ITimestampProvider", new Value.Obj("xdc.runtime.ITimestampProvider", po));
        pkgV.bind("ITimestampProvider", vo);
        // decls 
    }

    void TimestampNull$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.TimestampNull.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.TimestampNull", new Value.Obj("xdc.runtime.TimestampNull", po));
        pkgV.bind("TimestampNull", vo);
        // decls 
    }

    void TimestampStd$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.TimestampStd.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.TimestampStd", new Value.Obj("xdc.runtime.TimestampStd", po));
        pkgV.bind("TimestampStd", vo);
        // decls 
    }

    void Types$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Types.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Types", new Value.Obj("xdc.runtime.Types", po));
        pkgV.bind("Types", vo);
        // decls 
        om.bind("xdc.runtime.Types.CreatePolicy", new Proto.Enm("xdc.runtime.Types.CreatePolicy"));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$Label", new Proto.Obj());
        om.bind("xdc.runtime.Types.Label", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$Site", new Proto.Obj());
        om.bind("xdc.runtime.Types.Site", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$Timestamp64", new Proto.Obj());
        om.bind("xdc.runtime.Types.Timestamp64", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$FreqHz", new Proto.Obj());
        om.bind("xdc.runtime.Types.FreqHz", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$Common$", new Proto.Obj());
        om.bind("xdc.runtime.Types.Common$", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$__struct__1", new Proto.Obj());
        om.bind("xdc.runtime.Types.__struct__1", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$__struct__2", new Proto.Obj());
        om.bind("xdc.runtime.Types.__struct__2", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$__struct__3", new Proto.Obj());
        om.bind("xdc.runtime.Types.__struct__3", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$RtaDecoderData", new Proto.Obj());
        om.bind("xdc.runtime.Types.RtaDecoderData", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$ViewInfo", new Proto.Obj());
        om.bind("xdc.runtime.Types.ViewInfo", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$Vec", new Proto.Obj());
        om.bind("xdc.runtime.Types.Vec", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$Link", new Proto.Obj());
        om.bind("xdc.runtime.Types.Link", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$ModHdr", new Proto.Obj());
        om.bind("xdc.runtime.Types.ModHdr", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$ModHdrS", new Proto.Obj());
        om.bind("xdc.runtime.Types.ModHdrS", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$InstHdr", new Proto.Obj());
        om.bind("xdc.runtime.Types.InstHdr", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$PrmsHdr", new Proto.Obj());
        om.bind("xdc.runtime.Types.PrmsHdr", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$Base", new Proto.Obj());
        om.bind("xdc.runtime.Types.Base", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$SysFxns", new Proto.Obj());
        om.bind("xdc.runtime.Types.SysFxns", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("xdc.runtime.Types$$SysFxns2", new Proto.Obj());
        om.bind("xdc.runtime.Types.SysFxns2", new Proto.Str(spo, false));
    }

    void IInstance$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.IInstance.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.IInstance", new Value.Obj("xdc.runtime.IInstance", po));
        pkgV.bind("IInstance", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.runtime.IInstance.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.runtime.IInstance$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.runtime.IInstance.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.IInstance$$Params", new Proto.Obj());
        om.bind("xdc.runtime.IInstance.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.IInstance$$Instance_State", new Proto.Obj());
        om.bind("xdc.runtime.IInstance.Instance_State", new Proto.Str(po, false));
        om.bind("xdc.runtime.IInstance.Handle", insP);
        if (isROV) {
            om.bind("xdc.runtime.IInstance.Object", om.findStrict("xdc.runtime.IInstance.Instance_State", "xdc.runtime"));
        }//isROV
    }

    void LoggerBuf_TimestampProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.LoggerBuf_TimestampProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.LoggerBuf_TimestampProxy", new Value.Obj("xdc.runtime.LoggerBuf_TimestampProxy", po));
        pkgV.bind("LoggerBuf_TimestampProxy", vo);
        // decls 
    }

    void LoggerBuf_Module_GateProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.LoggerBuf_Module_GateProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.LoggerBuf_Module_GateProxy", new Value.Obj("xdc.runtime.LoggerBuf_Module_GateProxy", po));
        pkgV.bind("LoggerBuf_Module_GateProxy", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.runtime.LoggerBuf_Module_GateProxy.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.runtime.LoggerBuf_Module_GateProxy$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.runtime.LoggerBuf_Module_GateProxy.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.LoggerBuf_Module_GateProxy$$Params", new Proto.Obj());
        om.bind("xdc.runtime.LoggerBuf_Module_GateProxy.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.LoggerBuf_Module_GateProxy$$Instance_State", new Proto.Obj());
        om.bind("xdc.runtime.LoggerBuf_Module_GateProxy.Instance_State", new Proto.Str(po, false));
        om.bind("xdc.runtime.LoggerBuf_Module_GateProxy.Handle", insP);
        if (isROV) {
            om.bind("xdc.runtime.LoggerBuf_Module_GateProxy.Object", om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Instance_State", "xdc.runtime"));
        }//isROV
    }

    void LoggerSys_TimestampProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.LoggerSys_TimestampProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.LoggerSys_TimestampProxy", new Value.Obj("xdc.runtime.LoggerSys_TimestampProxy", po));
        pkgV.bind("LoggerSys_TimestampProxy", vo);
        // decls 
    }

    void Main_Module_GateProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Main_Module_GateProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Main_Module_GateProxy", new Value.Obj("xdc.runtime.Main_Module_GateProxy", po));
        pkgV.bind("Main_Module_GateProxy", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.runtime.Main_Module_GateProxy.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.runtime.Main_Module_GateProxy$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.runtime.Main_Module_GateProxy.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.Main_Module_GateProxy$$Params", new Proto.Obj());
        om.bind("xdc.runtime.Main_Module_GateProxy.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.Main_Module_GateProxy$$Instance_State", new Proto.Obj());
        om.bind("xdc.runtime.Main_Module_GateProxy.Instance_State", new Proto.Str(po, false));
        om.bind("xdc.runtime.Main_Module_GateProxy.Handle", insP);
        if (isROV) {
            om.bind("xdc.runtime.Main_Module_GateProxy.Object", om.findStrict("xdc.runtime.Main_Module_GateProxy.Instance_State", "xdc.runtime"));
        }//isROV
    }

    void Memory_HeapProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Memory_HeapProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Memory_HeapProxy", new Value.Obj("xdc.runtime.Memory_HeapProxy", po));
        pkgV.bind("Memory_HeapProxy", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.runtime.Memory_HeapProxy.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.runtime.Memory_HeapProxy$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.runtime.Memory_HeapProxy.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.Memory_HeapProxy$$Params", new Proto.Obj());
        om.bind("xdc.runtime.Memory_HeapProxy.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.Memory_HeapProxy$$Instance_State", new Proto.Obj());
        om.bind("xdc.runtime.Memory_HeapProxy.Instance_State", new Proto.Str(po, false));
        om.bind("xdc.runtime.Memory_HeapProxy.Handle", insP);
        if (isROV) {
            om.bind("xdc.runtime.Memory_HeapProxy.Object", om.findStrict("xdc.runtime.Memory_HeapProxy.Instance_State", "xdc.runtime"));
        }//isROV
    }

    void System_SupportProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.System_SupportProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.System_SupportProxy", new Value.Obj("xdc.runtime.System_SupportProxy", po));
        pkgV.bind("System_SupportProxy", vo);
        // decls 
    }

    void System_Module_GateProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.System_Module_GateProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.System_Module_GateProxy", new Value.Obj("xdc.runtime.System_Module_GateProxy", po));
        pkgV.bind("System_Module_GateProxy", vo);
        // decls 
        // insts 
        Object insP = om.bind("xdc.runtime.System_Module_GateProxy.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("xdc.runtime.System_Module_GateProxy$$Object", new Proto.Obj());
        Object objP = om.bind("xdc.runtime.System_Module_GateProxy.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.System_Module_GateProxy$$Params", new Proto.Obj());
        om.bind("xdc.runtime.System_Module_GateProxy.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("xdc.runtime.System_Module_GateProxy$$Instance_State", new Proto.Obj());
        om.bind("xdc.runtime.System_Module_GateProxy.Instance_State", new Proto.Str(po, false));
        om.bind("xdc.runtime.System_Module_GateProxy.Handle", insP);
        if (isROV) {
            om.bind("xdc.runtime.System_Module_GateProxy.Object", om.findStrict("xdc.runtime.System_Module_GateProxy.Instance_State", "xdc.runtime"));
        }//isROV
    }

    void Timestamp_SupportProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("xdc.runtime.Timestamp_SupportProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("xdc.runtime.Timestamp_SupportProxy", new Value.Obj("xdc.runtime.Timestamp_SupportProxy", po));
        pkgV.bind("Timestamp_SupportProxy", vo);
        // decls 
    }

    void IModule$$CONSTS()
    {
        // interface IModule
    }

    void Assert$$CONSTS()
    {
        // module Assert
        om.bind("xdc.runtime.Assert.raise", new Extern("xdc_runtime_Assert_raise__I", "xdc_Void(*)(xdc_Bits16,xdc_String,xdc_Int,xdc_runtime_Assert_Id)", true, false, "xdc.runtime.Assert.raise"));
    }

    void Core$$CONSTS()
    {
        // module Core
        om.bind("xdc.runtime.Core.assignLabel", new Extern("xdc_runtime_Core_assignLabel__I", "xdc_Void(*)(xdc_runtime_Types_Label*,xdc_runtime_Types_CordAddr__*,xdc_Bool)", true, false, "xdc.runtime.Core.assignLabel"));
        om.bind("xdc.runtime.Core.assignParams", new Extern("xdc_runtime_Core_assignParams__I", "xdc_Void(*)(xdc_Ptr,xdc_Ptr,xdc_SizeT,xdc_SizeT)", true, false, "xdc.runtime.Core.assignParams"));
        om.bind("xdc.runtime.Core.createObject", new Extern("xdc_runtime_Core_createObject__I", "xdc_Ptr(*)(xdc_runtime_Core_ObjDesc*,xdc_Ptr,xdc_SizeT,xdc_Ptr,xdc_Ptr,xdc_SizeT,xdc_runtime_Error_Block*)", true, false, "xdc.runtime.Core.createObject"));
        om.bind("xdc.runtime.Core.deleteObject", new Extern("xdc_runtime_Core_deleteObject__I", "xdc_Void(*)(xdc_runtime_Core_ObjDesc*,xdc_Ptr,xdc_Fxn,xdc_Int,xdc_Bool)", true, false, "xdc.runtime.Core.deleteObject"));
    }

    void Defaults$$CONSTS()
    {
        // module Defaults
    }

    void Diags$$CONSTS()
    {
        // module Diags
        om.bind("xdc.runtime.Diags.ALWAYS_OFF", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), "xdc.runtime.Diags.ALWAYS_OFF", 0));
        om.bind("xdc.runtime.Diags.ALWAYS_ON", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), "xdc.runtime.Diags.ALWAYS_ON", 1));
        om.bind("xdc.runtime.Diags.RUNTIME_OFF", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), "xdc.runtime.Diags.RUNTIME_OFF", 2));
        om.bind("xdc.runtime.Diags.RUNTIME_ON", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), "xdc.runtime.Diags.RUNTIME_ON", 3));
        om.bind("xdc.runtime.Diags.ENTRY", 0x0001L);
        om.bind("xdc.runtime.Diags.EXIT", 0x0002L);
        om.bind("xdc.runtime.Diags.LIFECYCLE", 0x0004L);
        om.bind("xdc.runtime.Diags.INTERNAL", 0x0008L);
        om.bind("xdc.runtime.Diags.ASSERT", 0x0010L);
        om.bind("xdc.runtime.Diags.USER1", 0x0100L);
        om.bind("xdc.runtime.Diags.USER2", 0x0200L);
        om.bind("xdc.runtime.Diags.USER3", 0x0400L);
        om.bind("xdc.runtime.Diags.USER4", 0x0800L);
        om.bind("xdc.runtime.Diags.USER5", 0x1000L);
        om.bind("xdc.runtime.Diags.USER6", 0x2000L);
        om.bind("xdc.runtime.Diags.USER7", 0x4000L);
        om.bind("xdc.runtime.Diags.USER8", 0x8000L);
        om.bind("xdc.runtime.Diags.ALL", 0xFFFFL);
        om.bind("xdc.runtime.Diags.setMask", new Extern("xdc_runtime_Diags_setMask__E", "xdc_Void(*)(xdc_String)", true, false, "xdc.runtime.Diags.setMask"));
    }

    void Error$$CONSTS()
    {
        // module Error
        om.bind("xdc.runtime.Error.TERMINATE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Error.Policy", "xdc.runtime"), "xdc.runtime.Error.TERMINATE", 0));
        om.bind("xdc.runtime.Error.UNWIND", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Error.Policy", "xdc.runtime"), "xdc.runtime.Error.UNWIND", 1));
        om.bind("xdc.runtime.Error.NUMARGS", 2L);
        om.bind("xdc.runtime.Error.check", new Extern("xdc_runtime_Error_check__E", "xdc_Bool(*)(xdc_runtime_Error_Block*)", true, false, "xdc.runtime.Error.check"));
        om.bind("xdc.runtime.Error.getData", new Extern("xdc_runtime_Error_getData__E", "xdc_runtime_Error_Data*(*)(xdc_runtime_Error_Block*)", true, false, "xdc.runtime.Error.getData"));
        om.bind("xdc.runtime.Error.getCode", new Extern("xdc_runtime_Error_getCode__E", "xdc_UInt16(*)(xdc_runtime_Error_Block*)", true, false, "xdc.runtime.Error.getCode"));
        om.bind("xdc.runtime.Error.getId", new Extern("xdc_runtime_Error_getId__E", "xdc_runtime_Error_Id(*)(xdc_runtime_Error_Block*)", true, false, "xdc.runtime.Error.getId"));
        om.bind("xdc.runtime.Error.getMsg", new Extern("xdc_runtime_Error_getMsg__E", "xdc_String(*)(xdc_runtime_Error_Block*)", true, false, "xdc.runtime.Error.getMsg"));
        om.bind("xdc.runtime.Error.getSite", new Extern("xdc_runtime_Error_getSite__E", "xdc_runtime_Types_Site*(*)(xdc_runtime_Error_Block*)", true, false, "xdc.runtime.Error.getSite"));
        om.bind("xdc.runtime.Error.init", new Extern("xdc_runtime_Error_init__E", "xdc_Void(*)(xdc_runtime_Error_Block*)", true, false, "xdc.runtime.Error.init"));
        om.bind("xdc.runtime.Error.print", new Extern("xdc_runtime_Error_print__E", "xdc_Void(*)(xdc_runtime_Error_Block*)", true, false, "xdc.runtime.Error.print"));
        om.bind("xdc.runtime.Error.raiseX", new Extern("xdc_runtime_Error_raiseX__E", "xdc_Void(*)(xdc_runtime_Error_Block*,xdc_Bits16,xdc_String,xdc_Int,xdc_runtime_Error_Id,xdc_IArg,xdc_IArg)", true, false, "xdc.runtime.Error.raiseX"));
    }

    void Gate$$CONSTS()
    {
        // module Gate
        om.bind("xdc.runtime.Gate.enterSystem", new Extern("xdc_runtime_Gate_enterSystem__E", "xdc_IArg(*)(xdc_Void)", true, false, "xdc.runtime.Gate.enterSystem"));
        om.bind("xdc.runtime.Gate.leaveSystem", new Extern("xdc_runtime_Gate_leaveSystem__E", "xdc_Void(*)(xdc_IArg)", true, false, "xdc.runtime.Gate.leaveSystem"));
    }

    void IGateProvider$$CONSTS()
    {
        // interface IGateProvider
        om.bind("xdc.runtime.IGateProvider.Q_BLOCKING", 1L);
        om.bind("xdc.runtime.IGateProvider.Q_PREEMPTING", 2L);
    }

    void GateNull$$CONSTS()
    {
        // module GateNull
        om.bind("xdc.runtime.GateNull.query", new Extern("xdc_runtime_GateNull_query__E", "xdc_Bool(*)(xdc_Int)", true, false, "xdc.runtime.GateNull.query"));
    }

    void Log$$CONSTS()
    {
        // module Log
        om.bind("xdc.runtime.Log.NUMARGS", 8L);
        om.bind("xdc.runtime.Log.PRINTFID", 0L);
        om.bind("xdc.runtime.Log.doPrint", new Extern("xdc_runtime_Log_doPrint__E", "xdc_Void(*)(xdc_runtime_Log_EventRec*)", true, false, "xdc.runtime.Log.doPrint"));
    }

    void ILogger$$CONSTS()
    {
        // interface ILogger
    }

    void LoggerBuf$$CONSTS()
    {
        // module LoggerBuf
        om.bind("xdc.runtime.LoggerBuf.BufType_CIRCULAR", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.LoggerBuf.BufType", "xdc.runtime"), "xdc.runtime.LoggerBuf.BufType_CIRCULAR", 0));
        om.bind("xdc.runtime.LoggerBuf.BufType_FIXED", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.LoggerBuf.BufType", "xdc.runtime"), "xdc.runtime.LoggerBuf.BufType_FIXED", 1));
        om.bind("xdc.runtime.LoggerBuf.FULL", Global.eval("-1"));
        om.bind("xdc.runtime.LoggerBuf.WRAP", 0L);
        om.bind("xdc.runtime.LoggerBuf.NEXT", 1L);
        om.bind("xdc.runtime.LoggerBuf.flushAll", new Extern("xdc_runtime_LoggerBuf_flushAll__E", "xdc_Void(*)(xdc_Void)", true, false, "xdc.runtime.LoggerBuf.flushAll"));
        om.bind("xdc.runtime.LoggerBuf.flushAllInternal", new Extern("xdc_runtime_LoggerBuf_flushAllInternal__E", "xdc_Void(*)(xdc_Int)", true, false, "xdc.runtime.LoggerBuf.flushAllInternal"));
    }

    void LoggerSys$$CONSTS()
    {
        // module LoggerSys
    }

    void Main$$CONSTS()
    {
        // module Main
    }

    void Memory$$CONSTS()
    {
        // module Memory
        om.bind("xdc.runtime.Memory.Q_BLOCKING", 1L);
        om.bind("xdc.runtime.Memory.alloc", new Extern("xdc_runtime_Memory_alloc__E", "xdc_Ptr(*)(xdc_runtime_IHeap_Handle,xdc_SizeT,xdc_SizeT,xdc_runtime_Error_Block*)", true, false, "xdc.runtime.Memory.alloc"));
        om.bind("xdc.runtime.Memory.calloc", new Extern("xdc_runtime_Memory_calloc__E", "xdc_Ptr(*)(xdc_runtime_IHeap_Handle,xdc_SizeT,xdc_SizeT,xdc_runtime_Error_Block*)", true, false, "xdc.runtime.Memory.calloc"));
        om.bind("xdc.runtime.Memory.free", new Extern("xdc_runtime_Memory_free__E", "xdc_Void(*)(xdc_runtime_IHeap_Handle,xdc_Ptr,xdc_SizeT)", true, false, "xdc.runtime.Memory.free"));
        om.bind("xdc.runtime.Memory.getStats", new Extern("xdc_runtime_Memory_getStats__E", "xdc_Void(*)(xdc_runtime_IHeap_Handle,xdc_runtime_Memory_Stats*)", true, false, "xdc.runtime.Memory.getStats"));
        om.bind("xdc.runtime.Memory.query", new Extern("xdc_runtime_Memory_query__E", "xdc_Bool(*)(xdc_runtime_IHeap_Handle,xdc_Int)", true, false, "xdc.runtime.Memory.query"));
        om.bind("xdc.runtime.Memory.getMaxDefaultTypeAlign", new Extern("xdc_runtime_Memory_getMaxDefaultTypeAlign__E", "xdc_SizeT(*)(xdc_Void)", true, false, "xdc.runtime.Memory.getMaxDefaultTypeAlign"));
        om.bind("xdc.runtime.Memory.valloc", new Extern("xdc_runtime_Memory_valloc__E", "xdc_Ptr(*)(xdc_runtime_IHeap_Handle,xdc_SizeT,xdc_SizeT,xdc_Char,xdc_runtime_Error_Block*)", true, false, "xdc.runtime.Memory.valloc"));
    }

    void IHeap$$CONSTS()
    {
        // interface IHeap
    }

    void HeapMin$$CONSTS()
    {
        // module HeapMin
    }

    void HeapStd$$CONSTS()
    {
        // module HeapStd
    }

    void Rta$$CONSTS()
    {
        // module Rta
        om.bind("xdc.runtime.Rta.Command_READ_MASK", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Rta.Command", "xdc.runtime"), "xdc.runtime.Rta.Command_READ_MASK", xdc.services.intern.xsr.Enum.intValue(0L)+0));
        om.bind("xdc.runtime.Rta.Command_WRITE_MASK", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Rta.Command", "xdc.runtime"), "xdc.runtime.Rta.Command_WRITE_MASK", xdc.services.intern.xsr.Enum.intValue(1L)+0));
        om.bind("xdc.runtime.Rta.Command_LOGGER_OFF", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Rta.Command", "xdc.runtime"), "xdc.runtime.Rta.Command_LOGGER_OFF", xdc.services.intern.xsr.Enum.intValue(2L)+0));
        om.bind("xdc.runtime.Rta.Command_LOGGER_ON", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Rta.Command", "xdc.runtime"), "xdc.runtime.Rta.Command_LOGGER_ON", xdc.services.intern.xsr.Enum.intValue(3L)+0));
        om.bind("xdc.runtime.Rta.Command_GET_CPU_SPEED", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Rta.Command", "xdc.runtime"), "xdc.runtime.Rta.Command_GET_CPU_SPEED", xdc.services.intern.xsr.Enum.intValue(4L)+0));
        om.bind("xdc.runtime.Rta.Command_RESET_LOGGER", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Rta.Command", "xdc.runtime"), "xdc.runtime.Rta.Command_RESET_LOGGER", xdc.services.intern.xsr.Enum.intValue(5L)+0));
        om.bind("xdc.runtime.Rta.Command_CHANGE_PERIOD", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Rta.Command", "xdc.runtime"), "xdc.runtime.Rta.Command_CHANGE_PERIOD", xdc.services.intern.xsr.Enum.intValue(6L)+0));
        om.bind("xdc.runtime.Rta.processCommand", new Extern("xdc_runtime_Rta_processCommand__E", "xdc_Void(*)(xdc_runtime_Rta_CommandPacket*,xdc_runtime_Rta_ResponsePacket*)", true, false, "xdc.runtime.Rta.processCommand"));
        om.bind("xdc.runtime.Rta.acknowledgeCmd", new Extern("xdc_runtime_Rta_acknowledgeCmd__E", "xdc_Void(*)(xdc_runtime_Rta_ResponsePacket*)", true, false, "xdc.runtime.Rta.acknowledgeCmd"));
        om.bind("xdc.runtime.Rta.readMask", new Extern("xdc_runtime_Rta_readMask__E", "xdc_Void(*)(xdc_runtime_Rta_ResponsePacket*,xdc_UArg)", true, false, "xdc.runtime.Rta.readMask"));
        om.bind("xdc.runtime.Rta.writeMask", new Extern("xdc_runtime_Rta_writeMask__E", "xdc_Void(*)(xdc_runtime_Rta_ResponsePacket*,xdc_UArg,xdc_UArg)", true, false, "xdc.runtime.Rta.writeMask"));
        om.bind("xdc.runtime.Rta.enableLog", new Extern("xdc_runtime_Rta_enableLog__E", "xdc_Void(*)(xdc_runtime_Rta_ResponsePacket*,xdc_UArg)", true, false, "xdc.runtime.Rta.enableLog"));
        om.bind("xdc.runtime.Rta.disableLog", new Extern("xdc_runtime_Rta_disableLog__E", "xdc_Void(*)(xdc_runtime_Rta_ResponsePacket*,xdc_UArg)", true, false, "xdc.runtime.Rta.disableLog"));
        om.bind("xdc.runtime.Rta.getCpuSpeed", new Extern("xdc_runtime_Rta_getCpuSpeed__E", "xdc_Void(*)(xdc_runtime_Rta_ResponsePacket*)", true, false, "xdc.runtime.Rta.getCpuSpeed"));
        om.bind("xdc.runtime.Rta.resetLog", new Extern("xdc_runtime_Rta_resetLog__E", "xdc_Void(*)(xdc_runtime_Rta_ResponsePacket*,xdc_UArg)", true, false, "xdc.runtime.Rta.resetLog"));
        om.bind("xdc.runtime.Rta.changePeriod", new Extern("xdc_runtime_Rta_changePeriod__E", "xdc_Void(*)(xdc_runtime_Rta_ResponsePacket*,xdc_UArg)", true, false, "xdc.runtime.Rta.changePeriod"));
    }

    void Startup$$CONSTS()
    {
        // module Startup
        om.bind("xdc.runtime.Startup.DONE", Global.eval("-1"));
        om.bind("xdc.runtime.Startup.NOTDONE", 0L);
        om.bind("xdc.runtime.Startup.execImplFxn", new Extern("xdc_runtime_Startup_exec__I", "xdc_Void(*)(xdc_Void)", true, false, "xdc.runtime.Startup.execImplFxn"));
        om.bind("xdc.runtime.Startup.exec", new Extern("xdc_runtime_Startup_exec__E", "xdc_Void(*)(xdc_Void)", true, false, "xdc.runtime.Startup.exec"));
        om.bind("xdc.runtime.Startup.rtsDone", new Extern("xdc_runtime_Startup_rtsDone__E", "xdc_Bool(*)(xdc_Void)", true, false, "xdc.runtime.Startup.rtsDone"));
        om.bind("xdc.runtime.Startup.reset", new Extern("xdc_runtime_Startup_reset__I", "xdc_Void(*)(xdc_Void)", true, false, "xdc.runtime.Startup.reset"));
        om.bind("xdc.runtime.Startup.startMods", new Extern("xdc_runtime_Startup_startMods__I", "xdc_Void(*)(xdc_Int[],xdc_Int)", true, false, "xdc.runtime.Startup.startMods"));
    }

    void Reset$$CONSTS()
    {
        // module Reset
    }

    void System$$CONSTS()
    {
        // module System
        om.bind("xdc.runtime.System.STATUS_UNKNOWN", 0xCAFEL);
        om.bind("xdc.runtime.System.abort", new Extern("xdc_runtime_System_abort__E", "xdc_Void(*)(xdc_String)", true, false, "xdc.runtime.System.abort"));
        om.bind("xdc.runtime.System.atexit", new Extern("xdc_runtime_System_atexit__E", "xdc_Bool(*)(xdc_Void(*)(xdc_Int))", true, false, "xdc.runtime.System.atexit"));
        om.bind("xdc.runtime.System.exit", new Extern("xdc_runtime_System_exit__E", "xdc_Void(*)(xdc_Int)", true, false, "xdc.runtime.System.exit"));
        om.bind("xdc.runtime.System.putch", new Extern("xdc_runtime_System_putch__E", "xdc_Void(*)(xdc_Char)", true, false, "xdc.runtime.System.putch"));
        om.bind("xdc.runtime.System.flush", new Extern("xdc_runtime_System_flush__E", "xdc_Void(*)(xdc_Void)", true, false, "xdc.runtime.System.flush"));
        om.bind("xdc.runtime.System.printf", new Extern("xdc_runtime_System_printf__E", "xdc_Int(*)(xdc_String,...)", true, false, "xdc.runtime.System.printf"));
        om.bind("xdc.runtime.System.aprintf", new Extern("xdc_runtime_System_aprintf__E", "xdc_Int(*)(xdc_String,...)", true, false, "xdc.runtime.System.aprintf"));
        om.bind("xdc.runtime.System.sprintf", new Extern("xdc_runtime_System_sprintf__E", "xdc_Int(*)(xdc_Char[],xdc_String,...)", true, false, "xdc.runtime.System.sprintf"));
        om.bind("xdc.runtime.System.asprintf", new Extern("xdc_runtime_System_asprintf__E", "xdc_Int(*)(xdc_Char[],xdc_String,...)", true, false, "xdc.runtime.System.asprintf"));
        om.bind("xdc.runtime.System.vprintf", new Extern("xdc_runtime_System_vprintf__E", "xdc_Int(*)(xdc_String,xdc_VaList)", true, false, "xdc.runtime.System.vprintf"));
        om.bind("xdc.runtime.System.avprintf", new Extern("xdc_runtime_System_avprintf__E", "xdc_Int(*)(xdc_String,xdc_VaList)", true, false, "xdc.runtime.System.avprintf"));
        om.bind("xdc.runtime.System.vsprintf", new Extern("xdc_runtime_System_vsprintf__E", "xdc_Int(*)(xdc_Char[],xdc_String,xdc_VaList)", true, false, "xdc.runtime.System.vsprintf"));
        om.bind("xdc.runtime.System.avsprintf", new Extern("xdc_runtime_System_avsprintf__E", "xdc_Int(*)(xdc_Char[],xdc_String,xdc_VaList)", true, false, "xdc.runtime.System.avsprintf"));
        om.bind("xdc.runtime.System.printfExtend", new Extern("xdc_runtime_System_printfExtend__I", "xdc_Int(*)(xdc_Char**,xdc_Char**,xdc_VaList*,xdc_runtime_System_ParseData*)", true, false, "xdc.runtime.System.printfExtend"));
        om.bind("xdc.runtime.System.doPrint", new Extern("xdc_runtime_System_doPrint__I", "xdc_Int(*)(xdc_Char[],xdc_String,xdc_VaList,xdc_Bool)", true, false, "xdc.runtime.System.doPrint"));
        om.bind("xdc.runtime.System.formatNum", new Extern("xdc_runtime_System_formatNum__I", "xdc_Char*(*)(xdc_Char*,xdc_UInt32,xdc_Int,xdc_Int)", true, false, "xdc.runtime.System.formatNum"));
        om.bind("xdc.runtime.System.putchar", new Extern("xdc_runtime_System_putchar__I", "xdc_Void(*)(xdc_Char**,xdc_Char)", true, false, "xdc.runtime.System.putchar"));
        om.bind("xdc.runtime.System.rtsExit", new Extern("xdc_runtime_System_rtsExit__I", "xdc_Void(*)(xdc_Void)", true, false, "xdc.runtime.System.rtsExit"));
    }

    void ISystemSupport$$CONSTS()
    {
        // interface ISystemSupport
    }

    void SysStd$$CONSTS()
    {
        // module SysStd
        om.bind("xdc.runtime.SysStd.abort", new Extern("xdc_runtime_SysStd_abort__E", "xdc_Void(*)(xdc_String)", true, false, "xdc.runtime.SysStd.abort"));
        om.bind("xdc.runtime.SysStd.exit", new Extern("xdc_runtime_SysStd_exit__E", "xdc_Void(*)(xdc_Int)", true, false, "xdc.runtime.SysStd.exit"));
        om.bind("xdc.runtime.SysStd.flush", new Extern("xdc_runtime_SysStd_flush__E", "xdc_Void(*)(xdc_Void)", true, false, "xdc.runtime.SysStd.flush"));
        om.bind("xdc.runtime.SysStd.putch", new Extern("xdc_runtime_SysStd_putch__E", "xdc_Void(*)(xdc_Char)", true, false, "xdc.runtime.SysStd.putch"));
        om.bind("xdc.runtime.SysStd.ready", new Extern("xdc_runtime_SysStd_ready__E", "xdc_Bool(*)(xdc_Void)", true, false, "xdc.runtime.SysStd.ready"));
    }

    void SysMin$$CONSTS()
    {
        // module SysMin
        om.bind("xdc.runtime.SysMin.abort", new Extern("xdc_runtime_SysMin_abort__E", "xdc_Void(*)(xdc_String)", true, false, "xdc.runtime.SysMin.abort"));
        om.bind("xdc.runtime.SysMin.exit", new Extern("xdc_runtime_SysMin_exit__E", "xdc_Void(*)(xdc_Int)", true, false, "xdc.runtime.SysMin.exit"));
        om.bind("xdc.runtime.SysMin.flush", new Extern("xdc_runtime_SysMin_flush__E", "xdc_Void(*)(xdc_Void)", true, false, "xdc.runtime.SysMin.flush"));
        om.bind("xdc.runtime.SysMin.putch", new Extern("xdc_runtime_SysMin_putch__E", "xdc_Void(*)(xdc_Char)", true, false, "xdc.runtime.SysMin.putch"));
        om.bind("xdc.runtime.SysMin.ready", new Extern("xdc_runtime_SysMin_ready__E", "xdc_Bool(*)(xdc_Void)", true, false, "xdc.runtime.SysMin.ready"));
        om.bind("xdc.runtime.SysMin.output", new Extern("xdc_runtime_SysMin_output__I", "xdc_Void(*)(xdc_Char*,xdc_UInt)", true, false, "xdc.runtime.SysMin.output"));
    }

    void Text$$CONSTS()
    {
        // module Text
        om.bind("xdc.runtime.Text.cordText", new Extern("xdc_runtime_Text_cordText__E", "xdc_String(*)(xdc_runtime_Types_CordAddr__*)", true, false, "xdc.runtime.Text.cordText"));
        om.bind("xdc.runtime.Text.ropeText", new Extern("xdc_runtime_Text_ropeText__E", "xdc_String(*)(xdc_Bits16)", true, false, "xdc.runtime.Text.ropeText"));
        om.bind("xdc.runtime.Text.matchRope", new Extern("xdc_runtime_Text_matchRope__E", "xdc_Int(*)(xdc_Bits16,xdc_String,xdc_Int*)", true, false, "xdc.runtime.Text.matchRope"));
        om.bind("xdc.runtime.Text.putLab", new Extern("xdc_runtime_Text_putLab__E", "xdc_Int(*)(xdc_runtime_Types_Label*,xdc_Char**,xdc_Int)", true, false, "xdc.runtime.Text.putLab"));
        om.bind("xdc.runtime.Text.putMod", new Extern("xdc_runtime_Text_putMod__E", "xdc_Int(*)(xdc_Bits16,xdc_Char**,xdc_Int)", true, false, "xdc.runtime.Text.putMod"));
        om.bind("xdc.runtime.Text.putSite", new Extern("xdc_runtime_Text_putSite__E", "xdc_Int(*)(xdc_runtime_Types_Site*,xdc_Char**,xdc_Int)", true, false, "xdc.runtime.Text.putSite"));
        om.bind("xdc.runtime.Text.matchVisFxn", new Extern("xdc_runtime_Text_matchVisFxn__I", "xdc_Bool(*)(xdc_Ptr,xdc_String)", true, false, "xdc.runtime.Text.matchVisFxn"));
        om.bind("xdc.runtime.Text.printVisFxn", new Extern("xdc_runtime_Text_printVisFxn__I", "xdc_Bool(*)(xdc_Ptr,xdc_String)", true, false, "xdc.runtime.Text.printVisFxn"));
        om.bind("xdc.runtime.Text.visitRope", new Extern("xdc_runtime_Text_visitRope__I", "xdc_Void(*)(xdc_Bits16,xdc_Fxn,xdc_Ptr)", true, false, "xdc.runtime.Text.visitRope"));
        om.bind("xdc.runtime.Text.visitRope2", new Extern("xdc_runtime_Text_visitRope2__I", "xdc_Void(*)(xdc_Bits16,xdc_Fxn,xdc_Ptr,xdc_String[])", true, false, "xdc.runtime.Text.visitRope2"));
        om.bind("xdc.runtime.Text.xprintf", new Extern("xdc_runtime_Text_xprintf__I", "xdc_Int(*)(xdc_Char**,xdc_String,...)", true, false, "xdc.runtime.Text.xprintf"));
    }

    void ITimestampClient$$CONSTS()
    {
        // interface ITimestampClient
    }

    void Timestamp$$CONSTS()
    {
        // module Timestamp
        om.bind("xdc.runtime.Timestamp.get32", new Extern("xdc_runtime_Timestamp_get32__E", "xdc_Bits32(*)(xdc_Void)", true, false, "xdc.runtime.Timestamp.get32"));
        om.bind("xdc.runtime.Timestamp.get64", new Extern("xdc_runtime_Timestamp_get64__E", "xdc_Void(*)(xdc_runtime_Types_Timestamp64*)", true, false, "xdc.runtime.Timestamp.get64"));
        om.bind("xdc.runtime.Timestamp.getFreq", new Extern("xdc_runtime_Timestamp_getFreq__E", "xdc_Void(*)(xdc_runtime_Types_FreqHz*)", true, false, "xdc.runtime.Timestamp.getFreq"));
    }

    void ITimestampProvider$$CONSTS()
    {
        // interface ITimestampProvider
    }

    void TimestampNull$$CONSTS()
    {
        // module TimestampNull
        om.bind("xdc.runtime.TimestampNull.get32", new Extern("xdc_runtime_TimestampNull_get32__E", "xdc_Bits32(*)(xdc_Void)", true, false, "xdc.runtime.TimestampNull.get32"));
        om.bind("xdc.runtime.TimestampNull.get64", new Extern("xdc_runtime_TimestampNull_get64__E", "xdc_Void(*)(xdc_runtime_Types_Timestamp64*)", true, false, "xdc.runtime.TimestampNull.get64"));
        om.bind("xdc.runtime.TimestampNull.getFreq", new Extern("xdc_runtime_TimestampNull_getFreq__E", "xdc_Void(*)(xdc_runtime_Types_FreqHz*)", true, false, "xdc.runtime.TimestampNull.getFreq"));
    }

    void TimestampStd$$CONSTS()
    {
        // module TimestampStd
        om.bind("xdc.runtime.TimestampStd.get32", new Extern("xdc_runtime_TimestampStd_get32__E", "xdc_Bits32(*)(xdc_Void)", true, false, "xdc.runtime.TimestampStd.get32"));
        om.bind("xdc.runtime.TimestampStd.get64", new Extern("xdc_runtime_TimestampStd_get64__E", "xdc_Void(*)(xdc_runtime_Types_Timestamp64*)", true, false, "xdc.runtime.TimestampStd.get64"));
        om.bind("xdc.runtime.TimestampStd.getFreq", new Extern("xdc_runtime_TimestampStd_getFreq__E", "xdc_Void(*)(xdc_runtime_Types_FreqHz*)", true, false, "xdc.runtime.TimestampStd.getFreq"));
    }

    void Types$$CONSTS()
    {
        // module Types
        om.bind("xdc.runtime.Types.STATIC_POLICY", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Types.CreatePolicy", "xdc.runtime"), "xdc.runtime.Types.STATIC_POLICY", 0));
        om.bind("xdc.runtime.Types.CREATE_POLICY", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Types.CreatePolicy", "xdc.runtime"), "xdc.runtime.Types.CREATE_POLICY", 1));
        om.bind("xdc.runtime.Types.DELETE_POLICY", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("xdc.runtime.Types.CreatePolicy", "xdc.runtime"), "xdc.runtime.Types.DELETE_POLICY", 2));
    }

    void IInstance$$CONSTS()
    {
        // interface IInstance
    }

    void LoggerBuf_TimestampProxy$$CONSTS()
    {
        // module LoggerBuf_TimestampProxy
        om.bind("xdc.runtime.LoggerBuf_TimestampProxy.get32", new Extern("xdc_runtime_LoggerBuf_TimestampProxy_get32__E", "xdc_Bits32(*)(xdc_Void)", true, false, "xdc.runtime.LoggerBuf_TimestampProxy.get32"));
        om.bind("xdc.runtime.LoggerBuf_TimestampProxy.get64", new Extern("xdc_runtime_LoggerBuf_TimestampProxy_get64__E", "xdc_Void(*)(xdc_runtime_Types_Timestamp64*)", true, false, "xdc.runtime.LoggerBuf_TimestampProxy.get64"));
        om.bind("xdc.runtime.LoggerBuf_TimestampProxy.getFreq", new Extern("xdc_runtime_LoggerBuf_TimestampProxy_getFreq__E", "xdc_Void(*)(xdc_runtime_Types_FreqHz*)", true, false, "xdc.runtime.LoggerBuf_TimestampProxy.getFreq"));
    }

    void LoggerBuf_Module_GateProxy$$CONSTS()
    {
        // module LoggerBuf_Module_GateProxy
        om.bind("xdc.runtime.LoggerBuf_Module_GateProxy.query", new Extern("xdc_runtime_LoggerBuf_Module_GateProxy_query__E", "xdc_Bool(*)(xdc_Int)", true, false, "xdc.runtime.LoggerBuf_Module_GateProxy.query"));
    }

    void LoggerSys_TimestampProxy$$CONSTS()
    {
        // module LoggerSys_TimestampProxy
        om.bind("xdc.runtime.LoggerSys_TimestampProxy.get32", new Extern("xdc_runtime_LoggerSys_TimestampProxy_get32__E", "xdc_Bits32(*)(xdc_Void)", true, false, "xdc.runtime.LoggerSys_TimestampProxy.get32"));
        om.bind("xdc.runtime.LoggerSys_TimestampProxy.get64", new Extern("xdc_runtime_LoggerSys_TimestampProxy_get64__E", "xdc_Void(*)(xdc_runtime_Types_Timestamp64*)", true, false, "xdc.runtime.LoggerSys_TimestampProxy.get64"));
        om.bind("xdc.runtime.LoggerSys_TimestampProxy.getFreq", new Extern("xdc_runtime_LoggerSys_TimestampProxy_getFreq__E", "xdc_Void(*)(xdc_runtime_Types_FreqHz*)", true, false, "xdc.runtime.LoggerSys_TimestampProxy.getFreq"));
    }

    void Main_Module_GateProxy$$CONSTS()
    {
        // module Main_Module_GateProxy
        om.bind("xdc.runtime.Main_Module_GateProxy.query", new Extern("xdc_runtime_Main_Module_GateProxy_query__E", "xdc_Bool(*)(xdc_Int)", true, false, "xdc.runtime.Main_Module_GateProxy.query"));
    }

    void Memory_HeapProxy$$CONSTS()
    {
        // module Memory_HeapProxy
    }

    void System_SupportProxy$$CONSTS()
    {
        // module System_SupportProxy
        om.bind("xdc.runtime.System_SupportProxy.abort", new Extern("xdc_runtime_System_SupportProxy_abort__E", "xdc_Void(*)(xdc_String)", true, false, "xdc.runtime.System_SupportProxy.abort"));
        om.bind("xdc.runtime.System_SupportProxy.exit", new Extern("xdc_runtime_System_SupportProxy_exit__E", "xdc_Void(*)(xdc_Int)", true, false, "xdc.runtime.System_SupportProxy.exit"));
        om.bind("xdc.runtime.System_SupportProxy.flush", new Extern("xdc_runtime_System_SupportProxy_flush__E", "xdc_Void(*)(xdc_Void)", true, false, "xdc.runtime.System_SupportProxy.flush"));
        om.bind("xdc.runtime.System_SupportProxy.putch", new Extern("xdc_runtime_System_SupportProxy_putch__E", "xdc_Void(*)(xdc_Char)", true, false, "xdc.runtime.System_SupportProxy.putch"));
        om.bind("xdc.runtime.System_SupportProxy.ready", new Extern("xdc_runtime_System_SupportProxy_ready__E", "xdc_Bool(*)(xdc_Void)", true, false, "xdc.runtime.System_SupportProxy.ready"));
    }

    void System_Module_GateProxy$$CONSTS()
    {
        // module System_Module_GateProxy
        om.bind("xdc.runtime.System_Module_GateProxy.query", new Extern("xdc_runtime_System_Module_GateProxy_query__E", "xdc_Bool(*)(xdc_Int)", true, false, "xdc.runtime.System_Module_GateProxy.query"));
    }

    void Timestamp_SupportProxy$$CONSTS()
    {
        // module Timestamp_SupportProxy
        om.bind("xdc.runtime.Timestamp_SupportProxy.get32", new Extern("xdc_runtime_Timestamp_SupportProxy_get32__E", "xdc_Bits32(*)(xdc_Void)", true, false, "xdc.runtime.Timestamp_SupportProxy.get32"));
        om.bind("xdc.runtime.Timestamp_SupportProxy.get64", new Extern("xdc_runtime_Timestamp_SupportProxy_get64__E", "xdc_Void(*)(xdc_runtime_Types_Timestamp64*)", true, false, "xdc.runtime.Timestamp_SupportProxy.get64"));
        om.bind("xdc.runtime.Timestamp_SupportProxy.getFreq", new Extern("xdc_runtime_Timestamp_SupportProxy_getFreq__E", "xdc_Void(*)(xdc_runtime_Types_FreqHz*)", true, false, "xdc.runtime.Timestamp_SupportProxy.getFreq"));
    }

    void IModule$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Assert$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Core$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Defaults$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Diags$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Error$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Gate$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IGateProvider$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void GateNull$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("xdc$runtime$GateNull$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function xdc.runtime.GateNull.create() called before xdc.useModule('xdc.runtime.GateNull')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("xdc.runtime.GateNull$$create", new Proto.Fxn(om.findStrict("xdc.runtime.GateNull.Module", "xdc.runtime"), om.findStrict("xdc.runtime.GateNull.Instance", "xdc.runtime"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("xdc.runtime.GateNull.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$GateNull$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.GateNull'];\n");
                sb.append("var __inst = xdc.om['xdc.runtime.GateNull.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['xdc.runtime']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['xdc.runtime.GateNull'].Instance_State);\n");
                sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.GateNull'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("xdc.runtime.GateNull$$construct", new Proto.Fxn(om.findStrict("xdc.runtime.GateNull.Module", "xdc.runtime"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("xdc.runtime.GateNull$$Object", "xdc.runtime"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("xdc.runtime.GateNull.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$GateNull$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.GateNull'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['xdc.runtime.GateNull'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.GateNull'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void Log$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ILogger$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void LoggerBuf$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("xdc$runtime$LoggerBuf$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function xdc.runtime.LoggerBuf.create() called before xdc.useModule('xdc.runtime.LoggerBuf')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("xdc.runtime.LoggerBuf$$create", new Proto.Fxn(om.findStrict("xdc.runtime.LoggerBuf.Module", "xdc.runtime"), om.findStrict("xdc.runtime.LoggerBuf.Instance", "xdc.runtime"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("xdc.runtime.LoggerBuf.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$LoggerBuf$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.LoggerBuf'];\n");
                sb.append("var __inst = xdc.om['xdc.runtime.LoggerBuf.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['xdc.runtime']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['xdc.runtime.LoggerBuf'].Instance_State);\n");
                sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.LoggerBuf'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("xdc.runtime.LoggerBuf$$construct", new Proto.Fxn(om.findStrict("xdc.runtime.LoggerBuf.Module", "xdc.runtime"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("xdc.runtime.LoggerBuf$$Object", "xdc.runtime"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("xdc.runtime.LoggerBuf.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$LoggerBuf$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.LoggerBuf'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['xdc.runtime.LoggerBuf'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.LoggerBuf'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void LoggerSys$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("xdc$runtime$LoggerSys$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function xdc.runtime.LoggerSys.create() called before xdc.useModule('xdc.runtime.LoggerSys')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("xdc.runtime.LoggerSys$$create", new Proto.Fxn(om.findStrict("xdc.runtime.LoggerSys.Module", "xdc.runtime"), om.findStrict("xdc.runtime.LoggerSys.Instance", "xdc.runtime"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("xdc.runtime.LoggerSys.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$LoggerSys$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.LoggerSys'];\n");
                sb.append("var __inst = xdc.om['xdc.runtime.LoggerSys.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['xdc.runtime']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['xdc.runtime.LoggerSys'].Instance_State);\n");
                sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.LoggerSys'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("xdc.runtime.LoggerSys$$construct", new Proto.Fxn(om.findStrict("xdc.runtime.LoggerSys.Module", "xdc.runtime"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("xdc.runtime.LoggerSys$$Object", "xdc.runtime"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("xdc.runtime.LoggerSys.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$LoggerSys$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.LoggerSys'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['xdc.runtime.LoggerSys'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.LoggerSys'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void Main$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Memory$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IHeap$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void HeapMin$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("xdc$runtime$HeapMin$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function xdc.runtime.HeapMin.create() called before xdc.useModule('xdc.runtime.HeapMin')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("xdc.runtime.HeapMin$$create", new Proto.Fxn(om.findStrict("xdc.runtime.HeapMin.Module", "xdc.runtime"), om.findStrict("xdc.runtime.HeapMin.Instance", "xdc.runtime"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("xdc.runtime.HeapMin.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$HeapMin$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.HeapMin'];\n");
                sb.append("var __inst = xdc.om['xdc.runtime.HeapMin.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['xdc.runtime']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['xdc.runtime.HeapMin'].Instance_State);\n");
                sb.append("__inst.align = __mod.PARAMS.align;\n");
                sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.HeapMin'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("xdc.runtime.HeapMin$$construct", new Proto.Fxn(om.findStrict("xdc.runtime.HeapMin.Module", "xdc.runtime"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("xdc.runtime.HeapMin$$Object", "xdc.runtime"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("xdc.runtime.HeapMin.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$HeapMin$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.HeapMin'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['xdc.runtime.HeapMin'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("__inst.align = __mod.PARAMS.align;\n");
                sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.HeapMin'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void HeapStd$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("xdc$runtime$HeapStd$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function xdc.runtime.HeapStd.create() called before xdc.useModule('xdc.runtime.HeapStd')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("xdc.runtime.HeapStd$$create", new Proto.Fxn(om.findStrict("xdc.runtime.HeapStd.Module", "xdc.runtime"), om.findStrict("xdc.runtime.HeapStd.Instance", "xdc.runtime"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("xdc.runtime.HeapStd.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$HeapStd$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.HeapStd'];\n");
                sb.append("var __inst = xdc.om['xdc.runtime.HeapStd.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['xdc.runtime']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['xdc.runtime.HeapStd'].Instance_State);\n");
                sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.HeapStd'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("xdc.runtime.HeapStd$$construct", new Proto.Fxn(om.findStrict("xdc.runtime.HeapStd.Module", "xdc.runtime"), null, 2, 0, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("xdc.runtime.HeapStd$$Object", "xdc.runtime"), null);
                        fxn.addArg(1, "__params", (Proto)om.findStrict("xdc.runtime.HeapStd.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$HeapStd$$construct = function( __obj, __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.HeapStd'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['xdc.runtime.HeapStd'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.HeapStd'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void Rta$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Startup$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Reset$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void System$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ISystemSupport$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void SysStd$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void SysMin$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Text$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ITimestampClient$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Timestamp$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void ITimestampProvider$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TimestampNull$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TimestampStd$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Types$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IInstance$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void LoggerBuf_TimestampProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void LoggerBuf_Module_GateProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("xdc$runtime$LoggerBuf_Module_GateProxy$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function xdc.runtime.LoggerBuf_Module_GateProxy.create() called before xdc.useModule('xdc.runtime.LoggerBuf_Module_GateProxy')\");\n");
                sb.append("}\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("xdc.runtime.LoggerBuf_Module_GateProxy$$create", new Proto.Fxn(om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Module", "xdc.runtime"), om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Instance", "xdc.runtime"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$LoggerBuf_Module_GateProxy$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.LoggerBuf_Module_GateProxy'];\n");
                sb.append("var __inst = xdc.om['xdc.runtime.LoggerBuf_Module_GateProxy.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['xdc.runtime']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['xdc.runtime.LoggerBuf_Module_GateProxy'].Instance_State);\n");
                sb.append("if (!__mod.delegate$) {\n");
                    sb.append("throw new Error(\"Unbound proxy module: xdc.runtime.LoggerBuf_Module_GateProxy\");\n");
                sb.append("}\n");
                sb.append("var __dmod = __mod.delegate$.$orig;\n");
                sb.append("var __dinst = __dmod.create(__params);\n");
                sb.append("__inst.$$bind('delegate$', __dinst);\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.LoggerBuf_Module_GateProxy'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void LoggerSys_TimestampProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Main_Module_GateProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("xdc$runtime$Main_Module_GateProxy$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function xdc.runtime.Main_Module_GateProxy.create() called before xdc.useModule('xdc.runtime.Main_Module_GateProxy')\");\n");
                sb.append("}\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("xdc.runtime.Main_Module_GateProxy$$create", new Proto.Fxn(om.findStrict("xdc.runtime.Main_Module_GateProxy.Module", "xdc.runtime"), om.findStrict("xdc.runtime.Main_Module_GateProxy.Instance", "xdc.runtime"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("xdc.runtime.Main_Module_GateProxy.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$Main_Module_GateProxy$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.Main_Module_GateProxy'];\n");
                sb.append("var __inst = xdc.om['xdc.runtime.Main_Module_GateProxy.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['xdc.runtime']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['xdc.runtime.Main_Module_GateProxy'].Instance_State);\n");
                sb.append("if (!__mod.delegate$) {\n");
                    sb.append("throw new Error(\"Unbound proxy module: xdc.runtime.Main_Module_GateProxy\");\n");
                sb.append("}\n");
                sb.append("var __dmod = __mod.delegate$.$orig;\n");
                sb.append("var __dinst = __dmod.create(__params);\n");
                sb.append("__inst.$$bind('delegate$', __dinst);\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.Main_Module_GateProxy'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void Memory_HeapProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("xdc$runtime$Memory_HeapProxy$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function xdc.runtime.Memory_HeapProxy.create() called before xdc.useModule('xdc.runtime.Memory_HeapProxy')\");\n");
                sb.append("}\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("xdc.runtime.Memory_HeapProxy$$create", new Proto.Fxn(om.findStrict("xdc.runtime.Memory_HeapProxy.Module", "xdc.runtime"), om.findStrict("xdc.runtime.Memory_HeapProxy.Instance", "xdc.runtime"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("xdc.runtime.Memory_HeapProxy.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$Memory_HeapProxy$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.Memory_HeapProxy'];\n");
                sb.append("var __inst = xdc.om['xdc.runtime.Memory_HeapProxy.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['xdc.runtime']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['xdc.runtime.Memory_HeapProxy'].Instance_State);\n");
                sb.append("if (!__mod.delegate$) {\n");
                    sb.append("throw new Error(\"Unbound proxy module: xdc.runtime.Memory_HeapProxy\");\n");
                sb.append("}\n");
                sb.append("var __dmod = __mod.delegate$.$orig;\n");
                sb.append("var __dinst = __dmod.create(__params);\n");
                sb.append("__inst.$$bind('delegate$', __dinst);\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.Memory_HeapProxy'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void System_SupportProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void System_Module_GateProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("xdc$runtime$System_Module_GateProxy$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function xdc.runtime.System_Module_GateProxy.create() called before xdc.useModule('xdc.runtime.System_Module_GateProxy')\");\n");
                sb.append("}\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("xdc.runtime.System_Module_GateProxy$$create", new Proto.Fxn(om.findStrict("xdc.runtime.System_Module_GateProxy.Module", "xdc.runtime"), om.findStrict("xdc.runtime.System_Module_GateProxy.Instance", "xdc.runtime"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("xdc.runtime.System_Module_GateProxy.Params", "xdc.runtime"), Global.newObject());
            sb = new StringBuilder();
            sb.append("xdc$runtime$System_Module_GateProxy$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['xdc.runtime.System_Module_GateProxy'];\n");
                sb.append("var __inst = xdc.om['xdc.runtime.System_Module_GateProxy.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['xdc.runtime']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['xdc.runtime.System_Module_GateProxy'].Instance_State);\n");
                sb.append("if (!__mod.delegate$) {\n");
                    sb.append("throw new Error(\"Unbound proxy module: xdc.runtime.System_Module_GateProxy\");\n");
                sb.append("}\n");
                sb.append("var __dmod = __mod.delegate$.$orig;\n");
                sb.append("var __dinst = __dmod.create(__params);\n");
                sb.append("__inst.$$bind('delegate$', __dinst);\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['xdc.runtime.System_Module_GateProxy'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void Timestamp_SupportProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IModule$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Assert$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Core$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Defaults$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Defaults.getCommon
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Defaults$$getCommon", new Proto.Fxn(om.findStrict("xdc.runtime.Defaults.Module", "xdc.runtime"), $$T_Obj, 2, 2, false));
                fxn.addArg(0, "mod", (Proto)om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"), $$UNDEF);
                fxn.addArg(1, "param", $$T_Str, $$UNDEF);
    }

    void Diags$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Diags.setMaskMeta
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Diags$$setMaskMeta", new Proto.Fxn(om.findStrict("xdc.runtime.Diags.Module", "xdc.runtime"), null, 3, 3, false));
                fxn.addArg(0, "pattern", $$T_Obj, $$UNDEF);
                fxn.addArg(1, "mask", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF);
                fxn.addArg(2, "mode", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF);
    }

    void Error$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Gate$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Gate.staticAlloc
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Gate$$staticAlloc", new Proto.Fxn(om.findStrict("xdc.runtime.Gate.Module", "xdc.runtime"), null, 2, 2, false));
                fxn.addArg(0, "stateObj", $$T_Obj, $$UNDEF);
                fxn.addArg(1, "fldName", $$T_Str, $$UNDEF);
    }

    void IGateProvider$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn IGateProvider.queryMeta
        fxn = (Proto.Fxn)om.bind("xdc.runtime.IGateProvider$$queryMeta", new Proto.Fxn(om.findStrict("xdc.runtime.IGateProvider.Module", "xdc.runtime"), $$T_Bool, 1, 1, false));
                fxn.addArg(0, "qual", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
    }

    void GateNull$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Log$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Log.lookupEventMessage
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Log$$lookupEventMessage", new Proto.Fxn(om.findStrict("xdc.runtime.Log.Module", "xdc.runtime"), null, 0, -1, false));
        // fxn Log.getTargetArgSize
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Log$$getTargetArgSize", new Proto.Fxn(om.findStrict("xdc.runtime.Log.Module", "xdc.runtime"), null, 0, -1, false));
        // fxn Log.lookupEventName
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Log$$lookupEventName", new Proto.Fxn(om.findStrict("xdc.runtime.Log.Module", "xdc.runtime"), null, 0, -1, false));
        // fxn Log.lookupModuleName
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Log$$lookupModuleName", new Proto.Fxn(om.findStrict("xdc.runtime.Log.Module", "xdc.runtime"), null, 0, -1, false));
        // fxn Log.getTargetEventRecSize
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Log$$getTargetEventRecSize", new Proto.Fxn(om.findStrict("xdc.runtime.Log.Module", "xdc.runtime"), null, 0, -1, false));
    }

    void ILogger$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn ILogger.getMetaArgs
        fxn = (Proto.Fxn)om.bind("xdc.runtime.ILogger$$getMetaArgs", new Proto.Fxn(om.findStrict("xdc.runtime.ILogger.Module", "xdc.runtime"), null, 0, -1, false));
    }

    void LoggerBuf$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn LoggerBuf.initDecoder
        fxn = (Proto.Fxn)om.bind("xdc.runtime.LoggerBuf$$initDecoder", new Proto.Fxn(om.findStrict("xdc.runtime.LoggerBuf.Module", "xdc.runtime"), null, 0, -1, false));
    }

    void LoggerSys$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Main$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Memory$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Memory.getMaxDefaultTypeAlignMeta
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Memory$$getMaxDefaultTypeAlignMeta", new Proto.Fxn(om.findStrict("xdc.runtime.Memory.Module", "xdc.runtime"), Proto.Elm.newCNum("(xdc_SizeT)"), 0, 0, false));
        // fxn Memory.staticPlace
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Memory$$staticPlace", new Proto.Fxn(om.findStrict("xdc.runtime.Memory.Module", "xdc.runtime"), $$T_Bool, 3, 3, false));
                fxn.addArg(0, "obj", $$T_Obj, $$UNDEF);
                fxn.addArg(1, "align", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF);
                fxn.addArg(2, "section", $$T_Str, $$UNDEF);
    }

    void IHeap$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void HeapMin$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void HeapStd$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Rta$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Rta.genRta
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Rta$$genRta", new Proto.Fxn(om.findStrict("xdc.runtime.Rta.Module", "xdc.runtime"), null, 0, -1, false));
    }

    void Startup$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Reset$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void System$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn System.atexitMeta
        fxn = (Proto.Fxn)om.bind("xdc.runtime.System$$atexitMeta", new Proto.Fxn(om.findStrict("xdc.runtime.System.Module", "xdc.runtime"), null, 1, 1, false));
                fxn.addArg(0, "handler", new Proto.Adr("xdc_Void(*)(xdc_Int)", "PFv"), $$UNDEF);
        // fxn System.mprintf
        fxn = (Proto.Fxn)om.bind("xdc.runtime.System$$mprintf", new Proto.Fxn(om.findStrict("xdc.runtime.System.Module", "xdc.runtime"), null, 0, -1, false));
    }

    void ISystemSupport$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void SysStd$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void SysMin$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Text$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Text.defineRopeCord
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Text$$defineRopeCord", new Proto.Fxn(om.findStrict("xdc.runtime.Text.Module", "xdc.runtime"), null, 0, -1, false));
        // fxn Text.defineRopeNode
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Text$$defineRopeNode", new Proto.Fxn(om.findStrict("xdc.runtime.Text.Module", "xdc.runtime"), null, 0, -1, false));
        // fxn Text.fetchAddr
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Text$$fetchAddr", new Proto.Fxn(om.findStrict("xdc.runtime.Text.Module", "xdc.runtime"), null, 0, -1, false));
        // fxn Text.fetchCord
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Text$$fetchCord", new Proto.Fxn(om.findStrict("xdc.runtime.Text.Module", "xdc.runtime"), null, 0, -1, false));
        // fxn Text.fetchId
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Text$$fetchId", new Proto.Fxn(om.findStrict("xdc.runtime.Text.Module", "xdc.runtime"), null, 0, -1, false));
        // fxn Text.fetchNode
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Text$$fetchNode", new Proto.Fxn(om.findStrict("xdc.runtime.Text.Module", "xdc.runtime"), null, 0, -1, false));
        // fxn Text.genModNames
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Text$$genModNames", new Proto.Fxn(om.findStrict("xdc.runtime.Text.Module", "xdc.runtime"), null, 0, -1, false));
        // fxn Text.genPkgName
        fxn = (Proto.Fxn)om.bind("xdc.runtime.Text$$genPkgName", new Proto.Fxn(om.findStrict("xdc.runtime.Text.Module", "xdc.runtime"), null, 0, -1, false));
    }

    void ITimestampClient$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Timestamp$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void ITimestampProvider$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TimestampNull$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TimestampStd$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Types$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IInstance$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void LoggerBuf_TimestampProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void LoggerBuf_Module_GateProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void LoggerSys_TimestampProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Main_Module_GateProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Memory_HeapProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void System_SupportProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void System_Module_GateProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Timestamp_SupportProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IModule$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Assert$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Core$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.Core.ObjDesc", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("fxnTab", "UPtr"));
        sizes.add(Global.newArray("modLink", "UPtr"));
        sizes.add(Global.newArray("objAlign", "USize"));
        sizes.add(Global.newArray("objHeap", "UPtr"));
        sizes.add(Global.newArray("objName", "USize"));
        sizes.add(Global.newArray("objSize", "USize"));
        sizes.add(Global.newArray("prmsInit", "UPtr"));
        sizes.add(Global.newArray("prmsSize", "USize"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Core.ObjDesc']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Core.ObjDesc']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Core.ObjDesc'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Defaults$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Diags$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.Diags.DictElem", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("modId", "UInt16"));
        sizes.add(Global.newArray("maskAddr", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Diags.DictElem']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Diags.DictElem']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Diags.DictElem'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Error$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.Error.Data", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("arg", "A2;TIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Error.Data']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Error.Data']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Error.Data'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Error.Block", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("unused", "UInt16"));
        sizes.add(Global.newArray("data", "Sxdc.runtime.Error;Data"));
        sizes.add(Global.newArray("id", "Exdc.runtime.Error;Id"));
        sizes.add(Global.newArray("msg", "UPtr"));
        sizes.add(Global.newArray("site", "Sxdc.runtime.Types;Site"));
        sizes.add(Global.newArray("xtra", "A4;TIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Error.Block']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Error.Block']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Error.Block'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Error.Module_State", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("count", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Error.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Error.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Error.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Gate$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void IGateProvider$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void GateNull$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Log$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.Log.EventRec", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("tstamp", "Sxdc.runtime.Types;Timestamp64"));
        sizes.add(Global.newArray("serial", "UInt32"));
        sizes.add(Global.newArray("evt", "UInt32"));
        sizes.add(Global.newArray("arg", "A8;TIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Log.EventRec']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Log.EventRec']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Log.EventRec'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void ILogger$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void LoggerBuf$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.LoggerBuf.Entry", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("tstamp", "Sxdc.runtime.Types;Timestamp64"));
        sizes.add(Global.newArray("serial", "UInt32"));
        sizes.add(Global.newArray("evt", "UInt32"));
        sizes.add(Global.newArray("arg1", "TIArg"));
        sizes.add(Global.newArray("arg2", "TIArg"));
        sizes.add(Global.newArray("arg3", "TIArg"));
        sizes.add(Global.newArray("arg4", "TIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.LoggerBuf.Entry']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.LoggerBuf.Entry']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.LoggerBuf.Entry'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.LoggerBuf.Instance_State", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("bufHeap", "UPtr"));
        sizes.add(Global.newArray("entryArr", "UPtr"));
        sizes.add(Global.newArray("curEntry", "UPtr"));
        sizes.add(Global.newArray("endEntry", "UPtr"));
        sizes.add(Global.newArray("readEntry", "UPtr"));
        sizes.add(Global.newArray("serial", "UInt32"));
        sizes.add(Global.newArray("numEntries", "TInt16"));
        sizes.add(Global.newArray("advance", "TInt8"));
        sizes.add(Global.newArray("enabled", "UShort"));
        sizes.add(Global.newArray("flush", "UShort"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.LoggerBuf.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.LoggerBuf.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.LoggerBuf.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void LoggerSys$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Main$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Memory$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.Memory.Stats", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("totalSize", "UIArg"));
        sizes.add(Global.newArray("totalFreeSize", "UIArg"));
        sizes.add(Global.newArray("largestFreeSize", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Memory.Stats']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Memory.Stats']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Memory.Stats'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Memory.Module_State", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("maxDefaultTypeAlign", "USize"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Memory.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Memory.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Memory.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void IHeap$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void HeapMin$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.HeapMin.Instance_State", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("buf", "UPtr"));
        sizes.add(Global.newArray("remainSize", "UIArg"));
        sizes.add(Global.newArray("startSize", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.HeapMin.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.HeapMin.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.HeapMin.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void HeapStd$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.HeapStd.Module_State", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("remainRTSSize", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.HeapStd.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.HeapStd.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.HeapStd.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.HeapStd.Instance_State", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("remainSize", "UIArg"));
        sizes.add(Global.newArray("startSize", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.HeapStd.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.HeapStd.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.HeapStd.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Rta$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.Rta.CommandPacket", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("cmdId", "Nxdc.runtime.Rta.Command;TInt;0;1;2;3;4;5;6"));
        sizes.add(Global.newArray("arg0", "UIArg"));
        sizes.add(Global.newArray("arg1", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Rta.CommandPacket']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Rta.CommandPacket']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Rta.CommandPacket'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Rta.ResponsePacket", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("cmdId", "Nxdc.runtime.Rta.Command;TInt;0;1;2;3;4;5;6"));
        sizes.add(Global.newArray("resp0", "UIArg"));
        sizes.add(Global.newArray("resp1", "UIArg"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Rta.ResponsePacket']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Rta.ResponsePacket']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Rta.ResponsePacket'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Startup$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.Startup.Module_State", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("stateTab", "UPtr"));
        sizes.add(Global.newArray("execFlag", "UShort"));
        sizes.add(Global.newArray("rtsDoneFlag", "UShort"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Startup.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Startup.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Startup.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Reset$$SIZES()
    {
    }

    void System$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.System.ParseData", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("width", "TInt"));
        sizes.add(Global.newArray("lFlag", "UShort"));
        sizes.add(Global.newArray("lJust", "UShort"));
        sizes.add(Global.newArray("precis", "TInt"));
        sizes.add(Global.newArray("len", "TInt"));
        sizes.add(Global.newArray("zpad", "TInt"));
        sizes.add(Global.newArray("end", "UPtr"));
        sizes.add(Global.newArray("aFlag", "UShort"));
        sizes.add(Global.newArray("ptr", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.System.ParseData']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.System.ParseData']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.System.ParseData'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.System.Module_State", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("atexitHandlers", "UPtr"));
        sizes.add(Global.newArray("numAtexitHandlers", "TInt"));
        sizes.add(Global.newArray("exitStatus", "TInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.System.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.System.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.System.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void ISystemSupport$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void SysStd$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void SysMin$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.SysMin.Module_State", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("outbuf", "UPtr"));
        sizes.add(Global.newArray("outidx", "UInt"));
        sizes.add(Global.newArray("wrapped", "UShort"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.SysMin.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.SysMin.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.SysMin.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Text$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.Text.Node", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("left", "UInt16"));
        sizes.add(Global.newArray("right", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Text.Node']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Text.Node']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Text.Node'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Text.MatchVisState", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("pat", "UPtr"));
        sizes.add(Global.newArray("lenp", "UPtr"));
        sizes.add(Global.newArray("res", "TInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Text.MatchVisState']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Text.MatchVisState']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Text.MatchVisState'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Text.PrintVisState", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("bufp", "UPtr"));
        sizes.add(Global.newArray("len", "TInt"));
        sizes.add(Global.newArray("res", "TInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Text.PrintVisState']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Text.PrintVisState']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Text.PrintVisState'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Text.Module_State", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("charBase", "UPtr"));
        sizes.add(Global.newArray("nodeBase", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Text.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Text.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Text.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void ITimestampClient$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Timestamp$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void ITimestampProvider$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void TimestampNull$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void TimestampStd$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Types$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("xdc.runtime.Types.Label", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("handle", "UPtr"));
        sizes.add(Global.newArray("modId", "UInt16"));
        sizes.add(Global.newArray("iname", "UPtr"));
        sizes.add(Global.newArray("named", "UShort"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Types.Label']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Types.Label']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Types.Label'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Types.Site", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("mod", "UInt16"));
        sizes.add(Global.newArray("file", "UPtr"));
        sizes.add(Global.newArray("line", "TInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Types.Site']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Types.Site']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Types.Site'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Types.Timestamp64", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("hi", "UInt32"));
        sizes.add(Global.newArray("lo", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Types.Timestamp64']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Types.Timestamp64']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Types.Timestamp64'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Types.FreqHz", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("hi", "UInt32"));
        sizes.add(Global.newArray("lo", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Types.FreqHz']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Types.FreqHz']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Types.FreqHz'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Types.Vec", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("len", "TInt"));
        sizes.add(Global.newArray("arr", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Types.Vec']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Types.Vec']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Types.Vec'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Types.Link", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("next", "UPtr"));
        sizes.add(Global.newArray("prev", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Types.Link']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Types.Link']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Types.Link'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Types.ModHdr", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("link", "Sxdc.runtime.Types;Link"));
        sizes.add(Global.newArray("instArrBeg", "UPtr"));
        sizes.add(Global.newArray("instArrEnd", "UPtr"));
        sizes.add(Global.newArray("instSize", "USize"));
        sizes.add(Global.newArray("curInst", "UPtr"));
        sizes.add(Global.newArray("diagsMask", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Types.ModHdr']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Types.ModHdr']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Types.ModHdr'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Types.ModHdrS", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("diagsMask", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Types.ModHdrS']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Types.ModHdrS']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Types.ModHdrS'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Types.InstHdr", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("link", "Sxdc.runtime.Types;Link"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Types.InstHdr']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Types.InstHdr']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Types.InstHdr'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Types.PrmsHdr", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("size", "USize"));
        sizes.add(Global.newArray("self", "UPtr"));
        sizes.add(Global.newArray("modFxns", "UPtr"));
        sizes.add(Global.newArray("instPrms", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Types.PrmsHdr']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Types.PrmsHdr']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Types.PrmsHdr'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Types.Base", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("base", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Types.Base']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Types.Base']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Types.Base'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Types.SysFxns", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("__create", "UFxn"));
        sizes.add(Global.newArray("__delete", "UFxn"));
        sizes.add(Global.newArray("__label", "UFxn"));
        sizes.add(Global.newArray("__mid", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Types.SysFxns']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Types.SysFxns']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Types.SysFxns'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("xdc.runtime.Types.SysFxns2", "xdc.runtime");
        sizes.clear();
        sizes.add(Global.newArray("__create", "UFxn"));
        sizes.add(Global.newArray("__delete", "UFxn"));
        sizes.add(Global.newArray("__label", "UFxn"));
        sizes.add(Global.newArray("__mid", "UInt16"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['xdc.runtime.Types.SysFxns2']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['xdc.runtime.Types.SysFxns2']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['xdc.runtime.Types.SysFxns2'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void IInstance$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void LoggerBuf_TimestampProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void LoggerBuf_Module_GateProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void LoggerSys_TimestampProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Main_Module_GateProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Memory_HeapProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void System_SupportProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void System_Module_GateProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Timestamp_SupportProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void IModule$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime");
        po.init("xdc.runtime.IModule.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("common$", (Proto)om.findStrict("xdc.runtime.Types.Common$", "xdc.runtime"), $$DEFAULT, "wh");
                        po.addFld("viewNameMap$", new Proto.Map((Proto)om.findStrict("xdc.runtime.Types.ViewInfo", "xdc.runtime")), $$DEFAULT, "wh");
                        po.addFld("rovShowRawTab$", $$T_Bool, true, "wh");
                        po.addFld("configNameMap$", new Proto.Map((Proto)om.findStrict("xdc.runtime.Types.ViewInfo", "xdc.runtime")), Global.newArray(new Object[]{Global.newArray(new Object[]{"xdc.runtime/Memory", Global.newObject("viewType", "module", "fields", Global.newArray(new Object[]{"common$.instanceHeap", "common$.instanceSection", "common$.memoryPolicy", "common$.namedModule", "common$.namedInstance", "common$.fxntab", "common$.romPatchTable"}))}), Global.newArray(new Object[]{"xdc.runtime/Diagnostics", Global.newObject("viewType", "module", "fields", Global.newArray(new Object[]{"common$.logger", "common$.diags_ASSERT", "common$.diags_ENTRY", "common$.diags_EXIT", "common$.diags_INTERNAL", "common$.diags_LIFECYCLE", "common$.diags_USER1", "common$.diags_USER2", "common$.diags_USER3", "common$.diags_USER4", "common$.diags_USER5", "common$.diags_USER6", "common$.diags_USER7", "common$.diags_USER8"}))}), Global.newArray(new Object[]{"xdc.runtime/Concurrency", Global.newObject("viewType", "module", "fields", Global.newArray(new Object[]{"common$.gate", "common$.gateParams"}))}), Global.newArray(new Object[]{"xdc.runtime/Log Events", Global.newObject("viewType", "module", "fields", Global.newArray(new Object[]{"Log.Event"}))}), Global.newArray(new Object[]{"xdc.runtime/Log Events", Global.newObject("viewType", "instance", "fields", Global.newArray(new Object[]{"Log.Event"}))}), Global.newArray(new Object[]{"xdc.runtime/Asserts", Global.newObject("viewType", "module", "fields", Global.newArray(new Object[]{"Assert.Id"}))}), Global.newArray(new Object[]{"xdc.runtime/Asserts", Global.newObject("viewType", "instance", "fields", Global.newArray(new Object[]{"Assert.Id"}))}), Global.newArray(new Object[]{"xdc.runtime/Errors", Global.newObject("viewType", "module", "fields", Global.newArray(new Object[]{"Error.Id"}))}), Global.newArray(new Object[]{"xdc.runtime/Errors", Global.newObject("viewType", "instance", "fields", Global.newArray(new Object[]{"Error.Id"}))})}), "rh");
                        po.addFld("Module__diagsEnabled", Proto.Elm.newCNum("(xdc_Bits32)"), 0L, "w");
                        po.addFld("Module__diagsIncluded", Proto.Elm.newCNum("(xdc_Bits32)"), 0L, "w");
                        po.addFld("Module__diagsMask", new Proto.Adr("xdc_Bits16*", "Pn"), null, "w");
                        po.addFld("Module__gateObj", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("Module__gatePrms", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("Module__id", Proto.Elm.newCNum("(xdc_Bits16)"), 0L, "w");
                        po.addFld("Module__loggerDefined", $$T_Bool, false, "w");
                        po.addFld("Module__loggerObj", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
                        po.addFld("Module__loggerFxn4", new Proto.Adr("xdc_Void(*)(xdc_Ptr,xdc_Bits32,xdc_IArg,xdc_IArg,xdc_IArg,xdc_IArg)", "PFv"), null, "w");
                        po.addFld("Module__loggerFxn8", new Proto.Adr("xdc_Void(*)(xdc_Ptr,xdc_Bits32,xdc_IArg,xdc_IArg,xdc_IArg,xdc_IArg,xdc_IArg,xdc_IArg,xdc_IArg,xdc_IArg)", "PFv"), null, "w");
                        po.addFld("Module__startupDoneFxn", new Proto.Adr("xdc_Bool(*)(xdc_Void)", "PFb"), null, "w");
                        po.addFld("Object__count", Proto.Elm.newCNum("(xdc_Int)"), 0L, "w");
                        po.addFld("Object__heap", (Proto)om.findStrict("xdc.runtime.IHeap.Handle", "xdc.runtime"), null, "w");
                        po.addFld("Object__sizeof", Proto.Elm.newCNum("(xdc_SizeT)"), 0L, "w");
                        po.addFld("Object__table", new Proto.Adr("xdc_Ptr", "Pv"), null, "w");
        }//isCFG
    }

    void Assert$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/Assert.xs");
        om.bind("xdc.runtime.Assert$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.Assert.Module", "xdc.runtime");
        po.init("xdc.runtime.Assert.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("E_assertFailed", (Proto)om.findStrict("xdc.runtime.Error$$Id", "xdc.runtime"), Global.newObject("msg", "assertion failure%s%s"), "r");
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.Assert$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.Assert$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.Assert$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.Assert$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct Assert.Desc
        po = (Proto.Obj)om.findStrict("xdc.runtime.Assert$$Desc", "xdc.runtime");
        po.init("xdc.runtime.Assert.Desc", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("mask", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("msg", $$T_Str, $$UNDEF, "w");
        // typedef Assert.Id
        pt = (Proto.Typedef)om.findStrict("xdc.runtime.Assert$$Id", "xdc.runtime");
        pt.init("xdc.runtime.Assert.Id", (Proto)om.findStrict("xdc.runtime.Assert.Desc", "xdc.runtime"), Global.get(cap, "Id$encode"));
        om.bind("xdc.runtime.Assert.Id", pt);
    }

    void Core$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.Core.Module", "xdc.runtime");
        po.init("xdc.runtime.Core.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("A_initializedParams", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "xdc.runtime"), Global.newObject("msg", "A_initializedParams: uninitialized Params struct"), "w");
        }//isCFG
        // struct Core.ObjDesc
        po = (Proto.Obj)om.findStrict("xdc.runtime.Core$$ObjDesc", "xdc.runtime");
        po.init("xdc.runtime.Core.ObjDesc", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("fxnTab", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("modLink", new Proto.Adr("xdc_runtime_Types_Link*", "PS"), $$UNDEF, "w");
                po.addFld("objAlign", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("objHeap", (Proto)om.findStrict("xdc.runtime.IHeap.Handle", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("objName", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("objSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("prmsInit", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("prmsSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
    }

    void Defaults$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/Defaults.xs");
        om.bind("xdc.runtime.Defaults$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.Defaults.Module", "xdc.runtime");
        po.init("xdc.runtime.Defaults.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("common$", (Proto)om.findStrict("xdc.runtime.Types.Common$", "xdc.runtime"), Global.newObject("diags_ASSERT", om.find("xdc.runtime.Diags.ALWAYS_ON"), "diags_ENTRY", om.find("xdc.runtime.Diags.ALWAYS_OFF"), "diags_EXIT", om.find("xdc.runtime.Diags.ALWAYS_OFF"), "diags_INTERNAL", om.find("xdc.runtime.Diags.ALWAYS_OFF"), "diags_LIFECYCLE", om.find("xdc.runtime.Diags.ALWAYS_OFF"), "diags_USER1", om.find("xdc.runtime.Diags.ALWAYS_OFF"), "diags_USER2", om.find("xdc.runtime.Diags.ALWAYS_OFF"), "diags_USER3", om.find("xdc.runtime.Diags.ALWAYS_OFF"), "diags_USER4", om.find("xdc.runtime.Diags.ALWAYS_OFF"), "diags_USER5", om.find("xdc.runtime.Diags.ALWAYS_OFF"), "diags_USER6", om.find("xdc.runtime.Diags.ALWAYS_OFF"), "diags_USER7", om.find("xdc.runtime.Diags.ALWAYS_OFF"), "diags_USER8", om.find("xdc.runtime.Diags.ALWAYS_OFF"), "fxntab", true, "gate", null, "gateParams", null, "instanceHeap", null, "instanceSection", null, "logger", null, "memoryPolicy", om.find("xdc.runtime.Types.DELETE_POLICY"), "namedInstance", false, "namedModule", true, "romPatchTable", false), "wh");
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.Defaults$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.Defaults$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.Defaults$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.Defaults$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("getCommon", (Proto.Fxn)om.findStrict("xdc.runtime.Defaults$$getCommon", "xdc.runtime"), Global.get(cap, "getCommon"));
    }

    void Diags$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/Diags.xs");
        om.bind("xdc.runtime.Diags$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.Diags.Module", "xdc.runtime");
        po.init("xdc.runtime.Diags.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ENTRY", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0001L, "rh");
                po.addFld("EXIT", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0002L, "rh");
                po.addFld("LIFECYCLE", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0004L, "rh");
                po.addFld("INTERNAL", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0008L, "rh");
                po.addFld("ASSERT", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0010L, "rh");
                po.addFld("USER1", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0100L, "rh");
                po.addFld("USER2", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0200L, "rh");
                po.addFld("USER3", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0400L, "rh");
                po.addFld("USER4", Proto.Elm.newCNum("(xdc_Bits16)"), 0x0800L, "rh");
                po.addFld("USER5", Proto.Elm.newCNum("(xdc_Bits16)"), 0x1000L, "rh");
                po.addFld("USER6", Proto.Elm.newCNum("(xdc_Bits16)"), 0x2000L, "rh");
                po.addFld("USER7", Proto.Elm.newCNum("(xdc_Bits16)"), 0x4000L, "rh");
                po.addFld("USER8", Proto.Elm.newCNum("(xdc_Bits16)"), 0x8000L, "rh");
                po.addFld("ALL", Proto.Elm.newCNum("(xdc_Bits16)"), 0xFFFFL, "rh");
        if (isCFG) {
                        po.addFld("setMaskEnabled", $$T_Bool, false, "w");
                        po.addFld("dictBase", new Proto.Adr("xdc_runtime_Diags_DictElem*", "PS"), null, "w");
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.Diags$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.Diags$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.Diags$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.Diags$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("setMaskMeta", (Proto.Fxn)om.findStrict("xdc.runtime.Diags$$setMaskMeta", "xdc.runtime"), Global.get(cap, "setMaskMeta"));
        // typedef Diags.Mask
        om.bind("xdc.runtime.Diags.Mask", Proto.Elm.newCNum("(xdc_Bits16)"));
        // struct Diags.DictElem
        po = (Proto.Obj)om.findStrict("xdc.runtime.Diags$$DictElem", "xdc.runtime");
        po.init("xdc.runtime.Diags.DictElem", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("modId", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("maskAddr", new Proto.Adr("xdc_Bits16*", "Pn"), $$UNDEF, "w");
    }

    void Error$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/Error.xs");
        om.bind("xdc.runtime.Error$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.Error.Module", "xdc.runtime");
        po.init("xdc.runtime.Error.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("NUMARGS", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("E_generic", (Proto)om.findStrict("xdc.runtime.Error$$Id", "xdc.runtime"), Global.newObject("msg", "generic error: %s"), "w");
                        po.addFld("E_memory", (Proto)om.findStrict("xdc.runtime.Error$$Id", "xdc.runtime"), Global.newObject("msg", "out of memory: heap=0x%x, size=%u"), "w");
                        po.addFld("policy", (Proto)om.findStrict("xdc.runtime.Error.Policy", "xdc.runtime"), om.find("xdc.runtime.Error.UNWIND"), "w");
                        po.addFld("raiseHook", new Proto.Adr("xdc_Void(*)(xdc_runtime_Error_Block*)", "PFv"), om.find("xdc.runtime.Error.print"), "w");
                        po.addFld("maxDepth", Proto.Elm.newCNum("(xdc_UInt16)"), 16L, "w");
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.Error$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.Error$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.Error$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.Error$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct Error.Desc
        po = (Proto.Obj)om.findStrict("xdc.runtime.Error$$Desc", "xdc.runtime");
        po.init("xdc.runtime.Error.Desc", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("msg", $$T_Str, $$UNDEF, "w");
                po.addFld("code", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
        // typedef Error.Id
        pt = (Proto.Typedef)om.findStrict("xdc.runtime.Error$$Id", "xdc.runtime");
        pt.init("xdc.runtime.Error.Id", (Proto)om.findStrict("xdc.runtime.Error.Desc", "xdc.runtime"), Global.get(cap, "Id$encode"));
        om.bind("xdc.runtime.Error.Id", pt);
        // struct Error.Data
        po = (Proto.Obj)om.findStrict("xdc.runtime.Error$$Data", "xdc.runtime");
        po.init("xdc.runtime.Error.Data", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("arg", new Proto.Arr(new Proto.Adr("xdc_IArg", "Pv"), false, xdc.services.intern.xsr.Enum.intValue(2L)), $$DEFAULT, "w");
        // struct Error.Block
        po = (Proto.Obj)om.findStrict("xdc.runtime.Error$$Block", "xdc.runtime");
        po.init("xdc.runtime.Error.Block", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("unused", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("data", (Proto)om.findStrict("xdc.runtime.Error.Data", "xdc.runtime"), $$DEFAULT, "w");
                po.addFld("id", (Proto)om.findStrict("xdc.runtime.Error$$Id", "xdc.runtime"), $$DEFAULT, "w");
                po.addFld("msg", $$T_Str, $$UNDEF, "w");
                po.addFld("site", (Proto)om.findStrict("xdc.runtime.Types.Site", "xdc.runtime"), $$DEFAULT, "w");
                po.addFld("xtra", new Proto.Arr(new Proto.Adr("xdc_IArg", "Pv"), false, xdc.services.intern.xsr.Enum.intValue(4L)), $$DEFAULT, "w");
        // struct Error.Module_State
        po = (Proto.Obj)om.findStrict("xdc.runtime.Error$$Module_State", "xdc.runtime");
        po.init("xdc.runtime.Error.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("count", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
    }

    void Gate$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/Gate.xs");
        om.bind("xdc.runtime.Gate$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.Gate.Module", "xdc.runtime");
        po.init("xdc.runtime.Gate.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.Gate$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.Gate$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.Gate$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.Gate$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("staticAlloc", (Proto.Fxn)om.findStrict("xdc.runtime.Gate$$staticAlloc", "xdc.runtime"), Global.get(cap, "staticAlloc"));
        // typedef Gate.Ref
        pt = (Proto.Typedef)om.findStrict("xdc.runtime.Gate$$Ref", "xdc.runtime");
        pt.init("xdc.runtime.Gate.Ref", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "xdc.runtime"), Global.get(cap, "Ref$encode"));
        om.bind("xdc.runtime.Gate.Ref", pt);
    }

    void IGateProvider$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/IGateProvider.xs");
        om.bind("xdc.runtime.IGateProvider$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.IGateProvider.Module", "xdc.runtime");
        po.init("xdc.runtime.IGateProvider.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.IGateProvider$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.IGateProvider$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("xdc.runtime.IGateProvider$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.IGateProvider$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.IGateProvider$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$static$init");
                if (fxn != null) om.bind("xdc.runtime.IGateProvider$$instance$static$init", true);
                if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "queryMeta");
                if (fxn != null) po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "xdc.runtime"), fxn);
        po = (Proto.Obj)om.findStrict("xdc.runtime.IGateProvider.Instance", "xdc.runtime");
        po.init("xdc.runtime.IGateProvider.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.IGateProvider$$Params", "xdc.runtime");
        po.init("xdc.runtime.IGateProvider.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
        }//isCFG
    }

    void GateNull$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/GateNull.xs");
        om.bind("xdc.runtime.GateNull$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.GateNull.Module", "xdc.runtime");
        po.init("xdc.runtime.GateNull.Module", om.findStrict("xdc.runtime.IGateProvider.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.runtime.GateNull$$create", "xdc.runtime"), Global.get("xdc$runtime$GateNull$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("xdc.runtime.GateNull$$construct", "xdc.runtime"), Global.get("xdc$runtime$GateNull$$construct"));
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.GateNull$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.GateNull$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("xdc.runtime.GateNull$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.GateNull$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.GateNull$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$static$init");
                if (fxn != null) om.bind("xdc.runtime.GateNull$$instance$static$init", true);
                if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "queryMeta");
                if (fxn != null) po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "xdc.runtime"), fxn);
        po = (Proto.Obj)om.findStrict("xdc.runtime.GateNull.Instance", "xdc.runtime");
        po.init("xdc.runtime.GateNull.Instance", om.findStrict("xdc.runtime.IGateProvider.Instance", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.GateNull$$Params", "xdc.runtime");
        po.init("xdc.runtime.GateNull.Params", om.findStrict("xdc.runtime.IGateProvider$$Params", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.GateNull$$Object", "xdc.runtime");
        po.init("xdc.runtime.GateNull.Object", om.findStrict("xdc.runtime.GateNull.Instance", "xdc.runtime"));
        po = (Proto.Obj)om.findStrict("xdc.runtime.GateNull$$Instance_State", "xdc.runtime");
        po.init("xdc.runtime.GateNull.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void Log$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/Log.xs");
        om.bind("xdc.runtime.Log$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.Log.Module", "xdc.runtime");
        po.init("xdc.runtime.Log.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("NUMARGS", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
                po.addFld("PRINTFID", Proto.Elm.newCNum("(xdc_Bits16)"), 0L, "rh");
        if (isCFG) {
                        po.addFld("L_construct", (Proto)om.findStrict("xdc.runtime.Log$$Event", "xdc.runtime"), Global.newObject("mask", 0x0004L, "msg", "<-- construct: %p('%s')"), "w");
                        po.addFld("L_create", (Proto)om.findStrict("xdc.runtime.Log$$Event", "xdc.runtime"), Global.newObject("mask", 0x0004L, "msg", "<-- create: %p('%s')"), "w");
                        po.addFld("L_destruct", (Proto)om.findStrict("xdc.runtime.Log$$Event", "xdc.runtime"), Global.newObject("mask", 0x0004L, "msg", "--> destruct: (%p)"), "w");
                        po.addFld("L_delete", (Proto)om.findStrict("xdc.runtime.Log$$Event", "xdc.runtime"), Global.newObject("mask", 0x0004L, "msg", "--> delete: (%p)"), "w");
                        po.addFld("idToInfo", new Proto.Map($$T_Str), Global.newArray(new Object[]{}), "wh");
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.Log$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.Log$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.Log$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.Log$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("lookupEventMessage", (Proto.Fxn)om.findStrict("xdc.runtime.Log$$lookupEventMessage", "xdc.runtime"), Global.get(cap, "lookupEventMessage"));
                po.addFxn("getTargetArgSize", (Proto.Fxn)om.findStrict("xdc.runtime.Log$$getTargetArgSize", "xdc.runtime"), Global.get(cap, "getTargetArgSize"));
                po.addFxn("lookupEventName", (Proto.Fxn)om.findStrict("xdc.runtime.Log$$lookupEventName", "xdc.runtime"), Global.get(cap, "lookupEventName"));
                po.addFxn("lookupModuleName", (Proto.Fxn)om.findStrict("xdc.runtime.Log$$lookupModuleName", "xdc.runtime"), Global.get(cap, "lookupModuleName"));
                po.addFxn("getTargetEventRecSize", (Proto.Fxn)om.findStrict("xdc.runtime.Log$$getTargetEventRecSize", "xdc.runtime"), Global.get(cap, "getTargetEventRecSize"));
        // struct Log.EventDesc
        po = (Proto.Obj)om.findStrict("xdc.runtime.Log$$EventDesc", "xdc.runtime");
        po.init("xdc.runtime.Log.EventDesc", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("mask", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("msg", $$T_Str, $$UNDEF, "w");
        // struct Log.EventRec
        po = (Proto.Obj)om.findStrict("xdc.runtime.Log$$EventRec", "xdc.runtime");
        po.init("xdc.runtime.Log.EventRec", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("tstamp", (Proto)om.findStrict("xdc.runtime.Types.Timestamp64", "xdc.runtime"), $$DEFAULT, "w");
                po.addFld("serial", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("evt", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Arr(new Proto.Adr("xdc_IArg", "Pv"), false, xdc.services.intern.xsr.Enum.intValue(8L)), $$DEFAULT, "w");
        // typedef Log.Event
        pt = (Proto.Typedef)om.findStrict("xdc.runtime.Log$$Event", "xdc.runtime");
        pt.init("xdc.runtime.Log.Event", (Proto)om.findStrict("xdc.runtime.Log.EventDesc", "xdc.runtime"), Global.get(cap, "Event$encode"));
        om.bind("xdc.runtime.Log.Event", pt);
        // typedef Log.EventId
        om.bind("xdc.runtime.Log.EventId", Proto.Elm.newCNum("(xdc_Bits16)"));
    }

    void ILogger$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/ILogger.xs");
        om.bind("xdc.runtime.ILogger$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.ILogger.Module", "xdc.runtime");
        po.init("xdc.runtime.ILogger.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.ILogger$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.ILogger$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("xdc.runtime.ILogger$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.ILogger$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.ILogger$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$static$init");
                if (fxn != null) om.bind("xdc.runtime.ILogger$$instance$static$init", true);
                if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "getMetaArgs");
                if (fxn != null) po.addFxn("getMetaArgs", (Proto.Fxn)om.findStrict("xdc.runtime.ILogger$$getMetaArgs", "xdc.runtime"), fxn);
        po = (Proto.Obj)om.findStrict("xdc.runtime.ILogger.Instance", "xdc.runtime");
        po.init("xdc.runtime.ILogger.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.ILogger$$Params", "xdc.runtime");
        po.init("xdc.runtime.ILogger.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void LoggerBuf$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/LoggerBuf.xs");
        om.bind("xdc.runtime.LoggerBuf$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf.Module", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf.Module", om.findStrict("xdc.runtime.ILogger.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("FULL", Proto.Elm.newCNum("(xdc_Int8)"), Global.eval("-1"), "rh");
                po.addFld("WRAP", Proto.Elm.newCNum("(xdc_Int8)"), 0L, "rh");
                po.addFld("NEXT", Proto.Elm.newCNum("(xdc_Int8)"), 1L, "rh");
        if (isCFG) {
                        po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "xdc.runtime"), $$UNDEF, "wh");
                        po.addFldV("TimestampProxy", (Proto)om.findStrict("xdc.runtime.ITimestampClient.Module", "xdc.runtime"), null, "wh", $$delegGet, $$delegSet);
                        po.addFld("enableFlush", $$T_Bool, false, "w");
                        po.addFldV("Module_GateProxy", (Proto)om.findStrict("xdc.runtime.IGateProvider.Module", "xdc.runtime"), null, "wh", $$delegGet, $$delegSet);
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.runtime.LoggerBuf$$create", "xdc.runtime"), Global.get("xdc$runtime$LoggerBuf$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("xdc.runtime.LoggerBuf$$construct", "xdc.runtime"), Global.get("xdc$runtime$LoggerBuf$$construct"));
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.LoggerBuf$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.LoggerBuf$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("xdc.runtime.LoggerBuf$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.LoggerBuf$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.LoggerBuf$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$static$init");
                if (fxn != null) om.bind("xdc.runtime.LoggerBuf$$instance$static$init", true);
                if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "getMetaArgs");
                if (fxn != null) po.addFxn("getMetaArgs", (Proto.Fxn)om.findStrict("xdc.runtime.ILogger$$getMetaArgs", "xdc.runtime"), fxn);
                po.addFxn("initDecoder", (Proto.Fxn)om.findStrict("xdc.runtime.LoggerBuf$$initDecoder", "xdc.runtime"), Global.get(cap, "initDecoder"));
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf.Instance", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf.Instance", om.findStrict("xdc.runtime.ILogger.Instance", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("FULL", Proto.Elm.newCNum("(xdc_Int8)"), Global.eval("-1"), "rh");
                po.addFld("WRAP", Proto.Elm.newCNum("(xdc_Int8)"), 0L, "rh");
                po.addFld("NEXT", Proto.Elm.newCNum("(xdc_Int8)"), 1L, "rh");
        if (isCFG) {
                        po.addFld("numEntries", Proto.Elm.newCNum("(xdc_Int)"), 64L, "w");
                        po.addFld("bufType", (Proto)om.findStrict("xdc.runtime.LoggerBuf.BufType", "xdc.runtime"), om.find("xdc.runtime.LoggerBuf.BufType_CIRCULAR"), "w");
                        po.addFld("exitFlush", $$T_Bool, false, "w");
                        po.addFld("bufSection", $$T_Str, null, "wh");
                        po.addFld("bufHeap", (Proto)om.findStrict("xdc.runtime.IHeap.Handle", "xdc.runtime"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf$$Params", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf.Params", om.findStrict("xdc.runtime.ILogger$$Params", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("FULL", Proto.Elm.newCNum("(xdc_Int8)"), Global.eval("-1"), "rh");
                po.addFld("WRAP", Proto.Elm.newCNum("(xdc_Int8)"), 0L, "rh");
                po.addFld("NEXT", Proto.Elm.newCNum("(xdc_Int8)"), 1L, "rh");
        if (isCFG) {
                        po.addFld("numEntries", Proto.Elm.newCNum("(xdc_Int)"), 64L, "w");
                        po.addFld("bufType", (Proto)om.findStrict("xdc.runtime.LoggerBuf.BufType", "xdc.runtime"), om.find("xdc.runtime.LoggerBuf.BufType_CIRCULAR"), "w");
                        po.addFld("exitFlush", $$T_Bool, false, "w");
                        po.addFld("bufSection", $$T_Str, null, "wh");
                        po.addFld("bufHeap", (Proto)om.findStrict("xdc.runtime.IHeap.Handle", "xdc.runtime"), null, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf$$Object", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf.Object", om.findStrict("xdc.runtime.LoggerBuf.Instance", "xdc.runtime"));
        // struct LoggerBuf.BasicView
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf$$BasicView", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("label", $$T_Str, $$UNDEF, "w");
                po.addFld("lastSerial", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("numEntries", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("type", $$T_Str, $$UNDEF, "w");
                po.addFld("enabledFlag", $$T_Bool, $$UNDEF, "w");
        // struct LoggerBuf.RecordView
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf$$RecordView", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf.RecordView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serial", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("timestampRaw", Proto.Elm.newCNum("(xdc_Long)"), $$UNDEF, "w");
                po.addFld("modName", $$T_Str, $$UNDEF, "w");
                po.addFld("text", $$T_Str, $$UNDEF, "w");
                po.addFld("eventId", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("eventName", $$T_Str, $$UNDEF, "w");
                po.addFld("arg0", new Proto.Adr("xdc_IArg", "Pv"), $$UNDEF, "w");
                po.addFld("arg1", new Proto.Adr("xdc_IArg", "Pv"), $$UNDEF, "w");
                po.addFld("arg2", new Proto.Adr("xdc_IArg", "Pv"), $$UNDEF, "w");
                po.addFld("arg3", new Proto.Adr("xdc_IArg", "Pv"), $$UNDEF, "w");
                po.addFld("arg4", new Proto.Adr("xdc_IArg", "Pv"), $$UNDEF, "w");
                po.addFld("arg5", new Proto.Adr("xdc_IArg", "Pv"), $$UNDEF, "w");
                po.addFld("arg6", new Proto.Adr("xdc_IArg", "Pv"), $$UNDEF, "w");
                po.addFld("arg7", new Proto.Adr("xdc_IArg", "Pv"), $$UNDEF, "w");
        // struct LoggerBuf.StopModeData
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf$$StopModeData", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf.StopModeData", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("bufferSymbol", $$T_Str, $$UNDEF, "w");
                po.addFld("bufferSize", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFxn("$xml", $$T_Met, Global.get("$$xml"));
        // struct LoggerBuf.Entry
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf$$Entry", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf.Entry", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("tstamp", (Proto)om.findStrict("xdc.runtime.Types.Timestamp64", "xdc.runtime"), $$DEFAULT, "w");
                po.addFld("serial", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("evt", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("arg1", new Proto.Adr("xdc_IArg", "Pv"), $$UNDEF, "w");
                po.addFld("arg2", new Proto.Adr("xdc_IArg", "Pv"), $$UNDEF, "w");
                po.addFld("arg3", new Proto.Adr("xdc_IArg", "Pv"), $$UNDEF, "w");
                po.addFld("arg4", new Proto.Adr("xdc_IArg", "Pv"), $$UNDEF, "w");
        // struct LoggerBuf.Instance_State
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf$$Instance_State", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("bufHeap", (Proto)om.findStrict("xdc.runtime.IHeap.Handle", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("entryArr", new Proto.Arr((Proto)om.findStrict("xdc.runtime.LoggerBuf.Entry", "xdc.runtime"), false), $$DEFAULT, "w");
                po.addFld("curEntry", new Proto.Adr("xdc_runtime_LoggerBuf_Entry*", "PS"), $$UNDEF, "w");
                po.addFld("endEntry", new Proto.Adr("xdc_runtime_LoggerBuf_Entry*", "PS"), $$UNDEF, "w");
                po.addFld("readEntry", new Proto.Adr("xdc_runtime_LoggerBuf_Entry*", "PS"), $$UNDEF, "w");
                po.addFld("serial", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("numEntries", Proto.Elm.newCNum("(xdc_Int16)"), $$UNDEF, "w");
                po.addFld("advance", Proto.Elm.newCNum("(xdc_Int8)"), $$UNDEF, "w");
                po.addFld("enabled", $$T_Bool, $$UNDEF, "w");
                po.addFld("flush", $$T_Bool, $$UNDEF, "w");
    }

    void LoggerSys$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/LoggerSys.xs");
        om.bind("xdc.runtime.LoggerSys$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerSys.Module", "xdc.runtime");
        po.init("xdc.runtime.LoggerSys.Module", om.findStrict("xdc.runtime.ILogger.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFldV("TimestampProxy", (Proto)om.findStrict("xdc.runtime.ITimestampClient.Module", "xdc.runtime"), null, "wh", $$delegGet, $$delegSet);
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.runtime.LoggerSys$$create", "xdc.runtime"), Global.get("xdc$runtime$LoggerSys$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("xdc.runtime.LoggerSys$$construct", "xdc.runtime"), Global.get("xdc$runtime$LoggerSys$$construct"));
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.LoggerSys$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.LoggerSys$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("xdc.runtime.LoggerSys$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.LoggerSys$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.LoggerSys$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$static$init");
                if (fxn != null) om.bind("xdc.runtime.LoggerSys$$instance$static$init", true);
                if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "getMetaArgs");
                if (fxn != null) po.addFxn("getMetaArgs", (Proto.Fxn)om.findStrict("xdc.runtime.ILogger$$getMetaArgs", "xdc.runtime"), fxn);
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerSys.Instance", "xdc.runtime");
        po.init("xdc.runtime.LoggerSys.Instance", om.findStrict("xdc.runtime.ILogger.Instance", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerSys$$Params", "xdc.runtime");
        po.init("xdc.runtime.LoggerSys.Params", om.findStrict("xdc.runtime.ILogger$$Params", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerSys$$Object", "xdc.runtime");
        po.init("xdc.runtime.LoggerSys.Object", om.findStrict("xdc.runtime.LoggerSys.Instance", "xdc.runtime"));
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerSys$$Instance_State", "xdc.runtime");
        po.init("xdc.runtime.LoggerSys.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void Main$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.Main.Module", "xdc.runtime");
        po.init("xdc.runtime.Main.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFldV("Module_GateProxy", (Proto)om.findStrict("xdc.runtime.IGateProvider.Module", "xdc.runtime"), null, "wh", $$delegGet, $$delegSet);
        }//isCFG
    }

    void Memory$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/Memory.xs");
        om.bind("xdc.runtime.Memory$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory.Module", "xdc.runtime");
        po.init("xdc.runtime.Memory.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
        if (isCFG) {
                        po.addFld("defaultHeapInstance", (Proto)om.findStrict("xdc.runtime.IHeap.Handle", "xdc.runtime"), $$UNDEF, "w");
                        po.addFld("defaultHeapSize", Proto.Elm.newCNum("(xdc_Int)"), 0x1000L, "wh");
                        po.addFldV("HeapProxy", (Proto)om.findStrict("xdc.runtime.IHeap.Module", "xdc.runtime"), null, "wh", $$delegGet, $$delegSet);
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.Memory$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.Memory$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.Memory$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.Memory$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("getMaxDefaultTypeAlignMeta", (Proto.Fxn)om.findStrict("xdc.runtime.Memory$$getMaxDefaultTypeAlignMeta", "xdc.runtime"), Global.get(cap, "getMaxDefaultTypeAlignMeta"));
                po.addFxn("staticPlace", (Proto.Fxn)om.findStrict("xdc.runtime.Memory$$staticPlace", "xdc.runtime"), Global.get(cap, "staticPlace"));
        // typedef Memory.Size
        om.bind("xdc.runtime.Memory.Size", new Proto.Adr("xdc_UArg", "Pv"));
        // struct Memory.Stats
        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory$$Stats", "xdc.runtime");
        po.init("xdc.runtime.Memory.Stats", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("totalSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("totalFreeSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("largestFreeSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct Memory.Module_View
        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory$$Module_View", "xdc.runtime");
        po.init("xdc.runtime.Memory.Module_View", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("maxDefaultTypeAlignment", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFxn("$xml", $$T_Met, Global.get("$$xml"));
        // struct Memory.Module_State
        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory$$Module_State", "xdc.runtime");
        po.init("xdc.runtime.Memory.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("maxDefaultTypeAlign", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
    }

    void IHeap$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.IHeap.Module", "xdc.runtime");
        po.init("xdc.runtime.IHeap.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.IHeap.Instance", "xdc.runtime");
        po.init("xdc.runtime.IHeap.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.IHeap$$Params", "xdc.runtime");
        po.init("xdc.runtime.IHeap.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void HeapMin$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/HeapMin.xs");
        om.bind("xdc.runtime.HeapMin$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapMin.Module", "xdc.runtime");
        po.init("xdc.runtime.HeapMin.Module", om.findStrict("xdc.runtime.IHeap.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("A_zeroSize", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "xdc.runtime"), Global.newObject("msg", "HeapMin_create cannot have a zero size value"), "w");
                        po.addFld("E_freeError", (Proto)om.findStrict("xdc.runtime.Error$$Id", "xdc.runtime"), Global.newObject("msg", "free() invalid in growth-only HeapMin"), "w");
                        po.addFld("freeError", $$T_Bool, true, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.runtime.HeapMin$$create", "xdc.runtime"), Global.get("xdc$runtime$HeapMin$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("xdc.runtime.HeapMin$$construct", "xdc.runtime"), Global.get("xdc$runtime$HeapMin$$construct"));
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.HeapMin$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.HeapMin$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("xdc.runtime.HeapMin$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.HeapMin$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.HeapMin$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$static$init");
                if (fxn != null) om.bind("xdc.runtime.HeapMin$$instance$static$init", true);
                if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapMin.Instance", "xdc.runtime");
        po.init("xdc.runtime.HeapMin.Instance", om.findStrict("xdc.runtime.IHeap.Instance", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("align", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "wh");
                        po.addFld("sectionName", $$T_Str, null, "wh");
                        po.addFld("buf", new Proto.Adr("xdc_Ptr", "Pv"), 0L, "w");
                        po.addFld("size", new Proto.Adr("xdc_UArg", "Pv"), 0L, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapMin$$Params", "xdc.runtime");
        po.init("xdc.runtime.HeapMin.Params", om.findStrict("xdc.runtime.IHeap$$Params", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("align", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "wh");
                        po.addFld("sectionName", $$T_Str, null, "wh");
                        po.addFld("buf", new Proto.Adr("xdc_Ptr", "Pv"), 0L, "w");
                        po.addFld("size", new Proto.Adr("xdc_UArg", "Pv"), 0L, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapMin$$Object", "xdc.runtime");
        po.init("xdc.runtime.HeapMin.Object", om.findStrict("xdc.runtime.HeapMin.Instance", "xdc.runtime"));
        // struct HeapMin.Instance_View
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapMin$$Instance_View", "xdc.runtime");
        po.init("xdc.runtime.HeapMin.Instance_View", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("address", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("label", $$T_Str, $$UNDEF, "w");
                po.addFld("buffer", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("remainSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("startSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFxn("$xml", $$T_Met, Global.get("$$xml"));
        // struct HeapMin.Instance_State
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapMin$$Instance_State", "xdc.runtime");
        po.init("xdc.runtime.HeapMin.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("buf", new Proto.Arr(Proto.Elm.newCNum("(xdc_Char)"), false), $$DEFAULT, "w");
                po.addFld("remainSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("startSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
    }

    void HeapStd$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/HeapStd.xs");
        om.bind("xdc.runtime.HeapStd$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapStd.Module", "xdc.runtime");
        po.init("xdc.runtime.HeapStd.Module", om.findStrict("xdc.runtime.IHeap.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("E_noRTSMemory", (Proto)om.findStrict("xdc.runtime.Error$$Id", "xdc.runtime"), Global.newObject("msg", "The RTS heap is used up. Examine Program.heap."), "w");
                        po.addFld("A_zeroSize", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "xdc.runtime"), Global.newObject("msg", "HeapStd_create cannot have a zero size value"), "w");
                        po.addFld("A_invalidTotalFreeSize", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "xdc.runtime"), Global.newObject("msg", "HeapStd instance totalFreeSize is greater than starting size"), "w");
                        po.addFld("A_invalidAlignment", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "xdc.runtime"), Global.newObject("msg", "HeapStd_alloc - requested alignment is greater than allowed"), "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.runtime.HeapStd$$create", "xdc.runtime"), Global.get("xdc$runtime$HeapStd$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("xdc.runtime.HeapStd$$construct", "xdc.runtime"), Global.get("xdc$runtime$HeapStd$$construct"));
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.HeapStd$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.HeapStd$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("xdc.runtime.HeapStd$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.HeapStd$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.HeapStd$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$static$init");
                if (fxn != null) om.bind("xdc.runtime.HeapStd$$instance$static$init", true);
                if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapStd.Instance", "xdc.runtime");
        po.init("xdc.runtime.HeapStd.Instance", om.findStrict("xdc.runtime.IHeap.Instance", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("size", new Proto.Adr("xdc_UArg", "Pv"), 0L, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapStd$$Params", "xdc.runtime");
        po.init("xdc.runtime.HeapStd.Params", om.findStrict("xdc.runtime.IHeap$$Params", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("size", new Proto.Adr("xdc_UArg", "Pv"), 0L, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapStd$$Object", "xdc.runtime");
        po.init("xdc.runtime.HeapStd.Object", om.findStrict("xdc.runtime.HeapStd.Instance", "xdc.runtime"));
        // struct HeapStd.Instance_View
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapStd$$Instance_View", "xdc.runtime");
        po.init("xdc.runtime.HeapStd.Instance_View", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("address", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("label", $$T_Str, $$UNDEF, "w");
                po.addFld("remainSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("startSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFxn("$xml", $$T_Met, Global.get("$$xml"));
        // struct HeapStd.Module_State
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapStd$$Module_State", "xdc.runtime");
        po.init("xdc.runtime.HeapStd.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("remainRTSSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct HeapStd.Instance_State
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapStd$$Instance_State", "xdc.runtime");
        po.init("xdc.runtime.HeapStd.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("remainSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("startSize", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
    }

    void Rta$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/Rta.xs");
        om.bind("xdc.runtime.Rta$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.Rta.Module", "xdc.runtime");
        po.init("xdc.runtime.Rta.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("LD_cmdRcvd", (Proto)om.findStrict("xdc.runtime.Log$$Event", "xdc.runtime"), Global.newObject("mask", 0x0200L, "msg", "LD_cmdRcvd: Received command: %d, arg0: 0x%x, arg1: 0x%x"), "w");
                        po.addFld("LD_writeMask", (Proto)om.findStrict("xdc.runtime.Log$$Event", "xdc.runtime"), Global.newObject("mask", 0x0200L, "msg", "LD_writeMask: Mask addres: 0x%x, New mask value: 0x%x"), "w");
                        po.addFld("A_invalidLogger", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "xdc.runtime"), Global.newObject("msg", "A_invalidLogger: The logger id %d is invalid."), "w");
                        po.addFld("E_badCommand", (Proto)om.findStrict("xdc.runtime.Error$$Id", "xdc.runtime"), Global.newObject("msg", "E_badCommand: Received invalid command, id: %d."), "w");
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.Rta$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.Rta$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.Rta$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.Rta$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("genRta", (Proto.Fxn)om.findStrict("xdc.runtime.Rta$$genRta", "xdc.runtime"), Global.get(cap, "genRta"));
        // struct Rta.CommandPacket
        po = (Proto.Obj)om.findStrict("xdc.runtime.Rta$$CommandPacket", "xdc.runtime");
        po.init("xdc.runtime.Rta.CommandPacket", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("cmdId", (Proto)om.findStrict("xdc.runtime.Rta.Command", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("arg0", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("arg1", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
        // struct Rta.ResponsePacket
        po = (Proto.Obj)om.findStrict("xdc.runtime.Rta$$ResponsePacket", "xdc.runtime");
        po.init("xdc.runtime.Rta.ResponsePacket", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("cmdId", (Proto)om.findStrict("xdc.runtime.Rta.Command", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("resp0", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("resp1", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
    }

    void Startup$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/Startup.xs");
        om.bind("xdc.runtime.Startup$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.Startup.Module", "xdc.runtime");
        po.init("xdc.runtime.Startup.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("DONE", Proto.Elm.newCNum("(xdc_Int)"), Global.eval("-1"), "rh");
                po.addFld("NOTDONE", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
        if (isCFG) {
                        po.addFld("maxPasses", Proto.Elm.newCNum("(xdc_Int)"), 32L, "w");
                        po.addFld("firstFxns", new Proto.Arr(new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), true), Global.newArray(new Object[]{}), "w");
                        po.addFld("lastFxns", new Proto.Arr(new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), true), Global.newArray(new Object[]{}), "w");
                        po.addFld("resetFxn", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), null, "wh");
                        po.addFld("startModsFxn", new Proto.Adr("xdc_Void(*)(xdc_Int[],xdc_Int)", "PFv"), om.find("xdc.runtime.Startup.startMods"), "r");
                        po.addFld("execImpl", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), om.find("xdc.runtime.Startup.execImplFxn"), "r");
                        po.addFld("sfxnTab", new Proto.Arr(new Proto.Adr("xdc_Int(*)(xdc_Int)", "PFn"), false), $$DEFAULT, "w");
                        po.addFld("sfxnRts", new Proto.Arr($$T_Bool, false), $$DEFAULT, "w");
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.Startup$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.Startup$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.Startup$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.Startup$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // typedef Startup.InitFxn
        om.bind("xdc.runtime.Startup.InitFxn", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"));
        // typedef Startup.SFxn
        om.bind("xdc.runtime.Startup.SFxn", new Proto.Adr("xdc_Int(*)(xdc_Int)", "PFn"));
        // struct Startup.Module_State
        po = (Proto.Obj)om.findStrict("xdc.runtime.Startup$$Module_State", "xdc.runtime");
        po.init("xdc.runtime.Startup.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("stateTab", new Proto.Adr("xdc_Int*", "Pn"), $$UNDEF, "w");
                po.addFld("execFlag", $$T_Bool, $$UNDEF, "w");
                po.addFld("rtsDoneFlag", $$T_Bool, $$UNDEF, "w");
    }

    void Reset$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.Reset.Module", "xdc.runtime");
        po.init("xdc.runtime.Reset.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("fxns", new Proto.Arr(new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), false), Global.newArray(new Object[]{}), "wh");
    }

    void System$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/System.xs");
        om.bind("xdc.runtime.System$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.System.Module", "xdc.runtime");
        po.init("xdc.runtime.System.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("STATUS_UNKNOWN", Proto.Elm.newCNum("(xdc_Int)"), 0xCAFEL, "rh");
        if (isCFG) {
                        po.addFld("A_cannotFitIntoArg", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "xdc.runtime"), Global.newObject("msg", "A_cannotFitIntoArg: sizeof(Float) > sizeof(Arg)"), "w");
                        po.addFld("extendedFormats", $$T_Str, "%$L", "wh");
                        po.addFldV("SupportProxy", (Proto)om.findStrict("xdc.runtime.ISystemSupport.Module", "xdc.runtime"), null, "wh", $$delegGet, $$delegSet);
                        po.addFld("maxAtexitHandlers", Proto.Elm.newCNum("(xdc_Int)"), 8L, "w");
                        po.addFld("extendFxn", new Proto.Adr("xdc_Int(*)(xdc_Char**,xdc_Char**,xdc_VaList*,xdc_runtime_System_ParseData*)", "PFn"), "&xdc_runtime_System_printfExtend__I", "r");
                        po.addFld("exitFxns", new Proto.Arr(new Proto.Adr("xdc_Void(*)(xdc_Int)", "PFv"), false), $$DEFAULT, "wh");
                        po.addFldV("Module_GateProxy", (Proto)om.findStrict("xdc.runtime.IGateProvider.Module", "xdc.runtime"), null, "wh", $$delegGet, $$delegSet);
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.System$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.System$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.System$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.System$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("atexitMeta", (Proto.Fxn)om.findStrict("xdc.runtime.System$$atexitMeta", "xdc.runtime"), Global.get(cap, "atexitMeta"));
                po.addFxn("mprintf", (Proto.Fxn)om.findStrict("xdc.runtime.System$$mprintf", "xdc.runtime"), Global.get(cap, "mprintf"));
        // typedef System.AtexitHandler
        om.bind("xdc.runtime.System.AtexitHandler", new Proto.Adr("xdc_Void(*)(xdc_Int)", "PFv"));
        // struct System.Module_View
        po = (Proto.Obj)om.findStrict("xdc.runtime.System$$Module_View", "xdc.runtime");
        po.init("xdc.runtime.System.Module_View", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("atexitHandlers", new Proto.Arr($$T_Str, false), $$DEFAULT, "w");
                po.addFld("numAtexitHandlers", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFxn("$xml", $$T_Met, Global.get("$$xml"));
        // struct System.ParseData
        po = (Proto.Obj)om.findStrict("xdc.runtime.System$$ParseData", "xdc.runtime");
        po.init("xdc.runtime.System.ParseData", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("width", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("lFlag", $$T_Bool, $$UNDEF, "w");
                po.addFld("lJust", $$T_Bool, $$UNDEF, "w");
                po.addFld("precis", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("len", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("zpad", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("end", new Proto.Adr("xdc_Char*", "Pn"), $$UNDEF, "w");
                po.addFld("aFlag", $$T_Bool, $$UNDEF, "w");
                po.addFld("ptr", new Proto.Adr("xdc_Char*", "Pn"), $$UNDEF, "w");
        // typedef System.ExtendFxn
        om.bind("xdc.runtime.System.ExtendFxn", new Proto.Adr("xdc_Int(*)(xdc_Char**,xdc_Char**,xdc_VaList*,xdc_runtime_System_ParseData*)", "PFn"));
        // struct System.Module_State
        po = (Proto.Obj)om.findStrict("xdc.runtime.System$$Module_State", "xdc.runtime");
        po.init("xdc.runtime.System.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("atexitHandlers", new Proto.Arr(new Proto.Adr("xdc_Void(*)(xdc_Int)", "PFv"), false), $$DEFAULT, "w");
                po.addFld("numAtexitHandlers", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("exitStatus", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
    }

    void ISystemSupport$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.ISystemSupport.Module", "xdc.runtime");
        po.init("xdc.runtime.ISystemSupport.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void SysStd$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.SysStd.Module", "xdc.runtime");
        po.init("xdc.runtime.SysStd.Module", om.findStrict("xdc.runtime.ISystemSupport.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void SysMin$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/SysMin.xs");
        om.bind("xdc.runtime.SysMin$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.SysMin.Module", "xdc.runtime");
        po.init("xdc.runtime.SysMin.Module", om.findStrict("xdc.runtime.ISystemSupport.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "xdc.runtime"), $$UNDEF, "wh");
                        po.addFld("bufSize", Proto.Elm.newCNum("(xdc_SizeT)"), 1024L, "w");
                        po.addFld("flushAtExit", $$T_Bool, true, "w");
                        po.addFld("sectionName", $$T_Str, null, "wh");
                        po.addFld("outputFxn", new Proto.Adr("xdc_Void(*)(xdc_Char*,xdc_UInt)", "PFv"), null, "w");
                        po.addFld("outputFunc", new Proto.Adr("xdc_Void(*)(xdc_Char*,xdc_UInt)", "PFv"), "&xdc_runtime_SysMin_output__I", "r");
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.SysMin$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.SysMin$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.SysMin$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.SysMin$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct SysMin.ModuleView
        po = (Proto.Obj)om.findStrict("xdc.runtime.SysMin$$ModuleView", "xdc.runtime");
        po.init("xdc.runtime.SysMin.ModuleView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("outBuf", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("outBufIndex", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("wrapped", $$T_Bool, $$UNDEF, "w");
        // struct SysMin.BufferEntryView
        po = (Proto.Obj)om.findStrict("xdc.runtime.SysMin$$BufferEntryView", "xdc.runtime");
        po.init("xdc.runtime.SysMin.BufferEntryView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("entry", $$T_Str, $$UNDEF, "w");
        // typedef SysMin.OutputFxn
        om.bind("xdc.runtime.SysMin.OutputFxn", new Proto.Adr("xdc_Void(*)(xdc_Char*,xdc_UInt)", "PFv"));
        // struct SysMin.Module_State
        po = (Proto.Obj)om.findStrict("xdc.runtime.SysMin$$Module_State", "xdc.runtime");
        po.init("xdc.runtime.SysMin.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("outbuf", new Proto.Arr(Proto.Elm.newCNum("(xdc_Char)"), false), $$DEFAULT, "w");
                po.addFld("outidx", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("wrapped", $$T_Bool, $$UNDEF, "w");
    }

    void Text$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/Text.xs");
        om.bind("xdc.runtime.Text$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.Text.Module", "xdc.runtime");
        po.init("xdc.runtime.Text.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("nameUnknown", $$T_Str, "{unknown-instance-name}", "w");
                        po.addFld("nameEmpty", $$T_Str, "{empty-instance-name}", "w");
                        po.addFld("nameStatic", $$T_Str, "{static-instance-name}", "w");
                        po.addFld("isLoaded", $$T_Bool, true, "w");
                        po.addFld("charTab", new Proto.Arr(Proto.Elm.newCNum("(xdc_Char)"), false), Global.newArray(new Object[]{0L}), "w");
                        po.addFld("nodeTab", new Proto.Arr((Proto)om.findStrict("xdc.runtime.Text.Node", "xdc.runtime"), false), Global.newArray(new Object[]{Global.newObject("left", 0L, "right", 0L)}), "w");
                        po.addFld("charCnt", Proto.Elm.newCNum("(xdc_Int16)"), 1L, "w");
                        po.addFld("nodeCnt", Proto.Elm.newCNum("(xdc_Int16)"), 1L, "w");
                        po.addFld("visitRopeFxn", new Proto.Adr("xdc_Void(*)(xdc_Bits16,xdc_Fxn,xdc_Ptr)", "PFv"), om.find("xdc.runtime.Text.visitRope"), "w");
                        po.addFld("visitRopeFxn2", new Proto.Adr("xdc_Void(*)(xdc_Bits16,xdc_Fxn,xdc_Ptr,xdc_String[])", "PFv"), om.find("xdc.runtime.Text.visitRope2"), "w");
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.Text$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.Text$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.Text$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.Text$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("defineRopeCord", (Proto.Fxn)om.findStrict("xdc.runtime.Text$$defineRopeCord", "xdc.runtime"), Global.get(cap, "defineRopeCord"));
                po.addFxn("defineRopeNode", (Proto.Fxn)om.findStrict("xdc.runtime.Text$$defineRopeNode", "xdc.runtime"), Global.get(cap, "defineRopeNode"));
                po.addFxn("fetchAddr", (Proto.Fxn)om.findStrict("xdc.runtime.Text$$fetchAddr", "xdc.runtime"), Global.get(cap, "fetchAddr"));
                po.addFxn("fetchCord", (Proto.Fxn)om.findStrict("xdc.runtime.Text$$fetchCord", "xdc.runtime"), Global.get(cap, "fetchCord"));
                po.addFxn("fetchId", (Proto.Fxn)om.findStrict("xdc.runtime.Text$$fetchId", "xdc.runtime"), Global.get(cap, "fetchId"));
                po.addFxn("fetchNode", (Proto.Fxn)om.findStrict("xdc.runtime.Text$$fetchNode", "xdc.runtime"), Global.get(cap, "fetchNode"));
                po.addFxn("genModNames", (Proto.Fxn)om.findStrict("xdc.runtime.Text$$genModNames", "xdc.runtime"), Global.get(cap, "genModNames"));
                po.addFxn("genPkgName", (Proto.Fxn)om.findStrict("xdc.runtime.Text$$genPkgName", "xdc.runtime"), Global.get(cap, "genPkgName"));
        // typedef Text.CordAddr
        om.bind("xdc.runtime.Text.CordAddr", new Proto.Adr("xdc_runtime_Types_CordAddr__*", "PE"));
        // typedef Text.Label
        om.bind("xdc.runtime.Text.Label", (Proto)om.findStrict("xdc.runtime.Types.Label", "xdc.runtime"));
        // typedef Text.RopeId
        om.bind("xdc.runtime.Text.RopeId", Proto.Elm.newCNum("(xdc_Bits16)"));
        // struct Text.Module_View
        po = (Proto.Obj)om.findStrict("xdc.runtime.Text$$Module_View", "xdc.runtime");
        po.init("xdc.runtime.Text.Module_View", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("charBase", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("nodeBase", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFxn("$xml", $$T_Met, Global.get("$$xml"));
        // struct Text.Node
        po = (Proto.Obj)om.findStrict("xdc.runtime.Text$$Node", "xdc.runtime");
        po.init("xdc.runtime.Text.Node", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("left", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("right", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
        // typedef Text.RopeVisitor
        om.bind("xdc.runtime.Text.RopeVisitor", new Proto.Adr("xdc_Bool(*)(xdc_Ptr,xdc_String)", "PFb"));
        // struct Text.MatchVisState
        po = (Proto.Obj)om.findStrict("xdc.runtime.Text$$MatchVisState", "xdc.runtime");
        po.init("xdc.runtime.Text.MatchVisState", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("pat", $$T_Str, $$UNDEF, "w");
                po.addFld("lenp", new Proto.Adr("xdc_Int*", "Pn"), $$UNDEF, "w");
                po.addFld("res", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
        // struct Text.PrintVisState
        po = (Proto.Obj)om.findStrict("xdc.runtime.Text$$PrintVisState", "xdc.runtime");
        po.init("xdc.runtime.Text.PrintVisState", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("bufp", new Proto.Adr("xdc_Char**", "PPn"), $$UNDEF, "w");
                po.addFld("len", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("res", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
        // typedef Text.VisitRopeFxn
        om.bind("xdc.runtime.Text.VisitRopeFxn", new Proto.Adr("xdc_Void(*)(xdc_Bits16,xdc_Fxn,xdc_Ptr)", "PFv"));
        // typedef Text.VisitRopeFxn2
        om.bind("xdc.runtime.Text.VisitRopeFxn2", new Proto.Adr("xdc_Void(*)(xdc_Bits16,xdc_Fxn,xdc_Ptr,xdc_String[])", "PFv"));
        // struct Text.Module_State
        po = (Proto.Obj)om.findStrict("xdc.runtime.Text$$Module_State", "xdc.runtime");
        po.init("xdc.runtime.Text.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("charBase", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("nodeBase", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void ITimestampClient$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.ITimestampClient.Module", "xdc.runtime");
        po.init("xdc.runtime.ITimestampClient.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void Timestamp$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/Timestamp.xs");
        om.bind("xdc.runtime.Timestamp$$capsule", cap);
        po = (Proto.Obj)om.findStrict("xdc.runtime.Timestamp.Module", "xdc.runtime");
        po.init("xdc.runtime.Timestamp.Module", om.findStrict("xdc.runtime.ITimestampClient.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFldV("SupportProxy", (Proto)om.findStrict("xdc.runtime.ITimestampProvider.Module", "xdc.runtime"), null, "wh", $$delegGet, $$delegSet);
        }//isCFG
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("xdc.runtime.Timestamp$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("xdc.runtime.Timestamp$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$static$init");
                if (fxn != null) om.bind("xdc.runtime.Timestamp$$module$static$init", true);
                if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("xdc.runtime.Timestamp$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void ITimestampProvider$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.ITimestampProvider.Module", "xdc.runtime");
        po.init("xdc.runtime.ITimestampProvider.Module", om.findStrict("xdc.runtime.ITimestampClient.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void TimestampNull$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.TimestampNull.Module", "xdc.runtime");
        po.init("xdc.runtime.TimestampNull.Module", om.findStrict("xdc.runtime.ITimestampProvider.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void TimestampStd$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.TimestampStd.Module", "xdc.runtime");
        po.init("xdc.runtime.TimestampStd.Module", om.findStrict("xdc.runtime.ITimestampProvider.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void Types$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.Types.Module", "xdc.runtime");
        po.init("xdc.runtime.Types.Module", om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        // typedef Types.ModuleId
        om.bind("xdc.runtime.Types.ModuleId", Proto.Elm.newCNum("(xdc_Bits16)"));
        // typedef Types.Event
        om.bind("xdc.runtime.Types.Event", Proto.Elm.newCNum("(xdc_Bits32)"));
        // typedef Types.EventId
        om.bind("xdc.runtime.Types.EventId", Proto.Elm.newCNum("(xdc_Bits32)"));
        // typedef Types.CordAddr
        om.bind("xdc.runtime.Types.CordAddr", new Proto.Adr("xdc_runtime_Types_CordAddr__*", "PE"));
        // typedef Types.GateRef
        om.bind("xdc.runtime.Types.GateRef", new Proto.Adr("xdc_runtime_Types_GateRef__*", "PE"));
        // typedef Types.RopeId
        om.bind("xdc.runtime.Types.RopeId", Proto.Elm.newCNum("(xdc_Bits16)"));
        // struct Types.Label
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$Label", "xdc.runtime");
        po.init("xdc.runtime.Types.Label", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("handle", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("modId", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("iname", $$T_Str, $$UNDEF, "w");
                po.addFld("named", $$T_Bool, $$UNDEF, "w");
        // struct Types.Site
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$Site", "xdc.runtime");
        po.init("xdc.runtime.Types.Site", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("mod", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
                po.addFld("file", $$T_Str, $$UNDEF, "w");
                po.addFld("line", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
        // struct Types.Timestamp64
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$Timestamp64", "xdc.runtime");
        po.init("xdc.runtime.Types.Timestamp64", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("hi", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("lo", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct Types.FreqHz
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$FreqHz", "xdc.runtime");
        po.init("xdc.runtime.Types.FreqHz", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("hi", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("lo", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
        // struct Types.Common$
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$Common$", "xdc.runtime");
        po.init("xdc.runtime.Types.Common$", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("diags_ASSERT", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("diags_ENTRY", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("diags_EXIT", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("diags_INTERNAL", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("diags_LIFECYCLE", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("diags_USER1", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("diags_USER2", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("diags_USER3", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("diags_USER4", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("diags_USER5", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("diags_USER6", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("diags_USER7", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("diags_USER8", (Proto)om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("fxntab", $$T_Bool, $$UNDEF, "w");
                po.addFld("gate", (Proto)om.findStrict("xdc.runtime.IGateProvider.Handle", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("gateParams", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("instanceHeap", (Proto)om.findStrict("xdc.runtime.IHeap.Handle", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("instanceSection", $$T_Str, $$UNDEF, "w");
                po.addFld("logger", (Proto)om.findStrict("xdc.runtime.ILogger.Handle", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("memoryPolicy", (Proto)om.findStrict("xdc.runtime.Types.CreatePolicy", "xdc.runtime"), $$UNDEF, "w");
                po.addFld("namedInstance", $$T_Bool, $$UNDEF, "w");
                po.addFld("namedModule", $$T_Bool, $$UNDEF, "w");
                po.addFld("romPatchTable", $$T_Bool, $$UNDEF, "w");
        // struct Types.__struct__1
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$__struct__1", "xdc.runtime");
        po.init("xdc.runtime.Types.__struct__1", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("type", $$T_Str, $$UNDEF, "w");
                po.addFld("metaArgs", $$T_Obj, $$UNDEF, "w");
        // struct Types.__struct__2
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$__struct__2", "xdc.runtime");
        po.init("xdc.runtime.Types.__struct__2", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("id", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("logger", $$T_Str, $$UNDEF, "w");
                po.addFld("diagsMask", $$T_Str, $$UNDEF, "w");
        // struct Types.__struct__3
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$__struct__3", "xdc.runtime");
        po.init("xdc.runtime.Types.__struct__3", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("id", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("msg", $$T_Str, $$UNDEF, "w");
        // struct Types.RtaDecoderData
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$RtaDecoderData", "xdc.runtime");
        po.init("xdc.runtime.Types.RtaDecoderData", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("targetName", $$T_Str, $$UNDEF, "w");
                po.addFld("binaryParser", $$T_Str, $$UNDEF, "w");
                po.addFld("endian", $$T_Str, $$UNDEF, "w");
                po.addFld("bitsPerChar", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("argSize", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("eventSize", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("loggers", new Proto.Arr((Proto)om.findStrict("xdc.runtime.Types.__struct__1", "xdc.runtime"), false), $$DEFAULT, "w");
                po.addFld("modMap", new Proto.Map((Proto)om.findStrict("xdc.runtime.Types.__struct__2", "xdc.runtime")), $$DEFAULT, "w");
                po.addFld("evtMap", new Proto.Map((Proto)om.findStrict("xdc.runtime.Types.__struct__3", "xdc.runtime")), $$DEFAULT, "w");
                po.addFxn("$xml", $$T_Met, Global.get("$$xml"));
        // struct Types.ViewInfo
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$ViewInfo", "xdc.runtime");
        po.init("xdc.runtime.Types.ViewInfo", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("viewType", $$T_Str, $$UNDEF, "w");
                po.addFld("viewFxn", $$T_Str, $$UNDEF, "w");
                po.addFld("fields", new Proto.Arr($$T_Str, false), $$DEFAULT, "w");
        // typedef Types.LoggerFxn4
        om.bind("xdc.runtime.Types.LoggerFxn4", new Proto.Adr("xdc_Void(*)(xdc_Ptr,xdc_Bits32,xdc_IArg,xdc_IArg,xdc_IArg,xdc_IArg)", "PFv"));
        // typedef Types.LoggerFxn8
        om.bind("xdc.runtime.Types.LoggerFxn8", new Proto.Adr("xdc_Void(*)(xdc_Ptr,xdc_Bits32,xdc_IArg,xdc_IArg,xdc_IArg,xdc_IArg,xdc_IArg,xdc_IArg,xdc_IArg,xdc_IArg)", "PFv"));
        // struct Types.Vec
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$Vec", "xdc.runtime");
        po.init("xdc.runtime.Types.Vec", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("len", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("arr", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct Types.Link
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$Link", "xdc.runtime");
        po.init("xdc.runtime.Types.Link", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("next", new Proto.Adr("xdc_runtime_Types_Link*", "PS"), $$UNDEF, "w");
                po.addFld("prev", new Proto.Adr("xdc_runtime_Types_Link*", "PS"), $$UNDEF, "w");
        // struct Types.ModHdr
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$ModHdr", "xdc.runtime");
        po.init("xdc.runtime.Types.ModHdr", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("link", (Proto)om.findStrict("xdc.runtime.Types.Link", "xdc.runtime"), $$DEFAULT, "w");
                po.addFld("instArrBeg", new Proto.Adr("xdc_UChar*", "Pn"), $$UNDEF, "w");
                po.addFld("instArrEnd", new Proto.Adr("xdc_UChar*", "Pn"), $$UNDEF, "w");
                po.addFld("instSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("curInst", new Proto.Adr("xdc_UChar*", "Pn"), $$UNDEF, "w");
                po.addFld("diagsMask", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
        // struct Types.ModHdrS
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$ModHdrS", "xdc.runtime");
        po.init("xdc.runtime.Types.ModHdrS", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("diagsMask", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
        // struct Types.InstHdr
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$InstHdr", "xdc.runtime");
        po.init("xdc.runtime.Types.InstHdr", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("link", (Proto)om.findStrict("xdc.runtime.Types.Link", "xdc.runtime"), $$DEFAULT, "w");
        // struct Types.PrmsHdr
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$PrmsHdr", "xdc.runtime");
        po.init("xdc.runtime.Types.PrmsHdr", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("size", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("self", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("modFxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("instPrms", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        // struct Types.Base
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$Base", "xdc.runtime");
        po.init("xdc.runtime.Types.Base", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("base", new Proto.Adr("xdc_runtime_Types_Base*", "PS"), $$UNDEF, "w");
        // struct Types.SysFxns
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$SysFxns", "xdc.runtime");
        po.init("xdc.runtime.Types.SysFxns", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("__create", new Proto.Adr("xdc_Ptr(*)(xdc_Ptr,xdc_SizeT,xdc_Ptr,xdc_Ptr,xdc_SizeT,xdc_runtime_Error_Block*)", "PFPv"), $$UNDEF, "w");
                po.addFld("__delete", new Proto.Adr("xdc_Void(*)(xdc_Ptr)", "PFv"), $$UNDEF, "w");
                po.addFld("__label", $$T_Obj, $$UNDEF, "w");
                po.addFld("__mid", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
        // struct Types.SysFxns2
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$SysFxns2", "xdc.runtime");
        po.init("xdc.runtime.Types.SysFxns2", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("__create", new Proto.Adr("xdc_Ptr(*)(xdc_Ptr,xdc_SizeT,xdc_Ptr,xdc_UChar*,xdc_SizeT,xdc_runtime_Error_Block*)", "PFPv"), $$UNDEF, "w");
                po.addFld("__delete", new Proto.Adr("xdc_Void(*)(xdc_Ptr)", "PFv"), $$UNDEF, "w");
                po.addFld("__label", $$T_Obj, $$UNDEF, "w");
                po.addFld("__mid", Proto.Elm.newCNum("(xdc_Bits16)"), $$UNDEF, "w");
    }

    void IInstance$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.IInstance.Module", "xdc.runtime");
        po.init("xdc.runtime.IInstance.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.IInstance.Instance", "xdc.runtime");
        po.init("xdc.runtime.IInstance.Instance", $$Instance);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("name", $$T_Str, null, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.IInstance$$Params", "xdc.runtime");
        po.init("xdc.runtime.IInstance.Params", $$Params);
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("name", $$T_Str, null, "w");
        }//isCFG
    }

    void LoggerBuf_TimestampProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf_TimestampProxy.Module", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf_TimestampProxy.Module", om.findStrict("xdc.runtime.ITimestampClient.Module", "xdc.runtime"));
                po.addFld("delegate$", (Proto)om.findStrict("xdc.runtime.ITimestampClient.Module", "xdc.runtime"), null, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void LoggerBuf_Module_GateProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Module", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf_Module_GateProxy.Module", om.findStrict("xdc.runtime.IGateProvider.Module", "xdc.runtime"));
                po.addFld("delegate$", (Proto)om.findStrict("xdc.runtime.IGateProvider.Module", "xdc.runtime"), null, "wh");
                po.addFld("abstractInstances$", $$T_Bool, false, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy$$create", "xdc.runtime"), Global.get("xdc$runtime$LoggerBuf_Module_GateProxy$$create"));
        }//isCFG
                po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "xdc.runtime"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Instance", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf_Module_GateProxy.Instance", om.findStrict("xdc.runtime.IGateProvider.Instance", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy$$Params", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf_Module_GateProxy.Params", om.findStrict("xdc.runtime.IGateProvider$$Params", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy$$Object", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf_Module_GateProxy.Object", om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Instance", "xdc.runtime"));
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy$$Instance_State", "xdc.runtime");
        po.init("xdc.runtime.LoggerBuf_Module_GateProxy.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void LoggerSys_TimestampProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerSys_TimestampProxy.Module", "xdc.runtime");
        po.init("xdc.runtime.LoggerSys_TimestampProxy.Module", om.findStrict("xdc.runtime.ITimestampClient.Module", "xdc.runtime"));
                po.addFld("delegate$", (Proto)om.findStrict("xdc.runtime.ITimestampClient.Module", "xdc.runtime"), null, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void Main_Module_GateProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.Main_Module_GateProxy.Module", "xdc.runtime");
        po.init("xdc.runtime.Main_Module_GateProxy.Module", om.findStrict("xdc.runtime.IGateProvider.Module", "xdc.runtime"));
                po.addFld("delegate$", (Proto)om.findStrict("xdc.runtime.IGateProvider.Module", "xdc.runtime"), null, "wh");
                po.addFld("abstractInstances$", $$T_Bool, false, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.runtime.Main_Module_GateProxy$$create", "xdc.runtime"), Global.get("xdc$runtime$Main_Module_GateProxy$$create"));
        }//isCFG
                po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "xdc.runtime"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("xdc.runtime.Main_Module_GateProxy.Instance", "xdc.runtime");
        po.init("xdc.runtime.Main_Module_GateProxy.Instance", om.findStrict("xdc.runtime.IGateProvider.Instance", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.Main_Module_GateProxy$$Params", "xdc.runtime");
        po.init("xdc.runtime.Main_Module_GateProxy.Params", om.findStrict("xdc.runtime.IGateProvider$$Params", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.Main_Module_GateProxy$$Object", "xdc.runtime");
        po.init("xdc.runtime.Main_Module_GateProxy.Object", om.findStrict("xdc.runtime.Main_Module_GateProxy.Instance", "xdc.runtime"));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Main_Module_GateProxy$$Instance_State", "xdc.runtime");
        po.init("xdc.runtime.Main_Module_GateProxy.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void Memory_HeapProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory_HeapProxy.Module", "xdc.runtime");
        po.init("xdc.runtime.Memory_HeapProxy.Module", om.findStrict("xdc.runtime.IHeap.Module", "xdc.runtime"));
                po.addFld("delegate$", (Proto)om.findStrict("xdc.runtime.IHeap.Module", "xdc.runtime"), null, "wh");
                po.addFld("abstractInstances$", $$T_Bool, false, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.runtime.Memory_HeapProxy$$create", "xdc.runtime"), Global.get("xdc$runtime$Memory_HeapProxy$$create"));
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory_HeapProxy.Instance", "xdc.runtime");
        po.init("xdc.runtime.Memory_HeapProxy.Instance", om.findStrict("xdc.runtime.IHeap.Instance", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory_HeapProxy$$Params", "xdc.runtime");
        po.init("xdc.runtime.Memory_HeapProxy.Params", om.findStrict("xdc.runtime.IHeap$$Params", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory_HeapProxy$$Object", "xdc.runtime");
        po.init("xdc.runtime.Memory_HeapProxy.Object", om.findStrict("xdc.runtime.Memory_HeapProxy.Instance", "xdc.runtime"));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory_HeapProxy$$Instance_State", "xdc.runtime");
        po.init("xdc.runtime.Memory_HeapProxy.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void System_SupportProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.System_SupportProxy.Module", "xdc.runtime");
        po.init("xdc.runtime.System_SupportProxy.Module", om.findStrict("xdc.runtime.ISystemSupport.Module", "xdc.runtime"));
                po.addFld("delegate$", (Proto)om.findStrict("xdc.runtime.ISystemSupport.Module", "xdc.runtime"), null, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void System_Module_GateProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.System_Module_GateProxy.Module", "xdc.runtime");
        po.init("xdc.runtime.System_Module_GateProxy.Module", om.findStrict("xdc.runtime.IGateProvider.Module", "xdc.runtime"));
                po.addFld("delegate$", (Proto)om.findStrict("xdc.runtime.IGateProvider.Module", "xdc.runtime"), null, "wh");
                po.addFld("abstractInstances$", $$T_Bool, false, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("xdc.runtime.System_Module_GateProxy$$create", "xdc.runtime"), Global.get("xdc$runtime$System_Module_GateProxy$$create"));
        }//isCFG
                po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "xdc.runtime"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("xdc.runtime.System_Module_GateProxy.Instance", "xdc.runtime");
        po.init("xdc.runtime.System_Module_GateProxy.Instance", om.findStrict("xdc.runtime.IGateProvider.Instance", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.System_Module_GateProxy$$Params", "xdc.runtime");
        po.init("xdc.runtime.System_Module_GateProxy.Params", om.findStrict("xdc.runtime.IGateProvider$$Params", "xdc.runtime"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("xdc.runtime.System_Module_GateProxy$$Object", "xdc.runtime");
        po.init("xdc.runtime.System_Module_GateProxy.Object", om.findStrict("xdc.runtime.System_Module_GateProxy.Instance", "xdc.runtime"));
        po = (Proto.Obj)om.findStrict("xdc.runtime.System_Module_GateProxy$$Instance_State", "xdc.runtime");
        po.init("xdc.runtime.System_Module_GateProxy.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void Timestamp_SupportProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("xdc.runtime.Timestamp_SupportProxy.Module", "xdc.runtime");
        po.init("xdc.runtime.Timestamp_SupportProxy.Module", om.findStrict("xdc.runtime.ITimestampProvider.Module", "xdc.runtime"));
                po.addFld("delegate$", (Proto)om.findStrict("xdc.runtime.ITimestampProvider.Module", "xdc.runtime"), null, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
    }

    void IModule$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.IModule", "xdc.runtime");
    }

    void Assert$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Assert", "xdc.runtime");
    }

    void Core$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Core", "xdc.runtime");
        vo.bind("ObjDesc$fetchDesc", Global.newObject("type", "xdc.runtime.Core.ObjDesc", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Core$$ObjDesc", "xdc.runtime");
        po.bind("modLink$fetchDesc", Global.newObject("type", "xdc.runtime.Types.Link", "isScalar", false));
    }

    void Defaults$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Defaults", "xdc.runtime");
    }

    void Diags$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Diags", "xdc.runtime");
        vo.bind("DictElem$fetchDesc", Global.newObject("type", "xdc.runtime.Diags.DictElem", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Diags$$DictElem", "xdc.runtime");
    }

    void Error$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Error", "xdc.runtime");
        vo.bind("Data$fetchDesc", Global.newObject("type", "xdc.runtime.Error.Data", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Error$$Data", "xdc.runtime");
        vo.bind("Block$fetchDesc", Global.newObject("type", "xdc.runtime.Error.Block", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Error$$Block", "xdc.runtime");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "xdc.runtime.Error.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Error$$Module_State", "xdc.runtime");
    }

    void Gate$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Gate", "xdc.runtime");
    }

    void IGateProvider$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.IGateProvider", "xdc.runtime");
    }

    void GateNull$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.GateNull", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.GateNull$$Instance_State", "xdc.runtime");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void Log$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Log", "xdc.runtime");
        vo.bind("EventRec$fetchDesc", Global.newObject("type", "xdc.runtime.Log.EventRec", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Log$$EventRec", "xdc.runtime");
    }

    void ILogger$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.ILogger", "xdc.runtime");
    }

    void LoggerBuf$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.LoggerBuf", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf$$Instance_State", "xdc.runtime");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Entry$fetchDesc", Global.newObject("type", "xdc.runtime.LoggerBuf.Entry", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf$$Entry", "xdc.runtime");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "xdc.runtime.LoggerBuf.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf$$Instance_State", "xdc.runtime");
        po.bind("entryArr$fetchDesc", Global.newObject("type", "xdc.runtime.LoggerBuf.Entry", "isScalar", false));
        po.bind("curEntry$fetchDesc", Global.newObject("type", "xdc.runtime.LoggerBuf.Entry", "isScalar", false));
        po.bind("endEntry$fetchDesc", Global.newObject("type", "xdc.runtime.LoggerBuf.Entry", "isScalar", false));
        po.bind("readEntry$fetchDesc", Global.newObject("type", "xdc.runtime.LoggerBuf.Entry", "isScalar", false));
    }

    void LoggerSys$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.LoggerSys", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerSys$$Instance_State", "xdc.runtime");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void Main$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Main", "xdc.runtime");
    }

    void Memory$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Memory", "xdc.runtime");
        vo.bind("Stats$fetchDesc", Global.newObject("type", "xdc.runtime.Memory.Stats", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory$$Stats", "xdc.runtime");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "xdc.runtime.Memory.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory$$Module_State", "xdc.runtime");
    }

    void IHeap$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.IHeap", "xdc.runtime");
    }

    void HeapMin$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.HeapMin", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapMin$$Instance_State", "xdc.runtime");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "xdc.runtime.HeapMin.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapMin$$Instance_State", "xdc.runtime");
        po.bind("buf$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Char", "isScalar", true));
    }

    void HeapStd$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.HeapStd", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapStd$$Instance_State", "xdc.runtime");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "xdc.runtime.HeapStd.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapStd$$Module_State", "xdc.runtime");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "xdc.runtime.HeapStd.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapStd$$Instance_State", "xdc.runtime");
    }

    void Rta$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Rta", "xdc.runtime");
        vo.bind("CommandPacket$fetchDesc", Global.newObject("type", "xdc.runtime.Rta.CommandPacket", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Rta$$CommandPacket", "xdc.runtime");
        vo.bind("ResponsePacket$fetchDesc", Global.newObject("type", "xdc.runtime.Rta.ResponsePacket", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Rta$$ResponsePacket", "xdc.runtime");
    }

    void Startup$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Startup", "xdc.runtime");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "xdc.runtime.Startup.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Startup$$Module_State", "xdc.runtime");
    }

    void Reset$$ROV()
    {
    }

    void System$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.System", "xdc.runtime");
        vo.bind("ParseData$fetchDesc", Global.newObject("type", "xdc.runtime.System.ParseData", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.System$$ParseData", "xdc.runtime");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "xdc.runtime.System.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.System$$Module_State", "xdc.runtime");
    }

    void ISystemSupport$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.ISystemSupport", "xdc.runtime");
    }

    void SysStd$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.SysStd", "xdc.runtime");
    }

    void SysMin$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.SysMin", "xdc.runtime");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "xdc.runtime.SysMin.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.SysMin$$Module_State", "xdc.runtime");
        po.bind("outbuf$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Char", "isScalar", true));
    }

    void Text$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Text", "xdc.runtime");
        vo.bind("Node$fetchDesc", Global.newObject("type", "xdc.runtime.Text.Node", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Text$$Node", "xdc.runtime");
        vo.bind("MatchVisState$fetchDesc", Global.newObject("type", "xdc.runtime.Text.MatchVisState", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Text$$MatchVisState", "xdc.runtime");
        vo.bind("PrintVisState$fetchDesc", Global.newObject("type", "xdc.runtime.Text.PrintVisState", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Text$$PrintVisState", "xdc.runtime");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "xdc.runtime.Text.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Text$$Module_State", "xdc.runtime");
    }

    void ITimestampClient$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.ITimestampClient", "xdc.runtime");
    }

    void Timestamp$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Timestamp", "xdc.runtime");
    }

    void ITimestampProvider$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.ITimestampProvider", "xdc.runtime");
    }

    void TimestampNull$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.TimestampNull", "xdc.runtime");
    }

    void TimestampStd$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.TimestampStd", "xdc.runtime");
    }

    void Types$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Types", "xdc.runtime");
        vo.bind("Label$fetchDesc", Global.newObject("type", "xdc.runtime.Types.Label", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$Label", "xdc.runtime");
        vo.bind("Site$fetchDesc", Global.newObject("type", "xdc.runtime.Types.Site", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$Site", "xdc.runtime");
        vo.bind("Timestamp64$fetchDesc", Global.newObject("type", "xdc.runtime.Types.Timestamp64", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$Timestamp64", "xdc.runtime");
        vo.bind("FreqHz$fetchDesc", Global.newObject("type", "xdc.runtime.Types.FreqHz", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$FreqHz", "xdc.runtime");
        vo.bind("Vec$fetchDesc", Global.newObject("type", "xdc.runtime.Types.Vec", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$Vec", "xdc.runtime");
        vo.bind("Link$fetchDesc", Global.newObject("type", "xdc.runtime.Types.Link", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$Link", "xdc.runtime");
        po.bind("next$fetchDesc", Global.newObject("type", "xdc.runtime.Types.Link", "isScalar", false));
        po.bind("prev$fetchDesc", Global.newObject("type", "xdc.runtime.Types.Link", "isScalar", false));
        vo.bind("ModHdr$fetchDesc", Global.newObject("type", "xdc.runtime.Types.ModHdr", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$ModHdr", "xdc.runtime");
        vo.bind("ModHdrS$fetchDesc", Global.newObject("type", "xdc.runtime.Types.ModHdrS", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$ModHdrS", "xdc.runtime");
        vo.bind("InstHdr$fetchDesc", Global.newObject("type", "xdc.runtime.Types.InstHdr", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$InstHdr", "xdc.runtime");
        vo.bind("PrmsHdr$fetchDesc", Global.newObject("type", "xdc.runtime.Types.PrmsHdr", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$PrmsHdr", "xdc.runtime");
        vo.bind("Base$fetchDesc", Global.newObject("type", "xdc.runtime.Types.Base", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$Base", "xdc.runtime");
        po.bind("base$fetchDesc", Global.newObject("type", "xdc.runtime.Types.Base", "isScalar", false));
        vo.bind("SysFxns$fetchDesc", Global.newObject("type", "xdc.runtime.Types.SysFxns", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$SysFxns", "xdc.runtime");
        vo.bind("SysFxns2$fetchDesc", Global.newObject("type", "xdc.runtime.Types.SysFxns2", "isScalar", false));
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types$$SysFxns2", "xdc.runtime");
    }

    void IInstance$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.IInstance", "xdc.runtime");
    }

    void LoggerBuf_TimestampProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.LoggerBuf_TimestampProxy", "xdc.runtime");
    }

    void LoggerBuf_Module_GateProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy$$Instance_State", "xdc.runtime");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void LoggerSys_TimestampProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.LoggerSys_TimestampProxy", "xdc.runtime");
    }

    void Main_Module_GateProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Main_Module_GateProxy", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Main_Module_GateProxy$$Instance_State", "xdc.runtime");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void Memory_HeapProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Memory_HeapProxy", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory_HeapProxy$$Instance_State", "xdc.runtime");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void System_SupportProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.System_SupportProxy", "xdc.runtime");
    }

    void System_Module_GateProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.System_Module_GateProxy", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.System_Module_GateProxy$$Instance_State", "xdc.runtime");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void Timestamp_SupportProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Timestamp_SupportProxy", "xdc.runtime");
    }

    void $$SINGLETONS()
    {
        pkgP.init("xdc.runtime.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "xdc.runtime"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xdc/runtime/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "xdc.runtime"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "xdc.runtime"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "xdc.runtime"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "xdc.runtime"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "xdc.runtime"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "xdc.runtime"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "xdc.runtime", Value.DEFAULT, false);
        pkgV.bind("$name", "xdc.runtime");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "xdc.runtime.");
        pkgV.bind("$vers", Global.newArray("2, 0, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['xdc.runtime'];\n");
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

    void IModule$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.IModule", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.IModule.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.IModule", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IModule", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IModule");
        vo.seal(null);
    }

    void Assert$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Assert", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Assert.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Assert", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.Assert$$capsule", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("Desc", om.findStrict("xdc.runtime.Assert.Desc", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Assert.Desc", "xdc.runtime"));
        vo.bind("Id", om.findStrict("xdc.runtime.Assert.Id", "xdc.runtime"));
        mcfgs.add("E_assertFailed");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("raise", om.findStrict("xdc.runtime.Assert.raise", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Assert_Handle__label__E", "xdc_runtime_Assert_Module__startupDone__E", "xdc_runtime_Assert_Object__create__E", "xdc_runtime_Assert_Object__delete__E", "xdc_runtime_Assert_Object__destruct__E", "xdc_runtime_Assert_Object__get__E", "xdc_runtime_Assert_Object__first__E", "xdc_runtime_Assert_Object__next__E", "xdc_runtime_Assert_Params__init__E", "xdc_runtime_Assert_Proxy__abstract__E", "xdc_runtime_Assert_Proxy__delegate__E", "xdc_runtime_Assert_isTrue__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_assertFailed"));
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Assert", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Assert");
    }

    void Core$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Core", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Core.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Core", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        mcfgs.add("A_initializedParams");
        vo.bind("ObjDesc", om.findStrict("xdc.runtime.Core.ObjDesc", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Core.ObjDesc", "xdc.runtime"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("assignLabel", om.findStrict("xdc.runtime.Core.assignLabel", "xdc.runtime"));
        vo.bind("assignParams", om.findStrict("xdc.runtime.Core.assignParams", "xdc.runtime"));
        vo.bind("createObject", om.findStrict("xdc.runtime.Core.createObject", "xdc.runtime"));
        vo.bind("deleteObject", om.findStrict("xdc.runtime.Core.deleteObject", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Core_Handle__label__E", "xdc_runtime_Core_Module__startupDone__E", "xdc_runtime_Core_Object__create__E", "xdc_runtime_Core_Object__delete__E", "xdc_runtime_Core_Object__destruct__E", "xdc_runtime_Core_Object__get__E", "xdc_runtime_Core_Object__first__E", "xdc_runtime_Core_Object__next__E", "xdc_runtime_Core_Params__init__E", "xdc_runtime_Core_Proxy__abstract__E", "xdc_runtime_Core_Proxy__delegate__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_initializedParams"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Core", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Core");
    }

    void Defaults$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Defaults", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Defaults.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Defaults", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.Defaults$$capsule", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Defaults_Handle__label__E", "xdc_runtime_Defaults_Module__startupDone__E", "xdc_runtime_Defaults_Object__create__E", "xdc_runtime_Defaults_Object__delete__E", "xdc_runtime_Defaults_Object__destruct__E", "xdc_runtime_Defaults_Object__get__E", "xdc_runtime_Defaults_Object__first__E", "xdc_runtime_Defaults_Object__next__E", "xdc_runtime_Defaults_Params__init__E", "xdc_runtime_Defaults_Proxy__abstract__E", "xdc_runtime_Defaults_Proxy__delegate__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Defaults", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Defaults");
    }

    void Diags$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Diags", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Diags.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Diags", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.Diags$$capsule", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("Mode", om.findStrict("xdc.runtime.Diags.Mode", "xdc.runtime"));
        vo.bind("Mask", om.findStrict("xdc.runtime.Diags.Mask", "xdc.runtime"));
        mcfgs.add("setMaskEnabled");
        mcfgs.add("dictBase");
        vo.bind("DictElem", om.findStrict("xdc.runtime.Diags.DictElem", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Diags.DictElem", "xdc.runtime"));
        vo.bind("ALWAYS_OFF", om.findStrict("xdc.runtime.Diags.ALWAYS_OFF", "xdc.runtime"));
        vo.bind("ALWAYS_ON", om.findStrict("xdc.runtime.Diags.ALWAYS_ON", "xdc.runtime"));
        vo.bind("RUNTIME_OFF", om.findStrict("xdc.runtime.Diags.RUNTIME_OFF", "xdc.runtime"));
        vo.bind("RUNTIME_ON", om.findStrict("xdc.runtime.Diags.RUNTIME_ON", "xdc.runtime"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("setMask", om.findStrict("xdc.runtime.Diags.setMask", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Diags_Handle__label__E", "xdc_runtime_Diags_Module__startupDone__E", "xdc_runtime_Diags_Object__create__E", "xdc_runtime_Diags_Object__delete__E", "xdc_runtime_Diags_Object__destruct__E", "xdc_runtime_Diags_Object__get__E", "xdc_runtime_Diags_Object__first__E", "xdc_runtime_Diags_Object__next__E", "xdc_runtime_Diags_Params__init__E", "xdc_runtime_Diags_Proxy__abstract__E", "xdc_runtime_Diags_Proxy__delegate__E", "xdc_runtime_Diags_query__E", "xdc_runtime_Diags_setMask__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", "./Diags.xdt");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "setMask", "entry", "\"%s\"", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./Diags.xdt");
        pkgV.bind("Diags", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Diags");
    }

    void Error$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Error", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Error.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Error", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.Error$$capsule", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("Policy", om.findStrict("xdc.runtime.Error.Policy", "xdc.runtime"));
        vo.bind("Desc", om.findStrict("xdc.runtime.Error.Desc", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Error.Desc", "xdc.runtime"));
        vo.bind("Id", om.findStrict("xdc.runtime.Error.Id", "xdc.runtime"));
        vo.bind("Data", om.findStrict("xdc.runtime.Error.Data", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Error.Data", "xdc.runtime"));
        vo.bind("Block", om.findStrict("xdc.runtime.Error.Block", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Error.Block", "xdc.runtime"));
        mcfgs.add("E_generic");
        mcfgs.add("E_memory");
        mcfgs.add("policy");
        mcfgs.add("raiseHook");
        mcfgs.add("maxDepth");
        vo.bind("Module_State", om.findStrict("xdc.runtime.Error.Module_State", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Error.Module_State", "xdc.runtime"));
        vo.bind("TERMINATE", om.findStrict("xdc.runtime.Error.TERMINATE", "xdc.runtime"));
        vo.bind("UNWIND", om.findStrict("xdc.runtime.Error.UNWIND", "xdc.runtime"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("check", om.findStrict("xdc.runtime.Error.check", "xdc.runtime"));
        vo.bind("getData", om.findStrict("xdc.runtime.Error.getData", "xdc.runtime"));
        vo.bind("getCode", om.findStrict("xdc.runtime.Error.getCode", "xdc.runtime"));
        vo.bind("getId", om.findStrict("xdc.runtime.Error.getId", "xdc.runtime"));
        vo.bind("getMsg", om.findStrict("xdc.runtime.Error.getMsg", "xdc.runtime"));
        vo.bind("getSite", om.findStrict("xdc.runtime.Error.getSite", "xdc.runtime"));
        vo.bind("init", om.findStrict("xdc.runtime.Error.init", "xdc.runtime"));
        vo.bind("print", om.findStrict("xdc.runtime.Error.print", "xdc.runtime"));
        vo.bind("raiseX", om.findStrict("xdc.runtime.Error.raiseX", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Error_Handle__label__E", "xdc_runtime_Error_Module__startupDone__E", "xdc_runtime_Error_Object__create__E", "xdc_runtime_Error_Object__delete__E", "xdc_runtime_Error_Object__destruct__E", "xdc_runtime_Error_Object__get__E", "xdc_runtime_Error_Object__first__E", "xdc_runtime_Error_Object__next__E", "xdc_runtime_Error_Params__init__E", "xdc_runtime_Error_Proxy__abstract__E", "xdc_runtime_Error_Proxy__delegate__E", "xdc_runtime_Error_check__E", "xdc_runtime_Error_getData__E", "xdc_runtime_Error_getCode__E", "xdc_runtime_Error_getId__E", "xdc_runtime_Error_getMsg__E", "xdc_runtime_Error_getSite__E", "xdc_runtime_Error_idToCode__E", "xdc_runtime_Error_init__E", "xdc_runtime_Error_print__E", "xdc_runtime_Error_raise__E", "xdc_runtime_Error_raiseX__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_generic", "E_memory"));
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "check", "entry", "%p", "exit", "%d"));
        loggables.add(Global.newObject("name", "getData", "entry", "%p", "exit", "%p"));
        loggables.add(Global.newObject("name", "getCode", "entry", "%p", "exit", "0x%x"));
        loggables.add(Global.newObject("name", "getId", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "getMsg", "entry", "%p", "exit", "\"%s\""));
        loggables.add(Global.newObject("name", "getSite", "entry", "%p", "exit", "%p"));
        loggables.add(Global.newObject("name", "init", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "print", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "raiseX", "entry", "%p, %d, \"%s\", %d", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Error", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Error");
    }

    void Gate$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Gate", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Gate.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Gate", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.Gate$$capsule", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("Ref", om.findStrict("xdc.runtime.Gate.Ref", "xdc.runtime"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("enterSystem", om.findStrict("xdc.runtime.Gate.enterSystem", "xdc.runtime"));
        vo.bind("leaveSystem", om.findStrict("xdc.runtime.Gate.leaveSystem", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Gate_Handle__label__E", "xdc_runtime_Gate_Module__startupDone__E", "xdc_runtime_Gate_Object__create__E", "xdc_runtime_Gate_Object__delete__E", "xdc_runtime_Gate_Object__destruct__E", "xdc_runtime_Gate_Object__get__E", "xdc_runtime_Gate_Object__first__E", "xdc_runtime_Gate_Object__next__E", "xdc_runtime_Gate_Params__init__E", "xdc_runtime_Gate_Proxy__abstract__E", "xdc_runtime_Gate_Proxy__delegate__E", "xdc_runtime_Gate_allocInstance__E", "xdc_runtime_Gate_freeInstance__E", "xdc_runtime_Gate_enterInstance__E", "xdc_runtime_Gate_enterModule__E", "xdc_runtime_Gate_enterSystem__E", "xdc_runtime_Gate_leaveInstance__E", "xdc_runtime_Gate_leaveModule__E", "xdc_runtime_Gate_leaveSystem__E", "xdc_runtime_Gate_canBlock__E", "xdc_runtime_Gate_canBePreempted__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "enterSystem", "entry", "", "exit", "%p"));
        loggables.add(Global.newObject("name", "leaveSystem", "entry", "%p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Gate", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Gate");
    }

    void IGateProvider$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.IGateProvider", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.IGateProvider.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.IGateProvider", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", om.findStrict("xdc.runtime.IGateProvider$$capsule", "xdc.runtime"));
        vo.bind("Instance", om.findStrict("xdc.runtime.IGateProvider.Instance", "xdc.runtime"));
        vo.bind("Params", om.findStrict("xdc.runtime.IGateProvider.Params", "xdc.runtime"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.runtime.IGateProvider.Params", "xdc.runtime")).newInstance());
        vo.bind("Handle", om.findStrict("xdc.runtime.IGateProvider.Handle", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IGateProvider", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IGateProvider");
        vo.seal(null);
    }

    void GateNull$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.GateNull", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.GateNull.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.GateNull", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.GateNull$$capsule", "xdc.runtime"));
        vo.bind("Instance", om.findStrict("xdc.runtime.GateNull.Instance", "xdc.runtime"));
        vo.bind("Params", om.findStrict("xdc.runtime.GateNull.Params", "xdc.runtime"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.runtime.GateNull.Params", "xdc.runtime")).newInstance());
        vo.bind("Handle", om.findStrict("xdc.runtime.GateNull.Handle", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
            vo.bind("__initObject", Global.get("xdc$runtime$GateNull$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("xdc.runtime.GateNull.query", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_GateNull_Handle__label__E", "xdc_runtime_GateNull_Module__startupDone__E", "xdc_runtime_GateNull_Object__create__E", "xdc_runtime_GateNull_Object__delete__E", "xdc_runtime_GateNull_Object__destruct__E", "xdc_runtime_GateNull_Object__get__E", "xdc_runtime_GateNull_Object__first__E", "xdc_runtime_GateNull_Object__next__E", "xdc_runtime_GateNull_Params__init__E", "xdc_runtime_GateNull_Proxy__abstract__E", "xdc_runtime_GateNull_Proxy__delegate__E", "xdc_runtime_GateNull_query__E", "xdc_runtime_GateNull_enter__E", "xdc_runtime_GateNull_leave__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.runtime.GateNull.Object", "xdc.runtime"));
        vo.bind("Instance_State", om.findStrict("xdc.runtime.GateNull.Instance_State", "xdc.runtime"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "query", "entry", "%d", "exit", "%d"));
        loggables.add(Global.newObject("name", "enter", "entry", "%p", "exit", "%p"));
        loggables.add(Global.newObject("name", "leave", "entry", "%p, %p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("GateNull", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("GateNull");
    }

    void Log$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Log", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Log.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Log", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.Log$$capsule", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("EventDesc", om.findStrict("xdc.runtime.Log.EventDesc", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Log.EventDesc", "xdc.runtime"));
        vo.bind("EventRec", om.findStrict("xdc.runtime.Log.EventRec", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Log.EventRec", "xdc.runtime"));
        vo.bind("Event", om.findStrict("xdc.runtime.Log.Event", "xdc.runtime"));
        vo.bind("EventId", om.findStrict("xdc.runtime.Log.EventId", "xdc.runtime"));
        mcfgs.add("L_construct");
        mcfgs.add("L_create");
        mcfgs.add("L_destruct");
        mcfgs.add("L_delete");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("doPrint", om.findStrict("xdc.runtime.Log.doPrint", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Log_Handle__label__E", "xdc_runtime_Log_Module__startupDone__E", "xdc_runtime_Log_Object__create__E", "xdc_runtime_Log_Object__delete__E", "xdc_runtime_Log_Object__destruct__E", "xdc_runtime_Log_Object__get__E", "xdc_runtime_Log_Object__first__E", "xdc_runtime_Log_Object__next__E", "xdc_runtime_Log_Params__init__E", "xdc_runtime_Log_Proxy__abstract__E", "xdc_runtime_Log_Proxy__delegate__E", "xdc_runtime_Log_getMask__E", "xdc_runtime_Log_getRope__E", "xdc_runtime_Log_getEventId__E", "xdc_runtime_Log_print0__E", "xdc_runtime_Log_print1__E", "xdc_runtime_Log_print2__E", "xdc_runtime_Log_print3__E", "xdc_runtime_Log_print4__E", "xdc_runtime_Log_print5__E", "xdc_runtime_Log_print6__E", "xdc_runtime_Log_put4__E", "xdc_runtime_Log_put8__E", "xdc_runtime_Log_write0__E", "xdc_runtime_Log_write1__E", "xdc_runtime_Log_write2__E", "xdc_runtime_Log_write3__E", "xdc_runtime_Log_write4__E", "xdc_runtime_Log_write5__E", "xdc_runtime_Log_write6__E", "xdc_runtime_Log_write7__E", "xdc_runtime_Log_write8__E", "xdc_runtime_Log_doPrint__E"));
        vo.bind("$$logEvtCfgs", Global.newArray("L_construct", "L_create", "L_destruct", "L_delete"));
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "doPrint", "entry", "%p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Log", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Log");
    }

    void ILogger$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.ILogger", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.ILogger.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.ILogger", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", om.findStrict("xdc.runtime.ILogger$$capsule", "xdc.runtime"));
        vo.bind("Instance", om.findStrict("xdc.runtime.ILogger.Instance", "xdc.runtime"));
        vo.bind("Params", om.findStrict("xdc.runtime.ILogger.Params", "xdc.runtime"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.runtime.ILogger.Params", "xdc.runtime")).newInstance());
        vo.bind("Handle", om.findStrict("xdc.runtime.ILogger.Handle", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ILogger", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ILogger");
        vo.seal(null);
    }

    void LoggerBuf$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.LoggerBuf", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.LoggerBuf", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.LoggerBuf$$capsule", "xdc.runtime"));
        vo.bind("Instance", om.findStrict("xdc.runtime.LoggerBuf.Instance", "xdc.runtime"));
        vo.bind("Params", om.findStrict("xdc.runtime.LoggerBuf.Params", "xdc.runtime"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.runtime.LoggerBuf.Params", "xdc.runtime")).newInstance());
        vo.bind("Handle", om.findStrict("xdc.runtime.LoggerBuf.Handle", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("BufType", om.findStrict("xdc.runtime.LoggerBuf.BufType", "xdc.runtime"));
        vo.bind("BasicView", om.findStrict("xdc.runtime.LoggerBuf.BasicView", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.LoggerBuf.BasicView", "xdc.runtime"));
        vo.bind("RecordView", om.findStrict("xdc.runtime.LoggerBuf.RecordView", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.LoggerBuf.RecordView", "xdc.runtime"));
        vo.bind("StopModeData", om.findStrict("xdc.runtime.LoggerBuf.StopModeData", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.LoggerBuf.StopModeData", "xdc.runtime"));
        vo.bind("TimestampProxy$proxy", om.findStrict("xdc.runtime.LoggerBuf_TimestampProxy", "xdc.runtime"));
        proxies.add("TimestampProxy");
        mcfgs.add("enableFlush");
        vo.bind("Entry", om.findStrict("xdc.runtime.LoggerBuf.Entry", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.LoggerBuf.Entry", "xdc.runtime"));
        vo.bind("Instance_State", om.findStrict("xdc.runtime.LoggerBuf.Instance_State", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.LoggerBuf.Instance_State", "xdc.runtime"));
        vo.bind("Module_GateProxy$proxy", om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy", "xdc.runtime"));
        proxies.add("Module_GateProxy");
        vo.bind("BufType_CIRCULAR", om.findStrict("xdc.runtime.LoggerBuf.BufType_CIRCULAR", "xdc.runtime"));
        vo.bind("BufType_FIXED", om.findStrict("xdc.runtime.LoggerBuf.BufType_FIXED", "xdc.runtime"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", om.has("xdc.runtime.LoggerBuf$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("xdc$runtime$LoggerBuf$$__initObject"));
        }//isCFG
        vo.bind("flushAll", om.findStrict("xdc.runtime.LoggerBuf.flushAll", "xdc.runtime"));
        vo.bind("flushAllInternal", om.findStrict("xdc.runtime.LoggerBuf.flushAllInternal", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_LoggerBuf_Handle__label__E", "xdc_runtime_LoggerBuf_Module__startupDone__E", "xdc_runtime_LoggerBuf_Object__create__E", "xdc_runtime_LoggerBuf_Object__delete__E", "xdc_runtime_LoggerBuf_Object__destruct__E", "xdc_runtime_LoggerBuf_Object__get__E", "xdc_runtime_LoggerBuf_Object__first__E", "xdc_runtime_LoggerBuf_Object__next__E", "xdc_runtime_LoggerBuf_Params__init__E", "xdc_runtime_LoggerBuf_Proxy__abstract__E", "xdc_runtime_LoggerBuf_Proxy__delegate__E", "xdc_runtime_LoggerBuf_write4__E", "xdc_runtime_LoggerBuf_write8__E", "xdc_runtime_LoggerBuf_flushAll__E", "xdc_runtime_LoggerBuf_flushAllInternal__E", "xdc_runtime_LoggerBuf_enable__E", "xdc_runtime_LoggerBuf_disable__E", "xdc_runtime_LoggerBuf_reset__E", "xdc_runtime_LoggerBuf_flush__E", "xdc_runtime_LoggerBuf_getNextEntry__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.runtime.LoggerBuf.Object", "xdc.runtime"));
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "write4", "entry", "%p, %d, %p, %p, %p, %p", "exit", ""));
        loggables.add(Global.newObject("name", "write8", "entry", "%p, %d, %p, %p, %p, %p, %p", "exit", ""));
        loggables.add(Global.newObject("name", "flushAll", "entry", "", "exit", ""));
        loggables.add(Global.newObject("name", "flushAllInternal", "entry", "%d", "exit", ""));
        loggables.add(Global.newObject("name", "enable", "entry", "%p", "exit", "%d"));
        loggables.add(Global.newObject("name", "disable", "entry", "%p", "exit", "%d"));
        loggables.add(Global.newObject("name", "reset", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "flush", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "getNextEntry", "entry", "%p, %p", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("LoggerBuf", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("LoggerBuf");
    }

    void LoggerSys$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.LoggerSys", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerSys.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.LoggerSys", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.LoggerSys$$capsule", "xdc.runtime"));
        vo.bind("Instance", om.findStrict("xdc.runtime.LoggerSys.Instance", "xdc.runtime"));
        vo.bind("Params", om.findStrict("xdc.runtime.LoggerSys.Params", "xdc.runtime"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.runtime.LoggerSys.Params", "xdc.runtime")).newInstance());
        vo.bind("Handle", om.findStrict("xdc.runtime.LoggerSys.Handle", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("TimestampProxy$proxy", om.findStrict("xdc.runtime.LoggerSys_TimestampProxy", "xdc.runtime"));
        proxies.add("TimestampProxy");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
            vo.bind("__initObject", Global.get("xdc$runtime$LoggerSys$$__initObject"));
        }//isCFG
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_LoggerSys_Handle__label__E", "xdc_runtime_LoggerSys_Module__startupDone__E", "xdc_runtime_LoggerSys_Object__create__E", "xdc_runtime_LoggerSys_Object__delete__E", "xdc_runtime_LoggerSys_Object__destruct__E", "xdc_runtime_LoggerSys_Object__get__E", "xdc_runtime_LoggerSys_Object__first__E", "xdc_runtime_LoggerSys_Object__next__E", "xdc_runtime_LoggerSys_Params__init__E", "xdc_runtime_LoggerSys_Proxy__abstract__E", "xdc_runtime_LoggerSys_Proxy__delegate__E", "xdc_runtime_LoggerSys_write4__E", "xdc_runtime_LoggerSys_write8__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.runtime.LoggerSys.Object", "xdc.runtime"));
        vo.bind("Instance_State", om.findStrict("xdc.runtime.LoggerSys.Instance_State", "xdc.runtime"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "write4", "entry", "%p, %d, %p, %p, %p, %p", "exit", ""));
        loggables.add(Global.newObject("name", "write8", "entry", "%p, %d, %p, %p, %p, %p, %p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("LoggerSys", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("LoggerSys");
    }

    void Main$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Main", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Main.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Main", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("Module_GateProxy$proxy", om.findStrict("xdc.runtime.Main_Module_GateProxy", "xdc.runtime"));
        proxies.add("Module_GateProxy");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Main_Handle__label__E", "xdc_runtime_Main_Module__startupDone__E", "xdc_runtime_Main_Object__create__E", "xdc_runtime_Main_Object__delete__E", "xdc_runtime_Main_Object__destruct__E", "xdc_runtime_Main_Object__get__E", "xdc_runtime_Main_Object__first__E", "xdc_runtime_Main_Object__next__E", "xdc_runtime_Main_Params__init__E", "xdc_runtime_Main_Proxy__abstract__E", "xdc_runtime_Main_Proxy__delegate__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Main", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Main");
    }

    void Memory$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Memory", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Memory", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.Memory$$capsule", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("Size", om.findStrict("xdc.runtime.Memory.Size", "xdc.runtime"));
        vo.bind("Stats", om.findStrict("xdc.runtime.Memory.Stats", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Memory.Stats", "xdc.runtime"));
        vo.bind("Module_View", om.findStrict("xdc.runtime.Memory.Module_View", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Memory.Module_View", "xdc.runtime"));
        mcfgs.add("defaultHeapInstance");
        vo.bind("HeapProxy$proxy", om.findStrict("xdc.runtime.Memory_HeapProxy", "xdc.runtime"));
        proxies.add("HeapProxy");
        vo.bind("Module_State", om.findStrict("xdc.runtime.Memory.Module_State", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Memory.Module_State", "xdc.runtime"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("alloc", om.findStrict("xdc.runtime.Memory.alloc", "xdc.runtime"));
        vo.bind("calloc", om.findStrict("xdc.runtime.Memory.calloc", "xdc.runtime"));
        vo.bind("free", om.findStrict("xdc.runtime.Memory.free", "xdc.runtime"));
        vo.bind("getStats", om.findStrict("xdc.runtime.Memory.getStats", "xdc.runtime"));
        vo.bind("query", om.findStrict("xdc.runtime.Memory.query", "xdc.runtime"));
        vo.bind("getMaxDefaultTypeAlign", om.findStrict("xdc.runtime.Memory.getMaxDefaultTypeAlign", "xdc.runtime"));
        vo.bind("valloc", om.findStrict("xdc.runtime.Memory.valloc", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Memory_Handle__label__E", "xdc_runtime_Memory_Module__startupDone__E", "xdc_runtime_Memory_Object__create__E", "xdc_runtime_Memory_Object__delete__E", "xdc_runtime_Memory_Object__destruct__E", "xdc_runtime_Memory_Object__get__E", "xdc_runtime_Memory_Object__first__E", "xdc_runtime_Memory_Object__next__E", "xdc_runtime_Memory_Params__init__E", "xdc_runtime_Memory_Proxy__abstract__E", "xdc_runtime_Memory_Proxy__delegate__E", "xdc_runtime_Memory_alloc__E", "xdc_runtime_Memory_calloc__E", "xdc_runtime_Memory_free__E", "xdc_runtime_Memory_getStats__E", "xdc_runtime_Memory_query__E", "xdc_runtime_Memory_getMaxDefaultTypeAlign__E", "xdc_runtime_Memory_valloc__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "alloc", "entry", "%p, 0x%x, 0x%x, %p", "exit", "%p"));
        loggables.add(Global.newObject("name", "calloc", "entry", "%p, 0x%x, 0x%x, %p", "exit", "%p"));
        loggables.add(Global.newObject("name", "free", "entry", "%p, %p, 0x%x", "exit", ""));
        loggables.add(Global.newObject("name", "getStats", "entry", "%p, %p", "exit", ""));
        loggables.add(Global.newObject("name", "query", "entry", "%p, %d", "exit", "%d"));
        loggables.add(Global.newObject("name", "getMaxDefaultTypeAlign", "entry", "", "exit", "0x%x"));
        loggables.add(Global.newObject("name", "valloc", "entry", "%p, 0x%x, 0x%x, %d, %p", "exit", "%p"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Memory", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Memory");
    }

    void IHeap$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.IHeap", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.IHeap.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.IHeap", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("xdc.runtime.IHeap.Instance", "xdc.runtime"));
        vo.bind("Params", om.findStrict("xdc.runtime.IHeap.Params", "xdc.runtime"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.runtime.IHeap.Params", "xdc.runtime")).newInstance());
        vo.bind("Handle", om.findStrict("xdc.runtime.IHeap.Handle", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IHeap", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IHeap");
        vo.seal(null);
    }

    void HeapMin$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.HeapMin", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapMin.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.HeapMin", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.HeapMin$$capsule", "xdc.runtime"));
        vo.bind("Instance", om.findStrict("xdc.runtime.HeapMin.Instance", "xdc.runtime"));
        vo.bind("Params", om.findStrict("xdc.runtime.HeapMin.Params", "xdc.runtime"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.runtime.HeapMin.Params", "xdc.runtime")).newInstance());
        vo.bind("Handle", om.findStrict("xdc.runtime.HeapMin.Handle", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("Instance_View", om.findStrict("xdc.runtime.HeapMin.Instance_View", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.HeapMin.Instance_View", "xdc.runtime"));
        mcfgs.add("A_zeroSize");
        mcfgs.add("E_freeError");
        mcfgs.add("freeError");
        vo.bind("Instance_State", om.findStrict("xdc.runtime.HeapMin.Instance_State", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.HeapMin.Instance_State", "xdc.runtime"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", om.has("xdc.runtime.HeapMin$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("xdc$runtime$HeapMin$$__initObject"));
        }//isCFG
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_HeapMin_Handle__label__E", "xdc_runtime_HeapMin_Module__startupDone__E", "xdc_runtime_HeapMin_Object__create__E", "xdc_runtime_HeapMin_Object__delete__E", "xdc_runtime_HeapMin_Object__destruct__E", "xdc_runtime_HeapMin_Object__get__E", "xdc_runtime_HeapMin_Object__first__E", "xdc_runtime_HeapMin_Object__next__E", "xdc_runtime_HeapMin_Params__init__E", "xdc_runtime_HeapMin_Proxy__abstract__E", "xdc_runtime_HeapMin_Proxy__delegate__E", "xdc_runtime_HeapMin_getStats__E", "xdc_runtime_HeapMin_alloc__E", "xdc_runtime_HeapMin_free__E", "xdc_runtime_HeapMin_isBlocking__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_freeError"));
        vo.bind("$$assertDescCfgs", Global.newArray("A_zeroSize"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.runtime.HeapMin.Object", "xdc.runtime"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "getStats", "entry", "%p, %p", "exit", ""));
        loggables.add(Global.newObject("name", "alloc", "entry", "%p, 0x%x, 0x%x, %p", "exit", "%p"));
        loggables.add(Global.newObject("name", "free", "entry", "%p, %p, 0x%x", "exit", ""));
        loggables.add(Global.newObject("name", "isBlocking", "entry", "%p", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("HeapMin", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("HeapMin");
    }

    void HeapStd$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.HeapStd", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.HeapStd.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.HeapStd", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.HeapStd$$capsule", "xdc.runtime"));
        vo.bind("Instance", om.findStrict("xdc.runtime.HeapStd.Instance", "xdc.runtime"));
        vo.bind("Params", om.findStrict("xdc.runtime.HeapStd.Params", "xdc.runtime"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.runtime.HeapStd.Params", "xdc.runtime")).newInstance());
        vo.bind("Handle", om.findStrict("xdc.runtime.HeapStd.Handle", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("Instance_View", om.findStrict("xdc.runtime.HeapStd.Instance_View", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.HeapStd.Instance_View", "xdc.runtime"));
        mcfgs.add("E_noRTSMemory");
        mcfgs.add("A_zeroSize");
        mcfgs.add("A_invalidTotalFreeSize");
        mcfgs.add("A_invalidAlignment");
        vo.bind("Module_State", om.findStrict("xdc.runtime.HeapStd.Module_State", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.HeapStd.Module_State", "xdc.runtime"));
        vo.bind("Instance_State", om.findStrict("xdc.runtime.HeapStd.Instance_State", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.HeapStd.Instance_State", "xdc.runtime"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", om.has("xdc.runtime.HeapStd$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("xdc$runtime$HeapStd$$__initObject"));
        }//isCFG
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_HeapStd_Handle__label__E", "xdc_runtime_HeapStd_Module__startupDone__E", "xdc_runtime_HeapStd_Object__create__E", "xdc_runtime_HeapStd_Object__delete__E", "xdc_runtime_HeapStd_Object__destruct__E", "xdc_runtime_HeapStd_Object__get__E", "xdc_runtime_HeapStd_Object__first__E", "xdc_runtime_HeapStd_Object__next__E", "xdc_runtime_HeapStd_Params__init__E", "xdc_runtime_HeapStd_Proxy__abstract__E", "xdc_runtime_HeapStd_Proxy__delegate__E", "xdc_runtime_HeapStd_free__E", "xdc_runtime_HeapStd_getStats__E", "xdc_runtime_HeapStd_alloc__E", "xdc_runtime_HeapStd_isBlocking__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_noRTSMemory"));
        vo.bind("$$assertDescCfgs", Global.newArray("A_zeroSize", "A_invalidTotalFreeSize", "A_invalidAlignment"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.runtime.HeapStd.Object", "xdc.runtime"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "free", "entry", "%p, %p, 0x%x", "exit", ""));
        loggables.add(Global.newObject("name", "getStats", "entry", "%p, %p", "exit", ""));
        loggables.add(Global.newObject("name", "alloc", "entry", "%p, 0x%x, 0x%x, %p", "exit", "%p"));
        loggables.add(Global.newObject("name", "isBlocking", "entry", "%p", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("HeapStd", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("HeapStd");
    }

    void Rta$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Rta", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Rta.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Rta", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.Rta$$capsule", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        mcfgs.add("LD_cmdRcvd");
        mcfgs.add("LD_writeMask");
        mcfgs.add("A_invalidLogger");
        mcfgs.add("E_badCommand");
        vo.bind("Command", om.findStrict("xdc.runtime.Rta.Command", "xdc.runtime"));
        vo.bind("CommandPacket", om.findStrict("xdc.runtime.Rta.CommandPacket", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Rta.CommandPacket", "xdc.runtime"));
        vo.bind("ResponsePacket", om.findStrict("xdc.runtime.Rta.ResponsePacket", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Rta.ResponsePacket", "xdc.runtime"));
        vo.bind("Command_READ_MASK", om.findStrict("xdc.runtime.Rta.Command_READ_MASK", "xdc.runtime"));
        vo.bind("Command_WRITE_MASK", om.findStrict("xdc.runtime.Rta.Command_WRITE_MASK", "xdc.runtime"));
        vo.bind("Command_LOGGER_OFF", om.findStrict("xdc.runtime.Rta.Command_LOGGER_OFF", "xdc.runtime"));
        vo.bind("Command_LOGGER_ON", om.findStrict("xdc.runtime.Rta.Command_LOGGER_ON", "xdc.runtime"));
        vo.bind("Command_GET_CPU_SPEED", om.findStrict("xdc.runtime.Rta.Command_GET_CPU_SPEED", "xdc.runtime"));
        vo.bind("Command_RESET_LOGGER", om.findStrict("xdc.runtime.Rta.Command_RESET_LOGGER", "xdc.runtime"));
        vo.bind("Command_CHANGE_PERIOD", om.findStrict("xdc.runtime.Rta.Command_CHANGE_PERIOD", "xdc.runtime"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("processCommand", om.findStrict("xdc.runtime.Rta.processCommand", "xdc.runtime"));
        vo.bind("acknowledgeCmd", om.findStrict("xdc.runtime.Rta.acknowledgeCmd", "xdc.runtime"));
        vo.bind("readMask", om.findStrict("xdc.runtime.Rta.readMask", "xdc.runtime"));
        vo.bind("writeMask", om.findStrict("xdc.runtime.Rta.writeMask", "xdc.runtime"));
        vo.bind("enableLog", om.findStrict("xdc.runtime.Rta.enableLog", "xdc.runtime"));
        vo.bind("disableLog", om.findStrict("xdc.runtime.Rta.disableLog", "xdc.runtime"));
        vo.bind("getCpuSpeed", om.findStrict("xdc.runtime.Rta.getCpuSpeed", "xdc.runtime"));
        vo.bind("resetLog", om.findStrict("xdc.runtime.Rta.resetLog", "xdc.runtime"));
        vo.bind("changePeriod", om.findStrict("xdc.runtime.Rta.changePeriod", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Rta_Handle__label__E", "xdc_runtime_Rta_Module__startupDone__E", "xdc_runtime_Rta_Object__create__E", "xdc_runtime_Rta_Object__delete__E", "xdc_runtime_Rta_Object__destruct__E", "xdc_runtime_Rta_Object__get__E", "xdc_runtime_Rta_Object__first__E", "xdc_runtime_Rta_Object__next__E", "xdc_runtime_Rta_Params__init__E", "xdc_runtime_Rta_Proxy__abstract__E", "xdc_runtime_Rta_Proxy__delegate__E", "xdc_runtime_Rta_processCommand__E", "xdc_runtime_Rta_acknowledgeCmd__E", "xdc_runtime_Rta_readMask__E", "xdc_runtime_Rta_writeMask__E", "xdc_runtime_Rta_enableLog__E", "xdc_runtime_Rta_disableLog__E", "xdc_runtime_Rta_getCpuSpeed__E", "xdc_runtime_Rta_resetLog__E", "xdc_runtime_Rta_changePeriod__E"));
        vo.bind("$$logEvtCfgs", Global.newArray("LD_cmdRcvd", "LD_writeMask"));
        vo.bind("$$errorDescCfgs", Global.newArray("E_badCommand"));
        vo.bind("$$assertDescCfgs", Global.newArray("A_invalidLogger"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "processCommand", "entry", "%p, %p", "exit", ""));
        loggables.add(Global.newObject("name", "acknowledgeCmd", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "readMask", "entry", "%p, %p", "exit", ""));
        loggables.add(Global.newObject("name", "writeMask", "entry", "%p, %p, %p", "exit", ""));
        loggables.add(Global.newObject("name", "enableLog", "entry", "%p, %p", "exit", ""));
        loggables.add(Global.newObject("name", "disableLog", "entry", "%p, %p", "exit", ""));
        loggables.add(Global.newObject("name", "getCpuSpeed", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "resetLog", "entry", "%p, %p", "exit", ""));
        loggables.add(Global.newObject("name", "changePeriod", "entry", "%p, %p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Rta", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Rta");
    }

    void Startup$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Startup", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Startup.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Startup", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.Startup$$capsule", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        mcfgs.add("maxPasses");
        vo.bind("InitFxn", om.findStrict("xdc.runtime.Startup.InitFxn", "xdc.runtime"));
        mcfgs.add("firstFxns");
        mcfgs.add("lastFxns");
        mcfgs.add("startModsFxn");
        vo.bind("execImplFxn", om.findStrict("xdc.runtime.Startup.execImplFxn", "xdc.runtime"));
        mcfgs.add("execImpl");
        vo.bind("SFxn", om.findStrict("xdc.runtime.Startup.SFxn", "xdc.runtime"));
        mcfgs.add("sfxnTab");
        mcfgs.add("sfxnRts");
        vo.bind("Module_State", om.findStrict("xdc.runtime.Startup.Module_State", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Startup.Module_State", "xdc.runtime"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("exec", om.findStrict("xdc.runtime.Startup.exec", "xdc.runtime"));
        vo.bind("rtsDone", om.findStrict("xdc.runtime.Startup.rtsDone", "xdc.runtime"));
        vo.bind("reset", om.findStrict("xdc.runtime.Startup.reset", "xdc.runtime"));
        vo.bind("startMods", om.findStrict("xdc.runtime.Startup.startMods", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Startup_Handle__label__E", "xdc_runtime_Startup_Module__startupDone__E", "xdc_runtime_Startup_Object__create__E", "xdc_runtime_Startup_Object__delete__E", "xdc_runtime_Startup_Object__destruct__E", "xdc_runtime_Startup_Object__get__E", "xdc_runtime_Startup_Object__first__E", "xdc_runtime_Startup_Object__next__E", "xdc_runtime_Startup_Params__init__E", "xdc_runtime_Startup_Proxy__abstract__E", "xdc_runtime_Startup_Proxy__delegate__E", "xdc_runtime_Startup_exec__E", "xdc_runtime_Startup_rtsDone__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Startup.xdt");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "exec", "entry", "", "exit", ""));
        loggables.add(Global.newObject("name", "rtsDone", "entry", "", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./Startup.xdt");
        pkgV.bind("Startup", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Startup");
    }

    void Reset$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Reset", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Reset.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Reset", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("xdc.runtime.Reset$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/runtime/Reset.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "xdc/runtime/Reset.xdt");
        pkgV.bind("Reset", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Reset");
    }

    void System$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.System", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.System.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.System", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.System$$capsule", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("AtexitHandler", om.findStrict("xdc.runtime.System.AtexitHandler", "xdc.runtime"));
        vo.bind("Module_View", om.findStrict("xdc.runtime.System.Module_View", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.System.Module_View", "xdc.runtime"));
        mcfgs.add("A_cannotFitIntoArg");
        vo.bind("SupportProxy$proxy", om.findStrict("xdc.runtime.System_SupportProxy", "xdc.runtime"));
        proxies.add("SupportProxy");
        mcfgs.add("maxAtexitHandlers");
        vo.bind("ParseData", om.findStrict("xdc.runtime.System.ParseData", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.System.ParseData", "xdc.runtime"));
        vo.bind("ExtendFxn", om.findStrict("xdc.runtime.System.ExtendFxn", "xdc.runtime"));
        mcfgs.add("extendFxn");
        vo.bind("Module_State", om.findStrict("xdc.runtime.System.Module_State", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.System.Module_State", "xdc.runtime"));
        vo.bind("Module_GateProxy$proxy", om.findStrict("xdc.runtime.System_Module_GateProxy", "xdc.runtime"));
        proxies.add("Module_GateProxy");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("abort", om.findStrict("xdc.runtime.System.abort", "xdc.runtime"));
        vo.bind("atexit", om.findStrict("xdc.runtime.System.atexit", "xdc.runtime"));
        vo.bind("exit", om.findStrict("xdc.runtime.System.exit", "xdc.runtime"));
        vo.bind("putch", om.findStrict("xdc.runtime.System.putch", "xdc.runtime"));
        vo.bind("flush", om.findStrict("xdc.runtime.System.flush", "xdc.runtime"));
        vo.bind("printf", om.findStrict("xdc.runtime.System.printf", "xdc.runtime"));
        vo.bind("aprintf", om.findStrict("xdc.runtime.System.aprintf", "xdc.runtime"));
        vo.bind("sprintf", om.findStrict("xdc.runtime.System.sprintf", "xdc.runtime"));
        vo.bind("asprintf", om.findStrict("xdc.runtime.System.asprintf", "xdc.runtime"));
        vo.bind("vprintf", om.findStrict("xdc.runtime.System.vprintf", "xdc.runtime"));
        vo.bind("avprintf", om.findStrict("xdc.runtime.System.avprintf", "xdc.runtime"));
        vo.bind("vsprintf", om.findStrict("xdc.runtime.System.vsprintf", "xdc.runtime"));
        vo.bind("avsprintf", om.findStrict("xdc.runtime.System.avsprintf", "xdc.runtime"));
        vo.bind("printfExtend", om.findStrict("xdc.runtime.System.printfExtend", "xdc.runtime"));
        vo.bind("doPrint", om.findStrict("xdc.runtime.System.doPrint", "xdc.runtime"));
        vo.bind("formatNum", om.findStrict("xdc.runtime.System.formatNum", "xdc.runtime"));
        vo.bind("putchar", om.findStrict("xdc.runtime.System.putchar", "xdc.runtime"));
        vo.bind("rtsExit", om.findStrict("xdc.runtime.System.rtsExit", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_System_Handle__label__E", "xdc_runtime_System_Module__startupDone__E", "xdc_runtime_System_Object__create__E", "xdc_runtime_System_Object__delete__E", "xdc_runtime_System_Object__destruct__E", "xdc_runtime_System_Object__get__E", "xdc_runtime_System_Object__first__E", "xdc_runtime_System_Object__next__E", "xdc_runtime_System_Params__init__E", "xdc_runtime_System_Proxy__abstract__E", "xdc_runtime_System_Proxy__delegate__E", "xdc_runtime_System_abort__E", "xdc_runtime_System_atexit__E", "xdc_runtime_System_exit__E", "xdc_runtime_System_putch__E", "xdc_runtime_System_flush__E", "xdc_runtime_System_printf_va__E", "xdc_runtime_System_aprintf_va__E", "xdc_runtime_System_sprintf_va__E", "xdc_runtime_System_asprintf_va__E", "xdc_runtime_System_vprintf__E", "xdc_runtime_System_avprintf__E", "xdc_runtime_System_vsprintf__E", "xdc_runtime_System_avsprintf__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_cannotFitIntoArg"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", "./System.xdt");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "abort", "entry", "\"%s\"", "exit", ""));
        loggables.add(Global.newObject("name", "atexit", "entry", "%p", "exit", "%d"));
        loggables.add(Global.newObject("name", "exit", "entry", "%d", "exit", ""));
        loggables.add(Global.newObject("name", "putch", "entry", "%d", "exit", ""));
        loggables.add(Global.newObject("name", "flush", "entry", "", "exit", ""));
        loggables.add(Global.newObject("name", "printf", "entry", "\"%s\"", "exit", "%d"));
        loggables.add(Global.newObject("name", "aprintf", "entry", "\"%s\"", "exit", "%d"));
        loggables.add(Global.newObject("name", "sprintf", "entry", "%p, \"%s\"", "exit", "%d"));
        loggables.add(Global.newObject("name", "asprintf", "entry", "%p, \"%s\"", "exit", "%d"));
        loggables.add(Global.newObject("name", "vprintf", "entry", "\"%s\", 0x%x", "exit", "%d"));
        loggables.add(Global.newObject("name", "avprintf", "entry", "\"%s\", 0x%x", "exit", "%d"));
        loggables.add(Global.newObject("name", "vsprintf", "entry", "%p, \"%s\", 0x%x", "exit", "%d"));
        loggables.add(Global.newObject("name", "avsprintf", "entry", "%p, \"%s\", 0x%x", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./System.xdt");
        pkgV.bind("System", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("System");
    }

    void ISystemSupport$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.ISystemSupport", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.ISystemSupport.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.ISystemSupport", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ISystemSupport", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ISystemSupport");
        vo.seal(null);
    }

    void SysStd$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.SysStd", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.SysStd.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.SysStd", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("abort", om.findStrict("xdc.runtime.SysStd.abort", "xdc.runtime"));
        vo.bind("exit", om.findStrict("xdc.runtime.SysStd.exit", "xdc.runtime"));
        vo.bind("flush", om.findStrict("xdc.runtime.SysStd.flush", "xdc.runtime"));
        vo.bind("putch", om.findStrict("xdc.runtime.SysStd.putch", "xdc.runtime"));
        vo.bind("ready", om.findStrict("xdc.runtime.SysStd.ready", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_SysStd_Handle__label__E", "xdc_runtime_SysStd_Module__startupDone__E", "xdc_runtime_SysStd_Object__create__E", "xdc_runtime_SysStd_Object__delete__E", "xdc_runtime_SysStd_Object__destruct__E", "xdc_runtime_SysStd_Object__get__E", "xdc_runtime_SysStd_Object__first__E", "xdc_runtime_SysStd_Object__next__E", "xdc_runtime_SysStd_Params__init__E", "xdc_runtime_SysStd_Proxy__abstract__E", "xdc_runtime_SysStd_Proxy__delegate__E", "xdc_runtime_SysStd_abort__E", "xdc_runtime_SysStd_exit__E", "xdc_runtime_SysStd_flush__E", "xdc_runtime_SysStd_putch__E", "xdc_runtime_SysStd_ready__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "abort", "entry", "\"%s\"", "exit", ""));
        loggables.add(Global.newObject("name", "exit", "entry", "%d", "exit", ""));
        loggables.add(Global.newObject("name", "flush", "entry", "", "exit", ""));
        loggables.add(Global.newObject("name", "putch", "entry", "%d", "exit", ""));
        loggables.add(Global.newObject("name", "ready", "entry", "", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("SysStd", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("SysStd");
    }

    void SysMin$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.SysMin", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.SysMin.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.SysMin", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.SysMin$$capsule", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("ModuleView", om.findStrict("xdc.runtime.SysMin.ModuleView", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.SysMin.ModuleView", "xdc.runtime"));
        vo.bind("BufferEntryView", om.findStrict("xdc.runtime.SysMin.BufferEntryView", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.SysMin.BufferEntryView", "xdc.runtime"));
        mcfgs.add("bufSize");
        mcfgs.add("flushAtExit");
        vo.bind("OutputFxn", om.findStrict("xdc.runtime.SysMin.OutputFxn", "xdc.runtime"));
        mcfgs.add("outputFxn");
        mcfgs.add("outputFunc");
        vo.bind("Module_State", om.findStrict("xdc.runtime.SysMin.Module_State", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.SysMin.Module_State", "xdc.runtime"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("abort", om.findStrict("xdc.runtime.SysMin.abort", "xdc.runtime"));
        vo.bind("exit", om.findStrict("xdc.runtime.SysMin.exit", "xdc.runtime"));
        vo.bind("flush", om.findStrict("xdc.runtime.SysMin.flush", "xdc.runtime"));
        vo.bind("putch", om.findStrict("xdc.runtime.SysMin.putch", "xdc.runtime"));
        vo.bind("ready", om.findStrict("xdc.runtime.SysMin.ready", "xdc.runtime"));
        vo.bind("output", om.findStrict("xdc.runtime.SysMin.output", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_SysMin_Handle__label__E", "xdc_runtime_SysMin_Module__startupDone__E", "xdc_runtime_SysMin_Object__create__E", "xdc_runtime_SysMin_Object__delete__E", "xdc_runtime_SysMin_Object__destruct__E", "xdc_runtime_SysMin_Object__get__E", "xdc_runtime_SysMin_Object__first__E", "xdc_runtime_SysMin_Object__next__E", "xdc_runtime_SysMin_Params__init__E", "xdc_runtime_SysMin_Proxy__abstract__E", "xdc_runtime_SysMin_Proxy__delegate__E", "xdc_runtime_SysMin_abort__E", "xdc_runtime_SysMin_exit__E", "xdc_runtime_SysMin_flush__E", "xdc_runtime_SysMin_putch__E", "xdc_runtime_SysMin_ready__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", "./SysMin.xdt");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "abort", "entry", "\"%s\"", "exit", ""));
        loggables.add(Global.newObject("name", "exit", "entry", "%d", "exit", ""));
        loggables.add(Global.newObject("name", "flush", "entry", "", "exit", ""));
        loggables.add(Global.newObject("name", "putch", "entry", "%d", "exit", ""));
        loggables.add(Global.newObject("name", "ready", "entry", "", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./SysMin.xdt");
        pkgV.bind("SysMin", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("SysMin");
    }

    void Text$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Text", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Text.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Text", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.Text$$capsule", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("CordAddr", om.findStrict("xdc.runtime.Text.CordAddr", "xdc.runtime"));
        vo.bind("Label", om.findStrict("xdc.runtime.Text.Label", "xdc.runtime"));
        vo.bind("RopeId", om.findStrict("xdc.runtime.Text.RopeId", "xdc.runtime"));
        vo.bind("Module_View", om.findStrict("xdc.runtime.Text.Module_View", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Text.Module_View", "xdc.runtime"));
        mcfgs.add("nameUnknown");
        mcfgs.add("nameEmpty");
        mcfgs.add("nameStatic");
        mcfgs.add("isLoaded");
        vo.bind("Node", om.findStrict("xdc.runtime.Text.Node", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Text.Node", "xdc.runtime"));
        vo.bind("RopeVisitor", om.findStrict("xdc.runtime.Text.RopeVisitor", "xdc.runtime"));
        vo.bind("MatchVisState", om.findStrict("xdc.runtime.Text.MatchVisState", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Text.MatchVisState", "xdc.runtime"));
        vo.bind("PrintVisState", om.findStrict("xdc.runtime.Text.PrintVisState", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Text.PrintVisState", "xdc.runtime"));
        mcfgs.add("charTab");
        mcfgs.add("nodeTab");
        mcfgs.add("charCnt");
        mcfgs.add("nodeCnt");
        vo.bind("VisitRopeFxn", om.findStrict("xdc.runtime.Text.VisitRopeFxn", "xdc.runtime"));
        vo.bind("VisitRopeFxn2", om.findStrict("xdc.runtime.Text.VisitRopeFxn2", "xdc.runtime"));
        mcfgs.add("visitRopeFxn");
        mcfgs.add("visitRopeFxn2");
        vo.bind("Module_State", om.findStrict("xdc.runtime.Text.Module_State", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Text.Module_State", "xdc.runtime"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("cordText", om.findStrict("xdc.runtime.Text.cordText", "xdc.runtime"));
        vo.bind("ropeText", om.findStrict("xdc.runtime.Text.ropeText", "xdc.runtime"));
        vo.bind("matchRope", om.findStrict("xdc.runtime.Text.matchRope", "xdc.runtime"));
        vo.bind("putLab", om.findStrict("xdc.runtime.Text.putLab", "xdc.runtime"));
        vo.bind("putMod", om.findStrict("xdc.runtime.Text.putMod", "xdc.runtime"));
        vo.bind("putSite", om.findStrict("xdc.runtime.Text.putSite", "xdc.runtime"));
        vo.bind("matchVisFxn", om.findStrict("xdc.runtime.Text.matchVisFxn", "xdc.runtime"));
        vo.bind("printVisFxn", om.findStrict("xdc.runtime.Text.printVisFxn", "xdc.runtime"));
        vo.bind("visitRope", om.findStrict("xdc.runtime.Text.visitRope", "xdc.runtime"));
        vo.bind("visitRope2", om.findStrict("xdc.runtime.Text.visitRope2", "xdc.runtime"));
        vo.bind("xprintf", om.findStrict("xdc.runtime.Text.xprintf", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Text_Handle__label__E", "xdc_runtime_Text_Module__startupDone__E", "xdc_runtime_Text_Object__create__E", "xdc_runtime_Text_Object__delete__E", "xdc_runtime_Text_Object__destruct__E", "xdc_runtime_Text_Object__get__E", "xdc_runtime_Text_Object__first__E", "xdc_runtime_Text_Object__next__E", "xdc_runtime_Text_Params__init__E", "xdc_runtime_Text_Proxy__abstract__E", "xdc_runtime_Text_Proxy__delegate__E", "xdc_runtime_Text_cordText__E", "xdc_runtime_Text_ropeText__E", "xdc_runtime_Text_matchRope__E", "xdc_runtime_Text_putLab__E", "xdc_runtime_Text_putMod__E", "xdc_runtime_Text_putSite__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Text.xdt");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "cordText", "entry", "%p", "exit", "\"%s\""));
        loggables.add(Global.newObject("name", "ropeText", "entry", "%d", "exit", "\"%s\""));
        loggables.add(Global.newObject("name", "matchRope", "entry", "%d, \"%s\", %p", "exit", "%d"));
        loggables.add(Global.newObject("name", "putLab", "entry", "%p, %p, %d", "exit", "%d"));
        loggables.add(Global.newObject("name", "putMod", "entry", "%d, %p, %d", "exit", "%d"));
        loggables.add(Global.newObject("name", "putSite", "entry", "%p, %p, %d", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./Text.xdt");
        pkgV.bind("Text", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Text");
    }

    void ITimestampClient$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.ITimestampClient", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.ITimestampClient.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.ITimestampClient", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ITimestampClient", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ITimestampClient");
        vo.seal(null);
    }

    void Timestamp$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Timestamp", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Timestamp.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Timestamp", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("xdc.runtime.Timestamp$$capsule", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("SupportProxy$proxy", om.findStrict("xdc.runtime.Timestamp_SupportProxy", "xdc.runtime"));
        proxies.add("SupportProxy");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("get32", om.findStrict("xdc.runtime.Timestamp.get32", "xdc.runtime"));
        vo.bind("get64", om.findStrict("xdc.runtime.Timestamp.get64", "xdc.runtime"));
        vo.bind("getFreq", om.findStrict("xdc.runtime.Timestamp.getFreq", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Timestamp_Handle__label__E", "xdc_runtime_Timestamp_Module__startupDone__E", "xdc_runtime_Timestamp_Object__create__E", "xdc_runtime_Timestamp_Object__delete__E", "xdc_runtime_Timestamp_Object__destruct__E", "xdc_runtime_Timestamp_Object__get__E", "xdc_runtime_Timestamp_Object__first__E", "xdc_runtime_Timestamp_Object__next__E", "xdc_runtime_Timestamp_Params__init__E", "xdc_runtime_Timestamp_Proxy__abstract__E", "xdc_runtime_Timestamp_Proxy__delegate__E", "xdc_runtime_Timestamp_get32__E", "xdc_runtime_Timestamp_get64__E", "xdc_runtime_Timestamp_getFreq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "get32", "entry", "", "exit", "0x%x"));
        loggables.add(Global.newObject("name", "get64", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "getFreq", "entry", "%p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Timestamp", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Timestamp");
    }

    void ITimestampProvider$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.ITimestampProvider", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.ITimestampProvider.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.ITimestampProvider", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ITimestampProvider", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ITimestampProvider");
        vo.seal(null);
    }

    void TimestampNull$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.TimestampNull", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.TimestampNull.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.TimestampNull", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("get32", om.findStrict("xdc.runtime.TimestampNull.get32", "xdc.runtime"));
        vo.bind("get64", om.findStrict("xdc.runtime.TimestampNull.get64", "xdc.runtime"));
        vo.bind("getFreq", om.findStrict("xdc.runtime.TimestampNull.getFreq", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_TimestampNull_Handle__label__E", "xdc_runtime_TimestampNull_Module__startupDone__E", "xdc_runtime_TimestampNull_Object__create__E", "xdc_runtime_TimestampNull_Object__delete__E", "xdc_runtime_TimestampNull_Object__destruct__E", "xdc_runtime_TimestampNull_Object__get__E", "xdc_runtime_TimestampNull_Object__first__E", "xdc_runtime_TimestampNull_Object__next__E", "xdc_runtime_TimestampNull_Params__init__E", "xdc_runtime_TimestampNull_Proxy__abstract__E", "xdc_runtime_TimestampNull_Proxy__delegate__E", "xdc_runtime_TimestampNull_get32__E", "xdc_runtime_TimestampNull_get64__E", "xdc_runtime_TimestampNull_getFreq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "get32", "entry", "", "exit", "0x%x"));
        loggables.add(Global.newObject("name", "get64", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "getFreq", "entry", "%p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TimestampNull", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TimestampNull");
    }

    void TimestampStd$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.TimestampStd", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.TimestampStd.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.TimestampStd", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("get32", om.findStrict("xdc.runtime.TimestampStd.get32", "xdc.runtime"));
        vo.bind("get64", om.findStrict("xdc.runtime.TimestampStd.get64", "xdc.runtime"));
        vo.bind("getFreq", om.findStrict("xdc.runtime.TimestampStd.getFreq", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_TimestampStd_Handle__label__E", "xdc_runtime_TimestampStd_Module__startupDone__E", "xdc_runtime_TimestampStd_Object__create__E", "xdc_runtime_TimestampStd_Object__delete__E", "xdc_runtime_TimestampStd_Object__destruct__E", "xdc_runtime_TimestampStd_Object__get__E", "xdc_runtime_TimestampStd_Object__first__E", "xdc_runtime_TimestampStd_Object__next__E", "xdc_runtime_TimestampStd_Params__init__E", "xdc_runtime_TimestampStd_Proxy__abstract__E", "xdc_runtime_TimestampStd_Proxy__delegate__E", "xdc_runtime_TimestampStd_get32__E", "xdc_runtime_TimestampStd_get64__E", "xdc_runtime_TimestampStd_getFreq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "get32", "entry", "", "exit", "0x%x"));
        loggables.add(Global.newObject("name", "get64", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "getFreq", "entry", "%p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TimestampStd", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TimestampStd");
    }

    void Types$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Types", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Types.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Types", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        mcfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        mcfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        vo.bind("ModuleId", om.findStrict("xdc.runtime.Types.ModuleId", "xdc.runtime"));
        vo.bind("Event", om.findStrict("xdc.runtime.Types.Event", "xdc.runtime"));
        vo.bind("EventId", om.findStrict("xdc.runtime.Types.EventId", "xdc.runtime"));
        vo.bind("CordAddr", om.findStrict("xdc.runtime.Types.CordAddr", "xdc.runtime"));
        vo.bind("GateRef", om.findStrict("xdc.runtime.Types.GateRef", "xdc.runtime"));
        vo.bind("RopeId", om.findStrict("xdc.runtime.Types.RopeId", "xdc.runtime"));
        vo.bind("CreatePolicy", om.findStrict("xdc.runtime.Types.CreatePolicy", "xdc.runtime"));
        vo.bind("Label", om.findStrict("xdc.runtime.Types.Label", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.Label", "xdc.runtime"));
        vo.bind("Site", om.findStrict("xdc.runtime.Types.Site", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.Site", "xdc.runtime"));
        vo.bind("Timestamp64", om.findStrict("xdc.runtime.Types.Timestamp64", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.Timestamp64", "xdc.runtime"));
        vo.bind("FreqHz", om.findStrict("xdc.runtime.Types.FreqHz", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.FreqHz", "xdc.runtime"));
        vo.bind("Common$", om.findStrict("xdc.runtime.Types.Common$", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.Common$", "xdc.runtime"));
        vo.bind("__struct__1", om.findStrict("xdc.runtime.Types.__struct__1", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.__struct__1", "xdc.runtime"));
        vo.bind("__struct__2", om.findStrict("xdc.runtime.Types.__struct__2", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.__struct__2", "xdc.runtime"));
        vo.bind("__struct__3", om.findStrict("xdc.runtime.Types.__struct__3", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.__struct__3", "xdc.runtime"));
        vo.bind("RtaDecoderData", om.findStrict("xdc.runtime.Types.RtaDecoderData", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.RtaDecoderData", "xdc.runtime"));
        vo.bind("ViewInfo", om.findStrict("xdc.runtime.Types.ViewInfo", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.ViewInfo", "xdc.runtime"));
        vo.bind("LoggerFxn4", om.findStrict("xdc.runtime.Types.LoggerFxn4", "xdc.runtime"));
        vo.bind("LoggerFxn8", om.findStrict("xdc.runtime.Types.LoggerFxn8", "xdc.runtime"));
        vo.bind("Vec", om.findStrict("xdc.runtime.Types.Vec", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.Vec", "xdc.runtime"));
        vo.bind("Link", om.findStrict("xdc.runtime.Types.Link", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.Link", "xdc.runtime"));
        vo.bind("ModHdr", om.findStrict("xdc.runtime.Types.ModHdr", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.ModHdr", "xdc.runtime"));
        vo.bind("ModHdrS", om.findStrict("xdc.runtime.Types.ModHdrS", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.ModHdrS", "xdc.runtime"));
        vo.bind("InstHdr", om.findStrict("xdc.runtime.Types.InstHdr", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.InstHdr", "xdc.runtime"));
        vo.bind("PrmsHdr", om.findStrict("xdc.runtime.Types.PrmsHdr", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.PrmsHdr", "xdc.runtime"));
        vo.bind("Base", om.findStrict("xdc.runtime.Types.Base", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.Base", "xdc.runtime"));
        vo.bind("SysFxns", om.findStrict("xdc.runtime.Types.SysFxns", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.SysFxns", "xdc.runtime"));
        vo.bind("SysFxns2", om.findStrict("xdc.runtime.Types.SysFxns2", "xdc.runtime"));
        tdefs.add(om.findStrict("xdc.runtime.Types.SysFxns2", "xdc.runtime"));
        vo.bind("STATIC_POLICY", om.findStrict("xdc.runtime.Types.STATIC_POLICY", "xdc.runtime"));
        vo.bind("CREATE_POLICY", om.findStrict("xdc.runtime.Types.CREATE_POLICY", "xdc.runtime"));
        vo.bind("DELETE_POLICY", om.findStrict("xdc.runtime.Types.DELETE_POLICY", "xdc.runtime"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Types_Handle__label__E", "xdc_runtime_Types_Module__startupDone__E", "xdc_runtime_Types_Object__create__E", "xdc_runtime_Types_Object__delete__E", "xdc_runtime_Types_Object__destruct__E", "xdc_runtime_Types_Object__get__E", "xdc_runtime_Types_Object__first__E", "xdc_runtime_Types_Object__next__E", "xdc_runtime_Types_Params__init__E", "xdc_runtime_Types_Proxy__abstract__E", "xdc_runtime_Types_Proxy__delegate__E", "xdc_runtime_Types_getEventId__E", "xdc_runtime_Types_getModuleId__E", "xdc_runtime_Types_makeEvent__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Types", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Types");
    }

    void IInstance$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.IInstance", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.IInstance.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.IInstance", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("xdc.runtime.IInstance.Instance", "xdc.runtime"));
        vo.bind("Params", om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.runtime.IInstance.Params", "xdc.runtime")).newInstance());
        vo.bind("Handle", om.findStrict("xdc.runtime.IInstance.Handle", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IInstance", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IInstance");
        vo.seal(null);
    }

    void LoggerBuf_TimestampProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.LoggerBuf_TimestampProxy", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf_TimestampProxy.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.LoggerBuf_TimestampProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("get32", om.findStrict("xdc.runtime.LoggerBuf_TimestampProxy.get32", "xdc.runtime"));
        vo.bind("get64", om.findStrict("xdc.runtime.LoggerBuf_TimestampProxy.get64", "xdc.runtime"));
        vo.bind("getFreq", om.findStrict("xdc.runtime.LoggerBuf_TimestampProxy.getFreq", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__Handle__label", "xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__Module__startupDone", "xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__Object__create", "xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__Object__delete", "xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__Object__destruct", "xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__Object__get", "xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__Object__first", "xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__Object__next", "xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__Params__init", "xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__Proxy__abstract", "xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__Proxy__delegate", "xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__get32", "xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__get64", "xdc_runtime_LoggerBuf_TimestampProxy_DELEGATE__getFreq"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        loggables.add(Global.newObject("name", "get32", "entry", "", "exit", "0x%x"));
        loggables.add(Global.newObject("name", "get64", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "getFreq", "entry", "%p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("LoggerBuf_TimestampProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("LoggerBuf_TimestampProxy");
    }

    void LoggerBuf_Module_GateProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.LoggerBuf_Module_GateProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Instance", "xdc.runtime"));
        vo.bind("Params", om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Params", "xdc.runtime"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Params", "xdc.runtime")).newInstance());
        vo.bind("Handle", om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Handle", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
            vo.bind("__initObject", Global.get("xdc$runtime$LoggerBuf_Module_GateProxy$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.query", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__Handle__label", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__Module__startupDone", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__Object__create", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__Object__delete", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__Object__destruct", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__Object__get", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__Object__first", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__Object__next", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__Params__init", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__Proxy__abstract", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__Proxy__delegate", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__queryMeta", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__query", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__enter", "xdc_runtime_LoggerBuf_Module_GateProxy_DELEGATE__leave"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Object", "xdc.runtime"));
        vo.bind("Instance_State", om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy.Instance_State", "xdc.runtime"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        loggables.add(Global.newObject("name", "query", "entry", "%d", "exit", "%d"));
        loggables.add(Global.newObject("name", "enter", "entry", "%p", "exit", "%p"));
        loggables.add(Global.newObject("name", "leave", "entry", "%p, %p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("LoggerBuf_Module_GateProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("LoggerBuf_Module_GateProxy");
    }

    void LoggerSys_TimestampProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.LoggerSys_TimestampProxy", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.LoggerSys_TimestampProxy.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.LoggerSys_TimestampProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("get32", om.findStrict("xdc.runtime.LoggerSys_TimestampProxy.get32", "xdc.runtime"));
        vo.bind("get64", om.findStrict("xdc.runtime.LoggerSys_TimestampProxy.get64", "xdc.runtime"));
        vo.bind("getFreq", om.findStrict("xdc.runtime.LoggerSys_TimestampProxy.getFreq", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__Handle__label", "xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__Module__startupDone", "xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__Object__create", "xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__Object__delete", "xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__Object__destruct", "xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__Object__get", "xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__Object__first", "xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__Object__next", "xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__Params__init", "xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__Proxy__abstract", "xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__Proxy__delegate", "xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__get32", "xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__get64", "xdc_runtime_LoggerSys_TimestampProxy_DELEGATE__getFreq"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        loggables.add(Global.newObject("name", "get32", "entry", "", "exit", "0x%x"));
        loggables.add(Global.newObject("name", "get64", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "getFreq", "entry", "%p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("LoggerSys_TimestampProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("LoggerSys_TimestampProxy");
    }

    void Main_Module_GateProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Main_Module_GateProxy", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Main_Module_GateProxy.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Main_Module_GateProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("xdc.runtime.Main_Module_GateProxy.Instance", "xdc.runtime"));
        vo.bind("Params", om.findStrict("xdc.runtime.Main_Module_GateProxy.Params", "xdc.runtime"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.runtime.Main_Module_GateProxy.Params", "xdc.runtime")).newInstance());
        vo.bind("Handle", om.findStrict("xdc.runtime.Main_Module_GateProxy.Handle", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
            vo.bind("__initObject", Global.get("xdc$runtime$Main_Module_GateProxy$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("xdc.runtime.Main_Module_GateProxy.query", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Main_Module_GateProxy_DELEGATE__Handle__label", "xdc_runtime_Main_Module_GateProxy_DELEGATE__Module__startupDone", "xdc_runtime_Main_Module_GateProxy_DELEGATE__Object__create", "xdc_runtime_Main_Module_GateProxy_DELEGATE__Object__delete", "xdc_runtime_Main_Module_GateProxy_DELEGATE__Object__destruct", "xdc_runtime_Main_Module_GateProxy_DELEGATE__Object__get", "xdc_runtime_Main_Module_GateProxy_DELEGATE__Object__first", "xdc_runtime_Main_Module_GateProxy_DELEGATE__Object__next", "xdc_runtime_Main_Module_GateProxy_DELEGATE__Params__init", "xdc_runtime_Main_Module_GateProxy_DELEGATE__Proxy__abstract", "xdc_runtime_Main_Module_GateProxy_DELEGATE__Proxy__delegate", "xdc_runtime_Main_Module_GateProxy_DELEGATE__queryMeta", "xdc_runtime_Main_Module_GateProxy_DELEGATE__query", "xdc_runtime_Main_Module_GateProxy_DELEGATE__enter", "xdc_runtime_Main_Module_GateProxy_DELEGATE__leave"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.runtime.Main_Module_GateProxy.Object", "xdc.runtime"));
        vo.bind("Instance_State", om.findStrict("xdc.runtime.Main_Module_GateProxy.Instance_State", "xdc.runtime"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        loggables.add(Global.newObject("name", "query", "entry", "%d", "exit", "%d"));
        loggables.add(Global.newObject("name", "enter", "entry", "%p", "exit", "%p"));
        loggables.add(Global.newObject("name", "leave", "entry", "%p, %p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Main_Module_GateProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Main_Module_GateProxy");
    }

    void Memory_HeapProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Memory_HeapProxy", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Memory_HeapProxy.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Memory_HeapProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("xdc.runtime.Memory_HeapProxy.Instance", "xdc.runtime"));
        vo.bind("Params", om.findStrict("xdc.runtime.Memory_HeapProxy.Params", "xdc.runtime"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.runtime.Memory_HeapProxy.Params", "xdc.runtime")).newInstance());
        vo.bind("Handle", om.findStrict("xdc.runtime.Memory_HeapProxy.Handle", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
            vo.bind("__initObject", Global.get("xdc$runtime$Memory_HeapProxy$$__initObject"));
        }//isCFG
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Memory_HeapProxy_DELEGATE__Handle__label", "xdc_runtime_Memory_HeapProxy_DELEGATE__Module__startupDone", "xdc_runtime_Memory_HeapProxy_DELEGATE__Object__create", "xdc_runtime_Memory_HeapProxy_DELEGATE__Object__delete", "xdc_runtime_Memory_HeapProxy_DELEGATE__Object__destruct", "xdc_runtime_Memory_HeapProxy_DELEGATE__Object__get", "xdc_runtime_Memory_HeapProxy_DELEGATE__Object__first", "xdc_runtime_Memory_HeapProxy_DELEGATE__Object__next", "xdc_runtime_Memory_HeapProxy_DELEGATE__Params__init", "xdc_runtime_Memory_HeapProxy_DELEGATE__Proxy__abstract", "xdc_runtime_Memory_HeapProxy_DELEGATE__Proxy__delegate", "xdc_runtime_Memory_HeapProxy_DELEGATE__alloc", "xdc_runtime_Memory_HeapProxy_DELEGATE__free", "xdc_runtime_Memory_HeapProxy_DELEGATE__isBlocking", "xdc_runtime_Memory_HeapProxy_DELEGATE__getStats"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.runtime.Memory_HeapProxy.Object", "xdc.runtime"));
        vo.bind("Instance_State", om.findStrict("xdc.runtime.Memory_HeapProxy.Instance_State", "xdc.runtime"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        loggables.add(Global.newObject("name", "alloc", "entry", "%p, 0x%x, 0x%x, %p", "exit", "%p"));
        loggables.add(Global.newObject("name", "free", "entry", "%p, %p, 0x%x", "exit", ""));
        loggables.add(Global.newObject("name", "isBlocking", "entry", "%p", "exit", "%d"));
        loggables.add(Global.newObject("name", "getStats", "entry", "%p, %p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Memory_HeapProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Memory_HeapProxy");
    }

    void System_SupportProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.System_SupportProxy", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.System_SupportProxy.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.System_SupportProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("abort", om.findStrict("xdc.runtime.System_SupportProxy.abort", "xdc.runtime"));
        vo.bind("exit", om.findStrict("xdc.runtime.System_SupportProxy.exit", "xdc.runtime"));
        vo.bind("flush", om.findStrict("xdc.runtime.System_SupportProxy.flush", "xdc.runtime"));
        vo.bind("putch", om.findStrict("xdc.runtime.System_SupportProxy.putch", "xdc.runtime"));
        vo.bind("ready", om.findStrict("xdc.runtime.System_SupportProxy.ready", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_System_SupportProxy_DELEGATE__Handle__label", "xdc_runtime_System_SupportProxy_DELEGATE__Module__startupDone", "xdc_runtime_System_SupportProxy_DELEGATE__Object__create", "xdc_runtime_System_SupportProxy_DELEGATE__Object__delete", "xdc_runtime_System_SupportProxy_DELEGATE__Object__destruct", "xdc_runtime_System_SupportProxy_DELEGATE__Object__get", "xdc_runtime_System_SupportProxy_DELEGATE__Object__first", "xdc_runtime_System_SupportProxy_DELEGATE__Object__next", "xdc_runtime_System_SupportProxy_DELEGATE__Params__init", "xdc_runtime_System_SupportProxy_DELEGATE__Proxy__abstract", "xdc_runtime_System_SupportProxy_DELEGATE__Proxy__delegate", "xdc_runtime_System_SupportProxy_DELEGATE__abort", "xdc_runtime_System_SupportProxy_DELEGATE__exit", "xdc_runtime_System_SupportProxy_DELEGATE__flush", "xdc_runtime_System_SupportProxy_DELEGATE__putch", "xdc_runtime_System_SupportProxy_DELEGATE__ready"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        loggables.add(Global.newObject("name", "abort", "entry", "\"%s\"", "exit", ""));
        loggables.add(Global.newObject("name", "exit", "entry", "%d", "exit", ""));
        loggables.add(Global.newObject("name", "flush", "entry", "", "exit", ""));
        loggables.add(Global.newObject("name", "putch", "entry", "%d", "exit", ""));
        loggables.add(Global.newObject("name", "ready", "entry", "", "exit", "%d"));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("System_SupportProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("System_SupportProxy");
    }

    void System_Module_GateProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.System_Module_GateProxy", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.System_Module_GateProxy.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.System_Module_GateProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("xdc.runtime.System_Module_GateProxy.Instance", "xdc.runtime"));
        vo.bind("Params", om.findStrict("xdc.runtime.System_Module_GateProxy.Params", "xdc.runtime"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("xdc.runtime.System_Module_GateProxy.Params", "xdc.runtime")).newInstance());
        vo.bind("Handle", om.findStrict("xdc.runtime.System_Module_GateProxy.Handle", "xdc.runtime"));
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
            vo.bind("__initObject", Global.get("xdc$runtime$System_Module_GateProxy$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("xdc.runtime.System_Module_GateProxy.query", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_System_Module_GateProxy_DELEGATE__Handle__label", "xdc_runtime_System_Module_GateProxy_DELEGATE__Module__startupDone", "xdc_runtime_System_Module_GateProxy_DELEGATE__Object__create", "xdc_runtime_System_Module_GateProxy_DELEGATE__Object__delete", "xdc_runtime_System_Module_GateProxy_DELEGATE__Object__destruct", "xdc_runtime_System_Module_GateProxy_DELEGATE__Object__get", "xdc_runtime_System_Module_GateProxy_DELEGATE__Object__first", "xdc_runtime_System_Module_GateProxy_DELEGATE__Object__next", "xdc_runtime_System_Module_GateProxy_DELEGATE__Params__init", "xdc_runtime_System_Module_GateProxy_DELEGATE__Proxy__abstract", "xdc_runtime_System_Module_GateProxy_DELEGATE__Proxy__delegate", "xdc_runtime_System_Module_GateProxy_DELEGATE__queryMeta", "xdc_runtime_System_Module_GateProxy_DELEGATE__query", "xdc_runtime_System_Module_GateProxy_DELEGATE__enter", "xdc_runtime_System_Module_GateProxy_DELEGATE__leave"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("xdc.runtime.System_Module_GateProxy.Object", "xdc.runtime"));
        vo.bind("Instance_State", om.findStrict("xdc.runtime.System_Module_GateProxy.Instance_State", "xdc.runtime"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        loggables.add(Global.newObject("name", "query", "entry", "%d", "exit", "%d"));
        loggables.add(Global.newObject("name", "enter", "entry", "%p", "exit", "%p"));
        loggables.add(Global.newObject("name", "leave", "entry", "%p, %p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("System_Module_GateProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("System_Module_GateProxy");
    }

    void Timestamp_SupportProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("xdc.runtime.Timestamp_SupportProxy", "xdc.runtime");
        po = (Proto.Obj)om.findStrict("xdc.runtime.Timestamp_SupportProxy.Module", "xdc.runtime");
        vo.init2(po, "xdc.runtime.Timestamp_SupportProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("xdc.runtime", "xdc.runtime"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "xdc.runtime")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("get32", om.findStrict("xdc.runtime.Timestamp_SupportProxy.get32", "xdc.runtime"));
        vo.bind("get64", om.findStrict("xdc.runtime.Timestamp_SupportProxy.get64", "xdc.runtime"));
        vo.bind("getFreq", om.findStrict("xdc.runtime.Timestamp_SupportProxy.getFreq", "xdc.runtime"));
        vo.bind("$$fxntab", Global.newArray("xdc_runtime_Timestamp_SupportProxy_DELEGATE__Handle__label", "xdc_runtime_Timestamp_SupportProxy_DELEGATE__Module__startupDone", "xdc_runtime_Timestamp_SupportProxy_DELEGATE__Object__create", "xdc_runtime_Timestamp_SupportProxy_DELEGATE__Object__delete", "xdc_runtime_Timestamp_SupportProxy_DELEGATE__Object__destruct", "xdc_runtime_Timestamp_SupportProxy_DELEGATE__Object__get", "xdc_runtime_Timestamp_SupportProxy_DELEGATE__Object__first", "xdc_runtime_Timestamp_SupportProxy_DELEGATE__Object__next", "xdc_runtime_Timestamp_SupportProxy_DELEGATE__Params__init", "xdc_runtime_Timestamp_SupportProxy_DELEGATE__Proxy__abstract", "xdc_runtime_Timestamp_SupportProxy_DELEGATE__Proxy__delegate", "xdc_runtime_Timestamp_SupportProxy_DELEGATE__get32", "xdc_runtime_Timestamp_SupportProxy_DELEGATE__get64", "xdc_runtime_Timestamp_SupportProxy_DELEGATE__getFreq"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        loggables.add(Global.newObject("name", "get32", "entry", "", "exit", "0x%x"));
        loggables.add(Global.newObject("name", "get64", "entry", "%p", "exit", ""));
        loggables.add(Global.newObject("name", "getFreq", "entry", "%p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Timestamp_SupportProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Timestamp_SupportProxy");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "xdc.runtime")).findStrict("PARAMS", "xdc.runtime");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("xdc.runtime.GateNull", "xdc.runtime")).findStrict("PARAMS", "xdc.runtime");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("xdc.runtime.LoggerBuf", "xdc.runtime")).findStrict("PARAMS", "xdc.runtime");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("xdc.runtime.LoggerSys", "xdc.runtime")).findStrict("PARAMS", "xdc.runtime");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("xdc.runtime.HeapMin", "xdc.runtime")).findStrict("PARAMS", "xdc.runtime");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("xdc.runtime.HeapStd", "xdc.runtime")).findStrict("PARAMS", "xdc.runtime");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy", "xdc.runtime")).findStrict("PARAMS", "xdc.runtime");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("xdc.runtime.Main_Module_GateProxy", "xdc.runtime")).findStrict("PARAMS", "xdc.runtime");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("xdc.runtime.Memory_HeapProxy", "xdc.runtime")).findStrict("PARAMS", "xdc.runtime");
            Global.put(dstP, "instance", srcP);
            dstP = (Scriptable)((XScriptO)om.findStrict("xdc.runtime.System_Module_GateProxy", "xdc.runtime")).findStrict("PARAMS", "xdc.runtime");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Assert", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Core", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Defaults", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Diags", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Error", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Gate", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.GateNull", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Log", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.LoggerBuf", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.LoggerSys", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Main", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Memory", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.HeapMin", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.HeapStd", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Rta", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Startup", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Reset", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.System", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.SysStd", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.SysMin", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Text", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Timestamp", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.TimestampNull", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.TimestampStd", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Types", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.LoggerBuf_TimestampProxy", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.LoggerBuf_Module_GateProxy", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.LoggerSys_TimestampProxy", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Main_Module_GateProxy", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Memory_HeapProxy", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.System_SupportProxy", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.System_Module_GateProxy", "xdc.runtime"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("xdc.runtime.Timestamp_SupportProxy", "xdc.runtime"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("xdc.runtime.LoggerBuf", "xdc.runtime");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"Records", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE_DATA"), "viewInitFxn", "viewInitRecords", "structName", "RecordView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("xdc.runtime.SysMin", "xdc.runtime");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Module", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE"), "viewInitFxn", "viewInitModule", "structName", "ModuleView")}), Global.newArray(new Object[]{"OutputBuffer", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE_DATA"), "viewInitFxn", "viewInitOutputBuffer", "structName", "BufferEntryView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("xdc.runtime.IModule")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Assert")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Core")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Defaults")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Diags")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Error")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Gate")).bless();
        ((Value.Obj)om.getv("xdc.runtime.IGateProvider")).bless();
        ((Value.Obj)om.getv("xdc.runtime.GateNull")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Log")).bless();
        ((Value.Obj)om.getv("xdc.runtime.ILogger")).bless();
        ((Value.Obj)om.getv("xdc.runtime.LoggerBuf")).bless();
        ((Value.Obj)om.getv("xdc.runtime.LoggerSys")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Main")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Memory")).bless();
        ((Value.Obj)om.getv("xdc.runtime.IHeap")).bless();
        ((Value.Obj)om.getv("xdc.runtime.HeapMin")).bless();
        ((Value.Obj)om.getv("xdc.runtime.HeapStd")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Rta")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Startup")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Reset")).bless();
        ((Value.Obj)om.getv("xdc.runtime.System")).bless();
        ((Value.Obj)om.getv("xdc.runtime.ISystemSupport")).bless();
        ((Value.Obj)om.getv("xdc.runtime.SysStd")).bless();
        ((Value.Obj)om.getv("xdc.runtime.SysMin")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Text")).bless();
        ((Value.Obj)om.getv("xdc.runtime.ITimestampClient")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Timestamp")).bless();
        ((Value.Obj)om.getv("xdc.runtime.ITimestampProvider")).bless();
        ((Value.Obj)om.getv("xdc.runtime.TimestampNull")).bless();
        ((Value.Obj)om.getv("xdc.runtime.TimestampStd")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Types")).bless();
        ((Value.Obj)om.getv("xdc.runtime.IInstance")).bless();
        ((Value.Obj)om.getv("xdc.runtime.LoggerBuf_TimestampProxy")).bless();
        ((Value.Obj)om.getv("xdc.runtime.LoggerBuf_Module_GateProxy")).bless();
        ((Value.Obj)om.getv("xdc.runtime.LoggerSys_TimestampProxy")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Main_Module_GateProxy")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Memory_HeapProxy")).bless();
        ((Value.Obj)om.getv("xdc.runtime.System_SupportProxy")).bless();
        ((Value.Obj)om.getv("xdc.runtime.System_Module_GateProxy")).bless();
        ((Value.Obj)om.getv("xdc.runtime.Timestamp_SupportProxy")).bless();
        ((Value.Arr)om.findStrict("$packages", "xdc.runtime")).add(pkgV);
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
        IModule$$OBJECTS();
        Assert$$OBJECTS();
        Core$$OBJECTS();
        Defaults$$OBJECTS();
        Diags$$OBJECTS();
        Error$$OBJECTS();
        Gate$$OBJECTS();
        IGateProvider$$OBJECTS();
        GateNull$$OBJECTS();
        Log$$OBJECTS();
        ILogger$$OBJECTS();
        LoggerBuf$$OBJECTS();
        LoggerSys$$OBJECTS();
        Main$$OBJECTS();
        Memory$$OBJECTS();
        IHeap$$OBJECTS();
        HeapMin$$OBJECTS();
        HeapStd$$OBJECTS();
        Rta$$OBJECTS();
        Startup$$OBJECTS();
        Reset$$OBJECTS();
        System$$OBJECTS();
        ISystemSupport$$OBJECTS();
        SysStd$$OBJECTS();
        SysMin$$OBJECTS();
        Text$$OBJECTS();
        ITimestampClient$$OBJECTS();
        Timestamp$$OBJECTS();
        ITimestampProvider$$OBJECTS();
        TimestampNull$$OBJECTS();
        TimestampStd$$OBJECTS();
        Types$$OBJECTS();
        IInstance$$OBJECTS();
        LoggerBuf_TimestampProxy$$OBJECTS();
        LoggerBuf_Module_GateProxy$$OBJECTS();
        LoggerSys_TimestampProxy$$OBJECTS();
        Main_Module_GateProxy$$OBJECTS();
        Memory_HeapProxy$$OBJECTS();
        System_SupportProxy$$OBJECTS();
        System_Module_GateProxy$$OBJECTS();
        Timestamp_SupportProxy$$OBJECTS();
        IModule$$CONSTS();
        Assert$$CONSTS();
        Core$$CONSTS();
        Defaults$$CONSTS();
        Diags$$CONSTS();
        Error$$CONSTS();
        Gate$$CONSTS();
        IGateProvider$$CONSTS();
        GateNull$$CONSTS();
        Log$$CONSTS();
        ILogger$$CONSTS();
        LoggerBuf$$CONSTS();
        LoggerSys$$CONSTS();
        Main$$CONSTS();
        Memory$$CONSTS();
        IHeap$$CONSTS();
        HeapMin$$CONSTS();
        HeapStd$$CONSTS();
        Rta$$CONSTS();
        Startup$$CONSTS();
        Reset$$CONSTS();
        System$$CONSTS();
        ISystemSupport$$CONSTS();
        SysStd$$CONSTS();
        SysMin$$CONSTS();
        Text$$CONSTS();
        ITimestampClient$$CONSTS();
        Timestamp$$CONSTS();
        ITimestampProvider$$CONSTS();
        TimestampNull$$CONSTS();
        TimestampStd$$CONSTS();
        Types$$CONSTS();
        IInstance$$CONSTS();
        LoggerBuf_TimestampProxy$$CONSTS();
        LoggerBuf_Module_GateProxy$$CONSTS();
        LoggerSys_TimestampProxy$$CONSTS();
        Main_Module_GateProxy$$CONSTS();
        Memory_HeapProxy$$CONSTS();
        System_SupportProxy$$CONSTS();
        System_Module_GateProxy$$CONSTS();
        Timestamp_SupportProxy$$CONSTS();
        IModule$$CREATES();
        Assert$$CREATES();
        Core$$CREATES();
        Defaults$$CREATES();
        Diags$$CREATES();
        Error$$CREATES();
        Gate$$CREATES();
        IGateProvider$$CREATES();
        GateNull$$CREATES();
        Log$$CREATES();
        ILogger$$CREATES();
        LoggerBuf$$CREATES();
        LoggerSys$$CREATES();
        Main$$CREATES();
        Memory$$CREATES();
        IHeap$$CREATES();
        HeapMin$$CREATES();
        HeapStd$$CREATES();
        Rta$$CREATES();
        Startup$$CREATES();
        Reset$$CREATES();
        System$$CREATES();
        ISystemSupport$$CREATES();
        SysStd$$CREATES();
        SysMin$$CREATES();
        Text$$CREATES();
        ITimestampClient$$CREATES();
        Timestamp$$CREATES();
        ITimestampProvider$$CREATES();
        TimestampNull$$CREATES();
        TimestampStd$$CREATES();
        Types$$CREATES();
        IInstance$$CREATES();
        LoggerBuf_TimestampProxy$$CREATES();
        LoggerBuf_Module_GateProxy$$CREATES();
        LoggerSys_TimestampProxy$$CREATES();
        Main_Module_GateProxy$$CREATES();
        Memory_HeapProxy$$CREATES();
        System_SupportProxy$$CREATES();
        System_Module_GateProxy$$CREATES();
        Timestamp_SupportProxy$$CREATES();
        IModule$$FUNCTIONS();
        Assert$$FUNCTIONS();
        Core$$FUNCTIONS();
        Defaults$$FUNCTIONS();
        Diags$$FUNCTIONS();
        Error$$FUNCTIONS();
        Gate$$FUNCTIONS();
        IGateProvider$$FUNCTIONS();
        GateNull$$FUNCTIONS();
        Log$$FUNCTIONS();
        ILogger$$FUNCTIONS();
        LoggerBuf$$FUNCTIONS();
        LoggerSys$$FUNCTIONS();
        Main$$FUNCTIONS();
        Memory$$FUNCTIONS();
        IHeap$$FUNCTIONS();
        HeapMin$$FUNCTIONS();
        HeapStd$$FUNCTIONS();
        Rta$$FUNCTIONS();
        Startup$$FUNCTIONS();
        Reset$$FUNCTIONS();
        System$$FUNCTIONS();
        ISystemSupport$$FUNCTIONS();
        SysStd$$FUNCTIONS();
        SysMin$$FUNCTIONS();
        Text$$FUNCTIONS();
        ITimestampClient$$FUNCTIONS();
        Timestamp$$FUNCTIONS();
        ITimestampProvider$$FUNCTIONS();
        TimestampNull$$FUNCTIONS();
        TimestampStd$$FUNCTIONS();
        Types$$FUNCTIONS();
        IInstance$$FUNCTIONS();
        LoggerBuf_TimestampProxy$$FUNCTIONS();
        LoggerBuf_Module_GateProxy$$FUNCTIONS();
        LoggerSys_TimestampProxy$$FUNCTIONS();
        Main_Module_GateProxy$$FUNCTIONS();
        Memory_HeapProxy$$FUNCTIONS();
        System_SupportProxy$$FUNCTIONS();
        System_Module_GateProxy$$FUNCTIONS();
        Timestamp_SupportProxy$$FUNCTIONS();
        IModule$$SIZES();
        Assert$$SIZES();
        Core$$SIZES();
        Defaults$$SIZES();
        Diags$$SIZES();
        Error$$SIZES();
        Gate$$SIZES();
        IGateProvider$$SIZES();
        GateNull$$SIZES();
        Log$$SIZES();
        ILogger$$SIZES();
        LoggerBuf$$SIZES();
        LoggerSys$$SIZES();
        Main$$SIZES();
        Memory$$SIZES();
        IHeap$$SIZES();
        HeapMin$$SIZES();
        HeapStd$$SIZES();
        Rta$$SIZES();
        Startup$$SIZES();
        Reset$$SIZES();
        System$$SIZES();
        ISystemSupport$$SIZES();
        SysStd$$SIZES();
        SysMin$$SIZES();
        Text$$SIZES();
        ITimestampClient$$SIZES();
        Timestamp$$SIZES();
        ITimestampProvider$$SIZES();
        TimestampNull$$SIZES();
        TimestampStd$$SIZES();
        Types$$SIZES();
        IInstance$$SIZES();
        LoggerBuf_TimestampProxy$$SIZES();
        LoggerBuf_Module_GateProxy$$SIZES();
        LoggerSys_TimestampProxy$$SIZES();
        Main_Module_GateProxy$$SIZES();
        Memory_HeapProxy$$SIZES();
        System_SupportProxy$$SIZES();
        System_Module_GateProxy$$SIZES();
        Timestamp_SupportProxy$$SIZES();
        IModule$$TYPES();
        Assert$$TYPES();
        Core$$TYPES();
        Defaults$$TYPES();
        Diags$$TYPES();
        Error$$TYPES();
        Gate$$TYPES();
        IGateProvider$$TYPES();
        GateNull$$TYPES();
        Log$$TYPES();
        ILogger$$TYPES();
        LoggerBuf$$TYPES();
        LoggerSys$$TYPES();
        Main$$TYPES();
        Memory$$TYPES();
        IHeap$$TYPES();
        HeapMin$$TYPES();
        HeapStd$$TYPES();
        Rta$$TYPES();
        Startup$$TYPES();
        Reset$$TYPES();
        System$$TYPES();
        ISystemSupport$$TYPES();
        SysStd$$TYPES();
        SysMin$$TYPES();
        Text$$TYPES();
        ITimestampClient$$TYPES();
        Timestamp$$TYPES();
        ITimestampProvider$$TYPES();
        TimestampNull$$TYPES();
        TimestampStd$$TYPES();
        Types$$TYPES();
        IInstance$$TYPES();
        LoggerBuf_TimestampProxy$$TYPES();
        LoggerBuf_Module_GateProxy$$TYPES();
        LoggerSys_TimestampProxy$$TYPES();
        Main_Module_GateProxy$$TYPES();
        Memory_HeapProxy$$TYPES();
        System_SupportProxy$$TYPES();
        System_Module_GateProxy$$TYPES();
        Timestamp_SupportProxy$$TYPES();
        if (isROV) {
            IModule$$ROV();
            Assert$$ROV();
            Core$$ROV();
            Defaults$$ROV();
            Diags$$ROV();
            Error$$ROV();
            Gate$$ROV();
            IGateProvider$$ROV();
            GateNull$$ROV();
            Log$$ROV();
            ILogger$$ROV();
            LoggerBuf$$ROV();
            LoggerSys$$ROV();
            Main$$ROV();
            Memory$$ROV();
            IHeap$$ROV();
            HeapMin$$ROV();
            HeapStd$$ROV();
            Rta$$ROV();
            Startup$$ROV();
            Reset$$ROV();
            System$$ROV();
            ISystemSupport$$ROV();
            SysStd$$ROV();
            SysMin$$ROV();
            Text$$ROV();
            ITimestampClient$$ROV();
            Timestamp$$ROV();
            ITimestampProvider$$ROV();
            TimestampNull$$ROV();
            TimestampStd$$ROV();
            Types$$ROV();
            IInstance$$ROV();
            LoggerBuf_TimestampProxy$$ROV();
            LoggerBuf_Module_GateProxy$$ROV();
            LoggerSys_TimestampProxy$$ROV();
            Main_Module_GateProxy$$ROV();
            Memory_HeapProxy$$ROV();
            System_SupportProxy$$ROV();
            System_Module_GateProxy$$ROV();
            Timestamp_SupportProxy$$ROV();
        }//isROV
        $$SINGLETONS();
        IModule$$SINGLETONS();
        Assert$$SINGLETONS();
        Core$$SINGLETONS();
        Defaults$$SINGLETONS();
        Diags$$SINGLETONS();
        Error$$SINGLETONS();
        Gate$$SINGLETONS();
        IGateProvider$$SINGLETONS();
        GateNull$$SINGLETONS();
        Log$$SINGLETONS();
        ILogger$$SINGLETONS();
        LoggerBuf$$SINGLETONS();
        LoggerSys$$SINGLETONS();
        Main$$SINGLETONS();
        Memory$$SINGLETONS();
        IHeap$$SINGLETONS();
        HeapMin$$SINGLETONS();
        HeapStd$$SINGLETONS();
        Rta$$SINGLETONS();
        Startup$$SINGLETONS();
        Reset$$SINGLETONS();
        System$$SINGLETONS();
        ISystemSupport$$SINGLETONS();
        SysStd$$SINGLETONS();
        SysMin$$SINGLETONS();
        Text$$SINGLETONS();
        ITimestampClient$$SINGLETONS();
        Timestamp$$SINGLETONS();
        ITimestampProvider$$SINGLETONS();
        TimestampNull$$SINGLETONS();
        TimestampStd$$SINGLETONS();
        Types$$SINGLETONS();
        IInstance$$SINGLETONS();
        LoggerBuf_TimestampProxy$$SINGLETONS();
        LoggerBuf_Module_GateProxy$$SINGLETONS();
        LoggerSys_TimestampProxy$$SINGLETONS();
        Main_Module_GateProxy$$SINGLETONS();
        Memory_HeapProxy$$SINGLETONS();
        System_SupportProxy$$SINGLETONS();
        System_Module_GateProxy$$SINGLETONS();
        Timestamp_SupportProxy$$SINGLETONS();
        $$INITIALIZATION();
    }
}
