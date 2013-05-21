/*
 *  Linker command file template for run-time configuration app.
 *  Copy this file to your build directory, and add codec libraries, to
 *  build Linux apps for the PC with release libraries.
 */
INPUT(
    /* Codec class libraries. */
    ti/sdo/ce/audio/lib/release/audio.a86U
    ti/sdo/ce/image/lib/release/image.a86U
    ti/sdo/ce/speech/lib/release/speech.a86U
    ti/sdo/ce/video/lib/release/video.a86U
    ti/sdo/ce/audio1/lib/release/auddec1.a86U
    ti/sdo/ce/audio1/lib/release/audenc1.a86U
    ti/sdo/ce/image1/lib/release/imgdec1.a86U
    ti/sdo/ce/image1/lib/release/imgenc1.a86U
    ti/sdo/ce/speech1/lib/release/sphdec1.a86U
    ti/sdo/ce/speech1/lib/release/sphenc1.a86U
    ti/sdo/ce/video1/lib/release/viddec1.a86U
    ti/sdo/ce/video1/lib/release/videnc1.a86U
    ti/sdo/ce/video2/lib/release/viddec2.a86U
    ti/sdo/ce/universal/lib/release/universal.a86U
    ti/sdo/ce/vidanalytics/lib/release/vidanalytics.a86U
    ti/sdo/ce/vidtranscode/lib/release/vidtranscode.a86U
    ti/sdo/ce/video2/split/lib/viddec2back.a86U
    ti/sdo/ce/video2/split/lib/viddec2front.a86U

    /* Codec engine libraries */
    ti/sdo/ce/lib/release/ce.a86U
    ti/sdo/ce/alg/lib/release/Algorithm_noOS.a86U
    ti/sdo/ce/alg/lib/release/alg.a86U
    ti/sdo/ce/ipc/linux/lib/release/ipc_linux.a86U
    ti/sdo/ce/osal/linux/lib/release/osal_linux_86U.a86U
    ti/sdo/ce/utils/xdm/lib/release/XdmUtils.a86U
    ti/sdo/ce/node/lib/release/node.a86U
)
