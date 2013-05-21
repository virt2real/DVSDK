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

#ifndef _VICP2_H
#define _VICP2_H

/* Indicates RES Not Available */ 
#define RESNA 0xFFFFFFFF 

/* VICP/IMCOP Memory banks (Offsets from the base address) */
/* IMGBUF */
#define IMGBUF_A_FULL_BASE  (unsigned int)0x00000 
                            /* A in full view*/
#define IMGBUF_B_FULL_BASE  (unsigned int)0x01000
                            /* B in full view*/
#define IMGBUF_C_FULL_BASE  (unsigned int)0x02000
                            /* C in full view*/
#define IMGBUF_D_FULL_BASE  (unsigned int)(_VICP2_dm365 ? 0x03000: RESNA)
                            /* D in full view*/
#define IMGBUF_E_FULL_BASE  (unsigned int)(_VICP2_dm365 ? 0x04000: RESNA) 
                            /* E in full view*/
/* IMX */
#define IMX0COEFFBUF_BASE    (unsigned int)(_VICP2_dm365 ? 0x05000: 0x03000)
                            /* iMX working memory*/
#define IMX0CMDBUF_BASE      (unsigned int)(_VICP2_dm365 ? 0x0D000: 0x05000)
                            /* iMX command memory*/
#define IMX1COEFFBUF_BASE    (unsigned int)(_VICP2_dm365 ? 0x09000: RESNA) 
                            /* iMX working memory*/
#define IMX1CMDBUF_BASE      (unsigned int)(_VICP2_dm365 ? 0x0E000: RESNA) 
                            /* iMX command memory*/
/* baby IMX */
#define BABYIMXCMDBUF_BASE   (unsigned int)(_VICP2_dm355 ? 0x06000: 0x16000)   
#define BABYIMXORIGBUF_BASE  (unsigned int)(_VICP2_dm355 ? 0x06400: 0x16400)   
#define BABYIMXREFBUF_BASE   (unsigned int)(_VICP2_dm355 ? 0x06C00: RESNA)   

/* SEQ */
#define SEQ_PMEM_BASE       (unsigned int)(_VICP2_dm365 ? 0x0F000: RESNA) 
                            /* SEQ prog memory*/

#define QIQMEM_BASE         (unsigned int)(_VICP2_dm365 ? 0x18C00 : RESNA)
#define HUFFMEM_BASE        (unsigned int)(_VICP2_dm365 ? 0x19400 : RESNA)
#define SEQBUF4_BASE        (unsigned int)(_VICP2_dm365 ? 0x1CC00 : RESNA)  

/* Length of the buffers */
#define IMGBUF_A_FULL_LEN  (unsigned int)0x01000
                            /* A in full view*/
#define IMGBUF_B_FULL_LEN  (unsigned int)0x01000
                            /* B in full view*/
#define IMGBUF_C_FULL_LEN  (unsigned int)0x01000
                            /* C in full view*/
#define IMGBUF_D_FULL_LEN  (unsigned int)(_VICP2_dm365 ? 0x01000: 0x0)
                            /* D in full view*/
#define IMGBUF_E_FULL_LEN  (unsigned int)(_VICP2_dm365 ? 0x01000: 0x0) 
                            /* E in full view*/
#define IMX0COEFFBUF_LEN    (unsigned int)(_VICP2_dm365 ? 0x4000: 0x02000)
                            /* iMX working memory*/
#define IMX0CMDBUF_LEN      (unsigned int)0x01000
                            /* iMX command memory*/
#define IMX1COEFFBUF_LEN    (unsigned int)(_VICP2_dm365 ? 0x04000: 0x0) 
                            /* iMX working memory*/
#define IMX1CMDBUF_LEN      (unsigned int)(_VICP2_dm365 ? 0x01000: 0x0) 
                            /* iMX command memory*/
/* baby IMX */
#define BABYIMXCMDBUF_LEN   (unsigned int)0x00400

#define BABYIMXORIGBUF_LEN  (unsigned int)0x00800

#define BABYIMXREFBUF_LEN   (unsigned int)(_VICP2_dm355 ? 0x01C00: 0x0)   

/* SEQ */
#define SEQ_PMEM_LEN       (unsigned int)(_VICP2_dm365 ? 0x01000: 0x0) 
                            /* SEQ prog memory*/

#define QIQMEM_LEN         (unsigned int)(_VICP2_dm365 ? 0x00400 : 0x0)
#define HUFFMEM_LEN        (unsigned int)(_VICP2_dm365 ? 0x01000 : 0x0)
#define SEQBUF4_LEN        (unsigned int)(_VICP2_dm365 ? 0x00800 : 0x0)  


/* Size of BUFFER memory space, this will be allocated to codecs */
#define VICP2_BUFSIZE (_VICP2_dm365 ? 0x1F400 : 0x8800  )

/* Size of REGISTER space that will be memory mapped */
#define VICP2_REGSIZE (_VICP2_dm365 ? 0x20000 : 0x1FF00 )

/* Size of PSC address space */
#define VICP2_PSCSIZE 0x2000 

/* Base address of PSC address space */
#define VICP2_PSCBASE 0x1C40000

/* Address of the DMA view of the IMCOP buffers space */
#define VICP2_DMAVIEWCONFIGBASE 0x11f00000


/* Some DM365 buffers and sizes that will not be used by codecs */  
#define RSVD_REGS_BASE          0x10000
#define RSVD_REGS_LEN           0x06000
#define RSVD_BIMXREF_BASE       0x16C00
#define RSVD_BIMXREF_LEN        0x02000
#define RSVD_PREDMEM_BASE       0x19000
#define RSVD_PREDMEM_LEN        0x00200
#define RSVD_MVMEM_BASE         0x19200
#define RSVD_MVMEM_LEN          0x00200
#define RSVD_SEQBUF1_BASE       0x1A400
#define RSVD_SEQBUF1_LEN        0x01000
#define RSVD_SEQBUF2_BASE       0x1B400
#define RSVD_SEQBUF2_LEN        0x01000
#define RSVD_SEQBUF3_BASE       0x1C400
#define RSVD_SEQBUF3_LEN        0x00800
#define RSVD_SEQDMEM_BASE       0x1F000
#define RSVD_SEQDMEM_LEN        0x00400  

/* Id offset from _VICP2_ipcKeyBase to shared memory containing VICP2 object */
#define _VICP2_SHMID (_VICP2_ipcKeyBase)
 
/* Id offset from _VICP2_ipcKeyBase to semaphore used for critical sections */
#define _VICP2_CSID (_VICP2_ipcKeyBase + 1)
 
/* Id offset from _VICP2_ipcKeyBase to lock used for protecting VICP2 object */
#define _VICP2_LOCKID (_VICP2_ipcKeyBase + 2)

/* Id offset from _VICP2_ipcKeyBase to semaphore used for managing scratch 
   VICP2 memory resources */
#define _VICP2_MEMID (_VICP2_ipcKeyBase + 3)


typedef struct _VICP2_IntObj {
    IRES_VICP2_Obj       resObj;
    unsigned int        configBase;
    Int buffSwitchesOnly[IRES_VICP2_NUMBUFFERS];
    Int numBuffSwitches; 
} _VICP2_IntObj;

extern unsigned int _VICP2_regSize; 

extern unsigned int _VICP2_bufSize;

extern unsigned int _VICP2_buffOffsets[IRES_VICP2_NUMBUFFERS];

extern unsigned int _VICP2_buffLens[IRES_VICP2_NUMBUFFERS];

extern unsigned int _VICP2_imcopConfigBase; 

extern Bool _VICP2_dm355;

extern Bool _VICP2_dm365;

#endif /* _VICP2_H */
/*
 *  @(#) ti.sdo.fc.ires.vicp; 1, 0, 1,177; 12-1-2010 17:25:26; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

