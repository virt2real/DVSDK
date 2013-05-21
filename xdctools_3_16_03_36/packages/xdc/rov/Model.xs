/* --COPYRIGHT--,EPL
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * --/COPYRIGHT--*/
/*
 *  ======== Model.xs ========
 */

/*
 *  ======== start ========
 */
function start(xmlVers, executable, recap, sym, mem, callBack)
{   
    xdc.om.$$bind('$name', 'rov');
    xdc.global.Program = xdc.useModule('xdc.rov.Program');
    Program.debugPrint("Beginning of Model.start");
    
    /* Check XML compatibility. */
    if (xmlVers != this.xmlVers) {
        Program.debugPrint("Incompatible version of ROV Model. Model version " +
                           this.xmlVers + ", client version " + xmlVers + ".");
        throw (new Error("Incompatible version of ROV Model. Model version " +
                         this.xmlVers + ", client version " + xmlVers + "."));
    }
    
    /* Store off the objects passed in */
    this.$private.sym = sym;
    this.$private.mem = mem;
    this.$private.callBack = callBack;
    this.$private.recap = recap;
        
    xdc.useModule('xdc.rov.support.ScalarStructs');
    
    /* Store off the list of all modules in the recap file */
    var mnames = [];
    for (var m in this.$private.recap.$modules) {
        if (m[0] != '#') {
            mnames.push(m);
        }
    }
    
    Program.$unseal('moduleNames');
    Program.moduleNames.$unseal();
    Program.moduleNames = mnames.sort();
    Program.moduleNames.$seal();
    Program.$seal('moduleNames');
    
    Program.$$bind('build', this.$private.recap.build);
        
    Program.$$bind('$modules', this.$private.recap.$modules);
    
    /* Notify the CallBack that we are about to start loading the packages. */
    callBack.updateStartupProgress(120, "Loading packages ...");
    
    /* Indicates whether getModuleDesc has been called on all modules. */
    Program.$private.allModsRead = false;
    
    /* 
     * Load all of the packages so the user gets this hit during 
     * startup rather than on the first view. 
     */
    for each (var mod in this.$private.recap.$modules) {
        try {
            Program.getModuleDesc(mod.$name);
        }
        catch (e) {
            Program.debugPrint("Failed to load module " + mod.$name + ": " + e);
            throw (new Error("Failed to load module " + mod.$name + ": " + e));
        }
    }

    /* getModuleDesc has been called on all modules. */
    Program.$private.allModsRead = true;
    
    /* 
     * TODO - version checks to ensure package versions in recap file
     * match package versions found along XDCPATH.
     */
    /*
    for each (var mod in this.$private.recap.$modules) {
        recapPkgVers = mod.$package.$vers.toString();
        pathPkg = xdc.loadPackage(mod.$package.$name);
        pathPkgVers = pathPkg.$vers;
    
        if (recapPkgVers != pathPkgVers) {
            throw new Error("xdc.rov.Model: Package " + mod.$package.$name
                + " version mismatch: Executable built with "
                + recapPkgVers + ", Package in path " + pathPkgVers);
        }
        else {
            print(mod.$package.$name + "Version matches fine.");
        }
    }
    */

    Program.debugPrint("bitsPerChar = " + this.$private.recap.build.target.bitsPerChar);

    /* 
     * Create the StringReader for reading dynamic strings. Create this first
     * in case the OFReader needs to fall back on it.
     */
    var strReader = initStringReader();
    
    /* Create and initialize the object file reader. */
    var ofReader = initOFReader(executable);  
    
    /* Bind the OFReader and StringReader to Program for looking up strings. */
    Program.$$bind('strReader', strReader);
    Program.$$bind('ofReader', ofReader);
    
    /* 
     * Set up the printf Formatter for any views that will use it. 
     * The formatter needs the symbol table for %r and the object
     * file reader for %s.
     */
    xdc.loadPackage('xdc.rta');
    
    /* 
     * TODO - We should be able to get the java implementation directly;
     * we shouldn't need to create a wrapper. 
     */
    //var javaSymTab = sym.getJavaImp();

    var javaSymTab = new xdc.jre.xdc.rov.ISymbolTable(
        {
            lookupDataSymbol: function lookupDataSymbol(addr) {
                return (sym.lookupDataSymbol(addr));
            },
            lookupFuncName: function lookupFuncName(addr) {
                return (sym.lookupFuncName(addr));
            }
        });

    xdc.jre.xdc.rta.Formatter.setSymbolTable(javaSymTab);
    
    /* Create the StructureDecoder and bind to Program. */
    var StructureDecoder = xdc.useModule('xdc.rov.StructureDecoder');
    var strDec = StructureDecoder.create(mem, this.$private.recap.build.target);
    Program.$$bind('strDec', strDec);
    
    /* Create the StateReader and bind to Program. */
    var StateReader = xdc.useModule('xdc.rov.StateReader');
    var stateReader = StateReader.create(sym, strDec);
    Program.$$bind('stateReader', stateReader);
    
    //Program.getModuleDesc('xdc.runtime.Text'); // ?????
    
    this.$private.initialized = true;
}

/*
 *  ======== initStringReader ========
 *  Creates a StringReader instance and saves it to the Model's $private
 *  object.
 */
function initStringReader()
{
    var Model = xdc.useModule('xdc.rov.Model');
    xdc.loadPackage('xdc.rov');

    /* Retrieve the MemoryImage java object. */
    var memReader = Model.getMemoryImageInst();
    
    /* Create a StringReader instance using the memory reader instance. */
    var strReader = new xdc.jre.xdc.rov.StringReader(memReader);
    
    /* Store the StringReader in the Model's $private object. */
    Model.$private.strReader = strReader;
    
    return (strReader);
}

/*
 *  ======== initOFReader ========
 *  Creates and initializes the object file reader. 
 *
 *  The StringReader should be initialized first; if anything goes wrong
 *  creating the object file reader, we fall back on the string reader.
 */
function initOFReader(executable)
{
    var Model = xdc.useModule('xdc.rov.Model');

    /* Retrieve the class name of the binary parser to use */
    var binaryParser = Model.$private.recap.build.target.binaryParser;
   
    var ofReader;
    
    /* Make sure the target defines a binary parser. */
    if (binaryParser != undefined) {
        try {
            /* Parse the package name from the class name so we can load it. */
            var parserPackage = 
                binaryParser.substring(0, binaryParser.lastIndexOf('.'));
    
            /* Load the parser's package */
            xdc.loadPackage(parserPackage);
            
            /* Get the parser class */
            var binaryParserClass = Packages[binaryParser];
            
            /* Create an instance of the ofReader */
            ofReader = new binaryParserClass();
            
            /* Initialize the OFReader */
            ofReader.parse(executable);
            
            /* 
             * Close the reader to release the file handle. The reader will 
             * reopen the file when a string lookup occurs.
             */
            ofReader.close();   
        }
        /* 
         * If there was a problem creating the OFReader, use the 
         * StringReader instead. 
         */
        catch (e) {
            print("Caught an exception while initializing the object " +
                  "file reader:\n" + e);
            ofReader = Model.$private.strReader;
        }
    }
    /* 
     * If the target doesn't define an object file reader, use the
     * string reader. 
     */
    else {
        print("The target does not specify an object file reader; using the " +
              "dynamic string reader instead.");
        ofReader = Model.$private.strReader;
    }

    /* Store the object file reader in the Model. */
    Model.$private.ofReader = ofReader;
    
    /* Initialize the formatter's OFReader */
    xdc.jre.xdc.rta.Formatter.setOFReader(ofReader);
    
    return (ofReader);
}
 
/*
 *  ======== reset ========
 */
function reset()
{
    var Program = xdc.useModule('xdc.rov.Program');
    Program.resetMods();
    Program.$$bind('moduleNames', undefined);
    Program.$$bind('build', undefined);
    Program.$$bind('$modules', undefined);
    Program.$$bind('_decoder', undefined);
}

/*
 *  ======== getISymbolTableInst ========
 */
function getISymbolTableInst()
{
    return (this.$private.sym);
}

/*
 *  ======== getMemoryImageInst ========
 */
function getMemoryImageInst()
{
    return (this.$private.mem);
}

/*
 *  ======== getICallBackInst ========
 */
function getICallBackInst()
{
    return (this.$private.callBack);
}

/*
 *  ======== getIOFReaderInst ========
 */
function getIOFReaderInst()
{
    return (this.$private.ofReader);
}

/* 
 * ======== getModuleList ========
 * This function returns a JavaScript object representing the package
 * hierarchy and the modules, including the views they support.
 */
function getModuleList()
{
    var root = {name: "ModuleList", modules: [], subPkgs: []};
    root.children = new Array();
   
    var pkg = root;
    
    /* For each module in the system... */
    for (var i = 0; i < Program.moduleNames.length; i++) {
        
        /* Break the module name into packages */
        var names = Program.moduleNames[i].split(".");
        
        for (var j = 0; j < names.length; j++) {
            var fullName = getFullName(names, j);
            
            /* If this is a module... */
            if (j == (names.length - 1)) {
                var module = {};
                module.name = names[j];
                module.fullName = fullName;
                module.tabs = Program.getSupportedTabs(fullName);
                pkg.modules[pkg.modules.length] = module;
                continue;
            }
            
            /* If the package hasn't already been created */
            var index;
            if ((index = indexOfChild(pkg, fullName)) == -1) {
                var newPkg = {
                                name: names[j], 
                                fullName: fullName,
                                modules: [], 
                                subPkgs: []
                             };
                pkg.subPkgs[pkg.subPkgs.length] = newPkg;
                pkg = newPkg;
            }
            else {
                pkg = pkg.subPkgs[index];
            }
        }
        
        /* Start back from the root. */
        pkg = root;
    }        
    
    return (root);
}

/*
 *  ======== getFullName ========
 *  Takes the array of names created by splitting a module's name
 *  by the periods '.' and finds the package name referenced at
 *  the given index.
 *  For example, for the module xdc.runtime.HeapStd, index 1 will return 
 *  "xdc.runtime".
 */
function getFullName(names, index)
{
    var pkgName = "";
    for (var i = 0; i <= index; i++) {
        if (i == 0) {
            pkgName += names[i];
        }
        else {
            pkgName += "." + names[i];
        }
    }
    return (pkgName);
}

/*
 *  ======== indexOfChild ========
 */
function indexOfChild(pkg, name)
{
    for (var i = 0; i < pkg.subPkgs.length; i++) {
        if (pkg.subPkgs[i].fullName.equals(name)) {
            return (i);
        }
    }
    
    return (-1);
}

/*
 *  @(#) xdc.rov; 1, 0, 0,237; 2-22-2010 10:33:38; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

