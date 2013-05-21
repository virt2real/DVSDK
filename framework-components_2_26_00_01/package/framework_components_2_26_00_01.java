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

public class framework_components_2_26_00_01
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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.global");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.dskt2");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.dman3");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.acpy3");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.addrspace");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.bufres");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.edma3chan");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.grouputils");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.hdvicp");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.memtcm");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.nullresource");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.sdma");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.shmbuf");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.vicp");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.memutils");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.utils");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.utils.api");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.utils.gtinfra");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.edma3");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.scpy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.hdintc");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.hdvicpsync");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.vicpsync");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.utils.trace");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.dman3.examples.fastcopy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.examples.dmaxfer");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.examples.dma");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.examples.codecs.auddec1");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.examples.codecs.template");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.examples.codecs.edmacodec1");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.examples.codecs.idma3codec1");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.ires.examples.codecs.vicp2codec1");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.addrspace");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.bufres");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.bufres_yield");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.dmaxferscratch");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.dummyedma3");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.hdvicp");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.lateacquire");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.memtcm");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.nonrtscexample");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.nullresource");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.scratchedma3");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.sdma");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.shmbuf");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.staticreg");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.vicp");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.fc.rman.examples.vicpsync");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("framework_components_2_26_00_01.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("framework_components_2_26_00_01", new Value.Obj("framework_components_2_26_00_01", pkgP));
    }

    void $$SINGLETONS()
    {
        pkgP.init("framework_components_2_26_00_01.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "framework_components_2_26_00_01"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "framework_components_2_26_00_01", Value.DEFAULT, false);
        pkgV.bind("$name", "framework_components_2_26_00_01");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "framework_components_2_26_00_01.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.fc.global", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.dskt2", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.dman3", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.acpy3", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.addrspace", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.bufres", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.edma3chan", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.grouputils", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.hdvicp", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.memtcm", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.nullresource", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.sdma", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.shmbuf", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.vicp", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.memutils", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.utils", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.utils.api", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.utils.gtinfra", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.edma3", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.scpy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.hdintc", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.hdvicpsync", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.vicpsync", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.utils.trace", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.dman3.examples.fastcopy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.examples.dmaxfer", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.examples.dma", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.examples.codecs.auddec1", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.examples.codecs.template", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.examples.codecs.edmacodec1", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.examples.codecs.idma3codec1", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.ires.examples.codecs.vicp2codec1", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.addrspace", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.bufres", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.bufres_yield", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.dmaxferscratch", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.dummyedma3", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.hdvicp", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.lateacquire", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.memtcm", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.nonrtscexample", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.nullresource", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.scratchedma3", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.sdma", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.shmbuf", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.staticreg", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.vicp", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.fc.rman.examples.vicpsync", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['framework_components_2_26_00_01'];\n");
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

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Arr)om.findStrict("$packages", "framework_components_2_26_00_01")).add(pkgV);
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
        if (isROV) {
        }//isROV
        $$SINGLETONS();
        $$INITIALIZATION();
    }
}
