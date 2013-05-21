/*
    Davinci ARM Evaluation Software

    (c)Texas Instruments 2003
*/


/** \file intc.h
    \brief Interrupt Controller User APIs

*/


#ifndef __INTC_H__
#define __INTC_H__

#include <tistdtypes.h>
/**
 \brief Interrupt Service Routine (ISR) prototype typedef
*/

void swi_vector(); 
void data_abort_vector();
void undef_vector();
void pref_abort_vector();


#endif /*   __INTC_H__   */

/*@}*/

/* Rev.No.   Date/Time               ECN No.          Modifier      */
/* -------   ---------               -------          --------      */

/* 1         25 Jun 2004 10:31:02    1881             xkeshavm      */
/*                                                                  */
/* Command header files added to develop test cases                 */
/********************************************************************/ 
