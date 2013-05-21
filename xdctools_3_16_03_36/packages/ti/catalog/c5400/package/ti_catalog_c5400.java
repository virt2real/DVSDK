/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-u15
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.*;

public class ti_catalog_c5400
{
    static final String VERS = "@(#) xdc-u15\n";

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
        Global.callFxn("loadPackage", xdcO, "xdc.platform");
        Global.callFxn("loadPackage", xdcO, "ti.catalog");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.catalog.c5400.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.catalog.c5400", new Value.Obj("ti.catalog.c5400", pkgP));
    }

    void ITMS320C54xx$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.ITMS320C54xx.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.ITMS320C54xx", new Value.Obj("ti.catalog.c5400.ITMS320C54xx", po));
        pkgV.bind("ITMS320C54xx", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.ITMS320C54xx.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.ITMS320C54xx$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.ITMS320C54xx.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.ITMS320C54xx$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.ITMS320C54xx.Params", new Proto.Str(po, true));
    }

    void TMS320C5401$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5401.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5401", new Value.Obj("ti.catalog.c5400.TMS320C5401", po));
        pkgV.bind("TMS320C5401", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5401.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5401$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5401.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5401$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5401.Params", new Proto.Str(po, true));
    }

    void TMS320C5402$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5402.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5402", new Value.Obj("ti.catalog.c5400.TMS320C5402", po));
        pkgV.bind("TMS320C5402", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5402.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5402$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5402.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5402$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5402.Params", new Proto.Str(po, true));
    }

    void TMS320C5402A$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5402A.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5402A", new Value.Obj("ti.catalog.c5400.TMS320C5402A", po));
        pkgV.bind("TMS320C5402A", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5402A.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5402A$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5402A.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5402A$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5402A.Params", new Proto.Str(po, true));
    }

    void TMS320C5404$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5404.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5404", new Value.Obj("ti.catalog.c5400.TMS320C5404", po));
        pkgV.bind("TMS320C5404", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5404.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5404$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5404.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5404$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5404.Params", new Proto.Str(po, true));
    }

    void TMS320C5405$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5405.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5405", new Value.Obj("ti.catalog.c5400.TMS320C5405", po));
        pkgV.bind("TMS320C5405", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5405.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5405$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5405.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5405$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5405.Params", new Proto.Str(po, true));
    }

    void TMS320C5407$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5407.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5407", new Value.Obj("ti.catalog.c5400.TMS320C5407", po));
        pkgV.bind("TMS320C5407", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5407.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5407$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5407.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5407$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5407.Params", new Proto.Str(po, true));
    }

    void TMS320C5409$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5409.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5409", new Value.Obj("ti.catalog.c5400.TMS320C5409", po));
        pkgV.bind("TMS320C5409", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5409.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5409$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5409.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5409$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5409.Params", new Proto.Str(po, true));
    }

    void TMS320C5409A$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5409A.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5409A", new Value.Obj("ti.catalog.c5400.TMS320C5409A", po));
        pkgV.bind("TMS320C5409A", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5409A.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5409A$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5409A.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5409A$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5409A.Params", new Proto.Str(po, true));
    }

    void TMS320C5410$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5410.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5410", new Value.Obj("ti.catalog.c5400.TMS320C5410", po));
        pkgV.bind("TMS320C5410", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5410.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5410$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5410.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5410$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5410.Params", new Proto.Str(po, true));
    }

    void TMS320C5410A$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5410A.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5410A", new Value.Obj("ti.catalog.c5400.TMS320C5410A", po));
        pkgV.bind("TMS320C5410A", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5410A.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5410A$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5410A.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5410A$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5410A.Params", new Proto.Str(po, true));
    }

    void TMS320C5416$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5416.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5416", new Value.Obj("ti.catalog.c5400.TMS320C5416", po));
        pkgV.bind("TMS320C5416", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5416.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5416$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5416.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5416$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5416.Params", new Proto.Str(po, true));
    }

    void TMS320C5420$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5420.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5420", new Value.Obj("ti.catalog.c5400.TMS320C5420", po));
        pkgV.bind("TMS320C5420", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5420.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5420$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5420.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5420$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5420.Params", new Proto.Str(po, true));
    }

    void TMS320C5470$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5470.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5470", new Value.Obj("ti.catalog.c5400.TMS320C5470", po));
        pkgV.bind("TMS320C5470", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5470.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5470$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5470.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5470$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5470.Params", new Proto.Str(po, true));
    }

    void TMS320C5471$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5471.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C5471", new Value.Obj("ti.catalog.c5400.TMS320C5471", po));
        pkgV.bind("TMS320C5471", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C5471.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5471$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C5471.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C5471$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C5471.Params", new Proto.Str(po, true));
    }

    void TMS320CDM270$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320CDM270.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320CDM270", new Value.Obj("ti.catalog.c5400.TMS320CDM270", po));
        pkgV.bind("TMS320CDM270", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320CDM270.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320CDM270$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320CDM270.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320CDM270$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320CDM270.Params", new Proto.Str(po, true));
    }

    void TMS320CDM310$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320CDM310.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320CDM310", new Value.Obj("ti.catalog.c5400.TMS320CDM310", po));
        pkgV.bind("TMS320CDM310", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320CDM310.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320CDM310$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320CDM310.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320CDM310$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320CDM310.Params", new Proto.Str(po, true));
    }

    void TMS320CDM320$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320CDM320.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320CDM320", new Value.Obj("ti.catalog.c5400.TMS320CDM320", po));
        pkgV.bind("TMS320CDM320", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320CDM320.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320CDM320$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320CDM320.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320CDM320$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320CDM320.Params", new Proto.Str(po, true));
    }

    void TMS320C54CST$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C54CST.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5400.TMS320C54CST", new Value.Obj("ti.catalog.c5400.TMS320C54CST", po));
        pkgV.bind("TMS320C54CST", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5400.TMS320C54CST.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C54CST$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5400.TMS320C54CST.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5400.TMS320C54CST$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5400.TMS320C54CST.Params", new Proto.Str(po, true));
    }

    void ITMS320C54xx$$CONSTS()
    {
        // interface ITMS320C54xx
    }

    void TMS320C5401$$CONSTS()
    {
        // module TMS320C5401
    }

    void TMS320C5402$$CONSTS()
    {
        // module TMS320C5402
    }

    void TMS320C5402A$$CONSTS()
    {
        // module TMS320C5402A
    }

    void TMS320C5404$$CONSTS()
    {
        // module TMS320C5404
    }

    void TMS320C5405$$CONSTS()
    {
        // module TMS320C5405
    }

    void TMS320C5407$$CONSTS()
    {
        // module TMS320C5407
    }

    void TMS320C5409$$CONSTS()
    {
        // module TMS320C5409
    }

    void TMS320C5409A$$CONSTS()
    {
        // module TMS320C5409A
    }

    void TMS320C5410$$CONSTS()
    {
        // module TMS320C5410
    }

    void TMS320C5410A$$CONSTS()
    {
        // module TMS320C5410A
    }

    void TMS320C5416$$CONSTS()
    {
        // module TMS320C5416
    }

    void TMS320C5420$$CONSTS()
    {
        // module TMS320C5420
    }

    void TMS320C5470$$CONSTS()
    {
        // module TMS320C5470
    }

    void TMS320C5471$$CONSTS()
    {
        // module TMS320C5471
    }

    void TMS320CDM270$$CONSTS()
    {
        // module TMS320CDM270
    }

    void TMS320CDM310$$CONSTS()
    {
        // module TMS320CDM310
    }

    void TMS320CDM320$$CONSTS()
    {
        // module TMS320CDM320
    }

    void TMS320C54CST$$CONSTS()
    {
        // module TMS320C54CST
    }

    void ITMS320C54xx$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TMS320C5401$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5401$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5401.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5401.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5401.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5401$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5401'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5401.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5401$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5401.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5401$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5401.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5401$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5401'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5402$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5402$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5402.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5402.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5402.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5402$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5402'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5402.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5402$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5402.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5402$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5402.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5402$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5402'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5402A$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5402A$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5402A.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5402A.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5402A.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5402A$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5402A'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5402A.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5402A$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5402A.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5402A$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5402A.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5402A$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5402A'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5404$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5404$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5404.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5404.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5404.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5404$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5404'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5404.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5404$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5404.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5404$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5404.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5404$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5404'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5405$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5405$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5405.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5405.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5405.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5405$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5405'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5405.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5405$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5405.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5405$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5405.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5405$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5405'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5407$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5407$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5407.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5407.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5407.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5407$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5407'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5407.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5407$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5407.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5407$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5407.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5407$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5407'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5409$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5409$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5409.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5409.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5409.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5409$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5409'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5409.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5409$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5409.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5409$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5409.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5409$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5409'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5409A$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5409A$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5409A.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5409A.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5409A.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5409A$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5409A'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5409A.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5409A$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5409A.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5409A$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5409A.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5409A$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5409A'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5410$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5410$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5410.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5410.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5410.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5410$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5410'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5410.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5410$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5410.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5410$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5410.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5410$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5410'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5410A$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5410A$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5410A.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5410A.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5410A.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5410A$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5410A'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5410A.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5410A$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5410A.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5410A$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5410A.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5410A$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5410A'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5416$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5416$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5416.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5416.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5416.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5416$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5416'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5416.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5416$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5416.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5416$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5416.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5416$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5416'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5420$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5420$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5420.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5420.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5420.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5420$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5420'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5420.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5420$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5420.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5420$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5420.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5420$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5420'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5470$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5470$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5470.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5470.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5470.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5470$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5470'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5470.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5470$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5470.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5470$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5470.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5470$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5470'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5471$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5471$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5471.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C5471.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5471.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5471$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5471'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C5471.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C5471$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C5471.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5471$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C5471.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C5471$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C5471'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320CDM270$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320CDM270$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320CDM270.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320CDM270.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320CDM270.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320CDM270$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320CDM270'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320CDM270.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320CDM270$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320CDM270.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320CDM270$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320CDM270.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320CDM270$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320CDM270'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320CDM310$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320CDM310$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320CDM310.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320CDM310.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320CDM310.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320CDM310$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320CDM310'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320CDM310.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320CDM310$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320CDM310.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320CDM310$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320CDM310.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320CDM310$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320CDM310'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320CDM320$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320CDM320$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320CDM320.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320CDM320.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320CDM320.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320CDM320$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320CDM320'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320CDM320.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320CDM320$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320CDM320.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320CDM320$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320CDM320.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320CDM320$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320CDM320'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C54CST$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C54CST$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C54CST.Module", "ti.catalog.c5400"), om.findStrict("ti.catalog.c5400.TMS320C54CST.Instance", "ti.catalog.c5400"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C54CST.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C54CST$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C54CST'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5400.TMS320C54CST.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5400']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5400.TMS320C54CST$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5400.TMS320C54CST.Module", "ti.catalog.c5400"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5400.TMS320C54CST$$Object", "ti.catalog.c5400"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5400.TMS320C54CST.Params", "ti.catalog.c5400"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5400$TMS320C54CST$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5400.TMS320C54CST'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.isa = __mod.PARAMS.isa;\n");
            sb.append("__inst.memMap = __mod.PARAMS.memMap;\n");
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void ITMS320C54xx$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5401$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5402$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5402A$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5404$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5405$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5407$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5409$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5409A$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5410$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5410A$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5416$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5420$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5470$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5471$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320CDM270$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320CDM310$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320CDM320$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C54CST$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void ITMS320C54xx$$SIZES()
    {
    }

    void TMS320C5401$$SIZES()
    {
    }

    void TMS320C5402$$SIZES()
    {
    }

    void TMS320C5402A$$SIZES()
    {
    }

    void TMS320C5404$$SIZES()
    {
    }

    void TMS320C5405$$SIZES()
    {
    }

    void TMS320C5407$$SIZES()
    {
    }

    void TMS320C5409$$SIZES()
    {
    }

    void TMS320C5409A$$SIZES()
    {
    }

    void TMS320C5410$$SIZES()
    {
    }

    void TMS320C5410A$$SIZES()
    {
    }

    void TMS320C5416$$SIZES()
    {
    }

    void TMS320C5420$$SIZES()
    {
    }

    void TMS320C5470$$SIZES()
    {
    }

    void TMS320C5471$$SIZES()
    {
    }

    void TMS320CDM270$$SIZES()
    {
    }

    void TMS320CDM310$$SIZES()
    {
    }

    void TMS320CDM320$$SIZES()
    {
    }

    void TMS320C54CST$$SIZES()
    {
    }

    void ITMS320C54xx$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.ITMS320C54xx.Module", om.findStrict("ti.catalog.ICpuDataSheet.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.ITMS320C54xx.Instance", om.findStrict("ti.catalog.ICpuDataSheet.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCore", $$T_Str, "5400", "wh");
                po.addFld("isa", $$T_Str, "54", "wh");
                po.addFld("minProgUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
                po.addFld("minDataUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
                po.addFld("dataWordSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.ITMS320C54xx.Params", om.findStrict("ti.catalog.ICpuDataSheet$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCore", $$T_Str, "5400", "wh");
                po.addFld("isa", $$T_Str, "54", "wh");
                po.addFld("minProgUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
                po.addFld("minDataUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
                po.addFld("dataWordSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
    }

    void TMS320C5401$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5401.xs");
        om.bind("ti.catalog.c5400.TMS320C5401$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5401.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5401.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM", "base", 0x1000L, "len", 0x2000L, "space", "code")}), Global.newArray(new Object[]{"P_ROM", Global.newObject("comment", "On-Chip Program ROM", "name", "P_ROM", "base", 0xf000L, "len", 0x0f00L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xff80L, "len", 0x0080L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x1000L, "len", 0x2000L, "space", "data")}), Global.newArray(new Object[]{"D_ROM", Global.newObject("comment", "On-Chip Data ROM", "name", "D_ROM", "base", 0xf000L, "len", 0x0f00L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5401$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5401$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5401$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5401$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5401$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5401$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5401$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5401$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5401.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5401.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5401$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5401.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5401$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5401.Object", om.findStrict("ti.catalog.c5400.TMS320C5401.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C5402$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5402.xs");
        om.bind("ti.catalog.c5400.TMS320C5402$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5402.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5402.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM", "base", 0x80L, "len", 0x3f80L, "page", 0L, "space", "code")}), Global.newArray(new Object[]{"P_ROM", Global.newObject("comment", "On-Chip Program ROM", "name", "P_ROM", "base", 0xf000L, "len", 0xf00L, "page", 0L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xff80L, "len", 0x80L, "page", 0L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "page", 1L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x80L, "len", 0x3f80L, "page", 1L, "space", "data")}), Global.newArray(new Object[]{"D_ROM", Global.newObject("comment", "On-Chip Data ROM", "name", "D_ROM", "base", 0xf000L, "len", 0xf00L, "page", 1L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5402$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5402$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5402$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5402$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5402$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5402$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5402$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5402$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5402.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5402.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5402$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5402.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5402$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5402.Object", om.findStrict("ti.catalog.c5400.TMS320C5402.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C5402A$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5402A.xs");
        om.bind("ti.catalog.c5400.TMS320C5402A$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5402A.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5402A.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM", "base", 0x80L, "len", 0x3f80L, "space", "code")}), Global.newArray(new Object[]{"P_ROM", Global.newObject("comment", "On-Chip Program ROM", "name", "P_ROM", "base", 0xC000L, "len", 0x3F00L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xff80L, "len", 0x80L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x80L, "len", 0x3f80L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5402A$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5402A$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5402A$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5402A$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5402A$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5402A$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5402A$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5402A$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5402A.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5402A.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5402A$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5402A.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5402A$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5402A.Object", om.findStrict("ti.catalog.c5400.TMS320C5402A.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C5404$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5404.xs");
        om.bind("ti.catalog.c5400.TMS320C5404$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5404.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5404.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM", "base", 0x0080L, "len", 0x3F80L, "space", "code")}), Global.newArray(new Object[]{"P_ROM0", Global.newObject("comment", "On-Chip Program ROM0", "name", "P_ROM0", "base", 0x8000L, "len", 0x7F00L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xff80L, "len", 0x0080L, "space", "code")}), Global.newArray(new Object[]{"P_ROM1", Global.newObject("comment", "On-Chip Program ROM1", "name", "P_ROM1", "base", 0x18000L, "len", 0x08000L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x0080L, "len", 0x3F80L, "space", "data")}), Global.newArray(new Object[]{"D_ROM", Global.newObject("comment", "On-Chip Data ROM", "name", "D_ROM", "base", 0xC000L, "len", 0x4000L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5404$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5404$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5404$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5404$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5404$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5404$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5404$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5404$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5404.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5404.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5404$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5404.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5404$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5404.Object", om.findStrict("ti.catalog.c5400.TMS320C5404.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C5405$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5405.xs");
        om.bind("ti.catalog.c5400.TMS320C5405$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5405.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5405.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM", "base", 0x0080L, "len", 0x3F80L, "space", "code")}), Global.newArray(new Object[]{"P_ROM", Global.newObject("comment", "On-Chip Program ROM", "name", "P_ROM", "base", 0xF000L, "len", 0x0F00L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xFF80L, "len", 0x0080L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x0080L, "len", 0x3F80L, "space", "data")}), Global.newArray(new Object[]{"D_ROM", Global.newObject("comment", "On-Chip Data ROM", "name", "D_ROM", "base", 0xF000L, "len", 0x0F00L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5405$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5405$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5405$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5405$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5405$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5405$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5405$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5405$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5405.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5405.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5405$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5405.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5405$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5405.Object", om.findStrict("ti.catalog.c5400.TMS320C5405.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C5407$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5407.xs");
        om.bind("ti.catalog.c5400.TMS320C5407$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5407.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5407.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM02", Global.newObject("comment", "On-Chip Program DARAM02", "name", "P_DARAM02", "base", 0x0080L, "len", 0x5F80L, "space", "code")}), Global.newArray(new Object[]{"P_DARAM04", Global.newObject("comment", "On-Chip Program DARAM04", "name", "P_DARAM04", "base", 0x0080L, "len", 0x9F80L, "space", "code")}), Global.newArray(new Object[]{"P_ROM0", Global.newObject("comment", "On-Chip Program ROM0", "name", "P_ROM0", "base", 0x6000L, "len", 0x9F00L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xFF80L, "len", 0x0080L, "space", "code")}), Global.newArray(new Object[]{"P_ROM1", Global.newObject("comment", "On-Chip Program ROM1", "name", "P_ROM1", "base", 0x18000L, "len", 0x08000L, "space", "code")}), Global.newArray(new Object[]{"P_ROM2", Global.newObject("comment", "On-Chip Program ROM2", "name", "P_ROM2", "base", 0x28000L, "len", 0x08000L, "space", "code")}), Global.newArray(new Object[]{"P_ROM3", Global.newObject("comment", "On-Chip Program ROM3", "name", "P_ROM3", "base", 0x38000L, "len", 0x06000L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM04", Global.newObject("comment", "On-Chip Data DARAM04", "name", "D_DARAM04", "base", 0x0080L, "len", 0x9F80L, "space", "data")}), Global.newArray(new Object[]{"D_ROM", Global.newObject("comment", "On-Chip Data ROM", "name", "D_ROM", "base", 0xC000L, "len", 0x4000L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5407$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5407$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5407$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5407$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5407$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5407$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5407$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5407$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5407.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5407.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5407$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5407.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5407$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5407.Object", om.findStrict("ti.catalog.c5400.TMS320C5407.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C5409$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5409.xs");
        om.bind("ti.catalog.c5400.TMS320C5409$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5409.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5409.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM", "base", 0x0080L, "len", 0x7F80L, "space", "code")}), Global.newArray(new Object[]{"P_ROM", Global.newObject("comment", "On-Chip Program ROM", "name", "P_ROM", "base", 0xC000L, "len", 0x3F00L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xFF80L, "len", 0x0080L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x0080L, "len", 0x7F80L, "space", "data")}), Global.newArray(new Object[]{"D_ROM", Global.newObject("comment", "On-Chip Data ROM", "name", "D_ROM", "base", 0xC000L, "len", 0x3F00L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5409$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5409$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5409$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5409$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5409$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5409$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5409$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5409$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5409.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5409.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5409$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5409.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5409$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5409.Object", om.findStrict("ti.catalog.c5400.TMS320C5409.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C5409A$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5409A.xs");
        om.bind("ti.catalog.c5400.TMS320C5409A$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5409A.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5409A.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM", "base", 0x0080L, "len", 0x7F80L, "space", "code")}), Global.newArray(new Object[]{"P_ROM", Global.newObject("comment", "On-Chip Program ROM", "name", "P_ROM", "base", 0xC000L, "len", 0x3F00L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xFF80L, "len", 0x0080L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x0080L, "len", 0x7F80L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5409A$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5409A$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5409A$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5409A$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5409A$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5409A$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5409A$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5409A$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5409A.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5409A.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5409A$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5409A.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5409A$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5409A.Object", om.findStrict("ti.catalog.c5400.TMS320C5409A.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C5410$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5410.xs");
        om.bind("ti.catalog.c5400.TMS320C5410$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5410.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5410.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM", "base", 0x0080L, "len", 0x1F80L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM1", Global.newObject("comment", "On-Chip Program SARAM1", "name", "P_SARAM1", "base", 0x2000L, "len", 0x6000L, "space", "code")}), Global.newArray(new Object[]{"P_ROM", Global.newObject("comment", "On-Chip Program ROM", "name", "P_ROM", "base", 0xC000L, "len", 0x3F80L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xFF80L, "len", 0x0080L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM2", Global.newObject("comment", "On-Chip Program SARAM2", "name", "P_SARAM2", "base", 0x18000L, "len", 0x08000L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "On-Chip Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x0080L, "len", 0x1F80L, "space", "data")}), Global.newArray(new Object[]{"D_SARAM1", Global.newObject("comment", "On-Chip Data SARAM1", "name", "D_SARAM1", "base", 0x2000L, "len", 0x6000L, "space", "data")}), Global.newArray(new Object[]{"D_SARAM2", Global.newObject("comment", "On-Chip Data SARAM2", "name", "D_SARAM2", "base", 0x8000L, "len", 0x8000L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5410$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5410$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5410$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5410$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5410$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5410$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5410$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5410$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5410.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5410.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5410$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5410.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5410$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5410.Object", om.findStrict("ti.catalog.c5400.TMS320C5410.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C5410A$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5410A.xs");
        om.bind("ti.catalog.c5400.TMS320C5410A$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5410A.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5410A.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM03", Global.newObject("comment", "On-Chip Program DARAM 0-3", "name", "P_DARAM03", "base", 0x0080L, "len", 0x7F80L, "space", "code")}), Global.newArray(new Object[]{"P_ROM", Global.newObject("comment", "On-Chip ROM", "name", "P_ROM", "base", 0xC000L, "len", 0x3F00L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xff80L, "len", 0x80L, "space", "code")}), Global.newArray(new Object[]{"P_DARAM47", Global.newObject("comment", "On-Chip Program DARAM 4-7", "name", "P_DARAM47", "base", 0x18000L, "len", 0x08000L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "On-Chip Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM03", Global.newObject("comment", "On-Chip Data DARAM 0-3", "name", "D_DARAM03", "base", 0x0080L, "len", 0x7f80L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM47", Global.newObject("comment", "On-Chip Data DARAM 4-7", "name", "D_DARAM47", "base", 0x8000L, "len", 0x8000L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5410A$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5410A$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5410A$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5410A$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5410A$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5410A$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5410A$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5410A$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5410A.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5410A.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5410A$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5410A.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5410A$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5410A.Object", om.findStrict("ti.catalog.c5400.TMS320C5410A.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C5416$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5416.xs");
        om.bind("ti.catalog.c5400.TMS320C5416$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5416.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5416.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM03", Global.newObject("comment", "On-Chip Program DARAM 0-3", "name", "P_DARAM03", "base", 0x80L, "len", 0x7f80L, "page", 0L, "space", "code")}), Global.newArray(new Object[]{"P_ROM", Global.newObject("comment", "On-Chip ROM", "name", "P_ROM", "base", 0xc000L, "len", 0x3f00L, "page", 0L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xff80L, "len", 0x80L, "page", 0L, "space", "code")}), Global.newArray(new Object[]{"P_DARAM47", Global.newObject("comment", "On-Chip Program DARAM 4-7", "name", "P_DARAM47", "base", 0x18000L, "len", 0x8000L, "page", 1L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM03", Global.newObject("comment", "On-Chip Program SARAM 0-3", "name", "P_SARAM03", "base", 0x28000L, "len", 0x8000L, "page", 2L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM47", Global.newObject("comment", "On-Chip Program SARAM 4-7", "name", "P_SARAM47", "base", 0x38000L, "len", 0x8000L, "page", 3L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "On-Chip Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "page", 1L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM03", Global.newObject("comment", "On-Chip Data DARAM 0-3", "name", "D_DARAM03", "base", 0x80L, "len", 0x7f80L, "page", 1L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM47", Global.newObject("comment", "On-Chip Data DARAM 4-7", "name", "D_DARAM47", "base", 0x8000L, "len", 0x8000L, "page", 1L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5416$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5416$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5416$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5416$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5416$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5416$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5416$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5416$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5416.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5416.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5416$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5416.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5416$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5416.Object", om.findStrict("ti.catalog.c5400.TMS320C5416.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C5420$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5420.xs");
        om.bind("ti.catalog.c5400.TMS320C5420$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5420.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5420.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM0", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM0", "base", 0x0080L, "len", 0x3F80L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM1", Global.newObject("comment", "On-Chip Program SARAM1", "name", "P_SARAM1", "base", 0x4000L, "len", 0x4000L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM2", Global.newObject("comment", "On-Chip Program SARAM2", "name", "P_SARAM2", "base", 0x8000L, "len", 0x7F80L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xFF80L, "len", 0x0080L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM3", Global.newObject("comment", "On-Chip Program SARAM3", "name", "P_SARAM3", "base", 0x18000L, "len", 0x08000L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "On-Chip Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM0", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM0", "base", 0x0080L, "len", 0x3F80L, "space", "data")}), Global.newArray(new Object[]{"D_SARAM1", Global.newObject("comment", "On-Chip Data SARAM1", "name", "D_SARAM1", "base", 0x4000L, "len", 0x4000L, "space", "data")}), Global.newArray(new Object[]{"D_SARAM2", Global.newObject("comment", "On-Chip Data SARAM2", "name", "D_SARAM2", "base", 0x8000L, "len", 0x8000L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5420$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5420$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5420$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5420$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5420$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5420$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5420$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5420$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5420.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5420.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5420$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5420.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5420$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5420.Object", om.findStrict("ti.catalog.c5400.TMS320C5420.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C5470$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5470.xs");
        om.bind("ti.catalog.c5400.TMS320C5470$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5470.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5470.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM", "base", 0x0080L, "len", 0x1F80L, "space", "code")}), Global.newArray(new Object[]{"P_APIDARAM", Global.newObject("comment", "On-Chip DARAM API Accessible", "name", "P_APIDARAM", "base", 0x2000L, "len", 0x2000L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM0", Global.newObject("comment", "On-Chip Program SARAM0", "name", "P_SARAM0", "base", 0x4000L, "len", 0x2000L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM1", Global.newObject("comment", "On-Chip Program SARAM1", "name", "P_SARAM1", "base", 0x6000L, "len", 0x2000L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM2", Global.newObject("comment", "On-Chip Program SARAM2", "name", "P_SARAM2", "base", 0x8000L, "len", 0x8000L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "On-Chip Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x0080L, "len", 0x1F80L, "space", "data")}), Global.newArray(new Object[]{"D_APIDARAM", Global.newObject("comment", "On-Chip DARAM API Accessible", "name", "D_APIDARAM", "base", 0x2000L, "len", 0x2000L, "space", "data")}), Global.newArray(new Object[]{"D_SARAM0", Global.newObject("comment", "On-Chip Data SARAM0", "name", "D_SARAM0", "base", 0x4000L, "len", 0x2000L, "space", "data")}), Global.newArray(new Object[]{"D_SARAM1", Global.newObject("comment", "On-Chip Data SARAM1", "name", "D_SARAM1", "base", 0x6000L, "len", 0x2000L, "space", "data")}), Global.newArray(new Object[]{"D_SARAM2", Global.newObject("comment", "On-Chip Data SARAM2", "name", "D_SARAM2", "base", 0xC000L, "len", 0x4000L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5470$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5470$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5470$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5470$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5470$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5470$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5470$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5470$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5470.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5470.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5470$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5470.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5470$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5470.Object", om.findStrict("ti.catalog.c5400.TMS320C5470.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C5471$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C5471.xs");
        om.bind("ti.catalog.c5400.TMS320C5471$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5471.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5471.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM", "base", 0x0080L, "len", 0x1F80L, "space", "code")}), Global.newArray(new Object[]{"P_APIDARAM", Global.newObject("comment", "On-Chip DARAM API Accessible", "name", "P_APIDARAM", "base", 0x2000L, "len", 0x2000L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM0", Global.newObject("comment", "On-Chip Program SARAM0", "name", "P_SARAM0", "base", 0x4000L, "len", 0x2000L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM1", Global.newObject("comment", "On-Chip Program SARAM1", "name", "P_SARAM1", "base", 0x6000L, "len", 0x2000L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM2", Global.newObject("comment", "On-Chip Program SARAM2", "name", "P_SARAM2", "base", 0x8000L, "len", 0x8000L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "On-Chip Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x1AL, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x0080L, "len", 0x1F80L, "space", "data")}), Global.newArray(new Object[]{"D_APIDARAM", Global.newObject("comment", "On-Chip DARAM API Accessible", "name", "D_APIDARAM", "base", 0x2000L, "len", 0x2000L, "space", "data")}), Global.newArray(new Object[]{"D_SARAM0", Global.newObject("comment", "On-Chip Data SARAM0", "name", "D_SARAM0", "base", 0x4000L, "len", 0x2000L, "space", "data")}), Global.newArray(new Object[]{"D_SARAM1", Global.newObject("comment", "On-Chip Data SARAM1", "name", "D_SARAM1", "base", 0x6000L, "len", 0x2000L, "space", "data")}), Global.newArray(new Object[]{"D_SARAM2", Global.newObject("comment", "On-Chip Data SARAM2", "name", "D_SARAM2", "base", 0xC000L, "len", 0x3800L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5471$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5471$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C5471$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C5471$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5471$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5471$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5471$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C5471$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5471.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5471.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5471$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5471.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5471$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C5471.Object", om.findStrict("ti.catalog.c5400.TMS320C5471.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320CDM270$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320CDM270.xs");
        om.bind("ti.catalog.c5400.TMS320CDM270$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM270.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320CDM270.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM", "base", 0x0080L, "len", 0x7F80L, "space", "code")}), Global.newArray(new Object[]{"P_ROM1", Global.newObject("comment", "On-Chip Program ROM not controlled by MP/MC", "name", "P_ROM1", "base", 0x8000L, "len", 0x4000L, "space", "code")}), Global.newArray(new Object[]{"P_ROM2", Global.newObject("comment", "On-Chip Program ROM controlled by MP/MC", "name", "P_ROM2", "base", 0xC000L, "len", 0x3F00L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xFF00L, "len", 0x0100L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM", Global.newObject("comment", "On-Chip SARAM", "name", "P_SARAM", "base", 0x1C000L, "len", 0x04000L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x0080L, "len", 0x7F80L, "space", "data")}), Global.newArray(new Object[]{"D_SARAM", Global.newObject("comment", "On-Chip SARAM", "name", "D_SARAM", "base", 0x8000L, "len", 0x4000L, "space", "data")}), Global.newArray(new Object[]{"D_ROM", Global.newObject("comment", "On-Chip Data ROM", "name", "D_ROM", "base", 0xC000L, "len", 0x4000L, "space", "data")}), Global.newArray(new Object[]{"IMAGE_BUFFER", Global.newObject("comment", "Co-processor Shared Memory (Image Buffer)", "name", "IMAGE_BUFFER", "base", 0x0000C000L, "len", 0x00004000L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320CDM270$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320CDM270$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320CDM270$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320CDM270$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320CDM270$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320CDM270$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320CDM270$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320CDM270$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM270.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320CDM270.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM270$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320CDM270.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM270$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320CDM270.Object", om.findStrict("ti.catalog.c5400.TMS320CDM270.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320CDM310$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320CDM310.xs");
        om.bind("ti.catalog.c5400.TMS320CDM310$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM310.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320CDM310.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM", "base", 0x0080L, "len", 0x7F80L, "space", "code")}), Global.newArray(new Object[]{"P_ROM", Global.newObject("comment", "On-Chip Program ROM", "name", "P_ROM", "base", 0xC000L, "len", 0x4000L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0x7F80L, "len", 0x0080L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM", Global.newObject("comment", "On-Chip SARAM", "name", "P_SARAM", "base", 0x18000L, "len", 0x08000L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x0080L, "len", 0x7F00L, "space", "data")}), Global.newArray(new Object[]{"D_SARAM", Global.newObject("comment", "On-Chip SARAM", "name", "D_SARAM", "base", 0x8000L, "len", 0x4000L, "space", "data")}), Global.newArray(new Object[]{"IMAGE_BUFFER_AC", Global.newObject("comment", "Co-processor Shared Memory (Image Buffer) A/C", "name", "IMAGE_BUFFER_AC", "base", 0x00008000L, "len", 0x00002000L, "space", "data")}), Global.newArray(new Object[]{"D_ROM", Global.newObject("comment", "On-Chip Data ROM", "name", "D_ROM", "base", 0xC000L, "len", 0x4000L, "space", "data")}), Global.newArray(new Object[]{"IMAGE_BUFFER_B", Global.newObject("comment", "Co-processor Shared Memory (Image Buffer) B", "name", "IMAGE_BUFFER", "base", 0x0000A000L, "len", 0x00002000L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320CDM310$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320CDM310$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320CDM310$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320CDM310$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320CDM310$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320CDM310$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320CDM310$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320CDM310$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM310.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320CDM310.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM310$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320CDM310.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM310$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320CDM310.Object", om.findStrict("ti.catalog.c5400.TMS320CDM310.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320CDM320$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320CDM320.xs");
        om.bind("ti.catalog.c5400.TMS320CDM320$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM320.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320CDM320.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM", Global.newObject("comment", "On-Chip Program DARAM", "name", "P_DARAM", "base", 0x0080L, "len", 0x7F80L, "space", "code")}), Global.newArray(new Object[]{"P_ROM", Global.newObject("comment", "On-Chip Program ROM", "name", "P_ROM", "base", 0x8000L, "len", 0x7F00L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xFF00L, "len", 0x0100L, "space", "code")}), Global.newArray(new Object[]{"P_SARAM", Global.newObject("comment", "On-Chip SARAM", "name", "P_SARAM", "base", 0x1C000L, "len", 0x04000L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x0080L, "len", 0x7F80L, "space", "data")}), Global.newArray(new Object[]{"D_SARAM", Global.newObject("comment", "On-Chip SARAM", "name", "D_SARAM", "base", 0x8000L, "len", 0x4000L, "space", "data")}), Global.newArray(new Object[]{"D_ROM", Global.newObject("comment", "On-Chip Data ROM", "name", "D_ROM", "base", 0xC000L, "len", 0x4000L, "space", "data")}), Global.newArray(new Object[]{"IMAGE_BUFFER", Global.newObject("comment", "Co-processor Shared Memory (Image Buffer)", "name", "IMAGE_BUFFER", "base", 0x0000C000L, "len", 0x00004000L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320CDM320$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320CDM320$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320CDM320$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320CDM320$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320CDM320$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320CDM320$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320CDM320$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320CDM320$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM320.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320CDM320.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM320$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320CDM320.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM320$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320CDM320.Object", om.findStrict("ti.catalog.c5400.TMS320CDM320.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void TMS320C54CST$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/TMS320C54CST.xs");
        om.bind("ti.catalog.c5400.TMS320C54CST$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C54CST.Module", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C54CST.Module", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memBlock", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), Global.newArray(new Object[]{Global.newArray(new Object[]{"P_DARAM0", Global.newObject("comment", "3 blocks of 8K words on-chip DARAM", "name", "P_DARAM", "base", 0x0080L, "len", 0x5F80L, "space", "code")}), Global.newArray(new Object[]{"P_DARAM1", Global.newObject("comment", "2 blocks of 8K words on-chip DARAM", "name", "P_DARAM", "base", 0x6000L, "len", 0x4000L, "space", "code")}), Global.newArray(new Object[]{"P_ROM", Global.newObject("comment", "On-Chip Program ROM", "name", "P_ROM", "base", 0x6000L, "len", 0x9F80L, "space", "code")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupts", "name", "VECT", "base", 0xFF80L, "len", 0x0080L, "space", "code")}), Global.newArray(new Object[]{"D_SPRAM", Global.newObject("comment", "Scratch-Pad RAM", "name", "D_SPRAM", "base", 0x60L, "len", 0x20L, "space", "data")}), Global.newArray(new Object[]{"D_DARAM", Global.newObject("comment", "On-Chip Data DARAM", "name", "D_DARAM", "base", 0x0080L, "len", 0x9F80L, "space", "data")}), Global.newArray(new Object[]{"D_ROM", Global.newObject("comment", "On-Chip Data ROM", "name", "D_ROM", "base", 0xC000L, "len", 0x4000L, "space", "data")})}), "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C54CST$$create", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C54CST$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5400.TMS320C54CST$$construct", "ti.catalog.c5400"), Global.get("ti$catalog$c5400$TMS320C54CST$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C54CST$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C54CST$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C54CST$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5400.TMS320C54CST$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C54CST.Instance", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C54CST.Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C54CST$$Params", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C54CST.Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx$$Params", "ti.catalog.c5400"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5400")), $$DEFAULT, "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C54CST$$Object", "ti.catalog.c5400");
        po.init("ti.catalog.c5400.TMS320C54CST.Object", om.findStrict("ti.catalog.c5400.TMS320C54CST.Instance", "ti.catalog.c5400"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5400"), fxn);
    }

    void ITMS320C54xx$$ROV()
    {
    }

    void TMS320C5401$$ROV()
    {
    }

    void TMS320C5402$$ROV()
    {
    }

    void TMS320C5402A$$ROV()
    {
    }

    void TMS320C5404$$ROV()
    {
    }

    void TMS320C5405$$ROV()
    {
    }

    void TMS320C5407$$ROV()
    {
    }

    void TMS320C5409$$ROV()
    {
    }

    void TMS320C5409A$$ROV()
    {
    }

    void TMS320C5410$$ROV()
    {
    }

    void TMS320C5410A$$ROV()
    {
    }

    void TMS320C5416$$ROV()
    {
    }

    void TMS320C5420$$ROV()
    {
    }

    void TMS320C5470$$ROV()
    {
    }

    void TMS320C5471$$ROV()
    {
    }

    void TMS320CDM270$$ROV()
    {
    }

    void TMS320CDM310$$ROV()
    {
    }

    void TMS320CDM320$$ROV()
    {
    }

    void TMS320C54CST$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.catalog.c5400.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.catalog.c5400"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5400/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.catalog.c5400"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.catalog.c5400"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.catalog.c5400", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.catalog.c5400");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.catalog.c5400.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.platform", Global.newArray()));
        imports.add(Global.newArray("ti.catalog", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.catalog.c5400'];\n");
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

    void ITMS320C54xx$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.ITMS320C54xx", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.ITMS320C54xx.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.ITMS320C54xx", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.ITMS320C54xx.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.ITMS320C54xx.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ITMS320C54xx", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ITMS320C54xx");
        vo.seal(null);
    }

    void TMS320C5401$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5401", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5401.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5401", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5401$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5401.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5401.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5401.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5401$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5401.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5401", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5401");
    }

    void TMS320C5402$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5402", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5402.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5402", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5402$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5402.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5402.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5402.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5402$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5402.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5402", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5402");
    }

    void TMS320C5402A$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5402A", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5402A.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5402A", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5402A$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5402A.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5402A.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5402A.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5402A$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5402A.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5402A", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5402A");
    }

    void TMS320C5404$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5404", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5404.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5404", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5404$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5404.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5404.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5404.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5404$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5404.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5404", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5404");
    }

    void TMS320C5405$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5405", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5405.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5405", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5405$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5405.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5405.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5405.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5405$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5405.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5405", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5405");
    }

    void TMS320C5407$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5407", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5407.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5407", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5407$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5407.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5407.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5407.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5407$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5407.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5407", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5407");
    }

    void TMS320C5409$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5409", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5409.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5409", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5409$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5409.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5409.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5409.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5409$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5409.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5409", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5409");
    }

    void TMS320C5409A$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5409A", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5409A.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5409A", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5409A$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5409A.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5409A.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5409A.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5409A$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5409A.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5409A", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5409A");
    }

    void TMS320C5410$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5410", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5410.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5410", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5410$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5410.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5410.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5410.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5410$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5410.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5410", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5410");
    }

    void TMS320C5410A$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5410A", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5410A.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5410A", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5410A$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5410A.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5410A.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5410A.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5410A$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5410A.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5410A", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5410A");
    }

    void TMS320C5416$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5416", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5416.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5416", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5416$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5416.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5416.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5416.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5416$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5416.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5416", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5416");
    }

    void TMS320C5420$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5420", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5420.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5420", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5420$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5420.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5420.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5420.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5420$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5420.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5420", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5420");
    }

    void TMS320C5470$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5470", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5470.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5470", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5470$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5470.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5470.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5470.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5470$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5470.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5470", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5470");
    }

    void TMS320C5471$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C5471", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C5471.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C5471", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C5471$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C5471.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C5471.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C5471.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C5471$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C5471.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C5471", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5471");
    }

    void TMS320CDM270$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM270", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM270.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320CDM270", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320CDM270$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320CDM270.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320CDM270.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320CDM270.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320CDM270$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320CDM270.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320CDM270", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320CDM270");
    }

    void TMS320CDM310$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM310", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM310.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320CDM310", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320CDM310$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320CDM310.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320CDM310.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320CDM310.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320CDM310$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320CDM310.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320CDM310", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320CDM310");
    }

    void TMS320CDM320$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM320", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320CDM320.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320CDM320", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320CDM320$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320CDM320.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320CDM320.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320CDM320.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320CDM320$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320CDM320.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320CDM320", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320CDM320");
    }

    void TMS320C54CST$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5400.TMS320C54CST", "ti.catalog.c5400");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5400.TMS320C54CST.Module", "ti.catalog.c5400");
        vo.init2(po, "ti.catalog.c5400.TMS320C54CST", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5400.TMS320C54CST$$capsule", "ti.catalog.c5400"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5400.TMS320C54CST.Instance", "ti.catalog.c5400"));
        vo.bind("Params", om.findStrict("ti.catalog.c5400.TMS320C54CST.Params", "ti.catalog.c5400"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5400.TMS320C54CST.Params", "ti.catalog.c5400")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5400", "ti.catalog.c5400"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5400")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5400.TMS320C54CST$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5400.TMS320C54CST.Object", "ti.catalog.c5400"));
        pkgV.bind("TMS320C54CST", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C54CST");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5401", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5402", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5402A", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5404", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5405", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5407", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5409", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5409A", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5410", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5410A", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5416", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5420", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5470", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C5471", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320CDM270", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320CDM310", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320CDM320", "ti.catalog.c5400"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5400.TMS320C54CST", "ti.catalog.c5400"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.catalog.c5400.ITMS320C54xx")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5401")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5402")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5402A")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5404")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5405")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5407")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5409")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5409A")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5410")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5410A")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5416")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5420")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5470")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C5471")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320CDM270")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320CDM310")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320CDM320")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5400.TMS320C54CST")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.catalog.c5400")).add(pkgV);
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
        ITMS320C54xx$$OBJECTS();
        TMS320C5401$$OBJECTS();
        TMS320C5402$$OBJECTS();
        TMS320C5402A$$OBJECTS();
        TMS320C5404$$OBJECTS();
        TMS320C5405$$OBJECTS();
        TMS320C5407$$OBJECTS();
        TMS320C5409$$OBJECTS();
        TMS320C5409A$$OBJECTS();
        TMS320C5410$$OBJECTS();
        TMS320C5410A$$OBJECTS();
        TMS320C5416$$OBJECTS();
        TMS320C5420$$OBJECTS();
        TMS320C5470$$OBJECTS();
        TMS320C5471$$OBJECTS();
        TMS320CDM270$$OBJECTS();
        TMS320CDM310$$OBJECTS();
        TMS320CDM320$$OBJECTS();
        TMS320C54CST$$OBJECTS();
        ITMS320C54xx$$CONSTS();
        TMS320C5401$$CONSTS();
        TMS320C5402$$CONSTS();
        TMS320C5402A$$CONSTS();
        TMS320C5404$$CONSTS();
        TMS320C5405$$CONSTS();
        TMS320C5407$$CONSTS();
        TMS320C5409$$CONSTS();
        TMS320C5409A$$CONSTS();
        TMS320C5410$$CONSTS();
        TMS320C5410A$$CONSTS();
        TMS320C5416$$CONSTS();
        TMS320C5420$$CONSTS();
        TMS320C5470$$CONSTS();
        TMS320C5471$$CONSTS();
        TMS320CDM270$$CONSTS();
        TMS320CDM310$$CONSTS();
        TMS320CDM320$$CONSTS();
        TMS320C54CST$$CONSTS();
        ITMS320C54xx$$CREATES();
        TMS320C5401$$CREATES();
        TMS320C5402$$CREATES();
        TMS320C5402A$$CREATES();
        TMS320C5404$$CREATES();
        TMS320C5405$$CREATES();
        TMS320C5407$$CREATES();
        TMS320C5409$$CREATES();
        TMS320C5409A$$CREATES();
        TMS320C5410$$CREATES();
        TMS320C5410A$$CREATES();
        TMS320C5416$$CREATES();
        TMS320C5420$$CREATES();
        TMS320C5470$$CREATES();
        TMS320C5471$$CREATES();
        TMS320CDM270$$CREATES();
        TMS320CDM310$$CREATES();
        TMS320CDM320$$CREATES();
        TMS320C54CST$$CREATES();
        ITMS320C54xx$$FUNCTIONS();
        TMS320C5401$$FUNCTIONS();
        TMS320C5402$$FUNCTIONS();
        TMS320C5402A$$FUNCTIONS();
        TMS320C5404$$FUNCTIONS();
        TMS320C5405$$FUNCTIONS();
        TMS320C5407$$FUNCTIONS();
        TMS320C5409$$FUNCTIONS();
        TMS320C5409A$$FUNCTIONS();
        TMS320C5410$$FUNCTIONS();
        TMS320C5410A$$FUNCTIONS();
        TMS320C5416$$FUNCTIONS();
        TMS320C5420$$FUNCTIONS();
        TMS320C5470$$FUNCTIONS();
        TMS320C5471$$FUNCTIONS();
        TMS320CDM270$$FUNCTIONS();
        TMS320CDM310$$FUNCTIONS();
        TMS320CDM320$$FUNCTIONS();
        TMS320C54CST$$FUNCTIONS();
        ITMS320C54xx$$SIZES();
        TMS320C5401$$SIZES();
        TMS320C5402$$SIZES();
        TMS320C5402A$$SIZES();
        TMS320C5404$$SIZES();
        TMS320C5405$$SIZES();
        TMS320C5407$$SIZES();
        TMS320C5409$$SIZES();
        TMS320C5409A$$SIZES();
        TMS320C5410$$SIZES();
        TMS320C5410A$$SIZES();
        TMS320C5416$$SIZES();
        TMS320C5420$$SIZES();
        TMS320C5470$$SIZES();
        TMS320C5471$$SIZES();
        TMS320CDM270$$SIZES();
        TMS320CDM310$$SIZES();
        TMS320CDM320$$SIZES();
        TMS320C54CST$$SIZES();
        ITMS320C54xx$$TYPES();
        TMS320C5401$$TYPES();
        TMS320C5402$$TYPES();
        TMS320C5402A$$TYPES();
        TMS320C5404$$TYPES();
        TMS320C5405$$TYPES();
        TMS320C5407$$TYPES();
        TMS320C5409$$TYPES();
        TMS320C5409A$$TYPES();
        TMS320C5410$$TYPES();
        TMS320C5410A$$TYPES();
        TMS320C5416$$TYPES();
        TMS320C5420$$TYPES();
        TMS320C5470$$TYPES();
        TMS320C5471$$TYPES();
        TMS320CDM270$$TYPES();
        TMS320CDM310$$TYPES();
        TMS320CDM320$$TYPES();
        TMS320C54CST$$TYPES();
        if (isROV) {
            ITMS320C54xx$$ROV();
            TMS320C5401$$ROV();
            TMS320C5402$$ROV();
            TMS320C5402A$$ROV();
            TMS320C5404$$ROV();
            TMS320C5405$$ROV();
            TMS320C5407$$ROV();
            TMS320C5409$$ROV();
            TMS320C5409A$$ROV();
            TMS320C5410$$ROV();
            TMS320C5410A$$ROV();
            TMS320C5416$$ROV();
            TMS320C5420$$ROV();
            TMS320C5470$$ROV();
            TMS320C5471$$ROV();
            TMS320CDM270$$ROV();
            TMS320CDM310$$ROV();
            TMS320CDM320$$ROV();
            TMS320C54CST$$ROV();
        }//isROV
        $$SINGLETONS();
        ITMS320C54xx$$SINGLETONS();
        TMS320C5401$$SINGLETONS();
        TMS320C5402$$SINGLETONS();
        TMS320C5402A$$SINGLETONS();
        TMS320C5404$$SINGLETONS();
        TMS320C5405$$SINGLETONS();
        TMS320C5407$$SINGLETONS();
        TMS320C5409$$SINGLETONS();
        TMS320C5409A$$SINGLETONS();
        TMS320C5410$$SINGLETONS();
        TMS320C5410A$$SINGLETONS();
        TMS320C5416$$SINGLETONS();
        TMS320C5420$$SINGLETONS();
        TMS320C5470$$SINGLETONS();
        TMS320C5471$$SINGLETONS();
        TMS320CDM270$$SINGLETONS();
        TMS320CDM310$$SINGLETONS();
        TMS320CDM320$$SINGLETONS();
        TMS320C54CST$$SINGLETONS();
        $$INITIALIZATION();
    }
}
