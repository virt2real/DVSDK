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
        if ( this.JPEGENC.watermark == false ) {
                lib = "lib/libjpgenc.a;lib/libimx.a";
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
        template = "ti/sdo/codecs/jpegenc/link.xdt";
    }

    return (template);
}
/*
 *  ======== VICPSYNC ========
 */
function close() {
xdc.useModule('ti.sdo.fc.vicpsync.VICPSYNC');
}
