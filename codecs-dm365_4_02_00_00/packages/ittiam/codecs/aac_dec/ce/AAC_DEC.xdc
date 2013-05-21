/****************************************************************************
*                                                                           *
*                   ITTIAM SYSTEMS PVT LTD, BANGALORE                       *
*                          COPYRIGHT(C) 2008                                *
*                                                                           *
*  This program is proprietary to Ittiam Systems Pvt. Ltd. and is protected *
*  under Indian Copyright Act as an unpublished work.Its use and disclosure *
*  is  limited by  the terms and conditions of a license  agreement. It may *
*  be copied or  otherwise reproduced or  disclosed  to persons outside the *
*  licensee 's  organization  except  in  accordance  with  the  terms  and *
*  conditions of  such an agreement. All  copies and reproductions shall be *
*  the  property  of Ittiam Systems Pvt.  Ltd. and  must  bear  this notice *
*  in its entirety.                                                         *
*                                                                           *
*****************************************************************************/


/*!
 *  ======== AAC_DEC========
 *  AAC_DEC codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.audio1.AUDDEC1, AAC_DEC declares that it "is
 *  a" audio1 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the AAC_DEC algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module AAC_DEC inherits ti.sdo.ce.audio1.IAUDDEC1
{
    readonly config ittiam.codecs.aac_dec.AAC_DEC.Module alg = 
        ittiam.codecs.aac_dec.AAC_DEC;

    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "ENHAACPDECODER_ITTIAM_IENHAACPDECODER";
    override readonly config String iresFxns = "AUDCDC_ITTIAM_IRES";

}


