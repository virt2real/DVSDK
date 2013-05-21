/*
 * Any additions to the generated linker-command files should be placed here
 */

/* -lbufres.a64P */

/*
 *  Create symbols that mark the base and end of the memory segment BUFMEM.
 */
SECTIONS {
    .bufmem_base: {
        _BUFMEM_base = .;
    } > BUFMEM
    .bufmem_end: {
        _BUFMEM_end = .;
        . += 1;
    } > BUFMEM (HIGH)
}

