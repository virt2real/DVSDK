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
/*
   L1DSRAM     : origin = 0x10f04000,  len = 0xc000
   EXTMEM      : origin = 0xE0000000,  len = 0x10000000
*/
   L1DSRAM     : origin = 0x00f04000,  len = 0xc000
   EXTMEM      : origin = 0xE0000000,  len = 0x10000000
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
    .bss      {} > EXTMEM
}
