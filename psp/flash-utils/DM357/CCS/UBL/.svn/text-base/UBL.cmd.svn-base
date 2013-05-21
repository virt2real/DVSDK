-e boot

EMIFStart  = 0x02000000;
EMIFSize   = 0x02000000; 
IRAMStart  = 0x00000000;
IRAMSize   = 0x00004000;

DRAMStart  = 0x00008000;
DRAMSize   = 0x00004000;
DDRStart   = 0x80000000;
DDRSize    = 0x10000000;

STACKStart = DRAMStart + DRAMSize;

__selfcopysrc = EMIFStart;
__selfcopydest = DRAMStart + 0x00000020;

MEMORY
{
  ARM_I_IVT       (RX)  : origin = 0x00000000   length = 0x00000020

  UBL_I_SELFCOPY  (RX)  : origin = 0x00000020   length = 0x000000E0
  UBL_I_TEXT      (RX)  : origin = 0x00000100   length = 0x00003300

  UBL_D_SELFCOPY  (RW)  : origin = 0x00008020   length = 0x000000E0
  UBL_D_TEXT      (RW)  : origin = 0x00008100   length = 0x00003300
  UBL_D_DATA      (RW)  : origin = 0x0000B400   length = 0x00000400

  UBL_F_SELFCOPY  (RX)  : origin = 0x02000000   length = 0x000000E0
  UBL_F_TEXT      (R)   : origin = 0x020000E0   length = 0x00003300
  UBL_F_DATA      (R)   : origin = 0x020033E0   length = 0x00000400

  UBL_BSS         (RW)  : origin = 0x0000B800   length = 0x00000400
  UBL_STACK       (RW)  : origin = 0x0000BC00   length = 0x00000400
  UBL_DRAM        (RWX) : origin = 0x80000000   length = 0x10000000
}

SECTIONS
{
  
  .selfcopy : load=UBL_F_SELFCOPY
  {
    *(.selfcopy)
    . = align(4);
  } 
  
  .text : load = UBL_F_TEXT, run = UBL_I_TEXT, LOAD_START(FLASHTEXTStart), LOAD_SIZE(FLASHTEXTSize)
  {
    *(.boot) 
    . = align(4);
    *(.text)
    . = align(4);
  }    

  .data : load = UBL_F_DATA, run = UBL_D_DATA, LOAD_START(FLASHDATAStart), LOAD_SIZE(FLASHDATASize), LOAD_END(__selfcopysrcend), FILL=0xFF
  {
    *(.const)
    . += 4; /* dummy hole creation so load_start and load_size resolve correctly */
    . = align(4);
  }

  .bss :
  {
    *(.bss)
    . = align(4);
  } > UBL_BSS
  
  .ddr_mem :
  {
    . += 0x10000000;
  } run = UBL_DRAM, type=DSECT, RUN_START(EXTERNAL_RAM_START), RUN_END(EXTERNAL_RAM_END)
   
}

