/*
 *  Copyright 2009 by Texas Instruments Incorporated.
 *
 */

function run(cmdr, args)
{
    /* Check for command line parameters */
    if (
        (this.deviceModuleName == null) ||
        (this.registerSettings == null)) {
        cmdr.usage();
    }
    
    var e4x =  new XML(this.registerSettings);
    var regs = {};
    for each(var c in e4x.register) {
        regs[c.name[0]] = c.value[0];
    }
  
    
    var deviceModule = xdc.useModule(this.deviceModuleName);
    var inst = deviceModule.create("test");
    
    var memMap = inst.getMemoryMap(regs);
 
    
    var memList = new java.util.ArrayList();
    for (var c in memMap) {
        if (memMap[c].name != undefined) {
                var memSec = new xdc.jre.org.eclipse.rtsc.xdctools.ui.wizards.MemorySection(
                        memMap[c].name,memMap[c].base, memMap[c].len, 
                        memMap[c].space, memMap[c].access);
                memList.add(memSec);
            }
    }
    
    return memList;        
}








/*
 *  @(#) xdc.tools.platformWizard.memoryMap; 1,0,0,43; 11-20-2009 13:27:45; /db/ztree/library/trees/xdctools/xdctools-d08x/src/
 */

