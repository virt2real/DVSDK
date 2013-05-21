/*
 *  Linker command file template for run-time configuration app.
 *  Copy this file to your build directory, and add codec libraries, to
 *  build Linux apps for the PC with release libraries.
 */
INPUT(
    /* Framework components libraries - GT trace disabled */

    /*
     *  Since there is no EDMA3 on the PC, use cpu-copy
     *  versions of acpy3 and dman3 libraries.
     */
    ti/sdo/fc/acpy3/lib/release/acpy3cpu.a86U
    ti/sdo/fc/dman3/lib/release/dman3cpu.a86U

    ti/sdo/fc/utils/lib/release/rmm.a86U
    ti/sdo/fc/utils/lib/release/smgr.a86U
    ti/sdo/fc/utils/lib/release/rmmp.a86U
    ti/sdo/fc/utils/lib/release/smgrmp.a86U
    ti/sdo/fc/utils/lib/release/shm.a86U
    ti/sdo/fc/memutils/lib/release/memutils_std.a86U
    ti/sdo/fc/rman/lib/release/rman.a86U

    /*
     *  These libraries may only be needed if RMAN is used. Put them here
     *  so the app doesn't have to add them.
     */
    ti/sdo/fc/ires/nullresource/lib/release/nullres.a86U
    ti/sdo/fc/ires/grouputils/lib/release/grouputils.a86U

    /* GT trace library */
    ti/sdo/utils/trace/lib/release/gt.a86U
)

