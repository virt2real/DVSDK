/* --------------------------------------------------------------------------
  FILE        : device.c                                                   
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : This file provides low-level, device-specific init functions
                for use the DM646x device.
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

extern __FAR__ Uint32 L2Start;
extern __FAR__ Uint32 EXTERNAL_RAM_START;


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define VTPVAL1 (0x00000003)
#define VTPVAL2 (0x00000002)
#define VTP_WAIT_VAL (0x000004B0)


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/


/************************************************************
* Local Variable Definitions                                *
\***********************************************************/

#if defined(DM6467_27MHz_459MHz)
#define OSC_IN_27MHz
  static const Uint32 PLL1_Mult = 17;       // DSP=459 MHz @ 27M input
  static const Uint32 PLL1Div4_ratio = 5;   // ATA divider
  static const Uint32 PLL1Div8_ratio = 17;  // VPBE = 27M
  static const Uint32 PLL1Div9_ratio = 5;   // VLYNQ divider
  static const Uint32 PLL2_Mult = 17;       // DDR=297 MHz @ 27M input
#elif defined(DM6467_27MHz_594MHz)
#define OSC_IN_27MHz
  static const Uint32 PLL1_Mult = 22;       // DSP=594 MHz @ 27M input
  static const Uint32 PLL1Div4_ratio = 6;   // ATA divider
  static const Uint32 PLL1Div8_ratio = 8;   // VPBE = 74.25M @ 594
  static const Uint32 PLL1Div9_ratio = 6;   // VLYNQ divider  
  static const Uint32 PLL2_Mult = 22;       // DDR=297 MHz @ 27M input  
#elif defined(DM6467_33MHz_594MHz)
#define OSC_IN_33MHz
  static const Uint32 PLL1_Mult = 18;       // DSP=594 MHz @ 33M input
  static const Uint32 PLL1Div4_ratio = 6;   // ATA divider
  static const Uint32 PLL1Div8_ratio = 8;   // VPBE = 74.25M @ 594
  static const Uint32 PLL1Div9_ratio = 6;   // VLYNQ divider  
  static const Uint32 PLL2_Mult = 18;       // DDR=297 MHz @ 33M input  
#elif defined(DM6467_27MHz_675MHz)
#define OSC_IN_27MHz
  static const Uint32 PLL1_Mult = 25;       // DSP=675 MHz @ 27M input
  static const Uint32 PLL1Div4_ratio = 7;   // ATA divider
  static const Uint32 PLL1Div8_ratio = 9;   // VPBE = 75M @ 675
  static const Uint32 PLL1Div9_ratio = 7;   // VLYNQ divider
  static const Uint32 PLL2_Mult = 23;       // DDR=310.5 MHz @ 27M input  
#elif defined(DM6467_27MHz_729MHz)
#define OSC_IN_27MHz
  static const Uint32 PLL1_Mult = 27;       // DSP=729 MHz @ 27M input
  static const Uint32 PLL1Div4_ratio = 7;   // ATA divider
  static const Uint32 PLL1Div8_ratio = 10;  // VPBE = 72.9M @ 729
  static const Uint32 PLL1Div9_ratio = 7;   // VLYNQ divider
  static const Uint32 PLL2_Mult = 23;       // DDR=310.5 MHz @ 27M input  
#elif defined(DM6467_33MHz_729MHz)
#define OSC_IN_33MHz
  static const Uint32 PLL1_Mult = 22;       // DSP=729 MHz @ 33M input
  static const Uint32 PLL1Div4_ratio = 7;   // ATA divider
  static const Uint32 PLL1Div8_ratio = 10;  // VPBE = 72.9M @ 729
  static const Uint32 PLL1Div9_ratio = 7;   // VLYNQ divider
  static const Uint32 PLL2_Mult = 18;       // DDR=297 MHz @ 33M input  
#elif defined(DM6467_33MHz_900MHz)
#define OSC_IN_33MHz
  static const Uint32 PLL1_Mult = 27;       // DSP=891-900 MHz @ 33-33.3MHz input
  static const Uint32 PLL1Div4_ratio = 9;   // ATA divider
  static const Uint32 PLL1Div8_ratio = 12;  // VPBE = 74.25M @ 891
  static const Uint32 PLL1Div9_ratio = 9;   // VLYNQ divider
  static const Uint32 PLL2_Mult = 24;       // DDR=400 MHz @ 33.3MHz input
#elif defined(DM6467_33MHz_1000MHz)
#define OSC_IN_33MHz
  static const Uint32 PLL1_Mult = 30;       // DSP=990-1000 MHz @ 33-33.3MHz input
  static const Uint32 PLL1Div4_ratio = 10;  // ATA divider
  static const Uint32 PLL1Div8_ratio = 13;  // VPBE = ~76M @ 1000
  static const Uint32 PLL1Div9_ratio = 10;  // VLYNQ divider
  static const Uint32 PLL2_Mult = 24;       // DDR=400 MHz @ 33.3MHz input  
#else
#define OSC_IN_33MHz
  // Use 594 values as defaults
  static const Uint32 PLL1_Mult = 18;       // DSP=594 MHz @ 33M input
  static const Uint32 PLL1Div4_ratio = 6;   // ATA divider
  static const Uint32 PLL1Div8_ratio = 8;   // VPBE = 74.25 @ 594
  static const Uint32 PLL1Div9_ratio = 6;   // VLYNQ divider
  static const Uint32 PLL2_Mult = 18;       // DDR=297 MHz @ 33M input
#endif

  static const Uint32 PLL1Div1_ratio = 1;
  static const Uint32 PLL1Div2_ratio = 2;   // ARM = 1/2 DSP speed
  static const Uint32 PLL1Div3_ratio = 4;   // Peripherals - /6 does not work

  static const Uint32 PLL2Div2_ratio = 1;
  static const Uint32 PLL2BPDiv_ratio = 2;

#if defined(OSC_IN_27MHz)
  static const Uint8 DDR_NM = 0;
  static const Uint8 DDR_CL = 5;
  static const Uint8 DDR_IBANK = 3;
  static const Uint8 DDR_PAGESIZE = 2;
  static const Uint16 DDR_T_RFC = 1275;
  static const Uint8 DDR_T_RP = 200;
  static const Uint8 DDR_T_RCD = 200;
  static const Uint8 DDR_T_WR = 150;
  static const Uint16 DDR_T_RAS = 450;
  static const Uint16 DDR_T_RC = 650;
  static const Uint8 DDR_T_RRD = 100;
  static const Uint8 DDR_T_WTR = 100;
  static const Uint32 DDR_T_RASMAX = 700000;
  static const Uint8 DDR_T_XP = 3;    
  static const Uint16 DDR_T_XSNR = 1375;
  static const Uint8 DDR_T_XSRD = 199;
  static const Uint8 DDR_T_RTP = 75;
  static const Uint8 DDR_T_CKE = 2;
  static const Uint16 DDR_RR = 78;
  static const Uint8 DDR_READ_Latency = 6; 
#elif defined(OSC_IN_33MHz)
  static const Uint8 DDR_NM = 0;
  static const Uint8 DDR_CL = 5;
  static const Uint8 DDR_IBANK = 3;
  static const Uint8 DDR_PAGESIZE = 2;
  static const Uint16 DDR_T_RFC = 1275;
  static const Uint8 DDR_T_RP = 125;
  static const Uint8 DDR_T_RCD = 125;
  static const Uint8 DDR_T_WR = 150;
  static const Uint16 DDR_T_RAS = 450;
  static const Uint16 DDR_T_RC = 575;
  static const Uint8 DDR_T_RRD = 100;
  static const Uint8 DDR_T_WTR = 75;
  static const Uint32 DDR_T_RASMAX = 700000;
  static const Uint8 DDR_T_XP = 3;
  static const Uint16 DDR_T_XSNR = 1375;
  static const Uint8 DDR_T_XSRD = 199;
  static const Uint8 DDR_T_RTP = 75;
  static const Uint8 DDR_T_CKE = 2;
  static const Uint8 DDR_RR = 78;
  static const Uint8 DDR_READ_Latency = 6; 
#else
#error OSC_IN should be defined
#endif

/************************************************************
* Global Variable Definitions                               *
************************************************************/

#if defined(OSC_IN_27MHz)
const String devString = "DM646x";
#elif defined(OSC_IN_33MHz)
const String devString = "DM646x-T";
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
  
  // Check for PCI enable
  if (SYSTEM->BOOTCFG & 0x00010000 )
  {
    // PCI mode
    DEVICE_pinmuxControl(0,0xFF,0x00000024);
    DEVICE_pinmuxControl(1,0xFF,0x0000002D);
  }
  else
  {
    // Normal mode
    DEVICE_pinmuxControl(0,0xFF,0x00000001);
    DEVICE_pinmuxControl(1,0xFF,0x0000002D);  
  }
  
  SYSTEM->VDD3P3V_PWDN = 0x180000c0;

  // System PLL Setup
  if (status == E_PASS) status |= DEVICE_PLL1Init();
  
  // DDR PLL setup
  if (status == E_PASS) status |= DEVICE_PLL2Init();
  
  // DDR2 module setup
  if (status == E_PASS)
#if defined(DM6467_27MHz_594MHz) || defined(DM6467_33MHz_594MHz) || \
    defined(DM6467_33MHz_729MHz)
    status |= DEVICE_DDR2Init(297);
#elif defined(DM6467_27MHz_675MHz) || defined(DM6467_27MHz_729MHz)
    status |= DEVICE_DDR2Init(311);
#elif defined(DM6467_33MHz_1000MHz)
    status |= DEVICE_DDR2Init(396);
#else
    status |= DEVICE_DDR2Init(297);
#endif
#endif /* SKIP_LOW_LEVEL_INIT */
      
  // AEMIF Setup (if not PCIEN)
  if ((SYSTEM->BOOTCFG & 0x00010000 ) == 0x0)
  {
    if (status == E_PASS) status |= DEVICE_EMIFInit();
  }

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

void DEVICE_pinPowerControl(Uint32 mask, Uint32 value)
{
  SYSTEM->VDD3P3V_PWDN &= ~mask;
  SYSTEM->VDD3P3V_PWDN |= (value & mask);
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
  VUint32 *L2 = (VUint32 *) &(L2Start);

  // Do always on power domain transitions
  while ((PSC->PTSTAT) & 0x00000001);
   
  for( i = (LPSC_DSP+1) ; i <= LPSC_TIMER1 ; i++ )
    PSC->MDCTL[i] |= PSC_ENABLE; // Enable
    
  PSC->MDCTL[LPSC_AINTC] |= PSC_ENABLE; // Enable

  // Initiate power-domain transition
  PSC->PTCMD |= 0x00000001;
  while ((PSC->PTSTAT) & 0x00000001);
  
  // Put DSP in local reset
  PSC->MDCTL[LPSC_DSP] &= ~(0x0100);
  
  // Initiate GEM power-domain transition
  PSC->PTCMD |= 0x00000002;
  while ((PSC->PTSTAT) & 0x00000002);
  
  // Set the DSP boot address to start of L2SRAM
  SYSTEM->DSPBOOTADDR = (Uint32) L2Start;
  
  // Fill in L2SRAM memory with "Branch to self" instruction
  for (i = 0; i <8; i++);
    L2[i] = 0x13131313;
  
  // Verify DSP is done with reset
  while ((PSC->MDSTAT[LPSC_DSP]) & (0x0100));
}


Uint32 DEVICE_PLL1Init()
{
  if (PLL1_Mult == 0)
    return E_FAIL;
               
  // Step 1 - Set PLL1 clock input to internal osc.
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_CLKMODE_MASK);	
		
  // Step 2 - Set PLL to bypass, then wait for PLL to stabilize
  PLL1->PLLCTL &= ~(DEVICE_PLLCTL_PLLENSRC_MASK | DEVICE_PLLCTL_PLLEN_MASK);
  UTIL_waitLoop( 4 );
    
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
  PLL1->PLLM = (PLL1_Mult - 1) & 0xff;
  PLL1->PLLDIV1 = DEVICE_PLLDIV_EN_MASK | (PLL1Div1_ratio-1);
  PLL1->PLLDIV2 = DEVICE_PLLDIV_EN_MASK | (PLL1Div2_ratio-1);
  PLL1->PLLDIV3 = DEVICE_PLLDIV_EN_MASK | (PLL1Div3_ratio-1);
  PLL1->PLLDIV4 = DEVICE_PLLDIV_EN_MASK | (PLL1Div4_ratio-1);
  PLL1->PLLDIV8 = DEVICE_PLLDIV_EN_MASK | (PLL1Div8_ratio-1);
  PLL1->PLLDIV9 = DEVICE_PLLDIV_EN_MASK | (PLL1Div9_ratio-1);
  UTIL_waitLoop( 150 );       
    
  // Step 10 - Initiate divider switchin
  PLL1->PLLCMD |= DEVICE_PLLCMD_GOSET_MASK;

  // Step 10 - Wait for phase alignment
  while( ( PLL1->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK ) );
    
  // Step 11 - Wait for PLL to reset ( ~5 usec )
  UTIL_waitLoop( 2000 );
	
  // Step 12 - Take out of reset
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
  PLL2->PLLCTL &= (~DEVICE_PLLCTL_CLKMODE_MASK);
  
  // Clear PLLENSRC bit and clear PLLEN bit for Bypass mode 
  // Step 2 - Set PLL to bypass, then wait for PLL to stabilize
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLENSRC_MASK | DEVICE_PLLCTL_PLLEN_MASK);
  UTIL_waitLoop((Uint32)(32*(PLL1_Mult/2)));
  
  // Step 3 - Reset PLL
  PLL2->PLLCTL |= DEVICE_PLLCTL_PLLRST_MASK;
  
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
  UTIL_waitLoop( 150 );
    
  // Step 8 - Load PLL multiplier and divisors
  PLL2->PLLM      = PLL2_Mult-1;
  PLL2->BPDIV     = DEVICE_PLLDIV_EN_MASK | (PLL2BPDiv_ratio-1);
  PLL2->PLLDIV2   = DEVICE_PLLDIV_EN_MASK | (PLL2Div2_ratio-1);

  // Step 9 - Bring PLL Out of Reset
  PLL2->PLLCMD |= DEVICE_PLLCMD_GOSET_MASK;

  // Step 10 - Wait for phase alignment
  while( ( PLL2->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK ) );
    
  // Step 11 - Wait for PLL to reset ( 2000 cycles )
  UTIL_waitLoop(256*(PLL1_Mult/2));
  
  // Step 12 - Release from reset
  PLL2->PLLCTL &= ~(DEVICE_PLLCTL_PLLRST_MASK);

  // Step 13 - Wait for PLL to re-lock ( 2000 cycles )
  UTIL_waitLoop(2000*(PLL1_Mult/2));      // Wait for locking
    
  // Step 13 - Switch out of BYPASS mode
  PLL2->PLLCTL |= DEVICE_PLLCTL_PLLEN_MASK;

  return E_PASS;
}

Uint32 DDR_Get_Val(Uint32 parm, Uint32 freq)
{
	Uint32 result;

	result = ((parm * freq) / 10000) - 1;

	/*
	 * Check if value calculated from formula results in decimal.
	 * If yes round off to next decimal, as the value to be
	 * written to register should be >= calculated value.
	 */
	if((parm * freq) % 10000)
		result++;

	return result;
}

Uint32 DEVICE_DDR2Init(Uint32 freq)
{ 
  VUint32 tempVal;
  VUint32 *ddrStart = (VUint32 *) &(EXTERNAL_RAM_START);
  Uint32 tRFC, tRP, tRCD, tWR, tRAS, tRC, tRRD, tWTR;
  
  // Set the DDR2 to enable
  DEVICE_LPSCTransition(LPSC_DDR2,PD0,PSC_ENABLE);
  
  // DDR VTP initialization
  DDR->VTPIOCR = VTPVAL1;
  DDR->VTPIOCR = VTPVAL2;

  // Wait for 40 VTP cycles or 80 ARM clock cycles.
  UTIL_waitLoop(VTP_WAIT_VAL);

  // Wait for DDR ready
  while (!(DDR->SDRSTAT & 0x04));
  
  // Set the DDR2 to syncreset
  DEVICE_LPSCTransition(LPSC_DDR2,PD0,PSC_SYNCRESET);
  
  // Set the DDR2 to enable
  DEVICE_LPSCTransition(LPSC_DDR2,PD0,PSC_ENABLE);

  // Wait before doing DDR timing programming
  UTIL_waitLoop(990000);
  
  // Setup the read latency
  DDR->DDRPHYCR = (0x00008AC0) | DDR_READ_Latency;
    
  // Set the BOOTUNLOCK and TIMUNLOCK bits
  DDR->SDBCR |= (0x00808000);
  
  // Set CAS LAtency 5, 8 banks, 1024-word page size 
  //DDR->SDBCR = 0x08D78A32;
  DDR->SDBCR =  0x00538000 |
                (DDR_NM << 14)   |
                (DDR_CL << 9)    |
                (DDR_IBANK << 4) |
                (DDR_PAGESIZE <<0);
 
  tRFC = DDR_Get_Val(DDR_T_RFC, freq);
  tRP  = DDR_Get_Val(DDR_T_RP, freq);
  tRCD = DDR_Get_Val(DDR_T_RCD, freq);
  tWR  = DDR_Get_Val(DDR_T_WR, freq);
  tRAS = DDR_Get_Val(DDR_T_RAS, freq);
  tRC  = DDR_Get_Val(DDR_T_RC, freq);
  tRRD = DDR_Get_Val(DDR_T_RRD, freq);
  tWTR = DDR_Get_Val(DDR_T_WTR, freq);
 
  // Program timing registers 
  //DDR->SDTIMR = 0x4B245C12;
  DDR->SDTIMR =   tRFC << 25	|              
                  tRP  << 22	|
                  tRCD << 19	|
                  tWR  << 16	|
                  tRAS << 11	|
                  tRC  << 6	|
                  tRRD << 3	|
                  tWTR << 0;
                  
  //DDR->SDTIMR2 = 0x3B2BC742;
  DDR->SDTIMR2 =  ((DDR_T_RASMAX / (DDR_RR * freq)) << 27) |
                  (DDR_T_XP << 25 )    |
                  (((DDR_T_XSNR * freq) / 10000) << 16)   |
                  (DDR_T_XSRD << 8)    |
                  (((DDR_T_RTP * freq) / 10000) << 5)     |
                  (DDR_T_CKE << 0);

  // Clear the BOOTUNLOCK and TIMUNLOCK bit 
  DDR->SDBCR &= (~0x00808000);
  
  // Set the refresh rate
  DDR->SDRCR = (DDR_RR * freq) / 10;
  
  // Dummy write/read to apply timing settings
  *ddrStart = DEVICE_DDR2_TEST_PATTERN;   // Write
  tempVal = *ddrStart;                    // Read
  *ddrStart =  tempVal;                   // Write
  
  return E_PASS;
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
  // This line is suspect
  SYSTEM->CLKCTL &= 0xFCFFFFFF;

  // Turn on the I/O pin buffers
  DEVICE_pinPowerControl(DEVICE_VDD3P3V_PWDN_UR0MDM_MASK,DEVICE_VDD3P3V_PWDN_UR0MDM_EN);
  DEVICE_pinPowerControl(DEVICE_VDD3P3V_PWDN_UR0DF_MASK,DEVICE_VDD3P3V_PWDN_UR0DF_EN);

  // The DM646x pin muxing registers must be set for UART0 use
  DEVICE_pinmuxControl(1,DEVICE_PINMUX_UART0_MASK,DEVICE_PINMUX_UART0_EN);
  
  // Reset and then power on the UART0 via PSC
  DEVICE_LPSCTransition(LPSC_UART0,PD0,PSC_SYNCRESET);
  DEVICE_LPSCTransition(LPSC_UART0,PD0,PSC_ENABLE);
  
  // Set ENHANCED_EN
  UART0->LCR = 0xBF;        // Enable access to EFR
  UART0->EFR |= 0x10;       // ENHANCED_EN = 1, First requirement to access MCR and IER

  // Put UART in reset
  UART0->LCR &= ~(0x80);    // Second requirement to access MCR and IER
  UART0->IER = 0x0;         // Clear IER (disable interrupts)
  UART0->MCR = 0x0;         // Disable flow control
  UART0->LCR &= ~(0x40);    // UART breaks are removed
  UART0->MDR1 = 0x07;       // Put UART in reset

  // Setup FIFO
  UART0->LCR &= ~(0x80);    // Second requirement to access MCR and IER
  UART0->MCR = 0x40;        // Enable access to TLR, TCR 
  UART0->TCR = 0x0F;
  UART0->TLR = 0x00;        // Make FCR determine FIFO level
  UART0->SCR &= ~(0xC0);    // Clear granularity bits
  UART0->FCR = 0x07;        // 16-byte receive FIFOs  
  UART0->LCR &= ~(0x80);    // Second requirement to access MCR and IER
  UART0->MCR &= ~(0x40);    // Disable access to TLR, TCR  
  
  // Clear ENHANCED_EN
  UART0->LCR = 0xBF;        // Enable access to EFR
  UART0->EFR &= ~(0x10);    // ENHANCED_EN = 0
  
  // Set clock dividers
  UART0->LCR = 0x83;        // 8-bits, no parity, one stop bit, Access DLL and DLH
  UART0->DLL = 0x0D;        //divider = 27000000/(16*115200) = 14.65 => 15 = 0x0F => 27000000/(16*15) = 112500 (2.3% error)
  UART0->DLH = 0x00;
  
  // Enable interrupts
  UART0->LCR &= ~(0x80);    // Requirement to access IER[3..0]
  UART0->IER = 0x03;        // Enable interrupts

  // Bring UART out of reset
  UART0->MDR1 = 0x00;       // UART in normal mode
  
  UTIL_waitLoop(100); 
   
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
  // Power-up the Timer
  DEVICE_LPSCTransition(LPSC_TIMER0, PD0 ,PSC_ENABLE);

  // Put timer into reset
  TIMER0->EMUMGT_CLKSPD = 0x00000003;
  TIMER0->TCR   = 0x00000000;
  
  // Setup as 2 unchained 32-bit timers
  TIMER0->TGCR  = 0x00000005;

  // Reset timers to zero 
  TIMER0->TIM12 = 0x00000000;

  // Set period to 5 sec
  TIMER0->PRD12 = 0x019BFCC0;

  return E_PASS;
}

void DEVICE_TIMER0Start(void)
{
  // Clear interrupt
  AINTC->IRQ1   |=  0x00000001;

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




