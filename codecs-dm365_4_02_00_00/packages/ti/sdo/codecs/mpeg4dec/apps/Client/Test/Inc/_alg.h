/*
 *  Copyright 2003 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) XDAS 2.51.00 11-29-2003 (xdas-2.50.00.9)
 */
/*
 *  ======== _alg.h ========
 */
#ifndef _ALG_
#define _ALG_

/*
 *  ======== _ALG_allocMemory ========
 */
extern Bool _ALG_allocMemory(IALG_MemRec *memTab, Int n);

/*
 *  ======== _ALG_freeMemory ========
 */
extern Void _ALG_freeMemory(IALG_MemRec *memTab, Int n);

#endif
