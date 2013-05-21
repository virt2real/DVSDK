/* --------------------------------------------------------------------------
  FILE        : device.c 				                             	 	        
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Sandeep Paulraj
  DESC        : This file provides low-level, device-specific init functions
                for use the DM36x device.
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
  static const Uint32 PLL1_Mult = DEVICE_PLL1_MULTIPLIER;
  static const Uint32 PLL2_Mult = DEVICE_PLL2_MULTIPLIER;
    

/************************************************************
* Global Variable Definitions                               *
************************************************************/

const String devString = "DM36x";
#define GPINT_GPEN		(unsigned int *)(0x01C21C08)		// WDT special function
#define GPTDAT_GPDIR	(unsigned int *)(0x01C21C0c)		// WDT special function

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

  POR_RESET();

  // System PSC setup - enable all
  DEVICE_PSCInit();
  
  DEVICE_pinmuxControl(0,0xFFFFFFFF,0x00FD0000);  // All Video Inputs
  DEVICE_pinmuxControl(1,0xFFFFFFFF,0x00145555);  // All Video Outputs
  DEVICE_pinmuxControl(2,0xFFFFFFFF,0x000000DA);  // EMIFA
  DEVICE_pinmuxControl(3,0xFFFFFFFF,0x00180000);  // SPI0, SPI1, UART1, I2C, SD0, SD1, McBSP0, CLKOUTs
  DEVICE_pinmuxControl(4,0xFFFFFFFF,0x55555555);  // MMC/SD0 instead of MS, SPI0

	GPIO->DIR02 &= 0xfeffffff;
	GPIO->CLRDATA02 = 0x01000000;

  // System PLL setup
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

void POR_RESET()
{

	if ((PLL1->RSTYPE)&3) {
    
    	VPSS_SYNC_RESET();  // VPSS sync reset
    
    	*GPINT_GPEN = 0x00020000;
    
    	*GPTDAT_GPDIR = 0x00020002;
    
    	while(1);
  	}

}

void VPSS_SYNC_RESET()
{
	unsigned int PdNum = 0;

	SYSTEM->VPSS_CLKCTL |= 0x00000080;						// VPSS_CLKMD 1:1

	//LPSC SyncReset DDR Clock Enable
	PSC->MDCTL[47] = ((PSC->MDCTL[47] & 0xffffffe0) | 0x00000001);        
            
	PSC->PTCMD = (1<<PdNum);

	while(! (((PSC->PTSTAT >> PdNum) & 0x00000001) == 0));      

	while(!((PSC->MDSTAT[47] &  0x0000001F) == 0x1));           
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
  
  unsigned char i=0;
  unsigned char lpsc_start;
  unsigned char lpsc_end,lpscgroup,lpscmin,lpscmax;
  unsigned int  PdNum = 0; 
 
  lpscmin  =0;
  lpscmax  =2;
  
  for(lpscgroup=lpscmin ; lpscgroup <=lpscmax; lpscgroup++) {
  if(lpscgroup==0)
  {
    lpsc_start = 0; // Enabling LPSC 3 to 28 SCR first
    lpsc_end   = 28;
  }
  else if (lpscgroup == 1) { /* Skip locked LPSCs [29-37] */
    lpsc_start = 38;
    lpsc_end   = 47;
   } else {
    lpsc_start = 50;
    lpsc_end   = 51;
   }

 	//NEXT=0x3, Enable LPSC's
 	for(i=lpsc_start; i<=lpsc_end; i++) {
   	     // CSL_FINS(CSL_PSC_0_REGS->MDCTL[i], PSC_MDCTL_NEXT, 0x3);	  
   	     PSC->MDCTL[i] |= 0x3; 
    }

 	//Program goctl to start transition sequence for LPSCs
 	//CSL_PSC_0_REGS->PTCMD = (1<<PdNum); /*Kick off Power Domain 0 Modules*/
       PSC->PTCMD = (1<<PdNum); 
       
 	//Wait for GOSTAT = NO TRANSITION from PSC for Powerdomain 0
 	//while(! (((CSL_PSC_0_REGS->PTSTAT >> PdNum) & 0x00000001) == 0));
 	 while(! (((PSC->PTSTAT >> PdNum) & 0x00000001) == 0)); 

 	//Wait for MODSTAT = ENABLE from LPSC's
 	for(i=lpsc_start; i<=lpsc_end; i++) {
   	     // while(!((CSL_PSC_0_REGS->MDSTAT[i] &  0x0000001F) == 0x3));   
   	     while(!((PSC->MDSTAT[i] &  0x0000001F) == 0x3));   
   	       	    		
    }	
  }	  

}

Uint32 DEVICE_PLL1Init(Uint32 PLLMult)
{
	unsigned int CLKSRC=0x0;    			  
	unsigned int j;
	
	

		/*Power up the PLL*/
	PLL1->PLLCTL &= 0xFFFFFFFD;		

	PLL1->PLLCTL &= 0xFFFFFEFF;  			
	PLL1->PLLCTL |= CLKSRC<<8;
	
	/*Set PLLENSRC '0', PLL Enable(PLLEN) selection is controlled through MMR*/
	PLL1->PLLCTL &= 0xFFFFFFDF;	
	
	/*Set PLLEN=0 => PLL BYPASS MODE*/
	PLL1->PLLCTL &= 0xFFFFFFFE;
	
	UTIL_waitLoop(150); 				
	
	 // PLLRST=1(reset assert)
	PLL1->PLLCTL |= 0x00000008; 
	
    UTIL_waitLoop(300); 
	
	/*Bring PLL out of Reset*/ 
 	PLL1->PLLCTL &= 0xFFFFFFF7;
   
	//Program the Multiper and Pre-Divider for PLL1
	 PLL1->PLLM   =   0x51;   // VCO will 24*2M/N+1 = 486Mhz
	 PLL1->PREDIV =   0x8000|0x7; 
	 
		 
	PLL1->SECCTL = 0x00470000;   // Assert TENABLE = 1, TENABLEDIV = 1, TINITZ = 1 
    //	for(j=0; j<0x100; j++) {} 
    PLL1->SECCTL = 0x00460000;   // Assert TENABLE = 1, TENABLEDIV = 1, TINITZ = 0 
	//	for(j=0; j<0x100; j++) {}
    PLL1->SECCTL = 0x00400000;   // Assert TENABLE = 0, TENABLEDIV = 0, TINITZ = 0 
	//	for(j=0; j<0x100; j++) {}
    PLL1->SECCTL = 0x00410000;   // Assert TENABLE = 0, TENABLEDIV = 0, TINITZ = 1



     //Program the PostDiv for PLL1
     PLL1->POSTDIV = 0x8000;
    
     // Post divider setting for PLL1 

	    PLL1->PLLDIV2 = 0x8001;   
	    PLL1->PLLDIV3 = 0x8001;   // POST DIV 486/2  -> MJCP/HDVICP
	    PLL1->PLLDIV4 = 0x8003;   // POST DIV 486/4  -> EDMA/EDMA CFG
	    PLL1->PLLDIV5 = 0x8001;   // POST DIV 486/2 -> VPSS
	    PLL1->PLLDIV6 = 0x8011;   // 27Mhz POST DIV 486/18  -> VENC
        PLL1->PLLDIV7 = 0x8000;   // POST DIV 486/2 -> DDR
	    PLL1->PLLDIV8 = 0x8003;   // POST DIV 486/4 -> MMC0/SD0
	    PLL1->PLLDIV9 = 0x8001;   // POST DIV 486/2 -> CLKOUT
	    
	 	UTIL_waitLoop(300);
	    
	    /*Set the GOSET bit */   
		 PLL1->PLLCMD = 0x00000001;  // Go
		 
		 UTIL_waitLoop(300);
		 
		 
		/*Wait for PLL to LOCK */
      
          while(! (((SYSTEM->PLL0_CONFIG) & 0x07000000) == 0x07000000));
        
     
        /*Enable the PLL Bit of PLLCTL*/
         PLL1->PLLCTL |= 0x00000001;   // PLLEN=0

  return E_PASS;
}

Uint32 DEVICE_PLL2Init()
{
	unsigned int CLKSRC=0x0;
 	/*Power up the PLL*/
	PLL2->PLLCTL &= 0xFFFFFFFD;	
			     	
	/*Select the Clock Mode as Onchip Oscilator or External Clock on MXI pin*/
	/*VDB has input on MXI pin */
	
	PLL2->PLLCTL &= 0xFFFFFEFF;  			
	PLL2->PLLCTL |= CLKSRC<<8;
	
	/*Set PLLENSRC '0', PLL Enable(PLLEN) selection is controlled through MMR*/
	PLL2->PLLCTL &= 0xFFFFFFDF;	
	
	/*Set PLLEN=0 => PLL BYPASS MODE*/
	PLL2->PLLCTL &= 0xFFFFFFFE;
	
	UTIL_waitLoop(50); 				
	
	 // PLLRST=1(reset assert)
	PLL2->PLLCTL |= 0x00000008;  


	UTIL_waitLoop(300); 

	  /*Bring PLL out of Reset*/
     PLL2->PLLCTL &= 0xFFFFFFF7;		
			 
     //Program the Multiper and Pre-Divider for PLL2
	 PLL2->PLLM   =   0x63;   // VCO will 24*2M/N+1 = 594Mhz
	 PLL2->PREDIV =   0x8000|0x7; 
	 
	 PLL2->POSTDIV = 0x8000;
    
	 PLL2->SECCTL = 0x00470000;   // Assert TENABLE = 1, TENABLEDIV = 1, TINITZ = 1 
     PLL2->SECCTL = 0x00460000;   // Assert TENABLE = 1, TENABLEDIV = 1, TINITZ = 0 
     PLL2->SECCTL = 0x00400000;   // Assert TENABLE = 0, TENABLEDIV = 0, TINITZ = 0 
     PLL2->SECCTL = 0x00410000;   // Assert TENABLE = 0, TENABLEDIV = 0, TINITZ = 1
			     
	  // Post divider setting for PLL2 

     PLL2->PLLDIV2 = 0x8001;   // 594/2 =297 Mhz -> ARM 
	 PLL2->PLLDIV4 = 0x801C;   // POST DIV 594/29 = 20.48 -> VOICE
	 PLL2->PLLDIV5 = 0x8007;   // POST DIV 594/8 = 74.25 ->VIDEO HD
	 
		     
	  //GoCmd for PostDivider to take effect
            
     PLL2->PLLCMD = 0x00000001;  
     
     UTIL_waitLoop(150);
              
      /*Wait for PLL to LOCK */
      while(! (((SYSTEM->PLL1_CONFIG) & 0x07000000) == 0x07000000)); 
     
     UTIL_waitLoop(4100);
             
      //Enable the PLL2
	    
	  PLL2->PLLCTL |= 0x00000001;   // PLLEN=0

	//do this after PLL's have been set up
	SYSTEM->PERI_CLKCTRL = 0x243F04FC;

  
  return E_PASS;
 
}


Uint32 DEVICE_DDR2Init()
{
 DEVICE_LPSCTransition(LPSC_DDR2,0,PSC_ENABLE);
  
  SYSTEM->VTPIOCR = (SYSTEM->VTPIOCR) & 0xFFFF9F3F;
  
   // Set bit CLRZ (bit 13)
   SYSTEM->VTPIOCR = (SYSTEM->VTPIOCR) | 0x00002000;
  
   // Check VTP READY Status
   while( !(SYSTEM->VTPIOCR & 0x8000));     
  
   // Set bit VTP_IOPWRDWN bit 14 for DDR input buffers)
   //SYSTEM->VTPIOCR = SYSTEM->VTPIOCR | 0x00004000;         
  
   // Set bit LOCK(bit7) and PWRSAVE (bit8)
   SYSTEM->VTPIOCR = SYSTEM->VTPIOCR | 0x00000080;     
    
   // Powerdown VTP as it is locked (bit 6)
   // Set bit VTP_IOPWRDWN bit 14 for DDR input buffers)
   SYSTEM->VTPIOCR = SYSTEM->VTPIOCR | 0x00004040;
  
  // Wait for calibration to complete 
  UTIL_waitLoop( 150 );
  
  // Set the DDR2 to synreset, then enable it again
  DEVICE_LPSCTransition(LPSC_DDR2,0,PSC_SYNCRESET);
  DEVICE_LPSCTransition(LPSC_DDR2,0,PSC_ENABLE);
    
 	DDR->DDRPHYCR = 0x000000C5; 

	DDR->SDBCR = 0x08D34832;		//Program SDRAM Bank Config Register
	DDR->SDBCR = 0x0853C832;

    DDR->SDTIMR =0x3C934B51;		//Program SDRAM Timing Control Register1
	DDR->SDTIMR2 =0x4221C72;		//Program SDRAM Timing Control Register2

	DDR->PBBPR = 0x000000FE;
		
	DDR->SDBCR = 0x08534832;		//Program SDRAM Bank Config Register

	DDR->SDRCR = 0x00000768;		//Program SDRAM Refresh Control Register

  DEVICE_LPSCTransition(LPSC_DDR2,0,PSC_SYNCRESET);
  DEVICE_LPSCTransition(LPSC_DDR2,0,PSC_ENABLE);

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

  AEMIF->AWCCR = 0xff;
  
  AEMIF->A1CR = 0x40400204;

  AEMIF->NANDFCR |= 1;

  AEMIF->A2CR = 0x00a00505;

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

  UART0->MDR = 0x0;
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
//interrupt for Timer0 in DM35x and DM36x is the same
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




