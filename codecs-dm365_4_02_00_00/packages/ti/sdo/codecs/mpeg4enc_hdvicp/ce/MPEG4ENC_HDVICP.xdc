/*!
 *  ======== MPEG4ENC_HDVICP========
 *  MPEG4ENC_HDVICP codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video1.IVIDENC1, MPEG4ENC_HDVICP declares that it "is
 *  a" video1 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the MPEG4ENC_HDVICP algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module MPEG4ENC_HDVICP inherits ti.sdo.ce.video1.IVIDENC1
{
    readonly config ti.sdo.codecs.mpeg4enc_hdvicp.MPEG4ENC_HDVICP.Module alg =
        ti.sdo.codecs.mpeg4enc_hdvicp.MPEG4ENC_HDVICP;
    
    override readonly config String ialgFxns = "MPEG4VENC_TI_IMPEG4VENC";

    override readonly config String iresFxns = "MPEG4VENC_TI_IRES";

}
