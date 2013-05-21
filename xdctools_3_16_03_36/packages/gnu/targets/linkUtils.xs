/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== genSections ========
 *
 *  This function generates section allocations. 
 */
function genSections(prog)
{
    var res = "";

    /* the section map is constructed from the target and program info */
    var sectMap = prog.getSectMap();

    if (sectMap['xdc.meta'] == undefined) {
        sectMap['xdc.meta'] = new prog.SectionSpec();
        sectMap['xdc.meta'].type = "COPY";
    }

    /* 'xdc.noload' section is not allocated or loaded, if
     * xdc.runtime.Text.isLoaded is 'false'.
     */
    if (xdc.om['xdc.runtime.Text'].isLoaded != true
        && sectMap['xdc.noload'] == undefined) {
        sectMap['xdc.noload'] = new prog.SectionSpec();
        sectMap['xdc.noload'].type = "COPY";
    }

    for (var sn in sectMap) {
        res += "    " + sectLine(sectMap, sn) + "\n";
    }
    return (res);
}

/*
 *  ======== sectLine ========
 *  Generate a line to be placed in a linker command file for the specified
 *  section.
 */
function sectLine(sectMap, sn)
{

    /* map section name to a memory name */
    if (sectMap[sn] == null) {
        throw new Error("Allocation for section name '" + sn
            + "' is not defined by the program '" + prog.name
            + "' or the platform '" + Program.platformName + "'");
    }

    var map = sectMap[sn];
    var res = sn + " ";

    if (map.runAddress != null && map.runAddress != undefined) {
        res += "0x" + map.runAddress.toString(16) + " ";
    }
    if (map.type != null && map.type!= undefined) {
        res += "(" + map.type + ") ";
    }
    res += ": ";

    if (map.loadAddress != null && map.loadAddress != undefined) {
        res += "AT (0x" + map.loadAddress.toString(16) + ") ";
    }

    if (map.loadAlign != null && map.loadAlign != undefined) {
        res += "ALIGN (0x" + map.loadAlign.toString(16) + ") ";
    }
    else if (map.runAlign != null && map.runAlign != undefined) {
        res += "ALIGN (0x" + map.runAlign.toString(16) + ") ";
    }

    res += "{*(" + sn + ")} ";

    if ("fill" in map && map.fill != null && map.fill != undefined) {
        res += "= 0x" + map.fill.toString(16);
    }

    return (res);
}
/*
 *  @(#) gnu.targets; 1, 0, 1,387; 2-24-2010 16:24:01; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

