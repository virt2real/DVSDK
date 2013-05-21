/*
 * dvtbMemory.c
 *
 * Memory alloc and free implementation
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include "dvtbMemory.h"

#include <stdio.h>

DvevmStRetCode
dvtb_allocCmemXdm1BufDesc(XDM1_BufDesc *xdmBuf)
{
	int i = 0;
	ASSERT(xdmBuf != NULL);
	ASSERT(xdmBuf->numBufs > 0 && xdmBuf->numBufs <= 16);

	for (i = 0; i < xdmBuf->numBufs; i++)
	{
		if (DVEVM_ST_FAIL == dvtb_allocCmemXdm1SingleBufDesc(&xdmBuf->descs[i]))
		{
			SYS_ERROR("Unable to allocate XDM1_BufDesc buffer\n");
			return DVEVM_ST_FAIL;
		}
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_allocCmemXdm1SingleBufDesc(XDM1_SingleBufDesc *xdmSingleBuf)
{
	ASSERT(xdmSingleBuf != NULL);
	ASSERT(xdmSingleBuf->bufSize > 0);

	if (NULL == (xdmSingleBuf->buf = Memory_contigAlloc(xdmSingleBuf->bufSize, Memory_DEFAULTALIGNMENT)))
	{
		SYS_ERROR("Unable to allocate contiguous XDM1_SingleBufDesc buffer\n");
		return DVEVM_ST_FAIL;
	}

	return DVEVM_ST_SUCCESS;
}


DvevmStRetCode
dvtb_allocCmem(DvevmStXdmBuffer *xdmbuf)
{
	int i = 0;

	ASSERT(xdmbuf != NULL);
	ASSERT(xdmbuf->numBufs > 0);

	// Initialize buffers
	for (i = 0; i < xdmbuf->numBufs; i++)
	{
		xdmbuf->bufs[i] = NULL;
		ASSERT(xdmbuf->bufSizes[i] > 0);
	}

	// Allocate 'numBufs' contiguous buffers
	for (i = 0; i < xdmbuf->numBufs; i++)
	{
		if (NULL == (xdmbuf->bufs[i] = Memory_contigAlloc(xdmbuf->bufSizes[i], Memory_DEFAULTALIGNMENT)))
		{
			SYS_ERROR("Unable to allocate <%d> contiguous buffers\n", xdmbuf->numBufs);
			SYS_ERROR("Failed while allocating %dth buffer\n", i);
			dvtb_freeCmem(xdmbuf);

			return DVEVM_ST_FAIL;
		}		
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_allocSingleBufCmem(char **buf, int bufSize)
{
	if (NULL == (*buf = Memory_contigAlloc(bufSize, Memory_DEFAULTALIGNMENT)))
	{
		SYS_ERROR("Unable to allocate a contiguous buffer of size <%d> \n", bufSize);
		return DVEVM_ST_FAIL;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_freeCmemXdm1BufDesc(XDM1_BufDesc *xdmBuf)
{
	int i = 0;

	ASSERT(xdmBuf != NULL);
	ASSERT(xdmBuf->numBufs > 0);

	for (i = 0; i < xdmBuf->numBufs; i++)
	{
		if (DVEVM_ST_FAIL == dvtb_freeCmemXdm1SingleBufDesc(&xdmBuf->descs[i]))
			return DVEVM_ST_FAIL;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_freeCmemXdm1SingleBufDesc(XDM1_SingleBufDesc *xdmSingleBuf)
{
	ASSERT(xdmSingleBuf != NULL);

	if (xdmSingleBuf->buf != NULL)
	{
		Memory_contigFree(xdmSingleBuf->buf, xdmSingleBuf->bufSize);
		xdmSingleBuf->buf = NULL;
		xdmSingleBuf->bufSize = 0;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_freeCmem(DvevmStXdmBuffer *xdmbuf)
{
	int i = 0;

	ASSERT(xdmbuf != NULL);
	ASSERT(xdmbuf->numBufs > 0);

	for (i = 0; i < xdmbuf->numBufs; i++)
	{
		if (xdmbuf->bufs[i] != NULL)
		{
			Memory_contigFree(xdmbuf->bufs[i], xdmbuf->bufSizes[i]);
			xdmbuf->bufs[i] = NULL;
		}

		xdmbuf->bufSizes[i] = 0;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_freeSingleBufCmem(char *buf, int bufSize)
{
	ASSERT(buf != NULL);
	Memory_contigFree(buf, bufSize);
	buf = NULL;
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_copyXdmBuf(DvevmStXdmBuffer *src, DvevmStXdmBuffer *dst)
{
	int i = 0;

	ASSERT(src != NULL);
	ASSERT(dst != NULL);
	ASSERT(src->numBufs > 0);

	dst->numBufs = src->numBufs;
	for (i = 0; i < src->numBufs; i++)
	{
		dst->bufSizes[i] = src->bufSizes[i];
		dst->bufs[i] = src->bufs[i];
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_allocCmemSingleChunk(DvevmStXdmBuffer *xdmbuf)
{
	int i = 0;
	unsigned int bufSize = 0;

	ASSERT(xdmbuf != NULL);
	ASSERT(xdmbuf->numBufs > 0);

	// Initialize buffers
	for (i = 0; i < xdmbuf->numBufs; i++)
	{
		xdmbuf->bufs[i] = NULL;
		ASSERT(xdmbuf->bufSizes[i] > 0);
		bufSize += xdmbuf->bufSizes[i];
	}

	if (NULL == (xdmbuf->bufs[0] = Memory_contigAlloc(bufSize, Memory_DEFAULTALIGNMENT)))
	{
		SYS_ERROR("Unable to allocate 1st contiguous buffer of size %d\n", bufSize);
		xdmbuf->bufs[0] = NULL;
		return DVEVM_ST_FAIL;
	}	

	// Allocate 'numBufs' contiguous buffers
	for (i = 1; i < xdmbuf->numBufs; i++)
	{
		xdmbuf->bufs[i] = xdmbuf->bufs[i - 1] + xdmbuf->bufSizes[i - 1];
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_freeCmemSingleChunk(DvevmStXdmBuffer *xdmbuf)
{
	int i = 0;
	unsigned int bufSize = 0;

	ASSERT(xdmbuf != NULL);
	ASSERT(xdmbuf->numBufs > 0);

	for (i = 0; i < xdmbuf->numBufs; i++)
	{
		bufSize += xdmbuf->bufSizes[i];
		xdmbuf->bufSizes[i] = 0;
	}

	if (xdmbuf->bufs[0] != NULL)
	{
		Memory_contigFree(xdmbuf->bufs[0], bufSize);
		xdmbuf->bufs[0] = NULL;
	}

	return DVEVM_ST_SUCCESS;
}
