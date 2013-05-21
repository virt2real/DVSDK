/*!
 *  ======== MPEG4DEC========
 *  MPEG4DEC codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video2.IVIDDEC2, MPEG4DEC declares that it "is
 *  a" video2 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the MPEG4DEC algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module MPEG4DEC inherits ti.sdo.ce.video2.IVIDDEC2
{
    readonly config ti.sdo.codecs.mpeg4dec.MPEG4DEC.Module alg =
        ti.sdo.codecs.mpeg4dec.MPEG4DEC;
    
    override readonly config String ialgFxns = "MP4VDEC_TI_IMP4VDEC";

    override readonly config String iresFxns = "MP4VDEC_TI_IRES";

}
