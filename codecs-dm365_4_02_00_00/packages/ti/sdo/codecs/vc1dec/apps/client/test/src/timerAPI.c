/******************************************************************************/
/* This is proprietary information, not to be published -- TI INTERNAL DATA   */
/* Copyright (C) 2003, Texas Instruments, Inc.  All Rights Reserved.          */
/* Author: Satheesh Radhakrishnan							      */
/* Date: Jul 16, 2003									      */
/*												      */
/******************************************************************************/

#include "timerAPI.h"
#include <cslr_tmr.h>
#include <cslr_tmr_001.h>

const CSL_TmrRegsOvly TIMER_REGS[3]= {CSL_TMR_0_REGS, CSL_TMR_1_REGS, CSL_TMR_2_REGS}; 

void resetTimer(CSL_TmrRegsOvly timer);
void setupTimer64(CSL_TmrRegsOvly  timer, Uint64 Period);
void startTimer(CSL_TmrRegsOvly  timer);
Uint64 getCount(CSL_TmrRegsOvly  timer);
void stopTimer(CSL_TmrRegsOvly timer);
void profileInit(int i);
void profileStart(int i);
Uint64 profileCount(int i);
Uint64 profileEnd(int i);
/*Resets the Timer and the state variables This should be done only once during initialization*/
void TimerReset(TimerState* tState, int i);
/* This should be called where you want start the profiling*/
void ProbeStart(TimerState* tState, int i);
/* This should be called where you want end the profiling*/
void ProbeEnd(TimerState* tState, int i);



void resetTimer(CSL_TmrRegsOvly timer)
{
   timer -> TCR   = CSL_TMR_TCR_RESETVAL;
   CSL_FINST(timer->TIM12, TMR_TIM12_CNT12, RESETVAL);
   CSL_FINST(timer->TIM34, TMR_TIM34_CNT34, RESETVAL);
   CSL_FINST(timer->PRD12, TMR_PRD12_PRD12, RESETVAL);
   CSL_FINST(timer->PRD34, TMR_PRD34_PRD34, RESETVAL);
   	
   timer -> TGCR  		= CSL_TMR_TGCR_RESETVAL;	
   timer -> WDTCR			= CSL_TMR_WDTCR_RESETVAL;
   timer -> PID12 		= (unsigned int)0x00010701C;//SL_TMR_PID12_RESETVAL;
   timer -> EMUMGT_CLKSPD 	= CSL_TMR_EMUMGT_CLKSPD_RESETVAL;
   timer -> GPTDAT_GPDIR  	= CSL_TMR_GPTDAT_GPDIR_RESETVAL;
   timer -> GPINT_GPEN    	= CSL_TMR_GPINT_GPEN_RESETVAL;
}

void setupTimer64(CSL_TmrRegsOvly  timer, Uint64 Period)
{
	Uint32 prd12, prd34;
	
	CSL_FINST(timer->TGCR, TMR_TGCR_TIMMODE, 64BIT_GPTIM);	// Init GPTx in 64-bit mode		
    	CSL_FINST(timer->TGCR, TMR_TGCR_TIM12RS, NOT_IN_RESET);	// Remove GPTx TIM12 from Reset	
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM34RS, NOT_IN_RESET);	// Remove GPTx TIM34 from Reset (required in 64-bit)
	
	
	prd12 = Period >> 32;
	prd34 = Period;
	CSL_FINS(timer->PRD12, TMR_PRD12_PRD12, prd12);			// Load GPTx TIM1234 Period   
	CSL_FINS(timer->PRD34, TMR_PRD34_PRD34, prd34);
}

void startTimer(CSL_TmrRegsOvly  timer)
{
	CSL_FINST(timer->TCR, TMR_TCR_ENAMODE12, ONCE);	//Start TIM12 in Oneshot
	CSL_FINST(timer->TCR, TMR_TCR_ENAMODE34, ONCE);	//Start TIM32 in Oneshot
}

Uint64 getCount(CSL_TmrRegsOvly  timer)
{
	Uint32 cnt12;
	Uint32 cnt34;
	Uint64 Count;

	cnt12 = (CSL_FEXTR(timer->TIM12, 31,16) << 16) | CSL_FEXTR(timer->TIM12, 15,0) ; //Get Count from TIM12
	cnt34 = (CSL_FEXTR(timer->TIM34, 31,16) << 16) | CSL_FEXTR(timer->TIM34, 15,0) ; //Get Count from TIM34
	Count = cnt34;
	Count = (Count << 32) | cnt12;
	return(Count);
}

void stopTimer(CSL_TmrRegsOvly timer)
{
	CSL_FINST(timer->TCR, TMR_TCR_ENAMODE12, DISABLED); //Stop TIM12
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM12RS, IN_RESET);
	CSL_FINST(timer->TCR, TMR_TCR_ENAMODE34, DISABLED); //Stop TIM34
	CSL_FINST(timer->TGCR, TMR_TGCR_TIM34RS, IN_RESET);
}

void profileInit(int i)
{
	CSL_TmrRegsOvly  timer;

	timer = TIMER_REGS[i];
	resetTimer(timer);
	setupTimer64(timer, 0xFFFFFFFFFFFFFFFF);
	
	CSL_FINS(timer->TIM12, TMR_TIM12_CNT12, 0);	// Load GPTx TIM1234 Counter w/ 0 (Start at beginning)
	CSL_FINS(timer->TIM34, TMR_TIM34_CNT34, 0);
}

void profileStart(int i)
{
	CSL_TmrRegsOvly  timer;

	timer = TIMER_REGS[i];
	startTimer(timer);
}

Uint64 profileCount(int i)
{
	Uint64 Count;
	CSL_TmrRegsOvly  timer;

	timer = TIMER_REGS[i];
	Count = getCount(timer);
	return(Count);
}

Uint64 profileEnd(int i)
{
	Uint64 Count;
	CSL_TmrRegsOvly  timer;

	timer = TIMER_REGS[i];
  	stopTimer(timer);
	Count = getCount(timer);
	resetTimer(timer);
	return((Count-60)*2);// 60 cycles overhead due to API calls**/
}


/*Resets the Timer and the state variables This should be done only once during initialization*/
void TimerReset(TimerState* tState, int i)
{
	CSL_TmrRegsOvly  timer;
	timer = TIMER_REGS[i];

	tState->Count = 0;   
	tState->TotalCycles = 0;
	tState->CurrentCycleCount = 0;
	tState->AverageCycleCount = 0;
	tState->PeakCycleCount = 0;
	
	resetTimer(timer);
	setupTimer64(timer, 0xFFFFFFFFFFFFFFFF);	
	CSL_FINS(timer->TIM12, TMR_TIM12_CNT12, 0);	// Load GPTx TIM1234 Counter w/ 0 (Start at beginning)
	CSL_FINS(timer->TIM34, TMR_TIM34_CNT34, 0);
}

/* This should be called where you want start the profiling*/
void ProbeStart(TimerState* tState, int i)
{
	CSL_TmrRegsOvly  timer;
	timer = TIMER_REGS[i];

	resetTimer(timer);
	setupTimer64(timer, 0xFFFFFFFFFFFFFFFF);	
	CSL_FINS(timer->TIM12, TMR_TIM12_CNT12, 0);	// Load GPTx TIM1234 Counter w/ 0 (Start at beginning)
	CSL_FINS(timer->TIM34, TMR_TIM34_CNT34, 0);



	startTimer(timer);
}

/* This should be called where you want end the profiling*/
void ProbeEnd(TimerState* tState, int i)
{
	CSL_TmrRegsOvly  timer;
	timer = TIMER_REGS[i];

   	tState->Count++;
   
	tState->CurrentCycleCount = (getCount(timer)-64)<<1;	/*Calculate current cycle count*/


         
	tState->TotalCycles += tState->CurrentCycleCount; 
   
   	/*Calculate average*/
   	tState->AverageCycleCount = (tState->TotalCycles)/(tState->Count);            
   
   	/*Calculate Peak*/      
   	if(tState->PeakCycleCount < tState->CurrentCycleCount)
      	tState->PeakCycleCount = tState->CurrentCycleCount;
}







