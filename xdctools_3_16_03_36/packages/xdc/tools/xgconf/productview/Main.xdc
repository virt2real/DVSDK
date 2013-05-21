package xdc.tools.xgconf.productview;

/*
 * @_nodoc
 */
metaonly module Main inherits xdc.tools.ICmd {

    override config String usage[] = [
        'xs xdc.tools.xgconf.productview --packagePath <package_path> <productview module0> .. <productview moduleN>'
    ];

instance:

    @CommandOption("packagePath")
    config String packagePath = null;

}
