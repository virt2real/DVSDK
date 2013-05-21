/*
 *  Linker command file for run-time configuration app. This file contains
 *  libraries specific to the app.
 */
INPUT(
    /* Codec libraries */
    ti/sdo/fc/ires/examples/codecs/auddec1/lib/release/auddec1_ti.a86U
    ti/xdais/dm/examples/audenc1_copy/lib/release/audenc1_copy.a86U
    
    /* IRES resource libraries needed by auddec1 ires codec */
    ti/sdo/fc/ires/bufres/lib/trace/bufres.a86U
)

