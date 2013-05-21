/*
 *  Linker command file template for run-time configuration app.
 *  Copy this file to your build directory, and add codec libraries, to
 *  build Linux apps for the PC with debug libraries.
 */
INPUT(
    /* Codec class libraries. */
    ti/sdo/ce/audio/lib/debug/audio.a86U
    ti/sdo/ce/image/lib/debug/image.a86U
    ti/sdo/ce/speech/lib/debug/speech.a86U
    ti/sdo/ce/video/lib/debug/video.a86U
    ti/sdo/ce/audio1/lib/debug/auddec1.a86U
    ti/sdo/ce/audio1/lib/debug/audenc1.a86U
    ti/sdo/ce/image1/lib/debug/imgdec1.a86U
    ti/sdo/ce/image1/lib/debug/imgenc1.a86U
    ti/sdo/ce/speech1/lib/debug/sphdec1.a86U
    ti/sdo/ce/speech1/lib/debug/sphenc1.a86U
    ti/sdo/ce/video1/lib/debug/viddec1.a86U
    ti/sdo/ce/video1/lib/debug/videnc1.a86U
    ti/sdo/ce/video2/lib/debug/viddec2.a86U
    ti/sdo/ce/universal/lib/debug/universal.a86U
    ti/sdo/ce/vidanalytics/lib/debug/vidanalytics.a86U
    ti/sdo/ce/vidtranscode/lib/debug/vidtranscode.a86U
    ti/sdo/ce/video2/split/lib/debug/viddec2back.a86U
    ti/sdo/ce/video2/split/lib/debug/viddec2front.a86U

    /* Codec engine libraries */
    ti/sdo/ce/lib/debug/ce.a86U
    ti/sdo/ce/alg/lib/debug/Algorithm_noOS.a86U
    ti/sdo/ce/alg/lib/debug/alg.a86U
    ti/sdo/ce/ipc/linux/lib/debug/ipc_linux.a86U
    ti/sdo/ce/osal/linux/lib/debug/osal_linux_86U.a86U
    ti/sdo/ce/utils/xdm/lib/debug/XdmUtils.a86U
    ti/sdo/ce/node/lib/debug/node.a86U

)

