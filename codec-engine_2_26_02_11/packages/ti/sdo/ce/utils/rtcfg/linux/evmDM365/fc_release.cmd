/*
 *  Linker command file template for run-time configuration app.
 *  Copy this file to your build directory, and add codec libraries, to
 *  build Linux apps for the PC with release libraries.
 */
INPUT(
    /* Framework components libraries - GT trace disabled */
    ti/sdo/fc/acpy3/lib/release/acpy3.a470MV
    ti/sdo/fc/dman3/lib/release/dman3.a470MV
    ti/sdo/fc/utils/lib/release/rmm.av5T
    ti/sdo/fc/utils/lib/release/smgr.av5T
    ti/sdo/fc/utils/lib/release/rmmp.av5T
    ti/sdo/fc/utils/lib/release/smgrmp.av5T
    ti/sdo/fc/utils/lib/release/shm.av5T
    ti/sdo/fc/memutils/lib/release/memutils.av5T
    ti/sdo/fc/rman/lib/release/rman.av5T

    /*
     *  These libraries may only be needed if RMAN is used. Put them here
     *  so the app doesn't have to add them.
     */
    ti/sdo/fc/ires/nullresource/lib/release/nullres.av5T
    ti/sdo/fc/ires/grouputils/lib/release/grouputils.av5T

    /* GT trace library */
    ti/sdo/utils/trace/lib/release/gt.av5T
)

