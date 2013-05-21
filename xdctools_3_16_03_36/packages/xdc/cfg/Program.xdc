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
 *  ======== Program.xdc ========
 */
package xdc.cfg;

/*!
 *  ======== Program ========
 *  The Program object for the configuration object model.
 *
 *  This module defines the "root" of the configuration object model; all
 *  configuration settings are for the executable represented by this
 *  object. Program configuration scripts reference this module via the
 *  global variable `Program`; i.e., `Program` implicitly initialized as
 *  follows:
 *  @p(code)
 *      var Program = xdc.useModule('xdc.cfg.Program');
 *  @p
 *
 *  After a configuration script completes successfully, the XDC runtime
 *  generates the following files:
 *  @p(nlist)
 *	- package/cfg/<exe_name>.c
 *	- package/cfg/<exe_name>.xdl
 *  @p
 *  where `<exe_name>` is the name of the executable with the final '.'
 *  character replaced with an '_'.
 *
 *  The generated C file contains code and data from each module used by the
 *  program and must be compiled and linked with the other sources to
 *  produce the final executable.
 *
 *  The generated linker command file must also be used during this final
 *  link step.  This linker command file is produced by expanding a template
 *  specified by `{@link xdc.cfg.Program#linkTemplate}`.
 *  Each template is responsible for expanding templates specified by each
 *  imported package's `getSects` method (see `{@link xdc.IPackage#getSects}`).
 *  This allows each package participating in the configuration of an
 *  executable to contribute a portion of the executable's linker command file.
 */

@Template("./Program.xdt")

metaonly module Program {

    /*!
     *  ======== GenerationOptions ========
     *  Options that control the files generated as part of program
     *  configuration.
     *
     *  @field(debuggerFiles) If set to `true` in a configuration script,
     *		debugger project files will be generated as part of the
     *		configuration step.  If set to `false`, these files will not 
     *		be generated.
     *
     *		If it is not set (or set to undefined) and the environment
     *		variable `environment["xdc.cfg.gen.debuggerFiles"]` is
     *		non-`null`, then the default value of this parameter is taken
     *		to be the value	of the following expression:
     *		@p(code)
     *		    environment["xdc.cfg.gen.debuggerFiles"] == "true"
     *		@p
     *		This makes it is possible to enable the generation of
     *		debugger project files from build scripts by passing
     *		the option `-Dxdc.cfg.gen.debuggerFiles=true` to the
     *		configuration tool (see
     *		`{@link xdc.bld.Executable#Attrs.xsopts}` or
     *          `{@link xdc.bld.PackageContents#Attrs.xsopts}`).
     *
     *		Finally, if `debuggerFiles` is not set (or set to `undefined`)
     *		and the environment variable above is not defined,
     *		the generation of debugger project files occurs only if
     *		`{@link xdc.cfg.Program#build.profile}` contains
     *          the string `"debug"`.  So, unless otherwise specified, debug
     *		profiles result in debugger project files being generated.
     */
    struct GenerationOptions {
        Bool debuggerFiles; /*! if `true`, generate debugger "project" files */
    };

    /*!
     *  ======== SectionSpec ========
     *  Map that instructs the linker where to place output sections.
     *
     *  This structure contains some fields that are specific to TI targets.
     *  On non-TI targets, such fields are ignored.
     *
     *  @field(runSegment) Defines the memory segment where the section is
     *		to be run.
     *  
     *  @field(loadSegment) Defines the memory segment where the section is
     *		to be loaded. If 'runSegment' or 'loadSegment' is defined,
     *          but not both, the linker is instructed to use the defined
     *          field as the load and run allocation for the section. 
     *
     *  @field(runAddress) Defines the memory address where the section is
     *		to be run. It is an error if both 'runSegment' and 'runAddress'
     *		are specified.
     *  
     *  @field(loadAddress) Defines the memory address where the section is
     *		to be loaded. It is an error if both 'loadSegment' and
     *		'loadAddress' are specified. If 'runAddress' or 'loadAddress'
     *          is defined, but not both, the linker is instructed to use the
     *          defined field as the load and run address for the section.
     *
     *  @field(runAlign) If runSegment is specified, runAlign determines the
     *		alignment. It is an error if both 'runAlign' and 'runAddress'
     *		are specified.
     *  
     *  @field(loadAlign) If runSegment is specified, runAlign determins the
     *		alignment. It is an error if both 'loadAlign' and 'loadAddress'
     *		are specified.
     *
     *  @field(type) Defines flags for special section types (COPY, DSECT,
     *		NOLOAD).
     *
     *  @field(fill) Defines the value to initialize an uninitialized
     *  section.
     */
    struct SectionSpec {
        String runSegment;  /*! segment where section contents are run */
        String loadSegment; /*! segment where section contents are loaded */
        UInt runAddress;    /*! start address of section when run */
        UInt loadAddress;   /*! start address of section when loaded */
        UInt runAlign;      /*! alignment of section within runSegment */
        UInt loadAlign;     /*! alignment of section within loadSegment */
        String type;        /*! target-specific flags */
        UInt fill;	    /*! fill value */
    };

    /*!
     *  ======== gen ========
     *  Generation options for this executable
     *
     *  This configuration parameter allows the program configuration script
     *  to control (to some extent) what files are generated as part of the
     *  configuration process.
     */
    config GenerationOptions gen;
    
    /*!
     *  ======== globalSection ========
     *  UNDER CONSTRUCTION
     *  @_nodoc
     *
     *  Section where `{@link #globals}` are placed.
     *
     *  All globals specified in the application configuration file
     *  are placed into this section.
     *
     *  The default is `null`, which means the `{@link #dataSection}` is used.
     */
    config String globalSection = null;

    /*!
     *  ======== sysStack ========
     *  The size of the executable's initial system stack
     *
     *  On platforms that support a separate "system stack", this
     *  parameter sets its initial size (in units of chars).
     */
    config UInt sysStack = 0x1000;

    /*!
     *  ======== stack ========
     *  The size of the executable's initial stack
     *
     *  On platforms that enable control of the initial stack size (the
     *  stack that exists immediately after reset), this parameter specifies
     *  its initial size (in units of chars).
     */
    config UInt stack = 0x1000;

    /*!
     *  ======== heap ========
     *  The size of the executable's initial heap
     *
     *  On platforms that enable control of the size of the heap managed by
     *  the run-time support function malloc(), this parameter specifies
     *  its initial size (in units of chars).
     */
    config UInt heap = 0x1000;

    /*!
     *  ======== argSize ========
     *  The size allocated for command line args to the executable
     *
     *  On platforms that require static allocation of space to hold
     *  command line arguments, this parameter specifies its maximum size
     *  (in units of chars).
     */
    config UInt argSize = 0x200;

    /*!
     *  ======== execCmd ========
     *  The command used to run this executable
     *
     *  If it is not set by the configuration script, it is set by the
     *  program's platform package (during program configuration).
     *
     *  This command is run as follows:
     *  @p(code)
     *      execCmd <prog> <args>
     *  @p
     *  where, `<prog>` is the name of the executable
     *
     *  @a(Note)
     *  This parameter is ignored if the exec command is specified as part
     *  of the test; see `{@link xdc.bld.Test#Attrs}`.
     *  and `<args>` are the arguments specified in the test (if any).
     */
    config String execCmd;

    /*!
     *  ======== linkTemplate ========
     *  The template for the Program's linker command file
     *
     *  A template is used to create the linker command file for each
     *  program.  It can be optionally specified by setting this
     *  configuration parameter in the program's configuration script.  If
     *  `linkTemplate` it is not set or set to `null`, the template is
     *  obtained from the platform associated with this program (i.e., the
     *  platform named by the `{@link #platform}` config in this module).
     *  See `{@link xdc.platform.IPlatform#getLinkTemplate IPlatform.getLinkTemplate}`.
     *
     *  The `linkTemplate` string names a package path relative path; e.g.,
     *  if the linker template you want to specify is
     *  `"templates/big_n_hairy.xdt"` in the package `myCompany.myPackage`,
     *  `linkTemplate` should be set to:
     *  @p(code)
     *      "myCompany/myPackage/templates/big_n_hairy.xdt"
     *  @p
     *  If `linkTemplate` begins with the string `"./"`, the file is NOT
     *  searched for along the package path; instead the file name is taken
     *  to specify a file relative to the current working directory.
     *
     *  In any case, if `linkTemplate` is non-`null`, the file must exist; 
     *  otherwise, the configuration step will fail.
     */
    config String linkTemplate = null;
    
    /*!
     *  ======== main ========
     *  The main entry point for the program
     *
     *  This parameter is optionally set by the user's program
     *  configuration script.  If it is not set, then a "legacy" `main()`
     *  function is assumed to be linked into the program; otherwise,
     *  the value of `main` is used as the "main" entry point to the
     *  program.
     */
    config Int (*main)(Int, Char*[]);

    /*!
     *  ======== sectMap ========
     *  A section name to SectionSpec mapping
     *
     *  This is a program specific mapping of output section names to
     *  {@link #SectionSpec} objects. The map supports mapping of section
     *  names to memory names; see {@link xdc.platform.IPlatform#sectMap}.
     *
     *  This parameter enables program configurations to place named
     *  sections in platform specific memory regions.  During generation of
     *  the linker command file, sections are mapped to named memories by
     *  first consulting this table; if the table does not contain a mapping,
     *  the target classifies each section as either "code", "data" or
     *  "stack" {@link xdc.bld.ITarget#sectMap} and the platform defines a
     *  memory region for each of these section types
     *  ({@link xdc.platform.IPlatform#codeMemory}/
     *  {@link xdc.platform.IPlatform#dataMemory}).  If
     *  this does not produce a result, an error is generated.
     *  It is important to note that `sectMap` does not contain the complete
     *  section allocation for the program. It only contains the entries
     *  explicitly added to `sectMap`. To get the complete section
     *  allocation, a user should call {@link #getSectMap}.
     *
     *  Suppose for example that the platform defines a memory segment
     *  named "DDR2".  The following configuration statement places
     *  everything from the ".text" section into the "DDR2" segment.
     *
     *  @p(code)
     *      Program.sectMap[".text"] = new prog.SectionSpec();
     *      Program.sectMap[".text"].runSegment = "DDR2";
     *  @p
     *
     *  @a(Note)
     *  If BIOS 5 configuration script (Tconf script) is executed, the
     *  section allocations configured in the Tconf script take precedence
     *  over any settings for the same sections in this parameter.
     *
     *  @see #SectionSpec
     *  @see xdc.platform.IPlatform#sectMap
     *  @see xdc.bld.ITarget#sectMap
     */
    config Any sectMap[string];	/* section name => SectionSpec */

    /*!
     *  ======== system ========
     *  @_nodoc
     *  A facade for the {@link xdc.runtime.System#SupportProxy} parameter
     *
     *  The program configuration script may select an implementation of
     *  the `xdc.runtime.ISystemSupport` interface and "bind" it by setting
     *  this parameter. If the module assigned to this parameter does not
     *  inherit from `xdc.runtime.ISystemSupport`, the configuration will fail.
     *
     *  If this parameter is not set (or set to `undefined`), then a default
     *  implementation is used: `xdc.runtime.SysStd` or, if
     *  `Program.build.target.os` is `null`, `xdc.runtime.SysMin`.  Recall that
     *  `Program.build.target.os` is specified in the Build Object Model;
     *  `Program.build.target` is the target specified when the executable was
     *  added to the package.
     *
     *  If this parameter is set to `null`, then the `System` module is not
     *  linked into the application (unless 'Memory' is used); any references
     *  to `System`'s methods will result in a linker error.  By setting this
     *  parameter to `null`, one is asserting that `System`'s methods will not 
     *  be used.
     */
    config Any system;

    /*!
     *  ======== name ========
     *  The name of the executable file
     *
     *  This is the full file name (relative to the package's base) of the
     *  executable that results from this configuration.
     *
     *  @a(readonly)
     *  This parameter is set by the generated program configuration script
     *  and must not be modified.
     */
    config String name;

    /*!
     *  ======== buildPackage ========
     *  The name of the executable's package
     *
     *  This is the full package name (relative to the package's repository)
     *  of the package that contains the executable being configured.
     *
     *  @a(readonly)
     *  This parameter is set by the generated program configuration script
     *  and must not be modified.
     */
    config String buildPackage;

    /*!
     *  ======== endian ========
     *  The endianess of the executable
     *
     *  This parameter is an alias for `build.target.model.dataModel` and is
     *  set to one of the following values: `"big"`, `"little"`, or `null`.
     *
     *  @a(readonly)
     *  This parameter is set by the generated program configuration script
     *  and must not be modified.
     */
    config String endian = null;

    /*!
     *  ======== codeModel ========
     *  The memory model for code
     *
     *  This parameter is an alias for `build.target.model.codeModel` and is
     *  set to one of the following target-specific values: `"near"`, `"far"`,
     *  `"large"`, or `null`.
     *
     *  @a(readonly)
     *  This parameter is set by the generated program configuration script
     *  and must not be modified.
     */
    config String codeModel = null;

    /*!
     *  ======== dataModel ========
     *  The memory model for data
     *
     *  This parameter is an alias for `build.target.model.dataModel` and is
     *  set to one of the following target-specific values: `"near"`, `"far"`,
     *  `"large"`, or `null`.
     *
     *  @a(readonly)
     *  This parameter is set by the generated program configuration script
     *  and must not be modified.
     */
    config String dataModel = null;

    /*!
     *  ======== build ========
     *  This program's build attributes
     *
     *  This parameter allows arbitrary build attributes to be carried
     *  forward from the Build Object Model (BOM) into the configuration
     *  model for program configuration scripts to read.
     *
     *  Conceptually, this config parameter should be declared as follows:
     *  @p(code)
     *      struct BuildAttrs inherits xdc.bld.Executable.Attrs {
     *          config xdc.bld.ITarget.Module target;
     *      };
     *  @p
     *  All parameters of the target associated with the executable being
     *  configured are available through '`Program.build.target`'. Any config
     *  parameter set in the BOM's `{@link xdc.bld.Executable#attrs}` is also
     *  available through `{@link #build}`.  For example, the name of the
     *  target is `Program.build.target.name` and the name of the
     *  executable's configuration script is `Program.build.cfgScript`.
     *
     *  @a(readonly)
     *  This parameter is set by the generated program configuration script
     *  and must not be modified.
     */
    config Any build;	/*  BuildAttrs */
    
    /*!
     *  ======== cpu ========
     *  The execution context "seen" by the executable.
     *
     *  Since the execution context is largely determined by the CPU that
     *  runs the executable, this configuration parameter allows scripts with
     *  access to the program object to conditionally configure based on CPU
     *  characteristics (e.g., ISA or revision of a chip).
     *
     *  @a(readonly)
     *  This parameter is set by the platform's implementation of
     *  `xdc.IPackage` (i.e., `package.xs`).
     */
    config xdc.platform.IExeContext.Instance cpu;

    /*!
     *  ======== platformName ========
     *  The name of the executable's platform
     *
     *  This field is the name of the platform instance used to create the
     *  executable; e.g., `"ti.platforms.sim55xx"`, or
     *  `"ti.platforms.sim6xxx:TMS320C6416"`.
     *
     *  Platform instance names have the form:
     *  @p(code)
     *      <platform_pkg>:<instance_id>
     *  @p
     *  where `<platform_pkg>` is the name of the platform package 
     *  responsible for creating the platform instance and the optional
     *  "`:<instance_id>`" is a suffix that uniquely identifies the creation
     *  parameters for this instance.
     *
     *  The creation parameters are the values specified by the map
     *  `{@link xdc.bld.BuildEnvironment#platformTable}`;
     *  if this map does not contain the platform instance name, the
     *  instance is created with default values that are specific to the
     *  platform.
     *
     *  @a(readonly)
     *  This parameter is set by the generated program configuration script
     *  and must not be modified.
     */
    config String platformName;

    /*!
     *  ======== platform ========
     *  The executable's platform instance object
     *
     *  The platform instance that provided an execution context for the
     *  executable being configured.
     *
     *  @a(readonly)
     *  This parameter is set by the generated program configuration script
     *  and must not be modified.
     */
    config xdc.platform.IPlatform.Instance platform;

    /*!
     *  ======== global ========
     *  Global variable declarations
     *
     *  Assignments to this hash table become global symbols that can be
     *  used to directly reference objects.  These objects are declared
     *  in a generated header that is indirectly included by the header
     *  `xdc/cfg/global.h`.
     *
     *  Configuration scripts define symbols by adding new properties to
     *  `global`.
     *  @p(code)
     *      Program.global.myInstance = Mod.create();
     *      Program.global.myString = "hello world";
     *  @p
     *
     *  Programs can reference the symbols defined in `global` by including
     *  the C/C++ header `xdc/cfg/global.h` as follows:
     *  @p(code)
     *      #include <pkg/Mod.h>
     *      #include <xdc/cfg/global.h>
     *         :
     *      Mod_fxn(myInstance, ...);
     *      printf("greetings: %s\n", myString);
     *  @p
     *
     *  To compile sources that include `xdc/cfg/global.h`, one symbol must be
     *  defined before including this header:
     *  @p(dlist)
     *      - `xdc_cfg__header__`
     *          the package qualified name of the executable-specific C/C++
     *          header generated by the program configuration tool; e.g.,
     *          `local/examples/package/cfg/mycfg_x62.h`.
     *  @p
     *  For example, to compile sources that reference the values declared in
     *  `{@link #global}` for a TI C6x target with a generated
     *  configuration header named `package/cfg/mycfg_x62.h` in a package
     *  named `local.examples` the following command line is sufficient:
     *  @p(code)
     *      cl6x -Dxdc_cfg__header__=local/examples/package/cfg/mycfg_x62.h ...
     *  @p
     *
     *  The `xdc_cfg__header__` symbol is automatically defined when you use
     *  the the XDC Build Engine (`{@link xdc.bld}`) to create executables; see
     *  `{@link xdc.bld.Executable#addObjects}`
     *
     *  @see xdc.bld.Executable#addObjects
     */
    config Any global[string];

    /*!
     *  ======== symbol ========
     *  UNDER CONSTRUCTION
     *  @_nodoc
     *
     *  global symbol specifications
     */
    config Any symbol[string];

    /*!
     *  ======== fixedCodeAddr ========
     *  UNDER CONSTRUCTION
     *  @_nodoc
     *
     *  fixed location of code for ROM assemblies
     */
    config UInt fixedCodeAddr = 0;

    /*!
     *  ======== fixedDataAddr ========
     *  UNDER CONSTRUCTION
     *  @_nodoc
     *
     *  fixed location of data for ROM assemblies
     */
    config UInt fixedDataAddr = 0;

    /*!
     *  ======== loadFixedDataAddr ========
     *  UNDER CONSTRUCTION
     *  @_nodoc
     *
     *  Load location of fixed data accessed from ROM assemblies
     *
     *  If an application that imports ROM assemblies cannot load data
     *  accessed from ROM to a runtime address, this address specifies the
     *  load address. The load address is specified when the application is
     *  configured. The runtime address for the data is specified at the
     *  time a ROM assembly is built, using `fixedDataAddr`.
     */
    config UInt loadFixedDataAddr;

    /*!
     *  ======== loadRom ========
     *  UNDER CONSTRUCTION
     *  @_nodoc
     *
     *  Control generation of 'type = DSECT' for ROM assemblies.
     *
     *  When there is no actual ROM on the target, for debugging purposes,
     *  we may need to load ROM sections to the target. If this parameter is
     *  set to `true`, the linker command file will allocate ROM sections in
     *  the same way as other sections.  
     */
    config Bool loadRom = false;

    /*!
     *  ======== exportModule ========
     *  Force all the symbols of a module to be part of a configuration
     *
     *  Although a call xdc.useModule() will force some of a module's methods
     *  to be part of a configuration, the linker is still free to omit any
     *  symbols that are not referenced.  Use of exportModule will force all
     *  methods of the specified module to be available.
     */
    Void exportModule(String modName);

    /*!
     *  ======== freezeRomConfig ========
     *  UNDER CONSTRUCTION
     *  @_nodoc
     */
    Void freezeRomConfig(String modName, String cfgName);

    /*!
     *  ======== freezeRomParams ========
     *  UNDER CONSTRUCTION
     *  @_nodoc
     */
    Void freezeRomParams( String modName );

    /*!
     *  ======== frozenRomConfig ========
     *  UNDER CONSTRUCTION
     *  @_nodoc
     */
    Bool frozenRomConfig( String modName, String cfgName );

    /*!
     *  ======== getSectMap ========
     *  Return the complete mapping of section names to `{@link #SectionSpec}`
     *  entries
     *
     *	The returned map is assembled from `{@link xdc.bld.ITarget#sectMap}`,
     *  `{@link xdc.platform.IPlatform#sectMap}`,
     *  `{@link xdc.platform.IPlatform#codeMemory}`,
     *  `{@link xdc.platform.IPlatform#dataMemory}`,
     *  `{@link xdc.platform.IPlatform#stackMemory}` and `{@link #sectMap}`.
     *  The function can be called at any time during configuration, but if
     *  it is called before all packages had a chance to change `sectMap`,
     *  the returned map may not correspond to the actual section
     *  allocation as configured in the linker command file.
     *
     *  @a(returns)
     *  `getSectMap` returns a map with section names as keys and
     *	`{@link #SectionSpec}` entries as values.
     *
     *  @a(Note)
     *  If BIOS 5 configuration script (Tconf script) is executed, the
     *  section allocations configured in the Tconf script are also being
     *  returned.
     */
    function getSectMap();

    /*!
     *  ======== importAssembly ========
     *  UNDER CONSTRUCTION
     *  @_nodoc
     */
    Void importAssembly(String asmName);

    /*!
     *  ======== importRomAssembly ========
     *  UNDER CONSTRUCTION
     *  @_nodoc
     */
    Void importRomAssembly(String romAsmName);

    /*!
     *  ======== patchRomFxn ========
     *  UNDER CONSTRUCTION
     *  @_nodoc
     */
    Void patchRomFxn(String modName, String fxnName, String patchSym);

    /*!
     *  ======== targetModules ========
     *  UNDER CONSTRUCTION
     *  @_nodoc
     *
     *  This function returns a list of target modules. The list is completed
     *  only after all packages are closed, and runtime.finalized() is closed,
     *  so the only time when this function can be safely called is from
     *  within module$static$init and instance$static$init functions, package
     *  validate() functions, and templates.
     */
    function targetModules();

}
/*
 *  @(#) xdc.cfg; 1, 0, 2, 0,237; 2-22-2010 10:33:11; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

