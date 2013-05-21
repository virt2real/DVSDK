
#ifndef __CSLR_DEVICE_H
#define __CSLR_DEVICE_H

/*********************************************************************
 * Copyright (C) 2003-2004 Texas Instruments Incorporated. 
 * All Rights Reserved 
 *********************************************************************/
 /** \file dm350.h
 * 
 * \brief This file contains the Chip Description for DM350 (ARM side)
 * 
 *********************************************************************/

#include <cslr.h>
#include <tistdtypes.h>

#define   CSL_IDEF_INLINE static

 #include "cslr_edmacc.h"	
 #include "cslr_edmatc0.h"
 #include "cslr_edmatc1.h"
 
 #include "cslr_tmr.h"
 #include "cslr_psc.h"
 #include "cslr_intc1.h"
 
/**************************************************************************\
* Include files for all the modules in the device
\**************************************************************************/
#include "cslr_edmacc_001.h"
#include "cslr_edmatc0_001.h"
#include "cslr_edmatc1_001.h"

#include "cslr_tmr_001.h"
#include "cslr_intc_001.h"

/**************************************************************************\
* Memory Region Descriptions for the device
\**************************************************************************/

/*********************************************************************
 * Memory Interface: AIM
 *********************************************************************/
 /** Memory Region/Memory Space Description for AIM
 *********************************************************************/

/*********************************************************************
 * Memory Space: RAM0
 *********************************************************************/
#define AIM_RAM0_START (0x0)
#define AIM_RAM0_END   (0x3fff)
#define AIM_RAM0_SIZE  (0x4000)

/*********************************************************************
 * Memory Space: RAM1
 *********************************************************************/
#define AIM_RAM1_START (0x4000)
#define AIM_RAM1_END   (0x7fff)
#define AIM_RAM1_SIZE  (0x4000)

/*********************************************************************
 * Memory Space: ROM
 *********************************************************************/
#define AIM_ROM_START (0x8000)
#define AIM_ROM_END   (0x9fff)
#define AIM_ROM_SIZE  (0x2000)

/*********************************************************************
 * Memory Space: DRAM0
 *********************************************************************/
#define AIM_DRAM0_START (0x10000)
#define AIM_DRAM0_END   (0x13fff)
#define AIM_DRAM0_SIZE  (0x4000)

/*********************************************************************
 * Memory Space: DRAM1
 *********************************************************************/
#define AIM_DRAM1_START (0x14000)
#define AIM_DRAM1_END   (0x17fff)
#define AIM_DRAM1_SIZE  (0x4000)

/*********************************************************************
 * Memory Space: DROM
 *********************************************************************/
#define AIM_DROM_START (0x18000)
#define AIM_DROM_END   (0x19fff)
#define AIM_DROM_SIZE  (0x2000)

/*********************************************************************
 * End of Memory Interface: AIM
 *********************************************************************/

/*********************************************************************
 * Memory Interface: ARM
 *********************************************************************/
 /** Memory Region/Memory Space Description for ARM
 *********************************************************************/

/*********************************************************************
 * Memory Space: ETB MEM
 *********************************************************************/
#define ARM_ETBMEM_START (0x1bc0000)
#define ARM_ETBMEM_END   (0x1bc0fff)
#define ARM_ETBMEM_SIZE  (0x1000)

/*********************************************************************
 * Memory Space: ETB REG
 *********************************************************************/
#define ARM_ETB_START (0x1bc1000)
#define ARM_ETB_END   (0x1bc17ff)
#define ARM_ETB_SIZE  (0x800)

/*********************************************************************
 * Memory Space: ARM_ICECRUSH
 *********************************************************************/
#define ARM_ARM_ICECRUSH_START (0x1bc1800)
#define ARM_ARM_ICECRUSH_END   (0x1bc18ff)
#define ARM_ARM_ICECRUSH_SIZE  (0x100)

/*********************************************************************
 * Memory Space: CFG
 *********************************************************************/
#define ARM_CFG_START (0x1c00000)
#define ARM_CFG_END   (0x1ffffff)
#define ARM_CFG_SIZE  (0x400000)

/*********************************************************************
 * Memory Space: AEMIF
 *********************************************************************/
#define ARM_AEMIF_START (0x2000000)
#define ARM_AEMIF_END   (0x9ffffff)
#define ARM_AEMIF_SIZE  (0x8000000)

/*********************************************************************
 * Memory Space: ImCop
 *********************************************************************/
#define ARM_IMCOP_START (0x11f00000)
#define ARM_IMCOP_END   (0x11f1ffff)
#define ARM_IMCOP_SIZE  (0x20000)

/*********************************************************************
 * Memory Space: DDRCTL
 *********************************************************************/
#define ARM_DDRCTL_START (0x20000000)
#define ARM_DDRCTL_END   (0x20007fff)
#define ARM_DDRCTL_SIZE  (0x8000)

/*********************************************************************
 * Memory Space: DDR2
 *********************************************************************/
#define ARM_DDR2_START (0x80000000)
#define ARM_DDR2_END   (0x8fffffff)
#define ARM_DDR2_SIZE  (0x10000000)

/*********************************************************************
 * End of Memory Interface: ARM
 *********************************************************************/

/*********************************************************************
 * Memory Interface: EMIF
 *********************************************************************/
 /** Memory Region/Memory Space Description for EMIF
 *********************************************************************/

/*********************************************************************
 * Memory Space: DDR
 *********************************************************************/
#define EMIF_DDR_START (0x80000000)
#define EMIF_DDR_END   (0x8fffffff)
#define EMIF_DDR_SIZE  (0x10000000)

/*********************************************************************
 * Memory Space: CE0:ASYNC
 *********************************************************************/
#define EMIF_CE0_ASYNC_START (0x2000000)
#define EMIF_CE0_ASYNC_END   (0x3ffffff)
#define EMIF_CE0_ASYNC_SIZE  (0x2000000)

/*********************************************************************
 * Memory Space: CE1:ASYNC
 *********************************************************************/
#define EMIF_CE1_ASYNC_START (0x4000000)
#define EMIF_CE1_ASYNC_END   (0x5ffffff)
#define EMIF_CE1_ASYNC_SIZE  (0x2000000)

/*********************************************************************
 * End of Memory Interface: EMIF
 *********************************************************************/

/**************************************************************************\
* Peripheral Instance counts
\**************************************************************************/
#define CSL_EDMACC_PER_CNT               1                                       
#define CSL_EDMATC0_PER_CNT              1                                       
#define CSL_EDMATC1_PER_CNT              1                                       
#define CSL_UART_PER_CNT                 3                                       
#define CSL_I2C_PER_CNT                  1                                       
#define CSL_TMR_PER_CNT                  4                                       
#define CSL_PWM_PER_CNT                  4                                       
#define CSL_SYS_PER_CNT                  1                                       
#define CSL_PLLC_PER_CNT                 2                                       
#define CSL_PSC_PER_CNT                  1                                       
#define CSL_SYSDFT_PER_CNT               1                                       
#define CSL_ARMINTC_PER_CNT              1                                       
#define CSL_USB_PER_CNT                  1                                       
#define CSL_RTO_PER_CNT                  1                                       
#define CSL_SPI_PER_CNT                  3                                       
#define CSL_GPIO_PER_CNT                 1                                       
#define CSL_VPSSCLK_PER_CNT              1                                       
#define CSL_HSSI_PER_CNT      	         1                                       
#define CSL_H3A_PER_CNT                  1                                       
#define CSL_IPIPEIF_PER_CNT              1                                       
#define CSL_OSD_PER_CNT                  1                                       
#define CSL_VENC_PER_CNT                 1                                       
#define CSL_CCDC_PER_CNT                 1                                       
#define CSL_VPSSBL_PER_CNT               1                                       
#define CSL_CFALD_PER_CNT                1                                       
#define CSL_IPIPE_PER_CNT                1                                       
#define CSL_IMCOP_PER_CNT                1                                       
#define CSL_IMX_PER_CNT                  1  
#define CSL_BIMX_PER_CNT				 1	
#define CSL_DCT_PER_CNT					 1
#define CSL_QIQ_PER_CNT					 1
#define CSL_BP_PER_CNT   				 1 
#define CSL_VLCD_PER_CNT                 1                                       
#define CSL_RC_PER_CNT					 1	
#define CSL_COPC_PER_CNT				 1	
#define CSL_SEQ_PER_CNT                  1                                       
#define CSL_EMIF_PER_CNT                 1                                       
#define CSL_MCBSP_PER_CNT                2                                       
#define CSL_MMCSD_PER_CNT                2                                       
#define CSL_MS_PER_CNT                   1                                       
#define CSL_DDR_PER_CNT                  1                                       

/**************************************************************************\
* Peripheral Base Address
\**************************************************************************/
#define CSL_EDMACC_0_REGS               ((CSL_EdmaccRegsOvly) 0x1c00000) 
#define CSL_EDMATC_0_REGS               ((CSL_Edmatc0RegsOvly) 0x01c10000)   
#define CSL_EDMATC_1_REGS               ((CSL_Edmatc1RegsOvly) 0x01c10400)   
#define CSL_UART_0_REGS                  ((CSL_UartRegsOvly) 0x01c20000)      
#define CSL_UART_1_REGS                  ((CSL_UartRegsOvly) 0x01c20400)      
#define CSL_UART_2_REGS                  ((CSL_UartRegsOvly) 0x01e06000)      
#define CSL_I2C_0_REGS                   ((CSL_I2cRegsOvly) 0x01c21000)       
#define CSL_TMR_0_REGS                   ((CSL_TmrRegsOvly) 0x01c21400)       
#define CSL_TMR_1_REGS                   ((CSL_TmrRegsOvly) 0x01c21800)       
#define CSL_TMR_2_REGS                   ((CSL_TmrRegsOvly) 0x01c21c00)       
#define CSL_TMR_3_REGS                   ((CSL_TmrRegsOvly) 0x01c20800)       
#define CSL_PWM_0_REGS                   ((CSL_PwmRegsOvly) 0x01c22000)       
#define CSL_PWM_1_REGS                   ((CSL_PwmRegsOvly) 0x01c22400)       
#define CSL_PWM_2_REGS                   ((CSL_PwmRegsOvly) 0x01c22800)       
#define CSL_PWM_3_REGS                   ((CSL_PwmRegsOvly) 0x01c22c00)       
#define CSL_SYS_0_REGS                   ((CSL_SysRegsOvly) 0x01c40000)       
#define CSL_PLLC_0_REGS                  ((CSL_PllcRegsOvly) 0x01c40800)      
#define CSL_PLLC_1_REGS                  ((CSL_PllcRegsOvly) 0x01c40c00)      
#define CSL_PSC_0_REGS                   ((CSL_PscRegsOvly) 0x01c41000)       
#define CSL_SYSDFT_0_REGS                ((CSL_SysdftRegsOvly) 0x01c42000)    
#define CSL_INTC1_REGS                   ((CSL_Intc1RegsOvly) 0x01c48000)   
#define CSL_USB_0_REGS                   ((CSL_UsbRegsOvly) 0x01c64000)       
#define CSL_RTO_0_REGS                   ((CSL_RtoRegsOvly) 0x01c20c00)       
#define CSL_SPI_0_REGS                   ((CSL_SpiRegsOvly) 0x01c66000)       
#define CSL_SPI_1_REGS                   ((CSL_SpiRegsOvly) 0x01c66800)       
#define CSL_SPI_2_REGS                   ((CSL_SpiRegsOvly) 0x01c67800)       
#define CSL_GPIO_REGS                    ((CSL_GpioRegsOvly) 0x01c67000)      
#define CSL_VPSSCLK_0_REGS               ((CSL_VpssclkRegsOvly) 0x01c70000)   
#define CSL_HSSI_0_REGS                	 ((CSL_HssiRegsOvly) 0x01c70300)      
#define CSL_H3A_0_REGS                   ((CSL_H3aRegsOvly) 0x01c70080)       
#define CSL_IPIPEIF_0_REGS               ((CSL_IpipeifRegsOvly) 0x01c70100)     
#define CSL_OSD_0_REGS                   ((CSL_OsdRegsOvly) 0x01c70200)       
#define CSL_VENC_0_REGS                  ((CSL_VencRegsOvly) 0x01c70400)      
#define CSL_CCDC_0_REGS                  ((CSL_CcdcRegsOvly) 0x01c70600)      
#define CSL_VPSSBL_0_REGS                ((CSL_VpssblRegsOvly) 0x01c70800)   
#define CSL_CFALD_0_REGS                 ((CSL_CfaldRegsOvly) 0x01c70900)     
#define CSL_IPIPE_0_REGS                 ((CSL_IpipeRegsOvly) 0x01c71000)       
#define CSL_IMCOP_0_REGS                 ((CSL_ImcopRegsOvly) 0x01cc0000)     
#define CSL_IMX_0_REGS                   ((CSL_ImxRegsOvly) 0x01cd0000) 
#define CSL_BIMX_0_REGS                  ((CSL_BimxRegsOvly) 0x01cd0080)
#define CSL_DCT_0_REGS					 ((CSL_DctRegs0vly) 0x01cd0100)
#define CSL_QIQ_0_REGS					 ((CSL_QiqRegs0vly) 0x01cd0180)
#define CSL_BP_0_REGS					 ((CSL_BpRegs0vly) 0x01cd0200)
#define CSL_VLCD_0_REGS                  ((CSL_VlcdRegsOvly) 0x01cd0280)
#define CSL_RC_0_REGS                  	 ((CSL_RcRegsOvly) 0x01cd0300)
#define CSL_COPC_0_REGS                  ((CSL_CopcRegsOvly) 0x01cd0380)
#define CSL_SEQ_0_REGS                   ((CSL_SeqRegsOvly) 0x01cdff00)       
#define CSL_EMIF_0_REGS                  ((CSL_EmifRegsOvly) 0x01e10000)      
#define CSL_MCBSP_0_REGS                 ((CSL_McbspRegsOvly) 0x01e02000)     
#define CSL_MCBSP_1_REGS                 ((CSL_McbspRegsOvly) 0x01e04000)     
#define CSL_MMCSD_0_REGS                 ((CSL_MmcsdRegsOvly) 0x01e11000)     
#define CSL_MMCSD_1_REGS                 ((CSL_MmcsdRegsOvly) 0x01e00000)     
#define CSL_MS_0_REGS                    ((CSL_MsRegsOvly) 0x01e20000)        
#define CSL_DDR_0_REGS                   ((CSL_DdrRegsOvly) 0x20000000)       

/** \brief CCDC Module Instances
* 
*/
typedef enum {
  CSL_CCDC_ANY    = -1, /**< <b>: Any instance of CCDC module</b> */
  CSL_CCDC_0      =  0  /**< <b>: CCDC Instance 0</b> */
} CSL_CcdcNum;

/** \brief H3A Module Instances
* 
*/
typedef enum {
  CSL_H3A_ANY    = -1, /**< <b>: Any instance of H3A module</b> */
  CSL_H3A_0      =  0  /**< <b>: H3A Instance 0</b> */
} CSL_H3aNum;

/** \brief IPIPEIF Module Instances
* 
*/
typedef enum {
  CSL_IPIPEIF_ANY    = -1, /**< <b>: Any instance of IPIPEIF module</b> */
  CSL_IPIPEIF_0      =  0  /**< <b>: IPIPEIF Instance 0</b> */
} CSL_IpipeifNum;

/** \brief IMCOP Module Instances
* 
*/
typedef enum {
  CSL_IMCOP_ANY    = -1, /**< <b>: Any instance of IMCOP module</b> */
  CSL_IMCOP_0      =  0  /**< <b>: IMCOP Instance 0</b> */
} CSL_ImcopNum;

/** \brief IMX Module Instances
* 
*/
typedef enum {
  CSL_IMX_ANY    = -1, /**< <b>: Any instance of IMX module</b> */
  CSL_IMX_0      =  0  /**< <b>: IMX Instance 0</b> */
} CSL_ImxNum;

/** \brief OSD Module Instances
* 
*/
typedef enum {
  CSL_OSD_ANY    = -1, /**< <b>: Any instance of OSD module</b> */
  CSL_OSD_0      =  0  /**< <b>: OSD Instance 0</b> */
} CSL_OsdNum;

/** \brief IPIPE Module Instances
* 
*/
typedef enum {
  CSL_IPIPE_ANY    = -1, /**< <b>: Any instance of IPIPE module</b> */
  CSL_IPIPE_0      =  0  /**< <b>: IPIPE Instance 0</b> */
} CSL_IpipeNum;


/** \brief SEQ Module Instances
* 
*/
typedef enum {
  CSL_SEQ_ANY    = -1, /**< <b>: Any instance of SEQ module</b> */
  CSL_SEQ_0      =  0  /**< <b>: SEQ Instance 0</b> */
} CSL_SeqNum;



typedef enum {
  CSL_HSSI_ANY    = -1, /**< <b>: Any instance of HSSI module</b> */ 
  CSL_HSSI_0      =  0  /**< <b>: HSSI Instance 0</b> */
} CSL_HssiNum;


/** \brief VENC Module Instances
* 
*/
typedef enum {
  CSL_VENC_ANY    = -1, /**< <b>: Any instance of VENC module</b> */
  CSL_VENC_0      =  0  /**< <b>: VENC Instance 0</b> */
} CSL_VencNum;


/** \brief CFALD Module Instances
* 
*/
typedef enum {
  CSL_CFALD_ANY    = -1, /**< <b>: Any instance of CFALD module</b> */
  CSL_CFALD_0      =  0  /**< <b>: CFALD Instance 0</b> */
} CSL_CFALDNum;


/** \brief VLCD Module Instances
* 
*/
typedef enum {
  CSL_VLCD_ANY    = -1, /**< <b>: Any instance of VLCD module</b> */
  CSL_VLCD_0      =  0  /**< <b>: VLCD Instance 0</b> */
} CSL_VlcdNum;


/** \brief VPSSBL Module Instances
* 
*/
typedef enum {
  CSL_VPSSBL_ANY    = -1, /**< <b>: Any instance of VPSSBL module</b> */
  CSL_VPSSBL_0      =  0  /**< <b>: VPSSBL Instance 0</b> */
} CSL_VpssblNum;

/** \brief VPSSCLK Module Instances
* 
*/
typedef enum {
  CSL_VPSSCLK_ANY    = -1, /**< <b>: Any instance of VPSSCLK module</b> */
  CSL_VPSSCLK_0      =  0  /**< <b>: VPSCLK Instance 0</b> */
} CSL_VpssclkNum;

/** \brief VPSS Module Instances
* 
*/
typedef enum {
  CSL_VPSS_ANY    = -1, /**< <b>: Any instance of VPSS module</b> */
  CSL_VPSS_0      =  0  /**< <b>: VPSS Instance 0</b> */
} CSL_VpssNum;


#endif


/* Rev.No.   Date/Time                         Modifier              */
/* -------   ---------                         --------              */
/* 01        09 Nov 2005 18:32:22              x0029935              */
/*                                                                   */
/* Added enum values for dm350 modules and changed the name of       */ 
/* Module level csl files like cslr_uart_001.h from cslr_uart_dm350.h*/
/*********************************************************************/
