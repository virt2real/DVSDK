/* --------------------------------------------------------------------------
    FILE        : ubl.c 				                             	 	  
    PURPOSE     : User boot loader main file
    PROJECT     : DM648 UBL for application loading
    AUTHOR      : Daniel Allred
    DESC        : The UBL has the job to load the application code
                  out of the NOR flash and into DDR RAM, and then configure
                  chip and EVM so that the application can run.  Basically
                  it has to do all the stuff that the GEL would do if the
                  application was being loaded from CCS.
 ----------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// This module's header file
#include "ubl.h"

// DEBUG module
#include "debug.h"

// AIS module
#include "ais.h"

// Common UTIL module
#include "util.h"

// DEVICE module (chip-specific init)
#include "device.h"

// I2C_ECP module (to communicate with EVM's MSP430)
#include "i2c_ecp.h"


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


/************************************************************
* Local Variable Definitions                                *
\***********************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

Uint32 gEntryPoint;
AIS_fxnPtr bootFunction;


/************************************************************
* Global Function Definitions                               *
************************************************************/

void main(void)
{
  Uint8       regValue;

  // Init the memory alloc routines
  UTIL_setCurrMemPtr(0);

  // System init
  if (DEVICE_init() != E_PASS)
  {
    DEBUG_printString("Device initialization failed.\r\n");
    return;
  }

  // Give some time for I2C bus to settle (power-supply issue?)
  UTIL_waitLoop(4000000);

  // Make sure our board and chip can read the NOR via EMIF
  if (I2C_ECP_write(I2C_ECP_VMX_REG,0x20) != E_PASS)
  {
    DEBUG_printString("Write to ECP EMIF/VP control register has failed.\r\n");
    return;
  }
  DEVICE_pinmuxControl( 0, DEVICE_PINMUX_EMIF_MASK, DEVICE_PINMUX_EMIF_EN );


  // Start body of UBL
  DEBUG_printString("Starting UBL - ");
  DEBUG_printString(UBL_FLASH_TYPE); 
  DEBUG_printString(" Flash, v");
  DEBUG_printString( UBL_VERSION_STRING );
  DEBUG_printString("\r\n");

  // Find and copy the application image from the NOR flash
  if (NORBOOT_copy() != E_PASS)
  {
    DEBUG_printString( "\tERROR: Application boot failed.\r\n" );
    return;
  }
  
  // Modify board-level and chip-level settings to prep for application run

  // Set board-level muxes for video ports
  if (I2C_ECP_write(I2C_ECP_VMX_REG,0x44) != E_PASS)
  {
    DEBUG_printString("Write to ECP VP control register appears to have failed.");
    return;
  }

  // Set video port capture clocks for SD capture
  if (I2C_ECP_write(I2C_ECP_CMD_REG,0x08) != E_PASS)
  {
    DEBUG_printString("Write to ECP command register appears to have failed.");
    return;
  }

  // Set board-level muxes for audio codecs(AIC33s)
  if (I2C_ECP_write(I2C_ECP_McASP_MUX_CTRL_REG,0x19) != E_PASS)
  {
    DEBUG_printString("Write to ECP McASP control register appears to have failed.");
    return;
  }

  // Do one read to force the last write to complete
  I2C_ECP_read(I2C_ECP_McASP_MUX_CTRL_REG,&regValue);

  DEBUG_printString("Board-level setup complete.\r\n");


  // Set chip-level pin muxes for audio ports
  DEVICE_pinmuxControl( 0,
                        DEVICE_PINMUX_MCASP_MASK,
                        DEVICE_PINMUX_MCASP_EN );
  // Set chip-level pin muxes for video ports
  DEVICE_pinmuxControl( 0,
                        DEVICE_PINMUX_VP0_MASK  |
                        DEVICE_PINMUX_VP1_MASK  |
                        DEVICE_PINMUX_VP34_MASK |
                        DEVICE_PINMUX_VP2_MASK,
                        DEVICE_PINMUX_VP0_EN  |
                        DEVICE_PINMUX_VP1_EN  |
                        DEVICE_PINMUX_VP34_EN |
                        DEVICE_PINMUX_VP2_EN );

  DEBUG_printString("Chip-level setup complete.\r\n");

  // Pass control to the entry point in RAM
  DEBUG_printString("Passing control to entry point at ");
  DEBUG_printHexInt(gEntryPoint);
  DEBUG_printString(".\r\n");
  bootFunction = (AIS_fxnPtr) gEntryPoint;
  (*bootFunction)();
}

/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
    HISTORY
        v1.00  -  DJA  -  16-Aug-2007
 	        Initial release 
 ----------------------------------------------------------------------------- */



