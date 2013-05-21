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


/******************************************************
* Global Typedef declarations                         *
******************************************************/

// Supported bootmodes
typedef enum _DEVICE_BootMode_
{
	DEVICE_BOOTMODE_NONE = 0,
	DEVICE_BOOTMODE_ARM,
	DEVICE_BOOTMODE_NOR_EMIFA,
	DEVICE_BOOTMODE_NAND_EMIFA_8BIT,
	DEVICE_BOOTMODE_NAND_EMIFA_16BIT,
	DEVICE_BOOTMODE_UHPI,										// 16 bit
	DEVICE_BOOTMODE_SPI0_FLASH,									// 24 bit address
	DEVICE_BOOTMODE_SPI0_EEPROM,								// 16 bit address
	DEVICE_BOOTMODE_SPI0_SLAVE,									// 16 bit data
	DEVICE_BOOTMODE_SPI1_FLASH,									// 24 bit address
	DEVICE_BOOTMODE_SPI1_EEPROM,								// 16 bit address
	DEVICE_BOOTMODE_SPI1_SLAVE,									// 16 bit data
	DEVICE_BOOTMODE_I2C0_MASTER,								// 16 bit address
	DEVICE_BOOTMODE_I2C0_SLAVE,									// 16 bit data
	DEVICE_BOOTMODE_I2C1_MASTER,								// 16 bit address
	DEVICE_BOOTMODE_I2C1_SLAVE,									// 16 bit data
	DEVICE_BOOTMODE_UART0,
	DEVICE_BOOTMODE_UART1,
	DEVICE_BOOTMODE_UART2,
	DEVICE_BOOTMODE_MMC,										// Not supported
	DEVICE_BOOTMODE_RMII,										// Not supported
	DEVICE_BOOTMODE_USB0,										// Not supported
	DEVICE_BOOTMODE_THB = 0xAA
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
  VUint32 REVID;              //0x00
  VUint32 DIEIDR[4];          //0x04
  VUint8  RSVD0[12];          //0x14
  VUint32 BOOTCFG;            //0x20
  VUint8  RSVD1[20];          //0x24
  VUint32 KICKR[2];           //0x38
  VUint32 HOSTCFG[2];         //0x40
  VUint8  RSVD2[152];         //0x48
  VUint32 IRAWSTRAT;          //0xE0
  VUint32 IENSTAT;            //0xE4
  VUint32 IENSET;             //0xE8
  VUint32 IENCLR;             //0xEC
  VUint32 EOI;                //0xF0
  VUint32 FLTADDRR;           //0xF4  
  VUint32 FLTSTAT;            //0xF8
  VUint8  RSVD3[20];          //0xFC
  VUint32 MSTPRI[3];          //0x110
  VUint8  RSVD4[4];           //0x11C
  VUint32 PINMUX[20];         //0x120
  VUint32 SUSPSRC;            //0x170
  VUint32 CHIPSIG;            //0x174
  VUint32 CHIPSIG_CLR;        //0x178
  VUint32 CFGSHIP[5];         //0x17C
}
DEVICE_SysModuleRegs;

#define SYSTEM ((DEVICE_SysModuleRegs*) 0x01C14000)

#define DEVICE_BOOTCFG_BOOTMODE_MASK    (0x000000C0)
#define DEVICE_BOOTCFG_BOOTMODE_SHIFT   (6)


// PLL Register structure - See sprufb3.pdf, Chapter 6 for more details.
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

#define PLL1 ((DEVICE_PLLRegs*) 0x01C11000)

#define DEVICE_PLLCTL_PLLEN_MASK    (0x00000001)
#define DEVICE_PLLCTL_PLLPWRDN_MASK (0x00000002)
#define DEVICE_PLLCTL_PLLRST_MASK   (0x00000008)
#define DEVICE_PLLCTL_PLLDIS_MASK   (0x00000010)
#define DEVICE_PLLCTL_PLLENSRC_MASK (0x00000020)
#define DEVICE_PLLCTL_CLKMODE_MASK  (0x00000100)

#define DEVICE_PLLCMD_GOSET_MASK    (0x00000001)
#define DEVICE_PLLSTAT_GOSTAT_MASK  (0x00000001)
#define DEVICE_PLLDIV_EN_MASK       (0x00008000)

#ifdef DM355_270
    #define DEVICE_PLL1_MULTIPLIER  (180u)
#else
    #define DEVICE_PLL1_MULTIPLIER  (144u)
#endif
#define DEVICE_PLL2_MULTIPLIER      (114u)

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
  VUint32 MDSTAT[41]; // 0x800
  VUint8 RSVD15[348]; // 0x8A4
  VUint32 MDCTL[41];  // 0xA00
}
DEVICE_PSCRegs;

#define PSC0 ((DEVICE_PSCRegs*) 0x01C10000)
#define PSC1 ((DEVICE_PSCRegs*) 0x01E27000)

#define EMURSTIE_MASK       (0x00000200)

#define PSC_ENABLE          (0x3)
#define PSC_DISABLE         (0x2)
#define PSC_SYNCRESET       (0x1)
#define PSC_SWRSTDISABLE    (0x0)

#define PSCNUM0             (0x0)
#define PSCNUM1             (0x1)

#define PD0                 (0x0)
#define PD1                 (0x1)

#define LPSC_EMIFA          (3)
#define LPSC_SPI0           (4)
#define LPSC_ARMRAM         (7)
#define LPSC_SCnKM          (8)
#define LPSC_UART0          (9)
#define LPSC_DMAX           (13)
#define LPSC_ARM            (14)

#define LPSC_GPIO           (3)
#define LPSC_UHPI0          (4)
#define LPSC_EMIFB          (6)
#define LPSC_SPI1           (10)
#define LPSC_I2C1           (11)
#define LPSC_UART1          (12)
#define LPSC_UART2          (13)
#define LPSC_L3CBA          (31)

// AEMIF Register structure - From EMIF 2.5 Spec
typedef struct _DEVICE_EMIF_REGS_
{
  VUint32 ERCSR;              // 0x00
  VUint32 AWCCR;              // 0x04
  VUint32 SDBCR;              // 0x08
  VUint32 SDRCR;              // 0x0C

  VUint32 A1CR;               // 0x10
  VUint32 A2CR;               // 0x14
  VUint32 A3CR;               // 0x18
  VUint32 A4CR;               // 0x1C

  VUint32 SDTIMR;             // 0x20
  VUint32 SDRSTAT;            // 0x24
  VUint32 DDRPHYCR;           // 0x28
  VUint32 DDRPHYSR;           // 0x2C

  VUint32 SDRACCR;            // 0x30
  VUint32 SDRACT;             // 0x34
  VUint32 DDRPHYREV;          // 0x38
  VUint32 SDRSRPDEXIT;        // 0x3C

  VUint32 EIRR;               // 0x40
  VUint32 EIMR;               // 0x44
  VUint32 EIMSR;              // 0x48
  VUint32 EIMCR;              // 0x4C

  VUint32 IOCR;               // 0x50
  VUint32 IOSR;               // 0x54
  VUint8 RSVD0[4];            // 0x58
  VUint32 ONENANDCTL;         // 0x5C  

  VUint32 NANDFCR;            // 0x60
  VUint32 NANDFSR;            // 0x64
  VUint32 PMCR;               // 0x68
  VUint8 RSVD1[4];            // 0x6C

  VUint32 NANDF1ECC;          // 0x70
  VUint32 NANDF2ECC;          // 0x74
  VUint32 NANDF3ECC;          // 0x78
  VUint32 NANDF4ECC;          // 0x7C

  VUint8 RSVD2[4];            // 0x80
  VUint32 IODFTEXECNT;        // 0x84
  VUint32 IODFTGBLCTRL;       // 0x88
  VUint8 RSVD3[4];            // 0x8C

  VUint32 IODFTMISRLSB;       // 0x90
  VUint32 IODFTMISRMID;       // 0x94
  VUint32 IODFTMISRMSB;       // 0x98
  VUint8 RSVD4[20];           // 0x9C

  VUint32 MODRELNUM;          // 0xB0
  VUint8 RSVD5[8];            // 0xB4
  VUint32 NAND4BITECCLOAD;    // 0xBC

  VUint32 NAND4BITECC1;       // 0xC0
  VUint32 NAND4BITECC2;       // 0xC4
  VUint32 NAND4BITECC3;       // 0xC8
  VUint32 NAND4BITECC4;       // 0xCC

  VUint32 NANDERRADD1;        // 0xD0
  VUint32 NANDERRADD2;        // 0xD4
  VUint32 NANDERRVAL1;        // 0xD8
  VUint32 NANDERRVAL2;        // 0xDC
}
DEVICE_EmifRegs;

#define AEMIF ((DEVICE_EmifRegs*) 0x68000000u)

#define DEVICE_EMIF_NUMBER_CE_REGION        (4)
#define DEVICE_EMIF_FIRST_CE_START_ADDR     (0x60000000)
#define DEVICE_EMIF_INTER_CE_REGION_SIZE    (0x02000000)

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
  VUint32 RBR;
  VUint32 IER;
  VUint32 IIR;
  VUint32 LCR;
  VUint32 MCR;
  VUint32 LSR;
  VUint8  RSVD0[8];         
  VUint8  DLL;
  VUint8  RSVD1[3];
  VUint8  DLH;
  VUint8  RSVD2[3];  
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
    VUint8  RSVD1[12];      // 0x2C
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
void    DEVICE_LPSCTransition(Uint8 pscnum, Uint8 module, Uint8 domain, Uint8 state);
void    DEVICE_PSCInit();

// Pinmux control function
void    DEVICE_pinmuxControl(Uint32 regOffset, Uint32 mask, Uint32 value);

// Initialization prototypes
Uint32  DEVICE_init(void);
Uint32  DEVICE_UART0Init(void);
Uint32  DEVICE_TIMER0Init(void);
Uint32  DEVICE_EMIFInit(void);
Uint32  DEVICE_I2C0Init(void);
Uint32  DEVICE_PLL2Init(void);
Uint32  DEVICE_PLL1Init(Uint32 PllMult);
Uint32  DEVICE_DDR2Init(void);
Uint32  DEVICE_I2C0Reset();

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


