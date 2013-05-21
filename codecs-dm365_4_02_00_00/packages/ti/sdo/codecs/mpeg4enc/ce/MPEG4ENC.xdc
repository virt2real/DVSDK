/*!
 *  ======== MPEG4ENC========
 *  MPEG4ENC codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video1.IVIDENC1, MPEG4ENC declares that it "is
 *  a" video1 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the MPEG4ENC algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module MPEG4ENC inherits ti.sdo.ce.video1.IVIDENC1
{
    readonly config ti.sdo.codecs.mpeg4enc.MPEG4ENC.Module alg =
        ti.sdo.codecs.mpeg4enc.MPEG4ENC;
    
    override readonly config String ialgFxns = "MP4VENC_TI_IMP4VENC";

    override readonly config String iresFxns = "MP4VENC_TI_IRES";

}
