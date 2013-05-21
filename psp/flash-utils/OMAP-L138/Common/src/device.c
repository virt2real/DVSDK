/* --------------------------------------------------------------------------
  FILE        : device.c
  PURPOSE     : Device (chip) specific initialization function
  PROJECT     : DM643x Booting and Flashing
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

/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern __FAR__ Uint32 DDRStart;


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

  // For Micron MT47H64M16BT-37E @ 162 MHz
  static const Uint8 DDR_NM = 0;                                               
  static const Uint8 DDR_CL = 3;                                               
  static const Uint8 DDR_IBANK = 3;                                            
  static const Uint8 DDR_PAGESIZE = 2;                                         
  static const Uint8 DDR_T_RFC = 20;                                           
  static const Uint8 DDR_T_RP = 2;                                             
  static const Uint8 DDR_T_RCD = 2;                                            
  static const Uint8 DDR_T_WR = 2;                                             
  static const Uint8 DDR_T_RAS = 6;                                            
  static const Uint8 DDR_T_RC = 8;                                             
  static const Uint8 DDR_T_RRD = 2;                                            
  static const Uint8 DDR_T_WTR = 1;                                            
  static const Uint8 DDR_T_XSNR = 22;                                          
  static const Uint8 DDR_T_XSRD = 199;                                         
  static const Uint8 DDR_T_RTP = 1;                                            
  static const Uint8 DDR_T_CKE = 2;                                            
  static const Uint16 DDR_RR = 1264;                                           
  static const Uint8 DDR_READ_Latency = 5;

  static const Uint32 PLL1_Mult = DEVICE_PLL1_MULTIPLIER;
  static const Uint32 PLL2_Mult = DEVICE_PLL2_MULTIPLIER;    


/************************************************************
* Global Variable Definitions                               *
************************************************************/

const String devString = "OMAP-L1x8";

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
  if (status == E_PASS) status |= DEVICE_PLL1Init(DEVICE_PLL1_MULTIPLIER);
  
  // DDR PLL Setup
  if (status == E_PASS) status |= DEVICE_PLL2Init(DEVICE_PLL1_MULTIPLIER);
  
  // DDR2 Timing Setup
  if (status == E_PASS) status |= DEVICE_DDR2Init();
#endif

  // AEMIF Setup
  if (status == E_PASS) status |= DEVICE_EMIFInit();

  // UART0 Setup
  if (status == E_PASS) status |= DEVICE_UART0Init();

  // TIMER0 Setup
  if (status == E_PASS) status |= DEVICE_TIMER0Init();

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
  SYSTEM->PINMUX[regOffset] &= ~mask;
  SYSTEM->PINMUX[regOffset] |= (mask & value);
}

DEVICE_BootMode DEVICE_bootMode( void )
{
  return (DEVICE_BootMode) ((SYSTEM->BOOTCFG & DEVICE_BOOTCFG_BOOTMODE_MASK) >> DEVICE_BOOTCFG_BOOTMODE_SHIFT); 
}

DEVICE_BusWidth DEVICE_emifBusWidth( void )
{
  if ( ((SYSTEM->BOOTCFG) & DEVICE_BOOTCFG_EMIFWIDTH_MASK) >> DEVICE_BOOTCFG_EMIFWIDTH_SHIFT)
    return DEVICE_BUSWIDTH_16BIT;
  else
    return DEVICE_BUSWIDTH_8BIT;
}

void DEVICE_PSCInit()
{                                                                    
  Uint32 i;
    
  while ((PSC->PTSTAT) & 0x00000001);

  for( i = LPSC_VPSS_MAST ; i <= LPSC_MCASP0 ; i++ )
    PSC->MDCTL[i] = (PSC->MDCTL[i] & 0xFFFFFFE0) | PSC_ENABLE;        

  for( i = LPSC_VLYNQ ; i <= LPSC_UART1 ; i++ )                    
    PSC->MDCTL[i] = (PSC->MDCTL[i] & 0xFFFFFFE0) | PSC_ENABLE;        
    
  for( i = LPSC_HECC ; i <= LPSC_TIMER1 ; i++ )                    
    PSC->MDCTL[i] = (PSC->MDCTL[i] & 0xFFFFFFE0) | PSC_ENABLE;        

  // Do Always-On Power Domain Transitions                         
  PSC->PTCMD |= 0x00000001;                                        
  while ((PSC->PTSTAT) & 0x00000001);                              

}                                                                    


Uint32 DEVICE_PLL1Init()
{                                                                   
  // Step 1 - Set PLL1 clock input to internal osc.
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_CLKMODE_MASK);	
		
  // Step 2 - Set PLL to bypass, then wait for PLL to stabilize
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLENSRC_MASK);
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLEN_MASK);
  UTIL_waitLoop( 32 );
    
  // Step 3 - Reset PLL
  PLL1->PLLCTL &= (~DEVICE_PLLCTL_PLLRST_MASK);
 
  // Step 4 - Disable PLL
  // Step 5 - Powerup PLL
  // Step 6 - Enable PLL
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLDIS_MASK;         // Disable PLL
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLPWRDN_MASK);    // Power up PLL
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLDIS_MASK);      // Enable PLL        
    
  // Step 7 - Wait for PLL to stabilize
  UTIL_waitLoop( 150 ); 
  
  // Step 8 - Load PLL multiplier and dividers, enable dividers as needed
  PLL1->PLLM = (PLL1_Mult - 1) & 0xff;          // 27Mhz * (21+1) = 594 MHz     
 			           
  // Step 10 - Bring PLL Out of Reset
  PLL1->PLLCMD |= DEVICE_PLLCMD_GOSET_MASK;

  // Step 10 - Wait for phase alignment
  while( ( PLL1->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK ) );
    
  // Step 11 - Wait for PLL to reset ( ~5 usec )
  UTIL_waitLoop( 256 );
	
  // Step 12 - Release from reset
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLRST_MASK;

  // Step 13 - Wait for PLL to re-lock ( 8000 ref clk cycles )
  UTIL_waitLoop( 8000 );
    
  // Step 13 - Switch out of BYPASS mode
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLEN_MASK;

  return E_PASS;
}                                                                   


Uint32 DEVICE_PLL2Init()                                                                      
{	                                                                                
  // 162 MHz DDR                                                                   
  Uint32 PLLDiv1_ratio = 12;                                                           
  Uint32 PLLDiv2_ratio = 2;                                                            

  // Step 1 - Set PLL2 clock input to internal osc. 
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_CLKMODE_MASK);    

  // Clear PLLENSRC bit and clear PLLEN bit for Bypass mode  
  // Step 2 - Set PLL to bypass, then wait for PLL to stabilize    
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLENSRC_MASK);
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLEN_MASK);
  UTIL_waitLoop(32*11);
  
    // Step 3 - Reset PLL
  PLL2->PLLCTL &= (~DEVICE_PLLCTL_PLLRST_MASK);
  
  // Step 4 - Disable PLL
  // Step 5 - Powerup PLL
  // Step 6 - Enable PLL
  PLL2->PLLCTL |= DEVICE_PLLCTL_PLLDIS_MASK;        // Disable PLL
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLPWRDN_MASK);   // Power up PLL
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLDIS_MASK);     // Enable PLL
  
  // Step 7 - Wait for PLL to stabilize
  UTIL_waitLoop( 150 );
  
  // Step 8 - Load PLL multiplier and divisors
  PLL2->PLLM = (PLL2_Mult-1) & 0xFF;                            // 27  Mhz * (23+1) = 648 MHz
  PLL2->PLLDIV1 = DEVICE_PLLDIV_EN_MASK | (PLLDiv1_ratio-1);    // 648 MHz / (11+1) = 54  MHz
  PLL2->PLLDIV2 = DEVICE_PLLDIV_EN_MASK | (PLLDiv2_ratio-1);    // 648 MHz / (1+1 ) = 324 MHz (the PHY DDR rate)
  
    // Step 10 - Bring PLL Out of Reset
  PLL1->PLLCMD |= DEVICE_PLLCMD_GOSET_MASK;

  // Step 10 - Wait for phase alignment
  while( ( PLL1->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK ) );
    
  // Step 11 - Wait for PLL to reset ( ~5 usec )
  UTIL_waitLoop( 256*11 );
	
  // Step 12 - Release from reset
  PLL1->PLLCTL |= (DEVICE_PLLCTL_PLLRST_MASK);

  // Step 13 - Wait for PLL to re-lock ( 8000 ref clk cycles )
  UTIL_waitLoop( 8000*(PLL1_Mult) );
    
  // Step 13 - Switch out of BYPASS mode
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLEN_MASK;

  return E_PASS;
}                                                                                    


Uint32 DEVICE_DDR2Init()                                                     
{
  Int32 tempVTP; 
  Uint32 *ddrStartPtr = (Uint32 *) &DDRStart;
    
  // Set the DDR2 to enable                                          
  DEVICE_LPSCTransition(LPSC_DDR2, PD0, PSC_ENABLE);

  // For Micron MT47H64M16BT-37E @ 162 MHz                           
  // Setup the read latency (CAS Latency + 3 = 6 (but write 6-1=5))  
  //DDR->DDRPHYCR = 0x50006405;                                      
  DDR->DDRPHYCR = 0x50006400 | DDR_READ_Latency;                     
  // Set TIMUNLOCK bit, CAS LAtency 3, 8 banks, 1024-word page size  
  //DDR->SDBCR = 0x00138632;                                         
  DDR->SDBCR = 0x00138000       |                                          
               (DDR_NM << 14)   |
               (DDR_CL << 9)    |
               (DDR_IBANK << 4) |
               (DDR_PAGESIZE <<0);
               
  // Program timing registers                                        
  //DDR->SDTIMR = 0x28923211;                                        
  DDR->SDTIMR = (DDR_T_RFC << 25) |                                  
                (DDR_T_RP << 22)  |                               
                (DDR_T_RCD << 19) |                               
                (DDR_T_WR << 16)  |                               
                (DDR_T_RAS << 11) |                               
                (DDR_T_RC << 6)   |                               
                (DDR_T_RRD << 3)  |                               
                (DDR_T_WTR << 0);                                 
  //DDR->SDTIMR2 = 0x0016C722;                                       
  DDR->SDTIMR2 = (DDR_T_XSNR << 16) |                                
                 (DDR_T_XSRD << 8)  |                             
                 (DDR_T_RTP << 5)   |                             
                 (DDR_T_CKE << 0);                                

  // Clear the TIMUNLOCK bit                                      
  DDR->SDBCR &= (~0x00008000);                                       

  // Set the refresh rate                                            
  DDR->SDRCR = DDR_RR;                                               

  // Dummy write/read to apply timing settings                       
  ddrStartPtr[0] = DEVICE_DDR2_TEST_PATTERN;                                      
  if (ddrStartPtr[0] == DEVICE_DDR2_TEST_PATTERN)                                 
  {
    ddrStartPtr[0] = 0x00000000;
  }

  // Set the DDR2 to syncreset                                       
  DEVICE_LPSCTransition(LPSC_DDR2, PD0, PSC_SYNCRESET);                          

  // Set the DDR2 to enable                                          
  DEVICE_LPSCTransition(LPSC_DDR2, PD0, PSC_ENABLE);                             


  // ***************** DDR2 VTP Calibration ***************           
  DDR->VTPIOCR = 0x201F;        // Clear calibration start bit       
  DDR->VTPIOCR = 0xA01F;        // Set calibration start bit         

  UTIL_waitLoop(400);              // Wait for calibration to complete  

  SYSTEM->DDRVTPER = 0x1;       // DDRVTPR Enable register           

  tempVTP = 0x3FF & DDRVTPR;    // Read calibration data             

  // Write calibration data to VTP Control register                  
  DDR->VTPIOCR = ((DDR->VTPIOCR) & 0xFFFFFC00) | tempVTP;            

  // Clear calibration enable bit                                    
  DDR->VTPIOCR = (DDR->VTPIOCR) & (~0x00002000);                     

  // DDRVTPR Enable register - disable DDRVTPR access                
  SYSTEM->DDRVTPER = 0x0;
  
  return E_PASS;                                                              
}                                                                   

Uint32 DEVICE_EMIFInit()
{
  Uint32 width = 0;
  VUint32 *ABCR = NULL;
  Uint32 currCE = 0;

  // Setup pinmux for emif
  if (DEVICE_emifBusWidth() == DEVICE_BUSWIDTH_8BIT)
  {
    DEVICE_pinmuxControl( 0, 0xFFFFFFFF, 0x00148001 );
  }
  else
  {
    DEVICE_pinmuxControl( 0, 0xFFFFFFFF, 0x00148002 );
  }

  ABCR = &(AEMIF->AB1CR);

  width = (DEVICE_emifBusWidth() == DEVICE_BUSWIDTH_8BIT)?0:1;

  while (currCE < DEVICE_EMIF_NUMBER_CE_REGION)
  {
    ABCR[currCE++] = 0x3FFFFFFC | width;      // Adjust for quicker access times   
  }

  return E_PASS;
}
 
Uint32 DEVICE_UART0Init()                                                             
{		                                                                     
  // The DM643x pin muxing registers must be set for UART0 use.
  DEVICE_pinmuxControl(1,0x00000100,0x00000100);
  SYSTEM->VDD3P3V_PWDN &= ~(1u << 10);

  //DEVICE_LPSCTransition(LPSC_UART0,PD0,PSC_ENABLE);

  UART0->PWREMU_MGNT = 0;
  UTIL_waitLoop(100);

  // Set DLAB bit - allows setting of clock divisors                           
  UART0->LCR |= 0x80;                                                          

  //divider = 27000000/(16*115200) = 14.64 => 15 = 0x0F (2% error is OK)       
  UART0->DLL = 0x0F;                                                           
  UART0->DLH = 0x00;                                                           

  // Enable, clear and reset FIFOs
  UART0->FCR |= 0x07;
  UTIL_waitLoop(100);

  UART0->FCR |= 0xC0;
  UTIL_waitLoop(100);

  // Enable interrupts
  UART0->IER = 0x07;
  UTIL_waitLoop(100);

  // Set word length to 8 bits, clear DLAB bit
  UART0->LCR = 0x03;
  UTIL_waitLoop(100);

  // Disable autoflow control
  UART0->MCR = 0x00;
  UTIL_waitLoop(100);

  // Enable receiver, transmitter, st to run.
  UART0->PWREMU_MGNT |= 0x6001;
  UTIL_waitLoop(100);

  if ((UART0->IIR & 0xC0) != 0xC0)
    return E_FAIL;
    
  UTIL_waitLoop(100);
  
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

/* --------------------------------------------------------------------------
    HISTORY
        v1.01 - 22-Feb-2008 - Init releas
        v1.02 - 21-Apr-2008 - Fix to DEVICE_emifBusWidth function to return correct result
            
 ----------------------------------------------------------------------------- */

