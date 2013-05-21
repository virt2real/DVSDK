/* --------------------------------------------------------------------------
  FILE        : boot.h
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : ARM926EJ-S entry point functionality header
 ----------------------------------------------------------------------------- */

#ifndef _BOOT_H_
#define _BOOT_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/


/***********************************************************
* Global Function Declarations                             *
***********************************************************/

/*
 * boot() has naked attribute (doesn't save registers since it is the entry point
 * out of boot and it doesn't have an exit point). This setup requires
 * that the gnu compiler uses the -nostdlib option. 
 */
#if defined(__TMS470__)
  extern void boot( void );
#elif defined(__GNUC__)
  extern void boot( void ) __attribute__((naked,section(".boot")));
#endif


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_BOOT_H_

