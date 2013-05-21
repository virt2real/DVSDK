-stack          0x00000800 /* Stack Size */  
-heap           0x00000800 /* Heap Size */

MEMORY
{
  DRAM        org=0xC0000000 len=0x04000000 /* SDRAM */
  SHARED_RAM  org=0x80000000 len=0x00020000 /* DDR for program */
  AEMIF       org=0x60000000 len=0x02000000 /* AEMIF CS2 region */
  AEMIF_CS3   org=0x62000000 len=0x02000000 /* AEMIF CS3 region */
}

SECTIONS
{
  .text :
  {
  } > SHARED_RAM
  .const :
  {
  } > SHARED_RAM
  .bss :
  {
  } > SHARED_RAM
  .far :
  {
  } > SHARED_RAM
  .stack :
  {
  } > SHARED_RAM
  .data :
  {
  } > SHARED_RAM
  .cinit :
  {
  } > SHARED_RAM
  .sysmem :
  {
  } > SHARED_RAM
  .cio :
  {
  } > SHARED_RAM
  .switch :
  {
  } > SHARED_RAM
  .aemif_mem :
  {
  } > AEMIF_CS3, RUN_START(NANDStart)
  .ddr_mem :
  {
    . += 0x0E000000;
  } run = DRAM,type=DSECT, RUN_START(EXTERNAL_RAM_START), RUN_END(EXTERNAL_RAM_END)
}