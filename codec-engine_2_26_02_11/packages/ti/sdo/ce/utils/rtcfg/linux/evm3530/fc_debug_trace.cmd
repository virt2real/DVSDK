/*
 *  Linker command file template for run-time configuration app.
 *  Copy this file to your build directory, and add codec libraries, to
 *  build Linux apps for the PC with debug libraries.
 */
INPUT(
    /* Framework components libraries - GT trace enabled */

    /*
     *  Since there is no EDMA3 on the ARM side for OMAP3530, use cpu-copy
     *  versions of acpy3 and dman3 libraries.
     */
    ti/sdo/fc/acpy3/lib/debug_trace/acpy3cpu.a470MV
    ti/sdo/fc/dman3/lib/debug_trace/dman3cpu.a470MV

    ti/sdo/fc/utils/lib/debug_trace/rmm.av5T
    ti/sdo/fc/utils/lib/debug_trace/smgr.av5T
    ti/sdo/fc/utils/lib/debug_trace/rmmp.av5T
    ti/sdo/fc/utils/lib/debug_trace/smgrmp.av5T
    ti/sdo/fc/utils/lib/debug_trace/shm.av5T
    ti/sdo/fc/memutils/lib/debug_trace/memutils.av5T
    ti/sdo/fc/rman/lib/debug_trace/rman.av5T

    /*
     *  These libraries may only be needed if RMAN is used. Put them here
     *  so the app doesn't have to add them.
     */
    ti/sdo/fc/ires/nullresource/lib/debug_trace/nullres.av5T
    ti/sdo/fc/ires/grouputils/lib/debug_trace/grouputils.av5T

    /* GT trace library */
    ti/sdo/utils/trace/lib/debug/gt.av5T
)

