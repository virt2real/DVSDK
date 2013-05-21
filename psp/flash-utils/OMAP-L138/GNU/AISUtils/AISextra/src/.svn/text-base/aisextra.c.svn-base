/* --------------------------------------------------------------------------
    FILE        : aisxtra.c 				                             	 	        
    PURPOSE     : AIS Extra commands for use in AIS Scripts
    PROJECT     : TI Boot and Flash Utilities
    AUTHOR      : Daniel Allred
 ----------------------------------------------------------------------------- */

#include "tistdtypes.h"
 
#include "device.h"
 
#pragma FUNC_EXT_CALLED(MakeROMEmulatableAndWait)
#pragma CODE_SECTION(MakeROMEmulatableAndWait,".text")
void MakeROMEmulatableAndWait()
{
	VUint32 *mem = (VUint32 *) 0x00800000;
  Uint32 i;
  
  // Unlock taps permanently
  SECURITYCTL->SYSTAPEN = 0xFFFFFFFF;
  
  // Update all L2 memory to be emulatable
  for (i=0; i< 64; i++)
  {
    MPPACTL->L2MPPA[i] |= C6740x_MPPA_EMU;
  }
  
  // Wait loop
  while (mem[0] != 0xDEADBEEF)
  {
  }
	
}

