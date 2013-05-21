/* --------------------------------------------------------------------------
  FILE        : device.h                                                   
  PROJECT     : TI Boot and Flashing Utilities
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

// Device function pointer type
typedef Uint32 (*DEVICE_FxnPtr)(void);

typedef enum _DEVICE_CacheType_
{
  DEVICE_CACHETYPE_L1P = 0x0,
  DEVICE_CACHETYPE_L1D = 0x1,
  DEVICE_CACHETYPE_L2  = 0x2
}
DEVICE_CacheType;

// Supported buswidth
typedef enum _DEVICE_BUSWIDTH_
{
  DEVICE_BUSWIDTH_8BIT  = BUS_8BIT,
  DEVICE_BUSWIDTH_16BIT = BUS_16BIT
}
DEVICE_BusWidth;

typedef enum _DEVICE_SECURE_TYPE_
{
  DEVICE_NONSECURE        = 0x0,
  DEVICE_GENERIC_SECURE   = 0x1,
  DEVICE_CUSTOM_SECURE    = 0x2,
  DEVICE_TEST             = 0x3,
  DEVICE_BAD              = 0x4
}
DEVICE_SecureType;

typedef enum _DEVICE_CHIPREVID_TYPE_
{
  DEVICE_CHIPREVID_TYPE_DSPONLY = 0x0, 
  DEVICE_CHIPREVID_TYPE_ARMONLY = 0x1,
  DEVICE_CHIPREVID_TYPE_DSPBOOT = 0x2,
  DEVICE_CHIPREVID_TYPE_ARMBOOT = 0x3
}
DEVICE_ChipRevIDType;

typedef enum _DEVICE_BOOTPERIPHERAL_
{
  DEVICE_BOOTPERIPHERAL_NONE = 0,
  DEVICE_BOOTPERIPHERAL_NOR,
  DEVICE_BOOTPERIPHERAL_UHPI,
  DEVICE_BOOTPERIPHERAL_SPI,
  DEVICE_BOOTPERIPHERAL_I2C,
  DEVICE_BOOTPERIPHERAL_NAND,
  DEVICE_BOOTPERIPHERAL_USB,
  DEVICE_BOOTPERIPHERAL_UART,
  DEVICE_BOOTPERIPHERAL_RMII,
  DEVICE_BOOTPERIPHERAL_ESF
}
DEVICE_BootPeripheral;

typedef enum _DEVICE_BOOTMODE_
{
  DEVICE_BOOTMODE_NONE = 0,
  DEVICE_BOOTMODE_EMU_DEBUG,  
  DEVICE_BOOTMODE_NOR_EMIFA,
  DEVICE_BOOTMODE_NAND_EMIFA_8BIT,
  DEVICE_BOOTMODE_NAND_EMIFA_16BIT,
  DEVICE_BOOTMODE_UHPI,                       // 16 bit
  DEVICE_BOOTMODE_SPI0_FLASH,                 // 24 bit address
  DEVICE_BOOTMODE_SPI0_EEPROM,                // 16 bit address
  DEVICE_BOOTMODE_SPI0_SLAVE,                 // 16 bit data
  DEVICE_BOOTMODE_SPI1_FLASH,                 // 24 bit address
  DEVICE_BOOTMODE_SPI1_EEPROM,                // 16 bit address
  DEVICE_BOOTMODE_SPI1_SLAVE,                 // 16 bit data
  DEVICE_BOOTMODE_I2C0_MASTER,                // 16 bit address
  DEVICE_BOOTMODE_I2C0_SLAVE,                 // 16 bit data
  DEVICE_BOOTMODE_I2C1_MASTER,                // 16 bit address
  DEVICE_BOOTMODE_I2C1_SLAVE,                 // 16 bit data
  DEVICE_BOOTMODE_UART0,
  DEVICE_BOOTMODE_UART1,
  DEVICE_BOOTMODE_UART2,
  DEVICE_BOOTMODE_ESF,
  DEVICE_BOOTMODE_MMC,                        // Not supported
  DEVICE_BOOTMODE_RMII,                       // Not supported
  DEVICE_BOOTMODE_USB11,                      // Not supported
  DEVICE_BOOTMODE_USB20,                      // Not supported
  DEVICE_BOOTMODE_THB = 0xAA  
}
DEVICE_BootMode;

// C6740 Megamodule Power Down Controller 
typedef struct _DEVICE_C6740_PDC_
{
  VUint32 PDCCMD;
}
DEVICE_C6740_PDCRegs;

#define PDC ((DEVICE_C6740_PDCRegs *) 0x01810000)

// C6740 IDMA
typedef struct _DEVICE_C6740_IDMA_
{
  VUint32 STAT;
  VUint32 MASK;
  VUint32 SOURCE;  
  VUint32 DEST;
  VUint32 CNT;  
}
DEVICE_C6740_IDMARegs;

#define IDMA0 ((DEVICE_C6740_IDMARegs *) 0x01820000)
#define IDMA1 ((DEVICE_C6740_IDMARegs *) 0x01820100)

// C6740 L1P Control
typedef struct _DEVICE_C6740_L1P_
{
  VUint8  RSVD0[0x20];    // 0x0000
  VUint32 L1PCFG;         // 0x0020
  VUint32 L1PCC;          // 0x0024
  VUint8  RSVD1[0x3FF8];  // 0x0028
  VUint32 L1PIBAR;        // 0x4020
  VUint32 L1PIWC;         // 0x4024
  VUint8  RSVD2[0x1000];  // 0x4028
  VUint32 L1PINV;         // 0x5028
}
DEVICE_C6740_L1PRegs;

#define L1PCTL ((DEVICE_C6740_L1PRegs *) 0x01840000)

// C6740 L1D Control
typedef struct _DEVICE_C6740_L1D_
{
  VUint8  RSVD0[0x40];    // 0x0000
  VUint32 L1DCFG;         // 0x0040
  VUint32 L1DCC;          // 0x0044
  VUint8  RSVD1[0x3FE8];  // 0x0048
  VUint32 L1DWIBAR;       // 0x4030
  VUint32 L1DWIWC;        // 0x4034
  VUint8  RSVD2[0x08];    // 0x4038
  VUint32 L1DWBAR;        // 0x4040
  VUint32 L1DWWC;         // 0x4044
  VUint32 L1DIBAR;        // 0x4048
  VUint32 L1DIWC;         // 0x404C
  VUint8  RSVD3[0xFF0];   // 0x4050
  VUint32 L1DWB;          // 0x5040
  VUint32 L1DWBINV;       // 0x5044
  VUint32 L1DINV;         // 0x5048
}
DEVICE_C6740_L1DRegs;

#define L1DCTL ((DEVICE_C6740_L1DRegs *) 0x01840000)


// C6740 L2 Control
typedef struct _DEVICE_C6740_L2_
{
  VUint32 L2CFG;          // 0x0000
  VUint8  RSVD0[0x3FFC];  // 0x0004
  VUint32 L2WBAR;         // 0x4000
  VUint32 L2WWC;          // 0x4004
  VUint8  RSVD1[0x08];    // 0x4008
  VUint32 L2WIBAR;        // 0x4010
  VUint32 L2WIWC;         // 0x4014
  VUint32 L2IBAR;         // 0x4018
  VUint32 L2IWC;          // 0x401C
  VUint8  RSVD2[0xFE0];   // 0x4020
  VUint32 L2WB;           // 0x5000
  VUint32 L2WBINV;        // 0x5004
  VUint32 L2INV;          // 0x5008
}
DEVICE_C6740_L2Regs;

#define L2CTL ((DEVICE_C6740_L2Regs *) 0x01840000)

// C6740 MPPA control
typedef struct _DEVICE_6474_MPPA_
{

  VUint32 L2MPFAR;        // 0x000
  VUint32 L2MPFSR;        // 0x004
  VUint32 L2MPFCLR;       // 0x008
  VUint8 RSVD0[0xF4];     // 0x00C
  VUint32 L2MPLK[4];      // 0x100
  VUint32 L2MPLKCMD;      // 0x110
  VUint32 L2MPLKSTAT;     // 0x114
  VUint8 RSVD1[0xE8];     // 0x118
  VUint32 L2MPPA[64];     // 0x200

  VUint8 RSVD3[0x100];    // 0x300

  VUint32 L1PMPFAR;       // 0x400
  VUint32 L1PMPFSR;       // 0x404
  VUint32 L1PMPFCLR;      // 0x408
  VUint8 RSVD4[0xF4];     // 0x40C
  VUint32 L1PMPLK[4];     // 0x500
  VUint32 L1PMPLKCMD;     // 0x510
  VUint32 L1PMPLKSTAT;    // 0x514
  VUint8 RSVD5[0xE8];     // 0x518
  VUint32 L1PMPPA[32];    // 0x600

  VUint8 RSVD6[0x580];    // 0x680

  VUint32 L1DMPFAR;       // 0xC00
  VUint32 L1DMPFSR;       // 0xC04
  VUint32 L1DMPFCLR;      // 0xC08
  VUint8 RSVD7[0xF4];     // 0xC0C
  VUint32 L1DMPLK[4];     // 0xD00
  VUint32 L1DMPLKCMD;     // 0xD10
  VUint32 L1DMPLKSTAT;    // 0xD14
  VUint8 RSVD8[0xE8];     // 0xD18
  VUint32 L1DMPPA[32];    // 0xE00
}
DEVICE_C6740_MPPARegs;

#define MPPACTL ((DEVICE_C6740_MPPARegs *) 0x0184A000)

#define C6740x_MPPA_UX      (0x00000001u)
#define C6740x_MPPA_UW      (0x00000002u)
#define C6740x_MPPA_UR      (0x00000004u)
#define C6740x_MPPA_SX      (0x00000008u)
#define C6740x_MPPA_SW      (0x00000010u)
#define C6740x_MPPA_SR      (0x00000020u)
#define C6740x_MPPA_EMU     (0x00000040u)
#define C6740x_MPPA_NS      (0x00000080u)


// C6740 Megamodule memory error controller
typedef struct _DEVICE_C6740_EDC_
{
  VUint8  RSVD0[4];     // 0x000
  VUint32 L2EDSTAT;     // 0x004
  VUint32 L2EDCMD;      // 0x008
  VUint32 L2EDADDR;     // 0x00C
  VUint32 L2EDPEN0;     // 0x010
  VUint32 L2EDPEN1;     // 0x014
  VUint32 L2EDCPEC;     // 0x018
  VUint32 L2EDNPEC;     // 0x01C
  VUint8  RSVD1[0x3E4]; // 0x020
  VUint32 L1PEDSTAT;    // 0x404
  VUint32 L1PEDCMD;     // 0x408
  VUint32 L1PEDADDR;    // 0x40C
}
DEVICE_C6740_EDCRegs;

#define DSP_EDC ((DEVICE_C6740_EDCRegs *) 0x01846000)


// C6740 Megamodule Interrupt Controller
typedef struct _DEVICE_C6740_INTC_
{
  VUint32 EVTFLAG[4];     // 0x000
  VUint8 RSVD0[16];       // 0x010
  VUint32 EVTSET[4];      // 0x020
  VUint8 RSVD1[16];       // 0x030
  VUint32 EVTCLR[4];      // 0x040
  VUint8 RSVD2[48];       // 0x050
  VUint32 EVTMASK[4];     // 0x080
  VUint8 RSVD3[16];       // 0x090
  VUint32 MEVTFLAG[4];    // 0x0A0
  VUint8 RSVD4[16];       // 0x0B0
  VUint32 EXPMASK[4];     // 0x0C0
  VUint8 RSVD5[16];
  VUint32 MEXPFLAG[4];
  VUint8 RSVD6[20];
  VUint32 INTMUX1;
  VUint32 INTMUX2;
  VUint32 INTMUX3;
  VUint8 RSVD7[48];
  VUint32 AEGMUX0;
  VUint32 AEGMUX1;
  VUint8 RSVD8[56];
  VUint32 INTXSTAT;
  VUint32 INTXCLR;
  VUint32 INTDMASK;
  VUint8 RSVD9[52];
  VUint32 EVTASRT;
}
DEVICE_C6740_INTCRegs;

#define DSP_INTC ((DEVICE_C6740_INTCRegs *) 0x01800000)


// System Control Module register structure
typedef struct _DEVICE_SYS_MODULE_REGS_
{
  VUint32 REVID;              //0x00
  VUint8  RSVD0[4];           //0x04
  VUint32 DIEIDR[4];          //0x04
  VUint32 DEVIDD[2];          //0x18
  VUint32 BOOTCFG;            //0x20
  VUint32 CHIPREVID;          //0x24
  VUint32 FEATURE_ENA;        //0x28
  VUint32 L2ROMDIV;           //0x2C
  VUint8  RSVD1[8];           //0x30
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
  VUint32 FLTCLR;             //0xFC
  VUint8  RSVD3[16];          //0x100
  VUint32 MSTPRI[3];          //0x110
  VUint8  RSVD4[4];           //0x11C
  VUint32 PINMUX[20];         //0x120
  VUint32 SUSPSRC;            //0x170
  VUint32 CHIPSIG;            //0x174
  VUint32 CHIPSIG_CLR;        //0x178
  VUint32 CFGCHIP[5];         //0x17C
  VUint8  RSVD5[5];           //0x190
  VUint32 ROMCHECKSUM[2];     //0x1A0
}
DEVICE_SysModuleRegs;

#define SYSTEM ((DEVICE_SysModuleRegs*) 0x01C14000)

#define DEVICE_BOOTCFG_BOOTMODE_MASK    (0x000000FFu)
#define DEVICE_BOOTCFG_BOOTMODE_SHIFT   (0)

#define DEVICE_CHIPREVID_TYPE_MASK      (0x00000030u)
#define DEVICE_CHIPREVID_TYPE_SHIFT     (4)

#define DEVICE_CFGCHIP0_PLL0MASTERLOCK_MASK    (0x00000010u)
#define DEVICE_CFGCHIP0_PLL0MASTERLOCK_SHIFT   (4)

#define DEVICE_CFGCHIP1_HPIBYTEAD_MASK  (0x00010000u)
#define DEVICE_CFGCHIP1_HPIBYTEAD_SHIFT (16)
#define DEVICE_CFGCHIP1_HPIENA_MASK     (0x00008000u)
#define DEVICE_CFGCHIP1_HPIENA_SHIFT    (15)

#define DEVICE_CFGCHIP3_RMII_MODE_MASK        (0x00000100u)
#define DEVICE_CFGCHIP3_RMII_MODE_SHIFT       (8)
#define DEVICE_CFGCHIP3_EMB_2XCLKSRC_MASK     (0x00000080u)
#define DEVICE_CFGCHIP3_EMB_2XCLKSRC_SHIFT    (7)
#define DEVICE_CFGCHIP3_RPI_TXCLKSRC_MASK     (0x00000040u)
#define DEVICE_CFGCHIP3_RPI_TXCLKSRC_SHIFT    (6)
#define DEVICE_CFGCHIP3_PLL1MASTERLOCK_MASK   (0x00000020u)
#define DEVICE_CFGCHIP3_PLL1MASTERLOCK_SHIFT  (5)
#define DEVICE_CFGCHIP3_ASYNC3_CLKSRC_MASK    (0x00000010u)
#define DEVICE_CFGCHIP3_ASYNC3_CLKSRC_SHIFT   (4)
#define DEVICE_CFGCHIP3_dMAXEVTSEL_MASK       (0x00000008u)
#define DEVICE_CFGCHIP3_dMAXEVTSEL_SHIFT      (3)
#define DEVICE_CFGCHIP3_DIV4p5ENA_MASK        (0x00000004u)
#define DEVICE_CFGCHIP3_DIV4p5ENA_SHIFT       (2)
#define DEVICE_CFGCHIP3_EMA_CLKSRC_MASK       (0x00000002u)
#define DEVICE_CFGCHIP3_EMA_CLKSRC_SHIFT      (1)

#define DEVICE_L2ROMDIV_ADDRLINE_MASK   (0x000003FFu)
#define DEVICE_L2ROMDIV_ADDRLINE_SHIFT  (0)

typedef struct _DEVICE_SUBSCHIP_CONFIG_REGS_
{
  VUint32 VTPIO_CTL;
  VUint32 DDR_SLEW;
  VUint32 DEEPSLEEP;
  VUint32 PUPD_ENA;
  VUint32 PUPD_SEL;
  VUint32 RXACTIVE;
  VUint32 RSVD0[2];
}
DEVICE_SubchipConfigRegs;

#define SUBCHIPCFG ((DEVICE_SubchipConfigRegs*) 0x01E2C000)

#define DEVICE_VTPIO_CTL_READY_MASK       (0x00008000u)
#define DEVICE_VTPIO_CTL_READY_SHIFT      (15)
#define DEVICE_VTPIO_CTL_IOPWRDN_MASK     (0x00004000u)
#define DEVICE_VTPIO_CTL_IOPWRDN_SHIFT    (14)
#define DEVICE_VTPIO_CTL_CLKRZ_MASK       (0x00002000u)
#define DEVICE_VTPIO_CTL_CLKRZ_SHIFT      (13)
#define DEVICE_VTPIO_CTL_PWRSAVE_MASK     (0x00000100u)
#define DEVICE_VTPIO_CTL_PWRSAVE_SHIFT    (8)
#define DEVICE_VTPIO_CTL_LOCK_MASK        (0x00000080u)
#define DEVICE_VTPIO_CTL_LOCK_SHIFT       (7)
#define DEVICE_VTPIO_CTL_POWERDN_MASK     (0x00000040u)
#define DEVICE_VTPIO_CTL_POWERDN_SHIFT    (6)

// Security Controller Module register structure
typedef struct _DEVICE_SECURITYCTL_REGS_
{
  VUint32 PID;                // 0x000  
  VUint8 RSVD0[12];           // 0x004
  VUint32 SYSSTATUS;          // 0x010
  VUint32 SYSWR;              // 0x014
  VUint8 RSVD1[4];            // 0x018
  VUint32 ARMWR;              // 0x01C
  VUint32 SYSCONTROL;         // 0x020
  VUint32 SYSCONTROLPROTECT;  // 0x024
  VUint32 SYSTAPEN;
  VUint32 SECRESERVED;
  VUint32 PSTATUS;
  VUint32 PREADDEBUGDAT;
  VUint32 PWRITEDEBUGDAT;
}
DEVICE_SecurityCtlRegs;

#define SECURITYCTL ((DEVICE_SecurityCtlRegs*) 0x01C13000)

#define DEVICE_SYSSTATUS_DEVICE_TYPE_MASK       (0x00000007u)
#define DEVICE_SYSSTATUS_DEVICE_TYPE_SHIFT      (0)
#define DEVICE_SYSSTATUS_DEVICE_TYPE_TEST       (0x00000000u)
#define DEVICE_SYSSTATUS_DEVICE_TYPE_SECURE     (0x00000002u)
#define DEVICE_SYSSTATUS_DEVICE_TYPE_NONSECURE  (0x00000003u)

#define DEVICE_SYSSTATUS_SEC_OVERRIDE_MASK      (0x00000020u)
#define DEVICE_SYSSTATUS_SEC_OVERRIDE_SHIFT     (5)

#define DEVICE_SYSSTATUS_TEST_SEC_MASK          (0x00000010u)
#define DEVICE_SYSSTATUS_TEST_SEC_SHIFT         (4)

#define DEVICE_SYSSTATUS_TEST_NONSEC_MASK       (0x00000008u)
#define DEVICE_SYSSTATUS_TEST_NONSEC_SHIFT      (3)

#define DEVICE_SYSCONTROL_SEC_UPDATE_MASK       (0x00000101u)
#define DEVICE_SYSCONTROL_SEC_UPDATE_SHIFT      (0)
#define DEVICE_SYSCONTROL_TEST_SEC_MMR_MASK     (0x00000100u)
#define DEVICE_SYSCONTROL_TEST_SEC_MMR_SHIFT    (8)

#define DEVICE_SECRESERVED_JTAG_UNLOCK_ALLOW_MASK (0x00000010u)
#define DEVICE_SECRESERVED_JTAG_UNLOCK_ALLOW_SHIFT (0x00000004u)

#define DEVICE_PSTATUS_JTAG_UNLOCK_REQEST_MASK  (0x00000200u)
#define DEVICE_PSTATUS_JTAG_UNLOCK_REQEST_SHIFT (9)

#define DEVICE_PSTATUS_JTAG_PWD1_DONE_MASK      (0x00000400u)
#define DEVICE_PSTATUS_JTAG_PWD1_DONE_SHIFT     (10)

#define DEVICE_PSTATUS_JTAG_PWD2_DONE_MASK      (0x00000800u)
#define DEVICE_PSTATUS_JTAG_PWD2_DONE_SHIFT     (11)

// Security Key Manager Module register structure
typedef struct _DEVICE_KEYMANAGER_REGS_
{
  VUint32 REVID;        // 0x00
  VUint32 STAT;         // 0x04
  VUint32 CHKSUMSTAT;   // 0x08
  VUint8 RSVD0[4];      // 0x0C
  VUint32 KEY1WRD[4];   // 0x10 - MPK
  VUint32 KEY2WRD[4];   // 0x20 - KEK
  VUint32 KEY3WRD[4];   // 0x30 - CEK
}
DEVICE_KeyManagerRegs;

#define KEYMANAGER ((DEVICE_KeyManagerRegs*) 0x01C12000)


typedef struct _DEVICE_IOPU_REGS_
{
  VUint32 REVISION;             // 0x000
  VUint32 CONFIGURATION;        // 0x004
  VUint32 RSVD0[2];             // 0x008      
  VUint32 INTR_RAW_STATUS;      // 0x010
  VUint32 INTR_ENABLED_STATUS;  // 0x014
  VUint32 INTR_ENABLE;          // 0x018
  VUint32 INTR_ENABLE_CLR;      // 0x01C
  VUint32 EOI;                  // 0x020
  VUint32 INTR_VECTOR;          // 0x024
  VUint8  RSVD1[0xD8];          // 0x028
  VUint32 IO_MPPA[128];         // 0x100
  VUint32 MPFAR;                // 0x300
  VUint32 MPFSR;                // 0x304
  VUint32 MPFCR;                // 0x308
}
DEVICE_IopuRegs;

#define IOPU0 ((DEVICE_IopuRegs *) 0x01C16000)
#define IOPU1 ((DEVICE_IopuRegs *) 0x01C24000)
#define IOPU2 ((DEVICE_IopuRegs *) 0x01C17000)
#define IOPU3 ((DEVICE_IopuRegs *) 0x01E29000)
#define IOPU4 ((DEVICE_IopuRegs *) 0x01D0E000)
#define IOPU5 ((DEVICE_IopuRegs *) 0x01F0B000)

#define IOPU0_IO_CNT (2)
#define IOPU1_IO_CNT (3)
#define IOPU2_IO_CNT (2)
#define IOPU3_IO_CNT (2)
#define IOPU4_IO_CNT (0)
#define IOPU5_IO_CNT (0)
#define IOPU6_IO_CNT (8)

typedef struct _MPU_RANGE_
{
  VUint32 MPSAR; // 0x00
  VUint32 MPEAR; // 0x04
  VUint32 MPPA;  // 0x08
  VUint32 RSVD;  // 0x0C
}
MPU_Range;

typedef struct _DEVICE_MPU_REGS_
{
  VUint32 REVISION;         // 0x000
  VUint32 CONFIGURATION;    // 0x004
  VUint8  RSVD0[8];         // 0x008
  VUint32 INTR_RAW_STATUS;  // 0x010
  VUint32 INTR_ENABLED_STATUS;
  VUint32 INTR_ENABLE;      // 0x018
  VUint32 INTR_ENABLE_CLR;  // 0x01C
  VUint32 EOI;              // 0x020
  VUint32 INTR_VECTOR;      // 0x024
  VUint8  RSVD1[0xD8];      // 0x028
  VUint32 FIXED_MPSAR;      // 0x100
  VUint32 FIXED_MPEAR;      // 0x104
  VUint32 FIXED_MPPA;       // 0x108
  VUint8  RSVD2[0xF4];      // 0x10C
  MPU_Range PROG_RANGE[16]; // 0x200 - 0x300
  VUint32 MPFAR;            // 0x300
  VUint32 MPFSR;            // 0x304
  VUint32 MPFCR;            // 0x308
}
DEVICE_MpuRegs;

#define MPU1 ((DEVICE_MpuRegs *) 0x01E14000)
#define MPU2 ((DEVICE_MpuRegs *) 0x01E15000)

#define MPU1_RANGE_CNT (6)
#define MPU2_RANGE_CNT (12)


typedef struct _DEVICE_DMAX_CTRL_REGS_
{
  VUint32 CONTROL;
  VUint32 STATUS;
  VUint32 WAKEUP;
  VUint32 CYCLECNT;
  VUint32 STALLCNT;
  VUint8 RSVD0[12];
  VUint32 CONTABBLKIDX0;
  VUint32 CONTABBLKIDX1;
  VUint32 CONTABPROPTR0;
  VUint32 CONTABPROPTR1;
  VUint8 RSVD1[976];
  VUint32 INTGPR0;
  VUint32 INTGPR1;
  VUint32 INTGPR2;
  VUint32 INTGPR3;
  VUint32 INTGPR4;
  VUint32 INTGPR5;
  VUint32 INTGPR6;
  VUint32 INTGPR7;
  VUint32 INTGPR8;
  VUint32 INTGPR9;
  VUint32 INTGPR10;
  VUint32 INTGPR11;
  VUint32 INTGPR12;
  VUint32 INTGPR13;
  VUint32 INTGPR14;
  VUint32 INTGPR15;
  VUint32 INTGPR16;
  VUint32 INTGPR17;
  VUint32 INTGPR18;
  VUint32 INTGPR19;
  VUint32 INTGPR20;
  VUint32 INTGPR21;
  VUint32 INTGPR22;
  VUint32 INTGPR23;
  VUint32 INTGPR24;
  VUint32 INTGPR25;
  VUint32 INTGPR26;
  VUint32 INTGPR27;
  VUint32 INTGPR28;
  VUint32 INTGPR29;
  VUint32 INTGPR30;
  VUint32 INTGPR31;
  VUint32 INTCTER0;
  VUint32 INTCTER1;
  VUint32 INTCTER2;
  VUint32 INTCTER3;
  VUint32 INTCTER4;
  VUint32 INTCTER5;
  VUint32 INTCTER6;
  VUint32 INTCTER7;
  VUint32 INTCTER8;
  VUint32 INTCTER9;
  VUint32 INTCTER10;
  VUint32 INTCTER11;
  VUint32 INTCTER12;
  VUint32 INTCTER13;
  VUint32 INTCTER14;
  VUint32 INTCTER15;
  VUint32 INTCTER16;
  VUint32 INTCTER17;
  VUint32 INTCTER18;
  VUint32 INTCTER19;
  VUint32 INTCTER20;
  VUint32 INTCTER21;
  VUint32 INTCTER22;
  VUint32 INTCTER23;
  VUint32 INTCTER24;
  VUint32 INTCTER25;
  VUint32 INTCTER26;
  VUint32 INTCTER27;
  VUint32 INTCTER28;
  VUint32 INTCTER29;
  VUint32 INTCTER30;
  VUint32 INTCTER31;
}
DEVICE_dMaxCtrlRegs;

#define DMAX0 ((DEVICE_dMaxCtrlRegs *) 0x01C37000)
#define DMAX1 ((DEVICE_dMaxCtrlRegs *) 0x01C37800)

#define DEVICE_CONTROL_COUNTENABLE_MASK       (0x00000008)
#define DEVICE_CONTROL_COUNTENABLE_SHIFT      (3)
#define DEVICE_CONTROL_ENABLE_MASK            (0x00000002)
#define DEVICE_CONTROL_ENABLE_SHIFT           (1)


// PLL Register structure
typedef struct _DEVICE_PLL_REGS_
{
  VUint32 PID;
  VUint8 RSVD0[204];
  VUint32 SHIFTDIV;
  VUint32 CS0;
  VUint32 DFTCNTR;
  VUint32 DFTCNTRCTRL;
  VUint32 FUSERR;
  VUint32 RSTYPE;
  VUint32 RSTCTRL;
  VUint32 RSTCFG;
  VUint32 RSISO;
  VUint8 RSVD1[12];
  VUint32 PLLCTL;
  VUint32 OCSEL;
  VUint32 SECCTL;
  VUint8 RSVD2[4];
  VUint32 PLLM;
  VUint32 PREDIV;
  VUint32 PLLDIV1;
  VUint32 PLLDIV2;
  VUint32 PLLDIV3;
  VUint32 OSCDIV1;
  VUint32 POSTDIV;
  VUint32 BPDIV;
  VUint32 WAKEUP;
  VUint8 RSVD3[4];
  VUint32 PLLCMD;
  VUint32 PLLSTAT;
  VUint32 ALNCTL;
  VUint32 DCHANGE;
  VUint32 CKEN;
  VUint32 CKSTAT;
  VUint32 SYSTAT;
  VUint8 RSVD4[12];
  VUint32 PLLDIV4;
  VUint32 PLLDIV5;
  VUint32 PLLDIV6;
  VUint32 PLLDIV7;
  VUint32 PLLDIV8;
  VUint32 PLLDIV9;
  VUint32 PLLDIV10;
  VUint32 PLLDIV11;
  VUint32 PLLDIV12;
  VUint32 PLLDIV13;
  VUint32 PLLDIV14;
  VUint8 RSVD5[4];
  VUint32 PLLDIV15;
  VUint8 RSVD6[88];
  VUint32 PLLHDIVEN;
  VUint32 EMUCNT0;
  VUint32 EMUCNT1;
}
DEVICE_PLLRegs;

#define PLL0 ((DEVICE_PLLRegs*) 0x01C11000)
#define PLL1 ((DEVICE_PLLRegs*) 0x01E1A000)

#define DEVICE_PLLCTL_PLLEN_MASK      (0x00000001)
#define DEVICE_PLLCTL_PLLPWRDN_MASK   (0x00000002)
#define DEVICE_PLLCTL_PLLRST_MASK     (0x00000008)
#define DEVICE_PLLCTL_PLLDIS_MASK     (0x00000010)
#define DEVICE_PLLCTL_PLLENSRC_MASK   (0x00000020)
#define DEVICE_PLLCTL_EXTCLKSRC_MASK  (0x00000200)
#define DEVICE_PLLCTL_CLKMODE_MASK    (0x00000100)

#define DEVICE_PLLCMD_GOSET_MASK      (0x00000001)
#define DEVICE_PLLSTAT_GOSTAT_MASK    (0x00000001)
#define DEVICE_PLLDIV_EN_MASK         (0x00008000)

// Power/Sleep Ctrl Register structure
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

#define PSC_MDCTL_LRSTZ_MASK     (0x00000100u)
#define PSC_MDCTL_LRSTZ_SHIFT    (0x00000008u)

#define PSCNUM0             (0x0)
#define PSCNUM1             (0x1)

#define PD0                 (0x0)
#define PD1                 (0x1)

// PSC0 (Matrix) defines
#define LPSC_TPCC           (0)
#define LPSC_TPTC0          (1)
#define LPSC_TPTC1          (2)
#define LPSC_EMIFA          (3)
#define LPSC_SPI0           (4)
#define LPSC_MMCSD0         (5)
#define LPSC_ARMINTC        (6)
#define LPSC_ARMRAM         (7)
#define LPSC_SCnKM          (8)
#define LPSC_UART0          (9)
#define LPSC_DMAX           (13)
#define LPSC_ARM            (14)
#define LPSC_DSP            (15)

// PSC1 (Subchip) defines
#define LPSC_TPCC1          (0)
#define LPSC_USB0           (1)
#define LPSC_USB1           (2)
#define LPSC_GPIO           (3)
#define LPSC_UHPI0          (4)
#define LPSC_EMAC           (5)
#define LPSC_EMIFB          (6)
#define LPSC_McASP0         (7)
#define LPSC_SATA           (8)
#define LPSC_VPIF           (9)
#define LPSC_SPI1           (10)
#define LPSC_I2C1           (11)
#define LPSC_UART1          (12)
#define LPSC_UART2          (13)
#define LPSC_McBSP0         (14)
#define LPSC_McBSP1         (15)
#define LPSC_LCDC           (16)
#define LPSC_HR_EPWM        (17)
#define LPSC_MMCSD1         (18)
#define LPSC_RPI            (19)
#define LPSC_ECAP           (20)
#define LPSC_TPTC2          (21)
#define LPSC_L3CBA          (31)


// AEMIF Register structure - From EMIF 2.5 Spec
typedef struct _DEVICE_EMIF25_REGS_
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
DEVICE_Emif25Regs;

#define AEMIF ((DEVICE_Emif25Regs*) 0x68000000u)

#define DEVICE_EMIF_NUMBER_CE_REGION                      (4)
#define DEVICE_EMIF_FIRST_CE_START_ADDR                   (0x60000000u)
#define DEVICE_EMIF_INTER_CE_REGION_SIZE                  (0x02000000u)

#define DEVICE_EMIF_AxCR_SS_MASK                          (0x80000000u)
#define DEVICE_EMIF_AxCR_SS_SHIFT                         (31)
#define DEVICE_EMIF_AxCR_EW_MASK                          (0x40000000u)
#define DEVICE_EMIF_AxCR_EW_SHIFT                         (30)
#define DEVICE_EMIF_AxCR_WSETUP_MASK                      (0x3C000000u)
#define DEVICE_EMIF_AxCR_WSETUP_SHIFT                     (26)
#define DEVICE_EMIF_AxCR_WSTROBE_MASK                     (0x03F00000u)
#define DEVICE_EMIF_AxCR_WSTROBE_SHIFT                    (20)
#define DEVICE_EMIF_AxCR_WHOLD_MASK                       (0x000E0000u)
#define DEVICE_EMIF_AxCR_WHOLD_SHIFT                      (17)
#define DEVICE_EMIF_AxCR_RSETUP_MASK                      (0x0001E000u)
#define DEVICE_EMIF_AxCR_RSETUP_SHIFT                     (13)
#define DEVICE_EMIF_AxCR_RSTROBE_MASK                     (0x00001F80u)
#define DEVICE_EMIF_AxCR_RSTROBE_SHIFT                    (7)
#define DEVICE_EMIF_AxCR_RHOLD_MASK                       (0x00000070u)
#define DEVICE_EMIF_AxCR_RHOLD_SHIFT                      (4)
#define DEVICE_EMIF_AxCR_TA_MASK                          (0x0000000Cu)
#define DEVICE_EMIF_AxCR_TA_SHIFT                         (2)
#define DEVICE_EMIF_AxCR_ASIZE_MASK                       (0x00000003u)
#define DEVICE_EMIF_AxCR_ASIZE_SHIFT                      (0)

#define DEVICE_EMIF_AWCC_WAITSTATE_MASK                   (0x000000FF)

#define DEVICE_EMIF_NANDFCR_4BITECC_SEL_MASK              (0x00000030)
#define DEVICE_EMIF_NANDFCR_4BITECC_SEL_SHIFT              (4)

#define DEVICE_EMIF_NANDFCR_4BITECC_START_MASK            (0x00001000)
#define DEVICE_EMIF_NANDFCR_4BITECC_START_SHIFT           (12)
#define DEVICE_EMIF_NANDFCR_4BITECC_ADD_CALC_START_MASK   (0x00002000)
#define DEVICE_EMIF_NANDFCR_4BITECC_ADD_CALC_START_SHIFT  (13)

#define DEVICE_EMIF_NANDFSR_ECC_STATE_MASK                (0x00000F00)
#define DEVICE_EMIF_NANDFSR_ECC_STATE_SHIFT               (8)
#define DEVICE_EMIF_NANDFSR_ECC_ERRNUM_MASK               (0x00030000)
#define DEVICE_EMIF_NANDFSR_ECC_ERRNUM_SHIFT              (16)


typedef struct _DEVICE_EMIF3A_REGS_
{
  VUint32 ERCSR;
  VUint32 SDRSTAT;
  VUint32 SDCR;
  VUint32 SDRCR;
  VUint32 SDTIMR;
  VUint32 SDTIMR2;
  VUint8 RSVD0[4];
  VUint32 SDRC2R;
  VUint32 PBBPR;
  VUint8 RSVD1[4];
  VUint32 VBCFG1;
  VUint32 VBCFG2;
  VUint8 RSVD2[16];
  VUint32 PERFC1R;
  VUint32 PERFC2R;
  VUint32 PCCR;
  VUint32 PCMRSR;
  VUint32 PCTR;
  VUint8 RSVD3[12];
  VUint32 IODFTGBLCTRL;
  VUint32 IODFTMISRR;
  VUint32 IODFTMISADDRRR;
  VUint32 IODFTMISR1R;
  VUint32 IODFTMISR2R;
  VUint32 IODFTMISR3R;
  VUint8 RSVD4[8];
  VUint32 ASYNCCS2CR;
  VUint32 ASYNCCS3CR;
  VUint32 ASYNCCS4CR;
  VUint32 ASYNCCS5CR;
  VUint8 RSVD5[16];
  VUint32 AWCCR;
  VUint8 RSVD6[28];
  VUint32 IRR;
  VUint32 IMR;
  VUint32 IMSR;
  VUint32 IMCR;
  VUint8 RSVD7[16];
  VUint32 DDRPHYREV;
  VUint32 DDRPHYC1R;
  VUint32 DDRPHYC2R;
  VUint32 DDRPHYC3R;
}
DEVICE_Emif3Regs;

#define EMIF3A ((DEVICE_Emif3Regs*) 0xB0000000u)

#define DEVICE_SDCR_NM_MASK     (0x00004000u)
#define DEIVCE_SDCR_NM_SHIFT    (14)


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

#define UHPI ((DEVICE_UHPIRegs*) 0x01E10000u)

#define DEVICE_HPIC_HPIRST_MASK     (0x00000080u)
#define DEVICE_HPIC_HPIRST_SHIFT    (7)

#define DEVICE_HPIC_HINT_MASK       (0x00000004u)
#define DEVICE_HPIC_HINT_SHIFT      (2)

#define DEVICE_HPIC_DSPINT_MASK     (0x00000002u)
#define DEVICE_HPIC_DSPINT_SHIFT    (1)



// UART Register structure - See sprued9b.pdf for more details.
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
  VUint8  DLL;
  VUint8  RSVD1[3];
  VUint8  DLH;
  VUint8  RSVD2[3];  
  VUint32 PID1;
  VUint32 PID2;
  VUint32 PWREMU_MGMT;
  VUint32 MDR;
}
DEVICE_UartRegs;

#define THR RBR
#define FCR IIR

#define UART0 ((DEVICE_UartRegs*) 0x01C42000)
#define UART1 ((DEVICE_UartRegs*) 0x01D0C000)
#define UART2 ((DEVICE_UartRegs*) 0x01D0D000)

#define DEVICE_UART0_DESIRED_BAUD   (115200)
#define DEVICE_UART0_OVERSAMPLE_CNT (16)

#define DEVICE_UART_DLL_MASK                  (0x000000FFu)
#define DEVICE_UART_DLL_SHIFT                 (0)
#define DEVICE_UART_DLH_MASK                  (0x000000FFu)
#define DEVICE_UART_DLH_SHIFT                 (0)

#define DEVICE_UART_PWREMU_MGMT_URST_MASK     (0x00008000u)
#define DEVICE_UART_PWREMU_MGMT_URST_SHIFT    (15)
#define DEVICE_UART_PWREMU_MGMT_UTRST_MASK    (0x00004000u)
#define DEVICE_UART_PWREMU_MGMT_UTRST_SHIFT   (14)
#define DEVICE_UART_PWREMU_MGMT_URRST_MASK    (0x00002000u)
#define DEVICE_UART_PWREMU_MGMT_URRST_SHIFT   (13)

#define DEVICE_UART_FCR_RXFIFTL_MASK          (0x000000C0u)
#define DEVICE_UART_FCR_RXFIFTL_SHIFT         (6)
#define DEVICE_UART_FCR_DMAMODE1_MASK         (0x00000008u)
#define DEVICE_UART_FCR_DMAMODE1_SHIFT        (3)
#define DEVICE_UART_FCR_TXCLR_MASK            (0x00000004u)
#define DEVICE_UART_FCR_TXCLR_SHIFT           (2)
#define DEVICE_UART_FCR_RXCLR_MASK            (0x00000002u)
#define DEVICE_UART_FCR_RXCLR_SHIFT           (1)
#define DEVICE_UART_FCR_FIFOEN_MASK           (0x00000001u)
#define DEVICE_UART_FCR_FIFOEN_SHIFT          (0)

#define DEVICE_UART_LSR_RXFIFOE_MASK          (0x00000080u)
#define DEVICE_UART_LSR_RXFIFOE_SHIFT         (7)
#define DEVICE_UART_LSR_TEMT_MASK             (0x00000040u)
#define DEVICE_UART_LSR_TEMT_SHIFT            (6)
#define DEVICE_UART_LSR_THRE_MASK             (0x00000020u)
#define DEVICE_UART_LSR_THRE_SHIFT            (5)
#define DEVICE_UART_LSR_BI_MASK               (0x00000010u)
#define DEVICE_UART_LSR_BI_SHIFT              (4)
#define DEVICE_UART_LSR_FE_MASK               (0x00000008u)
#define DEVICE_UART_LSR_FE_SHIFT              (3)
#define DEVICE_UART_LSR_PE_MASK               (0x00000004u)
#define DEVICE_UART_LSR_PE_SHIFT              (2)
#define DEVICE_UART_LSR_OE_MASK               (0x00000002u)
#define DEVICE_UART_LSR_OE_SHIFT              (1)
#define DEVICE_UART_LSR_DR_MASK               (0x00000001u)
#define DEVICE_UART_LSR_DR_SHIFT              (0)






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

#define I2C0 ((DEVICE_I2CRegs*) 0x01C22000u)
#define I2C1 ((DEVICE_I2CRegs*) 0x01E28000u)

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

// SPI Register structure
typedef struct _DEVICE_SPI_REGS_
{
  VUint32 SPIGCR0;
  VUint32 SPIGCR1;
  VUint32 SPIINT0;
  VUint32 SPILVL;
  VUint32 SPIFLG;
  VUint32 SPIPC0;
  VUint32 SPIPC1;
  VUint32 SPIPC2;
  VUint32 SPIPC3;
  VUint32 SPIPC4;
  VUint32 SPIPC5;
  VUint32 SPIPC6;
  VUint32 SPIPC7;
  VUint32 SPIPC8;
  VUint32 SPIDAT0;
  VUint32 SPIDAT1;
  VUint32 SPIBUF;
  VUint32 SPIEMU;
  VUint32 SPIDELAY;
  VUint32 SPIDEF;
  VUint32 SPIFMT[4];
  VUint32 TGINTVEC[2];
  VUint32 SPIDUMMY[51];
  VUint32 SPIIOLPBK;
}
DEVICE_SPIRegs;

#define SPI0 ((DEVICE_SPIRegs *) 0x01C41000u)
#define SPI1 ((DEVICE_SPIRegs *) 0x01F0E000u)

#define DEVICE_SPI_SPIGCR1_SPIEN_MASK     (0x01000000u)
#define DEVICE_SPI_SPIGCR1_SPIEN_SHIFT    (24)


// GPIO Register structures
typedef struct _DEVICE_GPIO_BANK_REGS_
{
  VUint16 DIR[2];
  VUint16 OUT_DATA[2];
  VUint16 SET_DATA[2];
  VUint16 CLR_DATA[2];
  VUint16 IN_DATA[2];
  VUint16 SET_RIS_TRIG[2];
  VUint16 CLR_RIS_TRIG[2];
  VUint16 SET_FAL_TRIG[2];
  VUint16 CLR_FAL_TRIG[2];
  VUint16 INTSTAT[2];
}
DEVICE_GPIOBankRegs;

typedef struct _DEVICE_GPIO_REGS_
{
  VUint32 PID;
  VUint32 PCR;
  VUint32 BINTEN;
  VUint8 RSVD0[4];
  DEVICE_GPIOBankRegs BANKPAIR[4];
} DEVICE_GPIORegs;

#define GPIO ((DEVICE_GPIORegs *) 0x01E26000u)

/***********************************************************
* Global Variable Declarations                             *
***********************************************************/


/***********************************************************
* Global Function Declarations                             *
***********************************************************/

// Execute LPSC state transition
extern __FAR__ void DEVICE_LPSCTransition(Uint8 pscnum, Uint8 module, Uint8 domain, Uint8 state);

// Pinmux control function
extern __FAR__ void DEVICE_pinmuxControl(Uint32 regOffset, Uint32 mask, Uint32 value);

// Device boot status functions
extern __FAR__ DEVICE_BootMode      DEVICE_bootMode( void );
extern __FAR__ DEVICE_BusWidth      DEVICE_emifBusWidth( void );
extern __FAR__ DEVICE_SecureType    DEVICE_secureType( void );
extern __FAR__ DEVICE_ChipRevIDType DEVICE_chipRevIDType( void );

// Initialization prototypes
extern __FAR__ Uint32  DEVICE_init(void);
extern __FAR__ Uint32  DEVICE_finalize(void);
extern __FAR__ void    DEVICE_kickUnlock(void); 
extern __FAR__ void    DEVICE_kickLock(void);
extern __FAR__ Uint32  DEVICE_iopuCtl( Uint8 iopuNum, Uint8 mppaNumStart, Uint8 mppaNumEnd, Uint32 value);
extern __FAR__ Uint32  DEVICE_mpuCtl(Uint8 mpuNum, Uint8 regNum, Uint32 startAddr, Uint32 endAddr, Uint32 mppaValue);
extern __FAR__ Uint32  DEVICE_pll0Config(Uint8 clk_src, Uint8 pllm, Uint8 prediv, Uint8 postdiv, Uint8 div1 ,Uint8 div3, Uint8 div7);
extern __FAR__ Uint32  DEVICE_pll1Config(Uint8 pllm,Uint8 postdiv, Uint8 div1 ,Uint8 div2, Uint8 div3);
extern __FAR__ Uint32  DEVICE_DDRConfig(Uint32 ddrphycr, Uint32 sdcr, Uint32 sdtimr, Uint32 sdtimr2, Uint32 sdrcr);

// Cache operations
#if defined(_TMS320C6X)
  extern __FAR__ void DEVICE_CacheBlockWb(DEVICE_CacheType cacheType,Uint32 baseAddr,Uint32 wordCnt,Bool wait);
  extern __FAR__ void DEVICE_CacheBlockWbInv(DEVICE_CacheType cacheType,Uint32 baseAddr,Uint32 wordCnt,Bool wait);
  extern __FAR__ void DEVICE_CacheBlockInv(DEVICE_CacheType cacheType,Uint32 baseAddr,Uint32 wordCnt, Bool wait);
#endif  

/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif // End _DEVICE_H_


