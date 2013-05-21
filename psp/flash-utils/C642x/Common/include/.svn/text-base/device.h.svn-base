/* --------------------------------------------------------------------------
  FILE        : device.h 				                             	 	        
  PURPOSE     : Device-specific Chip Support Library  -  DM643x version
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

// Supported buswidth
typedef enum _DEVICE_BusWidth_
{
  DEVICE_BUSWIDTH_8BIT   = BUS_8BIT,
  DEVICE_BUSWIDTH_16BIT  = BUS_16BIT
}
DEVICE_BusWidth;

// Supported bootmodes
typedef enum _DEVICE_BootMode_
{
  DEVICE_BOOTMODE_EMU     = 0x0,     // Emulation boot mode 
  DEVICE_BOOTMODE_HPI_x27 = 0x1,     // HPI, x27
  DEVICE_BOOTMODE_PCI     = 0x1,     // HPI, x27
  DEVICE_BOOTMODE_HPI     = 0x2,     // HPI, x20 fastboot and normal
  DEVICE_BOOTMODE_PCI_AI  = 0x2,     // HPI, x20 fastboot and normal
  DEVICE_BOOTMODE_HPI_x15 = 0x3,     // HPI, x15
  DEVICE_BOOTMODE_EMIF    = 0x4,     // EMIF direct boot/EMIF ROM with AIS
  DEVICE_BOOTMODE_I2C     = 0x5,     // I2C
  DEVICE_BOOTMODE_SPI_16  = 0x6,     // 16-bit SPI
  DEVICE_BOOTMODE_NAND    = 0x7,     // NAND
  DEVICE_BOOTMODE_UART    = 0x8,     // UART boot, no flow control
  DEVICE_BOOTMODE_EMIF_FB = 0x9,     // EMIF ROM no AIS
  DEVICE_BOOTMODE_VLYNQ   = 0xA,     // Vlynq
  DEVICE_BOOTMODE_UART_FC = 0xE,     // UART boot, with flow control
  DEVICE_BOOTMODE_SPI_24  = 0xF     // 24-bit SPI
}
DEVICE_BootMode;


// System Control Module register structure
typedef struct _DEVICE_SYS_MODULE_REGS_
{
	VUint32 PINMUX[2];      //0x00
	VUint32 DSPBOOTADDR;    //0x08
	VUint32 BOOTCOMPLT;     //0x0C
	VUint8 RSVD0[4];		//0x10
	VUint32 BOOTCFG;        //0x14
	VUint8 RSVD1[16];		//0x18
	VUint32 DEVICE_ID;		//0x28
	VUint8 RSVD2[4];		//0x2C
	VUint32 UHPICTL;  		//0x30
	VUint8 RSVD3[8];		//0x34
	VUint32 MSTPRI[2];		//0x3C
	VUint32 VPSS_CLKCTL;	//0x44
	VUint32 VDD3P3V_PWDN;   //0x48
	VUint32 DDRVTPER;       //0x4C
	VUint8 RSVD4[52];       //0x50
	VUint32 TIMERCTL;       //0x84
	VUint32 EDMATCCFG;      //0x88
}
DEVICE_SysModuleRegs;

#define SYSTEM ((DEVICE_SysModuleRegs*) 0x01C40000)
#define RESET_ADDR                      (0x00100000)
#define DEVICE_BOOTCFG_BOOTMODE_MASK    (0x0000000F)
#define DEVICE_BOOTCFG_BOOTMODE_SHIFT   (0)

#define DEVICE_BOOTCFG_EMIFWIDTH_MASK   (0x00010000)
#define DEVICE_BOOTCFG_EMIFWIDTH_SHIFT	(16)

#define DEVICE_BOOTCFG_FASTBOOT_MASK    (0x00080000)
#define DEVICE_BOOTCFG_FASTBOOT_SHIFT   (19)

#define DEVICE_BOOTCFG_PCIEN_MASK       (0x00020000)
#define DEVICE_BOOTCFG_PCIEN_SHIFT      (17)


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

// PLL Register structure, See spru978.pdf, Chapter 5 for more details.
typedef struct _DEVICE_PLL_REGS_
{
	VUint32 PID;                // 0x000
	VUint8 RSVD0[224];          // 0x004
	VUint32 RSTYPE;             // 0x0E4
	VUint8 RSVD1[24];           // 0x0E8
	VUint32 PLLCTL;             // 0x100
	VUint8 RSVD2[12];           // 0x104
	VUint32 PLLM;               // 0x110
	VUint8 RSVD3[4];            // 0x114
	VUint32 PLLDIV1;            // 0x118
	VUint32 PLLDIV2;            // 0x11C
	VUint32 PLLDIV3;            // 0x120
	VUint32 OSCDIV1;            // 0x124
	VUint8 RSVD4[4];            // 0x128
	VUint32 BPDIV;              // 0x12C
	VUint8 RSVD5[8];            // 0x130
	VUint32 PLLCMD;             // 0x138
	VUint32 PLLSTAT;            // 0x13C
	VUint32 ALNCTL;             // 0x140
	VUint32 DCHANGE;            // 0x144
	VUint32 CKEN;               // 0x148
	VUint32 CKSTAT;             // 0x14C
	VUint32 SYSTAT;             // 0x150
} 
DEVICE_PLLRegs;

#define PLL1 ((DEVICE_PLLRegs*) 0x01C40800)
#define PLL2 ((DEVICE_PLLRegs*) 0x01C40C00)
#define DEVICE_PLLCTL_PLLENSRC_MASK (0x00000020)
#define DEVICE_PLLCTL_PLLEN_MASK    (0x00000001)
#define DEVICE_PLLCTL_PLLPWRDN_MASK (0x00000002)
#define DEVICE_PLLCTL_PLLRST_MASK   (0x00000008)
#define DEVICE_PLLCTL_PLLDIS_MASK   (0x00000010)
#define DEVICE_PLLCTL_PLLENSRC_MASK (0x00000020)
#define DEVICE_PLLCTL_CLKMODE_MASK  (0x00000100)

#define DEVICE_PLLCMD_GOSET_MASK    (0x00000001)
#define DEVICE_PLLSTAT_GOSTAT_MASK  (0x00000001)
#define DEVICE_PLLDIV_EN_MASK       (0x00008000)

#define DEVICE_PLL1_MULTIPLIER      (22)
#define DEVICE_PLL2_MULTIPLIER      (24)


// Power/Sleep Ctrl Register structure - See spru978.pdf, Chapter 6
typedef struct _DEVICE_PSC_REGS_
{
	VUint32 PID;            // 0x00
	VUint8 RSVD0[20];       // 0x04
	VUint32 INTEVAL;        // 0x18
	VUint8 RSVD1[40];	    // 0x1C
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
	VUint32 MDSTAT[41];     // 0x800
	VUint8 RSVD8[348];      // 0x8A4
	VUint32 MDCTL[41];      // 0xA00
}
DEVICE_PSCRegs;

#define PSC ((DEVICE_PSCRegs*) 0x01C41000)	

// PSC constants
#define LPSC_VPSS_MAST    (0)
#define LPSC_VPSS_SLV     (1)
#define LPSC_TPCC         (2)
#define LPSC_TPTC0        (3)
#define LPSC_TPTC1        (4)
#define LPSC_TPTC2       	(5)
#define LPSC_EMAC_MEM     (6)
#define LPSC_MDIO         (7)
#define LPSC_EMAC         (8)
#define LPSC_MCASP0       (9)
#define LPSC_VLYNQ        (11)
#define LPSC_HPI          (12)
#define LPSC_DDR2         (13)
#define LPSC_EMIFA        (14)
#define LPSC_PCI          (15)
#define LPSC_MCBSP0       (16)
#define LPSC_MCBSP1       (17)
#define LPSC_I2C          (18)
#define LPSC_UART0        (19)
#define LPSC_UART1        (20)
#define LPSC_HECC         (22)
#define LPSC_PWM0         (23)
#define LPSC_PWM1         (24)
#define LPSC_PWM2         (25)
#define LPSC_GPIO         (26)
#define LPSC_TIMER0       (27)
#define LPSC_TIMER1       (28)
#define LPSC_DSP          (39)

#define EMURSTIE_MASK     (0x00000200)

#define PSC_ENABLE        (0x3)
#define PSC_DISABLE       (0x2)
#define PSC_SYNCRESET     (0x1)
#define PSC_SWRSTDISABLE  (0x0)

#define PD0               (0)

 
// DDR2 Memory Ctrl Register structure
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

#define DDR                 ((DEVICE_DDR2Regs*) 0x20000000)
#define DDRVTPR             (*((VUint32*) 0x01C42038))

#define DEVICE_DDR2_TEST_PATTERN    (0xA55AA55Au)
#define DEVICE_DDR2_RAM_SIZE        (0x08000000u)

#define DEVICE_MAX_IMAGE_SIZE 		(0x02000000u)
#define DEVICE_DDR2_START_ADDR 		(0x80000000u)
#define DEVICE_DDR2_END_ADDR 		((DEVICE_DDR2_START_ADDR + DEVICE_DDR2_RAM_SIZE))


// AEMIF Register structure - See spru984.pdf for more details.
typedef struct _DEVICE_EMIF_REGS_
{
    VUint32 ERCSR;          // 0x00
    VUint32 AWCCR;          // 0x04
    VUint32 SDBCR;          // 0x08
    VUint32 SDRCR;          // 0x0C
    VUint32 AB1CR;          // 0x10
    VUint32 AB2CR;          // 0x14
    VUint32 AB3CR;          // 0x18
    VUint32 AB4CR;          // 0x1C
    VUint32 SDTIMR;         // 0x20
    VUint32 DDRSR;          // 0x24
    VUint32 DDRPHYCR;       // 0x28
    VUint32 DDRPHYSR;       // 0x2C
    VUint32 TOTAR;          // 0x30
    VUint32 TOTACTR;        // 0x34
    VUint32 DDRPHYID_REV;   // 0x38
    VUint32 SDSRETR;        // 0x3C
    VUint32 EIRR;           // 0x40
    VUint32 EIMR;           // 0x44
    VUint32 EIMSR;          // 0x48
    VUint32 EIMCR;          // 0x4C
    VUint32 IOCTRLR;        // 0x50
    VUint32 IOSTATR;        // 0x54
    VUint8 RSVD0[8];        // 0x58
    VUint32 NANDFCR;        // 0x60
    VUint32 NANDFSR;        // 0x64
    VUint8 RSVD1[8];        // 0x68
    VUint32 NANDF1ECC;      // 0x70
    VUint32 NANDF2ECC;      // 0x74
    VUint32 NANDF3ECC;      // 0x78
    VUint32 NANDF4ECC;      // 0x7C
    VUint8 RSVD2[4];        // 0x80
    VUint32 IODFTECR;       // 0x84
    VUint32 IODFTGCR;       // 0x88
    VUint8 RSVD3[4];        // 0x8C
    VUint32 IODFTMRLR;      // 0x90
    VUint32 IODFTMRMR;      // 0x94
    VUint32 IODFTMRMSBR;    // 0x98
    VUint8 RSVD4[20];       // 0x9C
    VUint32 MODRNR;         // 0xB0
}
DEVICE_EmifRegs;

#define AEMIF ((DEVICE_EmifRegs*) 0x01E00000)


#define DEVICE_EMIF_NUMBER_CE_REGION        (4)
#define DEVICE_EMIF_FIRST_CE_START_ADDR     (0x42000000)
#define DEVICE_EMIF_INTER_CE_REGION_SIZE    (0x02000000)

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
}
DEVICE_UartRegs;

#define THR RBR
#define FCR IIR

#define UART0 ((DEVICE_UartRegs*) 0x01C20000)
#define UART1 ((DEVICE_UartRegs*) 0x01C20400)

/* -------------------------------------------------------------------------- *
 *    Timer Register structure - See sprue26.pdf for more details.            *
 * -------------------------------------------------------------------------- */
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
#define TIMER0_LO_INT_EVENT_NUM     (4)
#define TIMER0_HI_INT_EVENT_NUM     (5)

#define TIMER1 ((DEVICE_TimerRegs*) 0x01C21800)
#define TIMER1_LO_INT_EVENT_NUM     (6)
#define TIMER1_HI_INT_EVENT_NUM     (7)


/* -------------------------------------------------------------------------- *
 *    INTC register structure and masks - See DM643x datasheet for more info. *
 * -------------------------------------------------------------------------- */
typedef struct _DEVICE_INTC_REGS_
{
	VUint32 EVTFLAG[4];		// 0x000
	VUint8 RSVD0[16];		// 0x010
	VUint32 EVTSET[4];		// 0x020
	VUint8 RSVD1[16];		// 0x030
	VUint32 EVTCLR[4];		// 0x040
	VUint8 RSVD2[48];		// 0x050
	VUint32 EVTMASK[4];		// 0x080
	VUint8 RSVD3[16];		// 0x090
	VUint32 MEVTFLAG[4];	// 0x0A0
	VUint8 RSVD4[16];		// 0x0B0
	VUint32 EXPMASK[4];		// 0x0C0
	VUint8 RSVD5[16];		// 0x0D0
	VUint32 MEXPFLAG[4];	// 0x0E0
	VUint32 INTMUX[4];		// 0x100
	VUint8 RSVD6[48];		// 0x110
	VUint32 AEGMUX[2];		// 0x140
	VUint8 RSVD7[56];		// 0x148
	VUint32 INTXSTAT;		// 0x180
	VUint32 INTXCLR;		// 0x184
	VUint32 INTDMASK;		// 0x188
	VUint8 RSVD8[52];		// 0x18C
	VUint32 EVTASRT;		// 0x1C0
}
DEVICE_IntcRegs;

#define INTC ((DEVICE_IntcRegs*) 0x01800000)

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
Uint32  DEVICE_PLL2Init(void);
Uint32  DEVICE_PLL1Init(void);
Uint32  DEVICE_DDR2Init(void);
Uint32  DEVICE_I2C0Reset();

// Device boot status functions
DEVICE_BootMode    DEVICE_bootMode( void );
DEVICE_BusWidth    DEVICE_emifBusWidth( void );

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

/* --------------------------------------------------------------------------
    HISTORY
 	    v1.00  -  DJA  -  18-Feb-2008
 	      Initial Release
 ----------------------------------------------------------------------------- */
