/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/*
 *  ======== ti/sdo/fc/acpy3/acpy3_qdma.h ========
 *  This header defines hardware QDMA settings used by the
 *  ACPY3 library.
 *
 */

#ifndef ACPY3_QDMA_
#define ACPY3_QDMA_

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/


#define IDMA0_STATUS    ((volatile Uns *)0x01820000)
#define IDMA0_MASK      ((volatile Uns *)0x01820004)
#define IDMA0_SOURCE    ((volatile Uns *)0x01820008)
#define IDMA0_DEST      ((volatile Uns *)0x0182000C)
#define IDMA0_COUNT     ((volatile Uns *)0x01820010)

#define  ACPY3_NUM_QDMA_CHANNELS   4
#define  ACPY3_MAX_QDMA_CHANNELS   8    /* DaVinci has 8; 2430 has 4 */

/* Offsets of EDMA/QDMA peripheral registers from their base address */
#define ACPY3_QCHMAP_OFFSET          0x0200
#define ACPY3_QDMAQNUM_OFFSET        0x0260
#define ACPY3_QUETCMAP_OFFSET        0x0280
#define ACPY3_QUEPRI_OFFSET          0x0284
#define ACPY3_EMR_OFFSET             0x0300
#define ACPY3_EMRH_OFFSET            0x0304
#define ACPY3_EMCR_OFFSET            0x0308
#define ACPY3_EMCRH_OFFSET           0x030C
#define ACPY3_QEMR_OFFSET            0x0310
#define ACPY3_QEMCR_OFFSET           0x0314
#define ACPY3_QRAE0_OFFSET           0x0380
#define ACPY3_QDMA_IPR_OFFSET        0x1068
#define ACPY3_QDMA_IPRH_OFFSET       0x106C
#define ACPY3_QDMA_ICR_OFFSET        0x1070
#define ACPY3_QDMA_ICRH_OFFSET       0x1074
#define ACPY3_QER_OFFSET             0x1080
#define ACPY3_QEER_OFFSET            0x1084
#define ACPY3_QEECR_OFFSET           0x1088
#define ACPY3_QEESR_OFFSET           0x108C
#define ACPY3_QSER_OFFSET            0x1090
#define ACPY3_QSECR_OFFSET           0x1094
#define ACPY3_QDMA_PARAM_OFFSET      0x4000

/*
 * This is the definition of the QDMA/EDMA peripheral registers.
 * They are at a different base depending upon hardware.
 * But the offsets of the particular fields remains the same.
 */
typedef struct ACPY3_QDMA_REG_Str {
  Uns filler1[ACPY3_QCHMAP_OFFSET/sizeof(int)];
  Uns qchMap[ACPY3_MAX_QDMA_CHANNELS];    /* ACPY3_QCHMAP */
  Uns filler2[(ACPY3_QDMAQNUM_OFFSET -
              (ACPY3_QCHMAP_OFFSET + (ACPY3_MAX_QDMA_CHANNELS * sizeof(int))))
              / sizeof(int)];
  Uns qdmaQNum;                           /* ACPY3_QDMAQNUM */
  Uns filler3[(ACPY3_QUETCMAP_OFFSET -
              (ACPY3_QDMAQNUM_OFFSET + sizeof(int))) / sizeof(int)];
  Uns queTcMap;                           /* ACPY3_QUETCMAP */
  Uns quePri;                             /* ACPY3_QUEPRI */
  Uns filler4[(ACPY3_EMR_OFFSET -
              (ACPY3_QUEPRI_OFFSET + sizeof(int))) / sizeof(int)];
  Uns emr;                                /* ACPY3_EMR */
  Uns emrH;                               /* ACPY3_EMRH */
  Uns emcr;                               /* ACPY3_EMCR */
  Uns emcrH;                              /* ACPY3_EMCRH */
  Uns qemr;                               /* ACPY3_QEMR */
  Uns qemcr;                              /* ACPY3_QEMCR */
  Uns filler5[(ACPY3_QRAE0_OFFSET -
              (ACPY3_QEMCR_OFFSET + sizeof(int))) / sizeof(int)];
  Uns qrae0;                              /* ACPY3_QRAE0 */
  Uns filler6[(ACPY3_QDMA_IPR_OFFSET -
              (ACPY3_QRAE0_OFFSET + sizeof(int))) / sizeof(int)];
  Uns ipr;                                /* ACPY3_QDMA_IPR */
  Uns iprH;                               /* ACPY3_QDMA_IPRH */
  Uns icr;                                /* ACPY3_QDMA_ICR */
  Uns icrH;                               /* ACPY3_QDMA_ICRH */
  Uns filler7[(ACPY3_QER_OFFSET -
              (ACPY3_QDMA_ICRH_OFFSET + sizeof(int))) / sizeof(int)];
  Uns qer;                                /* ACPY3_QER */
  Uns qeer;                               /* ACPY3_QEER */
  Uns qeecr;                              /* ACPY3_QEECR */
  Uns qeesr;                              /* ACPY3_QEESR */
  Uns qser;                               /* ACPY3_QSER */
  Uns qsecr;                              /* ACPY3_QSECR */
  Uns filler8[(ACPY3_QDMA_PARAM_OFFSET -
              (ACPY3_QSECR_OFFSET + sizeof(int))) / sizeof(int)];
  Uns paRamBase[1];                       /* ACPY3_QDMA_PARAM_OFFSET */
} ACPY3_QDMA_REG_Str;

/*
 * The value ACPY3_EDMA3BASE should be defined as the offset
 * of the QDMA/EDMA registers at link time.
 */
extern __FAR__ volatile ACPY3_QDMA_REG_Str *ACPY3_EDMA3BASE;

/*
 *  QCHMAP: Queue to channel map register which specifies which parameter
 *  entry in bits 13-5 and the trigger word (which is word 7 in ACPY3
 *  implementation), in bits 4-2.
 */
#define ACPY3_QCHMAP (ACPY3_EDMA3BASE->qchMap)

/*
 *  QDMAQNUM: The QDMA queue number specifies which queue needs to be used
 *  for each of the individual QDMA channels, 4 in the case of Davinci. This
 *  register is defined in Figure 10 of the 3PCC spec.
 */
#define ACPY3_QDMAQNUM (&ACPY3_EDMA3BASE->qdmaQNum)

/*
 *  QUETCMAP: This register is specified in Figure 11 of the 3PCC  spec. In the
 *  case of Davinci there are 2 event queues and 2 TC channels. The default
 *  mapping is TC channel0 to Event Queue 0, etc.
 */
#define ACPY3_QUETCMAP (&ACPY3_EDMA3BASE->queTcMap)

/*
 *  QUEPRI: This register defines the priority for event queue. There are two
 *  event queues for Davinci, and hence two priorities need to be programmed.
 *  A "higher" value for the priority represents a lower priority.
 */
#define ACPY3_QUEPRI (&ACPY3_EDMA3BASE->quePri)

/* Event Missed Register */
#define ACPY3_EMR (&ACPY3_EDMA3BASE->emr)
/* Event Missed Register High */
#define ACPY3_EMRH (&ACPY3_EDMA3BASE->emrH)
/* Event Missed Clear Register */
#define ACPY3_EMCR (&ACPY3_EDMA3BASE->emcr)
/* Event Missed Clear Register High */
#define ACPY3_EMCRH (&ACPY3_EDMA3BASE->emcrH)
/* QDMA Event Missed Register */
#define ACPY3_QEMR (&ACPY3_EDMA3BASE->qemr)
/* QDMA Event Missed Clear Register */
#define ACPY3_QEMCR (&ACPY3_EDMA3BASE->qemcr)

/*
 *  QRAE0: This register represents the QDMA access enable register. This
 *  register needs to be set if the interrupts for specific TCC's is going
 *  to be used. This library uses polling of the interrupt pending register
 *  and hence does not need to set QRAE0.
 */
#define ACPY3_QRAE0 (&ACPY3_EDMA3BASE->qrae0)

/*
 *  QDMA_IPR : This represents the location where upon completion the DMA
 *  hardware posts completion, if the TCC used is one of the lower 32.
 */
#define ACPY3_QDMA_IPR (&ACPY3_EDMA3BASE->ipr)

/*
 *  QDMA_IPRH : This represents the location where upon completion the DMA
 *  hardware posts completion, if the TCC used is one of the upper 32.
 */
#define ACPY3_QDMA_IPRH (&ACPY3_EDMA3BASE->iprH)

/*
 *  QDMA_ICR: This represents the interrupt clear reg. Writing to this
 *  register should clear any corresp. bit in QDMA_IPR.
 */
#define ACPY3_QDMA_ICR (&ACPY3_EDMA3BASE->icr)

/*
 *  QDMA_ICRH: This represents the interrupt clear reg. Writing to this
 *  register should clear any corresp. bit in QDMA_IPRH.
 */
#define ACPY3_QDMA_ICRH (&ACPY3_EDMA3BASE->icrH)

/*
 *  QER: Queue Event register
 */
#define ACPY3_QER (&ACPY3_EDMA3BASE->qer)

/*
 *  QEER: Queue Event Enable register
 */
#define ACPY3_QEER (&ACPY3_EDMA3BASE->qeer)

/*
 *  QEECR: Queue Event Enable Set register is used to enable all the QDMA
 *  channels. To avoid the problem of read modify write seperate set and
 *  clear registers are provided for enabling the QDMA channels.
 */
#define ACPY3_QEECR (&ACPY3_EDMA3BASE->qeecr)

/* QEESR: register enables the individual QDMA channels to be enabled. */
#define ACPY3_QEESR (&ACPY3_EDMA3BASE->qeesr)

/* QDMA Secondary Event Register */
#define ACPY3_QSER (&ACPY3_EDMA3BASE->qser)
/* QDMA Secondary Event Clear Register */
#define ACPY3_QSECR (&ACPY3_EDMA3BASE->qsecr)
/* PaRam Base address */
#define ACPY3_QDMA_PARAM_BASE ((Uns)(&ACPY3_EDMA3BASE->paRamBase))

/*
 *  ======== ACPY3_QDMA_Config ========
 *  The module configuration structure for ACPY3 QDMA implementation.
 *  It is set at design time by the system integrator to adjust the behaviour
 *  of the module to be optimal for its execution environment.
 */
typedef struct ACPY3_QDMA_Config {

    /* Index of PaRam to be used as null PaRam */
    Uns   nullPaRamIndex;

} ACPY3_QDMA_Config;


/*
 *  ======== ACPY3_QDMA ========
 *  Default module configuration structure (defined in acpy3_qdma.c)
 */
extern __FAR__ ACPY3_QDMA_Config ACPY3_QDMA;

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif  /* ACPY3_QDMA_ */


/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

