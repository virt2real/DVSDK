-stack          0x00008000 /* Stack Size */  
-heap           0x00008000 /* Heap Size */

MEMORY
{
  DRAM        : origin=0x80000000 length=0x0E000000 /* DDR RAM */
  DRAM_PROG   : origin=0x8E000000 length=0x01000000 /* DDR for program */
  AEMIF       : origin=0x02000000 length=0x01000000 /* AEMIF CS2 region */
}

SECTIONS
{
  .text       > DRAM_PROG
  .const      > DRAM_PROG
  .bss        > DRAM_PROG
  .stack      > DRAM_PROG
  .data       > DRAM_PROG
  .cinit      > DRAM_PROG
  .sysmem     > DRAM_PROG
  .cio        > DRAM_PROG
  .ddr_mem :
  {
    . += 0x0E000000;
  } run = DRAM,type=DSECT, RUN_START(EXTERNAL_RAM_START), RUN_END(EXTERNAL_RAM_END)
  .aemif_mem  > AEMIF,START(EMIFStart)
}