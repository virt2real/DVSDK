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
 *  ======== Diags.xdc ========
 *
 *! Revision History
 *! ================
 *! 12-Mar-2008 agd	CDOC review changes
 *! 15-Feb-2008 sasha   Fixed setMaskEnabled documentation (CQ20777)
 */

/*!
 *  ======== Diags ========
 *  Diagnostics manager
 *
 *  Every XDC module has a "diagnostics mask" that allows clients to
 *  enable or disable diagnostics on a per module basis both at
 *  configuration time and at runtime. The `Diags` module manages a
 *  module's diagnostics mask.
 *
 *  You use the `Diags` module to set and clear bits in a module's
 *  diagnostics mask for the purpose of controlling diagnostics
 *  within that module. Each bit corresponds to a "type" of diagnostic
 *  that can be individually enabled or disabled.
 *
 *  A module's diagnostics mask controls both `{@link Assert}` and
 *  `{@link Log}` statements within that module. A module's diagnostics
 *  mask may also be used to conditionally execute blocks of code using
 *  the `{@link #query Diags_query()}` runtime function.
 *  
 *  A module's diagnostics mask can be set at configuration time and
 *  at runtime. The implementation of diagnostics is such that when they
 *  are permanently turned off at configuration time 
 *  (`{@link #ALWAYS_OFF Mode.ALWAYS_OFF}`), an optimizer can
 *  completely eliminate the diagnostics code from the program. Similarly,
 *  if diagnostics are permanently turned on at configuration time
 *  (`{@link #ALWAYS_ON Mode.ALWAYS_ON}`), the optimizer can
 *  eliminate all runtime conditional checking and simply
 *  invoke the diagnostics code directly. Runtime checking of the
 *  diagnostics mask is performed only when the diagnostics are configured
 *  to be runtime modifiable (`{@link #RUNTIME_OFF Mode.RUNTIME_OFF}` or 
 *  `{@link #RUNTIME_ON Mode.RUNTIME_ON}`).
 *
 *  Each bit of the diagnostics mask is controlled by one of the following
 *  constants.
 *
 *  @p(code)
 *  Constant    Meaning
 *  --------------------------
 *  ENTRY       Function entry
 *  EXIT        Function exit
 *  LIFECYCLE   Object life-cycle
 *  INTERNAL    Internal diagnostics
 *  ASSERT      Assert checking
 *  USER1       User defined diagnostics
 *  USER2       User defined diagnostics
 *  USER3       User defined diagnostics
 *  USER4       User defined diagnostics
 *  USER5       User defined diagnostics
 *  USER6       User defined diagnostics
 *  USER7       User defined diagnostics
 *  USER8       User defined diagnostics
 *  @p
 *
 *  These constants can be used from either JavaScript configuration
 *  scripts or C code and, therefore, have two "names". For example,
 *  to reference the ENTRY constant from JavaScript you must use
 *  `Diags.ENTRY` whereas from C you would use `Diags_ENTRY`.
 *
 *  The `ENTRY` and `EXIT` bits control Log statements at the entry and
 *  exit points, respectively, to each function within a module. This
 *  is useful for tracking the execution flow of your program.
 *
 *  The `LIFECYCLE` bit controls `Log` statements at the create/construct
 *  and delete/destruct points of each instance object for the module.
 *  This is useful for tracking the life-cycle of a module instance object.
 *
 *  The `ASSERT` bit controls Assert statements in a module. There are
 *  two classes of asserts:
 *
 *  @p(blist)
 *  - Public asserts, which have an `{@link Assert#Id Assert_Id}` and
 *  are documented in the module's reference pages. These asserts are
 *  on by default and are meant to help developers validate code that
 *  invokes a module's functions.
 *  - Internal asserts, which have no `{@link Assert#Id Assert_Id}`.
 *  These asserts are off by default and are typically used only when
 *  developing code. That is, like the standard C assert() mechanism,
 *  these asserts are not part of a deployed application.
 *  @p
 *
 *  When a module has the `ASSERT` bit set (which is set by default) in
 *  its diagnostics mask, the module executes all of its public assert
 *  statements. To enable internal asserts, you must set both the `ASSERT`
 *  and `INTERNAL` bits.
 *
 *  The `INTERNAL` bit is used to classify diagnostic code as being internal.
 *  That is to say, this class of diagnostics is undocumented and typically
 *  not used by client software.
 *
 *  The `USER1`-`8` bits are available to each module writer to use as he or
 *  she wishes.
 *
 *  @a(Examples)
 *  Configuration example: The following XDC configuration statements set
 *  a module's diagnostics mask in a configuration script. (In this case,
 *  the `Task` module of the `ti.sysbios.knl` package is used.) In this
 *  example, the `ENTRY` bit is turned on and the `EXIT` bit is turned off.
 *  Both bits are configured to be runtime modifiable.
 *  
 *  @p(code)
 *  var Diags = xdc.useModule('xdc.runtime.Diags');
 *  var Task = xdc.useModule('ti.sysbios.knl.Task');
 *
 *  Task.common$.diags_ENTRY = Diags.RUNTIME_ON;
 *  Task.common$.diags_EXIT = Diags.RUNTIME_OFF;
 *  @p
 *
 *  @p(html)
 *  <hr />
 *  @p
 *
 *  Runtime example: The following C code shows how to disable and
 *  reenable `ENTER` diagnostics at runtime for the `ti.sysbios.knl.Task`
 *  module configured in the previous example. The first call to
 *  `{@link Diags#setMask Diag_setMask()}` enables entry diagnostics
 *  (`"+E"`) for just the `ti.sysbios.knl.Task` module; any call to any
 *  `Task` method in the application causes an "entry" `Log` event to be
 *  generated. The second call disables ("-E") the generation of these
 *  events. See `{@link #setMask Diags_setMask()}` for a complete
 *  description of the strings accepted by this function.
 *
 *  @p(code)
 *  #include <xdc/runtime/Diags.h>
 *  :
 *  Diags_setMask("ti.sysbios.knl.Task+E");
 *  :
 *  Diags_setMask("ti.sysbios.knl.Task-E");
 *  @p
 *
 *  @p(html)
 *  <hr />
 *  @p
 *
 *  Configuration example: The following XDC configuration statements
 *  turn on asserts in the entire program.
 *
 *  @p(code)
 *  var Diags = xdc.useModule('xdc.runtime.Diags');
 *  var Defaults = xdc.useModule('xdc.runtime.Defaults');
 *
 *  Defaults.diags_ASSERT = Diags.ALWAYS_ON;
 *  @p
 *
 *  @p(html)
 *  <hr />
 *  @p
 *
 *  Configuration example: Using the
 *  `{@link Diags#setMaskMeta Diags.setMaskMeta()}` function, the
 *  following XDC configuration statements turn on asserts in all
 *  of the modules whose name begins with "`ti.sysbios.`" In this case,
 *  no change to the application code is necessary to enable these
 *  events. It is important to note that, while the configuration
 *  step must be re-run and the application must be re-linked, no
 *  application sources need to be recompiled.
 *
 *  @p(code)
 *  var Diags = xdc.useModule('xdc.runtime.Diags');
 *  Diags.setMaskMeta("ti.sysbios.%", Diags.ASSERT, Diags.ALWAYS_ON);
 *  @p
 */

@CustomHeader
@Template("./Diags.xdt")

module Diags {

    /*!
     *  ======== Mode ========
     *  Diagnostics mask bit value used at configuration time.
     *
     *  At run-time a module's diagnostics mask is an ordinary data word
     *  with each bit value being 0 or 1 indicating whether or not the
     *  corresponding diagnostic is disabled or enabled.  At configuration
     *  time, however, each bit of the diagnostics mask can be 
     *  placed in one of several `Mode`s; these modes determine its initial
     *  runtime value and whether or not the bit is modifiable at runtime.
     *
     *  When setting a module's diagnostics mask at configuration time,
     *  use one of the enumerated values of type `Mode`. These
     *  values will either set or clear a bit in the mask and also define
     *  if the bit can be changed at run-time. For example, using 
     *  `ALWAYS_OFF` as the bit value means that bit cannot be set
     *  at run-time. This fact can be used by an optimizer to perform
     *  constant-folding and dead-code elimination.
     */
    metaonly enum Mode {
        ALWAYS_OFF,     //! Bit is permanently cleared.
        ALWAYS_ON,      //! Bit is permanently set.
        RUNTIME_OFF,    //! Bit is cleared and modifiable at run-time.
        RUNTIME_ON      //! Bit is set and modifiable at run-time.
    };

    /*! Type used to specify bits in the diags mask. */
    typedef Bits16 Mask;

    const Mask ENTRY        = 0x0001;   //! Function entry
    const Mask EXIT         = 0x0002;   //! Function exit
    const Mask LIFECYCLE    = 0x0004;   //! Object life-cycle
    const Mask INTERNAL     = 0x0008;   //! Internal diagnostics

    const Mask ASSERT       = 0x0010;   //! Assert checking

    const Mask USER1        = 0x0100;   //! User defined diagnostics
    const Mask USER2        = 0x0200;   //! User defined diagnostics
    const Mask USER3        = 0x0400;   //! User defined diagnostics
    const Mask USER4        = 0x0800;   //! User defined diagnostics

    const Mask USER5        = 0x1000;   //! User defined diagnostics
    const Mask USER6        = 0x2000;   //! User defined diagnostics
    const Mask USER7        = 0x4000;   //! User defined diagnostics
    const Mask USER8        = 0x8000;   //! User defined diagnostics

    const Mask ALL          = 0xFFFF;   //! Turn on all diagnostics

    /*!
     *  ======== query ========
     *  Query the module's diagnostics mask against the given mask.
     *
     *  Use this query function to test the state of a module's
     *  diagnostics mask at runtime. This function will perform a logical
     *  `AND` operation on the module's diagnostics mask and the given mask.
     *  If any bits survive the operation, the function returns `true`.
     *
     *  @p(code)
     *  result = moduleMask & givenMask ? true : false;
     *  @p
     *
     *  This query function has a compile-time binding to the module's
     *  diagnostics mask. If the query function is part of the C code
     *  implementation of a module, then it will use that module's
     *  diagnostics mask. Otherwise, it will use the diagnostics mask
     *  of the `{@link Main xdc.runtime.Main}` module.
     *
     *  The implementation of the diagnostics mask and the query function
     *  is such that an optimizer can take advantage of dead code elimination
     *  and/or constant folding to eliminate or reduce code size. For example,
     *  if the query function is used in a conditional test, and the given
     *  mask contains only bits which have been configured to be permanently
     *  off, then the code for the entire conditional statement can be removed
     *  at link time. If the bits in the given mask have been configured to be
     *  permanently on, then the conditional code can be removed leaving the
     *  body of the conditional as direct in-line code.
     *
     *  @param(mask) mask of diagnostics bits to test
     *
     *  This given mask is constructed by `OR`'ing together
     *  the desired bits of the diagnostics mask using the constants listed
     *  in the {@link #ALL Mask Summary} above. The module's diagnostics
     *  mask will be logically `AND`'ed with the given mask, and return `true`
     *  if the result is non-zero and `false` otherwise.
     *
     *  @p(code)
     *      if (Diags_query(Diags_USER1 | Diags_USER4)) {
     *          :
     *      }
     *  @p
     *
     *  @a(Examples)
     *  In the following example, the `{@link #USER1 USER1}` bit of the
     *  module's diagnostics mask has been configured to be permanently off,
     *  thus the entire conditional code block can be removed at link time.
     *  Note, the C code below is part of the module itself.
     *
     *  Configuration Script
     *  @p(code)
     *  var Diags = xdc.useModule('xdc.runtime.Diags');
     *  var ModA = xdc.useModule('my.package.ModuleA');
     *  ModA.common$.diags_USER1 = Diags.ALWAYS_OFF;
     *  @p
     *  
     *  C Code, ModA.c
     *  @p(code)
     *  if (Diags_query(Diags_USER1)) {         // this code removed
     *      ...additional code here...          // this code removed
     *  }                                       // this code removed
     *  @p
     *
     *  @p(html)
     *  <hr />
     *  @p
     *
     *  In the following example, the `{@link #USER1 USER1}` bit of the
     *  module's diagnostics mask has been configured to be permanently on,
     *  thus the conditional code can be removed leaving the code contained
     *  within the conditional statement. Note, the C code below is part of
     *  the module itself.
     *
     *  Configuration Script
     *  @p(code)
     *  var Diags = xdc.useModule('xdc.runtime.Diags');
     *  var ModA = xdc.useModule('my.package.ModuleA');
     *  ModA.common$.diags_USER1 = Diags.ALWAYS_ON;
     *  @p
     *  
     *  C Code, ModA.c
     *  @p(code)
     *  if (Diags_query(Diags_USER1) {          // this code removed
     *      ...additional code here...          // this code remains
     *  }                                       // this code removed
     *  @p
     *
     */
    @Macro Bool query(Mask mask);

    /*!
     *  ======== setMask ========
     *  Set a module's diagnostics mask at runtime.
     *
     *  Use the given control string to set or clear bits in a module's
     *  diagnostics mask. The control string defines one or more actions
     *  where each action modifies the diagnostics mask in one or more
     *  modules. Each action can either set, clear, or assign a module's
     *  diagnostics mask. To both set and clear bits in the same diagnostics
     *  mask requires two actions, or you can assign the entire mask
     *  explicitly in one action. Each action can specify a given module or
     *  a set of modules using name prefix matching.
     *
     *  @a(Warning)
     *
     *  Each bit of a module's diagnostics mask that is to be modified at
     *  runtime, must be configured to be runtime modifiable in the
     *  program's configuration script. Use either `{@link #Mode RUNTIME_OFF}` 
     *  or `{@link #Mode RUNTIME_ON}` as the configuration value for the
     *  desired bit in the diagnostics mask. In addition, the
     *  `{@link Diags#setMaskEnabled Diags.setMaskEnabled}` configuration
     *  parameter must be set to `true` in order to load this function onto
     *  the target. Finally, the following configuration parameters must 
     *  have the values indicated (which are their default values):
     *
     *  @p(blist)
     *  - `{@link IModule#common$ <module>.common$.namedModule} = true;`
     *  - `{@link Text#isLoaded} = true;`
     *  @p
     *
     *  Note: any error that occurs during the parsing of the control string
     *  causes `Diags_setmask()` to return without processing the remainder
     *  of the control string.
     *
     *  @param(control) diagnostic mask control string 
     *
     *  This control string defines one or more actions
     *  where each action consists of a module name, an operator character,
     *  and a list of bit specifiers. Use the `%` character as a wildcard 
     *  to turn the module name into a prefix matching pattern for a set
     *  of modules. Multiple actions are separated with the `;` character.
     *
     *  @p
     *  The control string has the following format:
     *
     *  @p(code)
     *  <module[%]><op><bits>[;<module[%]><op><bits>]
     *  @p
     *
     *  Specify individual module names explicitly (e.g. 
     *  `ti.sysbios.knl.Task`), or match multiple modules using a prefix
     *  matching pattern specified with the `%` character (e.g.
     *  `ti.sysbios.knl.%`).
     *
     *  @p
     *  The operator is specified with a single character from the following
     *  table.
     *
     *  @p(code)
     *  Operator    Description
     *  --------------------------------------------------
     *  +           Set only the specified bits (other bits preserved)
     *  -           Clear only the specified bits (other bits preserved)
     *  =           Assign the entire mask to the given value where the
     *              specified bits are set and all other bits are cleared
     *  @p
     *
     *  The bits are specified with a list of characters from the following
     *  table. Refer to the {@link #ALL Mask Summary} for a list of each
     *  bit of the diagnostics mask.
     *
     *  @p(code)
     *  Control     Diagnostics
     *  Character   Constant        Description
     *  --------------------------------------------------
     *  E           ENTRY           Function entry
     *  X           EXIT            Function exit
     *  L           LIFECYCLE       Object life-cycle
     *  I           INTERNAL        Internal diagnostics
     *  A           ASSERT          Assert checking
     *  1           USER1           User defined diagnostics
     *  2           USER2           User defined diagnostics
     *  3           USER3           User defined diagnostics
     *  4           USER4           User defined diagnostics
     *  5           USER5           User defined diagnostics
     *  6           USER6           User defined diagnostics
     *  7           USER7           User defined diagnostics
     *  8           USER8           User defined diagnostics
     *  @p
     *
     *  @a(Examples)
     *  The following example demonstrates how to set a module's diagnostics
     *  mask (the `Task` module in this case) at runtime. In this example, the
     *  `{@link #USER1 USER1}` bit is turned on. Note that the module's
     *  `{@link #USER1 USER1}` diagnostics bit must be configured to be runtime
     *  modifiable. In this instance, the bit is initialized to off.
     *
     *  Configuration Script
     *  @p(code)
     *  var Diags = xdc.useModule('xdc.runtime.Diags');
     *  var Task = xdc.useModule('ti.sysbios.knl.Task');
     *  Task.common$.diags_USER1 = Diags.RUNTIME_OFF;
     *  @p
     *
     *  C Code
     *  @p(code)
     *  Diags_setMask("ti.sysbios.knl.Task+1");
     *  @p
     *
     *  @p(html)
     *  <hr />
     *  @p
     *
     *  The following example demonstrates the use of the `%` wildcard
     *  character to set the `{@link #USER1 USER1}` bit at runtime for
     *  all modules in the `ti.sysbios.knl` package. The meta-only
     *  `{@link #setMaskMeta Diags.setMaskMeta}` function is used to configure
     *  the `{@link #USER1 USER1}` bit to be runtime modifiable. The `setMask`
     *  function is used to actually set the `{@link #USER1 USER1}` bit at
     *  runtime in all the `ti.sysbios.knl` modules.
     *  Note the use of the `%` character in both functions to match all the
     *  module names within the given package.
     *
     *  Configuration Script
     *  @p(code)
     *  var Diags = xdc.useModule('xdc.runtime.Diags');
     *  Diags.setMaskMeta("ti.sysbios.knl.%", Diags.USER1, Diags.RUNTIME_OFF);
     *  @p
     *
     *  C Code
     *  @p(code)
     *  Diags_setMask("ti.sysbios.knl.%+1");
     *  @p
     *
     *  @p(html)
     *  <hr />
     *  @p
     *
     *  In the following example, the `{@link #ENTRY ENTRY}`, 
     *  `{@link #EXIT EXIT}` and `{@link #LIFECYCLE LIFECYCLE}` trace is
     *  enabled for all modules in the `ti.sysbios.knl` package but is
     *  initially off; i.e., no events will occur until explicitly turned
     *  on at runtime.
     *
     *  At runtime the call to `Diags_setMask` turns on
     *  `{@link #ENTRY ENTRY}` and `{@link #EXIT EXIT}` trace and turns off
     *  `{@link #LIFECYCLE LIFECYCLE}` trace for all modules in
     *  the application for which trace has been enabled during
     *  configuration.  In this case, the only modules that can generate
     *  events are those in the `ti.sysbios.knl` package.
     *
     *  Configuration Script
     *  @p(code)
     *  var Diags = xdc.useModule('xdc.runtime.Diags');
     *  Diags.setMaskMeta("ti.sysbios.knl.%",
     *      Diags.ENTRY | Diags.EXIT | Diags.LIFECYCLE, Diags.RUNTIME_OFF);
     *  @p
     *
     *  C Code
     *  @p(code)
     *  Diags_setMask("%+EX;%-L");
     *  @p
     */
    Void setMask(String control);

    /*!
     *  ======== setMaskMeta ========
     *  Set the module's diagnostics mask at config time.
     *
     *  @param(pattern) module prefix or regular expression
     *
     *  The `pattern` is used to match a module's name. If `pattern` is
     *  specified as a string, then name prefix matching is used. The
     *  pattern may also be a regular expression.  Only the masks of the
     *  modules matching `pattern` are set.
     *
     *  @param(mask) diagnostic fields to modify
     *
     *  The `mask` is used to determine which fields in the diags mask are
     *  modified. Each field specified in the mask is set to the given
     *  `mode` value.
     *
     *  @param(mode) mode to assign to the specified `mask` fields
     */
    metaonly Void setMaskMeta(Any pattern, Mask mask, Mode mode);

internal:

    /*!
     *  ======== setMaskEnabled ========
     *  Controls the ability to set the diags mask at run-time.
     *
     *  This configuration parameter allows whole program optimizers to reduce
     *  the code size. The default is false, which means the diags mask will
     *  not be modified at run-time and thus the code is not needed.
     *
     *  For now, this should be internal because its value is determined
     *  automatically, rather than through user's input. See CQ19111 for more
     *  details.
     */
    config Bool setMaskEnabled = false;

    /*
     *  ======== dictBase ========
     *  Array of module-id:diags-mask pairs in which each module is named
     *
     *  This array, generated by Diags.xdt, is terminated by an element
     *  with modId == 0.
     */
    config DictElem *dictBase = null;

    struct DictElem {
        Types.ModuleId  modId;      /* statically computed module id */
        Bits16          *maskAddr;  /* module's diags mask address */
    };
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:57; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

