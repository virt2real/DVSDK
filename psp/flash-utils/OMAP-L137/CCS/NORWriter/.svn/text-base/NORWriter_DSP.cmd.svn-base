-lrts64plus.lib
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

  .aemif_mem
  {
    . += 0x1000;
  } load = AEMIF, FILL=0x00000000, type=DSECT, START(_NORStart)
  .ddrram 
  {
    . += 0x1000;
  } load = DRAM, FILL=0x00000000, type=DSECT, START(_DDRStart)
  .extram 
  {
    . += 0x04000000;
  } load = DRAM, FILL=0x00000000, type=DSECT, START(_EXTERNAL_RAM_START), END(_EXTERNAL_RAM_END), SIZE(_EXTERNAL_RAM_SIZE)
}