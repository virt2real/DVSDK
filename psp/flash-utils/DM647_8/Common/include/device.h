/* --------------------------------------------------------------------------
  FILE        : device.h
  PURPOSE     : Device-specific Chip Support Library  -  DM647/8 version
  PROJECT     : DaVinci flashing utilities
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
  DEVICE_BOOTMODE_EMU           = 0x0,      // Emulation boot
  DEVICE_BOOTMODE_PCI_AI        = 0x1,      // PCI with autoinit - PCI Requires Fastboot, auto init data in I2C EEPROM
  DEVICE_BOOTMODE_HPI1          = 0x1,      // HPI, requires UHPIEN=1
  DEVICE_BOOTMODE_PCI           = 0x2,      // PCI, no autoinit - PCI Requires Fastboot, 
  DEVICE_BOOTMODE_HPI2          = 0x2,      // HPI, requires UHPIEN=1
  DEVICE_BOOTMODE_UART          = 0x3,      // UART Boot, no flow control
  DEVICE_BOOTMODE_EMIF          = 0x4,      // Fastboot => AIS (x20 PLL), No Fastboot => XiP (PLL bypass)
  DEVICE_BOOTMODE_I2C           = 0x5,      // Fastboot => x20 PLL, no Fastboot => PLL bypass
  DEVICE_BOOTMODE_SPI           = 0x6,      // Fastboot => x20 PLL, no Fastboot => PLL bypass
  DEVICE_BOOTMODE_SGMII0        = 0x8,      // SGMII0 - Boot Port, no packet forwarding
  DEVICE_BOOTMODE_SGMII0_PF     = 0x9,      // SGMII0 - Boot Port, SGMII1 - packet forwarding
  DEVICE_BOOTMODE_SGMII1_PF     = 0xA,      // SGMII1 - Boot Port, SGMII0 - packet forwarding
  DEVICE_BOOTMODE_UART_FC       = 0xE       // UART Boot, hardware flow control
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
  VUint32  PINMUX[1];     //0x00
  VUint8  RSVD0[4];       //0x04
  VUint32 DSPBOOTADDR;    //0x08
  VUint32 BOOTCOMPLT;     //0x0C
  VUint8  RSVD1[4];       //0x10
  VUint32 BOOTCFG;        //0x14
  VUint32 JTAGID;         //0x18
  VUint32 PRI_ALLOC;      //0x1C
  VUint8  RSVD2[52];      //0x20
  VUint32 KEY_REG;        //0x54
  VUint8  RSVD3[80];      //0x58
  VUint32 CFGPLL;         //0xA8
  VUint8  RSVD4[4];       //0xAC
  VUint32 CFGRX0;         //0xB0
  VUint32 CFGRX1;         //0xB4
  VUint32 CFGTX0;         //0xB8
  VUint32 CFGTX1;         //0xBC
  VUint8  RSVD5[4];       //0XC0
  VUint32 MAC_ADDR_R0;    //0xC4
  VUint32 MAC_ADDR_R1;    //0xC8
  VUint32 MAC_ADDR_RW0;   //0xCC
  VUint32 MAC_ADDR_RW1;   //0xD0
  VUint32 ESS_LOCK;       //0xD4
}
DEVICE_SysModuleRegs;

#define SYSTEM  ((DEVICE_SysModuleRegs*) 0x02049000)
#define RESET_ADDR                      (0x00800000)
#define DEVICE_KEY_REG_UNLOCK_VALUE     (0xADDDECAF)

#define DEVICE_BOOTCFG_BOOTMODE_MASK    (0x0000000F)
#define DEVICE_BOOTCFG_BOOTMODE_SHIFT   (0)

#define DEVICE_BOOTCFG_EMIFWIDTH_MASK   (0x00010000)
#define DEVICE_BOOTCFG_EMIFWIDTH_SHIFT  (16)

#define DEVICE_BOOTCFG_UHPIEN_MASK      (0x00020000)
#define DEVICE_BOOTCFG_UHPIEN_SHIFT     (17)

#define DEVICE_BOOTCFG_FASTBOOT_MASK    (0x00080000)
#define DEVICE_BOOTCFG_FASTBOOT_SHIFT   (19)

#define DEVICE_BOOTCFG_PCIEN_MASK       (0x00020000)
#define DEVICE_BOOTCFG_PCIEN_SHIFT      (17)

#define DEVICE_PINMUX_UART_MASK         (0x00003000)
#define DEVICE_PINMUX_SPI_MASK          (0x00003000)
#define DEVICE_PINUMX_UART_EN           (0x00002000)
#define DEVICE_PINMUX_SPI_EN            (0x00001000)

#define DEVICE_PINMUX_VP0_MASK          (0x00300000)
#define DEVICE_PINMUX_VP1_MASK          (0x00030000)
#define DEVICE_PINMUX_VP34_MASK         (0x0000C000)
#define DEVICE_PINMUX_EMIF_MASK         (0x0000C000)
#define DEVICE_PINMUX_MCASP_MASK        (0x00000300)
#define DEVICE_PINMUX_VP2_MASK          (0x00000030)
#define DEVICE_PINMUX_VLYNQ_MASK        (0x00000030)

#define DEVICE_PINMUX_VP0_EN            (0x00200000)
#define DEVICE_PINMUX_VP1_EN            (0x00030000)
#define DEVICE_PINMUX_VP34_EN           (0x0000C000)
#define DEVICE_PINMUX_EMIF_EN           (0x00008000)
#define DEVICE_PINMUX_MCASP_EN          (0x00000200)
#define DEVICE_PINMUX_VP2_EN            (0x00000020)
#define DEVICE_PINMUX_VLYNQ_EN          (0x00000030)


typedef struct _DEVICE_CACHE_REGS_
{
  VUint32 L2CFG;
  VUint8 RSVD0[28];
  VUint32 L1PCFG;
  VUint32 L1PCC;
  VUint8 RSVD1[24];
  VUint32 L1DCFG;
  VUint32 L1DCC;
  VUint8 RSVD2[16312];
  VUint32 L2WBAR;
  VUint32 L2WWC;
  VUint8 RSVD3[8];
  VUint32 L2WIBAR;
  VUint32 L2WIWC;
  VUint32 L2IBAR;
  VUint32 L2IWC;
  VUint32 L1PIBAR;
  VUint32 L1PIWC;
  VUint8 RSVD4[8];
  VUint32 L1DWIBAR;
  VUint32 L1DWIWC;
  VUint8 RSVD5[8];
  VUint32 L1DWBAR;
  VUint32 L1DWWC;
  VUint32 L1DIBAR;
  VUint32 L1DIWC;
  VUint8 RSVD6[4016];
  VUint32 L2WB;
  VUint32 L2WBINV;
  VUint32 L2INV;
  VUint8 RSVD7[28];
  VUint32 L1PINV;
  VUint8 RSVD8[20];
  VUint32 L1DWB;
  VUint32 L1DWBINV;
  VUint32 L1DINV;
  VUint8 RSVD9[12212];
  VUint32 MAR[256];
}
DEVICE_CacheRegs;

#define CACHE ((DEVICE_CacheRegs*)(0x01840000))


// PLL Register structure
typedef struct _DEVICE_PLL_REGS_
{
  VUint32 PID;                // 0x000
  VUint8  RSVD0[224];         // 0x004
  VUint32 RSTYPE;             // 0x0E4
  VUint8  RSVD1[24];          // 0x0E8
  VUint32 PLLCTL;             // 0x100
  VUint8  RSVD2[12];          // 0x104
  VUint32 PLLM;               // 0x110
  VUint32 PREDIV;             // 0x114
  VUint8  RSVD3[4];           // 0x118
  VUint32 PLLDIV2;            // 0x11C
  VUint8  RSVD4[24];          // 0x120
  VUint32 PLLCMD;             // 0x138
  VUint32 PLLSTAT;            // 0x13C
  VUint32 ALNCTL;             // 0x140
  VUint32 DCHANGE;            // 0x144
  VUint8  RSVD5[8];           // 0x148
  VUint32 SYSTAT;             // 0x150
  VUint8  RSVD6[12];          // 0x154
  VUint32 PLLDIV4;            // 0x160
}
DEVICE_PLLRegs;

#define PLL1 ((DEVICE_PLLRegs*) 0x020E0000)
#define PLL2 ((DEVICE_PLLRegs*) 0x02120000)
#define DEVICE_PLLCTL_PLLENSRC_MASK (0x00000020)
#define DEVICE_PLLCTL_PLLEN_MASK    (0x00000001)
#define DEVICE_PLLCTL_PLLRST_MASK   (0x00000008)
#define DEVICE_PLLCTL_PLLDIS_MASK   (0x00000010)
#define DEVICE_PLLCTL_PLLPWRDN_MASK (0x00000002)
#define DEVICE_PLLCMD_GOSET_MASK    (0x00000001)
#define DEVICE_PLLSTAT_GOSTAT_MASK  (0x00000001)
#define DEVICE_PLLSTAT_LOCK_MASK    (0x00000002)

#define DEVICE_PLL1_MULTIPLIER  (27u)

#define DEVICE_OSC_FREQ         (33000000u)
#define DEVICE_SYSTEM_FREQ (DEVICE_PLL1_MULTIPLIER * DEVICE_OSC_FREQ)


// Power/Sleep Ctrl Register structure
typedef struct _DEVICE_PSC_REGS_
{
  VUint32 PID;            // 0x00
  VUint8 RSVD0[20];       // 0x04
  VUint32 INTEVAL;        // 0x18
  VUint8 RSVD1[40];       // 0x1C
  VUint32 MERRPR1;        // 0x44
  VUint8 RSVD2[12];       // 0x48
  VUint32 MERRCR1;        // 0x54
  VUint8 RSVD3[200];      // 0x58
  VUint32 PTCMD;          // 0x120
  VUint8 RSVD4[4];        // 0x124
  VUint32 PTSTAT;         // 0x128
  VUint8 RSVD5[212];      // 0x12C
  VUint32 PDSTAT0;        // 0x200
  VUint8 RSVD6[252];      // 0x204
  VUint32 PDCTL0;         // 0x300
  VUint8 RSVD7[1276];     // 0x304
  VUint32 MDSTAT[40];     // 0x800
  VUint8 RSVD8[352];      // 0x8A0
  VUint32 MDCTL[40];      // 0xA00
}
DEVICE_PSCRegs;

#define PSC ((DEVICE_PSCRegs*) 0x02046000)

/* PSC constants */
#define LPSC_TPCC         (0)

#define LPSC_DDR2         (7)
#define LPSC_UHPI         (8)
#define LPSC_VLYNQ        (9)
#define LPSC_GPIO         (10)
#define LPSC_TIMER0       (11)
#define LPSC_TIMER1       (12)

#define LPSC_SPI          (17)
#define LPSC_I2C          (18)
#define LPSC_PCI          (19)
#define LPSC_VP0          (20)
#define LPSC_VP1          (21)
#define LPSC_VP2          (22)
#define LPSC_VP3          (23)
#define LPSC_VP4          (24)
#define LPSC_EMIFA        (25)
#define LPSC_TIMER2       (26)
#define LPSC_TIMER3       (27)
#define LPSC_VIC          (28)
#define LPSC_MCASP        (29)
#define LPSC_UART0        (30)
#define LPSC_IMCOP        (31)
#define LPSC_CHIPREGS     (32)
#define LPSC_DSP          (33)
#define LPSC_3PSW         (34)

#define EMURSTIE_MASK     (0x00000200)

#define PD0               (0)
#define PD1               (1)

#define PSC_ENABLE        (0x3)
#define PSC_DISABLE       (0x2)
#define PSC_SYNCRESET     (0x1)
#define PSC_SWRSTDISABLE  (0x0)

 
// DDR2 Memory Ctrl Register structure
typedef struct _DEVICE_DDR2_REGS_
{
  VUint32 MIDR;           //0x00
  VUint32 DMCSTAT;        //0x04
  VUint32 SDCFG;          //0x08
  VUint32 SDRFC;          //0x0C
  VUint32 SDTIM1;         //0x10
  VUint32 SDTIM2;         //0x14
  VUint8  RSVD0[8];       //0x18 
  VUint32 BPRIO;          //0x20
  VUint8  RSVD2[192];     //0x24 
  VUint32 DMCCTL;         //0xE4
}
DEVICE_DDR2Regs;

#define DDR2                      ((DEVICE_DDR2Regs*) 0x78000000)

#define DEVICE_DDR2_TEST_PATTERN  (0xA55AA55Au)
#define DEVICE_DDR2_RAM_SIZE      (0x10000000u)

#define DEVICE_MAX_IMAGE_SIZE     (0x02000000u)
#define DEVICE_DDR2_START_ADDR    (0xE0000000u)
#define DEVICE_DDR2_END_ADDR      ((RAM_START_ADDR + DDR_RAM_SIZE))


// AEMIF Register structure
typedef struct _DEVICE_EMIF_REGS_
{
  VUint32 MIDR;           // 0x00
  VUint32 STAT;           // 0x04
  VUint8  RSVD0[24];      // 0x08
  VUint32 BPRIO;          // 0x20
  VUint8  RSVD1[92];      // 0x24
  VUint32 AB1CR;          // 0x80
  VUint32 AB2CR;          // 0x84
  VUint8 RSVD2[24];       // 0x88
  VUint32 AWCCR;          // 0xA0
  VUint8 RSVD3[28];       // 0x84
  VUint32 INTRAW;         // 0xA0
  VUint32 INTMSK;         // 0xA4
  VUint32 INTMSKSET;      // 0xA8
  VUint32 INTMSKCLR;      // 0xAC
}
DEVICE_EmifRegs;

#define AEMIF ((DEVICE_EmifRegs*) 0x70000000)
#define DEVICE_EMIF_NUMBER_CE_REGION        (2)
#define DEVICE_EMIF_FIRST_CE_START_ADDR     (0xA0000000)
#define DEVICE_EMIF_INTER_CE_REGION_SIZE    (0x10000000)

#define DEVICE_EMIF_AWCC_WAITSTATE_MASK     (0x000007FF)


// UART Register structure
typedef struct _DEVICE_UART_REGS_
{
  VUint32 RBR;            // 0x00
  VUint32 IER;            // 0x04
  VUint32 IIR;            // 0x08
  VUint32 LCR;            // 0x0C
  VUint32 MCR;            // 0x10
  VUint32 LSR;            // 0x14
  VUint32 MSR;            // 0x18
  VUint32 SCR;            // 0x1C
  VUint8 DLL;             // 0x20
  VUint8 RSVDO[3];
  VUint8 DLH;             // 0x24
  VUint8 RSVD1[3];  
  VUint32 PID1;           // 0x28
  VUint32 PID2;           // 0x2C
  VUint32 PWREMU_MGNT;    // 0x30
  VUint32 MDR;            // 0x34
}
DEVICE_UartRegs;

#define THR RBR
#define FCR IIR

#define UART0 ((DEVICE_UartRegs*) 0x02047000)

#define DEVICE_UART0_DESIRED_BAUD   (115200)
#define DEVICE_UART0_OVERSAMPLE_CNT (16)


// Timer Register structure
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

#define TIMER0 ((DEVICE_TimerRegs*) 0x02044400)
#define TIMER0_LO_INT_EVENT_NUM     (67)
#define TIMER0_HI_INT_EVENT_NUM     (68)

#define TIMER1 ((DEVICE_TimerRegs*) 0x02044800)
#define TIMER1_LO_INT_EVENT_NUM     (69)
#define TIMER1_HI_INT_EVENT_NUM     (70)

#define TIMER2 ((DEVICE_TimerRegs*) 0x02044C00)
#define TIMER2_LO_INT_EVENT_NUM     (19)
#define TIMER2_HI_INT_EVENT_NUM     (20)

#define TIMER3 ((DEVICE_TimerRegs*) 0x02045000)
#define TIMER3_LO_INT_EVENT_NUM     (21)
#define TIMER3_HI_INT_EVENT_NUM     (22)


// I2C Register structure
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

#define I2C_PERIPHERAL_CNT      (1)
#define I2C_MEMORYMAP_SPACING   (0x00000000u)

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

#define SPI0 ((DEVICE_I2CRegs*) 0x02047800)

#define SPI_PERIPHERAL_CNT      (1)
#define SPI_MEMORYMAP_SPACING   (0x00000000u)



// INTC register structure and masks - See DM648 datasheet for more info.
typedef struct _DEVICE_INTC_REGS_
{
  VUint32 EVTFLAG[4];   // 0x000
  VUint8 RSVD0[16];     // 0x010
  VUint32 EVTSET[4];    // 0x020
  VUint8 RSVD1[16];     // 0x030
  VUint32 EVTCLR[4];    // 0x040
  VUint8 RSVD2[48];     // 0x050
  VUint32 EVTMASK[4];   // 0x080
  VUint8 RSVD3[16];     // 0x090
  VUint32 MEVTFLAG[4];  // 0x0A0
  VUint8 RSVD4[16];     // 0x0B0
  VUint32 EXPMASK[4];   // 0x0C0
  VUint8 RSVD5[16];     // 0x0D0
  VUint32 MEXPFLAG[4];  // 0x0E0
  VUint32 INTMUX[4];    // 0x100
  VUint8 RSVD6[48];     // 0x110
  VUint32 AEGMUX[2];    // 0x140
  VUint8 RSVD7[56];     // 0x148
  VUint32 INTXSTAT;     // 0x180
  VUint32 INTXCLR;      // 0x184
  VUint32 INTDMASK;     // 0x188
  VUint8 RSVD8[52];     // 0x18C
  VUint32 EVTASRT;      // 0x1C0
}
DEVICE_IntcRegs;

#define INTC ((DEVICE_IntcRegs*) 0x01800000)


/***********************************************************
* Device Init Function Prototypes                          *
***********************************************************/

// Execute LPSC state transition
void    DEVICE_LPSCTransition(Uint8 module, Uint8 domain, Uint8 state);
void    DEVICE_PSCInit();

// Pinmux control
void    DEVICE_pinmuxControl(Uint32 regOffset, Uint32 mask, Uint32 value);

// Initialization prototypes
Uint32  DEVICE_init(void);
Uint32  DEVICE_UART0Init(void);
Uint32  DEVICE_TIMER0Init(void);
Uint32  DEVICE_EMIFInit(void);
Uint32  DEVICE_I2C0Init(void);
Uint32  DEVICE_PLL1Init(Uint32 PllMult);
Uint32  DEVICE_DDR2Init(void);

Uint32 DEVICE_I2C0Reset();

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

/* ---------------------------------------------------------------------------
    HISTORY
       v1.00  -  DJA  -  07-Nov-2007
         Initial Release
 ----------------------------------------------------------------------------- */

