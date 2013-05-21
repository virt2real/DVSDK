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
 *  ======== Error.xdc ========
 *
 *! Revision History
 *! ================
 *! 11-Mar-2008 agd	started revision history and clarified a few things
 */

/*!
 *  ======== Error ========
 *  Runtime error manager
 *
 *  The `Error` module provides mechanisms for raising, checking, and
 *  handling errors in a program. You can configure it via the
 *  `{@link Error#policy Error.policy}` and
 *  `{@link Error#raiseHook Error.raiseHook}` configuration parameters.
 *
 *  Modules may define specific error types and reference these when
 *  raising an error. Each error type has a custom error message and
 *  can be parameterized with up to `{@link #NUMARGS}` arguments. A
 *  generic error type is provided for raising errors when not in a module.
 *
 *  Use the `{@link #check Error_check()}` function to determine if an
 *  error has been raised. It is important to understand that it is the
 *  caller's responsibility to check the error block after calling a
 *  function that takes an error block as an argument. Otherwise, a raised
 *  error may go undetected, which could compromise the integrity of the
 *  system. For example:
 *
 *  @p(code)
 *  Task_create(..., &eb);
 *
 *  if (Error_check(&eb)) {
 *      ...an error has been raised...
 *  }
 *  @p
 *
 *  The `{@link #raiseHook Error.raiseHook}` configuration parameter allows
 *  a configured function to be invoked when any error is raised. This
 *  function is passed a pointer to the error's error block and makes it
 *  easy to manage all errors from a common point. For example, you can
 *  trap any error (fatal or not) by simply setting a breakpoint in this
 *  function. You can use the following functions to extract information
 *  from an error block.
 *
 *  @p(blist)
 *  - `{@link #getData Error_getData()}`
 *  - `{@link #getCode Error_getCode()}`
 *  - `{@link #getId Error_getId()}`
 *  - `{@link #getMsg Error_getMsg()}`
 *  - `{@link #getSite Error_getSite()}`
 *  @p
 *  
 *  @a(Examples)
 *  Example 1: The following example shows how a module, named ModA,
 *  defines a custom error type and shows how this error is raised by
 *  the module. The module defines an `Id` of `E_notEven` in its module
 *  specification file (in this case, `ModA.xdc`). The error's message
 *  string takes only one argument. The module also defines a `mayFail()`
 *  function that takes an error block. In the module's C source file,
 *  the function checks for the error condition and raises the error if
 *  needed.
 *  
 *  This is part of ModA's XDC specification file for the module:
 *
 *  @p(code)
 *  config xdc.runtime.Error.Id E_notEven = {
 *      msg: "expected an even number (%d)"
 *  };
 *
 *  Void mayFail(Int x, xdc.runtime.Error.Block *eb);
 *  @p
 *
 *  This is part of the C code for the module:
 *
 *  @p(code)
 *  Void ModA_mayFail(Int x, Error_Block *eb)
 *  {
 *      if ((x % 2) != 0) {
 *          Error_raise(eb, ModA_E_notEven, x, 0);
 *          ...add error handling code here...
 *          return;
 *      }
 *      ...
 *  }
 *  @p
 *
 *  @p(html)
 *  <hr />
 *  @p
 *
 *  Example 2: The following C code supplies an error block to a function
 *  that requires one and tests the error block to see if the function
 *  raised an error. Note that an error block must be initialized before
 *  it can be used and same error block may be passed to several functions.
 *
 *  @p(code)
 *  #include <xdc/runtime/Error.h>
 *  #include <ti/sysbios/knl/Task.h>
 *  Error_Block eb;
 *  Task_Handle tsk;
 *
 *  Error_init(&eb);
 *  tsk = Task_create(..., &eb);
 *
 *  if (Error_check(&eb)) {
 *      ...an error has been raised...
 *  }
 *  @p
 *
 *  @p(html)
 *  <hr />
 *  @p
 *
 *  Example 3: The following C code shows that you may pass `NULL` to a
 *  function requiring an error block. In this case, if the function
 *  raises an error, the program is aborted (via
 *  `{@link System#abort xdc_runtime_System_abort()}`), thus execution
 *  control will never return to the caller.
 *
 *  @p(code)
 *  #include <xdc/runtime/Error.h>
 *  #include <ti/sysbios/knl/Task.h>
 *
 *  tsk = Task_create(..., NULL);
 *  ...will never get here if an error was raised in Task_create...
 *  @p
 *
 *  @p(html)
 *  <hr />
 *  @p
 *
 *  Example 4: The following C code shows how to write a function that
 *  is not part of a module and that takes an error block and raises
 *  the generic error type provided by the Error module. Note, if the
 *  caller passes `NULL` for the error block or if the error policy is
 *  `{@link #Policy TERMINATE}`, then the call to
 *  `{@link #raise Error_raise()}` will call
 *  `{@link System#abort xdc_runtime_System_abort()}` and never return.
 *
 *  @p(code)
 *  #include <xdc/runtime/Error.h>
 *
 *  Void myFunc(..., Error_Block *eb)
 *  {
 *      ...
 *
 *      if (...error condition detected...) {
 *          String  myErrorMsg = "my custom error message";
 *          Error_raise(eb, Error_E_generic, myErrorMsg, 0);
 *          ...add error handling code here...
 *          return;
 *      }
 *  }
 *  @p
 */

module Error {

    /*!
     *  ======== Policy ========
     *  Error handling policies
     *
     *  Regardless of the current policy in use, raising an error by
     *  calling `{@link #raise Error_raise}` will always invoke the
     *  error raise hook function assigned to the
     *  `{@link #raiseHook Error.raiseHook}` configuration parameter.
     *
     *  @field(TERMINATE) All raised errors are fatal. A call to
     *  `{@link #raise Error_raise}` will never return to the caller.
     *
     *  @field(UNWIND) Errors are returned to the caller. A call to
     *  `{@link #raise Error_raise}` will return back to the caller.
     */
    enum Policy {
        TERMINATE,
        UNWIND
    };

    /*!
     *  ======== Desc ========
     *  Error descriptor
     *
     *  Each type of error is defined with an error descriptor. This
     *  structure groups common information about the errors of this type.
     *
     *  @field(msg) The error message using a `printf` style format string, 
     *		    but limited to `{@link #NUMARGS}` arguments.
     *              This format string together with the two arguments passed
     *              to `Error_raise`` are used to create a human readable
     *              error message.
     *
     *  @field(code) A user assignable code, 0 by default. The user may
     *              optionally set this field during config to give the
     *              error a well-known numeric code. 
     */
    metaonly struct Desc {
        String msg;
        UInt16 code;
    };

    /*!
     *  ======== Id ========
     *  Error identifier
     *
     *  Each type of error raised is defined with a metaonly
     *  `{@link Error#Desc}`.
     *  An `Error_Id` is a 32-bit target value that encodes the information
     *  in the `Desc`.  Target programs use `Error_Id` values to "raise" and
     *  check for specific errors.
     *
     *  @a(Warning) `{@link #Id}` values may vary among different
     *  configurations of an application.  For example, the addition of a
     *  new module to a program may result in a different absolute value for
     *  `{@link #E_generic}`.  If you need error numbers that remain
     *  invariant, use the user definable `{@link #Desc Desc.code}` field.
     */
    @Encoded typedef Desc Id;
    
    /*!
     *  ======== NUMARGS ========
     *  Maximum number of arguments supported by an error.
     */
    const Int NUMARGS = 2;

    /*!
     *  ======== Data ========
     *  Error args
     *
     *  The two arguments (arg1, arg2) passed to `{@link #raise}` are 
     *  stored in one of these arrays within the associated Error_Block.
     *  To access these arguments use `{@link #getData}` to obtain a 
     *  pointer to the Error_Block's Data array.
     *
     *  @see #getData
     */
    struct Data {
        IArg arg[NUMARGS];
    }

    /*!
     *  ======== Block ========
     *  Error block
     *
     *  An opaque structure used to store information about errors once raised.
     *  This structure must be initialized via `{@link #init Error_init()}`
     *  before being used for the first time.
     */
    @Opaque struct Block {
        UInt16      unused;     /* for backward compatibility (was code) */
        Data        data;       /* arguments passed to raise() */
        Id          id;         /* id passed to raise() */
        String      msg;        /* msg associated with id */
        Types.Site  site;       /* info about Error_raise call site */
        IArg        xtra[4];    /* future expansion */
    };

    /*!
     *  ======== E_generic ========
     *  Generic error
     */
    config Id E_generic = {msg: "generic error: %s"}; 

    /*!
     *  ======== E_memory ========
     *  Out of memory error
     */
    config Id E_memory = {msg: "out of memory: heap=0x%x, size=%u"}; 

    /*!
     *  ======== policy ========
     *  System-wide error handling policy
     */
    config Policy policy = UNWIND;

    /*!
     *  ======== raiseHook ========
     *  The function to call whenever an error is raised
     *
     *  This function is always called when an error is raised, even if the
     *  Error policy is `{@link #Policy TERMINATE}`.  In rare cases it is
     *  possible that a raised error does not trigger a call to `raiseHook`;
     *  see `{@link #maxDepth}`.
     *
     *  @param(eb) non-`NULL` pointer to an `Error_Block`
     *
     *      Even if the client passes a `NULL` error block pointer, this
     *      parameter is always `non-NULL`.
     *
     *  @see #maxDepth
     */
    config Void (*raiseHook)(Block *) = Error.print;

    /*!
     *  ======== maxDepth ========
     *  Maximum number of concurrent calls to `{@link #raiseHook}`
     *
     *  To prevent errors that occur in the raiseHook function from
     *  causing an infinite recursion, the maximum number of concurrent
     *  calls to `{@link #raiseHook}` is limited by `Error_maxDepth`.  If
     *  the number of concurrent calls exceeds `Error_maxDepth`, the
     *  `raiseHook` function is not called.
     *
     *  In multi-threaded systems, errors raised by separate threads may
     *  be detected as recursive calls to `raiseHook`.  So, setting
     *  `Error.maxDepth` to a small value may - in rare instances - result in
     *  `errorHook` not being called for some raised errors.
     *
     *  If it is important that all raised errors trigger a call to the
     *  `raiseHook` function, set `Error.maxDepth` to an impossibly large
     *  number (0xffff) and either ensure that the raise hook never calls a
     *  function that can raise an error or add checks in `raiseHook` to
     *  protect against "double faults".
     */
    config UInt16 maxDepth = 16;
    
    /*!
     *  ======== check ========
     *  Return TRUE if an error was raised
     *
     *  @param(eb) pointer to an `Error_Block` or `NULL`
     *
     *  @a(returns)
     *  If `eb` is non-`NULL` and `{@link #policy Error.policy} == UNWIND` and
     *  an error was raised on `eb`, this function returns `TRUE`.  Otherwise,
     *  it returns `FALSE`.
     */
    Bool check(Block *eb);

    /*!
     *  ======== getData ========
     *  Get an error's argument list
     *
     *  @param(eb)      non-`NULL` pointer to an `Error_Block`
     *
     *  @a(returns)
     *  `getData` returns an array of type `{@link #Data}` with
     *  `{@link #NUMARGS}` elements containing the arguments provided
     *  at the time the error was raised.
     *
     *  @see #raise
     */
    Data *getData(Block *eb);

    /*!
     *  ======== getCode ========
     *  Get an error's code
     *
     *  @param(eb) non-`NULL` pointer to an `Error_Block`
     *
     *  @a(returns)
     *  `getCode` returns the error code associated with this error block.
     *
     *  @see #raise
     *  @see #Desc
     */
    UInt16 getCode(Block *eb);

    /*!
     *  ======== getId ========
     *  Get an error's id
     *
     *  @param(eb) non-`NULL` pointer to an `Error_Block`
     *
     *  @a(Warning)
     *  `Error_Id` values may vary among different configurations
     *  of an application.  For example, the addition of a new module to a
     *  program may result in a different absolute value for
     *  `{@link #E_generic}`.  If you need error numbers that remain
     *  invariant, use the user definable `{@link #Desc Desc.code}` field.
     *
     *  @see #raise
     *  @see #Desc
     */
    Id getId(Block *eb);

    /*!
     *  ======== getMsg ========
     *  Get an error's "printf" format string
     *
     *  @param(eb) non-`NULL` pointer to an `Error_Block`
     *
     *  @see #raise
     *  @see #Desc
     */
    String getMsg(Block *eb);

    /*!
     *  ======== getSite ========
     *  Get an error's call site info
     *
     *  @param(eb) non-`NULL` pointer to an `Error_Block`
     *
     *  @a(returns)
     *  `getSite` returns a pointer to an initialized
     *  `{@link Types#Site Types.Site}` structure.  However, in the
     *  event that the call site was compiled with `xdc_FILE` defined to
     *  be `NULL` (to minimize string space overhead) the `file`
     *  field may be set to `NULL`.
     *
     *  @see #raise
     *  @see #Desc
     */
    Types.Site *getSite(Block *eb);

    /*!
     *  ======== idToCode ========
     *  Extract the code associated with an `Error_Id`
     *
     *  @param(id) `Error_Id` from which to extract the user defined
     *             code 
     *  @_nodoc
     */
    @Macro UInt16 idToCode(Id id);
    
    /*!
     *  ======== init ========
     *  Put an error block into its initial state
     *
     *  To ensure reliable error detection, clients must call `init` for
     *  an `Error_Block` prior to any use.
     *  
     *  If the same Error Block is used multiple times, only the last error
     *  raised is retained.
     *
     *  @param(eb) pointer to an `Error_Block` or `NULL`
     *
     *      If `eb` is `NULL` this function simply returns.
     */
    Void init(Block *eb);

    /*!
     *  ======== print ========
     *  Print error using System.printf()
     *
     *  This function prints the error using `System_printf()`.  The output
     *  is on a single line terminated with a new line character and has the
     *  following form:
     *  @p(code)
     *      <site>: <file>, line <line_num>: <err_msg>
     *  @p
     *  where `<site>` is the module that raised the error, `<file>` and
     *  `<line_num>` are the file and line number of the containing the call
     *  site of the `Error_raise()`, and `<err_msg>` is the error message
     *  rendered with the arguments associated with the error.
     *
     *  @param(eb) pointer to an `Error_Block` or `NULL`
     *
     *      If `eb` is `NULL` this function simply returns with no output.
     *
     *  @a(Warning)
     *  This function is not protected by a gate and, as a result,
     *  if two threads call this method concurrently, the output of the two
     *  calls will be intermingled.  To prevent intermingled error output,
     *  you can either wrap all calls to this method with an appropriate
     *  `Gate_enter`/`Gate_leave` pair or simply ensure that only one
     *  thread in the system ever calls this method.
     */
    Void print(Block *eb);

    /*!
     *  ======== raise ========
     *  Raise an error
     *
     *  This function is used to raise an `Error` by writing call site,
     *  error ID, and error argument information into the `Error_Block`
     *  pointed to by `eb`.
     *
     *  If `Error_raise` is called more than once on an `Error_Block` object,
     *  the previous error information is overwritten; only the last error 
     *  is retained in the `Error_Block` object.
     *
     *  In all cases, any configured `{@link #raiseHook Error.raiseHook}`
     *  function is called with a non-`NULL` pointer to a fully
     *  initialized `Error_Block` object.
     *
     *  @param(eb) pointer to an `Error_Block` or `NULL`
     *
     *      If `eb` is `NULL` or `{@link #policy Error.policy} == TERMINATE`,
     *      this function does not return to the caller; after calling any
     *      configured `{@link #raiseHook}`, `System_abort` is called with the
     *      string `"xdc.runtime.Error.raise: terminating execution\n"`.
     *
     *  @param(id) the error to raise
     *
     *      This pointer identifies the class of error being raised;
     *      the error class indicates how to interpret any subsequent 
     *      arguments passed to `{@link #raise}`.
     *
     *  @param(arg1) error's first argument
     *
     *      The argument interprested by the first control character
     *      in the error message format string. It is ignored if not needed.
     *
     *  @param(arg2) error's second argument
     *
     *      The argument interpreted by the second control character
     *      in the error message format string. It is ignored if not needed.
     */
    @Macro Void raise(Block *eb, Id id, IArg arg1, IArg arg2);

    /*! @_nodoc */
    Void raiseX(Block *eb, Types.ModuleId mod, String file, Int line, Id id,
        IArg arg1, IArg arg2);

internal:

    struct Module_State {
        UInt16      count;
    };

}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

