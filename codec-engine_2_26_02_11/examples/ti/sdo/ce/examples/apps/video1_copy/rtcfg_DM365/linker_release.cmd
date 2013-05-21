/*
 *  Linker command file template for run-time configuration app.
 *  Copy this file to your build directory, and add codec libraries, to
 *  build Linux apps for DM365 with release libraries.
 */
INPUT(
    /* Codec libraries */

    /* Video encoder library */
    ti/xdais/dm/examples/videnc1_copy/lib/release/videnc1_copy_dma.av5T

    /* Video decoder libray */
    ti/xdais/dm/examples/viddec1_copy/lib/release/viddec1_copy.av5T
)
