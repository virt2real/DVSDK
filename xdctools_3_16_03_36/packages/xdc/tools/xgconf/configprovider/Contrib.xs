var cfgMain;

/* replace the standard error reporter to collect JS errors */
var jsErrors = new java.io.ByteArrayOutputStream();
var ps = new java.io.PrintStream(jsErrors);
var rhino = Packages.org.mozilla.javascript;
var er = rhino.tools.ToolErrorReporter(true, ps);
var older = rhino.Context.currentContext.setErrorReporter(er);

function module$meta$init() {
    cfgMain = xdc.module('xdc.cfg.Main');
}

/**
 * This function has no business being in this file, and should be moved
 * into xdc.cfg package. It's included here to avoid a compatibility break.
 * Since the issue of controlling how much of the config model is executed
 * has come up before, should make the xdc.cfg API robust enough to avoid
 * changing it again for a long while.
 */
function runUserScript(script) {
    cfgMain.$private.$$cfgCapsule._userscript(cfgMain.$private.$$legacy, script);
    if (xdc.om.$$errors.length > 0) {
        return (cfgMain.$capsule.getErrors());
    }
    return ("");
}

function execConfig(exeName, pkgName, cfgScript)
{
    var exception = null;
    var setRetVal, runRetVal, validateRetVal;

    function hasError(result) {
        var str = result + "";
        return (str.match("@@error:::") || str.match("@@fatal:::"));
    }

    try {
        var cfgtestDir = xdc.getPackageBase(pkgName);
        var cfName = 'package/cfg/' +  exeName.replace(/\.([^\.]*)$/,"_$1") + ".cfg";
        xdc.$$make_om('cfg');
        /* the following line should be removed before xdc-t34 */
        xdc.om.$$bind('$$genflg', 1);
        var saved_cwd = java.io.File('.').getCanonicalPath();
        utils.cwd =  cfgtestDir;

        /* initialize the configuration step */
        cfgMain.init();
        setRetVal = cfgMain.setExecutable(cfName, cfgtestDir);

        /* run the config model */
        if (!hasError(setRetVal)) {
            var script = cfgScript? cfgScript : null;
            if (this.breakAfterUserScript) {
                /* run only the user script */
                runRetVal = runUserScript(script);
            }
            else {
                /* run the whole config model */
                runRetVal = cfgMain.runStringCfg(script);
            }
        }

        /* validate the resulting configuration */
        if (!hasError(runRetVal)) {
            validateRetVal = cfgMain.validate();
        }
    }
    catch (e) {
    	
    	/* For some syntax and reference errors, Rhino prints out a part of
    	 * the stack trace, so the file name and the line number have to be
    	 * extracted from that output.
    	 */
        if ((jsErrors + "") != "") {
            var lines = (jsErrors + "").split(/\n/);
            for each (var line in lines) {
                var m = line.match(/^js: "([^\"]*)", line ([0-9]+): (.*)/)
                if (m) {
                    var fileName = m[1];
                    var lineNumber = m[2];
                    if (fileName.match(".*/" + pkgName + "$")
                        && lineNumber > 1) {
                        fileName = Program.build.cfgScript;

                        /* xdc.cfg gets the line number wrong by one */
                        lineNumber--;

                        var loc = "\"" + fileName + "\", line " + lineNumber;
                        if (!exception) {
                            exception = "";
                        }
                        exception += "@@fatal::: :::" + loc + "::: :::" + m[3];
                    }
                }
            }
        }

        if (exception == null) {
            var stackTrace = Packages.config.Shell.getStackTrace("");
            var loc = " ";
            
            /* If a string is an argument to 'throw', then that string is in 
             * e, and e doesn't have any other properties. For most other 
             * errors, the message is in e.message.
             */
            if (typeof(e) == "string") {
            	var msg = e;
            }
            else {
                var msg = e.message + "";
            }
            msg = msg.replace(/^.*XDCException: /, "");

            var configScriptName = Program.build.cfgScript;
            if (!java.io.File(configScriptName).isAbsolute()) {
                configScriptName =
                    java.io.File(configScriptName).getAbsolutePath() + "";
            }
            var configFileName = configScriptName.replace(/.*[\\\/]/,"").
                replace(/\.([^\.]*)$/,".cfg");

            if (loc == " ") {
                /* Search for configuration file in stack trace */
                var re = new RegExp('.*/' + configFileName + '\", ([0-9]+).*');
                var m = re.exec(stackTrace);
                if (m) {
                    loc = "\"" + configScriptName + "\", line " + m[1];
                }
            }

            if (loc == " ") {
                /* Search for package name in stack trace */
                var re = new RegExp('.*/' + pkgName + '\", line ([0-9]+).*');
                var m = re.exec(stackTrace);
                if (m) {
                    /* xdc.cfg gets the line number wrong by one */
                    loc = "\"" + configScriptName + "\", line " + (m[1] - 1);
                }
            }

            /* Format message with file name and line number*/
            exception = "@@fatal::: :::" + loc + "::: :::" + msg;
        }
    }
    finally {
        /* restore the error reporter */
        rhino.Context.currentContext.setErrorReporter(older);

        xdc.om.$$bind('_$$setRetVal', (setRetVal == undefined) ? null : setRetVal);
        xdc.om.$$bind('_$$runRetVal', (runRetVal == undefined) ? null : runRetVal);
        xdc.om.$$bind('_$$validateRetVal', (validateRetVal == undefined) ? null : validateRetVal);
        xdc.om.$$bind('_$$contribException', (exception == undefined) ? null : exception);

        utils.cwd = saved_cwd;

        /* unseal the entire model */
        for each (var mod in xdc.om.$modules) {
            for (var prop in mod) {
                mod.$unseal(prop);
            }
            for each (var inst in mod.$instances) {
                for (var prop in inst) {
                    inst.$unseal(prop);
                }
            }
        }

        return xdc;
    }
}
