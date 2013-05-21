/* 
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * */

extern int  __cinit__;  /* define by TI linker == -1 if .cinit isn't loaded */
extern char __bss__;    /* defined by the TI linker to be the start of .bss */
extern char __end__;    /* defined by the TI linker to be the end of .bss */

/*
 *  ======== _system_pre_init ========
 *  Called by the reset code prior to .cinit processing (which
 *  initializes all explicitly initialized C static or global variables)
 */
int _system_pre_init(void)
{
    /* if .cinit is not loaded, the loader has already initialized .bss */
    if (&__cinit__ != (int *)-1) {
        char *cp;
    
        /* otherwise, we initialize all .bss to 0 before .cinit is processed */
        for (cp = &__bss__; cp <= &__end__; ) {
            *cp++ = 0;
        }
    }    

    return (1);
}
/*
 *  @(#) ti.targets.rts430; 1, 0, 0,243; 2-24-2010 16:41:36; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

