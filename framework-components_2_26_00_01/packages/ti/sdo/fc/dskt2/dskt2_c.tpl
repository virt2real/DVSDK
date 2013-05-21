%%{
    var cpu = prog.cpu.attrs.cpuCore;
    var is6x = (cpu[0] == '6') ? true : false;
    var farString = (is6x) ? "far " : "";

    var objs = this.instances();

    var numGroups = 0;
    while (objs[0].hasOwnProperty("scrGroup" + numGroups + "ScratchSize")) {
        numGroups++;
    }

    var cacheWBInvFxn;
    if (this.CACHEWBINVFXN == null) {
        cacheWBInvFxn = "NULL";
    }
    else {
        cacheWBInvFxn = this.CACHEWBINVFXN.name;
        if (this.CACHEWBINVFXN.language == "C") {
            // Ignore the leading "_" for C names
            cacheWBInvFxn = cacheWBInvFxn.substr(1);
        }
    }
%%}

/* DSKT2 C source output */

#include <ti/sdo/fc/dskt2/dskt2.h>

%if (this.CACHEWBINVFXN != null) {
extern Void `cacheWBInvFxn`(Ptr, size_t, Bool);
%}
%
%if (is6x) {
far DSKT2_CacheWBInvFxn DSKT2_cacheWBInvFxn = `cacheWBInvFxn`;
%}
%else {
DSKT2_CacheWBInvFxn DSKT2_cacheWBInvFxn = NULL;
%}

%var dskt2objs = this.instances();
%for (var i = 0 ; i < dskt2objs.length ; i++) {
%    var a = dskt2objs[i];
%    if (a.name == "DSKT2_daramScratch") {
`farString`Uns _DSKT2_DARAM_SCRATCH_SIZES[`numGroups`] = {
%    }
%    else {
`farString`Uns _DSKT2_SARAM_SCRATCH_SIZES[`numGroups`] = {
%}
%    for (var j = 0; j < numGroups; j++) {
%        var tmp = "a.scrGroup" + j + "ScratchSize";
%        var size = eval(tmp);
     `utils.toHex(size)`,  /* `j` */
%    }
};
 
%}

