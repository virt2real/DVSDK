/*
 *  Linker-command file for the fastcopytest application
 */
-x

_FCPY_IFCPY = _FCPY_TI_IFCPY;
_FCPY_IDMA3 = _FCPY_TI_IDMA3;
_DMAN3_EDMA3BASE = 0x02A00000;

-stack 0x1000
-heap 0x2000

--trampolines


-lrts64plus.lib        /* C and C++ run-time library support */


MEMORY {
   CACHE_L2    : origin = 0xA70000,    len = 0x10000
   CACHE_L1P   : origin = 0xE00000,    len = 0x8000
   CACHE_L1D   : origin = 0x00f06000,  len = 0x2000 
   EXTMEM      : origin = 0xE7A00000,  len = 0x400000 
   L1DSRAM     : origin = 0xF00000,    len = 0x6000
}

SECTIONS
{    
    .image       > EXTMEM
    .sysmem      > L1DSRAM
    .far:     {} > EXTMEM
    .text:    {} > EXTMEM
    .const:   {} > EXTMEM
    .cinit:   {} > EXTMEM
    .stack:   {} > EXTMEM
    .switch:  {} > EXTMEM
    .cio:     {} > EXTMEM
}
