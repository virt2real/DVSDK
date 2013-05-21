/*****************************************************************************/
/*                                                                           */
/*                   ITTIAM SYSTEMS PVT LTD, BANGALORE                       */
/*                          COPYRIGHT(C) 2008                                */
/*                                                                           */
/*  This program is proprietary to Ittiam Systems Pvt. Ltd. and is protected */
/*  under Indian Copyright Act as an unpublished work.Its use and disclosure */
/*  is  limited by  the terms and conditions of a license  agreement. It may */
/*  be copied or  otherwise reproduced or  disclosed  to persons outside the */
/*  licensee 's  organization  except  in  accordance  with  the  terms  and */
/*  conditions of  such an agreement. All  copies and reproductions shall be */
/*  the  property  of Ittiam Systems Pvt.  Ltd. and  must  bear  this notice */
/*  in its entirety.                                                         */
/*                                                                           */
/*****************************************************************************/


/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var name = null;
    
    name = "lib_production/aac_dec_prod.a";

    print("    will link with " + this.$name + ":" + name);

    return (name);
}

/*
 *  ======== getSects ========
 */
function getSects()
{
    var template = null;
    //template = "ittiam/codecs/aac_dec/link.xdt";
    return (template);
}


/*
 *  ======== close ========
 */
function close() 
{
	xdc.useModule('ti.sdo.fc.ires.addrspace.ADDRSPACE');
	xdc.useModule('ti.sdo.fc.memutils.MEMUTILS'); 
}
