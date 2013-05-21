/************************************************************************************/
/*                  OMAP-DM290 Evaluation Program                                   */
/*                                                                                  */
/*                  File Name : intc.h                                              */
/*                                                                                  */
/************************************************************************************/
/*  << Revision Histrory >>                                                         */
/*                                                                                  */
/*  Revision    Date        Comments                                                */
/*  ========    ==========  ======================================================= */
/*  Rev 0.0     04/28/2005  First Revision                                          */
/************************************************************************************/
#ifndef		__INTC_H__
#define		__INTC_H__

#define		INTC_FIQ0			(0x30500)
#define		INTC_FIQ1			(0x30502)
#define		INTC_FIQ2			(0x30504)
#define		INTC_FIQ3			(0x30506)
#define		INTC_IRQ0			(0x30508)
#define		INTC_IRQ1			(0x3050A)
#define		INTC_IRQ2			(0x3050C)
#define		INTC_IRQ3			(0x3050E)
#define		INTC_FIQENTRY0		(0x30510)
#define		INTC_FIQENTRY1		(0x30512)
#define		INTC_FIQENTLCK0		(0x30514)
#define		INTC_FIQENTLCK1		(0x30516)
#define		INTC_IRQENTRY0		(0x30518)
#define		INTC_IRQENTRY1		(0x3051A)
#define		INTC_IRQENTLCK0		(0x3051C)
#define		INTC_IRQENTLCK1		(0x3051E)
#define		INTC_FISEL0			(0x30520)
#define		INTC_FISEL1			(0x30522)
#define		INTC_FISEL2			(0x30524)
#define		INTC_FISEL3			(0x30526)
#define		INTC_EINT0			(0x30528)
#define		INTC_EINT1			(0x3052A)
#define		INTC_EINT2			(0x3052C)
#define		INTC_EINT3			(0x3052E)
#define		INTC_INTRAW			(0x30530)
#define		INTC_EABASE0		(0x30538)
#define		INTC_EABASE1		(0x3053A)
#define		INTC_INTPRI00		(0x30540)
#define		INTC_INTPRI01		(0x30542)
#define		INTC_INTPRI02		(0x30544)
#define		INTC_INTPRI03		(0x30546)
#define		INTC_INTPRI04		(0x30548)
#define		INTC_INTPRI05		(0x3054A)
#define		INTC_INTPRI06		(0x3054C)
#define		INTC_INTPRI07		(0x3054E)
#define		INTC_INTPRI08		(0x30550)
#define		INTC_INTPRI09		(0x30552)
#define		INTC_INTPRI10		(0x30554)
#define		INTC_INTPRI11		(0x30556)
#define		INTC_INTPRI12		(0x30558)
#define		INTC_INTPRI13		(0x3055A)
#define		INTC_INTPRI14		(0x3055C)
#define		INTC_INTPRI15		(0x3055E)
#define		INTC_INTPRI16		(0x30560)
#define		INTC_INTPRI17		(0x30562)
#define		INTC_INTPRI18		(0x30564)
#define		INTC_INTPRI19		(0x30566)
#define		INTC_INTPRI20		(0x30568)
#define		INTC_INTPRI21		(0x3056A)
#define		INTC_INTPRI22		(0x3056C)
#define		INTC_INTPRI23		(0x3056E)
#define		INTC_INTPRI24		(0x30570)
#define		INTC_INTPRI25		(0x30572)

/* Interrupt ID */
#define		INT_TMR0		(0)		// TIMER0 Interrupt
#define		INT_TMR1		(1)		// TIMER1 Interrupt
#define		INT_TMR2		(2)		// TIMER2 Interrupt
#define		INT_TMR3		(3)		// TIMER3 Interrupt
#define		INT_TMR4		(4)		// TIMER4 Interrupt
#define		INT_TMR5		(5)		// TIMER5 Interrupt
#define		INT_SIF			(6)		// Serial I/F Interrupt
/* #define	INT_RSV			(7)	*/	// Reserved
#define		INT_WDT			(8)		// Watch Dog Timer interrupt
#define		INT_I2C0		(9)		// I2C #0 interrupt
#define		INT_I2C1		(10)	// I2C #1 interrupt
/* #define	INT_RSV			(11) */	// Reserved
/* #define	INT_RSV			(12) */	// Reserved
#define		INT_EXT0		(13)	// External #0 Interrupt (GIO0)
#define		INT_EXT1		(14)	// External #1 Interrupt (GIO1)
#define		INT_EXT2		(15)	// External #2 Interrupt (GIO2)
#define		INT_EXT3		(16)	// External #3 Interrupt (GIO3)
#define		INT_EXT4		(17)	// External #4 Interrupt (GIO4)
#define		INT_EXT5		(18)	// External #5 Interrupt (GIO5)
#define		INT_EXT6		(19)	// External #6 Interrupt (GIO6)
#define		INT_EXT7		(20)	// External #7 Interrupt (GIO7)
#define		INT_MTC0		(21)	// MTC Interrupt #1
#define		INT_MTC1		(22)	// MTC Interrupt #2
#define		INT_CCDVD0		(23)	// CCD VD Interrupt #1
#define		INT_CCDVD1		(24)	// CCD VD Interrupt #2
#define		INT_CCD_WEN		(25)	// CCD C_WEN Interrupt
#define		INT_ISP0		(26)	// ISP #0 Interrupt
#define		INT_ISP1		(27)	// ISP #1 Interrupt
#define		INT_ISP2		(28)	// ISP #2 Interrupt
#define		INT_ISP3		(29)	// ISP #3 Interrupt
#define		INT_ISPIF		(30)	// ISPIF VD interrupt
#define		INT_H3A0		(31)	// H3A Interrupt #0
#define		INT_H3A1		(32)	// H3A Interrupt #1
#define		INT_CLKC		(33)	// Clock Controller Interrupt
#define		INT_CCPRX		(34)	// CCP Receiver Interrupt
#define		INT_CCPTX		(35)	// CCP Transmitter Interrupt
#define		INT_VPIF		(36)	// Video Parallel I/F Interrupt
#define		INT_PWM0		(37)	// PWM #0 Interrupt
#define		INT_PWM1		(38)	// PWM #1 Interrupt
#define		INT_PWM2		(39)	// PWM #2 Interrupt
#define		INT_PWM3		(40)	// PWM #3 Interrupt
#define		INT_PWM4		(41)	// PWM #4 Interrupt
#define		INT_PWM5		(42)	// PWM #5 Interrupt
#define		INT_PWM6		(43)	// PWM #6 Interrupt
#define		INT_PWM7		(44)	// PWM #7 Interrupt
#define		INT_ADCMP		(45)	// ADC Interrupt
#define		INT_SEQ			(46)	// Sequencer Sync Interrupt
#define		INT_iMX			(47)	// iMX Interrupt
#define		INT_VLCD		(48)	// VLCD Interrupt
#define		INT_COPR		(49)	// Coprocessor Interrupt
#define		INT_DCT			(50)	// DCT Interrupt
/* #define	INT_RSV			(51) */	// Reserved

#pragma SWI_ALIAS(EnableIRQ, 0)
#pragma SWI_ALIAS(DisableIRQ, 1)
#pragma SWI_ALIAS(EnableFIQ, 2)
#pragma SWI_ALIAS(DisableFIQ, 3)

extern void EnableIRQ();
extern void DisableIRQ();
extern void EnableFIQ();
extern void DisableFIQ();

extern int IRQ_Entry;

#endif
