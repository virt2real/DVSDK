/* ---------------------------------------------------------------------------
  FILE        : device.c
  PURPOSE     : Device (chip) specific initialization function
  PROJECT     : DM648 User Boot-Loader
  AUTHOR      : Daniel Allred
  DESC        : This file provides low-level init functions for use
                in the UBL for booting an application.  Some functionality
                ( DDR init, multiplier init, etc.) is assumed to take
                place in AIS commands - therefore the UBL is intended
                for use as an AIS image.
 ----------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// This module's header file
#include "device.h"

// I2C header
#include "i2c_ecp.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern __FAR__ VUint32* DDRStart;


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
  Uint32 status = E_PASS;

#ifndef SKIP_LOW_LEVEL_INIT
  // System PSC Setup
  DEVICE_PSCInit();

  // System PLL Setup
  status |= DEVICE_PLL1Init(DEVICE_PLL1_MULTIPLIER);
  
  // DDR2 Timing Setup
  status |= DEVICE_DDR2Init();
#endif

  // AEMIF Setup
  status |= DEVICE_EMIFInit();

  // UART0 Setup
  //status |= DEVICE_UART0Init();

  // TIMER0 Setup
  status |= DEVICE_TIMER0Init();

  // I2C0 Setup
  status |= DEVICE_I2C0Init();

  return status;
}

void DEVICE_LPSCTransition(Uint8 module,Uint8 domain, Uint8 state)
{
  while ( (PSC->PTSTAT) & (0x00000001 << domain) );
  PSC->MDCTL[module] = ((PSC->MDCTL[module]) & (0xFFFFFFE0)) | (state);
  PSC->PTCMD |= (0x00000001 << domain);
  while ( (PSC->PTSTAT) & (0x00000001 << domain) );
  while (((PSC->MDSTAT[module]) & 0x1F) != state);
}

void DEVICE_pinmuxControl(Uint32 regOffset, Uint32 mask, Uint32 value)
{
  SYSTEM->KEY_REG = DEVICE_KEY_REG_UNLOCK_VALUE;
  UTIL_waitLoop(100);
  SYSTEM->PINMUX[regOffset] &= ~mask;
  SYSTEM->PINMUX[regOffset] |= (mask & value);
}

DEVICE_BootMode DEVICE_bootMode( void )
{
  return (DEVICE_BootMode) ((SYSTEM->BOOTCFG & DEVICE_BOOTCFG_BOOTMODE_MASK) >> DEVICE_BOOTCFG_BOOTMODE_SHIFT);  
}

DEVICE_BusWidth DEVICE_emifBusWidth( void )
{
  if ( ( (SYSTEM->BOOTCFG) & DEVICE_BOOTCFG_EMIFWIDTH_MASK) >> DEVICE_BOOTCFG_EMIFWIDTH_SHIFT )
    return DEVICE_BUSWIDTH_16BIT;
  else
    return DEVICE_BUSWIDTH_8BIT;
}

void DEVICE_PSCInit()
{                                                                    
  Uint32 i;

  while (PSC->PTSTAT & 0x00000001);

  PSC->MDCTL[LPSC_TPCC] = (PSC->MDCTL[LPSC_TPCC] & ~(0x1F)) | PSC_ENABLE;
                                     
  for( i = LPSC_DDR2 ; i <= LPSC_TIMER1 ; i++ )
  {
    PSC->MDCTL[i] =  (PSC->MDCTL[i] & ~(0x1F)) | PSC_ENABLE;
  }
                                                                     
  for( i = LPSC_SPI ; i <= LPSC_IMCOP ; i++ )
  {
    PSC->MDCTL[i] =  (PSC->MDCTL[i] & ~(0x1F)) | PSC_ENABLE;
  }

  PSC->MDCTL[LPSC_3PSW] =  (PSC->MDCTL[LPSC_3PSW] & ~(0x1F)) | PSC_ENABLE;
                                                                     
  // Do DSP Always-On Power Domain Transitions                         
  PSC->PTCMD |= 0x00000001;
  while ((PSC->PTSTAT) & 0x00000001);

  // Do Ethernet Always-On Power Domain Transitions                         
  PSC->PTCMD |= 0x00000002;
  while ((PSC->PTSTAT) & 0x00000002);
}                                                                    

Uint32 DEVICE_PLL1Init(Uint32 PLLMult)
{
  Bool PllIsPoweredUp = ( PLL1->PLLCTL & 0x0002 ) >> 1;

  if (PLLMult == 0)
    return E_FAIL;

  // Step 1 - Set PLL to bypass, then wait for PLL to stabilize
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLENSRC_MASK | DEVICE_PLLCTL_PLLEN_MASK);
    UTIL_waitLoop( 150 );

  // Step 2 - Reset PLL
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLRST_MASK;
    
  // Step 3 - Disable PLL
  // Step 4 - Powerup PLL
  // Step 5 - Enable PLL
  if ( PllIsPoweredUp )
  {
    PLL1->PLLCTL |= DEVICE_PLLCTL_PLLDIS_MASK;         // Disable PLL
    PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLPWRDN_MASK);      // Power up PLL
    PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLDIS_MASK);        // Enable PLL        
  }
  else
  {
    PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLDIS_MASK);        // Enable PLL
  }

  // Step 6 - Wait for PLL to stabilize
  UTIL_waitLoop( 5000 );

  // Step 7 - Load PLL multiplier
  PLL1->PLLM = (PLLMult - 1) & 0x3f;

  // Step 8 - Bring PLL Out of Reset
  PLL1->PLLCMD |= DEVICE_PLLCMD_GOSET_MASK;

  // Step 9 - Wait for phase alignment
  while( ( PLL1->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK ) != 0 );
    
  // Step 10 - Wait for PLL to reset ( 2000 cycles )
  UTIL_waitLoop( 2000 );

  // Step 11 - Release from reset
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLRST_MASK);
    
  // Step 12 - Wait for PLL to re-lock ( 2000 cycles )
  UTIL_waitLoop( 2000 );

  // Step 13 - Switch out of BYPASS mode
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLEN_MASK;

  if ( (PLL1->PLLSTAT & DEVICE_PLLSTAT_LOCK_MASK) != 0)
    return E_PASS;
  else
    return E_FAIL;
}                                                                   

Uint32 DEVICE_DDR2Init()                                                     
{
  // Make sure DDR2 module has power
  DEVICE_LPSCTransition(LPSC_DDR2, PD0, PSC_ENABLE );

  // DDR2 Register Initialization (for 265.9 MHz)
  DDR2->DMCCTL   = 0x50006405;    // DLL powered, ReadLatency=5
  DDR2->SDCFG    = 0x00008832;    // DDR Bank: 32-bit bus, CAS=4, 8 banks, 1024-word pg
#ifdef DDR_512MB
  DDR2->SDTIM1   = 0x68DB5BD9;
  DDR2->SDTIM2   = 0x00B7C722;
#else
  DDR2->SDTIM1   = 0x42DB5BD9;
  DDR2->SDTIM2   = 0x00A4C722;
#endif
  DDR2->SDCFG    &= ~(0x8000);    // Clear TIMUNLOCK bit
  DDR2->SDRFC    = 0x0000081A;    // Refresh Control [ 7.8 usec * freq ]

  UTIL_waitLoop( 1500 );

  return E_PASS;
}                                                                   
                                                                     
Uint32 DEVICE_EMIFInit()
{
  Uint32 currCE = 0, width = 0;
  VUint32 *ABCR = NULL;

  // Set PINMUX for EMIF use
  DEVICE_pinmuxControl(0,DEVICE_PINMUX_EMIF_MASK,DEVICE_PINMUX_EMIF_EN);

  // Set width to 8 or 16
  width = ( ( (SYSTEM->BOOTCFG) >> DEVICE_BOOTCFG_EMIFWIDTH_SHIFT) & 0x1 );

  AEMIF->AWCCR &= ~(DEVICE_EMIF_AWCC_WAITSTATE_MASK);

  ABCR = &(AEMIF->AB1CR);

  while (currCE < DEVICE_EMIF_NUMBER_CE_REGION)
  {
    ABCR[currCE++] = 0x3FFFFFFC | width;      // Adjust for quicker access times   
  }
  return E_PASS;
}
 
Uint32 DEVICE_UART0Init()                                                             
{
  Uint16 divider,dividerX2;

  DEVICE_LPSCTransition(LPSC_UART0,PD0,PSC_SYNCRESET);
  DEVICE_LPSCTransition(LPSC_UART0,PD0,PSC_ENABLE);

  // The DM648 pin muxing registers must be set for UART0 use
  DEVICE_pinmuxControl(0,DEVICE_PINMUX_UART_MASK,DEVICE_PINUMX_UART_EN);

  // Put UART in reset
  UART0->PWREMU_MGNT = 0;
  UTIL_waitLoop(10000);

  // Take out of reset, set free running
  UART0->PWREMU_MGNT = 0xE001;
                                                                            
  // Set DLAB bit - allows setting of clock divisors
  UART0->LCR |= 0x80;
  UTIL_waitLoop(100);

  //divider = 148500000/(16*115200) = 80.57 => 81 = 0x51 => 148500000/(16*81) = 114583 (0.54% error)
  divider = DEVICE_SYSTEM_FREQ / (6*DEVICE_UART0_DESIRED_BAUD * DEVICE_UART0_OVERSAMPLE_CNT);
  dividerX2 = (2*DEVICE_SYSTEM_FREQ) / (6*DEVICE_UART0_DESIRED_BAUD * DEVICE_UART0_OVERSAMPLE_CNT);
  if (divider*2 < dividerX2) divider++;

  UART0->DLL = divider & 0xFF;
  UART0->DLH = (divider >> 8) & 0xFF;
                                                                               
  // Enable, clear and reset FIFOs
  UART0->FCR = 0x0;
  UTIL_waitLoop(100);

  UART0->FCR = 0xC9;
  UTIL_waitLoop(100);

  // Disable autoflow control
  UART0->MCR = 0x00;
  UTIL_waitLoop(100);
                                                                               
  // Set word length to 8 bits, no parity, one stop bit, clear DLAB bit
  UART0->LCR = 0x03;
  UTIL_waitLoop(100);

  // Enable interrupts
  UART0->IER = 0x07;
  UTIL_waitLoop(100);

  // Set to run free
  UART0->PWREMU_MGNT |= 0x1;
  UTIL_waitLoop(100);

  if ( (UART0->IIR & 0xC0) != 0xC0 )
    return E_FAIL;

  UTIL_waitLoop(100);

  return E_PASS;
}

Uint32 DEVICE_I2C0Init()
{
  Uint32 iCLK = 0;
  Uint32 iPSC = 0x0E;
  Uint32 D = 5;
         
  // Enable the Xmt, Master Mode, free running, 7-bit address, 8-bit words, no DLB
  I2C0->ICMDR =  I2C_ICMDR_MST |       // Set MST - Master mode
                 I2C_ICMDR_TRX |       // Set TRX - Transmitter
                 I2C_ICMDR_FRE;
  UTIL_waitLoop(1000);

  // Set the DM648 address
  I2C0->ICOAR = DEVICE_I2C_OWN_ADDRESS & 0xFF;

  // Set Default I2C High and Low Clock Hold
  // Set prescalar to 14 (Scaled clock = input clk / PSC+1)
  // Input clock can range from 726/6=121 MHz - 891/6=148.5 MHz
  // Scaled clock will fall in range 8-9.9 MHz
  I2C0->ICPSC = (Uint32)(0xFF & iPSC);
  iCLK =(DEVICE_SYSTEM_FREQ/6)/(iPSC*DEVICE_I2C_TARGET_FREQ*2) - D;
  I2C0->ICCLKH = (Uint32)(0xFF & iCLK);
  I2C0->ICCLKL = (Uint32)(0xFF & iCLK);

  // Enable the Xmt, Master Mode, free runninf, 7-bit address, 8-bit words, no DLB
  I2C0->ICMDR =  I2C_ICMDR_MST |       // Set MST - Master mode
                 I2C_ICMDR_TRX |       // Set TRX - Transmitter
                 I2C_ICMDR_FRE;

  // Set backward compatibility mode
  I2C0->ICEMDR = I2C_ICEMDR_EXTMODE;

  I2C0->ICIMR = 0;

  // Read and clear interrupt status register
  I2C0->ICSTR |= 0x0000703F;

  // Read ICIVR until clear
  while ((I2C0->ICIVR & 0x7) != 0x0);
                  
  // Take I2C Out of Reset
  I2C0->ICMDR =  I2C_ICMDR_MST |       // Set MST - Master mode
                 I2C_ICMDR_TRX |       // Set TRX - Transmitter
                 I2C_ICMDR_FRE |       // Set free running
                 I2C_ICMDR_IRS;
  UTIL_waitLoop(1000);

  return E_PASS;
}              

Uint32 DEVICE_I2C0Reset()
{
  I2C0->ICMDR &= ~I2C_ICMDR_IRS;
  UTIL_waitLoop(200);

  // Read and clear interrupt status register
  I2C0->ICSTR |= 0x00007FFF;

  // Read ICIVR until clear
  while ((I2C0->ICIVR & 0x7) != 0x0);
                  
  // Take I2C Out of Reset
  I2C0->ICMDR |= I2C_ICMDR_IRS;
  UTIL_waitLoop(200);
  return E_PASS;
}

Uint32 DEVICE_TIMER0Init()
{
  // Power-up the Timer
 	DEVICE_LPSCTransition(LPSC_TIMER0, PD0 ,PSC_ENABLE);

  // Put timer into reset
  TIMER0->EMUMGT_CLKSPD = 0x00000003;
  TIMER0->TCR           = 0x00000000;

  // Setup as 2 unchained 32-bit timers
  TIMER0->TGCR = 0x00000005;

  // Reset the timer counter to zero
  TIMER0->TIM12 = 0x00000000;

  // Set period to 1 sec
  TIMER0->PRD12 = 0x019BFCC0;

  return E_PASS;
}

void DEVICE_TIMER0Start(void)
{
  Uint8 evtRegOffset = TIMER0_LO_INT_EVENT_NUM>>5;
  Uint8 evtBitOffset = TIMER0_LO_INT_EVENT_NUM - (evtRegOffset<<5);

  // Clear the INT event flag
  INTC->EVTCLR[evtRegOffset] = 0x1 << evtBitOffset;

  // Put timer out in reset
  TIMER0->TGCR  &= ~(0x00000001);
    
  // Reset the timer counter to zero
  TIMER0->TIM12 = 0x00000000;

  // Set for one-time run
  TIMER0->TCR   = 0x00000040;
    
  // Take timer out of reset
  TIMER0->TGCR  = 0x00000005;

}

void DEVICE_TIMER0Stop(void)
{
  Uint8 evtRegOffset = TIMER0_LO_INT_EVENT_NUM>>5;
  Uint8 evtBitOffset = TIMER0_LO_INT_EVENT_NUM - (evtRegOffset<<5);

  // Clear the INT event flag
  INTC->EVTCLR[evtRegOffset] = 0x1 << evtBitOffset;

  // Put timer in reset
  TIMER0->TCR   = 0x00000000;
  TIMER0->TGCR  = 0x00000000;

  // Reset timer count to zero 
  TIMER0->TIM12 = 0x00000000;
}


Uint32 DEVICE_TIMER0Status(void)
{
  Uint8 evtRegOffset = TIMER0_LO_INT_EVENT_NUM>>5;
  Uint8 evtBitOffset = TIMER0_LO_INT_EVENT_NUM - (evtRegOffset<<5);

  return ( (INTC->EVTFLAG[evtRegOffset]) & (0x1 << evtBitOffset) );
}

/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
  HISTORY
    v1.0 completion
      DJA  -  07-Nov-2007
 ----------------------------------------------------------------------------- */
