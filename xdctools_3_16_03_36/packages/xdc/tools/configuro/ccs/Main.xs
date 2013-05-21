/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

var xdcPathsFile;

/* 
 *  ======== run ========
 *  Main function, executed from the command line. Parses the arguments
 *  using getopt() and calls the above. If any function raises an
 *  exception, prints the error message and the usage.
 */
function run(cmdr, args)
{
    // print the usage message if requested
    if (args.length == 0) {
        cmdr.usage();
        return 1;
    }

    xdcPathsFile = this.xdcPathsFile;
    
    var xdcPathsPlainExample = 
        '--------------------------------------------------------\n' + 
        '# package path directories (absolute or relative to\n' +
        '# the project), one per line:\n' +  
        'c:\\davinciXYZevm\\codec_engine_1_20\\packages\n' + 
        'c:\\davinciXYZevm\\xdais_5_20\\packages\n' + 
        'd:\\mytools\\morepackages\n' +
        '--------------------------------------------------------\n' ;
    var xdcPathsJsExample = 
        '--------------------------------------------------------\n' + 
        '// DO NOT MOVE OR DELETE THIS LINE ' + 
        '[JavaScript xdcpaths]\n' + 
        '// Note: Use /FORWARD/ slashes for all directories!\n' + 
        'topdir = "c:/davinciXYZevm/;"\n' + 
        'xdcpaths = topdir + "codec_engine_1_20/packages;" + \n' + 
        '           topdir + "xdais_5_20/packages;" + \n' +
        '           "d:/mytools/morepackages";\n' +
        '--------------------------------------------------------\n' ;

    /* repositories we'll add to the package path */    
    var repos = [];

    /* process the --xdcpathsfile flag */
    if (this.xdcPathsFile != null) {
        var paths = "";
        var f = new java.io.File( this.xdcPathsFile );
        if (!f.exists()) {
            throw "\nERROR: xdc paths file " + this.xdcPathsFile + " not found!\n";
        }
        var paths = "";
        var lr = new java.io.LineNumberReader( java.io.FileReader(f) );
        var l;
        var firstLine = true;
        var xdcPathsType = "plain";
        while ((l = lr.readLine()) != null) {
            l = l + "";
            if (firstLine && (l.match( /^\/\// ) != null)) {
                // since the first line of the paths file begins with "//",
                // we interpret it as being a javascript xdcpaths file;
                // so we simply load and execute it and read "xdcpaths" variable
                try {
                    load( this.xdcPathsFile );
                    paths = xdcpaths;
                } catch (e) {
                    throw( "  Error: your script-based package paths file, " +
                           this.xdcPathsFile + ", is incorrect.\nThe package " + 
                           "path must be a semicolon-separated string " + 
                           "contained in variable named 'xdcpaths', "  +
                           "for example: \n" + xdcPathsJsExample
                           ); 
                     return;
                }
                xdcPathsType = "js";
                break;
            }
            firstLine = false;
            if (l == "" || (l.match( /^\s+$/) != null) ) {
                continue;  // empty lines
            }
            if (l.match( /^#/ ) != null) {
                continue;  // lines beginning with # are comments
            }
            paths = paths + ( paths != "" ? ";" : "" ) + l;
        };
        lr.close();
        
        if (paths == "") {
            print( "Warning: the list of package paths in file " +  
                   this.xdcPathsFile + " is completely empty.\n" + 
                   "If you get a build error, please open the file " + 
                   this.xdcPathsFile + " under 'Documents' folder in your " + 
                   "project and specify proper package paths.\n\n" +
                   "Example " + this.xdcPathsFile + " file (plain text variant):\n" + 
                   xdcPathsPlainExample + "\n" + 
                   "Example " + this.xdcPathsFile + " file (JavaScript variant):\n" + 
                   xdcPathsJsExample + "\n" +
                   "To silence this warning, define your package path to be " +
                   "at least one directory, even non-existent, e.g. 'c:/foo'.\n"
                    );
        }
        
        // remove extraneous semicolons
        paths = paths.replace( /;;/g, ";" ).replace( /;$/, "" ).replace( /^;/, "" );
        repos = paths.split(';');
    }

    /* process the --xp flags */
    if (this.xdcPath != null) {
        for (var i = 0; i < this.xdcPath.length; i++) {
            repos.push(this.xdcPath[i]);
        }
    }

    /* add all the found repositories to the package path */
    if (repos.length > 0) {
        var p = repos.join(';');
        java.lang.System.setProperty('xdc.path', p + ";" + java.lang.System.getProperty('xdc.path'));
    }

    var Configuro = xdc.module("xdc.tools.configuro.Main").create();
    for (var p in this) {
        if (p in Configuro) {
            Configuro[p] = this[p];
        }
    }

    print( "\nInfo: running XDC configuration using package path:" );
    print( environment['xdc.path'].replace( /;/g, "\n" ).replace( /\//g, "\\" ) + "\n" );
    print( "The configuration step is now running:\n" );

    Configuro.$module.$capsule._copy_stream = _copy_stream;
    Configuro.run( cmdr, args );

    if (new java.io.File( this.output ).exists()) {
        /* create <outdir>/cfg.c file if it doesn't exist */
        var file = new java.io.File( this.output + "/cfg.c" );
        if (!file.exists()) {
            var fw = new java.io.FileWriter( file );
            fw.write( "/* autogenerated file -- do not edit */\n" );
            fw.write( "extern int xdcconfig_generated;\n" );
            fw.close();
        }
    }
}

/* 
 *  ======== analyzeOutput ========
 *  Searches configuro output (i.e. stderr) for clues on what went wrong and
 *  describes how to fix it, if possible.
 */
function analyzeOutput( output )
{
    var info = "";
    var split;
    if ( (split = output.split( "Error: xdc.loadPackage: can't find package '" ))[1] != undefined ) {
        
        for (var i = 0; split[1].charAt(i) != "'"; i++);
        var missingPkg = split[1].substr( 0, i );
        info += 
            "XDC tools could not find package '" + missingPkg + "' in your " +
            "package path. \n" + 
            "If this is a valid package name -- \n" +  
            "To correct this error, you must locate a directory on your system \n" +
            "that contains the following path: '" + 
            missingPkg.replace( /\./g, "\\" ) + "\\'" + "\n" +
            "and you must make sure that the containing directory is listed in \n" +
            "the package paths in your '" + xdcPathsFile + "' file (located under\n" + 
            "the 'Documents' folder of your project).\n" +
            "For example, a package named 'ti.sdo.ce' may have a full path of \n" + 
            "c:\\davinciXYZevm\\codec_engine_1_20\\packages\\ti\\sdo\\ce\n" +
            "in which case the path 'c:\\davinciXYZevm\\codec_engine_1_20\\packages\\' \n" +
            "must be listed in the package paths file.                  ^^^^^^^^\n\n" +
            "Note: one common mistake is omitting the '/packages/' part\n" + 
            "from the package path when one exists; another is using BACKSLASHES (\\)\n" +
            "instead of FORWARD SLASHES (/) in javascript-based " + xdcPathsFile + " " +
            "file for directory separation." + 
            "\n\n" + 
            "If '" + missingPkg + "' is not a valid package name, \n" + 
            "correct it in your application configuration script (.cfg).\n" +
            "";
    } 
    else if ( (split = output.split( "Error: Can't find import file: '" ))[1] != undefined ) {
        for (var i = 0; split[1].charAt(i) != "'"; i++);
        var missingScript = split[1].substr( 0, i );
        info += 
            "XDC tools could not find file '" + missingScript + "' in your " +
            "package path. \n" + 
            "If this is a valid script name -- \n" +  
            "To correct this error, you must locate a directory on your system \n" +
            "that contains that script and add it to your package path.\n" +
            "(You can use an absolute path or one relative to your project,\n" +
            "e.g. '../../myTconfScripts/'.)\n" + 
            "If you are unsure which script attempted to load the missing script,\n" +
            "please look at the list of scripts located below the original error line above.\\n" +
            ""; 
    }
    else if ( (split = output.split( "exception from uncaught JavaScript throw:" ))[1] != undefined ) {
        info += 
            "A configuration script threw an exception (error). \n" + 
            "Please look at the highlighted script name and line number above " + 
            "to determine what could be the cause of error.\n" +
            ""; 
    }
    return info;
}

/* 
 *  ======== _copy_stream ========
 *  Reimplementation of Configuro's internal _copy_stream, that records stderr
 *  for later analysis
 */

function _copy_stream(ins, outs) {
    var stdErr = "";
    
    var thread = new java.lang.Thread(function() {
        var isr = new java.io.InputStreamReader(ins);
        var br = new java.io.BufferedReader(isr);
        var line;
        while (line = br.readLine()) {
            outs.println(line);
            if (outs == java.lang.System.err) {
                stdErr += line + "\n";
            }
        }
        if (outs == java.lang.System.err) {
            try {
                var info = analyzeOutput( stdErr  );
                if (info != "") {
                    print( "\n*************************" );
                    print( "Configuration step failed." );
                    print( "*************************" );
                    print( "" );
                    print( "Explanation: \n" + 
                           "-----------" );
                    print( info + "\n" );
                    print( "Please review the above information carefully to correct this configuration error." ); 
                }
            } catch (e) {
            }
        }
    });
    thread.start();
    return thread;
}
/*
 *  @(#) xdc.tools.configuro.ccs; 1, 0, 0, 0,34; 12-15-2007 18:23:21; /db/ztree/library/trees/bti-a52x/src/
 */

