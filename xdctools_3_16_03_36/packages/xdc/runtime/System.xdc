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
 *  ======== System.xdc ========
 */

package xdc.runtime;

/*!
 *  ======== System ========
 *  Basic system services
 *
 *  This module provides basic low-level "system" services; e.g.,
 *  character output, `printf`-like output, and exit handling.
 *
 *  This module is gated and other modules use its gate via the
 *  `{@link Gate#enterSystem}` and `{@link Gate#leaveSystem}`. The
 *  `System` gate must be enterable by any thread in a multi-threaded
 *  environments.  For example, in many real-time multi-threaded environments
 *  some types of threads, such as Interrupt Service Routines (ISRs), are not
 *  allowed to call operations that block the caller.  In such an environment,
 *  either the `System` gate must disable all interrupts or ISRs must never
 *  call a function in the `xdc.runtime` package.
 */

@Template("./System.xdt")
@Gated
@ModuleStartup
module System {

    /*! 
     *  ======== AtexitHandler ========
     *  `System`'s atexit function prototype.
     *
     *  Fuctions of this type can be added to the list of functions that
     *  are executed during application termination.
     *
     *  @see #atexit
     */
    typedef Void (*AtexitHandler)(Int);

    /*! 
     *  ======== STATUS_UNKNOWN ========
     *  Unknown exit status value
     *
     *  When the program exits by calling {@link #exit System_exit()} the
     *  `System`'s `atexit` functions are passed the status value passed to
     *  `System_exit()`.  However, if the program exits using 
     *  the ANSI C Standard Library `exit()` function, the `System`'s `atexit`
     *  functions are passed `System_STATUS_UNKNOWN`; ANSI C `atexit`
     *  functions are not passed the exit status.
     */
    const Int STATUS_UNKNOWN = 0xCAFE;

    /*! @_nodoc */
    @XmlDtd
    metaonly struct Module_View {
        String	atexitHandlers[];
        Int	numAtexitHandlers;
    };
   
    /*!
     *  ======== A_cannotFitIntoArg ========
     *  Assert that the target's `Float` type fits in an `IArg`
     *
     *  This assertion is triggered when the `%f` format specifier is used,
     *  the argument treated as an `IArg`, but for the current target
     *  `sizeof(Float)` > `sizeof(IArg)`.
     */
    config Assert.Id A_cannotFitIntoArg = {
        msg: "A_cannotFitIntoArg: sizeof(Float) > sizeof(Arg)"
    };

    /*!
     *  ======== extendedFormats ========
     *  Optional conversions supported by `{@link #printf System_printf}`
     *
     *  This string specifies the set of optional argument conversion
     *  specifiers required by the application.  By reducing the number of
     *  optional conversions understood by the `System {@link #printf}`
     *  methods, it is possible to significantly reduce the code size
     *  footprint of the `System` module.  This configuration parameter
     *  enables one to balance `printf` functionality against code size
     *  footprint.
     *
     *  The format of this string is simply a concatenated list of the desired
     *  conversion specifiers (with the leading `%` character).  For example,
     *  to support both `%f` and `%$L` set `extendedFormats` to `"%$L%f"`.
     *
     *  To disable all optional converstions, set `extendedFormats` to `null`
     *  or the empty string ("").
     *
     *  For a complete list of supported extensions, see the
     *  `{@link #printf System_printf}` "Extended_Format_Specifiers" section.
     *
     *  @a(Note)
     *  If an optional conversion is used by some part of the application and
     *  it is not specified in `extendedFormats`, the conversion character(s)
     *  and leading `%` are treated as ordinary characters to be output.  As
     *  a result, all subsequent arguments will almost certainly be converted
     *  using the wrong conversion specifier!
     *
     *  @see #printf
     */
    metaonly config String extendedFormats = "%$L";

    /*!
     *  ======== SupportProxy ========
     *  The implementation module of the low-level system functions.
     *
     *  This configuration parameter allows one to "bind" a different
     *  implementation of the low-level services required to implement
     *  `System`.
     *  @p(code)
     *      var System = xdc.useModule("xdc.runtime.System");
     *      var SysStd = xdc.useModule("xdc.runtime.SysStd");
     *      System.SupportProxy = SysStd;
     *  @p
     *
     *  If this parameter is not set, it defaults to `{@link SysMin}`.
     */
    proxy SupportProxy inherits ISystemSupport;

    /*!
     *  ======== maxAtexitHandlers ========
     *  Maximum number of dynamic atexit handlers allowed in the system.
     *
     *  Maximum number of `System` `atexit` handlers set during runtime via
     *  the `{@link System#atexit}` function.
     *
     */
    config Int maxAtexitHandlers = 8;

    /*!
     *  ======== abort ========
     *  Print a message and abort currently running executable.
     *
     *  This is called when an executable abnormally terminates.  
     *  The `System` gate is entered, the 
     *  `{@link #SupportProxy}`'s `abort` function is called
     *  and `abort` is called.
     *  No exit functions bound via `System_atexit()` or the ANSI C Standard
     *  Library `atexit()` functions are executed. 
     *
     *  @param(str)	abort message (not a format string)
     */
    Void abort(String str);

    /*!
     *  ======== atexit ========
     *  Add an exit handler
     *
     *  `System_atexit` pushes `handler` onto an internal stack of functions 
     *  to be executed when system is exiting (e.g. `System_exit` or `exit` is
     *  called). Up to `{@link #maxAtexitHandlers}` functions can be specified
     *  in this manner.  During the exit processing, the functions are popped
     *  off the internal stack and called until the stack is empty.
     *
     *  The `System` gate is entered before the `System_atexit` functions 
     *  are called.
     *
     *  The `SupportProxy`'s `{@link ISystemSupport#exit}` function is called
     *  after all the atexit functions are called.
     *
     *  @param(handler) the `AtexitHandler` to invoke during system
     *                  exit processing.
     *
     *  @a(returns)
     *  If `FALSE` is returned, the exit handler was not added and it will
     *  not be called during an exit.
     */
    Bool atexit(AtexitHandler handler);

    /*!
     *  ======== atexitMeta ========     
     *  Add an exit handler during configuration
     *
     *  This is the static counterpart to `System_atexit()`. This method can
     *  be used to add `atexit` handlers at configuration time.  These
     *  handlers do not count against the `maxAtexitHandlers`.
     *
     *  @param(handler) the `AtexitHandler` to invoke during system
     *                  exit processing.
     */
    metaonly Void atexitMeta(AtexitHandler handler);

    /*!
     *  ======== exit ========
     *  Exit currently running executable.
     *
     *  This function is called when an executable needs to terminate
     *  normally.  This function sets the exit code and simply calls `exit`.
     *  All functions bound via `System_atexit` or the ANSI C Standar Library
     *  `atexit` function are then executed. The `{@link #SupportProxy}`'s
     *  `exit` function is called during this time.
     *
     *  @param(stat)    exit status to return to calling environment.
     */
    Void exit(Int stat);

    /*!
     *  ======== putch ========
     *  Output a single character
     *
     *  The `{@link #SupportProxy}`'s `putch` function is called
     *  by this function.
     *
     *  @param(ch) character to be output.
     */
    Void putch(Char ch);

    /*!
     *  ======== flush ========
     *  Flush standard System I/O     
     *
     *  This function causes any buffered output characters are "written"
     *  to the output device.
     *
     *  The `{@link #SupportProxy}`'s `flush` function is called
     *  by this function.
     */
    Void flush();

    /*!
     *  ======== printf ========
     *  A smaller faster printf
     *
     *  This function behaves much like the ANSI C Standard `printf`
     *  but does not support the full range of format strings specified by
     *  the C Standard.  In addition, several non-standard format specifiers
     *  are recognized.
     *
     *  @a(Format Strings)
     *  The format string is a character string composed of zero or
     *  more directives: ordinary characters (not %), which are copied
     *  unchanged to the output stream; and conversion specifications, each of
     *  which results in fetching zero or more subsequent arguments.  Each
     *  conversion specification is introduced by the character %, and ends
     *  with a conversion specifier.  In between there may be (in this order)
     *  zero or more flags, an optional minimum field width, an optional
     *  precision and an optional length modifier.
     *
     *  @a(Flags)
     *  The following flags are supported:
     *  @p(dlist)
     *      - `-`
     *          The converted value is to be left adjusted on the field
     *          boundary (the default is right justification.)
     *      - `0`
     *          The value should be zero padded. For d, i, o, u, and x
     *          conversions, the converted value is padded on the left
     *          with zeros rather than blanks.
     *  @p
     *
     *  @a(Field Width)
     *  The optional field width specifier is a decimal digit string (with
     *  nonzero first digit) specifying a minimum field width. If the
     *  converted value has fewer characters than the field width, it will
     *  be padded with spaces on the left (or right, if the left-adjustment
     *  flag has been given).  Instead of a decimal digit string one may
     *  write `*` to specify that the field width is given in the next
     *  argument.  A negative field width is taken as a '-' flag followed
     *  by a positive field width.
     *
     *  @a(Precision)
     *  The optional precision specifier is a period ('.') followed by an
     *  optional decimal digit string.  Instead of a decimal digit string
     *  one may write `*` to specify that the precision is given in the 
     *  next argument which must be of type int.
     *
     *  If the precision is given as just '.', or the precision is
     *  negative, the precision is taken to be zero.  This gives the
     *  minimum number of digits to appear for d, i, o, u, and x
     *  conversions, or the maximum number of characters to be printed from
     *  a string for s conversions.
     *
     *  @a(Length Modifiers)
     *  The optional length modifier is a single character from the following
     *  list.
     *  @p(dlist)
     *      - `l`
     *          A  following integer conversion corresponds to a long int
     *          or unsigned long int argument
     *
     *  @p
     *
     *  @a(Conversion Specifiers)
     *  The following conversion specifiers are supported.
     *  @p(dlist)
     *      - `d`, `i`
     *          signed integer
     *      - `u`
     *          unsigned decimal
     *      - `x`
     *          unsigned hex
     *      - `o`
     *          unsigned octal
     *      - `p`
     *          pointer (@ + hex num)
     *      - `c`
     *          character
     *      - `s`
     *          string
     *  @p
     *  @a(Extended Conversion Specifiers)
     *  The following conversion specifiers are optionally supported.  See
     *  the `{@link #extendedFormats}` configuration parameter for more
     *  information about how to enable these conversion specifiers.
     *
     *  @p(dlist)
     *      - `f`
     *          decimal floating point.
     *      - `$`
     *          non-ANSI conversion prefix.  This prefix indicates that the
     *          next character identifies a non-ANSI standard conversion.
     *
     *          If the next character is `L` then the argument is treated as
     *          a pointer to a `{@link Types#Label}` and is converted to an
     *          appropriate string.
     *  @p
     *  
     *  @param(fmt) a 'printf-style' format string
     *
     *  @a(returns)
     *  `printf` returns the number of characters printed.
     */
    Int printf(String fmt, ...);

    /*!
     *  ======== aprintf ========
     *  `{@link #printf}` where all optional arguments are `IArg`s
     *
     *  This function will treat each argument as though it was widened to be 
     *  of type `IArg` prior to being passed to the `{@link #printf}` function
     *
     *  @see #printf
     */
    Int aprintf(String fmt, ...);

    /*!
     *  ======== sprintf ========
     *  Write formated output to a character buffer
     *
     *  This function is identical to `{@link #printf}` except that the
     *  output is copied to the specified character buffer `buf` followed
     *  by a terminating '\0' character.
     *
     *  @param(buf) a character output buffer
     *  @param(fmt) a 'printf-style' format string
     *
     *  @a(returns)
     *  `sprintf` returns the number of characters output not including the
     *  '\0' termination character.
     */
    Int sprintf(Char buf[], String fmt, ...);

    /*!
     *  ======== asprintf ========
     *  `{@link #sprintf}` where all optional arguments are `IArg`s
     *
     *  This function will treat each argument as though it was widened to be 
     *  of type `IArg` prior to being passed to the `{@link #sprintf}`
     *  function.
     *
     *  @see #sprintf
     */
    Int asprintf(Char buf[], String fmt, ...);

    /*!
     *  ======== vprintf ========
     *  A VaList printf
     *
     *  This function is identical to `{@link #printf}` except that its
     *  arguments are passed via a VaList (a "varargs list").
     *
     *  @param(fmt) a standard 'printf-style' format string.
     *  @param(va)  an args list that points to the arguments referenced
     *              by the fmt string
     *
     *  @a(returns)
     *  `vprintf` returns the number of characters output.
     */
    Int vprintf(String fmt, VaList va);

    /*!
     *  ======== avprintf ========
     *  `{@link #vprintf}` where all optional arguments are `IArg`s
     *
     *  This function will treat each argument as though it was widened to be 
     *  of type `IArg` prior to being passed to the `{@link #vprintf}`
     *  function.
     *
     *  @see #vprintf
     */
    Int avprintf(String fmt, VaList va);

    /*!
     *  ======== vsprintf ========
     *  A `VaList` sprintf
     *
     *  This function is identical to `{@link #sprintf}` except that 
     *  its arguments are passed via a `VaList` (a "varargs list").
     *
     *  @param(buf) a character output buffer
     *  @param(fmt) a standard '`printf`-style' format string.
     *  @param(va)  an arguments list that points to the arguments referenced
     *              by the `fmt` string
     *
     *  @a(returns)
     *  `vsprintf` returns the number of characters output.
     */
    Int vsprintf(Char buf[], String fmt, VaList va);

    /*!
     *  ======== avsprintf ========
     *  `{@link #vsprintf}` where all optional arguments are `IArg`s
     *
     *  This function is identical to `{@link #sprintf}` except that 
     *  its arguments are passed via a `VaList` (a "varargs list").
     *
     *  This function will treat each argument as though it was widened to be 
     *  of type `IArg` prior to being passed to the `vsprintf` function
     *
     *  @see #vsprintf
     */
    Int avsprintf(Char buf[], String fmt, VaList va);

internal:

    /*! struct used to keep track of state during doPrint */
    struct ParseData {
        Int     width;		/* width in format specifier */	 
        Bool    lFlag;		/* length modifier flag */
        Bool    lJust;		/* left justify flag */
        Int     precis;		/* precision in format specifier */	
        Int     len;		/* length of formatted number */ 	
        Int     zpad;		/* leading zero pad flag */
        Char    *end;		/* pointer to end of local buf to hold num */
	Bool	aFlag;		/* deal with vars on stack as IArgs */
	Char    *ptr;		/* ptr to local buf after filling in num */
    };

    /*! typedef for generated functions to process extended formats */
    typedef Int (*ExtendFxn)(Char **, Char **, VaList *, ParseData *);

    /*! config parameter used to call generated function  */
    readonly config ExtendFxn extendFxn = '&xdc_runtime_System_printfExtend__I';
    
    /*
     * ======== printfExtend ======== 
     *  System_printfExtend is generated based on extendedFormats string
     *
     *  This generated function is accessed through an internal config so
     *  that it is an indirect call in the ROM case, but optimized to a direct
     *  call in the RAM case.
     *
     * @_nodoc
     */
    Int printfExtend (Char **bufp, Char **fmt, VaList *va, ParseData *parse);

    /*!
     *  ======== exitFxns ========
     *  @_nodoc
     *  List of functions statically plugged to be called at exit
     *
     */
    metaonly config AtexitHandler exitFxns[];

    /*!
     *  ======== mprintf ========     
     *  @_nodoc
     */
    function mprintf(fmt, args);
    
    /*!
     *  ======== doPrint ========
     *  @_nodoc
     *
     */
    Int doPrint(Char buf[], String fmt, VaList va, Bool aFlag);
    
    /*!
     *  ======== formatNum ========
     *  @_nodoc
     *
     */
    Char *formatNum(Char *ptr, UInt32 n, Int zpad, Int base);
    
    /*!
     *  ======== putchar ========
     *  @_nodoc
     *
     *  Write character ch to the buffer and, if the buffer pointer is
     *  non-`NULL`, update the buffer pointer.
     */
    Void putchar(Char **bufp, Char ch);
    
    /*!
     *  ======== rtsExit ========
     *  @_nodoc
     */
    Void rtsExit();

    /*!
     *  ======== Module_State ========
     *  @_nodoc
     */
    struct Module_State {
        AtexitHandler  atexitHandlers[];   /* array of atexit handlers       */
        Int            numAtexitHandlers;  /* Current num of atexit handlers */
	Int            exitStatus;	   /* status for exit handlers       */
    };
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

