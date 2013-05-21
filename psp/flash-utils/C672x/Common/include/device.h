/* --------------------------------------------------------------------------
  FILE        : device.h                                                   
  PROJECT     : Catalog Flashing Utilities
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

#define DEVICE_MAX_FXN_ARG_CNT  (16)
#define DEVICE_FXN_CNT          (5)      


/******************************************************
* Global Typedef declarations                         *
******************************************************/

// Device function pointer type
typedef Uint32 (*DEVICE_FxnPtr)(void);


// Supported buswidth
typedef enum _DEVICE_BUS_WIDTH_
{
  DEVICE_BUSWIDTH_8BIT  = BUS_8BIT,
  DEVICE_BUSWIDTH_16BIT = BUS_16BIT
}
DEVICE_BusWidth;

typedef enum _DEVICE_BOOT_MODE_
{
  DEVICE_BOOTMODE_NAND8         = 0x00,
  DEVICE_BOOTMODE_SPIMASTER16   = 0x01,
  DEVICE_BOOTMODE_PARALLELFLASH = 0x02,
  DEVICE_BOOTMODE_SPISLAVE16    = 0x03,
  DEVICE_BOOTMODE_SPIMASTER24   = 0x04,
  DEVICE_BOOTMODE_I2CMASTER16   = 0x05,
  DEVICE_BOOTMODE_SPISLAVE_PF   = 0x06,
  DEVICE_BOOTMODE_I2CSLAVE8     = 0x07,  
  DEVICE_BOOTMODE_HPI           = 0x08
}
DEVICE_BootMode;

// System Control Module register structure
typedef struct _DEVICE_SYS_MODULE_REGS_
{
  VUint32 CFGPIN[2];          // 0x00
  VUint32 CFGHPI;             // 0x08
  VUint32 CFGHPIAMSB;         // 0x0C
  VUint32 CFGHPIAUMB;         // 0x10  
  VUint32 CFGRTI;             // 0x14
  VUint32 CFGMCASP[3];        // 0x18  
  VUint32 CFGBRIDGE;          // 0x24
}
DEVICE_SysModuleRegs;

#define SYSTEM ((DEVICE_SysModuleRegs*) 0x40000000)

#define DEVICE_BOOTCFG_CFGPIN0_MODE_MASK  (0x000000E0u)
#define DEVICE_BOOTCFG_CFGPIN0_MODE_SHIFT (0x05u)
#define DEVICE_BOOTCFG_CFGPIN1_HPI_MASK   (0x00000020u)
#define DEVICE_BOOTCFG_CFGPIN1_HPI_SHIFT  (0x05u)

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


// PLL Register structure
typedef struct _DEVICE_PLL_REGS_
{
  VUint32 PID;        // 0x000
  VUint8 RSVD0[224];  // 0x004
  VUint32 RSTYPE;     // 0x0E4
  VUint8 RSVD1[24];   // 0x0E8
  VUint32 PLLCTL;     // 0x100
  VUint8 RSVD2[12];   // 0x104
  VUint32 PLLM;       // 0x110
  VUint32 PLLDIV0;    // 0x114
  VUint32 PLLDIV1;    // 0x118
  VUint32 PLLDIV2;    // 0x11C
  VUint32 PLLDIV3;    // 0x120
  VUint8 RSVD4[4];    // 0x124
  VUint32 POSTDIV;    // 0x128
  VUint32 BPDIV;      // 0x12C
  VUint8 RSVD5[8];    // 0x130
  VUint32 PLLCMD;     // 0x138
  VUint32 PLLSTAT;    // 0x13C
  VUint32 ALNCTL;     // 0x140
  VUint32 DCHANGE;    // 0x144
  VUint32 CKEN;       // 0x148
  VUint32 CKSTAT;     // 0x14C
  VUint32 SYSTAT;     // 0x150
}
DEVICE_PLLRegs;

#define PLL1 ((DEVICE_PLLRegs*) 0x41000000)

#define DEVICE_PLLCTL_PLLEN_MASK    (0x00000001)
#define DEVICE_PLLCTL_PLLPWRDN_MASK (0x00000002)
#define DEVICE_PLLCTL_PLLRST_MASK   (0x00000008)
#define DEVICE_PLLCTL_PLLDIS_MASK   (0x00000010)
#define DEVICE_PLLCTL_PLLENSRC_MASK (0x00000020)
#define DEVICE_PLLCTL_CLKMODE_MASK  (0x00000100)

#define DEVICE_PLLCMD_GOSET_MASK    (0x00000001)
#define DEVICE_PLLSTAT_GOSTAT_MASK  (0x00000001)
#define DEVICE_PLLDIV_EN_MASK       (0x00008000)

#define DEVICE_ALNCTL_ALN1          (0x00000001)
#define DEVICE_ALNCTL_ALN2          (0x00000002)
#define DEVICE_ALNCTL_ALN3          (0x00000004)


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



#define AEMIF ((DEVICE_EmifRegs*) 0xF0000000u)

#define DEVICE_EMIF_NUMBER_CE_REGION        (1)
#define DEVICE_EMIF_FIRST_CE_START_ADDR     (0x90000000)
#define DEVICE_EMIF_INTER_CE_REGION_SIZE    (0x20000000)

#define DEVICE_EMIF_AWCC_WAITSTATE_MASK                 (0x000000FF)
#define DEVICE_DDR2_RAM_SIZE                (0x00010000u)
#define DEVICE_DDR2_START_ADDR              (0x10030000u)


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

#define I2C0 ((DEVICE_I2CRegs*) 0x49000000u)
#define I2C1 ((DEVICE_I2CRegs*) 0x4A000000u)

#define DEVICE_I2C_TARGET_FREQ      (200000u)

#define I2C_PERIPHERAL_CNT      (2)
#define I2C_MEMORYMAP_SPACING   (0x01000000u)

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

typedef struct _DEVICE_SPI_REGS_
{
  VUint32 SPIGCR0;          // 0x00
  VUint32 SPIGCR1;          // 0x04
  VUint32 SPIINT;           // 0x08
  VUint32 SPILVL;           // 0x0C
  VUint32 SPIFLG;           // 0x10
  VUint32 SPIPC0;           // 0x14
  VUint32 SPIPC1;           // 0x18
  VUint32 SPIPC2;           // 0x1C
  VUint32 SPIPC3;           // 0x20
  VUint32 SPIPC4;           // 0x24
  VUint32 SPIPC5;           // 0x28
  VUint32 SPIPC6;           // 0x2C
  VUint32 SPIPC7;           // 0x30
  VUint32 SPIPC8;           // 0x34
  VUint32 SPIDAT0;          // 0x38
  VUint32 SPIDAT1;          // 0x3C
  VUint32 SPIBUF;           // 0x40
  VUint32 SPIEMU;           // 0x44
  VUint32 SPIDELAY;         // 0x48
  VUint32 SPIDEF;           // 0x4C
  VUint32 SPIFMT[4];        // 0x50
  VUint32 TGINTVEC[2];      // 0x60
  VUint32 RSVD0[2];         // 0x68
  VUint32 MIBSPIE;          // 0x70
}
DEVICE_SPIRegs;

#define SPI0 ((DEVICE_SPIRegs *) 0x47000000u)
#define SPI1 ((DEVICE_SPIRegs *) 0x48000000u)

#define SPI_PERIPHERAL_CNT      (2)
#define SPI_MEMORYMAP_SPACING   (0x01000000u)


typedef struct _DEVICE_MCASP_REGS_
{
  VUint32 PID;                // 0x00
  VUint32 PWRDEMU;            // 0x04
  VUint32 RSVD0[2];           // 0x08
  VUint32 PFUNC;              // 0x10
  VUint32 PDIR;               // 0x14
  VUint32 PDOUT;              // 0x18
  VUint32 PDIN_PDSET;         // 0x1C
  VUint32 PDCLR;              // 0x20
  VUint32 RSVD1[8];           // 0x24
  VUint32 GBLCTL;             // 0x44
  VUint32 AMUTE;              // 0x48
  VUint32 DLBCTL;             // 0x4C
  VUint32 DITCTL;             // 0x50
  VUint32 RSVD2[3];           // 0x54
  VUint32 RGBLCTL;            // 0x60
  VUint32 RMASK;              // 0x64
  VUint32 RFMT;               // 0x68
  VUint32 AFSRCTL;            // 0x6C
  VUint32 ACLKRCTL;           // 0x70
  VUint32 AHCLKRCTL;          // 0x74
  VUint32 RTDM;               // 0x78
  VUint32 RINTCTL;            // 0x7C
  VUint32 RSTAT;              // 0x80
  VUint32 RSLOT;              // 0x84
  VUint32 RCLKCHK;            // 0x88
  VUint32 REVTCTL;            // 0x8C
  VUint32 RSVD3[4];           // 0x90
  VUint32 XGBLCTL;            // 0xA0
  VUint32 XMASK;              // 0xA4
  VUint32 XFMT;               // 0xA8
  VUint32 AFSXCTL;            // 0xAC
  VUint32 ACLKXCTL;           // 0xB0
  VUint32 AHCLKXCTL;          // 0xB4
  VUint32 XTDM;               // 0xB8
  VUint32 XINTCTL;            // 0xBC
  VUint32 XSTAT;              // 0xC0
  VUint32 XSLOT;              // 0xC4
  VUint32 XCLKCHK;            // 0xC8
  VUint32 XEVTCTL;            // 0xCC
  VUint32 RSVD4[12];          // 0xD0
  VUint32 DITCSRA0;           // 0x100
  VUint32 DITCSRA1;
  VUint32 DITCSRA2;
  VUint32 DITCSRA3;
  VUint32 DITCSRA4;
  VUint32 DITCSRA5;
  VUint32 DITCSRB0;
  VUint32 DITCSRB1;
  VUint32 DITCSRB2;
  VUint32 DITCSRB3;
  VUint32 DITCSRB4;
  VUint32 DITCSRB5;
  VUint32 DITUDRA0;
  VUint32 DITUDRA1;
  VUint32 DITUDRA2;
  VUint32 DITUDRA3;
  VUint32 DITUDRA4;
  VUint32 DITUDRA5;
  VUint32 DITUDRB0;
  VUint32 DITUDRB1;
  VUint32 DITUDRB2;
  VUint32 DITUDRB3;
  VUint32 DITUDRB4;
  VUint32 DITUDRB5; 
  VUint32 RSVD5[8];           // 0x160
  VUint32 SRCTL0;             // 0x180
  VUint32 SRCTL1;
  VUint32 SRCTL2;
  VUint32 SRCTL3;
  VUint32 SRCTL4;
  VUint32 SRCTL5;
  VUint32 SRCTL6;
  VUint32 SRCTL7;
  VUint32 SRCTL8;
  VUint32 SRCTL9;
  VUint32 SRCTL10;
  VUint32 SRCTL11;
  VUint32 SRCTL12;
  VUint32 SRCTL13;
  VUint32 SRCTL14;
  VUint32 SRCTL15;
  VUint32 RSVD6[16];          // 0x1C0
  VUint32 XBUF0;              // 0x200
  VUint32 XBUF1;
  VUint32 XBUF2;
  VUint32 XBUF3;
  VUint32 XBUF4;
  VUint32 XBUF5;
  VUint32 XBUF6;
  VUint32 XBUF7;
  VUint32 XBUF8;
  VUint32 XBUF9;
  VUint32 XBUF10;
  VUint32 XBUF11;
  VUint32 XBUF12;
  VUint32 XBUF13;
  VUint32 XBUF14;
  VUint32 XBUF15;
  VUint32 RSVD7[16];          // 0x240
  VUint32 RBUF0;              // 0x280
  VUint32 RBUF1;
  VUint32 RBUF2;
  VUint32 RBUF3;
  VUint32 RBUF4;
  VUint32 RBUF5;
  VUint32 RBUF6;
  VUint32 RBUF7;
  VUint32 RBUF8;
  VUint32 RBUF9;
  VUint32 RBUF10;
  VUint32 RBUF11;
  VUint32 RBUF12;
  VUint32 RBUF13;
  VUint32 RBUF14;
  VUint32 RBUF15;             // 0x2BC
} DEVICE_MCASPRegs;

#define MCASP0 ((DEVICE_MCASPRegs *) 0x54000000)
#define MCASP1 ((DEVICE_MCASPRegs *) 0x55000000)
#define MCASP2 ((DEVICE_MCASPRegs *) 0x56000000)

typedef struct _DEVICE_UHPI_REGS
{
  VUint32 PID;                // 0x00
  VUint32 PWREMU_MGMT;        // 0x04
  VUint32 GPIOINT;            // 0x08
  VUint32 GPIOEN;             // 0x0C
  VUint32 GPIODIR1;           // 0x10
  VUint32 GPIODAT1;           // 0x14
  VUint32 GPIODIR2;           // 0x18
  VUint32 GPIODAT2;           // 0x1C
  VUint32 GPIODIR3;           // 0x20
  VUint32 GPIODAT3;           // 0x24
  VUint32 RSVD0[2];           // 0x28
  VUint32 HPIC;               // 0x30
  VUint32 HPIAW;              // 0x34
  VUint32 HPIAR;              // 0x38
  VUint32 XHPIAW;             // 0x3C
  VUint32 XHPIAR;             // 0x40
}
DEVICE_UHPIRegs;

#define UHPI ((DEVICE_UHPIRegs*) 0x43000000)

typedef struct _DEVICE_MEMCTRL_REGS_
{
  VUint32 L1PISAR;
  VUint32 L1PICR;
  VUint32 MEMCSR;
  VUint32 BCFGR;
  VUint32 PCER;
}
DEVICE_MemCtrlRegs;

#define MEMCTRL ((DEVICE_MemCtrlRegs*) 0x20000000)

typedef struct _DEVICE_DMAX_CTRL_REGS_
{
    volatile Uint32 GIOGCR;       // 0x00
    volatile Uint32 RSVD0;        // 0x04
    volatile Uint32 DEPR;         // 0x08
    volatile Uint32 DEER;         // 0x0C
    volatile Uint32 DEDR;         // 0x10
    volatile Uint32 DEHPR;        // 0x14
    volatile Uint32 DELPR;        // 0x18
    volatile Uint32 DEFR;         // 0x1C
    volatile Uint32 RSVD1[4];     // 0x20
    volatile Uint32 GIODIR;       // 0x30
    volatile Uint32 DER0;         // 0x34
    volatile Uint32 RSVD2[2];     // 0x38    
    volatile Uint32 DFSR0;        // 0x40
    volatile Uint32 RSVD3[4];     // 0x44
    volatile Uint32 DER1;         // 0x54
    volatile Uint32 RSVD4[2];     // 0x58    
    volatile Uint32 DFSR1;        // 0x60
    volatile Uint32 RSVD5[4];     // 0x64
    volatile Uint32 DER2;         // 0x74
    volatile Uint32 RSVD6[2];     // 0x78
    volatile Uint32 DTCR0;        // 0x80
    volatile Uint32 RSVD7[4];     // 0x84
    volatile Uint32 DER3;         // 0x94
    volatile Uint32 RSVD8[2];     // 0x98
    volatile Uint32 DTCR1;        // 0xA0
}
DEVICE_dMaxCtrlRegs;

#define DMAX ((DEVICE_dMaxCtrlRegs *) 0x60000000)

/***********************************************************
* Global Variable Declarations                             *
***********************************************************/

extern far Uint32 DEVICE_fxnArg[DEVICE_MAX_FXN_ARG_CNT];
extern far const DEVICE_FxnPtr DEVICE_fxnPtr[];



/***********************************************************
* Global Function Declarations                             *
***********************************************************/

Uint32 DEVICE_init(void);
DEVICE_BootMode DEVICE_bootMode( void );
DEVICE_BusWidth DEVICE_emifBusWidth( void );
void DEVICE_pllConfig(Uint32 pllm, Uint32 div0, Uint32 div1, Uint32 div2, Uint32 div3);


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
