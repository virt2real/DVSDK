/*
 *  Linker command file template for run-time configuration app.
 *  Copy this file to your build directory, and add codec libraries, to
 *  build Linux apps with remote server for evm3530 with debug libraries.
 */
INPUT(
    /* Codec class libraries. */
    ti/sdo/ce/audio/lib/debug/audio.av5T
    ti/sdo/ce/image/lib/debug/image.av5T
    ti/sdo/ce/speech/lib/debug/speech.av5T
    ti/sdo/ce/video/lib/debug/video.av5T
    ti/sdo/ce/audio1/lib/debug/auddec1.av5T
    ti/sdo/ce/audio1/lib/debug/audenc1.av5T
    ti/sdo/ce/image1/lib/debug/imgdec1.av5T
    ti/sdo/ce/image1/lib/debug/imgenc1.av5T
    ti/sdo/ce/speech1/lib/debug/sphdec1.av5T
    ti/sdo/ce/speech1/lib/debug/sphenc1.av5T
    ti/sdo/ce/video1/lib/debug/viddec1.av5T
    ti/sdo/ce/video1/lib/debug/videnc1.av5T
    ti/sdo/ce/video2/lib/debug/viddec2.av5T
    ti/sdo/ce/universal/lib/debug/universal.av5T
    ti/sdo/ce/vidanalytics/lib/debug/vidanalytics.av5T
    ti/sdo/ce/vidtranscode/lib/debug/vidtranscode.av5T
    ti/sdo/ce/video2/split/lib/debug/viddec2back.av5T
    ti/sdo/ce/video2/split/lib/debug/viddec2front.av5T

    /* Codec engine libraries */
    ti/sdo/ce/lib/debug/ce.av5T
    ti/sdo/ce/alg/lib/debug/Algorithm_noOS.av5T
    ti/sdo/ce/alg/lib/debug/alg.av5T
    ti/sdo/ce/ipc/linux/lib/debug/ipc_linux.av5T
    ti/sdo/ce/osal/linux/lib/debug/osal_linux_470.av5T
    ti/sdo/ce/utils/xdm/lib/debug/XdmUtils.av5T
    ti/sdo/ce/node/lib/debug/node.av5T

    /* CMEM */
    ti/sdo/linuxutils/cmem/lib/cmem.a470MV
)
