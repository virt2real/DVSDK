/*
 *  Linker command file for run-time configuration app. This file contains
 *  libraries specific to the app.
 */
INPUT(
    /* Codec libraries */
    ti/sdo/fc/ires/examples/codecs/auddec1/lib/release/auddec1_ti.av5T
    ti/xdais/dm/examples/audenc1_copy/lib/release/audenc1_copy.av5T

    /* IRES resource libraries */
    ti/sdo/fc/ires/bufres/lib/trace/bufres.av5T
)
