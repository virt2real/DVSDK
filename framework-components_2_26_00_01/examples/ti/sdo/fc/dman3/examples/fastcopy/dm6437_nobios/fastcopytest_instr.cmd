/*
 *  Linker-command file for the fastcopytest application
 */
-x

_FCPY_IFCPY = _FCPY_TI_IFCPY;
_FCPY_IDMA3 = _FCPY_TI_IDMA3;
_DMAN3_EDMA3BASE = 0x01C00000;

-stack 0x1000
-heap 0x2000

--trampolines


-lrts64plus.lib        /* C and C++ run-time library support */

MEMORY {
   CACHE_L1P   : origin = 0x10e00000,  len = 0x8000
   CACHE_L1D   : origin = 0x10f10000,  len = 0x8000
   DDR         : origin = 0x83f00000,  len = 0xffe00
   L1DSRAM     : origin = 0x10f04000,  len = 0xc000
   EXTMEM      : origin = 0x80000000,    len = 0x0ffe00 
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
