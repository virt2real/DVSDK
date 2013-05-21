/* --------------------------------------------------------------------------
  FILE        : sft.c                                                   
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : The main project file for the serial flasher target
 ----------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// This module's header file 
#include "sft.h"

// Device specific CSL
#include "device.h"

// Misc. utility function include
#include "util.h"

// Project specific debug functionality
#include "debug.h"
#include "uartboot.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/



/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static Uint32 LOCAL_boot(void);
static void (*APPEntry)(void);


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

Uint32 gEntryPoint;


/************************************************************
* Global Function Definitions                               *
************************************************************/

// Main entry point
void main(void)
{

  // Call to real boot function code
  LOCAL_boot();
    
  // Jump to entry point
  APPEntry = (void (*)(void)) gEntryPoint;
  (*APPEntry)();  

}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 LOCAL_boot(void)
{
  DEVICE_BootMode bootMode;

  // Read boot mode 
  bootMode = DEVICE_bootMode();
  
  if (bootMode == DEVICE_BOOTMODE_UART)
  {
    // Wait until the RBL is done using the UART. 
    while((UART0->LSR & 0x40) == 0 );
  }

  // Platform Initialization
  if ( DEVICE_init() != E_PASS )
  {
    DEBUG_printString(devString);
    DEBUG_printString(" initialization failed!\r\n");
    asm(" MOV PC, #0");
  }
  else
  {
    DEBUG_printString(devString);
    DEBUG_printString(" initialization passed!\r\n");
  }

  // Set RAM pointer to beginning of RAM space
  UTIL_setCurrMemPtr(0);

  // Send some information to host
  DEBUG_printString("TI SFT Version: ");
  DEBUG_printString(SFT_VERSION_STRING);
  DEBUG_printString("\r\nBooting Catalog Serial Flasher\r\n");
  
  // Perform UART boot (always assume UART boot since this is only used for serial flashing)
  UARTBOOT_copy();
    
  DEBUG_printString("   DONE");
  
  UTIL_waitLoop(10000);

  DEVICE_TIMER0Stop();

  return E_PASS;    
}


/************************************************************
* End file                                                  *
************************************************************/
