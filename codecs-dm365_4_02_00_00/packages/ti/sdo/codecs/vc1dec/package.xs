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
       lib = "lib/vc1vdec_ti_arm926.a;lib/dma_ti_dm365.a"; 
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
        template = "ti/sdo/codecs/vc1dec/link.xdt";
    }

    return (template);
}

/*
* Needed so lib link deck has this lib after CODEC.
*/
function close() {
xdc.useModule('ti.sdo.fc.hdvicpsync.HDVICPSYNC');
}