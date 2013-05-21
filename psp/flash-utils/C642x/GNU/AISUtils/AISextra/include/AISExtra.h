/* --------------------------------------------------------------------------
  FILE        : AISExtra.h
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : Header file for AIS Extra commands for use in AIS Scripts    
 ----------------------------------------------------------------------------- */

#ifndef _AISEXTRA_H_
#define _AISEXTRA_H_

#include "tistdtypes.h" 

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

// Global Macro Declarations

// Function Prototypes

// Execute LPSC state transition
void LPSCTransition();

// UART send DONE function
void UARTSendDONE();

#endif // End _AISEXTRA_H_

