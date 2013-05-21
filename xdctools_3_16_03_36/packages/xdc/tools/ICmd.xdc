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
//! Generic xdc-script (xs) command 
metaonly interface ICmd {

    //! Usage for this command
    config String usage[] = [];

    //! 'xs' shell entry point
    final function main(args);

    //! 'xs' script entry point
    final function exec(args);

instance:

    //! Underlying implementation
    Any run(Cmdr.Instance cmdr, String args[]);
}
