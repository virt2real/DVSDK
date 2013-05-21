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
        if ( this.JPEGDEC.watermark == false ) {
                lib = "lib/libjpgdec.a;lib/libimx.a";
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
        template = "ti/sdo/codecs/jpegdec/link.xdt";
    }

    return (template);
}

/*
 *  ======== VICPSYNC ========
 */
function close() {
xdc.useModule('ti.sdo.fc.vicpsync.VICPSYNC');
}
