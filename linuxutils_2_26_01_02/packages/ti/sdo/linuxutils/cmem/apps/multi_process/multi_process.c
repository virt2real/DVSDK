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
 * multi_process.c
 *
 * This app tries to use CMEM from multiple processes. It takes the number
 * of processes to start as a parameter.
 *
 * Make sure you insert CMEM with enough buffers of the right size (specified
 * by BUFFER_SIZE below). You can also tweak the random time span the processes
 * sleep by changing DELAYSPAN.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <cmem.h>

#define BUFFER_SIZE 1000

#define DELAYSPAN 5.0

int main(int argc, char *argv[])
{
    unsigned int *ptr = NULL;
    pid_t newPid = 0;
    int pid = 0;
    int numProcesses;
    int r;
    int i;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Number of processes to fork>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    numProcesses = atoi(argv[1]);

    for (i=0; i<numProcesses; i++) {
        newPid = fork(); 

        if (newPid == -1) {
            fprintf(stderr, "Failed to fork off new process\n");
            exit(EXIT_FAILURE);
        }
        else if (newPid == 0) {
            pid = i;
            break;
        }

        printf("Forked off process %d\n", newPid);
    }

    if (newPid != 0) {
        printf("Main process exiting\n");
        exit(EXIT_SUCCESS);
    }

    /* First initialize the CMEM module */
    if (CMEM_init() == -1) {
        fprintf(stderr, "Process %d: Failed to initialize CMEM\n", pid);
        exit(EXIT_FAILURE);
    }

    printf("Process %d: CMEM initialized.\n", pid);

    /* First allocate a buffer from the pool that best fits */
    ptr = CMEM_alloc(BUFFER_SIZE, NULL);

    if (ptr == NULL) {
        fprintf(stderr, "Process %d: Failed to allocate buffer of size %d\n",
                pid, BUFFER_SIZE);
        exit(EXIT_FAILURE);
    }

    printf("Process %d: Allocated buffer at %#x\n", pid, (unsigned int) ptr);

    /* Write some data into this buffer */
    for (i=0; i < BUFFER_SIZE / sizeof(int) ; i++) {
        ptr[i] = 0xbeefbeef;
    }

#if 0
    srand(pid * 1024);

    r = 1 + (int) (DELAYSPAN * (rand() / (RAND_MAX + 1.0)));
#else
    r = (pid * 3) + 3;
#endif

    printf("Process %d: Sleeping for %d seconds\n", pid, r);

    sleep(r);

    if (pid % 2) {
        printf("Process %d: Freeing buffer at %#x\n", pid, (unsigned int) ptr);

        if (CMEM_free(ptr, NULL) < 0) {
            fprintf(stderr, "Process %d: Failed to free buffer at %#x\n",
                    pid, (unsigned int) ptr);
        }
    }
    else {
        printf("Process %d: intentionally neglecting to call CMEM_free()\n",
               pid);
    }


    if (pid != 0) {
        printf("Process %d: Exiting CMEM\n", pid);
        if (CMEM_exit() < 0) {
            fprintf(stderr, "Process %d: Failed to finalize the CMEM module\n",
                    pid);
        }
    }
    else {
        printf("Process %d: sleeping 5 ...\n", pid);
        sleep(5);
        printf("Process %d: exiting, intentionally forgetting to call "
               "CMEM_exit()\n", pid);
    }

    exit(EXIT_SUCCESS);
}
/*
 *  @(#) ti.sdo.linuxutils.cmem; 2, 2, 0,142; 11-30-2010 18:31:30; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

 */

