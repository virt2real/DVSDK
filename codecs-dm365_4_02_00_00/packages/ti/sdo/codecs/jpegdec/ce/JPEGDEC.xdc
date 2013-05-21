/*!
 *  ======== JPEGDEC========
 *  JPEGDEC codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.image1.IIMGDEC1, JPEGDEC declares that it "is
 *  a" image1 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the JPEGDEC algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module JPEGDEC inherits ti.sdo.ce.image1.IIMGDEC1
{
    readonly config ti.sdo.codecs.jpegdec.JPEGDEC.Module alg =
        ti.sdo.codecs.jpegdec.JPEGDEC;
    
    override readonly config String ialgFxns = "JPEGDEC_TI_IJPEGDEC";

    override readonly config String iresFxns = "JPEGDEC_TI_IRES";

}
