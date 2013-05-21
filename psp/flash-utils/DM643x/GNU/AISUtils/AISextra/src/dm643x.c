/* --------------------------------------------------------------------------
    FILE        : dm643x_AISExtras.c 				                             	 	        
    PURPOSE     : AIS Extra commands for use in AIS Scripts
    PROJECT     : AIS helper functions
    AUTHOR      : Daniel Allred
    DATE	       : Feb-2-2007
 
    HISTORY
 	     v1.00 completion
 	          Completion - Daniel Allred - 02-Feb-2007
          v1.01
               Revision to separate header files - DJA - 18-Feb-2008
 ----------------------------------------------------------------------------- */

#include "tistdtypes.h"
 
#include "device.h"
 
#include "dm643x.h"

#pragma DATA_SECTION(params,".params");
VUint32 params[32];

#pragma DATA_SECTION(seq,".data:uart");
const Uint8 seq[8] = {0x20,0x20,0x20,0x44,0x4F,0x4E,0x45};

#pragma FUNC_EXT_CALLED(LPSCTransition)
#pragma CODE_SECTION(LPSCTransition,".text")
void LPSCTransition()
{
	VUint32 module = params[0];
	VUint32 state  = params[1];
    while (PSC->PTSTAT & 0x00000001);
	PSC->MDCTL[module] = ((PSC->MDCTL[module]) & (0xFFFFFFE0)) | (state);
	PSC->PTCMD |= 0x00000001;
	while ((PSC->PTSTAT) & 0x00000001);
	while (((PSC->MDSTAT[module]) & 0x1F) != state);	
}

#pragma FUNC_EXT_CALLED(UARTSendDONE)
#pragma CODE_SECTION(UARTSendDONE,".text:uart")
void UARTSendDONE()
{
	Uint32 status,i,len = 8,timeOutCnt = 0;
	#define TIMEOUTMAX (0x01000000)

	for(i=0;i<len;i++)
	{
		/* Enable Timer one time */
		do{
			status = (UART0->LSR)&(0x20);
			timeOutCnt++;
		} while ((!status) && (timeOutCnt < TIMEOUTMAX) );

		if(timeOutCnt == TIMEOUTMAX)		
			return;
		
		// Send byte 
		(UART0->THR) = seq[i];
	}
}

