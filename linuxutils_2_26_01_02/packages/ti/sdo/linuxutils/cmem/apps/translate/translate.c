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
 * translate.c
 *
 * Tests the address translation. Inserting CMEM with the following
 * options works on the DVEVM (if mem=120M):
 *
 * insmod cmemk.ko phys_start=0x87800000 phys_end=0x88000000 pools=1x3145728 
 *
 * You should see lots of address translations on screen keeping "even steps"
 * as the increase (same offset).
 */

#include <stdio.h>
#include <stdlib.h>

#include <cmem.h>

#define BUFSIZE 1024 * 1024 * 3

int main(int argc, char *argv[])
{
    unsigned char *ptr, *orig;
    unsigned long physp;
    int i;
    int inc;
    

    /* First initialize the CMEM module */
    if (CMEM_init() == -1) {
        fprintf(stderr, "Failed to initialize CMEM\n");
        exit(EXIT_FAILURE);
    }

    printf("CMEM initialized.\n");

    /* First allocate a buffer from the pool that best fits */
    ptr = CMEM_alloc(BUFSIZE, NULL);

    if (ptr == NULL) {
        fprintf(stderr, "Failed to allocate buffer of size %d\n", BUFSIZE);
        CMEM_exit();
        exit(EXIT_FAILURE);
    }

    printf("Allocated buffer of size %d at virtual address %#x.\n", BUFSIZE,
           (unsigned int) ptr);

    orig = ptr;

    inc = 4096;
    printf("\nUsing inc = %d\n", inc);
    for (i=0; i<BUFSIZE; i+=inc) {
        physp = CMEM_getPhys(ptr);

        if (physp == 0) {
            fprintf(stderr, "Failed to get physical address of %#x\n",
                    (unsigned int) ptr);
            goto cleanup;
        }

        printf("virtual=%#x physical=%#x\n", (unsigned int) ptr,
                                             (unsigned int) physp);

        ptr += inc;
    } 

    ptr = orig;
    inc = 4096 / 2;
    printf("\nUsing inc = %d\n", inc);
    for (i=0; i<BUFSIZE; i+=inc) {
        physp = CMEM_getPhys(ptr);

        if (physp == 0) {
            fprintf(stderr, "Failed to get physical address of %#x\n",
                    (unsigned int) ptr);
            goto cleanup;
        }

        printf("virtual=%#x physical=%#x\n", (unsigned int) ptr,
                                             (unsigned int) physp);

        ptr += inc;
    } 

    ptr = orig;
    inc = 4096 / 3;
    printf("\nUsing inc = %d\n", inc);
    for (i=0; i<BUFSIZE; i+=inc) {
        physp = CMEM_getPhys(ptr);

        if (physp == 0) {
            fprintf(stderr, "Failed to get physical address of %#x\n",
                    (unsigned int) ptr);
            goto cleanup;
        }

        printf("virtual=%#x physical=%#x\n", (unsigned int) ptr,
                                             (unsigned int) physp);

        ptr += inc;
    } 

    ptr = orig;
    inc = 4096 / 4;
    printf("\nUsing inc = %d\n", inc);
    for (i=0; i<BUFSIZE; i+=inc) {
        physp = CMEM_getPhys(ptr);

        if (physp == 0) {
            fprintf(stderr, "Failed to get physical address of %#x\n",
                    (unsigned int) ptr);
            goto cleanup;
        }

        printf("virtual=%#x physical=%#x\n", (unsigned int) ptr,
                                             (unsigned int) physp);

        ptr += inc;
    }
 
cleanup:
    ptr = orig;
    if (CMEM_free(ptr, NULL) < 0) {
        fprintf(stderr, "Failed to free buffer at %#x\n",
                (unsigned int) ptr);
    }

    printf("Successfully freed buffer at %#x.\n", (unsigned int) ptr);

    if (CMEM_exit() < 0) {
        fprintf(stderr, "Failed to finalize the CMEM module\n");
    }

    exit(EXIT_SUCCESS);
}
/*
 *  @(#) ti.sdo.linuxutils.cmem; 2, 2, 0,142; 11-30-2010 18:31:30; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

 */

