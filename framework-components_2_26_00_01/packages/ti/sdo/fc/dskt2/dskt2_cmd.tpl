%%{
    var extScratch = (this.ALLOWEXTERNALSCRATCH == true) ? 1 : 0;
    var cpu = prog.cpu.attrs.cpuCore;
    var is6x = (cpu[0] == '6') ? true : false;
    var pageString = (is6x) ? "" : "PAGE 0";
%%}

/* DSKT2 linker output */

__DSKT_DARAM0   = `this.DARAM0SEG.heapLabel.name`;
__DSKT_DARAM1   = `this.DARAM1SEG.heapLabel.name`;
__DSKT_DARAM2   = `this.DARAM2SEG.heapLabel.name`;
__DSKT_SARAM0   = `this.SARAM0SEG.heapLabel.name`;
__DSKT_SARAM1   = `this.SARAM1SEG.heapLabel.name`;
__DSKT_SARAM2   = `this.SARAM2SEG.heapLabel.name`;
__DSKT_IPROG    = `this.IPROGSEG.heapLabel.name`;
__DSKT_EPROG    = `this.EPROGSEG.heapLabel.name`;
__DSKT_ESDATA   = `this.EXTERNALSEG.heapLabel.name`;
__DSKT_EXTERNAL = `this.EXTERNALSEG.heapLabel.name`;

__DSKT2_ALLOW_EXTERNAL_SCRATCH = `extScratch`;
__DSKT2_HEAP = `this.OWNDATASEG.heapLabel.name`;

SECTIONS {
    .dskt2: {} > `this.DSKT2SEG.name` `pageString`
}
