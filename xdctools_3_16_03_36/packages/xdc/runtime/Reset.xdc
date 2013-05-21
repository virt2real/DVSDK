/*!
 *  ======== Reset ========
 *  Startup reset function manager
 *
 *  This module defines the initial reset function and can be used without
 *  requiring any other `xdc.runtime` module.  The reset function is called
 *  as early as possible in the application startup and is intended for
 *  platform-specific hardware initialization.
 *
 *  @a(Warning)
 *  The reset function is _not_ supported on all platforms and, as a result,
 *  you should never place any "portable" code that is required for your
 *  application in this function.  Use the `@{link Startup}` module to
 *  define required application startup functions.
 *  
 *  @see Startup
 */
@Template("xdc/runtime/Reset.xdt")
metaonly module Reset
{
    /*!
     *  ======== fxns ========
     *  List of functions to call at reset
     *
     *  This array defines the functions that will be executed by the reset
     *  initialization function (`xdc_runtime_Startup_reset__I`) _in addition
     *  to_ the function specified by `@{link Startup#resetFxn}`.
     *
     *  The following code fragment shows how to add the externally defined
     *  function `myReset()` to this array.
     *  @p(code)
     *      var Reset = xdc.useModule("xdc.runtime.Reset");
     *      Reset.fxns[Reset.fxns.length++] = "&myReset";
     *  @p
     *
     *  @a(Warning)
     *  Although the functions specified in `fxns[]` are ordinary C functions,
     *  they are often called _before_ the C runtime is fully initialized;
     *  e.g., they may be called _before_ static variables are initialized.
     *  Reset functions should only assume that a minimal execution stack has
     *  initialized.
     *
     *  @see Startup.resetFxn
     */
    metaonly config xdc.runtime.Startup.InitFxn fxns[] = [];
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

