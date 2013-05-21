/* --COPYRIGHT--,ESD
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * --/COPYRIGHT--*/
/*
 *  ======== Startup.xdc ========
 *
 *! Revision History
 *! ================
 *! 14-Dec-2007 sasha   moved comments from the internal section to
 *                      implemenation
 */

package xdc.runtime;

/*!
 *  ======== Startup ========
 *  The `xdc.runtime` startup bootstrap
 *
 *  Every module can optionally define a startup function which is called
 *  before `main()`.  Modules declare that they want to participate in this
 *  startup sequence via the `@ModuleStartup` attribute in the module's spec
 *  file.  Modules that use this attribute must also implement the following
 *  startup function:
 *  @p(code)
 *      Int Mod_Module_startup(Int state);
 *  @p
 *  where "Mod" is the name of the module requesting startup support.
 *
 *  The parameter to the startup function serves as "state variable" whose
 *  initial value will be `Startup_NOTDONE`. If `startup()` returns a value
 *  other than `Startup_DONE`, it will be called in a subsequent pass with this
 *  return value passed in as `state`.  To ensure this process terminates,
 *  no startup function is ever called more than `{@link #maxPasses}`
 *  times.
 *
 *  For situations in which the startup of one module depends upon another
 *  having completed its startup processing, the following function is
 *  automatically defined for all modules and proxies:
 *  @p(code)
 *      Bool Mod_Module_startupDone();
 *  @p
 *  where "Mod" is the name of some module or proxy.  These predicates can
 *  be used as guards inside of a startup function to probe whether a
 *  particular module has completed its own startup processing.  As a
 *  convenience, the function `Startup_rtsDone()` probes the necessary set of
 *  `xdc.runtime` modules required to support instance `create()` functions, and
 *  should be called before any startup-time instance creation and/or
 *  memory allocation is performed.
 *  @p(code)
 *      Int Mod_Module_startup(Int state)
 *      {
 *          if (!Startup_rtsDone()) {
 *              return (Startup_NOTDONE);
 *          }
 *              .
 *              .
 *              .
 *          return (Startup_DONE);
 *      }
 *  @p
 *
 *  @a(Startup Sequence)
 *  The following list defines when in the startup sequence the user provided
 *  startup functions are being invoked:
 *  @p(nlist)
 *   - CPU is initialized and C stack setup is performed.
 *   - Function specified by `Startup.resetFxn` is called.
 *     `Startup.resetFxn` is called only on platforms where reset is performed
 *     before running a program. For example, boot code for all TI targets
 *     invokes `Startup.resetFxn`, while that function is not invoked on
 *     Microsoft targets.
 *   - C runtime initialization is performed.
 *   - Functions from the array `Startup.firstFxns` are called.
 *   - All `Mod_Module_startup` functions are called in a loop until all such
 *     functions return `Startup_DONE` or `maxPasses` threshold is reached.
 *   - Functions from the array `Startup.lastFxns` are called.
 *   - The function `main` is called.
 *  @p
 *     The steps 4 - 6 occur during C++ static object initialization. Since
 *     the ANSI C++ Language Standard does not provide a means to control
 *     the order of C++ constructors, if a C++ constructor uses an XDC module,
 *     there is no guarantee that the module's startup function already ran.
 *     Therefore, any C++ constructor that needs XDC modules' services should
 *     call `Startup_exec` first to force all startup related functions from
 *     steps 4 - 6 to run, before the constructor uses any XDC module.
 *  @p
 *     Also, if a target does not support C++, the steps 4 - 6 will not run
 *     automatically. It is then up to a user's code to invoke `Startup_exec`,
 *     possibly as the first step in `main`.
 *  @p
 */
@Template("./Startup.xdt")

module Startup {

    /*!
     *  ======== DONE ========
     *  Returned from module startup functions no further calls are required
     */
    const Int DONE = -1;

    /*!
     *  ======== NOTDONE ========
     *  Initial value of state argument passed to module startup functions
     */
    const Int NOTDONE = 0;

    /*!
     *  ======== maxPasses ========
     *  Max number of iterations over the set of startup functions
     */
    config Int maxPasses = 32;
    
    /*!
     *  ======== InitFxn ========
     *  Type of function assignable to `firstFxns`, `lastFxns`, or `resetFxn`
     */
    typedef Void (*InitFxn)();
    
    /*!
     *  ======== firstFxns ========
     *  List of functions called before module startup
     *
     */
    config InitFxn firstFxns[length] = [];

    /*!
     *  ======== lastFxns ========
     *  List of functions called after module startup
     *
     */
    config InitFxn lastFxns[length] = [];

    /*!
     *  ======== resetFxn ========
     *  Function to be called by during initialization
     *
     *  This function is called only on platforms where reset is performed
     *  before running the program. The purpose of this function is to set up
     *  the hardware registers (cache, external memory interface, etc.) before
     *  any other code executes.
     *  
     */
    metaonly config InitFxn resetFxn = null;

    /*!
     *  ======== exec ========
     *  Execute the startup functions of all resident modules
     *
     *  Note that this function is idempotent, and can be called at any point
     *  in the platform/target startup sequence in which "ordinary" C functions
     *  can execute.  By default, this function is called as part of the
     *  standard C++ static initialization sequence.
     *
     *  If your target compiler does not support C++, this function must be
     *  called at least once prior to using any `xdc.runtime` modules.
     *  Simply call this function at the very beginning of `main()`.
     */
    Void exec();

    /*!
     *  ======== rtsDone ========
     *  Query the state of the `xdc.runtime` package
     *
     *  This function is used by module startup functions to determine
     *  when it is possible to use the `xdc.runtime` modules; e.g. to
     *  allocate memory, create instances managed by some module (even
     *  those outside the `xdc.runtime` package), call a `Log` function,
     *  etc.
     *
     *  @a(returns)     
     *  Returns `TRUE` when all `xdc.runtime` modules have completed
     *  initialization.
     */
    Bool rtsDone();

internal:

    /*!
     *  ======== reset ========
     *  Application-specific reset function
     *
     *  This function is defined in `Startup.xdt`
     *  (`xdc_runtime_Startup_reset__I`) and is called as early as
     *  possible in the program initialization process; for many platforms,
     *  it is called prior the the initialization of the C runtime
     *  environment.
     */
    Void reset();

    Void startMods(Int state[], Int len);
    readonly config Void (*startModsFxn)(Int[], Int) = startMods;

    extern Void execImplFxn() = xdc_runtime_Startup_exec__I;

    readonly config Void (*execImpl)() = execImplFxn;

    typedef Int (*SFxn)(Int);
    config SFxn sfxnTab[];
    
    /*!
     *  ======== sfxnRts ========
     *  Array of runtime modules' startup functions 
     *
     *  This array also contains startup functions of the modules that inherit
     *  from interfaces in `xdc.runtime`. Functions added to this array are
     *  called only once before the startup procedure for all modules begins.
     */
    config Bool sfxnRts[];

    struct Module_State {
        Int *stateTab;      /* initially null */
        Bool execFlag;	    /* if true, startup code processing started */
        Bool rtsDoneFlag;
    };

}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

