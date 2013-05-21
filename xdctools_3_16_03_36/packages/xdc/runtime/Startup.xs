/* --COPYRIGHT--,ESD
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * --/COPYRIGHT--*/
/*
 *  ======== module$use ========
 */
function module$use()
{
    xdc.useModule("xdc.runtime.Reset");
    Program.freezeRomConfig(this.$name, 'maxPasses');
    Program.freezeRomConfig(this.$name, 'startModsFxn');
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(obj, params)
{
    obj.stateTab = null;
    obj.execFlag = false;
    obj.rtsDoneFlag = false;

    for each (var mod in Program.targetModules()) {
        Program.freezeRomConfig(mod.$name, 'Module__startupDoneFxn');
        if (mod.MODULE_STARTUP$) {
            this.sfxnTab.$add('&' + mod.$name.replace(/\./g, '_') + 
                '_Module_startup__E');
            var rtsFxn = false;
            if (mod.$package.$name == 'xdc.runtime') {
                rtsFxn = true;
            }
            else {
                var iL = mod.$spec.getInherits().toArray();
                rtsFxn = iL.length > 1 && 
                    iL[iL.length - 2].getPkgName() == 'xdc.runtime';
            }
            this.sfxnRts.$add(rtsFxn);
        }
    }
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

