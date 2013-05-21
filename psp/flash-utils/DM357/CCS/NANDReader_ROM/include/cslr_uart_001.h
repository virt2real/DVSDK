/******************************************************************************/
/*            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION          */ 
/*   Created 2005, (C) Copyright 2005 Texas Instruments.  All rights reserved.*/ 
/*																			  */
/* 	FILE	: cslr_uart_001.h	 				                          	  */
/*  PROJECT	: DaVinci ROM boot-loader 		                                  */
/*  AUTHOR	: Vignesh LA					                                  */
/*  DATE	: April-25-2005                                                   */
/******************************************************************************/

#ifndef _CSLR_UART_1_H_
#define _CSLR_UART_1_H_

#include <tistdtypes.h>

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint32 RBR;
    volatile Uint32 IER;
    volatile Uint32 IIR;
    volatile Uint32 LCR;
    volatile Uint32 MCR;
    volatile Uint32 LSR;
    volatile Uint32 MSR;
    volatile Uint32 SCR;
    volatile Uint8 DLL;
    volatile Uint8 RSVD0[3];
    volatile Uint8 DLH;
    volatile Uint8 RSVD1[3];
    volatile Uint32 PID1;
    volatile Uint32 PID2;
    volatile Uint32 PWREMU_MGMT;
} CSL_UartRegs;

/* Following 2 lines are added due to CSL3.x tools limitations */
#define THR	RBR   /* RBR & THR have same offset */
#define FCR IIR	  /* IIR & FCR have same offset */


/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* RBR */

#define CSL_UART_RBR_DATA_MASK           (0x000000FFu)
#define CSL_UART_RBR_DATA_SHIFT          (0x00000000u)
#define CSL_UART_RBR_DATA_RESETVAL       (0x00000000u)

#define CSL_UART_RBR_RESETVAL            (0x00000000u)

/* THR */

#define CSL_UART_THR_DATA_MASK           (0x000000FFu)
#define CSL_UART_THR_DATA_SHIFT          (0x00000000u)
#define CSL_UART_THR_DATA_RESETVAL       (0x00000000u)

#define CSL_UART_THR_RESETVAL            (0x00000000u)

/* IER */

#define CSL_UART_IER_EDSSI_MASK          (0x00000008u)
#define CSL_UART_IER_EDSSI_SHIFT         (0x00000003u)
#define CSL_UART_IER_EDSSI_RESETVAL      (0x00000000u)
#define CSL_UART_IER_EDSSI_DISABLE       (0x00000000u)
#define CSL_UART_IER_EDSSI_ENABLE        (0x00000001u)

#define CSL_UART_IER_ELSI_MASK           (0x00000004u)
#define CSL_UART_IER_ELSI_SHIFT          (0x00000002u)
#define CSL_UART_IER_ELSI_RESETVAL       (0x00000000u)
#define CSL_UART_IER_ELSI_DISABLE        (0x00000000u)
#define CSL_UART_IER_ELSI_ENABLE         (0x00000001u)

#define CSL_UART_IER_ETBEI_MASK          (0x00000002u)
#define CSL_UART_IER_ETBEI_SHIFT         (0x00000001u)
#define CSL_UART_IER_ETBEI_RESETVAL      (0x00000000u)
#define CSL_UART_IER_ETBEI_DISABLE       (0x00000000u)
#define CSL_UART_IER_ETBEI_ENABLE        (0x00000001u)

#define CSL_UART_IER_ERBI_MASK           (0x00000001u)
#define CSL_UART_IER_ERBI_SHIFT          (0x00000000u)
#define CSL_UART_IER_ERBI_RESETVAL       (0x00000000u)
#define CSL_UART_IER_ERBI_DISABLE        (0x00000000u)
#define CSL_UART_IER_ERBI_ENABLE         (0x00000001u)

#define CSL_UART_IER_RESETVAL            (0x00000000u)

/* IIR */

#define CSL_UART_IIR_FIFOEN_MASK         (0x000000C0u)
#define CSL_UART_IIR_FIFOEN_SHIFT        (0x00000006u)
#define CSL_UART_IIR_FIFOEN_RESETVAL     (0x00000000u)

#define CSL_UART_IIR_INTID_MASK          (0x0000000Eu)
#define CSL_UART_IIR_INTID_SHIFT         (0x00000001u)
#define CSL_UART_IIR_INTID_RESETVAL      (0x00000000u)
#define CSL_UART_IIR_INTID_MODSTAT       (0x00000000u)
#define CSL_UART_IIR_INTID_THRE          (0x00000001u)
#define CSL_UART_IIR_INTID_RDA           (0x00000002u)
#define CSL_UART_IIR_INTID_RLS           (0x00000003u)
#define CSL_UART_IIR_INTID_CTI           (0x00000006u)

#define CSL_UART_IIR_IPEND_MASK          (0x00000001u)
#define CSL_UART_IIR_IPEND_SHIFT         (0x00000000u)
#define CSL_UART_IIR_IPEND_RESETVAL      (0x00000001u)
#define CSL_UART_IIR_IPEND_NONE          (0x00000001u)

#define CSL_UART_IIR_RESETVAL            (0x00000001u)

/* FCR */

#define CSL_UART_FCR_RXFIFTL_MASK        (0x000000C0u)
#define CSL_UART_FCR_RXFIFTL_SHIFT       (0x00000006u)
#define CSL_UART_FCR_RXFIFTL_RESETVAL    (0x00000000u)
#define CSL_UART_FCR_RXFIFTL_CHAR1       (0x00000000u)
#define CSL_UART_FCR_RXFIFTL_CHAR4       (0x00000001u)
#define CSL_UART_FCR_RXFIFTL_CHAR8       (0x00000002u)
#define CSL_UART_FCR_RXFIFTL_CHAR14      (0x00000003u)

#define CSL_UART_FCR_DMAMODE1_MASK       (0x00000008u)
#define CSL_UART_FCR_DMAMODE1_SHIFT      (0x00000003u)
#define CSL_UART_FCR_DMAMODE1_RESETVAL   (0x00000000u)
#define CSL_UART_FCR_DMAMODE1_DISABLE    (0x00000000u)
#define CSL_UART_FCR_DMAMODE1_ENABLE     (0x00000001u)

#define CSL_UART_FCR_TXCLR_MASK          (0x00000004u)
#define CSL_UART_FCR_TXCLR_SHIFT         (0x00000002u)
#define CSL_UART_FCR_TXCLR_RESETVAL      (0x00000000u)
#define CSL_UART_FCR_TXCLR_CLR           (0x00000001u)

#define CSL_UART_FCR_RXCLR_MASK          (0x00000002u)
#define CSL_UART_FCR_RXCLR_SHIFT         (0x00000001u)
#define CSL_UART_FCR_RXCLR_RESETVAL      (0x00000000u)
#define CSL_UART_FCR_RXCLR_CLR           (0x00000001u)

#define CSL_UART_FCR_FIFOEN_MASK         (0x00000001u)
#define CSL_UART_FCR_FIFOEN_SHIFT        (0x00000000u)
#define CSL_UART_FCR_FIFOEN_RESETVAL     (0x00000000u)
#define CSL_UART_FCR_FIFOEN_DISABLE      (0x00000000u)
#define CSL_UART_FCR_FIFOEN_ENABLE       (0x00000001u)

#define CSL_UART_FCR_RESETVAL            (0x00000000u)

/* LCR */

#define CSL_UART_LCR_DLAB_MASK           (0x00000080u)
#define CSL_UART_LCR_DLAB_SHIFT          (0x00000007u)
#define CSL_UART_LCR_DLAB_RESETVAL       (0x00000000u)

#define CSL_UART_LCR_BC_MASK             (0x00000040u)
#define CSL_UART_LCR_BC_SHIFT            (0x00000006u)
#define CSL_UART_LCR_BC_RESETVAL         (0x00000000u)
#define CSL_UART_LCR_BC_DISABLE          (0x00000000u)
#define CSL_UART_LCR_BC_ENABLE           (0x00000001u)

#define CSL_UART_LCR_SP_MASK             (0x00000020u)
#define CSL_UART_LCR_SP_SHIFT            (0x00000005u)
#define CSL_UART_LCR_SP_RESETVAL         (0x00000000u)

#define CSL_UART_LCR_EPS_MASK            (0x00000010u)
#define CSL_UART_LCR_EPS_SHIFT           (0x00000004u)
#define CSL_UART_LCR_EPS_RESETVAL        (0x00000000u)

#define CSL_UART_LCR_PEN_MASK            (0x00000008u)
#define CSL_UART_LCR_PEN_SHIFT           (0x00000003u)
#define CSL_UART_LCR_PEN_RESETVAL        (0x00000000u)

#define CSL_UART_LCR_STB_MASK            (0x00000004u)
#define CSL_UART_LCR_STB_SHIFT           (0x00000002u)
#define CSL_UART_LCR_STB_RESETVAL        (0x00000000u)

#define CSL_UART_LCR_WLS_MASK            (0x00000003u)
#define CSL_UART_LCR_WLS_SHIFT           (0x00000000u)
#define CSL_UART_LCR_WLS_RESETVAL        (0x00000000u)
#define CSL_UART_LCR_WLS_BITS5           (0x00000000u)
#define CSL_UART_LCR_WLS_BITS6           (0x00000001u)
#define CSL_UART_LCR_WLS_BITS7           (0x00000002u)
#define CSL_UART_LCR_WLS_BITS8           (0x00000003u)

#define CSL_UART_LCR_RESETVAL            (0x00000000u)

/* MCR */

#define CSL_UART_MCR_AFE_MASK            (0x00000020u)
#define CSL_UART_MCR_AFE_SHIFT           (0x00000005u)
#define CSL_UART_MCR_AFE_RESETVAL        (0x00000000u)
#define CSL_UART_MCR_AFE_DISABLE         (0x00000000u)
#define CSL_UART_MCR_AFE_ENABLE          (0x00000001u)

#define CSL_UART_MCR_LOOP_MASK           (0x00000010u)
#define CSL_UART_MCR_LOOP_SHIFT          (0x00000004u)
#define CSL_UART_MCR_LOOP_RESETVAL       (0x00000000u)
#define CSL_UART_MCR_LOOP_DISABLE        (0x00000000u)
#define CSL_UART_MCR_LOOP_ENABLE         (0x00000001u)

#define CSL_UART_MCR_OUT2_MASK           (0x00000008u)
#define CSL_UART_MCR_OUT2_SHIFT          (0x00000003u)
#define CSL_UART_MCR_OUT2_RESETVAL       (0x00000000u)
#define CSL_UART_MCR_OUT2_HIGH           (0x00000000u)
#define CSL_UART_MCR_OUT2_LOW            (0x00000001u)

#define CSL_UART_MCR_OUT1_MASK           (0x00000004u)
#define CSL_UART_MCR_OUT1_SHIFT          (0x00000002u)
#define CSL_UART_MCR_OUT1_RESETVAL       (0x00000000u)
#define CSL_UART_MCR_OUT1_HIGH           (0x00000000u)
#define CSL_UART_MCR_OUT1_LOW            (0x00000001u)

#define CSL_UART_MCR_RTS_MASK            (0x00000002u)
#define CSL_UART_MCR_RTS_SHIFT           (0x00000001u)
#define CSL_UART_MCR_RTS_RESETVAL        (0x00000000u)
#define CSL_UART_MCR_RTS_HIGH            (0x00000000u)
#define CSL_UART_MCR_RTS_DISABLE         (0x00000000u)
#define CSL_UART_MCR_RTS_ENABLE          (0x00000001u)
#define CSL_UART_MCR_RTS_LOW             (0x00000001u)

#define CSL_UART_MCR_DTR_MASK            (0x00000001u)
#define CSL_UART_MCR_DTR_SHIFT           (0x00000000u)
#define CSL_UART_MCR_DTR_RESETVAL        (0x00000000u)
#define CSL_UART_MCR_DTR_HIGH            (0x00000000u)
#define CSL_UART_MCR_DTR_LOW             (0x00000001u)

#define CSL_UART_MCR_RESETVAL            (0x00000000u)

/* LSR */

#define CSL_UART_LSR_RXFIFOE_MASK        (0x00000080u)
#define CSL_UART_LSR_RXFIFOE_SHIFT       (0x00000007u)
#define CSL_UART_LSR_RXFIFOE_RESETVAL    (0x00000000u)

#define CSL_UART_LSR_TEMT_MASK           (0x00000040u)
#define CSL_UART_LSR_TEMT_SHIFT          (0x00000006u)
#define CSL_UART_LSR_TEMT_RESETVAL       (0x00000001u)

#define CSL_UART_LSR_THRE_MASK           (0x00000020u)
#define CSL_UART_LSR_THRE_SHIFT          (0x00000005u)
#define CSL_UART_LSR_THRE_RESETVAL       (0x00000001u)

#define CSL_UART_LSR_BI_MASK             (0x00000010u)
#define CSL_UART_LSR_BI_SHIFT            (0x00000004u)
#define CSL_UART_LSR_BI_RESETVAL         (0x00000000u)

#define CSL_UART_LSR_FE_MASK             (0x00000008u)
#define CSL_UART_LSR_FE_SHIFT            (0x00000003u)
#define CSL_UART_LSR_FE_RESETVAL         (0x00000000u)

#define CSL_UART_LSR_PE_MASK             (0x00000004u)
#define CSL_UART_LSR_PE_SHIFT            (0x00000002u)
#define CSL_UART_LSR_PE_RESETVAL         (0x00000000u)

#define CSL_UART_LSR_OE_MASK             (0x00000002u)
#define CSL_UART_LSR_OE_SHIFT            (0x00000001u)
#define CSL_UART_LSR_OE_RESETVAL         (0x00000000u)

#define CSL_UART_LSR_DR_MASK             (0x00000001u)
#define CSL_UART_LSR_DR_SHIFT            (0x00000000u)
#define CSL_UART_LSR_DR_RESETVAL         (0x00000000u)

#define CSL_UART_LSR_RESETVAL            (0x00000060u)

/* MSR */

#define CSL_UART_MSR_CD_MASK             (0x00000080u)
#define CSL_UART_MSR_CD_SHIFT            (0x00000007u)
#define CSL_UART_MSR_CD_RESETVAL         (0x00000000u)

#define CSL_UART_MSR_RI_MASK             (0x00000040u)
#define CSL_UART_MSR_RI_SHIFT            (0x00000006u)
#define CSL_UART_MSR_RI_RESETVAL         (0x00000000u)

#define CSL_UART_MSR_DSR_MASK            (0x00000020u)
#define CSL_UART_MSR_DSR_SHIFT           (0x00000005u)
#define CSL_UART_MSR_DSR_RESETVAL        (0x00000000u)

#define CSL_UART_MSR_CTS_MASK            (0x00000010u)
#define CSL_UART_MSR_CTS_SHIFT           (0x00000004u)
#define CSL_UART_MSR_CTS_RESETVAL        (0x00000000u)

#define CSL_UART_MSR_DCD_MASK            (0x00000008u)
#define CSL_UART_MSR_DCD_SHIFT           (0x00000003u)
#define CSL_UART_MSR_DCD_RESETVAL        (0x00000000u)

#define CSL_UART_MSR_TERI_MASK           (0x00000004u)
#define CSL_UART_MSR_TERI_SHIFT          (0x00000002u)
#define CSL_UART_MSR_TERI_RESETVAL       (0x00000000u)

#define CSL_UART_MSR_DDSR_MASK           (0x00000002u)
#define CSL_UART_MSR_DDSR_SHIFT          (0x00000001u)
#define CSL_UART_MSR_DDSR_RESETVAL       (0x00000000u)

#define CSL_UART_MSR_DCTS_MASK           (0x00000001u)
#define CSL_UART_MSR_DCTS_SHIFT          (0x00000000u)
#define CSL_UART_MSR_DCTS_RESETVAL       (0x00000000u)

#define CSL_UART_MSR_RESETVAL            (0x00000000u)

/* SCR */

#define CSL_UART_SCR_DATA_MASK           (0x000000FFu)
#define CSL_UART_SCR_DATA_SHIFT          (0x00000000u)
#define CSL_UART_SCR_DATA_RESETVAL       (0x00000000u)

#define CSL_UART_SCR_RESETVAL            (0x00000000u)

/* DLL */

#define CSL_UART_DLL_DLL_MASK            (0xFFu)
#define CSL_UART_DLL_DLL_SHIFT           (0x00u)
#define CSL_UART_DLL_DLL_RESETVAL        (0x00u)

#define CSL_UART_DLL_RESETVAL            (0x00u)

/* DLH */

#define CSL_UART_DLH_DLH_MASK            (0xFFu)
#define CSL_UART_DLH_DLH_SHIFT           (0x00u)
#define CSL_UART_DLH_DLH_RESETVAL        (0x00u)

#define CSL_UART_DLH_RESETVAL            (0x00u)

/* PID1 */

#define CSL_UART_PID1_CLS_MASK           (0x0000FF00u)
#define CSL_UART_PID1_CLS_SHIFT          (0x00000008u)
#define CSL_UART_PID1_CLS_RESETVAL       (0x00000001u)

#define CSL_UART_PID1_REV_MASK           (0x000000FFu)
#define CSL_UART_PID1_REV_SHIFT          (0x00000000u)
#define CSL_UART_PID1_REV_RESETVAL       (0x00000001u)

#define CSL_UART_PID1_RESETVAL           (0x00000101u)

/* PID2 */

#define CSL_UART_PID2_TYP_MASK           (0x000000FFu)
#define CSL_UART_PID2_TYP_SHIFT          (0x00000000u)
#define CSL_UART_PID2_TYP_RESETVAL       (0x00000004u)

#define CSL_UART_PID2_RESETVAL           (0x00000004u)

/* PWREMU_MGMT */

#define CSL_UART_PWREMU_MGMT_URST_MASK   (0x00008000u)
#define CSL_UART_PWREMU_MGMT_URST_SHIFT  (0x0000000Fu)
#define CSL_UART_PWREMU_MGMT_URST_RESETVAL (0x00000000u)
#define CSL_UART_PWREMU_MGMT_URST_RESET   (0x00000000u)
#define CSL_UART_PWREMU_MGMT_URST_ENABLE  (0x00000001u)

#define CSL_UART_PWREMU_MGMT_SOFT_MASK   (0x00000002u)
#define CSL_UART_PWREMU_MGMT_SOFT_SHIFT  (0x00000001u)
#define CSL_UART_PWREMU_MGMT_SOFT_RESETVAL (0x00000001u)

#define CSL_UART_PWREMU_MGMT_FREE_MASK   (0x00000001u)
#define CSL_UART_PWREMU_MGMT_FREE_SHIFT  (0x00000000u)
#define CSL_UART_PWREMU_MGMT_FREE_RESETVAL (0x00000000u)
#define CSL_UART_PWREMU_MGMT_FREE_STOP   (0x00000000u)
#define CSL_UART_PWREMU_MGMT_FREE_RUN    (0x00000001u)

#define CSL_UART_PWREMU_MGMT_RESETVAL    (0x00000002u)

#endif
