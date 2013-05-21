/*
 *  ======== package.xs ========
 *
 */

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var lib = null;
  
    if (prog.build.target.isa == "v5T") {        
        if ( this.H264ENC.watermark == false ) {
                lib = "lib/h264venc_ti_arm926.a;lib/h264v_ti_dma_dm365.a";
        }
        else {
                lib = null;
        }
        print("    will link with " + this.$name + ":" + lib);
    }
    return (lib);
}

/*
 *  ======== getSects ========
 */
function getSects()
{
    var template = null;

    if (Program.build.target.isa == "v5T") {
        template = "ti/sdo/codecs/h264enc/link.xdt";
    }

    return (template);
}

/*
* Needed so lib link deck has this lib after CODEC.
*/
function close() 
{
     xdc.useModule('ti.sdo.fc.hdvicpsync.HDVICPSYNC');
}
