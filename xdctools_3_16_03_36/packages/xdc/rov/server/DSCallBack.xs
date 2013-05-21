/* --COPYRIGHT--,EPL
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * --/COPYRIGHT--*/
function instance$meta$init(controllerIndex)
{    
    this.$$bind('$controller', xdc.jre.com.ti.dvt.server4.ControllerMap.getController(controllerIndex));
}

function updateStartupProgress(percent, message)
{
    this.$controller.updateStartupProgress(percent, message);
}

function getAbortFlag()
{
    return (this.$controller.getAbortFlag());
}
