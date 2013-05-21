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
/*!
 *  ======== Cmdr ========
 *  Command line tool context
 */
metaonly module Cmdr {

    enum Context { SHELL, SCRIPT };

instance:

    config Context context = SHELL;
    config Int tid = 0;
    config Any socket = null;
    
    create(Any cmdmod);
    
    function error(msg);

    /*!
     * Parse command-line arguments into config params.
     *
     * This function accepts an array of command-line arguments, and
     * uses them to set the values of config parameters in a module
     * instance. Parsing is controlled by the XDC declarations of the
     * instance config params.
     *
     * @a(Usage)
     * The following command-line argument syntaxes are supported,
     * following the syntax supported by GNU getopt() and getopt_long():
     *
     * @p(code)
     *   -f                a boolean flag with short name
     *   -f value          a number or string with short name
     *   -fvalue
     *   -f=value
     *   --longname        a boolean flag with long name
     *   --longname value  a number or string with long name
     *   --longname=value  a number or string with long name
     * @p
     *
     * In addition the following non-standard syntaxes are supported:
     * @p(code)
     *   -f:value
     *   --longnamevalue
     *   --longname:value
     * @p
     *
     * @a(Declaration)
     * The long and short names of the config parameter are declared
     * by the @CommandOption() attribute of the XDC spec language. For
     * example to declare a boolean flag with a short name of "-f" and
     * a long name of "--flag", and a default value of false:
     * @p(code)
     *    @ CommandOption("f,flag")
     *    config Bool myFlag = false;
     * @p
     *
     * Options of type Bool with no argument are assigned the value
     * "true". The types String and Int can also be used, and always
     * require an argument to be given on the command line.
     *
     * @a(Combining Short Flags)
     * Short-name options can be combined on the command line where there
     * is no ambiguity, for example the following usages are equivalent:
     * @p(code)
     *   -a -b -c -f filename
     *   -abcf filename
     * @p
     *
     * @a(Multiple Occurrences)
     * If the config param is declared as an array, the option may
     * be used multiple times on the command line and each occurence
     * will be recorded. For example the following records all -I
     * options, in order:
     * @p(code)
     *   @ CommandOption("I")
     *   config String includeDirs[] = [];
     * @p
     *
     * @a(Required Options)
     * If the config param has no default value declared, then it
     * is required on the command line, and a Javascript exception will
     * be raised if it is omitted.
     *
     * @param(inst)  instance with config parameters to set
     * @param(args)  an array of command-line arguments
     */
    function getopts(inst, args);

    function info(msg);
    function read();
    function usage();
    function time(msg);
    function verbose(flag);
    function warning(msg);
    function write(s);

}
