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
 *  ======== node_getPri.c ========
 *  NODE utility function for obtaining the Task Priority for the node.
 *
 */

#include <xdc/std.h>
#include <ti/sdo/ce/osal/Thread.h>
#include <node.h>
#include <_node.h>

/*
 *  ======== NODE_stat ========
 */
Int NODE_stat(NODE_Handle node, NODE_Stat *statBuf)
{
    Int status = 0;

    if (node->self == NULL) {
        statBuf->stackSize = 0;
        statBuf->stackUsed = 0;
    }
    else {
        Thread_Stat buf;

        status = Thread_stat(node->self, &buf);
        statBuf->stackSize = buf.stacksize;
        statBuf->stackUsed = buf.stackused;
    }

    return (status);
}
/*
 *  @(#) ti.sdo.ce.node; 1, 0, 0,427; 12-2-2010 21:24:36; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

