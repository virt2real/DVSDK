/* --------------------------------------------------------------------------
  FILE        : device.c 				                             	 	        
  PURPOSE     : Device (chip) specific initialization function
  PROJECT     : C672x ROM boot loader
  AUTHOR      : Daniel Allred
  DESC        : This file provides low-level init functions for use
                  in the UBL for booting an application.
-------------------------------------------------------------------------- */ 


// General type include
#include "tistdtypes.h"

// Util functions
#include "util.h"

// This module's header file
#include "device.h"

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


/************************************************************
* Global Function Definitions                               *
************************************************************/

Uint32 DEVICE_init()
{

  // Put PLL into bypass mode
  PLL1->PLLCTL &= (~DEVICE_PLLCTL_PLLEN_MASK);
  UTIL_waitLoop(200);

  // Set EMIF to 8-bit width, slowest possible timings
  AEMIF->A1CR = 0x3FFFFFFC;

  // Reset SPI0, SPI1
  SPI0->SPIGCR0 = 0x00;
  SPI1->SPIGCR0 = 0x00;
  
  // Reset I2C0, I2C1
  I2C0->ICMDR = 0x00;
  I2C1->ICMDR = 0x00;

  // Reset McASP0, McASP1, McASP2
  MCASP0->GBLCTL = 0x00;
  MCASP1->GBLCTL = 0x00;
  MCASP2->GBLCTL = 0x00;
  
  // Reset HPI
  SYSTEM->CFGHPI = 0x00;

  UTIL_waitLoop(1000);

  DEVICE_pllConfig(13,1-1,2-1,4-1,4-1);

  return E_PASS;
}

DEVICE_BusWidth DEVICE_emifBusWidth( void )
{
  return DEVICE_BUSWIDTH_8BIT;
}

DEVICE_BootMode DEVICE_bootMode( void )
{
  Uint8 temp;
  DEVICE_BootMode bootMode;

  // Capture SPI0SOMI, SPI0SIMO and SPI0CLK - use as lower 3 bits of devicePinRegister
  temp = (SYSTEM->CFGPIN[0] & DEVICE_BOOTCFG_CFGPIN0_MODE_MASK) >> DEVICE_BOOTCFG_CFGPIN0_MODE_SHIFT;

  // Capture /UHPI_HCS and use as top bit of devicePinRegister
  temp |= (((SYSTEM->CFGPIN[1] & DEVICE_BOOTCFG_CFGPIN1_HPI_MASK) >> DEVICE_BOOTCFG_CFGPIN1_HPI_SHIFT) << 3);
  
  // Set the boot mode   
  if (temp & 0x08)
  { 
    bootMode = (DEVICE_BootMode) (temp & 0x07);
  }
  else
  {
    bootMode = (DEVICE_BootMode) DEVICE_BOOTMODE_HPI;
  }

  return bootMode;
}

void DEVICE_pllConfig( Uint32 pllm, Uint32 div0, Uint32 div1, Uint32 div2, Uint32 div3 )
{

  // Step 1: Put PLL into bypass mode
  PLL1->PLLCTL &= (~DEVICE_PLLCTL_PLLEN_MASK);

  // Step 2: Wait 4 cycles of the slowest of PLLOUT or reference clock source (CLKIN or OSCIN)
  // Slowest clock is 12 MHz, max PLLOUT is 600 MHZ -> use 200 cycles to make sure we have 4 of 
  // slowest possible clock
  UTIL_waitLoop (200);

  // Step 3: Put PLL in reset (write PLLRST = 1)
  PLL1->PLLCTL = DEVICE_PLLCTL_PLLRST_MASK;
  
  // Step 4: Program PLLDIV0 and PLLM
  PLL1->PLLDIV0 = (DEVICE_PLLDIV_EN_MASK | div0);
  PLL1->PLLM = (pllm & 0x1F);

  // Step 5: Program PLLDIV1-n.
  // DIV1 - After PLL- SYSCLK1 DSP Core
  // DIV2 - After PLL- SYSCLK2 PERIPHS (must be 2,3, or 4 times less than DIV1)
  // DIV3 - After PLL- SYSCLK3 EMIF CLOCK
  PLL1->PLLDIV1 = (DEVICE_PLLDIV_EN_MASK | div1);
  PLL1->PLLDIV2 = (DEVICE_PLLDIV_EN_MASK | div2);
  PLL1->PLLDIV3 = (DEVICE_PLLDIV_EN_MASK | div3);
  
  // Step 6: Wait for PLL to properly reset (125 ns. Since in bypass, use max
  // CLKIN of 50MHz -> 20ns sycles
  UTIL_waitLoop(10);

  // Step 7: Enable PLL Align control, set go bit to implement divider change
  PLL1->ALNCTL = DEVICE_ALNCTL_ALN1 | DEVICE_ALNCTL_ALN2 | DEVICE_ALNCTL_ALN3;
  PLL1->PLLCMD = DEVICE_PLLCMD_GOSET_MASK;

  // Step 8: Wait for GO operation to complete
  while (PLL1->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK);

  // Step 9: clear GOSET bit
  PLL1->PLLCMD = 0x00;
  
  // Step 10: Wait for PLL to properly reset
  UTIL_waitLoop(10);

  // Step 11: Bring PLL out of reset
  PLL1->PLLCTL &= (~DEVICE_PLLCTL_PLLRST_MASK);
  
  // Step 12: Wait for PLL to lock
  // Wait 187.5us.  Shortest possible cycles time = 20ns -> 187,500/20 = 9375
  // using accurate Loop cycles = (9375-5)/(1.65) = 5679
  UTIL_waitLoopAccurate (5679);

  // Step 13: Exit bypass mode (write PLLEN = 1)
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLEN_MASK;
  
  // Reset dMax
  DMAX->GIODIR = 0x00;
  asm("\tnop 2");
  DMAX->GIOGCR = 0x00;

  // Reset Bridge
  SYSTEM->CFGBRIDGE = 1;
  SYSTEM->CFGBRIDGE = 0;
  
}


/************************************************************
* Local Function Definitions                                *
************************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
    HISTORY
        v1.0 completion 							 						      
            Daniel Allred  -  1-Nov-2007
 ----------------------------------------------------------------------------- */



