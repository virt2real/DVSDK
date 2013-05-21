/* --------------------------------------------------------------------------
  FILE        : device.h                                                   
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : Provides device differentiation for the project files. This
                file MUST be modified to match the device specifics.
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
  DEVICE_BOOTMODE_NOR     = 0x1,     // NOR boot mode (execute in place)
  DEVICE_BOOTMODE_HPI     = 0x2,     // HPI
  DEVICE_BOOTMODE_UART    = 0x3     // UART
}
DEVICE_BootMode;

// Supported buswidth
typedef enum _DEVICE_BusWidth_
{
  DEVICE_BUSWIDTH_8BIT  = BUS_8BIT,
  DEVICE_BUSWIDTH_16BIT = BUS_16BIT
}
DEVICE_BusWidth;

// System Control Module register structure
typedef struct _DEVICE_SYS_MODULE_REGS_
{
  VUint32 PINMUX[2];         //0x00
  VUint32 DSPBOOTADDR;       //0x08
  VUint32 SUSPSRC;           //0x0C
  VUint32 INTGEN;            //0x10
  VUint32 BOOTCFG;           //0x14
  VUint8 RSVD0[16];          //0x18
  VUint32 DEVICE_ID;         //0x28
  VUint8 RSVD1[8];           //0x2C
  VUint32 USBPHY_CTL;        //0x34
  VUint32 CHP_SHRTSW;        //0x38
  VUint32 MSTPRI[2];         //0x3C
  VUint32 VPSS_CLKCTL;       //0x44
  VUint32 VDD3P3V_PWDN;      //0x48
  VUint32 DDRVTPER;          //0x4C
  VUint8 RSVD2[32];          //0x50 
}
DEVICE_SysModuleRegs;

#define SYSTEM ((DEVICE_SysModuleRegs*) 0x01C40000)

#define DEVICE_BOOTCFG_EMIFWIDTH_SHIFT  (5)
#define DEVICE_BOOTCFG_EMIFWIDTH_MASK  (0x00000020)

#define DEVICE_BOOTCFG_BOOTMODE_SHIFT   (6)
#define DEVICE_BOOTCFG_BOOTMODE_MASK    (0x000000C0)

#define DEVICE_PINMUX_UART0_MASK        (0x00000001)
#define DEVICE_PINMUX_EMIF_MASK         (0x00020000)

#define DEVICE_PINMUX_UART0_EN          (0x00000001)
#define DEVICE_PINMUX_EMIF_EN           (0x00000000)
#define DEVICE_PINMUX_ATA_EN            (0x00020000)


// ARM Interrupt Controller register structure - See sprue26.pdf
typedef struct _DEVICE_AINTC_REGS_
{
    VUint32 FIQ0;
    VUint32 FIQ1;
    VUint32 IRQ0;
    VUint32 IRQ1;
    VUint32 FIQENTRY;
    VUint32 IRQENTRY;
    VUint32 EINT0;
    VUint32 EINT1;
    VUint32 INTCTL;
    VUint32 EABASE;
    VUint8 RSVD0[8];
    VUint32 INTPRI0;
    VUint32 INTPRI1;
    VUint32 INTPRI2;
    VUint32 INTPRI3;
    VUint32 INTPRI4;
    VUint32 INTPRI5;
    VUint32 INTPRI6;
    VUint32 INTPRI7;
}
DEVICE_AIntcRegs;

#define AINTC ((DEVICE_AIntcRegs*) 0x01C48000)


// PLL Register structure - See sprue14.pdf, Chapter 6 for more details.
typedef struct _DEVICE_PLL_REGS_
{
  VUint32 PID;
  VUint8 RSVD0[224];
  VUint32 RSTYPE;
  VUint8 RSVD1[24];  
  VUint32 PLLCTL;
  VUint8 RSVD2[12];  
  VUint32 PLLM;
  VUint8 RSVD3[4];
  VUint32 PLLDIV1;
  VUint32 PLLDIV2;
  VUint32 PLLDIV3;  
  VUint8 RSVD4[4]; 
  VUint32 POSTDIV;
  VUint32 BPDIV;
  VUint8 RSVD5[8];  
  VUint32 PLLCMD;
  VUint32 PLLSTAT;
  VUint32 ALNCTL;
  VUint32 DCHANGE;
  VUint32 CKEN;
  VUint32 CKSTAT;
  VUint32 SYSTAT;
  VUint8 RSVD6[12];
  VUint32 PLLDIV4;
  VUint32 PLLDIV5;
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
#define DEVICE_PLLSTAT_LOCK_MASK    (0x00000002)

#define DEVICE_PLLDIV_EN_MASK       (0x00008000)

#define DEVICE_PLL1_MULTIPLIER  (22u)

#define DEVICE_OSC_FREQ         (27000000u)
#define DEVICE_SYSTEM_FREQ (DEVICE_PLL1_MULTIPLIER * DEVICE_OSC_FREQ)

// Power/Sleep Ctrl Register structure - See sprue14.pdf, Chapter 7
typedef struct _DEVICE_PSC_REGS_
{
  VUint32 PID;        // 0x000
  VUint8 RSVD0[12];   // 0x004
  VUint32 GBLCTL;     // 0x010
  VUint8 RSVD1[4];    // 0x014
  VUint32 INTEVAL;    // 0x018
  VUint8 RSVD2[36];  // 0x01C
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
  VUint8 RSVD8[132];  // 0x07C
  VUint32 RAILSTAT;   // 0x100
  VUint32 RAILCTL;    // 0x104
  VUint32 RAILSEL;    // 0x108
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
  VUint32 MDSTAT[41]; // 0x800
  VUint8 RSVD15[348]; // 0x8A4
  VUint32 MDCTL[41];  // 0xA00
}
DEVICE_PSCRegs;

#define PSC ((DEVICE_PSCRegs*) 0x01C41000)

// PSC constants
#define LPSC_VPSS_MAST      (0)
#define LPSC_VPSS_SLV       (1)
#define LPSC_TPCC           (2)
#define LPSC_TPTC0          (3)
#define LPSC_TPTC1          (4)
#define LPSC_EMAC0          (5)
#define LPSC_EMAC1          (6)
#define LPSC_MDIO           (7)
#define LPSC_1394           (8)
#define LPSC_USB            (9)
#define LPSC_ATA            (10)
#define LPSC_VLYNQ          (11)
#define LPSC_HPI            (12)
#define LPSC_DDR2           (13)
#define LPSC_AEMIF          (14)
#define LPSC_MMCSD          (15)
#define LPSC_MEMSTK         (16)
#define LPSC_ASP            (17)
#define LPSC_I2C            (18)
#define LPSC_UART0          (19)
#define LPSC_GPIO           (26)
#define LPSC_TIMER0         (27)
#define LPSC_ARM            (31)
#define LPSC_DSP            (39)
#define LPSC_IMCOP          (40)

#define EMURSTIE_MASK       (0x00000200)

#define PD0                 (0)
#define PD1                 (1)

#define PSC_ENABLE          (0x3)
#define PSC_DISABLE         (0x2)
#define PSC_SYNCRESET       (0x1)
#define PSC_SWRSTDISABLE    (0x0)

 
// DDR2 Memory Ctrl Register structure - See sprue22b.pdf for more details.
typedef struct _DEVICE_DDR2_REGS_
{
  VUint8 RSVD0[4];        //0x00
  VUint32 SDRSTAT;        //0x04
  VUint32 SDBCR;          //0x08
  VUint32 SDRCR;          //0x0C
  VUint32 SDTIMR;         //0x10
  VUint32 SDTIMR2;        //0x14
  VUint8 RSVD1[8];        //0x18 
  VUint32 PBBPR;          //0x20
  VUint8 RSVD2[156];      //0x24 
  VUint32 IRR;            //0xC0
  VUint32 IMR;            //0xC4
  VUint32 IMSR;           //0xC8
  VUint32 IMCR;           //0xCC
  VUint8 RSVD3[20];       //0xD0
  VUint32 DDRPHYCR;       //0xE4
  VUint8 RSVD4[8];        //0xE8
  VUint32 VTPIOCR;        //0xF0
}
DEVICE_DDR2Regs;

#define DDR                       ((DEVICE_DDR2Regs*) 0x20000000)
#define DDRVTPR                   (*((VUint32*) 0x01C42030))

#define DEVICE_DDR2_TEST_PATTERN  (0xA55AA55Au)
#define DEVICE_DDR2_RAM_SIZE      (0x10000000u)

#define DEVICE_MAX_IMAGE_SIZE     (0x02000000u)
#define DEVICE_DDR2_START_ADDR    (0x80000000u)
#define DEVICE_DDR2_END_ADDR      ((DEVICE_DDR2_START_ADDR + DEVICE_DDR2_RAM_SIZE))


// AEMIF Register structure - See sprue20a.pdf for more details.
typedef struct _DEVICE_EMIF_REGS_
{
    VUint32 ERCSR;      // 0x00
    VUint32 AWCCR;      // 0x04
    VUint32 SDBCR;      // 0x08
    VUint32 SDRCR;      // 0x0C
    VUint32 AB1CR;      // 0x10
    VUint32 AB2CR;      // 0x14
    VUint32 AB3CR;
    VUint32 AB4CR;
    VUint32 SDTIMR;     // 0x20
    VUint32 DDRSR;
    VUint32 DDRPHYCR;
    VUint32 DDRPHYSR;
    VUint32 TOTAR;      // 0x30
    VUint32 TOTACTR;
    VUint32 DDRPHYID_REV;
    VUint32 SDSRETR;
    VUint32 EIRR;       // 0x40
    VUint32 EIMR;
    VUint32 EIMSR;
    VUint32 EIMCR;
    VUint32 IOCTRLR;    // 0x50
    VUint32 IOSTATR;
    VUint8 RSVD0[8];
    VUint32 NANDFCR;    // 0x60
    VUint32 NANDFSR;
    VUint8 RSVD1[8];
    VUint32 NANDF1ECC;  // 0x70
    VUint32 NANDF2ECC;
    VUint32 NANDF3ECC;
    VUint32 NANDF4ECC;
    VUint8 RSVD2[4];    // 0x80
    VUint32 IODFTECR;
    VUint32 IODFTGCR;
    VUint8 RSVD3[4];
    VUint32 IODFTMRLR;  // 0x90
    VUint32 IODFTMRMR;
    VUint32 IODFTMRMSBR;
    VUint8 RSVD4[20];
    VUint32 MODRNR;     // 0xB0
}
DEVICE_EmifRegs;

#define AEMIF ((DEVICE_EmifRegs*) 0x01E00000)

#define DEVICE_EMIF_NUMBER_CE_REGION        (4)
#define DEVICE_EMIF_FIRST_CE_START_ADDR     (0x02000000)
#define DEVICE_EMIF_INTER_CE_REGION_SIZE    (0x02000000)

#define DEVICE_EMIF_AWCC_WAITSTATE_MASK     (0x000007FF)


// UART Register structure - See sprue33.pdf for more details.
typedef struct _DEVICE_UART_REGS_
{
  VUint32 RBR;
  VUint32 IER;
  VUint32 IIR;
  VUint32 LCR;
  VUint32 MCR;
  VUint32 LSR;
  VUint32 MSR;
  VUint32 SCR;
  VUint8 DLL;
  VUint8 RSVDO[3];
  VUint8 DLH;
  VUint8 RSVD1[3];  
  VUint32 PID1;
  VUint32 PID2;
  VUint32 PWREMU_MGNT;
}
DEVICE_UartRegs;

#define THR RBR
#define FCR IIR

#define UART0 ((DEVICE_UartRegs*) 0x01C20000)

#define DEVICE_UART0_DESIRED_BAUD   (115200)
#define DEVICE_UART0_OVERSAMPLE_CNT (16)

// Timer Register structure - See sprue26.pdf for more details.
typedef struct _DEVICE_TIMER_REGS_
{
    VUint32 PID12;          // 0x00
    VUint32 EMUMGT_CLKSPD;  // 0x04
    VUint32 GPINT_GPEN;     // 0x08
    VUint32 GPTDAT_GPDIR;   // 0x0C
    VUint32 TIM12;          // 0x10
    VUint32 TIM34;          // 0x14
    VUint32 PRD12;          // 0x18
    VUint32 PRD34;          // 0x1C
    VUint32 TCR;            // 0x20
    VUint32 TGCR;           // 0x24
    VUint32 WDTCR;          // 0x28
}
DEVICE_TimerRegs;

#define TIMER0 ((DEVICE_TimerRegs*) 0x01C21400)

// I2C Register structure - See sprue27b.pdf for more details.
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

#define I2C0 ((DEVICE_I2CRegs*) 0x02047C00)

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


/***********************************************************
* Global Function Declarations                             *
***********************************************************/

// Execute LPSC state transition
extern void DEVICE_LPSCTransition(Uint8 module, Uint8 domain, Uint8 state);
extern void DEVICE_PSCInit();

// Pinmux control function
extern void DEVICE_pinmuxControl(Uint32 regOffset, Uint32 mask, Uint32 value);

// Initialization prototypes
extern Uint32 DEVICE_init(void);
extern Uint32 DEVICE_UART0Init(void);
extern Uint32 DEVICE_TIMER0Init(void);
extern Uint32 DEVICE_EMIFInit(void);
extern Uint32 DEVICE_I2C0Init(void);
extern Uint32 DEVICE_PLL2Init(void);
extern Uint32 DEVICE_PLL1Init(Uint32 PllMult);
extern Uint32 DEVICE_DDR2Init(void);
extern Uint32 DEVICE_I2C0Reset();

// Device boot status functions
extern DEVICE_BootMode DEVICE_bootMode( void );
extern DEVICE_BusWidth DEVICE_emifBusWidth( void );

extern void   DEVICE_TIMER0Start(void);
extern void   DEVICE_TIMER0Stop(void);
extern Uint32 DEVICE_TIMER0Status(void);


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif // End _DEVICE_H_

/* --------------------------------------------------------------------------
    HISTORY
       v1.00  -  DJA  -  07-Nov-2007
         Initial Release
 ----------------------------------------------------------------------------- */
