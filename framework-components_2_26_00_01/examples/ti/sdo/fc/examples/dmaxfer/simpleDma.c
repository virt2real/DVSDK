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
#include <xdc/std.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef xdc_target__os_Linux
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#include <ti/sdo/utils/trace/gt.h>

#include <ti/sdo/fc/memutils/memutils.h>

#define EDMAADDR 0x1C00000

/* Uses Event#/DMA Ch #N, assumes CH#1 mapped to Param #N */
void do1DDma(unsigned int src, unsigned int dst, unsigned int bytes,
        unsigned int edmaChan)
{
    unsigned int * pEdma;
    unsigned int * pParam;
    volatile unsigned int * ipr;

    int i = 0;
    unsigned *src_addr = (unsigned int *)src;
    unsigned *dest_addr = (unsigned int *)dst;
    unsigned int tccNum = (unsigned int)-1;

#ifdef xdc_target__os_Linux
    static int memfd = -1;           //File descriptor for "/dev/mem"

    memfd = open("/dev/mem", O_RDWR | O_SYNC);
    /* Obtain mmapped base address */
    pEdma = (unsigned int* )mmap(0, 0x8000,  PROT_READ | PROT_WRITE, MAP_SHARED,
            memfd, (off_t)EDMAADDR);
#else
    pEdma = (unsigned int* )EDMAADDR;
#endif

    /* 4. DMA from src to dst */
    /* Set param 1 */

    pParam = (unsigned int *)((unsigned int) pEdma + 0x4000 +
            (0x20 * edmaChan)); //param # edmaChan

    tccNum = (edmaChan << 12);

    pParam[0] = (0x00100008 | tccNum); //OPT TCC == edmachan + STATIC
#ifdef xdc_target__os_Linux
    pParam[1] = (unsigned int)MEMUTILS_getPhysicalAddr(src_addr);
#else
    pParam[1] = (unsigned int)src_addr;
#endif
    pParam[2] = 0x00010000 + bytes; //Bcnt, Acnt
#ifdef xdc_target__os_Linux
    pParam[3] = (unsigned int)MEMUTILS_getPhysicalAddr(dest_addr);
#else
    pParam[3] = (unsigned int)dest_addr;
#endif
    pParam[4] = 0x0;
    pParam[5] = 0xFFFF;
    pParam[6] = 0x0;
    pParam[7] = 0x1;

    printf("Param # %d\n", edmaChan);

    for (i = 0; i < 8; i++) {
       printf("0x%x\t",pParam[i]);
    }
    printf("\n");

    /* SECR = 0xFFFFFFFF */
    *((unsigned int *)((unsigned int) pEdma + 0x1040)) = 0xFFFFFFF;
    printf("SER 0x%x\n", *((unsigned int *)((unsigned int) pEdma + 0x1038)));

    /* EESR  = 0x2
    *((unsigned int *)((unsigned int) pEdma + 0x1030)) = (0x01 << edmaChan);
    printf("EER 0x%x\n", *((unsigned int *)((unsigned int) pEdma + 0x1020)));
    */

    /* IESR = 0x02 */
    /*
    *((unsigned int *)((unsigned int) pEdma + 0x1060)) = 0xFFFFFFF;
    printf("IER 0x%x\n", *((unsigned int *)((unsigned int) pEdma + 0x1050)));
    */

    /* ICR */
    *((unsigned int *)((unsigned int) pEdma + 0x1070)) = (0x01 << edmaChan);

    /* DCHMAP */
    *((unsigned int *)((unsigned int) pEdma + 0x100 + (0x4 * edmaChan))) =
            (edmaChan << 4) ;


    ipr = (unsigned int *)((unsigned int)pEdma+ 0x1068);
    printf("IPR Before 0x%x\n", *ipr);

    /* ESR = 0x02 */
    *((unsigned int *)((unsigned int) pEdma + 0x1010)) = (0x01 << edmaChan);

    printf("EER 0x%x\n", *((unsigned int *)((unsigned int) pEdma + 0x1020)));

    /* Check for completion */
    while (((*ipr) & (0x1 << edmaChan))  != (0x01 << edmaChan));
    printf("IPR After 0x%x\n", *ipr);


#ifdef xdc_target__os_Linux
    close(memfd);
#endif
}
/*
 *  @(#) ti.sdo.fc.examples.dmaxfer; 1, 0, 0,30; 12-1-2010 17:24:46; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

