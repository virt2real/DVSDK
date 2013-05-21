/*!
 *  ======== MPEG4DEC_HDVICP========
 *  MPEG4DEC_HDVICP codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video2.IVIDDEC2, MPEG4DEC_HDVICP declares that it "is
 *  a" video2 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the MPEG4DEC_HDVICP algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module MPEG4DEC_HDVICP inherits ti.sdo.ce.video2.IVIDDEC2
{
    readonly config ti.sdo.codecs.mpeg4dec_hdvicp.MPEG4DEC_HDVICP.Module alg =
        ti.sdo.codecs.mpeg4dec_hdvicp.MPEG4DEC_HDVICP;
    
    override readonly config String ialgFxns = "MPEG4VDEC_TI_IMPEG4VDEC";

    override readonly config String iresFxns = "MPEG4VDEC_TI_IRES";

}
