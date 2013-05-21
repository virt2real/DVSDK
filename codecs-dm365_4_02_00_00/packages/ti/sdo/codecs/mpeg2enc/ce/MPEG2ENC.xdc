/*!
 *  ======== MPEG2ENC========
 *  MPEG2ENC codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video1.IVIDENC1, MPEG2ENC declares that it "is
 *  a" video1 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the MPEG2ENC algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module MPEG2ENC inherits ti.sdo.ce.video1.IVIDENC1
{
    readonly config ti.sdo.codecs.mpeg2enc.MPEG2ENC.Module alg =
        ti.sdo.codecs.mpeg2enc.MPEG2ENC;
    
    override readonly config String ialgFxns = "MPEG2VENC_TI_IMPEG2VENC";

    override readonly config String iresFxns = "MPEG2VENC_TI_IRES";

}
