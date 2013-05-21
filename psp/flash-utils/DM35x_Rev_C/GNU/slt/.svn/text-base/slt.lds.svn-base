/*
 *  Desc: Linker command file slt application program.
 *  Auth: Daniel Allred
 */

ENTRY(boot)
SECTIONS 
{  
  EMIFStart  = 0x02000000;
  EMIFSize   = 0x02000000; 
  IRAMStart  = 0x00000000;
  IRAMSize   = 0x00008000;
  
  DRAMStart  = 0x00010000;
  DRAMSize   = 0x00008000;
  DDRStart   = 0x80000000;
  DDRSize    = 0x10000000;
  EXTERNAL_RAM_START = 0x80000000;
  EXTERNAL_RAM_END   = EXTERNAL_RAM_START + DDRSize;  
  
  STACKStart = DRAMStart + DRAMSize;
  
  . = EMIFStart;
  __selfcopysrc = EMIFStart;
  __selfcopydest = DRAMStart + 0x00000020;
  
  /* Self copy code is in first 256-32=224 bytes of image */
  .selfcopy : AT (0x0)
  {
    *(.selfcopy)    
    . = 0xE0;
  }

  /* The entry point address is fixed at 0x100 */
  . = 0x100;
  .boot    : AT ( LOADADDR(.selfcopy) + SIZEOF(.selfcopy))
  {
    *(.boot)
    . = ALIGN(4);
  }
  .text    : AT ( LOADADDR(.boot) + SIZEOF(.boot) )
  {
    *(.text)
    . = ALIGN(4);
  }
  
  /* Move into DRAM for placing const and data sections */
  . += (DRAMStart - IRAMStart);
  .rodata    : AT ( LOADADDR(.text) + SIZEOF(.text) )
  {
    *(.rodata*)
    *(.rodata)
    . = ALIGN(4);
  }  
  .data    : AT ( LOADADDR(.rodata) + SIZEOF(.rodata) )
  {
    *(.data)
    . = ALIGN(4);
  }
      
  __selfcopysrcend = __selfcopysrc + SIZEOF(.selfcopy) +
            SIZEOF(.boot) + SIZEOF(.text) + 
            SIZEOF(.data) + SIZEOF(.rodata);
  
  .bss    :
  {
    *(.bss) *(COMMON)
    . = ALIGN(4);
  }
}

