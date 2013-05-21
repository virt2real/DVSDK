#ifndef _RTO_TIMER_DEF
#define _RTO_TIMER_DEF

#include <csl_types.h>
#include <cslr_tmr_001.h>
#include <dm350.h>

#define QT				1	// USED to factor in the arm to timer clk ratios for loop counts while waiting for timer
							// to complete running, min number required is 8.5 since DAVINCI TIMER:ARM ratio is 1:8.5 times
#define	LOOP_DIV		10		// Interrupt Loop Count Divider prd12/LOOP_DIV
#define	LOOPLIMIT		20  //Used as a counter for the WDog Timer
//Function Proto Type
CSL_TmrRegsOvly timer[4]= {CSL_TMR_0_REGS, CSL_TMR_1_REGS, CSL_TMR_2_REGS,CSL_TMR_3_REGS}; 

#define CONT	02


//Flag to indicate runtime status and the number of times it fails.
//Uint32 failFlag=0;	
//Variable to indicate the count read from the count registers
//Uint32 count=0; 


void setupTimer(CSL_TmrRegsOvly  timer); 
void setupTimer_reg(CSL_TmrRegsOvly  timer);
void startTimer(CSL_TmrRegsOvly  timer);
void resetTimer(CSL_TmrRegsOvly  timer);

//void timerEmu_cntrl(); -- commented by vishwa

Uint16 chk_timer_gpt64(CSL_TmrRegsOvly  timer,int j);
Uint16 chk_timer_gpt64_Event_Mode(CSL_TmrRegsOvly  timer,int j);
Uint16 chk_timer_D32Unchained_TIM12(CSL_TmrRegsOvly  timer, int j, Uint32 prd12, Uint32 cnt12);
Uint16 chk_timer_D32Unchained_TIM34(CSL_TmrRegsOvly  timer, int j, Uint32 prd34, Uint32 pre34, Uint32 cnt34, Uint32 tddr34);
Uint16 chk_timer_D32Chained_TIM34(CSL_TmrRegsOvly  timer, int j, Uint32 prd12, Uint32 prd34, Uint32 cnt12, Uint32 cnt34);
Uint16 chk_timer_D32Unchained_TIM12_TIM34(CSL_TmrRegsOvly  timer,int j);
Uint16 chk_timer_WD_serv(CSL_TmrRegsOvly  timer, int j);
Uint16 chk_timer_Capture_TIM12(CSL_TmrRegsOvly timer, int j, Uint32 prd12, Uint32 cnt12);
Uint16 chk_timer_Onfly_TIM12(CSL_TmrRegsOvly timer, int j, Uint32 prd12, Uint32 cnt12,Uint32 rel12,Uint32 rel34);


Uint32 getCnt12 (CSL_TmrRegsOvly timer);
Uint32 getCnt34 (CSL_TmrRegsOvly timer);
Uint32 getCap12 (CSL_TmrRegsOvly  timer);
Uint32 getPrd12 (CSL_TmrRegsOvly timer);
Uint32 getPrd34 (CSL_TmrRegsOvly timer);

void WDTIM_service(CSL_TmrRegsOvly timer);

void setupTimer64_Mode(CSL_TmrRegsOvly  timer, Uint32 prd12, Uint32 prd34);
void setupTimer64plus_Event_Mode(CSL_TmrRegsOvly  timer, Uint32 prd12);
void setupTimerD32UC_Mode_TIM12(CSL_TmrRegsOvly  timer, Uint32 prd12);
void setupTimerD32UC_Mode_TIM34(CSL_TmrRegsOvly  timer, Uint32 prd34);
void setupTimerD32C_Mode_TIM12(CSL_TmrRegsOvly  timer, Uint32 prd12, Uint32 prd34);
void setupWDTimer_Mode(CSL_TmrRegsOvly  timer, Uint32 prd12, Uint32 prd34);
void setupTimer64plus_Capture_Mode(CSL_TmrRegsOvly  timer, Uint32 prd12);
void setupTimer64plus_Onfly_Mode(CSL_TmrRegsOvly  timer, Uint32 prd12,Uint32 rel12,Uint32 rel34);
void stopTIM12(CSL_TmrRegsOvly timer); 
void stopTIM34(CSL_TmrRegsOvly timer); 

										
void timerInterruptSetup(int j);
void dmaInterruptSetup(int j);



/* setup emulation to be controlled by the arm --- commented by vishwa
void timerEmu_cntrl () {
CSL_FINST(CSL_SYS_0_REGS->SUSPSRC, SYS_SUSPSRC_TIMR0SRC, ARMEMU);
CSL_FINST(CSL_SYS_0_REGS->SUSPSRC, SYS_SUSPSRC_TIMR1SRC, ARMEMU);
CSL_FINST(CSL_SYS_0_REGS->SUSPSRC, SYS_SUSPSRC_TIMR2SRC, ARMEMU);
}*/
  
void setupTimer(CSL_TmrRegsOvly  timer) {

   timer->PRD12 = 0x00001000;                           //PRD12 = 0x1000
   timer->PRD34 = 0x00000000;                           //PRD34 = 0x0000
   
   CSL_FINS(timer->TGCR, TMR_TGCR_TIMMODE , 0x1);     //TIMMODE = 32-bit dual
   CSL_FINS(timer->TGCR, TMR_TGCR_TIM12RS , 0x1);     //Take TIM12 out of reset
   CSL_FINS(timer->TGCR, TMR_TGCR_TIM34RS , 0x1);     //Take TIM34 out of reset
 }

void setupTimer_reg(CSL_TmrRegsOvly  timer) {
   
 //  timerEmu_cntrl (); //enable emulation control by arm-- Commented by Vishwa
   
   timer->TGCR  = 0x00005A0C;
   timer->PRD12 = 0xAAAAAAAA;   				//PRD12 = 0xAAAAAAAA
   timer->PRD34 = 0x55555555;                   //PRD34 = 0x55555555
   timer->EMUMGT_CLKSPD  = 0x03;                // Soft/Free =1/1, CLKDIV are Read only
   timer->GPINT_GPEN  = 0x00003333;
   timer->GPTDAT_GPDIR  = 0x03030303;
   timer->TIM12  = 0x55555555;
   timer->TIM34  = 0xAAAAAAAA;
   timer->TCR  = 0x02380238;
   timer->WDTCR  = 0xA5C60000;
   if(timer==CSL_TMR_3_REGS)
   {
   timer->CAP12 = 0xAAAAAAAA;
   timer->CAP34 = 0xAAAAAAAA;
   timer->REL12 = 0xAAAAAAAA; 
   timer->REL34 = 0xAAAAAAAA;
   timer->INTCTL_STAT =0x00000101;
   }
}
void startTimer(CSL_TmrRegsOvly timer) {

    CSL_FINST(timer->TCR, TMR_TCR_ENAMODE12, ONCE );   //one shot mode
   CSL_FINST(timer->TCR, TMR_TCR_ENAMODE34, ONCE );   //one shot mode
}

void resetTimer(CSL_TmrRegsOvly timer) {

   CSL_FINST(timer->TIM12, TMR_TIM12_CNT12, RESETVAL );
   CSL_FINST(timer->TIM34, TMR_TIM34_CNT34, RESETVAL );
   CSL_FINST(timer->PRD12, TMR_PRD12_PRD12, RESETVAL );
   CSL_FINST(timer->PRD34, TMR_PRD34_PRD34, RESETVAL );
   timer -> TCR   = CSL_TMR_TCR_RESETVAL;	
   timer -> TGCR  = CSL_TMR_TGCR_RESETVAL;	
   timer -> WDTCR = CSL_TMR_WDTCR_RESETVAL;
   timer -> PID12 = CSL_TMR_PID12_RESETVAL;
   timer -> EMUMGT_CLKSPD = CSL_TMR_EMUMGT_CLKSPD_RESETVAL;
   timer -> GPTDAT_GPDIR  = CSL_TMR_GPTDAT_GPDIR_RESETVAL;
   timer -> GPINT_GPEN    = CSL_TMR_GPINT_GPEN_RESETVAL;
}

void setupTimer64_Mode(CSL_TmrRegsOvly  timer, Uint32 prd12, Uint32 prd34) {

	//setup emulation control by ARM -- commented by vishwa
//	timerEmu_cntrl();	
	// Init GPTx in 64-bit mode
	CSL_FINST(timer->TGCR, TMR_TGCR_TIMMODE, 64BIT_GPTIM);	
	// Remove GPTx TIM12 from Reset
    CSL_FINST(timer->TGCR, TMR_TGCR_TIM12RS, NOT_IN_RESET);
	// Remove GPTx TIM34 from Reset (required in 64-bit)
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM34RS, NOT_IN_RESET);
	
	// Load GPTx TIM1234 Period
	CSL_FINS(timer->PRD12, TMR_PRD12_PRD12, prd12);   
	CSL_FINS(timer->PRD34, TMR_PRD34_PRD34, prd34);
	
	// Set Pulse Width to Max (4) if output pin is available
	//CSL_FINST(timer->TCR, TMR_TCR_CP12, PULSE_MODE);
	//CSL_FINST(timer->TCR, TMR_TCR_PWID12, INACTIVE_4CYCLES);

}

inline startTimerD32UC_Mode_TIM12(CSL_TmrRegsOvly timer) {

    CSL_FINST(timer->TCR, TMR_TCR_ENAMODE12, CONTINUOUS );   //one shot mode
    //CSL_FINST(timer->TCR, TMR_TCR_ENAMODE12, ONCE );   //one shot mode
}


inline stopTimerD32UC_Mode_TIM12(CSL_TmrRegsOvly timer) {

   // CSL_FINST(timer->TCR, TMR_TCR_ENAMODE12, CONTINUOUS );   //one shot mode
    CSL_FINST(timer->TCR, TMR_TCR_ENAMODE12, DISABLED );   //one shot mode
	CSL_FINST(timer->TIM12, TMR_TIM12_CNT12, RESETVAL );
}

inline stopTimerD32UC_Mode_TIM34(CSL_TmrRegsOvly timer) {

   // CSL_FINST(timer->TCR, TMR_TCR_ENAMODE12, CONTINUOUS );   //one shot mode
    CSL_FINST(timer->TCR, TMR_TCR_ENAMODE34, DISABLED );   //one shot mode
	CSL_FINST(timer->TIM34, TMR_TIM34_CNT34, RESETVAL );
}

inline startTimerD32UC_Mode_TIM34(CSL_TmrRegsOvly timer) {

   CSL_FINST(timer->TCR, TMR_TCR_ENAMODE34, CONTINUOUS );   //one shot mode
}

void setupTimerD32UC_Mode_TIM12(CSL_TmrRegsOvly  timer, Uint32 prd12) {
	//setup emulation control by ARM -- -- commented by vishwa
//	timerEmu_cntrl();	
// Init GPTx TIM12 in Dual 32-bit Un-chained mode
	CSL_FINST(timer->TGCR, TMR_TGCR_TIMMODE, 32BIT_DUAL);	
	// Remove GPTx TIM12 from Reset
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM12RS, NOT_IN_RESET);
	
	// Load GPTx TIM1234 Period
	CSL_FINS(timer->PRD12, TMR_PRD12_PRD12, prd12);   
		
	// Set Pulse Width to Max (4) if output pin is available
	//CSL_FINST(timer->TCR, TMR_TCR_CP12, PULSE_MODE);
	//CSL_FINST(timer->TCR, TMR_TCR_PWID12, INACTIVE_4CYCLES);

}
void setupTimerD32UC_Mode_TIM34(CSL_TmrRegsOvly  timer, Uint32 prd34) {
	//setup emulation control by ARM -- commented by vishwa
//	timerEmu_cntrl();	
	// Init GPTx TIM34 in Dual 32-bit Un-chained mode
	CSL_FINST(timer->TGCR, TMR_TGCR_TIMMODE, 32BIT_DUAL);	
	// Remove GPTx TIM34 from Reset 
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM34RS, NOT_IN_RESET);
	// Load GPTx TIM34 Period
	CSL_FINS(timer->PRD34, TMR_PRD34_PRD34, prd34);
	
	// Set Pulse Width to Max (4) if output pin is available
	//CSL_FINST(timer->TCR, TMR_TCR_CP34, PULSE_MODE);
	//CSL_FINST(timer->TCR, TMR_TCR_PWID34, INACTIVE_4CYCLES);
}	

void setupTimerD32C_Mode_TIM12(CSL_TmrRegsOvly  timer, Uint32 prd12, Uint32 prd34) {
	//setup emulation control by ARM -- commented by vishwa
//	timerEmu_cntrl();	
// Init GPTx TIM12 in Dual 32-bit Un-chained mode
	CSL_FINST(timer->TGCR, TMR_TGCR_TIMMODE, 32BIT_CHAINED);	
	// Remove GPTx TIM12 from Reset
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM12RS, NOT_IN_RESET);
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM34RS, NOT_IN_RESET);
	
	// Load GPTx TIM1234 Period
	CSL_FINS(timer->PRD12, TMR_PRD12_PRD12, prd12);   
	CSL_FINS(timer->PRD34, TMR_PRD34_PRD34, prd34); //prescale fs
		
	// Set Pulse Width to Max (4) if output pin is available
	//CSL_FINST(timer->TCR, TMR_TCR_CP12, PULSE_MODE);
	//CSL_FINST(timer->TCR, TMR_TCR_PWID12, INACTIVE_4CYCLES);

}

void setupWDTimer_Mode(CSL_TmrRegsOvly  timer, Uint32 prd12, Uint32 prd34){
	//setup emulation control by ARM -- commented by vishwa
//	timerEmu_cntrl();	
	// Init WDTIM in 64-bit mode
	CSL_FINST(timer->TGCR, TMR_TGCR_TIMMODE, 64BIT_WDTIM);	
	
	// Clear Watchdog Flag (by writing 1)
	CSL_FINST(timer->WDTCR, TMR_WDTCR_WDFLAG, TIMEOUT);	
	
	// Remove WDTIM TIM12 from Reset
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM12RS, NOT_IN_RESET);
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM34RS, NOT_IN_RESET);
	
	// Load GPTx TIM1234 Period
	CSL_FINS(timer->PRD12, TMR_PRD12_PRD12, prd12);   
	CSL_FINS(timer->PRD34, TMR_PRD34_PRD34, prd34); 
		
	// Set Pulse Width to Max (4) if output pin is available
	//CSL_FINST(timer->TCR, TMR_TCR_CP12, PULSE_MODE);
	//CSL_FINST(timer->TCR, TMR_TCR_PWID12, INACTIVE_4CYCLES);
		
}


/* Set up the Timer in Capture mode */
void setupTimer64plus_Capture_Mode(CSL_TmrRegsOvly  timer, Uint32 prd12)
{

	// Init GPTx TIM34 in Gneral Purpose  mode
	CSL_FINST(timer->TGCR, TMR_TGCR_TIMMODE,32BIT_DUAL );	
	// Remove GPTx TIM34 from Reset 
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM12RS, NOT_IN_RESET);
	// Load GPTx TIM34 Period
	CSL_FINS(timer->PRD12, TMR_PRD12_PRD12, prd12);
	//Set CAPMODE==1
	CSL_FINST(timer->TCR, TMR_TCR_CAPMODE12, ENABLE);
	
}

/* Update the counter register onfly  mode */
void setupTimer64plus_Onfly_Mode(CSL_TmrRegsOvly  timer, Uint32 prd12,Uint32 rel12,Uint32 rel34)
{

	// Init GPTx TIM34 in Gneral Purpose  mode
	CSL_FINST(timer->TGCR, TMR_TGCR_TIMMODE,32BIT_DUAL );	
	// Remove GPTx TIM34 from Reset 
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM12RS, NOT_IN_RESET);
	// Load GPTx TIM34 Period
	CSL_FINS(timer->PRD12, TMR_PRD12_PRD12, prd12);
	//Load the rel12 value
	CSL_FINS(timer->REL12, TMR_REL12_REL12, rel12);
	//Load the rel34 value
	CSL_FINS(timer->REL34, TMR_REL34_REL34, rel34);
}

void setupTimer64plus_Event_Mode(CSL_TmrRegsOvly  timer, Uint32 prd12) {

	//setup emulation control by ARM -- commented by vishwa
//	timerEmu_cntrl();	
	// Init GPTx in 32-bit mode
	CSL_FINST(timer->TGCR, TMR_TGCR_TIMMODE, 32BIT_DUAL);	
	// Remove GPTx TIM12 from Reset
    CSL_FINST(timer->TGCR, TMR_TGCR_TIM12RS, NOT_IN_RESET);
	//Enable ENAMODE=01 and READRSTMODE=1
	CSL_FINST(timer->TCR,TMR_TCR_ENAMODE12,ONCE);
	CSL_FINST(timer->TCR,TMR_TCR_READRSTMODE12,ENABLE);
		
	// Load GPTx TIM1234 Period
	CSL_FINS(timer->PRD12, TMR_PRD12_PRD12, prd12);   
	
	
}

void stopTIM12(CSL_TmrRegsOvly timer) {
	CSL_FINST(timer->TCR, TMR_TCR_ENAMODE12, DISABLED);
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM12RS, IN_RESET);
	}
void stopTIM34(CSL_TmrRegsOvly  timer) {
	CSL_FINST(timer->TCR, TMR_TCR_ENAMODE34, DISABLED);
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM34RS, IN_RESET);
	}
	
Uint32 getCnt12 (CSL_TmrRegsOvly  timer){
	Uint32 count = (CSL_FEXTR(timer->TIM12, 31,16) << 16) | CSL_FEXTR(timer->TIM12, 15,0) ;
return(count);
}
inline Uint32 getrawCnt12(CSL_TmrRegsOvly  timer){
	return ( (Uint32)(timer->TIM12));
}

inline Uint32 getrawCnt34(CSL_TmrRegsOvly  timer){
	return ( (Uint32)(timer->TIM34));
}

Uint32 getCnt34 (CSL_TmrRegsOvly  timer){
	Uint32 count = (CSL_FEXTR(timer->TIM34, 31,16) << 16) | CSL_FEXTR(timer->TIM34, 15,0) ;
return(count);
}

Uint32 getCap12 (CSL_TmrRegsOvly  timer){
	Uint32 count = (CSL_FEXTR(timer->CAP12, 31,16) << 16) | CSL_FEXTR(timer->CAP12, 15,0) ;
return(count);
}

Uint32 getPrd12 (CSL_TmrRegsOvly  timer){
	Uint32 count = (CSL_FEXTR(timer->PRD12, 31,16) << 16) | CSL_FEXTR(timer->PRD12, 15,0) ;
return(count);
}

Uint32 getPrd34 (CSL_TmrRegsOvly  timer){
	Uint32 count = (CSL_FEXTR(timer->PRD34, 31,16) << 16) | CSL_FEXTR(timer->PRD34, 15,0) ;
return(count);
}

void WDTIM_service(CSL_TmrRegsOvly  timer) {
  
  CSL_FINST(timer->WDTCR, TMR_WDTCR_WDKEY, PREACTIVE);	
  CSL_FINST(timer->WDTCR, TMR_WDTCR_WDKEY, ACTIVE);	
  
}

#endif


/* Rev.No.   Date/Time               ECN No.          Modifier      */
/* -------   ---------               -------          --------      */

/* 1         24 Feb 2005 10:48:44    7431             a0323288      */
/*                                                                  */
/* check in for regression                                          */
/********************************************************************/ 
/* Rev.No.   Date/Time               ECN No.          Modifier      */
/* -------   ---------               -------          --------      */

/* 1         25 Feb 2005 17:30:32    7535             a0323288      */
/*                                                                  */
/* reg checkin                                                      */
/********************************************************************/ 
/* Rev.No.   Date/Time               ECN No.          Modifier      */
/* -------   ---------               -------          --------      */

/* 1         25 Feb 2005 17:39:56    7536             a0323288      */
/*                                                                  */
/* initial checkin                                                  */
/********************************************************************/ 
/* Rev.No.   Date/Time               ECN No.          Modifier      */
/* -------   ---------               -------          --------      */

/* 4          Mar 17:47:06 7         8046             a0323288      */
/*                                                                  */
/* updated interruptFlag type to volatile boolean for accessibility in isr*/
/********************************************************************/ 
