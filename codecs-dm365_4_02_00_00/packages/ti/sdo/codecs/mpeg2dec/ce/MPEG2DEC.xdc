/*!
 *  ======== MPEG2DEC========
 *  MPEG2DEC codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video2.IVIDDEC2, MPEG2DEC declares that it "is
 *  a" video2 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the MPEG2DEC algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module MPEG2DEC inherits ti.sdo.ce.video2.IVIDDEC2
{
    readonly config ti.sdo.codecs.mpeg2dec.MPEG2DEC.Module alg =
        ti.sdo.codecs.mpeg2dec.MPEG2DEC;
    
    override readonly config String ialgFxns = "MPEG2VDEC_TI_IMPEG2VDEC";

    override readonly config String iresFxns = "MPEG2VDEC_TI_IRES";

}
