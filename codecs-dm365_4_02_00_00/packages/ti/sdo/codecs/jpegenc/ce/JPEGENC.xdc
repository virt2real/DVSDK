/*!
 *  ======== JPEGENC========
 *  JPEGENC codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.image1.IIMGENC1, JPEGENC declares that it "is
 *  a" image1 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the JPEGENC algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module JPEGENC inherits ti.sdo.ce.image1.IIMGENC1
{
    readonly config ti.sdo.codecs.jpegenc.JPEGENC.Module alg =
        ti.sdo.codecs.jpegenc.JPEGENC;
    
    override readonly config String ialgFxns = "JPEGENC_TI_IJPEGENC";

    override readonly config String iresFxns = "JPEGENC_TI_IRES";

}
