/*************************************************************/
/* edma.h                                                    */
/*   DM350 EDMA API                                          */
/*   ------------------------------------------------------  */
/*   01/26/2006  First release by                            */
/*************************************************************/

#ifndef __EDMA_H__
#define __EDMA_H__

#include "imcop_types.h"

/*********************************************************/
/* Register definitions                                  */
/*********************************************************/
typedef volatile unsigned int *Reg32;
#define EDMA_BASE (0x01c00000)
#define DRAE2	((Reg32)(EDMA_BASE+0x0350))
#define DRAEH2	((Reg32)(EDMA_BASE+0x0354))
#define ER		((Reg32)(EDMA_BASE+0x1000))
#define ERH		((Reg32)(EDMA_BASE+0x1004))
#define ECR     ((Reg32)(EDMA_BASE+0x1008))
#define ECRH    ((Reg32)(EDMA_BASE+0x100C))
#define ESR     ((Reg32)(EDMA_BASE+0x1010))
#define ESRH	((Reg32)(EDMA_BASE+0x1014))
#define CER		((Reg32)(EDMA_BASE+0x1018))
#define CERH	((Reg32)(EDMA_BASE+0x101C))
#define EER		((Reg32)(EDMA_BASE+0x1020))
#define EERH	((Reg32)(EDMA_BASE+0x1024))
#define EECR	((Reg32)(EDMA_BASE+0x1028))
#define EECRH	((Reg32)(EDMA_BASE+0x102C))
#define EESR	((Reg32)(EDMA_BASE+0x1030))
#define EESRH	((Reg32)(EDMA_BASE+0x1034))
#define SECRH	((Reg32)(EDMA_BASE+0x1044))
#define IER		((Reg32)(EDMA_BASE+0x1050))
#define IERH	((Reg32)(EDMA_BASE+0x1054))
#define IECR	((Reg32)(EDMA_BASE+0x1058))
#define IECRH	((Reg32)(EDMA_BASE+0x105C))
#define IESR	((Reg32)(EDMA_BASE+0x1060))
#define IESRH	((Reg32)(EDMA_BASE+0x1064))
#define IPR		((Reg32)(EDMA_BASE+0x1068))
#define IPRH	((Reg32)(EDMA_BASE+0x106C))
#define ICR		((Reg32)(EDMA_BASE+0x1070))
#define ICRH	((Reg32)(EDMA_BASE+0x1074))
#define PARAM_BASE (EDMA_BASE + 0x4000)
#define OPT_OFFSET		(0x0)
#define SRC_OFFSET		(0x4)
#define ACNT_OFFSET		(0x8)
#define BCNT_OFFSET		(0xA)
#define DST_OFFSET		(0xC)
#define SRCBIDX_OFFSET	(0x10)
#define DSTBIDX_OFFSET	(0x12)
#define LINK_OFFSET		(0x14)
#define BCNTRLD_OFFSET	(0x16)
#define SRCCIDX_OFFSET	(0x18)
#define DSTCIDX_OFFSET	(0x1A)
#define CCNT_OFFSET		(0x1C)

/*********************************************************/
/* Macros                                                */
/*********************************************************/
#define EDMA_GetLinkAddress(EntryNo) ((EntryNo)*0x20)
#define EDMA_EnableITCCHEN(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) |= (1<<23))
#define EDMA_DisableITCCHEN(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) &= ~(1<<23))
#define EDMA_EnableTCCHEN(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) |= (1<<22))
#define EDMA_DisableTCCHEN(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) &= ~(1<<22))
#define EDMA_EnableALLTCCHEN(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) |= (3<<22))
#define EDMA_DisableALLTCCHEN(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) &= ~(3<<22))
#define EDMA_EnableITCINTEN(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) |= (1<<21))
#define EDMA_DisableITCINTEN(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) &= ~(1<<21))
#define EDMA_EnableTCINTEN(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) |= (1<<20))
#define EDMA_DisableTCINTEN(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) &= ~(1<<20))
#define EDMA_EnableALLTCINTEN(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) |= (3<<20))
#define EDMA_DisableALLTCINTEN(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) &= ~(3<<20))
#define EDMA_SetTCC(EntryNo, ch) {*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) &= ~0x0003F000; \
                                  *(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) |= (ch&0x3F)<<12;}
#define EDMA_EnableEarlyCompletion(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) |= (1<<11))
#define EDMA_DisableEarlyCompletion(EntryNo)  (*(U32*)(EDMA_GetLinkAddress(EntryNo)+PARAM_BASE) &= ~(1<<11))


/*********************************************************/
/* Type definitions                                      */
/*********************************************************/
typedef enum _SyncType {
    ASync = 0,
    ABSync = 1
} SyncType;

typedef enum _TccMode {
    NormalCompletion = 0,
    EarlyCompletion = 1
} TccMode;

typedef enum _AddrMode {
    IncrementAddr = 0,
    FIFOAddr = 1
} AddrMode;

/* PaRam Option Parameter */
typedef struct _PaRamOption {
    U4 PRIVID;
    BOOL ITCCHEN;
    BOOL TCCHEN;
    BOOL ITCINTEN;
    BOOL TCINTEN;
    U6 TCC;
    TccMode TCCMODE;
    U3 FWID;
    BOOL STATICC;
    SyncType SYNCDIM;
    AddrMode DAM;
    AddrMode SAM;
} PaRamOption;

typedef struct _PaRamSet {
    U32 OPT;
    U32 SRC;
    U16 ACNT;
    U16 BCNT;
    U32 DST;
    S16 SRCBIDX;
    S16 DSTBIDX;
    U16 BCNTRLD;
    U16 LINK;
    S16 SRCCIDX;
    S16 DSTCIDX;
    U16 CCNT;
} PaRamSet;

/* option constants */
typedef enum _PaRamOptionConst {
    OPT_PRVID = (0xF << 24),
    OPT_ITCCHEN = (0x1 << 23),
    OPT_TCCHEN = (0x1 << 22),
    OPT_ITCINTEN = (0x1 << 21),
    OPT_TCINTEN = (0x1 << 20),
    OPT_TCC = (0x3F << 12),
    OPT_TCCMODE = (0x1 << 11),
    OPT_FWID = (0x7 << 8),
    OPT_STATIC = (0x1 << 3),
    OPT_SYNCDIM = (0x1 << 2),
    OPT_DAM = (0x1 << 1),
    OPT_SAM = (0x1 << 0)
} PaRamOptionConst;

/* event number */
typedef enum _DM350_EDMA_Event {
    TIMER3_TINT6 = 0,
    TIMER3_TINT7 = 1,
    McBSP0_XEVT = 2,
    McBSP0_REVT = 3,
    VPSS_EVT1 = 4,
    VPSS_EVT2 = 5,
    VPSS_EVT3 = 6,
    VPSS_EVT4 = 7,
    McBSP1_XEVT = 8,
    TIMER2_TINT4 = 8,
    McBSP1_REVT = 9,
    TIMER2_TINT5 = 9,
    SPI2_SPI2XEVT = 10,
    SPI2_SPI2REVT = 11,
    IMCOP_IMXINT = 12,
    IMCOP_SEQINT = 13,
    SPI1_SPI1XEVT = 14,
    SPI1_SPI1REVT = 15,
    SPI0_SPI0XEVT = 16,
    SPI0_SPI0REVT = 17,
    UART0_URXEVT0 = 18,
    UART0_UTXEVT0 = 19,
    UART1_URXEVT1 = 20,
    UART1_UTXEVT1 = 21,
    UART2_URXEVT2 = 22,
    UART2_UTXEVT2 = 23,
    RTOINT = 24,
    GPIO_GPINT9 = 25,
    MMC0RXEVT = 26,
    MEMSTK_MSEVT = 26,
    MMC0TXEVT = 27,
    I2C_ICREVT = 28,
    I2C_ICXEVT = 29,
    MMC1RXEVT = 30,
    MMC1TXEVT = 31,
    GPIO_GPINT0 = 32,
    GPIO_GPINT1 = 33,
    GPIO_GPINT2 = 34,
    GPIO_GPINT3 = 35,
    GPIO_GPINT4 = 36,
    GPIO_GPINT5 = 37,
    GPIO_GPINT6 = 38,
    GPIO_GPINT7 = 39,
    GPIO_GPBNKINT0 = 40,
    GPIO_GPBNKINT1 = 41,
    GPIO_GPBNKINT2 = 42,
    GPIO_GPBNKINT3 = 43,
    GPIO_GPBNKINT4 = 44,
    GPIO_GPBNKINT5 = 45,
    GPIO_GPBNKINT6 = 46,
    GPIO_GPINT8 = 47,
    TIMER0_TINT0 = 48,
    TIMER0_TINT1 = 49,
    TIMER1_TINT2 = 50,
    TIMER1_TINT3 = 51,
    PWM0 = 52,
    PWM1 = 53,
    PWM2 = 54,
    PWM3 = 55,
    IMCOP_VLCDINT = 56,
    IMCOP_BIMINT = 57,
    IMCOP_DCTINT = 58,
    IMCOP_QIQINT = 59,
    IMCOP_BPSINT = 60,
    IMCOP_VLCDERRINT = 61,
    IMCOP_RCNTINT = 62,
    IMCOP_COPCINT = 63
} DM350_EDMA_Event;


/*********************************************************/
/* Global Functions                                      */
/*********************************************************/
/* Config bus write 32bit */
#if 0
void MP4VDEC_TI_DM350_CFG_Write32(int byteAddress, U32 data);

/* Config bus read 32bit */
U32 MP4VDEC_TI_DM350_CFG_Read32(int byteAddress);

/* Config bus set field 32bit */
void MP4VDEC_TI_DM350_CFG_SetField32(int byteAddress, U32 data);

/* Config bus clear field 32bit */
void MP4VDEC_TI_DM350_CFG_ClearField32(int byteAddress, U32 data);
#endif

/* Make option parameter */
U32 MP4VDEC_TI_DM350_EDMA_MakeOptionParam(PaRamOption * psOpt);

/* Set PaRam set to a PaRam entry */
//void MP4VDEC_TI_DM350_EDMA_SetPaRamEntry(U7 entryNo,
     //                                    PaRamSet * psPaRamSet, MPEG4VDecParam * decParam);

/* Set region 2 (IMCOP region) */
void MP4VDEC_TI_DM350_EDMA_SetRegion2(U6 ch);

#if 0
/* Clear region 2 (IMCOP region) */
void MP4VDEC_TI_DM350_EDMA_ClearRegion2(U6 ch);
#endif
/* Enable Interrupt */
void MP4VDEC_TI_DM350_EDMA_EnableInterrupt(U6 ch);

/* Disable Interrupt */
void MP4VDEC_TI_DM350_EDMA_DisableInterrupt(U6 ch);

/* Clear Interrupt */
void MP4VDEC_TI_DM350_EDMA_ClearInterrupt(U6 ch);

/* Wait Interrupt */
void MP4VDEC_TI_DM350_EDMA_WaitInterrupt(U6 ch);

/* Set event trigger */
void MP4VDEC_TI_DM350_EDMA_SetEvent(U6 ch);

//void MP4VDEC_TI_DM350_CFG_Write32(int byteAddress, U32 data);

#define MP4VDEC_SEQEVENT0_ICR_ADDR      0x1074
#define ICR_ADDR                        ICRH


/* SEQ Event 0 */
#define MP4VDEC_SEQEVENT0_EDMACH0        62
#define MP4VDEC_SEQEVENT0_EDMACH0_ESR    (1<<(MP4VDEC_SEQEVENT0_EDMACH0-32))
#define MP4VDEC_SEQEVENT0_VAL_ADDRL      0x1014

/* EDMA Copy Channel */
#define DM350_EDMA_COPY_ENTRY		(55)
#define DM350_EDMA_COPY_CH			(55)

/* Fill Buffer Event */
#define MP4VDEC_FILLBITSTRMBFR_PING_EDMACH0        33
#define MP4VDEC_FILLBITSTRMBFR_PONG_EDMACH0        34

/* SEQ Event 17 */
#define MP4VDEC_SEQEVENT17_EDMACH0    35
#define MP4VDEC_SEQEVENT17_EDMACH1    36
#define MP4VDEC_SEQEVENT17_EDMACH2    37
#define MP4VDEC_SEQEVENT17_EDMACH0_ESR    (1<<(MP4VDEC_SEQEVENT17_EDMACH0-32))
#define MP4VDEC_SEQEVENT17_EDMACH2_ESR    (1<<(MP4VDEC_SEQEVENT17_EDMACH2-32))
#define MP4VDEC_SEQEVENT17_VAL_ADDRL      0x1014


/* SEQ Event 1 */
#define MP4VDEC_SEQEVENT1_EDMACH0    38
#define MP4VDEC_SEQEVENT1_EDMACH1    39
#define MP4VDEC_SEQEVENT1_EDMACH2    40
#define MP4VDEC_SEQEVENT1_EDMACH0_ESR    (1<<(MP4VDEC_SEQEVENT1_EDMACH0-32))
#define MP4VDEC_SEQEVENT1_VAL_ADDRL      0x1014

/* SEQ Event 2 */
#define MP4VDEC_SEQEVENT2_EDMACH0    63
#define MP4VDEC_SEQEVENT2_EDMACH0_ESR    (1<<31)

#define MP4VDEC_SEQEVENT2_EDMACH1    46 //6
#define MP4VDEC_SEQEVENT2_EDMACH2    47 //20
#define MP4VDEC_SEQEVENT2_EDMACH3    64
#define MP4VDEC_SEQEVENT2_EDMACH4    48 //7
#define MP4VDEC_SEQEVENT2_EDMACH5    65
#define MP4VDEC_SEQEVENT2_EDMACH6    49 //8
#define MP4VDEC_SEQEVENT2_EDMACH7    50 //9
//#define MP4VDEC_SEQEVENT2_EDMACH8    51//4
#define MP4VDEC_SEQEVENT2_EDMACH8    32 //4
#define MP4VDEC_SEQEVENT2_EDMACH9    52 //5
#define MP4VDEC_SEQEVENT2_EDMACH10   66
#define MP4VDEC_SEQEVENT2_EDMACH11   67
#define MP4VDEC_SEQEVENT2_EDMACH12   68
#define MP4VDEC_SEQEVENT2_EDMACH13   53 //23
#define MP4VDEC_SEQEVENT2_EDMACH13_ESR    (1<<(MP4VDEC_SEQEVENT2_EDMACH13-32))
#define MP4VDEC_SEQEVENT2_VAL_ADDRL      0x1014

#define MP4VDEC_SEQEVENT2_EDMACH14   54 //12
#define MP4VDEC_SEQEVENT2_EDMACH15   55 //19
#define MP4VDEC_SEQEVENT2_EDMACH16   69
#define MP4VDEC_SEQEVENT2_EDMACH17   56 //13
#define MP4VDEC_SEQEVENT2_EDMACH18   70
#define MP4VDEC_SEQEVENT2_EDMACH19   57 //14
#define MP4VDEC_SEQEVENT2_EDMACH20   58 //15
#define MP4VDEC_SEQEVENT2_EDMACH21   59 //10
#define MP4VDEC_SEQEVENT2_EDMACH22   71
#define MP4VDEC_SEQEVENT2_EDMACH23   60 //11
#define MP4VDEC_SEQEVENT2_EDMACH24   72
#define MP4VDEC_SEQEVENT2_EDMACH25   61 //27
#define MP4VDEC_SEQEVENT2_EDMACH26   73

/* To link different params for first col. (for buf B) & last col.(for buf C) */

#define MP4VDEC_SEQEVENT2_EDMACH27   74 //for luma
#define MP4VDEC_SEQEVENT2_EDMACH28   75 //for chroma
#define MP4VDEC_SEQEVENT2_EDMACH29   76 //for luma
#define MP4VDEC_SEQEVENT2_EDMACH30   77 //for chroma




/* SEQ Event 3 */
#define MP4VDEC_SEQEVENT3_EDMACH0    41
#define MP4VDEC_SEQEVENT3_EDMACH1    42
#define MP4VDEC_SEQEVENT3_EDMACH2    43
#define MP4VDEC_SEQEVENT3_EDMACH3    44
#define MP4VDEC_SEQEVENT3_EDMACH4    45
#define MP4VDEC_SEQEVENT3_EDMACH2_ESR    (1<<(MP4VDEC_SEQEVENT3_EDMACH2-32))
#define MP4VDEC_SEQEVENT3_EDMACH3_ESR    (1<<(MP4VDEC_SEQEVENT3_EDMACH3-32))
#define MP4VDEC_SEQEVENT3_EDMACH4_ESR    (1<<(MP4VDEC_SEQEVENT3_EDMACH4-32))
#define MP4VDEC_SEQEVENT3_VAL_ADDRL      0x1014



#if 0
extern char *edma_base_addr, *edma_param_base_addr;
extern unsigned int *virt_drae2, *virt_drae2h, *virt_er, *virt_erh,
    *virt_ecr, *virt_ecrh, *virt_esr, *virt_esrh, *virt_cer, *virt_cerh,
    *virt_eer, *virt_eerh, *virt_eecr, *virt_eecrh, *virt_eesr,
    *virt_eesrh, *virt_secr, *virt_secrh, *virt_ier, *virt_ierh,
    *virt_iecr, *virt_iecrh, *virt_iesr, *virt_iesrh, *virt_ipr,
    *virt_iprh, *virt_icr, *virt_icrh, *virt_dmaq4;
#endif


#endif                          // __EDMA_H__
