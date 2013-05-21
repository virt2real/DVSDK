var CAPSULE_DIR = "/package/cfg/";      //$NON-NLS-1$
var CAPSULE_EXT = ".cfg";            //$NON-NLS-1$
var PACKAGE_BLD_XML_FILE_STR = "package.bld.xml";

var exeName = "";
var pkgName = "";
var textBuffer = null;
var cfgName = null;
var specBrowser = null;
var cfgScript = null;

/*
 *  ======== run ========
 */
function run( cmdr, args )
{

    var inst = this.$private
    inst.self = this;
    var fileName = null;
    
    for (var p in inst.self) inst[p] = inst.self[p];

    inst.cmdr = cmdr;
    inst.args = args;

    inst.cmdr.verbose(inst.verboseFlag);

    _validate(inst);

    if (inst.executableName) {
        exeName = inst.executableName;
    }

    if (inst.executableName) {
        cfgName = inst.cfgFileName;
    }

    if (inst.args.length > 0) {
        pkgName = inst.args[0];
    }


    if (inst.cfgScript) {
        cfgScript = inst.cfgScript;
    }
    
    var mod = xdc.module('xdc.tools.xgconf.configprovider.ConfigProvider');
    inst.cfgInst = mod.create(cfgName, exeName, pkgName, cfgScript);

    var cfgRootNode = null;
    var socket = this.$private.cmdr.socket;
    inst.cfgInst.$private.socket = socket;
    
    var haveDone = false;
    var methods = socket.getClass().getDeclaredMethods();
    for (var i = 0; (methods != null) && (i < methods.length); i++) {
        var name = methods[i].getName();
        if (name.compareTo("isServerDone") == 0) {
            haveDone = true;
        }
    }
  //  print ('Exists isServerDone: ' + haveDone);
    
    // Command loop
    var getCMDS = true;
    while (getCMDS) {
        if (haveDone) {
            if (socket.isServerDone()) {
                break;
            }
        }
        var cmd = socket.takeFromClient();
        var Command = Packages.org.eclipse.rtsc.xdctools.model.cfgdata.Command;
        if (cmd instanceof Command) {
            try {
                var id = cmd.getId();
        //    print ('cmd id: ' + id);
                switch (id) {
                    case cmd.VALIDATE:
                    	/* set breakAfterUserScript if given */
                        var args = cmd.getArgs();
                    	if (args && args.size() > 0) {
                    		inst.cfgInst.breakAfterUserScript = args.get(0);
                    	}
                        cfgRootNode = inst.cfgInst.loadCfgModel();
                        var results = cmd.getResults();
                        cmd.setStatus(cmd.OK);
                        results.add(cfgRootNode);
            //        print("returned root node");
                        break;
                    case cmd.EXECFXN:
                        var args = cmd.getArgs();
                 //   print('execfxn args: ' + args);
                        var output = inst.cfgInst.runCFFxn(args.get(0),
                                args.get(1), args.get(2), args.get(3),
                                args.get(4), args.get(5));
                        var results = cmd.getResults();
                        if (output != undefined) {
                            for (var i = 0; i < output.length; i++) {
                                results.add(output[i]);
                            }
               //     print('execfxn results: ' + results);
                        }
                        cmd.setStatus(cmd.OK);
                //    print("returned execfxn output: " + output);
                        break;
                    case cmd.TERMINATE:
                        cmd.setStatus(cmd.TERMINATE);
                        getCMDS = false;
                        cfgRootNode = null;
              //      print ('terminated');
                        break;
                    default:
                        /* not present in older versions so check compatibility */
                        if (("SYNCEXEC" in Command) && (id == cmd.SYNCEXEC)) {
                            cmd.runnable.run();
                            cmd.setStatus(cmd.OK);
                            break;
                        }
                        if (("EVAL" in Command) && (id == cmd.EVAL)) {
                            var e;
                            try {
                                /* run the command */
                                var args = cmd.args;
                                var ret = inst.cfgInst.eval(args.get(0));
                                /* return with result and good status */
                                cmd.getResults().add(ret);
                                cmd.setStatus(cmd.OK);
                            }
                            catch (e) {
                                /* failed, so return with an exception */
                                if (e instanceof Error) {
                                    e = e.message;
                                }
                                cmd.getResults().add(e);
                                cmd.setStatus(cmd.FAILED);
                            }
                            break;
                        }
                        //print ('default: ');
                        cmd.setStatus(cmd.UNKNOWN);
                        break;
                }
                socket.giveToClient(cmd);
        //    print ('returned cmd to client');
    
            } catch (e) {
                //print ('exception: ' + e);
                var exception = null;
                if (e instanceof xdc.jre.xdc.services.global.XDCException) {
                    exception = e;
                } else if (e instanceof java.lang.Throwable) {
                    exception = new xdc.jre.xdc.services.global.XDCException("Configuration: ", e.message);
                    exception.initCause(e);
                } else if (e instanceof Error) {
                    exception = new xdc.jre.xdc.services.global.XDCException("Configuration: ", ""+e);
                    if (e.javaException instanceof java.lang.Throwable) {
                        exception.initCause(e.javaException);
                    }
                } else if ("javaException" in e) {
                    exception = new xdc.jre.xdc.services.global.XDCException("Configuration: ", e.message);
                    if (e.javaException instanceof java.lang.Throwable) {
                        exception.initCause(e.javaException);
                    }
                } else {
                    exception = new xdc.jre.xdc.services.global.XDCException("Configuration: ", "" + e);
                }
                cmd.setStatus(cmd.FAILED);
                var results = cmd.getResults();
                results.add(exception);
                socket.giveToClient(cmd);
                getCMDS = false;
            }
        }
    }  
    
    return;
}

/*
 *  ======== addXGConfJars ========
 */
function addXGConfJars() {

    var eclsLoader = xdc.jre.java.lang.Thread.currentThread().getContextClassLoader(); 
    var scl = new xdc.jre.config.ShellClassLoader([], eclsLoader);
    var xgconf = xdc.useModule('xdc.tools.xgconf.Main');
    
    var jarlist = xgconf.getJars(null);
    var jars = jarlist.split(java.io.File.pathSeparator);
    
    for (var j in jars) {
        scl.addJar(jars[j]);
    }
}

/*
 *  ======== _validate ========
 */
function _validate( inst )
{
    return (true);
    if (inst.cmdr == undefined) return(true);
    
    if (inst.fileName) {
        return (true);
    }
    
}
