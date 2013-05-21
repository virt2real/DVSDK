/*
 * SemThread.c
 *
 * Semaphore interface implementation
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

#include "SemThread.h"
#include "dvtbMemory.h"

#define MAXCOUNT 0x1000 /* Maximum semaphore count */

typedef struct SemThread_Object {
    int      count;
    HANDLE   sem;
	String name;
} SemThread_Object;

void
SemThread_Params_init( SemThread_Params *params )
{

}

SemThread_Handle
SemThread_create( int count, const SemThread_Params *params)
{
	SemThread_Object *sem;

	if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem((char **)&sem,sizeof(SemThread_Object)) )
	{
		SYS_ERROR("SemThread_create: Unable to allocate memory \n");
        sem = NULL;
    }
	else
	{
		if (!(sem->sem = CreateSemaphore((LPSECURITY_ATTRIBUTES)NULL, (LONG)count, (LONG)MAXCOUNT, NULL)))
		{
			SYS_ERROR("Sem_create: CreateSemaphore() failed\n");
			dvtb_freeSingleBufCmem((char *)sem, sizeof (SemThread_Object));
			sem = NULL;
		}
		else
		{
			sem->count = count;
			sem->name = params->name;
		}
    }
	return sem;
}

void
SemThread_delete( SemThread_Handle *sem )
{
	if (NULL != sem)
	{
		CloseHandle((*sem)->sem);
		dvtb_freeSingleBufCmem((char *)(*sem), sizeof (SemThread_Object));
		*sem = NULL;
    }
}

int
SemThread_pend( SemThread_Handle sem, unsigned int timeout )
{
	Bool retval = TRUE;

    --sem->count;

	WaitForSingleObject(sem->sem, INFINITE);

	return (retval);
}

int
SemThread_post( SemThread_Handle sem )
{
	Bool retval = TRUE;

	++sem->count;

    ReleaseSemaphore(sem->sem, 1, NULL);

	return (retval);
}



