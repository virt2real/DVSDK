/*
 *  Linker command file template for run-time configuration app.
 *  Copy this file to your build directory, and add codec libraries, to
 *  build Linux apps with remote server for evm3530 with release libraries.
 */
INPUT(
    /* Codec class libraries. */
    ti/sdo/ce/audio/lib/release/audio.av5T
    ti/sdo/ce/image/lib/release/image.av5T
    ti/sdo/ce/speech/lib/release/speech.av5T
    ti/sdo/ce/video/lib/release/video.av5T
    ti/sdo/ce/audio1/lib/release/auddec1.av5T
    ti/sdo/ce/audio1/lib/release/audenc1.av5T
    ti/sdo/ce/image1/lib/release/imgdec1.av5T
    ti/sdo/ce/image1/lib/release/imgenc1.av5T
    ti/sdo/ce/speech1/lib/release/sphdec1.av5T
    ti/sdo/ce/speech1/lib/release/sphenc1.av5T
    ti/sdo/ce/video1/lib/release/viddec1.av5T
    ti/sdo/ce/video1/lib/release/videnc1.av5T
    ti/sdo/ce/video2/lib/release/viddec2.av5T
    ti/sdo/ce/universal/lib/release/universal.av5T
    ti/sdo/ce/vidanalytics/lib/release/vidanalytics.av5T
    ti/sdo/ce/vidtranscode/lib/release/vidtranscode.av5T
    ti/sdo/ce/video2/split/lib/viddec2back.av5T
    ti/sdo/ce/video2/split/lib/viddec2front.av5T

    /* Codec engine libraries */
    ti/sdo/ce/lib/release/ce.av5T
    ti/sdo/ce/alg/lib/release/Algorithm_noOS.av5T
    ti/sdo/ce/alg/lib/release/alg.av5T
    ti/sdo/ce/ipc/linux/lib/release/ipc_linux.av5T
    ti/sdo/ce/osal/linux/lib/release/osal_linux_470.av5T
    ti/sdo/ce/utils/xdm/lib/release/XdmUtils.av5T
    ti/sdo/ce/node/lib/release/node.av5T

    /* CMEM */
    ti/sdo/linuxutils/cmem/lib/cmem.a470MV
)
