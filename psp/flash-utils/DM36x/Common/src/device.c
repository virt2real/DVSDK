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

//#define ARM270_DDR216_OSC24
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

const String devString = "DM36x";
#define GPINT_GPEN		(unsigned int *)(0x01C21C08)		// WDT special function
#define GPTDAT_GPDIR	(unsigned int *)(0x01C21C0c)		// WDT special function
#define TMPBUF          (unsigned int *)(0x17ff8)
#define TMPSTATUS		(unsigned int *)(0x17ff0)
#define FLAG_PORRST		0x00000001
#define FLAG_WDTRST		0x00000002
#define FLAG_FLGON		0x00000004
#define FLAG_FLGOFF		0x0000001

static const Uint16 DDR_T_RFC = 1275;
static const Uint16 DDR_T_RP = 200;
static const Uint16 DDR_T_RCD = 200;
static const Uint16 DDR_T_WR = 150 ;
static const Uint16 DDR_T_RAS = 450;
static const Uint16 DDR_T_RC = 650;
static const Uint16 DDR_T_RRD = 100;
static const Uint16 DDR_T_WTR = 100;
static const Uint32 DDR_T_RASMAX = 700000;
static const Uint16 DDR_T_XP = 2;
static const Uint16 DDR_T_XSNR = 1375;
static const Uint16 DDR_T_XSRD = 199;
static const Uint16 DDR_T_RTP = 75;
static const Uint16 DDR_T_CKE = 3;
static const Uint16 DDR_RR = 78;


/* PLL Divider settings for Various ARM/DDR Frequencies */
#if defined(ARM297_DDR270_OSC24)

#define PLL1_MUL		0x2d  
#define PLL1_PREDIV		0x3
#define PLL1_POSTDIV		0x0 	//PLL1 output ( 0x2d * 2* 24 / (0x3+ 1) = 540 MHZ )
	
#define PLL1_DIV1		0x2c	//USB 12 MHZ
#define PLL1_DIV2		0x1	// POST DIV 540/2 -> HDVICP max =270 MHZ 
#define PLL1_DIV3		0x1	// POST DIV 540/2  -> MJCP/HDVICP  max =270 MHZ 
#define PLL1_DIV4		0x3	// POST DIV 540/4  -> EDMA/EDMA CFG	MAX =135 MHZ 
#define PLL1_DIV5		0x1	// POST DIV 540/2 -> VPSS 	max =270 MHZ
#define PLL1_DIV6		0x13	// 27Mhz POST DIV 540/20  -> VENC 27 MHZ	
#define PLL1_DIV7		0x0	// POST DIV 540/2 -> DDR max =270 MHZ
#define PLL1_DIV8		0x05	// POST DIV 540/6 -> 90 MMC0/SD0 <=100
#define PLL1_DIV9		0x1	// POST DIV 540/2 -> CLKOUT


#define PLL2_MUL		0x63
#define PLL2_PREDIV		0x7
#define PLL2_POSTDIV		0x0	//PLL2 Output (0x63 * 2 * 24 / (0x7 + 1) = 594MHZ

#define PLL2_DIV1		0x18	// 594/25 23.6 MHZ USB
#define PLL2_DIV2		0x1  	// 594/2 =297 Mhz -> ARM 
#define PLL2_DIV3		0x1	// 297 MHZ 2 * ddr
#define PLL2_DIV4		0x1c 	// POST DIV 594/29 = 20.48 -> VOICE
#define PLL2_DIV5		0x07 	// POST DIV 594/8 = 74.25 ->VIDEO HD

#define PERIPHERAL_CLK_CTRL_VAL	0x243F04FC

#define DDR_FREQ	 270

#elif defined(ARM270_DDR216_OSC24)

#define PLL1_MUL		0x9  
#define PLL1_PREDIV		0x0
#define PLL1_POSTDIV		0x0 	//PLL1 output ( 0x9 * 2* 24 = 432 MHZ )

#define PLL1_DIV1		0x11	// POST DIV 432/18 ->24 mhz
#define PLL1_DIV2		0x1	// POST DIV 432/2  -> HDVICP max =216 MHZ
#define PLL1_DIV3		0x1	// POST DIV 432/2  -> MJCP/HDVICP
#define PLL1_DIV4		0x3	// POST DIV 432/4  -> EDMA/EDMA CFG
#define PLL1_DIV5		0x1	// POST DIV 432/2 -> VPSS
#define PLL1_DIV6		0x5	// POST DIV 432/(5+1) 72  -> VENC	
#define PLL1_DIV7		0x0	// POST DIV 432 -> DDR
#define PLL1_DIV8		0x04	// POST DIV 432/5 ->  86 MMC0/SD0
#define PLL1_DIV9		0x1	// POST DIV 432/2 -> CLKOUT

#define PLL2_MUL		0x2D
#define PLL2_PREDIV		0x7
#define PLL2_POSTDIV		0x0 	//PLL2 Output (0x2D * 2 * 24 / (0x7 + 1) = 270 MHZ


#define PLL2_DIV1		0xA	// USB 24.5  MHZ
#define PLL2_DIV2		0x0  	// 270 =270 Mhz -> ARM 
#define PLL2_DIV3		0x0	// 270 2* DDR
#define PLL2_DIV4		0x05 	// POST DIV 270/6  -> VOICE
#define PLL2_DIV5		0x09 	// POST DIV 270/10 = 27 MHZ ->VIDEO HD

#define PERIPHERAL_CLK_CTRL_VAL	0x243F04FC

#define DDR_FREQ	 216

#elif defined(ARM297_DDR277_OSC27) 

#define PLL1_MUL		0x2c
#define PLL1_PREDIV		0x03
#define PLL1_POSTDIV		0x0 	//PLL1 output ( 0x2c * 2 * 27 /4  = 594 MHZ )

#define PLL1_DIV1		0x17	//USB 24 MHZ
#define PLL1_DIV2		0x1
#define PLL1_DIV3		0x1	// POST DIV 594/2  -> MJCP/HDVICP
#define PLL1_DIV4		0x3	// POST DIV 594/4  -> EDMA/EDMA CFG
#define PLL1_DIV5		0x3	// POST DIV 540/4 -> VPSS
#define PLL1_DIV6		0x15	// 27Mhz POST DIV 594/22  -> VENC	
#define PLL1_DIV7		0x0	// POST DIV 597 -> DDR
#define PLL1_DIV8		0x03	// POST DIV 594/4 -> 90 MMC0/SD0
#define PLL1_DIV9		0x1	// POST DIV 594/2 -> CLKOUT

#define PLL2_MUL		0x100  
#define PLL2_PREDIV		0x18
#define PLL2_POSTDIV	0x0 		//PLL2 Output (0x100 * 2 * 27 / (0x18 + 1) = 552 MHZ

#define PLL2_DIV1		0x18	// 552.96/0x19  MHZ USB
#define PLL2_DIV2		0x0 	// 552.96/1 = 552.96 Mhz -> ARM 
#define PLL2_DIV3		0x1	// 552.96/2 = 276.48 mhz 2 * ddr
#define PLL2_DIV4		0x8 	// POST DIV 552.96/9 =  -> VOICE
#define PLL2_DIV5		0x0 	// POST DIV 552.96/1 = 552.96 ->VIDEO HD

#define PERIPHERAL_CLK_CTRL_VAL	0x0BFF077C

#define DDR_FREQ		 277

#elif defined(ARM216_DDR173_OSC19P2)

#define PLL1_MUL		0x2d 
#define PLL1_PREDIV		0x3
#define PLL1_POSTDIV		0x0 	//PLL1 output ( 0x2d * 2 * 19.2 /4  = 432  MHZ )

#define PLL1_DIV1		0x11	// USB ~24 MHZ
#define PLL1_DIV2		0x1	
#define PLL1_DIV3		0x1	// POST DIV  432/2  -> MJCP/HDVICP
#define PLL1_DIV4		0x3	// POST DIV  432/4  -> EDMA/EDMA CFG
#define PLL1_DIV5		0x3	// POST DIV  432/4  -> VPSS
#define PLL1_DIV6		0x0f	// POST DIV    432/16  -> VENC	
#define PLL1_DIV7		0x0	// POST DIV  432 -> DDR
#define PLL1_DIV8		0x04	// POST DIV  432/5 -> 86 MMC0/SD0
#define PLL1_DIV9		0x1	// POST DIV  432/2 -> CLKOUT

#define PLL2_MUL		0xE0
#define PLL2_PREDIV		0x18
#define PLL2_POSTDIV		0x0	//PLL2 Output (0xE0 * 2 * 19.2 / (0x18+ 1) = 344.064MHZ


#define PLL2_DIV1		0xd     // POST DIV 344/15=24 Mhz  ->USB PHY
#define PLL2_DIV2		0x0 	// 344/1 =344 Mhz -> DDR 
#define PLL2_DIV3		0x1	// POST DIV 344/2 Mhz  -> DDRx2
#define PLL2_DIV4		0x6 	// POST DIV 344/7 -> VOICE
#define PLL2_DIV5		0x0 	// POST DIV 344/1 ->VIDEO HD

#define PERIPHERAL_CLK_CTRL_VAL	0x0BFF05FC

#define DDR_FREQ		 173

#elif defined(ARM216_DDR173_OSC24)

#define PLL1_MUL		0x73 	// VCO will 2M/N+1 = 345 Mhz
#define PLL1_PREDIV		0xf
#define PLL1_POSTDIV		0x0  

#define PLL1_DIV1		0xD	// USB ~24 MHZ
#define PLL1_DIV2		0x1
#define PLL1_DIV3		0x1	// POST DIV 345/2  -> 172.5Mhz  MJCP/HDVICP
#define PLL1_DIV4		0x3	// POST DIV 345/4  -> 86.25Mhz EDMA/EDMA CFG
#define PLL1_DIV5		0x1	// POST DIV 345/2 -> 172.5 MHZ VPSS
#define PLL1_DIV6		0x0C	// POST DIV 345/13  -> 26.53 MHZ VENC	
#define PLL1_DIV7		0x0	// POST DIV 345 -> DDR
#define PLL1_DIV8		0x3	// POST DIV 345/4 = 86.25 MHZ-> MMC0/SD0
#define PLL1_DIV9		0x1	// POST DIV 345/2 = 172.5 MHZ-> CLKOUT

#define PLL2_MUL		0x12
#define PLL2_PREDIV		0x1
#define PLL2_POSTDIV		0x0 	//PLL2 Output (0x12 * 2 * 27 / (0x1 + 1) = 432 MHZ


#define PLL2_DIV1		0x11	// POST DIV 432/18=24 Mhz  ->USB PHY
#define PLL2_DIV2		0x1  	// 432/2 =216 Mhz -> ARM 
#define PLL2_DIV3		0x1	// POST DIV 432/2=216 Mhz  -> DDRx2
#define PLL2_DIV4		0x14	// POST DIV 432/21 = 20.57-> VOICE
#define PLL2_DIV5		0x0f 	// POST DIV 432/16 = 74.25 ->VIDEO HD

#define PERIPHERAL_CLK_CTRL_VAL	0x243F04FC

#define DDR_FREQ		 173

#elif defined(ARM432_DDR340_OSC24)

#define PLL1_MUL		0x55 
#define PLL1_PREDIV		0x5
#define PLL1_POSTDIV		0x0 	// PVCO will 24*2M/N+1 = 680 Mhz

#define PLL1_DIV1		0x1B	// POST DIV 680/28=24.3 Mhz->USB PHY 
#define PLL1_DIV2		0x1	// POST DIV 680/2=340Mhz->ARM926/ARM968
#define PLL1_DIV3		0x1	// POST DIV 680/2 = 340Mhz  -> MJCP/HDVICP
#define PLL1_DIV4		0x3	// POST DIV 680/4 = 170Mhz  -> EDMA/Peripheral CFG0 (1/2 Kaleido clock)
#define PLL1_DIV5		0x1	// POST DIV 680/2 = 340Mhz -> VPSS (max 270)
#define PLL1_DIV6		0x8	// POST DIV 680/9 = 75.6Mhz -> VENC	
#define PLL1_DIV7		0x0	// POST DIV 680/1 = 680Mhz -> DDRx2
#define PLL1_DIV8		0x6 	// POST DIV 680/7=  97 Mhz-> MMC0/SD0
#define PLL1_DIV9		0x1B	// POST DIV 680/28 = 24.3Mhz-> CLKOUT 

#define PLL2_MUL		0x9
#define PLL2_PREDIV		0x0
#define PLL2_POSTDIV	0x0 		// PLL2 Output (0x9 * 2 * 27 / (0x1 + 1) = 432MHZ

#define PLL2_DIV1		0x11	// POST DIV 432/18=24 Mhz  ->USB PHY
#define PLL2_DIV2		0x0 	// POST DIV 432/1=432 Mhz  -> ARM926/HDVICP 
#define PLL2_DIV3		0x1	// POST DIV 432/2=216 Mhz  -> DDRx2
#define PLL2_DIV4		0x14	// POST DIV 432/21= 20.5714 Mhz->VOICE
#define PLL2_DIV5		0x0f 	// POST DIV 432/16=27 Mhz  -> VENC

#define PERIPHERAL_CLK_CTRL_VAL	0x243F04FC

#define DDR_FREQ		 340

#else  //Arm 297 DDR 243 MHZ 

#define PLL1_MUL		0x51
#define PLL1_PREDIV		0x7
#define PLL1_POSTDIV	0x0 		//PVCO will 24*2M/N+1 = 486 Mhz

#define PLL1_DIV1		0x13	//POST DIV 486/20=24.3 Mhz->USB PHY 
#define PLL1_DIV2		0x1	//POST DIV 486/2=243Mhz->ARM926/ARM968
#define PLL1_DIV3		0x1	// POST DIV 486/2 = 243 Mhz  -> MJCP/HDVICP
#define PLL1_DIV4		0x3	// POST DIV 486/4 = 121.5 Mhz  -> EDMA/Peripheral CFG0 (1/2 Kaleido clock)
#define PLL1_DIV5		0x1	// POST DIV 486/2 = 243Mhz -> VPSS (max 270)
#define PLL1_DIV6		0x11	// POST DIV 486/18 = 27 Mhz -> VENC	
#define PLL1_DIV7		0x0	// POST DIV 486/1 = 486Mhz -> DDRx2
#define PLL1_DIV8		0x4	// POST DIV 486/5 = 97.25Mhz-> MMC0/SD0
#define PLL1_DIV9		0x1	// POST DIV 486/2 = 24.3Mhz-> CLKOUT 


#define PLL2_MUL		0x63
#define PLL2_PREDIV		0x7
#define PLL2_POSTDIV	0x0 		//PLL2 Output (0x63 * 2 * 24 / (0x7 + 1) = 594MHZ

#define PLL2_DIV1		0x18	// 594/25 23.6 MHZ USB
#define PLL2_DIV2		0x1  	// 594/2 =297 Mhz -> ARM 
#define PLL2_DIV3		0X1		// 297 MHZ 2 * ddr
#define PLL2_DIV4		0x1c 	// POST DIV 594/29 = 20.48 -> VOICE
#define PLL2_DIV5		0x07 	// POST DIV 594/8 = 74.25 ->VIDEO HD

#define PERIPHERAL_CLK_CTRL_VAL	0x243F04FC

#define DDR_FREQ		 243

#endif



/************************************************************
* Global Function Definitions                               *
************************************************************/


/*
 DDR uses PLL1 Sysclk 7
 Arm uses PLL2 Sysclk 2 

 DDR & ARM Source can be selected by configuring Peripheral ctl reg
 PERI_CLKCTL 0x48 System module Rrg 0x01c40000
 */



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

  POR_RESET();
  WDT_RESET();

#ifndef SKIP_LOW_LEVEL_INIT

   // System PSC setup - enable all
  DEVICE_PSCInit();
  
  DEVICE_pinmuxControl(0,0xFFFFFFFF,0x00FD0000);  // All Video Inputs
  DEVICE_pinmuxControl(1,0xFFFFFFFF,0x00145555);  // All Video Outputs
  DEVICE_pinmuxControl(2,0xFFFFFFFF,0x000000DA);  // EMIFA
  DEVICE_pinmuxControl(3,0xFFFFFFFF,0x00180000);  // SPI0, SPI1, UART1, I2C, SD0, SD1, McBSP0, CLKOUTs
  DEVICE_pinmuxControl(4,0xFFFFFFFF,0x55555555);  // MMC/SD0 instead of MS, SPI0

	GPIO->DIR02 &= 0xfeffffff;
	GPIO->CLRDATA02 = 0x01000000;

 
  if (status == E_PASS) status |= DEVICE_PLL1Init();

  if (status == E_PASS) status |= DEVICE_PLL2Init();

	if (status == E_PASS) 
		status |= DEVICE_DDR2Init();

#endif
  // AEMIF Setup
  if (status == E_PASS) status |= DEVICE_EMIFInit();

  // UART0 Setup
  if (status == E_PASS) status |= DEVICE_UART0Init();

  // TIMER0 Setup
  if (status == E_PASS) status |= DEVICE_TIMER0Init();
	
  // I2C0 Setup
  if (status == E_PASS) status |= DEVICE_I2C0Init();

  WDT_FLAG_ON();

  return status;
}

void POR_RESET()
{

	if ((PLL1->RSTYPE)&3) {
    
    	VPSS_SYNC_RESET();  // VPSS sync reset
    
	*TMPBUF = 0;
	*TMPSTATUS |= FLAG_PORRST;
    
    	*GPINT_GPEN = 0x00020000;
    
    	*GPTDAT_GPDIR = 0x00020002;
    
    	while(1);
  	}

}

void WDT_RESET()
{
    volatile unsigned int s;

     if((*TMPBUF == 0x591b3ed7)){
        *TMPBUF = 0;
		*TMPSTATUS |= FLAG_PORRST;
 		*TMPSTATUS |= FLAG_FLGOFF;  
        
        for (s=0;s<0x100;s++) {}

        VPSS_SYNC_RESET();

        *GPINT_GPEN = 0x00020000;                                   // WDT

        *GPTDAT_GPDIR = 0x00020002;                                 // execute >
  	     while(1);
    }
}

void WDT_FLAG_ON()
{

	SYSTEM->VPSS_CLKCTL &= 0xffffff7f;      // VPSS_CLKMD 1:2
	*TMPBUF = 0x591b3ed7; 
	*TMPSTATUS |= FLAG_FLGON;  
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


Uint32 DEVICE_PLL1Init()
{
	unsigned int CLKSRC=0x0;    			  
		

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
	 PLL1->PLLM   =   PLL1_MUL;   // VCO will 24*2M/N+1 = 486Mhz
	 PLL1->PREDIV =   0x8000 | PLL1_PREDIV; 
	 
		 
	PLL1->SECCTL = 0x00470000;   // Assert TENABLE = 1, TENABLEDIV = 1, TINITZ = 1 
    //	for(j=0; j<0x100; j++) {} 
    PLL1->SECCTL = 0x00460000;   // Assert TENABLE = 1, TENABLEDIV = 1, TINITZ = 0 
	//	for(j=0; j<0x100; j++) {}
    PLL1->SECCTL = 0x00400000;   // Assert TENABLE = 0, TENABLEDIV = 0, TINITZ = 0 
	//	for(j=0; j<0x100; j++) {}
    PLL1->SECCTL = 0x00410000;   // Assert TENABLE = 0, TENABLEDIV = 0, TINITZ = 1



     //Program the PostDiv for PLL1
     PLL1->POSTDIV = 0x8000 | PLL1_POSTDIV;
    
     // Post divider setting for PLL1 

		PLL1->PLLDIV1 = 0x8000 | PLL1_DIV1;
	    PLL1->PLLDIV2 = 0x8000 | PLL1_DIV2;   
	    PLL1->PLLDIV3 = 0x8000 | PLL1_DIV3;   // POST DIV 486/2  -> MJCP/HDVICP
	    PLL1->PLLDIV4 = 0x8000 | PLL1_DIV4;   // POST DIV 486/4  -> EDMA/EDMA CFG
	    PLL1->PLLDIV5 = 0x8000 | PLL1_DIV5;   // POST DIV 486/2 -> VPSS
	    PLL1->PLLDIV6 = 0x8000 | PLL1_DIV6;   // 27Mhz POST DIV 486/18  -> VENC
        PLL1->PLLDIV7 = 0x8000 | PLL1_DIV7;   // POST DIV 486/2 -> DDR
	    PLL1->PLLDIV8 = 0x8000 | PLL1_DIV8;   // POST DIV 486/4 -> MMC0/SD0
	    PLL1->PLLDIV9 = 0x8000 | PLL1_DIV9;   // POST DIV 486/2 -> CLKOUT
	    
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
	 PLL2->PLLM   = PLL2_MUL;  // VCO will 24*2M/N+1 = 594Mhz
	 PLL2->PREDIV = 0x8000 | PLL2_PREDIV; 
	 
	 PLL2->POSTDIV = 0x8000 | PLL2_POSTDIV;
    
	 PLL2->SECCTL = 0x00470000;   // Assert TENABLE = 1, TENABLEDIV = 1, TINITZ = 1 
     PLL2->SECCTL = 0x00460000;   // Assert TENABLE = 1, TENABLEDIV = 1, TINITZ = 0 
     PLL2->SECCTL = 0x00400000;   // Assert TENABLE = 0, TENABLEDIV = 0, TINITZ = 0 
     PLL2->SECCTL = 0x00410000;   // Assert TENABLE = 0, TENABLEDIV = 0, TINITZ = 1
			     
	  // Post divider setting for PLL2 

	 PLL2->PLLDIV1 = 0x8000 | PLL2_DIV1;
     PLL2->PLLDIV2 = 0x8000 | PLL2_DIV2;   // 594/2 =297 Mhz -> ARM 
	 PLL2->PLLDIV3 = 0x8000 | PLL2_DIV3;   // POST DIV 594/29 = 20.48 -> VOICE
	 PLL2->PLLDIV4 = 0x8000 | PLL2_DIV4;   // POST DIV 594/8 = 74.25 ->VIDEO HD
	 PLL2->PLLDIV5 = 0x8000 | PLL2_DIV5;
		     
	  //GoCmd for PostDivider to take effect
            
     PLL2->PLLCMD = 0x00000001;  
     
     UTIL_waitLoop(150);
              
      /*Wait for PLL to LOCK */
      while(! (((SYSTEM->PLL1_CONFIG) & 0x07000000) == 0x07000000)); 
     
     UTIL_waitLoop(4100);
             
      //Enable the PLL2
	    
	  PLL2->PLLCTL |= 0x00000001;   // PLLEN=0

	//do this after PLL's have been set up
	SYSTEM->PERI_CLKCTRL = PERIPHERAL_CLK_CTRL_VAL;

  
  return E_PASS;
 
}

Uint32 DDR_Get_Val(Uint32 parm, Uint32 freq)
{
	Uint32 result;

	
	result = ((parm * freq) / 10000) - 1;

    /* Check if value calculated from formula results in decimal. 
    * If yes round off to next decimal, as the value to be
     * written to register should be >= calculated value.
     */
   if((parm * freq) % 10000)
           result++;

	return result;
}

Uint32 DEVICE_DDR2Init()
{

 Uint32 tRFC, tRP, tRCD, tWR, tRAS, tRC, tRRD, tWTR;

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

	DDR->SDBCR = 0x534832;
	DDR->SDBCR = 0x53C832; // 0x53C832; Set the TIMUNLOCK to write into the TMR reg  


	tRFC = DDR_Get_Val(DDR_T_RFC, DDR_FREQ);
    tRP  = DDR_Get_Val(DDR_T_RP, DDR_FREQ);
    tRCD = DDR_Get_Val(DDR_T_RCD, DDR_FREQ);
    tWR  = DDR_Get_Val(DDR_T_WR, DDR_FREQ);
    tRAS = DDR_Get_Val(DDR_T_RAS, DDR_FREQ);
    tRC  = DDR_Get_Val(DDR_T_RC, DDR_FREQ);
    tRRD = DDR_Get_Val(DDR_T_RRD, DDR_FREQ);
    tWTR = DDR_Get_Val(DDR_T_WTR, DDR_FREQ);

   DDR->SDTIMR =    tRFC << 25	|              
                    tRP  << 22	|
                    tRCD << 19	|
                    tWR  << 16	|
                    tRAS << 11	|
                    tRC  << 6	|
                    tRRD << 3	|
                    tWTR << 0;

    DDR->SDTIMR2 =  ((DDR_T_RASMAX / (DDR_RR * DDR_FREQ)) << 27) |
                    (DDR_T_XP << 25 )    |
                    (((DDR_T_XSNR * DDR_FREQ) / 10000) << 16)   |
                    (DDR_T_XSRD << 8)    |
                    (((DDR_T_RTP * DDR_FREQ) / 10000) << 5)  |   
                     (DDR_T_CKE << 0);
      
	DDR->SDBCR = 0x534832; //0x534832; Reset the TIMUNLOCK TMR Write Disable

	DDR->PBBPR = 0x000000FE;
	
	DDR->SDBCR = 0xD34A32;	 //Enable DDR2 and DDR and SDram. Write '1' to BOOTUNLOCK

	DDR->SDBCR = 0x534A32;	//Enable DDR2 and DDR and SDram. Write '0' to BOOTUNLOCK

	DDR->SDRCR = (DDR_RR * DDR_FREQ) / 10; //Program SDRAM Refresh Control Registers


  DEVICE_LPSCTransition(LPSC_DDR2,0,PSC_SYNCRESET);
  DEVICE_LPSCTransition(LPSC_DDR2,0,PSC_ENABLE);

	return E_PASS;
}


Uint32 DEVICE_EMIFInit()
{

  AEMIF->AWCCR = 0xff;
  
  AEMIF->A1CR = 0x40400204;

  AEMIF->NANDFCR |= 1;

  AEMIF->A2CR = 0x00a00505;

  return E_PASS;  

}
 
Uint32 DEVICE_UART0Init()
{
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




