/*
 *  Linker-command file for the fastcopytest application
 */
-l fastcopytestcfg.cmd


_FCPY_IFCPY = _FCPY_TI_IFCPY;
_FCPY_IDMA3 = _FCPY_TI_IDMA3;
_DMAN3_EDMA3BASE = 0x02A00000;

SECTIONS
{    

    .image       >      DDR2 
    .internal    >      L1DSRAM
   
}
