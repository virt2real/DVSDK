/* --COPYRIGHT--,EPL
 *  Copyright (c) 2009 Texas Instruments and others.
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
 *  ======== ITarget.xdc ========
 *
 *! Revision History
 *! ================
 *! 26-Aug-2009 sasha	created
 */
package xdc.bld;

/*!
 *  ======== ITarget2 ========
 *  Extension of the interface {@link xdc.bld.ITarget}.
 *
 *  This interface contains some common structures and config parameters
 *  shared by several packages that contain targets.
 */
metaonly interface ITarget2 inherits ITarget {

    /*!
     *  ======== Command ========
     *  Required command and options.
     *
     *  The compile, link, and archive functions in this interface are
     *  implemented by expanding the strings specified in this structure
     *  and inserting strings from the Options structure to form a single
     *  command.  The strings in this structure can not be changed by
     *  the user (they are fixed by the target), but the string in the
     *  Options structure may be changed by the user.
     *
     *  The final command is:
     *	    Command.cmd Options.prefix Command.opts Options.suffix
     *
     *  @field(cmd)	name of a tool-chain executable without any path
     *			information.  The location of this executable is
     *			specified by the binDir (or pathPrefix) 
     *			configuration parameter.
     *
     *	@field(opts)	required options passed to the command; these options
     *			can not be changed or eliminated by user's
     *			configuration script.
     */
    struct Command {
	string cmd;	/*! the command to run */
	string opts;	/*! required options for the command */
    }

    /*!
     *  ======== Options ========
     *  User configurable command options.
     *
     *  The option strings allow the user to pass additional parameters to the
     *  executable that is responsible for compiling, linker, or archiving.
     *  See `xdc.bld.ITarget2.Command`.
     */
    struct Options {
	string prefix;	/*! options that appear before Command.opts */
	string suffix;	/*! options that appear after Command.opts */
    }

    /*!
     *  ======== ar ========
     *  The command used to create an archive
     */
    readonly config Command ar;

    /*!
     *  ======== arOpts ========
     *  User configurable archiver options.
     */
    config Options arOpts = {
	prefix: "",
	suffix: ""
    };

    /*!
     *  ======== lnk ========
     *  The command used to link executables.
     */
    readonly config Command lnk;

    /*!
     *  ======== lnkOpts ========
     *  User configurable linker options.
     */
    config Options lnkOpts = {
	prefix: "",
	suffix: ""
    };

    /*!
     *  ======== cc ========
     *  The command used to compile C/C++ source files into object files
     */
    readonly config Command cc;

    /*!
     *  ======== ccOpts ========
     *  User configurable compiler options.
     */
    config Options ccOpts = {
	prefix: "",
	suffix: ""
    };

    /*!
     *  ======== ccConfigOpts ========
     *  User configurable compiler options for the generated config C file.
     *
     *  By default, this parameter inherits values specified in ccOpts, by
     *  expanding $(ccOpts.prefix) and $(ccOpts.suffix) into the values
     *  specified in ccOpts for this target.
     */
    config Options ccConfigOpts = {
	prefix: "$(ccOpts.prefix)",
	suffix: "$(ccOpts.suffix)"
    };

    /*!
     *  ======== asm ========
     *  The command used to assembles assembly source files into object files
     */
    readonly config Command asm;

    /*!
     *  ======== asmOpts ========
     *  User configurable assembler options.
     */
    config Options asmOpts = {
	prefix: "",
	suffix: ""
    };

    /*!
     *  ======== includeOpts ========
     *  Additional user configurable target-specific include path options
     */
    config string includeOpts;
}/*
 *  @(#) xdc.bld; 1, 0, 2,238; 2-22-2010 10:33:31; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

