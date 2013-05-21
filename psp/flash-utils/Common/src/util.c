/* --------------------------------------------------------------------------
  FILE        : util.c                                                   
  PURPOSE     : Utility and misc. file
  PROJECT     : Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : Utility functions for flashing applications
 ----------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// This module's header file
#include "util.h"

// Device specific CSL
#include "device.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern __FAR__ Uint32 EXTERNAL_RAM_START, EXTERNAL_RAM_END;


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static Uint32 LOCAL_reflectNum(Uint32 inVal, Uint32 num);
static Uint8 LOCAL_CalcBitWiseParity(Uint8 val, Uint8 mask);


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

// Global memory allocation pointer
static VUint32 currMemPtr;


/************************************************************
* Global Function Definitions                               *
************************************************************/

// DDR Memory allocation routines (for storing large data)
void *UTIL_getCurrMemPtr(void)
{
  return ((void *)currMemPtr);
}

// Setup for an adhoc heap
void UTIL_setCurrMemPtr(void *value)
{
  currMemPtr = (VUint32)value;
}

// Allocate memory from the ad-hoc heap
void *UTIL_allocMem(Uint32 size)
{
  void *cPtr;
  Uint32 size_temp;

  // Ensure word boundaries
  size_temp = ((size + 4) >> 2 ) << 2;
  
  if((currMemPtr + size_temp) > ((Uint32) &EXTERNAL_RAM_END))
  {
    return NULL;
  }

  cPtr = (void *) (((Uint32) &EXTERNAL_RAM_START) + currMemPtr);
  currMemPtr += size_temp;

  return cPtr;
}

// Allocate memory from the ad-hoc heap
void *UTIL_callocMem(Uint32 size)
{
  void *ptr;
  Uint8 *cPtr;
  Uint32 i;

  // Alloc the memory
  ptr = UTIL_allocMem(size);

  // Clear the memory
  for (i=0,cPtr = ptr; i<size; i++)
  {
    cPtr[i] = 0x00;
  }

  return ptr;
}

// Simple wait loop - comes in handy.
void UTIL_waitLoop(Uint32 loopcnt)
{
  Uint32 i;
  for (i = 0; i<loopcnt; i++)
  {
    asm("   NOP");
  }
}

// Accurate n = ((t us * f MHz) - 5) / 1.65 
void UTIL_waitLoopAccurate (Uint32 loopcnt)
{
#if defined(_TMS320C6X)
//  asm ("      SUB     B15, 8, B15     ");                 // Done by compiler 
//  asm ("      STW     A4, *+B15[1]    ");                 // Done by compiler 
  asm ("      STW     B0, *+B15[2]    ");
  asm ("      SUB     A4, 24, A4      ");          // Total cycles taken by this function, with n = 0, including clocks taken to jump to this function 
  asm ("      CMPGT   A4, 0, B0       ");
  asm ("loop:                         ");
  asm (" [B0] B       loop            ");
  asm (" [B0] SUB     A4, 6, A4       ");          // Cycles taken by loop 
  asm ("      CMPGT   A4, 0, B0       ");
  asm ("      NOP     3               ");
  asm ("      LDW     *+B15[2], B0    ");
//  asm ("      B       B3              ");                 // Done by compiler 
//  asm ("      ADD     B15, 8, B15     ");                 // Done by compiler 
//  asm ("      NOP     4     
#elif defined(_TMS320C5XX) || defined(__TMS320C55X__)
  UTIL_waitLoop(loopcnt);
#elif defined(_TMS320C28X)
  UTIL_waitLoop(loopcnt);
#elif (defined(__TMS470__) || defined(__GNUC__))
  UTIL_waitLoop(loopcnt);
#endif
}

// CRC-32 routine (relflected, init xor val = 0xFFFFFFFF, final xor val = 0xFFFFFFFF)
Uint32 UTIL_calcCRC32(Uint32* lutCRC, Uint8 *data, Uint32 size, Uint32 currCRC)
{
  Uint32 len = size;
  Uint32 crc = currCRC;
  Int32 i;

  // Prepare input to get back into calculation state ( this means initial
  // input when starting fresh should be 0x00000000 )
  crc = currCRC ^ 0xFFFFFFFF;

  // Perform the algorithm on each byte
  for (i = 0; i < len; i++)
  {
    crc = (crc >> 8) ^ lutCRC[(crc & 0xFF) ^ data[i]];
  }

  // Exclusive OR the result with the specified value
  crc = crc ^ 0XFFFFFFFF;

  return crc;
}

// Function to build a reflected CRC-32 table (for standard CRC-32 algorithm)
// lutCRC must have 1024 bytes (256 32-bit words) available
void UTIL_buildCRC32Table(Uint32* lutCRC, Uint32 poly)
{
  Uint32 i,j,tableLen = 256;
  Uint32 crcAccum;
  
  for (i = 0; i < tableLen; i++)
  {
    crcAccum = LOCAL_reflectNum(i, 8) << (32 - 8);
    for (j = 0; j < 8; j++)
    {
      if ((crcAccum & 0x80000000) != 0x00000000)
      {
        crcAccum = (crcAccum << 1) ^ poly;
      }
      else
      {
        crcAccum = (crcAccum << 1);
      }
      lutCRC[i] = LOCAL_reflectNum(crcAccum, 32);
    }
  }
}

// CRC-16 routine (relflected, init xor val = 0xFFFF, final xor val = 0xFFFF)
Uint16 UTIL_calcCRC16(Uint16* lutCRC, Uint8 *data, Uint32 size, Uint16 currCRC)
{
  Uint32 len = size;
  Uint16 crc = currCRC;
  Int32 i;

  // Prepare input to get back into calculation state ( this means initial
  // input when starting fresh should be 0x00000000 )
  crc = currCRC ^ 0xFFFF;

  // Perform the algorithm on each byte
  for (i = 0; i < len; i++)
  {
    crc = (crc >> 8) ^ lutCRC[(crc & 0xFF) ^ data[i]];
  }

  // Exclusive OR the result with the specified value
  crc = crc ^ 0xFFFF;

  return crc;
}

// Function to build a reflected CRC-16 table (for standard CRC-16 algorithm)
// lutCRC must have 512 bytes (256 16-bit words) available
void UTIL_buildCRC16Table(Uint16* lutCRC, Uint16 poly)
{
  Uint32 i,j,tableLen = 256;
  Uint16 crcAccum;
  
  for (i = 0; i < tableLen; i++)
  {
    crcAccum = (Uint16) LOCAL_reflectNum(i, 8) << (16 - 8);
    for (j = 0; j < 8; j++)
    {
      if ((crcAccum & 0x8000) != 0x0000)
      {
        crcAccum = (crcAccum << 1) ^ poly;
      }
      else
      {
        crcAccum = (crcAccum << 1);
      }
      lutCRC[i] = (Uint16) LOCAL_reflectNum(crcAccum, 16);
    }
  }
}

#if (0)
// This stuff still not done
Uint32 UTIL_hammingECC(Uint8 *data, Uint16 cnt)
{
  Uint16 i, oddResult=0, evenResult=0;
  Uint8 bitParities = 0;
  Uint32 result;
  
  Byte[] byteParities = new Byte[cnt];

  // Create column parities
  for (int i = 0; i < cnt; i++)
    bitParities ^= data[i];

  evenResult |= (Uint16)((((Uint16)LOCAL_calcBitWiseParity(bitParities,0x0F)) << (Uint16)2) |
                 (((Uint16)LOCAL_calcBitWiseParity(bitParities,0x33)) << (Uint16)1) |
                 (((Uint16)LOCAL_calcBitWiseParity(bitParities,0x55)) << (Uint16)0));

  oddResult |= (Uint16) ((((Uint16)LOCAL_calcBitWiseParity(bitParities, 0xF0)) << (Uint16)2) |
                 (((Uint16)LOCAL_calcBitWiseParity(bitParities, 0xCC)) << (Uint16)1) |
                 (((Uint16)LOCAL_calcBitWiseParity(bitParities, 0xAA)) << (Uint16)0));

  // Create row Parities
  for (int i = 0; i < cnt; i++)
      byteParities[i] = LOCAL_calcBitWiseParity(data[i],0xFF);

  // Place even row parity bits
  for (int i = 0; i < Math.Log(cnt,2); i++ )
  {
      Byte val = CalcRowParityBits(byteParities,true,(UInt32)Math.Pow(2,i));
      evenResult |= (Uint16) (val << (3 + i));

      val = CalcRowParityBits(byteParities, false, (UInt32)Math.Pow(2, i));
      oddResult |= (Uint16) (val << (3 + i));
  }
  
  result = (UInt32) oddResult;
  result <<= 16;
  result |= (UInt32)evenResult;
  return result;

}
#endif

/***********************************************************
* Local Function Definitions                               *
***********************************************************/
static Uint32 LOCAL_reflectNum(Uint32 inVal, Uint32 num)
{
  Uint32 i,outVal = 0x0;

  for (i = 1; i < (num + 1); i++)
  {
    outVal |= (Uint32)( ((inVal & 0x1)) << (num - i));
    inVal >>= 1;
  }
  return outVal;
}

#if (0) 
static Uint8 LOCAL_calcBitWiseParity(Uint32* bits, Bool isEven, Uint16 chunkSizeInBits, Uint16 lengthInBits)
{
  Uint8 i,result = 0;
  Uint32 bitParities[64];   // Note this limits us to 2048 32-bit word calculations (8K pages)
  
  if (chunkSizeInBits < 32)
  {
    // Create column parities
    for (i=0; i<(lengthInBits >> 5); i++)
      bitParities[0] ^= bits[i];
    bits = bitParities;
  }
  else
    // Create row parities
    for (i=0; i<(lengthInBits >> 5); i++)  // cycle through all input 32-bit words
    {
      Uint32 j;
      Uint8 currBit = (i % 32);
      bitParities[i>>5] &= ~(0x1 << currBit);
      for (j=0; j<32; j++)
      {
        bits[i]
      
      for (j = 0; j < (lengthInBits >> 5); j++)
        bitParities[j] |=
  

  
  for (i = 0; i < (lengthInBits >> chunkSizeInBits); i++)
  {
    if ( (mask & 0x1) != 0)
    {
        result ^= (Uint8)(val & 0x1);
    }
    mask >>= 1;
    val >>= 1;
  }
  return (Uint8)(result & 0x1);
}
#endif

/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
    HISTORY
        v1.00  -  DJA  -  16-Aug-2007
           Initial release 
 ----------------------------------------------------------------------------- */



