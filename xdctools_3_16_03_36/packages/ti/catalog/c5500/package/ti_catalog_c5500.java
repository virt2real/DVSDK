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

public class ti_catalog_c5500
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
        pkgP = (Proto.Obj)om.bind("ti.catalog.c5500.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.catalog.c5500", new Value.Obj("ti.catalog.c5500", pkgP));
    }

    void ITMS320C55xx$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.ITMS320C55xx.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.ITMS320C55xx", new Value.Obj("ti.catalog.c5500.ITMS320C55xx", po));
        pkgV.bind("ITMS320C55xx", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.ITMS320C55xx.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.ITMS320C55xx$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.ITMS320C55xx.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.ITMS320C55xx$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.ITMS320C55xx.Params", new Proto.Str(po, true));
    }

    void TMS320C5501$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5501.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5501", new Value.Obj("ti.catalog.c5500.TMS320C5501", po));
        pkgV.bind("TMS320C5501", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5501.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5501$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5501.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5501$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5501.Params", new Proto.Str(po, true));
    }

    void TMS320C5502$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5502.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5502", new Value.Obj("ti.catalog.c5500.TMS320C5502", po));
        pkgV.bind("TMS320C5502", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5502.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5502$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5502.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5502$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5502.Params", new Proto.Str(po, true));
    }

    void TMS320C5503$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5503.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5503", new Value.Obj("ti.catalog.c5500.TMS320C5503", po));
        pkgV.bind("TMS320C5503", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5503.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5503$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5503.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5503$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5503.Params", new Proto.Str(po, true));
    }

    void TMS320C5504$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5504.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5504", new Value.Obj("ti.catalog.c5500.TMS320C5504", po));
        pkgV.bind("TMS320C5504", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5504.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5504$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5504.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5504$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5504.Params", new Proto.Str(po, true));
    }

    void TMS320C5505$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5505.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5505", new Value.Obj("ti.catalog.c5500.TMS320C5505", po));
        pkgV.bind("TMS320C5505", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5505.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5505$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5505.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5505$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5505.Params", new Proto.Str(po, true));
    }

    void TMS320C5507$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5507.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5507", new Value.Obj("ti.catalog.c5500.TMS320C5507", po));
        pkgV.bind("TMS320C5507", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5507.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5507$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5507.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5507$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5507.Params", new Proto.Str(po, true));
    }

    void TMS320C5509$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5509.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5509", new Value.Obj("ti.catalog.c5500.TMS320C5509", po));
        pkgV.bind("TMS320C5509", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5509.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5509$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5509.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5509$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5509.Params", new Proto.Str(po, true));
    }

    void TMS320C5509A$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5509A.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5509A", new Value.Obj("ti.catalog.c5500.TMS320C5509A", po));
        pkgV.bind("TMS320C5509A", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5509A.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5509A$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5509A.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5509A$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5509A.Params", new Proto.Str(po, true));
    }

    void TMS320C5510$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5510.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5510", new Value.Obj("ti.catalog.c5500.TMS320C5510", po));
        pkgV.bind("TMS320C5510", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5510.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5510$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5510.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5510$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5510.Params", new Proto.Str(po, true));
    }

    void TMS320C5510A$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5510A.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5510A", new Value.Obj("ti.catalog.c5500.TMS320C5510A", po));
        pkgV.bind("TMS320C5510A", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5510A.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5510A$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5510A.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5510A$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5510A.Params", new Proto.Str(po, true));
    }

    void TMS320C5514$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5514.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5514", new Value.Obj("ti.catalog.c5500.TMS320C5514", po));
        pkgV.bind("TMS320C5514", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5514.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5514$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5514.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5514$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5514.Params", new Proto.Str(po, true));
    }

    void TMS320C5515$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5515.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5515", new Value.Obj("ti.catalog.c5500.TMS320C5515", po));
        pkgV.bind("TMS320C5515", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5515.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5515$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5515.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5515$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5515.Params", new Proto.Str(po, true));
    }

    void TMS320C5561$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5561.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5561", new Value.Obj("ti.catalog.c5500.TMS320C5561", po));
        pkgV.bind("TMS320C5561", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5561.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5561$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5561.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5561$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5561.Params", new Proto.Str(po, true));
    }

    void IOMAP$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.IOMAP.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.IOMAP", new Value.Obj("ti.catalog.c5500.IOMAP", po));
        pkgV.bind("IOMAP", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.IOMAP.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.IOMAP$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.IOMAP.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.IOMAP$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.IOMAP.Params", new Proto.Str(po, true));
    }

    void TMS320C1035$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C1035.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C1035", new Value.Obj("ti.catalog.c5500.TMS320C1035", po));
        pkgV.bind("TMS320C1035", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C1035.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C1035$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C1035.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C1035$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C1035.Params", new Proto.Str(po, true));
    }

    void TMS320C1510$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C1510.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C1510", new Value.Obj("ti.catalog.c5500.TMS320C1510", po));
        pkgV.bind("TMS320C1510", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C1510.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C1510$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C1510.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C1510$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C1510.Params", new Proto.Str(po, true));
    }

    void TMS320C1610$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C1610.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C1610", new Value.Obj("ti.catalog.c5500.TMS320C1610", po));
        pkgV.bind("TMS320C1610", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C1610.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C1610$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C1610.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C1610$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C1610.Params", new Proto.Str(po, true));
    }

    void TMS320C1710$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C1710.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C1710", new Value.Obj("ti.catalog.c5500.TMS320C1710", po));
        pkgV.bind("TMS320C1710", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C1710.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C1710$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C1710.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C1710$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C1710.Params", new Proto.Str(po, true));
    }

    void TMS320C2320$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C2320.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C2320", new Value.Obj("ti.catalog.c5500.TMS320C2320", po));
        pkgV.bind("TMS320C2320", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C2320.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C2320$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C2320.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C2320$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C2320.Params", new Proto.Str(po, true));
    }

    void TMS320C2420$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C2420.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C2420", new Value.Obj("ti.catalog.c5500.TMS320C2420", po));
        pkgV.bind("TMS320C2420", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C2420.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C2420$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C2420.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C2420$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C2420.Params", new Proto.Str(po, true));
    }

    void TMS320C5903$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5903.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5903", new Value.Obj("ti.catalog.c5500.TMS320C5903", po));
        pkgV.bind("TMS320C5903", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5903.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5903$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5903.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5903$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5903.Params", new Proto.Str(po, true));
    }

    void TMS320C5905$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5905.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5905", new Value.Obj("ti.catalog.c5500.TMS320C5905", po));
        pkgV.bind("TMS320C5905", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5905.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5905$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5905.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5905$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5905.Params", new Proto.Str(po, true));
    }

    void TMS320C5910$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5910.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5910", new Value.Obj("ti.catalog.c5500.TMS320C5910", po));
        pkgV.bind("TMS320C5910", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5910.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5910$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5910.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5910$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5910.Params", new Proto.Str(po, true));
    }

    void TMS320C5912$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5912.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5912", new Value.Obj("ti.catalog.c5500.TMS320C5912", po));
        pkgV.bind("TMS320C5912", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5912.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5912$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5912.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5912$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5912.Params", new Proto.Str(po, true));
    }

    void TMS320C5944$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5944.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5944", new Value.Obj("ti.catalog.c5500.TMS320C5944", po));
        pkgV.bind("TMS320C5944", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5944.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5944$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5944.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5944$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5944.Params", new Proto.Str(po, true));
    }

    void TMS320C5946$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5946.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5946", new Value.Obj("ti.catalog.c5500.TMS320C5946", po));
        pkgV.bind("TMS320C5946", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5946.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5946$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5946.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5946$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5946.Params", new Proto.Str(po, true));
    }

    void TMS320C5948$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5948.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320C5948", new Value.Obj("ti.catalog.c5500.TMS320C5948", po));
        pkgV.bind("TMS320C5948", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320C5948.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5948$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320C5948.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320C5948$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320C5948.Params", new Proto.Str(po, true));
    }

    void TMS320CRYUJIN$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320CRYUJIN.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320CRYUJIN", new Value.Obj("ti.catalog.c5500.TMS320CRYUJIN", po));
        pkgV.bind("TMS320CRYUJIN", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320CRYUJIN.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320CRYUJIN$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320CRYUJIN.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320CRYUJIN$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320CRYUJIN.Params", new Proto.Str(po, true));
    }

    void TMS320CDA255$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320CDA255.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320CDA255", new Value.Obj("ti.catalog.c5500.TMS320CDA255", po));
        pkgV.bind("TMS320CDA255", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320CDA255.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320CDA255$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320CDA255.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320CDA255$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320CDA255.Params", new Proto.Str(po, true));
    }

    void TMS320CDA295$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320CDA295.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320CDA295", new Value.Obj("ti.catalog.c5500.TMS320CDA295", po));
        pkgV.bind("TMS320CDA295", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320CDA295.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320CDA295$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320CDA295.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320CDA295$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320CDA295.Params", new Proto.Str(po, true));
    }

    void TMS320CDA300$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320CDA300.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TMS320CDA300", new Value.Obj("ti.catalog.c5500.TMS320CDA300", po));
        pkgV.bind("TMS320CDA300", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TMS320CDA300.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320CDA300$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TMS320CDA300.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TMS320CDA300$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TMS320CDA300.Params", new Proto.Str(po, true));
    }

    void TNETV1050$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TNETV1050.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TNETV1050", new Value.Obj("ti.catalog.c5500.TNETV1050", po));
        pkgV.bind("TNETV1050", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TNETV1050.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TNETV1050$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TNETV1050.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TNETV1050$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TNETV1050.Params", new Proto.Str(po, true));
    }

    void TNETV1055$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.c5500.TNETV1055.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.c5500.TNETV1055", new Value.Obj("ti.catalog.c5500.TNETV1055", po));
        pkgV.bind("TNETV1055", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.catalog.c5500.TNETV1055.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TNETV1055$$Object", new Proto.Obj());
        Object objP = om.bind("ti.catalog.c5500.TNETV1055.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.catalog.c5500.TNETV1055$$Params", new Proto.Obj());
        om.bind("ti.catalog.c5500.TNETV1055.Params", new Proto.Str(po, true));
    }

    void ITMS320C55xx$$CONSTS()
    {
        // interface ITMS320C55xx
    }

    void TMS320C5501$$CONSTS()
    {
        // module TMS320C5501
    }

    void TMS320C5502$$CONSTS()
    {
        // module TMS320C5502
    }

    void TMS320C5503$$CONSTS()
    {
        // module TMS320C5503
    }

    void TMS320C5504$$CONSTS()
    {
        // module TMS320C5504
    }

    void TMS320C5505$$CONSTS()
    {
        // module TMS320C5505
    }

    void TMS320C5507$$CONSTS()
    {
        // module TMS320C5507
    }

    void TMS320C5509$$CONSTS()
    {
        // module TMS320C5509
    }

    void TMS320C5509A$$CONSTS()
    {
        // module TMS320C5509A
    }

    void TMS320C5510$$CONSTS()
    {
        // module TMS320C5510
    }

    void TMS320C5510A$$CONSTS()
    {
        // module TMS320C5510A
    }

    void TMS320C5514$$CONSTS()
    {
        // module TMS320C5514
    }

    void TMS320C5515$$CONSTS()
    {
        // module TMS320C5515
    }

    void TMS320C5561$$CONSTS()
    {
        // module TMS320C5561
    }

    void IOMAP$$CONSTS()
    {
        // interface IOMAP
    }

    void TMS320C1035$$CONSTS()
    {
        // module TMS320C1035
    }

    void TMS320C1510$$CONSTS()
    {
        // module TMS320C1510
    }

    void TMS320C1610$$CONSTS()
    {
        // module TMS320C1610
    }

    void TMS320C1710$$CONSTS()
    {
        // module TMS320C1710
    }

    void TMS320C2320$$CONSTS()
    {
        // module TMS320C2320
    }

    void TMS320C2420$$CONSTS()
    {
        // module TMS320C2420
    }

    void TMS320C5903$$CONSTS()
    {
        // module TMS320C5903
    }

    void TMS320C5905$$CONSTS()
    {
        // module TMS320C5905
    }

    void TMS320C5910$$CONSTS()
    {
        // module TMS320C5910
    }

    void TMS320C5912$$CONSTS()
    {
        // module TMS320C5912
    }

    void TMS320C5944$$CONSTS()
    {
        // module TMS320C5944
    }

    void TMS320C5946$$CONSTS()
    {
        // module TMS320C5946
    }

    void TMS320C5948$$CONSTS()
    {
        // module TMS320C5948
    }

    void TMS320CRYUJIN$$CONSTS()
    {
        // module TMS320CRYUJIN
    }

    void TMS320CDA255$$CONSTS()
    {
        // module TMS320CDA255
    }

    void TMS320CDA295$$CONSTS()
    {
        // module TMS320CDA295
    }

    void TMS320CDA300$$CONSTS()
    {
        // module TMS320CDA300
    }

    void TNETV1050$$CONSTS()
    {
        // module TNETV1050
    }

    void TNETV1055$$CONSTS()
    {
        // module TNETV1055
    }

    void ITMS320C55xx$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TMS320C5501$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5501$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5501.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5501.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5501.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5501$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5501'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5501.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5501$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5501.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5501$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5501.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5501$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5501'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5502$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5502$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5502.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5502.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5502.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5502$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5502'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5502.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5502$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5502.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5502$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5502.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5502$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5502'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5503$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5503$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5503.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5503.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5503.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5503$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5503'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5503.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5503$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5503.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5503$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5503.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5503$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5503'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5504$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5504$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5504.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5504.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5504.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5504$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5504'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5504.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5504$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5504.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5504$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5504.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5504$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5504'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5505$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5505$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5505.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5505.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5505.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5505$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5505'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5505.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5505$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5505.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5505$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5505.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5505$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5505'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5507$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5507$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5507.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5507.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5507.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5507$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5507'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5507.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5507$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5507.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5507$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5507.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5507$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5507'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5509$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5509$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5509.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5509.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5509.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5509$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5509'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5509.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5509$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5509.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5509$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5509.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5509$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5509'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5509A$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5509A$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5509A.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5509A.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5509A.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5509A$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5509A'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5509A.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5509A$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5509A.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5509A$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5509A.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5509A$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5509A'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5510$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5510$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5510.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5510.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5510.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5510$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5510'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5510.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5510$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5510.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5510$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5510.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5510$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5510'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5510A$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5510A$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5510A.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5510A.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5510A.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5510A$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5510A'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5510A.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5510A$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5510A.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5510A$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5510A.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5510A$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5510A'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5514$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5514$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5514.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5514.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5514.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5514$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5514'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5514.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5514$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5514.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5514$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5514.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5514$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5514'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5515$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5515$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5515.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5515.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5515.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5515$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5515'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5515.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5515$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5515.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5515$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5515.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5515$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5515'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5561$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5561$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5561.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5561.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5561.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5561$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5561'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5561.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5561$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5561.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5561$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5561.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5561$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5561'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void IOMAP$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TMS320C1035$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C1035$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C1035.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C1035.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C1035.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C1035$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C1035'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C1035.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C1035$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C1035.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C1035$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C1035.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C1035$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C1035'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C1510$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C1510$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C1510.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C1510.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C1510.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C1510$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C1510'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C1510.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C1510$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C1510.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C1510$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C1510.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C1510$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C1510'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C1610$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C1610$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C1610.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C1610.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C1610.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C1610$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C1610'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C1610.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C1610$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C1610.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C1610$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C1610.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C1610$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C1610'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C1710$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C1710$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C1710.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C1710.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C1710.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C1710$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C1710'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C1710.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C1710$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C1710.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C1710$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C1710.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C1710$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C1710'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C2320$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C2320$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C2320.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C2320.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C2320.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C2320$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C2320'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C2320.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C2320$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C2320.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C2320$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C2320.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C2320$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C2320'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C2420$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C2420$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C2420.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C2420.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C2420.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C2420$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C2420'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C2420.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C2420$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C2420.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C2420$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C2420.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C2420$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C2420'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5903$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5903$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5903.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5903.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5903.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5903$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5903'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5903.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5903$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5903.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5903$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5903.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5903$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5903'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5905$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5905$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5905.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5905.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5905.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5905$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5905'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5905.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5905$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5905.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5905$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5905.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5905$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5905'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5910$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5910$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5910.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5910.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5910.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5910$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5910'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5910.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5910$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5910.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5910$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5910.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5910$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5910'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5912$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5912$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5912.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5912.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5912.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5912$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5912'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5912.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5912$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5912.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5912$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5912.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5912$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5912'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5944$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5944$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5944.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5944.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5944.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5944$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5944'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5944.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5944$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5944.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5944$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5944.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5944$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5944'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5946$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5946$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5946.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5946.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5946.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5946$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5946'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5946.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5946$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5946.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5946$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5946.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5946$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5946'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320C5948$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5948$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5948.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320C5948.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5948.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5948$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5948'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320C5948.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320C5948$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320C5948.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5948$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320C5948.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320C5948$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320C5948'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320CRYUJIN$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320CRYUJIN$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320CRYUJIN.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320CRYUJIN.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320CRYUJIN.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320CRYUJIN$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320CRYUJIN'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320CRYUJIN.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320CRYUJIN$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320CRYUJIN.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320CRYUJIN$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320CRYUJIN.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320CRYUJIN$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320CRYUJIN'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320CDA255$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320CDA255$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320CDA255.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320CDA255.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320CDA255.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320CDA255$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320CDA255'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320CDA255.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320CDA255$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320CDA255.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320CDA255$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320CDA255.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320CDA255$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320CDA255'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320CDA295$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320CDA295$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320CDA295.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320CDA295.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320CDA295.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320CDA295$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320CDA295'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320CDA295.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320CDA295$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320CDA295.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320CDA295$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320CDA295.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320CDA295$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320CDA295'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TMS320CDA300$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320CDA300$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320CDA300.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TMS320CDA300.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320CDA300.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320CDA300$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320CDA300'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TMS320CDA300.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TMS320CDA300$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TMS320CDA300.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TMS320CDA300$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TMS320CDA300.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TMS320CDA300$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TMS320CDA300'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TNETV1050$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TNETV1050$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TNETV1050.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TNETV1050.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TNETV1050.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TNETV1050$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TNETV1050'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TNETV1050.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TNETV1050$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TNETV1050.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TNETV1050$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TNETV1050.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TNETV1050$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TNETV1050'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void TNETV1055$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TNETV1055$$create", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TNETV1055.Module", "ti.catalog.c5500"), om.findStrict("ti.catalog.c5500.TNETV1055.Instance", "ti.catalog.c5500"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.catalog.c5500.TNETV1055.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TNETV1055$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TNETV1055'];\n");
            sb.append("var __inst = xdc.om['ti.catalog.c5500.TNETV1055.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.catalog.c5500']);\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("ti.catalog.c5500.TNETV1055$$construct", new Proto.Fxn(om.findStrict("ti.catalog.c5500.TNETV1055.Module", "ti.catalog.c5500"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.catalog.c5500.TNETV1055$$Object", "ti.catalog.c5500"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.catalog.c5500.TNETV1055.Params", "ti.catalog.c5500"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$catalog$c5500$TNETV1055$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.catalog.c5500.TNETV1055'];\n");
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
            sb.append("for (__p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void ITMS320C55xx$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5501$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5502$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5503$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5504$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5505$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5507$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5509$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5509A$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5510$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5510A$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5514$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5515$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5561$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IOMAP$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C1035$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C1510$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C1610$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C1710$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C2320$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C2420$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5903$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5905$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5910$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5912$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5944$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5946$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320C5948$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320CRYUJIN$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320CDA255$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320CDA295$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TMS320CDA300$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TNETV1050$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TNETV1055$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void ITMS320C55xx$$SIZES()
    {
    }

    void TMS320C5501$$SIZES()
    {
    }

    void TMS320C5502$$SIZES()
    {
    }

    void TMS320C5503$$SIZES()
    {
    }

    void TMS320C5504$$SIZES()
    {
    }

    void TMS320C5505$$SIZES()
    {
    }

    void TMS320C5507$$SIZES()
    {
    }

    void TMS320C5509$$SIZES()
    {
    }

    void TMS320C5509A$$SIZES()
    {
    }

    void TMS320C5510$$SIZES()
    {
    }

    void TMS320C5510A$$SIZES()
    {
    }

    void TMS320C5514$$SIZES()
    {
    }

    void TMS320C5515$$SIZES()
    {
    }

    void TMS320C5561$$SIZES()
    {
    }

    void IOMAP$$SIZES()
    {
    }

    void TMS320C1035$$SIZES()
    {
    }

    void TMS320C1510$$SIZES()
    {
    }

    void TMS320C1610$$SIZES()
    {
    }

    void TMS320C1710$$SIZES()
    {
    }

    void TMS320C2320$$SIZES()
    {
    }

    void TMS320C2420$$SIZES()
    {
    }

    void TMS320C5903$$SIZES()
    {
    }

    void TMS320C5905$$SIZES()
    {
    }

    void TMS320C5910$$SIZES()
    {
    }

    void TMS320C5912$$SIZES()
    {
    }

    void TMS320C5944$$SIZES()
    {
    }

    void TMS320C5946$$SIZES()
    {
    }

    void TMS320C5948$$SIZES()
    {
    }

    void TMS320CRYUJIN$$SIZES()
    {
    }

    void TMS320CDA255$$SIZES()
    {
    }

    void TMS320CDA295$$SIZES()
    {
    }

    void TMS320CDA300$$SIZES()
    {
    }

    void TNETV1050$$SIZES()
    {
    }

    void TNETV1055$$SIZES()
    {
    }

    void ITMS320C55xx$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5500/ITMS320C55xx.xs");
        om.bind("ti.catalog.c5500.ITMS320C55xx$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.ITMS320C55xx.Module", om.findStrict("ti.catalog.ICpuDataSheet.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5500.ITMS320C55xx$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5500.ITMS320C55xx$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5500.ITMS320C55xx$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5500.ITMS320C55xx$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.ITMS320C55xx.Instance", om.findStrict("ti.catalog.ICpuDataSheet.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCore", $$T_Str, "5500", "wh");
                po.addFld("isa", $$T_Str, "55", "wh");
                po.addFld("minProgUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
                po.addFld("minDataUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
                po.addFld("dataWordSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.ITMS320C55xx.Params", om.findStrict("ti.catalog.ICpuDataSheet$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCore", $$T_Str, "5500", "wh");
                po.addFld("isa", $$T_Str, "55", "wh");
                po.addFld("minProgUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
                po.addFld("minDataUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
                po.addFld("dataWordSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
    }

    void TMS320C5501$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5501.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5501.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5501$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5501$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5501$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5501$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5501.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5501.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x008000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "32K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff8000L, "len", 0x008000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5501$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5501.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x008000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "32K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff8000L, "len", 0x008000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5501$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5501.Object", om.findStrict("ti.catalog.c5500.TMS320C5501.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5502$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5502.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5502.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5502$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5502$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5502$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5502$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5502.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5502.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "32K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff8000L, "len", 0x008000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5502$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5502.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "32K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff8000L, "len", 0x008000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5502$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5502.Object", om.findStrict("ti.catalog.c5500.TMS320C5502.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5503$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5503.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5503.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5503$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5503$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5503$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5503$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5503.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5503.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5503$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5503.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5503$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5503.Object", om.findStrict("ti.catalog.c5500.TMS320C5503.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5504$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5504.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5504.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5504$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5504$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5504$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5504$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5504.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5504.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"MMR", Global.newObject("comment", "Memory Mapped Registers", "name", "MMR", "base", 0x000000L, "len", 0x0000c0L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x0000c0L, "len", 0x00ff40L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "24 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x030000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "128K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xfe0000L, "len", 0x020000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5504$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5504.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"MMR", Global.newObject("comment", "Memory Mapped Registers", "name", "MMR", "base", 0x000000L, "len", 0x0000c0L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x0000c0L, "len", 0x00ff40L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "24 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x030000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "128K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xfe0000L, "len", 0x020000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5504$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5504.Object", om.findStrict("ti.catalog.c5500.TMS320C5504.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5505$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5505.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5505.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5505$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5505$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5505$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5505$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5505.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5505.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"MMR", Global.newObject("comment", "Memory Mapped Registers", "name", "MMR", "base", 0x000000L, "len", 0x0000c0L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x0000c0L, "len", 0x00ff40L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "32 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x040000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "128K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xfe0000L, "len", 0x020000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5505$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5505.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"MMR", Global.newObject("comment", "Memory Mapped Registers", "name", "MMR", "base", 0x000000L, "len", 0x0000c0L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x0000c0L, "len", 0x00ff40L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "32 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x040000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "128K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xfe0000L, "len", 0x020000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5505$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5505.Object", om.findStrict("ti.catalog.c5500.TMS320C5505.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5507$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5507.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5507.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5507$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5507$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5507$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5507$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5507.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5507.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "SARAM", "base", 0x10000L, "len", 0x10000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5507$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5507.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "SARAM", "base", 0x10000L, "len", 0x10000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5507$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5507.Object", om.findStrict("ti.catalog.c5500.TMS320C5507.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5509$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5509.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5509.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5509$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5509$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5509$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5509$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5509.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5509.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "24 blocks of 8K bytes", "name", "SARAM", "base", 0x10000L, "len", 0x30000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5509$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5509.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "24 blocks of 8K bytes", "name", "SARAM", "base", 0x10000L, "len", 0x30000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5509$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5509.Object", om.findStrict("ti.catalog.c5500.TMS320C5509.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5509A$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5509A.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5509A.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5509A$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5509A$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5509A$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5509A$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5509A.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5509A.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "24 blocks of 8K bytes", "name", "SARAM", "base", 0x10000L, "len", 0x30000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5509A$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5509A.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "24 blocks of 8K bytes", "name", "SARAM", "base", 0x10000L, "len", 0x30000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5509A$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5509A.Object", om.findStrict("ti.catalog.c5500.TMS320C5509A.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5510$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5510.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5510.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5510$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5510$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5510$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5510$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5510.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5510.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes of on-chip Dual-Access RAM", "name", "DARAM", "base", 0x0000c0L, "len", 0x00ff40L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "32 blocks of 8K bytes of on-chip Single-Access RAM", "name", "SARAM", "base", 0x10000L, "len", 0x40000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "32K bytes of on-chip ROM", "name", "ROM", "base", 0xff8000L, "len", 0x008000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5510$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5510.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes of on-chip Dual-Access RAM", "name", "DARAM", "base", 0x0000c0L, "len", 0x00ff40L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "32 blocks of 8K bytes of on-chip Single-Access RAM", "name", "SARAM", "base", 0x10000L, "len", 0x40000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "32K bytes of on-chip ROM", "name", "ROM", "base", 0xff8000L, "len", 0x008000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5510$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5510.Object", om.findStrict("ti.catalog.c5500.TMS320C5510.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5510A$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5510A.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5510A.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5510A$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5510A$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5510A$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5510A$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5510A.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5510A.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes of on-chip Dual-Access RAM", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "32 blocks of 8K bytes of on-chip Single-Access RAM", "name", "SARAM", "base", 0x10000L, "len", 0x40000L, "space", "code/data", "access", "RWX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5510A$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5510A.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes of on-chip Dual-Access RAM", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "32 blocks of 8K bytes of on-chip Single-Access RAM", "name", "SARAM", "base", 0x10000L, "len", 0x40000L, "space", "code/data", "access", "RWX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5510A$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5510A.Object", om.findStrict("ti.catalog.c5500.TMS320C5510A.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5514$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5514.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5514.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5514$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5514$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5514$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5514$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5514.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5514.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"MMR", Global.newObject("comment", "Memory Mapped Registers", "name", "MMR", "base", 0x000000L, "len", 0x0000c0L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x0000c0L, "len", 0x00ff40L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "25 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x032000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "128K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xfe0000L, "len", 0x020000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5514$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5514.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"MMR", Global.newObject("comment", "Memory Mapped Registers", "name", "MMR", "base", 0x000000L, "len", 0x0000c0L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x0000c0L, "len", 0x00ff40L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "25 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x032000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "128K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xfe0000L, "len", 0x020000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5514$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5514.Object", om.findStrict("ti.catalog.c5500.TMS320C5514.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5515$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5515.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5515.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5515$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5515$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5515$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5515$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5515.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5515.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"MMR", Global.newObject("comment", "Memory Mapped Registers", "name", "MMR", "base", 0x000000L, "len", 0x0000c0L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x0000c0L, "len", 0x00ff40L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "32 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x040000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "128K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xfe0000L, "len", 0x020000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5515$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5515.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"MMR", Global.newObject("comment", "Memory Mapped Registers", "name", "MMR", "base", 0x000000L, "len", 0x0000c0L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x0000c0L, "len", 0x00ff40L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "32 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x040000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "128K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xfe0000L, "len", 0x020000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5515$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5515.Object", om.findStrict("ti.catalog.c5500.TMS320C5515.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5561$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5561.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5561.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5561$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5561$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5561$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5561$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5561.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5561.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "4 blocks of 16K bytes on-chip Dual-Access RAM", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "64K bytes on-chip Single-Access RAM", "name", "SARAM", "base", 0x010000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM1", Global.newObject("comment", "4 blocks of 64K bytes on-chip Single-Access RAM", "name", "SARAM1", "base", 0x020000L, "len", 0x040000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"SHRAM", Global.newObject("comment", "2 block of 256K bytes shared memory", "name", "SHRAM", "base", 0xf80000L, "len", 0x07f000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "4K byte on-chip ROM", "name", "ROM", "base", 0xfff000L, "len", 0x001000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5561$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5561.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "4 blocks of 16K bytes on-chip Dual-Access RAM", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "64K bytes on-chip Single-Access RAM", "name", "SARAM", "base", 0x010000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM1", Global.newObject("comment", "4 blocks of 64K bytes on-chip Single-Access RAM", "name", "SARAM1", "base", 0x020000L, "len", 0x040000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"SHRAM", Global.newObject("comment", "2 block of 256K bytes shared memory", "name", "SHRAM", "base", 0xf80000L, "len", 0x07f000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "4K byte on-chip ROM", "name", "ROM", "base", 0xfff000L, "len", 0x001000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5561$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5561.Object", om.findStrict("ti.catalog.c5500.TMS320C5561.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void IOMAP$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5500/IOMAP.xs");
        om.bind("ti.catalog.c5500.IOMAP$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.IOMAP.Module", om.findStrict("ti.catalog.ICpuDataSheet.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5500.IOMAP$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5500.IOMAP$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5500.IOMAP$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5500.IOMAP$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.IOMAP.Instance", om.findStrict("ti.catalog.ICpuDataSheet.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCore", $$T_Str, "5500", "wh");
                po.addFld("isa", $$T_Str, "55", "wh");
                po.addFld("minProgUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
                po.addFld("minDataUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
                po.addFld("dataWordSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "12 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x018000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"PDROM", Global.newObject("comment", "32K bytes On-Chip ROM", "name", "PDROM", "base", 0xff8000L, "len", 0x008000L, "space", "code/data", "access", "RX")})}), "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.IOMAP.Params", om.findStrict("ti.catalog.ICpuDataSheet$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCore", $$T_Str, "5500", "wh");
                po.addFld("isa", $$T_Str, "55", "wh");
                po.addFld("minProgUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
                po.addFld("minDataUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
                po.addFld("dataWordSize", Proto.Elm.newCNum("(xdc_Int)"), 2L, "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "12 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x018000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"PDROM", Global.newObject("comment", "32K bytes On-Chip ROM", "name", "PDROM", "base", 0xff8000L, "len", 0x008000L, "space", "code/data", "access", "RX")})}), "wh");
    }

    void TMS320C1035$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1035.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1035.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C1035$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C1035$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C1035$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C1035$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1035.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1035.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "12 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x018000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "20 blocks of 8K bytes", "name", "SARAM", "base", 0x018000L, "len", 0x028000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"PDROM", Global.newObject("comment", "320K bytes On-Chip ROM", "name", "PDROM", "base", 0xfb0000L, "len", 0x050000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1035$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1035.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "12 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x018000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "20 blocks of 8K bytes", "name", "SARAM", "base", 0x018000L, "len", 0x028000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"PDROM", Global.newObject("comment", "320K bytes On-Chip ROM", "name", "PDROM", "base", 0xfb0000L, "len", 0x050000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1035$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1035.Object", om.findStrict("ti.catalog.c5500.TMS320C1035.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C1510$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1510.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1510.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C1510$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C1510$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C1510$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C1510$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1510.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1510.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1510$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1510.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1510$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1510.Object", om.findStrict("ti.catalog.c5500.TMS320C1510.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C1610$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1610.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1610.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C1610$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C1610$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C1610$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C1610$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1610.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1610.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1610$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1610.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1610$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1610.Object", om.findStrict("ti.catalog.c5500.TMS320C1610.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C1710$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1710.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1710.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C1710$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C1710$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C1710$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C1710$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1710.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1710.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "12 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x018000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"PDROM", Global.newObject("comment", "64K bytes On-Chip ROM", "name", "PDROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1710$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1710.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "12 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x018000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"PDROM", Global.newObject("comment", "64K bytes On-Chip ROM", "name", "PDROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1710$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C1710.Object", om.findStrict("ti.catalog.c5500.TMS320C1710.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C2320$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C2320.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C2320.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C2320$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C2320$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C2320$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C2320$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C2320.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C2320.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "12 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x018000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "20 blocks of 8K bytes", "name", "SARAM", "base", 0x018000L, "len", 0x028000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"PDROM", Global.newObject("comment", "320K bytes On-Chip ROM", "name", "PDROM", "base", 0xfb0000L, "len", 0x050000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C2320$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C2320.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "12 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x018000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "20 blocks of 8K bytes", "name", "SARAM", "base", 0x018000L, "len", 0x028000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"PDROM", Global.newObject("comment", "320K bytes On-Chip ROM", "name", "PDROM", "base", 0xfb0000L, "len", 0x050000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C2320$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C2320.Object", om.findStrict("ti.catalog.c5500.TMS320C2320.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C2420$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C2420.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C2420.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C2420$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C2420$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C2420$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C2420$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C2420.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C2420.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "12 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x018000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"PDROM", Global.newObject("comment", "64K bytes On-Chip ROM", "name", "PDROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C2420$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C2420.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "12 blocks of 8K bytes", "name", "SARAM", "base", 0x010000L, "len", 0x018000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"PDROM", Global.newObject("comment", "64K bytes On-Chip ROM", "name", "PDROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C2420$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C2420.Object", om.findStrict("ti.catalog.c5500.TMS320C2420.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5903$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5903.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5903.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5903$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5903$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5903$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5903$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5903.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5903.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5903$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5903.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5903$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5903.Object", om.findStrict("ti.catalog.c5500.TMS320C5903.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5905$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5905.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5905.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5905$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5905$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5905$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5905$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5905.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5905.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5905$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5905.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5905$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5905.Object", om.findStrict("ti.catalog.c5500.TMS320C5905.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5910$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5910.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5910.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5910$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5910$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5910$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5910$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5910.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5910.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5910$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5910.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5910$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5910.Object", om.findStrict("ti.catalog.c5500.TMS320C5910.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5912$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5912.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5912.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5912$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5912$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5912$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5912$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5912.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5912.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5912$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5912.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5912$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5912.Object", om.findStrict("ti.catalog.c5500.TMS320C5912.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5944$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5944.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5944.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5944$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5944$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5944$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5944$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5944.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5944.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5944$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5944.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5944$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5944.Object", om.findStrict("ti.catalog.c5500.TMS320C5944.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5946$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5946.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5946.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5946$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5946$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5946$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5946$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5946.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5946.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5946$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5946.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5946$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5946.Object", om.findStrict("ti.catalog.c5500.TMS320C5946.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320C5948$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5948.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5948.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5948$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5948$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320C5948$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320C5948$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5948.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5948.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5948$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5948.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5948$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320C5948.Object", om.findStrict("ti.catalog.c5500.TMS320C5948.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320CRYUJIN$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CRYUJIN.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CRYUJIN.Module", om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320CRYUJIN$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320CRYUJIN$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320CRYUJIN$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320CRYUJIN$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CRYUJIN.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CRYUJIN.Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"BANKED_SARAM", Global.newObject("comment", "64K bytes in 16 banks of SARAM", "name", "BANKED_SARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "192K bytes On-Chip Single-Access RAM", "name", "SARAM", "base", 0x010000L, "len", 0x030000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"PDROM", Global.newObject("comment", "128K bytes On-Chip ROM", "name", "PDROM", "base", 0xfe0000L, "len", 0x020000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CRYUJIN$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CRYUJIN.Params", om.findStrict("ti.catalog.c5500.IOMAP$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"BANKED_SARAM", Global.newObject("comment", "64K bytes in 16 banks of SARAM", "name", "BANKED_SARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "192K bytes On-Chip Single-Access RAM", "name", "SARAM", "base", 0x010000L, "len", 0x030000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"PDROM", Global.newObject("comment", "128K bytes On-Chip ROM", "name", "PDROM", "base", 0xfe0000L, "len", 0x020000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CRYUJIN$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CRYUJIN.Object", om.findStrict("ti.catalog.c5500.TMS320CRYUJIN.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320CDA255$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA255.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CDA255.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320CDA255$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320CDA255$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320CDA255$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320CDA255$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA255.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CDA255.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "24 blocks of 8K bytes", "name", "SARAM", "base", 0x10000L, "len", 0x30000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA255$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CDA255.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "8 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "24 blocks of 8K bytes", "name", "SARAM", "base", 0x10000L, "len", 0x30000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA255$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CDA255.Object", om.findStrict("ti.catalog.c5500.TMS320CDA255.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320CDA295$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA295.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CDA295.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320CDA295$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320CDA295$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320CDA295$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320CDA295$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA295.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CDA295.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.4", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "24 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x030000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA295$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CDA295.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.4", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "24 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x030000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA295$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CDA295.Object", om.findStrict("ti.catalog.c5500.TMS320CDA295.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TMS320CDA300$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA300.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CDA300.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320CDA300$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320CDA300$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TMS320CDA300$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TMS320CDA300$$construct"));
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA300.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CDA300.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.4", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "24 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x030000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA300$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CDA300.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.4", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM", Global.newObject("comment", "24 blocks of 8K bytes", "name", "DARAM", "base", 0x000000L, "len", 0x030000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"ROM", Global.newObject("comment", "64K bytes One-Wait-State On-Chip ROM", "name", "ROM", "base", 0xff0000L, "len", 0x010000L, "space", "code/data", "access", "RX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA300$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TMS320CDA300.Object", om.findStrict("ti.catalog.c5500.TMS320CDA300.Instance", "ti.catalog.c5500"));
                po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), $$UNDEF);
                po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), $$UNDEF);
    }

    void TNETV1050$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5500/TNETV1050.xs");
        om.bind("ti.catalog.c5500.TNETV1050$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TNETV1050.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TNETV1050.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TNETV1050$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TNETV1050$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TNETV1050$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TNETV1050$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5500.TNETV1050$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5500.TNETV1050$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5500.TNETV1050$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5500.TNETV1050$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TNETV1050.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TNETV1050.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM01", Global.newObject("comment", "2 blocks of 16K bytes on-chip Dual-Access RAM", "name", "DARAM01", "base", 0x000000L, "len", 0x008000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"DARAM23", Global.newObject("comment", "2 blocks of 16K bytes on-chip Dual-Access RAM", "name", "DARAM23", "base", 0x008000L, "len", 0x008000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "64K bytes on-chip Single-Access RAM", "name", "SARAM", "base", 0x010000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupt Vector Table", "name", "VECT", "base", 0xfff800L, "len", 0x000100L, "space", "code", "access", "RWX")})}), "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TNETV1050$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TNETV1050.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM01", Global.newObject("comment", "2 blocks of 16K bytes on-chip Dual-Access RAM", "name", "DARAM01", "base", 0x000000L, "len", 0x008000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"DARAM23", Global.newObject("comment", "2 blocks of 16K bytes on-chip Dual-Access RAM", "name", "DARAM23", "base", 0x008000L, "len", 0x008000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "64K bytes on-chip Single-Access RAM", "name", "SARAM", "base", 0x010000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupt Vector Table", "name", "VECT", "base", 0xfff800L, "len", 0x000100L, "space", "code", "access", "RWX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TNETV1050$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TNETV1050.Object", om.findStrict("ti.catalog.c5500.TNETV1050.Instance", "ti.catalog.c5500"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), fxn);
    }

    void TNETV1055$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5500/TNETV1055.xs");
        om.bind("ti.catalog.c5500.TNETV1055$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TNETV1055.Module", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TNETV1055.Module", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TNETV1055$$create", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TNETV1055$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.catalog.c5500.TNETV1055$$construct", "ti.catalog.c5500"), Global.get("ti$catalog$c5500$TNETV1055$$construct"));
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.c5500.TNETV1055$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5500.TNETV1055$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "instance$meta$init");
                if (fxn != null) om.bind("ti.catalog.c5500.TNETV1055$$instance$meta$init", true);
                if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.c5500.TNETV1055$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TNETV1055.Instance", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TNETV1055.Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM01", Global.newObject("comment", "2 blocks of 16K bytes on-chip Dual-Access RAM", "name", "DARAM01", "base", 0x000000L, "len", 0x008000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"DARAM23", Global.newObject("comment", "2 blocks of 16K bytes on-chip Dual-Access RAM", "name", "DARAM23", "base", 0x008000L, "len", 0x008000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "64K bytes on-chip Single-Access RAM", "name", "SARAM", "base", 0x010000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupt Vector Table", "name", "VECT", "base", 0xfff800L, "len", 0x000100L, "space", "code", "access", "RWX")})}), "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), fxn);
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TNETV1055$$Params", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TNETV1055.Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$Params", "ti.catalog.c5500"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
                po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.catalog.c5500")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DARAM01", Global.newObject("comment", "2 blocks of 16K bytes on-chip Dual-Access RAM", "name", "DARAM01", "base", 0x000000L, "len", 0x008000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"DARAM23", Global.newObject("comment", "2 blocks of 16K bytes on-chip Dual-Access RAM", "name", "DARAM23", "base", 0x008000L, "len", 0x008000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"SARAM", Global.newObject("comment", "64K bytes on-chip Single-Access RAM", "name", "SARAM", "base", 0x010000L, "len", 0x010000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"VECT", Global.newObject("comment", "On-Chip Interrupt Vector Table", "name", "VECT", "base", 0xfff800L, "len", 0x000100L, "space", "code", "access", "RWX")})}), "wh");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TNETV1055$$Object", "ti.catalog.c5500");
        po.init("ti.catalog.c5500.TNETV1055.Object", om.findStrict("ti.catalog.c5500.TNETV1055.Instance", "ti.catalog.c5500"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "ti.catalog.c5500"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "ti.catalog.c5500"), fxn);
    }

    void ITMS320C55xx$$ROV()
    {
    }

    void TMS320C5501$$ROV()
    {
    }

    void TMS320C5502$$ROV()
    {
    }

    void TMS320C5503$$ROV()
    {
    }

    void TMS320C5504$$ROV()
    {
    }

    void TMS320C5505$$ROV()
    {
    }

    void TMS320C5507$$ROV()
    {
    }

    void TMS320C5509$$ROV()
    {
    }

    void TMS320C5509A$$ROV()
    {
    }

    void TMS320C5510$$ROV()
    {
    }

    void TMS320C5510A$$ROV()
    {
    }

    void TMS320C5514$$ROV()
    {
    }

    void TMS320C5515$$ROV()
    {
    }

    void TMS320C5561$$ROV()
    {
    }

    void IOMAP$$ROV()
    {
    }

    void TMS320C1035$$ROV()
    {
    }

    void TMS320C1510$$ROV()
    {
    }

    void TMS320C1610$$ROV()
    {
    }

    void TMS320C1710$$ROV()
    {
    }

    void TMS320C2320$$ROV()
    {
    }

    void TMS320C2420$$ROV()
    {
    }

    void TMS320C5903$$ROV()
    {
    }

    void TMS320C5905$$ROV()
    {
    }

    void TMS320C5910$$ROV()
    {
    }

    void TMS320C5912$$ROV()
    {
    }

    void TMS320C5944$$ROV()
    {
    }

    void TMS320C5946$$ROV()
    {
    }

    void TMS320C5948$$ROV()
    {
    }

    void TMS320CRYUJIN$$ROV()
    {
    }

    void TMS320CDA255$$ROV()
    {
    }

    void TMS320CDA295$$ROV()
    {
    }

    void TMS320CDA300$$ROV()
    {
    }

    void TNETV1050$$ROV()
    {
    }

    void TNETV1055$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.catalog.c5500.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.catalog.c5500"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/c5500/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.catalog.c5500"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.catalog.c5500"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.catalog.c5500"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.catalog.c5500"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.catalog.c5500"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.catalog.c5500"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.catalog.c5500", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.catalog.c5500");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.catalog.c5500.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.platform", Global.newArray()));
        imports.add(Global.newArray("ti.catalog", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.catalog.c5500'];\n");
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

    void ITMS320C55xx$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.ITMS320C55xx", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.ITMS320C55xx.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.ITMS320C55xx", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5500.ITMS320C55xx$$capsule", "ti.catalog.c5500"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.ITMS320C55xx.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.ITMS320C55xx.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("ITMS320C55xx", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("ITMS320C55xx");
        vo.seal(null);
    }

    void TMS320C5501$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5501", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5501.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5501", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5501.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5501.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5501.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5501$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5501.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5501", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5501");
    }

    void TMS320C5502$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5502", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5502.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5502", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5502.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5502.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5502.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5502$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5502.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5502", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5502");
    }

    void TMS320C5503$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5503", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5503.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5503", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5503.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5503.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5503.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5503$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5503.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5503", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5503");
    }

    void TMS320C5504$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5504", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5504.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5504", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5504.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5504.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5504.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5504$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5504.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5504", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5504");
    }

    void TMS320C5505$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5505", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5505.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5505", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5505.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5505.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5505.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5505$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5505.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5505", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5505");
    }

    void TMS320C5507$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5507", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5507.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5507", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5507.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5507.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5507.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5507$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5507.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5507", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5507");
    }

    void TMS320C5509$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5509", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5509.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5509", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5509.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5509.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5509.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5509$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5509.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5509", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5509");
    }

    void TMS320C5509A$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5509A", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5509A.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5509A", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5509A.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5509A.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5509A.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5509A$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5509A.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5509A", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5509A");
    }

    void TMS320C5510$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5510", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5510.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5510", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5510.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5510.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5510.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5510$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5510.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5510", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5510");
    }

    void TMS320C5510A$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5510A", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5510A.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5510A", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5510A.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5510A.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5510A.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5510A$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5510A.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5510A", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5510A");
    }

    void TMS320C5514$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5514", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5514.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5514", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5514.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5514.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5514.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5514$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5514.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5514", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5514");
    }

    void TMS320C5515$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5515", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5515.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5515", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5515.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5515.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5515.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5515$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5515.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5515", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5515");
    }

    void TMS320C5561$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5561", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5561.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5561", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5561.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5561.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5561.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5561$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5561.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5561", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5561");
    }

    void IOMAP$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.IOMAP", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.IOMAP.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.IOMAP", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5500.IOMAP$$capsule", "ti.catalog.c5500"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.IOMAP.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.IOMAP.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.IOMAP.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IOMAP", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IOMAP");
        vo.seal(null);
    }

    void TMS320C1035$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C1035", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1035.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C1035", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C1035.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C1035.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C1035.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C1035$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C1035.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C1035", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C1035");
    }

    void TMS320C1510$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C1510", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1510.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C1510", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C1510.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C1510.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C1510.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C1510$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C1510.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C1510", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C1510");
    }

    void TMS320C1610$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C1610", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1610.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C1610", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C1610.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C1610.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C1610.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C1610$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C1610.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C1610", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C1610");
    }

    void TMS320C1710$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C1710", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C1710.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C1710", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C1710.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C1710.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C1710.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C1710$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C1710.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C1710", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C1710");
    }

    void TMS320C2320$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C2320", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C2320.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C2320", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C2320.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C2320.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C2320.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C2320$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C2320.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C2320", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C2320");
    }

    void TMS320C2420$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C2420", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C2420.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C2420", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C2420.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C2420.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C2420.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C2420$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C2420.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C2420", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C2420");
    }

    void TMS320C5903$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5903", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5903.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5903", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5903.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5903.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5903.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5903$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5903.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5903", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5903");
    }

    void TMS320C5905$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5905", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5905.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5905", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5905.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5905.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5905.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5905$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5905.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5905", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5905");
    }

    void TMS320C5910$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5910", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5910.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5910", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5910.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5910.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5910.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5910$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5910.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5910", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5910");
    }

    void TMS320C5912$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5912", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5912.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5912", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5912.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5912.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5912.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5912$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5912.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5912", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5912");
    }

    void TMS320C5944$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5944", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5944.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5944", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5944.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5944.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5944.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5944$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5944.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5944", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5944");
    }

    void TMS320C5946$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5946", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5946.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5946", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5946.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5946.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5946.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5946$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5946.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5946", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5946");
    }

    void TMS320C5948$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320C5948", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320C5948.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320C5948", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320C5948.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320C5948.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320C5948.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320C5948$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320C5948.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320C5948", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320C5948");
    }

    void TMS320CRYUJIN$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320CRYUJIN", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CRYUJIN.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320CRYUJIN", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320CRYUJIN.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320CRYUJIN.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320CRYUJIN.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320CRYUJIN$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320CRYUJIN.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320CRYUJIN", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320CRYUJIN");
    }

    void TMS320CDA255$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA255", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA255.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320CDA255", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320CDA255.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320CDA255.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320CDA255.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320CDA255$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320CDA255.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320CDA255", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320CDA255");
    }

    void TMS320CDA295$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA295", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA295.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320CDA295", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320CDA295.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320CDA295.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320CDA295.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320CDA295$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320CDA295.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320CDA295", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320CDA295");
    }

    void TMS320CDA300$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA300", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TMS320CDA300.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TMS320CDA300", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TMS320CDA300.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TMS320CDA300.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TMS320CDA300.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TMS320CDA300$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TMS320CDA300.Object", "ti.catalog.c5500"));
        pkgV.bind("TMS320CDA300", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TMS320CDA300");
    }

    void TNETV1050$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TNETV1050", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TNETV1050.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TNETV1050", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5500.TNETV1050$$capsule", "ti.catalog.c5500"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TNETV1050.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TNETV1050.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TNETV1050.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TNETV1050$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TNETV1050.Object", "ti.catalog.c5500"));
        pkgV.bind("TNETV1050", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TNETV1050");
    }

    void TNETV1055$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.c5500.TNETV1055", "ti.catalog.c5500");
        po = (Proto.Obj)om.findStrict("ti.catalog.c5500.TNETV1055.Module", "ti.catalog.c5500");
        vo.init2(po, "ti.catalog.c5500.TNETV1055", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.c5500.TNETV1055$$capsule", "ti.catalog.c5500"));
        vo.bind("Instance", om.findStrict("ti.catalog.c5500.TNETV1055.Instance", "ti.catalog.c5500"));
        vo.bind("Params", om.findStrict("ti.catalog.c5500.TNETV1055.Params", "ti.catalog.c5500"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.catalog.c5500.TNETV1055.Params", "ti.catalog.c5500")).newInstance());
        vo.bind("$package", om.findStrict("ti.catalog.c5500", "ti.catalog.c5500"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.c5500")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.c5500.TNETV1055$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.catalog.c5500.TNETV1055.Object", "ti.catalog.c5500"));
        pkgV.bind("TNETV1055", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TNETV1055");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5501", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5502", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5503", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5504", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5505", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5507", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5509", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5509A", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5510", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5510A", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5514", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5515", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5561", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C1035", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C1510", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C1610", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C1710", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C2320", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C2420", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5903", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5905", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5910", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5912", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5944", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5946", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320C5948", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320CRYUJIN", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320CDA255", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320CDA295", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TMS320CDA300", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TNETV1050", "ti.catalog.c5500"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.c5500.TNETV1055", "ti.catalog.c5500"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.catalog.c5500.ITMS320C55xx")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5501")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5502")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5503")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5504")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5505")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5507")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5509")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5509A")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5510")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5510A")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5514")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5515")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5561")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.IOMAP")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C1035")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C1510")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C1610")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C1710")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C2320")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C2420")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5903")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5905")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5910")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5912")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5944")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5946")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320C5948")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320CRYUJIN")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320CDA255")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320CDA295")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TMS320CDA300")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TNETV1050")).bless();
        ((Value.Obj)om.getv("ti.catalog.c5500.TNETV1055")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.catalog.c5500")).add(pkgV);
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
        ITMS320C55xx$$OBJECTS();
        TMS320C5501$$OBJECTS();
        TMS320C5502$$OBJECTS();
        TMS320C5503$$OBJECTS();
        TMS320C5504$$OBJECTS();
        TMS320C5505$$OBJECTS();
        TMS320C5507$$OBJECTS();
        TMS320C5509$$OBJECTS();
        TMS320C5509A$$OBJECTS();
        TMS320C5510$$OBJECTS();
        TMS320C5510A$$OBJECTS();
        TMS320C5514$$OBJECTS();
        TMS320C5515$$OBJECTS();
        TMS320C5561$$OBJECTS();
        IOMAP$$OBJECTS();
        TMS320C1035$$OBJECTS();
        TMS320C1510$$OBJECTS();
        TMS320C1610$$OBJECTS();
        TMS320C1710$$OBJECTS();
        TMS320C2320$$OBJECTS();
        TMS320C2420$$OBJECTS();
        TMS320C5903$$OBJECTS();
        TMS320C5905$$OBJECTS();
        TMS320C5910$$OBJECTS();
        TMS320C5912$$OBJECTS();
        TMS320C5944$$OBJECTS();
        TMS320C5946$$OBJECTS();
        TMS320C5948$$OBJECTS();
        TMS320CRYUJIN$$OBJECTS();
        TMS320CDA255$$OBJECTS();
        TMS320CDA295$$OBJECTS();
        TMS320CDA300$$OBJECTS();
        TNETV1050$$OBJECTS();
        TNETV1055$$OBJECTS();
        ITMS320C55xx$$CONSTS();
        TMS320C5501$$CONSTS();
        TMS320C5502$$CONSTS();
        TMS320C5503$$CONSTS();
        TMS320C5504$$CONSTS();
        TMS320C5505$$CONSTS();
        TMS320C5507$$CONSTS();
        TMS320C5509$$CONSTS();
        TMS320C5509A$$CONSTS();
        TMS320C5510$$CONSTS();
        TMS320C5510A$$CONSTS();
        TMS320C5514$$CONSTS();
        TMS320C5515$$CONSTS();
        TMS320C5561$$CONSTS();
        IOMAP$$CONSTS();
        TMS320C1035$$CONSTS();
        TMS320C1510$$CONSTS();
        TMS320C1610$$CONSTS();
        TMS320C1710$$CONSTS();
        TMS320C2320$$CONSTS();
        TMS320C2420$$CONSTS();
        TMS320C5903$$CONSTS();
        TMS320C5905$$CONSTS();
        TMS320C5910$$CONSTS();
        TMS320C5912$$CONSTS();
        TMS320C5944$$CONSTS();
        TMS320C5946$$CONSTS();
        TMS320C5948$$CONSTS();
        TMS320CRYUJIN$$CONSTS();
        TMS320CDA255$$CONSTS();
        TMS320CDA295$$CONSTS();
        TMS320CDA300$$CONSTS();
        TNETV1050$$CONSTS();
        TNETV1055$$CONSTS();
        ITMS320C55xx$$CREATES();
        TMS320C5501$$CREATES();
        TMS320C5502$$CREATES();
        TMS320C5503$$CREATES();
        TMS320C5504$$CREATES();
        TMS320C5505$$CREATES();
        TMS320C5507$$CREATES();
        TMS320C5509$$CREATES();
        TMS320C5509A$$CREATES();
        TMS320C5510$$CREATES();
        TMS320C5510A$$CREATES();
        TMS320C5514$$CREATES();
        TMS320C5515$$CREATES();
        TMS320C5561$$CREATES();
        IOMAP$$CREATES();
        TMS320C1035$$CREATES();
        TMS320C1510$$CREATES();
        TMS320C1610$$CREATES();
        TMS320C1710$$CREATES();
        TMS320C2320$$CREATES();
        TMS320C2420$$CREATES();
        TMS320C5903$$CREATES();
        TMS320C5905$$CREATES();
        TMS320C5910$$CREATES();
        TMS320C5912$$CREATES();
        TMS320C5944$$CREATES();
        TMS320C5946$$CREATES();
        TMS320C5948$$CREATES();
        TMS320CRYUJIN$$CREATES();
        TMS320CDA255$$CREATES();
        TMS320CDA295$$CREATES();
        TMS320CDA300$$CREATES();
        TNETV1050$$CREATES();
        TNETV1055$$CREATES();
        ITMS320C55xx$$FUNCTIONS();
        TMS320C5501$$FUNCTIONS();
        TMS320C5502$$FUNCTIONS();
        TMS320C5503$$FUNCTIONS();
        TMS320C5504$$FUNCTIONS();
        TMS320C5505$$FUNCTIONS();
        TMS320C5507$$FUNCTIONS();
        TMS320C5509$$FUNCTIONS();
        TMS320C5509A$$FUNCTIONS();
        TMS320C5510$$FUNCTIONS();
        TMS320C5510A$$FUNCTIONS();
        TMS320C5514$$FUNCTIONS();
        TMS320C5515$$FUNCTIONS();
        TMS320C5561$$FUNCTIONS();
        IOMAP$$FUNCTIONS();
        TMS320C1035$$FUNCTIONS();
        TMS320C1510$$FUNCTIONS();
        TMS320C1610$$FUNCTIONS();
        TMS320C1710$$FUNCTIONS();
        TMS320C2320$$FUNCTIONS();
        TMS320C2420$$FUNCTIONS();
        TMS320C5903$$FUNCTIONS();
        TMS320C5905$$FUNCTIONS();
        TMS320C5910$$FUNCTIONS();
        TMS320C5912$$FUNCTIONS();
        TMS320C5944$$FUNCTIONS();
        TMS320C5946$$FUNCTIONS();
        TMS320C5948$$FUNCTIONS();
        TMS320CRYUJIN$$FUNCTIONS();
        TMS320CDA255$$FUNCTIONS();
        TMS320CDA295$$FUNCTIONS();
        TMS320CDA300$$FUNCTIONS();
        TNETV1050$$FUNCTIONS();
        TNETV1055$$FUNCTIONS();
        ITMS320C55xx$$SIZES();
        TMS320C5501$$SIZES();
        TMS320C5502$$SIZES();
        TMS320C5503$$SIZES();
        TMS320C5504$$SIZES();
        TMS320C5505$$SIZES();
        TMS320C5507$$SIZES();
        TMS320C5509$$SIZES();
        TMS320C5509A$$SIZES();
        TMS320C5510$$SIZES();
        TMS320C5510A$$SIZES();
        TMS320C5514$$SIZES();
        TMS320C5515$$SIZES();
        TMS320C5561$$SIZES();
        IOMAP$$SIZES();
        TMS320C1035$$SIZES();
        TMS320C1510$$SIZES();
        TMS320C1610$$SIZES();
        TMS320C1710$$SIZES();
        TMS320C2320$$SIZES();
        TMS320C2420$$SIZES();
        TMS320C5903$$SIZES();
        TMS320C5905$$SIZES();
        TMS320C5910$$SIZES();
        TMS320C5912$$SIZES();
        TMS320C5944$$SIZES();
        TMS320C5946$$SIZES();
        TMS320C5948$$SIZES();
        TMS320CRYUJIN$$SIZES();
        TMS320CDA255$$SIZES();
        TMS320CDA295$$SIZES();
        TMS320CDA300$$SIZES();
        TNETV1050$$SIZES();
        TNETV1055$$SIZES();
        ITMS320C55xx$$TYPES();
        TMS320C5501$$TYPES();
        TMS320C5502$$TYPES();
        TMS320C5503$$TYPES();
        TMS320C5504$$TYPES();
        TMS320C5505$$TYPES();
        TMS320C5507$$TYPES();
        TMS320C5509$$TYPES();
        TMS320C5509A$$TYPES();
        TMS320C5510$$TYPES();
        TMS320C5510A$$TYPES();
        TMS320C5514$$TYPES();
        TMS320C5515$$TYPES();
        TMS320C5561$$TYPES();
        IOMAP$$TYPES();
        TMS320C1035$$TYPES();
        TMS320C1510$$TYPES();
        TMS320C1610$$TYPES();
        TMS320C1710$$TYPES();
        TMS320C2320$$TYPES();
        TMS320C2420$$TYPES();
        TMS320C5903$$TYPES();
        TMS320C5905$$TYPES();
        TMS320C5910$$TYPES();
        TMS320C5912$$TYPES();
        TMS320C5944$$TYPES();
        TMS320C5946$$TYPES();
        TMS320C5948$$TYPES();
        TMS320CRYUJIN$$TYPES();
        TMS320CDA255$$TYPES();
        TMS320CDA295$$TYPES();
        TMS320CDA300$$TYPES();
        TNETV1050$$TYPES();
        TNETV1055$$TYPES();
        if (isROV) {
            ITMS320C55xx$$ROV();
            TMS320C5501$$ROV();
            TMS320C5502$$ROV();
            TMS320C5503$$ROV();
            TMS320C5504$$ROV();
            TMS320C5505$$ROV();
            TMS320C5507$$ROV();
            TMS320C5509$$ROV();
            TMS320C5509A$$ROV();
            TMS320C5510$$ROV();
            TMS320C5510A$$ROV();
            TMS320C5514$$ROV();
            TMS320C5515$$ROV();
            TMS320C5561$$ROV();
            IOMAP$$ROV();
            TMS320C1035$$ROV();
            TMS320C1510$$ROV();
            TMS320C1610$$ROV();
            TMS320C1710$$ROV();
            TMS320C2320$$ROV();
            TMS320C2420$$ROV();
            TMS320C5903$$ROV();
            TMS320C5905$$ROV();
            TMS320C5910$$ROV();
            TMS320C5912$$ROV();
            TMS320C5944$$ROV();
            TMS320C5946$$ROV();
            TMS320C5948$$ROV();
            TMS320CRYUJIN$$ROV();
            TMS320CDA255$$ROV();
            TMS320CDA295$$ROV();
            TMS320CDA300$$ROV();
            TNETV1050$$ROV();
            TNETV1055$$ROV();
        }//isROV
        $$SINGLETONS();
        ITMS320C55xx$$SINGLETONS();
        TMS320C5501$$SINGLETONS();
        TMS320C5502$$SINGLETONS();
        TMS320C5503$$SINGLETONS();
        TMS320C5504$$SINGLETONS();
        TMS320C5505$$SINGLETONS();
        TMS320C5507$$SINGLETONS();
        TMS320C5509$$SINGLETONS();
        TMS320C5509A$$SINGLETONS();
        TMS320C5510$$SINGLETONS();
        TMS320C5510A$$SINGLETONS();
        TMS320C5514$$SINGLETONS();
        TMS320C5515$$SINGLETONS();
        TMS320C5561$$SINGLETONS();
        IOMAP$$SINGLETONS();
        TMS320C1035$$SINGLETONS();
        TMS320C1510$$SINGLETONS();
        TMS320C1610$$SINGLETONS();
        TMS320C1710$$SINGLETONS();
        TMS320C2320$$SINGLETONS();
        TMS320C2420$$SINGLETONS();
        TMS320C5903$$SINGLETONS();
        TMS320C5905$$SINGLETONS();
        TMS320C5910$$SINGLETONS();
        TMS320C5912$$SINGLETONS();
        TMS320C5944$$SINGLETONS();
        TMS320C5946$$SINGLETONS();
        TMS320C5948$$SINGLETONS();
        TMS320CRYUJIN$$SINGLETONS();
        TMS320CDA255$$SINGLETONS();
        TMS320CDA295$$SINGLETONS();
        TMS320CDA300$$SINGLETONS();
        TNETV1050$$SINGLETONS();
        TNETV1055$$SINGLETONS();
        $$INITIALIZATION();
    }
}
