/* --------------------------------------------------------------------------
  FILE        : selfcopy.h
  PROJECT     : DaVinci Serial boot and Flashing Utils
  AUTHOR      : Daniel Allred
  DESC        : Self-copy code used for XiP in NOR Flash
 ----------------------------------------------------------------------------- */

#ifndef _SELFCOPY_H_
#define _SELFCOPY_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/


/***********************************************************
* Global Typedef declarations                              *
***********************************************************/


/***********************************************************
* Global Function Declarations                             *
***********************************************************/

/*
 * UBL_selfcopy() has naked attribute (doesn't save registers since it is the entry
 * point when the UBL is found at the base of the NOR Flash and then goes 
 * directly to the the boot() function, which is also naked). This setup 
 * requires that the gnu compiler uses the -nostdlib option. 
 */
#if defined(__TMS470__)
  extern void selfcopy( void );
#elif defined(__GNUC__)
  extern void selfcopy( void ) __attribute__((naked,section(".selfcopy")));
#endif

/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif // _SELFCOPY_H_
