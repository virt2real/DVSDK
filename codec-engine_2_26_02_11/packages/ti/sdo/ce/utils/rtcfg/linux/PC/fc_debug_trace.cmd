/*
 *  Linker command file template for run-time configuration app.
 *  Copy this file to your build directory, and add codec libraries, to
 *  build Linux apps for the PC with debug libraries.
 */
INPUT(
    /* Framework components libraries - GT trace enabled */

    /*
     *  Since there is no EDMA3 on the PC, use cpu-copy
     *  versions of acpy3 and dman3 libraries.
     */
    ti/sdo/fc/acpy3/lib/debug_trace/acpy3cpu.a86U
    ti/sdo/fc/dman3/lib/debug_trace/dman3cpu.a86U

    ti/sdo/fc/utils/lib/debug_trace/rmm.a86U
    ti/sdo/fc/utils/lib/debug_trace/smgr.a86U
    ti/sdo/fc/utils/lib/debug_trace/rmmp.a86U
    ti/sdo/fc/utils/lib/debug_trace/smgrmp.a86U
    ti/sdo/fc/utils/lib/debug_trace/shm.a86U
    ti/sdo/fc/memutils/lib/debug_trace/memutils_std.a86U
    ti/sdo/fc/rman/lib/debug_trace/rman.a86U

    /*
     *  These libraries may only be needed if RMAN is used. Put them here
     *  so the app doesn't have to add them.
     */
    ti/sdo/fc/ires/nullresource/lib/debug_trace/nullres.a86U
    ti/sdo/fc/ires/grouputils/lib/debug_trace/grouputils.a86U

    /* GT trace library */
    ti/sdo/utils/trace/lib/debug/gt.a86U
)

