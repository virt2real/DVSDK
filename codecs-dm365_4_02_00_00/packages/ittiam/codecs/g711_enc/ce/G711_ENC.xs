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

/*
 *  ======== G711_ENC.xs ========
 *  This file implements the functions specified in the ti.sdo.ce.ICodec
 *  interface.  These functions enable the configuration tool to validate
 *  user supplied configuration parameters (e.g., stack size for the
 *  thread running this codec).
 */

var verbose = false;   /* set to true to enable verbose output during config */

/*
 *  ======== getCreationStackSize ========
 */
function getCreationStackSize(prog)
{
    if (verbose) {
    print("getting Creation stack size for " + this.$name
        + " built for the target " + prog.build.target.$name
        + ", running on platform " +  prog.platformName);
    }
    
    return (4096);
}

/*
 *  ======== getDaramScratchSize ========
 */
function getDaramScratchSize(prog)
{
    if (verbose) {
  print("getting DARAM scratch size for " + this.$name
      + " built for the target " + prog.build.target.$name
      + ", running onplatform " +  prog.platformName);
    }

    return (0);
}

/*
 *  ======== getSaramScratchSize ========
 */
function getSaramScratchSize(prog)
{
    if (verbose) {
  print("getting SARAM scratch size for " + this.$name
      + " built for the target " + prog.build.target.$name
      + ", running onplatform " +  prog.platformName);
    }

    return (0);
}

/*
 *  ======== getStackSize ========
 */
function getStackSize(prog)
{
    if (verbose) {
  print("getting stack size for " + this.$name
      + " built for the target " + prog.build.target.$name
      + ", running on platform " +  prog.platformName);
    }

    return (4096);
}
