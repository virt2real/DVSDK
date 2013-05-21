/*
 * Thread.c
 *
 * Thread interface implementation
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

#include "Thread.h"
#include "dvtbMemory.h"

typedef struct Thread_Object {
	HANDLE      	thrId;
	DWORD       	dwStackSize;
	Thread_RunFxn   fxn;
	IArg         	arg;
	String      	name;
	Int		priority;
	Bool		threadStatus;
} Thread_Object;


/*
 *  ======== Thread_SetPriority ========
 */
Bool
Thread1_setPriority( Thread_Handle handle, Thread_Priority newPri)
{
	Int priority;
	Bool retVal = FALSE;

	switch(newPri)
	{
		case Thread_Priority_LOWEST:
		     priority = 253;
		     break;

		case Thread_Priority_BELOW_NORMAL:
		     priority = 252;
		     break;

		case Thread_Priority_NORMAL:
		     priority = 251;
		     break;

		case Thread_Priority_ABOVE_NORMAL:
		     priority = 250;
		     break;

		case Thread_Priority_HIGHEST:
		     priority = 248;
		     break;

		case Thread_Priority_INVALID:
		     priority = -1;
		     break;
	}
	if(priority != -1)
	{
		handle->priority = priority;
		SetThreadPriority(handle->thrId, priority);
		retVal = TRUE;
	}
	else
		handle->priority = -1;

	return retVal;
}

/*
 *  ======== Thread_Params_init ========
 */
Void
Thread1_Params_init(Thread_Params *prms)
{
    prms->name = NULL;
    prms->arg = 0;
    prms->tls = NULL;
    prms->osPriority = Thread_INVALID_PRIORITY;
    prms->priority = Thread_Priority_NORMAL;
    prms->stackSize = 1024;
}

/*
 *  ======== Thread_create ========
 */
Thread_Handle
Thread1_create(Thread_RunFxn fxn, Thread_Params* params)
{
	Thread_Handle handle = NULL;

	if(DVEVM_ST_FAIL == dvtb_allocSingleBufCmem((char **)&handle,sizeof (Thread_Object)))
	{
		handle = NULL;
		SYS_ERROR("Unable to allocate memory for handle \n");
	}
	else
	{
		handle->fxn = fxn;
		handle->arg = params->arg;
		handle->name = params->name;

		handle->thrId = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)handle->fxn, (LPVOID)params->arg,CREATE_SUSPENDED, NULL);

		if(handle->thrId)
		{
			handle->threadStatus = TRUE; //Success
			Thread1_setPriority(handle, params->priority);
			ResumeThread(handle->thrId);
		}
		else
		{
			handle->threadStatus = FALSE; //fail
			dvtb_freeSingleBufCmem((char *)handle, sizeof (Thread_Object));
			handle = NULL;
			SYS_ERROR("CreateThread fails\n");
		}
	}

	return handle;
}

/*
 *  ======== Thread_delete ========
 */
Void
Thread1_delete(Thread_Handle *handle)
{

	if(NULL != handle)
	{
		if(TRUE == (*handle)->threadStatus)
		{
			// terminating thread.
			TerminateThread((*handle)->thrId, 0);

			// Wait until the object indicated by the handle closes
			Thread1_join(*handle);
		}
		dvtb_freeSingleBufCmem((char *)(*handle), sizeof (Thread_Object));
		*handle = NULL;
	}
}


/*
 *  ======== Thread_join ========
 */
Bool
Thread1_join(Thread_Handle handle)
{
	Bool retval = TRUE;
	DWORD error;

	// Wait until the object indicated by the handle closes
	error = WaitForSingleObject(handle->thrId, INFINITE);

	switch (error)
	{
		case WAIT_OBJECT_0:
		     retval = TRUE;
		     break;

		case WAIT_TIMEOUT:
		     retval = FALSE;
		     break;

		case WAIT_FAILED:
            	     retval = FALSE;
		     break;

		default:
		     retval = -1 ;
		     break;
	}

	return retval;
}

/*
 *  ======== Thread_sleep ========
 */
Bool
Thread1_sleep( UInt timeout )
{
	Int milliSeconds = timeout/1000;

	Sleep(milliSeconds);
	return TRUE;
}
