/*!
 *  ======== VC1DEC========
 *  VC1DEC codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video2.IVIDDEC2, VC1DEC declares that it "is
 *  a" video2 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the VC1DEC algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module VC1DEC inherits ti.sdo.ce.video2.IVIDDEC2
{
    readonly config ti.sdo.codecs.vc1dec.VC1DEC.Module alg =
        ti.sdo.codecs.vc1dec.VC1DEC;
    
    override readonly config String ialgFxns = "VC1VDEC_TI_IVC1VDEC";

    override readonly config String iresFxns = "VC1VDEC_TI_IRES";

}
