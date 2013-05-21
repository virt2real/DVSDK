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
   EXTMEM      : origin = 0x83f00000,    len = 0x0ffe00 
   L1DSRAM     : origin = 0x11f04000,    len = 0xc000
}

SECTIONS
{    
    .image       > EXTMEM
    .sysmem      > L1DSRAM
    .const       > EXTMEM
    .cinit       > EXTMEM
    .switch      > EXTMEM
    .stack       > EXTMEM
    .far         > EXTMEM
    .cio         > EXTMEM
}
