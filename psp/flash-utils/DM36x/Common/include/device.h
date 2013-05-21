/* --------------------------------------------------------------------------
  FILE        : device.h                                                   
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Sandeep Paulraj
  DESC        : Modified for DM36x
----------------------------------------------------------------------------- */

#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/


/************************************************************
* Global Variable Declarations                              *
************************************************************/

extern const String devString;


/******************************************************
* Global Typedef declarations                         *
******************************************************/

// Supported bootmodes
typedef enum _DEVICE_BootMode_
{
  DEVICE_BOOTMODE_NAND    = 0x0,    // NAND boot mode (RBL -> UBL) 
  DEVICE_BOOTMODE_AEMIF   = 0x1,    // NOR boot mode (execute in place)
  DEVICE_BOOTMODE_SD_MMC  = 0x2,    // SD card
  DEVICE_BOOTMODE_UART    = 0x3,     // UART
  DEVICE_BOOTMODE_USB     = 0x4,     
  DEVICE_BOOTMODE_SPI     = 0x5,    
  DEVICE_BOOTMODE_EMAC    = 0x6,    
  DEVICE_BOOTMODE_HPI     = 0x7     
}
DEVICE_BootMode;

// Supported buswidth
typedef enum _DEVICE_BusWidth_
{
  DEVICE_BUSWIDTH_8BIT  = BUS_8BIT,
  DEVICE_BUSWIDTH_16BIT = BUS_16BIT
}
DEVICE_BusWidth;

// System Control Module register structure for DM365
typedef struct _DEVICE_SYS_MODULE_REGS_
{
  VUint32 PINMUX[5];         //0x00
  VUint32 BOOTCFG;           //0x14
  VUint32 ARM_INTMUX;        //0x18
  VUint32 EDMA_EVTMUX;       //0x1C
  VUint32 DDR_SLEW;          //0x20
  VUint32 CLKOUT;            //0x24
  VUint32 DEVICE_ID;         //0x28
  VUint32 VDAC_CONFIG;       //0x2C
  VUint32 TIMER64_CTL;       //0x30
  VUint32 USBPHY_CTL;        //0x34
  VUint32 MISC;              //0x38
  VUint32 MSTPRI[2];         //0x3C
  VUint32 VPSS_CLKCTL;       //0x44
  VUint32 PERI_CLKCTRL;      //0x48
  VUint32 DEEPSLEEP;         //0x4C
  VUint32 DFT_ENABLE;        //0x50
  VUint32 DEBOUNCE[8];		 //0x54
  VUint32 VTPIOCR;			 //0x74
  VUint32 PUPDCTL0;          //0x78
  VUint32 PUPDCTL1;          //0x7C
  VUint32 HDIMCOPBT;		 //0x80
  VUint32 PLL0_CONFIG;       //0x84
  VUint32 PLL1_CONFIG;       //0x88
}
DEVICE_SysModuleRegs;

#define SYSTEM ((DEVICE_SysModuleRegs*) 0x01C40000)

#define DEVICE_BOOTCFG_BOOTMODE_MASK    (0x000000E0) //changed this refer chapter 5
#define DEVICE_BOOTCFG_BOOTMODE_SHIFT   (5) //changed this as well refer chapter 5

#define DEVICE_BOOTCFG_EMIFWIDTH_MASK   (0x00000004) //chnaged this from bit 3 to bit 2
#define DEVICE_BOOTCFG_EMIFWIDTH_SHIFT  (2) //changed this from 3 to 2

#define DEVICE_PINMUX_UART0_MASK        (0x00000001)
#define DEVICE_PINMUX_EMIF_MASK         (0x00000FFF)

#define DEVICE_PINMUX_UART0_EN          (0x00000001)
#define DEVICE_PINMUX_EMIF_EN           (0x00000000)
#define DEVICE_PINMUX_ATA_EN            (0x00020000)

#define DEVICE_VTPIOCR_PWRDN_MASK       (0x00000040)
#define DEVICE_VTPIOCR_LOCK_MASK        (0x00000080)
#define DEVICE_VTPIOCR_PWRSAVE_MASK     (0x00000100)
#define DEVICE_VTPIOCR_CLR_MASK         (0x00002000)
#define DEVICE_VTPIOCR_VTPIOREADY_MASK  (0x00004000)
#define DEVICE_VTPIOCR_READY_MASK       (0x00008000)

#define DEVICE_MISC_PLL1POSTDIV_MASK    (0x00000002)
#define DEVICE_MISC_AIMWAITST_MASK      (0x00000001)
#define DEVICE_MISC_TIMER2WDT_MASK      (0x00000010)

typedef struct _DEVICE_GPIO_REGS_
{
  VUint32 PID;         //0x00
  VUint32 RSVD1;           //0x4
  VUint32 BINTEN;        //0x8
  VUint32 RSVD2;       //0xC
  VUint32 DIR01;          //0x10
  VUint32 OUTDATA01;            //0x14
  VUint32 SETDATA01;         //0x18
  VUint32 CLRDATA01;       //0x1C
  VUint32 INDTATA01;       //0x20
  VUint32 SETRIS01;        //0x24
  VUint32 CLRRIS01;              //0x28
  VUint32 SETFAL01;         //0x2C
  VUint32 CLRFAL01;       //0x30
  VUint32 INTSTAT01;      //0x34
  VUint32 DIR02;          //0x10
  VUint32 OUTDATA02;            //0x14
  VUint32 SETDATA02;         //0x18
  VUint32 CLRDATA02;       //0x1C
  VUint32 INDTATA02;       //0x20
  VUint32 SETRIS02;        //0x24
  VUint32 CLRRIS02;              //0x28
  VUint32 SETFAL02;         //0x2C
  VUint32 CLRFAL02;       //0x30
  VUint32 INTSTAT02;      //0x34
}
DEVICE_GPIORegs;

#define GPIO ((DEVICE_GPIORegs*) 0x01C67000)


// ARM Interrupt Controller register structure - See sprufb3.pdf, Chapter 8 for more details.
typedef struct _DEVICE_AINTC_REGS_
{
  VUint32 FIQ0;		//0x00
  VUint32 FIQ1;		//0x04
  VUint32 IRQ0;		//0x08
  VUint32 IRQ1;		//0x0c
  VUint32 FIQENTRY;	//0x10
  VUint32 IRQENTRY;	//0x14
  VUint32 EINT0;	//0x18
  VUint32 EINT1;	//0x1c
  VUint32 INTCTL;	//0x20
  VUint32 EABASE;	//0x24
  VUint8 RSVD0[8];	//0x28
  VUint32 INTPRI0;	//0x30
  VUint32 INTPRI1;	//0x34
  VUint32 INTPRI2;	//0x38
  VUint32 INTPRI3;	//0x3c
  VUint32 INTPRI4;	//0x40
  VUint32 INTPRI5;	//0x44
  VUint32 INTPRI6;	//0x48
  VUint32 INTPRI7;	//0x4c
}
DEVICE_AIntcRegs;

#define AINTC ((DEVICE_AIntcRegs*) 0x01C48000)


// modified for DM365.Referred to GEL file 
typedef struct _DEVICE_PLL_REGS_
{
  VUint32 PID;			//0x00
  VUint8 RSVD0[224];	//0x04
  VUint32 RSTYPE;		//0xe4
  VUint8 RSVD1[24];  	//0xe8
  VUint32 PLLCTL;		//0x100
  VUint8 RSVD2[4];  	//0x104
  VUint32 SECCTL;		//0x108
  VUint32 RV;			//0x10c
  VUint32 PLLM;			//0x110
  VUint32 PREDIV;		//0x114
  VUint32 PLLDIV1;		//0x118
  VUint32 PLLDIV2;		//0x11c
  VUint32 PLLDIV3;  	//0x120
  VUint32 OSCDIV1;		//0x124
  VUint32 POSTDIV;		//0x128
  VUint32 BPDIV;		//0x12c
  VUint8 RSVD5[8];  	//0x130
  VUint32 PLLCMD;		//0x138
  VUint32 PLLSTAT;		//0x13c
  VUint32 ALNCTL;		//0x140
  VUint32 DCHANGE;		//0x144
  VUint32 CKEN;			//0x148
  VUint32 CKSTAT;		//0x14c
  VUint32 SYSTAT;		//0x150
  VUint8 RSVD6[12];		//0x154
  VUint32 PLLDIV4;		//0x160
  VUint32 PLLDIV5;		//0x164
  VUint32 PLLDIV6;		//0x168
  VUint32 PLLDIV7;		//0x16C
  VUint32 PLLDIV8;		//0x170
  VUint32 PLLDIV9;		//0x174
}
DEVICE_PLLRegs;

#define PLL1 ((DEVICE_PLLRegs*) 0x01C40800)
#define PLL2 ((DEVICE_PLLRegs*) 0x01C40C00)

#define DEVICE_PLLCTL_PLLEN_MASK    (0x00000001)
#define DEVICE_PLLCTL_PLLPWRDN_MASK (0x00000002)
#define DEVICE_PLLCTL_PLLRST_MASK   (0x00000008)
#define DEVICE_PLLCTL_PLLDIS_MASK   (0x00000010)
#define DEVICE_PLLCTL_PLLENSRC_MASK (0x00000020)
#define DEVICE_PLLCTL_CLKMODE_MASK  (0x00000100)

#define DEVICE_PLLCMD_GOSET_MASK    (0x00000001)
#define DEVICE_PLLSTAT_GOSTAT_MASK  (0x00000001)
#define DEVICE_PLLDIV_EN_MASK       (0x00008000)
#define DEVICE_PLLSTAT_LOCK_MASK    (0x00000002)

//these values have been taken from the GEl file
#define DEVICE_PLL1_MULTIPLIER  	(0x51)
#define DEVICE_PLL2_MULTIPLIER      (0x63)

#define DEVICE_OSC_FREQ         (24000000u)
#define DEVICE_SYSTEM_FREQ ((DEVICE_PLL1_MULTIPLIER * DEVICE_OSC_FREQ)>>3)

// Power/Sleep Ctrl Register structure - See sprufb3.pdf, Chapter 7
typedef struct _DEVICE_PSC_REGS_
{
  VUint32 PID;        // 0x000
  VUint8 RSVD0[16];   // 0x004
  VUint8 RSVD1[4];    // 0x014
  VUint32 INTEVAL;    // 0x018
  VUint8 RSVD2[36];   // 0x01C
  VUint32 MERRPR0;    // 0x040
  VUint32 MERRPR1;    // 0x044
  VUint8 RSVD3[8];    // 0x048
  VUint32 MERRCR0;    // 0x050
  VUint32 MERRCR1;    // 0x054
  VUint8 RSVD4[8];    // 0x058
  VUint32 PERRPR;     // 0x060
  VUint8 RSVD5[4];    // 0x064
  VUint32 PERRCR;     // 0x068
  VUint8 RSVD6[4];    // 0x06C
  VUint32 EPCPR;      // 0x070
  VUint8 RSVD7[4];    // 0x074
  VUint32 EPCCR;      // 0x078
  VUint8 RSVD8[144];  // 0x07C
  VUint8 RSVD9[20];   // 0x10C
  VUint32 PTCMD;      // 0x120
  VUint8 RSVD10[4];   // 0x124
  VUint32 PTSTAT;     // 0x128
  VUint8 RSVD11[212]; // 0x12C
  VUint32 PDSTAT0;    // 0x200
  VUint32 PDSTAT1;    // 0x204
  VUint8 RSVD12[248]; // 0x208
  VUint32 PDCTL0;     // 0x300
  VUint32 PDCTL1;     // 0x304
  VUint8 RSVD13[536]; // 0x308
  VUint32 MCKOUT0;    // 0x520
  VUint32 MCKOUT1;    // 0x524
  VUint8 RSVD14[728]; // 0x528
  VUint32 MDSTAT[52]; // 0x800
  VUint8 RSVD15[304]; // 0x8D0
  VUint32 MDCTL[52];  // 0xA00
}
DEVICE_PSCRegs;

#define PSC ((DEVICE_PSCRegs*) 0x01C41000)

// PSC constants
#define LPSC_TPCC			(0)
#define LPSC_TPTC0			(1)
#define LPSC_TPTC1          (2)
#define LPSC_TPTC2          (3)
#define LPSC_TPTC3          (4)
#define LPSC_TIMER3         (5)
#define LPSC_SPI1           (6)
#define LPSC_MMC_SD1        (7)
#define LPSC_ASP1           (8)
#define LPSC_USB            (9)
#define LPSC_PWM3           (10)
#define LPSC_SPI2           (11)
#define LPSC_RTO            (12)
#define LPSC_DDR2           (13)
#define LPSC_AEMIF          (14)
#define LPSC_MMC_SD0        (15)
#define LPSC_MEMSTK         (16)
#define TIMER4				(17)
#define LPSC_I2C            (18)
#define LPSC_UART0          (19)
#define LPSC_UART1          (20)
#define LPSC_UHPI          	(21)
#define LPSC_SPIO           (22)
#define LPSC_PWM0           (23)
#define LPSC_PWM1           (24)
#define LPSC_PWM2           (25)
#define LPSC_GPIO           (26)
#define LPSC_TIMER0         (27)
#define LPSC_TIMER1         (28)
#define LPSC_TIMER2         (29)
#define LPSC_SYSMOD         (30)
#define LPSC_ARM            (31)
#define LPSC_SPI3			(38)
#define LPSC_SPI4			(39)
#define LPSC_CPGMAC			(40)
#define LPSC_RTC			(41)
#define LPSC_KEYSCAN        (42)
#define LPSC_ADC			(43)
#define LPSC_VOICECODEC		(44)
#define LPSC_IMCOP			(50)
#define LPSC_KALEIDO		(51)


#define EMURSTIE_MASK       (0x00000200)

#define PD0                 (0)

#define PSC_ENABLE          (0x3)
#define PSC_DISABLE         (0x2)
#define PSC_SYNCRESET       (0x1)
#define PSC_SWRSTDISABLE    (0x0)

 
// DDR2 Memory Ctrl Register structure - See sprueh7d.pdf for more details.
typedef struct _DEVICE_DDR2_REGS_
{
  VUint8 RSVD0[4];        //0x00
  VUint32 SDRSTAT;        //0x04
  VUint32 SDBCR;          //0x08
  VUint32 SDRCR;          //0x0C
  VUint32 SDTIMR;         //0x10
  VUint32 SDTIMR2;        //0x14
  VUint8 RSVD1[4];        //0x18
  VUint32 SDBCR2;         //0x1C
  VUint32 PBBPR;          //0x20
  VUint8 RSVD2[156];      //0x24 
  VUint32 IRR;            //0xC0
  VUint32 IMR;            //0xC4
  VUint32 IMSR;           //0xC8
  VUint32 IMCR;           //0xCC
  VUint8 RSVD3[20];       //0xD0
  VUint32 DDRPHYCR;       //0xE4
  VUint32 DDRPHYCR2;       //0xE8
  VUint8 RSVD4[4];        //0xEC
}
DEVICE_DDR2Regs;

#define DDR                         ((DEVICE_DDR2Regs*) 0x20000000)

#define DEVICE_DDR2_TEST_PATTERN    (0xA55AA55Au)
//the size of DDR is 1GB
#define DEVICE_DDR2_RAM_SIZE        (0x40000000u)

#define DEVICE_MAX_IMAGE_SIZE       (0x02000000u)
#define DEVICE_DDR2_START_ADDR      (0x80000000u)
#define DEVICE_DDR2_END_ADDR        ((DEVICE_DDR2_START_ADDR + DEVICE_DDR2_RAM_SIZE))


// AEMIF Register structure - See sprued1b.pdf for more details.
typedef struct _DEVICE_EMIF_REGS_
{
  VUint32 ERCSR;             // 0x00
  VUint32 AWCCR;             // 0x04
  VUint8  RSVD0[8];          // 0x08
  VUint32 A1CR;              // 0x10
  VUint32 A2CR;              // 0x14
  VUint8  RSVD1[40];         // 0x18
  VUint32 EIRR;              // 0x40
  VUint32 EIMR;              // 0x44
  VUint32 EIMSR;             // 0x48
  VUint32 EIMCR;             // 0x4C
  VUint8  RSVD2[12];         // 0x50
  VUint32 ONENANDCTL;        // 0x5C  
  VUint32 NANDFCR;           // 0x60
  VUint32 NANDFSR;           // 0x64
  VUint8  RSVD3[8];          // 0x68
  VUint32 NANDF1ECC;         // 0x70
  VUint32 NANDF2ECC;         // 0x74
  VUint8  RSVD4[68];         // 0x78
  VUint32 NAND4BITECCLOAD;   // 0xBC
  VUint32 NAND4BITECC1;      // 0xC0
  VUint32 NAND4BITECC2;      // 0xC4
  VUint32 NAND4BITECC3;      // 0xC8
  VUint32 NAND4BITECC4;      // 0xCC
  VUint32 NANDERRADD1;       // 0xD0
  VUint32 NANDERRADD2;       // 0xD4
  VUint32 NANDERRVAL1;       // 0xD8
  VUint32 NANDERRVAL2;       // 0xDC
}
DEVICE_EmifRegs;

//The memory map is different for DM35x and DM36x w.r.t AEMIF
#define AEMIF ((DEVICE_EmifRegs*) 0x01D10000)

#define DEVICE_EMIF_NUMBER_CE_REGION        (2)
#define DEVICE_EMIF_FIRST_CE_START_ADDR     (0x02000000)
#define DEVICE_EMIF_INTER_CE_REGION_SIZE    (0x04000000)

#define DEVICE_EMIF_NANDFCR_4BITECC_SEL_MASK            (0x00000030)
#define DEVICE_EMIF_NANDFCR_4BITECC_SEL_SHIFT           (4)

#define DEVICE_EMIF_AWCC_WAITSTATE_MASK                 (0x000000FF)

#define DEVICE_EMIF_NANDFCR_4BITECC_START_MASK           (0x00001000)
#define DEVICE_EMIF_NANDFCR_4BITECC_START_SHIFT          (12)
#define DEVICE_EMIF_NANDFCR_4BITECC_ADD_CALC_START_MASK  (0x00002000)
#define DEVICE_EMIF_NANDFCR_4BITECC_ADD_CALC_START_SHIFT (13)

#define DEVICE_EMIF_NANDFSR_ECC_STATE_MASK              (0x00000F00)
#define DEVICE_EMIF_NANDFSR_ECC_STATE_SHIFT             (8)
#define DEVICE_EMIF_NANDFSR_ECC_ERRNUM_MASK             (0x00030000)
#define DEVICE_EMIF_NANDFSR_ECC_ERRNUM_SHIFT            (16)


// UART Register structure - See sprued9b.pdf for more details.
typedef struct _DEVICE_UART_REGS_
{
  VUint32 RBR;			//0x00
  VUint32 IER;			//0x04
  VUint32 IIR;			//0x08
  VUint32 LCR;			//0x0c
  VUint32 MCR;			//0x10
  VUint32 LSR;			//0x14
  VUint32 MSR;			//0x18
  VUint8  RSVD0[4];		//0x1c         
  VUint8  DLL;			//0x20
  VUint8  RSVD1[3];
  VUint8  DLH;			//0x24
  VUint8  RSVD2[3];  
  VUint32 PID1;			//0x28
  VUint32 PID2;			//0x2c
  VUint32 PWREMU_MGNT;	//0x30
  VUint32 MDR;			//0x34
}
DEVICE_UartRegs;

#define THR RBR
#define FCR IIR

#define UART0 ((DEVICE_UartRegs*) 0x01C20000)

#define DEVICE_UART0_DESIRED_BAUD   (115200)
#define DEVICE_UART0_OVERSAMPLE_CNT (16)

// Timer Register structure - See spruee5a.pdf for more details.
typedef struct _DEVICE_TIMER_REGS_
{
    VUint32 PID12;          // 0x00
    VUint32 EMUMGT_CLKSPD;  // 0x04
    VUint8  RSVD0[8];       // 0x08
    VUint32 TIM12;          // 0x10
    VUint32 TIM34;          // 0x14
    VUint32 PRD12;          // 0x18
    VUint32 PRD34;          // 0x1C
    VUint32 TCR;            // 0x20
    VUint32 TGCR;           // 0x24
    VUint32 WDTCR;          // 0x28
    VUint8  RSVD1[8];       // 0x2C
    VUint32 REL12;          // 0x34
    VUint32 REL34;          // 0x38
    VUint32 CAP12;          // 0x3C
    VUint32 CAP34;          // 0x40
    VUint32 INTCTL_STAT;    // 0x44
}
DEVICE_TimerRegs;

#define TIMER0 ((DEVICE_TimerRegs*) 0x01C21400)

// I2C Register structure - See spruee0a.pdf for more details.
typedef struct _DEVICE_I2C_REGS_
{
    VUint32 ICOAR;      // 0x00
    VUint32 ICIMR;      // 0x04
    VUint32 ICSTR;      // 0x08
    VUint32 ICCLKL;     // 0x0C
    VUint32 ICCLKH;     // 0x10
    VUint32 ICCNT;      // 0x14
    VUint32 ICDRR;      // 0x18
    VUint32 ICSAR;      // 0x1C
    VUint32 ICDXR;      // 0x20
    VUint32 ICMDR;      // 0x24
    VUint32 ICIVR;      // 0x28
    VUint32 ICEMDR;     // 0x2C
    VUint32 ICPSC;      // 0x30
    VUint32 ICPID1;     // 0x34
    VUint32 ICPID2;     // 0x38
}
DEVICE_I2CRegs;

#define I2C0 ((DEVICE_I2CRegs*) 0x01C21000)

#define DEVICE_I2C_TARGET_FREQ      (200000u)
#define DEVICE_I2C_OWN_ADDRESS      (0x10)

#define I2C_ICMDR_NACKMOD       (0x00008000)
#define I2C_ICMDR_FRE           (0x00004000)
#define I2C_ICMDR_STT           (0x00002000)
#define I2C_ICMDR_STP           (0x00000800)
#define I2C_ICMDR_MST           (0x00000400)
#define I2C_ICMDR_TRX           (0x00000200)
#define I2C_ICMDR_XA            (0x00000100)
#define I2C_ICMDR_RM            (0x00000080)
#define I2C_ICMDR_DLB           (0x00000040)
#define I2C_ICMDR_IRS           (0x00000020)
#define I2C_ICMDR_STB           (0x00000010)
#define I2C_ICMDR_FDF           (0x00000008)
#define I2C_ICMDR_BC8           (0x00000007)

#define I2C_ICSTR_AL_MSK        (0x00000001)
#define I2C_ICSTR_NACK_MSK      (0x00000002)
#define I2C_ICSTR_ARDY_MSK      (0x00000004)
#define I2C_ICSTR_ICRRDY_MSK    (0x00000008)
#define I2C_ICSTR_ICXRDY_MSK    (0x00000010)
#define I2C_ICSTR_SCD_MSK       (0x00000020)
#define I2C_ICSTR_BB_MSK        (0x00001000)

#define I2C_ICEMDR_EXTMODE      (0x00000000)



typedef struct _DEVICE_SDMMC_REGS_
{
    volatile Uint16 MMCCTL;
    volatile Uint8 RSVD0[2];
    volatile Uint16 MMCCLK;
    volatile Uint8 RSVD1[2];
    volatile Uint16 MMCST0;
    volatile Uint8 RSVD2[2];
    volatile Uint16 MMCST1;
    volatile Uint8 RSVD3[2];
    volatile Uint16 MMCIM;
    volatile Uint8 RSVD4[2];
    volatile Uint16 MMCTOR;
    volatile Uint8 RSVD5[2];
    volatile Uint16 MMCTOD;
    volatile Uint8 RSVD6[2];
    volatile Uint16 MMCBLEN;
    volatile Uint8 RSVD7[2];
    volatile Uint16 MMCNBLK;
    volatile Uint8 RSVD8[2];
    volatile Uint16 MMCNBLC;
    volatile Uint8 RSVD9[2];
    volatile Uint32 MMCDRR;
    volatile Uint32 MMCDXR;
    volatile Uint32 MMCCMD;
    volatile Uint32 MMCARGHL;
    volatile Uint32 MMCRSP01;
    volatile Uint32 MMCRSP23;
    volatile Uint32 MMCRSP45;
    volatile Uint32 MMCRSP67;
    volatile Uint16 MMCDRSP;
    volatile Uint8 RSVD10[2];
    volatile Uint16 MMCETOK;
    volatile Uint8 RSVD11[2];
    volatile Uint16 MMCCIDX;
    volatile Uint8 RSVD12[2];
    volatile Uint16 MMCCKC;
    volatile Uint8 RSVD13[2];
    volatile Uint16 MMCTORC;
    volatile Uint8 RSVD14[2];
    volatile Uint16 MMCTODC;
    volatile Uint8 RSVD15[2];
    volatile Uint16 MMCBLNC;
    volatile Uint8 RSVD16[2];
    volatile Uint16 SDIOCTL;
    volatile Uint8 RSVD17[2];
    volatile Uint16 SDIOST0;
    volatile Uint8 RSVD18[2];
    volatile Uint16 SDIOIEN;
    volatile Uint8 RSVD19[2];
    volatile Uint16 SDIOIST;
    volatile Uint8 RSVD20[2];
    volatile Uint16 MMCFIFOCTL;
} 
DEVICE_SDMMCRegs;

#define SDMMC ((DEVICE_SDMMCRegs*) 0x1D11000)
//0x01C40000
#define SDMMC_PERIPHERAL_CNT      (1)

#define DEVICE_SDMMC_MMCST0_DXRDY_MASK      (0x0200u)
#define DEVICE_SDMMC_MMCST0_DXRDY_SHIFT     (0x0009u)
#define DEVICE_SDMMC_MMCST0_DXRDY_RESETVAL  (0x0001u)

#define DEVICE_SDMMC_MMCFIFOCTL_FIFODIR_MASK (0x0002u)
#define DEVICE_SDMMC_MMCFIFOCTL_FIFODIR_SHIFT (0x0001u)
#define DEVICE_SDMMC_MMCFIFOCTL_FIFODIR_RESETVAL (0x0000u)

/*----FIFODIR Tokens----*/
#define DEVICE_SDMMC_MMCFIFOCTL_FIFODIR_READ (0x0000u)
#define DEVICE_SDMMC_MMCFIFOCTL_FIFODIR_WRITE (0x0001u)

#define DEVICE_SDMMC_MMCFIFOCTL_FIFORST_MASK (0x0001u)
#define DEVICE_SDMMC_MMCFIFOCTL_FIFORST_SHIFT (0x0000u)
#define DEVICE_SDMMC_MMCFIFOCTL_FIFORST_RESETVAL (0x0000u)


/***********************************************************
* Global Function Declarations                             *
***********************************************************/

// Execute LPSC state transition
void    DEVICE_LPSCTransition(Uint8 module, Uint8 domain, Uint8 state);
void    DEVICE_PSCInit();

// Pinmux control function
void    DEVICE_pinmuxControl(Uint32 regOffset, Uint32 mask, Uint32 value);

// Initialization prototypes
Uint32  DEVICE_init(void);
Uint32  DEVICE_UART0Init(void);
Uint32  DEVICE_TIMER0Init(void);
Uint32  DEVICE_EMIFInit(void);
Uint32  DEVICE_I2C0Init(void);
Uint32  DEVICE_PLL2Init();
Uint32  DEVICE_DDR2Init();
Uint32  DEVICE_PLL1Init();//Uses and Oscillator of 24 MHz

Uint32  DEVICE_I2C0Reset();
void VPSS_SYNC_RESET();
void POR_RESET();
void WDT_RESET();
void WDT_FLAG_ON();

// Device boot status functions
DEVICE_BootMode   DEVICE_bootMode( void );
DEVICE_BusWidth   DEVICE_emifBusWidth( void );

void    DEVICE_TIMER0Start(void);
void    DEVICE_TIMER0Stop(void);
Uint32  DEVICE_TIMER0Status(void);


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif // End _DEVICE_H_


