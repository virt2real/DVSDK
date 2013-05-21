/*!
 *  ======== H264DEC========
 *  H264DEC codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video2.IVIDDEC2, H264DEC declares that it "is
 *  a" video2 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the H264DEC algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module H264DEC inherits ti.sdo.ce.video2.IVIDDEC2
{
    readonly config ti.sdo.codecs.h264dec.H264DEC.Module alg =
        ti.sdo.codecs.h264dec.H264DEC;
    
    override readonly config String ialgFxns = "H264VDEC_TI_IH264VDEC";

    override readonly config String iresFxns = "H264VDEC_TI_IRES";

}
