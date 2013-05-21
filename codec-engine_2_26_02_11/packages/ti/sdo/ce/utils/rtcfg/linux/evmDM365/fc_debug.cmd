/*
 *  Linker command file template for run-time configuration app.
 *  Copy this file to your build directory, and add codec libraries, to
 *  build Linux apps for the PC with debug libraries.
 */
INPUT(
    /* Framework components libraries - GT trace disabled */
    ti/sdo/fc/acpy3/lib/debug/acpy3.a470MV
    ti/sdo/fc/dman3/lib/debug/dman3.a470MV
    ti/sdo/fc/utils/lib/debug/rmm.av5T
    ti/sdo/fc/utils/lib/debug/smgr.av5T
    ti/sdo/fc/utils/lib/debug/rmmp.av5T
    ti/sdo/fc/utils/lib/debug/smgrmp.av5T
    ti/sdo/fc/utils/lib/debug/shm.av5T
    ti/sdo/fc/memutils/lib/debug/memutils.av5T
    ti/sdo/fc/rman/lib/debug/rman.av5T

    /*
     *  These libraries may only be needed if RMAN is used. Put them here
     *  so the app doesn't have to add them.
     */
    ti/sdo/fc/ires/nullresource/lib/debug/nullres.av5T
    ti/sdo/fc/ires/grouputils/lib/debug/grouputils.av5T

    /* GT trace library */
    ti/sdo/utils/trace/lib/debug/gt.av5T
)

