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

public class ti_targets_omf_elf
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
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.targets.omf.elf.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.targets.omf.elf", new Value.Obj("ti.targets.omf.elf", pkgP));
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.targets.omf.elf.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.targets.omf.elf"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "ti.targets.omf.elf", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.targets.omf.elf");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.targets.omf.elf.");
        pkgV.bind("$vers", Global.newArray());
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.targets.omf.elf'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/elf.av5T',\n");
            sb.append("'lib/elf.a9t',\n");
            sb.append("'lib/elf.a54',\n");
            sb.append("'lib/elf.a55',\n");
            sb.append("'lib/elf.a55Pw',\n");
            sb.append("'lib/elf.a470',\n");
            sb.append("'lib/elf.aer4e',\n");
            sb.append("'lib/elf.ae64P',\n");
            sb.append("'lib/elf.ae64T',\n");
            sb.append("'lib/elf.am3',\n");
            sb.append("'lib/elf.aer4te',\n");
            sb.append("'lib/elf.a674',\n");
            sb.append("'lib/elf.aer4t',\n");
            sb.append("'lib/elf.a86N',\n");
            sb.append("'lib/elf.ar4te',\n");
            sb.append("'lib/elf.a62',\n");
            sb.append("'lib/elf.a64',\n");
            sb.append("'lib/elf.aer4',\n");
            sb.append("'lib/elf.a67',\n");
            sb.append("'lib/elf.a86U',\n");
            sb.append("'lib/elf.av7A',\n");
            sb.append("'lib/elf.a86W',\n");
            sb.append("'lib/elf.a11e',\n");
            sb.append("'lib/elf.ae9t',\n");
            sb.append("'lib/elf.a67P',\n");
            sb.append("'lib/elf.a470uC',\n");
            sb.append("'lib/elf.a28L',\n");
            sb.append("'lib/elf.ae470',\n");
            sb.append("'lib/elf.a11',\n");
            sb.append("'lib/elf.aem3',\n");
            sb.append("'lib/elf.a86GW',\n");
            sb.append("'lib/elf.a67e',\n");
            sb.append("'lib/elf.a28FP',\n");
            sb.append("'lib/elf.a430',\n");
            sb.append("'lib/elf.ae674e',\n");
            sb.append("'lib/elf.ae674',\n");
            sb.append("'lib/elf.a674e',\n");
            sb.append("'lib/elf.am3e',\n");
            sb.append("'lib/elf.ae64Te',\n");
            sb.append("'lib/elf.a86',\n");
            sb.append("'lib/elf.a64Te',\n");
            sb.append("'lib/elf.a28',\n");
            sb.append("'lib/elf.ae67P',\n");
            sb.append("'lib/elf.av6',\n");
            sb.append("'lib/elf.a62e',\n");
            sb.append("'lib/elf.a7e',\n");
            sb.append("'lib/elf.aer4fte',\n");
            sb.append("'lib/elf.a430X',\n");
            sb.append("'lib/elf.a430XL',\n");
            sb.append("'lib/elf.a5',\n");
            sb.append("'lib/elf.a7',\n");
            sb.append("'lib/elf.aem3e',\n");
            sb.append("'lib/elf.a9',\n");
            sb.append("'lib/elf.ar4e',\n");
            sb.append("'lib/elf.a64P',\n");
            sb.append("'lib/elf.a64T',\n");
            sb.append("'lib/elf.ae7',\n");
            sb.append("'lib/elf.ae9',\n");
            sb.append("'lib/elf.ae64Pe',\n");
            sb.append("'lib/elf.aer4fe',\n");
            sb.append("'lib/elf.a470e',\n");
            sb.append("'lib/elf.ar4t',\n");
            sb.append("'lib/elf.ae7e',\n");
            sb.append("'lib/elf.a54f',\n");
            sb.append("'lib/elf.a55H',\n");
            sb.append("'lib/elf.a470MV',\n");
            sb.append("'lib/elf.a64Pe',\n");
            sb.append("'lib/elf.a64e',\n");
            sb.append("'lib/elf.a55L',\n");
            sb.append("'lib/elf.ar4',\n");
            sb.append("'lib/elf.aer4ft',\n");
            sb.append("'lib/elf.a55Pb',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/elf.av5T', {target: 'gnu.targets.arm.GCArmv5T'}],\n");
            sb.append("['lib/elf.a9t', {target: 'ti.targets.arm.Arm9t'}],\n");
            sb.append("['lib/elf.a54', {target: 'ti.targets.C54'}],\n");
            sb.append("['lib/elf.a55', {target: 'ti.targets.C55'}],\n");
            sb.append("['lib/elf.a55Pw', {target: 'ti.targets.C55P_word'}],\n");
            sb.append("['lib/elf.a470', {target: 'ti.targets.TMS470'}],\n");
            sb.append("['lib/elf.aer4e', {target: 'ti.targets.arm.elf.R4_big_endian'}],\n");
            sb.append("['lib/elf.ae64P', {target: 'ti.targets.elf.C64P'}],\n");
            sb.append("['lib/elf.ae64T', {target: 'ti.targets.elf.C64T'}],\n");
            sb.append("['lib/elf.am3', {target: 'ti.targets.arm.M3'}],\n");
            sb.append("['lib/elf.aer4te', {target: 'ti.targets.arm.elf.R4t_big_endian'}],\n");
            sb.append("['lib/elf.a674', {target: 'ti.targets.C674'}],\n");
            sb.append("['lib/elf.aer4t', {target: 'ti.targets.arm.elf.R4t'}],\n");
            sb.append("['lib/elf.a86N', {target: 'microsoft.targets.Net32'}],\n");
            sb.append("['lib/elf.ar4te', {target: 'ti.targets.arm.R4t_big_endian'}],\n");
            sb.append("['lib/elf.a62', {target: 'ti.targets.C62'}],\n");
            sb.append("['lib/elf.a64', {target: 'ti.targets.C64'}],\n");
            sb.append("['lib/elf.aer4', {target: 'ti.targets.arm.elf.R4'}],\n");
            sb.append("['lib/elf.a67', {target: 'ti.targets.C67'}],\n");
            sb.append("['lib/elf.a86U', {target: 'gnu.targets.Linux86'}],\n");
            sb.append("['lib/elf.av7A', {target: 'gnu.targets.arm.GCArmv7A'}],\n");
            sb.append("['lib/elf.a86W', {target: 'microsoft.targets.Win32'}],\n");
            sb.append("['lib/elf.a11e', {target: 'ti.targets.arm.Arm11_big_endian'}],\n");
            sb.append("['lib/elf.ae9t', {target: 'ti.targets.arm.elf.Arm9t'}],\n");
            sb.append("['lib/elf.a67P', {target: 'ti.targets.C67P'}],\n");
            sb.append("['lib/elf.a470uC', {target: 'gnu.targets.UCArm9'}],\n");
            sb.append("['lib/elf.a28L', {target: 'ti.targets.C28_large'}],\n");
            sb.append("['lib/elf.ae470', {target: 'ti.targets.elf.TMS470'}],\n");
            sb.append("['lib/elf.a11', {target: 'ti.targets.arm.Arm11'}],\n");
            sb.append("['lib/elf.aem3', {target: 'ti.targets.arm.elf.M3'}],\n");
            sb.append("['lib/elf.a86GW', {target: 'gnu.targets.Mingw'}],\n");
            sb.append("['lib/elf.a67e', {target: 'ti.targets.C67_big_endian'}],\n");
            sb.append("['lib/elf.a28FP', {target: 'ti.targets.C28_float'}],\n");
            sb.append("['lib/elf.a430', {target: 'ti.targets.MSP430'}],\n");
            sb.append("['lib/elf.ae674e', {target: 'ti.targets.elf.C674_big_endian'}],\n");
            sb.append("['lib/elf.ae674', {target: 'ti.targets.elf.C674'}],\n");
            sb.append("['lib/elf.a674e', {target: 'ti.targets.C674_big_endian'}],\n");
            sb.append("['lib/elf.am3e', {target: 'ti.targets.arm.M3_big_endian'}],\n");
            sb.append("['lib/elf.ae64Te', {target: 'ti.targets.elf.C64T_big_endian'}],\n");
            sb.append("['lib/elf.a86', {target: 'microsoft.targets.VC98'}],\n");
            sb.append("['lib/elf.a64Te', {target: 'ti.targets.C64T_big_endian'}],\n");
            sb.append("['lib/elf.a28', {target: 'ti.targets.C28'}],\n");
            sb.append("['lib/elf.ae67P', {target: 'ti.targets.elf.C67P'}],\n");
            sb.append("['lib/elf.av6', {target: 'gnu.targets.arm.GCArmv6'}],\n");
            sb.append("['lib/elf.a62e', {target: 'ti.targets.C62_big_endian'}],\n");
            sb.append("['lib/elf.a7e', {target: 'ti.targets.arm.Arm7_big_endian'}],\n");
            sb.append("['lib/elf.aer4fte', {target: 'ti.targets.arm.elf.R4Ft_big_endian'}],\n");
            sb.append("['lib/elf.a430X', {target: 'ti.targets.MSP430_large_code'}],\n");
            sb.append("['lib/elf.a430XL', {target: 'ti.targets.MSP430_large_data'}],\n");
            sb.append("['lib/elf.a5', {target: 'gnu.targets.Sparc'}],\n");
            sb.append("['lib/elf.a7', {target: 'ti.targets.arm.Arm7'}],\n");
            sb.append("['lib/elf.aem3e', {target: 'ti.targets.arm.elf.M3_big_endian'}],\n");
            sb.append("['lib/elf.a9', {target: 'ti.targets.arm.Arm9'}],\n");
            sb.append("['lib/elf.ar4e', {target: 'ti.targets.arm.R4_big_endian'}],\n");
            sb.append("['lib/elf.a64P', {target: 'ti.targets.C64P'}],\n");
            sb.append("['lib/elf.a64T', {target: 'ti.targets.C64T'}],\n");
            sb.append("['lib/elf.ae7', {target: 'ti.targets.arm.elf.Arm7'}],\n");
            sb.append("['lib/elf.ae9', {target: 'ti.targets.arm.elf.Arm9'}],\n");
            sb.append("['lib/elf.ae64Pe', {target: 'ti.targets.elf.C64P_big_endian'}],\n");
            sb.append("['lib/elf.aer4fe', {target: 'ti.targets.arm.elf.R4F_big_endian'}],\n");
            sb.append("['lib/elf.a470e', {target: 'ti.targets.TMS470_big_endian'}],\n");
            sb.append("['lib/elf.ar4t', {target: 'ti.targets.arm.R4t'}],\n");
            sb.append("['lib/elf.ae7e', {target: 'ti.targets.arm.elf.Arm7_big_endian'}],\n");
            sb.append("['lib/elf.a54f', {target: 'ti.targets.C54_far'}],\n");
            sb.append("['lib/elf.a55H', {target: 'ti.targets.C55_huge'}],\n");
            sb.append("['lib/elf.a470MV', {target: 'gnu.targets.MVArm9'}],\n");
            sb.append("['lib/elf.a64Pe', {target: 'ti.targets.C64P_big_endian'}],\n");
            sb.append("['lib/elf.a64e', {target: 'ti.targets.C64_big_endian'}],\n");
            sb.append("['lib/elf.a55L', {target: 'ti.targets.C55_large'}],\n");
            sb.append("['lib/elf.ar4', {target: 'ti.targets.arm.R4'}],\n");
            sb.append("['lib/elf.aer4ft', {target: 'ti.targets.arm.elf.R4Ft'}],\n");
            sb.append("['lib/elf.a55Pb', {target: 'ti.targets.C55P_byte'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/elf.av5T'].suffix = 'v5T';\n");
            sb.append("pkg.build.libDesc['lib/elf.a9t'].suffix = '9t';\n");
            sb.append("pkg.build.libDesc['lib/elf.a54'].suffix = '54';\n");
            sb.append("pkg.build.libDesc['lib/elf.a55'].suffix = '55';\n");
            sb.append("pkg.build.libDesc['lib/elf.a55Pw'].suffix = '55Pw';\n");
            sb.append("pkg.build.libDesc['lib/elf.a470'].suffix = '470';\n");
            sb.append("pkg.build.libDesc['lib/elf.aer4e'].suffix = 'er4e';\n");
            sb.append("pkg.build.libDesc['lib/elf.ae64P'].suffix = 'e64P';\n");
            sb.append("pkg.build.libDesc['lib/elf.ae64T'].suffix = 'e64T';\n");
            sb.append("pkg.build.libDesc['lib/elf.am3'].suffix = 'm3';\n");
            sb.append("pkg.build.libDesc['lib/elf.aer4te'].suffix = 'er4te';\n");
            sb.append("pkg.build.libDesc['lib/elf.a674'].suffix = '674';\n");
            sb.append("pkg.build.libDesc['lib/elf.aer4t'].suffix = 'er4t';\n");
            sb.append("pkg.build.libDesc['lib/elf.a86N'].suffix = '86N';\n");
            sb.append("pkg.build.libDesc['lib/elf.ar4te'].suffix = 'r4te';\n");
            sb.append("pkg.build.libDesc['lib/elf.a62'].suffix = '62';\n");
            sb.append("pkg.build.libDesc['lib/elf.a64'].suffix = '64';\n");
            sb.append("pkg.build.libDesc['lib/elf.aer4'].suffix = 'er4';\n");
            sb.append("pkg.build.libDesc['lib/elf.a67'].suffix = '67';\n");
            sb.append("pkg.build.libDesc['lib/elf.a86U'].suffix = '86U';\n");
            sb.append("pkg.build.libDesc['lib/elf.av7A'].suffix = 'v7A';\n");
            sb.append("pkg.build.libDesc['lib/elf.a86W'].suffix = '86W';\n");
            sb.append("pkg.build.libDesc['lib/elf.a11e'].suffix = '11e';\n");
            sb.append("pkg.build.libDesc['lib/elf.ae9t'].suffix = 'e9t';\n");
            sb.append("pkg.build.libDesc['lib/elf.a67P'].suffix = '67P';\n");
            sb.append("pkg.build.libDesc['lib/elf.a470uC'].suffix = '470uC';\n");
            sb.append("pkg.build.libDesc['lib/elf.a28L'].suffix = '28L';\n");
            sb.append("pkg.build.libDesc['lib/elf.ae470'].suffix = 'e470';\n");
            sb.append("pkg.build.libDesc['lib/elf.a11'].suffix = '11';\n");
            sb.append("pkg.build.libDesc['lib/elf.aem3'].suffix = 'em3';\n");
            sb.append("pkg.build.libDesc['lib/elf.a86GW'].suffix = '86GW';\n");
            sb.append("pkg.build.libDesc['lib/elf.a67e'].suffix = '67e';\n");
            sb.append("pkg.build.libDesc['lib/elf.a28FP'].suffix = '28FP';\n");
            sb.append("pkg.build.libDesc['lib/elf.a430'].suffix = '430';\n");
            sb.append("pkg.build.libDesc['lib/elf.ae674e'].suffix = 'e674e';\n");
            sb.append("pkg.build.libDesc['lib/elf.ae674'].suffix = 'e674';\n");
            sb.append("pkg.build.libDesc['lib/elf.a674e'].suffix = '674e';\n");
            sb.append("pkg.build.libDesc['lib/elf.am3e'].suffix = 'm3e';\n");
            sb.append("pkg.build.libDesc['lib/elf.ae64Te'].suffix = 'e64Te';\n");
            sb.append("pkg.build.libDesc['lib/elf.a86'].suffix = '86';\n");
            sb.append("pkg.build.libDesc['lib/elf.a64Te'].suffix = '64Te';\n");
            sb.append("pkg.build.libDesc['lib/elf.a28'].suffix = '28';\n");
            sb.append("pkg.build.libDesc['lib/elf.ae67P'].suffix = 'e67P';\n");
            sb.append("pkg.build.libDesc['lib/elf.av6'].suffix = 'v6';\n");
            sb.append("pkg.build.libDesc['lib/elf.a62e'].suffix = '62e';\n");
            sb.append("pkg.build.libDesc['lib/elf.a7e'].suffix = '7e';\n");
            sb.append("pkg.build.libDesc['lib/elf.aer4fte'].suffix = 'er4fte';\n");
            sb.append("pkg.build.libDesc['lib/elf.a430X'].suffix = '430X';\n");
            sb.append("pkg.build.libDesc['lib/elf.a430XL'].suffix = '430XL';\n");
            sb.append("pkg.build.libDesc['lib/elf.a5'].suffix = '5';\n");
            sb.append("pkg.build.libDesc['lib/elf.a7'].suffix = '7';\n");
            sb.append("pkg.build.libDesc['lib/elf.aem3e'].suffix = 'em3e';\n");
            sb.append("pkg.build.libDesc['lib/elf.a9'].suffix = '9';\n");
            sb.append("pkg.build.libDesc['lib/elf.ar4e'].suffix = 'r4e';\n");
            sb.append("pkg.build.libDesc['lib/elf.a64P'].suffix = '64P';\n");
            sb.append("pkg.build.libDesc['lib/elf.a64T'].suffix = '64T';\n");
            sb.append("pkg.build.libDesc['lib/elf.ae7'].suffix = 'e7';\n");
            sb.append("pkg.build.libDesc['lib/elf.ae9'].suffix = 'e9';\n");
            sb.append("pkg.build.libDesc['lib/elf.ae64Pe'].suffix = 'e64Pe';\n");
            sb.append("pkg.build.libDesc['lib/elf.aer4fe'].suffix = 'er4fe';\n");
            sb.append("pkg.build.libDesc['lib/elf.a470e'].suffix = '470e';\n");
            sb.append("pkg.build.libDesc['lib/elf.ar4t'].suffix = 'r4t';\n");
            sb.append("pkg.build.libDesc['lib/elf.ae7e'].suffix = 'e7e';\n");
            sb.append("pkg.build.libDesc['lib/elf.a54f'].suffix = '54f';\n");
            sb.append("pkg.build.libDesc['lib/elf.a55H'].suffix = '55H';\n");
            sb.append("pkg.build.libDesc['lib/elf.a470MV'].suffix = '470MV';\n");
            sb.append("pkg.build.libDesc['lib/elf.a64Pe'].suffix = '64Pe';\n");
            sb.append("pkg.build.libDesc['lib/elf.a64e'].suffix = '64e';\n");
            sb.append("pkg.build.libDesc['lib/elf.a55L'].suffix = '55L';\n");
            sb.append("pkg.build.libDesc['lib/elf.ar4'].suffix = 'r4';\n");
            sb.append("pkg.build.libDesc['lib/elf.aer4ft'].suffix = 'er4ft';\n");
            sb.append("pkg.build.libDesc['lib/elf.a55Pb'].suffix = '55Pb';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Arr)om.findStrict("$packages", "ti.targets.omf.elf")).add(pkgV);
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
