/*
 *  Linker command file template for run-time configuration app.
 *  Copy this file to your build directory, and add codec libraries, to
 *  build Linux apps for the PC with release libraries.
 */
INPUT(
    /* Framework components libraries - GT trace enabled */

    ti/sdo/fc/acpy3/lib/trace/acpy3.a470MV
    ti/sdo/fc/dman3/lib/trace/dman3.a470MV
    ti/sdo/fc/utils/lib/trace/rmm.av5T
    ti/sdo/fc/utils/lib/trace/smgr.av5T
    ti/sdo/fc/utils/lib/trace/rmmp.av5T
    ti/sdo/fc/utils/lib/trace/smgrmp.av5T
    ti/sdo/fc/utils/lib/trace/shm.av5T
    ti/sdo/fc/memutils/lib/trace/memutils.av5T
    ti/sdo/fc/rman/lib/trace/rman.av5T

    /*
     *  These libraries may only be needed if RMAN is used. Put them here
     *  so the app doesn't have to add them.
     */
    ti/sdo/fc/ires/nullresource/lib/trace/nullres.av5T
    ti/sdo/fc/ires/grouputils/lib/trace/grouputils.av5T

    /* GT trace library */
    ti/sdo/utils/trace/lib/release/gt.av5T
)

