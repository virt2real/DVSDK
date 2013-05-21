/* THIS IS A GENERATED FILE -- DO NOT EDIT */

/* return the names of the generated config objects */
function getLibs(prog) {
    /* for programs, push the generated config object file into the
     * generated linker command file.
     */
    var name   = 'package/cfg/' + prog.name.replace('.','_');
    var suffix = prog.build.target.suffix;

    var libs = [
        name + '.o' + suffix,
    ];

    return libs.join(';');
}
