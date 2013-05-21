/* --------------------------------------------------------------------------
  FILE        : device.c 				                             	 	        
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : This file provides low-level, device-specific init functions
                for use the DM35x device.
-------------------------------------------------------------------------- */ 

// General type include
#include "tistdtypes.h"

// This module's header file
#include "device.h"

// Debug module
#include "debug.h"

// Utility functions
#include "util.h"


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

#ifdef DM355_270
  // For Micron MT47H64M16BT-37E @ 216 MHz
  static const Uint8 DDR_NM = 1;      // Must be set to 1 on DM35x (only 16-bit buswidth is supported)
  static const Uint8 DDR_CL = 3;
  static const Uint8 DDR_IBANK = 3;
  static const Uint8 DDR_PAGESIZE = 2;
  static const Uint8 DDR_T_RFC = 27;
  static const Uint8 DDR_T_RP = 2;
  static const Uint8 DDR_T_RCD = 2;
  static const Uint8 DDR_T_WR = 3;
  static const Uint8 DDR_T_RAS = 8;
  static const Uint8 DDR_T_RC = 11;
  static const Uint8 DDR_T_RRD = 2;
  static const Uint8 DDR_T_WTR = 1;
  static const Uint8 DDR_T_RASMAX = 8;
  static const Uint8 DDR_T_XP = 1;
  static const Uint8 DDR_T_XSNR = 29;
  static const Uint8 DDR_T_XSRD = 199;
  static const Uint8 DDR_T_RTP = 2;   // FIXME: Is this right?
  static const Uint8 DDR_T_CKE = 2;
  static const Uint16 DDR_RR = 1685;
  static const Uint8 DDR_READ_Latency = 4; 

  static const Uint32 PLL1_Mult = 180u;
  static const Uint32 PLL2_Mult = 144u;
#else
  // For Micron MT47H64M16BT-37E @ 171 MHz
  static const Uint8 DDR_NM = 1;      // Must be set to 1 on DM35x (only 16-bit buswidth is supported)
  static const Uint8 DDR_CL = 3;
  static const Uint8 DDR_IBANK = 3;
  static const Uint8 DDR_PAGESIZE = 2;
  static const Uint8 DDR_T_RFC = 21;
  static const Uint8 DDR_T_RP = 2;
  static const Uint8 DDR_T_RCD = 2;
  static const Uint8 DDR_T_WR = 2;
  static const Uint8 DDR_T_RAS = 6;
  static const Uint8 DDR_T_RC = 9;
  static const Uint8 DDR_T_RRD = 1;
  static const Uint8 DDR_T_WTR = 1;
  static const Uint8 DDR_T_RASMAX = 7;
  static const Uint8 DDR_T_XP = 2;
  static const Uint8 DDR_T_XSNR = 23;
  static const Uint8 DDR_T_XSRD = 199;
  static const Uint8 DDR_T_RTP = 3;
  static const Uint8 DDR_T_CKE = 3;
  static const Uint16 DDR_RR = 1336;
  static const Uint8 DDR_READ_Latency = 4; 
  
  static const Uint32 PLL1_Mult = 144u;
  static const Uint32 PLL2_Mult = 114u;  
#endif  


/************************************************************
* Global Variable Definitions                               *
************************************************************/

const String devString = "DM35x";


/************************************************************
* Global Function Definitions                               *
************************************************************/

Uint32 DEVICE_init()
{
  Uint32 status = E_PASS;
  Uint32 temp;

  // Mask all interrupts
  AINTC->INTCTL = 0x4;
  AINTC->EABASE = 0x0;
  AINTC->EINT0  = 0x0;
  AINTC->EINT1  = 0x0;		
   
  // Clear all interrupts
  AINTC->FIQ0 = 0xFFFFFFFF;
  AINTC->FIQ1 = 0xFFFFFFFF;
  AINTC->IRQ0 = 0xFFFFFFFF;
  AINTC->IRQ1 = 0xFFFFFFFF;

#ifndef SKIP_LOW_LEVEL_INIT
  // System PSC setup - enable all
  DEVICE_PSCInit();
  
  DEVICE_pinmuxControl(0,0xFFFFFFFF,0x00007F55);  // All Video Inputs
  DEVICE_pinmuxControl(1,0xFFFFFFFF,0x00145555);  // All Video Outputs
  DEVICE_pinmuxControl(2,0xFFFFFFFF,0x00000004);  // EMIFA
  DEVICE_pinmuxControl(3,0xFFFFFFFF,0x1BFF55FF);  // SPI0, SPI1, UART1, I2C, SD0, SD1, McBSP0, CLKOUTs
  DEVICE_pinmuxControl(4,0xFFFFFFFF,0x00000000);  // MMC/SD0 instead of MS, SPI0

  // System PLL setup
  if (status == E_PASS) status |= DEVICE_PLL1Init(PLL1_Mult);
  
  // DDR PLL setup
  if (status == E_PASS) status |= DEVICE_PLL2Init();

  // DDR2 module setup
  if (status == E_PASS) status |= DEVICE_DDR2Init();
#endif
			
  // AEMIF Setup
  if (status == E_PASS) status |= DEVICE_EMIFInit();

  temp = AEMIF->NANDERRADD1;

  // UART0 Setup
  if (status == E_PASS) status |= DEVICE_UART0Init();

  // TIMER0 Setup
  if (status == E_PASS) status |= DEVICE_TIMER0Init();
	
  // I2C0 Setup
  if (status == E_PASS) status |= DEVICE_I2C0Init();

  return status;
}

void DEVICE_LPSCTransition(Uint8 module, Uint8 domain, Uint8 state)
{
  // Wait for any outstanding transition to complete
  while ( (PSC->PTSTAT) & (0x00000001 << domain) );
  
  // If we are already in that state, just return
  if (((PSC->MDSTAT[module]) & 0x1F) == state) return;
    
  // Perform transition
  PSC->MDCTL[module] = ((PSC->MDCTL[module]) & (0xFFFFFFE0)) | (state);
  PSC->PTCMD |= (0x00000001 << domain);

  // Wait for transition to complete
  while ( (PSC->PTSTAT) & (0x00000001 << domain) );
  
  // Wait and verify the state
  while (((PSC->MDSTAT[module]) & 0x1F) != state);	
}

void DEVICE_pinmuxControl(Uint32 regOffset, Uint32 mask, Uint32 value)
{
  SYSTEM->PINMUX[regOffset] &= ~mask;
  SYSTEM->PINMUX[regOffset] |= (mask & value);
}

DEVICE_BootMode DEVICE_bootMode( void )
{
  return (DEVICE_BootMode) ((SYSTEM->BOOTCFG & DEVICE_BOOTCFG_BOOTMODE_MASK) >> DEVICE_BOOTCFG_BOOTMODE_SHIFT);
}

DEVICE_BusWidth DEVICE_emifBusWidth( void )
{
  if ( ( (SYSTEM->BOOTCFG & DEVICE_BOOTCFG_EMIFWIDTH_MASK) >> DEVICE_BOOTCFG_EMIFWIDTH_SHIFT) & 0x1 )
  {
    return DEVICE_BUSWIDTH_8BIT;
  }
  else
  {
    return DEVICE_BUSWIDTH_16BIT;
  }
}

void DEVICE_PSCInit()
{
  Uint32 i;
  
  //***************************************
  // Do always on power domain transitions
  //***************************************
  while ((PSC->PTSTAT) & 0x00000001);
 
  for( i = LPSC_VPSS_MAST ; i <= LPSC_ARM ; i++ )
    PSC->MDCTL[i] = (PSC->MDCTL[i] & 0xFFFFFFE0) | PSC_ENABLE;

  PSC->MDCTL[LPSC_VPSS_DAC] = (PSC->MDCTL[LPSC_VPSS_DAC] & 0xFFFFFFE0) | PSC_ENABLE;

  // Set EMURSTIE to 1 on the following
  PSC->MDCTL[LPSC_VPSS_MAST]    |= EMURSTIE_MASK;
  PSC->MDCTL[LPSC_VPSS_SLV]     |= EMURSTIE_MASK;
  PSC->MDCTL[LPSC_TIMER3]       |= EMURSTIE_MASK;
  PSC->MDCTL[LPSC_SPI1]         |= EMURSTIE_MASK;
  PSC->MDCTL[LPSC_USB]          |= EMURSTIE_MASK;
  PSC->MDCTL[LPSC_PWM3]         |= EMURSTIE_MASK;
  PSC->MDCTL[LPSC_DDR2]         |= EMURSTIE_MASK;
  PSC->MDCTL[LPSC_AEMIF]        |= EMURSTIE_MASK;
  PSC->MDCTL[LPSC_MMC_SD0]      |= EMURSTIE_MASK;
  PSC->MDCTL[LPSC_ASP0]         |= EMURSTIE_MASK;
  PSC->MDCTL[LPSC_GPIO]         |= EMURSTIE_MASK;
  PSC->MDCTL[LPSC_VPSS_DAC]     |= EMURSTIE_MASK;

  // Do Always-On Power Domain Transitions
  PSC->PTCMD |= 0x00000001;
  while ((PSC->PTSTAT) & 0x00000001);

  // Clear EMURSTIE to 0 on the following
  PSC->MDCTL[LPSC_VPSS_MAST]    &= (~EMURSTIE_MASK);
  PSC->MDCTL[LPSC_VPSS_SLV]     &= (~EMURSTIE_MASK);
  PSC->MDCTL[LPSC_TIMER3]       &= (~EMURSTIE_MASK);
  PSC->MDCTL[LPSC_SPI1]         &= (~EMURSTIE_MASK);
  PSC->MDCTL[LPSC_USB]          &= (~EMURSTIE_MASK);
  PSC->MDCTL[LPSC_PWM3]         &= (~EMURSTIE_MASK);
  PSC->MDCTL[LPSC_DDR2]         &= (~EMURSTIE_MASK);
  PSC->MDCTL[LPSC_AEMIF]        &= (~EMURSTIE_MASK);
  PSC->MDCTL[LPSC_MMC_SD0]      &= (~EMURSTIE_MASK);
  PSC->MDCTL[LPSC_ASP0]         &= (~EMURSTIE_MASK);
  PSC->MDCTL[LPSC_GPIO]         &= (~EMURSTIE_MASK);
  PSC->MDCTL[LPSC_VPSS_DAC]     &= (~EMURSTIE_MASK);
}


Uint32 DEVICE_PLL1Init(Uint32 PLLMult)
{
  Uint32 PLLDiv3_ratio = 0,PLLDiv4_ratio = 0;

  if (PLLMult == 0)
    return E_FAIL;
  
  // Calculate PLL divder ratio for divider 3 (feeds VPBE)
  while ( (PLLDiv3_ratio*27000000) < (24000000*(PLLMult>>3)) )
  {
    PLLDiv3_ratio++;
  }
  
  // Check to make sure we can supply 27 MHz VPBE clock
  if ((PLLDiv3_ratio * 27000000) != (24000000*(PLLMult>>3)))
    return E_FAIL;
  
  // See the device datasheet for more info (must be 2 or 4)
  PLLDiv4_ratio = 4;
               
  // Step 1 - Set PLL1 clock input to internal osc.
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_CLKMODE_MASK);	
		
  // Step 2 - Set PLL to bypass, then wait for PLL to stabilize
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLENSRC_MASK);
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLEN_MASK);
  UTIL_waitLoop( 150 );
    
  // Step 3 - Reset PLL
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLRST_MASK;
    
  // Step 4 - Disable PLL
  // Step 5 - Powerup PLL
  // Step 6 - Enable PLL
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLDIS_MASK;         // Disable PLL
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLPWRDN_MASK);    // Power up PLL
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLDIS_MASK);      // Enable PLL        
    
  // Step 7 - Wait for PLL to stabilize
  UTIL_waitLoop( 150 );
    
  // Step 8 - Load PLL multiplier and dividers, enable dividers as needed
  PLL1->PLLM = (PLLMult - 1) & 0xff;                // 432MHz or 540MHz (depends on PLLMult)
  PLL1->PLLDIV1 |= DEVICE_PLLDIV_EN_MASK;           // SYSCLK1 (ARM) fixed at 216MHz or 270MHz
  PLL1->PLLDIV2 |= DEVICE_PLLDIV_EN_MASK;           // SYSCLK2 (Peripherals) fixed at 432MHz/4 = 108MHz 
  PLL1->PLLDIV3 = DEVICE_PLLDIV_EN_MASK | (PLLDiv3_ratio-1);   // SYSCLK3 at 27MHz (VPBE)
  PLL1->PLLDIV4 = DEVICE_PLLDIV_EN_MASK | (PLLDiv4_ratio-1);   // SYSCLK4 (VPSS) at 432MHz/4 = 108MHz
  UTIL_waitLoop( 150 );
       
  // Step 9 - Set the processor AIM wait state to 1 and PLL1 post-divider equal to 1
  SYSTEM->MISC &= ~(DEVICE_MISC_PLL1POSTDIV_MASK | DEVICE_MISC_AIMWAITST_MASK);
    
  // Step 10 - Bring PLL Out of Reset
  PLL1->PLLCMD |= DEVICE_PLLCMD_GOSET_MASK;

  // Step 10 - Wait for phase alignment
  while( ( PLL1->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK ) );
    
  // Step 11 - Wait for PLL to reset ( ~5 usec )
  UTIL_waitLoop( 24*5*(PLLMult>>3) );
  //UTIL_waitLoop(2000);
	
  // Step 12 - Release from reset
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLRST_MASK);

  // Step 13 - Wait for PLL to re-lock ( 8000 ref clk cycles )
  UTIL_waitLoop( 8000 );
    
  // Step 13 - Switch out of BYPASS mode
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLEN_MASK;

  return E_PASS;
}


Uint32 DEVICE_PLL2Init()
{
  Bool PllIsPoweredUp = ( PLL2->PLLCTL & 0x0002 ) >> 1;
          
  // Step 1 - Set PLL2 clock input to internal osc. 
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_CLKMODE_MASK);
	
  // Step 2 - Set PLL to bypass, then wait for PLL to stabilize
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLENSRC_MASK);
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLEN_MASK);
  
  UTIL_waitLoop( 4*(PLL1_Mult>>3) );
  //UTIL_waitLoop( 150 );
	
  // Step 3 - Reset PLL
  PLL2->PLLCTL |= DEVICE_PLLCTL_PLLRST_MASK;
  
  // Step 4 - Disable PLL
  // Step 5 - Powerup PLL
  // Step 6 - Enable PLL
  if ( PllIsPoweredUp )
  {
    PLL2->PLLCTL |= DEVICE_PLLCTL_PLLDIS_MASK;         // Disable PLL
    PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLPWRDN_MASK);      // Power up PLL
    PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLDIS_MASK);        // Enable PLL        
  }
  else
  {
    PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLDIS_MASK);        // Enable PLL
  }
  // Step 7 - Wait for PLL to stabilize
  UTIL_waitLoop( 150 );
    
  // Step 8 - Load PLL multiplier and divisors
  PLL2->PLLM = (PLL2_Mult-1) & 0xFF;              // PLL2 fixed at 342 MHz
  PLL2->PLLDIV1 |= DEVICE_PLLDIV_EN_MASK;         // SYSCLK1 = 342MHz /1 = 342 MHz (PHY rate) = 171 MHZ DDR2 rate

  // Step 9 - Start PLL changes
  PLL2->PLLCMD |= DEVICE_PLLCMD_GOSET_MASK;

  // Step 10 - Wait for phase alignment
  while( ( PLL2->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK ) );
    
  // Step 11 - Wait for PLL to reset ( ~5 usec )
  UTIL_waitLoop( 24*5*(PLL1_Mult>>3) );
  //UTIL_waitLoop( 2000 );
	
  // Step 12 - Release from reset
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLRST_MASK);

  // Step 13 - Wait for PLL to re-lock ( 8000 ref clk cycles )
  UTIL_waitLoop( 8000*(PLL1_Mult>>3) );
  //UTIL_waitLoop( 2000 );
    
  // Step 13 - Switch out of BYPASS mode
  PLL2->PLLCTL |= DEVICE_PLLCTL_PLLEN_MASK;

  return E_PASS;
}


Uint32 DEVICE_DDR2Init()
{
  DEVICE_LPSCTransition(LPSC_DDR2,PD0,PSC_ENABLE);
  
  // DO VTP calibration
  SYSTEM->VTPIOCR &= ~( DEVICE_VTPIOCR_PWRDN_MASK | 
                        DEVICE_VTPIOCR_LOCK_MASK |
                        DEVICE_VTPIOCR_CLR_MASK );  // Clear CLR & PWRDN & LOCK bits

  // Set CLR (bit 13)
  SYSTEM->VTPIOCR |= DEVICE_VTPIOCR_CLR_MASK;       

  // Wait for ready 
  while( !(SYSTEM->VTPIOCR & DEVICE_VTPIOCR_READY_MASK) );

  // Set bit VTP_IO_READY(bit 14)
  SYSTEM->VTPIOCR |= DEVICE_VTPIOCR_VTPIOREADY_MASK;  
  
  // Set bit LOCK(bit 7) and  PWRSAVE  (bit 8)
  SYSTEM->VTPIOCR |= (DEVICE_VTPIOCR_PWRSAVE_MASK | DEVICE_VTPIOCR_LOCK_MASK);  
  
  // Powerdown VTP as it is locked  (bit 6)
  SYSTEM->VTPIOCR |= DEVICE_VTPIOCR_PWRDN_MASK;
  
  // Wait for calibration to complete 
  UTIL_waitLoop( 150 );
    
  // DDR Timing Setup for Micron MT47H64M16BT-37E @ 171 MHz  
 
  // Setup the read latency
  //External DQS gating enabled
  //DDR->DDRPHYCR = 0x50006494;
  DDR->DDRPHYCR = 0x50006400 | (0xFF & DDR_READ_Latency);
  
  DDR->PBBPR = 0x000000FE;

  // Set the refresh rate
  //DDR->SDRCR = 0x00000535;
  DDR->SDRCR = (0x0000FFFF & DDR_RR);
  
  // Set TIMUNLOCK bit, CAS LAtency, banks, 1024-word page size 
  //DDR->SDBCR = 0x0000C632;
  DDR->SDBCR =  0x00008000          |
                (DDR_NM << 14)      |
                (DDR_CL << 9)       |
                (DDR_IBANK << 4)    |
                (DDR_PAGESIZE <<0);
	
  // Program timing registers 
  //DDR->SDTIMR = 0x2A923249;
  DDR->SDTIMR =   (DDR_T_RFC << 25) |              
                  (DDR_T_RP << 22)  |
                  (DDR_T_RCD << 19) |
                  (DDR_T_WR << 16)  |
                  (DDR_T_RAS << 11) |
                  (DDR_T_RC << 6)   |
                  (DDR_T_RRD << 3)  |
                  (DDR_T_WTR << 0);
                  
  //DDR->SDTIMR2 = 0x3C17C763;
  DDR->SDTIMR2 =  (DDR_T_RASMAX << 27)  |
                  (DDR_T_XP << 25)      |
                  (DDR_T_XSNR << 16)    |
                  (DDR_T_XSRD << 8)     |
                  (DDR_T_RTP << 5)      |
                  (DDR_T_CKE << 0);
    
    
  // Clear the TIMUNLOCK bit
  //DDR->SDBCR = 0x00004632;
  DDR->SDBCR =  0x00000000          |
                (DDR_NM << 14)      |
                (DDR_CL << 9)       |
                (DDR_IBANK << 4)    |
                (DDR_PAGESIZE <<0);

  // Set the DDR2 to synreset, then enable it again
  DEVICE_LPSCTransition(LPSC_DDR2,PD0,PSC_SYNCRESET);
  DEVICE_LPSCTransition(LPSC_DDR2,PD0,PSC_ENABLE);

  
  return E_PASS;
}

Uint32 DEVICE_EMIFInit()
{
#if 0
  Uint32 currCE = 0;
  Uint32 width;
  VUint32 *ABCR = NULL;

  // Set width to 8 or 16
  width = (DEVICE_emifBusWidth() == DEVICE_BUSWIDTH_8BIT)? 0 : 1;

  // Set PINMUX for EMIF use
  DEVICE_pinmuxControl(2,DEVICE_PINMUX_EMIF_MASK,DEVICE_PINMUX_EMIF_EN);

  // FIXME
  AEMIF->AWCCR &= ( ~(DEVICE_EMIF_AWCC_WAITSTATE_MASK) | 0xFF );

  ABCR = &(AEMIF->AB1CR);

  while (currCE < DEVICE_EMIF_NUMBER_CE_REGION)
  {
    ABCR[currCE++] = 0x3FFFFFFC | width;      // Adjust for quicker access times   
  }
#endif

  AEMIF->AWCCR = 0xFF;

  // FIXME
  AEMIF->A1CR = 0x40400204;
  AEMIF->NANDFCR |= 1;

  /* Setup CE1 - 16-bit normal async, 9.26ns/cycle */
    //AEMIF->AB2CR = 0x0050043d;//0x00a00505;  // Setup=0, Strobe=A, Hold=0, TA=1, 16-bit
  AEMIF->A2CR = 0x00a00505;  // Setup=0, Strobe=A, Hold=0, TA=1, 16-bit
  AEMIF->NANDFCR &= ~2;

  return E_PASS;
}
 
Uint32 DEVICE_UART0Init()
{
#if 0
  Uint16 divider;

  // Reset and then power on the UART0 via PSC
  DEVICE_LPSCTransition(LPSC_UART0,PD0,PSC_SYNCRESET);
  DEVICE_LPSCTransition(LPSC_UART0,PD0,PSC_ENABLE);

  // Put UART in reset
  UART0->PWREMU_MGNT = 0;
  UTIL_waitLoop(10000);

  // Set free running
  UART0->PWREMU_MGNT = 0x0001;

  // Set DLAB bit - allows setting of clock divisors
  UART0->LCR |= 0x80;
  UTIL_waitLoop(100);

  //divider = 24000000/(16*115200) = 13.02 => 13 = 0x0D => 24000000/(16*13) = 115384 (0.16% error)
  //divider = DEVICE_OSC_FREQ / (DEVICE_UART0_DESIRED_BAUD * DEVICE_UART0_OVERSAMPLE_CNT);
  //dividerX2 = (2*DEVICE_OSC_FREQ) / (DEVICE_UART0_DESIRED_BAUD * DEVICE_UART0_OVERSAMPLE_CNT);
  //if (divider*2 < dividerX2) divider++;
  divider = 0x0D;

  UART0->DLL = divider & 0xFF;
  UART0->DLH = (divider >> 8) & 0xFF;

  // Enable, clear and reset FIFOs
  UART0->FCR = 0x0;
  UTIL_waitLoop(100);

  UART0->FCR = 0xC1;
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
  UART0->PWREMU_MGNT |= 0x6001;
  UTIL_waitLoop(100); 

  if ( (UART0->IIR & 0xC0) != 0xC0 )
    return E_FAIL;
                                                                               
  UTIL_waitLoop(100);

  // Disable the timer 
  TIMER0->TCR = 0x00000000;
  
  // Set to 64-bit GP Timer mode, enable TIMER12 & TIMER34
  TIMER0->TGCR = 0x00000003;

  // Reset timers to zero 
  TIMER0->TIM34 = 0x00000000;
  TIMER0->TIM12 = 0x00000000;

  // Set timer period (5 second timeout = (24000000 * 5) cycles = 0x080BEFC0) 
  TIMER0->PRD34 = 0x00000000;
  TIMER0->PRD12 = 0x07270E00;
#endif

  UART0->PWREMU_MGNT = 0;         // Reset UART TX & RX components

  UTIL_waitLoop( 100 );

  UART0->DLL = 0xd;               // Set baud rate
  UART0->DLH = 0;

  UART0->FCR = 0x0007;            // Clear UART TX & RX FIFOs
  UART0->FCR = 0x0000;            // Non-FIFO mode
  UART0->IER = 0x0007;            // Enable interrupts
  
  UART0->LCR = 0x0003;            // 8-bit words,
                                  // 1 STOP bit generated,
                                  // No Parity, No Stick paritiy,
                                  // No Break control
  
  UART0->MCR = 0x0000;            // RTS & CTS disabled,
                                  // Loopback mode disabled,
                                  // Autoflow disabled

  UART0->PWREMU_MGNT = 0xE001;    // Enable TX & RX componenets
        
  return E_PASS;
}

Uint32 DEVICE_I2C0Init()
{
#if 0
  Uint32 iCLK = 0;
  Uint32 iPSC = 2;
  Uint32 D = 5;
         
  // Enable the Xmt, Master Mode, free running, 7-bit address, 8-bit words, no DLB
  I2C0->ICMDR =  I2C_ICMDR_MST |       // Set MST - Master mode
                 I2C_ICMDR_TRX |       // Set TRX - Transmitter
                 I2C_ICMDR_FRE;
  UTIL_waitLoop(1000);

  // Set the DM648 address
  I2C0->ICOAR = DEVICE_I2C_OWN_ADDRESS & 0xFF;

  // Set Default I2C High and Low Clock Hold
  // Set prescalar to 2 (Scaled clock = input clk / PSC+1)
  // Input clock is 24MHz
  // Scaled clock will be 8MHz
  I2C0->ICPSC = (Uint32)(0xFF & iPSC);
  //iCLK = (24000000)/((2+1)*DEVICE_I2C_TARGET_FREQ*2) - D;
  iCLK = 20-D;
  I2C0->ICCLKH = (Uint32)(0xFF & iCLK);
  I2C0->ICCLKL = (Uint32)(0xFF & iCLK);

  // Enable the Xmt, Master Mode, free running, 7-bit address, 8-bit words, no DLB
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
#endif

  I2C0->ICMDR   = 0;                // Reset I2C
  I2C0->ICPSC   = 26;               // Config prescaler for 27MHz
  I2C0->ICCLKL  = 20;               // Config clk LOW for 20kHz
  I2C0->ICCLKH  = 20;               // Config clk HIGH for 20kHz
  I2C0->ICMDR   |= I2C_ICMDR_IRS;   // Release I2C from reset

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
  // Put timer into reset
  TIMER0->EMUMGT_CLKSPD = 0x00000003;
  TIMER0->TCR           = 0x00000000;
  
  // Enable TINT0, TINT1 interrupt
  TIMER0->INTCTL_STAT   = 0x00000001;
	
  // // Set to 64-bit GP Timer mode, enable TIMER12 & TIMER34
  TIMER0->TGCR = 0x00000003;

  // Reset timers to zero 
  TIMER0->TIM12 = 0x00000000;
  TIMER0->TIM34 = 0x00000000;
  
  // Set timer period (5 second timeout = (24000000 * 5) cycles = 0x07270E00) 
  TIMER0->PRD34 = 0x00000000;
  TIMER0->PRD12 = 0x07270E00;

  return E_PASS;
}

void DEVICE_TIMER0Start(void)
{
  // Clear interrupt
  AINTC->IRQ1   |=  0x00000001;

  // Put timer in reset
  TIMER0->TGCR  =   0x00000000;

  // Reset timer count to zero 
  TIMER0->TIM12 =   0x00000000;

  // Setup for one-shot mode
  TIMER0->TCR   =   0x00000040;

  // Start TIMER12
  TIMER0->TGCR  = 0x00000005;
}

void DEVICE_TIMER0Stop(void)
{
  // Clear interrupt
  AINTC->IRQ1   |=  0x00000001;

  // Put timer in reset
  TIMER0->TCR   = 0x00000000;
  TIMER0->TGCR  = 0x00000000;

  // Reset timer count to zero 
  TIMER0->TIM12 = 0x00000000;
}

Uint32 DEVICE_TIMER0Status(void)
{
  return ((AINTC->IRQ1)&0x1);
}


/************************************************************
* Local Function Definitions                                *
************************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/




