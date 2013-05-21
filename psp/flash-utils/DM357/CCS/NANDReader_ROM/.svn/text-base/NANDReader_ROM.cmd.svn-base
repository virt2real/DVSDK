-stack          0x00008000 /* Stack Size */  
-heap           0x00008000 /* Heap Size */

MEMORY
{
  DRAM        : origin=0x80000000 length=0x0E000000 /* DDR RAM */
  DRAM_PROG   : origin=0x8E000000 length=0x01000000 /* DDR for program */
  AEMIF       : origin=0x02000000 length=0x01000000 /* AEMIF CS2 region */
  ARM_IRAM    : origin=0x00008020 length=0x00003CE0 /* ARM internal RAM */
  STACK       : origin=0x0000BD00 length=0x00000300 /* ARM stack */
}

SECTIONS
{
  .boot       > ARM_IRAM
  .text       > ARM_IRAM
  .const      > ARM_IRAM
  .bss        > ARM_IRAM
  .stack      > ARM_IRAM
  .data       > ARM_IRAM
  .nandbuff   > ARM_IRAM
  .ddr_mem    > DRAM,START(DDRStart)
  .aemif_mem  > AEMIF,START(EMIFStart)
  .stack      > STACK,START(STACKStart)
}