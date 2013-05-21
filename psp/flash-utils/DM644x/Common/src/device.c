/* --------------------------------------------------------------------------
  FILE        : device.c                                                   
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : This file provides low-level, device-specific init functions
                for use the DM644x device.
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

extern __FAR__ Uint32 EXTERNAL_RAM_START;


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

#if defined(DM6441_LV)
    // For Micron MT47H64M16BT-37E @ 135 MHz   
    static const Uint8 DDR_NM = 0;
    static const Uint8 DDR_CL = 3;
    static const Uint8 DDR_IBANK = 3;
    static const Uint8 DDR_PAGESIZE = 2;
    static const Uint8 DDR_T_RFC = 17;
    static const Uint8 DDR_T_RP = 2;
    static const Uint8 DDR_T_RCD = 2;
    static const Uint8 DDR_T_WR = 2;
    static const Uint8 DDR_T_RAS = 5;
    static const Uint8 DDR_T_RC = 7;
    static const Uint8 DDR_T_RRD = 1;
    static const Uint8 DDR_T_WTR = 1;
    static const Uint8 DDR_T_XSNR = 18;
    static const Uint8 DDR_T_XSRD = 199;
    static const Uint8 DDR_T_RTP = 1;
    static const Uint8 DDR_T_CKE = 2;
    static const Uint16 DDR_RR = 1264;
    static const Uint8 DDR_READ_Latency = 5;
    
    static const Uint32 PLL2_Mult = 20;
    static const Uint32 PLL2_Div1 = 10;
    static const Uint32 PLL2_Div2 = 2;
#elif defined(DM644x_810MHz)
    //// For Micron MT47H64M16BT-37E @ 189 MHz
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
    static const Uint16 DDR_RR = 1229;
    static const Uint8 DDR_READ_Latency = 5; 
    
    static const Uint32 PLL2_Mult = 28;
    static const Uint32 PLL2_Div1 = 14;
    static const Uint32 PLL2_Div2 = 2;
#else
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
    static const Uint16 DDR_RR = 1053;
    static const Uint8 DDR_READ_Latency = 5; 
    
    static const Uint32 PLL2_Mult = 24;
    static const Uint32 PLL2_Div1 = 12;
    static const Uint32 PLL2_Div2 = 2;
#endif

#if defined(DM6441_LV)
    static const Uint32 PLL1_Mult = 15;  // DSP=405 MHz
#elif defined(DM6441)
    static const Uint32 PLL1_Mult = 19;  // DSP=513 MHz  
#elif defined(DM644x_810MHz)
    static const Uint32 PLL1_Mult = 30;  // DSP=810 MHz
#else
    static const Uint32 PLL1_Mult = 22;  // DSP=594 MHz
#endif   

/************************************************************
* Global Variable Definitions                               *
************************************************************/

#if defined(DM6441_LV)
  const String devString = "DM6441_LV";
#elif defined(DM6441)
  const String devString = "DM6441";
#elif defined(DM644x_810MHz)
  const String devString = "DM644x_810MHz";
#else
  const String devString = "DM644x";
#endif     

/************************************************************
* Global Function Definitions                               *
************************************************************/

Uint32 DEVICE_init()
{
  Uint32 status = E_PASS;
   
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
  // System PSC Setup
  DEVICE_PSCInit();

  // System PLL Setup
  if (status == E_PASS) status |= DEVICE_PLL1Init(PLL1_Mult);
  
  // DDR PLL setup
  if (status == E_PASS) status |= DEVICE_PLL2Init();
  
  // DDR2 module setup
  if (status == E_PASS) status |= DEVICE_DDR2Init();
#endif
      
  // AEMIF Setup
  if (status == E_PASS) status |= DEVICE_EMIFInit();

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
    return DEVICE_BUSWIDTH_16BIT;
  }
  else
  {
    return DEVICE_BUSWIDTH_8BIT;
  }
}

void DEVICE_PSCInit()
{
  Uint32 i;

  //***************************************
  // Do always on power domain transitions
  //***************************************
  while ((PSC->PTSTAT) & 0x00000001);

  for( i = LPSC_VPSS_MAST ; i < LPSC_1394 ; i++ )
    PSC->MDCTL[i] |= PSC_ENABLE; // Enable

  // Do this for enabling a WDT initiated reset this is a workaround
  // for a chip bug.  Not required under normal situations 
  // Copied from U-boot boards/DaVinci/platform.S and convereted to C
  //      LDR R6, P1394
  //      MOV R10, #0x0  
  //      STR R10, [R6]        
  PSC->MDCTL[LPSC_1394] = PSC_SWRSTDISABLE;
    
  for( i = LPSC_USB ; i < LPSC_DSP ; i++ )
    PSC->MDCTL[i] |= PSC_ENABLE;

  // Set EMURSTIE to 1 on the following
  PSC->MDCTL[LPSC_VPSS_SLV]   |= 0x0203;
  PSC->MDCTL[LPSC_EMAC0]      |= 0x0203;
  PSC->MDCTL[LPSC_EMAC1]      |= 0x0203;
  PSC->MDCTL[LPSC_MDIO]       |= 0x0203;
  PSC->MDCTL[LPSC_USB]        |= 0x0203;
  PSC->MDCTL[LPSC_ATA]        |= 0x0203;
  PSC->MDCTL[LPSC_VLYNQ]      |= 0x0203;
  PSC->MDCTL[LPSC_HPI]        |= 0x0203;
  PSC->MDCTL[LPSC_DDR2]       |= 0x0203;
  PSC->MDCTL[LPSC_AEMIF]      |= 0x0203;
  PSC->MDCTL[LPSC_MMCSD]      |= 0x0203;
  PSC->MDCTL[LPSC_MEMSTK]     |= 0x0203;
  PSC->MDCTL[LPSC_ASP]        |= 0x0203;
  PSC->MDCTL[LPSC_GPIO]       |= 0x0203;
  PSC->MDCTL[LPSC_IMCOP]      |= 0x0203;

  // Do Always-On Power Domain Transitions
  PSC->PTCMD |= 0x00000001;
  while ((PSC->PTSTAT) & 0x00000001);

  // Clear EMURSTIE to 0 on the following
  PSC->MDCTL[LPSC_VPSS_SLV]   &= 0x0003;
  PSC->MDCTL[LPSC_EMAC0]      &= 0x0003;
  PSC->MDCTL[LPSC_EMAC1]      &= 0x0003;
  PSC->MDCTL[LPSC_MDIO]       &= 0x0003;
  PSC->MDCTL[LPSC_USB]        &= 0x0003;
  PSC->MDCTL[LPSC_ATA]        &= 0x0003;
  PSC->MDCTL[LPSC_VLYNQ]      &= 0x0003;
  PSC->MDCTL[LPSC_HPI]        &= 0x0003;
  PSC->MDCTL[LPSC_DDR2]       &= 0x0003;
  PSC->MDCTL[LPSC_AEMIF]      &= 0x0003;
  PSC->MDCTL[LPSC_MMCSD]      &= 0x0003;
  PSC->MDCTL[LPSC_MEMSTK]     &= 0x0003;
  PSC->MDCTL[LPSC_ASP]        &= 0x0003;
  PSC->MDCTL[LPSC_GPIO]       &= 0x0003;
  PSC->MDCTL[LPSC_IMCOP]      &= 0x0003;    

  //***************************************
  // Do DSP power domain transition
  //***************************************
  if ((PSC->PDSTAT1 & 0x1F) == 0)
  {
    // Set PSC force mode
    PSC->GBLCTL |= 0x1;    // May not be necessary 
    
    // Set NEXT bit to on
    PSC->PDCTL1 |= 0x1;
    
    // Clear external power indicator
    PSC->PDCTL1 &= ~(0x100);

    // Put the C64x+ Core into SwRstDisable
    PSC->MDCTL[LPSC_DSP] = (PSC->MDCTL[LPSC_DSP] & (~0x00000001F)) | 0x0;
    
    // Start power domain transition
    PSC->PTCMD |= 0x00000002;

    // Wait for external power control pending to assert
    while ( !((PSC->EPCPR) & (0x00000002)) );
        
    // Short the two power domain's voltage rails
    SYSTEM->CHP_SHRTSW = 0x1;

    // Clear the external power control bit
    PSC->EPCCR = 0x00000002;

    // Set external power good indicator
    PSC->PDCTL1 |= 0x0100;
    
    // Wait for domain transition to complete
    while ((PSC->PTSTAT) & (0x00000002));

    // Enable DSP
    PSC->MDCTL[LPSC_DSP] = (PSC->MDCTL[LPSC_DSP] & (~0x00000001F)) | PSC_ENABLE;
    // Hold DSP in reset on next power up
    PSC->MDCTL[LPSC_DSP] = (PSC->MDCTL[LPSC_DSP] & (~0x100));
    // Enable IMCOP
    PSC->MDCTL[LPSC_IMCOP] = (PSC->MDCTL[LPSC_IMCOP] & (~0x00000001F)) | PSC_ENABLE;

    // Start power domain transition
    PSC->PTCMD |= 0x00000002;

    // Wait for domain transition to complete
    while ((PSC->PTSTAT) & (0x00000002));
    
    // Wait until DSP local reset is asserted
    while ((PSC->MDSTAT[LPSC_DSP]) & (0x00000100));
    
    // Clear PSC force mode
    PSC->GBLCTL &= ~(0x00000001);
  }
}

Uint32 DEVICE_PLL2Init()
{  
  Bool PllIsPoweredUp = ( PLL2->PLLCTL & 0x0002 ) >> 1;
          
  // Step 1 - Set PLL2 clock input to internal osc. 
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_CLKMODE_MASK);
  
  // Clear PLLENSRC bit and clear PLLEN bit for Bypass mode 
  // Step 2 - Set PLL to bypass, then wait for PLL to stabilize
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLENSRC_MASK | DEVICE_PLLCTL_PLLEN_MASK);
  UTIL_waitLoop((Uint32)(32*(PLL1_Mult/2)));
  
  // Step 3 - Reset PLL
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLRST_MASK);
  
  // Step 4 - Disable PLL
  // Step 5 - Powerup PLL
  // Step 6 - Enable PLL
  if ( PllIsPoweredUp )
  {
    PLL2->PLLCTL |= DEVICE_PLLCTL_PLLDIS_MASK;           // Disable PLL
    PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLPWRDN_MASK);      // Power up PLL
    PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLDIS_MASK);        // Enable PLL        
  }
  else
  {
    PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLDIS_MASK);        // Enable PLL
  }
  
  // Step 7 - Wait for PLL to stabilize
  UTIL_waitLoop( 5000 );
    
  // Step 8 - Load PLL multiplier and divisors
  PLL2->PLLM      = PLL2_Mult-1;     // 27  Mhz * (23+1) = 648 MHz 
  PLL2->PLLDIV1   = PLL2_Div1-1;     // 648 MHz / (11+1) = 54  MHz
  PLL2->PLLDIV2   = PLL2_Div2-1;     // 648 MHz / (1+1 ) = 324 MHz (the PHY DDR rate)
    
  PLL2->PLLDIV2 |= DEVICE_PLLDIV_EN_MASK;          // Enable DDR divider  
  PLL2->PLLDIV1 |= DEVICE_PLLDIV_EN_MASK;          // Enable VPBE divider  

  // Step 9 - Start PLL changes
  PLL2->PLLCMD |= DEVICE_PLLCMD_GOSET_MASK;

  // Step 10 - Wait for phase alignment
  while( ( PLL2->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK ) );
    
  // Step 11 - Wait for PLL to reset ( 2000 cycles )
  UTIL_waitLoop(256*(PLL1_Mult/2));
  
  // Step 12 - Release from reset
  PLL2->PLLCTL |= DEVICE_PLLCTL_PLLRST_MASK;

  // Step 13 - Wait for PLL to re-lock ( 2000 cycles )
  UTIL_waitLoop(2000*(PLL1_Mult/2));      // Wait for locking
    
  // Step 13 - Switch out of BYPASS mode
  PLL2->PLLCTL |= DEVICE_PLLCTL_PLLEN_MASK;

  if ( (PLL2->PLLSTAT & DEVICE_PLLSTAT_LOCK_MASK) != 0)
    return E_PASS;
  else
    return E_FAIL;
}

Uint32 DEVICE_DDR2Init()
{
  VUint32 *ddrStart = (VUint32 *) &(EXTERNAL_RAM_START);
  Int32 tempVTP;
  
  // Set the DDR2 to enable
  DEVICE_LPSCTransition(LPSC_DDR2,PD0,PSC_ENABLE);
    
  // For Micron MT47H64M16BT-37E @ 162 MHz
  // Setup the read latency (CAS Latency + 3 = 6 (but write 6-1=5))
  DDR->DDRPHYCR = (0x50006400) | DDR_READ_Latency;
  // Set TIMUNLOCK bit, CAS LAtency 3, 8 banks, 1024-word page size 
  //DDR->SDBCR = 0x00138632;
  DDR->SDBCR =  0x00138000 |
                (DDR_NM << 14)   |
                (DDR_CL << 9)    |
                (DDR_IBANK << 4) |
                (DDR_PAGESIZE <<0);
  
  // Program timing registers 
  //DDR->SDTIMR = 0x28923211;
  DDR->SDTIMR =   (DDR_T_RFC << 25) |              
                  (DDR_T_RP << 22)  |
                  (DDR_T_RCD << 19) |
                  (DDR_T_WR << 16)  |
                  (DDR_T_RAS << 11) |
                  (DDR_T_RC << 6)   |
                  (DDR_T_RRD << 3)  |
                  (DDR_T_WTR << 0);
                  
  //DDR->SDTIMR2 = 0x0016C722;
  DDR->SDTIMR2 =  (DDR_T_XSNR << 16) |
                  (DDR_T_XSRD << 8)  |
                  (DDR_T_RTP << 5)   |
                  (DDR_T_CKE << 0);
    
    
  // Clear the TIMUNLOCK bit 
  DDR->SDBCR &= (~0x00008000);
  
  // Set the refresh rate
  DDR->SDRCR = DDR_RR;
  
  // Dummy write/read to apply timing settings
  *ddrStart = DEVICE_DDR2_TEST_PATTERN;
  if (*ddrStart) (*ddrStart)++;
  
  // Set the DDR2 to syncreset
  DEVICE_LPSCTransition(LPSC_DDR2,PD0,PSC_SYNCRESET);

  // Set the DDR2 to enable
  DEVICE_LPSCTransition(LPSC_DDR2,PD0,PSC_ENABLE);
       
  /***************** DDR2 VTP Calibration ****************/
  DDR->VTPIOCR = 0x201F;        // Clear calibration start bit
  DDR->VTPIOCR = 0xA01F;        // Set calibration start bit 
  
  UTIL_waitLoop(11*33);              // Wait for calibration to complete 
     
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

Uint32 DEVICE_PLL1Init(Uint32 PLLMult)
{
  Bool PllIsPoweredUp = ( PLL1->PLLCTL & 0x0002 ) >> 1;

  if (PLLMult == 0)
    return E_FAIL;
               
  // Step 1 - Set PLL1 clock input to internal osc.
  PLL1->PLLCTL &= (~0x00000100);  
    
  // Step 2 - Set PLL to bypass, then wait for PLL to stabilize
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLENSRC_MASK | DEVICE_PLLCTL_PLLEN_MASK);
  UTIL_waitLoop( 150 );
    
  // Step 3 - Reset PLL
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLRST_MASK);
    
  // Step 4 - Disable PLL
  // Step 5 - Powerup PLL
  // Step 6 - Enable PLL
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
    
  // Step 7 - Wait for PLL to stabilize
  UTIL_waitLoop( 5000 );
    
  // Step 8 - Load PLL multiplier
  PLL1->PLLM = (PLLMult - 1) & 0x3f;
    
  // Step 9 - Bring PLL Out of Reset
  PLL1->PLLCMD |= DEVICE_PLLCMD_GOSET_MASK;

  // Step 10 - Wait for phase alignment
  while( ( PLL1->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK ) != 0 );
    
  // Step 11 - Wait for PLL to reset ( 2000 cycles )
  UTIL_waitLoop( 2000 );
  
  // Step 12 - Release from reset
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLRST_MASK;

  // Step 13 - Wait for PLL to re-lock ( 2000 cycles )
  UTIL_waitLoop( 2000 );
    
  // Step 13 - Switch out of BYPASS mode
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLEN_MASK;

  if ( (PLL1->PLLSTAT & DEVICE_PLLSTAT_LOCK_MASK) != 0)
    return E_PASS;
  else
    return E_FAIL;
}

Uint32 DEVICE_EMIFInit()
{
  Uint32 currCE = 0, width = 0;
  VUint32 *ABCR = NULL;

  // Set width to 8 or 16
  width = (DEVICE_emifBusWidth() == DEVICE_BUSWIDTH_8BIT)? 0 : 1;
  
  // Set PINMUX for EMIF use
  DEVICE_pinmuxControl(0,DEVICE_PINMUX_EMIF_MASK,DEVICE_PINMUX_EMIF_EN);

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

  // Reset and then power on the UART0 via PSC
//  DEVICE_LPSCTransition(LPSC_UART0,PD0,PSC_SYNCRESET);
//  DEVICE_LPSCTransition(LPSC_UART0,PD0,PSC_ENABLE);

  // The DM644x pin muxing registers must be set for UART0 use
  DEVICE_pinmuxControl(1,DEVICE_PINMUX_UART0_MASK,DEVICE_PINMUX_UART0_EN);

  // Put UART in reset
   UART0->PWREMU_MGNT = 0;
   UTIL_waitLoop(10000);

  // Take out of reset, set free running
  UART0->PWREMU_MGNT = 0xE003;
                                                                            
   // Set DLAB bit - allows setting of clock divisors
   UART0->LCR |= 0x80;
   UTIL_waitLoop(100);
                                                                                
   //divider = 27000000/(16*115200) = 14.65 => 15 = 0x0F => 27000000/(16*15) = 112500 (2.3% error)
  divider = DEVICE_OSC_FREQ / (DEVICE_UART0_DESIRED_BAUD * DEVICE_UART0_OVERSAMPLE_CNT);
  dividerX2 = (2*DEVICE_OSC_FREQ) / (DEVICE_UART0_DESIRED_BAUD * DEVICE_UART0_OVERSAMPLE_CNT);
  if (divider*2 < dividerX2) divider++;

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

  // Set timer period (5 second timeout = (27000000 * 5) cycles = 0x080BEFC0) 
  TIMER0->PRD34 = 0x00000000;
  TIMER0->PRD12 = 0x080BEFC0;
    
  return E_PASS;
}

Uint32 DEVICE_I2C0Init()
{
    return E_PASS;
}

Uint32 DEVICE_I2C0Reset()
{
    return E_PASS;
}

Uint32 DEVICE_TIMER0Init()
{
  // Put timer into reset
  TIMER0->EMUMGT_CLKSPD = 0x00000003;
  TIMER0->TCR   = 0x00000000;
  
  // Setup as 2 unchained 32-bit timers
  TIMER0->TGCR  = 0x00000005;

  // Reset timers to zero 
  TIMER0->TIM12 = 0x00000000;
  TIMER0->TIM34 = 0x00000000;

  // Set period to 5 sec
  TIMER0->PRD34 = 0x00000000;
  TIMER0->PRD12 = 0x019BFCC0;

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




