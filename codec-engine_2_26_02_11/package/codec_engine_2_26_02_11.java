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

public class codec_engine_2_26_02_11
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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.node");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.ipc");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.ipc.bios");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.ipc.dsplink");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.ipc.dsplink.dsp");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.ipc.linux");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.ipc.noOS");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.osal");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.osal.bios");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.osal.linux");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.osal.wince");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.osal.wince.utils");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.osal.noOS");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.alg");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.trace");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.speech");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.speech1");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.video");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.video1");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.video2");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.audio");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.audio1");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.global");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.image");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.image1");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.universal");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.vidtranscode");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.vidanalytics");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.video2.split");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.bioslog");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.utils");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.utils.rtcfg");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.utils.trace");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.utils.xdm");
        Global.callFxn("loadPackage", xdcO, "ti.dsplink.utils.lad");
        Global.callFxn("loadPackage", xdcO, "ti.dsplink.utils.ladclient");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.viddec1_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.videnc1_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.imgdec1_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.imgenc1_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.sphdec1_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.sphenc1_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.auddec1_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.audenc1_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.auddec1_ires");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.viddec2_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.viddec_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.videnc_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.imgdec_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.imgenc_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.sphdec_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.sphenc_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.auddec_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.audenc_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.g711");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.scale");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.vidtranscode_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.vidanalytics_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.viddec2split_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.codecs.universal_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.extensions");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.extensions.scale");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.servers");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.servers.all_codecs");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.servers.all_codecs_new_config");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.servers.server_api_example");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.servers.audio1_ires");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.buildutils");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.video_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.image_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.speech_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.audio_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.server_api_example");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.server_trace");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.video2_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.video1_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.image1_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.speech1_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.audio1_copy.sync");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.audio1_copy.async");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.audio1_ires");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.video2split_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.vidtranscode");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.vidanalytics");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.universal_copy");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.scale");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.speech");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.examples.apps.speech_copy_LAD");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.wizards.genserver");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.wizards.gencodecpkg");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("codec_engine_2_26_02_11.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("codec_engine_2_26_02_11", new Value.Obj("codec_engine_2_26_02_11", pkgP));
    }

    void $$SINGLETONS()
    {
        pkgP.init("codec_engine_2_26_02_11.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "codec_engine_2_26_02_11"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "codec_engine_2_26_02_11", Value.DEFAULT, false);
        pkgV.bind("$name", "codec_engine_2_26_02_11");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "codec_engine_2_26_02_11.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sdo.ce", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.node", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.ipc", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.ipc.bios", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.ipc.dsplink", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.ipc.dsplink.dsp", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.ipc.linux", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.ipc.noOS", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.osal", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.osal.bios", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.osal.linux", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.osal.wince", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.osal.wince.utils", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.osal.noOS", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.alg", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.trace", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.speech", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.speech1", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.video", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.video1", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.video2", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.audio", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.audio1", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.global", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.image", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.image1", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.universal", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.vidtranscode", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.vidanalytics", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.video2.split", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.bioslog", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.utils", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.utils.rtcfg", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.utils.trace", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.utils.xdm", Global.newArray()));
        imports.add(Global.newArray("ti.dsplink.utils.lad", Global.newArray()));
        imports.add(Global.newArray("ti.dsplink.utils.ladclient", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.viddec1_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.videnc1_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.imgdec1_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.imgenc1_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.sphdec1_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.sphenc1_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.auddec1_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.audenc1_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.auddec1_ires", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.viddec2_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.viddec_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.videnc_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.imgdec_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.imgenc_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.sphdec_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.sphenc_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.auddec_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.audenc_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.g711", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.scale", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.vidtranscode_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.vidanalytics_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.viddec2split_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.codecs.universal_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.extensions", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.extensions.scale", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.servers", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.servers.all_codecs", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.servers.all_codecs_new_config", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.servers.server_api_example", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.servers.audio1_ires", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.buildutils", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.video_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.image_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.speech_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.audio_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.server_api_example", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.server_trace", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.video2_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.video1_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.image1_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.speech1_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.audio1_copy.sync", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.audio1_copy.async", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.audio1_ires", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.video2split_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.vidtranscode", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.vidanalytics", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.universal_copy", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.scale", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.speech", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.examples.apps.speech_copy_LAD", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.wizards.genserver", Global.newArray()));
        imports.add(Global.newArray("ti.sdo.ce.wizards.gencodecpkg", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['codec_engine_2_26_02_11'];\n");
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
        ((Value.Arr)om.findStrict("$packages", "codec_engine_2_26_02_11")).add(pkgV);
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
